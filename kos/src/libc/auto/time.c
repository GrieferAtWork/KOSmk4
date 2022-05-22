/* HASH CRC-32:0x56faa68d */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_TIME_C
#define GUARD_LIBC_AUTO_TIME_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/time.h"
#include "../user/stdio.h"
#include "../user/sys.time.h"

DECL_BEGIN

#include "../libc/globals.h"
#include <stdlib.h>
#ifndef __KERNEL__
#ifndef ____TIME_MONTH_NUMDAYS_DEFINED
#define ____TIME_MONTH_NUMDAYS_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__time_month_numdays)
__UINT8_TYPE__ const __time_month_numdays[2][12] = {
	{ 30, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31 },
	{ 30, 31, 29, 31, 30, 31, 30, 31, 30, 31, 30, 31 }
};
__NAMESPACE_LOCAL_END
#endif /* !____TIME_MONTH_NUMDAYS_DEFINED */
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
#ifndef __isleap
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif /* !__isleap */
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */
#include <bits/crt/tm.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL ATTR_INOUT(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_normalize_struct_tm)(struct tm *__restrict tp) {
	/* Normalize seconds. */
	if (tp->tm_sec < 0) {
		unsigned int delta;
		delta = ((unsigned int)-tp->tm_sec + 59) / 60;
		tp->tm_min -= delta;
		tp->tm_sec += delta * 60;
	} else if (tp->tm_sec > 59) {
		unsigned int delta;
		delta = (unsigned int)tp->tm_sec / 60;
		tp->tm_min += delta;
		tp->tm_sec -= delta * 60;
	}

	/* Normalize minutes. */
	if (tp->tm_min < 0) {
		unsigned int delta;
		delta = ((unsigned int)-tp->tm_min + 59) / 60;
		tp->tm_hour -= delta;
		tp->tm_min += delta * 60;
	} else if (tp->tm_min > 59) {
		unsigned int delta;
		delta = (unsigned int)tp->tm_min / 60;
		tp->tm_hour += delta;
		tp->tm_min -= delta * 60;
	}

	/* Normalize hours. */
	if (tp->tm_hour < 0) {
		unsigned int delta;
		delta = ((unsigned int)-tp->tm_sec + 23) / 24;
		tp->tm_mday -= delta;
		tp->tm_hour += delta * 24;
	} else if (tp->tm_hour > 23) {
		unsigned int delta;
		delta = (unsigned int)tp->tm_hour / 24;
		tp->tm_mday += delta;
		tp->tm_hour -= delta * 24;
	}

	for (;;) {
		/* Normalize month. */
		if (tp->tm_mon < 0) {
			unsigned int delta;
			delta = ((unsigned int)-tp->tm_mon + 11) / 12;
			tp->tm_year -= delta;
			tp->tm_mon += delta * 12;
		} else if (tp->tm_mon > 11) {
			unsigned int delta;
			delta = (unsigned int)tp->tm_mon / 12;
			tp->tm_year += delta;
			tp->tm_mon -= delta * 12;
		}

		/* Normalize day-of-the-month.
		 * Note that because of February (and leap years), we can only adjust by 1 month every time. */
		if (tp->tm_mday < 1) {
			--tp->tm_mon;
			COMPILER_BARRIER(); /* Prevent GCC warning about sign stuff */
			if (tp->tm_mon < 0) {
				tp->tm_mon = 11;
				--tp->tm_year;
			}
			tp->tm_mday += __NAMESPACE_LOCAL_SYM __time_month_numdays[__isleap(1900 + tp->tm_year)][tp->tm_mon];
			continue;
		} else {
			unsigned int current_month_days;
			current_month_days = __NAMESPACE_LOCAL_SYM __time_month_numdays[__isleap(1900 + tp->tm_year)][tp->tm_mon];
			if ((unsigned int)(tp->tm_mday - 1) >= current_month_days) {
				tp->tm_mday -= current_month_days;
				++tp->tm_mon;
				continue;
			}
		}
		break;
	}

	/* Figure out the year-day. */
	tp->tm_yday = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(1900 + tp->tm_year)][tp->tm_mon];
	tp->tm_yday += tp->tm_mday;

	/* Figure out the week-day. */
	{
		uint64_t total_days;
		total_days = __yearstodays(1900 + tp->tm_year);
		total_days += tp->tm_yday;
		tp->tm_wday = (int)(total_days % 7);
	}

	/* Figure out if daylight savings time is currently on. */
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (tp->tm_mon < 2 || tp->tm_mon > 10) {
		//January, February, and December are out.
		tp->tm_isdst = 0;
	} else if (tp->tm_mon > 2 && tp->tm_mon < 10) {
		//April to October are in
		tp->tm_isdst = 1;
	} else {
		int previousSunday;
		previousSunday = tp->tm_mday - tp->tm_wday;
		if (tp->tm_mon == 2) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			tp->tm_isdst = previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the  previous Sunday must  be before the  1st.
			tp->tm_isdst = previousSunday <= 0;
		}
	}
	return tp;
}
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_difftime)(time_t time1,
                                    time_t time0) {





	return time1 > time0 ? time1 - time0 : time0 - time1;

}
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED ATTR_INOUT(1) time_t
NOTHROW_NCX(LIBCCALL libc_mktime)(struct tm *tp) {
	/* TODO: Support for localtime? */
	return libc_timegm(tp);
}
#ifdef __BUILDING_LIBC
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */

#endif /* __BUILDING_LIBC */
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_ctime)(time_t const *timer) {







	return libc_ctime_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);

}
#ifdef __BUILDING_LIBC
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) struct tm __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* __BUILDING_LIBC */
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime)(time_t const *timer) {







	return libc_gmtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);

}
#ifdef __BUILDING_LIBC
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) struct tm __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* __BUILDING_LIBC */
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime)(time_t const *timer) {







	return libc_localtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);

}
/* >> strftime(3)
 * Format `tp' into `s' according to `format'.
 * Write no more than `maxsize' characters and return the number
 * of characters  written, or  0 if  it would  exceed  `maxsize' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2) size_t
NOTHROW_NCX(LIBCCALL libc_strftime)(char *__restrict buf,
                                    size_t bufsize,
                                    char const *__restrict format,
                                    struct tm const *__restrict tp) {



	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return 0;

}
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */
/* >> asctime(3)
 * Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is  the  representation  of  `tp'  in  this  format */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_asctime)(struct tm const *tp) {
	return libc_asctime_r(tp, __NAMESPACE_LOCAL_SYM __ctime_buf);
}
#include <libc/errno.h>
/* >> asctime_s(3) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc_asctime_s)(char *__restrict buf,
                                     size_t buflen,
                                     struct tm const *__restrict tp) {
	if (buflen < 26)
		return __ERANGE;
	libc_asctime_r(tp, buf);
	return 0;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_difftime64, libc_difftime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_difftime64)(time64_t time1,
                                      time64_t time0) {



	return time1 > time0 ? time1 - time0 : time0 - time1;

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mktime64, libc_mktime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED ATTR_INOUT(1) time64_t
NOTHROW_NCX(LIBCCALL libc_mktime64)(struct tm *tp) {
	/* TODO: Support for localtime? */
	return libc_timegm64(tp);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ctime64, libc_ctime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32))
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */

