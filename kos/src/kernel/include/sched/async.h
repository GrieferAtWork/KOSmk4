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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H
#define GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <sched/sig-completion.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/lockop.h>

#ifdef __cplusplus
#include <kos/kernel/handle.h>
#endif /* __cplusplus */

#ifdef __CC__
DECL_BEGIN

#ifdef CONFIG_BUILDING_KERNEL_CORE
struct task;
INTDEF struct task asyncwork;
INTDEF ATTR_NORETURN void KCALL _asyncmain(void);
#endif /* CONFIG_BUILDING_KERNEL_CORE */


struct aio_handle_stat;
struct async;
struct async_ops {
	/* [1..1] The driver responsible for this providing the below operators.
	 * Whenever  a driver is  unloaded, all async jobs  claiming to use that
	 * driver will be canceled. */
	struct driver *ao_driver;

	/* [0..1] Optional destroy-callback  (fini_oob_fields+free)
	 * When not defined, simply `kfree(self)' as a replacement. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *ao_destroy)(struct async *__restrict self);

	/* [1..1] Connect to signals that  are delivered when work  arrives.
	 * This function should establish connections with `for_poll = true'
	 * @return: * : Absolute point in time when `ao_time' should be invoked.
	 *              You may return  `KTIME_INFINITE' to  indicate that  this
	 *              async job will never time out. */
	NONNULL_T((1)) ktime_t
	(FCALL *ao_connect)(struct async *__restrict self);

	/* [1..1] Check if there is any work that needs to be done right  now.
	 * If this function throws an exception, the error will be transferred
	 * to  an attached AIO handle, or dumped  to the system log before the
	 * async job is canceled.
	 * @return: true:  Work is available.
	 * @return: false: Nothing to do right now. */
	WUNUSED_T NONNULL_T((1)) __BOOL
	(FCALL *ao_test)(struct async *__restrict self);

	/* [1..1] Perform the actual work associated with the async job. This
	 * function will only ever be called _after_ `ao_test()' has returned
	 * indicative of work being available.
	 * If this function throws an exception, the error will be transferred
	 * to  an attached AIO handle, or dumped  to the system log before the
	 * async job is canceled.
	 *
	 * IMPORTANT: Note that this function isn't marked as `BLOCKING', but
	 *            also not as `NOBLOCK'. If BLOCKING is needed, then  you
	 *            must re-write your  code to such  that waiting is  done
	 *            through calls to `ao_connect()' and `ao_test()'!
	 *
	 * @return: * : One of `ASYNC_RESUME', `ASYNC_FINISHED' or `ASYNC_CANCEL' */
	WUNUSED_T NONNULL_T((1)) unsigned int
	(FCALL *ao_work)(struct async *__restrict self);

	/* [0..1] Called when the timeout returned by `ao_connect()' has expired.
	 *        When set to `NULL', behave the same as though a function had been
	 *        specified that always returns `ASYNC_CANCEL'.
	 * NOTE: May only ever be called when `ao_connect()' returns `!= KTIME_INFINITE'
	 * If  this  function  throws  an  exception,  the  error  will  be  transferred
	 * to  an  attached  AIO  handle,  or  dumped  to  the  system  log  before  the
	 * async job is canceled.
	 * @return: * : One of `ASYNC_RESUME', `ASYNC_FINISHED' or `ASYNC_CANCEL' */
	WUNUSED_T NONNULL_T((1)) unsigned int
	(FCALL *ao_time)(struct async *__restrict self);

	/* [0..1] Callback invoked (in the context of some async worker-thread)  every
	 *        time that the job is  canceled. Note that the  # of times that  this
	 *        callback  is invoked doesn't  necessarily match the  # of times that
	 *        one  calls  `async_cancel()'. However,  if  the async  job  was ever
	 *        started (via  `async_start()'), this  callback is  guarantied to  be
	 *        called at some point in the future. And if `async_start()' is called
	 *        once  again after this  callback is invoked (or  even from inside of
	 *        this callback), then this callback  is guarantied to be invoked  yet
	 *        again at some point in the future.
	 * NOTE:  This  callback is not invoked if `ASYNC_FINISHED' is returned by either
	 *        `ao_work' or `ao_time'. But it is called if `ASYNC_CANCEL' is returned. */
	NONNULL_T((1)) void
	(FCALL *ao_cancel)(struct async *__restrict self);

