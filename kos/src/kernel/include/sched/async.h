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
	 * @param: arg:    [1..1] A reference to `ob_pointer' passed when the object was registered.
	 * @return: true:  Work is available, and the `awc_work()'-callback should be invoked.
	 * @return: false: No work available at the moment. */
	NONNULL((1, 2)) bool (ASYNC_CALLBACK_CC *awc_poll)(void *__restrict arg,
	                                                   void *__restrict cookie);

	/* [1..1] Work-callback.
	 * Perform async work with all available data, returning
	 * once all work currently available has been completed.
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: arg: [1..1] A reference to `ob_pointer' passed when the object was registered. */
	NONNULL((1)) void (ASYNC_CALLBACK_CC *awc_work)(void *__restrict arg);

	/* [0..1] Test-callback.
	 * Prototype for test-async-work-available
	 * NOTE: Exceptions thrown by this function are logged and silently discarded
	 * @param: arg:    [1..1] A reference to `ob_pointer' passed when the object was registered.
	 * @return: true:  Work is available, and the `awc_work()'-callback should be invoked.
	 * @return: false: No work available at the moment. */
	NONNULL((1)) bool (ASYNC_CALLBACK_CC *awc_test)(void *__restrict arg);
};

struct timespec;
/* Called after a timeout set during `awc_poll()' has expired. */
typedef NONNULL((1)) void (ASYNC_CALLBACK_CC *async_worker_timeout_t)(void *__restrict arg);

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



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H */
