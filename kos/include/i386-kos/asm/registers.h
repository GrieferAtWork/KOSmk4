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
#ifndef _I386_KOS_ASM_REGISTERS_H
#define _I386_KOS_ASM_REGISTERS_H 1

#include <hybrid/host.h>

#define X86_REGISTER_NONE              0x0000 /* No/invalid register. */

/* Universal masks for registers. */
#define X86_REGISTER_IDMASK     0x03ff
#define X86_REGISTER_SIZEMASK   0x0c00
#define X86_REGISTER_CLASSMASK  0xf000

/* Return the size of a general-purpose, or misc. register. (in bytes) */
#define X86_REGISTER_SIZEOF(x) (1 << (3 - (((x) & 0xc00) >> 14)))


/* General-purpose registers. */
#define X86_REGISTER_GENERAL_PURPOSE   0x1000
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_RAX  0x1000 /* %rax */
#define X86_REGISTER_GENERAL_PURPOSE_RCX  0x1001 /* %rcx */
#define X86_REGISTER_GENERAL_PURPOSE_RDX  0x1002 /* %rdx */
#define X86_REGISTER_GENERAL_PURPOSE_RBX  0x1003 /* %rbx */
#define X86_REGISTER_GENERAL_PURPOSE_RSP  0x1004 /* %rsp */
#define X86_REGISTER_GENERAL_PURPOSE_RBP  0x1005 /* %rbp */
#define X86_REGISTER_GENERAL_PURPOSE_RSI  0x1006 /* %rsi */
#define X86_REGISTER_GENERAL_PURPOSE_RDI  0x1007 /* %rdi */
#define X86_REGISTER_GENERAL_PURPOSE_R8   0x1008 /* %r8 */
#define X86_REGISTER_GENERAL_PURPOSE_R9   0x1009 /* %r9 */
#define X86_REGISTER_GENERAL_PURPOSE_R10  0x100a /* %r10 */
#define X86_REGISTER_GENERAL_PURPOSE_R11  0x100b /* %r11 */
#define X86_REGISTER_GENERAL_PURPOSE_R12  0x100c /* %r12 */
#define X86_REGISTER_GENERAL_PURPOSE_R13  0x100d /* %r13 */
#define X86_REGISTER_GENERAL_PURPOSE_R14  0x100e /* %r14 */
#define X86_REGISTER_GENERAL_PURPOSE_R15  0x100f /* %r15 */
#endif /* __x86_64__ */
#define X86_REGISTER_GENERAL_PURPOSE_EAX  0x1400 /* %eax */
#define X86_REGISTER_GENERAL_PURPOSE_ECX  0x1401 /* %ecx */
#define X86_REGISTER_GENERAL_PURPOSE_EDX  0x1402 /* %edx */
#define X86_REGISTER_GENERAL_PURPOSE_EBX  0x1403 /* %ebx */
#define X86_REGISTER_GENERAL_PURPOSE_ESP  0x1404 /* %esp */
#define X86_REGISTER_GENERAL_PURPOSE_EBP  0x1405 /* %ebp */
#define X86_REGISTER_GENERAL_PURPOSE_ESI  0x1406 /* %esi */
#define X86_REGISTER_GENERAL_PURPOSE_EDI  0x1407 /* %edi */
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_R8D  0x1408 /* %r8d */
#define X86_REGISTER_GENERAL_PURPOSE_R9D  0x1409 /* %r9d */
#define X86_REGISTER_GENERAL_PURPOSE_R10D 0x140a /* %r10d */
#define X86_REGISTER_GENERAL_PURPOSE_R11D 0x140b /* %r11d */
#define X86_REGISTER_GENERAL_PURPOSE_R12D 0x140c /* %r12d */
#define X86_REGISTER_GENERAL_PURPOSE_R13D 0x140d /* %r13d */
#define X86_REGISTER_GENERAL_PURPOSE_R14D 0x140e /* %r14d */
#define X86_REGISTER_GENERAL_PURPOSE_R15D 0x140f /* %r15d */
#endif /* __x86_64__ */
#define X86_REGISTER_GENERAL_PURPOSE_AX   0x1800 /* %ax */
#define X86_REGISTER_GENERAL_PURPOSE_CX   0x1801 /* %cx */
#define X86_REGISTER_GENERAL_PURPOSE_DX   0x1802 /* %dx */
#define X86_REGISTER_GENERAL_PURPOSE_BX   0x1803 /* %bx */
#define X86_REGISTER_GENERAL_PURPOSE_SP   0x1804 /* %sp */
#define X86_REGISTER_GENERAL_PURPOSE_BP   0x1805 /* %bp */
#define X86_REGISTER_GENERAL_PURPOSE_SI   0x1806 /* %si */
#define X86_REGISTER_GENERAL_PURPOSE_DI   0x1807 /* %di */
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_R8W  0x1808 /* %r8w */
#define X86_REGISTER_GENERAL_PURPOSE_R9W  0x1809 /* %r9w */
#define X86_REGISTER_GENERAL_PURPOSE_R10W 0x180a /* %r10w */
#define X86_REGISTER_GENERAL_PURPOSE_R11W 0x180b /* %r11w */
#define X86_REGISTER_GENERAL_PURPOSE_R12W 0x180c /* %r12w */
#define X86_REGISTER_GENERAL_PURPOSE_R13W 0x180d /* %r13w */
#define X86_REGISTER_GENERAL_PURPOSE_R14W 0x180e /* %r14w */
#define X86_REGISTER_GENERAL_PURPOSE_R15W 0x180f /* %r15w */
#endif /* __x86_64__ */
#define X86_REGISTER_GENERAL_PURPOSE_AL   0x1c00 /* %al */
#define X86_REGISTER_GENERAL_PURPOSE_CL   0x1c01 /* %cl */
#define X86_REGISTER_GENERAL_PURPOSE_DL   0x1c02 /* %dl */
#define X86_REGISTER_GENERAL_PURPOSE_BL   0x1c03 /* %bl */
#define X86_REGISTER_GENERAL_PURPOSE_AH   0x1c04 /* %ah */
#define X86_REGISTER_GENERAL_PURPOSE_CH   0x1c05 /* %ch */
#define X86_REGISTER_GENERAL_PURPOSE_DH   0x1c06 /* %dh */
#define X86_REGISTER_GENERAL_PURPOSE_BH   0x1c07 /* %bh */
#ifdef __x86_64__
#define X86_REGISTER_GENERAL_PURPOSE_R8L  0x1c08 /* %r8l */
#define X86_REGISTER_GENERAL_PURPOSE_R9L  0x1c09 /* %r9l */
#define X86_REGISTER_GENERAL_PURPOSE_R10L 0x1c0a /* %r10l */
#define X86_REGISTER_GENERAL_PURPOSE_R11L 0x1c0b /* %r11l */
#define X86_REGISTER_GENERAL_PURPOSE_R12L 0x1c0c /* %r12l */
#define X86_REGISTER_GENERAL_PURPOSE_R13L 0x1c0d /* %r13l */
#define X86_REGISTER_GENERAL_PURPOSE_R14L 0x1c0e /* %r14l */
#define X86_REGISTER_GENERAL_PURPOSE_R15L 0x1c0f /* %r15l */
#define X86_REGISTER_GENERAL_PURPOSE_SPL  0x1c14 /* %spl */
#define X86_REGISTER_GENERAL_PURPOSE_BPL  0x1c15 /* %bpl */
#define X86_REGISTER_GENERAL_PURPOSE_SIL  0x1c16 /* %sil */
#define X86_REGISTER_GENERAL_PURPOSE_DIL  0x1c17 /* %dil */
#endif /* __x86_64__ */


