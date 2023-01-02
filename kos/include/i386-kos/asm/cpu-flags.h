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
#ifndef _I386_KOS_ASM_CPU_FLAGS_H
#define _I386_KOS_ASM_CPU_FLAGS_H 1

#include <hybrid/typecore.h>

#define EFLAGS_CF          __UINT32_C(0x00000001) /* [bit(0)] Carry Flag Status. (signed arithmetic) */
#define EFLAGS_PF          __UINT32_C(0x00000004) /* [bit(2)] Parity Flag Status. */
#define EFLAGS_AF          __UINT32_C(0x00000010) /* [bit(4)] Auxiliary Carry Flag Status. */
#define EFLAGS_ZF          __UINT32_C(0x00000040) /* [bit(6)] Zero Flag Status. */
#define EFLAGS_SF          __UINT32_C(0x00000080) /* [bit(7)] Sign Flag Status. */
#define EFLAGS_TF          __UINT32_C(0x00000100) /* [bit(8)] Trap Flag (System). (generate an `int1' after executing a single instruction) */
#define EFLAGS_IF          __UINT32_C(0x00000200) /* [bit(9)] Interrupt Enable Flag (System). */
#define EFLAGS_DF          __UINT32_C(0x00000400) /* [bit(10)] Direction Flag (Control). */
#define EFLAGS_OF          __UINT32_C(0x00000800) /* [bit(11)] Overflow Flag Status. (unsigned arithmetic) */
#define EFLAGS_IOPL(n)     (((n) & 3) << 12)      /* [bit(12,13)] I/O Privilege Level (System). */
#define EFLAGS_IOPLMASK    __UINT32_C(0x00003000) /* [bit(12,13)] I/O Privilege Level (System). */
#define EFLAGS_NT          __UINT32_C(0x00004000) /* [bit(14)] Nested Task Flag (System). */
#define EFLAGS_RF          __UINT32_C(0x00010000) /* [bit(16)] Resume Flag (System).
                                                   * Suppress %drN-style instruction breakpoints for 1 instruction.
                                                   * Cleared  before execution of every instruction (after checking
                                                   * for %drN-style instruction breakpoints))
                                                   * Used to prevent hw-breakpoints from triggering multiple times
                                                   * when the attached instruction causes a #PF (or similar),  and
                                                   * ends up being executed more than once by the hardware. */
#define EFLAGS_VM          __UINT32_C(0x00020000) /* [bit(17)] Virtual 8086 Mode (System). */
#define EFLAGS_AC          __UINT32_C(0x00040000) /* [bit(18)] Alignment Check (System). */
#define EFLAGS_VIF         __UINT32_C(0x00080000) /* [bit(19)] Virtual Interrupt Flag (System). */
#define EFLAGS_VIP         __UINT32_C(0x00100000) /* [bit(20)] Virtual Interrupt Pending (System). */
#define EFLAGS_ID          __UINT32_C(0x00200000) /* [bit(21)] ID Flag (System). */
#define EFLAGS_GETIOPL(flags) (((flags) >> 12) & 3)

/* Mask of bits that user-space may assume to always be modifiable. There are
 * a  couple of bits in here that I wish weren't available to ring#3, however
 * ring#3  already has implicit access to them  since these are the bits that
 * `popf[l|q]' allows to be modified, so  there'd be no point in  restricting
 * this set in any form.
 *
 * The only thing that I don't understand about this is `EFLAGS.AC', because
 * there are 2 dedicated instructions `stac' and `clac' that can be used  to
 * set/clear that bit. However attempting to  do so (normally) causes a  #GP
 * if done so from ring#3  (and there is no way  to disable this other  than
 * emulating these instructions for ring#3 from kernel-space, as done by the
 * KOS kernel). So it doesn't actually make sense to lock those instructions
 * as being privileged when in fact everything they might be useful for  can
 * already  be done via  the `popf' instruction  (which isn't privileged for
 * `EFLAGS.AC' and cannot be made to be privileged, either...) */
#define EFLAGS_UMASK                                                         \
	(EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF | EFLAGS_TF | \
	 EFLAGS_DF | EFLAGS_OF | EFLAGS_NT | EFLAGS_AC | EFLAGS_ID)

