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
#ifndef GUARD_KERNEL_SRC_DEV_TTYBASE_C
#define GUARD_KERNEL_SRC_DEV_TTYBASE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <dev/ttybase.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid-ctty.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>

#include <hybrid/atomic.h>

#include <asm/ioctls.h>
#include <kos/except-inval.h>
#include <kos/except-io.h>
#include <linux/termios.h> /* struct termiox */
#include <sys/stat.h>
#include <sys/types.h> /* loff_t */

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <libterm/termio.h>

DECL_BEGIN

PRIVATE NOBLOCK void
NOTHROW(KCALL ttybase_log_setsession)(struct ttybase_device *__restrict self,
                                      struct task *__restrict UNUSED(session),
                                      struct taskpid *__restrict session_pid) {
	printk(KERN_NOTICE "[ctty][+] Assign tty %q as controller for session %u\n",
	       self->cd_name, taskpid_getrootpid(session_pid));
}

PRIVATE NOBLOCK void
NOTHROW(KCALL ttybase_log_delsession)(struct ttybase_device *__restrict self,
                                      struct task *__restrict UNUSED(session),
                                      struct taskpid *__restrict session_pid) {
	printk(KERN_NOTICE "[ctty][-] Remove tty %q as controller for session %u\n",
	       self->cd_name, taskpid_getrootpid(session_pid));
}



/* Initialize a given TTY character device. */
PUBLIC NOBLOCK void
NOTHROW(KCALL ttybase_device_cinit)(struct ttybase_device *__restrict self,
                                    pterminal_oprinter_t oprinter) {
	assert(self->t_cproc.m_pointer == NULL);
	assert(self->t_fproc.m_pointer == NULL);
	self->cd_type.ct_fini  = &ttybase_device_fini;
	self->cd_type.ct_read  = &ttybase_device_iread;
	self->cd_type.ct_write = &ttybase_device_owrite;
	self->cd_type.ct_poll  = &ttybase_device_poll;
	self->cd_type.ct_ioctl = &ttybase_device_ioctl;
	self->cd_type.ct_stat  = &ttybase_device_stat;
	/* Initialize the terminal driver. */
	terminal_init(&self->t_term,
	              oprinter,
	              &kernel_terminal_raise,
	              &kernel_terminal_check_sigttou);
}




LOCAL void KCALL
kernel_terminal_check_sigtty(struct terminal *__restrict self,
                             bool is_SIGTTOU) {
	struct ttybase_device *term;
	REF struct task *my_leader;
	term = container_of(self, struct ttybase_device, t_term);
	assert(character_device_isattybase(term));
	my_leader = task_getprocessgroupleader();
	FINALLY_DECREF_UNLIKELY(my_leader);
	if unlikely(FORTASK(my_leader, this_taskpid) != ATOMIC_READ(term->t_fproc.m_pointer)) {
		struct taskpid *my_leader_pid;
		REF struct task *oldproc;
		REF struct taskpid *oldpid;
		my_leader_pid = FORTASK(my_leader, this_taskpid);
again_set_myleader_as_fproc:
		if (term->t_fproc.cmpxch(NULL, my_leader_pid))
			return; /* Lazily set the caller as the initial foreground process */
		/* Check if the old foreground process has already
		 * terminated, but hasn't been cleaned up, yet. */
		oldpid = term->t_fproc.get();
		if unlikely(!oldpid)
			goto again_set_myleader_as_fproc;
		oldproc = taskpid_gettask(oldpid);
		if unlikely(!oldproc) {
			bool xch_ok;
do_try_override_fproc:
			xch_ok = term->t_fproc.cmpxch(oldpid, my_leader_pid);
			decref_likely(oldpid);
			if unlikely(!xch_ok)
				goto again_set_myleader_as_fproc;
			return; /* All right! we've got the lock. */
		}
		if (ATOMIC_READ(oldproc->t_flags) & (TASK_FTERMINATING |
		                                     TASK_FTERMINATED)) {
			decref_unlikely(oldproc);
			goto do_try_override_fproc;
		}
		decref_unlikely(oldproc);
		decref_unlikely(oldpid);


		/* 11.1.4 -- Terminal Access Control */
		if (is_SIGTTOU) {
			printk(KERN_INFO "[tty:%q] Background process group %p [tid=%u], thread %p [tid=%u] tried to write\n",
			       term->cd_name, my_leader, (unsigned int)task_getrootpid_of_s(my_leader),
			       THIS_TASK, task_getroottid_s());
			/* ... Attempts by a process in a background process group to write to its controlling
			 * terminal shall cause the process group to be sent a SIGTTOU signal unless one of the
			 * following special cases applies:
			 *   - If [...] the process is ignoring or blocking the SIGTTOU signal, the process
			 *     is allowed to write to the terminal and the SIGTTOU signal is not sent.
			 *   - If [...] the process group of the writing process is orphaned, and the writing
			 *     process is not ignoring or blocking the SIGTTOU signal, the write() shall return -1
			 *     with errno set to [EIO] and no signal shall be sent */
			if (taskpid_isorphan_p(my_leader_pid)) {
do_throw_ttou:
				THROW(E_IOERROR_NODATA,
				      E_IOERROR_SUBSYSTEM_TTY,
				      E_IOERROR_REASON_TTY_ORPHAN_SIGTTOU);
			}
			/* NOTE: We also do the same if our process group leader has died, because once
			 *       that has happened, any other process is allowed to steal the TTY! */
			if (my_leader->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED))
				goto do_throw_ttou;
			task_raisesignalprocessgroup(my_leader, SIGTTOU);
			/* We might get here if the calling process changed its process group
			 * in the mean time. - In this case, just re-raise `SIGTTIN' within the
			 * calling process only. */
			task_raisesignalprocess(task_getprocess(), SIGTTOU);
			/* We might get here if `SIGTTOU' is being ignored by the calling thread.
			 * -> As described by POSIX, allow the process to write in this szenario. */
		} else {
			printk(KERN_INFO "[tty:%q] Background process group %p [tid=%u], thread %p [tid=%u] tried to read\n",
			       term->cd_name, my_leader, (unsigned int)task_getrootpid_of_s(my_leader),
			       THIS_TASK, task_getroottid_s());
			/* ... if the reading process is ignoring or blocking the SIGTTIN signal, or if
			 * the process group of the reading process isorphaned, the read() shall return
			 * -1, with errno set to [EIO] and no signal shall be sent. */
			if (taskpid_isorphan_p(my_leader_pid))
				goto do_throw_ttin;
			/* NOTE: We also do the same if our process group leader has died, because once
			 *       that has happened, any other process is allowed to steal the TTY! */
			if (my_leader->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED))
				goto do_throw_ttin;
			task_raisesignalprocessgroup(my_leader, SIGTTIN);
			/* We might get here if the calling process changed its process group
			 * in the mean time. - In this case, just re-raise `SIGTTIN' within the
			 * calling process only. */
			task_raisesignalprocess(task_getprocess(), SIGTTIN);
			/* We might get here if `SIGTTIN' is being ignored by the calling thread. */
do_throw_ttin:
			THROW(E_IOERROR_NODATA,
			      E_IOERROR_SUBSYSTEM_TTY,
			      E_IOERROR_REASON_TTY_ORPHAN_SIGTTIN);
		}
	}
}

