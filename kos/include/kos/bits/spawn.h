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
#ifndef _KOS_BITS_SPAWN_H
#define _KOS_BITS_SPAWN_H 1

#include <__stdinc.h>

#include <kos/bits/spawn-action.h>

/* Spawn action type codes.
 * NOTES:
 *   - Actions are executed in ascending order:
 *     >> struct sas_actions *act = &actions->sas_actions;
 *     >> do {
 *     >>     size_t i;
 *     >>     for (i = 0; i < act->sal_count; ++i) {
 *     >>         do_action((struct spawn_action *)((byte_t *)act->sal_actions +
 *     >>                                           i * act->sal_stride));
 *     >>     }
 *     >>     act = act->sal_next;
 *     >> } while (act);
 *
 *   - Spawn actions that take file descriptors as arguments always operate
 *     on the then-current file descriptor table state of the child process,
 *     with respect to any manipulation which may have already been performed
 *     by a previous step.
 *     Be warned though that with passing `CLONE_FILES', the child process
 *     will share its descriptor table with your own process, meaning that
 *     when `CLONE_FILES' is passed, descriptor manipulation actions become
 *     pretty much pointless (since you could have just as well done them
 *     yourself before calling `process_spawn(2)').
 *
 *   - The `actions->sas_clone_flags' flagset mustn't contain any of the
 *     following flags. If one of these flags is contained, `process_spawn(2)'
 *     will always fail with an E_INVALID_ARGUMENT exception:
 *        CLONE_VM | CLONE_SIGHAND | CLONE_VFORK | CLONE_THREAD | CLONE_SETTLS |
 *        CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID
 *
 *   - Before any action is performed, the child process will have already been
 *     created, though will not yet be visible in /proc, but will by default have
 *     inherited it's parent process's components as specified by `actions->sas_clone_flags'
 *     Note that for this purpose, file handles marked as O_CLOEXEC or O_CLOFORK
 *     (unless `CLONE_FILES' was set) will have both already been closed.
 *
 *   - `process_spawn(2)' will propagate any exception in the following order:
 *     #1: Clone the calling thread, but assign a new VM, and
 *         Load the filesystem location described by `DFD:PATHNAME'
 *         (some) possible errors:  ENOENT, ENOMEM
 *     #2: Load the specified executable into the new thread's VM, and
 *         execute all of the specified spawn actions.
 *         (some) possible errors:  ENOEXEC
 *     #3: Make the new thread visible and start it
 *     The following conditions also result an exception, though the point in
 *     time when this exception is propagated is undefined:
 *      - Some other kind of invalid argument or faulty pointer
 *
 *   - The `CLONE_DETACHED' flag can be used to have the new process start out
 *     in a detached state.
 *
 */
