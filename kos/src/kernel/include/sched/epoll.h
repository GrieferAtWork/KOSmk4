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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_EPOLL_H
#define GUARD_KERNEL_INCLUDE_SCHED_EPOLL_H 1

#include <kernel/compiler.h>

#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <sched/sig.h>
#include <sched/sigcomp.h>

#include <kos/sched/shared-lock.h>
#include <sys/epoll.h>


/*[[[config CONFIG_HAVE_KERNEL_EPOLL_RPC = true
 * Kernel feature: EPOLL monitors can be used to send RPCs.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_EPOLL_RPC
#undef CONFIG_HAVE_KERNEL_EPOLL_RPC
#elif !defined(CONFIG_HAVE_KERNEL_EPOLL_RPC)
#define CONFIG_HAVE_KERNEL_EPOLL_RPC
#elif (-CONFIG_HAVE_KERNEL_EPOLL_RPC - 1) == -1
#undef CONFIG_HAVE_KERNEL_EPOLL_RPC
#define CONFIG_NO_KERNEL_EPOLL_RPC
#endif /* ... */
/*[[[end]]]*/

#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
#include <sched/rpc-internal.h> /* struct pending_rpc */
#include <kos/lockop.h>
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */

#ifdef __CC__
DECL_BEGIN


/*[[[config CONFIG_KERNEL_EPOLL_MAX_NESTING! = 4
 * NOTE: Linux also uses `4' for this
 * ]]]*/
#ifndef CONFIG_KERNEL_EPOLL_MAX_NESTING
#define CONFIG_KERNEL_EPOLL_MAX_NESTING 4
#endif /* !CONFIG_KERNEL_EPOLL_MAX_NESTING */
/*[[[end]]]*/

struct epoll_controller;

#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
struct taskpid;
struct epoll_monitor_rpc {
	union {
		struct pending_rpc emr_rpc;    /* The actual RPC */
#if OFFSET_PENDING_RPC_LINK == 0
		REF struct taskpid *emr_target; /* [1..1][const] RPC target thread/process.
		                                 * What specifically this is depends on `emr_rpc.pr_flags & RPC_DOMAIN_F_PROC' */
#else /* OFFSET_PENDING_RPC_LINK == 0 */
		struct {
			__byte_t _emr_pad[OFFSET_PENDING_RPC_LINK];
			REF struct taskpid *emr_target; /* ... */
		};
#endif /* OFFSET_PENDING_RPC_LINK != 0 */
	};
};
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */

struct epoll_handle_monitor {
#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
	union {
		struct {
			struct epoll_controller     *ehm_ctrl;  /* [1..1][const][valid_if(!epoll_handle_monitor_isrpc || ehm_rpc != NULL)]
			                                         * The  primary epoll controller  (exists once for  every epoll-fd that is
			                                         * created  by  user-space,  whereas  this   `struct epoll_handle_monitor'
			                                         * exists once for every monitored file descriptor, aka. handle) */
			struct epoll_handle_monitor *ehm_rnext; /* [0..1][valid_if(!epoll_handle_monitor_isrpc)]
			                                         * Next   monitor   that   has   been    raised. */
		};
		Tobpostlockop(epoll_controller) _ehm_plop;  /* Used internally... */
		Toblockop(epoll_controller)     _ehm_lop;   /* Used internally... */
	};
#else /* CONFIG_HAVE_KERNEL_EPOLL_RPC */
	struct epoll_controller     *ehm_ctrl;  /* [1..1][const][valid_if(!epoll_handle_monitor_isrpc || ehm_rpc != NULL)]
	                                         * The  primary epoll controller  (exists once for  every epoll-fd that is
	                                         * created  by  user-space,  whereas  this   `struct epoll_handle_monitor'
	                                         * exists once for every monitored file descriptor, aka. handle) */
	struct epoll_handle_monitor *ehm_rnext; /* [0..1][valid_if(!epoll_handle_monitor_isrpc)]
	                                         * Next   monitor   that   has   been    raised. */
#endif /* !CONFIG_HAVE_KERNEL_EPOLL_RPC */
	uintptr_half_t               ehm_raised;  /* [lock(ATOMIC)][valid_if(!epoll_handle_monitor_isrpc)]
	                                           * Incremented  once the monitored  condition is met.  When this happens, the
	                                           * monitor is added to the chain of raised monitors, and `ehm_ctrl->ec_avail'
	                                           * will  be send (using `sig_send()', thus waking up whichever thread waiting
	                                           * in  `epoll_wait(2)').  Note  that  `ehm_comp'  doesn't  (and  can't)   use
	                                           * `sig_completion_reprime()', since the  effective set of  signals to  which
	                                           * one  must  listen when  polling `ehm_hand*'  may  depend on  some internal
	                                           * state,  and may change over time. As such, the consumer of epoll events is
	                                           * responsible for resetting the set of signals monitored by `ehm_comp' every
	                                           * time that signal is broadcast. */
	uintptr_half_t               ehm_handtyp; /* [const] The type of handle being monitored. */
	WEAK REF void               *ehm_handptr; /* [const][1..1] Handle type pointer. (always valid in the context of `ehm_handtyp') */
	uint32_t                     ehm_fdkey;   /* [const] FD-key used to differentiate monitors for the same file. */
	uint32_t                     ehm_events;  /* [lock(ehm_ctrl->ec_lock)] Epoll events (Set of `EPOLL*'; s.a. `EPOLL_EVENTS') */
#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
	union {
		union epoll_data          ehm_data;   /* [lock(ehm_ctrl->ec_lock)][valid_if(!epoll_handle_monitor_isrpc)] Epoll user data. */
		struct epoll_monitor_rpc *ehm_rpc;    /* [0..1][owned][lock(CLEAR_ONCE(ATOMIC))][valid_if(epoll_handle_monitor_isrpc)] RPC send on rising edge. */
	};
#else /* CONFIG_HAVE_KERNEL_EPOLL_RPC */
	union epoll_data             ehm_data;    /* [lock(ehm_ctrl->ec_lock)] Epoll user data. */
#endif /* !CONFIG_HAVE_KERNEL_EPOLL_RPC */
	struct sigmulticomp          ehm_comp;    /* Completion controller attached to pollable signals of `ehm_hand*'
	                                           * Signals monitored by this controller  are established by doing  a
	                                           * regular `handle_poll()' on `ehm_hand*', followed by making use of
	                                           * `sigmulticomp_connect_from_task()'. */
};

