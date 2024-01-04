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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIG_COMPLETION_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIG_COMPLETION_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/sig.h>

#if TASK_CONNECTION_STAT_BROADCAST == 0 && !defined(NDEBUG)
#include <hybrid/__assert.h>
#endif /* TASK_CONNECTION_STAT_BROADCAST == 0 && !NDEBUG */

#ifdef __CC__
DECL_BEGIN

struct task;
struct sig_completion;
struct sig_completion_context;

/* Signal post-completion callback (to-be registered from `sig_completion_t()')
 * NOTE: `context->scc_post' is unused  and its value  is undefined when  this
 *       callback is invoked. However, `scc_sender' and `scc_caller' are still
 *       valid when this function is invoked. */
typedef NOBLOCK NONNULL_T((1)) void
NOTHROW_T(FCALL *sig_postcompletion_t)(struct sig_completion_context *__restrict context,
                                       void *buf);

struct sig_completion_context {
	struct sig          *scc_sender; /* [1..1][const] The sender-signal (which may differ from `self->tc_sig'
	                                  * when the signal is being sent through something like `sig_altsend()') */
	struct task         *scc_caller; /* [1..1][const] The thread that (supposedly) is sending the  signal.
	                                  * In  order to support functions like `sig_broadcast_as_nopr()', the
	                                  * sig-post-completion callback should not make use of THIS_TASK, but
	                                  * instead assume that `scc_caller' is the caller's thread. */
	sig_postcompletion_t scc_post;   /* [0..1][out] When  non-NULL  upon  return  of  `sig_completion_t()',
	                                  * this callback will be enqueued to-be executed with the buffer given
	                                  * to  `sig_completion_t()'  once  all SMP-locks  have  been released.
	                                  * Using this  mechanism, a  signal completion  callback can  schedule
	                                  * further operations, which may not necessarily be SMP-lock friendly,
	                                  * to-be performed  at a  later point,  once all  SMP-locks have  been
	                                  * released.
	                                  * Note that even NOBLOCK functions may not always be  SMP-lock-safe,
	                                  * which  includes further calls to `sig_send()' / `sig_broadcast()'.
	                                  * When using  this mechanism,  you must  also make  sure to  account
	                                  * for the  possibility  that  either the  associated  signal  and/or
	                                  * used  `sig_completion' descriptor gets destroyed before/while this
	                                  * callback will eventually be executed.  As such, it is  recommended
	                                  * to use  the normal  signal completion  function as  a  first-stage
	                                  * callback to construct references to objects which are then written
	                                  * back to the  shared buffer  and eventually inherited  by a  second
	                                  * stage callback pointed to by this  field. For an example of  this,
	                                  * take a look at  the `struct rising_edge_detector' example code  at
	                                  * the bottom of this file. */
};


/* Callback prototype for signal completion functions.
 * WARNING: Signal completion functions are invoked in a context where SMP-locks are  held,
 *          meaning that the set of things they're allowed to do is _very_ limited. (As in:
 *          not even NOBLOCK functions are necessarily safe). To break out of this  prison,
 *          the completion function  may set-up a  phase-2 `sig_postcompletion_t'  callback
 *          that will be invoked once SMP-locks have been released. (s.a. `scc_post')
 * @param: self:        The signal completion controller.
 *                      HINT: The signal that was sent is `self->tc_sig'
 * @param: context:     Context information about how the completion function is being invoked.
 * @param: buf:         A  variable-length buffer (of  length `bufsize') that  is aligned by at
 *                      least `sizeof(void *)'  and will  be passed  to `context->scc_post'  if
 *                      that function pointer ends up as non-NULL. Note that the buffer pointer
 *                      itself may be `NULL' when the given `bufsize' is `0'
 * @param: bufsize:     The size of `buf' (in bytes)
 * @return: >  bufsize: The given `buf' is too small, and the caller must allocate a  larger
 *                      buffer of at least `return' bytes and call this function once again.
 * @return: <= bufsize: Success (when `context->scc_post' is  non-NULL, that function will  be
 *                      invoked once all SMP-locks have  been released). Warning: Try to  keep
 *                      the required buffer size as small as possible. - The associated buffer
 *                      needs to be allocated on-stack, and that space might be very  limited. */
