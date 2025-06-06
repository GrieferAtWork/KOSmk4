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

#if defined(CONFIG_EXPERIMENTAL_KERNEL_SIG_V2) || defined(__DEEMON__)
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
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
#define sigcon_link_insert_before(self, successor)       \
	sigcon_rlink_insert_before(self, self, successor)
#define sigcon_rlink_insert_before(self_head, self_tail, successor) \
	(void)((self_tail)->sc_next = (successor),                      \
	       (self_head)->sc_prev = (successor)->sc_prev,             \
	       (successor)->sc_prev = (self_tail),                      \
	       (self_head)->sc_prev->sc_next = (self_head))

/* Internal key used to chain threads that have to be destroyed. */
#define sig_destroylater_next(thread) KEY_task__next(thread)

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


LOCAL NOBLOCK void
NOTHROW(FCALL destroy_tasks)(struct task *destroy_later) {
	while (destroy_later) {
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
#define DEFINE_sig_sendmany_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_altbroadcast
#include "sig-send.c.inl"
#define DEFINE_sig_altbroadcast_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast_cleanup_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast_for_fini
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast_for_fini_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_altbroadcast_for_fini
#include "sig-send.c.inl"
#define DEFINE_sig_altbroadcast_for_fini_nopr
#include "sig-send.c.inl"
#define DEFINE_sig_broadcast_for_fini_cleanup_nopr
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
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_sendmany_nopr)(struct sig *__restrict self, size_t maxcount) {
	return sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_NORMAL, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_nopr)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_nopr)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcast_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP, NULL, THIS_TASK, cleanup, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_for_fini)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_FINI, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_for_fini_nopr)(struct sig *__restrict self) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI, NULL, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini_nopr)(struct sig *self, struct sig *sender) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER, sender, THIS_TASK, NULL, NULL, NULL);
}
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcast_for_fini_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup) {
	return sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CLEANUP, NULL, THIS_TASK, cleanup, NULL, NULL);
}
DECL_END
#endif /* __OPTIMIZE_SIZE__ */
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
NOTHROW(KCALL pertask_fix_task_connections)(struct task *__restrict self) {
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

/* Push/pop the active  set of  connections:
 * >> struct sig a = SIG_INIT, b = SIG_INIT;
 * >> struct taskcons cons;
 * >> task_connect(&a);
 * >> assert(task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_pushcons(&cons);
 * >> assert(!task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_connect(&b);
 * >> assert(!task_wasconnected(&a));
 * >> assert(task_wasconnected(&b));
 * >>
 * >> task_disconnectall();
 * >> assert(!task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_popcons();
 * >> assert(task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b)); */
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
	        "Cannot call `task_popconnections()' when you've still "
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
 * Note that for this purpose,  only signals from the  currently active set of  task
 * connections will  be connected.  Connections established  outside the  bounds  of
 * the current `task_pushconnections()...task_popconnections()'  pair will _NOT_  be
 * connected. If one of  the signals which  the calling thread  is connected to  has
 * already been  sent (i.e.  `task_waitfor()' wouldn't  block), then  this  function
 * will return early, and the exact (if  any) signals that were connected to  `self'
 * are left undefined (meaning that the caller can really only handle this happening
 * by using `sigmulticomp_disconnectall()', but also meaning that `cb' may still get
 * invoked  in case the caller was connected to  more than one signal, and more than
 * one of those gets triggered before connections of `self' get disconnected).
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
#else /* CONFIG_EXPERIMENTAL_KERNEL_SIG_V2 */
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <sched/pertask.h>
#include <sched/sig-completion.h>
#include <sched/sig-select.h>
#include <sched/sig.h>
#include <sched/task-clone.h> /* DEFINE_PERTASK_RELOCATION */
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/sched/preemption.h>

#include <kos/nopf.h>
#include <kos/types.h>

#include <alloca.h>
#include <atomic.h>
#include <inttypes.h>
#include <stdalign.h>

#if defined(__i386__) || defined(__x86_64__)
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/segment.h>
#endif /* __i386__ || __x86_64__ */
#include <stdint.h>

/* Internal key used to chain threads that have to be destroyed. */
#define sig_destroylater_next(thread) KEY_task__next(thread)

DECL_BEGIN

/* Assert offsets */
static_assert(offsetof(struct task_connection, tc_sig) == OFFSET_TASK_CONNECTION_SIG);
static_assert(offsetof(struct task_connection, tc_connext) == OFFSET_TASK_CONNECTION_CONNEXT);
static_assert(offsetof(struct task_connection, tc_signext) == OFFSET_TASK_CONNECTION_SIGNEXT);
static_assert(offsetof(struct task_connection, tc_cons) == OFFSET_TASK_CONNECTION_CONS);
static_assert(offsetof(struct task_connection, tc_stat) == OFFSET_TASK_CONNECTION_STAT);
static_assert(sizeof(struct task_connection) == SIZEOF_TASK_CONNECTION);
static_assert(alignof(struct task_connection) == ALIGNOF_TASK_CONNECTION);
static_assert(offsetof(struct task_connections, tcs_prev) == OFFSET_TASK_CONNECTIONS_PREV);
static_assert(offsetof(struct task_connections, tcs_thread) == OFFSET_TASK_CONNECTIONS_THREAD);
static_assert(offsetof(struct task_connections, tcs_con) == OFFSET_TASK_CONNECTIONS_CON);
static_assert(offsetof(struct task_connections, tcs_dlvr) == OFFSET_TASK_CONNECTIONS_DLVR);
static_assert(offsetof(struct task_connections, tcs_static) == OFFSET_TASK_CONNECTIONS_STATIC);
static_assert(sizeof(struct task_connections) == SIZEOF_TASK_CONNECTIONS);
static_assert(alignof(struct task_connections) == ALIGNOF_TASK_CONNECTIONS);


/* Root connections set. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct task_connections) this_root_connections = {
	.tcs_prev   = NULL,
	.tcs_thread = NULL,
	.tcs_con    = NULL,
	.tcs_dlvr   = NULL,
	.tcs_static = { }
};

/* [1..1][lock(PRIVATE(THIS_TASK))]  Current   set   of   in-use   connections.
 * Most of the time, this will simply point to `PERTASK(this_root_connections)' */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct task_connections *)
this_connections = &this_root_connections;

/* Define relocations */
DEFINE_PERTASK_RELOCATION(this_root_connections + OFFSET_TASK_CONNECTIONS_THREAD);
DEFINE_PERTASK_RELOCATION(this_connections);

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_fix_task_connections)(struct task *__restrict self) {
	struct task *active_thread;
	struct task_connections *self_connections;
	self_connections = FORTASK(self, this_connections);
	if (!ADDR_ISKERN(self_connections))
		goto fixit;
	if (!IS_ALIGNED((uintptr_t)self_connections, alignof(struct task_connections)))
		goto fixit;
	if (memcpy_nopf(&active_thread, &self_connections->tcs_thread, sizeof(struct task *)) != 0)
		goto fixit;
	if (active_thread != self)
		goto fixit;
	return;
fixit:
	FORTASK(self, this_connections) = &FORTASK(self, this_root_connections);
	bzero(&FORTASK(self, this_root_connections), sizeof(struct task_connections));
	FORTASK(self, this_root_connections.tcs_thread) = self;
}

#if defined(__x86_64__) || defined(__i386__)
INTERN NOBLOCK ATTR_RETNONNULL struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void);
#endif /* __x86_64__ || __i386__ */

/* Push/pop the active  set of  connections:
 * >> struct sig a = SIG_INIT, b = SIG_INIT;
 * >> struct task_connections cons;
 * >> task_connect(&a);
 * >> assert(task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_pushconnections(&cons);
 * >> assert(!task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_connect(&b);
 * >> assert(!task_wasconnected(&a));
 * >> assert(task_wasconnected(&b));
 * >>
 * >> task_disconnectall();
 * >> assert(!task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_popconnections();
 * >> assert(task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b)); */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushconnections)(struct task_connections *__restrict cons) {
	struct task_connections *oldcons;
	unsigned int i;
#ifdef NDEBUG
	oldcons = THIS_CONNECTIONS;
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
	if unlikely(!read_nopf(&FORTASK(mythread, this_connections), &oldcons)) {
		assertf(read_nopf(&FORTASK(mythread, this_connections), &oldcons),
		        "Corrupt TLS base pointer: mythread = %p", mythread);
		/* Allow the user to IGNORE the assertion check, in which case we'll
		 * try to repair the damage... */
		mythread = x86_repair_broken_tls_state();
		oldcons  = FORTASK(mythread, this_connections);
	}
#else /* ... */
	oldcons = THIS_CONNECTIONS;
#endif /* !... */
	assertf(cons != oldcons,
	        "Connections set %p has already been pushed",
	        cons);
	cons->tcs_prev = oldcons;

	/* Disable async notifications for the old set of connections,
	 * and use the receiver thread for the new set of connections.
	 * Really, though: This should always just be `THIS_TASK' */
	cons->tcs_thread = atomic_xch(&oldcons->tcs_thread, NULL);
	cons->tcs_con    = NULL; /* No connections in use (yet) */
	cons->tcs_dlvr   = NULL; /* Nothing was delivered (yet) */
	DBG_memset(cons->tcs_static, 0xcc, sizeof(cons->tcs_static));

	/* Set-up statically allocated connections. */
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i)
		cons->tcs_static[i].tc_sig = NULL; /* Available for use. */

	/* Finally, set the active connection set to `cons' */
	PERTASK_SET(this_connections, cons);
}

PUBLIC NOBLOCK ATTR_RETNONNULL struct task_connections *
NOTHROW(FCALL task_popconnections)(void) {
	struct task_connections *oldcons;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;
	assert((cons->tcs_prev == NULL) == (cons == THIS_ROOT_CONNECTIONS));
	assertf(cons != THIS_ROOT_CONNECTIONS,
	        "Cannot pop connections: Root connection set %p is already active",
	        cons);

	/* Make sure that no connections are left active. */
	assertf(cons->tcs_con == NULL,
	        "Cannot call `task_popconnections()' when you've still "
	        "got connections that haven't been disconnected, yet\n"
	        "call `task_disconnectall()' first!");

	/* Set the TLS pointer for the current set of connection to the old set. */
	oldcons = cons->tcs_prev;
	PERTASK_SET(this_connections, oldcons);

	/* Re-enable asynchronous notifications as the result of `sig_send()' / `sig_broadcast()' */
	atomic_write(&oldcons->tcs_thread, THIS_TASK);

	/* Make bad usage consistent by filling memory with garbage. */
	DBG_memset(cons, 0xcc, sizeof(*cons));

	return cons;
}


/* Allocate a new task connection. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct task_connection *FCALL
task_connection_alloc(struct task_connections *__restrict self) THROWS(E_BADALLOC) {
	unsigned int i;
	struct task_connection *result;

	/* Check if one of the static slots is available. */
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i) {
		result = &self->tcs_static[i];
		if (!result->tc_sig)
			goto done;
	}

	/* Must dynamically allocate a new slot. */
	result = (struct task_connection *)kmalloc(sizeof(struct task_connection),
	                                           GFP_LOCKED | GFP_PREFLT);
