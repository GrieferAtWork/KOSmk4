/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_UTIME_C
#define GUARD_LIBC_USER_UTIME_C 1

#include "../api.h"
#include "utime.h"
#include <fcntl.h>
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libd_utime,hash:CRC-32=0x6878a23c]]]*/
/* >> utime(2), utime64(2) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBDCALL libd_utime)(char const *filename,
                                 struct utimbuf const *file_times)
/*[[[body:libd_utime]]]*/
{
	errno_t error;
	if (file_times) {
		struct timespec tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_nsec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_nsec = 0;
		error = sys_utimensat(AT_FDCWD, filename, tv, libd_AT_DOSPATH);
	} else {
		error = sys_utimensat(AT_FDCWD, filename, NULL, libd_AT_DOSPATH);
	}
	return libc_seterrno_syserr(error);
}
/*[[[end:libd_utime]]]*/

/*[[[head:libc_utime,hash:CRC-32=0x6d91920]]]*/
/* >> utime(2), utime64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_utime)(char const *filename,
                                 struct utimbuf const *file_times)
/*[[[body:libc_utime]]]*/
{
	errno_t error;
#ifdef __NR_utime
	error = sys_utime(filename, file_times);
#else /* __NR_utime */
	if (file_times) {
		struct timeval tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat(AT_FDCWD, filename, tv);
	} else {
		error = sys_futimesat(AT_FDCWD, filename, NULL);
	}
#endif /* !__NR_utime */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_utime]]]*/

/*[[[head:libd_utime64,hash:CRC-32=0x6d40d98f]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd_utime64, libd_utime);
#else /* MAGIC:alias */
/* >> utime(2), utime64(2) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBDCALL libd_utime64)(char const *filename,
                                   struct utimbuf64 const *file_times)
/*[[[body:libd_utime64]]]*/
{
	errno_t error;
	if (file_times) {
		struct timespec64 tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_nsec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_nsec = 0;
		error = sys_utimensat_time64(AT_FDCWD, filename, tv, libd_AT_DOSPATH);
	} else {
		error = sys_utimensat_time64(AT_FDCWD, filename, NULL, libd_AT_DOSPATH);
	}
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libd_utime64]]]*/

/*[[[head:libc_utime64,hash:CRC-32=0xe596098]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_utime64, libc_utime);
#else /* MAGIC:alias */
/* >> utime(2), utime64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_utime64)(char const *filename,
                                   struct utimbuf64 const *file_times)
/*[[[body:libc_utime64]]]*/
{
	errno_t error;
#ifdef __NR_utime64
	error = sys_utime64(filename, file_times);
#else /* __NR_utime64 */
	if (file_times) {
		struct timeval64 tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat64(AT_FDCWD, filename, tv);
	} else {
		error = sys_futimesat64(AT_FDCWD, filename, NULL);
	}
#endif /* !__NR_utime64 */
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_utime64]]]*/

/*[[[head:libc_futime,hash:CRC-32=0x9d778b28]]]*/
/* >> futime(3), futime64(3) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_FDARG(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_futime)(fd_t fd,
                                  struct utimbuf const *file_times)
/*[[[body:libc_futime]]]*/
{
	errno_t error;
	if (file_times) {
		struct timeval tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat(fd, NULL, tv);
	} else {
		error = sys_futimesat(fd, NULL, NULL);
	}
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_futime]]]*/

/*[[[head:libc_futime64,hash:CRC-32=0xdcec718b]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futime64, libc_futime);
#else /* MAGIC:alias */
/* >> futime(3), futime64(3) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_FDARG(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_futime64)(fd_t fd,
                                    struct utimbuf64 const *file_times)
/*[[[body:libc_futime64]]]*/
{
	errno_t error;
	if (file_times) {
		struct timeval64 tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat64(fd, NULL, tv);
	} else {
		error = sys_futimesat64(fd, NULL, NULL);
	}
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futime64]]]*/





/*[[[start:exports,hash:CRC-32=0x27ef11ee]]]*/
DEFINE_PUBLIC_ALIAS_P(DOS$__utime,libd_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_utime,libd_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(DOS$_utime,libd_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(DOS$_utime32,libd_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(DOS$utime,libd_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(__utime,libc_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(__libc_utime,libc_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_utime,libc_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(_utime32,libc_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(utime,libc_utime,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf const *file_times),(filename,file_times));
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(DOS$__utime64,libd_utime64,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf64 const *file_times),(filename,file_times));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS_P(DOS$_utime64,libd_utime64,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf64 const *file_times),(filename,file_times));
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(DOS$utime64,libd_utime64,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBDCALL,(char const *filename, struct utimbuf64 const *file_times),(filename,file_times));
DEFINE_PUBLIC_ALIAS_P(__utime64,libc_utime64,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf64 const *file_times),(filename,file_times));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_utime64,libc_utime64,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf64 const *file_times),(filename,file_times));
#endif /* __LIBCCALL_IS_LIBDCALL */
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(utime64,libc_utime64,ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(char const *filename, struct utimbuf64 const *file_times),(filename,file_times));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_futime,libc_futime,ATTR_FDARG(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct utimbuf const *file_times),(fd,file_times));
DEFINE_PUBLIC_ALIAS_P(_futime32,libc_futime,ATTR_FDARG(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct utimbuf const *file_times),(fd,file_times));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(futime,libc_futime,ATTR_FDARG(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct utimbuf const *file_times),(fd,file_times));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_futime64,libc_futime64,ATTR_FDARG(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct utimbuf64 const *file_times),(fd,file_times));
#endif /* __LIBCCALL_IS_LIBDCALL */
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(futime64,libc_futime64,ATTR_FDARG(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct utimbuf64 const *file_times),(fd,file_times));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UTIME_C */