typedef NOBLOCK NOPREEMPT NONNULL_T((1, 2)) size_t
NOTHROW_T(FCALL *sig_completion_t)(struct sig_completion *__restrict self,
                                   struct sig_completion_context *__restrict context,
                                   void *buf, size_t bufsize);

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
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) __BOOL
NOTHROW(KCALL sig_completion_reprime)(struct sig_completion *__restrict self,
                                      __BOOL for_poll);



struct sig_completion
#if defined(__cplusplus) && !defined(__WANT_SIG_COMPLETION_INIT)
    : task_connection              /* The underlying connection */
#define _sig_completion_con_ /* nothing */
#endif /* __cplusplus && !defined(__WANT_SIG_COMPLETION_INIT) */
{
#if !defined(__cplusplus) || defined(__WANT_SIG_COMPLETION_INIT)
	struct task_connection sc_con; /* The underlying connection */
#define _sig_completion_con_ sc_con.
#endif /* !__cplusplus || defined(__WANT_SIG_COMPLETION_INIT) */
	sig_completion_t       sc_cb;  /* [1..1][const] Completion callback. */
};

#ifdef __WANT_SIG_COMPLETION_INIT
#define SIG_COMPLETION_INIT(cb)                                                                            \
	{                                                                                                      \
		/* .sc_con = */ {                                                                                  \
			/* .tc_sig     = */ __NULLPTR,                                                                 \
			/* .tc_connext = */ __NULLPTR,                                                                 \
			/* .tc_signext = */ __NULLPTR,                                                                 \
			/* .tc_stat    = */ { (struct task_connections *)(uintptr_t)(TASK_CONNECTION_STAT_BROADCAST) } \
		},                                                                                                 \
		/* .sc_cb = */ cb                                                                                  \
	}
#endif /* __WANT_SIG_COMPLETION_INIT */

/* Initialize a given signal completion controller. */
#define sig_completion_init(self, cb)                                       \
	((self)->_sig_completion_con_ tc_stat = TASK_CONNECTION_STAT_BROADCAST, \
	 (self)->sc_cb                        = (cb))

/* Check if the given signal completion controller `self' was connected. */
#define sig_completion_wasconnected(self) \
	(!TASK_CONNECTION_STAT_ISDONE(__hybrid_atomic_load(&(self)->_sig_completion_con_ tc_stat, __ATOMIC_ACQUIRE)))

/* Connect the given signal completion controller to the specified signal.
 * The caller must  ensure that `completion'  hasn't been connected,  yet. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion)(struct sig *__restrict self,
                                      struct sig_completion *__restrict completion);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion_for_poll)(struct sig *__restrict self,
                                               struct sig_completion *__restrict completion);

/* NOTE: When  this  function returns,  the caller  can be  certain that  the callback
 *       of `self' is/won't be executed anymore, unless `self' is once again connected
 *       to some signal through use of `sig_connect_completion[_for_poll]()'
 * @return: true:  Completion function was disconnected before it could be  triggered,
 *                 or the last time the completion function was triggered, it made use
 *                 of `sig_completion_reprime()' to re-prime itself.
 * @return: false: Completion  function was already triggered, but not re-primed.
 *                 Alternatively, the signal completion function had already been
 *                 disconnected, or had never been connected to begin with. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_completion_disconnect)(struct sig_completion *__restrict self);





/************************************************************************/
/* SIGNAL MULTI-COMPLETION API                                          */
/************************************************************************/

/* Signal multi-completion routing.
 * Using  this, you can connect a single completion function onto multiple
 * signals, where the completion function itself is then invoked  whenever
 * any of  the signal  are triggered.  Note however,  that the  completion
 * callback must still behave just like a regular `sig_completion_t', with
 * the only addition being that  it can extract the completion  controller
 * via  `((struct sig_multicompletion_route *)self)->mr_con'.  Also   note
 * that as far as re-priming goes,  the completion function has to  decide
 * this  on a  per-signal basis, and  as far as  synchronization goes, the
 * completion function itself may be invoked simultaneously for  different
 * signals, though is  guarantied to  not be  invoked again  for the  same
 * signal until the  mandatory call  to `sig_completion_release()'  during
 * the PAYLOAD phase.
 *
 * A multi-completion  controller  can  be disconnected  from  all  attached
 * signals  by  using   `sig_multicompletion_disconnectall()',  which   also
 * guaranties  that any completion function which have be getting invoked on
 * some other CPU has already passed the point of `sig_completion_release()' */
