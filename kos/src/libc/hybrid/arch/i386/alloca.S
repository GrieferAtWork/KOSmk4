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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_ALLOC_S
#define GUARD_LIBC_HYBRID_ARCH_I386_ALLOC_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/instr/compat.h>

#ifndef SIZEOF_POINTER
#include <hybrid/typecore.h>
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */


#undef alloca
#undef _alloca

.section .text.crt.utility
INTERN_FUNCTION(libc_alloca)
	.cfi_startproc
	popP_cfi %Pcx              /* return address */
	.cfi_register %Pip, %Pcx
#ifdef __x86_64__
	subP   %R_sysvabi0P, %Psp  /* Allocate stack memory */
#else /* __x86_64__ */
	subP   0(%Psp), %Psp       /* Allocate stack memory */
#endif /* !__x86_64__ */
.Lalloca_dos_join:
	andP   $(~(SIZEOF_POINTER - 1)), %Psp /* Re-align stack */
	.cfi_same_value %Psp
#ifdef __x86_64__
	movP   %Psp, %Pax          /* Return the new stack pointer in `%Pax' */
#else /* __x86_64__ */
	leaP   4(%Psp), %Pax       /* Must add 4 to return pointer because CDECL means
	                            * caller  still has to  free arguments from stack. */
#endif /* !__x86_64__ */
	jmpP   *%Pcx               /* Return to caller */
	.cfi_endproc
END(libc_alloca)

DEFINE_PUBLIC_ALIAS(alloca, libc_alloca)
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_alloca, libc_alloca)
#endif /* !__KERNEL__ */

#ifdef __x86_64__
#ifndef __KERNEL__
/* Need a different calling convention for DOS */

.section .text.crt.dos.utility
INTERN_FUNCTION(libd_alloca)
	.cfi_startproc
	popP_cfi %Pdx              /* return address */
	.cfi_register %Pip, %Pdx
	subP   %Pcx, %Psp          /* Allocate stack memory */
	jmp    .Lalloca_dos_join   /* Rest of the function is shared with `libc_alloca()' */
	.cfi_endproc
END(libd_alloca)

DEFINE_PUBLIC_ALIAS(DOS$alloca, libd_alloca)
DEFINE_PUBLIC_ALIAS(DOS$_alloca, libd_alloca)
#endif /* !__KERNEL__ */
#endif /* __x86_64__ */


#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_ALLOC_S */
