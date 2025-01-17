/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(lfutex_t = __uintptr_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]
%[default:section(".text.crt{|.dos}.sched.futex")]
%[default:nodos]
%[default:no_inline_truncate]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/bits/shared-rwlock.h>
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
}%[insert:prefix(
#include <bits/os/timespec.h>
)]%[insert:prefix(
#include <kos/asm/futex.h>
)]%[insert:prefix(
#include <kos/syscalls.h>
)]%{
#endif /* !__KERNEL__ */

#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

/* `shared_rwlock' is the  same as an `atomic_rwlock', with the
 * addition that a `shared_rwlock' includes a signal with which
 * one can do blocking waits for the lock to become available. */

#ifdef __KERNEL__
#define SHARED_RWLOCK_INIT              { 0, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_READ         { 1, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_WRITE        { (__uintptr_t)-1, SIG_INIT, SIG_INIT }
#define shared_rwlock_init(self)        ((self)->sl_lock = 0, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_read(self)   (void)((self)->sl_lock = 1, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_write(self)  (void)((self)->sl_lock = (__uintptr_t)-1, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_cinit(self)       (__hybrid_assert((self)->sl_lock == 0), sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_read(self)  (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_write(self) (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = (__uintptr_t)-1, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_broadcast_for_fini(self)   \
	(sig_broadcast_for_fini(&(self)->sl_rdwait), \
	 sig_broadcast_for_fini(&(self)->sl_wrwait))
#else /* __KERNEL__ */
#define SHARED_RWLOCK_INIT              { 0, 0, 0 }
#define SHARED_RWLOCK_INIT_READ         { 1, 0, 0 }
#define SHARED_RWLOCK_INIT_WRITE        { (__uintptr_t)-1, 0, 0 }
#define shared_rwlock_init(self)        (void)((self)->sl_lock = 0, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_init_read(self)   (void)((self)->sl_lock = 1, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_init_write(self)  (void)((self)->sl_lock = (__uintptr_t)-1, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_cinit(self)       (__hybrid_assert((self)->sl_lock == 0), __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
#define shared_rwlock_cinit_read(self)  (__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1, __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
#define shared_rwlock_cinit_write(self) (__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = (__uintptr_t)-1, __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
/* NOTE: we use `sys_Xlfutex()', because the only possible exception is E_SEGFAULT */
#define shared_rwlock_broadcast_for_fini(self)                                                                        \
	((self)->sl_rdwait ? (void)sys_Xlfutex(&(self)->sl_rdwait, LFUTEX_WAKE, (__uintptr_t)-1, __NULLPTR, 0) : (void)0, \
	 (self)->sl_rdwait ? (void)sys_Xlfutex(&(self)->sl_wrwait, LFUTEX_WAKE, (__uintptr_t)-1, __NULLPTR, 0) : (void)0)
#endif /* !__KERNEL__ */

/* Check if reading/writing is possible, or a read/write lock is being held. */
#ifdef __COMPILER_WORKAROUND_GCC_105689_MAC
#define shared_rwlock_reading(self)  __COMPILER_WORKAROUND_GCC_105689_MAC(self, __hybrid_atomic_load(&__cw_105689_self->sl_lock, __ATOMIC_ACQUIRE) != 0)
#define shared_rwlock_writing(self)  __COMPILER_WORKAROUND_GCC_105689_MAC(self, __hybrid_atomic_load(&__cw_105689_self->sl_lock, __ATOMIC_ACQUIRE) == (__uintptr_t)-1)
#define shared_rwlock_canread(self)  __COMPILER_WORKAROUND_GCC_105689_MAC(self, __hybrid_atomic_load(&__cw_105689_self->sl_lock, __ATOMIC_ACQUIRE) != (__uintptr_t)-1)
#define shared_rwlock_canwrite(self) __COMPILER_WORKAROUND_GCC_105689_MAC(self, __hybrid_atomic_load(&__cw_105689_self->sl_lock, __ATOMIC_ACQUIRE) == 0)
#else /* __COMPILER_WORKAROUND_GCC_105689_MAC */
#define shared_rwlock_reading(self)  (__hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE) != 0)
#define shared_rwlock_writing(self)  (__hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE) == (__uintptr_t)-1)
#define shared_rwlock_canread(self)  (__hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE) != (__uintptr_t)-1)
#define shared_rwlock_canwrite(self) (__hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE) == 0)
#endif /* !__COMPILER_WORKAROUND_GCC_105689_MAC */

/* >> shared_rwlock_tryupgrade(3)
 * Try to upgrade a read-lock to a write-lock. Return `false' upon failure. */
#ifdef __COMPILER_WORKAROUND_GCC_105689_MAC
#define shared_rwlock_tryupgrade(self) \
	__COMPILER_WORKAROUND_GCC_105689_MAC(self, __hybrid_atomic_cmpxch(&__cw_105689_self->sl_lock, 1, (__uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
#else /* __COMPILER_WORKAROUND_GCC_105689_MAC */
#define shared_rwlock_tryupgrade(self) \
	__hybrid_atomic_cmpxch(&(self)->sl_lock, 1, (__uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)
#endif /* !__COMPILER_WORKAROUND_GCC_105689_MAC */

}


@@>> shared_rwlock_tryread(3)
@@Try to acquire a read-lock to `self'
[[extern_inline, wunused, nothrow, kernel, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>")]]
$bool shared_rwlock_tryread([[inout]] struct shared_rwlock *__restrict self) {
	$uintptr_t temp;
	__COMPILER_WORKAROUND_GCC_105689(self);
	do {
		temp = __hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE);
		if (temp == ($uintptr_t)-1)
			return $false;
		__hybrid_assert(temp != ($uintptr_t)-2);
	} while (!__hybrid_atomic_cmpxch_weak(&self->@sl_lock@, temp, temp + 1,
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return $true;
}

@@>> shared_rwlock_trywrite(3)
@@Try to acquire a write-lock to `self'
[[extern_inline, wunused, nothrow, kernel, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>")]]
$bool shared_rwlock_trywrite([[inout]] struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (!__hybrid_atomic_cmpxch(&self->@sl_lock@, 0, ($uintptr_t)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return $false;
	__COMPILER_BARRIER();
	return $true;
}


@@>> shared_rwlock_endwrite(3)
@@Release a write-lock from `self'
[[extern_inline, nothrow, kernel, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>", "<hybrid/__assert.h>", "<kos/asm/futex.h>")]]
[[requires_include("<kos/bits/shared-rwlock.h>"), requires(defined(__shared_rwlock_wrwait_send))]]
void shared_rwlock_endwrite([[inout]] struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	__hybrid_assertf(self->@sl_lock@ == ($uintptr_t)-1, "Lock isn't in write-mode (%x)", self->@sl_lock@);
	__hybrid_atomic_store(&self->@sl_lock@, 0, __ATOMIC_RELEASE);
	if (!@__shared_rwlock_wrwait_send@(self))
		@__shared_rwlock_rdwait_broadcast@(self);
}


@@>> shared_rwlock_endread(3)
@@Release a read-lock from `self'
@@@return: true:  The lock has become free.
@@@return: false: The lock is still held by something.
[[extern_inline, nothrow, kernel, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>", "<hybrid/__assert.h>", "<kos/asm/futex.h>")]]
[[requires_include("<kos/bits/shared-rwlock.h>"), requires(defined(__shared_rwlock_wrwait_send))]]
$bool shared_rwlock_endread([[inout]] struct shared_rwlock *__restrict self) {
	$uintptr_t __result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_READ_BARRIER();
	__hybrid_assertf(self->@sl_lock@ != ($uintptr_t)-1, "Lock is in write-mode (%x)", self->@sl_lock@);
	__hybrid_assertf(self->@sl_lock@ != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(&self->@sl_lock@, __ATOMIC_RELEASE);
	if (__result == 0)
		@__shared_rwlock_wrwait_send@(self);
	return __result == 0;
}


@@>> shared_rwlock_end(3)
@@Release a read- or write-lock from `self'
@@@return: true:  The lock has become free.
@@@return: false: The lock is still held by something.
[[extern_inline, nothrow, kernel, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>", "<hybrid/__assert.h>", "<kos/asm/futex.h>")]]
[[requires_include("<kos/bits/shared-rwlock.h>"), requires(defined(__shared_rwlock_wrwait_send))]]
$bool shared_rwlock_end([[inout]] struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	if (self->@sl_lock@ != ($uintptr_t)-1) {
		/* Read-lock */
		$uintptr_t __result;
		__hybrid_assertf(self->@sl_lock@ != 0, "No remaining read-locks");
		__result = __hybrid_atomic_decfetch(&self->@sl_lock@, __ATOMIC_RELEASE);
		if (__result == 0)
			@__shared_rwlock_wrwait_send@(self);
		return __result == 0;
	}
	/* Write-lock */
	__hybrid_atomic_store(&self->@sl_lock@, 0, __ATOMIC_RELEASE);
	if (!@__shared_rwlock_wrwait_send@(self))
		@__shared_rwlock_rdwait_broadcast@(self);
	return $true;
}



@@>> shared_rwlock_downgrade(3)
@@Downgrade a write-lock to a read-lock (Always succeeds).
[[extern_inline, nothrow, kernel, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>", "<hybrid/__assert.h>", "<kos/asm/futex.h>")]]
[[requires_include("<kos/bits/shared-rwlock.h>"), requires(defined(__shared_rwlock_wrwait_send))]]
void shared_rwlock_downgrade([[inout]] struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(self->@sl_lock@ == ($uintptr_t)-1, "Lock isn't in write-mode (%x)", self->@sl_lock@);
	__hybrid_atomic_store(&self->@sl_lock@, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(self); /* Allow for more readers. */
}


/************************************************************************/
/* Blocking-upgrade a read-lock into a write-lock                       */
/************************************************************************/

@@>> shared_rwlock_upgrade(3)
@@Blocking-upgrade a read-lock into a write-lock
@@NOTE: The lock is always upgraded, but when `false' is returned, no lock
@@      may  have been  held temporarily,  meaning that  the caller should
@@      re-load local copies of affected resources.
@@@return: true:  Upgrade was performed without the read-lock being lost
@@@return: false: The read-lock had to be released before a write-lock was acquired
[[wunused, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[extern_inline, kernel, decl_include("<kos/bits/shared-rwlock.h>", "<kos/anno.h>")]]
[[requires_function(shared_rwlock_endread, shared_rwlock_write)]]
[[impl_include("<hybrid/__atomic.h>")]]
$bool shared_rwlock_upgrade([[inout]] struct shared_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__hybrid_atomic_cmpxch(&self->@sl_lock@, 1, ($uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
		return $true; /* Lock wasn't lost */
	shared_rwlock_endread(self);
	shared_rwlock_write(self);
	return $false; /* Lock was (temporarily) lost */
}






/************************************************************************/
/* Proper (blocking) read-/write-lock acquire functions                 */
/************************************************************************/
%[define(DEFINE_SHARED_RWLOCK_READ_USER_PREFIX =
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
@@pp_ifndef __SHARED_RWLOCK_WAITREADEXPR_DEFINED@@
#define __SHARED_RWLOCK_WAITREADEXPR_DEFINED
@@push_namespace(local)@@
static struct @lfutexexpr@ const @__shared_rwlock_waitreadexpr@[] = {
	/* Wait while `sl_lock == (uintptr_t)-1' */
	@LFUTEXEXPR_INIT@(offsetof(struct @shared_rwlock@, @sl_lock@), @LFUTEX_WAIT_WHILE@, ($uintptr_t)-1, 0),
	@LFUTEXEXPR_INIT@(0, @LFUTEX_EXPREND@, 0, 0)
};
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_SHARED_RWLOCK_WRITE_USER_PREFIX =
#include <kos/syscalls.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>
@@pp_ifndef __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED@@
#define __SHARED_RWLOCK_WAITWRITEEXPR_DEFINED
@@push_namespace(local)@@
static struct @lfutexexpr@ const @__shared_rwlock_waitwriteexpr@[] = {
	/* Wait until `sl_lock == 0' */
	@LFUTEXEXPR_INIT@(offsetof(struct @shared_rwlock@, @sl_lock@), @LFUTEX_WAIT_UNTIL@, 0, 0),
	@LFUTEXEXPR_INIT@(0, @LFUTEX_EXPREND@, 0, 0)
};
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_SHARED_RWLOCK_READ_PREFIX =
@@pp_ifdef __KERNEL__@@
#include <hybrid/__assert.h>
#include <sched/sig.h>
@@pp_else@@
DEFINE_SHARED_RWLOCK_READ_USER_PREFIX
@@pp_endif@@
)]

%[define(DEFINE_SHARED_RWLOCK_WRITE_PREFIX =
@@pp_ifdef __KERNEL__@@
#include <hybrid/__assert.h>
#include <sched/sig.h>
@@pp_else@@
DEFINE_SHARED_RWLOCK_WRITE_USER_PREFIX
@@pp_endif@@
)]


@@>> shared_rwlock_read(3)
@@Acquire a read-lock to the given shared_rwlock.
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_READ_PREFIX)]]
void shared_rwlock_read([[inout]] struct shared_rwlock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_tryread(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_tryread(self))
				goto success;
		});
		@task_connect@(&self->@sl_rdwait@);
		if unlikely(shared_rwlock_tryread(self)) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@(@KTIME_INFINITE@);
	}
success:
@@pp_else@@
	while (!shared_rwlock_tryread(self)) {
		__hybrid_atomic_store(&self->@sl_rdwait@, 1, __ATOMIC_SEQ_CST);
		LFutexExprI64_except(&self->@sl_rdwait@, self,
		                     __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitreadexpr@,
		                     NULL, 0);
	}
@@pp_endif@@
	COMPILER_READ_BARRIER();
}


@@>> shared_rwlock_write(3)
@@Acquire a write-lock to the given shared_rwlock.
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_WRITE_PREFIX)]]
void shared_rwlock_write([[inout]] struct shared_rwlock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_trywrite(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		@task_connect@(&self->@sl_wrwait@);
		if unlikely(shared_rwlock_trywrite(self)) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@(@KTIME_INFINITE@);
	}
success:
@@pp_else@@
	while (!shared_rwlock_trywrite(self)) {
		__hybrid_atomic_store(&self->@sl_wrwait@, 1, __ATOMIC_SEQ_CST);
		LFutexExprI64_except(&self->@sl_wrwait@, self,
		                     __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitwriteexpr@,
		                     NULL, 0);
	}
@@pp_endif@@
	COMPILER_BARRIER();
}


@@>> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
@@Acquire a read-lock to the given shared_rwlock.
@@@return: true:  Successfully acquired a read-lock.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_rwlock_read_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_rwlock_read_with_timeout64")]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_READ_PREFIX)]]
$bool shared_rwlock_read_with_timeout([[inout]] struct shared_rwlock *__restrict self,
                                      __shared_rwlock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_tryread(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_tryread(self))
				goto success;
		});
		@task_connect@(&self->@sl_rdwait@);
		if unlikely(shared_rwlock_tryread(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	while (!shared_rwlock_tryread(self)) {
		__hybrid_atomic_store(&self->@sl_rdwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI_except(&self->@sl_rdwait@, self,
		                       __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitreadexpr@,
		                       abs_timeout, 0) < 0)
			return false;
	}
@@pp_endif@@
	COMPILER_READ_BARRIER();
	return true;
}


@@>> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
@@Acquire a write-lock to the given shared_rwlock.
@@@return: true:  Successfully acquired a write-lock.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_rwlock_write_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_rwlock_write_with_timeout64")]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_WRITE_PREFIX)]]
$bool shared_rwlock_write_with_timeout([[inout]] struct shared_rwlock *__restrict self,
                                       __shared_rwlock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_trywrite(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		@task_connect@(&self->@sl_wrwait@);
		if unlikely(shared_rwlock_trywrite(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	while (!shared_rwlock_trywrite(self)) {
		__hybrid_atomic_store(&self->@sl_wrwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI_except(&self->@sl_wrwait@, self,
		                       __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitwriteexpr@,
		                       abs_timeout, @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@) < 0)
			return false;
	}
@@pp_endif@@
	COMPILER_BARRIER();
	return true;
}





/************************************************************************/
/* Wait-for-lock (w/o acquire) functions                                */
/************************************************************************/


@@>> shared_rwlock_waitread(3)
@@Wait until acquiring a read-lock to `self' no longer blocks
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_READ_PREFIX)]]
void shared_rwlock_waitread([[inout]] struct shared_rwlock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == ($uintptr_t)-1) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_rdwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@(@KTIME_INFINITE@);
	}
success:
@@pp_else@@
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == ($uintptr_t)-1) {
		__hybrid_atomic_store(&self->@sl_rdwait@, 1, __ATOMIC_SEQ_CST);
		LFutexExprI64_except(&self->@sl_rdwait@, self, __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitreadexpr@,
		                     NULL, @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@);
	}
@@pp_endif@@
	COMPILER_READ_BARRIER();
}


@@>> shared_rwlock_waitwrite(3)
@@Wait until acquiring a write-lock to `self' no longer blocks
[[kernel, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_WRITE_PREFIX)]]
void shared_rwlock_waitwrite([[inout]] struct shared_rwlock *__restrict self) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_wrwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		@task_waitfor@(@KTIME_INFINITE@);
	}
success:
@@pp_else@@
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(&self->@sl_wrwait@, 1, __ATOMIC_SEQ_CST);
		LFutexExprI64_except(&self->@sl_wrwait@, self, __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitwriteexpr@,
		                     NULL, @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@);
	}
@@pp_endif@@
	COMPILER_BARRIER();
}


@@>> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
@@Wait until acquiring a read-lock to `self' no longer blocks
@@@return: true:  A read-lock became available.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_rwlock_waitread_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_rwlock_waitread_with_timeout64")]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_READ_PREFIX)]]
$bool shared_rwlock_waitread_with_timeout([[inout]] struct shared_rwlock *__restrict self,
                                          __shared_rwlock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == ($uintptr_t)-1) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_rdwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == ($uintptr_t)-1) {
		__hybrid_atomic_store(&self->@sl_rdwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI_except(&self->@sl_rdwait@, self,
		                       __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitreadexpr@,
		                       abs_timeout,
		                       @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@ |
		                       @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@) < 0)
			return false;
	}
@@pp_endif@@
	COMPILER_READ_BARRIER();
	return true;
}


@@>> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
@@Wait until acquiring a write-lock to `self' no longer blocks
@@@return: true:  A write-lock became available.
@@@return: false: The given `abs_timeout' has expired.
[[kernel, wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_rwlock_waitwrite_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_rwlock_waitwrite_with_timeout64")]]
[[requires(defined(__KERNEL__) || $has_function(LFutexExprI_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_WRITE_PREFIX)]]
$bool shared_rwlock_waitwrite_with_timeout([[inout]] struct shared_rwlock *__restrict self,
                                           __shared_rwlock_timespec abs_timeout) {
@@pp_ifdef __KERNEL__@@
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_wrwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor@(abs_timeout))
			return false;
	}
success:
@@pp_else@@
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(&self->@sl_wrwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI_except(&self->@sl_wrwait@, self,
		                       __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitwriteexpr@,
		                       abs_timeout,
		                       @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@ |
		                       @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@) < 0)
			return false;
	}
@@pp_endif@@
	COMPILER_BARRIER();
	return true;
}



/************************************************************************/
/* 64-bit time functions                                                */
/************************************************************************/
%#if !defined(__KERNEL__) && defined(__USE_TIME64)
[[preferred_time64_variant_of(shared_rwlock_read_with_timeout), doc_alias("shared_rwlock_read_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires($has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_READ_USER_PREFIX)]]
$bool shared_rwlock_read_with_timeout64([[inout]] struct shared_rwlock *__restrict self,
                                        [[in_opt]] struct timespec64 const *abs_timeout) {
	while (!shared_rwlock_tryread(self)) {
		__hybrid_atomic_store(&self->@sl_rdwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI64_except(&self->@sl_rdwait@, self,
		                         __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitreadexpr@,
		                         abs_timeout, @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@) < 0)
			return false;
	}
	COMPILER_READ_BARRIER();
	return true;
}

[[preferred_time64_variant_of(shared_rwlock_write_with_timeout), doc_alias("shared_rwlock_write_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires($has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_WRITE_USER_PREFIX)]]
$bool shared_rwlock_write_with_timeout64([[inout]] struct shared_rwlock *__restrict self,
                                         [[in_opt]] struct timespec64 const *abs_timeout) {
	while (!shared_rwlock_trywrite(self)) {
		__hybrid_atomic_store(&self->@sl_wrwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI64_except(&self->@sl_wrwait@, self,
		                         __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitwriteexpr@,
		                         abs_timeout, @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@) < 0)
			return false;
	}
	COMPILER_BARRIER();
	return true;
}

[[preferred_time64_variant_of(shared_rwlock_waitread_with_timeout), doc_alias("shared_rwlock_waitread_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires($has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_READ_USER_PREFIX)]]
$bool shared_rwlock_waitread_with_timeout64([[inout]] struct shared_rwlock *__restrict self,
                                            [[in_opt]] struct timespec64 const *abs_timeout) {
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == ($uintptr_t)-1) {
		__hybrid_atomic_store(&self->@sl_rdwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI64_except(&self->@sl_rdwait@, self,
		                         __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitreadexpr@,
		                         abs_timeout,
		                         @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@ |
		                         @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@) < 0)
			return false;
	}
	COMPILER_READ_BARRIER();
	return true;
}

[[preferred_time64_variant_of(shared_rwlock_waitwrite_with_timeout), doc_alias("shared_rwlock_waitwrite_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>", "<bits/os/timespec.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires($has_function(LFutexExprI64_except))]]
[[impl_prefix(DEFINE_SHARED_RWLOCK_WRITE_USER_PREFIX)]]
$bool shared_rwlock_waitwrite_with_timeout64([[inout]] struct shared_rwlock *__restrict self,
                                             [[in_opt]] struct timespec64 const *abs_timeout) {
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(&self->@sl_wrwait@, 1, __ATOMIC_SEQ_CST);
		if (LFutexExprI64_except(&self->@sl_wrwait@, self,
		                         __NAMESPACE_LOCAL_SYM @__shared_rwlock_waitwriteexpr@,
		                         abs_timeout,
		                         @LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE@ |
		                         @LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL@) < 0)
			return false;
	}
	COMPILER_BARRIER();
	return true;
}
%#endif /* !__KERNEL__ && __USE_TIME64 */






/************************************************************************/
/* Kernel NoeXcept functions                                            */
/************************************************************************/
%#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
@@>> shared_rwlock_read_nx(3)
@@Acquire a read-lock to the given shared_rwlock.
@@@return: true:  Successfully acquired a read-lock.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_read_nx([[inout]] struct shared_rwlock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_tryread(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_tryread(self))
				goto success;
		});
		@task_connect@(&self->@sl_rdwait@);
		if unlikely(shared_rwlock_tryread(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(@KTIME_INFINITE@))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}


@@>> shared_rwlock_write_nx(3)
@@Acquire a write-lock to the given shared_rwlock.
@@Acquire  a  lock   to  the  given   shared_lock.
@@@return: true:  Successfully acquired a write-lock.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_write_nx([[inout]] struct shared_rwlock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_trywrite(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		@task_connect@(&self->@sl_wrwait@);
		if unlikely(shared_rwlock_trywrite(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(@KTIME_INFINITE@))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}


@@>> shared_rwlock_read_with_timeout_nx(3)
@@Acquire a read-lock to the given shared_rwlock.
@@@return: true:  Successfully acquired a read-lock.
@@@return: false: The given `abs_timeout' has expired.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_read_with_timeout_nx([[inout]] struct shared_rwlock *__restrict self,
                                         __shared_rwlock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_tryread(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_tryread(self))
				goto success;
		});
		@task_connect@(&self->@sl_rdwait@);
		if unlikely(shared_rwlock_tryread(self)) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}


@@>> shared_rwlock_write_with_timeout_nx(3)
@@Acquire a write-lock to the given shared_rwlock.
@@@return: true:  Successfully acquired a write-lock.
@@@return: false: The given `abs_timeout' has expired.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_write_with_timeout_nx([[inout]] struct shared_rwlock *__restrict self,
                                          __shared_rwlock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (!shared_rwlock_trywrite(self)) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		@task_connect@(&self->@sl_wrwait@);
		if unlikely(shared_rwlock_trywrite(self)) {
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

@@>> shared_rwlock_waitread_nx(3)
@@Wait until acquiring a read-lock to `self' no longer blocks
@@@return: true:  A read-lock became available.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_waitread_nx([[inout]] struct shared_rwlock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == ($uintptr_t)-1) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_rdwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(@KTIME_INFINITE@))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}