	/* [0..1] Optional callback to facilitate the `ht_progress' operation of AIO handles.
	 * @return: * :  One of `AIO_PROGRESS_STATUS_*' */
	NOBLOCK NONNULL_T((1)) unsigned int
	NOTHROW_T(FCALL *ao_progress)(struct async *__restrict self,
	                              struct aio_handle_stat *__restrict stat);

	/* [0..1] Optional callback to facilitate the `ht_retsize' operation of AIO handles.
	 * NOTE: This callback will only be called after the handle's callback has completed,
	 *       and  the  async job  has  already been,  or  is currently  pending deletion. */
	NOBLOCK NONNULL_T((1)) size_t
	NOTHROW_T(FCALL *ao_retsize)(struct async *__restrict self);
};

/* Async work/time return values. */
#define ASYNC_RESUME   0 /* More work is available. */
#define ASYNC_FINISHED 1 /* All work is done. (delete the async job) */
#define ASYNC_CANCEL   2 /* Same as `ASYNC_FINISHED',  but invoke  `ao_cancel' (if  defined),
                          * and complete an attached AIO operation as `AIO_COMPLETION_CANCEL' */





/* Internal async states. Transitions:
 *   _ASYNC_ST_INIT           ->  _ASYNC_ST_INIT_STOP       // async_cancel()
 *   _ASYNC_ST_INIT           ->  _ASYNC_ST_ADDALL          // async_start()
 *
 *   _ASYNC_ST_INIT_STOP      ->  _ASYNC_ST_ADDALL          // async_start()
 *
 *   _ASYNC_ST_ADDALL         ->  _ASYNC_ST_ADDALL_STOP     // async_cancel()
 *   _ASYNC_ST_ADDALL         ->  _ASYNC_ST_TRIGGERED       // add-to-all-lockop-completion
 *
 *   _ASYNC_ST_ADDALL_STOP    ->  _ASYNC_ST_ADDALL          // async_start()
 *   _ASYNC_ST_ADDALL_STOP    ->  _ASYNC_ST_INIT_STOP       // add-to-all-lockop-completion
 *
 *   _ASYNC_ST_READY          ->  _ASYNC_ST_TRIGGERED       // Signal-completion-callback
 *   _ASYNC_ST_READY          ->  _ASYNC_ST_TRIGGERED_STOP  // ao_work:!=ASYNC_RESUME or async_cancel()
 *   _ASYNC_ST_READY          ->  _ASYNC_ST_READY_TMO       // ao_connect:return!=KTIME_INFINITE
 *
 *   _ASYNC_ST_READY_TMO      ->  _ASYNC_ST_SLEEPING        // worker-waits-for-timeout
 *   _ASYNC_ST_READY_TMO      ->  _ASYNC_ST_DELTMO          // async_cancel()
 *
 *   _ASYNC_ST_SLEEPING       ->  _ASYNC_ST_READY_TMO       // timeout-not-expired
 *   _ASYNC_ST_SLEEPING       ->  _ASYNC_ST_TRIGGERED_STOP  // async_cancel()
 *   _ASYNC_ST_SLEEPING       ->  _ASYNC_ST_TRIGGERED       // timeout-expired->ao_time:ASYNC_RESUME
 *   _ASYNC_ST_SLEEPING       ->  _ASYNC_ST_DELTMO          // timeout-expired->ao_time:ASYNC_FINISHED
 *   _ASYNC_ST_SLEEPING       ->  _ASYNC_ST_TRIGGERED_STOP  // timeout-expired->ao_time:ASYNC_CANCEL
 *
 *   _ASYNC_ST_TRIGGERED      ->  _ASYNC_ST_TRIGGERED_STOP  // async_cancel()
 *   _ASYNC_ST_TRIGGERED      ->  _ASYNC_ST_READY           // Async-event-handled
 *
 *   _ASYNC_ST_TRIGGERED_STOP ->  _ASYNC_ST_TRIGGERED       // async_start()
 *   _ASYNC_ST_TRIGGERED_STOP ->  _ASYNC_ST_DELALL          // Async-event-handled
 *
 *   _ASYNC_ST_DELALL_STRT    ->  _ASYNC_ST_TRIGGERED       // del-from-all-lockop-completion
 *   _ASYNC_ST_DELALL_STRT    ->  _ASYNC_ST_DELALL          // async_cancel()
 *
 *   _ASYNC_ST_DELALL         ->  _ASYNC_ST_DELALL_STRT     // async_start()
 *   _ASYNC_ST_DELALL         ->  _ASYNC_ST_INIT_STOP       // del-from-all-lockop-completion
 *
 *   _ASYNC_ST_DELTMO_STRT    ->  _ASYNC_ST_TRIGGERED       // del-from-tmo-lockop-completion
 *
 *   _ASYNC_ST_DELTMO         ->  _ASYNC_ST_DELTMO_STRT     // async_start()
 *   _ASYNC_ST_DELTMO         ->  _ASYNC_ST_TRIGGERED_STOP  // del-from-tmo-lockop-completion
 */
#define _ASYNC_ST_INIT            0 /* Initial state */
#define _ASYNC_ST_INIT_STOP       1 /* Same as `_ASYNC_ST_INIT', but `async_cancel()' was called */
#define _ASYNC_ST_ADDALL          2 /* A lockop is pending to add the job to `async_all_list' */
#define _ASYNC_ST_ADDALL_STOP     3 /* Same as `_ASYNC_ST_ADDALL', but `async_cancel()' was called */
#define _ASYNC_ST_DELALL_STRT     4 /* Same as `_ASYNC_ST_DELALL', but `async_start()' was called */
#define _ASYNC_ST_DELALL          5 /* A lockop is pending to remove the job from `async_all_list' */
#define _ASYNC_ST_READY           6 /* The job is fully up & running. */
/*efine _ASYNC_ST_                7  * ... */
#define _ASYNC_ST_READY_TMO       8 /* Same as `_ASYNC_ST_READY', but a timeout was set. */
/*efine _ASYNC_ST_                9  * ... */
#define _ASYNC_ST_TRIGGERED      10 /* An async event was triggered. */
#define _ASYNC_ST_TRIGGERED_STOP 11 /* Same as `_ASYNC_ST_TRIGGERED', but `async_cancel()' was called */
#define _ASYNC_ST_SLEEPING       12 /* Waiting for timeout to expire. */
/*efine _ASYNC_ST_               13  * ... */
#define _ASYNC_ST_DELTMO_STRT    14 /* Same as `_ASYNC_ST_DELTMO', but `async_start()' was called */
#define _ASYNC_ST_DELTMO         15 /* A lockop is pending to remove the job from the timeout queue */



