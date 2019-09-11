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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C
#define GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C 1

#include "../api.h"
/**/

#include "../libc/uchar.h"
#include "parts.wchar.unistd.h"
#include <unistd.h>
#include <uchar.h>
#include <fcntl.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:wttyname,hash:0xf6f504cf]]]*/
/* >> wttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wttyname") char32_t *
NOTHROW_RPC(LIBCCALL libc_wttyname)(fd_t fd)
/*[[[body:wttyname]]]*/
{
	CRT_UNIMPLEMENTED("wttyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:wttyname]]]*/

/*[[[head:DOS$wttyname,hash:0x77871921]]]*/
/* >> wttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wttyname") char16_t *
NOTHROW_RPC(LIBDCALL libd_wttyname)(fd_t fd)
/*[[[body:DOS$wttyname]]]*/
{
	CRT_UNIMPLEMENTED("wttyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$wttyname]]]*/

/*[[[head:wttyname_r,hash:0x3f91befb]]]*/
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wttyname_r") int
NOTHROW_RPC(LIBCCALL libc_wttyname_r)(fd_t fd,
                                      char32_t *buf,
                                      size_t buflen)
/*[[[body:wttyname_r]]]*/
{
	CRT_UNIMPLEMENTED("wttyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wttyname_r]]]*/

/*[[[head:DOS$wttyname_r,hash:0x806113fd]]]*/
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wttyname_r") int
NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd,
                                      char16_t *buf,
                                      size_t buflen)
/*[[[body:DOS$wttyname_r]]]*/
{
	CRT_UNIMPLEMENTED("wttyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wttyname_r]]]*/

/*[[[head:wgetlogin,hash:0xaf2bfbfa]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wgetlogin") char32_t *
NOTHROW_NCX(LIBCCALL libc_wgetlogin)(void)
/*[[[body:wgetlogin]]]*/
{
	CRT_UNIMPLEMENTED("wgetlogin"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:wgetlogin]]]*/

/*[[[head:DOS$wgetlogin,hash:0x9fed067e]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wgetlogin") char16_t *
NOTHROW_NCX(LIBDCALL libd_wgetlogin)(void)
/*[[[body:DOS$wgetlogin]]]*/
{
	CRT_UNIMPLEMENTED("wgetlogin"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$wgetlogin]]]*/

/*[[[head:wpathconf,hash:0xa2d82e95]]]*/
/* >> wpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wpathconf") long int
NOTHROW_RPC(LIBCCALL libc_wpathconf)(char32_t const *path,
                                     int name)
/*[[[body:wpathconf]]]*/
{
	long int result;
	char *used_path;
	used_path = libc_uchar_c32tombs(path);
	if unlikely(!used_path)
		return -1;
	result = pathconf(used_path, name);
	libc_uchar_free(used_path);
	return result;
}
/*[[[end:wpathconf]]]*/

/*[[[head:DOS$wpathconf,hash:0xc8c9496f]]]*/
/* >> wpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wpathconf") long int
NOTHROW_RPC(LIBDCALL libd_wpathconf)(char16_t const *path,
                                     int name)
/*[[[body:DOS$wpathconf]]]*/
{
	long int result;
	char *used_path;
	used_path = libc_uchar_c16tombs(path);
	if unlikely(!used_path)
		return -1;
	result = pathconf(used_path, name);
	libc_uchar_free(used_path);
	return result;
}
/*[[[end:DOS$wpathconf]]]*/

/*[[[head:wlinkat,hash:0x21a8cc91]]]*/
/* >> wlinkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTERN NONNULL((2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wlinkat") int
NOTHROW_RPC(LIBCCALL libc_wlinkat)(fd_t fromfd,
                                   char32_t const *from,
                                   fd_t tofd,
                                   char32_t const *to,
                                   atflag_t flags)
/*[[[body:wlinkat]]]*/
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
	libc_uchar_free(used_to);
done_from:
	libc_uchar_free(used_from);
done:
	return result;
}
/*[[[end:wlinkat]]]*/

/*[[[head:DOS$wlinkat,hash:0x80ff0d14]]]*/
/* >> wlinkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTERN NONNULL((2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wlinkat") int
NOTHROW_RPC(LIBDCALL libd_wlinkat)(fd_t fromfd,
                                   char16_t const *from,
                                   fd_t tofd,
                                   char16_t const *to,
                                   atflag_t flags)
/*[[[body:DOS$wlinkat]]]*/
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
	libc_uchar_free(used_to);
done_from:
	libc_uchar_free(used_from);
done:
	return result;
}
/*[[[end:DOS$wlinkat]]]*/

/*[[[head:wchdir,hash:0x26fc5611]]]*/
/* >> wchdir(2)
 * Change the current working directory to `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wchdir") int
NOTHROW_RPC(LIBCCALL libc_wchdir)(char32_t const *path)
/*[[[body:wchdir]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c32tombs(path);
	if likely(used_path) {
		result = chdir(used_path);
		libc_uchar_free(used_path);
	}
	return result;
}
/*[[[end:wchdir]]]*/

/*[[[head:DOS$wchdir,hash:0x372dfdb]]]*/
/* >> wchdir(2)
 * Change the current working directory to `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wchdir") int
NOTHROW_RPC(LIBDCALL libd_wchdir)(char16_t const *path)
/*[[[body:DOS$wchdir]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c16tombs(path);
	if likely(used_path) {
		result = chdir(used_path);
		libc_uchar_free(used_path);
	}
	return result;
}
/*[[[end:DOS$wchdir]]]*/

/*[[[head:wgetcwd,hash:0x38106f72]]]*/
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wgetcwd") char32_t *
NOTHROW_RPC(LIBCCALL libc_wgetcwd)(char32_t *buf,
                                   size_t bufsize)
/*[[[body:wgetcwd]]]*/
{
	CRT_UNIMPLEMENTED("wgetcwd"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:wgetcwd]]]*/

/*[[[head:DOS$wgetcwd,hash:0xe9f69ad6]]]*/
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wgetcwd") char16_t *
NOTHROW_RPC(LIBDCALL libd_wgetcwd)(char16_t *buf,
                                   size_t bufsize)
/*[[[body:DOS$wgetcwd]]]*/
{
	CRT_UNIMPLEMENTED("wgetcwd"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$wgetcwd]]]*/

/*[[[head:wfaccessat,hash:0xb4e000e9]]]*/
/* >> wfaccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wfaccessat") int
NOTHROW_RPC(LIBCCALL libc_wfaccessat)(fd_t dfd,
                                      char32_t const *file,
                                      int type,
                                      atflag_t flags)
/*[[[body:wfaccessat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = faccessat(dfd, used_file, type, flags);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:wfaccessat]]]*/

/*[[[head:DOS$wfaccessat,hash:0x9b7983b8]]]*/
/* >> wfaccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wfaccessat") int
NOTHROW_RPC(LIBDCALL libd_wfaccessat)(fd_t dfd,
                                      char16_t const *file,
                                      int type,
                                      atflag_t flags)
/*[[[body:DOS$wfaccessat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = faccessat(dfd, used_file, type, flags);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:DOS$wfaccessat]]]*/

/*[[[head:wfchownat,hash:0x8dc061e3]]]*/
/* >> wfchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wfchownat") int
NOTHROW_RPC(LIBCCALL libc_wfchownat)(fd_t dfd,
                                     char32_t const *file,
                                     uid_t owner,
                                     gid_t group,
                                     atflag_t flags)
/*[[[body:wfchownat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = fchownat(dfd, used_file, owner, group, flags);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:wfchownat]]]*/

/*[[[head:DOS$wfchownat,hash:0x372a8ffe]]]*/
/* >> wfchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wfchownat") int
NOTHROW_RPC(LIBDCALL libd_wfchownat)(fd_t dfd,
                                     char16_t const *file,
                                     uid_t owner,
                                     gid_t group,
                                     atflag_t flags)
/*[[[body:DOS$wfchownat]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = fchownat(dfd, used_file, owner, group, flags);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:DOS$wfchownat]]]*/

/*[[[head:wsymlinkat,hash:0x96f055fe]]]*/
/* >> wsymlinkat(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TOFD:TO' */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wsymlinkat") int
NOTHROW_RPC(LIBCCALL libc_wsymlinkat)(char32_t const *from,
                                      fd_t tofd,
                                      char32_t const *to)
/*[[[body:wsymlinkat]]]*/
{
	int result = -1;
	char *used_from, *used_to;
	used_from = libc_uchar_c32tombs(from);
	if unlikely(!used_from)
		goto done;
	used_to = libc_uchar_c32tombs(to);
	if unlikely(!used_to)
		goto done_from;
	result = symlinkat(used_from, tofd, used_to);
	libc_uchar_free(used_to);
done_from:
	libc_uchar_free(used_from);
done:
	return result;
}
/*[[[end:wsymlinkat]]]*/

/*[[[head:DOS$wsymlinkat,hash:0x77472c1f]]]*/
/* >> wsymlinkat(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TOFD:TO' */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wsymlinkat") int
NOTHROW_RPC(LIBDCALL libd_wsymlinkat)(char16_t const *from,
                                      fd_t tofd,
                                      char16_t const *to)
/*[[[body:DOS$wsymlinkat]]]*/
{
	int result = -1;
	char *used_from, *used_to;
	used_from = libc_uchar_c16tombs(from);
	if unlikely(!used_from)
		goto done;
	used_to = libc_uchar_c16tombs(to);
	if unlikely(!used_to)
		goto done_from;
	result = symlinkat(used_from, tofd, used_to);
	libc_uchar_free(used_to);
done_from:
	libc_uchar_free(used_from);
done:
	return result;
}
/*[[[end:DOS$wsymlinkat]]]*/

/*[[[head:wreadlinkat,hash:0xfd675ca2]]]*/
/* >> wreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wreadlinkat") ssize_t
NOTHROW_RPC(LIBCCALL libc_wreadlinkat)(fd_t dfd,
                                       char32_t const *__restrict path,
                                       char32_t *__restrict buf,
                                       size_t buflen)
/*[[[body:wreadlinkat]]]*/
{
	return libc_wfreadlinkat(dfd, path, buf, buflen, 0);
}
/*[[[end:wreadlinkat]]]*/

/*[[[head:DOS$wreadlinkat,hash:0x8af43a35]]]*/
/* >> wreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wreadlinkat") ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlinkat)(fd_t dfd,
                                       char16_t const *__restrict path,
                                       char16_t *__restrict buf,
                                       size_t buflen)
/*[[[body:DOS$wreadlinkat]]]*/
{
	return libd_wfreadlinkat(dfd, path, buf, buflen, 0);
}
/*[[[end:DOS$wreadlinkat]]]*/

/*[[[head:wfreadlinkat,hash:0x9227c64c]]]*/
/* >> wfreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wfreadlinkat") ssize_t
NOTHROW_RPC(LIBCCALL libc_wfreadlinkat)(fd_t dfd,
                                        char32_t const *__restrict path,
                                        char32_t *__restrict buf,
                                        size_t buflen,
                                        atflag_t flags)
/*[[[body:wfreadlinkat]]]*/
{
	CRT_UNIMPLEMENTED("wfreadlinkat"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wfreadlinkat]]]*/