/* Get/set  the mask of raised, pollable data channels. The field accessed
 * by these macros is only valid for monitors from the `ec_pending' chain. */
#define epoll_handle_monitor_getwtest(self) \
	((uint32_t)(uintptr_t)(self)->ehm_comp.smc_cons[0].sc_next)
#define epoll_handle_monitor_setwtest(self, value) \
	(void)((self)->ehm_comp.smc_cons[0].sc_next = (struct sigcon *)(uintptr_t)(uint32_t)(value))

/* Check if a given monitor is an RPC event (as opposed to a pollable event) */
#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
#define epoll_handle_monitor_isrpc(self) ((self)->ehm_raised == (uintptr_half_t)-1)
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */


struct epoll_controller_ent {
	struct epoll_handle_monitor *ece_mon; /* [0..1][owned] Pointed-to monitor (NULL for sentinel, INTERNAL_STUB for deleted) */
};

struct epoll_controller {
	/* NOTE: `struct epoll_controller' needs weak  reference counting support  because
	 *       it can be used to reference other, arbitrary handle objects. As such,  it
	 *       would be possible to form a reference loop using the epoll controller and
	 *       some other handle that can reference other handles (such as encapsulating
	 *       an  epoll controller within a unix-domain socket datagram, when the epoll
	 *       controller  is already monitoring some socket also holding a reference to
	 *       the send-queue) */
	WEAK refcnt_t                     ec_refcnt;     /* Reference counter. */
	WEAK refcnt_t                     ec_weakrefcnt; /* Weak reference counter. */
	/* TODO: Don't use a shared_lock here; change this to use `atomic_lock' instead! */
	struct shared_lock                ec_lock;       /* Lock  for this epoll  controller. This one has  to be held whenever
	                                                  * making modifications  to, or  scanning the  set of  monitored  file
	                                                  * descriptors. Additionally, `epoll_wait(2)' will temporarily acquire
	                                                  * a this lock while searching for handle monitors that may have  been
	                                                  * raised in the mean time. */
#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
	Toblockop_slist(epoll_controller) ec_lops;       /* Lock operations. */
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */
	WEAK struct epoll_handle_monitor *ec_raised;     /* [0..1][lock(APPEND(ATOMIC), CLEAR(ec_lock))]
	                                                  * Singly linked list  of raised monitors  (chained via  `ehm_rnext').
	                                                  * By taking an element from this chain, you implicitly acquire a lock
	                                                  * to its `ehm_comp', `ehm_rnext'  and `ehm_raised' fields, which  you
	                                                  * release by re-connecting its completion controller. */
	WEAK struct epoll_handle_monitor *ec_pending;    /* [0..1][lock(ec_lock)] Similar  to  `ec_raised',  but  this  chain
	                                                  * contains  all monitors  that have  been raised,  and confirmed to
	                                                  * be  asserted, but have  yet to consumed  by user-space. The chain
	                                                  * is sorted from least-recently-raised to most-recently-raised, and
	                                                  * the `ehm_wtest' field */
	struct sig                        ec_avail;      /* Send once every time that `ec_raised' becomes non-NULL. */
	size_t                            ec_used;       /* [lock(ec_lock)] Amount of used (non-NULL and non-deleted) entries */
	size_t                            ec_size;       /* [lock(ec_lock)] Amount of (non-NULL) entries. */
	size_t                            ec_mask;       /* [lock(ec_lock)] Hash-mask for `pn_list' */
	struct epoll_controller_ent      *ec_list;       /* [1..sc_mask+1][owned][lock(ec_lock)] Hash-vector of monitors.
	                                                  * For  hashing,  the  `h_data'  pointer  of  handles  is  used. */
};

