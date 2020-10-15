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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_C
#define GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_C 1
#define __SIG_INTERNAL_EXPOSE_CONTROL_WORD 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/selftest.h> /* DEFINE_TEST */
#include <sched/rpc.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#if defined(__i386__) || defined(__x86_64__)
#include <kernel/vm/nopf.h>

#include <asm/intrin.h>
#include <kos/kernel/segment.h>
#endif /* __i386__ || __x86_64__ */

DECL_BEGIN

#ifdef CONFIG_NO_SMP
#define SIG_SMPLOCK_BIT 0x0000
#define SIG_SMPLOCK_TST(ptr)      0
#define SIG_SMPLOCK_CLR(ptr)      ptr
#define SIG_SMPLOCK_SET(ptr)      ptr
#define SIG_SMPLOCK_CPY(to, from) to
#else /* CONFIG_NO_SMP */
#define SIG_SMPLOCK_BIT 0x0001
#define SIG_SMPLOCK_TST(ptr)      ((uintptr_t)(ptr) & SIG_SMPLOCK_BIT)
#define SIG_SMPLOCK_CLR(ptr)      (struct task_connection *)((uintptr_t)(ptr) & ~SIG_SMPLOCK_BIT)
#define SIG_SMPLOCK_SET(ptr)      (struct task_connection *)((uintptr_t)(ptr) | SIG_SMPLOCK_BIT)
#define SIG_SMPLOCK_CPY(to, from) (struct task_connection *)((uintptr_t)(to) | ((uintptr_t)(from) & SIG_SMPLOCK_BIT))
#endif /* !CONFIG_NO_SMP */


/* Acquire/release the SMP lock for a given signal,
 * alongside disabling preemption for the duration
 * of holding the lock. */
#if SIG_SMPLOCK_BIT != 0
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _sig_smp_lock_acquire)(struct sig *__restrict self) {
	while ((ATOMIC_FETCHOR(self->s_ctl, SIG_SMPLOCK_BIT) & SIG_SMPLOCK_BIT) != 0)
		task_pause();
}
#define _sig_smp_lock_release(self) \
	ATOMIC_AND((self)->s_ctl, ~SIG_SMPLOCK_BIT)
#else /* SIG_SMPLOCK_BIT != 0 */
#define _sig_smp_lock_acquire(self) (void)0
#define _sig_smp_lock_release(self) (void)0
#endif /* SIG_SMPLOCK_BIT == 0 */

#define sig_smp_lock_acquire_nosmp(self) \
	do {                                 \
		pflag_t _ssl_was = PREEMPTION_PUSHOFF()
#define sig_smp_lock_acquire(self)        \
		sig_smp_lock_acquire_nosmp(self); \
		_sig_smp_lock_acquire(self)
#define sig_smp_lock_release(self)   \
		_sig_smp_lock_release(self); \
		sig_smp_lock_release_nosmp(self)
#define sig_smp_lock_break_nosmp(self) \
		PREEMPTION_POP(_ssl_was)
#define sig_smp_lock_break(self)      \
		(_sig_smp_lock_release(self), \
		 sig_smp_lock_break_nosmp(self))
#define sig_smp_lock_release_nosmp(self) \
		sig_smp_lock_break_nosmp(self);  \
	}	__WHILE0



/* Root connections set. */
PUBLIC ATTR_PERTASK struct task_connections this_root_connections = {
	/* .tsc_prev   = */ NULL,
	/* .tcs_thread = */ NULL, /* Fill in by `pertask_init_task_connections()' */
	/* .tcs_con    = */ NULL,
	/* .tcs_dlvr   = */ NULL,
	/* .tcs_static = */ { }
};

/* [1..1][lock(PRIVATE(THIS_TASK))] Current set of in-use connections.
 * Most of the time, this will simply point to `PERTASK(this_root_connections)' */
PUBLIC ATTR_PERTASK struct task_connections *
this_connections = NULL; /* Fill in by `pertask_init_task_connections()' */

