/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIG_C
#define GUARD_KERNEL_INCLUDE_SCHED_SIG_C 1
#define __SIG_INTERNAL_EXPOSE_CONTROL_WORD 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/selftest.h> /* DEFINE_TEST */
#include <sched/pertask.h>
#include <sched/rpc.h>
#include <sched/sig-completion.h>
#include <sched/sig-select.h>
#include <sched/sig.h>
#include <sched/task-clone.h> /* DEFINE_PERTASK_RELOCATION */
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <kos/nopf.h>

#include <alloca.h>
#include <assert.h>
#include <inttypes.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#if defined(__i386__) || defined(__x86_64__)
#include <asm/intrin.h>
#include <kos/kernel/x86/segment.h>
#endif /* __i386__ || __x86_64__ */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Internal key used to chain threads that have to be destroyed. */
#define sig_destroylater_next(thread) KEY_task__next(thread)

DECL_BEGIN

/* Assert offsets */
static_assert(offsetof(struct task_connection, tc_sig) == OFFSET_TASK_CONNECTION_SIG);
static_assert(offsetof(struct task_connection, tc_connext) == OFFSET_TASK_CONNECTION_CONNEXT);
static_assert(offsetof(struct task_connection, tc_signext) == OFFSET_TASK_CONNECTION_SIGNEXT);
static_assert(offsetof(struct task_connection, tc_cons) == OFFSET_TASK_CONNECTION_CONS);
static_assert(offsetof(struct task_connection, tc_stat) == OFFSET_TASK_CONNECTION_STAT);
static_assert(sizeof(struct task_connection) == SIZEOF_TASK_CONNECTION);
static_assert(alignof(struct task_connection) == ALIGNOF_TASK_CONNECTION);
static_assert(offsetof(struct task_connections, tcs_prev) == OFFSET_TASK_CONNECTIONS_PREV);
static_assert(offsetof(struct task_connections, tcs_thread) == OFFSET_TASK_CONNECTIONS_THREAD);
static_assert(offsetof(struct task_connections, tcs_con) == OFFSET_TASK_CONNECTIONS_CON);
static_assert(offsetof(struct task_connections, tcs_dlvr) == OFFSET_TASK_CONNECTIONS_DLVR);
static_assert(offsetof(struct task_connections, tcs_static) == OFFSET_TASK_CONNECTIONS_STATIC);
static_assert(sizeof(struct task_connections) == SIZEOF_TASK_CONNECTIONS);
static_assert(alignof(struct task_connections) == ALIGNOF_TASK_CONNECTIONS);


/* Root connections set. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct task_connections) this_root_connections = {
	.tcs_prev   = NULL,
	.tcs_thread = NULL,
	.tcs_con    = NULL,
	.tcs_dlvr   = NULL,
	.tcs_static = { }
};

/* [1..1][lock(PRIVATE(THIS_TASK))]  Current   set   of   in-use   connections.
 * Most of the time, this will simply point to `PERTASK(this_root_connections)' */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct task_connections *)
this_connections = &this_root_connections;

/* Define relocations */
DEFINE_PERTASK_RELOCATION(this_root_connections + OFFSET_TASK_CONNECTIONS_THREAD);
DEFINE_PERTASK_RELOCATION(this_connections);

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_fix_task_connections)(struct task *__restrict self) {
	struct task *active_thread;
	struct task_connections *self_connections;
	self_connections = FORTASK(self, this_connections);
	if (!ADDR_ISKERN(self_connections))
		goto fixit;
	if (!IS_ALIGNED((uintptr_t)self_connections, alignof(struct task_connections)))
		goto fixit;
	if (memcpy_nopf(&active_thread, &self_connections->tcs_thread, sizeof(struct task *)) != 0)
		goto fixit;
	if (active_thread != self)
		goto fixit;
	return;
fixit:
	FORTASK(self, this_connections) = &FORTASK(self, this_root_connections);
	bzero(&FORTASK(self, this_root_connections), sizeof(struct task_connections));
	FORTASK(self, this_root_connections.tcs_thread) = self;
}

#if defined(__x86_64__) || defined(__i386__)
INTERN NOBLOCK ATTR_RETNONNULL struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void);
#endif /* __x86_64__ || __i386__ */

/* Push/pop the active  set of  connections:
 * >> struct sig a = SIG_INIT, b = SIG_INIT;
 * >> struct task_connections cons;
 * >> task_connect(&a);
 * >> assert(task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_pushconnections(&cons);
 * >> assert(!task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_connect(&b);
 * >> assert(!task_wasconnected(&a));
 * >> assert(task_wasconnected(&b));
 * >>
 * >> task_disconnectall();
 * >> assert(!task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b));
 * >>
 * >> task_popconnections();
 * >> assert(task_wasconnected(&a));
 * >> assert(!task_wasconnected(&b)); */
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
	if unlikely(!read_nopf(&FORTASK(mythread, this_connections), &oldcons)) {
		assertf(read_nopf(&FORTASK(mythread, this_connections), &oldcons),
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
	cons->tcs_prev = oldcons;

	/* Disable async notifications for the old set of connections,
	 * and use the receiver thread for the new set of connections.
	 * Really, though: This should always just be `THIS_TASK' */
	cons->tcs_thread = ATOMIC_XCH(oldcons->tcs_thread, NULL);
	cons->tcs_con    = NULL; /* No connections in use (yet) */
	cons->tcs_dlvr   = NULL; /* Nothing was delivered (yet) */
	DBG_memset(cons->tcs_static, 0xcc, sizeof(cons->tcs_static));

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
	assert((cons->tcs_prev == NULL) == (cons == THIS_ROOT_CONNECTIONS));
	assertf(cons != THIS_ROOT_CONNECTIONS,
	        "Cannot pop connections: Root connection set %p is already active",
	        cons);

	/* Make sure that no connections are left active. */
	assertf(cons->tcs_con == NULL,
	        "Cannot call `task_popconnections()' when you've still "
	        "got connections that haven't been disconnected, yet\n"
	        "call `task_disconnectall()' first!");

	/* Set the TLS pointer for the current set of connection to the old set. */
	oldcons = cons->tcs_prev;
	PERTASK_SET(this_connections, oldcons);

	/* Re-enable asynchronous notifications as the result of `sig_send()' / `sig_broadcast()' */
	ATOMIC_WRITE(oldcons->tcs_thread, THIS_TASK);

	/* Make bad usage consistent by filling memory with garbage. */
	DBG_memset(cons, 0xcc, sizeof(*cons));

	return cons;
}


/* Allocate a new task connection. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct task_connection *FCALL
task_connection_alloc(struct task_connections *__restrict self) THROWS(E_BADALLOC) {
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

/* Free a given task connection. */
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



#if defined(SIG_CONTROL_SMPLOCK) && SIG_CONTROL_SMPLOCK != 0
#define sig_smplock_set(con)      ((struct task_connection *)((uintptr_t)(con) | SIG_CONTROL_SMPLOCK))
#define sig_smplock_clr(con)      ((struct task_connection *)((uintptr_t)(con) & ~SIG_CONTROL_SMPLOCK))
#define sig_smplock_tst(con)      ((uintptr_t)(con) & SIG_CONTROL_SMPLOCK)
#define sig_smplock_cpy(to, from) (struct task_connection *)((uintptr_t)(to) | ((uintptr_t)(from) & SIG_CONTROL_SMPLOCK))
#define sig_smplock_tryacquire_nopr(self) \
	(!(__hybrid_atomic_fetchor((self)->s_ctl, SIG_CONTROL_SMPLOCK, __ATOMIC_ACQUIRE) & SIG_CONTROL_SMPLOCK))
#define sig_smplock_acquire_nopr(self)             \
	do {                                           \
		while (!sig_smplock_tryacquire_nopr(self)) \
			task_pause();                          \
	}	__WHILE0
#define sig_smplock_release_nopr(self) \
	__hybrid_atomic_fetchand((self)->s_ctl, ~SIG_CONTROL_SMPLOCK, __ATOMIC_RELEASE)
#else /* SIG_CONTROL_SMPLOCK != 0 */
#define sig_smplock_set(con)              con
#define sig_smplock_clr(con)              con
#define sig_smplock_tst(con)              0
#define sig_smplock_cpy(to, from)         to
#define sig_smplock_tryacquire_nopr(self) 1
#define sig_smplock_acquire_nopr(self)    (void)0
#define sig_smplock_release_nopr(self)    (void)0
#endif /* SIG_CONTROL_SMPLOCK == 0 */

#define sig_smplock_acquire(self) preemption_acquire_smp(sig_smplock_tryacquire_nopr(self))
#define sig_smplock_release(self) preemption_release_smp(sig_smplock_release_nopr(self))


#ifdef TASK_CONNECTION_STAT_FLOCK
#define TASK_CONNECTION_STAT_FLOCK_OPT TASK_CONNECTION_STAT_FLOCK
#else /* TASK_CONNECTION_STAT_FLOCK */
#define TASK_CONNECTION_STAT_FLOCK_OPT 0
#endif /* !TASK_CONNECTION_STAT_FLOCK */


/* Connect the calling thread to a given signal.
 * @throw: E_BADALLOC: Insufficient  memory  (only  when there  are  at least
 *                     `CONFIG_TASK_STATIC_CONNECTIONS' connections already). */
PUBLIC NONNULL((1)) void FCALL
task_connect(struct sig *__restrict target) THROWS(E_BADALLOC) {
	struct task_connection *con, *next;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;
	assert(IS_ALIGNED((uintptr_t)cons, TASK_CONNECTION_STAT_FMASK + 1));

	/* When a signal was already delivered, `task_connect()' becomes a no-op */
	if unlikely(ATOMIC_READ(cons->tcs_dlvr) != NULL)
		return;

	/* Allocate a new connection for `cons' */
	con = task_connection_alloc(cons);
	assert(!sig_smplock_tst(con));

	/* Fill in the new connection. */
	con->tc_sig     = target;
	con->tc_connext = cons->tcs_con;
	cons->tcs_con   = con;
	con->tc_cons    = cons;

	/* Now insert the connection onto the stack used by `target'
	 * NOTE: `sig_send()' will always  traverse the chain  to the  last
	 *       thread, meaning that we can (and have to) insert ourselves
	 *       at the front of the chain.
	 * Also note that inserting a new connection can be done without
	 * having  to tinker with the signal's SMP-lock, so this part is
	 * actually surprisingly simple. */
	do {
		next = ATOMIC_READ(target->s_con);
		con->tc_signext = sig_smplock_clr(next);
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(target->s_con, next,
	                             sig_smplock_cpy(con, next)));
}


/* Exactly the same as `task_connect()', however must be used when the connection
 * is  made for a poll-based operation that only wishes to wait for some event to
 * be  triggered, but does not wish to act upon this event by acquiring some kind
 * of lock with the intend to release  it eventually, where the act of  releasing
 * said lock includes a call to `sig_send()'.
 *
 * This connect() function is  only required for signals  that may be delivered  via
 * `sig_send()',  meaning that only a single thread  would be informed of the signal
 * event having taken  place. If  in this scenario,  the recipient  thread (i.e  the
 * thread that called  `task_connect()') then  decides not  to act  upon the  signal
 * in question, but rather to do something else, the original intent of `sig_send()'
 * will become lost, that intent  being for some (single)  thread to try to  acquire
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
PUBLIC NONNULL((1)) void FCALL
task_connect_for_poll(struct sig *__restrict target) THROWS(E_BADALLOC) {
	struct task_connection *con, *next;
	struct task_connections *cons;
	cons = THIS_CONNECTIONS;
	assert(IS_ALIGNED((uintptr_t)cons, TASK_CONNECTION_STAT_FMASK + 1));

	/* When a signal was already delivered, `task_connect()' becomes a no-op */
	if unlikely(ATOMIC_READ(cons->tcs_dlvr) != NULL)
		return;

	/* Allocate a new connection for `cons' */
	con = task_connection_alloc(cons);
	assert(!sig_smplock_tst(con));

	/* Fill in the new connection. */
	con->tc_sig     = target;
	con->tc_connext = cons->tcs_con;
	cons->tcs_con   = con;
	con->tc_cons    = (struct task_connections *)((uintptr_t)cons | TASK_CONNECTION_STAT_FPOLL);

	/* Now insert the connection onto the stack used by `target'
	 * NOTE: `sig_send()' will always  traverse the chain  to the  last
	 *       thread, meaning that we can (and have to) insert ourselves
	 *       at the front of the chain.
	 * Also note that inserting a new connection can be done without
	 * having  to tinker with the signal's SMP-lock, so this part is
	 * actually surprisingly simple. */
	do {
		next = ATOMIC_READ(target->s_con);
		con->tc_signext = sig_smplock_clr(next);
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(target->s_con, next,
	                             sig_smplock_cpy(con, next)));
}

