/* HASH CRC-32:0x11bbcef8 */
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
#ifndef GUARD_LIBC_AUTO_FSTAB_H
#define GUARD_LIBC_AUTO_FSTAB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fstab.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getfsspec(3)
 * Find and return the fstab entry with `strcmp(ent->fs_spec, special_file) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `special_file'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `special_file'
 * @return: NULL: [errno = *] Error */
INTDEF WUNUSED ATTR_IN(1) struct fstab *NOTHROW_NCX(LIBDCALL libd_getfsspec)(const char *special_file);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getfsspec(3)
 * Find and return the fstab entry with `strcmp(ent->fs_spec, special_file) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `special_file'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `special_file'
 * @return: NULL: [errno = *] Error */
INTDEF WUNUSED ATTR_IN(1) struct fstab *NOTHROW_NCX(LIBCCALL libc_getfsspec)(const char *special_file);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getfsfile(3)
 * Find and return the fstab entry with `strcmp(ent->fs_file, mount_point) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `mount_point'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `mount_point'
 * @return: NULL: [errno = *] Error */
INTDEF WUNUSED ATTR_IN(1) struct fstab *NOTHROW_NCX(LIBDCALL libd_getfsfile)(const char *mount_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getfsfile(3)
 * Find and return the fstab entry with `strcmp(ent->fs_file, mount_point) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `mount_point'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `mount_point'
 * @return: NULL: [errno = *] Error */
INTDEF WUNUSED ATTR_IN(1) struct fstab *NOTHROW_NCX(LIBCCALL libc_getfsfile)(const char *mount_point);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FSTAB_H */