/* Kernel-level implementations for terminal system operators. */
PUBLIC ssize_t LIBTERM_CC
kernel_terminal_check_sigttou(struct terminal *__restrict self) {
	kernel_terminal_check_sigtty(self, true);
	return 0;
}

PUBLIC ssize_t LIBTERM_CC
kernel_terminal_raise(struct terminal *__restrict self,
                      unsigned int signo) {
	REF struct taskpid *fg_pid;
	struct ttybase_device *term;
	term = container_of(self, struct ttybase_device, t_term);
	assert(character_device_isattybase(term));
	fg_pid = ttybase_device_getfproc(term);
	if (fg_pid) {
		REF struct task *fg;
		FINALLY_DECREF_UNLIKELY(fg_pid);
		fg = taskpid_gettask(fg_pid);
		if likely(fg) {
			FINALLY_DECREF_UNLIKELY(fg);
			task_raisesignalprocessgroup(fg, signo);
		}
	}
	return 0;
}

/* Check if the calling thread is allowed to read from `self'
 * This function must be called by read-operator overrides! */
PUBLIC void KCALL
kernel_terminal_check_sigttin(struct terminal *__restrict self) {
	kernel_terminal_check_sigtty(self, false);
}

/* Default character-device read/write operator implementations for tty devices
 * These functions will call forward to `terminal_iread()' and `terminal_owrite()' */
PUBLIC NONNULL((1)) size_t KCALL
ttybase_device_iread(struct character_device *__restrict self,
                     USER CHECKED void *dst,
                     size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	struct ttybase_device *me;
	assert(character_device_isattybase(self));
	me = (struct ttybase_device *)self;
	kernel_terminal_check_sigtty(&me->t_term, false);
	result = terminal_iread(&me->t_term, dst, num_bytes, mode);
	assert(result <= num_bytes);
	return result;
}

PUBLIC NONNULL((1)) size_t KCALL
ttybase_device_owrite(struct character_device *__restrict self,
                      USER CHECKED void const *src,
                      size_t num_bytes, iomode_t mode) THROWS(...) {
	ssize_t result;
	struct ttybase_device *me;
	assert(character_device_isattybase(self));
	me     = (struct ttybase_device *)self;
	result = terminal_owrite(&me->t_term, src, num_bytes, mode);
	assert((size_t)result <= num_bytes);
	return (size_t)result;
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ttybase_device_fini)(struct character_device *__restrict self) {
	struct ttybase_device *me;
	me = (struct ttybase_device *)self;
	assertf(!me->t_cproc.m_pointer,
	        "An session leader should be holding a reference to their CTTY, "
	        "meaning that if we truely were supposed to be a CTTY, the associated "
	        "session should have kept us from being destroyed");
	terminal_fini(&me->t_term);
	xatomic_ref_fini(&me->t_fproc);
}


LOCAL void KCALL
termios_to_termios2(USER CHECKED struct termios2 *__restrict dst,
                    USER CHECKED struct termios const *__restrict src) {
	dst->c_iflag = src->c_iflag;
	dst->c_oflag = src->c_oflag;
	dst->c_cflag = src->c_cflag;
	dst->c_lflag = src->c_lflag;
	dst->c_line  = src->c_line;
	{
		STATIC_ASSERT(sizeof(dst->c_cc) <= sizeof(src->c_cc));
		memcpy(dst->c_cc, src->c_cc, sizeof(dst->c_cc));
	}
	dst->c_ispeed = src->c_ispeed;
	dst->c_ospeed = src->c_ospeed;
}

