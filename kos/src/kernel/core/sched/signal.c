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
#include <sched/signal.h>

#ifdef CONFIG_USE_NEW_SIGNAL_API
#include <kernel/except.h>
#include <kernel/printk.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

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
	ATOMIC_FETCHAND((self)->s_ctl, ~SIG_SMPLOCK_BIT)
#else /* SIG_SMPLOCK_BIT != 0 */
#define _sig_smp_lock_acquire(self) (void)0
#define _sig_smp_lock_release(self) (void)0
#endif /* SIG_SMPLOCK_BIT == 0 */

#define sig_smp_lock_acquire_nosmp(self)         \
	do {                                         \
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


/* Push/pop the active set of connections. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushconnections)(struct task_connections *__restrict cons) {
	struct task_connections *oldcons;
	unsigned int i;
	oldcons = THIS_CONNECTIONS;
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




/* Remove `con' from the linked list of active connections of `self'. */
LOCAL NOPREEMPT NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_unlink_from_sig)(struct sig *__restrict self,
                                               struct task_connection *__restrict con) {
	struct task_connection *chain;
again:
	assert(!SIG_SMPLOCK_TST(con->tc_signext));
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
		pchain = &chain->tc_signext;
		for (;;) {
			chain = *pchain;
			assert(chain);
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
		pchain = &chain->tc_signext;
		for (;;) {
			chain = *pchain;
			assert(chain);
			if (chain == con)
				break; /* Found the entry! */
			pchain = &chain->tc_signext;
		}
		/* Unlink the element. */
		*pchain = chain->tc_signext;
		/* Clear the SMP-lock bit. */
		ATOMIC_FETCHAND(self->s_ctl, ~SIG_SMPLOCK_BIT);
	}
}
#endif /* SIG_SMPLOCK_BIT != 0 */


/* Try to send the signal to a single, other thread, for the purpose
 * of forwarding. Additionally, release the SMP-lock of `self' */
PRIVATE NOPREEMPT NOBLOCK ATTR_NOINLINE ATTR_COLD NONNULL((1, 2)) bool
NOTHROW(FCALL sig_sendone_for_forwarding_and_unlock)(struct sig *self,
                                                     struct sig *sender) {
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
	receiver  = NULL;
	/* Find the first connection that is able to accept the signal. */
	for (;;) {
		uintptr_t status;
		status = ATOMIC_READ(con->tc_stat);
		assert(status != TASK_CONNECTION_STAT_BROADCAST);
		if (!TASK_CONNECTION_STAT_CHECK(status))
			receiver  = con; /* This connection is still in alive. */
		assert(status == TASK_CONNECTION_STAT_SENT);
		con = con->tc_signext;
		if (!con)
			break;
	}
	if unlikely(!receiver)
		goto no_cons;
	/* Try to switch the connection from `!TASK_CONNECTION_STAT_CHECK'
	 * to `TASK_CONNECTION_STAT_SENT'. */
	target_cons = ATOMIC_READ(receiver->tc_cons);
	if unlikely(TASK_CONNECTION_STAT_CHECK(target_cons))
		goto again;
	if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
	                        (struct task_connections *)TASK_CONNECTION_STAT_SENT))
		goto again;
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
	ATOMIC_FETCHAND(self->s_ctl, ~SIG_SMPLOCK_BIT);
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
	/* Delete this connection, but don't forward already-sent signals. */
	task_disconnect_connection(con, self, false);

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


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_sig_send 1
#include "signal-newsend.c.inl"

#define DEFINE_sig_altsend 1
#include "signal-newsend.c.inl"

#define DEFINE_sig_broadcast 1
#include "signal-newsend.c.inl"

#define DEFINE_sig_altbroadcast 1
#include "signal-newsend.c.inl"

#define DEFINE_task_waitfor 1
#include "signal-waitfor.c.inl"

#define DEFINE_task_waitfor_norpc 1
#include "signal-waitfor.c.inl"

#define DEFINE_task_waitfor_nx 1
#include "signal-waitfor.c.inl"

#define DEFINE_task_waitfor_norpc_nx 1
#include "signal-waitfor.c.inl"
#endif /* !__INTELLISENSE__ */


#else /* CONFIG_USE_NEW_SIGNAL_API */

