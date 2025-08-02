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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIG_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIG_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

/*[[[config CONFIG_TASK_STATIC_CONNECTIONS! = 3
 * Max  number of signal  connections guarantied to not
 * invoke `kmalloc()' and potentially throw exceptions.
 * ]]]*/
#ifndef CONFIG_TASK_STATIC_CONNECTIONS
#define CONFIG_TASK_STATIC_CONNECTIONS 3
#endif /* !CONFIG_TASK_STATIC_CONNECTIONS */
/*[[[end]]]*/



/* Use a new `struct sig` implementation as per ./sig.md */
#undef CONFIG_EXPERIMENTAL_KERNEL_SIG_V2
#if 1
#define CONFIG_EXPERIMENTAL_KERNEL_SIG_V2
#endif

DECL_BEGIN

/* `struct sigcon' offsets */
#define OFFSET_SIGCON_SIG  0
#define OFFSET_SIGCON_PREV __SIZEOF_POINTER__
#define OFFSET_SIGCON_NEXT (__SIZEOF_POINTER__ * 2)
#define OFFSET_SIGCON_CONS (__SIZEOF_POINTER__ * 3)
#define OFFSET_SIGCON_STAT (__SIZEOF_POINTER__ * 3)
#define SIZEOF_SIGCON      (__SIZEOF_POINTER__ * 4)
#define ALIGNOF_SIGCON     __ALIGNOF_POINTER__

/* `struct sigtaskcon' offsets */
#define OFFSET_SIGCON_TASK_THRNEXT SIZEOF_SIGCON
#define SIZEOF_SIGCON_TASK         (SIZEOF_SIGCON + __SIZEOF_POINTER__)
#define ALIGNOF_SIGCON_TASK        __ALIGNOF_POINTER__

/* `struct taskcons' offsets */
#define OFFSET_TASKCONS_DELIVER 0
#define OFFSET_TASKCONS_THREAD  __SIZEOF_POINTER__
#define OFFSET_TASKCONS_PREV    (__SIZEOF_POINTER__ * 2)
#define OFFSET_TASKCONS_CONS    (__SIZEOF_POINTER__ * 3)
#define OFFSET_TASKCONS_STATIC  (__SIZEOF_POINTER__ * 4)
#define SIZEOF_TASKCONS         (OFFSET_TASKCONS_STATIC + (SIZEOF_SIGCON_TASK * CONFIG_TASK_STATIC_CONNECTIONS))
#define _ALIGNOF_TASKCONS_TASK  __ALIGNOF_POINTER__
#define ALIGNOF_TASKCONS_TASK   _ALIGNOF_TASKCONS_TASK


#ifndef CONFIG_NO_SMP
#define SIG_SMPLOCK 0x0001 /* SMP lock bit for `(uintptr_t)struct sig::s_con' */
#endif /* !CONFIG_NO_SMP */

/* Possible values for `struct sigcon::sc_stat' */
#define SIGCON_STAT_F_POLL      0x0001 /* [valid_if(SIGCON_STAT_ISCONNECTED(.))] FLAG: This is a poll-based connection */
#define SIGCON_STAT_ST_THRBCAST 0x0000 /* [valid_if(!SIGCON_STAT_ISCONNECTED(.))] Status: connection was broadcast */
#define SIGCON_STAT_ST_THRSENT  0x0001 /* [valid_if(!SIGCON_STAT_ISCONNECTED(.))] Status: connection was sent */
#define SIGCON_STAT_TP_COMP     0x0002 /* [valid_if(!SIGCON_STAT_ISTHREAD(.))] Type code: this is a completion callback (and not a thread) */
/*efine SIGCON_STAT_TP_...      0x0004  * [valid_if(!SIGCON_STAT_ISTHREAD(.))] Type code: ... */
#define SIGCON_STAT_ISCONNECTED(st) ((st) >= 0x0002) /* Is this connection still connected (iow: is it owned by `sc_sig' and its lock?) */
#define SIGCON_STAT_ISTHREAD(st)    ((st) >= 0x0004) /* Is this a `struct sigtaskcon'? */
#define SIGCON_STAT_ISCOMP(st)      ((st) <= 0x0003) /* Assuming "SIGCON_STAT_ISCONNECTED() == true": Is this a `struct sigcompcon'? */
#define SIGCON_STAT_ISDEAD(st)      ((st) <= 0x0001) /* True if the connection was sent/broadcast */
#define SIGCON_CONS_MINALIGN    2 /* Minimal alignment required of `struct taskcons' */


#if SIGCON_CONS_MINALIGN > ALIGNOF_TASKCONS_TASK
#undef ALIGNOF_TASKCONS_TASK
#define ALIGNOF_TASKCONS_TASK SIGCON_CONS_MINALIGN
#endif /* SIGCON_CONS_MINALIGN > ALIGNOF_TASKCONS_TASK */


#ifdef __CC__

/* Cleanup function  which may  be scheduled  for invocation  before internal  resources
 * are  released and  post-completion callbacks  defined by  signal completion functions
 * are run.  This is  a  special mechanism  that is  required  to prevent  certain  race
 * conditions,  and  should be  used  in situations  where  a signal  is  kept allocated
 * through use  of an  SMP-lock which  must  be released  once the  `struct sig'  itself
 * no longer needs to be used, but  before any possible extended callbacks are  invoked,
 * as may be the result of decref()-ing woken threads (which may end up being destroyed,
 * and  consequently destroying a  whole bunch of other  things, including open handles)
 *
 * An example of a race condition prevented by this is:
 *      _asyncjob_main()
 *      aio_handle_complete_nopr()          // The connect() operation has completed
 *      aio_handle_generic_func()           // == ah_func  (note: this one must also invoke `aio_handle_release()')
 *      sig_broadcast()                     // !!! Wrong usage here
 *          decref_unlikely(target_thread)  // This actually ends up destroying `target_thread'
 *      task_destroy()
 *      fini_this_handle_manager()
 *      handman_destroy()
 *      handle_socket_decref()
 *      socket_destroy()
 *          decref_likely(self->sk_ncon.axr_obj)
 *      socket_connect_aio_destroy()
 *          aio_handle_generic_fini()
 *              aio_handle_fini()
 *              >> Deadlock here, since aio_handle_fini() can only return once
 *                 aio_handle_release()  has been called for the attached AIO.
 * The solution is to invoke `aio_handle_release(self)' from inside `scc_cb'
 *
 * NOTE: The cleanup callback itself gets invoked immediately after all internal
 *       SMP-lock have been  released (but before  preemption is re-enabled,  or
 *       post-exec signal completion callbacks are invoked)
 */
struct sig_cleanup_callback;
struct sig_cleanup_callback {
	/* [1..1] Cleanup callback. */
	NOBLOCK NOPREEMPT NONNULL_T((1)) void
	NOTHROW_T(FCALL *scc_cb)(struct sig_cleanup_callback *self);
	/* User-data goes here. */
};


