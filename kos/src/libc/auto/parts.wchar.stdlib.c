/* HASH CRC-32:0x81093d6e */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.stdlib.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "uchar.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.system") int
NOTHROW_RPC(LIBDCALL libd_wsystem)(char16_t const *cmd) {
	int result;
	char *used_cmd;
	if (!cmd) {
		result = libc_system(NULL);
	} else {
		used_cmd = libd_convert_wcstombs(cmd);
		if unlikely(!used_cmd)
			return -1;
		result = libc_system(used_cmd);

		libc_free(used_cmd);

	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.system") int
NOTHROW_RPC(LIBKCALL libc_wsystem)(char32_t const *cmd) {
	int result;
	char *used_cmd;
	if (!cmd) {
		result = libc_system(NULL);
	} else {
		used_cmd = libc_convert_wcstombs(cmd);
		if unlikely(!used_cmd)
			return -1;
		result = libc_system(used_cmd);

		libc_free(used_cmd);

	}
	return result;
}
#include <asm/os/fcntl.h>
#include <asm/os/limits.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED NONNULL((1)) char16_t *
NOTHROW_RPC(LIBDCALL libd_wrealpath)(char16_t const *filename,
                                     char16_t *resolved) {




	return libd_wfrealpathat(__AT_FDCWD, filename, resolved, resolved ? 256 : 0, 0);













































}
#include <asm/os/fcntl.h>
#include <asm/os/limits.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") WUNUSED NONNULL((1)) char32_t *
NOTHROW_RPC(LIBKCALL libc_wrealpath)(char32_t const *filename,
                                     char32_t *resolved) {




	return libc_wfrealpathat(__AT_FDCWD, filename, resolved, resolved ? 256 : 0, 0);













































}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED char16_t *
NOTHROW_RPC(LIBDCALL libd_wfrealpath)(fd_t fd,
                                      char16_t *resolved,
                                      size_t buflen) {

	return libd_wfrealpath4(fd, resolved, buflen, 0);

































}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") WUNUSED char32_t *
NOTHROW_RPC(LIBKCALL libc_wfrealpath)(fd_t fd,
                                      char32_t *resolved,
                                      size_t buflen) {

	return libc_wfrealpath4(fd, resolved, buflen, 0);

































}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED char16_t *
NOTHROW_RPC(LIBDCALL libd_wfrealpath4)(fd_t fd,
                                       char16_t *resolved,
                                       size_t buflen,
                                       atflag_t flags) {
	char *utf8_resolved;
	char16_t *wcs_resolved;
	size_t resolved_length;
	utf8_resolved = libd_frealpath4(fd, NULL, 0, flags);
	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = libd_convert_mbstowcs(utf8_resolved);

	libc_free(utf8_resolved);

	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = libd_wcslen(wcs_resolved) + 1;
	if (resolved_length > buflen) {

		libc_free(wcs_resolved);


		(void)libc_seterrno(ERANGE);



		return NULL;
	}
	(char16_t *)libc_memcpyw(resolved, wcs_resolved, resolved_length);

	libc_free(wcs_resolved);

	return resolved;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") WUNUSED char32_t *
NOTHROW_RPC(LIBKCALL libc_wfrealpath4)(fd_t fd,
                                       char32_t *resolved,
                                       size_t buflen,
                                       atflag_t flags) {
	char *utf8_resolved;
	char32_t *wcs_resolved;
	size_t resolved_length;
	utf8_resolved = libc_frealpath4(fd, NULL, 0, flags);
	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = libc_convert_mbstowcs(utf8_resolved);

	libc_free(utf8_resolved);

	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = libc_wcslen(wcs_resolved) + 1;
	if (resolved_length > buflen) {

		libc_free(wcs_resolved);


		(void)libc_seterrno(ERANGE);



		return NULL;
	}
	(char32_t *)libc_memcpyl(resolved, wcs_resolved, resolved_length);

	libc_free(wcs_resolved);

	return resolved;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.property") WUNUSED NONNULL((2)) char16_t *
NOTHROW_RPC(LIBDCALL libd_wfrealpathat)(fd_t dirfd,
                                        char16_t const *filename,
                                        char16_t *resolved,
                                        size_t buflen,
                                        atflag_t flags) {
	char *utf8_filename, *utf8_resolved;
	char16_t *wcs_resolved;
	size_t resolved_length;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return NULL;
	utf8_resolved = libd_frealpathat(dirfd, utf8_filename, NULL, 0, flags);

	libc_free(utf8_filename);

	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = libd_convert_mbstowcs(utf8_resolved);

	libc_free(utf8_resolved);

	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = libd_wcslen(wcs_resolved) + 1;
	if (resolved_length > buflen) {

		libc_free(wcs_resolved);


		(void)libc_seterrno(ERANGE);



		return NULL;
	}
	(char16_t *)libc_memcpyw(resolved, wcs_resolved, resolved_length);

	libc_free(wcs_resolved);

	return resolved;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") WUNUSED NONNULL((2)) char32_t *
NOTHROW_RPC(LIBKCALL libc_wfrealpathat)(fd_t dirfd,
                                        char32_t const *filename,
                                        char32_t *resolved,
                                        size_t buflen,
                                        atflag_t flags) {
	char *utf8_filename, *utf8_resolved;
	char32_t *wcs_resolved;
	size_t resolved_length;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return NULL;
	utf8_resolved = libc_frealpathat(dirfd, utf8_filename, NULL, 0, flags);

	libc_free(utf8_filename);

	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = libc_convert_mbstowcs(utf8_resolved);

	libc_free(utf8_resolved);

	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = libc_wcslen(wcs_resolved) + 1;
	if (resolved_length > buflen) {

		libc_free(wcs_resolved);


		(void)libc_seterrno(ERANGE);



		return NULL;
	}
	(char32_t *)libc_memcpyl(resolved, wcs_resolved, resolved_length);

	libc_free(wcs_resolved);

	return resolved;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wtoi)(char16_t const *nptr) {
#if __SIZEOF_INT__ <= 4
	return (int)libd_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)libd_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wtoi)(char32_t const *nptr) {
#if __SIZEOF_INT__ <= 4
	return (int)libc_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)libc_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_wtol)(char16_t const *nptr) {
#if __SIZEOF_LONG__ <= 4
	return (long)libd_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libd_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_wtol, libc_wtoi);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBKCALL libc_wtol)(char32_t const *nptr) {
#if __SIZEOF_LONG__ <= 4
	return (long)libc_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wtoll)(char16_t const *nptr) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libd_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libd_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_wtoll, libc_wtoi);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_wtoll, libc_wtol);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBKCALL libc_wtoll)(char32_t const *nptr) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wsystem, libd_wsystem);
