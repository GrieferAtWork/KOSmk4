/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
#include <syscall.h>
#include <unistd.h>

#include "../libc/uchar.h"
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
INTERN ATTR_SECTION(".text.crt.fs.stat.kos_fstat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_fstat)(fd_t fd,
                                     struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstat(fd,
	                   (struct stat *)buf);
	return libc_seterrno_syserr(error);
}

INTERN ATTR_SECTION(".text.crt.fs.stat.kos_stat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_stat)(char const *__restrict filename,
                                    struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstatat(AT_FDCWD,
	                     filename,
	                     (struct stat *)buf,
	                     0);
	return libc_seterrno_syserr(error);
}

INTERN ATTR_SECTION(".text.crt.fs.stat.kos_lstat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_lstat)(char const *__restrict filename,
                                     struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstatat(AT_FDCWD,
	                     filename,
	                     (struct stat *)buf,
	                     AT_SYMLINK_NOFOLLOW);
	return libc_seterrno_syserr(error);
}

INTERN ATTR_SECTION(".text.crt.fs.stat.kos_fstatat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_kos_fstatat)(fd_t dirfd,
                                       char const *__restrict filename,
                                       struct __kos_stat *__restrict buf,
                                       atflag_t flags) {
	errno_t error;
	error = sys_kfstatat(dirfd,
	                     filename,
	                     (struct stat *)buf,
	                     flags);
	return libc_seterrno_syserr(error);
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
LOCAL NONNULL((1, 2)) void LIBCCALL
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

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.cyg_fstat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_cyg_fstat)(fd_t fd,
                                     struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.cyg_stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_cyg_stat)(char const *__restrict filename,
                                    struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.cyg_lstat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_cyg_lstat)(char const *__restrict filename,
                                     struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.cyg_fstatat") NONNULL((2, 3)) int
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
LOCAL NONNULL((1, 2)) void LIBCCALL
convstat_kos2glc(struct __glc_stat *__restrict dst,
                 struct __kos_stat const *__restrict src) {
	dst->st_dev     = (u64)src->st_dev;
	dst->st_ino     = (u32)src->st_ino32;
	dst->st_mode    = (u32)src->st_mode;
	dst->st_nlink   = (u32)src->st_nlink;
	dst->st_uid     = (u32)src->st_uid;
	dst->st_gid     = (u32)src->st_gid;
	dst->st_rdev    = (u64)src->st_rdev;
	dst->st_size    = (u32)src->st_size32;
	dst->st_blksize = (u32)src->st_blksize;
	dst->st_blocks  = (u32)src->st_blocks32;
	dst->st_atim    = src->st_atim32;
	dst->st_mtim    = src->st_mtim32;
	dst->st_ctim    = src->st_ctim32;
}

LOCAL NONNULL((1, 2)) void LIBCCALL
convstat_kos2glc64(struct __glc_stat64 *__restrict dst,
                   struct __kos_stat const *__restrict src) {
	dst->st_dev     = (u64)src->st_dev;
	dst->st_ino32   = (u32)src->st_ino32;
	dst->st_mode    = (u32)src->st_mode;
	dst->st_nlink   = (u32)src->st_nlink;
	dst->st_uid     = (u32)src->st_uid;
	dst->st_gid     = (u32)src->st_gid;
	dst->st_rdev    = (u64)src->st_rdev;
	dst->st_size64  = (u64)src->st_size64;
	dst->st_blksize = (u32)src->st_blksize;
	dst->st_blocks  = (u32)src->st_blocks32;
	dst->st_atim    = src->st_atim32;
	dst->st_mtim    = src->st_mtim32;
	dst->st_ctim    = src->st_ctim32;
	dst->st_ino64   = (u64)src->st_ino64;
}

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstat") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_glc_fstat)(fd_t fd,
                                     struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstat64") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_glc_fstat64)(fd_t fd,
                                       struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_stat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_stat)(char const *__restrict filename,
                                    struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_stat64") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_stat64)(char const *__restrict filename,
                                      struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_lstat") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_lstat)(char const *__restrict filename,
                                     struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_lstat64") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_glc_lstat64)(char const *__restrict filename,
                                       struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstatat") NONNULL((2, 3)) int
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

INTERN ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstatat64") NONNULL((2, 3)) int
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

LOCAL NONNULL((1, 2)) void LIBCCALL
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
LOCAL NONNULL((1, 2)) void LIBCCALL
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

LOCAL NONNULL((1, 2)) void LIBCCALL
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

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.dos_fstat32") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_dos_fstat32)(fd_t fd,
                                       struct __dos_stat32 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos32(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.dos_fstat32i64") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_dos_fstat32i64)(fd_t fd,
                                          struct __dos_stat32i64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos32i64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.dos_fstat64") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_dos_fstat64)(fd_t fd,
                                       struct __dos_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.dos_stat32") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_dos_stat32)(char const *__restrict filename,
                                      struct __dos_stat32 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.dos_stat32i64") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_dos_stat32i64)(char const *__restrict filename,
                                         struct __dos_stat32i64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32i64(buf, &st);
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.fs.stat.dos_stat64") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_dos_stat64)(char const *__restrict filename,
                                      struct __dos_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos64(buf, &st);
	return result;
}







/*[[[head:libc_mkdir,hash:CRC-32=0xd15b9301]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mkdir)(char const *pathname,
                                 mode_t mode)
/*[[[body:libc_mkdir]]]*/
{
	errno_t result;
	result = sys_mkdirat(AT_FDCWD,
	                     pathname,
	                     mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mkdir]]]*/

