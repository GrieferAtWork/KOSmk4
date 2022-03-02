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
#ifndef GUARD_LIBC_USER_SYS_STAT_C
#define GUARD_LIBC_USER_SYS_STAT_C 1
#define __DEFINE_DOS_STAT_STRUCTURES 1

#include "../api.h"
/**/

#include <bits/os/cygwin/stat.h>
#include <bits/os/dos/stat.h>
#include <bits/os/kos/stat.h>
#include <bits/os/linux/stat.h>
#include <kos/syscalls.h>

#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <syscall.h>
#include <uchar.h>
#include <unistd.h>

#include "sys.stat.h"

DECL_BEGIN


DEFINE_PUBLIC_ALIAS(kstat, libc_kos_stat);
DEFINE_PUBLIC_ALIAS(kstat64, libc_kos_stat);
DEFINE_PUBLIC_ALIAS(klstat, libc_kos_lstat);
DEFINE_PUBLIC_ALIAS(klstat64, libc_kos_lstat);
DEFINE_PUBLIC_ALIAS(kfstat, libc_kos_fstat);
DEFINE_PUBLIC_ALIAS(kfstat64, libc_kos_fstat);
DEFINE_PUBLIC_ALIAS(kfstatat, libc_kos_fstatat);
DEFINE_PUBLIC_ALIAS(kfstatat64, libc_kos_fstatat);

DEFINE_INTERN_ALIAS(libc_kstat, libc_kos_stat);
DEFINE_INTERN_ALIAS(libc_kstat64, libc_kos_stat);
DEFINE_INTERN_ALIAS(libc_klstat, libc_kos_lstat);
DEFINE_INTERN_ALIAS(libc_klstat64, libc_kos_lstat);
DEFINE_INTERN_ALIAS(libc_kfstat, libc_kos_fstat);
DEFINE_INTERN_ALIAS(libc_kfstat64, libc_kos_fstat);
DEFINE_INTERN_ALIAS(libc_kfstatat, libc_kos_fstatat);
DEFINE_INTERN_ALIAS(libc_kfstatat64, libc_kos_fstatat);

/* KOS Native stat() */
INTERN ATTR_SECTION(".text.crt.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_fstat)(fd_t fd,
                                     struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstat(fd,
	                   (struct stat *)buf);
	return libc_seterrno_syserr(error);
}

INTERN ATTR_SECTION(".text.crt.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_fstatat)(fd_t dirfd,
                                       char const *__restrict filename,
                                       struct __kos_stat *__restrict buf,
                                       atflag_t flags) {
	errno_t error;
	error = sys_kfstatat(dirfd, filename, (struct stat *)buf, flags);
	return libc_seterrno_syserr(error);
}

INTERN ATTR_SECTION(".text.crt.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_stat)(char const *__restrict filename,
                                    struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstatat(AT_FDCWD,
	                     filename,
	                     (struct stat *)buf,
	                     0);
	return libc_seterrno_syserr(error);
}

INTERN ATTR_SECTION(".text.crt.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_lstat)(char const *__restrict filename,
                                     struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstatat(AT_FDCWD,
	                     filename,
	                     (struct stat *)buf,
	                     AT_SYMLINK_NOFOLLOW);
	return libc_seterrno_syserr(error);
}


DEFINE_PUBLIC_ALIAS(DOS$kstat, libd_kos_stat);
DEFINE_PUBLIC_ALIAS(DOS$kstat64, libd_kos_stat);
DEFINE_PUBLIC_ALIAS(DOS$klstat, libd_kos_lstat);
DEFINE_PUBLIC_ALIAS(DOS$klstat64, libd_kos_lstat);
DEFINE_PUBLIC_ALIAS(DOS$kfstat64, libd_kos_fstat);
DEFINE_PUBLIC_ALIAS(DOS$kfstatat64, libd_kos_fstatat);

DEFINE_INTERN_ALIAS(libd_kstat, libd_kos_stat);
DEFINE_INTERN_ALIAS(libd_kstat64, libd_kos_stat);
DEFINE_INTERN_ALIAS(libd_klstat, libd_kos_lstat);
DEFINE_INTERN_ALIAS(libd_klstat64, libd_kos_lstat);
DEFINE_INTERN_ALIAS(libd_kfstatat, libd_kos_fstatat);
DEFINE_INTERN_ALIAS(libd_kfstatat64, libd_kos_fstatat);

INTERN ATTR_SECTION(".text.crt.dos.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_kos_fstatat)(fd_t dirfd,
                                       char const *__restrict filename,
                                       struct __kos_stat *__restrict buf,
                                       atflag_t flags) {
	errno_t error;
	error = sys_kfstatat(dirfd, filename, (struct stat *)buf, flags | libd_AT_DOSPATH);
	return libc_seterrno_syserr(error);
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_kos_stat)(char const *__restrict filename,
                                    struct __kos_stat *__restrict buf) {
	return libd_kos_fstatat(AT_FDCWD, filename, buf, 0);
}

INTERN ATTR_SECTION(".text.crt.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_kos_lstat)(char const *__restrict filename,
                                     struct __kos_stat *__restrict buf) {
	return libd_kos_fstatat(AT_FDCWD, filename, buf, AT_SYMLINK_NOFOLLOW);
}



/* CYGWIN stat() emulation */
DEFINE_PUBLIC_ALIAS(DOS$stat, libc_cyg_stat);
DEFINE_PUBLIC_ALIAS(DOS$stat64, libc_cyg_stat);
DEFINE_PUBLIC_ALIAS(DOS$lstat, libc_cyg_lstat);
DEFINE_PUBLIC_ALIAS(DOS$lstat64, libc_cyg_lstat);
DEFINE_PUBLIC_ALIAS(DOS$fstat, libc_cyg_fstat);
DEFINE_PUBLIC_ALIAS(DOS$fstat64, libc_cyg_fstat);
DEFINE_PUBLIC_ALIAS(DOS$fstatat, libc_cyg_fstatat);
DEFINE_PUBLIC_ALIAS(DOS$fstatat64, libc_cyg_fstatat);
LOCAL ATTR_SECTION(".text.crt.dos.compat.cyg.fs.stat") NONNULL((1, 2)) void LIBCCALL
convstat_kos2cyg(struct __cyg_stat *__restrict dst,
                 struct __kos_stat const *__restrict src) {
	dst->st_dev      = (u32)src->st_dev;
	dst->st_ino      = (u64)src->st_ino64;
	dst->st_mode     = (u32)src->st_mode;
	dst->st_nlink    = (__UINT16_TYPE__)src->st_nlink;
	dst->st_uid      = (u32)src->st_uid;
	dst->st_gid      = (u32)src->st_gid;
	dst->st_rdev     = (u32)src->st_rdev;
	dst->st_size     = (u64)src->st_size64;
	dst->st_atim     = src->st_atim64;
	dst->st_mtim     = src->st_mtim64;
	dst->st_ctim     = src->st_ctim64;
	dst->st_blksize  = (u32)src->st_blksize;
	dst->st_blocks   = (u64)src->st_blocks64;
	dst->st_birthtim = src->st_ctim64;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.cyg.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_cyg_fstat)(fd_t fd,
                                     struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.cyg.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_cyg_stat)(char const *__restrict filename,
                                    struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.cyg.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_cyg_lstat)(char const *__restrict filename,
                                     struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.cyg.fs.stat") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc_cyg_fstatat)(fd_t dirfd,
                                       char const *__restrict filename,
                                       struct __cyg_stat *__restrict buf,
                                       atflag_t flags) {
	struct __kos_stat st;
	int result = libc_kos_fstatat(dirfd, filename, &st, flags);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}




