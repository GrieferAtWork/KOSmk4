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
#ifndef GUARD_KERNEL_SRC_SCHED_ASYNC_C
#define GUARD_KERNEL_SRC_SCHED_ASYNC_C 1
#define __WANT_ASYNC__a_lockop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_ASYNC
#include <kernel/aio.h>
#include <kernel/malloc.h>
#include <sched/async-intern.h>
#include <sched/async.h>
#include <sched/lockop.h>
#include <sched/signal.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/bsearch.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

#define async_as_lockop(self)      (&(self)->_a_lockop)
#define async_from_lockop(lop)     container_of(lop, struct async, _a_lockop)
#define async_as_postlockop(self)  (&(self)->_a_postlockop)
#define async_from_postlockop(lop) container_of(lop, struct async, _a_postlockop)


/* API access to the set of all running async jobs. */
PUBLIC struct REF async_list /**/ async_all_list = LIST_HEAD_INITIALIZER(async_all_list);
PUBLIC size_t /*               */ async_all_size = 0;
PUBLIC struct atomic_lock /*   */ async_all_lock = ATOMIC_LOCK_INIT;
PUBLIC struct lockop_slist /*  */ async_all_lops = SLIST_HEAD_INITIALIZER(async_all_lops);



#ifndef __async_slist_defined
#define __async_slist_defined 1
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
PRIVATE WUNUSED REF struct async *FCALL async_trypopready(void) {
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
	LIST_REMOVE(me, a_all); /* Actually remove from the list. */
	--async_all_size;

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

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
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
#define async_tmo_release_f()  atomic_lock_release(&async_tmo_lock)
#define async_tmo_acquired()   atomic_lock_acquired(&async_tmo_lock)
#define async_tmo_available()  atomic_lock_available(&async_tmo_lock)


/* Insert the given `job' into the async-timeout list, inheriting a reference */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_tmo_insert)(REF struct async *__restrict job, ktime_t timeout) {
	struct async **p_next, *next;
	for (p_next = &async_tmo_list.lh_first; (next = *p_next) != NULL;
	     p_next = &next->a_tmolnk.le_next) {
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
	if ((job->a_tmolnk.le_next = next) != NULL)
		next->a_tmolnk.le_prev = &job->a_tmolnk.le_next;
	job->a_tmolnk.le_prev = p_next;
}



/* Find the given `thread' within the given async-thread-controller. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) struct async_thread_data *
NOTHROW(FCALL async_thread_controller_findthread)(struct async_thread_controller *__restrict self,
                                                  struct task *__restrict thread) {
	size_t i;
	BSEARCH(i, self->atc_threads, self->atc_count, ->atd_thread, thread) {
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
 * be careful not to kill the hard-coded `_asyncwork' thread, which is
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
do_handle_timeout:
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
								error_printf("timeout async job %p", job);
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
do_handle_triggered_stop:
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
				error_printf("canceling async job %p", job);
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
			LIST_REMOVE(job, a_all);
			--async_all_size;
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
			/* Complete the async job. */
			ATOMIC_CMPXCH(job->a_stat, _ASYNC_ST_READY, _ASYNC_ST_TRIGGERED_STOP);
			aio = ATOMIC_XCH(job->a_aio, NULL);
			if (status == ASYNC_CANCEL) {
				if (aio) {
					PREEMPTION_DISABLE();
					aio_handle_complete_nopr(aio, AIO_COMPLETION_CANCEL);
					PREEMPTION_ENABLE();
				}
				goto again_rd_stat;
			}
			/* Non-cancel completion. */
			if (aio) {
				PREEMPTION_DISABLE();
				aio_handle_complete_nopr(aio, AIO_COMPLETION_SUCCESS);
				PREEMPTION_ENABLE();
			}
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
			if (st == _ASYNC_ST_TRIGGERED_STOP)
				goto do_handle_triggered_stop; /* async_cancel() was called in the mean time... */
			if (st == _ASYNC_ST_TRIGGERED)
				goto again_handle_triggered; /* async_cancel()+async_start() was called in the mean time... */
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
			error_printf("running async job %p", job);
		}
		ATOMIC_CMPXCH(job->a_stat, _ASYNC_ST_READY, _ASYNC_ST_TRIGGERED_STOP);
		goto again_rd_stat;
	}

	/* Drop the reference that we've gotten from the ready-list. */
	decref_unlikely(job);
	goto again;
}




struct async_aio_data {
	REF struct async *aad_job; /* [1..1] A reference to  the associated job. */
};
STATIC_ASSERT(AIO_HANDLE_DRIVER_POINTER_COUNT >= 1);

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
 * `async_cancel()'  will  immediatly  indicate  completion  (with
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
	++async_all_size;
	LIST_INSERT_HEAD(&async_all_list, me, a_all);

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
			++async_all_size;
			LIST_INSERT_HEAD(&async_all_list, self, a_all);
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
			LIST_REMOVE(self, a_all); /* Remove from the all-list */
			--async_all_size;
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
						async_tmo_release_f();
						async_all_reap();
						async_tmo_reap();
						goto again;
					}
					LIST_REMOVE(self, a_all); /* Remove from the all-list */
					--async_all_size;
					async_all_release_f();
					LIST_REMOVE(self, a_tmolnk); /* Remove from the timeout list */
					async_tmo_release_f();
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

#else /* CONFIG_USE_NEW_ASYNC */

#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/async.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/aref.h>

#include <assert.h>
#include <inttypes.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_NO_SMP
#define IF_SMP(...) __VA_ARGS__
#else /* !CONFIG_NO_SMP */
#define IF_SMP(...) /* nothing */
#endif /* CONFIG_NO_SMP */

struct aworker {
	WEAK refcnt_t                 aw_refcnt; /* Reference counter */
	struct async_worker_callbacks aw_cb;     /* [const] Worker callbacks */
	WEAK void                    *aw_obj;    /* [0..1][lock(CLEAR_ONCE && SMP(aw_inuse))]
	                                          * Object pointer. When set to NULL, this worker
	                                          * may be removed */
	uintptr_half_t                aw_typ;    /* [const] Object type (one of `HANDLE_TYPE_*'). */
	uintptr_half_t               _aw_pad;    /* ... */
