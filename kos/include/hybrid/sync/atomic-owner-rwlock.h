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
#ifndef __GUARD_HYBRID_SYNC_ATOMIC_OWNER_RWLOCK_H
#define __GUARD_HYBRID_SYNC_ATOMIC_OWNER_RWLOCK_H 1

#include "../../__stdinc.h"
#include "../__atomic.h"
#include "../typecore.h"

#ifndef __INTELLISENSE__
#endif /* !__INTELLISENSE__ */
#include "../__assert.h"
#include "../sched/__yield.h"
#include "../sched/__gettid.h"

__DECL_BEGIN

#if __SIZEOF_POINTER__ == 4
#define __ATOMIC_OWNER_RWLOCK_NMASK __UINT32_C(0x7fffffff)
#define __ATOMIC_OWNER_RWLOCK_WFLAG __UINT32_C(0x80000000)
#elif __SIZEOF_POINTER__ == 8
#define __ATOMIC_OWNER_RWLOCK_NMASK __UINT64_C(0x7fffffffffffffff)
#define __ATOMIC_OWNER_RWLOCK_WFLAG __UINT64_C(0x8000000000000000)
#else
#error "Unsupported sizeof(void *)"
#endif

#define __ATOMIC_OWNER_RWLOCK_OFFSETOF_LOCK     0
#if __HYBRID_SIZEOF_TID__ >= __SIZEOF_POINTER__
#define __ATOMIC_OWNER_RWLOCK_OFFSETOF_OWNER    __HYBRID_SIZEOF_TID__
#define __ATOMIC_OWNER_RWLOCK_SIZE           (2*__HYBRID_SIZEOF_TID__)
#else /* __HYBRID_SIZEOF_TID__ >= __SIZEOF_POINTER__ */
#define __ATOMIC_OWNER_RWLOCK_OFFSETOF_OWNER    __SIZEOF_POINTER__
#define __ATOMIC_OWNER_RWLOCK_SIZE           (2*__SIZEOF_POINTER__)
#endif /* __HYBRID_SIZEOF_TID__ < __SIZEOF_POINTER__ */

#ifdef __CC__
struct __ATTR_PACKED atomic_owner_rwlock {
	/* Similar to a regular rwlock, but allow for owner write-recursion: */
	union __ATTR_PACKED {
		__UINTPTR_TYPE__   aorw_lock;  /* The underlying synchronization atomic. */
#if __HYBRID_SIZEOF_TID__ > __SIZEOF_POINTER__
		__BYTE_TYPE__    __aorw_align[__HYBRID_SIZEOF_TID__]; /* Force threadid alignment. */
#endif /* __HYBRID_SIZEOF_TID__ > __SIZEOF_POINTER__ */
	};
	__hybrid_tid_t         aorw_owner; /* [valid_if(ATOMIC_READ(self->aorw_lock) & __ATOMIC_OWNER_RWLOCK_WFLAG)]
	                                    * A unique identifier for the thread owning this lock. */
#if __HYBRID_SIZEOF_TID__ < __SIZEOF_POINTER__
	__BYTE_TYPE__        __aorw_pad[__SIZEOF_POINTER__ - __HYBRID_SIZEOF_TID__]; /* ... */
#endif /* __HYBRID_SIZEOF_TID__ < __SIZEOF_POINTER__ */
};

