/* Copyright (c) 2019-2020 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODNE2K_NE2K_C
#define GUARD_MODNE2K_NE2K_C 1
#define _KOS_SOURCE 1

#include "ne2k.h"

#include <kernel/compiler.h>

#include <drivers/pci.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/isr.h>
#include <kernel/printk.h>
#include <sched/cpu.h>

#include <hybrid/atomic.h>

#include <kos/except/io.h>
#include <kos/io/ne2k.h>
#include <sys/io.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

PRIVATE NOBLOCK bool
NOTHROW(FCALL Ne2k_InterruptHandler)(void *arg) {
	Ne2kDevice *me;
	u8 status;
	me = (Ne2kDevice *)arg;

	/* Start receiving data. (XXX: Is this really required?) */
	outb(E8390_CMD(me->nd_iobase), E8390_NODMA | E8390_START);

	/* Read the interrupt status register. */
	status = inb(EN0_ISR(me->nd_iobase)) & ENISR_ALL;
	if (!status)
		return false; /* Not our interrupt... */

	printk(KERN_DEBUG "[ne2k] Interrupt: %p: %#.2I8x!\n", me, status);
	if (status & ENISR_RX) {
		/* Schedule a job to safely receive data. */

		/* TODO: Signal an async worker to start receiving packet data. */

		/* Since we're going to re-enable interrupts before
		 * data will actually be read, we must mask all
		 * interrupts caused by the chip, so-as not to deal
		 * with multiple incoming packets at once. */
		outb(EN0_IMR(me->nd_iobase), ENISR_ALL & ~(ENISR_RX));

		/* Don't acknowledge the receive signal below.
		 * It will only be acknowledged once the data loader job has finished. */
		status &= ~ENISR_RX;
	}

	if (status & ENISR_RX_ERR) {
		u8 recv_error = inb(EN0_TSR(me->nd_iobase));
		printk(KERN_ERR "[ne2k] Receive error: %.2I8x\n", recv_error);
		/* TODO: Handle `recv_error' by passing it to the async worker */
	}

	if (status & (ENISR_TX | ENISR_TX_ERR)) {
		u8 transmit_status;
		if (status & ENISR_TX_ERR) {
			transmit_status = inb(EN0_TSR(me->nd_iobase));
			if (transmit_status & ENTSR_EMSK)
				printk(KERN_ERR "[ne2k] Transmit error: %.2I8x\n", transmit_status);
		} else {
			transmit_status = ENISR_TX; /* Successful transmission. */
		}
		/*dev->n_senderr = transmit_status;*/
		/* TODO: Handle `transmit_status' by passing it to the async worker */
		/* Acknowledge errors */
		if (status & ENISR_TX_ERR)
			outb(EN0_ISR(me->nd_iobase), ENISR_TX_ERR);
		if (status & ENISR_TX)
			outb(EN0_ISR(me->nd_iobase), ENISR_TX);
		COMPILER_WRITE_BARRIER();
		semaphore_post(&me->nd_txisr);
	}

	if unlikely(status & ENISR_OVER)
		printk(KERN_ERR "[ne2k] Receiver overwrote the ring\n");
	if unlikely(status & ENISR_COUNTERS)
		printk(KERN_ERR "[ne2k] Counters need emptying\n");
	/* Acknowledge all handled signals. */
	if (status)
		outb(EN0_ISR(me->nd_iobase), status);
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL Ne2k_Fini)(struct character_device *__restrict self) {
	Ne2kDevice *me;
	me = (Ne2kDevice *)self;
	hisr_unregister(&Ne2k_InterruptHandler, me);
	nic_device_fini(me);
}

struct ne2k_upload_printer_data {
	port_t nup_dataport; /* [const] Data output port. */
	u8     nup_half;     /* Half-word */
	bool   nup_hashalf;  /* Half-word-valid */
};

