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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_IDT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_IDT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kos/kernel/segment.h>

DECL_BEGIN

#define X86_IDTFLAG_PRESENT                 0x80 /* Set to 0 for unused interrupts. */
/* Descriptor Privilege LevelGate call protection.
 * Specifies which privilege Level the calling Descriptor minimum should have.
 * So hardware and CPU interrupts can be protected from being called out of userspace. */
#define X86_IDTFLAG_DPL(n)          (((n)&3)<<5) /* Mask: 0x60 */
#define X86_IDTFLAG_DPL_MASK                0x60
#define X86_IDTFLAG_STORAGE_SEGMENT         0x10 /* Set to 0 for interrupt gates. */
#define X86_IDTTYPE_MASK                    0x0f
#define X86_IDTTYPE_80386_32_TASK_GATE      0x05
#define X86_IDTTYPE_80286_16_INTERRUPT_GATE 0x06
#define X86_IDTTYPE_80286_16_TRAP_GATE      0x07
#define X86_IDTTYPE_80386_32_INTERRUPT_GATE 0x0e
#define X86_IDTTYPE_80386_32_TRAP_GATE      0x0f

/* Different TRAP vs. Interrupt gate:
 *   - Upon entry into an interrupt gate, #IF is disabled
 *   - Upon entry to a trap gate, #IF is left unchanged.
 * NOTE: The default X86-interrupt handling code used by
 *       KOS assumes that Interrupt gates are being used,
 *       as it modifies part of the start prior to allocating
 *       it, meaning that it assumes not to be interrupted
 *       and have some other piece of code tinker with
 *       unallocated stack memory. */


/* Return the IRQ numbers of hardware interrupt
 * lines wired either to the master, or slave PIC.
 * @param: i :  The line number (0..7)
 * @return: * : The IRQ number. */
#define X86_INTNO_PIC1(i) (X86_INTERRUPT_PIC1_BASE+(i))
#define X86_INTNO_PIC2(i) (X86_INTERRUPT_PIC2_BASE+(i))


/* Interrupt numbers. */
#define X86_INTERRUPT_SYSCALL       0x80 /* System call interrupt. */
#define X86_INTERRUPT_APIC_IPI      0xee
#define X86_INTERRUPT_APIC_SPURIOUS 0xef
#define X86_INTERRUPT_PIC1_BASE     0xf0
#define X86_INTERRUPT_PIC2_BASE     0xf8

/* NOTE: These names must match the interrupt vectors above! */
#define X86_IRQ_APICIPI  irq_ee
#define X86_IRQ_APICSPUR irq_ef
#define X86_IRQ_ATA0     irq_fe
#define X86_IRQ_ATA1     irq_ff
#define X86_IRQ_KBD      irq_f1
#define X86_IRQ_PS2M     irq_fc



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_IDT_H */