/*[[[head:DOS$wfreadlinkat,hash:0xebddadf]]]*/
/* >> wfreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wfreadlinkat") ssize_t
NOTHROW_RPC(LIBDCALL libd_wfreadlinkat)(fd_t dfd,
                                        char16_t const *__restrict path,
                                        char16_t *__restrict buf,
                                        size_t buflen,
                                        atflag_t flags)
/*[[[body:DOS$wfreadlinkat]]]*/
{
	CRT_UNIMPLEMENTED("wfreadlinkat"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wfreadlinkat]]]*/

/*[[[head:wunlinkat,hash:0xc40f36f6]]]*/
/* >> wunlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wunlinkat") int
NOTHROW_RPC(LIBCCALL libc_wunlinkat)(fd_t dfd,
                                     char32_t const *name,
                                     atflag_t flags)
/*[[[body:wunlinkat]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c32tombs(name);
	if likely(used_name) {
		result = unlinkat(dfd, used_name, flags);
		libc_uchar_free(used_name);
	}
	return result;
}
/*[[[end:wunlinkat]]]*/

/*[[[head:DOS$wunlinkat,hash:0x608225e9]]]*/
/* >> wunlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wunlinkat") int
NOTHROW_RPC(LIBDCALL libd_wunlinkat)(fd_t dfd,
                                     char16_t const *name,
                                     atflag_t flags)
/*[[[body:DOS$wunlinkat]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c16tombs(name);
	if likely(used_name) {
		result = unlinkat(dfd, used_name, flags);
		libc_uchar_free(used_name);
	}
	return result;
}
/*[[[end:DOS$wunlinkat]]]*/