struct task;
struct sig;
struct sigcon;
struct sigtaskcon;
struct sigcompcon;
struct taskcons;

struct sig {
	struct sigcon *s_con; /* [0..1]
	                       * [lock(READ(ATOMIC), WRITE(ATOMIC &&
	                       *     if (s_con == NULL): ATOMIC
	                       *     if (s_con != NULL): !PREEMPTION_ENABLED() && SIG_SMPLOCK
	                       * ))]
	                       * Oldest (next-to-wake) connection; Lowest bit is `SIG_SMPLOCK'
	                       * All connections in this list are guarantied to be  connected.
	                       * iow: `SIGCON_STAT_ISCONNECTED(sc_stat) == true` is an invariant.
	                       * NOTE: `SIG_SMPLOCK' is NEVER set when there are no connections.
	                       *       iow: `(uintptr_t)s_con  ==  SIG_SMPLOCK`  is  invalid,  and
	                       *       `SIG_SMPLOCK` must *ALWAYS* be or'd with a non-NULL sigcon. */
};

#define SIG_INIT_EX(c) { c }
#define SIG_INIT       { __NULLPTR }
#define sig_init(x)    (void)((x)->s_con = __NULLPTR)
#define sig_cinit(x)   __hybrid_assert((x)->s_con == __NULLPTR)
#define sig_isempty(x) (__hybrid_atomic_load(&(x)->s_con, __ATOMIC_ACQUIRE) == __NULLPTR)


#ifdef __OPTIMIZE_SIZE__
#define _sig_deliver_unlikely(self, expr) expr
#else /* __OPTIMIZE_SIZE__ */
#define _sig_deliver_unlikely(self, expr) (likely(sig_isempty(self)) ? 0 : expr)
#endif /* !__OPTIMIZE_SIZE__ */



struct sigcon {
	/* Signal connection.
	 * OWNER:
	 * - if (SIGCON_STAT_ISCONNECTED(sc_stat)): sc_sig
	 * - if (SIGCON_STAT_ISDEAD(sc_stat)):      OWNER_OF(<sigtaskcon>/<sigcompcon>)
	 */
	struct sig    *sc_sig;  /* [1..1][const] Signal of this connection */
	struct sigcon *sc_prev; /* [1..1][valid_if(SIGCON_STAT_ISCONNECTED(sc_stat))]
	                         * [lock(!PREEMPTION_ENABLED() && ((uintptr_t)sc_sig->s_con & SIG_SMPLOCK))] */
	struct sigcon *sc_next; /* [1..1][valid_if(SIGCON_STAT_ISCONNECTED(sc_stat))]
	                         * [lock(!PREEMPTION_ENABLED() && ((uintptr_t)sc_sig->s_con & SIG_SMPLOCK))] */
	union {
		struct taskcons *sc_cons; /* [1..1][const][valid_if(SIGCON_STAT_ISTHREAD(sc_stat))] Thread connections controller. */
		uintptr_t        sc_stat; /* [lock(READ(ATOMIC), WRITE(ATOMIC &&
		                           *  if (SIGCON_STAT_ISDEAD(sc_stat)):      CALLER IS OWNER_OF(<sigtaskcon>/<sigcompcon>)
		                           *  if (SIGCON_STAT_ISCONNECTED(sc_stat)): !PREEMPTION_ENABLED() && ((uintptr_t)sc_sig->s_con & SIG_SMPLOCK)
		                           * ))] */
	};
};

#define SIGCON_INIT(s, prev, next, cons) \
	{                                    \
		/* .sc_sig  = */ s,              \
		/* .sc_prev = */ prev,           \
		/* .sc_next = */ next,           \
		{ /* .sc_cons = */ cons }        \
	}


struct sigtaskcon;
struct sigtaskcon_slist { /* SLIST_HEAD(sigtaskcon_slist, sigtaskcon) */
	struct sigtaskcon *slh_first; /* [0..1] List head */
};

struct sigtaskcon
#if defined(__cplusplus) && !defined(__WANT_SIGTASKCON_INIT)
    : sigcon /* The underlying connection */
#define _sigtaskcon_con_ /* nothing */
#endif /* __cplusplus && !__WANT_SIGTASKCON_INIT */
{
#if !defined(__cplusplus) || defined(__WANT_SIGTASKCON_INIT)
	struct sigcon sct_con; /* The underlying connection */
#define _sigtaskcon_con_ sct_con.
#endif /* !__cplusplus || __WANT_SIGTASKCON_INIT */

	/* More fields here that may be used by `struct taskcons` to  track
	 * allocated task connections. However, all of these fields will be
	 * [lock(THIS_TASK)] (iow: thread-local), and so aren't relevant to
	 * the cross-thread part of the signal system. */
	struct { /* SLIST_ENTRY(sigtaskcon) */
		struct sigtaskcon *sle_next; /* [0..1] Next-link */
	} sct_thrnext; /* [0..1][lock(THIS_TASK)] Next connection within the thread. */
};

#ifdef __WANT_SIGTASKCON_INIT
#define SIGTASKCON_INIT(s, prev, next, cons, thrnext)          \
	{                                                          \
		/* .sct_con     = */ SIGCON_INIT(s, prev, next, cons), \
		/* .sct_thrnext = */ { thrnext }                       \
	}
#endif /* __WANT_SIGTASKCON_INIT */


#if ALIGNOF_TASKCONS_TASK > _ALIGNOF_TASKCONS_TASK
struct ATTR_ALIGNED(ALIGNOF_TASKCONS_TASK) taskcons
#else /* ALIGNOF_TASKCONS_TASK > _ALIGNOF_TASKCONS_TASK */
struct taskcons
#endif /* ALIGNOF_TASKCONS_TASK <= _ALIGNOF_TASKCONS_TASK */
{
	struct sig  *tcs_deliver; /* [0..1][lock(SET(ATOMIC && !PREEMPTION_ENABLED() && <SENDER:SIG_SMPLOCK>),
	                           *             CLEAR(ATOMIC && THIS_TASK))]
	                           * The first signal that was delivered, or NULL if none were, yet. */
	struct task *tcs_thread;  /* [0..1][lock(READ(ATOMIC), WRITE(ATOMIC && THIS_TASK))]
	                           * The thread that is listening  for this signal (which  is
	                           * always the thread  that owns this  controller), or  NULL
	                           * if this is not the currently-active controller, in which
	                           * case signals can still be received, but the thread  will
	                           * not receive any wake-ups. */

	/* More fields here that implement allocation of `struct  sigtaskcon`
	 * for  the  owning  thread. However,  all  of these  fields  will be
	 * "[lock(THIS_TASK)]" (iow: thread-local), and so aren't relevant to
	 * the cross-thread part of the signal system. */
	struct taskcons        *tcs_prev;   /* [0..1][lock(PRIVATE(THIS_TASK))]
	                                     * [(!= NULL) == (this == &this_rootcons)]
	                                     * Previous set of active connections. */
	struct sigtaskcon_slist tcs_cons;   /* [0..1][chain(->sct_thrnext)][lock(PRIVATE(THIS_TASK))]
	                                     * Chain of allocated connections. */
	struct sigtaskcon       tcs_static[CONFIG_TASK_STATIC_CONNECTIONS];
	                                    /* [*.in_use_if(.sc_sig != NULL)][lock(PRIVATE(THIS_TASK))]
	                                     * Statically allocated connections. Any connection that belongs
	                                     * to  this connections set, but points outside of this array is
	                                     * allocated dynamically using `kmalloc()', and as such, must be
	                                     * freed by `kfree()' */
};



