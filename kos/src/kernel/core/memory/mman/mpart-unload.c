/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_UNLOAD_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_UNLOAD_C 1
#define __WANT_SIG_COMPLETION_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/malloc.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <sched/async.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

DECL_BEGIN

#ifndef BADPOINTER
#if __SIZEOF_POINTER__ == 4
#define BADPOINTER UINT32_C(0xcccccccc)
#elif __SIZEOF_POINTER__ == 8
#define BADPOINTER UINT64_C(0xcccccccccccccccc)
#elif __SIZEOF_POINTER__ == 2
#define BADPOINTER UINT16_C(0xcccc)
#elif __SIZEOF_POINTER__ == 1
#define BADPOINTER UINT8_C(0xcc)
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !BADPOINTER */



struct mpart_ajob {
	struct async      mpaj_async; /* Underlying async controller. */
	REF struct mpart *mpaj_part;  /* [0..1][lock(PRIVATE)]  The  part in  question.  Set to
	                               * NULL when `mpart_ajob_v_work' returns != ASYNC_RESUME. */
	unsigned          mpaj_state; /* Current async state (one of `MPART_AJOB_ST_*') */
#define MPART_AJOB_ST_WORKING 0x0000 /* Currently doing work (but not stuff that might ). */
	/* TODO: State for waiting for completion of AIO write-to-disk/swap during unloading. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_ajob_v_destroy)(struct async *__restrict self) {
	struct mpart_ajob *me = (struct mpart_ajob *)self;
	xdecref(me->mpaj_part);
	kfree(me);
}

PRIVATE NONNULL((1)) ktime_t
NOTHROW(FCALL mpart_ajob_v_connect)(struct async *__restrict self) {
	struct mpart_ajob *me = (struct mpart_ajob *)self;
	if (me->mpaj_state != MPART_AJOB_ST_WORKING) {
		/* TODO */
		COMPILER_IMPURE();
		return KTIME_INFINITE;
	}
	return KTIME_NONBLOCK;
}

PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_ajob_v_test)(struct async *__restrict self) {
	struct mpart_ajob *me = (struct mpart_ajob *)self;
	if (me->mpaj_state != MPART_AJOB_ST_WORKING) {
		/* TODO */
		COMPILER_IMPURE();
		return false;
	}
	return true;
}


#define MPART_XF_WILLMASK \
	(MPART_XF_WILLMERGE | MPART_XF_WILLTRIM)

PRIVATE WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_ajob_v_work)(struct async *__restrict self) {
	struct mpart_ajob *me  = (struct mpart_ajob *)self;
	REF struct mpart *part = me->mpaj_part;
	if (me->mpaj_state != MPART_AJOB_ST_WORKING) {
		/* TODO: stuff like handling AIO completion for write-to-disk/swap */
		return ASYNC_RESUME;
	}
again:
	assert(PREEMPTION_ENABLED());
	assert(part->mp_xflags & MPART_XF_INJOBLIST);

	/* Merge the part if the caller requested us to do so. */
	if (part->mp_xflags & MPART_XF_WILLMERGE) {
		atomic_and(&part->mp_xflags, ~MPART_XF_WILLMERGE);

		/* TODO: `mpart_merge_locked()' includes calls to kmalloc(),  but
		 *       if  those  fail, it  will set  `MPART_XF_WILLMERGE' once
		 *       again. That's OK because we handle it below be  starting
		 *       over, but what's not OK is that we don't do anything  in
		 *       the mean time to ensure that we don't end in an infinite
		 *       loop of bad allocations.
		 *
		 * Generally speaking, we really need a `mpart_merge_or_unlock'
		 * function, though...
		 *
		 * Another downside (and reason why this needs a special impl) is
		 * that we can't  keep working  using the merged  part (iow:  the
		 * return value of `mpart_merge()') since that might differ  from
		 * the caller-given `part'. If it does, then we're not allowed to
		 * fiddle  with its `MPART_XF_INJOBLIST'  flag (which most likely
		 * isn't even set, either) */
		decref(mpart_merge(incref(part)));
	}

	if (part->mp_xflags & MPART_XF_WILLTRIM) {
		/* TODO: Just like with `MPART_XF_WILLMERGE', we really
		 *       need a  new function:  `mpart_trim_or_unlock'! */
		atomic_and(&part->mp_xflags, ~MPART_XF_WILLTRIM);
		mpart_trim(incref(part));
	}

	/* Clear the `MPART_XF_INJOBLIST',  but only if  none
	 * of the other `MPART_XF_WILL*' flags are still set,
	 * as may be the case if another thread re-set  them. */
	for (;;) {
		uintptr_quarter_t xflags;
		xflags = atomic_read(&part->mp_xflags);
		assert(xflags & MPART_XF_INJOBLIST);
		if (xflags & MPART_XF_WILLMASK)
			goto again;
		if (atomic_cmpxch_weak(&part->mp_xflags, xflags,
		                       xflags & ~MPART_XF_INJOBLIST))
			break;
	}

	decref(part);
	me->mpaj_part = NULL;
	return ASYNC_FINISHED;
}


