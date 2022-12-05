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
#ifdef __INTELLISENSE__
#include "futex-syscalls.c"
//#define DEFINE_COMPAT_FUTEX 1
#endif /* __INTELLISENSE__ */

#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/mman/futexfd.h>
#include <sched/rpc.h>
#include <sched/tsc.h>

#include <string.h>

#ifdef DEFINE_COMPAT_FUTEX
#define LOCAL_uintptr_t              compat_uintptr_t
#define LOCAL_lfutex_t               compat_lfutex_t
#define LOCAL_struct_lfutexexpr      struct compat_lfutexexpr
#define LOCAL_struct_timespec64      struct compat_timespec64
#define LOCAL_mfutexfd_new           compat_mfutexfd_new
#define LOCAL_task_waitfor_futex     compat_task_waitfor_futex
#define LOCAL_sys_lfutex_makefd_impl compat_sys_lfutex_makefd_impl
#define LOCAL_validate_readable      compat_validate_readable
#define LOCAL_validate_readwrite     compat_validate_readwrite
#define LOCAL_validate_user          compat_validate_user
#else /* DEFINE_COMPAT_FUTEX */
#define LOCAL_uintptr_t              uintptr_t
#define LOCAL_lfutex_t               lfutex_t
#define LOCAL_struct_lfutexexpr      struct lfutexexpr
#define LOCAL_struct_timespec64      struct timespec64
#define LOCAL_mfutexfd_new           mfutexfd_new
#define LOCAL_task_waitfor_futex     task_waitfor_futex
#define LOCAL_sys_lfutex_makefd_impl sys_lfutex_makefd_impl
#define LOCAL_validate_readable      validate_readable
#define LOCAL_validate_readwrite     validate_readwrite
#define LOCAL_validate_user          validate_user
#endif /* !DEFINE_COMPAT_FUTEX */

DECL_BEGIN

/* Mask for futex flags affecting timeout characteristics. */
#define FUTEX_TIMEOUT_FLAG_MASK          \
	(LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE | \
	 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE | \
	 LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME | \
	 LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL)

/* @return: 0:          A connected signal was triggered.
 * @return: -ETIMEDOUT: The given timeout has expired. */
PRIVATE syscall_slong_t KCALL
LOCAL_task_waitfor_futex(syscall_ulong_t flags,
                         USER UNCHECKED LOCAL_struct_timespec64 const *timeout) {
	ktime_t tmo;

	/* Mask flag bits. */
	flags &= LFUTEX_FLAGMASK;

	/* Validate that only known flags are being used. */
	VALIDATE_FLAGSET(flags,
	                 FUTEX_TIMEOUT_FLAG_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP);
	if (!timeout) {
		/* Simple case: Without any timeout.
		 * In this case, still validate that `flags' aren't malformed. */
		if unlikely((flags & (FUTEX_TIMEOUT_FLAG_MASK & ~LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL)) != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
			      flags,
			      FUTEX_TIMEOUT_FLAG_MASK,
			      flags & FUTEX_TIMEOUT_FLAG_MASK);
		}
		task_waitfor();
		return 0;
	}
	LOCAL_validate_readable(timeout, sizeof(*timeout));
	COMPILER_READ_BARRIER();
	if (flags & LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME) {
		/* XXX: How should we implement this? */
	}
	/* Accept both relative-, and absolute timeouts. */
	if (flags & LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE) {
		tmo = ktime() + relktime_from_user_rel(timeout);
	} else {
		tmo = ktime_from_user(timeout);
	}
	if (!task_waitfor(tmo))
		return -ETIMEDOUT;
	return 0;
}

