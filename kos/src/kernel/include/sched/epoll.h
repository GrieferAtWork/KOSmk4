/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
#include <sched/mutex.h>
#include <sched/signal-completion.h>
#include <sched/signal.h>

#include <sys/epoll.h>

#ifdef __CC__
DECL_BEGIN


#ifndef CONFIG_EPOLL_MAX_NESTING
#define CONFIG_EPOLL_MAX_NESTING 4 /* NOTE: Linux also uses `4' for this */
#endif /* !CONFIG_EPOLL_MAX_NESTING */

struct epoll_controller;
struct epoll_handle_monitor {
	struct epoll_controller     *ehm_ctrl;    /* [1..1][const] The primary  epoll controller (exists  once
	                                           * for every epoll-fd that is created by user-space, whereas
	                                           * this `struct epoll_handle_monitor' exists once for  every
	                                           * monitored file descriptor, aka. handle) */
	struct epoll_handle_monitor *ehm_rnext;   /* [0..1] Next monitor that has been raised. */
	uintptr_half_t               ehm_raised;  /* [lock(ATOMIC)] Incremented  once   the  monitored   condition  is   met.
	                                           * When this  happens,  the  monitor  is  added  to  the  chain  of  raised
	                                           * monitors,  and  `ehm_ctrl->ec_avail' will  be send  (using `sig_send()',
	                                           * thus  waking   up  whatever   a  thread   waiting  in   `epoll_wait(2)')
	                                           * Note that `ehm_comp' doesn't (and can't) use `sig_completion_reprime()',
	                                           * since the effective set of signals to which one must listen when polling
	                                           * `ehm_hand' may depend on some internal state, and may change over  time.
	                                           * As  such,  the consumer  of epoll  events  is responsible  for resetting
	                                           * the  set of  signals monitored by  `ehm_comp' every time  that signal is
	                                           * broadcast. */
	uintptr_half_t               ehm_handtyp; /* [const] The type of handle being monitored. */
	WEAK REF void               *ehm_handptr; /* [const][1..1] Handle type pointer. (always valid in the context of `ehm_handtyp') */
	uint32_t                     ehm_fdkey;   /* [const] FD-key used to differentiate monitors for the same file. */
	uint32_t                     ehm_events;  /* [lock(ehm_ctrl->ec_lock)] Epoll events (Set of `EPOLL*'; s.a. `EPOLL_EVENTS') */
	union epoll_data             ehm_data;    /* [lock(ehm_ctrl->ec_lock)] Epoll user data. */
	struct sig_multicompletion   ehm_comp;    /* Completion controller attached to pollable signals of `ehm_hand'
	                                           * Signals monitored by this controller are established by doing  a
	                                           * regular `handle_poll()' on `ehm_hand', followed by making use of
	                                           * `sig_multicompletion_connect_from_task()'. */
};

/* Get/set  the mask of raised, pollable data channels. The field accessed
 * by these macros is only valid for monitors from the `ec_pending' chain. */
#define epoll_handle_monitor_getwtest(self) \
	((uint32_t)(uintptr_t)(self)->ehm_comp.sm_set.sms_routes[0].tc_signext)
#define epoll_handle_monitor_setwtest(self, value) \
	((self)->ehm_comp.sm_set.sms_routes[0].tc_signext = (struct task_connection *)(uintptr_t)(uint32_t)(value))


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
	struct mutex                      ec_lock;       /* Lock  for this epoll  controller. This one has  to be held whenever
	                                                  * making modifications  to, or  scanning the  set of  monitored  file
	                                                  * descriptors. Additionally, `epoll_wait(2)' will temporarily acquire
	                                                  * a this lock while searching for handle monitors that may have  been
	                                                  * raised in the mean time. */
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
	size_t                            ec_size;       /* [lock(ec_lock)] Amount of (non-NULL) entires. */
	size_t                            ec_mask;       /* [lock(ec_lock)] Hash-mask for `pn_list' */
	struct epoll_controller_ent      *ec_list;       /* [1..sc_mask+1][owned][lock(ec_lock)] Hash-vector of monitors.
	                                                  * For  hashing,  the  `h_data'  pointer  of  handles  is  used. */
};

