/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_TIME_C
#define GUARD_LIBC_USER_SYS_TIME_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>
#include <sys/stat.h>
#include <sys/timex.h>

#include <fcntl.h>
#include <syscall.h>

#include "sys.time.h"

DECL_BEGIN

/*[[[head:libc_gettimeofday,hash:CRC-32=0xf2548e19]]]*/
/* >> gettimeofday(2), gettimeofday64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_gettimeofday)(struct timeval *__restrict tv,
                                        __timezone_ptr_t tz)
/*[[[body:libc_gettimeofday]]]*/
{
	errno_t result;
	result = sys_gettimeofday(tv, tz);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_gettimeofday]]]*/

/*[[[head:libc_getitimer,hash:CRC-32=0x6311bd3]]]*/
/* >> getitimer(2), getitimer64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_getitimer)(__itimer_which_t which,
                                     struct itimerval *curr_value)
/*[[[body:libc_getitimer]]]*/
{
	errno_t result;
	result = sys_getitimer((syscall_ulong_t)which, curr_value);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getitimer]]]*/

/*[[[head:libc_setitimer,hash:CRC-32=0xd14049a1]]]*/
/* >> setitimer(2), setitimer64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN_OPT(2) ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_setitimer)(__itimer_which_t which,
                                     struct itimerval const *newval,
                                     struct itimerval *oldval)
/*[[[body:libc_setitimer]]]*/
{
	errno_t result;
	result = sys_setitimer((syscall_ulong_t)which, newval, oldval);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setitimer]]]*/

/*[[[head:libc_utimes,hash:CRC-32=0xfcf5370e]]]*/
/* >> utimes(2), utimes64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_utimes)(char const *file,
                                  struct timeval const tvp[2])
/*[[[body:libc_utimes]]]*/
{
	errno_t result;
	result = sys_utimes(file, tvp);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_utimes]]]*/

/*[[[head:libc_futimesat,hash:CRC-32=0x4aad14c1]]]*/
/* >> futimesat(2), futimesat64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_FDARG(1) ATTR_IN(2) ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_futimesat)(fd_t fd,
                                     char const *file,
                                     struct timeval const tvp[2])
/*[[[body:libc_futimesat]]]*/
{
	errno_t result;
	result = sys_futimesat(fd, file, tvp);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futimesat]]]*/

/*[[[head:libc_settimeofday,hash:CRC-32=0x4adcc077]]]*/
/* >> settimeofday(2), settimeofday64(2) */
INTERN ATTR_SECTION(".text.crt.system.adjtime") ATTR_IN_OPT(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_settimeofday)(struct timeval const *tv,
                                        struct timezone const *tz)
/*[[[body:libc_settimeofday]]]*/
{
	errno_t result;
	result = sys_settimeofday(tv, tz);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_settimeofday]]]*/

/*[[[head:libc_adjtime,hash:CRC-32=0x29a5610]]]*/
/* >> adjtime(3), adjtime64(3) */
INTERN ATTR_SECTION(".text.crt.system.adjtime") ATTR_IN_OPT(1) ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_adjtime)(struct timeval const *delta,
                                   struct timeval *olddelta)
/*[[[body:libc_adjtime]]]*/
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
/*[[[end:libc_adjtime]]]*/

/*[[[head:libc_lutimes,hash:CRC-32=0x4eff0d6e]]]*/
/* >> lutimes(2), lutimes64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_lutimes)(char const *file,
                                   struct timeval const tvp[2])
/*[[[body:libc_lutimes]]]*/
{
	struct timespec ts[2];
	if (!tvp)
		return utimensat(AT_FDCWD, file, NULL, AT_SYMLINK_NOFOLLOW);
	TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
	TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
	return utimensat(AT_FDCWD, file, ts, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:libc_lutimes]]]*/

/*[[[head:libc_futimes,hash:CRC-32=0xcafff83f]]]*/
/* >> futimes(2), futimes64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_FDARG(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_futimes)(fd_t fd,
                                   struct timeval const tvp[2])
/*[[[body:libc_futimes]]]*/
{
	errno_t result;
	if (!tvp) {
		result = sys_utimensat(fd, NULL, NULL, AT_SYMLINK_NOFOLLOW);
	} else {
		struct timespec ts[2];
		TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
		TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
		result = sys_utimensat(fd, NULL, ts, AT_SYMLINK_NOFOLLOW);
	}
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futimes]]]*/