@@>> shared_rwlock_waitwrite_nx(3)
@@Wait until acquiring a write-lock to `self' no longer blocks
@@Acquire a lock to the given shared_lock.
@@@return: true:  A write-lock became available.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_waitwrite_nx([[inout]] struct shared_rwlock *__restrict self) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_wrwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(@KTIME_INFINITE@))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}


@@>> shared_rwlock_waitread_with_timeout_nx(3)
@@Wait until acquiring a read-lock to `self' no longer blocks
@@@return: true:  A read-lock became available.
@@@return: false: The given `abs_timeout' has expired.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_waitread_with_timeout_nx([[inout]] struct shared_rwlock *__restrict self,
                                             __shared_rwlock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == ($uintptr_t)-1) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_rdwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != ($uintptr_t)-1) {
			@task_disconnectall@();
			break;
		}
		if (!@task_waitfor_nx@(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}


@@>> shared_rwlock_waitwrite_with_timeout_nx(3)
@@Wait until acquiring a write-lock to `self' no longer blocks
@@@return: true:  A write-lock became available.
@@@return: false: The given `abs_timeout' has expired.
@@@return: false: Preemption was disabled, and the operation would have blocked.
@@@return: false: There are pending X-RPCs that could not be serviced.
[[crt_impl_if(defined(__KERNEL__)), requires(defined(__KERNEL__))]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-rwlock.h>")]]
[[attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[impl_include("<hybrid/__assert.h>", "<sched/sig.h>")]]
$bool shared_rwlock_waitwrite_with_timeout_nx([[inout]] struct shared_rwlock *__restrict self,
                                              __shared_rwlock_timespec abs_timeout) {
	__hybrid_assert(!@task_wasconnected@());
	while (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) != 0) {
		@TASK_POLL_BEFORE_CONNECT@({
			if (__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		@task_connect_for_poll@(&self->@sl_wrwait@);
		if unlikely(__hybrid_atomic_load(&self->@sl_lock@, __ATOMIC_ACQUIRE) == 0) {
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
%[insert:function(shared_rwlock_read      = shared_rwlock_read_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_write     = shared_rwlock_write_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_waitread  = shared_rwlock_waitread_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_waitwrite = shared_rwlock_waitwrite_with_timeout, externLinkageOverride: "C++")]
%#if !defined(__KERNEL__) && defined(__USE_TIME64) && (!defined(__USE_STRUCT64_MACRO) || !defined(_TIMESPEC_MATCHES_TIMESPEC64))
%[insert:function(shared_rwlock_read      = shared_rwlock_read_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_write     = shared_rwlock_write_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_waitread  = shared_rwlock_waitread_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_waitwrite = shared_rwlock_waitwrite_with_timeout64, externLinkageOverride: "C++")]
%#endif /* !__KERNEL__ && __USE_TIME64 && (!__USE_STRUCT64_MACRO || !_TIMESPEC_MATCHES_TIMESPEC64) */
%#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
%[insert:function(shared_rwlock_read_nx      = shared_rwlock_read_with_timeout_nx, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_write_nx     = shared_rwlock_write_with_timeout_nx, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_waitread_nx  = shared_rwlock_waitread_with_timeout_nx, externLinkageOverride: "C++")]
%[insert:function(shared_rwlock_waitwrite_nx = shared_rwlock_waitwrite_with_timeout_nx, externLinkageOverride: "C++")]
%#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
%#elif defined(__HYBRID_PP_VA_OVERLOAD)
%{
#define __PRIVATE_shared_rwlock_read_1      (shared_rwlock_read)
#define __PRIVATE_shared_rwlock_read_2      shared_rwlock_read_with_timeout
#define __PRIVATE_shared_rwlock_write_1     (shared_rwlock_write)
#define __PRIVATE_shared_rwlock_write_2     shared_rwlock_write_with_timeout
#define __PRIVATE_shared_rwlock_waitread_1  (shared_rwlock_waitread)
#define __PRIVATE_shared_rwlock_waitread_2  shared_rwlock_waitread_with_timeout
#define __PRIVATE_shared_rwlock_waitwrite_1 (shared_rwlock_waitwrite)
#define __PRIVATE_shared_rwlock_waitwrite_2 shared_rwlock_waitwrite_with_timeout
#define shared_rwlock_read(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_read_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_write(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_write_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitread(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitread_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitwrite(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitwrite_, (__VA_ARGS__))(__VA_ARGS__)
#if !defined(__KERNEL__) && defined(__USE_TIME64)
#define __PRIVATE_shared_rwlock_read64_1      (shared_rwlock_read)
#define __PRIVATE_shared_rwlock_read64_2      shared_rwlock_read_with_timeout64
#define __PRIVATE_shared_rwlock_write64_1     (shared_rwlock_write)
#define __PRIVATE_shared_rwlock_write64_2     shared_rwlock_write_with_timeout64
#define __PRIVATE_shared_rwlock_waitread64_1  (shared_rwlock_waitread)
#define __PRIVATE_shared_rwlock_waitread64_2  shared_rwlock_waitread_with_timeout64
#define __PRIVATE_shared_rwlock_waitwrite64_1 (shared_rwlock_waitwrite)
#define __PRIVATE_shared_rwlock_waitwrite64_2 shared_rwlock_waitwrite_with_timeout64
#define shared_rwlock_read64(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_read64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_write64(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_write64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitread64(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitread64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitwrite64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitwrite64_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__KERNEL__ && __USE_TIME64 */
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#define __PRIVATE_shared_rwlock_read_nx_1      (shared_rwlock_read_nx)
#define __PRIVATE_shared_rwlock_read_nx_2      shared_rwlock_read_with_timeout_nx
#define __PRIVATE_shared_rwlock_write_nx_1     (shared_rwlock_write_nx)
#define __PRIVATE_shared_rwlock_write_nx_2     shared_rwlock_write_with_timeout_nx
#define __PRIVATE_shared_rwlock_waitread_nx_1  (shared_rwlock_waitread_nx)
#define __PRIVATE_shared_rwlock_waitread_nx_2  shared_rwlock_waitread_with_timeout_nx
#define __PRIVATE_shared_rwlock_waitwrite_nx_1 (shared_rwlock_waitwrite_nx)
#define __PRIVATE_shared_rwlock_waitwrite_nx_2 shared_rwlock_waitwrite_with_timeout_nx
#define shared_rwlock_read_nx(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_read_nx_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_write_nx(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_write_nx_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitread_nx(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitread_nx_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitwrite_nx(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitwrite_nx_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
}
%#endif /* ... */


%{

#ifdef __KERNEL__
/* Shared R/W-lock polling functions. */
#define shared_rwlock_pollconnect_read_ex(self, cb)  cb(&(self)->sl_rdwait)
#define shared_rwlock_pollconnect_write_ex(self, cb) cb(&(self)->sl_wrwait)
#ifdef __OPTIMIZE_SIZE__
#define shared_rwlock_pollread_ex(self, cb)       \
	(shared_rwlock_pollconnect_read_ex(self, cb), \
	 shared_rwlock_canread(self))
#define shared_rwlock_pollwrite_ex(self, cb)       \
	(shared_rwlock_pollconnect_write_ex(self, cb), \
	 shared_rwlock_canwrite(self))
#else /* __OPTIMIZE_SIZE__ */
#define shared_rwlock_pollread_ex(self, cb)        \
	(shared_rwlock_canread(self) ||                \
	 (shared_rwlock_pollconnect_read_ex(self, cb), \
	  shared_rwlock_canread(self)))
#define shared_rwlock_pollwrite_ex(self, cb)        \
	(shared_rwlock_canwrite(self) ||                \
	 (shared_rwlock_pollconnect_write_ex(self, cb), \
	  shared_rwlock_canwrite(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#define shared_rwlock_pollconnect_read(self)  shared_rwlock_pollconnect_read_ex(self, task_connect_for_poll)
#define shared_rwlock_pollconnect_write(self) shared_rwlock_pollconnect_write_ex(self, task_connect_for_poll)
#define shared_rwlock_pollread(self)          shared_rwlock_pollread_ex(self, task_connect_for_poll)
#define shared_rwlock_pollwrite(self)         shared_rwlock_pollwrite_ex(self, task_connect_for_poll)
#endif /* __KERNEL__ */

__SYSDECL_END
#endif /* __CC__ */

}