#ifndef CONFIG_NO_SMP
	uintptr_t                     aw_inuse;  /* # of CPUs using `aw_obj' right now. */
#endif /* !CONFIG_NO_SMP */
};

#define aworker_decref_obj(self, obj) \
	(*handle_type_db.h_decref[(self)->aw_typ])(obj);

DEFINE_REFCOUNT_FUNCTIONS(struct aworker, aw_refcnt, kfree)

#define aworker_eq(self, cb, obj, typ)           \
	((self)->aw_cb.awc_work == (cb)->awc_work && \
	 ATOMIC_READ((self)->aw_obj) == (obj) &&     \
	 (self)->aw_cb.awc_poll == (cb)->awc_poll && \
	 (self)->aw_cb.awc_test == (cb)->awc_test && \
	 (self)->aw_typ == (typ))

LOCAL NOBLOCK bool
NOTHROW(FCALL aworker_clearobj)(struct aworker *__restrict self) {
	void *old_value;
#ifdef CONFIG_NO_SMP
	pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
	old_value = ATOMIC_XCH(self->aw_obj, NULL);
#ifndef CONFIG_NO_SMP
	while (ATOMIC_READ(self->aw_inuse))
		task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
	PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
	return old_value != NULL;
}

LOCAL WUNUSED NONNULL((1)) /*nullable*/ REF void *
NOTHROW(FCALL aworker_getref)(struct aworker *__restrict self) {
	REF void *result;
	PREEMPTION_DISABLE();
	IF_SMP(ATOMIC_INC(self->aw_inuse));
	COMPILER_READ_BARRIER();
	result = self->aw_obj;
	COMPILER_READ_BARRIER();
	/* Try to acquire a reference. */
	if (likely(result) && unlikely(!(*handle_type_db.h_tryincref[self->aw_typ])(result)))
		result = NULL;
	IF_SMP(ATOMIC_DEC(self->aw_inuse));
	PREEMPTION_ENABLE();
	return result;
}

LOCAL NONNULL((1, 2)) bool
NOTHROW(FCALL aworker_calltest)(struct aworker *__restrict self,
                                void *__restrict obj) {
	bool result;
	TRY {
		result = (*self->aw_cb.awc_test)(obj);
	} EXCEPT {
		error_printf("aworker:test@%p(%p:%#x)",
		             self->aw_cb.awc_test, obj,
		             (unsigned int)self->aw_typ);
		result = false;
	}
	return result;
}

LOCAL NONNULL((1, 2)) bool
NOTHROW(FCALL aworker_callpoll)(struct aworker *__restrict self,
                                void *__restrict obj) {
	bool result;
	TRY {
		result = (*self->aw_cb.awc_poll)(obj, (void *)self);
	} EXCEPT {
		error_printf("aworker:poll@%p(%p:%#x)",
		             self->aw_cb.awc_poll, obj,
		             (unsigned int)self->aw_typ);
		result = false;
	}
	return result;
}

LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL aworker_callwork)(struct aworker *__restrict self,
                                void *__restrict obj) {
	TRY {
		(*self->aw_cb.awc_work)(obj);
	} EXCEPT {
		error_printf("aworker:poll@%p(%p:%#x)",
		             self->aw_cb.awc_work, obj,
		             (unsigned int)self->aw_typ);
	}
}



struct awork_vector {
	WEAK refcnt_t                                 av_refcnt; /* Reference counter. */
	size_t                                        av_testc;  /* # of worker threads with test-callbacks.
	                                                           * All such workers come before those without! */
	size_t                                        av_workc;  /* # of worker threads. */
	COMPILER_FLEXIBLE_ARRAY(REF struct aworker *, av_workv); /* [0..awc_workc] Vector of workers */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL awork_vector_destroy)(struct awork_vector *__restrict self) {
	size_t i;
	for (i = 0; i < self->av_workc; ++i)
		decref_unlikely(self->av_workv[i]);
	kfree(self);
}

DEFINE_REFCOUNT_FUNCTIONS(struct awork_vector, av_refcnt, awork_vector_destroy)

PRIVATE struct awork_vector empty_awork = {
	/* .aws_refcnt = */ 2, /* +1: empty_awork; +1: awork */
	/* .awc_testc  = */ 0, /* No workers defined by default... */
	/* .awc_workc  = */ 0  /* No workers defined by default... */
};

ARREF(awork_vector_arref, awork_vector);

/* Registered async work. */
PRIVATE struct awork_vector_arref awork = ARREF_INIT(&empty_awork);

/* Signal broadcast when `awork' has changed. */
PRIVATE struct sig awork_changed = SIG_INIT;

#define TRY_DELETE_ASYNC_WORKER_SUCCESS  0 /* Success */
#define TRY_DELETE_ASYNC_WORKER_BADALLOC 1 /* Failed to allocate a new set of workers */
#define TRY_DELETE_ASYNC_WORKER_CHANGED  2 /* `old_workers' differed from the active set of workers. */

/* Try to delete a worker from `old_workers' and assign atomically
 * update the global set of active async workers. */
