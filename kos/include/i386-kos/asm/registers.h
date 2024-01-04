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
#ifndef _I386_KOS_ASM_REGISTERS_H
#define _I386_KOS_ASM_REGISTERS_H 1

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#define X86_REGISTER_NONE __UINT16_C(0x0000) /* No/invalid register. */

/* Universal masks for registers. */
#define X86_REGISTER_IDMASK      __UINT16_C(0x03ff)
#define X86_REGISTER_SIZEMASK    __UINT16_C(0x0c00)
#define _X86_REGISTER_SIZESHIFT  10
#define X86_REGISTER_CLASSMASK   __UINT16_C(0xf000)
#define _X86_REGISTER_CLASSSHIFT 12

/* Return the size of a general-purpose, or misc. register. (in bytes) */
#define X86_REGISTER_SIZEOF_SHIFT(x) (3 - (((x) & __UINT16_C(0xc00)) >> 10))
#define X86_REGISTER_SIZEOF(x)       (__SIZE_C(1) << X86_REGISTER_SIZEOF_SHIFT(x))
#define X86_REGISTER_SIZEMASK_1BYTE __UINT16_C(0x0c00)
#define X86_REGISTER_SIZEMASK_2BYTE __UINT16_C(0x0800)
#define X86_REGISTER_SIZEMASK_4BYTE __UINT16_C(0x0400)
#define X86_REGISTER_SIZEMASK_8BYTE __UINT16_C(0x0000)
#ifdef __x86_64__
#define X86_REGISTER_SIZEMASK_PTR X86_REGISTER_SIZEMASK_8BYTE
#else /* __x86_64__ */
#define X86_REGISTER_SIZEMASK_PTR X86_REGISTER_SIZEMASK_4BYTE
#endif /* !__x86_64__ */


