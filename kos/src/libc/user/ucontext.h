/* HASH 0x6196b423 */
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
#ifndef GUARD_LIBC_USER_UCONTEXT_H
#define GUARD_LIBC_USER_UCONTEXT_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ucontext.h>

DECL_BEGIN

/* Get user context and store it in variable pointed to by UCP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_getcontext)(ucontext_t *__restrict ucp);
/* Set user context from information of variable pointed to by UCP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setcontext)(ucontext_t const *__restrict ucp);
/* Save current context in context variable pointed to by OUCP and set
 * context from variable pointed to by UCP */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_swapcontext)(ucontext_t *__restrict oucp, ucontext_t const *__restrict ucp);
/* Manipulate user context UCP to continue with calling functions FUNC
 * and the ARGC-1 parameters following ARGC when the context is used
 * the next time in `setcontext' or `swapcontext'.
 * We cannot say anything about the parameters FUNC takes; `void'
 * is as good as any other choice */
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp, __makecontext_func_t func, int argc, ...);

DECL_END

#endif /* !GUARD_LIBC_USER_UCONTEXT_H */
