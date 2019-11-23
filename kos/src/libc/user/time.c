/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_TIME_C
#define GUARD_LIBC_USER_TIME_C 1

#include "../api.h"
#include "time.h"
#include <kos/syscalls.h>


DECL_BEGIN


#undef tzname
#undef __tzname
#undef timezone
#undef __timezone
#undef daylight
#undef __daylight
PUBLIC ATTR_SECTION(".bss.crt.time.timezone.tzname") char *tzname[2]      = { NULL, NULL };
PUBLIC ATTR_SECTION(".bss.crt.time.timezone.timezone") longptr_t timezone = 0;
PUBLIC ATTR_SECTION(".bss.crt.time.timezone.daylight") int daylight       = 0;
DEFINE_PUBLIC_ALIAS(__tzname, tzname);
DEFINE_PUBLIC_ALIAS(__timezone, timezone);
DEFINE_PUBLIC_ALIAS(__daylight, daylight);

DEFINE_NOREL_GLOBAL_META(char *, tzname, ".crt.time.timezone.tzname");
DEFINE_NOREL_GLOBAL_META(longptr_t, timezone, ".crt.time.timezone.timezone");
DEFINE_NOREL_GLOBAL_META(int, daylight, ".crt.time.timezone.daylight");
#define tzname     GET_NOREL_GLOBAL(tzname)
#define timezone   GET_NOREL_GLOBAL(timezone)
#define daylight   GET_NOREL_GLOBAL(daylight)

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

/*[[[head:tzset,hash:CRC-32=0x492f9fc0]]]*/
/* Set time conversion information from the TZ environment variable.
 * If TZ is not defined, a locale-dependent default is used */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.time.tzset") void
NOTHROW_NCX(LIBCCALL libc_tzset)(void)
/*[[[body:tzset]]]*/
{
	CRT_UNIMPLEMENTED("tzset"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:tzset]]]*/




/*[[[head:clock,hash:CRC-32=0xddb0b9af]]]*/
/* Time used by the program so far (user time + system time)
 * The result / CLOCKS_PER_SECOND is program time in seconds */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock") clock_t
NOTHROW_NCX(LIBCCALL libc_clock)(void)
/*[[[body:clock]]]*/
{
	CRT_UNIMPLEMENTED("clock"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:clock]]]*/

/*[[[head:getdate,hash:CRC-32=0x91989807]]]*/
/* Parse the given string as a date specification and return a value
 * representing the value.  The templates from the file identified by
 * the environment variable DATEMSK are used.  In case of an error
 * `getdate_err' is set */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.getdate") __STRUCT_TM *
NOTHROW_NCX(LIBCCALL libc_getdate)(const char *string)
/*[[[body:getdate]]]*/
{
	(void)string;
	CRT_UNIMPLEMENTED("getdate"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getdate]]]*/

/*[[[head:getdate_r,hash:CRC-32=0x300334e2]]]*/
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.getdate_r") int
NOTHROW_NCX(LIBCCALL libc_getdate_r)(const char *__restrict string,
                                     __STRUCT_TM *__restrict resbufp)
/*[[[body:getdate_r]]]*/
{
	(void)string;
	(void)resbufp;
	CRT_UNIMPLEMENTED("getdate_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getdate_r]]]*/

/*[[[head:timespec_get,hash:CRC-32=0xe844bbac]]]*/
/* Set TS to calendar time based in time base BASE */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.timespec_get") int
NOTHROW_NCX(LIBCCALL libc_timespec_get)(struct timespec *ts,
                                        int base)
/*[[[body:timespec_get]]]*/
{
	(void)ts;
	(void)base;
	CRT_UNIMPLEMENTED("timespec_get"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:timespec_get]]]*/

/*[[[head:time,hash:CRC-32=0x76530343]]]*/
/* Return the current time and put it in *TIMER if TIMER is not NULL */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.time.time") time_t
NOTHROW_NCX(LIBCCALL libc_time)(time_t *timer)
/*[[[body:time]]]*/
{
	time_t result;
	result = sys_time(timer);
	return libc_seterrno_syserr(result);
}
/*[[[end:time]]]*/

/*[[[head:time64,hash:CRC-32=0x3895b2a4]]]*/
/* Return the current time and put it in *TIMER if TIMER is not NULL */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_time64, libc_time);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.time.time64") time64_t
NOTHROW_NCX(LIBCCALL libc_time64)(time64_t *timer)
/*[[[body:time64]]]*/
{
	time_t result;
	result = sys_time64(timer);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:time64]]]*/

