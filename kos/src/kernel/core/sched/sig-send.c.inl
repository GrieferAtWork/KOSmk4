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
//#define         DEFINE_sig_send
//#define      DEFINE_sig_altsend
//#define    DEFINE_sig_send_nopr
//#define DEFINE_sig_altsend_nopr
#define DEFINE_sig_sendto
//#define                          DEFINE_sig_altsendto
//#define                        DEFINE_sig_sendto_nopr
//#define                     DEFINE_sig_altsendto_nopr
//#define                          DEFINE_sig_broadcast
//#define                       DEFINE_sig_altbroadcast
//#define                     DEFINE_sig_broadcast_nopr
//#define                  DEFINE_sig_altbroadcast_nopr
//#define                  DEFINE_sig_broadcast_as_nopr
//#define             DEFINE_sig_broadcast_cleanup_nopr
//#define          DEFINE_sig_broadcast_as_cleanup_nopr
//#define                 DEFINE_sig_broadcast_for_fini
//#define              DEFINE_sig_altbroadcast_for_fini
//#define            DEFINE_sig_broadcast_for_fini_nopr
//#define         DEFINE_sig_altbroadcast_for_fini_nopr
//#define         DEFINE_sig_broadcast_as_for_fini_nopr
//#define    DEFINE_sig_broadcast_for_fini_cleanup_nopr
//#define DEFINE_sig_broadcast_as_for_fini_cleanup_nopr
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_sig_send) +                            \
     defined(DEFINE_sig_send_nopr) +                       \
     defined(DEFINE_sig_altsend) +                         \
     defined(DEFINE_sig_altsend_nopr) +                    \
     defined(DEFINE_sig_sendto) +                          \
     defined(DEFINE_sig_sendto_nopr) +                     \
     defined(DEFINE_sig_altsendto) +                       \
     defined(DEFINE_sig_altsendto_nopr) +                  \
     defined(DEFINE_sig_broadcast) +                       \
     defined(DEFINE_sig_broadcast_nopr) +                  \
     defined(DEFINE_sig_altbroadcast) +                    \
     defined(DEFINE_sig_altbroadcast_nopr) +               \
     defined(DEFINE_sig_broadcast_as_nopr) +               \
     defined(DEFINE_sig_broadcast_cleanup_nopr) +          \
     defined(DEFINE_sig_broadcast_as_cleanup_nopr) +       \
     defined(DEFINE_sig_broadcast_for_fini) +              \
     defined(DEFINE_sig_broadcast_for_fini_nopr) +         \
     defined(DEFINE_sig_altbroadcast_for_fini) +           \
     defined(DEFINE_sig_altbroadcast_for_fini_nopr) +      \
     defined(DEFINE_sig_broadcast_as_for_fini_nopr) +      \
     defined(DEFINE_sig_broadcast_for_fini_cleanup_nopr) + \
     defined(DEFINE_sig_broadcast_as_for_fini_cleanup_nopr)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_sig_send
/* Send signal `self' to exactly 1 connected thread
 *  - The receiver is the thread who's connection has been pending the longest.
 *  - Note the special interaction of this function with poll-based connections.
 *    For  more  information  on  this  subject,  see `task_connect_for_poll()'.
 * @return: true:  A waiting thread was signaled.
 * @return: false: The given signal didn't have any active connections. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sig_send)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altsend)
#define LOCAL_HAVE_SENDER
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL sig_altsend)(struct sig *self,
                           struct sig *sender)
#elif defined(DEFINE_sig_send_nopr)
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) bool
NOTHROW(FCALL sig_send_nopr)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altsend_nopr)
#define LOCAL_HAVE_SENDER
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) bool
NOTHROW(FCALL sig_altsend_nopr)(struct sig *self,
                                struct sig *sender)
#elif defined(DEFINE_sig_sendto)
#define LOCAL_HAVE_TARGET_THREAD
/* Send signal `self' to the given thread `target'
 *  - Behaves  the same as `sig_send()', however signal completion
 *    callbacks  and task_connection's that point to threads other
 *    than `target' are silently skipped, and the function behaves
 *    as  though anything other  than true thread-connections made
 *    by `target' didn't exist.
 * @return: true:  The specified `target' was connected, and the signal
 *                 was delivered as expected.
 * @return: false: The specified `target' wasn't connected to `self'. */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sig_sendto)(struct sig *__restrict self,
                          struct task *__restrict target)
