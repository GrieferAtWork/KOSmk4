/* HASH CRC-32:0xf3044bd5 */
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
#ifndef __local_gmtime_r_defined
#define __local_gmtime_r_defined 1
#include <__crt.h>
#include <bits/types.h>
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
#endif /* !__STRUCT_TM */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: dos_gmtime_s from time */
#ifndef __local___localdep_dos_gmtime_s_defined
#define __local___localdep_dos_gmtime_s_defined 1
#if defined(__CRT_HAVE__gmtime32_s) && defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_gmtime_s,(__STRUCT_TM *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_gmtime32_s,(__tp,__timer))
#elif defined(__CRT_HAVE__gmtime64_s) && !defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_gmtime_s,(__STRUCT_TM *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_gmtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__gmtime64_s) || defined(__CRT_HAVE__gmtime32_s)
__NAMESPACE_LOCAL_END
#include <local/time/dos_gmtime_s.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_dos_gmtime_s __LIBC_LOCAL_NAME(dos_gmtime_s)
#else /* ... */
#undef __local___localdep_dos_gmtime_s_defined
#endif /* !... */
#endif /* !__local___localdep_dos_gmtime_s_defined */
/* Dependency: gmtime64_r from time */
#ifndef __local___localdep_gmtime64_r_defined
#define __local___localdep_gmtime64_r_defined 1
#ifdef __CRT_HAVE_gmtime64_r
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),gmtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),gmtime_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/time/gmtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_gmtime64_r __LIBC_LOCAL_NAME(gmtime64_r)
#endif /* !... */
#endif /* !__local___localdep_gmtime64_r_defined */
__NAMESPACE_LOCAL_END
#ifdef __BUILDING_LIBC
#ifndef __isleap
#define __isleap(__year) ((__year)%4 == 0 && ((__year)%100 != 0 || (__year)%400 == 0))
#endif /* !__isleap */
#ifndef __daystoyears
#define __daystoyears(__n_days)  ((400*((__n_days)+1))/146097)
#endif /* !__daystoyears */
#ifndef __yearstodays
#define __yearstodays(__n_years) (((146097*(__n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
#ifndef ____TIME_MONTHSTART_YDAY_DEFINED
#define ____TIME_MONTHSTART_YDAY_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__time_monthstart_yday)
__UINT16_TYPE__ const __time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};
__NAMESPACE_LOCAL_END
#endif /* !____TIME_MONTHSTART_YDAY_DEFINED */

#endif /* __BUILDING_LIBC */
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__LOCAL_LIBC(gmtime_r) __ATTR_NONNULL((1, 2)) __STRUCT_TM *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gmtime_r))(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp) {









































#if defined(__CRT_HAVE__gmtime64_s) || defined(__CRT_HAVE__gmtime32_s)
	return __localdep_dos_gmtime_s(__tp, __timer) ? __NULLPTR : __tp;
#elif defined(__USE_TIME_BITS64)
	return __localdep_gmtime64_r(__timer, __tp);
#else /* ... */
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_gmtime64_r(&__tm64, __tp);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gmtime_r_defined
#define __local___localdep_gmtime_r_defined 1
#define __localdep_gmtime_r __LIBC_LOCAL_NAME(gmtime_r)
#endif /* !__local___localdep_gmtime_r_defined */
#endif /* !__local_gmtime_r_defined */
