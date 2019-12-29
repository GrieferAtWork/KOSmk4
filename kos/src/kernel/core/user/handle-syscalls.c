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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C
#define GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C 1
#define _GNU_SOURCE 1 /* TIMEVAL_TO_TIMESPEC */
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <fs/file.h>
#include <fs/node.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <bits/iovec-struct.h> /* struct iovec */
#include <kos/except-fs.h>
#include <kos/except-inval.h>
#include <kos/hop.h>
#include <kos/io.h>
#include <linux/fs.h> /* General purpose ioctl()s */
#include <sys/mount.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <sys/time.h> /* TIMEVAL_TO_TIMESPEC */
#include <sys/uio.h>

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <malloca.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/iovec-struct.h>
#include <compat/bits/timespec.h>
#include <compat/bits/timeval.h>
#include <compat/kos/types.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

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
			if (d->e_pointers[0] == (__UINTPTR_TYPE__)-1)
				d->e_pointers[0] = (__UINTPTR_TYPE__)(__INTPTR_TYPE__)oldfd;
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
		if (!PERTASK_GET(this_exception_pointers[0])) /* fd */
			PERTASK_SET(this_exception_pointers[0], (uintptr_t)fd);
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
	case _IOW(_IOC_TYPE(FIONBIO), _IOC_NR(FIONBIO), int):
		/* Set/clear IO_NONBLOCK */
		validate_readable(arg, sizeof(int));
		handle_stflags(THIS_HANDLE_MANAGER,
		               fd,
		               ~IO_NONBLOCK,
		               ATOMIC_READ(*(int *)arg) ? IO_NONBLOCK : 0);
		break;

	case FIOASYNC:
	case _IOW(_IOC_TYPE(FIOASYNC), _IOC_NR(FIOASYNC), int): {
		/* Set/clear IO_ASYNC */
		int mode;
		validate_readable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		mode = *(USER CHECKED int *)arg;
		COMPILER_READ_BARRIER();
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
			switch (_IOC_NR(command)) {
			case _IOC_NR(TCGETS) ... _IOC_NR(TIOCPKT):
			case _IOC_NR(TIOCNOTTY) ... _IOC_NR(TIOCGEXCL):
			case _IOC_NR(TIOCSERCONFIG) ... _IOC_NR(TIOCGICOUNT):
				/* TTY-specific ioctl()s (user-space uses one of these to implement `isatty()') */
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
		    PERTASK_GET(this_exception_pointers[0]) == E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND) {
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
		    PERTASK_GET(this_exception_pointers[0]) == E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND) {
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
		if (!IO_CANWRITE(hand.h_mode))
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
		if (!IO_CANWRITE(hand.h_mode))
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
	retpos  = (uint64_t)sys_lseek64(fd, offset, whence);
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
		if (!IO_CANREAD(hand.h_mode))
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
		if (!IO_CANWRITE(hand.h_mode))
			THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
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
		if (!IO_CANREAD(hand.h_mode))
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
		if (!IO_CANWRITE(hand.h_mode))
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
		if (!IO_CANREAD(hand.h_mode))
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
		if (!IO_CANWRITE(hand.h_mode))
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
		if (!IO_CANREAD(hand.h_mode))
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
		if (!IO_CANWRITE(hand.h_mode))
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
		if (!IO_CANREAD(hand.h_mode))
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
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = ATOMIC_READ(iov[i].iov_base);
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
		if (!IO_CANWRITE(hand.h_mode))
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
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = ATOMIC_READ(iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					validate_writable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
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
		if (!IO_CANREAD(hand.h_mode))
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
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
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
		if (!IO_CANWRITE(hand.h_mode))
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
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base = (void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
					((struct aio_buffer_entry *)dst.ab_entv)[i].ab_size = ATOMIC_READ(iov[i].iov_len);
					compat_validate_writable(((struct aio_buffer_entry *)dst.ab_entv)[i].ab_base,
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

#define MANGLE_HANDLE_DATA_POINTER(p) \
	(u64)(uintptr_t)(p) /* TODO: Option to mangle kernel-space pointers! */

	case HOP_HANDLE_STAT: {
		struct hop_handle_stat st;
		char const *name;
		memset(&st, 0, sizeof(st));
		st.hs_struct_size = sizeof(st);
		st.hs_mode        = hand->h_mode;
		st.hs_type        = hand->h_type;
		st.hs_kind        = handle_typekind(hand);
		st.hs_refcnt      = (*handle_type_db.h_refcnt[hand->h_type])(hand->h_data);
		st.hs_address     = MANGLE_HANDLE_DATA_POINTER(hand->h_data);
		name              = handle_type_db.h_typename[hand->h_type];
		memcpy(st.hs_typename, name,
		       strnlen(name, COMPILER_LENOF(st.hs_typename) - 1),
		       sizeof(char));
		COMPILER_BARRIER();
		{
			struct hop_handle_stat *info;
			size_t info_size;
			info = (struct hop_handle_stat *)arg;
			validate_writable(info, sizeof(struct hop_handle_stat));
			info_size = ATOMIC_READ(info->hs_struct_size);
			if (info_size != sizeof(struct hop_handle_stat))
				THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_handle_stat), info_size);
			memcpy(info, &st, sizeof(struct hop_handle_stat));
		}
	}	break;

	case HOP_HANDLE_REOPEN:
		return handle_installhop((struct hop_openfd *)arg, *hand);
		break;

	case HOP_HANDLE_NOOP:
		break;

	case HOP_HANDLE_GETREFCNT:
		validate_writable(arg, sizeof(uintptr_t));
		*(uintptr_t *)arg = handle_refcnt(*hand);
		break;

	case HOP_HANDLE_GETADDRESS:
		validate_writable(arg, sizeof(u64));
		*(USER u64 *)arg = MANGLE_HANDLE_DATA_POINTER(hand->h_data);
		break;

	case HOP_HANDLE_GETTYPE:
		validate_writable(arg, sizeof(uint16_t));
		*(USER uint16_t *)arg = (uint16_t)hand->h_type;
		break;

	case HOP_HANDLE_GETKIND:
		validate_writable(arg, sizeof(uint16_t));
		*(USER uint16_t *)arg = (uint16_t)handle_typekind(hand);
		break;

	case HOP_HANDLE_GETMODE:
		validate_writable(arg, sizeof(uint16_t));
		*(USER uint16_t *)arg = (uint16_t)hand->h_mode;
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
		if (!PERTASK_GET(this_exception_pointers[0])) /* fd */
			PERTASK_SET(this_exception_pointers[0], (uintptr_t)fd);
		if (!PERTASK_GET(this_exception_pointers[2])) /* actual_handle_type */
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)hand->h_type);
		if (!PERTASK_GET(this_exception_pointers[4])) /* actual_handle_kind */
			PERTASK_SET(this_exception_pointers[4], (uintptr_t)handle_typekind(hand));
		break;
	case ERROR_CODEOF(E_INVALID_ARGUMENT_UNKNOWN_COMMAND):
		if (PERTASK_GET(this_exception_pointers[0]) != E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND)
			break;
		if ((hop_command >> 16) == HANDLE_TYPE_UNDEFINED ||
		    (hop_command >> 16) >= HANDLE_TYPE_COUNT)
			break;
		/* If the command does actually exist, but simply cannot be applied to the
		 * associated handle type, translate the exception to `E_INVALID_HANDLE_FILETYPE',
		 * with the required file type set there. */
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_INVALID_HANDLE_FILETYPE));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)fd);
		PERTASK_SET(this_exception_pointers[1], (uintptr_t)(hop_command >> 16)); /* HOP Commands encode the required type like this */
		PERTASK_SET(this_exception_pointers[2], (uintptr_t)hand->h_type);
		PERTASK_SET(this_exception_pointers[4], (uintptr_t)handle_typekind(hand));
		PERTASK_SET(this_exception_pointers[3], (uintptr_t)HANDLE_TYPEKIND_GENERIC); /* XXX: Not necessarily correct... */
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
			result = (*handle_type_db.h_hop[hand.h_type])(hand.h_data,
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
		if (!IO_CANREAD(hand.h_mode))
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
		if (!IO_CANREAD(hand.h_mode))
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
/* select(), select64(), pselect6(), pselect6_64()                      */
/************************************************************************/
#undef WANT_SYS_POLL
#if (defined(__ARCH_WANT_SYSCALL_POLL) ||         \
     defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL64) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL64))
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
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||           \
     defined(__ARCH_WANT_SYSCALL_PPOLL64) ||         \
     defined(__ARCH_WANT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_64) ||     \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL64) ||  \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64))
