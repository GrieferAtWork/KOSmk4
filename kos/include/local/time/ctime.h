/* HASH CRC-32:0x2b2e439d */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ctime_defined
#define __local_ctime_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ctime32 from time */
#ifndef __local___localdep_ctime32_defined
#define __local___localdep_ctime32_defined 1
#ifdef __CRT_HAVE_ctime
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime32,(__time32_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime32)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime32,(__time32_t const *__timer),_ctime32,(__timer))
#else /* ... */
#undef __local___localdep_ctime32_defined
#endif /* !... */
#endif /* !__local___localdep_ctime32_defined */
/* Dependency: ctime64 from time */
#ifndef __local___localdep_ctime64_defined
#define __local___localdep_ctime64_defined 1
#ifdef __CRT_HAVE_ctime64
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),ctime64,(__timer))
#elif defined(__CRT_HAVE_ctime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime64)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),_ctime64,(__timer))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/time/ctime64.h>
__NAMESPACE_LOCAL_BEGIN
/* Equivalent to `asctime(localtime(timer))' */
#define __localdep_ctime64 __LIBC_LOCAL_NAME(ctime64)
#endif /* !... */
#endif /* !__local___localdep_ctime64_defined */
/* Dependency: ctime_r from time */
#ifndef __local___localdep_ctime_r_defined
#define __local___localdep_ctime_r_defined 1
#ifdef __CRT_HAVE_ctime_r
__NAMESPACE_LOCAL_END
#ifndef __STRUCT_TM
#ifdef __tm_defined
#define __STRUCT_TM struct tm
#else /* __tm_defined */
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
struct tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	__LONGPTR_TYPE__ tm_gmtoff;   /* Seconds east of UTC. */
	char const      *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	__LONGPTR_TYPE__ __tm_gmtoff; /* Seconds east of UTC. */
	char const      *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif
__NAMESPACE_LOCAL_BEGIN
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_ctime_r,(__TM_TYPE(time) const *__restrict __timer, char __buf[26]),ctime_r,(__timer,__buf))
#else /* __CRT_HAVE_ctime_r */
__NAMESPACE_LOCAL_END
#include <local/time/ctime_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
#define __localdep_ctime_r __LIBC_LOCAL_NAME(ctime_r)
#endif /* !__CRT_HAVE_ctime_r */
#endif /* !__local___localdep_ctime_r_defined */
__NAMESPACE_LOCAL_END
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32))
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_ctime && !__CRT_HAVE__ctime32) */
__NAMESPACE_LOCAL_BEGIN
/* Equivalent to `asctime(localtime(timer))' */
__LOCAL_LIBC(ctime) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctime))(__TM_TYPE(time) const *__timer) {
#ifdef __BUILDING_LIBC
	return __localdep_ctime_r(__timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
#else /* __BUILDING_LIBC */
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_ctime64(&__tm64);





#endif /* !__BUILDING_LIBC */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ctime_defined
#define __local___localdep_ctime_defined 1
#define __localdep_ctime __LIBC_LOCAL_NAME(ctime)
#endif /* !__local___localdep_ctime_defined */
#endif /* !__local_ctime_defined */
