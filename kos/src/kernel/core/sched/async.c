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
#ifndef GUARD_KERNEL_SRC_SCHED_ASYNC_C
#define GUARD_KERNEL_SRC_SCHED_ASYNC_C 1
#define __WANT_ASYNC__a_lockop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/malloc.h>
#include <sched/async-intern.h>
#include <sched/async.h>
#include <sched/sig.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/bsearch.h>

#include <kos/lockop.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

#define async_as_lockop(self)      (&(self)->_a_lockop)
#define async_from_lockop(lop)     container_of(lop, struct async, _a_lockop)
#define async_as_postlockop(self)  (&(self)->_a_postlockop)
#define async_from_postlockop(lop) container_of(lop, struct async, _a_postlockop)


/* There  is 1 pre-defined async worker which  can't ever go away and is
 * used to implement the fallback mechanism for `mpart_start_asyncjob()'
 *
 * We set-up the static initialization of async workers such that this
 * one is linked in by default. */
INTDEF struct async mpart_ajob_fallback_worker;

/* API access to the set of all running async jobs. */
PUBLIC struct REF async_list /**/ async_all_list = { &mpart_ajob_fallback_worker };
PUBLIC size_t /*               */ async_all_size = 1;
PUBLIC struct atomic_lock /*   */ async_all_lock = ATOMIC_LOCK_INIT;
PUBLIC struct lockop_slist /*  */ async_all_lops = SLIST_HEAD_INITIALIZER(async_all_lops);



#ifndef __async_slist_defined
#define __async_slist_defined
SLIST_HEAD(async_slist, async);
#endif /* !__async_slist_defined */

/* [0..n][lock(ATOMIC)]   List   of  ready/new   async  jobs.
 * Jobs in this list always have one of the following states:
 *   - _ASYNC_ST_TRIGGERED
 *   - _ASYNC_ST_TRIGGERED_STOP
 */
PRIVATE struct REF async_slist async_ready = LIST_HEAD_INITIALIZER(async_ready);

/* Signal send whenever a new job is added to `async_ready' */
PRIVATE struct sig async_ready_sig = SIG_INIT;

/* Lock that must be held when removing threads from `async_ready' */
PRIVATE struct atomic_lock async_ready_poplock = ATOMIC_LOCK_INIT;

/* Try to pop a ready async job. */
PRIVATE WUNUSED REF struct async *FCALL
async_trypopready(void) THROWS(E_WOULDBLOCK) {
	REF struct async *result;
	/* Pop the first ready async job. */
	atomic_lock_acquire(&async_ready_poplock);
again_read_first:
	result = ATOMIC_READ(async_ready.slh_first);
	if (result) {
		if (!ATOMIC_CMPXCH_WEAK(async_ready.slh_first,
		                        result,
		                        result->a_ready.sle_next))
			goto again_read_first;
	}
	atomic_lock_release(&async_ready_poplock);
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_addready_postlop)(struct postlockop *__restrict self) {
	REF struct async *me = async_from_postlockop(self);
	sig_multicompletion_init(&me->a_comp);
	SLIST_ATOMIC_INSERT(&async_ready, me, a_ready);
	sig_send(&async_ready_sig);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_destroy_later)(struct postlockop *__restrict self) {
	struct async *me;
	me = async_from_postlockop(self);
	async_destroy(me);
}


PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(FCALL async_delall_lop)(struct lockop *__restrict self) {
	REF struct async *me;
	unsigned int st;
	me = async_from_lockop(self);
again:
	st = ATOMIC_READ(me->a_stat);
	if unlikely(st != _ASYNC_ST_DELALL) {
		struct postlockop *post;
		assert(st == _ASYNC_ST_DELALL_STRT);
		/* Re-add the async job to the list of ready jobs, so-as
		 * to comply with the user's wish to resume  operations. */
		if (!ATOMIC_CMPXCH_WEAK(me->a_stat,
		                        _ASYNC_ST_DELALL_STRT,
		                        _ASYNC_ST_TRIGGERED))
			goto again;
		post           = async_as_postlockop(me);
		post->plo_func = &async_addready_postlop;
		return post;
	}

	/* Actually remove the async job from the all-list.
	 * Note that in doing this we'll be holding 2 references to `me'! */
	if (!ATOMIC_CMPXCH_WEAK(me->a_stat,
	                        _ASYNC_ST_DELALL,
	                        _ASYNC_ST_INIT_STOP))
		goto again;
	async_all_remove(me); /* Actually remove from the list. */

	/* The reference from `async_all_list'. Note that even after this
	 * we're still holding another reference  to `me' that was  given
	 * to us by the caller, which we still have to drop. */
	decref_nokill(me);

	if (ATOMIC_DECFETCH(me->a_refcnt) == 0) {
		/* Special case: `me' was just destroyed!
		 * However, in the interest of efficiency, postpone the
		 * actual destruction until  the caller releases  their
		 * lock to `async_all_lock' */
		struct postlockop *post;
		post           = async_as_postlockop(me);
		post->plo_func = &async_destroy_later;
		return post;
	}

	return NULL;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_postcompletion)(struct sig_completion_context *__restrict UNUSED(context),
                                    void *buf) {
	REF struct async *me;
	unsigned int st;
	me = *(REF struct async **)buf;
again:
	st = ATOMIC_READ(me->a_stat);
	if unlikely(st != _ASYNC_ST_READY &&
	            st != _ASYNC_ST_READY_TMO) {
		/* Can happen if the job  was cancel'd in the mean  time,
		 * or if more than one of the job's connected signals was
		 * delivered before we could get here. */
		decref(me);
		return;
	}

	/* Mark the job as having been triggered. */
	if (!ATOMIC_CMPXCH_WEAK(me->a_stat, st, _ASYNC_ST_TRIGGERED))
		goto again;

	/* Add the job to the list of ready jobs. */
	SLIST_ATOMIC_INSERT(&async_ready, me, a_ready); /* Inherit reference */
	sig_send(&async_ready_sig);
}


