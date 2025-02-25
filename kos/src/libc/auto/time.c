/* HASH CRC-32:0x8e573519 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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
#include "../user/signal.h"
#include "../user/stdio.h"
#include "string.h"
#include "../user/sys.time.h"
#include "../user/sys.times.h"

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
#include <bits/os/timespec.h>
#include <bits/os/tms.h>
#include <hybrid/__overflow.h>
/* >> clock(3)
 * Time used by the program so  far (user time + system  time)
 * The `result / CLOCKS_PER_SECOND' is program time in seconds */
INTERN ATTR_SECTION(".text.crt.time") WUNUSED clock_t
NOTHROW_NCX(LIBCCALL libc_clock)(void) {
	clock_t result;
#ifdef __CLOCK_PROCESS_CPUTIME_ID
	struct timespec64 ts;
	if unlikely(libc_clock_gettime64(__CLOCK_PROCESS_CPUTIME_ID, &ts))
		return -1;
	__STATIC_IF((clock_t)-1 < 0) {
		if (__hybrid_overflow_scast(ts.tv_sec, &result))
			goto overflow;
		if (__hybrid_overflow_smul(result, __CLOCKS_PER_SEC, &result))
			goto overflow;
		if (__hybrid_overflow_sadd(result, ts.tv_nsec / (1000000000 / __CLOCKS_PER_SEC), &result))
			goto overflow;
	} __STATIC_ELSE((clock_t)-1 < 0) {
		if (__hybrid_overflow_ucast(ts.tv_sec, &result))
			goto overflow;
		if (__hybrid_overflow_umul(result, __CLOCKS_PER_SEC, &result))
			goto overflow;
		if (__hybrid_overflow_uadd(result, ts.tv_nsec / (1000000000 / __CLOCKS_PER_SEC), &result))
			goto overflow;
	}
#else /* __CLOCK_PROCESS_CPUTIME_ID */
	struct tms ts;
	if unlikely(libc_times(&ts))
		return -1;
	__STATIC_IF((clock_t)-1 < 0) {
		if (__hybrid_overflow_scast(ts.tms_utime, &result))
			goto overflow;
		if (__hybrid_overflow_sadd(result, ts.tms_stime, &result))
			goto overflow;
	} __STATIC_ELSE((clock_t)-1 < 0) {
		if (__hybrid_overflow_ucast(ts.tms_utime, &result))
			goto overflow;
		if (__hybrid_overflow_uadd(result, ts.tms_stime, &result))
			goto overflow;
	}
#endif /* !__CLOCK_PROCESS_CPUTIME_ID */
	return result;
overflow:
	return (clock_t)-1;
}
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_difftime)(time_t time1,
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
#include "../libc/tls-globals.h"
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_ctime)(time_t const *timer) {







	char (*const _p_ctime_buf)[26] = &libc_get_tlsglobals()->ltg_ctime_buf;
#define ctime_buf (*_p_ctime_buf)
	return libc_ctime_r(timer, ctime_buf);

}
#undef ctime_buf
#include "../libc/tls-globals.h"
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime)(time_t const *timer) {







	struct tm *const _p_tmbuf = &libc_get_tlsglobals()->ltg_tmbuf;
#define tmbuf (*_p_tmbuf)
	return libc_gmtime_r(timer, &tmbuf);

}
#undef tmbuf
#include "../libc/tls-globals.h"
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime)(time_t const *timer) {







	struct tm *const _p_tmbuf = &libc_get_tlsglobals()->ltg_tmbuf;
#define tmbuf (*_p_tmbuf)
	return libc_localtime_r(timer, &tmbuf);

}
#undef tmbuf
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
#include "../libc/tls-globals.h"
/* >> asctime(3)
 * Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is  the  representation  of  `tp'  in  this  format */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_asctime)(struct tm const *tp) {
	char (*const _p_ctime_buf)[26] = &libc_get_tlsglobals()->ltg_ctime_buf;
#define ctime_buf (*_p_ctime_buf)
	return libc_asctime_r(tp, ctime_buf);
}
#undef ctime_buf
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
DEFINE_INTERN_ALIAS_P(libc_difftime64,libc_difftime,ATTR_CONST WUNUSED,double,NOTHROW,LIBCCALL,(time64_t time1, time64_t time0),(time1,time0));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED double
NOTHROW(LIBCCALL libc_difftime64)(time64_t time1,
                                  time64_t time0) {



	return time1 > time0 ? time1 - time0 : time0 - time1;

}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_mktime64,libc_mktime,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
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
DEFINE_INTERN_ALIAS_P(libc_ctime64,libc_ctime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include "../libc/tls-globals.h"
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_ctime64)(time64_t const *timer) {




	char (*const _p_ctime_buf)[26] = &libc_get_tlsglobals()->ltg_ctime_buf;
#define ctime_buf (*_p_ctime_buf)
	return libc_ctime64_r(timer, ctime_buf);

}
#undef ctime_buf
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_gmtime64,libc_gmtime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include "../libc/tls-globals.h"
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime64)(time64_t const *timer) {




	struct tm *const _p_tmbuf = &libc_get_tlsglobals()->ltg_tmbuf;
#define tmbuf (*_p_tmbuf)
	return libc_gmtime64_r(timer, &tmbuf);

}
#undef tmbuf
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_localtime64,libc_localtime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include "../libc/tls-globals.h"
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime64)(time64_t const *timer) {




	struct tm *const _p_tmbuf = &libc_get_tlsglobals()->ltg_tmbuf;
#define tmbuf (*_p_tmbuf)
	return libc_localtime64_r(timer, &tmbuf);

}
#undef tmbuf
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
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	if ((time64_t)(time_t)result != result) {

		return (time_t)__libc_seterrno(EOVERFLOW);



	}
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */

	return (time_t)result;
}
#ifndef __isleap
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif /* !__isleap */
/* >> dysize(3)
 * Return the number of days in YEAR */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_dysize)(__STDC_INT_AS_UINT_T year) {
	return __isleap(year) ? 366 : 365;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_timegm64,libc_timegm,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
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
                                        int base) {
	if (base == __TIME_UTC) {
		if (libc_clock_gettime(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_timespec_get64,libc_timespec_get,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_timespec_get64)(struct timespec64 *ts,
                                          int base) {
	if (base == __TIME_UTC) {
		if (libc_clock_gettime64(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_timespec_getres)(struct timespec *ts,
                                           int base) {
	if (base == __TIME_UTC) {
		if (libc_clock_getres(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc_timespec_getres64,libc_timespec_getres,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_timespec_getres64)(struct timespec64 *ts,
                                             int base) {
	if (base == __TIME_UTC) {
		if (libc_clock_getres64(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#undef getdate_err
INTERN ATTR_SECTION(".bss.crt.time") int libc_getdate_err = 0;
DEFINE_PUBLIC_ALIAS(getdate_err, libc_getdate_err);
#define getdate_err GET_NOREL_GLOBAL(getdate_err)
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <bits/crt/tm.h>
#include "../libc/tls-globals.h"
/* >> getdate(3)
 * Parse the given string as a date specification and return a value
 * representing the value. The templates from the file identified by
 * the environment variable `$DATEMSK' are used. In case of an error
 * `getdate_err' is set */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) struct tm *
NOTHROW_NCX(LIBCCALL libc_getdate)(const char *string) {
	struct tm *const _p_tmbuf = &libc_get_tlsglobals()->ltg_tmbuf;
#define tmbuf (*_p_tmbuf)
	int error = libc_getdate_r(string, &tmbuf);
	if (error == 0)
		return &tmbuf;
	/* Caution: this part here is still thread-unsafe! */
	__LOCAL_getdate_err = error;
	return NULL;
}
#undef tmbuf
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
	tp->tm_year = (int)__daystoyears(t); /* TODO: This doesn't work for exact dates! (s.a. `deemon:time') */
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
DEFINE_INTERN_ALIAS_P(libc_gmtime64_r,libc_gmtime_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
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
	tp->tm_year = (int)__daystoyears(t); /* TODO: This doesn't work for exact dates! (s.a. `deemon:time') */
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
DEFINE_INTERN_ALIAS_P(libc_localtime64_r,libc_localtime_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
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
DEFINE_INTERN_ALIAS_P(libc_ctime64_r,libc_ctime_r,ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, char buf[26]),(timer,buf));
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
NOTHROW(LIBDCALL libc___daylight)(void) {
	return &__LOCAL_daylight;
}
#include <libc/template/timezone.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST ATTR_RETNONNULL WUNUSED long *
NOTHROW(LIBDCALL libc___timezone)(void) {
	return (long *)&__LOCAL_timezone;
}
#include <libc/template/tzname.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST ATTR_RETNONNULL WUNUSED char **
NOTHROW(LIBDCALL libc___tzname)(void) {
	return __LOCAL_tzname;
}
#include <libc/template/dstbias.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST ATTR_RETNONNULL WUNUSED __LONG32_TYPE__ *
NOTHROW(LIBDCALL libc___dstbias)(void) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.time") ATTR_OUT(1) ATTR_OUT_OPT(2) errno_t
NOTHROW_NCX(LIBDCALL libd__get_tzname)(size_t *result,
                                       char *buf,
                                       size_t bufsize,
                                       int index) {
	return libd_errno_kos2dos(libc__get_tzname(result, buf, bufsize, index));
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(1) ATTR_OUT_OPT(2) errno_t
NOTHROW_NCX(LIBCCALL libc__get_tzname)(size_t *result,
                                       char *buf,
                                       size_t bufsize,
                                       int index) {
	char *reqstr;
	size_t reqsiz;
	if (index < 0 || index > 1 || !result || (!buf && bufsize)) {

		return EINVAL;



	}

	libc_tzset(); /* Update state of `tzname' */

	reqstr  = __LOCAL_tzname[(unsigned int)index];
	reqsiz  = (libc_strlen(reqstr) + 1) * sizeof(char);
	*result = reqsiz;
	if (bufsize > reqsiz)
		bufsize = reqsiz;
	libc_memcpy(buf, reqstr, bufsize);
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
DEFINE_INTERN_ALIAS_P(libc__gmtime64_s,libc__gmtime32_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(struct tm *__restrict tp, time64_t const *__restrict timer),(tp,timer));
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
DEFINE_INTERN_ALIAS_P(libc__localtime64_s,libc__localtime32_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(struct tm *__restrict tp, time64_t const *__restrict timer),(tp,timer));
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
DEFINE_INTERN_ALIAS_P(libc__ctime64_s,libc__ctime32_s,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char buf[26], size_t bufsize, time64_t const *__restrict timer),(buf,bufsize,timer));
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__strtime_s)(char *buf,
                                      size_t bufsize) {
	return libd_errno_kos2dos(libc__strtime_s(buf, bufsize));
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__strtime_s)(char *buf,
                                      size_t bufsize) {
	if unlikely(bufsize < 9) {

		return ERANGE;



	}

	libc__strtime(buf);




	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__strdate_s)(char *buf,
                                      size_t bufsize) {
	return libd_errno_kos2dos(libc__strdate_s(buf, bufsize));
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__strdate_s)(char *buf,
                                      size_t bufsize) {
	if unlikely(bufsize < 9) {

		return ERANGE;



	}

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
#ifndef __KERNEL__
#include <bits/os/sigset.h>
#include <bits/os/timespec.h>
INTERN ATTR_SECTION(".text.crt.compat.glibc") ATTR_IN(1) ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc___nanosleep_nocancel)(struct timespec const *requested_time,
                                                struct timespec *remaining) {
	fd_t result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)libc_sigemptyset(&nss);
	(void)libc_sigaddset(&nss, __SIGRPC);
	result = libc_sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = libc_nanosleep(requested_time, remaining);
		(void)libc_sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P(libc___nanosleep64_nocancel,libc___nanosleep_nocancel,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 const *requested_time, struct timespec64 *remaining),(requested_time,remaining));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <bits/os/sigset.h>
#include <bits/os/timespec.h>
INTERN ATTR_SECTION(".text.crt.compat.glibc") ATTR_IN(1) ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc___nanosleep64_nocancel)(struct timespec64 const *requested_time,
                                                  struct timespec64 *remaining) {
	fd_t result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)libc_sigemptyset(&nss);
	(void)libc_sigaddset(&nss, __SIGRPC);
	result = libc_sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = libc_nanosleep64(requested_time, remaining);
		(void)libc_sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(clock,libc_clock,WUNUSED,clock_t,NOTHROW_NCX,LIBCCALL,(void),());
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_difftime32,libc_difftime,ATTR_CONST WUNUSED,double,NOTHROW,LIBCCALL,(time_t time1, time_t time0),(time1,time0));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(difftime,libc_difftime,ATTR_CONST WUNUSED,double,NOTHROW,LIBCCALL,(time_t time1, time_t time0),(time1,time0));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_mktime32,libc_mktime,ATTR_PURE WUNUSED ATTR_INOUT(1),time_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(timelocal,libc_mktime,ATTR_PURE WUNUSED ATTR_INOUT(1),time_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
DEFINE_PUBLIC_ALIAS_P(mktime,libc_mktime,ATTR_PURE WUNUSED ATTR_INOUT(1),time_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_ctime32,libc_ctime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(time_t const *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(ctime,libc_ctime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(time_t const *timer),(timer));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_gmtime32,libc_gmtime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(gmtime,libc_gmtime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *timer),(timer));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_localtime32,libc_localtime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(localtime,libc_localtime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *timer),(timer));
DEFINE_PUBLIC_ALIAS_P(strftime,libc_strftime,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp),(buf,bufsize,format,tp));
DEFINE_PUBLIC_ALIAS_P(asctime,libc_asctime,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(struct tm const *tp),(tp));
DEFINE_PUBLIC_ALIAS_P(asctime_s,libc_asctime_s,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t buflen, struct tm const *__restrict tp),(buf,buflen,tp));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_difftime64,libc_difftime64,ATTR_CONST WUNUSED,double,NOTHROW,LIBCCALL,(time64_t time1, time64_t time0),(time1,time0));
#endif /* __LIBCCALL_IS_LIBDCALL */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__difftime64,libc_difftime64,ATTR_CONST WUNUSED,double,NOTHROW,LIBCCALL,(time64_t time1, time64_t time0),(time1,time0));
DEFINE_PUBLIC_ALIAS_P(difftime64,libc_difftime64,ATTR_CONST WUNUSED,double,NOTHROW,LIBCCALL,(time64_t time1, time64_t time0),(time1,time0));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(timelocal64,libc_mktime64,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
DEFINE_PUBLIC_ALIAS_P(__mktime64,libc_mktime64,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_mktime64,libc_mktime64,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __LIBCCALL_IS_LIBDCALL */
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(mktime64,libc_mktime64,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__ctime64,libc_ctime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_ctime64,libc_ctime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(ctime64,libc_ctime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__gmtime64,libc_gmtime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_gmtime64,libc_gmtime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(gmtime64,libc_gmtime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_localtime64,libc_localtime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__localtime64,libc_localtime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
DEFINE_PUBLIC_ALIAS_P(localtime64,libc_localtime64,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *timer),(timer));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_mkgmtime,libc_timegm,ATTR_PURE WUNUSED ATTR_INOUT(1),time_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
DEFINE_PUBLIC_ALIAS_P(_mkgmtime32,libc_timegm,ATTR_PURE WUNUSED ATTR_INOUT(1),time_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(timegm,libc_timegm,ATTR_PURE WUNUSED ATTR_INOUT(1),time_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
DEFINE_PUBLIC_ALIAS_P(dysize,libc_dysize,ATTR_CONST WUNUSED,int,NOTHROW,LIBCCALL,(__STDC_INT_AS_UINT_T year),(year));
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__timegm64,libc_timegm64,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_mkgmtime64,libc_timegm64,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __LIBCCALL_IS_LIBDCALL */
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(timegm64,libc_timegm64,ATTR_PURE WUNUSED ATTR_INOUT(1),time64_t,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_timespec32_get,libc_timespec_get,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec *ts, int base),(ts,base));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(timespec_get,libc_timespec_get,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec *ts, int base),(ts,base));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_timespec64_get,libc_timespec_get64,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
#endif /* __LIBCCALL_IS_LIBDCALL */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__timespec_get64,libc_timespec_get64,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
DEFINE_PUBLIC_ALIAS_P(timespec_get64,libc_timespec_get64,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_timespec32_get,libc_timespec_getres,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec *ts, int base),(ts,base));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(timespec_getres,libc_timespec_getres,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec *ts, int base),(ts,base));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_timespec64_get,libc_timespec_getres64,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
#endif /* __LIBCCALL_IS_LIBDCALL */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__timespec_getres64,libc_timespec_getres64,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
DEFINE_PUBLIC_ALIAS_P(timespec_getres64,libc_timespec_getres64,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 *ts, int base),(ts,base));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS_P(getdate,libc_getdate,ATTR_IN(1),struct tm *,NOTHROW_NCX,LIBCCALL,(const char *string),(string));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strftime_l,libc_strftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,bufsize,format,tp,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strftime_l,libc_strftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,bufsize,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(strftime_l,libc_strftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,bufsize,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(strptime,libc_strptime,ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3),char *,NOTHROW_NCX,LIBCCALL,(char const *__restrict s, char const *__restrict format, struct tm *__restrict tp),(s,format,tp));
DEFINE_PUBLIC_ALIAS_P(strptime_l,libc_strptime_l,ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3),char *,NOTHROW_NCX,LIBCCALL,(char const *__restrict s, char const *__restrict format, struct tm *__restrict tp, locale_t locale),(s,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(getdate_r,libc_getdate_r,ATTR_IN(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(char const *__restrict string, struct tm *__restrict resbufp),(string,resbufp));
DEFINE_PUBLIC_ALIAS_P(__gmtime_r,libc_gmtime_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
DEFINE_PUBLIC_ALIAS_P(gmtime_r,libc_gmtime_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
DEFINE_PUBLIC_ALIAS_P(__localtime_r,libc_localtime_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
DEFINE_PUBLIC_ALIAS_P(localtime_r,libc_localtime_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
DEFINE_PUBLIC_ALIAS_P(ctime_r,libc_ctime_r,ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(time_t const *__restrict timer, char buf[26]),(timer,buf));
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__gmtime64_r,libc_gmtime64_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
DEFINE_PUBLIC_ALIAS_P(gmtime64_r,libc_gmtime64_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__localtime64_r,libc_localtime64_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
DEFINE_PUBLIC_ALIAS_P(localtime64_r,libc_localtime64_r,ATTR_IN(1) ATTR_OUT(2),struct tm *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, struct tm *__restrict tp),(timer,tp));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__ctime64_r,libc_ctime64_r,ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, char buf[26]),(timer,buf));
DEFINE_PUBLIC_ALIAS_P(ctime64_r,libc_ctime64_r,ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(time64_t const *__restrict timer, char buf[26]),(timer,buf));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS_P(__asctime_r,libc_asctime_r,ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(struct tm const *__restrict tp, char buf[26]),(tp,buf));
DEFINE_PUBLIC_ALIAS_P(asctime_r,libc_asctime_r,ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(struct tm const *__restrict tp, char buf[26]),(tp,buf));
DEFINE_PUBLIC_ALIAS_P(DOS$__daylight,libc___daylight,ATTR_CONST ATTR_RETNONNULL WUNUSED,int *,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__daylight,libc___daylight,ATTR_CONST ATTR_RETNONNULL WUNUSED,int *,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__timezone,libc___timezone,ATTR_CONST ATTR_RETNONNULL WUNUSED,long *,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__timezone,libc___timezone,ATTR_CONST ATTR_RETNONNULL WUNUSED,long *,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__tzname,libc___tzname,ATTR_CONST ATTR_RETNONNULL WUNUSED,char **,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__tzname,libc___tzname,ATTR_CONST ATTR_RETNONNULL WUNUSED,char **,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__dstbias,libc___dstbias,ATTR_CONST ATTR_RETNONNULL WUNUSED,__LONG32_TYPE__ *,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__dstbias,libc___dstbias,ATTR_CONST ATTR_RETNONNULL WUNUSED,__LONG32_TYPE__ *,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_get_daylight,libc__get_daylight,,errno_t,NOTHROW_NCX,LIBCCALL,(int *p_result),(p_result));
DEFINE_PUBLIC_ALIAS_P(_get_timezone,libc__get_timezone,,errno_t,NOTHROW_NCX,LIBCCALL,(long *p_seconds),(p_seconds));
DEFINE_PUBLIC_ALIAS_P(_get_dstbias,libc__get_dstbias,,errno_t,NOTHROW_NCX,LIBCCALL,(__LONG32_TYPE__ *p_result),(p_result));
DEFINE_PUBLIC_ALIAS_P(DOS$_get_tzname,libd__get_tzname,ATTR_OUT(1) ATTR_OUT_OPT(2),errno_t,NOTHROW_NCX,LIBDCALL,(size_t *result, char *buf, size_t bufsize, int index),(result,buf,bufsize,index));
DEFINE_PUBLIC_ALIAS_P(_get_tzname,libc__get_tzname,ATTR_OUT(1) ATTR_OUT_OPT(2),errno_t,NOTHROW_NCX,LIBCCALL,(size_t *result, char *buf, size_t bufsize, int index),(result,buf,bufsize,index));
DEFINE_PUBLIC_ALIAS_P(_gmtime32_s,libc__gmtime32_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(struct tm *__restrict tp, time32_t const *__restrict timer),(tp,timer));
DEFINE_PUBLIC_ALIAS_P(_gmtime64_s,libc__gmtime64_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(struct tm *__restrict tp, time64_t const *__restrict timer),(tp,timer));
DEFINE_PUBLIC_ALIAS_P(_localtime32_s,libc__localtime32_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(struct tm *__restrict tp, time32_t const *__restrict timer),(tp,timer));
DEFINE_PUBLIC_ALIAS_P(_localtime64_s,libc__localtime64_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(struct tm *__restrict tp, time64_t const *__restrict timer),(tp,timer));
DEFINE_PUBLIC_ALIAS_P(_ctime32_s,libc__ctime32_s,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char buf[26], size_t bufsize, time32_t const *__restrict timer),(buf,bufsize,timer));
DEFINE_PUBLIC_ALIAS_P(_ctime64_s,libc__ctime64_s,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char buf[26], size_t bufsize, time64_t const *__restrict timer),(buf,bufsize,timer));
DEFINE_PUBLIC_ALIAS_P(_strtime,libc__strtime,ATTR_OUT(1),char *,NOTHROW_NCX,LIBCCALL,(char buf[9]),(buf));
DEFINE_PUBLIC_ALIAS_P(_strdate,libc__strdate,ATTR_OUT(1),char *,NOTHROW_NCX,LIBCCALL,(char buf[9]),(buf));
DEFINE_PUBLIC_ALIAS_P(DOS$_strtime_s,libd__strtime_s,ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBDCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(_strtime_s,libc__strtime_s,ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$_strdate_s,libd__strdate_s,ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBDCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(_strdate_s,libc__strdate_s,ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(_getsystime,libc__getsystime,ATTR_OUT(1),unsigned int,NOTHROW_NCX,LIBCCALL,(struct tm *tp),(tp));
DEFINE_PUBLIC_ALIAS_P(_setsystime,libc__setsystime,ATTR_INOUT(1),unsigned int,NOTHROW_NCX,LIBCCALL,(struct tm *tp, unsigned int milliseconds),(tp,milliseconds));
DEFINE_PUBLIC_ALIAS_P(__nanosleep_nocancel,libc___nanosleep_nocancel,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_NCX,LIBCCALL,(struct timespec const *requested_time, struct timespec *remaining),(requested_time,remaining));
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__nanosleep64_nocancel,libc___nanosleep64_nocancel,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_NCX,LIBCCALL,(struct timespec64 const *requested_time, struct timespec64 *remaining),(requested_time,remaining));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_TIME_C */
