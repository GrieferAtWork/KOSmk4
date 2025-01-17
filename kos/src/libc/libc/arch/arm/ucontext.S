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
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_UCONTEXT_S
#define GUARD_LIBC_LIBC_ARCH_ARM_UCONTEXT_S 1
#define __ASSEMBLER__ 1

#include "../../../api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/arm.h>
#include <cfi.h>
/**/


/* INTERN NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_getcontext)(ucontext_t *__restrict ucp); */
.section ".text.crt.cpu.ucontext"
INTERN_FUNCTION(libc_getcontext)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_getcontext)
DEFINE_PUBLIC_ALIAS(getcontext, libc_getcontext)



.section ".text.crt.cpu.ucontext"
INTERN_FUNCTION(libc_swapcontext)
	.cfi_startproc simple
	b      . /* TODO */
	.cfi_endproc
END(libc_swapcontext)
DEFINE_PUBLIC_ALIAS(swapcontext, libc_swapcontext)


/* INTERN NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setcontext)(ucontext_t const *__restrict ucp); */
.section ".text.crt.cpu.ucontext"
INTERN_FUNCTION(libc_setcontext)
	.cfi_startproc simple
	b      . /* TODO */
	.cfi_endproc
END(libc_setcontext)
DEFINE_PUBLIC_ALIAS(setcontext, libc_setcontext)




.section ".text.crt.cpu.ucontext"
	nop /* For unwinding... */
INTERN_FUNCTION(libc_makecontext_exit_thread)
	/* No CFI annotation, because we don't return! */
	b      . /* TODO */
END(libc_makecontext_exit_thread)



#endif /* GUARD_LIBC_LIBC_ARCH_ARM_UCONTEXT_S */
