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
#ifndef GUARD_LIBC_USER_SYS_STAT_C
#define GUARD_LIBC_USER_SYS_STAT_C 1

#include "../api.h"
#include "sys.stat.h"

#include <fcntl.h>
#include <kos/syscalls.h>
#include <unistd.h>

DECL_BEGIN


DEFINE_PUBLIC_WEAK_ALIAS(kstat,libc_kos_stat);
DEFINE_PUBLIC_WEAK_ALIAS(kstat64,libc_kos_stat);
DEFINE_PUBLIC_WEAK_ALIAS(klstat,libc_kos_lstat);
DEFINE_PUBLIC_WEAK_ALIAS(klstat64,libc_kos_lstat);
DEFINE_PUBLIC_WEAK_ALIAS(kfstat,libc_kos_fstat);
DEFINE_PUBLIC_WEAK_ALIAS(kfstat64,libc_kos_fstat);
DEFINE_PUBLIC_WEAK_ALIAS(kfstatat,libc_kos_fstatat);
DEFINE_PUBLIC_WEAK_ALIAS(kfstatat64,libc_kos_fstatat);

DEFINE_INTERN_ALIAS(libc_kstat,libc_kos_stat);
DEFINE_INTERN_ALIAS(libc_kstat64,libc_kos_stat);
DEFINE_INTERN_ALIAS(libc_klstat,libc_kos_lstat);
DEFINE_INTERN_ALIAS(libc_klstat64,libc_kos_lstat);
DEFINE_INTERN_ALIAS(libc_kfstat,libc_kos_fstat);
DEFINE_INTERN_ALIAS(libc_kfstat64,libc_kos_fstat);
DEFINE_INTERN_ALIAS(libc_kfstatat,libc_kos_fstatat);
DEFINE_INTERN_ALIAS(libc_kfstatat64,libc_kos_fstatat);

