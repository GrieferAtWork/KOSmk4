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

%[define_replacement(lfutex_t = __uintptr_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]
%[default:section(".text.crt{|.dos}.sched.futex")]
%[default:nodos]
%[default:no_inline_truncate]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/bits/shared-lock.h>
)]%[insert:prefix(
#include <kos/bits/shared-recursive-lock.h>
)]%[insert:prefix(
#include <kos/sched/shared-lock.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/__assert.h>
)]%[insert:prefix(
#include <hybrid/__atomic.h>
)]%[insert:prefix(
#include <bits/os/timespec.h>
)]%[insert:prefix(
#include <kos/asm/futex.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

/*
 * `shared_recursive_lock' just like `shared_lock', but remembers
 * the thread that acquired the lock, thus allowing for recursion
 *
 * NOTE: This interface is not available in kernel-space. For the
 *       rationale, see  `<kos/sched/shared-recursive-rwlock.h>'.
 */

#define SHARED_RECURSIVE_LOCK_INIT        { SHARED_LOCK_INIT, __SHARED_RECURSIVE_LOCK_BADTID, 0 }
#define shared_recursive_lock_init(self)  (void)(shared_lock_init(&(self)->sr_lock), (self)->sr_owner = __SHARED_RECURSIVE_LOCK_BADTID, (self)->sr_rcnt = 0)
#ifdef __SHARED_RECURSIVE_LOCK_BADTID_ISZERO
#define shared_recursive_lock_cinit(self) (shared_lock_cinit(&(self)->sr_lock), __hybrid_assert((self)->sr_owner == __SHARED_RECURSIVE_LOCK_BADTID), __hybrid_assert((self)->sr_rcnt == 0))
#else /* __SHARED_RECURSIVE_LOCK_BADTID_ISZERO */
#define shared_recursive_lock_cinit(self) (shared_lock_cinit(&(self)->sr_lock), (self)->sr_owner = __SHARED_RECURSIVE_LOCK_BADTID, __hybrid_assert((self)->sr_rcnt == 0))
#endif /* !__SHARED_RECURSIVE_LOCK_BADTID_ISZERO */
#ifdef shared_lock_broadcast_for_fini
#define shared_recursive_lock_broadcast_for_fini(self) \
	shared_lock_broadcast_for_fini(&(self)->sr_lock)
#endif /* shared_lock_broadcast_for_fini */

/* Check if locking is possible, or a lock is being held. */
#define shared_recursive_lock_available(self) (shared_lock_available(&(self)->sr_lock) || __shared_recursive_lock_isown(self))
#define shared_recursive_lock_acquired(self)  __shared_recursive_lock_isown(self)
/* #define shared_recursive_lock_acquired(self) (shared_lock_acquired(&(self)->sr_lock) && __shared_recursive_lock_isown(self)) */

}


@@>> shared_recursive_lock_tryacquire(3)
@@Try to acquire a recursive lock to `self'
[[extern_inline, wunused, nothrow, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-recursive-lock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>")]]
$bool shared_recursive_lock_tryacquire([[inout]] struct shared_recursive_lock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
@@pp_ifdef __KERNEL__@@
	if (__hybrid_atomic_xch(self->@sr_lock@.@sl_lock@, 1, __ATOMIC_ACQUIRE) == 0)
@@pp_else@@
	if (__hybrid_atomic_cmpxch(self->@sr_lock@.@sl_lock@, 0, 1, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE))
@@pp_endif@@
	{
		__shared_recursive_lock_setown(self);
		return $true;
	}
	if (__shared_recursive_lock_isown(self)) {
		++self->@sr_rcnt@;
		return $true;
	}
	return $false;
}


@@>> shared_recursive_lock_release(3)
@@Release a recursive lock from `self'
@@@return: true:  The lock has become free.
@@@return: false: You're still holding the lock
[[extern_inline, nothrow, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-recursive-lock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>", "<hybrid/__assert.h>", "<kos/asm/futex.h>")]]
[[requires_include("<kos/bits/shared-recursive-lock.h>"), requires(defined(__shared_lock_send))]]
$bool shared_recursive_lock_release([[inout]] struct shared_recursive_lock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	__hybrid_assertf(self->@sr_lock@.@sl_lock@ != 0, "Lock isn't acquired");
	__hybrid_assertf(__shared_recursive_lock_isown(self), "You're not the owner of this lock");
	if (self->@sr_rcnt@ == 0) {
@@pp_ifdef __KERNEL__@@
		self->@sr_owner@ = __SHARED_RECURSIVE_LOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(self->@sr_lock@.@sl_lock@, 0, __ATOMIC_RELEASE);
		__shared_lock_send(&self->@sr_lock@);
@@pp_else@@
		unsigned int lockstate;
		self->@sr_owner@ = __SHARED_RECURSIVE_LOCK_BADTID;
		__COMPILER_BARRIER();
		lockstate = self->@sr_lock@.@sl_lock@;
		__hybrid_atomic_store(self->@sr_lock@.@sl_lock@, 0, __ATOMIC_RELEASE);
		if (lockstate >= 2)
			__shared_lock_send(&self->@sr_lock@);
@@pp_endif@@
		return $true;
	}
	--self->@sr_rcnt@;
	return $false;
}


/************************************************************************/
/* Proper (blocking) lock acquire functions                             */
/************************************************************************/

@@>> shared_recursive_lock_acquire(3)
@@Acquire a recursive lock to the given shared_recursive_lock.
[[decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-lock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_lock_acquire)]]
void shared_recursive_lock_acquire([[inout]] struct shared_recursive_lock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self)) {
		++self->@sr_rcnt@;
		return;
	}
	shared_lock_acquire(&self->@sr_lock@);
	__shared_recursive_lock_setown(self);
}