/* Must be INTERN because used in the static init of `mpart_ajob_fallback_worker' */
INTERN NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL async_completion)(struct sig_completion *__restrict self,
                                struct sig_completion_context *__restrict context,
                                void *buf, size_t bufsize) {
	struct async *me;

	/*sig_multicompletion_trydisconnectall(self);*/ /* TODO: Optimization */
	me = container_of(sig_multicompletion_controller(self),
	                  struct async, a_comp);
	if (bufsize < sizeof(REF struct async *))
		return sizeof(REF struct async *);
	if unlikely(!tryincref(me))
		return 0; /* Shouldn't really happen, but (might?) due to race conditions? */

	/* Do all of the actual work in a post-completion callback. */
	*(REF struct async **)buf = me; /* Inherit reference */
	context->scc_post         = &async_postcompletion;
	return sizeof(REF struct async *);
}


/* Reconnect async job signals.
 * @return: * : The timeout of the job. */
PRIVATE NONNULL((1)) ktime_t FCALL
async_reconnect(struct async *__restrict self) {
	ktime_t result;
again:
	sig_multicompletion_disconnectall(&self->a_comp);
	assert(!task_wasconnected());
	assert(!sig_multicompletion_wasconnected(&self->a_comp));
	TRY {
		result = (*self->a_ops->ao_connect)(self);
		sig_multicompletion_connect_from_task(/* completion: */ &self->a_comp,
		                                      /* cb:         */ &async_completion,
		                                      /* for_poll:   */ true);
	} EXCEPT {
		sig_multicompletion_disconnectall(&self->a_comp);
		task_disconnectall();
		RETHROW();
	}
	if unlikely(task_receiveall() != NULL) {
		sig_multicompletion_disconnectall(&self->a_comp);
		goto again;
	}
	return result;
}


/* NOTE: This list usually contains async jobs with status `_ASYNC_ST_READY_TMO'.
 *       Jobs that have a different status should be ignored, and you may  assume
 *       that there are already pending lockops to remove them! */
PRIVATE struct REF async_list /**/ async_tmo_list; /* [0..n][lock(async_tmo_lock)] List of timeout jobs. */
PRIVATE struct atomic_lock /*   */ async_tmo_lock; /* Lock for the timeout-job list */
PRIVATE struct lockop_slist /*  */ async_tmo_lops; /* Pending lock operations for `async_tmo_lock' */
#define _async_tmo_reap()      _lockop_reap_atomic_lock(&async_tmo_lops, &async_tmo_lock)
#define async_tmo_reap()       lockop_reap_atomic_lock(&async_tmo_lops, &async_tmo_lock)
#define async_tmo_tryacquire() atomic_lock_tryacquire(&async_tmo_lock)
#define async_tmo_acquire()    atomic_lock_acquire(&async_tmo_lock)
#define async_tmo_acquire_nx() atomic_lock_acquire_nx(&async_tmo_lock)
#define async_tmo_release()    (atomic_lock_release(&async_tmo_lock), async_tmo_reap())
#define _async_tmo_release()   atomic_lock_release(&async_tmo_lock)
#define async_tmo_acquired()   atomic_lock_acquired(&async_tmo_lock)
#define async_tmo_available()  atomic_lock_available(&async_tmo_lock)
#define async_tmo_waitfor()    atomic_lock_waitfor(&async_tmo_lock)
#define async_tmo_waitfor_nx() atomic_lock_waitfor_nx(&async_tmo_lock)


/* Insert the given `job' into the async-timeout list, inheriting a reference */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_tmo_insert)(REF struct async *__restrict job, ktime_t timeout) {
	struct async **p_next, *next;
	for (p_next = LIST_PFIRST(&async_tmo_list); (next = *p_next) != NULL;
	     p_next = LIST_PNEXT(next, a_tmolnk)) {
		ktime_t next_timeout;

		COMPILER_READ_BARRIER();
		next_timeout = next->a_tmo;
		COMPILER_READ_BARRIER();

		/* Make sure that this is a valid entry, and that the
		 * timeout  value   we've   read   is   valid,   too. */
		if (ATOMIC_READ(next->a_stat) != _ASYNC_ST_READY_TMO)
			continue;

		if (timeout >= next_timeout)
			break; /* Insert before this one! */
	}

	/* Actually insert the new job into the list. */
	LIST_P_INSERT_BEFORE(p_next, job, a_tmolnk);
}



