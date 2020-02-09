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
#ifndef _I386_KOS_BITS_SPAWN_ACTION32_H
#define _I386_KOS_BITS_SPAWN_ACTION32_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/typecore.h>
#include <hybrid/host.h>

__DECL_BEGIN

#if !defined(__x86_64__) && defined(__i386__)
#define spawn_actionx32       spawn_action
#define spawn_action_listx32  spawn_action_list
#define spawn_actionsx32      spawn_actions
#define __OFFSET_SPAWN_ACTION_TYPE                      __OFFSET_SPAWN_ACTIONX32_TYPE
#define __OFFSET_SPAWN_ACTION_SIGDFL_SIGSET             __OFFSET_SPAWN_ACTIONX32_SIGDFL_SIGSET
#define __OFFSET_SPAWN_ACTION_SIGDFL_SIGSETSZ           __OFFSET_SPAWN_ACTIONX32_SIGDFL_SIGSETSZ
#define __OFFSET_SPAWN_ACTION_SIGPROCMASK_SIGSET        __OFFSET_SPAWN_ACTIONX32_SIGPROCMASK_SIGSET
#define __OFFSET_SPAWN_ACTION_SIGPROCMASK_SIGSETSZ      __OFFSET_SPAWN_ACTIONX32_SIGPROCMASK_SIGSETSZ
#define __OFFSET_SPAWN_ACTION_SETPGID_PID               __OFFSET_SPAWN_ACTIONX32_SETPGID_PID
#define __OFFSET_SPAWN_ACTION_SCHED_SETPARAM_PARAM      __OFFSET_SPAWN_ACTIONX32_SCHED_SETPARAM_PARAM
#define __OFFSET_SPAWN_ACTION_SCHED_SETSCHEDULER_PARAM  __OFFSET_SPAWN_ACTIONX32_SCHED_SETSCHEDULER_PARAM
#define __OFFSET_SPAWN_ACTION_SCHED_SETSCHEDULER_POLICY __OFFSET_SPAWN_ACTIONX32_SCHED_SETSCHEDULER_POLICY
#define __OFFSET_SPAWN_ACTION_OPENAT_FD                 __OFFSET_SPAWN_ACTIONX32_OPENAT_FD
#define __OFFSET_SPAWN_ACTION_OPENAT_DFD                __OFFSET_SPAWN_ACTIONX32_OPENAT_DFD
#define __OFFSET_SPAWN_ACTION_OPENAT_FILENAME           __OFFSET_SPAWN_ACTIONX32_OPENAT_FILENAME
#define __OFFSET_SPAWN_ACTION_OPENAT_OFLAGS             __OFFSET_SPAWN_ACTIONX32_OPENAT_OFLAGS
#define __OFFSET_SPAWN_ACTION_OPENAT_MODE               __OFFSET_SPAWN_ACTIONX32_OPENAT_MODE
#define __OFFSET_SPAWN_ACTION_CLOSE_FD                  __OFFSET_SPAWN_ACTIONX32_CLOSE_FD
#define __OFFSET_SPAWN_ACTION_CLOSERANGE_LOFD           __OFFSET_SPAWN_ACTIONX32_CLOSERANGE_LOFD
#define __OFFSET_SPAWN_ACTION_CLOSERANGE_HIFD           __OFFSET_SPAWN_ACTIONX32_CLOSERANGE_HIFD
#define __OFFSET_SPAWN_ACTION_DUP2_OLDFD                __OFFSET_SPAWN_ACTIONX32_DUP2_OLDFD
#define __OFFSET_SPAWN_ACTION_DUP2_NEWFD                __OFFSET_SPAWN_ACTIONX32_DUP2_NEWFD
#define __OFFSET_SPAWN_ACTION_TCSETPGRP_TTYFD           __OFFSET_SPAWN_ACTIONX32_TCSETPGRP_TTYFD
#define __OFFSET_SPAWN_ACTION_UMASK_MASK                __OFFSET_SPAWN_ACTIONX32_UMASK_MASK
#define __OFFSET_SPAWN_ACTION_FSMODE_MASK               __OFFSET_SPAWN_ACTIONX32_FSMODE_MASK
#define __OFFSET_SPAWN_ACTION_FSMODE_FLAG               __OFFSET_SPAWN_ACTIONX32_FSMODE_FLAG
#endif /* !__x86_64__ && __i386__ */

