/* HASH CRC-32:0xaeda9f81 */
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
#include "../user/parts.wchar.unistd.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "uchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wremove)(char16_t const *filename) {
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wremoveat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wremoveat) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return libd_wremoveat(__AT_FDCWD, filename);
#else /* __AT_FDCWD && ((__CRT_HAVE_wremoveat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wremoveat || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	char *utf8_filename;
	int result;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libd_remove(utf8_filename);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wremoveat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wremoveat && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wremove)(char32_t const *filename) {
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wremoveat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wremoveat) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return libc_wremoveat(__AT_FDCWD, filename);
#else /* __AT_FDCWD && ((__CRT_HAVE_wremoveat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wremoveat || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 4) || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	char *utf8_filename;
	int result;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_remove(utf8_filename);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wremoveat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wremoveat && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 4) && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_wrename)(char16_t const *oldname,
                                   char16_t const *newname_or_path) {
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wrenameat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wrenameat) || defined(__CRT_HAVE_wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$wrenameat2) || (defined(__CRT_HAVE_renameat2) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return libd_wrenameat(__AT_FDCWD, oldname, __AT_FDCWD, newname_or_path);
#else /* __AT_FDCWD && ((__CRT_HAVE_wrenameat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wrenameat || __CRT_HAVE_wrenameat2 || (__CRT_HAVE_renameat2 && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_renameat || __CRT_HAVE_renameat2) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$wrenameat2 || (__CRT_HAVE_renameat2 && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_renameat || __CRT_HAVE_renameat2) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = libd_convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = libd_convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}
	result = libd_rename(utf8_oldname, utf8_newname_or_path);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wrenameat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wrenameat && !__CRT_HAVE_wrenameat2 && (!__CRT_HAVE_renameat2 || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$wrenameat2 && (!__CRT_HAVE_renameat2 || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wrename)(char32_t const *oldname,
                                   char32_t const *newname_or_path) {
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wrenameat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wrenameat) || defined(__CRT_HAVE_wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$wrenameat2) || (defined(__CRT_HAVE_renameat2) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return libc_wrenameat(__AT_FDCWD, oldname, __AT_FDCWD, newname_or_path);
#else /* __AT_FDCWD && ((__CRT_HAVE_wrenameat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wrenameat || __CRT_HAVE_wrenameat2 || (__CRT_HAVE_renameat2 && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_renameat || __CRT_HAVE_renameat2) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$wrenameat2 || (__CRT_HAVE_renameat2 && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_renameat || __CRT_HAVE_renameat2) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = libc_convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = libc_convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}
	result = libc_rename(utf8_oldname, utf8_newname_or_path);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wrenameat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wrenameat && !__CRT_HAVE_wrenameat2 && (!__CRT_HAVE_renameat2 || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$wrenameat2 && (!__CRT_HAVE_renameat2 || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify") NONNULL((2, 4)) int
NOTHROW_RPC(LIBDCALL libd_wrenameat)(fd_t oldfd,
                                     char16_t const *oldname,
                                     fd_t newfd,
                                     char16_t const *newname_or_path) {
#if (defined(__CRT_HAVE_wrenameat2) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_renameat2) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
	return libd_wrenameat2(oldfd, oldname, newfd, newname_or_path, 0);
#else /* (__CRT_HAVE_wrenameat2 && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wrenameat2 || (__CRT_HAVE_renameat2 && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_renameat2 && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = libd_convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = libd_convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}
	result = libd_renameat(oldfd, utf8_oldname, newfd, utf8_newname_or_path);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* (!__CRT_HAVE_wrenameat2 || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wrenameat2 && (!__CRT_HAVE_renameat2 || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_renameat2 || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") NONNULL((2, 4)) int
NOTHROW_RPC(LIBKCALL libc_wrenameat)(fd_t oldfd,
                                     char32_t const *oldname,
                                     fd_t newfd,
                                     char32_t const *newname_or_path) {
#if (defined(__CRT_HAVE_wrenameat2) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_renameat2) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
	return libc_wrenameat2(oldfd, oldname, newfd, newname_or_path, 0);
#else /* (__CRT_HAVE_wrenameat2 && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wrenameat2 || (__CRT_HAVE_renameat2 && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_renameat2 && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = libc_convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = libc_convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}
	result = libc_renameat(oldfd, utf8_oldname, newfd, utf8_newname_or_path);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* (!__CRT_HAVE_wrenameat2 || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wrenameat2 && (!__CRT_HAVE_renameat2 || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 4) && (!__CRT_HAVE_renameat2 || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wremoveat)(fd_t dirfd,
                                     char16_t const *filename) {
#if ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wunlinkat) || (defined(__CRT_HAVE_unlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_unlinkat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && defined(__AT_REMOVEREG) && defined(__AT_REMOVEDIR)
	return libd_wunlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);
#else /* ((__CRT_HAVE_wunlinkat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wunlinkat || (__CRT_HAVE_unlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_unlinkat && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __AT_REMOVEREG && __AT_REMOVEDIR */
	char *utf8_filename;
	int result;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libd_removeat(dirfd, utf8_filename);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* ((!__CRT_HAVE_wunlinkat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wunlinkat && (!__CRT_HAVE_unlinkat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_unlinkat || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || !__AT_REMOVEREG || !__AT_REMOVEDIR */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wremoveat)(fd_t dirfd,
                                     char32_t const *filename) {
#if ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wunlinkat) || (defined(__CRT_HAVE_unlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_unlinkat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && defined(__AT_REMOVEREG) && defined(__AT_REMOVEDIR)
	return libc_wunlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);
#else /* ((__CRT_HAVE_wunlinkat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wunlinkat || (__CRT_HAVE_unlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_unlinkat && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __AT_REMOVEREG && __AT_REMOVEDIR */
	char *utf8_filename;
	int result;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_removeat(dirfd, utf8_filename);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
#endif /* ((!__CRT_HAVE_wunlinkat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wunlinkat && (!__CRT_HAVE_unlinkat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 4) && (!__CRT_HAVE_unlinkat || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || !__AT_REMOVEREG || !__AT_REMOVEDIR */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.modify") NONNULL((2, 4)) int
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
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}
	result = libd_renameat2(oldfd, utf8_oldname, newfd, utf8_newname_or_path, flags);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.modify") NONNULL((2, 4)) int
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
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}
	result = libc_renameat2(oldfd, utf8_oldname, newfd, utf8_newname_or_path, flags);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_newname_or_path);
	libc_free(utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
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
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_wremove, libc_wremove);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(wremove, libc_wremove);
DEFINE_PUBLIC_ALIAS(DOS$_wrename, libd_wrename);
DEFINE_PUBLIC_ALIAS(DOS$wrename, libd_wrename);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_wrename, libc_wrename);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(wrename, libc_wrename);
DEFINE_PUBLIC_ALIAS(DOS$wrenameat, libd_wrenameat);
DEFINE_PUBLIC_ALIAS(wrenameat, libc_wrenameat);
DEFINE_PUBLIC_ALIAS(DOS$wremoveat, libd_wremoveat);
DEFINE_PUBLIC_ALIAS(wremoveat, libc_wremoveat);
DEFINE_PUBLIC_ALIAS(DOS$wrenameat2, libd_wrenameat2);
DEFINE_PUBLIC_ALIAS(wrenameat2, libc_wrenameat2);
DEFINE_PUBLIC_ALIAS(DOS$_wfopen, libd_wfopen);
DEFINE_PUBLIC_ALIAS(DOS$wfopen, libd_wfopen);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_wfopen, libc_wfopen);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(wfopen, libc_wfopen);
DEFINE_PUBLIC_ALIAS(DOS$_wfreopen, libd_wfreopen);
DEFINE_PUBLIC_ALIAS(DOS$wfreopen, libd_wfreopen);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_wfreopen, libc_wfreopen);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(wfreopen, libc_wfreopen);
DEFINE_PUBLIC_ALIAS(DOS$_wpopen, libd_wpopen);
DEFINE_PUBLIC_ALIAS(DOS$wpopen, libd_wpopen);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_wpopen, libc_wpopen);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(wpopen, libc_wpopen);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_STDIO_C */