LOCAL void KCALL
termios2_to_termios(USER CHECKED struct termios *__restrict dst,
                    USER CHECKED struct termios2 const *__restrict src) {
	dst->c_iflag = src->c_iflag;
	dst->c_oflag = src->c_oflag;
	dst->c_cflag = src->c_cflag;
	dst->c_lflag = src->c_lflag;
	dst->c_line  = src->c_line;
	{
		STATIC_ASSERT(sizeof(src->c_cc) <= sizeof(dst->c_cc));
		memcpy(dst->c_cc, src->c_cc, sizeof(src->c_cc));
		memset((byte_t *)dst->c_cc +  sizeof(src->c_cc), 0,
		       sizeof(dst->c_cc) - sizeof(src->c_cc));
	}
	dst->c_ispeed = src->c_ispeed;
	dst->c_ospeed = src->c_ospeed;
}

LOCAL void KCALL
termios_to_termio(USER CHECKED struct termio *__restrict dst,
                  USER CHECKED struct termios const *__restrict src) {
	dst->c_iflag = (u16)src->c_iflag;
	dst->c_oflag = (u16)src->c_oflag;
	dst->c_cflag = (u16)src->c_cflag;
	dst->c_lflag = (u16)src->c_lflag;
	dst->c_line  = (u8)src->c_line;
	{
		STATIC_ASSERT(sizeof(dst->c_cc) <= sizeof(src->c_cc));
		memcpy(dst->c_cc, src->c_cc, sizeof(dst->c_cc));
	}
}

LOCAL void KCALL
termio_to_termios(USER CHECKED struct termios *__restrict dst,
                  USER CHECKED struct termio const *__restrict src) {
	dst->c_iflag = src->c_iflag;
	dst->c_oflag = src->c_oflag;
	dst->c_cflag = src->c_cflag;
	dst->c_lflag = src->c_lflag;
	dst->c_line  = src->c_line;
	{
		STATIC_ASSERT(sizeof(src->c_cc) <= sizeof(dst->c_cc));
		memcpy(dst->c_cc, src->c_cc, sizeof(src->c_cc));
		memset((byte_t *)dst->c_cc +  sizeof(src->c_cc), 0,
		       sizeof(dst->c_cc) - sizeof(src->c_cc));
	}
	dst->c_ispeed = 0;
	dst->c_ospeed = 0;
}

LOCAL void KCALL
termios_to_termiox(USER CHECKED struct termiox *__restrict dst,
                   USER CHECKED struct termios const *__restrict src) {
	/* I have no idea if this flag-mapping is even correct... */
	dst->x_hflag = (u16)src->c_iflag;
	dst->x_cflag = (u16)src->c_oflag;
	dst->x_sflag = (u16)src->c_lflag;
	{
		STATIC_ASSERT(sizeof(dst->x_rflag) <= sizeof(src->c_cc));
		memcpy(dst->x_rflag, src->c_cc, sizeof(dst->x_rflag));
	}
}

LOCAL void KCALL
termiox_to_termios(USER CHECKED struct termios *__restrict dst,
                   USER CHECKED struct termiox const *__restrict src) {
	dst->c_iflag = src->x_hflag;
	dst->c_oflag = src->x_cflag;
	dst->c_lflag = src->x_sflag;
	dst->c_cflag = 0;
	dst->c_line  = 0;
	{
		STATIC_ASSERT(sizeof(src->x_rflag) <= sizeof(dst->c_cc));
		memcpy(dst->c_cc, src->x_rflag, sizeof(src->x_rflag));
		memset((byte_t *)dst->c_cc +  sizeof(src->x_rflag), 0,
		       sizeof(dst->c_cc) - sizeof(src->x_rflag));
	}
	dst->c_ispeed = 0;
	dst->c_ospeed = 0;
}