/* Possible flags for `__sig_remcon' */
#define __SIG_REMCON_F_NORMAL  0x0000 /* Normal flags */
#define __SIG_REMCON_F_FORWARD 0x0001 /* If the "sigcon" has status "SIGCON_STAT_ST_THRSENT", try to forward the signal to another receiver. */

/* Internal, low-level API for adding/removing a signal connection */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL __sig_addcon)(struct sigcon *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void NOTHROW(FCALL __sig_addcon_nopr)(struct sigcon *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL __sig_remcon)(struct sigcon *__restrict self, unsigned int flags);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void NOTHROW(FCALL __sig_remcon_nopr)(struct sigcon *__restrict self, unsigned int flags);




/* Possible flags for `_sigcon_disconnect' */
#define _SIGCON_DISCONNECT_F_NORMAL  __SIG_REMCON_F_NORMAL  /* Normal flags */
#define _SIGCON_DISCONNECT_F_FORWARD __SIG_REMCON_F_FORWARD /* Try to forward a delivered, but unused signal to another receiver. */

#ifdef __INTELLISENSE__
/* Connect a given signal-connection `self' to a signal `to'
 * The caller must have already initialized:
 * - `self->sc_cons' / `self->sc_stat' as:
 *   - When `self' is `struct sigtaskcon':
 *     - `&<<associated_taskcons>>'
 *     - `&<<associated_taskcons>> | SIGCON_STAT_F_POLL'
 *   - When `self' is `struct sigcompcon':
 *     - `SIGCON_STAT_TP_COMP'
 *     - `SIGCON_STAT_TP_COMP | SIGCON_STAT_F_POLL'
 * These functions will then transfer ownership of `self' to `to',
 * until `to' delivers a signal to `self' (that doesn't see `self'
 * re-prime itself), or until `self' is manually disconnected,  as
 * done via `_sigcon_disconnect()'
 *
 * Behavior is undefined when `self' was already connected and no
 * call to `_sigcon_disconnect()' has yet  to be done, even  when
 * `to' has delivered a signal to `self' in the mean-time. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _sigcon_connect)(struct sigcon *__restrict self,
                               struct sig *__restrict to);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL _sigcon_connect_nopr)(struct sigcon *__restrict self,
                                    struct sig *__restrict to);

/* Disconnect `self' from its associated signal. Behavior is  undefined
 * when `self' wasn't connected (via `_sigcon_connect()'), or when this
 * function is called multiple times.
 * @param: flags: Set of `_SIGCON_DISCONNECT_F_*' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _sigcon_disconnect)(struct sigcon *__restrict self,
                                  unsigned int flags);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL _sigcon_disconnect_nopr)(struct sigcon *__restrict self,
                                       unsigned int flags);
#else /* __INTELLISENSE__ */
#define _sigcon_connect(self, to)            ((self)->sc_sig = (to), __sig_addcon(self))
#define _sigcon_connect_nopr(self, to)       ((self)->sc_sig = (to), __sig_addcon_nopr(self))
#define _sigcon_disconnect(self, flags)      __sig_remcon(self, flags)
#define _sigcon_disconnect_nopr(self, flags) __sig_remcon_nopr(self, flags)
#endif /* !__INTELLISENSE__ */





/* Possible values for `sig_xsend()::flags' / `sig_xsendmany()::flags' */
#define SIG_XSEND_F_NORMAL        0x0000 /* Normal flags */
#define SIG_XSEND_F_NOPR          0x0001 /* Caller guaranties that preemption is already disabled */
#define SIG_XSEND_F_FINI          0x0002 /* Disallow re-priming of signal completion callbacks */
#define SIG_XSEND_F_SENDER        0x0004 /* The "sender" argument is valid (when not set, use "self" instead) */
#define SIG_XSEND_F_CALLER        0x0008 /* The "caller" argument may differ from "THIS_TASK" */
#define SIG_XSEND_F_TARGET        0x0010 /* The "target" argument is valid */
#define SIG_XSEND_F_CLEANUP       0x0020 /* The "cleanup" argument is valid */
#define SIG_XSEND_F_LOCKED        0x0040 /* Inherit the SMP-lock to "self". May only be set when preemption is  disabled.
                                          * When this flag is set, "SIG_XSEND_F_NOPR" specifies the preemption state that
                                          * will be restored upon return:
                                          * - (flags & SIG_XSEND_F_NOPR) != 0 -> keep off on return
                                          * - (flags & SIG_XSEND_F_NOPR) == 0 -> turn on upon return */
#define SIG_XSEND_F_WAKE_WAITFOR  0x1000 /* s.a. `TASK_WAKE_FWAITFOR' */
#define SIG_XSEND_F_WAKE_HIGHPRIO 0x4000 /* s.a. `TASK_WAKE_FHIGHPRIO' */

/* Multi-purpose, generic signal sending (featuring all available options)
 * You probably shouldn't be using  these, since they're much slower  than
 * the special-purpose versions below. */
FUNDEF NOBLOCK /*NOPREEMPT_IF(flags & SIG_XSEND_F_NOPR)*/ NONNULL((1, 4)) __BOOL
NOTHROW(FCALL sig_xsend)(struct sig *self,
                         unsigned int flags,                   /* Set of `SIG_XSEND_F_*' */
                         struct sig *sender,                   /* For sig_altsend */
                         struct task *caller,                  /* For sig_sendas */
                         struct task *target,                  /* For sig_sendto */
                         struct sig_cleanup_callback *cleanup, /* For sig_send_cleanup */
                         struct sigcon *reprime);              /* Ring of extra connections to reprime (nullable) */
FUNDEF NOBLOCK /*NOPREEMPT_IF(flags & SIG_XSEND_F_NOPR)*/ NONNULL((1, 5)) size_t
NOTHROW(FCALL sig_xsendmany)(struct sig *self,
                             size_t maxcount,
                             unsigned int flags,                   /* Set of `SIG_XSEND_F_*' */
                             struct sig *sender,                   /* For sig_altsend */
                             struct task *caller,                  /* For sig_sendas */
                             struct sig_cleanup_callback *cleanup, /* For sig_send_cleanup */
                             struct sigcon *reprime,               /* Ring of extra connections to reprime (nullable) */
                             struct task *destroy_later);          /* Linked list of dead threads to-be destroyed later (linked via `sig_destroylater_next()') */
#define sig_xbroadcast(self, flags, sender, caller, cleanup, reprime, destroy_later) \
	sig_xsendmany(self, (size_t)-1, flags, sender, caller, cleanup, reprime, destroy_later)


/* Special-purpose signal sending function:
 * - *_nopr*:      The caller guaranties that preemption is disabled.
 * - *alt*:        Cause ther receiving thread to return a custom value from `task_waitfor()'.
 * - *sendto*:     Target a specific thread (ignoring all completion-receivers, and receivers for different threads).
 * - *as*:         Send while impersonating a specific thread
 * - *_cleanup*:   Invoke a given `cleanup' prior to doing any other kind of cleanup, but after having
 *                 released all internal SMP-locks. May be used to release further SMP-locks which may
 *                 have  been used to guard `self' from being destroyed (e.g. this can be used to call
 *                 `aio_handle_release()' when  sending a  signal from  an AIO  completion  function).
 *                 It is guarantied that `callback' is invoked exactly once.
 * - *_unlikely*:  Hint that it is unlikely that anyone is connected to the signal.
 * - *_for_fini*:  Disallow re-priming of signal completion callbacks
 *
 * @return: * : Indicative of the # of non-polling threads that received the signal (true==1, false==0)
 */
/*[[[deemon (printPrototypes from ".sig-config")();]]]*/
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL sig_send)(struct sig *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) __BOOL NOTHROW(FCALL sig_send_nopr)(struct sig *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_sendmany)(struct sig *__restrict self, size_t maxcount);
FUNDEF NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast)(struct sig *self, struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_nopr)(struct sig *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_nopr)(struct sig *self, struct sig *sender);
FUNDEF NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_for_fini)(struct sig *__restrict self);

