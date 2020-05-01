/* HASH CRC-32:0x4e43e3a0 */
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
#ifndef __local_mktime64_defined
#define __local_mktime64_defined 1
#include <__crt.h>
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
/* Dependency: "mktime32" from "time" */
#ifndef ____localdep_mktime32_defined
#define ____localdep_mktime32_defined 1
#ifdef __CRT_HAVE_mktime
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_mktime32,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime32)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_mktime32,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_mktime32,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal,(__tp))
#else /* LIBC: mktime */
#undef ____localdep_mktime32_defined
#endif /* mktime32... */
#endif /* !____localdep_mktime32_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
/* Return the `time_t' representation of TP and normalize TP */
__LOCAL_LIBC(mktime64) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mktime64))(__STRUCT_TM __KOS_FIXED_CONST *__tp) {
#line 651 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_mktime) || defined(__CRT_HAVE__mktime32) || defined(__CRT_HAVE_timelocal)
	return (__time64_t)__localdep_mktime32(__tp);
#else /* __CRT_HAVE_mktime || __CRT_HAVE__mktime32 || __CRT_HAVE_timelocal */
	__time64_t __result;
	__result = __yearstodays(__tp->tm_year) - __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	__result += __tp->tm_yday;
	__result *= 86400; /* SECONDS_PER_DAY */
	__result += __tp->tm_hour*60*60;
	__result += __tp->tm_min*60;
	__result += __tp->tm_sec;
	return __result;
#endif /* !__CRT_HAVE_mktime && !__CRT_HAVE__mktime32 && !__CRT_HAVE_timelocal */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mktime64_defined */