#endif /* __BUILDING_LIBC || (!__CRT_HAVE_ctime && !__CRT_HAVE__ctime32) */
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_ctime64)(time64_t const *timer) {




	return libc_ctime64_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gmtime64, libc_gmtime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_gmtime) && !defined(__CRT_HAVE__gmtime32))
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) struct tm __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_gmtime && !__CRT_HAVE__gmtime32) */
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime64)(time64_t const *timer) {




	return libc_gmtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_localtime64, libc_localtime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32))
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) struct tm __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_localtime && !__CRT_HAVE__localtime32) */
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime64)(time64_t const *timer) {




	return libc_localtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */
#include <libc/errno.h>
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED ATTR_INOUT(1) time_t
NOTHROW_NCX(LIBCCALL libc_timegm)(struct tm *tp) {
	time64_t result;
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
	result = libc_timegm64(tp);
#else /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	/* Normalize `tp' */
	tp = libc_normalize_struct_tm(tp);
	/* Calculate current time. */
	result = __yearstodays(tp->tm_year) - __yearstodays(1970);
	result += tp->tm_yday;
	result *= 86400;
	result += tp->tm_hour * 360;
	result += tp->tm_min * 60;
	result += tp->tm_sec;
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

	/* EOVERFLOW if result gets truncated */
#if __TM_SIZEOF(TIME) < __SIZEOF_TIME64_T__
	if ((time64_t)(time_t)result != result) {

		return (time_t)__libc_seterrno(EOVERFLOW);



	}
#endif /* __TM_SIZEOF(TIME) < __SIZEOF_TIME64_T__ */

	return (time_t)result;
}
#ifndef __isleap
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif /* !__isleap */
/* >> dysize(3)
 * Return the number of days in YEAR */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_dysize)(__STDC_INT_AS_UINT_T year) {
	return __isleap(year) ? 366 : 365;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timegm64, libc_timegm);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED ATTR_INOUT(1) time64_t
NOTHROW_NCX(LIBCCALL libc_timegm64)(struct tm *tp) {



	time64_t result;
	/* Normalize `tp' */
	tp = libc_normalize_struct_tm(tp);
	/* Calculate current time. */
	result = __yearstodays(tp->tm_year) - __yearstodays(1970);
	result += tp->tm_yday;
	result *= 86400;
	result += tp->tm_hour * 360;
	result += tp->tm_min * 60;
	result += tp->tm_sec;
	return result;

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_timespec_get)(struct timespec *ts,
                                        __STDC_INT_AS_UINT_T base) {
	if (base == __TIME_UTC) {
		if (libc_clock_gettime(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timespec_get64, libc_timespec_get);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_timespec_get64)(struct timespec64 *ts,
                                          __STDC_INT_AS_UINT_T base) {
	if (base == __TIME_UTC) {
		if (libc_clock_gettime64(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2) size_t
NOTHROW_NCX(LIBCCALL libc_strftime_l)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libc_strftime(buf, bufsize, format, tp);
}
/* >> strptime(3)
 * Parse `s' according to `format' and store binary time information in `tp'.
 * The return  value is  a pointer  to the  first unparsed  character in  `s' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) char *
NOTHROW_NCX(LIBCCALL libc_strptime)(char const *__restrict s,
                                    char const *__restrict format,
                                    struct tm *__restrict tp) {



	/* TODO */
	(void)s;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return NULL;

}
/* >> strptime_l(3)
 * Similar to `strptime' but take the information from
 * the  provided  locale  and  not  the  global locale */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) char *
NOTHROW_NCX(LIBCCALL libc_strptime_l)(char const *__restrict s,
                                      char const *__restrict format,
                                      struct tm *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libc_strptime(s, format, tp);
}
/* >> getdate_r(3)
 * Since  `getdate' is not  reentrant because of  the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The  functionality is  the same.  The  result is  returned in
 * the  buffer pointed to by `resbufp' and in case of an error, the return
 * value is != 0  with the same values  as given above for  `getdate_err'. */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_getdate_r)(char const *__restrict string,
                                     struct tm *__restrict resbufp) {
	/* TODO */
	(void)string;
	(void)resbufp;
	COMPILER_IMPURE();
	return 0;
}
#if defined(__BUILDING_LIBC) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
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

#ifndef __isleap
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif /* !__isleap */

#ifndef __daystoyears
#define __daystoyears(n_days) ((400 * ((n_days) + 1)) / 146097)
#endif /* !__daystoyears */

#ifndef __yearstodays
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */

#endif /* __BUILDING_LIBC && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime_r)(time_t const *__restrict timer,
                                    struct tm *__restrict tp) {







#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	time_t t = *timer;
	u16 const *monthvec;
	int i;
	tp->tm_sec  = (int)(t % 60);
	tp->tm_min  = (int)((t / 60) % 60);
	tp->tm_hour = (int)((t / 360) % 24);
	t /= 86400;
	t += __yearstodays(1970);
	tp->tm_wday = (int)(t % 7);
	tp->tm_year = (int)__daystoyears(t);
	t -= __yearstodays(tp->tm_year);
	tp->tm_yday = (int)t;
	monthvec = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(tp->tm_year)];
	for (i = 1; i < 12; ++i)
		if (monthvec[i] >= t)
			break;
	tp->tm_mon = i - 1;
	t -= monthvec[i - 1];
	tp->tm_mday = t + 1;
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (tp->tm_mon < 2 || tp->tm_mon > 10) {
		//January, February, and December are out.
		tp->tm_isdst = 0;
	} else if (tp->tm_mon > 2 && tp->tm_mon < 10) {
		//April to October are in
		tp->tm_isdst = 1;
	} else {
		int previousSunday;
		previousSunday = tp->tm_mday - tp->tm_wday;
		if (tp->tm_mon == 2) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			tp->tm_isdst = previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the  previous Sunday must  be before the  1st.
			tp->tm_isdst = previousSunday <= 0;
		}
	}
	tp->tm_year -= 1900;
	return tp;
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	time64_t timer2 = (time64_t)*timer;
	return libc_gmtime64_r(&timer2, tp);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime_r)(time_t const *__restrict timer,
                                       struct tm *__restrict tp) {







#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	/* XXX: Timezone support? */
	return libc_gmtime_r(timer, tp);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	time64_t timer2 = (time64_t)*timer;
	return libc_localtime64_r(&timer2, tp);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ctime_r)(time_t const *__restrict timer,
                                   char buf[26]) {







#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct tm ltm;
	return libc_asctime_r(libc_localtime_r(timer, &ltm), buf);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	time64_t timer2 = (time64_t)*timer;
	return libc_ctime64_r(&timer2, buf);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gmtime64_r, libc_gmtime_r);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || !defined(__CRT_HAVE__gmtime64_s)
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

