/* HASH CRC-32:0xf15d6903 */
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
#ifndef GUARD_LIBC_AUTO_MNTENT_H
#define GUARD_LIBC_AUTO_MNTENT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mntent.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Prepare to begin reading and/or writing mount table
 * entries from the beginning of FILE.  MODE is as for `fopen' */
INTDEF NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBDCALL libd_setmntent)(char const *file, char const *mode);
/* Read one mount table entry from STREAM.  Returns a pointer to storage
 * reused on the next call, or null for EOF or error (use feof/ferror to check) */
INTDEF NONNULL((1)) struct mntent *NOTHROW_RPC(LIBDCALL libd_getmntent)(FILE *stream);
/* Reentrant version of the above function */
INTDEF NONNULL((1, 2, 3)) struct mntent *NOTHROW_RPC(LIBDCALL libd_getmntent_r)(FILE *__restrict stream, struct mntent *__restrict result, char *__restrict buffer, __STDC_INT_AS_SIZE_T bufsize);
/* Write the mount table entry described by MNT to STREAM.
 * Return zero on success, nonzero on failure */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_addmntent)(FILE *__restrict stream, struct mntent const *__restrict mnt);
/* Close a stream opened with `setmntent' */
INTDEF NONNULL((1)) int NOTHROW_RPC_NOKOS(LIBDCALL libd_endmntent)(FILE *stream);
/* Search MNT->mnt_opts for an option matching OPT.
 * Returns the address of the substring, or null if none found */
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBDCALL libd_hasmntopt)(struct mntent const *mnt, char const *opt);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Search MNT->mnt_opts for an option matching OPT.
 * Returns the address of the substring, or null if none found */
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBCCALL libc_hasmntopt)(struct mntent const *mnt, char const *opt);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MNTENT_H */
