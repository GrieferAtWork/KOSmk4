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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C
#define GUARD_KERNEL_SRC_USER_HANDLE_SYSCALLS_C 1
#define _GNU_SOURCE 1 /* TIMEVAL_TO_TIMESPEC */
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/fs/fs.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <kernel/mman.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rt/except-handler.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <bits/os/iovec.h> /* struct iovec */
#include <compat/config.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/ioctl/fd.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
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
#include <format-printer.h>
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

#undef sigmask

DECL_BEGIN

/************************************************************************/
/* dup(), dup2(), dup3()                                                */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_DUP
DEFINE_SYSCALL1(fd_t, dup, fd_t, fd) {
	unsigned int result;
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
	hand.h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
	RAII_FINALLY { decref_unlikely(hand); };
	result = handle_install(THIS_HANDLE_MANAGER, hand);
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
			struct exception_data *d = except_data();
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
	RAII_FINALLY { decref_unlikely(hand); };
	handle_installinto_sym((unsigned int)newfd, hand);
	return newfd;
}
#endif /* __ARCH_WANT_SYSCALL_DUP3 */





/************************************************************************/
/* fcntl()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FCNTL
DEFINE_SYSCALL3(syscall_slong_t, fcntl, fd_t, fd,
                fcntl_t, command, UNCHECKED USER void *, arg) {
	return handle_fcntl(THIS_HANDLE_MANAGER, fd, command, arg);
}
#endif /* __ARCH_WANT_SYSCALL_FCNTL */





/************************************************************************/
/* ioctl(), ioctlf()                                                    */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_IOCTL) || defined(__ARCH_WANT_SYSCALL_IOCTLF)
PRIVATE NOBLOCK void
NOTHROW(KCALL ioctl_complete_exception_info)(unsigned int fd) {
	except_code_t code = except_code();
	switch (code) {

	case EXCEPT_CODEOF(E_INVALID_HANDLE_OPERATION):
		if (!PERTASK_TEST(this_exception_args.e_invalid_handle.ih_fd)) /* fd */
			PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, fd);
		break;

	default: break;
	}
}

