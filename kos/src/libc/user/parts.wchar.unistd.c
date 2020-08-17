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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C
#define GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C 1
#define _UTF_SOURCE 1

#include "../api.h"
/**/

#include "../libc/uchar.h"
#include "parts.wchar.unistd.h"
#include <unistd.h>
#include <unicode.h>
#include <format-printer.h>
#include <malloc.h>
#include <string.h>
#include <uchar.h>
#include <fcntl.h>
#include <stdio.h> /* L_ctermid */
#include <sys/utsname.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_wttyname,hash:CRC-32=0x197d3063]]]*/
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED char32_t *
NOTHROW_RPC(LIBKCALL libc_wttyname)(fd_t fd)
/*[[[body:libc_wttyname]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTEDF("wttyname(%" PRIxN(__SIZEOF_FD_T__) ")", fd); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_wttyname]]]*/

/*[[[head:libd_wttyname,hash:CRC-32=0x9cce60ac]]]*/
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED char16_t *
NOTHROW_RPC(LIBDCALL libd_wttyname)(fd_t fd)
/*[[[body:libd_wttyname]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTEDF("DOS$wttyname(%" PRIxN(__SIZEOF_FD_T__) ")", fd); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd_wttyname]]]*/

/*[[[head:libc_wttyname_r,hash:CRC-32=0x5a5cd16f]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wttyname_r)(fd_t fd,
                                      char32_t *buf,
                                      size_t buflen)
/*[[[body:libc_wttyname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("wttyname_r(%" PRIxN(__SIZEOF_FD_T__) ", %p, %Ix)", fd, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_wttyname_r]]]*/

/*[[[head:libd_wttyname_r,hash:CRC-32=0x9e01164a]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd,
                                      char16_t *buf,
                                      size_t buflen)
/*[[[body:libd_wttyname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("DOS$wttyname_r(%" PRIxN(__SIZEOF_FD_T__) ", %p, %Ix)", fd, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_wttyname_r]]]*/

/*[[[head:libc_wgetlogin,hash:CRC-32=0xd4d820d2]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc_wgetlogin)(void)
/*[[[body:libc_wgetlogin]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("wgetlogin"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_wgetlogin]]]*/

/*[[[head:libd_wgetlogin,hash:CRC-32=0xe17f878b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd_wgetlogin)(void)
/*[[[body:libd_wgetlogin]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$wgetlogin"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd_wgetlogin]]]*/

/*[[[head:libc_wpathconf,hash:CRC-32=0xf27f013b]]]*/
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) longptr_t
NOTHROW_RPC(LIBKCALL libc_wpathconf)(char32_t const *path,
                                     __STDC_INT_AS_UINT_T name)
/*[[[body:libc_wpathconf]]]*/
{
	longptr_t result;
	char *used_path;
	used_path = libc_uchar_c32tombs(path);
	if unlikely(!used_path)
		return -1;
	result = pathconf(used_path, name);
	free(used_path);
	return result;
}
/*[[[end:libc_wpathconf]]]*/

/*[[[head:libd_wpathconf,hash:CRC-32=0x795cfdfb]]]*/
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) longptr_t
NOTHROW_RPC(LIBDCALL libd_wpathconf)(char16_t const *path,
                                     __STDC_INT_AS_UINT_T name)
/*[[[body:libd_wpathconf]]]*/
{
	longptr_t result;
	char *used_path;
	used_path = libc_uchar_c16tombs(path);
	if unlikely(!used_path)
		return -1;
	result = pathconf(used_path, name);
	free(used_path);
	return result;
}
/*[[[end:libd_wpathconf]]]*/

/*[[[head:libc_wlinkat,hash:CRC-32=0xc663ce73]]]*/
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((2, 4)) int
NOTHROW_RPC(LIBKCALL libc_wlinkat)(fd_t fromfd,
                                   char32_t const *from,
                                   fd_t tofd,
                                   char32_t const *to,
                                   atflag_t flags)
/*[[[body:libc_wlinkat]]]*/
{
	int result = -1;
	char *used_from = NULL, *used_to = NULL;
	if (from) {
		used_from = libc_uchar_c32tombs(from);
		if unlikely(!used_from)
			goto done;
	}
	if (to) {
		used_to = libc_uchar_c32tombs(to);
		if unlikely(!used_to)
			goto done_from;
	}
	result = linkat(fromfd, used_from, tofd, used_to, flags);
	free(used_to);
done_from:
	free(used_from);
done:
	return result;
}
/*[[[end:libc_wlinkat]]]*/

/*[[[head:libd_wlinkat,hash:CRC-32=0x81955674]]]*/
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2, 4)) int
NOTHROW_RPC(LIBDCALL libd_wlinkat)(fd_t fromfd,
                                   char16_t const *from,
                                   fd_t tofd,
                                   char16_t const *to,
                                   atflag_t flags)