done:
	return result;
}

/* Free a given task connection. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_free)(struct task_connections *__restrict self,
                                    struct task_connection *__restrict con) {
	if (con >= self->tcs_static &&
	    con < COMPILER_ENDOF(self->tcs_static)) {
		/* Free a static connection. */
		con->tc_sig = NULL;
	} else {
		/* Free a dynamically allocated connection. */
		kfree(con);
	}
}



#if defined(SIG_CONTROL_SMPLOCK) && SIG_CONTROL_SMPLOCK != 0
#define sig_smplock_set(con)      ((struct task_connection *)((uintptr_t)(con) | SIG_CONTROL_SMPLOCK))
#define sig_smplock_clr(con)      ((struct task_connection *)((uintptr_t)(con) & ~SIG_CONTROL_SMPLOCK))
#define sig_smplock_tst(con)      ((uintptr_t)(con) & SIG_CONTROL_SMPLOCK)
#define sig_smplock_cpy(to, from) (struct task_connection *)((uintptr_t)(to) | ((uintptr_t)(from) & SIG_CONTROL_SMPLOCK))
#define sig_smplock_tryacquire_nopr(self) \
	(!(atomic_fetchor_explicit(&(self)->s_ctl, SIG_CONTROL_SMPLOCK, memory_order_acquire) & SIG_CONTROL_SMPLOCK))
#define sig_smplock_acquire_nopr(self)             \
	do {                                           \
		while (!sig_smplock_tryacquire_nopr(self)) \
			task_pause();                          \
	}	__WHILE0
#define sig_smplock_release_nopr(self) \
	atomic_and_explicit(&(self)->s_ctl, ~SIG_CONTROL_SMPLOCK, memory_order_release)
#else /* SIG_CONTROL_SMPLOCK != 0 */
#define sig_smplock_set(con)              con
#define sig_smplock_clr(con)              con
#define sig_smplock_tst(con)              0
#define sig_smplock_cpy(to, from)         to
#define sig_smplock_tryacquire_nopr(self) 1
#define sig_smplock_acquire_nopr(self)    (void)0
#define sig_smplock_release_nopr(self)    (void)0
#endif /* SIG_CONTROL_SMPLOCK == 0 */

#define sig_smplock_acquire(self) preemption_acquire_smp(sig_smplock_tryacquire_nopr(self))
#define sig_smplock_release(self) preemption_release_smp(sig_smplock_release_nopr(self))


#ifdef TASK_CONNECTION_STAT_FLOCK
#define TASK_CONNECTION_STAT_FLOCK_OPT TASK_CONNECTION_STAT_FLOCK
#else /* TASK_CONNECTION_STAT_FLOCK */
#define TASK_CONNECTION_STAT_FLOCK_OPT 0
#endif /* !TASK_CONNECTION_STAT_FLOCK */


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
task_connect(struct sig *__restrict target) THROWS(E_BADALLOC) {
	struct task_connection *con, *next;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;
	assert(IS_ALIGNED((uintptr_t)cons, TASK_CONNECTION_STAT_FMASK + 1));

	/* When a signal was already delivered, `task_connect()' becomes a no-op */
	if unlikely(atomic_read(&cons->tcs_dlvr) != NULL)
		return;

	/* Allocate a new connection for `cons' */
	con = task_connection_alloc(cons);
	assert(!sig_smplock_tst(con));

	/* Fill in the new connection. */
	con->tc_sig     = target;
	con->tc_connext = cons->tcs_con;
	cons->tcs_con   = con;
	con->tc_cons    = cons;

	/* Now insert the connection onto the stack used by `target'
	 * NOTE: `sig_send()' will always  traverse the chain  to the  last
	 *       thread, meaning that we can (and have to) insert ourselves
	 *       at the front of the chain.
	 * Also note that inserting a new connection can be done without
	 * having  to tinker with the signal's SMP-lock, so this part is
	 * actually surprisingly simple. */
	do {
		next = atomic_read(&target->s_con);
		con->tc_signext = sig_smplock_clr(next);
		assertf(con != sig_smplock_clr(next), "Duplicate connection?");
		COMPILER_WRITE_BARRIER();
	} while (!atomic_cmpxch_weak(&target->s_con, next,
	                             sig_smplock_cpy(con, next)));
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
task_connect_for_poll(struct sig *__restrict target) THROWS(E_BADALLOC) {
	struct task_connection *con, *next;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;
	assert(IS_ALIGNED((uintptr_t)cons, TASK_CONNECTION_STAT_FMASK + 1));

	/* When a signal was already delivered, `task_connect()' becomes a no-op */
	if unlikely(atomic_read(&cons->tcs_dlvr) != NULL)
		return;

	/* Allocate a new connection for `cons' */
	con = task_connection_alloc(cons);
	assert(!sig_smplock_tst(con));

	/* Fill in the new connection. */
	con->tc_sig     = target;
	con->tc_connext = cons->tcs_con;
	cons->tcs_con   = con;
	con->tc_cons    = (struct task_connections *)((uintptr_t)cons | TASK_CONNECTION_STAT_FPOLL);

	/* Now insert the connection onto the stack used by `target'
	 * NOTE: `sig_send()' will always  traverse the chain  to the  last
	 *       thread, meaning that we can (and have to) insert ourselves
	 *       at the front of the chain.
	 * Also note that inserting a new connection can be done without
	 * having  to tinker with the signal's SMP-lock, so this part is
	 * actually surprisingly simple. */
	do {
		next = atomic_read(&target->s_con);
		con->tc_signext = sig_smplock_clr(next);
		assertf(con != sig_smplock_clr(next), "Duplicate connection?");
		COMPILER_WRITE_BARRIER();
	} while (!atomic_cmpxch_weak(&target->s_con, next,
	                             sig_smplock_cpy(con, next)));
}

/* Remove `con' from the linked list of active connections of `self'. */
LOCAL NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_unlink_from_sig)(struct sig *__restrict self,
                                               struct task_connection *__restrict con) {
	struct task_connection *chain;
again:
	assert(!sig_smplock_tst(con->tc_signext));
	assert(!con->tc_signext || ADDR_ISKERN(con->tc_signext));
	assert(!preemption_ison());
#if TASK_CONNECTION_STAT_FLOCK != 0
	assert(con->tc_stat & TASK_CONNECTION_STAT_FLOCK);
#endif /* TASK_CONNECTION_STAT_FLOCK != 0 */
	assert(con->tc_stat != (TASK_CONNECTION_STAT_COMPLETION | TASK_CONNECTION_STAT_FLOCK));
	assert(con->tc_stat != (TASK_CONNECTION_STAT_COMPLETION_FOR_POLL | TASK_CONNECTION_STAT_FLOCK));
	chain = atomic_read(&self->s_con);
	if (sig_smplock_clr(chain) == con) {
		/* The first entry already is the connection we're trying to unlink!
		 * In this case, we must use an atomic operation, since other thread
		 * or CPUs may have added more connections since the the read above. */
		if (!atomic_cmpxch_weak(&self->s_con, chain,
		                        /* Keep the SMP-lock bit set! */
		                        sig_smplock_set(con->tc_signext)))
			goto again;
	} else {
		struct task_connection **pchain;

		/* Since the caller has acquired the SMP-lock of `self' for us,
		 * we  are  able to  access  all of  the  attached connections! */
		chain  = sig_smplock_clr(chain);
		pchain = &chain->tc_signext;
		assert(chain->tc_sig == self);
		for (;;) {
			chain = *pchain;
			assert(!sig_smplock_tst(chain));
			assert(chain && ADDR_ISKERN(chain));
			assert(chain->tc_sig == self);
			if (chain == con)
				break; /* Found the entry! */
			pchain = &chain->tc_signext;
		}

		/* Unlink the element. */
		*pchain = chain->tc_signext;
	}
	DBG_memset(&con->tc_signext, 0xcc, sizeof(con->tc_signext));
}


/* Same as `task_connection_unlink_from_sig()', but also release the SMP-lock. The  caller
 * must then release the preemption lock through use of `sig_smp_lock_release_nosmp(self)' */
#if SIG_CONTROL_SMPLOCK == 0
#define TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG 1
#define task_connection_unlink_from_sig_and_unlock(self, con) \
	task_connection_unlink_from_sig(self, con)
#else /* SIG_CONTROL_SMPLOCK == 0 */
LOCAL NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_unlink_from_sig_and_unlock)(struct sig *__restrict self,
                                                          struct task_connection *__restrict con) {
	struct task_connection *chain;
again:
	assert(!sig_smplock_tst(con->tc_signext));
	assert(!con->tc_signext || ADDR_ISKERN(con->tc_signext));
	chain = atomic_read(&self->s_con);
	if (sig_smplock_clr(chain) == con) {
		/* The first entry already is the connection we're trying to unlink!
		 * In this case, we must use an atomic operation, since other thread
		 * or CPUs may have added more connections since the the read above. */
		if (!atomic_cmpxch_weak(&self->s_con,
		                        chain,
		                        /* Don't keep the SMP-lock bit set! */
		                        con->tc_signext))
			goto again;
	} else {
		struct task_connection **pchain;

		/* Since the caller has acquired the SMP-lock of `self' for us,
		 * we  are  able to  access  all of  the  attached connections! */
		chain  = sig_smplock_clr(chain);
		pchain = &chain->tc_signext;
		assert(chain->tc_sig == self);
		for (;;) {
			chain = *pchain;
			assert(!sig_smplock_tst(chain));
			assert(chain && ADDR_ISKERN(chain));
			assert(chain->tc_sig == self);
			if (chain == con)
				break; /* Found the entry! */
			pchain = &chain->tc_signext;
		}

		/* Unlink the element. */
		*pchain = chain->tc_signext;
		COMPILER_WRITE_BARRIER();

		/* Clear the SMP-lock bit. */
		atomic_and(&self->s_ctl, ~SIG_CONTROL_SMPLOCK);
	}
	DBG_memset(&con->tc_signext, 0xcc, sizeof(con->tc_signext));
}
#endif /* SIG_CONTROL_SMPLOCK != 0 */

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((2)) bool
NOTHROW(FCALL is_connection_in_chain)(struct task_connection *chain,
                                      struct task_connection *con) {
	for (; chain; chain = chain->tc_connext) {
		if (chain == con)
			return true;
	}
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL destroy_tasks)(struct task *destroy_later) {
	while (destroy_later) {
		struct task *next;
		next = sig_destroylater_next(destroy_later);
		destroy(destroy_later);
		destroy_later = next;
	}
}


struct sig_post_completion {
	struct sig_post_completion     *spc_next; /* [0..1] Next post-completion descriptor. */
	sig_postcompletion_t            spc_cb;   /* [1..1] Post-completion callback to-be invoked. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, spc_buf); /* Buffer to-be passed to `spc_cb' */
};