#include <kernel/cache.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sched/yield.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define LOG_SET_ts_cons(v) \
	printk(KERN_DEBUG "%s:%d: %p.ts_cons = %p\n", __FILE__, __LINE__, THIS_TASK, (void *)(v))

DECL_BEGIN

/* Must use locked memory to prevent dependency recursion with various sub-systems */
#define SIGNAL_GFP GFP_LOCKED


/* FIXME: Supposedly, `connection_alloc()' (sometimes?) leaks memory. Figure out what that's about */
DEFINE_PREALLOCATION_CACHE(PRIVATE, connection, struct task_connection, 64);

/* Active connections of the current thread */
PUBLIC ATTR_PERTASK struct task_connections this_connections = {
	.tc_signals = {
		.ts_thread = NULL,
		.ts_cons   = NULL,
		.ts_dlvr   = NULL
	},
#if CONFIG_TASK_STATIC_CONNECTIONS >= 1
	.tc_static = {
#define INIT_STATIC                                     \
		{                                               \
			.tc_cons    = NULL,                         \
			.tc_signal  = TASK_CONNECTION_DISCONNECTED, \
			.tc_signext = NULL,                         \
			.tc_connext = NULL                          \
		}
		INIT_STATIC
#if CONFIG_TASK_STATIC_CONNECTIONS >= 2
		, INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 2 */
#if CONFIG_TASK_STATIC_CONNECTIONS >= 3
		, INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 3 */
#if CONFIG_TASK_STATIC_CONNECTIONS >= 4
		, INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 4 */
#if CONFIG_TASK_STATIC_CONNECTIONS >= 5
		, INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 5 */
#if CONFIG_TASK_STATIC_CONNECTIONS >= 6
		, INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 6 */
#if CONFIG_TASK_STATIC_CONNECTIONS >= 7
		, INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 7 */
#if CONFIG_TASK_STATIC_CONNECTIONS >= 8
		, INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 8 */
#if CONFIG_TASK_STATIC_CONNECTIONS >= 9
#error "`CONFIG_TASK_STATIC_CONNECTIONS' is too large"
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 9 */
	},
#undef INIT_STATIC
#endif /* CONFIG_TASK_STATIC_CONNECTIONS >= 1 */
	.tc_static_v = NULL /* Fill in by `init_task_connections' */
};

DEFINE_PERTASK_INIT(pertask_init_task_connections);
DEFINE_PERTASK_ONEXIT(task_disconnectall); /* Disconnect all remaining connections during task cleanup. */

INTERN NOBLOCK void
NOTHROW(KCALL pertask_init_task_connections)(struct task *__restrict self) {
	struct task_connections *cons;
	cons                       = &FORTASK(self, this_connections);
	cons->tc_static_v          = cons->tc_static;
	cons->tc_signals.ts_thread = self;
}

#ifndef __INTELLISENSE__
DECL_END

#include "signal-send.c.inl"

#define DEFINE_ALTERNATE 1
#include "signal-send.c.inl"

#define DEFINE_SINGLE    1
#include "signal-send.c.inl"

#define DEFINE_SINGLE    1
#define DEFINE_ALTERNATE 1
#include "signal-send.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */



/* Connect the calling thread to a given signal.
 * @throw: E_BADALLOC:   [task_connect[_ghost]] Insufficient memory (only when there are
 *                        at least `CONFIG_TASK_STATIC_CONNECTIONS' connections already). */
PUBLIC NONNULL((1)) void FCALL
task_connect(struct sig *__restrict target) /*THROWS(E_BADALLOC)*/ {
	struct task_connection *con, *chain;
	struct task_connections *mycons;
	unsigned int i;
	uintptr_t flags = 0;
	assertf(IS_ALIGNED((uintptr_t)target, 2),
	        "target = %p", target);
	mycons = &PERTASK(this_connections);
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i) {
		con = &mycons->tc_static_v[i];
		if (con->tc_signal == TASK_CONNECTION_DISCONNECTED)
			goto initialize_con;
	}
	assert(task_isconnected());
	con   = connection_alloc(SIGNAL_GFP);
	flags = 1;
