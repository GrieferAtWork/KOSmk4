/* HASH CRC-32:0x524a2ef9 */
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
#ifndef __local_shared_lock_waitfor_with_timeout64_defined
#define __local_shared_lock_waitfor_with_timeout64_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <kos/anno.h>
#include <kos/bits/shared-lock.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_LFutexExprI64_except_defined
#define __local___localdep_LFutexExprI64_except_defined
#if defined(__CRT_HAVE_LFutexExprI) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO_OPT(4) __ATTR_NONNULL((1, 3)),int,__THROWING,__localdep_LFutexExprI64_except,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__expr, struct __timespec64 const *__timeout, unsigned int __timeout_flags),LFutexExprI,(__ulockaddr,__base,__expr,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_LFutexExprI64)
__NAMESPACE_LOCAL_END
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO_OPT(4) __ATTR_NONNULL((1, 3)),int,__THROWING,__localdep_LFutexExprI64_except,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__expr, struct __timespec64 const *__timeout, unsigned int __timeout_flags),LFutexExprI64,(__ulockaddr,__base,__expr,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futexexpr/LFutexExprI64_except.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_LFutexExprI64_except __LIBC_LOCAL_NAME(LFutexExprI64_except)
#else /* ... */
#undef __local___localdep_LFutexExprI64_except_defined
#endif /* !... */
#endif /* !__local___localdep_LFutexExprI64_except_defined */
__NAMESPACE_LOCAL_END
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
#ifndef __SHARED_LOCK_WAITEXPR_DEFINED
#define __SHARED_LOCK_WAITEXPR_DEFINED
__NAMESPACE_LOCAL_BEGIN
static struct lfutexexpr const __shared_lock_waitexpr[] = {
	/* Wait until `sl_lock == 0' */
	LFUTEXEXPR_INIT(__builtin_offsetof(struct shared_lock, sl_lock), LFUTEX_WAIT_UNTIL, 0, 0),
	LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
};
__NAMESPACE_LOCAL_END
#endif /* !__SHARED_LOCK_WAITEXPR_DEFINED */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_waitfor_with_timeout64) __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL
(__FCALL __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64))(struct shared_lock *__restrict __self, struct __timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	while (__hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(__self->sl_sig, 1, __ATOMIC_SEQ_CST);
		if ((__NAMESPACE_LOCAL_SYM __localdep_LFutexExprI64_except)(&__self->sl_sig, __self,
		                         __NAMESPACE_LOCAL_SYM __shared_lock_waitexpr, __abs_timeout,
		                         LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE |
		                         LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL) < 0)
			return 0;
	}
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#define __local___localdep_shared_lock_waitfor_with_timeout64_defined
#define __localdep_shared_lock_waitfor_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64)
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout64_defined */
#else /* __CRT_HAVE_LFutexExprI64 || __CRT_HAVE_LFutexExprI || (__cplusplus && __KOS__ && (__CRT_HAVE_LFutexExpr64 || __CRT_HAVE_LFutexExpr)) */
#undef __local_shared_lock_waitfor_with_timeout64_defined
#endif /* !__CRT_HAVE_LFutexExprI64 && !__CRT_HAVE_LFutexExprI && (!__cplusplus || !__KOS__ || (!__CRT_HAVE_LFutexExpr64 && !__CRT_HAVE_LFutexExpr)) */
#endif /* !__local_shared_lock_waitfor_with_timeout64_defined */