PUBLIC NONNULL((1)) syscall_slong_t KCALL /* @return: -EINVAL: Unsupported `cmd' */
ttybase_device_tryioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                        USER UNCHECKED void *arg, iomode_t UNUSED(mode)) THROWS(...) {
	struct ttybase_device *me;
	assert(character_device_isattybase(self));
	me = (struct ttybase_device *)self;
	switch (cmd) {

	case TCGETS:
	case _IOR(_IOC_TYPE(TCGETS), _IOC_NR(TCGETS), struct termio):
		validate_writable(arg, sizeof(struct termio));
		COMPILER_WRITE_BARRIER();
		termios_to_termio((USER CHECKED struct termio *)arg, &me->t_term.t_ios);
		break;

	case _IOW(_IOC_TYPE(TCSETS), _IOC_NR(TCSETS), struct termio):
		cmd = TCSETS;
		goto do_TCSETS;
	case _IOW(_IOC_TYPE(TCSETSW), _IOC_NR(TCSETSW), struct termio):
		cmd = TCSETSW;
		goto do_TCSETS;
	case _IOW(_IOC_TYPE(TCSETSF), _IOC_NR(TCSETSF), struct termio):
		cmd = TCSETSF;
		goto do_TCSETS;
	case TCSETS:
	case TCSETSW:
	case TCSETSF:
do_TCSETS: {
		struct termios new_io;
		validate_readable(arg, sizeof(struct termio));
		COMPILER_READ_BARRIER();
		termio_to_termios(&new_io, (USER CHECKED struct termio *)arg);
		COMPILER_READ_BARRIER();
		/* DRIVER: if (cmd != TCSETS) WAIT_FOR_UNWRITTEN_DATA_TO_BE_TRANSMITTED(); */
		if (cmd == TCSETSW) /* Clear the input buffer */
			ringbuffer_setwritten(&me->t_term.t_ibuf, 0);
		terminal_setios(&me->t_term, &new_io, NULL);
	}	break;

	case TCGETA:
	case _IOR(_IOC_TYPE(TCGETA), _IOC_NR(TCGETA), struct termios):
		validate_writable(arg, sizeof(struct termios));
		COMPILER_WRITE_BARRIER();
		memcpy(arg, &me->t_term.t_ios, sizeof(struct termios));
		break;

	case _IOW(_IOC_TYPE(TCSETA), _IOC_NR(TCSETA), struct termios):
		cmd = TCSETA;
		goto do_TCSETA;
	case _IOW(_IOC_TYPE(TCSETAW), _IOC_NR(TCSETAW), struct termios):
		cmd = TCSETAW;
		goto do_TCSETA;
	case _IOW(_IOC_TYPE(TCSETAF), _IOC_NR(TCSETAF), struct termios):
		cmd = TCSETAF;
		goto do_TCSETA;
	case TCSETA:
	case TCSETAW:
	case TCSETAF:
do_TCSETA: {
		struct termios new_io;
		validate_readable(arg, sizeof(struct termios));
		COMPILER_READ_BARRIER();
		memcpy(&new_io, arg, sizeof(struct termios));
		COMPILER_READ_BARRIER();
		/* DRIVER: if (cmd != TCSETA) WAIT_FOR_UNWRITTEN_DATA_TO_BE_TRANSMITTED(); */
		if (cmd == TCSETAW) /* Clear the input buffer */
			ringbuffer_setwritten(&me->t_term.t_ibuf, 0);
		terminal_setios(&me->t_term, &new_io, NULL);
	}	break;


	case TCGETS2:
		validate_writable(arg, sizeof(struct termios2));
		COMPILER_WRITE_BARRIER();
		termios_to_termios2((USER CHECKED struct termios2 *)arg, &me->t_term.t_ios);
		break;

	case TCSETS2:
	case TCSETSW2:
	case TCSETSF2: {
		struct termios new_io;
		validate_readable(arg, sizeof(struct termios2));
		COMPILER_READ_BARRIER();
		termios2_to_termios(&new_io, (USER CHECKED struct termios2 *)arg);
		COMPILER_READ_BARRIER();
		/* DRIVER: if (cmd != TCSETS2) WAIT_FOR_UNWRITTEN_DATA_TO_BE_TRANSMITTED(); */
		if (cmd == TCSETSW2) /* Clear the input buffer */
			ringbuffer_setwritten(&me->t_term.t_ibuf, 0);
		terminal_setios(&me->t_term, &new_io, NULL);
	}	break;

	case TCFLSH:
		/* Discard data received, but not read (aka. what the driver send) */
		switch ((uintptr_t)arg) {

		case TCIFLUSH:
			linebuffer_clear(&me->t_term.t_ipend);
			ringbuffer_setwritten(&me->t_term.t_ibuf, 0);
			break;

		case TCOFLUSH:
			linebuffer_clear(&me->t_term.t_opend);
			/* DRIVER: CLEAR_NON_TRANSMITTED_OUTPUT_BUFFER(); */
			break;

		case TCIOFLUSH:
			linebuffer_clear(&me->t_term.t_ipend);
			ringbuffer_setwritten(&me->t_term.t_ibuf, 0);
			linebuffer_clear(&me->t_term.t_opend);
			/* DRIVER: CLEAR_NON_TRANSMITTED_OUTPUT_BUFFER(); */
			break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_TCFLSH_COMMAND,
			      (uintptr_t)arg);
			break;
		}
		break;

	case TIOCSPGRP:
	case _IOW(_IOC_TYPE(TIOCSPGRP), _IOC_NR(TIOCSPGRP), upid_t): {
		upid_t pid;
		REF struct taskpid *oldpid;
		REF struct taskpid *newpid;
		REF struct task *newthread;
		REF struct task *newgroup;
		validate_readable(arg, sizeof(upid_t));
		COMPILER_READ_BARRIER();
		pid = *(USER CHECKED upid_t *)arg;
		COMPILER_READ_BARRIER();
		newthread = pid == 0
		            ? incref(THIS_TASK)
		            : pidns_lookup_task(THIS_PIDNS, pid);
		/* Always assign the taskpid of a process group leader! */
		{
			FINALLY_DECREF_UNLIKELY(newthread);
			newgroup = task_getprocessgroupleader_of(newthread);
		}
		newpid = incref(FORTASK(newgroup, this_taskpid));
		decref_unlikely(newgroup);
		printk(KERN_INFO "[tty:%q] Set foreground process group to %p [tid=%u]\n",
		       me->cd_name, newgroup, (unsigned int)taskpid_getrootpid(newpid));
		oldpid = me->t_fproc.exchange_inherit_new(newpid);
		xdecref(oldpid);
	}	break;

	case TIOCGPGRP:
	case _IOR(_IOC_TYPE(TIOCGPGRP), _IOC_NR(TIOCGPGRP), upid_t): {
		upid_t respid;
		REF struct taskpid *tpid;
		validate_writable(arg, sizeof(upid_t));
		respid = (upid_t)-ESRCH;
		tpid = me->t_fproc.get();
		if (tpid) {
			respid = taskpid_getpid(tpid);
			decref_unlikely(tpid);
		}
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED upid_t *)arg = respid;
	}	break;

	case TIOCGSID:
	case _IOR(_IOC_TYPE(TIOCGSID), _IOC_NR(TIOCGSID), upid_t): {
		upid_t respid;
		REF struct taskpid *tpid;
		validate_writable(arg, sizeof(upid_t));
		respid = (upid_t)-ENOTTY;
		tpid = me->t_cproc.get();
		if (tpid) {
			respid = taskpid_getpid(tpid);
			decref_unlikely(tpid);
		}
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED upid_t *)arg = respid;
	}	break;

	case TIOCSETD:
	case _IOW(_IOC_TYPE(TIOCSETD), _IOC_NR(TIOCSETD), int):
	case _IOW(_IOC_TYPE(TIOCSETD), _IOC_NR(TIOCSETD), cc_t):
		validate_readable(arg, sizeof(cc_t));
		ATOMIC_WRITE(me->t_term.t_ios.c_line, *(cc_t *)arg);
		/* DRIVER: UPDATE_LINE_DISCIPLINE(); */
		break;

	case TIOCGETD:
	case _IOR(_IOC_TYPE(TIOCGETD), _IOC_NR(TIOCGETD), int):
		validate_writable(arg, sizeof(int));
		*(USER CHECKED int *)arg = ATOMIC_READ(me->t_term.t_ios.c_line);
		break;

	case _IOR(_IOC_TYPE(TIOCGETD), _IOC_NR(TIOCGETD), cc_t):
		validate_writable(arg, sizeof(cc_t));
		*(USER CHECKED cc_t *)arg = ATOMIC_READ(me->t_term.t_ios.c_line);
		break;

	case TCSBRK:
		if (arg) {
			/* DRIVER: WAIT_FOR_UNWRITTEN_DATA_TO_BE_TRANSMITTED() */
			break;
		}
		ATTR_FALLTHROUGH
	case TCSBRKP:
		/* DRIVER: SEND_BREAK_CHARACTER() */
		break;

	case TIOCSBRK:
	case TIOCCBRK:
		/* DRIVER: TURN_BREAK_CHARACTERS_ON_OR_OFF() */
		break;

	case TCXONC:
		switch ((uintptr_t)arg) {

		case TCOOFF:
			ATOMIC_FETCHOR(me->t_term.t_ios.c_iflag, IXOFF);
			break;

		case TCOON:
			if (ATOMIC_FETCHAND(me->t_term.t_ios.c_iflag, ~IXOFF) & IXOFF)
				sig_broadcast(&me->t_term.t_opend.lb_nful);
			break;

		case TCIOFF:
			ATOMIC_FETCHOR(me->t_term.t_ios.c_iflag, __IIOFF);
			break;

		case TCION:
			if (ATOMIC_FETCHAND(me->t_term.t_ios.c_iflag, ~__IIOFF) & __IIOFF)
				sig_broadcast(&me->t_term.t_ibuf.rb_nfull);
			break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_TCXONC_COMMAND,
			      (uintptr_t)arg);
			break;
		}
		break;

	case FIONREAD:
	case _IOR(_IOC_TYPE(FIONREAD), _IOC_NR(FIONREAD), unsigned int):
		validate_writable(arg, sizeof(unsigned int));
		*(USER CHECKED unsigned int *)arg = (unsigned int)ATOMIC_READ(me->t_term.t_ibuf.rb_avail);
		break;
