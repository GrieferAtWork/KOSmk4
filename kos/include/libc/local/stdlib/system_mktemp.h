/* HASH CRC-32:0x3c5aaf66 */
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
#ifndef __local_system_mktemp_defined
#define __local_system_mktemp_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bcmpc_defined
#define __local___localdep_bcmpc_defined
#ifdef __CRT_HAVE_bcmpc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmpc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bcmpc __LIBC_LOCAL_NAME(memcmpc)
#endif /* !... */
#endif /* !__local___localdep_bcmpc_defined */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_getpid_defined
#define __local___localdep_getpid_defined
#ifdef __CRT_HAVE_getpid
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__getpid,())
#elif defined(__CRT_HAVE___libc_getpid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__libc_getpid,())
#else /* ... */
#undef __local___localdep_getpid_defined
#endif /* !... */
#endif /* !__local___localdep_getpid_defined */
#ifndef __local___localdep_gettid_defined
#define __local___localdep_gettid_defined
#ifdef __CRT_HAVE_gettid
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),gettid,())
#elif defined(__CRT_HAVE___threadid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),__threadid,())
#elif defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ,())
#else /* ... */
#undef __local___localdep_gettid_defined
#endif /* !... */
#endif /* !__local___localdep_gettid_defined */
#ifndef __local___localdep_gettimeofday_defined
#define __local___localdep_gettimeofday_defined
#if defined(__CRT_HAVE_gettimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),__gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_gettimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),__libc_gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday,(struct timeval *__restrict __tv, void * __tz),__gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE___gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/gettimeofday.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gettimeofday __LIBC_LOCAL_NAME(gettimeofday)
#else /* ... */
#undef __local___localdep_gettimeofday_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday_defined */
#ifndef __local___localdep_gettimeofday64_defined
#define __local___localdep_gettimeofday64_defined
#if defined(__CRT_HAVE_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),__gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),__gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),__libc_gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/gettimeofday64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gettimeofday64 __LIBC_LOCAL_NAME(gettimeofday64)
#else /* ... */
#undef __local___localdep_gettimeofday64_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday64_defined */
#ifndef __local___localdep_mkdir_defined
#define __local___localdep_mkdir_defined
#ifdef __CRT_HAVE_mkdir
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),mkdir,(__pathname,__mode))
#elif defined(__CRT_HAVE___mkdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),__mkdir,(__pathname,__mode))
#elif defined(__CRT_HAVE___libc_mkdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),__libc_mkdir,(__pathname,__mode))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mkdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkdir __LIBC_LOCAL_NAME(mkdir)
#else /* (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat)) */
#undef __local___localdep_mkdir_defined
#endif /* (!__CRT_DOS_PRIMARY || !__CRT_HAVE__mkdir) && (!__AT_FDCWD || (!__CRT_HAVE_mkdirat && !__CRT_HAVE_fmkdirat)) */
#endif /* !... */
#endif /* !__local___localdep_mkdir_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
__NAMESPACE_LOCAL_END
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local___localdep_open_defined
#endif /* !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !... */
#endif /* !__local___localdep_open_defined */
#ifndef __local___localdep_rand_defined
#define __local___localdep_rand_defined
#ifdef __CRT_HAVE_rand
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),rand,())
#else /* __CRT_HAVE_rand */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_random) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),random,())
#else /* __CRT_HAVE_random && __SIZEOF_INT__ == __SIZEOF_LONG__ */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/rand.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rand __LIBC_LOCAL_NAME(rand)
#endif /* !__CRT_HAVE_random || __SIZEOF_INT__ != __SIZEOF_LONG__ */
#endif /* !__CRT_HAVE_rand */
#endif /* !__local___localdep_rand_defined */
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
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
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
#elif defined(__CRT_HAVE___stat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),__stat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
#if (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/stat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_stat __LIBC_LOCAL_NAME(stat)
#else /* (__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */
#undef __local___localdep_stat_defined
#endif /* (!__AT_FDCWD || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64)) && !__CRT_HAVE_stat && !__CRT_HAVE_stat64 && !__CRT_HAVE___stat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32 */
#endif /* !... */
#endif /* !__local___localdep_stat_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <asm/os/oflags.h>
#include <asm/crt/stdio.h>
#include <bits/os/timeval.h>
#include <bits/os/stat.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(system_mktemp) __ATTR_WUNUSED __ATTR_INOUT(2) __fd_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(system_mktemp))(unsigned int __what, char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags) {
	/* Selection of random letters which  may appear as replacements for  XXXXXX
	 * For this  purpose,  only  use  lower-case letters,  as  well  as  digits.
	 * We  could also  use upper-case letters,  but that may  not work correctly
	 * depending on the calling process running in DOS-mode, or flags containing
	 * O_DOSPATH... */
	static char const __letters[] = "abcdefghijklmnopqrstuvwxyz0123456789";
