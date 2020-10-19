/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "signal.c"
#define DEFINE_sig_send 1
//#define DEFINE_sig_altsend 1
//#define DEFINE_sig_broadcast 1
//#define DEFINE_sig_altbroadcast 1
//#define DEFINE_sig_broadcast_as_nopr 1
//#define DEFINE_sig_broadcast_destroylater_nopr 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_sig_send) /**/ + defined(DEFINE_sig_altsend) +      \
     defined(DEFINE_sig_broadcast) + defined(DEFINE_sig_altbroadcast) + \
     defined(DEFINE_sig_broadcast_as_nopr) + defined(DEFINE_sig_broadcast_destroylater_nopr)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_sig_send
/* Send signal `self' to exactly 1 connected thread
 *  - The receiver is the thread who's connection has been pending the longest.
 *  - Note the special interaction of this function with poll-based connections.
 *    For more information on this subject, see `task_connect_for_poll()'.
 * @return: true:  A waiting thread was signaled.
 * @return: false: The given signal didn't have any active connections. */
PUBLIC NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_send)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altsend)
#define HAVE_SENDER
PUBLIC NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sig_altsend)(struct sig *self,
                           struct sig *sender)
#elif defined(DEFINE_sig_broadcast)
#define HAVE_BROADCAST
#define HAVE_BROADCAST_RESULT
/* Send signal to all connected threads.
 * @return: * : The actual number of threads notified,
 *              not counting poll-based connections. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altbroadcast)
#define HAVE_BROADCAST
#define HAVE_BROADCAST_RESULT
#define HAVE_SENDER
PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast)(struct sig *self,
                                struct sig *sender)
#elif defined(DEFINE_sig_broadcast_as_nopr)
#define HAVE_BROADCAST
#define HAVE_BROADCAST_RESULT
#define HAVE_SENDER_THREAD
#define HAVE_NOPREEMPT
/* Same as `sig_broadcast()', but impersonate `sender_thread', and
 * wake up thread through use of `task_wake_as()'. The same rules
 * apply, meaning that the (true) caller must ensure that their
 * CPU won't change, and that `sender_thread' is also running as
 * part of their CPU. */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_as_nopr)(struct sig *__restrict self,
                                     struct task *__restrict sender_thread)
#elif defined(DEFINE_sig_broadcast_destroylater_nopr)
#define HAVE_BROADCAST
#define HAVE_DESTROYLATER
#define HAVE_NOPREEMPT
/* Same as `sig_broadcast()', don't immediatly destroy threads when their
 * reference counter reaches 0. Instead, chain those threads together and
 * return them to the caller, to-be destroyed at their leisure.
 *
 * This function is needed to comply with the no-decref requirement of AIO
 * completion functions that have yet to invoke `aio_handle_release()':
 * >> PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
 * >> NOTHROW(FCALL my_aio_completion)(struct aio_handle *__restrict self,
 * >>                                  unsigned int status) {
 * >>     struct task *delme_threads = NULL;
 * >>     sig_broadcast_destroylater_nopr((struct sig *)self->ah_data[0], &delme_threads);
 * >>     aio_handle_release(self);
 * >>     while (unlikely(delme_threads)) {
 * >>         struct task *next;
 * >>         next = sig_destroylater_next(delme_threads);
 * >>         destroy(delme_threads);
 * >>         delme_threads = next;
 * >>     }
 * >> } */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_broadcast_destroylater_nopr)(struct sig *__restrict self,
                                               struct task **__restrict pdestroy_later)
