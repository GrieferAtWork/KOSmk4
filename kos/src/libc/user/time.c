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
#ifndef GUARD_LIBC_USER_TIME_C
#define GUARD_LIBC_USER_TIME_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h>

#include "time.h"

/**/
#include "../libc/globals.h"

DECL_BEGIN


DEFINE_PUBLIC_ALIAS(DOS$__tzname, libd___tzname);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.time.timezone.__tzname") char **
NOTHROW_NCX(libd___tzname)(void) {
	return &tzname;
}

DEFINE_PUBLIC_ALIAS(DOS$__daylight, libd___daylight);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.time.timezone.__daylight") int *
NOTHROW_NCX(libd___daylight)(void) {
	return &daylight;
}

DEFINE_PUBLIC_ALIAS(DOS$__timezone, libd___timezone);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.time.timezone.__daylight") longptr_t *
NOTHROW_NCX(libd___timezone)(void) {
	return &timezone;
}




/*[[[head:libc_tzset,hash:CRC-32=0x5a534c25]]]*/
/* >> tzset(3)
 * Set time conversion information from the `$TZ' environment variable.
 * If `$TZ' is not defined, a locale-dependent default is used */
INTERN ATTR_SECTION(".text.crt.time") void
NOTHROW_NCX(LIBCCALL libc_tzset)(void)
/*[[[body:libc_tzset]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("tzset"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_tzset]]]*/




/*[[[head:libc_clock,hash:CRC-32=0xf771aaae]]]*/
/* >> clock(3)
 * Time used by the program so far (user time + system time)
 * The `result / CLOCKS_PER_SECOND' is program time in seconds */
INTERN ATTR_SECTION(".text.crt.time") WUNUSED clock_t
NOTHROW_NCX(LIBCCALL libc_clock)(void)
/*[[[body:libc_clock]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("clock"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clock]]]*/

/*[[[head:libc_getdate,hash:CRC-32=0x9fe7ec20]]]*/
/* >> getdate(3)
 * Parse the given string as a date specification and return a value
 * representing the value. The templates from the file identified by
 * the environment variable `$DATEMSK' are used. In case of an error
 * `getdate_err' is set */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1)) struct tm *
NOTHROW_NCX(LIBCCALL libc_getdate)(const char *string)
/*[[[body:libc_getdate]]]*/
/*AUTO*/{
	(void)string;
	CRT_UNIMPLEMENTEDF("getdate(%q)", string); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getdate]]]*/

/*[[[head:libc_clock_adjtime,hash:CRC-32=0xc1841cf]]]*/
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTERN ATTR_SECTION(".text.crt.time") int
NOTHROW_NCX(LIBCCALL libc_clock_adjtime)(clockid_t clock_id,
                                         struct timex *utx)
/*[[[body:libc_clock_adjtime]]]*/
/*AUTO*/{
	(void)clock_id;
	(void)utx;
	CRT_UNIMPLEMENTEDF("clock_adjtime(%" PRIxN(__SIZEOF_CLOCKID_T__) ", %p)", clock_id, utx); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clock_adjtime]]]*/

/*[[[head:libc_clock_adjtime64,hash:CRC-32=0x3411c04e]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_adjtime64, libc_clock_adjtime);
#else /* MAGIC:alias */
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTERN ATTR_SECTION(".text.crt.time") int
NOTHROW_NCX(LIBCCALL libc_clock_adjtime64)(clockid_t clock_id,
                                           struct timex64 *utx)
/*[[[body:libc_clock_adjtime64]]]*/
/*AUTO*/{
	(void)clock_id;
	(void)utx;
	CRT_UNIMPLEMENTEDF("clock_adjtime64(%" PRIxN(__SIZEOF_CLOCKID_T__) ", %p)", clock_id, utx); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_adjtime64]]]*/



