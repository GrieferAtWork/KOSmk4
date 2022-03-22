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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pid.h>

#include <hybrid/sync/atomic-rwlock.h>

#include <bits/os/siginfo.h>

#include <libc/string.h> /* __libc_memset() */


#ifdef __CC__
DECL_BEGIN

/************************************************************************/
/* SIGNAL SCHEDULING                                                    */
/************************************************************************/

struct task;
struct taskpid;
struct procgrp;

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */


/* Raise a posix signal within a given thread `target'
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given thread `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or > `_NSIG' */
FUNDEF NONNULL((1, 2)) __BOOL FCALL
task_raisesignalthread(struct task *__restrict target,
                       siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE);

/* Raise a posix signal within the given process `proc'
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `_NSIG+1' */
FUNDEF NONNULL((1, 2)) __BOOL FCALL
task_raisesignalprocess(struct taskpid *__restrict proc,
                        siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE);


/* Send a signal to every process within the given `group'
 * @return: * : The number of processes to which the signal was delivered. */
FUNDEF NONNULL((1, 2, 3)) size_t FCALL
task_raisesignalprocessgroup(struct procgrp *__restrict group,
                             siginfo_t const *__restrict info,
                             struct taskpid *__restrict sender)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE);

/* Same as `task_raisesignalprocessgroup()', but `signo' must be in range `1..31',
 * allowing this function to use "non-queuing" signals, thus preventing the chance
 * of running out of memory while trying to send a signal.
 * NOTE: This function is unable to encode a sender PID/UID, and instead uses
 *       defaults (s.a. `userexcept_exec_user_signo_rpc()') for this purpose. */
FUNDEF NONNULL((1)) size_t FCALL
_task_raisesignoprocessgroup(struct procgrp *__restrict group, signo_t signo)
		THROWS(E_WOULDBLOCK);
/* Like `_task_raisesignoprocessgroup()' is to `task_raisesignalprocessgroup()',
 * but for a single process. This is in fact the same as  `proc_sig_schedule()'. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL _task_raisesignoprocess)(struct taskpid *__restrict proc, signo_t signo)
		ASMNAME("proc_sig_schedule");
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL _task_raisesignothread)(struct task *__restrict thread, signo_t signo)
		ASMNAME("task_sig_schedule");


#ifdef __cplusplus
extern "C++" {

LOCAL ATTR_ARTIFICIAL NONNULL((1)) __BOOL FCALL
task_raisesignalthread(struct task *__restrict target, signo_t signo)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalthread(target, &info);
}

LOCAL ATTR_ARTIFICIAL NONNULL((1)) __BOOL FCALL
task_raisesignalprocess(struct taskpid *__restrict target, signo_t signo)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocess(target, &info);
}

LOCAL ATTR_ARTIFICIAL NONNULL((1, 3)) size_t FCALL
task_raisesignalprocessgroup(struct procgrp *__restrict target, signo_t signo,
                             struct taskpid *__restrict sender)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocessgroup(target, &info, sender);
}

LOCAL ATTR_ARTIFICIAL NONNULL((1)) size_t FCALL
task_raisesignalprocessgroup(struct procgrp *__restrict target, signo_t signo)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	return task_raisesignalprocessgroup(target, signo, task_gettaskpid());
}

LOCAL ATTR_ARTIFICIAL NONNULL((1, 2)) size_t FCALL
task_raisesignalprocessgroup(struct procgrp *__restrict target,
                             siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	return task_raisesignalprocessgroup(target, info, task_gettaskpid());
}

} /* extern "C++" */
#endif /* __cplusplus */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H */
