/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDB_REMOTE_SERIAL_C
#define GUARD_MODGDB_REMOTE_SERIAL_C 1

#include <kernel/compiler.h>
#include <kernel/interrupt.h>
#include <kernel/printk.h>
#include <kernel/except.h>
#include <hybrid/host.h>
#include <kos/io/serial.h>
#include <sys/io.h>
#include <stdio.h>

#if defined(__i386__) || defined(__x86_64__)
#include <kernel/pic.h>
#include <kernel/cpuid.h>
#endif

#include "gdb.h"

DECL_BEGIN


PRIVATE u8     GDBSerial_IO_IsrVector;
PRIVATE port_t GDBSerial_IO_PortBase;

INTERN NOBLOCK struct icpustate *
NOTHROW(FCALL GDBSerial_InterruptHandler)(struct icpustate *__restrict state) {
	u8 iir = inb(SERIAL_IOADDR_IIR(GDBSerial_IO_PortBase));
	if (iir & SERIAL_IRR_NIP)
		return NULL; /* Not for us! */
	switch (iir & SERIAL_IRR_TYP) {

	case SERIAL_IRR_TYP_RDA:
	case SERIAL_IRR_TYP_CTO: {
		u8 data;
#if 1 /* The other variant produces unassigned interrupts. */
		data = inb(SERIAL_IOADDR_RBR(GDBSerial_IO_PortBase));
#ifdef X86_PIC_EOI
		X86_PIC_EOI(GDBSerial_IO_IsrVector);
#endif /* X86_PIC_EOI */
		state = GDBRemote_PutByte(state, data);
#else
		for (;;) {
			data  = inb(SERIAL_IOADDR_RBR(GDBSerial_IO_PortBase));
			state = GDBRemote_PutByte(state, data);
			/* Keep on reading while there is still data! */
			if (!(inb(SERIAL_IOADDR_LSR(GDBSerial_IO_PortBase)) & SERIAL_LSR_DA))
				break;
		}
#endif
	}	break;

	default:
		printk(KERN_WARNING "Unexpected serial interrupt: %#.2I8x\n", iir);
		break;
	}
	return state;
}



FORCELOCAL bool FCALL GDBSerial_IO_IsTransmitEmpty(void) {
	return inb(SERIAL_IOADDR_LSR(GDBSerial_IO_PortBase)) & SERIAL_LSR_THRE;
}


INTERN void FCALL
GDBSerial_PutData(void const *buf, size_t bufsize) {
#if defined(__i386__) || defined(__x86_64__)
#define MAKE_DWORD(a, b, c, d) ((u32)(a) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))
	if (__x86_bootcpu_idfeatures.ci_80000002a == MAKE_DWORD('Q', 'E', 'M', 'U')) {
		/* Slight optimization: QEMU doesn't care about transmit-empty.
		 * -> To make debugging with QEMU faster, write all data at once. */
		outsb(SERIAL_IOADDR_THR(GDBSerial_IO_PortBase), buf, bufsize);
	} else
#endif
	{
		size_t i;
		for (i = 0; i < bufsize; ++i) {
			while (!GDBSerial_IO_IsTransmitEmpty())
				task_tryyield_or_pause();
			outb(SERIAL_IOADDR_THR(GDBSerial_IO_PortBase), ((byte_t *)buf)[i]);
		}
	}
}



INTERN void FCALL
GDBSerial_Initialize(char *args) {
	if (sscanf(args, "%I16U:%I8U",
	           &GDBSerial_IO_PortBase,
	           &GDBSerial_IO_IsrVector) != 2) {
		printk(KERN_ERR "[gdb] Invalid arguments for serial transport method: %q", args);
		THROW(E_INVALID_ARGUMENT);
	}
	printk(KERN_INFO "[gdb] Enable serial transport on port %#I16x (isr#%#I8x)\n",
	       GDBSerial_IO_PortBase, GDBSerial_IO_IsrVector);
	GDBRemote_RegisterInterruptHandler((isr_vector_t)GDBSerial_IO_IsrVector,
	                                   &GDBSerial_InterruptHandler);
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
		/* Enable interrupts before we read data, since once we do that read,
		 * any additional data which may arrive from then on can trigger an IRQ! */
		outb(SERIAL_IOADDR_IER(GDBSerial_IO_PortBase), SERIAL_EIR_RDA);
		if (avail & SERIAL_LSR_DA) {
			u8 data = inb(SERIAL_IOADDR_RBR(GDBSerial_IO_PortBase));
			printk(KERN_INFO "[gdb] Processing initial byte %#.2I8x\n", data);
			GDBRemote_PutByteFromHere(data);
		}
	}
}

INTERN void FCALL GDBSerial_Finalize(void) {
	GDBRemote_UnregisterInterruptHandler((isr_vector_t)GDBSerial_IO_IsrVector);
}



DECL_END

#endif /* !GUARD_MODGDB_REMOTE_SERIAL_C */