/*[[[head:wgetlogin_r,hash:0xae70d3e0]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wgetlogin_r") int
NOTHROW_RPC(LIBCCALL libc_wgetlogin_r)(char32_t *name,
                                       size_t name_len)
/*[[[body:wgetlogin_r]]]*/
{
	CRT_UNIMPLEMENTED("wgetlogin_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wgetlogin_r]]]*/

/*[[[head:DOS$wgetlogin_r,hash:0x44bc6bc3]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wgetlogin_r") int
NOTHROW_RPC(LIBDCALL libd_wgetlogin_r)(char16_t *name,
                                       size_t name_len)
/*[[[body:DOS$wgetlogin_r]]]*/
{
	CRT_UNIMPLEMENTED("wgetlogin_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wgetlogin_r]]]*/

/*[[[head:wgethostname,hash:0x940eeecc]]]*/
/* >> wgethostname(3)
 * Return the name assigned to the hosting machine, as set by `wsethostname(2)' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wgethostname") int
NOTHROW_NCX(LIBCCALL libc_wgethostname)(char32_t *name,
                                        size_t buflen)
/*[[[body:wgethostname]]]*/
{
	CRT_UNIMPLEMENTED("wgethostname"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wgethostname]]]*/

/*[[[head:DOS$wgethostname,hash:0xa7ca1354]]]*/
/* >> wgethostname(3)
 * Return the name assigned to the hosting machine, as set by `wsethostname(2)' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wgethostname") int
NOTHROW_NCX(LIBDCALL libd_wgethostname)(char16_t *name,
                                        size_t buflen)
/*[[[body:DOS$wgethostname]]]*/
{
	CRT_UNIMPLEMENTED("wgethostname"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wgethostname]]]*/

/*[[[head:wsetlogin,hash:0x24f90e3e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wsetlogin") int
NOTHROW_NCX(LIBCCALL libc_wsetlogin)(char32_t const *name)
/*[[[body:wsetlogin]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c32tombs(name);
	if likely(used_name) {
		result = setlogin(used_name);
		libc_uchar_free(used_name);
	}
	return result;
}
/*[[[end:wsetlogin]]]*/

/*[[[head:DOS$wsetlogin,hash:0x4bdcacf9]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wsetlogin") int
NOTHROW_NCX(LIBDCALL libd_wsetlogin)(char16_t const *name)
/*[[[body:DOS$wsetlogin]]]*/
{
	int result = -1;
	char *used_name;
	used_name = libc_uchar_c16tombs(name);
	if likely(used_name) {
		result = setlogin(used_name);
		libc_uchar_free(used_name);
	}
	return result;
}
/*[[[end:DOS$wsetlogin]]]*/

/*[[[head:wsethostname,hash:0x436c08c3]]]*/
/* >> wsethostname(2)
 * Set the name of the hosting machine */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wsethostname") int
NOTHROW_NCX(LIBCCALL libc_wsethostname)(char32_t const *name,
                                        size_t len)
/*[[[body:wsethostname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c32tombsn(name, len, &used_len);
	if likely(used_name) {
		result = sethostname(used_name, used_len);
		libc_uchar_freen(used_name, used_len);
	}
	return result;
}
/*[[[end:wsethostname]]]*/

/*[[[head:DOS$wsethostname,hash:0xcdab178a]]]*/
/* >> wsethostname(2)
 * Set the name of the hosting machine */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wsethostname") int
NOTHROW_NCX(LIBDCALL libd_wsethostname)(char16_t const *name,
                                        size_t len)
/*[[[body:DOS$wsethostname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c16tombsn(name, len, &used_len);
	if likely(used_name) {
		result = sethostname(used_name, used_len);
		libc_uchar_freen(used_name, used_len);
	}
	return result;
}
/*[[[end:DOS$wsethostname]]]*/

/*[[[head:wgetdomainname,hash:0xeb137c64]]]*/
/* >> wgetdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `wsetdomainname(2)' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wgetdomainname") int
NOTHROW_NCX(LIBCCALL libc_wgetdomainname)(char32_t *name,
                                          size_t buflen)
/*[[[body:wgetdomainname]]]*/
{
	CRT_UNIMPLEMENTED("wgetdomainname"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wgetdomainname]]]*/

/*[[[head:DOS$wgetdomainname,hash:0x3b560f]]]*/
/* >> wgetdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `wsetdomainname(2)' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wgetdomainname") int
NOTHROW_NCX(LIBDCALL libd_wgetdomainname)(char16_t *name,
                                          size_t buflen)
/*[[[body:DOS$wgetdomainname]]]*/
{
	CRT_UNIMPLEMENTED("wgetdomainname"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wgetdomainname]]]*/