PRIVATE ATTR_NOINLINE syscall_slong_t KCALL
LOCAL_sys_lfutex_makefd_impl(USER UNCHECKED LOCAL_lfutex_t *uaddr,
                             syscall_ulong_t futex_op, LOCAL_lfutex_t val,
                             USER UNCHECKED LOCAL_struct_timespec64 const *timeout,
                             LOCAL_lfutex_t val2) {
	fd_t resfd;
	struct handle_install_data install;
	REF struct mfutexfd *mfd;
	LOCAL_struct_lfutexexpr expr[2];
	REF struct mfutex *ftx;
	if unlikely(timeout != NULL) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_FD_WITH_TIMEOUT);
	}

	/* Construct a futex at the given address. */
	LOCAL_validate_user(uaddr, sizeof(*uaddr));
	ftx = mman_createfutex(THIS_MMAN, uaddr);
	FINALLY_DECREF(ftx);

	/* Setup a futex expression descriptor for the single caller-given expression. */
	expr[0].fe_condition = futex_op & ~LFUTEX_FDBIT;
	expr[0].fe_offset    = 0;
	expr[0].fe_val       = val;
	expr[0].fe_val2      = val2;
	expr[1].fe_condition = LFUTEX_EXPREND;

	/* Create a new futex-fd object and install it as a handle. */
	resfd = handles_install_begin(&install);
	TRY {
		mfd = LOCAL_mfutexfd_new(ftx, uaddr, expr);
	} EXCEPT {
		handles_install_rollback(&install);
		RETHROW();
	}
	handles_install_commit_inherit(&install, mfd, IO_RDWR);
	return resfd;
}






/************************************************************************/
/* lfutex()                                                             */
/************************************************************************/
#if (defined(DEFINE_COMPAT_FUTEX) ? defined(__ARCH_WANT_COMPAT_SYSCALL_LFUTEX) \
                                  : defined(__ARCH_WANT_SYSCALL_LFUTEX))
#ifdef DEFINE_COMPAT_FUTEX
DEFINE_COMPAT_SYSCALL5(syscall_slong_t, lfutex,
                       USER UNCHECKED LOCAL_lfutex_t *, uaddr,
                       syscall_ulong_t, futex_op,
                       LOCAL_lfutex_t, val,
                       USER UNCHECKED LOCAL_struct_timespec64 const *, timeout,
                       LOCAL_lfutex_t, val2)
#else /* DEFINE_COMPAT_FUTEX */
DEFINE_SYSCALL5(syscall_slong_t, lfutex,
                USER UNCHECKED LOCAL_lfutex_t *, uaddr,
                syscall_ulong_t, futex_op,
                LOCAL_lfutex_t, val,
                USER UNCHECKED LOCAL_struct_timespec64 const *, timeout,
                LOCAL_lfutex_t, val2)