#define __OFFSET_SPAWN_ACTIONX32_TYPE                      0
#define __OFFSET_SPAWN_ACTIONX32_SIGDFL_SIGSET             4  /* [FIELD(sa_sigdfl.sa_sigset)] */
#define __OFFSET_SPAWN_ACTIONX32_SIGDFL_SIGSETSZ           8  /* [FIELD(sa_sigdfl.sa_sigsetsz)] */
#define __OFFSET_SPAWN_ACTIONX32_SIGPROCMASK_SIGSET        4  /* [FIELD(sa_sigprocmask.sa_sigset)] */
#define __OFFSET_SPAWN_ACTIONX32_SIGPROCMASK_SIGSETSZ      8  /* [FIELD(sa_sigprocmask.sa_sigsetsz)] */
#define __OFFSET_SPAWN_ACTIONX32_SETPGID_PID               4  /* [FIELD(sa_setpgid.sa_pid)] */
#define __OFFSET_SPAWN_ACTIONX32_SCHED_SETPARAM_PARAM      4  /* [FIELD(sa_sched_setparam.sa_param)] */
#define __OFFSET_SPAWN_ACTIONX32_SCHED_SETSCHEDULER_PARAM  4  /* [FIELD(sa_sched_setscheduler.sa_param)] */
#define __OFFSET_SPAWN_ACTIONX32_SCHED_SETSCHEDULER_POLICY 8  /* [FIELD(sa_sched_setscheduler.sa_policy)] */
#define __OFFSET_SPAWN_ACTIONX32_OPENAT_FD                 4  /* [FIELD(sa_openat.sa_fd)] */
#define __OFFSET_SPAWN_ACTIONX32_OPENAT_DFD                8  /* [FIELD(sa_openat.sa_dfd)] */
#define __OFFSET_SPAWN_ACTIONX32_OPENAT_FILENAME           12 /* [FIELD(sa_openat.sa_filename)] */
#define __OFFSET_SPAWN_ACTIONX32_OPENAT_OFLAGS             16 /* [FIELD(sa_openat.sa_oflags)] */
#define __OFFSET_SPAWN_ACTIONX32_OPENAT_MODE               20 /* [FIELD(sa_openat.sa_mode)] */
#define __OFFSET_SPAWN_ACTIONX32_CLOSE_FD                  4  /* [FIELD(sa_close.sa_fd)] */
#define __OFFSET_SPAWN_ACTIONX32_CLOSERANGE_LOFD           4  /* [FIELD(sa_closerange.sa_lofd)] */
#define __OFFSET_SPAWN_ACTIONX32_CLOSERANGE_HIFD           8  /* [FIELD(sa_closerange.sa_hifd)] */
#define __OFFSET_SPAWN_ACTIONX32_DUP2_OLDFD                4  /* [FIELD(sa_dup2.sa_oldfd)] */
#define __OFFSET_SPAWN_ACTIONX32_DUP2_NEWFD                8  /* [FIELD(sa_dup2.sa_newfd)] */
#define __OFFSET_SPAWN_ACTIONX32_TCSETPGRP_TTYFD           4  /* [FIELD(sa_tcsetpgrp.sa_ttyfd)] */
#define __OFFSET_SPAWN_ACTIONX32_UMASK_MASK                4  /* [FIELD(sa_umask.sa_mask)] */
#define __OFFSET_SPAWN_ACTIONX32_FSMODE_MASK               4  /* [FIELD(sa_fsmode.sa_mask)] */
#define __OFFSET_SPAWN_ACTIONX32_FSMODE_FLAG               8  /* [FIELD(sa_fsmode.sa_flag)] */

#ifdef __CC__
struct __sigset_struct;
struct sched_param;
struct spawn_actionx32 /*[PREFIX(sa_)]*/ {
	__UINT32_TYPE__ sa_type; /* Action type (one of `SPAWN_ACTION_*') */
	union {

		struct {
			__HYBRID_PTR32(struct __sigset_struct) sa_sigset;   /* [1..1] Signal set */
			__UINT32_TYPE__                        sa_sigsetsz; /* Signal set size (in bytes) */
		} sa_sigdfl; /* SPAWN_ACTION_SIGDFL */

