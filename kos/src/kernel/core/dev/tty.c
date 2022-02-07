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
#ifndef GUARD_KERNEL_SRC_DEV_TTY_C
#define GUARD_KERNEL_SRC_DEV_TTY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group-ctty.h>
#include <sched/group.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h> /* task_serve() */
#include <sched/sigaction.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <compat/config.h>
#include <compat/kos/types.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <kos/ioctl/tty.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/termiox.h> /* struct termiox */
#include <sys/types.h>   /* loff_t */

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <termios.h>

#include <libterm/termio.h>

DECL_BEGIN

#ifdef CONFIG_USE_NEW_GROUP
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL ttydev_log_setsession)(struct ttydev *__restrict self,
                                     struct procgrp *__restrict session) {
	device_getname_lock_acquire(self);
	printk(KERN_NOTICE "[ctty][+] Assign tty %q as controller for session %u\n",
	       device_getname(self), procgrp_getrootpgid(session));
	device_getname_lock_release(self);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL ttydev_log_delsession)(struct ttydev *__restrict self,
                                     struct procgrp *__restrict session) {
	device_getname_lock_acquire(self);
	printk(KERN_NOTICE "[ctty][-] Remove tty %q as controller for session %u\n",
	       device_getname(self), procgrp_getrootpgid(session));
	device_getname_lock_release(self);
}
#else /* CONFIG_USE_NEW_GROUP */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(KCALL ttydev_log_setsession)(struct ttydev *__restrict self,
                                     struct task *__restrict UNUSED(session),
                                     struct taskpid *__restrict session_pid) {
	device_getname_lock_acquire(self);
	printk(KERN_NOTICE "[ctty][+] Assign tty %q as controller for session %u\n",
	       device_getname(self), taskpid_getroottid(session_pid));
	device_getname_lock_release(self);
}

PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(KCALL ttydev_log_delsession)(struct ttydev *__restrict self,
                                     struct task *__restrict UNUSED(session),
                                     struct taskpid *__restrict session_pid) {
	device_getname_lock_acquire(self);
	printk(KERN_NOTICE "[ctty][-] Remove tty %q as controller for session %u\n",
	       device_getname(self), taskpid_getroottid(session_pid));
	device_getname_lock_release(self);
}
#endif /* !CONFIG_USE_NEW_GROUP */


#ifdef CONFIG_USE_NEW_GROUP
/* Chechk if the given `signo' is marked, or handled as SIG_IGN */
PRIVATE WUNUSED bool FCALL
is_signal_ignored(signo_t signo)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	bool result;
	struct sighand_ptr *handptr;
	struct sighand *hand;
	if (sigmask_ismasked(signo))
		return true;
	handptr = THIS_SIGHAND_PTR;
	if (!handptr)
		return false;
	hand = sighand_ptr_lockread(handptr);
	if unlikely(!hand)
		return false;
	result = hand->sh_actions[signo - 1].sa_handler == SIG_IGN;
	sync_endread(hand);
	return result;
}
#endif /* CONFIG_USE_NEW_GROUP */

