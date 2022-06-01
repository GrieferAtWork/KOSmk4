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
#ifndef __GUARD_HYBRID_SCHED_ATOMIC_ONCE_H
#define __GUARD_HYBRID_SCHED_ATOMIC_ONCE_H 1

#include "../../__stdinc.h"
#include "../typecore.h"
#include "../__atomic.h"
#include "../__assert.h"

#ifndef __INTELLISENSE__
#include "__yield.h"
#endif /* !__INTELLISENSE__ */

__DECL_BEGIN

#define __ATOMIC_ONCE_PENDING 0 /* Pending execution. */
#define __ATOMIC_ONCE_RUNNING 1 /* Currently running. */
#define __ATOMIC_ONCE_RUNDONE 2 /* Was executed. */

#ifdef __CC__
struct atomic_once {
	__UINTPTR_TYPE__   ao_state;
};
#define ATOMIC_ONCE_INIT              { __ATOMIC_ONCE_PENDING }
#if __ATOMIC_ONCE_PENDING == 0
#define atomic_once_cinit(self)       (void)__hybrid_assert((self)->ao_state == __ATOMIC_ONCE_PENDING)
#else /* __ATOMIC_ONCE_PENDING == 0 */
#define atomic_once_cinit(self)       (void)((self)->ao_state = __ATOMIC_ONCE_PENDING)
#endif /* !__ATOMIC_ONCE_PENDING == 0 */
#define atomic_once_init(self)        (void)((self)->ao_state = __ATOMIC_ONCE_PENDING)

#define ATOMIC_ONCE_RUN(self, ...)     \
	do {                               \
		if (atomic_once_enter(self)) { \
			__VA_ARGS__;               \
			atomic_once_success(self); \
		}                              \
	}	__WHILE0


/* Enter the atomic-once block
 * @return: true:  The caller is now responsible for executing the associated function.
 * @return: false: The associated function has already been executed. */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL (atomic_once_enter)(struct atomic_once *__restrict __self);

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
/* Enter the atomic-once block
 * @return: * : One of `ATOMIC_ONCE_ENTER_NX_*'. */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned int __NOTHROW(atomic_once_enter_nx)(struct atomic_once *__restrict __self);
#define ATOMIC_ONCE_ENTER_NX_MUSTRUN    __ATOMIC_ONCE_PENDING /* Atomic-once successfully entered. */
#define ATOMIC_ONCE_ENTER_NX_WOULDBLOCK __ATOMIC_ONCE_RUNNING /* The operation would have blocked. */
#define ATOMIC_ONCE_ENTER_NX_ALREADY    __ATOMIC_ONCE_RUNDONE /* Atomic-once was already executed. */
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Try to enter the atomic-once block
 * @return: * : One of `ATOMIC_ONCE_TRYENTER_*' */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned int __NOTHROW(atomic_once_tryenter)(struct atomic_once *__restrict __self);
#define ATOMIC_ONCE_TRYENTER_MUSTRUN    __ATOMIC_ONCE_PENDING /* Atomic-once successfully entered. */
#define ATOMIC_ONCE_TRYENTER_INPROGRESS __ATOMIC_ONCE_RUNNING /* Atomic-once is currently being run by another thread (the caller should yield() and try again later). */
#define ATOMIC_ONCE_TRYENTER_ALREADY    __ATOMIC_ONCE_RUNDONE /* Atomic-once was already executed. */

/* Indicate a successful completion of the associated function */
__LOCAL __ATTR_NONNULL((1)) void __NOTHROW(atomic_once_success)(struct atomic_once *__restrict __self);

/* Indicate a failed completion of the associated function */
__LOCAL __ATTR_NONNULL((1)) void __NOTHROW(atomic_once_abort)(struct atomic_once *__restrict __self);


#ifndef __INTELLISENSE__

/* Enter the atomic-once block
 * @return: true:  The caller is now responsible for executing the associated function.
 * @return: false: The associated function has already been executed. */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL (atomic_once_enter)(struct atomic_once *__restrict __self) {
	__UINTPTR_TYPE__ __state;
	for (;;) {
		__state = __hybrid_atomic_load(__self->ao_state, __ATOMIC_ACQUIRE);
		if (__state == __ATOMIC_ONCE_RUNDONE)
			break;
		if (__state == __ATOMIC_ONCE_PENDING) {
			if (__hybrid_atomic_cmpxch_weak(__self->ao_state,
			                                __ATOMIC_ONCE_PENDING,
			                                __ATOMIC_ONCE_RUNNING,
			                                __ATOMIC_SEQ_CST,
			                                __ATOMIC_SEQ_CST))
				return 1;
			continue;
		}
		__hybrid_assertf(__state == __ATOMIC_ONCE_RUNNING,
		                 "atomic_once_enter(%p) : Invalid state: %p",
		                 __self, (void *)__state);
		__hybrid_yield();
	}
	return 0;
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
/* Enter the atomic-once block
 * @return: * : One of `ATOMIC_ONCE_ENTER_NX_*'. */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned int