initialize_con:
	do {
		chain = ATOMIC_READ(target->s_ptr);
		if (ATOMIC_READ(mycons->tc_signals.ts_dlvr))
			return; /* A pending signal has already been delivered (no need for more connections) */
#ifdef SIG_TEMPLOCK
		if unlikely(chain == SIG_TEMPLOCK) {
			task_pause();
			goto initialize_con;
		}
		assert(con != SIG_TEMPLOCK);
#endif /* SIG_TEMPLOCK */
		con->tc_cons = &mycons->tc_signals;
		assert(!((uintptr_t)mycons->tc_signals.ts_cons & 1));
		con->tc_connext = (struct task_connection *)((uintptr_t)mycons->tc_signals.ts_cons | flags);
		con->tc_signal  = target;
		con->tc_signext = chain;
	} while (!ATOMIC_CMPXCH_WEAK(target->s_ptr, chain, con));
	mycons->tc_signals.ts_cons = con;
	LOG_SET_ts_cons(con);
}

PUBLIC NONNULL((1)) void FCALL
task_connect_ghost(struct sig *__restrict target) /*THROWS(E_BADALLOC)*/ {
	struct task_connection *con, *chain;
	struct task_connections *mycons;
	unsigned int i;
	uintptr_t flags = 0;
	assert(IS_ALIGNED((uintptr_t)target, 2));
	mycons          = &PERTASK(this_connections);
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i) {
		con = &mycons->tc_static_v[i];
		if (con->tc_signal == TASK_CONNECTION_DISCONNECTED)
			goto initialize_con;
	}
	assert(task_isconnected());
	con   = connection_alloc(SIGNAL_GFP);
	flags = 1;
initialize_con:
	do {
		chain = ATOMIC_READ(target->s_ptr);
		if (ATOMIC_READ(mycons->tc_signals.ts_dlvr))
			return; /* A pending signal has already been delivered (no need for more connections) */
#ifdef SIG_TEMPLOCK
		if unlikely(chain == SIG_TEMPLOCK) {
			task_pause();
			goto initialize_con;
		}
		assert(con != SIG_TEMPLOCK);
#endif /* SIG_TEMPLOCK */
		con->tc_cons = &mycons->tc_signals;
		assert(!((uintptr_t)mycons->tc_signals.ts_cons & 1));
		con->tc_connext = (struct task_connection *)((uintptr_t)mycons->tc_signals.ts_cons | flags);
		con->tc_signal  = (struct sig *)((uintptr_t)target | 1);
		con->tc_signext = chain;
	} while (!ATOMIC_CMPXCH_WEAK(target->s_ptr, chain, con));
	mycons->tc_signals.ts_cons = con;
	LOG_SET_ts_cons(con);
}


PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL task_isconnected)(void) {
	struct task_connections *mycons;
	mycons = &PERTASK(this_connections);
	return mycons->tc_signals.ts_cons != NULL;
}