/* @param: signo: One of `SIGTTOU' or `SIGTTIN' */
PRIVATE NONNULL((1)) void KCALL
kernel_terminal_check_sigtty(struct ttydev *__restrict self,
                             signo_t signo) {
#ifdef CONFIG_USE_NEW_GROUP
	struct taskpid *mypid = task_gettaskpid();
	struct procgrp *fggrp;
	REF struct procgrp *mygrp;
	assert(chrdev_istty(self));
again:
	fggrp = awref_ptr(&self->t_fproc);
	mygrp = taskpid_getprocgrpptr(mypid);
	if likely(mygrp == fggrp)
		return; /* Caller is part of foreground process group. */
	if unlikely(!fggrp)
		return; /* Also done by linux: if no foreground group is set, allow access */
	mygrp = taskpid_getprocgrp(mypid);
	FINALLY_DECREF_UNLIKELY(mygrp);
	if (mygrp == fggrp)
		return; /* Caller is part of foreground process group. */
	if (axref_ptr(&mygrp->pgr_session->ps_ctty) != self) {
		/* Allow TTY access from processes outside the controlling
		 * session. POSIX appears silent on  what to do here,  but
		 * looking at the linux kernel sources, we find:
		 * drivers/tty/tty_jobctrl.c:__tty_check_change:
		 * >> if (current->signal->tty != tty)
		 * >>     return 0;
		 * Which seems to imply that TTY access is granted if the
		 * calling process doesn't have the given TTY set as  the
		 * controlling TTY. */
		return;
	}
	device_getname_lock_acquire(self);
	printk(KERN_INFO "[tty:%q] Background process group %" PRIuN(__SIZEOF_PID_T__) " "
	                 "[sid:%" PRIuN(__SIZEOF_PID_T__) "] tried to %s\n",
	       device_getname(self), procgrp_getrootpgid(mygrp), procgrp_getrootsid(mygrp),
	       signo == SIGTTIN ? "read" : "write");
	device_getname_lock_release(self);

	/* ...  Attempts by a process in a background process group to write to its controlling
	 * terminal shall cause the process group to be sent a SIGTTOU signal unless one of the
	 * following special cases applies:
	 *   - If [...] the process is ignoring or blocking the SIGTTOU signal, the process
	 *     is allowed to  write to the  terminal and  the SIGTTOU signal  is not  sent.
	 *   - If [...] the  process group of  the writing  process is orphaned,  and the  writing
	 *     process is not ignoring or blocking the SIGTTOU signal, the write() shall return -1
	 *     with errno set to [EIO] and no signal shall be sent */
	if (is_signal_ignored(signo)) {
		if (signo == SIGTTIN) {
			/* ...  if the reading process is ignoring or blocking the SIGTTIN signal, or if
			 * the process group of the reading process is orphaned, the read() shall return
			 * -1, with errno set to [EIO] and no signal shall be sent. */
do_throw_E_IOERROR_REASON_TTY_ORPHAN_SIGTTIN:
			THROW(E_IOERROR_NODATA,
			      E_IOERROR_SUBSYSTEM_TTY,
			      E_IOERROR_REASON_TTY_SIGTTIN);
		}
		return;
	}

	procgrp_memb_read(mygrp);
	/* Check that `mygrp' still is the caller's process group. */
	if unlikely(mygrp != taskpid_getprocgrpptr(mypid)) {
		procgrp_memb_endread(mygrp);
		goto again;
	}
	if (!procgrp_orphaned(mygrp)) {
		/* XXX: The `procgrp_orphaned()'  check must  be made  interlocked with  sending
		 *      the `SIGTTOU' to the process group. -- If the group stops being orphaned
		 *      before  we're able to send the signal,  it would violate posix; iow: the
		 *      special handling  for orphaned  process groups  must happen  interlocked
		 *      with the sending of a signal to a non-orphaned one. */
		procgrp_memb_endread(mygrp);
		task_raisesignalprocessgroup(mygrp, signo);
		task_serve();
		/* FIXME: We might get here if the calling process changed groups.
		 *        This race condition  must be fixed  by keeping the  lock
		 *        to `procgrp_memb_endread()' until  after we've send  the
		 *        signal to all of the group members (which is  guarantied
		 *        to include the calling process).
		 * The only case  where we ~truely~  want to get  here is when  the
		 * caller uses a userprocmask that changed `signo' to masked before
		 * we  were able to send it the  signal. When that happens, we want
		 * to fall through to the throwing the exception below. */
		task_raisesignalprocess(mypid, signo);
		task_serve();
	} else {
		procgrp_memb_endread(mygrp);
	}

/*do_throw_E_IOERROR_REASON_TTY_ORPHAN_SIGTTOU:*/
	if (signo == SIGTTIN)
		goto do_throw_E_IOERROR_REASON_TTY_ORPHAN_SIGTTIN;
	THROW(E_IOERROR_NODATA,
	      E_IOERROR_SUBSYSTEM_TTY,
	      E_IOERROR_REASON_TTY_SIGTTOU);

#else /* CONFIG_USE_NEW_GROUP */
	REF struct taskpid *my_leader_pid;
	assert(chrdev_istty(self));
	my_leader_pid = task_getprocessgroupleaderpid();
	FINALLY_DECREF_UNLIKELY(my_leader_pid);
	if unlikely(my_leader_pid != axref_ptr(&self->t_fproc)) {
		REF struct task *my_leader;
		REF struct task *oldproc;
		REF struct taskpid *oldpid;
again_set_myleader_as_fproc:
		if (axref_cmpxch(&self->t_fproc, NULL, my_leader_pid))
			return; /* Lazily set the caller as the initial foreground process */
		/* Check if the old foreground process has already
		 * terminated, but  hasn't been  cleaned up,  yet. */
		oldpid = axref_get(&self->t_fproc);
		if unlikely(!oldpid)
			goto again_set_myleader_as_fproc;
		oldproc = taskpid_gettask(oldpid);
		if unlikely(!oldproc) {
			bool xch_ok;
do_try_override_fproc:
			xch_ok = axref_cmpxch(&self->t_fproc, oldpid, my_leader_pid);
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
		if (signo == SIGTTOU) {
			device_getname_lock_acquire(self);
			printk(KERN_INFO "[tty:%q] Background process group %p "
			                 "[pgid=%" PRIuN(__SIZEOF_PID_T__) "] tried to write\n",
			       device_getname(self), awref_ptr(&my_leader_pid->tp_thread),
			       taskpid_getroottid(my_leader_pid));
			device_getname_lock_release(self);

			/* When `SIGTTOU' is ignored, allow the write */
			if (THIS_SIGHAND_PTR) {
				struct sighand *hand;
				hand = sighand_ptr_lockread(THIS_SIGHAND_PTR);
				if likely(hand) {
					USER CHECKED user_sighandler_func_t fun;
					fun = hand->sh_actions[SIGTTOU - 1].sa_handler;
					sync_endread(hand);
					if (fun == SIG_IGN || fun == SIG_CONT)
						return;
				}
			}

			/* When `SIGTTOU' is masked, allow the write */
			if (sigmask_ismasked(SIGTTOU))
				return;

			/* ...  Attempts by a process in a background process group to write to its controlling
			 * terminal shall cause the process group to be sent a SIGTTOU signal unless one of the
			 * following special cases applies:
			 *   - If [...] the process is ignoring or blocking the SIGTTOU signal, the process
			 *     is allowed to  write to the  terminal and  the SIGTTOU signal  is not  sent.
			 *   - If [...] the  process group of  the writing  process is orphaned,  and the  writing
			 *     process is not ignoring or blocking the SIGTTOU signal, the write() shall return -1
			 *     with errno set to [EIO] and no signal shall be sent */
			if (taskpid_isorphan_p(my_leader_pid)) {
do_throw_ttou:
				THROW(E_IOERROR_NODATA,
				      E_IOERROR_SUBSYSTEM_TTY,
				      E_IOERROR_REASON_TTY_SIGTTOU);
			}

			/* NOTE: We also do the same if our process group leader has died, because once
			 *       that has happened,  any other  process is  allowed to  steal the  TTY! */
			my_leader = taskpid_gettask(my_leader_pid);
			if (my_leader) {
				FINALLY_DECREF_UNLIKELY(my_leader);
				if (my_leader->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED))
					goto do_throw_ttou;
				task_raisesignalprocessgroup(my_leader, SIGTTOU);
				task_serve();
			} else {
				goto do_throw_ttou;
			}

			/* We might get here if the  calling process changed its process  group
			 * in the mean time. - In this case, just re-raise `SIGTTIN' within the
			 * calling process only. */
			task_raisesignalprocess(task_getprocess(), SIGTTOU);
			task_serve();
			/* We might get here if `SIGTTOU' is being ignored by the calling thread.
			 * -> As described by POSIX, allow the process to write in this scenario. */
		} else {
			device_getname_lock_acquire(self);
			printk(KERN_INFO "[tty:%q] Background process group %p "
			                 "[pgid=%" PRIuN(__SIZEOF_PID_T__) "] tried to read\n",
			       device_getname(self), my_leader_pid,
			       taskpid_getroottid(my_leader_pid));
			device_getname_lock_release(self);

			/* ... if the reading process is ignoring or blocking the SIGTTIN signal, or if
			 * the process group of the reading process isorphaned, the read() shall return
			 * -1, with errno set to [EIO] and no signal shall be sent. */
			if (taskpid_isorphan_p(my_leader_pid))
				goto do_throw_ttin;
			/* NOTE: We also do the same if our process group leader has died, because once
			 *       that has happened,  any other  process is  allowed to  steal the  TTY! */
			my_leader = taskpid_gettask(my_leader_pid);
			if (my_leader) {
				FINALLY_DECREF_UNLIKELY(my_leader);
				if (my_leader->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED))
					goto do_throw_ttin;
				task_raisesignalprocessgroup(my_leader, SIGTTIN);
				task_serve();
			} else {
				goto do_throw_ttin;
			}
			/* We might get here if the  calling process changed its process  group
			 * in the mean time. - In this case, just re-raise `SIGTTIN' within the
			 * calling process only. */
			task_raisesignalprocess(task_getprocess(), SIGTTIN);
			task_serve();
			/* We might get here if `SIGTTIN' is being ignored by the calling thread. */
do_throw_ttin:
			THROW(E_IOERROR_NODATA,
			      E_IOERROR_SUBSYSTEM_TTY,
			      E_IOERROR_REASON_TTY_SIGTTIN);
		}
	}
