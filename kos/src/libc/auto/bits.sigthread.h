/* HASH CRC-32:0x9e4e0504 */
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
#ifndef GUARD_LIBC_AUTO_BITS_SIGTHREAD_H
#define GUARD_LIBC_AUTO_BITS_SIGTHREAD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <bits/sigthread.h>

DECL_BEGIN

DECL_END
#include <pthread.h>
#include <bits/sigset.h>
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_pthread_sigmask)(__STDC_INT_AS_UINT_T how, sigset_t const *newmask, sigset_t *oldmask);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pthread_kill)(pthread_t threadid, signo_t signo);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pthread_sigqueue)(pthread_t threadid, signo_t signo, union sigval const value);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_BITS_SIGTHREAD_H */
