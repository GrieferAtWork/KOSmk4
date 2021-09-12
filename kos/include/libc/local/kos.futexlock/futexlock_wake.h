/* HASH CRC-32:0x529af009 */
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
#ifndef __local_futexlock_wake_defined
#define __local_futexlock_wake_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_futex_wakemask) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_futex_wakemask_defined
#define __local___localdep_futex_wakemask_defined 1
#ifdef __CRT_HAVE_futex_wakemask
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_futex_wakemask,(__uintptr_t *__uaddr, __SIZE_TYPE__ __max_wake, __uintptr_t __mask_and, __uintptr_t __mask_or),futex_wakemask,(__uaddr,__max_wake,__mask_and,__mask_or))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futex/futex_wakemask.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_futex_wakemask __LIBC_LOCAL_NAME(futex_wakemask)
#else /* ... */
#undef __local___localdep_futex_wakemask_defined
#endif /* !... */
#endif /* !__local___localdep_futex_wakemask_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
#include <kos/bits/futex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(futexlock_wake) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(futexlock_wake))(__uintptr_t *__ulockaddr, __SIZE_TYPE__ __max_wake) {
	if (!(__hybrid_atomic_load(*__ulockaddr, __ATOMIC_ACQUIRE) & __LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	return (__NAMESPACE_LOCAL_SYM __localdep_futex_wakemask)(&__ulockaddr, 1, (__uintptr_t)~__LFUTEX_WAIT_LOCK_WAITERS, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_futexlock_wake_defined
#define __local___localdep_futexlock_wake_defined 1
#define __localdep_futexlock_wake __LIBC_LOCAL_NAME(futexlock_wake)
#endif /* !__local___localdep_futexlock_wake_defined */
#else /* __CRT_HAVE_futex_wakemask || __CRT_HAVE_lfutex64 || __CRT_HAVE_lfutex */
#undef __local_futexlock_wake_defined
#endif /* !__CRT_HAVE_futex_wakemask && !__CRT_HAVE_lfutex64 && !__CRT_HAVE_lfutex */
#endif /* !__local_futexlock_wake_defined */
