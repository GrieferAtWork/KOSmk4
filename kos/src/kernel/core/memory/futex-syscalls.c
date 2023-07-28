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
#ifndef GUARD_KERNEL_SRC_MEMORY_FUTEX_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_FUTEX_SYSCALLS_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/panic.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/group.h>
#include <sched/tsc.h>

#include <bits/os/timespec.h>
#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <kos/futex.h>
#include <kos/futexexpr.h>
#include <linux/futex.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <stddef.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/timespec.h>
#include <compat/kos/futex.h>
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN





/************************************************************************/
/* futex()                                                              */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FUTEX) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTEX))
#define WANT_FUTEX 1
#endif /* futex... */

#ifdef WANT_FUTEX
/* XXX: Check  if these are all of them (you'll see if they
 *      are when you actually implement `sys_futex_impl()') */
#define LINUX_FUTEX_USES_TIMEOUT(futex_op)    \
	(((futex_op)&127) == FUTEX_WAIT ||        \
	 ((futex_op)&127) == FUTEX_LOCK_PI ||     \
	 ((futex_op)&127) == FUTEX_WAIT_BITSET || \
	 ((futex_op)&127) == FUTEX_WAIT_REQUEUE_PI)

/* Futex system call used for linux compatibility.
 * When targeting KOS specifically, you are advised to make use of lfutex() instead */
PRIVATE syscall_slong_t KCALL
sys_futex_impl(NCX UNCHECKED uint32_t *uaddr,
               syscall_ulong_t futex_op,
               uint32_t val,
               ktime_t timeout,
               uint32_t val2,
               NCX UNCHECKED uint32_t *uaddr2,
               uint32_t val3) {
	syscall_slong_t result;
	REF struct mfutex *f;
	assert(!task_wasconnected());
	switch (futex_op & 127) {

	case FUTEX_WAIT_BITSET: /* XXX: Channel support? */
	case FUTEX_WAIT: {
		/* while(*uaddr == val) wait(uaddr, rel_timeout); */
		validate_user(uaddr, sizeof(*uaddr));
		f = mman_createfutex(THIS_MMAN, uaddr);
		FINALLY_DECREF(f);
		mfutex_connect(f);
		TRY {
			result = 0;
			if (atomic_read(uaddr) == val) {
				if (!task_waitfor(timeout))
					result = -ETIMEDOUT;
			} else {
				task_disconnectall();
			}
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
	}	break;

	case FUTEX_WAKE_BITSET: /* XXX: Channel support? */
	case FUTEX_WAKE: /* wake(uaddr); */
		validate_user(uaddr, 1);
		f = mman_lookupfutex(THIS_MMAN, uaddr);
		result = 0;
		if (f) {
			if (val == (uint32_t)-1) {
				result = mfutex_broadcast(f);
			} else {
				/* Only signal at most `val' connected threads. */
				result = mfutex_sendmany(f, (size_t)val);
			}
			decref_unlikely(f);
		}
		break;

	// TODO: case FUTEX_FD:
	// TODO: case FUTEX_REQUEUE:
	// TODO: case FUTEX_CMP_REQUEUE:
	// TODO: case FUTEX_WAKE_OP:
	// TODO: case FUTEX_LOCK_PI:
	// TODO: case FUTEX_UNLOCK_PI:
	// TODO: case FUTEX_TRYLOCK_PI:
	// TODO: case FUTEX_WAIT_REQUEUE_PI:
	// TODO: case FUTEX_CMP_REQUEUE_PI:
		(void)val2;
		(void)uaddr2;
		(void)val3;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_FUTEX_OP,
		      futex_op);
		break;
	}
	assert(!task_wasconnected());
	return result;
}
#endif /* WANT_FUTEX */

