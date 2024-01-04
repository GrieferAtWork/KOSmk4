/* HASH CRC-32:0x5fb751fd */
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
#ifndef _KOS_SCHED_SHARED_LOCK_H
#define _KOS_SCHED_SHARED_LOCK_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/bits/shared-lock.h>
#include <bits/types.h>
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <kos/anno.h>

#ifdef __KERNEL__
#include <kernel/types.h> /* ktime_t */
#include <sched/sig.h>
#else /* __KERNEL__ */
#include <bits/os/timespec.h>
#include <kos/asm/futex.h>
#include <kos/syscalls.h>
#endif /* !__KERNEL__ */

#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __KERNEL__
#if __SIZEOF_INT__ < __SIZEOF_POINTER__
#define SHARED_LOCK_INIT               { 0, {}, SIG_INIT }
#define SHARED_LOCK_INIT_LOCKED        { 1, {}, SIG_INIT }
#else /* __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#define SHARED_LOCK_INIT               { 0, SIG_INIT }
#define SHARED_LOCK_INIT_LOCKED        { 1, SIG_INIT }
#endif /* __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define shared_lock_init(self)         (void)(sig_init(&(self)->sl_sig), (self)->sl_lock = 0)
#define shared_lock_init_locked(self)  (void)(sig_init(&(self)->sl_sig), (self)->sl_lock = 1)
#define shared_lock_cinit(self)        (void)(sig_cinit(&(self)->sl_sig), __hybrid_assert((self)->sl_lock == 0))
#define shared_lock_cinit_locked(self) (void)(sig_cinit(&(self)->sl_sig), (self)->sl_lock = 1)
#else /* __KERNEL__ */
#define SHARED_LOCK_INIT               { 0 }
#define SHARED_LOCK_INIT_LOCKED        { 1 }
#define shared_lock_init(self)         (void)((self)->sl_lock = 0)
#define shared_lock_init_locked(self)  (void)((self)->sl_lock = 1)
#define shared_lock_cinit(self)        (void)(__hybrid_assert((self)->sl_lock == 0))
#define shared_lock_cinit_locked(self) (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1)
#endif /* !__KERNEL__ */
#define shared_lock_acquired(self)  (!__shared_lock_available(self))
#define shared_lock_available(self) __shared_lock_available(self)
#ifdef __KERNEL__
#define shared_lock_broadcast_for_fini(self) \
	sig_broadcast_for_fini(&(self)->sl_sig)
#elif defined(__shared_lock_sendall)
#define shared_lock_broadcast_for_fini(self) \
	((self)->sl_lock >= 2 ? __shared_lock_sendall(self) : (void)0)
#endif /* !__KERNEL__ */

#ifdef __shared_lock_tryacquire
/* >> shared_lock_tryacquire(3)
 * Try to acquire a lock to a given `struct shared_lock *self'
 * @return: true:  success
 * @return: false: error */
#define shared_lock_tryacquire(self) __shared_lock_tryacquire(self)
#else /* __shared_lock_tryacquire */
#ifndef shared_lock_tryacquire
#define shared_lock_tryacquire shared_lock_tryacquire
#ifdef __CRT_HAVE_shared_lock_tryacquire
/* >> shared_lock_tryacquire(3)
 * Try to acquire a lock to a given `struct shared_lock *self'
 * @return: true:  success
 * @return: false: error */
__LIBC __ATTR_INOUT(1) __BOOL __NOTHROW_NCX(__FCALL shared_lock_tryacquire)(struct shared_lock *__restrict __self) __CASMNAME_SAME("shared_lock_tryacquire");
#else /* __CRT_HAVE_shared_lock_tryacquire */
#include <libc/local/kos.sched.shared-lock/shared_lock_tryacquire.h>
/* >> shared_lock_tryacquire(3)
 * Try to acquire a lock to a given `struct shared_lock *self'
 * @return: true:  success
 * @return: false: error */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_tryacquire, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __BOOL __NOTHROW_NCX(__FCALL shared_lock_tryacquire)(struct shared_lock *__restrict __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_tryacquire))(__self); })
#endif /* !__CRT_HAVE_shared_lock_tryacquire */
#endif /* !shared_lock_tryacquire */
#endif /* !__shared_lock_tryacquire */



#ifdef __shared_lock_sendone
#ifdef __shared_lock_release_ex
/* >> shared_lock_release_ex(3)
 * Release a lock from a given shared_lock.
 * @return: true:  A waiting thread was signaled.
 * @return: false: No thread was waiting for the lock. */
