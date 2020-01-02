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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "futex-syscalls.c"
#define DEFINE_COMPAT_FUTEX 1
#endif /* __INTELLISENSE__ */

#ifdef DEFINE_COMPAT_FUTEX
#define FUNC(x)  compat_##x
#define FUNC2(x) COMPAT_##x
#else /* DEFINE_COMPAT_FUTEX */
#define FUNC(x)  x
#define FUNC2(x) x
#endif /* !DEFINE_COMPAT_FUTEX */

DECL_BEGIN

/* Mask for futex flags affecting timeout characteristics. */
#define FUTEX_TIMEOUT_FLAG_MASK          \
	(LFUTEX_WAIT_FLAG_TIMEOUT_SYSQTIME | \
	 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE | \
	 LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME)

/* @return: 0:          A connected signal was triggered.
 * @return: -ETIMEDOUT: The given timeout has expired. */
PRIVATE syscall_slong_t KCALL
FUNC(task_waitfor_futex)(syscall_ulong_t flags,
                         USER UNCHECKED struct FUNC(timespec64) const *timeout) {
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
	COMPILER_READ_BARRIER();
#ifdef DEFINE_COMPAT_FUTEX
	{
		struct timespec tm;
		tm.tv_sec  = timeout->tv_sec;
		tm.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		tmo = timespec_to_qtime(&tm);
	}
#else /* DEFINE_COMPAT_FUTEX */
	tmo = timespec_to_qtime(timeout);
#endif /* !DEFINE_COMPAT_FUTEX */
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






/************************************************************************/
/* lfutex()                                                             */
/************************************************************************/
#if (defined(DEFINE_COMPAT_FUTEX) ? defined(__ARCH_WANT_COMPAT_SYSCALL_LFUTEX) \
                                  : defined(__ARCH_WANT_SYSCALL_LFUTEX))
#ifdef DEFINE_COMPAT_FUTEX
DEFINE_COMPAT_SYSCALL5(syscall_slong_t, lfutex,
                       USER UNCHECKED compat_uintptr_t *, uaddr,
                       syscall_ulong_t, futex_op,
                       compat_uintptr_t, val,
                       USER UNCHECKED struct compat_timespec64 const *, timeout,
                       compat_uintptr_t, val2)
#else /* DEFINE_COMPAT_FUTEX */
DEFINE_SYSCALL5(syscall_slong_t, lfutex,
                USER UNCHECKED uintptr_t *, uaddr,
                syscall_ulong_t, futex_op,
                uintptr_t, val,
                USER UNCHECKED struct timespec64 const *, timeout,
                uintptr_t, val2)
