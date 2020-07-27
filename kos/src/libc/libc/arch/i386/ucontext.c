/* HASH CRC-32:0x8280fc89 */
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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_C
#define GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_C 1

#include "../../../api.h"
/**/

#include <hybrid/host.h>

#include <stdlib.h>
#include <ucontext.h>
#include <stdarg.h>
/**/

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(makecontext, libc_makecontext);
INTERN ATTR_SECTION(".text.crt.cpu.ucontext") NONNULL((1, 2)) void
NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp,
                                        __makecontext_func_t func,
                                        __STDC_INT_AS_SIZE_T argc,
                                        ...) {
#ifdef __x86_64__
	(void)ucp;
	(void)func;
	(void)argc;
	/* TODO */
	abort();
#else /* __x86_64__ */
	va_list args;
	va_start(args, argc);
	(void)ucp;
	(void)func;
	(void)argc;
	/* TODO */
	abort();
	va_end(args);
#endif /* !__x86_64__ */
}



DECL_END

#endif /* GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_C */