/*[[[head:wsetdomainname,hash:0xc215341b]]]*/
/* >> wsetdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wsetdomainname") int
NOTHROW_NCX(LIBCCALL libc_wsetdomainname)(char32_t const *name,
                                          size_t len)
/*[[[body:wsetdomainname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c32tombsn(name, len, &used_len);
	if likely(used_name) {
		result = setdomainname(used_name, used_len);
		libc_uchar_freen(used_name, used_len);
	}
	return result;
}
/*[[[end:wsetdomainname]]]*/

/*[[[head:DOS$wsetdomainname,hash:0x8b6dc583]]]*/
/* >> wsetdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wsetdomainname") int
NOTHROW_NCX(LIBDCALL libd_wsetdomainname)(char16_t const *name,
                                          size_t len)
/*[[[body:DOS$wsetdomainname]]]*/
{
	int result = -1;
	char *used_name;
	size_t used_len;
	used_name = libc_uchar_c16tombsn(name, len, &used_len);
	if likely(used_name) {
		result = setdomainname(used_name, used_len);
		libc_uchar_freen(used_name, used_len);
	}
	return result;
}
/*[[[end:DOS$wsetdomainname]]]*/

/*[[[head:wchroot,hash:0x98d23583]]]*/
/* >> wchroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wchroot") int
NOTHROW_RPC(LIBCCALL libc_wchroot)(char32_t const *__restrict path)
/*[[[body:wchroot]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c32tombs(path);
	if likely(used_path) {
		result = chroot(used_path);
		libc_uchar_free(used_path);
	}
	return result;
}
/*[[[end:wchroot]]]*/

