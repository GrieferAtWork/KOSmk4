/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_C
#define GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/cache.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/rpc.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sched/yield.h>

#include <kos/jiffies.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Must use locked memory to prevent dependency recursion with various sub-systems */
#define SIGNAL_GFP     GFP_LOCKED


/* FIXME: Supposedly, `connection_alloc()' (sometimes?) leaks memory. Figure out what that's about */
DEFINE_PREALLOCATION_CACHE(PRIVATE, connection, struct task_connection, 64);


INTERN ATTR_PERTASK struct task_connections _this_cons = {
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
#endif
#if CONFIG_TASK_STATIC_CONNECTIONS >= 3
		, INIT_STATIC
#endif
#if CONFIG_TASK_STATIC_CONNECTIONS >= 4
		, INIT_STATIC
#endif
#if CONFIG_TASK_STATIC_CONNECTIONS >= 5
		, INIT_STATIC
#endif
#if CONFIG_TASK_STATIC_CONNECTIONS >= 6
		, INIT_STATIC
#endif
#if CONFIG_TASK_STATIC_CONNECTIONS >= 7
		, INIT_STATIC
#endif
#if CONFIG_TASK_STATIC_CONNECTIONS >= 8
		, INIT_STATIC
#endif
#if CONFIG_TASK_STATIC_CONNECTIONS >= 9
#error "`CONFIG_TASK_STATIC_CONNECTIONS' is too large"
#endif
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
	cons                       = &FORTASK(self, _this_cons);
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



PUBLIC NONNULL((1)) void KCALL
task_connect(struct sig *__restrict target) THROWS(E_BADALLOC) {
	struct task_connection *con, *chain;
	struct task_connections *mycons;
	unsigned int i;
	uintptr_t flags = 0;
	assertf(IS_ALIGNED((uintptr_t)target, 2),
	        "target = %p", target);
	mycons = &PERTASK(_this_cons);
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
}

PUBLIC NONNULL((1)) void KCALL
task_connect_ghost(struct sig *__restrict target) THROWS(E_BADALLOC) {
	struct task_connection *con, *chain;
	struct task_connections *mycons;
	unsigned int i;
	uintptr_t flags = 0;
	assert(IS_ALIGNED((uintptr_t)target, 2));
	mycons          = &PERTASK(_this_cons);
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
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL task_connect_c)(struct task_connection *__restrict con,
                               struct sig *__restrict target) {
	struct task_connection *chain;
	struct task_connections *mycons;
	assert(IS_ALIGNED((uintptr_t)target, 2));
	mycons = &PERTASK(_this_cons);
#ifdef SIG_TEMPLOCK
initialize_con:
#endif /* SIG_TEMPLOCK */
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
		con->tc_connext = mycons->tc_signals.ts_cons;
		con->tc_signal  = target;
		con->tc_signext = chain;
	} while (!ATOMIC_CMPXCH_WEAK(target->s_ptr, chain, con));
	mycons->tc_signals.ts_cons = con;
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL task_connect_ghost_c)(struct task_connection *__restrict con,
                                    struct sig *__restrict target) {
	struct task_connection *chain;
	struct task_connections *mycons;
	assert(IS_ALIGNED((uintptr_t)target, 2));
	mycons = &PERTASK(_this_cons);
#ifdef SIG_TEMPLOCK
initialize_con:
#endif /* SIG_TEMPLOCK */
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
		con->tc_connext = mycons->tc_signals.ts_cons;
		con->tc_signal  = (struct sig *)((uintptr_t)target | 1);
		con->tc_signext = chain;
	} while (!ATOMIC_CMPXCH_WEAK(target->s_ptr, chain, con));
	mycons->tc_signals.ts_cons = con;
}



PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL task_isconnected)(void) {
	struct task_connections *mycons;
	mycons = &PERTASK(_this_cons);
	return mycons->tc_signals.ts_cons != NULL;
}

#if 0 /* This can't be used consistently, because a connection is terminated
       * as soon as the signal is delivered (meaning you'd no longer be connected
       * once the signal was given!) */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL task_isconnected_to)(struct sig *__restrict signal) {
	struct task_connections *mycons;
	struct task_connection *con;
	mycons = &PERTASK(_this_cons);
	for (con = mycons->tc_signals.ts_cons; con;
	     con = ((struct task_connection *)((uintptr_t)con & ~1))->tc_connext) {
		if (((uintptr_t)con->tc_signal & ~1) == (uintptr_t)signal)
			return true;
	}
	return false;
}
#endif

