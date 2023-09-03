/* HASH CRC-32:0xfec244f5 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lstat_defined
#define __local_lstat_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <features.h>
#include <bits/os/stat.h>
#if (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dos_stat32i32_defined
#define __local___localdep_dos_stat32i32_defined
#ifdef __CRT_HAVE__stat
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_stat32i32,(char const *__restrict __filename, struct __dos_stat32 *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32)
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_stat32i32,(char const *__restrict __filename, struct __dos_stat32 *__restrict __buf),_stat32,(__filename,__buf))
#else /* ... */
#undef __local___localdep_dos_stat32i32_defined
#endif /* !... */
#endif /* !__local___localdep_dos_stat32i32_defined */
#ifndef __local___localdep_dos_stat32i64_defined
#define __local___localdep_dos_stat32i64_defined
#ifdef __CRT_HAVE__stati64
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_stat32i64,(char const *__restrict __filename, struct __dos_stat32i64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64)
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_stat32i64,(char const *__restrict __filename, struct __dos_stat32i64 *__restrict __buf),_stat32i64,(__filename,__buf))
#else /* ... */
#undef __local___localdep_dos_stat32i64_defined
#endif /* !... */
#endif /* !__local___localdep_dos_stat32i64_defined */
#ifndef __local___localdep_dos_stat64i32_defined
#define __local___localdep_dos_stat64i32_defined
#ifdef __CRT_HAVE__stat64
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_stat64i32,(char const *__restrict __filename, struct __dos_stat64i32 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32)
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_stat64i32,(char const *__restrict __filename, struct __dos_stat64i32 *__restrict __buf),_stat64i32,(__filename,__buf))
#else /* ... */
#undef __local___localdep_dos_stat64i32_defined
#endif /* !... */
#endif /* !__local___localdep_dos_stat64i32_defined */
#ifndef __local___localdep_fstatat_defined
#define __local___localdep_fstatat_defined
#if defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE___fstatat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),__fstatat64_time64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),fstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),fstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/fstatat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fstatat __LIBC_LOCAL_NAME(fstatat)
#else /* ... */
#undef __local___localdep_fstatat_defined
#endif /* !... */
#endif /* !__local___localdep_fstatat_defined */
#if !defined(__local___localdep_glibc_lstat_defined) && defined(__CRT_HAVE_lstat)
#define __local___localdep_glibc_lstat_defined
__NAMESPACE_LOCAL_END
#include <bits/os/linux/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_glibc_lstat,(char const *__restrict __filename, struct __glc_stat *__restrict __buf),lstat,(__filename,__buf))
#endif /* !__local___localdep_glibc_lstat_defined && __CRT_HAVE_lstat */
#if !defined(__local___localdep_glibc_lstat64_defined) && defined(__CRT_HAVE_lstat64)
#define __local___localdep_glibc_lstat64_defined
__NAMESPACE_LOCAL_END
#include <bits/os/linux/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_glibc_lstat64,(char const *__restrict __filename, struct __glc_stat64 *__restrict __buf),lstat64,(__filename,__buf))
#endif /* !__local___localdep_glibc_lstat64_defined && __CRT_HAVE_lstat64 */
#if !defined(__local___localdep_glibc_lstat64_time64_defined) && defined(__CRT_HAVE___lstat64_time64)
#define __local___localdep_glibc_lstat64_time64_defined
__NAMESPACE_LOCAL_END
#include <bits/os/linux/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_glibc_lstat64_time64,(char const *__restrict __filename, struct __glc_stat64_time64 *__restrict __buf),__lstat64_time64,(__filename,__buf))
#endif /* !__local___localdep_glibc_lstat64_time64_defined && __CRT_HAVE___lstat64_time64 */
#ifndef __local___localdep_lstat64_defined
#define __local___localdep_lstat64_defined
#if defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),klstat,(__filename,__buf))
#elif defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),klstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE___lstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),__lstat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),lstat,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64))
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),lstat64,(__filename,__buf))
#elif (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/lstat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lstat64 __LIBC_LOCAL_NAME(lstat64)
#else /* ... */
#undef __local___localdep_lstat64_defined
#endif /* !... */
#endif /* !__local___localdep_lstat64_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(lstat) __ATTR_IN(1) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lstat))(char const *__restrict __filename, struct stat *__restrict __buf) {
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))
	return (__NAMESPACE_LOCAL_SYM __localdep_fstatat)(__AT_FDCWD, __filename, __buf, __AT_SYMLINK_NOFOLLOW);