DEFINE_PERTASK_INIT(pertask_init_task_connections);
DEFINE_PERTASK_ONEXIT(task_disconnectall); /* Disconnect all remaining connections during task cleanup. */

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_init_task_connections)(struct task *__restrict self) {
	struct task_connections *rootcons;
	rootcons = &FORTASK(self, this_root_connections);
	rootcons->tcs_thread = self;
	FORTASK(self, this_connections) = rootcons;
}

#if defined(__x86_64__) || defined(__i386__)
INTERN NOBLOCK ATTR_RETNONNULL struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void);
#endif /* __x86_64__ || __i386__ */

/* Push/pop the active set of connections. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushconnections)(struct task_connections *__restrict cons) {
	struct task_connections *oldcons;
	unsigned int i;
#ifdef NDEBUG
	oldcons = THIS_CONNECTIONS;
#elif defined(__i386__) || defined(__x86_64__)
	struct task *mythread;
#ifdef __x86_64__
	mythread = (struct task *)__rdgsbaseq();
#else /* __x86_64__ */
	mythread = NULL;
	if likely(__rdfs() == SEGMENT_KERNEL_FSBASE) {
		struct desctab gdt;
		__sgdt(&gdt);
		if likely(gdt.dt_limit > SEGMENT_KERNEL_FSBASE) {
			struct segment *fsseg;
			fsseg    = (struct segment *)(gdt.dt_base + SEGMENT_KERNEL_FSBASE);
			mythread = (struct task *)segment_rdbaseX(fsseg);
		}
	}
#endif /* !__x86_64__ */
	if unlikely(memcpy_nopf(&oldcons, &FORTASK(mythread, this_connections), sizeof(oldcons)) != 0) {
		assertf(memcpy_nopf(&oldcons, &FORTASK(mythread, this_connections), sizeof(oldcons)) == 0,
		        "Corrupt TLS base pointer: mythread = %p", mythread);
		/* Allow the user to IGNORE the assertion check, in which case we'll
		 * try to repair the damage... */
		mythread = x86_repair_broken_tls_state();
		oldcons  = FORTASK(mythread, this_connections);
	}
#else /* ... */
	oldcons = THIS_CONNECTIONS;
#endif /* !... */
	assertf(cons != oldcons,
	        "Connections set %p has already been pushed",
	        cons);
	cons->tsc_prev = oldcons;
	/* Disable async notifications for the old set of connections,
	 * and use the receiver thread for the new set of connections.
	 * Really, though: This should always just be `THIS_TASK' */
	cons->tcs_thread = ATOMIC_XCH(oldcons->tcs_thread, NULL);
	cons->tcs_con    = NULL; /* No connections in use (yet) */
	cons->tcs_dlvr   = NULL; /* Nothing was delivered (yet) */
#ifndef NDEBUG
	memset(cons->tcs_static, 0xcc, sizeof(cons->tcs_static));
#endif /* !NDEBUG */
	/* Set-up statically allocated connections. */
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i)
		cons->tcs_static[i].tc_sig = NULL; /* Available for use. */
	/* Finally, set the active connection set to `cons' */
	PERTASK_SET(this_connections, cons);
}

PUBLIC NOBLOCK ATTR_RETNONNULL struct task_connections *
NOTHROW(FCALL task_popconnections)(void) {
	struct task_connections *oldcons;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;
	assert((cons->tsc_prev == NULL) == (cons == THIS_ROOT_CONNECTIONS));
	assertf(cons != THIS_ROOT_CONNECTIONS,
	        "Cannot pop connections: Root connection set %p is already active",
	        cons);
	/* Terminate all connections that may still be active for `cons'. */
	task_disconnectall();

	/* Set the TLS pointer for the current set of connection to the old set. */
	oldcons = cons->tsc_prev;
	PERTASK_SET(this_connections, oldcons);

	/* Re-enable asynchronous notifications as the result of `sig_send()' / `sig_broadcast()' */
	ATOMIC_WRITE(oldcons->tcs_thread, THIS_TASK);

	/* Make bad usage consistent by filling memory with garbage. */
#ifndef NDEBUG
	memset(cons, 0xcc, sizeof(*cons));
#endif /* !NDEBUG */

	return cons;
}