#endif /* !CONFIG_USE_NEW_GROUP */
}

/* Kernel-level implementations for terminal system operators. */
PUBLIC NONNULL((1)) ssize_t LIBTERM_CC
ttydev_v_chk_sigttou(struct terminal *__restrict self) {
	struct ttydev *tty;
	tty = container_of(self, struct ttydev, t_term);
	kernel_terminal_check_sigtty(tty, SIGTTOU);
	return 0;
}

PUBLIC NONNULL((1)) ssize_t LIBTERM_CC
ttydev_v_raise(struct terminal *__restrict self,
               signo_t signo) {
#ifdef CONFIG_USE_NEW_GROUP
	REF struct procgrp *fg;
	struct ttydev *term;
	term = container_of(self, struct ttydev, t_term);
	assert(chrdev_istty(term));
	fg = ttydev_getfproc(term);
	if (fg) {
		FINALLY_DECREF_UNLIKELY(fg);
		task_raisesignalprocessgroup(fg, signo);
		task_serve();
	}
	return 0;
#else /* CONFIG_USE_NEW_GROUP */
	REF struct taskpid *fg_pid;
	struct ttydev *term;
	term = container_of(self, struct ttydev, t_term);
	assert(chrdev_istty(term));
	fg_pid = ttydev_getfproc(term);
	if (fg_pid) {
		REF struct task *fg;
		{
			FINALLY_DECREF_UNLIKELY(fg_pid);
			fg = taskpid_gettask(fg_pid);
		}
		if likely(fg) {
			FINALLY_DECREF_UNLIKELY(fg);
			task_raisesignalprocessgroup(fg, signo);
			task_serve();
		}
	}
	return 0;
#endif /* !CONFIG_USE_NEW_GROUP */
}

/* Default tty operators. */
PUBLIC NONNULL((1)) size_t KCALL
ttydev_v_read(struct mfile *__restrict self,
              USER CHECKED void *dst,
              size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	struct ttydev *me = mfile_astty(self);
	assert(mfile_istty(self));
	kernel_terminal_check_sigtty(me, SIGTTIN);
	result = terminal_iread(&me->t_term, dst, num_bytes, mode);
	assert(result <= num_bytes);
	return result;
}

PUBLIC NONNULL((1)) size_t KCALL
ttydev_v_write(struct mfile *__restrict self,
               USER CHECKED void const *src,
               size_t num_bytes, iomode_t mode) THROWS(...) {
	ssize_t result;
	struct ttydev *me = mfile_astty(self);
	assert(mfile_istty(self));
	result = terminal_owrite(&me->t_term, src, num_bytes, mode);
	assert((size_t)result <= num_bytes);
	return (size_t)result;
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ttydev_v_destroy)(struct mfile *__restrict self) {
	struct ttydev *me = mfile_astty(self);
	assertf(!awref_ptr(&me->t_cproc),
	        "A session leader should be holding a reference to their CTTY, "
	        "meaning that if we truly were supposed to be a CTTY, the "
	        "associated session should have kept us from being destroyed");
	terminal_fini(&me->t_term);
#ifndef CONFIG_USE_NEW_GROUP
	axref_fini(&me->t_fproc);
#endif /* !CONFIG_USE_NEW_GROUP */
	chrdev_v_destroy(self);
}


LOCAL NONNULL((1, 2)) void KCALL
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

