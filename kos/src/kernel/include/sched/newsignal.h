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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_NEWSIGNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_NEWSIGNAL_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

#include <sched/pertask.h>

#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_H
#include <sched/signal.h>
#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_H */

#ifdef CONFIG_USE_NEW_SIGNAL_API
DECL_BEGIN

/* Declare support for signal-driven poll operations
 * >> bool pollread(MyType *self) {
 * >>     if (sync_canread(self))
 * >>         return true;
 * >>     task_connect_for_poll(&self->m_signal);
 * >>     return unlikely(sync_canread(self)); // Re-check to prevent race condition
 * >> }
 */
#if defined(__cplusplus) && defined(__CC__)
#define __DEFINE_SYNC_POLL(T, _pollread, _pollwrite)                                                                                                  \
	extern "C++" {                                                                                                                                    \
	FORCELOCAL ATTR_ARTIFICIAL WUNUSED NONNULL((1)) __BOOL (KCALL sync_pollread)(T *__restrict self) THROWS(E_BADALLOC) { return _pollread(self); }   \
	FORCELOCAL ATTR_ARTIFICIAL WUNUSED NONNULL((1)) __BOOL (KCALL sync_pollwrite)(T *__restrict self) THROWS(E_BADALLOC) { return _pollwrite(self); } \
	}
#else /* __cplusplus && __CC__ */
#define __DEFINE_SYNC_POLL(T, _pollread, _pollwrite) /* nothing */
#endif /* !__cplusplus || !__CC__ */


#ifdef __CC__

struct sig;
struct task;
struct task_connection;
struct task_connections;

struct sig {
#ifdef __SIG_INTERNAL_EXPOSE_CONTROL_WORD
	union {
		struct task_connection *s_con; /* [0..1][chain(->tc_signext)]
		                                * [lock(INSERT(ATOMIC))]
		                                * [lock(REMOVE(!PREEMPTION_ENABLED() && IF_SMP(SMP_LOCK(tc_sig))))]
		                                * Chain of established connections.
		                                * In SMP, the least significant bit is a lock that needs to be
		                                * held when connections are removed. Note however that this lock
		                                * may only be acquired when preemption is disabled, as it must
		                                * be guarantied that the lock always becomes available while doing
		                                * a `while (!trylock()) task_pause()'-loop. */
		uintptr_t               s_ctl; /* Signal control word */
	};
#else /* __SIG_INTERNAL_EXPOSE_CONTROL_WORD */
	struct task_connection *s_con; /* [0..1][chain(->tc_signext)]
	                                * [lock(INSERT(ATOMIC))]
	                                * [lock(REMOVE(!PREEMPTION_ENABLED() && IF_SMP(SMP_LOCK(tc_sig))))]
	                                * Chain of established connections.
	                                * In SMP, the least significant bit is a lock that needs to be
	                                * held when connections are removed. Note however that this lock
	                                * may only be acquired when preemption is disabled, as it must
	                                * be guarantied that the lock always becomes available while doing
	                                * a `while (!trylock()) task_pause()'-loop. */
#endif /* !__SIG_INTERNAL_EXPOSE_CONTROL_WORD */
};

#ifdef __SIG_INTERNAL_EXPOSE_CONTROL_WORD
#define SIG_INIT { { __NULLPTR } }
#else /* __SIG_INTERNAL_EXPOSE_CONTROL_WORD */
#define SIG_INIT { __NULLPTR }
#endif /* !__SIG_INTERNAL_EXPOSE_CONTROL_WORD */

#define sig_init(x)  (void)((x)->s_con = __NULLPTR)
#define sig_cinit(x) (void)(__hybrid_assert((x)->s_con == __NULLPTR))



/* Send signal `self' to exactly 1 connected thread
 * @return: true:  A waiting thread was signaled.
 * @return: false: The given signal didn't have any active connections. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_send)(struct sig *__restrict self);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sig_altsend)(struct sig *self,
                           struct sig *sender);

/* Send signal to all connected threads
 * @return: * : The actual number of threads notified, not counting ghosts. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast)(struct sig *self,
                                struct sig *sender);

/* Check if the given signal has viable recipients.
 * This includes poll-based connections. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_iswaiting)(struct sig *__restrict self);

/* Count the # of viable recipients of the given signal.
 * This includes poll-based connections. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_numwaiting)(struct sig *__restrict self);





/* Connection status values (is-connected is every `x' with `!TASK_CONNECTION_STAT_CHECK(x)')
 * This initial `!TASK_CONNECTION_STAT_CHECK(x)'-state can transition to:
 *   - TASK_CONNECTION_STAT_SENT:      Some thread called `sig_send(tc_sig)', and the
 *                                     associated `struct task_connection' was selected.
 *   - TASK_CONNECTION_STAT_BROADCAST: Some thread called `sig_broadcast(tc_sig)'.
 * Also note that any recipient can only ever have at most 1 connection with
 * a state of `TASK_CONNECTION_STAT_SENT' or `TASK_CONNECTION_STAT_BROADCAST',
 * though this invariant is only true when interlocked with the SMP-locks of
 * all attached signals. (s.a. `tcs_dlvr')
 */