#endif /* ... */
{
#ifdef CONFIG_USE_NEW_SIGNAL_API
	struct task_connection *con;
#ifdef HAVE_BROADCAST
	size_t result = 0;
#endif /* HAVE_BROADCAST */
#ifdef HAVE_SENDER
#define LOCAL_sender sender
	assert(sender);
#else /* HAVE_SENDER */
#define LOCAL_sender self
#endif /* !HAVE_SENDER */
#ifdef HAVE_NOPREEMPT
	assert(!PREEMPTION_ENABLED());
#define LOCAL_PREEMPTION_PUSHOFF() (void)0
#define LOCAL_PREEMPTION_POP()     (void)0
#define LOCAL_was       PREEMPTION_DISABLED_VALUE
#else /* HAVE_NOPREEMPT */
	pflag_t was;
#define LOCAL_PREEMPTION_PUSHOFF() was = PREEMPTION_PUSHOFF()
#define LOCAL_PREEMPTION_POP()     PREEMPTION_POP(was)
#define LOCAL_was       was
#endif /* !HAVE_NOPREEMPT */
#ifdef HAVE_SENDER_THREAD
#define LOCAL_sender_thread     sender_thread
#define LOCAL_task_wake(thread) task_wake_as(thread, sender_thread)
#else /* HAVE_SENDER_THREAD */
#define LOCAL_sender_thread     THIS_TASK
#define LOCAL_task_wake(thread) task_wake(thread)
#endif /* !HAVE_SENDER_THREAD */
#ifdef HAVE_DESTROYLATER
#define LOCAL_decref_task(thread)                               \
	(assert((thread)->t_refcnt >= 1),                           \
	 (ATOMIC_FETCHDEC((thread)->t_refcnt) == 1                  \
	  ? (void)(sig_destroylater_next(thread) = *pdestroy_later, \
	           *pdestroy_later                = (thread))       \
	  : (void)0))
#else /* HAVE_DESTROYLATER */
#define LOCAL_decref_task(thread) decref(thread)
#endif /* !HAVE_DESTROYLATER */
again_disable_preemption:
	LOCAL_PREEMPTION_PUSHOFF();
#ifdef CONFIG_NO_SMP
again:
#endif /* CONFIG_NO_SMP */
	con = ATOMIC_READ(self->s_con);
	if (con) {
#ifdef HAVE_BROADCAST
		struct task_connection *next;
#endif /* HAVE_BROADCAST */
		struct task_connection *receiver;
		struct task_connections *target_cons;
#ifndef CONFIG_NO_SMP
		/* Wait if the SMP lock isn't available at the moment. */
		if unlikely((uintptr_t)con & SIG_CONTROL_SMPLOCK) {
			LOCAL_PREEMPTION_POP();
			task_pause();
			goto again_disable_preemption;
		}
		/* Acquire the SMP-lock and validate that `con' is still correct. */
		if (!ATOMIC_CMPXCH_WEAK(self->s_con, con,
		                        sig_smplock_set(con)))
			goto again_disable_preemption;
		con = sig_smplock_set(con);
		__IF0 {
again:
			con = ATOMIC_READ(self->s_con);
			assert(sig_smplock_tst(con));
			if (!sig_smplock_clr(con)) {
				if (!ATOMIC_CMPXCH_WEAK(self->s_con, con, 0))
					goto again;
				goto done;
			}
		}
#endif /* !CONFIG_NO_SMP */
#ifdef HAVE_BROADCAST
again_select_receiver:
		/* Find a suitable candidate:
		 *    During broadcast:
		 *       #1: Just use the first connection */
		receiver = sig_smplock_clr(con);
		assert(receiver);
		/* Unlink `receiver' from the connection chain, but keep ahold of the signal lock.
		 * The later must be done to ensure that the signal isn't broadcast again until
		 * we're done, so-as to ensure that auto-re-prime completion callbacks are invoked
		 * for every time they are selected as signal targets. */
		if (!ATOMIC_CMPXCH_WEAK(self->s_con, con,
		                        sig_smplock_set(receiver->tc_signext))) {
			con = ATOMIC_READ(self->s_con);
			assert(sig_smplock_tst(con));
			assert(sig_smplock_clr(con) != NULL);
			goto again_select_receiver;
		}
		/* Acquire a lock to `receiver' */
#ifndef CONFIG_NO_SMP
again_read_target_cons:
		target_cons = ATOMIC_READ(receiver->tc_cons);
		/* NOTE: Waiting until we can lock the connection here is allowed, since
		 *       you're allowed to (and required to) acquire connection locks
		 *       without having to release the associated signal-lock.
		 * Doing this doesn't result in a race condition, since the other end
		 * of this syncing mechanism (which is `task_disconnect()') will release
		 * its initial connection-lock if it fails to acquire the signal lock,
		 * which it will because we're already holding that one! */
		while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
			task_pause();
			target_cons = ATOMIC_READ(receiver->tc_cons);
		}
		/* Mark the receiver for broadcast, and acquire a lock to it. */
		if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again_read_target_cons;
#else /* !CONFIG_NO_SMP */
		target_cons = ATOMIC_XCH(receiver->tc_cons,
		                         (struct task_connections *)TASK_CONNECTION_STAT_BROADCAST);
#endif /* CONFIG_NO_SMP */
		/* Unlink `receiver' from our chain and unlock `self' */
		next = receiver->tc_signext;
#ifndef CONFIG_NO_SMP
		assert(!sig_smplock_tst(next));
#endif /* !CONFIG_NO_SMP */
		ATOMIC_WRITE(self->s_con, sig_smplock_set(next));
		/* Deal with special connections. */
		if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
			if (TASK_CONNECTION_STAT_ISDONE(target_cons))
				goto again;
			/* Special case: broadcast includes completion callbacks.
			 * Do this in a separate function so-as to keep the additional overhead outside of this function. */
#ifdef HAVE_DESTROYLATER
			result += sig_broadcast_as_destroylater_with_initial_completion_nopr(self,
			                                                                     LOCAL_sender_thread,
			                                                                     LOCAL_sender,
			                                                                     (struct sig_completion *)receiver,
			                                                                     pdestroy_later);
			goto done;
#else /* HAVE_DESTROYLATER */
			result += sig_broadcast_as_with_initial_completion_nopr(self,
			                                                        LOCAL_sender_thread,
			                                                        LOCAL_sender,
			                                                        LOCAL_was,
			                                                        (struct sig_completion *)receiver);
			return result;
#endif /* !HAVE_DESTROYLATER */
		}
		target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
		/* Try to set our signal as the one delivered to `target_cons'. */
		if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, LOCAL_sender)) {
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			goto again;
		}
		/* Suitable receiver. */
		++result;
		/* Wake-up the thread attached to the connection */
		{
			REF struct task *thread;
			thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			if likely(thread) {
#ifdef CONFIG_NO_SMP
				if (!next)
#else /* CONFIG_NO_SMP */
				if (!next && ATOMIC_CMPXCH(self->s_ctl, SIG_CONTROL_SMPLOCK, 0))
#endif /* !CONFIG_NO_SMP */
				{
					/* Special case: No other remaining signals. - In this case, do the
					 * wake-up of `thread' while no longer holding the SMP-lock to `self'
					 * We do this because `task_wake()' can be a bit smarter when it comes
					 * to scheduling if preemption is enabled (since in that case, it can
					 * do direct context switches, possibly even over to `thread' itself) */
					LOCAL_PREEMPTION_POP();
					LOCAL_task_wake(thread);
					LOCAL_decref_task(thread);
					return result;
				}
				LOCAL_task_wake(thread);
#ifdef HAVE_DESTROYLATER
				LOCAL_decref_task(thread);
#else /* HAVE_DESTROYLATER */
				/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
				assert(thread->t_refcnt >= 1);
				if unlikely(ATOMIC_FETCHDEC(thread->t_refcnt) == 1) {
					result += sig_broadcast_as_with_initial_destroylater_nopr(self,
					                                                          LOCAL_sender_thread,
					                                                          LOCAL_sender,
					                                                          LOCAL_was,
					                                                          thread);
					return result;
				}
#endif /* !HAVE_DESTROYLATER */
			}
		}
		goto again;