/*[[[head:DOS$wchroot,hash:0x6f698556]]]*/
/* >> wchroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wchroot") int
NOTHROW_RPC(LIBDCALL libd_wchroot)(char16_t const *__restrict path)
/*[[[body:DOS$wchroot]]]*/
{
	int result = -1;
	char *used_path;
	used_path = libc_uchar_c16tombs(path);
	if likely(used_path) {
		result = chroot(used_path);
		libc_uchar_free(used_path);
	}
	return result;
}
/*[[[end:DOS$wchroot]]]*/

/*[[[head:wctermid,hash:0x90689809]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wctermid") char32_t *
NOTHROW_NCX(LIBCCALL libc_wctermid)(char32_t *s)
/*[[[body:wctermid]]]*/
{
	CRT_UNIMPLEMENTED("wctermid"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:wctermid]]]*/

/*[[[head:DOS$wctermid,hash:0x639baf88]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wctermid") char16_t *
NOTHROW_NCX(LIBDCALL libd_wctermid)(char16_t *s)
/*[[[body:DOS$wctermid]]]*/
{
	CRT_UNIMPLEMENTED("wctermid"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$wctermid]]]*/

/*[[[head:wchown,hash:0x656e769a]]]*/
/* >> wchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wchown") int
NOTHROW_RPC(LIBCCALL libc_wchown)(char32_t const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:wchown]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = chown(used_file, owner, group);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:wchown]]]*/

/*[[[head:DOS$wchown,hash:0xdc258c15]]]*/
/* >> wchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wchown") int
NOTHROW_RPC(LIBDCALL libd_wchown)(char16_t const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:DOS$wchown]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = chown(used_file, owner, group);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:DOS$wchown]]]*/

/*[[[head:wlink,hash:0x4efc9ee8]]]*/
/* >> wlink(2)
 * Create a hard link from `FROM', leading to `TO' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wlink") int
NOTHROW_RPC(LIBCCALL libc_wlink)(char32_t const *from,
                                 char32_t const *to)
/*[[[body:wlink]]]*/
{
	return libc_wlinkat(AT_FDCWD, from, AT_FDCWD, to, 0);
}
/*[[[end:wlink]]]*/

/*[[[head:DOS$wlink,hash:0x44de9cec]]]*/
/* >> wlink(2)
 * Create a hard link from `FROM', leading to `TO' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wlink") int
NOTHROW_RPC(LIBDCALL libd_wlink)(char16_t const *from,
                                 char16_t const *to)
/*[[[body:DOS$wlink]]]*/
{
	return libd_wlinkat(AT_FDCWD, from, AT_FDCWD, to, 0);
}
/*[[[end:DOS$wlink]]]*/