/*[[[body:libd_wlinkat]]]*/
{
	int result = -1;
	char *used_from = NULL, *used_to = NULL;
	if (from) {
		used_from = libc_uchar_c16tombs(from);
		if unlikely(!used_from)
			goto done;
	}
	if (to) {
		used_to = libc_uchar_c16tombs(to);
		if unlikely(!used_to)
			goto done_from;
	}
	result = linkat(fromfd, used_from, tofd, used_to, flags);
	free(used_to);
done_from:
	free(used_from);
done:
	return result;
}
/*[[[end:libd_wlinkat]]]*/

/*[[[head:libc_wchdir,hash:CRC-32=0x17d82a4d]]]*/
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wchdir)(char32_t const *path)
/*[[[body:libc_wchdir]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c32tombs(path);
	if likely(used_path) {
		result = chdir(used_path);
		free(used_path);
	}
	return result;
}
/*[[[end:libc_wchdir]]]*/

/*[[[head:libd_wchdir,hash:CRC-32=0x1ba11c06]]]*/
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wchdir)(char16_t const *path)
/*[[[body:libd_wchdir]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c16tombs(path);
	if likely(used_path) {
		result = chdir(used_path);
		free(used_path);
	}
	return result;
}
/*[[[end:libd_wchdir]]]*/

/*[[[head:libc_wgetcwd,hash:CRC-32=0x875905f9]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.unsorted") char32_t *
NOTHROW_RPC(LIBKCALL libc_wgetcwd)(char32_t *buf,
                                   size_t bufsize)
/*[[[body:libc_wgetcwd]]]*/
{
	char32_t *result;
	size_t result_len;
	result = libc_wget_current_dir_name();
	if unlikely(!result)
		return NULL;
	if (!buf) {
		char32_t *new_result;
		if (!bufsize)
			return result;
		result_len = c32slen(result);
		if (bufsize <= result_len) {
			libc_seterrno(ERANGE);
			free(result);
			return NULL;
		}
		new_result = (char32_t *)realloc(result, bufsize * 4);
		if unlikely(!new_result) {
			free(result);
			return NULL;
		}
		return new_result;
	}
	result_len = c32slen(result);
	if (bufsize <= result_len) {
		libc_seterrno(ERANGE);
		free(result);
		return NULL;
	}
	memcpyl(buf, result, result_len + 1);
	free(result);
	return buf;
}
/*[[[end:libc_wgetcwd]]]*/

/*[[[head:libd_wgetcwd,hash:CRC-32=0x967505a2]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") char16_t *
NOTHROW_RPC(LIBDCALL libd_wgetcwd)(char16_t *buf,
                                   size_t bufsize)
/*[[[body:libd_wgetcwd]]]*/
{
	char16_t *result;
	size_t result_len;
	result = libd_wget_current_dir_name();
	if unlikely(!result)
		return NULL;
	if (!buf) {
		char16_t *new_result;
		if (!bufsize)
			return result;
		result_len = c16slen(result);
		if (bufsize <= result_len) {
			libc_seterrno(ERANGE);
			free(result);
			return NULL;
		}
		new_result = (char16_t *)realloc(result, bufsize * 4);
		if unlikely(!new_result) {
			free(result);
			return NULL;
		}
		return new_result;
	}
	result_len = c16slen(result);
	if (bufsize <= result_len) {
		libc_seterrno(ERANGE);
		free(result);
		return NULL;
	}
	memcpyw(buf, result, result_len + 1);
	free(result);
	return buf;
}
/*[[[end:libd_wgetcwd]]]*/

/*[[[head:libc_wfaccessat,hash:CRC-32=0x9eb0525e]]]*/
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wfaccessat)(fd_t dfd,
                                      char32_t const *file,
                                      __STDC_INT_AS_UINT_T type,
                                      atflag_t flags)
/*[[[body:libc_wfaccessat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = faccessat(dfd, used_file, type, flags);
		free(used_file);
	}
	return result;
}
/*[[[end:libc_wfaccessat]]]*/

/*[[[head:libd_wfaccessat,hash:CRC-32=0x57b9f099]]]*/
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wfaccessat)(fd_t dfd,
                                      char16_t const *file,
                                      __STDC_INT_AS_UINT_T type,
                                      atflag_t flags)
/*[[[body:libd_wfaccessat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = faccessat(dfd, used_file, type, flags);
		free(used_file);
	}
	return result;
}
/*[[[end:libd_wfaccessat]]]*/

/*[[[head:libc_wfchownat,hash:CRC-32=0xbc394209]]]*/
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wfchownat)(fd_t dfd,
                                     char32_t const *file,
                                     uid_t owner,
                                     gid_t group,
                                     atflag_t flags)
/*[[[body:libc_wfchownat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = fchownat(dfd, used_file, owner, group, flags);
		free(used_file);
	}
	return result;
}
/*[[[end:libc_wfchownat]]]*/

/*[[[head:libd_wfchownat,hash:CRC-32=0x37e2a440]]]*/
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wfchownat)(fd_t dfd,
                                     char16_t const *file,
                                     uid_t owner,
                                     gid_t group,
                                     atflag_t flags)
/*[[[body:libd_wfchownat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = fchownat(dfd, used_file, owner, group, flags);
		free(used_file);
	}
	return result;
}
/*[[[end:libd_wfchownat]]]*/