PRIVATE NOBLOCK_IF(gfp_flags & GFP_ATOMIC) NONNULL((1)) unsigned int
NOTHROW(KCALL try_delete_async_worker)(struct awork_vector *__restrict old_workers,
                                       size_t worker_index, gfp_t gfp_flags) {
	REF struct awork_vector *new_workers;
	assert(worker_index < old_workers->av_workc);
	if (old_workers->av_workc == 1) {
		/* Simple case: Just assign the empty workers list. */
		new_workers = incref(&empty_awork);
	} else {
		size_t i;
		assert(old_workers->av_workc >= 2);
		new_workers = (REF struct awork_vector *)kmalloc_nx(offsetof(struct awork_vector, av_workv) +
		                                                    ((old_workers->av_workc - 1) *
		                                                     sizeof(REF struct aworker *)),
		                                                    gfp_flags);
		if unlikely(!new_workers)
			return TRY_DELETE_ASYNC_WORKER_BADALLOC;
		new_workers->av_refcnt = 1;
		new_workers->av_testc  = old_workers->av_testc;
		new_workers->av_workc  = old_workers->av_workc - 1;
		if (worker_index < new_workers->av_testc)
			--new_workers->av_testc; /* The to-be-removed worker had a test-function */
		memcpy(new_workers->av_workv,
		       old_workers->av_workv,
		       worker_index,
		       sizeof(REF struct aworker *));
		memcpy(new_workers->av_workv + worker_index,
		       old_workers->av_workv + worker_index + 1,
		       old_workers->av_workc - worker_index,
		       sizeof(REF struct aworker *));
		for (i = 0; i < new_workers->av_workc; ++i)
			incref(new_workers->av_workv[i]);
	}
	/* Try to exchange the global async workers vector. */
	if (arref_cmpxch_inherit_new(&awork, old_workers, new_workers))
		return TRY_DELETE_ASYNC_WORKER_SUCCESS; /* success! */
	/* The async workers vector was changed in the mean time. */
	decref_likely(new_workers);
	return TRY_DELETE_ASYNC_WORKER_CHANGED;
}


#ifndef __aworker_axref_defined
#define __aworker_axref_defined
AXREF(aworker_axref, aworker);
#endif /* !__aworker_axref_defined */

/* [lock(PRIVATE(_asyncwork))] The  timeout   argument
 * for the async worker main `task_waitfor()' function */
PRIVATE ktime_t asyncmain_timeout_p = KTIME_INFINITE;

/* [0..1] The worker who's timeout callback should
 * be invoked when `asyncmain_timeout_p'  expires. */
PRIVATE struct aworker_axref asyncmain_timeout_worker = AXREF_INIT(NULL);

/* [lock(PRIVATE(_asyncwork))][1..1]
 * [valid_if(asyncmain_timeout_worker != NULL)]
 * The timeout callback to-be invoked when the timeout expires. */
PRIVATE async_worker_timeout_t asyncmain_timeout_cb = NULL;


/* This  function may be called by `awc_poll()'-callbacks to
 * specify the realtime() timestamp when `awc_time()' should
 * be invoked. The given `cookie' must be the same  argument
 * prviously passed to `awc_poll()' */
PUBLIC NOBLOCK NONNULL((2, 3)) void
NOTHROW(FCALL async_worker_timeout)(ktime_t abs_timeout,
                                    void *__restrict cookie,
                                    async_worker_timeout_t on_timeout) {
	struct aworker *w;
	w = (struct aworker *)cookie;
	assertf(THIS_TASK == &_asyncwork, "This function may only be called by async-worker-poll-callbacks");
	assertf(on_timeout && ADDR_ISKERN((void *)on_timeout), "Bad on_timeout callback");
	assertf(w && ADDR_ISKERN(w) && !wasdestroyed(w), "Bad cookie");
	if (abs_timeout >= asyncmain_timeout_p)
		return; /* The previous timeout is already older! */

	/* Set the used timeout. */
	asyncmain_timeout_p  = abs_timeout;
	asyncmain_timeout_cb = on_timeout;
	/* Set the associated worker as the one that will receive the timeout. */
	axref_set(&asyncmain_timeout_worker, w);
}


/* @return: true:  Previously connected signals have been disconnected.
 * @return: false: Move onto the step of waiting for something to happen. */
PRIVATE bool NOTHROW(FCALL _asyncjob_main)(void);

