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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIG_C
#define GUARD_KERNEL_INCLUDE_SCHED_SIG_C 1
#define CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS 0
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/selftest.h>
#include <sched/sig.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <sched/pertask.h>
#include <sched/sigcomp.h>
#include <sched/task-clone.h> /* DEFINE_PERTASK_RELOCATION */
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sequence/list.h>

#include <kos/nopf.h>
#include <kos/types.h>

#include <alloca.h>
#include <atomic.h>
#include <stdint.h>

#if defined(__i386__) || defined(__x86_64__)
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/segment.h>
#endif /* __i386__ || __x86_64__ */

DECL_BEGIN

/* Assert that alignof of `struct taskcons' is working out. */
static_assert(alignof(struct taskcons) == ALIGNOF_TASKCONS_TASK);
static_assert(alignof(struct taskcons) >= SIGCON_CONS_MINALIGN);
static_assert(SIGCON_CONS_MINALIGN > (SIGCON_STAT_F_POLL));


/* Extra flags for `task_wake()' from `SIG_XSEND_F_*' */
#ifndef __DEEMON__
#if (SIG_XSEND_F_WAKE_WAITFOR == TASK_WAKE_FWAITFOR && \
     SIG_XSEND_F_WAKE_HIGHPRIO == TASK_WAKE_FHIGHPRIO)
#define take_wake_flags__from__sig_xsend_flags(flags) \
	((flags) & (SIG_XSEND_F_WAKE_WAITFOR | SIG_XSEND_F_WAKE_HIGHPRIO))
#else /* ... */
#define take_wake_flags__from__sig_xsend_flags(flags)                \
	(((flags) & SIG_XSEND_F_WAKE_WAITFOR ? TASK_WAKE_FWAITFOR : 0) | \
	 ((flags) & SIG_XSEND_F_WAKE_HIGHPRIO ? TASK_WAKE_FHIGHPRIO : 0))
#endif /* !... */
#endif /* !__DEEMON__ */


/* Helpers for managing the ring formed by "struct sigcon" objects. */
#define sigcon_link_self(self)       \
	(void)((self)->sc_prev = (self), \
	       (self)->sc_next = (self))
#define sigcon_link_insert_before(self, successor) \
	sigcon_rlink_insert_before(self, self, successor)
#define sigcon_rlink_insert_before(self_head, self_tail, successor) \
	(void)((self_tail)->sc_next = (successor),                      \
	       (self_head)->sc_prev = (successor)->sc_prev,             \
	       (successor)->sc_prev = (self_tail),                      \
	       (self_head)->sc_prev->sc_next = (self_head))

#if defined(NDEBUG) || defined(NDEBUG_SIG) || 1
#define sigcon_verify_ring_IS_NOOP
#define sigcon_verify_ring(head) (void)0
#else /* NDEBUG || NDEBUG_SIG */

/* Check if [head,tail] references "item" */
PRIVATE ATTR_PURE NONNULL((1, 2, 3)) bool
NOTHROW(FCALL ring_contains)(struct sigcon *head,
                             struct sigcon *tail,
                             struct sigcon *item) {
	struct sigcon *iter = head;
	for (;;) {
		if (iter == item)
			return true;
		if (iter == tail)
			break;
		iter = iter->sc_next;
	}
	return false;
}

PRIVATE ATTR_PURE ATTR_NOINLINE NONNULL((1)) void
NOTHROW(FCALL sigcon_verify_ring)(struct sigcon *__restrict head) {
	struct sigcon *prev = NULL;
	struct sigcon *iter = head;
	do {
		uintptr_t stat;
		assertf(iter, "Unexpected NULL-pointer in sigcon ring (prev: %p)", prev);
		assertf(iter->sc_prev->sc_next == iter,
		        "Bad prev->next pointer: %p != %p",
		        iter->sc_prev->sc_next, iter);
		assertf(iter->sc_next->sc_prev == iter,
		        "Bad next->prev pointer: %p != %p",
		        iter->sc_next->sc_prev, iter);

		stat = atomic_read_relaxed(&iter->sc_stat);
		assertf(SIGCON_STAT_ISCONNECTED(stat),
		        "sigcon %p has status %#Ix, which "
		        /**/ "indicates that it isn't connected",
		        iter, stat);

		/* Assert that the ring doesn't contain sub-rings:
		 *
		 *  [A] -> [B] -> [C] -> [D]
		 *                 ^      |
		 *  This isn't >>> |      v
		 *  allowed       [F] <- [E]
		 *
		 * If this fails:
		 * - "iter" is the "C"-node
		 * - "prev" is the "F"-node
		 * - "head" is the "A"-node
		 */
		assertf(!prev || !ring_contains(head, prev, iter),
		        "End of sigcon ring doesn't point back to head.\n"
		        "iter: %p\n"
		        "prev: %p\n"
		        "head: %p",
		        iter, prev, head);

		prev = iter;
	} while ((iter = iter->sc_next) != head);
}
#endif /* !NDEBUG && !NDEBUG_SIG */

/* Debug sigcon ring verification hooks */
#define sigcon_verify_ring_beforesend(head)   sigcon_verify_ring(head)
#define sigcon_verify_ring_duringsend(head)   sigcon_verify_ring(head)
#define sigcon_verify_ring_aftersend(head)    sigcon_verify_ring(head)
#define sigcon_verify_ring_beforeinsert(head) sigcon_verify_ring(head)
#define sigcon_verify_ring_afterinsert(head)  sigcon_verify_ring(head)
#define sigcon_verify_ring_beforeremove(head) sigcon_verify_ring(head)
#define sigcon_verify_ring_afterremove(head)  sigcon_verify_ring(head)
#define sigcon_verify_ring_beforecount(head)  sigcon_verify_ring(head)


/* Internal key used to chain threads that have to be destroyed. */
#define sig_destroylater_next(thread) KEY_task__next(thread)

/* Destroy a chain of tasks whose reference counters hit ZERO(0) */
LOCAL NOBLOCK void
NOTHROW(FCALL sig_destroylater_act)(struct task *destroy_later) {
	while unlikely(destroy_later) {
		struct task *next;
		next = sig_destroylater_next(destroy_later);
		destroy(destroy_later);
		destroy_later = next;
	}
}


struct sigpostcomp {
	struct sigpostcomp             *spc_next; /* [0..1] Next post-completion descriptor. */
	sigcomp_postcb_t                spc_cb;   /* [1..1] Post-completion callback to-be invoked. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, spc_buf); /* Buffer to-be passed to `spc_cb' */
};

#define sigpostcomp_alloc(bufsize) \
	((struct sigpostcomp *)alloca(offsetof(struct sigpostcomp, spc_buf) + (bufsize)))

/* @param: struct sigpostcomp           **ppost_completion_chain: ...
 * @param: struct sigcompcon             *sc:                     ...
 * @param: struct sigcompctx *context:                ... */
#define sigcomp_invoke(ppost_completion_chain, sc, context)        \
	do {                                                           \
		size_t _pc_reqlen;                                         \
		(context)->scc_post   = NULL;                              \
		(context)->scc_mode = SIGCOMP_MODE_F_NORMAL;               \
		_pc_reqlen = (*(sc)->scc_cb)(sc, context, NULL, 0);        \
		if (_pc_reqlen != 0 || (context)->scc_post != NULL) {      \
			struct sigpostcomp *_pc_ent;                           \
			for (;;) {                                             \
				size_t _pc_newlen;                                 \
				_pc_ent = sigpostcomp_alloc(_pc_reqlen);           \
				_pc_newlen = (*(sc)->scc_cb)(sc, context,          \
				                             _pc_ent->spc_buf,     \
				                             _pc_reqlen);          \
				if unlikely(_pc_newlen > _pc_reqlen) {             \
					_pc_reqlen = _pc_newlen;                       \
					continue;                                      \
				}                                                  \
				if unlikely((context)->scc_post == NULL)           \
					break;                                         \
				/* Finish fill in `_pc_ent' and enqueue it. */     \
				_pc_ent->spc_cb   = (context)->scc_post;           \
				_pc_ent->spc_next = *(ppost_completion_chain);     \
				*(ppost_completion_chain) = _pc_ent;               \
				break;                                             \
			}                                                      \
		}                                                          \
	}	__WHILE0




/* Trigger phase #2 for pending signal-completion functions.
 * NOTE: During this, the completion callback will clear the
 *       SMP  lock  bit  of its  own  completion controller. */
#define sig_run_phase_2(chain, context)                \
	do {                                               \
		for (; chain; chain = chain->spc_next)         \
			(*chain->spc_cb)(context, chain->spc_buf); \
	}	__WHILE0



/* Combine 2 rings "remainder" and "reprime" by returning whichever ring
 * is  non-NULL, or inserting  "reprime" at the  end of "remainder" when
 * both are non-NULL. */
PRIVATE WUNUSED struct sigcon *
NOTHROW(FCALL combine_remainder_and_reprime)(struct sigcon *remainder,
                                             struct sigcon *reprime) {
	struct sigcon *reprime_head;
	struct sigcon *reprime_tail;
	if (remainder == NULL)
		return reprime;
	if (reprime == NULL)
		return remainder;
	reprime_head = reprime;
	reprime_tail = reprime->sc_prev;
	assert(reprime_head->sc_prev->sc_next == reprime_head);
	assert(reprime_head->sc_next->sc_prev == reprime_head);
	assert(reprime_tail->sc_prev->sc_next == reprime_tail);
	assert(reprime_tail->sc_next->sc_prev == reprime_tail);
	assert(remainder->sc_prev->sc_next == remainder);
	assert(remainder->sc_next->sc_prev == remainder);

	/* Insert "[reprime_head,reprime_tail]" before "reprime" */
	sigcon_rlink_insert_before(reprime_head, reprime_tail, remainder);
	return remainder;
}



/* This call does everything needed to (in order):
 * - invoke phase#1 callback of "receiver"
 *   - if the callback indicates that that it wants to be re-primed, do so.
 *   - if the callback indicates that it can't receive the signal:
 *     - if it also re-primed itself, add "receiver" to an internal list
 *       of non-viable receivers that will always be skipped by the code
 *       used to search for receivers, as seen above.
 *     - Make use of a custom "sig_send" implementation that is skips
 *       non-viable receivers,  and inherits  the caller's  SMP-lock,
 *       preemption_flag_t, "caller", "cleanup", etc.. Once that call
 *       has completed, and  released all relevant  locks and so  on,
 *       return true/false indicative  of that  function having  been
 *       able to send the signal.
 * - If non-NULL, inject connections from "reprime" at the end of "self"
 * - release the SMP-lock from "self" by assigning `remainder`
 * - invoke "cleanup" callbacks (while preemption is still off)
 * - restore preemption as per "was"
 * - destroy receiver threads whose reference counters dropped to 0
 * - invoke phase#2 callback of "receiver"
 * - return true */
PRIVATE ATTR_NOINLINE NONNULL((1, 2, 3, 4, 5)) bool KCALL
sig_completion_invoke_and_unlock_and_preemption_pop(struct sig *self,
                                                    struct sig *sender,
                                                    struct sigcompcon *receiver,
                                                    struct sigcon *remainder,
                                                    struct task *caller,
                                                    struct sigcon *reprime,
                                                    struct sig_cleanup_callback *cleanup,
                                                    preemption_flag_t was,
                                                    unsigned int flags) {
	struct sigpostcomp *phase2 = NULL;
	struct sigcompctx context;
	assert(SIGCON_STAT_ISCONNECTED(atomic_read_relaxed(&receiver->sc_stat)));
	assert(SIGCON_STAT_ISCOMP(atomic_read_relaxed(&receiver->sc_stat)));

	/* Signal completion callback. */
	context.scc_sender = sender;
	context.scc_caller = caller;
	sigcomp_invoke(&phase2, receiver, &context);

	if (!(context.scc_mode & SIGCOMP_MODE_F_REPRIME) || (flags & SIG_XSEND_F_FINI)) {
		/* Release out ownership of "receiver" (if it wasn't reprimed) */
		atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRSENT);
	} else {
		/* Re-prime connection */
		if (reprime == NULL) {
			sigcon_link_self(receiver);
			reprime = receiver;
		} else {
			sigcon_link_insert_before(receiver, reprime);
		}
	}

	/* Deal with the case where the completion function didn't accept the signal. */
	if (context.scc_mode & SIGCOMP_MODE_F_NONVIABLE) {
		bool result;
		flags |= SIG_XSEND_F_LOCKED;
		flags &= ~SIG_XSEND_F_NOPR;
		if (!preemption_wason(&was))
			flags |= SIG_XSEND_F_NOPR;
#if defined(__OPTIMIZE__) && !defined(__OPTIMIZE_SIZE__)
		if (phase2 == NULL) /* So the compiler can generate a tail-call */
			return sig_xsend(self, flags, sender, caller, NULL, cleanup, reprime);
#endif /* __OPTIMIZE__ && !__OPTIMIZE_SIZE__ */
		result = sig_xsend(self, flags, sender, caller, NULL, cleanup, reprime);
		sig_run_phase_2(phase2, &context);
		return result;
	}

	/* Write-back the finalized, new ring of connections and release lock. */
	remainder = combine_remainder_and_reprime(remainder, reprime);
