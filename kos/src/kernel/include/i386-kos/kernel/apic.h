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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_APIC_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_APIC_H 1

#include <kernel/compiler.h>
#include <bits/types.h>
#include <sys/mmio.h>

DECL_BEGIN

/* APIC (Advanced Programmable Interrupt Controller) API. */
/* LAPIC (Local Advanced Programmable Interrupt Controller) API. */


#define APIC_ID                                 0x0020     /* LAPIC ID of the calling CPU. */
#    define APIC_ID_FMASK                       0xff000000 /* Mask of the actual ID. */
#    define APIC_ID_FSHIFT                      24         /* Shift of the actual ID. */

#define APIC_EOI                                0x00b0     /* EndOfInterrupt */
#    define APIC_EOI_FSIGNAL                    0x00000000 /* Written to `APIC_EOI' to signal END-OF-INTERRUPT */

#define APIC_SPURIOUS                           0x00f0     /* Spurious interrupt vector & apic-enabled. */
#    define APIC_SPURIOUS_FVECTOR               0x000000ff /* Mask of the spurious interrupt vector. */
#    define APIC_SPURIOUS_FENABLED              0x00000100 /* When set, the APIC is enabled. */

/* Return the address of the i'th 32-bit word of a
 * bitset describing which interrupts are pending. */
#define APIC_ISR(i)                            (0x100 + (i) * 0x10)
#define APIC_ISR_COUNT                          8 /* 8 * 32 == 256 */
#define APIC_ISR_INDEX(intno)                  ((intno) / 32)
#define APIC_ISR_MASK(intno)                   (__CCAST(__UINT32_TYPE__)1 << ((intno) % 32))

#define APIC_LINT0                              0x0350     /* Local interrupt vector #0 */
#define APIC_LINT1                              0x0360     /* Local interrupt vector #1 */
#    define APIC_LINT_FVECTOR                   0x000000ff /* Mask of the interrupt vector number. */
#    define APIC_LINT_FDELIVERY                 0x00000700 /* Mask for the delivery type used. */
#        define APIC_LINT_DELIVERY_FNORMAL      0x00000000 /* Normal delivery. */
/*       define APIC_LINT_DELIVERY_F            0x00000000 ... 0x00000300  */
#        define APIC_LINT_DELIVERY_FNMI         0x00000400 /* Normal delivery. */
/*       define APIC_LINT_DELIVERY_F            0x00000500 ... 0x00000600  */
#        define APIC_LINT_DELIVERY_FEXTERNAL    0x00000700 /* External interrupt (???) */
#    define APIC_LINT_FPENDING                  0x00001000 /* The interrupt is pending delivery. */
#    define APIC_LINT_FPOLARITY                 0x00002000 /* The polarity bit. */
#        define APIC_LINT_POLARITY_FHIGH        0x00000000 /* High polarity. */
#        define APIC_LINT_POLARITY_FLOW         0x00002000 /* Low polarity. */
#    define APIC_LINT_FLEVELACK                 0x00004000 /* Level-triggered interrupt has been acknowledged. */
#    define APIC_LINT_FTRIGGER                  0x00008000 /* The triggering mode. */
#        define APIC_LINT_TRIGGER_EDGE          0x00000000 /* Edge-triggered. */
#        define APIC_LINT_TRIGGER_LEVEL         0x00008000 /* Level-triggered. */
#    define APIC_LINT_FDISABLED                 0x00010000 /* The interrupt is disabled. */

#define APIC_TIMER                              0x0320     /* Interrupt vector fired by the LAPIC timer. */
#    define APIC_TIMER_FVECTOR                  0x000000ff /* Mask for the interrupt vector number fired by the timer. */
#    define APIC_TIMER_FPENDING                 0x00001000 /* The timer interrupt is pending delivery. */
#    define APIC_TIMER_FDISABLED                0x00010000 /* The timer interrupt is disabled. */
#    define APIC_TIMER_FMODE                    0x00020000 /* Mask for the timer operations mode. */
#        define APIC_TIMER_MODE_FONESHOT        0x00000000 /* The timer will only fire once. */
#        define APIC_TIMER_MODE_FPERIODIC       0x00020000 /* The timer will fire periodically. */
#    define APIC_TIMER_FSOURCE                  0x000c0000 /* Timer source. */
#        define APIC_TIMER_SOURCE_FCLKIN        0x00000000 /* Use CLKIN as input. */
#        define APIC_TIMER_SOURCE_FTMBASE       0x00040000 /* Use TMBASE as input. */
#        define APIC_TIMER_SOURCE_FDIV          0x00080000 /* Use the output of the divider as input. */

