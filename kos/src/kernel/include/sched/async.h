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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H
#define GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#ifdef CONFIG_USE_NEW_ASYNC
#include <sched/lockop.h>
#include <sched/signal-completion.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-lock.h>

#ifdef __cplusplus
#include <kos/kernel/handle.h>
#endif /* __cplusplus */

/* TODO: DEPRECATED: BEGIN */
#define async_job_t struct async *
#define ASYNC_JOB_WORK_COMPLETE ASYNC_FINISHED
#define ASYNC_JOB_WORK_AGAIN    ASYNC_RESUME
#define async_job_free          async_free
#define async_job_callbacks     async_ops
#define async_worker_callbacks  async_worker_ops
/* TODO: DEPRECATED: END */


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
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *ao_destroy)(struct async *__restrict self);

	/* [1..1] Connect to signals that  are delivered when work  arrives.
	 * This function should establish connections with `for_poll = true'
	 * @return: * : Absolute point in time when `ao_time' should be invoked.
	 *              You may return  `KTIME_INFINITE' to  indicate that  this
	 *              async job will never time out. */
	NONNULL((1)) ktime_t
	(FCALL *ao_connect)(struct async *__restrict self);

	/* [1..1] Check if there is any work that needs to be done right now.
	 * @return: true:  Work is available.
	 * @return: false: Nothing to do right now. */
	WUNUSED NONNULL((1)) __BOOL
	(FCALL *ao_test)(struct async *__restrict self);

	/* [1..1] Perform the actual work associated with the async job. This
	 * function will only ever be called _after_ `ao_test()' has returned
	 * indicative of work being available.
	 * @return: * : One of `ASYNC_RESUME', `ASYNC_FINISHED' or `ASYNC_CANCEL' */
	WUNUSED NONNULL((1)) unsigned int
	(FCALL *ao_work)(struct async *__restrict self);

	/* [0..1] Called when the timeout returned by `ao_connect()' has expired.
	 *        When set to `NULL', behave the same as though a function had been
	 *        specified that always returns `ASYNC_CANCEL'.
	 * NOTE: May only ever be called when `ao_connect()' returns `!= KTIME_INFINITE'
	 * @return: * : One of `ASYNC_RESUME', `ASYNC_FINISHED' or `ASYNC_CANCEL' */
	WUNUSED NONNULL((1)) unsigned int
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
	NONNULL((1)) void
	(FCALL *ao_cancel)(struct async *__restrict self);

	/* [0..1] Optional callback to facilitate the `ht_progress' operation of AIO handles.
	 * @return: * :  One of `AIO_PROGRESS_STATUS_*' */
	NOBLOCK NONNULL((1)) unsigned int
	/*NOTHROW*/ (FCALL *ao_progress)(struct async *__restrict self,
	                                 struct aio_handle_stat *__restrict stat);

	/* [0..1] Optional callback to facilitate the `ht_retsize' operation of AIO handles.
	 * NOTE: This callback will only be called after the handle's callback has completed,
	 *       and  the  async job  has  already been,  or  is currently  pending deletion. */
	NOBLOCK NONNULL((1)) size_t
	/*NOTHROW*/ (FCALL *ao_retsize)(struct async *__restrict self);
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
	SLIST_ENTRY(REF async)     a_ready;   /* [lock(ATOMIC)] List of ready jobs. */
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

/* Initialize the given async controller and attach `aio'. The
 * caller must follow this up with a call to  `async_start()',
 * after  which point `aio'  will be notified  once the job is
 * completed (when restarted  later, or  canceled before  that
 * point, the AIO handle will not be notified).  Additionally,
 * use of `async_cancel()' will immediatly indicate completion
 * (with CANCEL status), and `aio_handle_cancel()' will behave
 * the same as `async_cancel()' */
#define async_init_aio(self, ops, aio) \
	((self)->a_ops = (ops), _async_init_aio(self, aio))
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _async_init_aio)(struct async *__restrict self,
                               /*out*/ struct aio_handle *__restrict aio);


/* Helpers for constructing async objects. */
#define async_new(T, ops) \
	((T *)__async_init_ptr((struct async *)kmemalign(__COMPILER_ALIGNOF(T), sizeof(T), GFP_NORMAL), ops))
#define async_new_aio(T, ops, aio) \
	((T *)__async_init_aio_ptr((struct async *)kmemalign(__COMPILER_ALIGNOF(T), sizeof(T), GFP_NORMAL), ops, aio))
#define async_free(self) kfree(self)
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