#ifndef sigcon_verify_ring_IS_NOOP
	if (remainder)
		sigcon_verify_ring_afterremove(remainder);
#endif /* !sigcon_verify_ring_IS_NOOP */
	atomic_write(&self->s_con, remainder); /* Release SMP-lock */
	if (cleanup)
		(*cleanup->scc_cb)(cleanup);
	preemption_pop(&was);
	sig_run_phase_2(phase2, &context);
	return true;
}

/* This call does everything needed to (in order):
 * - invoke phase#1 callback of "receiver"
 * - Resume a broadcast on "self" using the specified options
 * - invoke phase#2 callback of "receiver"
 * - return the number of non-poll receivers that were notified
 */
PRIVATE ATTR_NOINLINE NONNULL((1, 2, 3, 4, 5, 6, 8)) size_t KCALL
sig_completion_invoke_and_continue_broadcast(struct sig *self,
                                             struct sig *sender,
                                             struct sigcompcon *receiver,
                                             struct sigcon *remainder_head,
                                             struct sigcon *remainder_tail,
                                             struct sigcon *sigctl,
                                             size_t maxcount,
                                             struct task *caller,
                                             struct sigcon *reprime,
                                             struct sig_cleanup_callback *cleanup,
                                             struct task *destroy_later,
                                             preemption_flag_t was,
                                             unsigned int flags) {
	size_t result = 0;
	struct sigpostcomp *phase2 = NULL;
	struct sigcompctx context;
	uintptr_t stat = atomic_read_relaxed(&receiver->sc_stat);
	assert(SIGCON_STAT_ISCONNECTED(stat));
	assert(SIGCON_STAT_ISCOMP(stat));
	assert(maxcount > 0);

	/* Signal completion callback. */
	context.scc_sender = sender;
	context.scc_caller = caller;
	sigcomp_invoke(&phase2, receiver, &context);

	if (!(context.scc_mode & SIGCOMP_MODE_F_REPRIME) || (flags & SIG_XSEND_F_FINI)) {
		/* Release out ownership of "receiver" (if it wasn't reprimed) */
		atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST);
	} else {
		/* Re-prime connection */
		if (reprime == NULL) {
			sigcon_link_self(receiver);
			reprime = receiver;
		} else {
			sigcon_link_insert_before(receiver, reprime);
		}
	}

	/* Deal with the case where the completion function didn't accept the signal. */
	if (!(context.scc_mode & SIGCOMP_MODE_F_NONVIABLE) &&
	    !(stat & SIGCON_STAT_F_POLL))
		++result;

	if unlikely(remainder_head == sigctl) {
		/* Special case: the completion-callback was the last receiver
		 * -> nothing left to do but unlock the signal and exit. */
restore_reprime_and_unlock:
#ifndef sigcon_verify_ring_IS_NOOP
		if (reprime)
			sigcon_verify_ring_afterremove(reprime);
#endif /* !sigcon_verify_ring_IS_NOOP */
		atomic_write(&self->s_con, reprime);
		if (cleanup)
			(*cleanup->scc_cb)(cleanup);
		preemption_pop(&was);
		goto done;
	}

	/* Form a ring from the remainder. */
	remainder_tail->sc_next = remainder_head;
	remainder_head->sc_prev = remainder_tail;

	/* Check for special case: we're supposed to stop now. */
#ifndef __OPTIMIZE_SIZE__
	if unlikely(result >= maxcount) {
		reprime = combine_remainder_and_reprime(remainder_head, reprime);
		goto restore_reprime_and_unlock;
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Write-back remaining connections to the signal, and resume
	 * the  broadcast whilst having `sig_xsendmany()' inherit our
	 * lock-state. */
	sigcon_verify_ring_afterremove(remainder_head);
#ifdef SIG_SMPLOCK
	atomic_write(&self->s_con, (struct sigcon *)((uintptr_t)remainder_head | SIG_SMPLOCK));
#else /* SIG_SMPLOCK */
	atomic_write(&self->s_con, remainder_head);
#endif /* !SIG_SMPLOCK */

	flags |= SIG_XSEND_F_LOCKED;
	flags &= ~SIG_XSEND_F_NOPR;
	if (!preemption_wason(&was))
		flags |= SIG_XSEND_F_NOPR;
#if defined(__OPTIMIZE__) && !defined(__OPTIMIZE_SIZE__)
	if (result == 0 && phase2 == NULL) {
		/* So the compiler can generate a tail-call */
		return sig_xsendmany(self, maxcount, flags, sender,
		                     caller, cleanup, reprime, destroy_later);
	}
#endif /* __OPTIMIZE__ && !__OPTIMIZE_SIZE__ */
	maxcount -= result;
	result += sig_xsendmany(self, maxcount, flags, sender,
	                        caller, cleanup, reprime, destroy_later);
done:
	sig_run_phase_2(phase2, &context);
	return result;
}

#ifndef __INTELLISENSE__
DECL_END
/*[[[deemon (printSigCIncludes from "...include.sched.sig-config")();]]]*/
#define DEFINE_sig_xsend
#include "sig-send.c.inl"
#define DEFINE_sig_xsendmany
#include "sig-send.c.inl"
#ifndef __OPTIMIZE_SIZE__
#define DEFINE_sig_send
#include "sig-send.c.inl"
#define DEFINE_sig_send_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_sendmany
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast
#include "sig-send.c.inl"
#define DEFINE_sig_altbroadcast
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_altbroadcast_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast_for_fini
#include "sig-send.c.inl"
#else /* !__OPTIMIZE_SIZE__ */
DECL_BEGIN
PUBLIC NOBLOCK NONNULL((1)) bool NOTHROW(FCALL sig_send)(struct sig *__restrict self) {
	return sig_xsend(self, SIG_XSEND_F_NORMAL, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) bool NOTHROW(FCALL sig_send_nopr)(struct sig *__restrict self) {
	return sig_xsend(self, SIG_XSEND_F_NOPR, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_sendmany)(struct sig *__restrict self, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NORMAL, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_NORMAL, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_nopr)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_nopr)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_for_fini)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_FINI, NULL, THIS_TASK, NULL, NULL, NULL);
}
DECL_END
#endif /* __OPTIMIZE_SIZE__ */
PUBLIC NOBLOCK NONNULL((1, 2)) bool NOTHROW(FCALL sig_altsend)(struct sig *self, struct sig *sender) {
	return sig_xsend(self, SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) bool NOTHROW(FCALL sig_altsend_nopr)(struct sig *self, struct sig *sender) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) bool NOTHROW(FCALL sig_send_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP, NULL, THIS_TASK, NULL, cleanup, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_altsend_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, NULL, cleanup, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) bool NOTHROW(FCALL sig_sendas)(struct sig *__restrict self, struct task *__restrict caller) {
	return sig_xsend(self, SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_altsendas)(struct sig *self, struct sig *sender, struct task *__restrict caller) {
	return sig_xsend(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) bool NOTHROW(FCALL sig_sendas_nopr)(struct sig *__restrict self, struct task *__restrict caller) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_altsendas_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_sendas_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, NULL, caller, NULL, cleanup, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) bool NOTHROW(FCALL sig_altsendas_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, NULL, cleanup, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) bool NOTHROW(FCALL sig_sendto)(struct sig *__restrict self, struct task *__restrict target) {
	return sig_xsend(self, SIG_XSEND_F_TARGET, NULL, THIS_TASK, target, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_altsendto)(struct sig *self, struct sig *sender, struct task *__restrict target) {
	return sig_xsend(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET, sender, THIS_TASK, target, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) bool NOTHROW(FCALL sig_sendto_nopr)(struct sig *__restrict self, struct task *__restrict target) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET, NULL, THIS_TASK, target, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_altsendto_nopr)(struct sig *self, struct sig *sender, struct task *__restrict target) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET, sender, THIS_TASK, target, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_sendto_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict target, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, NULL, THIS_TASK, target, cleanup, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) bool NOTHROW(FCALL sig_altsendto_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict target, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, target, cleanup, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_sendasto)(struct sig *__restrict self, struct task *caller, struct task *target) {
	return sig_xsend(self, SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, NULL, caller, target, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2, 3, 4)) bool NOTHROW(FCALL sig_altsendasto)(struct sig *self, struct sig *sender, struct task *caller, struct task *target) {
	return sig_xsend(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, sender, caller, target, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) bool NOTHROW(FCALL sig_sendasto_nopr)(struct sig *__restrict self, struct task *caller, struct task *target) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, NULL, caller, target, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) bool NOTHROW(FCALL sig_altsendasto_nopr)(struct sig *self, struct sig *sender, struct task *caller, struct task *target) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, sender, caller, target, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) bool NOTHROW(FCALL sig_sendasto_cleanup_nopr)(struct sig *__restrict self, struct task *caller, struct task *target, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, NULL, caller, target, cleanup, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4, 5)) bool NOTHROW(FCALL sig_altsendasto_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *caller, struct task *target, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, sender, caller, target, cleanup, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altsendmany)(struct sig *self, struct sig *sender, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_sendmany_nopr)(struct sig *__restrict self, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altsendmany_nopr)(struct sig *self, struct sig *sender, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_sendmany_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP, NULL, THIS_TASK, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altsendmany_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_sendmanyas)(struct sig *__restrict self, struct task *__restrict caller, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altsendmanyas)(struct sig *self, struct sig *sender, struct task *__restrict caller, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_sendmanyas_nopr)(struct sig *__restrict self, struct task *__restrict caller, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altsendmanyas_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_sendmanyas_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, NULL, caller, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) size_t NOTHROW(FCALL sig_altsendmanyas_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_for_fini_nopr)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini_nopr)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcast_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP, NULL, THIS_TASK, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcast_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcast_for_fini_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CLEANUP, NULL, THIS_TASK, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas)(struct sig *__restrict self, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas)(struct sig *self, struct sig *sender, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas_nopr)(struct sig *__restrict self, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_broadcastas_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, NULL, caller, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) size_t NOTHROW(FCALL sig_altbroadcastas_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas_for_fini)(struct sig *__restrict self, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_FINI | SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas_for_fini)(struct sig *self, struct sig *sender, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas_for_fini_nopr)(struct sig *__restrict self, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CALLER, NULL, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas_for_fini_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_broadcastas_for_fini_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, NULL, caller, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) size_t NOTHROW(FCALL sig_altbroadcastas_for_fini_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, cleanup, NULL, NULL);
}
/*[[[end]]]*/
DECL_BEGIN
#endif /* !__INTELLISENSE__ */



/* Internal, low-level API for adding/removing a signal connection */
static_assert(__SIG_REMCON_F_NORMAL == _SIGCON_DISCONNECT_F_NORMAL);
static_assert(__SIG_REMCON_F_FORWARD == _SIGCON_DISCONNECT_F_FORWARD);

#ifndef __INTELLISENSE__
DECL_END
#define DEFINE___sig_addcon
#include "sig-addcon.c.inl"
#define DEFINE___sig_addcon_nopr
#include "sig-addcon.c.inl"
#define DEFINE___sig_remcon
#include "sig-remcon.c.inl"
#define DEFINE___sig_remcon_nopr
#include "sig-remcon.c.inl"
#define DEFINE_sig_numcon
#include "sig-numcon.c.inl"
#define DEFINE_sig_numcon_nopr
#include "sig-numcon.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */



/* Assert offsets */
static_assert(sizeof(struct sig) == SIZEOF_SIG);
static_assert(alignof(struct sig) == ALIGNOF_SIG);
static_assert(offsetof(struct sigcon, sc_sig) == OFFSET_SIGCON_SIG);
static_assert(offsetof(struct sigcon, sc_prev) == OFFSET_SIGCON_PREV);
static_assert(offsetof(struct sigcon, sc_next) == OFFSET_SIGCON_NEXT);
static_assert(offsetof(struct sigcon, sc_cons) == OFFSET_SIGCON_CONS);
static_assert(offsetof(struct sigcon, sc_stat) == OFFSET_SIGCON_STAT);
static_assert(sizeof(struct sigcon) == SIZEOF_SIGCON);
static_assert(alignof(struct sigcon) == ALIGNOF_SIGCON);
static_assert(offsetof(struct sigtaskcon, sct_thrnext) == OFFSET_SIGCON_TASK_THRNEXT);
static_assert(sizeof(struct sigtaskcon) == SIZEOF_SIGCON_TASK);
static_assert(alignof(struct sigtaskcon) == ALIGNOF_SIGCON_TASK);
static_assert(offsetof(struct taskcons, tcs_deliver) == OFFSET_TASKCONS_DELIVER);
static_assert(offsetof(struct taskcons, tcs_thread) == OFFSET_TASKCONS_THREAD);
static_assert(offsetof(struct taskcons, tcs_prev) == OFFSET_TASKCONS_PREV);
static_assert(offsetof(struct taskcons, tcs_cons) == OFFSET_TASKCONS_CONS);
static_assert(offsetof(struct taskcons, tcs_static) == OFFSET_TASKCONS_STATIC);
static_assert(sizeof(struct taskcons) == SIZEOF_TASKCONS);
static_assert(alignof(struct taskcons) == ALIGNOF_TASKCONS_TASK);

/* Root connections set. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct taskcons) this_rootcons = {
	.tcs_deliver = NULL,
	.tcs_thread  = NULL,
	.tcs_prev    = NULL,
	.tcs_cons    = SLIST_HEAD_INITIALIZER(this_rootcons.tcs_cons),
	.tcs_static  = {}
};

/* [1..1][lock(PRIVATE(THIS_TASK))] Current set of in-use  connections.
 * Most of the time, this will simply point to `PERTASK(this_rootcons)' */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct taskcons *) this_cons = &this_rootcons;

/* Define relocations */
DEFINE_PERTASK_RELOCATION(this_rootcons + OFFSET_TASKCONS_THREAD);
DEFINE_PERTASK_RELOCATION(this_cons);


INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_fix_taskcons)(struct task *__restrict self) {
	struct task *active_thread;
	struct taskcons *self_connections;
	self_connections = FORTASK(self, this_cons);
	if (!ADDR_ISKERN(self_connections))
		goto fixit;
	if (!IS_ALIGNED((uintptr_t)self_connections, alignof(struct taskcons)))
		goto fixit;
	if (memcpy_nopf(&active_thread, &self_connections->tcs_thread, sizeof(struct task *)) != 0)
		goto fixit;
	if (active_thread != self)
		goto fixit;
	return;
fixit:
	FORTASK(self, this_cons) = &FORTASK(self, this_rootcons);
	bzero(&FORTASK(self, this_rootcons), sizeof(struct taskcons));
	FORTASK(self, this_rootcons.tcs_thread) = self;
}


