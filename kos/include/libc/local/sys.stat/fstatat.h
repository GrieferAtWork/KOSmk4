/* HASH CRC-32:0x1828f27c */
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
#ifndef __local_fstatat_defined
#define __local_fstatat_defined
#include <__crt.h>
#include <features.h>
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fstatat64_defined
#define __local___localdep_fstatat64_defined
#if defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),kfstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),kfstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE___fstatat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),__fstatat64_time64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) && defined(__STAT32_MATCHES_STAT64)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),fstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64))
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),fstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/fstatat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fstatat64 __LIBC_LOCAL_NAME(fstatat64)
#else /* ... */
#undef __local___localdep_fstatat64_defined
#endif /* !... */
#endif /* !__local___localdep_fstatat64_defined */
__LOCAL_LIBC(fstatat) __ATTR_IN(2) __ATTR_OUT(3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fstatat))(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags) {
	struct stat64 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_fstatat64)(__dirfd, __filename, &__st, __flags);
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
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fstatat_defined
#define __local___localdep_fstatat_defined
#define __localdep_fstatat __LIBC_LOCAL_NAME(fstatat)
#endif /* !__local___localdep_fstatat_defined */
#else /* (__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64 */
#undef __local_fstatat_defined
#endif /* (!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64 */
#endif /* !__local_fstatat_defined */