#ifndef __isleap
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif /* !__isleap */

#ifndef __daystoyears
#define __daystoyears(n_days) ((400 * ((n_days) + 1)) / 146097)
#endif /* !__daystoyears */

#ifndef __yearstodays
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */

#endif /* __BUILDING_LIBC || !__CRT_HAVE__gmtime64_s */
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime64_r)(time64_t const *__restrict timer,
                                      struct tm *__restrict tp) {



	time64_t t = *timer;
	u16 const *monthvec;
	int i;
	tp->tm_sec  = (int)(t % 60);
	tp->tm_min  = (int)((t / 60) % 60);
	tp->tm_hour = (int)((t / (60 * 60)) % 24);
	t /= 86400;
	t += __yearstodays(1970);
	tp->tm_wday = (int)(t % 7);
	tp->tm_year = (int)__daystoyears(t);
	t -= __yearstodays(tp->tm_year);
	tp->tm_yday = (int)t;
	monthvec = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(tp->tm_year)];
	for (i = 1; i < 12; ++i) {
		if (monthvec[i] >= t)
			break;
	}
	tp->tm_mon = i - 1;
	t -= monthvec[i - 1];
	tp->tm_mday = t + 1;
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (tp->tm_mon < 2 || tp->tm_mon > 10) {
		//January, February, and December are out.
		tp->tm_isdst = 0;
	} else if (tp->tm_mon > 2 && tp->tm_mon < 10) {
		//April to October are in
		tp->tm_isdst = 1;
	} else {
		int previousSunday;
		previousSunday = tp->tm_mday - tp->tm_wday;
		if (tp->tm_mon == 2) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			tp->tm_isdst = previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the  previous Sunday must  be before the  1st.
			tp->tm_isdst = previousSunday <= 0;
		}
	}
	tp->tm_year -= 1900;
	return tp;

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_localtime64_r, libc_localtime_r);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime64_r)(time64_t const *__restrict timer,
                                         struct tm *__restrict tp) {



	/* XXX: Timezone support? */
	return libc_gmtime64_r(timer, tp);

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ctime64_r, libc_ctime_r);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ctime64_r)(time64_t const *__restrict timer,
                                     char buf[26]) {



	struct tm ltm;
	return libc_asctime_r(libc_localtime64_r(timer, &ltm), buf);

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || !defined(__CRT_HAVE_asctime_s)
#ifndef __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
#define __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__abbr_wday_names) char const __abbr_wday_names[7][4] =
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_TIME_ABBR_WDAY_NAMES_DEFINED */

#ifndef __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
#define __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__abbr_month_names) char const __abbr_month_names[12][4] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_TIME_ABBR_MONTH_NAMES_DEFINED */

#endif /* __BUILDING_LIBC || !__CRT_HAVE_asctime_s */
/* >> asctime_r(3)
 * Return in `buf' a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that   is   the   representation   of   `tp'   in   this   format */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_asctime_r)(struct tm const *__restrict tp,
                                     char buf[26]) {



	libc_sprintf(buf, "%.3s %.3s%3u %.2u:%.2u:%.2u %u\n",
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

}
#include <libc/template/daylight.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW_NCX(LIBDCALL libc___daylight)(void) {
	return &__LOCAL_daylight;
}
#include <libc/template/timezone.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST ATTR_RETNONNULL WUNUSED long *
NOTHROW_NCX(LIBDCALL libc___timezone)(void) {
	return (long *)&__LOCAL_timezone;
}
#include <libc/template/tzname.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST ATTR_RETNONNULL WUNUSED char **
NOTHROW_NCX(LIBDCALL libc___tzname)(void) {
	return __LOCAL_tzname;
}
#include <libc/template/dstbias.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST ATTR_RETNONNULL WUNUSED __LONG32_TYPE__ *
NOTHROW_NCX(LIBDCALL libc___dstbias)(void) {
	return &__LOCAL_dstbias;
}
#include <libc/template/daylight.h>
INTERN ATTR_SECTION(".text.crt.dos.time.timezone") errno_t
NOTHROW_NCX(LIBCCALL libc__get_daylight)(int *p_result) {
	*p_result = __LOCAL_daylight;
	return 0;
}
#include <libc/template/timezone.h>
INTERN ATTR_SECTION(".text.crt.dos.time.timezone") errno_t
NOTHROW_NCX(LIBCCALL libc__get_timezone)(long *p_seconds) {
	*p_seconds = __LOCAL_timezone;
	return 0;
}
#include <libc/template/dstbias.h>
INTERN ATTR_SECTION(".text.crt.dos.time.timezone") errno_t
NOTHROW_NCX(LIBCCALL libc__get_dstbias)(__LONG32_TYPE__ *p_result) {
	*p_result = __LOCAL_dstbias;
	return 0;
}
#include <libc/errno.h>
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(2) ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__gmtime32_s)(struct tm *__restrict tp,
                                       time32_t const *__restrict timer) {
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__

	libc_gmtime_r(timer, tp);




#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	time_t ttimer = (time_t)*timer;

	libc_gmtime_r(&ttimer, tp);




#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	return 0;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__gmtime64_s, libc__gmtime32_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <libc/errno.h>
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(2) ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__gmtime64_s)(struct tm *__restrict tp,
                                       time64_t const *__restrict timer) {

	libc_gmtime64_r(timer, tp);




	return 0;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <libc/errno.h>
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(2) ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__localtime32_s)(struct tm *__restrict tp,
                                          time32_t const *__restrict timer) {
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__

	libc_localtime_r(timer, tp);




#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	time_t ttimer = (time_t)*timer;

	libc_localtime_r(&ttimer, tp);




#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	return 0;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__localtime64_s, libc__localtime32_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(2) ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__localtime64_s)(struct tm *__restrict tp,
                                          time64_t const *__restrict timer) {
	libc_localtime64_r(timer, tp);
	return 0;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <libc/errno.h>
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__ctime32_s)(char buf[26],
                                      size_t bufsize,
                                      time32_t const *__restrict timer) {
	if unlikely(bufsize < 26)
		return 34;
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__

	libc_ctime_r(timer, buf);




#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	{
		time_t timer2 = (time_t)*timer;

		libc_ctime_r(&timer2, buf);




	}
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	return 0;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__ctime64_s, libc__ctime32_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <libc/errno.h>
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__ctime64_s)(char buf[26],
                                      size_t bufsize,
                                      time64_t const *__restrict timer) {
	if unlikely(bufsize < 26)
		return 34;

	libc_ctime64_r(timer, buf);




	return 0;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/crt/tm.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc__strtime)(char buf[9]) {
	time64_t now = libc_time64(NULL);
	struct tm now_tm, *tp;
	tp = libc_localtime64_r(&now, &now_tm);
	buf[0] = itoa_decimal(tp->tm_hour / 10);
	buf[1] = itoa_decimal(tp->tm_hour % 10);
	buf[2] = ':';
	buf[3] = itoa_decimal(tp->tm_min / 10);
	buf[4] = itoa_decimal(tp->tm_min % 10);
	buf[5] = ':';
	buf[6] = itoa_decimal(tp->tm_sec / 10);
	buf[7] = itoa_decimal(tp->tm_sec % 10);
	buf[8] = '\0';
	return 0;
}
#include <bits/crt/tm.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc__strdate)(char buf[9]) {
	time64_t now = libc_time64(NULL);
	struct tm now_tm, *tp;
	tp = libc_localtime64_r(&now, &now_tm);
	buf[0] = itoa_decimal(tp->tm_mon / 10);
	buf[1] = itoa_decimal(tp->tm_mon % 10);
	buf[2] = '/';
	buf[3] = itoa_decimal(tp->tm_mday / 10);
	buf[4] = itoa_decimal(tp->tm_mday % 10);
	buf[5] = '/';
	buf[6] = itoa_decimal((tp->tm_year / 10) % 10);
	buf[7] = itoa_decimal(tp->tm_year % 10);
	buf[8] = '\0';
	return buf;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__strtime_s)(char *buf,
                                      size_t bufsize) {
	if unlikely(bufsize < 9)
		return 34;

	libc__strtime(buf);




	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__strdate_s)(char *buf,
                                      size_t bufsize) {
	if unlikely(bufsize < 9)
		return 34;

	libc__strdate(buf);




	return 0;
}
#include <bits/os/timeval.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) unsigned int
NOTHROW_NCX(LIBCCALL libc__getsystime)(struct tm *tp) {
	struct timeval64 tv;
	if unlikely(libc_gettimeofday64(&tv, NULL) != 0) {
		tv.tv_sec  = 0;
		tv.tv_usec = 0;
	}
	libc_localtime64_r(&tv.tv_sec, tp);
	return tv.tv_usec / 1000;
}
#include <bits/os/timeval.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_INOUT(1) unsigned int
NOTHROW_NCX(LIBCCALL libc__setsystime)(struct tm *tp,
                                       unsigned int milliseconds) {
	struct timeval64 tv;
	tv.tv_sec  = libc_mktime64(tp);
	tv.tv_usec = milliseconds * 1000;
	return (unsigned int)libc_settimeofday64(&tv, NULL);
}
#endif /* !__KERNEL__ */
#undef _mkgmtime
#undef ctime_s
#undef gmtime_s
#undef localtime_s

