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
#ifndef GUARD_LIBC_USER_TIME_C
#define GUARD_LIBC_USER_TIME_C 1

#include "../api.h"
/**/

#include <kos/exec/idata.h>

#include <stdlib.h>

#include "../libc/globals.h"
#include "../libc/syscalls.h"
#include "time.h"

DECL_BEGIN

/************************************************************************/
/* GLOBAL SYMBOLS: tzname, timezone, daylight, _dstbias                 */
/************************************************************************/
#undef tzname
#undef timezone
#undef daylight
#undef _tzname
#undef _timezone
#undef _daylight
#undef __tzname
#undef __timezone
#undef __daylight
#undef _dstbias
PRIVATE ATTR_SECTION(".bss.crt.time.timezone") char *libc_tzname_buf[2] = { NULL, NULL };
INTERN ATTR_SECTION(".bss.crt.time.timezone") longptr_t libc_timezone = 0;
INTERN ATTR_SECTION(".bss.crt.time.timezone") int libc_daylight = 0;
INTERN ATTR_SECTION(".bss.crt.dos.time.timezone") __LONG32_TYPE__ libc__dstbias = 0;

/* Default string pointed-to by `tzname[0,1]' before `tzset(3)' is called. */
PRIVATE ATTR_SECTION(".rodata.crt.time.timezone")
char const libc_tzname_default[] = "GMT";

INTERN ATTR_SECTION(".text.crt.time.timezone") ATTR_RETNONNULL WUNUSED char **
NOTHROW(LIBCCALL libc_resolve_tzname)(void) {
	if (!libc_tzname_buf[1]) {
		libc_tzname_buf[0] = (char *)libc_tzname_default;
		COMPILER_WRITE_BARRIER();
		libc_tzname_buf[1] = (char *)libc_tzname_default;
	}
	return libc_tzname_buf;
}

/* Exports */
DEFINE_PUBLIC_ALIAS(daylight, libc_daylight);
DEFINE_PUBLIC_ALIAS(_daylight, libc_daylight);
DEFINE_PUBLIC_ALIAS(__daylight, libc_daylight);
DEFINE_PUBLIC_ALIAS(timezone, libc_timezone);
DEFINE_PUBLIC_ALIAS(_timezone, libc_timezone);
DEFINE_PUBLIC_ALIAS(__timezone, libc_timezone);
DEFINE_PUBLIC_IDATA(tzname, libc_resolve_tzname, 2 * __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(_tzname, libc_resolve_tzname, 2 * __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(__tzname, libc_resolve_tzname, 2 * __SIZEOF_POINTER__);
DEFINE_PUBLIC_ALIAS(_dstbias, libc__dstbias);

/* Restore NOREL definitions */
#define tzname   GET_NOREL_GLOBAL(tzname)
#define timezone GET_NOREL_GLOBAL(timezone)
#define daylight GET_NOREL_GLOBAL(daylight)
#define _dstbias GET_NOREL_GLOBAL(_dstbias)




/************************************************************************/
/* MAGIC FUNCTIONS                                                      */
/************************************************************************/

/*[[[head:libc_tzset,hash:CRC-32=0x58b1d4b5]]]*/
/* >> tzset(3)
 * Set time conversion information from the `$TZ' environment variable.
 * If  `$TZ'  is  not  defined,  a  locale-dependent  default  is  used */
INTERN ATTR_SECTION(".text.crt.time") void
NOTHROW_NCX(LIBCCALL libc_tzset)(void)
/*[[[body:libc_tzset]]]*/
{
	char const *tz = getenv("TZ");
	if (!tz)
		tz = "/etc/localtime";
	if (!*tz)
		tz = "Universal";
	if (*tz == ':')
		++tz;
	/* TODO:
	 * https://www.man7.org/linux/man-pages/man3/tzset.3.html
	 * https://www.man7.org/linux/man-pages/man5/tzfile.5.html */
	CRT_UNIMPLEMENTED("tzset"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_tzset]]]*/



/*[[[head:libc_clock_adjtime,hash:CRC-32=0x1182d872]]]*/
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_INOUT(2) int
NOTHROW_NCX(LIBCCALL libc_clock_adjtime)(clockid_t clock_id,
                                         struct timex *utx)
/*[[[body:libc_clock_adjtime]]]*/
/*AUTO*/{
	(void)clock_id;
	(void)utx;
	CRT_UNIMPLEMENTEDF("clock_adjtime(clock_id: %" PRIxN(__SIZEOF_CLOCKID_T__) ", utx: %p)", clock_id, utx); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_clock_adjtime]]]*/

