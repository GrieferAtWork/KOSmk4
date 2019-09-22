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
#ifndef GUARD_LIBC_USER_SYS_TIME_C
#define GUARD_LIBC_USER_SYS_TIME_C 1

#include "../api.h"
#include "sys.time.h"
#include <kos/syscalls.h>
#include <sys/stat.h>
#include <sys/timex.h>
#include <fcntl.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:gettimeofday,hash:CRC-32=0x7609ea3c]]]*/
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.gettimeofday") int
NOTHROW_NCX(LIBCCALL libc_gettimeofday)(struct timeval *__restrict tv,
                                        __timezone_ptr_t tz)
/*[[[body:gettimeofday]]]*/
{
	errno_t result;
	result = sys_gettimeofday(tv, tz);
	return libc_seterrno_syserr(result);
}
/*[[[end:gettimeofday]]]*/

/*[[[head:getitimer,hash:CRC-32=0x213b3a5e]]]*/
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.getitimer") int
NOTHROW_NCX(LIBCCALL libc_getitimer)(__itimer_which_t which,
                                     struct itimerval *curr_value)
/*[[[body:getitimer]]]*/
{
	errno_t result;
	result = sys_getitimer((syscall_ulong_t)which, curr_value);
	return libc_seterrno_syserr(result);
}
/*[[[end:getitimer]]]*/

/*[[[head:setitimer,hash:CRC-32=0x9ca764ad]]]*/
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.setitimer") int
NOTHROW_NCX(LIBCCALL libc_setitimer)(__itimer_which_t which,
                                     struct itimerval const *newval,
                                     struct itimerval *oldval)
/*[[[body:setitimer]]]*/
{
	errno_t result;
	result = sys_setitimer((syscall_ulong_t)which, newval, oldval);
	return libc_seterrno_syserr(result);
}
/*[[[end:setitimer]]]*/

/*[[[head:utimes,hash:CRC-32=0xfa149490]]]*/
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.utimes") int
NOTHROW_NCX(LIBCCALL libc_utimes)(char const *file,
                                  struct timeval const tvp[2])
/*[[[body:utimes]]]*/
{
	errno_t result;
	result = sys_utimes(file, tvp);
	return libc_seterrno_syserr(result);
}
/*[[[end:utimes]]]*/

/*[[[head:futimesat,hash:CRC-32=0xb82d4f22]]]*/
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.futimesat") int
NOTHROW_NCX(LIBCCALL libc_futimesat)(fd_t fd,
                                     char const *file,
                                     struct timeval const tvp[2])
/*[[[body:futimesat]]]*/
{
	errno_t result;
	result = sys_futimesat(fd, file, tvp);
	return libc_seterrno_syserr(result);
}
/*[[[end:futimesat]]]*/

/*[[[head:settimeofday,hash:CRC-32=0x2fd8087f]]]*/
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.adjtime.settimeofday") int
NOTHROW_NCX(LIBCCALL libc_settimeofday)(struct timeval const *tv,
                                        struct timezone const *tz)
/*[[[body:settimeofday]]]*/
{
	errno_t result;
	result = sys_settimeofday(tv, tz);
	return libc_seterrno_syserr(result);
}
/*[[[end:settimeofday]]]*/

/*[[[head:adjtime,hash:CRC-32=0xfde21674]]]*/
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.adjtime.adjtime") int
NOTHROW_NCX(LIBCCALL libc_adjtime)(struct timeval const *delta,
                                   struct timeval *olddelta)
/*[[[body:adjtime]]]*/
{
	struct timeval64 delta64;
	struct timeval64 olddelta64;
	int result;
	if (delta) {
		delta64.tv_sec  = (time64_t)delta->tv_sec;
		delta64.tv_usec = delta->tv_usec;
	}
	result = adjtime64(delta ? &delta64 : NULL,
	                   olddelta ? &olddelta64 : NULL);
	if likely(result == 0 && olddelta) {
		olddelta->tv_sec  = (time32_t)olddelta64.tv_sec;
		olddelta->tv_usec = olddelta64.tv_usec;
	}
	return result;
}
/*[[[end:adjtime]]]*/

/*[[[head:lutimes,hash:CRC-32=0x2c6cff56]]]*/
/* Same as `utimes', but does not follow symbolic links */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.lutimes") int
NOTHROW_NCX(LIBCCALL libc_lutimes)(char const *file,
                                   struct timeval const tvp[2])