/*[[[head:libc_time,hash:CRC-32=0x7977f7df]]]*/
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTERN ATTR_SECTION(".text.crt.time") time_t
NOTHROW_NCX(LIBCCALL libc_time)(time_t *timer)
/*[[[body:libc_time]]]*/
{
#ifdef SYS_time
	time_t result;
	result = sys_time(timer);
	return libc_seterrno_syserr(result);
#else /* SYS_time */
	struct timeval tv;
	errno_t error;
	error = sys_gettimeofday(&tv, NULL);
	if (E_ISERR(error)) {
		libc_seterrno(-error);
		return -1;
	}
	if (timer)
		*timer = tv.tv_sec;
	return tv.tv_sec;
#endif /* !SYS_time */
}
/*[[[end:libc_time]]]*/

/*[[[head:libc_time64,hash:CRC-32=0x3ccc9773]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_time64, libc_time);
#else /* MAGIC:alias */
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTERN ATTR_SECTION(".text.crt.time") time64_t
NOTHROW_NCX(LIBCCALL libc_time64)(time64_t *timer)
/*[[[body:libc_time64]]]*/
{
#ifdef SYS_time64
	time_t result;
	result = sys_time64(timer);
	return libc_seterrno_syserr(result);
#else /* SYS_time64 */
	struct timeval64 tv;
	errno_t error;
	error = sys_gettimeofday64(&tv, NULL);
	if (E_ISERR(error)) {
		libc_seterrno(-error);
		return -1;
	}
	if (timer)
		*timer = tv.tv_sec;
	return tv.tv_sec;
#endif /* !SYS_time64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_time64]]]*/

/*[[[head:libc_stime,hash:CRC-32=0xdc7ded8e]]]*/
/* >> stime(3), stime64(3)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_stime)(time_t const *when)
/*[[[body:libc_stime]]]*/
{
	errno_t error;
#ifdef __NR_stime
	error = sys_stime(when);
#else /* __NR_stime */
	struct timeval tv;
	tv.tv_sec  = *when;
	tv.tv_usec = 0;
	error = sys_settimeofday(&tv, NULL);
#endif /* !__NR_stime */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_stime]]]*/

/*[[[head:libc_stime64,hash:CRC-32=0xf7c9f588]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_stime64, libc_stime);
#else /* MAGIC:alias */
/* >> stime(3), stime64(3)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_stime64)(time64_t const *when)
/*[[[body:libc_stime64]]]*/
{
	errno_t error;
#ifdef __NR_stime
	error = sys_stime64(when);
#else /* __NR_stime */
	struct timeval64 tv;
	tv.tv_sec  = *when;
	tv.tv_usec = 0;
	error = sys_settimeofday64(&tv, NULL);
#endif /* !__NR_stime */
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_stime64]]]*/


/*[[[head:libc_nanosleep,hash:CRC-32=0x8055bcef]]]*/
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_nanosleep)(struct timespec const *requested_time,
                                     struct timespec *remaining)
/*[[[body:libc_nanosleep]]]*/
{
	errno_t error;
	error = sys_nanosleep(requested_time, remaining);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_nanosleep]]]*/

/*[[[head:libc_nanosleep64,hash:CRC-32=0x9f5c511]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_nanosleep64, libc_nanosleep);
#else /* MAGIC:alias */
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_nanosleep64)(struct timespec64 const *__restrict requested_time,
                                       struct timespec64 *remaining)
/*[[[body:libc_nanosleep64]]]*/
{
	errno_t error;
	error = sys_nanosleep64(requested_time, remaining);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_nanosleep64]]]*/

/*[[[head:libc_clock_settime64,hash:CRC-32=0x4f6b29a7]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_settime64, libc_clock_settime);
#else /* MAGIC:alias */
/* >> clock_settime(2)
 * Set clock `clock_id' to value `tp' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_clock_settime64)(clockid_t clock_id,
                                           struct timespec64 const *tp)
/*[[[body:libc_clock_settime64]]]*/
{
	errno_t error;
	error = sys_clock_settime64(clock_id, tp);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_settime64]]]*/

