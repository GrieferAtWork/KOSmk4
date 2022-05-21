/* HASH CRC-32:0xd4025b86 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
/* >> endmntent(3) */
INTDEF ATTR_ACCESS_RW(1) int NOTHROW_RPC_NOKOS(LIBDCALL libd_endmntent)(FILE *stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> endmntent(3) */
INTDEF ATTR_ACCESS_RW(1) int NOTHROW_RPC_NOKOS(LIBCCALL libc_endmntent)(FILE *stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getmntent(3), getmntent_r(3) */
INTDEF ATTR_ACCESS_RW(1) struct mntent *NOTHROW_RPC(LIBDCALL libd_getmntent)(FILE *stream);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getmntent(3), getmntent_r(3) */
INTDEF ATTR_ACCESS_RW(1) struct mntent *NOTHROW_RPC(LIBCCALL libc_getmntent)(FILE *stream);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getmntent(3), getmntent_r(3) */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2, 3)) struct mntent *NOTHROW_RPC(LIBDCALL libd_getmntent_r)(FILE *__restrict stream, struct mntent *__restrict result, char *__restrict buffer, __STDC_INT_AS_SIZE_T bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getmntent(3), getmntent_r(3) */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2, 3)) struct mntent *NOTHROW_RPC(LIBCCALL libc_getmntent_r)(FILE *__restrict stream, struct mntent *__restrict result, char *__restrict buffer, __STDC_INT_AS_SIZE_T bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> addmntent(3)
 * Append a  line  `"%s %s %s %s %d %d\n"  %  (mnt_fsname,  mnt_dir,
 * mnt_type, mnt_opts, mnt_freq, mnt_passno)' to the end of `stream'
 * @return: 0: Success
 * @return: 1: Error (WARNING: `errno' is left undefined) */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) int (LIBDCALL libd_addmntent)(FILE *__restrict stream, struct mntent const *__restrict mnt) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> addmntent(3)
 * Append a  line  `"%s %s %s %s %d %d\n"  %  (mnt_fsname,  mnt_dir,
 * mnt_type, mnt_opts, mnt_freq, mnt_passno)' to the end of `stream'
 * @return: 0: Success
 * @return: 1: Error (WARNING: `errno' is left undefined) */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) int (LIBCCALL libc_addmntent)(FILE *__restrict stream, struct mntent const *__restrict mnt) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBDCALL libd_hasmntopt)(struct mntent const *mnt, char const *opt);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBCCALL libc_hasmntopt)(struct mntent const *mnt, char const *opt);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MNTENT_H */
