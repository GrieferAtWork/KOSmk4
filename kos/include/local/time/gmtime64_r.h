/* HASH CRC-32:0x33357133 */
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
#ifndef __local_gmtime64_r_defined
#define __local_gmtime64_r_defined 1
#ifndef __tm_defined
#define __tm_defined 1
#ifdef __std_tm_defined
__NAMESPACE_STD_USING(tm)
#else /* __std_tm_defined */
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
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
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
/* Dependency: "dos_gmtime64_s" from "time" */
#ifndef ____localdep_dos_gmtime64_s_defined
#define ____localdep_dos_gmtime64_s_defined 1
#if defined(__CRT_HAVE__gmtime64_s)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_gmtime64_s,(struct tm *__restrict __tp, __time64_t const *__restrict __timer),_gmtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__gmtime32_s)
#include <local/time/dos_gmtime64_s.h>
#define __localdep_dos_gmtime64_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dos_gmtime64_s))
#else /* CUSTOM: dos_gmtime64_s */
#undef ____localdep_dos_gmtime64_s_defined
#endif /* dos_gmtime64_s... */
#endif /* !____localdep_dos_gmtime64_s_defined */

__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(gmtime64_r) __ATTR_NONNULL((1, 2)) struct tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gmtime64_r))(__time64_t const *__restrict __timer,
                                                        struct tm *__restrict __tp) {
#line 1673 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE__gmtime32_s) || defined(__CRT_HAVE__gmtime64_s)) && !defined(__BUILDING_LIBC)
	return __localdep_dos_gmtime64_s(__tp, __timer) ? __NULLPTR : __tp;
#else
	__time64_t __t; int __i;
	__UINT16_TYPE__ const *__monthvec;
	__t = *__timer;
	__tp->tm_sec  = (int)(__t % 60);
	__tp->tm_min  = (int)((__t/60) % 60);
	__tp->tm_hour = (int)((__t/(60*60)) % 24);
	__t /= 86400; /* SECONDS_PER_DAY */
	__t += __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	__tp->tm_wday = (int)(__t % 7); /* DAYS_PER_WEEK */
	__tp->tm_year = (int)__daystoyears(__t);
	__t -= __yearstodays(__tp->tm_year);
	__tp->tm_yday = (int)__t;
	__monthvec = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(__tp->tm_year)];
	for (__i = 1; __i < 12; ++__i)
		if (__monthvec[__i] >= __t)
			break;
	__tp->tm_mon = __i;
	__t -= __monthvec[__i - 1];
	__tp->tm_mday = __t;
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (__tp->tm_mon < 3 || __tp->tm_mon > 11) {
		//January, February, and December are out.
		__tp->tm_isdst = 0;
	} else if (__tp->tm_mon > 3 && __tp->tm_mon < 11) {
		//April to October are in
		__tp->tm_isdst = 1;
	} else {
		int __previousSunday;
		__previousSunday = __tp->tm_mday - __tp->tm_wday;
		if (__tp->tm_mon == 3) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			__tp->tm_isdst = __previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the previous Sunday must be before the 1st.
			__tp->tm_isdst = __previousSunday <= 0;
		}
	}
	__tp->tm_year -= 1900;
	return __tp;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_gmtime64_r_defined */