/* Remove `con' from the linked list of active connections of `self'. */
LOCAL NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_unlink_from_sig)(struct sig *__restrict self,
                                               struct task_connection *__restrict con) {
	struct task_connection *chain;
again:
	assert(!sig_smplock_tst(con->tc_signext));
	assert(!con->tc_signext || ADDR_ISKERN(con->tc_signext));
	chain = ATOMIC_READ(self->s_con);
	if (sig_smplock_clr(chain) == con) {
		/* The first entry already is the connection we're trying to unlink!
		 * In this case, we must use an atomic operation, since other thread
		 * or CPUs may have added more connections since the the read above. */
		if (!ATOMIC_CMPXCH_WEAK(self->s_con, chain,
		                        /* Keep the SMP-lock bit set! */
		                        sig_smplock_set(con->tc_signext)))
			goto again;
	} else {
		struct task_connection **pchain;

		/* Since the caller has acquired the SMP-lock of `self' for us,
		 * we  are  able to  access  all of  the  attached connections! */
		chain  = sig_smplock_clr(chain);
		pchain = &chain->tc_signext;
		assert(chain->tc_sig == self);
		for (;;) {
			chain = *pchain;
			assert(!sig_smplock_tst(chain));
			assert(chain && ADDR_ISKERN(chain));
			assert(chain->tc_sig == self);
			if (chain == con)
				break; /* Found the entry! */
			pchain = &chain->tc_signext;
		}

		/* Unlink the element. */
		*pchain = chain->tc_signext;
	}
	DBG_memset(&con->tc_signext, 0xcc, sizeof(con->tc_signext));
}


/* Same as `task_connection_unlink_from_sig()', but also release the SMP-lock. The  caller
 * must then release the preemption lock through use of `sig_smp_lock_release_nosmp(self)' */
#if SIG_CONTROL_SMPLOCK == 0
#define TASK_CONNECTION_UNLINK_FROM_SIG_AND_UNLOCK_IS_TASK_CONNECTION_UNLINK_FROM_SIG 1
#define task_connection_unlink_from_sig_and_unlock(self, con) \
	task_connection_unlink_from_sig(self, con)