/*[[[head:libc_wsymlinkat,hash:CRC-32=0x8ef74765]]]*/
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1, 3)) int
NOTHROW_RPC(LIBKCALL libc_wsymlinkat)(char32_t const *link_text,
                                      fd_t tofd,
                                      char32_t const *target_path)
/*[[[body:libc_wsymlinkat]]]*/
{
	int result = -1;
	char *used_from, *used_to;
	used_from = libc_uchar_c32tombs(link_text);
	if unlikely(!used_from)
		goto done;
	used_to = libc_uchar_c32tombs(target_path);
	if unlikely(!used_to)
		goto done_from;
	result = symlinkat(used_from, tofd, used_to);
	free(used_to);
done_from:
	free(used_from);
done:
	return result;
}
/*[[[end:libc_wsymlinkat]]]*/

/*[[[head:libd_wsymlinkat,hash:CRC-32=0xbf05c6c3]]]*/
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1, 3)) int
NOTHROW_RPC(LIBDCALL libd_wsymlinkat)(char16_t const *link_text,
                                      fd_t tofd,
                                      char16_t const *target_path)
/*[[[body:libd_wsymlinkat]]]*/
{
	int result = -1;
	char *used_from, *used_to;
	used_from = libc_uchar_c16tombs(link_text);
	if unlikely(!used_from)
		goto done;
	used_to = libc_uchar_c16tombs(target_path);
	if unlikely(!used_to)
		goto done_from;
	result = symlinkat(used_from, tofd, used_to);
	free(used_to);
done_from:
	free(used_from);
done:
	return result;
}
/*[[[end:libd_wsymlinkat]]]*/

/*[[[head:libc_wreadlinkat,hash:CRC-32=0x6970d8df]]]*/
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBKCALL libc_wreadlinkat)(fd_t dfd,
                                       char32_t const *path,
                                       char32_t *buf,
                                       size_t buflen)
/*[[[body:libc_wreadlinkat]]]*/
{
	return libc_wfreadlinkat(dfd, path, buf, buflen, 0);
}
/*[[[end:libc_wreadlinkat]]]*/

/*[[[head:libd_wreadlinkat,hash:CRC-32=0xc18b914]]]*/
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlinkat)(fd_t dfd,
                                       char16_t const *path,
                                       char16_t *buf,
                                       size_t buflen)
/*[[[body:libd_wreadlinkat]]]*/
{
	return libd_wfreadlinkat(dfd, path, buf, buflen, 0);
}
/*[[[end:libd_wreadlinkat]]]*/

/*[[[head:libc_wfreadlinkat,hash:CRC-32=0x4fa5e505]]]*/
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBKCALL libc_wfreadlinkat)(fd_t dfd,
                                        char32_t const *path,
                                        char32_t *buf,
                                        size_t buflen,
                                        atflag_t flags)
/*[[[body:libc_wfreadlinkat]]]*/
/*AUTO*/{
	(void)dfd;
	(void)path;
	(void)buf;
	(void)buflen;
	(void)flags;
	CRT_UNIMPLEMENTEDF("wfreadlinkat(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %Ix, %" PRIxN(__SIZEOF_ATFLAG_T__) ")", dfd, path, buf, buflen, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_wfreadlinkat]]]*/

/*[[[head:libd_wfreadlinkat,hash:CRC-32=0xe2270f14]]]*/
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBDCALL libd_wfreadlinkat)(fd_t dfd,
                                        char16_t const *path,
                                        char16_t *buf,
                                        size_t buflen,
                                        atflag_t flags)
/*[[[body:libd_wfreadlinkat]]]*/
/*AUTO*/{
	(void)dfd;
	(void)path;
	(void)buf;
	(void)buflen;
	(void)flags;
	CRT_UNIMPLEMENTEDF("DOS$wfreadlinkat(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %Ix, %" PRIxN(__SIZEOF_ATFLAG_T__) ")", dfd, path, buf, buflen, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_wfreadlinkat]]]*/

/*[[[head:libc_wunlinkat,hash:CRC-32=0x9629522e]]]*/
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wunlinkat)(fd_t dfd,
                                     char32_t const *name,
                                     atflag_t flags)
/*[[[body:libc_wunlinkat]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c32tombs(name);
	if likely(used_name) {
		result = unlinkat(dfd, used_name, flags);
		free(used_name);
	}
	return result;
}
/*[[[end:libc_wunlinkat]]]*/

/*[[[head:libd_wunlinkat,hash:CRC-32=0xd9df1ca7]]]*/
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wunlinkat)(fd_t dfd,
                                     char16_t const *name,
                                     atflag_t flags)
/*[[[body:libd_wunlinkat]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c16tombs(name);
	if likely(used_name) {
		result = unlinkat(dfd, used_name, flags);
		free(used_name);
	}
	return result;
}
/*[[[end:libd_wunlinkat]]]*/

