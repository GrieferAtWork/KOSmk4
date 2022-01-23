/* HASH CRC-32:0x2a435e38 */
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
#ifndef __local_c32get_current_dir_name_defined
#define __local_c32get_current_dir_name_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wgetcwd) || (defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wgetcwd)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__c32getenv_defined
#define __local___localdep__c32getenv_defined
#if defined(__CRT_HAVE__wgetenv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep__c32getenv,(__CHAR32_TYPE__ const *__varname),_wgetenv,(__varname))
#elif defined(__CRT_HAVE_KOS$_wgetenv)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep__c32getenv,(__CHAR32_TYPE__ const *__varname),_wgetenv,(__varname))
#else /* ... */
#undef __local___localdep__c32getenv_defined
#endif /* !... */
#endif /* !__local___localdep__c32getenv_defined */
#ifndef __local___localdep_c32dup_defined
#define __local___localdep_c32dup_defined
#if defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32dup,(__CHAR32_TYPE__ const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_KOS$wcsdup)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32dup,(__CHAR32_TYPE__ const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32dup,(__CHAR32_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_KOS$_wcsdup)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32dup,(__CHAR32_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32dup __NAMESPACE_LOCAL_TYPEHAX(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict),__CHAR32_TYPE__ *(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict),wcsdup)
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32dup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32dup __LIBC_LOCAL_NAME(c32dup)
#else /* ... */
#undef __local___localdep_c32dup_defined
#endif /* !... */
#endif /* !__local___localdep_c32dup_defined */
#ifndef __local___localdep_c32getcwd_defined
#define __local___localdep_c32getcwd_defined
#if defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__CHAR32_TYPE__ *,__NOTHROW_RPC,__localdep_c32getcwd,(__CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_KOS$wgetcwd)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(,__CHAR32_TYPE__ *,__NOTHROW_RPC,__localdep_c32getcwd,(__CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__CHAR32_TYPE__ *,__NOTHROW_RPC,__localdep_c32getcwd,(__CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_KOS$_wgetcwd)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(,__CHAR32_TYPE__ *,__NOTHROW_RPC,__localdep_c32getcwd,(__CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_c32getcwd_defined
#endif /* !... */
#endif /* !__local___localdep_c32getcwd_defined */
#ifndef __local___localdep_stat_defined
#define __local___localdep_stat_defined
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
#else /* ... */
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
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
#elif defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#else /* ... */
#undef __local___localdep_stat_defined
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_stat_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32get_current_dir_name) __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ *
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32get_current_dir_name))(void) {
#if ((defined(__CRT_HAVE__wgetenv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wgetenv)) && ((defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))) && ((defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wcsdup) || (defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wcsdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
	/* Specs require us to return a duplicate of $PWD iff it's correct
	 *   ***Author's comment: DUMB!***
	 */
	__CHAR32_TYPE__ *__pwd = (__NAMESPACE_LOCAL_SYM __localdep__c32getenv)("PWD");
	if (__pwd && *__pwd) {
		struct stat __st_pwd, __st_cwd;
		if ((__NAMESPACE_LOCAL_SYM __localdep_stat)(__pwd, &__st_pwd) == 0 &&
		    (__NAMESPACE_LOCAL_SYM __localdep_stat)(".", &__st_cwd) == 0) {
			if (__st_pwd.st_dev == __st_cwd.st_dev &&
			    __st_pwd.st_ino == __st_cwd.st_ino)
				return (__NAMESPACE_LOCAL_SYM __localdep_c32dup)(__pwd);
		}
	}
#endif /* ((__CRT_HAVE__wgetenv && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wgetenv) && ((__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64))) && ((__CRT_HAVE_wcsdup && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wcsdup || (__CRT_HAVE__wcsdup && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wcsdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
	return (__NAMESPACE_LOCAL_SYM __localdep_c32getcwd)(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32get_current_dir_name_defined
#define __local___localdep_c32get_current_dir_name_defined
#define __localdep_c32get_current_dir_name __LIBC_LOCAL_NAME(c32get_current_dir_name)
#endif /* !__local___localdep_c32get_current_dir_name_defined */
#else /* (__CRT_HAVE_wgetcwd && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wgetcwd || (__CRT_HAVE__wgetcwd && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wgetcwd */
#undef __local_c32get_current_dir_name_defined
#endif /* (!__CRT_HAVE_wgetcwd || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wgetcwd && (!__CRT_HAVE__wgetcwd || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wgetcwd */
#endif /* !__local_c32get_current_dir_name_defined */
