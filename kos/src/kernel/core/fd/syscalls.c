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
#ifndef GUARD_KERNEL_SRC_FD_SYSCALLS_C
#define GUARD_KERNEL_SRC_FD_SYSCALLS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fs/fs.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/mman.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/pid.h>
#include <sched/sigaction.h>
#include <sched/task.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <linux/close_range.h>
#include <linux/kcmp.h>

#include <atomic.h>
#include <errno.h>
#include <stddef.h>

DECL_BEGIN

/************************************************************************/
/* dup(), dup2(), dup3()                                                */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_DUP
DEFINE_SYSCALL1(fd_t, dup, fd_t, fd) {
	REF struct handle hand = handles_lookup(fd);
	hand.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
	RAII_FINALLY { decref_unlikely(hand); };
	return handles_install(hand);
}
#endif /* __ARCH_WANT_SYSCALL_DUP */


#ifdef __ARCH_WANT_SYSCALL_DUP2
DEFINE_SYSCALL2(fd_t, dup2, fd_t, oldfd, fd_t, newfd) {
	REF struct handle hand = handles_lookup(oldfd);
	hand.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
	TRY {
		newfd = handles_install_into(newfd, hand);
	} EXCEPT {
		if (was_thrown(E_INVALID_HANDLE_FILETYPE)) {
			if (PERTASK_GET(this_exception_args.e_invalid_handle.ih_fd) == (uintptr_t)-1)
				PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, (uintptr_t)(intptr_t)oldfd);
		}
		decref_unlikely(hand);
		RETHROW();
	}
	decref_unlikely(hand);
	return newfd;
}
#endif /* __ARCH_WANT_SYSCALL_DUP2 */


#ifdef __ARCH_WANT_SYSCALL_DUP3
DEFINE_SYSCALL3(fd_t, dup3, fd_t, oldfd, fd_t, newfd, oflag_t, flags) {
	struct handle hand;
	VALIDATE_FLAGSET(flags, O_CLOEXEC | O_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_DUP3_OFLAG);
	if unlikely(oldfd == newfd) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_DUP3_SAMEFD,
		      (syscall_slong_t)oldfd);
	}
	hand = handles_lookup(oldfd);
	hand.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
	hand.h_mode |= IO_HANDLE_FFROM_OPENFLAG(flags);
	RAII_FINALLY { decref_unlikely(hand); };
	return handles_install_into(newfd, hand);
}
#endif /* __ARCH_WANT_SYSCALL_DUP3 */





/************************************************************************/
/* ftruncate(), ftruncate64()                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FTRUNCATE
DEFINE_SYSCALL2(errno_t, ftruncate, fd_t, fd, syscall_ulong_t, length) {
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_TRUNC, hand.h_mode);
	handle_truncate(hand, (pos_t)length);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FTRUNCATE */

#ifdef __ARCH_WANT_SYSCALL_FTRUNCATE64
DEFINE_SYSCALL2(errno_t, ftruncate64, fd_t, fd, uint64_t, length) {
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_TRUNC, hand.h_mode);
	handle_truncate(hand, (pos_t)length);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FTRUNCATE64 */





/************************************************************************/
/* fallocate(), fallocate64()                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FALLOCATE
DEFINE_SYSCALL4(errno_t, fallocate,
                fd_t, fd, syscall_ulong_t, mode,
                syscall_ulong_t, offset,
                syscall_ulong_t, length) {
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	handle_allocate(hand, mode, (pos_t)offset, (pos_t)length);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FALLOCATE */

