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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGCOMP_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGCOMP_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

/*[[[config CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS! = 1
 * # of statically pre-allocated connections available
 * to any `struct sigmulticomp' out-of-the-box.
 * ]]]*/
#ifndef CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS
#define CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS 1
#endif /* !CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS */
/*[[[end]]]*/

#ifdef __CC__
DECL_BEGIN

struct task;
struct sig;
struct sigcompcon;
struct sigcompctx;


/* Signal post-completion callback (to-be registered from `sigcomp_cb_t()')
 * NOTE: `ctx->scc_post' is unused and its value is undefined when  this
 *       callback is invoked. However, `scc_sender' and `scc_caller' are
 *       still valid when this function is invoked. */
typedef NOBLOCK NONNULL_T((1)) void
NOTHROW_T(FCALL *sigcomp_postcb_t)(struct sigcompctx *__restrict ctx,
                                   void *buf);

struct sigcompctx {
	struct sig          *scc_sender; /* [1..1][const] The sender-signal (which may differ from `self->sc_sig'
	                                  * when the signal is being sent through something like `sig_altsend()') */
	struct task         *scc_caller; /* [1..1][const] The thread that (supposedly) is sending the  signal.
	                                  * In  order to support  functions like `sig_broadcastas_nopr()', the
	                                  * sig-post-completion callback should not make use of THIS_TASK, but
	                                  * instead assume that `scc_caller' is the caller's thread. */
	sigcomp_postcb_t     scc_post;   /* [0..1][out] When non-NULL upon return of `sigcomp_cb_t()', this
	                                  * callback will be enqueued to-be executed with the buffer  given
	                                  * to `sigcomp_cb_t()' once all SMP-locks have been released.
	                                  *
	                                  * Using this  mechanism, a  signal completion  callback can  schedule
	                                  * further operations, which may not necessarily be SMP-lock friendly,
	                                  * to-be performed  at a  later point,  once all  SMP-locks have  been
	                                  * released.
	                                  *
	                                  * Note that even NOBLOCK functions may not always be SMP-lock-safe,
	                                  * which includes further calls to `sig_send()' / `sig_broadcast()'.
	                                  * When using this  mechanism, you  must also make  sure to  account
	                                  * for the possibility that either the associated signal and/or used
	                                  * `sigcompcon' descriptor gets destroyed before/while this callback
	                                  * will  eventually be executed.  As such, it  is recommended to use
	                                  * the normal signal completion  function as a first-stage  callback
	                                  * to construct references to objects which are then written back to
	                                  * the shared  buffer and  eventually inherited  by a  second  stage
	                                  * callback pointed to by this field. For an example of this, take a
	                                  * look at `struct rising_edge_detector' in ./sigcomp.md */
#define SIGCOMP_MODE_F_NORMAL    0x0000 /* Normal status (don't reprime + signal accepted) */
#define SIGCOMP_MODE_F_REPRIME   0x0001 /* Re-prime the connection, allowing for uninterrupted monitoring of signals being sent. */
#define SIGCOMP_MODE_F_NONVIABLE 0x0002 /* Signal could not be received. (in the case of `sig_send()', search for another receiver) */
	unsigned int         scc_mode;   /* [out] Signal completion status (set of `SIGCOMP_MODE_F_*'; defaults to 0)
	                                  * NOTE: This field may only be accessed during phase-1 callbacks. */
};

/* Callback prototype for signal completion functions.
 * WARNING: Signal completion functions are invoked in a context where SMP-locks are  held,
 *          meaning that the set of things they're allowed to do is _very_ limited. (As in:
 *          not even NOBLOCK functions are necessarily safe). To break out of this  prison,
 *          the completion function may set-up  a phase-2 `sigcomp_postcb_t' callback  that
 *          will be invoked once SMP-locks have been released. (s.a. `scc_post')
 * @param: self:        The signal completion controller.
 *                      HINT: The signal that was sent is `self->sc_sig'
 * @param: ctx:         Context information about how the completion function is being invoked.
 * @param: buf:         A variable-length buffer (of length `bufsize') that is aligned by at
 *                      least `sizeof(void *)' and will be passed to `ctx->scc_post' if that
 *                      function pointer ends up as  non-NULL. Note that the buffer  pointer
 *                      itself may be `NULL' when the given `bufsize' is `0'
 * @param: bufsize:     The size of `buf' (in bytes)
 * @return: >  bufsize: The given `buf' is too small, and the caller must allocate a  larger
 *                      buffer of at least `return' bytes and call this function once again.
 * @return: <= bufsize: Success (when  `ctx->scc_post'  is  non-NULL, that  function  will  be
 *                      invoked once all SMP-locks have  been released). Warning: Try to  keep
 *                      the required buffer size as small as possible. - The associated buffer
 *                      needs to be allocated on-stack, and that space might be very  limited. */