#if 0 /* This can't be used consistently, because a connection is terminated
       * as soon as the signal is delivered (meaning you'd no longer be connected
       * once the signal was given!) */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL task_isconnected_to)(struct sig *__restrict signal) {
	struct task_connections *mycons;
	struct task_connection *con;
	mycons = &PERTASK(this_connections);
	for (con = mycons->tc_signals.ts_cons; con;
	     con = ((struct task_connection *)((uintptr_t)con & ~1))->tc_connext) {
		if (((uintptr_t)con->tc_signal & ~1) == (uintptr_t)signal)
			return true;
	}
	return false;
}
#endif

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_disconnect_c_impl)(struct task_connection *__restrict con) {
	struct sig *signal;
	struct task_connection *sigcon;
again:
	do {
		signal = ATOMIC_READ(con->tc_signal);
		if (signal == TASK_CONNECTION_DELIVERING) {
			task_tryyield_or_pause();
			goto again;
		}
		if (signal == TASK_CONNECTION_DELIVERED)
			goto done_unlink_con;
		assertf(signal != TASK_CONNECTION_DISCONNECTING,
		        "Recursive disconnection isn't allowed (or should ever happen)");
	} while (!ATOMIC_CMPXCH_WEAK(con->tc_signal, signal,
	                             TASK_CONNECTION_DISCONNECTING));
	signal = (struct sig *)((uintptr_t)signal & ~1); /* Clear GHOST bit */
	/* Successfully marked the connection such that it won't be delivered.
	 * Now we must manually remove the connection from the signal. */
again_read_signal_pointer:
	sigcon = ATOMIC_READ(signal->s_ptr);
	if (sigcon == con) {
		/* lucky! we're the first connection, so we can try to directly unlink ourself! */
#ifdef SIG_TEMPLOCK
		assert(con->tc_signext != SIG_TEMPLOCK);
#endif /* SIG_TEMPLOCK */
		if (ATOMIC_CMPXCH_WEAK(signal->s_ptr, con, con->tc_signext))
			goto done_unlink_con;
		goto again_read_signal_pointer;
	}
	if unlikely(!sigcon) {
		/* The signal is currently being delivered, but hasn't reached our
		 * connection yet. - There's really nothing we can do to stop it now,
		 * so all we can really do is let it happen and wait until our connection
		 * changes its state to `TASK_CONNECTION_DELIVERED', indicating
		 * that the signal sender is done with us. */
		for (;;) {
			signal = ATOMIC_READ(con->tc_signal);
			assert(signal == TASK_CONNECTION_DISCONNECTING ||
			       signal == TASK_CONNECTION_DELIVERED);
			if (signal == TASK_CONNECTION_DELIVERED)
				break;
			task_tryyield_or_pause();
		}
		goto done_unlink_con;
	}
#ifdef SIG_TEMPLOCK
	if unlikely(sigcon == SIG_TEMPLOCK) {
		task_pause();
		goto again_read_signal_pointer;
	}
#endif /* SIG_TEMPLOCK */
	/* The slow case:
	 *   - We must steal all of the signal's connections and replace them with
	 *     a new, temporary set of connections which we can track independently
	 *     for being broadcast.
	 *   - After doing this, search the stolen set of connections for our's,
	 *     and if found remove it.
	 *     If not found, this can only mean that some other thread has already
	 *     done the same, and is currently in the process or removing their
	 *     own connection from the signal, in which case we must wait for them
	 *     to be finished, before trying again.
	 *   - After restoring the old chain of connections, check if the signal
	 *     was delivered in the mean time, and if so: broadcast it again.
	 */
	{
		struct task_connection *sigcon_iter, *sigcon_prev;
		struct task_connection tempcon;
		struct task_sigset tempcons;
		bool did_find;
		tempcons.ts_thread = NULL; /* Not an actual target */
		tempcons.ts_cons   = &tempcon;
		tempcons.ts_dlvr   = NULL;
		tempcon.tc_connext = NULL;
		tempcon.tc_cons    = &tempcons;
		tempcon.tc_signal  = signal;
		tempcon.tc_signext = NULL;
		if (!ATOMIC_CMPXCH_WEAK(signal->s_ptr, sigcon, &tempcon))
			goto again_read_signal_pointer;

		/* Search the set of stolen connection for our own. */
		did_find    = false;
		sigcon_prev = sigcon;
		sigcon_iter = sigcon->tc_signext;
		for (; sigcon_iter;
		     sigcon_prev = sigcon_iter,
		     sigcon_iter = sigcon_iter->tc_signext) {
			if (sigcon_iter != con)
				continue; /* Not our connection! */
			/* Found it! (remove our connection) */
			assert(sigcon_prev->tc_signext == con);
			sigcon_prev->tc_signext = sigcon_iter = con->tc_signext;
			did_find                              = true;
			break;
		}
		/* Restore all of the signals. */
#ifdef SIG_TEMPLOCK
		{
			struct task_connection *oldcon;
			assert(sigcon != SIG_TEMPLOCK);
			while ((oldcon = ATOMIC_CMPXCH_VAL(signal->s_ptr, &tempcon, sigcon)) != &tempcon) {
				if (oldcon == SIG_TEMPLOCK) {
					task_pause();
					continue;
				}
				/* Manually disconnect the temporary connection. */
				task_disconnect_c_impl(&tempcon);
			}
		}
#else /* SIG_TEMPLOCK */
		if (!ATOMIC_CMPXCH(signal->s_ptr, &tempcon, sigcon)) {
			/* Manually disconnect the temporary connection. */
			task_disconnect_c_impl(&tempcon);
		}
#endif /* !SIG_TEMPLOCK */
		if (tempcons.ts_dlvr)
			sig_altbroadcast(signal, tempcons.ts_dlvr);
		if (!did_find) {
			/* If we didn't find our signal, there must be another thread that's
			 * currently in the process of disconnecting the from the same signal,
			 * in which case the  */
			task_tryyield_or_pause();
			goto again_read_signal_pointer;
		}
	}
done_unlink_con:
	/* Mark the connection as free */
	con->tc_signal = TASK_CONNECTION_DISCONNECTED;
}


