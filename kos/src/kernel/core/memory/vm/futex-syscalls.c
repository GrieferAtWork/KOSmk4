/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_SYSCALLS_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/panic.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>
#include <sched/cpu.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <bits/timespec.h>
#include <kos/except-inval.h>
#include <kos/futex.h>
#include <kos/futexexpr.h>
#include <kos/futexlock.h>
#include <linux/futex.h>

#include <assert.h>
#include <errno.h>

#include "vm-nodeapi.h"

DECL_BEGIN


/* Futex system call used for linux compatibility.
 * When targeting KOS specifically, you are advised to make use of lfutex() instead */
DEFINE_SYSCALL6(syscall_slong_t, futex,
                USER UNCHECKED uint32_t *, uaddr,
                syscall_ulong_t, futex_op,
                uint32_t, val,
                USER UNCHECKED struct timespec32 const *, timeout_or_val2,
                USER UNCHECKED uint32_t *, uaddr2,
                uint32_t, val3) {
	kernel_panic("TODO");
}

/* Mask for futex flags affecting timeout characteristics. */
#define FUTEX_TIMEOUT_FLAG_MASK          \
	(LFUTEX_WAIT_FLAG_TIMEOUT_SYSQTIME | \
	 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE | \
	 LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME)

/* @return: 0:          A connected signal was triggered.
 * @return: -ETIMEDOUT: The given timeout has expired. */
PRIVATE syscall_slong_t KCALL
task_waitfor_futex(syscall_ulong_t flags,
                   USER UNCHECKED struct timespec const *timeout) {
	qtime_t tmo;
	/* Mask flag bits. */
	flags &= LFUTEX_FLAGMASK;
	/* Validate that only known flags are being used. */
	VALIDATE_FLAGSET(flags,
	                 FUTEX_TIMEOUT_FLAG_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP);
	if (!timeout) {
		/* Simple case: Without any timeout.
		 * In this case, still validate that `flags' aren't malformed. */
		if unlikely((flags & FUTEX_TIMEOUT_FLAG_MASK) != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
			      flags,
			      FUTEX_TIMEOUT_FLAG_MASK,
			      flags & FUTEX_TIMEOUT_FLAG_MASK);
		}
		task_waitfor();
		return 0;
	}
	validate_readable(timeout, sizeof(*timeout));
	tmo = timespec_to_qtime(timeout);
	if (flags & LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME) {
		/* TODO: tmo = qtime_realtime_to_cpu(tmo); */
	}
	/* Allow for relative timeouts by adding the
	 * current quantum time to the given timeout. */
	if (flags & LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE)
		tmo += quantum_time();
	if (!task_waitfor(&tmo))
		return -ETIMEDOUT;
	return 0;
}