#endif /* !DEFINE_COMPAT_FUTEX */
{
	syscall_slong_t result;
	REF struct mfutex *f;
	assert(!task_wasconnected());
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
		LOCAL_validate_user(uaddr, 1);
		f = mman_lookupfutex(THIS_MMAN, uaddr);
		result = 0;
		if (f) {
			if (count == (size_t)-1) {
				result = mfutex_broadcast(f);
			} else {
				result = mfutex_sendmany(f, count);
			}
			decref_unlikely(f);
		}
	}	break;

	case LFUTEX_WAKEMASK: {
		size_t count = (size_t)val;
		LOCAL_lfutex_t mask_and = (LOCAL_lfutex_t)(LOCAL_uintptr_t)(uintptr_t)timeout;
		LOCAL_lfutex_t mask_or  = (LOCAL_lfutex_t)val2;
#ifdef __OPTIMIZE_SIZE__
#define APPLY_MASK()                                            \
		do {                                                    \
			LOCAL_lfutex_t _oldval;                             \
			COMPILER_WRITE_BARRIER();                           \
			do {                                                \
				_oldval = ATOMIC_READ(*uaddr);                  \
			} while (!ATOMIC_CMPXCH_WEAK(*uaddr, _oldval,       \
			                             (_oldval & mask_and) | \
			                             mask_or));             \
			COMPILER_WRITE_BARRIER();                           \
		}	__WHILE0
#else /* __OPTIMIZE_SIZE__ */
#define APPLY_MASK()                                                \
		do {                                                        \
			COMPILER_WRITE_BARRIER();                               \
			if likely(!mask_or) {                                   \
				ATOMIC_AND(*uaddr, mask_and);                       \
			} else if (mask_and == (LOCAL_lfutex_t)-1) {            \
				ATOMIC_OR(*uaddr, mask_or);                         \
			} else {                                                \
				LOCAL_lfutex_t _oldval;                             \
				do {                                                \
					_oldval = ATOMIC_READ(*uaddr);                  \
				} while (!ATOMIC_CMPXCH_WEAK(*uaddr, _oldval,       \
				                             (_oldval & mask_and) | \
				                             mask_or));             \
			}                                                       \
			COMPILER_WRITE_BARRIER();                               \
		}	__WHILE0
#endif /* !__OPTIMIZE_SIZE__ */
		if unlikely((futex_op & LFUTEX_FLAGMASK) != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
			      futex_op,
			      LFUTEX_FLAGMASK,
			      futex_op & LFUTEX_FLAGMASK);
		}
		LOCAL_validate_readwrite(uaddr, 1);
		f = mman_lookupfutex(THIS_MMAN, uaddr);
		result = 0;
		if (!f) {
			APPLY_MASK();
			/* Do a second check for the futex, thus ensuring
			 * that  we're  interlocked  with  `APPLY_MASK()' */
			f = mman_lookupfutex(THIS_MMAN, uaddr);
			if unlikely(f) {
				result = mfutex_broadcast(f);
				decref_unlikely(f);
				if ((size_t)result > count)
					result = (syscall_slong_t)count;
			}
		} else {
			FINALLY_DECREF_UNLIKELY(f);
			if (count == (size_t)-1) {
				/* Since we're doing a broadcast, no need to wait
				 * with  the  signal  application  until   later! */
				APPLY_MASK();
				result = mfutex_broadcast(f);
			} else {
				/* Only signal at most `count' connected threads. */
				while (count) {
					if (!mfutex_send(f)) {
						size_t temp;
						APPLY_MASK();
						/* Broadcast again after modifying the memory location. */
						temp = mfutex_broadcast(f);
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

#define DEFINE_WAIT_WHILE_OPERATOR(id, should_wait, ...)              \
	case id: {                                                        \
		LOCAL_validate_readable(uaddr, sizeof(*uaddr));               \
		__VA_ARGS__;                                                  \
		/* Connect  to  the  futex first,  thus  performing the       \
		 * should-wait checked in a manner that is interlocked. */    \
		f = mman_createfutex(THIS_MMAN, uaddr);                       \
		FINALLY_DECREF(f);                                            \
		if (futex_op & LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL) {            \
			mfutex_connect_for_poll(f);                               \
		} else {                                                      \
			mfutex_connect(f);                                        \
		}                                                             \
		/* Read the futex value. */                                   \
		TRY {                                                         \
			if (should_wait) {                                        \
				/* Yes, we should wait. */                            \
				result = LOCAL_task_waitfor_futex(futex_op, timeout); \
				break;                                                \
			}                                                         \
		} EXCEPT {                                                    \
			task_disconnectall();                                     \
			RETHROW();                                                \
		}                                                             \
		/* No, we shouldn't wait. */                                  \
		task_disconnectall();                                         \
		result = 1;                                                   \
	}	break
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE, ATOMIC_READ(*uaddr) == val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_UNTIL, ATOMIC_READ(*uaddr) != val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_ABOVE, ATOMIC_READ(*uaddr) > val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_BELOW, ATOMIC_READ(*uaddr) < val);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_BITMASK, (ATOMIC_READ(*uaddr) & val) == val2);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_UNTIL_BITMASK, (ATOMIC_READ(*uaddr) & val) != val2);
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_EX, bcmp(uaddr, (USER CHECKED void const *)(uintptr_t)val, val2) == 0, LOCAL_validate_readable((USER UNCHECKED void const *)(uintptr_t)val, val2));
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_UNTIL_EX, bcmp(uaddr, (USER CHECKED void const *)(uintptr_t)val, val2) != 0, LOCAL_validate_readable((USER UNCHECKED void const *)(uintptr_t)val, val2));
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_ABOVE_EX, memcmp(uaddr, (USER CHECKED void const *)(uintptr_t)val, val2) > 0, LOCAL_validate_readable((USER UNCHECKED void const *)(uintptr_t)val, val2));
	DEFINE_WAIT_WHILE_OPERATOR(LFUTEX_WAIT_WHILE_BELOW_EX, memcmp(uaddr, (USER CHECKED void const *)(uintptr_t)val, val2) < 0, LOCAL_validate_readable((USER UNCHECKED void const *)(uintptr_t)val, val2));