LOCAL NONNULL((1, 2)) void KCALL
termios2_to_termios(USER CHECKED struct termios *__restrict dst,
                    USER CHECKED struct termios2 const *__restrict src) {
	dst->c_iflag = src->c_iflag;
	dst->c_oflag = src->c_oflag;
	dst->c_cflag = src->c_cflag;
	dst->c_lflag = src->c_lflag;
	dst->c_line  = src->c_line;
	{
		STATIC_ASSERT(sizeof(src->c_cc) <= sizeof(dst->c_cc));
		bzero(mempcpy(dst->c_cc, src->c_cc, sizeof(src->c_cc)),
		      sizeof(dst->c_cc) - sizeof(src->c_cc));
	}
	dst->c_ispeed = src->c_ispeed;
	dst->c_ospeed = src->c_ospeed;
}

LOCAL NONNULL((1, 2)) void KCALL
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

LOCAL NONNULL((1, 2)) void KCALL
termio_to_termios(USER CHECKED struct termios *__restrict dst,
                  USER CHECKED struct termio const *__restrict src) {
	dst->c_iflag = src->c_iflag;
	dst->c_oflag = src->c_oflag;
	dst->c_cflag = src->c_cflag;
	dst->c_lflag = src->c_lflag;
	dst->c_line  = src->c_line;
	{
		STATIC_ASSERT(sizeof(src->c_cc) <= sizeof(dst->c_cc));
		bzero(mempcpy(dst->c_cc, src->c_cc, sizeof(src->c_cc)),
		      sizeof(dst->c_cc) - sizeof(src->c_cc));
	}
	dst->c_ispeed = 0;
	dst->c_ospeed = 0;
}

LOCAL NONNULL((1, 2)) void KCALL
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

LOCAL NONNULL((1, 2)) void KCALL
termiox_to_termios(USER CHECKED struct termios *__restrict dst,
                   USER CHECKED struct termiox const *__restrict src) {
	dst->c_iflag = src->x_hflag;
	dst->c_oflag = src->x_cflag;
	dst->c_lflag = src->x_sflag;
	dst->c_cflag = 0;
	dst->c_line  = 0;
	{
		STATIC_ASSERT(sizeof(src->x_rflag) <= sizeof(dst->c_cc));
		bzero(mempcpy(dst->c_cc, src->x_rflag, sizeof(src->x_rflag)),
		      sizeof(dst->c_cc) - sizeof(src->x_rflag));
	}
	dst->c_ispeed = 0;
	dst->c_ospeed = 0;
}


#ifndef CONFIG_USE_NEW_GROUP
#define TTYDEV_SETCTTY_ALREADY     1  /* `self' was already the controlling terminal of the calling session. */
#define TTYDEV_SETCTTY_SUCCESS     0  /* Successfully assigned `self' as CTTY. */
#define TTYDEV_SETCTTY_NOTLEADER (-1) /* The calling process isn't the session leader, and `caller_must_be_leader' was true. */
#define TTYDEV_SETCTTY_DIFFERENT (-2) /* The calling session already had a CTTY assigned, and `override_different_ctty' was false. */
#define TTYDEV_SETCTTY_INUSE     (-3) /* The tty is already used as the CTTY of another session, and `steal_from_other_session' was false. */

/* [IMPL(TIOCSCTTY)] Set the given tty device as the controlling terminal of the calling session.
 * @param: steal_from_other_session: Allow the terminal to be stolen from another session.
 * @return: * : One of `TTYDEV_SETCTTY_*' */
PRIVATE NOBLOCK NONNULL((1)) int
NOTHROW(KCALL ttydev_setctty)(struct ttydev *__restrict self,
                              bool steal_from_other_session) {
	struct task *proc;
	REF struct task *session;
	struct taskpid *session_pid;
	assert(self);
	assert(chrdev_istty(self));
	proc    = task_getprocess();
	session = task_getsessionleader_srch_of(proc);
	FINALLY_DECREF_UNLIKELY(session);
	if unlikely(session != proc)
		return TTYDEV_SETCTTY_NOTLEADER;
	session_pid = FORTASK(session, this_taskpid);
again_check_tg_ctty:
	if (axref_ptr(&FORTASK(session, this_taskgroup).tg_ctty) != NULL) {
		REF struct ttydev *old_ctty;
		old_ctty = axref_get(&FORTASK(session, this_taskgroup).tg_ctty);
		if likely(old_ctty) {
			FINALLY_DECREF_UNLIKELY(old_ctty);
			if (old_ctty == self)
				return TTYDEV_SETCTTY_ALREADY;
			return TTYDEV_SETCTTY_DIFFERENT;
		}
	}
again_check_t_cproc:
	if unlikely(awref_ptr(&self->t_cproc) != NULL) {
		REF struct taskpid *old_cproc;
		old_cproc = awref_get(&self->t_cproc);
		if (old_cproc) {
			REF struct task *old_cproc_task;
			FINALLY_DECREF_UNLIKELY(old_cproc);
			if unlikely(old_cproc == session_pid)
				return TTYDEV_SETCTTY_ALREADY;
			if (!steal_from_other_session)
				return TTYDEV_SETCTTY_INUSE;

			/* Change the TTY's session pointer to the new session. */
			if unlikely(!awref_cmpxch(&self->t_cproc, old_cproc, session_pid))
				goto again_check_t_cproc;

			/* Set the TTY link of the new session task descriptor. */
			if unlikely(!axref_cmpxch(&FORTASK(session, this_taskgroup).tg_ctty, NULL, self)) {
				awref_cmpxch(&self->t_cproc, session_pid, old_cproc);
				goto again_check_tg_ctty;
			}

			/* Delete the TTY link from the old session task descriptor */
			old_cproc_task = taskpid_gettask(old_cproc);
			if likely(old_cproc_task) {
				if (axref_cmpxch(&FORTASK(old_cproc_task, this_taskgroup).tg_ctty, self, NULL))
					ttydev_log_delsession(self, old_cproc_task, old_cproc);
				decref_unlikely(old_cproc_task);
			}
			ttydev_log_setsession(self, session, session_pid);
			return TTYDEV_SETCTTY_SUCCESS;
		}
	}

	/* Set the TTY's session pointer to the calling session. */
	if (!awref_cmpxch(&self->t_cproc, NULL, session_pid))
		goto again_check_t_cproc;

	/* Set the TTY link of the session task descriptor. */
	if unlikely(!axref_cmpxch(&FORTASK(session, this_taskgroup).tg_ctty, NULL, self)) {
		awref_cmpxch(&self->t_cproc, FORTASK(session, this_taskpid), NULL);
		goto again_check_tg_ctty;
	}
	ttydev_log_setsession(self, session, session_pid);
	return TTYDEV_SETCTTY_SUCCESS;
}


