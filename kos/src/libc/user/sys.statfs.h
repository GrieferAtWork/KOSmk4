/* HASH CRC-32:0x7f83b51 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_STATFS_H
#define GUARD_LIBC_USER_SYS_STATFS_H 1

#include "../api.h"
#include "../auto/sys.statfs.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/statfs.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_statfs)(char const *file, struct statfs *buf);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_fstatfs)(fd_t filedes, struct statfs *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_statfs64)(const char *file, struct statfs64 *buf);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_fstatfs64)(fd_t filedes, struct statfs64 *buf);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STATFS_H */