struct sig_multicompletion;
struct _sig_multicompletion_route
#if defined(__cplusplus) && !defined(__WANT_SIG_COMPLETION_INIT)
    : sig_completion                    /* The underlying completion function */
#define __sig_multicompletion_route_com_ /* nothing */
#endif /* __cplusplus && !defined(__WANT_SIG_COMPLETION_INIT) */
{
#if !defined(__cplusplus) || defined(__WANT_SIG_COMPLETION_INIT)
	struct sig_completion       mr_com; /* The underlying completion function */
#define __sig_multicompletion_route_com_ mr_com.
#endif /* !__cplusplus || __WANT_SIG_COMPLETION_INIT */
	struct sig_multicompletion *mr_con; /* [1..1][const] The attached controller. */
};

/* Given a given  `struct sig_completion *sc', as  passed to  a
 * `sig_completion_t()', return the associated multi-completion
 * controller. The caller must ensure that `sc' is a completion
 * controller owned by some `struct sig_multicompletion', which
 * can  easily  be done  by  only invoking  this  function from
 * callbacks registered by
 *   - `sig_multicompletion_alloc()' or
 *   - `sig_multicompletion_connect()' */
#define sig_multicompletion_controller(sc) \
	(((struct _sig_multicompletion_route *)(sc))->mr_con)



struct _sig_multicompletion_set {
	struct _sig_multicompletion_set  *sms_next; /* [0..1][owned][WRITE_ONCE] More connections. */
	struct _sig_multicompletion_route sms_routes[CONFIG_TASK_STATIC_CONNECTIONS]; /* Static routes */
};

struct sig_multicompletion {
	/* TODO: The initial # of statically allocated routes should only be `1'! */
	struct _sig_multicompletion_set sm_set; /* Set of connections */
};

/* Initialize the given signal multi-completion controller. */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_init)(struct sig_multicompletion *__restrict self) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(self->sm_set.sms_routes); ++i)
		self->sm_set.sms_routes[i].__sig_multicompletion_route_com_ _sig_completion_con_ tc_stat = TASK_CONNECTION_STAT_BROADCAST;
	self->sm_set.sms_next = __NULLPTR;
}

/* Initialize the given signal multi-completion controller.
 * This function is allowed to assume that `self' was  pre-
 * initialized to all zeroes, as may be done by GFP_CALLOC. */
#if TASK_CONNECTION_STAT_BROADCAST != 0 || !defined(NDEBUG)
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_cinit)(struct sig_multicompletion *__restrict self) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(self->sm_set.sms_routes); ++i) {
#if TASK_CONNECTION_STAT_BROADCAST != 0
		self->sm_set.sms_routes[i].__sig_multicompletion_route_com_ _sig_completion_con_ tc_stat = TASK_CONNECTION_STAT_BROADCAST;
#else /* TASK_CONNECTION_STAT_BROADCAST != 0 */
		__hybrid_assert(self->sm_set.sms_routes[i].__sig_multicompletion_route_com_ _sig_completion_con_ tc_stat == 0);
#endif /* TASK_CONNECTION_STAT_BROADCAST == 0 */
	}
}
#else /* TASK_CONNECTION_STAT_BROADCAST != 0 || !NDEBUG */
#define sig_multicompletion_cinit(self) (void)0
#endif /* TASK_CONNECTION_STAT_BROADCAST == 0 && NDEBUG */

/* Finalize a given signal multi-completion controller.
 * WARNING: This  function will _not_  disconnect any remaining signals.
 *          If active connections could possibly remain, it is up to the
 *          caller to call `sig_multicompletion_disconnectall()'  first! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_fini)(struct sig_multicompletion *__restrict self);


/* Sever all (still-alive) connections that are active for `self'. Note that this  function
 * may not be called from inside of signal-completion-callbacks, or any other callback that
 * may  be executed in the context of holding  an SMP-lock. (though you are allowed to call
 * this function from a `sig_postcompletion_t' callback) */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_disconnectall)(struct sig_multicompletion *__restrict self);

