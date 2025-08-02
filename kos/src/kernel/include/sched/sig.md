# Signal: mid-level, Kernel Synchronization Primitive

## Synopsis

At a basic level, `struct sig` is a *thread/callback wait queue*, allowing threads/callbacks to be added at random, and be removed+notified as part of signal delivery.


## Brief

- Signals are mid-level, state-less synchronization primitives that can be used to implement arbitrarily complex higher-level objects, such as mutexes, semaphores, condition-variables, ..., _anything_
- Whatever state a signal may have in some arbitrary context, it only gains this state indirectly by being used in a specific way.


## Usage

### Basic Example

```c
PRIVATE struct sig mysig = SIG_INIT;

PRIVATE void connect(void) {
	task_connect(&mysig);
}

PRIVATE void wait(void) {
	task_waitfor();
}

PRIVATE void post(void) {
	sig_send(&mysig);
}
```

Synchronization here happens as follows:

- Whenever a thread calls `connect()`, it will become attached to `mysig`, such that another thread sending that signal (as by `post()`) will notify the original thread that called `connect()` of this condition.
- For this purpose, it doesn't matter if the original thread that called `connect()` has already called `wait()` (and began blocking), or is still busy doing other things, but is planning to call `wait()` eventually
- The `task_waitfor()` function (when eventually called) will then cause the calling thread to suspend execution until one of the signals that its caller is connected to has been sent (but note that if one of those signals is sent before `task_waitfor()` is called, then `task_waitfor()` will never block to begin with, but return immediately)
- The moment that `task_waitfor()` returns, **all** connections that the calling thread had made in the past will have already been severed (to be even more precise: a connection is severed before `sig_send()` returns, with the only exception being signal completion functions that set the `SIGCOMP_MODE_F_REPRIME` flag)


### Real-World Example

How to use `struct sig`, and what **interlocked** means:

- If you think of DOS's `InterlockedIncrement` functions, or similar, I'm sorry to disappoint you, but that function should have been called `AtomicIncrement`, as it has nothing to do with interlocked behavior.
- Performing something interlocked means that an operation happens in a specific context where certain events can be monitored/handled, similar to how this would happen during a transaction (s.a. `/kos/src/kernel/modrtm`).
- For simplicity, consider the following example:

```c
[ 1] PRIVATE bool is_ready = false;
[ 2] PRIVATE struct sig became_ready = SIG_INIT;
[ 3]
[ 4] PRIVATE void wait_until_ready(void) {
[ 5] 	task_connect(&became_ready);
[ 6] 	if (atomic_read(&is_ready)) {
[ 7] 		task_disconnectall();
[ 8] 		return;
[ 9] 	}
[10] 	task_waitfor();
[11] }
[12]
[13] PRIVATE void become_ready(void) {
[14] 	atomic_write(&is_ready, true);
[15] 	sig_broadcast(&became_ready);
[16] }
```

Here, the read from `is_ready` on line #6 is interlocked with the async monitoring of `became_ready` that began on line #5. As such, line #6 knows that when `is_ready` isn't `true` yet, the calling thread will get notified after it becomes so (s.a. line #15) As such, all possible race conditions are handled here:

- case #1: `atomic_write(&is_ready, true);` happens before `task_connect(&became_ready)`:
	- `sig_broadcast(&became_ready)` has no-one to notify
	- The caller of `wait_until_ready()` will notice this in line #6
	- The `wait_until_ready()` function never starts blocking. Note that since this case is usually the most likely one, another test of the `is_ready` condition usually also happens before the initial connect. Though since no connect() will have happened at that point, such a test wouldn't be interlocked, and can only ever serve to speed up the case where an object is already ready from the get-go. Such models are referred to as test+connect+test, though the minimal requirement for race-less synchronization is always connect+test.
- case #2: `atomic_write(&is_ready, true);` happens after `task_connect(&became_ready)`, but before `atomic_read(&is_ready)`.
	- Line #6 will notice this, and disconnect from the `became_ready` signal once again, and the waiting thread never starts blocking.
