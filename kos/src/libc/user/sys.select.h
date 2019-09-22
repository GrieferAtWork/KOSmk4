/* HASH CRC-32:0xdb31ccb7 */
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
#ifndef GUARD_LIBC_USER_SYS_SELECT_H
#define GUARD_LIBC_USER_SYS_SELECT_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/select.h>

DECL_BEGIN

DECL_END
#include <bits/sigaction.h>
DECL_BEGIN

#ifndef __sighandler_t_defined
#define __sighandler_t_defined 1
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */

INTDEF __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_select)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timeval *__restrict timeout);
INTDEF __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_pselect)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timespec const *__restrict timeout, sigset_t const *__restrict sigmask);
INTDEF __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_select64)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timeval64 *__restrict timeout);
INTDEF __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_pselect64)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timespec64 const *__restrict timeout, sigset_t const *__restrict sigmask);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SELECT_H */
