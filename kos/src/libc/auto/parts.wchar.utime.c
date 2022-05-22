/* HASH CRC-32:0x14afc1d3 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_UTIME_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_UTIME_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.utime.h"
#include "../user/stdlib.h"
#include "uchar.h"
#include "../user/utime.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBDCALL libd_wutime)(char16_t const *file,
                                  struct utimbuf const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime







#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
	struct utimbuf64 buf64;
	if (!file_times)
		return libd_wutime64(file, NULL);
	buf64.actime  = (time64_t)file_times->actime;
	buf64.modtime = (time64_t)file_times->modtime;
	return libd_wutime64(file, &buf64);
#else /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	int result;
	char *utf8_file;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libd_utime(utf8_file, file_times);

	libc_free(utf8_file);

	return result;
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBKCALL libc_wutime)(char32_t const *file,
                                  struct utimbuf const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime







#if defined(__LIBCCALL_IS_LIBKCALL) && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
	struct utimbuf64 buf64;
	if (!file_times)
		return libc_wutime64(file, NULL);
	buf64.actime  = (time64_t)file_times->actime;
	buf64.modtime = (time64_t)file_times->modtime;
	return libc_wutime64(file, &buf64);
#else /* __LIBCCALL_IS_LIBKCALL && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	int result;
	char *utf8_file;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libc_utime(utf8_file, file_times);

	libc_free(utf8_file);

	return result;
#endif /* !__LIBCCALL_IS_LIBKCALL || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBDCALL libd_wutime64)(char16_t const *file,
                                    struct utimbuf64 const *file_times) {

	int result;
	char *utf8_file;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libd_utime64(utf8_file, file_times);

	libc_free(utf8_file);

	return result;


















}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_wutime64, libc_wutime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBKCALL libc_wutime64)(char32_t const *file,
                                    struct utimbuf64 const *file_times) {

	int result;
	char *utf8_file;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = libc_utime64(utf8_file, file_times);

	libc_free(utf8_file);

	return result;


















}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wutime, libd_wutime);
DEFINE_PUBLIC_ALIAS(DOS$_wutime32, libd_wutime);
DEFINE_PUBLIC_ALIAS(DOS$wutime, libd_wutime);
DEFINE_PUBLIC_ALIAS(wutime, libc_wutime);
DEFINE_PUBLIC_ALIAS(DOS$_wutime64, libd_wutime64);
DEFINE_PUBLIC_ALIAS(DOS$wutime64, libd_wutime64);
DEFINE_PUBLIC_ALIAS(wutime64, libc_wutime64);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_UTIME_C */
