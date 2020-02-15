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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_S
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_S 1

#include <kernel/compiler.h>

#include <kernel/paging.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/jccN.h>

.section .text

#define PAD_FOR(start, size) \
	.if size > (.- start);   \
	.skip size - (.- start); \
	.endif;


.section .rodata.free
INTERN_FUNCTION(x86_pagedir_syncall_cr3)
	movl %cr3, %eax
	movl %eax, %cr3
	/* --- TLB reload happens here */
	ret
INTERN_CONST(x86_pagedir_syncall_cr3_size, . - x86_pagedir_syncall_cr3)
END(x86_pagedir_syncall_cr3)

.section .rodata.free
INTERN_FUNCTION(x86_pagedir_syncall_cr4)
	pushfl
	cli
	movl   %cr4, %eax
	leal   -CR4_PGE(%eax), %ecx
	movl   %ecx, %cr4
	/* --- TLB reload happens here */
	movl   %eax, %cr4
	popfl
	ret
INTERN_CONST(x86_pagedir_syncall_cr4_size, . - x86_pagedir_syncall_cr4)
END(x86_pagedir_syncall_cr4)





/* Same as `pagedir_syncall()', but also ensures that
 * all of kernel-space is synced. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void); */
PUBLIC_FUNCTION(pagedir_syncall)
	.cfi_startproc
	movl   $(2), %eax
	invpcid 1f, %eax
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
 * >> NOTHROW(FCALL x86_pagedir_syncall_maybe_global)(PAGEDIR_PAGEALIGNED VIRT void *addr,
 * >>                                                 PAGEDIR_PAGEALIGNED size_t num_bytes); */
PUBLIC_FUNCTION(x86_pagedir_syncall_maybe_global)
	.cfi_startproc
	addl   %edx, %ecx
	jo8    pagedir_syncall /* sync up until, or past the end of the address space. */
	cmpl   $(KERNELSPACE_BASE), %ecx
	ja8    pagedir_syncall
	/* Only invalidate user-space. */
	movl   %cr3, %eax
	movl   %eax, %cr3
	/* --- TLB reload happens here */
	ret
	PAD_FOR(x86_pagedir_syncall_maybe_global, x86_pagedir_syncall_cr3_size)
	.cfi_endproc
END(x86_pagedir_syncall_maybe_global)


/* X86-specific implementation for invalidating the TLB of a single page. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone)(VIRT void *addr); */
PUBLIC_FUNCTION(pagedir_syncone)
	.cfi_startproc
	invlpg (%ecx)
	/* --- TLB reload happens here */
	ret
	PAD_FOR(pagedir_syncone, x86_pagedir_syncall_cr3_size)
	PAD_FOR(pagedir_syncone, x86_pagedir_syncall_cr4_size)
	.cfi_endproc
END(pagedir_syncone)


/* X86-specific implementation for invalidating every TLB over a given range. */
/* >> FUNDEF NOBLOCK void
 * >> NOTHROW(FCALL pagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
 * >>                             PAGEDIR_PAGEALIGNED size_t num_bytes); */
PUBLIC_FUNCTION(pagedir_sync)
	.cfi_startproc
	cmpl   $(CONFIG_PAGEDIR_LARGESYNC_THRESHOLD * 4096), %edx
	jae8   x86_pagedir_syncall_maybe_global
	movl   %ecx, %eax
	movl   %edx, %ecx
	shrl   $(12), %ecx
	testl  %ecx, %ecx
	jz8    2f
1:	invlpg (%eax)
	/* --- TLB reload happens here */
	addl   $(4096), %eax
	loop   1b
2:	ret
	PAD_FOR(pagedir_sync, x86_pagedir_syncall_cr3_size)
	PAD_FOR(pagedir_sync, x86_pagedir_syncall_cr4_size)
	.cfi_endproc
END(pagedir_sync)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_S */