PRIVATE struct async_ops const mpart_ajob_ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = &mpart_ajob_v_destroy,
	.ao_connect = &mpart_ajob_v_connect,
	.ao_test    = &mpart_ajob_v_test,
	.ao_work    = &mpart_ajob_v_work,
};


INTDEF struct mpart_ajob mpart_ajob_fallback_worker;
/* Signal broadcast when something gets added to `mpart_ajob_fallback_list' */
PRIVATE struct sig mpart_ajob_fallback_sig = {
#ifndef CONFIG_NO_SMP
	{
#endif /* !CONFIG_NO_SMP */
		.s_con = &mpart_ajob_fallback_worker.mpaj_async.a_comp.sm_set.sms_routes[0].mr_com.sc_con,
#ifndef CONFIG_NO_SMP
	}
#endif /* !CONFIG_NO_SMP */
};


/* [0..n][lock(ATOMIC)] Fallback list of mem-parts with pending async jobs. */
PRIVATE struct REF mpart_slist mpart_ajob_fallback_list =
SLIST_HEAD_INITIALIZER(mpart_ajob_fallback_list);


/* Try to allocate a new async job to do `what', but if that fails, use a fallback
 * global async job to do the same thing. _DONT_ call this function directly! This
 * function is used as the fallback-path when one of the named mem-part  functions
 * can't  be completed without blocking, meaning that  it needs to be finished via
 * async means. - If you  were to call this  function directly, that initial  non-
 * blocking attempt  would not  be performed,  which would  introduce  unnecessary
 * overhead  in the case  where the operation could  have been done synchronously.
 * When multiple operations are scheduled at the same time, they will be performed
 * in the following order:
 *  - MPART_XF_WILLMERGE:  `mpart_merge()'
 *  - MPART_XF_WILLTRIM:   `mpart_trim()'
 * @param: what: Set of `MPART_XF_WILLMERGE | MPART_XF_WILLTRIM' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_start_asyncjob)(/*inherit(always)*/ REF struct mpart *__restrict self,
                                    uintptr_quarter_t what) {
	uintptr_quarter_t old_flags;
	assert((what & ~(MPART_XF_WILLMERGE | MPART_XF_WILLTRIM)) == 0);
	assert((what & (MPART_XF_WILLMERGE | MPART_XF_WILLTRIM)) != 0);
	old_flags = atomic_fetchor(&self->mp_xflags, what | MPART_XF_INJOBLIST);
	if (!(old_flags & MPART_XF_INJOBLIST)) {
		/* It  falls on us to either allocate an async job to do the work,
		 * or (if that fails) to add `self' to the global fallback-list of
		 * parts with pending async jobs. */
		struct mpart_ajob *job;
		job = async_new_gfp_nx(struct mpart_ajob, &mpart_ajob_ops, GFP_ATOMIC);
		if likely(job) {
			job->mpaj_part = self; /* Inherit reference */
			decref(async_start(&job->mpaj_async));
			return;
		}

		/* Fallback: insert  into the global  list of jobs,  and tell the fallback
		 *           worker to do its thing for `self'. Note also that this insert
		 *           inherits our caller-given reference to `self'! */
		SLIST_ATOMIC_INSERT(&mpart_ajob_fallback_list, self, _mp_joblink);
		sig_broadcast(&mpart_ajob_fallback_sig);
		return;
	}
	decref(self);
}



/************************************************************************/
/* Fallback async job worker for mem-part jobs.                         */
/************************************************************************/
PRIVATE NONNULL((1)) ktime_t FCALL
mpart_ajob_fallback_v_connect(struct async *__restrict self) {
	struct mpart_ajob *me = (struct mpart_ajob *)self;
	assert(me == &mpart_ajob_fallback_worker);

	/* Service the current part. */
	if (me->mpaj_part != NULL)
		return mpart_ajob_v_connect(&me->mpaj_async);

	/* Wait for new jobs to appear */
	task_connect(&mpart_ajob_fallback_sig);
	return KTIME_INFINITE;
}

PRIVATE WUNUSED NONNULL((1)) bool FCALL
mpart_ajob_fallback_v_test(struct async *__restrict self) {
	struct mpart_ajob *me = (struct mpart_ajob *)self;
	assert(me == &mpart_ajob_fallback_worker);

	/* Service the current part. */
	if (me->mpaj_part != NULL)
		return mpart_ajob_v_test(&me->mpaj_async);

	/* Check if there are more async jobs. */
	return atomic_read(&mpart_ajob_fallback_list.slh_first) != NULL;
}