#define TASK_CONNECTION_STAT_SENT         ((uintptr_t)-1) /* Signal was sent, and must be forwarded if not received via `task_waitfor()'
                                                           * In this state, the attached signal must not be free'd, though this case can
                                                           * easily be handled by broadcasting signals one last time before disconnecting.
                                                           * Transitions to (with [lock(SMP_LOCK(tc_sig))]):
                                                           *   - TASK_CONNECTION_STAT_BROADCAST: Any thread called `sig_broadcast()'
                                                           *                                     on the attached signal. */
#define TASK_CONNECTION_STAT_BROADCAST    ((uintptr_t)-2) /* Signal was broadcast (forwarding is unnecessary if ignored)
                                                           * In this state, `tc_sig' must be considered to be `[valid_if(false)]', and the
                                                           * thread that originally connected to the signal mustn't directly re-connect.
                                                           * When all (past) connections have entered this state, the associated signal is
                                                           * allowed to have it's backing memory be free'd!
                                                           * NOTE: THIS STATUS WILL NEVER APPEAR IN SIGNAL CONNECTION CHAINS! */
#define TASK_CONNECTION_STAT_CHECK(x)     ((uintptr_t)(x) >= (uintptr_t)-2)

/* For use when `!TASK_CONNECTION_STAT_CHECK(x)': check for poll-connections. */
#define TASK_CONNECTION_STAT_GETCONS(x)   ((struct task_connections *)((uintptr_t)(x) & ~1))
#define TASK_CONNECTION_STAT_ISNORM(x)    (((uintptr_t)(x) & 1) == 0)
#define TASK_CONNECTION_STAT_ISPOLL(x)    (((uintptr_t)(x) & 1) != 0)

struct task_connection {
	struct sig                  *tc_sig;     /* [1..1][const] The connected signal. */
	struct task_connection      *tc_connext; /* [0..1][lock(THIS_TASK)] Next connection established by the caller. */
	struct task_connection      *tc_signext; /* [0..1][lock(!PREEMPTION_ENABLED() && IF_SMP(SMP_LOCK(tc_sig)))]
	                                          * Next connection for the same signal. */
	union {
		struct task_connections *tc_cons; /* [1..1] Attached connection set/connection status.
		                                   * The least significant bit is set in case of a poll-connection. */
		WEAK uintptr_t           tc_stat; /* Connection status (one of `TASK_CONNECTION_STAT_*'). */
	};
};


/* Max number of signal connections guarantied to not invoke `kmalloc()'
 * and potentially throw exceptions, or serve RPC functions. */
#ifndef CONFIG_TASK_STATIC_CONNECTIONS
#define CONFIG_TASK_STATIC_CONNECTIONS 3
#endif /* !CONFIG_TASK_STATIC_CONNECTIONS */

struct task_connections {
	struct task_connections *tsc_prev;   /* [0..1][lock(PRIVATE(THIS_TASK))]
	                                      * [(!= NULL) == (this == &this_root_connections)]
	                                      * Previous set of active connections. */
	WEAK struct task        *tcs_thread; /* [0..1][lock(PRIVATE(THIS_TASK))]
	                                      * The thread to wake upon signal delivery. (may also be `NULL')
	                                      * This field is usually `NULL' for all connection sets 
	                                      * `!= FORTASK(tcs_thread, this_connections)', and is set
	                                      * as equal to `THIS_TASK' for `PERTASK(this_connections)'
	                                      * Note that it is guarantied that this task-pointer remains
	                                      * valid from the point of view of potentially attached signal,
	                                      * even after this field may be set to NULL/non-NULL, for as
	                                      * long as the actual, underlying thread no longer has any
	                                      * active connections. (i.e. has called `task_disconnectall()') */
	struct task_connection  *tcs_con;    /* [0..1][chain(->tc_connext)][lock(PRIVATE(THIS_TASK))]
	                                      * Chain of active connections. */
	struct sig              *tcs_dlvr;   /* [0..1][lock(WRITE_ONCE, CLEAR(PRIVATE))]
	                                      * The first signal that got delivered. */
	struct task_connection   tcs_static[CONFIG_TASK_STATIC_CONNECTIONS];
	                                     /* [*.in_use_if(.tc_sig != NULL)][lock(PRIVATE(THIS_TASK))]
	                                      * Statically allocated connections. Any connection that belongs to
	                                      * this connections set, but points outside of this array is allocated
	                                      * dynamically using `kmalloc()', and as such, must be freed by `kfree()' */
};