/*[[[head:waccess,hash:0x9f650ed7]]]*/
/* >> waccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.waccess") int
NOTHROW_RPC(LIBCCALL libc_waccess)(char32_t const *file,
                                   int type)
/*[[[body:waccess]]]*/
{
	return libc_wfaccessat(AT_FDCWD, file, type, 0);
}
/*[[[end:waccess]]]*/

/*[[[head:DOS$waccess,hash:0x33e0617f]]]*/
/* >> waccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.waccess") int
NOTHROW_RPC(LIBDCALL libd_waccess)(char16_t const *file,
                                   int type)
/*[[[body:DOS$waccess]]]*/
{
	return libd_wfaccessat(AT_FDCWD, file, type, 0);
}
/*[[[end:DOS$waccess]]]*/

/*[[[head:wunlink,hash:0x5094f28b]]]*/
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wunlink") int
NOTHROW_RPC(LIBCCALL libc_wunlink)(char32_t const *file)
/*[[[body:wunlink]]]*/
{
	return libc_wunlinkat(AT_FDCWD, file, 0);
}
/*[[[end:wunlink]]]*/

/*[[[head:DOS$wunlink,hash:0x70260ea7]]]*/
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wunlink") int
NOTHROW_RPC(LIBDCALL libd_wunlink)(char16_t const *file)
/*[[[body:DOS$wunlink]]]*/
{
	return libd_wunlinkat(AT_FDCWD, file, 0);
}
/*[[[end:DOS$wunlink]]]*/

/*[[[head:wrmdir,hash:0x7d2af5e2]]]*/
/* >> wrmdir(2)
 * Remove a directory referred to by `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wrmdir") int
NOTHROW_RPC(LIBCCALL libc_wrmdir)(char32_t const *path)
/*[[[body:wrmdir]]]*/
{
	return libc_wunlinkat(AT_FDCWD, path, AT_REMOVEDIR);
}
/*[[[end:wrmdir]]]*/

/*[[[head:DOS$wrmdir,hash:0xd499bc5e]]]*/
/* >> wrmdir(2)
 * Remove a directory referred to by `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wrmdir") int
NOTHROW_RPC(LIBDCALL libd_wrmdir)(char16_t const *path)
/*[[[body:DOS$wrmdir]]]*/
{
	return libd_wunlinkat(AT_FDCWD, path, AT_REMOVEDIR);
}
/*[[[end:DOS$wrmdir]]]*/

/*[[[head:weuidaccess,hash:0xf3e45cde]]]*/
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.weuidaccess") int
NOTHROW_RPC(LIBCCALL libc_weuidaccess)(char32_t const *file,
                                       int type)
/*[[[body:weuidaccess]]]*/
{
	return libc_wfaccessat(AT_FDCWD, file, type, AT_EACCESS);
}
/*[[[end:weuidaccess]]]*/

/*[[[head:DOS$weuidaccess,hash:0x9468b452]]]*/
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.weuidaccess") int
NOTHROW_RPC(LIBDCALL libd_weuidaccess)(char16_t const *file,
                                       int type)
/*[[[body:DOS$weuidaccess]]]*/
{
	return libd_wfaccessat(AT_FDCWD, file, type, AT_EACCESS);
}
/*[[[end:DOS$weuidaccess]]]*/

/*[[[head:wget_current_dir_name,hash:0x82faff9]]]*/
INTERN WUNUSED ATTR_MALLOC
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wget_current_dir_name") char32_t *
NOTHROW_RPC(LIBCCALL libc_wget_current_dir_name)(void)
/*[[[body:wget_current_dir_name]]]*/
{
	return libc_wgetcwd(NULL, 0);
}
/*[[[end:wget_current_dir_name]]]*/

/*[[[head:DOS$wget_current_dir_name,hash:0x22d1e03b]]]*/
INTERN WUNUSED ATTR_MALLOC
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wget_current_dir_name") char16_t *
NOTHROW_RPC(LIBDCALL libd_wget_current_dir_name)(void)
/*[[[body:DOS$wget_current_dir_name]]]*/
{
	return libd_wgetcwd(NULL, 0);
}
/*[[[end:DOS$wget_current_dir_name]]]*/

/*[[[head:wlchown,hash:0x150c2465]]]*/
/* >> wlchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wlchown") int
NOTHROW_RPC(LIBCCALL libc_wlchown)(char32_t const *file,
                                   uid_t owner,
                                   gid_t group)
/*[[[body:wlchown]]]*/
{
	return libc_wfchownat(AT_FDCWD, file, owner, group, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:wlchown]]]*/