DEFINE_SYSCALL5(syscall_slong_t, lfutex,
                USER UNCHECKED uintptr_t *, uaddr,
                syscall_ulong_t, futex_op,
                uintptr_t, val,
                USER UNCHECKED struct timespec64 const *, timeout,
                uintptr_t, val2) {
	syscall_slong_t result;
	REF struct vm_futex *f;
	assert(!task_isconnected());
	switch (futex_op & LFUTEX_CMDMASK) {

	case LFUTEX_WAKE: {
		size_t count = (size_t)val;
		if unlikely((futex_op & LFUTEX_FLAGMASK) != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
			      futex_op,
			      LFUTEX_FLAGMASK,
			      futex_op & LFUTEX_FLAGMASK);
		}
		validate_user(uaddr, 1);
		f = vm_getfutex_existing(THIS_VM, (vm_virt_t)uaddr);
		result = 0;
		if (f) {
			if (count == (size_t)-1) {
				result = sig_broadcast(&f->f_signal);
			} else {
				/* Only signal at most `count' connected threads. */
				while (count) {
					if (!sig_send(&f->f_signal))
						break;
					++result;
					--count;
				}
			}
			decref_unlikely(f);
		}
	}	break;

	case LFUTEX_NOP:
		/* NOTE: Intentionally don't validate `futex_op & LFUTEX_FLAGMASK',
		 *       since this command's purpose is to literally do nothing,
		 *       meaning that also doing nothing for unknown flags is the
		 *       correct thing to do in terms of forward-compatibility. */
		result = 0;
		break;

	case LFUTEX_WAIT: {
		validate_user(uaddr, 1);
		f = vm_getfutex(THIS_VM, (vm_virt_t)uaddr);
		FINALLY_DECREF(f);
		task_connect(&f->f_signal);
		/* NOTE: The futex `f' must be kept alive during the wait,
		 *       since even though semantics would allow it to be
		 *       destroyed before being waited upon, doing so in
		 *       practice would immediately trigger its signal, and
		 *       any sender thread to not broadcast to the same futex,
		 *       meaning that we wouldn't sleep at all, but instead
		 *       instantly wake up once again! */
		result = task_waitfor_futex(futex_op, timeout);
	}	break;

	case LFUTEX_WAIT_LOCK: {
		lfutex_t oldval, newval;
		validate_writable(uaddr, sizeof(*uaddr));
		for (;;) {
			oldval = ATOMIC_READ(*uaddr);
			if ((oldval & LFUTEX_WAIT_LOCK_TIDMASK) == 0) {
				if (!val)
					val = task_gettid();
				/* Lock is available. */
				newval = (oldval & ~LFUTEX_WAIT_LOCK_TIDMASK) | val;
				if (!ATOMIC_CMPXCH_WEAK(*uaddr, oldval, newval))
					continue;
				return 1;
			}
			/* Lock isn't available (connect to it, then set the
			 * is-waiting bit and sleep until it becomes available) */
			newval = oldval | LFUTEX_WAIT_LOCK_WAITERS;
			{
				f = vm_getfutex(THIS_VM, (vm_virt_t)uaddr);
				FINALLY_DECREF(f);
				task_connect(&f->f_signal);
				if (!ATOMIC_CMPXCH_WEAK(*uaddr, oldval, newval)) {
					/* Failed to set the locked bit (try again) */
					task_disconnectall();
					continue;
				}
				/* Wait for the futex and return the resulting status code. */
				result = task_waitfor_futex(futex_op, timeout);
				break;
			}
		}
	}	break;

#define DEFINE_WAIT_WHILE_OPERATOR(id, validate, should_wait)      \
	case id: {                                                     \
		validate(uaddr, sizeof(*uaddr));                           \
		/* Connect to the futex first, thus performing the         \
		 * should-wait checked in a manner that is interlocked. */ \
		f = vm_getfutex(THIS_VM, (vm_virt_t)uaddr);                \
		FINALLY_DECREF(f);                                         \
		task_connect(&f->f_signal);                                \
		/* Read the futex value. */                                \
		if (should_wait) {                                         \
			/* Yes, we should wait. */                             \
			result = task_waitfor_futex(futex_op, timeout);        \
			break;                                                 \
		}                                                          \
		/* No, we shouldn't wait. */                               \
		task_disconnectall();                                      \
		result = 1;                                                \
	}	break
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE, validate_readable, ATOMIC_READ(*uaddr) == val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_UNTIL, validate_readable, ATOMIC_READ(*uaddr) != val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_ABOVE, validate_readable, ATOMIC_READ(*uaddr) > val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_BELOW, validate_readable, ATOMIC_READ(*uaddr) < val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_BITMASK, validate_readable, (ATOMIC_READ(*uaddr) & val) == val2);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_UNTIL_BITMASK, validate_readable, (ATOMIC_READ(*uaddr) & val) != val2);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_CMPXCH, validate_writable, ATOMIC_CMPXCH(*uaddr, val, val2));
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_UNTIL_CMPXCH, validate_writable, !ATOMIC_CMPXCH(*uaddr, val, val2));
#undef DEFINE_WAIT_WHILE_OPERATOR

	/* TODO: Futex FD support */
#define LFUTEX_FDWAIT               (LFUTEX_FDBIT | LFUTEX_WAIT)
#define LFUTEX_FDWAIT_LOCK          (LFUTEX_FDBIT | LFUTEX_WAIT_LOCK)
#define LFUTEX_FDWAIT_WHILE         (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE)
#define LFUTEX_FDWAIT_UNTIL         (LFUTEX_FDBIT | LFUTEX_WAIT_UNTIL)
#define LFUTEX_FDWAIT_WHILE_ABOVE   (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_ABOVE)
#define LFUTEX_FDWAIT_WHILE_BELOW   (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_BELOW)
#define LFUTEX_FDWAIT_WHILE_BITMASK (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_BITMASK)
#define LFUTEX_FDWAIT_UNTIL_BITMASK (LFUTEX_FDBIT | LFUTEX_WAIT_UNTIL_BITMASK)
#define LFUTEX_FDWAIT_WHILE_CMPXCH  (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_CMPXCH)
#define LFUTEX_FDWAIT_UNTIL_CMPXCH  (LFUTEX_FDBIT | LFUTEX_WAIT_UNTIL_CMPXCH)


	default:
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
		      futex_op);
	}
	return result;
}

DEFINE_SYSCALL5(errno_t, lfutexexpr,
                USER UNCHECKED void *, base,
                size_t, exprc,
                USER UNCHECKED struct lfutexexpr const *, exprv,
                USER UNCHECKED struct timespec64 const *, timeout,
                syscall_ulong_t, timeout_flags) {
	THROW(E_NOT_IMPLEMENTED_TODO);
}

DEFINE_SYSCALL6(errno_t, lfutexlockexpr,
                USER UNCHECKED uintptr_t *, ulockaddr,
                USER UNCHECKED void *, base,
                size_t, exprc,
                USER UNCHECKED struct lfutexexpr const *, exprv,
                USER UNCHECKED struct timespec64 const *, timeout,
                syscall_ulong_t, timeout_flags) {
	THROW(E_NOT_IMPLEMENTED_TODO);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_SYSCALLS_C */
