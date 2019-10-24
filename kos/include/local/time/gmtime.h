/* HASH CRC-32:0x7c99f53c */
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
#ifndef __local_gmtime_defined
#define __local_gmtime_defined 1
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
/* Dependency: "gmtime64" from "time" */
#ifndef ____localdep_gmtime64_defined
#define ____localdep_gmtime64_defined 1
#if defined(__CRT_HAVE_gmtime64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime64,(__time64_t const *__timer),gmtime64,(__timer))
#elif defined(__CRT_HAVE_gmtime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime64,(__time64_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE__gmtime64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime64,(__time64_t const *__timer),_gmtime64,(__timer))
#else /* LIBC: gmtime64 */
#include <local/time/gmtime64.h>
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
#define __localdep_gmtime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64))
#endif /* gmtime64... */
#endif /* !____localdep_gmtime64_defined */

/* Dependency: "gmtime32" from "time" */
#ifndef ____localdep_gmtime32_defined
#define ____localdep_gmtime32_defined 1
#if defined(__CRT_HAVE_gmtime)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime32,(__time32_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE__gmtime32)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime32,(__time32_t const *__timer),_gmtime32,(__timer))
#else /* LIBC: gmtime */
#undef ____localdep_gmtime32_defined
#endif /* gmtime32... */
#endif /* !____localdep_gmtime32_defined */

/* Dependency: "gmtime_r" from "time" */
#ifndef ____localdep_gmtime_r_defined
#define ____localdep_gmtime_r_defined 1
#if defined(__CRT_HAVE_gmtime_r)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime_r,(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp),gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime_r)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime_r,(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp),__gmtime_r,(__timer,__tp))
#else /* LIBC: gmtime_r */
#include <local/time/gmtime_r.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_gmtime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime_r))
#endif /* gmtime_r... */
#endif /* !____localdep_gmtime_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__LOCAL_LIBC(gmtime) __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gmtime))(__TM_TYPE(time) const *__timer) {
#line 529 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_gmtime64) || defined(__CRT_HAVE__gmtime64)
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_gmtime64(&__tm64);
#elif defined(__CRT_HAVE_gmtime) || defined(__CRT_HAVE__gmtime32)
	__time32_t __tm32 = (__time32_t)*__timer;
	return __localdep_gmtime32(&__tm32);
#else
	return __localdep_gmtime_r(__timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_gmtime_defined */
