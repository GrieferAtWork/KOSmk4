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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

#include <sched/pertask.h>

#include <hybrid/__assert.h>

#include <kos/jiffies.h>
#include <stdbool.h>

DECL_BEGIN

/* Declare support for signal-driven poll operations
 * >> bool pollread(MyType *self) {
 * >>     if (sync_canread(self))
 * >>         return true;
 * >>     task_connect_ghost(&self->m_signal);
 * >>     return unlikely(sync_canread(self)); // Re-check to prevent race condition
 * >> }
 */
#if defined(__cplusplus) && defined(__CC__)
#define __DEFINE_SYNC_POLL(T, _pollread, _pollwrite)                                                                                  \
	extern "C++" {                                                                                                                    \
	FORCELOCAL WUNUSED NONNULL((1)) __BOOL (KCALL sync_pollread)(T *__restrict self) THROWS(E_BADALLOC) { return _pollread(self); }   \
	FORCELOCAL WUNUSED NONNULL((1)) __BOOL (KCALL sync_pollwrite)(T *__restrict self) THROWS(E_BADALLOC) { return _pollwrite(self); } \
	}
#else /* __cplusplus && __CC__ */
#define __DEFINE_SYNC_POLL(T, _pollread, _pollwrite) /* nothing */
#endif /* !__cplusplus || !__CC__ */


#ifdef __CC__

struct task_connection;
struct task_connections;

#ifndef CONFIG_NO_SMP
/* A special (and very rarely seen) value for `struct sig::s_ptr' that
 * is used to indicate that another CPU is currently invoking `sig_send()',
 * and has removed the pending chain of connections, though has not yet
 * re-scheduled the remaining connections that will won't be signaled.
 * WARNING: You may only ever assign this value to `s_ptr' when you have
 *          previously disabled preemption, as the only reason why this
 *          could ever appear while inside of `sig_broadcast()' must remain
 *          another CPU having TEMPorarily LOCKed the connections chain.
 *          In this case you must deal with the lock by calling `task_pause()'
 *         (DON'T EVEN THINK about calling `task_yield()') though, in order
 *          to given that other CPU its best chances of releasing the temporary
 *          lock.
 *       -> Similarly, you are only allowed to re-enable preemption _AFTER_
 *          you have released this kind of lock.
 * Note that when SMP is disabled, or when only 1 core is online after preemption has
 * been disabled (`defined(CONFIG_NO_SMP) || (!PREEMPTION_ENABLED() && cpu_online_count <= 1)'),
 * this special locking value is unnecessary and not required, as it is sufficient to
 * simply disable preemption when wishing to pop a limited number of connections from `s_ptr'. */
#define SIG_TEMPLOCK ((struct task_connection *)-1)
#endif /* !CONFIG_NO_SMP */




/* Synchronous, automatic (and since KOS400 non-blocking when sending),
 * low-level scheduling mechanism.
 * A signal on its own should be seen as entirely state-less. It only
 * gains a state once a user starts to operate with it, allowing one
 * thread to wait for a signal to be delivered, while another thread
 * gains the ability to asynchronously wake another thread, who will
 * receive that wake-up synchronously.
 * Using signals, a simple locking mechanism can be implemented as
 * follows, with any other kind of possible locking mechanism possible
 * to be built on-top:
 * >> struct lock {
 * >>     struct sig   l_signal;
 * >>     unsigned int l_locked;
 * >> };
 * >>
 * >> bool try_acquire(struct lock *me) {
 * >>     return ATOMIC_CMPXCH(me->l_locked,0,1);
 * >> }
 * >>
 * >> void acquire(struct lock *me) {
 * >>     while (!try_acquire(me)) {
 * >>         task_connect(&me->l_signal);
 * >>         if (try_acquire(me)) {
 * >>             task_disconnectall();
 * >>             break;
 * >>         }
 * >>         task_waitfor();
 * >>     }
 * >> }
 * >>
 * >> void release(struct lock *me) {
 * >>     ATOMIC_WRITE(me->l_locked,0);
 * >>     sig_broadcast(&me->l_signal);
 * >> }
 * The above example could easily be extended to provide
 * functionality for polling, recursion, or better
 * performance by using `TASK_POLL_BEFORE_CONNECT()'
 * in `acquire()', or `sig_send()' in `release()'.
 */
