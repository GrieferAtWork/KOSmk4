/* HASH CRC-32:0x495516c2 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_STATFS_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_STATFS_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.statfs.h"

DECL_BEGIN

/* Return information about the filesystem on which FILE resides */
INTERN ATTR_SECTION(".text.crt.dos.fs.statfs.statfs") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_statfs)(char const *file,
                                  struct statfs *buf) {
	return libc_statfs(file, buf);
}
/* Return information about the filesystem containing the file FILDES refers to */
INTERN ATTR_SECTION(".text.crt.dos.fs.statfs.statfs") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_fstatfs)(fd_t filedes,
                                   struct statfs *buf) {
	return libc_fstatfs(filedes, buf);
}
/* Return information about the filesystem on which FILE resides */
INTERN ATTR_SECTION(".text.crt.dos.fs.statfs.statfs") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_statfs64)(const char *file,
                                    struct statfs64 *buf) {
	return libc_statfs64(file, buf);
}
/* Return information about the filesystem containing the file FILDES refers to */
INTERN ATTR_SECTION(".text.crt.dos.fs.statfs.statfs") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_fstatfs64)(fd_t filedes,
                                     struct statfs64 *buf) {
	return libc_fstatfs64(filedes, buf);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__statfs, libd_statfs);
DEFINE_PUBLIC_ALIAS(DOS$statfs, libd_statfs);
DEFINE_PUBLIC_ALIAS(DOS$fstatfs, libd_fstatfs);
DEFINE_PUBLIC_ALIAS(DOS$statfs64, libd_statfs64);
DEFINE_PUBLIC_ALIAS(DOS$fstatfs64, libd_fstatfs64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_STATFS_C */