/* Functions without fast-paths */
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL sig_altsend)(struct sig *self, struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) __BOOL NOTHROW(FCALL sig_altsend_nopr)(struct sig *self, struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) __BOOL NOTHROW(FCALL sig_send_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_altsend_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL sig_sendas)(struct sig *__restrict self, struct task *__restrict caller);
FUNDEF NOBLOCK NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_altsendas)(struct sig *self, struct sig *sender, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) __BOOL NOTHROW(FCALL sig_sendas_nopr)(struct sig *__restrict self, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_altsendas_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_sendas_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) __BOOL NOTHROW(FCALL sig_altsendas_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL sig_sendto)(struct sig *__restrict self, struct task *__restrict target);
FUNDEF NOBLOCK NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_altsendto)(struct sig *self, struct sig *sender, struct task *__restrict target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) __BOOL NOTHROW(FCALL sig_sendto_nopr)(struct sig *__restrict self, struct task *__restrict target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_altsendto_nopr)(struct sig *self, struct sig *sender, struct task *__restrict target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_sendto_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict target, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) __BOOL NOTHROW(FCALL sig_altsendto_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict target, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_sendasto)(struct sig *__restrict self, struct task *caller, struct task *target);
FUNDEF NOBLOCK NONNULL((1, 2, 3, 4)) __BOOL NOTHROW(FCALL sig_altsendasto)(struct sig *self, struct sig *sender, struct task *caller, struct task *target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) __BOOL NOTHROW(FCALL sig_sendasto_nopr)(struct sig *__restrict self, struct task *caller, struct task *target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) __BOOL NOTHROW(FCALL sig_altsendasto_nopr)(struct sig *self, struct sig *sender, struct task *caller, struct task *target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) __BOOL NOTHROW(FCALL sig_sendasto_cleanup_nopr)(struct sig *__restrict self, struct task *caller, struct task *target, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4, 5)) __BOOL NOTHROW(FCALL sig_altsendasto_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *caller, struct task *target, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altsendmany)(struct sig *self, struct sig *sender, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_sendmany_nopr)(struct sig *__restrict self, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altsendmany_nopr)(struct sig *self, struct sig *sender, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_sendmany_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altsendmany_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_sendmanyas)(struct sig *__restrict self, struct task *__restrict caller, size_t maxcount);
FUNDEF NOBLOCK NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altsendmanyas)(struct sig *self, struct sig *sender, struct task *__restrict caller, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_sendmanyas_nopr)(struct sig *__restrict self, struct task *__restrict caller, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altsendmanyas_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_sendmanyas_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) size_t NOTHROW(FCALL sig_altsendmanyas_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup, size_t maxcount);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini)(struct sig *self, struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t NOTHROW(FCALL sig_broadcast_for_fini_nopr)(struct sig *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini_nopr)(struct sig *self, struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcast_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcast_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcast_for_fini_cleanup_nopr)(struct sig *__restrict self, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcast_for_fini_cleanup_nopr)(struct sig *self, struct sig *sender, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas)(struct sig *__restrict self, struct task *__restrict caller);
FUNDEF NOBLOCK NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas)(struct sig *self, struct sig *sender, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas_nopr)(struct sig *__restrict self, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_broadcastas_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) size_t NOTHROW(FCALL sig_altbroadcastas_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas_for_fini)(struct sig *__restrict self, struct task *__restrict caller);
FUNDEF NOBLOCK NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas_for_fini)(struct sig *self, struct sig *sender, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t NOTHROW(FCALL sig_broadcastas_for_fini_nopr)(struct sig *__restrict self, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_altbroadcastas_for_fini_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t NOTHROW(FCALL sig_broadcastas_for_fini_cleanup_nopr)(struct sig *__restrict self, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3, 4)) size_t NOTHROW(FCALL sig_altbroadcastas_for_fini_cleanup_nopr)(struct sig *self, struct sig *sender, struct task *__restrict caller, struct sig_cleanup_callback *__restrict cleanup);
#if !defined(__INTELLISENSE__) && !defined(__OPTIMIZE_SIZE__)
#define sig_altsend(self, sender)                                               sig_xsend(self, SIG_XSEND_F_SENDER, sender, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altsend_nopr(self, sender)                                          sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER, sender, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_send_cleanup_nopr(self, cleanup)                                    sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP, __NULLPTR, THIS_TASK, __NULLPTR, cleanup, __NULLPTR)
#define sig_altsend_cleanup_nopr(self, sender, cleanup)                         sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, __NULLPTR, cleanup, __NULLPTR)
#define sig_sendas(self, caller)                                                sig_xsend(self, SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altsendas(self, sender, caller)                                     sig_xsend(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_sendas_nopr(self, caller)                                           sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altsendas_nopr(self, sender, caller)                                sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_sendas_cleanup_nopr(self, caller, cleanup)                          sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, __NULLPTR, caller, __NULLPTR, cleanup, __NULLPTR)
#define sig_altsendas_cleanup_nopr(self, sender, caller, cleanup)               sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, __NULLPTR, cleanup, __NULLPTR)
#define sig_sendto(self, target)                                                sig_xsend(self, SIG_XSEND_F_TARGET, __NULLPTR, THIS_TASK, target, __NULLPTR, __NULLPTR)
#define sig_altsendto(self, sender, target)                                     sig_xsend(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET, sender, THIS_TASK, target, __NULLPTR, __NULLPTR)
#define sig_sendto_nopr(self, target)                                           sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET, __NULLPTR, THIS_TASK, target, __NULLPTR, __NULLPTR)
#define sig_altsendto_nopr(self, sender, target)                                sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET, sender, THIS_TASK, target, __NULLPTR, __NULLPTR)
#define sig_sendto_cleanup_nopr(self, target, cleanup)                          sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, __NULLPTR, THIS_TASK, target, cleanup, __NULLPTR)
#define sig_altsendto_cleanup_nopr(self, sender, target, cleanup)               sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, target, cleanup, __NULLPTR)
#define sig_sendasto(self, caller, target)                                      sig_xsend(self, SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, __NULLPTR, caller, target, __NULLPTR, __NULLPTR)
#define sig_altsendasto(self, sender, caller, target)                           sig_xsend(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, sender, caller, target, __NULLPTR, __NULLPTR)
#define sig_sendasto_nopr(self, caller, target)                                 sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, __NULLPTR, caller, target, __NULLPTR, __NULLPTR)
#define sig_altsendasto_nopr(self, sender, caller, target)                      sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET, sender, caller, target, __NULLPTR, __NULLPTR)
#define sig_sendasto_cleanup_nopr(self, caller, target, cleanup)                sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, __NULLPTR, caller, target, cleanup, __NULLPTR)
#define sig_altsendasto_cleanup_nopr(self, sender, caller, target, cleanup)     sig_xsend(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP, sender, caller, target, cleanup, __NULLPTR)
#define sig_altsendmany(self, sender, maxcount)                                 sig_xsendmany(self, maxcount, SIG_XSEND_F_SENDER, sender, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_sendmany_nopr(self, maxcount)                                       sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR, __NULLPTR, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altsendmany_nopr(self, sender, maxcount)                            sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER, sender, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_sendmany_cleanup_nopr(self, cleanup, maxcount)                      sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP, __NULLPTR, THIS_TASK, cleanup, __NULLPTR, __NULLPTR)
#define sig_altsendmany_cleanup_nopr(self, sender, cleanup, maxcount)           sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, cleanup, __NULLPTR, __NULLPTR)
#define sig_sendmanyas(self, caller, maxcount)                                  sig_xsendmany(self, maxcount, SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altsendmanyas(self, sender, caller, maxcount)                       sig_xsendmany(self, maxcount, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_sendmanyas_nopr(self, caller, maxcount)                             sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altsendmanyas_nopr(self, sender, caller, maxcount)                  sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_sendmanyas_cleanup_nopr(self, caller, cleanup, maxcount)            sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, __NULLPTR, caller, cleanup, __NULLPTR, __NULLPTR)
#define sig_altsendmanyas_cleanup_nopr(self, sender, caller, cleanup, maxcount) sig_xsendmany(self, maxcount, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, cleanup, __NULLPTR, __NULLPTR)
#define sig_altbroadcast_for_fini(self, sender)                                 sig_xbroadcast(self, SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER, sender, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_broadcast_for_fini_nopr(self)                                       sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI, __NULLPTR, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altbroadcast_for_fini_nopr(self, sender)                            sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER, sender, THIS_TASK, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_broadcast_cleanup_nopr(self, cleanup)                               sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP, __NULLPTR, THIS_TASK, cleanup, __NULLPTR, __NULLPTR)
#define sig_altbroadcast_cleanup_nopr(self, sender, cleanup)                    sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, cleanup, __NULLPTR, __NULLPTR)
#define sig_broadcast_for_fini_cleanup_nopr(self, cleanup)                      sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CLEANUP, __NULLPTR, THIS_TASK, cleanup, __NULLPTR, __NULLPTR)
#define sig_altbroadcast_for_fini_cleanup_nopr(self, sender, cleanup)           sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP, sender, THIS_TASK, cleanup, __NULLPTR, __NULLPTR)
#define sig_broadcastas(self, caller)                                           sig_xbroadcast(self, SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altbroadcastas(self, sender, caller)                                sig_xbroadcast(self, SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_broadcastas_nopr(self, caller)                                      sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altbroadcastas_nopr(self, sender, caller)                           sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_broadcastas_cleanup_nopr(self, caller, cleanup)                     sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, __NULLPTR, caller, cleanup, __NULLPTR, __NULLPTR)
#define sig_altbroadcastas_cleanup_nopr(self, sender, caller, cleanup)          sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, cleanup, __NULLPTR, __NULLPTR)
#define sig_broadcastas_for_fini(self, caller)                                  sig_xbroadcast(self, SIG_XSEND_F_FINI | SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altbroadcastas_for_fini(self, sender, caller)                       sig_xbroadcast(self, SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_broadcastas_for_fini_nopr(self, caller)                             sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CALLER, __NULLPTR, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_altbroadcastas_for_fini_nopr(self, sender, caller)                  sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER, sender, caller, __NULLPTR, __NULLPTR, __NULLPTR)
#define sig_broadcastas_for_fini_cleanup_nopr(self, caller, cleanup)            sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, __NULLPTR, caller, cleanup, __NULLPTR, __NULLPTR)
#define sig_altbroadcastas_for_fini_cleanup_nopr(self, sender, caller, cleanup) sig_xbroadcast(self, SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CALLER | SIG_XSEND_F_CLEANUP, sender, caller, cleanup, __NULLPTR, __NULLPTR)
#endif /* !__INTELLISENSE__ && !__OPTIMIZE_SIZE__ */
#define sig_send_unlikely(self)                                                          _sig_deliver_unlikely(self, sig_send(self))
#define sig_altsend_unlikely(self, sender)                                               _sig_deliver_unlikely(self, sig_altsend(self, sender))
#define sig_send_nopr_unlikely(self)                                                     _sig_deliver_unlikely(self, sig_send_nopr(self))
#define sig_altsend_nopr_unlikely(self, sender)                                          _sig_deliver_unlikely(self, sig_altsend_nopr(self, sender))
#define sig_send_cleanup_nopr_unlikely(self, cleanup)                                    _sig_deliver_unlikely(self, sig_send_cleanup_nopr(self, cleanup))
#define sig_altsend_cleanup_nopr_unlikely(self, sender, cleanup)                         _sig_deliver_unlikely(self, sig_altsend_cleanup_nopr(self, sender, cleanup))
#define sig_sendas_unlikely(self, caller)                                                _sig_deliver_unlikely(self, sig_sendas(self, caller))
#define sig_altsendas_unlikely(self, sender, caller)                                     _sig_deliver_unlikely(self, sig_altsendas(self, sender, caller))
#define sig_sendas_nopr_unlikely(self, caller)                                           _sig_deliver_unlikely(self, sig_sendas_nopr(self, caller))
#define sig_altsendas_nopr_unlikely(self, sender, caller)                                _sig_deliver_unlikely(self, sig_altsendas_nopr(self, sender, caller))
#define sig_sendas_cleanup_nopr_unlikely(self, caller, cleanup)                          _sig_deliver_unlikely(self, sig_sendas_cleanup_nopr(self, caller, cleanup))
#define sig_altsendas_cleanup_nopr_unlikely(self, sender, caller, cleanup)               _sig_deliver_unlikely(self, sig_altsendas_cleanup_nopr(self, sender, caller, cleanup))
#define sig_sendto_unlikely(self, target)                                                _sig_deliver_unlikely(self, sig_sendto(self, target))
#define sig_altsendto_unlikely(self, sender, target)                                     _sig_deliver_unlikely(self, sig_altsendto(self, sender, target))
#define sig_sendto_nopr_unlikely(self, target)                                           _sig_deliver_unlikely(self, sig_sendto_nopr(self, target))
#define sig_altsendto_nopr_unlikely(self, sender, target)                                _sig_deliver_unlikely(self, sig_altsendto_nopr(self, sender, target))
#define sig_sendto_cleanup_nopr_unlikely(self, target, cleanup)                          _sig_deliver_unlikely(self, sig_sendto_cleanup_nopr(self, target, cleanup))
#define sig_altsendto_cleanup_nopr_unlikely(self, sender, target, cleanup)               _sig_deliver_unlikely(self, sig_altsendto_cleanup_nopr(self, sender, target, cleanup))
#define sig_sendasto_unlikely(self, caller, target)                                      _sig_deliver_unlikely(self, sig_sendasto(self, caller, target))
#define sig_altsendasto_unlikely(self, sender, caller, target)                           _sig_deliver_unlikely(self, sig_altsendasto(self, sender, caller, target))
#define sig_sendasto_nopr_unlikely(self, caller, target)                                 _sig_deliver_unlikely(self, sig_sendasto_nopr(self, caller, target))
#define sig_altsendasto_nopr_unlikely(self, sender, caller, target)                      _sig_deliver_unlikely(self, sig_altsendasto_nopr(self, sender, caller, target))
#define sig_sendasto_cleanup_nopr_unlikely(self, caller, target, cleanup)                _sig_deliver_unlikely(self, sig_sendasto_cleanup_nopr(self, caller, target, cleanup))
#define sig_altsendasto_cleanup_nopr_unlikely(self, sender, caller, target, cleanup)     _sig_deliver_unlikely(self, sig_altsendasto_cleanup_nopr(self, sender, caller, target, cleanup))
#define sig_sendmany_unlikely(self, maxcount)                                            _sig_deliver_unlikely(self, sig_sendmany(self, maxcount))
#define sig_altsendmany_unlikely(self, sender, maxcount)                                 _sig_deliver_unlikely(self, sig_altsendmany(self, sender, maxcount))
#define sig_sendmany_nopr_unlikely(self, maxcount)                                       _sig_deliver_unlikely(self, sig_sendmany_nopr(self, maxcount))
#define sig_altsendmany_nopr_unlikely(self, sender, maxcount)                            _sig_deliver_unlikely(self, sig_altsendmany_nopr(self, sender, maxcount))
#define sig_sendmany_cleanup_nopr_unlikely(self, cleanup, maxcount)                      _sig_deliver_unlikely(self, sig_sendmany_cleanup_nopr(self, cleanup, maxcount))
#define sig_altsendmany_cleanup_nopr_unlikely(self, sender, cleanup, maxcount)           _sig_deliver_unlikely(self, sig_altsendmany_cleanup_nopr(self, sender, cleanup, maxcount))
#define sig_sendmanyas_unlikely(self, caller, maxcount)                                  _sig_deliver_unlikely(self, sig_sendmanyas(self, caller, maxcount))
#define sig_altsendmanyas_unlikely(self, sender, caller, maxcount)                       _sig_deliver_unlikely(self, sig_altsendmanyas(self, sender, caller, maxcount))
#define sig_sendmanyas_nopr_unlikely(self, caller, maxcount)                             _sig_deliver_unlikely(self, sig_sendmanyas_nopr(self, caller, maxcount))
#define sig_altsendmanyas_nopr_unlikely(self, sender, caller, maxcount)                  _sig_deliver_unlikely(self, sig_altsendmanyas_nopr(self, sender, caller, maxcount))
#define sig_sendmanyas_cleanup_nopr_unlikely(self, caller, cleanup, maxcount)            _sig_deliver_unlikely(self, sig_sendmanyas_cleanup_nopr(self, caller, cleanup, maxcount))
#define sig_altsendmanyas_cleanup_nopr_unlikely(self, sender, caller, cleanup, maxcount) _sig_deliver_unlikely(self, sig_altsendmanyas_cleanup_nopr(self, sender, caller, cleanup, maxcount))
#define sig_broadcast_unlikely(self)                                                     _sig_deliver_unlikely(self, sig_broadcast(self))
#define sig_altbroadcast_unlikely(self, sender)                                          _sig_deliver_unlikely(self, sig_altbroadcast(self, sender))
#define sig_broadcast_nopr_unlikely(self)                                                _sig_deliver_unlikely(self, sig_broadcast_nopr(self))
#define sig_altbroadcast_nopr_unlikely(self, sender)                                     _sig_deliver_unlikely(self, sig_altbroadcast_nopr(self, sender))
#define sig_broadcast_for_fini_unlikely(self)                                            _sig_deliver_unlikely(self, sig_broadcast_for_fini(self))
#define sig_altbroadcast_for_fini_unlikely(self, sender)                                 _sig_deliver_unlikely(self, sig_altbroadcast_for_fini(self, sender))
#define sig_broadcast_for_fini_nopr_unlikely(self)                                       _sig_deliver_unlikely(self, sig_broadcast_for_fini_nopr(self))
#define sig_altbroadcast_for_fini_nopr_unlikely(self, sender)                            _sig_deliver_unlikely(self, sig_altbroadcast_for_fini_nopr(self, sender))
#define sig_broadcast_cleanup_nopr_unlikely(self, cleanup)                               _sig_deliver_unlikely(self, sig_broadcast_cleanup_nopr(self, cleanup))
#define sig_altbroadcast_cleanup_nopr_unlikely(self, sender, cleanup)                    _sig_deliver_unlikely(self, sig_altbroadcast_cleanup_nopr(self, sender, cleanup))
#define sig_broadcast_for_fini_cleanup_nopr_unlikely(self, cleanup)                      _sig_deliver_unlikely(self, sig_broadcast_for_fini_cleanup_nopr(self, cleanup))
#define sig_altbroadcast_for_fini_cleanup_nopr_unlikely(self, sender, cleanup)           _sig_deliver_unlikely(self, sig_altbroadcast_for_fini_cleanup_nopr(self, sender, cleanup))
#define sig_broadcastas_unlikely(self, caller)                                           _sig_deliver_unlikely(self, sig_broadcastas(self, caller))
#define sig_altbroadcastas_unlikely(self, sender, caller)                                _sig_deliver_unlikely(self, sig_altbroadcastas(self, sender, caller))
#define sig_broadcastas_nopr_unlikely(self, caller)                                      _sig_deliver_unlikely(self, sig_broadcastas_nopr(self, caller))
#define sig_altbroadcastas_nopr_unlikely(self, sender, caller)                           _sig_deliver_unlikely(self, sig_altbroadcastas_nopr(self, sender, caller))
#define sig_broadcastas_cleanup_nopr_unlikely(self, caller, cleanup)                     _sig_deliver_unlikely(self, sig_broadcastas_cleanup_nopr(self, caller, cleanup))
#define sig_altbroadcastas_cleanup_nopr_unlikely(self, sender, caller, cleanup)          _sig_deliver_unlikely(self, sig_altbroadcastas_cleanup_nopr(self, sender, caller, cleanup))
#define sig_broadcastas_for_fini_unlikely(self, caller)                                  _sig_deliver_unlikely(self, sig_broadcastas_for_fini(self, caller))
#define sig_altbroadcastas_for_fini_unlikely(self, sender, caller)                       _sig_deliver_unlikely(self, sig_altbroadcastas_for_fini(self, sender, caller))
#define sig_broadcastas_for_fini_nopr_unlikely(self, caller)                             _sig_deliver_unlikely(self, sig_broadcastas_for_fini_nopr(self, caller))
#define sig_altbroadcastas_for_fini_nopr_unlikely(self, sender, caller)                  _sig_deliver_unlikely(self, sig_altbroadcastas_for_fini_nopr(self, sender, caller))
#define sig_broadcastas_for_fini_cleanup_nopr_unlikely(self, caller, cleanup)            _sig_deliver_unlikely(self, sig_broadcastas_for_fini_cleanup_nopr(self, caller, cleanup))
#define sig_altbroadcastas_for_fini_cleanup_nopr_unlikely(self, sender, caller, cleanup) _sig_deliver_unlikely(self, sig_altbroadcastas_for_fini_cleanup_nopr(self, sender, caller, cleanup))
/*[[[end]]]*/


/* Check if the given signal has viable recipients (including poll-based connections) */
#define sig_hascon(self) (!sig_isempty(self))

/* Count the # of viable recipients of the given signal (including poll-based connections) */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_numcon)(struct sig *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_numcon_nopr)(struct sig *__restrict self);


