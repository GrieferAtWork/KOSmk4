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

#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
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


/* TODO: Mem-parts need to have a mechanism that will
 *       asynchronously write changed blocks to  disk
 * - This would  essentially be  a  slightly modified,  and  async
 *   version of `mpart_lock_acquire_and_setcore_denywrite_nodma').
 * - Following the completion of the sync, check if the part has 1-2 reference
 *   left (+1: current-working-reference, +1: if `MPART_F_GLOBAL_REF' is set).
 *   Note  the check order  here which must interlock  with the invariant that
 *   `MPART_F_GLOBAL_REF' can only ever be cleared once!
 * - If `MPART_F_GLOBAL_REF' is set, check if the associated file is MFILE_F_PERSISTENT for being set.
 * - If so, goto `cleanup'. Else, acquire a lock to the file (if not anon)
 *   and the global parts list.
 * - If afterwards the reference counter is still 2 and no unsynced changes exist,
 *   we know that  nothing else  is using  the part and  we can  proceed to  clear
 *   `MPART_F_GLOBAL_REF', drop the inherited reference,  unlock the file and  the
 *   global list, and finally  drop the working reference  which will then end  up
 *   destroying the part. (The file and global  list locks are needed to keep  the
 *   part invisible while we're check if it's invisible. - Without it, we couldn't
 *   ensure that the part  does not randomly  become used by  some other piece  of
 *   code)
 * - When `MPART_F_GLOBAL_REF' wasn't set, simply drop the working reference  (which
 *   should also cause the part to be destroyed). When the part doesn't end up being
 *   destroyed, it may be a good idea to pass it along to `mpart_merge()'...
 * cleanup:
 * - Check if `MPART_F_NOFREE' is set, and if so: return and do nothing
 * - Check if it's possible to change the part's state to `MPART_ST_VOID', which can
 *   be done if there no unsynced changes (changes may still exist if the associated
 *   file doesn't support `mo_saveblocks').
 * - If the state can be set to `MPART_ST_VOID', make the change before also clearing
 *   `MPART_F_BLKST_INL', and dealloc  `mp_blkst_ptr' (if  appropriate), and  setting
 *   `mp_blkst_ptr = NULL'.
 * - If the state cannot be set to `MPART_ST_VOID', consider offloading the part into
 *   swap  memory (for this purpose there should be  a flag that gets set by the orig
 *   call to `mpart_unload()', which takes a flags argument of actions to perform for
 *   the purpose of unloading)
 *
 * Once implemented, this will form the basis of unloading unused file data
 * as  the result of wanting to free up memory after `system_clearcache()',
 * or as the result of a failed allocation:
 *  - Writing changed file contents to disk
 *  - Swap off-loading changed blocks of anonymous files, or files that don't
 *    support a write-back operator
 *  - Unloading file data that was accessed, but is no longer being used
 *
 * This mechanism is needed for:
 *  - Memory-unload-for-cache-clearing (including the automatic write-back
 *    of any remaining unwritten changes)
 *  - The implementation of `flatdirnode_anon_parts_after()' which needs
 *    a way to get rid of mem-parts which were originally allocated  for
 *    memory beyond the (then-lowered) end of the directory stream.  (In
 *    this case, larger gaps within the directory stream would be gotten
 *    rid of automatically during cache clear operations)
 *    For this case,  there would also  need to  be a version  of the  unload
 *    function: `mfile_unload(struct mfile *self, pos_t start, pos_t count)',
 *    that also exists as a variant where all parts that can result in errors
 *    being  thrown synchronously getting  preallocated beforehand (since the
 *    full unload path may include the creation of an async worker)
 *
 * All  of this functionality needs to be implemented by a new
 * function, which will do all of this via asynchronous means:
 * >> FUNDEF NOBLOCK NONNULL((1)) void
 * >> NOTHROW(FCALL mpart_unload)(struct mpart *__restrict self);
 *
 * When the file backing `self' doesn't have an `mo_saveblocks' operator,
 * then  this function should  also be able to  off-load parts into swap.
 *
 * As far as semantics go, `mpart_unload()' should be called in any case
 * where some mem-part is known to  no longer be needed, representing  a
 * hint to unload  it (and _only_  a hint; this  function will never  do
 * anything that could result in the part's backing data becoming lost).
 *
 * Since this operation needs to be asynchronous, it could be implemented
 * by use of async jobs.
 *
 * NOTE: As far as the implementation goes, it might be suitable to define
 *       a global async worker who's sole purpose is to reap a global list
 *       of mem-parts that are  supposed to be unloaded.  `mpart_unload()'
 *       is then implemented by ATOMIC_FETCHOR-setting a flag to  indicate
 *       that the part was added to said list, before SLIST_ATOMIC_INSERT-
 *       ing the part into said list  (the list also inherits a  reference
 *       to the part during this process).
 *       To work around the problem that mpart doesn't contain any
 *       free fields in  this scenario, we  can do the  following:
 *        - If the part is apart of `mpart_all_list', simply set a global
 *          flag  that tells the async worker for mpart unloading to scan
 *          the global list  of mem-parts for  any featuring the  should-
 *          unload flag.
 *        - If the part isn't apart of `mpart_all_list', add it to the
 *          list before doing the same  as the previous case (XXX:  is
 *          there any reason why some  part shouldn't be added to  the
 *          global list? I can only imagine that it might be important
 *          to document that  `mpart_unload()' may add  a part to  the
 *          global list if it's not already apart of it)
 *          XXX: Is this really a good  idea? I know that the  mpart_merge
 *               system also does this, but it doing so I also find to  be
 *               a  very bad idea that should probably be revisited in the
 *               future, simply because it doesn't scale at all when there
 *               are thousands of mpart-s in the global list...
 *          See the TODO below, which suggests adding a new pointer to
 *          mpart for the purpose of chaining parts which are supposed
 *          to be unloaded.
 *
 * There  also needs to be a synchronous variant of `mpart_unload()' that
 * can be called from `system_clearcache()' and returns information about
 * how  much memory became free as a result. This version can also be the
 * one that is used to implement the async-job variant! */