#if __SIZEOF_SIZE_T__ != __SIZEOF_INT__
	case _IOR(_IOC_TYPE(FIONREAD), _IOC_NR(FIONREAD), size_t):
		validate_writable(arg, sizeof(size_t));
		*(USER CHECKED size_t *)arg = ATOMIC_READ(me->t_term.t_ibuf.rb_avail);
		break;
#endif /* __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */

	case TIOCOUTQ:
	case _IOR(_IOC_TYPE(TIOCOUTQ), _IOC_NR(TIOCOUTQ), int):
		validate_writable(arg, sizeof(unsigned int));
		*(USER CHECKED unsigned int *)arg = (unsigned int)ATOMIC_READ(me->t_term.t_opend.lb_line.lc_size);
		break;
#if __SIZEOF_SIZE_T__ != __SIZEOF_INT__
	case _IOR(_IOC_TYPE(TIOCOUTQ), _IOC_NR(TIOCOUTQ), size_t):
		validate_writable(arg, sizeof(size_t));
		*(USER CHECKED size_t *)arg = ATOMIC_READ(me->t_term.t_opend.lb_line.lc_size);
		break;
#endif /* __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */

	case FIOQSIZE:
	case _IOR(_IOC_TYPE(FIOQSIZE), _IOC_NR(FIOQSIZE), loff_t):
		validate_writable(arg, sizeof(loff_t));
		*(USER CHECKED loff_t *)arg = ATOMIC_READ(me->t_term.t_ibuf.rb_avail) +
		                              ATOMIC_READ(me->t_term.t_ipend.lb_line.lc_size) +
		                              ATOMIC_READ(me->t_term.t_canon.lb_line.lc_size);
		break;

	case TIOCSTI:
	case _IOW(_IOC_TYPE(TIOCSTI), _IOC_NR(TIOCSTI), char):
		validate_readable(arg, sizeof(byte_t));
		ringbuffer_write(&me->t_term.t_ibuf, arg, 1);
		break;

	case TIOCGSOFTCAR:
	case _IOR(_IOC_TYPE(TIOCGSOFTCAR), _IOC_NR(TIOCGSOFTCAR), int):
		validate_writable(arg, sizeof(int));
		*(USER CHECKED int *)arg = ATOMIC_READ(me->t_term.t_ios.c_cflag) & CLOCAL ? 1 : 0;
		break;

	case TIOCSSOFTCAR:
	case _IOW(_IOC_TYPE(TIOCSSOFTCAR), _IOC_NR(TIOCSSOFTCAR), int): {
		int lcmode;
		validate_writable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		lcmode = *(USER CHECKED int *)arg;
		COMPILER_READ_BARRIER();
		if (lcmode) {
			ATOMIC_FETCHOR(me->t_term.t_ios.c_cflag, CLOCAL);
		} else {
			ATOMIC_FETCHAND(me->t_term.t_ios.c_cflag, ~CLOCAL);
		}
	}	break;

	/* XXX: Exclusive terminal mode enabled with `TIOCEXCL' */
	/* XXX: Exclusive terminal mode disabled with `TIOCNXCL' */
	/* XXX: Exclusive terminal mode tested with `TIOCGEXCL' */

	case TIOCSCTTY: {
		int error;
		error = ttybase_device_setctty(me,
		                               true,
		                               cred_allow_ctty_stealing() && (uintptr_t)arg != 0,
		                               false);
		if (error == TTYBASE_DEVICE_SETCTTY_INUSE)
			THROW(E_INSUFFICIENT_RIGHTS_CTTY_STEALING);
		if (error == TTYBASE_DEVICE_SETCTTY_DIFFERENT)
			THROW(E_INVALID_CONTEXT_CTTY_ALREADY_ASSIGNED);
		if (error == TTYBASE_DEVICE_SETCTTY_NOTLEADER)
			THROW(E_INVALID_CONTEXT_NOT_SESSION_LEADER);
	}	break;

	case TIOCNOTTY: {
		int error;
		error = ttybase_device_hupctty(me);
		if (error == TTYBASE_DEVICE_HUPCTTY_NOTLEADER)
			THROW(E_INVALID_CONTEXT_NOT_SESSION_LEADER);
		if (error == TTYBASE_DEVICE_HUPCTTY_DIFFERENT)
			THROW(E_INVALID_CONTEXT_CTTY_DIFFERS);
	}	break;

	/* XXX: TIOCMGET: Modem bits? */
	/* XXX: TIOCMBIS: Modem bits? */
	/* XXX: TIOCMBIC: Modem bits? */
	/* XXX: TIOCMSET: Modem bits? */
	
	/* XXX: TIOCCONS: Set this tty as the one bound to /dev/console (and /dev/tty0) */

	case TCGETX:
	case _IOR(_IOC_TYPE(TCGETX), _IOC_NR(TCGETX), struct termiox):
		validate_writable(arg, sizeof(struct termiox));
		COMPILER_WRITE_BARRIER();
		termios_to_termiox((USER CHECKED struct termiox *)arg, &me->t_term.t_ios);
		break;

	case _IOW(_IOC_TYPE(TCSETX), _IOC_NR(TCSETX), struct termiox):
		cmd = TCSETX;
		goto do_TCSETX;
	case _IOW(_IOC_TYPE(TCSETXF), _IOC_NR(TCSETXF), struct termiox):
		cmd = TCSETXF;
		goto do_TCSETX;
	case _IOW(_IOC_TYPE(TCSETXW), _IOC_NR(TCSETXW), struct termiox):
		cmd = TCSETXW;
		goto do_TCSETX;
	case TCSETX:
	case TCSETXF:
	case TCSETXW:
