/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_I386_MSABI64_H
#define GUARD_LIBC_LIBC_ARCH_I386_MSABI64_H 1

/* Some reminders on the differences between SYSVABI and MSABI:
 *
 * ```
 *  [argv]   SYSVABI    MSABI
 *  ARG#1    %rdi       %rcx
 *  ARG#2    %rsi       %rdx
 *  ARG#3    %rdx       %r8
 *  ARG#4    %rcx       %r9
 *  ARG#5    %r8        8(%rsp)
 *  ARG#6    %r9        16(%rsp)
 *  ARG#7    8(%rsp)    24(%rsp)
 *  ARG#8    16(%rsp)   32(%rsp)
 *           ...        ...
 *
 *  [Preserve]
 *  SYSVABI    %rbx, %rbp,             %r12, %r13, %r14, %r15
 *  MSABI      %rbx, %rbp, %rdi, %rsi, %r12, %r13, %r14, %r15
 *
 *  [Clobber]
 *  SYSVABI    %rax, %rcx, %rdx, %rsi, %rdi, %r8, %r9, %r10, %r11
 *  MSABI      %rax, %rcx, %rdx,             %r8, %r9, %r10, %r11
 * ```
 */


/* 32 unnecessary bytes of pure bloat, as mandated by the specs (ugh...) */
#define MSABI_SHADOWSPACE_SIZE 32

/* NOTE: There is a requirement that `(MSABI_SAVEZONE_SIZE % 16) == 0',
 *       in order to ensure a 16-bit aligned stack upon entry to libc_* */
#define MSABI_SAVEZONE_SIZE 176
#define MSABI_SAVEZONE_PUSH()       \
	pushq_cfi_r %rdi;               \
	pushq_cfi_r %rsi;               \
	subq   $(160), %rsp;            \
	.cfi_adjust_cfa_offset 160;     \
	movaps %xmm15, (9 * 16)(%rsp);  \
	.cfi_rel_offset %xmm15, 9 * 16; \
	movaps %xmm14, (8 * 16)(%rsp);  \
	.cfi_rel_offset %xmm14, 8 * 16; \
	movaps %xmm13, (7 * 16)(%rsp);  \
	.cfi_rel_offset %xmm13, 7 * 16; \
	movaps %xmm12, (6 * 16)(%rsp);  \
	.cfi_rel_offset %xmm12, 6 * 16; \
	movaps %xmm11, (5 * 16)(%rsp);  \
	.cfi_rel_offset %xmm11, 5 * 16; \
	movaps %xmm10, (4 * 16)(%rsp);  \
	.cfi_rel_offset %xmm10, 4 * 16; \
	movaps %xmm9,  (3 * 16)(%rsp);  \
	.cfi_rel_offset %xmm9,  3 * 16; \
	movaps %xmm8,  (2 * 16)(%rsp);  \
	.cfi_rel_offset %xmm8,  2 * 16; \
	movaps %xmm7,  (1 * 16)(%rsp);  \
	.cfi_rel_offset %xmm7,  1 * 16; \
	movaps %xmm6,  (0 * 16)(%rsp);  \
	.cfi_rel_offset %xmm6,  0 * 16

#define MSABI_SAVEZONE_POP()       \
	movaps (0 * 16)(%rsp), %xmm6;  \
	.cfi_same_value %xmm6;         \
	movaps (1 * 16)(%rsp), %xmm7;  \
	.cfi_same_value %xmm7;         \
	movaps (2 * 16)(%rsp), %xmm8;  \
	.cfi_same_value %xmm8;         \
	movaps (3 * 16)(%rsp), %xmm9;  \
	.cfi_same_value %xmm9;         \
	movaps (4 * 16)(%rsp), %xmm10; \
	.cfi_same_value %xmm10;        \
	movaps (5 * 16)(%rsp), %xmm11; \
	.cfi_same_value %xmm11;        \
	movaps (6 * 16)(%rsp), %xmm12; \
	.cfi_same_value %xmm12;        \
	movaps (7 * 16)(%rsp), %xmm13; \
	.cfi_same_value %xmm13;        \
	movaps (8 * 16)(%rsp), %xmm14; \
	.cfi_same_value %xmm14;        \
	movaps (9 * 16)(%rsp), %xmm15; \
	.cfi_same_value %xmm15;        \
	addq   $(160), %rsp;           \
	.cfi_adjust_cfa_offset -160;   \
	popq_cfi_r %rsi;               \
	popq_cfi_r %rdi

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_MSABI64_H */