#define WANT_SYS_POLLSELECT_SIGSET 1
#endif /* p(poll|select)... */
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL64) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL64))
#define WANT_SYS_POLL_SIGSET 1
#endif /* ppoll... */
#if (defined(__ARCH_WANT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_64) ||     \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64))
#define WANT_SYS_SELECT_SIGSET 1
#endif /* pselect... */

#if defined(WANT_SYS_POLL) || defined(WANT_SYS_SELECT)
PRIVATE poll_mode_t KCALL do_poll_handle(struct handle &hnd,
                                         poll_mode_t what) {
	poll_mode_t result;
	/* Verify that the caller has access to the
	 * indicated data channel of the handle. */
	if (what & POLLIN) {
		if (!IO_CANREAD(hnd.h_mode))
			return POLLERR;
	}
	if (what & POLLOUT) {
		if (!IO_CANWRITE(hnd.h_mode))
			return POLLERR;
	}
	TRY {
		result = handle_poll(hnd, what);
	} EXCEPT {
		if (was_thrown(E_FSERROR_UNSUPPORTED_OPERATION) &&
		    error_data()->e_pointers[0] == E_FILESYSTEM_OPERATION_POLL)
			result = POLLHUP; /* Poll is unsupported. */
		else {
			/* XXX: Are there exceptions that should yield POLLERR? */
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
        size_t nfds, qtime_t const *timeout) {
	size_t i, result = 0;
again:
	assert(!task_isconnected());
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
			if unlikely(pfd.events & ~(POLLIN | POLLPRI | POLLOUT)) {
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
			if (what & (POLLIN | POLLPRI | POLLOUT))
				++result; /* Got something! */
			fds[i].revents = what;
		} EXCEPT {
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
          qtime_t const *timeout) {
	typedef u8 fds_word_t;
	enum { BITS_PER_FDS_WORD = 8 };
	size_t nfds_words, i, result = 0;
again:
	assert(!task_isconnected());
	nfds_words = CEILDIV(nfds, BITS_PER_FDS_WORD);
	for (i = 0; i < nfds_words; ++i) {
		fds_word_t rbits, wbits, ebits, mask;
		fds_word_t new_rbits, new_wbits, new_ebits;
		unsigned int j, maxbits = BITS_PER_FDS_WORD;
		if (i == nfds_words - 1)
			maxbits = nfds % BITS_PER_FDS_WORD;
		rbits = wbits = ebits = 0;
		if (readfds)   rbits = ((fds_word_t *)readfds)[i];
		if (writefds)  wbits = ((fds_word_t *)writefds)[i];
		if (exceptfds) ebits = ((fds_word_t *)exceptfds)[i];
		if (!(rbits | wbits | ebits))
			continue;
		new_rbits = new_wbits = new_ebits = 0;
		for (j = 0, mask = 1; j < maxbits; ++j, mask <<= 1) {
			poll_mode_t what, mode;
			struct handle hnd;
			mode = 0;
			if (rbits & mask) mode |= POLLIN;
			if (wbits & mask) mode |= POLLOUT;
			if (ebits & mask) mode |= POLLPRI;
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
				decref(hnd);
				RETHROW();
			}
			assert(!(what & POLLIN) || (mode & POLLIN));
			assert(!(what & POLLOUT) || (mode & POLLOUT));
			assert(!(what & POLLPRI) || (mode & POLLPRI));
			decref(hnd);
			if (!(what & (POLLIN | POLLOUT | POLLPRI)))
				continue;
			if (!result) {
				/* Clear all fd_set bits leading words. */
				if (readfds)   memset(readfds, 0, i * sizeof(fds_word_t));
				if (writefds)  memset(writefds, 0, i * sizeof(fds_word_t));
				if (exceptfds) memset(exceptfds, 0, i * sizeof(fds_word_t));
			}
			++result;
			if (what & POLLIN)
				new_rbits |= mask;
			if (what & POLLOUT)
				new_wbits |= mask;
			if (what & POLLPRI)
				new_ebits |= mask;
		}
		if (result) {
			/* Update the fd-set words of  */
			if (readfds)   ((fds_word_t *)readfds)[i] = new_rbits;
			if (writefds)  ((fds_word_t *)writefds)[i] = new_wbits;
			if (exceptfds) ((fds_word_t *)exceptfds)[i] = new_ebits;
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
atomic_sigmask_begin(struct kernel_sigmask *__restrict mymask,
                     sigset_t *__restrict oldmask,
                     USER CHECKED sigset_t const *newmask) {
	memcpy(oldmask, &mymask->sm_mask, sizeof(sigset_t));
	TRY {
		memcpy(&mymask->sm_mask, &newmask, sizeof(sigset_t));
		if unlikely(sigismember(&mymask->sm_mask, SIGKILL) ||
		            sigismember(&mymask->sm_mask, SIGSTOP)) {
			sigdelset(&mymask->sm_mask, SIGKILL);
			sigdelset(&mymask->sm_mask, SIGSTOP);
			COMPILER_BARRIER();
			sigmask_check();
		}
	} EXCEPT {
		bool mandatory_were_masked;
		mandatory_were_masked = sigismember(&mymask->sm_mask, SIGKILL) ||
		                        sigismember(&mymask->sm_mask, SIGSTOP);
		memcpy(&mymask->sm_mask, oldmask, sizeof(sigset_t));
		if (mandatory_were_masked)
			sigmask_check_after_except();
		RETHROW();
	}
}

PRIVATE void KCALL
atomic_sigmask_except(struct kernel_sigmask *__restrict mymask,
                      sigset_t const *__restrict oldmask) {
	memcpy(&mymask->sm_mask, oldmask, sizeof(sigset_t));
	sigmask_check_after_except();
}

PRIVATE void KCALL
atomic_sigmask_return(struct kernel_sigmask *__restrict mymask,
                      sigset_t const *__restrict oldmask,
                      syscall_ulong_t syscall_result) {
	memcpy(&mymask->sm_mask, oldmask, sizeof(sigset_t));
	sigmask_check_after_syscall(syscall_result);
}
#endif /* WANT_SYS_POLLSELECT_SIGSET */

#ifdef WANT_SYS_POLL_SIGSET
#undef sigmask
PRIVATE size_t KCALL
do_ppoll(USER CHECKED struct pollfd *fds,
         size_t nfds, qtime_t const *timeout,
         USER CHECKED sigset_t const *sigmask) {
	size_t result;
	if (sigmask) {
		sigset_t oldmask;
		struct kernel_sigmask *mymask;
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
           qtime_t const *timeout,
           USER CHECKED sigset_t const *sigmask) {
	size_t result;
	if (sigmask) {
		sigset_t oldmask;
		struct kernel_sigmask *mymask;
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
	validate_writablem(fds, nfds, sizeof(struct pollfd));
	if (timeout < 0) {
		result = do_poll(fds, nfds, NULL);
	} else if (timeout == 0) {
		qtime_t zero = { 0, 0 };
		result = do_poll(fds, nfds, &zero);
	} else {
		qtime_t tmo = quantum_time();
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
	validate_writablem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout_ts->tv_sec;
		tms.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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
	validate_readable_opt(sigmask, sizeof(compat_sigset_t));
	validate_writablem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout_ts->tv_sec;
		tms.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
		result = do_ppoll(fds, nfds, &tmo, sigmask);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL */

#ifdef __ARCH_WANT_SYSCALL_PPOLL64
DEFINE_SYSCALL5(ssize_t, ppoll64,
                USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                USER UNCHECKED struct timespec64 const *, timeout_ts,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize) {
	size_t result;
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_readable_opt(sigmask, sizeof(sigset_t));
	validate_writablem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout_ts->tv_sec;
		tms.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
		result = do_ppoll(fds, nfds, &tmo, sigmask);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PPOLL64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PPOLL64
DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll64,
                       USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout_ts,
                       USER UNCHECKED compat_sigset_t const *, sigmask,
                size_t, sigsetsize) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	size_t result;
	if unlikely(sigsetsize != sizeof(compat_sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_readable_opt(sigmask, sizeof(compat_sigset_t));
	validate_writablem(fds, nfds, sizeof(struct pollfd));
	if (!timeout_ts) {
		result = do_ppoll(fds, nfds, NULL, sigmask);
	} else {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout_ts->tv_sec;
		tms.tv_nsec = timeout_ts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
		result = do_ppoll(fds, nfds, &tmo, sigmask);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL64 */

#ifdef __ARCH_WANT_SYSCALL_SELECT
DEFINE_SYSCALL5(ssize_t, select, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timeval32 *, timeout) {
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tms);
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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
#endif /* __ARCH_WANT_SYSCALL_SELECT */

#ifdef __ARCH_WANT_SYSCALL_SELECT64
DEFINE_SYSCALL5(ssize_t, select64, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timeval64 *, timeout) {
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tms);
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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
#endif /* __ARCH_WANT_SYSCALL_SELECT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SELECT
DEFINE_COMPAT_SYSCALL5(ssize_t, select, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timeval32 *, timeout) {
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tms);
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SELECT64
DEFINE_COMPAT_SYSCALL5(ssize_t, select64, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timeval64 *, timeout) {
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		TIMEVAL_TO_TIMESPEC(timeout, &tms);
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	validate_readable_opt(ss.ss_ptr, sizeof(sigset_t));
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout->tv_sec;
		tms.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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

#ifdef __ARCH_WANT_SYSCALL_PSELECT6_64
DEFINE_SYSCALL6(ssize_t, pselect6_64, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timespec64 const *, timeout,
                USER UNCHECKED void const *, sigmask_sigset_and_len) {
	struct sigset_and_len {
		sigset_t const *ss_ptr;
		size_t          ss_len;
	};
	size_t result, nfd_size;
	struct sigset_and_len ss;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	validate_readable_opt(ss.ss_ptr, sizeof(sigset_t));
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout->tv_sec;
		tms.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(compat_sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	validate_readable_opt(ss.ss_ptr, sizeof(compat_sigset_t));
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout->tv_sec;
		tms.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_64
DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6_64, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout,
                       USER UNCHECKED void const *, sigmask_sigset_and_len) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	struct sigset_and_len {
		compat_sigset_t const *ss_ptr;
		compat_size_t          ss_len;
	};
	size_t result, nfd_size;
	struct sigset_and_len ss;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	validate_writable_opt(readfds, nfd_size);
	validate_writable_opt(writefds, nfd_size);
	validate_writable_opt(exceptfds, nfd_size);
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if unlikely(ss.ss_len != sizeof(compat_sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      ss.ss_len);
	validate_readable_opt(ss.ss_ptr, sizeof(compat_sigset_t));
	if (timeout) {
		qtime_t tmo;
		struct timespec tms;
		validate_readable(timeout, sizeof(*timeout));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)timeout->tv_sec;
		tms.tv_nsec = timeout->tv_nsec;
		COMPILER_READ_BARRIER();
		if (!tms.tv_sec && !tms.tv_nsec) {
			tmo.q_jtime = 0;
			tmo.q_qtime = 0;
			tmo.q_qsize = 1;
		} else {
			tmo = quantum_time() + timespec_to_qtime(&tms);
		}
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


DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C */
