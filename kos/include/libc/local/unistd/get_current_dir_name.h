/* HASH CRC-32:0x2ec2888a */
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
#ifndef __local_get_current_dir_name_defined
#define __local_get_current_dir_name_defined
#include <__crt.h>
#if defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getcwd_defined
#define __local___localdep_getcwd_defined
#ifdef __CRT_HAVE_getcwd
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),getcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),_getcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_getcwd_defined
#endif /* !... */
#endif /* !__local___localdep_getcwd_defined */
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#else /* __CRT_HAVE_getenv */
__NAMESPACE_LOCAL_END
#include <libc/template/environ.h>
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
#define __local___localdep_stat_defined
#if defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat64,(__filename,__buf))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#else /* ... */
#undef __local___localdep_stat_defined
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_stat_defined */
#ifndef __local___localdep_strdup_defined
#define __local___localdep_strdup_defined
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,(__string))
#elif defined(__CRT_HAVE__strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),_strdup,(__string))
#elif defined(__CRT_HAVE__mbsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),_mbsdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),__strdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/string/strdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strdup __LIBC_LOCAL_NAME(strdup)
#else /* ... */
#undef __local___localdep_strdup_defined
#endif /* !... */
#endif /* !__local___localdep_strdup_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(get_current_dir_name) __ATTR_MALLOC __ATTR_WUNUSED char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(get_current_dir_name))(void) {
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && ((defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
	/* Specs require us to return a duplicate of $PWD iff it's correct
	 *   ***Author's comment: DUMB!***
	 */
	char *__pwd = (__NAMESPACE_LOCAL_SYM __localdep_getenv)("PWD");
	if (__pwd && *__pwd) {
		struct stat __st_pwd, __st_cwd;
		if ((__NAMESPACE_LOCAL_SYM __localdep_stat)(__pwd, &__st_pwd) == 0 &&
		    (__NAMESPACE_LOCAL_SYM __localdep_stat)(".", &__st_cwd) == 0) {
			if (__st_pwd.st_dev == __st_cwd.st_dev &&
			    __st_pwd.st_ino == __st_cwd.st_ino)
				return (__NAMESPACE_LOCAL_SYM __localdep_strdup)(__pwd);
		}
	}
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && ((__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64))) && (__CRT_HAVE_strdup || __CRT_HAVE__strdup || __CRT_HAVE__mbsdup || __CRT_HAVE___strdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
	return (__NAMESPACE_LOCAL_SYM __localdep_getcwd)(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_get_current_dir_name_defined
#define __local___localdep_get_current_dir_name_defined
#define __localdep_get_current_dir_name __LIBC_LOCAL_NAME(get_current_dir_name)
#endif /* !__local___localdep_get_current_dir_name_defined */
#else /* __CRT_HAVE_getcwd || __CRT_HAVE__getcwd */
#undef __local_get_current_dir_name_defined
#endif /* !__CRT_HAVE_getcwd && !__CRT_HAVE__getcwd */
#endif /* !__local_get_current_dir_name_defined */