/*[[[head:libc_gettimeofday64,hash:CRC-32=0xbf361a8b]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gettimeofday64, libc_gettimeofday);
#else /* MAGIC:alias */
/* >> gettimeofday(2), gettimeofday64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_gettimeofday64)(struct timeval64 *__restrict tv,
                                          __timezone_ptr_t tz)
/*[[[body:libc_gettimeofday64]]]*/
{
	errno_t result;
	result = sys_gettimeofday64(tv, tz);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_gettimeofday64]]]*/

/*[[[head:libc_getitimer64,hash:CRC-32=0x755e48a5]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_getitimer64, libc_getitimer);
#else /* MAGIC:alias */
/* >> getitimer(2), getitimer64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_getitimer64)(__itimer_which_t which,
                                       struct itimerval64 *curr_value)
/*[[[body:libc_getitimer64]]]*/
{
	errno_t result;
	result = sys_getitimer64((syscall_ulong_t)which, curr_value);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_getitimer64]]]*/

/*[[[head:libc_setitimer64,hash:CRC-32=0xa7839f86]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_setitimer64, libc_setitimer);
#else /* MAGIC:alias */
/* >> setitimer(2), setitimer64(2) */
INTERN ATTR_SECTION(".text.crt.time") ATTR_IN_OPT(2) ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_setitimer64)(__itimer_which_t which,
                                       struct itimerval64 const *newval,
                                       struct itimerval64 *oldval)
/*[[[body:libc_setitimer64]]]*/
{
	errno_t result;
	result = sys_setitimer64((syscall_ulong_t)which, newval, oldval);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_setitimer64]]]*/

/*[[[head:libc_utimes64,hash:CRC-32=0x19f7ba80]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_utimes64, libc_utimes);
#else /* MAGIC:alias */
/* >> utimes(2), utimes64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_utimes64)(char const *file,
                                    struct timeval64 const tvp[2])
/*[[[body:libc_utimes64]]]*/
{
	errno_t result;
	result = sys_utimes64(file, tvp);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_utimes64]]]*/

/*[[[head:libc_settimeofday64,hash:CRC-32=0xc1e2742e]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_settimeofday64, libc_settimeofday);
#else /* MAGIC:alias */
/* >> settimeofday(2), settimeofday64(2) */
INTERN ATTR_SECTION(".text.crt.system.adjtime") ATTR_IN_OPT(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_settimeofday64)(struct timeval64 const *tv,
                                          struct timezone const *tz)
/*[[[body:libc_settimeofday64]]]*/
{
	errno_t result;
	result = sys_settimeofday64(tv, tz);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_settimeofday64]]]*/

/*[[[head:libc_adjtime64,hash:CRC-32=0x8c14c52a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_adjtime64, libc_adjtime);
#else /* MAGIC:alias */
/* >> adjtime(3), adjtime64(3) */
INTERN ATTR_SECTION(".text.crt.system.adjtime") ATTR_IN_OPT(1) ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_adjtime64)(struct timeval64 const *delta,
                                     struct timeval64 *olddelta)
/*[[[body:libc_adjtime64]]]*/
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
				olddelta->tv_usec = -(s64)((u64)-tntx.offset % 1000000);
				olddelta->tv_sec  = -(s64)((u64)-tntx.offset / 1000000);
			} else {
				olddelta->tv_usec = tntx.offset % 1000000;
				olddelta->tv_sec  = tntx.offset / 1000000;
			}
		}
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_adjtime64]]]*/

/*[[[head:libc_lutimes64,hash:CRC-32=0x266b88e]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lutimes64, libc_lutimes);
#else /* MAGIC:alias */
/* >> lutimes(2), lutimes64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_lutimes64)(char const *file,
                                     struct timeval64 const tvp[2])
/*[[[body:libc_lutimes64]]]*/
{
	struct timespec64 ts[2];
	if (!tvp)
		return utimensat64(AT_FDCWD, file, NULL, AT_SYMLINK_NOFOLLOW);
	TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
	TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
	return utimensat64(AT_FDCWD, file, ts, AT_SYMLINK_NOFOLLOW);
}
#endif /* MAGIC:alias */
/*[[[end:libc_lutimes64]]]*/