/* GLIBC stat() emulation */
DEFINE_PUBLIC_ALIAS(stat, libc_glc_stat);
DEFINE_PUBLIC_ALIAS(stat64, libc_glc_stat64);
DEFINE_PUBLIC_ALIAS(lstat, libc_glc_lstat);
DEFINE_PUBLIC_ALIAS(lstat64, libc_glc_lstat64);
DEFINE_PUBLIC_ALIAS(fstat, libc_glc_fstat);
DEFINE_PUBLIC_ALIAS(fstat64, libc_glc_fstat64);
DEFINE_PUBLIC_ALIAS(fstatat, libc_glc_fstatat);
DEFINE_PUBLIC_ALIAS(fstatat64, libc_glc_fstatat64);
DEFINE_INTERN_ALIAS(libc_stat, libc_glc_stat);
DEFINE_INTERN_ALIAS(libc_stat64, libc_glc_stat64);
DEFINE_INTERN_ALIAS(libc_lstat, libc_glc_lstat);
DEFINE_INTERN_ALIAS(libc_lstat64, libc_glc_lstat64);
DEFINE_INTERN_ALIAS(libc_fstat, libc_glc_fstat);
DEFINE_INTERN_ALIAS(libc_fstat64, libc_glc_fstat64);
DEFINE_INTERN_ALIAS(libc_fstatat, libc_glc_fstatat);
DEFINE_INTERN_ALIAS(libc_fstatat64, libc_glc_fstatat64);
LOCAL ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((1, 2)) void LIBCCALL
convstat_kos2glc(struct __glc_stat *__restrict dst,
                 struct __kos_stat const *__restrict src) {
	dst->st_dev          = (typeof(dst->st_dev))src->st_dev;
	dst->st_ino          = (typeof(dst->st_ino))src->st_ino32;
	dst->st_mode         = (typeof(dst->st_mode))src->st_mode;
	dst->st_nlink        = (typeof(dst->st_nlink))src->st_nlink;
	dst->st_uid          = (typeof(dst->st_uid))src->st_uid;
	dst->st_gid          = (typeof(dst->st_gid))src->st_gid;
	dst->st_rdev         = (typeof(dst->st_rdev))src->st_rdev;
	dst->st_size         = (typeof(dst->st_size))src->st_size32;
	dst->st_blksize      = (typeof(dst->st_blksize))src->st_blksize;
	dst->st_blocks       = (typeof(dst->st_blocks))src->st_blocks32;
	dst->st_atim.tv_sec  = (typeof(dst->st_atim.tv_sec))src->st_atim32.tv_sec;
	dst->st_atim.tv_nsec = (typeof(dst->st_atim.tv_nsec))src->st_atim32.tv_nsec;
	dst->st_mtim.tv_sec  = (typeof(dst->st_mtim.tv_sec))src->st_mtim32.tv_sec;
	dst->st_mtim.tv_nsec = (typeof(dst->st_mtim.tv_nsec))src->st_mtim32.tv_nsec;
	dst->st_ctim.tv_sec  = (typeof(dst->st_ctim.tv_sec))src->st_ctim32.tv_sec;
	dst->st_ctim.tv_nsec = (typeof(dst->st_ctim.tv_nsec))src->st_ctim32.tv_nsec;
}

LOCAL ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((1, 2)) void LIBCCALL
convstat_kos2glc64(struct __glc_stat64 *__restrict dst,
                   struct __kos_stat const *__restrict src) {
	dst->st_dev          = (typeof(dst->st_dev))src->st_dev;
	dst->st_ino32        = (typeof(dst->st_ino32))src->st_ino32;
	dst->st_mode         = (typeof(dst->st_mode))src->st_mode;
	dst->st_nlink        = (typeof(dst->st_nlink))src->st_nlink;
	dst->st_uid          = (typeof(dst->st_uid))src->st_uid;
	dst->st_gid          = (typeof(dst->st_gid))src->st_gid;
	dst->st_rdev         = (typeof(dst->st_rdev))src->st_rdev;
	dst->st_size64       = (typeof(dst->st_size64))src->st_size64;
	dst->st_blksize      = (typeof(dst->st_blksize))src->st_blksize;
	dst->st_blocks       = (typeof(dst->st_blocks))src->st_blocks32;
	dst->st_atim.tv_sec  = (typeof(dst->st_atim.tv_sec))src->st_atim32.tv_sec;
	dst->st_atim.tv_nsec = (typeof(dst->st_atim.tv_nsec))src->st_atim32.tv_nsec;
	dst->st_mtim.tv_sec  = (typeof(dst->st_mtim.tv_sec))src->st_mtim32.tv_sec;
	dst->st_mtim.tv_nsec = (typeof(dst->st_mtim.tv_nsec))src->st_mtim32.tv_nsec;
	dst->st_ctim.tv_sec  = (typeof(dst->st_ctim.tv_sec))src->st_ctim32.tv_sec;
	dst->st_ctim.tv_nsec = (typeof(dst->st_ctim.tv_nsec))src->st_ctim32.tv_nsec;
	dst->st_ino64        = (typeof(dst->st_ino64))src->st_ino64;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_glc_fstat)(fd_t fd,
                                     struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_glc_fstat64)(fd_t fd,
                                       struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_stat)(char const *__restrict filename,
                                    struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_stat64)(char const *__restrict filename,
                                      struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_lstat)(char const *__restrict filename,
                                     struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_lstat64)(char const *__restrict filename,
                                       struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc_glc_fstatat)(fd_t dirfd,
                                       char const *__restrict filename,
                                       struct __glc_stat *__restrict buf,
                                       atflag_t flags) {
	struct __kos_stat st;
	int result = libc_kos_fstatat(dirfd,
	                              filename,
	                              &st,
	                              flags);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc_glc_fstatat64)(fd_t dirfd,
                                         char const *__restrict filename,
                                         struct __glc_stat64 *__restrict buf,
                                         atflag_t flags) {
	struct __kos_stat st;
	int result = libc_kos_fstatat(dirfd,
	                              filename,
	                              &st,
	                              flags);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}


