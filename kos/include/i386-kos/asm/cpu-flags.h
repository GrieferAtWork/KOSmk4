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
#ifndef _I386_KOS_ASM_CPU_FLAGS_H
#define _I386_KOS_ASM_CPU_FLAGS_H 1

#define EFLAGS_CF          0x00000001 /* [bit(0)] Carry Flag Status. */
#define EFLAGS_PF          0x00000004 /* [bit(2)] Parity Flag Status. */
#define EFLAGS_AF          0x00000010 /* [bit(4)] Auxiliary Carry Flag Status. */
#define EFLAGS_ZF          0x00000040 /* [bit(6)] Zero Flag Status. */
#define EFLAGS_SF          0x00000080 /* [bit(7)] Sign Flag Status. */
#define EFLAGS_TF          0x00000100 /* [bit(8)] Trap Flag (System). (generate an `int1' after executing a single instruction) */
#define EFLAGS_IF          0x00000200 /* [bit(9)] Interrupt Enable Flag (System). */
#define EFLAGS_DF          0x00000400 /* [bit(10)] Direction Flag (Control). */
#define EFLAGS_OF          0x00000800 /* [bit(11)] Overflow Flag Status. */
#define EFLAGS_IOPL(n) (((n)&3) << 12)/* [bit(12,13)] I/O Privilege Level (System). */
#define EFLAGS_IOPLMASK    0x00003000 /* [bit(12,13)] I/O Privilege Level (System). */
#define EFLAGS_NT          0x00004000 /* [bit(14)] Nested Task Flag (System). */
#define EFLAGS_RF          0x00010000 /* [bit(16)] Resume Flag (System). */
#define EFLAGS_VM          0x00020000 /* [bit(17)] Virtual 8086 Mode (System). */
#define EFLAGS_AC          0x00040000 /* [bit(18)] Alignment Check (System). */
#define EFLAGS_VIF         0x00080000 /* [bit(19)] Virtual Interrupt Flag (System). */
#define EFLAGS_VIP         0x00100000 /* [bit(20)] Virtual Interrupt Pending (System). */
#define EFLAGS_ID          0x00200000 /* [bit(21)] ID Flag (System). */
#define EFLAGS_GTIOPL(flags) (((flags) >> 12) & 3)

/* Mask of bits that user-space may assume to always be modifiable
 * There are a couple of instructions in here that I wish weren't available
 * to ring#3, however ring#3 already has implicit access to them since these
 * are the bits that `popf[l|q]' allows to be modified.
 * The only thing that I don't understand about this is `EFLAGS.AC', because
 * there are 2 dedicated instructions `stac' and `clac' that can be used to
 * set/clear that bit. However attempting to do so (normally) causes a #GP
 * if done so from ring#3 (and there is no way to disable this other than
 * emulating these instructions for ring#3 from kernel-space, as done by
 * the KOS kernel). So it doesn't actually make sense to lock these instructions
 * as being privileged when in fact everything they might be useful for can
 * already be done via the `popf' instruction (which isn't privileged for
 * `EFLAGS.AC' and cannot be made to be privileged, either...) */
#define EFLAGS_UMASK                                                         \
	(EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF | EFLAGS_TF | \
	 EFLAGS_DF | EFLAGS_OF | EFLAGS_NT | EFLAGS_AC | EFLAGS_ID)

/* %cr0 */
#define CR0_PE             0x00000001 /* [bit(0)] Protected Mode Enable. */
#define CR0_MP             0x00000002 /* [bit(1)] Monitor CO-Processor. */
#define CR0_EM             0x00000004 /* [bit(2)] Emulation. */
#define CR0_TS             0x00000008 /* [bit(3)] Task Switched. */
#define CR0_ET             0x00000010 /* [bit(4)] Extension Type. */
#define CR0_NE             0x00000020 /* [bit(5)] Numeric Error. */
#define CR0_WP             0x00010000 /* [bit(16)] Write Protect. */
#define CR0_AM             0x00040000 /* [bit(18)] Alignment Mask. */
#define CR0_NW             0x20000000 /* [bit(29)] Not-write Through. */
#define CR0_CD             0x40000000 /* [bit(30)] Cache Disable. */
#define CR0_PG             0x80000000 /* [bit(31)] Paging. */

