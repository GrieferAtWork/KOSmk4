/* HASH CRC-32:0x7f734a3f */
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
#ifndef __local_futexlock_timedwaitwhile_above_defined
#define __local_futexlock_timedwaitwhile_above_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <bits/types.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lfutexlock_defined
#define __local___localdep_lfutexlock_defined 1
#if defined(__CRT_HAVE_lfutexlock64) && defined(__USE_TIME_BITS64)
__CVREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutexlock,(__uintptr_t *__ulockaddr, __uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutexlock64,(__ulockaddr,__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutexlock) && !defined(__USE_TIME_BITS64)
__CVREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutexlock,(__uintptr_t *__ulockaddr, __uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutexlock,(__ulockaddr,__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futexlock/lfutexlock.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lfutexlock __LIBC_LOCAL_NAME(lfutexlock)
#endif /* !... */
#endif /* !__local___localdep_lfutexlock_defined */
__NAMESPACE_LOCAL_END
#include <kos/bits/futex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(futexlock_timedwaitwhile_above) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_above))(__uintptr_t *__ulockaddr, __uintptr_t *__uaddr, __uintptr_t __above_value, struct timespec const *__rel_timeout) {
	return (__NAMESPACE_LOCAL_SYM __localdep_lfutexlock)(__ulockaddr, __uaddr, LFUTEX_WAIT_WHILE_ABOVE, __above_value, __rel_timeout);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_futexlock_timedwaitwhile_above_defined
#define __local___localdep_futexlock_timedwaitwhile_above_defined 1
#define __localdep_futexlock_timedwaitwhile_above __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_above)
#endif /* !__local___localdep_futexlock_timedwaitwhile_above_defined */
#else /* __CRT_HAVE_lfutexlock64 || __CRT_HAVE_lfutexlock */
#undef __local_futexlock_timedwaitwhile_above_defined
#endif /* !__CRT_HAVE_lfutexlock64 && !__CRT_HAVE_lfutexlock */
#endif /* !__local_futexlock_timedwaitwhile_above_defined */