DEFINE_PUBLIC_ALIAS(DOS$wsystem, libd_wsystem);
DEFINE_PUBLIC_ALIAS(wsystem, libc_wsystem);
DEFINE_PUBLIC_ALIAS(DOS$wrealpath, libd_wrealpath);
DEFINE_PUBLIC_ALIAS(wrealpath, libc_wrealpath);
DEFINE_PUBLIC_ALIAS(DOS$wfrealpath, libd_wfrealpath);
DEFINE_PUBLIC_ALIAS(wfrealpath, libc_wfrealpath);
DEFINE_PUBLIC_ALIAS(DOS$wfrealpath4, libd_wfrealpath4);
DEFINE_PUBLIC_ALIAS(wfrealpath4, libc_wfrealpath4);
DEFINE_PUBLIC_ALIAS(DOS$wfrealpathat, libd_wfrealpathat);
DEFINE_PUBLIC_ALIAS(wfrealpathat, libc_wfrealpathat);
DEFINE_PUBLIC_ALIAS(DOS$_wtoi, libd_wtoi);
DEFINE_PUBLIC_ALIAS(DOS$wtoi, libd_wtoi);
DEFINE_PUBLIC_ALIAS(wtoi, libc_wtoi);
DEFINE_PUBLIC_ALIAS(DOS$_wtol, libd_wtol);
DEFINE_PUBLIC_ALIAS(DOS$wtol, libd_wtol);
DEFINE_PUBLIC_ALIAS(wtol, libc_wtol);
DEFINE_PUBLIC_ALIAS(DOS$_wtoll, libd_wtoll);
DEFINE_PUBLIC_ALIAS(DOS$wtoll, libd_wtoll);
DEFINE_PUBLIC_ALIAS(wtoll, libc_wtoll);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_C */