#if defined(__x86_64__) || defined(__i386__)
INTERN NOBLOCK ATTR_RETNONNULL struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void);
#endif /* __x86_64__ || __i386__ */

/* Push/pop the active set of connections:
 * >> DEFINE_SIG(a);
 * >> DEFINE_SIG(b);
 * >> struct taskcons cons;
 * >> task_connect(&a);
 * >> assert(task_isconnectedto(&a));
 * >> assert(!task_isconnectedto(&b));
 * >>
 * >> task_pushcons(&cons);
 * >> assert(!task_isconnectedto(&a));
 * >> assert(!task_isconnectedto(&b));
 * >>
 * >> task_connect(&b);
 * >> assert(!task_isconnectedto(&a));
 * >> assert(task_isconnectedto(&b));
 * >>
 * >> task_disconnectall();
 * >> assert(!task_isconnectedto(&a));
 * >> assert(!task_isconnectedto(&b));
 * >>
 * >> task_popcons();
 * >> assert(task_isconnectedto(&a));
 * >> assert(!task_isconnectedto(&b)); */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushcons)(struct taskcons *__restrict cons) {
	struct taskcons *oldcons;
	unsigned int i;
#ifdef NDEBUG
	oldcons = THIS_CONS;
#elif defined(__i386__) || defined(__x86_64__)
	struct task *mythread;
#ifdef __x86_64__
	mythread = (struct task *)__rdgsbaseq();
#else /* __x86_64__ */
	mythread = NULL;
	if likely(__rdfs() == SEGMENT_KERNEL_FSBASE) {
		struct desctab gdt;
		__sgdt(&gdt);
		if likely(gdt.dt_limit > SEGMENT_KERNEL_FSBASE) {
			struct segment *fsseg;
			fsseg    = (struct segment *)(gdt.dt_base + SEGMENT_KERNEL_FSBASE);
			mythread = (struct task *)segment_rdbaseX(fsseg);
		}
	}
#endif /* !__x86_64__ */
	if unlikely(!read_nopf(&FORTASK(mythread, this_cons), &oldcons)) {
		assertf(read_nopf(&FORTASK(mythread, this_cons), &oldcons),
		        "Corrupt TLS base pointer: mythread = %p", mythread);
		/* Allow the user to IGNORE the assertion check, in which case we'll
		 * try to repair the damage... */
		mythread = x86_repair_broken_tls_state();
		oldcons  = FORTASK(mythread, this_cons);
	}
#else /* ... */
	oldcons = THIS_CONS;
#endif /* !... */
	assertf(cons != oldcons,
	        "Connections set %p has already been pushed",
	        cons);
	cons->tcs_prev = oldcons;

	/* Disable async notifications for the old set of connections,
	 * and use the receiver thread for the new set of connections.
	 * Really, though: This should always just be `THIS_TASK' */
	cons->tcs_thread  = atomic_xch(&oldcons->tcs_thread, NULL);
	SLIST_INIT(&cons->tcs_cons); /* No connections in use (yet) */
	cons->tcs_deliver = NULL;    /* Nothing was delivered (yet) */
	DBG_memset(cons->tcs_static, 0xcc, sizeof(cons->tcs_static));

	/* Set-up statically allocated connections. */
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i)
		cons->tcs_static[i].sc_sig = NULL; /* Available for use. */

	/* Finally, set the active connection set to `cons' */
	PERTASK_SET(this_cons, cons);
}

PUBLIC NOBLOCK ATTR_RETNONNULL struct taskcons *
NOTHROW(FCALL task_popcons)(void) {
	struct taskcons *oldcons;
	struct taskcons *cons = THIS_CONS;
	assert((cons->tcs_prev == NULL) == (cons == THIS_ROOTCONS));
	assertf(cons != THIS_ROOTCONS,
	        "Cannot pop connections: Root connection set %p is already active",
	        cons);

	/* Make sure that no connections are left active. */
	assertf(SLIST_EMPTY(&cons->tcs_cons),
	        "Cannot call `task_popcons()' when you've still "
	        "got connections that haven't been disconnected, yet\n"
	        "call `task_disconnectall()' first!");

	/* Set the TLS pointer for the current set of connection to the old set. */
	oldcons = cons->tcs_prev;
	PERTASK_SET(this_cons, oldcons);

	/* Re-enable asynchronous notifications as the result of `sig_send()' / `sig_broadcast()' */
	atomic_write(&oldcons->tcs_thread, THIS_TASK);

	/* Make bad usage consistent by filling memory with garbage. */
	DBG_memset(cons, 0xcc, sizeof(*cons));

	return cons;
}





/* Allocate a new task connection. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct sigtaskcon *FCALL
taskcons_alloccon(struct taskcons *__restrict self) THROWS(E_BADALLOC) {
	unsigned int i;
	struct sigtaskcon *result;

	/* Check if one of the static slots is available. */
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i) {
		result = &self->tcs_static[i];
		if (!result->sc_sig)
			goto done;
	}

	/* Must dynamically allocate a new slot. */
	result = (struct sigtaskcon *)kmalloc(sizeof(struct sigtaskcon),
	                                       GFP_LOCKED | GFP_PREFLT);
done:
	return result;
}

/* Free a given task connection. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL taskcons_freecon)(struct taskcons *__restrict self,
                                struct sigtaskcon *__restrict con) {
	if (con >= self->tcs_static &&
	    con < COMPILER_ENDOF(self->tcs_static)) {
		/* Free a static connection. */
		DBG_memset(con, 0xaa, sizeof(*con)); /* Not-allocated */
		con->sc_sig = NULL;
	} else {
		/* Free a dynamically allocated connection. */
		kfree(con);
	}
}



/* @param: flags: Set of `0 | SIGCON_STAT_F_POLL' */
LOCAL NONNULL((1)) void FCALL
task_connect_impl(struct sig *__restrict target, uintptr_t flags)
		THROWS(E_BADALLOC) {
	struct taskcons *cons = THIS_CONS;
	struct sigtaskcon *con;
	assert(IS_ALIGNED((uintptr_t)cons, SIGCON_CONS_MINALIGN));

	/* When a signal was already delivered, `task_connect()'
	 * no  longer needs to  do anything and  can be a no-op. */
	if (atomic_read(&cons->tcs_deliver) != NULL)
		return;

	/* Allocate a new connection for `cons' */
	con = taskcons_alloccon(cons);
	con->sc_cons = (struct taskcons *)((uintptr_t)cons | flags);
	_sigcon_connect(con, target);

	/* Add connection to per-thread list. */
	SLIST_INSERT(&cons->tcs_cons, con, sct_thrnext);
}


/* Connect the calling thread to a given signal.
 * NOTE: If  the caller was already connected to `target', a second connection
 *       will be established, and `task_disconnect()' must be called more than
 *       once. However, aside  from this, having  multiple connections to  the
 *       same signal has no other adverse side-effects.
 * NOTE: When  the signal  test expression is  able to throw  an exception, the
 *       caller of this function is  responsible to disconnect from the  signal
 *       afterwards. However, exceptions that may be thrown by `task_waitfor()'
 *       always guaranty that _all_ established connections have been  removed.
 * >> if (test())
 * >>     return true;
 * >> task_connect(s);
 * >> TRY {
 * >>     if (test()) {
 * >>         task_disconnectall();
 * >>         return true;
 * >>     }
 * >> } EXCEPT {
 * >>     task_disconnectall();
 * >>     RETHROW();
 * >> }
 * >> task_waitfor();
 *
 * @throw: E_BADALLOC: Insufficient  memory  (only  when there  are  at least
 *                     `CONFIG_TASK_STATIC_CONNECTIONS' connections already). */
PUBLIC NONNULL((1)) void FCALL
task_connect(struct sig *__restrict target)
		THROWS(E_BADALLOC) {
	return task_connect_impl(target, 0);
}

/* Exactly the same as `task_connect()', however must be used when the connection
 * is  made for a poll-based operation that only wishes to wait for some event to
 * be  triggered, but does not wish to act upon this event by acquiring some kind
 * of lock with the intend to release  it eventually, where the act of  releasing
 * said lock includes a call to `sig_send()'.
 *
 * This connect() function is only required for signals that may be delivered  via
 * `sig_send()', meaning that only a single thread would be informed of the signal
 * event having taken place.  If in this scenario,  the recipient thread (i.e  the
 * thread  that called `task_connect()')  then decides not to  act upon the signal
 * in question, but rather do something else, the original intent of  `sig_send()'
 * will  become lost, that intent being for some (single) thread to try to acquire
 * an accompanying lock (for example: `<kos/sched/shared-lock.h>')
 *
 * As  far as semantics go, a signal  connection established with this function will
 * never satisfy a call to `sig_send()', and will instead be skipped if  encountered
 * during  its search for  a recipient (such that  by default, poll-connections will
 * only  be  acted upon  when  `sig_broadcast()' is  used).  However, if  a  call to
 * `sig_send()'  is unable to  find any non-poll-based  connections, it will proceed
 * to act like a call to `sig_broadcast()' and wake all polling threads, though will
 * still  end up  returning `false', indicative  of not having  woken any (non-poll)
 * waiting thread.
 *
 * With all of  this in  mind, this  function can  also be  though of  as a  sort-of
 * low-priority task connection, that will only be triggered after other connections
 * have already been served, and  will only be woken  by `sig_send()' when no  other
 * connections exist.
 *
 * In practice, this function must be used whenever it is unknown what will eventually
 * happen  after `task_waitfor()', or  if what happens  afterwards doesn't include the
 * acquisition  of some kind of lock, whose  release includes the sending of `target'.
 *
 * Note  however that `task_connect()' may still be used even if it is followed by
 * a call to `task_disconnect()' (or similar). If in this scenario the signal  had
 * already been send to the calling thread with `sig_send()' being the origin, the
 * signal is forwarded to  the next waiting  thread the same  way another call  to
 * `sig_send()'  would.  The only  slight problem  in this  situation is  that the
 * original call to `sig_send()' had already  returned `true', and if this  second
 * internal  call fails due to a lack of recipients, the initial true return value
 * was  incorrect since no thread ended up  actually receiving the signal. This is
 * not  something that can be fixed and as such should be kept in mind when making
 * decisions based on the return value of `sig_send()'.
 *
 * s.a. The difference between `task_disconnectall()' and `task_receiveall()' */
