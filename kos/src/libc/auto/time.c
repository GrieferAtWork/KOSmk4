/* HASH CRC-32:0x46574321 */
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
#ifndef GUARD_LIBC_AUTO_TIME_C
#define GUARD_LIBC_AUTO_TIME_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/time.h"
#include <stdio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Return the difference between TIME1 and TIME0 */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_difftime)(time_t time1,
                                    time_t time0) {
#ifdef __BUILDING_LIBC
	return time1 > time0 ? time1 - time0 : time0 - time1;
#elif defined(__CRT_HAVE_difftime) || defined(__CRT_HAVE__difftime32)
	return difftime32((time32_t)time1, (time32_t)time0);
#else /* ... */
	return difftime64((time32_t)time1, (time32_t)time0);


#endif /* !... */
}
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif
/* Return the `time_t' representation of TP and normalize TP */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED NONNULL((1)) time_t
NOTHROW_NCX(LIBCCALL libc_mktime)(__STRUCT_TM __KOS_FIXED_CONST *tp) {
#ifdef __BUILDING_LIBC
	__TM_TYPE(time) result;
	result = __yearstodays(tp->tm_year) - __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	result += tp->tm_yday;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->tm_hour*60*60;
	result += tp->tm_min*60;
	result += tp->tm_sec;
	return result;
#else /* __BUILDING_LIBC */
	return (time_t)mktime64(tp);











#endif /* !__BUILDING_LIBC */
}
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32))
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_ctime && !__CRT_HAVE__ctime32) */
/* Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_ctime)(time_t const *timer) {
#ifdef __BUILDING_LIBC
	return ctime_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
#else /* __BUILDING_LIBC */
	time64_t tm64 = (time64_t)*timer;
	return ctime64(&tm64);