/* Find the given `thread' within the given async-thread-controller. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) struct async_thread_data *
NOTHROW(FCALL async_thread_controller_findthread)(struct async_thread_controller *__restrict self,
                                                  struct task *__restrict thread) {
	size_t i;
	BSEARCH (i, self->atc_threads, self->atc_count, ->atd_thread, thread) {
		return self->atc_threads[i];
	}
	return NULL;
}

/* Find the `thread' that is sleeping on `job'. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) struct async_thread_data *
NOTHROW(FCALL async_thread_controller_findsleepon)(struct async_thread_controller *__restrict self,
                                                   struct async *__restrict job) {
	size_t i;
	for (i = 0; i < self->atc_count; ++i) {
		if (ATOMIC_READ(self->atc_threads[i]->atd_sleepon) == job)
			return self->atc_threads[i];
	}
	return NULL;
}






/************************************************************************
 * ASYNC WORKER THREAD MAIN FUNCTION                                    *
 ************************************************************************
 * This function is designed to be called by an arbitrary # of threads,
 * and  will do all of the work of servicing async jobs as they appear.
 * When there's nothing to do, simply wait for more jobs to come in.
 *
 * In order to service async jobs faster, you may spawn threads to run
 * this  function in parallel,  and you may also  kill such threads by
 * sending them an RPC that will throw an E_EXIT_THREAD exception, but
 * be  careful not to kill the hard-coded `asyncwork' thread, which is
 * statically allocated and must not be killed.
 ************************************************************************/