#define APIC_ICR0                               0x0300     /* Common options to send to `APIC_ICR1' */
#    define APIC_ICR0_FVECTOR                   0x000000ff /* Interrupt that should be triggered. */
#    define APIC_ICR0_FPAGENO                   0x000000ff /* Page number to execute (for `APIC_ICR0_TYPE_FSIPI'). */
#    define APIC_ICR0_FTYPE                     0x00000700 /* The type of interrupt to trigger. */
#        define APIC_ICR0_TYPE_FNORMAL          0x00000000 /* Trigger a normal interrupt. */
#        define APIC_ICR0_TYPE_FLOWPRIO         0x00000100 /* Trigger a low-priority interrupt. */
#        define APIC_ICR0_TYPE_FSMI             0x00000200 /* Trigger a system-management interrupt. */
#        define APIC_ICR0_TYPE_FNMI             0x00000400 /* Trigger a non-maskable interrupt. */
#        define APIC_ICR0_TYPE_FINIT            0x00000500 /* INIT or INIT-level de-assert. */
#        define APIC_ICR0_TYPE_FSIPI            0x00000600 /* Startup Inter-Processor Interrupt. */
#    define APIC_ICR0_FDEST                     0x00000800 /* The kind of destination to which to send the interrupt. */
#        define APIC_ICR0_DEST_PHYSICAL         0x00000000 /* Physical destination. */
#        define APIC_ICR0_DEST_LOGICAL          0x00000800 /* Logical destination. */
#    define APIC_ICR0_FPENDING                  0x00001000 /* The interrupt is pending delivery. */
#    define APIC_ICR0_FASSERT                   0x00004000 /* Assert the interrupt (set for all, except for INIT-de-assert) */
#    define APIC_ICR0_FLEVELTRIG                0x00008000 /* ??? Set for INIT-de-assert */
#    define APIC_ICR0_FTARGET                   0x000c0000 /* Mask for the target of the interrupt. */
#        define APIC_ICR0_TARGET_FICR1          0x00000000 /* Send to the CPU id stored in `APIC_ICR1'. */
#        define APIC_ICR0_TARGET_FSELF          0x00040000 /* Send to the calling CPU. */
#        define APIC_ICR0_TARGET_FALL           0x00080000 /* Send to all CPUs. */
#        define APIC_ICR0_TARGET_FOTHERS        0x000c0000 /* Send to all but the calling CPU. */

#define APIC_ICR1                               0x0310     /* ID of the target APIC. */
#    define APIC_ICR1_FDEST                     0xff000000 /* Mask of the target APIC ID. */
#    define APIC_ICR1_SDEST                     24         /* Shift of the target APIC ID. */
#    define APIC_ICR1_GTDEST(x)               ((x) >> APIC_ICR1_SDEST)
#    define APIC_ICR1_MKDEST(lapic_id)        ((lapic_id) << APIC_ICR1_SDEST)

#define APIC_TIMER_DIVIDE                       0x03e0     /* Timer divide register. */
#    define APIC_TIMER_DIVIDE_FMASK             0x0000000b /* Mask for the divide mode. */
#    define APIC_TIMER_DIVIDE_F1                0x0000000b /* Divide by 1 */
#    define APIC_TIMER_DIVIDE_F2                0x00000000 /* Divide by 2 */
#    define APIC_TIMER_DIVIDE_F4                0x00000001 /* Divide by 4 */
#    define APIC_TIMER_DIVIDE_F8                0x00000002 /* Divide by 8 */
#    define APIC_TIMER_DIVIDE_F16               0x00000003 /* Divide by 16 */
#    define APIC_TIMER_DIVIDE_F32               0x00000008 /* Divide by 32 */
#    define APIC_TIMER_DIVIDE_F64               0x00000009 /* Divide by 64 */
#    define APIC_TIMER_DIVIDE_F128              0x0000000a /* Divide by 128 */

#define APIC_TIMER_INITIAL                      0x0380     /* Initial timer value. */

#define APIC_TIMER_CURRENT                      0x0390     /* Current timer value. */

#define APIC_SIZE                               0x1500


#ifdef __CC__
/* [const] Virtual base addresses of the local (per-cpu) APIC.
 * HINT: APIC stands for Advanced Programmable Interrupt Controller. */
DATDEF VIRT volatile __byte_t *const x86_lapicbase;
#define X86_HAVE_LAPIC             (x86_lapicbase != __NULLPTR)
#define lapic_read(offset)         readl(x86_lapicbase + (offset))
#define lapic_write(offset, value) writel(x86_lapicbase + (offset), value)

/* [valid_if(X86_HAVE_LAPIC)] The LAPIC ID of the controller associated with the CPU. */
DATDEF ATTR_PERCPU __u8 const thiscpu_x86_lapicid;

/* [valid_if(X86_HAVE_LAPIC)] The LAPIC version of the controller associated with the CPU.
 *                            This is one of `APICVER_*' from `<sched/smp.h>' */
DATDEF ATTR_PERCPU __u8 const thiscpu_x86_lapicversion;

#endif /* __CC__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_APIC_H */