/* Allocate a new task connection. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct task_connection *FCALL
task_connection_alloc(struct task_connections *__restrict self) /*THROWS(E_BADALLOC)*/ {
	unsigned int i;
	struct task_connection *result;
	/* Check if one of the static slots is available. */
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i) {
		result = &self->tcs_static[i];
		if (!result->tc_sig)
			goto done;
	}
	/* Must dynamically allocate a new slot. */
	result = (struct task_connection *)kmalloc(sizeof(struct task_connection),
	                                           GFP_LOCKED | GFP_PREFLT);
done:
	return result;
}

/* Freee a given task connection. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_free)(struct task_connections *__restrict self,
                                    struct task_connection *__restrict con) {
	if (con >= self->tcs_static &&
	    con < COMPILER_ENDOF(self->tcs_static)) {
		/* Free a static connection. */
		con->tc_sig = NULL;
	} else {
		/* Free a dynamically allocated connection. */
		kfree(con);
	}
}



/* Connect the calling thread to a given signal.
 * @throw: E_BADALLOC: Insufficient memory (only when there are at least
 *                     `CONFIG_TASK_STATIC_CONNECTIONS' connections already). */
PUBLIC NONNULL((1)) void FCALL
task_connect(struct sig *__restrict target) /*THROWS(E_BADALLOC)*/ {
	struct task_connection *con, *next;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;

	/* When a signal was already delivered, `task_connect()' becomes a no-op */
	if unlikely(ATOMIC_READ(cons->tcs_dlvr) != NULL)
		return;

	/* Allocate a new connection for `cons' */
	con = task_connection_alloc(cons);
	assert(!SIG_SMPLOCK_TST(con));

	/* Fill in the new connection. */
	con->tc_sig     = target;
	con->tc_connext = cons->tcs_con;
	cons->tcs_con   = con;
	con->tc_cons    = cons;

	/* Now insert the connection onto the stack used by `target'
	 * NOTE: `sig_send()' will always traverse the chain to the last
	 *       thread, meaning that we can (and have to) insert ourselves
	 *       at the front of the chain.
	 * Also note that inserting a new connection can be done without
	 * having to tinker with the signal's SMP-lock, so this part is
	 * actually surprisingly simple. */
	do {
		next = ATOMIC_READ(target->s_con);
		con->tc_signext = SIG_SMPLOCK_CLR(next);
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(target->s_con, next,
	                             SIG_SMPLOCK_CPY(con, next)));
}


/* Exactly the same as `task_connect()', however must be used when the connection
 * is made for a poll-based operation that only wishes to wait for some event to
 * be triggered, but does not wish to act upon this event by acquiring some kind
 * of lock with the intend to release it eventually, where the act of releasing
 * said lock includes a call to `sig_send()'.
 *
 * This connect() function is only required for signals that may be delivered via
 * `sig_send()', meaning that only a single thread would be informed of the signal
 * event having taken place. If in this scenario, the recipient thread (i.e the
 * thread that called `task_connect()') then decides not to act upon the signal
 * in question, but rather to do something else, the original intend of `sig_send()'
 * will become lost, that intend being for some (single) thread to try to acquire
 * an accompanying lock (for an example of this, see kernel header <sched/mutex.h>)
 *
 * As far as semantics go, a signal connection established with this function will
 * never satisfy a call to `sig_send()', and will instead be skipped if encountered
 * during its search for a recipient (such that by default, poll-connections will
 * only be acted upon when `sig_broadcast()' is used). However, if a call to
 * `sig_send()' is unable to find any non-poll-based connections, it will proceed
 * to act like a call to `sig_broadcast()' and wake all polling thread, though will
 * still end up returning `false', indicative of not having woken any (properly)
 * waiting thread.
 *
 * With all of this in mind, this function can also be though of as a sort-of
 * low-priority task connection, that will only be triggered after other connections
 * have already been served, and will only be woken by `sig_send()', when no other
 * connections exist.
 *
 * In practice, this function must be used whenever it is unknown what will eventually
 * happen after `task_waitfor()', or if what happens afterwards doesn't include the
 * acquisition of some kind of lock, whose release includes the sending of `target'.
 *
 * s.a. The difference between `task_disconnectall()' and `task_receiveall()' */