#else /* SIG_CONTROL_SMPLOCK == 0 */
LOCAL NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL task_connection_unlink_from_sig_and_unlock)(struct sig *__restrict self,
                                                          struct task_connection *__restrict con) {
	struct task_connection *chain;
again:
	assert(!sig_smplock_tst(con->tc_signext));
	assert(!con->tc_signext || ADDR_ISKERN(con->tc_signext));
	chain = ATOMIC_READ(self->s_con);
	if (sig_smplock_clr(chain) == con) {
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
		 * we  are  able to  access  all of  the  attached connections! */
		chain  = sig_smplock_clr(chain);
		pchain = &chain->tc_signext;
		assert(chain->tc_sig == self);
		for (;;) {
			chain = *pchain;
			assert(!sig_smplock_tst(chain));
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
		ATOMIC_AND(self->s_ctl, ~SIG_CONTROL_SMPLOCK);
	}
	DBG_memset(&con->tc_signext, 0xcc, sizeof(con->tc_signext));
}
#endif /* SIG_CONTROL_SMPLOCK != 0 */

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((2)) bool
NOTHROW(FCALL is_connection_in_chain)(struct task_connection *chain,
                                      struct task_connection *con) {
	for (; chain; chain = chain->tc_signext) {
		if (chain == con)
			return true;
	}
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL destroy_tasks)(struct task *destroy_later) {
	while (destroy_later) {
		struct task *next;
		next = sig_destroylater_next(destroy_later);
		destroy(destroy_later);
		destroy_later = next;
	}
}


struct sig_post_completion {
	struct sig_post_completion     *spc_next; /* [0..1] Next post-completion descriptor. */
	sig_postcompletion_t            spc_cb;   /* [1..1] Post-completion callback to-be invoked. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, spc_buf); /* Buffer to-be passed to `spc_cb' */
};

#define sig_post_completion_alloc(bufsize) \
	((struct sig_post_completion *)alloca(offsetof(struct sig_post_completion, spc_buf) + (bufsize)))

/* @param: struct sig_post_completion   **ppost_completion_chain: ...
 * @param: struct sig_completion         *sc:                     ...
 * @param: struct sig_completion_context *context:                ... */
#define invoke_sig_completion(ppost_completion_chain, sc, context) \
	do {                                                           \
		size_t _pc_reqlen;                                         \
		(context)->scc_post = NULL;                                \
		_pc_reqlen = (*(sc)->sc_cb)(sc, context, NULL, 0);         \
		if (_pc_reqlen != 0 || (context)->scc_post != NULL) {      \
			struct sig_post_completion *_pc_ent;                   \
			for (;;) {                                             \
				size_t _pc_newlen;                                 \
				_pc_ent = sig_post_completion_alloc(_pc_reqlen);   \
				_pc_newlen = (*(sc)->sc_cb)(sc, context,           \
				                            _pc_ent->spc_buf,      \
				                            _pc_reqlen);           \
				if unlikely(_pc_newlen > _pc_reqlen) {             \
					_pc_reqlen = _pc_newlen;                       \
					continue;                                      \
				}                                                  \
				if unlikely((context)->scc_post == NULL)           \
					break;                                         \
				/* Finish fill in `_pc_ent' and enqueue it. */     \
				_pc_ent->spc_cb   = (context)->scc_post;           \
				_pc_ent->spc_next = *(ppost_completion_chain);     \
				*(ppost_completion_chain) = _pc_ent;               \
				break;                                             \
			}                                                      \
		}                                                          \
	}	__WHILE0




/* Trigger phase #2 for pending signal-completion functions.
 * NOTE: During this, the completion callback will clear the
 *       SMP  lock  bit  of its  own  completion controller. */
#define sig_run_phase_2(chain, context)                \
	do {                                               \
		for (; chain; chain = chain->spc_next)         \
			(*chain->spc_cb)(context, chain->spc_buf); \
	}	__WHILE0



#ifndef CONFIG_NO_SMP
#define sig_completion_unlock(self) ATOMIC_AND((self)->tc_stat, ~TASK_CONNECTION_STAT_FLOCK)
LOCAL NOBLOCK void
NOTHROW(FCALL sig_unlock_pending)(struct sig_completion *sc_pending) {
	while (sc_pending) {
		struct sig_completion *next;
		next = (struct sig_completion *)sc_pending->tc_connext;
		sig_completion_unlock(sc_pending);
		sc_pending = next;
	}
}
#else /* !CONFIG_NO_SMP */
#define sig_completion_unlock(self) (void)0
#define sig_unlock_pending(chain)   (void)0
#endif /* CONFIG_NO_SMP */


/* Internal, extended signal broadcast function:
 *   #1: Perform a broadcast, alongside a number of optional, additional actions
 *   #2: Release all internal SMP-locks
 *   #3: Invoke `cleanup' (if non-NULL)
 *   #4: Restore the preemption behavior according to `was'
 *   #5: Destroy all  threads  who's  reference  counters  dropped to  0  in  the  mean  time
 *   #6: Invoke phase-2 completion callbacks, as have been registered by completion functions
 *   #7: Return the # of non-polling connections to which the signal was delivered
 * @param: self:            [1..1] The signal to broadcast
 * @param: sender:          [1..1] The sending signal (s.a. `sig_altbroadcast()')
 * @param: caller:          [1..1] The sending thread (s.a. `sig_broadcast_as()')
 * @param: sc_pending:      [0..1] When non-NULL, invoke this completion function,
 *                                 and  remember  it   as  having  been   invoked.
 * @param: destroy_later:   [0..1] A chain of threads that must be destroyed during step #5
 *                                 This chain  uses  `sig_destroylater_next()'  for  links.
 * @param: cleanup:         [0..1] When non-NULL, invoke this callback during step #3
 * @param: phase_one_state:        The state  that must  be written  to sig_completion  descriptors
 *                                 prior to invocation of their phase-1 callback. Should be one of:
 *                                  - TASK_CONNECTION_STAT_BROADCAST | TASK_CONNECTION_STAT_FLOCK_OPT | TASK_CONNECTION_STAT_FFINI
 *                                  - TASK_CONNECTION_STAT_BROADCAST | TASK_CONNECTION_STAT_FLOCK_OPT
 *                                 When   `TASK_CONNECTION_STAT_FFINI'   is   set,  this   will   prevent  the
 *                                 completion function from repriming itself (s.a. `sig_broadcast_for_fini()')
 * @param: was:                    The preemption-enabled state to restore during step #4
 * @return: * :                    The # of (additional, non-poll) connections that received the signal.
 *                                 Does  not   include  `sc_pending'   when   that  one   is   non-NULL. */
PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL sig_intern_broadcast)(struct sig *self,
                                    struct sig *sender,
                                    struct task *__restrict caller,
                                    struct sig_completion *sc_pending,
                                    struct task *destroy_later,
                                    struct sig_cleanup_callback *cleanup,
                                    uintptr_t phase_one_state,
                                    preemption_flag_t was) {
#ifndef CONFIG_NO_SMP
	uintptr_t ctl;
#endif /* !CONFIG_NO_SMP */
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	struct task_connections *target_cons;
	struct task_connection *receiver;
	struct task_connection *con;
	size_t result = 0;

	/* Signal completion callback. */
	context.scc_sender = sender;
	context.scc_caller = caller;
	if (sc_pending) {
		ATOMIC_WRITE(sc_pending->tc_stat, phase_one_state);
		assert(sc_pending->tc_sig == self);
		invoke_sig_completion(&phase2, sc_pending, &context);
		sc_pending->tc_connext = NULL;
	}
again:
#ifdef CONFIG_NO_SMP
	con = ATOMIC_READ(self->s_con);
#else /* CONFIG_NO_SMP */
	ctl = ATOMIC_READ(self->s_ctl);
	con = sig_smplock_clr(ctl);
#endif /* !CONFIG_NO_SMP */
	if (!con) {
no_cons:
		/* No one else here! (and nothing for us to do...) */
#if SIG_CONTROL_SMPLOCK != 0
		if (!ATOMIC_CMPXCH_WEAK(self->s_ctl, ctl, (uintptr_t)con))
			goto again;
#endif /* SIG_CONTROL_SMPLOCK != 0 */

		/* Trigger phase #2 for pending signal-completion functions.
		 * NOTE: During this, the completion callback will clear the
		 *       SMP  lock  bit  of its  own  completion controller. */
		sig_unlock_pending(sc_pending);
		if (cleanup)
			(*cleanup->scc_cb)(cleanup);
		preemption_pop(&was);
		destroy_tasks(destroy_later);
		sig_run_phase_2(phase2, &context);
		return result;
	}
	if (!is_connection_in_chain(sc_pending, con)) {
		/* Use the first connection */
		receiver = con;
#ifndef CONFIG_NO_SMP
		assert(!sig_smplock_tst(receiver->tc_signext));
#endif /* !CONFIG_NO_SMP */

		/* Unlink `receiver' from the pending chain. */
#ifdef CONFIG_NO_SMP
		if (!ATOMIC_CMPXCH_WEAK(self->s_con, con, (uintptr_t)receiver->tc_signext))
			goto again;
#else /* CONFIG_NO_SMP */
		if (!ATOMIC_CMPXCH_WEAK(self->s_ctl, ctl, (uintptr_t)receiver->tc_signext))
			goto again;
#endif /* !CONFIG_NO_SMP */
	} else {
		/* Find another receiver. */
		struct task_connection **preceiver;
		preceiver = &con->tc_signext;
		for (;;) {
			receiver = *preceiver;
			if (!receiver)
				goto no_cons;
			if (!is_connection_in_chain(sc_pending, receiver))
				break;
			preceiver = &receiver->tc_signext;
		}
		/* Unlink the receiver. */
		*preceiver = receiver->tc_signext;
	}
#ifndef CONFIG_NO_SMP
again_read_target_cons:
	target_cons = ATOMIC_READ(receiver->tc_cons);

	/* NOTE: Waiting until we can lock the connection here is allowed, since
	 *       you're allowed to  (and required to)  acquire connection  locks
	 *       without having to release the associated signal-lock.
	 * Doing  this doesn't result  in a race condition,  since the other end
	 * of this syncing mechanism (which is `task_disconnect()') will release
	 * its initial connection-lock if it  fails to acquire the signal  lock,
	 * which it will because we're already holding that one! */
	while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
		task_pause();
		target_cons = ATOMIC_READ(receiver->tc_cons);
	}

	/* Mark the receiver for broadcast, and acquire a lock to it. */
	if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
	                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
	                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
		goto again_read_target_cons;
#else /* !CONFIG_NO_SMP */
	target_cons = ATOMIC_XCH(receiver->tc_cons,
	                         (struct task_connections *)TASK_CONNECTION_STAT_BROADCAST);
#endif /* CONFIG_NO_SMP */

	if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
		struct sig_completion *sc;
		if (TASK_CONNECTION_STAT_ISDONE(target_cons))
			goto again;
		sc = (struct sig_completion *)receiver;
		ATOMIC_WRITE(sc->tc_stat, phase_one_state);

		/* Signal completion callback. */
		invoke_sig_completion(&phase2, sc, &context);

		/* Enqueue `sc' for unlock before phase #2. */
		sc->tc_connext = sc_pending;
		sc_pending     = sc;
	} else {
		target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);

		/* Try  to  set our  signal as  the  one delivered  to `target_cons'.
		 * If  that part fails, change signal state to BROADCAST (even though
		 * that's not entirely correct), so we can get rid of the connection. */
		if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender)) {
			/* Unlink the signal, and mark it as broadcast. */
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
		} else {
			REF struct task *thread;
			/* Unlock the signal, and wake-up the thread attached to the connection */
			thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			if likely(thread) {
				task_wake_as(thread, caller);
				assert(thread->t_refcnt >= 1);
				if unlikely(ATOMIC_FETCHDEC(thread->t_refcnt) == 1) {
					sig_destroylater_next(thread) = destroy_later;
					destroy_later                 = thread;
				}
			}
		}
	}
	goto again;
}

PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2, 3)) bool
NOTHROW(FCALL sig_intern_send)(struct sig *self,
                               struct sig *sender,
                               struct task *__restrict caller,
                               struct sig_completion *sc_pending,
                               struct task *destroy_later,
                               struct sig_cleanup_callback *cleanup,
                               preemption_flag_t was) {
	bool result;
#ifndef CONFIG_NO_SMP
	uintptr_t ctl;
#endif /* !CONFIG_NO_SMP */
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	struct task_connections *target_cons;
	struct task_connection *receiver;
	struct task_connection *con;
	context.scc_sender = sender;
	context.scc_caller = caller;

	/* Signal completion callback. */
	if (sc_pending) {
		invoke_sig_completion(&phase2, sc_pending, &context);
		sc_pending->tc_connext = NULL;
	}
again:
#ifdef CONFIG_NO_SMP
	con = ATOMIC_READ(self->s_con);
#else /* CONFIG_NO_SMP */
	ctl = ATOMIC_READ(self->s_ctl);
	con = sig_smplock_clr(ctl);
#endif /* !CONFIG_NO_SMP */
	if unlikely(!con) {
		/* No one else here! (and nothing for us to do...)
		 * This  is an  undefined situation,  since the  original call to
		 * `sig_send()' that caused the signal which we ended up ignoring
		 * to  be delivered returned `true', even though now, in the end,
		 * no one actually ended up getting the signal... */
#if SIG_CONTROL_SMPLOCK != 0
		if (!ATOMIC_CMPXCH_WEAK(self->s_ctl, ctl, (uintptr_t)con))
			goto again;
#endif /* SIG_CONTROL_SMPLOCK != 0 */

		/* Trigger phase #2 for pending signal-completion functions.
		 * NOTE: During this, the completion callback will clear the
		 *       SMP  lock  bit  of its  own  completion controller. */
		result = false;
		goto done;
	}

	/* Find a suitable candidate:
	 *    During send:
	 *       #1: Use the last-in-chain, non-poll connection
	 *       #2: Broadcast all poll connections (but stop if
	 *           a non-poll connection shows up before we're
	 *           down)
	 *       #3: If no non-poll connection could be found,
	 *           return `false' */
	receiver = con;
	if (!receiver->tc_signext) {
		/* Special case: Only one connection to choose from... */
	} else {
		struct task_connection *iter;
		iter = receiver;
		if (TASK_CONNECTION_STAT_ISPOLL(receiver->tc_stat))
			receiver = NULL;

		/* Find the last non-poll connection. */
		do {
			if (!TASK_CONNECTION_STAT_ISPOLL(iter->tc_stat))
				receiver = iter;
		} while ((iter = iter->tc_signext) != NULL);
		if (!receiver) {
			/* No non-poll connections found.
			 * Just use the last connection in-chain. */
			receiver = sig_smplock_clr(con);
			while (receiver->tc_signext)
				receiver = receiver->tc_signext;
		}
	}
again_read_target_cons:
	target_cons = ATOMIC_READ(receiver->tc_cons);

#ifndef CONFIG_NO_SMP
	/* NOTE: Waiting until we can lock the connection here is allowed, since
	 *       you're allowed to  (and required to)  acquire connection  locks
	 *       without having to release the associated signal-lock.
	 * Doing  this doesn't result  in a race condition,  since the other end
	 * of this syncing mechanism (which is `task_disconnect()') will release
	 * its initial connection-lock if it  fails to acquire the signal  lock,
	 * which it will because we're already holding that one! */
	while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
		task_pause();
		target_cons = ATOMIC_READ(receiver->tc_cons);
	}
#endif /* !CONFIG_NO_SMP */
	if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
		struct sig_completion *sc;
		if unlikely(TASK_CONNECTION_STAT_ISDONE(target_cons)) {
			/* The target is already dead. (change it to broadcast) */
			if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
			                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
			                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
				goto again_read_target_cons;
			task_connection_unlink_from_sig(self, receiver);
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
			goto again;
		}

		/* Signal completion callback. */
		if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again_read_target_cons;
		task_connection_unlink_from_sig(self, receiver);
		sc = (struct sig_completion *)receiver;

		/* Trigger phase #1 */
		invoke_sig_completion(&phase2, sc, &context);
		if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
			/* Enqueue the completion function so we don't re-trigger it. */
			sc->tc_signext = sc_pending;
			sc_pending     = sc;

			/* Search for more connections (preferably one that isn't poll-based) */
			goto again;
		}

		/* Unlock the signal. */
		sig_smplock_release_nopr(self);

		/* Instead of enqueuing `sc' to-be unlocked later, do so immediately. */
		sig_completion_unlock(sc);
		goto success;
	}

	/* Check if the selected receiver is poll-based */
	if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
		REF struct task *thread;
		/* Special case: poll-based connections don't (really) count.
		 * Instead, those get marked for broadcast. */
		if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again_read_target_cons;
		task_connection_unlink_from_sig(self, receiver);
		target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
		thread = NULL;

		/* Set the delivered signal, and capture
		 * the thread  thread, if  there is  one */
		if (ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender))
			thread = xincref(ATOMIC_READ(target_cons->tcs_thread));

		/* Unlock the connection. */
		ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
		if (thread) {
			task_wake_as(thread, caller);

			/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
			assert(thread->t_refcnt >= 1);
			if unlikely(ATOMIC_FETCHDEC(thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = destroy_later;
				destroy_later                 = thread;
			}
		}
		goto again;
	}

	/* Mark the receiver as sent, and acquire a lock to it. */
	if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
	                        (struct task_connections *)(TASK_CONNECTION_STAT_SENT |
	                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
		goto again_read_target_cons;

	/* Set the signal sender as being delivered for the target connection set. */
	if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender)) {
		/* Unlink the signal, and mark it as broadcast. */
		task_connection_unlink_from_sig(self, receiver);
		ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
		goto again;
	}

	/* The simple case:  We managed to  deliver the  signal,
	 * and now we must wake-up the connected thread (if any) */
	{
		REF struct task *thread;
		thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
#ifndef CONFIG_NO_SMP
		ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_SENT);
#endif /* !CONFIG_NO_SMP */
		sig_smplock_release_nopr(self);

		/* Wake-up the thread. */
		if likely(thread) {
			task_wake_as(thread, caller);

			/* Only destroy dead threads _after_ we've released the SMP-lock to `self' */
			assert(thread->t_refcnt >= 1);
			if unlikely(ATOMIC_FETCHDEC(thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = destroy_later;
				destroy_later                 = thread;
			}
		}
	}
success:
	result = true;
done:

	/* Trigger phase #2 for all of the pending completion function. */
	sig_unlock_pending(sc_pending);
	if (cleanup)
		(*cleanup->scc_cb)(cleanup);
	preemption_pop(&was);
	destroy_tasks(destroy_later);
	sig_run_phase_2(phase2, &context);
	return result;
}


PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2, 3, 4)) void
NOTHROW(FCALL sig_completion_runsingle)(struct sig *self,
                                        struct sig_completion *__restrict sc,
                                        struct task *__restrict caller,
                                        struct sig *sender,
                                        struct sig_cleanup_callback *cleanup,
                                        preemption_flag_t was) {
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	(void)self;
	context.scc_sender = sender;
	context.scc_caller = caller;

	/* Trigger phase #1 */
	invoke_sig_completion(&phase2, sc, &context);

	/* Release locks. */
	sig_completion_unlock(sc);
	sig_smplock_release_nopr(self);
	if (cleanup)
		(*cleanup->scc_cb)(cleanup);
	preemption_pop(&was);

	/* Run phase #2 callback. */
	sig_run_phase_2(phase2, &context);
}



/* Try to send the signal to a single, other thread, for the purpose
 * of  forwarding.  Additionally,  release  the  SMP-lock  of `self' */
PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE NONNULL((1, 2)) bool
NOTHROW(FCALL sig_sendone_for_forwarding_and_unlock)(struct sig *self,
                                                     struct sig *sender,
                                                     preemption_flag_t was) {
	bool result = false;
	bool is_broadcasting_poll = false;
#ifndef CONFIG_NO_SMP
	uintptr_t ctl;
#endif /* !CONFIG_NO_SMP */
	struct sig_completion *sc_pending = NULL;
	struct task_connections *target_cons;
	struct task_connection *receiver;
	struct task_connection *con;
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	REF struct task *destroy_later = NULL;
again:
#ifdef CONFIG_NO_SMP
	con = ATOMIC_READ(self->s_con);
#else /* CONFIG_NO_SMP */
	ctl = ATOMIC_READ(self->s_ctl);
	con = sig_smplock_clr(ctl);
#endif /* !CONFIG_NO_SMP */
	if unlikely(!con) {
no_cons:
		/* No one else here! (and nothing for us to do...)
		 * This  is an  undefined situation,  since the  original call to
		 * `sig_send()' that caused the signal which we ended up ignoring
		 * to  be delivered returned `true', even though now, in the end,
		 * no one actually ended up getting the signal... */
#if SIG_CONTROL_SMPLOCK != 0
		con = sig_smplock_clr(ctl);
		if (!ATOMIC_CMPXCH_WEAK(self->s_ctl, ctl, (uintptr_t)con))
			goto again;
#endif /* SIG_CONTROL_SMPLOCK != 0 */
		result = false;
		preemption_pop(&was);
		goto done;
	}

	/* Non-broadcast signals are sent to the oldest connection of  `self'.
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
		if (!TASK_CONNECTION_STAT_ISDONE(status)) {
			if (is_broadcasting_poll || !TASK_CONNECTION_STAT_ISPOLL(status)) {
				/* Make sure that  `con' isn't a  phase-2-pending completion  callback.
				 * If it is, then the callback of `con' used `sig_completion_reprime()'
				 * during phase-1 in order to re-queue itself. */
				if (!is_connection_in_chain(sc_pending, con))
					receiver = con; /* This connection is still in alive. */
			}
		}
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

	/* Try to switch the connection from `!TASK_CONNECTION_STAT_ISDONE'
	 * to `TASK_CONNECTION_STAT_SENT'. */
	target_cons = ATOMIC_READ(receiver->tc_cons);

#ifndef CONFIG_NO_SMP
	/* NOTE: Waiting until we can lock the connection here is allowed, since
	 *       you're allowed to  (and required to)  acquire connection  locks
	 *       without having to release the associated signal-lock.
	 * Doing  this doesn't result  in a race condition,  since the other end
	 * of this syncing mechanism (which is `task_disconnect()') will release
	 * its initial connection-lock if it  fails to acquire the signal  lock,
	 * which it will because we're already holding that one! */
	while (unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK)) {
		task_pause();
		target_cons = ATOMIC_READ(receiver->tc_cons);
	}