/*[[[head:stime,hash:CRC-32=0xad3640eb]]]*/
/* Set the system time to *WHEN. This call is restricted to the superuser */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.stime") int
NOTHROW_NCX(LIBCCALL libc_stime)(time_t const *when)
/*[[[body:stime]]]*/
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
/*[[[end:stime]]]*/

/*[[[head:stime64,hash:CRC-32=0x8cb7c7cc]]]*/
/* Set the system time to *WHEN. This call is restricted to the superuser */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_stime64, libc_stime);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.stime64") int
NOTHROW_NCX(LIBCCALL libc_stime64)(time64_t const *when)
/*[[[body:stime64]]]*/
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
/*[[[end:stime64]]]*/


/*[[[head:nanosleep,hash:CRC-32=0xfd20d3e9]]]*/
/* Pause execution for a number of nanoseconds */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.nanosleep") int
NOTHROW_RPC(LIBCCALL libc_nanosleep)(struct timespec const *requested_time,
                                     struct timespec *remaining)
/*[[[body:nanosleep]]]*/
{
	errno_t error;
	error = sys_nanosleep(requested_time, remaining);
	return libc_seterrno_syserr(error);
}
/*[[[end:nanosleep]]]*/

/*[[[head:nanosleep64,hash:CRC-32=0x37a52444]]]*/
/* Pause execution for a number of nanoseconds */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_nanosleep64, libc_nanosleep);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.nanosleep64") int
NOTHROW_RPC(LIBCCALL libc_nanosleep64)(struct timespec64 const *__restrict requested_time,
                                       struct timespec64 *remaining)
/*[[[body:nanosleep64]]]*/
{
	errno_t error;
	error = sys_nanosleep64(requested_time, remaining);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:nanosleep64]]]*/

/*[[[head:clock_settime64,hash:CRC-32=0xe4b49a58]]]*/
/* Set clock CLOCK_ID to value TP */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_settime64, libc_clock_settime);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_settime64") int
NOTHROW_NCX(LIBCCALL libc_clock_settime64)(clockid_t clock_id,
                                           struct timespec64 const *tp)
/*[[[body:clock_settime64]]]*/
{
	errno_t error;
	error = sys_clock_settime64(clock_id, tp);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:clock_settime64]]]*/

/*[[[head:clock_settime,hash:CRC-32=0xa18c2f96]]]*/
/* Set clock CLOCK_ID to value TP */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_settime") int
NOTHROW_NCX(LIBCCALL libc_clock_settime)(clockid_t clock_id,
                                         struct timespec const *tp)
/*[[[body:clock_settime]]]*/
{
	errno_t error;
	error = sys_clock_settime(clock_id, tp);
	return libc_seterrno_syserr(error);
}
/*[[[end:clock_settime]]]*/

/*[[[head:clock_getcpuclockid,hash:CRC-32=0x61427c43]]]*/
/* Return clock ID for CPU-time clock */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_getcpuclockid") int
NOTHROW_NCX(LIBCCALL libc_clock_getcpuclockid)(pid_t pid,
                                               clockid_t *clock_id)
/*[[[body:clock_getcpuclockid]]]*/
{
	(void)pid;
	(void)clock_id;
	CRT_UNIMPLEMENTED("clock_getcpuclockid"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:clock_getcpuclockid]]]*/

/*[[[head:clock_gettime,hash:CRC-32=0x270ca9de]]]*/
/* Get current value of clock CLOCK_ID and store it in TP */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_gettime") int
NOTHROW_NCX(LIBCCALL libc_clock_gettime)(clockid_t clock_id,
                                         struct timespec *tp)
/*[[[body:clock_gettime]]]*/
{
	errno_t error;
	error = sys_clock_gettime(clock_id, tp);
	return libc_seterrno_syserr(error);
}
/*[[[end:clock_gettime]]]*/

/*[[[head:clock_gettime64,hash:CRC-32=0xdafedac9]]]*/
/* Get current value of clock CLOCK_ID and store it in TP */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_gettime64, libc_clock_gettime);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_gettime64") int
NOTHROW_NCX(LIBCCALL libc_clock_gettime64)(clockid_t clock_id,
                                           struct timespec64 *tp)
/*[[[body:clock_gettime64]]]*/
{
	errno_t error;
	error = sys_clock_gettime64(clock_id, tp);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:clock_gettime64]]]*/

/*[[[head:clock_getres,hash:CRC-32=0x43f02de6]]]*/
/* Get resolution of clock CLOCK_ID */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_getres") int
NOTHROW_NCX(LIBCCALL libc_clock_getres)(clockid_t clock_id,
                                        struct timespec *res)