INTERN ATTR_NORETURN void KCALL _asyncmain(void) {
	for (;;) {
		size_t i;
		REF struct awork_vector *workers;
again:
		assert(PREEMPTION_ENABLED());
		assert(!task_wasconnected());
		PREEMPTION_DISABLE();
		workers = arref_get_nopr(&awork);
		PREEMPTION_ENABLE();
		/* First pass: test() for work and service immediately if present. */
		for (i = 0; i < workers->av_testc; ++i) {
			struct aworker *w;
			REF void *obj;
			w = workers->av_workv[i];
			assert(w->aw_cb.awc_test);
			PREEMPTION_DISABLE();
			IF_SMP(ATOMIC_INC(w->aw_inuse));
			COMPILER_READ_BARRIER();
			obj = w->aw_obj;
			COMPILER_READ_BARRIER();
			if unlikely(!obj) {
				unsigned int error;
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				error = try_delete_async_worker(workers, i, GFP_NORMAL);
				if (error == TRY_DELETE_ASYNC_WORKER_SUCCESS ||
				    error == TRY_DELETE_ASYNC_WORKER_CHANGED) {
					decref_likely(workers);
					goto again;
				}
				continue;
			}
			/* Try to acquire a reference. */
			if unlikely(!(*handle_type_db.h_tryincref[w->aw_typ])(obj)) {
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				continue; /* Skip dead objects. */
			}
			IF_SMP(ATOMIC_DEC(w->aw_inuse));
			PREEMPTION_ENABLE();
			assert(!task_wasconnected());
			if (aworker_calltest(w, obj)) {
				assert(!task_wasconnected());
				/* Service this worker. */
				aworker_callwork(w, obj);
				assert(!task_wasconnected());
				/* TODO: Do automatic re-ordering of async workers based on how often
				 *       they are being triggered. (workers that have work more often
				 *       should come before those that have less often) */
			}
			aworker_decref_obj(w, obj);
		}
		/* Second pass: poll() for work and service if available. */
		for (i = 0; i < workers->av_workc; ++i) {
			struct aworker *w;
			REF void *obj;
			w = workers->av_workv[i];
			PREEMPTION_DISABLE();
			IF_SMP(ATOMIC_INC(w->aw_inuse));
			COMPILER_READ_BARRIER();
			obj = w->aw_obj;
			COMPILER_READ_BARRIER();
			if unlikely(!obj) {
				unsigned int error;
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				error = try_delete_async_worker(workers, i, GFP_NORMAL);
				if (error == TRY_DELETE_ASYNC_WORKER_SUCCESS ||
				    error == TRY_DELETE_ASYNC_WORKER_CHANGED) {
					decref_likely(workers);
					goto again;
				}
				continue;
			}
			/* Try to acquire a reference. */
			if unlikely(!(*handle_type_db.h_tryincref[w->aw_typ])(obj)) {
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				continue; /* Skip dead objects. */
			}
			IF_SMP(ATOMIC_DEC(w->aw_inuse));
			PREEMPTION_ENABLE();
			if (aworker_callpoll(w, obj)) {
				/* Service this worker. */
				task_disconnectall();
				aworker_callwork(w, obj);
				aworker_decref_obj(w, obj);
				decref_unlikely(workers);
				goto again;
			}
			aworker_decref_obj(w, obj);
		}
		decref_unlikely(workers);
		/* Service async jobs. */
		if (_asyncjob_main()) {
			task_disconnectall();
			goto again;
		}
		{
			struct sig *received_signal;
			/* Also wait for async workers to have changed. */
			TRY {
				task_connect_for_poll(&awork_changed);
				received_signal = task_waitfor(asyncmain_timeout_p);
			} EXCEPT {
				task_disconnectall();
				error_printf("_asyncmain:task_waitfor()");
				goto again;
			}
			if (!received_signal) {
				REF struct aworker *receiver;
				/* A timeout expired. (invoke the associated worker's time-callback) */
				asyncmain_timeout_p = KTIME_INFINITE;
				receiver = axref_steal(&asyncmain_timeout_worker);
				if likely(receiver) {
					REF void *obj;
					obj = aworker_getref(receiver);
					if likely(obj) {
						TRY {
							(*asyncmain_timeout_cb)(obj);
						} EXCEPT {
							error_printf("aworker:time@%p(%p:%#x)",
							             asyncmain_timeout_cb, obj,
							             (unsigned int)receiver->aw_typ);
						}
						aworker_decref_obj(receiver, obj);
					}
					decref_unlikely(receiver);
				}
			} else if (received_signal == &awork_changed) {
				/* If workers have changed, clear any defined timeout. */
				asyncmain_timeout_p = KTIME_INFINITE;
				axref_clear(&asyncmain_timeout_worker);
			}
		}
	}
}


/* Register an async worker callback.
 * NOTE: All callbacks should be non-blocking  in that they mustn't wait  for
 *       work to become available themself (that's what `poll()' is for, such
 *       that a single thread can wait for async work to become available for
 *       _all_ async workers)
 * @param: cb:         Callbacks for the async worker being registered.
 *                     NOTE: The backing storage of the `cb' container itself
 *                           doesn't need to be persistent! It only needs  to
 *                           remain valid until this function returns!
 * @param: ob_pointer: A pointer  to a  handle data  object. The  destructor of  this
 *                     object is responsible for invoking `unregister_async_worker()'
 *                     Callbacks  will  no  longer   be  invoked  if  this   object's
 *                     reference   counter  has  reached   0,  however  the  object's
 *                     destructor  must   still  unregister   the  callbacks   before
 *                     the memory  used to  back its  reference counter  is  free()d!
 * @param: ob_type:    The object type for `ob_pointer' (one of `HANDLE_TYPE_*')
 * @return: true:      Successfully registered a new async worker.
 * @return: false:     An async worker for the given object/callback combination
 *                     was already registered. */