#define ATOMIC_OWNER_RWLOCK_INIT             { { 0 }, __HYBRID_GETTID_INVALID }
#define ATOMIC_OWNER_RWLOCK_INIT_READ        { { 1 }, __HYBRID_GETTID_INVALID }
#ifdef __HYBRID_GETTID_INVALID_IS_ZERO
#define atomic_owner_rwlock_cinit(self)      (void)(__hybrid_assert((self)->aorw_lock == 0), __hybrid_assert((self)->aorw_owner == __HYBRID_GETTID_INVALID))
#define atomic_owner_rwlock_cinit_read(self) (void)(__hybrid_assert((self)->aorw_lock == 0), __hybrid_assert((self)->aorw_owner == __HYBRID_GETTID_INVALID), (self)->aorw_lock = 1)
#else /* __HYBRID_GETTID_INVALID_IS_ZERO */
#define atomic_owner_rwlock_cinit(self)      (void)(__hybrid_assert((self)->aorw_lock == 0), (self)->aorw_owner = __HYBRID_GETTID_INVALID)
#define atomic_owner_rwlock_cinit_read(self) (void)(__hybrid_assert((self)->aorw_lock == 0), (self)->aorw_lock = 1, (self)->aorw_owner = __HYBRID_GETTID_INVALID)
#endif /* !__HYBRID_GETTID_INVALID_IS_ZERO */
#define atomic_owner_rwlock_init(self)       (void)((self)->aorw_lock = 0, (self)->aorw_owner = __HYBRID_GETTID_INVALID)
#define atomic_owner_rwlock_init_read(self)  (void)((self)->aorw_lock = 1, (self)->aorw_owner = __HYBRID_GETTID_INVALID)

#define atomic_owner_rwlock_reading(x)   (__hybrid_atomic_load((x)->aorw_lock, __ATOMIC_ACQUIRE) != 0)
#define atomic_owner_rwlock_writing(x)   (__hybrid_atomic_load((x)->aorw_lock, __ATOMIC_ACQUIRE) & __ATOMIC_OWNER_RWLOCK_WFLAG && \
                                          __hybrid_gettid_iscaller((x)->aorw_owner))


/* Acquire an exclusive read/write lock. */
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_tryread)(struct atomic_owner_rwlock *__restrict __self);
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_trywrite)(struct atomic_owner_rwlock *__restrict __self);
__LOCAL void (atomic_owner_rwlock_read)(struct atomic_owner_rwlock *__restrict __self);
__LOCAL void (atomic_owner_rwlock_write)(struct atomic_owner_rwlock *__restrict __self);
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_read_nx)(struct atomic_owner_rwlock *__restrict __self);
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_write_nx)(struct atomic_owner_rwlock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Same as `atomic_owner_rwlock_trywrite()',  but allow for  the assumption  to
 * be made that the calling thread isn't already holding a write-lock to `self' */
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_trywrite_r)(struct atomic_owner_rwlock *__restrict __self);
__LOCAL void (atomic_owner_rwlock_write_r)(struct atomic_owner_rwlock *__restrict __self);
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_write_r_nx)(struct atomic_owner_rwlock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */


/* Try to upgrade a read-lock to a write-lock. Return `FALSE' upon failure. */
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_tryupgrade)(struct atomic_owner_rwlock *__restrict __self);

/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources. */
__LOCAL __ATTR_WUNUSED __BOOL (atomic_owner_rwlock_upgrade)(struct atomic_owner_rwlock *__restrict __self);

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held  temporarily, meaning that the caller  should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
__LOCAL __ATTR_WUNUSED unsigned int __NOTHROW(atomic_owner_rwlock_upgrade_nx)(struct atomic_owner_rwlock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Downgrade a write-lock to a read-lock (Always succeeds). */
__LOCAL void __NOTHROW(atomic_owner_rwlock_downgrade)(struct atomic_owner_rwlock *__restrict __self);

/* End reading/writing/either.
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __BOOL __NOTHROW(atomic_owner_rwlock_endwrite)(struct atomic_owner_rwlock *__restrict __self);
__LOCAL __BOOL __NOTHROW(atomic_owner_rwlock_endread)(struct atomic_owner_rwlock *__restrict __self);
__LOCAL __BOOL __NOTHROW(atomic_owner_rwlock_end)(struct atomic_owner_rwlock *__restrict __self);

/* Check if acquiring a read- or write-lock is possible without blocking */
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_canread)(struct atomic_owner_rwlock const *__restrict __self);
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_canwrite)(struct atomic_owner_rwlock const *__restrict __self);