PUBLIC NONNULL((1)) void FCALL
task_connect_for_poll(struct sig *__restrict target) /*THROWS(E_BADALLOC)*/ {
	struct task_connection *con, *next;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;

	/* When a signal was already delivered, `task_connect()' becomes a no-op */
	if unlikely(ATOMIC_READ(cons->tcs_dlvr) != NULL)
		return;

	/* Allocate a new connection for `cons' */
	con = task_connection_alloc(cons);
	assert(!SIG_SMPLOCK_TST(con));

	/* Fill in the new connection. */
	con->tc_sig     = target;
	con->tc_connext = cons->tcs_con;
	cons->tcs_con   = con;
	con->tc_cons    = (struct task_connections *)((uintptr_t)cons | 1);

	/* Now insert the connection onto the stack used by `target'
	 * NOTE: `sig_send()' will always traverse the chain to the last
	 *       thread, meaning that we can (and have to) insert ourselves
	 *       at the front of the chain.
	 * Also note that inserting a new connection can be done without
	 * having to tinker with the signal's SMP-lock, so this part is
	 * actually surprisingly simple. */
	do {
		next = ATOMIC_READ(target->s_con);
		con->tc_signext = SIG_SMPLOCK_CLR(next);
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(target->s_con, next,
	                             SIG_SMPLOCK_CPY(con, next)));
}





/* Remove `con' from the linked list of active connections of `self'. */
LOCAL NOPREEMPT NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_unlink_from_sig)(struct sig *__restrict self,
                                               struct task_connection *__restrict con) {
	struct task_connection *chain;
again:
	assert(!SIG_SMPLOCK_TST(con->tc_signext));
	assert(!con->tc_signext || ADDR_ISKERN(con->tc_signext));
	chain = ATOMIC_READ(self->s_con);
	if (SIG_SMPLOCK_CLR(chain) == con) {
		/* The first entry already is the connection we're trying to unlink!
		 * In this case, we must use an atomic operation, since other thread
		 * or CPUs may have added more connections since the the read above. */
		if (!ATOMIC_CMPXCH_WEAK(self->s_con,
		                        chain,
		                        /* Keep the SMP-lock bit set! */
		                        SIG_SMPLOCK_SET(con->tc_signext)))
			goto again;
	} else {
		struct task_connection **pchain;
		/* Since the caller has acquired the SMP-lock of `self' for us,
		 * we are able to access all of the attached connections! */
		chain  = SIG_SMPLOCK_CLR(chain);
		pchain = &chain->tc_signext;
		assert(chain->tc_sig == self);
		for (;;) {
			chain = *pchain;
			assert(!SIG_SMPLOCK_TST(chain));
			assert(chain && ADDR_ISKERN(chain));
			assert(chain->tc_sig == self);
			if (chain == con)
				break; /* Found the entry! */
			pchain = &chain->tc_signext;
		}
		/* Unlink the element. */
		*pchain = chain->tc_signext;
	}
}


/* Same as `task_connection_unlink_from_sig()', but also release the SMP-lock. The caller
 * must then release the preemption lock through use of `sig_smp_lock_release_nosmp(self)' */
#if SIG_SMPLOCK_BIT == 0
#define TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG 1
#define task_connection_unlink_from_sig_and_unlock(self, con) \
	task_connection_unlink_from_sig(self, con)
