/* HASH CRC-32:0xa38ce3cc */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_TIME_C
#define GUARD_LIBC_AUTO_DOSABI_TIME_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/time.h"

DECL_BEGIN

/* Return the current time and put it in *TIMER if TIMER is not NULL */
INTERN ATTR_SECTION(".text.crt.dos.time") time_t
NOTHROW_NCX(LIBDCALL libd_time)(time_t *timer) {
	return libc_time(timer);
}
/* Return the difference between TIME1 and TIME0 */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBDCALL libd_difftime)(time_t time1,
                                    time_t time0) {
	return libc_difftime(time1, time0);
}
/* Return the `time_t' representation of TP and normalize TP */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_PURE WUNUSED NONNULL((1)) time_t
NOTHROW_NCX(LIBDCALL libd_mktime)(__STRUCT_TM __KOS_FIXED_CONST *tp) {
	return libc_mktime(tp);
}
/* Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_ctime)(time_t const *timer) {
	return libc_ctime(timer);
}
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *
NOTHROW_NCX(LIBDCALL libd_gmtime)(time_t const *timer) {
	return libc_gmtime(timer);
}
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *
NOTHROW_NCX(LIBDCALL libd_localtime)(time_t const *timer) {
	return libc_localtime(timer);
}
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_strftime)(char *__restrict buf,
                                    size_t bufsize,
                                    char const *__restrict format,
                                    __STRUCT_TM const *__restrict tp) {
	return libc_strftime(buf, bufsize, format, tp);
}
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_asctime)(struct tm const *tp) {
	return libc_asctime(tp);
}
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd_asctime_s)(char *__restrict buf,
                                     size_t buflen,
                                     struct tm const *__restrict tp) {
	return libc_asctime_s(buf, buflen, tp);
}
/* Return the current time and put it in *TIMER if TIMER is not NULL */
INTERN ATTR_SECTION(".text.crt.dos.time") time64_t
NOTHROW_NCX(LIBDCALL libd_time64)(time64_t *timer) {
	return libc_time64(timer);
}
/* Return the difference between TIME1 and TIME0 */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBDCALL libd_difftime64)(time64_t time1,
                                      time64_t time0) {
	return libc_difftime64(time1, time0);
}
/* Return the `time_t' representation of TP and normalize TP */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_PURE WUNUSED NONNULL((1)) time64_t
NOTHROW_NCX(LIBDCALL libd_mktime64)(__STRUCT_TM __KOS_FIXED_CONST *tp) {
	return libc_mktime64(tp);
}
/* Equivalent to `asctime(localtime(timer))' */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_ctime64)(time64_t const *timer) {
	return libc_ctime64(timer);
}
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *
NOTHROW_NCX(LIBDCALL libd_gmtime64)(time64_t const *timer) {
	return libc_gmtime64(timer);
}
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *
NOTHROW_NCX(LIBDCALL libd_localtime64)(time64_t const *timer) {
	return libc_localtime64(timer);
}
/* Set the system time to *WHEN. This call is restricted to the superuser */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_stime)(time_t const *when) {
	return libc_stime(when);
}
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_PURE WUNUSED NONNULL((1)) time_t
NOTHROW_NCX(LIBDCALL libd_timegm)(__STRUCT_TM *tp) {
	return libc_timegm(tp);
}
/* Return the number of days in YEAR */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd_dysize)(__STDC_INT_AS_UINT_T year) {
	return libc_dysize(year);
}
/* Set the system time to *WHEN. This call is restricted to the superuser */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_stime64)(time64_t const *when) {
	return libc_stime64(when);
}
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTERN ATTR_SECTION(".text.crt.dos.time") ATTR_PURE WUNUSED NONNULL((1)) time64_t
NOTHROW_NCX(LIBDCALL libd_timegm64)(__STRUCT_TM *tp) {
	return libc_timegm64(tp);
}
/* Pause execution for a number of nanoseconds */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_nanosleep)(struct timespec const *requested_time,
                                     struct timespec *remaining) {
	return libc_nanosleep(requested_time, remaining);
}
/* Get resolution of clock CLOCK_ID */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_clock_getres)(clockid_t clock_id,
                                        struct timespec *res) {
	return libc_clock_getres(clock_id, res);
}
/* Get current value of clock CLOCK_ID and store it in TP */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_clock_gettime)(clockid_t clock_id,
                                         struct timespec *tp) {
	return libc_clock_gettime(clock_id, tp);
}
/* Set clock CLOCK_ID to value TP */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_clock_settime)(clockid_t clock_id,
                                         struct timespec const *tp) {
	return libc_clock_settime(clock_id, tp);
}
/* Create new per-process timer using CLOCK_ID */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_timer_create)(clockid_t clock_id,
                                        struct sigevent *__restrict evp,
                                        timer_t *__restrict timerid) {
	return libc_timer_create(clock_id, evp, timerid);
}
/* Delete timer TIMERID */
INTERN ATTR_SECTION(".text.crt.dos.timer") int
NOTHROW_NCX(LIBDCALL libd_timer_delete)(timer_t timerid) {
	return libc_timer_delete(timerid);
}
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_timer_settime)(timer_t timerid,
                                         __STDC_INT_AS_UINT_T flags,
                                         struct itimerspec const *__restrict value,
                                         struct itimerspec *__restrict ovalue) {
	return libc_timer_settime(timerid, flags, value, ovalue);
}
/* Get current value of timer TIMERID and store it in VALUE */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_timer_gettime)(timer_t timerid,
                                         struct itimerspec *value) {
	return libc_timer_gettime(timerid, value);
}
/* Get expiration overrun for timer TIMERID */
INTERN ATTR_SECTION(".text.crt.dos.timer") int
NOTHROW_NCX(LIBDCALL libd_timer_getoverrun)(timer_t timerid) {
	return libc_timer_getoverrun(timerid);
}
/* High-resolution sleep with the specified clock */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((3)) int
NOTHROW_RPC(LIBDCALL libd_clock_nanosleep)(clockid_t clock_id,
                                           __STDC_INT_AS_UINT_T flags,
                                           struct timespec const *__restrict requested_time,
                                           struct timespec *remaining) {
	return libc_clock_nanosleep(clock_id, flags, requested_time, remaining);
}
/* Return clock ID for CPU-time clock */
INTERN ATTR_SECTION(".text.crt.dos.time") int
NOTHROW_NCX(LIBDCALL libd_clock_getcpuclockid)(pid_t pid,
                                               clockid_t *clock_id) {
	return libc_clock_getcpuclockid(pid, clock_id);
}
/* Pause execution for a number of nanoseconds */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_nanosleep64)(struct timespec64 const *__restrict requested_time,
                                       struct timespec64 *remaining) {
	return libc_nanosleep64(requested_time, remaining);
}
/* Get resolution of clock CLOCK_ID */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_clock_getres64)(clockid_t clock_id,
                                          struct timespec64 *res) {
	return libc_clock_getres64(clock_id, res);
}
/* Get current value of clock CLOCK_ID and store it in TP */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_clock_gettime64)(clockid_t clock_id,
                                           struct timespec64 *tp) {
	return libc_clock_gettime64(clock_id, tp);
}
/* Set clock CLOCK_ID to value TP */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_clock_settime64)(clockid_t clock_id,
                                           struct timespec64 const *tp) {
	return libc_clock_settime64(clock_id, tp);
}
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_timer_settime64)(timer_t timerid,
                                           __STDC_INT_AS_UINT_T flags,
                                           struct itimerspec64 const *__restrict value,
                                           struct itimerspec64 *__restrict ovalue) {
	return libc_timer_settime64(timerid, flags, value, ovalue);
}
/* Get current value of timer TIMERID and store it in VALUE */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_timer_gettime64)(timer_t timerid,
                                           struct itimerspec64 *value) {
	return libc_timer_gettime64(timerid, value);
}
/* High-resolution sleep with the specified clock */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((3)) int
NOTHROW_RPC(LIBDCALL libd_clock_nanosleep64)(clockid_t clock_id,
                                             __STDC_INT_AS_UINT_T flags,
                                             struct timespec64 const *requested_time,
                                             struct timespec64 *remaining) {
	return libc_clock_nanosleep64(clock_id, flags, requested_time, remaining);
}
/* Set TS to calendar time based in time base BASE */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_timespec_get)(struct timespec *ts,
                                        __STDC_INT_AS_UINT_T base) {
	return libc_timespec_get(ts, base);
}
/* Parse the given string as a date specification and return a value
 * representing the value.  The templates from the file identified by
 * the environment variable DATEMSK are used.  In case of an error
 * `getdate_err' is set */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) __STRUCT_TM *