/*[[[body:lutimes]]]*/
{
	struct timespec ts[2];
	if (!tvp)
		return utimensat(AT_FDCWD, file, NULL, AT_SYMLINK_NOFOLLOW);
	TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
	TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
	return utimensat(AT_FDCWD, file, ts, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:lutimes]]]*/

/*[[[head:futimes,hash:CRC-32=0xb33ee961]]]*/
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.futimes") int
NOTHROW_NCX(LIBCCALL libc_futimes)(fd_t fd,
                                   struct timeval const tvp[2])
/*[[[body:futimes]]]*/
{
	errno_t result;
	if (!tvp)
		result = sys_utimensat(fd, NULL, NULL, AT_SYMLINK_NOFOLLOW);
	else {
		struct timespec ts[2];
		TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
		TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
		result = sys_utimensat(fd, NULL, ts, AT_SYMLINK_NOFOLLOW);
	}
	return libc_seterrno_syserr(result);
}
/*[[[end:futimes]]]*/

/*[[[head:gettimeofday64,hash:CRC-32=0xbb8e1c36]]]*/
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gettimeofday64, libc_gettimeofday);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.time.gettimeofday64") int
NOTHROW_NCX(LIBCCALL libc_gettimeofday64)(struct timeval64 *__restrict tv,
                                          __timezone_ptr_t tz)
/*[[[body:gettimeofday64]]]*/
{
	errno_t result;
	result = sys_gettimeofday64(tv, tz);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:gettimeofday64]]]*/

/*[[[head:getitimer64,hash:CRC-32=0x3a34ee27]]]*/
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_getitimer64, libc_getitimer);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.getitimer64") int
NOTHROW_NCX(LIBCCALL libc_getitimer64)(__itimer_which_t which,
                                       struct itimerval64 *curr_value)
/*[[[body:getitimer64]]]*/
{
	errno_t result;
	result = sys_getitimer64((syscall_ulong_t)which, curr_value);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:getitimer64]]]*/

/*[[[head:setitimer64,hash:CRC-32=0x8b17a63d]]]*/
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_setitimer64, libc_setitimer);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.time.setitimer64") int
NOTHROW_NCX(LIBCCALL libc_setitimer64)(__itimer_which_t which,
                                       struct itimerval64 const *newval,
                                       struct itimerval64 *oldval)
/*[[[body:setitimer64]]]*/
{
	errno_t result;
	result = sys_setitimer64((syscall_ulong_t)which, newval, oldval);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:setitimer64]]]*/

/*[[[head:utimes64,hash:CRC-32=0x9e404299]]]*/
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_utimes64, libc_utimes);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.utimes64") int
NOTHROW_NCX(LIBCCALL libc_utimes64)(char const *file,
                                    struct timeval64 const tvp[2])
/*[[[body:utimes64]]]*/
{
	errno_t result;
	result = sys_utimes64(file, tvp);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:utimes64]]]*/

/*[[[head:settimeofday64,hash:CRC-32=0x6627348b]]]*/
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_settimeofday64, libc_settimeofday);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.adjtime.settimeofday64") int
NOTHROW_NCX(LIBCCALL libc_settimeofday64)(struct timeval64 const *tv,
                                          struct timezone const *tz)
/*[[[body:settimeofday64]]]*/
{
	errno_t result;
	result = sys_settimeofday64(tv, tz);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:settimeofday64]]]*/

/*[[[head:adjtime64,hash:CRC-32=0x82a73cd5]]]*/
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_adjtime64, libc_adjtime);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.adjtime.adjtime64") int
NOTHROW_NCX(LIBCCALL libc_adjtime64)(struct timeval64 const *delta,
                                     struct timeval64 *olddelta)