#define sig_post_completion_alloc(bufsize) \
	((struct sig_post_completion *)alloca(offsetof(struct sig_post_completion, spc_buf) + (bufsize)))

/* @param: struct sig_post_completion   **ppost_completion_chain: ...
 * @param: struct sig_completion         *sc:                     ...
 * @param: struct sig_completion_context *context:                ... */
#define invoke_sig_completion(ppost_completion_chain, sc, context) \
	do {                                                           \
		size_t _pc_reqlen;                                         \
		(context)->scc_post = NULL;                                \
		_pc_reqlen = (*(sc)->sc_cb)(sc, context, NULL, 0);         \
		if (_pc_reqlen != 0 || (context)->scc_post != NULL) {      \
			struct sig_post_completion *_pc_ent;                   \
			for (;;) {                                             \
				size_t _pc_newlen;                                 \
				_pc_ent = sig_post_completion_alloc(_pc_reqlen);   \
				_pc_newlen = (*(sc)->sc_cb)(sc, context,           \
				                            _pc_ent->spc_buf,      \
				                            _pc_reqlen);           \
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



#ifndef CONFIG_NO_SMP
#define sig_completion_unlock(self) atomic_and(&(self)->tc_stat, ~TASK_CONNECTION_STAT_FLOCK)
LOCAL NOBLOCK void
NOTHROW(FCALL sig_unlock_pending)(struct sig_completion *sc_pending) {
	while (sc_pending) {
		struct sig_completion *next;
		next = (struct sig_completion *)sc_pending->tc_connext;
		sig_completion_unlock(sc_pending);
		sc_pending = next;
	}
}
#else /* !CONFIG_NO_SMP */
#define sig_completion_unlock(self) (void)0
#define sig_unlock_pending(chain)   (void)0
#endif /* CONFIG_NO_SMP */


/* Internal, extended signal broadcast function:
 *   #1: Perform a broadcast, alongside a number of optional, additional actions
 *   #2: Release all internal SMP-locks
 *   #3: Invoke `cleanup' (if non-NULL)
 *   #4: Restore the preemption behavior according to `was'
 *   #5: Destroy all  threads  who's  reference  counters  dropped to  0  in  the  mean  time
 *   #6: Invoke phase-2 completion callbacks, as have been registered by completion functions
 *   #7: Return the # of non-polling connections to which the signal was delivered
 * @param: self:            [1..1] The signal to broadcast
 * @param: sender:          [1..1] The sending signal (s.a. `sig_altbroadcast()')
 * @param: caller:          [1..1] The sending thread (s.a. `sig_broadcast_as()')
 * @param: sc_pending:      [0..1] When non-NULL, invoke this completion function,
 *                                 and  remember  it   as  having  been   invoked.
 * @param: destroy_later:   [0..1] A chain of threads that must be destroyed during step #5
 *                                 This chain  uses  `sig_destroylater_next()'  for  links.
 * @param: cleanup:         [0..1] When non-NULL, invoke this callback during step #3
 * @param: phase_one_state:        The state  that must  be written  to sig_completion  descriptors
 *                                 prior to invocation of their phase-1 callback. Should be one of:
 *                                  - TASK_CONNECTION_STAT_BROADCAST | TASK_CONNECTION_STAT_FLOCK_OPT | TASK_CONNECTION_STAT_FFINI
 *                                  - TASK_CONNECTION_STAT_BROADCAST | TASK_CONNECTION_STAT_FLOCK_OPT
 *                                 When   `TASK_CONNECTION_STAT_FFINI'   is   set,  this   will   prevent  the
 *                                 completion function from repriming itself (s.a. `sig_broadcast_for_fini()')
 * @param: was:                    The preemption-enabled state to restore during step #4
 * @return: * :                    The # of (additional, non-poll) connections that received the signal.
 *                                 Does  not   include  `sc_pending'   when   that  one   is   non-NULL. */
PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL sig_intern_broadcast)(struct sig *self,
                                    struct sig *sender,
                                    struct task *__restrict caller,
                                    struct sig_completion *sc_pending,
                                    struct task *destroy_later,
                                    struct sig_cleanup_callback *cleanup,
                                    uintptr_t phase_one_state,
                                    preemption_flag_t was) {
#ifndef CONFIG_NO_SMP
	uintptr_t ctl;
#endif /* !CONFIG_NO_SMP */
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	struct task_connections *target_cons;
	struct task_connection *receiver;
	struct task_connection *con;
	size_t result = 0;

	/* Signal completion callback. */
	context.scc_sender = sender;
	context.scc_caller = caller;
	if (sc_pending) {
		atomic_write(&sc_pending->tc_stat, phase_one_state);
		assert(sc_pending->tc_sig == self);
		invoke_sig_completion(&phase2, sc_pending, &context);
		sc_pending->tc_connext = NULL;
	}
again:
#ifdef CONFIG_NO_SMP
	con = atomic_read(&self->s_con);
#else /* CONFIG_NO_SMP */
	ctl = atomic_read(&self->s_ctl);
	assertf(sig_smplock_tst(ctl), "Caller must gift us this lock!");
	con = sig_smplock_clr(ctl);
#endif /* !CONFIG_NO_SMP */
	if (!con) {
no_cons:
		/* No one else here! (and nothing for us to do...) */
#if SIG_CONTROL_SMPLOCK != 0
		if (!atomic_cmpxch_weak(&self->s_ctl, ctl, (uintptr_t)con))
			goto again;
#endif /* SIG_CONTROL_SMPLOCK != 0 */

		/* Trigger phase #2 for pending signal-completion functions.
		 * NOTE: During this, the completion callback will clear the
		 *       SMP  lock  bit  of its  own  completion controller. */
		sig_unlock_pending(sc_pending);
		if (cleanup)
			(*cleanup->scc_cb)(cleanup);
		preemption_pop(&was);
		destroy_tasks(destroy_later);
		sig_run_phase_2(phase2, &context);
		return result;
	}
	if (!is_connection_in_chain(sc_pending, con)) {
		/* Use the first connection */
		receiver = con;
#ifndef CONFIG_NO_SMP
		assert(!sig_smplock_tst(receiver->tc_signext));
#endif /* !CONFIG_NO_SMP */

		/* Unlink `receiver' from the pending chain.
		 * IMPORTANT: During this operation, we must *retain* the SMP-lock to the signal,
		 *            since  said lock  is needed  for the  *ENTIRE* broadcast operation. */
#ifdef CONFIG_NO_SMP
		if (!atomic_cmpxch_weak(&self->s_con, con, sig_smplock_set((uintptr_t)receiver->tc_signext)))
			goto again;
#else /* CONFIG_NO_SMP */
		if (!atomic_cmpxch_weak(&self->s_ctl, ctl, sig_smplock_set((uintptr_t)receiver->tc_signext)))
			goto again;
#endif /* !CONFIG_NO_SMP */
	} else {
		/* Find another receiver (the first one was reprimed). */
		struct task_connection **preceiver;
		preceiver = &con->tc_signext;
		for (;;) {
			receiver = *preceiver;
			if (!receiver)
				goto no_cons;
			if (!is_connection_in_chain(sc_pending, receiver))
				break; /* Found a receiver that isn't a completion callback, or wasn't reprimed */
			preceiver = &receiver->tc_signext;
		}

		/* Unlink the receiver. */
		assert(*preceiver == receiver);
		*preceiver = receiver->tc_signext;
	}
#ifndef CONFIG_NO_SMP
again_read_target_cons:
	target_cons = atomic_read(&receiver->tc_cons);

	/* NOTE: Waiting until we can lock the connection here is allowed, since
	 *       you're allowed to  (and required to)  acquire connection  locks
	 *       without having to release the associated signal-lock.
	 * Doing  this doesn't result  in a race condition,  since the other end
	 * of this syncing mechanism (which is `task_disconnect()') will release
	 * its initial connection-lock if it  fails to acquire the signal  lock,
	 * which it will because we're already holding that one! */
	while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
		task_pause();
		target_cons = atomic_read(&receiver->tc_cons);
	}

	/* Mark the receiver for broadcast, and acquire a lock to it. */
	if (!atomic_cmpxch_weak(&receiver->tc_cons, target_cons,
	                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
	                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
		goto again_read_target_cons;
#else /* !CONFIG_NO_SMP */
	target_cons = atomic_xch(&receiver->tc_cons,
	                         (struct task_connections *)TASK_CONNECTION_STAT_BROADCAST);
#endif /* CONFIG_NO_SMP */

	if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
		struct sig_completion *sc;
		if (TASK_CONNECTION_STAT_ISDONE(target_cons)) {
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
			atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
			goto again;
		}
		sc = (struct sig_completion *)receiver;
		atomic_write(&sc->tc_stat, phase_one_state);

		/* Signal completion callback. */
		invoke_sig_completion(&phase2, sc, &context);

		/* Enqueue `sc' for unlock before phase #2. */
		sc->tc_connext = sc_pending;
		sc_pending     = sc;
	} else {
		target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);

		/* Try  to  set our  signal as  the  one delivered  to `target_cons'.
		 * If  that part fails, change signal state to BROADCAST (even though
		 * that's not entirely correct), so we can get rid of the connection. */
		if (!atomic_cmpxch(&target_cons->tcs_dlvr, NULL, sender)) {
			/* Unlink the signal, and mark it as broadcast. */
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
			atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
		} else {
			REF struct task *thread;
			/* Unlock the signal, and wake-up the thread attached to the connection */
			thread = xincref(atomic_read(&target_cons->tcs_thread));
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
			atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
			if likely(thread) {
				task_wake_as(thread, caller);
				assert(thread->t_refcnt >= 1);
				if unlikely(atomic_fetchdec(&thread->t_refcnt) == 1) {
					sig_destroylater_next(thread) = destroy_later;
					destroy_later                 = thread;
				}
			}
		}
	}
	goto again;
}

PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2, 3)) bool
NOTHROW(FCALL sig_intern_send)(struct sig *self,
                               struct sig *sender,
                               struct task *__restrict caller,
                               struct sig_completion *sc_pending,
                               struct task *destroy_later,
                               struct sig_cleanup_callback *cleanup,
                               preemption_flag_t was) {
	bool result;
#ifndef CONFIG_NO_SMP
	uintptr_t ctl;
#endif /* !CONFIG_NO_SMP */
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	struct task_connections *target_cons;
	struct task_connection *receiver;
	struct task_connection *con;
	context.scc_sender = sender;
	context.scc_caller = caller;

	/* Signal completion callback. */
	if (sc_pending) {
		invoke_sig_completion(&phase2, sc_pending, &context);
		sc_pending->tc_connext = NULL;
	}
again:
#ifdef CONFIG_NO_SMP
	con = atomic_read(&self->s_con);
#else /* CONFIG_NO_SMP */
	ctl = atomic_read(&self->s_ctl);
	con = sig_smplock_clr(ctl);
#endif /* !CONFIG_NO_SMP */
	if unlikely(!con) {
		/* No one else here! (and nothing for us to do...)
		 * This  is an  undefined situation,  since the  original call to
		 * `sig_send()' that caused the signal which we ended up ignoring
		 * to  be delivered returned `true', even though now, in the end,
		 * no one actually ended up getting the signal... */
#if SIG_CONTROL_SMPLOCK != 0
		if (!atomic_cmpxch_weak(&self->s_ctl, ctl, (uintptr_t)con))
			goto again;
#endif /* SIG_CONTROL_SMPLOCK != 0 */

		/* Trigger phase #2 for pending signal-completion functions.
		 * NOTE: During this, the completion callback will clear the
		 *       SMP  lock  bit  of its  own  completion controller. */
		result = false;
		goto done;
	}

	/* Find a suitable candidate:
	 *    During send:
	 *       #1: Use the last-in-chain, non-poll connection
	 *       #2: Broadcast all poll connections (but stop if
	 *           a non-poll connection shows up before we're
	 *           down)
	 *       #3: If no non-poll connection could be found,
	 *           return `false' */
	receiver = con;
	if (!receiver->tc_signext) {
		/* Special case: Only one connection to choose from... */
	} else {
		struct task_connection *iter;
		iter = receiver;
		if (TASK_CONNECTION_STAT_ISPOLL(receiver->tc_stat))
			receiver = NULL;

		/* Find the last non-poll connection. */
		do {
			if (!TASK_CONNECTION_STAT_ISPOLL(iter->tc_stat))
				receiver = iter;
		} while ((iter = iter->tc_signext) != NULL);
		if (!receiver) {
			/* No non-poll connections found.
			 * Just use the last connection in-chain. */
			receiver = sig_smplock_clr(con);
			while (receiver->tc_signext)
				receiver = receiver->tc_signext;
		}
	}
again_read_target_cons:
	target_cons = atomic_read(&receiver->tc_cons);

#ifndef CONFIG_NO_SMP
	/* NOTE: Waiting until we can lock the connection here is allowed, since
	 *       you're allowed to  (and required to)  acquire connection  locks
	 *       without having to release the associated signal-lock.
	 * Doing  this doesn't result  in a race condition,  since the other end
	 * of this syncing mechanism (which is `task_disconnect()') will release
	 * its initial connection-lock if it  fails to acquire the signal  lock,
	 * which it will because we're already holding that one! */
	while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
		task_pause();
		target_cons = atomic_read(&receiver->tc_cons);
	}
