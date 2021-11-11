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
#ifndef GUARD_KERNEL_SRC_SCHED_SHARED_RWLOCK_C
#define GUARD_KERNEL_SRC_SCHED_SHARED_RWLOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <hybrid/atomic.h>
#include <sched/shared_rwlock.h>

#include <assert.h>
#include <stdbool.h>

DECL_BEGIN

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool FCALL
shared_rwlock_read_with_timeout(struct shared_rwlock *__restrict self,
                                ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK) {
	assert(!task_wasconnected());
	while (!shared_rwlock_tryread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_tryread(self))
				goto success;
		});
		task_connect(&self->sl_rdwait);
		if unlikely(shared_rwlock_tryread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}

PUBLIC BLOCKING NOCONNECT NONNULL((1)) void FCALL
shared_rwlock_write(struct shared_rwlock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	assert(!task_wasconnected());
	while (!shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(shared_rwlock_trywrite(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
success:
	COMPILER_BARRIER();
}

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool FCALL
shared_rwlock_write_with_timeout(struct shared_rwlock *__restrict self,
                                 ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK) {
	assert(!task_wasconnected());
	while (!shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(shared_rwlock_trywrite(self)) {
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

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict self) {
	assert(!task_wasconnected());
	while (!shared_rwlock_tryread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_tryread(self))
				goto success;
		});
		task_connect(&self->sl_rdwait);
		if unlikely(shared_rwlock_tryread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx())
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_read_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                  ktime_t abs_timeout) {
	assert(!task_wasconnected());
	while (!shared_rwlock_tryread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_tryread(self))
				goto success;
		});
		task_connect(&self->sl_rdwait);
		if unlikely(shared_rwlock_tryread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict self) {
	assert(!task_wasconnected());
	while (!shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(shared_rwlock_trywrite(self)) {
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

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_write_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                   ktime_t abs_timeout) {
	assert(!task_wasconnected());
	while (!shared_rwlock_trywrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_trywrite(self))
				goto success;
		});
		task_connect(&self->sl_wrwait);
		if unlikely(shared_rwlock_trywrite(self)) {
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


PUBLIC BLOCKING NOCONNECT NONNULL((1)) void FCALL
shared_rwlock_waitread(struct shared_rwlock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canread(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(shared_rwlock_canread(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
success:
	COMPILER_READ_BARRIER();
}

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool FCALL
shared_rwlock_waitread_with_timeout(struct shared_rwlock *__restrict self,
                                    ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canread(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(shared_rwlock_canread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}

PUBLIC BLOCKING NOCONNECT NONNULL((1)) void FCALL
shared_rwlock_waitwrite(struct shared_rwlock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canwrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canwrite(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(shared_rwlock_canwrite(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
success:
	COMPILER_BARRIER();
}

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool FCALL
shared_rwlock_waitwrite_with_timeout(struct shared_rwlock *__restrict self,
                                     ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canwrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canwrite(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(shared_rwlock_canwrite(self)) {
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

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict self) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canread(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(shared_rwlock_canread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx())
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_waitread_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                      ktime_t abs_timeout) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canread(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canread(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_rdwait);
		if unlikely(shared_rwlock_canread(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_READ_BARRIER();
	return true;
}

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict self) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canwrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canwrite(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(shared_rwlock_canwrite(self)) {
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

PUBLIC BLOCKING NOCONNECT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL shared_rwlock_waitwrite_with_timeout_nx)(struct shared_rwlock *__restrict self,
                                                       ktime_t abs_timeout) {
	assert(!task_wasconnected());
	while (!shared_rwlock_canwrite(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (shared_rwlock_canwrite(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_wrwait);
		if unlikely(shared_rwlock_canwrite(self)) {
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

#endif /* !GUARD_KERNEL_SRC_SCHED_SHARED_RWLOCK_C */
