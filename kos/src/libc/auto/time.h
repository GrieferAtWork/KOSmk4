/* HASH CRC-32:0xc16f81bd */
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
#ifndef GUARD_LIBC_AUTO_TIME_H
#define GUARD_LIBC_AUTO_TIME_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <time.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
INTDEF time_t NOTHROW_NCX(LIBDCALL libd_time)(time_t *timer);
/* Return the difference between TIME1 and TIME0 */
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBDCALL libd_difftime)(time_t time1, time_t time0);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the difference between TIME1 and TIME0 */
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_difftime)(time_t time1, time_t time0);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `time_t' representation of TP and normalize TP */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time_t NOTHROW_NCX(LIBDCALL libd_mktime)(__STRUCT_TM __KOS_FIXED_CONST *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `time_t' representation of TP and normalize TP */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time_t NOTHROW_NCX(LIBCCALL libc_mktime)(__STRUCT_TM __KOS_FIXED_CONST *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_ctime)(time_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_ctime)(time_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *NOTHROW_NCX(LIBDCALL libd_gmtime)(time_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *NOTHROW_NCX(LIBCCALL libc_gmtime)(time_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *NOTHROW_NCX(LIBDCALL libd_localtime)(time_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *NOTHROW_NCX(LIBCCALL libc_localtime)(time_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_strftime)(char *__restrict buf, size_t bufsize, char const *__restrict format, __STRUCT_TM const *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBCCALL libc_strftime)(char *__restrict buf, size_t bufsize, char const *__restrict format, __STRUCT_TM const *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_asctime)(struct tm const *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_asctime)(struct tm const *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_asctime_s)(char *__restrict buf, size_t buflen, struct tm const *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_asctime_s)(char *__restrict buf, size_t buflen, struct tm const *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
INTDEF time64_t NOTHROW_NCX(LIBDCALL libd_time64)(time64_t *timer);
/* Return the difference between TIME1 and TIME0 */
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBDCALL libd_difftime64)(time64_t time1, time64_t time0);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the difference between TIME1 and TIME0 */
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_difftime64)(time64_t time1, time64_t time0);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `time_t' representation of TP and normalize TP */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time64_t NOTHROW_NCX(LIBDCALL libd_mktime64)(__STRUCT_TM __KOS_FIXED_CONST *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `time_t' representation of TP and normalize TP */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time64_t NOTHROW_NCX(LIBCCALL libc_mktime64)(__STRUCT_TM __KOS_FIXED_CONST *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_ctime64)(time64_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_ctime64)(time64_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBDCALL libd_gmtime64)(time64_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_gmtime64)(time64_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBDCALL libd_localtime64)(time64_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_localtime64)(time64_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Set the system time to *WHEN. This call is restricted to the superuser */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_stime)(time_t const *when);
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time_t NOTHROW_NCX(LIBDCALL libd_timegm)(__STRUCT_TM *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time_t NOTHROW_NCX(LIBCCALL libc_timegm)(__STRUCT_TM *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the number of days in YEAR */
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBDCALL libd_dysize)(__STDC_INT_AS_UINT_T year);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the number of days in YEAR */
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_dysize)(__STDC_INT_AS_UINT_T year);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Set the system time to *WHEN. This call is restricted to the superuser */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_stime64)(time64_t const *when);
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time64_t NOTHROW_NCX(LIBDCALL libd_timegm64)(__STRUCT_TM *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time64_t NOTHROW_NCX(LIBCCALL libc_timegm64)(__STRUCT_TM *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Pause execution for a number of nanoseconds */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_nanosleep)(struct timespec const *requested_time, struct timespec *remaining);
/* Get resolution of clock CLOCK_ID */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_clock_getres)(clockid_t clock_id, struct timespec *res);
/* Get current value of clock CLOCK_ID and store it in TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_clock_gettime)(clockid_t clock_id, struct timespec *tp);
/* Set clock CLOCK_ID to value TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_clock_settime)(clockid_t clock_id, struct timespec const *tp);
/* Create new per-process timer using CLOCK_ID */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBDCALL libd_timer_create)(clockid_t clock_id, struct sigevent *__restrict evp, timer_t *__restrict timerid);
/* Delete timer TIMERID */
INTDEF int NOTHROW_NCX(LIBDCALL libd_timer_delete)(timer_t timerid);
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBDCALL libd_timer_settime)(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec const *__restrict value, struct itimerspec *__restrict ovalue);
/* Get current value of timer TIMERID and store it in VALUE */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_timer_gettime)(timer_t timerid, struct itimerspec *value);
/* Get expiration overrun for timer TIMERID */
INTDEF int NOTHROW_NCX(LIBDCALL libd_timer_getoverrun)(timer_t timerid);
/* High-resolution sleep with the specified clock */
INTDEF NONNULL((3)) int NOTHROW_RPC(LIBDCALL libd_clock_nanosleep)(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec const *__restrict requested_time, struct timespec *remaining);
/* Return clock ID for CPU-time clock */
INTDEF int NOTHROW_NCX(LIBDCALL libd_clock_getcpuclockid)(pid_t pid, clockid_t *clock_id);
/* Pause execution for a number of nanoseconds */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_nanosleep64)(struct timespec64 const *__restrict requested_time, struct timespec64 *remaining);
/* Get resolution of clock CLOCK_ID */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_clock_getres64)(clockid_t clock_id, struct timespec64 *res);
/* Get current value of clock CLOCK_ID and store it in TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_clock_gettime64)(clockid_t clock_id, struct timespec64 *tp);
/* Set clock CLOCK_ID to value TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_clock_settime64)(clockid_t clock_id, struct timespec64 const *tp);
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBDCALL libd_timer_settime64)(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec64 const *__restrict value, struct itimerspec64 *__restrict ovalue);
/* Get current value of timer TIMERID and store it in VALUE */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_timer_gettime64)(timer_t timerid, struct itimerspec64 *value);
/* High-resolution sleep with the specified clock */
INTDEF NONNULL((3)) int NOTHROW_RPC(LIBDCALL libd_clock_nanosleep64)(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec64 const *requested_time, struct timespec64 *remaining);
/* Set TS to calendar time based in time base BASE */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_timespec_get)(struct timespec *ts, __STDC_INT_AS_UINT_T base);
/* Parse the given string as a date specification and return a value
 * representing the value.  The templates from the file identified by
 * the environment variable DATEMSK are used.  In case of an error
 * `getdate_err' is set */