LOCAL void KCALL
Ne2k_PrintData(struct ne2k_upload_printer_data *__restrict self,
               USER CHECKED void const *data, size_t num_bytes) {
	if unlikely(self->nup_hashalf) {
		union {
			u16 w;
			u8 b[2];
		} word;
		if unlikely(!num_bytes)
			return;
		word.b[0] = self->nup_half;
		word.b[1] = *(byte_t *)data;
		data = (byte_t *)data + 1;
		--num_bytes;
		outw(self->nup_dataport, word.w);
		self->nup_hashalf = false;
	}
	outsw(self->nup_dataport, data, num_bytes / 2);
	if unlikely(num_bytes & 1) {
		self->nup_hashalf = true;
		self->nup_half = ((byte_t *)data)[num_bytes - 1];
	}
}

PRIVATE void KCALL
Ne2k_UploadPacketImpl(struct ne2k_upload_printer_data *__restrict printer,
                      struct nic_packet const *__restrict self) {
again:
	/* Printer header data */
	Ne2k_PrintData(printer, self->np_head, self->np_headsz);
	if (self->np_inner) {
		/* Print wrapped packet data. */
		if (!self->np_tailsz) {
			/* Inline-optimization */
			self = self->np_inner;
			goto again;
		}
		Ne2k_UploadPacketImpl(printer, self->np_inner);
	}
	/* Printer tail data */
	Ne2k_PrintData(printer, self->np_tail, self->np_tailsz);
}

PRIVATE void KCALL
Ne2k_UploadPacket(port_t dataport,
                  struct nic_packet const *__restrict self) {
	struct ne2k_upload_printer_data d;
	d.nup_dataport = dataport;
	d.nup_hashalf  = false;
	Ne2k_UploadPacketImpl(&d, self);
	if unlikely(d.nup_hashalf) {
		union {
			u16 w;
			u8 b[2];
		} word;
		word.b[0] = d.nup_half;
		word.b[1] = 0;
		outw(dataport, word.w);
	}
}

PRIVATE void KCALL
Ne2k_WaitForRemoteDmaComplete(Ne2kDevice *__restrict self) {
	u8 status;
	status = inb(EN0_ISR(self->nd_iobase));
	if (!(status & ENISR_RDC)) {
		struct timespec timeout;
		timeout = realtime();
		timeout.add_milliseconds(400);
		while (!((status = inb(EN0_ISR(self->nd_iobase))) & ENISR_RDC)) {
			if (realtime() > timeout) {
				printk(KERN_WARNING "[ne2k] Timeout waiting for remote-dma-complete on card at %#I16x\n",
				       self->nd_iobase);
				THROW(E_IOERROR_TIMEOUT,
				      E_IOERROR_SUBSYSTEM_NET,
				      E_IOERROR_REASON_NE2K_WAIT4RDMA);
			}
			task_tryyield_or_pause();
		}
	}
	/* Acknowledge remote DMA completion. */
	outb(EN0_ISR(self->nd_iobase), ENISR_RDC);
}