#define shared_lock_release_ex(self) __shared_lock_release_ex(self)
#else /* __shared_lock_release_ex */
#ifndef shared_lock_release_ex
#define shared_lock_release_ex shared_lock_release_ex
#ifdef __CRT_HAVE_shared_lock_release_ex
/* >> shared_lock_release_ex(3)
 * Release a lock from a given shared_lock.
 * @return: true:  A waiting thread was signaled.
 * @return: false: No thread was waiting for the lock. */
__LIBC __ATTR_INOUT(1) __BOOL __NOTHROW_NCX(__FCALL shared_lock_release_ex)(struct shared_lock *__restrict __self) __CASMNAME_SAME("shared_lock_release_ex");
#elif defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
#include <libc/local/kos.sched.shared-lock/shared_lock_release_ex.h>
/* >> shared_lock_release_ex(3)
 * Release a lock from a given shared_lock.
 * @return: true:  A waiting thread was signaled.
 * @return: false: No thread was waiting for the lock. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_release_ex, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __BOOL __NOTHROW_NCX(__FCALL shared_lock_release_ex)(struct shared_lock *__restrict __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_release_ex))(__self); })
#else /* ... */
#undef shared_lock_release_ex
#endif /* !... */
#endif /* !shared_lock_release_ex */
#endif /* !__shared_lock_release_ex */
#define shared_lock_release(self) (void)shared_lock_release_ex(self)
#endif /* __shared_lock_sendone */

#ifdef __CRT_HAVE_shared_lock_acquire
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
__LIBC __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_lock_acquire)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_acquire");
#elif defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire.h>
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_acquire, __FORCELOCAL __ATTR_ARTIFICIAL __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_lock_acquire)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire))(__self); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire_with_timeout)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_acquire_with_timeout");
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__shared_lock_wait_impl_timeout)
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout.h>
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_acquire_with_timeout, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire_with_timeout)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout))(__self, __abs_timeout); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_lock_waitfor
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
__LIBC __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_lock_waitfor)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_waitfor");
#elif defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor.h>
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_waitfor, __FORCELOCAL __ATTR_ARTIFICIAL __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_lock_waitfor)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor))(__self); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor_with_timeout)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_waitfor_with_timeout");
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__shared_lock_wait_impl_timeout)
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout.h>
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_waitfor_with_timeout, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor_with_timeout)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout))(__self, __abs_timeout); })
#endif /* ... */
#if !defined(__KERNEL__) && defined(__USE_TIME64)
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_lock_acquire_with_timeout64)(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_acquire_with_timeout64");
#elif defined(__shared_lock_wait_impl_timeout64)
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout64.h>
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_acquire_with_timeout64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_lock_acquire_with_timeout64)(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64))(__self, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_lock_waitfor_with_timeout64)(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_waitfor_with_timeout64");
#elif defined(__shared_lock_wait_impl_timeout64)
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout64.h>
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_waitfor_with_timeout64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_lock_waitfor_with_timeout64)(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64))(__self, __abs_timeout); })
#endif /* ... */
#endif /* !__KERNEL__ && __USE_TIME64 */