INTERN ATTR_NORETURN void KCALL _asyncmain(void) {
	REF struct async *job;
	unsigned int st;
	/* Wait for & consume ready async jobs. */
again:
again_pop_job:
	job = async_trypopready();
	if (job == NULL) {
		/* Wait for jobs to become available (but respect `async_timeout') */
		task_connect(&async_ready_sig);
		job = async_trypopready();
		if unlikely(job != NULL) {
			task_disconnectall();
		} else {
			/* Try to get a job that is pending for timeout. */
			async_tmo_acquire();
			LIST_FOREACH (job, &async_tmo_list, a_tmolnk) {
				REF struct async_thread_controller *ctl;
				struct async_thread_data *ctx;
				struct sig *wait_status;
				ktime_t timeout;
				if unlikely(!ATOMIC_CMPXCH(job->a_stat,
				                           _ASYNC_ST_READY_TMO,
				                           _ASYNC_ST_SLEEPING))
					continue;

				/* Remove `job' from the list of timeout jobs, thus
				 * claiming it for ourselves. */
				LIST_REMOVE(job, a_tmolnk);
				async_tmo_release();
				COMPILER_READ_BARRIER();
				timeout = job->a_tmo;
				COMPILER_READ_BARRIER();

				/* Remember the fact that within our thread's async-controller data-area.
				 * NOTE: For the purpose of thread-safe interlocking, this _must_ happen
				 *       before we  re-validate  `job->a_stat == _ASYNC_ST_SLEEPING'  in
				 *       the next step! */
				ctl = arref_get(&async_threads);
				ctx = async_thread_controller_findthread(ctl, THIS_TASK);
				assertf(ctx, "If this fails, that would mean that we're not actually "
				             "one of the currently registered async worker threads!");
				incref(ctx);
				decref_unlikely(ctl);
				ATOMIC_WRITE(ctx->atd_sleepon, job);

				/* After having read the timeout, re-verify that the job hasn't
				 * been cancel'd in the mean time. Because if it has been, then
				 * there's a chance that the  timeout we've read is bogus.  And
				 * furthermore, we wouldn't even be supposed to wait for it! */
				if unlikely(ATOMIC_READ(job->a_stat) != _ASYNC_ST_SLEEPING) {
					ATOMIC_WRITE(ctx->atd_sleepon, NULL);
					decref_unlikely(ctx);
					goto again_rd_stat;
				}

				if unlikely(ktime() >= timeout) {
					unsigned int tmo_status;
					ATOMIC_WRITE(ctx->atd_sleepon, NULL);
					decref_unlikely(ctx);
					task_disconnectall(); /* &async_ready_sig */
do_handle_timeout:
					assert(!task_wasconnected());
					/* Timeout expired. */
					tmo_status = ASYNC_CANCEL;
					if (job->a_ops->ao_time != NULL) {
						TRY {
							tmo_status = (*job->a_ops->ao_time)(job);
						} EXCEPT {
							struct aio_handle *aio;
							aio = ATOMIC_XCH(job->a_aio, NULL);
							if (aio) {
								PREEMPTION_DISABLE();
								aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
								PREEMPTION_ENABLE();
							} else {
								except_printf("timeout async job %p", job);
							}
						}
					}
					if (tmo_status == ASYNC_CANCEL) {
						/* Cancel the async job.
						 *   #1: job->a_stat == _ASYNC_ST_SLEEPING
						 *       -> Set status to `_ASYNC_ST_TRIGGERED_STOP' and handle a normal trigger event
						 *   #2: job->a_stat == _ASYNC_ST_TRIGGERED_STOP
						 *       Cause: `async_cancel()'
						 *       -> Leave status as `_ASYNC_ST_TRIGGERED_STOP' and handle a normal trigger event
						 *   #3: job->a_stat == _ASYNC_ST_TRIGGERED
						 *       Cause: `async_cancel()+async_start()'
						 *       -> Leave status as `_ASYNC_ST_TRIGGERED' and handle a normal trigger event */
						ATOMIC_CMPXCH(job->a_stat, _ASYNC_ST_SLEEPING, _ASYNC_ST_TRIGGERED_STOP);
						goto again_rd_stat;
					}
					if (tmo_status == ASYNC_FINISHED) {
						/* Finish the async job. (but don't call the cancel callback)
						 * -> Complete an attached AIO handle with a successful status
						 *   #1: job->a_stat == _ASYNC_ST_SLEEPING
						 *   #2: job->a_stat == _ASYNC_ST_TRIGGERED_STOP
						 *   #3: job->a_stat == _ASYNC_ST_TRIGGERED
						 * If `job->a_stat == _ASYNC_ST_SLEEPING', continue with removing
						 * the job. - Otherwise, later code will jump to  `again_rd_stat'
						 * in order to handle a generic trigger event. */
						struct aio_handle *aio;
						aio = ATOMIC_XCH(job->a_aio, NULL);
						if (aio) {
							PREEMPTION_DISABLE();
							aio_handle_complete_nopr(aio, AIO_COMPLETION_SUCCESS);
							PREEMPTION_ENABLE();
						}
						st = _ASYNC_ST_SLEEPING;
						goto do_delete_job;
					}

					/* Keep the async job, and handle a regular trigger event.
					 * If the status  still indicates SLEEPING,  change it  to
					 * indicate a normal trigger event instead. */
					ATOMIC_CMPXCH(job->a_stat, _ASYNC_ST_SLEEPING, _ASYNC_ST_TRIGGERED);
					goto again_do_work;
				}

				/* Wait for something to happen... */
				TRY {
					wait_status = task_waitfor(timeout);
				} EXCEPT {
					ATOMIC_WRITE(ctx->atd_sleepon, NULL);
					decref_unlikely(job);
					decref_unlikely(ctx);
					RETHROW();
				}

				/* Write-back that we've stopped sleeping on `job' */
				ATOMIC_WRITE(ctx->atd_sleepon, NULL);
				decref_unlikely(ctx);

				/* Check if the timeout has expired. */
				if (wait_status == NULL && ktime() >= timeout)
					goto do_handle_timeout;

				/* Timeout didn't expire.
				 * -> Try to re-add the job to the list of sleeping
				 *    jobs, since we know that it's time has yet to
				 *    come! */
				async_tmo_acquire();
				if likely(ATOMIC_CMPXCH(job->a_stat,
				                        _ASYNC_ST_SLEEPING,
				                        _ASYNC_ST_READY_TMO)) {
					async_tmo_insert(job, timeout); /* Inherit reference */
					async_tmo_release();
					goto again_pop_job;
				}
				async_tmo_release();

				/* The job's status no longer indicates SLEEPING.
				 * This can happen if the job was canceled in the mean time. */
				goto again_rd_stat;
			} /* LIST_FOREACH (job, &async_tmo_list, a_tmolnk) */
			async_tmo_release();

			/* Wait without any timeouts. */
			task_waitfor();
			goto again_pop_job;
		} /* if (job == NULL) */
	}     /* if (job == NULL) */
again_rd_stat:
	st = ATOMIC_READ(job->a_stat);
	if unlikely(st != _ASYNC_ST_TRIGGERED) {
		struct aio_handle *aio;
		assert(st == _ASYNC_ST_TRIGGERED_STOP);
/*do_handle_triggered_stop:*/
		aio = ATOMIC_XCH(job->a_aio, NULL);
		if (aio) {
			PREEMPTION_DISABLE();
			aio_handle_complete_nopr(aio, AIO_COMPLETION_CANCEL);
			PREEMPTION_ENABLE();
		}
		if (job->a_ops->ao_cancel) {
			/* Invoke the cancel-callback. */
			TRY {
				(*job->a_ops->ao_cancel)(job);
			} EXCEPT {
				except_printf("canceling async job %p", job);
			}
		}

		/* Get rid of this job */
do_delete_job:
		if (async_all_tryacquire()) {
			if (!ATOMIC_CMPXCH_WEAK(job->a_stat, st,
			                        _ASYNC_ST_INIT_STOP)) {
				async_all_release();
				goto again_rd_stat;
			}
			async_all_remove(job);
			async_all_release();
			decref_nokill(job); /* The reference from `async_all_list' */
			decref(job);        /* The reference from `async_ready' (returned by `async_popready') */
		} else {
			struct lockop *lop;
			if (!ATOMIC_CMPXCH_WEAK(job->a_stat, st,
			                        _ASYNC_ST_DELALL))
				goto again_rd_stat;

			/* Schedule a pending lock-operation to remove
			 * `job'  from  the  list of  all  async jobs. */
			sig_multicompletion_disconnectall(&job->a_comp);
			sig_multicompletion_fini(&job->a_comp);
			lop          = async_as_lockop(job);
			lop->lo_func = &async_delall_lop; /* NOTE: `async_delall_lop' inherits a reference to `job'! */
			SLIST_ATOMIC_INSERT(&async_all_lops, lop, lo_link);
			_async_all_reap();
		}
		goto again;
	}

	/* Switch the job from TRIGGERED to READY */
again_handle_triggered:
	if (!ATOMIC_CMPXCH_WEAK(job->a_stat,
	                        _ASYNC_ST_TRIGGERED,
	                        _ASYNC_ST_READY))
		goto again_rd_stat;

	/* Check if this job is ready! */
again_do_work:
	TRY {
		unsigned int status;
		/* Do the work! */
		status = (*job->a_ops->ao_work)(job);
		assert(status == ASYNC_RESUME ||
		       status == ASYNC_FINISHED ||
		       status == ASYNC_CANCEL);
		if (status != ASYNC_RESUME) {
			struct aio_handle *aio;
			bool did_set_stop;

			/* Complete the async job. */
			aio = ATOMIC_XCH(job->a_aio, NULL);

			/* Set  async stop state.  -- If it was  already set, then that
			 * means that whoever set the state is doing the cleanup, which
			 * may or many not involve re-adding the job to the ready list. */
			did_set_stop = ATOMIC_CMPXCH(job->a_stat, _ASYNC_ST_READY,
			                             _ASYNC_ST_TRIGGERED_STOP);
			if (status == ASYNC_CANCEL) {
				if (aio) {
					PREEMPTION_DISABLE();
					aio_handle_complete_nopr(aio, AIO_COMPLETION_CANCEL);
					PREEMPTION_ENABLE();
				}
				if (!did_set_stop)
					goto decref_job_and_again;
				goto again_rd_stat;
			}

			/* Non-cancel completion. */
			if (aio) {
				PREEMPTION_DISABLE();
				aio_handle_complete_nopr(aio, AIO_COMPLETION_SUCCESS);
				PREEMPTION_ENABLE();
			}
			if (!did_set_stop)
				goto decref_job_and_again;
			st = ATOMIC_READ(job->a_stat);
			if unlikely(st == _ASYNC_ST_TRIGGERED)
				goto again_handle_triggered;
			assert(st == _ASYNC_ST_TRIGGERED_STOP);
			goto do_delete_job;
		}

again_rd_stat_before_reconnect:
		st = ATOMIC_READ(job->a_stat);
		if likely(st == _ASYNC_ST_READY) {
			ktime_t timeout;

			/* Re-connect completion handling for `job' */
			timeout = async_reconnect(job);

			/* Now that we're interlocked with the job's connect callback,
			 * check  once again  if there is  more work left  to be done. */
			if ((*job->a_ops->ao_test)(job))
				goto again_do_work;

			if (timeout != KTIME_INFINITE) {
				job->a_tmo = timeout;
				async_tmo_acquire();
				if (!ATOMIC_CMPXCH(job->a_stat, _ASYNC_ST_READY, _ASYNC_ST_READY_TMO)) {
					async_tmo_release();
					goto again_rd_stat_before_reconnect;
				}

				/* Insert `job' into the async-tmo-queue at the correct position. */
				async_tmo_insert(job, timeout); /* Inherit reference */
				async_tmo_release();

				/* Directly jump back to the start and don't decref() job,
				 * since  we've gifted out  reference to the timeout-list! */
				goto again;
			}
		} else {
			/* Don't  directly handle TRIGGERED_STOP. - `async_cancel()' will have
			 * added the job to the ready-list,  and if we immediately handle  the
			 * stop request, then the job will eventually be popped from the ready
			 * list (which may have already happened at this point).
			 *
			 * This would lead to corruption because being on the ready-list means that
			 * your state is either `_ASYNC_ST_TRIGGERED' or `_ASYNC_ST_TRIGGERED_STOP'
			 *
			 * The same also goes for `_ASYNC_ST_TRIGGERED'. In both states, we have
			 * to manually pop the job from the ready queue before we're allowed  to
			 * do anything! */
#if 0
			if (st == _ASYNC_ST_TRIGGERED_STOP) {
				/* async_cancel() was called in the mean time... */
				goto do_handle_triggered_stop;
			}
			if (st == _ASYNC_ST_TRIGGERED) {
				/* async_cancel()+async_start() was called in the mean time... */
				goto again_handle_triggered;
			}
#endif
		}
	} EXCEPT {
		/* Async error-completion.
		 * Note that when an AIO handle is attached to the job, then we
		 * don't  print an error message, but let _it_ handle the error
		 * for us! */
		struct aio_handle *aio;
		aio = ATOMIC_XCH(job->a_aio, NULL);
		if (aio) {
			PREEMPTION_DISABLE();
			aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
			PREEMPTION_ENABLE();
		} else {
			/* May get here in case of errors happening in an async  job
			 * that doesn't have an AIO handle attached, or that used to
			 * have one attached, but was  canceled before it could  use
			 * that handle. */
			except_printf("running async job %p", job);
		}
		ATOMIC_CMPXCH(job->a_stat, _ASYNC_ST_READY, _ASYNC_ST_TRIGGERED_STOP);
		goto again_rd_stat;
	}

	/* Drop the reference that we've gotten from the ready-list. */
decref_job_and_again:
	decref_unlikely(job);
	goto again;
}




