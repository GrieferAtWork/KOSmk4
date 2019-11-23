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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H
#define GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H 1

#include <kernel/compiler.h>

#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_H
#include <sched/pid.h>
#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_H */
#ifndef GUARD_KERNEL_INCLUDE_DEV_TTYBASE_H
#include <dev/ttybase.h>
#endif /* !GUARD_KERNEL_INCLUDE_DEV_TTYBASE_H */

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

DECL_BEGIN

#ifdef __CC__

/* Return a reference to the controlling terminal of the calling/given process. */
FORCELOCAL WUNUSED REF struct ttybase_device *KCALL task_getctty(void) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED REF struct ttybase_device *NOTHROW(KCALL task_getctty_nx)(void);
FORCELOCAL WUNUSED REF struct ttybase_device *KCALL task_getctty_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED REF struct ttybase_device *NOTHROW(KCALL task_getctty_of_nx)(struct task *__restrict thread);


/* The character device made available under /dev/ttybase_device
 * This device implements all operators as direct aliasing callbacks
 * to the TTY character device addressable through `task_getctty()' */
DATDEF struct character_device dev_tty;

#define __TASK_CTTY_FIELD(thread) \
	((XATOMIC_WEAKLYREF(struct ttybase_device) &)FORTASK(thread, this_taskgroup).tg_ctty)

#ifndef __INTELLISENSE__


FORCELOCAL WUNUSED REF struct ttybase_device *KCALL
task_getctty(void) THROWS(E_WOULDBLOCK) {
	REF struct ttybase_device *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader();
	result = (REF struct ttybase_device *)__TASK_CTTY_FIELD(session_leader).get();
	decref_unlikely(session_leader);
	return result;
}

FORCELOCAL WUNUSED REF struct ttybase_device *
NOTHROW(KCALL task_getctty_nx)(void) {
	REF struct ttybase_device *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader_nx();
	if unlikely(!session_leader)
		return NULL;
	result = (REF struct ttybase_device *)__TASK_CTTY_FIELD(session_leader).get();
	decref_unlikely(session_leader);
	return result;
}

FORCELOCAL WUNUSED REF struct ttybase_device *KCALL
task_getctty_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct ttybase_device *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader_of(thread);
	result = (REF struct ttybase_device *)__TASK_CTTY_FIELD(session_leader).get();
	decref_unlikely(session_leader);
	return result;
}

FORCELOCAL WUNUSED REF struct ttybase_device *
NOTHROW(KCALL task_getctty_of_nx)(struct task *__restrict thread) {
	REF struct ttybase_device *result;
	REF struct task *session_leader;
	session_leader = task_getsessionleader_of_nx(thread);
	if unlikely(!session_leader)
		return NULL;
	result = (REF struct ttybase_device *)__TASK_CTTY_FIELD(session_leader).get();
	decref_unlikely(session_leader);
	return result;
}
#endif /* !__INTELLISENSE__ */



#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H */
