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
#ifndef __GUARD_HYBRID_SYNC_ATOMIC_LOCK_H
#define __GUARD_HYBRID_SYNC_ATOMIC_LOCK_H 1

#include "../../__stdinc.h"
#include "../typecore.h"
#include "../__atomic.h"
#include "../__assert.h"
#ifndef __INTELLISENSE__
#include "../sched/__yield.h"
#endif /* !__INTELLISENSE__ */
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#ifndef __INTELLISENSE__
#include <sched/task.h> /* task_pause() */
#endif /* !__INTELLISENSE__ */
#include <kos/anno.h>   /* __NOPREEMPT */
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */


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

#define atomic_lock_acquired(self)   (__hybrid_atomic_load((self)->a_lock, __ATOMIC_ACQUIRE) != 0)
#define atomic_lock_available(self)  (__hybrid_atomic_load((self)->a_lock, __ATOMIC_ACQUIRE) == 0)
#define atomic_lock_tryacquire(self) (__hybrid_atomic_xch((self)->a_lock, 1, __ATOMIC_ACQUIRE) == 0)
#if defined(NDEBUG) || defined(NDEBUG_SYNC)
#define atomic_lock_release(self) \
	__hybrid_atomic_store((self)->a_lock, 0, __ATOMIC_RELEASE)
#else /* NDEBUG || NDEBUG_SYNC */
#define atomic_lock_release(self)          \
	(__hybrid_assert((self)->a_lock != 0), \
	 __hybrid_atomic_store((self)->a_lock, 0, __ATOMIC_RELEASE))
#endif /* !NDEBUG || !NDEBUG_SYNC */


/* Acquire an exclusive lock. */
__LOCAL __ATTR_NONNULL((1)) void (atomic_lock_acquire)(struct atomic_lock *__restrict __self);
__LOCAL __ATTR_NONNULL((1)) void (atomic_lock_waitfor)(struct atomic_lock *__restrict __self);
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW(atomic_lock_acquire_nx)(struct atomic_lock *__restrict __self);
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW(atomic_lock_waitfor_nx)(struct atomic_lock *__restrict __self);
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void __NOTHROW(atomic_lock_acquire_nopr)(struct atomic_lock *__restrict __self);
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void __NOTHROW(atomic_lock_waitfor_nopr)(struct atomic_lock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

#if !defined(__INTELLISENSE__) && !defined(__NO_builtin_expect)
#undef atomic_lock_tryacquire
#define atomic_lock_tryacquire(self) __builtin_expect(__hybrid_atomic_xch((self)->a_lock, 1, __ATOMIC_ACQUIRE) == 0, 1)
#define atomic_lock_acquire_nx(self) __builtin_expect(atomic_lock_acquire_nx(self), 1)
#define atomic_lock_waitfor_nx(self) __builtin_expect(atomic_lock_waitfor_nx(self), 1)
#endif /* !__INTELLISENSE__ && !__NO_builtin_expect */

#ifndef __INTELLISENSE__
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
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
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
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void
__NOTHROW(atomic_lock_acquire_nopr)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_tryacquire(__self))
		task_pause();
	__COMPILER_READ_BARRIER();
}
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void
__NOTHROW(atomic_lock_waitfor_nopr)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_available(__self))
		task_pause();
	__COMPILER_READ_BARRIER();
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#endif /* !__INTELLISENSE__ */


#ifdef __DEFINE_SYNC_MUTEX
__DEFINE_SYNC_MUTEX(struct atomic_lock,
                    atomic_lock_tryacquire,
                    atomic_lock_acquire,
                    atomic_lock_acquire_nx,
                    atomic_lock_release,
                    atomic_lock_acquired,
                    atomic_lock_available)
#endif /* __DEFINE_SYNC_MUTEX */

__DECL_END
#endif /* __CC__ */


#endif /* !__GUARD_HYBRID_SYNC_ATOMIC_LOCK_H */