#define TTYDEV_HUPCTTY_ALREADY      1  /* The calling session didn't have a CTTY to begin with */
#define TTYDEV_HUPCTTY_SUCCESS      0  /* Successfully gave up control of the CTTY (when `pold_ctty' was non-NULL, that old CTTY is stored there) */
#define TTYDEV_HUPCTTY_NOTLEADER  (-1) /* The calling process isn't the session leader, and `caller_must_be_leader' was true. */
#define TTYDEV_HUPCTTY_DIFFERENT  (-2) /* `required_old_ctty' was non-NULL and differed from the actually set old CTTY */

/* [IMPL(TIOCNOTTY)] Give up the controlling terminal of the calling session.
 * @return: * : One of `TTYDEV_HUPCTTY_*' */
PRIVATE NOBLOCK int
NOTHROW(KCALL ttydev_hupctty)(struct ttydev *required_old_ctty DFL(__NULLPTR)) {
	struct task *proc;
	struct taskpid *session_pid;
	REF struct task *session;
	assert(!required_old_ctty || chrdev_istty(required_old_ctty));
	proc    = task_getprocess();
	session = task_getsessionleader_srch_of(proc);
	FINALLY_DECREF_UNLIKELY(session);
	if unlikely(session != proc)
		return TTYDEV_HUPCTTY_NOTLEADER;
	session_pid = FORTASK(session, this_taskpid);
	if (required_old_ctty) {
again_my_ctty_pointer_cmpxch:
		if (!axref_cmpxch(&FORTASK(session, this_taskgroup).tg_ctty,
		                  required_old_ctty, NULL)) {
			struct ttydev *old_ctty;
			old_ctty = axref_ptr(&FORTASK(session, this_taskgroup).tg_ctty);
			if (old_ctty == NULL)
				return TTYDEV_HUPCTTY_ALREADY;
			if (old_ctty == required_old_ctty)
				goto again_my_ctty_pointer_cmpxch;
			return TTYDEV_HUPCTTY_DIFFERENT;
		}
		if (awref_cmpxch(&required_old_ctty->t_cproc, session_pid, NULL))
			ttydev_log_delsession(required_old_ctty, session, session_pid);
	} else {
		REF struct ttydev *old_ctty;
		old_ctty = axref_steal(&FORTASK(session, this_taskgroup).tg_ctty);
		if (!old_ctty)
			return TTYDEV_HUPCTTY_ALREADY;
		if (awref_cmpxch(&old_ctty->t_cproc, session_pid, NULL))
			ttydev_log_delsession(old_ctty, session, session_pid);
		decref(old_ctty);
	}
	return TTYDEV_HUPCTTY_SUCCESS;
}
#endif /* !CONFIG_USE_NEW_GROUP */





/* @return: -EINVAL: Unsupported `cmd' */
PUBLIC NONNULL((1)) syscall_slong_t KCALL
_ttydev_tryioctl(struct mfile *__restrict self, ioctl_t cmd,
                 USER UNCHECKED void *arg, iomode_t UNUSED(mode)) THROWS(...) {
	struct ttydev *me = mfile_astty(self);
	assert(mfile_istty(self));
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
	case _IOW(_IOC_TYPE(TIOCSPGRP), _IOC_NR(TIOCSPGRP), pid_t): {
#ifdef CONFIG_USE_NEW_GROUP
		pid_t pid;
		struct taskpid *mypid;
		REF struct procgrp *grp;
		TRY {
			kernel_terminal_check_sigtty(me, SIGTTOU);
		} EXCEPT {
			if (was_thrown(E_IOERROR_NODATA)) {
				struct exception_data *dat = except_data();
				bzero(&dat->e_args, sizeof(dat->e_args));
				dat->e_code                               = EXCEPT_CODEOF(E_INVALID_ARGUMENT_BAD_STATE);
				dat->e_args.e_invalid_argument.ia_context = E_INVALID_ARGUMENT_CONTEXT_TIOCSPGRP_SIGTTOU;
			}
			RETHROW();
		}
		validate_readable(arg, sizeof(pid_t));
		COMPILER_READ_BARRIER();
		pid = *(USER CHECKED pid_t const *)arg;
		COMPILER_READ_BARRIER();
		mypid = task_gettaskpid();
		{
			REF struct procgrp *mygrp;
			mygrp = taskpid_getprocgrp(mypid);
			FINALLY_DECREF_UNLIKELY(mygrp);
			if (mygrp->pgr_sleader != awref_ptr(&me->t_cproc)) {
				THROW(E_INVALID_ARGUMENT_BAD_STATE,
				      E_INVALID_ARGUMENT_CONTEXT_TIOCSPGRP_NOT_CALLER_SESSION);
			}
		}
		if (pid == 0) {
			/* KOS extension: we accept `0' as alias for "current process group" */
			grp = taskpid_getprocgrp(mypid);
		} else {
			grp = pidns_grplookup_srch(mypid->tp_ns, pid);
		}
		FINALLY_DECREF_UNLIKELY(grp);
		if (grp->pgr_sleader != awref_ptr(&me->t_cproc)) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_TIOCSPGRP_DIFFERENT_SESSION);
		}

		/* Always assign the taskpid of a process group leader! */
		device_getname_lock_acquire(me);
		printk(KERN_TRACE "[tty:%q] Set foreground process group to "
		                  "[pgid:%" PRIuN(__SIZEOF_PID_T__) ",sid:%" PRIuN(__SIZEOF_PID_T__) "]\n",
		       device_getname(me), procgrp_getrootpgid(grp), procgrp_getrootsid(grp));
		device_getname_lock_release(me);

		/* Set `grp' as the foreground process group.
		 * FIXME: Race condition when the session leader relinquishes CTTY control. */
		awref_set(&me->t_fproc, grp);
