/* HASH CRC-32:0x9a083a1a */
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
#ifndef GUARD_LIBC_AUTO_DIRECT_C
#define GUARD_LIBC_AUTO_DIRECT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/direct.h"
#include "../user/ctype.h"
#include "../user/stdlib.h"
#include "../user/sys.stat.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") char *
NOTHROW_RPC(LIBDCALL libd__getdcwd)(int drive,
                                    char *buf,
                                    size_t size) {
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {

		(void)libc_seterrno(EINVAL);



		return NULL;
	}
	return libd_frealpath4(__AT_FDDRIVE_CWD(drive), buf, size, 0);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.property") char *
NOTHROW_RPC(LIBCCALL libc__getdcwd)(int drive,
                                    char *buf,
                                    size_t size) {
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {

		(void)libc_seterrno(EINVAL);



		return NULL;
	}
	return libc_frealpath4(__AT_FDDRIVE_CWD(drive), buf, size, 0);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.property") int
NOTHROW_RPC(LIBCCALL libc__chdrive)(int drive) {
	drive = libc_toupper((unsigned char)drive);
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {

		return libc_seterrno(EINVAL);



	}
	return libc_fchdir(__AT_FDDRIVE_ROOT(drive));
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd__mkdir)(char const *path) {
	return libd_mkdir(path, 0755);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc__mkdir)(char const *path) {
	return libc_mkdir(path, 0755);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_getdcwd_nolock, libd__getdcwd);
DEFINE_PUBLIC_ALIAS(DOS$_getdcwd, libd__getdcwd);
DEFINE_PUBLIC_ALIAS(_getdcwd, libc__getdcwd);
DEFINE_PUBLIC_ALIAS(_chdrive, libc__chdrive);
DEFINE_PUBLIC_ALIAS(DOS$_mkdir, libd__mkdir);
DEFINE_PUBLIC_ALIAS(_mkdir, libc__mkdir);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_DIRECT_C */
