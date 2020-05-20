/* HASH CRC-32:0x76bfbdad */
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
#ifndef GUARD_LIBC_USER_SYS_MOUNT_H
#define GUARD_LIBC_USER_SYS_MOUNT_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/mount.h>

DECL_BEGIN

INTDEF int NOTHROW_RPC(LIBCCALL libc_mount)(char const *special_file, char const *dir, char const *fstype, unsigned long int mountflags, void const *data);
INTDEF int NOTHROW_RPC(LIBCCALL libc_umount)(char const *special_file);
INTDEF int NOTHROW_RPC(LIBCCALL libc_umount2)(char const *special_file, int flags);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MOUNT_H */