#else /* CONFIG_USE_NEW_GROUP */
		pid_t pid;
		REF struct taskpid *oldpid;
		REF struct taskpid *newpid;
		REF struct task *newthread;
		validate_readable(arg, sizeof(pid_t));
		COMPILER_READ_BARRIER();
		pid = *(USER CHECKED pid_t *)arg;
		COMPILER_READ_BARRIER();
		newthread = pid == 0
		            ? incref(THIS_TASK)
		            : pidns_lookuptask_srch(THIS_PIDNS, pid);
		/* Always assign the taskpid of a process group leader! */
		{
			FINALLY_DECREF_UNLIKELY(newthread);
			newpid = task_getprocessgroupleaderpid_of(newthread);
		}
		device_getname_lock_acquire(me);
		printk(KERN_TRACE "[tty:%q] Set foreground process group to [pgid=%" PRIuN(__SIZEOF_PID_T__) "]\n",
		       device_getname(me), taskpid_getroottid(newpid));
		device_getname_lock_release(me);
		oldpid = axref_xch_inherit(&me->t_fproc, newpid);
		xdecref(oldpid);
#endif /* !CONFIG_USE_NEW_GROUP */
	}	break;

	case TIOCGPGRP:
	case _IOR(_IOC_TYPE(TIOCGPGRP), _IOC_NR(TIOCGPGRP), pid_t): {
		pid_t respid;
#ifdef CONFIG_USE_NEW_GROUP
		REF struct procgrp *grp;
		{
			REF struct procgrp *mygrp;
			mygrp = task_getprocgrp();
			FINALLY_DECREF_UNLIKELY(mygrp);
			if (mygrp->pgr_sleader != awref_ptr(&me->t_cproc)) {
				THROW(E_INVALID_ARGUMENT_BAD_STATE,
				      E_INVALID_ARGUMENT_CONTEXT_TIOCGPGRP_NOT_CALLER_SESSION);
			}
		}
		respid = 0;
		grp    = awref_get(&me->t_fproc);
		if (grp) {
			respid = procgrp_getpgid_s(grp);
			decref_unlikely(grp);
		}
#else /* CONFIG_USE_NEW_GROUP */
		REF struct taskpid *tpid;
		validate_writable(arg, sizeof(pid_t));
		respid = -ESRCH;
		tpid   = axref_get(&me->t_fproc);
		if (tpid) {
			respid = taskpid_gettid(tpid);
			decref_unlikely(tpid);
		}
#endif /* !CONFIG_USE_NEW_GROUP */
		validate_writable(arg, sizeof(pid_t));
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED pid_t *)arg = respid;
	}	break;

	case TIOCGSID:
	case _IOR(_IOC_TYPE(TIOCGSID), _IOC_NR(TIOCGSID), pid_t): {
		pid_t respid;
#ifdef CONFIG_USE_NEW_GROUP
		REF struct procgrp *grp;
		grp = task_getprocgrp();
		FINALLY_DECREF_UNLIKELY(grp);
		if (grp->pgr_sleader != awref_ptr(&me->t_cproc)) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_TIOCGSID_NOT_CALLER_SESSION);
		}
		respid = procgrp_getsid_s(grp);
#else /* CONFIG_USE_NEW_GROUP */
		REF struct taskpid *tpid;
		respid = -ENOTTY;
		tpid   = awref_get(&me->t_cproc);
		if (tpid) {
			respid = taskpid_gettid(tpid);
			decref_unlikely(tpid);
		}
#endif /* !CONFIG_USE_NEW_GROUP */
		validate_writable(arg, sizeof(pid_t));
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED pid_t *)arg = respid;
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
			ATOMIC_OR(me->t_term.t_ios.c_iflag, IXOFF);
			break;

		case TCOON:
			if (ATOMIC_FETCHAND(me->t_term.t_ios.c_iflag, ~IXOFF) & IXOFF)
				sig_broadcast(&me->t_term.t_opend.lb_nful);
			break;

		case TCIOFF:
			ATOMIC_OR(me->t_term.t_ios.c_iflag, __IIOFF);
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
			ATOMIC_OR(me->t_term.t_ios.c_cflag, CLOCAL);
		} else {
			ATOMIC_AND(me->t_term.t_ios.c_cflag, ~CLOCAL);
		}
	}	break;

	/* XXX: Exclusive terminal mode enabled with `TIOCEXCL' */
	/* XXX: Exclusive terminal mode disabled with `TIOCNXCL' */
	/* XXX: Exclusive terminal mode tested with `TIOCGEXCL' */