/*[[[head:libc_chmod,hash:CRC-32=0x4c77b6a9]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chmod)(char const *filename,
                                 mode_t mode)
/*[[[body:libc_chmod]]]*/
{
	errno_t result;
	result = sys_fchmodat(AT_FDCWD,
	                      filename,
	                      mode,
	                      0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chmod]]]*/


/*[[[head:libc_lchmod,hash:CRC-32=0xda2c7e30]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_lchmod)(char const *filename,
                                  mode_t mode)
/*[[[body:libc_lchmod]]]*/
{
	errno_t result;
	result = sys_fchmodat(AT_FDCWD,
	                      filename,
	                      mode,
	                      AT_SYMLINK_NOFOLLOW);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lchmod]]]*/

/*[[[head:libc_umask,hash:CRC-32=0xe4c0afb5]]]*/
INTERN ATTR_SECTION(".text.crt.fs.basic_property") mode_t
NOTHROW_NCX(LIBCCALL libc_umask)(mode_t mode)
/*[[[body:libc_umask]]]*/
{
	return sys_umask(mode);
}
/*[[[end:libc_umask]]]*/

/*[[[head:libc_getumask,hash:CRC-32=0x7bc9cea4]]]*/
/* Return the current umask.
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

/*[[[head:libc_fmkdirat,hash:CRC-32=0xec4900f0]]]*/
/* @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fmkdirat)(fd_t dirfd,
                                    char const *pathname,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:libc_fmkdirat]]]*/
{
	errno_t result;
	result = sys_fmkdirat(dirfd,
	                      pathname,
	                      mode,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fmkdirat]]]*/

/*[[[head:libc_fmknodat,hash:CRC-32=0x8b2fc75b]]]*/
/* @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fmknodat)(fd_t dirfd,
                                    char const *nodename,
                                    mode_t mode,
                                    dev_t dev,
                                    atflag_t flags)
/*[[[body:libc_fmknodat]]]*/
{
	errno_t result;
	result = sys_fmknodat(dirfd,
	                      nodename,
	                      mode,
	                      dev,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fmknodat]]]*/

/*[[[head:libc_mkfifo,hash:CRC-32=0x8e4cb40e]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mkfifo)(char const *fifoname,
                                  mode_t mode)
/*[[[body:libc_mkfifo]]]*/
{
	return mknod(fifoname, S_IFIFO | mode, 0);
}
/*[[[end:libc_mkfifo]]]*/

/*[[[head:libc_fchmodat,hash:CRC-32=0x26083bb4]]]*/
/* @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fchmodat)(fd_t dirfd,
                                    char const *filename,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:libc_fchmodat]]]*/
{
	errno_t result;
	result = sys_fchmodat(dirfd,
	                      filename,
	                      mode,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchmodat]]]*/

/*[[[head:libc_mkdirat,hash:CRC-32=0x7210f157]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_mkdirat)(fd_t dirfd,
                                   char const *pathname,
                                   mode_t mode)
/*[[[body:libc_mkdirat]]]*/
{
	errno_t result;
	result = sys_mkdirat(dirfd,
	                     pathname,
	                     mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mkdirat]]]*/

/*[[[head:libc_mkfifoat,hash:CRC-32=0x3b7c88b7]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_mkfifoat)(fd_t dirfd,
                                    char const *fifoname,
                                    mode_t mode)
/*[[[body:libc_mkfifoat]]]*/
{
	return mknodat(dirfd, fifoname, S_IFIFO | mode, 0);
}
/*[[[end:libc_mkfifoat]]]*/

/*[[[head:libc_fchmod,hash:CRC-32=0x3cb37aa0]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") int
NOTHROW_RPC(LIBCCALL libc_fchmod)(fd_t fd,
                                  mode_t mode)
/*[[[body:libc_fchmod]]]*/
{
	errno_t result;
	result = sys_fchmod(fd,
	                    mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchmod]]]*/

/*[[[head:libc_mknod,hash:CRC-32=0x18d62bde]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mknod)(char const *nodename,
                                 mode_t mode,
                                 dev_t dev)
/*[[[body:libc_mknod]]]*/
{
	errno_t result;
	result = sys_mknodat(AT_FDCWD,
	                     nodename,
	                     mode,
	                     dev);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mknod]]]*/

