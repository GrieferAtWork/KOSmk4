/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_SERIAL_C
#define GUARD_MODGDBSERVER_SERIAL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/isr.h>
#include <kernel/printk.h>

#include <hybrid/host.h>
#include <hybrid/sched/preemption.h>

#include <hw/bus/serial.h>
#include <sys/io.h>

#include <inttypes.h>
#include <stdio.h>

#include "gdb.h"

#if defined(__i386__) || defined(__x86_64__)
#include <kernel/x86/cpuid.h>
#endif /* __i386__ || __x86_64__ */

DECL_BEGIN

PRIVATE u8     GDBSerial_IO_IsrVector;
PRIVATE port_t GDBSerial_IO_PortBase;

PRIVATE NOBLOCK bool
NOTHROW(FCALL GDBSerial_InterruptHandler)(void *UNUSED(arg)) {
	u8 iir = inb(SERIAL_IOADDR_IIR(GDBSerial_IO_PortBase));
	if (iir & SERIAL_IRR_NIP)
		return false; /* Not for us! */
	switch (iir & SERIAL_IRR_TYP) {

	case SERIAL_IRR_TYP_RDA:
	case SERIAL_IRR_TYP_CTO: {
		u8 data;
#if 1 /* The other variant produces unassigned interrupts. */
		data = inb(SERIAL_IOADDR_RBR(GDBSerial_IO_PortBase));
#ifdef X86_PIC_EOI
		X86_PIC_EOI(GDBSerial_IO_IsrVector);
#endif /* X86_PIC_EOI */
		GDBRemote_PostByte(data);
#else
		for (;;) {
			data  = inb(SERIAL_IOADDR_RBR(GDBSerial_IO_PortBase));
			GDBRemote_PostByte(data);
			/* Keep on reading while there is still data! */
			if (!(inb(SERIAL_IOADDR_LSR(GDBSerial_IO_PortBase)) & SERIAL_LSR_DA))
				break;
		}
#endif
	}	break;

	default:
		printk(KERN_WARNING "[gdb] Unexpected serial interrupt: %#.2" PRIx8 "\n", iir);
		break;
	}
	return true;
}

FORCELOCAL ATTR_ARTIFICIAL bool FCALL GDBSerial_IO_IsTransmitEmpty(void) {
	return inb(SERIAL_IOADDR_LSR(GDBSerial_IO_PortBase)) & SERIAL_LSR_THRE;
}

INTERN void
NOTHROW(FCALL GDBSerial_PutData)(void const *buf, size_t bufsize) {
#if defined(__i386__) || defined(__x86_64__)
#define MAKE_DWORD(a, b, c, d) ((u32)(a) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))
	if (bootcpu_x86_cpuid.ci_80000002a == MAKE_DWORD('Q', 'E', 'M', 'U')) {
		/* Slight optimization: QEMU doesn't care about transmit-empty.
		 * -> To make debugging with QEMU faster, write all data at once. */
		outsb(SERIAL_IOADDR_THR(GDBSerial_IO_PortBase), buf, bufsize);
	} else
#endif /* __i386__ || __x86_64__ */
	{
		size_t i;
		for (i = 0; i < bufsize; ++i) {
			while (!GDBSerial_IO_IsTransmitEmpty())
				task_tryyield_or_pause();
			outb(SERIAL_IOADDR_THR(GDBSerial_IO_PortBase), ((byte_t *)buf)[i]);
		}
	}
}


INTERN void FCALL GDBSerial_Init(char *args) {
	if (sscanf(args, "%" SCNU16 ":%" SCNU8,
	           &GDBSerial_IO_PortBase,
	           &GDBSerial_IO_IsrVector) != 2) {
		printk(KERN_ERR "[gdb] Invalid arguments for serial transport method: %q", args);
		THROW(E_INVALID_ARGUMENT);
	}
	printk(KERN_INFO "[gdb] Enable serial transport on port %#" PRIx16 " (isr#%#" PRIx8 ")\n",
	       GDBSerial_IO_PortBase, GDBSerial_IO_IsrVector);
	isr_register_at((isr_vector_t)GDBSerial_IO_IsrVector,
	                &GDBSerial_InterruptHandler, NULL);
	/* Configure serial */
	outb(SERIAL_IOADDR_IER(GDBSerial_IO_PortBase), 0);
	outb(SERIAL_IOADDR_LCR(GDBSerial_IO_PortBase), SERIAL_LCR_DLAB);
	outb(SERIAL_IOADDR_DLL(GDBSerial_IO_PortBase), SERIAL_DL_38400 & 0xff);
	outb(SERIAL_IOADDR_DLM(GDBSerial_IO_PortBase), SERIAL_DL_38400 >> 8);
	outb(SERIAL_IOADDR_LCR(GDBSerial_IO_PortBase), SERIAL_LCR_DWL_8 | SERIAL_LCR_STB_1 |
	                                               SERIAL_LCR_PRT_NO);
	outb(SERIAL_IOADDR_FCR(GDBSerial_IO_PortBase), SERIAL_FCR_ENABLED | SERIAL_FCR_CRFIFO |
	                                               SERIAL_FCR_CTFIFO | SERIAL_FCR_DMA_0 |
	                                               SERIAL_FCR_RITL_14);
	outb(SERIAL_IOADDR_MCR(GDBSerial_IO_PortBase), SERIAL_MCR_AXO2 | SERIAL_MCR_RTS |
	                                               SERIAL_MCR_DTR);
	{
		/* Check if data is already available (which is likely to be the case). */
		u8 avail = inb(SERIAL_IOADDR_LSR(GDBSerial_IO_PortBase));
		/* Enable  interrupts before we  read data, since once  we do that read,
		 * any additional data which may arrive from then on can trigger an IRQ! */
		outb(SERIAL_IOADDR_IER(GDBSerial_IO_PortBase), SERIAL_EIR_RDA);
		if (avail & SERIAL_LSR_DA) {
			u8 data = inb(SERIAL_IOADDR_RBR(GDBSerial_IO_PortBase));
			preemption_flag_t was;
			printk(KERN_INFO "[gdb] Processing initial byte %#.2" PRIx8 "\n", data);
			/* Calls to `GDBRemote_PostByte()' require that preemption be turned off. */
			preemption_pushoff(&was);
			GDBRemote_PostByte(data);
			preemption_pop(&was);
		}
	}
}

INTERN void FCALL GDBSerial_Fini(void) {
	isr_unregister_at((isr_vector_t)GDBSerial_IO_IsrVector,
	                  &GDBSerial_InterruptHandler, NULL);
}



DECL_END

#endif /* !GUARD_MODGDBSERVER_SERIAL_C */