PUBLIC NONNULL((1, 2)) bool KCALL
register_async_worker(struct async_worker_callbacks const *__restrict cb,
                      void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	REF struct aworker *new_worker;
	REF struct awork_vector *old_workers;
	REF struct awork_vector *new_workers;
	size_t i;
	assert(cb);
	assert(cb->awc_poll);
	assert(cb->awc_work);
	assert(ob_pointer);
	assert(ob_type < HANDLE_TYPE_COUNT);
again:
	old_workers = arref_get(&awork);
	/* Check if this worker has already been defined. */
	{
		size_t c;
		i = 0;
		c = old_workers->av_testc;
		if (!cb->awc_test) {
			i = c;
			c = old_workers->av_workc;
		}
		for (; i < c; ++i) {
			if (aworker_eq(old_workers->av_workv[i],
			               cb, ob_pointer, ob_type))
				return false; /* Already defined. */
		}
	}
	TRY {
		/* Allocate enough space for +1 additional worker. */
		new_workers = (REF struct awork_vector *)kmalloc(offsetof(struct awork_vector, av_workv) +
		                                                 (old_workers->av_workc + 1) *
		                                                 sizeof(struct aworker),
		                                                 GFP_NORMAL);
		TRY {
			new_worker = (REF struct aworker *)kmalloc(sizeof(struct aworker), GFP_NORMAL);
		} EXCEPT {
			kfree(new_workers);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(old_workers);
		RETHROW();
	}

	/* Initialize the new worker */
	new_worker->aw_refcnt = 1;
	memcpy(&new_worker->aw_cb, cb, sizeof(*cb));
	new_worker->aw_obj = ob_pointer;
	new_worker->aw_typ = ob_type;
	IF_SMP(new_worker->aw_inuse = 0);

	/* Fill in the new workers vector. */
	new_workers->av_refcnt = 1;
	new_workers->av_testc  = old_workers->av_testc;
	new_workers->av_workc  = old_workers->av_workc + 1;
	if (cb->awc_test) {
		/* Insert `new_worker' at the front */
		++new_workers->av_testc;
		memcpy(new_workers->av_workv + 1,
		       old_workers->av_workv,
		       old_workers->av_workc,
		       sizeof(REF struct aworker *));
		new_workers->av_workv[0] = new_worker;
	} else {
		/* Insert `new_worker' after test-enabled workers */
		memcpy(new_workers->av_workv,
		       old_workers->av_workv,
		       old_workers->av_testc,
		       sizeof(REF struct aworker *));
		new_workers->av_workv[old_workers->av_testc] = new_worker; /* Inherit reference. */
		memcpy(new_workers->av_workv + old_workers->av_testc + 1,
		       old_workers->av_workv + old_workers->av_testc,
		       old_workers->av_workc - old_workers->av_testc,
		       sizeof(REF struct aworker *));
	}
	/* Acquire references to all of the old workers. */
	for (i = 0; i < old_workers->av_workc; ++i)
		incref(old_workers->av_workv[i]);

	/* Try to install the new async workers vector. */
	if (arref_cmpxch_inherit_new(&awork, old_workers, new_workers)) {
		decref_likely(old_workers);
		/* Indicate that workers have changed. */
		sig_broadcast(&awork_changed);
		return true;
	}
	/* The old set of workers has changed -> try again! */
	decref_likely(new_workers);
	decref_likely(old_workers);
	goto again;
}

/* Delete a previously defined async worker, using the same arguments as those
 * previously  passed  to `register_async_worker()'.  This function  should be
 * called from the destructor of `ob_pointer'
 * @param: cb:     Callbacks for the async worker being unregistered.
 *                 NOTE: The backing storage of the `cb' container itself
 *                       doesn't need to be persistent! It only needs  to
 *                       remain valid until this function returns!
 * @return: true:  Successfully deleted an async worker for the
 *                 given      object/callback      combination.
 * @return: false: No async worker for the given object/callback
 *                 combination had been registered. */
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL unregister_async_worker)(struct async_worker_callbacks const *__restrict cb,
                                       void *__restrict ob_pointer, uintptr_half_t ob_type) {
	REF struct awork_vector *workers;
	size_t i, count;
	assert(cb);
	assert(cb->awc_poll);
	assert(cb->awc_work);
	assert(ob_pointer);
	assert(ob_type < HANDLE_TYPE_COUNT);
	workers = arref_get(&awork);
	/* Figure out which parts of the worker-vector we need to search. */
	i     = 0;
	count = workers->av_testc;
	if (!cb->awc_test) {
		i     = count;
		count = workers->av_workc;
	}
	for (; i < count; ++i) {
		struct aworker *w;
		w = workers->av_workv[i];
		/* Check if this is the worker we're looking for. */
		if (aworker_eq(w, cb, ob_pointer, ob_type)) {
			bool result;
			/* Try to clear the worker's pointed-to object. */
			result = aworker_clearobj(w);

			/* If this worker is currently set as the timeout
			 * receiver, then remove  it from that  position. */
			axref_cmpxch_inherit_new(&asyncmain_timeout_worker, w, NULL);

			/* Always try to remove the worker. */
			try_delete_async_worker(workers, i, GFP_ATOMIC);
			decref_likely(workers);

			/* Indicate that workers have changed. */
			sig_broadcast(&awork_changed);
			return result;
		}
	}
	/* The worker wasn't found (or it was deleted during a prior pass) */
	decref_unlikely(workers);
	return false;
}















/************************************************************************/
/* ASYNC_JOB API                                                        */
/************************************************************************/

/* Special values for `async_job::aj_aio' */
#define ASYNC_JOB_AIO_NONPRESENT ((struct aio_handle *)0)  /* No AIO attached to this job, or AIO has already been triggered */
#define ASYNC_JOB_AIO_CANCELED   ((struct aio_handle *)-1) /* The async job has been canceled. */
#if 1
#define ASYNC_JOB_AIO_ISSPEC(x)    ((x) == ASYNC_JOB_AIO_CANCELED)
#else
#define ASYNC_JOB_AIO_ISSPEC(x)    ((uintptr_t)(x) >= (uintptr_t)-1)
#endif
#define ASYNC_JOB_AIO_ISPRESENT(x) (((uintptr_t)(x)-1) < (uintptr_t)-2)

struct async_job {
	REF struct async_job             *aj_next;   /* [0..1][lock(PRIVATE(ASYNC_WORKER))] Next async job. */
	struct async_job_callbacks const *aj_ops;    /* [1..1][const] Async job callbacks.
	                                              * NOTE: This field also holds a reference to `aj_ops->jc_driver' */
	WEAK struct aio_handle           *aj_aio;    /* [0..1][lock(CLEAR_ONCE)] Attached AIO and job cancellation indicator. */
	WEAK refcnt_t                     aj_refcnt; /* Reference counter.
	                                              * WARNING: This function _must_ always be located at the end of this structure!
	                                              *          This placement  is  part  of  the  ABI  (s.a.  `async_job_refcnt()') */
};

/* [0..1][lock(INSERT(ATOMIC), REMOVE(PRIVATE(ASYNC_WORKER)))]
 * Chain of active async-jobs. */
PRIVATE ATTR_READMOSTLY REF struct async_job *WEAK async_jobs = NULL;

/* [?..1] The async job currently configured to receive timeouts. */
PRIVATE struct async_job *async_job_current_timeout = NULL;