PUBLIC NONNULL((1)) void FCALL
task_connect_for_poll(struct sig *__restrict target)
		THROWS(E_BADALLOC) {
	return task_connect_impl(target, SIGCON_STAT_F_POLL);
}



/* Find and return a self-pointer to your thread's  connection
 * to `target'. If you are  not connected (or made an  attempt
 * to connect *after* having already received another signal),
 * this function returns `NULL'.
 * - Only searches the currently active set of connections,
 *   meaning this won't  find a signal  connected before  a
 *   call to `task_pushcons()'
 * - Only  connections that haven't been disconnected (via
 *   use of `task_disconnect()' or `task_disconnectall()')
 *   are returned.
 * - When connected to the same signal multiple times, this
 *   will return one at random.
 * - When `target' is an invalid pointer, return "NULL" */
PUBLIC NOBLOCK ATTR_PURE WUNUSED struct sigtaskcon **
NOTHROW(FCALL task_findcon_p)(struct sig const *target) {
	struct sigtaskcon **con_p;
	struct taskcons *cons = THIS_CONS;
	SLIST_P_FOREACH (con_p, &cons->tcs_cons, sct_thrnext) {
		if ((*con_p)->sc_sig == target)
			return con_p;
	}
	return NULL;
}


/* Disconnect from a specific signal `target'
 * WARNING: If `target' was already  send to the calling  thread
 *          before it could  be disconnected  by this  function,
 *          the calling  thread will  continue  to remain  in  a
 *          signaled state, such  that the next  call to one  of
 *          the signal receive functions (e.g. `task_waitfor()')
 *          will not block.
 * WARNING: Removing a specific signal is an O(N) operation, and
 *          in most cases you probably wans `task_disconnectall'
 * @return: true:  Disconnected from `target'
 * @return: false: You weren't actually  connected to  `target'.
 *                 Note that when a signal was already received,
 *                 `task_connect()'  becomes  a  no-op,  so  the
 *                 return value here can only be trusted for the
 *                 first connection made. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target) {
	struct sigtaskcon **con_p, *con;
	con_p = task_findcon_p(target);
	if (!con_p)
		return false;
	con = *con_p;
	_sigcon_disconnect(con, _SIGCON_DISCONNECT_F_FORWARD);
	SLIST_P_REMOVE(con_p, sct_thrnext);
	taskcons_freecon(THIS_CONS, con);
	return true;
}

/* Remove all established connections, but don't do anything beyond that.
 * @param: flags: Set of `_SIGCON_DISCONNECT_F_*' */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskcons_disconnectall)(struct taskcons *__restrict cons,
                                      unsigned int flags) {
	struct sigtaskcon *con;
	SLIST_FOREACH_SAFE (con, &cons->tcs_cons, sct_thrnext) {
		_sigcon_disconnect(con, flags);
		taskcons_freecon(cons, con);
	}
	SLIST_CLEAR(&cons->tcs_cons);
}


/* Disconnect from all connected signals.
 * Signals with a state of `SIGCON_STAT_ST_THRSENT' will be forwarded. */
PUBLIC NOBLOCK void
NOTHROW(FCALL task_disconnectall)(void) {
	struct taskcons *cons = THIS_CONS;
	taskcons_disconnectall(cons, _SIGCON_DISCONNECT_F_FORWARD);
	COMPILER_WRITE_BARRIER(); /* "tcs_deliver" must be written *after* disconnecting */
	cons->tcs_deliver = NULL;
}

/* Same as `task_disconnectall()', but don't forward signals with
 * a `SIGCON_STAT_ST_THRSENT'-state, but rather return the sender
 * of the signal that was received.
 * As such, the caller must properly pass on information about the
 * fact that a signal may have been received, as well as act  upon
 * this fact.
 *
 * As such, this function is more closely related to `task_trywait()'
 * than  `task_disconnectall()',  and implemented  to  atomically do:
 * >> struct sig *result;
 * >> result = task_trywait();
 * >> if (result == NULL)
 * >>     task_disconnectall(); // Nothing received --> still disconnect
 * >> return result;
 * @return: NULL: No signal was sent yet, and all connections were severed.
 * @return: * :   The received signal (for `sig_altsend', the "sender" argument) */
PUBLIC NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_receiveall)(void) {
	struct sig *result;
	struct taskcons *cons = THIS_CONS;
	taskcons_disconnectall(cons, _SIGCON_DISCONNECT_F_NORMAL);
	COMPILER_BARRIER(); /* "tcs_deliver" must be read *after* disconnecting */
	result = cons->tcs_deliver;
	cons->tcs_deliver = NULL;
	return result;
}


/* Check if the calling thread was connected to any  signal.
 * For this purpose, it doesn't matter if a connected signal
 * has  already been sent  or not (iow:  both alive and dead
 * connections will cause this function to return `true')
 *
 * As far as this function is concerned, a connection is only fully
 * released  once the calling thread has done one of the following:
 *  - Called `task_disconnect()' on every connected signal
 *  - Called `task_disconnectall()'
 *  - Called `task_receiveall()'
 *  - Called `task_trywait()'          (with a non-NULL return value)
 *  - Called `task_waitfor()'          (with a non-NULL return value)
 *  - Called `task_waitfor_nx()'       (with a non-NULL return value)
 *  - Called `task_waitfor_norpc()'    (with a non-NULL return value)
 *  - Called `task_waitfor_norpc_nx()' (with a non-NULL return value) */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL task_isconnected)(void) {
	struct taskcons *cons = THIS_CONS;
	return !SLIST_EMPTY(&cons->tcs_cons);
}


/* Check if there is a signal that was delivered,
 * disconnecting all other  connected signals  if
 * this was the case.
 * @return: NULL: No signal is available.
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
PUBLIC NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_trywait)(void) {
	struct taskcons *cons = THIS_CONS;
	struct sig *result = atomic_read(&cons->tcs_deliver);
	if (result) {
		COMPILER_READ_BARRIER();
		taskcons_disconnectall(cons, _SIGCON_DISCONNECT_F_NORMAL);
		COMPILER_WRITE_BARRIER();
		assert(result == cons->tcs_deliver);
		cons->tcs_deliver = NULL;
	}
	return result;
}




/************************************************************************/
/* SIGNAL MULTI-COMPLETION API                                          */
/************************************************************************/

#define _sigmulticomp_xtra_GFP (GFP_LOCKED | GFP_PREFLT)
#define _sigmulticomp_xtra_sizeof(n)                  \
	(offsetof(struct _sigmulticomp_xtra, smcx_cons) + \
	 ((n) * sizeof(struct _sigmulticompcon)))
#define _sigmulticomp_xtra_alloc(n) \
	(struct _sigmulticomp_xtra *)kmalloc(_sigmulticomp_xtra_sizeof(n), _sigmulticomp_xtra_GFP)
#define _sigmulticomp_xtra_alloc_nx(n) \
	(struct _sigmulticomp_xtra *)kmalloc_nx(_sigmulticomp_xtra_sizeof(n), _sigmulticomp_xtra_GFP)
#define _sigmulticomp_xtra_free(self) kfree(self)
#define _sigmulticomp_xtra_setusable(self)                                         \
	(void)((self)->smcx_alloc = (kmalloc_usable_size(self) -                       \
	                             offsetof(struct _sigmulticomp_xtra, smcx_cons)) / \
	                            sizeof(struct _sigmulticompcon))



/* Finalize a given signal multi-completion controller.
 * WARNING: This  function will _not_  disconnect any remaining signals.
 *          If active connections could possibly remain, it is up to the
 *          caller to call `sigmulticomp_disconnectall()' first! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigmulticomp_fini)(struct sigmulticomp *__restrict self) {
	/* Free all extended connection sets. */
	struct _sigmulticomp_xtra *xtra = self->smc_xtra;
	DBG_memset(&self->smc_xtra, 0xcc, sizeof(self->smc_xtra));
	while (xtra) {
		struct _sigmulticomp_xtra *next;
		next = xtra->smcx_next;
		_sigmulticomp_xtra_free(xtra);
		xtra = next;
	}
}

PRIVATE NOBLOCK ATTR_INOUTS(1, 2) void
NOTHROW(FCALL _sigmulticompcon_v_disconnectall)(struct _sigmulticompcon *v, size_t c) {
	size_t i;
	for (i = 0; i < c; ++i)
		sigcompcon_disconnect(&v[i]);
}

PRIVATE NOBLOCK NOPREEMPT ATTR_INOUTS(1, 2) void
NOTHROW(FCALL _sigmulticompcon_v_disconnectall_nopr)(struct _sigmulticompcon *v, size_t c) {
	size_t i;
	for (i = 0; i < c; ++i)
		sigcompcon_disconnect_nopr(&v[i]);
}

PRIVATE ATTR_RETNONNULL NOBLOCK NONNULL((1)) struct _sigmulticomp_xtra *
NOTHROW(FCALL _sigmulticomp_xtra_maybe_shrink_after_disconnect)(struct _sigmulticomp_xtra *__restrict self) {
	/* If more than half the connection slots are unused, shrink-to-fit */
	if (self->smcx_used < (self->smcx_alloc >> 1)) {
		struct _sigmulticomp_xtra *newbuf;
		size_t req = _sigmulticomp_xtra_sizeof(self->smcx_used);
		newbuf = (struct _sigmulticomp_xtra *)krealloc_nx(self, req, GFP_ATOMIC | _sigmulticomp_xtra_GFP);
		if (newbuf) {
			self = newbuf;
			_sigmulticomp_xtra_setusable(self);
		}
	}
	return self;
}

#define X_sigmulticomp_xtra_disconnectall(self) \
	(unlikely(*(self)) ? (void)(*(self) = _sigmulticomp_xtra_disconnectall(*(self))) : (void)0)
PRIVATE ATTR_RETNONNULL ATTR_NOINLINE NOBLOCK NONNULL((1)) struct _sigmulticomp_xtra *
NOTHROW(FCALL _sigmulticomp_xtra_disconnectall)(struct _sigmulticomp_xtra *__restrict self) {
	_sigmulticompcon_v_disconnectall(self->smcx_cons, self->smcx_used);
	if (self->smcx_next) {
		struct _sigmulticomp_xtra *next;
		next = self->smcx_next;
		self->smcx_next = NULL; /* Only keep the first (presumably largest) extension table. */
		if unlikely(next) {
			self = next;
			do {
				next = self->smcx_next;
				_sigmulticompcon_v_disconnectall(self->smcx_cons, self->smcx_used);
				_sigmulticomp_xtra_free(self);
			} while ((self = next) != NULL);
		} else {
			self = _sigmulticomp_xtra_maybe_shrink_after_disconnect(self);
		}
	}
	self->smcx_used = 0;
	return self;
}

#define X_sigmulticomp_xtra_disconnectall_nopr(self) \
	(unlikely(*(self)) ? (void)(*(self) = _sigmulticomp_xtra_disconnectall_nopr(*(self))) : (void)0)
PRIVATE ATTR_RETNONNULL ATTR_NOINLINE NOBLOCK NOPREEMPT NONNULL((1)) struct _sigmulticomp_xtra *
NOTHROW(FCALL _sigmulticomp_xtra_disconnectall_nopr)(struct _sigmulticomp_xtra *__restrict self) {
	_sigmulticompcon_v_disconnectall_nopr(self->smcx_cons, self->smcx_used);
	if (self->smcx_next) {
		struct _sigmulticomp_xtra *next;
		next = self->smcx_next;
		self->smcx_next = NULL; /* Only keep the first (presumably largest) extension table. */
		if unlikely(next) {
			self = next;
			do {
				next = self->smcx_next;
				_sigmulticompcon_v_disconnectall_nopr(self->smcx_cons, self->smcx_used);
				_sigmulticomp_xtra_free(self);
			} while ((self = next) != NULL);
		} else {
			self = _sigmulticomp_xtra_maybe_shrink_after_disconnect(self);
		}
	}
	self->smcx_used = 0;
	return self;
}