/* %cr0 */
#define CR0_PE             __UINT32_C(0x00000001) /* [bit(0)] Protected Mode Enable. */
#define CR0_MP             __UINT32_C(0x00000002) /* [bit(1)] Monitor CO-Processor. */
#define CR0_EM             __UINT32_C(0x00000004) /* [bit(2)] Emulation. */
#define CR0_TS             __UINT32_C(0x00000008) /* [bit(3)] Task Switched. */
#define CR0_ET             __UINT32_C(0x00000010) /* [bit(4)] Extension Type. */
#define CR0_NE             __UINT32_C(0x00000020) /* [bit(5)] Numeric Error. */
#define CR0_WP             __UINT32_C(0x00010000) /* [bit(16)] Write Protect. */
#define CR0_AM             __UINT32_C(0x00040000) /* [bit(18)] Alignment Mask. */
#define CR0_NW             __UINT32_C(0x20000000) /* [bit(29)] Not-write Through. */
#define CR0_CD             __UINT32_C(0x40000000) /* [bit(30)] Cache Disable. */
#define CR0_PG             __UINT32_C(0x80000000) /* [bit(31)] Paging. */

/* %cr2 */
#define CR3_PWT            __UINT32_C(0x00000008) /* [bit(3)] Page-level Write-Through. */
#define CR3_PCD            __UINT32_C(0x00000010) /* [bit(4)] Page-level Cache Disable. */

/* %cr4 */
#define CR4_VME            __UINT32_C(0x00000001) /* [bit(0)] Virtual 8086 mode extensions. */
#define CR4_PVI            __UINT32_C(0x00000002) /* [bit(1)] Protected mode virtual interrupts. */
#define CR4_TSD            __UINT32_C(0x00000004) /* [bit(2)] Time stamp disable. */
#define CR4_DE             __UINT32_C(0x00000008) /* [bit(3)] Debugging extensions. */
#define CR4_PSE            __UINT32_C(0x00000010) /* [bit(4)] Page size extension. */
#define CR4_PAE            __UINT32_C(0x00000020) /* [bit(5)] Physical address extension. */
#define CR4_MCE            __UINT32_C(0x00000040) /* [bit(6)] Machine check exception. */
#define CR4_PGE            __UINT32_C(0x00000080) /* [bit(7)] Page global enable. */
#define CR4_PCE            __UINT32_C(0x00000100) /* [bit(8)] Performance Monitoring counter enable. */
#define CR4_OSFXSR         __UINT32_C(0x00000200) /* [bit(9)] OS support for FXSAVE and FXRSTOR Instructions. */
#define CR4_OSXMMEXCPT     __UINT32_C(0x00000400) /* [bit(10)] OS support for unmasked SIMD floating point Exceptions. */
#define CR4_UMIP           __UINT32_C(0x00000800) /* [bit(11)] Disable user-space access to `s(g|i)dt' (s.a. `CPUID_7C_UMIP'). */
#define CR4_VMXE           __UINT32_C(0x00002000) /* [bit(13)] Virtual Machine extensions enable. */
#define CR4_SMXE           __UINT32_C(0x00004000) /* [bit(14)] Safer mode extensions enable. */
#define CR4_FSGSBASE       __UINT32_C(0x00010000) /* [bit(16)] Enable (rd|wr)(fs|gs)base instructions. */
#define CR4_PCIDE          __UINT32_C(0x00020000) /* [bit(17)] Enables process-context identifiers. */
#define CR4_OSXSAVE        __UINT32_C(0x00040000) /* [bit(18)] XSAVE and Processor extended states enable. */
#define CR4_SMEP           __UINT32_C(0x00100000) /* [bit(20)] Supervisor Mode executions Protection enable. */
#define CR4_SMAP           __UINT32_C(0x00200000) /* [bit(21)] Supervisor Mode access Protection enable. */
#define CR4_PKE            __UINT32_C(0x00400000) /* [bit(22)] Protection-Key-Enable. */


