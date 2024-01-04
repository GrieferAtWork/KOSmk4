/* HASH CRC-32:0xb4ba366b */
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
#ifndef GUARD_LIBC_AUTO_SYS_MOUNT_H
#define GUARD_LIBC_AUTO_SYS_MOUNT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/mount.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mount(2)
 * @param: mountflags: Set of `MS_*' from <sys/mount.h> */
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(5) int NOTHROW_RPC(LIBDCALL libd_mount)(char const *special_file, char const *dir, char const *fstype, ulongptr_t mountflags, void const *data);
/* >> umount(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_umount)(char const *special_file);
/* >> umount2(2)
 * @param: flags: Set of `MNT_FORCE | MNT_DETACH | MNT_EXPIRE | UMOUNT_NOFOLLOW' */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_umount2)(char const *special_file, __STDC_INT_AS_UINT_T flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_MOUNT_H */
