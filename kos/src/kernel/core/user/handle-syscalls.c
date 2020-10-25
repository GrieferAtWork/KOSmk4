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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C
#define GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C 1
#define _GNU_SOURCE 1 /* TIMEVAL_TO_TIMESPEC */
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <fs/file.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <bits/os/iovec.h> /* struct iovec */
#include <compat/config.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/hop/handle.h>
#include <kos/io.h>
#include <linux/fs.h>
#include <linux/kcmp.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <sys/time.h> /* TIMEVAL_TO_TIMESPEC */
#include <sys/uio.h>

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <malloca.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/iovec.h>
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

#if (defined(__ARCH_WANT_SYSCALL_SELECT) && defined(__ARCH_WANT_SYSCALL__NEWSELECT))
#include <kos/compat/linux-oldselect.h>
#endif /* __ARCH_WANT_SYSCALL_SELECT && __ARCH_WANT_SYSCALL__NEWSELECT */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) && defined(__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT))
#include <compat/kos/compat/linux-oldselect.h>
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT && __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */

DECL_BEGIN

STATIC_ASSERT(IO_HANDLE_FFROM_OPENFLAG(O_CLOEXEC) == IO_CLOEXEC);
STATIC_ASSERT(IO_HANDLE_FFROM_OPENFLAG(O_CLOFORK) == IO_CLOFORK);
STATIC_ASSERT(IO_HANDLE_FFROM_OPENFLAG(O_CLOEXEC | O_CLOFORK) == (IO_CLOEXEC | IO_CLOFORK));
STATIC_ASSERT(IO_HANDLE_FTO_OPENFLAG(IO_CLOEXEC) == O_CLOEXEC);
STATIC_ASSERT(IO_HANDLE_FTO_OPENFLAG(IO_CLOFORK) == O_CLOFORK);
STATIC_ASSERT(IO_HANDLE_FTO_OPENFLAG(IO_CLOEXEC | IO_CLOFORK) == (O_CLOEXEC | O_CLOFORK));
STATIC_ASSERT(IO_HANDLE_FFROM_FD(FD_CLOEXEC) == IO_CLOEXEC);
STATIC_ASSERT(IO_HANDLE_FFROM_FD(FD_CLOFORK) == IO_CLOFORK);
STATIC_ASSERT(IO_HANDLE_FFROM_FD(FD_CLOEXEC | FD_CLOFORK) == (IO_CLOEXEC | IO_CLOFORK));
STATIC_ASSERT(IO_HANDLE_FTO_FD(IO_CLOEXEC) == FD_CLOEXEC);
STATIC_ASSERT(IO_HANDLE_FTO_FD(IO_CLOFORK) == FD_CLOFORK);
STATIC_ASSERT(IO_HANDLE_FTO_FD(IO_CLOEXEC | IO_CLOFORK) == (FD_CLOEXEC | FD_CLOFORK));

/************************************************************************/
/* dup(), dup2(), dup3()                                                */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_DUP
DEFINE_SYSCALL1(fd_t, dup, fd_t, fd) {
	unsigned int result;
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	hand.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
	TRY {
		result = handle_install(THIS_HANDLE_MANAGER, hand);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_DUP */


#ifdef __ARCH_WANT_SYSCALL_DUP2
DEFINE_SYSCALL2(fd_t, dup2, fd_t, oldfd, fd_t, newfd) {
	struct handle hand;
	hand = handle_lookup((unsigned int)oldfd);
	hand.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
	TRY {
		handle_installinto_sym((unsigned int)newfd, hand);
	} EXCEPT {
		if (was_thrown(E_INVALID_HANDLE_FILETYPE)) {
			struct exception_data *d = error_data();
			if (d->e_args.e_invalid_handle.ih_fd == (uintptr_t)-1)
				d->e_args.e_invalid_handle.ih_fd = (uintptr_t)(intptr_t)oldfd;
		}
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return newfd;
}
#endif /* __ARCH_WANT_SYSCALL_DUP2 */


#ifdef __ARCH_WANT_SYSCALL_DUP3
DEFINE_SYSCALL3(fd_t, dup3, fd_t, oldfd, fd_t, newfd, oflag_t, flags) {
	struct handle hand;
	VALIDATE_FLAGSET(flags,
	                 O_CLOEXEC | O_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_DUP3_OFLAG);
	hand = handle_lookup((unsigned int)oldfd);
	hand.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
	hand.h_mode |= IO_HANDLE_FTO_OPENFLAG(flags);
	TRY {
		handle_installinto_sym((unsigned int)newfd, hand);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return newfd;
}
#endif /* __ARCH_WANT_SYSCALL_DUP3 */





/************************************************************************/
/* fcntl()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FCNTL
DEFINE_SYSCALL3(syscall_slong_t, fcntl,
                fd_t, fd,
                syscall_ulong_t, command,
                UNCHECKED USER void *, arg) {
	return handle_fcntl(THIS_HANDLE_MANAGER,
	                    fd,
	                    command,
	                    arg);
}
#endif /* __ARCH_WANT_SYSCALL_FCNTL */





/************************************************************************/
/* ioctl(), ioctlf()                                                    */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_IOCTL) || defined(__ARCH_WANT_SYSCALL_IOCTLF)
PRIVATE NOBLOCK void
NOTHROW(KCALL ioctl_complete_exception_info)(unsigned int fd) {
	error_code_t code = error_code();
	switch (code) {

	case ERROR_CODEOF(E_INVALID_HANDLE_OPERATION):
		if (!PERTASK_GET(this_exception_args.e_invalid_handle.ih_fd)) /* fd */
			PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, (uintptr_t)fd);
		break;

	default: break;
	}
}

PRIVATE bool KCALL
ioctl_generic(syscall_ulong_t command,
              unsigned int fd,
              struct handle const *__restrict hand,
              USER UNCHECKED void *arg,
              syscall_slong_t *__restrict result) {
	switch (command) {

	case FIOCLEX:
		/* Set IO_CLOEXEC */
		if (hand->h_mode & IO_CLOEXEC)
			break;
		handle_stflags(THIS_HANDLE_MANAGER, fd, ~0, IO_CLOEXEC);
		break;

	case FIONCLEX:
		/* Clear IO_CLOEXEC */
		if (!(hand->h_mode & IO_CLOEXEC))
			break;
		handle_stflags(THIS_HANDLE_MANAGER, fd, ~IO_CLOEXEC, 0);
		break;

	case FIONBIO:
	case _IOW(_IOC_TYPE(FIONBIO), _IOC_NR(FIONBIO), int): {
		int mode;
		/* Set/clear IO_NONBLOCK */
		validate_readable(arg, sizeof(int));
		mode = ATOMIC_READ(*(int *)arg);
		/* XXX: Verify mode == 0/1 */
		handle_stflags(THIS_HANDLE_MANAGER,
		               fd,
		               ~IO_NONBLOCK,
		               mode ? IO_NONBLOCK : 0);
	}	break;

	case FIOASYNC:
	case _IOW(_IOC_TYPE(FIOASYNC), _IOC_NR(FIOASYNC), int): {
		/* Set/clear IO_ASYNC */
		int mode;
		validate_readable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		mode = *(USER CHECKED int *)arg;
		COMPILER_READ_BARRIER();
		/* XXX: Verify mode == 0/1 */
		handle_stflags(THIS_HANDLE_MANAGER,
		               fd,
		               ~IO_ASYNC,
		               mode ? IO_ASYNC
		                    : 0);
	}	break;

#if __SIZEOF_LOFF_T__ == 8
	case FIOQSIZE:
#endif /* __SIZEOF_LOFF_T__ == 8 */
	case _IOR(_IOC_TYPE(FIOQSIZE), _IOC_NR(FIOQSIZE), u64): {
		pos_t value;
		if unlikely(!handle_datasize(hand, &value)) {
			*result = -ENOTTY;
			return true;
		}
		validate_writable(arg, sizeof(u64));
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED u64 *)arg = (u64)value;
	}	break;

#if __SIZEOF_LOFF_T__ == 4
	case FIOQSIZE:
#endif /* __SIZEOF_LOFF_T__ == 4 */
	case _IOR(_IOC_TYPE(FIOQSIZE), _IOC_NR(FIOQSIZE), u32): {
		pos_t value;
		if unlikely(!handle_datasize(hand, &value)) {
			*result = -ENOTTY;
			return true;
		}
		validate_writable(arg, sizeof(u32));
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED u32 *)arg = (u32)value;
	}	break;

	case FIGETBSZ:
	case _IOR(_IOC_TYPE(FIGETBSZ), _IOC_NR(FIGETBSZ), int): {
		struct stat st;
		validate_writable(arg, sizeof(int));
		handle_stat(*hand, &st);
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED int *)arg = (int)(unsigned int)st.st_blksize;
	}	break;

	default:
		if (_IOC_TYPE(command) == 'T') {
			/* All KOS-specific ioctl commands with type='T' are
			 * tty-specific, so we must return `-ENOTTY' for all
			 * of them! */
			if (_IOC_ISKOS(command))
				goto do_return_notty;
			switch (_IOC_NR(command)) {

			case _IOC_NR(TCGETS) ... _IOC_NR(TIOCPKT):
			case _IOC_NR(TIOCNOTTY) ... _IOC_NR(TIOCGEXCL):
			case _IOC_NR(TIOCSERCONFIG) ... _IOC_NR(TIOCGICOUNT):
				/* TTY-specific ioctl()s (user-space uses one of these to implement `isatty()') */
do_return_notty:
				*result = -ENOTTY;
				return true;

			default:
				break;
			}
		}
		return false;
	}
	*result = 0;