/* General-purpose registers. */
#define X86_REGISTER_GENERAL_PURPOSE      __UINT16_C(0x1000)
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_RAX  __UINT16_C(0x1000) /* %rax */
#define X86_REGISTER_GENERAL_PURPOSE_RCX  __UINT16_C(0x1001) /* %rcx */
#define X86_REGISTER_GENERAL_PURPOSE_RDX  __UINT16_C(0x1002) /* %rdx */
#define X86_REGISTER_GENERAL_PURPOSE_RBX  __UINT16_C(0x1003) /* %rbx */
#define X86_REGISTER_GENERAL_PURPOSE_RSP  __UINT16_C(0x1004) /* %rsp */
#define X86_REGISTER_GENERAL_PURPOSE_RBP  __UINT16_C(0x1005) /* %rbp */
#define X86_REGISTER_GENERAL_PURPOSE_RSI  __UINT16_C(0x1006) /* %rsi */
#define X86_REGISTER_GENERAL_PURPOSE_RDI  __UINT16_C(0x1007) /* %rdi */
#define X86_REGISTER_GENERAL_PURPOSE_R8   __UINT16_C(0x1008) /* %r8 */
#define X86_REGISTER_GENERAL_PURPOSE_R9   __UINT16_C(0x1009) /* %r9 */
#define X86_REGISTER_GENERAL_PURPOSE_R10  __UINT16_C(0x100a) /* %r10 */
#define X86_REGISTER_GENERAL_PURPOSE_R11  __UINT16_C(0x100b) /* %r11 */
#define X86_REGISTER_GENERAL_PURPOSE_R12  __UINT16_C(0x100c) /* %r12 */
#define X86_REGISTER_GENERAL_PURPOSE_R13  __UINT16_C(0x100d) /* %r13 */
#define X86_REGISTER_GENERAL_PURPOSE_R14  __UINT16_C(0x100e) /* %r14 */
#define X86_REGISTER_GENERAL_PURPOSE_R15  __UINT16_C(0x100f) /* %r15 */
#endif /* __x86_64__ */
#define X86_REGISTER_GENERAL_PURPOSE_EAX  __UINT16_C(0x1400) /* %eax */
#define X86_REGISTER_GENERAL_PURPOSE_ECX  __UINT16_C(0x1401) /* %ecx */
#define X86_REGISTER_GENERAL_PURPOSE_EDX  __UINT16_C(0x1402) /* %edx */
#define X86_REGISTER_GENERAL_PURPOSE_EBX  __UINT16_C(0x1403) /* %ebx */
#define X86_REGISTER_GENERAL_PURPOSE_ESP  __UINT16_C(0x1404) /* %esp */
#define X86_REGISTER_GENERAL_PURPOSE_EBP  __UINT16_C(0x1405) /* %ebp */
#define X86_REGISTER_GENERAL_PURPOSE_ESI  __UINT16_C(0x1406) /* %esi */
#define X86_REGISTER_GENERAL_PURPOSE_EDI  __UINT16_C(0x1407) /* %edi */
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_R8D  __UINT16_C(0x1408) /* %r8d */
#define X86_REGISTER_GENERAL_PURPOSE_R9D  __UINT16_C(0x1409) /* %r9d */
#define X86_REGISTER_GENERAL_PURPOSE_R10D __UINT16_C(0x140a) /* %r10d */
#define X86_REGISTER_GENERAL_PURPOSE_R11D __UINT16_C(0x140b) /* %r11d */
#define X86_REGISTER_GENERAL_PURPOSE_R12D __UINT16_C(0x140c) /* %r12d */
#define X86_REGISTER_GENERAL_PURPOSE_R13D __UINT16_C(0x140d) /* %r13d */
#define X86_REGISTER_GENERAL_PURPOSE_R14D __UINT16_C(0x140e) /* %r14d */
#define X86_REGISTER_GENERAL_PURPOSE_R15D __UINT16_C(0x140f) /* %r15d */
#endif /* __x86_64__ */
#define X86_REGISTER_GENERAL_PURPOSE_AX   __UINT16_C(0x1800) /* %ax */
#define X86_REGISTER_GENERAL_PURPOSE_CX   __UINT16_C(0x1801) /* %cx */
#define X86_REGISTER_GENERAL_PURPOSE_DX   __UINT16_C(0x1802) /* %dx */
#define X86_REGISTER_GENERAL_PURPOSE_BX   __UINT16_C(0x1803) /* %bx */
#define X86_REGISTER_GENERAL_PURPOSE_SP   __UINT16_C(0x1804) /* %sp */
#define X86_REGISTER_GENERAL_PURPOSE_BP   __UINT16_C(0x1805) /* %bp */
#define X86_REGISTER_GENERAL_PURPOSE_SI   __UINT16_C(0x1806) /* %si */
#define X86_REGISTER_GENERAL_PURPOSE_DI   __UINT16_C(0x1807) /* %di */
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_R8W  __UINT16_C(0x1808) /* %r8w */
#define X86_REGISTER_GENERAL_PURPOSE_R9W  __UINT16_C(0x1809) /* %r9w */
#define X86_REGISTER_GENERAL_PURPOSE_R10W __UINT16_C(0x180a) /* %r10w */
#define X86_REGISTER_GENERAL_PURPOSE_R11W __UINT16_C(0x180b) /* %r11w */
#define X86_REGISTER_GENERAL_PURPOSE_R12W __UINT16_C(0x180c) /* %r12w */
#define X86_REGISTER_GENERAL_PURPOSE_R13W __UINT16_C(0x180d) /* %r13w */
#define X86_REGISTER_GENERAL_PURPOSE_R14W __UINT16_C(0x180e) /* %r14w */
#define X86_REGISTER_GENERAL_PURPOSE_R15W __UINT16_C(0x180f) /* %r15w */
#endif /* __x86_64__ */
#define X86_REGISTER_GENERAL_PURPOSE_AL   __UINT16_C(0x1c00) /* %al */
#define X86_REGISTER_GENERAL_PURPOSE_CL   __UINT16_C(0x1c01) /* %cl */
#define X86_REGISTER_GENERAL_PURPOSE_DL   __UINT16_C(0x1c02) /* %dl */
#define X86_REGISTER_GENERAL_PURPOSE_BL   __UINT16_C(0x1c03) /* %bl */
#define X86_REGISTER_GENERAL_PURPOSE_AH   __UINT16_C(0x1c04) /* %ah */
#define X86_REGISTER_GENERAL_PURPOSE_CH   __UINT16_C(0x1c05) /* %ch */
#define X86_REGISTER_GENERAL_PURPOSE_DH   __UINT16_C(0x1c06) /* %dh */
#define X86_REGISTER_GENERAL_PURPOSE_BH   __UINT16_C(0x1c07) /* %bh */
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_R8L  __UINT16_C(0x1c08) /* %r8l */
#define X86_REGISTER_GENERAL_PURPOSE_R9L  __UINT16_C(0x1c09) /* %r9l */
#define X86_REGISTER_GENERAL_PURPOSE_R10L __UINT16_C(0x1c0a) /* %r10l */
#define X86_REGISTER_GENERAL_PURPOSE_R11L __UINT16_C(0x1c0b) /* %r11l */
#define X86_REGISTER_GENERAL_PURPOSE_R12L __UINT16_C(0x1c0c) /* %r12l */
#define X86_REGISTER_GENERAL_PURPOSE_R13L __UINT16_C(0x1c0d) /* %r13l */
#define X86_REGISTER_GENERAL_PURPOSE_R14L __UINT16_C(0x1c0e) /* %r14l */
#define X86_REGISTER_GENERAL_PURPOSE_R15L __UINT16_C(0x1c0f) /* %r15l */
#define X86_REGISTER_GENERAL_PURPOSE_SPL  __UINT16_C(0x1c14) /* %spl */
#define X86_REGISTER_GENERAL_PURPOSE_BPL  __UINT16_C(0x1c15) /* %bpl */
#define X86_REGISTER_GENERAL_PURPOSE_SIL  __UINT16_C(0x1c16) /* %sil */
#define X86_REGISTER_GENERAL_PURPOSE_DIL  __UINT16_C(0x1c17) /* %dil */
#endif /* __x86_64__ */