#elif defined(DEFINE_sig_altsendto)
#define LOCAL_HAVE_TARGET_THREAD
#define LOCAL_HAVE_SENDER
FUNDEF NOBLOCK NONNULL((1, 2, 3)) bool
NOTHROW(FCALL sig_altsendto)(struct sig *self,
                             struct task *__restrict target,
                             struct sig *sender)
#elif defined(DEFINE_sig_sendto_nopr)
#define LOCAL_HAVE_TARGET_THREAD
#define LOCAL_HAVE_NOPREEMPT
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) bool
NOTHROW(FCALL sig_sendto_nopr)(struct sig *__restrict self,
                               struct task *__restrict target)
#elif defined(DEFINE_sig_altsendto_nopr)
#define LOCAL_HAVE_TARGET_THREAD
#define LOCAL_HAVE_SENDER
#define LOCAL_HAVE_NOPREEMPT
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) bool
NOTHROW(FCALL sig_altsendto_nopr)(struct sig *self,
                                  struct task *__restrict target,
                                  struct sig *sender)
#elif defined(DEFINE_sig_broadcast)
#define LOCAL_HAVE_BROADCAST
/* Send signal to all connected threads.
 * @return: * : The actual number of threads notified,
 *              not  counting  poll-based connections. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altbroadcast)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_SENDER
PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast)(struct sig *self,
                                struct sig *sender)
#elif defined(DEFINE_sig_broadcast_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_nopr)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altbroadcast_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_NOPREEMPT
#define LOCAL_HAVE_SENDER
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast_nopr)(struct sig *self,
                                     struct sig *sender)
#elif defined(DEFINE_sig_broadcast_as_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_SENDER_THREAD
#define LOCAL_HAVE_NOPREEMPT
/* Same as `sig_broadcast()', but impersonate `caller', and
 * wake up thread through use of `task_wake_as()'. The same
 * rules apply, meaning that the (true) caller must  ensure
 * that their CPU won't change,  and that `caller' is  also
 * running as part of their CPU. */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_as_nopr)(struct sig *__restrict self,
                                     struct task *__restrict caller)
#elif defined(DEFINE_sig_broadcast_cleanup_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_CLEANUP
#define LOCAL_HAVE_NOPREEMPT
/* Same as `sig_broadcast()', but invoke a given `cleanup' prior to doing any  other
 * kind of cleanup, but after having released all internal SMP-locks. May be used to
 * release further SMP-locks  which may have  been used to  guard `self' from  being
 * destroyed (such  as calling  `aio_handle_release()' when  sending a  signal  from
 * inside of an AIO completion function)
 * Note that all of these functions guaranty that `callback' is invoked exactly once. */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_broadcast_cleanup_nopr)(struct sig *__restrict self,
                                          struct sig_cleanup_callback *__restrict cleanup)
#elif defined(DEFINE_sig_broadcast_as_cleanup_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_CLEANUP
#define LOCAL_HAVE_SENDER_THREAD
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL sig_broadcast_as_cleanup_nopr)(struct sig *__restrict self,
                                             struct task *__restrict caller,
                                             struct sig_cleanup_callback *__restrict cleanup)
