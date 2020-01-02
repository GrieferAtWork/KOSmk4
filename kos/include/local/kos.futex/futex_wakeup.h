/* HASH CRC-32:0xd1a8649 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_futex_wakeup_defined
#if (defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex))
#define __local_futex_wakeup_defined 1
#include <hybrid/__atomic.h>

#include <kos/bits/futex.h>
__NAMESPACE_LOCAL_BEGIN
/* Wake all threads waiting for `*UADDR' if there are any threads that are waiting for that address.
 * Same as testing for, and clearing the `LFUTEX_WAIT_LOCK_WAITERS' bit before calling `futex_wakeall()'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__LOCAL_LIBC(futex_wakeup) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(futex_wakeup))(__uintptr_t *__uaddr) {
#line 323 "kos/src/libc/magic/kos.futex.c"
	if (*__uaddr & LFUTEX_WAIT_LOCK_WAITERS) {
		__atomic_fetch_and(*uaddr, ~__LFUTEX_WAIT_LOCK_WAITERS, __ATOMIC_SEQ_CST);
		return futex_wakeall(uaddr);
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)) */
#endif /* !__local_futex_wakeup_defined */