/* Segment registers. */
#define X86_REGISTER_SEGMENT       __UINT16_C(0x2000)
#   define X86_REGISTER_SEGMENT_ES __UINT16_C(0x2800) /* %es */
#   define X86_REGISTER_SEGMENT_CS __UINT16_C(0x2801) /* %cs */
#   define X86_REGISTER_SEGMENT_SS __UINT16_C(0x2802) /* %ss */
#   define X86_REGISTER_SEGMENT_DS __UINT16_C(0x2803) /* %ds */
#   define X86_REGISTER_SEGMENT_FS __UINT16_C(0x2804) /* %fs */
#   define X86_REGISTER_SEGMENT_GS __UINT16_C(0x2805) /* %gs */


/* Control registers. */
#define X86_REGISTER_CONTROL        __UINT16_C(0x3000)
#ifdef __x86_64__
#   define X86_REGISTER_CONTROL_CR0 __UINT16_C(0x3000) /* %cr0 */
#   define X86_REGISTER_CONTROL_CR2 __UINT16_C(0x3002) /* %cr2 */
#   define X86_REGISTER_CONTROL_CR3 __UINT16_C(0x3003) /* %cr3 */
#   define X86_REGISTER_CONTROL_CR4 __UINT16_C(0x3004) /* %cr4 */
#   define X86_REGISTER_CONTROL_CR8 __UINT16_C(0x3008) /* %cr4 */
#else /* __x86_64__ */
#   define X86_REGISTER_CONTROL_CR0 __UINT16_C(0x3400) /* %cr0 */
#   define X86_REGISTER_CONTROL_CR2 __UINT16_C(0x3402) /* %cr2 */
#   define X86_REGISTER_CONTROL_CR3 __UINT16_C(0x3403) /* %cr3 */
#   define X86_REGISTER_CONTROL_CR4 __UINT16_C(0x3404) /* %cr4 */
#endif /* !__x86_64__ */