#else /* HAVE_BROADCAST */
		/* Find a suitable candidate:
		 *    During send:
		 *       #1: Use the last-in-chain, non-poll connection
		 *       #2: Broadcast all poll connections (but stop if
		 *           a non-poll connection shows up before we're
		 *           down)
		 *       #3: If no non-poll connection could be found,
		 *           return `false' */
		receiver = sig_smplock_clr(con);
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

		/* Acquire a lock to `receiver' */
again_read_target_cons:
		target_cons = ATOMIC_READ(receiver->tc_cons);
#ifndef CONFIG_NO_SMP
		/* NOTE: Waiting until we can lock the connection here is allowed, since
		 *       you're allowed to (and required to) acquire connection locks
		 *       without having to release the associated signal-lock.
		 * Doing this doesn't result in a race condition, since the other end
		 * of this syncing mechanism (which is `task_disconnect()') will release
		 * its initial connection-lock if it fails to acquire the signal lock,
		 * which it will because we're already holding that one! */
		while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
			task_pause();
			target_cons = ATOMIC_READ(receiver->tc_cons);
		}
#endif /* !CONFIG_NO_SMP */
		if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
			struct sig_completion *sc;
			if unlikely(TASK_CONNECTION_STAT_ISDEAD(target_cons)) {
				/* The target is already dead. (change it to broadcast) */
				if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
				                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
				                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
					goto again_read_target_cons;
				task_connection_unlink_from_sig(self, receiver);
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
				ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
				goto again;
			}
			/* Signal completion callback. */
			if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
			                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
			                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
				goto again_read_target_cons;
			task_connection_unlink_from_sig(self, receiver);
			sc = (struct sig_completion *)receiver;
			if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
				/* Special case: Deal with poll-based connections receiver. */
