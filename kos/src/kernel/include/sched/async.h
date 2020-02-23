/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H
#define GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#ifdef __cplusplus
#include <kernel/handle.h>
#endif /* __cplusplus */

/* The async callback API can be used to facilitate the servicing of
 * operations that require synchronous access as the result of async
 * input (such as hardware interrupts)
 * For this purpose, a pre-defined thread `_asyncwork' is defined that
 * exists on a similar level to `_boottask', which always idles in the
 * background, waiting for async work to become available.
 * Note however that KOS is allowed to distribute the async work-load
 * over multiple threads spanning across multiple CPUs in order to
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
INTDEF struct task _asyncwork;
INTDEF ATTR_NORETURN void NOTHROW(FCALL _asyncmain)(void);
#endif /* CONFIG_BUILDING_KERNEL_CORE */

#define ASYNC_CALLBACK_CC FCALL

struct async_worker_callbacks {
	/* [1..1] Poll-callback.
	 * Test for available work (if available, return `true'),
	 * else: connect to the appropriate signals that get broadcast
	 * when work does become available, and finally test once again
	 * for work being available (and also return `true' if this is
	 * the case), in order to prevent the race condition of work
	 * becoming available after the first test, but before a signal
	 * connection got established.
	 * NOTE: If need be, this function should also call `async_worker_timeout()'
	 *       with the appropriate realtime()-timeout for when the `awc_time()'
	 *       callback should be invoked. Also note that this has to be done
	 *       every time that this callback is invoked, as timeouts may either
	 *       only be maintained until the next time that the backing async-thread
	 *       restarts polling, and/or only exist on the basis of keeping track of
	 *       the timeout that will expire the earliest.
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: self:   [1..1] A reference to `ob_pointer' passed when the object was registered.
	 * @return: true:  Work is available, and the `awc_work()'-callback should be invoked.
	 * @return: false: No work available at the moment. */
	NONNULL((1, 2)) bool (ASYNC_CALLBACK_CC *awc_poll)(void *__restrict self,
	                                                   void *__restrict cookie);

	/* [1..1] Work-callback.
	 * Perform async work with all available data, returning
	 * once all work currently available has been completed.
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: self: [1..1] A reference to `ob_pointer' passed when the object was registered. */
	NONNULL((1)) void (ASYNC_CALLBACK_CC *awc_work)(void *__restrict self);

	/* [0..1] Test-callback.
	 * Prototype for test-async-work-available
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: self:   [1..1] A reference to `ob_pointer' passed when the object was registered.
	 * @return: true:  Work is available, and the `awc_work()'-callback should be invoked.
	 * @return: false: No work available at the moment. */
	NONNULL((1)) bool (ASYNC_CALLBACK_CC *awc_test)(void *__restrict self);
};

struct timespec;
/* Called after a timeout set during `awc_poll()' has expired. */
typedef NONNULL((1)) void (ASYNC_CALLBACK_CC *async_worker_timeout_t)(void *__restrict self);

/* This function may be called by `awc_poll()'-callbacks to
 * specify the realtime() timestamp when `on_timeout()' should
 * be invoked. The given `cookie' must be the same argument
 * prviously passed to `awc_poll()'
 * NOTE: After this function got called, `awc_poll()' should return
 *       `false', as the timeout may not come into effect otherwise. */
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(ASYNC_CALLBACK_CC async_worker_timeout)(struct timespec const *__restrict abs_timeout,
                                                void *__restrict cookie,
                                                async_worker_timeout_t on_timeout);


/* Register an async worker callback.
 * NOTE: All callbacks should be non-blocking in that they mustn't wait for
 *       work to become available themself (that's what `poll()' is for, such
 *       that a single thread can wait for async work to become available for
 *       _all_ async workers)
 * @param: cb:         Callbacks for the async worker being registered.
 *                     NOTE: The backing storage of the `cb' container itself
 *                           doesn't need to be persistent! It only needs to
 *                           remain valid until this function returns!
 * @param: ob_pointer: A pointer to a handle data object. The destructor of this
 *                     object is responsible for invoking `unregister_async_worker()'
 *                     Callbacks will no longer be invoked if this object's
 *                     reference counter has reached 0, however the object's
 *                     destructor must still unregister the callbacks before
 *                     the memory used to back its reference counter is free()d!
 * @param: ob_type:    The object type for `ob_pointer' (one of `HANDLE_TYPE_*')
 * @return: true:      Successfully registered a new async worker.
 * @return: false:     An async worker for the given object/callback combination
 *                     was already registered. */
