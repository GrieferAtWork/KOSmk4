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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_S
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_S 1

#include <kernel/compiler.h>

#include <kernel/paging.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/jccN.h>

#define PAD_FOR(start, size) \
	.if size > (.- start);   \
	.skip size - (.- start); \
	.endif;

.section .rodata.free
INTERN_FUNCTION(x86_pagedir_syncall_cr3)
	movq %cr3, %rax
	movq %rax, %cr3
	/* --- TLB reload happens here */
	ret
INTERN_CONST(x86_pagedir_syncall_cr3_size, . - x86_pagedir_syncall_cr3)
END(x86_pagedir_syncall_cr3)

.section .rodata.free
INTERN_FUNCTION(x86_pagedir_syncall_cr4)
	pushfq
	cli
	movq   %cr4, %rax
	leaq   -CR4_PGE(%rax), %rcx
	movq   %rcx, %cr4
	/* --- TLB reload happens here */
	movq   %rax, %cr4
	popfq
	ret
INTERN_CONST(x86_pagedir_syncall_cr4_size, . - x86_pagedir_syncall_cr4)
END(x86_pagedir_syncall_cr4)




/* Same as `pagedir_syncall()', but also ensures that
 * all of kernel-space is synced. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void); */
.section .text
PUBLIC_FUNCTION(pagedir_syncall)
	.cfi_startproc
	movq   $(2), %rax
	invpcid 1f, %rax
	/* --- TLB reload happens here */
	ret
1:	.long 0x00000000, 0x00000000
	PAD_FOR(pagedir_syncall, x86_pagedir_syncall_cr3_size)
	PAD_FOR(pagedir_syncall, x86_pagedir_syncall_cr4_size)
	.cfi_endproc
END(pagedir_syncall)

/* Hybrid of `pagedir_syncall()' and `pagedir_syncall_user()': When the given range
 * overlaps with kernel-space, behave the same as `pagedir_syncall()', otherwise,
 * behave the same as `pagedir_syncall_user()' */
/* >> FUNDEF NOBLOCK void
 * >> NOTHROW(FCALL x86_pagedir_syncall_maybe_global)(VIRT vm_virt_t virt_addr,
 * >>                                                 size_t num_pages); */
.section .text
PUBLIC_FUNCTION(x86_pagedir_syncall_maybe_global)
	.cfi_startproc
	shlq   $(12), %rsi
	addq   %rsi, %rdi
	jo8    pagedir_syncall /* sync up until, or past the end of the address space. */
	cmpq   $(0), %rdi
	jl8    pagedir_syncall
	/* Only invalidate user-space. */
	movq   %cr3, %rax
	movq   %rax, %cr3
	/* --- TLB reload happens here */
	ret
	PAD_FOR(x86_pagedir_syncall_maybe_global, x86_pagedir_syncall_cr3_size)
	.cfi_endproc
END(x86_pagedir_syncall_maybe_global)



/* X86-specific implementation for invalidating every TLB over a given range. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL x86_pagedir_sync)(VIRT vm_virt_t virt_addr, size_t num_pages); */
.section .text
PUBLIC_FUNCTION(x86_pagedir_sync)
	.cfi_startproc
	cmpq   $(CONFIG_PAGEDIR_LARGESYNC_THRESHOLD), %rsi
	jae8   x86_pagedir_syncall_maybe_global
	testq  %rsi, %rsi
	jz8    2f
	movq   %rsi, %rcx
1:	invlpg (%rdi)
	/* --- TLB reload happens here */
	addq   $(4096), %rdi
	loop   1b
2:	ret
	.cfi_endproc
END(x86_pagedir_sync)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_S */
