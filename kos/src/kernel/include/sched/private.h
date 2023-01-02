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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PRIVATE_H
#define GUARD_KERNEL_INCLUDE_SCHED_PRIVATE_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

struct task;

typedef NOBLOCK NONNULL_T((2)) void
NOTHROW_T(FCALL *cpu_private_function_t)(void *buf, struct task *__restrict thread);

/* Call a given `func' in a context such that thread-private variables of `thread'
 * can be read, and following variable-specific restrictions, may potentially also
 * be writable.
 * This is done by ensuring that `func' is run:
 *  - While preemption is disabled
 *  - From some arbitrary  thread hosted by  `thread->t_cpu' at  the
 *    time that `func' is invoked (which is guarantied to not change
 *    because preemption is disabled)
 *    WARNING: When `func' is called, there is a possibility
 *             that `thread == THIS_TASK'
 * If `thread' is hosted by a different CPU, an IPI will be scheduled for execution
 * on said CPU. It is the allocation of a reference-counted control structure  that
 * has  to be shared with the target CPU in this scenario that may potentially fail
 * due to an allocation  failure. Note that this  control structure is required  to
 * safely handle the case of the original thread getting interrupted such that this
 * function will return by throwing an `E_INTERRUPT' exception.
 * This function is most useful for accessing private registers caches of  `thread'
 * from an arbitrary, different thread, such as the x86-specific `x86_get_irregs()'
 * @param: thread:    The thread who's private variables the caller wishes to access.
 * @param: func:      The function used to access `thread's private variables.
 * @param: stack_buf: A buffer of `bufsize'  bytes that is allocated  in the caller's kernel  stack.
 *                    This buffer is passed to `func()' when `thread' is hosted by the caller's CPU.
 *                    When  `thread'  is hosted  by  a different  CPU,  a reference  counted control
 *                    structure containing  sufficient space  for `bufsize'  is allocated  and  pre-
 *                    initialized with the contents of `stack_buf'.  Following this, an IPI is  used
 *                    to invoke `func' in the context  of `thread->t_cpu', whilst passing a  pointer
 *                    to  the memory-copy of this buffer to  `func()', before the return of `func()'
 *                    will cause the  original caller of  `cpu_call_private_function()' to wake  up,
 *                    at  which  the  same  pointer  previously  passed  to  `func()'  is  returned.
 *                    The caller must always clean up this pointer via a call to
 *                    `cpu_private_function_finibuf_ex()', which will free() a dynamically allocated
 *                    buffer, unless the buffer wasn't dynamically allocated.
 * @param: bufsize:   Size of `stack_buf'
 * @param: bufalign:  Alignment requirements of `stack_buf' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *KCALL
cpu_private_function_callbuf_ex(struct task *__restrict thread,
                                cpu_private_function_t func, void *stack_buf,
                                size_t bufsize, size_t bufalign)
		THROWS(E_BADALLOC, E_INTERRUPT);
#define cpu_private_function_call_ex(thread, func, bufptr)                     \
	((__typeof__(bufptr))cpu_private_function_callbuf_ex(thread, func, bufptr, \
	                                                     sizeof(*(bufptr)),    \
	                                                     COMPILER_ALIGNOF(*(bufptr))))


FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL __cpu_private_function_do_finibuf_ex)(void *used_buf)
		ASMNAME("cpu_private_function_do_finibuf_ex");

/* Cleanup the buffer returned by `cpu_call_private_function()'
 * @param: used_buf:  == cpu_private_function_callbuf_ex():return
 * @param: stack_buf: == cpu_private_function_callbuf_ex():stack_buf */
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL cpu_private_function_finibuf_ex)(void *used_buf,
                                               void *stack_buf) {
	if (used_buf != stack_buf)
		__cpu_private_function_do_finibuf_ex(used_buf);
}



/* Simplified variant of `cpu_private_function_callbuf_ex()':
 * >> cpu_private_function_call() {
 * >>     void *ptr;
 * >>     ptr = cpu_private_function_callbuf_ex(thread, func, stack_buf, bufsize, bufalign);
 * >>     if (ptr != stack_buf)
 * >>         memcpy(stack_buf, ptr, bufsize);
 * >>     cpu_private_function_finibuf_ex(ptr, stack_buf);
 * >> }
 */
FUNDEF NONNULL((1, 2)) void KCALL
cpu_private_function_callbuf(struct task *__restrict thread,
                             cpu_private_function_t func, void *stack_buf,
                             size_t bufsize, size_t bufalign)
		THROWS(E_BADALLOC, E_INTERRUPT);
#define cpu_private_function_call(thread, func, bufptr) \
	cpu_private_function_callbuf(thread, func, bufptr, sizeof(*(bufptr)), COMPILER_ALIGNOF(*(bufptr)))



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_CPU_H */