- case #3: `atomic_write(&is_ready, true);` happens after `if (atomic_read(&is_ready))`
	- In this case, the caller of `wait_until_ready()` will end up inside of `task_waitfor()`, which will return as soon as line #15 gets executed.
	- Because by this point, the waiting thread has already been connected to the `became_ready` signal, it doesn't matter if `sig_broadcast()` is called before, or after `task_waitfor();`. In both cases, `task_waitfor()` will not return before `sig_broadcast()` has been called, but will return as soon as it has been called.


### Details

#### Signal Reception Priority Order

In order to improve performance, signals sent through `struct sig` may not always reach all  waiting / some specific waiting  thread.

- `sig_send()`:
	1. Try to send a signal to the longest-living connection that wasn't established as a poll-connection, and return `true`
	2. If no such connection exists, but there are still other connections (iow: only poll-connections remain), randomly select one of the poll-based connections and signal it. (Note that "random" here may not actually required to be random at all, but, in fact, is allowed to depend to the order in which connections had been enqueued).Continue with step #1
	3. If no connections are left, return `false`
- `sig_broadcast()`:
	1. If there is any connection (regardless of that connection being non-poll-, or poll-based), simply signal that connection. If the connection was non-poll-based, the value to-be returned by `sig_broadcast()` is incremented by one. Continue with step #1
	2. If no connections are left, return the number of signaled non-poll connections.

Whether a connection is poll- or non-poll-based depends on how it was established:

- Normal (non-poll) connections:
	- `task_connect()`
	- `sigcompcon_connect()`
	- `SIGCOMP_MODE_F_REPRIME` (under `sigcompcon_disablepoll()`)
- Poll connections:
	- `task_connect_for_poll()`
	- `sigcompcon_connect_for_poll()`
	- `SIGCOMP_MODE_F_REPRIME` (under `sigcompcon_enablepoll()`)





## Related

### Concept Stack

Signals are a mid-level concept:

1. Low-level: per-task scheduling controls
	- `task_wake()`
		- Send a sporadic wake-up to a specific thread
	- `task_sleep()`
		- Enter a sleeping state until a timeout expires, or a sporadic wake-up is received
	- Sporadic interrupts (aka. *wake-ups*) still exist at this level
	- This API-level then wraps arch-specific IPI mechanisms, as well as the system scheduler (both of which could be considered as part of an even lower level for our purposes: *0. super-low-level*)
2. Mid-level: Kernel Signals
	- `task_connect()`
		- Establishes a `struct sigtaskcon` between the calling thread and some `struct sig`
	- `task_waitfor()`
		- Wait until at least one of the signals the calling thread is connected to has been delivered. If at least one signal was already delivered at the time this function is called, the thread never starts sleeping and the call returns immediately. This call is the mid-level wrapper around `task_sleep()`
	- `sig_send()`, `sig_boardcast()`
		- Send signals to threads/completion-callbacks that may be connected to a given signal. In the case of threads, this call is the mid-level wrapper around `task_wake()`
	- Sporadic interrupts are no longer possible at this level, since a thread only stops sleeping upon the **explicit** delivery of a connected signal, and wake-events are context-targeted, rather than thread-targeted.
3. High-level: Synchronization primitives
	- `struct semaphore` (`<sched/semaphore.h>`)
	- `struct shared_lock` (`<kos/sched/shared-lock.h>`)
	- `struct shared_rwlock` (`<kos/sched/shared-rwlock.h>`)
	- `struct shared_recursive_lock` (`<kos/sched/shared-recursive-lock.h>`)
	- `struct shared_recursive_rwlock` (`<kos/sched/shared-recursive-rwlock.h>`)
	- Often, these high-level primitives aren't actually used, and system components instead make direct use of `struct sig`. That is OK and even encouraged (so-long as it isn't done to re-implement functionality already available from synchronization primitives)


## Internals

Documentation on how signals are implemented internally.

### Data types

Overview of relevant `struct`s and `#define`-constants used by the core sig-implementation.

