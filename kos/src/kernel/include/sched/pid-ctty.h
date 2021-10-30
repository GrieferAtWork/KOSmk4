/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H
#define GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H 1

#include <kernel/compiler.h>

#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_H
#include <sched/pid.h>
#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_H */
#ifndef GUARD_KERNEL_INCLUDE_DEV_TTY_H
#include <dev/tty.h>
#endif /* !GUARD_KERNEL_INCLUDE_DEV_TTY_H */

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

DECL_BEGIN

#ifdef __CC__

/* Return a reference to the controlling terminal of the calling/given process. */
LOCAL WUNUSED REF struct ttydev *KCALL task_getctty(void) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED REF struct ttydev *NOTHROW(KCALL task_getctty_nx)(void);
LOCAL WUNUSED REF struct ttydev *KCALL task_getctty_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED REF struct ttydev *NOTHROW(KCALL task_getctty_of_nx)(struct task *__restrict thread);


#ifndef CONFIG_USE_NEW_FS
/* The   character   device   made   available   under   /dev/ttydev
 * This device implements all operators as direct aliasing callbacks
 * to  the TTY character device addressable through `task_getctty()' */
DATDEF struct chrdev dev_tty;
#endif /* !CONFIG_USE_NEW_FS */

#ifndef __INTELLISENSE__
LOCAL WUNUSED REF struct ttydev *KCALL
task_getctty(void) THROWS(E_WOULDBLOCK) {
	REF struct ttydev *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader();
	if unlikely(!session_leader)
		return __NULLPTR;
	result = axref_get(&FORTASK(session_leader, this_taskgroup).tg_ctty);
	decref_unlikely(session_leader);
	return result;
}

LOCAL WUNUSED REF struct ttydev *
NOTHROW(KCALL task_getctty_nx)(void) {
	REF struct ttydev *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader_nx();
	if unlikely(!session_leader)
		return __NULLPTR;
	result = axref_get(&FORTASK(session_leader, this_taskgroup).tg_ctty);
	decref_unlikely(session_leader);
	return result;
}

LOCAL WUNUSED REF struct ttydev *KCALL
task_getctty_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct ttydev *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader_of(thread);
	if unlikely(!session_leader)
		return __NULLPTR;
	result = axref_get(&FORTASK(session_leader, this_taskgroup).tg_ctty);
	decref_unlikely(session_leader);
	return result;
}

LOCAL WUNUSED REF struct ttydev *
NOTHROW(KCALL task_getctty_of_nx)(struct task *__restrict thread) {
	REF struct ttydev *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader_of_nx(thread);
	if unlikely(!session_leader)
		return __NULLPTR;
	result = axref_get(&FORTASK(session_leader, this_taskgroup).tg_ctty);
	decref_unlikely(session_leader);
	return result;
}
#endif /* !__INTELLISENSE__ */



#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H */