struct async_aio_data {
	REF struct async *aad_job; /* [1..1] A reference to  the associated job. */
};
static_assert(AIO_HANDLE_DRIVER_POINTER_COUNT >= 1);

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL async_aio_fini)(struct aio_handle *__restrict self) {
	struct async_aio_data *data;
	data = (struct async_aio_data *)self->ah_data;
	decref_likely(data->aad_job);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL async_aio_cancel)(struct aio_handle *__restrict self) {
	struct async_aio_data *data;
	data = (struct async_aio_data *)self->ah_data;
	async_cancel(data->aad_job);
}

PRIVATE NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(KCALL async_aio_progress)(struct aio_handle *__restrict self,
                                  struct aio_handle_stat *__restrict stat) {
	struct async_aio_data *data;
	struct async *job;
	data = (struct async_aio_data *)self->ah_data;
	job  = data->aad_job;
	/* Check if the operation has completed. */
	if (ATOMIC_READ(job->a_aio) == NULL) {
		stat->hs_completed = 1;
		stat->hs_total     = 1;
		return AIO_PROGRESS_STATUS_COMPLETED;
	}
	if (!job->a_ops->ao_progress) {
		stat->hs_completed = 0;
		stat->hs_total     = 1;
		return AIO_PROGRESS_STATUS_INPROGRESS;
	}
	return (*job->a_ops->ao_progress)(job, stat);
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL async_aio_retsize)(struct aio_handle *__restrict self) {
	struct async_aio_data *data;
	struct async *job;
	size_t result;
	data   = (struct async_aio_data *)self->ah_data;
	job    = data->aad_job;
	result = (*job->a_ops->ao_retsize)(job);
	return result;
}