/* NOTE: Within the int1 handler, B{0-3} may be set even if the associated breakpoint
 *       in %dr7 isn't enabled (enabling a breakpoint may only cause an exception  to
 *       be  generated when its condition is detected, but doesn't necessarily affect
 *       if and what bits get set within %dr6)
 * NOTE: Undefined bits must remain unchanged! */
#define DR6_B0             __UINT32_C(0x00000001) /* [bit(0)] Breakpoint condition 0 detected */
#define DR6_B1             __UINT32_C(0x00000002) /* [bit(1)] Breakpoint condition 1 detected */
#define DR6_B2             __UINT32_C(0x00000004) /* [bit(2)] Breakpoint condition 2 detected */
#define DR6_B3             __UINT32_C(0x00000008) /* [bit(3)] Breakpoint condition 3 detected */
#define DR6_BD             __UINT32_C(0x00002000) /* [bit(13)] Set in `int1' if `DR7_GD' was set and the calling instruction attempted to access %dr{0-7} */
#define DR6_BS             __UINT32_C(0x00004000) /* [bit(14)] The exception was triggered by single-step (s.a. `EFLAGS_TF') */
#define DR6_BT             __UINT32_C(0x00008000) /* [bit(15)] The exception was triggered by a task-switch (caused if `*(TSS + 100) & 0x1') */
#define DR6_RTM            __UINT32_C(0x00010000) /* [bit(16)] Always set, except for exceptions triggered within restricted transactional memory regions. */

#define DR7_BREAKPOINT_COUNT 4

/* NOTE: Undefined bits must remain unchanged! */
#define DR7_L0             __UINT32_C(0x00000001) /* [bit(0)] local DR0 breakpoint. */
#define DR7_G0             __UINT32_C(0x00000002) /* [bit(1)] global DR0 breakpoint. */
#define DR7_L1             __UINT32_C(0x00000004) /* [bit(2)] local DR1 breakpoint. */
#define DR7_G1             __UINT32_C(0x00000008) /* [bit(3)] global DR1 breakpoint. */
#define DR7_L2             __UINT32_C(0x00000010) /* [bit(4)] local DR2 breakpoint. */
#define DR7_G2             __UINT32_C(0x00000020) /* [bit(5)] global DR2 breakpoint. */
#define DR7_L3             __UINT32_C(0x00000040) /* [bit(6)] local DR3 breakpoint. */
#define DR7_G3             __UINT32_C(0x00000080) /* [bit(7)] global DR3 breakpoint. */
#define DR7_LE             __UINT32_C(0x00000100) /* [bit(8)] Local exact breakpoint enable. */
#define DR7_GE             __UINT32_C(0x00000200) /* [bit(9)] Global exact breakpoint enable. */
#define DR7_RTM            __UINT32_C(0x00000800) /* [bit(11)] Restricted transactional memory (Requires `IA32_DEBUGCTL.RTM'). */
#define DR7_GD             __UINT32_C(0x00002000) /* [bit(13)] Enable debug register protection.
                                                   * mov  instructions attempting to access debug registers
                                                   * will cause a #DB exception to be triggered on said mov */
