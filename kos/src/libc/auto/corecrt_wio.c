/* HASH CRC-32:0xe77d233d */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WIO_C
#define GUARD_LIBC_AUTO_CORECRT_WIO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/corecrt_wio.h"
#include "parts.wchar.fcntl.h"
#include "parts.wchar.unistd.h"
#include "../user/stdlib.h"
#include "string.h"
#include "uchar.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED ATTR_IN(1) errno_t
NOTHROW_RPC(LIBDCALL libd__waccess_s)(char16_t const *file,
                                      __STDC_INT_AS_UINT_T type) {
	if (libd_waccess(file, type) != 0)
		return __libd_geterrno_or(1);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED ATTR_IN(1) errno_t
NOTHROW_RPC(LIBKCALL libc__waccess_s)(char32_t const *file,
                                      __STDC_INT_AS_UINT_T type) {
	if (libc_waccess(file, type) != 0)
		return __libc_geterrno_or(1);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wmktemp_s)(char16_t *template_,
                                      size_t bufsize) {
	if (bufsize < 6)
		goto err_inval;
	template_ = libd__wmktemp(template_);
	if (!*template_)
		goto err_inval; /* ??? */
	return 0;
err_inval:

	return 22;



}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wmktemp_s)(char32_t *template_,
                                      size_t bufsize) {
	if (bufsize < 6)
		goto err_inval;
	template_ = libc__wmktemp(template_);
	if (!*template_)
		goto err_inval; /* ??? */
	return 0;
err_inval:

	return EINVAL;



}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_RETNONNULL ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__wmktemp)(char16_t *template_) {
	char *utf8_template, *rand;
	char16_t *rand_dst;
	size_t i;
	utf8_template = libd_convert_wcstombs(template_);
	if unlikely(!utf8_template)
		goto err;
	utf8_template = libc_mktemp(utf8_template);
	if (!*utf8_template)
		goto err_utf8_template;
	rand = libc_strend(utf8_template) - 6;
	rand_dst = libd_wcsend(template_) - 6;
	for (i = 0; i < 6; ++i)
		rand_dst[i] = (char16_t)(unsigned char)rand[i];

	libc_free(utf8_template);

	return template_;
err_utf8_template:

	libc_free(utf8_template);

err:
	*template_ = '\0';
	return template_;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_RETNONNULL ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__wmktemp)(char32_t *template_) {
	char *utf8_template, *rand;
	char32_t *rand_dst;
	size_t i;
	utf8_template = libc_convert_wcstombs(template_);
	if unlikely(!utf8_template)
		goto err;
	utf8_template = libc_mktemp(utf8_template);
	if (!*utf8_template)
		goto err_utf8_template;
	rand = libc_strend(utf8_template) - 6;
	rand_dst = libc_wcsend(template_) - 6;
	for (i = 0; i < 6; ++i)
		rand_dst[i] = (char32_t)(unsigned char)rand[i];

	libc_free(utf8_template);

	return template_;
err_utf8_template:

	libc_free(utf8_template);

err:
	*template_ = '\0';
	return template_;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") ATTR_IN(2) ATTR_OUT(1) errno_t
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
INTERN ATTR_SECTION(".text.crt.dos.fs.io") ATTR_IN(2) ATTR_OUT(1) errno_t
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t
NOTHROW_RPC(LIBDCALL libd__wsopen_dispatch)(char16_t const *filename,
                                            oflag_t oflags,
                                            int sflags,
                                            mode_t mode,
                                            fd_t *fd,
                                            int bsecure) {
	(void)bsecure;
	return libd__wsopen_s(fd, filename, oflags, sflags, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t
NOTHROW_RPC(LIBKCALL libc__wsopen_dispatch)(char32_t const *filename,
                                            oflag_t oflags,
                                            int sflags,
                                            mode_t mode,
                                            fd_t *fd,
                                            int bsecure) {
	(void)bsecure;
	return libc__wsopen_s(fd, filename, oflags, sflags, mode);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED ATTR_IN(1) fd_t
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
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.io") WUNUSED ATTR_IN(1) fd_t
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
DEFINE_PUBLIC_ALIAS(DOS$_wmktemp_s, libd__wmktemp_s);
DEFINE_PUBLIC_ALIAS(_wmktemp_s, libc__wmktemp_s);
DEFINE_PUBLIC_ALIAS(DOS$_wmktemp, libd__wmktemp);
DEFINE_PUBLIC_ALIAS(_wmktemp, libc__wmktemp);
DEFINE_PUBLIC_ALIAS(DOS$_wsopen_s, libd__wsopen_s);
DEFINE_PUBLIC_ALIAS(_wsopen_s, libc__wsopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_wsopen_dispatch, libd__wsopen_dispatch);
DEFINE_PUBLIC_ALIAS(_wsopen_dispatch, libc__wsopen_dispatch);
DEFINE_PUBLIC_ALIAS("?_wsopen@@YAHPB_WHHH@Z", libd__wsopen);
DEFINE_PUBLIC_ALIAS(DOS$_wsopen, libd__wsopen);
DEFINE_PUBLIC_ALIAS(_wsopen, libc__wsopen);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WIO_C */