/* Float registers. */
#define X86_REGISTER_FLOAT          __UINT16_C(0x4000)
#   define X86_REGISTER_FLOAT_ST(x) (__UINT16_C(0x4000) | ((x) & 7)) /* %st(x) */
#   define X86_REGISTER_FLOAT_ST0   __UINT16_C(0x4000) /* %st(0) */
#   define X86_REGISTER_FLOAT_ST1   __UINT16_C(0x4001) /* %st(1) */
#   define X86_REGISTER_FLOAT_ST2   __UINT16_C(0x4002) /* %st(2) */
#   define X86_REGISTER_FLOAT_ST3   __UINT16_C(0x4003) /* %st(3) */
#   define X86_REGISTER_FLOAT_ST4   __UINT16_C(0x4004) /* %st(4) */
#   define X86_REGISTER_FLOAT_ST5   __UINT16_C(0x4005) /* %st(5) */
#   define X86_REGISTER_FLOAT_ST6   __UINT16_C(0x4006) /* %st(6) */
#   define X86_REGISTER_FLOAT_ST7   __UINT16_C(0x4007) /* %st(7) */

/* MMX registers. */
#define X86_REGISTER_MMX        __UINT16_C(0x5000)
#   define X86_REGISTER_MMX_MM0 __UINT16_C(0x5000) /* %mm0 */
#   define X86_REGISTER_MMX_MM1 __UINT16_C(0x5001) /* %mm1 */
#   define X86_REGISTER_MMX_MM2 __UINT16_C(0x5002) /* %mm2 */
#   define X86_REGISTER_MMX_MM3 __UINT16_C(0x5003) /* %mm3 */
#   define X86_REGISTER_MMX_MM4 __UINT16_C(0x5004) /* %mm4 */
#   define X86_REGISTER_MMX_MM5 __UINT16_C(0x5005) /* %mm5 */
#   define X86_REGISTER_MMX_MM6 __UINT16_C(0x5006) /* %mm6 */
#   define X86_REGISTER_MMX_MM7 __UINT16_C(0x5007) /* %mm7 */

/* XMM registers. */
#define X86_REGISTER_XMM          __UINT16_C(0x6000)
#   define X86_REGISTER_XMM_XMM0  __UINT16_C(0x6000) /* %xmm0 */
#   define X86_REGISTER_XMM_XMM1  __UINT16_C(0x6001) /* %xmm1 */
#   define X86_REGISTER_XMM_XMM2  __UINT16_C(0x6002) /* %xmm2 */
#   define X86_REGISTER_XMM_XMM3  __UINT16_C(0x6003) /* %xmm3 */
#   define X86_REGISTER_XMM_XMM4  __UINT16_C(0x6004) /* %xmm4 */
#   define X86_REGISTER_XMM_XMM5  __UINT16_C(0x6005) /* %xmm5 */
#   define X86_REGISTER_XMM_XMM6  __UINT16_C(0x6006) /* %xmm6 */
#   define X86_REGISTER_XMM_XMM7  __UINT16_C(0x6007) /* %xmm7 */
#ifdef __x86_64__
#   define X86_REGISTER_XMM_XMM8  __UINT16_C(0x6008) /* %xmm8 */
#   define X86_REGISTER_XMM_XMM9  __UINT16_C(0x6009) /* %xmm9 */
#   define X86_REGISTER_XMM_XMM10 __UINT16_C(0x600a) /* %xmm10 */
#   define X86_REGISTER_XMM_XMM11 __UINT16_C(0x600b) /* %xmm11 */
#   define X86_REGISTER_XMM_XMM12 __UINT16_C(0x600c) /* %xmm12 */
#   define X86_REGISTER_XMM_XMM13 __UINT16_C(0x600d) /* %xmm13 */
#   define X86_REGISTER_XMM_XMM14 __UINT16_C(0x600e) /* %xmm14 */
#   define X86_REGISTER_XMM_XMM15 __UINT16_C(0x600f) /* %xmm15 */
#endif /* __x86_64__ */