PRIVATE NONNULL((1)) void FCALL
asyncjob_timeout_worker_timeout(void *__restrict UNUSED(self)) {
	unsigned int status;
	assert(async_job_current_timeout);
	/* Check for `ASYNC_JOB_AIO_CANCELED' and call jc_cancel that's what happened. */
	if (ATOMIC_READ(async_job_current_timeout->aj_aio) == ASYNC_JOB_AIO_CANCELED) {
		if (async_job_current_timeout->aj_ops->jc_cancel) {
			TRY {
				(*async_job_current_timeout->aj_ops->jc_cancel)(async_job_current_timeout + 1);
			} EXCEPT {
				error_printf("ajob:cancel@%p(%p)",
				             async_job_current_timeout->aj_ops->jc_cancel,
				             async_job_current_timeout + 1);
			}
		}
		goto do_delete_job;
	}
	TRY {
		status = (*async_job_current_timeout->aj_ops->jc_time)(async_job_current_timeout + 1);
	} EXCEPT {
		struct aio_handle *aio;
		/* Signal AIO completion with error. */
		PREEMPTION_DISABLE();
		aio = ATOMIC_XCH(async_job_current_timeout->aj_aio,
		                 ASYNC_JOB_AIO_NONPRESENT);
		if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
			aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
			PREEMPTION_ENABLE();
		} else {
			PREEMPTION_ENABLE();
			/* Log an exception that's going to be discarded. */
			error_printf("ajob:time@%p(%p)",
			             async_job_current_timeout->aj_ops->jc_time,
			             async_job_current_timeout + 1);
		}
		goto do_delete_job;
	}
	if (status == ASYNC_JOB_WORK_COMPLETE) {
		struct async_job **pjob, *job;
do_delete_job:
		/* Delete this job. */
		pjob = &async_jobs;
		job  = ATOMIC_READ(async_jobs);
		for (;;) {
			assert(job);
			if (job == async_job_current_timeout)
				break;
			pjob = &job->aj_next;
			job  = *pjob;
		}
		if unlikely(!ATOMIC_CMPXCH(*pjob, job, job->aj_next)) {
			/* This can  happen  when  `pjob == &async_jobs',
			 * and new jobs have been added in the mean time. */
			struct async_job *prev;
			assert(pjob == &async_jobs);
			prev = ATOMIC_READ(async_jobs);
			for (;;) {
				assert(prev);
				if (prev->aj_next == job)
					break;
				prev = prev->aj_next;
			}
			ATOMIC_WRITE(prev->aj_next, job->aj_next);
		}
		/* Drop our reference to the job, which will likely destroy it. */
		decref_likely(job + 1);
	}
}


PRIVATE NONNULL((1, 2)) bool FCALL
asyncjob_timeout_worker_poll(void *__restrict UNUSED(self),
                             void *__restrict UNUSED(cookie)) {
	/* Should never be called */
	return false;
}

PRIVATE NONNULL((1)) void FCALL
asyncjob_timeout_worker_work(void *__restrict UNUSED(self)) {
	/* Should never be called */
}

/* A stub async-worker that's used for async-job timeouts */
PRIVATE struct aworker asyncjob_timeout_worker = {
	/* .aw_refcnt = */ 1, /* +1: asyncjob_timeout_worker */
	/* .aw_cb     = */ {
		/* .awc_poll = */ &asyncjob_timeout_worker_poll,
		/* .awc_work = */ &asyncjob_timeout_worker_work,
		/* .awc_test = */ NULL
	},
	/* .aw_obj   = */ &drv_self,
	/* .aw_typ   = */ HANDLE_TYPE_DRIVER,
	/* ._aw_pad  = */ 0
#ifndef CONFIG_NO_SMP
	,
	/* .aw_inuse = */ 0
#endif /* !CONFIG_NO_SMP */
};


/* @return: true:  Previously connected signals have been disconnected.
 * @return: false: Move onto the step of waiting for something to happen. */
PRIVATE bool NOTHROW(FCALL _asyncjob_main)(void) {
	struct async_job **pjob, *job;
	bool result = false;
	pjob = &async_jobs;
	job  = ATOMIC_READ(async_jobs);
handle_job:
	while (job) {
		struct aio_handle *state;
		state = ATOMIC_READ(job->aj_aio);
		if unlikely(ASYNC_JOB_AIO_ISSPEC(state)) {
			/* Special state handling. */
			if (state == ASYNC_JOB_AIO_CANCELED) {
				/* Invoke the cancellation callback. */
				if (job->aj_ops->jc_cancel) {
					result = true;
					task_disconnectall();
					TRY {
						(*job->aj_ops->jc_cancel)(job + 1);
					} EXCEPT {
						error_printf("ajob:cancel@%p(%p)",
						             job->aj_ops->jc_cancel,
						             job + 1);
					}
				}
				goto do_delete_job;
			}
		} else {
			/* Normal operations: poll()+work() if available. */
			unsigned int pollcode;
			ktime_t asyncjob_main_timeout;
			TRY {
				pollcode = (*job->aj_ops->jc_poll)(job + 1, &asyncjob_main_timeout);
			} EXCEPT {
				struct aio_handle *aio;
				/* Signal AIO completion with error. */
				result = true;
				task_disconnectall();
				PREEMPTION_DISABLE();
				aio = ATOMIC_XCH(job->aj_aio, ASYNC_JOB_AIO_NONPRESENT);
				if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
					aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
					PREEMPTION_ENABLE();
				} else {
					PREEMPTION_ENABLE();
					/* Log an exception that's going to be discarded. */
					error_printf("ajob:poll@%p(%p)",
					             job->aj_ops->jc_poll,
					             job + 1);
				}
				goto do_delete_job;
			}
			switch (pollcode) {

			case ASYNC_JOB_POLL_AVAILABLE: {
				unsigned int status;
				result = true;
				task_disconnectall();
				TRY {
					status = (*job->aj_ops->jc_work)(job + 1);
				} EXCEPT {
					struct aio_handle *aio;
					/* Signal AIO completion with error. */
					PREEMPTION_DISABLE();
					aio = ATOMIC_XCH(job->aj_aio, ASYNC_JOB_AIO_NONPRESENT);
					if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
						aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
						PREEMPTION_ENABLE();
					} else {
						PREEMPTION_ENABLE();
						/* Log an exception that's going to be discarded. */
						error_printf("ajob:work@%p(%p)",
						             job->aj_ops->jc_work,
						             job + 1);
					}
					goto do_delete_job;
				}
				if (status == ASYNC_JOB_WORK_COMPLETE) {
					struct aio_handle *aio;
					struct async_job *next;
					/* Signal successful AIO completion. */
do_delete_job_success:
					PREEMPTION_DISABLE();
					aio = ATOMIC_XCH(job->aj_aio, ASYNC_JOB_AIO_NONPRESENT);
					if (ASYNC_JOB_AIO_ISPRESENT(aio))
						aio_handle_complete_nopr(aio, AIO_COMPLETION_SUCCESS);
					PREEMPTION_ENABLE();
do_delete_job:
					/* Remove this job. */
					next = job->aj_next;
					COMPILER_READ_BARRIER();
					if unlikely(!ATOMIC_CMPXCH(*pjob, job, next)) {
						/* This can  happen  when  `pjob == &async_jobs',
						 * and new jobs have been added in the mean time. */
						struct async_job *prev;
						assert(pjob == &async_jobs);
						prev = ATOMIC_READ(async_jobs);
						for (;;) {
							assert(prev);
							if (prev->aj_next == job)
								break;
							prev = prev->aj_next;
						}
						ATOMIC_WRITE(prev->aj_next, next);
					}
					/* Drop our reference to the job, which will likely destroy it. */
					decref_likely(job + 1);
					job = next;
					goto handle_job;
				}
			}	break;

			case ASYNC_JOB_POLL_WAITFOR: {
				assertf(job->aj_ops->jc_time,
				        "poll returned `ASYNC_JOB_POLL_WAITFOR', but "
				        "the job does not define a timeout callback!");
				/* Use the async-worker timeout mechanism to set-up
				 * a  custom callback for when the timeout expires. */
				if (asyncjob_main_timeout >= asyncmain_timeout_p)
					break;
				/* Set the used timeout and callback routing. */
				asyncmain_timeout_p  = asyncjob_main_timeout;
				asyncmain_timeout_cb = &asyncjob_timeout_worker_timeout;
				/* NOTE: Because only  the async  worker (i.e.  us) is  allowed  to
				 *       remove async jobs, we don't even have to store a reference
				 *       to the job  within `async_job_current_timeout', since  the
				 *       job  will  always  be kept  alive  by its  entry  with the
				 *       `async_jobs' chain. */
				async_job_current_timeout = job;
				/* Set the associated worker as the one that will receive the timeout. */
				axref_set(&asyncmain_timeout_worker, &asyncjob_timeout_worker);
			}	break;

			case ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT:
				break;

			case ASYNC_JOB_POLL_DELETE:
				goto do_delete_job_success;

			default:
				__builtin_unreachable();
			}

		}
		pjob = &job->aj_next;
		job = *pjob;
	}
	return result;
}