/*[[[head:libc_wgetlogin_r,hash:CRC-32=0xb19bb0f9]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wgetlogin_r)(char32_t *name,
                                       size_t name_len)
/*[[[body:libc_wgetlogin_r]]]*/
/*AUTO*/{
	(void)name;
	(void)name_len;
	CRT_UNIMPLEMENTEDF("wgetlogin_r(%p, %Ix)", name, name_len); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_wgetlogin_r]]]*/

/*[[[head:libd_wgetlogin_r,hash:CRC-32=0xc6473cdc]]]*/
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wgetlogin_r)(char16_t *name,
                                       size_t name_len)
/*[[[body:libd_wgetlogin_r]]]*/
/*AUTO*/{
	(void)name;
	(void)name_len;
	CRT_UNIMPLEMENTEDF("DOS$wgetlogin_r(%p, %Ix)", name, name_len); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_wgetlogin_r]]]*/

/*[[[head:libc_wgethostname,hash:CRC-32=0xd1b517c6]]]*/
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wgethostname)(char32_t *name,
                                        size_t buflen)
/*[[[body:libc_wgethostname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if likely(result == 0) {
		struct format_c32snprintf_data printer_data;
		struct format_8to32_data convert_data;
		size_t len = strnlen(uts.nodename, _UTSNAME_NODENAME_LENGTH);
		ssize_t width;
		printer_data.sd_buffer     = name;
		printer_data.sd_bufsiz     = buflen;
		convert_data.fd_arg        = &printer_data;
		convert_data.fd_printer    = format_c32snprintf_printer;
		convert_data.fd_incomplete = 0;
		width = format_8to32(&convert_data, uts.nodename, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {
			libc_seterrno(ERANGE);
			return -1;
		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
/*[[[end:libc_wgethostname]]]*/

/*[[[head:libd_wgethostname,hash:CRC-32=0x7e0254d6]]]*/
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wgethostname)(char16_t *name,
                                        size_t buflen)
/*[[[body:libd_wgethostname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if likely(result == 0) {
		struct format_c16snprintf_data printer_data;
		struct format_8to16_data convert_data;
		size_t len = strnlen(uts.nodename, _UTSNAME_NODENAME_LENGTH);
		ssize_t width;
		printer_data.sd_buffer     = name;
		printer_data.sd_bufsiz     = buflen;
		convert_data.fd_arg        = &printer_data;
		convert_data.fd_printer    = format_c16snprintf_printer;
		convert_data.fd_incomplete = 0;
		width = format_8to16(&convert_data, uts.nodename, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {
			libc_seterrno(ERANGE);
			return -1;
		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
/*[[[end:libd_wgethostname]]]*/

/*[[[head:libc_wsetlogin,hash:CRC-32=0xd58b641]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wsetlogin)(char32_t const *name)
/*[[[body:libc_wsetlogin]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c32tombs(name);
	if likely(used_name) {
		result = setlogin(used_name);
		free(used_name);
	}
	return result;
}
/*[[[end:libc_wsetlogin]]]*/

/*[[[head:libd_wsetlogin,hash:CRC-32=0x92e3b95b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wsetlogin)(char16_t const *name)
/*[[[body:libd_wsetlogin]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c16tombs(name);
	if likely(used_name) {
		result = setlogin(used_name);
		free(used_name);
	}
	return result;
}
/*[[[end:libd_wsetlogin]]]*/

/*[[[head:libc_wsethostname,hash:CRC-32=0x6bc0a8af]]]*/
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wsethostname)(char32_t const *name,
                                        size_t len)
/*[[[body:libc_wsethostname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c32tombsn(name, len, &used_len);
	if likely(used_name) {
		result = sethostname(used_name, used_len);
		free(used_name);
	}
	return result;
}
/*[[[end:libc_wsethostname]]]*/

/*[[[head:libd_wsethostname,hash:CRC-32=0xb8876ab1]]]*/
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wsethostname)(char16_t const *name,
                                        size_t len)
/*[[[body:libd_wsethostname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c16tombsn(name, len, &used_len);
	if likely(used_name) {
		result = sethostname(used_name, used_len);
		free(used_name);
	}
	return result;
}
/*[[[end:libd_wsethostname]]]*/

/*[[[head:libc_wgetdomainname,hash:CRC-32=0x5e18eb41]]]*/
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wgetdomainname)(char32_t *name,
                                          size_t buflen)
/*[[[body:libc_wgetdomainname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if likely(result == 0) {
		struct format_c32snprintf_data printer_data;
		struct format_8to32_data convert_data;
		size_t len = strnlen(uts.domainname, _UTSNAME_DOMAIN_LENGTH);
		ssize_t width;
		printer_data.sd_buffer     = name;
		printer_data.sd_bufsiz     = buflen;
		convert_data.fd_arg        = &printer_data;
		convert_data.fd_printer    = format_c32snprintf_printer;
		convert_data.fd_incomplete = 0;
		width = format_8to32(&convert_data, uts.domainname, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {
			libc_seterrno(ERANGE);
			return -1;
		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
/*[[[end:libc_wgetdomainname]]]*/

