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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_COMPLETION_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_COMPLETION_H 1

#include <kernel/compiler.h>

#include <sched/signal.h>

#ifdef __CC__
DECL_BEGIN

#ifdef CONFIG_USE_NEW_SIGNAL_API
/* Signal completion usage example:
 * >>
 * >> // `struct rising_edge_detector' can be used for implementing an asynchronous
 * >> // connection to a signal (i.e. do the equivalent of `task_connect()' asynchronous,
 * >> // including across return-to-userspace-and-back-via-syscall and similar situations)
 * >> struct rising_edge_detector: sig_completion {
 * >> 	bool       red_detected; // Set to true when a rising edge was detected
 * >> 	struct sig red_ondetect; // Broadcast when `red_detected' becomes true
 * >> };
 * >>
 * >> PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 4, 5)) void
 * >> NOTHROW(KCALL rising_edge_detector_completion)(struct sig_completion *__restrict self,
 * >>                                                struct task *__restrict sender_thread,
 * >>                                                unsigned int phase,
 * >>                                                struct task **__restrict pdestroy_later,
 * >>                                                struct sig *UNUSED(sender)) {
 * >> 	struct rising_edge_detector *me;
 * >> 	me = (struct rising_edge_detector *)self;
 * >> 	switch (phase) {
 * >> 	case SIG_COMPLETION_PHASE_SETUP:
 * >> #if 0 // (optional): Automatic re-prime
 * >> 		sig_completion_reprime(self, true);
 * >> #endif
 * >> 		break;
 * >> 	case SIG_COMPLETION_PHASE_PAYLOAD:
 * >> 		sig_completion_release(me);
 * >> 		// NOTE: There is a race here, since we've already unlocked `sig_completion_release()',
 * >> 		//       but are still accessing fields of `me'. This race could be fixed by making
 * >> 		//       `struct rising_edge_detector' heap-allocated & reference counted, with an
 * >> 		//       `incref(me)' before `sig_completion_release(me)', and a decref further down
 * >> 		//       below.
 * >> 		if (!ATOMIC_XCH(me->red_detected, true)) {
 * >> 			sig_broadcast_as_destroylater_nopr(&me->red_ondetect,
 * >> 			                                   sender_thread,
 * >> 			                                   pdestroy_later);
 * >> 		}
 * >> 		break;
 * >> 	default: __builtin_unreachable();
 * >> 	}
 * >> }
 * >>
 * >> PRIVATE NOBLOCK NONNULL((1)) void
 * >> NOTHROW(FCALL rising_edge_detector_init)(struct rising_edge_detector *__restrict self,
 * >>                                          struct sig *__restrict signal) {
 * >> 	sig_completion_init(self, &rising_edge_detector_completion);
 * >> 	sig_init(&self->red_ondetect);
 * >> 	self->red_detected = false;
 * >> 	sig_connect_completion_for_poll(signal, self);
 * >> }
 * >>
 * >> PRIVATE NOBLOCK NONNULL((1)) void
 * >> NOTHROW(FCALL rising_edge_detector_fini)(struct rising_edge_detector *__restrict self) {
 * >> 	sig_completion_disconnect(self);
 * >> }
 * >>
 * >> PRIVATE NOBLOCK NONNULL((1)) void FCALL
 * >> rising_edge_detector_waitfor(struct rising_edge_detector *__restrict self) {
 * >> 	while (!ATOMIC_XCH(self->red_detected, false)) {
 * >> 		task_connect(&self->red_ondetect);
 * >> 		if unlikely(ATOMIC_XCH(self->red_detected, false)) {
 * >> 			task_disconnectall();
 * >> 			break;
 * >> 		}
 * >> 		task_waitfor();
 * >> 	}
 * >> }
 * >>
 * >> PRIVATE struct sig mysig = SIG_INIT;
 * >> PRIVATE struct rising_edge_detector red;
 * >>
 * >> PRIVATE void demo(void) {
 * >> 	// Async task_connect()
 * >> 	rising_edge_detector_init(&red, &mysig);
 * >>
 * >> 	// At this point, control flow could even return
 * >> 	// back to user-space, and `red' would still be
 * >> 	// able to pick up on `mysig' being triggered.
 * >>
 * >> 	sig_broadcast(&mysig);
 * >>
 * >> 	// Async task_waitfor()
 * >> 	rising_edge_detector_waitfor(&red);
 * >> 	rising_edge_detector_fini(&red);
 * >> }
 */



struct sig_completion;
struct task;
/* Callback prototype for signal completion functions.
 * >> PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 4, 5)) void
 * >> NOTHROW(KCALL my_sig_completion)(struct sig_completion *__restrict self,
 * >>                                  struct task *__restrict sender_thread,
 * >>                                  unsigned int phase,
 * >>                                  struct task **__restrict pdestroy_later,
 * >>                                  struct sig *sender) {
 * >>     switch (phase) {
 * >>     case SIG_COMPLETION_PHASE_SETUP:
 * >>         sig_completion_reprime(self, signal); // Optional!
 * >>         break;
 * >>     case SIG_COMPLETION_PHASE_PAYLOAD:
 * >>         sig_completion_release(self);
 * >>         break;
 * >>     default: __builtin_unreachable();
 * >>     }
 * >> }
 * @param: self:           The signal completion controller.
 * @param: sender_thread:  The thread that (supposedly) is sending the signal.
 *                         In order to support functions like `sig_broadcast_as_nopr()',
 *                         the sig-completion callback should not make use of THIS_TASK,
 *                         but instead assume that `sender_thread' is the caller's thread.
 * @param: phase:          One of `SIG_COMPLETION_PHASE_*'
 *                         Note that once the first phase is triggered for any signal
 *                         completion function, it is guarantied that the second phase
 *                         will also be triggered before the next time preemption gets
 *                         re-enabled, _and_ before the SMP-lock of `self' is released.
 * @param: pdestroy_later: Chain of threads to-be destroyed later (s.a. `sig_broadcast_destroylater_nopr()')
 * @param: sender:         The sender-signal (which may differ from `self->tc_sig') when
 *                         the signal is being sent through a function like `sig_altsend()' */