/* KOS Native stat() */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat.kos_fstat") int
NOTHROW_RPC(LIBCCALL libc_kos_fstat)(fd_t fd,
                                     struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstat(fd,
	                   (struct stat *)buf);
	return libc_seterrno_syserr(error);
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat.kos_stat") int
NOTHROW_RPC(LIBCCALL libc_kos_stat)(char const *__restrict filename,
                                    struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstatat(AT_FDCWD,
	                     filename,
	                     (struct stat *)buf,
	                     0);
	return libc_seterrno_syserr(error);
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat.kos_lstat") int
NOTHROW_RPC(LIBCCALL libc_kos_lstat)(char const *__restrict filename,
                                     struct __kos_stat *__restrict buf) {
	errno_t error;
	error = sys_kfstatat(AT_FDCWD,
	                     filename,
	                     (struct stat *)buf,
	                     AT_SYMLINK_NOFOLLOW);
	return libc_seterrno_syserr(error);
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat.kos_fstatat") int
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
DEFINE_PUBLIC_WEAK_ALIAS(DOS$stat, libc_cyg_stat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$stat64, libc_cyg_stat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$lstat, libc_cyg_lstat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$lstat64, libc_cyg_lstat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fstat, libc_cyg_fstat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fstat64, libc_cyg_fstat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fstatat, libc_cyg_fstatat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fstatat64, libc_cyg_fstatat);
LOCAL NONNULL((1, 2)) void LIBCCALL
convstat_kos2cyg(struct __cyg_stat *__restrict dst,
                 struct __kos_stat const *__restrict src) {
	dst->st_dev      = (__UINT32_TYPE__)src->st_dev;
	dst->st_ino      = (__UINT64_TYPE__)src->st_ino64;
	dst->st_mode     = (__UINT32_TYPE__)src->st_mode;
	dst->st_nlink    = (__UINT16_TYPE__)src->st_nlink;
	dst->st_uid      = (__UINT32_TYPE__)src->st_uid;
	dst->st_gid      = (__UINT32_TYPE__)src->st_gid;
	dst->st_rdev     = (__UINT32_TYPE__)src->st_rdev;
	dst->st_size     = (__UINT64_TYPE__)src->st_size64;
	dst->st_atim     = src->st_atim64;
	dst->st_mtim     = src->st_mtim64;
	dst->st_ctim     = src->st_ctim64;
	dst->st_blksize  = (__UINT32_TYPE__)src->st_blksize;
	dst->st_blocks   = (__UINT64_TYPE__)src->st_blocks64;
	dst->st_birthtim = src->st_ctim64;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.cyg_fstat") int
NOTHROW_RPC(LIBCCALL libc_cyg_fstat)(fd_t fd,
                                     struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.cyg_stat") int
NOTHROW_RPC(LIBCCALL libc_cyg_stat)(char const *__restrict filename,
                                    struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.cyg_lstat") int
NOTHROW_RPC(LIBCCALL libc_cyg_lstat)(char const *__restrict filename,
                                     struct __cyg_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2cyg(buf, &st);
	return result;
}
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.cyg_fstatat") int
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
DEFINE_PUBLIC_WEAK_ALIAS(stat, libc_glc_stat);
DEFINE_PUBLIC_WEAK_ALIAS(stat64, libc_glc_stat64);
DEFINE_PUBLIC_WEAK_ALIAS(lstat, libc_glc_lstat);
DEFINE_PUBLIC_WEAK_ALIAS(lstat64, libc_glc_lstat64);
DEFINE_PUBLIC_WEAK_ALIAS(fstat, libc_glc_fstat);
DEFINE_PUBLIC_WEAK_ALIAS(fstat64, libc_glc_fstat64);
DEFINE_PUBLIC_WEAK_ALIAS(fstatat, libc_glc_fstatat);
DEFINE_PUBLIC_WEAK_ALIAS(fstatat64, libc_glc_fstatat64);
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
	dst->st_dev     = (__UINT64_TYPE__)src->st_dev;
	dst->st_ino     = (__UINT32_TYPE__)src->st_ino32;
	dst->st_mode    = (__UINT32_TYPE__)src->st_mode;
	dst->st_nlink   = (__UINT32_TYPE__)src->st_nlink;
	dst->st_uid     = (__UINT32_TYPE__)src->st_uid;
	dst->st_gid     = (__UINT32_TYPE__)src->st_gid;
	dst->st_rdev    = (__UINT64_TYPE__)src->st_rdev;
	dst->st_size    = (__UINT32_TYPE__)src->st_size32;
	dst->st_blksize = (__UINT32_TYPE__)src->st_blksize;
	dst->st_blocks  = (__UINT32_TYPE__)src->st_blocks32;
	dst->st_atim    = src->st_atim32;
	dst->st_mtim    = src->st_mtim32;
	dst->st_ctim    = src->st_ctim32;
}
LOCAL NONNULL((1, 2)) void LIBCCALL
convstat_kos2glc64(struct __glc_stat64 *__restrict dst,
                   struct __kos_stat const *__restrict src) {
	dst->st_dev     = (__UINT64_TYPE__)src->st_dev;
	dst->st_ino32   = (__UINT32_TYPE__)src->st_ino32;
	dst->st_mode    = (__UINT32_TYPE__)src->st_mode;
	dst->st_nlink   = (__UINT32_TYPE__)src->st_nlink;
	dst->st_uid     = (__UINT32_TYPE__)src->st_uid;
	dst->st_gid     = (__UINT32_TYPE__)src->st_gid;
	dst->st_rdev    = (__UINT64_TYPE__)src->st_rdev;
	dst->st_size64  = (__UINT64_TYPE__)src->st_size64;
	dst->st_blksize = (__UINT32_TYPE__)src->st_blksize;
	dst->st_blocks  = (__UINT32_TYPE__)src->st_blocks32;
	dst->st_atim    = src->st_atim32;
	dst->st_mtim    = src->st_mtim32;
	dst->st_ctim    = src->st_ctim32;
	dst->st_ino64   = (__UINT64_TYPE__)src->st_ino64;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstat") int
NOTHROW_RPC(LIBCCALL libc_glc_fstat)(fd_t fd,
                                     struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstat64") int
NOTHROW_RPC(LIBCCALL libc_glc_fstat64)(fd_t fd,
                                       struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_stat") int
NOTHROW_RPC(LIBCCALL libc_glc_stat)(char const *__restrict filename,
                                    struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_stat64") int
NOTHROW_RPC(LIBCCALL libc_glc_stat64)(char const *__restrict filename,
                                      struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_lstat") int
NOTHROW_RPC(LIBCCALL libc_glc_lstat)(char const *__restrict filename,
                                     struct __glc_stat *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2glc(buf, &st);
	return result;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_lstat64") int
NOTHROW_RPC(LIBCCALL libc_glc_lstat64)(char const *__restrict filename,
                                       struct __glc_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_lstat(filename, &st);
	if likely(!result)
		convstat_kos2glc64(buf, &st);
	return result;
}

INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstatat") int
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

INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.stat_glc.glc_fstatat64") int
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
DEFINE_PUBLIC_WEAK_ALIAS(_fstat, libc_dos_fstat32);
DEFINE_PUBLIC_WEAK_ALIAS(_fstat32, libc_dos_fstat32);
DEFINE_PUBLIC_WEAK_ALIAS(_fstati64, libc_dos_fstat32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_fstat32i64, libc_dos_fstat32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_fstat64, libc_dos_fstat64);
DEFINE_PUBLIC_WEAK_ALIAS(_fstat64i32, libc_dos_fstat64);
DEFINE_PUBLIC_WEAK_ALIAS(_stat, libc_dos_stat32);
DEFINE_PUBLIC_WEAK_ALIAS(_stat32, libc_dos_stat32);
DEFINE_PUBLIC_WEAK_ALIAS(_stati64, libc_dos_stat32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_stat32i64, libc_dos_stat32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_stat64, libc_dos_stat64);
DEFINE_PUBLIC_WEAK_ALIAS(_stat64i32, libc_dos_stat64);
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
	dst->st_dev     = (__dos_dev_t)src->st_dev;
	dst->st_ino     = (__dos_ino_t)src->st_ino32;
	dst->st_mode    = (__uint16_t)src->st_mode;
	dst->st_nlink   = (__int16_t)src->st_nlink;
	dst->st_uid     = (__int16_t)src->st_uid;
	dst->st_gid     = (__int16_t)src->st_gid;
	dst->st_rdev    = (__dos_dev_t)src->st_rdev;
	dst->st_size32  = (__UINT32_TYPE__)src->st_size32;
	dst->st_atime32 = (__time32_t)src->st_atim32.tv_sec;
	dst->st_mtime32 = (__time32_t)src->st_mtim32.tv_sec;
	dst->st_ctime32 = (__time32_t)src->st_ctim32.tv_sec;
}
LOCAL NONNULL((1, 2)) void LIBCCALL
convstat_kos2dos32i64(struct __dos_stat32i64 *__restrict dst,
                      struct __kos_stat const *__restrict src) {
	dst->st_dev     = (__dos_dev_t)src->st_dev;
	dst->st_ino     = (__dos_ino_t)src->st_ino32;
	dst->st_mode    = (__uint16_t)src->st_mode;
	dst->st_nlink   = (__int16_t)src->st_nlink;
	dst->st_uid     = (__int16_t)src->st_uid;
	dst->st_gid     = (__int16_t)src->st_gid;
	dst->st_rdev    = (__dos_dev_t)src->st_rdev;
	dst->st_size64  = (__UINT64_TYPE__)src->st_size64;
	dst->st_atime32 = (__time32_t)src->st_atim32.tv_sec;
	dst->st_mtime32 = (__time32_t)src->st_mtim32.tv_sec;
	dst->st_ctime32 = (__time32_t)src->st_ctim32.tv_sec;
}
LOCAL NONNULL((1, 2)) void LIBCCALL
convstat_kos2dos64(struct __dos_stat64 *__restrict dst,
                   struct __kos_stat const *__restrict src) {
	dst->st_dev     = (__dos_dev_t)src->st_dev;
	dst->st_ino     = (__dos_ino_t)src->st_ino32;
	dst->st_mode    = (__uint16_t)src->st_mode;
	dst->st_nlink   = (__int16_t)src->st_nlink;
	dst->st_uid     = (__int16_t)src->st_uid;
	dst->st_gid     = (__int16_t)src->st_gid;
	dst->st_rdev    = (__dos_dev_t)src->st_rdev;
	dst->st_size64  = (__UINT64_TYPE__)src->st_size64;
	dst->st_atime64 = (__time64_t)src->st_atim64.tv_sec;
	dst->st_mtime64 = (__time64_t)src->st_mtim64.tv_sec;
	dst->st_ctime64 = (__time64_t)src->st_ctim64.tv_sec;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.dos_fstat32") int
NOTHROW_RPC(LIBCCALL libc_dos_fstat32)(fd_t fd,
                                       struct __dos_stat32 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos32(buf, &st);
	return result;
}
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.dos_fstat32i64") int
NOTHROW_RPC(LIBCCALL libc_dos_fstat32i64)(fd_t fd,
                                          struct __dos_stat32i64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos32i64(buf, &st);
	return result;
}
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.dos_fstat64") int
NOTHROW_RPC(LIBCCALL libc_dos_fstat64)(fd_t fd,
                                       struct __dos_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_fstat(fd, &st);
	if likely(!result)
		convstat_kos2dos64(buf, &st);
	return result;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.dos_stat32") int
NOTHROW_RPC(LIBCCALL libc_dos_stat32)(char const *__restrict filename,
                                      struct __dos_stat32 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32(buf, &st);
	return result;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.dos_stat32i64") int
NOTHROW_RPC(LIBCCALL libc_dos_stat32i64)(char const *__restrict filename,
                                         struct __dos_stat32i64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos32i64(buf, &st);
	return result;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.stat.dos_stat64") int
NOTHROW_RPC(LIBCCALL libc_dos_stat64)(char const *__restrict filename,
                                      struct __dos_stat64 *__restrict buf) {
	struct __kos_stat st;
	int result = libc_kos_stat(filename, &st);
	if likely(!result)
		convstat_kos2dos64(buf, &st);
	return result;
}





/*[[[start:implementation]]]*/

/*[[[head:mkdir,hash:0x5f276ca6]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.mkdir") int
NOTHROW_RPC(LIBCCALL libc_mkdir)(char const *pathname,
                                 mode_t mode)
/*[[[body:mkdir]]]*/
{
	errno_t result;
	result = sys_mkdirat(AT_FDCWD,
	                     pathname,
	                     mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:mkdir]]]*/

/*[[[head:chmod,hash:0x13b58f24]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.chmod") int
NOTHROW_RPC(LIBCCALL libc_chmod)(char const *filename,
                                 mode_t mode)
/*[[[body:chmod]]]*/
{
	errno_t result;
	result = sys_fchmodat(AT_FDCWD,
	                      filename,
	                      mode,
	                      0);
	return libc_seterrno_syserr(result);
}
/*[[[end:chmod]]]*/
DEFINE_INTERN_ALIAS(libc__chmod, libc_chmod);
DEFINE_PUBLIC_WEAK_ALIAS(_chmod, libc__chmod);


/*[[[head:lchmod,hash:0x650bac64]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.lchmod") int
NOTHROW_RPC(LIBCCALL libc_lchmod)(char const *filename,
                                  mode_t mode)
/*[[[body:lchmod]]]*/
{
	errno_t result;
	result = sys_fchmodat(AT_FDCWD,
	                      filename,
	                      mode,
	                      AT_SYMLINK_NOFOLLOW);
	return libc_seterrno_syserr(result);
}
/*[[[end:lchmod]]]*/

/*[[[head:umask,hash:0xede0c36]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.basic_property.umask") mode_t
NOTHROW_NCX(LIBCCALL libc_umask)(mode_t mode)
/*[[[body:umask]]]*/
{
	return sys_umask(mode);
}
/*[[[end:umask]]]*/

/*[[[head:getumask,hash:0x5f12beb2]]]*/
/* Return the current umask.
 * WARNING: This function isn't thread-safe */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.basic_property.getumask") mode_t
NOTHROW_NCX(LIBCCALL libc_getumask)(void)
/*[[[body:getumask]]]*/
{
	mode_t result;
	result = sys_umask(0);
	sys_umask(result);
	return result;
}
/*[[[end:getumask]]]*/

/*[[[head:fmkdirat,hash:0xec454724]]]*/
/* @param flags: Set of `0|AT_DOSPATH' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.fmkdirat") int
NOTHROW_RPC(LIBCCALL libc_fmkdirat)(fd_t dirfd,
                                    char const *pathname,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:fmkdirat]]]*/
{
	errno_t result;
	result = sys_fmkdirat(AT_FDCWD,
	                      pathname,
	                      mode,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:fmkdirat]]]*/

/*[[[head:fmknodat,hash:0xb6bb0c1]]]*/
/* @param flags: Set of `0|AT_DOSPATH' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.fmknodat") int
NOTHROW_RPC(LIBCCALL libc_fmknodat)(fd_t dirfd,
                                    char const *nodename,
                                    mode_t mode,
                                    dev_t dev,
                                    atflag_t flags)
/*[[[body:fmknodat]]]*/
{
	errno_t result;
	result = sys_fmknodat(AT_FDCWD,
	                      nodename,
	                      mode,
	                      dev,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:fmknodat]]]*/

/*[[[head:mkfifo,hash:0x12b7a012]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.mkfifo") int
NOTHROW_RPC(LIBCCALL libc_mkfifo)(char const *fifoname,
                                  mode_t mode)
/*[[[body:mkfifo]]]*/
{
	return mknod(fifoname, S_IFIFO | mode, 0);
}
/*[[[end:mkfifo]]]*/

/*[[[head:fchmodat,hash:0x382c84be]]]*/
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.fchmodat") int
NOTHROW_RPC(LIBCCALL libc_fchmodat)(fd_t dirfd,
                                    char const *filename,
                                    mode_t mode,
                                    atflag_t flags)
/*[[[body:fchmodat]]]*/
{
	errno_t result;
	result = sys_fchmodat(dirfd,
	                      filename,
	                      mode,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:fchmodat]]]*/

/*[[[head:mkdirat,hash:0x97c84560]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.mkdirat") int
NOTHROW_RPC(LIBCCALL libc_mkdirat)(fd_t dirfd,
                                   char const *pathname,
                                   mode_t mode)
/*[[[body:mkdirat]]]*/
{
	errno_t result;
	result = sys_mkdirat(dirfd,
	                     pathname,
	                     mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:mkdirat]]]*/

/*[[[head:mkfifoat,hash:0x206155a6]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.mkfifoat") int
NOTHROW_RPC(LIBCCALL libc_mkfifoat)(fd_t dirfd,
                                    char const *fifoname,
                                    mode_t mode)
/*[[[body:mkfifoat]]]*/
{
	return mknodat(dirfd, fifoname, S_IFIFO | mode, 0);
}
/*[[[end:mkfifoat]]]*/

/*[[[head:fchmod,hash:0x339a7cd]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.fchmod") int
NOTHROW_RPC(LIBCCALL libc_fchmod)(fd_t fd,
                                  mode_t mode)
/*[[[body:fchmod]]]*/
{
	errno_t result;
	result = sys_fchmod(fd,
	                    mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:fchmod]]]*/

/*[[[head:mknod,hash:0xa94d6080]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.mknod") int
NOTHROW_RPC(LIBCCALL libc_mknod)(char const *nodename,
                                 mode_t mode,
                                 dev_t dev)
/*[[[body:mknod]]]*/
{
	errno_t result;
	result = sys_mknodat(AT_FDCWD,
	                     nodename,
	                     mode,
	                     dev);
	return libc_seterrno_syserr(result);
}
/*[[[end:mknod]]]*/

/*[[[head:mknodat,hash:0xf7e1415a]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify.mknodat") int
NOTHROW_RPC(LIBCCALL libc_mknodat)(fd_t dirfd,
                                   char const *nodename,
                                   mode_t mode,
                                   dev_t dev)
/*[[[body:mknodat]]]*/
{
	errno_t result;
	result = sys_mknodat(dirfd,
	                     nodename,
	                     mode,
	                     dev);
	return libc_seterrno_syserr(result);
}
/*[[[end:mknodat]]]*/



/*[[[head:utimensat,hash:0x1c09df59]]]*/
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.utimensat") int
NOTHROW_RPC(LIBCCALL libc_utimensat)(fd_t dirfd,
                                     char const *filename,
                                     struct timespec const times[2/*or:3*/],
                                     atflag_t flags)
/*[[[body:utimensat]]]*/
{
	errno_t result;
	result = sys_utimensat(dirfd,
	                       filename,
	                       times,
	                       flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:utimensat]]]*/

/*[[[head:utimensat64,hash:0x73bde57e]]]*/
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_utimensat64, libc_utimensat);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.utimensat64") int
NOTHROW_RPC(LIBCCALL libc_utimensat64)(fd_t dirfd,
                                       char const *filename,
                                       struct timespec64 const times[2/*or:3*/],
                                       atflag_t flags)
/*[[[body:utimensat64]]]*/
{
	errno_t result;
	result = sys_utimensat64(dirfd,
	                         filename,
	                         times,
	                         flags);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:utimensat64]]]*/

/*[[[head:futimens,hash:0x371ffb20]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.futimens") int
NOTHROW_RPC(LIBCCALL libc_futimens)(fd_t fd,
                                    struct timespec const times[2/*or:3*/])
/*[[[body:futimens]]]*/
{
	errno_t result;
	result = sys_utimensat(fd,
	                       NULL,
	                       times,
	                       0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futimens]]]*/

/*[[[head:futimens64,hash:0x387958a2]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futimens64, libc_futimens);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.futimens64") int
NOTHROW_RPC(LIBCCALL libc_futimens64)(fd_t fd,
                                      struct timespec64 const times[2/*or:3*/])