#elif defined(DEFINE_sig_broadcast_for_fini)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_FOR_FINI
/* Same  as the regular `sig_broadcast' function, but must be used if
 * `self'  is being broadcast one last time prior to being destroyed.
 * When these functions are used, signal completion callbacks are not
 * allowed to make  use of  `sig_completion_reprime()', but  instead,
 * that function will return `false' and do nothing.
 * @return: * : The actual number of threads notified,
 *              not  counting  poll-based connections. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_for_fini)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altbroadcast_for_fini)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_FOR_FINI
#define LOCAL_HAVE_SENDER
PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast_for_fini)(struct sig *self,
                                         struct sig *sender)
#elif defined(DEFINE_sig_broadcast_for_fini_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_FOR_FINI
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_for_fini_nopr)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altbroadcast_for_fini_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_FOR_FINI
#define LOCAL_HAVE_NOPREEMPT
#define LOCAL_HAVE_SENDER
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast_for_fini_nopr)(struct sig *self,
                                              struct sig *sender)
#elif defined(DEFINE_sig_broadcast_as_for_fini_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_FOR_FINI
#define LOCAL_HAVE_SENDER_THREAD
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_as_for_fini_nopr)(struct sig *__restrict self,
                                              struct task *__restrict caller)
#elif defined(DEFINE_sig_broadcast_for_fini_cleanup_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_FOR_FINI
#define LOCAL_HAVE_CLEANUP
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_broadcast_for_fini_cleanup_nopr)(struct sig *__restrict self,
                                                   struct sig_cleanup_callback *__restrict cleanup)
#elif defined(DEFINE_sig_broadcast_as_for_fini_cleanup_nopr)
#define LOCAL_HAVE_BROADCAST
#define LOCAL_HAVE_FOR_FINI
#define LOCAL_HAVE_CLEANUP
#define LOCAL_HAVE_SENDER_THREAD
#define LOCAL_HAVE_NOPREEMPT
PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL sig_broadcast_as_for_fini_cleanup_nopr)(struct sig *__restrict self,
                                                      struct task *__restrict caller,
                                                      struct sig_cleanup_callback *__restrict cleanup)
#endif /* ... */
{
	struct task_connection *con;
	struct task_connection *receiver;
	struct task_connections *target_cons;
#ifdef LOCAL_HAVE_BROADCAST
	/* FIXME: Broadcasting to a large number other threads running on another CPU
	 *        can lead to  a (not-really?) soft-lock  scenario that can  randomly
	 *        resolve itself after an arbitrary amount of time.
	 * The problem is that  the condition which our  caller is broadcasting may  have
	 * gone  away before we've  finished broadcasting to  all listening threads. When
	 * this happens, it can be that other  threads which we've already send a  signal
	 * to re-add themself to the signal queue before we're done, at which point we'll
	 * end up broadcasting to them once again.
	 * Solution: Instead of implementing sig_broadcast() as
	 *           `while (try_broadcast_one()) ++result',
	 *           implement it as this instead:
	 *           recv = atomic_xch(&self->s_con, SMP_LOCK);
	 *           while (recv) { next = ...; broadcast_to(...); ++result; recv = next; }
	 */
	struct task_connection *next;
	size_t result = 0;
#endif /* LOCAL_HAVE_BROADCAST */
#ifdef LOCAL_HAVE_SENDER
#define LOCAL_sender sender
	assert(sender);
#else /* LOCAL_HAVE_SENDER */
#define LOCAL_sender self
#endif /* !LOCAL_HAVE_SENDER */
#ifdef LOCAL_HAVE_NOPREEMPT
	assert(!preemption_ison());
#define LOCAL_preemption_pushoff() (void)0
#define LOCAL_preemption_pop()     (void)0
#define LOCAL_was                  PREEMPTION_OFF_VALUE
#else /* LOCAL_HAVE_NOPREEMPT */
	preemption_flag_t was;
#define LOCAL_preemption_pushoff() preemption_pushoff(&was)
#define LOCAL_preemption_pop()     preemption_pop(&was)
#define LOCAL_was                  was
#endif /* !LOCAL_HAVE_NOPREEMPT */
#ifdef LOCAL_HAVE_SENDER_THREAD
#define LOCAL_caller            caller
#define LOCAL_task_wake(thread) task_wake_as(thread, caller)
#else /* LOCAL_HAVE_SENDER_THREAD */
#define LOCAL_caller            THIS_TASK
#define LOCAL_task_wake(thread) task_wake(thread)
#endif /* !LOCAL_HAVE_SENDER_THREAD */
#ifdef LOCAL_HAVE_CLEANUP
#define LOCAL_exec_cleanup() (*cleanup->scc_cb)(cleanup)
#define LOCAL_cleanup        cleanup
#else /* LOCAL_HAVE_CLEANUP */
#define LOCAL_exec_cleanup() (void)0
#define LOCAL_cleanup        NULL
#endif /* !LOCAL_HAVE_CLEANUP */
#ifdef LOCAL_HAVE_FOR_FINI
#define LOCAL_TASK_CONNECTION_STAT_FFINI TASK_CONNECTION_STAT_FFINI
#else /* LOCAL_HAVE_FOR_FINI */
#define LOCAL_TASK_CONNECTION_STAT_FFINI 0
#endif /* !LOCAL_HAVE_FOR_FINI */
#ifndef CONFIG_NO_SMP
again_disable_preemption:
#endif /* !CONFIG_NO_SMP */

	/* Optimization:
	 * If nothing is connected to the signal, we don't have to disable
	 * preemption (though the extra check after preemption was  turned
	 * off is still  required so that  the connections-exist check  is
	 * interlocked with preemption being off). */
#if !defined(__OPTIMIZE_SIZE__) && !defined(LOCAL_HAVE_NOPREEMPT)
	if (!atomic_read(&self->s_con)) {
		LOCAL_exec_cleanup();
#ifdef LOCAL_HAVE_BROADCAST
		return result;
#else /* LOCAL_HAVE_BROADCAST */
		return false;
#endif /* !LOCAL_HAVE_BROADCAST */
	}
#endif /* !__OPTIMIZE_SIZE__ && !LOCAL_HAVE_NOPREEMPT */

	/* Make sure that preemption is disabled. */
	LOCAL_preemption_pushoff();
#ifdef CONFIG_NO_SMP
again:
#endif /* CONFIG_NO_SMP */
	con = atomic_read(&self->s_con);
	if (!con) {
#if !defined(CONFIG_NO_SMP) || defined(LOCAL_HAVE_TARGET_THREAD)
done_exec_cleanup:
#endif /* !CONFIG_NO_SMP || LOCAL_HAVE_TARGET_THREAD */
		LOCAL_exec_cleanup();
		LOCAL_preemption_pop();
#ifdef LOCAL_HAVE_BROADCAST
		return result;
#else /* LOCAL_HAVE_BROADCAST */
		return false;
#endif /* !LOCAL_HAVE_BROADCAST */
	}

	/* Wait if the SMP lock isn't available at the moment. */
#ifndef CONFIG_NO_SMP
	if unlikely((uintptr_t)con & SIG_CONTROL_SMPLOCK) {
		LOCAL_preemption_pop();
		task_tryyield_or_pause();
		goto again_disable_preemption;
	}
	/* Acquire the SMP-lock and validate that `con' is still correct. */
	if (!atomic_cmpxch_weak(&self->s_con, con,
	                        sig_smplock_set(con)))
		goto again_disable_preemption;
	con = sig_smplock_set(con);
	__IF0 {
again:
		con = atomic_read(&self->s_con);
		assert(sig_smplock_tst(con));
		if (!sig_smplock_clr(con)) {
			if (!atomic_cmpxch_weak(&self->s_con, con, 0))
				goto again;
			goto done_exec_cleanup;
		}
	}
#endif /* !CONFIG_NO_SMP */


#ifdef LOCAL_HAVE_BROADCAST
again_select_receiver:
	/* Find a suitable candidate:
	 *    During broadcast:
	 *       #1: Just use the first connection */
	receiver = sig_smplock_clr(con);
	assert(receiver);

	/* Unlink `receiver' from the connection chain, but keep ahold of the signal lock.
	 * The later must be done  to ensure that the  signal isn't broadcast again  until
	 * we're done, so-as to ensure that auto-re-prime completion callbacks are invoked
	 * for every time they are selected as signal targets. */
	if (!atomic_cmpxch_weak(&self->s_con, con,
	                        sig_smplock_set(receiver->tc_signext))) {
		con = atomic_read(&self->s_con);
		assert(sig_smplock_tst(con));
		assert(sig_smplock_clr(con) != NULL);
		goto again_select_receiver;
	}

	/* Acquire a lock to `receiver' */
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

	/* Unlink `receiver' from our chain and unlock `self' */
	next = receiver->tc_signext;
#ifndef CONFIG_NO_SMP
	assert(!sig_smplock_tst(next));
#endif /* !CONFIG_NO_SMP */
	atomic_write(&self->s_con, sig_smplock_set(next));

	/* Deal with special connections. */
	if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
		if (TASK_CONNECTION_STAT_ISDONE(target_cons)) {
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
			atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
			goto again;
		}
		if (!TASK_CONNECTION_STAT_ISPOLL(target_cons))
			++result;

		/* Special case: broadcast includes completion callbacks.
		 * Do this in a separate function so-as to keep the additional overhead outside of this function. */
		result += sig_intern_broadcast(self,
		                               LOCAL_sender,
		                               LOCAL_caller,
		                               (struct sig_completion *)receiver,
		                               NULL,
		                               LOCAL_cleanup,
		                               TASK_CONNECTION_STAT_BROADCAST |
		                               TASK_CONNECTION_STAT_FLOCK_OPT |
		                               LOCAL_TASK_CONNECTION_STAT_FFINI,
		                               LOCAL_was);
		return result;
	}
	target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);

	/* Try to set our signal as the one delivered to `target_cons'. */
	if (!atomic_cmpxch(&target_cons->tcs_dlvr, NULL, LOCAL_sender)) {
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
		atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
		goto again;
	}

	/* Suitable receiver. */
	if (!TASK_CONNECTION_STAT_ISPOLL(target_cons))
		++result;

	/* Wake-up the thread attached to the connection */
	{
		REF struct task *thread;
		thread = xincref(atomic_read(&target_cons->tcs_thread));
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
		atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
		if likely(thread) {
#ifdef CONFIG_NO_SMP
			if (!next)
#else /* CONFIG_NO_SMP */
			if (!next && atomic_cmpxch(&self->s_ctl, SIG_CONTROL_SMPLOCK, 0))
#endif /* !CONFIG_NO_SMP */
			{
				/* Special  case: No other  remaining signals. - In  this case, do the
				 * wake-up  of `thread' while no longer holding the SMP-lock to `self'
				 * We do this because `task_wake()' can be a bit smarter when it comes
				 * to scheduling if preemption is enabled (since in that case, it  can
				 * do direct context switches, possibly even over to `thread'  itself) */
				LOCAL_exec_cleanup();
				LOCAL_preemption_pop();
				LOCAL_task_wake(thread);
				decref_unlikely(thread);
				return result;
			}
			LOCAL_task_wake(thread);

			/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
			assert(thread->t_refcnt >= 1);
			if unlikely(atomic_fetchdec(&thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = NULL;
				result += sig_intern_broadcast(self,
				                               LOCAL_sender,
				                               LOCAL_caller,
				                               NULL,
				                               thread,
				                               LOCAL_cleanup,
				                               TASK_CONNECTION_STAT_BROADCAST |
				                               TASK_CONNECTION_STAT_FLOCK_OPT |
				                               LOCAL_TASK_CONNECTION_STAT_FFINI,
				                               LOCAL_was);
				return result;
			}
		}
	}
	goto again;
#else /* LOCAL_HAVE_BROADCAST */
	receiver = sig_smplock_clr(con);

#ifdef LOCAL_HAVE_TARGET_THREAD
	/* Find a suitable receiver: Just pick the first true-task  connection
	 *                           that points to the caller-given `target'.
	 * NOTE: Assuming that `target' isn't connected more than once, we don't
	 *       actually search for  the oldest connection  that qualifies  for
	 *       what we're looking  for, since there  really shouldn't be  more
	 *       than a single connection  matching those requirements to  begin
	 *       with! */
again_read_target_cons:
	target_cons = atomic_read(&receiver->tc_cons);
#ifndef CONFIG_NO_SMP
	while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
		task_pause();
		target_cons = atomic_read(&receiver->tc_cons);
	}