Note that other implementation details below only cover the case where `SIG_SMPLOCK` needs to be defined. Semantics when this bit isn't needed are identical (meaning that locking is **only** done via disabling of preemption), but the details of such an implementation are left to the reader as an exercise.

#### Implementation

```c
#ifndef CONFIG_NO_SMP
#define SIG_SMPLOCK 0x0001 /* SMP lock bit for `(uintptr_t)struct sig::s_con' */
#endif /* !CONFIG_NO_SMP */

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

/* Possible values for `struct sigcon::sc_stat' */
#define SIGCON_STAT_F_POLL      0x0001 /* [valid_if(SIGCON_STAT_ISCONNECTED(.))] FLAG: This is a poll-based connection */
#define SIGCON_STAT_ST_THRBCAST 0x0000 /* [valid_if(!SIGCON_STAT_ISCONNECTED(.))] Status: connection was broadcast */
#define SIGCON_STAT_ST_THRSENT  0x0001 /* [valid_if(!SIGCON_STAT_ISCONNECTED(.))] Status: connection was sent */
#define SIGCON_STAT_TP_COMP     0x0002 /* [valid_if(!SIGCON_STAT_ISTHREAD(.))] Type code: this is a completion callback (and not a thread) */
#define SIGCON_STAT_ISCONNECTED(st) ((st) >= 0x0002) /* Is this connection still connected (iow: is it owned by `sc_sig' and its lock?) */
#define SIGCON_STAT_ISTHREAD(st)    ((st) >= 0x0004) /* Is this a `struct sigtaskcon'? */
#define SIGCON_STAT_ISCOMP(st)      ((st) <= 0x0003) /* Assuming "SIGCON_STAT_ISCONNECTED() == true": Is this a `struct sigcompcon'? */
#define SIGCON_STAT_ISDEAD(st)      ((st) <= 0x0001) /* True if the connection was sent/broadcast */

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

struct sigtaskcon: sigcon {
	// ...

	/* More fields here that may be used by `struct taskcons` to track
	 * allocated task connections. However, all of these fields will be
	 * [lock(THIS_TASK)] (iow: thread-local), and so aren't relevant to
	 * the cross-thread part of the signal system. */
};

struct sigcompcon: sigcon {
	sigcomp_cb_t sc_cb;  /* [1..1][const] Completion callback. */
};

struct taskcons {
	struct sig  *tcs_deliver; /* [0..1][lock(SET(ATOMIC), CLEAR(ATOMIC && THIS_TASK))]
	                           * The first signal that was delivered, or NULL if none were, yet. */
	struct task *tcs_thread;  /* [0..1][lock(READ(ATOMIC), WRITE(ATOMIC && THIS_TASK))]
	                           * The thread that is listening  for this signal (which  is
	                           * always the thread  that owns this  controller), or  NULL
	                           * if this is not the currently-active controller, in which
	                           * case signals can still be received, but the thread  will
	                           * not receive any wake-ups. */

	// ...

	/* More fields here that implement allocation of `struct sigtaskcon`
	 * for  the  owning  thread. However,  all  of these  fields  will be
	 * "[lock(THIS_TASK)]" (iow: thread-local), and so aren't relevant to
	 * the cross-thread part of the signal system. */
};