#endif /* !__BUILDING_LIBC */
}
#ifdef __BUILDING_LIBC
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) __STRUCT_TM __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC */
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *
NOTHROW_NCX(LIBCCALL libc_gmtime)(time_t const *timer) {
#ifdef __BUILDING_LIBC
	return gmtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#else /* __BUILDING_LIBC */
	time64_t tm64 = (time64_t)*timer;
	return gmtime64(&tm64);





#endif /* !__BUILDING_LIBC */
}
#ifdef __BUILDING_LIBC
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) __STRUCT_TM __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC */
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *
NOTHROW_NCX(LIBCCALL libc_localtime)(time_t const *timer) {
#ifdef __BUILDING_LIBC
	return localtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#else /* __BUILDING_LIBC */
	time64_t tm64 = (time64_t)*timer;
	return localtime64(&tm64);





#endif /* !__BUILDING_LIBC */
}
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBCCALL libc_strftime)(char *__restrict buf,
                                    size_t bufsize,
                                    char const *__restrict format,
                                    __STRUCT_TM const *__restrict tp) {
#ifdef __BUILDING_LIBC
	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return 0;
#elif defined(__CRT_HAVE_strftime_l) || defined(__CRT_HAVE__strftime_l) || defined(__CRT_HAVE___strftime_l)
	return crt_strftime_l(buf, bufsize, format, tp, NULL);
#else /* ... */
	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return 0;
#endif /* !... */
}
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
__NAMESPACE_LOCAL_END
#endif
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_asctime)(struct tm const *tp) {
	return asctime_r(tp, __NAMESPACE_LOCAL_SYM __ctime_buf);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_asctime_s)(char *__restrict buf,
                                     size_t buflen,
                                     struct tm const *__restrict tp) {
	if (buflen < 26)
		return __ERANGE;
	asctime_r(tp, buf);
	return 0;
}
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_difftime64, libc_difftime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* Return the difference between TIME1 and TIME0 */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_difftime64)(time64_t time1,
                                      time64_t time0) {
#ifdef __BUILDING_LIBC
	return time1 > time0 ? time1 - time0 : time0 - time1;
#elif defined(__CRT_HAVE_difftime) || defined(__CRT_HAVE__difftime32)
	return difftime32((time32_t)time1, (time32_t)time0);
#else /* ... */
	return time1 > time0 ? time1 - time0 : time0 - time1;
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mktime64, libc_mktime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif
/* Return the `time_t' representation of TP and normalize TP */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED NONNULL((1)) time64_t
NOTHROW_NCX(LIBCCALL libc_mktime64)(__STRUCT_TM __KOS_FIXED_CONST *tp) {
#ifdef __BUILDING_LIBC
	time64_t result;
	result = __yearstodays(tp->tm_year) - __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	result += tp->tm_yday;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->tm_hour*60*60;
	result += tp->tm_min*60;
	result += tp->tm_sec;
	return result;
#elif defined(__CRT_HAVE_mktime) || defined(__CRT_HAVE__mktime32) || defined(__CRT_HAVE_timelocal)
	return (time64_t)mktime32(tp);
#else /* ... */
	time64_t result;
	result = __yearstodays(tp->tm_year) - __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	result += tp->tm_yday;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->tm_hour*60*60;
	result += tp->tm_min*60;
	result += tp->tm_sec;
	return result;
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ctime64, libc_ctime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32))
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_ctime && !__CRT_HAVE__ctime32) */
/* Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_ctime64)(time64_t const *timer) {
#ifdef __BUILDING_LIBC
	return ctime64_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
#elif defined(__CRT_HAVE_ctime) || defined(__CRT_HAVE__ctime32)
	time32_t tm32 = (time32_t)*timer;
	return ctime32(&tm32);
#else /* ... */
	return ctime64_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gmtime64, libc_gmtime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_gmtime) && !defined(__CRT_HAVE__gmtime32))
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) __STRUCT_TM __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_gmtime && !__CRT_HAVE__gmtime32) */
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_gmtime64)(time64_t const *timer) {
#ifdef __BUILDING_LIBC
	return gmtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#elif defined(__CRT_HAVE_gmtime) || defined(__CRT_HAVE__gmtime32)
	time32_t tm32 = (time32_t)*timer;
	return gmtime32(&tm32);
#else /* ... */
	return gmtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_localtime64, libc_localtime);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32))
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) __STRUCT_TM __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC || (!__CRT_HAVE_localtime && !__CRT_HAVE__localtime32) */
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTERN ATTR_SECTION(".text.crt.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_localtime64)(time64_t const *timer) {
#ifdef __BUILDING_LIBC
	return localtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#elif defined(__CRT_HAVE_localtime) || defined(__CRT_HAVE__localtime32)
	time32_t tm32 = (time32_t)*timer;
	return localtime32(&tm32);
#else /* ... */
	return localtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED NONNULL((1)) time_t
NOTHROW_NCX(LIBCCALL libc_timegm)(__STRUCT_TM *tp) {
#ifdef __BUILDING_LIBC
	/* TODO: Timezones */
	return mktime(tp);
#else /* __BUILDING_LIBC */
	return (time_t)timegm64(tp);



#endif /* !__BUILDING_LIBC */
}
#ifndef __isleap
#define __isleap(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#endif
/* Return the number of days in YEAR */
INTERN ATTR_SECTION(".text.crt.time") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_dysize)(__STDC_INT_AS_UINT_T year) {
	return __isleap(year) ? 366 : 365;
}
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timegm64, libc_timegm);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTERN ATTR_SECTION(".text.crt.time") ATTR_PURE WUNUSED NONNULL((1)) time64_t
NOTHROW_NCX(LIBCCALL libc_timegm64)(__STRUCT_TM *tp) {
#ifdef __BUILDING_LIBC
	/* TODO: Timezones */
	return mktime64(tp);
#elif defined(__CRT_HAVE_timegm)
	return (time64_t)timegm32(tp);
#else /* ... */
	/* TODO: Timezones */
	return mktime64(tp);
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBCCALL libc_strftime_l)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      __STRUCT_TM const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return strftime(buf, bufsize, format, tp);
}
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2, 3)) char *
NOTHROW_NCX(LIBCCALL libc_strptime)(char const *__restrict s,
                                    char const *__restrict format,
                                    __STRUCT_TM *__restrict tp) {
#ifdef __BUILDING_LIBC
	/* TODO */
	(void)s;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return NULL;
#elif defined(__CRT_HAVE_strptime_l)
	return crt_strptime_l(s, format, tp, NULL);
#else /* ... */
	/* TODO */
	(void)s;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return NULL;
#endif /* !... */
}
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2, 3)) char *
NOTHROW_NCX(LIBCCALL libc_strptime_l)(char const *__restrict s,
                                      char const *__restrict format,
                                      __STRUCT_TM *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return strptime(s, format, tp);
}
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_getdate_r)(char const *__restrict string,
                                     __STRUCT_TM *__restrict resbufp) {
	/* TODO */
	(void)string;
	(void)resbufp;
	COMPILER_IMPURE();
	return 0;
}
#ifdef __BUILDING_LIBC
#ifndef __isleap
#define __isleap(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#endif
#ifndef __daystoyears
#define __daystoyears(n_days)  ((400*((n_days)+1))/146097)
#endif
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif
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
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_gmtime_r)(time_t const *__restrict timer,
                                    __STRUCT_TM *__restrict tp) {
#ifdef __BUILDING_LIBC
	time_t t; int i;
	u16 const *monthvec;
	t = *timer;
	tp->tm_sec  = (int)(t % 60);
	tp->tm_min  = (int)((t / 60) % 60);
	tp->tm_hour = (int)((t / (60 * 60)) % 24);
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
			//That means the previous Sunday must be before the 1st.
			tp->tm_isdst = previousSunday <= 0;
		}
	}
	tp->tm_year -= 1900;
	return tp;