#endif /* !CONFIG_NO_SMP */
	if (TASK_CONNECTION_STAT_ISSPEC(target_cons) ||
	    atomic_read(&TASK_CONNECTION_STAT_ASCONS(target_cons)->tcs_thread) != target) {
		receiver = receiver->tc_signext;
		if (!receiver)
			goto done_exec_cleanup; /* No receiver found... */
		goto again_read_target_cons;
	}
#else /* LOCAL_HAVE_TARGET_THREAD */

	/* Find a suitable candidate:
	 *    During send:
	 *       #1: Use the last-in-chain, non-poll connection
	 *       #2: Broadcast all poll connections (but stop if
	 *           a non-poll connection shows up before we're
	 *           down)
	 *       #3: If no non-poll connection could be found,
	 *           return `false' */
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
		assert(!TASK_CONNECTION_STAT_ISDEAD(target_cons));
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
		                                                    LOCAL_TASK_CONNECTION_STAT_FFINI |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again_read_target_cons;
		task_connection_unlink_from_sig(self, receiver);
		sc = (struct sig_completion *)receiver;
		if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
			/* Special case: Deal with poll-based connections receiver. */
			return sig_intern_send(self,
			                       LOCAL_sender,
			                       LOCAL_caller,
			                       sc,
			                       NULL,
			                       LOCAL_cleanup,
			                       LOCAL_was);
		} else {
			/* Invoke this completion function as the only thing we do. */
			sig_completion_runsingle(self,
			                         sc,
			                         LOCAL_caller,
			                         LOCAL_sender,
			                         LOCAL_cleanup,
			                         LOCAL_was);
		}
		return true;
	}