/*[[[head:libd_wgetdomainname,hash:CRC-32=0x66f56a57]]]*/
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wgetdomainname)(char16_t *name,
                                          size_t buflen)
/*[[[body:libd_wgetdomainname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if likely(result == 0) {
		struct format_c16snprintf_data printer_data;
		struct format_8to16_data convert_data;
		size_t len = strnlen(uts.domainname, _UTSNAME_DOMAIN_LENGTH);
		ssize_t width;
		printer_data.sd_buffer     = name;
		printer_data.sd_bufsiz     = buflen;
		convert_data.fd_arg        = &printer_data;
		convert_data.fd_printer    = format_c16snprintf_printer;
		convert_data.fd_incomplete = 0;
		width = format_8to16(&convert_data, uts.domainname, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {
			libc_seterrno(ERANGE);
			return -1;
		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}
/*[[[end:libd_wgetdomainname]]]*/

/*[[[head:libc_wsetdomainname,hash:CRC-32=0x54bd266b]]]*/
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wsetdomainname)(char32_t const *name,
                                          size_t len)
/*[[[body:libc_wsetdomainname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c32tombsn(name, len, &used_len);
	if likely(used_name) {
		result = setdomainname(used_name, used_len);
		free(used_name);
	}
	return result;
}
/*[[[end:libc_wsetdomainname]]]*/

/*[[[head:libd_wsetdomainname,hash:CRC-32=0xa62d6bff]]]*/
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wsetdomainname)(char16_t const *name,
                                          size_t len)
/*[[[body:libd_wsetdomainname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c16tombsn(name, len, &used_len);
	if likely(used_name) {
		result = setdomainname(used_name, used_len);
		free(used_name);
	}
	return result;
}
/*[[[end:libd_wsetdomainname]]]*/

/*[[[head:libc_wchroot,hash:CRC-32=0xa030a461]]]*/
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wchroot)(char32_t const *__restrict path)
/*[[[body:libc_wchroot]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c32tombs(path);
	if likely(used_path) {
		result = chroot(used_path);
		free(used_path);
	}
	return result;
}
/*[[[end:libc_wchroot]]]*/

/*[[[head:libd_wchroot,hash:CRC-32=0xab394b59]]]*/
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wchroot)(char16_t const *__restrict path)
/*[[[body:libd_wchroot]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c16tombs(path);
	if likely(used_path) {
		result = chroot(used_path);
		free(used_path);
	}
	return result;
}
/*[[[end:libd_wchroot]]]*/

/*[[[head:libc_wctermid,hash:CRC-32=0x107f11bb]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") char32_t *
NOTHROW_NCX(LIBKCALL libc_wctermid)(char32_t *s)
/*[[[body:libc_wctermid]]]*/
{
	char32_t *printer_data = s;
	struct format_8to32_data convert_data;
	char buf[L_ctermid], *ptr;
	size_t len;
	ptr = ctermid(buf);
	if unlikely(!ptr)
		return NULL;
	convert_data.fd_arg        = &printer_data;
	convert_data.fd_incomplete = 0;
	convert_data.fd_printer    = &format_c32sprintf_printer;
	len = strlen(ptr);
	if unlikely(format_8to32(&convert_data, ptr, len) < 0)
		return NULL;
	*printer_data = '\0'; /* NUL-terminate */
	return s;
}
/*[[[end:libc_wctermid]]]*/

/*[[[head:libd_wctermid,hash:CRC-32=0xd79fb817]]]*/
INTERN ATTR_SECTION(".text.crt.dos.unsorted") char16_t *
NOTHROW_NCX(LIBDCALL libd_wctermid)(char16_t *s)
/*[[[body:libd_wctermid]]]*/
{
	char16_t *printer_data = s;
	struct format_8to16_data convert_data;
	char buf[L_ctermid], *ptr;
	size_t len;
	ptr = ctermid(buf);
	if unlikely(!ptr)
		return NULL;
	convert_data.fd_arg        = &printer_data;
	convert_data.fd_incomplete = 0;
	convert_data.fd_printer    = &format_c16sprintf_printer;
	len = strlen(ptr);
	if unlikely(format_8to16(&convert_data, ptr, len) < 0)
		return NULL;
	*printer_data = '\0'; /* NUL-terminate */
	return s;
}
/*[[[end:libd_wctermid]]]*/

/*[[[head:libc_wchown,hash:CRC-32=0x2f331c1b]]]*/
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wchown)(char32_t const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libc_wchown]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = chown(used_file, owner, group);
		free(used_file);
	}
	return result;
}
/*[[[end:libc_wchown]]]*/

/*[[[head:libd_wchown,hash:CRC-32=0xcf8e8e82]]]*/
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wchown)(char16_t const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libd_wchown]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = chown(used_file, owner, group);
		free(used_file);
	}
	return result;
}
/*[[[end:libd_wchown]]]*/

/*[[[head:libc_wlink,hash:CRC-32=0x9d334238]]]*/
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wlink)(char32_t const *from,
                                 char32_t const *to)