/* Root connections set. */
DATDEF ATTR_PERTASK struct task_connections this_root_connections;
#define THIS_ROOT_CONNECTIONS (&PERTASK(this_root_connections))

/* [1..1][lock(PRIVATE(THIS_TASK))] Current set of in-use connections.
 * Most of the time, this will simply point to `PERTASK(this_root_connections)' */
DATDEF ATTR_PERTASK struct task_connections *this_connections;
#define THIS_CONNECTIONS PERTASK_GET(this_connections)


/* Push/pop the active set of connections. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushconnections)(struct task_connections *__restrict cons);
FUNDEF NOBLOCK ATTR_RETNONNULL struct task_connections *
NOTHROW(FCALL task_popconnections)(void);
#define task_popconnections(...) task_popconnections() /* TODO: Remove me! */




/* Connect the calling thread to a given signal.
 * NOTE: It the caller was already connected to `target', a second connection
 *       will be established, and `task_disconnect()' must be called more than
 *       once. However, aside from this, having multiple connections to the
 *       same signal has no other adverse side-effects.
 * NOTE: When the signal test expression is able to throw an exception, the
 *       caller of this function is responsible to disconnect from the signal
 *       afterwards. However, exceptions that may be thrown by `task_waitfor()'
 *       always guaranty that _all_ established connections have been removed.
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
 * @throw: E_BADALLOC: Insufficient memory (only when there are at least
 *                     `CONFIG_TASK_STATIC_CONNECTIONS' connections already). */
FUNDEF NONNULL((1)) void FCALL
task_connect(struct sig *__restrict target) /*THROWS(E_BADALLOC)*/;

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
FUNDEF NONNULL((1)) void FCALL
task_connect_for_poll(struct sig *__restrict target) /*THROWS(E_BADALLOC)*/;


/* Disconnect from a specific signal `target'
 * @return: true:  Disconnected from `target'
 * @return: false: You weren't actually connected to `target' */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target);

/* Disconnect from all connected signal.
 * Signals with a state of `TASK_CONNECTION_STAT_SENT' will be forwarded. */
FUNDEF NOBLOCK void
NOTHROW(FCALL task_disconnectall)(void);

/* Same as `task_disconnectall()', but don't forward signals with a
 * `TASK_CONNECTION_STAT_SENT'-state, but rather return the sender
 * of of the signal that was received.
 * As such, the caller must properly pass on information about the
 * fact that a signal may have been received, as well as act upon
 * this fact. */
FUNDEF NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_receiveall)(void);

/* Check if the calling thread is connected to any signal. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_isconnected)(void);

/* Check if the calling thread is connected to the given signal. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_isconnected_to)(struct sig const *__restrict target);

#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_isconnected)(struct sig const *__restrict target)
		ASMNAME("task_isconnected_to");
} /* extern "C++" */
#endif /* __cplusplus */


/* Check if there is a signal to was delivered, disconnecting
 * all other connected signals if this was the case.
 * @return: NULL: No signal is available
 * @return: * :   The signal that was delivered. */
FUNDEF NOBLOCK struct sig *NOTHROW(FCALL task_trywait)(void);

/* Wait for the first signal to be delivered, unconditionally
 * disconnecting all connected signals thereafter.
 * NOTE: Prior to fully starting to block, this function will call `task_serve()'
 * @param: abs_timeout:  The `realtime()' timeout for the wait.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked.
 * @throw: * :           [task_waitfor] An error was thrown by an RPC function.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 *              WARNING: In all other cases, task connections are preserved when an exception
 *                       is thrown, meaning that if some interlocked signal check might thrown
 *                       an exception, you are required to TRY ... EXCEPT { task_disconnectall(); }
 *                       to prevent signal connections from being leaked!
 * @return: NULL: No signal has become available (never returned when `NULL' is passed for `abs_timeout').
 * @return: * :   The signal that was delivered. */
FUNDEF struct sig *FCALL
task_waitfor(struct timespec const *abs_timeout DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, ...);

