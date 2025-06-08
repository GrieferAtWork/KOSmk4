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
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_SETJMP_S
#define GUARD_LIBC_LIBC_ARCH_ARM_SETJMP_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/arm.h>

#include <setjmp.h>
#include <signal.h>

#undef setjmp
#undef longjmp

.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_setjmp)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_setjmp)
DEFINE_PUBLIC_ALIAS(setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(_setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(__setjmp, libc_setjmp)
DEFINE_PUBLIC_ALIAS(_setjmp3, libc_setjmp)


.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_longjmp)
	.cfi_startproc
	.cfi_signal_frame__entry
	cmp    r1, #0 /* if (sig == 0) */
	moveq  r1, #1 /*     sig = 1; */
INTERN_FUNCTION(libc___fast_longjmp)
	b      . /* TODO */
	.cfi_endproc
END(libc___fast_longjmp)
END(libc_longjmp)
DEFINE_PUBLIC_ALIAS(longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(_longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(__longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(__libc_longjmp, libc_longjmp)
DEFINE_PUBLIC_ALIAS(__fast_longjmp, libc___fast_longjmp)



.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc__setjmpex)
	.cfi_startproc
	mov    r1, 1 /* savemask = true */
INTERN_FUNCTION(libc_sigsetjmp)
	b      . /* TODO */
	.cfi_endproc
END(libc_sigsetjmp)
END(libc__setjmpex)

DEFINE_PUBLIC_ALIAS(_setjmpex, libc__setjmpex)
DEFINE_PUBLIC_ALIAS(sigsetjmp, libc_sigsetjmp)
DEFINE_PUBLIC_ALIAS(__sigsetjmp, libc_sigsetjmp)
DEFINE_PUBLIC_ALIAS(__libc_siglongjmp, libc_sigsetjmp)

.section .text.crt.utility.setjmp
INTERN_FUNCTION(libc_siglongjmp)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_siglongjmp)

DEFINE_PUBLIC_ALIAS(siglongjmp, libc_siglongjmp)
DEFINE_PUBLIC_ALIAS(__siglongjmp, libc_siglongjmp)

#endif /* !GUARD_LIBC_LIBC_ARCH_ARM_SETJMP_S */