#ifdef CONFIG_USE_NEW_GROUP
	case TIOCSCTTY: {
		REF struct procgrp *mygrp;
		REF struct procgrp *oldcproc;
		struct ttydev *oldtty;
		mygrp = task_getprocgrp();
		FINALLY_DECREF_UNLIKELY(mygrp);
again_TIOCSCTTY:
		oldtty = axref_ptr(&mygrp->pgr_session->ps_ctty);
		if (oldtty != NULL) {
			if (oldtty == me)
				break; /* No-op. -- This is allowed */
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_TIOCSCTTY_ALREADY_HAVE_CTTY);
		}
		if (!procgrp_issessionleader(mygrp)) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_TIOCSCTTY_NOT_SESSION_LEADER);
		}
		oldcproc = awref_get(&me->t_cproc);
		if (oldcproc) {
			FINALLY_DECREF_UNLIKELY(oldcproc);
			if ((uintptr_t)arg != 1 || !capable(CAP_SYS_ADMIN)) {
				THROW(E_INVALID_ARGUMENT_BAD_STATE,
				      E_INVALID_ARGUMENT_CONTEXT_TIOCSCTTY_CANNOT_STEAL_CTTY);
			}
			if (!axref_cmpxch(&oldcproc->pgr_session->ps_ctty, me, NULL))
				goto again_TIOCSCTTY;
			if (!awref_cmpxch(&me->t_cproc, oldcproc, mygrp)) {
				axref_cmpxch(&oldcproc->pgr_session->ps_ctty, NULL, me);
				goto again_TIOCSCTTY;
			}
			ttydev_log_delsession(me, oldcproc);
		} else {
			if (!awref_cmpxch(&me->t_cproc, NULL, mygrp))
				goto again_TIOCSCTTY;
		}
		awref_set(&me->t_fproc, mygrp);
		ttydev_log_setsession(me, mygrp);
	}	break;

	case TIOCNOTTY: {
		REF struct procgrp *mygrp = task_getprocgrp();
		FINALLY_DECREF_UNLIKELY(mygrp);
again_TIOCNOTTY:
		if (axref_ptr(&mygrp->pgr_session->ps_ctty) != me) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_TIOCNOTTY_NOT_CALLER_SESSION);
		}
		if (!awref_cmpxch(&me->t_cproc, mygrp->pgr_sleader, NULL))
			goto again_TIOCNOTTY;
		if (!axref_cmpxch(&mygrp->pgr_session->ps_ctty, me, NULL))
			goto again_TIOCNOTTY;
		for (;;) {
			REF struct procgrp *fproc;
			fproc = awref_get(&me->t_fproc);
			if (!fproc)
				break;
			FINALLY_DECREF_UNLIKELY(fproc);
			if (fproc->pgr_sleader != mygrp->pgr_sleader)
				break;
			if (awref_cmpxch(&me->t_fproc, fproc, NULL))
				break;
		}
		ttydev_log_delsession(me, mygrp);
	}	break;
#else /* CONFIG_USE_NEW_GROUP */
	case TIOCSCTTY: {
		int error;
		error = ttydev_setctty(me, (uintptr_t)arg != 0 && capable(CAP_ALLOW_CTTY_STEALING));
		if (error == TTYDEV_SETCTTY_INUSE)
			THROW(E_INSUFFICIENT_RIGHTS, CAP_ALLOW_CTTY_STEALING);
		if (error == TTYDEV_SETCTTY_DIFFERENT)
			THROW(E_INVALID_CONTEXT_CTTY_ALREADY_ASSIGNED);
		if (error == TTYDEV_SETCTTY_NOTLEADER)
			THROW(E_INVALID_CONTEXT_NOT_SESSION_LEADER);
	}	break;

	case TIOCNOTTY: {
		int error;
		error = ttydev_hupctty(me);
		if (error == TTYDEV_HUPCTTY_NOTLEADER)
			THROW(E_INVALID_CONTEXT_NOT_SESSION_LEADER);
		if (error == TTYDEV_HUPCTTY_DIFFERENT)
			THROW(E_INVALID_CONTEXT_CTTY_DIFFERS);
	}	break;
#endif /* !CONFIG_USE_NEW_GROUP */

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
	case TCSETXW: {
		struct termios new_io;
do_TCSETX:
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
		signo_t signo;
		validate_readable(arg, sizeof(signo_t));
		COMPILER_READ_BARRIER();
		signo = *(USER CHECKED signo_t *)arg;
		COMPILER_READ_BARRIER();
		if unlikely(signo <= 0 || signo >= NSIG) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
			      signo);
		}
		ttydev_v_raise(&me->t_term, signo);
	}	break;

	/* XXX: TIOCVHANGUP? */

	/* KOS-specific tty ioctl commands */
	case TTYIO_IBUF_GETLIMIT:
	case TTYIO_CANON_GETLIMIT:
	case TTYIO_OPEND_GETLIMIT:
	case TTYIO_IPEND_GETLIMIT:
#if defined(__ARCH_HAVE_COMPAT) && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T
	case _IO_WITHTYPE(TTYIO_IBUF_GETLIMIT, compat_size_t):
	case _IO_WITHTYPE(TTYIO_CANON_GETLIMIT, compat_size_t):
	case _IO_WITHTYPE(TTYIO_OPEND_GETLIMIT, compat_size_t):
	case _IO_WITHTYPE(TTYIO_IPEND_GETLIMIT, compat_size_t):
