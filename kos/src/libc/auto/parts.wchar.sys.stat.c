/* HASH CRC-32:0xb579eb36 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wmkdir)(char16_t const *pathname,
                                  mode_t mode) {




	return libd_wmkdirat(__AT_FDCWD, pathname, mode);












}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wmkdir)(char32_t const *pathname,
                                  mode_t mode) {




	return libc_wmkdirat(__AT_FDCWD, pathname, mode);












}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wchmod)(char16_t const *filename,
                                  mode_t mode) {

	return libd_wfchmodat(__AT_FDCWD, filename, mode, 0);












}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wchmod)(char32_t const *filename,
                                  mode_t mode) {

	return libc_wfchmodat(__AT_FDCWD, filename, mode, 0);












}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wlchmod)(char16_t const *filename,
                                   mode_t mode) {

	return libd_wfchmodat(__AT_FDCWD, filename, mode, __AT_SYMLINK_NOFOLLOW);












}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wlchmod)(char32_t const *filename,
                                   mode_t mode) {

	return libc_wfchmodat(__AT_FDCWD, filename, mode, __AT_SYMLINK_NOFOLLOW);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wmkfifo)(char16_t const *fifoname,
                                   mode_t mode) {

	return libd_wmknod(fifoname, mode | __S_IFIFO, 0);












}
#include <asm/os/stat.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wmkfifo)(char32_t const *fifoname,
                                   mode_t mode) {

	return libc_wmknod(fifoname, mode | __S_IFIFO, 0);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wmkdirat)(fd_t dirfd,
                                    char16_t const *pathname,
                                    mode_t mode) {

	return libd_wfmkdirat(dirfd, pathname, mode, 0);












}
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wmkdirat)(fd_t dirfd,
                                    char32_t const *pathname,
                                    mode_t mode) {

	return libc_wfmkdirat(dirfd, pathname, mode, 0);












}
#include <asm/os/stat.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wmkfifoat)(fd_t dirfd,
                                     char16_t const *fifoname,
                                     mode_t mode) {

	return libd_wmknodat(dirfd, fifoname, mode | __S_IFIFO, 0);












}
#include <asm/os/stat.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wmkfifoat)(fd_t dirfd,
                                     char32_t const *fifoname,
                                     mode_t mode) {

	return libc_wmknodat(dirfd, fifoname, mode | __S_IFIFO, 0);












}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_wmknod)(char16_t const *nodename,
                                  mode_t mode,
                                  dev_t dev) {

	return libd_wmknodat(__AT_FDCWD, nodename, mode, dev);












}
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBKCALL libc_wmknod)(char32_t const *nodename,
                                  mode_t mode,
                                  dev_t dev) {

	return libc_wmknodat(__AT_FDCWD, nodename, mode, dev);












}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_wmknodat)(fd_t dirfd,
                                    char16_t const *nodename,
                                    mode_t mode,
                                    dev_t dev) {

	return libd_wfmknodat(dirfd, nodename, mode, dev, 0);












}
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBKCALL libc_wmknodat)(fd_t dirfd,
                                    char32_t const *nodename,
                                    mode_t mode,
                                    dev_t dev) {

	return libc_wfmknodat(dirfd, nodename, mode, dev, 0);












}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify_time") ATTR_IN(2) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBDCALL libd_wutimensat)(fd_t dirfd,
                                      char16_t const *filename,
                                      struct timespec const times[2 /*or:3*/],
                                      atflag_t flags) {
























#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__

	struct timespec64 tms[3];
	if (!times)
		return libd_wutimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	if (flags & __AT_CHANGE_BTIME) {
		tms[2].tv_sec  = (time64_t)times[2].tv_sec;
		tms[2].tv_nsec = times[2].tv_nsec;
	}
	return libd_wutimensat64(dirfd, filename, tms, flags);










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
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(2) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBKCALL libc_wutimensat)(fd_t dirfd,
                                      char32_t const *filename,
                                      struct timespec const times[2 /*or:3*/],
                                      atflag_t flags) {
























#if defined(__LIBCCALL_IS_LIBKCALL) && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__

	struct timespec64 tms[3];
	if (!times)
		return libc_wutimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	if (flags & __AT_CHANGE_BTIME) {
		tms[2].tv_sec  = (time64_t)times[2].tv_sec;
		tms[2].tv_nsec = times[2].tv_nsec;
	}
	return libc_wutimensat64(dirfd, filename, tms, flags);










#else /* __LIBCCALL_IS_LIBKCALL && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	int result;
	char *utf8_filename;
	utf8_filename = libc_convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = libc_utimensat(dirfd, utf8_filename, times, flags);

	libc_free(utf8_filename);

	return result;
#endif /* !__LIBCCALL_IS_LIBKCALL || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
}
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify_time") ATTR_IN(2) ATTR_IN_OPT(3) int
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
DEFINE_INTERN_ALIAS_P(libc_wutimensat64,libc_wutimensat,ATTR_IN(2) ATTR_IN_OPT(3),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags),(dirfd,filename,times,flags));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(2) ATTR_IN_OPT(3) int
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
DEFINE_PUBLIC_ALIAS_P(DOS$wmkdir,libd_wmkdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *pathname, mode_t mode),(pathname,mode));
DEFINE_PUBLIC_ALIAS_P(wmkdir,libc_wmkdir,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *pathname, mode_t mode),(pathname,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$_wchmod,libd_wchmod,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$wchmod,libd_wchmod,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(wchmod,libc_wchmod,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$wlchmod,libd_wlchmod,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(wlchmod,libc_wlchmod,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$wfmkdirat,libd_wfmkdirat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *pathname, mode_t mode, atflag_t flags),(dirfd,pathname,mode,flags));
DEFINE_PUBLIC_ALIAS_P(wfmkdirat,libc_wfmkdirat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *pathname, mode_t mode, atflag_t flags),(dirfd,pathname,mode,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wfmknodat,libd_wfmknodat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *nodename, mode_t mode, dev_t dev, atflag_t flags),(dirfd,nodename,mode,dev,flags));
DEFINE_PUBLIC_ALIAS_P(wfmknodat,libc_wfmknodat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *nodename, mode_t mode, dev_t dev, atflag_t flags),(dirfd,nodename,mode,dev,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wmkfifo,libd_wmkfifo,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *fifoname, mode_t mode),(fifoname,mode));
DEFINE_PUBLIC_ALIAS_P(wmkfifo,libc_wmkfifo,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *fifoname, mode_t mode),(fifoname,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$wfchmodat,libd_wfchmodat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *filename, mode_t mode, atflag_t flags),(dirfd,filename,mode,flags));
DEFINE_PUBLIC_ALIAS_P(wfchmodat,libc_wfchmodat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *filename, mode_t mode, atflag_t flags),(dirfd,filename,mode,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$wmkdirat,libd_wmkdirat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *pathname, mode_t mode),(dirfd,pathname,mode));
DEFINE_PUBLIC_ALIAS_P(wmkdirat,libc_wmkdirat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *pathname, mode_t mode),(dirfd,pathname,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$wmkfifoat,libd_wmkfifoat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *fifoname, mode_t mode),(dirfd,fifoname,mode));
DEFINE_PUBLIC_ALIAS_P(wmkfifoat,libc_wmkfifoat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *fifoname, mode_t mode),(dirfd,fifoname,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$wmknod,libd_wmknod,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char16_t const *nodename, mode_t mode, dev_t dev),(nodename,mode,dev));
DEFINE_PUBLIC_ALIAS_P(wmknod,libc_wmknod,ATTR_IN(1),int,NOTHROW_RPC,LIBKCALL,(char32_t const *nodename, mode_t mode, dev_t dev),(nodename,mode,dev));
DEFINE_PUBLIC_ALIAS_P(DOS$wmknodat,libd_wmknodat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *nodename, mode_t mode, dev_t dev),(dirfd,nodename,mode,dev));
DEFINE_PUBLIC_ALIAS_P(wmknodat,libc_wmknodat,ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *nodename, mode_t mode, dev_t dev),(dirfd,nodename,mode,dev));
DEFINE_PUBLIC_ALIAS_P(DOS$wutimensat,libd_wutimensat,ATTR_IN(2) ATTR_IN_OPT(3),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags),(dirfd,filename,times,flags));
DEFINE_PUBLIC_ALIAS_P(wutimensat,libc_wutimensat,ATTR_IN(2) ATTR_IN_OPT(3),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags),(dirfd,filename,times,flags));
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(DOS$wutimensat64,libd_wutimensat64,ATTR_IN(2) ATTR_IN_OPT(3),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char16_t const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags),(dirfd,filename,times,flags));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(wutimensat64,libc_wutimensat64,ATTR_IN(2) ATTR_IN_OPT(3),int,NOTHROW_RPC,LIBKCALL,(fd_t dirfd, char32_t const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags),(dirfd,filename,times,flags));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_SYS_STAT_C */
