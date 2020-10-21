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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_EPOLL_H
#define GUARD_KERNEL_INCLUDE_SCHED_EPOLL_H 1

#include <kernel/compiler.h>

#include <kernel/handle.h>
#include <kernel/types.h>
#include <sched/rwlock.h>
#include <sched/signal-completion.h>
#include <sched/signal.h>

#include <sys/epoll.h>

#ifdef __CC__
#ifdef CONFIG_USE_NEW_SIGNAL_API
DECL_BEGIN

struct epoll_controller;
struct epoll_handle_monitor {
	struct epoll_controller     *ehm_ctrl;   /* [1..1][const] The primary epoll controller (exists once
	                                          * for every epoll-fd that is created by user-space, whereas
	                                          * this `struct epoll_handle_monitor' exists once for every
	                                          * monitored file descriptor, aka. handle) */
	struct handle                ehm_hand;   /* [1..1][const] The handle that is being monitored. */
	struct sig_multicompletion   ehm_comp;   /* Completion controller attached to pollable signals of `ehm_hand'
	                                          * Signals monitored by this controller are established by doing a
	                                          * regular `handle_poll()' on `ehm_hand', followed by making use of
	                                          * `sig_multicompletion_connect_from_task()'. */
	struct epoll_event           ehm_info;   /* [lock(ehm_ctrl->ec_lock)] Currently-set epoll information.
	                                          * This is the set of EPOLL* conditions to wait for, as well as
	                                          * the user-data-field that is handed back to user-space when the
	                                          * condition is met. */
	struct epoll_handle_monitor *ehm_rnext;  /* [0..1] Next monitor that has been raised. */
	WEAK bool                    ehm_raised; /* [lock(ATOMIC)] set to `true' once the monitored condition is met.
	                                          * When this happens, the monitor is added to the chain of raised
	                                          * monitors, and `ehm_ctrl->ec_avail' will be send (using `sig_send()',
	                                          * thus waking up whatever a thread waiting in `epoll_wait(2)')
	                                          * Note that `ehm_comp' doesn't (and can't) use `sig_completion_reprime()',
	                                          * since the effective set of signals to which one must listen when polling
	                                          * `ehm_hand' may depend on some internal state, and may change over time.
	                                          * As such, the consumer of epoll events is responsible for resetting
	                                          * the set of signals monitored by `ehm_comp' every time that signal is
	                                          * broadcast. */
};

struct epoll_controller {
	WEAK refcnt_t                     ec_refcnt; /* Reference counter. */
	struct rwlock                     ec_lock;   /* Lock for this epoll controller. This one has to be held whenever
	                                              * making modifications to, or scanning the set of monitored file
	                                              * descriptors. Additionally, `epoll_wait(2)' will temporarily acquire
	                                              * a read-lock to this rwlock while searching for handle monitors that
	                                              * may have been raised in the mean time. */
	WEAK struct epoll_handle_monitor *ec_raised; /* [0..1][lock(ATOMIC)] Singly linked list of
	                                              * raised monitors (chained via `ehm_rnext'). */
	struct sig                        ec_avail;  /* Send once every time that `ec_raised' becomes non-NULL. */
	/* TODO: (some kind of) list of all defined monitors. */
};



/* NOTE: Completion functions for `epoll_handle_monitor' do this:
 * >> PHASE_1() {
 * >>     struct epoll_handle_monitor *me;
 * >>     me = container_of(sig_multicompletion_controller(self),
 * >>                       struct epoll_handle_monitor, ehm_comp);
 * >>     // TODO: sig_multicompletion_trydisconnect(&me->ehm_comp);
 * >>     //       Tries to disconnect the controller from as many
 * >>     //       signals as possible, but simply skips+ignores
 * >>     //       signals for which it cannot acquire the SMP-lock.
 * >>     // >> As far as semantics go, this is completely unnecessary,
 * >>     //    but doing this may still be able to still improve
 * >>     //    performace, since none of the other signals which
 * >>     //    we may be connected to at the moment won't cause
 * >>     //    us to be invoked as often.
 * >>     bool did_raise = ATOMIC_XCH(me->ehm_raised, true);
 * >>     if likely(did_raise) {
 * >>         ATOMIC_SLIST_INSERT(me, me->ehm_ctrl->ec_raised);
 * >>         PHASE_2.args[0] = incref(me->ehm_ctrl);
 * >>     }
 * >> }
 * >> PHASE_2(struct epoll_controller *self) {
 * >>     sig_send(&self->ec_avail);
 * >>     decref_unlikely(self);
 * >> }
 *
 * NOTE: Inside of `epoll_wait(2)', code will check the list of raised
 *       monitors and check if they are still ready then. This check can
 *       be skipped by employing `EPOLLET', meaning that past rising edge
 *       events can still be detected by looking at 
 */


/* TODO */


DECL_END
#endif /* CONFIG_USE_NEW_SIGNAL_API */
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_EPOLL_H */