/* Disconnect from a specific signal `target'
 * No-op if the caller isn't actually connected to `target'
 * WARNING: If the connected signal was already sent, causing the calling
 *          thread to enter a signaled state, that state will not be
 *          reverted by this call! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target) {
	struct task_connections *mycons;
	struct task_connection **pcon, *con;
	mycons = &PERTASK(this_connections);
	for (pcon = &mycons->tc_signals.ts_cons;
	     (con = *pcon) != NULL; pcon = &con->tc_connext) {
		if (((uintptr_t)con->tc_signal & ~1) == (uintptr_t)target) {
			*pcon = con->tc_connext;
			if (pcon == &mycons->tc_signals.ts_cons)
				LOG_SET_ts_cons(con->tc_connext);
			task_disconnect_c_impl(con);
			return;
		}
	}
	/* Failed to find `target' within our connections set.
	 * However, there is a possibility that `target' was/is being sent,
	 * such that its connection slot already changed state to either
	 * `TASK_CONNECTION_DELIVERED' or `TASK_CONNECTION_DELIVERING',
	 * meaning that the connection's gone in this case as well! */
}


PUBLIC NOBLOCK struct sig *
NOTHROW(FCALL task_disconnectall)(void) {
	struct sig *result;
	struct task_connection *con, *next;
	struct task_connections *mycons;
	mycons = &PERTASK(this_connections);
	con    = mycons->tc_signals.ts_cons;
	if unlikely(!con)
		return NULL; /* No active connections. */
	mycons->tc_signals.ts_cons = NULL;
	LOG_SET_ts_cons(NULL);
	while (con) {
		next = con->tc_connext;
		task_disconnect_c_impl(con);
		if ((uintptr_t)next & 1)
			connection_free(con);
		con = (struct task_connection *)((uintptr_t)next & ~1);
	}
	result = mycons->tc_signals.ts_dlvr;
	COMPILER_WRITE_BARRIER();
	mycons->tc_signals.ts_dlvr = NULL;
	assert(!task_isconnected());
	return result;
}

#undef CONFIG_TASK_PUSHCONNECTIONS_REENTRANT
/* We need the connection push/pop sub-system to be re-entrant because
 * it gets used by the #PF handler, that it would cause problems to
 * introduce a rule to disallow its use from other handlers, especially
 * considering that our gdbstub uses this mechanism from within debug
 * traps. */
#define CONFIG_TASK_PUSHCONNECTIONS_REENTRANT 1

#ifdef CONFIG_TASK_PUSHCONNECTIONS_REENTRANT
#define IF_REENTRANT(...) __VA_ARGS__
#else /* CONFIG_TASK_PUSHCONNECTIONS_REENTRANT */
#define IF_REENTRANT(...) /* nothing */
#endif /* !CONFIG_TASK_PUSHCONNECTIONS_REENTRANT */