DECL_END

#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_difftime32, libc_difftime);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(difftime, libc_difftime);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mktime32, libc_mktime);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(timelocal, libc_mktime);
DEFINE_PUBLIC_ALIAS(mktime, libc_mktime);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_ctime32, libc_ctime);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(ctime, libc_ctime);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_gmtime32, libc_gmtime);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(gmtime, libc_gmtime);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_localtime32, libc_localtime);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(localtime, libc_localtime);
DEFINE_PUBLIC_ALIAS(strftime, libc_strftime);
DEFINE_PUBLIC_ALIAS(asctime, libc_asctime);
DEFINE_PUBLIC_ALIAS(asctime_s, libc_asctime_s);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_difftime64, libc_difftime64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__difftime64, libc_difftime64);
DEFINE_PUBLIC_ALIAS(difftime64, libc_difftime64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mktime64, libc_mktime64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(timelocal64, libc_mktime64);
DEFINE_PUBLIC_ALIAS(mktime64, libc_mktime64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_ctime64, libc_ctime64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(ctime64, libc_ctime64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_gmtime64, libc_gmtime64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(gmtime64, libc_gmtime64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_localtime64, libc_localtime64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(localtime64, libc_localtime64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mkgmtime, libc_timegm);
DEFINE_PUBLIC_ALIAS(_mkgmtime32, libc_timegm);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(timegm, libc_timegm);
DEFINE_PUBLIC_ALIAS(dysize, libc_dysize);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mkgmtime64, libc_timegm64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(timegm64, libc_timegm64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_timespec32_get, libc_timespec_get);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(timespec_get, libc_timespec_get);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_timespec64_get, libc_timespec_get64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(timespec_get64, libc_timespec_get64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strftime_l, libc_strftime_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strftime_l, libc_strftime_l);
DEFINE_PUBLIC_ALIAS(strftime_l, libc_strftime_l);
DEFINE_PUBLIC_ALIAS(strptime, libc_strptime);
DEFINE_PUBLIC_ALIAS(strptime_l, libc_strptime_l);
DEFINE_PUBLIC_ALIAS(getdate_r, libc_getdate_r);
DEFINE_PUBLIC_ALIAS(__gmtime_r, libc_gmtime_r);
DEFINE_PUBLIC_ALIAS(gmtime_r, libc_gmtime_r);
DEFINE_PUBLIC_ALIAS(localtime_r, libc_localtime_r);
DEFINE_PUBLIC_ALIAS(ctime_r, libc_ctime_r);
DEFINE_PUBLIC_ALIAS(gmtime64_r, libc_gmtime64_r);
DEFINE_PUBLIC_ALIAS(localtime64_r, libc_localtime64_r);
DEFINE_PUBLIC_ALIAS(ctime64_r, libc_ctime64_r);
DEFINE_PUBLIC_ALIAS(asctime_r, libc_asctime_r);
DEFINE_PUBLIC_ALIAS(DOS$__daylight, libc___daylight);
DEFINE_PUBLIC_ALIAS(__p__daylight, libc___daylight);
DEFINE_PUBLIC_ALIAS(DOS$__timezone, libc___timezone);
DEFINE_PUBLIC_ALIAS(__p__timezone, libc___timezone);
DEFINE_PUBLIC_ALIAS(DOS$__tzname, libc___tzname);
DEFINE_PUBLIC_ALIAS(__p__tzname, libc___tzname);
DEFINE_PUBLIC_ALIAS(DOS$__dstbias, libc___dstbias);
DEFINE_PUBLIC_ALIAS(__p__dstbias, libc___dstbias);
DEFINE_PUBLIC_ALIAS(_get_daylight, libc__get_daylight);
DEFINE_PUBLIC_ALIAS(_get_timezone, libc__get_timezone);
DEFINE_PUBLIC_ALIAS(_get_dstbias, libc__get_dstbias);
DEFINE_PUBLIC_ALIAS(_gmtime32_s, libc__gmtime32_s);
DEFINE_PUBLIC_ALIAS(_gmtime64_s, libc__gmtime64_s);
DEFINE_PUBLIC_ALIAS(_localtime32_s, libc__localtime32_s);
DEFINE_PUBLIC_ALIAS(_localtime64_s, libc__localtime64_s);
DEFINE_PUBLIC_ALIAS(_ctime32_s, libc__ctime32_s);
DEFINE_PUBLIC_ALIAS(_ctime64_s, libc__ctime64_s);
DEFINE_PUBLIC_ALIAS(_strtime, libc__strtime);
DEFINE_PUBLIC_ALIAS(_strdate, libc__strdate);
DEFINE_PUBLIC_ALIAS(_strtime_s, libc__strtime_s);
DEFINE_PUBLIC_ALIAS(_strdate_s, libc__strdate_s);
DEFINE_PUBLIC_ALIAS(_getsystime, libc__getsystime);
DEFINE_PUBLIC_ALIAS(_setsystime, libc__setsystime);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_TIME_C */