/*[[[head:libc_mknodat,hash:CRC-32=0xa16ab194]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_mknodat)(fd_t dirfd,
                                   char const *nodename,
                                   mode_t mode,
                                   dev_t dev)
/*[[[body:libc_mknodat]]]*/
{
	errno_t result;
	result = sys_mknodat(dirfd,
	                     nodename,
	                     mode,
	                     dev);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mknodat]]]*/



/*[[[head:libc_utimensat,hash:CRC-32=0x29bcfaa9]]]*/
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_utimensat)(fd_t dirfd,
                                     char const *filename,
                                     struct timespec const times[2 /*or:3*/],
                                     atflag_t flags)
/*[[[body:libc_utimensat]]]*/
{
	errno_t result;
	result = sys_utimensat(dirfd,
	                       filename,
	                       times,
	                       flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_utimensat]]]*/

/*[[[head:libc_utimensat64,hash:CRC-32=0xcd992e3]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_utimensat64, libc_utimensat);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_utimensat64)(fd_t dirfd,
                                       char const *filename,
                                       struct timespec64 const times[2 /*or:3*/],
                                       atflag_t flags)
/*[[[body:libc_utimensat64]]]*/
{
	errno_t result;
#ifdef SYS_utimensat64
	result = sys_utimensat64(dirfd,
	                         filename,
	                         times,
	                         flags);
#elif defined(SYS_utimensat_time64)
	result = sys_utimensat_time64(dirfd,
	                              filename,
	                              times,
	                              flags);
#else /* ... */
#error "No way to implement `utimensat64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_utimensat64]]]*/

/*[[[head:libc_futimens,hash:CRC-32=0x21c4a0c1]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify_time") int
NOTHROW_RPC(LIBCCALL libc_futimens)(fd_t fd,
                                    struct timespec const times[2 /*or:3*/])
/*[[[body:libc_futimens]]]*/
{
	errno_t result;
	result = sys_utimensat(fd,
	                       NULL,
	                       times,
	                       0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futimens]]]*/

/*[[[head:libc_futimens64,hash:CRC-32=0x727ddb86]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futimens64, libc_futimens);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") int
NOTHROW_RPC(LIBCCALL libc_futimens64)(fd_t fd,
                                      struct timespec64 const times[2 /*or:3*/])
/*[[[body:libc_futimens64]]]*/
{
	errno_t result;
#ifdef SYS_utimensat64
	result = sys_utimensat64(fd,
	                         NULL,
	                         times,
	                         0);
#elif defined(SYS_utimensat_time64)
	result = sys_utimensat_time64(fd,
	                              NULL,
	                              times,
	                              0);
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
	used_filename = libc_uchar_c32tombs(filename);
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
	used_filename = libc_uchar_c16tombs(filename);
	if likely(used_filename) {
		result = libc_dos_stat64(used_filename, buf);
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
	used_filename = libc_uchar_c32tombs(filename);
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
	used_filename = libc_uchar_c16tombs(filename);
	if likely(used_filename) {
		result = libc_dos_stat32i64(used_filename, buf);
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
	used_filename = libc_uchar_c32tombs(filename);
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
	used_filename = libc_uchar_c16tombs(filename);
	if likely(used_filename) {
		result = libc_dos_stat32(used_filename, buf);
		free(used_filename);
	}
	return result;
}
/*[[[end:libd__wstat32]]]*/





/*[[[start:exports,hash:CRC-32=0x4107dd50]]]*/
DEFINE_PUBLIC_ALIAS(mkdir, libc_mkdir);
DEFINE_PUBLIC_ALIAS(_chmod, libc_chmod);
DEFINE_PUBLIC_ALIAS(chmod, libc_chmod);
DEFINE_PUBLIC_ALIAS(lchmod, libc_lchmod);
DEFINE_PUBLIC_ALIAS(_umask, libc_umask);
DEFINE_PUBLIC_ALIAS(umask, libc_umask);
DEFINE_PUBLIC_ALIAS(getumask, libc_getumask);
DEFINE_PUBLIC_ALIAS(fmkdirat, libc_fmkdirat);
DEFINE_PUBLIC_ALIAS(fmknodat, libc_fmknodat);
DEFINE_PUBLIC_ALIAS(mkfifo, libc_mkfifo);
DEFINE_PUBLIC_ALIAS(fchmodat, libc_fchmodat);
DEFINE_PUBLIC_ALIAS(mkdirat, libc_mkdirat);
DEFINE_PUBLIC_ALIAS(mkfifoat, libc_mkfifoat);
DEFINE_PUBLIC_ALIAS(fchmod, libc_fchmod);
DEFINE_PUBLIC_ALIAS(mknod, libc_mknod);
DEFINE_PUBLIC_ALIAS(mknodat, libc_mknodat);
DEFINE_PUBLIC_ALIAS(utimensat, libc_utimensat);
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
