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

%[define_replacement(lfutex_t = __uintptr_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]
%[default:section(".text.crt{|.dos}.sched.futex")]
%[default:nodos]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/bits/shared-lock.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/__assert.h>
)]%[insert:prefix(
#include <hybrid/__atomic.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

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
}
@@>> shared_lock_tryacquire(3)
@@Try to acquire a lock to a given `struct shared_lock *self'
@@@return: true:  success
@@@return: false: error
[[cc(__FCALL), guard(shared_lock_tryacquire)]]
[[decl_include("<kos/bits/shared-lock.h>")]]
[[impl_include("<kos/bits/shared-lock.h>", "<hybrid/__atomic.h>")]]
$bool shared_lock_tryacquire([[inout]] struct shared_lock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	return __shared_lock_tryacquire(self);
@@pp_else@@
	unsigned int lockword;
	do {
		lockword = __hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE);
		if ((lockword & ~__SHARED_LOCK_UNLOCKED_WAITING) != 0)
			return false; /* Lock is acquired */
	} while (!__hybrid_atomic_cmpxch_weak(&self->@sl_lock@, lockword,
	                                      lockword ? 2 : 1, /* Set canonical lock state */
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	return true;
@@pp_endif@@
}
%{
#endif /* !__shared_lock_tryacquire */



#ifdef __shared_lock_sendone
#ifdef __shared_lock_release_ex
/* >> shared_lock_release_ex(3)
 * Release a lock from a given shared_lock.
 * @return: true:  A waiting thread was signaled.
 * @return: false: No thread was waiting for the lock. */
#define shared_lock_release_ex(self) __shared_lock_release_ex(self)
#else /* __shared_lock_release_ex */
}

@@>> shared_lock_release_ex(3)
@@Release a lock from a given shared_lock.
@@@return: true:  A waiting thread was signaled.
@@@return: false: No thread was waiting for the lock.
[[cc(__FCALL), guard(shared_lock_release_ex)]]
[[decl_include("<kos/bits/shared-lock.h>")]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall)))]]
[[impl_include("<kos/bits/shared-lock.h>", "<hybrid/__atomic.h>")]]
$bool shared_lock_release_ex([[inout]] struct shared_lock *__restrict self) {
@@pp_ifdef __shared_lock_release_ex@@
	return __shared_lock_release_ex(self);
@@pp_else@@
	unsigned int lockword;
	do {
		lockword = __hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE);
		__hybrid_assertf(lockword > 0 && lockword < __SHARED_LOCK_UNLOCKED_WAITING,
		                 "Lock is not held by anyone (lockword: %#x)", lockword);
		if (lockword >= 2) {
			/* There (might be) are waiting threads */
			__hybrid_atomic_store(&self->@sl_lock@,
			                      __SHARED_LOCK_UNLOCKED_WAITING,
			                      __ATOMIC_RELEASE);
			if (__shared_lock_sendone(self))
				return true;

			/* Apparently, there actually aren't any waiting threads...
			 * -> Try to clear the waiting-threads-are-present flag */
			if (__hybrid_atomic_cmpxch(&self->@sl_lock@, __SHARED_LOCK_UNLOCKED_WAITING, 0,
			                           __ATOMIC_RELEASE, __ATOMIC_RELAXED)) {
				/* Make sure that  there really aren't  any waiting  threads
				 * (just in case a thread came by after we read the lockword
				 * above) */
				if (__shared_lock_sendall(self))
					return true;
			}
			break;
		}

		/* There are no waiting threads */
	} while (!__hybrid_atomic_cmpxch_weak(&self->@sl_lock@, 1, 0,
	                                      __ATOMIC_RELEASE,
	                                      __ATOMIC_RELAXED));
	/* No-one was waiting for the lock */
	return false;
@@pp_endif@@
}
%{
#endif /* !__shared_lock_release_ex */
#define shared_lock_release(self) (void)shared_lock_release_ex(self)
#endif /* __shared_lock_sendone */

}


@@>> shared_lock_acquire(3)
@@Acquire a lock to the given shared_lock.
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__KERNEL__) || defined(__shared_lock_wait_impl))]]
[[impl_include("<kos/bits/shared-lock.h>")]]
void shared_lock_acquire([[inout]] struct shared_lock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_tryacquire(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__shared_lock_tryacquire(self)) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@(@KTIME_INFINITE@);
	}
success:
	;
@@pp_else@@
	__shared_lock_acquire_or_wait_impl(self, {
		__shared_lock_wait_impl(self);
	});
@@pp_endif@@
}


@@>> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
@@Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
@@@return: true:  Successfully acquired a lock.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_lock_acquire_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_lock_acquire_with_timeout64")]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__KERNEL__) || defined(__shared_lock_wait_impl_timeout))]]
[[impl_include("<kos/bits/shared-lock.h>")]]
$bool shared_lock_acquire_with_timeout([[inout]] struct shared_lock *__restrict self,
                                       __shared_lock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_tryacquire(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__shared_lock_tryacquire(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	__shared_lock_acquire_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout(self, abs_timeout))
			return false; /* Timeout */
	});
@@pp_endif@@
	return true;
}


@@>> shared_lock_waitfor(3)
@@Wait for `self' to become available.
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__KERNEL__) || defined(__shared_lock_wait_impl))]]
[[impl_include("<kos/bits/shared-lock.h>")]]
void shared_lock_waitfor([[inout]] struct shared_lock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_available(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_available(self))
				return;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__shared_lock_available(self)) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@(@KTIME_INFINITE@);
	}