/*[[[head:libc_clock_adjtime64,hash:CRC-32=0x39345566]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_adjtime64, libc_clock_adjtime);
#else /* MAGIC:alias */
/* >> clock_adjtime(2), clock_adjtime64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_INOUT(2) int
NOTHROW_NCX(LIBCCALL libc_clock_adjtime64)(clockid_t clock_id,
                                           struct timex64 *utx)
/*[[[body:libc_clock_adjtime64]]]*/
/*AUTO*/{
	(void)clock_id;
	(void)utx;
	CRT_UNIMPLEMENTEDF("clock_adjtime64(clock_id: %" PRIxN(__SIZEOF_CLOCKID_T__) ", utx: %p)", clock_id, utx); /* TODO */
	return libc_seterrno(ENOSYS);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_adjtime64]]]*/

/*[[[head:libc_time,hash:CRC-32=0xc233bc10]]]*/
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT_OPT(1) time_t
NOTHROW_NCX(LIBCCALL libc_time)(time_t *timer)
/*[[[body:libc_time]]]*/
{
#ifdef SYS_time
	time_t result = sys_time(timer);
	return libc_seterrno_syserr(result);
#else /* SYS_time */
	struct timeval tv;
	errno_t error;
	error = sys_gettimeofday(&tv, NULL);
	if (E_ISERR(error))
		return libc_seterrno_neg(error);
	if (timer)
		*timer = tv.tv_sec;
	return tv.tv_sec;
#endif /* !SYS_time */
}
/*[[[end:libc_time]]]*/

/*[[[head:libc_time64,hash:CRC-32=0x2e5a7db9]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_time64, libc_time);
#else /* MAGIC:alias */
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT_OPT(1) time64_t
NOTHROW_NCX(LIBCCALL libc_time64)(time64_t *timer)
/*[[[body:libc_time64]]]*/
{
#ifdef SYS_time64
	time64_t result = sys_time64(timer);
	return libc_seterrno_syserr(result);
#else /* SYS_time64 */
	struct timeval64 tv;
	errno_t error;
	error = sys_gettimeofday64(&tv, NULL);
	if (E_ISERR(error))
		return libc_seterrno_neg(error);
	if (timer)
		*timer = tv.tv_sec;
	return tv.tv_sec;
#endif /* !SYS_time64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_time64]]]*/

/*[[[head:libc_stime,hash:CRC-32=0xeea72ff6]]]*/
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_stime)(time_t const *when)
/*[[[body:libc_stime]]]*/
{
	errno_t error;
#ifdef SYS_stime
	error = sys_stime(when);
#else /* SYS_stime */
	struct timeval tv;
	tv.tv_sec  = *when;
	tv.tv_usec = 0;
	error = sys_settimeofday(&tv, NULL);
#endif /* !SYS_stime */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_stime]]]*/

/*[[[head:libc_stime64,hash:CRC-32=0xf15a7558]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_stime64, libc_stime);
#else /* MAGIC:alias */
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_stime64)(time64_t const *when)
/*[[[body:libc_stime64]]]*/
{
	errno_t error;
#ifdef SYS_stime64
	error = sys_stime64(when);
#else /* SYS_stime64 */
	struct timeval64 tv;
	tv.tv_sec  = *when;
	tv.tv_usec = 0;
	error = sys_settimeofday64(&tv, NULL);
#endif /* !SYS_stime64 */
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_stime64]]]*/


/*[[[head:libc_nanosleep,hash:CRC-32=0x7ed0a5c6]]]*/
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds
 * @return: 0 : Success
 * @return: -1: [errno=EINTR]  System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: -1: [errno=EINVAL] Invalid `requested_time->tv_nsec' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_nanosleep)(struct timespec const *requested_time,
                                     struct timespec *remaining)
/*[[[body:libc_nanosleep]]]*/
{
	errno_t error;
	error = sys_nanosleep(requested_time, remaining);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_nanosleep]]]*/

/*[[[head:libc_nanosleep64,hash:CRC-32=0xe016a9a6]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_nanosleep64, libc_nanosleep);
#else /* MAGIC:alias */
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds
 * @return: 0 : Success
 * @return: -1: [errno=EINTR]  System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: -1: [errno=EINVAL] Invalid `requested_time->tv_nsec' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(1) ATTR_OUT_OPT(2) int
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

/*[[[head:libc_clock_settime64,hash:CRC-32=0xc2d0ed9a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_settime64, libc_clock_settime);
#else /* MAGIC:alias */
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(2) int
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

/*[[[head:libc_clock_settime,hash:CRC-32=0x1db27616]]]*/
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_clock_settime)(clockid_t clock_id,
                                         struct timespec const *tp)
