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
#ifndef _KOS_BITS_SPAWN_ACTION_H
#define _KOS_BITS_SPAWN_ACTION_H 1

#include <__stdinc.h>
#include <bits/types.h>

__DECL_BEGIN

#define __OFFSET_SPAWN_ACTION_TYPE                      0
#define __OFFSET_SPAWN_ACTION_SIGDFL_SIGSET             __SIZEOF_POINTER__       /* [FIELD(sa_sigdfl.sa_sigset)] */
#define __OFFSET_SPAWN_ACTION_SIGDFL_SIGSETSZ           (__SIZEOF_POINTER__ * 2) /* [FIELD(sa_sigdfl.sa_sigsetsz)] */
#define __OFFSET_SPAWN_ACTION_SIGPROCMASK_SIGSET        __SIZEOF_POINTER__       /* [FIELD(sa_sigprocmask.sa_sigset)] */
#define __OFFSET_SPAWN_ACTION_SIGPROCMASK_SIGSETSZ      (__SIZEOF_POINTER__ * 2) /* [FIELD(sa_sigprocmask.sa_sigsetsz)] */
#define __OFFSET_SPAWN_ACTION_SETPGID_PID               __SIZEOF_POINTER__       /* [FIELD(sa_setpgid.sa_pid)] */
#define __OFFSET_SPAWN_ACTION_SCHED_SETPARAM_PARAM      __SIZEOF_POINTER__       /* [FIELD(sa_sched_setparam.sa_param)] */
#define __OFFSET_SPAWN_ACTION_SCHED_SETSCHEDULER_PARAM  __SIZEOF_POINTER__       /* [FIELD(sa_sched_setscheduler.sa_param)] */
#define __OFFSET_SPAWN_ACTION_SCHED_SETSCHEDULER_POLICY (__SIZEOF_POINTER__ * 2) /* [FIELD(sa_sched_setscheduler.sa_policy)] */
#define __OFFSET_SPAWN_ACTION_OPENAT_FD                 __SIZEOF_POINTER__       /* [FIELD(sa_openat.sa_fd)] */
#define __OFFSET_SPAWN_ACTION_OPENAT_DFD                (__SIZEOF_POINTER__ + __SIZEOF_FD_T__) /* [FIELD(sa_openat.sa_dfd)] */
#define __OFFSET_SPAWN_ACTION_OPENAT_FILENAME           (__SIZEOF_POINTER__ + __SIZEOF_FD_T__ * 2) /* [FIELD(sa_openat.sa_filename)] */
#define __OFFSET_SPAWN_ACTION_OPENAT_OFLAGS             (__SIZEOF_POINTER__ * 2 + __SIZEOF_FD_T__ * 2) /* [FIELD(sa_openat.sa_oflags)] */
#define __OFFSET_SPAWN_ACTION_OPENAT_MODE               (__SIZEOF_POINTER__ * 2 + __SIZEOF_FD_T__ * 2 + __SIZEOF_OFLAG_T__) /* [FIELD(sa_openat.sa_mode)] */
#define __OFFSET_SPAWN_ACTION_CLOSE_FD                  __SIZEOF_POINTER__       /* [FIELD(sa_close.sa_fd)] */
#define __OFFSET_SPAWN_ACTION_CLOSERANGE_LOFD           __SIZEOF_POINTER__       /* [FIELD(sa_closerange.sa_lofd)] */
#define __OFFSET_SPAWN_ACTION_CLOSERANGE_HIFD           (__SIZEOF_POINTER__ + __SIZEOF_FD_T__) /* [FIELD(sa_closerange.sa_hifd)] */
#define __OFFSET_SPAWN_ACTION_DUP2_OLDFD                __SIZEOF_POINTER__       /* [FIELD(sa_dup2.sa_oldfd)] */
#define __OFFSET_SPAWN_ACTION_DUP2_NEWFD                (__SIZEOF_POINTER__ + __SIZEOF_FD_T__) /* [FIELD(sa_dup2.sa_newfd)] */
#define __OFFSET_SPAWN_ACTION_TCSETPGRP_TTYFD           __SIZEOF_POINTER__       /* [FIELD(sa_tcsetpgrp.sa_ttyfd)] */