#ifdef __ARCH_WANT_SYSCALL_FALLOCATE64
DEFINE_SYSCALL4(errno_t, fallocate64,
                fd_t, fd, syscall_ulong_t, mode,
                uint64_t, offset, uint64_t, length) {
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	handle_allocate(hand, mode, (pos_t)offset, (pos_t)length);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FALLOCATE64 */





/************************************************************************/
/* close(), close_range()                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_CLOSE
DEFINE_SYSCALL1(errno_t, close, fd_t, fd) {
	struct handle ohand;
	decref(*handles_close(fd, &ohand));
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_CLOSE */
#ifdef __ARCH_WANT_SYSCALL_CLOSE_RANGE
DEFINE_SYSCALL3(errno_t, close_range,
                unsigned int, minfd,
                unsigned int, maxfd,
                unsigned int, flags) {
	struct handman *man = THIS_HANDMAN;
	VALIDATE_FLAGSET(flags, CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC,
	                 E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_FLAGS);
	switch (flags) {
	case CLOSE_RANGE_UNSHARE:
		if (isshared(man)) {
			REF struct handman *omn;
			man = handman_fork_and_closerange(man, minfd, maxfd);
			omn = task_sethandman_inherit(man);
			decref_unlikely(omn);
			break;
		}
		ATTR_FALLTHROUGH
	case 0:
		handman_closerange(man, minfd, maxfd);
		break;
	case CLOSE_RANGE_CLOEXEC | CLOSE_RANGE_UNSHARE:
		if (isshared(man)) {
			REF struct handman *omn;
			man = handman_fork(man);
			omn = task_sethandman_inherit(man);
			decref_unlikely(omn);
		}
		ATTR_FALLTHROUGH
	case CLOSE_RANGE_CLOEXEC:
		handman_setcloexec_range(man, minfd, maxfd);
		break;
	default: __builtin_unreachable();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOSE_RANGE */





/************************************************************************/
/* fsync(), fdatasync()                                                 */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FSYNC
DEFINE_SYSCALL1(errno_t, fsync, fd_t, fd) {
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	handle_sync(hand);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSYNC */

#ifdef __ARCH_WANT_SYSCALL_FDATASYNC
DEFINE_SYSCALL1(errno_t, fdatasync, fd_t, fd) {
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	handle_datasync(hand);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FDATASYNC */





/************************************************************************/
/* kreaddir(), kreaddirf()                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KREADDIR
DEFINE_SYSCALL4(ssize_t, kreaddir,
                fd_t, fd, NCX UNCHECKED struct dirent *, buf,
                size_t, bufsize, syscall_ulong_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 READDIR_MODEMASK | READDIR_FLAGMASK,
	                 E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE);
	validate_writable(buf, bufsize);
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if ((mode & READDIR_MODEMASK) == READDIR_MULTIPLE) {
		size_t partial, alignoff;
		result = 0;
		mode &= ~(READDIR_MODEMASK);
#if READDIR_DEFAULT != 0
		mode |= READDIR_DEFAULT;
#endif /* READDIR_DEFAULT != 0 */
		for (;;) {
			partial = handle_readdir(hand, buf, bufsize, (readdir_mode_t)mode);
			if (!partial) {
				/* Append an EOF directory entry. */
				if ((mode & READDIR_WANTEOF) && result != 0 &&
				    (bufsize >= COMPILER_OFFSETOF(struct dirent, d_name) + 1)) {
					buf->d_namlen  = 0;
					buf->d_name[0] = '\0';
					result += COMPILER_OFFSETOF(struct dirent, d_name) + 1;
				}
				break; /* End of directory. */
			}
			if (partial > bufsize) {
				/* User-space buffer has been used up.
				 * If this is the first entry that was read, return its required size. */
				if (!result)
					result = partial;
				break;
			}
			/* Move the buffer past this entry. */
			buf = (NCX struct dirent *)((byte_t *)buf + partial);
			bufsize -= partial;
			result += partial;
			/* Align the buffer by INodes (8 bytes). */
			alignoff = (uintptr_t)buf & (sizeof(ino64_t) - 1);
			if (alignoff) {
				alignoff = sizeof(ino64_t) - alignoff;
				if (bufsize < alignoff)
					break;
				buf = (NCX struct dirent *)((byte_t *)buf + alignoff);
				bufsize -= alignoff;
				result += alignoff;
			}
		}
	} else {
		if ((mode & READDIR_MODEMASK) > READDIR_MODEMAX) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE,
			      mode & READDIR_MODEMASK);
		}
		result = handle_readdir(hand, buf, bufsize, (readdir_mode_t)mode);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_KREADDIR */

#ifdef __ARCH_WANT_SYSCALL_KREADDIRF
DEFINE_SYSCALL5(ssize_t, kreaddirf,
                fd_t, fd, struct dirent *, buf,
                size_t, bufsize, syscall_ulong_t, mode,
                iomode_t, iomode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 READDIR_MODEMASK | READDIR_FLAGMASK,
	                 E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE);
	VALIDATE_FLAGSET(iomode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_KREADDIRF_IOMODE);
	validate_writable(buf, bufsize);
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if ((mode & READDIR_MODEMASK) == READDIR_MULTIPLE) {
		size_t partial, alignoff;
		result = 0;
		mode &= ~(READDIR_MODEMASK);
#if READDIR_DEFAULT != 0
		mode |= READDIR_DEFAULT;
#endif /* READDIR_DEFAULT != 0 */
		for (;;) {
			partial = handle_readdirf(hand, buf, bufsize, (readdir_mode_t)mode,
			                          (hand.h_mode & ~IO_USERF_MASK) | iomode);
			if (!partial) {
				/* Append an EOF directory entry. */
				if ((mode & READDIR_WANTEOF) && result != 0 &&
				    (bufsize >= COMPILER_OFFSETOF(struct dirent, d_name) + 1)) {
					buf->d_namlen  = 0;
					buf->d_name[0] = '\0';
					result += COMPILER_OFFSETOF(struct dirent, d_name) + 1;
				}
				break; /* End of directory. */
			}
			if (partial > bufsize) {
				/* User-space buffer has been used up.
				 * If this is the first entry that was read, return its required size. */
				if (!result)
					result = partial;
				break;
			}
			/* Move the buffer past this entry. */
			buf = (NCX struct dirent *)((byte_t *)buf + partial);
			bufsize -= partial;
			result += partial;
			/* Align the buffer by INodes (8 bytes). */
			alignoff = (uintptr_t)buf & (sizeof(ino64_t) - 1);
			if (alignoff) {
				alignoff = sizeof(ino64_t) - alignoff;
				if (bufsize < alignoff)
					break;
				buf = (NCX struct dirent *)((byte_t *)buf + alignoff);
				bufsize -= alignoff;
				result += alignoff;
			}
		}
	} else {
		if ((mode & READDIR_MODEMASK) > READDIR_MODEMAX) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE,
			      mode & READDIR_MODEMASK);
		}
		result = handle_readdirf(hand, buf, bufsize, (readdir_mode_t)mode,
		                         (hand.h_mode & ~IO_USERF_MASK) | iomode);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_KREADDIRF */





/************************************************************************/
/* kcmp()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KCMP
PRIVATE NONNULL((1)) void KCALL
kcmp_require_inspect_process(struct task *__restrict thread) {
	struct task *me = THIS_TASK;
	if (thread == me)
		return; /* Always allowed to inspect yourself */
	if (task_getprocpid_of(me) == task_getprocpid_of(thread))
		return; /* Another thread within the current process */
	if (task_getprocptr_of(me) == task_getparentprocessptr_of(thread))
		return; /* One of our child threads */
	require(CAP_SYS_PTRACE);
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct task *KCALL
kcmp_get_thread_from_pid(pid_t pid) {
	REF struct task *result;
	/* Lookup the thread in question */
	result = pidns_lookuptask_srch(THIS_PIDNS, pid);
	TRY {
		/* Make sure that the caller is allowed to inspect `thread' */
		kcmp_require_inspect_process(result);
	} EXCEPT {
		decref_unlikely(result);
		RETHROW();
	}
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct handman *KCALL
kcmp_get_handman_from_pid(pid_t pid) {
	REF struct handman *result;
	REF struct task *thread;
	thread = kcmp_get_thread_from_pid(pid); /* Lookup the thread in question */
	result = task_gethandman(thread);       /* Retrieve the thread's handle manager. */
	decref_unlikely(thread);
	return result;
}

PRIVATE WUNUSED REF struct handle KCALL
kcmp_get_handle_from_pid(pid_t pid, fd_t fd) {
	REF struct handman *hman;
	hman = kcmp_get_handman_from_pid(pid);
	FINALLY_DECREF_UNLIKELY(hman);
	/* XXX: Support for symbolic handles? */
	return handman_lookup(hman, fd);
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct mman *KCALL
kcmp_get_mman_from_pid(pid_t pid) {
	REF struct mman *result;
	REF struct task *thread;
	thread = kcmp_get_thread_from_pid(pid); /* Lookup the thread in question */
	result = task_getmman(thread);          /* Retrieve the thread's mman. */
	decref_unlikely(thread);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct fs *KCALL
kcmp_get_fs_from_pid(pid_t pid) {
	REF struct fs *result;
	REF struct task *thread;
	thread = kcmp_get_thread_from_pid(pid); /* Lookup the thread in question */
	result = task_getfs(thread);            /* Retrieve the thread's filesystem controller. */
	decref_unlikely(thread);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct sighand_ptr *KCALL
kcmp_get_sighand_ptr_from_pid(pid_t pid) {
	REF struct sighand_ptr *result;
	REF struct task *thread;
	thread = kcmp_get_thread_from_pid(pid); /* Lookup the thread in question */
	result = task_getsighand_ptr(thread);   /* Retrieve the thread's filesystem controller. */
	decref_unlikely(thread);
	return result;
}

#define KCMP_ORDER_EQUAL    0 /* type(pid1:idx1) == type(pid2:idx2) */
#define KCMP_ORDER_LESS     1 /* type(pid1:idx1) <  type(pid2:idx2) */
#define KCMP_ORDER_MORE     2 /* type(pid1:idx1) >  type(pid2:idx2) */
#define KCMP_ORDER_NOTEQUAL 3 /* type(pid1:idx1) != type(pid2:idx2) */

PRIVATE NOBLOCK ATTR_PURE syscall_slong_t
NOTHROW(FCALL kcmp_pointer)(void *a, void *b) {
	a = skew_kernel_pointer(a);
	b = skew_kernel_pointer(b);
	if (a < b)
		return KCMP_ORDER_LESS;
	if (a > b)
		return KCMP_ORDER_MORE;
	return KCMP_ORDER_EQUAL;
}


DEFINE_SYSCALL5(syscall_slong_t, kcmp,
                pid_t, pid1, pid_t, pid2, syscall_ulong_t, type,
                syscall_ulong_t, idx1, syscall_ulong_t, idx2) {
	syscall_slong_t result;
	switch (type) {

	case KCMP_FILE: {
		REF struct handle hand1;
		REF struct handle hand2;
		hand1 = kcmp_get_handle_from_pid(pid1, (fd_t)(syscall_slong_t)idx1);
		RAII_FINALLY { decref_unlikely(hand1); };
		hand2  = kcmp_get_handle_from_pid(pid2, (fd_t)(syscall_slong_t)idx2);
		result = kcmp_pointer(hand1.h_data, hand2.h_data);
		decref_unlikely(hand2);
	}	break;

	case KCMP_VM: {
		REF struct mman *mm1;
		REF struct mman *mm2;
		mm1 = kcmp_get_mman_from_pid(pid1);
		FINALLY_DECREF_UNLIKELY(mm1);
		mm2 = kcmp_get_mman_from_pid(pid2);
		FINALLY_DECREF_UNLIKELY(mm2);
		result = kcmp_pointer(mm1, mm2);
	}	break;

	case KCMP_FILES: {
		REF struct handman *hman1;
		REF struct handman *hman2;
		hman1 = kcmp_get_handman_from_pid(pid1);
		FINALLY_DECREF_UNLIKELY(hman1);
		hman2 = kcmp_get_handman_from_pid(pid2);
		FINALLY_DECREF_UNLIKELY(hman2);
		result = kcmp_pointer(hman1, hman2);
	}	break;

	case KCMP_FS: {
		REF struct fs *fs1;
		REF struct fs *fs2;
		fs1 = kcmp_get_fs_from_pid(pid1);
		FINALLY_DECREF_UNLIKELY(fs1);
		fs2 = kcmp_get_fs_from_pid(pid2);
		FINALLY_DECREF_UNLIKELY(fs2);
		result = kcmp_pointer(fs1, fs2);
	}	break;

	case KCMP_SIGHAND: {
		REF struct sighand_ptr *hand1;
		REF struct sighand_ptr *hand2;
		hand1 = kcmp_get_sighand_ptr_from_pid(pid1);
		FINALLY_DECREF_UNLIKELY(hand1);
		hand2 = kcmp_get_sighand_ptr_from_pid(pid2);
		FINALLY_DECREF_UNLIKELY(hand2);
		result = kcmp_pointer(hand1 ? atomic_read(&hand1->sp_hand) : NULL,
		                      hand2 ? atomic_read(&hand2->sp_hand) : NULL);
	}	break;

	/* XXX: Support for `KCMP_IO' */
	/* XXX: Support for `KCMP_SYSVSEM' */
	/* XXX: Support for `KCMP_EPOLL_TFD' */

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_KCMP_TYPE,
		      type);
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_KCMP */


DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_SYSCALLS_C */
