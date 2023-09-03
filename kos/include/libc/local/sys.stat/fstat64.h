/* HASH CRC-32:0x37d6f1fa */
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
#ifndef __local_fstat64_defined
#define __local_fstat64_defined
#include <__crt.h>
#if defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dos_fstat32i32_defined
#define __local___localdep_dos_fstat32i32_defined
#ifdef __CRT_HAVE__fstat
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_fstat32i32,(__fd_t __fd, struct __dos_stat32 *__restrict __buf),_fstat,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32)
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_fstat32i32,(__fd_t __fd, struct __dos_stat32 *__restrict __buf),_fstat32,(__fd,__buf))
#else /* ... */
#undef __local___localdep_dos_fstat32i32_defined
#endif /* !... */
#endif /* !__local___localdep_dos_fstat32i32_defined */
#ifndef __local___localdep_dos_fstat32i64_defined
#define __local___localdep_dos_fstat32i64_defined
#ifdef __CRT_HAVE__fstati64
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_fstat32i64,(__fd_t __fd, struct __dos_stat32i64 *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64)
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_fstat32i64,(__fd_t __fd, struct __dos_stat32i64 *__restrict __buf),_fstat32i64,(__fd,__buf))
#else /* ... */
#undef __local___localdep_dos_fstat32i64_defined
#endif /* !... */
#endif /* !__local___localdep_dos_fstat32i64_defined */
#ifndef __local___localdep_dos_fstat64i32_defined
#define __local___localdep_dos_fstat64i32_defined
#ifdef __CRT_HAVE__fstat64
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_fstat64i32,(__fd_t __fd, struct __dos_stat64i32 *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32)
__NAMESPACE_LOCAL_END
#include <bits/os/dos/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_dos_fstat64i32,(__fd_t __fd, struct __dos_stat64i32 *__restrict __buf),_fstat64i32,(__fd,__buf))
#else /* ... */
#undef __local___localdep_dos_fstat64i32_defined
#endif /* !... */
#endif /* !__local___localdep_dos_fstat64i32_defined */
#if !defined(__local___localdep_glibc_fstat_defined) && defined(__CRT_HAVE_fstat)
#define __local___localdep_glibc_fstat_defined
__NAMESPACE_LOCAL_END
#include <bits/os/linux/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_glibc_fstat,(__fd_t __fd, struct __glc_stat *__restrict __buf),fstat,(__fd,__buf))
#endif /* !__local___localdep_glibc_fstat_defined && __CRT_HAVE_fstat */
#if !defined(__local___localdep_glibc_fstat64_defined) && defined(__CRT_HAVE_fstat64)
#define __local___localdep_glibc_fstat64_defined
__NAMESPACE_LOCAL_END
#include <bits/os/linux/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_glibc_fstat64,(__fd_t __fd, struct __glc_stat64 *__restrict __buf),fstat64,(__fd,__buf))
#endif /* !__local___localdep_glibc_fstat64_defined && __CRT_HAVE_fstat64 */
#if !defined(__local___localdep_glibc_fstat64_time64_defined) && defined(__CRT_HAVE___fstat64_time64)
#define __local___localdep_glibc_fstat64_time64_defined
__NAMESPACE_LOCAL_END
#include <bits/os/linux/stat.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_glibc_fstat64_time64,(__fd_t __fd, struct __glc_stat64_time64 *__restrict __buf),__fstat64_time64,(__fd,__buf))
#endif /* !__local___localdep_glibc_fstat64_time64_defined && __CRT_HAVE___fstat64_time64 */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fstat64) __ATTR_FDARG(1) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fstat64))(__fd_t __fd, struct __stat64 *__restrict __buf) {
#if defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64)
#ifdef __CRT_HAVE___fstat64_time64
	struct __glc_stat64_time64 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_glibc_fstat64_time64)(__fd, &__st);
#elif defined(__CRT_HAVE_fstat64)
	struct __glc_stat64 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_glibc_fstat64)(__fd, &__st);
#else /* ... */
	struct __glc_stat __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_glibc_fstat)(__fd, &__st);
#endif /* !... */
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
		__buf->st_size      = (__off64_t)__st.st_size;
#ifdef _STATBUF_ST_BLKSIZE
		__buf->st_blksize   = (__blksize_t)__st.st_blksize;
#endif /* _STATBUF_ST_BLKSIZE */
#ifdef _STATBUF_ST_BLOCKS
		__buf->st_blocks    = (__blkcnt64_t)__st.st_blocks;
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
#else /* __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 */
	/* $has_function(dos_fstat64i32) || $has_function(dos_fstat32i64) || $has_function(dos_fstat32i32) */
#if defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)
	struct __dos_stat64i32 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_dos_fstat64i32)(__fd, &__st);
#elif defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64)
	struct __dos_stat32i64 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_dos_fstat32i64)(__fd, &__st);
#else /* ... */
	struct __dos_stat32 __st;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_dos_fstat32i32)(__fd, &__st);
#endif /* !... */
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
		__buf->st_size      = (__off64_t)__st.st_size;
#ifdef _STATBUF_ST_BLKSIZE
		__buf->st_blksize   = (__blksize_t)0;
#endif /* _STATBUF_ST_BLKSIZE */
#ifdef _STATBUF_ST_BLOCKS
		__buf->st_blocks    = (__blkcnt64_t)0;
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
#endif /* !__CRT_HAVE_fstat && !__CRT_HAVE_fstat64 && !__CRT_HAVE___fstat64_time64 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fstat64_defined
#define __local___localdep_fstat64_defined
#define __localdep_fstat64 __LIBC_LOCAL_NAME(fstat64)
#endif /* !__local___localdep_fstat64_defined */
#else /* __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32 */
#undef __local_fstat64_defined
#endif /* !__CRT_HAVE_fstat && !__CRT_HAVE_fstat64 && !__CRT_HAVE___fstat64_time64 && !__CRT_HAVE__fstat && !__CRT_HAVE__fstat32 && !__CRT_HAVE__fstati64 && !__CRT_HAVE__fstat32i64 && !__CRT_HAVE__fstat64 && !__CRT_HAVE__fstat64i32 */
#endif /* !__local_fstat64_defined */
