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
#ifndef GUARD_KERNEL_SRC_SCHED_SEMAPHORE_C
#define GUARD_KERNEL_SRC_SCHED_SEMAPHORE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/semaphore.h>
#include <sched/sig.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stdint.h>

DECL_BEGIN

/* Acquire a ticked from the given semaphore, or block until `abs_timeout'.
 * @return: true:  Successfully acquired a ticket.
 * @return: false: The given `abs_timeout' has expired. */
PUBLIC BLOCKING NONNULL((1)) bool FCALL
semaphore_wait(struct semaphore *__restrict self, ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK) {
	uintptr_t count;
again:
	assert(!task_wasconnected());
	do {
		count = atomic_read(&self->s_count);
		if (!count) {
			TASK_POLL_BEFORE_CONNECT({
				count = atomic_read(&self->s_count);
				if (count != 0)
					goto do_exchange;
			});
			task_connect(&self->s_avail);
			count = atomic_read(&self->s_count);
			if likely(!count) {
				if unlikely(!task_waitfor(abs_timeout))
					return false;
				goto again;
			}
			task_disconnectall();
		}
#ifdef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
do_exchange:
		;
#endif /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT */
	} while (!atomic_cmpxch_weak(&self->s_count, count, count - 1));
	return true;
}


/* Acquire a ticked from the given semaphore, or block until `abs_timeout'.
 * @return: true:  Successfully acquired a ticket.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool
NOTHROW(FCALL semaphore_wait_nx)(struct semaphore *__restrict self,
                                 ktime_t abs_timeout) {
	uintptr_t count;
again:
	assert(!task_wasconnected());
	do {
		count = atomic_read(&self->s_count);
		if (!count) {
			TASK_POLL_BEFORE_CONNECT({
				count = atomic_read(&self->s_count);
				if (count != 0)
					goto do_exchange;
			});
			task_connect(&self->s_avail);
			count = atomic_read(&self->s_count);
			if likely(!count) {
				if unlikely(!task_waitfor_nx(abs_timeout))
					return false;
				goto again;
			}
			task_disconnectall();
		}
#ifdef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
do_exchange:
		;
#endif /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT */
	} while (!atomic_cmpxch_weak(&self->s_count, count, count - 1));
	return true;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_SEMAPHORE_C */