do_TCSETX: {
		struct termios new_io;
		validate_readable(arg, sizeof(struct termiox));
		COMPILER_READ_BARRIER();
		termiox_to_termios(&new_io, (USER CHECKED struct termiox *)arg);
		COMPILER_READ_BARRIER();
		/* DRIVER: if (cmd != TCSETS) WAIT_FOR_UNWRITTEN_DATA_TO_BE_TRANSMITTED(); */
		if (cmd == TCSETXF) /* Clear the input buffer */
			ringbuffer_setwritten(&me->t_term.t_ibuf, 0);
		terminal_setios(&me->t_term, &new_io, NULL);
	}	break;

	case TIOCSIG: {
		int signo;
		validate_readable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		signo = *(USER CHECKED int *)arg;
		COMPILER_READ_BARRIER();
		if unlikely(signo == 0 || signo >= NSIG) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
			      signo);
		}
		kernel_terminal_raise(&me->t_term, (unsigned int)signo);
	}	break;

	/* XXX: TIOCVHANGUP? */

	default:
		return -EINVAL;
	}
	return 0;
}

PUBLIC NONNULL((1)) syscall_slong_t KCALL
ttybase_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                     USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	syscall_slong_t result;
	result = ttybase_device_tryioctl(self, cmd, arg, mode);
	if (result == -EINVAL) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}