/*[[[body:libc_wlink]]]*/
{
	return libc_wlinkat(AT_FDCWD, from, AT_FDCWD, to, 0);
}
/*[[[end:libc_wlink]]]*/

/*[[[head:libd_wlink,hash:CRC-32=0x37e67619]]]*/
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_wlink)(char16_t const *from,
                                 char16_t const *to)
/*[[[body:libd_wlink]]]*/
{
	return libd_wlinkat(AT_FDCWD, from, AT_FDCWD, to, 0);
}
/*[[[end:libd_wlink]]]*/

/*[[[head:libc_waccess,hash:CRC-32=0xcafdd590]]]*/
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_waccess)(char32_t const *file,
                                   __STDC_INT_AS_UINT_T type)
/*[[[body:libc_waccess]]]*/
{
	return libc_wfaccessat(AT_FDCWD, file, type, 0);
}
/*[[[end:libc_waccess]]]*/

/*[[[head:libd_waccess,hash:CRC-32=0xd55aa363]]]*/
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_waccess)(char16_t const *file,
                                   __STDC_INT_AS_UINT_T type)
/*[[[body:libd_waccess]]]*/
{
	return libd_wfaccessat(AT_FDCWD, file, type, 0);
}
/*[[[end:libd_waccess]]]*/

/*[[[head:libc_wunlink,hash:CRC-32=0x6721f6f9]]]*/
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wunlink)(char32_t const *file)
/*[[[body:libc_wunlink]]]*/
{
	return libc_wunlinkat(AT_FDCWD, file, 0);
}
/*[[[end:libc_wunlink]]]*/

/*[[[head:libd_wunlink,hash:CRC-32=0x1f7b767f]]]*/
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wunlink)(char16_t const *file)
/*[[[body:libd_wunlink]]]*/
{
	return libd_wunlinkat(AT_FDCWD, file, 0);
}
/*[[[end:libd_wunlink]]]*/

/*[[[head:libc_wrmdir,hash:CRC-32=0x179689e9]]]*/
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wrmdir)(char32_t const *path)
/*[[[body:libc_wrmdir]]]*/
{
	return libc_wunlinkat(AT_FDCWD, path, AT_REMOVEDIR);
}
/*[[[end:libc_wrmdir]]]*/

/*[[[head:libd_wrmdir,hash:CRC-32=0xe1a8c26f]]]*/
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wrmdir)(char16_t const *path)
/*[[[body:libd_wrmdir]]]*/
{
	return libd_wunlinkat(AT_FDCWD, path, AT_REMOVEDIR);
}
/*[[[end:libd_wrmdir]]]*/

/*[[[head:libc_weuidaccess,hash:CRC-32=0x1a74ab24]]]*/
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_weuidaccess)(char32_t const *file,
                                       __STDC_INT_AS_UINT_T type)
/*[[[body:libc_weuidaccess]]]*/
{
	return libc_wfaccessat(AT_FDCWD, file, type, AT_EACCESS);
}
/*[[[end:libc_weuidaccess]]]*/

/*[[[head:libd_weuidaccess,hash:CRC-32=0x217db802]]]*/
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_weuidaccess)(char16_t const *file,
                                       __STDC_INT_AS_UINT_T type)
/*[[[body:libd_weuidaccess]]]*/
{
	return libd_wfaccessat(AT_FDCWD, file, type, AT_EACCESS);
}
/*[[[end:libd_weuidaccess]]]*/

/*[[[head:libc_wget_current_dir_name,hash:CRC-32=0x1b575bc4]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_MALLOC WUNUSED char32_t *
NOTHROW_RPC(LIBKCALL libc_wget_current_dir_name)(void)
/*[[[body:libc_wget_current_dir_name]]]*/
{
	char *utf8_path;
	char32_t *result;
	utf8_path = get_current_dir_name();
	if unlikely(!utf8_path)
		return NULL;
	result = libc_uchar_mbstoc32(utf8_path);
	free(utf8_path);
	return result;
}
/*[[[end:libc_wget_current_dir_name]]]*/

/*[[[head:libd_wget_current_dir_name,hash:CRC-32=0xe2fa0038]]]*/
INTERN ATTR_SECTION(".text.crt.dos.unsorted") ATTR_MALLOC WUNUSED char16_t *
NOTHROW_RPC(LIBDCALL libd_wget_current_dir_name)(void)
/*[[[body:libd_wget_current_dir_name]]]*/
{
	char *utf8_path;
	char16_t *result;
	utf8_path = get_current_dir_name();
	if unlikely(!utf8_path)
		return NULL;
	result = libc_uchar_mbstoc16(utf8_path);
	free(utf8_path);
	return result;
}
/*[[[end:libd_wget_current_dir_name]]]*/

/*[[[head:libc_wlchown,hash:CRC-32=0x454b7451]]]*/
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wlchown)(char32_t const *file,
                                   uid_t owner,
                                   gid_t group)
/*[[[body:libc_wlchown]]]*/
{
	return libc_wfchownat(AT_FDCWD, file, owner, group, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:libc_wlchown]]]*/