#ifdef HAVE_DESTROYLATER
				bool result;
				result = sig_send_as_destroylater_with_initial_completion_nopr(self,
				                                                               LOCAL_sender_thread,
				                                                               LOCAL_sender,
				                                                               sc,
				                                                               pdestroy_later);
				LOCAL_PREEMPTION_POP();
				return result;
#else /* HAVE_DESTROYLATER */
				return sig_send_as_with_initial_completion_nopr(self,
				                                                LOCAL_sender_thread,
				                                                LOCAL_sender,
				                                                sc,
				                                                LOCAL_was);
#endif /* !HAVE_DESTROYLATER */
			} else {
				/* Invoke the phase-1 callback. */
#ifdef HAVE_DESTROYLATER
#define LOCAL_pdestroy_later pdestroy_later
#else /* HAVE_DESTROYLATER */
#define LOCAL_pdestroy_later (&destroy_later)
				REF struct task *destroy_later = NULL;
#endif /* !HAVE_DESTROYLATER */
				(*sc->sc_cb)(sc, self, SIG_COMPLETION_PHASE_SETUP,
				             LOCAL_pdestroy_later, LOCAL_sender);
				/* Unlock the signal. */
				sig_smplock_release_nopr(self);
				/* Invoke phase #2. (this one also unlocks `receiver') */
				(*sc->sc_cb)(sc, self, SIG_COMPLETION_PHASE_PAYLOAD,
				             LOCAL_pdestroy_later, LOCAL_sender);
				LOCAL_PREEMPTION_POP();
#ifndef HAVE_DESTROYLATER
				destroy_tasks(destroy_later);
#endif /* !HAVE_DESTROYLATER */
			}
			return true;
		}
		if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
			REF struct task *thread;
			/* Special case: poll-based connections don't (really) count.
			 * Instead, those get marked for broadcast. */
			if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
			                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
			                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
				goto again_read_target_cons;
			task_connection_unlink_from_sig(self, receiver);
			target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
			thread = NULL;
			/* Set the delivered signal, and capture
			 * the thread thread, if there is one */
			if (ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, LOCAL_sender))
				thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
			/* Unlock the connection. */
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			if (thread) {
				LOCAL_task_wake(thread);
#ifdef HAVE_DESTROYLATER
				LOCAL_decref_task(thread);
#else /* HAVE_DESTROYLATER */
				/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
				assert(thread->t_refcnt >= 1);
				if unlikely(ATOMIC_FETCHDEC(thread->t_refcnt) == 1) {
					return sig_send_as_with_initial_destroylater_nopr(self,
					                                                  LOCAL_sender_thread,
					                                                  LOCAL_sender,
					                                                  LOCAL_was,
					                                                  thread);
				}
#endif /* !HAVE_DESTROYLATER */
			}
			goto again;
		}
		/* Mark the receiver as sent, and acquire a lock to it. */
		if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_SENT |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again_read_target_cons;
		/* Set the signal sender as being delivered for the target connection set. */
		if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, LOCAL_sender)) {
			/* Unlink the signal, and mark it as broadcast. */
			task_connection_unlink_from_sig(self, receiver);
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			goto again;
		}
		/* The simple case: We managed to deliver the signal, and now we must wake-up
		 * the connected thread (if any) */
		{
			REF struct task *thread;
			thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
#ifndef CONFIG_NO_SMP
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_SENT);
#endif /* !CONFIG_NO_SMP */
			sig_smplock_release_nopr(self);
			LOCAL_PREEMPTION_POP();
			/* Wake-up the thread. */
			if likely(thread) {
				LOCAL_task_wake(thread);
				LOCAL_decref_task(thread);
			}
		}
		return true;
#endif /* !HAVE_BROADCAST */
	}
done:
	LOCAL_PREEMPTION_POP();
#undef LOCAL_was
#undef LOCAL_PREEMPTION_PUSHOFF
#undef LOCAL_PREEMPTION_POP
#undef LOCAL_sender_thread
#undef LOCAL_task_wake
#undef LOCAL_decref_task
#undef LOCAL_sender
#ifdef HAVE_BROADCAST
	return result;