/*[[[body:libc_clock_settime]]]*/
{
	errno_t error;
	error = sys_clock_settime(clock_id, tp);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_clock_settime]]]*/

/*[[[head:libc_clock_getcpuclockid,hash:CRC-32=0x1b48e07d]]]*/
/* >> clock_getcpuclockid(2)
 * Return clock ID for CPU-time clock
 * @return: 0 :     Success
 * @return: ENOSYS: Not supported
 * @return: EPERM:  You're not allowed to read the CPU-time clock of `pid'
 * @return: ESRCH:  No such process `pid' */
INTERN ATTR_SECTION(".text.crt.time") errno_t
NOTHROW_NCX(LIBCCALL libc_clock_getcpuclockid)(pid_t pid,
                                               clockid_t *clock_id)
/*[[[body:libc_clock_getcpuclockid]]]*/
/*AUTO*/{
	(void)pid;
	(void)clock_id;
	CRT_UNIMPLEMENTEDF("clock_getcpuclockid(pid: %" PRIxN(__SIZEOF_PID_T__) ", clock_id: %p)", pid, clock_id); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_clock_getcpuclockid]]]*/

/*[[[head:libc_clock_gettime,hash:CRC-32=0xdb5b4ac0]]]*/
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_clock_gettime)(clockid_t clock_id,
                                         struct timespec *tp)
/*[[[body:libc_clock_gettime]]]*/
{
	errno_t error;
	error = sys_clock_gettime(clock_id, tp);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_clock_gettime]]]*/

/*[[[head:libc_clock_gettime64,hash:CRC-32=0xdca0a062]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_gettime64, libc_clock_gettime);
#else /* MAGIC:alias */
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(2) int
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

/*[[[head:libc_clock_getres,hash:CRC-32=0xd2268ed8]]]*/
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_clock_getres)(clockid_t clock_id,
                                        struct timespec *res)
/*[[[body:libc_clock_getres]]]*/
{
	errno_t error;
	error = sys_clock_getres(clock_id, res);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_clock_getres]]]*/

/*[[[head:libc_clock_getres64,hash:CRC-32=0xa0ccca94]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_getres64, libc_clock_getres);
#else /* MAGIC:alias */
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_clock_getres64)(clockid_t clock_id,
                                          struct timespec64 *res)
/*[[[body:libc_clock_getres64]]]*/
{
	errno_t error;
	error = sys_clock_getres_time64(clock_id, res);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_getres64]]]*/

/*[[[head:libc_clock_nanosleep,hash:CRC-32=0xac0af5ca]]]*/
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME'
 * @return: 0 :      Success
 * @return: EINTR:   System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: EINVAL:  Invalid `clock_id', `flags' or `requested_time->tv_nsec'
 * @return: ENOTSUP: Clock specified by `clock_id' isn't supported. */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(3) ATTR_OUT_OPT(4) errno_t
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
	/* Posix wants us to return the actual errno code. */
	error = abs(error);
	return error;
}
/*[[[end:libc_clock_nanosleep]]]*/

/*[[[head:libc_clock_nanosleep64,hash:CRC-32=0x3efca500]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_nanosleep64, libc_clock_nanosleep);
#else /* MAGIC:alias */
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME'
 * @return: 0 :      Success
 * @return: EINTR:   System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
 * @return: EINVAL:  Invalid `clock_id', `flags' or `requested_time->tv_nsec'
 * @return: ENOTSUP: Clock specified by `clock_id' isn't supported. */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN(3) ATTR_OUT_OPT(4) errno_t
NOTHROW_RPC(LIBCCALL libc_clock_nanosleep64)(clockid_t clock_id,
                                             __STDC_INT_AS_UINT_T flags,
                                             struct timespec64 const *requested_time,
                                             struct timespec64 *remaining)
/*[[[body:libc_clock_nanosleep64]]]*/
{
	errno_t error;
	error = sys_clock_nanosleep_time64(clock_id,
	                                   (syscall_ulong_t)(unsigned int)flags,
	                                   requested_time, remaining);
	if unlikely(E_ISERR(error))
		error = -error;
	return error; /* Posix wants us to return the actual errno code. */
}
#endif /* MAGIC:alias */
/*[[[end:libc_clock_nanosleep64]]]*/

/*[[[head:libc_timer_create,hash:CRC-32=0x544a8581]]]*/
/* >> timer_create(2)
 * Create new per-process timer using `clock_id' */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_IN_OPT(2) ATTR_OUT(3) int
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

/*[[[head:libc_timer_gettime,hash:CRC-32=0x7f753c2a]]]*/
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_timer_gettime)(timer_t timerid,
                                         struct itimerspec *value)