struct sig {
	WEAK struct task_connection *s_ptr; /* [0..1] Atomic linked list of active connections. */
};
#define SIG_INIT     { 0 }
#define sig_init(x)  (void)((x)->s_ptr = 0)
#define sig_cinit(x) (void)(__hybrid_assert((x)->s_ptr == 0))


/* Send signal `self' to up to 1 connected threads
 * @return: true:  The signal was delivered to at least 1 non-ghost connection.
 * @return: false: No non-ghost connections could be reached. */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL sig_send)(struct sig *__restrict self);

/* Send signal to all connected threads
 * @return: true: The actual number of threads notified, not counting ghosts. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL sig_broadcast)(struct sig *__restrict self);

/* Alternative signal sender functions:
 *  - Operate the same way as their regular counterparts
 *  - Able to use a custom `sender' signal that is returned
 *    to the caller of `task_wait()' as the origin of the
 *    signal, rather than the signal that was actually used.
 *  - Be careful when using this, as improper use may result
 *    in unexpected behavior where `task_wait()' returns a
 *    signal to which the waiting task wasn't even connected,
 *    while in fact it really wasn't connected to it.
 *  - `sender' must not necessarily be a `struct sig *', but
 *    can also be an arbitrary data pointer or 32/64-bit data
 *    word. However the one thing that it is not allowed to be
 *    is a NULL-pointer, as that value is internally used to
 *    indicate a signal that hasn't been sent, yet.
 *  - This functionality hasn't gotten much use yet, however
 *    it is getting used by kernel-space RPC acknowledgement
 *    to indicate to user-RPCs that the thread did receive the
 *    RPC, however was unable to execute it as the RPC was
 *    scheduled past the point of no return, after which the
 *    thread will never again return to user-space (after an `exit()')
 *    In that case, the thread waiting for the RPC will read a
 *    sender signal not matching the expected value of the
 *    ack-signal, but the thread's join-signal, which is then
 *    interpreted as the thread's inability to serve further
 *    user-space RPCs. */
FUNDEF NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL sig_altsend)(struct sig *__restrict self, struct sig *sender);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(KCALL sig_altbroadcast)(struct sig *__restrict self, struct sig *sender);




struct task_connection {
	struct task_sigset                *tc_cons;    /* [0..1][lock(SET(PRIVATE),CLEAR(tc_signal))] Associated connections set. */
	struct sig                        *tc_signal;  /* [0..1][lock(SET(PRIVATE),CLEAR(.))] The connected signal
	                                                * NOTE: The lowest-order bit is used to indicate ghost connections. */
#define TASK_CONNECTION_DELIVERED      ((struct sig *)0)  /* Set once signal delivery has been completed. */
#define TASK_CONNECTION_DELIVERING     ((struct sig *)-1) /* Set while a signal is being delivered. */
#define TASK_CONNECTION_DISCONNECTING  ((struct sig *)-2) /* The signal is being disconnected. */
#define TASK_CONNECTION_DISCONNECTED   ((struct sig *)-3) /* The signal has been disconnected. */
	struct task_connection            *tc_signext; /* [0..1][const] Next connection made by `tc_signal'. */
	struct task_connection            *tc_connext; /* [0..1][const] Next connection made by the thread.
	                                                * NOTE: The lowest-order bit is used to indicate heap-allocated connections. */
};

struct task_sigset {
	struct task            *ts_thread; /* [0..1][const] The thread to wake upon signal delivery, or
	                                    *              `NULL' if the task is only receiving the signal
	                                    *               passively. */
	struct task_connection *ts_cons;   /* [0..1][lock(PRIVATE)] Chain of active connections. */
	struct sig             *ts_dlvr;   /* [0..1][lock(WRITE_ONCE,CLEAR(PRIVATE))] The signal that got delivered. */
};


/* Max number of signal connections guarantied to not invoke `kmalloc()'
 * and potentially throw exceptions, or serve RPC functions.
 * A value of ONE(1) would suffice, but a static buffer is mandatory
 * due to the fact that allocating a dynamic buffer (using `kmalloc()')
 * may need to acquire its own locks in case that new memory must be
 * vm_paged_map()-ed. In this case, when locking needs to be done, a logic
 * recursion can only be prevented if it is possible to use at least
 * one signal slot that is allocated statically (`task_connect()' uses
 * `task_push_connections()' to free up that static slot before calling
 * `kmalloc()'). */
#ifndef CONFIG_TASK_STATIC_CONNECTIONS
#define CONFIG_TASK_STATIC_CONNECTIONS  3
#endif /* !CONFIG_TASK_STATIC_CONNECTIONS */

