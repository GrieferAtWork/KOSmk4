/* HASH CRC-32:0xeea56476 */
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
#ifndef __local_fdmatch_defined
#define __local_fdmatch_defined
#include <__crt.h>
#include <features.h>
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__fstat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__fstat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_fstat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_fstat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fstat_defined
#define __local___localdep_fstat_defined
#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32i64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),fstat,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),fstat64,(__fd,__buf))
#else /* ... */
#undef __local___localdep_fstat_defined
#endif /* !... */
#endif /* !__local___localdep_fstat_defined */
__LOCAL_LIBC(fdmatch) __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fdmatch))(__fd_t __fd1, __fd_t __fd2) {
	struct stat __st1, __st2;
	if ((__NAMESPACE_LOCAL_SYM __localdep_fstat)(__fd1, &__st1) == 0 && (__NAMESPACE_LOCAL_SYM __localdep_fstat)(__fd2, &__st2) == 0) {
		return __st1.st_dev == __st2.st_dev &&
		       __st1.st_ino == __st2.st_ino;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fdmatch_defined
#define __local___localdep_fdmatch_defined
#define __localdep_fdmatch __LIBC_LOCAL_NAME(fdmatch)
#endif /* !__local___localdep_fdmatch_defined */
#else /* (__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__fstat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__fstat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_fstat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_fstat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */
#undef __local_fdmatch_defined
#endif /* (!__CRT_HAVE_kfstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__fstat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__fstat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__fstat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__fstat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_fstat || (__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) && (!__CRT_HAVE_fstat64 || (!__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) */
#endif /* !__local_fdmatch_defined */