```





### Connecting to a signal

To add a connection to a signal, after the caller initialized `con->sc_stat` as:

- `SIGCON_STAT_TP_COMP`: Connection is a completion callback
- `SIGCON_STAT_TP_COMP | SIGCON_STAT_F_POLL`: Connection is a polling completion callback
- `(uintptr_t)my_taskcons`: Connection is a thread connection
- `(uintptr_t)my_taskcons | SIGCON_STAT_F_POLL`: Connection is a polling thread connection

#### Implementation

```c
void sig_addcon(struct sig *self, struct sigcon *con) {
	preemption_flag_t was;
	struct sigcon *sigctl;
	con->sc_sig = self;
again:
	sigctl = atomic_read(&self->s_con);
	assertf((uintptr_t)sigctl != 0 | SIG_SMPLOCK, "SIG_SMPLOCK must not appear without connections");
	if ((uintptr_t)sigctl == 0) {
		/* Special case: first connection (can be set-up completely atomically) */
		con->sc_prev = con;
		con->sc_next = con;
		if (!atomic_cmpxch_weak(&self->s_con, NULL, con))
			goto again;
		return;
	}
	if ((uintptr_t)sigctl & SIG_SMPLOCK) {
		task_tryyield_or_pause();
		goto again;
	}

	preemption_pushoff(&was);

	/* Acquire SMP-lock */
	if (!atomic_cmpxch_weak(&self->s_con, sigctl,
	                        (struct sigcon *)((uintptr_t)sigctl | SIG_SMPLOCK))) {
		preemption_pop(&was);
		goto again;
	}

	/* Insert "con" before "sigctl" in the ring (thus placing it at the end of the queue) */
	con->sc_next = sigctl;
	con->sc_prev = sigctl->sc_prev;
	assert(con->sc_prev->sc_next == sigctl);
	con->sc_prev->sc_next = con;
	sigctl->sc_prev = con;
	atomic_write(&self->s_con, sigctl); /* Release SMP-lock */
	preemption_pop(&was);
}
```





### Disconnecting from a signal

To remove a connection from a signal:

- When `forward_received == true`, forward `SIGCON_STAT_ST_THRSENT` signals to the receiver that is next-in-line

#### Implementation

```c
void sig_remcon(struct sigcon *con, bool forward_received) {
	struct sig *self;
	struct sigcon *sigctl;
	preemption_flag_t was;
	uintptr_t stat;
again:
	stat = atomic_read(&con->sc_stat);
	if (SIGCON_STAT_ISDEAD(stat)) {
handle_dead_connection:
		/* Signal was already sent -> possibly forward, but
		 * no need to remove (because that was already done) */
		if (forward_received && stat == SIGCON_STAT_ST_THRSENT) {
			if (!sig_send(con->sc_sig))
				printk(KERN_WARNING "[sig] Signal %p cannot be forwarded (no recipients)\n", self);
		}
		return;
	}

	self = con->sc_sig;
	sigctl = atomic_read(&self->s_con);
	assertf((uintptr_t)sigctl != 0 | SIG_SMPLOCK, "SIG_SMPLOCK must not appear without connections");
	if unlikely((uintptr_t)sigctl == 0) {
		/* Race condition: another thread *just* sent this signal, and only *just* unlocked
		 * the signal, but did so *after* our first check regarding the connection state.
		 *
		 * This can only happen when the connection is *now* dead. */
		stat = atomic_read(&con->sc_stat);
		assertf(SIGCON_STAT_ISDEAD(stat),
		        "Signal has no more connections, but our connection isn't dead?");
		goto handle_dead_connection;
	}
	if ((uintptr_t)sigctl & SIG_SMPLOCK) {
		task_tryyield_or_pause();
		goto again;
	}

	preemption_pushoff(&was);
	/* Acquire SMP-lock */
	if (!atomic_cmpxch_weak(&self->s_con, sigctl,
	                        (struct sigcon *)((uintptr_t)sigctl | SIG_SMPLOCK))) {
		preemption_pop(&was);
		goto again;
	}

	if (sigctl == con) {
		/* Special case: first connection is being removed while still connected. */
		struct sigcon *prev, *next;
		assert(!SIGCON_STAT_ISDEAD(con->sc_stat));
		assert(con->sc_next->sc_prev == con);
		assert(con->sc_prev->sc_next == con);
		assert((con->sc_next == con) == (con->sc_prev == con));
		prev = con->sc_prev;
		next = con->sc_next;
		DBG_memset(&con->sc_prev, 0xcc, sizeof(con->sc_prev));
		DBG_memset(&con->sc_next, 0xcc, sizeof(con->sc_next));
		if (next == con) {
			/* Double-special case: last connection is being removed */
			next = NULL;
		} else {
			next->sc_prev = prev;
			prev->sc_next = next;
		}
		atomic_write(&self->s_con, next); /* Also releases SMP-lock */
	} else {
		struct sigcon *prev, *next;

		/* Must check again if the connection has died since we checked above. */
		stat = atomic_read(&con->sc_stat);
		if (SIGCON_STAT_ISDEAD(stat)) {
			atomic_write(&self->s_con, sigctl); /* Release SMP-lock */
			preemption_pop(&was);
			goto handle_dead_connection;
		}

		/* Remove some random connection (that is not the first in-queue) */
		assert(!SIGCON_STAT_ISDEAD(con->sc_stat));
		assert(con->sc_next->sc_prev == con);
		assert(con->sc_prev->sc_next == con);
		assert(con->sc_next != con);
		assert(con->sc_prev != con);
		prev = con->sc_prev;
		next = con->sc_next;
		DBG_memset(&con->sc_prev, 0xcc, sizeof(con->sc_prev));
		DBG_memset(&con->sc_next, 0xcc, sizeof(con->sc_next));
		next->sc_prev = prev;
		prev->sc_next = next;
		atomic_write(&self->s_con, sigctl); /* Release SMP-lock */
	}

	preemption_pop(&was);
}
```





### Sending a signal

To send a signal, `sig_send` (and its derivatives) are used and implemented as follows:

#### Implementation

```c
bool sig_send(struct sig *self) {
	struct sigcon *sigctl;
	struct sigcon *receiver;
	struct sigcon *remainder;
	struct taskcons *tcs;
	preemption_flag_t was;

again:
	sigctl = atomic_read(&self->s_con);
	assertf((uintptr_t)sigctl != 0 | SIG_SMPLOCK, "SIG_SMPLOCK must not appear without connections");
	if ((uintptr_t)sigctl == 0) {
		/* Special case: no-one is connected */
		HANDLE_CLEANUP_IF_PRESENT(); /* for sig_send_cleanup */
		return false;
	}
	if ((uintptr_t)sigctl & SIG_SMPLOCK) {
		task_tryyield_or_pause();
		goto again;
	}

	preemption_pushoff(&was);

	/* Acquire SMP-lock */
	if (!atomic_cmpxch_weak(&self->s_con, sigctl,
	                        (struct sigcon *)((uintptr_t)sigctl | SIG_SMPLOCK))) {
		preemption_pop(&was);
		goto again;
	}

again_find_receiver:
	receiver = sigctl;
	assert(receiver->sc_sig == self);

#if SIG_SENDTO
	/* ... (Custom code to find connections made by the given thread) */
#else /* SIG_SENDTO */
	if (atomic_read_relaxed(&receiver->sc_stat) & SIGCON_STAT_F_POLL) {
		/* Try to find a non-polling receiver, and if we manage to find
		 * one, shove all of the poll-based ones to the back of the queue. */
		struct sigcon *poll_head;
		struct sigcon *poll_tail;
		do {
			assert(receiver->sc_prev->sc_next == receiver);
			assert(receiver->sc_next->sc_prev == receiver);
			assert((receiver->sc_next != receiver) || (receiver->sc_next == sigctl));
			receiver = receiver->sc_next;
			if (receiver == sigctl) {
				/* All remaining connections are poll-based.
				 * Essentially the same as "sig_broadcast()", but:
				 * - Allowed to assume that the wait queue is non-empty
				 * - Inherits the SMP-lock to "self"
				 * - Inherits the preemption state in "was"
				 * For more info, see description of `sig_broadcast()`
				 */
				sig_broadcast_and_unlock_and_preemption_pop(
						/* struct sig                  *self     */ self,
						/* struct sig                  *sender   */ self,      /* For: `sig_altsend` */
						/* struct task                 *caller   */ THIS_TASK, /* For: `sig_sendas` */
						/* struct sig_cleanup_callback *cleanup  */ NULL,      /* For: `sig_send_cleanup` */
						/* preemption_flag_t            was      */ was
				);
				return false;
			}
		} while (atomic_read_relaxed(&receiver->sc_stat) & SIGCON_STAT_F_POLL);

		/* Shove the chain of poll-based receivers to the back of the queue. */
		poll_head = sigctl;
		poll_tail = receiver->sc_prev;
		assert(poll_tail != receiver);
		assert(poll_tail->sc_next == receiver);

		/* Unlink poll-based connections from queue */
		poll_head->sc_prev->sc_next = receiver;
		receiver->sc_prev = poll_head->sc_prev;

		remainder = receiver->sc_next;
		assert(remainder != receiver);

		/* Re-insert poll-based connections before "remainder" (which will become the queue's
		 * new head, meaning that anything that appears before it will actually appear at the
		 * end of the queue) */
		poll_head->sc_prev = remainder->sc_prev;
		poll_head->sc_prev->sc_next = poll_head;
		poll_tail->sc_next = remainder;
		remainder->sc_prev = poll_tail;
	} else {
		remainder = receiver->sc_next;
		if unlikely(remainder == receiver)
			remainder = NULL; /* Special case: last connection goes away */
	}
#endif /* !SIG_SENDTO */

	/* Remove "receiver" from the wait queue. */
	assert(receiver != remainder);
	assert(receiver->sc_prev->sc_next == receiver);
	assert(receiver->sc_next->sc_prev == receiver);
	receiver->sc_prev->sc_next = receiver->sc_next;
	receiver->sc_next->sc_prev = receiver->sc_prev;

	/* Load the status/task word of "receiver" */
	tcs = atomic_read_relaxed(&receiver->sc_cons);
	assert(SIGCON_STAT_ISCONNECTED((uintptr_t)tcs));

	/* Deal with completion-callbacks */
#if !SIG_SENDTO
	if unlikely(SIGCON_STAT_ISCOMP((uintptr_t)tcs)) {
		/* This call does everything needed to (in order):
		 * - invoke phase#1 callback of "receiver"
		 *   - if the callback indicates that that it wants to be re-primed, do so.
		 *   - if the callback indicates that it can't receive the signal:
		 *     - if it also re-primed itself, add "receiver" to an internal list
		 *       of non-viable receivers that will always be skipped by the code
		 *       used to search for receivers, as seen above.
		 *     - Make use of a custom "sig_send" implementation that skips
		 *       non-viable receivers, and inherits the caller's SMP-lock,
		 *       preemption_flag_t, "caller", "cleanup", etc.. Once that call
		 *       has completed, and released all relevant locks and so on,
		 *       return true/false indicative of that function having been
		 *       able to send the signal.
		 * - release the SMP-lock from "self" by assigning `remainder`
		 * - invoke "cleanup" callbacks (while preemption is still off)
		 * - restore preemption as per "was"
		 * - destroy receiver threads whose reference counters dropped to 0
		 * - invoke phase#2 callback of "receiver"
		 * - return true
		 */
		return sig_completion_invoke_and_unlock_and_preemption_pop(
				/* struct sig                  *self      */ self,
				/* struct sig                  *sender    */ self,
				/* struct sigcompcon          *receiver  */ (struct sigcompcon *)receiver,
				/* struct sigcon               *remainder */ remainder,
				/* struct task                 *caller    */ THIS_TASK, /* For: `sig_sendas` */
				/* struct sig_cleanup_callback *cleanup   */ NULL,      /* For: `sig_send_cleanup`; s.a. `HANDLE_CLEANUP_IF_PRESENT()` */
				/* preemption_flag_t            was       */ was
		);
	} else
#endif /* !SIG_SENDTO */
	{
		REF struct task *thread;
		tcs = (struct taskcons *)((uintptr_t)tcs & ~SIGCON_STAT_F_POLL);
		assert(SIGCON_STAT_ISTHREAD((uintptr_t)tcs));

		/* Try to set out signal as the sender. "sig_altsend"
		 * sets the given signal here, rather than "self". */
		if (!atomic_cmpxch(&tcs->tcs_deliver, NULL, self)) {
			/* Failed to deliver signal :(
			 * - Mark the receiver for broadcast
			 * - Jump back to find another receiver (this one we already removed from the queue)
			 */
			atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST); /* This releases our ownership of "receiver" */
			/* vvv this write isn't necessary, because "self->s_con" isn't used anywhere after
			 *     the "again_find_receiver" label (because there is no jump back to "again",
			 *     which is the only place where such a read happens) */
//			atomic_write(&self->s_con, (struct sigcon *)((uintptr_t)remainder | SIG_SMPLOCK)); /* Keep SMP-lock */
			sigctl = remainder;
			goto again_find_receiver;
		}

		/* First signal delivered -> must wake the thread after locks were released. */
		thread = xincref(atomic_read(&tcs->tcs_thread));
		atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRSENT); /* This releases our ownership of "receiver" */
		atomic_write(&self->s_con, remainder); /* Release SMP-lock */
		HANDLE_CLEANUP_IF_PRESENT(); /* for sig_send_cleanup */
		preemption_pop(&was);
		if (thread) {
			task_wake(thread); /* Or `task_wake_as` in case of `sig_sendas` */
			decref_unlikely(thread);
			return true;
		}
	}
	return true;
}
```




### Broadcasting a signal

Broadcasting a signal works similar to sending one, however rather than focusing on only a single receiver, all receivers receive a signal (*once*; re-priming completion callbacks are also only invoked once, even when indicating that they aren't viable):

- Nothing happens when `tcs_thread` of a `struct sigtaskcon` connection was already assigned
- poll-based connections are neither skipped, nor moved to the back, but treated like any other
- Semantically (*almost*) identical to:

  ```c
  size_t sig_broadcast(struct sig *self) {
  	size_t result = 0;
  	while (sig_send(self))
  		++result;
  	return result;
  }
  ```
	- *almost* because:
		- self-re-priming signal completions are only notified **once**
		- poll-based connections are signaled as they appear in the wait queue, as opposed to only after no more non-poll-based ones exist
		- `sc_stat` is always set to `SIGCON_STAT_ST_THRBCAST` (meaning disconnecting never forwards the signal)
		- preemption and `SIG_SMPLOCK` is only disabled/acquired **once** (meaning that signal's connections will become empty atomically)
		- Cleanup happens in bulk (s.a. the comment for `sig_completion_invoke_and_unlock_and_preemption_pop` above):
			1. release the SMP-lock from `self`
			2. `HANDLE_CLEANUP_IF_PRESENT()` happens **once** (while preemption is still off, but after the signal's SMP-lock was released)
			3. restore preemption as it was before `sig_broadcast()`
			4. destroyed threads (s.a. the `decref_unlikely(thread)` above) are all deleted
			5. phase #2 signal completion callbacks are executed all at once at the end
- The alternate function `sig_sendmany()` is implemented in terms of `sig_broadcast()`. The only difference is that `sig_sendmany()` stops once `result >= maxcount`. All receivers that haven't been enumerated at that point are then simply inserted at the front of `reprimed` (see *Implementation* below)
	- As such, `sig_sendmany(sig, 1)` is (*almost*) identical to `sig_send(sig)`
		- *almost* because `sig_send()` skips over poll-based connections and only broadcasts them once no non-poll-based ones remain
	- As such, `sig_sendmany(sig, (size_t)-1)` is identical to `sig_broadcast(sig)`


#### Implementation

```c
size_t sig_broadcast(struct sig *self) {
	size_t result;
	struct task_slist destroy_later;
	struct sigcompcon *reprimed;
	struct sig_post_completion *phase2;

	struct sigcon *sigctl;
	struct sigcon *receiver;
	struct taskcons *tcs;
	preemption_flag_t was;

again:
	sigctl = atomic_read(&self->s_con);
	assertf((uintptr_t)sigctl != 0 | SIG_SMPLOCK, "SIG_SMPLOCK must not appear without connections");
	if ((uintptr_t)sigctl == 0) {
		/* Special case: no-one is connected */
		HANDLE_CLEANUP_IF_PRESENT(); /* for sig_send_cleanup */
		return false;
	}
	if ((uintptr_t)sigctl & SIG_SMPLOCK) {
		task_tryyield_or_pause();
		goto again;
	}
	preemption_pushoff(&was);

	/* Acquire SMP-lock */
	if (!atomic_cmpxch_weak(&self->s_con, sigctl,
	                        (struct sigcon *)((uintptr_t)sigctl | SIG_SMPLOCK))) {
		preemption_pop(&was);
		goto again;
	}

	result        = 0;
	destroy_later = SLIST_HEAD_INITIALIZER(destroy_later);
	reprimed      = NULL;
	phase2        = NULL;

	/* Enumerate all receivers and signal each of them. */
	receiver = sigctl;
	do {
		struct sigcon *next = receiver->sc_next;
		bool bcast_ok;
		uintptr_t stat = atomic_read(&receiver->sc_stat);
		assert(SIGCON_STAT_ISCONNECTED(stat));
//		assert(receiver->sc_prev->sc_next == receiver); /* Cannot be asserted because we might no longer own "receiver->sc_prev". Also: we destroy these links via DBG_memset */
//		assert(receiver->sc_next->sc_prev == receiver); /* Cannot be asserted because we might no longer own "receiver->sc_next" (if it is "sigctl"). Also: we destroy these links via DBG_memset */
		DBG_memset(&receiver->sc_prev, 0xcc, sizeof(receiver->sc_prev));
		DBG_memset(&receiver->sc_next, 0xcc, sizeof(receiver->sc_next));

		if (SIGCON_STAT_ISCOMP(stat)) {
			struct sigcompcon *sc = (struct sigcompcon *)receiver;
			int status = invoke_sig_completion(&phase2, sc, ...); // "context" not documented here
#if !IS_BROADCAST_FOR_FINI
			if (status & SIGCOMP_MODE_F_REPRIME) {
				/* Insert into "reprimed" queue (at the end, such that order is maintained)
				 * Note that repriming isn't allowed during `sig_broadcast_for_fini()`! */
				if (reprimed == NULL) {
					sc->sc_prev = sc;
					sc->sc_next = sc;
					reprimed = sc;
				} else {
					sc->sc_next = reprimed;
					sc->sc_prev = reprimed->sc_prev;
					reprimed->sc_prev->sc_next = sc;
					reprimed->sc_prev = sc;
				}
			} else
#endif /* !IS_BROADCAST_FOR_FINI */
			{
				atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST); /* This releases our ownership of "receiver" */
			}
			bcast_ok = (status & SIGCOMP_MODE_F_NONVIABLE) == 0;
		} else {
			struct taskcons *tcs = (struct taskcons *)(stat & ~SIGCON_STAT_F_POLL);
			bcast_ok = atomic_cmpxch(&tcs->tcs_deliver, NULL, self);
			if (bcast_ok) {
				/* First signal delivered -> must wake the thread after locks were released. */
				REF struct task *thread = xincref(atomic_read(&tcs->tcs_thread));
				atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST); /* This releases our ownership of "receiver" */
				if (thread) {
					task_wake(thread); /* Or `task_wake_as` in case of `sig_boardcastas` */
					if unlikely(atomic_decfetch(&thread->t_refcnt) == 0)
						SLIST_INSERT(&destroy_later, thread, XXX);
				}
			} else {
				atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST); /* This releases our ownership of "receiver" */
			}
		}

		/* Keep track of the # of successful non-poll broadcasts */
		if (bcast_ok && !(stat & SIGCON_STAT_F_POLL))
			++result;

		/* Move on to the next receiver */
		receiver = next;
	} while (receiver != sigctl);

	atomic_write(&self->s_con, reprimed); /* Release SMP-lock; only reprimed connections remain */
	HANDLE_CLEANUP_IF_PRESENT(); /* for sig_broadcast_cleanup */
	preemption_pop(&was);
	sig_destroylater_act(&destroy_later);
	sig_run_phase_2(phase2, ...); // "context" not documented here
	return result;
}
```
