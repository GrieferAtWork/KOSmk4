/* HASH CRC-32:0x91e709ce */
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
#include "parts.wchar.unistd.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "uchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wremove)(char16_t const *filename) {

	return libd_wremoveat(__AT_FDCWD, filename);












}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wremove)(char32_t const *filename) {

	return libc_wremoveat(__AT_FDCWD, filename);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wrename)(char16_t const *oldname,
                                   char16_t const *newname_or_path) {

	return libd_wrenameat(__AT_FDCWD, oldname, __AT_FDCWD, newname_or_path);





















}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wrename)(char32_t const *oldname,
                                   char32_t const *newname_or_path) {

	return libc_wrenameat(__AT_FDCWD, oldname, __AT_FDCWD, newname_or_path);





















}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBDCALL libd_wrenameat)(fd_t oldfd,
                                     char16_t const *oldname,
                                     fd_t newfd,
                                     char16_t const *newname_or_path) {

	return libd_wrenameat2(oldfd, oldname, newfd, newname_or_path, 0);





















}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBKCALL libc_wrenameat)(fd_t oldfd,
                                     char32_t const *oldname,
                                     fd_t newfd,
                                     char32_t const *newname_or_path) {

	return libc_wrenameat2(oldfd, oldname, newfd, newname_or_path, 0);





















}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wremoveat)(fd_t dirfd,
                                     char16_t const *filename) {

	return libd_wunlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);












}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wremoveat)(fd_t dirfd,
                                     char32_t const *filename) {

	return libc_wunlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBDCALL libd_wrenameat2)(fd_t oldfd,
                                      char16_t const *oldname,
                                      fd_t newfd,
                                      char16_t const *newname_or_path,
                                      atflag_t flags) {
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = libd_convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = libd_convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {

		libc_free(utf8_oldname);

		return -1;
	}
	result = libd_renameat2(oldfd, utf8_oldname, newfd, utf8_newname_or_path, flags);

	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);

	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBKCALL libc_wrenameat2)(fd_t oldfd,
                                      char32_t const *oldname,
                                      fd_t newfd,
                                      char32_t const *newname_or_path,
                                      atflag_t flags) {
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = libc_convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = libc_convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {

		libc_free(utf8_oldname);

		return -1;
	}
	result = libc_renameat2(oldfd, utf8_oldname, newfd, utf8_newname_or_path, flags);

	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);

	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
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

	libc_free(utf8_mode);

done_utf8_filename:

	libc_free(utf8_filename);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
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

	libc_free(utf8_mode);

done_utf8_filename:

	libc_free(utf8_filename);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *
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

	libc_free(utf8_mode);

done_utf8_filename:

	libc_free(utf8_filename);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *
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

	libc_free(utf8_mode);

done_utf8_filename:

	libc_free(utf8_filename);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
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

	libc_free(utf8_mode);

done_utf8_command:

	libc_free(utf8_command);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *
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

	libc_free(utf8_mode);

done_utf8_command:

	libc_free(utf8_command);

done:
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wremove, libd_wremove);
DEFINE_PUBLIC_ALIAS(DOS$wremove, libd_wremove);
DEFINE_PUBLIC_ALIAS(wremove, libc_wremove);
DEFINE_PUBLIC_ALIAS(DOS$_wrename, libd_wrename);
DEFINE_PUBLIC_ALIAS(DOS$wrename, libd_wrename);
DEFINE_PUBLIC_ALIAS(wrename, libc_wrename);
DEFINE_PUBLIC_ALIAS(DOS$wrenameat, libd_wrenameat);
DEFINE_PUBLIC_ALIAS(wrenameat, libc_wrenameat);
DEFINE_PUBLIC_ALIAS(DOS$wremoveat, libd_wremoveat);
DEFINE_PUBLIC_ALIAS(wremoveat, libc_wremoveat);
DEFINE_PUBLIC_ALIAS(DOS$wrenameat2, libd_wrenameat2);
DEFINE_PUBLIC_ALIAS(wrenameat2, libc_wrenameat2);
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