__NOTHROW(atomic_once_enter_nx)(struct atomic_once *__restrict __self) {
	__UINTPTR_TYPE__ __state;
	for (;;) {
		__state = __hybrid_atomic_load(__self->ao_state, __ATOMIC_ACQUIRE);
		if (__state == __ATOMIC_ONCE_RUNDONE)
			break;
		if (__state == __ATOMIC_ONCE_PENDING) {
			if (__hybrid_atomic_cmpxch_weak(__self->ao_state,
			                                __ATOMIC_ONCE_PENDING,
			                                __ATOMIC_ONCE_RUNNING,
			                                __ATOMIC_SEQ_CST,
			                                __ATOMIC_SEQ_CST))
				return ATOMIC_ONCE_ENTER_NX_MUSTRUN;
			continue;
		}
		__hybrid_assertf(__state == __ATOMIC_ONCE_RUNNING,
		                 "atomic_once_enter_nx(%p) : Invalid state: %p",
		                 __self, (void *)__state);
		if (!__hybrid_yield_nx())
			return ATOMIC_ONCE_ENTER_NX_WOULDBLOCK;
	}
	return ATOMIC_ONCE_ENTER_NX_ALREADY;
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Try to enter the atomic-once block
 * @return: * : One of `ATOMIC_ONCE_TRYENTER_*' */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned int
__NOTHROW(atomic_once_tryenter)(struct atomic_once *__restrict __self) {
	__UINTPTR_TYPE__ __state;
	for (;;) {
		__state = __hybrid_atomic_load(__self->ao_state, __ATOMIC_ACQUIRE);
		if (__state == __ATOMIC_ONCE_RUNDONE)
			break;
		if (__state == __ATOMIC_ONCE_PENDING) {
			if (__hybrid_atomic_cmpxch_weak(__self->ao_state,
			                                __ATOMIC_ONCE_PENDING,
			                                __ATOMIC_ONCE_RUNNING,
			                                __ATOMIC_SEQ_CST,
			                                __ATOMIC_SEQ_CST))
				return ATOMIC_ONCE_TRYENTER_MUSTRUN;
			continue;
		}
		__hybrid_assertf(__state == __ATOMIC_ONCE_RUNNING,
		                 "atomic_once_tryenter(%p) : Invalid state: %p",
		                 __self, (void *)__state);
		break;
	}
	return __state;
}

/* Indicate a successful completion of the associated function */
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(atomic_once_success)(struct atomic_once *__restrict __self) {
#if !defined(NDEBUG) && !defined(NDEBUG_SYNC)
	__UINTPTR_TYPE__ __state;
	do {
		__state = __self->ao_state;
		__hybrid_assertf(__self->ao_state == __ATOMIC_ONCE_RUNNING,
		                 "atomic_once_success(%p): Invalid state: %p", (void *)__state);
	} while (!__hybrid_atomic_cmpxch_weak(__self->ao_state,
	                                      __ATOMIC_ONCE_RUNNING,
	                                      __ATOMIC_ONCE_RUNDONE,
	                                      __ATOMIC_RELEASE,
	                                      __ATOMIC_RELEASE));
#else /* !NDEBUG && !NDEBUG_SYNC */
	__hybrid_atomic_store(__self->ao_state, __ATOMIC_ONCE_RUNDONE, __ATOMIC_RELEASE);
#endif /* NDEBUG || NDEBUG_SYNC */
}

/* Indicate a failed completion of the associated function */
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(atomic_once_abort)(struct atomic_once *__restrict __self) {
#if !defined(NDEBUG) && !defined(NDEBUG_SYNC)
	__UINTPTR_TYPE__ __state;
	do {
		__state = __self->ao_state;
		__hybrid_assertf(__self->ao_state == __ATOMIC_ONCE_RUNNING,
		                 "atomic_once_success(%p): Invalid state: %p", (void *)__state);
	} while (!__hybrid_atomic_cmpxch_weak(__self->ao_state,
	                                      __ATOMIC_ONCE_RUNNING,
	                                      __ATOMIC_ONCE_PENDING,
	                                      __ATOMIC_RELEASE,
	                                      __ATOMIC_RELEASE));
#else /* !NDEBUG && !NDEBUG_SYNC */
	__hybrid_atomic_store(__self->ao_state, __ATOMIC_ONCE_PENDING, __ATOMIC_RELEASE);
#endif /* NDEBUG || NDEBUG_SYNC */
}

#endif /* !__INTELLISENSE__ */


#endif /* __CC__ */


__DECL_END

#endif /* !__GUARD_HYBRID_SCHED_ATOMIC_ONCE_H */
