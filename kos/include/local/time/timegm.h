/* HASH CRC-32:0x2c1708de */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_timegm_defined
#define __local_timegm_defined 1
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
/* Dependency: "timegm64" from "time" */
#ifndef ____localdep_timegm64_defined
#define ____localdep_timegm64_defined 1
#ifdef __CRT_HAVE_timegm64
/* Like `mktime', but for TP represents Universal Time, not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_timegm64,(__STRUCT_TM *__tp),timegm64,(__tp))
#elif defined(__CRT_HAVE_timegm) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Like `mktime', but for TP represents Universal Time, not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_timegm64,(__STRUCT_TM *__tp),timegm,(__tp))
#else /* LIBC: timegm64 */
#include <local/time/timegm64.h>
/* Like `mktime', but for TP represents Universal Time, not local time */
#define __localdep_timegm64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm64))
#endif /* timegm64... */
#endif /* !____localdep_timegm64_defined */

/* Dependency: "mktime" from "time" */
#ifndef ____localdep_mktime_defined
#define ____localdep_mktime_defined 1
#if defined(__CRT_HAVE_mktime64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,__localdep_mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,__localdep_mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,__localdep_mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE_mktime) && (!defined(__USE_TIME_BITS64))
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,__localdep_mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime32) && (!defined(__USE_TIME_BITS64))
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,__localdep_mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal) && (!defined(__USE_TIME_BITS64))
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,__localdep_mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal,(__tp))
#else /* LIBC: mktime */
#include <local/time/mktime.h>
/* Return the `time_t' representation of TP and normalize TP */
#define __localdep_mktime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))
#endif /* mktime... */
#endif /* !____localdep_mktime_defined */

__NAMESPACE_LOCAL_BEGIN
/* Like `mktime', but for TP represents Universal Time, not local time */
__LOCAL_LIBC(timegm) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __TM_TYPE(time)
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timegm))(__STRUCT_TM *__tp) {
#line 882 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_timegm64) && !defined(__BUILDING_LIBC)
	return (__TM_TYPE(time))__localdep_timegm64(__tp);
#else
	/* TODO: Timezones */
	return __localdep_mktime(__tp);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_timegm_defined */