/*[[[head:libc_clock_settime,hash:CRC-32=0xb876b1cd]]]*/
/* >> clock_settime(2)
 * Set clock `clock_id' to value `tp' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_clock_settime)(clockid_t clock_id,
                                         struct timespec const *tp)
/*[[[body:libc_clock_settime]]]*/
{
	errno_t error;
	error = sys_clock_settime(clock_id, tp);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_clock_settime]]]*/

/*[[[head:libc_clock_getcpuclockid,hash:CRC-32=0x83d68da1]]]*/
/* >> clock_getcpuclockid(2)
 * Return clock ID for CPU-time clock */
INTERN ATTR_SECTION(".text.crt.time") int
NOTHROW_NCX(LIBCCALL libc_clock_getcpuclockid)(pid_t pid,
                                               clockid_t *clock_id)
/*[[[body:libc_clock_getcpuclockid]]]*/
/*AUTO*/{
	(void)pid;
	(void)clock_id;
	CRT_UNIMPLEMENTEDF("clock_getcpuclockid(%" PRIxN(__SIZEOF_PID_T__) ", %p)", pid, clock_id); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clock_getcpuclockid]]]*/

/*[[[head:libc_clock_gettime,hash:CRC-32=0x3e256f99]]]*/
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_clock_gettime)(clockid_t clock_id,
                                         struct timespec *tp)
/*[[[body:libc_clock_gettime]]]*/
{
	errno_t error;
	error = sys_clock_gettime(clock_id, tp);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_clock_gettime]]]*/

/*[[[head:libc_clock_gettime64,hash:CRC-32=0x1d34c320]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_gettime64, libc_clock_gettime);
#else /* MAGIC:alias */
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_clock_gettime64)(clockid_t clock_id,
                                           struct timespec64 *tp)
/*[[[body:libc_clock_gettime64]]]*/
{
	errno_t error;
	error = sys_clock_gettime64(clock_id, tp);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_gettime64]]]*/

/*[[[head:libc_clock_getres,hash:CRC-32=0xf3fb1bf7]]]*/
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_clock_getres)(clockid_t clock_id,
                                        struct timespec *res)
/*[[[body:libc_clock_getres]]]*/
{
	errno_t error;
	error = sys_clock_getres(clock_id, res);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_clock_getres]]]*/

/*[[[head:libc_clock_getres64,hash:CRC-32=0xb1f342fd]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_getres64, libc_clock_getres);
#else /* MAGIC:alias */
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_clock_getres64)(clockid_t clock_id,
                                          struct timespec64 *res)
/*[[[body:libc_clock_getres64]]]*/
{
	errno_t error;
#ifdef SYS_clock_getres64
	error = sys_clock_getres64(clock_id, res);
#elif defined(SYS_clock_getres_time64)
	error = sys_clock_getres_time64(clock_id, res);
#else /* ... */
#error "No way to implement `clock_getres64()'"
#endif /* !... */
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_getres64]]]*/

/*[[[head:libc_clock_nanosleep,hash:CRC-32=0xc00ba06f]]]*/
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((3)) int
NOTHROW_RPC(LIBCCALL libc_clock_nanosleep)(clockid_t clock_id,
                                           __STDC_INT_AS_UINT_T flags,
                                           struct timespec const *__restrict requested_time,
                                           struct timespec *remaining)
/*[[[body:libc_clock_nanosleep]]]*/
{
	errno_t error;
	error = sys_clock_nanosleep(clock_id,
	                            (syscall_ulong_t)(unsigned int)flags,
	                            requested_time, remaining);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_clock_nanosleep]]]*/