PUBLIC NONNULL((1)) poll_mode_t KCALL
ttybase_device_poll(struct character_device *__restrict self,
                    poll_mode_t what) THROWS(...) {
	int error;
	struct ttybase_device *me;
	assert(character_device_isattybase(self));
	me = (struct ttybase_device *)self;
	if (what & POLLIN) {
		error = terminal_poll_iread(&me->t_term);
		if (error == TERMINAL_POLL_NONBLOCK)
			return POLLIN;
	}
	if (what & POLLOUT) {
		error = terminal_poll_owrite(&me->t_term);
		if (error == TERMINAL_POLL_NONBLOCK)
			return POLLOUT;
	}
	return 0;
}


PUBLIC NONNULL((1)) void KCALL
ttybase_device_stat(struct character_device *__restrict self,
                    USER CHECKED struct stat *result) THROWS(...) {
	struct ttybase_device *me;
	assert(character_device_isattybase(self));
	me = (struct ttybase_device *)self;
	/* Try to give user-space an estimate on the number of unread input bytes. */
	result->st_size = ATOMIC_READ(me->t_term.t_ibuf.rb_avail) +
	                  ATOMIC_READ(me->t_term.t_ipend.lb_line.lc_size) +
	                  ATOMIC_READ(me->t_term.t_canon.lb_line.lc_size);
}

/* [IMPL(TIOCSCTTY)] Set the given tty device as the controlling terminal of the calling session.
 * @param: steal_from_other_session: Allow the terminal to be stolen from another session.
 * @param: override_different_ctty:  If the calling session already had a CTTY assigned, override it.
 * @return: * : One of `TTYBASE_DEVICE_SETCTTY_*' */
PUBLIC NOBLOCK int
NOTHROW(KCALL ttybase_device_setctty)(struct ttybase_device *__restrict self,
                                      bool caller_must_be_leader,
                                      bool steal_from_other_session,
                                      bool override_different_ctty) {
	struct task *proc;
	REF struct task *session;
	struct taskpid *session_pid;
	assert(self);
	assert(character_device_isattybase(self));
	proc = task_getprocess();
	session = task_getsessionleader_of(proc);
	FINALLY_DECREF_UNLIKELY(session);
	if unlikely(session != proc && caller_must_be_leader)
		return TTYBASE_DEVICE_SETCTTY_NOTLEADER;
	session_pid = FORTASK(session, this_taskpid);
again_check_tg_ctty:
	if (ATOMIC_READ(FORTASK(session, this_taskgroup).tg_ctty.m_pointer) != NULL) {
		auto &my_ctty_pointer = __TASK_CTTY_FIELD(session);
		REF struct ttybase_device *old_ctty;
		old_ctty = my_ctty_pointer.get();
		if likely(old_ctty) {
			FINALLY_DECREF_UNLIKELY(old_ctty);
			if (old_ctty == self)
				return TTYBASE_DEVICE_SETCTTY_ALREADY;
			if (!override_different_ctty)
				return TTYBASE_DEVICE_SETCTTY_DIFFERENT;
again_check_t_cproc_inner:
			if unlikely(ATOMIC_READ(self->t_cproc.m_pointer) != NULL) {
				REF struct taskpid *old_cproc;
				old_cproc = self->t_cproc.get();
				if (old_cproc) {
					FINALLY_DECREF_UNLIKELY(old_cproc);
					if unlikely(old_cproc == session_pid)
						return TTYBASE_DEVICE_SETCTTY_ALREADY;
					if (!steal_from_other_session)
						return TTYBASE_DEVICE_SETCTTY_INUSE;
					/* Change the TTY's session pointer to the new session. */
					if unlikely(!self->t_cproc.cmpxch(old_cproc, session_pid))
						goto again_check_t_cproc_inner;
					/* Set the TTY link of the new session task descriptor. */
					if unlikely(!my_ctty_pointer.cmpxch(old_ctty, self)) {
						self->t_cproc.cmpxch(session_pid, old_cproc);
						goto again_check_tg_ctty;
					}
					{
						/* Delete the TTY link from the old session task descriptor */
						REF struct task *old_cproc_task;
						old_cproc_task = taskpid_gettask(old_cproc);
						if likely(old_cproc_task) {
							auto &old_ctty_pointer = __TASK_CTTY_FIELD(old_cproc_task);
							if (old_ctty_pointer.cmpxch(self, NULL))
								ttybase_log_delsession(self, old_cproc_task, old_cproc);
							decref_unlikely(old_cproc_task);
						}
					}
					goto remove_from_old_ctty_and_succeed;
				}
			}
			/* Change the TTY's session pointer to the new session. */
			if unlikely(!self->t_cproc.cmpxch(NULL, session_pid))
				goto again_check_t_cproc_inner;
			/* Change the calling session's CTTY link to the new TTY */
			if unlikely(!my_ctty_pointer.cmpxch(old_ctty, self)) {
				self->t_cproc.cmpxch(session_pid, NULL);
				goto again_check_tg_ctty;
			}
remove_from_old_ctty_and_succeed:
			/* Remove the calling session from the old TTY's session link */
			if (old_ctty->t_cproc.cmpxch(session_pid, NULL))
				ttybase_log_delsession(old_ctty, session, session_pid);
			ttybase_log_setsession(self, session, session_pid);
			return TTYBASE_DEVICE_SETCTTY_SUCCESS;
		}
	}
again_check_t_cproc:
	if unlikely(ATOMIC_READ(self->t_cproc.m_pointer) != NULL) {
		REF struct taskpid *old_cproc;
		old_cproc = self->t_cproc.get();
		if (old_cproc) {
			FINALLY_DECREF_UNLIKELY(old_cproc);
			if unlikely(old_cproc == session_pid)
				return TTYBASE_DEVICE_SETCTTY_ALREADY;
			if (!steal_from_other_session)
				return TTYBASE_DEVICE_SETCTTY_INUSE;
			/* Change the TTY's session pointer to the new session. */
			if unlikely(!self->t_cproc.cmpxch(old_cproc, session_pid))
				goto again_check_t_cproc;
			{
				/* Set the TTY link of the new session task descriptor. */
				auto &my_ctty_pointer = __TASK_CTTY_FIELD(session);
				if unlikely(!my_ctty_pointer.cmpxch(NULL, self)) {
					self->t_cproc.cmpxch(session_pid, old_cproc);
					goto again_check_tg_ctty;
				}
			}
			{
				/* Delete the TTY link from the old session task descriptor */
				REF struct task *old_cproc_task;
				old_cproc_task = taskpid_gettask(old_cproc);
				if likely(old_cproc_task) {
					auto &old_ctty_pointer = __TASK_CTTY_FIELD(old_cproc_task);
					if (old_ctty_pointer.cmpxch(self, NULL))
						ttybase_log_delsession(self, old_cproc_task, old_cproc);
					decref_unlikely(old_cproc_task);
				}
			}
			ttybase_log_setsession(self, session, session_pid);
			return TTYBASE_DEVICE_SETCTTY_SUCCESS;
		}
	}
	/* Set the TTY's session pointer to the calling session. */
	if (!self->t_cproc.cmpxch(NULL, session_pid))
		goto again_check_t_cproc;
	{
		/* Set the TTY link of the session task descriptor. */
		auto &my_ctty_pointer = __TASK_CTTY_FIELD(session);
		if unlikely(!my_ctty_pointer.cmpxch(NULL, self)) {
			self->t_cproc.cmpxch(FORTASK(session, this_taskpid), NULL);
			goto again_check_tg_ctty;
		}
		ttybase_log_setsession(self, session, session_pid);
	}
	return TTYBASE_DEVICE_SETCTTY_SUCCESS;
}