/************************************************************************/
/* Compatibility for gLibc's mess of different stat structures...       */
/************************************************************************/


/*
 * Names -> types:
 *  - _STAT_VER_KERNEL:                  `struct linux_stat32'
 *  - _STAT_VER_KERNEL | STAT_CONV_F_64: `struct linux_stat64'
 *  - _STAT_VER_KERNEL64:                `struct linux_stat64'
 *  - _STAT_VER_LINUX:                   `struct __glc_stat'
 *  - _STAT_VER_LINUX | STAT_CONV_F_64:  `struct __glc_stat64'
 *  - _STAT_VER_LINUX_OLD:               ???  (weird, platform-specific alias for `_STAT_VER_KERNEL')
 *  - _STAT_VER_SVR4:                    ???  (Not implemented anywhere; historical artifact)
 */
#ifdef __x86_64__
#define _STAT_VER_KERNEL 0
#define _STAT_VER_LINUX  1
#define _MKNOD_VER_LINUX 0
#elif defined(__i386__)
#define _STAT_VER_LINUX_OLD 1
#define _STAT_VER_KERNEL    1
#define _STAT_VER_SVR4      2
#define _STAT_VER_LINUX     3
#define _MKNOD_VER_LINUX    1
#define _MKNOD_VER_SVR4     2
#elif defined(__alpha__)
#define _STAT_VER_KERNEL     0
#define _STAT_VER_GLIBC2     1
#define _STAT_VER_GLIBC2_1   2
#define _STAT_VER_KERNEL64   3
#define _STAT_VER_GLIBC2_3_4 3
#define _STAT_VER_LINUX      3
#define _MKNOD_VER_LINUX     0
#elif defined(__ia64__)
#define _STAT_VER_KERNEL 0
#define _STAT_VER_LINUX  1
#define _MKNOD_VER_LINUX 0
#elif (defined(__m64k__) || defined(__microblaze__) || \
       defined(__mips__) || defined(__powerpc__) ||    \
       defined(__sparc__))
#define _STAT_VER_LINUX_OLD 1
#define _STAT_VER_KERNEL    1
#define _STAT_VER_SVR4      2
#define _STAT_VER_LINUX     3
#define _MKNOD_VER_LINUX    1
#define _MKNOD_VER_SVR4     2
#elif defined(__s390__)
#if __SIZEOF_POINTER__ == 8
#define _STAT_VER_KERNEL 0
#define _STAT_VER_LINUX  1
#define _MKNOD_VER_LINUX 0
#else /* __SIZEOF_POINTER__ == 8 */
#define _STAT_VER_LINUX_OLD 1
#define _STAT_VER_KERNEL    1
#define _STAT_VER_SVR4      2
#define _STAT_VER_LINUX     3
#define _MKNOD_VER_LINUX    1
#define _MKNOD_VER_SVR4     2
#endif /* __SIZEOF_POINTER__ != 8 */
#elif __SIZEOF_POINTER__ == 8
#define _STAT_VER_KERNEL 0
#define _STAT_VER_LINUX  0
#define _MKNOD_VER_LINUX 0
#else /* ... */
#define _STAT_VER_LINUX_OLD 1
#define _STAT_VER_KERNEL    1
#define _STAT_VER_LINUX     3
#define _STAT_VER_SVR4      2
#define _MKNOD_VER_LINUX    1
#define _MKNOD_VER_SVR4     2
#endif /* !... */