#endif /* !CONFIG_NO_SMP */
	if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
		struct sig_completion *sc;
		if unlikely(TASK_CONNECTION_STAT_ISDONE(target_cons))
			goto again;
		sc = (struct sig_completion *)receiver;
		if (!ATOMIC_CMPXCH_WEAK(sc->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_BROADCAST |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again;

		/* Unlink `sc' from the signal. */
		task_connection_unlink_from_sig(self, receiver);

		/* Signal completion callback. */
		context.scc_sender = sender;
		context.scc_caller = THIS_TASK;
		invoke_sig_completion(&phase2, sc, &context);

		/* Enqueue `sc' for unlock before phase #2. */
		sc->tc_connext = sc_pending;
		sc_pending     = sc;
		if unlikely(TASK_CONNECTION_STAT_ISPOLL(target_cons))
			goto again; /* Deal with poll-based connections. */
	} else {
		struct task *thread;
		if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
		                        (struct task_connections *)(TASK_CONNECTION_STAT_SENT |
		                                                    TASK_CONNECTION_STAT_FLOCK_OPT)))
			goto again;
		if unlikely(TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
			/* Deal with poll-based connections. */
			bool did_deliver;
			target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
			did_deliver = ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender);
			task_connection_unlink_from_sig(self, receiver);
			if (did_deliver) {
				thread = ATOMIC_READ(target_cons->tcs_thread);
				if likely(thread)
					task_wake(thread);
			}
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			goto again;
		}

		/* Try  to  set our  signal as  the  one delivered  to `target_cons'.
		 * If  that part fails, change signal state to BROADCAST (even though
		 * that's not entirely correct), so we can get rid of the connection. */
		if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender)) {
			/* Unlink the signal, and mark it as broadcast. */
			task_connection_unlink_from_sig(self, receiver);
			ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
			goto again;
		}

		/* Unlock the signal, and wake-up the thread attached to the connection */
		thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
		ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_SENT);
		sig_smplock_release_nopr(self);
		preemption_pop(&was);
		if likely(thread) {
			task_wake(thread);
			assert(thread->t_refcnt >= 1);
			if unlikely(ATOMIC_FETCHDEC(thread->t_refcnt) == 1) {
				sig_destroylater_next(thread) = destroy_later;
				destroy_later                 = thread;
			}
		}
	}
	result = true;
done:

	/* Trigger phase #2 for pending signal-completion functions.
	 * NOTE: During this, the completion callback will clear the
	 *       SMP  lock  bit  of its  own  completion controller. */
	sig_unlock_pending(sc_pending);
	preemption_pop(&was);

	/* Invoke phase-2 callbacks. */
	sig_run_phase_2(phase2, &context);

	/* Destroy pending threads. */
	destroy_tasks(destroy_later);
	return result;
}




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
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) bool
NOTHROW(KCALL sig_completion_reprime)(struct sig_completion *__restrict self,
                                      bool for_poll) {
	struct task_connection *next;
	struct sig *signal = self->tc_sig;

	/* At this point, we're allowed to assume all of the following: */
	assert(!preemption_ison());
#ifndef CONFIG_NO_SMP
	assert(signal->s_ctl & SIG_CONTROL_SMPLOCK);
	assert(self->tc_stat & TASK_CONNECTION_STAT_FLOCK);
#endif /* !CONFIG_NO_SMP */

	/* If the signal was sent for the purpose of finalization, then don't
	 * allow completion callback re-priming, since we're supposed to take
	 * care of all connections going away. */
	if unlikely(self->tc_stat & TASK_CONNECTION_STAT_FFINI)
		return false;

	/* Re-write the status of `self' to match the request. */
	ATOMIC_WRITE(self->tc_stat,
	             for_poll ? TASK_CONNECTION_STAT_FLOCK_OPT | TASK_CONNECTION_STAT_COMPLETION_FOR_POLL
	                      : TASK_CONNECTION_STAT_FLOCK_OPT | TASK_CONNECTION_STAT_COMPLETION);

	/* Now we must insert `self' into the chain of `signal' */
	do {
		next = ATOMIC_READ(signal->s_con);
#ifndef CONFIG_NO_SMP
		assert(sig_smplock_tst(next));
#endif /* !CONFIG_NO_SMP */
		self->tc_signext = sig_smplock_clr(next);
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(signal->s_con, next,
	                             sig_smplock_set(self)));
	return true;
}

/* Connect the given signal completion controller to the specified signal.
 * The caller must  ensure that `completion'  hasn't been connected,  yet. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion)(struct sig *__restrict self,
                                      struct sig_completion *__restrict completion) {
	struct task_connection *next;

	/* Re-write the status of `self' to match the request. */
	completion->tc_stat = TASK_CONNECTION_STAT_COMPLETION;
	completion->tc_sig  = self;
	DBG_memset(&completion->tc_connext, 0xcc,
	           sizeof(completion->tc_connext));

	/* Now we must insert `completion' into the chain of `self' */
	do {
		next = ATOMIC_READ(self->s_con);
		completion->tc_signext = sig_smplock_clr(next);
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(self->s_con, next,
	                             sig_smplock_cpy(completion, next)));
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sig_connect_completion_for_poll)(struct sig *__restrict self,
                                               struct sig_completion *__restrict completion) {
	struct task_connection *next;

	/* Re-write the status of `self' to match the request. */
	completion->tc_stat = TASK_CONNECTION_STAT_COMPLETION_FOR_POLL;
	completion->tc_sig  = self;
	DBG_memset(&completion->tc_connext, 0xcc,
	           sizeof(completion->tc_connext));

	/* Now we must insert `completion' into the chain of `self' */
	do {
		next = ATOMIC_READ(self->s_con);
		completion->tc_signext = sig_smplock_clr(next);
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(self->s_con, next,
	                             sig_smplock_cpy(completion, next)));
}




LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_disconnect_connection)(struct task_connection *__restrict self,
                                          struct task_connections *__restrict cons,
                                          bool forward_sent_signals) {
	struct sig *signal;
	struct task_connection *signal_cons;
	preemption_flag_t was;
	uintptr_t status;
	signal = self->tc_sig;

	/* Acquire a lock to the connection. */
#ifdef CONFIG_NO_SMP
	preemption_pushoff(&was);
	status = ATOMIC_READ(self->tc_stat);
	if (TASK_CONNECTION_STAT_ISDEAD(status)) {
		preemption_pop(&was);
		goto done; /* Dead connection */
	}
	signal_cons = ATOMIC_READ(signal->s_con);
#else /* CONFIG_NO_SMP */
again:
	status = ATOMIC_READ(self->tc_stat);
	if (TASK_CONNECTION_STAT_ISDEAD(status))
		goto done; /* Dead connection */
	if unlikely(status & TASK_CONNECTION_STAT_FLOCK) {
		task_pause();
		goto again;
	}
	preemption_pushoff(&was);
	if (!ATOMIC_CMPXCH_WEAK(self->tc_stat, status,
	                        status | TASK_CONNECTION_STAT_FLOCK)) {
		preemption_pop(&was);
		goto again;
	}

	/* Now upgrade the lock to also include the associated signal. */
again_signal_cons:
	signal_cons = ATOMIC_READ(signal->s_con);
	if unlikely(sig_smplock_tst(signal_cons)) {
		ATOMIC_AND(self->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
		preemption_pop(&was);
		task_pause();
		goto again;
	}
	if (!ATOMIC_CMPXCH_WEAK(signal->s_con, signal_cons,
	                        sig_smplock_set(signal_cons)))
		goto again_signal_cons;
#endif /* !CONFIG_NO_SMP */

	/* At this point, we're holding all of the necessary locks, both
	 * to `self' and `signal'. With that in mind, remove `self' from
	 * the connection queue of `signal' */
	if likely(status != TASK_CONNECTION_STAT_SENT || !forward_sent_signals) {
		/* Unlink our connection, and unlock the signal. */
		task_connection_unlink_from_sig_and_unlock(signal, self);
		preemption_pop(&was);
	} else {
		/* Unlink our connection. */
		task_connection_unlink_from_sig(signal, self);

		/* Forward the signal. */
		if (!sig_sendone_for_forwarding_and_unlock(signal,
		                                           ATOMIC_READ(cons->tcs_dlvr),
		                                           was)) {
			/* At least log the fact that there has been a minor inconsistency... */
			printk(KERN_WARNING "[sig] Signal %p cannot be forwarded (no recipients)\n",
			       self);
		}
	}
done:
	DBG_memset(&self->tc_sig, 0xcc, sizeof(self->tc_sig));
}

/* NOTE: When  this  function returns,  the caller  can be  certain that  the callback
 *       of `self' is/won't be executed anymore, unless `self' is once again connected
 *       to some signal through use of `sig_connect_completion[_for_poll]()'
 * @return: true:  Completion function was disconnected before it could be  triggered,
 *                 or the last time the completion function was triggered, it made use
 *                 of `sig_completion_reprime()' to re-prime itself.
 * @return: false: Completion  function was already triggered, but not re-primed.
 *                 Alternatively, the signal completion function had already been
 *                 disconnected, or had never been connected to begin with. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sig_completion_disconnect)(struct sig_completion *__restrict self) {
	struct sig *signal;
	struct task_connection *signal_cons;
	preemption_flag_t was;
	uintptr_t status;
	signal = self->tc_sig;

	/* Acquire a lock to the connection. */
#ifdef CONFIG_NO_SMP
	preemption_pushoff(&was);
	status = ATOMIC_READ(self->tc_stat);
	if (TASK_CONNECTION_STAT_ISDONE(status)) {
		preemption_pop(&was);
		return false; /* Dead connection */
	}
	assert(status == TASK_CONNECTION_STAT_COMPLETION ||
	       status == TASK_CONNECTION_STAT_COMPLETION_FOR_POLL);
	signal_cons = ATOMIC_READ(signal->s_con);
#else /* CONFIG_NO_SMP */
again:
	status = ATOMIC_READ(self->tc_stat);
	if (TASK_CONNECTION_STAT_ISDONE(status))
		return false; /* Dead connection */
	if unlikely(status & TASK_CONNECTION_STAT_FLOCK) {
		task_pause();
		goto again;
	}
	assert(status == TASK_CONNECTION_STAT_COMPLETION ||
	       status == TASK_CONNECTION_STAT_COMPLETION_FOR_POLL);
	preemption_pushoff(&was);
	if (!ATOMIC_CMPXCH_WEAK(self->tc_stat, status,
	                        status | TASK_CONNECTION_STAT_FLOCK)) {
		preemption_pop(&was);
		goto again;
	}

	/* Now upgrade the lock to also include the associated signal. */
again_signal_cons:
	signal_cons = ATOMIC_READ(signal->s_con);
	if unlikely(sig_smplock_tst(signal_cons)) {
		ATOMIC_AND(self->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
		preemption_pop(&was);
		task_pause();
		goto again;
	}
	if (!ATOMIC_CMPXCH_WEAK(signal->s_con, signal_cons,
	                        sig_smplock_set(signal_cons)))
		goto again_signal_cons;
#endif /* !CONFIG_NO_SMP */

	/* At this point, we're holding all of the necessary locks, both
	 * to `self' and `signal'. With that in mind, remove `self' from
	 * the connection queue of `signal' */
	task_connection_unlink_from_sig_and_unlock(signal, self);
	preemption_pop(&was);
	DBG_memset(&self->tc_sig, 0xcc, sizeof(self->tc_sig));
	DBG_memset(&self->tc_connext, 0xcc, sizeof(self->tc_connext));
	DBG_memset(&self->tc_signext, 0xcc, sizeof(self->tc_signext));
	COMPILER_WRITE_BARRIER();
	self->tc_stat = TASK_CONNECTION_STAT_BROADCAST;
	return true;
}


/* Disconnect from a specific signal `target'
 * WARNING: If `target' was already  send to the calling  thread
 *          before it could  be disconnected  by this  function,
 *          the calling  thread will  continue  to remain  in  a
 *          signaled state, such  that the next  call to one  of
 *          the signal receive functions (e.g. `task_waitfor()')
 *          will not block.
 * @return: true:  Disconnected from `target'
 * @return: false: You weren't actually connected to `target' */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target) {
	struct task_connections *self;
	struct task_connection **p_con, *con;
	self = THIS_CONNECTIONS;
	for (p_con = &self->tcs_con; (con = *p_con) != NULL;
	     p_con = &con->tc_connext) {
		if (con->tc_sig != target)
			continue; /* Some other signal... */

		/* Disconnect */
		task_disconnect_connection(con, self, true);

		/* Unlink */
		*p_con = con->tc_connext;

		/* Free */
		task_connection_free(self, con);
		return true;
	}
	return false;
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

/* Disconnect from all connected signals.
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
 * `TASK_CONNECTION_STAT_SENT'-state, but rather return the  sender
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
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL task_wasconnected)(void) {
	struct task_connections *self;
	self = THIS_CONNECTIONS;

	/* Check if there are any active connections. */
	return self->tcs_con != NULL;
}