#elif defined(__CRT_HAVE__gmtime32_s) || defined(__CRT_HAVE__gmtime64_s)
	return dos_gmtime_s(tp, timer) ? NULL : tp;
#elif defined(__USE_TIME_BITS64)
	return gmtime64_r(timer, tp);
#else /* ... */
	time64_t tm64 = (time64_t)*timer;
	return gmtime64_r(&tm64, tp);
#endif /* !... */
}
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_localtime_r)(time_t const *__restrict timer,
                                       __STRUCT_TM *__restrict tp) {
#ifdef __BUILDING_LIBC
	/* XXX: Timezone support? */
	return gmtime_r(timer, tp);
#elif defined(__CRT_HAVE__localtime32_s) || defined(__CRT_HAVE__localtime64_s)
	return dos_localtime_s(tp, timer) ? NULL : tp;
#elif defined(__USE_TIME_BITS64)
	return localtime64_r(timer, tp);
#else /* ... */
	time64_t tm64 = (time64_t)*timer;
	return localtime64_r(&tm64, tp);
#endif /* !... */
}
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_ctime_r)(time_t const *__restrict timer,
                                   char buf[26]) {
#ifdef __BUILDING_LIBC
	struct tm ltm;
	return asctime_r(localtime_r(timer, &ltm), buf);
#elif defined(__CRT_HAVE__ctime32_s) || defined(__CRT_HAVE__ctime64_s)
	return dos_ctime_s(buf, 26, timer) ? NULL : __buf;
#else /* ... */
	struct tm ltm;
	return asctime_r(localtime_r(timer, &ltm), buf);
#endif /* !... */
}
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gmtime64_r, libc_gmtime_r);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE__gmtime64_s) && !defined(__CRT_HAVE__gmtime32_s))
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

#endif /* __BUILDING_LIBC || (!__CRT_HAVE__gmtime64_s && !__CRT_HAVE__gmtime32_s) */
#ifndef __isleap
#define __isleap(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#endif
#ifndef __daystoyears
#define __daystoyears(n_days)  ((400*((n_days)+1))/146097)
#endif
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_gmtime64_r)(time64_t const *__restrict timer,
                                      __STRUCT_TM *__restrict tp) {
#ifdef __BUILDING_LIBC
	time_t t; int i;
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
			//That means the previous Sunday must be before the 1st.
			tp->tm_isdst = previousSunday <= 0;
		}
	}
	tp->tm_year -= 1900;
	return tp;
#elif defined(__CRT_HAVE__gmtime64_s) || defined(__CRT_HAVE__gmtime32_s)
	return dos_gmtime64_s(tp, timer) ? NULL : tp;