#define STAT_CONV_F_64 0x8000 /* 64-bit flag */
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 3)) errno_t
NOTHROW(LIBCCALL stat_conv)(int vers, struct stat const *__restrict st, void *__restrict buf) {
	switch (vers) {

	case _STAT_VER_KERNEL:
#ifdef __LINUX_STAT32_MATCHES_LINUX_STAT64
	case _STAT_VER_KERNEL | STAT_CONV_F_64:
#ifdef _STAT_VER_KERNEL64
	case _STAT_VER_KERNEL64:
#endif /* _STAT_VER_KERNEL64 */
#endif /* __LINUX_STAT32_MATCHES_LINUX_STAT64 */
	{
		struct linux_stat32 *res;
		res = (struct linux_stat32 *)buf;
		bzero(res, sizeof(*res));
		res->st_dev        = (typeof(res->st_dev))st->st_dev;
		res->st_ino        = (typeof(res->st_ino))st->st_ino;
		res->st_mode       = (typeof(res->st_mode))st->st_mode;
		res->st_nlink      = (typeof(res->st_nlink))st->st_nlink;
		res->st_uid        = (typeof(res->st_uid))st->st_uid;
		res->st_gid        = (typeof(res->st_gid))st->st_gid;
		res->st_rdev       = (typeof(res->st_rdev))st->st_rdev;
		res->st_size       = (typeof(res->st_size))st->st_size;
		res->st_blksize    = (typeof(res->st_blksize))st->st_blksize;
		res->st_blocks     = (typeof(res->st_blocks))st->st_blocks;
		res->st_atime      = (typeof(res->st_atime))st->st_atime;
		res->st_atime_nsec = (typeof(res->st_atime_nsec))st->st_atimensec;
		res->st_mtime      = (typeof(res->st_mtime))st->st_mtime;
		res->st_mtime_nsec = (typeof(res->st_mtime_nsec))st->st_mtimensec;
		res->st_ctime      = (typeof(res->st_ctime))st->st_ctime;
		res->st_ctime_nsec = (typeof(res->st_ctime_nsec))st->st_ctimensec;
	}	break;

#ifndef __LINUX_STAT32_MATCHES_LINUX_STAT64
	case _STAT_VER_KERNEL | STAT_CONV_F_64:
#ifdef _STAT_VER_KERNEL64
	case _STAT_VER_KERNEL64:
#endif /* _STAT_VER_KERNEL64 */
	{
		struct linux_stat64 *res;
		res = (struct linux_stat64 *)buf;
		bzero(res, sizeof(*res));
		res->st_dev        = (typeof(res->st_dev))st->st_dev;
#ifdef _HAVE_LINUX_STAT64___ST_INO
		res->__st_ino      = (typeof(res->__st_ino))st->st_ino;
#endif /* _HAVE_LINUX_STAT64___ST_INO */
		res->st_mode       = (typeof(res->st_mode))st->st_mode;
		res->st_nlink      = (typeof(res->st_nlink))st->st_nlink;
		res->st_uid        = (typeof(res->st_uid))st->st_uid;
		res->st_gid        = (typeof(res->st_gid))st->st_gid;
		res->st_rdev       = (typeof(res->st_rdev))st->st_rdev;
		res->st_size       = (typeof(res->st_size))st->st_size;
		res->st_blksize    = (typeof(res->st_blksize))st->st_blksize;
		res->st_blocks     = (typeof(res->st_blocks))st->st_blocks;
		res->st_atime      = (typeof(res->st_atime))st->st_atime;
		res->st_atime_nsec = (typeof(res->st_atime_nsec))st->st_atimensec;
		res->st_mtime      = (typeof(res->st_mtime))st->st_mtime;
		res->st_mtime_nsec = (typeof(res->st_mtime_nsec))st->st_mtimensec;
		res->st_ctime      = (typeof(res->st_ctime))st->st_ctime;
		res->st_ctime_nsec = (typeof(res->st_ctime_nsec))st->st_ctimensec;
		res->st_ino        = (typeof(res->st_ino))st->st_ino;
	}	break;
#endif /* !__LINUX_STAT32_MATCHES_LINUX_STAT64 */

#ifdef _STAT_VER_GLIBC2_1
	case _STAT_VER_GLIBC2_1: {
		struct glibc21_stat {
			__dev_t st_dev;
			__ino64_t st_ino;
			__mode_t st_mode;
			__nlink_t st_nlink;
			__uid_t st_uid;
			__gid_t st_gid;
			__dev_t st_rdev;
			__off_t st_size;
			__time_t st_atime;
			__time_t st_mtime;
			__time_t st_ctime;
			__blkcnt64_t st_blocks;
			__blksize_t st_blksize;
			unsigned int st_flags;
			unsigned int st_gen;
			int __pad3;
			long __glibc_reserved[4];
		};
		struct glibc21_stat *res;
		res = (struct glibc21_stat *)buf;
		bzero(res, sizeof(*res));
		res->st_dev     = st->st_dev;
		res->st_ino     = st->st_ino;
		res->st_mode    = st->st_mode;
		res->st_nlink   = st->st_nlink;
		res->st_uid     = st->st_uid;
		res->st_gid     = st->st_gid;
		res->st_rdev    = st->st_rdev;
		res->st_size    = st->st_size;
		res->st_atime   = st->st_atime;
		res->st_mtime   = st->st_mtime;
		res->st_ctime   = st->st_ctime;
		res->st_blocks  = st->st_blocks;
		res->st_blksize = st->st_blksize;
		res->st_flags   = st->st_flags;
		res->st_gen     = st->st_gen;
	}	break;
#endif /* _STAT_VER_GLIBC2_1 */

	case _STAT_VER_LINUX:
		convstat_kos2glc((struct __glc_stat *)buf, st);
		break;

	case _STAT_VER_LINUX | STAT_CONV_F_64:
		convstat_kos2glc64((struct __glc_stat64 *)buf, st);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}

DEFINE_PUBLIC_ALIAS(__fxstat, libc___fxstat);
DEFINE_PUBLIC_ALIAS(_fxstat, libc___fxstat);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((3)) int
NOTHROW_RPC(LIBCCALL libc___fxstat)(int vers, fd_t fd, void *__restrict buf) {
	struct stat info;
	errno_t error = sys_kfstat(fd, &info);
	if (error == -EOK)
		error = stat_conv(vers, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__fxstat64, libc___fxstat64);
DEFINE_PUBLIC_ALIAS(_fxstat64, libc___fxstat64);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((3)) int
NOTHROW_RPC(LIBCCALL libc___fxstat64)(int vers, fd_t fd, void *__restrict buf) {
	struct stat info;
	errno_t error = sys_kfstat(fd, &info);
	if (error == -EOK)
		error = stat_conv(vers | STAT_CONV_F_64, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__xstat, libc___xstat);
DEFINE_PUBLIC_ALIAS(_xstat, libc___xstat);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc___xstat)(int vers, char const *filename, void *__restrict buf) {
	struct stat info;
	errno_t error = sys_kstat(filename, &info);
	if (error == -EOK)
		error = stat_conv(vers, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__xstat64, libc___xstat64);
DEFINE_PUBLIC_ALIAS(_xstat64, libc___xstat64);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc___xstat64)(int vers, char const *filename, void *__restrict buf) {
	struct stat info;
	errno_t error = sys_kstat(filename, &info);
	if (error == -EOK)
		error = stat_conv(vers | STAT_CONV_F_64, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__fxstatat, libc___fxstatat);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((3, 4)) int
NOTHROW_RPC(LIBCCALL libc___fxstatat)(int vers, fd_t dfd,
                                      char const *filename,
                                      void *__restrict buf,
                                      atflag_t flags) {
	struct stat info;
	errno_t error = sys_kfstatat(dfd, filename, &info, flags);
	if (error == -EOK)
		error = stat_conv(vers, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__fxstatat64, libc___fxstatat64);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((3, 4)) int
NOTHROW_RPC(LIBCCALL libc___fxstatat64)(int vers, fd_t dfd,
                                        char const *filename,
                                        void *__restrict buf,
                                        atflag_t flags) {
	struct stat info;
	errno_t error = sys_kfstatat(dfd, filename, &info, flags);
	if (error == -EOK)
		error = stat_conv(vers | STAT_CONV_F_64, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__lxstat, libc___lxstat);
DEFINE_PUBLIC_ALIAS(_lxstat, libc___lxstat);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc___lxstat)(int vers, char const *filename, void *__restrict buf) {
	struct stat info;
	errno_t error = sys_klstat(filename, &info);
	if (error == -EOK)
		error = stat_conv(vers, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__lxstat64, libc___lxstat64);
DEFINE_PUBLIC_ALIAS(_lxstat64, libc___lxstat64);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc___lxstat64)(int vers, char const *filename, void *__restrict buf) {
	struct stat info;
	errno_t error = sys_klstat(filename, &info);
	if (error == -EOK)
		error = stat_conv(vers | STAT_CONV_F_64, &info, buf);
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__xmknod, libc___xmknod);
DEFINE_PUBLIC_ALIAS(_xmknod, libc___xmknod);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((2, 4)) int
NOTHROW_RPC(LIBCCALL libc___xmknod)(int vers, char const *path, mode_t mode, void *dev) {
	errno_t error;
	if (vers == _MKNOD_VER_LINUX) {
		error = sys_mknod(path, mode, *(uint32_t *)dev);
	} else {
		error = -EINVAL;
	}
	return libc_seterrno_syserr(error);
}

DEFINE_PUBLIC_ALIAS(__xmknodat, libc___xmknodat);
DEFINE_PUBLIC_ALIAS(_xmknodat, libc___xmknodat);
INTERN ATTR_SECTION(".text.crt.glibc.fs.stat") NONNULL((3, 5)) int
NOTHROW_RPC(LIBCCALL libc___xmknodat)(int vers, fd_t dfd, char const *path, mode_t mode, void *dev) {
	errno_t error;
	if (vers == _MKNOD_VER_LINUX) {
		error = sys_mknodat(dfd, path, mode, *(uint32_t *)dev);
	} else {
		error = -EINVAL;
	}
	return libc_seterrno_syserr(error);
}




/* DOS stat() emulation */
DEFINE_PUBLIC_ALIAS(_fstat, libc_dos_fstat32);
DEFINE_PUBLIC_ALIAS(_fstat32, libc_dos_fstat32);
DEFINE_PUBLIC_ALIAS(_fstati64, libc_dos_fstat32i64);
DEFINE_PUBLIC_ALIAS(_fstat32i64, libc_dos_fstat32i64);
DEFINE_PUBLIC_ALIAS(_fstat64, libc_dos_fstat64);
DEFINE_PUBLIC_ALIAS(_fstat64i32, libc_dos_fstat64);
DEFINE_PUBLIC_ALIAS(_stat, libc_dos_stat32);
DEFINE_PUBLIC_ALIAS(_stat32, libc_dos_stat32);
DEFINE_PUBLIC_ALIAS(_stati64, libc_dos_stat32i64);
DEFINE_PUBLIC_ALIAS(_stat32i64, libc_dos_stat32i64);
DEFINE_PUBLIC_ALIAS(_stat64, libc_dos_stat64);
DEFINE_PUBLIC_ALIAS(_stat64i32, libc_dos_stat64);
DEFINE_INTERN_ALIAS(libc__fstat, libc_dos_fstat32);
DEFINE_INTERN_ALIAS(libc__fstat32, libc_dos_fstat32);
DEFINE_INTERN_ALIAS(libc__fstati64, libc_dos_fstat32i64);
DEFINE_INTERN_ALIAS(libc__fstat32i64, libc_dos_fstat32i64);
DEFINE_INTERN_ALIAS(libc__fstat64, libc_dos_fstat64);
DEFINE_INTERN_ALIAS(libc__fstat64i32, libc_dos_fstat64);
DEFINE_INTERN_ALIAS(libc__stat, libc_dos_stat32);
DEFINE_INTERN_ALIAS(libc__stat32, libc_dos_stat32);
DEFINE_INTERN_ALIAS(libc__stati64, libc_dos_stat32i64);
DEFINE_INTERN_ALIAS(libc__stat32i64, libc_dos_stat32i64);
DEFINE_INTERN_ALIAS(libc__stat64, libc_dos_stat64);
DEFINE_INTERN_ALIAS(libc__stat64i32, libc_dos_stat64);

LOCAL ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) void LIBCCALL
convstat_kos2dos32(struct __dos_stat32 *__restrict dst,
                   struct __kos_stat const *__restrict src) {
	dst->st_dev     = (u32)src->st_dev;
	dst->st_ino     = (u16)src->st_ino32;
	dst->st_mode    = (u16)src->st_mode;
	dst->st_nlink   = (s16)src->st_nlink;
	dst->st_uid     = (s16)src->st_uid;
	dst->st_gid     = (s16)src->st_gid;
	dst->st_rdev    = (u32)src->st_rdev;
	dst->st_size32  = (u32)src->st_size32;
	dst->st_atime32 = (time32_t)src->st_atim32.tv_sec;
	dst->st_mtime32 = (time32_t)src->st_mtim32.tv_sec;
	dst->st_ctime32 = (time32_t)src->st_ctim32.tv_sec;
}
LOCAL ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) void LIBCCALL
convstat_kos2dos32i64(struct __dos_stat32i64 *__restrict dst,
                      struct __kos_stat const *__restrict src) {
	dst->st_dev     = (u32)src->st_dev;
	dst->st_ino     = (u16)src->st_ino32;
	dst->st_mode    = (u16)src->st_mode;
	dst->st_nlink   = (s16)src->st_nlink;
	dst->st_uid     = (s16)src->st_uid;
	dst->st_gid     = (s16)src->st_gid;
	dst->st_rdev    = (u32)src->st_rdev;
	dst->st_size64  = (u64)src->st_size64;
	dst->st_atime32 = (time32_t)src->st_atim32.tv_sec;
	dst->st_mtime32 = (time32_t)src->st_mtim32.tv_sec;
	dst->st_ctime32 = (time32_t)src->st_ctim32.tv_sec;
}

LOCAL ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) void LIBCCALL
convstat_kos2dos64(struct __dos_stat64 *__restrict dst,
                   struct __kos_stat const *__restrict src) {
	dst->st_dev     = (u32)src->st_dev;
	dst->st_ino     = (u16)src->st_ino32;
	dst->st_mode    = (u16)src->st_mode;
	dst->st_nlink   = (s16)src->st_nlink;
	dst->st_uid     = (s16)src->st_uid;
	dst->st_gid     = (s16)src->st_gid;
	dst->st_rdev    = (u32)src->st_rdev;
	dst->st_size64  = (u64)src->st_size64;
	dst->st_atime64 = (time64_t)src->st_atim64.tv_sec;
	dst->st_mtime64 = (time64_t)src->st_mtim64.tv_sec;
	dst->st_ctime64 = (time64_t)src->st_ctim64.tv_sec;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_dos_fstat32)(fd_t fd,
                                       struct __dos_stat32 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos32(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_dos_fstat32i64)(fd_t fd,
                                          struct __dos_stat32i64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos32i64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_dos_fstat64)(fd_t fd,
                                       struct __dos_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_dos_stat32)(char const *__restrict filename,
                                      struct __dos_stat32 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_dos_stat32i64)(char const *__restrict filename,
                                         struct __dos_stat32i64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32i64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_dos_stat64)(char const *__restrict filename,
                                      struct __dos_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos64(buf, &st);
	return result;
}


DEFINE_PUBLIC_ALIAS(DOS$_stat, libd_dos_stat32);
DEFINE_PUBLIC_ALIAS(DOS$_stat32, libd_dos_stat32);
DEFINE_PUBLIC_ALIAS(DOS$_stati64, libd_dos_stat32i64);
DEFINE_PUBLIC_ALIAS(DOS$_stat32i64, libd_dos_stat32i64);
DEFINE_PUBLIC_ALIAS(DOS$_stat64, libd_dos_stat64);
DEFINE_PUBLIC_ALIAS(DOS$_stat64i32, libd_dos_stat64);
DEFINE_INTERN_ALIAS(libd__stat, libd_dos_stat32);
DEFINE_INTERN_ALIAS(libd__stat32, libd_dos_stat32);
DEFINE_INTERN_ALIAS(libd__stati64, libd_dos_stat32i64);
DEFINE_INTERN_ALIAS(libd__stat32i64, libd_dos_stat32i64);
DEFINE_INTERN_ALIAS(libd__stat64, libd_dos_stat64);
DEFINE_INTERN_ALIAS(libd__stat64i32, libd_dos_stat64);

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libd_dos_stat32)(char const *__restrict filename,
                                      struct __dos_stat32 *__restrict buf) {
	struct __kos_stat st;
	int result = libd_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libd_dos_stat32i64)(char const *__restrict filename,
                                         struct __dos_stat32i64 *__restrict buf) {
	struct __kos_stat st;
	int result = libd_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32i64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.compat.dos.fs.stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libd_dos_stat64)(char const *__restrict filename,
                                      struct __dos_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libd_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos64(buf, &st);
	return result;
}







/*[[[head:libd_mkdir,hash:CRC-32=0xb6c6cee3]]]*/
/* >> mkdir(2) */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mkdir)(char const *pathname,
                                 mode_t mode)
