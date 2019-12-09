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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_S
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_S 1

#include <kernel/compiler.h>

#include <kernel/paging.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/jccN.h>

.section .text

#define RELOAD_WITH_CR3_TEXTSIZE 7  /* == sizeof(x86_pagedir_syncall_cr3_text) */
#define RELOAD_WITH_CR4_TEXTSIZE 16 /* == sizeof(x86_pagedir_syncall_cr4_text) */

#define PAD_FOR(start, size) \
	.if size > (.- start);   \
	.skip size - (.- start); \
	.endif;



/* Same as `pagedir_syncall()', but also ensures that
 * all of kernel-space is synced. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void); */
PUBLIC_FUNCTION(pagedir_syncall)
	.cfi_startproc
	movq   $(2), %rax
	invpcid 1f, %rax
	ret
1:	.long 0x00000000, 0x00000000
	PAD_FOR(pagedir_syncall, RELOAD_WITH_CR3_TEXTSIZE)
	PAD_FOR(pagedir_syncall, RELOAD_WITH_CR4_TEXTSIZE)
	.cfi_endproc
END(pagedir_syncall)

/* Hybrid of `pagedir_syncall()' and `pagedir_syncall_user()': When the given range
 * overlaps with kernel-space, behave the same as `pagedir_syncall()', otherwise,
 * behave the same as `pagedir_syncall_user()' */
/* FUNDEF NOBLOCK void NOTHROW(FCALL x86_pagedir_syncall_maybe_global)(VIRT vm_virt_t virt_addr, size_t num_pages); */
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
	ret
	PAD_FOR(x86_pagedir_syncall_maybe_global, RELOAD_WITH_CR3_TEXTSIZE)
	.cfi_endproc
END(x86_pagedir_syncall_maybe_global)



/* X86-specific implementation for invalidating every TLB over a given range. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL x86_pagedir_sync)(VIRT vm_virt_t virt_addr, size_t num_pages); */
PUBLIC_FUNCTION(x86_pagedir_sync)
	.cfi_startproc
	cmpq   $(CONFIG_PAGEDIR_LARGESYNC_THRESHOLD), %rsi
	jae8   x86_pagedir_syncall_maybe_global
	movq   %rdi, %rax
	movq   %rsi, %rdi
	testq  %rdi, %rdi
	jz8    2f
1:	invlpg (%rax)
	addq   $(4096), %rax
	loop   1b
2:	ret
	.cfi_endproc
END(x86_pagedir_sync)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_S */
