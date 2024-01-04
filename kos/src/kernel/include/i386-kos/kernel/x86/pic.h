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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PIC_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PIC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hw/ic/pic.h>
#include <sys/io.h>

#include "idt.h"

DECL_BEGIN

/* Interrupt numbers. */
#define X86_INTERRUPT_PIC1_BASE 0xf0
#define X86_INTERRUPT_PIC2_BASE 0xf8

/* Return the  IRQ numbers  of hardware  interrupt
 * lines wired either to the master, or slave PIC.
 * @param: i :  The line number (0..7)
 * @return: * : The IRQ number. */
#define X86_INTNO_PIC1(i) (X86_INTERRUPT_PIC1_BASE + (i))
#define X86_INTNO_PIC2(i) (X86_INTERRUPT_PIC2_BASE + (i))

#ifdef __CC__
#define X86_PIC1_IRR() (outb(X86_PIC1_CMD, X86_PIC_READ_IRR), inb(X86_PIC2_CMD))
#define X86_PIC2_IRR() (outb(X86_PIC2_CMD, X86_PIC_READ_IRR), inb(X86_PIC2_CMD))
#define X86_PIC1_ISR() (outb(X86_PIC1_CMD, X86_PIC_READ_ISR), inb(X86_PIC2_CMD))
#define X86_PIC2_ISR() (outb(X86_PIC2_CMD, X86_PIC_READ_ISR), inb(X86_PIC2_CMD))

/* Signal EOI (End of interrupt) to the first (master), or second (slave) PIC. */
#define X86_PIC_EOI(intno)                 \
	((intno) >= X86_INTERRUPT_PIC2_BASE    \
	 ? outb(X86_PIC2_CMD, X86_PIC_CMD_EOI) \
	 : (void)0,                            \
	 outb(X86_PIC1_CMD, X86_PIC_CMD_EOI))
#define X86_PIC1_EOI() (outb(X86_PIC1_CMD, X86_PIC_CMD_EOI))
#define X86_PIC2_EOI() (outb(X86_PIC2_CMD, X86_PIC_CMD_EOI), outb(X86_PIC1_CMD, X86_PIC_CMD_EOI))


struct x86_spurious_interrupts {
	u32 sp_pic1; /* Amount of spurious interrupts that occurred on PIC #1. */
	u32 sp_pic2; /* Amount of spurious interrupts that occurred on PIC #2. */
	u32 sp_apic; /* Amount of spurious interrupts that occurred through the APIC. */
};

/* Tracking information about spurious interrupts.
 * >> Useful for detecting faulty software  that sends EOI commands at  the
 *    wrong time, or for tracking problems in hardware, such as line noise. */
DATDEF ATTR_PERCPU struct x86_spurious_interrupts thiscpu_x86_spurious_interrupts;


/* Get/Set   the  mask  of  disabled  interrupt  lines.
 * >> `INTNO_PIC1_STMASK()' disables irq_t: 0x20...0x27
 * >> `INTNO_PIC2_STMASK()' disables irq_t: 0x28...0x2f */
#define X86_PIC1_GTMASK()  inb_p(X86_PIC1_DATA)
#define X86_PIC1_STMASK(m) outb_p(X86_PIC1_DATA, m)
#define X86_PIC2_GTMASK()  inb_p(X86_PIC2_DATA)
#define X86_PIC2_STMASK(m) outb_p(X86_PIC2_DATA, m)
#endif /* __CC__ */

/* Standard ISA IRQ numbers.
 * >> This is the default wireing of hardware interrupts. */
#define X86_INTNO_PIC1_PIT   X86_INTNO_PIC1(0) /* Programmable Interrupt Timer Interrupt. */
#define X86_INTNO_PIC1_KBD   X86_INTNO_PIC1(1) /* Keyboard Interrupt. */
#define X86_INTNO_PIC1_CAS   X86_INTNO_PIC1(2) /* Cascade (used internally by the two PICs. never raised). */
#define X86_INTNO_PIC1_COM2  X86_INTNO_PIC1(3) /* COM2 (if enabled). */
#define X86_INTNO_PIC1_COM1  X86_INTNO_PIC1(4) /* COM1 (if enabled). */
#define X86_INTNO_PIC1_LPT2  X86_INTNO_PIC1(5) /* LPT2 (if enabled). */
#define X86_INTNO_PIC1_FLOP  X86_INTNO_PIC1(6) /* Floppy Disk. */
#define X86_INTNO_PIC1_LPT1  X86_INTNO_PIC1(7) /* LPT1 / Unreliable "spurious" interrupt (usually). */
#define X86_INTNO_PIC2_CMOS  X86_INTNO_PIC2(0) /* CMOS real-time clock (if enabled). */
#define X86_INTNO_PIC2_FREE1 X86_INTNO_PIC2(1) /* Free for peripherals / legacy SCSI / NIC. */
#define X86_INTNO_PIC2_FREE2 X86_INTNO_PIC2(2) /* Free for peripherals / SCSI / NIC. */
#define X86_INTNO_PIC2_FREE3 X86_INTNO_PIC2(3) /* Free for peripherals / SCSI / NIC. */
#define X86_INTNO_PIC2_PS2M  X86_INTNO_PIC2(4) /* PS2 Mouse. */
#define X86_INTNO_PIC2_FPU   X86_INTNO_PIC2(5) /* FPU / Coprocessor / Inter-processor. */
#define X86_INTNO_PIC2_ATA1  X86_INTNO_PIC2(6) /* Primary ATA Hard Disk. */
#define X86_INTNO_PIC2_ATA2  X86_INTNO_PIC2(7) /* Secondary ATA Hard Disk. */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PIC_H */