/*[[[body:libd_mkdir]]]*/
{
	return libc_fmkdirat(AT_FDCWD, pathname, mode, libd_AT_DOSPATH);
}
/*[[[end:libd_mkdir]]]*/

/*[[[head:libc_mkdir,hash:CRC-32=0x23d69e46]]]*/
/* >> mkdir(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mkdir)(char const *pathname,
                                 mode_t mode)
/*[[[body:libc_mkdir]]]*/
{
	errno_t result;
	result = sys_mkdirat(AT_FDCWD, pathname, mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mkdir]]]*/

/*[[[head:libd_chmod,hash:CRC-32=0x7d876a1a]]]*/
/* >> chmod(2) */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_chmod)(char const *filename,
                                 mode_t mode)
/*[[[body:libd_chmod]]]*/
{
	return libc_fchmodat(AT_FDCWD, filename, mode, libd_AT_DOSPATH);
}
/*[[[end:libd_chmod]]]*/

/*[[[head:libc_chmod,hash:CRC-32=0x8da3e74c]]]*/
/* >> chmod(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chmod)(char const *filename,
                                 mode_t mode)
/*[[[body:libc_chmod]]]*/
{
	errno_t result;
	result = sys_fchmodat(AT_FDCWD, filename, mode, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chmod]]]*/

