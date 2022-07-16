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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_TRACE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_TRACE_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kos/kernel/handle.h>

/*[[[config CONFIG_HAVE_KERNEL_SYSCALL_TRACING = true]]]*/
#ifdef CONFIG_NO_KERNEL_SYSCALL_TRACING
#undef CONFIG_HAVE_KERNEL_SYSCALL_TRACING
#elif !defined(CONFIG_HAVE_KERNEL_SYSCALL_TRACING)
#define CONFIG_HAVE_KERNEL_SYSCALL_TRACING
#elif (-CONFIG_HAVE_KERNEL_SYSCALL_TRACING - 1) == -1
#undef CONFIG_HAVE_KERNEL_SYSCALL_TRACING
#define CONFIG_NO_KERNEL_SYSCALL_TRACING
#endif /* ... */
/*[[[end]]]*/

#ifdef __CC__
DECL_BEGIN

#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
/* Low-level, arch-specific enable/disable system call tracing.
 * NOTE: Don't   call   `arch_syscall_tracing_setenabled()'    directly.
 *       Low-level system call tracing is enabled/disabled automatically
 *       when tracing callbacks are  installed/deleted as the result  of
 *       calls to  `syscall_trace_start()'  and  `syscall_trace_stop()'.
 *       Manually enabling/disable tracing will work, however attempting
 *       to  start/stop  tracing  via  installation  of  dynamic tracing
 *       callbacks may break, since those  functions may only call  this
 *       one when the first callback is registered, or the last callback
 *       is deleted.
 * NOTE: A user can manually invoke this function from the builtin debugger
 *       through use of the `sctrace 0|1' command.
 * @param: nx:     When true, don't throw an exception or block.
 * @return: true:  Successfully changed the current tracing state.
 * @return: false: Tracing was already enabled/disabled, or could
 *                 not  be  enabled/disabled  when  `nx == true'. */
FUNDEF bool (KCALL arch_syscall_tracing_setenabled)(bool enable, bool nx);

/* Check if system call tracing is enabled. */
FUNDEF WUNUSED bool NOTHROW(KCALL arch_syscall_tracing_getenabled)(void);

struct rpc_syscall_info;

/* Trace a given system call.
 * This  function is called  at the start  of any user-level system
 * call   so-long   as  `arch_syscall_tracing_getenabled() == true'
 * Custom system call invocation mechanisms that directly call into
 * the underlying system call tables, rather than going through the
 * provided `syscall_emulate()' family  of functions must  manually
 * invoke this callback */
FUNDEF NONNULL((1)) void FCALL
syscall_trace(struct rpc_syscall_info const *__restrict info);


/* Prototype for dynamically defined system call tracing callbacks.
 * @param: self: A temporary  reference  to  the  object  registered
 *               in `syscall_trace_start()' alongside this callback. */
typedef NONNULL_T((1, 2)) void
(FCALL *syscall_trace_callback_t)(void *__restrict self,
                                  struct rpc_syscall_info const *__restrict info);
#define _SYSCALL_TRACE_CALLBACK_T(name, Tself) \
	void (FCALL *name)(Tself *__restrict self, struct rpc_syscall_info const *__restrict info)

/* Start/stop the  tracing of  system  calls by  installing/deleting  callbacks
 * that are invoked for every system call invoked after `syscall_trace_start()'
 * returns, and before `syscall_trace_stop()' returns.
 * NOTE: The internal structures related to these functions don't keep a permanent
 *       reference to the given `ob_pointer'  object, meaning that so-long as  you
 *       make sure to call `syscall_trace_stop()' from the object's finalizer, you
 *       can safely use these functions with arbitrary kernel objects.
 * @param: cb:         The callback to-be invoked when a system call is performed.
 * @param: ob_pointer: A pointer to an object of type `ob_type'
 * @param: ob_type:    One of `HANDLE_TYPE_*' that describes the type of object that `ob_pointer' is.
 * @return: true:      Successfully registered/deleted the given callback/object pair.
 * @return: false:     The same callback/object pair was already registered/was never registered at all. */
FUNDEF NONNULL((1, 2)) __BOOL FCALL
syscall_trace_start(syscall_trace_callback_t cb,
                    void *__restrict ob_pointer,
                    uintptr_half_t ob_type);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL syscall_trace_stop)(syscall_trace_callback_t cb,
                                  void *__restrict ob_pointer,
                                  uintptr_half_t ob_type);


/* C++ helper overloads. */
#ifdef __cplusplus
#define _ASYNC_WORKER_CXX_FWD_STRUCT(HT, T) T;
HANDLE_FOREACH_CUSTOMTYPE(_ASYNC_WORKER_CXX_FWD_STRUCT)
#undef _ASYNC_WORKER_CXX_FWD_STRUCT
extern "C++" {
#define _ASYNC_WORKER_CXX_DECLARE(HT, T)                                          \
	LOCAL NONNULL((1, 2)) __BOOL FCALL                                            \
	syscall_trace_start(_SYSCALL_TRACE_CALLBACK_T(cb, T),                         \
	                    T *__restrict ob_pointer) {                               \
		return syscall_trace_start((syscall_trace_callback_t)cb, ob_pointer, HT); \
	}                                                                             \
	LOCAL NONNULL((1, 2)) __BOOL                                                  \
	NOTHROW(FCALL syscall_trace_stop)(_SYSCALL_TRACE_CALLBACK_T(cb, T),           \
	                                  T *__restrict ob_pointer) {                 \
		return syscall_trace_stop((syscall_trace_callback_t)cb, ob_pointer, HT);  \
	}
HANDLE_FOREACH_CUSTOMTYPE(_ASYNC_WORKER_CXX_DECLARE)
#undef _ASYNC_WORKER_CXX_DECLARE
} /* extern "C++" */
#endif /* __cplusplus */

#else /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */
#define arch_syscall_tracing_setenabled(enable) 0
#define arch_syscall_tracing_getenabled()       0
#define syscall_trace(info)                     (void)0
#define syscall_trace_start(...)                0
#define syscall_trace_stop(...)                 0
#endif /* CONFIG_NO_KERNEL_SYSCALL_TRACING */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_TRACE_H */