/*[[[head:DOS$wlchown,hash:0xb64c9c17]]]*/
/* >> wlchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wlchown") int
NOTHROW_RPC(LIBDCALL libd_wlchown)(char16_t const *file,
                                   uid_t owner,
                                   gid_t group)
/*[[[body:DOS$wlchown]]]*/
{
	return libd_wfchownat(AT_FDCWD, file, owner, group, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:DOS$wlchown]]]*/

/*[[[head:wtruncate,hash:0x83d0367]]]*/
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wtruncate") int
NOTHROW_NCX(LIBCCALL libc_wtruncate)(char32_t const *file,
                                     __PIO_OFFSET length)
/*[[[body:wtruncate]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = truncate(used_file, length);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:wtruncate]]]*/

/*[[[head:DOS$wtruncate,hash:0xa799799e]]]*/
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wtruncate") int
NOTHROW_NCX(LIBDCALL libd_wtruncate)(char16_t const *file,
                                     __PIO_OFFSET length)
/*[[[body:DOS$wtruncate]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = truncate(used_file, length);
		libc_uchar_free(used_file);
	}
	return result;
}
/*[[[end:DOS$wtruncate]]]*/

/*[[[head:wtruncate64,hash:0xba082b49]]]*/
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_wtruncate64, libc_wtruncate);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wtruncate64") int
NOTHROW_NCX(LIBCCALL libc_wtruncate64)(char32_t const *file,
                                       __PIO_OFFSET64 length)
/*[[[body:wtruncate64]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c32tombs(file);
	if likely(used_file) {
		result = truncate64(used_file, length);
		libc_uchar_free(used_file);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:wtruncate64]]]*/

/*[[[head:DOS$wtruncate64,hash:0x6c518e68]]]*/
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libd_wtruncate64, libd_wtruncate);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wtruncate64") int
NOTHROW_NCX(LIBDCALL libd_wtruncate64)(char16_t const *file,
                                       __PIO_OFFSET64 length)
/*[[[body:DOS$wtruncate64]]]*/
{
	int result = -1;
	char *used_file;
	used_file = libc_uchar_c16tombs(file);
	if likely(used_file) {
		result = truncate64(used_file, length);
		libc_uchar_free(used_file);
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:DOS$wtruncate64]]]*/

/*[[[head:wsymlink,hash:0xa6f43dc1]]]*/
/* >> wsymlink(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TO'.
 * Same as `wsymlinkat(FROM, AT_FDCWD, TO)' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wsymlink") int
NOTHROW_RPC(LIBCCALL libc_wsymlink)(char32_t const *from,
                                    char32_t const *to)
/*[[[body:wsymlink]]]*/
{
	return libc_wsymlinkat(from, AT_FDCWD, to);
}
/*[[[end:wsymlink]]]*/

/*[[[head:DOS$wsymlink,hash:0x648ee8b]]]*/
/* >> wsymlink(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TO'.
 * Same as `wsymlinkat(FROM, AT_FDCWD, TO)' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wsymlink") int
NOTHROW_RPC(LIBDCALL libd_wsymlink)(char16_t const *from,
                                    char16_t const *to)
/*[[[body:DOS$wsymlink]]]*/
{
	return libd_wsymlinkat(from, AT_FDCWD, to);
}
/*[[[end:DOS$wsymlink]]]*/

/*[[[head:wreadlink,hash:0x534bd44e]]]*/
/* >> wreadlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `wreadlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wreadlink") ssize_t
NOTHROW_RPC(LIBCCALL libc_wreadlink)(char32_t const *__restrict path,
                                     char32_t *__restrict buf,
                                     size_t buflen)
/*[[[body:wreadlink]]]*/
{
	return libc_wfreadlinkat(AT_FDCWD, path, buf, buflen, 0);
}
/*[[[end:wreadlink]]]*/

