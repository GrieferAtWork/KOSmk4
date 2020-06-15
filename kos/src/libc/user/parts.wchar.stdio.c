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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_STDIO_C
#define GUARD_LIBC_USER_PARTS_WCHAR_STDIO_C 1

#include "../api.h"
/**/

#include "../libc/uchar.h"
#include "malloc.h"
#include "parts.wchar.stdio.h"
#include "stdio-api.h"
#include "stdio.h"
#include "stdlib.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_wremove,hash:CRC-32=0xff46ff3c]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wremove)(char32_t const *filename)
/*[[[body:libc_wremove]]]*/
{
	int result = -1;
	/*utf-8*/ char *utf8_filename;
	utf8_filename = libc_uchar_c32tombs(filename);
	if likely(utf8_filename) {
		result = remove(utf8_filename);
		free(utf8_filename);
	}
	return result;
}
/*[[[end:libc_wremove]]]*/

/*[[[head:libd_wremove,hash:CRC-32=0xf7fbba8b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wremove)(char16_t const *filename)
/*[[[body:libd_wremove]]]*/
{
	int result = -1;
	/*utf-8*/ char *utf8_filename;
	utf8_filename = libc_uchar_c16tombs(filename);
	if likely(utf8_filename) {
		result = remove(utf8_filename);
		free(utf8_filename);
	}
	return result;
}
/*[[[end:libd_wremove]]]*/

/*[[[head:libc_wfopen,hash:CRC-32=0x6eca40bf]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc_wfopen)(char32_t const *filename,
                                  char32_t const *mode)
/*[[[body:libc_wfopen]]]*/
{
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libc_uchar_c32tombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libc_uchar_c32tombs(mode);
	if unlikely(!utf8_mode) {
		free(utf8_filename);
		goto done;
	}
	result = fopen(utf8_filename, utf8_mode);
	free(utf8_mode);
	free(utf8_filename);
done:
	return result;
}
/*[[[end:libc_wfopen]]]*/

/*[[[head:libd_wfopen,hash:CRC-32=0x89861ff5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd_wfopen)(char16_t const *filename,
                                  char16_t const *mode)
/*[[[body:libd_wfopen]]]*/
{
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libc_uchar_c16tombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libc_uchar_c16tombs(mode);
	if unlikely(!utf8_mode) {
		free(utf8_filename);
		goto done;
	}
	result = fopen(utf8_filename, utf8_mode);
	free(utf8_mode);
	free(utf8_filename);
done:
	return result;
}
/*[[[end:libd_wfopen]]]*/

/*[[[head:libc_wfreopen,hash:CRC-32=0x4ea495f0]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc_wfreopen)(char32_t const *filename,
                                    char32_t const *mode,
                                    FILE *stream)
/*[[[body:libc_wfreopen]]]*/
{
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libc_uchar_c32tombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libc_uchar_c32tombs(mode);
	if unlikely(!utf8_mode) {
		free(utf8_filename);
		goto done;
	}
	result = freopen(utf8_filename, utf8_mode, stream);
	free(utf8_mode);
	free(utf8_filename);
done:
	return result;
}
/*[[[end:libc_wfreopen]]]*/

/*[[[head:libd_wfreopen,hash:CRC-32=0x434b7b12]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd_wfreopen)(char16_t const *filename,
                                    char16_t const *mode,
                                    FILE *stream)
/*[[[body:libd_wfreopen]]]*/
{
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = libc_uchar_c16tombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = libc_uchar_c16tombs(mode);
	if unlikely(!utf8_mode) {
		free(utf8_filename);
		goto done;
	}
	result = freopen(utf8_filename, utf8_mode, stream);
	free(utf8_mode);
	free(utf8_filename);
done:
	return result;
}
/*[[[end:libd_wfreopen]]]*/

/*[[[head:libc_wpopen,hash:CRC-32=0x81ec51f1]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc_wpopen)(char32_t const *command,
                                  char32_t const *mode)
/*[[[body:libc_wpopen]]]*/
{
	FILE *result = NULL;
	/*utf-8*/ char *utf8_command;
	/*utf-8*/ char *utf8_mode;
	utf8_command = libc_uchar_c32tombs(command);
	if unlikely(!utf8_command)
		goto done;
	utf8_mode = libc_uchar_c32tombs(mode);
	if unlikely(!utf8_mode) {
		free(utf8_command);
		goto done;
	}
	result = popen(utf8_command, utf8_mode);
	free(utf8_mode);
	free(utf8_command);
done:
	return result;
}
/*[[[end:libc_wpopen]]]*/

/*[[[head:libd_wpopen,hash:CRC-32=0x34f8cf3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd_wpopen)(char16_t const *command,
                                  char16_t const *mode)
/*[[[body:libd_wpopen]]]*/
{
	FILE *result = NULL;
	/*utf-8*/ char *utf8_command;
	/*utf-8*/ char *utf8_mode;
	utf8_command = libc_uchar_c16tombs(command);
	if unlikely(!utf8_command)
		goto done;
	utf8_mode = libc_uchar_c16tombs(mode);
	if unlikely(!utf8_mode) {
		free(utf8_command);
		goto done;
	}
	result = popen(utf8_command, utf8_mode);
	free(utf8_mode);
	free(utf8_command);
done:
	return result;
}
/*[[[end:libd_wpopen]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xf8f5be99]]]*/
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
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_STDIO_C */