/* Check if the calling thread was connected to the given signal.
 * Always returns `false' when `target == NULL'. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL task_wasconnected_to)(struct sig const *target) {
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

/* Check if there is a signal that was delivered,
 * disconnecting all other  connected signals  if
 * this was the case.
 * @return: NULL: No signal is available.
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
PUBLIC NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_trywait)(void) {
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
 * This     includes     poll-based    connections. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sig_iswaiting)(struct sig *__restrict self) {
	bool result = false;
	struct task_connection *cons;

	/* Quick check: Are there any established connections? */
	cons = sig_smplock_clr(ATOMIC_READ(self->s_con));
	if (cons) {
		/* Acquire the SMP-lock for `self', so we can inspect
		 * the chain of established connections more closely. */
		sig_smplock_acquire(self);
		for (cons = sig_smplock_clr(ATOMIC_READ(self->s_con));
		     cons; cons = cons->tc_signext) {
			uintptr_t status = ATOMIC_READ(cons->tc_stat);
			if (!TASK_CONNECTION_STAT_ISDONE(status)) {
				/* Found an alive, normal connection! */
				result = true;
				break;
			}
		}
		sig_smplock_release(self);
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
	cons = sig_smplock_clr(ATOMIC_READ(self->s_con));
	if (cons) {
		/* Acquire the SMP-lock for `self', so we can inspect
		 * the chain of established connections more closely. */
		sig_smplock_acquire(self);
		for (cons = sig_smplock_clr(ATOMIC_READ(self->s_con));
		     cons; cons = cons->tc_signext) {
			uintptr_t status;
			status = ATOMIC_READ(cons->tc_stat);
			if (!TASK_CONNECTION_STAT_ISDONE(status))
				++result; /* Found an alive, normal connection! */
		}
		sig_smplock_release(self);
	}
	return result;
}



/************************************************************************/
/* SIGNAL MULTI-COMPLETION API                                          */
/************************************************************************/

/* Finalize a given signal multi-completion controller.
 * WARNING: This  function will _not_  disconnect any remaining signals.
 *          If active connections could possibly remain, it is up to the
 *          caller to call `sig_multicompletion_disconnectall()'  first! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_fini)(struct sig_multicompletion *__restrict self) {
	struct _sig_multicompletion_set *ext;

	/* Make sure that `self' isn't still connected. */
	assert(!sig_multicompletion_wasconnected(self));

	/* Free all extended connection sets. */
	ext = self->sm_set.sms_next;
	DBG_memset(self, 0xcc, sizeof(*self));
	while (ext) {
		struct _sig_multicompletion_set *next;
		next = ext->sms_next;
		kfree(ext);
		ext = next;
	}
}


/* Sever all (still-alive) connections that are active for `self'. Note that this  function
 * may not be called from inside of signal-completion-callbacks, or any other callback that
 * may  be executed in the context of holding an SMP-lock. (though you area allowed to call
 * this function from a `sig_postcompletion_t' callback) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sig_multicompletion_disconnectall)(struct sig_multicompletion *__restrict self) {
	struct _sig_multicompletion_set *set;
	set = &self->sm_set;
	do {
		unsigned int i;
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
#ifndef __OPTIMIZE_SIZE__
			if (set->sms_routes[i].tc_stat != TASK_CONNECTION_STAT_BROADCAST)
#endif /* !__OPTIMIZE_SIZE__ */
			{
				sig_completion_disconnect(&set->sms_routes[i]);
			}
		}
	} while ((set = set->sms_next) != NULL);
}

/* Check if the given signal multi-completion controller `self' was connected. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sig_multicompletion_wasconnected)(struct sig_multicompletion const *__restrict self) {
	struct _sig_multicompletion_set const *set;
	set = &self->sm_set;
	do {
		unsigned int i;
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
			if (sig_completion_wasconnected(&set->sms_routes[i]))
				return true;
		}
	} while ((set = set->sms_next) != NULL);
	return false;
}


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
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct sig_completion *FCALL
sig_multicompletion_alloc(struct sig_multicompletion *__restrict self,
                          sig_completion_t cb)
		THROWS(E_BADALLOC) {
	struct _sig_multicompletion_route *result;
	struct _sig_multicompletion_set *set;
	unsigned int i;
	set = &self->sm_set;
	do {
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
			result = &set->sms_routes[i];
			if (result->tc_stat == TASK_CONNECTION_STAT_BROADCAST)
				goto done; /* Unused completion entry. */
		}
	} while ((set = set->sms_next) != NULL);

	/* Must allocate a new set of completion descriptors.
	 * NOTE: These descriptors must be allocated as LOCKED, since they're made
	 *       use of  by code  that may  be running  with preemption  disabled. */
	set = (struct _sig_multicompletion_set *)kmalloc(sizeof(struct _sig_multicompletion_set),
	                                                 GFP_LOCKED | GFP_PREFLT);
	for (i = 0; i < lengthof(self->sm_set.sms_routes); ++i)
		set->sms_routes[i].tc_stat = TASK_CONNECTION_STAT_BROADCAST;

	/* Insert the set into the list of known sets. */
	set->sms_next         = self->sm_set.sms_next;
	self->sm_set.sms_next = set;

	/* Use the first descriptor from the newly allocated set. */
	result = &set->sms_routes[0];
done:
	result->mr_con = self;
	result->sc_cb  = cb;
	return result;
}

PUBLIC WUNUSED NONNULL((1)) struct sig_completion *
NOTHROW(FCALL sig_multicompletion_alloc_nx)(struct sig_multicompletion *__restrict self,
                                            sig_completion_t cb) {
	struct _sig_multicompletion_route *result;
	struct _sig_multicompletion_set *set;
	unsigned int i;
	set = &self->sm_set;
	do {
		for (i = 0; i < lengthof(set->sms_routes); ++i) {
			result = &set->sms_routes[i];
			if (result->tc_stat == TASK_CONNECTION_STAT_BROADCAST)
				goto done; /* Unused completion entry. */
		}
	} while ((set = set->sms_next) != NULL);

	/* Must allocate a new set of completion descriptors.
	 * NOTE: These descriptors must be allocated as LOCKED, since they're made
	 *       use of  by code  that may  be running  with preemption  disabled. */
	set = (struct _sig_multicompletion_set *)kmalloc_nx(sizeof(struct _sig_multicompletion_set),
	                                                    GFP_LOCKED | GFP_PREFLT);
	if unlikely(!set)
		return NULL; /* Allocation failed. */
	for (i = 0; i < lengthof(self->sm_set.sms_routes); ++i)
		set->sms_routes[i].tc_stat = TASK_CONNECTION_STAT_BROADCAST;

	/* Insert the set into the list of known sets. */
	set->sms_next         = self->sm_set.sms_next;
	self->sm_set.sms_next = set;

	/* Use the first descriptor from the newly allocated set. */
	result = &set->sms_routes[0];
done:
	result->mr_con = self;
	result->sc_cb  = cb;
	return result;
}