/*[[[head:libc_clock_nanosleep64,hash:CRC-32=0xb134bae4]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_nanosleep64, libc_clock_nanosleep);
#else /* MAGIC:alias */
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((3)) int
NOTHROW_RPC(LIBCCALL libc_clock_nanosleep64)(clockid_t clock_id,
                                             __STDC_INT_AS_UINT_T flags,
                                             struct timespec64 const *requested_time,
                                             struct timespec64 *remaining)
/*[[[body:libc_clock_nanosleep64]]]*/
{
	errno_t error;
#ifdef SYS_clock_nanosleep64
	error = sys_clock_nanosleep64(clock_id,
	                              (syscall_ulong_t)(unsigned int)flags,
	                              requested_time, remaining);
#elif defined(SYS_clock_nanosleep_time64)
	error = sys_clock_nanosleep_time64(clock_id,
                                       (syscall_ulong_t)(unsigned int)flags,
                                       requested_time, remaining);
#else /* ... */
#error "No way to implement `clock_nanosleep64()'"
#endif /* !... */
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_nanosleep64]]]*/

/*[[[head:libc_timer_create,hash:CRC-32=0x6d7f4b04]]]*/
/* >> timer_create(2)
 * Create new per-process timer using `clock_id' */
INTERN ATTR_SECTION(".text.crt.timer") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc_timer_create)(clockid_t clock_id,
                                        struct sigevent *__restrict evp,
                                        timer_t *__restrict timerid)
/*[[[body:libc_timer_create]]]*/
{
	errno_t error;
	error = sys_timer_create(clock_id, evp, timerid);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timer_create]]]*/

/*[[[head:libc_timer_delete,hash:CRC-32=0x76b0e52b]]]*/
/* >> timer_delete(2)
 * Delete timer `timerid' */
INTERN ATTR_SECTION(".text.crt.timer") int
NOTHROW_NCX(LIBCCALL libc_timer_delete)(timer_t timerid)
/*[[[body:libc_timer_delete]]]*/
{
	errno_t error;
	error = sys_timer_delete(timerid);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timer_delete]]]*/

/*[[[head:libc_timer_getoverrun,hash:CRC-32=0x6f9285ac]]]*/
/* >> timer_getoverrun(2)
 * Get expiration overrun for timer `timerid' */
INTERN ATTR_SECTION(".text.crt.timer") int
NOTHROW_NCX(LIBCCALL libc_timer_getoverrun)(timer_t timerid)
/*[[[body:libc_timer_getoverrun]]]*/
{
	syscall_slong_t result;
	result = sys_timer_getoverrun(timerid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_timer_getoverrun]]]*/

/*[[[head:libc_timer_gettime,hash:CRC-32=0xc3ab1637]]]*/
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTERN ATTR_SECTION(".text.crt.timer") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_timer_gettime)(timer_t timerid,
                                         struct itimerspec *value)
/*[[[body:libc_timer_gettime]]]*/
{
	errno_t error;
	error = sys_timer_gettime(timerid, value);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timer_gettime]]]*/

/*[[[head:libc_timer_gettime64,hash:CRC-32=0xc73f1f91]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_gettime64, libc_timer_gettime);
#else /* MAGIC:alias */
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTERN ATTR_SECTION(".text.crt.timer") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_timer_gettime64)(timer_t timerid,
                                           struct itimerspec64 *value)
/*[[[body:libc_timer_gettime64]]]*/
{
	errno_t error;
	error = sys_timer_gettime64(timerid, value);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_timer_gettime64]]]*/

/*[[[head:libc_timer_settime,hash:CRC-32=0x6bb41f34]]]*/
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTERN ATTR_SECTION(".text.crt.timer") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc_timer_settime)(timer_t timerid,
                                         __STDC_INT_AS_UINT_T flags,
                                         struct itimerspec const *__restrict value,
                                         struct itimerspec *__restrict ovalue)
/*[[[body:libc_timer_settime]]]*/
{
	errno_t error;
	error = sys_timer_settime(timerid,
	                          (syscall_ulong_t)(unsigned int)flags,
	                          value, ovalue);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timer_settime]]]*/