/*[[[body:libc_timer_gettime]]]*/
{
	errno_t error;
	error = sys_timer_gettime(timerid, value);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timer_gettime]]]*/

/*[[[head:libc_timer_gettime64,hash:CRC-32=0x8906e96b]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_gettime64, libc_timer_gettime);
#else /* MAGIC:alias */
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_OUT(2) int
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

/*[[[head:libc_timer_settime,hash:CRC-32=0x767c85b0]]]*/
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_IN(3) ATTR_OUT_OPT(4) int
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

/*[[[head:libc_timer_settime64,hash:CRC-32=0x48219ed1]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_settime64, libc_timer_settime);
#else /* MAGIC:alias */
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_IN(3) ATTR_OUT_OPT(4) int
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





/*[[[start:exports,hash:CRC-32=0x5d9266fc]]]*/
DEFINE_PUBLIC_ALIAS_P(__time,libc_time,ATTR_OUT_OPT(1),time_t,NOTHROW_NCX,LIBCCALL,(time_t *timer),(timer));
DEFINE_PUBLIC_ALIAS_P(__libc_time,libc_time,ATTR_OUT_OPT(1),time_t,NOTHROW_NCX,LIBCCALL,(time_t *timer),(timer));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_time32,libc_time,ATTR_OUT_OPT(1),time_t,NOTHROW_NCX,LIBCCALL,(time_t *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(time,libc_time,ATTR_OUT_OPT(1),time_t,NOTHROW_NCX,LIBCCALL,(time_t *timer),(timer));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_time64,libc_time64,ATTR_OUT_OPT(1),time64_t,NOTHROW_NCX,LIBCCALL,(time64_t *timer),(timer));
#endif /* __LIBCCALL_IS_LIBDCALL */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__time64,libc_time64,ATTR_OUT_OPT(1),time64_t,NOTHROW_NCX,LIBCCALL,(time64_t *timer),(timer));
DEFINE_PUBLIC_ALIAS_P(time64,libc_time64,ATTR_OUT_OPT(1),time64_t,NOTHROW_NCX,LIBCCALL,(time64_t *timer),(timer));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS_P_VOID(_tzset,libc_tzset,,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(__tzset,libc_tzset,,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(tzset,libc_tzset,,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__stime,libc_stime,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(time_t const *when),(when));
DEFINE_PUBLIC_ALIAS_P(__libc_stime,libc_stime,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(time_t const *when),(when));
DEFINE_PUBLIC_ALIAS_P(stime,libc_stime,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(time_t const *when),(when));
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(stime64,libc_stime64,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(time64_t const *when),(when));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS_P(__nanosleep,libc_nanosleep,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_RPC,LIBCCALL,(struct timespec const *requested_time, struct timespec *remaining),(requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(__libc_nanosleep,libc_nanosleep,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_RPC,LIBCCALL,(struct timespec const *requested_time, struct timespec *remaining),(requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(__libc_nanosleep,libc_nanosleep,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_RPC,LIBCCALL,(struct timespec const *requested_time, struct timespec *remaining),(requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(nanosleep,libc_nanosleep,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_RPC,LIBCCALL,(struct timespec const *requested_time, struct timespec *remaining),(requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(__clock_getres,libc_clock_getres,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec *res),(clock_id,res));
DEFINE_PUBLIC_ALIAS_P(clock_getres,libc_clock_getres,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec *res),(clock_id,res));
DEFINE_PUBLIC_ALIAS_P(__clock_gettime,libc_clock_gettime,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(clock_gettime,libc_clock_gettime,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(__clock_settime,libc_clock_settime,ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec const *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(clock_settime,libc_clock_settime,ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec const *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(timer_create,libc_timer_create,ATTR_IN_OPT(2) ATTR_OUT(3),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct sigevent *__restrict evp, timer_t *__restrict timerid),(clock_id,evp,timerid));
DEFINE_PUBLIC_ALIAS_P(timer_delete,libc_timer_delete,,int,NOTHROW_NCX,LIBCCALL,(timer_t timerid),(timerid));
DEFINE_PUBLIC_ALIAS_P(timer_settime,libc_timer_settime,ATTR_IN(3) ATTR_OUT_OPT(4),int,NOTHROW_NCX,LIBCCALL,(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec const *__restrict value, struct itimerspec *__restrict ovalue),(timerid,flags,value,ovalue));
DEFINE_PUBLIC_ALIAS_P(timer_gettime,libc_timer_gettime,ATTR_OUT_OPT(2),int,NOTHROW_NCX,LIBCCALL,(timer_t timerid, struct itimerspec *value),(timerid,value));
DEFINE_PUBLIC_ALIAS_P(timer_getoverrun,libc_timer_getoverrun,,int,NOTHROW_NCX,LIBCCALL,(timer_t timerid),(timerid));
DEFINE_PUBLIC_ALIAS_P(__clock_nanosleep,libc_clock_nanosleep,ATTR_IN(3) ATTR_OUT_OPT(4),errno_t,NOTHROW_RPC,LIBCCALL,(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec const *__restrict requested_time, struct timespec *remaining),(clock_id,flags,requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(clock_nanosleep,libc_clock_nanosleep,ATTR_IN(3) ATTR_OUT_OPT(4),errno_t,NOTHROW_RPC,LIBCCALL,(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec const *__restrict requested_time, struct timespec *remaining),(clock_id,flags,requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(__clock_getcpuclockid,libc_clock_getcpuclockid,,errno_t,NOTHROW_NCX,LIBCCALL,(pid_t pid, clockid_t *clock_id),(pid,clock_id));
DEFINE_PUBLIC_ALIAS_P(clock_getcpuclockid,libc_clock_getcpuclockid,,errno_t,NOTHROW_NCX,LIBCCALL,(pid_t pid, clockid_t *clock_id),(pid,clock_id));
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__nanosleep64,libc_nanosleep64,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_RPC,LIBCCALL,(struct timespec64 const *__restrict requested_time, struct timespec64 *remaining),(requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(nanosleep64,libc_nanosleep64,ATTR_IN(1) ATTR_OUT_OPT(2),int,NOTHROW_RPC,LIBCCALL,(struct timespec64 const *__restrict requested_time, struct timespec64 *remaining),(requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(__clock_getres64,libc_clock_getres64,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec64 *res),(clock_id,res));
DEFINE_PUBLIC_ALIAS_P(clock_getres64,libc_clock_getres64,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec64 *res),(clock_id,res));
DEFINE_PUBLIC_ALIAS_P(__clock_gettime64,libc_clock_gettime64,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec64 *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(clock_gettime64,libc_clock_gettime64,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec64 *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(__clock_settime64,libc_clock_settime64,ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec64 const *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(clock_settime64,libc_clock_settime64,ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timespec64 const *tp),(clock_id,tp));
DEFINE_PUBLIC_ALIAS_P(__timer_settime64,libc_timer_settime64,ATTR_IN(3) ATTR_OUT_OPT(4),int,NOTHROW_NCX,LIBCCALL,(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec64 const *__restrict value, struct itimerspec64 *__restrict ovalue),(timerid,flags,value,ovalue));
DEFINE_PUBLIC_ALIAS_P(timer_settime64,libc_timer_settime64,ATTR_IN(3) ATTR_OUT_OPT(4),int,NOTHROW_NCX,LIBCCALL,(timer_t timerid, __STDC_INT_AS_UINT_T flags, struct itimerspec64 const *__restrict value, struct itimerspec64 *__restrict ovalue),(timerid,flags,value,ovalue));
DEFINE_PUBLIC_ALIAS_P(__timer_gettime64,libc_timer_gettime64,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(timer_t timerid, struct itimerspec64 *value),(timerid,value));
DEFINE_PUBLIC_ALIAS_P(timer_gettime64,libc_timer_gettime64,ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(timer_t timerid, struct itimerspec64 *value),(timerid,value));
DEFINE_PUBLIC_ALIAS_P(__clock_nanosleep_time64,libc_clock_nanosleep64,ATTR_IN(3) ATTR_OUT_OPT(4),errno_t,NOTHROW_RPC,LIBCCALL,(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec64 const *requested_time, struct timespec64 *remaining),(clock_id,flags,requested_time,remaining));
DEFINE_PUBLIC_ALIAS_P(clock_nanosleep64,libc_clock_nanosleep64,ATTR_IN(3) ATTR_OUT_OPT(4),errno_t,NOTHROW_RPC,LIBCCALL,(clockid_t clock_id, __STDC_INT_AS_UINT_T flags, struct timespec64 const *requested_time, struct timespec64 *remaining),(clock_id,flags,requested_time,remaining));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS_P(clock_adjtime,libc_clock_adjtime,ATTR_INOUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timex *utx),(clock_id,utx));
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P(__clock_adjtime64,libc_clock_adjtime64,ATTR_INOUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timex64 *utx),(clock_id,utx));
DEFINE_PUBLIC_ALIAS_P(clock_adjtime64,libc_clock_adjtime64,ATTR_INOUT(2),int,NOTHROW_NCX,LIBCCALL,(clockid_t clock_id, struct timex64 *utx),(clock_id,utx));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TIME_C */