#ifndef SPAWN_ACTION_NONE
/*[[[enum]]]*/
#ifdef __CC__
enum {
	SPAWN_ACTION_NONE,               /* No action (ignored) */
	SPAWN_ACTION_SIGDFL,             /* `foreach(s: sa_sigset) sigaction(s, SIG_DFL);' */
	SPAWN_ACTION_SIGPROCMASK,        /* `sigprocmask(SIG_SETMASK, sa_sigset);' */
	SPAWN_ACTION_SETPGID,            /* `setpgid(0, sa_pgid);' */
	SPAWN_ACTION_SETSID,             /* `setsid();' */
	SPAWN_ACTION_SCHED_SETPARAM,     /* `sched_setparam(sa_sched_setparam);' */
	SPAWN_ACTION_SCHED_SETSCHEDULER, /* `sched_setscheduler(sa_sched_setparam);' */
	SPAWN_ACTION_OPENAT,             /* `dup2(openat(sa_dfd, sa_filename, sa_oflags, sa_mode), sa_fd);' */
	SPAWN_ACTION_CLOSE,              /* `close(sa_fd);' */
	SPAWN_ACTION_CLOSERANGE,         /* `for (fd_t f = sa_lofd; f <= sa_hifd; ++f) close(f);'
	                                  * NOTE: Invalid-handle errors are ignored for this operation! */
	SPAWN_ACTION_DUP2,               /* `dup2(sa_oldfd, sa_newfd);' */
	SPAWN_ACTION_TCSETPGRP,          /* `tcsetpgrp(sa_ttyfd, 0);'
	                                  * Set the process group of a terminal to the same group
	                                  * as the child process. This action only makes sense if
	                                  * preceded by `SPAWN_ACTION_SETPGID' and/or `SPAWN_ACTION_SETSID' */
	SPAWN_ACTION_UMASK,              /* `umask(sa_mask);' */
	SPAWN_ACTION_FSMODE,             /* `fsmode(sa_mask, sa_flag);' */
	SPAWN_ACTION_SETUID,             /* `setuid(sa_uid);' */
	SPAWN_ACTION_SETGID,             /* `setgid(sa_gid);' */
	SPAWN_ACTION_SETREUID,           /* `setreuid(sa_ruid, sa_euid);' */
	SPAWN_ACTION_SETREGID,           /* `setregid(sa_rgid, sa_egid);' */
	SPAWN_ACTION_SETRESUID,          /* `setresuid(sa_ruid, sa_euid, sa_suid);' */
	SPAWN_ACTION_SETRESGID,          /* `setresgid(sa_rgid, sa_egid, sa_sgid);' */
	SPAWN_ACTION_SETFSUID,           /* `setfsuid(sa_fsuid);' */
	SPAWN_ACTION_SETFSGID,           /* `setfsgid(sa_fsgid);' */
	SPAWN_ACTION_SETGROUPS,          /* `setgroups(sa_gcnt, sa_gvec);' */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SPAWN_ACTION_NONE               SPAWN_ACTION_NONE               /* No action (ignored) */
#define SPAWN_ACTION_SIGDFL             SPAWN_ACTION_SIGDFL             /* `foreach(s: sa_sigset) sigaction(s, SIG_DFL);' */
#define SPAWN_ACTION_SIGPROCMASK        SPAWN_ACTION_SIGPROCMASK        /* `sigprocmask(SIG_SETMASK, sa_sigset);' */
#define SPAWN_ACTION_SETPGID            SPAWN_ACTION_SETPGID            /* `setpgid(0, sa_pgid);' */
#define SPAWN_ACTION_SETSID             SPAWN_ACTION_SETSID             /* `setsid();' */
#define SPAWN_ACTION_SCHED_SETPARAM     SPAWN_ACTION_SCHED_SETPARAM     /* `sched_setparam(sa_sched_setparam);' */
#define SPAWN_ACTION_SCHED_SETSCHEDULER SPAWN_ACTION_SCHED_SETSCHEDULER /* `sched_setscheduler(sa_sched_setparam);' */
#define SPAWN_ACTION_OPENAT             SPAWN_ACTION_OPENAT             /* `dup2(openat(sa_dfd, sa_filename, sa_oflags, sa_mode), sa_fd);' */
#define SPAWN_ACTION_CLOSE              SPAWN_ACTION_CLOSE              /* `close(sa_fd);' */
#define SPAWN_ACTION_CLOSERANGE         SPAWN_ACTION_CLOSERANGE         /* `for (fd_t f = sa_lofd; f <= sa_hifd; ++f) close(f);'
                                                                         * NOTE: Invalid-handle errors are ignored for this operation! */
#define SPAWN_ACTION_DUP2               SPAWN_ACTION_DUP2               /* `dup2(sa_oldfd, sa_newfd);' */
#define SPAWN_ACTION_TCSETPGRP          SPAWN_ACTION_TCSETPGRP          /* `tcsetpgrp(sa_ttyfd, 0);'
                                                                         * Set the process group of a terminal to the same group
                                                                         * as the child process. This action only makes sense if
                                                                         * preceded by `SPAWN_ACTION_SETPGID' and/or `SPAWN_ACTION_SETSID' */
#define SPAWN_ACTION_UMASK              SPAWN_ACTION_UMASK              /* `umask(sa_mask);' */
#define SPAWN_ACTION_FSMODE             SPAWN_ACTION_FSMODE             /* `fsmode(sa_mask, sa_flag);' */
#define SPAWN_ACTION_SETUID             SPAWN_ACTION_SETUID             /* `setuid(sa_uid);' */
#define SPAWN_ACTION_SETGID             SPAWN_ACTION_SETGID             /* `setgid(sa_gid);' */
#define SPAWN_ACTION_SETREUID           SPAWN_ACTION_SETREUID           /* `setreuid(sa_ruid, sa_euid);' */
#define SPAWN_ACTION_SETREGID           SPAWN_ACTION_SETREGID           /* `setregid(sa_rgid, sa_egid);' */
#define SPAWN_ACTION_SETRESUID          SPAWN_ACTION_SETRESUID          /* `setresuid(sa_ruid, sa_euid, sa_suid);' */
#define SPAWN_ACTION_SETRESGID          SPAWN_ACTION_SETRESGID          /* `setresgid(sa_rgid, sa_egid, sa_sgid);' */
#define SPAWN_ACTION_SETFSUID           SPAWN_ACTION_SETFSUID           /* `setfsuid(sa_fsuid);' */
#define SPAWN_ACTION_SETFSGID           SPAWN_ACTION_SETFSGID           /* `setfsgid(sa_fsgid);' */
#define SPAWN_ACTION_SETGROUPS          SPAWN_ACTION_SETGROUPS          /* `setgroups(sa_gcnt, sa_gvec);' */
#else /* __COMPILER_PREFERR_ENUMS */
#define SPAWN_ACTION_NONE               0  /* No action (ignored) */
#define SPAWN_ACTION_SIGDFL             1  /* `foreach(s: sa_sigset) sigaction(s, SIG_DFL);' */
#define SPAWN_ACTION_SIGPROCMASK        2  /* `sigprocmask(SIG_SETMASK, sa_sigset);' */
#define SPAWN_ACTION_SETPGID            3  /* `setpgid(0, sa_pgid);' */
#define SPAWN_ACTION_SETSID             4  /* `setsid();' */
#define SPAWN_ACTION_SCHED_SETPARAM     5  /* `sched_setparam(sa_sched_setparam);' */
#define SPAWN_ACTION_SCHED_SETSCHEDULER 6  /* `sched_setscheduler(sa_sched_setparam);' */
#define SPAWN_ACTION_OPENAT             7  /* `dup2(openat(sa_dfd, sa_filename, sa_oflags, sa_mode), sa_fd);' */
#define SPAWN_ACTION_CLOSE              8  /* `close(sa_fd);' */
#define SPAWN_ACTION_CLOSERANGE         9  /* `for (fd_t f = sa_lofd; f <= sa_hifd; ++f) close(f);'
                                            * NOTE: Invalid-handle errors are ignored for this operation! */
#define SPAWN_ACTION_DUP2               10 /* `dup2(sa_oldfd, sa_newfd);' */
#define SPAWN_ACTION_TCSETPGRP          11 /* `tcsetpgrp(sa_ttyfd, 0);'
                                            * Set the process group of a terminal to the same group
                                            * as the child process. This action only makes sense if
                                            * preceded by `SPAWN_ACTION_SETPGID' and/or `SPAWN_ACTION_SETSID' */
#define SPAWN_ACTION_UMASK              12 /* `umask(sa_mask);' */
#define SPAWN_ACTION_FSMODE             13 /* `fsmode(sa_mask, sa_flag);' */
#define SPAWN_ACTION_SETUID             14 /* `setuid(sa_uid);' */
#define SPAWN_ACTION_SETGID             15 /* `setgid(sa_gid);' */
#define SPAWN_ACTION_SETREUID           16 /* `setreuid(sa_ruid, sa_euid);' */
#define SPAWN_ACTION_SETREGID           17 /* `setregid(sa_rgid, sa_egid);' */
#define SPAWN_ACTION_SETRESUID          18 /* `setresuid(sa_ruid, sa_euid, sa_suid);' */
#define SPAWN_ACTION_SETRESGID          19 /* `setresgid(sa_rgid, sa_egid, sa_sgid);' */
#define SPAWN_ACTION_SETFSUID           20 /* `setfsuid(sa_fsuid);' */
#define SPAWN_ACTION_SETFSGID           21 /* `setfsgid(sa_fsgid);' */
#define SPAWN_ACTION_SETGROUPS          22 /* `setgroups(sa_gcnt, sa_gvec);' */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !SPAWN_ACTION_NONE */


#endif /* !_KOS_BITS_SPAWN_H */