#endif /* !CONFIG_NO_SMP */

	if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
		struct sig_completion *sc;
		if unlikely(TASK_CONNECTION_STAT_ISDONE(target_cons)) {
			/* The target is already dead. (change it to broadcast) */
			if (!atomic_cmpxch_weak(&receiver->tc_cons, target_cons,
			                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
			                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
				goto again_read_target_cons;
			task_connection_unlink_from_sig(self, receiver);
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
			atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
			goto again;
		}

		/* Signal completion callback. */
		if (!atomic_cmpxch_weak(&receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again_read_target_cons;
		task_connection_unlink_from_sig(self, receiver);
		sc = (struct sig_completion *)receiver;

		/* Trigger phase #1 */
		invoke_sig_completion(&phase2, sc, &context);
		if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
			/* Enqueue the completion function so we don't re-trigger it. */
			sc->tc_signext = sc_pending;
			sc_pending     = sc;

			/* Search for more connections (preferably one that isn't poll-based) */
			goto again;
		}

		/* Unlock the signal. */
		sig_smplock_release_nopr(self);

		/* Instead of enqueuing `sc' to-be unlocked later, do so immediately. */
		sig_completion_unlock(sc);
		goto success;
	}

	/* Check if the selected receiver is poll-based */
	if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
		REF struct task *thread;
		/* Special case: poll-based connections don't (really) count.
		 * Instead, those get marked for broadcast. */
		if (!atomic_cmpxch_weak(&receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again_read_target_cons;
		task_connection_unlink_from_sig(self, receiver);
		target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
		thread = NULL;

		/* Set the delivered signal, and capture
		 * the thread  thread, if  there is  one */
		if (atomic_cmpxch(&target_cons->tcs_dlvr, NULL, sender))
			thread = xincref(atomic_read(&target_cons->tcs_thread));

		/* Unlock the connection. */
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
		atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
		if (thread) {
			task_wake_as(thread, caller);

			/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
			assert(thread->t_refcnt >= 1);
			if unlikely(atomic_fetchdec(&thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = destroy_later;
				destroy_later                 = thread;
			}
		}
		goto again;
	}

	/* Mark the receiver as sent, and acquire a lock to it. */
	if (!atomic_cmpxch_weak(&receiver->tc_cons, target_cons,
	                        (struct task_connections *)(TASK_CONNECTION_STAT_SENT |
	                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
		goto again_read_target_cons;

	/* Set the signal sender as being delivered for the target connection set. */
	if (!atomic_cmpxch(&target_cons->tcs_dlvr, NULL, sender)) {
		/* Unlink the signal, and mark it as broadcast. */
		task_connection_unlink_from_sig(self, receiver);
		atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
		goto again;
	}
	sig_smplock_release_nopr(self);

	/* The simple case:  We managed to  deliver the  signal,
	 * and now we must wake-up the connected thread (if any) */
	{
		REF struct task *thread;
		thread = xincref(atomic_read(&target_cons->tcs_thread));
		/* !!! Note that "received" is NOT removed from the signal's queue.
		 *     The signal only gets removed once the receiver  disconnects,
		 *     or the signal is broadcast. */
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
		atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_SENT);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */

		/* Wake-up the thread. */
		if likely(thread) {
			task_wake_as(thread, caller);

			/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
			assert(thread->t_refcnt >= 1);
			if unlikely(atomic_fetchdec(&thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = destroy_later;
				destroy_later                 = thread;
			}
		}
	}
success:
	result = true;
done:

	/* Trigger phase #2 for all of the pending completion function. */
	sig_unlock_pending(sc_pending);
	if (cleanup)
		(*cleanup->scc_cb)(cleanup);
	preemption_pop(&was);
	destroy_tasks(destroy_later);
	sig_run_phase_2(phase2, &context);
	return result;
}


PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2, 3, 4)) void
NOTHROW(FCALL sig_completion_runsingle)(struct sig *self,
                                        struct sig_completion *__restrict sc,
                                        struct task *__restrict caller,
                                        struct sig *sender,
                                        struct sig_cleanup_callback *cleanup,
                                        preemption_flag_t was) {
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	(void)self;
	context.scc_sender = sender;
	context.scc_caller = caller;

	/* Trigger phase #1 */
	invoke_sig_completion(&phase2, sc, &context);

	/* Release locks. */
	sig_completion_unlock(sc);
	sig_smplock_release_nopr(self);
	if (cleanup)
		(*cleanup->scc_cb)(cleanup);
	preemption_pop(&was);

	/* Run phase #2 callback. */
	sig_run_phase_2(phase2, &context);
}



/* Try to send the signal to a single, other thread, for the purpose
 * of  forwarding.  Additionally,  release  the  SMP-lock  of `self' */
PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2)) bool
NOTHROW(FCALL sig_sendone_for_forwarding_and_unlock)(struct sig *self,
                                                     struct sig *sender,
                                                     preemption_flag_t was) {
	bool result = false;
	bool is_broadcasting_poll = false;
#ifndef CONFIG_NO_SMP
	uintptr_t ctl;
#endif /* !CONFIG_NO_SMP */
	struct sig_completion *sc_pending = NULL;
	struct task_connections *target_cons;
	struct task_connection *receiver;
	struct task_connection *con;
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	REF struct task *destroy_later = NULL;
again:
#ifdef CONFIG_NO_SMP
	con = atomic_read(&self->s_con);
#else /* CONFIG_NO_SMP */
	ctl = atomic_read(&self->s_ctl);
	con = sig_smplock_clr(ctl);
#endif /* !CONFIG_NO_SMP */
	if unlikely(!con) {
no_cons:
		/* No one else here! (and nothing for us to do...)
		 * This  is an  undefined situation,  since the  original call to
		 * `sig_send()' that caused the signal which we ended up ignoring
		 * to  be delivered returned `true', even though now, in the end,
		 * no one actually ended up getting the signal... */
#if SIG_CONTROL_SMPLOCK != 0
		con = sig_smplock_clr(ctl);
		if (!atomic_cmpxch_weak(&self->s_ctl, ctl, (uintptr_t)con))
			goto again;
#endif /* SIG_CONTROL_SMPLOCK != 0 */
		result = false;
		preemption_pop(&was);
		goto done;
	}

	/* Non-broadcast signals are sent to the oldest connection of  `self'.
	 * As such, walk the chain of known connections until we find the last
	 * one of them all.
	 * NOTE: Since we're holding the SMP-lock at the moment, we are safe to
	 *       do this. */
	receiver = NULL;

	/* Find the first connection that is able to accept the signal. */
	for (;;) {
		uintptr_t status;
		status = atomic_read(&con->tc_stat);
		assert(status != TASK_CONNECTION_STAT_BROADCAST);
		if (!TASK_CONNECTION_STAT_ISDONE(status)) {
			if (is_broadcasting_poll || !TASK_CONNECTION_STAT_ISPOLL(status)) {
				/* Make sure that  `con' isn't a  phase-2-pending completion  callback.
				 * If it is, then the callback of `con' used `sig_completion_reprime()'
				 * during phase-1 in order to re-queue itself. */
				if (!is_connection_in_chain(sc_pending, con))
					receiver = con; /* This connection is still in alive. */
			}
		}
		con = con->tc_signext;
		if (!con)
			break;
	}
	if unlikely(!receiver) {
		if (is_broadcasting_poll)
			goto no_cons;
		is_broadcasting_poll = true;
		goto again;
	}

	/* Try to switch the connection from `!TASK_CONNECTION_STAT_ISDONE'
	 * to `TASK_CONNECTION_STAT_SENT'. */
	target_cons = atomic_read(&receiver->tc_cons);

#ifndef CONFIG_NO_SMP
	/* NOTE: Waiting until we can lock the connection here is allowed, since
	 *       you're allowed to  (and required to)  acquire connection  locks
	 *       without having to release the associated signal-lock.
	 * Doing  this doesn't result  in a race condition,  since the other end
	 * of this syncing mechanism (which is `task_disconnect()') will release
	 * its initial connection-lock if it  fails to acquire the signal  lock,
	 * which it will because we're already holding that one! */
	while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
		task_pause();
		target_cons = atomic_read(&receiver->tc_cons);
	}
#endif /* !CONFIG_NO_SMP */
	if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
		struct sig_completion *sc;
		if unlikely(TASK_CONNECTION_STAT_ISDONE(target_cons))
			goto again;
		sc = (struct sig_completion *)receiver;
		if (!atomic_cmpxch_weak(&sc->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again;

		/* Unlink `sc' from the signal. */
		task_connection_unlink_from_sig(self, receiver);

		/* Signal completion callback. */
		context.scc_sender = sender;
		context.scc_caller = THIS_TASK;
		invoke_sig_completion(&phase2, sc, &context);

		/* Enqueue `sc' for unlock before phase #2. */
		sc->tc_connext = sc_pending;
		sc_pending     = sc;
		if unlikely(TASK_CONNECTION_STAT_ISPOLL(target_cons))
			goto again; /* Deal with poll-based connections. */
	} else {
		struct task *thread;
		if (!atomic_cmpxch_weak(&receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_SENT |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again;
		if unlikely(TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
			/* Deal with poll-based connections. */
			bool did_deliver;
			target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
			did_deliver = atomic_cmpxch(&target_cons->tcs_dlvr, NULL, sender);
			task_connection_unlink_from_sig(self, receiver);
			if (did_deliver) {
				thread = atomic_read(&target_cons->tcs_thread);
				if likely(thread)
					task_wake(thread);
			}
			atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			goto again;
		}

		/* Try  to  set our  signal as  the  one delivered  to `target_cons'.
		 * If  that part fails, change signal state to BROADCAST (even though
		 * that's not entirely correct), so we can get rid of the connection. */
		if (!atomic_cmpxch(&target_cons->tcs_dlvr, NULL, sender)) {
			/* Unlink the signal, and mark it as broadcast. */
			task_connection_unlink_from_sig(self, receiver);
			atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			goto again;
		}

		/* Unlock the signal, and wake-up the thread attached to the connection */
		thread = xincref(atomic_read(&target_cons->tcs_thread));
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
		atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_SENT);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
		sig_smplock_release_nopr(self);
		preemption_pop(&was);
		if likely(thread) {
			task_wake(thread);
			assert(thread->t_refcnt >= 1);
			if unlikely(atomic_fetchdec(&thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = destroy_later;
				destroy_later                 = thread;
			}
		}
	}
	result = true;
done:

	/* Trigger phase #2 for pending signal-completion functions.
	 * NOTE: During this, the completion callback will clear the
	 *       SMP  lock  bit  of its  own  completion controller. */
	sig_unlock_pending(sc_pending);
	preemption_pop(&was);

	/* Invoke phase-2 callbacks. */
	sig_run_phase_2(phase2, &context);

	/* Destroy pending threads. */
	destroy_tasks(destroy_later);
	return result;
}




/* Re-prime  the completion callback to be invoked once again the next time that the
 * attached signal is delivered. This function is a no-op if the caller's completion
 * function was invoked from `sig_broadcast_for_fini()'.
 *
 * NOTE: If used, this  function must be  called from  `sig_completion_t()'.
 *       It cannot be used from a phase-2 (post) signal-completion callback.
 * WARNING: Call this function at most once from `sig_completion_t()'. Else,
 *          you'll cause hard undefined behavior, that'll probably end in  a
 *          system crash.
 * @param: for_poll: True if the new connection should be poll-based (s.a. `task_connect_for_poll()')
 * @return: true:  Re-priming was successful.
 * @return: false: Re-priming failed because the sender used `sig_broadcast_for_fini()'. */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) bool
NOTHROW(KCALL sig_completion_reprime)(struct sig_completion *__restrict self,
                                      bool for_poll) {
	struct task_connection *next;
	struct sig *signal = self->tc_sig;

	/* At this point, we're allowed to assume all of the following: */
	assert(!preemption_ison());
#ifndef CONFIG_NO_SMP
	assert(signal->s_ctl & SIG_CONTROL_SMPLOCK);
	assert(self->tc_stat & TASK_CONNECTION_STAT_FLOCK);
#endif /* !CONFIG_NO_SMP */

	/* If the signal was sent for the purpose of finalization, then don't
	 * allow completion callback re-priming, since we're supposed to take
	 * care of all connections going away. */
	if unlikely(self->tc_stat & TASK_CONNECTION_STAT_FFINI)
		return false;

	/* Re-write the status of `self' to match the request. */
	atomic_write(&self->tc_stat,
	             for_poll ? TASK_CONNECTION_STAT_FLOCK_OPT | TASK_CONNECTION_STAT_COMPLETION_FOR_POLL
	                      : TASK_CONNECTION_STAT_FLOCK_OPT | TASK_CONNECTION_STAT_COMPLETION);

	/* Now we must insert `self' into the chain of `signal' */
	do {
		next = atomic_read(&signal->s_con);
#ifndef CONFIG_NO_SMP
		assert(sig_smplock_tst(next));
#endif /* !CONFIG_NO_SMP */
		self->tc_signext = sig_smplock_clr(next);
		assertf(self != sig_smplock_clr(next), "Duplicate connection?");
		COMPILER_WRITE_BARRIER();
	} while (!atomic_cmpxch_weak(&signal->s_con, next,
	                             sig_smplock_set(self)));
	return true;
}

/* Connect the given signal completion controller to the specified signal.
 * The caller must  ensure that `completion'  hasn't been connected,  yet. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion)(struct sig *__restrict self,
                                      struct sig_completion *__restrict completion) {
	struct task_connection *next;

	/* Re-write the status of `self' to match the request. */
	completion->tc_stat = TASK_CONNECTION_STAT_COMPLETION;
	completion->tc_sig  = self;
	DBG_memset(&completion->tc_connext, 0xcc,
	           sizeof(completion->tc_connext));

	/* Now we must insert `completion' into the chain of `self' */
	do {
		next = atomic_read(&self->s_con);
		completion->tc_signext = sig_smplock_clr(next);
		assertf(completion != sig_smplock_clr(next), "Duplicate connection?");
		COMPILER_WRITE_BARRIER();
	} while (!atomic_cmpxch_weak(&self->s_con, next,
	                             sig_smplock_cpy(completion, next)));
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion_for_poll)(struct sig *__restrict self,
                                               struct sig_completion *__restrict completion) {
	struct task_connection *next;

	/* Re-write the status of `self' to match the request. */
	completion->tc_stat = TASK_CONNECTION_STAT_COMPLETION_FOR_POLL;
	completion->tc_sig  = self;
	DBG_memset(&completion->tc_connext, 0xcc,
	           sizeof(completion->tc_connext));

	/* Now we must insert `completion' into the chain of `self' */
	do {
		next = atomic_read(&self->s_con);
		completion->tc_signext = sig_smplock_clr(next);
		assertf(completion != sig_smplock_clr(next), "Duplicate connection?");
		COMPILER_WRITE_BARRIER();
	} while (!atomic_cmpxch_weak(&self->s_con, next,
	                             sig_smplock_cpy(completion, next)));
}




LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_disconnect_connection)(struct task_connection *__restrict self,
                                          struct task_connections *__restrict cons,
                                          bool forward_sent_signals) {
	struct sig *signal;
	struct task_connection *signal_cons;
	preemption_flag_t was;
	uintptr_t status;
	signal = self->tc_sig;

	/* Acquire a lock to the connection. */
#ifdef CONFIG_NO_SMP
	preemption_pushoff(&was);
	status = atomic_read(&self->tc_stat);
	if (TASK_CONNECTION_STAT_ISDEAD(status)) {
		preemption_pop(&was);
		goto done; /* Dead connection */
	}
	signal_cons = atomic_read(&signal->s_con);
#else /* CONFIG_NO_SMP */
again:
	status = atomic_read(&self->tc_stat);
	if unlikely(status & TASK_CONNECTION_STAT_FLOCK) {
		task_pause();
		goto again;
	}
	if (TASK_CONNECTION_STAT_ISDEAD(status))
		goto done; /* Dead connection */
	preemption_pushoff(&was);
	if (!atomic_cmpxch_weak(&self->tc_stat, status,
	                        status | TASK_CONNECTION_STAT_FLOCK)) {
		preemption_pop(&was);
		goto again;
	}

	/* Now upgrade the lock to also include the associated signal. */
again_signal_cons:
	signal_cons = atomic_read(&signal->s_con);
	if unlikely(sig_smplock_tst(signal_cons)) {
		atomic_and(&self->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
		preemption_pop(&was);
		task_pause();
		goto again;
	}
	if (!atomic_cmpxch_weak(&signal->s_con, signal_cons,
	                        sig_smplock_set(signal_cons)))
		goto again_signal_cons;
#endif /* !CONFIG_NO_SMP */

	/* At this point, we're holding all of the necessary locks, both
	 * to `self' and `signal'. With that in mind, remove `self' from
	 * the connection queue of `signal' */
	if likely(status != TASK_CONNECTION_STAT_SENT || !forward_sent_signals) {
		/* Unlink our connection, and unlock the signal. */
		task_connection_unlink_from_sig_and_unlock(signal, self);
		preemption_pop(&was);
	} else {
		/* Unlink our connection. */
		task_connection_unlink_from_sig(signal, self);

		/* Forward the signal. */
		if (!sig_sendone_for_forwarding_and_unlock(signal,
		                                           atomic_read(&cons->tcs_dlvr),
		                                           was)) {
			/* At least log the fact that there has been a minor inconsistency... */
			printk(KERN_WARNING "[sig] Signal %p cannot be forwarded (no recipients)\n",
			       self);
		}
	}
done:
	DBG_memset(&self->tc_sig, 0xcc, sizeof(self->tc_sig));
}

/* NOTE: When  this  function returns,  the caller  can be  certain that  the callback
 *       of `self' is/won't be executed anymore, unless `self' is once again connected
 *       to some signal through use of `sig_connect_completion[_for_poll]()'
 * @return: true:  Completion function was disconnected before it could be  triggered,
 *                 or the last time the completion function was triggered, it made use
 *                 of `sig_completion_reprime()' to re-prime itself.
 * @return: false: Completion  function was already triggered, but not re-primed.
 *                 Alternatively, the signal completion function had already been
 *                 disconnected, or had never been connected to begin with. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sig_completion_disconnect)(struct sig_completion *__restrict self) {
	struct sig *signal;
	struct task_connection *signal_cons;
	preemption_flag_t was;
	uintptr_t status;
	signal = self->tc_sig;

	/* Acquire a lock to the connection. */
#ifdef CONFIG_NO_SMP
	preemption_pushoff(&was);
	status = atomic_read(&self->tc_stat);
	if (TASK_CONNECTION_STAT_ISDONE(status)) {
		preemption_pop(&was);
		return false; /* Dead connection */
	}
	assert(status == TASK_CONNECTION_STAT_COMPLETION ||
	       status == TASK_CONNECTION_STAT_COMPLETION_FOR_POLL);
	signal_cons = atomic_read(&signal->s_con);
#else /* CONFIG_NO_SMP */
again:
	status = atomic_read(&self->tc_stat);
	if unlikely(status & TASK_CONNECTION_STAT_FLOCK) {
		task_pause();
		goto again;
	}
	if (TASK_CONNECTION_STAT_ISDONE(status))
		return false; /* Dead connection */
	assert(status == TASK_CONNECTION_STAT_COMPLETION ||
	       status == TASK_CONNECTION_STAT_COMPLETION_FOR_POLL);
	preemption_pushoff(&was);
	if (!atomic_cmpxch_weak(&self->tc_stat, status,
	                        status | TASK_CONNECTION_STAT_FLOCK)) {
		preemption_pop(&was);
		goto again;
	}

	/* Now upgrade the lock to also include the associated signal. */
again_signal_cons:
	signal_cons = atomic_read(&signal->s_con);
	if unlikely(sig_smplock_tst(signal_cons)) {
		atomic_and(&self->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
		preemption_pop(&was);
		task_pause();
		goto again;
	}
	if (!atomic_cmpxch_weak(&signal->s_con, signal_cons,
	                        sig_smplock_set(signal_cons)))
		goto again_signal_cons;
#endif /* !CONFIG_NO_SMP */

	/* At this point, we're holding all of the necessary locks, both
	 * to `self' and `signal'. With that in mind, remove `self' from
	 * the connection queue of `signal' */
	task_connection_unlink_from_sig_and_unlock(signal, self);
	preemption_pop(&was);
	DBG_memset(&self->tc_sig, 0xcc, sizeof(self->tc_sig));
	DBG_memset(&self->tc_connext, 0xcc, sizeof(self->tc_connext));
	DBG_memset(&self->tc_signext, 0xcc, sizeof(self->tc_signext));
	COMPILER_WRITE_BARRIER();
	self->tc_stat = TASK_CONNECTION_STAT_BROADCAST;
	return true;
}


/* Disconnect from a specific signal `target'
 * WARNING: If `target' was already  send to the calling  thread
 *          before it could  be disconnected  by this  function,
 *          the calling  thread will  continue  to remain  in  a
 *          signaled state, such  that the next  call to one  of
 *          the signal receive functions (e.g. `task_waitfor()')
 *          will not block.
 * @return: true:  Disconnected from `target'
 * @return: false: You weren't actually connected to `target' */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target) {
	struct task_connections *self;
	struct task_connection **p_con, *con;
	self = THIS_CONNECTIONS;
	for (p_con = &self->tcs_con; (con = *p_con) != NULL;
	     p_con = &con->tc_connext) {
		if (con->tc_sig != target)
			continue; /* Some other signal... */

		/* Disconnect */
		task_disconnect_connection(con, self, true);

		/* Unlink */
		*p_con = con->tc_connext;

		/* Free */
		task_connection_free(self, con);
		return true;
	}
	return false;
}


LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_connection_disconnect_all)(struct task_connections *__restrict self,
                                              bool forward_sent_signals) {
	struct task_connection *con;
	while ((con = self->tcs_con) != NULL) {

		/* Disconnect */
		task_disconnect_connection(con, self, forward_sent_signals);

		/* Unlink */
		self->tcs_con = con->tc_connext;

		/* Free */
		task_connection_free(self, con);
	}
}

