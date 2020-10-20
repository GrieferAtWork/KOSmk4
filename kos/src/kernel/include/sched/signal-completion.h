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

struct task;
struct sig_completion;
struct sig_completion_context;

/* Signal post-completion callback (to-be registered from `sig_completion_t()')
 * NOTE: `context->scc_post' is unused and its value is undefined when this
 *       callback is invoked. The only reason that this one's here is so this
 *       function can make use of `scc_destroy_later' to prevent the dead-lock
 *       scenario described in `sig_broadcast_destroylater_nopr()' */
typedef NOBLOCK NONNULL((1)) void
/*NOTHROW*/ (FCALL *sig_postcompletion_t)(struct sig_completion_context *__restrict context,
                                          void *buf);

struct sig_completion_context {
	struct sig          *scc_sender;        /* [1..1][const] The sender-signal (which may differ from `self->tc_sig')
	                                         * when the signal is being sent through a function like `sig_altsend()' */
	struct task         *scc_caller;        /* [1..1][const] The thread that (supposedly) is sending the signal.
	                                         * In order to support functions like `sig_broadcast_as_nopr()',
	                                         * the sig-completion callback should not make use of THIS_TASK,
	                                         * but instead assume that `sender_thread' is the caller's thread. */
	sig_postcompletion_t scc_post;          /* [0..1][out] When non-NULL upon return of `sig_completion_t()',
	                                         * this callback will be enqueued to-be executed the buffer given
	                                         * to `sig_completion_t()' once all SMP-locks have been released.
	                                         * Using this mechanism, a signal completion callback can schedule
	                                         * further operations which may not necessarily be SMP-lock friendly
	                                         * to-be performed at a later point, once all SMP-locks have been
	                                         * released.
	                                         * Note that even NOBLOCK functions may not always be SMP-lock-safe,
	                                         * which includes further calls to `sig_send()' / `sig_broadcast()'
	                                         * When using this mechanism, you must also make sure to account
	                                         * for the possibility that either the associated signal and/or
	                                         * used sig_completion descriptor get destroyed before/while this
	                                         * callback will eventually be executed. As such it is recommended
	                                         * to have use the normal signal completion function as a first-stage
	                                         * callback to construct references to objects which are then written
	                                         * back to the shared buffer and eventually inherited by a second
	                                         * stage callback pointed to by this field. For an example of this,
	                                         * look at the example code at the bottom of this file. */
	REF struct task     *scc_destroy_later; /* [0..1] Chain of threads to-be destroyed later
	                                         * s.a. `sig_broadcast_destroylater_nopr()'
	                                         * WARNING: This pointer is only valid during execution of `sig_postcompletion_t()'
	                                         *          It is not valid during `sig_completion_t()'! */
};


/* Callback prototype for signal completion functions.
 * @param: self:        The signal completion controller.
 *                      HINT: The signal that was sent is `self->tc_sig'
 * @param: context:     Context information about how the completion function is being invoked.
 * @param: buf:         A variable-length buffer (of length `bufsize') that is aligned by at
 *                      least `sizeof(void *)' and will be passed to `context->scc_post' if
 *                      that function pointer ends up as non-NULL. Note that the buffer pointer
 *                      itself may be `NULL' when the given `bufsize' is `0'
 * @param: bufsize:     The size of `buf' (in bytes)
 * @return: >  bufsize: The given `buf' is too small, and the caller must allocate a larger
 *                      buffer of at least `return' bytes and call this function once again.
 * @return: <= bufsize: Success (when `context->scc_post' is non-NULL, that function will be
 *                      invoked once all SMP-locks have been released). Warning: Try to keep
 *                      the required buffer size as small as possible. - The associated buffer
 *                      needs to be allocated on-stack, and that space might be very limited. */
typedef NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
/*NOTHROW*/ (FCALL *sig_completion_t)(struct sig_completion *__restrict self,
                                      struct sig_completion_context *__restrict context,
                                      void *buf, size_t bufsize);

