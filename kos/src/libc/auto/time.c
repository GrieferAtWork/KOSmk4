/* HASH CRC-32:0x5384e47b */
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
#ifndef GUARD_LIBC_AUTO_TIME_C
#define GUARD_LIBC_AUTO_TIME_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "time.h"
#include "stdio.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Return the difference between TIME1 and TIME0 */
INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.time.difftime") double
NOTHROW_NCX(LIBCCALL libc_difftime)(time_t time1,
                                    time_t time0) {
#line 417 "kos/src/libc/magic/time.c"
	return (double)time1 - (double)time0;
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
/* Return the `time_t' representation of TP and normalize TP */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.mktime") time_t
NOTHROW_NCX(LIBCCALL libc_mktime)(__STRUCT_TM __KOS_FIXED_CONST *tp) {
#line 439 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_mktime64) || defined(__CRT_HAVE__mktime64)
	return (time_t)libc_mktime64(tp);
#elif defined(__CRT_HAVE_mktime) || defined(__CRT_HAVE__mktime32)
	return (time_t)libc_mktime32(tp);
#else
	__TM_TYPE(time) result;
	result = __yearstodays(tp->tm_year) - __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	result += tp->tm_yday;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->tm_hour*60*60;
	result += tp->tm_min*60;
	result += tp->tm_sec;
	return result;
#endif
}

#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_ctime64) && !defined(__CRT_HAVE__ctime64) && \
     !defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32)) || \
     !defined(__CRT_HAVE_asctime) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK char __ctime_buf[26] = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY char __ctime_buf[26] = {0};
#else
__PRIVATE __ATTR_UNUSED char __ctime_buf[26] = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */
/* Equivalent to `asctime (localtime (timer))' */
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.ctime") char *
NOTHROW_NCX(LIBCCALL libc_ctime)(time_t const *timer) {
#line 488 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_ctime64) || defined(__CRT_HAVE__ctime64)
	time64_t tm64 = (time64_t)*timer;
	return libc_ctime64(&tm64);
#elif defined(__CRT_HAVE_ctime) || defined(__CRT_HAVE__ctime32)
	time32_t tm32 = (time32_t)*timer;
	return libc_ctime32(&tm32);
#else
	return libc_ctime_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
#endif
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_gmtime64) && !defined(__CRT_HAVE__gmtime64) && \
     !defined(__CRT_HAVE_gmtime) && !defined(__CRT_HAVE__gmtime32)) || \
    (!defined(__CRT_HAVE_localtime64) && !defined(__CRT_HAVE__localtime64) && \
     !defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32)) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK __STRUCT_TM __gmtime_buf = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY __STRUCT_TM __gmtime_buf = {0};
#else
__PRIVATE __ATTR_UNUSED __STRUCT_TM __gmtime_buf = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.gmtime") struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime)(time_t const *timer) {
#line 529 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_gmtime64) || defined(__CRT_HAVE__gmtime64)
	time64_t tm64 = (time64_t)*timer;
	return libc_gmtime64(&tm64);
#elif defined(__CRT_HAVE_gmtime) || defined(__CRT_HAVE__gmtime32)
	time32_t tm32 = (time32_t)*timer;
	return libc_gmtime32(&tm32);
#else
	return libc_gmtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_gmtime64) && !defined(__CRT_HAVE__gmtime64) && \
     !defined(__CRT_HAVE_gmtime) && !defined(__CRT_HAVE__gmtime32)) || \
    (!defined(__CRT_HAVE_localtime64) && !defined(__CRT_HAVE__localtime64) && \
     !defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32)) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK __STRUCT_TM __gmtime_buf = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY __STRUCT_TM __gmtime_buf = {0};
#else
__PRIVATE __ATTR_UNUSED __STRUCT_TM __gmtime_buf = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.localtime") struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime)(time_t const *timer) {
#line 546 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_localtime64) || defined(__CRT_HAVE__localtime64)
	time64_t tm64 = (time64_t)*timer;
	return libc_localtime64(&tm64);
#elif defined(__CRT_HAVE_localtime) || defined(__CRT_HAVE__localtime32)
	time32_t tm32 = (time32_t)*timer;
	return libc_localtime32(&tm32);
#else
	return libc_localtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