#else /* SIG_SMPLOCK_BIT == 0 */
LOCAL NOPREEMPT NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_unlink_from_sig_and_unlock)(struct sig *__restrict self,
                                                          struct task_connection *__restrict con) {
	struct task_connection *chain;
again:
	assert(!SIG_SMPLOCK_TST(con->tc_signext));
	assert(!con->tc_signext || ADDR_ISKERN(con->tc_signext));
	chain = ATOMIC_READ(self->s_con);
	if (SIG_SMPLOCK_CLR(chain) == con) {
		/* The first entry already is the connection we're trying to unlink!
		 * In this case, we must use an atomic operation, since other thread
		 * or CPUs may have added more connections since the the read above. */
		if (!ATOMIC_CMPXCH_WEAK(self->s_con,
		                        chain,
		                        /* Don't keep the SMP-lock bit set! */
		                        con->tc_signext))
			goto again;
	} else {
		struct task_connection **pchain;
		/* Since the caller has acquired the SMP-lock of `self' for us,
		 * we are able to access all of the attached connections! */
		chain  = SIG_SMPLOCK_CLR(chain);
		pchain = &chain->tc_signext;
		assert(chain->tc_sig == self);
		for (;;) {
			chain = *pchain;
			assert(!SIG_SMPLOCK_TST(chain));
			assert(chain && ADDR_ISKERN(chain));
			assert(chain->tc_sig == self);
			if (chain == con)
				break; /* Found the entry! */
			pchain = &chain->tc_signext;
		}
		/* Unlink the element. */
		*pchain = chain->tc_signext;
		COMPILER_WRITE_BARRIER();
		/* Clear the SMP-lock bit. */
		ATOMIC_AND(self->s_ctl, ~SIG_SMPLOCK_BIT);
	}
}
#endif /* SIG_SMPLOCK_BIT != 0 */


/* Try to send the signal to a single, other thread, for the purpose
 * of forwarding. Additionally, release the SMP-lock of `self' */
PRIVATE NOPREEMPT NOBLOCK ATTR_NOINLINE NONNULL((1, 2)) bool
NOTHROW(FCALL sig_sendone_for_forwarding_and_unlock)(struct sig *self,
                                                     struct sig *sender) {
	bool is_broadcasting_poll = false;
	uintptr_t clt;
	struct task_connections *target_cons;
	struct task_connection *receiver;
	struct task_connection *con;
#if SIG_SMPLOCK_BIT != 0
	REF struct task *target_thread;
#else /* SIG_SMPLOCK_BIT != 0 */
	struct task *target_thread;
#endif /* SIG_SMPLOCK_BIT == 0 */
again:
	clt = ATOMIC_READ(self->s_ctl);
	con = SIG_SMPLOCK_CLR(clt);
	if unlikely(!con) {
no_cons:
		/* No one else here! (and nothing for us to do...)
		 * This is an undefined situation, since the original call to
		 * `sig_send()' that caused the signal which we ended up ignoring
		 * to be delivered returned `true', even though now, in the end,
		 * no one actually ended up getting the signal... */
#if SIG_SMPLOCK_BIT != 0
		if (!ATOMIC_CMPXCH_WEAK(self->s_ctl, clt, 0))
			goto again;
#endif /* SIG_SMPLOCK_BIT != 0 */
		return false;
	}
	/* Non-broadcast signals are sent to the oldest connection of `self'.
	 * As such, walk the chain of known connections until we find the last
	 * one of them all.
	 * NOTE: Since we're holding the SMP-lock at the moment, we are safe to
	 *       do this. */
	receiver = NULL;
	/* Find the first connection that is able to accept the signal. */
	for (;;) {
		uintptr_t status;
		status = ATOMIC_READ(con->tc_stat);
		assert(status != TASK_CONNECTION_STAT_BROADCAST);
		if (!TASK_CONNECTION_STAT_CHECK(status)) {
			if (is_broadcasting_poll || TASK_CONNECTION_STAT_ISNORM(status))
				receiver = con; /* This connection is still in alive. */
		}
		assert(status == TASK_CONNECTION_STAT_SENT);
		con = con->tc_signext;
		if (!con)
			break;
	}
	if unlikely(!receiver) {
		if (is_broadcasting_poll)
			goto no_cons;
		is_broadcasting_poll = true;
		goto again;
	}
	/* Try to switch the connection from `!TASK_CONNECTION_STAT_CHECK'
	 * to `TASK_CONNECTION_STAT_SENT'. */
	target_cons = ATOMIC_READ(receiver->tc_cons);
	if unlikely(TASK_CONNECTION_STAT_CHECK(target_cons))
		goto again;
	if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
	                        (struct task_connections *)TASK_CONNECTION_STAT_SENT))
		goto again;
	if unlikely(TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
		/* Deal with poll-based connections. */
		bool did_deliver;
		target_cons = TASK_CONNECTION_STAT_GETCONS(target_cons);
		did_deliver = ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender);
		task_connection_unlink_from_sig(self, receiver);
		ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
		if (did_deliver) {
			target_thread = ATOMIC_READ(target_cons->tcs_thread);
			if likely(target_thread)
				task_wake(target_thread);
		}
		goto again;
	}
	/* Try to set our signal as the one delivered to `target_cons'.
	 * If that part fails, change signal state to BROADCAST (even though
	 * that's not entirely correct), so we can get rid of the connection. */
	if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender)) {
		/* Unlink the signal, and mark it as broadcast. */
		task_connection_unlink_from_sig(self, receiver);
		ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
		goto again;
	}
	/* Unlock the signal, and wake-up the thread attached to the connection */
	target_thread = ATOMIC_READ(target_cons->tcs_thread);