/*[[[head:libc_futimes64,hash:CRC-32=0xf6f2677a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futimes64, libc_lutimes);
#else /* MAGIC:alias */
/* >> lutimes(2), lutimes64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_FDARG(1) ATTR_IN_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_futimes64)(fd_t fd,
                                     struct timeval64 const tvp[2])
/*[[[body:libc_futimes64]]]*/
{
	errno_t result;
	if (!tvp) {
#ifdef SYS_utimensat64
		result = sys_utimensat64(fd, NULL, NULL, AT_SYMLINK_NOFOLLOW);
#elif defined(SYS_utimensat_time64)
		result = sys_utimensat_time64(fd, NULL, NULL, AT_SYMLINK_NOFOLLOW);
#else /* ... */
#error "No way to implement `futimes64()'"
#endif /* !... */
	} else {
		struct timespec64 ts[2];
		TIMEVAL_TO_TIMESPEC(&tvp[0], &ts[0]);
		TIMEVAL_TO_TIMESPEC(&tvp[1], &ts[1]);
#ifdef SYS_utimensat64
		result = sys_utimensat64(fd, NULL, ts, AT_SYMLINK_NOFOLLOW);
#elif defined(SYS_utimensat_time64)
		result = sys_utimensat_time64(fd, NULL, ts, AT_SYMLINK_NOFOLLOW);
#else /* ... */
#error "No way to implement `futimes64()'"
#endif /* !... */
	}
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futimes64]]]*/

/*[[[head:libc_futimesat64,hash:CRC-32=0x2cdba7fd]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futimesat64, libc_futimesat);
#else /* MAGIC:alias */
/* >> futimesat(2), futimesat64(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") ATTR_FDARG(1) ATTR_IN(2) ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_futimesat64)(fd_t fd,
                                       char const *file,
                                       struct timeval64 const tvp[2])
/*[[[body:libc_futimesat64]]]*/
{
	errno_t result;
	result = sys_futimesat64(fd, file, tvp);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futimesat64]]]*/





/*[[[start:exports,hash:CRC-32=0xc32cd66f]]]*/
DEFINE_PUBLIC_ALIAS(__gettimeofday, libc_gettimeofday);
DEFINE_PUBLIC_ALIAS(__libc_gettimeofday, libc_gettimeofday);
DEFINE_PUBLIC_ALIAS(gettimeofday, libc_gettimeofday);
DEFINE_PUBLIC_ALIAS(__getitimer, libc_getitimer);
DEFINE_PUBLIC_ALIAS(__libc_getitimer, libc_getitimer);
DEFINE_PUBLIC_ALIAS(getitimer, libc_getitimer);
DEFINE_PUBLIC_ALIAS(__setitimer, libc_setitimer);
DEFINE_PUBLIC_ALIAS(__libc_setitimer, libc_setitimer);
DEFINE_PUBLIC_ALIAS(setitimer, libc_setitimer);
DEFINE_PUBLIC_ALIAS(__utimes, libc_utimes);
DEFINE_PUBLIC_ALIAS(utimes, libc_utimes);
DEFINE_PUBLIC_ALIAS(futimesat, libc_futimesat);
DEFINE_PUBLIC_ALIAS(__settimeofday, libc_settimeofday);
DEFINE_PUBLIC_ALIAS(__libc_settimeofday, libc_settimeofday);
DEFINE_PUBLIC_ALIAS(settimeofday, libc_settimeofday);
DEFINE_PUBLIC_ALIAS(__adjtime, libc_adjtime);
DEFINE_PUBLIC_ALIAS(adjtime, libc_adjtime);
DEFINE_PUBLIC_ALIAS(lutimes, libc_lutimes);
DEFINE_PUBLIC_ALIAS(futimes, libc_futimes);
DEFINE_PUBLIC_ALIAS(gettimeofday64, libc_gettimeofday64);
DEFINE_PUBLIC_ALIAS(getitimer64, libc_getitimer64);
DEFINE_PUBLIC_ALIAS(setitimer64, libc_setitimer64);
DEFINE_PUBLIC_ALIAS(utimes64, libc_utimes64);
DEFINE_PUBLIC_ALIAS(settimeofday64, libc_settimeofday64);
DEFINE_PUBLIC_ALIAS(adjtime64, libc_adjtime64);
DEFINE_PUBLIC_ALIAS(lutimes64, libc_lutimes64);
DEFINE_PUBLIC_ALIAS(futimes64, libc_futimes64);
DEFINE_PUBLIC_ALIAS(futimesat64, libc_futimesat64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIME_C */
