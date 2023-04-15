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
#ifndef __GUARD_HYBRID_SCHED_ATOMIC_LOCK_H
#define __GUARD_HYBRID_SCHED_ATOMIC_LOCK_H 1

#include "../../__stdinc.h"
#include "../__assert.h"
#include "../__atomic.h"
#include "../typecore.h"
#include "__preemption.h"
#ifndef __INTELLISENSE__
#include "__yield.h"
#endif /* !__INTELLISENSE__ */

#ifndef __NOPREEMPT
#define __NOPREEMPT /* Annotation for functions that may only be called with preemption disabled. */
#endif /* !__NOPREEMPT */

#define __SIZEOF_ATOMIC_LOCK __SIZEOF_INT__

#ifdef __CC__
__DECL_BEGIN

struct atomic_lock {
	unsigned int a_lock; /* Lock word. (non-zero if held) */
};

#define ATOMIC_LOCK_INIT                 { 0 }
#define ATOMIC_LOCK_INIT_ACQUIRED        { 1 }
#define atomic_lock_init(self)           (void)((self)->a_lock = 0)
#define atomic_lock_init_acquired(self)  (void)((self)->a_lock = 1)
#define atomic_lock_cinit(self)          __hybrid_assert((self)->a_lock == 0)
#define atomic_lock_cinit_acquired(self) (void)((self)->a_lock = 1)

#define atomic_lock_acquired(self)   (__hybrid_atomic_load(&(self)->a_lock, __ATOMIC_ACQUIRE) != 0)
#define atomic_lock_available(self)  (__hybrid_atomic_load(&(self)->a_lock, __ATOMIC_ACQUIRE) == 0)
#define atomic_lock_tryacquire(self) __likely(__hybrid_atomic_xch(&(self)->a_lock, 1, __ATOMIC_ACQUIRE) == 0)
#if defined(NDEBUG) || defined(NDEBUG_SYNC)
#define atomic_lock_release(self) _atomic_lock_release_NDEBUG(self)
#else /* NDEBUG || NDEBUG_SYNC */
#define atomic_lock_release(self) \
	(__hybrid_assert(atomic_lock_acquired(self)), _atomic_lock_release_NDEBUG(self))
#endif /* !NDEBUG || !NDEBUG_SYNC */
#define _atomic_lock_release_NDEBUG(self) \
	__hybrid_atomic_store(&(self)->a_lock, 0, __ATOMIC_RELEASE)


/* Acquire an exclusive lock. */
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void __NOTHROW(atomic_lock_acquire_nopr)(struct atomic_lock *__restrict __self);
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void __NOTHROW(atomic_lock_waitfor_nopr)(struct atomic_lock *__restrict __self);
#ifdef __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD
/* No need to have duplicate code -- if `__hybrid_preemption_tryyield_nopr()'
 * is  the same as `__hybrid_yield()', the `*_nopr' variant behaves just like
 * the normal variant! */
#define atomic_lock_acquire(self) atomic_lock_acquire_nopr(self)
#define atomic_lock_waitfor(self) atomic_lock_waitfor_nopr(self)
#else /* __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */
__LOCAL __ATTR_NONNULL((1)) void (atomic_lock_acquire)(struct atomic_lock *__restrict __self);
__LOCAL __ATTR_NONNULL((1)) void (atomic_lock_waitfor)(struct atomic_lock *__restrict __self);
#endif /* !__HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */

#define atomic_lock_release_nopr atomic_lock_release
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW(atomic_lock_acquire_nx)(struct atomic_lock *__restrict __self);
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW(atomic_lock_waitfor_nx)(struct atomic_lock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Acquire/release a given atomic_lock as an smp-lock
 * @param: __hybrid_preemption_flag_t *p_flag: preemption control flag. */
#define atomic_lock_acquire_smp_r(self, p_flag) __hybrid_preemption_acquire_smp_r(atomic_lock_tryacquire(self), p_flag)
#define atomic_lock_release_smp_r(self, p_flag) __hybrid_preemption_release_smp_r(atomic_lock_release(self), p_flag)
#define atomic_lock_acquire_smp_b(self)         __hybrid_preemption_acquire_smp_b(atomic_lock_tryacquire(self))
#define atomic_lock_release_smp_b(self)         __hybrid_preemption_release_smp_b(atomic_lock_release(self))
#define atomic_lock_acquire_smp(self)           __hybrid_preemption_acquire_smp(atomic_lock_tryacquire(self))
#define atomic_lock_release_smp(self)           __hybrid_preemption_release_smp(atomic_lock_release(self))


#ifndef __INTELLISENSE__
#ifndef __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD
__LOCAL __ATTR_NONNULL((1)) void
(atomic_lock_acquire)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_tryacquire(__self))
		__hybrid_yield();
	__COMPILER_READ_BARRIER();
}
__LOCAL __ATTR_NONNULL((1)) void
(atomic_lock_waitfor)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_available(__self))
		__hybrid_yield();
	__COMPILER_READ_BARRIER();
}
#endif /* !__HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */

__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void
__NOTHROW(atomic_lock_acquire_nopr)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_tryacquire(__self))
		__hybrid_preemption_tryyield_nopr();
	__COMPILER_READ_BARRIER();
}
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void
__NOTHROW(atomic_lock_waitfor_nopr)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_available(__self))
		__hybrid_preemption_tryyield_nopr();
	__COMPILER_READ_BARRIER();
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#ifndef __NO_builtin_expect
#define atomic_lock_acquire_nx(self) __builtin_expect(atomic_lock_acquire_nx(self), 1)
#define atomic_lock_waitfor_nx(self) __builtin_expect(atomic_lock_waitfor_nx(self), 1)
#endif /* !__NO_builtin_expect */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(atomic_lock_acquire_nx)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_tryacquire(__self)) {
		if __unlikely(!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(atomic_lock_waitfor_nx)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_available(__self)) {
		if __unlikely(!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#endif /* !__INTELLISENSE__ */

__DECL_END
#endif /* __CC__ */


#endif /* !__GUARD_HYBRID_SCHED_ATOMIC_LOCK_H */