#if SIG_SMPLOCK_BIT != 0
	xincref(target_thread);
	ATOMIC_AND(self->s_ctl, ~SIG_SMPLOCK_BIT);
#endif /* SIG_SMPLOCK_BIT != 0 */
	if likely(target_thread) {
		task_wake(target_thread);
#if SIG_SMPLOCK_BIT != 0
		decref(target_thread);
#endif /* SIG_SMPLOCK_BIT != 0 */
	}
	return true;
}


LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_disconnect_connection)(struct task_connection *__restrict self,
                                          struct task_connections *__restrict cons,
                                          bool forward_sent_signals) {
	uintptr_t old_state;
	struct sig *target;
	target = self->tc_sig;
again:
	old_state = ATOMIC_READ(self->tc_stat);
	if unlikely(old_state == TASK_CONNECTION_STAT_BROADCAST)
		return; /* After a broadcast, the signal will have already disconnected itself. */
	/* Acquire the SMP-lock for the signal. */
	sig_smp_lock_acquire(target);
	/* Make sure that our state hasn't changed. */
	if unlikely(ATOMIC_READ(self->tc_stat) != old_state) {
		sig_smp_lock_break(target);
		task_pause();
		goto again;
	}
#ifdef TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG
	task_connection_unlink_from_sig(target, self);
#endif /* TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG */
	if likely(old_state != TASK_CONNECTION_STAT_SENT || !forward_sent_signals) {
		/* Unlink our connection, and unlock the signal. */
#ifndef TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG
		task_connection_unlink_from_sig_and_unlock(target, self);
#endif /* !TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG */
	} else {
		/* Unlink our connection. */
#ifndef TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG
		task_connection_unlink_from_sig(target, self);
#endif /* !TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG */
		/* Forward the signal. */
		if (!sig_sendone_for_forwarding_and_unlock(target, ATOMIC_READ(cons->tcs_dlvr))) {
			/* At least log the fact that there has been a minor inconsistency... */
			printk(KERN_WARNING "[sig] Signal %p cannot be forwarded (no recipients)\n",
			       self);
		}
	}
	/* Release the SMP-lock from the signal. */
	sig_smp_lock_release_nosmp(target);
}


