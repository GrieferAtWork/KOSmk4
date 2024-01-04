/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HYBRID_SCHED_SIGNAL_H
#define _KOS_HYBRID_SCHED_SIGNAL_H 1

/* A hybrid compatibility header for writing code that work both in user-space,
 * as well as in kernel-space with the functionality to access the intersection
 * of signal-functionality possible on both ends */

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#ifdef __KERNEL__
#include <sched/sig.h>
#else /* __KERNEL__ */
#include <kos/futex.h>
#endif /* !__KERNEL__ */

__DECL_BEGIN

#ifdef __CC__

#ifdef __KERNEL__
typedef struct sig sched_signal_t;
#define SCHED_SIGNAL_INIT SIG_INIT
#else /* __KERNEL__ */
typedef lfutex_t sched_signal_t;
#define SCHED_SIGNAL_INIT 0
#endif /* !__KERNEL__ */

#ifdef __INTELLISENSE__

/* Initialize a given signal */
void sched_signal_init(sched_signal_t *__self);

/* Initialize an already zero-initialized signal */
void sched_signal_cinit(sched_signal_t *__self);

/* Broadcast a signal, waking all threads waiting on it. */
__SIZE_TYPE__ sched_signal_broadcast(sched_signal_t *__self);
__SIZE_TYPE__ sched_signal_broadcast_for_fini(sched_signal_t *__self);

/* Wake a single thread waiting on the given signal. */
__BOOL sched_signal_send(sched_signal_t *__self);

/* Wake a single thread waiting on the given signal. */
__SIZE_TYPE__ sched_signal_sendmany(sched_signal_t *__self, __SIZE_TYPE__ __max_count);

#ifdef __KERNEL__
#define sched_signal_connect          task_connect
#define sched_signal_connect_for_poll task_connect_for_poll
#endif /* __KERNEL__ */
#elif defined(__KERNEL__)

#define sched_signal_init               sig_init
#define sched_signal_cinit              sig_cinit
#define sched_signal_broadcast          sig_broadcast
#define sched_signal_broadcast_for_fini sig_broadcast_for_fini
#define sched_signal_send               sig_send
#define sched_signal_sendmany           sig_sendmany
#define sched_signal_connect            task_connect
#define sched_signal_connect_for_poll   task_connect_for_poll

#else /* __KERNEL__ */

#define sched_signal_init(self)  (*(self) = 0)
#define sched_signal_cinit(self) (__hybrid_assert(*(self) == 0))

#ifdef __CRT_HAVE_futexlock_wakeall
#define sched_signal_broadcast          futexlock_wakeall
#define sched_signal_broadcast_for_fini futexlock_wakeall
#else /* __CRT_HAVE_futexlock_wakeall */
#define sched_signal_broadcast(self)          __hybrid_assertion_failed("Missing CRT feature: __CRT_HAVE_futexlock_wakeall")
#define sched_signal_broadcast_for_fini(self) __hybrid_assertion_failed("Missing CRT feature: __CRT_HAVE_futexlock_wakeall")
#endif /* !__CRT_HAVE_futexlock_wakeall */

#ifdef __CRT_HAVE_futexlock_wake
#define sched_signal_send(self)                futexlock_wake(self, 1)
#define sched_signal_sendmany(self, max_count) futexlock_wake(self, max_count)
#else /* __CRT_HAVE_futexlock_wake */
#define sched_signal_send(self)                __hybrid_assertion_failed("Missing CRT feature: __CRT_HAVE_futexlock_wake")
#define sched_signal_sendmany(self, max_count) __hybrid_assertion_failed("Missing CRT feature: __CRT_HAVE_futexlock_wake")
#endif /* !__CRT_HAVE_futexlock_wake */

#endif /* !__KERNEL__ */

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_HYBRID_SCHED_SIGNAL_H */