/* Allocate a completion descriptor from `completion' and connect it to `self' */
PUBLIC NOBLOCK NONNULL((1, 2, 3)) void FCALL
sig_connect_multicompletion(struct sig *__restrict self,
                            struct sig_multicompletion *__restrict completion,
                            sig_completion_t cb)
		THROWS(E_BADALLOC) {
	struct sig_completion *route;
	route = sig_multicompletion_alloc(completion, cb);
	sig_connect_completion(self, route);
}

/* No-except version of `sig_connect_multicompletion()'. Returns `false' if no
 * completion descriptor could be allocated from the pool of `completion', and
 * `true' if a completion descriptor  could be allocated and was  subsequently
 * connected. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL sig_connect_multicompletion_nx)(struct sig *__restrict self,
                                              struct sig_multicompletion *__restrict completion,
                                              sig_completion_t cb) {
	struct sig_completion *route;
	route = sig_multicompletion_alloc_nx(completion, cb);
	if unlikely(!route)
		return false;
	sig_connect_completion(self, route);
	return true;
}


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
PUBLIC NOBLOCK NONNULL((1)) void FCALL
sig_multicompletion_connect_from_task(struct sig_multicompletion *__restrict completion,
                                      sig_completion_t cb, bool for_poll)
		THROWS(E_BADALLOC) {
	struct task_connection *con;
	struct task_connections *cons;
	uintptr_t newroute_status;
	cons = THIS_CONNECTIONS;
#ifndef __OPTIMIZE_SIZE__
	/* Quick check: was one of the calling thread's signals already delivered? */
	if (cons->tcs_dlvr != NULL)
		return;
#endif /* !__OPTIMIZE_SIZE__ */
	newroute_status = for_poll ? TASK_CONNECTION_STAT_COMPLETION_FOR_POLL
	                           : TASK_CONNECTION_STAT_COMPLETION;
	for (con = cons->tcs_con; con; con = con->tc_connext) {
		struct sig_completion *route;
		struct task_connection *signext;
		struct sig *signal;
		preemption_flag_t was;
		route  = sig_multicompletion_alloc(completion, cb);
		signal = con->tc_sig;

		/* Initialize `route' as needed prior to a connection being made. */
		route->tc_stat = newroute_status;
		route->tc_sig  = signal;
		DBG_memset(&route->tc_connext, 0xcc, sizeof(route->tc_connext));

		/* This is where it gets complicated, because we must:
		 *    #1: Disable preemption
		 *    #2: Acquire the SMP-lock of `con', and make sure that  `con'
		 *        hasn't been delivered,  yet. This way  we know that  the
		 *        signal pointed to by `con->tc_sig' hasn't been destroyed
		 *        yet, either.
		 *    #3: While holding the  SMP-lock of `con',  insert our  new
		 *        connection `route' into the signal's connection queue.
		 *    #4: Release our SMP-lock on `con'
		 *    #5: Re-enable preemption (if it was enabled before)
		 *
		 * Note  that in order to append a connection onto the wait-queue
		 * of  some signal, one normally doesn't need to acquire any SMP-
		 * locks. In this case however, we still need to acquire the SMP-
		 * lock  of `con', with  which we can prevent  any other CPU from
		 * (fully) broadcasting the attached signal as part of finalizing
		 * that signal (~ala `sig_broadcast_for_fini()') */

		/* Step #1 */
		preemption_pushoff(&was);

		/* Step #2 */
#ifndef CONFIG_NO_SMP
		for (;;)
#endif /* !CONFIG_NO_SMP */
		{
			uintptr_t status;
			status = ATOMIC_READ(con->tc_stat);
			if (TASK_CONNECTION_STAT_ISSPEC(status)) {
				assertf(!TASK_CONNECTION_STAT_ISCOMP(status),
				        "This should be a task connection, so why does "
				        "its status indicate a completion function?\n"
				        "status = %#" PRIxPTR,
				        status);

				/* Connection is already dead.
				 * Abort everything and  make sure  that our  thread's
				 * delivered-connection field is non-NULL (since  that
				 * field may not have been set yet by whoever had sent
				 * the signal) */
				preemption_pop(&was);

				/* Mark  `route'  as  unused  (since  it  was  never  fully connected)
				 * This  must be  done to ensure  that `self' remains  in a consistent
				 * state in regards to finalization (or rather: disconnect in general) */
				route->tc_stat = TASK_CONNECTION_STAT_BROADCAST;

#ifdef CONFIG_NO_SMP
				assert(ATOMIC_READ(cons->tcs_dlvr) != NULL);
#else /* CONFIG_NO_SMP */

				/* If  the signal was  send by some  other CPU, our thread's
				 * delivered-signal field may not have become non-NULL, yet.
				 * In this case, simply pause until that happens. */
				while (ATOMIC_READ(cons->tcs_dlvr) == NULL)
					task_tryyield_or_pause();
#endif /* !CONFIG_NO_SMP */
				return;
			}

#ifndef CONFIG_NO_SMP
			/* Make sure that `con' isn't already locked. */
			if unlikely(status & TASK_CONNECTION_STAT_FLOCK) {
				/* Pausing w/ preemption may  do better than pausing  w/o
				 * As such, try to re-enable preemption while we do this. */
				preemption_pop(&was);
				task_tryyield_or_pause();
				preemption_pushoff(&was);
				continue;
			}

			/* Acquire a lock to `con' */
			if (ATOMIC_CMPXCH_WEAK(con->tc_stat,
			                       status,
			                       status | TASK_CONNECTION_STAT_FLOCK))
				break;
#endif /* !CONFIG_NO_SMP */
		}

		/* Step #3 (Do the actual job of inserting `route' into the signal) */
		do {
			signext = ATOMIC_READ(signal->s_con);
			route->tc_signext = sig_smplock_clr(signext);
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(signal->s_con, signext,
		                             sig_smplock_cpy(route, signext)));

#ifndef CONFIG_NO_SMP
		/* Step #4 */
		ATOMIC_AND(con->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
#endif /* !CONFIG_NO_SMP */

		/* Step #5 */
		preemption_pop(&was);
	}
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
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_broadcast(self);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_send(self))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}

PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altsendmany)(struct sig *self,
                               struct sig *sender,
                               size_t maxcount) {
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_altbroadcast(self, sender);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_altsend(self, sender))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}

PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_sendmany_nopr)(struct sig *__restrict self,
                                 size_t maxcount) {
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_broadcast_nopr(self);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_send_nopr(self))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}

PUBLIC NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altsendmany_nopr)(struct sig *self,
                                    struct sig *sender,
                                    size_t maxcount) {
	size_t result;
	if (maxcount == (size_t)-1) {
		result = sig_altbroadcast_nopr(self, sender);
	} else {
		result = 0;
		while (maxcount) {
			if (!sig_altsend_nopr(self, sender))
				break;
			--maxcount;
			++result;
		}
	}
	return result;
}




/* Send  a signal to the oldest (and preferably non-poll-based) connection of
 * `self' for which `selector'  returns non-NULL. Connections are  enumerated
 * twice from oldest to most recent, only including non-poll-based during the
 * first pass, and only including poll-based ones during the second pass.
 * @param: self:     The signal which should be sent.
 * @param: selector: A selector callback that can be used to select the
 *                   connection that should be sent.
 * @param: cookie:   An argument that should be passed to `selector'
 * @param: caller:   The (supposed) calling thread (s.a. `sig_broadcast_as()')
 * @param: cleanup:  When non-NULL, an optional cleanup callback (s.a. `sig_broadcast_cleanup_nopr()')
 * @param: run_cleanup_when_notarget: If true, also run `cleanup' when returning `SIG_SEND_SELECT_NOTARGET'
 * @return: * :      One of `SIG_SEND_SELECT_*' */
