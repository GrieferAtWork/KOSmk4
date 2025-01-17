/* HASH CRC-32:0x2cad3614 */
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
#ifndef GUARD_LIBC_USER_UCONTEXT_H
#define GUARD_LIBC_USER_UCONTEXT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ucontext.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> getcontext(3)
 * Save the caller's current register  state into the given  `ucp'
 * Usually, this function will never  fail and always return  `0'.
 * However on architectures where this function isn't implemented,
 * it will always returns `-1' with `errno=ENOSYS'
 * NOTE: If  it is known  at compile-time that  this function will always
 *       succeed,  and never return with an ENOSYS error, then KOS system
 *       headers will define a macro `__CRT_SUPPORTS_UCONTEXT', which you
 *       may test for, and which allows you to omit error-checks for this
 *       function.
 * WARNING: If the context returned by  this function is loaded after  the
 *          calling function has returned, then the behavior is undefined. */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_getcontext)(ucontext_t *__restrict ucp);
/* >> setcontext(3)
 * Populate the current machine register state with values from `ucp',
 * such  that this  function will not  return to the  caller, but will
 * instead  return to the  machine context that  is described by `ucp'
 * The caller must have previously initialized `ucp' by either:
 *   - A call to `getcontext(3)'
 *   - A call to `swapcontext(3)' where `ucp' was the `oucp' argument
 *   - A call to `makecontext(3)'
 *   - By manually  filling  in  required structure  fields.  Note  however
 *     that this method  of initializting a  `ucontext_t' is  non-portable,
 *     not only between different architectures, but also between different
 *     C  libraries,  or even  different versions  of  the same  C library,
 *     as  the layout, meaning, and names of fields are never standardized.
 * NOTE: Unless  this function is  not implemented by  the hosting libc (in
 *       which case `-1' is returned, and `errno' is set to `ENOSYS'), this
 *       function will never return normally (since execution will  instead
 *       continue at the location pointed-to by `ucp')
 * NOTE: If  it is known  at compile-time that  this function will always
 *       succeed,  and never return with an ENOSYS error, then KOS system
 *       headers will define a macro `__CRT_SUPPORTS_UCONTEXT', which you
 *       may test for, and which allows you to omit error-checks for this
 *       function. */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_setcontext)(ucontext_t const *__restrict ucp);
/* >> swapcontext(3)
 * Atomically perform both a `getcontext(oucp)',  as well as a  `setcontext(ucp)',
 * such that execution will  continue at `ucp',  but code that  is hosted by  that
 * control path will be  able to resume execution  with the caller's control  path
 * by  a   call  to   one   of  `setcontext(OUCP)'   or   `swapcontext(..., OUCP)'
 * The given  `ucp' must  be  initialized the  same way  as  is also  required  by
 * `setcontext(3)',  and  this function  will  always return  `0'  (once execution
 * has  once  again been  loaded  from the  context  described by  `oucp'), unless
 * the linked libc doesn't implement this function (in which case `swapcontext(3)'
 * always returns `-1' with `errno' set to `ENOSYS'
 * NOTE: If  it is known  at compile-time that  this function will always
 *       succeed,  and never return with an ENOSYS error, then KOS system
 *       headers will define a macro `__CRT_SUPPORTS_UCONTEXT', which you
 *       may test for, and which allows you to omit error-checks for this
 *       function. */
INTDEF ATTR_IN(2) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_swapcontext)(ucontext_t *__restrict oucp, ucontext_t const *__restrict ucp);
/* >> makecontext(3)
 * Initialize  a  user-context  `ucp'  to  perform  a  call  to  `func',  which
 * should take exactly `argc' arguments  of integer or pointer type  (floating-
 * point,  or  by-value  struct-arguments   cannot  be  accepted  by   `func').
 * Note  that  officially, arguments  taken by  `func' must  be of  type `int',
 * and  you're  not even  allowed to  pass pointer  arguments. However,  as far
 * as  doing so is  possible for the targeted  architecture, this function will
 * also  permit the use  of pointer-sized arguments  to-be forwarded to `func'.
 * Though if you want to be fully portable and compliant with POSIX, you should
 * check the relation  between `__SIZEOF_INT__'  and `__SIZEOF_POINTER__',  and
 * use macros  to pass  a variable  number of  int-arguments that  make up  the
 * different parts  of  a  full pointer,  before  re-constructing  the  pointer
 * argument inside of `func'.
 * Before using this function, the caller must:
 *   - Fill in `ucp->uc_stack.ss_sp' and `ucp->uc_stack.ss_size' to
 *     point  to  the  stack  on  which  `func'  will  be  executed
 *   - Have `ucp->uc_link' point to the context that should be  loaded
 *     when `func' returns normally, or set to `NULL' if the return of
 *     `func' should be handled as a call to `pthread_exit(NULL)' */
INTDEF ATTR_OUT(1) NONNULL((2)) void NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp, void (LIBKCALL *func)(void), __STDC_INT_AS_SIZE_T argc, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_UCONTEXT_H */