/* Root connections set. */
DATDEF ATTR_PERTASK struct taskcons this_rootcons;
#define THIS_ROOTCONS (&PERTASK(this_rootcons))

/* [1..1][lock(PRIVATE(THIS_TASK))] Current set of in-use  connections.
 * Most of the time, this will simply point to `PERTASK(this_rootcons)' */
DATDEF ATTR_PERTASK struct taskcons *this_cons;
#define THIS_CONS PERTASK_GET(this_cons)


/* Push/pop the active  set of  connections:
 * >> struct sig a = SIG_INIT, b = SIG_INIT;
 * >> struct taskcons cons;
 * >> task_connect(&a);
 * >> assert(task_isconnected(&a));
 * >> assert(!task_isconnected(&b));
 * >>
 * >> task_pushcons(&cons);
 * >> assert(!task_isconnected(&a));
 * >> assert(!task_isconnected(&b));
 * >>
 * >> task_connect(&b);
 * >> assert(!task_isconnected(&a));
 * >> assert(task_isconnected(&b));
 * >>
 * >> task_disconnectall();
 * >> assert(!task_isconnected(&a));
 * >> assert(!task_isconnected(&b));
 * >>
 * >> task_popcons();
 * >> assert(task_isconnected(&a));
 * >> assert(!task_isconnected(&b)); */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushcons)(struct taskcons *__restrict cons);