PRIVATE WUNUSED NONNULL((1)) unsigned int FCALL
mpart_ajob_fallback_v_work(struct async *__restrict self) {
	REF struct mpart *chain, *next;
	struct mpart_ajob *me = (struct mpart_ajob *)self;
	assert(me == &mpart_ajob_fallback_worker);

	/* Service the current part. */
	if (me->mpaj_part != NULL) {
		unsigned int result;
service_part:
		result = mpart_ajob_v_work(&me->mpaj_async);
		assert(result == ASYNC_RESUME || result == ASYNC_FINISHED);
		assert((me->mpaj_part != NULL) == (result == ASYNC_RESUME));
		if (result == ASYNC_RESUME)
			return result;
		assert(me->mpaj_part == NULL);
	}

	/* Try to load the next part with an async job. */
	chain = SLIST_ATOMIC_CLEAR(&mpart_ajob_fallback_list);
	if unlikely(chain == NULL)
		return ASYNC_RESUME; /* Wait for more parts. */

	/* Restore all elements that come after `chain' */
	next = SLIST_NEXT(chain, _mp_joblink);
	if unlikely(next) {
		REF struct mpart *last;
		last = next;
		while (SLIST_NEXT(last, _mp_joblink))
			last = SLIST_NEXT(last, _mp_joblink);
		SLIST_ATOMIC_INSERT_R(&mpart_ajob_fallback_list, next, last, _mp_joblink);
		sig_broadcast(&mpart_ajob_fallback_sig);
	}

	/* Start servicing `chain' */
	me->mpaj_part  = chain; /* Inherit reference. */
	me->mpaj_state = MPART_AJOB_ST_WORKING;
	goto service_part;
}

PRIVATE struct async_ops const mpart_ajob_fallback_ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = (typeof_field(struct async_ops, ao_destroy))(void *)-1,
	.ao_connect = &mpart_ajob_fallback_v_connect,
	.ao_test    = &mpart_ajob_fallback_v_test,
	.ao_work    = &mpart_ajob_fallback_v_work,
};

INTDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t /* From "sched/async.c" */
NOTHROW(FCALL async_completion)(struct sig_completion *__restrict self,
                                struct sig_completion_context *__restrict context,
                                void *buf, size_t bufsize);

/* Fallback async worker for `mpart_start_asyncjob()'
 * This one's defined as INTERN because it is  linked
 * into the global `async_all_list' by default. */
INTERN struct mpart_ajob mpart_ajob_fallback_worker = {
	.mpaj_async = {
		.a_refcnt = 2, /* +1: mpart_ajob_fallback_worker, +1: async_all_list */
		.a_stat   = _ASYNC_ST_READY,
		.a_ops    = &mpart_ajob_fallback_ops,
		.a_comp   = {
			.sm_set = {
				.sms_next   = NULL,
				.sms_routes = {
					[0] = {
						.mr_com = {
							.sc_con = {
								.tc_sig     = &mpart_ajob_fallback_sig,
								.tc_connext = NULL,
								.tc_signext = NULL,
								{ .tc_stat = TASK_CONNECTION_STAT_COMPLETION },
							},
							.sc_cb  = &async_completion,
						},
						.mr_con = &mpart_ajob_fallback_worker.mpaj_async.a_comp,
					},
#define INIT_ADDITIONAL_CON                                    \
	{                                                          \
		 .mr_com = {                                           \
		 	.sc_con = {                                        \
		 		.tc_sig     = NULL,                            \
		 		.tc_connext = NULL,                            \
		 		.tc_signext = NULL,                            \
		 		{ .tc_stat = TASK_CONNECTION_STAT_BROADCAST }, \
		 	},                                                 \
		 	.sc_cb = NULL,                                     \
		 },                                                    \
		 .mr_con = NULL,                                       \
	}
#if CONFIG_TASK_STATIC_CONNECTIONS >= 2
					[1] = INIT_ADDITIONAL_CON,
#if CONFIG_TASK_STATIC_CONNECTIONS >= 3
					[2] = INIT_ADDITIONAL_CON,
#if CONFIG_TASK_STATIC_CONNECTIONS >= 4
					[3] = INIT_ADDITIONAL_CON,
#if CONFIG_TASK_STATIC_CONNECTIONS >= 5
#error "CONFIG_TASK_STATIC_CONNECTIONS is too large; please adjust this code"
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 5 */
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 4 */
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 3 */
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 2 */
				},
			},
		},
		.a_all = {
			.le_next = NULL,
			.le_prev = &async_all_list.lh_first,
		},
		.a_ready  = { NULL },
		.a_aio    = NULL,
		.a_tmolnk = { (struct async *)BADPOINTER, (struct async **)BADPOINTER },
		{ .a_tmo = KTIME_NONBLOCK },
	},
	.mpaj_part  = NULL,
	.mpaj_state = MPART_AJOB_ST_WORKING,
};


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_UNLOAD_C */
