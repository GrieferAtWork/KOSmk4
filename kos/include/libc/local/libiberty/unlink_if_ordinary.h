/* HASH CRC-32:0x279e7362 */
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
#ifndef __local_unlink_if_ordinary_defined
#define __local_unlink_if_ordinary_defined
#include <__crt.h>
#include <features.h>
#include <bits/os/stat.h>
#include <asm/os/fcntl.h>
#if ((defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lstat_defined
#define __local___localdep_lstat_defined
#if defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),klstat,(__filename,__buf))
#elif defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),klstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#elif defined(__CRT_HAVE___lstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),__lstat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),lstat,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat,(char const *__restrict __filename, struct stat *__restrict __buf),lstat64,(__filename,__buf))
#elif (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/lstat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lstat __LIBC_LOCAL_NAME(lstat)
#else /* ... */
#undef __local___localdep_lstat_defined
#endif /* !... */
#endif /* !__local___localdep_lstat_defined */
#ifndef __local___localdep_unlink_defined
#define __local___localdep_unlink_defined
#ifdef __CRT_HAVE_unlink
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),unlink,(__file))
#elif defined(__CRT_HAVE__unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__libc_unlink,(__file))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/unlink.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unlink __LIBC_LOCAL_NAME(unlink)
#else /* ... */
#undef __local___localdep_unlink_defined
#endif /* !... */
#endif /* !__local___localdep_unlink_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unlink_if_ordinary) __ATTR_IN(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unlink_if_ordinary))(char const *__filename) {
	struct stat __st;
	if ((__NAMESPACE_LOCAL_SYM __localdep_lstat)(__filename, &__st) != 0)
		return 1;
	if (!__S_ISREG(__st.st_mode) && !__S_ISLNK(__st.st_mode))
		return 1;
	/* Sorry, no way  to prevent  the race  where
	 * the file is replaced before we get here... */
	return (__NAMESPACE_LOCAL_SYM __localdep_unlink)(__filename);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unlink_if_ordinary_defined
#define __local___localdep_unlink_if_ordinary_defined
#define __localdep_unlink_if_ordinary __LIBC_LOCAL_NAME(unlink_if_ordinary)
#endif /* !__local___localdep_unlink_if_ordinary_defined */
#else /* ((__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_lstat || __CRT_HAVE_lstat64 || __CRT_HAVE___lstat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32) && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) */
#undef __local_unlink_if_ordinary_defined
#endif /* ((!__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64)) && (!__CRT_HAVE_klstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_klstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_lstat && !__CRT_HAVE_lstat64 && !__CRT_HAVE___lstat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32) || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) */
#endif /* !__local_unlink_if_ordinary_defined */