#define __NUM_LETTERS 36
	char *__xloc = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__template_) - (__suffixlen + 6);
	__UINT32_TYPE__ __seed, __overflow;
	__SIZE_TYPE__ __i, __attempt;
	__fd_t __result;

	/* Verify the validity of the input template. */
	if __unlikely(__xloc < __template_ || (__NAMESPACE_LOCAL_SYM __localdep_bcmpc)(__xloc, "XXXXXX", 6, sizeof(char)) != 0) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}

	/* Calculate an  initial,  random  seed.
	 * For this purpose, try to make use of:
	 *   - gettimeofday()
	 *   - gettid() or getpid()
	 *   - rand() */
	__attempt = 0;
__again:
	{
#if (defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE___gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)) && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
		struct __timeval64 __tv;
		if ((__NAMESPACE_LOCAL_SYM __localdep_gettimeofday64)(&__tv, __NULLPTR) == 0) {
			__seed = (__UINT32_TYPE__)(__tv.tv_sec) ^
			       (__UINT32_TYPE__)(__tv.tv_sec >> 32) ^
			       (__UINT32_TYPE__)(__tv.tv_usec << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE___gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
		struct timeval __tv;
		if ((__NAMESPACE_LOCAL_SYM __localdep_gettimeofday)(&__tv, __NULLPTR) == 0) {
			__seed = (__UINT32_TYPE__)(__tv.tv_sec) ^
#if __SIZEOF_TIME_T__ > 4
			       (__UINT32_TYPE__)(__tv.tv_sec >> 32) ^
#endif /* __SIZEOF_TIME_T__ > 4 */
			       (__UINT32_TYPE__)(__tv.tv_usec << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
#endif /* ... */
		{
			__UINT32_TYPE__ __sum;
#ifdef __RAND_MAX
#define __LIBC_RAND_MAX __RAND_MAX
#else /* __RAND_MAX */
#define __LIBC_RAND_MAX 0x7fff
#endif /* !__RAND_MAX */
			__seed = __sum = 0;
			/* Generate at least 32 bits of random data. */
			do {
				__seed *= __LIBC_RAND_MAX;
				__seed += (__UINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_rand)();
			} while (!__hybrid_overflow_uadd(__sum, __LIBC_RAND_MAX, &__sum));
#undef __LIBC_RAND_MAX
		}
	}
#if defined(__CRT_HAVE_gettid) || defined(__CRT_HAVE___threadid) || defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)
	__seed ^= (__NAMESPACE_LOCAL_SYM __localdep_gettid)();
#elif defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)
	__seed ^= (__NAMESPACE_LOCAL_SYM __localdep_getpid)();
#endif /* ... */

	/* Using the seed, generate some initial random data.
	 * We've generated 32 bits of entropy above, and with
	 * a total of 6 characters to generate from a pool of
	 * 36 letters each, this 5.333(rep) bits per digit. */
	__overflow = __seed >> 30;
	for (__i = 0; __i < 6; ++__i) {
		unsigned int __digit;
		__digit = __seed & 0x1f;                      /* digit in 0-31 */
		__digit += __overflow & ((1 << (__i & 3)) - 1); /* Add a random addend between 0-7 */

		/* Right now, digit in 0-38. But because we're using 2 addend, `0' is less
		 * likely than the other digits. As such, subtract a bit if we're not at 0
		 * already. */
		if (__digit)
			--__digit;
		if (__digit)
			--__digit;

		/* Now, digit in 0-36, but 36 itself would still be invalid. */
		if (__digit > 35)
			__digit = 35;

		/* All right! we've got the digit. */
		__xloc[__i] = __letters[__digit];
		__seed >>= 5;
	}

	/* Try to create/test the file/directory. */
	(void)__flags;
	switch (__what) {

#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
	case 0: {
#ifdef __O_RDWR
#ifdef __O_ACCMODE
		__flags &= ~__O_ACCMODE;
#endif /* __O_ACCMODE */
		__flags |= __O_RDWR;
#endif /* __O_RDWR */
#ifdef __O_CREAT
		__flags |= __O_CREAT;
#endif /* __O_CREAT */
#ifdef __O_EXCL
		__flags |= __O_EXCL;
#endif /* __O_EXCL */
		__result = (__NAMESPACE_LOCAL_SYM __localdep_open)(__template_, __flags, 0600);
	}	break;
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */

#if defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
	case 1:
		__result = (__NAMESPACE_LOCAL_SYM __localdep_mkdir)(__template_, 0700);
		break;
#endif /* __CRT_HAVE_mkdir || __CRT_HAVE___mkdir || __CRT_HAVE___libc_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat)) */

#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
	case 2: {
#if (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
		struct stat __st;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_stat)(__template_, &__st);
#else /* (__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */
		__result = (__NAMESPACE_LOCAL_SYM __localdep_open)(__template_,
#ifdef __O_RDONLY
		              __O_RDONLY
#elif defined(__O_RDWR)
		              __O_RDWR
#elif defined(__O_WRONLY)
		              __O_WRONLY
#else /* ... */
		              0
#endif /* !... */
		              ,
		              0600);
#endif /* (!__AT_FDCWD || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64)) && (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_stat && !__CRT_HAVE_stat64 && !__CRT_HAVE___stat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32 */
		if (__result < 0) {
			/* File doesn't already exist. */
			__result = 0;
		} else {
			/* File does already exist. */
#if (!defined(__AT_FDCWD) || ((!defined(__CRT_HAVE_kfstatat) || !defined(__CRT_KOS_PRIMARY)) && (!defined(__CRT_HAVE_kfstatat64) || !defined(__CRT_KOS_PRIMARY)) && !defined(__CRT_HAVE_fstatat) && !defined(__CRT_HAVE_fstatat64) && !defined(__CRT_HAVE___fstatat64_time64))) && (!defined(__CRT_HAVE_kstat) || !defined(__CRT_KOS_PRIMARY)) && (!defined(__CRT_HAVE_kstat64) || !defined(__CRT_KOS_PRIMARY)) && !defined(__CRT_HAVE_stat) && !defined(__CRT_HAVE_stat64) && !defined(__CRT_HAVE___stat64_time64) && !defined(__CRT_HAVE__stat) && !defined(__CRT_HAVE__stat32) && !defined(__CRT_HAVE__stati64) && !defined(__CRT_HAVE__stat32i64) && !defined(__CRT_HAVE__stat64) && !defined(__CRT_HAVE__stat64i32) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close))
			(__NAMESPACE_LOCAL_SYM __localdep_close)(__result);
#endif /* (!__AT_FDCWD || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64)) && (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_stat && !__CRT_HAVE_stat64 && !__CRT_HAVE___stat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32 && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) */
#ifdef __EEXIST
			__result = __libc_seterrno(__EEXIST);
#else /* __EEXIST */
			__result = __libc_seterrno(1);
#endif /* !__EEXIST */
#define __NEED_do_try_again
			goto __do_try_again;
		}
	}	break;
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */

	default: __builtin_unreachable();
	}
	if (__result == -1) {
		/* Only re-attempt if the error was that the file already existed. */
#if defined(__libc_geterrno) && defined(__EEXIST)
		if (__libc_geterrno() == __EEXIST)
#endif /* __libc_geterrno && __EEXIST */
		{
#ifdef __NEED_do_try_again
#undef __NEED_do_try_again
__do_try_again:
#endif /* __NEED_do_try_again */
			/* Limit the max # of attempts */
#ifdef __TMP_MAX
			if (__attempt < __TMP_MAX)
#else /* __TMP_MAX */
			if (__attempt < 238328)
#endif /* !__TMP_MAX */
			{
				++__attempt;
				goto __again;
			}
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_system_mktemp_defined
#define __local___localdep_system_mktemp_defined
#define __localdep_system_mktemp __LIBC_LOCAL_NAME(system_mktemp)
#endif /* !__local___localdep_system_mktemp_defined */
#endif /* !__local_system_mktemp_defined */