#endif /* !DEFINE_COMPAT_FUTEX */
{
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
		f = vm_getfutex_existing(THIS_VM, uaddr);
		result = 0;
		if (f) {
			if (count == (size_t)-1) {
				result = sig_broadcast(&f->f_signal);
			} else {
				/* Only signal at most `count' connected threads.
				 * TODO: Make sure that when a already received signal connection is discarded
				 *      (such as is the case when `task_popconnections()' appears in an except-
				 *       path), the already delivered signal gets broadcast, thus ensuring that
				 *       sending a signal to a single thread (like we do here), don't end up
				 *       being ignored because the thread that was chosen ended up terminating!
				 */
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

	case LFUTEX_WAKEMASK: {
		size_t count = (size_t)val;
		FUNC(lfutex_t) mask_and = (FUNC(lfutex_t))(uintptr_t)timeout;
		FUNC(lfutex_t) mask_or  = (FUNC(lfutex_t))val2;
#ifdef __OPTIMIZE_SIZE__
#define APPLY_MASK()                                            \
		do {                                                    \
			FUNC(lfutex_t) _oldval;                             \
			COMPILER_WRITE_BARRIER();                           \
			do {                                                \
				_oldval = ATOMIC_READ(*uaddr);                  \
			} while (!ATOMIC_CMPXCH_WEAK(*uaddr, _oldval,       \
			                             (_oldval & mask_and) | \
			                             mask_or));             \
			COMPILER_WRITE_BARRIER();                           \
		} __WHILE0
#else /* __OPTIMIZE_SIZE__ */
#define APPLY_MASK()                                                \
		do {                                                        \
			COMPILER_WRITE_BARRIER();                               \
			if likely(!mask_or) {                                   \
				ATOMIC_FETCHAND(*uaddr, mask_and);                  \
			} else if (mask_and == (FUNC(lfutex_t))-1) {            \
				ATOMIC_FETCHOR(*uaddr, mask_or);                    \
			} else {                                                \
				FUNC(lfutex_t) _oldval;                             \
				do {                                                \
					_oldval = ATOMIC_READ(*uaddr);                  \
				} while (!ATOMIC_CMPXCH_WEAK(*uaddr, _oldval,       \
				                             (_oldval & mask_and) | \
				                             mask_or));             \
			}                                                       \
			COMPILER_WRITE_BARRIER();                               \
		} __WHILE0
#endif /* !__OPTIMIZE_SIZE__ */
		if unlikely((futex_op & LFUTEX_FLAGMASK) != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
			      futex_op,
			      LFUTEX_FLAGMASK,
			      futex_op & LFUTEX_FLAGMASK);
		}
		validate_user(uaddr, 1);
		f = vm_getfutex_existing(THIS_VM, uaddr);
		result = 0;
		if (!f) {
			APPLY_MASK();
			/* Do a second check for the futex, thus ensuring
			 * that we're interlocked with `APPLY_MASK()' */
			f = vm_getfutex_existing(THIS_VM, uaddr);
			if unlikely(f) {
				result = sig_broadcast(&f->f_signal);
				decref_unlikely(f);
				if ((size_t)result > count)
					result = (syscall_slong_t)count;
			}
		} else {
			FINALLY_DECREF_UNLIKELY(f);
			if (count == (size_t)-1) {
				/* Since we're doing a broadcast, no need to wait
				 * with the signal application until later! */
				APPLY_MASK();
				result = sig_broadcast(&f->f_signal);
			} else {
				/* Only signal at most `count' connected threads.
				 * TODO: Make sure that when a already received signal connection is discarded
				 *      (such as is the case when `task_popconnections()' appears in an except-
				 *       path), the already delivered signal gets broadcast, thus ensuring that
				 *       sending a signal to a single thread (like we do here), don't end up
				 *       being ignored because the thread that was chosen ended up terminating!
				 */
				while (count) {
					if (!sig_send(&f->f_signal)) {
						size_t temp;
						APPLY_MASK();
						/* Broadcast again after modifying the memory location. */
						temp = sig_broadcast(&f->f_signal);
						if unlikely(temp > count)
							temp = count;
						result += temp;
						break;
					}
					++result;
					--count;
				}
			}
		}
#undef APPLY_MASK
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
		f = vm_getfutex(THIS_VM, uaddr);
		FINALLY_DECREF(f);
		task_connect(&f->f_signal);
		/* NOTE: The futex `f' must be kept alive during the wait,
		 *       since even though semantics would allow it to be
		 *       destroyed before being waited upon, doing so in
		 *       practice would immediately trigger its signal, and
		 *       any sender thread to not broadcast to the same futex,
		 *       meaning that we wouldn't sleep at all, but instead
		 *       instantly wake up once again! */
		result = FUNC(task_waitfor_futex)(futex_op, timeout);
	}	break;

	case LFUTEX_WAIT_LOCK: {
		FUNC(lfutex_t) oldval, newval;
		validate_writable(uaddr, sizeof(*uaddr));
		for (;;) {
			oldval = ATOMIC_READ(*uaddr);
			if ((oldval & FUNC2(LFUTEX_WAIT_LOCK_TIDMASK)) == 0) {
				if (!val)
					val = task_gettid();
				/* Lock is available. */
				newval = (oldval & ~FUNC2(LFUTEX_WAIT_LOCK_TIDMASK)) | val;
				if (!ATOMIC_CMPXCH_WEAK(*uaddr, oldval, newval))
					continue;
				return 1;
			}
			/* Lock isn't available (connect to it, then set the
			 * is-waiting bit and sleep until it becomes available) */
			newval = oldval | FUNC2(LFUTEX_WAIT_LOCK_WAITERS);
			{
				f = vm_getfutex(THIS_VM, uaddr);
				FINALLY_DECREF(f);
				task_connect(&f->f_signal);
				if (!ATOMIC_CMPXCH_WEAK(*uaddr, oldval, newval)) {
					/* Failed to set the locked bit (try again) */
					task_disconnectall();
					continue;
				}
				/* Wait for the futex and return the resulting status code. */
				result = FUNC(task_waitfor_futex)(futex_op, timeout);
				break;
			}
		}
	}	break;

#define DEFINE_WAIT_WHILE_OPERATOR(id, validate, should_wait)      \
	case id: {                                                     \
		validate(uaddr, sizeof(*uaddr));                           \
		/* Connect to the futex first, thus performing the         \
		 * should-wait checked in a manner that is interlocked. */ \
		f = vm_getfutex(THIS_VM, uaddr);                           \
		FINALLY_DECREF(f);                                         \
		task_connect(&f->f_signal);                                \
		/* Read the futex value. */                                \
		if (should_wait) {                                         \
			/* Yes, we should wait. */                             \
			result = FUNC(task_waitfor_futex)(futex_op, timeout);  \
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
#endif /* __ARCH_WANT_SYSCALL_LFUTEX */





/************************************************************************/
/* lfutexexpr()                                                         */
/************************************************************************/
#if (defined(DEFINE_COMPAT_FUTEX) ? defined(__ARCH_WANT_COMPAT_SYSCALL_LFUTEXEXPR) \
                                  : defined(__ARCH_WANT_SYSCALL_LFUTEXEXPR))
#ifdef DEFINE_COMPAT_FUTEX
DEFINE_COMPAT_SYSCALL5(errno_t, lfutexexpr,
                       USER UNCHECKED void *, base,
                       size_t, exprc,
                       USER UNCHECKED struct compat_lfutexexpr const *, exprv,
                       USER UNCHECKED struct compat_timespec64 const *, timeout,
                       syscall_ulong_t, timeout_flags)
#else /* DEFINE_COMPAT_FUTEX */
DEFINE_SYSCALL5(errno_t, lfutexexpr,
                USER UNCHECKED void *, base,
                size_t, exprc,
                USER UNCHECKED struct lfutexexpr const *, exprv,
                USER UNCHECKED struct timespec64 const *, timeout,
                syscall_ulong_t, timeout_flags)
#endif /* !DEFINE_COMPAT_FUTEX */
{
	(void)base;
	(void)exprc;
	(void)exprv;
	(void)timeout;
	(void)timeout_flags;
	THROW(E_NOT_IMPLEMENTED_TODO);
}
#endif /* __ARCH_WANT_SYSCALL_LFUTEXEXPR */





/************************************************************************/
/* lfutexlockexpr()                                                     */
/************************************************************************/
#if (defined(DEFINE_COMPAT_FUTEX) ? defined(__ARCH_WANT_COMPAT_SYSCALL_LFUTEXLOCKEXPR) \
                                  : defined(__ARCH_WANT_SYSCALL_LFUTEXLOCKEXPR))
#ifdef DEFINE_COMPAT_FUTEX
DEFINE_COMPAT_SYSCALL6(errno_t, lfutexlockexpr,
                       USER UNCHECKED compat_uintptr_t *, ulockaddr,
                       USER UNCHECKED void *, base,
                       size_t, exprc,
                       USER UNCHECKED struct compat_lfutexexpr const *, exprv,
                       USER UNCHECKED struct compat_timespec64 const *, timeout,
                       syscall_ulong_t, timeout_flags)
#else /* DEFINE_COMPAT_FUTEX */
DEFINE_SYSCALL6(errno_t, lfutexlockexpr,
                USER UNCHECKED uintptr_t *, ulockaddr,
                USER UNCHECKED void *, base,
                size_t, exprc,
                USER UNCHECKED struct lfutexexpr const *, exprv,
                USER UNCHECKED struct timespec64 const *, timeout,
                syscall_ulong_t, timeout_flags)
#endif /* !DEFINE_COMPAT_FUTEX */
{
	(void)ulockaddr;
	(void)base;
	(void)exprc;
	(void)exprv;
	(void)timeout;
	(void)timeout_flags;
	THROW(E_NOT_IMPLEMENTED_TODO);
}
#endif /* __ARCH_WANT_SYSCALL_LFUTEXLOCKEXPR */


DECL_END

#undef FUNC2
#undef FUNC
#undef DEFINE_COMPAT_FUTEX