#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _epoll_controller_lock_reap)(struct epoll_controller *__restrict self);
#define epoll_controller_lock_reap(self)    (void)(!oblockop_mustreap(&(self)->ec_lops) || (_epoll_controller_lock_reap(self), 0))
#define epoll_controller_lock_release(self) (shared_lock_release(&(self)->ec_lock), epoll_controller_lock_reap(self))
#else /* CONFIG_HAVE_KERNEL_EPOLL_RPC */
#define epoll_controller_lock_release(self) shared_lock_release(&(self)->ec_lock)
#endif /* !CONFIG_HAVE_KERNEL_EPOLL_RPC */
#define _epoll_controller_lock_release(self)   shared_lock_release(&(self)->ec_lock)
#define epoll_controller_lock_tryacquire(self) shared_lock_tryacquire(&(self)->ec_lock)
#define epoll_controller_lock_acquire(self)    shared_lock_acquire(&(self)->ec_lock)
#define epoll_controller_lock_acquire_nx(self) shared_lock_acquire_nx(&(self)->ec_lock)
#define epoll_controller_lock_acquired(self)   shared_lock_acquired(&(self)->ec_lock)


/* Hash-vector iteration helper macros */
#define epoll_controller_hashof_ex(handptr, fd_key) \
	((uintptr_t)(handptr) ^ (uintptr_t)(fd_key))
#define epoll_controller_hashof(monitor) \
	epoll_controller_hashof_ex((monitor)->ehm_handptr, (monitor)->ehm_fdkey)
#define epoll_controller_hashnx(i, perturb) \
	((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)

/* Destroy the given epoll controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL epoll_controller_destroy)(struct epoll_controller *__restrict self);
DEFINE_WEAKREFCNT_FUNCTIONS(struct epoll_controller, ec_weakrefcnt, kfree)
DEFINE_REFCNT_FUNCTIONS(struct epoll_controller, ec_refcnt, epoll_controller_destroy)

/* Create  a new epoll  controller and return  a reference to it.
 * This function is used by the `epoll_create(2)' syscall family. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct epoll_controller *KCALL
epoll_controller_create(void) THROWS(E_BADALLOC);

/* Add a monitor for `hand:fd_key' to the given epoll controller.
 * @throw: E_ILLEGAL_REFERENCE_LOOP: `hand' is another epoll controller that is either the same
 *                                   as `self', or is already monitoring `self'. Also thrown if
 *                                   the max depth of nested epoll controllers would exceed the
 *                                   compile-time `CONFIG_KERNEL_EPOLL_MAX_NESTING' limit.
 * @return: true:  Success
 * @return: false: Another monitor for `hand:fd_key' already exists. */
FUNDEF NONNULL((1, 2)) bool KCALL
epoll_controller_addmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key,
                            NCX struct epoll_event const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT,
		       E_ILLEGAL_REFERENCE_LOOP);

#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
/* Add a monitor for `hand' to the given epoll controller. When a raising edge
 * for the monitored conditions is detected (or if the conditions are  already
 * met at the time of the this function being called), trigger delivery of the
 * given RPC before automatically removing  the associated epoll monitor  from
 * `self'.  When the thread/process  targeted by said  RPC has already exited,
 * the RPC is silently discarded.
 * @param: rpc: The  RPC that should  be delivered upon  a raising-edge event being
 *              triggered.  Note that  this RPC  is _always_  inherited, and should
 *              some kind of exception be triggered during creation of the monitor,
 *              or should this function return `false'
 * @throw: E_ILLEGAL_REFERENCE_LOOP: `hand' is another epoll controller that is either the same
 *                                   as `self', or is already monitoring `self'. Also thrown if
 *                                   the max depth of nested epoll controllers would exceed the
 *                                   compile-time `CONFIG_KERNEL_EPOLL_MAX_NESTING' limit.
 * @return: true:  Success
 * @return: false: Another monitor for `hand:fd_key' already exists. */