/* [IMPL(TIOCNOTTY)] Give up the controlling terminal of the calling session.
 * @param: old_ctty:  The expected old CTTY, or NULL if the CTTY should always be given up.
 * @param: pold_ctty: When non-NULL, store the old CTTY here upon success.
 * @return: * : One of `TTYBASE_DEVICE_HUPCTTY_*' */
PUBLIC NOBLOCK int
NOTHROW(KCALL ttybase_device_hupctty)(struct ttybase_device *required_old_ctty,
                                      bool caller_must_be_leader,
                                      REF struct ttybase_device **pold_ctty) {
	struct task *proc;
	struct taskpid *session_pid;
	REF struct task *session;
	assert(!required_old_ctty || character_device_isattybase(required_old_ctty));
	proc = task_getprocess();
	session = task_getsessionleader_of(proc);
	FINALLY_DECREF_UNLIKELY(session);
	if unlikely(session != proc && caller_must_be_leader)
		return TTYBASE_DEVICE_HUPCTTY_NOTLEADER;
	session_pid = FORTASK(session, this_taskpid);
	if (required_old_ctty) {
		auto &my_ctty_pointer = __TASK_CTTY_FIELD(session);
again_my_ctty_pointer_cmpxch:
		if (!my_ctty_pointer.cmpxch(required_old_ctty, NULL)) {
			struct ttybase_device *old_ctty;
			old_ctty = ATOMIC_READ(my_ctty_pointer.m_pointer);
			if (old_ctty == NULL)
				return TTYBASE_DEVICE_HUPCTTY_ALREADY;
			if (old_ctty == required_old_ctty)
				goto again_my_ctty_pointer_cmpxch;
			return TTYBASE_DEVICE_HUPCTTY_DIFFERENT;
		}
		if (required_old_ctty->t_cproc.cmpxch(session_pid, NULL))
			ttybase_log_delsession(required_old_ctty, session, session_pid);
		if (pold_ctty) {
			incref(required_old_ctty);
			*pold_ctty = required_old_ctty;
		}
	} else {
		REF struct ttybase_device *old_ctty;
		auto &my_ctty_pointer = __TASK_CTTY_FIELD(session);
		old_ctty = my_ctty_pointer.exchange(NULL);
		if (!old_ctty)
			return TTYBASE_DEVICE_HUPCTTY_ALREADY;
		if (old_ctty->t_cproc.cmpxch(session_pid, NULL))
			ttybase_log_delsession(old_ctty, session, session_pid);
		if (pold_ctty) {
			*pold_ctty = old_ctty;
		} else {
			decref(old_ctty);
		}
	}
	return TTYBASE_DEVICE_HUPCTTY_SUCCESS;
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_TTYBASE_C */