#elif (defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64)
#if (defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
	struct stat64 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_lstat64)(__filename, &__st);






#else /* (__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_lstat || __CRT_HAVE_lstat64 || __CRT_HAVE___lstat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */
	struct __glc_stat __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_glibc_lstat)(__filename, &__st);
#endif /* (!__CRT_HAVE_klstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_klstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_lstat && !__CRT_HAVE_lstat64 && !__CRT_HAVE___lstat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32 */
	if (__result == 0) {
		__buf->st_dev       = (__dev_t)__st.st_dev;
		__buf->st_ino       = (__ino_t)__st.st_ino;
		__buf->st_mode      = (__mode_t)__st.st_mode;
		__buf->st_nlink     = (__nlink_t)__st.st_nlink;
		__buf->st_uid       = (__uid_t)__st.st_uid;
		__buf->st_gid       = (__gid_t)__st.st_gid;
#ifdef _STATBUF_ST_RDEV
		__buf->st_rdev      = (__dev_t)__st.st_rdev;
#endif /* _STATBUF_ST_RDEV */
		__buf->st_size      = (__off_t)__st.st_size;
#ifdef _STATBUF_ST_BLKSIZE
		__buf->st_blksize   = (__blksize_t)__st.st_blksize;
#endif /* _STATBUF_ST_BLKSIZE */
#ifdef _STATBUF_ST_BLOCKS
		__buf->st_blocks    = (__blkcnt_t)__st.st_blocks;
#endif /* _STATBUF_ST_BLOCKS */
		__buf->st_atime     = (__time_t)__st.st_atime;
		__buf->st_mtime     = (__time_t)__st.st_mtime;
		__buf->st_ctime     = (__time_t)__st.st_ctime;
#ifdef _STATBUF_ST_NSEC
		__buf->st_atimespec = (__syscall_ulong_t)__st.st_atimespec;
		__buf->st_mtimespec = (__syscall_ulong_t)__st.st_mtimespec;
		__buf->st_ctimespec = (__syscall_ulong_t)__st.st_ctimespec;
#endif /* _STATBUF_ST_NSEC */
	}
	return __result;
#else /* ... */
	/* $has_function(dos_stat64i32) || $has_function(dos_stat32i64) || $has_function(dos_stat32i32) */







	struct __dos_stat32 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_dos_stat32i32)(__filename, &__st);

	if (__result == 0) {
		__buf->st_dev       = (__dev_t)__st.st_dev;
		__buf->st_ino       = (__ino_t)__st.st_ino;
		__buf->st_mode      = (__mode_t)__st.st_mode;
		__buf->st_nlink     = (__nlink_t)__st.st_nlink;
		__buf->st_uid       = (__uid_t)__st.st_uid;
		__buf->st_gid       = (__gid_t)__st.st_gid;
#ifdef _STATBUF_ST_RDEV
		__buf->st_rdev      = (__dev_t)__st.st_rdev;
#endif /* _STATBUF_ST_RDEV */
		__buf->st_size      = (__off_t)__st.st_size;
#ifdef _STATBUF_ST_BLKSIZE
		__buf->st_blksize   = (__blksize_t)0;
#endif /* _STATBUF_ST_BLKSIZE */
#ifdef _STATBUF_ST_BLOCKS
		__buf->st_blocks    = (__blkcnt_t)0;
#endif /* _STATBUF_ST_BLOCKS */
		__buf->st_atime     = (__time_t)__st.st_atime;
		__buf->st_mtime     = (__time_t)__st.st_mtime;
		__buf->st_ctime     = (__time_t)__st.st_ctime;
#ifdef _STATBUF_ST_NSEC
		__buf->st_atimespec = (__syscall_ulong_t)0;
		__buf->st_mtimespec = (__syscall_ulong_t)0;
		__buf->st_ctimespec = (__syscall_ulong_t)0;
#endif /* _STATBUF_ST_NSEC */
	}
	return __result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lstat_defined
#define __local___localdep_lstat_defined
#define __localdep_lstat __LIBC_LOCAL_NAME(lstat)
#endif /* !__local___localdep_lstat_defined */
#else /* (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_lstat || __CRT_HAVE_lstat64 || __CRT_HAVE___lstat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */
#undef __local_lstat_defined
#endif /* (!__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64)) && (!__CRT_HAVE_klstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_klstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_lstat && !__CRT_HAVE_lstat64 && !__CRT_HAVE___lstat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32 */
#endif /* !__local_lstat_defined */
