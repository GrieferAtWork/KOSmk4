/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_MUTEX_H
#define GUARD_KERNEL_INCLUDE_SCHED_MUTEX_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/signal.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__
struct task;
struct timespec;

struct mutex {
	struct sig        m_unlock; /* Signal send when the mutex is unlocked. */
	WEAK struct task *m_owner;  /* [0..1][lock(WRITE_IF(== NULL),CLEAR_IF(== THIS_TASK))] The owner of this mutex. */
	uintptr_t         m_count;  /* [lock(PRIVATE(m_owner == THIS_TASK))] Number of recursive locks (== 1 for the first lock). */
};
#define MUTEX_INIT          { SIG_INIT, __NULLPTR, 0 }
#define mutex_init(x)       (void)(sig_init(&(x)->m_unlock), (x)->m_owner = __NULLPTR, (x)->m_count = 0)
#define mutex_cinit(x)      (void)(sig_cinit(&(x)->m_unlock), __hybrid_assert((x)->m_owner == __NULLPTR), __hybrid_assert((x)->m_count == 0))
#define mutex_init_held(x)  (void)(sig_init(&(x)->m_unlock), (x)->m_owner = THIS_TASK, (x)->m_count = 1)
#define mutex_cinit_held(x) (void)(sig_cinit(&(x)->m_unlock), (x)->m_owner = THIS_TASK, (x)->m_count = 1)
#define mutex_acquired(x)   (__hybrid_atomic_load((x)->m_owner, __ATOMIC_ACQUIRE) == THIS_TASK)

/* Try to acquire a lock to the given mutex without blocking. */
LOCAL NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL mutex_tryacquire)(struct mutex *__restrict self) {
	struct task *old_task, *me = THIS_TASK;
	do {
		old_task = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
		if (old_task) {
			if (old_task == me) {
				++self->m_count;
				__COMPILER_WRITE_BARRIER();
				return true;
			}
			return false;
		}
	} while (!__hybrid_atomic_cmpxch_weak(self->m_owner, old_task, me,
	                                      __ATOMIC_SEQ_CST,
	                                      __ATOMIC_SEQ_CST));
	self->m_count = 1;
	__COMPILER_WRITE_BARRIER();
	return true;
}

/* Same as `mutex_acquire()', but it's unlikely that
 * the lock can be acquired without blocking. */
#define mutex_acquire_unlikely mutex_acquire

/* Acquire a lock to the given mutex, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
LOCAL NONNULL((1)) bool
(KCALL mutex_acquire)(struct mutex *__restrict self,
                      struct timespec const *abs_timeout DFL(__NULLPTR))
                      THROWS(E_WOULDBLOCK,...) {
	struct task *old_task, *me = THIS_TASK;
again:
	do {
		old_task = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
		if (old_task) {
			if (old_task == me) {
				++self->m_count;
				__COMPILER_WRITE_BARRIER();
				return true;
			}
			TASK_POLL_BEFORE_CONNECT({
				old_task = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
				if (!old_task)
					goto do_exchange;
			});
			task_connect(&self->m_unlock);
			old_task = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
			if likely(old_task) {
				if unlikely(!task_waitfor(abs_timeout))
					return false;
				goto again;
			}
			task_disconnectall();
		}
#ifdef CONFIG_YIELD_BEFORE_CONNECT
do_exchange:
		;
#endif /* CONFIG_YIELD_BEFORE_CONNECT */
	} while (!__hybrid_atomic_cmpxch_weak(self->m_owner, old_task, me,
	                                      __ATOMIC_SEQ_CST,
	                                      __ATOMIC_SEQ_CST));
	self->m_count = 1;
	__COMPILER_WRITE_BARRIER();
	return true;
}