PRIVATE WUNUSED NONNULL((3, 5)) bool KCALL
ioctl_generic(ioctl_t cmd,
              unsigned int fd,
              struct handle const *__restrict hand,
              USER UNCHECKED void *arg,
              syscall_slong_t *__restrict result) {
	/* Check for specific commands. */
	switch (cmd) {

	case FIOCLEX: /* FD_IOC_CLEX */
		/* Set IO_CLOEXEC */
		if (hand->h_mode & IO_CLOEXEC)
			break;
		handle_chflags(THIS_HANDLE_MANAGER, fd, ~0, IO_CLOEXEC);
		break;

	case FIONCLEX: /* FD_IOC_NCLEX */
		/* Clear IO_CLOEXEC */
		if (!(hand->h_mode & IO_CLOEXEC))
			break;
		handle_chflags(THIS_HANDLE_MANAGER, fd, ~IO_CLOEXEC, 0);
		break;

	case FD_IOC_DUPFD:
		*result = handle_installopenfd((USER UNCHECKED struct openfd *)arg, hand);
		goto done;

	case FD_IOC_NOOP:
		/* Intentional no-op */
		break;

	case FD_IOC_CAST: {
		struct handle newhand;
		USER CHECKED struct fdcast *cast;
		uintptr_half_t reqtype;
		validate_readwrite(arg, sizeof(*cast));
		cast = (USER CHECKED struct fdcast *)arg;
		COMPILER_READ_BARRIER();
		reqtype = cast->fc_rqtyp;
		COMPILER_READ_BARRIER();
		newhand = *hand;
		if (reqtype == hand->h_type) {
			handle_incref(newhand);
		} else {
			if unlikely(reqtype >= HANDLE_TYPE_COUNT) {
err_bad_handle_type:
				THROW(E_INVALID_HANDLE_FILETYPE,
				      /* fd:                 */ fd, /* Filled in the caller */
				      /* needed_handle_type: */ reqtype,
				      /* actual_handle_type: */ hand->h_type,
				      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
				      /* actual_handle_kind: */ handle_typekind(hand));
			}

			/* Do the requested cast. */
			newhand.h_data = _handle_tryas(newhand, reqtype);
			if unlikely(!newhand.h_data)
				goto err_bad_handle_type;
			newhand.h_type = reqtype;
		}
		RAII_FINALLY { handle_decref(newhand); };

		/* Install the new handle. */
		*result = handle_installopenfd(&cast->fc_resfd, newhand);
		goto done;
	}	break;

	case FD_IOC_DESC: {
		size_t reqlen;
		struct fddesc desc;
		struct format_snprintf_data pdat;

		/* Load arguments. */
		validate_readwrite(arg, sizeof(desc));
		memcpy(&desc, arg, sizeof(desc));
		COMPILER_READ_BARRIER();

		/* Setup an snprintf-style printer */
		pdat.sd_buffer = desc.fdc_buf;
		pdat.sd_bufsiz = (size_t)desc.fdc_len;
		validate_writable(pdat.sd_buffer, pdat.sd_bufsiz);

		/* Print the link's text. */
		reqlen = handle_printlink(*hand, &format_snprintf_printer, &pdat);
		COMPILER_WRITE_BARRIER();

		/* Write-back the required buffer size */
		((USER CHECKED struct fddesc *)arg)->fdc_len = reqlen;
		goto done;
	}	break;


#if !defined(NDEBUG) && !defined(NDEBUG_HANDLE_REFCNT)
		/* Debug commands for direct reference control.
		 *
		 * You should never need these, and the only reason
		 * they  are here, is in case they might one day be
		 * useful for the purpose of debugging.
		 *
		 * The logic behind requiring `CAP_SYS_MODULE' is
		 * that there would be no point in keeping a user
		 * from directly modifying the reference counters
		 * of handles, so-long as that user would already
		 * be  able to just load a hacked driver to do it
		 * for them! */
	case _FD_IOC_INCREF:
		require(CAP_SYS_MODULE);
		kernel_poison(_KERNEL_POISON_NO_WARRANTY);
		handle_incref(*hand);
		break;

	case _FD_IOC_DECREF:
		require(CAP_SYS_MODULE);
		kernel_poison(_KERNEL_POISON_NO_WARRANTY);
		handle_decref(*hand);
		break;
#endif /* !NDEBUG && !NDEBUG_HANDLE_REFCNT */

	default:
		/* Commands for which we accept any size value. */
		switch (_IO_WITHSIZE(cmd, 0)) {

		case _IO_WITHSIZE(FIONBIO, 0): /* FD_IOC_NBIO */
			/* Set/clear IO_NONBLOCK */
			handle_chflags(THIS_HANDLE_MANAGER, fd, ~IO_NONBLOCK,
			               ioctl_intarg_getbool(cmd, arg) ? IO_NONBLOCK : 0);
			break;

		case _IO_WITHSIZE(FIOASYNC, 0): /* FD_IOC_ASYNC */
			/* Set/clear IO_ASYNC */
			handle_chflags(THIS_HANDLE_MANAGER, fd, ~IO_ASYNC,
			               ioctl_intarg_getbool(cmd, arg) ? IO_ASYNC : 0);
			break;

		case _IO_WITHSIZE(FIOQSIZE, 0): { /* FD_IOC_QSIZE */
			pos_t value;
			if (_IOC_SIZE(cmd) == 0)
				cmd = _IO_WITHSIZE(cmd, sizeof(loff_t));
			if unlikely(!handle_datasize(hand, &value))
				goto return_ENOTTY;
			*result = ioctl_intarg_setu64(cmd, arg, (u64)value);
			goto done;
		}	break;

		case _IO_WITHSIZE(FIGETBSZ, 0): { /* FD_IOC_GETBSZ */
			struct stat st;
			handle_stat(*hand, &st);
			*result = ioctl_intarg_setuint(cmd, arg, st.st_blksize);
			goto done;
		}	break;


		case _IO_WITHSIZE(FD_IOC_GETTYPE, 0):
			*result = ioctl_intarg_setu32(cmd, arg, hand->h_type);
			goto done;

		case _IO_WITHSIZE(FD_IOC_GETKIND, 0):
			*result = ioctl_intarg_setu32(cmd, arg, handle_typekind(hand));
			goto done;

		case _IO_WITHSIZE(FD_IOC_GETMODE, 0):
			*result = ioctl_intarg_setu32(cmd, arg, hand->h_mode);
			goto done;

		case _IO_WITHSIZE(FD_IOC_GETADDR, 0):
			*result = ioctl_intarg_setu64(cmd, arg, (uint64_t)(uintptr_t)skew_kernel_pointer(hand->h_data));
			goto done;

		case _IO_WITHSIZE(FD_IOC_GETRADDR, 0):
			require(CAP_SYS_MODULE);
			*result = ioctl_intarg_setu64(cmd, arg, (uint64_t)(uintptr_t)hand->h_data);
			goto done;

		case _IO_WITHSIZE(FD_IOC_GETREFCNT, 0):
			*result = ioctl_intarg_setu64(cmd, arg, (uint64_t)handle_refcnt(*hand));
			goto done;

		case _IO_WITHSIZE(FD_IOC_POLLTEST, 0): {
			poll_mode_t what;
			what    = (poll_mode_t)ioctl_intarg_getu32(cmd, arg);
			what    = handle_polltest(*hand, what);
			*result = ioctl_intarg_setu32(cmd, arg, (uint32_t)what);
			goto done;
		}	break;

		default:
			if (_IOC_TYPE(cmd) == 'T') {
				/* Return -ENOTTY for unsupported tty-ioctls */
return_ENOTTY:
				*result = -ENOTTY;
				return true;
			}
			return false;
		}
		break;
	}
	*result = 0;
done:
	return true;
}
#endif /* __ARCH_WANT_SYSCALL_IOCTL || __ARCH_WANT_SYSCALL_IOCTLF */