typedef NOBLOCK NOPREEMPT NONNULL_T((1, 2)) size_t
NOTHROW_T(FCALL *sigcomp_cb_t)(struct sigcompcon *__restrict self,
                               struct sigcompctx *__restrict ctx,
                               void *buf, size_t bufsize);

/* Helper macros to enable/disable polling, for use by `sigcomp_cb_t'
 * when   `ctx->scc_mode |= SIGCOMP_MODE_F_REPRIME'   was    enabled.
 *
 * By default, the  polling-mode stays whatever  it was before  the
 * signal was delivered to the completion function, so these macros
 * only have to be used when wishing to use a different mode. */
#define sigcompcon_enablepoll(self) \
	__hybrid_atomic_or(&(self)->_sigcompcon_con_ sc_stat, SIGCON_STAT_F_POLL, __ATOMIC_SEQ_CST)
#define sigcompcon_disablepoll(self) \
	__hybrid_atomic_and(&(self)->_sigcompcon_con_ sc_stat, ~SIGCON_STAT_F_POLL, __ATOMIC_SEQ_CST)




struct sigcompcon
#if defined(__cplusplus) && !defined(__WANT_SIGCOMPCON_INIT)
    : sigcon /* The underlying connection */
#define _sigcompcon_con_  /* nothing */
#define _sigcompcon_ascon /* nothing */
#endif /* __cplusplus && !defined(__WANT_SIGCOMPCON_INIT) */
{
#if !defined(__cplusplus) || defined(__WANT_SIGCOMPCON_INIT)
	struct sigcon scc_con; /* The underlying connection */
#define _sigcompcon_con_ scc_con.
#define _sigcompcon_ascon(x) (&(x)->scc_con)
#endif /* !__cplusplus || defined(__WANT_SIGCOMPCON_INIT) */
	sigcomp_cb_t  scc_cb;  /* [1..1][const] Completion callback. */
};

#ifdef __WANT_SIGCOMPCON_INIT
#define SIGCOMPCON_INIT_EX(s, prev, next, flags, cb) \
	{ SIGCON_INIT(s, prev, next, (struct taskcons *)(SIGCON_STAT_TP_COMP | (flags))), cb }
#define SIGCOMPCON_INIT(cb) \
	SIGCOMPCON_INIT_EX(__NULLPTR, __NULLPTR, __NULLPTR, 0, cb)
#endif /* __WANT_SIGCOMPCON_INIT */


/* Initialize a given signal completion controller.
 *
 * After use  of this  function, the  connection can  be
 * connected to some signal using `sigcompcon_connect()' */
#define sigcompcon_init(self, cb) (void)((self)->scc_cb = (cb))


/* Connection mode flags for:
 * - sigcompcon_connect_ex
 * - sigmulticomp_connect_ex
 * - sigmulticomp_connect_ex_nx
 */
#define SIGCOMPCON_CONNECT_F_NORMAL 0                  /* Normal connection */
#define SIGCOMPCON_CONNECT_F_POLL   SIGCON_STAT_F_POLL /* Polling connection */

/* Connect the  given signal  completion controller  to the  specified
 * signal. The caller must ensure that `self' isn't already connected.
 *
 * NOTE: After receiving a signal, and  not re-priming itself, `self'  may
 *       still be considered as "connected", and `sigcompcon_disconnect()'
 *       should be called before another call to `sigcompcon_connect()'.
 * @param: flags: Set of `SIGCOMPCON_CONNECT_F_*' */
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL sigcompcon_connect)(struct sigcompcon *__restrict self, struct sig *__restrict target);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL sigcompcon_connect_for_poll)(struct sigcompcon *__restrict self, struct sig *__restrict target);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL sigcompcon_connect_ex)(struct sigcompcon *__restrict self, struct sig *__restrict target, uintptr_t flags);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) void NOTHROW(FCALL sigcompcon_connect_nopr)(struct sigcompcon *__restrict self, struct sig *__restrict target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) void NOTHROW(FCALL sigcompcon_connect_for_poll_nopr)(struct sigcompcon *__restrict self, struct sig *__restrict target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) void NOTHROW(FCALL sigcompcon_connect_ex_nopr)(struct sigcompcon *__restrict self, struct sig *__restrict target, uintptr_t flags);
#else /* __INTELLISENSE__ */
#define sigcompcon_connect_ex(self, target, flags)                     \
	((self)->_sigcompcon_con_ sc_stat = SIGCON_STAT_TP_COMP | (flags), \
	 _sigcon_connect(_sigcompcon_ascon(self), target))
