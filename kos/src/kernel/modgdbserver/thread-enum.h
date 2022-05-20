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
#ifndef GUARD_MODGDBSERVER_THREAD_ENUM_H
#define GUARD_MODGDBSERVER_THREAD_ENUM_H 1

#include <kernel/compiler.h>

#include <sched/cpu.h>

#include "gdb.h"

DECL_BEGIN

typedef NONNULL_T((2)) ssize_t
NOTHROW_T(FCALL *PTHREAD_ENUM_CALLBACK)(void *arg, struct task *__restrict thread);

/* Enumerate thread that are:
 *  - In EVERY_CPU->c_running
 *  - In EVERY_CPU->c_sleeping
 *  - In EVERY_CPU->c_pending
 *  - In FORCPU(EVERY_CPU, thiscpu_idle)
 * @return: >= 0: The total sum of return values of `callback'
 * @return: <  0: The first negative return value of `callback' */
INTDEF ssize_t NOTHROW(FCALL GDBThread_Enumerate)(PTHREAD_ENUM_CALLBACK callback, void *arg);

/* Return the nth, system-wide thread, or NULL if `nth' is out-of-bounds */
INTDEF REF struct task *NOTHROW(FCALL GDBThread_GetNth)(size_t nth);

DECL_END

#endif /* !GUARD_MODGDBSERVER_THREAD_ENUM_H */