/* Serve all (still-alive) connections that are active for `self'. Note that this  function
 * may not be called from inside of signal-completion-callbacks, or any other callback that
 * may  be executed in the context of holding an SMP-lock. (though you area allowed to call
 * this function from a `sigcomp_postcb_t' callback) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _sigmulticomp_disconnectallN)(struct sigmulticomp *__restrict self,
                                            size_t n_static) {
	size_t i;
	for (i = 0; i < n_static; ++i) {
		struct _sigmulticompcon *con = &self->smc_cons[i];
		if (__sigmulticompcon_smc_cons_inuse(con)) {
			sigcompcon_disconnect(con);
			__sigmulticompcon_smc_cons_setunused(con);
		} else {
			/* Allocation  happens  0->N, so  the  first unused
			 * slot means everything thereafter is also unused! */
			break;
		}
	}
	X_sigmulticomp_xtra_disconnectall(&self->smc_xtra);
}

PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL _sigmulticomp_disconnectall_noprN)(struct sigmulticomp *__restrict self,
                                                 size_t n_static) {
	size_t i;
	for (i = 0; i < n_static; ++i) {
		struct _sigmulticompcon *con = &self->smc_cons[i];
		if (__sigmulticompcon_smc_cons_inuse(con)) {
			sigcompcon_disconnect_nopr(con);
			__sigmulticompcon_smc_cons_setunused(con);
		} else {
			/* Allocation  happens  0->N, so  the  first unused
			 * slot means everything thereafter is also unused! */
			break;
		}
	}
	X_sigmulticomp_xtra_disconnectall_nopr(&self->smc_xtra);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _sigmulticomp_disconnectall1)(struct sigmulticomp *__restrict self) {
#ifdef __OPTIMIZE_SIZE__
	_sigmulticomp_disconnectallN(self, 1);
#else /* __OPTIMIZE_SIZE__ */
	if (__sigmulticompcon_smc_cons_inuse(&self->smc_cons[0])) {
		sigcompcon_disconnect(&self->smc_cons[0]);
		__sigmulticompcon_smc_cons_setunused(&self->smc_cons[0]);
	}
	X_sigmulticomp_xtra_disconnectall(&self->smc_xtra);
#endif /* !__OPTIMIZE_SIZE__ */
}

PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL _sigmulticomp_disconnectall_nopr1)(struct sigmulticomp *__restrict self) {
#ifdef __OPTIMIZE_SIZE__
	_sigmulticomp_disconnectall_noprN(self, 1);
#else /* __OPTIMIZE_SIZE__ */
	if (__sigmulticompcon_smc_cons_inuse(&self->smc_cons[0])) {
		sigcompcon_disconnect_nopr(&self->smc_cons[0]);
		__sigmulticompcon_smc_cons_setunused(&self->smc_cons[0]);
	}
	X_sigmulticomp_xtra_disconnectall_nopr(&self->smc_xtra);
#endif /* !__OPTIMIZE_SIZE__ */
}




#define X_sigmulticomp_xtra_isconnected(self) \
	(unlikely(self) ? _sigmulticomp_xtra_isconnected(self) : false)
PRIVATE ATTR_NOINLINE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL _sigmulticomp_xtra_isconnected)(struct _sigmulticomp_xtra *__restrict self) {
#if 1
	/* Because disconnecting always frees all  but the first extension  table,
	 * we  also know that all but the first  must be fully in-use. As such, we
	 * can assume that in the presence of a second extension table, that table
	 * *must* contain at least 1 connection! */
	if (self->smcx_next)
		return true;
	return self->smcx_used > 0;
#else
	do {
		if (self->smcx_used > 0)
			return true;
	} while ((self = self->smcx_next) != NULL);
	return false;
#endif
}

/* Check if the given signal multi-completion controller `self'
 * is connected to  any signal  (iow: if there  are any  in-use
 * connections present). */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL _sigmulticomp_isconnectedM)(struct sigmulticomp const *__restrict self, size_t n_static) {
	size_t i;
	for (i = 0; i < n_static; ++i) {
		if (__sigmulticompcon_smc_cons_inuse(&self->smc_cons[i]))
			return true;
	}
	return X_sigmulticomp_xtra_isconnected(self->smc_xtra);
}

FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL _sigmulticomp_isconnected1)(struct sigmulticomp const *__restrict self) {
#ifdef __OPTIMIZE_SIZE__
	return _sigmulticomp_isconnectedM(self, 1);
#else /* __OPTIMIZE_SIZE__ */
	if (__sigmulticompcon_smc_cons_inuse(&self->smc_cons[0]))
		return true;
	return X_sigmulticomp_xtra_isconnected(self->smc_xtra);
#endif /* !__OPTIMIZE_SIZE__ */
}



/*[[[config CONFIG_SIGMULTICOMP_XTRA_STARTSIZE! = 4
 * Initial # of dynamically allocated connections the first
 * time a `struct _sigmulticomp_xtra' is allocated.
 * ]]]*/
#ifndef CONFIG_SIGMULTICOMP_XTRA_STARTSIZE
#define CONFIG_SIGMULTICOMP_XTRA_STARTSIZE 4
#endif /* !CONFIG_SIGMULTICOMP_XTRA_STARTSIZE */
/*[[[end]]]*/


/* Allocate+initialize a new signal completion descriptor that is
 * attached to the signal multi-completion controller `self', and
 * will invoke `cb' when triggered. The returned pointer is owned
 * by `self', meaning that the caller doesn't have to bother with
 * ownership  themself. The returned connection must be connected
 * to a signal using `sigcompcon_connect()'.
 *
 * If all of that sounds too complicated for you, then just use
 * `sigmulticomp_connect',  which  encapsulates   the  job   of
 * allocating+connecting to a signal for you. */

PRIVATE ATTR_NOINLINE NONNULL((1, 2)) struct sigcompcon *FCALL
sigmulticomp_alloccon_xtra(struct sigmulticomp *__restrict self,
                           sigcomp_cb_t cb, bool nx)
		THROWS(E_BADALLOC) {
	struct _sigmulticompcon *result;
	struct _sigmulticomp_xtra *xtra = self->smc_xtra;
	if unlikely(!xtra) {
		xtra = _sigmulticomp_xtra_alloc_nx(CONFIG_SIGMULTICOMP_XTRA_STARTSIZE);
		if unlikely(!xtra) {
			xtra = _sigmulticomp_xtra_alloc_nx(1);
			if unlikely(!xtra) {
				if (nx)
					return NULL;
				xtra = _sigmulticomp_xtra_alloc(1);
			}
		}
		_sigmulticomp_xtra_setusable(xtra);
		assert(xtra->smcx_alloc >= 1);
		xtra->smcx_used = 0;
		xtra->smcx_next = NULL;
		self->smc_xtra = xtra;
	} else if unlikely(xtra->smcx_used >= xtra->smcx_alloc) {
		/* Allocate another table. */
		struct _sigmulticomp_xtra *next;
		size_t next_sz = xtra->smcx_used << 1;
		assert(next_sz > xtra->smcx_used);
		next = _sigmulticomp_xtra_alloc_nx(next_sz);
		if unlikely(!next) {
			next_sz = xtra->smcx_used + 1;
			next = _sigmulticomp_xtra_alloc_nx(next_sz);
			if unlikely(!next) {
				if (nx)
					return NULL;
				next = _sigmulticomp_xtra_alloc(1);
			}
		}
		_sigmulticomp_xtra_setusable(next);
		assert(next->smcx_alloc >= 1);
		next->smcx_used = 0;
		next->smcx_next = xtra;
		self->smc_xtra = xtra = next;
	}
	assert(xtra->smcx_used < xtra->smcx_alloc);
	result = &xtra->smcx_cons[xtra->smcx_used];
	++xtra->smcx_used;
	_sigmulticompcon_init(result, self, cb);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct sigcompcon *FCALL
_sigmulticomp_allocconN(struct sigmulticomp *__restrict self,
                        sigcomp_cb_t cb, size_t n_static)
		THROWS(E_BADALLOC) {
	size_t i;
	for (i = 0; i < n_static; ++i) {
		struct _sigmulticompcon *con = &self->smc_cons[i];
		if (!__sigmulticompcon_smc_cons_inuse(con)) {
			_sigmulticompcon_init(con, self, cb);
			return con;
		}
	}
	return sigmulticomp_alloccon_xtra(self, cb, false);
}

PUBLIC WUNUSED NONNULL((1, 2)) struct sigcompcon *
NOTHROW(FCALL _sigmulticomp_alloccon_nxN)(struct sigmulticomp *__restrict self,
                                          sigcomp_cb_t cb, size_t n_static) {
	size_t i;
	for (i = 0; i < n_static; ++i) {
		struct _sigmulticompcon *con = &self->smc_cons[i];
		if (!__sigmulticompcon_smc_cons_inuse(con)) {
			_sigmulticompcon_init(con, self, cb);
			return con;
		}
	}
	return sigmulticomp_alloccon_xtra(self, cb, true);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct sigcompcon *FCALL
_sigmulticomp_alloccon1(struct sigmulticomp *__restrict self, sigcomp_cb_t cb)
		THROWS(E_BADALLOC) {
#ifdef __OPTIMIZE_SIZE__
	return _sigmulticomp_allocconN(self, cb, 1);
#else /* __OPTIMIZE_SIZE__ */
	if (!__sigmulticompcon_smc_cons_inuse(&self->smc_cons[0])) {
		_sigmulticompcon_init(&self->smc_cons[0], self, cb);
		return &self->smc_cons[0];
	}
	return sigmulticomp_alloccon_xtra(self, cb, false);
#endif /* !__OPTIMIZE_SIZE__ */
}

PUBLIC WUNUSED NONNULL((1, 2)) struct sigcompcon *
NOTHROW(FCALL _sigmulticomp_alloccon_nx1)(struct sigmulticomp *__restrict self,
                                          sigcomp_cb_t cb) {
#ifdef __OPTIMIZE_SIZE__
	return _sigmulticomp_alloccon_nxN(self, cb, 1);
#else /* __OPTIMIZE_SIZE__ */
	if (!__sigmulticompcon_smc_cons_inuse(&self->smc_cons[0])) {
		_sigmulticompcon_init(&self->smc_cons[0], self, cb);
		return &self->smc_cons[0];
	}
	return sigmulticomp_alloccon_xtra(self, cb, true);
#endif /* !__OPTIMIZE_SIZE__ */
}



/* Combination of `sigmulticomp_alloccon()' + `sigcompcon_connect()' */
PUBLIC NOBLOCK NONNULL((1, 2, 3)) void FCALL
_sigmulticomp_connect_ex1(struct sigmulticomp *__restrict self,
                          struct sig *__restrict target, sigcomp_cb_t cb,
                          uintptr_t flags)
		THROWS(E_BADALLOC) {
	struct sigcompcon *con = sigmulticomp_alloccon(self, cb);
	sigcompcon_connect_ex(con, target, flags);
}

PUBLIC NOBLOCK WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL _sigmulticomp_connect_ex_nx1)(struct sigmulticomp *__restrict self,
                                            struct sig *__restrict target, sigcomp_cb_t cb,
                                            uintptr_t flags) {
	struct sigcompcon *con = sigmulticomp_alloccon_nx(self, cb);
	if unlikely(!con)
		return false;
	sigcompcon_connect_ex(con, target, flags);
	return true;
}

PUBLIC NOBLOCK NONNULL((1, 2, 3)) void FCALL
_sigmulticomp_connect_exN(struct sigmulticomp *__restrict self,
                          struct sig *__restrict target, sigcomp_cb_t cb,
                          uintptr_t flags, size_t n_static)
		THROWS(E_BADALLOC) {
	struct sigcompcon *con = _sigmulticomp_allocconN(self, cb, n_static);
	sigcompcon_connect_ex(con, target, flags);
}

PUBLIC NOBLOCK WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL _sigmulticomp_connect_ex_nxN)(struct sigmulticomp *__restrict self,
                                            struct sig *__restrict target, sigcomp_cb_t cb,
                                            uintptr_t flags, size_t n_static) {
	struct sigcompcon *con = _sigmulticomp_alloccon_nxN(self, cb, n_static);
	if unlikely(!con)
		return false;
	sigcompcon_connect_ex(con, target, flags);
	return true;
}



