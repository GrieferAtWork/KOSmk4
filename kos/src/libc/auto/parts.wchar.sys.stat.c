/* HASH CRC-32:0xeebea020 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_SYS_STAT_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_SYS_STAT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.sys.stat.h"
#include "../user/stdlib.h"
#include "../user/sys.stat.h"
#include "uchar.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wmkdir)(char16_t const *pathname,
                                  mode_t mode) {
#ifdef __CRT_DOS_PRIMARY
	(void)mode;
	return dos_c16mkdir(pathname);
#else /* __CRT_DOS_PRIMARY */
	return libd_wmkdirat(__AT_FDCWD, pathname, mode);











#endif /* !__CRT_DOS_PRIMARY */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wmkdir)(char32_t const *pathname,
                                  mode_t mode) {
#if defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
	(void)mode;
	return dos_c32mkdir(pathname);
#else /* __CRT_DOS_PRIMARY && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL */
	return libc_wmkdirat(__AT_FDCWD, pathname, mode);











#endif /* !__CRT_DOS_PRIMARY || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wchmod)(char16_t const *filename,
                                  mode_t mode) {
#ifdef __AT_FDCWD
	return libd_wfchmodat(__AT_FDCWD, filename, mode, 0);
#else /* __AT_FDCWD */
	int result;
	char *utf8_filename;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libd_chmod(utf8_filename, mode);

	libc_free(utf8_filename);

	return result;
#endif /* !__AT_FDCWD */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wchmod)(char32_t const *filename,
                                  mode_t mode) {
#ifdef __AT_FDCWD
	return libc_wfchmodat(__AT_FDCWD, filename, mode, 0);
#else /* __AT_FDCWD */
	int result;
	char *utf8_filename;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_chmod(utf8_filename, mode);

	libc_free(utf8_filename);

	return result;
#endif /* !__AT_FDCWD */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wlchmod)(char16_t const *filename,
                                   mode_t mode) {
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW)
	return libd_wfchmodat(__AT_FDCWD, filename, mode, __AT_SYMLINK_NOFOLLOW);
#else /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW */
	int result;
	char *utf8_filename;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libd_lchmod(utf8_filename, mode);

	libc_free(utf8_filename);

	return result;
#endif /* !__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wlchmod)(char32_t const *filename,
                                   mode_t mode) {
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW)
	return libc_wfchmodat(__AT_FDCWD, filename, mode, __AT_SYMLINK_NOFOLLOW);
#else /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW */
	int result;
	char *utf8_filename;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_lchmod(utf8_filename, mode);

	libc_free(utf8_filename);

	return result;
