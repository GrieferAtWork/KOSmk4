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
#ifndef GUARD_LIBC_USER_TIME_C
#define GUARD_LIBC_USER_TIME_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h>

#include "time.h"
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


/*[[[start:implementation]]]*/

/*[[[head:libc_tzset,hash:CRC-32=0x8eab8534]]]*/
/* Set time conversion information from the TZ environment variable.
 * If TZ is not defined, a locale-dependent default is used */
INTERN ATTR_SECTION(".text.crt.time") void
NOTHROW_NCX(LIBCCALL libc_tzset)(void)
/*[[[body:libc_tzset]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("tzset"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_tzset]]]*/




/*[[[head:libc_clock,hash:CRC-32=0xfee125c9]]]*/
/* Time used by the program so far (user time + system time)
 * The result / CLOCKS_PER_SECOND is program time in seconds */
INTERN ATTR_SECTION(".text.crt.time") WUNUSED clock_t
NOTHROW_NCX(LIBCCALL libc_clock)(void)
/*[[[body:libc_clock]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("clock"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clock]]]*/

/*[[[head:libc_getdate,hash:CRC-32=0x173db77]]]*/
/* Parse the given string as a date specification and return a value
 * representing the value.  The templates from the file identified by
 * the environment variable DATEMSK are used.  In case of an error
 * `getdate_err' is set */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1)) __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_getdate)(const char *string)
/*[[[body:libc_getdate]]]*/
/*AUTO*/{
	(void)string;
	CRT_UNIMPLEMENTED("getdate"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getdate]]]*/


/*[[[head:libc_timespec_get,hash:CRC-32=0xa4d83ba3]]]*/
/* Set TS to calendar time based in time base BASE */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_timespec_get)(struct timespec *ts,
                                        __STDC_INT_AS_UINT_T base)
/*[[[body:libc_timespec_get]]]*/
/*AUTO*/{
	(void)ts;
	(void)base;
	CRT_UNIMPLEMENTED("timespec_get"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_timespec_get]]]*/

/*[[[head:libc_time,hash:CRC-32=0x30ecd375]]]*/
/* Return the current time and put it in *TIMER if TIMER is not NULL */
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

/*[[[head:libc_time64,hash:CRC-32=0xef326569]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_time64, libc_time);
#else /* MAGIC:alias */
/* Return the current time and put it in *TIMER if TIMER is not NULL */
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

/*[[[head:libc_stime,hash:CRC-32=0x48f0c454]]]*/
/* Set the system time to *WHEN. This call is restricted to the superuser */
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

/*[[[head:libc_stime64,hash:CRC-32=0xaee27dcb]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_stime64, libc_stime);
#else /* MAGIC:alias */
/* Set the system time to *WHEN. This call is restricted to the superuser */
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


/*[[[head:libc_nanosleep,hash:CRC-32=0x47540e17]]]*/
/* Pause execution for a number of nanoseconds */
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

/*[[[head:libc_nanosleep64,hash:CRC-32=0xdb3e1fe1]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_nanosleep64, libc_nanosleep);
#else /* MAGIC:alias */
/* Pause execution for a number of nanoseconds */
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

/*[[[head:libc_clock_settime64,hash:CRC-32=0xb1ca6bc9]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_settime64, libc_clock_settime);
#else /* MAGIC:alias */
/* Set clock CLOCK_ID to value TP */
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

/*[[[head:libc_clock_settime,hash:CRC-32=0x38b64b92]]]*/
/* Set clock CLOCK_ID to value TP */
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

/*[[[head:libc_clock_getcpuclockid,hash:CRC-32=0x209f65d6]]]*/
/* Return clock ID for CPU-time clock */
INTERN ATTR_SECTION(".text.crt.time") int
NOTHROW_NCX(LIBCCALL libc_clock_getcpuclockid)(pid_t pid,
                                               clockid_t *clock_id)
/*[[[body:libc_clock_getcpuclockid]]]*/
/*AUTO*/{
	(void)pid;
	(void)clock_id;
	CRT_UNIMPLEMENTED("clock_getcpuclockid"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_clock_getcpuclockid]]]*/