/* Segment registers. */
#define X86_REGISTER_SEGMENT           0x2000
#   define X86_REGISTER_SEGMENT_ES     0x2000 /* %es */
#   define X86_REGISTER_SEGMENT_CS     0x2001 /* %cs */
#   define X86_REGISTER_SEGMENT_SS     0x2002 /* %ss */
#   define X86_REGISTER_SEGMENT_DS     0x2003 /* %ds */
#   define X86_REGISTER_SEGMENT_FS     0x2004 /* %fs */
#   define X86_REGISTER_SEGMENT_GS     0x2005 /* %gs */


/* Control registers. */
#define X86_REGISTER_CONTROL           0x3000
#   define X86_REGISTER_CONTROL_CR0    0x3000 /* %cr0 */
#   define X86_REGISTER_CONTROL_CR2    0x3002 /* %cr2 */
#   define X86_REGISTER_CONTROL_CR3    0x3003 /* %cr3 */
#   define X86_REGISTER_CONTROL_CR4    0x3004 /* %cr4 */

/* Float registers. */
#define X86_REGISTER_FLOAT             0x4000
#   define X86_REGISTER_FLOAT_ST(x)   (0x4000|((x)&7)) /* %st(x) */
#   define X86_REGISTER_FLOAT_ST0      0x4000 /* %st(0) */
#   define X86_REGISTER_FLOAT_ST1      0x4001 /* %st(1) */
#   define X86_REGISTER_FLOAT_ST2      0x4002 /* %st(2) */
#   define X86_REGISTER_FLOAT_ST3      0x4003 /* %st(3) */
#   define X86_REGISTER_FLOAT_ST4      0x4004 /* %st(4) */
#   define X86_REGISTER_FLOAT_ST5      0x4005 /* %st(5) */
#   define X86_REGISTER_FLOAT_ST6      0x4006 /* %st(6) */
#   define X86_REGISTER_FLOAT_ST7      0x4007 /* %st(7) */