/* Disconnect from all connected signals.
 * Signals with a state of `TASK_CONNECTION_STAT_SENT' will be forwarded. */
PUBLIC NOBLOCK void
NOTHROW(FCALL task_disconnectall)(void) {
	struct task_connections *self;
	self = THIS_CONNECTIONS;
	task_connection_disconnect_all(self, true);
	COMPILER_BARRIER();
	self->tcs_dlvr = NULL;
}

/* Same as `task_disconnectall()', but don't forward signals with a
 * `TASK_CONNECTION_STAT_SENT'-state, but rather return the  sender
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
	struct task_connections *self;
	struct sig *result;
	self = THIS_CONNECTIONS;
	task_connection_disconnect_all(self, false);
	COMPILER_BARRIER();
	result = self->tcs_dlvr;
	self->tcs_dlvr = NULL;
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
NOTHROW(FCALL task_wasconnected)(void) {
	struct task_connections *self;
	self = THIS_CONNECTIONS;

	/* Check if there are any active connections. */
	return self->tcs_con != NULL;
}

/* Check if the calling thread was connected to the given signal.
 * Always returns `false' when `target == NULL'. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL task_wasconnected_to)(struct sig const *target) {
	struct task_connections *self;
	struct task_connection *con;
	self = THIS_CONNECTIONS;

	/* Find the connection for `target' */
	for (con = self->tcs_con; con; con = con->tc_connext) {
		if (con->tc_sig == target)
			return true; /* Found it! */
	}
	return false;
}