LOCAL NONNULL((1)) void
NOTHROW(KCALL task_disconnect_c_impl)(struct task_connection *__restrict con) {
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


PUBLIC NONNULL((1)) void
NOTHROW(KCALL task_disconnect_c)(struct task_connection *__restrict con) {
	struct task_connection **pcon, *iter;
	/* Remove the given connection from the chain of per-task linked connections. */
	pcon = &PERTASK(_this_cons.tc_signals.ts_cons);
	for (;;) {
		iter = *pcon;
		assertf(iter, "Not connected with task-connection at %p", con);
		if (iter != con) {
			pcon = &((struct task_connection *)((uintptr_t)iter & ~1))->tc_connext;
			continue;
		}
		*pcon = con->tc_connext;
		break;
	}
	task_disconnect_c_impl(con);
}

#if 0 /* Cannot be used without race condition, as the signal may
       * have already been delivered, causing the connection to
       * already be disconnected. */
PUBLIC NONNULL((1)) void
NOTHROW(KCALL task_disconnect)(struct sig *__restrict target) {
	struct task_connections *mycons;
	struct task_connection **pcon, *con;
	mycons = &PERTASK(_this_cons);
	for (pcon = &mycons->tc_signals.ts_cons;
	     (con = *pcon) != NULL; pcon = &con->tc_connext) {
		if (((uintptr_t)con->tc_signal & ~1) == (uintptr_t)target) {
			*pcon = con->tc_connext;
			task_disconnect_c_impl(con);
			return;
		}
	}
	COMPILER_READ_BARRIER();
	/* If the signal wasn't found, then it must have been delivered
	 * in the mean time, or already been delivered before. */
	assertf(mycons->tc_signals.ts_dlvr == target,
	        "Signal %p was never connected, or connected "
	        "as part of a pushed connections set",
	        target);
}
#endif

PUBLIC struct sig *
NOTHROW(KCALL task_disconnectall)(void) {
	struct sig *result;
	struct task_connection *con, *next;
	struct task_connections *mycons;
	mycons = &PERTASK(_this_cons);
	con    = mycons->tc_signals.ts_cons;
	if unlikely(!con)
		return NULL; /* No active connections. */
	mycons->tc_signals.ts_cons = NULL;
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



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_pushconnections)(struct task_connections *__restrict cons) {
	struct task_connections *mycons;
	struct task_connection *con;
	unsigned int i;
	IF_REENTRANT(pflag_t was);
	mycons = &PERTASK(_this_cons);
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
	cons->tc_signals.ts_cons   = con;
	COMPILER_WRITE_BARRIER();
	if (con) {
		mycons->tc_signals.ts_cons = NULL;
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
NOTHROW(KCALL task_popconnections)(struct task_connections *__restrict cons) {
	struct task_connection *con;
	struct task_connections *mycons;
	IF_REENTRANT(pflag_t was);
	mycons = &PERTASK(_this_cons);
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


PUBLIC NOBLOCK struct sig *NOTHROW(KCALL task_trywait)(void) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(_this_cons);
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	}
	return result;
}


PUBLIC struct sig *KCALL
task_waitfor(qtime_t const *abs_timeout) THROWS(E_WOULDBLOCK,...) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(_this_cons);
again:
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
got_signal:
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	} else {
		if unlikely_untraced(!PREEMPTION_ENABLED())
			THROW(E_WOULDBLOCK_PREEMPTED);
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
	return result;
}

PUBLIC WUNUSED struct sig *
NOTHROW(KCALL task_waitfor_nx)(qtime_t const *abs_timeout) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(_this_cons);
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
			return NULL;
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
	return result;
}

/* Same as `task_waitfor', but don't serve RPC functions, and return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
PUBLIC struct sig *
NOTHROW(KCALL task_waitfor_norpc_nx)(qtime_t const *abs_timeout) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(_this_cons);
again:
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
got_signal:
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	} else {
		if unlikely_untraced(!PREEMPTION_ENABLED())
			return NULL;
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
	return result;
}



PUBLIC struct sig *KCALL
task_waitfor_norpc(qtime_t const *abs_timeout) THROWS(E_WOULDBLOCK) {
	struct task_connections *mycons;
	struct sig *result;
	mycons = &PERTASK(_this_cons);
again:
	result = mycons->tc_signals.ts_dlvr;
	if (result) {
got_signal:
		task_disconnectall();
		COMPILER_WRITE_BARRIER();
		mycons->tc_signals.ts_dlvr = NULL;
	} else {
		if unlikely_untraced(!PREEMPTION_ENABLED())
			THROW(E_WOULDBLOCK_PREEMPTED);
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
	return result;
}




DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_C */