/*[[[head:libd_lchmod,hash:CRC-32=0xb033c580]]]*/
/* >> lchmod(2) */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_lchmod)(char const *filename,
                                  mode_t mode)
/*[[[body:libd_lchmod]]]*/
{
	return libc_fchmodat(AT_FDCWD, filename, mode, libd_AT_DOSPATH | AT_SYMLINK_NOFOLLOW);
}
/*[[[end:libd_lchmod]]]*/


/*[[[head:libc_lchmod,hash:CRC-32=0x3a2b4d4d]]]*/
/* >> lchmod(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_lchmod)(char const *filename,
                                  mode_t mode)
/*[[[body:libc_lchmod]]]*/
{
	errno_t result;
	result = sys_fchmodat(AT_FDCWD, filename, mode, AT_SYMLINK_NOFOLLOW);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lchmod]]]*/

/*[[[head:libc_umask,hash:CRC-32=0x66e3a967]]]*/
/* >> umask(2) */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") mode_t
NOTHROW_NCX(LIBCCALL libc_umask)(mode_t mode)
/*[[[body:libc_umask]]]*/
{
	return sys_umask(mode);
}
/*[[[end:libc_umask]]]*/

/*[[[head:libc_getumask,hash:CRC-32=0x556d0e0d]]]*/
/* >> getumask(2)
 * Return the current umask.
 * WARNING: This function isn't thread-safe */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") mode_t
NOTHROW_NCX(LIBCCALL libc_getumask)(void)
/*[[[body:libc_getumask]]]*/
{
	mode_t result;
	result = sys_umask(0);
	sys_umask(result);
	return result;
}
/*[[[end:libc_getumask]]]*/

/*[[[head:libd_fmkdirat,hash:CRC-32=0xd70f0e8c]]]*/
/* >> fmkdirat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_fmkdirat)(fd_t dirfd,
                                    char const *pathname,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:libd_fmkdirat]]]*/
{
	return libc_fmkdirat(dirfd, pathname, mode, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_fmkdirat]]]*/

/*[[[head:libc_fmkdirat,hash:CRC-32=0x1a4187d0]]]*/
/* >> fmkdirat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fmkdirat)(fd_t dirfd,
                                    char const *pathname,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:libc_fmkdirat]]]*/
{
	errno_t result;
	result = sys_fmkdirat(dirfd, pathname, mode, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fmkdirat]]]*/

/*[[[head:libd_fmknodat,hash:CRC-32=0xaaa1f9fc]]]*/
/* >> fmknodat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_fmknodat)(fd_t dirfd,
                                    char const *nodename,
                                    mode_t mode,
                                    dev_t dev,
                                    atflag_t flags)
/*[[[body:libd_fmknodat]]]*/
{
	return libc_fmknodat(dirfd, nodename, mode, dev, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_fmknodat]]]*/

/*[[[head:libc_fmknodat,hash:CRC-32=0xcc411bd]]]*/
/* >> fmknodat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fmknodat)(fd_t dirfd,
                                    char const *nodename,
                                    mode_t mode,
                                    dev_t dev,
                                    atflag_t flags)
/*[[[body:libc_fmknodat]]]*/
{
	errno_t result;
	result = sys_fmknodat(dirfd, nodename, mode, dev, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fmknodat]]]*/

/*[[[head:libd_fchmodat,hash:CRC-32=0x760c9903]]]*/
/* >> fchmodat(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_fchmodat)(fd_t dirfd,
                                    char const *filename,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:libd_fchmodat]]]*/
{
	return libc_fchmodat(dirfd, filename, mode, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_fchmodat]]]*/

/*[[[head:libc_fchmodat,hash:CRC-32=0x11dc663c]]]*/
/* >> fchmodat(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fchmodat)(fd_t dirfd,
                                    char const *filename,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:libc_fchmodat]]]*/
{
	errno_t result;
	result = sys_fchmodat(dirfd, filename, mode, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchmodat]]]*/

/*[[[head:libd_mkdirat,hash:CRC-32=0x338e699c]]]*/
/* >> mkdirat(2) */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_mkdirat)(fd_t dirfd,
                                   char const *pathname,
                                   mode_t mode)
