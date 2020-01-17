/* HASH CRC-32:0x238f94d3 */
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
#ifndef GUARD_LIBC_AUTO_SIGNAL_H
#define GUARD_LIBC_AUTO_SIGNAL_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <signal.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set, int signo);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set, int signo);
/* @param signo: One of `SIG*' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set, int signo);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *set);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SIGNAL_H */
