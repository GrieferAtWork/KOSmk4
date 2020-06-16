/* HASH CRC-32:0xc183828d */
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
#ifndef __local_c32ftime_l_defined
#define __local_c32ftime_l_defined 1
#include <__crt.h>
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
/* Dependency: c32ftime from parts.uchar.time */
#ifndef __local___localdep_c32ftime_defined
#define __local___localdep_c32ftime_defined 1
#if defined(__CRT_HAVE_wcsftime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32ftime,(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif defined(__CRT_HAVE_KOS$wcsftime)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32ftime,(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsftime.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32ftime (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ *__restrict, __SIZE_TYPE__, __CHAR32_TYPE__ const *__restrict, struct __NAMESPACE_STD_SYM tm const *__restrict))&__LIBC_LOCAL_NAME(wcsftime))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.time/c32ftime.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32ftime __LIBC_LOCAL_NAME(c32ftime)
#endif /* !... */
#endif /* !__local___localdep_c32ftime_defined */
__LOCAL_LIBC(c32ftime_l) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32ftime_l))(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __maxsize, __CHAR32_TYPE__ const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale) {
	(void)__locale;
	return __localdep_c32ftime(__buf, __maxsize, __format, __tp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32ftime_l_defined
#define __local___localdep_c32ftime_l_defined 1
#define __localdep_c32ftime_l __LIBC_LOCAL_NAME(c32ftime_l)
#endif /* !__local___localdep_c32ftime_l_defined */
#endif /* !__local_c32ftime_l_defined */