FUNDEF NONNULL((1, 2, 5)) bool KCALL
epoll_controller_addmonitor_rpc(struct epoll_controller *__restrict self,
                                struct handle const *__restrict hand,
                                uint32_t fd_key, uint32_t events,
                                /*inherit(always)*/ struct epoll_monitor_rpc *__restrict rpc)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_ILLEGAL_REFERENCE_LOOP);
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */


/* Modify the monitor for `hand:fd_key' within the given epoll controller.
 * @return: true:  Success
 * @return: false: The given `hand:fd_key' isn't being monitored by `self'. */
FUNDEF NONNULL((1, 2)) bool KCALL
epoll_controller_modmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key,
                            NCX struct epoll_event const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT);

/* Delete the monitor for `hand:fd_key' within the given epoll controller.
 * When the monitor is attached to an  RPC, that RPC will be canceled  and
 * this function only returns `true' if it managed to prevent the RPC from
 * being delivered. If the RPC was already send, this function will return
 * `false', acting as though the  associated monitor was already  deleted,
 * even if was still dangling due to race conditions.
 * @return: true:  Success
 * @return: false: The given `hand:fd_key' isn't being monitored by `self'. */
FUNDEF NONNULL((1, 2)) bool KCALL
epoll_controller_delmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key)
		THROWS(E_WOULDBLOCK);


/* Try  to consume  pending events  from `self'.  Note that this
 * function  can throw  E_BADALLOC because  in the  event that a
 * monitor has to  be re-primed,  there is a  chance that  doing
 * so might  require more  signal connection  descriptors to  be
 * allocated, which in turn might cause that allocation to fail.
 * When this happens, all already-consumed events will be marked
 * as raised once again, and be  back onto the queue of  pending
 * events. The same thing also happens when writing to  `events'
 * would result in a SEGFAULT.
 * NOTE: The caller must ensure that !task_isconnected()
 * @param: maxevents: The max number of events to consume (asserted to be >= 1)
 * @return: * : The actual number of consumed events.
 * @return: 0 : No monitors have  been raised at  this time. Once  any
 *              monitor becomes raised, `self->ec_avail' will be send. */
FUNDEF NONNULL((1)) size_t KCALL
epoll_controller_trywait(struct epoll_controller *__restrict self,
                         NCX struct epoll_event *events,
                         size_t maxevents)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT);

/* Same  as  `epoll_controller_trywait()',   but  blocking  wait   until
 * at  least  1 event  could be  consumed.  If `abs_timeout'  is finite,
 * and expires  while  waiting  for  the first  event  to  appear,  then
 * this function will return `0' (note that if `abs_timeout' was already
 * expired from  the get-go,  this function  will still  try to  consume
 * already-pending  events,  thus  behaving  identical  to  a  call   to
 * `epoll_controller_trywait()') */
FUNDEF BLOCKING NONNULL((1)) size_t KCALL
epoll_controller_wait(struct epoll_controller *__restrict self,
                      NCX struct epoll_event *events,
                      size_t maxevents,
                      ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT);

#ifndef __sigset_t_defined
#define __sigset_t_defined
struct __sigset_struct;
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

FUNDEF NONNULL((1, 4)) size_t KCALL
epoll_controller_wait_with_sigmask(struct epoll_controller *__restrict self,
                                   NCX struct epoll_event *events,
                                   size_t maxevents,
                                   sigset_t const *__restrict sigmask,
                                   ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT);


/* Quickly check if there are pending events that can be waited upon. */
#define epoll_controller_canwait(self)                                          \
	(__hybrid_atomic_load(&(self)->ec_raised, __ATOMIC_ACQUIRE) != __NULLPTR || \
	 __hybrid_atomic_load(&(self)->ec_pending, __ATOMIC_ACQUIRE) != __NULLPTR)
#define epoll_controller_pollconnect_ex(self, cb) cb(&(self)->ec_avail)
#define epoll_controller_pollconnect(self)        epoll_controller_pollconnect_ex(self, task_connect_for_poll)

#define epoll_controller_poll_unlikely(self) \
	(epoll_controller_pollconnect(self),     \
	 epoll_controller_canwait(self))
#ifdef __OPTIMIZE_SIZE__
#define epoll_controller_poll(self) \
	epoll_controller_poll_unlikely(self)
#else /* __OPTIMIZE_SIZE__ */
#define epoll_controller_poll(self)       \
	(epoll_controller_canwait(self) ||    \
	 (epoll_controller_pollconnect(self), \
	  epoll_controller_canwait(self)))
#endif /* !__OPTIMIZE_SIZE__ */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_EPOLL_H */