/* Push/pop the active set of connections.
 * NOTE: After having been pushed, the calling thread will appear to not be connected
 *       to anything. - Similarly, `task_popconnections()' may only be called after
 *       all connections made were disconnected again.
 *    -> Signals delivered in the mean time will then immediately be available. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushconnections)(struct task_connections *__restrict cons) {
	struct task_connections *mycons;
	struct task_connection *con;
	unsigned int i;
	IF_REENTRANT(pflag_t was);
	mycons = &PERTASK(this_connections);
	assertf(mycons->tc_static_v != cons->tc_static,
	        "Connection %p set was already pushed", cons); /* Why does this fail? */
	/* Initialize the static connection vector. */
	for (i = 0; i < CONFIG_TASK_STATIC_CONNECTIONS; ++i) {
		cons->tc_static[i].tc_cons    = NULL;
		cons->tc_static[i].tc_signal  = TASK_CONNECTION_DISCONNECTED;
		cons->tc_static[i].tc_signext = NULL;
		cons->tc_static[i].tc_connext = NULL;
	}
	cons->tc_signals.ts_thread = NULL;
	cons->tc_signals.ts_dlvr   = NULL;
	IF_REENTRANT(was = PREEMPTION_PUSHOFF());
	con = mycons->tc_signals.ts_cons;
	cons->tc_signals.ts_cons = con;
	COMPILER_WRITE_BARRIER();
	if (con) {
		mycons->tc_signals.ts_cons = NULL;
		LOG_SET_ts_cons(NULL);
		COMPILER_WRITE_BARRIER();
		do {
			struct task_sigset *con_sigset;
			do {
				con_sigset = ATOMIC_READ(con->tc_cons);
				if (!con_sigset)
					break; /* The signal is/was being delivered. */
			} while (!ATOMIC_CMPXCH_WEAK(con->tc_cons, con_sigset, &cons->tc_signals));
		} while ((con = (struct task_connection *)((uintptr_t)con->tc_connext & ~1)) != NULL);
	}
	COMPILER_BARRIER();
	cons->tc_static_v   = mycons->tc_static_v;
	mycons->tc_static_v = cons->tc_static;
	COMPILER_BARRIER();
	{
		/* Remember any signal that has already been delivered. */
		struct sig *last_deliver;
		last_deliver = ATOMIC_READ(mycons->tc_signals.ts_dlvr);
		if (last_deliver)
			ATOMIC_CMPXCH(cons->tc_signals.ts_dlvr, NULL, last_deliver);
	}
	IF_REENTRANT(PREEMPTION_POP(was));
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_popconnections)(struct task_connections *__restrict cons) {
	struct task_connection *con;
	struct task_connections *mycons;
	IF_REENTRANT(pflag_t was);
	mycons = &PERTASK(this_connections);
	assertf(cons->tc_signals.ts_thread == NULL,
	        "Invalid saved connection set");
	assertf(mycons->tc_static_v == cons->tc_static,
	        "Invalid connection set popped");
	assertf(mycons->tc_signals.ts_cons == NULL,
	        "Can't pop connection set: there are still active connections");
	IF_REENTRANT(was = PREEMPTION_PUSHOFF());
	mycons->tc_signals.ts_dlvr = NULL;
	mycons->tc_static_v        = cons->tc_static_v;
	con                        = cons->tc_signals.ts_cons;
	mycons->tc_signals.ts_cons = con;
	LOG_SET_ts_cons(con);
	COMPILER_BARRIER();
	/* Restore connections. */
	for (; con; con = (struct task_connection *)((uintptr_t)con->tc_connext & ~1)) {
		struct task_sigset *con_sigset;
		do {
			con_sigset = ATOMIC_READ(con->tc_cons);
			if (!con_sigset)
				break; /* The signal is/was being delivered. */
		} while (!ATOMIC_CMPXCH_WEAK(con->tc_cons, con_sigset, &mycons->tc_signals));
	}
	COMPILER_BARRIER();
	/* Remember any signal that was delivered in the mean time. */
	{
		struct sig *last_deliver;
		last_deliver = ATOMIC_READ(cons->tc_signals.ts_dlvr);
		if (last_deliver)
			ATOMIC_CMPXCH(mycons->tc_signals.ts_dlvr, NULL, last_deliver);
	}
	IF_REENTRANT(PREEMPTION_POP(was));
}
#undef IF_REENTRANT

/* Check if there is a signal to was delivered, disconnecting
 * all other connected signals if this was the case.
 * @return: NULL: No signal is available
 * @return: * :   The signal that was delivered. */
PUBLIC NOBLOCK struct sig *NOTHROW(FCALL task_trywait)(void) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(this_connections);
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	}
	return result;
}

/* Wait for the first signal to be delivered, unconditionally
 * disconnecting all connected signals thereafter.
 * NOTE: Prior to fully starting to block, this function will call `task_serve()'
 * @param: abs_timeout:  The `realtime()' timeout for the wait.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked.
 * @throw: * :          [task_waitfor] An error was thrown by an RPC function.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 * @return: NULL: No signal has become available (never returned when `NULL' is passed for `abs_timeout').
 * @return: * :   The signal that was delivered. */
