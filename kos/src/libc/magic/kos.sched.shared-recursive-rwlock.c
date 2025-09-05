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
#include <kos/bits/shared-recursive-rwlock.h>
)]%[insert:prefix(
#include <kos/sched/shared-rwlock.h>
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
 * `shared_recursive_rwlock' just like  `shared_rwlock', but allows  for
 * the owning thread to recursively acquire a write-lock multiple times.
 * WARNING: Trying to acquire a write-lock when holding a read-lock will
 *          DEADLOCK. The only way to safely do this is by making use of
 *          `shared_recursive_rwlock_upgrade(3)'!
 *
 * NOTE: This system is NOT available in kernel-space. It could easily be
 *       provided, using the same implementation as in user-space, but we
 *       intentionally don't do this as the necessity of recursive  locks
 *       indicates a flaw in your design.
 *       If  it's possible that you might need to recursively acquire the
 *       same lock, then that means that your function itself is able  to
 *       recurse. This fact alone violates the unspoken rule of trying to
 *       be  non-blocking about most of everything, and you should try to
 *       re-design your system, preferably using atomic locks!
 *
 * The only reason why the system is provided in user-space, is  because
 * it  is needed for stdio files, which  by design have to use recursive
 * locks, (s.a. `flockfile(3)',  `funlockfile(3)', and interaction  with
 * `funopen(3)').  And  because certain  stdio operations  are read-only
 * (ftell(3)), it stands to reason to use a read/write-lock that is also
 * able to do recursive write-locks.
 */

#define SHARED_RECURSIVE_RWLOCK_INIT(self)                    { SHARED_RWLOCK_INIT(self.srr_lock), __SHARED_RECURSIVE_RWLOCK_BADTID, 0 }
#define SHARED_RECURSIVE_RWLOCK_INIT_READ(self)               { SHARED_RWLOCK_INIT_READ(self.srr_lock), __SHARED_RECURSIVE_RWLOCK_BADTID, 0 }
#define SHARED_RECURSIVE_RWLOCK_INIT_NAMED(self, name)        { SHARED_RWLOCK_INIT_NAMED(self.srr_lock, name ".srr_lock"), __SHARED_RECURSIVE_RWLOCK_BADTID, 0 }
#define SHARED_RECURSIVE_RWLOCK_INIT_READ_NAMED(self, name)   { SHARED_RWLOCK_INIT_READ_NAMED(self.srr_lock, name ".srr_lock"), __SHARED_RECURSIVE_RWLOCK_BADTID, 0 }
#define shared_recursive_rwlock_init(self)                    (void)(shared_rwlock_init(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, (self)->srr_wrcnt = 0)
#define shared_recursive_rwlock_init_read(self)               (void)(shared_rwlock_init_read(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, (self)->srr_wrcnt = 0)
#define shared_recursive_rwlock_init_write(self)              (void)(shared_rwlock_init_write(&(self)->srr_lock), __shared_recursive_rwlock_setown(self))
#define shared_recursive_rwlock_init_named(self, name)        (void)(shared_rwlock_init_named(&(self)->srr_lock, name ".srr_lock"), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, (self)->srr_wrcnt = 0)
#define shared_recursive_rwlock_init_read_named(self, name)   (void)(shared_rwlock_init_read_named(&(self)->srr_lock, name ".srr_lock"), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, (self)->srr_wrcnt = 0)
#define shared_recursive_rwlock_init_write_named(self, name)  (void)(shared_rwlock_init_write_named(&(self)->srr_lock, name ".srr_lock"), __shared_recursive_rwlock_setown(self))
#ifdef __SHARED_RECURSIVE_RWLOCK_BADTID_ISZERO
#define shared_recursive_rwlock_cinit(self)                   (shared_rwlock_cinit(&(self)->srr_lock), __hybrid_assert((self)->srr_writer == __SHARED_RECURSIVE_RWLOCK_BADTID), __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_read(self)              (shared_rwlock_cinit_read(&(self)->srr_lock), __hybrid_assert((self)->srr_writer == __SHARED_RECURSIVE_RWLOCK_BADTID), __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_named(self, name)       (shared_rwlock_cinit_named(&(self)->srr_lock, name ".srr_lock"), __hybrid_assert((self)->srr_writer == __SHARED_RECURSIVE_RWLOCK_BADTID), __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_read_named(self, name)  (shared_rwlock_cinit_read_named(&(self)->srr_lock, name ".srr_lock"), __hybrid_assert((self)->srr_writer == __SHARED_RECURSIVE_RWLOCK_BADTID), __hybrid_assert((self)->srr_wrcnt == 0))
#else /* __SHARED_RECURSIVE_RWLOCK_BADTID_ISZERO */
#define shared_recursive_rwlock_cinit(self)                   (shared_rwlock_cinit(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_read(self)              (shared_rwlock_cinit_read(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_named(self, name)       (shared_rwlock_cinit_named(&(self)->srr_lock, name ".srr_lock"), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_read_named(self, name)  (shared_rwlock_cinit_read_named(&(self)->srr_lock, name ".srr_lock"), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, __hybrid_assert((self)->srr_wrcnt == 0))
#endif /* !__SHARED_RECURSIVE_RWLOCK_BADTID_ISZERO */
#define shared_recursive_rwlock_cinit_write(self)             (void)(shared_rwlock_cinit_write(&(self)->srr_lock), __shared_recursive_rwlock_setown(self))
#define shared_recursive_rwlock_cinit_write_named(self, name) (void)(shared_rwlock_cinit_write_named(&(self)->srr_lock, name ".srr_lock"), __shared_recursive_rwlock_setown(self))
#define shared_recursive_rwlock_broadcast_for_fini(self)      shared_rwlock_broadcast_for_fini(&(self)->srr_lock)
#define DEFINE_SHARED_RECURSIVE_RWLOCK(self)                  struct shared_recursive_rwlock self = SHARED_RECURSIVE_RWLOCK_INIT(self)
#define DEFINE_SHARED_RECURSIVE_RWLOCK_READ(self)             struct shared_recursive_rwlock self = SHARED_RECURSIVE_RWLOCK_INIT_READ(self)
#define DEFINE_SHARED_RECURSIVE_RWLOCK_NAMED(self, name)      struct shared_recursive_rwlock self = SHARED_RECURSIVE_RWLOCK_INIT_NAMED(self, name)
#define DEFINE_SHARED_RECURSIVE_RWLOCK_READ_NAMED(self, name) struct shared_recursive_rwlock self = SHARED_RECURSIVE_RWLOCK_INIT_READ_NAMED(self, name)

/* Check if reading/writing is possible, or a read/write lock is being held. */
#define shared_recursive_rwlock_canread(self)  (shared_rwlock_canread(&(self)->srr_lock) || __shared_recursive_rwlock_isown(self))
#define shared_recursive_rwlock_canwrite(self) (shared_rwlock_canwrite(&(self)->srr_lock) || __shared_recursive_rwlock_isown(self))
#define shared_recursive_rwlock_reading(self)  shared_rwlock_reading(&(self)->srr_lock)
#define shared_recursive_rwlock_writing(self)  __shared_recursive_rwlock_isown(self)
/* #define shared_recursive_rwlock_writing(self) (shared_rwlock_writing(&(self)->srr_lock) && __shared_recursive_rwlock_isown(self)) */

/* >> shared_recursive_rwlock_tryupgrade(3)
 * Try to upgrade a read-lock to a recursive write-lock. Return `false' upon failure. */
#define shared_recursive_rwlock_tryupgrade(self)    \
	(shared_rwlock_tryupgrade(&(self)->srr_lock) && \
	 (__shared_recursive_rwlock_setown(self), 1))

}


@@>> shared_recursive_rwlock_tryread(3)
@@Try  to acquire a read-lock to `self'
[[extern_inline, wunused, nothrow, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-recursive-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>"), requires_function(shared_rwlock_tryread)]]
$bool shared_recursive_rwlock_tryread([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (shared_rwlock_tryread(&self->@srr_lock@))
		return $true;
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return $true;
	}
	return $false;
}

@@>> shared_recursive_rwlock_trywrite(3)
@@Try to acquire a recursive write-lock to `self'
[[extern_inline, wunused, nothrow, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-recursive-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>"), requires_function(shared_rwlock_trywrite)]]
$bool shared_recursive_rwlock_trywrite([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (shared_rwlock_trywrite(&self->@srr_lock@)) {
		__shared_recursive_rwlock_setown(self);
		return $true;
	}
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return $true;
	}
	return $false;
}


@@>> shared_recursive_rwlock_endwrite(3)
@@Release a recursive write-lock from `self'
@@@return: true:  The lock has become free.
@@@return: false: You're still holding the lock
[[extern_inline, nothrow, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-recursive-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>", "<hybrid/__assert.h>", "<kos/asm/futex.h>")]]
[[requires_include("<kos/bits/shared-recursive-rwlock.h>"), requires(defined(__shared_rwlock_wrwait_send))]]
$bool shared_recursive_rwlock_endwrite([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	__hybrid_assertf(self->@srr_lock@.@sl_lock@ == ($uintptr_t)-1,
	                 "Lock isn't in write-mode (%x)",
	                 self->@srr_lock@.@sl_lock@);
	__hybrid_assertf(__shared_recursive_rwlock_isown(self),
	                 "You're not the owner of this lock");
	if (self->@srr_wrcnt@ == 0) {
		self->@srr_writer@ = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(&self->@srr_lock@.@sl_lock@, 0, __ATOMIC_RELEASE);
		if (!@__shared_rwlock_wrwait_send@(&self->@srr_lock@))
			@__shared_rwlock_rdwait_broadcast@(&self->@srr_lock@);
		return $true;
	}
	--self->@srr_wrcnt@;
	return $false;
}


@@>> shared_recursive_rwlock_endread(3)
@@Release  a   read-lock  from   `self'
@@@return: true:  The lock has become free.
@@@return: false: The lock is still held by something.
[[extern_inline, nothrow, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-recursive-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<hybrid/__atomic.h>", "<hybrid/__assert.h>", "<kos/asm/futex.h>")]]
[[requires_include("<kos/bits/shared-recursive-rwlock.h>"), requires(defined(__shared_rwlock_wrwait_send))]]
$bool shared_recursive_rwlock_endread([[inout]] struct shared_recursive_rwlock *__restrict self) {
	$uintptr_t result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	COMPILER_READ_BARRIER();
	if (self->@srr_lock@.@sl_lock@ == ($uintptr_t)-1)
		return shared_recursive_rwlock_endwrite(self);
	__hybrid_assertf(self->@srr_lock@.@sl_lock@ != 0, "Lock isn't held by anyone");
	result = __hybrid_atomic_decfetch(&self->@srr_lock@.@sl_lock@, __ATOMIC_RELEASE);
	if (result == 0)
		@__shared_rwlock_wrwait_send@(&self->@srr_lock@);
	return result == 0;
}


/* Because read-after-write causes is handled as a recursive write, endread() must
 * be able to release write-locks, meaning it must already be able to release both
 * types of locks, so the generic end-lock function become identical to it! */
%[insert:function(shared_recursive_rwlock_end = shared_recursive_rwlock_endread)]



@@>> shared_recursive_rwlock_downgrade(3)
@@Downgrade a recursive write-lock to a read-lock (Always succeeds, but you have
@@to ensure  that  you're only  holding  a  single write-lock  at  the  moment).
[[extern_inline, nothrow, cc(__FCALL), attribute(__NOBLOCK)]]
[[decl_include("<kos/bits/shared-recursive-rwlock.h>", "<kos/anno.h>")]]
[[impl_include("<kos/bits/shared-recursive-rwlock.h>", "<hybrid/__assert.h>")]]
[[requires_function(shared_rwlock_downgrade)]]
void shared_recursive_rwlock_downgrade([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__hybrid_assertf(__shared_recursive_rwlock_isown(self), "You're not holding this lock");
	__hybrid_assertf(self->@srr_wrcnt@ > 0, "You're holding more than 1 write-lock");
	self->@srr_writer@ = __SHARED_RECURSIVE_RWLOCK_BADTID;
	COMPILER_WRITE_BARRIER();
	shared_rwlock_downgrade(&self->@srr_lock@);
}


/************************************************************************/
/* Blocking-upgrade a read-lock into a recursive write-lock             */
/************************************************************************/

@@>> shared_recursive_rwlock_upgrade(3)
@@Blocking-upgrade a read-lock into a recursive write-lock
@@NOTE: The lock is always upgraded, but when `false' is returned, no lock
@@      may  have been  held temporarily,  meaning that  the caller should
@@      re-load local copies of affected resources.
@@@return: true:  Upgrade was performed without the read-lock being lost
@@@return: false: The read-lock had to be released before a recursive write-lock was acquired
[[extern_inline, wunused, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[decl_include("<kos/bits/shared-recursive-rwlock.h>", "<kos/anno.h>")]]
[[requires_function(shared_recursive_rwlock_endread, shared_recursive_rwlock_write)]]
[[impl_include("<hybrid/__atomic.h>")]]
$bool shared_recursive_rwlock_upgrade([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__hybrid_atomic_cmpxch(&self->@srr_lock@.@sl_lock@, 1, ($uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)) {
		__shared_recursive_rwlock_setown(self);
		return $true; /* Lock wasn't lost */
	}
	shared_recursive_rwlock_endread(self);
	shared_recursive_rwlock_write(self);
	return $false; /* Lock was (temporarily) lost */
}






/************************************************************************/
/* Proper (blocking) read-/write-lock acquire functions                 */
/************************************************************************/
@@>> shared_recursive_rwlock_read(3)
@@Acquire a read-lock to the given shared_recursive_rwlock.
[[decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_read)]]
void shared_recursive_rwlock_read([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return;
	}
	shared_rwlock_read(&self->@srr_lock@);
}


@@>> shared_recursive_rwlock_write(3)
@@Acquire a recursive write-lock to the given shared_recursive_rwlock.
[[decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_write)]]
void shared_recursive_rwlock_write([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return;
	}
	shared_rwlock_write(&self->@srr_lock@);
	__shared_recursive_rwlock_setown(self);
}


@@>> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
@@Acquire a read-lock to the given shared_recursive_rwlock.
@@@return: true:  Successfully acquired a read-lock.
@@@return: false: The given `abs_timeout' has expired.
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_recursive_rwlock_read_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_recursive_rwlock_read_with_timeout64")]]
[[requires_function(shared_rwlock_read_with_timeout)]]
$bool shared_recursive_rwlock_read_with_timeout([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                __shared_rwlock_timespec abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return true;
	}
	return shared_rwlock_read_with_timeout(&self->@srr_lock@, abs_timeout);
}


@@>> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
@@Acquire a recursive write-lock to the given shared_recursive_rwlock.
@@@return: true:  Successfully acquired a recursive write-lock.
@@@return: false: The given `abs_timeout' has expired.
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_recursive_rwlock_write_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_recursive_rwlock_write_with_timeout64")]]
[[requires_function(shared_rwlock_write_with_timeout)]]
$bool shared_recursive_rwlock_write_with_timeout([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                 __shared_rwlock_timespec abs_timeout) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return true;
	}
	result = shared_rwlock_write_with_timeout(&self->@srr_lock@, abs_timeout);
	if (result)
		__shared_recursive_rwlock_setown(self);
	return result;
}





/************************************************************************/
/* Wait-for-lock (w/o acquire) functions                                */
/************************************************************************/


@@>> shared_recursive_rwlock_waitread(3)
@@Wait until acquiring a read-lock to `self' no longer blocks
[[decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_waitread)]]
void shared_recursive_rwlock_waitread([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return;
	shared_rwlock_waitread(&self->@srr_lock@);
}


@@>> shared_recursive_rwlock_waitwrite(3)
@@Wait until acquiring a recursive write-lock to `self' no longer blocks
[[decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_waitwrite)]]
void shared_recursive_rwlock_waitwrite([[inout]] struct shared_recursive_rwlock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return;
	shared_rwlock_waitwrite(&self->@srr_lock@);
}


@@>> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
@@Wait until acquiring a read-lock to `self' no longer blocks
@@@return: true:  A read-lock became available.
@@@return: false: The given `abs_timeout' has expired.
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_recursive_rwlock_waitread_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_recursive_rwlock_waitread_with_timeout64")]]
[[requires_function(shared_rwlock_waitread_with_timeout)]]
$bool shared_recursive_rwlock_waitread_with_timeout([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                    __shared_rwlock_timespec abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return $true;
	return shared_rwlock_waitread_with_timeout(&self->@srr_lock@, abs_timeout);
}


@@>> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
@@Wait until acquiring a recursive write-lock to `self' no longer blocks
@@@return: true:  A write-lock became available.
@@@return: false: The given `abs_timeout' has expired.
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("shared_recursive_rwlock_waitwrite_with_timeout")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("shared_recursive_rwlock_waitwrite_with_timeout64")]]
[[requires_function(shared_rwlock_waitwrite_with_timeout)]]
$bool shared_recursive_rwlock_waitwrite_with_timeout([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                     __shared_rwlock_timespec abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return $true;
	return shared_rwlock_waitwrite_with_timeout(&self->@srr_lock@, abs_timeout);
}



/************************************************************************/
/* 64-bit time functions                                                */
/************************************************************************/
%#ifdef __USE_TIME64
[[preferred_time64_variant_of(shared_recursive_rwlock_read_with_timeout), doc_alias("shared_recursive_rwlock_read_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>", "<bits/os/timespec.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_read_with_timeout64)]]
$bool shared_recursive_rwlock_read_with_timeout64([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                  [[in_opt]] struct timespec64 const *abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return $true;
	}
	return shared_rwlock_read_with_timeout64(&self->@srr_lock@, abs_timeout);
}

[[preferred_time64_variant_of(shared_recursive_rwlock_write_with_timeout), doc_alias("shared_recursive_rwlock_write_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>", "<bits/os/timespec.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_write_with_timeout64)]]
$bool shared_recursive_rwlock_write_with_timeout64([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                   [[in_opt]] struct timespec64 const *abs_timeout) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self)) {
		++self->@srr_wrcnt@;
		return $true;
	}
	result = shared_rwlock_write_with_timeout64(&self->@srr_lock@, abs_timeout);
	if (result)
		__shared_recursive_rwlock_setown(self);
	return result;
}

[[preferred_time64_variant_of(shared_recursive_rwlock_waitread_with_timeout), doc_alias("shared_recursive_rwlock_waitread_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>", "<bits/os/timespec.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_waitread_with_timeout64)]]
$bool shared_recursive_rwlock_waitread_with_timeout64([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                      [[in_opt]] struct timespec64 const *abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return $true;
	return shared_rwlock_waitread_with_timeout64(&self->@srr_lock@, abs_timeout);
}

[[preferred_time64_variant_of(shared_recursive_rwlock_waitwrite_with_timeout), doc_alias("shared_recursive_rwlock_waitwrite_with_timeout")]]
[[wunused, decl_include("<kos/anno.h>", "<kos/bits/shared-recursive-rwlock.h>", "<bits/os/timespec.h>")]]
[[extern_inline, attribute(__BLOCKING), cc(__FCALL), throws(E_WOULDBLOCK, ...)]]
[[requires_function(shared_rwlock_waitwrite_with_timeout64)]]
$bool shared_recursive_rwlock_waitwrite_with_timeout64([[inout]] struct shared_recursive_rwlock *__restrict self,
                                                       [[in_opt]] struct timespec64 const *abs_timeout) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_rwlock_isown(self))
		return $true;
	return shared_rwlock_waitwrite_with_timeout64(&self->@srr_lock@, abs_timeout);
}
%#endif /* !__USE_TIME64 */





%#ifdef __cplusplus
%[insert:function(shared_recursive_rwlock_read      = shared_recursive_rwlock_read_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_rwlock_write     = shared_recursive_rwlock_write_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_rwlock_waitread  = shared_recursive_rwlock_waitread_with_timeout, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_rwlock_waitwrite = shared_recursive_rwlock_waitwrite_with_timeout, externLinkageOverride: "C++")]
%#if defined(__USE_TIME64) && (!defined(__USE_STRUCT64_MACRO) || !defined(_TIMESPEC_MATCHES_TIMESPEC64))
%[insert:function(shared_recursive_rwlock_read      = shared_recursive_rwlock_read_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_rwlock_write     = shared_recursive_rwlock_write_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_rwlock_waitread  = shared_recursive_rwlock_waitread_with_timeout64, externLinkageOverride: "C++")]
%[insert:function(shared_recursive_rwlock_waitwrite = shared_recursive_rwlock_waitwrite_with_timeout64, externLinkageOverride: "C++")]
%#endif /* __USE_TIME64 && (!__USE_STRUCT64_MACRO || !_TIMESPEC_MATCHES_TIMESPEC64) */
%#elif defined(__HYBRID_PP_VA_OVERLOAD)
%{
#define __PRIVATE_shared_recursive_rwlock_read_1      (shared_recursive_rwlock_read)
#define __PRIVATE_shared_recursive_rwlock_read_2      shared_recursive_rwlock_read_with_timeout
#define __PRIVATE_shared_recursive_rwlock_write_1     (shared_recursive_rwlock_write)
#define __PRIVATE_shared_recursive_rwlock_write_2     shared_recursive_rwlock_write_with_timeout
#define __PRIVATE_shared_recursive_rwlock_waitread_1  (shared_recursive_rwlock_waitread)
#define __PRIVATE_shared_recursive_rwlock_waitread_2  shared_recursive_rwlock_waitread_with_timeout
#define __PRIVATE_shared_recursive_rwlock_waitwrite_1 (shared_recursive_rwlock_waitwrite)
#define __PRIVATE_shared_recursive_rwlock_waitwrite_2 shared_recursive_rwlock_waitwrite_with_timeout
#define shared_recursive_rwlock_read(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_read_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_write(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_write_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitread(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitread_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitwrite(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitwrite_, (__VA_ARGS__))(__VA_ARGS__)
#ifdef __USE_TIME64
#define __PRIVATE_shared_recursive_rwlock_read64_1      (shared_recursive_rwlock_read)
#define __PRIVATE_shared_recursive_rwlock_read64_2      shared_recursive_rwlock_read_with_timeout64
#define __PRIVATE_shared_recursive_rwlock_write64_1     (shared_recursive_rwlock_write)
#define __PRIVATE_shared_recursive_rwlock_write64_2     shared_recursive_rwlock_write_with_timeout64
#define __PRIVATE_shared_recursive_rwlock_waitread64_1  (shared_recursive_rwlock_waitread)
#define __PRIVATE_shared_recursive_rwlock_waitread64_2  shared_recursive_rwlock_waitread_with_timeout64
#define __PRIVATE_shared_recursive_rwlock_waitwrite64_1 (shared_recursive_rwlock_waitwrite)
#define __PRIVATE_shared_recursive_rwlock_waitwrite64_2 shared_recursive_rwlock_waitwrite_with_timeout64
#define shared_recursive_rwlock_read64(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_read64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_write64(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_write64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitread64(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitread64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitwrite64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitwrite64_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_TIME64 */
}
%#endif /* ... */


%{

__SYSDECL_END
#endif /* __CC__ */

}