/* Disconnect from a specific signal `target'
 * @return: true:  Disconnected from `target'
 * @return: false: You weren't actually connected to `target' */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target) {
	struct task_connections *self;
	struct task_connection *con, **pcon;
	self = THIS_CONNECTIONS;
	/* Find the connection for `target' */
	pcon = &self->tcs_con;
	for (;;) {
		con = *pcon;
		if unlikely(!con)
			return false;
		if (con->tc_sig == target)
			break; /* Found it! */
		pcon = &con->tc_connext;
	}
	/* Delete this connection, and also forward an already-sent signal,
	 * even though in the event of the signal needing to be forwarded,
	 * the calling thread will have already received said signal, there
	 * is a good chance that once the caller notices that they've received
	 * a signal from which they've previously disconnected, they will
	 * choose to ignore that signal, though at that point we'll already
	 * no longer be able to forward it.
	 * So better be safe than sorry, and immediately forward it! */
	task_disconnect_connection(con, self, true);

	/* Unlink the connection from the thread-local active chain. */
	*pcon = con->tc_connext;

	/* Free the connection descriptor. */
	task_connection_free(self, con);
	return true;
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_connection_disconnect_all)(struct task_connections *__restrict self,
                                              bool forward_sent_signals) {
	struct task_connection *con;
	while ((con = self->tcs_con) != NULL) {
		/* Disconnect */
		task_disconnect_connection(con, self, forward_sent_signals);
		/* Unlink */
		self->tcs_con = con->tc_connext;
		/* Free */
		task_connection_free(self, con);
	}
}

/* Disconnect from all connected signal.
 * Signals with a state of `TASK_CONNECTION_STAT_SENT' will be forwarded. */
PUBLIC NOBLOCK void
NOTHROW(FCALL task_disconnectall)(void) {
	struct task_connections *self;
	self = THIS_CONNECTIONS;
	task_connection_disconnect_all(self, true);
	COMPILER_BARRIER();
	self->tcs_dlvr = NULL;
}

/* Same as `task_disconnectall()', but don't forward signals with a
 * `TASK_CONNECTION_STAT_SENT'-state, but rather return the sender
 * of of the signal that was received.
 * As such, the caller must properly pass on information about the
 * fact that a signal may have been received, as well as act upon
 * this fact. */
PUBLIC NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_receiveall)(void) {
	struct task_connections *self;
	struct sig *result;
	self = THIS_CONNECTIONS;
	task_connection_disconnect_all(self, false);
	COMPILER_BARRIER();
	result = self->tcs_dlvr;
	self->tcs_dlvr = NULL;
	return result;
}

/* Check if the calling thread is connected to any signal. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL task_isconnected)(void) {
	struct task_connections *self;
	self = THIS_CONNECTIONS;
	/* Check if there are any active connections. */
	return self->tcs_con != NULL;
}

/* Check if the calling thread is connected to the given signal. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL task_isconnected_to)(struct sig const *__restrict target) {
	struct task_connections *self;
	struct task_connection *con;
	self = THIS_CONNECTIONS;
	/* Find the connection for `target' */
	for (con = self->tcs_con; con; con = con->tc_connext) {
		if (con->tc_sig == target)
			return true; /* Found it! */
	}
	return false;
}

/* Check if there is a signal to was delivered, disconnecting
 * all other connected signals if this was the case.
 * @return: NULL: No signal is available
 * @return: * :   The signal that was delivered. */
PUBLIC NOBLOCK struct sig *NOTHROW(FCALL task_trywait)(void) {
	struct task_connections *self;
	struct sig *result;
	self   = THIS_CONNECTIONS;
	result = ATOMIC_READ(self->tcs_dlvr);
	if (result) {
		task_connection_disconnect_all(self, false);
		COMPILER_BARRIER();
		self->tcs_dlvr = NULL;
	}
	return result;
}



