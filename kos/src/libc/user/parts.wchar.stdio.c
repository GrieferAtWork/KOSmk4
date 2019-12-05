/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

/*[[[head:wremove,hash:CRC-32=0xf6a1a683]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.modify.wremove") int
NOTHROW_NCX(LIBCCALL libc_wremove)(char32_t const *filename)
/*[[[body:wremove]]]*/
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
/*[[[end:wremove]]]*/

/*[[[head:DOS$wremove,hash:CRC-32=0xa0d3f86f]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.modify.wremove") int
NOTHROW_NCX(LIBDCALL libd_wremove)(char16_t const *filename)
/*[[[body:DOS$wremove]]]*/
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
/*[[[end:DOS$wremove]]]*/

/*[[[head:wfopen,hash:CRC-32=0xcf9a2e1d]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.access.wfopen") FILE *
NOTHROW_NCX(LIBCCALL libc_wfopen)(char32_t const *filename,
                                  char32_t const *mode)
/*[[[body:wfopen]]]*/
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
/*[[[end:wfopen]]]*/

/*[[[head:DOS$wfopen,hash:CRC-32=0x9d8f28d7]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access.wfopen") FILE *
NOTHROW_NCX(LIBDCALL libd_wfopen)(char16_t const *filename,
                                  char16_t const *mode)
/*[[[body:DOS$wfopen]]]*/
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
/*[[[end:DOS$wfopen]]]*/

/*[[[head:wfreopen,hash:CRC-32=0x82a70bb1]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.access.wfreopen") FILE *
NOTHROW_NCX(LIBCCALL libc_wfreopen)(char32_t const *filename,
                                    char32_t const *mode,
                                    FILE *stream)
/*[[[body:wfreopen]]]*/
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
/*[[[end:wfreopen]]]*/

/*[[[head:DOS$wfreopen,hash:CRC-32=0x5879d237]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access.wfreopen") FILE *
NOTHROW_NCX(LIBDCALL libd_wfreopen)(char16_t const *filename,
                                    char16_t const *mode,
                                    FILE *stream)
/*[[[body:DOS$wfreopen]]]*/
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
/*[[[end:DOS$wfreopen]]]*/

/*[[[head:wpopen,hash:CRC-32=0x9399bc11]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.access.wpopen") FILE *
NOTHROW_NCX(LIBCCALL libc_wpopen)(char32_t const *command,
                                  char32_t const *mode)
/*[[[body:wpopen]]]*/
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
/*[[[end:wpopen]]]*/

/*[[[head:DOS$wpopen,hash:CRC-32=0xe3acdce2]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access.wpopen") FILE *
NOTHROW_NCX(LIBDCALL libd_wpopen)(char16_t const *command,
                                  char16_t const *mode)
/*[[[body:DOS$wpopen]]]*/
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
/*[[[end:DOS$wpopen]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xfb3ce698]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(wremove, libc_wremove);
DEFINE_PUBLIC_WEAK_ALIAS(_wremove, libc_wremove);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wremove, libd_wremove);
DEFINE_PUBLIC_WEAK_ALIAS(wfopen, libc_wfopen);
DEFINE_PUBLIC_WEAK_ALIAS(_wfopen, libc_wfopen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wfopen, libd_wfopen);
DEFINE_PUBLIC_WEAK_ALIAS(wfreopen, libc_wfreopen);
DEFINE_PUBLIC_WEAK_ALIAS(_wfreopen, libc_wfreopen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wfreopen, libd_wfreopen);
DEFINE_PUBLIC_WEAK_ALIAS(wpopen, libc_wpopen);
DEFINE_PUBLIC_WEAK_ALIAS(_wpopen, libc_wpopen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wpopen, libd_wpopen);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_STDIO_C */