/*[[[head:libc_clock_gettime,hash:CRC-32=0xe8fee769]]]*/
/* Get current value of clock CLOCK_ID and store it in TP */
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

/*[[[head:libc_clock_gettime64,hash:CRC-32=0x347e0759]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_gettime64, libc_clock_gettime);
#else /* MAGIC:alias */
/* Get current value of clock CLOCK_ID and store it in TP */
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

/*[[[head:libc_clock_getres,hash:CRC-32=0x3783c432]]]*/
/* Get resolution of clock CLOCK_ID */
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

/*[[[head:libc_clock_getres64,hash:CRC-32=0xd2cbbcad]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_getres64, libc_clock_getres);
#else /* MAGIC:alias */
/* Get resolution of clock CLOCK_ID */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_clock_getres64)(clockid_t clock_id,
                                          struct timespec64 *res)
/*[[[body:libc_clock_getres64]]]*/
{
	errno_t error;
	error = sys_clock_getres64(clock_id, res);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_getres64]]]*/

/*[[[head:libc_clock_nanosleep,hash:CRC-32=0x66c50c87]]]*/
/* High-resolution sleep with the specified clock */
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

/*[[[head:libc_clock_nanosleep64,hash:CRC-32=0x7fe07179]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_nanosleep64, libc_clock_nanosleep);
#else /* MAGIC:alias */
/* High-resolution sleep with the specified clock */
INTERN ATTR_SECTION(".text.crt.time") NONNULL((3)) int
NOTHROW_RPC(LIBCCALL libc_clock_nanosleep64)(clockid_t clock_id,
                                             __STDC_INT_AS_UINT_T flags,
                                             struct timespec64 const *requested_time,
                                             struct timespec64 *remaining)
/*[[[body:libc_clock_nanosleep64]]]*/
{
	errno_t error;
	error = sys_clock_nanosleep64(clock_id,
	                              (syscall_ulong_t)(unsigned int)flags,
	                              requested_time, remaining);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_nanosleep64]]]*/

/*[[[head:libc_timer_create,hash:CRC-32=0x5714465e]]]*/
/* Create new per-process timer using CLOCK_ID */
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

/*[[[head:libc_timer_delete,hash:CRC-32=0x32582c8e]]]*/
/* Delete timer TIMERID */
INTERN ATTR_SECTION(".text.crt.timer") int
NOTHROW_NCX(LIBCCALL libc_timer_delete)(timer_t timerid)
/*[[[body:libc_timer_delete]]]*/
{
	errno_t error;
	error = sys_timer_delete(timerid);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timer_delete]]]*/

/*[[[head:libc_timer_getoverrun,hash:CRC-32=0x2c7c508a]]]*/
/* Get expiration overrun for timer TIMERID */
INTERN ATTR_SECTION(".text.crt.timer") int
NOTHROW_NCX(LIBCCALL libc_timer_getoverrun)(timer_t timerid)
/*[[[body:libc_timer_getoverrun]]]*/
{
	syscall_slong_t result;
	result = sys_timer_getoverrun(timerid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_timer_getoverrun]]]*/

/*[[[head:libc_timer_gettime,hash:CRC-32=0x8e60ba37]]]*/
/* Get current value of timer TIMERID and store it in VALUE */
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

/*[[[head:libc_timer_gettime64,hash:CRC-32=0xb3484657]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_gettime64, libc_timer_gettime);
#else /* MAGIC:alias */
/* Get current value of timer TIMERID and store it in VALUE */
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

/*[[[head:libc_timer_settime,hash:CRC-32=0x123033ad]]]*/
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
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

/*[[[head:libc_timer_settime64,hash:CRC-32=0x7be61ba6]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_settime64, libc_timer_settime);
#else /* MAGIC:alias */
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
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

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x500dacb3]]]*/
DEFINE_PUBLIC_ALIAS(clock, libc_clock);
DEFINE_PUBLIC_ALIAS(time, libc_time);
DEFINE_PUBLIC_ALIAS(_time64, libc_time64);
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
DEFINE_PUBLIC_ALIAS(timespec_get, libc_timespec_get);
DEFINE_PUBLIC_ALIAS(getdate, libc_getdate);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TIME_C */
