/* HASH CRC-32:0x54f6bb87 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_DIRECT_C
#define GUARD_LIBC_AUTO_DOSABI_DIRECT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/direct.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.fs.property") char *
NOTHROW_RPC(LIBDCALL libd__getdcwd)(int drive,
                                    char *buf,
                                    size_t size) {
	return libc__getdcwd(drive, buf, size);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.property") int
NOTHROW_RPC(LIBDCALL libd__chdrive)(int drive) {
	return libc__chdrive(drive);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.property") unsigned int
NOTHROW_RPC(LIBDCALL libd__getdiskfree)(unsigned int drive,
                                        struct _diskfree_t *diskfree) {
	return libc__getdiskfree(drive, diskfree);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd__mkdir)(char const *path) {
	return libc__mkdir(path);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$_getdcwd, libd__getdcwd);
DEFINE_PUBLIC_ALIAS(DOS$_chdrive, libd__chdrive);
DEFINE_PUBLIC_ALIAS(DOS$_getdiskfree, libd__getdiskfree);
DEFINE_PUBLIC_ALIAS(DOS$_mkdir, libd__mkdir);

#endif /* !GUARD_LIBC_AUTO_DOSABI_DIRECT_C */