/* Connect `self' to all signals currently connected to by the calling  thread.
 * In other words: all signals the caller is connected to via `task_connect()'.
 *
 * Note that for this purpose, only signals from the currently active set  of
 * task connections will  be connected. Connections  established outside  the
 * bounds  of the current  `task_pushcons()...task_popcons()' pair will _NOT_
 * be connected. If one of the signals which the calling thread is  connected
 * to has  already been  sent (i.e.  `task_waitfor()' wouldn't  block),  then
 * this function will return early, and the exact (if any) signals that  were
 * connected  to  `self'  are left  undefined  (meaning that  the  caller can
 * really only handle this happening by using `sigmulticomp_disconnectall()',
 * but also meaning that `cb'  may still get invoked  in case the caller  was
 * connected  to  more than  one  signal, and  more  than one  of  those gets
 * triggered before connections of `self' get disconnected).
 *
 * As such, the safe way to use this function is as follows
 * (exception  handling   not   displayed   for   brevity):
 * >> task_connect(&foo);
 * >> task_connect(&bar);
 * >> task_connect(&foobar);
 * >> ...
 * >> struct sigmulticomp smc;
 * >> sigmulticomp_init(&smc);
 * >> sigmulticomp_connect_from_task(&smc, &my_callback);
 * >> if (task_receiveall()) {  // Or `task_trywait()' if per-task
 * >>                           // connections should remain
 * >>     sigmulticomp_disconnectall(&smc);
 * >>     // Error:   One of the caller's signals may have already
 * >>     //          been delivered before `smc' could connect to
 * >>     //          all of them.
 * >> } else {
 * >>     // Success: Connections established (calling thread is no longer connected)
 * >> }
 *
 * This function is used to implement epoll objects using the regular,
 * old poll-api already exposed via `handle_poll()', without the  need
 * of complicating that existing ABI.
 *
 * @param: flags_mask: Set of `SIGCOMPCON_CONNECT_F_*' specifying which (if any)
 *                     mode flags to inherit from the original task  connections
 * @param: flags_set:  Set of `SIGCOMPCON_CONNECT_F_*' specifying which (if any)
 *                     mode flags to  add to the  `sigcompcon'-s being  created.
 */
PUBLIC NOBLOCK NONNULL((1)) void FCALL
_sigmulticomp_connect_from_taskN(struct sigmulticomp *__restrict self,
                                 sigcomp_cb_t cb,
                                 uintptr_t flags_mask,
                                 uintptr_t flags_set,
                                 size_t n_static)
		THROWS(E_BADALLOC) {
	struct sigtaskcon *iter;
	struct taskcons *cons = THIS_CONS;
	assert(flags_mask == SIGCOMPCON_CONNECT_F_NORMAL ||
	       flags_mask == SIGCOMPCON_CONNECT_F_POLL);
	assert(flags_set == SIGCOMPCON_CONNECT_F_NORMAL ||
	       flags_set == SIGCOMPCON_CONNECT_F_POLL);
#ifndef __OPTIMIZE_SIZE__
	if likely(flags_mask == 0) {
		/* Don't have to read "sc_stat" of every connection and cause bus contention */
		SLIST_FOREACH (iter, &cons->tcs_cons, sct_thrnext) {
			if unlikely(atomic_read(&cons->tcs_deliver) != NULL)
				break;
			_sigmulticomp_connect_exN(self, iter->sc_sig, cb, flags_set, n_static);
		}
		return;
	}
#endif /* !__OPTIMIZE_SIZE__ */
	SLIST_FOREACH (iter, &cons->tcs_cons, sct_thrnext) {
		uintptr_t flags;
#ifndef __OPTIMIZE_SIZE__
		if unlikely(atomic_read(&cons->tcs_deliver) != NULL)
			break; /* Connections will be incomplete anyways, so just stop prematurely. */
#endif /* !__OPTIMIZE_SIZE__ */
		flags = (atomic_read(&iter->sc_stat) & flags_mask) | flags_set;
		assert(flags == SIGCOMPCON_CONNECT_F_NORMAL ||
		       flags == SIGCOMPCON_CONNECT_F_POLL);
		_sigmulticomp_connect_exN(self, iter->sc_sig, cb, flags, n_static);
	}
}

PUBLIC NOBLOCK NONNULL((1)) void FCALL
_sigmulticomp_connect_from_task1(struct sigmulticomp *__restrict self,
                                 sigcomp_cb_t cb,
                                 uintptr_t flags_mask,
                                 uintptr_t flags_set)
		THROWS(E_BADALLOC) {
#ifndef __OPTIMIZE_SIZE__
	if likely(!__sigmulticompcon_smc_cons_inuse(&self->smc_cons[0])) {
		struct taskcons *cons = THIS_CONS;
		struct sigtaskcon *first = SLIST_FIRST(&cons->tcs_cons);
		if unlikely(!first)
			return;
		if (SLIST_NEXT(first, sct_thrnext) == NULL) {
			/* Simple case: thread only has 1 connection, and the singular,
			 * statically allocated slot of "self" isn't in use. -> Just do
			 * a regular connect! */
			uintptr_t flags = flags_mask ? ((atomic_read(&first->sc_stat) & flags_mask) | flags_set)
			                             : flags_set;
			assert(flags == SIGCOMPCON_CONNECT_F_NORMAL ||
			       flags == SIGCOMPCON_CONNECT_F_POLL);
			_sigmulticompcon_init(&self->smc_cons[0], self, cb);
			sigcompcon_connect_ex(&self->smc_cons[0], first->sc_sig, flags);
			return;
		}
	}
#endif /* !__OPTIMIZE_SIZE__ */
	_sigmulticomp_connect_from_taskN(self, cb, flags_mask, flags_set, 1);
}


DECL_END




#ifdef DEFINE_TEST
DECL_BEGIN


DEFINE_TEST(recursive_signals) {
	struct taskcons cons;
	DEFINE_SIG_NAMED(s, "kernel.selftest:recursive_signals:s");
	task_disconnectall();
	task_connect(&s);
	task_pushcons(&cons);
	task_connect(&s);

	assert(task_isconnected());
	assert(task_isconnectedto(&s));
	assert(task_trywait() == NULL);

	sig_broadcast(&s);

	/* Simulate what kfree() for the signal would do, thus
	 * ensuring  that  the signal  can still  be received,
	 * even after it was destroyed. */
	memset(&s, 0xcc, sizeof(s));

	assert(task_isconnected());
	assert(task_isconnectedto(&s));

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);

	assert(task_popcons() == &cons);

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);
}

DEFINE_TEST(broadcast_after_send) {
	DEFINE_SIG_NAMED(s, "kernel.selftest:broadcast_after_send:s");
	task_connect(&s);
	assert(sig_send(&s));
	assert(sig_broadcast(&s) == 0);
	task_disconnectall();
}

DEFINE_TEST(pushpop_connections) {
	DEFINE_SIG_NAMED(a, "kernel.selftest:pushpop_connections:a");
	DEFINE_SIG_NAMED(b, "kernel.selftest:pushpop_connections:b");
	struct taskcons cons;
	assert(!sig_hascon(&a) && sig_numcon(&a) == 0);
	assert(!sig_hascon(&b) && sig_numcon(&b) == 0);

	task_connect(&a);
	assert(task_isconnectedto(&a));
	assert(!task_isconnectedto(&b));
	assert(sig_hascon(&a) && sig_numcon(&a) == 1);
	assert(!sig_hascon(&b) && sig_numcon(&b) == 0);

	task_pushcons(&cons);
	assert(!task_isconnectedto(&a));
	assert(!task_isconnectedto(&b));
	assert(sig_hascon(&a) && sig_numcon(&a) == 1);
	assert(!sig_hascon(&b) && sig_numcon(&b) == 0);

	task_connect(&b);
	assert(!task_isconnectedto(&a));
	assert(task_isconnectedto(&b));
	assert(sig_hascon(&a) && sig_numcon(&a) == 1);
	assert(sig_hascon(&b) && sig_numcon(&b) == 1);

	task_disconnectall();
	assert(!task_isconnectedto(&a));
	assert(!task_isconnectedto(&b));
	assert(sig_hascon(&a) && sig_numcon(&a) == 1);
	assert(!sig_hascon(&b) && sig_numcon(&b) == 0);

	assert(task_popcons() == &cons);
	assert(task_isconnectedto(&a));
	assert(!task_isconnectedto(&b));
	assert(sig_hascon(&a) && sig_numcon(&a) == 1);
	assert(!sig_hascon(&b) && sig_numcon(&b) == 0);

	assert(task_disconnect(&a));
	assert(!task_isconnectedto(&a));
	assert(!task_isconnectedto(&b));
	assert(!task_isconnected());
	assert(!sig_hascon(&a) && sig_numcon(&a) == 0);
	assert(!sig_hascon(&b) && sig_numcon(&b) == 0);
}

#if CONFIG_TASK_STATIC_CONNECTIONS >= 3
#include <parts/assert-failed.h>
#include <kernel/printk.h>
#include <stdio.h>

#define FAIL(line, expr, ...) __assertion_failedf_at(expr, __FILE__, line, NULL, __VA_ARGS__)

#define RST_LO 0
#define RST_HI 2
#define RST_N  3 /* # of task/comp connections to make available during testing */
static_assert(RST_LO == 0);
static_assert(RST_HI == RST_N - 1);
static_assert(RST_N <= CONFIG_TASK_STATIC_CONNECTIONS);

typedef unsigned int rst_opcode_t;
#define RST_DONE                     0
#define RST_SIG_SEND_TRUE            1
#define RST_SIG_SEND_FALSE           2
#define RST_TASK_DISCONNECT          3
#define RST_TASK_DISCONNECTALL       4
#define RST_TASK_RECEIVEALL          5
#define RST_TASK_CONNECT             6
#define RST_TASK_CONNECT_FOR_POLL    7
#define RST_RING_START               8
#define _RST_SETLINE                 9
#define    RST_RING_END              0
#define    RST_RING_COMP(i)          (1 + (RST_N * 0) + (i))
#define    RST_RING_TASK(i)          (1 + (RST_N * 1) + (i))

#define RST_COMP_CONNECT(i)          (16 + (RST_N * 0) + (i))
#define RST_COMP_CONNECT_FOR_POLL(i) (16 + (RST_N * 1) + (i))
#define RST_COMP_DISCONNECT(i)       (16 + (RST_N * 2) + (i))
#define RST_COMP_ISSENT(i)           (16 + (RST_N * 3) + (i))
#define RST_COMP_ISBCST(i)           (16 + (RST_N * 4) + (i))
#define RST_TASK_ISSENT(i)           (16 + (RST_N * 5) + (i))
#define RST_TASK_ISBCST(i)           (16 + (RST_N * 6) + (i))
#define RST_SIG_BROADCAST(n)         (16 + (RST_N * 7) + (n))
#define RST_SIG_SENDMANY(max, n)     (16 + (RST_N * 9) + ((max) * ((RST_N + 1) * 2)) + (n))

PRIVATE ATTR_FREETEXT char const *KCALL
nameof_rst_ring(rst_opcode_t id) {
	static ATTR_FREEDATA char buf[256];
	static ATTR_FREEDATA char *unused_start = buf;
	char *result = unused_start;
	if (id >= RST_RING_COMP(RST_LO) && id <= RST_RING_COMP(RST_HI)) {
		unused_start += sprintf(result, FREESTR("comp%u"), (unsigned int)(id - RST_RING_COMP(RST_LO)));
	} else if (id >= RST_RING_TASK(RST_LO) && id <= RST_RING_TASK(RST_HI)) {
		unused_start += sprintf(result, FREESTR("task%u"), (unsigned int)(id - RST_RING_TASK(RST_LO)));
	} else {
		unused_start += sprintf(result, FREESTR("{?:%u}"), (unsigned int)id);
	}
	++unused_start;
	return result;
}

PRIVATE ATTR_FREETEXT char const *KCALL
nameof_rst_ptr(struct sigcompcon *comp_cons, struct sigcon *ptr) {
	static ATTR_FREEDATA char buf[256];
	static ATTR_FREEDATA char *unused_start = buf;
	struct taskcons *cons = THIS_CONS;
	char *result = unused_start;
	if (ptr == NULL)
		return FREESTR("NULL");
	if (ptr >= cons->tcs_static && ptr < COMPILER_ENDOF(cons->tcs_static)) {
		unused_start += sprintf(result, FREESTR("task%u"), (unsigned int)((struct sigtaskcon *)ptr - cons->tcs_static));
	} else if (ptr >= comp_cons && ptr < (comp_cons + RST_N)) {
		unused_start += sprintf(result, FREESTR("comp%u"), (unsigned int)((struct sigcompcon *)ptr - comp_cons));
	} else {
		unused_start += sprintf(result, FREESTR("{?:%p}"), ptr);
	}
	++unused_start;
	return result;
}


