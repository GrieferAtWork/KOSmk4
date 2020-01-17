/* HASH CRC-32:0xdb5365cb */
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
#ifndef GUARD_LIBC_USER_TIME_H
#define GUARD_LIBC_USER_TIME_H 1

#include "../api.h"
#include "../auto/time.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <time.h>

DECL_BEGIN

/* Time used by the program so far (user time + system time)
 * The result / CLOCKS_PER_SECOND is program time in seconds */
INTDEF WUNUSED clock_t NOTHROW_NCX(LIBCCALL libc_clock)(void);
/* Return the current time and put it in *TIMER if TIMER is not NULL */
INTDEF time_t NOTHROW_NCX(LIBCCALL libc_time)(time_t *timer);
/* Return the current time and put it in *TIMER if TIMER is not NULL */
INTDEF time64_t NOTHROW_NCX(LIBCCALL libc_time64)(time64_t *timer);
/* Set time conversion information from the TZ environment variable.
 * If TZ is not defined, a locale-dependent default is used */
INTDEF void NOTHROW_NCX(LIBCCALL libc_tzset)(void);
/* Set the system time to *WHEN. This call is restricted to the superuser */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_stime)(time_t const *when);
/* Set the system time to *WHEN. This call is restricted to the superuser */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_stime64)(time64_t const *when);
/* Pause execution for a number of nanoseconds */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_nanosleep)(struct timespec const *requested_time, struct timespec *remaining);
/* Get resolution of clock CLOCK_ID */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_getres)(clockid_t clock_id, struct timespec *res);
/* Get current value of clock CLOCK_ID and store it in TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_gettime)(clockid_t clock_id, struct timespec *tp);
/* Set clock CLOCK_ID to value TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_settime)(clockid_t clock_id, struct timespec const *tp);
/* Create new per-process timer using CLOCK_ID */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_timer_create)(clockid_t clock_id, struct sigevent *__restrict evp, timer_t *__restrict timerid);
/* Delete timer TIMERID */
INTDEF int NOTHROW_NCX(LIBCCALL libc_timer_delete)(timer_t timerid);
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_timer_settime)(timer_t timerid, int flags, struct itimerspec const *__restrict value, struct itimerspec *__restrict ovalue);
/* Get current value of timer TIMERID and store it in VALUE */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_timer_gettime)(timer_t timerid, struct itimerspec *value);
/* Get expiration overrun for timer TIMERID */
INTDEF int NOTHROW_NCX(LIBCCALL libc_timer_getoverrun)(timer_t timerid);
/* High-resolution sleep with the specified clock */
INTDEF NONNULL((3)) int NOTHROW_RPC(LIBCCALL libc_clock_nanosleep)(clockid_t clock_id, int flags, struct timespec const *__restrict requested_time, struct timespec *remaining);
/* Return clock ID for CPU-time clock */
INTDEF int NOTHROW_NCX(LIBCCALL libc_clock_getcpuclockid)(pid_t pid, clockid_t *clock_id);
/* Pause execution for a number of nanoseconds */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_nanosleep64)(struct timespec64 const *__restrict requested_time, struct timespec64 *remaining);
/* Get resolution of clock CLOCK_ID */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_getres64)(clockid_t clock_id, struct timespec64 *res);
/* Get current value of clock CLOCK_ID and store it in TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_gettime64)(clockid_t clock_id, struct timespec64 *tp);
/* Set clock CLOCK_ID to value TP */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_clock_settime64)(clockid_t clock_id, struct timespec64 const *tp);
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_timer_settime64)(timer_t timerid, int flags, struct itimerspec64 const *__restrict value, struct itimerspec64 *__restrict ovalue);
/* Get current value of timer TIMERID and store it in VALUE */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_timer_gettime64)(timer_t timerid, struct itimerspec64 *value);
/* High-resolution sleep with the specified clock */
INTDEF NONNULL((3)) int NOTHROW_RPC(LIBCCALL libc_clock_nanosleep64)(clockid_t clock_id, int flags, struct timespec64 const *requested_time, struct timespec64 *remaining);
/* Set TS to calendar time based in time base BASE */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_timespec_get)(struct timespec *ts, int base);
/* Parse the given string as a date specification and return a value
 * representing the value.  The templates from the file identified by
 * the environment variable DATEMSK are used.  In case of an error
 * `getdate_err' is set */
INTDEF NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_getdate)(const char *string);
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_getdate_r)(const char *__restrict string, __STRUCT_TM *__restrict resbufp);
INTDEF char *libc_tzname[2];
INTDEF int libc_daylight;
INTDEF longptr_t libc_timezone;

DECL_END

#endif /* !GUARD_LIBC_USER_TIME_H */