/*[[[head:libd_wlchown,hash:CRC-32=0x48758deb]]]*/
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wlchown)(char16_t const *file,
                                   uid_t owner,
                                   gid_t group)
/*[[[body:libd_wlchown]]]*/
{
	return libd_wfchownat(AT_FDCWD, file, owner, group, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:libd_wlchown]]]*/

/*[[[head:libc_wtruncate,hash:CRC-32=0x716a1bf3]]]*/
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wtruncate)(char32_t const *file,
                                     __PIO_OFFSET length)
/*[[[body:libc_wtruncate]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = truncate(used_file, length);
		free(used_file);
	}
	return result;
}
/*[[[end:libc_wtruncate]]]*/

/*[[[head:libd_wtruncate,hash:CRC-32=0xf601bee4]]]*/
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wtruncate)(char16_t const *file,
                                     __PIO_OFFSET length)
/*[[[body:libd_wtruncate]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = truncate(used_file, length);
		free(used_file);
	}
	return result;
}
/*[[[end:libd_wtruncate]]]*/

/*[[[head:libc_wtruncate64,hash:CRC-32=0x3def1a44]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_wtruncate64, libc_wtruncate);
#else /* MAGIC:alias */
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wtruncate64)(char32_t const *file,
                                       __PIO_OFFSET64 length)
/*[[[body:libc_wtruncate64]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = truncate64(used_file, length);
		free(used_file);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_wtruncate64]]]*/

/*[[[head:libd_wtruncate64,hash:CRC-32=0x87a0167f]]]*/
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wtruncate64)(char16_t const *file,
                                       __PIO_OFFSET64 length)
/*[[[body:libd_wtruncate64]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = truncate64(used_file, length);
		free(used_file);
	}
	return result;
}
/*[[[end:libd_wtruncate64]]]*/

/*[[[head:libc_wsymlink,hash:CRC-32=0x83f5e635]]]*/
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wsymlink)(char32_t const *link_text,
                                    char32_t const *target_path)
/*[[[body:libc_wsymlink]]]*/
{
	return libc_wsymlinkat(link_text, AT_FDCWD, target_path);
}
/*[[[end:libc_wsymlink]]]*/

/*[[[head:libd_wsymlink,hash:CRC-32=0xe0595e73]]]*/
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_wsymlink)(char16_t const *link_text,
                                    char16_t const *target_path)
/*[[[body:libd_wsymlink]]]*/
{
	return libd_wsymlinkat(link_text, AT_FDCWD, target_path);
}
/*[[[end:libd_wsymlink]]]*/

/*[[[head:libc_wreadlink,hash:CRC-32=0xbb5a15d5]]]*/
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1, 2)) ssize_t
NOTHROW_RPC(LIBKCALL libc_wreadlink)(char32_t const *path,
                                     char32_t *buf,
                                     size_t buflen)
/*[[[body:libc_wreadlink]]]*/
{
	return libc_wfreadlinkat(AT_FDCWD, path, buf, buflen, 0);
}
/*[[[end:libc_wreadlink]]]*/

/*[[[head:libd_wreadlink,hash:CRC-32=0x2bb64aea]]]*/
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1, 2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlink)(char16_t const *path,
                                     char16_t *buf,
                                     size_t buflen)