#endif /* __ARCH_HAVE_COMPAT && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T */
	{
		size_t value;
#if defined(__ARCH_HAVE_COMPAT) && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T
		validate_writable(arg, _IOC_SIZE(cmd));
#else /* __ARCH_HAVE_COMPAT && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T */
		validate_writable(arg, sizeof(size_t));
#endif /* !__ARCH_HAVE_COMPAT || __SIZEOF_SIZE_T__ == __ARCH_COMPAT_SIZEOF_SIZE_T */
		switch (_IOC_NR(cmd)) {

		case _IOC_NR(TTYIO_IBUF_GETLIMIT):
			value = ATOMIC_READ(me->t_term.t_ibuf.rb_limit);
			break;

		case _IOC_NR(TTYIO_CANON_GETLIMIT):
			value = ATOMIC_READ(me->t_term.t_canon.lb_limt);
			break;

		case _IOC_NR(TTYIO_OPEND_GETLIMIT):
			value = ATOMIC_READ(me->t_term.t_opend.lb_limt);
			break;

		case _IOC_NR(TTYIO_IPEND_GETLIMIT):
			value = ATOMIC_READ(me->t_term.t_ipend.lb_limt);
			break;

		default: __builtin_unreachable();
		}
		COMPILER_WRITE_BARRIER();
#if defined(__ARCH_HAVE_COMPAT) && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T
		if (_IOC_SIZE(cmd) == sizeof(compat_size_t)) {
			*(USER CHECKED compat_size_t *)arg = (compat_size_t)value;
		} else
#endif /* defined(__ARCH_HAVE_COMPAT) && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T */
		{
			*(USER CHECKED size_t *)arg = (size_t)value;
		}
	}	break;

	case TTYIO_IBUF_SETLIMIT:
	case TTYIO_CANON_SETLIMIT:
	case TTYIO_OPEND_SETLIMIT:
	case TTYIO_IPEND_SETLIMIT:
#if defined(__ARCH_HAVE_COMPAT) && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T
	case _IO_WITHTYPE(TTYIO_IBUF_SETLIMIT, compat_size_t):
	case _IO_WITHTYPE(TTYIO_CANON_SETLIMIT, compat_size_t):
	case _IO_WITHTYPE(TTYIO_OPEND_SETLIMIT, compat_size_t):
	case _IO_WITHTYPE(TTYIO_IPEND_SETLIMIT, compat_size_t):
#endif /* __ARCH_HAVE_COMPAT && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T */
	{
		size_t value;
		struct linebuffer *lnbuf;
		require(CAP_SET_TTY_BUFFER_SIZES);
		COMPILER_READ_BARRIER();
#if defined(__ARCH_HAVE_COMPAT) && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T
		if (_IOC_SIZE(cmd) == sizeof(compat_size_t)) {
			validate_readable(arg, sizeof(compat_size_t));
			value = *(USER CHECKED compat_size_t *)arg;
		} else
#endif /* __ARCH_HAVE_COMPAT && __SIZEOF_SIZE_T__ != __ARCH_COMPAT_SIZEOF_SIZE_T */
		{
			validate_readable(arg, sizeof(size_t));
			value = *(USER CHECKED size_t *)arg;
		}
		COMPILER_READ_BARRIER();
		switch (_IOC_NR(cmd)) {

		case _IOC_NR(TTYIO_IBUF_SETLIMIT):
			if (!value) {
				ringbuffer_close(&me->t_term.t_ibuf);
			} else {
				ATOMIC_WRITE(me->t_term.t_ibuf.rb_limit, value);
			}
			goto done;

		case _IOC_NR(TTYIO_CANON_SETLIMIT):
			lnbuf = &me->t_term.t_canon;
			break;

		case _IOC_NR(TTYIO_OPEND_SETLIMIT):
			lnbuf = &me->t_term.t_opend;
			break;

		case _IOC_NR(TTYIO_IPEND_SETLIMIT):
			lnbuf = &me->t_term.t_ipend;
			break;

		default: __builtin_unreachable();
		}
		if (!value) {
			linebuffer_close(lnbuf);
		} else {
			ATOMIC_WRITE(lnbuf->lb_limt, value);
		}
	}	break;

	default:
		return -EINVAL;
	}
done:
	return 0;
}


PUBLIC NONNULL((1)) syscall_slong_t KCALL
ttydev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	syscall_slong_t result;
	result = _ttydev_tryioctl(self, cmd, arg, mode);
	if (result == -EINVAL)
		result = chrdev_v_ioctl(self, cmd, arg, mode);
	return result;
}

PUBLIC NONNULL((1)) void KCALL
ttydev_v_pollconnect(struct mfile *__restrict self,
                     poll_mode_t what) THROWS(...) {
	struct ttydev *me = mfile_astty(self);
	assert(mfile_istty(self));
	if (what & POLLINMASK)
		terminal_pollconnect_iread(&me->t_term);
	if (what & POLLOUTMASK) {
		/* Assume that writing output never blocks. */
#define noop_connect_ex(cb) (void)0
		terminal_pollconnect_owrite(&me->t_term, noop_connect_ex);
#undef noop_connect_ex
	}
}

PUBLIC NONNULL((1)) poll_mode_t KCALL
ttydev_v_polltest(struct mfile *__restrict self,
                  poll_mode_t what) THROWS(...) {
	poll_mode_t result = 0;
	struct ttydev *me = mfile_astty(self);
	assert(mfile_istty(self));
	if (what & POLLINMASK) {
		if (terminal_caniread(&me->t_term))
			result |= POLLINMASK;
	}
	if (what & POLLOUTMASK) {
		/* Assume that output writing never blocks. */
		if (terminal_canowrite(&me->t_term, 1))
			result |= POLLOUTMASK;
	}
	return result;
}


PUBLIC NONNULL((1)) void KCALL
ttydev_v_stat(struct mfile *__restrict self,
              USER CHECKED struct stat *result) THROWS(...) {
	struct ttydev *me = mfile_astty(self);
	assert(mfile_istty(self));

	/* Try to give user-space an estimate on the number of unread input bytes. */
	result->st_size = ATOMIC_READ(me->t_term.t_ibuf.rb_avail) +
	                  ATOMIC_READ(me->t_term.t_ipend.lb_line.lc_size) +
	                  ATOMIC_READ(me->t_term.t_canon.lb_line.lc_size);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_TTY_C */