/* Destroy an async-job that has previously been started (i.e. `async_job_start(self)' was called). */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_destroy)(async_job_t self) {
	struct async_job *me;
	me = self - 1;
	if (me->aj_ops->jc_fini)
		(*me->aj_ops->jc_fini)(self);
	decref_unlikely(me->aj_ops->jc_driver);
	kfree(me);
}


/* Allocate and  return a  new async-job  with the  given  callbacks.
 * Note that this  job hasn't  been started yet,  which is  something
 * that will only be done once the caller invokes `async_job_start()'
 * If the job should be free()'d before that point, `async_job_free()' should be used.
 * Afterwards, the  job should  be considered  as reference-counted,  with the  caller
 * of `async_job_start()' being responsible to inherit a reference to the job.
 * NOTE: The  returned pointer  itself points  at a  user-defined structure of
 *       `cb->jc_jobsize' bytes aligned on some `cb->jc_jobalign'-byte border.
 * >> struct my_job_desc *desc;
 * >> async_job_t job;
 * >> job  = async_job_alloc(&my_job);
 * >> desc = (struct my_job_desc *)job;
 * >> // Initialize the job descriptor.
 * >> desc->...;
 * >> // Start the job and inherit a reference to `job'
 * >> async_job_start(job);
 * >> // Do something else...
 * >> ...
 * >> if (should_cancel) {
 * >>     async_job_cancel(job);
 * >>     decref(job);
 * >> } else {
 * >>     decref(job);
 * >> }
 * WARNING: Unlike with async workers, the backing memory for the given `cb' must
 *          have static storage duration backed by a reference to `cb->jc_driver' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) /*inherit*/ async_job_t FCALL
async_job_alloc(struct async_job_callbacks const *__restrict cb) {
	struct async_job *result;
	assert(cb);
	assert(cb->jc_driver);
	assert(cb->jc_poll);
	assert(cb->jc_work);
	assertf((cb->jc_jobalign & (cb->jc_jobalign - 1)) == 0,
	        "Not a pointer-of-2: %#" PRIxSIZ,
	        cb->jc_jobalign);
	result = (struct async_job *)kmemalign_offset(MAX(alignof(struct async_job), cb->jc_jobalign),
	                                              sizeof(struct async_job),
	                                              sizeof(struct async_job) + cb->jc_jobsize,
	                                              GFP_NORMAL);
	result->aj_refcnt = 2;
	result->aj_ops    = cb;
	result->aj_aio    = ASYNC_JOB_AIO_NONPRESENT;
	incref(cb->jc_driver);
#ifndef NDEBUG
	result->aj_next = (REF struct async_job *)0x1234;
#endif /* !NDEBUG */
	return result + 1;
}

/* Free a previously allocated, but not-yet started job */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_free)(async_job_t self) {
	struct async_job *me;
	me = self - 1;
	assert(me->aj_refcnt == 2);
	assert(me->aj_aio == ASYNC_JOB_AIO_NONPRESENT);
	kfree(me);
}


struct async_job_aio_data {
	REF async_job_t ajad_job; /* [1..1] A reference to  the associated  job.
	                           * NOTE: This points to the user-data portion! */
};
STATIC_ASSERT(sizeof(struct async_job_aio_data) <=
              AIO_HANDLE_DRIVER_POINTER_COUNT * sizeof(void *));

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL async_job_aio_fini)(struct aio_handle *__restrict self) {
	struct async_job_aio_data *data;
	data = (struct async_job_aio_data *)self->ah_data;
	decref(data->ajad_job);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL async_job_aio_cancel)(struct aio_handle *__restrict self) {
	struct async_job_aio_data *data;
	data = (struct async_job_aio_data *)self->ah_data;
	async_job_cancel(data->ajad_job);
}