PRIVATE struct aio_handle_type const async_aio = {
	.ht_fini     = &async_aio_fini,
	.ht_cancel   = &async_aio_cancel,
	.ht_progress = &async_aio_progress,
	.ht_retsize  = &async_aio_retsize,
};

PRIVATE struct aio_handle_type const async_aio_noretsize = {
	.ht_fini     = &async_aio_fini,
	.ht_cancel   = &async_aio_cancel,
	.ht_progress = &async_aio_progress,
	.ht_retsize  = NULL,
};

/* Initialize   the  given  async  controller  and  attach  `aio'.
 * The  caller must follow this up with a call to `async_start()',
 * after  which  point  `aio' will  be  notified once  the  job is
 * completed (when restarted later, or canceled before that point,
 * the AIO  handle will  not be  notified). Additionally,  use  of
 * `async_cancel()' will  immediately  indicate  completion  (with
 * CANCEL  status),  and  `aio_handle_cancel()'  will  behave  the
 * same as `async_cancel()' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _async_init_aio)(struct async *__restrict self,
                               /*out*/ struct aio_handle *__restrict aio) {
	struct async_aio_data *aio_data;
	self->a_refcnt    = 2; /* +1: `self', +1: `aio_data->aad_job' */
	self->a_stat      = _ASYNC_ST_INIT;
	self->a_aio       = aio;
	aio_data          = (struct async_aio_data *)aio->ah_data;
	aio_data->aad_job = self;
	aio_handle_init(aio,
	                self->a_ops->ao_retsize
	                ? &async_aio
	                : &async_aio_noretsize);
}


/* Destroy a given async controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_destroy)(struct async *__restrict self) {
	assert(self->a_stat == _ASYNC_ST_INIT ||
	       self->a_stat == _ASYNC_ST_INIT_STOP);
	if (self->a_ops->ao_destroy) {
		(*self->a_ops->ao_destroy)(self);
	} else {
		kfree(self);
	}
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(FCALL async_addall_lop)(struct lockop *__restrict self) {
	struct postlockop *post;
	REF struct async *me;
	unsigned int st;
	me = async_from_lockop(self);
again:
	st = ATOMIC_READ(me->a_stat);
	assert(st == _ASYNC_ST_ADDALL ||
	       st == _ASYNC_ST_ADDALL_STOP);
	if unlikely(st != _ASYNC_ST_ADDALL) {
		if (!ATOMIC_CMPXCH_WEAK(me->a_stat, st, _ASYNC_ST_INIT_STOP))
			goto again;
		decref_nokill(me);
		decref(me);
		return NULL;
	}
	if (!ATOMIC_CMPXCH_WEAK(me->a_stat, st, _ASYNC_ST_TRIGGERED))
		goto again;
	async_all_insert(me);

	/* Use a post-lockop to add `self' to the ready list, as well
	 * as  to  initialize  `a_comp'  and  send  `async_ready_sig' */
	post           = async_as_postlockop(me);
	post->plo_func = &async_addready_postlop;
	return post;
}


#define _ASYNC_ST_STRTFOR(x) ((x) & ~1)
#define _ASYNC_ST_STOPFOR(x) ((x) | 1)


/* Start (or re-start) a given async job.
 * Note that when re-starting an async controller, previously attached
 * AIO  handles will always be detached (iow: any async controller can
 * only ever be attached once to only a single AIO handle) */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct async *
NOTHROW(FCALL async_start)(struct async *__restrict self) {
	unsigned int st;
again:
	st = ATOMIC_READ(self->a_stat);
	switch (__builtin_expect(st, _ASYNC_ST_INIT)) {

	case _ASYNC_ST_INIT:
	case _ASYNC_ST_INIT_STOP:
		sig_multicompletion_init(&self->a_comp);
		if (async_all_tryacquire()) {
			if (!ATOMIC_CMPXCH_WEAK(self->a_stat, st, _ASYNC_ST_TRIGGERED)) {
				async_all_release();
				goto again;
			}
			ATOMIC_ADD(self->a_refcnt, 2); /* +1: async_all_list, +1: async_ready */
			async_all_insert(self);
			async_all_release();

			/* wake-up one of the async worker-threads. */
			SLIST_ATOMIC_INSERT(&async_ready, self, a_ready);
			sig_send(&async_ready_sig);
		} else {
			struct lockop *lop;
			if (!ATOMIC_CMPXCH_WEAK(self->a_stat, st, _ASYNC_ST_ADDALL))
				goto again;

			/* Enqueue a pending lock-operation to add the async  job
			 * to the list of all jobs, as well as add it to the list
			 * of ready jobs once that's done. */
			ATOMIC_ADD(self->a_refcnt, 2); /* +1: async_all_list, +1: async_ready */
			lop          = async_as_lockop(self);
			lop->lo_func = &async_addall_lop;
			SLIST_ATOMIC_INSERT(&async_all_lops, lop, lo_link);
			_async_all_reap();
		}
		break;

#if (_ASYNC_ST_STRTFOR(_ASYNC_ST_ADDALL_STOP) == _ASYNC_ST_ADDALL &&       \
     _ASYNC_ST_STRTFOR(_ASYNC_ST_DELALL) == _ASYNC_ST_DELALL_STRT &&       \
     _ASYNC_ST_STRTFOR(_ASYNC_ST_TRIGGERED_STOP) == _ASYNC_ST_TRIGGERED && \
     _ASYNC_ST_STRTFOR(_ASYNC_ST_DELTMO) == _ASYNC_ST_DELTMO_STRT)
	case _ASYNC_ST_ADDALL_STOP:
	case _ASYNC_ST_DELALL:
	case _ASYNC_ST_TRIGGERED_STOP:
	case _ASYNC_ST_DELTMO:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat, st, _ASYNC_ST_STRTFOR(st)))
			goto again;
		break;
