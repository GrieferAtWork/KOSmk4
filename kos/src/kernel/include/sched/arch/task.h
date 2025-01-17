/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ARCH_TASK_H
#define GUARD_KERNEL_INCLUDE_SCHED_ARCH_TASK_H 1

#include <kernel/compiler.h>

DECL_BEGIN


#ifdef __CC__
typedef int pflag_t;
#define PREEMPTION_ENABLED_VALUE               1
#define PREEMPTION_DISABLED_VALUE              0
#define task_pause()                     (void)0
#define PREEMPTION_ENABLE()              (void)0
#define PREEMPTION_ENABLE_WAIT()         (void)0
#define PREEMPTION_ENABLE_WAIT_DISABLE() (void)0
#define PREEMPTION_ENABLE_P()            (void)0
#define PREEMPTION_DISABLE()             (void)0
#define PREEMPTION_ENABLED()                   0
#define PREEMPTION_PUSHOFF()                   0
#define PREEMPTION_WASENABLED(flag)            0
#define PREEMPTION_WAIT()                XBLOCK({ for (;;) {} })
#define PREEMPTION_HALT()                XBLOCK({ for (;;) {} })
#define PREEMPTION_POP(flag)             (void)0
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ARCH_TASK_H */