/* %cr2 */
#define CR3_PWT            0x00000008 /* [bit(3)] Page-level Write-Through. */
#define CR3_PCD            0x00000010 /* [bit(4)] Page-level Cache Disable. */

/* %cr4 */
#define CR4_VME            0x00000001 /* [bit(0)] Virtual 8086 mode extensions. */
#define CR4_PVI            0x00000002 /* [bit(1)] Protected mode virtual interrupts. */
#define CR4_TSD            0x00000004 /* [bit(2)] Time stamp disable. */
#define CR4_DE             0x00000008 /* [bit(3)] Debugging extensions. */
#define CR4_PSE            0x00000010 /* [bit(4)] Page size extension. */
#define CR4_PAE            0x00000020 /* [bit(5)] Physical address extension. */
#define CR4_MCE            0x00000040 /* [bit(6)] Machine check exception. */
#define CR4_PGE            0x00000080 /* [bit(7)] Page global enable. */
#define CR4_PCE            0x00000100 /* [bit(8)] Performance Monitoring counter enable. */
#define CR4_OSFXSR         0x00000200 /* [bit(9)] OS support for FXSAVE and FXRSTOR Instructions. */
#define CR4_OSXMMEXCPT     0x00000400 /* [bit(10)] OS support for unmasked SIMD floating point Exceptions. */
#define CR4_UMIP           0x00000800 /* [bit(11)] Disable user-space access to `s(g|i)dt' (s.a. `CPUID_7C_UMIP'). */
#define CR4_VMXE           0x00002000 /* [bit(13)] Virtual Machine extensions enable. */
#define CR4_SMXE           0x00004000 /* [bit(14)] Safer mode extensions enable. */
#define CR4_FSGSBASE       0x00010000 /* [bit(16)] Enable (rd|wr)(fs|gs)base instructions. */
#define CR4_PCIDE          0x00020000 /* [bit(17)] Enables process-context identifiers. */
#define CR4_OSXSAVE        0x00040000 /* [bit(18)] XSAVE and Processor extended states enable. */
#define CR4_SMEP           0x00100000 /* [bit(20)] Supervisor Mode executions Protection enable. */
#define CR4_SMAP           0x00200000 /* [bit(21)] Supervisor Mode access Protection enable. */
#define CR4_PKE            0x00400000 /* [bit(22)] Protection-Key-Enable. */


/* NOTE: Within the int1 handler, B{0-3} may be set even if the associated breakpoint
 *       in %dr7 isn't enabled (enabling a breakpoint may only cause an exception to
 *       be generated when its condition is detected, but doesn't necessarily affect
 *       if and what bits get set within %dr6)
 * NOTE: Undefined bits must remain unchanged! */
#define DR6_B0             0x00000001 /* [bit(0)] Breakpoint condition 0 detected */
#define DR6_B1             0x00000002 /* [bit(1)] Breakpoint condition 1 detected */
#define DR6_B2             0x00000004 /* [bit(2)] Breakpoint condition 2 detected */
#define DR6_B3             0x00000008 /* [bit(3)] Breakpoint condition 3 detected */
#define DR6_BD             0x00002000 /* [bit(13)] Set in `int1' if `DR7_GD' was set and the calling instruction attempted to access %dr{0-7} */
#define DR6_BS             0x00004000 /* [bit(14)] The exception was triggered by single-step (s.a. `EFLAGS_TF') */
#define DR6_BT             0x00008000 /* [bit(15)] The exception was triggered by a task-switch (caused if `*(TSS + 100) & 0x1') */
#define DR6_RTM            0x00010000 /* [bit(16)] Always set, except for exceptions triggered within restricted transactional memory regions. */

#define DR7_BREAKPOINT_COUNT 4