#else /* ... */
	case _ASYNC_ST_ADDALL_STOP:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_ADDALL_STOP,
		                        _ASYNC_ST_ADDALL))
			goto again;
		break;

	case _ASYNC_ST_DELALL:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_DELALL,
		                        _ASYNC_ST_DELALL_STRT))
			goto again;
		break;

	case _ASYNC_ST_TRIGGERED_STOP:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_TRIGGERED_STOP,
		                        _ASYNC_ST_TRIGGERED))
			goto again;
		break;

	case _ASYNC_ST_DELTMO:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_DELTMO,
		                        _ASYNC_ST_DELTMO_STRT))
			goto again;
		break;
#endif /* !... */

	default:
		break;
	}
	return self;
}


PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(FCALL async_deltmo_lop)(struct lockop *__restrict self) {
	REF struct async *me;
	unsigned int st;
	me = container_of(self, struct async, _a_tmolockop);

	/* Actually remove from the timeout list! */
	LIST_REMOVE(me, a_tmolnk); /* Inherit reference */
	decref_nokill(me); /* The caller already gave us a reference, drop the new one. */

again_rd_stat:
	st = ATOMIC_READ(me->a_stat);
	assert(st == _ASYNC_ST_DELTMO ||
	       st == _ASYNC_ST_DELTMO_STRT);
	if unlikely(st == _ASYNC_ST_DELTMO_STRT) {
		/* Mark the async job as triggered to reset its state. */
		if (!ATOMIC_CMPXCH_WEAK(me->a_stat,
		                        _ASYNC_ST_DELTMO_STRT,
		                        _ASYNC_ST_TRIGGERED))
			goto again_rd_stat;
	} else {
		/* Mark the async job as stop-triggered. */
		if (!ATOMIC_CMPXCH_WEAK(me->a_stat,
		                        _ASYNC_ST_DELTMO,
		                        _ASYNC_ST_TRIGGERED_STOP))
			goto again_rd_stat;
	}

	/* Use a post-lockop to add the job to the ready-list. */
	me->_a_tmopostlockop.plo_func = &async_addready_postlop;
	return &me->_a_tmopostlockop;
}



/* Stop (or schedule to stop) a given async job.
 * When an AIO handle is attached to `self', complete with `AIO_COMPLETION_CANCEL'
 * WARNING: AIO  cancellation  happens asynchronously,  meaning that  this function
 *          may return while  another thread  is still calling  `ao_work', or  some
 *          other function apart  of `self->a_ops'. The  only component with  which
 *          this function  is synchronous  is a  potentially attached  AIO  handle.
 *          If an AIO handle is attached, it's completion function is either  being
 *          called by another  CPU at this  very moment (though  this call may  not
 *          necessarily return before this function does), has already been called,
 *          or will  have  been  called with  `AIO_COMPLETION_CANCEL'  before  this
 *          function  returns!  (the case  of another  CPU  is synchronized  by the
 *          SMP-specific loop in `aio_handle_fini()') */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct async *