/* Destroy a given async controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_destroy)(struct async *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct async, a_refcnt, async_destroy);

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
#define __async_list_defined 1
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
	NONNULL((1)) ktime_t (FCALL *awo_connect)(void *__restrict self);

	/* [1..1] Test callback (s.a. `struct async_ops::ao_test') */
	WUNUSED NONNULL((1)) __BOOL (FCALL *awo_test)(void *__restrict self);

	/* [1..1] Work callback (s.a. `struct async_ops::ao_work') */
	WUNUSED NONNULL((1)) unsigned int (FCALL *awo_work)(void *__restrict self);

	/* [0..1] Timeout callback (s.a. `struct async_ops::ao_time') */
	WUNUSED NONNULL((1)) unsigned int (FCALL *awo_time)(void *__restrict self);

	/* [0..1] Cancel callback (s.a. `struct async_ops::ao_time') */
	NONNULL((1)) void (FCALL *awo_cancel)(void *__restrict self);
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
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct async *KCALL
async_worker_new(struct async_worker_ops const *__restrict ops,
                 void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC);


/* TODO: Once support for `#ifndef CONFIG_USE_NEW_ASYNC' is gone, get rid
 *       of  `register_async_worker()'  and   `unregister_async_worker()'
 *       Sub-systems  should  instead make  use  of `async_worker_new()',
 *       and simply store the returned object somewhere, and simply  make
 *       use of `async_cancel()+decref()' instead of unregister. */

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

#else /* CONFIG_USE_NEW_ASYNC */

#ifdef __cplusplus
#include <kernel/handle.h>
#endif /* __cplusplus */

/* The async callback API can be used to facilitate the servicing of
 * operations that require synchronous access as the result of async
 * input (such as hardware interrupts)
 * For this purpose, a pre-defined thread `asyncwork' is defined that
 * exists on a similar level to `boottask', which always idles in the
 * background,   waiting   for  async   work  to   become  available.
 * Note however that KOS is allowed to distribute the async work-load
 * over multiple threads  spanning across multiple  CPUs in order  to
 * improve performance.
 * The public API consists of 2 functions:
 *  - register_async_worker()
 *  - unregister_async_worker()
 * Which can be used to register objects and callbacks that need to be
 * invoked in the context of said thread in order to check for work to
 * be available, and process that work as necessary
 */

DECL_BEGIN

#ifdef __CC__


#ifdef CONFIG_BUILDING_KERNEL_CORE
struct task;
INTDEF struct task asyncwork;
INTDEF ATTR_NORETURN void KCALL _asyncmain(void);
#endif /* CONFIG_BUILDING_KERNEL_CORE */

struct async_worker_callbacks {
	/* [1..1] Poll-callback.
	 * Test  for  available  work  (if  available,  return `true'),
	 * else: connect  to the appropriate signals that get broadcast
	 * when work does become available, and finally test once again
	 * for  work being available (and also return `true' if this is
	 * the  case), in order  to prevent the  race condition of work
	 * becoming available after the first test, but before a signal
	 * connection got established.
	 * NOTE: If need be, this function should also call  `async_worker_timeout()'
	 *       with the appropriate  realtime()-timeout for  when the  `awc_time()'
	 *       callback  should  be invoked.  Also note  that this  has to  be done
	 *       every time that  this callback  is invoked, as  timeouts may  either
	 *       only be maintained until the next time that the backing async-thread
	 *       restarts polling, and/or only exist on the basis of keeping track of
	 *       the timeout that will expire the earliest.
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: self:   [1..1] A reference to `ob_pointer' passed when the object was registered.
	 * @return: true:  Work is available, and the `awc_work()'-callback should be invoked.
	 * @return: false: No work available at the moment. */
	NONNULL((1, 2)) bool (FCALL *awc_poll)(void *__restrict self,
	                                       void *__restrict cookie);

	/* [1..1] Work-callback.
	 * Perform async work with all available data, returning
	 * once all work currently available has been completed.
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: self: [1..1] A reference to `ob_pointer' passed when the object was registered. */
	NONNULL((1)) void (FCALL *awc_work)(void *__restrict self);

	/* [0..1] Test-callback.
	 * Prototype for test-async-work-available
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: self:   [1..1] A reference to `ob_pointer' passed when the object was registered.
	 * @return: true:  Work is available, and the `awc_work()'-callback should be invoked.
	 * @return: false: No work available at the moment. */
	NONNULL((1)) bool (FCALL *awc_test)(void *__restrict self);
};

/* Called after a timeout set during `awc_poll()' has expired. */
typedef NONNULL((1)) void (FCALL *async_worker_timeout_t)(void *__restrict self);

/* This function may  be called  by `awc_poll()'-callbacks  to
 * specify the realtime() timestamp when `on_timeout()' should
 * be invoked. The  given `cookie' must  be the same  argument
 * prviously passed to `awc_poll()'
 * NOTE: After  this function got called, `awc_poll()' should return
 *       `false', as the timeout may not come into effect otherwise. */
