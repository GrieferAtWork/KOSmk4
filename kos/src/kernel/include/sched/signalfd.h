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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGNALFD_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGNALFD_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/types.h>

#include <bits/sigset.h>

/* signalfd() objects are really very simple:
 * read(): >> CHECK_PENDING_SIGNALS(domain: PROCESS | THREAD, mask: sf_mask)
 *         -> Translate any such pending signal into `struct signalfd_siginfo',
 *            after removing it from the signal queue.
 *            Note that the checked domain is always PROCESS and THREAD of the
 *            calling thread, meaning that sharing signalfd handles between
 *            processes does _not_ actually share the poll of polled signals.
 *            This behavior is implied by the linux documentation:
 *            ```
 *            After a fork(2), the child inherits a copy of the signalfd file
 *            descriptor.  A read(2) from the file descriptor in the child will
 *            return information about signals queued to the child.
 *            ```
 *            So in other words: It always polls your own pending signals!
 * poll(): >> task_connect(PROCESS->SIGQUEUE->AVAIL);
 *         >> task_connect(THREAD->SIGQUEUE->AVAIL);
 */

DECL_BEGIN

#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

struct signalfd {
	WEAK refcnt_t sf_refcnt; /* Reference counter. */
	sigset_t      sf_mask;   /* Mask of signals polled by this signalfd. */
};

DEFINE_REFCOUNT_FUNCTIONS(struct signalfd, sf_refcnt, kfree)

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNALFD_H */