INTDEF NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBDCALL libd_getdate)(const char *string);
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBDCALL libd_strftime_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, __STRUCT_TM const *__restrict tp, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBCCALL libc_strftime_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, __STRUCT_TM const *__restrict tp, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
INTDEF NONNULL((1, 2, 3)) char *NOTHROW_NCX(LIBDCALL libd_strptime)(char const *__restrict s, char const *__restrict format, __STRUCT_TM *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
INTDEF NONNULL((1, 2, 3)) char *NOTHROW_NCX(LIBCCALL libc_strptime)(char const *__restrict s, char const *__restrict format, __STRUCT_TM *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
INTDEF NONNULL((1, 2, 3)) char *NOTHROW_NCX(LIBDCALL libd_strptime_l)(char const *__restrict s, char const *__restrict format, __STRUCT_TM *__restrict tp, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
INTDEF NONNULL((1, 2, 3)) char *NOTHROW_NCX(LIBCCALL libc_strptime_l)(char const *__restrict s, char const *__restrict format, __STRUCT_TM *__restrict tp, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_getdate_r)(char const *__restrict string, __STRUCT_TM *__restrict resbufp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_getdate_r)(char const *__restrict string, __STRUCT_TM *__restrict resbufp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBDCALL libd_gmtime_r)(time_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_gmtime_r)(time_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBDCALL libd_localtime_r)(time_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_localtime_r)(time_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_ctime_r)(time_t const *__restrict timer, char buf[26]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_ctime_r)(time_t const *__restrict timer, char buf[26]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBDCALL libd_gmtime64_r)(time64_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_gmtime64_r)(time64_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBDCALL libd_localtime64_r)(time64_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_localtime64_r)(time64_t const *__restrict timer, __STRUCT_TM *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_ctime64_r)(time64_t const *__restrict timer, char buf[26]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_ctime64_r)(time64_t const *__restrict timer, char buf[26]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_asctime_r)(__STRUCT_TM const *__restrict tp, char buf[26]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_asctime_r)(__STRUCT_TM const *__restrict tp, char buf[26]);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_TIME_H */
