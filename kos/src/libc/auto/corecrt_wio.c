/* HASH CRC-32:0xc6366e7d */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WIO_C
#define GUARD_LIBC_AUTO_CORECRT_WIO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/corecrt_wio.h"
#include "parts.wchar.fcntl.h"
#include "../user/parts.wchar.unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED NONNULL((1)) errno_t
NOTHROW_RPC(LIBDCALL libd__waccess_s)(char16_t const *file,
                                      __STDC_INT_AS_UINT_T type) {
	if (libd_waccess(file, type) != 0)
		return __libd_geterrno_or(1);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED NONNULL((1)) errno_t
NOTHROW_RPC(LIBKCALL libc__waccess_s)(char32_t const *file,
                                      __STDC_INT_AS_UINT_T type) {
	if (libc_waccess(file, type) != 0)
		return __libc_geterrno_or(1);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBDCALL libd__wsopen_s)(fd_t *fd,
                                     char16_t const *filename,
                                     oflag_t oflags,
                                     int sflags,
                                     mode_t mode) {
	fd_t result;
	if (!fd) {

		return 22;



	}
	result = libd__wsopen(filename, oflags, sflags, mode);
	if (result < 0)
		return __libd_geterrno_or(1);
	*fd = result;
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBKCALL libc__wsopen_s)(fd_t *fd,
                                     char32_t const *filename,
                                     oflag_t oflags,
                                     int sflags,
                                     mode_t mode) {
	fd_t result;
	if (!fd) {

		return EINVAL;



	}
	result = libc__wsopen(filename, oflags, sflags, mode);
	if (result < 0)
		return __libc_geterrno_or(1);
	*fd = result;
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED NONNULL((1, 5)) errno_t
NOTHROW_RPC(LIBDCALL libd__wsopen_dispatch)(char16_t const *filename,
                                            oflag_t oflags,
                                            int sflags,
                                            mode_t mode,
                                            fd_t *fd,
                                            int bsecure) {
	(void)bsecure;
	return libd__wsopen_s(fd, filename, oflags, sflags, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED NONNULL((1, 5)) errno_t
NOTHROW_RPC(LIBKCALL libc__wsopen_dispatch)(char32_t const *filename,
                                            oflag_t oflags,
                                            int sflags,
                                            mode_t mode,
                                            fd_t *fd,
                                            int bsecure) {
	(void)bsecure;
	return libc__wsopen_s(fd, filename, oflags, sflags, mode);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(VLIBDCALL libd__wsopen)(char16_t const *filename,
                                    oflag_t oflags,
                                    int sflags,
                                    ...) {
	fd_t result;
	va_list args;
	va_start(args, sflags);
	(void)sflags;
	result = libd_wopen(filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(VLIBKCALL libc__wsopen)(char32_t const *filename,
                                    oflag_t oflags,
                                    int sflags,
                                    ...) {
	fd_t result;
	va_list args;
	va_start(args, sflags);
	(void)sflags;
	result = libc_wopen(filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_waccess_s, libd__waccess_s);
DEFINE_PUBLIC_ALIAS(_waccess_s, libc__waccess_s);
DEFINE_PUBLIC_ALIAS(DOS$_wsopen_s, libd__wsopen_s);
DEFINE_PUBLIC_ALIAS(_wsopen_s, libc__wsopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_wsopen_dispatch, libd__wsopen_dispatch);
DEFINE_PUBLIC_ALIAS(_wsopen_dispatch, libc__wsopen_dispatch);
DEFINE_PUBLIC_ALIAS("?_wsopen@@YAHPB_WHHH@Z", libd__wsopen);
DEFINE_PUBLIC_ALIAS(DOS$_wsopen, libd__wsopen);
DEFINE_PUBLIC_ALIAS(_wsopen, libc__wsopen);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WIO_C */