FUNDEF NOBLOCK NONNULL((2, 3)) void
NOTHROW(FCALL async_worker_timeout)(ktime_t abs_timeout,
                                                void *__restrict cookie,
                                                async_worker_timeout_t on_timeout);


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
FUNDEF NONNULL((1, 2)) bool KCALL
register_async_worker(struct async_worker_callbacks const *__restrict cb,
                      void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC);

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
FUNDEF NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL unregister_async_worker)(struct async_worker_callbacks const *__restrict cb,
                                       void *__restrict ob_pointer, uintptr_half_t ob_type);

#ifdef __cplusplus
#define _ASYNC_WORKER_CXX_FWD_STRUCT(HT, T) T;
HANDLE_FOREACH_CUSTOMTYPE(_ASYNC_WORKER_CXX_FWD_STRUCT)
#undef _ASYNC_WORKER_CXX_FWD_STRUCT
extern "C++" {

#define _ASYNC_WORKER_CXX_DECLARE(HT, T)                                                       \
	LOCAL NONNULL((1, 2)) bool KCALL                                                           \
	register_async_worker(struct async_worker_callbacks const *__restrict cb,                  \
	                      T *__restrict ob_pointer) THROWS(E_BADALLOC) {                       \
		return register_async_worker(cb, (void *)ob_pointer, HT);                              \
	}                                                                                          \
	LOCAL NOBLOCK NONNULL((1, 2)) bool                                                         \
	NOTHROW(KCALL unregister_async_worker)(struct async_worker_callbacks const *__restrict cb, \
	                                       T *__restrict ob_pointer) {                         \
		return unregister_async_worker(cb, (void *)ob_pointer, HT);                            \
	}
HANDLE_FOREACH_CUSTOMTYPE(_ASYNC_WORKER_CXX_DECLARE)
#undef _ASYNC_WORKER_CXX_DECLARE

}
#endif /* __cplusplus */




/* Return codes for `async_job_callbacks::jc_poll' */
#define ASYNC_JOB_POLL_AVAILABLE         0 /* Work appears to be available, and `jc_work()' should be invoked. */
#define ASYNC_JOB_POLL_WAITFOR           1 /* No work available right now (but the proper signals were connected) */
#define ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT 2 /* Same as `ASYNC_JOB_POLL_WAITFOR', but ignore `timeout'. */
#define ASYNC_JOB_POLL_DELETE            3 /* Nothing left to do (delete the job with a success status) */

/* Return codes for `async_job_callbacks::jc_work' adn `async_job_callbacks::jc_time' */
#define ASYNC_JOB_WORK_COMPLETE 0 /* Work  has been completed, and the async-job should delete itself. In
                                   * this case, the caller will unlink the async-job and invoke `jc_fini' */
#define ASYNC_JOB_WORK_AGAIN    1 /* Work  is still incomplete, and the caller should call `jc_poll()' next
                                   * until that function returns `true' before calling this function again. */

/* A pointer to the `self' argument of async jobs. */
struct async_job;
typedef struct async_job *async_job_t;
struct aio_handle_stat;

/* Async jobs are similar to async workers, however are designed as
 * one-time jobs that delete themself once they've been  completed.
 * NOTE: async job callbacks are inherently thread-safe:
 *
 *   - jc_fini() is the last function that may ever be called, and
 *     will only be invoked _after_ any other callback has already
 *     returned.
 *
 *   - Only one of `jc_poll()', `jc_work()', `jc_time()' and `jc_cancel()'
 *     may  ever be called  at the same time.  (i.e. no synchronization is
 *     necessary between these callbacks)
 *
 *   - Only `jc_progress()' and `jc_retsize()' might be called from  the
 *     outside of the async-job, however since these callbacks are meant
 *     to perform read-only operations,  they should also be  inherently
 *     thread-safe,  since they aren't  meant to modify  the state of an
 *     async-job (though if done right,  even that would be allowed  and
 *     possible) (also  note that  `jc_retsize()' is  only called  after
 *     the job had already been deleted/canceled)
 *
 *   - `jc_work()' will only  ever be called  after `jc_poll()'  returned
 *     with  `ASYNC_JOB_POLL_AVAILABLE'  between  `jc_poll()'  returning,
 *     and a previous call to `jc_work()', or the start of the async job.
 */
struct async_job_callbacks {
	size_t         jc_jobsize;  /* Size of the structure pointed-to by the `self' arguments used by callbacks. */
	size_t         jc_jobalign; /* Alignment requirements of the structure pointed-to by the `self' arguments used by callbacks. */
	struct driver *jc_driver;   /* [1..1] The driver implementing the callbacks. */