/* Check if the given signal has viable recipients.
 * This includes poll-based connections. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sig_iswaiting)(struct sig *__restrict self) {
	bool result = false;
	struct task_connection *cons;
	/* Quick check: Are there any established connections? */
	cons = SIG_SMPLOCK_CLR(ATOMIC_READ(self->s_con));
	if (cons) {
		/* Acquire the SMP-lock for `self', so we can inspect
		 * the chain of established connections more closely. */
		sig_smp_lock_acquire(self);
		for (cons = SIG_SMPLOCK_CLR(ATOMIC_READ(self->s_con));
		     cons; cons = cons->tc_signext) {
			uintptr_t status;
			status = ATOMIC_READ(cons->tc_stat);
			if (!TASK_CONNECTION_STAT_CHECK(status)) {
				/* Found an alive, normal connection! */
				result = true;
				break;
			}
		}
		sig_smp_lock_release(self);
	}
	return result;
}

/* Count the # of viable recipients of the given signal.
 * This includes poll-based connections. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_numwaiting)(struct sig *__restrict self) {
	size_t result = 0;
	struct task_connection *cons;
	/* Quick check: Are there any established connections? */
	cons = SIG_SMPLOCK_CLR(ATOMIC_READ(self->s_con));
	if (cons) {
		/* Acquire the SMP-lock for `self', so we can inspect
		 * the chain of established connections more closely. */
		sig_smp_lock_acquire(self);
		for (cons = SIG_SMPLOCK_CLR(ATOMIC_READ(self->s_con));
		     cons; cons = cons->tc_signext) {
			uintptr_t status;
			status = ATOMIC_READ(cons->tc_stat);
			if (!TASK_CONNECTION_STAT_CHECK(status))
				++result; /* Found an alive, normal connection! */
		}
		sig_smp_lock_release(self);
	}
	return result;
}


/* Same as `sig_send()', but repeat the operation up to `maxcount' times,
 * and return the # of times that `sig_send()' would have returned `true'
 * Equivalent to:
 * >> size_t result = 0;
 * >> while (maxcount) {
 * >>     if (!sig_send(self))
 * >>         break;
 * >>     --maxcount;
 * >>     ++result;
 * >> }
 * >> return result; */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_sendmany)(struct sig *__restrict self,
                            size_t maxcount) {
	size_t result = 0;
	while (maxcount) {
		if (!sig_send(self))
			break;
		--maxcount;
		++result;
	}
	return result;
}

PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altsendmany)(struct sig *self,
                               struct sig *sender,
                               size_t maxcount) {
	size_t result = 0;
	while (maxcount) {
		if (!sig_altsend(self, sender))
			break;
		--maxcount;
		++result;
	}
	return result;
}

#ifdef DEFINE_TEST
DEFINE_TEST(recursive_signals) {
	struct task_connections cons;
	struct sig s = SIG_INIT;
	task_disconnectall();
	task_connect(&s);
	task_pushconnections(&cons);
	task_connect(&s);

	assert(task_isconnected());
	assert(task_isconnected(&s));
	assert(task_trywait() == NULL);

	sig_broadcast(&s);

	/* Simulate what kfree() for the signal would do, thus
	 * ensuring that the the signal can still be received,
	 * even after it was destroyed. */
	memset(&s, 0xcc, sizeof(s));

	assert(task_isconnected());
	assert(task_isconnected(&s));

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);

	assert(task_popconnections() == &cons);

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);
}
#endif /* DEFINE_TEST */


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_sig_send 1
#include "signal-send.c.inl"

#define DEFINE_sig_altsend 1
#include "signal-send.c.inl"

#define DEFINE_sig_broadcast 1
#include "signal-send.c.inl"

#define DEFINE_sig_altbroadcast 1
#include "signal-send.c.inl"

#define DEFINE_sig_broadcast_as_nopr 1
#include "signal-send.c.inl"

#define DEFINE_sig_broadcast_destroylater_nopr 1
#include "signal-send.c.inl"

#define DEFINE_task_waitfor 1
#include "signal-waitfor.c.inl"

#define DEFINE_task_waitfor_norpc 1
#include "signal-waitfor.c.inl"

#define DEFINE_task_waitfor_nx 1
#include "signal-waitfor.c.inl"

#define DEFINE_task_waitfor_norpc_nx 1
#include "signal-waitfor.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_C */
