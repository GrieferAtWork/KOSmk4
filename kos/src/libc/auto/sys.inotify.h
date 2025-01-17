/* HASH CRC-32:0x870e80dc */
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
#ifndef GUARD_LIBC_AUTO_SYS_INOTIFY_H
#define GUARD_LIBC_AUTO_SYS_INOTIFY_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/inotify.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inotify_init1(2)
 * @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
INTDEF fd_t NOTHROW_NCX(LIBDCALL libd_inotify_init1)(__STDC_INT_AS_UINT_T flags);
/* >> inotify_rm_watch(2)
 * @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_inotify_rm_watch)(fd_t notify_fd, __watchfd_t wd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_INOTIFY_H */
