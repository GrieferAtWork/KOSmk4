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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ASYNC_INTERN_H
#define GUARD_KERNEL_INCLUDE_SCHED_ASYNC_INTERN_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_ASYNC
#include <kernel/types.h>
#include <sched/async.h>

#include <kos/aref.h>

#ifdef __CC__

DECL_BEGIN

struct async_thread_data {
	/* Per-async-worker-thread controller context. */
	REF struct task *atd_thread;  /* [1..1][const] The async-worker thread in question. */
	struct async    *atd_sleepon; /* [0..1][lock(PRIVATE(THIS_TASK))] The job that  this
	                               * thread is currently sleeping upon in order to await
	                               * its timeout to expire.
	                               * NOTE: When the  controller is  copied, this  field
	                               *       is initialized as `NULL', since the original
	                               *       thread wouldn't know  that its  thread-local
	                               *       area was allocated anew. */
};

struct async_thread_controller {
	/* Async thread controller.  - Used to  maintain the list  of
	 * running async worker threads, as well as to maintain their
	 * individual per-thread variables. */
	WEAK refcnt_t                                     atc_refcnt;   /* Reference counter. */
	size_t                                            atc_count;    /* [const] # of threads */
	COMPILER_FLEXIBLE_ARRAY(struct async_thread_data, atc_threads); /* [atc_count] Per-thread  info  (sorted  ascendingly
	                                                                 * by `ADDROF(atd_thread)', thus allowing for threads
	                                                                 * to be located via BSEARCH) */
};

/* Destroy the given async-thread-controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_thread_controller_destroy)(struct async_thread_controller *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct async_thread_controller, atc_refcnt, async_thread_controller_destroy);


#ifndef __async_thread_controller_arref_defined
#define __async_thread_controller_arref_defined 1
ARREF(async_thread_controller_arref, async_thread_controller);
#endif /* !__async_thread_controller_arref_defined */

/* [1..1] The current controller for running async worker threads. */
DATDEF struct async_thread_controller_arref async_threads;


/* TODO: Functions to control the # of async worker-threads. */


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_ASYNC */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ASYNC_INTERN_H */