/*done:*/
	return true;
}
#endif /* __ARCH_WANT_SYSCALL_IOCTL || __ARCH_WANT_SYSCALL_IOCTLF */

#ifdef __ARCH_WANT_SYSCALL_IOCTL
DEFINE_SYSCALL3(syscall_slong_t, ioctl,
                fd_t, fd,
                syscall_ulong_t, command,
                UNCHECKED USER void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		result = handle_ioctl(hand,
		                      command,
		                      arg);
	} EXCEPT {
		if (was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) &&
		    PERTASK_GET(this_exception_args.e_invalid_argument.ia_context) == E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND) {
			TRY {
				if (ioctl_generic(command, fd, &hand, arg, &result))
					goto done;
			} EXCEPT {
				ioctl_complete_exception_info((unsigned int)fd);
				decref(hand);
				RETHROW();
			}
		}
		ioctl_complete_exception_info((unsigned int)fd);
		decref(hand);
		RETHROW();
	}
done:
	decref(hand);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_IOCTL */

#ifdef __ARCH_WANT_SYSCALL_IOCTLF
DEFINE_SYSCALL4(syscall_slong_t, ioctlf,
                fd_t, fd, syscall_ulong_t, command,
                iomode_t, mode,
                USER UNCHECKED void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		result = handle_ioctlf(hand,
		                       command,
		                       arg,
		                       mode);
	} EXCEPT {
		if (was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) &&
		    PERTASK_GET(this_exception_args.e_invalid_argument.ia_context) == E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND) {
			TRY {
				if (ioctl_generic(command, fd, &hand, arg, &result))
					goto done;
			} EXCEPT {
				ioctl_complete_exception_info((unsigned int)fd);
				decref(hand);
				RETHROW();
			}
		}
		ioctl_complete_exception_info((unsigned int)fd);
		decref(hand);
		RETHROW();
	}
done:
	decref(hand);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_IOCTLF */





/************************************************************************/
/* ftruncate(), ftruncate64()                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FTRUNCATE
DEFINE_SYSCALL2(errno_t, ftruncate, fd_t, fd, syscall_ulong_t, length) {
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_TRUNC, hand.h_mode);
		handle_truncate(hand, (pos_t)length);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_FTRUNCATE */

