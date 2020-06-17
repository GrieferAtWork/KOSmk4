/* HASH CRC-32:0xcd58cd83 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_MOUNT_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_MOUNT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.mount.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.fs.mount") int
NOTHROW_RPC(LIBDCALL libd_mount)(char const *special_file,
                                 char const *dir,
                                 char const *fstype,
                                 ulongptr_t mountflags,
                                 void const *data) {
	return libc_mount(special_file, dir, fstype, mountflags, data);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.mount") int
NOTHROW_RPC(LIBDCALL libd_umount)(char const *special_file) {
	return libc_umount(special_file);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.mount") int
NOTHROW_RPC(LIBDCALL libd_umount2)(char const *special_file,
                                   __STDC_INT_AS_UINT_T flags) {
	return libc_umount2(special_file, flags);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$mount, libd_mount);
DEFINE_PUBLIC_ALIAS(DOS$umount, libd_umount);
DEFINE_PUBLIC_ALIAS(DOS$umount2, libd_umount2);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_MOUNT_C */