NOTHROW(FCALL async_cancel)(struct async *__restrict self) {
	unsigned int st;
	struct aio_handle *aio;

	/* Deal with AIO cancel-completion */
	aio = ATOMIC_XCH(self->a_aio, NULL);
	if (aio != NULL)
		aio_handle_complete(aio, AIO_COMPLETION_CANCEL);
again:
	st = ATOMIC_READ(self->a_stat);
	switch (__builtin_expect(st, _ASYNC_ST_READY)) {

	case _ASYNC_ST_READY:
		/* Special handling for when the job has a custom cancel callback.
		 * If it does, then we must force one of the async  worker-threads
		 * to invoke that callback for us!
		 * We can do this by transitioning the the job to `_ASYNC_ST_TRIGGERED_STOP',
		 * the  same  we also  would  if we  can't  acquire `async_all_tryacquire()'. */
		if (self->a_ops->ao_cancel != NULL)
			goto do_async_cancel;

		/* Try to remove the job from the all-jobs list ourselves. */
		if (async_all_tryacquire()) {
			if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
			                        _ASYNC_ST_READY,
			                        _ASYNC_ST_INIT_STOP)) {
				async_all_release();
				goto again;
			}
			async_all_remove(self); /* Remove from the all-list */
			async_all_release();

			/* Disconnect completion signals & finalize the controller. */
			sig_multicompletion_disconnectall(&self->a_comp);
			sig_multicompletion_fini(&self->a_comp);

			/* Drop the old reference from `async_all_list' */
			decref_nokill(self);
		} else {
do_async_cancel:
			if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
			                        _ASYNC_ST_READY,
			                        _ASYNC_ST_TRIGGERED_STOP))
				goto again;

			/* Add to the ready list and let one of the
			 * async worker-threads  deal with  this... */
			incref(self);
			SLIST_ATOMIC_INSERT(&async_ready, self, a_ready);
			sig_send(&async_ready_sig);
		}
		break;

	case _ASYNC_ST_READY_TMO:
		/* Remove the async job from the list of jobs w/ timeouts. */
		if (async_tmo_tryacquire()) {
			if (self->a_ops->ao_cancel == NULL) {
				if (async_all_tryacquire()) {
					/* Remove from the all- and tmo-list at the same time.
					 * This way, we don't need one of the async workers to do anything for us! */
					if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
					                        _ASYNC_ST_READY_TMO,
					                        _ASYNC_ST_INIT_STOP)) {
						async_all_release_f();
						_async_tmo_release();
						async_all_reap();
						async_tmo_reap();
						goto again;
					}
					async_all_remove(self); /* Remove from the all-list */
					async_all_release_f();
					LIST_REMOVE(self, a_tmolnk); /* Remove from the timeout list */
					_async_tmo_release();
					async_all_reap();
					async_tmo_reap();
					sig_multicompletion_disconnectall(&self->a_comp);
					sig_multicompletion_fini(&self->a_comp);
					decref_nokill(self); /* Drop the old reference from `async_all_list' */
					decref_nokill(self); /* Drop the old reference from `async_tmo_list' */
					break;
				}
			}
			if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
			                        _ASYNC_ST_READY_TMO,
			                        _ASYNC_ST_TRIGGERED_STOP)) {
				async_tmo_release();
				goto again;
			}
			LIST_REMOVE(self, a_tmolnk); /* Inherit reference */
			async_tmo_release();
			SLIST_ATOMIC_INSERT(&async_ready, self, a_ready); /* Inherit reference */
			sig_send(&async_ready_sig);
		} else {
			if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
			                        _ASYNC_ST_READY_TMO,
			                        _ASYNC_ST_DELTMO))
				goto again;

			/* Enqueue a lock-operation to remove `self' from the timeout list. */
			incref(self);
			self->_a_tmolockop.lo_func = &async_deltmo_lop;
			SLIST_ATOMIC_INSERT(&async_tmo_lops, &self->_a_tmolockop, lo_link);
			_async_tmo_reap();
		}
		break;

	case _ASYNC_ST_SLEEPING: {
		REF struct async_thread_controller *ctl;
		struct async_thread_data *ctx;
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_SLEEPING,
		                        _ASYNC_ST_TRIGGERED_STOP))
			goto again;

		/* Add the job to the ready-list. */
		incref(self);
		SLIST_ATOMIC_INSERT(&async_ready, self, a_ready);

		/* We  know that one of the async workers is currently sleeping
		 * in an attempt to wait for  the timeout of `self' to  expire.
		 * As such, we (try) to wake that specific async worker thread. */
		ctl = arref_get(&async_threads);
		ctx = async_thread_controller_findsleepon(ctl, self);
		if unlikely(!ctx)
			goto fallback_wait_all_threads;

		/* Send the async-ready signal (which  is what's used to  control
		 * when individual async-worker-threads are awake, with the usual
		 * system  state reflecting _all_ worker threads being connected,
		 * and waiting for this signal to be delivered)
		 *
		 * As such, make use of the special `sig_sendto()' function to
		 * send the signal to _only_ the thread that's sleeping on the
		 * caller-given async job! */
		if (!sig_sendto(&async_ready_sig, ctx->atd_thread))
			goto fallback_wait_all_threads;

		/* All right! We did what we came here to do, that is: send a
		 * signal to _only_ the worker thread that's responsible  for
		 * the */
		decref_unlikely(ctl);
		break;

		/* If something goes wrong, and we're unable to locate the
		 * specific async worker thread of `self', or were  unable
		 * to successfully  send it  the async-ready-signal,  then
		 * fall back to broadcasting all threads. */
fallback_wait_all_threads:
		decref_unlikely(ctl);
		sig_broadcast(&async_ready_sig);
	}	break;


#if (_ASYNC_ST_STOPFOR(_ASYNC_ST_INIT) == _ASYNC_ST_INIT_STOP &&           \
     _ASYNC_ST_STOPFOR(_ASYNC_ST_ADDALL) == _ASYNC_ST_ADDALL_STOP &&       \
     _ASYNC_ST_STOPFOR(_ASYNC_ST_DELALL_STRT) == _ASYNC_ST_DELALL &&       \
     _ASYNC_ST_STOPFOR(_ASYNC_ST_TRIGGERED) == _ASYNC_ST_TRIGGERED_STOP && \
     _ASYNC_ST_STOPFOR(_ASYNC_ST_DELTMO_STRT) == _ASYNC_ST_DELTMO)
	case _ASYNC_ST_INIT:
	case _ASYNC_ST_ADDALL:
	case _ASYNC_ST_DELALL_STRT:
	case _ASYNC_ST_TRIGGERED:
	case _ASYNC_ST_DELTMO_STRT:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat, st, _ASYNC_ST_STOPFOR(st)))
			goto again;
		break;
#else /* ... */
	case _ASYNC_ST_INIT:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_INIT,
		                        _ASYNC_ST_INIT_STOP))
			goto again;
		break;

	case _ASYNC_ST_ADDALL:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_ADDALL,
		                        _ASYNC_ST_ADDALL_STOP))
			goto again;
		break;

	case _ASYNC_ST_DELALL_STRT:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_DELALL_STRT,
		                        _ASYNC_ST_DELALL))
			goto again;
		break;

	case _ASYNC_ST_TRIGGERED:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_TRIGGERED,
		                        _ASYNC_ST_TRIGGERED_STOP))
			goto again;
		break;

	case _ASYNC_ST_DELTMO_STRT:
		if (!ATOMIC_CMPXCH_WEAK(self->a_stat,
		                        _ASYNC_ST_DELTMO_STRT,
		                        _ASYNC_ST_DELTMO))
			goto again;
		break;
#endif /* !... */

	default:
		break;
	}
	return self;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_ASYNC_C */