#define sigcompcon_connect_ex_nopr(self, target, flags)                \
	((self)->_sigcompcon_con_ sc_stat = SIGCON_STAT_TP_COMP | (flags), \
	 _sigcon_connect_nopr(_sigcompcon_ascon(self), target))
#define sigcompcon_connect(self, target)               sigcompcon_connect_ex(self, target, SIGCOMPCON_CONNECT_F_NORMAL)
#define sigcompcon_connect_for_poll(self, target)      sigcompcon_connect_ex(self, target, SIGCOMPCON_CONNECT_F_POLL)
#define sigcompcon_connect_nopr(self, target)          sigcompcon_connect_ex_nopr(self, target, SIGCOMPCON_CONNECT_F_NORMAL)
#define sigcompcon_connect_for_poll_nopr(self, target) sigcompcon_connect_ex_nopr(self, target, SIGCOMPCON_CONNECT_F_POLL)
#endif /* !__INTELLISENSE__ */


/* Disconnect  a "Signal Completion Connection" `self' after it had previously
 * been connected (via `sigcompcon_connect()'). After a call to this function,
 * it is guarantied that `self->scc_cb'  isn't being executed anymore  (though
 * note  that it is possible for a  related `sigcomp_postcb_t' to still run on
 * another thread, though  since those callbacks  shouldn't access the  sigcon
 * that was used to deliver the signal, that shouldn't matter)
 *
 * NOTE: This function *may* still be called after "self" has been "delievered"
 *       (even when "self" didn't re-prime itself),  in which case the call  is
 *       a no-op (though only 1 such call  is allowed). iow: you don't have  to
 *       worry about "self" having received (or currently receiving) a  signal. */
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigcompcon_disconnect)(struct sigcompcon *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL sigcompcon_disconnect_nopr)(struct sigcompcon *__restrict self);
#else /* __INTELLISENSE__ */
#define sigcompcon_disconnect(self) \
	_sigcon_disconnect(_sigcompcon_ascon(self), _SIGCON_DISCONNECT_F_FORWARD)
#define sigcompcon_disconnect_nopr(self) \
	_sigcon_disconnect_nopr(_sigcompcon_ascon(self), _SIGCON_DISCONNECT_F_FORWARD)
#endif /* !__INTELLISENSE__ */







/************************************************************************/
/* SIGNAL MULTI-COMPLETION API                                          */
/************************************************************************/

/* Signal multi-completion routing.
 * Using this, you can connect a single completion function onto multiple
 * signals, where the completion function itself is then invoked whenever
 * any of the  signal are  triggered. Note however,  that the  completion
 * callback must still  behave just like  a regular `sigcomp_cb_t',  with
 * the  only addition being that it can extract the completion controller
 * via `sigmulticomp_fromcon(self)' during  phase #1. Also  note that  as
 * far as re-priming goes, the completion function has to decide this  on
 * a per-signal basis, and as far as synchronization goes, the completion
 * function itself may be  invoked simultaneously for different  signals,
 * though is guarantied to not be invoked again for the same signal until
 * the previous call has finished.
 *
 * A multi-completion controller can be disconnected from all attached
 * signals  by using `sigmulticomp_disconnectall()', which is the same
 * as going through all connections one-by-one and disconnecting  them
 * via `sigcompcon_disconnect()'. */
struct sigmulticomp;
struct _sigmulticompcon
#if defined(__cplusplus) && !defined(__WANT_SIGCOMPCON_INIT)
    : sigcompcon /* The underlying completion function */