/* Re-prime the completion callback to be invoked once again the next time that the
 * attached signal is delivered. In this case, the completion function is responsible
 * to ensure that no-one is currently trying to destroy the associated signal. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) __BOOL
NOTHROW(KCALL sig_completion_reprime)(struct sig_completion *__restrict self,
                                      __BOOL for_poll);



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




#if 0 /* Signal completion usage example */
/* `struct rising_edge_detector' can be used for implementing an asynchronous
 * connection to a signal (i.e. do the equivalent of `task_connect()' asynchronous,
 * including across return-to-userspace-and-back-via-syscall and similar situations) */
struct rising_edge_detector {
	WEAK refcnt_t         red_refcnt;   /* Reference counter */
	struct sig_completion red_compl;    /* The used completion callback */
	bool                  red_detected; /* Set to true when a rising edge was detected */
	struct sig            red_ondetect; /* Broadcast when `red_detected' becomes true */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rising_edge_detector_destroy)(struct rising_edge_detector *__restrict self) {
	sig_completion_disconnect(&self->red_compl);
	kfree(self);
}
DEFINE_REFCOUNT_FUNCTIONS(struct rising_edge_detector, red_refcnt, rising_edge_detector_destroy)

PRIVATE NOBLOCK void
NOTHROW(FCALL red_phase2)(struct sig_completion_context *__restrict context,
                          void *buf) {
	REF struct rising_edge_detector *me;
	me = *(REF struct rising_edge_detector **)buf;
	sig_broadcast_destroylater(&me->red_ondetect, &context->scc_destroy_later);
	decref_unlikely(me);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL red_phase1)(struct sig_completion *__restrict self,
                          struct sig_completion_context *__restrict context,
                          void *buf, size_t bufsize) {
	struct rising_edge_detector *me;
	me = (struct rising_edge_detector *)self;
	/* Automatic re-prime. Could also be implemented by counting the # of
	 * detected raising edges, rather than keeping a boolean flag, and re-
	 * connecting `me' to its signal prior to decrementing the edge-counter
	 * to `0' in `rising_edge_detector_waitfor()' */
	sig_completion_reprime(self, true);
	if (me->red_detected)
		return 0;
	if (bufsize < sizeof(void *))
		return sizeof(void *); /* Need a larger buffer */
	if (ATOMIC_XCH(me->red_detected, true))
		return 0; /* Only need phase2 if we manage to set `red_detected' to true. */
	*(void **)buf = incref(me); /* Inherited by `red_phase2()' */
	context->scc_post = &red_phase2;
	return sizeof(void *);
}

PRIVATE NOBLOCK NONNULL((1)) REF struct rising_edge_detector *
NOTHROW(FCALL rising_edge_detector_create)(struct sig *__restrict signal) {
	REF struct rising_edge_detector *result;
	result = (REF struct rising_edge_detector *)kmalloc(sizeof(REF struct rising_edge_detector),
	                                                    GFP_NORMAL);
	result->red_refcnt   = 1;
	result->red_detected = false;
	sig_init(&result->red_ondetect);
	sig_completion_init(&result->red_compl, &red_phase1);
	sig_connect_completion_for_poll(signal, &result->red_compl);
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void FCALL
rising_edge_detector_waitfor(struct rising_edge_detector *__restrict self) {
	while (!ATOMIC_XCH(self->red_detected, false)) {
		task_connect(&self->red_ondetect);
		if unlikely(ATOMIC_XCH(self->red_detected, false)) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
}

PRIVATE struct sig mysig = SIG_INIT;
PRIVATE REF struct rising_edge_detector *red;

PRIVATE void demo(void) {
	/* This is essentially an async task_connect() */
	red = rising_edge_detector_create(&mysig);

	/* At this point, control flow could even return
	 * back to user-space, and `red' would still be
	 * able to pick up on `mysig' being triggered. */

	sig_broadcast(&mysig);

	/* Async task_waitfor() */
	rising_edge_detector_waitfor(red);
	decref(red);
}
#endif


#endif /* CONFIG_USE_NEW_SIGNAL_API */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_COMPLETION_H */
