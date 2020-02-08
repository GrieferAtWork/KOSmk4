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
#define SPAWN_ACTION_NONE               0x0000 /* No action (ignored) */
#define SPAWN_ACTION_SIGDFL             0x0001 /* `foreach(s: sa_sigset) sigaction(s, SIG_DFL);' */
#define SPAWN_ACTION_SIGPROCMASK        0x0002 /* `sigprocmask(SIG_SETMASK, sa_sigset);' */
#define SPAWN_ACTION_SETPGID            0x0003 /* `setpgid(0, sa_pgid);' */
#define SPAWN_ACTION_SETSID             0x0004 /* `setsid();' */
#define SPAWN_ACTION_SCHED_SETPARAM     0x0005 /* `sched_setparam(sa_sched_setparam);' */
#define SPAWN_ACTION_SCHED_SETSCHEDULER 0x0006 /* `sched_setscheduler(sa_sched_setparam);' */
#define SPAWN_ACTION_OPENAT             0x0007 /* `dup2(openat(sa_dfd, sa_filename, sa_oflags, sa_mode), sa_fd);' */
#define SPAWN_ACTION_CLOSE              0x0008 /* `close(sa_fd);' */
#define SPAWN_ACTION_CLOSERANGE         0x0009 /* `for (fd_t f = sa_lofd; f <= sa_hifd; ++f) close(f);'
                                                * NOTE: Invalid-handle errors are ignored for this operation! */
#define SPAWN_ACTION_DUP2               0x000a /* `dup2(sa_oldfd, sa_newfd);' */
#define SPAWN_ACTION_TCSETPGRP          0x000b /* `tcsetpgrp(sa_ttyfd, 0);'
                                                * Set the process group of a terminal to the same group
                                                * as the child process. This action only makes sense if
                                                * preceded by `SPAWN_ACTION_SETPGID' and/or `SPAWN_ACTION_SETSID' */
#endif /* !SPAWN_ACTION_NONE */


#endif /* !_KOS_BITS_SPAWN_H */