/* MMX registers. */
#define X86_REGISTER_MMX               0x5000
#   define X86_REGISTER_MMX_MM0        0x5000 /* %mm0 */
#   define X86_REGISTER_MMX_MM1        0x5001 /* %mm1 */
#   define X86_REGISTER_MMX_MM2        0x5002 /* %mm2 */
#   define X86_REGISTER_MMX_MM3        0x5003 /* %mm3 */
#   define X86_REGISTER_MMX_MM4        0x5004 /* %mm4 */
#   define X86_REGISTER_MMX_MM5        0x5005 /* %mm5 */
#   define X86_REGISTER_MMX_MM6        0x5006 /* %mm6 */
#   define X86_REGISTER_MMX_MM7        0x5007 /* %mm7 */

/* XMM registers. */
#define X86_REGISTER_XMM               0x6000
#   define X86_REGISTER_XMM_XMM0       0x6000 /* %xmm0 */
#   define X86_REGISTER_XMM_XMM1       0x6001 /* %xmm1 */
#   define X86_REGISTER_XMM_XMM2       0x6002 /* %xmm2 */
#   define X86_REGISTER_XMM_XMM3       0x6003 /* %xmm3 */
#   define X86_REGISTER_XMM_XMM4       0x6004 /* %xmm4 */
#   define X86_REGISTER_XMM_XMM5       0x6005 /* %xmm5 */
#   define X86_REGISTER_XMM_XMM6       0x6006 /* %xmm6 */
#   define X86_REGISTER_XMM_XMM7       0x6007 /* %xmm7 */
#ifdef __x86_64__
#   define X86_REGISTER_XMM_XMM8       0x6008 /* %xmm8 */
#   define X86_REGISTER_XMM_XMM9       0x6009 /* %xmm9 */
#   define X86_REGISTER_XMM_XMM10      0x600a /* %xmm10 */
#   define X86_REGISTER_XMM_XMM11      0x600b /* %xmm11 */
#   define X86_REGISTER_XMM_XMM12      0x600c /* %xmm12 */
#   define X86_REGISTER_XMM_XMM13      0x600d /* %xmm13 */
#   define X86_REGISTER_XMM_XMM14      0x600e /* %xmm14 */
#   define X86_REGISTER_XMM_XMM15      0x600f /* %xmm15 */
#endif /* __x86_64__ */

