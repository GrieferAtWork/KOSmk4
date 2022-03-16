/* HASH CRC-32:0xd4fab1f9 */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WDIRECT_C
#define GUARD_LIBC_AUTO_CORECRT_WDIRECT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "corecrt_wdirect.h"
#include "parts.wchar.stdlib.h"
#include "parts.wchar.sys.stat.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unsorted") char16_t *
NOTHROW_RPC(LIBDCALL libd__wgetdcwd)(int drive,
                                     char16_t *buf,
                                     size_t size) {
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {

		(void)libc_seterrno(EINVAL);



		return NULL;
	}
	return libd_wfrealpath4(__AT_FDDRIVE_CWD(drive), buf, size, 0);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.unsorted") char32_t *
NOTHROW_RPC(LIBKCALL libc__wgetdcwd)(int drive,
                                     char32_t *buf,
                                     size_t size) {
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {

		(void)libc_seterrno(EINVAL);



		return NULL;
	}
	return libc_wfrealpath4(__AT_FDDRIVE_CWD(drive), buf, size, 0);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd__wmkdir)(char16_t const *path) {
	return libd_wmkdir(path, 0755);
}
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc__wmkdir)(char32_t const *path) {
	return libc_wmkdir(path, 0755);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wgetdcwd_nolock, libd__wgetdcwd);
DEFINE_PUBLIC_ALIAS(DOS$_wgetdcwd, libd__wgetdcwd);
DEFINE_PUBLIC_ALIAS(_wgetdcwd, libc__wgetdcwd);
DEFINE_PUBLIC_ALIAS(DOS$_wmkdir, libd__wmkdir);
DEFINE_PUBLIC_ALIAS(_wmkdir, libc__wmkdir);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WDIRECT_C */
