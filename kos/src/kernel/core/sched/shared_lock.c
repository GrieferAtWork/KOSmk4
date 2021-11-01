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
#ifndef GUARD_KERNEL_SRC_SCHED_SHARED_LOCK_C
#define GUARD_KERNEL_SRC_SCHED_SHARED_LOCK_C 1

#include <kernel/compiler.h>

#include <sched/shared_lock.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stdbool.h>

DECL_BEGIN

/* Acquire a lock to the given shared_lock. */
PUBLIC BLOCKING NONNULL((1)) void FCALL
shared_lock_acquire(struct shared_lock *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	assert(!task_wasconnected());
	while (!shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
success:
	COMPILER_BARRIER();
}

/* Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
shared_lock_acquire_with_timeout(struct shared_lock *__restrict self,
                                 ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK, ...) {
	assert(!task_wasconnected());
	while (!shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}

/* Acquire a lock to the given shared_lock.
 * @return: true:  Successfully acquired a lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_lock_acquire_nx)(struct shared_lock *__restrict self) {
	assert(!task_wasconnected());
	while (!shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx())
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}

/* Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_lock_acquire_with_timeout_nx)(struct shared_lock *__restrict self,
                                                   ktime_t abs_timeout) {
	assert(!task_wasconnected());
	while (!shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}


/* Acquire a lock to the given shared_lock. */
PUBLIC BLOCKING NONNULL((1)) void FCALL
shared_lock_waitfor(struct shared_lock *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	assert(!task_wasconnected());
	while (!shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_available(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
success:
	COMPILER_BARRIER();
}

/* Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
shared_lock_waitfor_with_timeout(struct shared_lock *__restrict self,
                                 ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK, ...) {
	assert(!task_wasconnected());
	while (!shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_available(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}

/* Acquire a lock to the given shared_lock.
 * @return: true:  The lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_lock_waitfor_nx)(struct shared_lock *__restrict self) {
	assert(!task_wasconnected());
	while (!shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_available(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx())
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}

/* Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_lock_waitfor_with_timeout_nx)(struct shared_lock *__restrict self,
                                                   ktime_t abs_timeout) {
	assert(!task_wasconnected());
	while (!shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_lock_available(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_SHARED_LOCK_C */