/* Check if there is a signal that was delivered,
 * disconnecting all other  connected signals  if
 * this was the case.
 * @return: NULL: No signal is available.
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
PUBLIC NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_trywait)(void) {
	struct task_connections *self;
	struct sig *result;
	self   = THIS_CONNECTIONS;
	result = atomic_read(&self->tcs_dlvr);
	if (result) {
		task_connection_disconnect_all(self, false);
		COMPILER_BARRIER();
		self->tcs_dlvr = NULL;
	}
	return result;
}



/* Check if the given signal has viable recipients.
 * This     includes     poll-based    connections. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sig_iswaiting)(struct sig *__restrict self) {
	bool result = false;
	struct task_connection *cons;

	/* Quick check: Are there any established connections? */
	cons = sig_smplock_clr(atomic_read(&self->s_con));
	if (cons) {
		/* Acquire the SMP-lock for `self', so we can inspect
		 * the chain of established connections more closely. */
		sig_smplock_acquire(self);
		for (cons = sig_smplock_clr(atomic_read(&self->s_con));
		     cons; cons = cons->tc_signext) {
			uintptr_t status = atomic_read(&cons->tc_stat);
			if (!TASK_CONNECTION_STAT_ISDONE(status)) {
				/* Found an alive, normal connection! */
				result = true;
				break;
			}
		}
		sig_smplock_release(self);
	}
	return result;
}

/* Count the # of viable recipients of the given signal.
 * This includes poll-based connections. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_numwaiting)(struct sig *__restrict self) {
	size_t result = 0;
	struct task_connection *cons;

	/* Quick check: Are there any established connections? */
	cons = sig_smplock_clr(atomic_read(&self->s_con));
	if (cons) {
		/* Acquire the SMP-lock for `self', so we can inspect
		 * the chain of established connections more closely. */
		sig_smplock_acquire(self);
		for (cons = sig_smplock_clr(atomic_read(&self->s_con));
		     cons; cons = cons->tc_signext) {
			uintptr_t status;
			status = atomic_read(&cons->tc_stat);
			if (!TASK_CONNECTION_STAT_ISDONE(status))
				++result; /* Found an alive, normal connection! */
		}
		sig_smplock_release(self);
	}
	return result;
}



/************************************************************************/
/* SIGNAL MULTI-COMPLETION API                                          */
/************************************************************************/

/* Finalize a given signal multi-completion controller.
 * WARNING: This  function will _not_  disconnect any remaining signals.
 *          If active connections could possibly remain, it is up to the
 *          caller to call `sig_multicompletion_disconnectall()'  first! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_fini)(struct sig_multicompletion *__restrict self) {
	struct _sig_multicompletion_set *ext;

	/* Make sure that `self' isn't still connected. */
	assert(!sig_multicompletion_wasconnected(self));

	/* Free all extended connection sets. */
	ext = self->sm_set.sms_next;
	DBG_memset(self, 0xcc, sizeof(*self));
	while (ext) {
		struct _sig_multicompletion_set *next;
		next = ext->sms_next;
		kfree(ext);
		ext = next;
	}
}


/* Serve all (still-alive) connections that are active for `self'. Note that this  function
 * may not be called from inside of signal-completion-callbacks, or any other callback that
 * may  be executed in the context of holding an SMP-lock. (though you area allowed to call
 * this function from a `sig_postcompletion_t' callback) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_disconnectall)(struct sig_multicompletion *__restrict self) {
	struct _sig_multicompletion_set *set;
	set = &self->sm_set;
	do {
		unsigned int i;
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
#ifndef __OPTIMIZE_SIZE__
			if (set->sms_routes[i].tc_stat != TASK_CONNECTION_STAT_BROADCAST)
#endif /* !__OPTIMIZE_SIZE__ */
			{
				sig_completion_disconnect(&set->sms_routes[i]);
			}
		}
	} while ((set = set->sms_next) != NULL);
}

/* Check if the given signal multi-completion controller `self' was connected. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sig_multicompletion_wasconnected)(struct sig_multicompletion const *__restrict self) {
	struct _sig_multicompletion_set const *set;
	set = &self->sm_set;
	do {
		unsigned int i;
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
			if (sig_completion_wasconnected(&set->sms_routes[i]))
				return true;
		}
	} while ((set = set->sms_next) != NULL);
	return false;
}


/* Allocate and return a new signal completion descriptor that  is
 * attached  to the signal multi-completion controller `self', and
 * will invoke `cb' when triggered. The returned pointer is  owned
 * by  `self', meaning that the caller doesn't have to bother with
 * ownership themself. Also  note that this  these functions  will
 * keep on returning the same completion until that completion has
 * been connected, and will re-use older completions if those  got
 * tripped, but didn't re-prime themself.
 *
 * If all of that sounds too complicated for you, then just use
 * `sig_connect_multicompletion', which encapsulates the job of
 * allocating+connecting to a signal for you. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct sig_completion *FCALL
sig_multicompletion_alloc(struct sig_multicompletion *__restrict self,
                          sig_completion_t cb)
		THROWS(E_BADALLOC) {
	struct _sig_multicompletion_route *result;
	struct _sig_multicompletion_set *set;
	unsigned int i;
	set = &self->sm_set;
	do {
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
			result = &set->sms_routes[i];
			if (result->tc_stat == TASK_CONNECTION_STAT_BROADCAST)
				goto done; /* Unused completion entry. */
		}
	} while ((set = set->sms_next) != NULL);

	/* Must allocate a new set of completion descriptors.
	 * NOTE: These descriptors must be allocated as LOCKED, since they're made
	 *       use of  by code  that may  be running  with preemption  disabled. */
	set = (struct _sig_multicompletion_set *)kmalloc(sizeof(struct _sig_multicompletion_set),
	                                                 GFP_LOCKED | GFP_PREFLT);
	for (i = 0; i < lengthof(self->sm_set.sms_routes); ++i)
		set->sms_routes[i].tc_stat = TASK_CONNECTION_STAT_BROADCAST;

	/* Insert the set into the list of known sets. */
	set->sms_next         = self->sm_set.sms_next;
	self->sm_set.sms_next = set;

	/* Use the first descriptor from the newly allocated set. */
	result = &set->sms_routes[0];
done:
	result->mr_con = self;
	result->sc_cb  = cb;
	return result;
}

