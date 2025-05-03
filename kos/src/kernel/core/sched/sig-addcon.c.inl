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
#ifdef __INTELLISENSE__
#include "sig.c"
//#define DEFINE___sig_addcon
#define DEFINE___sig_addcon_nopr
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE___sig_addcon) + \
     defined(DEFINE___sig_addcon_nopr)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

#ifdef DEFINE___sig_addcon
#define LOCAL___sig_addcon __sig_addcon
#elif defined(DEFINE___sig_addcon_nopr)
#define LOCAL___sig_addcon __sig_addcon_nopr
#define LOCAL_IS_NOPR
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#include <kernel/compiler.h>

#include <kernel/panic.h>
#include <sched/sig.h>

#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <atomic.h>

DECL_BEGIN

#ifdef LOCAL_IS_NOPR
#define LOCAL_NOPREEMPT NOPREEMPT
#else /* LOCAL_IS_NOPR */
#define LOCAL_NOPREEMPT /* nothing */
#endif /* !LOCAL_IS_NOPR */

#ifdef LOCAL_IS_NOPR
#define LOCAL_task_yield() task_pause()
#else /* LOCAL_IS_NOPR */
#define LOCAL_task_yield() task_tryyield_or_pause()
#endif /* !LOCAL_IS_NOPR */


PUBLIC NOBLOCK LOCAL_NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL LOCAL___sig_addcon)(struct sigcon *__restrict self) {
	struct sigcon *sigctl;
	struct sig *to = self->sc_sig;
#ifndef LOCAL_IS_NOPR
	preemption_flag_t was;
#else /* !LOCAL_IS_NOPR */
	assert(!preemption_ison() || kernel_poisoned());
#endif /* LOCAL_IS_NOPR */
#ifdef SIG_SMPLOCK
again:
#endif /* SIG_SMPLOCK */

	sigctl = atomic_read(&to->s_con);
#ifdef SIG_SMPLOCK
	assertf((uintptr_t)sigctl != (0 | SIG_SMPLOCK),
	        "SIG_SMPLOCK must not appear without connections");
#endif /* SIG_SMPLOCK */
	if ((uintptr_t)sigctl == 0) {
		/* Special case: first connection (can be set-up completely atomically) */
		sigcon_link_self(self);
		sigcon_verify_ring_afterinsert(self);
		if (!atomic_cmpxch_weak(&to->s_con, NULL, self))
			goto again;
		return;
	}

#ifdef SIG_SMPLOCK
	if ((uintptr_t)sigctl & SIG_SMPLOCK) {
		LOCAL_task_yield();
		goto again;
	}
#endif /* SIG_SMPLOCK */

#ifndef LOCAL_IS_NOPR
	preemption_pushoff(&was);
#endif /* !LOCAL_IS_NOPR */

	/* Acquire SMP-lock */
#ifdef SIG_SMPLOCK
	if unlikely(!atomic_cmpxch_weak(&to->s_con, sigctl,
	                                (struct sigcon *)((uintptr_t)sigctl | SIG_SMPLOCK))) {
#ifndef LOCAL_IS_NOPR
		preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
		goto again;
	}
#endif /* SIG_SMPLOCK */

	/* Insert "self" before "sigctl" in the ring (thus placing it at the end of the queue) */
	sigcon_verify_ring_beforeinsert(sigctl);
	sigcon_link_insert_before(self, sigctl);
	sigcon_verify_ring_afterinsert(sigctl);
	atomic_write(&to->s_con, sigctl); /* Release SMP-lock */

#ifndef LOCAL_IS_NOPR
	preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
}

#undef LOCAL_task_yield
#undef LOCAL_NOPREEMPT

DECL_END

#undef LOCAL___sig_addcon
#undef LOCAL_IS_NOPR

#undef DEFINE___sig_addcon_nopr
#undef DEFINE___sig_addcon