#define DR7_LN(n)          (__UINT32_C(0x1) << ((n)*2))
#define DR7_GN(n)          (__UINT32_C(0x2) << ((n)*2))
#define DR7_C0             __UINT32_C(0x00030000) /* [bit(16..17)] conditions for DR0. */
#define DR7_S0             __UINT32_C(0x000c0000) /* [bit(18..19)] size of DR0 breakpoint. */
#define DR7_C1             __UINT32_C(0x00300000) /* [bit(20..21)] conditions for DR1. */
#define DR7_S1             __UINT32_C(0x00c00000) /* [bit(22..23)] size of DR1 breakpoint. */
#define DR7_C2             __UINT32_C(0x03000000) /* [bit(24..25)] conditions for DR2. */
#define DR7_S2             __UINT32_C(0x0c000000) /* [bit(26..27)] size of DR2 breakpoint. */
#define DR7_C3             __UINT32_C(0x30000000) /* [bit(28..29)] conditions for DR3. */
#define DR7_S3             __UINT32_C(0xc0000000) /* [bit(30..31)] size of DR3 breakpoint . */
#define DR7_CN(n)          (__UINT32_C(0x3) << DR7_CN_SHIFT(n))
#define DR7_SN(n)          (__UINT32_C(0x3) << DR7_SN_SHIFT(n))
#define DR7_C0_SHIFT       16
#define DR7_S0_SHIFT       18
#define DR7_C1_SHIFT       20
#define DR7_S1_SHIFT       22
#define DR7_C2_SHIFT       24
#define DR7_S2_SHIFT       26
#define DR7_C3_SHIFT       28
#define DR7_S3_SHIFT       30
#define DR7_CN_SHIFT(n)    (16 + (4 * (n)))
#define DR7_SN_SHIFT(n)    (18 + (4 * (n)))
#define DR_S1              __UINT32_C(0x0) /* Break within a 1-byte range */
#define DR_S2              __UINT32_C(0x1) /* Break within a 2-byte range */
#define DR_S4              __UINT32_C(0x3) /* Break within a 4-byte range */
#define DR_S8              __UINT32_C(0x2) /* Break within a 8-byte range */
#define DR_CEXEC           __UINT32_C(0x0) /* Break on execute */
#define DR_CWRITE          __UINT32_C(0x1) /* Break on write */
#define DR_CREADWRITE      __UINT32_C(0x3) /* Break on read/write */
#define DR_CIO             __UINT32_C(0x2) /* Break on io (usually unsupported, never supported on __x86_64__) */


/* From: Figure 8-6 --- IA-32 Intel Architecture Software Developer's Manual, Volume 1
 * NOTE: For use with `__fldcw()' */
/* Exception masks. */
#define FCW_IM   __UINT16_C(0x0001) /* [bit(0)] Invalid Operation */
#define FCW_DM   __UINT16_C(0x0002) /* [bit(1)] Denormal operand. */
#define FCW_ZM   __UINT16_C(0x0004) /* [bit(2)] Zero divide. */
#define FCW_OM   __UINT16_C(0x0008) /* [bit(3)] Overflow. */
#define FCW_UM   __UINT16_C(0x0010) /* [bit(4)] Underflow. */
#define FCW_PM   __UINT16_C(0x0020) /* [bit(5)] Precision. */
/* FPU Control. */
#define FCW_PC   __UINT16_C(0x0300) /* [bit(8 - 9)] Precision control. */
#   define FCW_PC_SINGLE  __UINT16_C(0x0000) /* Single Precision (24 bits) */
#   define FCW_PC_DOUBLE  __UINT16_C(0x0200) /* Double Precision (53 bits) */
#   define FCW_PC_EXTEND  __UINT16_C(0x0300) /* Double Extended Precision (64 bits) */
#define FCW_RC   __UINT16_C(0x0c00) /* [bit(10 - 11)] Rounding control. */
#   define FCW_RC_NEAREST __UINT16_C(0x0000) /* Result   is   closest  to   the  infinitely   precise  result.
                                              * If 2 values are equally close, the even one is used. (DEFAULT) */
#   define FCW_RC_DOWN    __UINT16_C(0x0400) /* Round towards -INF */
#   define FCW_RC_UP      __UINT16_C(0x0800) /* Round towards +INF */
#   define FCW_RC_TRUNC   __UINT16_C(0x0c00) /* Truncate non-representable bits. */
#define FCW_X    __UINT16_C(0x1000) /* [bit(12)] Infinity Control. */