PRIVATE ATTR_FREETEXT void KCALL
assert_sig_cons(struct sig *s, size_t n,
                struct sigcon *const *scv,
                rst_opcode_t const *scv_names, int line,
                struct sigcompcon *comp_cons) {
#define NAMEOF_RING_ITEM(i) nameof_rst_ring(scv_names[i])
	size_t i;
	struct sigcon *start, *prev, *iter;
	if (n == 0) {
		if (s->s_con != NULL) {
			FAIL(line, NULL, "SIGNAL->s_con == NULL (is: %s)",
			     nameof_rst_ptr(comp_cons, s->s_con));
		}
		return;
	}
	start = prev = scv[0];
	if (s->s_con != start) {
		FAIL(line, NULL, "SIGNAL->s_con == %s (is: %s)",
		     NAMEOF_RING_ITEM(0), nameof_rst_ptr(comp_cons, s->s_con));
	}
	if (start->sc_sig != s) {
		FAIL(line, NULL, "%s->sc_sig == SIGNAL (%p != %p)",
		     NAMEOF_RING_ITEM(0), start->sc_sig, s);
	}
	if (!SIGCON_STAT_ISCONNECTED(start->sc_stat)) {
		FAIL(line, NULL, "SIGCON_STAT_ISCONNECTED(%s->sc_stat) (is: %#Ix)",
		     NAMEOF_RING_ITEM(0), start->sc_stat);
	}

	for (i = 1; i < n; ++i) {
		iter = scv[i];
		if (prev->sc_next != iter) {
			FAIL(line, NULL, "%s->sc_next == %s (%s != %s)",
			     NAMEOF_RING_ITEM(i - 1), NAMEOF_RING_ITEM(i),
			     nameof_rst_ptr(comp_cons, prev->sc_next),
			     nameof_rst_ptr(comp_cons, iter));
		}
		if (iter->sc_prev != prev) {
			FAIL(line, NULL, "%s->sc_prev == %s (%s != %s)",
			     NAMEOF_RING_ITEM(i), NAMEOF_RING_ITEM(i - 1),
			     nameof_rst_ptr(comp_cons, iter->sc_prev),
			     nameof_rst_ptr(comp_cons, prev));
		}
		if (iter->sc_sig != s) {
			FAIL(line, NULL, "%s->sc_sig == SIGNAL (%p != %p)",
			     NAMEOF_RING_ITEM(i), iter->sc_sig, s);
		}
		if (!SIGCON_STAT_ISCONNECTED(iter->sc_stat)) {
			FAIL(line, NULL, "SIGCON_STAT_ISCONNECTED(%s->sc_stat) (is: %#Ix)",
			     NAMEOF_RING_ITEM(i), iter->sc_stat);
		}
		prev = iter;
	}
	if (prev->sc_next != start) {
		FAIL(line, NULL, "%s->sc_next == %s (%s != %s)",
		     NAMEOF_RING_ITEM(n - 1), NAMEOF_RING_ITEM(0),
		     nameof_rst_ptr(comp_cons, prev->sc_next),
		     nameof_rst_ptr(comp_cons, start));
	}
	if (start->sc_prev != prev) {
		FAIL(line, NULL, "%s->sc_prev == %s (%s != %s)",
		     NAMEOF_RING_ITEM(0), NAMEOF_RING_ITEM(i - 1),
		     nameof_rst_ptr(comp_cons, start->sc_prev),
		     nameof_rst_ptr(comp_cons, prev));
	}
#undef NAMEOF_RING_ITEM
}


PRIVATE ATTR_FREETEXT NOBLOCK NOPREEMPT NONNULL_T((1, 2)) size_t
NOTHROW(FCALL test_noop_sigcomp_cb)(struct sigcompcon *__restrict self,
                                    struct sigcompctx *__restrict ctx,
                                    void *buf, size_t bufsize) {
	(void)self;
	(void)ctx;
	(void)buf;
	(void)bufsize;
	return 0;
}

#define RST_F_NORMAL 0x00
#define RST_F_NOPR   0x01 /* Test no-preemption code paths */
#define RST_F_XSEND  0x02 /* Use slower, but more generic sig_x* functions */
PRIVATE ATTR_FREETEXT void KCALL
run_signal_test(rst_opcode_t const *test, int line, unsigned int flags) {
#define L_sigcompcon_connect(x, y)          ((flags & RST_F_NOPR) ? sigcompcon_connect_nopr(x, y) : sigcompcon_connect(x, y))
#define L_sigcompcon_connect_for_poll(x, y) ((flags & RST_F_NOPR) ? sigcompcon_connect_for_poll_nopr(x, y) : sigcompcon_connect_for_poll(x, y))
#define L_sigcompcon_disconnect(x)          ((flags & RST_F_NOPR) ? sigcompcon_disconnect_nopr(x) : sigcompcon_disconnect(x))
#define _L_sig_send(x)                      ((flags & RST_F_NOPR) ? sig_send_nopr(x) : sig_send(x))
#define _L_sig_xsend(x)                     sig_xsend(x, (flags & RST_F_NOPR) ? SIG_XSEND_F_NOPR : SIG_XSEND_F_NORMAL, NULL, THIS_TASK, NULL, NULL, NULL)
#define L_sig_send(x)                       ((flags & RST_F_XSEND) ? _L_sig_xsend(x) : _L_sig_send(x))
#define _L_sig_sendmany(x, n)               ((flags & RST_F_NOPR) ? sig_sendmany_nopr(x, n) : sig_sendmany(x, n))
#define _L_sig_xsendmany(x, n)              sig_xsendmany(x, n, (flags & RST_F_NOPR) ? SIG_XSEND_F_NOPR : SIG_XSEND_F_NORMAL, NULL, THIS_TASK, NULL, NULL, NULL)
#define L_sig_sendmany(x, n)                ((flags & RST_F_XSEND) ? _L_sig_xsendmany(x, n) : _L_sig_sendmany(x, n))
#define _L_sig_broadcast(x)                 ((flags & RST_F_NOPR) ? sig_broadcast_nopr(x) : sig_broadcast(x))
#define _L_sig_xbroadcast(x)                sig_xbroadcast(x, (flags & RST_F_NOPR) ? SIG_XSEND_F_NOPR : SIG_XSEND_F_NORMAL, NULL, THIS_TASK, NULL, NULL, NULL)
#define L_sig_broadcast(x)                  ((flags & RST_F_XSEND) ? _L_sig_xbroadcast(x) : _L_sig_broadcast(x))
	rst_opcode_t opcode;
	DEFINE_SIG_NAMED(s, "kernel.selftest:run_signal_test:s");
	struct sigcompcon comps[RST_N];
	struct taskcons *cons = THIS_CONS;
	{
		size_t i;
		for (i = 0; i < RST_N; ++i)
			sigcompcon_init(&comps[i], &test_noop_sigcomp_cb);
	}

	while ((opcode = *test++) != RST_DONE) {
		if ((flags & RST_F_NOPR) && PREEMPTION_ENABLED())
			FAIL(line, "!PREEMPTION_ENABLED()", NULL);
		switch (opcode) {
		case RST_SIG_SEND_TRUE:
			if (!L_sig_send(&s))
				FAIL(line, "sig_send()", NULL);
			break;
		case RST_SIG_SEND_FALSE:
			if (L_sig_send(&s))
				FAIL(line, "!sig_send()", NULL);
			break;
		case RST_TASK_DISCONNECT:
			if (!task_disconnect(&s))
				FAIL(line, "task_disconnect()", NULL);
			break;
		case RST_TASK_DISCONNECTALL:
			task_disconnectall();
			break;
		case RST_TASK_RECEIVEALL: {
			struct sig *rcv = task_receiveall();
			if (rcv != &s)
				FAIL(line, "task_receiveall() == SIGNAL", "task_receiveall%p", rcv);
		}	break;
		case RST_TASK_CONNECT:
			task_connect(&s);
			break;
		case RST_TASK_CONNECT_FOR_POLL:
			task_connect_for_poll(&s);
			break;
		case RST_RING_START: {
			rst_opcode_t const *name_start = test;
			struct sigcon *ass_cons[RST_N * 2];
			size_t n = 0;
			while ((opcode = *test++) != RST_RING_END) {
				assert(n < COMPILER_LENOF(ass_cons));
				switch (opcode) {
				case RST_RING_COMP(RST_LO) ... RST_RING_COMP(RST_HI):
					ass_cons[n++] = &comps[opcode - RST_RING_COMP(RST_LO)];
					break;
				case RST_RING_TASK(RST_LO) ... RST_RING_TASK(RST_HI):
					ass_cons[n++] = &cons->tcs_static[opcode - RST_RING_TASK(RST_LO)];
					break;
				default: FAIL(line, NULL, "Unknown opcode: %#I8x", opcode);
				}
			}
			assert_sig_cons(&s, n, ass_cons, name_start, line, comps);
		}	break;

		case _RST_SETLINE:
			line = *test++;
#ifndef sigcon_verify_ring_IS_NOOP
			printk(KERN_RAW "%s(%d): run_signal_test\n", __FILE__, line);
#endif /* !sigcon_verify_ring_IS_NOOP */
			break;

		case RST_COMP_CONNECT(RST_LO) ... RST_COMP_CONNECT(RST_HI):
			L_sigcompcon_connect(&comps[opcode - RST_COMP_CONNECT(RST_LO)], &s);
			break;
		case RST_COMP_CONNECT_FOR_POLL(RST_LO) ... RST_COMP_CONNECT_FOR_POLL(RST_HI):
			L_sigcompcon_connect_for_poll(&comps[opcode - RST_COMP_CONNECT_FOR_POLL(RST_LO)], &s);
			break;
		case RST_COMP_DISCONNECT(RST_LO) ... RST_COMP_DISCONNECT(RST_HI):
			L_sigcompcon_disconnect(&comps[opcode - RST_COMP_DISCONNECT(RST_LO)]);
			break;
		case RST_SIG_BROADCAST(RST_LO) ... RST_SIG_BROADCAST(RST_N * 2 - 1): {
			size_t want_n = opcode - RST_SIG_BROADCAST(RST_LO);
			size_t real_n = L_sig_broadcast(&s);
			if (want_n != real_n)
				FAIL(line, "sig_broadcast()", "sig_broadcast() == %Iu (is: %Iu)", want_n, real_n);
		}	break;
		case RST_SIG_SENDMANY(RST_LO, RST_LO) ... RST_SIG_SENDMANY((RST_N + 1) * 2, (RST_N + 1) * 2): {
			size_t oparg = opcode - RST_SIG_SENDMANY(RST_LO, RST_LO);
			size_t want_n = oparg % ((RST_N + 1) * 2);
			size_t send_n = oparg / ((RST_N + 1) * 2);
			size_t real_n = L_sig_sendmany(&s, send_n);
			if (want_n != real_n)
				FAIL(line, "sig_sendmany()", "sig_sendmany(%Iu) == %Iu (is: %Iu)", send_n, want_n, real_n);
		}	break;
		case RST_COMP_ISSENT(RST_LO) ... RST_COMP_ISSENT(RST_HI): {
			struct sigcompcon *c = &comps[opcode - RST_COMP_ISSENT(RST_LO)];
			if (c->sc_stat != SIGCON_STAT_ST_THRSENT) {
				FAIL(line, NULL, "%s->sc_stat == SIGCON_STAT_ST_THRSENT (is: %#Ix)",
				     nameof_rst_ring(RST_RING_COMP(opcode - RST_COMP_ISSENT(RST_LO))),
				     c->sc_stat);
			}
		}	break;
		case RST_COMP_ISBCST(RST_LO) ... RST_COMP_ISBCST(RST_HI): {
			struct sigcompcon *c = &comps[opcode - RST_COMP_ISBCST(RST_LO)];
			if (c->sc_stat != SIGCON_STAT_ST_THRBCAST) {
				FAIL(line, NULL, "%s->sc_stat == SIGCON_STAT_ST_THRBCAST (is: %#Ix)",
				     nameof_rst_ring(RST_RING_COMP(opcode - RST_COMP_ISBCST(RST_LO))),
				     c->sc_stat);
			}
		}	break;
		case RST_TASK_ISSENT(RST_LO) ... RST_TASK_ISSENT(RST_HI): {
			struct sigtaskcon *c = &cons->tcs_static[opcode - RST_TASK_ISSENT(RST_LO)];
			if (c->sc_stat != SIGCON_STAT_ST_THRSENT) {
				FAIL(line, NULL, "%s->sc_stat == SIGCON_STAT_ST_THRSENT (is: %#Ix)",
				     nameof_rst_ring(RST_RING_TASK(opcode - RST_TASK_ISSENT(RST_LO))),
				     c->sc_stat);
			}
		}	break;
		case RST_TASK_ISBCST(RST_LO) ... RST_TASK_ISBCST(RST_HI): {
			struct sigtaskcon *c = &cons->tcs_static[opcode - RST_TASK_ISBCST(RST_LO)];
			if (c->sc_stat != SIGCON_STAT_ST_THRBCAST) {
				FAIL(line, NULL, "%s->sc_stat == SIGCON_STAT_ST_THRBCAST (is: %#Ix)",
				     nameof_rst_ring(RST_RING_TASK(opcode - RST_TASK_ISBCST(RST_LO))),
				     c->sc_stat);
			}
		}	break;

		default: FAIL(line, NULL, "Unknown opcode: %#I8x", opcode);
		}
#undef _line
	}
#undef L_sigcompcon_connect
#undef L_sigcompcon_connect_for_poll
#undef L_sigcompcon_disconnect
#undef _L_sig_send
#undef _L_sig_xsend
#undef L_sig_send
#undef _L_sig_sendmany
#undef _L_sig_xsendmany
#undef L_sig_sendmany
#undef _L_sig_broadcast
#undef _L_sig_xbroadcast
#undef L_sig_broadcast
}