#undef DEFINE_WAIT_WHILE_OPERATOR

	default:
		/* Futex FD support (single-expression; s.a. `lfutexexpr(2)') */
		if (futex_op & LFUTEX_FDBIT)
			return LOCAL_sys_lfutex_makefd_impl(uaddr, futex_op, val, timeout, val2);
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
		      futex_op);
		break;
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
                       USER UNCHECKED LOCAL_lfutex_t *, ulockaddr,
                       USER UNCHECKED void *, base,
                       USER UNCHECKED LOCAL_struct_lfutexexpr const *, expr,
                       USER UNCHECKED LOCAL_struct_timespec64 const *, timeout,
                       syscall_ulong_t, flags)
#else /* DEFINE_COMPAT_FUTEX */
DEFINE_SYSCALL5(errno_t, lfutexexpr,
                USER UNCHECKED LOCAL_lfutex_t *, ulockaddr,
                USER UNCHECKED void *, base,
                USER UNCHECKED LOCAL_struct_lfutexexpr const *, expr,
                USER UNCHECKED LOCAL_struct_timespec64 const *, timeout,
                syscall_ulong_t, flags)
#endif /* !DEFINE_COMPAT_FUTEX */
{
	errno_t result;
	REF struct mfutex *f;
	validate_user(ulockaddr, sizeof(*ulockaddr));
	validate_readable(expr, sizeof(*expr));
	f = mman_createfutex(THIS_MMAN, ulockaddr);
	FINALLY_DECREF(f);

	/* Connect to the named futex. */
	if (flags & (LFUTEX_FDBIT | LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL)) {
		if (flags & LFUTEX_FDBIT) {
			fd_t resfd;
			struct handle_install_data install;
			REF struct mfutexfd *mfd;
			if unlikely(timeout != NULL) {
				THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
				      E_INVALID_ARGUMENT_CONTEXT_LFUTEXEXPR_FD_WITH_TIMEOUT);
			}
			VALIDATE_FLAGSET(flags, LFUTEX_FDBIT,
			                 E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP);

			/* Create a new futex-fd object. */
			resfd = handles_install_begin(&install);
			TRY {
				mfd = LOCAL_mfutexfd_new(f, base, expr);
			} EXCEPT {
				handles_install_rollback(&install);
				RETHROW();
			}
			handles_install_commit_inherit(&install, mfd, IO_RDWR);
			return resfd;
		}
		mfutex_connect_for_poll(f);
	} else {
		mfutex_connect(f);
	}

	/* Evaluate expressions. */
	TRY {
		LOCAL_struct_lfutexexpr const *iter = expr;
		for (;; ++iter) {
			errno_t expr_result;
			syscall_ulong_t cond;
			USER CHECKED LOCAL_uintptr_t *uaddr;
			cond  = ATOMIC_READ(iter->fe_condition);
			uaddr = (USER UNCHECKED LOCAL_uintptr_t *)((USER UNCHECKED byte_t *)base +
			                                           ATOMIC_READ(iter->fe_offset));
			/* !!! Don't use LOCAL_validate_readable here -- (base+fe_offset might produce large pointers) */
			validate_readable(uaddr, sizeof(*uaddr));
			switch (cond) {

			case LFUTEX_EXPREND:
				if unlikely(iter == expr)
					goto bad_opcode; /* Not allowed as the first expression! */
				goto must_wait;

			case LFUTEX_NOP:
				expr_result = 0; /* no-op */
				break;

#define DEFINE_CASE(id, should_wait)          \
			case id:                          \
				expr_result = !(should_wait); \
				break
			DEFINE_CASE(LFUTEX_WAIT_WHILE, /* >> if (*uaddr == val) return waitfor(uaddr); return 1; */
			            ATOMIC_READ(*uaddr) == iter->fe_val);
			DEFINE_CASE(LFUTEX_WAIT_UNTIL, /* >> if (*uaddr != val) return waitfor(uaddr); return 1; */
			            ATOMIC_READ(*uaddr) != iter->fe_val);
			DEFINE_CASE(LFUTEX_WAIT_WHILE_ABOVE, /* >> if ((unsigned)*uaddr > val) return waitfor(uaddr); return 1; */
			            ATOMIC_READ(*uaddr) > iter->fe_val);
			DEFINE_CASE(LFUTEX_WAIT_WHILE_BELOW, /* >> if ((unsigned)*uaddr < val) return waitfor(uaddr); return 1; */
			            ATOMIC_READ(*uaddr) < iter->fe_val);
			DEFINE_CASE(LFUTEX_WAIT_WHILE_BITMASK, /* >> if ((*uaddr & val) == val2) return waitfor(uaddr); return 1; */
			            (ATOMIC_READ(*uaddr) & iter->fe_val) == iter->fe_val2);
			DEFINE_CASE(LFUTEX_WAIT_UNTIL_BITMASK, /* >> if ((*uaddr & val) != val2) return waitfor(uaddr); return 1; */
			            (ATOMIC_READ(*uaddr) & iter->fe_val) != iter->fe_val2);
#undef DEFINE_CASE

			case LFUTEX_WAIT_WHILE_EX:
			case LFUTEX_WAIT_UNTIL_EX:
			case LFUTEX_WAIT_WHILE_ABOVE_EX:
			case LFUTEX_WAIT_WHILE_BELOW_EX: {
				/* Compare variable-sized memory blobs. */
				size_t num_bytes = iter->fe_val2;
				USER CHECKED void const *rhs;
				int cmp;
				rhs = (USER UNCHECKED byte_t *)base + iter->fe_val;
				COMPILER_READ_BARRIER();
				/* !!! Don't use LOCAL_validate_readable here -- (base+fe_val might produce large pointers) */
				rhs = validate_readable(rhs, num_bytes);
				cmp = memcmp(uaddr, rhs, num_bytes);
				switch (cond) {
				case LFUTEX_WAIT_WHILE_EX:       expr_result = !(cmp == 0); break;
				case LFUTEX_WAIT_UNTIL_EX:       expr_result = !(cmp != 0); break;
				case LFUTEX_WAIT_WHILE_ABOVE_EX: expr_result = !(cmp >  0); break;
				case LFUTEX_WAIT_WHILE_BELOW_EX: expr_result = !(cmp <  0); break;
				default: __builtin_unreachable();
				}
			}	break;

			default:
bad_opcode:
				THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
				      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
				      cond);
				break;
			}
			if (expr_result != 0) {
				result = expr_result;
				task_disconnectall();
				goto done;
			}

			/* This right here prevents threads being unkillable
			 * whenever  they're  executing  futex  expressions. */
			task_serve();
		}
	} EXCEPT {
		task_disconnectall();
		RETHROW();
	}
must_wait:
	/* Do the wait */
	result = LOCAL_task_waitfor_futex(flags, timeout);
done:
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_LFUTEXEXPR */


DECL_END

#undef LOCAL_uintptr_t
#undef LOCAL_lfutex_t
#undef LOCAL_struct_lfutexexpr
#undef LOCAL_struct_timespec64
#undef LOCAL_mfutexfd_new
#undef LOCAL_task_waitfor_futex
#undef LOCAL_sys_lfutex_makefd_impl
#undef LOCAL_validate_readable
#undef LOCAL_validate_readwrite
#undef LOCAL_validate_user
#undef DEFINE_COMPAT_FUTEX