#define __sigmulticompcon_com_  /* nothing */
#define __sigmulticompcon_ascom /* nothing */
#endif /* __cplusplus && !defined(__WANT_SIGCOMPCON_INIT) */
{
#if !defined(__cplusplus) || defined(__WANT_SIGCOMPCON_INIT)
	struct sigcompcon    mr_com; /* The underlying completion function */
#define __sigmulticompcon_com_     mr_com.
#define __sigmulticompcon_ascom(x) (&(x)->mr_com)
#endif /* !__cplusplus || __WANT_SIGCOMPCON_INIT */
	struct sigmulticomp *mr_multcon; /* [1..1][const] The attached controller. */
};
#define _sigmulticompcon_init(self, multcon, cb)               \
	(void)(sigcompcon_init(__sigmulticompcon_ascom(self), cb), \
	       (self)->mr_multcon = (multcon))

/* Given  a  given  `struct sigcompcon *sc', as  passed  to a
 * `sigcomp_cb_t()', return  the associated  multi-completion
 * controller.  The  caller  must  ensure  that  `sc'  is   a
 * completion controller owned by some `struct sigmulticomp',
 * which can easily  be done by  only invoking this  function
 * from callbacks registered by
 *   - `sigmulticomp_connect()' or
 *   - `sigmulticomp_connect_from_task()' */
#define sigmulticomp_fromcon(sc) \
	(((struct _sigmulticompcon *)(sc))->mr_multcon)



struct _sigmulticomp_xtra {
	struct _sigmulticomp_xtra                       *smcx_next;  /* [0..1][owned] More connections. */
	size_t                                           smcx_used;  /* [<= smcx_alloc] # of used, leading items of `smcx_cons' */
	size_t                                           smcx_alloc; /* [!0] # of allocated items in `smcx_cons' */
	COMPILER_FLEXIBLE_ARRAY(struct _sigmulticompcon, smcx_cons); /* [0..smcx_used|ALLOC(smcx_alloc)] Extra connections */
};

struct sigmulticomp {
	/* NOTE: This structure (and its API) is specifically designed such that individual
	 *       source files can simply override  `CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS'
	 *       with custom values and have those work out-of-the-box. */
	struct _sigmulticomp_xtra *smc_xtra; /* [0..1] Extra connections */
#if CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS > 0
	struct _sigmulticompcon    smc_cons[CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS]; /* Pre-allocated connections (unused is indicated by `!__sigmulticompcon_smc_cons_inuse()') */
#elif CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 0
	COMPILER_FLEXIBLE_ARRAY(struct _sigmulticompcon, smc_cons); /* Pre-allocated connections (unused is indicated by `!__sigmulticompcon_smc_cons_inuse()') */
#endif /* ... */
};

/* Check if a given `struct _sigmulticompcon *con' from
 * `struct sigmulticomp::smc_cons' is currently in-use. */
#define __sigmulticompcon_smc_cons_inuse(con) \
	((con)->__sigmulticompcon_com_ _sigcompcon_con_ sc_sig != __NULLPTR)
/* Mark `con' as unused following is being disconnected. */
#define __sigmulticompcon_smc_cons_setunused(con) \
	(void)((con)->__sigmulticompcon_com_ _sigcompcon_con_ sc_sig = __NULLPTR)

/* Initialize the given signal multi-completion controller. */
#define _sigmulticomp_init0(self)  (void)((self)->smc_xtra = __NULLPTR)
#define _sigmulticomp_cinit0(self) __hybrid_assert((self)->smc_xtra == __NULLPTR)
#if CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS <= 0
#define sigmulticomp_init(self)  _sigmulticomp_init0(self)
#define sigmulticomp_cinit(self) _sigmulticomp_cinit0(self)
#elif CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1
#define sigmulticomp_init(self)  (void)(_sigmulticomp_init0(self), (self)->smc_cons[0].__sigmulticompcon_com_ _sigcompcon_con_ sc_sig = __NULLPTR)
#define sigmulticomp_cinit(self) (_sigmulticomp_cinit0(self), __hybrid_assert((self)->smc_cons[0].__sigmulticompcon_com_ _sigcompcon_con_ sc_sig = __NULLPTR))
#else /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS >= 2 */
#define sigmulticomp_init(self)  sigmulticomp_init(self)
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigmulticomp_init)(struct sigmulticomp *__restrict self) {
	unsigned int i;
	_sigmulticomp_init0(self);
	for (i = 0; i < CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS; ++i)
		self->smc_cons[i].__sigmulticompcon_com_ _sigcompcon_con_ sc_sig = __NULLPTR;
}
#ifdef NDEBUG
#define sigmulticomp_cinit(self) (void)0
#else /* NDEBUG */
#define sigmulticomp_cinit(self) sigmulticomp_cinit(self)
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigmulticomp_cinit)(struct sigmulticomp *__restrict self) {
	unsigned int i;
	_sigmulticomp_cinit0(self);
	for (i = 0; i < CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS; ++i)
		__hybrid_assert(self->smc_cons[i].mr_multcon == __NULLPTR);
}
#endif /* !NDEBUG */
#endif /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS >= 2 */