/*[[[body:adjtime64]]]*/
{
	int result;
	struct timex64 tntx;
	if (delta) {
		struct timeval64 tmp;
		/* We will do some check here. */
		tmp.tv_sec  = delta->tv_sec + delta->tv_usec / 1000000L;
		tmp.tv_usec = delta->tv_usec % 1000000L;
		tntx.offset = tmp.tv_usec + tmp.tv_sec * 1000000L;
		tntx.modes  = ADJ_OFFSET_SINGLESHOT;
	} else {
		tntx.modes = ADJ_OFFSET_SS_READ;
	}
	result = adjtimex64(&tntx);
	if likely(result == 0) {
		if (olddelta) {
			if (tntx.offset < 0) {
				olddelta->tv_usec = -(-tntx.offset % 1000000);
				olddelta->tv_sec  = -(-tntx.offset / 1000000);
			} else {
				olddelta->tv_usec = tntx.offset % 1000000;
				olddelta->tv_sec  = tntx.offset / 1000000;
			}
		}
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:adjtime64]]]*/

/*[[[head:lutimes64,hash:CRC-32=0xdd76983e]]]*/
/* Same as `utimes', but does not follow symbolic links */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lutimes64, libc_lutimes);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.lutimes64") int
NOTHROW_NCX(LIBCCALL libc_lutimes64)(char const *file,
                                     struct timeval64 const tvp[2])
/*[[[body:lutimes64]]]*/
{
	struct timespec64 ts[2];
	if (!tvp)
		return utimensat64(AT_FDCWD, file, NULL, AT_SYMLINK_NOFOLLOW);
	TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
	TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
	return utimensat64(AT_FDCWD, file, ts, AT_SYMLINK_NOFOLLOW);
}
#endif /* MAGIC:alias */
/*[[[end:lutimes64]]]*/

/*[[[head:futimes64,hash:CRC-32=0x3663dd8]]]*/
/* Same as `utimes', but does not follow symbolic links */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futimes64, libc_lutimes);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.futimes64") int
NOTHROW_NCX(LIBCCALL libc_futimes64)(fd_t fd,
                                     struct timeval64 const tvp[2])
/*[[[body:futimes64]]]*/
{
	errno_t result;
	if (!tvp)
		result = sys_utimensat64(fd, NULL, NULL, AT_SYMLINK_NOFOLLOW);
	else {
		struct timespec64 ts[2];
		TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
		TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
		result = sys_utimensat64(fd, NULL, ts, AT_SYMLINK_NOFOLLOW);
	}
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futimes64]]]*/

/*[[[head:futimesat64,hash:CRC-32=0xddd91621]]]*/
/* Same as `utimes', but takes an open file descriptor instead of a name */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futimesat64, libc_futimesat);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.modify_time.futimesat64") int
NOTHROW_NCX(LIBCCALL libc_futimesat64)(fd_t fd,
                                       char const *file,
                                       struct timeval64 const tvp[2])
/*[[[body:futimesat64]]]*/
{
	errno_t result;
	result = sys_futimesat64(fd, file, tvp);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futimesat64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4df9c20d]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(gettimeofday, libc_gettimeofday);
DEFINE_PUBLIC_WEAK_ALIAS(getitimer, libc_getitimer);
DEFINE_PUBLIC_WEAK_ALIAS(setitimer, libc_setitimer);
DEFINE_PUBLIC_WEAK_ALIAS(utimes, libc_utimes);
DEFINE_PUBLIC_WEAK_ALIAS(futimesat, libc_futimesat);
DEFINE_PUBLIC_WEAK_ALIAS(settimeofday, libc_settimeofday);
DEFINE_PUBLIC_WEAK_ALIAS(adjtime, libc_adjtime);
DEFINE_PUBLIC_WEAK_ALIAS(lutimes, libc_lutimes);
DEFINE_PUBLIC_WEAK_ALIAS(futimes, libc_futimes);
DEFINE_PUBLIC_WEAK_ALIAS(gettimeofday64, libc_gettimeofday64);
DEFINE_PUBLIC_WEAK_ALIAS(getitimer64, libc_getitimer64);
DEFINE_PUBLIC_WEAK_ALIAS(setitimer64, libc_setitimer64);
DEFINE_PUBLIC_WEAK_ALIAS(utimes64, libc_utimes64);
DEFINE_PUBLIC_WEAK_ALIAS(settimeofday64, libc_settimeofday64);
DEFINE_PUBLIC_WEAK_ALIAS(adjtime64, libc_adjtime64);
DEFINE_PUBLIC_WEAK_ALIAS(lutimes64, libc_lutimes64);
DEFINE_PUBLIC_WEAK_ALIAS(futimes64, libc_futimes64);
DEFINE_PUBLIC_WEAK_ALIAS(futimesat64, libc_futimesat64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIME_C */