struct aio_handle;
struct async {
	WEAK refcnt_t              a_refcnt;  /* Reference counter. */
	unsigned int               a_stat;    /* [lock(ATOMIC)] Async status (one of `_ASYNC_ST_*') */
	struct async_ops const    *a_ops;     /* [1..1][const] Worker operators. */
#ifdef __WANT_ASYNC__a_lockop
	union {
		struct lockop             _a_lockop;     /* ... */
		struct postlockop         _a_postlockop; /* ... */
		struct sig_multicompletion a_comp;       /* ... */
	};
#else /* __WANT_ASYNC__a_lockop */
	struct sig_multicompletion a_comp;    /* [valid_if(a_stat >= _ASYNC_ST_READY)][lock(ASYNC_WORKER)]
	                                       * Internal  signal  completion controller  used  to monitor
	                                       * async  jobs for completion, as well as to maintain a list
	                                       * of ready jobs, without having to globally re-connect  all
	                                       * jobs whenever one of them becomes ready. */
#endif /* !__WANT_ASYNC__a_lockop */
	LIST_ENTRY(REF async)      a_all;     /* [0..1][lock(async_all_lock)] Entry in the list of all async jobs. */
	SLIST_ENTRY(REF async)     a_ready;   /* [0..1][lock(ATOMIC)] List of ready jobs. */
	WEAK struct aio_handle    *a_aio;     /* [0..1][lock(CLEAR_ONCE)] Attached AIO and job cancellation indicator. */
	LIST_ENTRY(REF async)      a_tmolnk;  /* [0..1][lock(INTERN)]
	                                       * [valid_if(_ASYNC_ST_READY_TMO || _ASYNC_ST_DELTMO ||
	                                       *           _ASYNC_ST_DELTMO_STRT)]
	                                       * Link entry in the list of async jobs w/ timeouts. */
	union {
		ktime_t                a_tmo;     /* [lock(INTERN)][valid_if(_ASYNC_ST_READY_TMO || _ASYNC_ST_SLEEPING)]
		                                   * Timeout of this job. */
		struct lockop         _a_tmolockop;     /* ... */
		struct postlockop     _a_tmopostlockop; /* ... */
	};
	/* Worker-specific data will go here... */
};