/*[[[body:futimens64]]]*/
{
	errno_t result;
	result = sys_utimensat64(fd,
	                         NULL,
	                         times,
	                         0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futimens64]]]*/

/*[[[head:_wstat64i32,hash:0xda998397]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat64i32") int
NOTHROW_NCX(LIBCCALL libc__wstat64i32)(char32_t const *filename,
                                       struct __dos_stat64i32 *buf)
/*[[[body:_wstat64i32]]]*/
{
	CRT_UNIMPLEMENTED("_wstat64i32"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_wstat64i32]]]*/

/*[[[head:DOS$_wstat64,hash:0xcd556392]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat64") int
NOTHROW_NCX(LIBDCALL libd__wstat64)(char16_t const *filename,
                                    struct __dos_stat64 *buf)
/*[[[body:DOS$_wstat64]]]*/
{
	CRT_UNIMPLEMENTED("_wstat64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$_wstat64]]]*/

/*[[[head:_wstat32i64,hash:0x886e57f]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat32i64") int
NOTHROW_NCX(LIBCCALL libc__wstat32i64)(char32_t const *filename,
                                       struct __dos_stat32i64 *buf)
/*[[[body:_wstat32i64]]]*/
{
	CRT_UNIMPLEMENTED("_wstat32i64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_wstat32i64]]]*/

/*[[[head:DOS$_wstat64i32,hash:0x159420cc]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat64i32") int
NOTHROW_NCX(LIBDCALL libd__wstat64i32)(char16_t const *filename,
                                       struct __dos_stat64i32 *buf)
/*[[[body:DOS$_wstat64i32]]]*/
{
	CRT_UNIMPLEMENTED("_wstat64i32"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$_wstat64i32]]]*/

/*[[[head:DOS$_wstat32i64,hash:0xc1168b35]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat32i64") int
NOTHROW_NCX(LIBDCALL libd__wstat32i64)(char16_t const *filename,
                                       struct __dos_stat32i64 *buf)
/*[[[body:DOS$_wstat32i64]]]*/
{
	CRT_UNIMPLEMENTED("_wstat32i64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$_wstat32i64]]]*/

/*[[[head:_wstat32,hash:0xf4ed6134]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat32") int
NOTHROW_NCX(LIBCCALL libc__wstat32)(char32_t const *filename,
                                    struct __dos_stat32 *buf)
/*[[[body:_wstat32]]]*/
{
	CRT_UNIMPLEMENTED("_wstat32"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_wstat32]]]*/

/*[[[head:DOS$_wstat32,hash:0xe610fba1]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat32") int
NOTHROW_NCX(LIBDCALL libd__wstat32)(char16_t const *filename,
                                    struct __dos_stat32 *buf)
/*[[[body:DOS$_wstat32]]]*/
{
	CRT_UNIMPLEMENTED("_wstat32"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$_wstat32]]]*/

/*[[[head:_wstat64,hash:0x92a75de0]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.stat._wstat64") int
NOTHROW_NCX(LIBCCALL libc__wstat64)(char32_t const *filename,
                                    struct __dos_stat64 *buf)
/*[[[body:_wstat64]]]*/
{
	CRT_UNIMPLEMENTED("_wstat64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_wstat64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x10749090]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(mkdir, libc_mkdir);
DEFINE_PUBLIC_WEAK_ALIAS(chmod, libc_chmod);
DEFINE_PUBLIC_WEAK_ALIAS(_chmod, libc_chmod);
DEFINE_PUBLIC_WEAK_ALIAS(lchmod, libc_lchmod);
DEFINE_PUBLIC_WEAK_ALIAS(umask, libc_umask);
DEFINE_PUBLIC_WEAK_ALIAS(_umask, libc_umask);
DEFINE_PUBLIC_WEAK_ALIAS(getumask, libc_getumask);
DEFINE_PUBLIC_WEAK_ALIAS(fmkdirat, libc_fmkdirat);
DEFINE_PUBLIC_WEAK_ALIAS(fmknodat, libc_fmknodat);
DEFINE_PUBLIC_WEAK_ALIAS(mkfifo, libc_mkfifo);
DEFINE_PUBLIC_WEAK_ALIAS(fchmodat, libc_fchmodat);
DEFINE_PUBLIC_WEAK_ALIAS(mkdirat, libc_mkdirat);
DEFINE_PUBLIC_WEAK_ALIAS(mkfifoat, libc_mkfifoat);
DEFINE_PUBLIC_WEAK_ALIAS(fchmod, libc_fchmod);
DEFINE_PUBLIC_WEAK_ALIAS(mknod, libc_mknod);
DEFINE_PUBLIC_WEAK_ALIAS(mknodat, libc_mknodat);
DEFINE_PUBLIC_WEAK_ALIAS(utimensat, libc_utimensat);
DEFINE_PUBLIC_WEAK_ALIAS(utimensat64, libc_utimensat64);
DEFINE_PUBLIC_WEAK_ALIAS(futimens, libc_futimens);
DEFINE_PUBLIC_WEAK_ALIAS(futimens64, libc_futimens64);
DEFINE_PUBLIC_WEAK_ALIAS(_wstat32, libc__wstat32);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wstat32, libd__wstat32);
DEFINE_PUBLIC_WEAK_ALIAS(_wstat64, libc__wstat64);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wstat64, libd__wstat64);
DEFINE_PUBLIC_WEAK_ALIAS(_wstat32i64, libc__wstat32i64);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wstat32i64, libd__wstat32i64);
DEFINE_PUBLIC_WEAK_ALIAS(_wstat64i32, libc__wstat64i32);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wstat64i32, libd__wstat64i32);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STAT_C */