/*[[[head:DOS$wreadlink,hash:0x48b98f87]]]*/
/* >> wreadlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `wreadlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted.wreadlink") ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlink)(char16_t const *__restrict path,
                                     char16_t *__restrict buf,
                                     size_t buflen)
/*[[[body:DOS$wreadlink]]]*/
{
	return libd_wfreadlinkat(AT_FDCWD, path, buf, buflen, 0);
}
/*[[[end:DOS$wreadlink]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xd98c0689]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(wttyname, libc_wttyname);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wttyname, libd_wttyname);
DEFINE_PUBLIC_WEAK_ALIAS(wttyname_r, libc_wttyname_r);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wttyname_r, libd_wttyname_r);
DEFINE_PUBLIC_WEAK_ALIAS(wgetlogin, libc_wgetlogin);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wgetlogin, libd_wgetlogin);
DEFINE_PUBLIC_WEAK_ALIAS(wchown, libc_wchown);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wchown, libd_wchown);
DEFINE_PUBLIC_WEAK_ALIAS(wpathconf, libc_wpathconf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wpathconf, libd_wpathconf);
DEFINE_PUBLIC_WEAK_ALIAS(wlink, libc_wlink);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wlink, libd_wlink);
DEFINE_PUBLIC_WEAK_ALIAS(waccess, libc_waccess);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$waccess, libd_waccess);
DEFINE_PUBLIC_WEAK_ALIAS(wchdir, libc_wchdir);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wchdir, libd_wchdir);
DEFINE_PUBLIC_WEAK_ALIAS(wgetcwd, libc_wgetcwd);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wgetcwd, libd_wgetcwd);
DEFINE_PUBLIC_WEAK_ALIAS(wunlink, libc_wunlink);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wunlink, libd_wunlink);
DEFINE_PUBLIC_WEAK_ALIAS(wrmdir, libc_wrmdir);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wrmdir, libd_wrmdir);
DEFINE_PUBLIC_WEAK_ALIAS(weuidaccess, libc_weuidaccess);
DEFINE_PUBLIC_WEAK_ALIAS(weaccess, libc_weuidaccess);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$weuidaccess, libd_weuidaccess);
DEFINE_PUBLIC_WEAK_ALIAS(wget_current_dir_name, libc_wget_current_dir_name);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wget_current_dir_name, libd_wget_current_dir_name);
DEFINE_PUBLIC_WEAK_ALIAS(wfaccessat, libc_wfaccessat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wfaccessat, libd_wfaccessat);
DEFINE_PUBLIC_WEAK_ALIAS(wfchownat, libc_wfchownat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wfchownat, libd_wfchownat);
DEFINE_PUBLIC_WEAK_ALIAS(wlinkat, libc_wlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wlinkat, libd_wlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(wsymlinkat, libc_wsymlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wsymlinkat, libd_wsymlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(wreadlinkat, libc_wreadlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wreadlinkat, libd_wreadlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(wfreadlinkat, libc_wfreadlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wfreadlinkat, libd_wfreadlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(wunlinkat, libc_wunlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wunlinkat, libd_wunlinkat);
DEFINE_PUBLIC_WEAK_ALIAS(wlchown, libc_wlchown);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wlchown, libd_wlchown);
DEFINE_PUBLIC_WEAK_ALIAS(wtruncate, libc_wtruncate);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wtruncate, libd_wtruncate);
DEFINE_PUBLIC_WEAK_ALIAS(wtruncate64, libc_wtruncate64);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wtruncate64, libd_wtruncate64);
DEFINE_PUBLIC_WEAK_ALIAS(wsymlink, libc_wsymlink);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wsymlink, libd_wsymlink);
DEFINE_PUBLIC_WEAK_ALIAS(wreadlink, libc_wreadlink);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wreadlink, libd_wreadlink);
DEFINE_PUBLIC_WEAK_ALIAS(wgetlogin_r, libc_wgetlogin_r);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wgetlogin_r, libd_wgetlogin_r);
DEFINE_PUBLIC_WEAK_ALIAS(wgethostname, libc_wgethostname);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wgethostname, libd_wgethostname);
DEFINE_PUBLIC_WEAK_ALIAS(wsetlogin, libc_wsetlogin);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wsetlogin, libd_wsetlogin);
DEFINE_PUBLIC_WEAK_ALIAS(wsethostname, libc_wsethostname);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wsethostname, libd_wsethostname);
DEFINE_PUBLIC_WEAK_ALIAS(wgetdomainname, libc_wgetdomainname);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wgetdomainname, libd_wgetdomainname);
DEFINE_PUBLIC_WEAK_ALIAS(wsetdomainname, libc_wsetdomainname);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wsetdomainname, libd_wsetdomainname);
DEFINE_PUBLIC_WEAK_ALIAS(wchroot, libc_wchroot);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wchroot, libd_wchroot);
DEFINE_PUBLIC_WEAK_ALIAS(wctermid, libc_wctermid);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wctermid, libd_wctermid);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C */