#ifdef __ARCH_WANT_SYSCALL_IOCTL
DEFINE_SYSCALL3(syscall_slong_t, ioctl, fd_t, fd,
                ioctl_t, command, UNCHECKED USER void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	TRY {
		result = handle_ioctl(hand, command, arg);
	} EXCEPT {
		if (was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) &&
		    PERTASK_EQ(this_exception_args.e_invalid_argument.ia_context,
		               E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND)) {
			NESTED_TRY {
				if (ioctl_generic(command, fd, &hand, arg, &result))
					goto done;
			} EXCEPT {
				ioctl_complete_exception_info((unsigned int)fd);
				RETHROW();
			}
		}
		ioctl_complete_exception_info((unsigned int)fd);
		RETHROW();
	}
done:
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_IOCTL */

#ifdef __ARCH_WANT_SYSCALL_IOCTLF
DEFINE_SYSCALL4(syscall_slong_t, ioctlf, fd_t, fd,
                ioctl_t, command, iomode_t, mode,
                USER UNCHECKED void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE);
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	TRY {
		result = handle_ioctlf(hand, command, arg, mode);
	} EXCEPT {
		if (was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) &&
		    PERTASK_EQ(this_exception_args.e_invalid_argument.ia_context,
		               E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND)) {
			NESTED_TRY {
				if (ioctl_generic(command, fd, &hand, arg, &result))
					goto done;
			} EXCEPT {
				ioctl_complete_exception_info((unsigned int)fd);
				RETHROW();
			}
		}
		ioctl_complete_exception_info((unsigned int)fd);
		RETHROW();
	}
done:
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
	hand = handle_lookup((unsigned int)fd);
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
	hand = handle_lookup((unsigned int)fd);
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
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	handle_allocate(hand, mode, (pos_t)offset, (pos_t)length);
	return -EOK;
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
	RAII_FINALLY { decref_unlikely(hand); };
	result = handle_seek(hand, (off_t)offset, whence);
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
	RAII_FINALLY { decref_unlikely(hand); };
	result = handle_seek(hand, (off_t)offset, whence);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	result = handle_read(hand, buf, bufsize);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	result = handle_write(hand, buf, bufsize);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	result = handle_readf(hand, buf, bufsize,
	                      (hand.h_mode & ~IO_USERF_MASK) | mode);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	result = handle_writef(hand, buf, bufsize,
	                       (hand.h_mode & ~IO_USERF_MASK) | mode);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	result = handle_pread(hand, buf, bufsize, (pos_t)offset);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	result = handle_pwrite(hand, buf, bufsize, (pos_t)offset);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	result = handle_preadf(hand, buf, bufsize, (pos_t)offset,
	                       (hand.h_mode & ~IO_USERF_MASK) | mode);
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
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	result = handle_pwritef(hand, buf, bufsize, (pos_t)offset,
	                        (hand.h_mode & ~IO_USERF_MASK) | mode);
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
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_readv(hand, &dst, num_bytes);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_SYSCALL_PWRITEV
DEFINE_SYSCALL3(ssize_t, writev, fd_t, fd,
                USER UNCHECKED struct iovec const *, iov,
                size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_writev(hand, &dst, num_bytes);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITEV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PREADV
DEFINE_COMPAT_SYSCALL3(ssize_t, readv, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count)
		result = 0;
	else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t const *)&iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			compat_validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_readv(hand, &dst, num_bytes);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PWRITEV