#define async_init(self, ops)           \
	((self)->a_refcnt = 1,              \
	 (self)->a_stat   = _ASYNC_ST_INIT, \
	 (self)->a_ops    = (ops),          \
	 (self)->a_aio    = __NULLPTR)

/* Initialize the given async controller and attach `aio'.  The
 * caller must follow this up  with a call to  `async_start()',
 * after which point  `aio' will  be notified once  the job  is
 * completed  (when  restarted later,  or canceled  before that
 * point, the AIO handle  will not be notified).  Additionally,
 * use of `async_cancel()' will immediately indicate completion
 * (with  CANCEL status), and `aio_handle_cancel()' will behave
 * the same as `async_cancel()' */
#define async_init_aio(self, ops, aio) \
	((self)->a_ops = (ops), _async_init_aio(self, aio))
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _async_init_aio)(struct async *__restrict self,
                               /*out*/ struct aio_handle *__restrict aio);


/* Helpers for constructing async objects. */
#define async_new(T, ops)                      ((T *)__async_init_ptr((struct async *)kmemalign(__COMPILER_ALIGNOF(T), sizeof(T), GFP_NORMAL), ops))
#define async_new_aio(T, ops, aio)             ((T *)__async_init_aio_ptr((struct async *)kmemalign(__COMPILER_ALIGNOF(T), sizeof(T), GFP_NORMAL), ops, aio))
#define async_new_gfp(T, ops, gfp)             ((T *)__async_init_ptr((struct async *)kmemalign(__COMPILER_ALIGNOF(T), sizeof(T), gfp), ops))
#define async_new_aio_gfp(T, ops, aio, gfp)    ((T *)__async_init_aio_ptr((struct async *)kmemalign(__COMPILER_ALIGNOF(T), sizeof(T), gfp), ops, aio))
#define async_new_nx(T, ops)                   ((T *)__async_init_ptr_nx((struct async *)kmemalign_nx(__COMPILER_ALIGNOF(T), sizeof(T), GFP_NORMAL), ops))
#define async_new_aio_nx(T, ops, aio)          ((T *)__async_init_aio_ptr_nx((struct async *)kmemalign_nx(__COMPILER_ALIGNOF(T), sizeof(T), GFP_NORMAL), ops, aio))
#define async_new_gfp_nx(T, ops, gfp)          ((T *)__async_init_ptr_nx((struct async *)kmemalign_nx(__COMPILER_ALIGNOF(T), sizeof(T), gfp), ops))
#define async_new_aio_gfp_nx(T, ops, aio, gfp) ((T *)__async_init_aio_ptr_nx((struct async *)kmemalign_nx(__COMPILER_ALIGNOF(T), sizeof(T), gfp), ops, aio))
#define async_free(self)                       kfree(self)
FORCELOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct async *
NOTHROW(__async_init_ptr)(struct async *__restrict self,
                          struct async_ops const *__restrict ops) {
	async_init(self, ops);
	return self;
}
FORCELOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct async *
NOTHROW(__async_init_aio_ptr)(struct async *__restrict self,
                              struct async_ops const *__restrict ops,
                              struct aio_handle *__restrict aio) {
	async_init_aio(self, ops, aio);
	return self;
}
FORCELOCAL ATTR_ARTIFICIAL WUNUSED NONNULL((2)) struct async *
NOTHROW(__async_init_ptr_nx)(struct async *self,
                             struct async_ops const *__restrict ops) {
	if likely(self)
		async_init(self, ops);
	return self;
}
FORCELOCAL ATTR_ARTIFICIAL WUNUSED NONNULL((2, 3)) struct async *
NOTHROW(__async_init_aio_ptr_nx)(struct async *self,
                                 struct async_ops const *__restrict ops,
                                 struct aio_handle *__restrict aio) {
	if likely(self)
		async_init_aio(self, ops, aio);
	return self;
}