/* Same as `task_waitfor', but don't serve RPC functions. */
FUNDEF struct sig *FCALL
task_waitfor_norpc(struct timespec const *abs_timeout DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);

/* Same as `task_waitfor', but only service NX RPCs, and return `NULL' if
 * there are pending RPCs that are allowed to throw exception, or if preemption
 * was disabled, and the operation would have blocked. */
FUNDEF struct sig *
NOTHROW(FCALL task_waitfor_nx)(struct timespec const *abs_timeout DFL(__NULLPTR));

/* Same as `task_waitfor', but don't serve RPC functions, and return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
FUNDEF struct sig *
NOTHROW(FCALL task_waitfor_norpc_nx)(struct timespec const *abs_timeout DFL(__NULLPTR));


#ifdef CONFIG_BUILDING_KERNEL_CORE
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_init_task_connections)(struct task *__restrict self);
#endif /* CONFIG_BUILDING_KERNEL_CORE */

#endif /* __CC__ */


/* Configuration option for standard synchronization primitives.
 * Before connecting to a signal, try to yield a couple of times
 * to try and get other threads to release some kind of lock, as
 * `task_yield()' is a much faster operation than task_connect()+task_wait().
 * Doing this may improve performance, especially on single-core machines.
 * Note however that this option does not affect the behavior of
 * low-level `struct sig' objects, but instead primitives found in
 * <sched/[...].h>, such as `struct mutex', `struct rwlock',
 * `struct semaphore' and `struct shared_rwlock'
 * NOTE: The number that this is defined to describes the
 *       max number of times `task_yield()' is attempted
 *      (implementing a kind-of spin-locking mechanism),
 *       before a signal is actually connected. */
#ifndef CONFIG_YIELD_BEFORE_CONNECT
#ifndef CONFIG_NO_YIELD_BEFORE_CONNECT
#define CONFIG_YIELD_BEFORE_CONNECT  4
#endif /* !CONFIG_NO_YIELD_BEFORE_CONNECT */
#elif defined(CONFIG_NO_YIELD_BEFORE_CONNECT)
#undef CONFIG_YIELD_BEFORE_CONNECT
#endif

#if defined(CONFIG_YIELD_BEFORE_CONNECT) && (CONFIG_YIELD_BEFORE_CONNECT+0) == 0
#undef CONFIG_YIELD_BEFORE_CONNECT
#endif /* CONFIG_YIELD_BEFORE_CONNECT && (CONFIG_YIELD_BEFORE_CONNECT+0) == 0 */


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
#ifdef __CC__
#ifdef CONFIG_YIELD_BEFORE_CONNECT
#ifndef __task_tryyield_defined
#define __task_tryyield_defined 1
FUNDEF NOBLOCK_IF(!PREEMPTION_ENABLED())
unsigned int NOTHROW(KCALL task_tryyield)(void);
#endif /* !__task_tryyield_defined */
#if CONFIG_YIELD_BEFORE_CONNECT == 1
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                          \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
	} __WHILE0
#elif CONFIG_YIELD_BEFORE_CONNECT == 2
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                          \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
	} __WHILE0
#elif CONFIG_YIELD_BEFORE_CONNECT == 3
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                          \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
	} __WHILE0
#elif CONFIG_YIELD_BEFORE_CONNECT == 4
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                          \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
	} __WHILE0
#elif CONFIG_YIELD_BEFORE_CONNECT == 5
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                          \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
	} __WHILE0
#elif CONFIG_YIELD_BEFORE_CONNECT == 6
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                          \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
		if (task_tryyield() != 0) \
			break;                \
		__VA_ARGS__;              \
	} __WHILE0
#else /* CONFIG_YIELD_BEFORE_CONNECT == ... */
#define TASK_POLL_BEFORE_CONNECT(...)                            \
	do {                                                         \
		unsigned int __poll_count = CONFIG_YIELD_BEFORE_CONNECT; \
		do {                                                     \
			if (task_tryyield() != 0)                            \
				break;                                           \
			__VA_ARGS__;                                         \
		} while (--__poll_count);                                \
	} __WHILE0
#endif /* CONFIG_YIELD_BEFORE_CONNECT != ... */
#else /* CONFIG_YIELD_BEFORE_CONNECT */
#define TASK_POLL_BEFORE_CONNECT(...) (void)0
#endif /* !CONFIG_YIELD_BEFORE_CONNECT */
#endif /* __CC__ */


DECL_END
#endif /* CONFIG_USE_NEW_SIGNAL_API */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_NEWSIGNAL_H */