/*[[[head:libc_timer_settime64,hash:CRC-32=0x6821e593]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_settime64, libc_timer_settime);
#else /* MAGIC:alias */
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTERN ATTR_SECTION(".text.crt.timer") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc_timer_settime64)(timer_t timerid,
                                           __STDC_INT_AS_UINT_T flags,
                                           struct itimerspec64 const *__restrict value,
                                           struct itimerspec64 *__restrict ovalue)
/*[[[body:libc_timer_settime64]]]*/
{
	errno_t error;
	error = sys_timer_settime64(timerid,
	                            (syscall_ulong_t)(unsigned int)flags,
	                            value, ovalue);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_timer_settime64]]]*/





/*[[[start:exports,hash:CRC-32=0xa6442b3f]]]*/
DEFINE_PUBLIC_ALIAS(clock, libc_clock);
DEFINE_PUBLIC_ALIAS(time, libc_time);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_time64, libc_time64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(time64, libc_time64);
DEFINE_PUBLIC_ALIAS(tzset, libc_tzset);
DEFINE_PUBLIC_ALIAS(stime, libc_stime);
DEFINE_PUBLIC_ALIAS(stime64, libc_stime64);
DEFINE_PUBLIC_ALIAS(__nanosleep, libc_nanosleep);
DEFINE_PUBLIC_ALIAS(nanosleep, libc_nanosleep);
DEFINE_PUBLIC_ALIAS(__clock_getres, libc_clock_getres);
DEFINE_PUBLIC_ALIAS(clock_getres, libc_clock_getres);
DEFINE_PUBLIC_ALIAS(__clock_gettime, libc_clock_gettime);
DEFINE_PUBLIC_ALIAS(clock_gettime, libc_clock_gettime);
DEFINE_PUBLIC_ALIAS(__clock_settime, libc_clock_settime);
DEFINE_PUBLIC_ALIAS(clock_settime, libc_clock_settime);
DEFINE_PUBLIC_ALIAS(timer_create, libc_timer_create);
DEFINE_PUBLIC_ALIAS(timer_delete, libc_timer_delete);
DEFINE_PUBLIC_ALIAS(timer_settime, libc_timer_settime);
DEFINE_PUBLIC_ALIAS(timer_gettime, libc_timer_gettime);
DEFINE_PUBLIC_ALIAS(timer_getoverrun, libc_timer_getoverrun);
DEFINE_PUBLIC_ALIAS(__clock_nanosleep, libc_clock_nanosleep);
DEFINE_PUBLIC_ALIAS(clock_nanosleep, libc_clock_nanosleep);
DEFINE_PUBLIC_ALIAS(__clock_getcpuclockid, libc_clock_getcpuclockid);
DEFINE_PUBLIC_ALIAS(clock_getcpuclockid, libc_clock_getcpuclockid);
DEFINE_PUBLIC_ALIAS(nanosleep64, libc_nanosleep64);
DEFINE_PUBLIC_ALIAS(clock_getres64, libc_clock_getres64);
DEFINE_PUBLIC_ALIAS(clock_gettime64, libc_clock_gettime64);
DEFINE_PUBLIC_ALIAS(clock_settime64, libc_clock_settime64);
DEFINE_PUBLIC_ALIAS(timer_settime64, libc_timer_settime64);
DEFINE_PUBLIC_ALIAS(timer_gettime64, libc_timer_gettime64);
DEFINE_PUBLIC_ALIAS(clock_nanosleep64, libc_clock_nanosleep64);
DEFINE_PUBLIC_ALIAS(getdate, libc_getdate);
DEFINE_PUBLIC_ALIAS(clock_adjtime, libc_clock_adjtime);
DEFINE_PUBLIC_ALIAS(clock_adjtime64, libc_clock_adjtime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TIME_C */
