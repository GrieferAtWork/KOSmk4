/* HASH CRC-32:0x3f208a5a */
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
#ifndef __local_wget_current_dir_name_defined
#define __local_wget_current_dir_name_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined 1
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#else /* __CRT_HAVE_getenv */
__NAMESPACE_LOCAL_END
#include <libc/local/environ.h>
__NAMESPACE_LOCAL_BEGIN
#ifdef __LOCAL_environ
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#else /* __LOCAL_environ */
#undef __local___localdep_getenv_defined
#endif /* !__LOCAL_environ */
#endif /* !__CRT_HAVE_getenv */
#endif /* !__local___localdep_getenv_defined */
#ifndef __local___localdep_stat_defined
#define __local___localdep_stat_defined 1
#if defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat,(__filename,__buf))
#else /* ... */
#undef __local___localdep_stat_defined
#endif /* !... */
#endif /* !__local___localdep_stat_defined */
#ifndef __local___localdep_wcsdup_defined
#define __local___localdep_wcsdup_defined 1
#ifdef __CRT_HAVE_wcsdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsdup,(__WCHAR_TYPE__ const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsdup,(__WCHAR_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsdup __LIBC_LOCAL_NAME(wcsdup)
#else /* ... */
#undef __local___localdep_wcsdup_defined
#endif /* !... */
#endif /* !__local___localdep_wcsdup_defined */
#ifndef __local___localdep_wgetcwd_defined
#define __local___localdep_wgetcwd_defined 1
#ifdef __CRT_HAVE_wgetcwd
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__WCHAR_TYPE__ *,__NOTHROW_RPC,__localdep_wgetcwd,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__WCHAR_TYPE__ *,__NOTHROW_RPC,__localdep_wgetcwd,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_wgetcwd_defined
#endif /* !... */
#endif /* !__local___localdep_wgetcwd_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wget_current_dir_name) __ATTR_MALLOC __ATTR_WUNUSED __WCHAR_TYPE__ *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wget_current_dir_name))(void) {
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && ((defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && !defined(__USE_FILE_OFFSET64))) && (defined(__CRT_HAVE_wcsdup) || defined(__CRT_HAVE__wcsdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign))
	/* Specs require us to return a duplicate of $PWD iff it's correct
	 *   ***Author's comment: DUMB!***
	 */
	__WCHAR_TYPE__ *__pwd = __localdep_getenv("PWD");
	if (__pwd && *__pwd) {
		struct stat __st_pwd, __st_cwd;
		if (__localdep_stat(__pwd, &__st_pwd) == 0 &&
		    __localdep_stat(".", &__st_cwd) == 0) {
			if (__st_pwd.st_dev == __st_cwd.st_dev &&
			    __st_pwd.st_ino == __st_cwd.st_ino)
				return __localdep_wcsdup(__pwd);
		}
	}
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && ((__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat64 && __USE_FILE_OFFSET64) || (__CRT_HAVE_stat && !__USE_FILE_OFFSET64)) && (__CRT_HAVE_wcsdup || __CRT_HAVE__wcsdup || __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) */
	return __localdep_wgetcwd(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wget_current_dir_name_defined
#define __local___localdep_wget_current_dir_name_defined 1
#define __localdep_wget_current_dir_name __LIBC_LOCAL_NAME(wget_current_dir_name)
#endif /* !__local___localdep_wget_current_dir_name_defined */
#else /* __CRT_HAVE_wgetcwd || __CRT_HAVE__wgetcwd */
#undef __local_wget_current_dir_name_defined
#endif /* !__CRT_HAVE_wgetcwd && !__CRT_HAVE__wgetcwd */
#endif /* !__local_wget_current_dir_name_defined */