@@pp_else@@
	__shared_lock_waitfor_or_wait_impl(self, {
		__shared_lock_wait_impl(self);
	});
@@pp_endif@@
}


@@>> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
@@Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
@@@return: true:  The lock became available.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_lock_waitfor_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_lock_waitfor_with_timeout64")]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__KERNEL__) || defined(__shared_lock_wait_impl_timeout))]]
[[impl_include("<kos/bits/shared-lock.h>")]]
$bool shared_lock_waitfor_with_timeout([[inout]] struct shared_lock *__restrict self,
                                       __shared_lock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_available(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_available(self))
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__shared_lock_available(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	__shared_lock_waitfor_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout(self, abs_timeout))
			return false; /* Timeout */
	});
@@pp_endif@@
	return true;
}




%#if !defined(__KERNEL__) && defined(__USE_TIME64)
[[preferred_time64_variant_of(shared_lock_acquire_with_timeout), doc_alias("shared_lock_acquire_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__shared_lock_wait_impl_timeout64))]]
[[impl_include("<kos/bits/shared-lock.h>")]]
$bool shared_lock_acquire_with_timeout64([[inout]] struct shared_lock *__restrict self,
                                         [[in_opt]] struct timespec64 const *abs_timeout) {
	__shared_lock_acquire_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout64(self, abs_timeout))
			return false; /* Timeout */
	});
	return true;
}

[[preferred_time64_variant_of(shared_lock_waitfor_with_timeout), doc_alias("shared_lock_waitfor_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__shared_lock_wait_impl_timeout64))]]
[[impl_include("<kos/bits/shared-lock.h>")]]
$bool shared_lock_waitfor_with_timeout64([[inout]] struct shared_lock *__restrict self,
                                         [[in_opt]] struct timespec64 const *abs_timeout) {
	__shared_lock_waitfor_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout64(self, abs_timeout))
			return false; /* Timeout */
	});
	return true;
}
%#endif /* !__KERNEL__ && __USE_TIME64 */





%
%
%#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
@@>> shared_lock_acquire_nx(3)
@@Acquire a lock to the given shared_lock.
@@@return: true:  Successfully acquired a lock.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_lock_acquire_nx([[inout]] struct shared_lock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_tryacquire(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__shared_lock_tryacquire(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(@KTIME_INFINITE@))
			return false;
	}
success:
	return true;
}


@@>> shared_lock_acquire_with_timeout_nx(3)
@@Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
@@@return: true:  Successfully acquired a lock.
@@@return: false: The given `abs_timeout' has expired.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_lock_acquire_with_timeout_nx([[inout]] struct shared_lock *__restrict self,
                                          __shared_lock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_tryacquire(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__shared_lock_tryacquire(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(abs_timeout))
			return false;
	}
success:
	return true;
}


@@>> shared_lock_waitfor_nx(3)
@@Wait that `self' becomes available.
@@@return: true:  The lock became available.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_lock_waitfor_nx([[inout]] struct shared_lock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_available(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_available(self))
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__shared_lock_available(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(@KTIME_INFINITE@))
			return false;
	}
success:
	return true;
}


@@>> shared_lock_waitfor_with_timeout_nx(3)
@@Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
@@@return: true:  The lock became available.
@@@return: false: The given `abs_timeout' has expired.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, E_INTERRUPT)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_lock_waitfor_with_timeout_nx([[inout]] struct shared_lock *__restrict self,
                                          __shared_lock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (!__shared_lock_available(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__shared_lock_available(self))
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__shared_lock_available(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(abs_timeout))
			return false;
	}
success:
	return true;
}
%#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */



%#ifdef __cplusplus
%[insert:function(shared_lock_acquire = shared_lock_acquire_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_lock_waitfor = shared_lock_waitfor_with_timeout, externLinkageOverride: "C++")]
%#if !defined(__KERNEL__) && defined(__USE_TIME64)
%[insert:function(shared_lock_acquire = shared_lock_acquire_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_lock_waitfor = shared_lock_waitfor_with_timeout64, externLinkageOverride: "C++")]
%#endif /* !__KERNEL__ && __USE_TIME64 */
%#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
%[insert:function(shared_lock_acquire_nx = shared_lock_acquire_with_timeout_nx, externLinkageOverride: "C++")]
%[insert:function(shared_lock_waitfor_nx = shared_lock_waitfor_with_timeout_nx, externLinkageOverride: "C++")]
%#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
%#elif defined(__HYBRID_PP_VA_OVERLOAD)
%{
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
}
%#endif /* ... */


%
%
%{
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
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