/* Check if the given signal multi-completion controller `self' was connected. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL sig_multicompletion_wasconnected)(struct sig_multicompletion const *__restrict self);

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
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct sig_completion *FCALL
sig_multicompletion_alloc(struct sig_multicompletion *__restrict self,
                          sig_completion_t cb)
		THROWS(E_BADALLOC);
FUNDEF WUNUSED NONNULL((1)) struct sig_completion *
NOTHROW(FCALL sig_multicompletion_alloc_nx)(struct sig_multicompletion *__restrict self,
                                            sig_completion_t cb);

/* Allocate a completion descriptor from `completion' and connect it to `self' */
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void FCALL
sig_connect_multicompletion(struct sig *__restrict self,
                            struct sig_multicompletion *__restrict completion,
                            sig_completion_t cb)
		THROWS(E_BADALLOC);

/* No-except version of `sig_connect_multicompletion()'. Returns `false' if no
 * completion descriptor could be allocated from the pool of `completion', and
 * `true' if a completion descriptor  could be allocated and was  subsequently
 * connected. */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2, 3)) __BOOL
NOTHROW(FCALL sig_connect_multicompletion_nx)(struct sig *__restrict self,
                                              struct sig_multicompletion *__restrict completion,
                                              sig_completion_t cb);


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
FUNDEF NOBLOCK NONNULL((1)) void FCALL
sig_multicompletion_connect_from_task(struct sig_multicompletion *__restrict completion,
                                      sig_completion_t cb, bool for_poll)
		THROWS(E_BADALLOC);



#if 0 /* Signal completion usage example */
/* `struct rising_edge_detector'   can  be  used  for  implementing  an  asynchronous
 * connection to a signal (i.e. do the equivalent of `task_connect()' asynchronously,
 * including across return-to-userspace-and-back-via-syscall  or similar  situations) */
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
DEFINE_REFCNT_FUNCTIONS(struct rising_edge_detector, red_refcnt, rising_edge_detector_destroy)

PRIVATE NOBLOCK void
NOTHROW(FCALL red_phase2)(struct sig_completion_context *__restrict UNUSED(context),
                          void *buf) {
	REF struct rising_edge_detector *me;
	me = *(REF struct rising_edge_detector **)buf;
	sig_broadcast(&me->red_ondetect);
	decref_unlikely(me);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL red_phase1)(struct sig_completion *__restrict self,
                          struct sig_completion_context *__restrict context,
                          void *buf, size_t bufsize) {
	struct rising_edge_detector *me;
	me = container_of(self, struct rising_edge_detector, red_compl);
	/* Automatic re-prime. Could also be  implemented by counting the #  of
	 * detected  raising edges, rather than keeping a boolean flag, and re-
	 * connecting `me' to its signal prior to decrementing the edge-counter
	 * to `0' in `rising_edge_detector_waitfor()'
	 * Though admittedly, doing that would turn this into more of a semaphore,
	 * rather than a simple raising-edge-detector... */
	sig_completion_reprime(self, true);
	if (me->red_detected)
		return 0;
	if (bufsize < sizeof(void *))
		return sizeof(void *); /* Need a larger buffer */
	if (atomic_xch(&me->red_detected, true))
		return 0; /* Only need phase2 if we manage to set `red_detected' to true. */
	*(void **)buf = incref(me); /* Inherited by `red_phase2()' */
	context->scc_post = &red_phase2;
	return sizeof(void *);
}

PRIVATE NOBLOCK NONNULL((1)) REF struct rising_edge_detector *FCALL
rising_edge_detector_create(struct sig *__restrict signal) THROWS(E_BADALLOC) {
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

PRIVATE BLOCKING NONNULL((1)) void FCALL
rising_edge_detector_waitfor(struct rising_edge_detector *__restrict self) {
	while (!atomic_xch(&self->red_detected, false)) {
		task_connect(&self->red_ondetect);
		if unlikely(atomic_xch(&self->red_detected, false)) {
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
	 * back  to user-space, and `red' would still be
	 * able to pick up on `mysig' being triggered. */

	sig_broadcast(&mysig);

	/* Async task_waitfor() */
	rising_edge_detector_waitfor(red);
	decref(red);
}
#endif

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIG_COMPLETION_H */