/* NOTE: Undefined bits must remain unchanged! */
#define DR7_L0             0x00000001 /* [bit(0)] local DR0 breakpoint. */
#define DR7_G0             0x00000002 /* [bit(1)] global DR0 breakpoint. */
#define DR7_L1             0x00000004 /* [bit(2)] local DR1 breakpoint. */
#define DR7_G1             0x00000008 /* [bit(3)] global DR1 breakpoint. */
#define DR7_L2             0x00000010 /* [bit(4)] local DR2 breakpoint. */
#define DR7_G2             0x00000020 /* [bit(5)] global DR2 breakpoint. */
#define DR7_L3             0x00000040 /* [bit(6)] local DR3 breakpoint. */
#define DR7_G3             0x00000080 /* [bit(7)] global DR3 breakpoint. */
#define DR7_LE             0x00000100 /* [bit(8)] Local exact breakpoint enable. */
#define DR7_GE             0x00000200 /* [bit(9)] Global exact breakpoint enable. */
#define DR7_RTM            0x00000800 /* [bit(11)] Restricted transactional memory (Requires `IA32_DEBUGCTL.RTM'). */
#define DR7_GD             0x00002000 /* [bit(13)] Enable debug register protection.
                                       * mov instructions attempting to access debug registers
                                       * will cause a #DB exception to be triggered on said mov */
#define DR7_LN(n)         (0x1 << ((n)*2))
#define DR7_GN(n)         (0x2 << ((n)*2))
#define DR7_C0             0x00030000 /* [bit(16..17)] conditions for DR0. */
#define DR7_S0             0x000c0000 /* [bit(18..19)] size of DR0 breakpoint. */
#define DR7_C1             0x00300000 /* [bit(20..21)] conditions for DR1. */
#define DR7_S1             0x00c00000 /* [bit(22..23)] size of DR1 breakpoint. */
#define DR7_C2             0x03000000 /* [bit(24..25)] conditions for DR2. */
#define DR7_S2             0x0c000000 /* [bit(26..27)] size of DR2 breakpoint. */
#define DR7_C3             0x30000000 /* [bit(28..29)] conditions for DR3. */
#define DR7_S3             0xc0000000 /* [bit(30..31)] size of DR3 breakpoint . */
#define DR7_CN(n)          (0x3 << DR7_CN_SHIFT(n))
#define DR7_SN(n)          (0x3 << DR7_SN_SHIFT(n))
#define DR7_C0_SHIFT       16
#define DR7_S0_SHIFT       18
#define DR7_C1_SHIFT       20
#define DR7_S1_SHIFT       22
#define DR7_C2_SHIFT       24
#define DR7_S2_SHIFT       26
#define DR7_C3_SHIFT       28
#define DR7_S3_SHIFT       30
#define DR7_CN_SHIFT(n)   (16+(4*(n)))
#define DR7_SN_SHIFT(n)   (18+(4*(n)))
#define DR_S1              0x0 /* Break within a 1-byte range */
#define DR_S2              0x1 /* Break within a 2-byte range */
#define DR_S4              0x3 /* Break within a 4-byte range */
#define DR_S8              0x2 /* Break within a 8-byte range */
#define DR_CEXEC           0x0 /* Break on execute */
#define DR_CWRITE          0x1 /* Break on write */
#define DR_CREADWRITE      0x3 /* Break on read/write */
#define DR_CIO             0x2 /* Break on io (usually unsupported, never supported on __x86_64__) */


/* From: Figure 8-6 --- IA-32 Intel Architecture Software Developer's Manual, Volume 1
 * NOTE: For use with `__fldcw()' */
/* Exception masks. */
#define FCW_IM   0x0001 /* [bit(0)] Invalid Operation */
#define FCW_DM   0x0002 /* [bit(1)] Denormal operand. */
#define FCW_ZM   0x0004 /* [bit(2)] Zero divide. */
#define FCW_OM   0x0008 /* [bit(3)] Overflow. */
#define FCW_UM   0x0010 /* [bit(4)] Underflow. */
#define FCW_PM   0x0020 /* [bit(5)] Precision. */
/* FPU Control. */
#define FCW_PC   0x0300 /* [bit(8 - 9)] Precision control. */
#   define FCW_PC_SINGLE  0x0000 /* Single Precision (24 bits) */
#   define FCW_PC_DOUBLE  0x0200 /* Double Precision (53 bits) */
#   define FCW_PC_EXTEND  0x0300 /* Double Extended Precision (64 bits) */
#define FCW_RC   0x0c00 /* [bit(10 - 11)] Rounding control. */
#   define FCW_RC_NEAREST 0x0000 /* Result is closest to the infinitely precise result.
                                  * If 2 values are equally close, the even one is used. (DEFAULT) */