struct task_connections {
	struct task_sigset      tc_signals;                                /* Task signal set. */
	struct task_connection  tc_static[CONFIG_TASK_STATIC_CONNECTIONS]; /* Statically allocated connections. */
	struct task_connection *tc_static_v; /* [1..1] Pointer to the previous/current vector of statically allocated connections. */
};


/* Push/pop the active set of connections.
 * NOTE: After having been pushed, the calling thread will appear to not be connected
 *       to anything. - Similarly, `task_popconnections()' may only be called after
 *       all connections made were disconnected again.
 *    -> Signals delivered in the mean time will then immediately be available. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_pushconnections)(struct task_connections *__restrict cons);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_popconnections)(struct task_connections *__restrict cons);


/* NOTE: It is valid to destroy a signal after it was broadcast, even before it
 *       has been received! - The following sequence of calls is valid:
 * >> struct sig *send;
 * >> struct sig t = SIG_INIT;
 * >> assert(!task_isconnected());
 * >> task_connect(&t);
 * >> assert(task_isconnected());
 * >> sig_broadcast(&t);
 * >> memset(&t, 0xcc, sizeof(t)); // Invalidate the signal
 * >> send = task_waitfor();       // Wait for the signal (will not access the signal's memory!)
 * >> assert(send == &t);          // The correct signal was send
 * This is quite important, since it allows one to poll any given object without
 * have to make sure that that object is still alive when task_waitfor() is called! */

/* Connect the calling thread to a given signal.
 * @throw: E_BADALLOC:   [task_connect[_ghost]] Insufficient memory (only when there are
 *                        at least `CONFIG_TASK_STATIC_CONNECTIONS' connections already). */
FUNDEF NONNULL((1)) void KCALL task_connect(struct sig *__restrict target) THROWS(E_BADALLOC);
FUNDEF NONNULL((1)) void KCALL task_connect_ghost(struct sig *__restrict target) THROWS(E_BADALLOC);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL task_connect_c)(struct task_connection *__restrict con, struct sig *__restrict target);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL task_connect_ghost_c)(struct task_connection *__restrict con, struct sig *__restrict target);

/* Disconnect a given connection */
FUNDEF NONNULL((1)) void NOTHROW(KCALL task_disconnect_c)(struct task_connection *__restrict con);

/* Remove all active signals.
 * In case one of them got delivered, return the signal that got. Otherwise, return `NULL' */
FUNDEF struct sig *NOTHROW(KCALL task_disconnectall)(void);

/* Check if the calling thread is connected to any signal. */
FUNDEF NOBLOCK WUNUSED ATTR_CONST bool NOTHROW(KCALL task_isconnected)(void);

/* Check if there is a signal to was delivered, disconnecting all
 * other connected signals if this was the case.
 * @return: NULL: No signal is available
 * @return: * :   The signal that was delivered. */
FUNDEF NOBLOCK struct sig *NOTHROW(KCALL task_trywait)(void);

struct timespec;

/* Wait for the first signal to be delivered,
 * disconnecting all connected signals thereafter.
 * NOTE: Prior to fully starting to block, this function will call `task_serve()'
 * @param: abs_timeout:  The global (s.a. `quantum_time()') timeout for the wait.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked.
 * @throw: * :          [task_waitfor] An error was thrown by an RPC function.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
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
FUNDEF struct sig *NOTHROW(FCALL task_waitfor_nx)(struct timespec const *abs_timeout DFL(__NULLPTR));

/* Same as `task_waitfor', but don't serve RPC functions, and return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
FUNDEF struct sig *NOTHROW(FCALL task_waitfor_norpc_nx)(struct timespec const *abs_timeout DFL(__NULLPTR));
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
 * >>     task_connect(&lock_signal);
 * >>     if unlikely(try_lock()) {
 * >>         // Prevent a race condition:
 * >>         //     Lock became available after the last
 * >>         //     check, but before a connection was made
 * >>         task_disconnectall();
 * >>         return true;
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
#else
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                                                         \
		unsigned int __poll_count = CONFIG_YIELD_BEFORE_CONNECT; \
		do {                                                     \
			if (task_tryyield() != 0)                            \
				break;                                           \
			__VA_ARGS__;                                         \
		} while (--__poll_count);                                \
	} __WHILE0
#endif
#else
#define TASK_POLL_BEFORE_CONNECT(...) (void)0
#endif
#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGNAL_H */