PRIVATE void KCALL
Ne2k_SendPacket(struct nic_device *__restrict self,
                struct nic_packet const *__restrict packet,
                /*out*/ struct aio_handle *__restrict aio) {
	Ne2kDevice *me;
	u16 aligned_size;
	me = (Ne2kDevice *)self;
	aligned_size = packet->np_total;
	if unlikely(aligned_size & 1)
		++aligned_size;

	{
		/* TODO: Don't use an rwlock here!
		 *       Instead, use a pending-ops-chain alongside an async worker
		 *       that gets triggered by device interrupts and will handle
		 *       pending tasks asynchronously. */
		SCOPED_WRITELOCK(&me->nd_iolock);

		/* Perform a read-before-write. */
		outb(E8390_CMD(me->nd_iobase), E8390_PAGE0 | E8390_RREAD | E8390_START);
		outb(EN0_RCNTLO(me->nd_iobase), 1);
		outb(E8390_CMD(me->nd_iobase), E8390_PAGE0 | E8390_NODMA | E8390_START);
		outb(EN0_ISR(me->nd_iobase), ENISR_RDC); /* ACK remote-dma-completed for the read */
		outb(EN0_RCNTLO(me->nd_iobase), aligned_size & 0xff);
		outb(EN0_RCNTHI(me->nd_iobase), aligned_size >> 8);
		outb(EN0_RSARLO(me->nd_iobase), 0);
		outb(EN0_RSARHI(me->nd_iobase), me->nd_tx_start);
		outb(E8390_CMD(me->nd_iobase), E8390_PAGE0 | E8390_RWRITE | E8390_START);

		/* Copy packet data onto the NIC.
		 * XXX: In theory, packet uploading could also be done asynchronously,
		 *      since AIO requires that buffers remain valid until the I/O is
		 *      canceled, or completes. */
		Ne2k_UploadPacket(NE_DATAPORT(me->nd_iobase), packet);

		/* Wait for the card to ACK the DMA completion. */
		Ne2k_WaitForRemoteDmaComplete(me);

		ATOMIC_WRITE(me->nd_txisr.s_count, 0);

		/* Perform the transmission. */
		outb(E8390_CMD(me->nd_iobase), E8390_NODMA | E8390_START);
		outb(EN0_TPSR(me->nd_iobase), me->nd_tx_start);
		outb(EN0_TCNTLO(me->nd_iobase), aligned_size & 0xff);
		outb(EN0_TCNTHI(me->nd_iobase), aligned_size >> 8);
		outb(E8390_CMD(me->nd_iobase), E8390_TRANS | E8390_NODMA | E8390_START);

		/* TODO: Use an async command-chain */
		semaphore_wait(&me->nd_txisr);
	}

	/* TODO: Route `aio' to be marked as completed once a transmit-complete interrupt is fired */
	/* TODO: Route `aio's cancel operator to half transmission */
	aio_handle_init(aio, &aio_noop_type);
	aio_handle_success(aio);
}

PRIVATE uintptr_t KCALL
Ne2k_ApplyFlagsUnlocked(Ne2kDevice *__restrict self,
                        uintptr_t flags)
		THROWS(E_IOERROR) {
	u8 temp;
	unsigned int i;
	Ne2k_ResetCard(self->nd_iobase);
	self->nd_rx_nxt = self->nd_rx_start;
	if (!(flags & IFF_UP))
		return flags;
	/* Acknowledge interrupts. (From `Ne2k_ResetCard()') */
	outb(EN0_ISR(self->nd_iobase), 0xff);
	outb(E8390_CMD(self->nd_iobase), E8390_PAGE0 | E8390_STOP | E8390_NODMA);

	/* Set word-wide mode & enable loop-back. */
	outb(EN0_DCFG(self->nd_iobase), ENDCFG_FT1 | ENDCFG_LS | ENDCFG_WTS);

	/* Clear count registers. */
	outb(EN0_RCNTLO(self->nd_iobase), 0);
	outb(EN0_RCNTHI(self->nd_iobase), 0);

	/* Configure receive-mode */
	temp = 0;
	if (flags & IFF_LOOPBACK)
		temp |= ERXCR_MON;
	if (flags & IFF_PROMISC) /* Accept all packages. */
		temp |= ERXCR_AR | ERXCR_AB | ERXCR_AM | ERXCR_PRO;
	else {
		if (flags & IFF_ALLMULTI)
			temp |= ERXCR_AM;
		if (flags & IFF_BROADCAST)
			temp |= ERXCR_AB; /* Accept broadcast packages. */
	}
	outb(EN0_RXCR(self->nd_iobase), temp);

	/* Disable loopback for all packages. */
	outb(EN0_TXCR(self->nd_iobase), ETXCR_LOOPBACK_INTERN);

	/* Configure the card's receive buffer. */
	outb(EN0_BOUNDARY(self->nd_iobase), self->nd_rx_nxt);
	outb(EN0_STARTPG(self->nd_iobase), self->nd_rx_start);
	outb(EN0_STOPPG(self->nd_iobase), self->nd_rx_end);

	/* Acknowledge anything that may still be dangling. */
	outb(EN0_ISR(self->nd_iobase), 0xff);

	/* Enable all the interrupts that we are handling. */
	outb(EN0_IMR(self->nd_iobase), ENISR_ALL);

	/* Switch to page 1. */
	outb(E8390_CMD(self->nd_iobase), E8390_PAGE1 | E8390_STOP | E8390_NODMA);

	/* Configure the hardware address to listen for. */
	for (i = 0; i < ETH_ALEN; ++i)
		outb(EN1_PHYS_SHIFT(self->nd_iobase, i), self->nd_mac[i]);
	for (i = 0; i < 8; ++i) /* XXX: Multicast? */
		outb(EN1_MULT_SHIFT(self->nd_iobase, i), 0xff);
	/* Still being in page #1, set the next-package pointer. */
	outb(EN1_CURPAG(self->nd_iobase), self->nd_rx_nxt);

	/* Finally, turn on the card. */
	outb(E8390_CMD(self->nd_iobase), E8390_PAGE0 | E8390_NODMA | E8390_START);

	/* And disable loopback, allowing for outgoing packages. */
	if (!(flags & IFF_LOOPBACK))
		outb(EN0_TXCR(self->nd_iobase), ETXCR_LOOPBACK_NORMAL);

	flags |= IFF_RUNNING;
	return flags;
}