/* YMM registers. */
#define X86_REGISTER_YMM          __UINT16_C(0x7000)
#   define X86_REGISTER_YMM_YMM0  __UINT16_C(0x7000) /* %ymm0 */
#   define X86_REGISTER_YMM_YMM1  __UINT16_C(0x7001) /* %ymm1 */
#   define X86_REGISTER_YMM_YMM2  __UINT16_C(0x7002) /* %ymm2 */
#   define X86_REGISTER_YMM_YMM3  __UINT16_C(0x7003) /* %ymm3 */
#   define X86_REGISTER_YMM_YMM4  __UINT16_C(0x7004) /* %ymm4 */
#   define X86_REGISTER_YMM_YMM5  __UINT16_C(0x7005) /* %ymm5 */
#   define X86_REGISTER_YMM_YMM6  __UINT16_C(0x7006) /* %ymm6 */
#   define X86_REGISTER_YMM_YMM7  __UINT16_C(0x7007) /* %ymm7 */
#ifdef __x86_64__
#   define X86_REGISTER_YMM_YMM8  __UINT16_C(0x7008) /* %ymm8 */
#   define X86_REGISTER_YMM_YMM9  __UINT16_C(0x7009) /* %ymm9 */
#   define X86_REGISTER_YMM_YMM10 __UINT16_C(0x700a) /* %ymm10 */
#   define X86_REGISTER_YMM_YMM11 __UINT16_C(0x700b) /* %ymm11 */
#   define X86_REGISTER_YMM_YMM12 __UINT16_C(0x700c) /* %ymm12 */
#   define X86_REGISTER_YMM_YMM13 __UINT16_C(0x700d) /* %ymm13 */
#   define X86_REGISTER_YMM_YMM14 __UINT16_C(0x700e) /* %ymm14 */
#   define X86_REGISTER_YMM_YMM15 __UINT16_C(0x700f) /* %ymm15 */
#endif /* __x86_64__ */

/* Debug registers. */
#define X86_REGISTER_DEBUG        __UINT16_C(0x8000)
#ifdef __x86_64__
#   define X86_REGISTER_DEBUG_DR0 __UINT16_C(0x8000) /* %dr0 */
#   define X86_REGISTER_DEBUG_DR1 __UINT16_C(0x8001) /* %dr1 */
#   define X86_REGISTER_DEBUG_DR2 __UINT16_C(0x8002) /* %dr2 */
#   define X86_REGISTER_DEBUG_DR3 __UINT16_C(0x8003) /* %dr3 */
#   define X86_REGISTER_DEBUG_DR6 __UINT16_C(0x8006) /* %dr6 */
#   define X86_REGISTER_DEBUG_DR7 __UINT16_C(0x8007) /* %dr7 */
#else /* __x86_64__ */
#   define X86_REGISTER_DEBUG_DR0 __UINT16_C(0x8400) /* %dr0 */
#   define X86_REGISTER_DEBUG_DR1 __UINT16_C(0x8401) /* %dr1 */
#   define X86_REGISTER_DEBUG_DR2 __UINT16_C(0x8402) /* %dr2 */
#   define X86_REGISTER_DEBUG_DR3 __UINT16_C(0x8403) /* %dr3 */
#   define X86_REGISTER_DEBUG_DR6 __UINT16_C(0x8406) /* %dr6 */
#   define X86_REGISTER_DEBUG_DR7 __UINT16_C(0x8407) /* %dr7 */
#endif /* !__x86_64__ */