DEFINE_COMPAT_SYSCALL3(ssize_t, writev, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			compat_validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_writev(hand, &dst, num_bytes);
	}
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
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_preadv(hand, &dst, num_bytes, (pos_t)offset);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_SYSCALL_PWRITEV
DEFINE_SYSCALL4(ssize_t, pwritev, fd_t, fd,
                USER UNCHECKED struct iovec const *, iov,
                size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)ATOMIC_READ(iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_pwritev(hand, &dst, num_bytes, (pos_t)offset);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITEV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PREADV
DEFINE_COMPAT_SYSCALL4(ssize_t, preadv, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t *)&iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			compat_validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_preadv(hand, &dst, num_bytes, (pos_t)offset);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PWRITEV
DEFINE_COMPAT_SYSCALL4(ssize_t, pwritev, fd_t, fd,
                       USER UNCHECKED struct compat_iovec const *, iov,
                       size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handle_lookup((unsigned int)fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (USER CHECKED byte_t *)(void *)ATOMIC_READ(*(compat_uintptr_t const *)&iov[i].iov_base);
			entries[i].ive_size = ATOMIC_READ(iov[i].iov_len);
			compat_validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_pwritev(hand, &dst, num_bytes, (pos_t)offset);
	}
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
	RAII_FINALLY { decref_unlikely(hand); };
	handle_sync(hand);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSYNC */

#ifdef __ARCH_WANT_SYSCALL_FDATASYNC
DEFINE_SYSCALL1(errno_t, fdatasync, fd_t, fd) {
	struct handle hand;
	hand = handle_lookup((unsigned int)fd);
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
                fd_t, fd, USER UNCHECKED struct dirent *, buf,
                size_t, bufsize, syscall_ulong_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 READDIR_MODEMASK | READDIR_FLAGMASK,
	                 E_INVALID_ARGUMENT_CONTEXT_KREADDIR_MODE);
	validate_writable(buf, bufsize);
	hand = handle_lookup((unsigned int)fd);
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
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_KREADDIRF */





/************************************************************************/
/* poll(), ppoll(), ppoll64()                                           */
/* select(), select64(), pselect6(), pselect6_time64()                  */
/************************************************************************/
#undef WANT_SYS_POLL
#if (defined(__ARCH_WANT_SYSCALL_POLL) ||         \
     defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
#define WANT_SYS_POLL 1
#endif /* poll... */
#undef WANT_SYS_SELECT
#if (defined(__ARCH_WANT_SYSCALL_SELECT) ||               \
     defined(__ARCH_WANT_SYSCALL_SELECT64) ||             \
     defined(__ARCH_WANT_SYSCALL_SELECT_TIME64) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6) ||             \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT64) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
#define WANT_SYS_SELECT 1
#endif /* select... */
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||                  \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) ||           \
     defined(__ARCH_WANT_SYSCALL_PSELECT6) ||               \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64) || \
     defined(__ARCH_WANT_SYSCALL_EPOLL_PWAIT))
#define WANT_SYS_POLLSELECT_SIGSET 1
#endif /* p(poll|select)... */
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
#define WANT_SYS_POLL_SIGSET 1
#endif /* ppoll... */
#if (defined(__ARCH_WANT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
#define WANT_SYS_SELECT_SIGSET 1
#endif /* pselect... */

#if defined(WANT_SYS_POLL) || defined(WANT_SYS_SELECT)
PRIVATE poll_mode_t KCALL do_poll_handle(struct handle &hnd,
                                         poll_mode_t what) {
	/* Always allow polling for these conditions. */
	what |= POLLERR | POLLHUP | POLLNVAL;
	/* Verify that the caller has access to the
	 * indicated  data  channel of  the handle. */
	if (what & POLLINMASK) {
		if unlikely(!IO_CANREAD(hnd.h_mode))
			return POLLERR;
	}
	if (what & POLLOUTMASK) {
		if unlikely(!IO_CANWRITE(hnd.h_mode))
			return POLLERR;
	}
	return handle_poll(hnd, what) & what;
}
#endif /* WANT_SYS_POLL || WANT_SYS_SELECT */

/* Low-level implementations for the user-space poll() and select() system calls. */
#ifdef WANT_SYS_POLL
PRIVATE size_t KCALL
do_poll_scan(USER CHECKED struct pollfd *fds, size_t nfds) {
	size_t i, result = 0;
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
			 * if  we  already know  we won't  wait  on any  of them */
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
			 * from  all  previous poll-signals! */
			task_disconnectall();
			decref(hnd);
			RETHROW();
		}
/*decref_hnd_and_continue:*/
		decref(hnd);
	}
	return result;
}