/* Finalize a given signal multi-completion controller.
 * WARNING: This  function will _not_  disconnect any remaining signals.
 *          If active connections could possibly remain, it is up to the
 *          caller to call `sigmulticomp_disconnectall()' first! */
#if defined(NDEBUG) || defined(__INTELLISENSE__)
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigmulticomp_fini)(struct sigmulticomp *__restrict self);
#else /* NDEBUG || __INTELLISENSE__ */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL __sigmulticomp_fini)(struct sigmulticomp *__restrict self)
		ASMNAME("sigmulticomp_fini");
#define sigmulticomp_fini(self)                        \
	(__hybrid_assert(!sigmulticomp_isconnected(self)), \
	 __sigmulticomp_fini(self))
#endif /* !NDEBUG && !__INTELLISENSE__ */


/* Serve all (still-alive) connections that are active for `self'. Note that this  function
 * may not be called from inside of signal-completion-callbacks, or any other callback that
 * may  be executed in the context of holding an SMP-lock. (though you area allowed to call
 * this function from a `sigcomp_postcb_t' callback) */
#if CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigmulticomp_disconnectall)(struct sigmulticomp *__restrict self)
		ASMNAME("_sigmulticomp_disconnectall1");
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL sigmulticomp_disconnectall_nopr)(struct sigmulticomp *__restrict self)
		ASMNAME("_sigmulticomp_disconnectall_nopr1");
#else /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1 */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _sigmulticomp_disconnectallN)(struct sigmulticomp *__restrict self, size_t n_static);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void NOTHROW(FCALL _sigmulticomp_disconnectall_noprN)(struct sigmulticomp *__restrict self, size_t n_static);
#define sigmulticomp_disconnectall(self)      _sigmulticomp_disconnectallN(self, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#define sigmulticomp_disconnectall_nopr(self) _sigmulticomp_disconnectall_noprN(self, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#endif /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS != 1 */


/* Check if the given signal multi-completion controller `self'
 * is connected to  any signal  (iow: if there  are any  in-use
 * connections present). */
#if CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL sigmulticomp_isconnected)(struct sigmulticomp const *__restrict self)
		ASMNAME("_sigmulticomp_isconnected1");
#else /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1 */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL _sigmulticomp_isconnectedM)(struct sigmulticomp const *__restrict self, size_t n_static);
#define sigmulticomp_isconnected(self) _sigmulticomp_isconnectedM(self, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#endif /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS != 1 */



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
#if CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct sigcompcon *FCALL
sigmulticomp_alloccon(struct sigmulticomp *__restrict self, sigcomp_cb_t cb)
		THROWS(E_BADALLOC)
		ASMNAME("_sigmulticomp_alloccon1");
FUNDEF WUNUSED NONNULL((1, 2)) struct sigcompcon *
NOTHROW(FCALL sigmulticomp_alloccon_nx)(struct sigmulticomp *__restrict self,
                                        sigcomp_cb_t cb)
		ASMNAME("_sigmulticomp_alloccon_nx1");
#else /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1 */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct sigcompcon *FCALL
_sigmulticomp_allocconN(struct sigmulticomp *__restrict self,
                        sigcomp_cb_t cb, size_t n_static)
		THROWS(E_BADALLOC);
FUNDEF WUNUSED NONNULL((1, 2)) struct sigcompcon *
NOTHROW(FCALL _sigmulticomp_alloccon_nxN)(struct sigmulticomp *__restrict self,
                                       sigcomp_cb_t cb, size_t n_static);
#define sigmulticomp_alloccon(self, cb)    _sigmulticomp_allocconN(self, cb, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#define sigmulticomp_alloccon_nx(self, cb) _sigmulticomp_alloccon_nxN(self, cb, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#endif /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS != 1 */