FUNDEF NOBLOCK ATTR_RETNONNULL struct taskcons *
NOTHROW(FCALL task_popcons)(void);




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
FUNDEF NONNULL((1)) void FCALL
task_connect(struct sig *__restrict target)
		THROWS(E_BADALLOC);

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
FUNDEF NONNULL((1)) void FCALL
task_connect_for_poll(struct sig *__restrict target)
		THROWS(E_BADALLOC);

/* Helper  for `task_connect()' that allows for the assumption that the calling
 * thread has less than `CONFIG_TASK_STATIC_CONNECTIONS' connections right now. */
#define task_connect_nx(target)          NOEXCEPT_DO(task_connect(target))
#define task_connect_for_poll_nx(target) NOEXCEPT_DO(task_connect_for_poll(target))


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
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct sigtaskcon **
NOTHROW(FCALL task_findcon_p)(struct sig const *target);


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
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target);


/* Disconnect from all connected signals.
 * Signals with a state of `SIGCON_STAT_ST_THRSENT' will be forwarded. */
FUNDEF NOBLOCK void
NOTHROW(FCALL task_disconnectall)(void);

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
FUNDEF NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_receiveall)(void);

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
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_isconnected)(void);

/* Check if the calling thread was connected to the given signal.
 * Always returns `false' when `target == NULL'. */
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_isconnectedto)(struct sig const *target);
#else /* __INTELLISENSE__ */
#define task_isconnectedto(target) (task_findcon_p(target) != __NULLPTR)
#endif /* !__INTELLISENSE__ */