FUNDEF NONNULL((1, 2)) bool KCALL
register_async_worker(struct async_worker_callbacks const *__restrict cb,
                      void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC);

/* Delete a previously defined async worker, using the same arguments as those
 * previously passed to `register_async_worker()'. This function should be
 * called from the destructor of `ob_pointer'
 * @param: cb:     Callbacks for the async worker being unregistered.
 *                 NOTE: The backing storage of the `cb' container itself
 *                       doesn't need to be persistent! It only needs to
 *                       remain valid until this function returns!
 * @return: true:  Successfully deleted an async worker for the
 *                 given object/callback combination.
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

/* A pointer to the `self' argument of async jobs. */
struct async_job;
typedef struct async_job *async_job_t;
struct aio_handle_stat;

/* Async jobs are similar to async workers, however are designed as
 * one-time jobs that delete themself once they've been completed.
 * NOTE: async job callbacks are inherently thread-safe:
 *   - aj_fini() is the last function that may ever be called, and
 *     will only be invoked _after_ any other callback has already
 *     returned.
 *   - Only one of `jc_poll()', `jc_work()', `jc_time()' and `jc_cancel()'
 *     may ever be called at the same time. (i.e. no synchronization is
 *     necessary between these callbacks)
 *   - Only `jc_progress()' and `jc_retsize()' might be called from the
 *     outside of the async-job, however since these callbacks are meant
 *     to perform read-only operations, they should also be inherently
 *     thread-safe, since they aren't meant to modify the state of an
 *     async-job (though if done right, even that would be allowed and
 *     possible) (also note that `jc_retsize()' is only called after
 *     the job had already been deleted/canceled)
 */
struct async_job_callbacks {
	size_t         jc_jobsize;  /* Size of the structure pointed-to by the `self' arguments used by callbacks. */
	size_t         jc_jobalign; /* Alignment requirements of the structure pointed-to by the `self' arguments used by callbacks. */
	struct driver *jc_driver;   /* [1..1] The driver implementing the callbacks. */

	/* [0..1] Finalizer for `self' */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/ (ASYNC_CALLBACK_CC *aj_fini)(async_job_t self);

	/* [1..1] Poll-callback. Behaves similar to the one for async workers.
	 * If this function returns with an exception, the job will also be deleted.
	 * @param: timeout: [out] Must be filled in with a realtime() timestamp when `false' is
	 *                        returned. Once this point in time has elapsed, the `jc_time()'
	 *                        callback is invoked.
	 *                        NOTE: This argument only has meaning when `ASYNC_JOB_POLL_WAITFOR'
	 *                              is returned.
	 * @return: * : One of `ASYNC_JOB_POLL_*' */
	NONNULL((1, 2)) unsigned int (ASYNC_CALLBACK_CC *jc_poll)(async_job_t self, struct timespec *__restrict timeout);

	/* [1..1] Perform the work associated with this async-job.
	 * If this function returns with an exception, the job will also be deleted.
	 * @return: true:  Work is still incomplete, and the caller should call `jc_poll()' next
	 *                 until that function returns `true' before calling this function again. 
	 * @return: false: Work has been completed, and the async-job should delete itself.
	 *                 In this case, the caller will unlink the async-job and invoke `aj_fini'*/
	NONNULL((1)) bool (ASYNC_CALLBACK_CC *jc_work)(async_job_t self);