/* Destroy a given async controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_destroy)(struct async *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct async, a_refcnt, async_destroy);

/* Start (or re-start) a given async job.
 * Note that when re-starting an async controller, previously attached
 * AIO  handles will always be detached (iow: any async controller can
 * only ever be attached once to only a single AIO handle) */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct async *
NOTHROW(FCALL async_start)(struct async *__restrict self);

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
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct async *
NOTHROW(FCALL async_cancel)(struct async *__restrict self);


#ifndef __async_list_defined
#define __async_list_defined
LIST_HEAD(async_list, async);
#endif /* !__async_list_defined */

/* API access to the set of all running async jobs. */
DATDEF struct REF async_list /**/ async_all_list; /* [0..n][lock(async_all_lock)] List of all running async jobs. */
DATDEF size_t /*               */ async_all_size; /* [lock(async_all_lock)] Total # of async jobs. */
DATDEF struct atomic_lock /*   */ async_all_lock; /* Lock for the async-job list */
DATDEF struct lockop_slist /*  */ async_all_lops; /* Pending lock operations for `async_all_lock' */
#define _async_all_reap()      _lockop_reap_atomic_lock(&async_all_lops, &async_all_lock)
#define async_all_reap()       lockop_reap_atomic_lock(&async_all_lops, &async_all_lock)
#define async_all_tryacquire() atomic_lock_tryacquire(&async_all_lock)
#define async_all_acquire()    atomic_lock_acquire(&async_all_lock)
#define async_all_acquire_nx() atomic_lock_acquire_nx(&async_all_lock)
#define async_all_release()    (atomic_lock_release(&async_all_lock), async_all_reap())
#define async_all_release_f()  atomic_lock_release(&async_all_lock)
#define async_all_acquired()   atomic_lock_acquired(&async_all_lock)
#define async_all_available()  atomic_lock_available(&async_all_lock)
#define async_all_waitfor()    atomic_lock_waitfor(&async_all_lock)
#define async_all_waitfor_nx() atomic_lock_waitfor_nx(&async_all_lock)





/************************************************************************/
/* HIGH-LEVEL ASYNC WORKER API                                          */
/************************************************************************/

/* High-level  helper wrappers for kernel-object-level async operations.
 * These functions automatically deal with weak references to some given
 * kernel object, as well as  the encapsulation of the underlying  async
 * controller object.
 *
 * NOTE: The `self' argument for all of the following is always the
 *       kernel object against which the associated async worker is
 *       bound.
 *       Note that `!wasdestroyed((T *)self)' is guarantied here!
 *
 * Also note that the guaranty is made that none of the callbacks
 * will  ever be  invoked again  once `self'  has been destroyed! */
struct async_worker_ops {
	struct async_ops awo_async; /* Underlying async ops. */

	/* [1..1] Connect callback (s.a. `struct async_ops::ao_connect') */
	NONNULL_T((1)) ktime_t (FCALL *awo_connect)(void *__restrict self);

	/* [1..1] Test callback (s.a. `struct async_ops::ao_test') */
	WUNUSED_T NONNULL_T((1)) __BOOL (FCALL *awo_test)(void *__restrict self);

	/* [1..1] Work callback (s.a. `struct async_ops::ao_work') */
	WUNUSED_T NONNULL_T((1)) unsigned int (FCALL *awo_work)(void *__restrict self);

	/* [0..1] Timeout callback (s.a. `struct async_ops::ao_time') */
	WUNUSED_T NONNULL_T((1)) unsigned int (FCALL *awo_time)(void *__restrict self);