PRIVATE ATTR_FREETEXT void KCALL
do_run_signal_test(rst_opcode_t const *test, int line) {
	run_signal_test(test, line, RST_F_NORMAL);
	run_signal_test(test, line, RST_F_XSEND);
	PREEMPTION_DISABLE();
	run_signal_test(test, line, RST_F_NOPR);
	run_signal_test(test, line, RST_F_XSEND | RST_F_NOPR);
	PREEMPTION_ENABLE();
}

#define RST_BEGIN                      \
	do {                               \
		int _xtest_lno = __LINE__ + 1; \
		static ATTR_FREERODATA rst_opcode_t const _xtest_dat[] = {
#define L _RST_SETLINE, __LINE__,
#define RST_END                                     \
			RST_DONE                                \
		};                                          \
		do_run_signal_test(_xtest_dat, _xtest_lno); \
	}	__WHILE0

#define C0 RST_RING_COMP(0)
#define C1 RST_RING_COMP(1)
#define C2 RST_RING_COMP(2)
#define T0 RST_RING_TASK(0)
#define T1 RST_RING_TASK(1)
#define T2 RST_RING_TASK(2)

DEFINE_TEST(sig_test_generic) {
	RST_BEGIN
		L /**/ RST_RING_START, RST_RING_END,

		/* Send on empty signal */
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_RING_START, RST_RING_END,

		/* Sendmany on empty signal */
		L /**/ RST_SIG_SENDMANY(RST_HI, 0),
		L /**/ RST_RING_START, RST_RING_END,

		/* Broadcast on empty signal */
		L /**/ RST_SIG_BROADCAST(0),
		L /**/ RST_RING_START, RST_RING_END,

		/* Send to task connection */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_ISSENT(0),
		L /**/ RST_TASK_RECEIVEALL,
		L /**/ RST_RING_START, RST_RING_END,

		/* Send to task connection (poll) */
		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_ISBCST(0),
		L /**/ RST_TASK_RECEIVEALL,
		L /**/ RST_RING_START, RST_RING_END,

		/* Send to comp connection */
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_RING_START, C0, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_ISSENT(0),
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, RST_RING_END,

		/* Send to comp connection (poll) */
		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_RING_START, C0, RST_RING_END,
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_ISBCST(0),
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, RST_RING_END,

		/* Disconnect task (single) */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_TASK_DISCONNECT,
		L /**/ RST_RING_START, RST_RING_END,

		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, T1, RST_RING_END,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, T1, T2, RST_RING_END,
		L /**/ RST_TASK_DISCONNECT,
		L /**/ RST_TASK_DISCONNECT,
		L /**/ RST_TASK_DISCONNECT,
		L /**/ RST_RING_START, RST_RING_END,

		/* Disconnect task (all) */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, RST_RING_END,

		L /**/ RST_TASK_CONNECT,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, T1, T2, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, RST_RING_END,

		/* Signal forwarding during disconnect (task -> comp) */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_RING_START, T0, C0, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C0, RST_RING_END,
		L /**/ RST_TASK_DISCONNECT,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_RECEIVEALL,
		L /**/ RST_COMP_ISSENT(0),

		/* Signal forwarding during disconnect (comp -> task) */
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, C0, T0, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_COMP_ISSENT(0),
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_RECEIVEALL,

		/* Send to poll+npoll */
		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C0, RST_RING_END,
		L /**/ RST_COMP_ISSENT(1),
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, RST_RING_END,

		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C0, RST_RING_END,
		L /**/ RST_COMP_ISSENT(1),
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_ISBCST(0),

		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, T1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, RST_RING_END,

		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, T1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, T0, RST_RING_END,
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, RST_RING_END,

		/* Send to npoll+poll */
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_COMP_CONNECT_FOR_POLL(1),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C1, RST_RING_END,
		L /**/ RST_COMP_ISSENT(0),
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_RING_START, RST_RING_END,

		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_COMP_CONNECT_FOR_POLL(1),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C1, RST_RING_END,
		L /**/ RST_COMP_ISSENT(0),
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_ISBCST(1),

		L /**/ RST_TASK_CONNECT,
		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_RING_START, T0, T1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, T1, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, RST_RING_END,

		L /**/ RST_TASK_CONNECT,
		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_RING_START, T0, T1, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, T1, RST_RING_END,
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, RST_RING_END,

		/* Broadcast to poll+npoll */
		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_SIG_BROADCAST(1),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_ISBCST(0),
		L /**/ RST_COMP_ISBCST(1),

		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, T0, T1, RST_RING_END,
		/* This is actually "0" instead of "1" because the poll-connection is received first,
		 * but  that one doesn't count to the total, and the second connection isn't received
		 * because at that point the thread already has a signal. */
		L /**/ RST_SIG_BROADCAST(0),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_RECEIVEALL,

		/* Broadcast to npoll+poll */
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_COMP_CONNECT_FOR_POLL(1),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_SIG_BROADCAST(1),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_ISBCST(0),
		L /**/ RST_COMP_ISBCST(1),

		L /**/ RST_TASK_CONNECT,
		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_RING_START, T0, T1, RST_RING_END,
		L /**/ RST_SIG_BROADCAST(1),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_RECEIVEALL,

		/* Send signal to poll+poll+poll+poll */
		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_COMP_CONNECT_FOR_POLL(1),
		L /**/ RST_COMP_CONNECT_FOR_POLL(2),
		L /**/ RST_TASK_CONNECT_FOR_POLL,
		L /**/ RST_RING_START, C0, C1, C2, T0, RST_RING_END,
		L /**/ RST_SIG_SEND_FALSE,
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_ISBCST(0),
		L /**/ RST_COMP_ISBCST(1),
		L /**/ RST_COMP_ISBCST(2),
		L /**/ RST_TASK_RECEIVEALL,

		/* Send signal to norm+poll+poll+poll */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_COMP_CONNECT_FOR_POLL(1),
		L /**/ RST_COMP_CONNECT_FOR_POLL(2),
		L /**/ RST_RING_START, T0, C0, C1, C2, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C0, C1, C2, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(2),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, C1, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_RECEIVEALL,

		/* Send signal to poll+poll+norm+poll */
		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_COMP_CONNECT_FOR_POLL(1),
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_COMP_CONNECT_FOR_POLL(2),
		L /**/ RST_RING_START, C0, C1, T0, C2, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C2, C0, C1, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_RING_START, C2, C0, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, C2, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(2),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_RECEIVEALL,

		/* Send signal to poll+poll+poll+norm */
		L /**/ RST_COMP_CONNECT_FOR_POLL(0),
		L /**/ RST_COMP_CONNECT_FOR_POLL(1),
		L /**/ RST_COMP_CONNECT_FOR_POLL(2),
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, C0, C1, C2, T0, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C0, C1, C2, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(2),
		L /**/ RST_RING_START, C0, C1, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_RING_START, C0, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_RECEIVEALL,

		/* Send signal to norm+norm+norm+norm (w/ forwarding) */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_COMP_CONNECT(2),
		L /**/ RST_RING_START, T0, C0, C1, C2, RST_RING_END,
		L /**/ RST_SIG_SEND_TRUE,
		L /**/ RST_RING_START, C0, C1, C2, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_COMP_ISSENT(0),
		L /**/ RST_RING_START, C1, C2, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_COMP_ISSENT(1),
		L /**/ RST_RING_START, C2, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_COMP_ISSENT(2),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(2),

		/* Broadcast signal to norm+norm+norm+norm (w/ forwarding) */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_COMP_CONNECT(2),
		L /**/ RST_RING_START, T0, C0, C1, C2, RST_RING_END,
		L /**/ RST_SIG_BROADCAST(4),
		L /**/ RST_RING_START, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_COMP_ISBCST(0),
		L /**/ RST_COMP_ISBCST(1),
		L /**/ RST_COMP_ISBCST(2),
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_COMP_DISCONNECT(2),

		/* Sendmany signal to norm+norm+norm+norm (w/ forwarding) */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_COMP_CONNECT(2),
		L /**/ RST_RING_START, T0, C0, C1, C2, RST_RING_END,
		L /**/ RST_SIG_SENDMANY(3, 3),
		L /**/ RST_RING_START, C2, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_COMP_ISBCST(0),
		L /**/ RST_COMP_ISBCST(1),
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_RING_START, C2, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(2),
		L /**/ RST_RING_START, RST_RING_END,

		/* Disconnect with multiple other signals */
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_COMP_CONNECT(2),
		L /**/ RST_RING_START, T0, C0, C1, C2, RST_RING_END,
		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, C0, C1, C2, RST_RING_END,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, C0, C1, C2, T0, RST_RING_END,

		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, C1, C2, T0, RST_RING_END,
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_RING_START, C1, C2, T0, C0, RST_RING_END,

		L /**/ RST_COMP_DISCONNECT(2),
		L /**/ RST_RING_START, C1, T0, C0, RST_RING_END,
		L /**/ RST_COMP_CONNECT(2),
		L /**/ RST_RING_START, C1, T0, C0, C2, RST_RING_END,

		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, C1, T0, C2, RST_RING_END,
		L /**/ RST_COMP_CONNECT(0),
		L /**/ RST_RING_START, C1, T0, C2, C0, RST_RING_END,

		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, C1, C2, C0, RST_RING_END,
		L /**/ RST_TASK_CONNECT,
		L /**/ RST_RING_START, C1, C2, C0, T0, RST_RING_END,

		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_RING_START, C2, C0, T0, RST_RING_END,
		L /**/ RST_COMP_CONNECT(1),
		L /**/ RST_RING_START, C2, C0, T0, C1, RST_RING_END,

		L /**/ RST_TASK_DISCONNECTALL,
		L /**/ RST_RING_START, C2, C0, C1, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(1),
		L /**/ RST_RING_START, C2, C0, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(2),
		L /**/ RST_RING_START, C0, RST_RING_END,
		L /**/ RST_COMP_DISCONNECT(0),
		L /**/ RST_RING_START, RST_RING_END,
	RST_END;
}

#undef RST_BEGIN
#undef L
#undef RST_END
#undef C0
#undef C1
#undef C2
#undef T0
#undef T1
#undef T2

#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 3 */

DECL_END
#endif /* DEFINE_TEST */

#ifndef __INTELLISENSE__
#define DEFINE_task_waitfor
#include "sig-waitfor.c.inl"
#define DEFINE_task_waitfor_with_sigmask
#include "sig-waitfor.c.inl"
#define DEFINE_task_waitfor_norpc
#include "sig-waitfor.c.inl"
#define DEFINE_task_waitfor_nx
#include "sig-waitfor.c.inl"
#define DEFINE_task_waitfor_norpc_nx
#include "sig-waitfor.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIG_C */