#else /* HAVE_BROADCAST */
	return false;
#endif /* !HAVE_BROADCAST */
#else /* CONFIG_USE_NEW_SIGNAL_API */

#ifdef HAVE_BROADCAST_RESULT
	size_t result = 0;
#endif /* HAVE_BROADCAST_RESULT */
#ifdef HAVE_DESTROYLATER
	struct task *destroylater_threads = NULL;
#endif /* HAVE_DESTROYLATER */
	struct task_connection *con;
#ifndef HAVE_NOPREEMPT
	pflag_t was;
#endif /* !HAVE_NOPREEMPT */
#ifdef HAVE_SENDER
#define SIG_SENDER sender
	assert(sender);
#else /* HAVE_SENDER */
#define SIG_SENDER self
#endif /* !HAVE_SENDER */
#ifdef HAVE_NOPREEMPT
	assert(!PREEMPTION_ENABLED());
#endif /* HAVE_NOPREEMPT */
again:
#if SIG_SMPLOCK_BIT != 0
	/* Lock the signal. */
	con = ATOMIC_READ(self->s_con);
	if (SIG_SMPLOCK_TST(con)) {
		if (SIG_SMPLOCK_CLR(con) == NULL)
			goto done_nocon_nounlock;
#define NEED_done_nocon_nounlock
		for (;;) {
			task_pause();
#ifndef HAVE_NOPREEMPT
			was = PREEMPTION_PUSHOFF();
#endif /* !HAVE_NOPREEMPT */
			con = (struct task_connection *)ATOMIC_FETCHOR(self->s_ctl, SIG_SMPLOCK_BIT);
			if (((uintptr_t)con & SIG_SMPLOCK_BIT) == 0)
				break;
preemption_pop_and_lock:
#ifndef HAVE_NOPREEMPT
			PREEMPTION_POP(was)
#endif /* !HAVE_NOPREEMPT */
			;
		}
	} else {
#ifndef HAVE_NOPREEMPT
		was = PREEMPTION_PUSHOFF();
#endif /* !HAVE_NOPREEMPT */
		con = (struct task_connection *)ATOMIC_FETCHOR(self->s_ctl, SIG_SMPLOCK_BIT);
		if unlikely(((uintptr_t)con & SIG_SMPLOCK_BIT) != 0)
			goto preemption_pop_and_lock;
	}
#else /* SIG_SMPLOCK_BIT != 0 */
#ifndef HAVE_NOPREEMPT
	was = PREEMPTION_PUSHOFF();
#endif /* !HAVE_NOPREEMPT */
	con = ATOMIC_READ(self->s_con);