/* Try to (asynchronously) sync unwritten data of `self' before unload `self' from memory.
 * Note that contrary to its name, this function will never unload memory that is actually
 * still in use, or in a  way by which said memory  cannot be recovered (by re-loading  it
 * from swap). Instead, this function only tries  to unload pre-loaded file data, as  well
 * write-back changed file data to  disk so-as to make  it possible to essentially  change
 * the state of `self' to `MPART_ST_VOID' (or simply destroy `self' all-together).
 * @param: self:  The mem-part which should be unloaded. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_unload)(/*inherit(always)*/ REF struct mpart *__restrict self) {
	/* TODO: Try to do the unload synchronously before falling back to an async worker! */
	mpart_start_asyncjob(self, MPART_XF_WILLUNLOAD);
}


/* Synchronous version of `mpart_unload()'. Upon entry, the caller must be holding a lock
 * to `self' and `unlock'. The lock to  `self' is unconditionally released, but the  lock
 * to `unlock' is  only released when  `false' is  returned, or an  exception is  thrown.
 * Locking logic:
 *  - return != MPART_UNLOADNOW_ST_RETRY:
 *    - !mpart_lock_acquired(self);
 *    - decref(self);
 *  - return == MPART_UNLOADNOW_ST_RETRY:
 *    - !mpart_lock_acquired(self);
 *    - unlockinfo_xunlock(unlock);
 *  - EXCEPT:
 *    - !mpart_lock_acquired(self);
 *    - unlockinfo_xunlock(unlock);
 * @param: flags: Set of `MPART_UNLOADNOW_F_*'
 * @param: self:  The mem-part which should be unloaded. */
PUBLIC BLOCKING NONNULL((1)) unsigned int FCALL
mpart_unloadnow_or_unlock(/*inherit(on_success)*/ REF struct mpart *__restrict self,
                          unsigned int flags, struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, ...) {
	assert(mpart_lock_acquired(self));
	/* TODO: Do the unload synchronously. - When blocking becomes necessary,  release
	 *       locks, do the blocking operation, and return `MPART_UNLOADNOW_ST_RETRY'. */
	(void)flags;
	(void)unlock;

	mpart_lock_release(self);
	decref(self);
	return MPART_UNLOADNOW_ST_INUSE;
}



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
	(MPART_XF_WILLMERGE | MPART_XF_WILLTRIM | MPART_XF_WILLUNLOAD)

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
		ATOMIC_AND(part->mp_xflags, ~MPART_XF_WILLMERGE);

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

	if (part->mp_xflags & MPART_XF_WILLUNLOAD) {
		ATOMIC_AND(part->mp_xflags, ~MPART_XF_WILLUNLOAD);
		/* TODO */
	}

	if (part->mp_xflags & MPART_XF_WILLTRIM) {
		/* TODO: Just like with `MPART_XF_WILLMERGE', we really
		 *       need a  new function:  `mpart_trim_or_unlock'! */
		ATOMIC_AND(part->mp_xflags, ~MPART_XF_WILLTRIM);
		mpart_trim(incref(part));
	}

	/* Clear the `MPART_XF_INJOBLIST',  but only if  none
	 * of the other `MPART_XF_WILL*' flags are still set,
	 * as may be the case if another thread re-set  them. */
	for (;;) {
		uintptr_quarter_t xflags;
		xflags = ATOMIC_READ(part->mp_xflags);
		assert(xflags & MPART_XF_INJOBLIST);
		if (xflags & MPART_XF_WILLMASK)
			goto again;
		if (ATOMIC_CMPXCH_WEAK(part->mp_xflags, xflags,
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


/* Try to allocate a new async job to  do `what', but if that fails use a  fallback
 * global  async job to do the same thing. _DONT_ call this function directly! This
 * function is used as the fallback-path when one of mpart named mem-part functions
 * can't be completed without  blocking, meaning that it  needs to be finished  via
 * async means. - If  you were to  call this function  directly, that initial  non-
 * blocking  attempt  would not  be  performed, which  would  introduce unnecessary
 * overhead  in the  case where the  operation could have  been done synchronously.
 * When multiple operations are scheduled at the same time, they will be  performed
 * in the following order:
 *  - MPART_XF_WILLMERGE:  `mpart_merge()'
 *  - MPART_XF_WILLUNLOAD: `mpart_unload()'
 *  - MPART_XF_WILLTRIM:   `mpart_trim()'
 * @param: what: Set of `MPART_XF_WILLMERGE | MPART_XF_WILLTRIM | MPART_XF_WILLUNLOAD' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_start_asyncjob)(/*inherit(always)*/ REF struct mpart *__restrict self,
                                    uintptr_quarter_t what) {
	uintptr_quarter_t old_flags;
	assert((what & ~(MPART_XF_WILLMERGE | MPART_XF_WILLTRIM | MPART_XF_WILLUNLOAD)) == 0);
	assert((what & (MPART_XF_WILLMERGE | MPART_XF_WILLTRIM | MPART_XF_WILLUNLOAD)) != 0);
	old_flags = ATOMIC_FETCHOR(self->mp_xflags, what | MPART_XF_INJOBLIST);
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
	return ATOMIC_READ(mpart_ajob_fallback_list.slh_first) != NULL;
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
	.ao_destroy = (typeoffield(struct async_ops, ao_destroy))(void *)-1,
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