PRIVATE bool KCALL
Ne2k_SetFlags(struct nic_device *__restrict self,
              uintptr_t old_flags, uintptr_t new_flags) {
	Ne2kDevice *me;
	assert(!(new_flags & IFF_STATUS));
	assert((old_flags & IFF_CONST) == (new_flags & IFF_CONST));
	me = (Ne2kDevice *)self;
	SCOPED_WRITELOCK(&me->nd_iolock);
	if unlikely(self->nd_ifflags != old_flags)
		return false;
	Ne2k_ApplyFlagsUnlocked(me, new_flags);
	self->nd_ifflags = new_flags;
	return true;
}


PRIVATE struct nic_device_ops const Ne2k_NICDeviceOps = {
	/* .nd_send     = */ &Ne2k_SendPacket,
	/* .nd_setflags = */ &Ne2k_SetFlags,
};


PRIVATE ATTR_FREERODATA struct {
	u8 off;
	u8 val;
} const Ne2k_StartupSequence[] = {
	{ EN0_ISR(0),    0xff }, /* Acknowledge interrupts. (From `Ne2k_ResetCard()') */
	{ E8390_CMD(0),  E8390_PAGE0 | E8390_NODMA | E8390_STOP },
	{ EN0_DCFG(0),   ENDCFG_FT1 | ENDCFG_LS | ENDCFG_WTS }, /* Set word-wide mode. */
	{ EN0_RCNTLO(0), 0 },                                   /* Clear count registers. */
	{ EN0_RCNTHI(0), 0 },                                   /* ... */
	{ EN0_IMR(0),    0 },                                   /* Mask completion irq. */
	{ EN0_ISR(0),    0xff },                                /* ... */
	{ EN0_RXCR(0),   ERXCR_MON },                           /* Enable monitoring mode (Don't receive packages for now). */
	{ EN0_TXCR(0),   ETXCR_LOOPBACK_INTERN },               /* Set loopback mode to intern (Don't send packages for now). */
	/* At this point, we'll be trying to read the first couple bytes of PROM. */
	{ EN0_RCNTLO(0), NE_PROM_SIZE & 0xff },                 /* Setup a couple of bytes for reading. */
	{ EN0_RCNTHI(0), (NE_PROM_SIZE & 0xff00) >> 8 },        /* ... */
	{ EN0_RSARLO(0), 0 },                         /* Select DMA 0x0000 for reading. */
	{ EN0_RSARHI(0), 0 },                         /* ... */
	{ E8390_CMD(0),  E8390_RREAD | E8390_START }, /* Execute a remote read. */
};