	/* [?..1] Callback that is invoked when the timeout filled in by `jc_poll()' has elapsed.
	 *        This callback only has to be [valid] when `jc_poll()' is able to return `ASYNC_JOB_POLL_WAITFOR'.
	 *        If that callback only ever returns `ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT', then this callback
	 *        doesn't need to be filled in.
	 * If this function returns with an exception, the job will also be deleted.
	 * @return: true:  Same as with `jc_work': don't delete the job.
	 * @return: false: Same as with `jc_work': delete the job. */
	NONNULL((1)) bool (ASYNC_CALLBACK_CC *jc_time)(async_job_t self);

	/* [0..1] Optional callback that is invoked when the job is explicitly canceled (s.a. `async_job_cancel()').
	 *  NOTE: When this callback is invoked, it is guarantied that none of this job's
	 *        other callbacks are being executed at the same time. This is done by
	 *        having `async_job_cancel()' change the job's internal state to indicate
	 *        that the job is being canceled, which then causes the backing async
	 *        worker to then invoke this callback.
	 * If this function returns with an exception, that error will be discarded,
	 * and the job will be deleted none-the-less. */
	NONNULL((1)) void (ASYNC_CALLBACK_CC *jc_cancel)(async_job_t self);

	/* [0..1] Optional callback to facilitate the `ht_progress' operation of AIO handles.
	 * WARNING: This callback may be called at the same time as one of the callbacks! */
	NOBLOCK NONNULL((1)) unsigned int
	/*NOTHROW*/ (ASYNC_CALLBACK_CC *jc_progress)(async_job_t self, struct aio_handle_stat *__restrict stat);

	/* [0..1] Optional callback to facilitate the `ht_retsize' operation of AIO handles.
	 * NOTE: This callback will only be called after the handle's callback has completed,
	 *       and the async job has already been, or is currently pending deletion. */
	NOBLOCK NONNULL((1)) size_t
	/*NOTHROW*/ (ASYNC_CALLBACK_CC *jc_retsize)(async_job_t self);
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

DEFINE_REFCOUNT_FUNCTIONS_EX(struct async_job, async_job_refcnt, async_job_destroy)

/* Allocate and return a new async-job with the given callbacks.
 * Note that this job hasn't been started yet, which is something
 * that will only be done once the caller invokes `async_job_start()'
 * If the job should be free()'d before that point, `async_job_free()' should be used.
 * Afterwards, the job should be considered as reference-counted, with the caller
 * of `async_job_start()' being responsible to inherit a reference to the job.
 * NOTE: The returned pointer itself points at a user-defined structure of
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

/* Start the given async job, and optionally connect a given AIO handle
 * for process monitoring, job completion notification, and cancellation:
 *   - `aio_handle_cancel()' can be used to the same effect as `async_job_cancel()'
 *   - `aio->ah_func' will be invoked under the following conditions
 *     after `async_job_start()' had been called to start the async job,
 *     just after the job has been deleted:
 *     - AIO_COMPLETION_SUCCESS:
 *       - `jc_poll()' returning `ASYNC_JOB_POLL_DELETE'
 *       - `jc_work()' returning `false'
 *       - `jc_time()' returning `false'
 *     - AIO_COMPLETION_CANCEL:
 *       - `aio_handle_cancel()' has been called
 *       - `async_job_cancel()' has been called
 *     - AIO_COMPLETION_FAILURE:
 *       - `jc_poll()' returned with an exception
 *       - `jc_work()' returned with an exception
 *       - `jc_time()' returned with an exception
 * @return: * : Always re-returns `self' */
FUNDEF NOBLOCK NONNULL((1)) REF async_job_t
NOTHROW(FCALL async_job_start)(async_job_t self,
                               /*out,opt*/ struct aio_handle *aio DFL(__NULLPTR));

/* Cancel a given job.
 * This function can be used to prevent future invocation of the given job's functions.
 * WARNING: Job cancellation also happens asynchronously (except for in regards to
 *          the `AIO_COMPLETION_CANCEL' completion status of a possibly connected AIO
 *          handle), meaning that even after this function returns, the job may continue
 *          to exist for a while longer before eventually being deleted! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_cancel)(async_job_t self);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H */
