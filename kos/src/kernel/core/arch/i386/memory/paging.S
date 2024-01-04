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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING_S
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/paging.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/jccN.h>

#define PAD_FOR(start, size) \
	.if size > (.- start);   \
	.skip size - (.- start); \
	.endif;

.section .rodata.free
INTERN_FUNCTION(x86_pagedir_syncall_cr3)
	movP %cr3, %Pax
	movP %Pax, %cr3
	/* --- TLB reload happens here */
	ret
INTERN_CONST(x86_pagedir_syncall_cr3_size, . - x86_pagedir_syncall_cr3)
END(x86_pagedir_syncall_cr3)

.section .rodata.free
INTERN_FUNCTION(x86_pagedir_syncall_cr4)
	pushfP
	cli
	movP   %cr4, %Pax
	leaP   -CR4_PGE(%Pax), %Pcx
	movP   %Pcx, %cr4
	/* --- TLB reload happens here */
	movP   %Pax, %cr4
	popfP
	ret
INTERN_CONST(x86_pagedir_syncall_cr4_size, . - x86_pagedir_syncall_cr4)
END(x86_pagedir_syncall_cr4)


/* Same as `pagedir_syncall()', but also ensures that
 * all of kernel-space is synced. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void); */
.section .text
PUBLIC_FUNCTION(pagedir_syncall)
	.cfi_startproc
	movP   $(2), %Pax
	invpcid 1f, %Pax
	/* --- TLB reload happens here */
	ret
1:	.long 0x00000000, 0x00000000
	PAD_FOR(pagedir_syncall, x86_pagedir_syncall_cr3_size)
	PAD_FOR(pagedir_syncall, x86_pagedir_syncall_cr4_size)
	.cfi_endproc
END(pagedir_syncall)


/* Hybrid of `pagedir_syncall()' and `pagedir_syncall_user()': When the given range
 * overlaps with kernel-space, behave  the same as `pagedir_syncall()',  otherwise,
 * behave the same as `pagedir_syncall_user()' */
/* >> FUNDEF NOBLOCK void
 * >> NOTHROW(FCALL x86_pagedir_syncall_maybe_global)(PAGEDIR_PAGEALIGNED VIRT void *addr,
 * >>                                                 PAGEDIR_PAGEALIGNED size_t num_bytes); */
.section .text
PUBLIC_FUNCTION(x86_pagedir_syncall_maybe_global)
	.cfi_startproc
	addP   %R_fcall1P, %R_fcall0P
	jo8    pagedir_syncall /* sync up until, or past the end of the address space. */
#ifdef __x86_64__
	cmpP   $(0), %R_fcall0P
	jl8    pagedir_syncall
#else /* __x86_64__ */
	cmpl   $(KERNELSPACE_BASE), %R_fcall0P
	ja8    pagedir_syncall
#endif /* !__x86_64__ */
	/* Only invalidate user-space. */
	movP   %cr3, %Pax
	movP   %Pax, %cr3
	/* --- TLB reload happens here */
	ret
	PAD_FOR(x86_pagedir_syncall_maybe_global, x86_pagedir_syncall_cr3_size)
	.cfi_endproc
END(x86_pagedir_syncall_maybe_global)




/* In 64-bit mode, presence of `invlpg' can be assumed, so no need to
 * define a dedicated subroutine which may get rewritten in case that
 * instruction wasn't supported */
#ifndef __x86_64__
/* X86-specific implementation for invalidating the TLB of a single page. */
/* FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone)(VIRT void *addr); */
.section .text
PUBLIC_FUNCTION(pagedir_syncone)
	.cfi_startproc
	invlpg (%R_fcall0P)
	/* --- TLB reload happens here */
	ret
	PAD_FOR(pagedir_syncone, x86_pagedir_syncall_cr3_size)
	PAD_FOR(pagedir_syncone, x86_pagedir_syncall_cr4_size)
	.cfi_endproc
END(pagedir_syncone)
#endif /* !__x86_64__ */



/* X86-specific implementation for invalidating every TLB over a given range. */
/* >> FUNDEF NOBLOCK void
 * >> NOTHROW(FCALL pagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
 * >>                             PAGEDIR_PAGEALIGNED size_t num_bytes); */
.section .text
PUBLIC_FUNCTION(pagedir_sync)
	.cfi_startproc
	cmpP   $(ARCH_PAGEDIR_LARGESYNC_THRESHOLD), %R_fcall1P
	jae8   x86_pagedir_syncall_maybe_global
#ifdef __x86_64__
	shrP   $(12), %R_fcall1P
	testP  %R_fcall1P, %R_fcall1P
#else /* __x86_64__ */
	movP   %R_fcall0P, %Pax
	movP   %R_fcall1P, %Pcx
	shrP   $(12), %Pcx
	testP  %Pcx, %Pcx
#endif /* !__x86_64__ */
	jz8    2f
#ifdef __x86_64__
	movP   %R_fcall1P, %Pcx
#endif /* __x86_64__ */

1:	/* Main loop */
#ifdef __x86_64__
	invlpg (%R_fcall0P)
	/* --- TLB reload happens here */
	addP   $(PAGESIZE), %R_fcall0P
#else /* __x86_64__ */
	invlpg (%Pax)
	/* --- TLB reload happens here */
	addP   $(PAGESIZE), %Pax
#endif /* !__x86_64__ */
	loop   1b

2:	ret
#ifndef __x86_64__
	PAD_FOR(pagedir_sync, x86_pagedir_syncall_cr3_size)
	PAD_FOR(pagedir_sync, x86_pagedir_syncall_cr4_size)
#endif /* !__x86_64__ */
	.cfi_endproc
END(pagedir_sync)



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING_S */