#ifdef __ARCH_WANT_SYSCALL_FTRUNCATE64
DEFINE_SYSCALL2(errno_t, ftruncate64, fd_t, fd, uint64_t, length) {
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_TRUNC, hand.h_mode);
		handle_truncate(hand, (pos_t)length);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return 0;
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
	hand = handle_lookup((unsigned int)fd);
	TRY {
		handle_allocate(hand,
		                mode,
		                (pos_t)offset,
		                (pos_t)length);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_FALLOCATE */

#ifdef __ARCH_WANT_SYSCALL_FALLOCATE64
DEFINE_SYSCALL4(errno_t, fallocate64,
                fd_t, fd, syscall_ulong_t, mode,
                uint64_t, offset, uint64_t, length) {
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		handle_allocate(hand,
		                mode,
		                (pos_t)offset,
		                (pos_t)length);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_FALLOCATE64 */





/************************************************************************/
/* close()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_CLOSE
DEFINE_SYSCALL1(errno_t, close, fd_t, fd) {
	handle_close((unsigned int)fd);
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_CLOSE */





/************************************************************************/
/* lseek(), lseek64(), _llseek()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_LSEEK
DEFINE_SYSCALL3(syscall_slong_t, lseek,
                fd_t, fd, syscall_slong_t, offset,
                syscall_ulong_t, whence) {
	pos_t result;
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		result = handle_seek(hand, (off_t)offset, whence);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (syscall_slong_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_LSEEK */

#ifdef __ARCH_WANT_SYSCALL_LSEEK64
DEFINE_SYSCALL3(int64_t, lseek64,
                fd_t, fd, int64_t, offset,
                syscall_ulong_t, whence) {
	pos_t result;
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		result = handle_seek(hand,
		                     (off_t)offset,
		                     whence);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (int64_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_LSEEK64 */

#ifdef __ARCH_WANT_SYSCALL__LLSEEK
DEFINE_SYSCALL4(errno_t, _llseek, fd_t, fd, int64_t, offset,
                USER UNCHECKED uint64_t *, result,
                syscall_ulong_t, whence) {
	uint64_t retpos;
	validate_writable(result, sizeof(uint64_t));
	retpos  = (uint64_t)sys_lseek64(fd, offset, whence);
	*result = retpos;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL__LLSEEK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL__LLSEEK
DEFINE_COMPAT_SYSCALL4(errno_t, _llseek,
                       fd_t, fd, int64_t, offset,
                       USER UNCHECKED uint64_t *, result,
                       syscall_ulong_t, whence) {
	uint64_t retpos;
	compat_validate_writable(result, sizeof(uint64_t));
#ifdef __ARCH_WANT_SYSCALL_LSEEK64
	retpos  = (uint64_t)sys_lseek64(fd, offset, whence);
#else /* __ARCH_WANT_SYSCALL_LSEEK64 */
	retpos  = (uint64_t)sys_lseek(fd, offset, whence);
#endif /* !__ARCH_WANT_SYSCALL_LSEEK64 */
	*result = retpos;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL__LLSEEK */





/************************************************************************/
/* read(), write(), readf(), writef()                                   */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_READ
DEFINE_SYSCALL3(ssize_t, read, fd_t, fd,
                USER UNCHECKED void *, buf, size_t, bufsize) {
	size_t result;
	struct handle hand;
	validate_writable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		result = handle_read(hand, buf, bufsize);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_READ */

#ifdef __ARCH_WANT_SYSCALL_WRITE
DEFINE_SYSCALL3(ssize_t, write, fd_t, fd,
                USER UNCHECKED void const *, buf, size_t, bufsize) {
	size_t result;
	struct handle hand;
	validate_readable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		result = handle_write(hand, buf, bufsize);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_WRITE */

#ifdef __ARCH_WANT_SYSCALL_READF
DEFINE_SYSCALL4(ssize_t, readf,
                fd_t, fd, USER UNCHECKED void *, buf,
                size_t, bufsize, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_READF_MODE);
	validate_writable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		result = handle_readf(hand,
		                      buf,
		                      bufsize,
		                      (hand.h_mode & ~IO_USERF_MASK) | mode);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_READF */

#ifdef __ARCH_WANT_SYSCALL_WRITEF
DEFINE_SYSCALL4(ssize_t, writef,
                fd_t, fd, USER UNCHECKED void const *, buf,
                size_t, bufsize, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_WRITEF_MODE);
	validate_readable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		result = handle_writef(hand,
		                       buf,
		                       bufsize,
		                       (hand.h_mode & ~IO_USERF_MASK) | mode);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_WRITEF */





/************************************************************************/
/* pread64(), pwrite64(), pread64f(), pwrite64f()                       */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PREAD64
DEFINE_SYSCALL4(ssize_t, pread64, fd_t, fd,
                USER UNCHECKED void *, buf,
                size_t, bufsize, uint64_t, offset) {
	size_t result;
	struct handle hand;
	validate_writable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		result = handle_pread(hand,
		                      buf,
		                      bufsize,
		                      (pos_t)offset);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREAD64 */

#ifdef __ARCH_WANT_SYSCALL_PWRITE64
DEFINE_SYSCALL4(ssize_t, pwrite64, fd_t, fd,
                USER UNCHECKED void const *, buf,
                size_t, bufsize, uint64_t, offset) {
	size_t result;
	struct handle hand;
	validate_readable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		result = handle_pwrite(hand,
		                       buf,
		                       bufsize,
		                       (pos_t)offset);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITE64 */

#ifdef __ARCH_WANT_SYSCALL_PREAD64F
DEFINE_SYSCALL5(ssize_t, pread64f,
                fd_t, fd, USER UNCHECKED void *, buf,
                size_t, bufsize, uint64_t, offset, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_PREADF_MODE);
	validate_writable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		result = handle_preadf(hand,
		                       buf,
		                       bufsize,
		                       (pos_t)offset,
		                       (hand.h_mode & ~IO_USERF_MASK) | mode);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREAD64F */

#ifdef __ARCH_WANT_SYSCALL_PWRITE64F
DEFINE_SYSCALL5(ssize_t, pwrite64f,
                fd_t, fd, USER UNCHECKED void const *, buf,
                size_t, bufsize, uint64_t, offset, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_PWRITEF_MODE);
	validate_readable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		result = handle_pwritef(hand,
		                        buf,
		                        bufsize,
		                        (pos_t)offset,
		                        (hand.h_mode & ~IO_USERF_MASK) | mode);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITE64F */





/************************************************************************/
/* readv(), writev()                                                  */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PREADV
DEFINE_SYSCALL3(ssize_t, readv, fd_t, fd,
                USER UNCHECKED struct iovec const *, iov,
                size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					validate_writable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                  ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_readv(hand,
				                      &dst,
				                      num_bytes);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_SYSCALL_PWRITEV
DEFINE_SYSCALL3(ssize_t, writev, fd_t, fd,
                USER UNCHECKED struct iovec const *, iov,
                size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					validate_readable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                  ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_writev(hand,
				                       &dst,
				                       num_bytes);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITEV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PREADV
DEFINE_COMPAT_SYSCALL3(ssize_t, readv, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					compat_validate_writable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                         ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_readv(hand,
				                      &dst,
				                      num_bytes);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PWRITEV
DEFINE_COMPAT_SYSCALL3(ssize_t, writev, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					compat_validate_readable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                         ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_writev(hand,
				                       &dst,
				                       num_bytes);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PWRITEV */





/************************************************************************/
/* preadv(), pwritev()                                                  */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PREADV
DEFINE_SYSCALL4(ssize_t, preadv, fd_t, fd,
                USER UNCHECKED struct iovec const *, iov,
                size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					validate_writable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                  ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_preadv(hand,
				                       &dst,
				                       num_bytes,
				                       (pos_t)offset);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_SYSCALL_PWRITEV
DEFINE_SYSCALL4(ssize_t, pwritev, fd_t, fd,
                USER UNCHECKED struct iovec const *, iov,
                size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					validate_readable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                  ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_pwritev(hand,
				                        &dst,
				                        num_bytes,
				                        (pos_t)offset);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITEV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PREADV
DEFINE_COMPAT_SYSCALL4(ssize_t, preadv, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					compat_validate_writable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                         ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_preadv(hand,
				                       &dst,
				                       num_bytes,
				                       (pos_t)offset);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PWRITEV
DEFINE_COMPAT_SYSCALL4(ssize_t, pwritev, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct aio_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
		if unlikely(!count)
			result = 0;
		else {
			dst.ab_entc = count;
			dst.ab_entv = (struct aio_buffer_entry *)malloca(count *
			                                                 sizeof(struct aio_buffer_entry));
			TRY {
				size_t i;
				for (i = 0, num_bytes = 0; i < count; ++i) {
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					compat_validate_readable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
					                         ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size);
					num_bytes += ((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size;
				}
				dst.ab_head = dst.ab_entv[0];
				dst.ab_last = dst.ab_entv[count - 1].ab_size;
				result = handle_pwritev(hand,
				                        &dst,
				                        num_bytes,
				                        (pos_t)offset);
			} EXCEPT {
				freea((void *)dst.ab_entv);
				RETHROW();
			}
			freea((void *)dst.ab_entv);
		}
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PWRITEV */





/************************************************************************/
/* fsync(), fdatasync()                                                 */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FSYNC
DEFINE_SYSCALL1(errno_t, fsync, fd_t, fd) {
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		handle_sync(hand);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_FSYNC */

#ifdef __ARCH_WANT_SYSCALL_FDATASYNC
DEFINE_SYSCALL1(errno_t, fdatasync, fd_t, fd) {
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		handle_datasync(hand);
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_FDATASYNC */





/************************************************************************/
/* hop(), hopf()                                                        */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_HOP) || defined(__ARCH_WANT_SYSCALL_HOPF)
#define hop_do_generic_operation(hand, hop_command, fd, arg) \
	hop_do_generic_operation(hand, hop_command, arg)
PRIVATE syscall_slong_t
(KCALL hop_do_generic_operation)(struct handle *__restrict hand,
                                 uintptr_t hop_command,
                                 USER UNCHECKED void *arg) {
	switch (hop_command) {

	case HOP_HANDLE_STAT: {
		USER CHECKED struct hop_handle_stat *info;
		struct hop_handle_stat st;
		size_t info_size;
		char const *name;
		memset(&st, 0, sizeof(st));
		st.hs_struct_size = sizeof(st);
		st.hs_mode        = hand->h_mode;
		st.hs_type        = hand->h_type;
		st.hs_kind        = handle_typekind(hand);
		st.hs_refcnt      = (*handle_type_db.h_refcnt[hand->h_type])(hand->h_data);
		st.hs_address     = (u64)(uintptr_t)skew_kernel_pointer(hand->h_data);
		name              = handle_type_db.h_typename[hand->h_type];
		memcpy(st.hs_typename, name,
		       strnlen(name, COMPILER_LENOF(st.hs_typename) - 1),
		       sizeof(char));
		COMPILER_BARRIER();
		info = (USER CHECKED struct hop_handle_stat *)arg;
		validate_readwrite(info, sizeof(*info));
		info_size = ATOMIC_READ(info->hs_struct_size);
		if (info_size != sizeof(*info))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*info), info_size);
		memcpy(info, &st, sizeof(*info));
	}	break;

	case HOP_HANDLE_REOPEN:
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, *hand);
		break;

	case HOP_HANDLE_NOOP:
		break;

	case HOP_HANDLE_GET_REFCNT:
		validate_writable(arg, sizeof(u64));
		*(u64 *)arg = (u64)handle_refcnt(*hand);
		break;

	case HOP_HANDLE_GET_ADDRESS:
		validate_writable(arg, sizeof(u64));
		*(USER CHECKED u64 *)arg = (u64)(uintptr_t)skew_kernel_pointer(hand->h_data);
		break;

	case HOP_HANDLE_GET_TYPE:
		validate_writable(arg, sizeof(uint16_t));
		*(USER CHECKED uint16_t *)arg = (uint16_t)hand->h_type;
		break;

	case HOP_HANDLE_GET_KIND:
		validate_writable(arg, sizeof(uint16_t));
		*(USER CHECKED uint16_t *)arg = (uint16_t)handle_typekind(hand);
		break;

	case HOP_HANDLE_GET_MODE:
		validate_writable(arg, sizeof(uint16_t));
		*(USER CHECKED uint16_t *)arg = (uint16_t)hand->h_mode;
		break;

	case HOP_HANDLE_DUP: {
		struct handle dup;
		dup = *hand;
		dup.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
		return handle_install(THIS_HANDLE_MANAGER, dup);
	}	break;

	case HOP_HANDLE_DUP_CLOEXEC: {
		struct handle dup;
		dup = *hand;
		dup.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
		dup.h_mode |= IO_CLOEXEC;
		return handle_install(THIS_HANDLE_MANAGER, dup);
	}	break;

	case HOP_HANDLE_DUP_CLOFORK: {
		struct handle dup;
		dup = *hand;
		dup.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
		dup.h_mode |= IO_CLOFORK;
		return handle_install(THIS_HANDLE_MANAGER, dup);
	}	break;

	case HOP_HANDLE_DUP_CLOEXEC_CLOFORK: {
		struct handle dup;
		dup = *hand;
		dup.h_mode |= (IO_CLOEXEC | IO_CLOFORK);
		return handle_install(THIS_HANDLE_MANAGER, dup);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      hop_command);
		break;
	}
	return 0;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL hop_complete_exception_info)(struct handle *__restrict hand,
                                           unsigned int fd,
                                           uintptr_t hop_command) {
	error_code_t code = error_code();
	switch (code) {

	case ERROR_CODEOF(E_INVALID_HANDLE_FILETYPE):
		if (!PERTASK_GET(this_exception_args.e_invalid_handle.ih_fd))
			PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, (uintptr_t)fd);
		if (!PERTASK_GET(this_exception_args.e_invalid_handle.ih_filetype.f_actual_handle_type))
			PERTASK_SET(this_exception_args.e_invalid_handle.ih_filetype.f_actual_handle_type, (uintptr_t)hand->h_type);
		if (!PERTASK_GET(this_exception_args.e_invalid_handle.ih_filetype.f_actual_handle_kind))
			PERTASK_SET(this_exception_args.e_invalid_handle.ih_filetype.f_actual_handle_kind, (uintptr_t)handle_typekind(hand));
		break;

	case ERROR_CODEOF(E_INVALID_ARGUMENT_UNKNOWN_COMMAND):
		if (PERTASK_GET(this_exception_args.e_invalid_argument.ia_context) != E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND)
			break;
		if ((hop_command >> 16) == HANDLE_TYPE_UNDEFINED ||
		    (hop_command >> 16) >= HANDLE_TYPE_COUNT)
			break;
		if (hand->h_type == (hop_command >> 16))
			break;
		/* If the command (may) actually exist, but simply cannot be applied to the
		 * associated handle type, translate the exception to `E_INVALID_HANDLE_FILETYPE',
		 * with the required file type set there. */
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_INVALID_HANDLE_FILETYPE));
		PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, (uintptr_t)fd);
		PERTASK_SET(this_exception_args.e_invalid_handle.ih_filetype.f_needed_handle_type, (uintptr_t)(hop_command >> 16)); /* HOP Commands encode the required type like this */
		PERTASK_SET(this_exception_args.e_invalid_handle.ih_filetype.f_actual_handle_type, (uintptr_t)hand->h_type);
		PERTASK_SET(this_exception_args.e_invalid_handle.ih_filetype.f_needed_handle_kind, (uintptr_t)HANDLE_TYPEKIND_GENERIC); /* XXX: Not necessarily correct... */
		PERTASK_SET(this_exception_args.e_invalid_handle.ih_filetype.f_actual_handle_kind, (uintptr_t)handle_typekind(hand));
		break;

	default: break;
	}
}
#endif /* __ARCH_WANT_SYSCALL_HOP || __ARCH_WANT_SYSCALL_HOPF */

#ifdef __ARCH_WANT_SYSCALL_HOP
DEFINE_SYSCALL3(syscall_slong_t, hop,
                fd_t, fd, syscall_ulong_t, cmd,
                USER UNCHECKED void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if ((cmd & 0xffff0000) == (HOP_HANDLE_STAT & 0xffff0000)) {
			result = hop_do_generic_operation(&hand, cmd, (unsigned int)fd, arg);
		} else {
			uintptr_half_t wanted_type;
			/* Do implicit handle casting based on the expected type encoded in `cmd >> 16'.
			 * e.g.: A DATABLOCK command on a FILE object should be allowed */
			wanted_type = (u16)(cmd >> 16);
			if (wanted_type != hand.h_type) {
				/* This should be a try-as!
				 * If handles cannot be converted, we should invoke the HOP on the original
				 * handle, for example allowing FIFO-related handles to re-use PIPE-hop()s! */
				REF void *new_data;
				new_data = handle_tryas(hand, wanted_type);
				if (new_data) {
					hand.h_data = new_data; /* Inherit reference */
					hand.h_type = wanted_type;
				}
			}
			result = (*handle_type_db.h_hop[wanted_type])(hand.h_data,
			                                              cmd,
			                                              arg,
			                                              hand.h_mode);
		}
	} EXCEPT {
		/* Auto-complete some exceptions with handle-specific information. */
		hop_complete_exception_info(&hand, (unsigned int)fd, cmd);
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_HOP */

#ifdef __ARCH_WANT_SYSCALL_HOPF
DEFINE_SYSCALL4(syscall_slong_t, hopf,
                fd_t, fd, syscall_ulong_t, cmd,
                iomode_t, mode,
                USER UNCHECKED void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_HOPF_MODE);
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if ((cmd & 0xffff0000) == (HOP_HANDLE_STAT & 0xffff0000)) {
			result = hop_do_generic_operation(&hand, cmd, (unsigned int)fd, arg);
		} else {
			result = (*handle_type_db.h_hop[hand.h_type])(hand.h_data,
			                                              cmd,
			                                              arg,
			                                              (hand.h_mode & ~IO_USERF_MASK) | mode);
		}
	} EXCEPT {
		/* Auto-complete some exceptions with handle-specific information. */
		hop_complete_exception_info(&hand, (unsigned int)fd, cmd);
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_HOPF */





/************************************************************************/
/* kreaddir(), kreaddirf()                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KREADDIR
DEFINE_SYSCALL4(ssize_t, kreaddir,
                fd_t, fd, USER UNCHECKED struct dirent *, buf,
                size_t, bufsize, syscall_ulong_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 READDIR_MODEMASK | READDIR_FLAGMASK,
	                 E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE);
	validate_writable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
	TRY {
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
				buf = (USER struct dirent *)((byte_t *)buf + partial);
				bufsize -= partial;
				result += partial;
				/* Align the buffer by INodes (8 bytes). */
				alignoff = (uintptr_t)buf & (sizeof(ino64_t) - 1);
				if (alignoff) {
					alignoff = sizeof(ino64_t) - alignoff;
					if (bufsize < alignoff)
						break;
					buf = (USER struct dirent *)((byte_t *)buf + alignoff);
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
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
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
	hand = handle_lookup((unsigned int)fd);
	TRY {
		if unlikely(!IO_CANREAD(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
		if ((mode & READDIR_MODEMASK) == READDIR_MULTIPLE) {
			size_t partial, alignoff;
			result = 0;
			mode &= ~(READDIR_MODEMASK);
#if READDIR_DEFAULT != 0
			mode |= READDIR_DEFAULT;
#endif
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
				buf = (USER struct dirent *)((byte_t *)buf + partial);
				bufsize -= partial;
				result += partial;
				/* Align the buffer by INodes (8 bytes). */
				alignoff = (uintptr_t)buf & (sizeof(ino64_t) - 1);
				if (alignoff) {
					alignoff = sizeof(ino64_t) - alignoff;
					if (bufsize < alignoff)
						break;
					buf = (USER struct dirent *)((byte_t *)buf + alignoff);
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
	} EXCEPT {
		decref(hand);
		RETHROW();
	}
	decref(hand);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_KREADDIRF */





/************************************************************************/
/* poll(), ppoll(), ppoll64()                                           */
/* select(), select64(), pselect6(), pselect6_time64()                  */
/************************************************************************/
#undef WANT_SYS_POLL
#if (defined(__ARCH_WANT_SYSCALL_POLL) ||           \
     defined(__ARCH_WANT_SYSCALL_PPOLL) ||          \
     defined(__ARCH_WANT_SYSCALL_PPOLL64) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
#define WANT_SYS_POLL 1
#endif /* poll... */
#undef WANT_SYS_SELECT
#if (defined(__ARCH_WANT_SYSCALL_SELECT) ||          \
     defined(__ARCH_WANT_SYSCALL_SELECT64) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_64) ||     \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64))
#define WANT_SYS_SELECT 1
#endif /* select... */
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||                  \
     defined(__ARCH_WANT_SYSCALL_PPOLL64) ||                \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) ||           \
     defined(__ARCH_WANT_SYSCALL_PSELECT6) ||               \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_64) ||            \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL64) ||         \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64) ||     \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64) || \
     defined(__ARCH_WANT_SYSCALL_EPOLL_PWAIT))
#define WANT_SYS_POLLSELECT_SIGSET 1
#endif /* p(poll|select)... */
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||          \
     defined(__ARCH_WANT_SYSCALL_PPOLL64) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
#define WANT_SYS_POLL_SIGSET 1
#endif /* ppoll... */
#if (defined(__ARCH_WANT_SYSCALL_PSELECT6) ||           \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_64) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
#define WANT_SYS_SELECT_SIGSET 1
#endif /* pselect... */

#if defined(WANT_SYS_POLL) || defined(WANT_SYS_SELECT)
PRIVATE poll_mode_t KCALL do_poll_handle(struct handle &hnd,
                                         poll_mode_t what) {
	poll_mode_t result;
	/* Always allow polling for these conditions. */
	what |= POLLERR | POLLHUP | POLLNVAL;
	/* Verify that the caller has access to the
	 * indicated data channel of the handle. */
	if (what & POLLINMASK) {
		if unlikely(!IO_CANREAD(hnd.h_mode))
			return POLLERR;
	}
	if (what & POLLOUTMASK) {
		if unlikely(!IO_CANWRITE(hnd.h_mode))
			return POLLERR;
	}
	TRY {
		result = handle_poll(hnd, what) & what;
	} EXCEPT {
		if (was_thrown(E_FSERROR_UNSUPPORTED_OPERATION) &&
		    PERTASK_GET(this_exception_args.e_invalid_argument.ia_context) == E_FILESYSTEM_OPERATION_POLL)
			result = POLLHUP; /* Poll is unsupported. */
		else {
			/* XXX: Are there other exceptions that should yield POLLERR? */
			RETHROW();
		}
	}
	return result;
}
#endif /* WANT_SYS_POLL || WANT_SYS_SELECT */

/* Low-level implementations for the user-space poll() and select() system calls. */
#ifdef WANT_SYS_POLL
PRIVATE size_t KCALL
do_poll(USER CHECKED struct pollfd *fds,
        size_t nfds, struct timespec const *timeout) {
	size_t i, result = 0;
again:
	assert(!task_wasconnected());
	for (i = 0; i < nfds; ++i) {
		struct handle hnd;
		struct pollfd pfd;
		memcpy(&pfd, &fds[i], sizeof(struct pollfd));
		COMPILER_READ_BARRIER();
		if (pfd.fd < 0) {
			/* Negative fd values should simply be ignored */
			fds[i].revents = 0;
			continue;
		}
		TRY {
			hnd = handle_lookup((unsigned int)pfd.fd);
		} EXCEPT {
			if (!was_thrown(E_INVALID_HANDLE))
				RETHROW();
			fds[i].revents = POLLNVAL; /* Invalid handle. */
			continue;
		}
		TRY {
			poll_mode_t what;
#if 0 /* POSIX doesn't specify this... (as a matter of fact: certain bits _should_ be ignored) */
			if unlikely(pfd.events & ~(POLLINMASK | POLLPRI | POLLOUTMASK)) {
				fds[i].revents = POLLNVAL; /* Invalid poll mode. */
				goto decref_hnd_and_continue;
			}
#endif
#ifndef __OPTIMIZE_SIZE__
			/* No need to stay connected to a whole bunch of signals
			 * if we already know we won't wait on any of them */
			if (result != 0)
				task_disconnectall();
#endif /* !__OPTIMIZE_SIZE__ */
			/* Actually perform the poll. */
			what = do_poll_handle(hnd, pfd.events);
			if (what & (POLLINMASK | POLLPRI | POLLOUTMASK))
				++result; /* Got something! */
			fds[i].revents = what;
		} EXCEPT {
			/* Make sure that we're disconnected
			 * from all previous poll-signals! */
			task_disconnectall();
			decref(hnd);
			RETHROW();
		}
/*decref_hnd_and_continue:*/
		decref(hnd);
	}
	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}
	/* Wait for something to happen */
	if (!task_waitfor(timeout))
		return 0; /* Timeout */
	/* Check to see what happened. */
	goto again;
}
#endif /* WANT_SYS_POLL */

#ifdef WANT_SYS_SELECT
PRIVATE size_t KCALL
do_select(size_t nfds,
          USER CHECKED fd_set *readfds,
          USER CHECKED fd_set *writefds,
          USER CHECKED fd_set *exceptfds,
          struct timespec const *timeout) {
	typedef u8 fds_word_t;
	enum { BITS_PER_FDS_WORD = 8 };
	size_t nfds_words, i, result = 0;
again:
	assert(!task_wasconnected());
	nfds_words = CEILDIV(nfds, BITS_PER_FDS_WORD);
	for (i = 0; i < nfds_words; ++i) {
		fds_word_t rbits, wbits, ebits, mask;
		fds_word_t new_rbits, new_wbits, new_ebits;
		unsigned int j, maxbits = BITS_PER_FDS_WORD;
		if (i == nfds_words - 1)
			maxbits = nfds % BITS_PER_FDS_WORD;
		rbits = wbits = ebits = 0;
		if (readfds)
			rbits = ((fds_word_t *)readfds)[i];
		if (writefds)
			wbits = ((fds_word_t *)writefds)[i];
		if (exceptfds)
			ebits = ((fds_word_t *)exceptfds)[i];
		if (!(rbits | wbits | ebits))
			continue;
		new_rbits = new_wbits = new_ebits = 0;
		for (j = 0, mask = 1; j < maxbits; ++j, mask <<= 1) {
			poll_mode_t what, mode;
			struct handle hnd;
			mode = 0;
			if (rbits & mask)
				mode |= POLLSELECT_READFDS;
			if (wbits & mask)
				mode |= POLLSELECT_WRITEFDS;
			if (ebits & mask)
				mode |= POLLSELECT_EXCEPTFDS;
			if (!mode)
				continue;
			hnd = handle_lookup(i * BITS_PER_FDS_WORD + j);
			TRY {
#ifndef __OPTIMIZE_SIZE__
				/* No need to stay connected to a whole bunch of signals
				 * if we already know we won't wait on any of them */
				if (result != 0)
					task_disconnectall();
#endif /* !__OPTIMIZE_SIZE__ */
				what = do_poll_handle(hnd, mode);
			} EXCEPT {
				/* Make sure that we're disconnected
				 * from all previous poll-signals! */
				task_disconnectall();
				decref(hnd);
				RETHROW();
			}
			assert(!(what & ~mode));
			decref(hnd);
			if (!what)
				continue;
			if (!result) {
				/* Clear all fd_set bits leading words. */
				if (readfds)
					memset(readfds, 0, i * sizeof(fds_word_t));
				if (writefds)
					memset(writefds, 0, i * sizeof(fds_word_t));
				if (exceptfds)
					memset(exceptfds, 0, i * sizeof(fds_word_t));
			}
			++result;
			if (what & POLLSELECT_READFDS)
				new_rbits |= mask;
			if (what & POLLSELECT_WRITEFDS)
				new_wbits |= mask;
			if (what & POLLSELECT_EXCEPTFDS)
				new_ebits |= mask;
		}
		if (result) {
			/* Update the fd-set words of all signaled FDs */
			if (readfds)
				((fds_word_t *)readfds)[i] = new_rbits;
			if (writefds)
				((fds_word_t *)writefds)[i] = new_wbits;
			if (exceptfds)
				((fds_word_t *)exceptfds)[i] = new_ebits;
		}
	}
	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}
	/* Wait for something to happen */
	if (!task_waitfor(timeout))
		return 0; /* Timeout */
	/* Check to see what happened. */
	goto again;
}
#endif /* WANT_SYS_SELECT */

#ifdef WANT_SYS_POLLSELECT_SIGSET
/* POLL/SELECT Helper functions */
PRIVATE void KCALL
atomic_sigmask_begin(USER CHECKED sigset_t *mymask,
                     sigset_t *__restrict oldmask,
                     USER CHECKED sigset_t const *newmask) {
	memcpy(oldmask, mymask, sizeof(sigset_t));
	TRY {
		memcpy(mymask, &newmask, sizeof(sigset_t));
		if unlikely(sigismember(mymask, SIGKILL) ||
		            sigismember(mymask, SIGSTOP)) {
			sigdelset(mymask, SIGKILL);
			sigdelset(mymask, SIGSTOP);
			COMPILER_BARRIER();
			sigmask_check();
		}
	} EXCEPT {
		bool mandatory_were_masked;
		mandatory_were_masked = sigismember(mymask, SIGKILL) ||
		                        sigismember(mymask, SIGSTOP);
		memcpy(mymask, oldmask, sizeof(sigset_t));
		if (mandatory_were_masked)
			sigmask_check_after_except();
		RETHROW();
	}
}

PRIVATE void KCALL
atomic_sigmask_except(USER CHECKED sigset_t *mymask,
                      sigset_t const *__restrict oldmask) {
	memcpy(mymask, oldmask, sizeof(sigset_t));
	sigmask_check_after_except();
}

PRIVATE void KCALL
atomic_sigmask_return(USER CHECKED sigset_t *mymask,
                      sigset_t const *__restrict oldmask,
                      syscall_ulong_t syscall_result) {
	memcpy(mymask, oldmask, sizeof(sigset_t));
	sigmask_check_after_syscall(syscall_result);
}
#endif /* WANT_SYS_POLLSELECT_SIGSET */

#ifdef __ARCH_WANT_SYSCALL_EPOLL_PWAIT
#undef sigmask
DEFINE_SYSCALL6(ssize_t, epoll_pwait,
                fd_t, epfd, USER UNCHECKED struct epoll_event *, events,
                size_t, maxevents, syscall_slong_t, timeout,
                USER UNCHECKED sigset_t const *, sigmask, size_t, sigsetsize) {
	ssize_t result;
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	if (sigmask) {
		sigset_t oldmask;
		USER CHECKED sigset_t *mymask;
		mymask = sigmask_getwr();
		atomic_sigmask_begin(mymask, &oldmask, sigmask);
		TRY {
			result = sys_epoll_wait(epfd, events, maxevents, timeout);
		} EXCEPT {
			atomic_sigmask_except(mymask, &oldmask);
			RETHROW();
		}
		atomic_sigmask_return(mymask, &oldmask, result);
	} else {
		result = sys_epoll_wait(epfd, events, maxevents, timeout);
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_EPOLL_PWAIT */

#ifdef WANT_SYS_POLL_SIGSET
#undef sigmask
PRIVATE size_t KCALL
do_ppoll(USER CHECKED struct pollfd *fds,
         size_t nfds, struct timespec const *timeout,
         USER CHECKED sigset_t const *sigmask) {
	size_t result;
	if (sigmask) {
		sigset_t oldmask;
		USER CHECKED sigset_t *mymask;
		mymask = sigmask_getwr();
		atomic_sigmask_begin(mymask, &oldmask, sigmask);
		TRY {
			result = do_poll(fds, nfds, timeout);
		} EXCEPT {
			atomic_sigmask_except(mymask, &oldmask);
			RETHROW();
		}
		atomic_sigmask_return(mymask, &oldmask, result);
	} else {
		result = do_poll(fds, nfds, timeout);
	}
	return result;
}
#endif /* WANT_SYS_POLL_SIGSET */

#ifdef WANT_SYS_SELECT_SIGSET
PRIVATE size_t KCALL
do_pselect(size_t nfds,
           USER CHECKED fd_set *readfds,
           USER CHECKED fd_set *writefds,
           USER CHECKED fd_set *exceptfds,
           struct timespec const *timeout,
           USER CHECKED sigset_t const *sigmask) {
	size_t result;
	if (sigmask) {
		sigset_t oldmask;
		USER CHECKED sigset_t *mymask;
		mymask = sigmask_getwr();
		atomic_sigmask_begin(mymask, &oldmask, sigmask);
		TRY {
			result = do_select(nfds, readfds, writefds, exceptfds, timeout);
		} EXCEPT {
			atomic_sigmask_except(mymask, &oldmask);
			RETHROW();
		}
		atomic_sigmask_return(mymask, &oldmask, result);
	} else {
		result = do_select(nfds, readfds, writefds, exceptfds, timeout);
	}
	return result;
}
#endif /* WANT_SYS_SELECT_SIGSET */

#ifdef __ARCH_WANT_SYSCALL_POLL
DEFINE_SYSCALL3(ssize_t, poll,
                USER UNCHECKED struct pollfd *, fds,
                size_t, nfds, syscall_slong_t, timeout) {
	size_t result;
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (timeout < 0) {
		result = do_poll(fds, nfds, NULL);
	} else if (timeout == 0) {
		struct timespec zero = { 0, 0 };
		result = do_poll(fds, nfds, &zero);
	} else {
		struct timespec tmo = realtime();
		tmo.add_milliseconds((uintptr_t)timeout);
		result = do_poll(fds, nfds, &tmo);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_POLL */

#ifdef __ARCH_WANT_SYSCALL_PPOLL
DEFINE_SYSCALL5(ssize_t, ppoll,
                USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                USER UNCHECKED struct timespec32 const *, timeout_ts,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize) {
	size_t result;
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_readable_opt(sigmask, sizeof(sigset_t));
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		struct timespec tmo;
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout_ts->tv_sec;
		tmo.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_ppoll(fds, nfds, &tmo, sigmask);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PPOLL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PPOLL
DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll,
                       USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                       USER UNCHECKED struct compat_timespec32 const *, timeout_ts,
                       USER UNCHECKED compat_sigset_t const *, sigmask,
                size_t, sigsetsize) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	size_t result;
	if unlikely(sigsetsize != sizeof(compat_sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	compat_validate_readable_opt(sigmask, sizeof(compat_sigset_t));
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		struct timespec tmo;
		compat_validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout_ts->tv_sec;
		tmo.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_ppoll(fds, nfds, &tmo, sigmask);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL */

#if (defined(__ARCH_WANT_SYSCALL_PPOLL64) || \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64))
#ifdef __ARCH_WANT_SYSCALL_PPOLL64
DEFINE_SYSCALL5(ssize_t, ppoll64,
                USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                USER UNCHECKED struct timespec64 const *, timeout_ts,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize)
#else /* __ARCH_WANT_SYSCALL_PPOLL64 */
DEFINE_SYSCALL5(ssize_t, ppoll_time64,
                USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                USER UNCHECKED struct timespec64 const *, timeout_ts,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize)
#endif /* !__ARCH_WANT_SYSCALL_PPOLL64 */
{
	size_t result;
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_readable_opt(sigmask, sizeof(sigset_t));
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		struct timespec tmo;
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout_ts->tv_sec;
		tmo.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_ppoll(fds, nfds, &tmo, sigmask);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PPOLL64 || __ARCH_WANT_SYSCALL_PPOLL_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_PPOLL64
DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll64,
                       USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout_ts,
                       USER UNCHECKED compat_sigset_t const *, sigmask,
                       size_t, sigsetsize)
#else /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL64 */
DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll_time64,
                       USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout_ts,
                       USER UNCHECKED compat_sigset_t const *, sigmask,
                       size_t, sigsetsize)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_PPOLL64 */
{
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	size_t result;
	if unlikely(sigsetsize != sizeof(compat_sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	compat_validate_readable_opt(sigmask, sizeof(compat_sigset_t));
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		struct timespec tmo;
		compat_validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout_ts->tv_sec;
		tmo.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_ppoll(fds, nfds, &tmo, sigmask);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL64 || __ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64 */

#if (defined(__ARCH_WANT_SYSCALL_SELECT) || \
     defined(__ARCH_WANT_SYSCALL__NEWSELECT))
#ifdef __ARCH_WANT_SYSCALL__NEWSELECT
DEFINE_SYSCALL5(ssize_t, _newselect, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timeval32 *, timeout)
#else /* __ARCH_WANT_SYSCALL__NEWSELECT */
DEFINE_SYSCALL5(ssize_t, select, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timeval32 *, timeout)
#endif /* !__ARCH_WANT_SYSCALL__NEWSELECT */
{
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	if (timeout) {
		struct timespec tmo;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tmo);
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   &tmo);
	} else {
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   NULL);
	}
	return (ssize_t)result;
}

#if (defined(__ARCH_WANT_SYSCALL_SELECT) && \
     defined(__ARCH_WANT_SYSCALL__NEWSELECT))
DEFINE_SYSCALL1(ssize_t, select,
                USER UNCHECKED struct sel_arg_struct const *, arg) {
	validate_readable(arg, sizeof(*arg));
	return sys__newselect(ATOMIC_READ(arg->n),
	                      ATOMIC_READ(arg->inp),
	                      ATOMIC_READ(arg->outp),
	                      ATOMIC_READ(arg->exp),
	                      ATOMIC_READ(arg->tvp));
}
#endif /* __ARCH_WANT_SYSCALL_SELECT && __ARCH_WANT_SYSCALL__NEWSELECT */
#endif /* __ARCH_WANT_SYSCALL_SELECT || __ARCH_WANT_SYSCALL__NEWSELECT */

#if (defined(__ARCH_WANT_SYSCALL_SELECT64) || \
     defined(__ARCH_WANT_SYSCALL_SELECT_TIME64))
#ifdef __ARCH_WANT_SYSCALL_SELECT64
DEFINE_SYSCALL5(ssize_t, select64, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timeval64 *, timeout)
#else /* __ARCH_WANT_SYSCALL_SELECT64 */
DEFINE_SYSCALL5(ssize_t, select_time64, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timeval64 *, timeout)
#endif /* !__ARCH_WANT_SYSCALL_SELECT64 */
{
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	if (timeout) {
		struct timespec tmo;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tmo);
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   &tmo);
	} else {
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   NULL);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SELECT64 || __ARCH_WANT_SYSCALL_SELECT_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT))
PRIVATE ssize_t KCALL
compat_sys_select_impl(size_t nfds,
                       USER UNCHECKED fd_set *readfds,
                       USER UNCHECKED fd_set *writefds,
                       USER UNCHECKED fd_set *exceptfds,
                       USER UNCHECKED struct compat_timeval32 *timeout) {
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	if (timeout) {
		struct timespec tmo;
		compat_validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tmo);
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   &tmo);
	} else {
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   NULL);
	}
	return (ssize_t)result;
}

#ifdef __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT
DEFINE_COMPAT_SYSCALL5(ssize_t, _newselect, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timeval32 *, timeout)
#else /* __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */
DEFINE_COMPAT_SYSCALL5(ssize_t, select, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timeval32 *, timeout)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */
{
	return compat_sys_select_impl(nfds,
	                              readfds,
	                              writefds,
	                              exceptfds,
	                              timeout);
}

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) && \
     defined(__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT))
DEFINE_COMPAT_SYSCALL1(ssize_t, select,
                       USER UNCHECKED struct compat_sel_arg_struct const *, arg) {
	compat_ulongptr_t n;                     /* nfds argument */
	compat_ptr(fd_set) inp;                  /* Read fd-set */
	compat_ptr(fd_set) outp;                 /* Write fd-set */
	compat_ptr(fd_set) exp;                  /* Except fd-set */
	compat_ptr(struct compat_timeval32) tvp; /* Timeout argument */
	compat_validate_readable(arg, sizeof(*arg));
	COMPILER_READ_BARRIER();
	n    = arg->n;
	inp  = arg->inp;
	outp = arg->outp;
	exp  = arg->exp;
	tvp  = arg->tvp;
	COMPILER_READ_BARRIER();
	return compat_sys_select_impl(n, inp, outp, exp, tvp);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT && __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT || __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_SELECT64
DEFINE_COMPAT_SYSCALL5(ssize_t, select64, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timeval64 *, timeout)
#else /* __ARCH_WANT_COMPAT_SYSCALL_SELECT64 */
DEFINE_COMPAT_SYSCALL5(ssize_t, select_time64, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timeval64 *, timeout)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_SELECT64 */
{
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	if (timeout) {
		struct timespec tmo;
		compat_validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tmo);
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   &tmo);
	} else {
		result = do_select(nfds,
		                   readfds,
		                   writefds,
		                   exceptfds,
		                   NULL);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT64 */

#ifdef __ARCH_WANT_SYSCALL_PSELECT6
DEFINE_SYSCALL6(ssize_t, pselect6, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timespec32 const *, timeout,
                USER UNCHECKED void const *, sigmask_sigset_and_len) {
	struct sigset_and_len {
		sigset_t const *ss_ptr;
		size_t          ss_len;
	};
	size_t result, nfd_size;
	struct sigset_and_len ss;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	validate_readable_opt(ss.ss_ptr, sizeof(sigset_t));
	if (timeout) {
		struct timespec tmo;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout->tv_sec;
		tmo.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    &tmo,
		                    ss.ss_ptr);
	} else {
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    NULL,
		                    ss.ss_ptr);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PSELECT6 */

#if (defined(__ARCH_WANT_SYSCALL_PSELECT6_64) || \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64))
#ifdef __ARCH_WANT_SYSCALL_PSELECT6_64
DEFINE_SYSCALL6(ssize_t, pselect6_64, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timespec64 const *, timeout,
                USER UNCHECKED void const *, sigmask_sigset_and_len)
#else /* __ARCH_WANT_SYSCALL_PSELECT6_64 */
DEFINE_SYSCALL6(ssize_t, pselect6_time64, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timespec64 const *, timeout,
                USER UNCHECKED void const *, sigmask_sigset_and_len)
#endif /* !__ARCH_WANT_SYSCALL_PSELECT6_64 */
{
	struct sigset_and_len {
		sigset_t const *ss_ptr;
		size_t          ss_len;
	};
	size_t result, nfd_size;
	struct sigset_and_len ss;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	validate_readable_opt(ss.ss_ptr, sizeof(sigset_t));
	if (timeout) {
		struct timespec tmo;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout->tv_sec;
		tmo.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    &tmo,
		                    ss.ss_ptr);
	} else {
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    NULL,
		                    ss.ss_ptr);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PSELECT6_64 || __ARCH_WANT_SYSCALL_PSELECT6_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PSELECT6
DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timespec32 const *, timeout,
                       USER UNCHECKED void const *, sigmask_sigset_and_len) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	struct sigset_and_len {
		compat_sigset_t const *ss_ptr;
		compat_size_t          ss_len;
	};
	size_t result, nfd_size;
	struct sigset_and_len ss;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readable(sigmask_sigset_and_len, sizeof(ss));
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(compat_sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	compat_validate_readable_opt(ss.ss_ptr, sizeof(compat_sigset_t));
	if (timeout) {
		struct timespec tmo;
		compat_validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout->tv_sec;
		tmo.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    &tmo,
		                    ss.ss_ptr);
	} else {
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    NULL,
		                    ss.ss_ptr);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PSELECT6 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64
DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6_64, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout,
                       USER UNCHECKED void const *, sigmask_sigset_and_len)
#else /* __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64 */
DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6_time64, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout,
                       USER UNCHECKED void const *, sigmask_sigset_and_len)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64 */
{
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	struct sigset_and_len {
		compat_sigset_t const *ss_ptr;
		compat_size_t          ss_len;
	};
	size_t result, nfd_size;
	struct sigset_and_len ss;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readable(sigmask_sigset_and_len, sizeof(ss));
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(compat_sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	compat_validate_readable_opt(ss.ss_ptr, sizeof(compat_sigset_t));
	if (timeout) {
		struct timespec tmo;
		compat_validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tmo.tv_sec  = (time_t)timeout->tv_sec;
		tmo.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tmo.tv_sec || tmo.tv_nsec)
			tmo += realtime();
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    &tmo,
		                    ss.ss_ptr);
	} else {
		result = do_pselect(nfds,
		                    readfds,
		                    writefds,
		                    exceptfds,
		                    NULL,
		                    ss.ss_ptr);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64 || __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64 */





/************************************************************************/
/* pause()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PAUSE
DEFINE_SYSCALL0(errno_t, pause) {
	for (;;) {
		assert(!task_wasconnected());
		/* Wait forever (equivalent to `select(0, NULL, NULL, NULL, NULL)')
		 * NOTE: `task_waitfor()' calls `task_serve()', which may in turn throw
		 *       `E_INTERRUPT' when a signal gets delivered to our thread. */
		task_waitfor();
	}
	/* Can't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_PAUSE */