#else /* ... */
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
			//That means the previous Sunday must be before the 1st.
			tp->tm_isdst = previousSunday <= 0;
		}
	}
	tp->tm_year -= 1900;
	return tp;
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_localtime64_r, libc_localtime_r);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_localtime64_r)(time64_t const *__restrict timer,
                                         __STRUCT_TM *__restrict tp) {
#ifdef __BUILDING_LIBC
	/* XXX: Timezone support? */
	return gmtime64_r(timer, tp);
#elif defined(__CRT_HAVE__localtime64_s) || defined(__CRT_HAVE__localtime32_s)
	return dos_localtime64_s(tp, timer) ? NULL : tp;
#else /* ... */
	/* XXX: Timezone support? */
	return gmtime64_r(timer, tp);
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ctime64_r, libc_ctime_r);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_ctime64_r)(time64_t const *__restrict timer,
                                     char buf[26]) {
#ifdef __BUILDING_LIBC
	struct tm ltm;
	return asctime_r(localtime64_r(timer, &ltm), buf);
#elif defined(__CRT_HAVE__ctime64_s) || defined(__CRT_HAVE__ctime32_s)
	return dos_ctime64_s(buf, 26, timer) ? NULL : __buf;
#else /* ... */
	struct tm ltm;
	return asctime_r(localtime64_r(timer, &ltm), buf);
#endif /* !... */
}
#endif /* !(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) */
#if defined(__BUILDING_LIBC) || !defined(__CRT_HAVE_asctime_s)
#ifndef __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
#define __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__abbr_wday_names) char const __abbr_wday_names[7][4] =
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
__NAMESPACE_LOCAL_END
#endif
#ifndef __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
#define __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__abbr_month_names) char const __abbr_month_names[12][4] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun",  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
__NAMESPACE_LOCAL_END
#endif
#endif /* __BUILDING_LIBC || !__CRT_HAVE_asctime_s */
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_asctime_r)(__STRUCT_TM const *__restrict tp,
                                     char buf[26]) {
#ifdef __BUILDING_LIBC
	sprintf(buf,
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
#elif defined(__CRT_HAVE_asctime_s)
	return crt_asctime_s(buf, 26, tp) ? NULL : buf;
#else /* ... */
	sprintf(buf,
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
#endif /* !... */
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(difftime, libc_difftime);
DEFINE_PUBLIC_ALIAS(mktime, libc_mktime);
DEFINE_PUBLIC_ALIAS(ctime, libc_ctime);
DEFINE_PUBLIC_ALIAS(gmtime, libc_gmtime);
DEFINE_PUBLIC_ALIAS(localtime, libc_localtime);
DEFINE_PUBLIC_ALIAS(strftime, libc_strftime);
DEFINE_PUBLIC_ALIAS(asctime, libc_asctime);
DEFINE_PUBLIC_ALIAS(asctime_s, libc_asctime_s);
DEFINE_PUBLIC_ALIAS(_difftime64, libc_difftime64);
DEFINE_PUBLIC_ALIAS(__difftime64, libc_difftime64);
DEFINE_PUBLIC_ALIAS(difftime64, libc_difftime64);
DEFINE_PUBLIC_ALIAS(_mktime64, libc_mktime64);
DEFINE_PUBLIC_ALIAS(timelocal64, libc_mktime64);
DEFINE_PUBLIC_ALIAS(mktime64, libc_mktime64);
DEFINE_PUBLIC_ALIAS(_ctime64, libc_ctime64);
DEFINE_PUBLIC_ALIAS(ctime64, libc_ctime64);
DEFINE_PUBLIC_ALIAS(_gmtime64, libc_gmtime64);
DEFINE_PUBLIC_ALIAS(gmtime64, libc_gmtime64);
DEFINE_PUBLIC_ALIAS(_localtime64, libc_localtime64);
DEFINE_PUBLIC_ALIAS(localtime64, libc_localtime64);
DEFINE_PUBLIC_ALIAS(timegm, libc_timegm);
DEFINE_PUBLIC_ALIAS(dysize, libc_dysize);
DEFINE_PUBLIC_ALIAS(timegm64, libc_timegm64);
DEFINE_PUBLIC_ALIAS(_strftime_l, libc_strftime_l);
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
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_TIME_C */