#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#ifdef __CRT_HAVE_shared_lock_acquire_nx
/* >> shared_lock_acquire_nx(3)
 * Acquire a lock to the given shared_lock.
 * @return: true:  Successfully acquired a lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire_nx)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_acquire_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_nx.h>
/* >> shared_lock_acquire_nx(3)
 * Acquire a lock to the given shared_lock.
 * @return: true:  Successfully acquired a lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_acquire_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire_nx)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire_nx))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_lock_acquire_with_timeout_nx
/* >> shared_lock_acquire_with_timeout_nx(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire_with_timeout_nx)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_acquire_with_timeout_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout_nx.h>
/* >> shared_lock_acquire_with_timeout_nx(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_acquire_with_timeout_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire_with_timeout_nx)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout_nx))(__self, __abs_timeout); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_lock_waitfor_nx
/* >> shared_lock_waitfor_nx(3)
 * Wait that `self' becomes available.
 * @return: true:  The lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor_nx)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_waitfor_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_nx.h>
/* >> shared_lock_waitfor_nx(3)
 * Wait that `self' becomes available.
 * @return: true:  The lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_waitfor_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor_nx)(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor_nx))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_lock_waitfor_with_timeout_nx
/* >> shared_lock_waitfor_with_timeout_nx(3)
 * Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor_with_timeout_nx)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) __CASMNAME_SAME("shared_lock_waitfor_with_timeout_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout_nx.h>
/* >> shared_lock_waitfor_with_timeout_nx(3)
 * Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_lock_waitfor_with_timeout_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor_with_timeout_nx)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout_nx))(__self, __abs_timeout); })
#endif /* ... */
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#ifdef __cplusplus
extern "C++" {
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_acquire,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_acquire,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__shared_lock_wait_impl_timeout)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout.h>
extern "C++" {
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_waitfor,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_waitfor,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__shared_lock_wait_impl_timeout)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout.h>
extern "C++" {
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout))(__self, __abs_timeout); }
#endif /* ... */
} /* extern "C++" */
#if !defined(__KERNEL__) && defined(__USE_TIME64)
extern "C++" {
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_acquire,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_acquire,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__shared_lock_wait_impl_timeout64)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout64.h>
extern "C++" {
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_lock_acquire)(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_waitfor,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_waitfor,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__shared_lock_wait_impl_timeout64)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout64.h>
extern "C++" {
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_lock_waitfor)(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64))(__self, __abs_timeout); }
#endif /* ... */
} /* extern "C++" */
#endif /* !__KERNEL__ && __USE_TIME64 */
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
extern "C++" {
#ifdef __CRT_HAVE_shared_lock_acquire_with_timeout_nx
/* >> shared_lock_acquire_with_timeout_nx(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_acquire_nx,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout_nx,(__self,__abs_timeout))
#elif defined(__KERNEL__)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout_nx.h>
extern "C++" {
/* >> shared_lock_acquire_with_timeout_nx(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_acquire_nx)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout_nx))(__self, __abs_timeout); }
#endif /* ... */
#ifdef __CRT_HAVE_shared_lock_waitfor_with_timeout_nx
/* >> shared_lock_waitfor_with_timeout_nx(3)
 * Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,shared_lock_waitfor_nx,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout_nx,(__self,__abs_timeout))
#elif defined(__KERNEL__)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout_nx.h>
extern "C++" {
/* >> shared_lock_waitfor_with_timeout_nx(3)
 * Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_lock_waitfor_nx)(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, E_INTERRUPT) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout_nx))(__self, __abs_timeout); }
#endif /* ... */
} /* extern "C++" */
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_shared_lock_acquire_1 (shared_lock_acquire)
#define __PRIVATE_shared_lock_acquire_2 shared_lock_acquire_with_timeout
#define __PRIVATE_shared_lock_waitfor_1 (shared_lock_waitfor)
#define __PRIVATE_shared_lock_waitfor_2 shared_lock_waitfor_with_timeout
#define shared_lock_acquire(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_lock_acquire_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_lock_waitfor(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_lock_waitfor_, (__VA_ARGS__))(__VA_ARGS__)
#if !defined(__KERNEL__) && defined(__USE_TIME64)
#define __PRIVATE_shared_lock_acquire64_1 (shared_lock_acquire)
#define __PRIVATE_shared_lock_acquire64_2 shared_lock_acquire_with_timeout64
#define __PRIVATE_shared_lock_waitfor64_1 (shared_lock_waitfor)
#define __PRIVATE_shared_lock_waitfor64_2 shared_lock_waitfor_with_timeout64
#define shared_lock_acquire64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_lock_acquire64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_lock_waitfor64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_lock_waitfor64_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__KERNEL__ && __USE_TIME64 */
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#define __PRIVATE_shared_lock_acquire_nx_1 (shared_lock_acquire_nx)
#define __PRIVATE_shared_lock_acquire_nx_2 shared_lock_acquire_with_timeout_nx
#define __PRIVATE_shared_lock_waitfor_nx_1 (shared_lock_waitfor_nx)
#define __PRIVATE_shared_lock_waitfor_nx_2 shared_lock_waitfor_with_timeout_nx
#define shared_lock_acquire_nx(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_lock_acquire_nx_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_lock_waitfor_nx(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_lock_waitfor_nx_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#endif /* ... */


#ifdef __KERNEL__
/* Shared-lock polling functions. */
#define shared_lock_pollconnect_ex(self, cb) cb(&(self)->sl_sig)
#define shared_lock_poll_unlikely_ex(self, cb) \
	(shared_lock_pollconnect_ex(self, cb),     \
	 shared_lock_available(self))
#ifdef __OPTIMIZE_SIZE__
#define shared_lock_poll_ex(self, cb) \
	shared_lock_poll_unlikely_ex(self, cb)
#else /* __OPTIMIZE_SIZE__ */
#define shared_lock_poll_ex(self, cb)       \
	(shared_lock_available(self) ||         \
	 (shared_lock_pollconnect_ex(self, cb), \
	  shared_lock_available(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#define shared_lock_pollconnect(self)   shared_lock_pollconnect_ex(self, task_connect_for_poll)
#define shared_lock_poll(self)          shared_lock_poll_ex(self, task_connect_for_poll)
#define shared_lock_poll_unlikely(self) shared_lock_poll_unlikely_ex(self, task_connect_for_poll)
#endif /* __KERNEL__ */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SCHED_SHARED_LOCK_H */