@@>> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
@@Acquire a recursive lock to the given shared_recursive_lock.
@@@return: true:  Successfully acquired a recursive lock.
@@@return: false: The given `abs_timeout' has expired.
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-lock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_recursive_lock_acquire_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_recursive_lock_acquire_with_timeout64")]]
[[requires_function(shared_lock_acquire_with_timeout)]]
$bool shared_recursive_lock_acquire_with_timeout([[inout]] struct shared_recursive_lock *__restrict self,
                                                 __shared_lock_timespec abs_timeout) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self)) {
		++self->@sr_rcnt@;
		return true;
	}
	result = shared_lock_acquire_with_timeout(&self->@sr_lock@, abs_timeout);
	if (result)
		__shared_recursive_lock_setown(self);
	return result;
}





/************************************************************************/
/* Wait-for-lock (w/o acquire) functions                                */
/************************************************************************/

@@>> shared_recursive_lock_waitfor(3)
@@Wait until acquiring a recursive lock to `self' no longer blocks
[[decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-lock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_lock_waitfor)]]
void shared_recursive_lock_waitfor([[inout]] struct shared_recursive_lock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self))
		return;
	shared_lock_waitfor(&self->@sr_lock@);
}


@@>> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
@@Wait until acquiring a recursive lock to `self' no longer blocks
@@@return: true:  A lock became available.
@@@return: false: The given `abs_timeout' has expired.
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-lock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_recursive_lock_waitfor_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_recursive_lock_waitfor_with_timeout64")]]
[[requires_function(shared_lock_waitfor_with_timeout)]]
$bool shared_recursive_lock_waitfor_with_timeout([[inout]] struct shared_recursive_lock *__restrict self,
                                                 __shared_lock_timespec abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self))
		return $true;
	return shared_lock_waitfor_with_timeout(&self->@sr_lock@, abs_timeout);
}



/************************************************************************/
/* 64-bit time functions                                                */
/************************************************************************/
%#ifdef __USE_TIME64
[[preferred_time64_variant_of(shared_recursive_lock_acquire_with_timeout), doc_alias("shared_recursive_lock_acquire_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-lock.h>", "<bits/os/timespec.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_lock_acquire_with_timeout64)]]
$bool shared_recursive_lock_acquire_with_timeout64([[inout]] struct shared_recursive_lock *__restrict self,
                                                   [[in_opt]] struct timespec64 const *abs_timeout) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self)) {
		++self->@sr_rcnt@;
		return $true;
	}
	result = shared_lock_acquire_with_timeout64(&self->@sr_lock@, abs_timeout);
	if (result)
		__shared_recursive_lock_setown(self);
	return result;
}

[[preferred_time64_variant_of(shared_recursive_lock_waitfor_with_timeout), doc_alias("shared_recursive_lock_waitfor_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-lock.h>", "<bits/os/timespec.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_lock_waitfor_with_timeout64)]]
$bool shared_recursive_lock_waitfor_with_timeout64([[inout]] struct shared_recursive_lock *__restrict self,
                                                   [[in_opt]] struct timespec64 const *abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self))
		return $true;
	return shared_lock_waitfor_with_timeout64(&self->@sr_lock@, abs_timeout);
}
%#endif /* !__USE_TIME64 */





%#ifdef __cplusplus
%[insert:function(shared_recursive_lock_acquire = shared_recursive_lock_acquire_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_lock_waitfor = shared_recursive_lock_waitfor_with_timeout, externLinkageOverride: "C++")]
%#if defined(__USE_TIME64) && (!defined(__USE_STRUCT64_MACRO) || !defined(_TIMESPEC_MATCHES_TIMESPEC64))
%[insert:function(shared_recursive_lock_acquire = shared_recursive_lock_acquire_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_lock_waitfor = shared_recursive_lock_waitfor_with_timeout64, externLinkageOverride: "C++")]
%#endif /* __USE_TIME64 && (!__USE_STRUCT64_MACRO || !_TIMESPEC_MATCHES_TIMESPEC64) */
%#elif defined(__HYBRID_PP_VA_OVERLOAD)
%{
#define __PRIVATE_shared_recursive_lock_acquire_1 (shared_recursive_lock_acquire)
#define __PRIVATE_shared_recursive_lock_acquire_2 shared_recursive_lock_acquire_with_timeout
#define __PRIVATE_shared_recursive_lock_waitfor_1 (shared_recursive_lock_waitfor)
#define __PRIVATE_shared_recursive_lock_waitfor_2 shared_recursive_lock_waitfor_with_timeout
#define shared_recursive_lock_acquire(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_acquire_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_lock_waitfor(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_waitfor_, (__VA_ARGS__))(__VA_ARGS__)
#ifdef __USE_TIME64
#define __PRIVATE_shared_recursive_lock_acquire64_1 (shared_recursive_lock_acquire)
#define __PRIVATE_shared_recursive_lock_acquire64_2 shared_recursive_lock_acquire_with_timeout64
#define __PRIVATE_shared_recursive_lock_waitfor64_1 (shared_recursive_lock_waitfor)
#define __PRIVATE_shared_recursive_lock_waitfor64_2 shared_recursive_lock_waitfor_with_timeout64
#define shared_recursive_lock_acquire64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_acquire64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_lock_waitfor64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_waitfor64_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_TIME64 */
}
%#endif /* ... */


%{

__SYSDECL_END
#endif /* __CC__ */

}