PUBLIC struct sig *FCALL
task_waitfor(struct timespec const *abs_timeout)
		THROWS(E_WOULDBLOCK, ...) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(this_connections);
again:
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
got_signal:
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	} else {
		if unlikely_untraced(!PREEMPTION_ENABLED()) {
			result = task_disconnectall();
			if unlikely_untraced(result)
				goto done;
			THROW(E_WOULDBLOCK_PREEMPTED);
		}
		PREEMPTION_DISABLE();
		COMPILER_READ_BARRIER();
		result = mycons->tc_signals.ts_dlvr;
		if unlikely(result) {
			PREEMPTION_ENABLE();
			goto got_signal;
		}
		TRY {
			if (task_serve())
				goto again;
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		if (!task_sleep(abs_timeout))
			return task_disconnectall(); /* Timeout */
		COMPILER_READ_BARRIER();
		goto again;
	}
done:
	assert(!task_isconnected());
	return result;
}

/* Same as `task_waitfor', but only service NX RPCs, and return `NULL' if
 * there are pending RPCs that are allowed to throw exception, or if preemption
 * was disabled, and the operation would have blocked. */
PUBLIC WUNUSED struct sig *
NOTHROW(FCALL task_waitfor_nx)(struct timespec const *abs_timeout) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(this_connections);
again:
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
got_signal:
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	} else {
		unsigned int what;
		if unlikely_untraced(!PREEMPTION_ENABLED())
			return task_disconnectall();
		PREEMPTION_DISABLE();
		COMPILER_READ_BARRIER();
		result = mycons->tc_signals.ts_dlvr;
		if unlikely(result) {
			PREEMPTION_ENABLE();
			goto got_signal;
		}
		what = task_serve_nx();
		if (what & TASK_SERVE_NX_DIDRUN)
			goto again;
		if (what & TASK_SERVE_NX_XPENDING) {
			/* Can't go to sleep while there are pending X-RPCs */
			PREEMPTION_ENABLE();
			return task_disconnectall();
		}
		if (!task_sleep(abs_timeout))
			return task_disconnectall(); /* Timeout */
		COMPILER_READ_BARRIER();
		goto again;
	}
	assert(!task_isconnected());
	return result;
}

/* Same as `task_waitfor', but don't serve RPC functions, and return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
PUBLIC struct sig *
NOTHROW(FCALL task_waitfor_norpc_nx)(struct timespec const *abs_timeout) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(this_connections);
again:
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
got_signal:
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	} else {
		if unlikely_untraced(!PREEMPTION_ENABLED())
			return task_disconnectall();
		PREEMPTION_DISABLE();
		COMPILER_READ_BARRIER();
		result = mycons->tc_signals.ts_dlvr;
		if unlikely(result) {
			PREEMPTION_ENABLE();
			goto got_signal;
		}
		if (!task_sleep(abs_timeout))
			return task_disconnectall(); /* Timeout */
		COMPILER_READ_BARRIER();
		goto again;
	}
	assert(!task_isconnected());
	return result;
}

/* Same as `task_waitfor', but don't serve RPC functions. */
PUBLIC struct sig *FCALL
task_waitfor_norpc(struct timespec const *abs_timeout)
		THROWS(E_WOULDBLOCK) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(this_connections);
again:
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
got_signal:
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	} else {
		if unlikely_untraced(!PREEMPTION_ENABLED()) {
			result = task_disconnectall();
			if unlikely_untraced(result)
				goto done;
			THROW(E_WOULDBLOCK_PREEMPTED);
		}
		PREEMPTION_DISABLE();
		COMPILER_READ_BARRIER();
		result = mycons->tc_signals.ts_dlvr;
		if unlikely(result) {
			PREEMPTION_ENABLE();
			goto got_signal;
		}
		if (!task_sleep(abs_timeout))
			return task_disconnectall(); /* Timeout */
		COMPILER_READ_BARRIER();
		goto again;
	}
done:
	assert(!task_isconnected());
	return result;
}


DECL_END
#endif /* !CONFIG_USE_NEW_SIGNAL_API */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_C */