typedef NOBLOCK NOPREEMPT NONNULL((1, 2, 4, 5)) void
/*NOTHROW*/ (KCALL *sig_completion_t)(struct sig_completion *__restrict self,
                                      struct task *__restrict sender_thread,
                                      unsigned int phase,
                                      struct task **__restrict pdestroy_later,
                                      struct sig *sender);
#define SIG_COMPLETION_PHASE_SETUP   0 /* First phase: At this point, the SMP-lock for `signal' is
                                        * still held, During this phase, the completion function
                                        * may use `sig_completion_reprime()' to re-prime itself.
                                        * Note that even NOBLOCK operation may not be safe during
                                        * this phase due to the internal SMP-lock. Such operations must
                                        * instead be performed during the `SIG_COMPLETION_PHASE_PAYLOAD'
                                        * phase. */
#define SIG_COMPLETION_PHASE_PAYLOAD 1 /* The payload phase: During this phase, the callback is
                                        * required to invoke `sig_completion_release(self)' in
                                        * order to unlock the completion callback, allowing a
                                        * potential other thread to cancel/destroy/re-connect the
                                        * completion function.
                                        * During this phase, the callback is also allowed to trigger
                                        * other signals (but should be aware that doing so may cause
                                        * other signal completion functions to do the same, possibly
                                        * resulting in a stack-overflow if this goes on for too long) */

/* Re-prime the completion callback to be invoked once again the next time that the
 * attached signal is delivered. In this case, the completion function is responsible
 * to ensure that no-one is currently trying to destroy the associated signal. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) __BOOL
NOTHROW(KCALL sig_completion_reprime)(struct sig_completion *__restrict self,
                                      __BOOL for_poll);

/* Release the SMP-lock of `self'. This function must be invoked from every signal
 * completion function when invoked with `phase == SIG_COMPLETION_PHASE_PAYLOAD'.
 * Once this function returns, `self' (i.e. the `struct sig_completion' argument)
 * must be thought of as pointing to free'd memory, since the return of this
 * function means that the completion function...
 *   ... can now get invoked again (assuming that the completion function
 *       used `sig_completion_reprime()' during the SETUP phase)
 *   ... may have already been disconnected (in case it reprimed itself
 *       earlier, which is done by `sig_completion_disconnect()', which
 *       in turn stops blocking once `sig_completion_release()' is called
 *       from the completion callback), following which the completion
 *       function's controller's backing memory may have been free'd.
 * Essentially, this function must be used in the same way as `aio_handle_release()'
 * has to be used from AIO completion functions. */
#ifdef CONFIG_NO_SMP
#define sig_completion_release(self) (void)0
#else /* CONFIG_NO_SMP */
#define sig_completion_release(self)                       \
	__hybrid_atomic_and(_sig_completion_con(self).tc_stat, \
	                    ~TASK_CONNECTION_STAT_FLOCK,       \
	                    __ATOMIC_RELEASE)
#endif /* !CONFIG_NO_SMP */



struct sig_completion
#ifdef __cplusplus
    : task_connection              /* The underlying connection */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct task_connection sc_con; /* The underlying connection */
#endif /* __cplusplus */
	sig_completion_t       sc_cb;  /* [1..1][const] Completion callback. */
};

#ifdef __cplusplus
#define _sig_completion_con(self) (*(self))
#else /* __cplusplus */
#define _sig_completion_con(self) (self)->sc_con
#endif /* !__cplusplus */

/* Initialize a given signal completion controller. */
#define sig_completion_init(self, cb)                                    \
	(_sig_completion_con(self).tc_stat = TASK_CONNECTION_STAT_BROADCAST, \
	 (self)->sc_cb                     = (cb))

/* Connect the given signal completion controller to the specified signal.
 * The caller must ensure that `completion' hasn't been connected, yet. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion)(struct sig *__restrict self,
                                      struct sig_completion *__restrict completion);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion_for_poll)(struct sig *__restrict self,
                                               struct sig_completion *__restrict completion);

/* NOTE: When this function returns, the caller can be certain that the callback
 *       of `self' is/won't be executed anymore, unless `self' is once again connected
 *       to some signal through use of `sig_connect_completion[_for_poll]()'
 * @return: true:  Completion function was disconnected before it could be triggered,
 *                 or the last time the completion function was triggered, it made use
 *                 of `sig_completion_reprime()' to re-prime itself.
 * @return: false: Completion function was already triggered, but not re-primed.
 *                 Alternatively, the signal completion function had already been
 *                 disconnected, or had never been connected to begin with. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_completion_disconnect)(struct sig_completion *__restrict self);

#endif /* CONFIG_USE_NEW_SIGNAL_API */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_COMPLETION_H */