#ifndef __INTELLISENSE__
__LOCAL __BOOL __NOTHROW(atomic_owner_rwlock_endwrite)(struct atomic_owner_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __f;
	__COMPILER_BARRIER();
	__hybrid_assertf(__hybrid_gettid_iscaller(__self->aorw_owner),
	                 "You're not the owner!\n"
	                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
	                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
	                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
	                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(__f & __ATOMIC_OWNER_RWLOCK_WFLAG,
		                 "Lock isn't in write-mode (%#lx)"
		                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
		                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
		                 (unsigned long)__f,
		                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
		                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
#if !defined(NDEBUG) && !defined(NDEBUG_SYNC)
		if (!(__f & __ATOMIC_OWNER_RWLOCK_NMASK))
			__self->aorw_owner = __HYBRID_GETTID_INVALID;
#endif /* !NDEBUG && !NDEBUG_SYNC */
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __f & __ATOMIC_OWNER_RWLOCK_NMASK ? __f - 1 : 0,
	                                      __ATOMIC_RELEASE, __ATOMIC_RELAXED));
	return __f & __ATOMIC_OWNER_RWLOCK_NMASK ? 0 : 1; /* Return `true' if the lock was released */
}

__LOCAL __BOOL __NOTHROW(atomic_owner_rwlock_endread)(struct atomic_owner_rwlock *__restrict __self) {
#if defined(NDEBUG) || defined(NDEBUG_SYNC)
	__COMPILER_READ_BARRIER();
	return __hybrid_atomic_fetchdec(__self->aorw_lock, __ATOMIC_RELEASE) == 1;
#else /* NDEBUG || NDEBUG_SYNC */
	__UINTPTR_TYPE__ __f;
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(__f != 0, "Lock isn't held by anyone");
		if (__f & __ATOMIC_OWNER_RWLOCK_WFLAG) {
			__hybrid_assertf(__f != __ATOMIC_OWNER_RWLOCK_WFLAG,
			                 "No more read-locks available. - You probably meant to close a write-lock");
			__hybrid_assertf(__hybrid_gettid_iscaller(__self->aorw_owner),
			                 "You're not the owner!\n"
			                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
			                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
			                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
			                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
		}
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __f - 1,
	                                      __ATOMIC_RELEASE, __ATOMIC_RELAXED));
	return __f == 1;
#endif /* !NDEBUG && !NDEBUG_SYNC */
}

__LOCAL __BOOL __NOTHROW(atomic_owner_rwlock_end)(struct atomic_owner_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __f, __newval;
	__COMPILER_BARRIER();
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(__f != 0, "Lock isn't held by anyone");
		__newval = __f - 1;
		if (__f & __ATOMIC_OWNER_RWLOCK_WFLAG) {
#if !defined(NDEBUG) && !defined(NDEBUG_SYNC)
			__hybrid_assertf(__hybrid_gettid_iscaller(__self->aorw_owner) ||
			                 __self->aorw_owner == __HYBRID_GETTID_INVALID,
			                 "Lock is in write-mode (%#lx)\n"
			                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
			                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
			                 (unsigned long)__f,
			                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
			                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
#endif /* !NDEBUG && !NDEBUG_SYNC */
			if (!(__f & __ATOMIC_OWNER_RWLOCK_NMASK)) {
#if !defined(NDEBUG) && !defined(NDEBUG_SYNC)
				__self->aorw_owner = __HYBRID_GETTID_INVALID;
#endif /* !NDEBUG && !NDEBUG_SYNC */
				__newval = 0;
			}
		}
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __newval,
	                                      __ATOMIC_RELEASE, __ATOMIC_RELAXED));
	return __newval == 0;
}

