/* HASH CRC-32:0xf96a4498 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_futex_timedwaitwhile_anybit_defined
#define __local_futex_timedwaitwhile_anybit_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lfutex_defined
#define __local___localdep_lfutex_defined
#if defined(__CRT_HAVE_lfutex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutex64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex64,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futex/lfutex.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lfutex __LIBC_LOCAL_NAME(lfutex)
#endif /* !... */
#endif /* !__local___localdep_lfutex_defined */
__NAMESPACE_LOCAL_END
#include <kos/asm/futex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(futex_timedwaitwhile_anybit) __ATTR_IN(1) __ATTR_IN_OPT(3) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(futex_timedwaitwhile_anybit))(__uintptr_t *__uaddr, __uintptr_t __bitmask, struct timespec const *__rel_timeout) {
	return (__NAMESPACE_LOCAL_SYM __localdep_lfutex)(__uaddr, LFUTEX_WAIT_UNTIL_BITMASK, __bitmask, __rel_timeout, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_futex_timedwaitwhile_anybit_defined
#define __local___localdep_futex_timedwaitwhile_anybit_defined
#define __localdep_futex_timedwaitwhile_anybit __LIBC_LOCAL_NAME(futex_timedwaitwhile_anybit)
#endif /* !__local___localdep_futex_timedwaitwhile_anybit_defined */
#else /* __CRT_HAVE_lfutex64 || __CRT_HAVE_lfutex */
#undef __local_futex_timedwaitwhile_anybit_defined
#endif /* !__CRT_HAVE_lfutex64 && !__CRT_HAVE_lfutex */
#endif /* !__local_futex_timedwaitwhile_anybit_defined */