PRIVATE ATTR_FREETEXT bool KCALL
Ne2k_ProbePciDevice(struct pci_device *__restrict dev) THROWS(...) {
	port_t iobase;
	unsigned int i;
	byte_t prom[NE_PROM_SIZE];
	REF Ne2kDevice *self;

	if (!(dev->pd_res[0].pr_flags & PCI_RESOURCE_FIO))
		return false;
	if (dev->pd_res[0].pr_size < 0xff)
		return false;
	iobase = (port_t)dev->pd_res[0].pr_start;
	printk(FREESTR(KERN_DEBUG "[ne2k] Found NE2K(%p) at %#I16x (pci:%#I32x)\n"),
	       dev, iobase, dev->pd_base);
	Ne2k_ResetCard(iobase);
	/* Execute a sequence of startup instructions. */
	for (i = 0; i < COMPILER_LENOF(Ne2k_StartupSequence); ++i) {
		outb(iobase +
		     Ne2k_StartupSequence[i].off,
		     Ne2k_StartupSequence[i].val);
	}

	/* Read PROM. */
	for (i = 0; i < NE_PROM_SIZE; i++)
		prom[i] = inb(NE_DATAPORT(iobase));
	outb(E8390_CMD(iobase), E8390_PAGE1 | E8390_STOP);

	printk(FREESTR(KERN_DEBUG "[ne2k] PROM:\n%$[hex]\n"),
	       sizeof(prom), prom);

	/* Construct the device. */
	self = CHARACTER_DEVICE_ALLOC(Ne2kDevice);
	FINALLY_DECREF_UNLIKELY(self);
	nic_device_cinit(self, &Ne2k_NICDeviceOps);
	rwlock_cinit_write(&self->nd_iolock);
	semaphore_cinit(&self->nd_txisr, 0);
	self->cd_type.ct_fini = &Ne2k_Fini;
	self->nd_pcidev = dev;
	self->nd_iobase = iobase;
	memcpy(self->nd_mac, prom, ETH_ALEN);
	self->nd_ifflags  = IFF_BROADCAST | IFF_MULTICAST;
	self->nd_tx_start = 64;
	self->nd_tx_end   = 70;
	self->nd_rx_start = 70;
	self->nd_rx_end   = 128;

	/* set-up IRQ handling. */
	hisr_register_at(X86_INTERRUPT_PIC1_BASE +
	                 PCI_GDEV3C_IRQLINE(pci_read(dev->pd_base, PCI_GDEV3C)),
	                 &Ne2k_InterruptHandler, self);

	/* Reset the NIC */
	self->nd_ifflags |= IFF_UP;
	Ne2k_ApplyFlagsUnlocked(self, self->nd_ifflags);
	sync_endwrite(&self->nd_iolock);

	{
		static unsigned int n = 0; /* XXX: Better naming */
		sprintf(self->cd_name, "ne2k%u", n++);
	}

	character_device_register_auto(self);
	return true;
}

PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL Ne2k_InitDriver(void) {
	struct pci_device *dev;
	PCI_FOREACH_CLASS(dev,
	                  PCI_DEV8_CLASS_NETWORK,
	                  PCI_DEV8_CLASS_NOCLASS) {
		TRY {
			Ne2k_ProbePciDevice(dev);
		} EXCEPT {
			error_printf(FREESTR("Initializing ne2k at pci:%#I32x"),
			             dev->pd_base);
		}
	}
	printk(KERN_DEBUG "NE2K: DONE\n");
}


DECL_END

#endif /* !GUARD_MODNE2K_NE2K_C */
