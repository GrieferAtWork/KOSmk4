/* HASH CRC-32:0x3f246e15 */
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
#ifndef GUARD_LIBC_AUTO_UCONTEXT_H
#define GUARD_LIBC_AUTO_UCONTEXT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ucontext.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Save the caller's current register state into the given `UCP'
 * Usually, this function will never fail and always return `0'.
 * However on architectures where this function isn't implemented,
 * it will always returns `-1' with `errno=ENOSYS'
 * NOTE: If it is known at compile-time that this function will always
 *       succeed, and never return with an ENOSYS error, then KOS system
 *       headers will define a macro `__CRT_SUPPORTS_UCONTEXT', which you
 *       may test for, and which allows you to omit error-checks for this
 *       function. */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_getcontext)(ucontext_t *__restrict ucp);
/* Populate the current machine register state with values from `UCP',
 * that that this function will not return to the caller, but will instead
 * return to the machine context that is described by `UCP'
 * The caller must have previously initialized `UCP' by either:
 *   - A call to `getcontext(3)'
 *   - A call to `swapcontext(3)' where `UCP' was the `OUCP' argument
 *   - A call to `makecontext(3)'
 *   - By manually filling in required structure fields. Note however
 *     that this method of initializting a `ucontext_t' is non-portable,
 *     not only between different architectures, but also between different
 *     C libraries, or even different versions of the same C library,
 *     as the layout, meaning, and names of fields are never standardized.
 * NOTE: Unless this function is not implemented by the hosting libc (in
 *       which case `-1' is returned, and `errno' is set to `ENOSYS'), this
 *       function will never return normally (since execution will instead
 *       continue at the location pointed-to by `UCP')
 * NOTE: If it is known at compile-time that this function will always
 *       succeed, and never return with an ENOSYS error, then KOS system
 *       headers will define a macro `__CRT_SUPPORTS_UCONTEXT', which you
 *       may test for, and which allows you to omit error-checks for this
 *       function. */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_setcontext)(ucontext_t const *__restrict ucp);
/* Atomically perform both a `getcontext(oucp)', as well as a `setcontext(ucp)',
 * such that execution will continue at `ucp', but code that is hosted by that
 * control path will be able to resume execution with the caller's control path
 * by a call to one of `setcontext(OUCP)' or `swapcontext(..., OUCP)'
 * The given `UCP' must be initialized the same way as is also required by
 * `setcontext(3)', and this function will always return `0' (once execution
 * has once again been loaded from the context described by `oucp'), unless
 * the linked libc doesn't implement this function (in which case `swapcontext(3)'
 * always returns `-1' with `errno' set to `ENOSYS'
 * NOTE: If it is known at compile-time that this function will always
 *       succeed, and never return with an ENOSYS error, then KOS system
 *       headers will define a macro `__CRT_SUPPORTS_UCONTEXT', which you
 *       may test for, and which allows you to omit error-checks for this
 *       function. */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_swapcontext)(ucontext_t *__restrict oucp, ucontext_t const *__restrict ucp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UCONTEXT_H */