PUBLIC WUNUSED NONNULL((1)) struct sig_completion *
NOTHROW(FCALL sig_multicompletion_alloc_nx)(struct sig_multicompletion *__restrict self,
                                            sig_completion_t cb) {
	struct _sig_multicompletion_route *result;
	struct _sig_multicompletion_set *set;
	unsigned int i;
	set = &self->sm_set;
	do {
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
			result = &set->sms_routes[i];
			if (result->tc_stat == TASK_CONNECTION_STAT_BROADCAST)
				goto done; /* Unused completion entry. */
		}
	} while ((set = set->sms_next) != NULL);

	/* Must allocate a new set of completion descriptors.
	 * NOTE: These descriptors must be allocated as LOCKED, since they're made
	 *       use of  by code  that may  be running  with preemption  disabled. */
	set = (struct _sig_multicompletion_set *)kmalloc_nx(sizeof(struct _sig_multicompletion_set),
	                                                    GFP_LOCKED | GFP_PREFLT);
	if unlikely(!set)
		return NULL; /* Allocation failed. */
	for (i = 0; i < lengthof(self->sm_set.sms_routes); ++i)
		set->sms_routes[i].tc_stat = TASK_CONNECTION_STAT_BROADCAST;

	/* Insert the set into the list of known sets. */
	set->sms_next         = self->sm_set.sms_next;
	self->sm_set.sms_next = set;

	/* Use the first descriptor from the newly allocated set. */
	result = &set->sms_routes[0];
done:
	result->mr_con = self;
	result->sc_cb  = cb;
	return result;
}

/* Allocate a completion descriptor from `completion' and connect it to `self' */
PUBLIC NOBLOCK NONNULL((1, 2, 3)) void FCALL
sig_connect_multicompletion(struct sig *__restrict self,
                            struct sig_multicompletion *__restrict completion,
                            sig_completion_t cb)
		THROWS(E_BADALLOC) {
	struct sig_completion *route;
	route = sig_multicompletion_alloc(completion, cb);
	sig_connect_completion(self, route);
}

/* No-except version of `sig_connect_multicompletion()'. Returns `false' if no
 * completion descriptor could be allocated from the pool of `completion', and
 * `true' if a completion descriptor  could be allocated and was  subsequently
 * connected. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL sig_connect_multicompletion_nx)(struct sig *__restrict self,
                                              struct sig_multicompletion *__restrict completion,
                                              sig_completion_t cb) {
	struct sig_completion *route;
	route = sig_multicompletion_alloc_nx(completion, cb);
	if unlikely(!route)
		return false;
	sig_connect_completion(self, route);
	return true;
}


/* Connect `completion' to all signals currently connected to by the calling thread.
 * In other words: all signals the caller is connected to via `task_connect()'. Note
 * that  for  this purpose,  only  signals from  the  currently active  set  of task
 * connections  will be connected. Connections established outside the bounds of the
 * current  `task_pushconnections()...task_popconnections()'  pair  will  _NOT_   be
 * connected. If one of  the signals which  the calling thread  is connected to  has
 * already been sent (i.e. `task_waitfor()' wouldn't block), then this function will
 * return early, and the exact (if any) signals that were connected to  `completion'
 * are left undefined (meaning that the caller can really only handle this happening
 * by using `sig_multicompletion_disconnectall()',  but also meaning  that `cb'  may
 * still  get invoked in case the caller was  connected to more than one signal, and
 * more than one  of those  gets triggered  before connections  of `completion'  get
 * disconnected) As such, the safe way to use this function is as follows (exception
 * handling not displayed for brevity):
 * >> task_connect(&foo);
 * >> task_connect(&bar);
 * >> task_connect(&foobar);
 * >> ...
 * >> struct sig_multicompletion smc;
 * >> sig_multicompletion_init(&smc);
 * >> sig_multicompletion_connect_from_task(&smc, &my_callback);
 * >> if (task_receiveall()) {  // Or `task_trywait()' if per-task
 * >>                           // connections should remain
 * >>     sig_multicompletion_disconnectall(&smc);
 * >>     // Error:   One of the caller's signals may have already
 * >>     //          been delivered before `smc' could connect to
 * >>     //          all of them.
 * >> } else {
 * >>     // Success: Connections established (calling thread is no longer connected)
 * >> }
 * This function is used to implement epoll objects using the regular,
 * old poll-api already exposed via `handle_poll()', without the  need
 * of complicating that existing ABI. */
PUBLIC NOBLOCK NONNULL((1)) void FCALL
sig_multicompletion_connect_from_task(struct sig_multicompletion *__restrict completion,
                                      sig_completion_t cb, bool for_poll)
		THROWS(E_BADALLOC) {
	struct task_connection *con;
	struct task_connections *cons;
	uintptr_t newroute_status;
	cons = THIS_CONNECTIONS;
#ifndef __OPTIMIZE_SIZE__
	/* Quick check: was one of the calling thread's signals already delivered? */
	if (cons->tcs_dlvr != NULL)
		return;
#endif /* !__OPTIMIZE_SIZE__ */
	newroute_status = for_poll ? TASK_CONNECTION_STAT_COMPLETION_FOR_POLL
	                           : TASK_CONNECTION_STAT_COMPLETION;
	for (con = cons->tcs_con; con; con = con->tc_connext) {
		struct sig_completion *route;
		struct task_connection *signext;
		struct sig *signal;
		preemption_flag_t was;
		route  = sig_multicompletion_alloc(completion, cb);
		signal = con->tc_sig;

		/* Initialize `route' as needed prior to a connection being made. */
		route->tc_stat = newroute_status;
		route->tc_sig  = signal;
		DBG_memset(&route->tc_connext, 0xcc, sizeof(route->tc_connext));

		/* This is where it gets complicated, because we must:
		 *    #1: Disable preemption
		 *    #2: Acquire the SMP-lock of `con', and make sure that  `con'
		 *        hasn't been delivered,  yet. This way  we know that  the
		 *        signal pointed to by `con->tc_sig' hasn't been destroyed
		 *        yet, either.
		 *    #3: While holding the  SMP-lock of `con',  insert our  new
		 *        connection `route' into the signal's connection queue.
		 *    #4: Release our SMP-lock on `con'
		 *    #5: Re-enable preemption (if it was enabled before)
		 *
		 * Note  that in order to append a connection onto the wait-queue
		 * of  some signal, one normally doesn't need to acquire any SMP-
		 * locks. In this case however, we still need to acquire the SMP-
		 * lock  of `con', with  which we can prevent  any other CPU from
		 * (fully) broadcasting the attached signal as part of finalizing
		 * that signal (~ala `sig_broadcast_for_fini()') */

		/* Step #1 */
		preemption_pushoff(&was);

		/* Step #2 */
#ifndef CONFIG_NO_SMP
		for (;;)
#endif /* !CONFIG_NO_SMP */
		{
			uintptr_t status;
			status = atomic_read(&con->tc_stat);
			if (TASK_CONNECTION_STAT_ISSPEC(status)) {
				assertf(!TASK_CONNECTION_STAT_ISCOMP(status),
				        "This should be a task connection, so why does "
				        /**/ "its status indicate a completion function?\n"
				        "status = %#" PRIxPTR,
				        status);

				/* Connection is already dead.
				 * Abort everything and  make sure  that our  thread's
				 * delivered-connection field is non-NULL (since  that
				 * field may not have been set yet by whoever had sent
				 * the signal) */
				preemption_pop(&was);

				/* Mark  `route'  as  unused  (since  it  was  never  fully connected)
				 * This  must be  done to ensure  that `self' remains  in a consistent
				 * state in regards to finalization (or rather: disconnect in general) */
				route->tc_stat = TASK_CONNECTION_STAT_BROADCAST;

#ifdef CONFIG_NO_SMP
				assert(atomic_read(&cons->tcs_dlvr) != NULL);
#else /* CONFIG_NO_SMP */

				/* If  the signal was  send by some  other CPU, our thread's
				 * delivered-signal field may not have become non-NULL, yet.
				 * In this case, simply pause until that happens. */
				while (atomic_read(&cons->tcs_dlvr) == NULL)
					task_tryyield_or_pause();
#endif /* !CONFIG_NO_SMP */
				return;
			}

#ifndef CONFIG_NO_SMP
			/* Make sure that `con' isn't already locked. */
			if unlikely(status & TASK_CONNECTION_STAT_FLOCK) {
				/* Pausing w/ preemption may  do better than pausing  w/o
				 * As such, try to re-enable preemption while we do this. */
				preemption_tryyield_f(&was);
				continue;
			}

			/* Acquire a lock to `con' */
			if (atomic_cmpxch_weak(&con->tc_stat,
			                       status,
			                       status | TASK_CONNECTION_STAT_FLOCK))
				break;
#endif /* !CONFIG_NO_SMP */
		}

		/* Step #3 (Do the actual job of inserting `route' into the signal) */
		do {
			signext = atomic_read(&signal->s_con);
			route->tc_signext = sig_smplock_clr(signext);
			assertf(route != sig_smplock_clr(signext), "Duplicate connection?");
			COMPILER_WRITE_BARRIER();
		} while (!atomic_cmpxch_weak(&signal->s_con, signext,
		                             sig_smplock_cpy(route, signext)));

#ifndef CONFIG_NO_SMP
		/* Step #4 */
		atomic_and(&con->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
#endif /* !CONFIG_NO_SMP */

		/* Step #5 */
		preemption_pop(&was);
	}
}



/* Same as `sig_send()', but repeat the operation up to `maxcount' times,
 * and return the # of times that `sig_send()' would have returned `true'
 * Equivalent to:
 * >> size_t result = 0;
 * >> while (maxcount) {
 * >>     if (!sig_send(self))
 * >>         break;
 * >>     --maxcount;
 * >>     ++result;
 * >> }
 * >> return result; */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_sendmany)(struct sig *__restrict self,
                            size_t maxcount) {
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_broadcast(self);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_send(self))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}

PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altsendmany)(struct sig *self,
                               struct sig *sender,
                               size_t maxcount) {
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_altbroadcast(self, sender);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_altsend(self, sender))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}

PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_sendmany_nopr)(struct sig *__restrict self,
                                 size_t maxcount) {
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_broadcast_nopr(self);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_send_nopr(self))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}

PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altsendmany_nopr)(struct sig *self,
                                    struct sig *sender,
                                    size_t maxcount) {
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_altbroadcast_nopr(self, sender);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_altsend_nopr(self, sender))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}




/* Send  a signal to the oldest (and preferably non-poll-based) connection of
 * `self' for which `selector'  returns non-NULL. Connections are  enumerated
 * twice from oldest to most recent, only including non-poll-based during the
 * first pass, and only including poll-based ones during the second pass.
 * @param: self:     The signal which should be sent.
 * @param: selector: A selector callback that can be used to select the
 *                   connection that should be sent.
 * @param: cookie:   An argument that should be passed to `selector'
 * @param: caller:   The (supposed) calling thread (s.a. `sig_broadcast_as()')
 * @param: cleanup:  When non-NULL, an optional cleanup callback (s.a. `sig_broadcast_cleanup_nopr()')
 * @param: run_cleanup_when_notarget: If true, also run `cleanup' when returning `SIG_SEND_SELECT_NOTARGET'
 * @return: * :      One of `SIG_SEND_SELECT_*' */