/*[[[body:clock_getres]]]*/
{
	errno_t error;
	error = sys_clock_getres(clock_id, res);
	return libc_seterrno_syserr(error);
}
/*[[[end:clock_getres]]]*/

/*[[[head:clock_getres64,hash:CRC-32=0x9e7fb8bf]]]*/
/* Get resolution of clock CLOCK_ID */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_getres64, libc_clock_getres);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_getres64") int
NOTHROW_NCX(LIBCCALL libc_clock_getres64)(clockid_t clock_id,
                                          struct timespec64 *res)
/*[[[body:clock_getres64]]]*/
{
	errno_t error;
	error = sys_clock_getres64(clock_id, res);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:clock_getres64]]]*/

/*[[[head:clock_nanosleep,hash:CRC-32=0xd84ddb6]]]*/
/* High-resolution sleep with the specified clock */
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_nanosleep") int
NOTHROW_RPC(LIBCCALL libc_clock_nanosleep)(clockid_t clock_id,
                                           int flags,
                                           struct timespec const *__restrict requested_time,
                                           struct timespec *remaining)
/*[[[body:clock_nanosleep]]]*/
{
	errno_t error;
	error = sys_clock_nanosleep(clock_id,
	                            (syscall_ulong_t)(unsigned int)flags,
	                            requested_time, remaining);
	return libc_seterrno_syserr(error);
}
/*[[[end:clock_nanosleep]]]*/

/*[[[head:clock_nanosleep64,hash:CRC-32=0x3037707]]]*/
/* High-resolution sleep with the specified clock */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_clock_nanosleep64, libc_clock_nanosleep);
#else
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.time.clock_nanosleep64") int
NOTHROW_RPC(LIBCCALL libc_clock_nanosleep64)(clockid_t clock_id,
                                             int flags,
                                             struct timespec64 const *requested_time,
                                             struct timespec64 *remaining)
/*[[[body:clock_nanosleep64]]]*/
{
	errno_t error;
	error = sys_clock_nanosleep64(clock_id,
	                              (syscall_ulong_t)(unsigned int)flags,
	                              requested_time, remaining);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:clock_nanosleep64]]]*/

/*[[[head:timer_create,hash:CRC-32=0x80dea55c]]]*/
/* Create new per-process timer using CLOCK_ID */
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timer_create") int
NOTHROW_NCX(LIBCCALL libc_timer_create)(clockid_t clock_id,
                                        struct sigevent *__restrict evp,
                                        timer_t *__restrict timerid)
/*[[[body:timer_create]]]*/
{
	errno_t error;
	error = sys_timer_create(clock_id, evp, timerid);
	return libc_seterrno_syserr(error);
}
/*[[[end:timer_create]]]*/

/*[[[head:timer_delete,hash:CRC-32=0x7803c09c]]]*/
/* Delete timer TIMERID */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.timer.timer_delete") int
NOTHROW_NCX(LIBCCALL libc_timer_delete)(timer_t timerid)
/*[[[body:timer_delete]]]*/
{
	errno_t error;
	error = sys_timer_delete(timerid);
	return libc_seterrno_syserr(error);
}
/*[[[end:timer_delete]]]*/

/*[[[head:timer_getoverrun,hash:CRC-32=0x59f05e2c]]]*/
/* Get expiration overrun for timer TIMERID */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.timer.timer_getoverrun") int
NOTHROW_NCX(LIBCCALL libc_timer_getoverrun)(timer_t timerid)
/*[[[body:timer_getoverrun]]]*/
{
	syscall_slong_t result;
	result = sys_timer_getoverrun(timerid);
	return libc_seterrno_syserr(result);
}
/*[[[end:timer_getoverrun]]]*/

/*[[[head:timer_gettime,hash:CRC-32=0xff66caf9]]]*/
/* Get current value of timer TIMERID and store it in VALUE */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timer_gettime") int
NOTHROW_NCX(LIBCCALL libc_timer_gettime)(timer_t timerid,
                                         struct itimerspec *value)
/*[[[body:timer_gettime]]]*/
{
	errno_t error;
	error = sys_timer_gettime(timerid, value);
	return libc_seterrno_syserr(error);
}
/*[[[end:timer_gettime]]]*/

/*[[[head:timer_gettime64,hash:CRC-32=0xb718214d]]]*/
/* Get current value of timer TIMERID and store it in VALUE */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_gettime64, libc_timer_gettime);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timer_gettime64") int
NOTHROW_NCX(LIBCCALL libc_timer_gettime64)(timer_t timerid,
                                           struct itimerspec64 *value)
/*[[[body:timer_gettime64]]]*/
{
	errno_t error;
	error = sys_timer_gettime64(timerid, value);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:timer_gettime64]]]*/

