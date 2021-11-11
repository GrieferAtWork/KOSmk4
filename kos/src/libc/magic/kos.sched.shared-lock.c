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
#include <sched/signal.h>
#else /* __KERNEL__ */
#include <bits/os/timespec.h>
#include <kos/bits/futex.h>
#include <kos/syscalls.h>
#endif /* !__KERNEL__ */

#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __KERNEL__
#define SHARED_LOCK_INIT               { SIG_INIT, 0 }
#define SHARED_LOCK_INIT_LOCKED        { SIG_INIT, 1 }
#define shared_lock_init(self)         (void)(sig_init(&(self)->sl_sig), (self)->sl_lock = 0)
#define shared_lock_init_locked(self)  (void)(sig_init(&(self)->sl_sig), (self)->sl_lock = 1)
#define shared_lock_cinit(self)        (void)(sig_cinit(&(self)->sl_sig), __hybrid_assert((self)->sl_lock == 0))
#define shared_lock_cinit_locked(self) (void)(sig_cinit(&(self)->sl_sig), (self)->sl_lock = 1)
#else /* __KERNEL__ */
#define SHARED_LOCK_INIT               { 0, 0 }
#define SHARED_LOCK_INIT_LOCKED        { 0, 1 }
#define shared_lock_init(self)         (void)((self)->sl_sig = 0, (self)->sl_lock = 0)
#define shared_lock_init_locked(self)  (void)((self)->sl_sig = 0, (self)->sl_lock = 1)
#define shared_lock_cinit(self)        (void)(__hybrid_assert((self)->sl_sig == 0), __hybrid_assert((self)->sl_lock == 0))
#define shared_lock_cinit_locked(self) (void)(__hybrid_assert((self)->sl_sig == 0), (self)->sl_lock = 1)
#endif /* !__KERNEL__ */
#define shared_lock_acquired(self)     (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) != 0)
#define shared_lock_available(self)    (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) == 0)
#ifdef __KERNEL__
#define shared_lock_broadcast_for_fini(self) \
	sig_broadcast_for_fini(&(self)->sl_sig)
#else /* __KERNEL__ */
/* NOTE: we use `sys_Xlfutex()', because the only possible exception is E_SEGFAULT */
#define shared_lock_broadcast_for_fini(self) \
	((self)->sl_sig ? (void)sys_Xlfutex(&(self)->sl_sig, LFUTEX_WAKE, (__uintptr_t)-1, __NULLPTR, 0) : (void)0)
#endif /* !__KERNEL__ */

#define shared_lock_tryacquire(self) \
	(__hybrid_atomic_xch((self)->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)

#ifdef __KERNEL__
#define __shared_lock_send(self) \
	sig_send(&(self)->sl_sig)
#else /* __KERNEL__ */
/* NOTE: we use `sys_Xlfutex()', because the only possible exception is E_SEGFAULT */
#define __shared_lock_send(self) \
	((self)->sl_sig ? (sys_Xlfutex(&(self)->sl_sig, LFUTEX_WAKEMASK, 1, __NULLPTR, 0) != 0) : 0)
#endif /* !__KERNEL__ */

/* Release a lock from a given shared_lock.
 * @return: true:  A waiting thread was signaled.
 * @return: false: Either no  thread was  signaled, or  the
 *                 lock remains held by the calling thread. */
#if defined(NDEBUG) || defined(NDEBUG_SYNC)
#define shared_lock_release(self)                                 \
	(__hybrid_atomic_store((self)->sl_lock, 0, __ATOMIC_RELEASE), \
	 __shared_lock_send(self))
#else /* NDEBUG || NDEBUG_SYNC */
#define shared_lock_release(self)                                 \
	(__hybrid_assert((self)->sl_lock != 0),                       \
	 __hybrid_atomic_store((self)->sl_lock, 0, __ATOMIC_RELEASE), \
	 __shared_lock_send(self))
#endif /* !NDEBUG || !NDEBUG_SYNC */

}


%[define(DEFINE_SHARED_LOCK_ACQUIRE_USER_PREFIX =
#include <kos/syscalls.h>
#include <kos/bits/futex.h>
#include <kos/bits/futex-expr.h>
@@pp_ifndef __SHARED_LOCK_WAITEXPR_DEFINED@@
#define __SHARED_LOCK_WAITEXPR_DEFINED
@@push_namespace(local)@@
static struct @lfutexexpr@ const @__shared_lock_waitexpr@[] = {
	/* Wait until `sl_lock == 0' */
	@LFUTEXEXPR_INIT@(offsetof(struct @shared_lock@, @sl_lock@), @LFUTEX_WAIT_UNTIL@, 0, 0)
};
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_SHARED_LOCK_ACQUIRE_PREFIX =
@@pp_ifdef __KERNEL__@@
#include <hybrid/__assert.h>
#include <sched/signal.h>
@@pp_else@@
DEFINE_SHARED_LOCK_ACQUIRE_USER_PREFIX
@@pp_endif@@
)]

@@>> shared_lock_acquire(3)
@@Acquire a lock to the given shared_lock.
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExpr64_except))]]
[[impl_prefix(DEFINE_SHARED_LOCK_ACQUIRE_PREFIX)]]
void shared_lock_acquire([[nonnull]] struct shared_lock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@();
	}