#endif /* !__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW */
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wfmkdirat)(fd_t dirfd,
                                     char16_t const *pathname,
                                     mode_t mode,
                                     atflag_t flags) {
	int result;
	char *utf8_pathname;
	utf8_pathname = libd_convert_wcstombs(pathname);
	if unlikely(!utf8_pathname)
		return -1;
	result = libd_fmkdirat(dirfd, utf8_pathname, mode, flags);

	libc_free(utf8_pathname);

	return result;
}
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wfmkdirat)(fd_t dirfd,
                                     char32_t const *pathname,
                                     mode_t mode,
                                     atflag_t flags) {
	int result;
	char *utf8_pathname;
	utf8_pathname = libc_convert_wcstombs(pathname);
	if unlikely(!utf8_pathname)
		return -1;
	result = libc_fmkdirat(dirfd, utf8_pathname, mode, flags);

	libc_free(utf8_pathname);

	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wfmknodat)(fd_t dirfd,
                                     char16_t const *nodename,
                                     mode_t mode,
                                     dev_t dev,
                                     atflag_t flags) {
	int result;
	char *utf8_nodename;
	utf8_nodename = libd_convert_wcstombs(nodename);
	if unlikely(!utf8_nodename)
		return -1;
	result = libd_fmknodat(dirfd, utf8_nodename, mode, dev, flags);

	libc_free(utf8_nodename);

	return result;
}
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wfmknodat)(fd_t dirfd,
                                     char32_t const *nodename,
                                     mode_t mode,
                                     dev_t dev,
                                     atflag_t flags) {
	int result;
	char *utf8_nodename;
	utf8_nodename = libc_convert_wcstombs(nodename);
	if unlikely(!utf8_nodename)
		return -1;
	result = libc_fmknodat(dirfd, utf8_nodename, mode, dev, flags);

	libc_free(utf8_nodename);

	return result;
}
#include <asm/os/stat.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wmkfifo)(char16_t const *fifoname,
                                   mode_t mode) {
#ifdef __S_IFIFO
	return libd_wmknod(fifoname, mode | __S_IFIFO, 0);
#else /* __S_IFIFO */
	int result;
	char *utf8_fifoname;
	utf8_fifoname = libd_convert_wcstombs(fifoname);
	if unlikely(!utf8_fifoname)
		return -1;
	result = libd_mkfifo(utf8_fifoname, mode);

	libc_free(utf8_fifoname);

	return result;
#endif /* !__S_IFIFO */
}
#include <asm/os/stat.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wmkfifo)(char32_t const *fifoname,
                                   mode_t mode) {
#ifdef __S_IFIFO
	return libc_wmknod(fifoname, mode | __S_IFIFO, 0);
#else /* __S_IFIFO */
	int result;
	char *utf8_fifoname;
	utf8_fifoname = libc_convert_wcstombs(fifoname);
	if unlikely(!utf8_fifoname)
		return -1;
	result = libc_mkfifo(utf8_fifoname, mode);

	libc_free(utf8_fifoname);

	return result;
#endif /* !__S_IFIFO */
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wfchmodat)(fd_t dirfd,
                                     char16_t const *filename,
                                     mode_t mode,
                                     atflag_t flags) {
	int result;
	char *utf8_filename;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libd_fchmodat(dirfd, utf8_filename, mode, flags);

	libc_free(utf8_filename);

	return result;
}
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wfchmodat)(fd_t dirfd,
                                     char32_t const *filename,
                                     mode_t mode,
                                     atflag_t flags) {
	int result;
	char *utf8_filename;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_fchmodat(dirfd, utf8_filename, mode, flags);

	libc_free(utf8_filename);

	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wmkdirat)(fd_t dirfd,
                                    char16_t const *pathname,
                                    mode_t mode) {

	return libd_wfmkdirat(dirfd, pathname, mode, 0);












}
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wmkdirat)(fd_t dirfd,
                                    char32_t const *pathname,
                                    mode_t mode) {

	return libc_wfmkdirat(dirfd, pathname, mode, 0);












}
#include <asm/os/stat.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wmkfifoat)(fd_t dirfd,
                                     char16_t const *fifoname,
                                     mode_t mode) {
#ifdef __S_IFIFO
	return libd_wmknodat(dirfd, fifoname, mode | __S_IFIFO, 0);
#else /* __S_IFIFO */
	int result;
	char *utf8_fifoname;
	utf8_fifoname = libd_convert_wcstombs(fifoname);
	if unlikely(!utf8_fifoname)
		return -1;
	result = libd_mkfifoat(dirfd, utf8_fifoname, mode);

	libc_free(utf8_fifoname);

	return result;
#endif /* !__S_IFIFO */
}
#include <asm/os/stat.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wmkfifoat)(fd_t dirfd,
                                     char32_t const *fifoname,
                                     mode_t mode) {
#ifdef __S_IFIFO
	return libc_wmknodat(dirfd, fifoname, mode | __S_IFIFO, 0);
#else /* __S_IFIFO */
	int result;
	char *utf8_fifoname;
	utf8_fifoname = libc_convert_wcstombs(fifoname);
	if unlikely(!utf8_fifoname)
		return -1;
	result = libc_mkfifoat(dirfd, utf8_fifoname, mode);

	libc_free(utf8_fifoname);

	return result;
#endif /* !__S_IFIFO */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_wmknod)(char16_t const *nodename,
                                  mode_t mode,
                                  dev_t dev) {
#ifdef __AT_FDCWD
	return libd_wmknodat(__AT_FDCWD, nodename, mode, dev);
#else /* __AT_FDCWD */
	int result;
	char *utf8_nodename;
	utf8_nodename = libd_convert_wcstombs(nodename);
	if unlikely(!utf8_nodename)
		return -1;
	result = libd_mknod(utf8_nodename, mode, dev);

	libc_free(utf8_nodename);

	return result;
#endif /* !__AT_FDCWD */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBKCALL libc_wmknod)(char32_t const *nodename,
                                  mode_t mode,
                                  dev_t dev) {
#ifdef __AT_FDCWD
	return libc_wmknodat(__AT_FDCWD, nodename, mode, dev);
#else /* __AT_FDCWD */
	int result;
	char *utf8_nodename;
	utf8_nodename = libc_convert_wcstombs(nodename);
	if unlikely(!utf8_nodename)
		return -1;
	result = libc_mknod(utf8_nodename, mode, dev);

	libc_free(utf8_nodename);

	return result;
#endif /* !__AT_FDCWD */
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wmknodat)(fd_t dirfd,
                                    char16_t const *nodename,
                                    mode_t mode,
                                    dev_t dev) {

	return libd_wfmknodat(dirfd, nodename, mode, dev, 0);












}
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wmknodat)(fd_t dirfd,
                                    char32_t const *nodename,
                                    mode_t mode,
                                    dev_t dev) {

	return libc_wfmknodat(dirfd, nodename, mode, dev, 0);












}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wutimensat)(fd_t dirfd,
                                      char16_t const *filename,
                                      struct timespec const times[2 /*or:3*/],
                                      atflag_t flags) {
























#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
#ifdef __AT_CHANGE_CTIME
	struct timespec64 tms[3];
	if (!times)
		return libd_wutimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	if (flags & __AT_CHANGE_CTIME) {
		tms[2].tv_sec  = (time64_t)times[2].tv_sec;
		tms[2].tv_nsec = times[2].tv_nsec;
	}
	return libd_wutimensat64(dirfd, filename, tms, flags);
#else /* __AT_CHANGE_CTIME */
	struct timespec64 tms[2];
	if (!times)
		return libd_wutimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return libd_wutimensat64(dirfd, filename, tms, flags);
#endif /* !__AT_CHANGE_CTIME */
#else /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	int result;
	char *utf8_filename;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libd_utimensat(dirfd, utf8_filename, times, flags);

	libc_free(utf8_filename);

	return result;
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wutimensat)(fd_t dirfd,
                                      char32_t const *filename,
                                      struct timespec const times[2 /*or:3*/],
                                      atflag_t flags) {
























#if __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL) && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
#ifdef __AT_CHANGE_CTIME
	struct timespec64 tms[3];
	if (!times)
		return libc_wutimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	if (flags & __AT_CHANGE_CTIME) {
		tms[2].tv_sec  = (time64_t)times[2].tv_sec;
		tms[2].tv_nsec = times[2].tv_nsec;
	}
	return libc_wutimensat64(dirfd, filename, tms, flags);
#else /* __AT_CHANGE_CTIME */
	struct timespec64 tms[2];
	if (!times)
		return libc_wutimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return libc_wutimensat64(dirfd, filename, tms, flags);
#endif /* !__AT_CHANGE_CTIME */
#else /* __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	int result;
	char *utf8_filename;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_utimensat(dirfd, utf8_filename, times, flags);

	libc_free(utf8_filename);

	return result;
#endif /* __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_wutimensat64)(fd_t dirfd,
                                        char16_t const *filename,
                                        struct timespec64 const times[2 /*or:3*/],
                                        atflag_t flags) {

	int result;
	char *utf8_filename;
	utf8_filename = libd_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libd_utimensat64(dirfd, utf8_filename, times, flags);

	libc_free(utf8_filename);

	return result;

























}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_wutimensat64, libc_wutimensat);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBKCALL libc_wutimensat64)(fd_t dirfd,
                                        char32_t const *filename,
                                        struct timespec64 const times[2 /*or:3*/],
                                        atflag_t flags) {

	int result;
	char *utf8_filename;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_utimensat64(dirfd, utf8_filename, times, flags);

	libc_free(utf8_filename);

	return result;

























}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$wmkdir, libd_wmkdir);
DEFINE_PUBLIC_ALIAS(wmkdir, libc_wmkdir);
DEFINE_PUBLIC_ALIAS(DOS$_wchmod, libd_wchmod);
DEFINE_PUBLIC_ALIAS(DOS$wchmod, libd_wchmod);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_wchmod, libc_wchmod);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(wchmod, libc_wchmod);
DEFINE_PUBLIC_ALIAS(DOS$wlchmod, libd_wlchmod);
DEFINE_PUBLIC_ALIAS(wlchmod, libc_wlchmod);
DEFINE_PUBLIC_ALIAS(DOS$wfmkdirat, libd_wfmkdirat);
DEFINE_PUBLIC_ALIAS(wfmkdirat, libc_wfmkdirat);
DEFINE_PUBLIC_ALIAS(DOS$wfmknodat, libd_wfmknodat);
DEFINE_PUBLIC_ALIAS(wfmknodat, libc_wfmknodat);
DEFINE_PUBLIC_ALIAS(DOS$wmkfifo, libd_wmkfifo);
DEFINE_PUBLIC_ALIAS(wmkfifo, libc_wmkfifo);
DEFINE_PUBLIC_ALIAS(DOS$wfchmodat, libd_wfchmodat);
DEFINE_PUBLIC_ALIAS(wfchmodat, libc_wfchmodat);
DEFINE_PUBLIC_ALIAS(DOS$wmkdirat, libd_wmkdirat);
DEFINE_PUBLIC_ALIAS(wmkdirat, libc_wmkdirat);
DEFINE_PUBLIC_ALIAS(DOS$wmkfifoat, libd_wmkfifoat);
DEFINE_PUBLIC_ALIAS(wmkfifoat, libc_wmkfifoat);
DEFINE_PUBLIC_ALIAS(DOS$wmknod, libd_wmknod);
DEFINE_PUBLIC_ALIAS(wmknod, libc_wmknod);
DEFINE_PUBLIC_ALIAS(DOS$wmknodat, libd_wmknodat);
DEFINE_PUBLIC_ALIAS(wmknodat, libc_wmknodat);
DEFINE_PUBLIC_ALIAS(DOS$wutimensat, libd_wutimensat);
DEFINE_PUBLIC_ALIAS(wutimensat, libc_wutimensat);
DEFINE_PUBLIC_ALIAS(DOS$wutimensat64, libd_wutimensat64);
DEFINE_PUBLIC_ALIAS(wutimensat64, libc_wutimensat64);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_SYS_STAT_C */