/************************************************************************/
/* kcmp()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KCMP
PRIVATE NONNULL((1)) void KCALL
kcmp_require_inspect_process(struct task *__restrict thread) {
	struct task *me = THIS_TASK;
	struct task *thread_parent;
	if (thread == me)
		return; /* Always allowed to inspect yourself */
	thread_parent = task_getprocessparentptr_of(thread);
	if (thread_parent == task_getprocess_of(me))
		return; /* Check if the caller's process is the parent of `thread' */
	require(CAP_SYS_PTRACE);
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct task *KCALL
kcmp_get_thread_from_pid(pid_t pid) {
	REF struct task *result;
	/* Lookup the thread in question */
	result = pidns_lookup_task(THIS_PIDNS, (upid_t)pid);
	TRY {
		/* Make sure that the caller is allowed to inspect `thread' */
		kcmp_require_inspect_process(result);
	} EXCEPT {
		decref_unlikely(result);
		RETHROW();
	}
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct handle_manager *KCALL
kcmp_get_handle_manager_from_pid(pid_t pid) {
	REF struct handle_manager *result;
	REF struct task *thread;
	/* Lookup the thread in question */
	thread = kcmp_get_thread_from_pid(pid);
	FINALLY_DECREF_UNLIKELY(thread);
	/* Retrieve the thread's handle manager. */
	result = task_gethandlemanager(thread);
	return result;
}

PRIVATE WUNUSED REF struct handle KCALL
kcmp_get_handle_from_pid(pid_t pid, unsigned int fd) {
	REF struct handle result;
	REF struct handle_manager *hman;
	hman = kcmp_get_handle_manager_from_pid(pid);
	FINALLY_DECREF_UNLIKELY(hman);
	/* XXX: Support for symbolic handles? */
	result = handle_lookupin(fd, hman);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct vm *KCALL
kcmp_get_vm_from_pid(pid_t pid) {
	REF struct vm *result;
	REF struct task *thread;
	/* Lookup the thread in question */
	thread = kcmp_get_thread_from_pid(pid);
	FINALLY_DECREF_UNLIKELY(thread);
	/* Retrieve the thread's vm. */
	result = task_getvm(thread);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct fs *KCALL
kcmp_get_fs_from_pid(pid_t pid) {
	REF struct fs *result;
	REF struct task *thread;
	/* Lookup the thread in question */
	thread = kcmp_get_thread_from_pid(pid);
	FINALLY_DECREF_UNLIKELY(thread);
	/* Retrieve the thread's filesystem controller. */
	result = task_getfs(thread);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED REF struct sighand_ptr *KCALL
kcmp_get_sighand_ptr_from_pid(pid_t pid) {
	REF struct sighand_ptr *result;
	REF struct task *thread;
	/* Lookup the thread in question */
	thread = kcmp_get_thread_from_pid(pid);
	FINALLY_DECREF_UNLIKELY(thread);
	/* Retrieve the thread's filesystem controller. */
	result = task_getsighand_ptr(thread);
	return result;
}

#define KCMP_ORDER_EQUAL    0 /* type(pid1:idx1) == type(pid2:idx2) */
#define KCMP_ORDER_LESS     1 /* type(pid1:idx1) <  type(pid2:idx2) */
#define KCMP_ORDER_MORE     2 /* type(pid1:idx1) >  type(pid2:idx2) */
#define KCMP_ORDER_NOTEQUAL 3 /* type(pid1:idx1) != type(pid2:idx2) */

PRIVATE NOBLOCK syscall_slong_t
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
		hand1 = kcmp_get_handle_from_pid(pid1, (unsigned int)idx1);
		TRY {
			hand2  = kcmp_get_handle_from_pid(pid2, (unsigned int)idx2);
			result = kcmp_pointer(hand1.h_data, hand2.h_data);
			decref_unlikely(hand2);
		} EXCEPT {
			decref_unlikely(hand1);
			RETHROW();
		}
		decref_unlikely(hand1);
	}	break;

	case KCMP_VM: {
		REF struct vm *vm1;
		REF struct vm *vm2;
		vm1 = kcmp_get_vm_from_pid(pid1);
		FINALLY_DECREF_UNLIKELY(vm1);
		vm2 = kcmp_get_vm_from_pid(pid2);
		FINALLY_DECREF_UNLIKELY(vm2);
		result = kcmp_pointer(vm1, vm2);
	}	break;

	case KCMP_FILES: {
		REF struct handle_manager *hman1;
		REF struct handle_manager *hman2;
		hman1 = kcmp_get_handle_manager_from_pid(pid1);
		FINALLY_DECREF_UNLIKELY(hman1);
		hman2 = kcmp_get_handle_manager_from_pid(pid2);
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
		result = kcmp_pointer(hand1 ? ATOMIC_READ(hand1->sp_hand) : NULL,
		                      hand2 ? ATOMIC_READ(hand2->sp_hand) : NULL);
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

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C */