	/* [0..1] Cancel callback (s.a. `struct async_ops::ao_time') */
	NONNULL_T((1)) void (FCALL *awo_cancel)(void *__restrict self);
};

/* Static initializer for `struct async_worker_ops::awo_async' */
#define ASYNC_WORKER_OPS_INIT_BASE               \
	{                                            \
		.ao_driver   = &drv_self,                \
		.ao_destroy  = &_async_worker_v_destroy, \
		.ao_connect  = &_async_worker_v_connect, \
		.ao_test     = &_async_worker_v_test,    \
		.ao_work     = &_async_worker_v_work,    \
		.ao_time     = &_async_worker_v_time,    \
		.ao_cancel   = &_async_worker_v_cancel,  \
		.ao_progress = __NULLPTR,                \
		.ao_retsize  = __NULLPTR                 \
	}

/* Operators for `struct async_worker_ops::awo_async' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _async_worker_v_destroy)(struct async *__restrict self);
FUNDEF NONNULL((1)) ktime_t FCALL _async_worker_v_connect(struct async *__restrict self);
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL _async_worker_v_test(struct async *__restrict self);
FUNDEF WUNUSED NONNULL((1)) unsigned int FCALL _async_worker_v_work(struct async *__restrict self);
FUNDEF WUNUSED NONNULL((1)) unsigned int FCALL _async_worker_v_time(struct async *__restrict self);
FUNDEF NONNULL((1)) void FCALL _async_worker_v_cancel(struct async *__restrict self);

/* Create (but don't start) a new async worker for the given object. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct async *KCALL
async_worker_new(struct async_worker_ops const *__restrict ops,
                 void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC);


/* TODO: Get rid of `register_async_worker()' and `unregister_async_worker()'
 *       Sub-systems  should  instead make  use of  `async_worker_new()', and
 *       simply store the returned object  somewhere, and simply make use  of
 *       `async_cancel()+decref()' instead of unregister. */

/* Using  an internal database of known async workers, add or remove
 * workers for the given operator table, that are bound to the given
 * ob_pointer/ob_type pair. */
FUNDEF NONNULL((1, 2)) __BOOL KCALL
register_async_worker(struct async_worker_ops const *__restrict ops,
                      void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(KCALL unregister_async_worker)(struct async_worker_ops const *__restrict ops,
                                       void *__restrict ob_pointer, uintptr_half_t ob_type);

#ifdef __cplusplus
#define _ASYNC_WORKER_CXX_FWD_STRUCT(HT, T) T;
HANDLE_FOREACH_CUSTOMTYPE(_ASYNC_WORKER_CXX_FWD_STRUCT)
#undef _ASYNC_WORKER_CXX_FWD_STRUCT
extern "C++" {
#define _ASYNC_WORKER_CXX_DECLARE(HT, T)                                                  \
	LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct async *KCALL                 \
	async_worker_new(struct async_worker_ops const *__restrict ops,                       \
	                 T *__restrict ob_pointer) THROWS(E_BADALLOC) {                       \
		return async_worker_new(ops, (void *)ob_pointer, HT);                             \
	}                                                                                     \
	LOCAL NONNULL((1, 2)) bool KCALL                                                      \
	register_async_worker(struct async_worker_ops const *__restrict ops,                  \
	                      T *__restrict ob_pointer) THROWS(E_BADALLOC) {                  \
		return register_async_worker(ops, (void *)ob_pointer, HT);                        \
	}                                                                                     \
	LOCAL NOBLOCK NONNULL((1, 2)) bool                                                    \
	NOTHROW(KCALL unregister_async_worker)(struct async_worker_ops const *__restrict ops, \
	                                       T *__restrict ob_pointer) {                    \
		return unregister_async_worker(ops, (void *)ob_pointer, HT);                      \
	}
HANDLE_FOREACH_CUSTOMTYPE(_ASYNC_WORKER_CXX_DECLARE)
#undef _ASYNC_WORKER_CXX_DECLARE
} /* extern "C++" */
#endif /* __cplusplus */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H */