/* Hash-vector iteration helper macros */
#define epoll_controller_hashof(monitor) \
	((uintptr_t)(monitor)->ehm_handptr ^ (uintptr_t)(monitor)->ehm_fdkey)
#define epoll_controller_hashof_ex(handptr, fd_key) \
	((uintptr_t)(handptr) ^ (uintptr_t)(fd_key))
#define epoll_controller_hashnx(i, perturb) \
	((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)

/* Destroy the given epoll controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL epoll_controller_destroy)(struct epoll_controller *__restrict self);
DEFINE_WEAKREFCOUNT_FUNCTIONS(struct epoll_controller, ec_weakrefcnt, kfree)
DEFINE_REFCOUNT_FUNCTIONS(struct epoll_controller, ec_refcnt, epoll_controller_destroy)

/* Create  a new epoll  controller and return  a reference to it.
 * This function is used by the `epoll_create(2)' syscall family. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct epoll_controller *KCALL
epoll_controller_create(void) THROWS(E_BADALLOC);

/* Add a monitor for `hand' to the given epoll controller.
 * @throw: E_ILLEGAL_REFERENCE_LOOP: `hand' is another epoll controller that is either the same
 *                                   as `self', or is already monitoring `self'. Also thrown if
 *                                   the max depth of nested epoll controllers would exceed the
 *                                   compile-time `CONFIG_EPOLL_MAX_NESTING' limit.
 * @return: true:  Success
 * @return: false: Another monitor for `hand' already exists. */
FUNDEF NONNULL((1, 2)) bool KCALL
epoll_controller_addmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key,
                            USER CHECKED struct epoll_event const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT,
		       E_ILLEGAL_REFERENCE_LOOP);

/* Modify the monitor for `hand' within the given epoll controller.
 * @return: true:  Success
 * @return: false: The given `hand' isn't being monitored by `self'. */
FUNDEF NONNULL((1, 2)) bool KCALL
epoll_controller_modmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key,
                            USER CHECKED struct epoll_event const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT);

/* Delete the monitor for `hand' within the given epoll controller.
 * @return: true:  Success
 * @return: false: The given `hand' isn't being monitored by `self'. */
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
 * @param: maxevents: The max number of events to consume (asserted to be >= 1)
 * @return: * : The actual number of consumed events.
 * @return: 0 : No monitors have  been raised at  this time. Once  any
 *              monitor becomes raised, `self->ec_avail' will be send. */
FUNDEF NOCONNECT NONNULL((1)) size_t KCALL
epoll_controller_trywait(struct epoll_controller *__restrict self,
                         USER CHECKED struct epoll_event *events,
                         size_t maxevents)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT);

/* Same  as  `epoll_controller_trywait()',   but  blocking  wait   until
 * at  least  1 event  could be  consumed.  If `abs_timeout'  is finite,
 * and expires  while  waiting  for  the first  event  to  appear,  then
 * this function will return `0' (note that if `abs_timeout' was already
 * expired from  the get-go,  this function  will still  try to  consume
 * already-pending  events,  thus  behaving  identical  to  a  call   to
 * `epoll_controller_trywait()') */
FUNDEF NONNULL((1)) size_t KCALL
epoll_controller_wait(struct epoll_controller *__restrict self,
                      USER CHECKED struct epoll_event *events,
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
                                   USER CHECKED struct epoll_event *events,
                                   size_t maxevents,
                                   sigset_t const *__restrict sigmask,
                                   ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT);


/* Quickly check if there are pending events that can be waited upon. */
#define epoll_controller_canwait(self)                                         \
	(__hybrid_atomic_load((self)->ec_raised, __ATOMIC_ACQUIRE) != __NULLPTR || \
	 __hybrid_atomic_load((self)->ec_pending, __ATOMIC_ACQUIRE) != __NULLPTR)
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