INTERN NONNULL((1, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.time.strftime") size_t
NOTHROW_NCX(LIBCCALL libc_strftime)(char *__restrict buf,
                                    size_t bufsize,
                                    char const *__restrict format,
                                    __STRUCT_TM const *__restrict tp) {
#line 574 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE_strftime_l) || defined(__CRT_HAVE__strftime_l)) && !defined(__BUILDING_LIBC)
	return libc_crt_strftime_l(buf, bufsize, format, tp, NULL);
#else
	/* TODO */
	return 0;
#endif
}

#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_ctime64) && !defined(__CRT_HAVE__ctime64) && \
     !defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32)) || \
     !defined(__CRT_HAVE_asctime) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK char __ctime_buf[26] = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY char __ctime_buf[26] = {0};
#else
__PRIVATE __ATTR_UNUSED char __ctime_buf[26] = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.asctime") char *
NOTHROW_NCX(LIBCCALL libc_asctime)(struct tm const *tp) {
#line 607 "kos/src/libc/magic/time.c"
	return libc_asctime_r(tp, __NAMESPACE_LOCAL_SYM __ctime_buf);
}

#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.time.asctime_s") errno_t
NOTHROW_NCX(LIBCCALL libc_asctime_s)(char *__restrict buf,
                                     size_t buflen,
                                     struct tm const *__restrict tp) {
#line 616 "kos/src/libc/magic/time.c"
	if (buflen < 26)
		return __ERANGE;
	libc_asctime_r(tp, buf);
	return 0;
}

/* Return the difference between TIME1 and TIME0 */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_difftime64, libc_difftime);
#else
INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.time.difftime64") double
NOTHROW_NCX(LIBCCALL libc_difftime64)(time64_t time1,
                                      time64_t time0) {
#line 640 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE_difftime) || defined(__CRT_HAVE__difftime32)) && !defined(__BUILDING_LIBC)
	return libc_difftime32((time32_t)time1, (time32_t)time0);
#else /* ... */
	return (double)time1 - (double)time0;
#endif /* !... */
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
/* Return the `time_t' representation of TP and normalize TP */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mktime64, libc_mktime);
#else
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.mktime64") time64_t
NOTHROW_NCX(LIBCCALL libc_mktime64)(__STRUCT_TM __KOS_FIXED_CONST *tp) {
#line 658 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE_mktime) || defined(__CRT_HAVE__mktime32)) && !defined(__BUILDING_LIBC)
	return (time64_t)libc_mktime32(tp);
#else
	time64_t result;
	result = __yearstodays(tp->tm_year) - __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	result += tp->tm_yday;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->tm_hour*60*60;
	result += tp->tm_min*60;
	result += tp->tm_sec;
	return result;
#endif
}
#endif /* MAGIC:alias */

#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_ctime64) && !defined(__CRT_HAVE__ctime64) && \
     !defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32)) || \
     !defined(__CRT_HAVE_asctime) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK char __ctime_buf[26] = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY char __ctime_buf[26] = {0};
#else
__PRIVATE __ATTR_UNUSED char __ctime_buf[26] = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */
/* Equivalent to `asctime (localtime (timer))' */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ctime64, libc_ctime);
#else
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.ctime64") char *
NOTHROW_NCX(LIBCCALL libc_ctime64)(time64_t const *timer) {
#line 692 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE_ctime) || defined(__CRT_HAVE__ctime32)) && !defined(__BUILDING_LIBC)
	time32_t tm32 = (time32_t)*timer;
	return libc_ctime32(&tm32);
#else
	return libc_ctime64_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
#endif
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_gmtime64) && !defined(__CRT_HAVE__gmtime64) && \
     !defined(__CRT_HAVE_gmtime) && !defined(__CRT_HAVE__gmtime32)) || \
    (!defined(__CRT_HAVE_localtime64) && !defined(__CRT_HAVE__localtime64) && \
     !defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32)) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK __STRUCT_TM __gmtime_buf = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY __STRUCT_TM __gmtime_buf = {0};
#else
__PRIVATE __ATTR_UNUSED __STRUCT_TM __gmtime_buf = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gmtime64, libc_gmtime);
#else
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.gmtime64") __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_gmtime64)(time64_t const *timer) {
#line 703 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE_gmtime) || defined(__CRT_HAVE__gmtime32)) && !defined(__BUILDING_LIBC)
	time32_t tm32 = (time32_t)*timer;
	return libc_gmtime32(&tm32);
