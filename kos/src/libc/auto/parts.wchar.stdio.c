/* HASH CRC-32:0x50055409 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_STDIO_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_STDIO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.stdio.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "uchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wremove)(char16_t const *filename) {
	int result = -1;
	/*utf-8*/ char *utf8_filename;
	utf8_filename = libd_convert_wcstombs(filename);
	if likely(utf8_filename) {
		result = libd_remove(utf8_filename);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wremove)(char32_t const *filename) {
	int result = -1;
	/*utf-8*/ char *utf8_filename;
	utf8_filename = libc_convert_wcstombs(filename);
	if likely(utf8_filename) {
		result = libc_remove(utf8_filename);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd_wfopen)(char16_t const *filename,
                                  char16_t const *mode) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libd_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_filename;
	result = libd_fopen(utf8_filename, utf8_mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_utf8_filename:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc_wfopen)(char32_t const *filename,
                                  char32_t const *mode) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libc_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_filename;
	result = libc_fopen(utf8_filename, utf8_mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_utf8_filename:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd_wfreopen)(char16_t const *filename,
                                    char16_t const *mode,
                                    FILE *stream) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libd_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_filename;
	result = libd_freopen(utf8_filename, utf8_mode, stream);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_utf8_filename:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc_wfreopen)(char32_t const *filename,
                                    char32_t const *mode,
                                    FILE *stream) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libc_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_filename;
	result = libc_freopen(utf8_filename, utf8_mode, stream);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_utf8_filename:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd_wpopen)(char16_t const *command,
                                  char16_t const *mode) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_command;
	/*utf-8*/ char *utf8_mode;
	utf8_command = libd_convert_wcstombs(command);
	if unlikely(!utf8_command)
		goto done;
	utf8_mode = libd_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_command;
	result = libc_popen(utf8_command, utf8_mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_utf8_command:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_command);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc_wpopen)(char32_t const *command,
                                  char32_t const *mode) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_command;
	/*utf-8*/ char *utf8_mode;
	utf8_command = libc_convert_wcstombs(command);
	if unlikely(!utf8_command)
		goto done;
	utf8_mode = libc_convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_command;
	result = libc_popen(utf8_command, utf8_mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_utf8_command:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_command);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wremove, libd_wremove);
DEFINE_PUBLIC_ALIAS(DOS$wremove, libd_wremove);
DEFINE_PUBLIC_ALIAS(wremove, libc_wremove);
DEFINE_PUBLIC_ALIAS(DOS$_wfopen, libd_wfopen);
DEFINE_PUBLIC_ALIAS(DOS$wfopen, libd_wfopen);
DEFINE_PUBLIC_ALIAS(wfopen, libc_wfopen);
DEFINE_PUBLIC_ALIAS(DOS$_wfreopen, libd_wfreopen);
DEFINE_PUBLIC_ALIAS(DOS$wfreopen, libd_wfreopen);
DEFINE_PUBLIC_ALIAS(wfreopen, libc_wfreopen);
DEFINE_PUBLIC_ALIAS(DOS$_wpopen, libd_wpopen);
DEFINE_PUBLIC_ALIAS(DOS$wpopen, libd_wpopen);
DEFINE_PUBLIC_ALIAS(wpopen, libc_wpopen);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_STDIO_C */