NOTHROW_NCX(LIBDCALL libd_getdate)(const char *string) {
	return libc_getdate(string);
}
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_strftime_l)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      __STRUCT_TM const *__restrict tp,
                                      locale_t locale) {
	return libc_strftime_l(buf, bufsize, format, tp, locale);
}
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2, 3)) char *
NOTHROW_NCX(LIBDCALL libd_strptime)(char const *__restrict s,
                                    char const *__restrict format,
                                    __STRUCT_TM *__restrict tp) {
	return libc_strptime(s, format, tp);
}
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2, 3)) char *
NOTHROW_NCX(LIBDCALL libd_strptime_l)(char const *__restrict s,
                                      char const *__restrict format,
                                      __STRUCT_TM *__restrict tp,
                                      locale_t locale) {
	return libc_strptime_l(s, format, tp, locale);
}
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_getdate_r)(char const *__restrict string,
                                     __STRUCT_TM *__restrict resbufp) {
	return libc_getdate_r(string, resbufp);
}
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBDCALL libd_gmtime_r)(time_t const *__restrict timer,
                                    __STRUCT_TM *__restrict tp) {
	return libc_gmtime_r(timer, tp);
}
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBDCALL libd_localtime_r)(time_t const *__restrict timer,
                                       __STRUCT_TM *__restrict tp) {
	return libc_localtime_r(timer, tp);
}
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_ctime_r)(time_t const *__restrict timer,
                                   char buf[26]) {
	return libc_ctime_r(timer, buf);
}
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBDCALL libd_gmtime64_r)(time64_t const *__restrict timer,
                                      __STRUCT_TM *__restrict tp) {
	return libc_gmtime64_r(timer, tp);
}
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) __STRUCT_TM *
NOTHROW_NCX(LIBDCALL libd_localtime64_r)(time64_t const *__restrict timer,
                                         __STRUCT_TM *__restrict tp) {
	return libc_localtime64_r(timer, tp);
}
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_ctime64_r)(time64_t const *__restrict timer,
                                     char buf[26]) {
	return libc_ctime64_r(timer, buf);
}
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_asctime_r)(__STRUCT_TM const *__restrict tp,
                                     char buf[26]) {
	return libc_asctime_r(tp, buf);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$time, libd_time);