__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_tryread)(struct atomic_owner_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __f;
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		if (__f & __ATOMIC_OWNER_RWLOCK_WFLAG &&
		    !__hybrid_gettid_iscaller(__self->aorw_owner))
			return 0;
		__hybrid_assertf((__f & __ATOMIC_OWNER_RWLOCK_NMASK) != __ATOMIC_OWNER_RWLOCK_NMASK,
		                 "Too many locks (recursion?)");
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __f + 1,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_owner_rwlock_trywrite)(struct atomic_owner_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __f, __newval;
	__hybrid_tid_t __mytid = __hybrid_gettid();
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		if (__f & __ATOMIC_OWNER_RWLOCK_WFLAG) {
			if (!__hybrid_gettid_equal(__self->aorw_owner, __mytid))
				return 0;
			__newval = __f + 1;
		} else {
			if (__f)
				return 0;
			__newval = __ATOMIC_OWNER_RWLOCK_WFLAG;
		}
		__hybrid_assertf(__newval & __ATOMIC_OWNER_RWLOCK_WFLAG,
		                 "Too many write-locks");
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __newval,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	if (__newval == __ATOMIC_OWNER_RWLOCK_WFLAG)
		__self->aorw_owner = __mytid;
	__COMPILER_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_owner_rwlock_trywrite_r)(struct atomic_owner_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __f;
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(!(__f & __ATOMIC_OWNER_RWLOCK_WFLAG) ||
		                 !__hybrid_gettid_iscaller(__self->aorw_owner),
		                 "atomic_owner_rwlock_trywrite_r() cannot be used if you're "
		                 "already holding a write-lock to `self'\n"
		                 "Lock:   %#lx\n"
		                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
		                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
		                 (unsigned long)__f,
		                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
		                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
		if (__f)
			return 0;
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __ATOMIC_OWNER_RWLOCK_WFLAG,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	__self->aorw_owner = __hybrid_gettid();
	__COMPILER_BARRIER();
	return 1;
}

__LOCAL void (atomic_owner_rwlock_read)(struct atomic_owner_rwlock *__restrict __self) {
	while (!atomic_owner_rwlock_tryread(__self))
		__hybrid_yield();
	__COMPILER_READ_BARRIER();
}

__LOCAL void (atomic_owner_rwlock_write)(struct atomic_owner_rwlock *__restrict __self) {
	while (!atomic_owner_rwlock_trywrite(__self))
		__hybrid_yield();
	__COMPILER_BARRIER();
}

__LOCAL void (atomic_owner_rwlock_write_r)(struct atomic_owner_rwlock *__restrict __self) {
	while (!atomic_owner_rwlock_trywrite_r(__self))
		__hybrid_yield();
	__COMPILER_BARRIER();
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_owner_rwlock_read_nx)(struct atomic_owner_rwlock *__restrict __self) {
	while (!atomic_owner_rwlock_tryread(__self)) {
		if (!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_owner_rwlock_write_nx)(struct atomic_owner_rwlock *__restrict __self) {
	while (!atomic_owner_rwlock_trywrite(__self)) {
		if (!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_owner_rwlock_write_r_nx)(struct atomic_owner_rwlock *__restrict __self) {
	while (!atomic_owner_rwlock_trywrite_r(__self)) {
		if (!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

__LOCAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_owner_rwlock_tryupgrade)(struct atomic_owner_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __f;
	__hybrid_tid_t __mytid = __hybrid_gettid();
__again:
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		if (__f != 1) {
			if (__f & __ATOMIC_OWNER_RWLOCK_WFLAG &&
			    __hybrid_gettid_equal(__self->aorw_owner, __mytid)) {
				/* Do nothing when upgrading a read-lock ontop of a write-lock. */
				if (__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __f,
				                                __ATOMIC_RELEASE, __ATOMIC_RELAXED))
					goto __success;
				goto __again;
			}
			return 0;
		}
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, __ATOMIC_OWNER_RWLOCK_WFLAG,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	__self->aorw_owner = __mytid;
__success:
	__COMPILER_WRITE_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL
(atomic_owner_rwlock_upgrade)(struct atomic_owner_rwlock *__restrict __self) {
	if (atomic_owner_rwlock_tryupgrade(__self))
		return 1;
	atomic_owner_rwlock_endread(__self);
	atomic_owner_rwlock_write(__self);
	return 0;
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED unsigned int
__NOTHROW(atomic_owner_rwlock_upgrade_nx)(struct atomic_owner_rwlock *__restrict __self) {
	if (atomic_owner_rwlock_tryupgrade(__self))
		return 1;
	atomic_owner_rwlock_endread(__self);
	if (!atomic_owner_rwlock_write_nx(__self))
		return 0;
	return 2;
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

__LOCAL void
__NOTHROW(atomic_owner_rwlock_downgrade)(struct atomic_owner_rwlock *__restrict __self) {
#if defined(NDEBUG) || defined(NDEBUG_SYNC)
	__COMPILER_WRITE_BARRIER();
	ATOMIC_WRITE(__self->aorw_lock, 1);
#else /* NDEBUG || NDEBUG_SYNC */
	__UINTPTR_TYPE__ __f;
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__hybrid_gettid_iscaller(__self->aorw_owner),
	                 "You're not the owner!\n"
	                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
	                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
	                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
	                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
	do {
		__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(__f & __ATOMIC_OWNER_RWLOCK_WFLAG,
		                 "Lock not in write-mode (%#lx)"
		                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
		                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
		                 (unsigned long)__f,
		                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
		                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
		__hybrid_assertf(!(__f & __ATOMIC_OWNER_RWLOCK_NMASK),
		                 "Lock has more than one writer (%#lx)"
		                 "Caller: " __HYBRID_GETTID_PRINTF_FMT "\n"
		                 "Owner:  " __HYBRID_GETTID_PRINTF_FMT "\n",
		                 (unsigned long)__f,
		                 __HYBRID_GETTID_PRINTF_ARG(__hybrid_gettid()),
		                 __HYBRID_GETTID_PRINTF_ARG(__self->aorw_owner));
	} while (!__hybrid_atomic_cmpxch_weak(__self->aorw_lock, __f, 1,
	                                      __ATOMIC_RELEASE, __ATOMIC_RELAXED));
#endif /* !NDEBUG && !NDEBUG_SYNC */
}

__LOCAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_owner_rwlock_canread)(struct atomic_owner_rwlock const *__restrict __self) {
	return !(__hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE) & __ATOMIC_OWNER_RWLOCK_WFLAG) ||
	       __hybrid_gettid_iscaller(__self->aorw_owner);
}

__LOCAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_owner_rwlock_canwrite)(struct atomic_owner_rwlock const *__restrict __self) {
	__UINTPTR_TYPE__ __f;
	__f = __hybrid_atomic_load(__self->aorw_lock, __ATOMIC_ACQUIRE);
	return !__f || ((__f & __ATOMIC_OWNER_RWLOCK_WFLAG) && __hybrid_gettid_iscaller(__self->aorw_owner));
}
#endif /* !__INTELLISENSE__ */

#endif /* __CC__ */


#ifdef __DEFINE_SYNC_RWLOCK
__DEFINE_SYNC_RWLOCK(struct atomic_owner_rwlock,
                     atomic_owner_rwlock_tryread,
                     atomic_owner_rwlock_read,
                     atomic_owner_rwlock_read_nx,
                     atomic_owner_rwlock_endread,
                     atomic_owner_rwlock_reading,
                     atomic_owner_rwlock_canread,
                     atomic_owner_rwlock_trywrite,
                     atomic_owner_rwlock_write,
                     atomic_owner_rwlock_write_nx,
                     atomic_owner_rwlock_endwrite,
                     atomic_owner_rwlock_writing,
                     atomic_owner_rwlock_canwrite,
                     atomic_owner_rwlock_end,
                     atomic_owner_rwlock_tryupgrade,
                     atomic_owner_rwlock_upgrade,
                     atomic_owner_rwlock_upgrade_nx,
                     atomic_owner_rwlock_downgrade)
#endif /* __DEFINE_SYNC_RWLOCK */

__DECL_END

#endif /* !__GUARD_HYBRID_SYNC_ATOMIC_OWNER_RWLOCK_H */
