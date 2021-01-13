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
#ifndef GUARD_KERNEL_SRC_SCHED_MUTEX_C
#define GUARD_KERNEL_SRC_SCHED_MUTEX_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <hybrid/atomic.h>
#include <sched/mutex.h>

#include <stdbool.h>

DECL_BEGIN

/* Acquire a lock to the given mutex, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
PUBLIC NONNULL((1)) bool KCALL
mutex_acquire(struct mutex *__restrict self, ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK, ...) {
	struct task *old_task, *me = THIS_TASK;
again:
	do {
		old_task = ATOMIC_READ(self->m_owner);
		if (old_task) {
			if (old_task == me) {
				++self->m_count;
				COMPILER_WRITE_BARRIER();
				return true;
			}
			TASK_POLL_BEFORE_CONNECT({
				old_task = ATOMIC_READ(self->m_owner);
				if (!old_task)
					goto do_exchange;
			});
			task_connect(&self->m_unlock);
			old_task = ATOMIC_READ(self->m_owner);
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
	} while (!ATOMIC_CMPXCH_WEAK(self->m_owner, old_task, me));
	self->m_count = 1;
	COMPILER_WRITE_BARRIER();
	return true;
}

/* Acquire a lock to the given mutex, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL mutex_acquire_nx)(struct mutex *__restrict self,
                                ktime_t abs_timeout) {
	struct task *old_task, *me = THIS_TASK;
again:
	do {
		old_task = ATOMIC_READ(self->m_owner);
		if (old_task) {
			if (old_task == me) {
				++self->m_count;
				COMPILER_WRITE_BARRIER();
				return true;
			}
			TASK_POLL_BEFORE_CONNECT({
				old_task = ATOMIC_READ(self->m_owner);
				if (!old_task)
					goto do_exchange;
			});
			task_connect(&self->m_unlock);
			old_task = ATOMIC_READ(self->m_owner);
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
	} while (!ATOMIC_CMPXCH_WEAK(self->m_owner, old_task, me));
	self->m_count = 1;
	COMPILER_WRITE_BARRIER();
	return true;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_MUTEX_C */