#ifdef __CC__
struct __sigset_struct;
struct sched_param;
struct spawn_action /*[PREFIX(sa_)]*/ {
	__uintptr_t sa_type; /* Action type (one of `SPAWN_ACTION_*') */
	union {

		struct {
			struct __sigset_struct *sa_sigset;   /* [1..1] Signal set */
			__size_t                sa_sigsetsz; /* Signal set size (in bytes) */
		} sa_sigdfl; /* SPAWN_ACTION_SIGDFL */

		struct {
			struct __sigset_struct *sa_sigset;   /* [1..1] Signal set */
			__size_t                sa_sigsetsz; /* Signal set size (in bytes) */
		} sa_sigprocmask; /* SPAWN_ACTION_SIGPROCMASK */

		struct {
			__pid_t sa_pid; /* Process group ID for the child process (or 0 to place the child process in its own group) */
		} sa_setpgid; /* SPAWN_ACTION_SETPGID */

		struct {
			struct sched_param *sa_param; /* [1..1] Scheduler params */
		} sa_sched_setparam; /* SPAWN_ACTION_SCHED_SETPARAM */

		struct {
			struct sched_param *sa_param;  /* [1..1] Scheduler params */
			__syscall_ulong_t   sa_policy; /* Scheduler policy */
		} sa_sched_setscheduler; /* SPAWN_ACTION_SCHED_SETSCHEDULER */

		struct {
			__fd_t      sa_fd;       /* Target FD number (the FD number in which the handle will be stored)
			                          * HINT: chroot()+chdir() during spawn() can be implemented by using
			                          *       AT_FDROOT / AT_FDCWD here! */
			__fd_t      sa_dfd;      /* Directory FD to which the given filename is relative. */
			char const *sa_filename; /* [1..1] The name of the file to-be opened. */
			__oflag_t   sa_oflags;   /* Open flags. */
			__mode_t    sa_mode;     /* File creation mode. */
		} sa_openat; /* SPAWN_ACTION_OPENAT */

		struct {
			__fd_t      sa_fd;       /* FD number to-be closed */
		} sa_close; /* SPAWN_ACTION_CLOSE */

		struct {
			__ufd_t     sa_lofd;     /* First file descriptor to-be closed */
			__ufd_t     sa_hifd;     /* Last file descriptor to-be closed */
		} sa_closerange; /* SPAWN_ACTION_CLOSERANGE */

		struct {
			__fd_t      sa_oldfd;    /* Old file descriptor number */
			__fd_t      sa_newfd;    /* New file descriptor number */
		} sa_dup2; /* SPAWN_ACTION_DUP2 */

		struct {
			__fd_t      sa_ttyfd;    /* File descriptor for the TTY to update. */
		} sa_tcsetpgrp; /* SPAWN_ACTION_TCSETPGRP */

	};
};

struct spawn_action_list {
	struct spawn_action_list *sal_next;          /* [0..1] Next set of actions. */
	__size_t                  sal_stride;        /* == sizeof(struct spawn_action) */
	__size_t                  sal_count;         /* # of actions specified in `sal_actions' */
	struct spawn_action       sal_actions[1024]; /* [sas_count] Vector of actions. */
};

struct spawn_actions {
	__syscall_ulong_t         sas_clone_flags; /* Flags to-be used for spawning the new process (Set of `CLONE_*') */
	void                     *sas_reserved1;   /* Reserved (must be NULL) */
	void                     *sas_reserved2;   /* Reserved (must be NULL) */
	struct spawn_action_list  sas_actions;     /* Actions to-be taken for modifying the new process's execution context. */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_BITS_SPAWN_ACTION_H */