	/* [0..1] Finalizer for `self' */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *jc_fini)(async_job_t self);

	/* [1..1] Poll-callback. Behaves  similar  to  the one  for  async  workers.
	 * If this function returns with an exception, the job will also be deleted.
	 * @param: timeout: [out] Must be filled in with an absolute ktime() timestamp when
	 *                        `ASYNC_JOB_POLL_WAITFOR'  is returned. Once this point in
	 *                        time has elapsed, the `jc_time()' callback is invoked.
	 *                        NOTE: This argument only has meaning when `ASYNC_JOB_POLL_WAITFOR'
	 *                              is returned.
	 * @return: * : One of `ASYNC_JOB_POLL_*' */
	NONNULL((1, 2)) unsigned int
	(FCALL *jc_poll)(async_job_t self, /*out*/ ktime_t *__restrict timeout);

	/* [1..1] Perform the work associated with this async-job.
	 * If this function returns with an exception, the job will also be deleted.
	 * NOTE: This callback will only be invoked if `jc_poll' returned
	 *       `ASYNC_JOB_POLL_AVAILABLE' at some point between now and
	 *       the last call to `jc_work', or the creation of the async
	 *       job.
	 * @return: * : One of `ASYNC_JOB_WORK_*' */
	NONNULL((1)) unsigned int
	(FCALL *jc_work)(async_job_t self);

	/* [?..1] Callback that is invoked when the timeout filled in by `jc_poll()' has elapsed.
	 *        This callback only has to be [valid] when `jc_poll()' is able to return `ASYNC_JOB_POLL_WAITFOR'.
	 *        If  that  callback  only  ever  returns  `ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT',  then  this callback
	 *        doesn't need to be filled in.
	 * If this function returns with an exception, the job will also be deleted.
	 * @return: * : One of `ASYNC_JOB_WORK_*' */
	NONNULL((1)) unsigned int
	(FCALL *jc_time)(async_job_t self);

	/* [0..1] Optional callback that is invoked when the job is explicitly canceled (s.a. `async_job_cancel()').
	 *  NOTE: When this callback is invoked, it is guarantied that none of this job's
	 *        other callbacks are being  executed at the same  time. This is done  by
	 *        having `async_job_cancel()' change the job's internal state to indicate
	 *        that  the job  is being canceled,  which then causes  the backing async
	 *        worker to then invoke this callback.
	 * If this function returns with an exception, that error will be discarded,
	 * and the job will be deleted none-the-less. */
	NONNULL((1)) void
	(FCALL *jc_cancel)(async_job_t self);

	/* [0..1] Optional callback to facilitate the `ht_progress' operation of AIO handles.
	 * WARNING:  This callback may  be called at the  same time as  one of the callbacks! */
	NOBLOCK NONNULL((1)) unsigned int
	/*NOTHROW*/ (FCALL *jc_progress)(async_job_t self, struct aio_handle_stat *__restrict stat);

	/* [0..1] Optional callback to facilitate the `ht_retsize' operation of AIO handles.
	 * NOTE: This callback will only be called after the handle's callback has completed,
	 *       and  the  async job  has  already been,  or  is currently  pending deletion. */
	NOBLOCK NONNULL((1)) size_t
	/*NOTHROW*/ (FCALL *jc_retsize)(async_job_t self);
};

/* Destroy an async-job that has previously been started (i.e. `async_job_start(self)' was called). */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL async_job_destroy)(async_job_t self);

/* Return an lvalue-reference to the reference counter for for the given async-job. */
#ifdef __cplusplus
struct __async_job_struct { WEAK refcnt_t __aj_refcnt; };
#define async_job_refcnt(self) ((struct __async_job_struct *)(self))[-1].__aj_refcnt
#else /* __cplusplus */
#define async_job_refcnt(self) (((WEAK refcnt_t *)(self))[-1])
#endif /* !__cplusplus */

DEFINE_REFCOUNT_FUNCTIONS_P(struct async_job, async_job_refcnt, async_job_destroy)

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
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) /*inherit*/ async_job_t FCALL
async_job_alloc(struct async_job_callbacks const *__restrict cb);

/* Free a previously allocated, but not-yet started job */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL async_job_free)(async_job_t self);

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
FUNDEF NOBLOCK NONNULL((1)) REF async_job_t
NOTHROW(FCALL async_job_start)(async_job_t self,
                               /*out,opt*/ struct aio_handle *aio DFL(__NULLPTR));

/* Cancel a given job.
 * This function can be used to prevent future invocation of the given job's functions.
 * WARNING: Job  cancellation  also happens  asynchronously  (except for  in  regards to
 *          the `AIO_COMPLETION_CANCEL' completion  status of a  possibly connected  AIO
 *          handle), meaning that even after this function returns, the job may continue
 *          to exist for a while longer before eventually being deleted! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_cancel)(async_job_t self);

#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_USE_NEW_ASYNC */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H */