#   define FCW_RC_DOWN    0x0400 /* Round towards -INF */
#   define FCW_RC_UP      0x0800 /* Round towards +INF */
#   define FCW_RC_TRUNC   0x0c00 /* Truncate non-representable bits. */
#define FCW_X    0x1000 /* [bit(12)] Infinity Control. */


/* FPU Status word bits. */
#define FSW_IE   0x0001 /* [bit(0)] Invalid Operation (Exception) */
#define FSW_DE   0x0002 /* [bit(1)] Denormalized Operand (Exception) */
#define FSW_ZE   0x0004 /* [bit(2)] Zero Divide (Exception) */
#define FSW_OE   0x0008 /* [bit(3)] Overflow (Exception) */
#define FSW_UE   0x0010 /* [bit(4)] Underflow (Exception) */
#define FSW_PE   0x0020 /* [bit(5)] Precision (Exception) */
#define FSW_SF   0x0040 /* [bit(6)] Stack Fault */
#define FSW_ES   0x0080 /* [bit(7)] Error Summary Status */
#define FSW_C0   0x0100 /* [bit(8)] Condition code */
#define FSW_C1   0x0200 /* [bit(9)] Condition code */
#define FSW_C2   0x0400 /* [bit(10)] Condition code */
#define FSW_C3   0x4000 /* [bit(14)] Condition code */
#define FSW_TOP  0x3800 /* [bit(11 - 13)] Top of stack pointer */
#define FSW_TOP_SHIFT 11 /* Shift for `FSW_TOP' */
#define FSW_B    0x8000 /* [bit(15)] FPU Busy */


/* Bit-pair values for `fs_ftw' (repeated 8 times with i=0:7) */
#define FTW_VALID(i)  0x0              /* Valid */
#define FTW_ZERO(i)  (0x1 << ((i)*2))  /* Zero */
#define FTW_SPEC(i)  (0x2 << ((i)*2))  /* Special (invalid (NaN, unsupported), infinity, or denormal) */
#define FTW_EMPTY(i) (0x3 << ((i)*2))  /* Empty */
#define FTW_MASK(i)  (0x3 << ((i)*2))  /* Mask */
#define FTW_ALLEMPTY  0xffff /* All empty */


/* MXCSR bits. (for use with `__stmxcsr()' / `__ldmxcsr()') */
#define MXCSR_IE  0x00000001 /* [bit(0)] Invalid Operation Flag (sticky, Exception) */
#define MXCSR_DE  0x00000002 /* [bit(1)] Denormal Flag (sticky, Exception) */
#define MXCSR_ZE  0x00000004 /* [bit(2)] Zero Divide Flag (sticky, Exception) */
#define MXCSR_OE  0x00000008 /* [bit(3)] Overflow Flag (sticky, Exception) */
#define MXCSR_UE  0x00000010 /* [bit(4)] Underflow Flag (sticky, Exception) */
#define MXCSR_PE  0x00000020 /* [bit(5)] Precision Flag (sticky, Exception) */
#define MXCSR_DAZ 0x00000040 /* [bit(6)] Denormals Are Zeros */
#define MXCSR_IM  0x00000080 /* [bit(7)] Invalid Operation (Exception mask) */
#define MXCSR_DM  0x00000100 /* [bit(8)] Denormal operand (Exception mask) */
#define MXCSR_ZM  0x00000200 /* [bit(9)] Zero divide (Exception mask) */
#define MXCSR_OM  0x00000400 /* [bit(10)] Overflow (Exception mask) */
#define MXCSR_UM  0x00000800 /* [bit(11)] Underflow (Exception mask) */
#define MXCSR_PM  0x00001000 /* [bit(12)] Precision (Exception mask) */
#define MXCSR_RC  0x00006000 /* [bit(13 - 14)] Rounding control. */
#   define MXCSR_RC_NEAREST 0x00000000 /* Result is closest to the infinitely precise result.
                                        * If 2 values are equally close, the even one is used. (DEFAULT) */
#   define MXCSR_RC_DOWN    0x00002000 /* Round towards -INF */
#   define MXCSR_RC_UP      0x00004000 /* Round towards +INF */
#   define MXCSR_RC_TRUNC   0x00006000 /* Truncate non-representable bits. */
#define MXCSR_FZ  0x00008000 /* [bit(15)] Flush-to-zero. */



#endif /* !_I386_KOS_ASM_CPU_FLAGS_H */
