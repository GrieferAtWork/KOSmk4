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
#ifndef GUARD_LIBC_USER_SYS_TIMERFD_C
#define GUARD_LIBC_USER_SYS_TIMERFD_C 1

#include "../api.h"
#include "sys.timerfd.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:timerfd_create,hash:CRC-32=0xf52726d4]]]*/
/* Return file descriptor for new interval timer source */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.timer.timerfd_create") fd_t
NOTHROW(LIBCCALL libc_timerfd_create)(clockid_t clock_id,
                                      int flags)
/*[[[body:timerfd_create]]]*/
{
	fd_t result;
	result = sys_timerfd_create(clock_id, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:timerfd_create]]]*/

/*[[[head:timerfd_settime,hash:CRC-32=0xf134c1a3]]]*/
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timerfd_settime") int
NOTHROW_NCX(LIBCCALL libc_timerfd_settime)(fd_t ufd,
                                           int flags,
                                           struct itimerspec const *utmr,
                                           struct itimerspec *otmr)
/*[[[body:timerfd_settime]]]*/
{
	errno_t error;
	error = sys_timerfd_settime(ufd, (syscall_ulong_t)flags, utmr, otmr);
	return libc_seterrno_syserr(error);
}
/*[[[end:timerfd_settime]]]*/

/*[[[head:timerfd_gettime,hash:CRC-32=0x3c5cb1be]]]*/
/* Return the next expiration time of UFD */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timerfd_gettime") int
NOTHROW_NCX(LIBCCALL libc_timerfd_gettime)(fd_t ufd,
                                           struct itimerspec *__restrict otmr)
/*[[[body:timerfd_gettime]]]*/
{
	errno_t error;
	error = sys_timerfd_gettime(ufd, otmr);
	return libc_seterrno_syserr(error);
}
/*[[[end:timerfd_gettime]]]*/

/*[[[head:timerfd_settime64,hash:CRC-32=0x8ccf7a5d]]]*/
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timerfd_settime64, libc_timerfd_settime);
#else
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timerfd_settime64") int
NOTHROW_NCX(LIBCCALL libc_timerfd_settime64)(fd_t ufd,
                                             int flags,
                                             struct itimerspec64 const *utmr,
                                             struct itimerspec64 *otmr)
/*[[[body:timerfd_settime64]]]*/
{
	errno_t error;
	error = sys_timerfd_settime64(ufd, (syscall_ulong_t)flags, utmr, otmr);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:timerfd_settime64]]]*/

/*[[[head:timerfd_gettime64,hash:CRC-32=0x1b09caeb]]]*/
/* Return the next expiration time of UFD */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timerfd_gettime64, libc_timerfd_gettime);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.timer.timerfd_gettime64") int
NOTHROW_NCX(LIBCCALL libc_timerfd_gettime64)(fd_t ufd,
                                             struct itimerspec64 *__restrict otmr)
/*[[[body:timerfd_gettime64]]]*/
{
	errno_t error;
	error = sys_timerfd_gettime64(ufd, otmr);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:timerfd_gettime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x819948c6]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(timerfd_create, libc_timerfd_create);
DEFINE_PUBLIC_WEAK_ALIAS(timerfd_settime, libc_timerfd_settime);
DEFINE_PUBLIC_WEAK_ALIAS(timerfd_gettime, libc_timerfd_gettime);
DEFINE_PUBLIC_WEAK_ALIAS(timerfd_settime64, libc_timerfd_settime64);
DEFINE_PUBLIC_WEAK_ALIAS(timerfd_gettime64, libc_timerfd_gettime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMERFD_C */
