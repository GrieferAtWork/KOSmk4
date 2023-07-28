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
#ifndef GUARD_KERNEL_SRC_FD_IOCTL_C
#define GUARD_KERNEL_SRC_FD_IOCTL_C 1
#define _KOS_SOURCE 1
#define __EXTENSIONS__ 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/panic.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/task.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/ioctl/fd.h>
#include <linux/fs.h>
#include <sys/fcntl.h>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include <sys/types.h> /* loff_t */

#include <errno.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/************************************************************************/
/* ioctl(), ioctlf()                                                    */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_IOCTL) || defined(__ARCH_WANT_SYSCALL_IOCTLF)
PRIVATE NOBLOCK void
NOTHROW(KCALL ioctl_complete_exception_info)(fd_t fd) {
	except_code_t code = except_code();
	switch (code) {

	case EXCEPT_CODEOF(E_INVALID_HANDLE_OPERATION):
		if (!PERTASK_TEST(this_exception_args.e_invalid_handle.ih_fd)) /* fd */
			PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, (uintptr_t)(intptr_t)fd);
		break;

	default: break;
	}
}

static_assert(FD_IOC_DIRECTIO == _FIODIRECTIO);
static_assert(FD_IOC_DIRECTIO_OFF == DIRECTIO_OFF);
static_assert(FD_IOC_DIRECTIO_ON == DIRECTIO_ON);
static_assert(FD_IOC_DIRECTIO_MAND == DIRECTIO_MAND);
static iomode_t const directio_modes[] = {
	[FD_IOC_DIRECTIO_OFF]  = 0,
	[FD_IOC_DIRECTIO_ON]   = IO_DIRECT | IO_OPTDIRECT,
	[FD_IOC_DIRECTIO_MAND] = IO_DIRECT,
};

PRIVATE WUNUSED iomode_t FCALL get_directio_mode(uintptr_t cmd) {
	if (cmd >= lengthof(directio_modes)) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_DIRECTIO_MODE,
		      cmd);
	}
	return directio_modes[cmd];
}


PRIVATE WUNUSED NONNULL((3, 5)) bool KCALL
ioctl_generic(ioctl_t cmd, fd_t fd,
              struct handle const *__restrict hand,
              NCX UNCHECKED void *arg,
              syscall_slong_t *__restrict result) {
	/* Check for specific commands. */
	switch (cmd) {

	case FIOCLEX: /* aka. FD_IOC_CLEX */
		/* Set IO_CLOEXEC */
		if (hand->h_mode & IO_CLOEXEC)
			break;
		handman_sethandflags(THIS_HANDMAN, fd, ~0, (IO_CLOEXEC));
		break;

	case FIONCLEX: /* aka. FD_IOC_NCLEX */
		/* Clear IO_CLOEXEC */
		if (!(hand->h_mode & IO_CLOEXEC))
			break;
		handman_sethandflags(THIS_HANDMAN, fd, ~(IO_CLOEXEC), 0);
		break;

	case FD_IOC_DUPFD: {
		NCX UNCHECKED struct openfd *ofd;
		ofd = (NCX UNCHECKED struct openfd *)arg;
		*result = handles_install_openfd(hand, ofd);
	}	goto done;

	case FD_IOC_NOOP:
		/* Intentional no-op */
		break;

	case FD_IOC_CAST: {
		struct handle newhand;
		NCX struct fdcast *cast;
		uintptr_half_t reqtype;
		validate_readwrite(arg, sizeof(*cast));
		cast = (NCX struct fdcast *)arg;
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
				      /* fd:                 */ fd,
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
		*result = handles_install_openfd(newhand, &cast->fc_resfd);
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
		((NCX struct fddesc *)arg)->fdc_len = reqlen;
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

	case FD_IOC_DIRECTIO: {
		/* Adjust handle flags */
		iomode_t iomode = get_directio_mode((uintptr_t)arg);
		handman_sethandflags(THIS_HANDMAN, fd,
		                     ~(IO_DIRECT | IO_OPTDIRECT),
		                     iomode);
	}	break;

	default:
		/* Commands for which we accept any size value. */
		switch (_IO_WITHSIZE(cmd, 0)) {

		case _IO_WITHSIZE(FIONBIO, 0): /* FD_IOC_NBIO */
			/* Set/clear IO_NONBLOCK */
			handman_sethandflags(THIS_HANDMAN, fd, ~IO_NONBLOCK,
			                     ioctl_intarg_getbool(cmd, arg)
			                     ? IO_NONBLOCK
			                     : 0);
			break;

		case _IO_WITHSIZE(FIOASYNC, 0): /* FD_IOC_ASYNC */
			/* Set/clear IO_ASYNC */
			handman_sethandflags(THIS_HANDMAN, fd, ~IO_ASYNC,
			                     ioctl_intarg_getbool(cmd, arg)
			                     ? IO_ASYNC
			                     : 0);
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

		case _IO_WITHSIZE(FD_IOC_GETDIRECTIO, 0): {
			unsigned int mode = FD_IOC_DIRECTIO_OFF;
			if (hand->h_mode & IO_DIRECT) {
				mode = FD_IOC_DIRECTIO_MAND;
				if (hand->h_mode & IO_OPTDIRECT)
					mode = FD_IOC_DIRECTIO_ON;
			}
			*result = ioctl_intarg_setuint(cmd, arg, mode);
			goto done;
		}	break;

		case _IO_WITHSIZE(FD_IOC_SETDIRECTIO, 0): {
			/* Adjust handle flags */
			unsigned int umode = ioctl_intarg_getuint(cmd, arg);
			iomode_t iomode    = get_directio_mode(umode);
			handman_sethandflags(THIS_HANDMAN, fd,
			                     ~(IO_DIRECT | IO_OPTDIRECT),
			                     iomode);
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
                ioctl_t, command, NCX UNCHECKED void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	hand = handles_lookup(fd);
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
				ioctl_complete_exception_info(fd);
				RETHROW();
			}
		}
		ioctl_complete_exception_info(fd);
		RETHROW();
	}
done:
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_IOCTL */

#ifdef __ARCH_WANT_SYSCALL_IOCTLF
DEFINE_SYSCALL4(syscall_slong_t, ioctlf, fd_t, fd,
                ioctl_t, command, iomode_t, mode,
                NCX UNCHECKED void *, arg) {
	struct handle hand;
	syscall_slong_t result;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_IOCTLF_MODE);
	hand = handles_lookup(fd);
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
				ioctl_complete_exception_info(fd);
				RETHROW();
			}
		}
		ioctl_complete_exception_info(fd);
		RETHROW();
	}
done:
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_IOCTLF */

DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_IOCTL_C */