#endif /* !LOCAL_HAVE_TARGET_THREAD */

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
		thread      = NULL;

		/* Set the delivered signal, and capture
		 * the thread  thread, if  there is  one */
		if (atomic_cmpxch(&target_cons->tcs_dlvr, NULL, LOCAL_sender))
			thread = xincref(atomic_read(&target_cons->tcs_thread));

		/* Unlock the connection. */
		atomic_write(&receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
		if (thread) {
			LOCAL_task_wake(thread);

			/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
			assert(thread->t_refcnt >= 1);
			if unlikely(atomic_fetchdec(&thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = NULL;
				return sig_intern_send(self,
				                       LOCAL_sender,
				                       LOCAL_caller,
				                       NULL,
				                       thread,
				                       LOCAL_cleanup,
				                       LOCAL_was);
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
	if (!atomic_cmpxch(&target_cons->tcs_dlvr, NULL, LOCAL_sender)) {
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
		LOCAL_exec_cleanup();
		LOCAL_preemption_pop();

		/* Wake-up the thread. */
		if likely(thread) {
			LOCAL_task_wake(thread);
			decref_unlikely(thread);
		}
	}
	return true;
#endif /* !LOCAL_HAVE_BROADCAST */
#undef LOCAL_TASK_CONNECTION_STAT_FFINI
#undef LOCAL_exec_cleanup
#undef LOCAL_cleanup
#undef LOCAL_was
#undef LOCAL_preemption_pushoff
#undef LOCAL_preemption_pop
#undef LOCAL_caller
#undef LOCAL_task_wake
#undef LOCAL_decref_task
#undef LOCAL_sender
}

#undef LOCAL_HAVE_SENDER_THREAD
#undef LOCAL_HAVE_TARGET_THREAD
#undef LOCAL_HAVE_CLEANUP
#undef LOCAL_HAVE_BROADCAST
#undef LOCAL_HAVE_FOR_FINI
#undef LOCAL_HAVE_SENDER
#undef LOCAL_HAVE_NOPREEMPT


DECL_END

#undef DEFINE_sig_send
#undef DEFINE_sig_send_nopr
#undef DEFINE_sig_altsend
#undef DEFINE_sig_altsend_nopr
#undef DEFINE_sig_sendto
#undef DEFINE_sig_sendto_nopr
#undef DEFINE_sig_altsendto
#undef DEFINE_sig_altsendto_nopr
#undef DEFINE_sig_broadcast
#undef DEFINE_sig_broadcast_nopr
#undef DEFINE_sig_altbroadcast
#undef DEFINE_sig_altbroadcast_nopr
#undef DEFINE_sig_broadcast_as_nopr
#undef DEFINE_sig_broadcast_cleanup_nopr
#undef DEFINE_sig_broadcast_as_cleanup_nopr
#undef DEFINE_sig_broadcast_for_fini
#undef DEFINE_sig_broadcast_for_fini_nopr
#undef DEFINE_sig_altbroadcast_for_fini
#undef DEFINE_sig_altbroadcast_for_fini_nopr
#undef DEFINE_sig_broadcast_as_for_fini_nopr
#undef DEFINE_sig_broadcast_for_fini_cleanup_nopr
#undef DEFINE_sig_broadcast_as_for_fini_cleanup_nopr