PUBLIC NOBLOCK NONNULL((1, 2, 4)) unsigned int
NOTHROW(FCALL sig_send_select_as)(struct sig *__restrict self,
                                  sig_send_selector_t selector, void *cookie,
                                  struct task *__restrict caller,
                                  struct sig_cleanup_callback *cleanup,
                                  bool run_cleanup_when_notarget) {
	preemption_flag_t was;
	struct sig *sender;
	struct task_connection *sig_con;
	struct task_connection *receiver;
	struct task_connection *last_ingored_connection;
	struct sig_select_context context;
	bool select_poll = false;
	context.ssc_signal    = self;
	context.ssc_flag      = SIG_SELECT_FLAG_NORMAL;
	context.ssc_wakeflags = TASK_WAKE_FNORMAL;
	context.ssc_caller    = caller;
	preemption_pushoff(&was);
#ifdef CONFIG_NO_SMP
	sig_con = ATOMIC_READ(self->s_con);
	if (!sig_con)
		goto done;
#else /* CONFIG_NO_SMP */
	for (;;) {
		sig_con = ATOMIC_READ(self->s_con);
		if (!sig_con)
			goto done;
		if unlikely((uintptr_t)sig_con & SIG_CONTROL_SMPLOCK) {
			preemption_pop(&was);
			task_tryyield_or_pause();
			preemption_pushoff(&was);
			continue;
		}
		if (ATOMIC_CMPXCH_WEAK(self->s_con, sig_con,
		                       sig_smplock_set(sig_con)))
			break;
	}
#endif /* !CONFIG_NO_SMP */

	/* Figure out which signal we should select. */
	last_ingored_connection = NULL;
again:
	for (;;) {
		struct task_connections *target_cons;
		for (receiver = sig_con;
		     receiver->tc_connext != last_ingored_connection;
		     receiver = receiver->tc_signext)
			;
#ifndef CONFIG_NO_SMP
again_read_cons:
#endif /* !CONFIG_NO_SMP */
		target_cons = ATOMIC_READ(receiver->tc_cons);
		if (!TASK_CONNECTION_STAT_ISDONE(target_cons) &&
		    (!!TASK_CONNECTION_STAT_ISPOLL(target_cons)) == select_poll) {

#ifndef CONFIG_NO_SMP
			/* NOTE: Waiting until we can lock the connection here is allowed, since
			 *       you're allowed to  (and required to)  acquire connection  locks
			 *       without having to release the associated signal-lock.
			 * Doing  this doesn't result  in a race condition,  since the other end
			 * of this syncing mechanism (which is `task_disconnect()') will release
			 * its initial connection-lock if it  fails to acquire the signal  lock,
			 * which it will because we're already holding that one! */
			if unlikely((uintptr_t)target_cons & TASK_CONNECTION_STAT_FLOCK) {
				task_pause();
				goto again_read_cons;
			}
			if (!ATOMIC_CMPXCH_WEAK(receiver->tc_cons, target_cons,
			                        (struct task_connections *)((uintptr_t)target_cons |
			                                                    TASK_CONNECTION_STAT_FLOCK)))
				goto again_read_cons;
#endif /* !CONFIG_NO_SMP */

			/* Figure out the exact details of this receiver. */
			if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
				/* Completion callback */
				context.ssc_type  = SIG_SELECT_TYPE_COMPLETION;
				context.ssc_compl = (struct sig_completion *)receiver;
			} else {
				/* Sleeping thread */
				struct task_connections *chain;
				context.ssc_type = SIG_SELECT_TYPE_THREAD;
				for (chain = TASK_CONNECTION_STAT_ASCONS(target_cons);;) {
					if (chain->tcs_thread) {
						context.ssc_thread = chain->tcs_thread;
						break;
					}
					if (!chain->tcs_prev) {
						/* Assume that `chain' is `this_root_connections' of the
						 * target  thread, which we  can use to reverse-engineer
						 * the actual thread */
						context.ssc_thread = (struct task *)((uintptr_t)chain -
						                                     (uintptr_t)&this_root_connections);
						break;
					}
					chain = chain->tcs_prev;
				}
			}

			/* Figure out if we want to send to this connection. */
			sender = (*selector)(cookie, &context);
			if (sender != NULL) {
				REF struct task *thread;
				if (TASK_CONNECTION_STAT_ISSPEC(target_cons)) {
					/* Invoke a completion function. */
					task_connection_unlink_from_sig(self, receiver);
					sig_completion_runsingle(self,
					                         (struct sig_completion *)receiver,
					                         context.ssc_caller, sender,
					                         cleanup, was);
					return SIG_SEND_SELECT_SUCCESS;
				}

				/* Send the signal to a normal thread. */
				if (TASK_CONNECTION_STAT_ISPOLL(target_cons)) {
					/* Send the signal to a normal thread. */
					ATOMIC_WRITE(receiver->tc_stat,
					             TASK_CONNECTION_STAT_BROADCAST |
					             TASK_CONNECTION_STAT_FLOCK_OPT);
					task_connection_unlink_from_sig_and_unlock(self, receiver);
					target_cons = TASK_CONNECTION_STAT_ASCONS(target_cons);
					if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender))
						goto unlock_receiver_and_return_already;
					thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
					ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
				} else {
					ATOMIC_WRITE(receiver->tc_stat,
					             TASK_CONNECTION_STAT_SENT |
					             TASK_CONNECTION_STAT_FLOCK_OPT);
					assert(target_cons == TASK_CONNECTION_STAT_ASCONS(target_cons));
					if (!ATOMIC_CMPXCH(target_cons->tcs_dlvr, NULL, sender)) {
						/* Another signal was already delivered to the specified thread. */
						task_connection_unlink_from_sig_and_unlock(self, receiver);
unlock_receiver_and_return_already:
						ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_BROADCAST);
						if (cleanup)
							(*cleanup->scc_cb)(cleanup);
						preemption_pop(&was);
						return SIG_SEND_SELECT_ALREADY;
					}
					sig_smplock_release_nopr(self);
					thread = xincref(ATOMIC_READ(target_cons->tcs_thread));
#if TASK_CONNECTION_STAT_FLOCK_OPT != 0
					ATOMIC_WRITE(receiver->tc_stat, TASK_CONNECTION_STAT_SENT);
#endif /* TASK_CONNECTION_STAT_FLOCK_OPT != 0 */
				}
				if (cleanup)
					(*cleanup->scc_cb)(cleanup);
				preemption_pop(&was);

				/* Wake-up the thread. */
				if likely(thread) {
					task_wake_as(thread,
					             context.ssc_caller,
					             context.ssc_wakeflags);
					decref_unlikely(thread);
				}
				return SIG_SEND_SELECT_SUCCESS;
			}
#ifndef CONFIG_NO_SMP
			ATOMIC_AND(receiver->tc_stat, ~TASK_CONNECTION_STAT_FLOCK);
#endif /* !CONFIG_NO_SMP */
		}
		if (receiver == sig_con)
			break;
		last_ingored_connection = receiver;
	}
	if (!select_poll) {
		context.ssc_flag = SIG_SELECT_FLAG_FORPOLL;
		select_poll      = true;
		goto again;
	}
	sig_smplock_release_nopr(self);
done:
	if (cleanup && run_cleanup_when_notarget)
		(*cleanup->scc_cb)(cleanup);
	preemption_pop(&was);
	return SIG_SEND_SELECT_NOTARGET;
}

PUBLIC NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL sig_send_select)(struct sig *__restrict self,
                               sig_send_selector_t selector, void *cookie,
                               struct sig_cleanup_callback *cleanup,
                               bool run_cleanup_when_notarget) {
	unsigned int result;
	result = sig_send_select_as(self,
	                            selector,
	                            cookie,
	                            THIS_TASK,
	                            cleanup,
	                            run_cleanup_when_notarget);
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

	assert(task_wasconnected());
	assert(task_wasconnected(&s));
	assert(task_trywait() == NULL);

	sig_broadcast(&s);

	/* Simulate what kfree() for the signal would do, thus
	 * ensuring that the the signal can still be received,
	 * even after it was destroyed. */
	memset(&s, 0xcc, sizeof(s));

	assert(task_wasconnected());
	assert(task_wasconnected(&s));

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);

	assert(task_popconnections() == &cons);

	assert(task_trywait() == &s);
	assert(task_trywait() == NULL);
}

DEFINE_TEST(broadcast_after_send) {
	struct sig s = SIG_INIT;
	task_connect(&s);
	assert(sig_send(&s));
	assert(sig_broadcast(&s) == 0);
	task_disconnectall();
}

DEFINE_TEST(pushpop_connections) {
	struct sig a = SIG_INIT, b = SIG_INIT;
	struct task_connections cons;
	assert(!sig_iswaiting(&a) && sig_numwaiting(&a) == 0);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	task_connect(&a);
	assert(task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	task_pushconnections(&cons);
	assert(!task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	task_connect(&b);
	assert(!task_wasconnected(&a));
	assert(task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(sig_iswaiting(&b) && sig_numwaiting(&b) == 1);

	task_disconnectall();
	assert(!task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	assert(task_popconnections() == &cons);
	assert(task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(sig_iswaiting(&a) && sig_numwaiting(&a) == 1);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);

	assert(task_disconnect(&a));
	assert(!task_wasconnected(&a));
	assert(!task_wasconnected(&b));
	assert(!task_wasconnected());
	assert(!sig_iswaiting(&a) && sig_numwaiting(&a) == 0);
	assert(!sig_iswaiting(&b) && sig_numwaiting(&b) == 0);
}
#endif /* DEFINE_TEST */


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_sig_send
#include "sig-send.c.inl"

#define DEFINE_sig_send_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_altsend
#include "sig-send.c.inl"

#define DEFINE_sig_altsend_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_sendto
#include "sig-send.c.inl"

#define DEFINE_sig_sendto_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_altsendto
#include "sig-send.c.inl"

#define DEFINE_sig_altsendto_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_altbroadcast
#include "sig-send.c.inl"

#define DEFINE_sig_altbroadcast_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_as_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_cleanup_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_as_cleanup_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_for_fini
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_for_fini_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_altbroadcast_for_fini
#include "sig-send.c.inl"

#define DEFINE_sig_altbroadcast_for_fini_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_as_for_fini_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_for_fini_cleanup_nopr
#include "sig-send.c.inl"

#define DEFINE_sig_broadcast_as_for_fini_cleanup_nopr
#include "sig-send.c.inl"

#define DEFINE_task_waitfor
#include "sig-waitfor.c.inl"

#define DEFINE_task_waitfor_with_sigmask
#include "sig-waitfor.c.inl"

#define DEFINE_task_waitfor_norpc
#include "sig-waitfor.c.inl"

#define DEFINE_task_waitfor_nx
#include "sig-waitfor.c.inl"

#define DEFINE_task_waitfor_norpc_nx
#include "sig-waitfor.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIG_C */