/* Combination of `sigmulticomp_alloccon()' + `sigcompcon_connect()' */
#define sigmulticomp_connect(self, target, cb)             sigmulticomp_connect_ex(self, target, cb, SIGCOMPCON_CONNECT_F_NORMAL)
#define sigmulticomp_connect_for_poll(self, target, cb)    sigmulticomp_connect_ex(self, target, cb, SIGCOMPCON_CONNECT_F_POLL)
#define sigmulticomp_connect_nx(self, target, cb)          sigmulticomp_connect_ex_nx(self, target, cb, SIGCOMPCON_CONNECT_F_NORMAL)
#define sigmulticomp_connect_for_poll_nx(self, target, cb) sigmulticomp_connect_ex_nx(self, target, cb, SIGCOMPCON_CONNECT_F_POLL)
#if CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1
__COMPILER_EIREDIRECT(NOBLOCK NONNULL((1, 2, 3)),void,,FCALL,
sigmulticomp_connect_ex,(struct sigmulticomp *__restrict self,
                         struct sig *__restrict target, sigcomp_cb_t cb,
                         uintptr_t flags), _sigmulticomp_connect_ex1, THROWS(E_BADALLOC) {
	struct sigcompcon *con = sigmulticomp_alloccon(self, cb);
	sigcompcon_connect_ex(con, target, flags);
});
__COMPILER_EIREDIRECT(NOBLOCK WUNUSED NONNULL((1, 2, 3)),__BOOL,NOTHROW,FCALL,
sigmulticomp_connect_ex_nx,(struct sigmulticomp *__restrict self,
                            struct sig *__restrict target, sigcomp_cb_t cb,
                            uintptr_t flags), _sigmulticomp_connect_ex_nx1, {
	struct sigcompcon *con = sigmulticomp_alloccon_nx(self, cb);
	if unlikely(!con)
		return 0;
	sigcompcon_connect_ex(con, target, flags);
	return 1;
});
#else /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1 */
__COMPILER_EIDECLARE(NOBLOCK NONNULL((1, 2, 3)),void,,FCALL,
_sigmulticomp_connect_exN,(struct sigmulticomp *__restrict self,
                           struct sig *__restrict target, sigcomp_cb_t cb,
                           uintptr_t flags, size_t n_static), THROWS(E_BADALLOC) {
	struct sigcompcon *con = _sigmulticomp_allocconN(self, cb, n_static);
	sigcompcon_connect_ex(con, target, flags);
});
__COMPILER_EIDECLARE(NOBLOCK WUNUSED NONNULL((1, 2, 3)),__BOOL,NOTHROW,FCALL,
_sigmulticomp_connect_ex_nxN,(struct sigmulticomp *__restrict self,
                              struct sig *__restrict target, sigcomp_cb_t cb,
                              uintptr_t flags, size_t n_static), {
	struct sigcompcon *con = _sigmulticomp_alloccon_nxN(self, cb, n_static);
	if unlikely(!con)
		return 0;
	sigcompcon_connect_ex(con, target, flags);
	return 1;
});
#define sigmulticomp_connect_ex(self, target, cb, flags) \
	_sigmulticomp_connect_exN(self, target, cb, flags, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#define sigmulticomp_connect_ex_nx(self, target, cb, flags) \
	_sigmulticomp_connect_ex_nxN(self, target, cb, flags, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#endif /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS != 1 */


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
#if CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1
FUNDEF NOBLOCK NONNULL((1)) void FCALL
sigmulticomp_connect_from_task(struct sigmulticomp *__restrict self,
                               sigcomp_cb_t cb,
                               uintptr_t flags_mask,
                               uintptr_t flags_set)
		THROWS(E_BADALLOC)
		ASMNAME("_sigmulticomp_connect_from_task1");
#else /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS == 1 */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
_sigmulticomp_connect_from_taskN(struct sigmulticomp *__restrict self,
                                 sigcomp_cb_t cb,
                                 uintptr_t flags_mask,
                                 uintptr_t flags_set,
                                 size_t n_static)
		THROWS(E_BADALLOC);
#define sigmulticomp_connect_from_task(self, cb, flags_mask, flags_set) \
	_sigmulticomp_connect_from_taskN(self, cb, flags_mask, flags_set, CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS)
#endif /* CONFIG_SIGMULTICOMP_STATIC_CONNECTIONS != 1 */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGCOMP_H */
