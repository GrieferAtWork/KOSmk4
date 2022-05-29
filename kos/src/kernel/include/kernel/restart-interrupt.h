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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RESTART_INTERRUPT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RESTART_INTERRUPT_H 1

#include <kernel/compiler.h>

#include <kernel/arch/restart-interrupt.h>

#ifndef KERNEL_INTERRUPT_CALLBACK_CC
#define KERNEL_INTERRUPT_CALLBACK_CC FCALL
#endif /* !KERNEL_INTERRUPT_CALLBACK_CC */

#ifdef __CC__
DECL_BEGIN

/* Callback prototype for `kernel_restart_interrupt()' */
#ifndef __kernel_interrupt_callback_t_defined
#define __kernel_interrupt_callback_t_defined
typedef ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
(KERNEL_INTERRUPT_CALLBACK_CC *kernel_interrupt_callback_t)(struct icpustate *__restrict state);
#endif /* !__kernel_interrupt_callback_t_defined */

/* Hard-set the current stack depth to `state' and invoke `cb()' by passing `state' to it.
 * Once  `cb()' returns, the cpu state returned by it is loaded, and execution is resumed.
 * WARNING: When this function is called, the caller's stack is _NOT_ unwound until `state'
 *          is reached. - No TRY-EXCEPT/FINALLY blocks or destructors are invoked, and this
 *          function does  not  return  in  any  way that  is  observable  to  the  caller.
 *          Rather,  it behaves similar to `longjmp()', in that `cb()' is made to return to
 *          the origin of `state' after being injected ontop of that location. */
#ifndef __kernel_restart_interrupt_defined
#define __kernel_restart_interrupt_defined
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void
NOTHROW(KERNEL_INTERRUPT_CALLBACK_CC kernel_restart_interrupt)(struct icpustate *__restrict state,
                                                               kernel_interrupt_callback_t cb);
#endif /* !__kernel_restart_interrupt_defined */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RESTART_INTERRUPT_H */