success:
@@pp_else@@
	while (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(self->@sl_sig@, 1, __ATOMIC_SEQ_CST);
		LFutexExpr64_except(&self->@sl_sig@, self, 1, __NAMESPACE_LOCAL_SYM @__shared_lock_waitexpr@, NULL, 0);
	}
@@pp_endif@@
	COMPILER_BARRIER();
}


@@>> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
@@Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
@@@return: true:  Successfully acquired a lock.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_lock_acquire_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_lock_acquire_with_timeout64")]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExpr_except))]]
[[impl_prefix(DEFINE_SHARED_LOCK_ACQUIRE_PREFIX)]]
$bool shared_lock_acquire_with_timeout([[nonnull]] struct shared_lock *__restrict self,
                                       __shared_lock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	while (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(self->@sl_sig@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExpr_except(&self->@sl_sig@, self, 1,
		                      __NAMESPACE_LOCAL_SYM @__shared_lock_waitexpr@,
		                      abs_timeout, @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@) < 0)
			return false;
	}
@@pp_endif@@
	COMPILER_BARRIER();
	return true;
}


@@>> shared_lock_waitfor(3)
@@Wait that `self' becomes available.
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExpr64_except))]]
[[impl_prefix(DEFINE_SHARED_LOCK_ACQUIRE_PREFIX)]]
void shared_lock_waitfor([[nonnull]] struct shared_lock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				return;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@();
	}
@@pp_else@@
	while (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(self->@sl_sig@, 1, __ATOMIC_SEQ_CST);
		LFutexExpr64_except(&self->@sl_sig@, self, 1, __NAMESPACE_LOCAL_SYM @__shared_lock_waitexpr@,
		                    NULL, 0);
	}
@@pp_endif@@
}


@@>> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
@@Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
@@@return: true:  The lock became available.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_lock_waitfor_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_lock_waitfor_with_timeout64")]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExpr_except))]]
[[impl_prefix(DEFINE_SHARED_LOCK_ACQUIRE_PREFIX)]]
$bool shared_lock_waitfor_with_timeout([[nonnull]] struct shared_lock *__restrict self,
                                       __shared_lock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	while (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(self->@sl_sig@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExpr_except(&self->@sl_sig@, self, 1,
		                      __NAMESPACE_LOCAL_SYM @__shared_lock_waitexpr@, abs_timeout,
		                      @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@ |
		                      @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@) < 0)
			return false;
	}
@@pp_endif@@
	return true;
}




%#if !defined(__KERNEL__) && defined(__USE_TIME64)
[[preferred_time64_variant_of(shared_lock_acquire_with_timeout), doc_alias("shared_lock_acquire_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires($has_function(LFutexExpr64_except))]]
[[impl_prefix(DEFINE_SHARED_LOCK_ACQUIRE_USER_PREFIX)]]
$bool shared_lock_acquire_with_timeout64([[nonnull]] struct shared_lock *__restrict self,
                                         struct timespec64 const *abs_timeout) {
	while (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(self->@sl_sig@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExpr64_except(&self->@sl_sig@, self, 1,
		                        __NAMESPACE_LOCAL_SYM @__shared_lock_waitexpr@,
		                        abs_timeout, @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@) < 0)
			return false;
	}
	COMPILER_BARRIER();
	return true;
}

[[preferred_time64_variant_of(shared_lock_waitfor_with_timeout), doc_alias("shared_lock_waitfor_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires($has_function(LFutexExpr64_except))]]
[[impl_prefix(DEFINE_SHARED_LOCK_ACQUIRE_USER_PREFIX)]]
$bool shared_lock_waitfor_with_timeout64([[nonnull]] struct shared_lock *__restrict self,
                                         struct timespec64 const *abs_timeout) {
	while (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(self->@sl_sig@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExpr64_except(&self->@sl_sig@, self, 1,
		                        __NAMESPACE_LOCAL_SYM @__shared_lock_waitexpr@, abs_timeout,
		                        @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@ |
		                        @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@) < 0)
			return false;
	}
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
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/signal.h>")]]
$bool shared_lock_acquire_nx([[nonnull]] struct shared_lock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@())
			return false;
	}
success:
	COMPILER_BARRIER();
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
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/signal.h>")]]
$bool shared_lock_acquire_with_timeout_nx([[nonnull]] struct shared_lock *__restrict self,
                                          __shared_lock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_xch(self->@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}


@@>> shared_lock_waitfor_nx(3)
@@Wait that `self' becomes available.
@@@return: true:  The lock became available.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-lock.h>")]]
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/signal.h>")]]
$bool shared_lock_waitfor_nx([[nonnull]] struct shared_lock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@())
			return false;
	}
success:
	COMPILER_BARRIER();
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
[[attribute(__BLOCKING, __NOCONNECT), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/signal.h>")]]
$bool shared_lock_waitfor_with_timeout_nx([[nonnull]] struct shared_lock *__restrict self,
                                          __shared_lock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_sig@);
		if unlikely(__hybrid_atomic_load(self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
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