#ifdef __cplusplus
extern "C++" {
FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_isconnected)(struct sig const *target) {
	return task_isconnectedto(target);
}
} /* extern "C++" */
#endif /* __cplusplus */


/* Check if there is a signal that was delivered,
 * disconnecting all other  connected signals  if
 * this was the case.
 * @return: NULL: No signal is available.
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
FUNDEF NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_trywait)(void);

/* Wait for the first signal to be delivered, unconditionally
 * disconnecting all connected signals thereafter  (including
 * in the case of a timeout).
 * NOTE: Prior to fully starting to block, this function will call `task_serve()'
 * @param: abs_timeout:  The `ktime()' timeout for the wait.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 * @throw: * :           [task_waitfor] An error was thrown by an RPC function.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 * @return: NULL: No signal  has  become  available  (never  returned
 *                when `KTIME_INFINITE' is passed for `abs_timeout').
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
FUNDEF BLOCKING struct sig *FCALL
task_waitfor(ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);

/* Same as `task_waitfor', but don't serve RPC functions. */
FUNDEF BLOCKING struct sig *FCALL
task_waitfor_norpc(ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_WOULDBLOCK);

/* Same as `task_waitfor', but only service NX RPCs, and return `NULL'
 * if there are pending RPCs that  are allowed to throw exception,  or
 * if preemption was disabled, and the operation would have blocked. */