#endif /* SIG_SMPLOCK_BIT == 0 */

	if (con) {
#ifdef HAVE_BROADCAST
		struct task_connection *next;
		struct task_connections *target_cons;
		assert(con->tc_sig == self);
		target_cons = (struct task_connections *)ATOMIC_XCH(con->tc_stat,
		                                                    TASK_CONNECTION_STAT_SENT);
		assert((uintptr_t)target_cons != TASK_CONNECTION_STAT_BROADCAST);
		if (TASK_CONNECTION_STAT_CHECK(target_cons)) {
			/* Signal was already sent in the past.
			 * -> Change it's disposition to BROADCAST, and unlink it. */
			assert((uintptr_t)target_cons == TASK_CONNECTION_STAT_SENT);
			next = con->tc_signext;
			COMPILER_BARRIER();
			ATOMIC_WRITE(con->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			assert(!next || ADDR_ISKERN(next));
			assert(!SIG_SMPLOCK_TST(next));
			ATOMIC_WRITE(self->s_con, next);
#ifndef HAVE_NOPREEMPT
			PREEMPTION_POP(was);
#endif /* !HAVE_NOPREEMPT */
		} else {
			REF struct task *target_thread = NULL;
			struct task_connections *real_target_cons;
			real_target_cons = TASK_CONNECTION_STAT_GETCONS(target_cons);
			/* Set the delivered signal, and capture
			 * the target_thread thread, if there is one */
			if (ATOMIC_CMPXCH(real_target_cons->tcs_dlvr, NULL, SIG_SENDER))
				target_thread = xincref(ATOMIC_READ(real_target_cons->tcs_thread));
			next = con->tc_signext;
			COMPILER_BARRIER();
			ATOMIC_WRITE(con->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			assert(!next || ADDR_ISKERN(next));
			assert(!SIG_SMPLOCK_TST(next));
			ATOMIC_WRITE(self->s_con, next);
#ifndef HAVE_NOPREEMPT
			PREEMPTION_POP(was);
#endif /* !HAVE_NOPREEMPT */
			if (target_thread) {
#ifdef HAVE_SENDER_THREAD
				task_wake_as(target_thread, sender_thread);
#else /* HAVE_SENDER_THREAD */
				task_wake(target_thread);
#endif /* !HAVE_SENDER_THREAD */
#ifdef HAVE_DESTROYLATER
				assert(target_thread->t_refcnt > 0);
				if unlikely(ATOMIC_FETCHDEC(target_thread->t_refcnt) == 1) {
					/* Destroy this thread later... */
					sig_destroylater_next(target_thread) = destroylater_threads;
					destroylater_threads                 = target_thread;
				}
#else /* HAVE_DESTROYLATER */
				decref_unlikely(target_thread);
#endif /* !HAVE_DESTROYLATER */
			}
			/* Only normal connections count towards the returned # of threads. */
#ifdef HAVE_BROADCAST_RESULT
			if (TASK_CONNECTION_STAT_ISNORM(target_cons))
				++result;
#endif /* HAVE_BROADCAST_RESULT */
		}
		/* Try to wake up the remaining threads. */
#ifdef __OPTIMIZE_SIZE__
		goto again;
#else /* __OPTIMIZE_SIZE__ */
		if (next)
			goto again;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* HAVE_BROADCAST */
		struct task_connections *target_cons;
		struct task_connection *receiver;
		REF struct task *target_thread;
start_find_receiver:
		receiver = NULL;
		for (;;) {
			uintptr_t status;
			assert(con->tc_sig == self);
			status = ATOMIC_READ(con->tc_stat);
			assert(status != TASK_CONNECTION_STAT_BROADCAST);
			if (!TASK_CONNECTION_STAT_CHECK(status)) {
				if (TASK_CONNECTION_STAT_ISNORM(status))
					receiver = con; /* This connection is still in alive. */
			} else {
				assert(status == TASK_CONNECTION_STAT_SENT);
			}
			con = con->tc_signext;
			if (!con)
				break;
		}
		if likely(receiver) {
			target_cons = ATOMIC_READ(receiver->tc_cons);
			if unlikely(TASK_CONNECTION_STAT_CHECK(target_cons)) {
again_find_receiver:
				con = SIG_SMPLOCK_CLR(ATOMIC_READ(self->s_con));
				assertf(con, "We've holding the SMP-lock, and we already know that there "
				             "connections from above. So more could have only been added "
				             "in the mean time, but none could have been removed!");
				goto start_find_receiver;
			}
			assertf(TASK_CONNECTION_STAT_ISNORM(target_cons),
			        "We've checked this above, and established "
			        "connections can't suddenly become poll-based!");
			if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
			                        (struct task_connections *)TASK_CONNECTION_STAT_SENT))
				goto again_find_receiver;
			if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, SIG_SENDER)) {
				/* Unlink the signal, and mark it as broadcast. */
				task_connection_unlink_from_sig(self, receiver);
				ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
				goto again_find_receiver;
			}
			/* Unlock the signal, and wake-up the thread attached to the connection */
			target_thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
			_sig_smp_lock_release(self);
#ifndef HAVE_NOPREEMPT
			PREEMPTION_POP(was);
