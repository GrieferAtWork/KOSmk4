/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_THREADS_C
#define GUARD_LIBC_USER_THREADS_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <pthread.h>

#include "pthread.h"
#include "threads.h"

DECL_BEGIN

/*[[[head:libc_thrd_sleep,hash:CRC-32=0x9cd378f9]]]*/
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_thrd_sleep)(struct timespec const *time_point,
                                      struct timespec *remaining)
/*[[[body:libc_thrd_sleep]]]*/
{
	errno_t error;
	error = sys_nanosleep(time_point, remaining);
	if likely(E_ISOK(error))
		return 0;
	if (error == -EINTR)
		return -1;
	return -2;
}
/*[[[end:libc_thrd_sleep]]]*/

/*[[[head:libc_thrd_sleep64,hash:CRC-32=0x9a6a415f]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_thrd_sleep64, libc_thrd_sleep);
#else /* MAGIC:alias */
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_ACCESS_RO(1) ATTR_ACCESS_WR_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_thrd_sleep64)(struct timespec64 const *time_point,
                                        struct timespec64 *remaining)
/*[[[body:libc_thrd_sleep64]]]*/
{
#ifdef __NR_nanosleep64
	errno_t error;
	error = sys_nanosleep64(time_point, remaining);
	if likely(E_ISOK(error))
		return 0;
	if (error == -EINTR)
		return -1;
	return -2;
#else /* __NR_nanosleep64 */
	int result;
	struct timespec32 tp32, rm32;
	tp32.tv_sec  = (time32_t)time_point->tv_sec;
	tp32.tv_nsec = time_point->tv_nsec;
	result = thrd_sleep(&tp32, remaining ? &rm32 : NULL);
	if ((result != 0) && remaining) {
		remaining->tv_sec  = (time64_t)rm32.tv_sec;
		remaining->tv_nsec = rm32.tv_nsec;
	}
	return result;
#endif /* !__NR_nanosleep64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_thrd_sleep64]]]*/


/*[[[start:exports,hash:CRC-32=0x6da5b87c]]]*/
DEFINE_PUBLIC_ALIAS(thrd_sleep, libc_thrd_sleep);
DEFINE_PUBLIC_ALIAS(thrd_sleep64, libc_thrd_sleep64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_THREADS_C */
