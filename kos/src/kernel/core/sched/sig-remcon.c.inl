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
//#define DEFINE___sig_remcon
#define DEFINE___sig_remcon_nopr
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE___sig_remcon) + \
     defined(DEFINE___sig_remcon_nopr)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

#ifdef DEFINE___sig_remcon
#define LOCAL___sig_remcon __sig_remcon
#elif defined(DEFINE___sig_remcon_nopr)
#define LOCAL___sig_remcon __sig_remcon_nopr
#define LOCAL_IS_NOPR
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#include <kernel/compiler.h>

#include <kernel/panic.h>
#include <kernel/printk.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <stdint.h>

DECL_BEGIN

#ifdef LOCAL_IS_NOPR
#define LOCAL_NOPREEMPT NOPREEMPT
#else /* LOCAL_IS_NOPR */
#define LOCAL_NOPREEMPT /* nothing */
#endif /* !LOCAL_IS_NOPR */

#ifdef LOCAL_IS_NOPR
#define LOCAL_task_yield() task_pause()
#define LOCAL_sig_send(s)  sig_send_nopr(s)
#else /* LOCAL_IS_NOPR */
#define LOCAL_task_yield() task_tryyield_or_pause()
#define LOCAL_sig_send(s)  sig_send(s)
#endif /* !LOCAL_IS_NOPR */


PUBLIC NOBLOCK LOCAL_NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL LOCAL___sig_remcon)(struct sigcon *__restrict self,
                                  unsigned int flags) {
	uintptr_t stat;
	struct sigcon *sigctl;
	struct sig *from = self->sc_sig;
#ifndef LOCAL_IS_NOPR
	preemption_flag_t was;
#else /* !LOCAL_IS_NOPR */
	assert(!preemption_ison() || kernel_poisoned());
#endif /* LOCAL_IS_NOPR */

again:
	stat = atomic_read(&self->sc_stat);
	if (SIGCON_STAT_ISDEAD(stat)) {
handle_dead_connection:
		/* Signal  was already sent -> possibly forward, but
		 * no need to remove (because that was already done) */
		if (stat == SIGCON_STAT_ST_THRSENT && (flags & __SIG_REMCON_F_FORWARD)) {
			struct sig *target = self->sc_sig;
			if (!LOCAL_sig_send(target)) {
#ifdef CONFIG_SIG_DEBUG_NAMES
				char const *name = sig_getname(target);
				if (name && ADDR_ISKERN(name) && pagedir_ismapped(name)) {
					printk(KERN_WARNING "[sig] Signal %q@%p cannot be forwarded (no recipients)\n",
					       name, target);
				} else
#endif /* CONFIG_SIG_DEBUG_NAMES */
				{
					printk(KERN_WARNING "[sig] Signal %p cannot be forwarded (no recipients)\n",
					       target);
				}
			}
		}
		DBG_memset(&self->sc_sig, 0xcc, sizeof(self->sc_sig));
		return;
	}

	from   = self->sc_sig;
	sigctl = atomic_read(&from->s_con);
	assertf((uintptr_t)sigctl != (0 | SIG_SMPLOCK),
	        "SIG_SMPLOCK must not appear without connections");
	if unlikely((uintptr_t)sigctl == 0) {
		/* Race condition: another thread *just* sent this signal, and only *just* unlocked
		 * the  signal, but did so *after* our  first check regarding the connection state.
		 *
		 * This can only happen when the connection is *now* dead. */
		stat = atomic_read(&self->sc_stat);
		assertf(SIGCON_STAT_ISDEAD(stat),
		        "Signal has no more connections, but our connection isn't dead?");
		goto handle_dead_connection;
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
	if unlikely(!atomic_cmpxch_weak(&from->s_con, sigctl,
	                                (struct sigcon *)((uintptr_t)sigctl | SIG_SMPLOCK))) {
#ifndef LOCAL_IS_NOPR
		preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
		goto again;
	}
#endif /* SIG_SMPLOCK */
	sigcon_verify_ring_beforeremove(sigctl);

	if (sigctl == self) {
		/* Special case: first connection is being removed while still connected. */
		struct sigcon *prev, *next;
		assert(!SIGCON_STAT_ISDEAD(self->sc_stat));
		prev = self->sc_prev;
		next = self->sc_next;
		assert(next->sc_prev == self);
		assert(prev->sc_next == self);
		assert((next == self) == (prev == self));
		DBG_memset(&self->sc_prev, 0xcc, sizeof(self->sc_prev));
		DBG_memset(&self->sc_next, 0xcc, sizeof(self->sc_next));
		if (next == self) {
			/* Double-special case: last connection is being removed */
			next = NULL;
		} else {
			next->sc_prev = prev;
			prev->sc_next = next;
			sigcon_verify_ring_afterremove(next);
		}
		atomic_write(&from->s_con, next); /* Also releases SMP-lock */
	} else {
		struct sigcon *prev, *next;

		/* Must check again if the connection has died since we checked above. */
		stat = atomic_read(&self->sc_stat);
		if (SIGCON_STAT_ISDEAD(stat)) {
			sigcon_verify_ring_afterremove(sigctl);
#ifdef SIG_SMPLOCK
			atomic_write(&from->s_con, sigctl); /* Release SMP-lock */
#endif /* SIG_SMPLOCK */
#ifndef LOCAL_IS_NOPR
			preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
			goto handle_dead_connection;
		}

		/* Remove some random connection (that is not the first in-queue) */
		assert(!SIGCON_STAT_ISDEAD(self->sc_stat));
		assert(self->sc_next->sc_prev == self);
		assert(self->sc_prev->sc_next == self);
		assert(self->sc_next != self);
		assert(self->sc_prev != self);
		prev = self->sc_prev;
		next = self->sc_next;
		DBG_memset(&self->sc_prev, 0xcc, sizeof(self->sc_prev));
		DBG_memset(&self->sc_next, 0xcc, sizeof(self->sc_next));
		next->sc_prev = prev;
		prev->sc_next = next;
		sigcon_verify_ring_afterremove(sigctl);
#ifdef SIG_SMPLOCK
		atomic_write(&from->s_con, sigctl); /* Release SMP-lock */
#endif /* SIG_SMPLOCK */
	}

#ifndef LOCAL_IS_NOPR
	preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
	DBG_memset(&self->sc_sig, 0xcc, sizeof(self->sc_sig));
}

#undef LOCAL_sig_send
#undef LOCAL_task_yield
#undef LOCAL_NOPREEMPT

DECL_END

#undef LOCAL___sig_remcon
#undef LOCAL_IS_NOPR

#undef DEFINE___sig_remcon_nopr
#undef DEFINE___sig_remcon