/* YMM registers. */
#define X86_REGISTER_YMM               0x7000
#   define X86_REGISTER_YMM_YMM0       0x7000 /* %ymm0 */
#   define X86_REGISTER_YMM_YMM1       0x7001 /* %ymm1 */
#   define X86_REGISTER_YMM_YMM2       0x7002 /* %ymm2 */
#   define X86_REGISTER_YMM_YMM3       0x7003 /* %ymm3 */
#   define X86_REGISTER_YMM_YMM4       0x7004 /* %ymm4 */
#   define X86_REGISTER_YMM_YMM5       0x7005 /* %ymm5 */
#   define X86_REGISTER_YMM_YMM6       0x7006 /* %ymm6 */
#   define X86_REGISTER_YMM_YMM7       0x7007 /* %ymm7 */
#ifdef __x86_64__
#   define X86_REGISTER_YMM_YMM8       0x7008 /* %ymm8 */
#   define X86_REGISTER_YMM_YMM9       0x7009 /* %ymm9 */
#   define X86_REGISTER_YMM_YMM10      0x700a /* %ymm10 */
#   define X86_REGISTER_YMM_YMM11      0x700b /* %ymm11 */
#   define X86_REGISTER_YMM_YMM12      0x700c /* %ymm12 */
#   define X86_REGISTER_YMM_YMM13      0x700d /* %ymm13 */
#   define X86_REGISTER_YMM_YMM14      0x700e /* %ymm14 */
#   define X86_REGISTER_YMM_YMM15      0x700f /* %ymm15 */
#endif

/* Debug registers. */
#define X86_REGISTER_DEBUG             0x8000
#   define X86_REGISTER_DEBUG_DR0      0x8000 /* %dr0 */
#   define X86_REGISTER_DEBUG_DR1      0x8001 /* %dr1 */
#   define X86_REGISTER_DEBUG_DR2      0x8002 /* %dr2 */
#   define X86_REGISTER_DEBUG_DR3      0x8003 /* %dr3 */
#   define X86_REGISTER_DEBUG_DR4      0x8004 /* %dr4 */
#   define X86_REGISTER_DEBUG_DR5      0x8005 /* %dr5 */
#   define X86_REGISTER_DEBUG_DR6      0x8006 /* %dr6 */
#   define X86_REGISTER_DEBUG_DR7      0x8007 /* %dr7 */
#ifdef __x86_64__
#   define X86_REGISTER_DEBUG_DR8      0x8008 /* %dr8 */
#   define X86_REGISTER_DEBUG_DR9      0x8009 /* %dr9 */
#   define X86_REGISTER_DEBUG_DR10     0x800a /* %dr10 */
#   define X86_REGISTER_DEBUG_DR11     0x800b /* %dr11 */
#   define X86_REGISTER_DEBUG_DR12     0x800c /* %dr12 */
#   define X86_REGISTER_DEBUG_DR13     0x800d /* %dr13 */
#   define X86_REGISTER_DEBUG_DR14     0x800e /* %dr14 */
#   define X86_REGISTER_DEBUG_DR15     0x800f /* %dr15 */
#endif /* __x86_64__ */

/* Misc. registers. */
#define X86_REGISTER_MISC              0xe000
#ifdef __x86_64__
#   define X86_REGISTER_MISC_RFLAGS    0xe000 /* %rflags */
#endif /* __x86_64__ */
#   define X86_REGISTER_MISC_EFLAGS    0xe400 /* %eflags */
#   define X86_REGISTER_MISC_FLAGS     0xe800 /* %flags */
#   define X86_REGISTER_MISC_TR        0xe810 /* %tr (ltr, str; TaskRegister) */
#   define X86_REGISTER_MISC_LDT       0xe811 /* %ldt (lldt, sldt; LocalDescriptorTable) */
#   define X86_REGISTER_MISC_GDT       0xe812 /* %gdt (lgdt, sgdt; GlobalDescriptorTable) */
#   define X86_REGISTER_MISC_IDT       0xe813 /* %idt (lidt, sidt; InterruptDescriptorTable) */

/* Model-specific registers. */
#define X86_REGISTER_MSR               0xf000


#endif /* !_I386_KOS_ASM_REGISTERS_H */
