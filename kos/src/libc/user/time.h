/* HASH CRC-32:0xc68a95ca */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_TIME_H
#define GUARD_LIBC_USER_TIME_H 1

#include "../api.h"
#include "../auto/time.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <time.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> clock(3)
 * Time used by the program so far (user time + system time)
 * The `result / CLOCKS_PER_SECOND' is program time in seconds */
INTDEF WUNUSED clock_t NOTHROW_NCX(LIBCCALL libc_clock)(void);
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTDEF time_t NOTHROW_NCX(LIBCCALL libc_time)(time_t *timer);
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTDEF time64_t NOTHROW_NCX(LIBCCALL libc_time64)(time64_t *timer);
/* >> tzset(3)
 * Set time conversion information from the `$TZ' environment variable.
 * If `$TZ' is not defined, a locale-dependent default is used */
INTDEF void NOTHROW_NCX(LIBCCALL libc_tzset)(void);
/* >> stime(3), stime64(3)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_stime)(time_t const *when);
/* >> stime(3), stime64(3)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_stime64)(time64_t const *when);
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_nanosleep)(struct timespec const *requested_time, struct timespec *remaining);
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_getres)(clockid_t clock_id, struct timespec *res);
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_gettime)(clockid_t clock_id, struct timespec *tp);
/* >> clock_settime(2)
 * Set clock `clock_id' to value `tp' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_settime)(clockid_t clock_id, struct timespec const *tp);
/* >> timer_create(2)
 * Create new per-process timer using `clock_id' */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_timer_create)(clockid_t clock_id, struct sigevent *__restrict evp, timer_t *__restrict timerid);
/* >> timer_delete(2)
 * Delete timer `timerid' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_timer_delete)(timer_t timerid);
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_timer_settime)(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec const *__restrict value, struct itimerspec *__restrict ovalue);
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_timer_gettime)(timer_t timerid, struct itimerspec *value);
/* >> timer_getoverrun(2)
 * Get expiration overrun for timer `timerid' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_timer_getoverrun)(timer_t timerid);
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock */
INTDEF NONNULL((3)) int NOTHROW_RPC(LIBCCALL libc_clock_nanosleep)(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec const *__restrict requested_time, struct timespec *remaining);
/* >> clock_getcpuclockid(2)
 * Return clock ID for CPU-time clock */
INTDEF int NOTHROW_NCX(LIBCCALL libc_clock_getcpuclockid)(pid_t pid, clockid_t *clock_id);
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_nanosleep64)(struct timespec64 const *__restrict requested_time, struct timespec64 *remaining);
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_getres64)(clockid_t clock_id, struct timespec64 *res);
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_gettime64)(clockid_t clock_id, struct timespec64 *tp);
/* >> clock_settime(2)
 * Set clock `clock_id' to value `tp' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_settime64)(clockid_t clock_id, struct timespec64 const *tp);
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_timer_settime64)(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec64 const *__restrict value, struct itimerspec64 *__restrict ovalue);
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_timer_gettime64)(timer_t timerid, struct itimerspec64 *value);
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock */
INTDEF NONNULL((3)) int NOTHROW_RPC(LIBCCALL libc_clock_nanosleep64)(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec64 const *requested_time, struct timespec64 *remaining);
/* >> getdate(3)
 * Parse the given string as a date specification and return a value
 * representing the value. The templates from the file identified by
 * the environment variable `$DATEMSK' are used. In case of an error
 * `getdate_err' is set */
INTDEF NONNULL((1)) struct tm *NOTHROW_NCX(LIBCCALL libc_getdate)(const char *string);
#endif /* !__KERNEL__ */
INTDEF char *libc_tzname[2];
INTDEF int libc_daylight;
INTDEF longptr_t libc_timezone;
#ifndef __KERNEL__
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_clock_adjtime)(clockid_t clock_id, struct timex *utx);
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_clock_adjtime64)(clockid_t clock_id, struct timex64 *utx);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_TIME_H */