		struct {
			__HYBRID_PTR32(struct __sigset_struct) sa_sigset;   /* [1..1] Signal set */
			__UINT32_TYPE__                        sa_sigsetsz; /* Signal set size (in bytes) */
		} sa_sigprocmask; /* SPAWN_ACTION_SIGPROCMASK */

		struct {
			__UINT32_TYPE__ sa_pid; /* Process group ID for the child process (or 0 to place the child process in its own group) */
		} sa_setpgid; /* SPAWN_ACTION_SETPGID */

		struct {
			__HYBRID_PTR32(struct sched_param) sa_param; /* [1..1] Scheduler params */
		} sa_sched_setparam; /* SPAWN_ACTION_SCHED_SETPARAM */

		struct {
			__HYBRID_PTR32(struct sched_param) sa_param;  /* [1..1] Scheduler params */
			__ULONG32_TYPE__                   sa_policy; /* Scheduler policy */
		} sa_sched_setscheduler; /* SPAWN_ACTION_SCHED_SETSCHEDULER */

		struct {
			__INT32_TYPE__             sa_fd;       /* Target FD number (the FD number in which the handle will be stored)
			                                         * HINT: chroot()+chdir() during spawn() can be implemented by using
			                                         *       AT_FDROOT / AT_FDCWD here! */
			__INT32_TYPE__             sa_dfd;      /* Directory FD to which the given filename is relative. */
			__HYBRID_PTR32(char const) sa_filename; /* [1..1] The name of the file to-be opened. */
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
			__UINT32_TYPE__            sa_oflags;   /* Open flags. */
#else /* __USE_KOS || __USE_KOS_KERNEL */
			__INT32_TYPE__             sa_oflags;   /* Open flags. */
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
			__UINT32_TYPE__            sa_mode;     /* File creation mode. */
		} sa_openat; /* SPAWN_ACTION_OPENAT */

		struct {
			__INT32_TYPE__      sa_fd;       /* FD number to-be closed */
		} sa_close; /* SPAWN_ACTION_CLOSE */

		struct {
			__UINT32_TYPE__     sa_lofd;     /* First file descriptor to-be closed */
			__UINT32_TYPE__     sa_hifd;     /* Last file descriptor to-be closed */
		} sa_closerange; /* SPAWN_ACTION_CLOSERANGE */

		struct {
			__INT32_TYPE__      sa_oldfd;    /* Old file descriptor number */
			__INT32_TYPE__      sa_newfd;    /* New file descriptor number */
		} sa_dup2; /* SPAWN_ACTION_DUP2 */

		struct {
			__INT32_TYPE__      sa_ttyfd;    /* File descriptor for the TTY to update. */
		} sa_tcsetpgrp; /* SPAWN_ACTION_TCSETPGRP */

		struct {
			__UINT32_TYPE__     sa_mask;     /* The new umask to apply. */
		} sa_umask; /* SPAWN_ACTION_UMASK */

		struct {
			__UINT32_TYPE__     sa_mask;     /* FS mode mask (set of bits to keep). */
			__UINT32_TYPE__     sa_flag;     /* FS mode flag (set of bits to set). */
		} sa_fsmode; /* SPAWN_ACTION_FSMODE */

	};
};

struct spawn_action_listx32 {
	__HYBRID_PTR32(struct spawn_action_listx32) sal_next;          /* [0..1] Next set of actions. */
	__UINT32_TYPE__                             sal_stride;        /* == sizeof(struct spawn_action) */
	__UINT32_TYPE__                             sal_count;         /* # of actions specified in `sal_actions' */
	struct spawn_actionx32                      sal_actions[1024]; /* [sas_count] Vector of actions. */
};

struct spawn_actionsx32 {
	__ULONG32_TYPE__            sas_clone_flags; /* Flags to-be used for spawning the new process (Set of `CLONE_*') */
	__HYBRID_PTR32(void)        sas_reserved1;   /* Reserved (must be NULL) */
	__HYBRID_PTR32(void)        sas_reserved2;   /* Reserved (must be NULL) */
	struct spawn_action_listx32 sas_actions;     /* Actions to-be taken for modifying the new process's execution context. */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_SPAWN_ACTION32_H */