/*[[[body:libd_mkdirat]]]*/
{
	return libc_fmkdirat(dirfd, pathname, mode, libd_AT_DOSPATH);
}
/*[[[end:libd_mkdirat]]]*/

/*[[[head:libc_mkdirat,hash:CRC-32=0x4c90230b]]]*/
/* >> mkdirat(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_mkdirat)(fd_t dirfd,
                                   char const *pathname,
                                   mode_t mode)
/*[[[body:libc_mkdirat]]]*/
{
	errno_t result;
	result = sys_mkdirat(dirfd, pathname, mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mkdirat]]]*/

/*[[[head:libc_fchmod,hash:CRC-32=0x704729c3]]]*/
/* >> fchmod(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") int
NOTHROW_RPC(LIBCCALL libc_fchmod)(fd_t fd,
                                  mode_t mode)
/*[[[body:libc_fchmod]]]*/
{
	errno_t result;
	result = sys_fchmod(fd, mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchmod]]]*/

/*[[[head:libd_mknod,hash:CRC-32=0x84d97e77]]]*/
/* >> mknod(2) */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mknod)(char const *nodename,
                                 mode_t mode,
                                 dev_t dev)
/*[[[body:libd_mknod]]]*/
{
	return libc_fmknodat(AT_FDCWD, nodename, mode, dev, libd_AT_DOSPATH);
}
/*[[[end:libd_mknod]]]*/

/*[[[head:libc_mknod,hash:CRC-32=0xfb80f6ef]]]*/
/* >> mknod(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mknod)(char const *nodename,
                                 mode_t mode,
                                 dev_t dev)
/*[[[body:libc_mknod]]]*/
{
	errno_t result;
#ifdef SYS_mknod
	result = sys_mknod(nodename, mode, dev);
#else /* SYS_mknod */
	result = sys_mknodat(AT_FDCWD, nodename, mode, dev);
#endif /* !SYS_mknod */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mknod]]]*/

/*[[[head:libd_mknodat,hash:CRC-32=0xeada9488]]]*/
/* >> mknodat(2) */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_mknodat)(fd_t dirfd,
                                   char const *nodename,
                                   mode_t mode,
                                   dev_t dev)
/*[[[body:libd_mknodat]]]*/
{
	return libc_fmknodat(dirfd, nodename, mode, dev, libd_AT_DOSPATH);
}
/*[[[end:libd_mknodat]]]*/

/*[[[head:libc_mknodat,hash:CRC-32=0x962170b7]]]*/
/* >> mknodat(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_mknodat)(fd_t dirfd,
                                   char const *nodename,
                                   mode_t mode,
                                   dev_t dev)
/*[[[body:libc_mknodat]]]*/
{
	errno_t result;
	result = sys_mknodat(dirfd, nodename, mode, dev);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mknodat]]]*/

/*[[[head:libd_utimensat,hash:CRC-32=0x7b3eac46]]]*/
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_utimensat)(fd_t dirfd,
                                     char const *filename,
                                     struct timespec const times[2 /*or:3*/],
                                     atflag_t flags)
/*[[[body:libd_utimensat]]]*/
{
	return libc_utimensat(dirfd, filename, times, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_utimensat]]]*/



/*[[[head:libc_utimensat,hash:CRC-32=0x2d0e96da]]]*/
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_utimensat)(fd_t dirfd,
                                     char const *filename,
                                     struct timespec const times[2 /*or:3*/],
                                     atflag_t flags)
/*[[[body:libc_utimensat]]]*/
{
	errno_t result;
	result = sys_utimensat(dirfd, filename, times, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_utimensat]]]*/

/*[[[head:libd_utimensat64,hash:CRC-32=0xc7b1c5a6]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd_utimensat64, libd_utimensat);
#else /* MAGIC:alias */
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_utimensat64)(fd_t dirfd,
                                       char const *filename,
                                       struct timespec64 const times[2 /*or:3*/],
                                       atflag_t flags)
/*[[[body:libd_utimensat64]]]*/
{
	return libc_utimensat64(dirfd, filename, times, flags | libd_AT_DOSPATH);
}
#endif /* MAGIC:alias */
/*[[[end:libd_utimensat64]]]*/

/*[[[head:libc_utimensat64,hash:CRC-32=0x3b985c10]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_utimensat64, libc_utimensat);
#else /* MAGIC:alias */
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_utimensat64)(fd_t dirfd,
                                       char const *filename,
                                       struct timespec64 const times[2 /*or:3*/],
                                       atflag_t flags)
/*[[[body:libc_utimensat64]]]*/
{
	errno_t result;
#ifdef SYS_utimensat64
	result = sys_utimensat64(dirfd, filename, times, flags);
#elif defined(SYS_utimensat_time64)
	result = sys_utimensat_time64(dirfd, filename, times, flags);
#else /* ... */
#error "No way to implement `utimensat64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_utimensat64]]]*/

/*[[[head:libc_futimens,hash:CRC-32=0x4157f34c]]]*/
/* >> futimens(2), futimens64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") int
NOTHROW_RPC(LIBCCALL libc_futimens)(fd_t fd,
                                    struct timespec const times[2 /*or:3*/])
/*[[[body:libc_futimens]]]*/
{
	errno_t result;
	result = sys_utimensat(fd, NULL, times, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futimens]]]*/

/*[[[head:libc_futimens64,hash:CRC-32=0x80bd0f8a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futimens64, libc_futimens);
#else /* MAGIC:alias */
/* >> futimens(2), futimens64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") int
NOTHROW_RPC(LIBCCALL libc_futimens64)(fd_t fd,
                                      struct timespec64 const times[2 /*or:3*/])