#endif /* !HAVE_NOPREEMPT */
			if (target_thread) {
#ifdef HAVE_SENDER_THREAD
				task_wake_as(target_thread, sender_thread);
#else /* HAVE_SENDER_THREAD */
				task_wake(target_thread);
#endif /* !HAVE_SENDER_THREAD */
#ifdef HAVE_DESTROYLATER
				assert(target_thread->t_refcnt > 0);
				if unlikely(ATOMIC_FETCHDEC(target_thread->t_refcnt) == 1) {
					/* Destroy this thread later... */
					sig_destroylater_next(target_thread) = destroylater_threads;
					destroylater_threads                 = target_thread;
				}
#else /* HAVE_DESTROYLATER */
				decref_unlikely(target_thread);
#endif /* !HAVE_DESTROYLATER */
			}
			return true;
		} else {
			struct task_connection *next;
			/* No regular connections, but there might be poll-based ones.
			 * If there are any, we must broadcast to all of them! */
			con = SIG_SMPLOCK_CLR(ATOMIC_READ(self->s_con));
			assertf(con, "We've holding the SMP-lock, and we already know that there "
			             "connections from above. So more could have only been added "
			             "in the mean time, but none could have been removed!");
			assert(con->tc_sig == self);
			/* Simply do a broadcast to _all_ connections. */
			target_cons = (struct task_connections *)ATOMIC_XCH(con->tc_stat,
			                                                    TASK_CONNECTION_STAT_SENT);
			assert((uintptr_t)target_cons != TASK_CONNECTION_STAT_BROADCAST);
			if (TASK_CONNECTION_STAT_CHECK(target_cons)) {
				/* Signal was already sent in the past.
				 * -> Change it's disposition to BROADCAST, and unlink it. */
				assert((uintptr_t)target_cons == TASK_CONNECTION_STAT_SENT);
				next = con->tc_signext;
				COMPILER_BARRIER();
				ATOMIC_WRITE(con->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
				assert(!next || ADDR_ISKERN(next));
				assert(!SIG_SMPLOCK_TST(next));
				ATOMIC_WRITE(self->s_con, next);
#ifndef HAVE_NOPREEMPT
				PREEMPTION_POP(was);
#endif /* !HAVE_NOPREEMPT */
			} else {
				REF struct task *target_thread = NULL;
				target_cons = TASK_CONNECTION_STAT_GETCONS(target_cons);
				/* Set the delivered signal, and capture
				 * the target_thread thread, if there is one */
				if (ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, SIG_SENDER))
					target_thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
				next = con->tc_signext;
				COMPILER_BARRIER();
				ATOMIC_WRITE(con->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
				assert(!next || ADDR_ISKERN(next));
				assert(!SIG_SMPLOCK_TST(next));
				ATOMIC_WRITE(self->s_con, next);
#ifndef HAVE_NOPREEMPT
				PREEMPTION_POP(was);
#endif /* !HAVE_NOPREEMPT */
				if (target_thread) {
#ifdef HAVE_SENDER_THREAD
					task_wake_as(target_thread, sender_thread);
#else /* HAVE_SENDER_THREAD */
					task_wake(target_thread);
#endif /* !HAVE_SENDER_THREAD */
#ifdef HAVE_DESTROYLATER
					assert(target_thread->t_refcnt > 0);
					if unlikely(ATOMIC_FETCHDEC(target_thread->t_refcnt) == 1) {
						/* Destroy this thread later... */
						sig_destroylater_next(target_thread) = destroylater_threads;
						destroylater_threads                 = target_thread;
					}
#else /* HAVE_DESTROYLATER */
					decref_unlikely(target_thread);
#endif /* !HAVE_DESTROYLATER */
				}
			}
			/* Try to wake up the remaining threads. */
#ifdef __OPTIMIZE_SIZE__
			goto again;
#else /* __OPTIMIZE_SIZE__ */
			if (next)
				goto again;
#endif /* !__OPTIMIZE_SIZE__ */
		}
#endif /* !HAVE_BROADCAST */
	}

/*done_nocon:*/
	_sig_smp_lock_release(self);
#ifndef HAVE_NOPREEMPT
	PREEMPTION_POP(was);
#endif /* !HAVE_NOPREEMPT */
#ifdef NEED_done_nocon_nounlock
#undef NEED_done_nocon_nounlock
done_nocon_nounlock:
#endif /* NEED_done_nocon_nounlock */
#ifdef HAVE_BROADCAST_RESULT
	return result;
#elif defined(HAVE_DESTROYLATER)
	return destroylater_threads;
#else /* ... */
	return false;
#endif /* !... */
#undef SIG_SENDER
#endif /* !CONFIG_USE_NEW_SIGNAL_API */
}

#undef HAVE_SENDER_THREAD
#undef HAVE_DESTROYLATER
#undef HAVE_BROADCAST_RESULT
#undef HAVE_BROADCAST
#undef HAVE_SENDER
#undef HAVE_NOPREEMPT


DECL_END

#undef DEFINE_sig_broadcast_destroylater_nopr
#undef DEFINE_sig_broadcast_as_nopr
#undef DEFINE_sig_altbroadcast
#undef DEFINE_sig_broadcast
#undef DEFINE_sig_altsend
#undef DEFINE_sig_send

