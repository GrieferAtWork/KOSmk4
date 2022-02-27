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
#ifndef GUARD_KERNEL_SRC_FD_FCNTL_C
#define GUARD_KERNEL_SRC_FD_FCNTL_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/fifonode.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/pipe.h>
#include <kernel/syscall.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>

/************************************************************************/
/* fcntl(2)                                                             */
/************************************************************************/

DECL_BEGIN

#ifdef __ARCH_WANT_SYSCALL_FCNTL
#define WANT_FCNTL
#endif /* __ARCH_WANT_SYSCALL_FCNTL */

#ifdef WANT_FCNTL
INTDEF size_t KCALL /* from "misc/pipe.c" */
ringbuffer_set_pipe_limit(struct ringbuffer *__restrict self,
                          size_t new_lim);


PRIVATE syscall_slong_t KCALL
sys_fcntl_impl(fd_t fd, fcntl_t command,
               UNCHECKED USER void *arg) {
	struct handman *man = THIS_HANDMAN;
	switch (command) {

	case F_DUPFD: {
		REF struct handle buf;
		REF struct handle *hand;
		hand = handles_lookup(fd, &buf);
		__builtin_assume(hand == &buf);
		RAII_FINALLY { decref_unlikely(*hand); };
		hand->h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
		return handman_install(man, hand, (fd_t)(intptr_t)(uintptr_t)arg);
	}	break;

	case F_DUPFD_CLOEXEC: {
		REF struct handle buf;
		REF struct handle *hand;
		hand = handles_lookup(fd, &buf);
		__builtin_assume(hand == &buf);
		RAII_FINALLY { decref_unlikely(*hand); };
		hand->h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
		hand->h_mode |= IO_CLOEXEC;
		return handman_install(man, hand, (fd_t)(intptr_t)(uintptr_t)arg);
	}	break;

	case F_DUP2FD: {
		REF struct handle buf;
		REF struct handle *hand;
		hand = handles_lookup(fd, &buf);
		__builtin_assume(hand == &buf);
		RAII_FINALLY { decref_unlikely(*hand); };
		hand->h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
		return handman_install_into(man, (fd_t)(intptr_t)(uintptr_t)arg, hand);
	}	break;

	case F_DUP2FD_CLOEXEC: {
		REF struct handle buf;
		REF struct handle *hand;
		hand = handles_lookup(fd, &buf);
		__builtin_assume(hand == &buf);
		RAII_FINALLY { decref_unlikely(*hand); };
		hand->h_mode &= ~(IO_CLOEXEC | IO_CLOFORK);
		hand->h_mode |= IO_CLOEXEC;
		return handman_install_into(man, (fd_t)(intptr_t)(uintptr_t)arg, hand);
	}	break;

	case F_GETFD: {
		iomode_t mode;
		mode = handman_gethandflags(man, fd);
		return IO_HANDLE_FTO_FD(mode);
	}	break;

	case F_SETFD: {
		iomode_t newmode;
		VALIDATE_FLAGSET((uintptr_t)arg, FD_CLOEXEC | FD_CLOFORK,
		                 E_INVALID_ARGUMENT_CONTEXT_F_SETFD_FDFLAGS);
		newmode = IO_HANDLE_FFROM_FD((uintptr_t)arg);
		assert(!(newmode & ~(IO_CLOEXEC | IO_CLOFORK)));
		handman_sethandflags(man, fd, ~(IO_CLOEXEC | IO_CLOFORK), newmode);
	}	break;

	case F_GETFL: {
		iomode_t mode;
		mode = handman_gethandflags(man, fd);
		mode &= IO_SETFL_MASK;
		return IO_TO_OPENFLAG_NOHANDLE(mode);
	}	break;

	case F_SETFL:
	case F_SETFL_XCH: {
		iomode_t omode, nmode;
		VALIDATE_FLAGSET((uintptr_t)arg, IO_SETFL_MASK,
		                 E_INVALID_ARGUMENT_CONTEXT_F_SETFL_OFLAGS);
		nmode = IO_FROM_OPENFLAG_NOHANDLE((oflag_t)(uintptr_t)arg);
		omode = handman_sethandflags(man, fd, (iomode_t)~IO_SETFL_MASK, nmode);
		if (command == F_SETFL)
			omode = -EOK;
		return omode;
	}	break;

	case F_NEXT:
		/* Find the first valid FD >= the given one. */
		return handman_findnext(man, fd);

	case F_CLOSEM:
		/* Close all handles `>= fd'
		 * KOS returns the  actual number of  closed files, however  given
		 * that this fcntl doesn't have very large support, this  behavior
		 * may differ on those few other platforms that actually implement
		 * this command. */
		return handman_closerange(man, (unsigned int)fd, (unsigned int)-1);

	case F_MAXFD: {
		unsigned int fdend;
		(void)fd; /* Unused by this fcntl() command */
		handman_read(man);
		fdend = handman_usefdend(man);
		handman_endread(man);
		if unlikely(fdend == 0) {
			THROW(E_INVALID_HANDLE_FILE, -1,
			      E_INVALID_HANDLE_FILE_UNBOUND, 0,
			      ATOMIC_READ(man->hm_maxfd));
		}
		--fdend;
		return (syscall_slong_t)(syscall_ulong_t)fdend;
	}	break;

	//TODO:case F_GETLK32:
	//TODO:case F_SETLK32:
	//TODO:case F_SETLKW32:
	//TODO:case F_SETOWN:
	//TODO:case F_GETOWN:
	//TODO:case F_SETSIG:
	//TODO:case F_GETSIG:
	//TODO:case F_GETLK64:
	//TODO:case F_SETLK64:
	//TODO:case F_SETLKW64:
	//TODO:case F_SETOWN_EX:
	//TODO:case F_GETOWN_EX:
	//TODO:case F_SETLEASE:
	//TODO:case F_GETLEASE:
	//TODO:case F_NOTIFY:

	case F_GETPIPE_SZ:
	case F_SETPIPE_SZ: {
		struct ringbuffer *rb;
		REF struct handle buf;
		REF struct handle *hand;
		hand = handles_lookup(fd, &buf);
		__builtin_assume(hand == &buf);
		RAII_FINALLY { decref_unlikely(*hand); };

		/* Switch  on  the  handle  type  (this  fcntl() code
		 * should have really been an ioctl if you ask me...) */
		switch (hand->h_type) {

		case HANDLE_TYPE_PIPE_READER:
		case HANDLE_TYPE_PIPE_WRITER: {
			struct pipe_reader *me;
			me = (struct pipe_reader *)hand->h_data;
			rb = &me->pr_pipe->p_buffer;
		}	break;

		case HANDLE_TYPE_PIPE: {
			struct pipe *me;
			me = (struct pipe *)hand->h_data;
			rb = &me->p_buffer;
		}	break;

		case HANDLE_TYPE_FIFOHANDLE: {
			struct fifohandle *me;
			me = (struct fifohandle *)hand->h_data;
			rb = &me->fu_fifo->ff_buffer;
		}	break;

		case HANDLE_TYPE_MFILE: {
			struct mfile *me;
			me = (struct mfile *)hand->h_data;
			if (!mfile_isfifo(me)) {
				THROW(E_INVALID_HANDLE_FILETYPE,
				      /* fd:                 */ fd,
				      /* needed_handle_type: */ HANDLE_TYPE_MFILE,
				      /* actual_handle_type: */ HANDLE_TYPE_MFILE,
				      /* needed_handle_kind: */ HANDLE_TYPEKIND_MFILE_FFIFONODE,
				      /* actual_handle_kind: */ handle_typekind(hand));
			}
			rb = &mfile_asfifo(me)->ff_buffer;
		}	break;

		default:
			THROW(E_INVALID_HANDLE_FILETYPE,
			      /* fd:                 */ fd,
			      /* needed_handle_type: */ HANDLE_TYPE_PIPE,
			      /* actual_handle_type: */ hand->h_type,
			      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
			      /* actual_handle_kind: */ handle_typekind(hand));
			break;
		}
		if (command == F_GETPIPE_SZ) {
			if unlikely(!IO_CANREAD(hand->h_mode)) {
				THROW(E_INVALID_HANDLE_OPERATION, fd,
				      E_INVALID_HANDLE_OPERATION_GETPROPERTY,
				      hand->h_mode);
			}
			return ATOMIC_READ(rb->rb_limit);
		} else {
			size_t newsize;
			if unlikely(!IO_CANWRITE(hand->h_mode)) {
				THROW(E_INVALID_HANDLE_OPERATION, fd,
				      E_INVALID_HANDLE_OPERATION_SETPROPERTY,
				      hand->h_mode);
			}
			newsize = (size_t)(uintptr_t)arg;
			if unlikely(newsize < 1) {
				/* Linux requires PAGESIZE here... */
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_F_SETPIPE_SZ_TOO_SMALL,
				      newsize);
			}
			/* Permissions checking is done in `ringbuffer_set_pipe_limit()' */
			ringbuffer_set_pipe_limit(rb, newsize);
		}
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_FCNTL_COMMAND,
		      command);
		break;
	}
	return -EOK;
}
#endif /* WANT_FCNTL */

#ifdef __ARCH_WANT_SYSCALL_FCNTL
DEFINE_SYSCALL3(syscall_slong_t, fcntl, fd_t, fd,
                fcntl_t, command, UNCHECKED USER void *, arg) {
	return sys_fcntl_impl(fd, command, arg);
}
#endif /* __ARCH_WANT_SYSCALL_FCNTL */


DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_FCNTL_C */