/* FPU Status word bits. */
#define FSW_IE   __UINT16_C(0x0001) /* [bit(0)] Invalid Operation (Exception) */
#define FSW_DE   __UINT16_C(0x0002) /* [bit(1)] Denormalized Operand (Exception) */
#define FSW_ZE   __UINT16_C(0x0004) /* [bit(2)] Zero Divide (Exception) */
#define FSW_OE   __UINT16_C(0x0008) /* [bit(3)] Overflow (Exception) */
#define FSW_UE   __UINT16_C(0x0010) /* [bit(4)] Underflow (Exception) */
#define FSW_PE   __UINT16_C(0x0020) /* [bit(5)] Precision (Exception) */
#define FSW_SF   __UINT16_C(0x0040) /* [bit(6)] Stack Fault */
#define FSW_ES   __UINT16_C(0x0080) /* [bit(7)] Error Summary Status */
#define FSW_C0   __UINT16_C(0x0100) /* [bit(8)] Condition code */
#define FSW_C1   __UINT16_C(0x0200) /* [bit(9)] Condition code */
#define FSW_C2   __UINT16_C(0x0400) /* [bit(10)] Condition code */
#define FSW_C3   __UINT16_C(0x4000) /* [bit(14)] Condition code */
#define FSW_TOP  __UINT16_C(0x3800) /* [bit(11 - 13)] Top of stack pointer */
#define FSW_TOP_SHIFT 11 /* Shift for `FSW_TOP' */
#define FSW_B    __UINT16_C(0x8000) /* [bit(15)] FPU Busy */


/* Bit-pair values for `fs_ftw' (repeated 8 times with i=0:7) */
#define FTW_VALID(i) __UINT16_C(0x0)               /* Valid */
#define FTW_ZERO(i)  (__UINT16_C(0x1) << ((i)*2))  /* Zero */
#define FTW_SPEC(i)  (__UINT16_C(0x2) << ((i)*2))  /* Special (invalid (NaN, unsupported), infinity, or denormal) */
#define FTW_EMPTY(i) (__UINT16_C(0x3) << ((i)*2))  /* Empty */
#define FTW_MASK(i)  (__UINT16_C(0x3) << ((i)*2))  /* Mask */
#define FTW_ALLEMPTY __UINT16_C(0xffff) /* All empty */


/* MXCSR bits. (for use with `__stmxcsr()' / `__ldmxcsr()') */
#define MXCSR_IE  __UINT16_C(0x00000001) /* [bit(0)] Invalid Operation Flag (sticky, Exception) */
#define MXCSR_DE  __UINT16_C(0x00000002) /* [bit(1)] Denormal Flag (sticky, Exception) */
#define MXCSR_ZE  __UINT16_C(0x00000004) /* [bit(2)] Zero Divide Flag (sticky, Exception) */
#define MXCSR_OE  __UINT16_C(0x00000008) /* [bit(3)] Overflow Flag (sticky, Exception) */
#define MXCSR_UE  __UINT16_C(0x00000010) /* [bit(4)] Underflow Flag (sticky, Exception) */
#define MXCSR_PE  __UINT16_C(0x00000020) /* [bit(5)] Precision Flag (sticky, Exception) */
#define MXCSR_DAZ __UINT16_C(0x00000040) /* [bit(6)] Denormals Are Zeros */
#define MXCSR_IM  __UINT16_C(0x00000080) /* [bit(7)] Invalid Operation (Exception mask) */
#define MXCSR_DM  __UINT16_C(0x00000100) /* [bit(8)] Denormal operand (Exception mask) */
#define MXCSR_ZM  __UINT16_C(0x00000200) /* [bit(9)] Zero divide (Exception mask) */
#define MXCSR_OM  __UINT16_C(0x00000400) /* [bit(10)] Overflow (Exception mask) */
#define MXCSR_UM  __UINT16_C(0x00000800) /* [bit(11)] Underflow (Exception mask) */
#define MXCSR_PM  __UINT16_C(0x00001000) /* [bit(12)] Precision (Exception mask) */
#define MXCSR_RC  __UINT16_C(0x00006000) /* [bit(13 - 14)] Rounding control. */
#   define MXCSR_RC_NEAREST __UINT16_C(0x00000000) /* Result   is   closest  to   the  infinitely   precise  result.
                                                    * If 2 values are equally close, the even one is used. (DEFAULT) */
#   define MXCSR_RC_DOWN    __UINT16_C(0x00002000) /* Round towards -INF */
#   define MXCSR_RC_UP      __UINT16_C(0x00004000) /* Round towards +INF */
#   define MXCSR_RC_TRUNC   __UINT16_C(0x00006000) /* Truncate non-representable bits. */
#define MXCSR_FZ  __UINT16_C(0x00008000) /* [bit(15)] Flush-to-zero. */



#endif /* !_I386_KOS_ASM_CPU_FLAGS_H */