/*[[[head:timer_settime,hash:CRC-32=0xa408bcc5]]]*/
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timer_settime") int
NOTHROW_NCX(LIBCCALL libc_timer_settime)(timer_t timerid,
                                         int flags,
                                         struct itimerspec const *__restrict value,
                                         struct itimerspec *__restrict ovalue)
/*[[[body:timer_settime]]]*/
{
	errno_t error;
	error = sys_timer_settime(timerid,
	                          (syscall_ulong_t)(unsigned int)flags,
	                          value, ovalue);
	return libc_seterrno_syserr(error);
}
/*[[[end:timer_settime]]]*/

/*[[[head:timer_settime64,hash:CRC-32=0xaff7f5e4]]]*/
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timer_settime64, libc_timer_settime);
#else
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timer_settime64") int
NOTHROW_NCX(LIBCCALL libc_timer_settime64)(timer_t timerid,
                                           int flags,
                                           struct itimerspec64 const *__restrict value,
                                           struct itimerspec64 *__restrict ovalue)
/*[[[body:timer_settime64]]]*/
{
	errno_t error;
	error = sys_timer_settime64(timerid,
	                            (syscall_ulong_t)(unsigned int)flags,
	                            value, ovalue);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:timer_settime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x591e4492]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(clock, libc_clock);
DEFINE_PUBLIC_WEAK_ALIAS(time, libc_time);
DEFINE_PUBLIC_WEAK_ALIAS(time64, libc_time64);
DEFINE_PUBLIC_WEAK_ALIAS(tzset, libc_tzset);
DEFINE_PUBLIC_WEAK_ALIAS(stime, libc_stime);
DEFINE_PUBLIC_WEAK_ALIAS(stime64, libc_stime64);
DEFINE_PUBLIC_WEAK_ALIAS(nanosleep, libc_nanosleep);
DEFINE_PUBLIC_WEAK_ALIAS(__nanosleep, libc_nanosleep);
DEFINE_PUBLIC_WEAK_ALIAS(clock_getres, libc_clock_getres);
DEFINE_PUBLIC_WEAK_ALIAS(__clock_getres, libc_clock_getres);
DEFINE_PUBLIC_WEAK_ALIAS(clock_gettime, libc_clock_gettime);
DEFINE_PUBLIC_WEAK_ALIAS(__clock_gettime, libc_clock_gettime);
DEFINE_PUBLIC_WEAK_ALIAS(clock_settime, libc_clock_settime);
DEFINE_PUBLIC_WEAK_ALIAS(__clock_settime, libc_clock_settime);
DEFINE_PUBLIC_WEAK_ALIAS(timer_create, libc_timer_create);
DEFINE_PUBLIC_WEAK_ALIAS(timer_delete, libc_timer_delete);
DEFINE_PUBLIC_WEAK_ALIAS(timer_settime, libc_timer_settime);
DEFINE_PUBLIC_WEAK_ALIAS(timer_gettime, libc_timer_gettime);
DEFINE_PUBLIC_WEAK_ALIAS(timer_getoverrun, libc_timer_getoverrun);
DEFINE_PUBLIC_WEAK_ALIAS(clock_nanosleep, libc_clock_nanosleep);
DEFINE_PUBLIC_WEAK_ALIAS(__clock_nanosleep, libc_clock_nanosleep);
DEFINE_PUBLIC_WEAK_ALIAS(clock_getcpuclockid, libc_clock_getcpuclockid);
DEFINE_PUBLIC_WEAK_ALIAS(__clock_getcpuclockid, libc_clock_getcpuclockid);
DEFINE_PUBLIC_WEAK_ALIAS(nanosleep64, libc_nanosleep64);
DEFINE_PUBLIC_WEAK_ALIAS(clock_getres64, libc_clock_getres64);
DEFINE_PUBLIC_WEAK_ALIAS(clock_gettime64, libc_clock_gettime64);
DEFINE_PUBLIC_WEAK_ALIAS(clock_settime64, libc_clock_settime64);
DEFINE_PUBLIC_WEAK_ALIAS(timer_settime64, libc_timer_settime64);
DEFINE_PUBLIC_WEAK_ALIAS(timer_gettime64, libc_timer_gettime64);
DEFINE_PUBLIC_WEAK_ALIAS(clock_nanosleep64, libc_clock_nanosleep64);
DEFINE_PUBLIC_WEAK_ALIAS(timespec_get, libc_timespec_get);
DEFINE_PUBLIC_WEAK_ALIAS(getdate, libc_getdate);
DEFINE_PUBLIC_WEAK_ALIAS(getdate_r, libc_getdate_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TIME_C */
