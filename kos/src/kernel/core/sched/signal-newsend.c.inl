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
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_sig_send) /**/ + defined(DEFINE_sig_altsend) + \
     defined(DEFINE_sig_broadcast) + defined(DEFINE_sig_altbroadcast)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_sig_send
/* Send signal `self' to exactly 1 connected thread
 * @return: true:  A waiting thread was signaled.
 * @return: false: The given signal didn't have any active connections. */
PUBLIC NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_send)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altsend)
#define HAVE_SENDER 1
PUBLIC NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sig_altsend)(struct sig *self,
                           struct sig *sender)
#elif defined(DEFINE_sig_broadcast)
#define HAVE_BROADCAST 1
/* Send signal to all connected threads
 * @return: * : The actual number of threads notified, not counting ghosts. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self)
#elif defined(DEFINE_sig_altbroadcast)
#define HAVE_BROADCAST 1
#define HAVE_SENDER 1
PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast)(struct sig *self,
                                struct sig *sender)
#endif /* ... */
{
#ifdef HAVE_BROADCAST
	size_t result = 0;
#endif /* HAVE_BROADCAST */
	struct task_connection *con;
	pflag_t was;
#ifdef HAVE_SENDER
#define SIG_SENDER sender
	assert(sender);
#else /* HAVE_SENDER */
#define SIG_SENDER self
#endif /* !HAVE_SENDER */
#ifdef HAVE_BROADCAST
again:
#endif /* HAVE_BROADCAST */
#if SIG_SMPLOCK_BIT != 0
	/* Lock the signal. */
	con = ATOMIC_READ(self->s_con);
	if (SIG_SMPLOCK_TST(con)) {
		if (SIG_SMPLOCK_CLR(con) == NULL)
			goto done_nocon_nounlock;
#define NEED_done_nocon_nounlock
		for (;;) {
			task_pause();
			was = PREEMPTION_PUSHOFF();
			con = (struct task_connection *)ATOMIC_FETCHOR(self->s_ctl, SIG_SMPLOCK_BIT);
			if (((uintptr_t)con & SIG_SMPLOCK_BIT) == 0)
				break;
preemption_pop_and_lock:
			PREEMPTION_POP(was);
		}
	} else {
		was = PREEMPTION_PUSHOFF();
		con = (struct task_connection *)ATOMIC_FETCHOR(self->s_ctl, SIG_SMPLOCK_BIT);
		if unlikely(((uintptr_t)con & SIG_SMPLOCK_BIT) != 0)
			goto preemption_pop_and_lock;
	}
#else /* SIG_SMPLOCK_BIT != 0 */
	was = PREEMPTION_PUSHOFF();
	con = ATOMIC_READ(self->s_con);
#endif /* SIG_SMPLOCK_BIT == 0 */

	if (con) {
#ifdef HAVE_BROADCAST
		struct task_connections *target_cons;
		target_cons = (struct task_connections *)ATOMIC_XCH(con->tc_stat,
		                                                    TASK_CONNECTION_STAT_SENT);
		assert((uintptr_t)target_cons != TASK_CONNECTION_STAT_BROADCAST);
		if (TASK_CONNECTION_STAT_CHECK(target_cons)) {
			/* Signal was already sent in the past.
			 * -> Change it's disposition to BROADCAST, and unlink it. */
			struct task_connection *next;
			assert((uintptr_t)target_cons == TASK_CONNECTION_STAT_SENT);
			next = con->tc_signext;
			COMPILER_BARRIER();
			ATOMIC_WRITE(con->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			ATOMIC_WRITE(self->s_con, next);
			PREEMPTION_POP(was);
		} else {
			REF struct task *target_thread = NULL;
			struct task_connection *next;
			/* Set the delivered signal, and capture
			 * the target_thread thread, if there is one */
			if (ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, SIG_SENDER))
				target_thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
			next = con->tc_signext;
			COMPILER_BARRIER();
			ATOMIC_WRITE(con->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			ATOMIC_WRITE(self->s_con, next);
			PREEMPTION_POP(was);
			if (target_thread) {
				task_wake(target_thread);
				decref_unlikely(target_thread);
			}
			++result;
		}
		/* Try to wake up the remaining threads. */
		goto again;
#else /* HAVE_BROADCAST */
		struct task_connections *target_cons;
		struct task_connection *receiver;
		REF struct task *target_thread;
again_find_receiver:
		receiver = NULL;
		for (;;) {
			uintptr_t status;
			status = ATOMIC_READ(con->tc_stat);
			assert(status != TASK_CONNECTION_STAT_BROADCAST);
			if (!TASK_CONNECTION_STAT_CHECK(status))
				receiver = con; /* This connection is still in alive. */
			assert(status == TASK_CONNECTION_STAT_SENT);
			con = con->tc_signext;
			if (!con)
				break;
		}
		if (receiver) {
			target_cons = ATOMIC_READ(receiver->tc_cons);
			if unlikely(TASK_CONNECTION_STAT_CHECK(target_cons))
				goto again_find_receiver;
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
			PREEMPTION_POP(was);
			if (target_thread) {
				task_wake(target_thread);
				decref_unlikely(target_thread);
			}
			return true;
		}
#endif /* !HAVE_BROADCAST */
	}


/*done_nocon:*/
	_sig_smp_lock_release(self);
	PREEMPTION_POP(was);
#ifdef NEED_done_nocon_nounlock
#undef NEED_done_nocon_nounlock
done_nocon_nounlock:
#endif /* NEED_done_nocon_nounlock */
#ifdef HAVE_BROADCAST
	return result;
#else /* HAVE_BROADCAST */
	return false;
#endif /* !HAVE_BROADCAST */
#undef SIG_SENDER
}

#undef HAVE_BROADCAST
#undef HAVE_SENDER


DECL_END

#undef DEFINE_sig_altbroadcast
#undef DEFINE_sig_broadcast
#undef DEFINE_sig_altsend
#undef DEFINE_sig_send

