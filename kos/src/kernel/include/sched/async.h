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

/* Async callback prototype. */
typedef bool (FCALL *async_callback_t)(void *arg);


/* Register an async worker callback.
 * NOTE: All callbacks should be non-blocking in that they mustn't wait for
 *       work to become available themself (that's what `poll()' is for, such
 *       that a single thread can wait for async work to become available for
 *       _all_ async workers)
 * @param: test: [0..1] Check if work is available right now, returning `true'
 *                      if this is the case and `work()' should be invoked.
 *                      `arg' is a temporary reference to `ob_pointer:ob_type'
 *                      This callback is optional.
 * @param: poll: [1..1] Do the equivalent of test()+connect()+test() for work
 *                      being available, returning `true' if this is the case.
 *                      `arg' is a temporary reference to `ob_pointer:ob_type'
 * @param: work: [1..1] Perform the actual work, but don't block if no work is
 *                      available. Returns `true' if work was performed, but
 *                      returns `false' if no work was available. This callback
 *                      should be written with the assumption that work being
 *                      available is highly likely.
 * @param: ob_pointer:  A pointer to a handle data object. The destructor of this
 *                      object is responsible for invoking `unregister_async_worker()'
 *                      Callbacks will no longer be invoked if this object's
 *                      reference counter has reached 0, however the object's
 *                      destructor must still unregister the callbacks before
 *                      the memory used to back its reference counter is free()d!
 * @param: ob_type:     The object type for `ob_pointer' (one of `HANDLE_TYPE_*')
 */
FUNDEF NONNULL((2, 3, 4)) void KCALL
register_async_worker(async_callback_t test,
                      async_callback_t poll,
                      async_callback_t work,
                      void *ob_pointer,
                      uintptr_half_t ob_type)
		THROWS(E_BADALLOC);

/* Delete a previously defined async worker, using the same arguments as those
 * previously passed to `register_async_worker()'. This function should be
 * called from the destructor of `ob_pointer' */
FUNDEF NOBLOCK NONNULL((2, 3, 4)) void
NOTHROW(KCALL unregister_async_worker)(async_callback_t test,
                                       async_callback_t poll,
                                       async_callback_t work,
                                       void *ob_pointer,
                                       uintptr_half_t ob_type);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ASYNC_H */