/* Misc. registers. */
#define X86_REGISTER_MISC               __UINT16_C(0x9000)
#   define X86_REGISTER_MISC_EFLAGS     __UINT16_C(0x9400) /* %eflags */
#   define X86_REGISTER_MISC_FLAGS      __UINT16_C(0x9800) /* %flags */
#   define X86_REGISTER_MISC_EIP        __UINT16_C(0x9401) /* %eip */
#   define X86_REGISTER_MISC_IP         __UINT16_C(0x9801) /* %ip */
#ifdef __x86_64__
#   define X86_REGISTER_MISC_RFLAGS     __UINT16_C(0x9000) /* %rflags */
#   define X86_REGISTER_MISC_RIP        __UINT16_C(0x9001) /* %rip */
#endif /* __x86_64__ */
#   define X86_REGISTER_MISC_TR         __UINT16_C(0x9810) /* %tr (ltr, str; TaskRegister) */
#   define X86_REGISTER_MISC_LDT        __UINT16_C(0x9811) /* %ldt (lldt, sldt; LocalDescriptorTable) */
#   define X86_REGISTER_MISC_GDT_LIMIT  __UINT16_C(0x9812) /* %gdt.limit (lgdt, sgdt; GlobalDescriptorTable) */
#   define X86_REGISTER_MISC_GDT_BASEL  __UINT16_C(0x9413) /* %gdt.basel (lgdt, sgdt; GlobalDescriptorTable) */
#   define X86_REGISTER_MISC_IDT_LIMIT  __UINT16_C(0x9814) /* %idt.limit (lidt, sidt; InterruptDescriptorTable) */
#   define X86_REGISTER_MISC_IDT_BASEL  __UINT16_C(0x9415) /* %idt.basel (lidt, sidt; InterruptDescriptorTable) */
#ifdef __x86_64__
#   define X86_REGISTER_MISC_GDT_BASEQ  __UINT16_C(0x9013) /* %gdt.baseq (lgdt, sgdt; GlobalDescriptorTable) */
#   define X86_REGISTER_MISC_IDT_BASEQ  __UINT16_C(0x9015) /* %idt.baseq (lidt, sidt; InterruptDescriptorTable) */
#endif /* __x86_64__ */
#   define X86_REGISTER_MISC_FSBASEL    __UINT16_C(0x9420) /* %fs.basel */
#   define X86_REGISTER_MISC_GSBASEL    __UINT16_C(0x9421) /* %gs.basel */
#ifdef __x86_64__
/* NOTE:
 *   - `X86_REGISTER_MISC_GSBASE(L|Q)' always  refers to  the
 *     user-space `%gs.base' register. As such, its value is:
 *     >> #ifdef __KERNEL__
 *     >> __rdmsr(IA32_KERNEL_GS_BASE);
 *     >> #else
 *     >> __rdmsr(IA32_GS_BASE); // or `__rdgsbase()'
 *     >> #endif
 *   - `X86_REGISTER_MISC_KGSBASE(L|Q)'   always    refers   to    the
 *     kernel-space `%kernel_gs.base' register. As such, its value is:
 *     >> #ifdef __KERNEL__
 *     >> __rdmsr(IA32_GS_BASE); // or `__rdgsbase()', or `__rdgsptr(0)'
 *     >> #else
 *     >> // Not actually allowed to be read, but this is what you ~would~ have to do
 *     >> __rdmsr(IA32_KERNEL_GS_BASE);
 *     >> #endif */