PUBLIC NOBLOCK NONNULL((1, 2, 4)) unsigned int
NOTHROW(FCALL sig_send_select_as)(struct sig *__restrict self,
                                  sig_send_selector_t selector, void *cookie,
                                  struct task *__restrict caller,
                                  struct sig_cleanup_callback *cleanup,
                                  bool run_cleanup_when_notarget) {
	preemption_flag_t was;
	struct sig *sender;
	struct task_connection *sig_con;
	struct task_connection *receiver;
	struct task_connection *last_ingored_connection;
	struct sig_select_context context;
	bool select_poll = false;
	context.ssc_signal    = self;
	context.ssc_flag      = SIG_SELECT_FLAG_NORMAL;
	context.ssc_wakeflags = TASK_WAKE_FNORMAL;
	context.ssc_caller    = caller;
	preemption_pushoff(&was);
#ifdef CONFIG_NO_SMP
	sig_con = atomic_read(&self->s_con);
	if (!sig_con)
		goto done;
#else /* CONFIG_NO_SMP */
	for (;;) {
		sig_con = atomic_read(&self->s_con);
		if (!sig_con)
			goto done;
		if unlikely((uintptr_t)sig_con & SIG_CONTROL_SMPLOCK) {
			preemption_tryyield_f(&was);
			continue;
		}
		if (atomic_cmpxch_weak(&self->s_con, sig_con,
		                       sig_smplock_set(sig_con)))
			break;
	}
#endif /* !CONFIG_NO_SMP */

	/* Figure out which signal we should select. */
	last_ingored_connection = NULL;
again:
	for (;;) {
		struct task_connections *target_cons;
		for (receiver = sig_con;
		     receiver->tc_connext != last_ingored_connection;
		     receiver = receiver->tc_signext)
			;
#ifndef CONFIG_NO_SMP
again_read_cons:
#endif /* !CONFIG_NO_SMP */
		target_cons = atomic_read(&receiver->tc_cons);
		if (!TASK_CONNECTION_STAT_ISDONE(target_cons) &&
		    (!!TASK_CONNECTION_STAT_ISPOLL(target_cons)) == select_poll) {

#ifndef CONFIG_NO_SMP
			/* NOTE: Waiting until we can lock the connection here is allowed, since
			 *       you're allowed to  (and required to)  acquire connection  locks
			 *       without having to release the associated signal-lock.
			 * Doing  this doesn't result  in a race condition,  since the other end
			 * of this syncing mechanism (which is `task_disconnect()') will release
			 * its initial connection-lock if it  fails to acquire the signal  lock,
			 * which it will because we're already holding that one! */
			if unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK) {
				task_pause();
				goto again_read_cons;
			}
			if (!atomic_cmpxch_weak(&receiver->tc_cons, target_cons,
			                        (struct task_connections *)((uintptr_t)target_cons |
			                                                    TASK_CONNECTION_STAT_FLOCK)))
				goto again_read_cons;
#endif /* !CONFIG_NO_SMP */

			/* Figure out the exact details of this receiver. */
			if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
				/* Completion callback */
				context.ssc_type  = SIG_SELECT_TYPE_COMPLETION;
				context.ssc_compl = (struct sig_completion *)receiver;
			} else {
				/* Sleeping thread */
				struct task_connections *chain;
				context.ssc_type = SIG_SELECT_TYPE_THREAD;
				for (chain = TASK_CONNECTION_STAT_ASCONS(target_cons);;) {
					if (chain->tcs_thread) {
						context.ssc_thread = chain->tcs_thread;
						break;
					}
					if (!chain->tcs_prev) {
						/* Assume that `chain' is `this_root_connections' of the
						 * target  thread, which we  can use to reverse-engineer
						 * the actual thread */
						context.ssc_thread = (struct task *)((uintptr_t)chain -
						                                     (uintptr_t)&this_root_connections);
						break;
					}
					chain = chain->tcs_prev;
				}
			}

			/* Figure out if we want to send to this connection. */
			sender = (*selector)(cookie, &context);
			if (sender != NULL) {
				REF struct task *thread;
				if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
					/* Invoke a completion function. */
					atomic_write(&receiver->tc_stat,
					             TASK_CONNECTION_STAT_BROADCAST |
					             TASK_CONNECTION_STAT_FLOCK_OPT);
					task_connection_unlink_from_sig(self, receiver);
					sig_completion_runsingle(self,
					                         (struct sig_completion *)receiver,
					                         context.ssc_caller, sender,
					                         cleanup, was);
					return SIG_SEND_SELECT_SUCCESS;
				}

				/* Send the signal to a normal thread. */
				if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
					/* Send the signal to a normal thread. */
					atomic_write(&receiver->tc_stat,
					             TASK_CONNECTION_STAT_BROADCAST |
					             TASK_CONNECTION_STAT_FLOCK_OPT);
					task_connection_unlink_from_sig_and_unlock(self, receiver);
					target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
					if (!atomic_cmpxch(&target_cons->tcs_dlvr, NULL, sender))
						goto unlock_receiver_and_return_already;
					thread = xincref(atomic_read(&target_cons->tcs_thread));
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
					atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
				} else {
					atomic_write(&receiver->tc_stat,
					             TASK_CONNECTION_STAT_SENT |
					             TASK_CONNECTION_STAT_FLOCK_OPT);
					assert(target_cons == TASK_CONNECTION_STAT_ASCONS(target_cons));
					if (!atomic_cmpxch(&target_cons->tcs_dlvr, NULL, sender)) {
						/* Another signal was already delivered to the specified thread. */
						task_connection_unlink_from_sig_and_unlock(self, receiver);
unlock_receiver_and_return_already:
						atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
						if (cleanup)
							(*cleanup->scc_cb)(cleanup);
						preemption_pop(&was);
						return SIG_SEND_SELECT_ALREADY;
					}
					sig_smplock_release_nopr(self);
					thread = xincref(atomic_read(&target_cons->tcs_thread));
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
					atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_SENT);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
				}
				if (cleanup)
					(*cleanup->scc_cb)(cleanup);
				preemption_pop(&was);

				/* Wake-up the thread. */
				if likely(thread) {
					task_wake_as(thread,
					             context.ssc_caller,
					             context.ssc_wakeflags);
					decref_unlikely(thread);
				}
				return SIG_SEND_SELECT_SUCCESS;
			}
#ifndef CONFIG_NO_SMP
			atomic_and(&receiver->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
#endif /* !CONFIG_NO_SMP */
		}
		if (receiver == sig_con)
			break;
		last_ingored_connection = receiver;
	}
	if (!select_poll) {
		context.ssc_flag = SIG_SELECT_FLAG_FORPOLL;
		select_poll      = true;
		goto again;
	}
	sig_smplock_release_nopr(self);
done:
	if (cleanup && run_cleanup_when_notarget)
		(*cleanup->scc_cb)(cleanup);
	preemption_pop(&was);
	return SIG_SEND_SELECT_NOTARGET;
}

PUBLIC NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL sig_send_select)(struct sig *__restrict self,
                               sig_send_selector_t selector, void *cookie,
                               struct sig_cleanup_callback *cleanup,
                               bool run_cleanup_when_notarget) {
	unsigned int result;
	result = sig_send_select_as(self,
	                            selector,
	                            cookie,
	                            THIS_TASK,
	                            cleanup,
	                            run_cleanup_when_notarget);
	return result;
}


#ifndef __INTELLISENSE__
DECL_END
#define DEFINE_sig_send
#include "sig-send-old.c.inl"
#define DEFINE_sig_send_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_altsend
#include "sig-send-old.c.inl"
#define DEFINE_sig_altsend_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_sendto
#include "sig-send-old.c.inl"
#define DEFINE_sig_sendto_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_altsendto
#include "sig-send-old.c.inl"
#define DEFINE_sig_altsendto_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_altbroadcast
#include "sig-send-old.c.inl"
#define DEFINE_sig_altbroadcast_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_as_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_cleanup_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_as_cleanup_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_for_fini
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_for_fini_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_altbroadcast_for_fini
#include "sig-send-old.c.inl"
#define DEFINE_sig_altbroadcast_for_fini_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_as_for_fini_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_for_fini_cleanup_nopr
#include "sig-send-old.c.inl"
#define DEFINE_sig_broadcast_as_for_fini_cleanup_nopr
#include "sig-send-old.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */

DECL_END
#endif /* !CONFIG_EXPERIMENTAL_KERNEL_SIG_V2 */















#ifdef DEFINE_TEST
DECL_BEGIN


DEFINE_TEST(recursive_signals) {
	struct task_connections cons;
	struct sig s = SIG_INIT;
	task_disconnectall();
	task_connect(&s);
	task_pushconnections(&cons);
	task_connect(&s);

	assert(task_wasconnected());
	assert(task_wasconnected(&s));
	assert(task_trywait() == NULL);

	sig_broadcast(&s);

	/* Simulate what kfree() for the signal would do, thus
	 * ensuring that the the signal can still be received,
	 * even after it was destroyed. */
	memset(&s, 0xcc, sizeof(s));

	assert(task_wasconnected());
	assert(task_wasconnected(&s));

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);

	assert(task_popconnections() == &cons);

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);
}

DEFINE_TEST(broadcast_after_send) {
	struct sig s = SIG_INIT;
	task_connect(&s);
	assert(sig_send(&s));
	assert(sig_broadcast(&s) == 0);
	task_disconnectall();
}

DEFINE_TEST(pushpop_connections) {
	struct sig a = SIG_INIT, b = SIG_INIT;
	struct task_connections cons;
	assert(!sig_iswaiting(&a) && sig_numwaiting(&a) == 0);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	task_connect(&a);
	assert(task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	task_pushconnections(&cons);
	assert(!task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	task_connect(&b);
	assert(!task_wasconnected(&a));
	assert(task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(sig_iswaiting(&b) && sig_numwaiting(&b) == 1);

	task_disconnectall();
	assert(!task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	assert(task_popconnections() == &cons);
	assert(task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	assert(task_disconnect(&a));
	assert(!task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(!task_wasconnected());
	assert(!sig_iswaiting(&a) && sig_numwaiting(&a) == 0);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);
}

#ifdef CONFIG_EXPERIMENTAL_KERNEL_SIG_V2
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
		unused_start += sprintf(result, "comp%u", (unsigned int)(id - RST_RING_COMP(RST_LO)));
	} else if (id >= RST_RING_TASK(RST_LO) && id <= RST_RING_TASK(RST_HI)) {
		unused_start += sprintf(result, "task%u", (unsigned int)(id - RST_RING_TASK(RST_LO)));
	} else {
		unused_start += sprintf(result, "{?:%u}", (unsigned int)id);
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
		return "NULL";
	if (ptr >= cons->tcs_static && ptr < COMPILER_ENDOF(cons->tcs_static)) {
		unused_start += sprintf(result, "task%u", (unsigned int)((struct sigtaskcon *)ptr - cons->tcs_static));
	} else if (ptr >= comp_cons && ptr < (comp_cons + RST_N)) {
		unused_start += sprintf(result, "comp%u", (unsigned int)((struct sigcompcon *)ptr - comp_cons));
	} else {
		unused_start += sprintf(result, "{?:%p}", ptr);
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
	struct sig s = SIG_INIT;
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
#endif /* CONFIG_EXPERIMENTAL_KERNEL_SIG_V2 */


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
