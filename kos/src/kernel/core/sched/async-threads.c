/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_ASYNC_THREADS_C
#define GUARD_KERNEL_SRC_SCHED_ASYNC_THREADS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <sched/async-intern.h>
#include <sched/async.h>
#include <sched/rpc-internal.h>
#include <sched/task.h>

#include <hybrid/sequence/bsearch.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>

DECL_BEGIN

PRIVATE struct async_thread_data _asyncwork_data = {
	.atd_refcnt  = 2, /* +1: _asyncwork_data, +1: _async_workers_deafult.atc_threads[0] */
	.atd_thread  = &asyncwork,
	.atd_sleepon = NULL,
	.atd_killrpc = NULL, /* `asyncwork' can't be killed, so this can be `NULL'! */
};


/* The default set of async workers (which is exactly 1, that is `asyncwork'). */
PRIVATE struct async_thread_controller _async_workers_deafult = {
	.atc_refcnt  = 2, /* +1: _async_workers_deafult, +1: async_threads */
	.atc_count   = 1,
	.atc_threads = { &_asyncwork_data },
};

/* Destroy the given async-thread-data. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_thread_data_destroy)(struct async_thread_data *__restrict self) {
	if (self->atd_killrpc) {
		assert(!(self->atd_killrpc->pr_flags & _RPC_CONTEXT_DONTFREE));
		pending_rpc_free(self->atd_killrpc);
	}
	decref(self->atd_thread);
	kfree(self);
}

/* Destroy the given async-thread-controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_thread_controller_destroy)(struct async_thread_controller *__restrict self) {
	size_t i;
	for (i = 0; i < self->atc_count; ++i)
		decref(self->atc_threads[i]);
	kfree(self);
}


/* [1..1] The current controller for running async worker threads. */
PUBLIC struct async_thread_controller_arref
async_threads = ARREF_INIT(&_async_workers_deafult);


/* Spawn a new async worker thread, and return a reference to it. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct task *FCALL
async_threads_spawn(void) THROWS(E_BADALLOC) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

/* Kill the given async-worker-thread.
 * @return: true:  Success: The given `thread' will soon be dead!
 * @return: false: Either  `thread' isn't an  async-worker thread, is the
 *                 root async worker thread (`asyncwork'), or has already
 *                 been killed (the  thread actually terminating  happens
 *                 asynchronously, and independent of this function) */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL async_threads_kill)(struct task *__restrict thread) {
	size_t i;
	REF struct async_thread_controller *ctl;
	ctl = arref_get(&async_threads);
	BSEARCH (i, ctl->atc_threads, ctl->atc_count, ->atd_thread, thread) {
		REF struct async_thread_data *dat;
		struct pending_rpc *rpc;
		dat = incref(ctl->atc_threads[i]);
		decref_unlikely(ctl);
		rpc = atomic_xch(&dat->atd_killrpc, NULL);
		if (!rpc) {
			/* Already killed... (or not allowed to kill) */
			decref_unlikely(dat);
			return false;
		}
		decref_unlikely(dat);

		/* Deliver the pending kill-rpc.
		 * All of the remaining work needed to get rid of `thread'
		 * will  then  be performed  from within  `thread' itself! */
		if unlikely(!task_rpc_schedule(thread, rpc)) {
			/* Deal with the possibility that the async-worker thread
			 * died through other means? */
			assert(!(rpc->pr_flags & _RPC_CONTEXT_DONTFREE));
			pending_rpc_free(rpc);
		}
		return true;
	}
	decref_unlikely(ctl);
	return false;
}


/* Count & return the # of live threads described by `self' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL async_thread_controller_livecount)(struct async_thread_controller const *__restrict self) {
	size_t i, result = 0;
	for (i = 0; i < self->atc_count; ++i) {
		struct async_thread_data *thread;
		thread = self->atc_threads[i];
		if (thread->atd_thread == &asyncwork ||
		    thread->atd_killrpc != NULL)
			++result; /* This one's live! */
	}
	return result;
}

/* Get/Set the # of async worker threads running on the system. */
PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(FCALL async_threads_getcount)(void) {
	size_t result;
	REF struct async_thread_controller *ctl;
	ctl    = arref_get(&async_threads);
	result = async_thread_controller_livecount(ctl);
	decref_unlikely(ctl);
	return result;
}

PUBLIC size_t FCALL
async_threads_setcount(size_t new_count) THROWS(E_BADALLOC) {
	size_t old_count;
	REF struct async_thread_controller *ctl;
	ctl       = arref_get(&async_threads);
	old_count = async_thread_controller_livecount(ctl);
	FINALLY_DECREF_UNLIKELY(ctl);
	if (old_count != new_count) {
		if (old_count > new_count) {
			size_t i, num_kill;
			num_kill = old_count - new_count;
			/* Kill some of the threads. */
			for (i = 0; i < ctl->atc_count && num_kill; ++i) {
				if (async_threads_kill(ctl->atc_threads[i]->atd_thread))
					--num_kill;
			}
		} else {
			size_t num_more;
			/* Spawn some more threads. */
			num_more = new_count - old_count;
			while (num_more--) {
				decref_unlikely(async_threads_spawn());
			}
		}
	}
	return old_count;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_ASYNC_THREADS_C */