#   define X86_REGISTER_MISC_FSBASEQ    __UINT16_C(0x9020) /* %fs.baseq (user-space) */
#   define X86_REGISTER_MISC_GSBASEQ    __UINT16_C(0x9021) /* %gs.baseq (user-space) */
#   define X86_REGISTER_MISC_KGSBASEL   __UINT16_C(0x9422) /* %kernel_gs.baseq (kernel-space; should always equal `THIS_TASK') */
#   define X86_REGISTER_MISC_KGSBASEQ   __UINT16_C(0x9022) /* %kernel_gs.baseq (kernel-space; should always equal `THIS_TASK') */
#endif /* __x86_64__ */
#   define X86_REGISTER_MISC_FCW        __UINT16_C(0x9830) /* %fcw (FpuControlWord; `sfpuenv::fe_fcw,sfpustate::fs_fcw,xfpustate::fx_fcw') */
#   define X86_REGISTER_MISC_FSW        __UINT16_C(0x9831) /* %fsw (FpuStatusWord; `sfpuenv::fe_fsw,sfpustate::fs_fsw,xfpustate::fx_fsw') */
#   define X86_REGISTER_MISC_FTW        __UINT16_C(0x9832) /* %ftw (FpuTagWord; `sfpuenv::fe_ftw,sfpustate::fs_ftw') */
#   define X86_REGISTER_MISC_FTWX       __UINT16_C(0x9c33) /* %ftwx (FpuTagWordX; `xfpustate::fx_ftw') */
#   define X86_REGISTER_MISC_FOP        __UINT16_C(0x9834) /* %fop (FpuOPcode; `sfpuenv::fe_fop,sfpustate::fs_fop,xfpustate::fx_fop')
                                                            * NOTE: actually an 11-bit register */
#   define X86_REGISTER_MISC_FIPL       __UINT16_C(0x9435) /* %fipl (FpuInstructionPointer; `sfpuenv::fe_fip,sfpustate::fs_fip,xfpustate::fx_fip') */
#   define X86_REGISTER_MISC_FCS        __UINT16_C(0x9836) /* %fcs (FpuCodeSegment; `sfpuenv::fe_fcs,sfpustate::fs_fcs') (NOTE: Always `0' for `xfpustate') */
#   define X86_REGISTER_MISC_FDPL       __UINT16_C(0x9437) /* %fdpl (FpuDataPointer; `sfpuenv::fe_fdp,sfpustate::fs_fdp,xfpustate::fx_fdp') */
#   define X86_REGISTER_MISC_FDS        __UINT16_C(0x9838) /* %fds (FpuDataSegment; `sfpuenv::fe_fds,sfpustate::fs_fds') (NOTE: Always `0' for `xfpustate') */
#ifdef __x86_64__
#   define X86_REGISTER_MISC_FIPQ       __UINT16_C(0x9035) /* %fipq (FpuInstructionPointer; `sfpuenv::fe_fip,sfpustate::fs_fip,xfpustate::fx_fip') */
#   define X86_REGISTER_MISC_FDPQ       __UINT16_C(0x9037) /* %fdpq (FpuDataPointer; `sfpuenv::fe_fdp,sfpustate::fs_fdp,xfpustate::fx_fdp') */
#endif /* __x86_64__ */
#   define X86_REGISTER_MISC_MXCSR      __UINT16_C(0x9439) /* %mxcsr (MXCSR (SSE only); `xfpustate::fx_mxcsr') */
#   define X86_REGISTER_MISC_MXCSR_MASK __UINT16_C(0x943a) /* %mxcsr_mask (MXCSR mask (SSE only); `xfpustate::fx_mxcsr_mask') */
#   define X86_REGISTER_MISC_MWAIT      __UINT16_C(0x9701) /* mwait:%ecx */
#   define X86_REGISTER_MISC_MONITOR    __UINT16_C(0x9702) /* monitor:%ecx */
#   define X86_REGISTER_MISC_TPAUSE     __UINT16_C(0x9703) /* tpause:operand */
#   define X86_REGISTER_MISC_ENCLS      __UINT16_C(0x9704) /* encls:%eax */
#   define X86_REGISTER_MISC_ENCLU      __UINT16_C(0x9705) /* enclu:%eax */
#   define X86_REGISTER_MISC_GI         __UINT16_C(0x9706) /* GlobalInterrupt (s.a. clgi/stgi) */

/* Extended Control Register */
#define X86_REGISTER_XCR __UINT16_C(0xd000)

/* Performance Counter Register */
#define X86_REGISTER_PCR __UINT16_C(0xe000)

/* Model-Specific Registers. */
#define X86_REGISTER_MSR __UINT16_C(0xf000)


#endif /* !_I386_KOS_ASM_REGISTERS_H */