DEFINE_PUBLIC_ALIAS(DOS$difftime, libd_difftime);
DEFINE_PUBLIC_ALIAS(DOS$mktime, libd_mktime);
DEFINE_PUBLIC_ALIAS(DOS$ctime, libd_ctime);
DEFINE_PUBLIC_ALIAS(DOS$gmtime, libd_gmtime);
DEFINE_PUBLIC_ALIAS(DOS$localtime, libd_localtime);
DEFINE_PUBLIC_ALIAS(DOS$strftime, libd_strftime);
DEFINE_PUBLIC_ALIAS(DOS$asctime, libd_asctime);
DEFINE_PUBLIC_ALIAS(DOS$asctime_s, libd_asctime_s);
DEFINE_PUBLIC_ALIAS(DOS$_time64, libd_time64);
DEFINE_PUBLIC_ALIAS(DOS$time64, libd_time64);
DEFINE_PUBLIC_ALIAS(DOS$_difftime64, libd_difftime64);
DEFINE_PUBLIC_ALIAS(DOS$__difftime64, libd_difftime64);
DEFINE_PUBLIC_ALIAS(DOS$difftime64, libd_difftime64);
DEFINE_PUBLIC_ALIAS(DOS$_mktime64, libd_mktime64);
DEFINE_PUBLIC_ALIAS(DOS$timelocal64, libd_mktime64);
DEFINE_PUBLIC_ALIAS(DOS$mktime64, libd_mktime64);
DEFINE_PUBLIC_ALIAS(DOS$_ctime64, libd_ctime64);
DEFINE_PUBLIC_ALIAS(DOS$ctime64, libd_ctime64);
DEFINE_PUBLIC_ALIAS(DOS$_gmtime64, libd_gmtime64);
DEFINE_PUBLIC_ALIAS(DOS$gmtime64, libd_gmtime64);
DEFINE_PUBLIC_ALIAS(DOS$_localtime64, libd_localtime64);
DEFINE_PUBLIC_ALIAS(DOS$localtime64, libd_localtime64);
DEFINE_PUBLIC_ALIAS(DOS$stime, libd_stime);
DEFINE_PUBLIC_ALIAS(DOS$timegm, libd_timegm);
DEFINE_PUBLIC_ALIAS(DOS$dysize, libd_dysize);
DEFINE_PUBLIC_ALIAS(DOS$stime64, libd_stime64);
DEFINE_PUBLIC_ALIAS(DOS$timegm64, libd_timegm64);
DEFINE_PUBLIC_ALIAS(DOS$__nanosleep, libd_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$nanosleep, libd_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$__clock_getres, libd_clock_getres);
DEFINE_PUBLIC_ALIAS(DOS$clock_getres, libd_clock_getres);
DEFINE_PUBLIC_ALIAS(DOS$__clock_gettime, libd_clock_gettime);
DEFINE_PUBLIC_ALIAS(DOS$clock_gettime, libd_clock_gettime);
DEFINE_PUBLIC_ALIAS(DOS$__clock_settime, libd_clock_settime);
DEFINE_PUBLIC_ALIAS(DOS$clock_settime, libd_clock_settime);
DEFINE_PUBLIC_ALIAS(DOS$timer_create, libd_timer_create);
DEFINE_PUBLIC_ALIAS(DOS$timer_delete, libd_timer_delete);
DEFINE_PUBLIC_ALIAS(DOS$timer_settime, libd_timer_settime);
DEFINE_PUBLIC_ALIAS(DOS$timer_gettime, libd_timer_gettime);
DEFINE_PUBLIC_ALIAS(DOS$timer_getoverrun, libd_timer_getoverrun);
DEFINE_PUBLIC_ALIAS(DOS$__clock_nanosleep, libd_clock_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$clock_nanosleep, libd_clock_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$__clock_getcpuclockid, libd_clock_getcpuclockid);
DEFINE_PUBLIC_ALIAS(DOS$clock_getcpuclockid, libd_clock_getcpuclockid);
DEFINE_PUBLIC_ALIAS(DOS$nanosleep64, libd_nanosleep64);
DEFINE_PUBLIC_ALIAS(DOS$clock_getres64, libd_clock_getres64);
DEFINE_PUBLIC_ALIAS(DOS$clock_gettime64, libd_clock_gettime64);
DEFINE_PUBLIC_ALIAS(DOS$clock_settime64, libd_clock_settime64);
DEFINE_PUBLIC_ALIAS(DOS$timer_settime64, libd_timer_settime64);
DEFINE_PUBLIC_ALIAS(DOS$timer_gettime64, libd_timer_gettime64);
DEFINE_PUBLIC_ALIAS(DOS$clock_nanosleep64, libd_clock_nanosleep64);
DEFINE_PUBLIC_ALIAS(DOS$timespec_get, libd_timespec_get);
DEFINE_PUBLIC_ALIAS(DOS$getdate, libd_getdate);
DEFINE_PUBLIC_ALIAS(DOS$_strftime_l, libd_strftime_l);
DEFINE_PUBLIC_ALIAS(DOS$__strftime_l, libd_strftime_l);
DEFINE_PUBLIC_ALIAS(DOS$strftime_l, libd_strftime_l);
DEFINE_PUBLIC_ALIAS(DOS$strptime, libd_strptime);
DEFINE_PUBLIC_ALIAS(DOS$strptime_l, libd_strptime_l);
DEFINE_PUBLIC_ALIAS(DOS$getdate_r, libd_getdate_r);
DEFINE_PUBLIC_ALIAS(DOS$__gmtime_r, libd_gmtime_r);
DEFINE_PUBLIC_ALIAS(DOS$gmtime_r, libd_gmtime_r);
DEFINE_PUBLIC_ALIAS(DOS$localtime_r, libd_localtime_r);
DEFINE_PUBLIC_ALIAS(DOS$ctime_r, libd_ctime_r);
DEFINE_PUBLIC_ALIAS(DOS$gmtime64_r, libd_gmtime64_r);
DEFINE_PUBLIC_ALIAS(DOS$localtime64_r, libd_localtime64_r);
DEFINE_PUBLIC_ALIAS(DOS$ctime64_r, libd_ctime64_r);
DEFINE_PUBLIC_ALIAS(DOS$asctime_r, libd_asctime_r);

#endif /* !GUARD_LIBC_AUTO_DOSABI_TIME_C */
