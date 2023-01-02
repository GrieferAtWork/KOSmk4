/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#define __LINKER__ 1
#endif /* __INTELLISENSE__ */

#include <hybrid/compiler.h>

#include <kernel/x86/idt-names.h>
#include <kernel/x86/idt.h> /* IDT_CONFIG_ISTRAP() */

#include <hybrid/host.h>

#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/segment.h>


#ifndef PREFIX
#define IS_DEFAULT_PREFIX 1
#define PREFIX x86_
#endif /* !PREFIX */

#define SYMBOL(prefix2, id) PP_CAT3(PREFIX, prefix2, IDT_X86_##id)
#ifdef IS_DEFAULT_PREFIX
#define PROVIDE_IDT_ADDRESS(id) /* nothing */
#else /* IS_DEFAULT_PREFIX */
#define PROVIDE_IDT_ADDRESS(id) \
	PROVIDE_HIDDEN(SYMBOL(idt_, id) = PP_CAT3(x86_, idt_, IDT_X86_##id));
#ifdef __x86_64__
#define PROVIDE_IST(id) \
	PROVIDE_HIDDEN(SYMBOL(idtist_, id) = PP_CAT3(x86_, idtist_, IDT_X86_##id));
#endif /* __x86_64__ */
#define PROVIDE_DPL(id) \
	PROVIDE_HIDDEN(SYMBOL(idtdpl_, id) = PP_CAT3(x86_, idtdpl_, IDT_X86_##id));
#endif /* !IS_DEFAULT_PREFIX */


#ifdef __x86_64__
#define DEFINE(id, segment_name, args)                                                      \
	PROVIDE_HIDDEN(PP_CAT4(__, PREFIX, idtlo_, id) = SEGMENT_##segment_name##_INIT_U args); \
	PROVIDE_HIDDEN(PP_CAT4(__, PREFIX, idthi_, id) = SEGMENT_##segment_name##_HI_INIT_U args);
#define DEFINE_INTRGATE_EX(id, offset, TYPE, DPL, IST) \
	DEFINE(id, INTRGATE, (offset, SEGMENT_KERNEL_CODE, IST, TYPE, DPL, 1))
#ifndef PROVIDE_IST
#define PROVIDE_IST(id) PROVIDE_HIDDEN(SYMBOL(idtist_, id) = 0);
#endif /* !PROVIDE_IST */
#else /* __x86_64__ */
#define DEFINE(id, segment_name, args)                                                       \
	PROVIDE_HIDDEN(PP_CAT4(__, PREFIX, idtlo_, id) = SEGMENT_##segment_name##_INIT_UL args); \
	PROVIDE_HIDDEN(PP_CAT4(__, PREFIX, idthi_, id) = SEGMENT_##segment_name##_INIT_UH args);
#define DEFINE_INTRGATE_EX(id, offset, TYPE, DPL, IST) \
	DEFINE(id, INTRGATE, (offset, SEGMENT_KERNEL_CODE, TYPE, DPL, 1))
#ifndef PROVIDE_IST
#define PROVIDE_IST(id) /* nothing */
#endif /* !PROVIDE_IST */
#endif /* !__x86_64__ */

#ifndef PROVIDE_DPL
#define PROVIDE_DPL(id) PROVIDE_HIDDEN(SYMBOL(idtdpl_, id) = 0);
#endif /* !PROVIDE_DPL */

#define DEFINE_INTRGATE(id, TYPE) \
	PROVIDE_DPL(id)               \
	PROVIDE_IST(id)               \
	PROVIDE_IDT_ADDRESS(id)       \
	DEFINE_INTRGATE_EX(id, SYMBOL(idt_, id), TYPE, SYMBOL(idtdpl_, id), SYMBOL(idtist_, id))

#define INTR(id) DEFINE_INTRGATE(id, SEGMENT_DESCRIPTOR_TYPE_INTRGATE)
#define TRAP(id) DEFINE_INTRGATE(id, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE)
#define GATE(id)                                           \
	DEFINE_INTRGATE(id, IDT_CONFIG_ISTRAP(0x##id)          \
	                    ? SEGMENT_DESCRIPTOR_TYPE_TRAPGATE \
	                    : SEGMENT_DESCRIPTOR_TYPE_INTRGATE)

#ifdef __x86_64__
/* Can't safely make  use of  traps on x86_64,  since on  entry to  any
 * kind of interrupt, we need to check if the interrupt originated from
 * user-space,  and if it  did, need to  invoke `swapgs', which would't
 * work properly if another interrupt could happen before then,  making
 * us think that `swapgs' was  already invoked when it actually  wasn't
 *
 * Thus, the only safe way to do a TRAP interrupt becomes:
 * >> entry:
 * >>     testb  $3, OFFSET_IRREGS_CS(%rsp)
 * >>     jz     1f
 * >>     swapgs
 * >> 1:  testb  $EFLAGS_IF, OFFSET_IRREGS_EFLAGS(%rsp)
 * >>     jz     1f
 * >>     sti
 * >> 1:
 * >>
 * >>     ...    # Actual interrupt handler
 * >>
 * >>
 * >>     testb  $3, OFFSET_IRREGS_CS(%rsp)
 * >>     jz     1f
 * >>     swapgs
 * >> 1:  iret
 */
#undef TRAP
#undef GATE
#define TRAP(id) DEFINE_INTRGATE(id, SEGMENT_DESCRIPTOR_TYPE_INTRGATE)
#define GATE(id) DEFINE_INTRGATE(id, SEGMENT_DESCRIPTOR_TYPE_INTRGATE)
#endif /* __x86_64__ */


/* TRAP: Leave EFLAGS.IF unchanged
 * INTR: Clear EFLAGS.IF to disable preemption.
 * GATE: Either TRAP() or INTR(), based on `IDT_CONFIG_ISTRAP()' */

GATE(00) /* #DE -- Divide by zero */
GATE(01) /* #DB -- Debug */
GATE(02) /* NMI -- Non-maskable Interrupt */
GATE(03) /* #BP -- Breakpoint */
GATE(04) /* #OF -- Overflow */
GATE(05) /* #BR -- Bound Range */
GATE(06) /* #UD -- Illegal Instruction */
GATE(07) /* #NM -- Device not available. */

#ifdef __x86_64__
GATE(08) /* #DF -- Double Fault. */
#else /* __x86_64__ */
/* Special handling for #DF (implemented using a task gate on i386) */
PROVIDE_DPL(08)
DEFINE(08, TASKGATE, (SEGMENT_CPU_TSS_DF, SYMBOL(idtdpl_, 08), 1))
#endif /* !__x86_64__ */

GATE(09)
GATE(0a) /* #TS -- Invalid TSS. */
GATE(0b) /* #NP -- Segment not present. */
GATE(0c) /* #SS -- Stack segment fault. */
GATE(0d) /* #GP -- General Protection Fault. */
GATE(0e) /* #PF -- Page Fault. */
GATE(0f)
GATE(10)
GATE(11)
GATE(12)
GATE(13)
GATE(14)
GATE(15)
GATE(16)
GATE(17)
GATE(18)
GATE(19)
GATE(1a)
GATE(1b)
GATE(1c)
GATE(1d)
GATE(1e)
GATE(1f)

/* MS Service interrupts. */
GATE(20)
GATE(21)
GATE(22)
GATE(23)
GATE(24)
GATE(25)
GATE(26)
GATE(27)
GATE(28)
GATE(29) /* ms_fastfail */
GATE(2a)
GATE(2b)
GATE(2c)
GATE(2d)
GATE(2e)
GATE(2f)

/* Non-exception/service vectors.
 * All of these are configured as interrupts, with the
 * exception  of  80h  (which is  the  syscall vector) */
INTR(30)
INTR(31)
INTR(32)
INTR(33)
INTR(34)
INTR(35)
INTR(36)
INTR(37)
INTR(38)
INTR(39)
INTR(3a)
INTR(3b)
INTR(3c)
INTR(3d)
INTR(3e)
INTR(3f)
INTR(40)
INTR(41)
INTR(42)
INTR(43)
INTR(44)
INTR(45)
INTR(46)
INTR(47)
INTR(48)
INTR(49)
INTR(4a)
INTR(4b)
INTR(4c)
INTR(4d)
INTR(4e)
INTR(4f)
INTR(50)
INTR(51)
INTR(52)
INTR(53)
INTR(54)
INTR(55)
INTR(56)
INTR(57)
INTR(58)
INTR(59)
INTR(5a)
INTR(5b)
INTR(5c)
INTR(5d)
INTR(5e)
INTR(5f)
INTR(60)
INTR(61)
INTR(62)
INTR(63)
INTR(64)
INTR(65)
INTR(66)
INTR(67)
INTR(68)
INTR(69)
INTR(6a)
INTR(6b)
INTR(6c)
INTR(6d)
INTR(6e)
INTR(6f)
INTR(70)
INTR(71)
INTR(72)
INTR(73)
INTR(74)
INTR(75)
INTR(76)
INTR(77)
INTR(78)
INTR(79)
INTR(7a)
INTR(7b)
INTR(7c)
INTR(7d)
INTR(7e)
INTR(7f)
TRAP(80) /* Keep interrupts on for system calls. */
INTR(81)
INTR(82)
INTR(83)
INTR(84)
INTR(85)
INTR(86)
INTR(87)
INTR(88)
INTR(89)
INTR(8a)
INTR(8b)
INTR(8c)
INTR(8d)
INTR(8e)
INTR(8f)
INTR(90)
INTR(91)
INTR(92)
INTR(93)
INTR(94)
INTR(95)
INTR(96)
INTR(97)
INTR(98)
INTR(99)
INTR(9a)
INTR(9b)
INTR(9c)
INTR(9d)
INTR(9e)
INTR(9f)
INTR(a0)
INTR(a1)
INTR(a2)
INTR(a3)
INTR(a4)
INTR(a5)
INTR(a6)
INTR(a7)
INTR(a8)
INTR(a9)
INTR(aa)
INTR(ab)
INTR(ac)
INTR(ad)
INTR(ae)
INTR(af)
INTR(b0)
INTR(b1)
INTR(b2)
INTR(b3)
INTR(b4)
INTR(b5)
INTR(b6)
INTR(b7)
INTR(b8)
INTR(b9)
INTR(ba)
INTR(bb)
INTR(bc)
INTR(bd)
INTR(be)
INTR(bf)
INTR(c0)
INTR(c1)
INTR(c2)
INTR(c3)
INTR(c4)
INTR(c5)
INTR(c6)
INTR(c7)
INTR(c8)
INTR(c9)
INTR(ca)
INTR(cb)
INTR(cc)
INTR(cd)
INTR(ce)
INTR(cf)
INTR(d0)
INTR(d1)
INTR(d2)
INTR(d3)
INTR(d4)
INTR(d5)
INTR(d6)
INTR(d7)
INTR(d8)
INTR(d9)
INTR(da)
INTR(db)
INTR(dc)
INTR(dd)
INTR(de)
INTR(df)
INTR(e0)
INTR(e1)
INTR(e2)
INTR(e3)
INTR(e4)
INTR(e5)
INTR(e6)
INTR(e7)
INTR(e8)
INTR(e9)
INTR(ea)
INTR(eb)
INTR(ec)
INTR(ed)
INTR(ee)
INTR(ef)
INTR(f0)
INTR(f1)
INTR(f2)
INTR(f3)
INTR(f4)
INTR(f5)
INTR(f6)
INTR(f7)
INTR(f8)
INTR(f9)
INTR(fa)
INTR(fb)
INTR(fc)
INTR(fd)
INTR(fe)
INTR(ff)

#undef PREFIX
#undef SYMBOL
#undef TRAP
#undef INTR
#undef GATE
#undef PROVIDE_DPL
#undef PROVIDE_IST
#undef PROVIDE_IDT_ADDRESS
#undef DEFINE_INTRGATE
#undef DEFINE_INTRGATE_EX
#undef IS_DEFAULT_PREFIX
#undef DEFINE