#else
	return libc_gmtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_gmtime64) && !defined(__CRT_HAVE__gmtime64) && \
     !defined(__CRT_HAVE_gmtime) && !defined(__CRT_HAVE__gmtime32)) || \
    (!defined(__CRT_HAVE_localtime64) && !defined(__CRT_HAVE__localtime64) && \
     !defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32)) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK __STRUCT_TM __gmtime_buf = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY __STRUCT_TM __gmtime_buf = {0};
#else
__PRIVATE __ATTR_UNUSED __STRUCT_TM __gmtime_buf = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
/* Return the `struct tm' representation of *TIMER in the local timezone */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_localtime64, libc_localtime);
#else
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.localtime64") __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_localtime64)(time64_t const *timer) {
#line 715 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE_localtime) || defined(__CRT_HAVE__localtime32)) && !defined(__BUILDING_LIBC)
	time32_t tm32 = (time32_t)*timer;
	return libc_localtime32(&tm32);
#else
	return libc_localtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Like `mktime', but for TP represents Universal Time, not local time */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.timegm") time_t
NOTHROW_NCX(LIBCCALL libc_timegm)(__STRUCT_TM *tp) {
#line 877 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_timegm64) && !defined(__BUILDING_LIBC)
	return (time_t)libc_timegm64(tp);
#else
	/* TODO: Timezones */
	return libc_mktime(tp);
#endif
}

/* Return the number of days in YEAR */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.time.dysize") int
NOTHROW_NCX(LIBCCALL libc_dysize)(int year) {
#line 894 "kos/src/libc/magic/time.c"
	return __isleap(year) ? 366 : 365;
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Like `mktime', but for TP represents Universal Time, not local time */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timegm64, libc_timegm);
#else
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.timegm64") time64_t
NOTHROW_NCX(LIBCCALL libc_timegm64)(__STRUCT_TM *tp) {
#line 912 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_timegm) && !defined(__BUILDING_LIBC)
	return (time64_t)libc_timegm32(tp);
#else /* __CRT_HAVE_timegm && !__BUILDING_LIBC */
	/* TODO: Timezones */
	return libc_mktime64(tp);
#endif /* !__CRT_HAVE_timegm || __BUILDING_LIBC */
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
INTERN NONNULL((1, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.time.strftime_l") size_t
NOTHROW_NCX(LIBCCALL libc_strftime_l)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      __STRUCT_TM const *__restrict tp,
                                      locale_t locale) {
#line 1373 "kos/src/libc/magic/time.c"
	(void)locale;
	return libc_strftime(buf, bufsize, format, tp);
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.time.strptime") char *
NOTHROW_NCX(LIBCCALL libc_strptime)(char const *__restrict s,
                                    char const *__restrict format,
                                    __STRUCT_TM *__restrict tp) {
#line 1393 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_strptime_l) && !defined(__BUILDING_LIBC)
	return libc_crt_strptime_l(s, format, tp, NULL);
#else
	/* TODO */
	return NULL;
#endif
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.time.strptime_l") char *
NOTHROW_NCX(LIBCCALL libc_strptime_l)(char const *__restrict s,
                                      char const *__restrict format,
                                      __STRUCT_TM *__restrict tp,
                                      locale_t locale) {
#line 1411 "kos/src/libc/magic/time.c"
	(void)locale;
	return libc_strptime(s, format, tp);
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.getdate_r") int
NOTHROW_NCX(LIBCCALL libc_getdate_r)(char const *__restrict string,
                                     __STRUCT_TM *__restrict resbufp) {
#line 1418 "kos/src/libc/magic/time.c"
	/* TODO */
	return 0;
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.gmtime_r") __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_gmtime_r)(time_t const *__restrict timer,
                                    __STRUCT_TM *__restrict tp) {
#line 1434 "kos/src/libc/magic/time.c"
	time64_t tm64 = (time64_t)*timer;
	return libc_gmtime64_r(&tm64, tp);
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.localtime_r") __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_localtime_r)(time_t const *__restrict timer,
                                       __STRUCT_TM *__restrict tp) {
#line 1450 "kos/src/libc/magic/time.c"
	time64_t tm64 = (time64_t)*timer;
	return libc_localtime64_r(&tm64, tp);
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.ctime_r") char *
NOTHROW_NCX(LIBCCALL libc_ctime_r)(time_t const *__restrict timer,
                                   char buf[26]) {
#line 1465 "kos/src/libc/magic/time.c"
	struct tm ltm;
	return libc_asctime_r(libc_localtime_r(timer, &ltm), buf);
}

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */

#ifndef __LIBC_TIME_MOUNTSTART_YDAY_DEFINED
#define __LIBC_TIME_MOUNTSTART_YDAY_DEFINED 1
#if (!defined(__CRT_HAVE__gmtime32_s) && !defined(__CRT_HAVE__gmtime64_s)) || \
    (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN_CONST __ATTR_UNUSED __ATTR_WEAK __UINT16_TYPE__ const __time_monthstart_yday[2][13] =
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN_CONST __ATTR_UNUSED __ATTR_SELECTANY __UINT16_TYPE__ const __time_monthstart_yday[2][13] =
#else
__PRIVATE __ATTR_UNUSED __UINT16_TYPE__ const __time_monthstart_yday[2][13] =
#endif
{
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_TIME_MOUNTSTART_YDAY_DEFINED */
#ifndef __isleap
#define __isleap(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#endif /* !__isleap */
#ifndef __daystoyears
#define __daystoyears(n_days)  ((400*((n_days)+1))/146097)
#endif /* !__daystoyears */
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gmtime64_r, libc_gmtime_r);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.gmtime64_r") __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_gmtime64_r)(time64_t const *__restrict timer,
                                      __STRUCT_TM *__restrict tp) {
#line 1515 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE__gmtime32_s) || defined(__CRT_HAVE__gmtime64_s)) && !defined(__BUILDING_LIBC)
	return libc_dos_gmtime64_s(tp, timer) ? NULL : tp;
#else
	time64_t t; int i;
	u16 const *monthvec;
	t = *timer;
	tp->tm_sec  = (int)(t % 60);
	tp->tm_min  = (int)((t/60) % 60);
	tp->tm_hour = (int)((t/(60*60)) % 24);
	t /= 86400; /* SECONDS_PER_DAY */
	t += __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	tp->tm_wday = (int)(t % 7); /* DAYS_PER_WEEK */
	tp->tm_year = (int)__daystoyears(t);
	t -= __yearstodays(tp->tm_year);
	tp->tm_yday = (int)t;
	monthvec = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(tp->tm_year)];
	for (i = 1; i < 12; ++i)
		if (monthvec[i] >= t)
			break;
	tp->tm_mon = i;
	t -= monthvec[i - 1];
	tp->tm_mday = t;
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (tp->tm_mon < 3 || tp->tm_mon > 11) {
		//January, February, and December are out.
		tp->tm_isdst = 0;
	} else if (tp->tm_mon > 3 && tp->tm_mon < 11) {
		//April to October are in
		tp->tm_isdst = 1;
	} else {
		int previousSunday;
		previousSunday = tp->tm_mday - tp->tm_wday;
		if (tp->tm_mon == 3) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			tp->tm_isdst = previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the previous Sunday must be before the 1st.
			tp->tm_isdst = previousSunday <= 0;
		}
	}
	tp->tm_year -= 1900;
	return tp;
#endif
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_localtime64_r, libc_localtime_r);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.localtime64_r") __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_localtime64_r)(time64_t const *__restrict timer,
                                         __STRUCT_TM *__restrict tp) {
#line 1566 "kos/src/libc/magic/time.c"
	/* XXX: Timezone support? */
	return libc_gmtime64_r(timer, tp);
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ctime64_r, libc_ctime_r);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.ctime64_r") char *
NOTHROW_NCX(LIBCCALL libc_ctime64_r)(time64_t const *__restrict timer,
                                     char buf[26]) {
#line 1579 "kos/src/libc/magic/time.c"
	struct tm ltm;
	return libc_asctime_r(libc_localtime64_r(timer, &ltm), buf);
}
#endif /* MAGIC:alias */

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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */

#ifndef __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
#define __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED 1
#if (!defined(__CRT_HAVE__asctime32_s) && !defined(__CRT_HAVE__asctime64_s)) || \
    (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN_CONST __ATTR_UNUSED __ATTR_WEAK char const __abbr_wday_names[7][4] =
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN_CONST __ATTR_UNUSED __ATTR_SELECTANY char const __abbr_wday_names[7][4] =
#else
__PRIVATE __ATTR_UNUSED char const __abbr_wday_names[7][4] =
#endif
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_TIME_ABBR_WDAY_NAMES_DEFINED */
#ifndef __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
#define __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED 1
#if (!defined(__CRT_HAVE__asctime32_s) && !defined(__CRT_HAVE__asctime64_s)) || \
    (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN_CONST __ATTR_UNUSED __ATTR_WEAK char const __abbr_month_names[12][4] =
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN_CONST __ATTR_UNUSED __ATTR_SELECTANY char const __abbr_month_names[12][4] =
#else
__PRIVATE __ATTR_UNUSED char const __abbr_month_names[12][4] =
#endif
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun",  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_TIME_ABBR_MONTH_NAMES_DEFINED */
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.asctime_r") char *
NOTHROW_NCX(LIBCCALL libc_asctime_r)(__STRUCT_TM const *__restrict tp,
                                     char buf[26]) {
#line 1633 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_asctime_s) && !defined(__BUILDING_LIBC)
	return libc_crt_asctime_s(buf, 26, tp) ? NULL : buf;
#else
	libc_sprintf(buf,
	        "%.3s %.3s%3u %.2u:%.2u:%.2u %u\n",
	       (unsigned int)tp->tm_wday >= 7 ? "??" "?" :
	        __NAMESPACE_LOCAL_SYM __abbr_wday_names[tp->tm_wday],
	       (unsigned int)tp->tm_mon >= 12 ? "??" "?" :
	        __NAMESPACE_LOCAL_SYM __abbr_month_names[tp->tm_mon],
	       (unsigned int)tp->tm_mday,
	       (unsigned int)tp->tm_hour,
	       (unsigned int)tp->tm_min,
	       (unsigned int)tp->tm_sec,
	       (unsigned int)tp->tm_year + 1900);
	return buf;
#endif
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(difftime, libc_difftime);
DEFINE_PUBLIC_WEAK_ALIAS(mktime, libc_mktime);
DEFINE_PUBLIC_WEAK_ALIAS(timelocal, libc_mktime);
DEFINE_PUBLIC_WEAK_ALIAS(ctime, libc_ctime);
DEFINE_PUBLIC_WEAK_ALIAS(gmtime, libc_gmtime);
DEFINE_PUBLIC_WEAK_ALIAS(localtime, libc_localtime);
DEFINE_PUBLIC_WEAK_ALIAS(strftime, libc_strftime);
DEFINE_PUBLIC_WEAK_ALIAS(asctime, libc_asctime);
DEFINE_PUBLIC_WEAK_ALIAS(asctime_s, libc_asctime_s);
DEFINE_PUBLIC_WEAK_ALIAS(difftime64, libc_difftime64);
DEFINE_PUBLIC_WEAK_ALIAS(mktime64, libc_mktime64);
DEFINE_PUBLIC_WEAK_ALIAS(timelocal64, libc_mktime64);
DEFINE_PUBLIC_WEAK_ALIAS(ctime64, libc_ctime64);
DEFINE_PUBLIC_WEAK_ALIAS(gmtime64, libc_gmtime64);
DEFINE_PUBLIC_WEAK_ALIAS(localtime64, libc_localtime64);
DEFINE_PUBLIC_WEAK_ALIAS(timegm, libc_timegm);
DEFINE_PUBLIC_WEAK_ALIAS(dysize, libc_dysize);
DEFINE_PUBLIC_WEAK_ALIAS(timegm64, libc_timegm64);
DEFINE_PUBLIC_WEAK_ALIAS(strftime_l, libc_strftime_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strftime_l, libc_strftime_l);
DEFINE_PUBLIC_WEAK_ALIAS(strptime, libc_strptime);
DEFINE_PUBLIC_WEAK_ALIAS(strptime_l, libc_strptime_l);
DEFINE_PUBLIC_WEAK_ALIAS(getdate_r, libc_getdate_r);
DEFINE_PUBLIC_WEAK_ALIAS(gmtime_r, libc_gmtime_r);
DEFINE_PUBLIC_WEAK_ALIAS(__gmtime_r, libc_gmtime_r);
DEFINE_PUBLIC_WEAK_ALIAS(localtime_r, libc_localtime_r);
DEFINE_PUBLIC_WEAK_ALIAS(ctime_r, libc_ctime_r);
DEFINE_PUBLIC_WEAK_ALIAS(gmtime64_r, libc_gmtime64_r);
DEFINE_PUBLIC_WEAK_ALIAS(localtime64_r, libc_localtime64_r);
DEFINE_PUBLIC_WEAK_ALIAS(ctime64_r, libc_ctime64_r);
DEFINE_PUBLIC_WEAK_ALIAS(asctime_r, libc_asctime_r);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_TIME_C */