/* Acquire a lock to the given mutex, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
LOCAL WUNUSED NONNULL((1)) bool
NOTHROW(KCALL mutex_acquire_nx)(struct mutex *__restrict self,
                                struct timespec const *abs_timeout DFL(__NULLPTR)) {
	struct task *old_task, *me = THIS_TASK;
again:
	do {
		old_task = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
		if (old_task) {
			if (old_task == me) {
				++self->m_count;
				__COMPILER_WRITE_BARRIER();
				return true;
			}
			TASK_POLL_BEFORE_CONNECT({
				old_task = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
				if (!old_task)
					goto do_exchange;
			});
			task_connect(&self->m_unlock);
			old_task = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
			if likely(old_task) {
				if unlikely(!task_waitfor_nx(abs_timeout))
					return false;
				goto again;
			}
			task_disconnectall();
		}
#ifdef CONFIG_YIELD_BEFORE_CONNECT
do_exchange:
		;
#endif /* CONFIG_YIELD_BEFORE_CONNECT */
	} while (!__hybrid_atomic_cmpxch_weak(self->m_owner, old_task, me,
	                                      __ATOMIC_SEQ_CST,
	                                      __ATOMIC_SEQ_CST));
	self->m_count = 1;
	__COMPILER_WRITE_BARRIER();
	return true;
}


/* Release a lock from a given mutex.
 * @return: true:  A waiting thread was signaled.
 * @return: false: Either no thread was signaled, or the
 *                 lock remains held by the calling thread. */
LOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mutex_release)(struct mutex *__restrict self) {
	__hybrid_assertf(self->m_owner == THIS_TASK,
	                 "You're not holding a lock to this mutex!");
	__hybrid_assertf(self->m_count >= 1, "Invalid mutex state");
	--self->m_count;
	if (self->m_count == 0) {
		__hybrid_atomic_store(self->m_owner, __NULLPTR, __ATOMIC_RELEASE);
		/* Signal a single waiting thread that the mutex is now available. */
		return sig_send(&self->m_unlock);
	}
	return false;
}

/* Release a lock from a given mutex.
 * @return: true:  The lock was released.
 * @return: false: The calling thread continues to hold the lock. */
LOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mutex_release_r)(struct mutex *__restrict self) {
	__hybrid_assertf(self->m_owner == THIS_TASK,
	                 "You're not holding a lock to this mutex!");
	__hybrid_assertf(self->m_count >= 1, "Invalid mutex state");
	--self->m_count;
	if (self->m_count == 0) {
		__hybrid_atomic_store(self->m_owner, __NULLPTR, __ATOMIC_RELEASE);
		/* Signal a single waiting thread that the mutex is now available. */
		sig_send(&self->m_unlock);
		return true;
	}
	return false;
}



LOCAL NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL mutex_available)(struct mutex const *__restrict self) {
	struct task *owner;
	owner = __hybrid_atomic_load(self->m_owner, __ATOMIC_ACQUIRE);
	return !owner || owner == THIS_TASK;
}

/* Mutex polling functions. */
#define mutex_pollconnect_ex(self, cb) cb(&(self)->m_unlock)
#define mutex_poll_unlikely_ex(self, cb) \
	(mutex_pollconnect_ex(self, cb),     \
	 mutex_available(self))
#ifdef __OPTIMIZE_SIZE__
#define mutex_poll_ex(self, cb)      \
	mutex_poll_unlikely_ex(self, cb)
#else /* __OPTIMIZE_SIZE__ */
#define mutex_poll_ex(self, cb)       \
	(mutex_available(self) ||         \
	 (mutex_pollconnect_ex(self, cb), \
	  mutex_available(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#define mutex_pollconnect(self)   mutex_pollconnect_ex(self, task_connect_for_poll)
#define mutex_poll(self)          mutex_poll_ex(self, task_connect_for_poll)
#define mutex_poll_unlikely(self) mutex_poll_unlikely_ex(self, task_connect_for_poll)


/* Integration into the sync_* API-system. */
__DEFINE_SYNC_MUTEX(struct mutex,
                    mutex_tryacquire,
                    mutex_acquire,
                    mutex_acquire_nx,
                    mutex_release,
                    mutex_acquired,
                    mutex_available)

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_MUTEX_H */