PRIVATE size_t KCALL
do_poll(USER CHECKED struct pollfd *fds,
        size_t nfds, ktime_t abs_timeout) {
	size_t result;
	/* TODO: Special optimization for when  `abs_timeout == KTIME_NONBLOCK'!
	 *       In this case, it's  enough if we just  test all of the  handles
	 *       for their poll conditions, and forgo all of the signal handling */
again:
	/* Do the poll-scan. */
	result = do_poll_scan(fds, nfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor(abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}

PRIVATE size_t KCALL
do_poll_with_sigmask(USER CHECKED struct pollfd *fds,
                     size_t nfds, ktime_t abs_timeout,
                     sigset_t const *__restrict sigmask) {
	size_t result;
again:
	/* Do the poll-scan. */
	result = do_poll_scan(fds, nfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor_with_sigmask(sigmask, abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}
#endif /* WANT_SYS_POLL */

#ifdef WANT_SYS_SELECT
PRIVATE size_t KCALL
do_select_scan(size_t nfds,
               USER CHECKED fd_set *readfds,
               USER CHECKED fd_set *writefds,
               USER CHECKED fd_set *exceptfds) {
	typedef u8 fds_word_t;
	enum { BITS_PER_FDS_WORD = 8 };
	size_t nfds_words, i, result = 0;
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
				 * if  we  already know  we won't  wait  on any  of them */
				if (result != 0)
					task_disconnectall();
#endif /* !__OPTIMIZE_SIZE__ */
				what = do_poll_handle(hnd, mode);
			} EXCEPT {
				/* Make sure that we're disconnected
				 * from  all  previous poll-signals! */
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
					bzero(readfds, i, sizeof(fds_word_t));
				if (writefds)
					bzero(writefds, i, sizeof(fds_word_t));
				if (exceptfds)
					bzero(exceptfds, i, sizeof(fds_word_t));
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
	return result;
}

PRIVATE size_t KCALL
do_select(size_t nfds,
          USER CHECKED fd_set *readfds,
          USER CHECKED fd_set *writefds,
          USER CHECKED fd_set *exceptfds,
          ktime_t abs_timeout) {
	size_t result;
again:
	/* Do the select-scan. */
	result = do_select_scan(nfds, readfds, writefds, exceptfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor(abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}

PRIVATE size_t KCALL
do_select_with_sigmask(size_t nfds,
                       USER CHECKED fd_set *readfds,
                       USER CHECKED fd_set *writefds,
                       USER CHECKED fd_set *exceptfds,
                       ktime_t abs_timeout,
                       sigset_t const *__restrict sigmask) {
	size_t result;
again:
	/* Do the select-scan. */
	result = do_select_scan(nfds, readfds, writefds, exceptfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor_with_sigmask(sigmask, abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}
#endif /* WANT_SYS_SELECT */

#ifdef __ARCH_WANT_SYSCALL_POLL
DEFINE_SYSCALL3(ssize_t, poll,
                USER UNCHECKED struct pollfd *, fds,
                size_t, nfds, syscall_slong_t, timeout) {
	size_t result;
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (timeout < 0) {
		result = do_poll(fds, nfds, KTIME_INFINITE);
	} else if (timeout == 0) {
		result = do_poll(fds, nfds, KTIME_NONBLOCK);
	} else {
		ktime_t then = ktime();
		then += relktime_from_milliseconds((uintptr_t)timeout);
		result = do_poll(fds, nfds, then);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_POLL */


#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *
sys_ppoll_generic(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info,
                  USER CHECKED struct pollfd *fds, size_t nfds, ktime_t abs_timeout,
                  USER UNCHECKED sigset_t const *sigmask, size_t sigsetsize) {
	size_t result;
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (sigmask) {
		sigset_t these;
		if unlikely(sigsetsize != sizeof(sigset_t)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
			      sigsetsize);
		}
		validate_readable(sigmask, sizeof(sigset_t));
		memcpy(&these, sigmask, sizeof(sigset_t));

		/* These signals cannot be masked.  */
		sigdelset(&these, SIGSTOP);
		sigdelset(&these, SIGKILL);

		/* Indicate that we want to receive wake-ups for masked signals. */
		ATOMIC_OR(THIS_TASK->t_flags, TASK_FWAKEONMSKRPC);

		/* This will clear `TASK_FWAKEONMSKRPC', as well as
		 * perform a check for signals not in `these' which
		 * may have also appeared in the mean time prior to
		 * returning to user-space. */
		userexcept_sysret_inject_self();

again:
		TRY {
			result = do_poll_with_sigmask(fds, nfds, abs_timeout, &these);
		} EXCEPT {
			/* This function  only returns  normally
			 * when the syscall should be restarted. */
			state = userexcept_handler_with_sigmask(state, sc_info, &these);
			PERTASK_SET(this_exception_code, 1); /* Prevent internal fault */
			goto again;
		}
	} else {
		result = do_poll(fds, nfds, abs_timeout);
	}
	icpustate_setreturn(state, result);
	return state;
}
#endif /* ppoll... */

#ifdef __ARCH_WANT_SYSCALL_PPOLL
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_ppoll_impl(struct icpustate *__restrict state,
               struct rpc_syscall_info *__restrict sc_info) {
	USER UNCHECKED struct pollfd *fds                  = (USER UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                        = (size_t)sc_info->rsi_regs[1];
	USER UNCHECKED struct timespec32 const *timeout_ts = (USER UNCHECKED struct timespec32 const *)sc_info->rsi_regs[2];
	USER UNCHECKED sigset_t const *sigmask             = (USER UNCHECKED sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                  = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_ppoll_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_ppoll_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL5(ssize_t, ppoll,
                USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                USER UNCHECKED struct timespec32 const *, timeout_ts,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize) {
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_ppoll_rpc, NULL);
		__builtin_unreachable();
	}
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PPOLL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PPOLL
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_ppoll_impl(struct icpustate *__restrict state,
                      struct rpc_syscall_info *__restrict sc_info) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	USER UNCHECKED struct pollfd *fds                         = (USER UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                               = (size_t)sc_info->rsi_regs[1];
	USER UNCHECKED struct compat_timespec32 const *timeout_ts = (USER UNCHECKED struct compat_timespec32 const *)sc_info->rsi_regs[2];
	USER UNCHECKED compat_sigset_t const *sigmask             = (USER UNCHECKED compat_sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                         = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_ppoll_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_ppoll_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll,
                       USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                       USER UNCHECKED struct compat_timespec32 const *, timeout_ts,
                       USER UNCHECKED compat_sigset_t const *, sigmask,
                       size_t, sigsetsize) {
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_ppoll_rpc, NULL);
		__builtin_unreachable();
	}
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		compat_validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL */

#ifdef __ARCH_WANT_SYSCALL_PPOLL_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_ppoll_time64_impl(struct icpustate *__restrict state,
                             struct rpc_syscall_info *__restrict sc_info) {
	STATIC_ASSERT(sizeof(sigset_t) == sizeof(sigset_t));
	USER UNCHECKED struct pollfd *fds                  = (USER UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                        = (size_t)sc_info->rsi_regs[1];
	USER UNCHECKED struct timespec64 const *timeout_ts = (USER UNCHECKED struct timespec64 const *)sc_info->rsi_regs[2];
	USER UNCHECKED sigset_t const *sigmask             = (USER UNCHECKED sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                  = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_ppoll_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_ppoll_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL5(ssize_t, ppoll_time64,
                USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                USER UNCHECKED struct timespec64 const *, timeout_ts,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize) {
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_ppoll_time64_rpc, NULL);
		__builtin_unreachable();
	}
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PPOLL_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_ppoll_time64_impl(struct icpustate *__restrict state,
                             struct rpc_syscall_info *__restrict sc_info) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	USER UNCHECKED struct pollfd *fds                         = (USER UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                               = (size_t)sc_info->rsi_regs[1];
	USER UNCHECKED struct compat_timespec64 const *timeout_ts = (USER UNCHECKED struct compat_timespec64 const *)sc_info->rsi_regs[2];
	USER UNCHECKED compat_sigset_t const *sigmask             = (USER UNCHECKED compat_sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                         = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_ppoll_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_ppoll_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll_time64,
                       USER UNCHECKED struct pollfd *, fds, size_t, nfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout_ts,
                       USER UNCHECKED compat_sigset_t const *, sigmask,
                       size_t, sigsetsize) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_ppoll_time64_rpc, NULL);
		__builtin_unreachable();
	}
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		compat_validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64 */

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
	ktime_t abs_timeout;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
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
	ktime_t abs_timeout;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
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
	ktime_t abs_timeout;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
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
	ktime_t abs_timeout;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT64 */

#if (defined(__ARCH_WANT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *
sys_pselect_generic(struct icpustate *__restrict state,
                    struct rpc_syscall_info *__restrict sc_info, size_t nfds,
                    USER UNCHECKED fd_set *readfds, USER UNCHECKED fd_set *writefds,
                    USER UNCHECKED fd_set *exceptfds, ktime_t abs_timeout,
                    USER UNCHECKED sigset_t const *sigmask, size_t sigsetsize) {
	size_t result, nfd_size;
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	if (sigmask) {
		sigset_t these;
		if unlikely(sigsetsize != sizeof(sigset_t)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
			      sigsetsize);
		}
		validate_readable(sigmask, sizeof(sigset_t));
		memcpy(&these, sigmask, sizeof(sigset_t));

		/* These signals cannot be masked.  */
		sigdelset(&these, SIGSTOP);
		sigdelset(&these, SIGKILL);

		/* Indicate that we want to receive wake-ups for masked signals. */
		ATOMIC_OR(THIS_TASK->t_flags, TASK_FWAKEONMSKRPC);

		/* This will clear `TASK_FWAKEONMSKRPC', as well as
		 * perform a check for signals not in `these' which
		 * may have also appeared in the mean time prior to
		 * returning to user-space. */
		userexcept_sysret_inject_self();

again:
		TRY {
			result = do_select_with_sigmask(nfds, readfds, writefds, exceptfds, abs_timeout, &these);
		} EXCEPT {
			/* This function  only returns  normally
			 * when the syscall should be restarted. */
			state = userexcept_handler_with_sigmask(state, sc_info, &these);
			PERTASK_SET(this_exception_code, 1); /* Prevent internal fault */
			goto again;
		}
	} else {
		result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	}
	icpustate_setreturn(state, result);
	return state;
}

#endif /* pselect... */

#ifdef __ARCH_WANT_SYSCALL_PSELECT6
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_pselect6_impl(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info) {
	struct sigset_and_len {
		sigset_t const *ss_ptr;
		size_t          ss_len;
	};
	size_t nfds                                       = (size_t)sc_info->rsi_regs[0];
	USER UNCHECKED fd_set *readfds                    = (USER UNCHECKED fd_set *)sc_info->rsi_regs[1];
	USER UNCHECKED fd_set *writefds                   = (USER UNCHECKED fd_set *)sc_info->rsi_regs[2];
	USER UNCHECKED fd_set *exceptfds                  = (USER UNCHECKED fd_set *)sc_info->rsi_regs[3];
	USER UNCHECKED struct timespec32 const *timeout   = (USER UNCHECKED struct timespec32 const *)sc_info->rsi_regs[4];
	USER UNCHECKED void const *sigmask_sigset_and_len = (USER UNCHECKED void const *)sc_info->rsi_regs[5];
	struct sigset_and_len ss;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds,
	                           exceptfds, abs_timeout, ss.ss_ptr, ss.ss_len);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_pselect6_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_pselect6_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

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
	struct sigset_and_len ss;
	size_t result, nfd_size;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if (ss.ss_ptr) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_pselect6_rpc, NULL);
		__builtin_unreachable();
	}
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PSELECT6 */

#ifdef __ARCH_WANT_SYSCALL_PSELECT6_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_pselect6_time64_impl(struct icpustate *__restrict state,
                         struct rpc_syscall_info *__restrict sc_info) {
	struct sigset_and_len {
		sigset_t const *ss_ptr;
		size_t          ss_len;
	};
	size_t nfds                                       = (size_t)sc_info->rsi_regs[0];
	USER UNCHECKED fd_set *readfds                    = (USER UNCHECKED fd_set *)sc_info->rsi_regs[1];
	USER UNCHECKED fd_set *writefds                   = (USER UNCHECKED fd_set *)sc_info->rsi_regs[2];
	USER UNCHECKED fd_set *exceptfds                  = (USER UNCHECKED fd_set *)sc_info->rsi_regs[3];
	USER UNCHECKED struct timespec64 const *timeout   = (USER UNCHECKED struct timespec64 const *)sc_info->rsi_regs[4];
	USER UNCHECKED void const *sigmask_sigset_and_len = (USER UNCHECKED void const *)sc_info->rsi_regs[5];
	struct sigset_and_len ss;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds,
	                           exceptfds, abs_timeout, ss.ss_ptr, ss.ss_len);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_pselect6_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_pselect6_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL6(ssize_t, pselect6_time64, size_t, nfds,
                USER UNCHECKED fd_set *, readfds,
                USER UNCHECKED fd_set *, writefds,
                USER UNCHECKED fd_set *, exceptfds,
                USER UNCHECKED struct timespec64 const *, timeout,
                USER UNCHECKED void const *, sigmask_sigset_and_len) {
	struct sigset_and_len {
		sigset_t const *ss_ptr;
		size_t          ss_len;
	};
	struct sigset_and_len ss;
	size_t result, nfd_size;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if (ss.ss_ptr) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_pselect6_time64_rpc, NULL);
		__builtin_unreachable();
	}
	nfd_size = CEILDIV(nfds, __NFDBITS);
	validate_readwrite_opt(readfds, nfd_size);
	validate_readwrite_opt(writefds, nfd_size);
	validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PSELECT6_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PSELECT6
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_pselect6_impl(struct icpustate *__restrict state,
                         struct rpc_syscall_info *__restrict sc_info) {
	struct sigset_and_len {
		compat_ptr(compat_sigset_t const) ss_ptr;
		compat_size_t                     ss_len;
	};
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	size_t nfds                                            = (size_t)sc_info->rsi_regs[0];
	USER UNCHECKED fd_set *readfds                         = (USER UNCHECKED fd_set *)sc_info->rsi_regs[1];
	USER UNCHECKED fd_set *writefds                        = (USER UNCHECKED fd_set *)sc_info->rsi_regs[2];
	USER UNCHECKED fd_set *exceptfds                       = (USER UNCHECKED fd_set *)sc_info->rsi_regs[3];
	USER UNCHECKED struct compat_timespec32 const *timeout = (USER UNCHECKED struct compat_timespec32 const *)sc_info->rsi_regs[4];
	USER UNCHECKED void const *sigmask_sigset_and_len      = (USER UNCHECKED void const *)sc_info->rsi_regs[5];
	struct sigset_and_len ss;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds,
	                           exceptfds, abs_timeout, ss.ss_ptr, ss.ss_len);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_pselect6_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_pselect6_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timespec32 const *, timeout,
                       USER UNCHECKED void const *, sigmask_sigset_and_len) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	struct sigset_and_len {
		compat_ptr(compat_sigset_t const) ss_ptr;
		compat_size_t                     ss_len;
	};
	struct sigset_and_len ss;
	size_t result, nfd_size;
	ktime_t abs_timeout;
	compat_validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if (ss.ss_ptr) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_pselect6_rpc, NULL);
		__builtin_unreachable();
	}
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PSELECT6 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_pselect6_time64_impl(struct icpustate *__restrict state,
                                struct rpc_syscall_info *__restrict sc_info) {
	struct sigset_and_len {
		compat_ptr(compat_sigset_t const) ss_ptr;
		compat_size_t                     ss_len;
	};
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	size_t nfds                                            = (size_t)sc_info->rsi_regs[0];
	USER UNCHECKED fd_set *readfds                         = (USER UNCHECKED fd_set *)sc_info->rsi_regs[1];
	USER UNCHECKED fd_set *writefds                        = (USER UNCHECKED fd_set *)sc_info->rsi_regs[2];
	USER UNCHECKED fd_set *exceptfds                       = (USER UNCHECKED fd_set *)sc_info->rsi_regs[3];
	USER UNCHECKED struct compat_timespec64 const *timeout = (USER UNCHECKED struct compat_timespec64 const *)sc_info->rsi_regs[4];
	USER UNCHECKED void const *sigmask_sigset_and_len      = (USER UNCHECKED void const *)sc_info->rsi_regs[5];
	struct sigset_and_len ss;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds,
	                           exceptfds, abs_timeout, ss.ss_ptr, ss.ss_len);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_pselect6_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_pselect6_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6_time64, size_t, nfds,
                       USER UNCHECKED fd_set *, readfds,
                       USER UNCHECKED fd_set *, writefds,
                       USER UNCHECKED fd_set *, exceptfds,
                       USER UNCHECKED struct compat_timespec64 const *, timeout,
                       USER UNCHECKED void const *, sigmask_sigset_and_len) {
	STATIC_ASSERT(sizeof(compat_sigset_t) == sizeof(sigset_t));
	struct sigset_and_len {
		compat_ptr(compat_sigset_t const) ss_ptr;
		compat_size_t                     ss_len;
	};
	struct sigset_and_len ss;
	size_t result, nfd_size;
	ktime_t abs_timeout;
	compat_validate_readable(sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	memcpy(&ss, sigmask_sigset_and_len, sizeof(ss));
	COMPILER_READ_BARRIER();
	if (ss.ss_ptr) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_pselect6_time64_rpc, NULL);
		__builtin_unreachable();
	}
	nfd_size = CEILDIV(nfds, __NFDBITS);
	compat_validate_readwrite_opt(readfds, nfd_size);
	compat_validate_readwrite_opt(writefds, nfd_size);
	compat_validate_readwrite_opt(exceptfds, nfd_size);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64 */




/************************************************************************/
/* pause()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PAUSE
DEFINE_SYSCALL0(errno_t, pause) {
	for (;;) {
		assert(!task_wasconnected());
		/* Wait forever (equivalent to `select(0, NULL, NULL, NULL, NULL)')
		 * NOTE: `task_waitfor()' calls `task_serve()', which may in turn throw
		 *       `E_INTERRUPT' when  a signal  gets  delivered to  our  thread. */
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

PRIVATE ATTR_RETNONNULL WUNUSED REF struct mman *KCALL
kcmp_get_mman_from_pid(pid_t pid) {
	REF struct mman *result;
	REF struct task *thread;
	/* Lookup the thread in question */
	thread = kcmp_get_thread_from_pid(pid);
	FINALLY_DECREF_UNLIKELY(thread);
	/* Retrieve the thread's mman. */
	result = task_getmman(thread);
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
		RAII_FINALLY { decref_unlikely(hand1); };
		hand2  = kcmp_get_handle_from_pid(pid2, (unsigned int)idx2);
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