/*[[[body:libc_futimens64]]]*/
{
	errno_t result;
#ifdef SYS_utimensat64
	result = sys_utimensat64(fd, NULL, times, 0);
#elif defined(SYS_utimensat_time64)
	result = sys_utimensat_time64(fd, NULL, times, 0);
#else /* ... */
#error "No way to implement `futimens64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futimens64]]]*/

/*[[[impl:libc__wstat64i32]]]*/
/*[[[impl:libd__wstat64i32]]]*/
DEFINE_INTERN_ALIAS(libc__wstat64i32, libc__wstat64);
DEFINE_INTERN_ALIAS(libd__wstat64i32, libd__wstat64);

/*[[[head:libc__wstat64,hash:CRC-32=0x2b12ba1e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.stat") NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc__wstat64)(char32_t const *filename,
                                    struct __dos_stat64 *buf)
/*[[[body:libc__wstat64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = convert_c32tombs(filename);
	if likely(used_filename) {
		result = libc_dos_stat64(used_filename, buf);
		free(used_filename);
	}
	return result;
}
/*[[[end:libc__wstat64]]]*/

/*[[[head:libd__wstat64,hash:CRC-32=0xbff437e6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.stat") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__wstat64)(char16_t const *filename,
                                    struct __dos_stat64 *buf)
/*[[[body:libd__wstat64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = convert_c16tombs(filename);
	if likely(used_filename) {
		result = libd_dos_stat64(used_filename, buf);
		free(used_filename);
	}
	return result;
}
/*[[[end:libd__wstat64]]]*/

/*[[[head:libc__wstat32i64,hash:CRC-32=0x9e88dcc0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.stat") NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc__wstat32i64)(char32_t const *filename,
                                       struct __dos_stat32i64 *buf)
/*[[[body:libc__wstat32i64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = convert_c32tombs(filename);
	if likely(used_filename) {
		result = libc_dos_stat32i64(used_filename, buf);
		free(used_filename);
	}
	return result;
}
/*[[[end:libc__wstat32i64]]]*/

/*[[[head:libd__wstat32i64,hash:CRC-32=0x28148a19]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.stat") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__wstat32i64)(char16_t const *filename,
                                       struct __dos_stat32i64 *buf)
/*[[[body:libd__wstat32i64]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = convert_c16tombs(filename);
	if likely(used_filename) {
		result = libd_dos_stat32i64(used_filename, buf);
		free(used_filename);
	}
	return result;
}
/*[[[end:libd__wstat32i64]]]*/

/*[[[head:libc__wstat32,hash:CRC-32=0x1bdc2abc]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.stat") NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc__wstat32)(char32_t const *filename,
                                    struct __dos_stat32 *buf)
/*[[[body:libc__wstat32]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = convert_c32tombs(filename);
	if likely(used_filename) {
		result = libc_dos_stat32(used_filename, buf);
		free(used_filename);
	}
	return result;
}
/*[[[end:libc__wstat32]]]*/

/*[[[head:libd__wstat32,hash:CRC-32=0x8f3aa744]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.stat") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__wstat32)(char16_t const *filename,
                                    struct __dos_stat32 *buf)
/*[[[body:libd__wstat32]]]*/
{
	int result = -1;
	char *used_filename;
	used_filename = convert_c16tombs(filename);
	if likely(used_filename) {
		result = libd_dos_stat32(used_filename, buf);
		free(used_filename);
	}
	return result;
}
/*[[[end:libd__wstat32]]]*/





/*[[[start:exports,hash:CRC-32=0x4d44fc43]]]*/
DEFINE_PUBLIC_ALIAS(DOS$__mkdir, libd_mkdir);
DEFINE_PUBLIC_ALIAS(DOS$__libc_mkdir, libd_mkdir);
DEFINE_PUBLIC_ALIAS(DOS$mkdir, libd_mkdir);
DEFINE_PUBLIC_ALIAS(__mkdir, libc_mkdir);
DEFINE_PUBLIC_ALIAS(__libc_mkdir, libc_mkdir);
DEFINE_PUBLIC_ALIAS(mkdir, libc_mkdir);
DEFINE_PUBLIC_ALIAS(DOS$_chmod, libd_chmod);
DEFINE_PUBLIC_ALIAS(DOS$__chmod, libd_chmod);
DEFINE_PUBLIC_ALIAS(DOS$__libc_chmod, libd_chmod);
DEFINE_PUBLIC_ALIAS(DOS$chmod, libd_chmod);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_chmod, libc_chmod);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__chmod, libc_chmod);
DEFINE_PUBLIC_ALIAS(__libc_chmod, libc_chmod);
DEFINE_PUBLIC_ALIAS(chmod, libc_chmod);
DEFINE_PUBLIC_ALIAS(DOS$lchmod, libd_lchmod);
DEFINE_PUBLIC_ALIAS(lchmod, libc_lchmod);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_umask, libc_umask);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__umask, libc_umask);
DEFINE_PUBLIC_ALIAS(__libc_umask, libc_umask);
DEFINE_PUBLIC_ALIAS(umask, libc_umask);
DEFINE_PUBLIC_ALIAS(getumask, libc_getumask);
DEFINE_PUBLIC_ALIAS(DOS$fmkdirat, libd_fmkdirat);
DEFINE_PUBLIC_ALIAS(fmkdirat, libc_fmkdirat);
DEFINE_PUBLIC_ALIAS(DOS$fmknodat, libd_fmknodat);
DEFINE_PUBLIC_ALIAS(fmknodat, libc_fmknodat);
DEFINE_PUBLIC_ALIAS(DOS$fchmodat, libd_fchmodat);
DEFINE_PUBLIC_ALIAS(fchmodat, libc_fchmodat);
DEFINE_PUBLIC_ALIAS(DOS$mkdirat, libd_mkdirat);
DEFINE_PUBLIC_ALIAS(mkdirat, libc_mkdirat);
DEFINE_PUBLIC_ALIAS(__fchmod, libc_fchmod);
DEFINE_PUBLIC_ALIAS(__libc_fchmod, libc_fchmod);
DEFINE_PUBLIC_ALIAS(fchmod, libc_fchmod);
DEFINE_PUBLIC_ALIAS(DOS$mknod, libd_mknod);
DEFINE_PUBLIC_ALIAS(mknod, libc_mknod);
DEFINE_PUBLIC_ALIAS(DOS$mknodat, libd_mknodat);
DEFINE_PUBLIC_ALIAS(mknodat, libc_mknodat);
DEFINE_PUBLIC_ALIAS(DOS$utimensat, libd_utimensat);
DEFINE_PUBLIC_ALIAS(utimensat, libc_utimensat);
DEFINE_PUBLIC_ALIAS(DOS$utimensat64, libd_utimensat64);
DEFINE_PUBLIC_ALIAS(utimensat64, libc_utimensat64);
DEFINE_PUBLIC_ALIAS(futimens, libc_futimens);
DEFINE_PUBLIC_ALIAS(futimens64, libc_futimens64);
DEFINE_PUBLIC_ALIAS(DOS$_wstat32, libd__wstat32);
DEFINE_PUBLIC_ALIAS(_wstat32, libc__wstat32);
DEFINE_PUBLIC_ALIAS(DOS$_wstat64, libd__wstat64);
DEFINE_PUBLIC_ALIAS(_wstat64, libc__wstat64);
DEFINE_PUBLIC_ALIAS(DOS$_wstat32i64, libd__wstat32i64);
DEFINE_PUBLIC_ALIAS(_wstat32i64, libc__wstat32i64);
DEFINE_PUBLIC_ALIAS(DOS$_wstat64i32, libd__wstat64i32);
DEFINE_PUBLIC_ALIAS(_wstat64i32, libc__wstat64i32);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STAT_C */
