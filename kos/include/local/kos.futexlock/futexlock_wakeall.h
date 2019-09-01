/* HASH 0x6b29609a */
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
#ifndef __local_futexlock_wakeall_defined
#if (defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_futexlock_wake))
#define __local_futexlock_wakeall_defined 1
/* Dependency: "futexlock_wake" from "kos.futexlock" */
#ifndef ____localdep_futexlock_wake_defined
#define ____localdep_futexlock_wake_defined 1
#if defined(__CRT_HAVE_futexlock_wake)
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_futexlock_wake,(__uintptr_t *__ulockaddr, __SIZE_TYPE__ __max_wake),futexlock_wake,(__ulockaddr,__max_wake))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <local/kos.futexlock/futexlock_wake.h>
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
#define __localdep_futexlock_wake (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_wake))
#else /* CUSTOM: futexlock_wake */
#undef ____localdep_futexlock_wake_defined
#endif /* futexlock_wake... */
#endif /* !____localdep_futexlock_wake_defined */

__NAMESPACE_LOCAL_BEGIN
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__LOCAL_LIBC(futexlock_wakeall) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(futexlock_wakeall))(__uintptr_t *__ulockaddr) {
#line 152 "kos/src/libc/magic/kos.futexlock.c"
	return __localdep_futexlock_wake(__uaddr, (__SIZE_TYPE__)-1);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_futexlock_wake)) */
#endif /* !__local_futexlock_wakeall_defined */
