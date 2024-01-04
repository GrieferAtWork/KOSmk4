/* HASH CRC-32:0x762cb1cb */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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

#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct tm *NOTHROW_NCX(LIBCCALL libc_normalize_struct_tm)(struct tm *__restrict tp);
/* >> clock(3)
 * Time used by the program so  far (user time + system  time)
 * The `result / CLOCKS_PER_SECOND' is program time in seconds */
INTDEF WUNUSED clock_t NOTHROW_NCX(LIBCCALL libc_clock)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTDEF ATTR_OUT_OPT(1) time_t NOTHROW_NCX(LIBDCALL libd_time)(time_t *timer);
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBDCALL libd_difftime)(time_t time1, time_t time0);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_difftime)(time_t time1, time_t time0);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time_t NOTHROW_NCX(LIBDCALL libd_mktime)(struct tm *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time_t NOTHROW_NCX(LIBCCALL libc_mktime)(struct tm *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_ctime)(time_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_ctime)(time_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBDCALL libd_gmtime)(time_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBCCALL libc_gmtime)(time_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBDCALL libd_localtime)(time_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBCCALL libc_localtime)(time_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strftime(3)
 * Format `tp' into `s' according to `format'.
 * Write no more than `maxsize' characters and return the number
 * of characters  written, or  0 if  it would  exceed  `maxsize' */
INTDEF ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2) size_t NOTHROW_NCX(LIBDCALL libd_strftime)(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strftime(3)
 * Format `tp' into `s' according to `format'.
 * Write no more than `maxsize' characters and return the number
 * of characters  written, or  0 if  it would  exceed  `maxsize' */
INTDEF ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2) size_t NOTHROW_NCX(LIBCCALL libc_strftime)(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> asctime(3)
 * Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is  the  representation  of  `tp'  in  this  format */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_asctime)(struct tm const *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> asctime(3)
 * Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is  the  representation  of  `tp'  in  this  format */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_asctime)(struct tm const *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> asctime_s(3) */
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_asctime_s)(char *__restrict buf, size_t buflen, struct tm const *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> asctime_s(3) */
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc_asctime_s)(char *__restrict buf, size_t buflen, struct tm const *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTDEF ATTR_OUT_OPT(1) time64_t NOTHROW_NCX(LIBDCALL libd_time64)(time64_t *timer);
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBDCALL libd_difftime64)(time64_t time1, time64_t time0);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBCCALL libc_difftime64)(time64_t time1, time64_t time0);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time64_t NOTHROW_NCX(LIBDCALL libd_mktime64)(struct tm *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time64_t NOTHROW_NCX(LIBCCALL libc_mktime64)(struct tm *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_ctime64)(time64_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_ctime64)(time64_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBDCALL libd_gmtime64)(time64_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBCCALL libc_gmtime64)(time64_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBDCALL libd_localtime64)(time64_t const *timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct tm *NOTHROW_NCX(LIBCCALL libc_localtime64)(time64_t const *timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_stime)(time_t const *when);
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time_t NOTHROW_NCX(LIBDCALL libd_timegm)(struct tm *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time_t NOTHROW_NCX(LIBCCALL libc_timegm)(struct tm *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dysize(3)
 * Return the number of days in YEAR */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_dysize)(__STDC_INT_AS_UINT_T year);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dysize(3)
 * Return the number of days in YEAR */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_dysize)(__STDC_INT_AS_UINT_T year);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_stime64)(time64_t const *when);
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time64_t NOTHROW_NCX(LIBDCALL libd_timegm64)(struct tm *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) time64_t NOTHROW_NCX(LIBCCALL libc_timegm64)(struct tm *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds
 * @return: 0 : Success
 * @return: -1: [errno=EINTR]  System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: -1: [errno=EINVAL] Invalid `requested_time->tv_nsec' */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_nanosleep)(struct timespec const *requested_time, struct timespec *remaining);
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_clock_getres)(clockid_t clock_id, struct timespec *res);
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_clock_gettime)(clockid_t clock_id, struct timespec *tp);
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
INTDEF ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_clock_settime)(clockid_t clock_id, struct timespec const *tp);
/* >> timer_create(2)
 * Create new per-process timer using `clock_id' */
INTDEF ATTR_IN_OPT(2) ATTR_OUT(3) int NOTHROW_NCX(LIBDCALL libd_timer_create)(clockid_t clock_id, struct sigevent *__restrict evp, timer_t *__restrict timerid);
/* >> timer_delete(2)
 * Delete timer `timerid' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_timer_delete)(timer_t timerid);
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTDEF ATTR_IN(3) ATTR_OUT_OPT(4) int NOTHROW_NCX(LIBDCALL libd_timer_settime)(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec const *__restrict value, struct itimerspec *__restrict ovalue);
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTDEF ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_timer_gettime)(timer_t timerid, struct itimerspec *value);
/* >> timer_getoverrun(2)
 * Get expiration overrun for timer `timerid' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_timer_getoverrun)(timer_t timerid);
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME'
 * @return: 0 :      Success
 * @return: EINTR:   System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: EINVAL:  Invalid `clock_id', `flags' or `requested_time->tv_nsec'
 * @return: ENOTSUP: Clock specified by `clock_id' isn't supported. */
INTDEF ATTR_IN(3) ATTR_OUT_OPT(4) errno_t NOTHROW_RPC(LIBDCALL libd_clock_nanosleep)(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec const *__restrict requested_time, struct timespec *remaining);
/* >> clock_getcpuclockid(2)
 * Return clock ID for CPU-time clock
 * @return: 0 :     Success
 * @return: ENOSYS: Not supported
 * @return: EPERM:  You're not allowed to read the CPU-time clock of `pid'
 * @return: ESRCH:  No such process `pid' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_clock_getcpuclockid)(pid_t pid, clockid_t *clock_id);
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds
 * @return: 0 : Success
 * @return: -1: [errno=EINTR]  System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: -1: [errno=EINVAL] Invalid `requested_time->tv_nsec' */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_nanosleep64)(struct timespec64 const *__restrict requested_time, struct timespec64 *remaining);
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_clock_getres64)(clockid_t clock_id, struct timespec64 *res);
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_clock_gettime64)(clockid_t clock_id, struct timespec64 *tp);
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
INTDEF ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_clock_settime64)(clockid_t clock_id, struct timespec64 const *tp);
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTDEF ATTR_IN(3) ATTR_OUT_OPT(4) int NOTHROW_NCX(LIBDCALL libd_timer_settime64)(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec64 const *__restrict value, struct itimerspec64 *__restrict ovalue);
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_timer_gettime64)(timer_t timerid, struct itimerspec64 *value);
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME'
 * @return: 0 :      Success
 * @return: EINTR:   System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: EINVAL:  Invalid `clock_id', `flags' or `requested_time->tv_nsec'
 * @return: ENOTSUP: Clock specified by `clock_id' isn't supported. */
INTDEF ATTR_IN(3) ATTR_OUT_OPT(4) errno_t NOTHROW_RPC(LIBDCALL libd_clock_nanosleep64)(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec64 const *requested_time, struct timespec64 *remaining);
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_timespec_get)(struct timespec *ts, int base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_timespec_get)(struct timespec *ts, int base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_timespec_get64)(struct timespec64 *ts, int base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_timespec_get64)(struct timespec64 *ts, int base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_timespec_getres)(struct timespec *ts, int base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_timespec_getres)(struct timespec *ts, int base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_timespec_getres64)(struct timespec64 *ts, int base);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_timespec_getres64)(struct timespec64 *ts, int base);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getdate(3)
 * Parse the given string as a date specification and return a value
 * representing the value. The templates from the file identified by
 * the environment variable `$DATEMSK' are used. In case of an error
 * `getdate_err' is set */
INTDEF ATTR_IN(1) struct tm *NOTHROW_NCX(LIBDCALL libd_getdate)(const char *string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getdate(3)
 * Parse the given string as a date specification and return a value
 * representing the value. The templates from the file identified by
 * the environment variable `$DATEMSK' are used. In case of an error
 * `getdate_err' is set */
INTDEF ATTR_IN(1) struct tm *NOTHROW_NCX(LIBCCALL libc_getdate)(const char *string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
INTDEF ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2) size_t NOTHROW_NCX(LIBDCALL libd_strftime_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
INTDEF ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_STRFTIME(3, 0) ATTR_OUTS(1, 2) size_t NOTHROW_NCX(LIBCCALL libc_strftime_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, struct tm const *__restrict tp, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strptime(3)
 * Parse `s' according to `format' and store binary time information in `tp'.
 * The return  value is  a pointer  to the  first unparsed  character in  `s' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) char *NOTHROW_NCX(LIBDCALL libd_strptime)(char const *__restrict s, char const *__restrict format, struct tm *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strptime(3)
 * Parse `s' according to `format' and store binary time information in `tp'.
 * The return  value is  a pointer  to the  first unparsed  character in  `s' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) char *NOTHROW_NCX(LIBCCALL libc_strptime)(char const *__restrict s, char const *__restrict format, struct tm *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strptime_l(3)
 * Similar to `strptime' but take the information from
 * the  provided  locale  and  not  the  global locale */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) char *NOTHROW_NCX(LIBDCALL libd_strptime_l)(char const *__restrict s, char const *__restrict format, struct tm *__restrict tp, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strptime_l(3)
 * Similar to `strptime' but take the information from
 * the  provided  locale  and  not  the  global locale */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) char *NOTHROW_NCX(LIBCCALL libc_strptime_l)(char const *__restrict s, char const *__restrict format, struct tm *__restrict tp, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getdate_r(3)
 * Since  `getdate' is not  reentrant because of  the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The  functionality is  the same.  The  result is  returned in
 * the  buffer pointed to by `resbufp' and in case of an error, the return
 * value is != 0  with the same values  as given above for  `getdate_err'. */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_getdate_r)(char const *__restrict string, struct tm *__restrict resbufp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getdate_r(3)
 * Since  `getdate' is not  reentrant because of  the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The  functionality is  the same.  The  result is  returned in
 * the  buffer pointed to by `resbufp' and in case of an error, the return
 * value is != 0  with the same values  as given above for  `getdate_err'. */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_getdate_r)(char const *__restrict string, struct tm *__restrict resbufp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTDEF ATTR_INOUT(2) int NOTHROW_NCX(LIBDCALL libd_clock_adjtime)(clockid_t clock_id, struct timex *utx);
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTDEF ATTR_INOUT(2) int NOTHROW_NCX(LIBDCALL libd_clock_adjtime64)(clockid_t clock_id, struct timex64 *utx);
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBDCALL libd_gmtime_r)(time_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBCCALL libc_gmtime_r)(time_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBDCALL libd_localtime_r)(time_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBCCALL libc_localtime_r)(time_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_ctime_r)(time_t const *__restrict timer, char buf[26]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_ctime_r)(time_t const *__restrict timer, char buf[26]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBDCALL libd_gmtime64_r)(time64_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBCCALL libc_gmtime64_r)(time64_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBDCALL libd_localtime64_r)(time64_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(1) ATTR_OUT(2) struct tm *NOTHROW_NCX(LIBCCALL libc_localtime64_r)(time64_t const *__restrict timer, struct tm *__restrict tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_ctime64_r)(time64_t const *__restrict timer, char buf[26]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_ctime64_r)(time64_t const *__restrict timer, char buf[26]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> asctime_r(3)
 * Return in `buf' a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that   is   the   representation   of   `tp'   in   this   format */
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_asctime_r)(struct tm const *__restrict tp, char buf[26]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> asctime_r(3)
 * Return in `buf' a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that   is   the   representation   of   `tp'   in   this   format */
INTDEF ATTR_IN(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_asctime_r)(struct tm const *__restrict tp, char buf[26]);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW(LIBDCALL libc___daylight)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED long *NOTHROW(LIBDCALL libc___timezone)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char **NOTHROW(LIBDCALL libc___tzname)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED __LONG32_TYPE__ *NOTHROW(LIBDCALL libc___dstbias)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_daylight)(int *p_result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_daylight)(int *p_result);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_timezone)(long *p_seconds);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_timezone)(long *p_seconds);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_dstbias)(__LONG32_TYPE__ *p_result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_dstbias)(__LONG32_TYPE__ *p_result);
INTDEF ATTR_OUT(1) ATTR_OUT_OPT(2) errno_t NOTHROW_NCX(LIBDCALL libd__get_tzname)(size_t *result, char *buf, size_t bufsize, int index);
INTDEF ATTR_OUT(1) ATTR_OUT_OPT(2) errno_t NOTHROW_NCX(LIBCCALL libc__get_tzname)(size_t *result, char *buf, size_t bufsize, int index);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__gmtime32_s)(struct tm *__restrict tp, time32_t const *__restrict timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc__gmtime32_s)(struct tm *__restrict tp, time32_t const *__restrict timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__gmtime64_s)(struct tm *__restrict tp, time64_t const *__restrict timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc__gmtime64_s)(struct tm *__restrict tp, time64_t const *__restrict timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__localtime32_s)(struct tm *__restrict tp, time32_t const *__restrict timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc__localtime32_s)(struct tm *__restrict tp, time32_t const *__restrict timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__localtime64_s)(struct tm *__restrict tp, time64_t const *__restrict timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc__localtime64_s)(struct tm *__restrict tp, time64_t const *__restrict timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__ctime32_s)(char buf[26], size_t bufsize, time32_t const *__restrict timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__ctime32_s)(char buf[26], size_t bufsize, time32_t const *__restrict timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__ctime64_s)(char buf[26], size_t bufsize, time64_t const *__restrict timer);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__ctime64_s)(char buf[26], size_t bufsize, time64_t const *__restrict timer);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd__strtime)(char buf[9]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc__strtime)(char buf[9]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd__strdate)(char buf[9]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc__strdate)(char buf[9]);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__strtime_s)(char *buf, size_t bufsize);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__strtime_s)(char *buf, size_t bufsize);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__strdate_s)(char *buf, size_t bufsize);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__strdate_s)(char *buf, size_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(1) unsigned int NOTHROW_NCX(LIBDCALL libd__getsystime)(struct tm *tp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(1) unsigned int NOTHROW_NCX(LIBCCALL libc__getsystime)(struct tm *tp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT(1) unsigned int NOTHROW_NCX(LIBDCALL libd__setsystime)(struct tm *tp, unsigned int milliseconds);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT(1) unsigned int NOTHROW_NCX(LIBCCALL libc__setsystime)(struct tm *tp, unsigned int milliseconds);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd___nanosleep_nocancel)(struct timespec const *requested_time, struct timespec *remaining);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc___nanosleep_nocancel)(struct timespec const *requested_time, struct timespec *remaining);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd___nanosleep64_nocancel)(struct timespec64 const *requested_time, struct timespec64 *remaining);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc___nanosleep64_nocancel)(struct timespec64 const *requested_time, struct timespec64 *remaining);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_TIME_H */
