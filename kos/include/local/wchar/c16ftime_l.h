/* HASH CRC-32:0x1b274688 */
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
#ifndef __local_c16ftime_l_defined
#define __local_c16ftime_l_defined 1
#ifndef __STRUCT_TM
#ifdef __tm_defined
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#else /* __tm_defined */
#define __STRUCT_TM struct __NAMESPACE_STD_SYM __NAMESPACE_STD_SYM tm
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
struct __NAMESPACE_STD_SYM tm {
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
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Dependency: "wcsftime" from "wchar" */
#ifndef ____localdep_c16ftime_defined
#define ____localdep_c16ftime_defined 1
#if defined(__CRT_HAVE_wcsftime) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16ftime,(__CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR16_TYPE__ const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif defined(__CRT_HAVE_DOS$wcsftime)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16ftime,(__CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR16_TYPE__ const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsftime.h>
#define __localdep_c16ftime (*(__SIZE_TYPE__(__LIBCCALL*)(__CHAR16_TYPE__ *__restrict, __SIZE_TYPE__, __CHAR16_TYPE__ const *__restrict, struct __NAMESPACE_STD_SYM tm const *__restrict))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime)))
#else /* LIBC: c16ftime */
#include <local/wchar/c16ftime.h>
#define __localdep_c16ftime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ftime))
#endif /* c16ftime... */
#endif /* !____localdep_c16ftime_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16ftime_l) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16ftime_l))(__CHAR16_TYPE__ *__restrict __buf,
                                                        __SIZE_TYPE__ __maxsize,
                                                        __CHAR16_TYPE__ const *__restrict __format,
                                                        __STRUCT_TM const *__restrict __tp,
                                                        __locale_t __locale) {
#line 1116 "kos/src/libc/magic/wchar.c"
	(void)__locale;
	return __localdep_c16ftime(__buf, __maxsize, __format, __tp);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16ftime_l_defined */