FUNDEF BLOCKING WUNUSED struct sig *
NOTHROW(FCALL task_waitfor_nx)(ktime_t abs_timeout DFL(KTIME_INFINITE));

/* Same as  `task_waitfor',  but  don't serve  RPC  functions,  and  return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
FUNDEF BLOCKING WUNUSED struct sig *
NOTHROW(FCALL task_waitfor_norpc_nx)(ktime_t abs_timeout DFL(KTIME_INFINITE));

#ifndef __sigset_t_defined
#define __sigset_t_defined
struct __sigset_struct;
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/* Same as `task_waitfor()', but uses `task_serve_with_sigmask()' instead of `task_serve()' */
FUNDEF BLOCKING NONNULL((1)) struct sig *FCALL
task_waitfor_with_sigmask(sigset_t const *__restrict sigmask,
                          ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);

#ifdef BUILDING_KERNEL_CORE
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_fix_taskcons)(struct task *__restrict self);
#endif /* BUILDING_KERNEL_CORE */




/*[[[config CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT: int = 4
 * Configuration option for standard synchronization  primitives.
 * Before connecting to a signal, try to yield a couple of  times
 * to try and get other threads to release some kind of lock,  as
 * `task_yield()' is a much faster operation than task_connect()+
 * task_waitfor(). Doing this may improve performance, especially
 * on single-core machines.
 * Note however that this option does not affect the behavior of
 * low-level  `struct sig' objects, but instead primitives found
 * in <sched/[...].h>, such as `struct mutex',  `struct rwlock',
 * `struct semaphore' and `struct shared_rwlock'
 * NOTE: The number that this is defined to describes the
 *       max  number of times `task_yield()' is attempted
 *       (implementing a kind-of spin-locking mechanism),
 *       before a signal is actually connected.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#undef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#define CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT 0
#elif !defined(CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT)
#define CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT 4
#elif (CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT + 0) <= 0
#undef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#define CONFIG_NO_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#define CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT 0
#endif /* ... */
/*[[[end]]]*/


/* Helper macro to implement spin-locking before connecting a signal:
 * >> while (!try_lock()) {
 * >>     TASK_POLL_BEFORE_CONNECT({
 * >>         if (try_lock())
 * >>             return true;
 * >>     });
 * >>     assert(!task_isconnected());
 * >>     task_connect(&lock_signal);
 * >>     TRY {
 * >>         if unlikely(try_lock()) {
 * >>             // Prevent a race condition:
 * >>             //     Lock became available after the last
 * >>             //     check, but before a connection was made
 * >>             task_disconnectall();
 * >>             return true;
 * >>         }
 * >>     } EXCEPT {
 * >>         task_disconnectall();
 * >>         RETHROW();
 * >>     }
 * >>     if (!task_waitfor(TIMEOUT))
 * >>         return false;
 * >> }
 * >> return true;
 */
#ifdef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#ifndef __task_tryyield_defined
#define __task_tryyield_defined
FUNDEF NOBLOCK_IF(!PREEMPTION_ENABLED())
unsigned int NOTHROW(KCALL task_tryyield)(void);
#endif /* !__task_tryyield_defined */
#if CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 1
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 2
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 3
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 4
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 5
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 6
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#else /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == ... */
#define TASK_POLL_BEFORE_CONNECT(...)                                             \
	do {                                                                          \
		unsigned int __poll_count = CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT; \
		do {                                                                      \
			if (task_tryyield() != 0)                                             \
				break;                                                            \
			__VA_ARGS__;                                                          \
		} while (--__poll_count);                                                 \
	}	__WHILE0
#endif /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT != ... */
#else /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT */
#define TASK_POLL_BEFORE_CONNECT(...) (void)0
#endif /* !CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT */


/************************************************************************/
/* SIGNAL WAITING HELPER MACROS                                         */
/************************************************************************/
#define _task_waituntil_ex_small(wait_if_false_expr, _connect, _task_waitfor) \
	do {                                                                      \
		_connect;                                                             \
		if ((wait_if_false_expr)) {                                           \
			task_disconnectall();                                             \
			break;                                                            \
		}                                                                     \
		_task_waitfor;                                                        \
	}	__WHILE1
#define _task_waituntil_ex_fast(wait_if_false_expr, _connect, _task_waitfor) \
	do {                                                                     \
		if ((wait_if_false_expr))                                            \
			break;                                                           \
		_connect;                                                            \
		if ((wait_if_false_expr)) {                                          \
			task_disconnectall();                                            \
			break;                                                           \
		}                                                                    \
		_task_waitfor;                                                       \
	}	__WHILE1
#ifdef __OPTIMIZE_SIZE__
#define _task_waituntil_ex _task_waituntil_ex_small
#else /* __OPTIMIZE_SIZE__ */
#define _task_waituntil_ex _task_waituntil_ex_fast
#endif /* !__OPTIMIZE_SIZE__ */

/* Wait for a given signal while/until a given expression becomes true. */
#define task_waituntil(signal, wait_if_false_expr)             _task_waituntil_ex(wait_if_false_expr, task_connect(signal), task_waitfor())
#define task_waitwhile(signal, wait_if_true_expr)              task_waituntil(signal, !(wait_if_true_expr))
#define task_waituntil_norpc(signal, wait_if_false_expr)       _task_waituntil_ex(wait_if_false_expr, task_connect(signal), task_waitfor_norpc())
#define task_waitwhile_norpc(signal, wait_if_true_expr)        task_waituntil_norpc(signal, !(wait_if_true_expr))
#define task_waituntil_small(signal, wait_if_false_expr)       _task_waituntil_ex_small(wait_if_false_expr, task_connect(signal), task_waitfor())
#define task_waitwhile_small(signal, wait_if_true_expr)        task_waituntil_small(signal, !(wait_if_true_expr))
#define task_waituntil_norpc_small(signal, wait_if_false_expr) _task_waituntil_ex_small(wait_if_false_expr, task_connect(signal), task_waitfor_norpc())
#define task_waitwhile_norpc_small(signal, wait_if_true_expr)  task_waituntil_norpc_small(signal, !(wait_if_true_expr))
#define task_waituntil_fast(signal, wait_if_false_expr)        _task_waituntil_ex_fast(wait_if_false_expr, task_connect(signal), task_waitfor())
#define task_waitwhile_fast(signal, wait_if_true_expr)         task_waituntil_fast(signal, !(wait_if_true_expr))
#define task_waituntil_norpc_fast(signal, wait_if_false_expr)  _task_waituntil_ex_fast(wait_if_false_expr, task_connect(signal), task_waitfor_norpc())
#define task_waitwhile_norpc_fast(signal, wait_if_true_expr)   task_waituntil_norpc_fast(signal, !(wait_if_true_expr))
#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIG_H */