/*[[[body:libd_wreadlink]]]*/
{
	return libd_wfreadlinkat(AT_FDCWD, path, buf, buflen, 0);
}
/*[[[end:libd_wreadlink]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x33edbb3b]]]*/
DEFINE_PUBLIC_ALIAS(DOS$wttyname, libd_wttyname);
DEFINE_PUBLIC_ALIAS(wttyname, libc_wttyname);
DEFINE_PUBLIC_ALIAS(DOS$wttyname_r, libd_wttyname_r);
DEFINE_PUBLIC_ALIAS(wttyname_r, libc_wttyname_r);
DEFINE_PUBLIC_ALIAS(DOS$wgetlogin, libd_wgetlogin);
DEFINE_PUBLIC_ALIAS(wgetlogin, libc_wgetlogin);
DEFINE_PUBLIC_ALIAS(DOS$wchown, libd_wchown);
DEFINE_PUBLIC_ALIAS(wchown, libc_wchown);
DEFINE_PUBLIC_ALIAS(DOS$wpathconf, libd_wpathconf);
DEFINE_PUBLIC_ALIAS(wpathconf, libc_wpathconf);
DEFINE_PUBLIC_ALIAS(DOS$wlink, libd_wlink);
DEFINE_PUBLIC_ALIAS(wlink, libc_wlink);
DEFINE_PUBLIC_ALIAS(DOS$waccess, libd_waccess);
DEFINE_PUBLIC_ALIAS(waccess, libc_waccess);
DEFINE_PUBLIC_ALIAS(DOS$_wchdir, libd_wchdir);
DEFINE_PUBLIC_ALIAS(DOS$wchdir, libd_wchdir);
DEFINE_PUBLIC_ALIAS(wchdir, libc_wchdir);
DEFINE_PUBLIC_ALIAS(DOS$_wgetcwd, libd_wgetcwd);
DEFINE_PUBLIC_ALIAS(DOS$wgetcwd, libd_wgetcwd);
DEFINE_PUBLIC_ALIAS(wgetcwd, libc_wgetcwd);
DEFINE_PUBLIC_ALIAS(DOS$_wunlink, libd_wunlink);
DEFINE_PUBLIC_ALIAS(DOS$wunlink, libd_wunlink);
DEFINE_PUBLIC_ALIAS(wunlink, libc_wunlink);
DEFINE_PUBLIC_ALIAS(DOS$_wrmdir, libd_wrmdir);
DEFINE_PUBLIC_ALIAS(DOS$wrmdir, libd_wrmdir);
DEFINE_PUBLIC_ALIAS(wrmdir, libc_wrmdir);
DEFINE_PUBLIC_ALIAS(DOS$weuidaccess, libd_weuidaccess);
DEFINE_PUBLIC_ALIAS(weuidaccess, libc_weuidaccess);
DEFINE_PUBLIC_ALIAS(DOS$wget_current_dir_name, libd_wget_current_dir_name);
DEFINE_PUBLIC_ALIAS(wget_current_dir_name, libc_wget_current_dir_name);
DEFINE_PUBLIC_ALIAS(DOS$wfaccessat, libd_wfaccessat);
DEFINE_PUBLIC_ALIAS(wfaccessat, libc_wfaccessat);
DEFINE_PUBLIC_ALIAS(DOS$wfchownat, libd_wfchownat);
DEFINE_PUBLIC_ALIAS(wfchownat, libc_wfchownat);
DEFINE_PUBLIC_ALIAS(DOS$wlinkat, libd_wlinkat);
DEFINE_PUBLIC_ALIAS(wlinkat, libc_wlinkat);
DEFINE_PUBLIC_ALIAS(DOS$wsymlinkat, libd_wsymlinkat);
DEFINE_PUBLIC_ALIAS(wsymlinkat, libc_wsymlinkat);
DEFINE_PUBLIC_ALIAS(DOS$wreadlinkat, libd_wreadlinkat);
DEFINE_PUBLIC_ALIAS(wreadlinkat, libc_wreadlinkat);
DEFINE_PUBLIC_ALIAS(DOS$wfreadlinkat, libd_wfreadlinkat);
DEFINE_PUBLIC_ALIAS(wfreadlinkat, libc_wfreadlinkat);
DEFINE_PUBLIC_ALIAS(DOS$wunlinkat, libd_wunlinkat);
DEFINE_PUBLIC_ALIAS(wunlinkat, libc_wunlinkat);
DEFINE_PUBLIC_ALIAS(DOS$wlchown, libd_wlchown);
DEFINE_PUBLIC_ALIAS(wlchown, libc_wlchown);
DEFINE_PUBLIC_ALIAS(DOS$wtruncate, libd_wtruncate);
DEFINE_PUBLIC_ALIAS(wtruncate, libc_wtruncate);
DEFINE_PUBLIC_ALIAS(DOS$wtruncate64, libd_wtruncate64);
DEFINE_PUBLIC_ALIAS(wtruncate64, libc_wtruncate64);
DEFINE_PUBLIC_ALIAS(DOS$wsymlink, libd_wsymlink);
DEFINE_PUBLIC_ALIAS(wsymlink, libc_wsymlink);
DEFINE_PUBLIC_ALIAS(DOS$wreadlink, libd_wreadlink);
DEFINE_PUBLIC_ALIAS(wreadlink, libc_wreadlink);
DEFINE_PUBLIC_ALIAS(DOS$wgetlogin_r, libd_wgetlogin_r);
DEFINE_PUBLIC_ALIAS(wgetlogin_r, libc_wgetlogin_r);
DEFINE_PUBLIC_ALIAS(DOS$wgethostname, libd_wgethostname);
DEFINE_PUBLIC_ALIAS(wgethostname, libc_wgethostname);
DEFINE_PUBLIC_ALIAS(DOS$wsetlogin, libd_wsetlogin);
DEFINE_PUBLIC_ALIAS(wsetlogin, libc_wsetlogin);
DEFINE_PUBLIC_ALIAS(DOS$wsethostname, libd_wsethostname);
DEFINE_PUBLIC_ALIAS(wsethostname, libc_wsethostname);
DEFINE_PUBLIC_ALIAS(DOS$wgetdomainname, libd_wgetdomainname);
DEFINE_PUBLIC_ALIAS(wgetdomainname, libc_wgetdomainname);
DEFINE_PUBLIC_ALIAS(DOS$wsetdomainname, libd_wsetdomainname);
DEFINE_PUBLIC_ALIAS(wsetdomainname, libc_wsetdomainname);
DEFINE_PUBLIC_ALIAS(DOS$wchroot, libd_wchroot);
DEFINE_PUBLIC_ALIAS(wchroot, libc_wchroot);
DEFINE_PUBLIC_ALIAS(DOS$wctermid, libd_wctermid);
DEFINE_PUBLIC_ALIAS(wctermid, libc_wctermid);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C */