PRIVATE NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(KCALL async_job_aio_progress)(struct aio_handle *__restrict self,
                                      struct aio_handle_stat *__restrict stat) {
	struct async_job_aio_data *data;
	struct aio_handle *aio_status;
	struct async_job *job;
	data = (struct async_job_aio_data *)self->ah_data;
	job  = data->ajad_job - 1;
	aio_status = ATOMIC_READ(job->aj_aio);
	/* Check if the operation has completed. */
	if (!ASYNC_JOB_AIO_ISPRESENT(aio_status)) {
		stat->hs_completed = 1;
		stat->hs_total     = 1;
		return AIO_PROGRESS_STATUS_COMPLETED;
	}
	if (!job->aj_ops->jc_progress) {
		stat->hs_completed = 0;
		stat->hs_total     = 1;
		return AIO_PROGRESS_STATUS_INPROGRESS;
	}
	return (*job->aj_ops->jc_progress)(job + 1, stat);
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL async_job_aio_retsize)(struct aio_handle *__restrict self) {
	struct async_job_aio_data *data;
	struct aio_handle *aio_status;
	struct async_job *job;
	data = (struct async_job_aio_data *)self->ah_data;
	job  = data->ajad_job - 1;
	aio_status = ATOMIC_READ(job->aj_aio);
	assert(job->aj_ops->jc_retsize);
	/* Check if the operation has completed. */
	if (!ASYNC_JOB_AIO_ISPRESENT(aio_status))
		return 0;
	return (*job->aj_ops->jc_retsize)(job + 1);
}

PRIVATE struct aio_handle_type const async_job_aio = {
	/* .ht_fini     = */ &async_job_aio_fini,
	/* .ht_cancel   = */ &async_job_aio_cancel,
	/* .ht_progress = */ &async_job_aio_progress,
	/* .ht_retsize  = */ &async_job_aio_retsize
};

PRIVATE struct aio_handle_type const async_job_aio_noretsize = {
	/* .ht_fini     = */ &async_job_aio_fini,
	/* .ht_cancel   = */ &async_job_aio_cancel,
	/* .ht_progress = */ &async_job_aio_progress
};



/* Start the given async job, and  optionally connect a given AIO  handle
 * for process monitoring, job completion notification, and cancellation:
 *   - `aio_handle_cancel()' can be used to the same effect as `async_job_cancel()'
 *   - `aio->ah_func'  will  be invoked  under the  following conditions
 *     after `async_job_start()' had been called to start the async job,
 *     just after the job has been deleted:
 *     - AIO_COMPLETION_SUCCESS:
 *       - `jc_poll()' returning `ASYNC_JOB_POLL_DELETE'
 *       - `jc_work()' returning `ASYNC_JOB_WORK_COMPLETE'
 *       - `jc_time()' returning `ASYNC_JOB_WORK_COMPLETE'
 *     - AIO_COMPLETION_CANCEL:
 *       - `aio_handle_cancel()' has been called
 *       - `async_job_cancel()' has been called
 *     - AIO_COMPLETION_FAILURE:
 *       - `jc_poll()' returned with an exception
 *       - `jc_work()' returned with an exception
 *       - `jc_time()' returned with an exception
 * Note also that when `aio' is given, it will be initialize to inherit a reference
 * to `self', meaning that `decref(async_job_start(job, aio))' is a valid use case!
 * @return: * : Always re-returns `self' */
PUBLIC NOBLOCK NONNULL((1)) REF async_job_t
NOTHROW(FCALL async_job_start)(async_job_t self,
                               /*out,opt*/ struct aio_handle *aio) {
	struct async_job *me, *next;
	assert(!ASYNC_JOB_AIO_ISSPEC(aio));
	me = self - 1;
#ifndef NDEBUG
	assert(me->aj_next == (REF struct async_job *)0x1234);
#endif /* !NDEBUG */
	assert(me->aj_refcnt == 2);
	assert(me->aj_aio == ASYNC_JOB_AIO_NONPRESENT);
	/* Initialize the AIO handle (if given) */
	if (aio) {
		struct async_job_aio_data *data;
		data = (struct async_job_aio_data *)aio->ah_data;
		data->ajad_job = self;
		me->aj_refcnt  = 3; /* +1: `data->ajad_job' */
		COMPILER_WRITE_BARRIER();
		aio_handle_init(aio,
		                me->aj_ops->jc_retsize
		                ? &async_job_aio
		                : &async_job_aio_noretsize);
	}

	me->aj_aio = aio;
	/* Register the job.
	 * NOTE: The first implicit reference is inherited by `async_jobs' */
	do {
		next = ATOMIC_READ(async_jobs);
		me->aj_next = next;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(async_jobs, next, me));
	/* Signal that new async jobs have become available. */
	sig_broadcast(&awork_changed);
	return self; /* Return the second implicit reference */
}


/* Cancel a given job.
 * This function can be used to prevent future invocation of the given job's functions.
 * WARNING: Job  cancellation  also happens  asynchronously  (except for  in  regards to
 *          the `AIO_COMPLETION_CANCEL' completion  status of a  possibly connected  AIO
 *          handle), meaning that even after this function returns, the job may continue
 *          to exist for a while longer before eventually being deleted! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_cancel)(async_job_t self) {
	struct async_job *me;
	struct aio_handle *aio;
	me  = self - 1;
	PREEMPTION_DISABLE();
	aio = ATOMIC_XCH(me->aj_aio, ASYNC_JOB_AIO_CANCELED);
	if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
		/* Signal AIO completion with `AIO_COMPLETION_CANCEL' */
		aio_handle_complete_nopr(aio, AIO_COMPLETION_CANCEL);
	}
	PREEMPTION_ENABLE();
	/* Wake up the async worker to have to get rid of this job. */
	if (aio != ASYNC_JOB_AIO_CANCELED)
		sig_broadcast(&awork_changed);
}






DECL_END
#endif /* !CONFIG_USE_NEW_ASYNC */

#endif /* !GUARD_KERNEL_SRC_SCHED_ASYNC_C */