#ifdef __ARCH_WANT_SYSCALL_FUTEX
DEFINE_SYSCALL6(syscall_slong_t, futex,
                NCX UNCHECKED uint32_t *, uaddr,
                syscall_ulong_t, futex_op,
                uint32_t, val,
                NCX UNCHECKED struct timespec32 const *, timeout_or_val2,
                NCX UNCHECKED uint32_t *, uaddr2,
                uint32_t, val3) {
	syscall_slong_t result;
	ktime_t timeout = KTIME_INFINITE;
	if (LINUX_FUTEX_USES_TIMEOUT(futex_op) && timeout_or_val2) {
		/* `FUTEX_WAIT' takes a relative timeout, while all others takes an absolute one. */
		if ((futex_op & 127) == FUTEX_WAIT) {
			timeout = ktime() + relktime_from_user_rel(timeout_or_val2);
		} else {
			timeout = ktime_from_user(timeout_or_val2);
		}
	}
	result = sys_futex_impl(uaddr, futex_op, val, timeout,
	                        (uint32_t)(uintptr_t)timeout_or_val2,
	                        uaddr2, val3);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_FUTEX */

#ifdef __ARCH_WANT_SYSCALL_FUTEX_TIME64
DEFINE_SYSCALL6(syscall_slong_t, futex_time64,
                NCX UNCHECKED uint32_t *, uaddr,
                syscall_ulong_t, futex_op,
                uint32_t, val,
                NCX UNCHECKED struct timespec64 const *, timeout_or_val2,
                NCX UNCHECKED uint32_t *, uaddr2,
                uint32_t, val3) {
	syscall_slong_t result;
	ktime_t timeout = KTIME_INFINITE;
	if (LINUX_FUTEX_USES_TIMEOUT(futex_op) && timeout_or_val2) {
		/* `FUTEX_WAIT' takes a relative timeout, while all others takes an absolute one. */
		if ((futex_op & 127) == FUTEX_WAIT) {
			timeout = ktime() + relktime_from_user_rel(timeout_or_val2);
		} else {
			timeout = ktime_from_user(timeout_or_val2);
		}
	}
	result = sys_futex_impl(uaddr, futex_op, val, timeout,
	                        (uint32_t)(uintptr_t)timeout_or_val2,
	                        uaddr2, val3);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_FUTEX_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FUTEX
DEFINE_COMPAT_SYSCALL6(syscall_slong_t, futex,
                       NCX UNCHECKED uint32_t *, uaddr,
                       syscall_ulong_t, futex_op,
                       uint32_t, val,
                       NCX UNCHECKED struct compat_timespec32 const *, timeout_or_val2,
                       NCX UNCHECKED uint32_t *, uaddr2,
                       uint32_t, val3) {
	syscall_slong_t result;
	ktime_t timeout = KTIME_INFINITE;
	if (LINUX_FUTEX_USES_TIMEOUT(futex_op) && timeout_or_val2) {
		/* `FUTEX_WAIT' takes a relative timeout, while all others takes an absolute one. */
		if ((futex_op & 127) == FUTEX_WAIT) {
			timeout = ktime() + relktime_from_user_rel(timeout_or_val2);
		} else {
			timeout = ktime_from_user(timeout_or_val2);
		}
	}
	result = sys_futex_impl(uaddr, futex_op, val, timeout,
	                        (uint32_t)(uintptr_t)timeout_or_val2,
	                        uaddr2, val3);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FUTEX */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FUTEX_TIME64
DEFINE_COMPAT_SYSCALL6(syscall_slong_t, futex_time64,
                       NCX UNCHECKED uint32_t *, uaddr,
                       syscall_ulong_t, futex_op,
                       uint32_t, val,
                       NCX UNCHECKED struct compat_timespec64 const *, timeout_or_val2,
                       NCX UNCHECKED uint32_t *, uaddr2,
                       uint32_t, val3) {
	syscall_slong_t result;
	ktime_t timeout = KTIME_INFINITE;
	if (LINUX_FUTEX_USES_TIMEOUT(futex_op) && timeout_or_val2) {
		/* `FUTEX_WAIT' takes a relative timeout, while all others takes an absolute one. */
		if ((futex_op & 127) == FUTEX_WAIT) {
			timeout = ktime() + relktime_from_user_rel(timeout_or_val2);
		} else {
			timeout = ktime_from_user(timeout_or_val2);
		}
	}
	result = sys_futex_impl(uaddr, futex_op, val, timeout,
	                        (uint32_t)(uintptr_t)timeout_or_val2,
	                        uaddr2, val3);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FUTEX_TIME64 */

DECL_END

#ifndef __INTELLISENSE__
#if (defined(__ARCH_WANT_SYSCALL_LFUTEX) || \
     defined(__ARCH_WANT_SYSCALL_LFUTEXEXPR))
#include "futex-syscalls-impl.c.inl"
#endif /* lfutex... */
#if (defined(__ARCH_WANT_COMPAT_SYSCALL_LFUTEX) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_LFUTEXEXPR))
#define DEFINE_COMPAT_FUTEX 1
#include "futex-syscalls-impl.c.inl"
#endif /* lfutex... (compat) */
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_FUTEX_SYSCALLS_C */
