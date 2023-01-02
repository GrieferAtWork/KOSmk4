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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIG_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIG_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

/*
 * KOS Signal explanation:
 *
 * - Signals themself are  low-level, state-less synchronization  primitives
 *   that can be used to implement arbitrarily complex higher-level objects,
 *   such as mutexes, semaphores, condition-variables, ..., _anything_
 * - Whatever state a signal may have in some arbitrary context, it only
 *   gains  this  state  indirectly by  being  used in  a  specific way.
 *
 * Basic example:
 * >> PRIVATE struct sig mysig = SIG_INIT;
 * >>
 * >> PRIVATE void connect(void) {
 * >>     task_connect(&mysig);
 * >> }
 * >>
 * >> PRIVATE void wait(void) {
 * >>     task_waitfor();
 * >> }
 * >>
 * >> PRIVATE void post(void) {
 * >>     sig_send(&mysig);
 * >> }
 *
 * Synchronization here happens as follows:
 *   - Whenever  a thread calls `connect()', it will become attached to `mysig',
 *     such that another thread sending that signal (as by `post()') will notify
 *     the original thread that called `connect()' of this condition.
 *   - For  this purpose, it  doesn't matter if the  original thread that called
 *     `connect()' has already called `wait()' (and began blocking), or is still
 *     busy doing other things, but is planning to call `wait()' eventually
 *   - The `task_waitfor()' function (when  eventually called) will then  cause
 *     the  calling thread to  suspend execution until one  of the signals that
 *     its  caller is connected to has been send (but note that if one of those
 *     signals is send before `task_waitfor()' is called, then `task_waitfor()'
 *     will never block to begin with, but return immediately)
 *   - The moment that `task_waitfor()' returns, _all_ connections that  the
 *     calling  thread had made  in the past will  have already been severed
 *     (to be even more precise: a connection is severed before `sig_send()'
 *     returns, with the  only exception being  signal completion  functions
 *     that call `sig_completion_reprime()')
 *
 * How to use `struct sig', and what `interlocked' means:
 *   - If you think of dos's  `InterlockedIncrement' functions, or similar, I'm  sorry
 *     to disappoint you, but that function should have been called `AtomicIncrement',
 *     as it has nothing to do with interlocked behavior.
 *   - Performing something interlocked means that  an operation happens in a  specific
 *     context where certain events can be monitored/handled, similar to how this would
 *     happen during a transaction (s.a. /kos/src/kernel/modrtm).
 *   - For simplicity, consider the following example:
 *     [ 1] PRIVATE bool       is_ready     = false;
 *     [ 2] PRIVATE struct sig became_ready = SIG_INIT;
 *     [ 3]
 *     [ 4] PRIVATE void wait_until_ready(void) {
 *     [ 5]     task_connect(&became_ready);
 *     [ 6]     if (ATOMIC_READ(is_ready)) {
 *     [ 7]         task_disconnectall();
 *     [ 8]         return;
 *     [ 9]     }
 *     [10]     task_waitfor();
 *     [11] }
 *     [12]
 *     [13] PRIVATE void become_ready(void) {
 *     [14]     ATOMIC_WRITE(is_ready, true);
 *     [15]     sig_broadcast(&became_ready);
 *     [16] }
 *     Here, the read from `is_ready' on line #6 is interlocked with the  async
 *     monitoring  of `became_ready'  that began on  line #5. As  such, line #6
 *     knows that when `is_ready' isn't `true' yet, the calling thread will get
 *     notified after it becomes so (s.a. line #15) As such, all possible  race
 *     conditions are handled here:
 *        case #1: `ATOMIC_WRITE(is_ready, true);' happens before `task_connect(&became_ready)':
 *                  - `sig_broadcast(&became_ready)' has no-one to notify
 *                  - The caller of `wait_until_ready()' will notice this in line #6
 *                  - The `wait_until_ready()' function never starts blocking
 *                 Note that since this case is usually the most likely one, another test
 *                 of the `is_ready'  condition usually also  happens before the  initial
 *                 connect. Though since no connect()  will have happened at that  point,
 *                 such a test wouldn't be interlocked, and can only ever serve to  speed
 *                 up the case  where an object  is already ready  from the get-go.  Such
 *                 models are  referred  to  as test+connect+test,  whereas  the  minimal
 *                 requirement for race-less synchronization is connect+test.
 *        case #2: `ATOMIC_WRITE(is_ready, true);' happens after `task_connect(&became_ready)',
 *                 but before `ATOMIC_READ(is_ready)'.
 *                  - Line #6 will notice this, and disconnect from the `became_ready'
 *                    signal once again, and the waiting thread never starts blocking.
 *        case #3: `ATOMIC_WRITE(is_ready, true);' happens after `if (ATOMIC_READ(is_ready))'
 *                  - In this case, the caller of `wait_until_ready()' will end up inside of
 *                    `task_waitfor()', which will return as soon as line #15 gets executed.
 *                  - Because by this point, the waiting thread has already been connected
 *                    to the `became_ready' signal, it doesn't matter if `sig_broadcast()'
 *                    is  called  before,  or  after  `task_waitfor();'.  In  both  cases,
 *                    `task_waitfor()'  will not return  before `sig_broadcast()' has been
 *                    called, but will return as soon as it has been called.
 */



DECL_BEGIN

/* Signal reception priority order:
 *
 * In order to improve performance, signals sent through `struct sig'
 * may not always reach all  waiting / some specific waiting  thread.
 *
 * sig_send():
 *    #1: Try to send a signal to the longest-living connection that
 *        wasn't established as a poll-connection, and return `true'
 *    #2: If no such connection exists, but there are still (alive)
 *        connections (iow: only poll-connections remain), randomly
 *        select one of the  poll-based connections and signal  it.
 *        (Note that  "random" here  may not  actually required  to
 *        be random at all, but, in  fact, is allowed to depend  to
 *        the  order  in  which  connections  had  been  enqueued).
 *        Continue with step #1
 *    #4: If no (alive) connections are left, return `false'
 *
 * sig_broadcast():
 *    #1: If there is any  (alive) connection (irregardless of  that
 *        connection  being non-poll-, or poll-based), simply signal
 *        that connection. If the connection was non-poll-based, the
 *        value  to-be returned by sig_broadcast() is incremented by
 *        one.
 *        Continue with step #1
 *    #2: If no (alive) connections are left, return the number of
 *        signaled non-poll connections.
 *
 * Normal (non-poll) connections:
 *   - task_connect()
 *   - sig_connect_completion()
 *   - sig_completion_reprime(for_poll: false)
 *
 * Poll connections:
 *   - task_connect_for_poll()
 *   - sig_connect_completion_for_poll()
 *   - sig_completion_reprime(for_poll: true)
 *
 */



/*[[[config CONFIG_TASK_STATIC_CONNECTIONS! = 3
 * Max  number of signal  connections guarantied to not
 * invoke `kmalloc()' and potentially throw exceptions.
 * ]]]*/
#ifndef CONFIG_TASK_STATIC_CONNECTIONS
#define CONFIG_TASK_STATIC_CONNECTIONS 3
#endif /* !CONFIG_TASK_STATIC_CONNECTIONS */
/*[[[end]]]*/



/* `struct task_connection' offsets */
#define OFFSET_TASK_CONNECTION_SIG     0
#define OFFSET_TASK_CONNECTION_CONNEXT __SIZEOF_POINTER__
#define OFFSET_TASK_CONNECTION_SIGNEXT (__SIZEOF_POINTER__ * 2)
#define OFFSET_TASK_CONNECTION_CONS    (__SIZEOF_POINTER__ * 3)
#define OFFSET_TASK_CONNECTION_STAT    (__SIZEOF_POINTER__ * 3)
#define SIZEOF_TASK_CONNECTION         (__SIZEOF_POINTER__ * 4)
#define ALIGNOF_TASK_CONNECTION        __ALIGNOF_POINTER__

/* `struct task_connections' offsets */
#define OFFSET_TASK_CONNECTIONS_PREV   0
#define OFFSET_TASK_CONNECTIONS_THREAD __SIZEOF_POINTER__
#define OFFSET_TASK_CONNECTIONS_CON    (__SIZEOF_POINTER__ * 2)
#define OFFSET_TASK_CONNECTIONS_DLVR   (__SIZEOF_POINTER__ * 3)
#define OFFSET_TASK_CONNECTIONS_STATIC (__SIZEOF_POINTER__ * 4)
#define SIZEOF_TASK_CONNECTIONS        ((__SIZEOF_POINTER__ * 4) + (SIZEOF_TASK_CONNECTION * CONFIG_TASK_STATIC_CONNECTIONS))
#define ALIGNOF_TASK_CONNECTIONS       __ALIGNOF_POINTER__


#ifdef __CC__

struct sig;
struct task;
struct task_connection;
struct task_connections;

struct sig {
#ifdef CONFIG_NO_SMP
	struct task_connection *s_con; /* [0..1][chain(->tc_signext)]
	                                * [lock(INSERT(ATOMIC))]
	                                * [lock(REMOVE(!PREEMPTION_ENABLED() && IF_SMP(SMP_LOCK(tc_sig))))]
	                                * Chain of established connections.
	                                * In SMP, the  least significant bit  is a lock  that needs to  be
	                                * held when connections are removed.  Note however that this  lock
	                                * may only be  acquired when  preemption is disabled,  as it  must
	                                * be guarantied that the lock always becomes available while doing
	                                * a `while (!trylock()) task_pause()'-loop. */
#else /* CONFIG_NO_SMP */
	union {
		struct task_connection *s_con; /* [0..1][chain(->tc_signext)]
		                                * [lock(INSERT(ATOMIC))]
		                                * [lock(REMOVE(!PREEMPTION_ENABLED() && IF_SMP(SMP_LOCK(tc_sig))))]
		                                * Chain of established connections.
		                                * In SMP, the  least significant bit  is a lock  that needs to  be
		                                * held when connections are removed.  Note however that this  lock
		                                * may only be  acquired when  preemption is disabled,  as it  must
		                                * be guarantied that the lock always becomes available while doing
		                                * a `while (!trylock()) task_pause()'-loop. */
		uintptr_t               s_ctl; /* Signal control word */
	};
#endif /* !CONFIG_NO_SMP */
};

#ifndef CONFIG_NO_SMP
#define SIG_CONTROL_SMPLOCK 0x0001 /* SMP lock bit for `struct sig::s_ctl' */
#endif /* !CONFIG_NO_SMP */

#ifdef CONFIG_NO_SMP
#define SIG_INIT       { __NULLPTR }
#else /* CONFIG_NO_SMP */
#define SIG_INIT       { { __NULLPTR } }
#endif /* !CONFIG_NO_SMP */
#define sig_init(x)    (void)((x)->s_con = __NULLPTR)
#define sig_cinit(x)   __hybrid_assert((x)->s_con == __NULLPTR)
#define sig_isempty(x) ((x)->s_con == __NULLPTR)



/* Send signal `self' to exactly 1 connected thread
 *  - The receiver is the thread who's connection has been pending the longest.
 *  - Note the special interaction of this function with poll-based connections.
 *    For  more  information  on  this  subject,  see `task_connect_for_poll()'.
 * @return: true:  A waiting thread was signaled.
 * @return: false: The given signal didn't have any active connections. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_send)(struct sig *__restrict self);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sig_altsend)(struct sig *self,
                           struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) __BOOL
NOTHROW(FCALL sig_send_nopr)(struct sig *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sig_altsend_nopr)(struct sig *self,
                                struct sig *sender);

/* Send signal `self' to the given thread `target'
 *  - Behaves  the same as `sig_send()', however signal completion
 *    callbacks  and task_connection's that point to threads other
 *    than `target' are silently skipped, and the function behaves
 *    as  though anything other  than true thread-connections made
 *    by `target' didn't exist.
 * @return: true:  The specified `target' was connected, and the signal
 *                 was delivered as expected.
 * @return: false: The specified `target' wasn't connected to `self'. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_sendto)(struct sig *__restrict self,
                          struct task *__restrict target);
FUNDEF NOBLOCK NONNULL((1, 2, 3)) __BOOL
NOTHROW(FCALL sig_altsendto)(struct sig *self,
                             struct task *__restrict target,
                             struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sig_sendto_nopr)(struct sig *__restrict self,
                               struct task *__restrict target);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) __BOOL
NOTHROW(FCALL sig_altsendto_nopr)(struct sig *self,
                                  struct task *__restrict target,
                                  struct sig *sender);

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
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_sendmany)(struct sig *__restrict self,
                            size_t maxcount);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altsendmany)(struct sig *self,
                               struct sig *sender,
                               size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_sendmany_nopr)(struct sig *__restrict self,
                                 size_t maxcount);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altsendmany_nopr)(struct sig *self,
                                    struct sig *sender,
                                    size_t maxcount);

/* Send signal to all connected threads.
 * @return: * : The actual number of threads notified,
 *              not  counting  poll-based connections. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast)(struct sig *__restrict self);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast)(struct sig *self,
                                struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_nopr)(struct sig *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast_nopr)(struct sig *self,
                                     struct sig *sender);

/* Same  as the regular `sig_broadcast' function, but must be used if
 * `self'  is being broadcast one last time prior to being destroyed.
 * When these functions are used, signal completion callbacks are not
 * allowed to make  use of  `sig_completion_reprime()', but  instead,
 * that function will return `false' and do nothing.
 * @return: * : The actual number of threads notified,
 *              not  counting  poll-based connections. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_for_fini)(struct sig *__restrict self);
FUNDEF NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast_for_fini)(struct sig *self,
                                         struct sig *sender);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_for_fini_nopr)(struct sig *__restrict self);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_altbroadcast_for_fini_nopr)(struct sig *self,
                                              struct sig *sender);

/* Same as `sig_broadcast()', but impersonate `caller', and
 * wake up thread through use of `task_wake_as()'. The same
 * rules apply, meaning that the (true) caller must  ensure
 * that their CPU won't change,  and that `caller' is  also
 * running as part of their CPU. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_as_nopr)(struct sig *__restrict self,
                                     struct task *__restrict caller);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) size_t
NOTHROW(FCALL sig_broadcast_as_for_fini_nopr)(struct sig *__restrict self,
                                              struct task *__restrict caller);


/* Cleanup function  which may  be scheduled  for invocation  before internal  resources
 * are  released and  post-completion callbacks  defined by  signal completion functions
 * are run.  This is  a  special mechanism  that is  required  to prevent  certain  race
 * conditions,  and  should be  used  in situations  where  a signal  is  kept allocated
 * through use  of an  SMP-lock which  must  be released  once the  `struct sig'  itself
 * no longer needs to be used, but  before any possible extended callbacks are  invoked,
 * as may be the result of decref()-ing woken threads (which may end up being destroyed,
 * and  consequently destroying a  whole bunch of other  things, including open handles)
 *
 * An example of a race condition prevented by this is:
 *      _asyncjob_main()
 *      aio_handle_complete_nopr()          // The connect() operation has completed
 *      aio_handle_generic_func()           // == ah_func  (note: this one must also invoke `aio_handle_release()')
 *      sig_broadcast()                     // !!! Wrong usage here
 *          decref_unlikely(target_thread)  // This actually ends up destroying `target_thread'
 *      task_destroy()
 *      fini_this_handle_manager()
 *      handman_destroy()
 *      handle_socket_decref()
 *      socket_destroy()
 *          decref_likely(self->sk_ncon.axr_obj)
 *      socket_connect_aio_destroy()
 *          aio_handle_generic_fini()
 *              aio_handle_fini()
 *              >> Deadlock here, since aio_handle_fini() can only return once
 *                 aio_handle_release()  has been called for the attached AIO.
 * The solution is to invoke `aio_handle_release(self)' from inside `scc_cb'
 *
 * NOTE: The cleanup callback itself gets invoked immediately after all internal
 *       SMP-lock have been  released (but before  preemption is re-enabled,  or
 *       post-exec signal completion callbacks are invoked)
 */
struct sig_cleanup_callback;
struct sig_cleanup_callback {
	/* [1..1] Cleanup callback. */
	NOBLOCK NOPREEMPT NONNULL_T((1)) void
	NOTHROW_T(FCALL *scc_cb)(struct sig_cleanup_callback *self);
	/* User-data goes here. */
};

/* Same as `sig_broadcast()', but invoke a given `cleanup' prior to doing any  other
 * kind of cleanup, but after having released all internal SMP-locks. May be used to
 * release further SMP-locks  which may have  been used to  guard `self' from  being
 * destroyed (such  as calling  `aio_handle_release()' when  sending a  signal  from
 * inside of an AIO completion function)
 * Note that all of these functions guaranty that `callback' is invoked exactly once. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_broadcast_cleanup_nopr)(struct sig *__restrict self,
                                          struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL sig_broadcast_as_cleanup_nopr)(struct sig *__restrict self,
                                             struct task *__restrict caller,
                                             struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL sig_broadcast_for_fini_cleanup_nopr)(struct sig *__restrict self,
                                                   struct sig_cleanup_callback *__restrict cleanup);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL sig_broadcast_as_for_fini_cleanup_nopr)(struct sig *__restrict self,
                                                      struct task *__restrict caller,
                                                      struct sig_cleanup_callback *__restrict cleanup);

/* Check if the given signal has viable recipients.
 * This     includes     poll-based    connections. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sig_iswaiting)(struct sig *__restrict self);

/* Count the # of viable recipients of the given signal.
 * This includes poll-based connections. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL sig_numwaiting)(struct sig *__restrict self);


/* Connection status values (is-connected is every `x' with `!TASK_CONNECTION_STAT_CHECK(x)')
 *
 * This initial `!TASK_CONNECTION_STAT_CHECK(x)'-state can transition to:
 *   - TASK_CONNECTION_STAT_SENT:      Some  thread  called `sig_send(tc_sig)',  and the
 *                                     associated `struct task_connection' was selected.
 *   - TASK_CONNECTION_STAT_BROADCAST: Some thread called `sig_broadcast(tc_sig)'.
 *
 * Also note that any recipient can only  ever have at most 1 connection  with
 * a state of `TASK_CONNECTION_STAT_SENT' or `TASK_CONNECTION_STAT_BROADCAST',
 * though this invariant is only true  when interlocked with the SMP-locks  of
 * all attached signals. (s.a. `tcs_dlvr') */
#define TASK_CONNECTION_STAT_BROADCAST           0x0000 /* Signal was broadcast (forwarding is unnecessary if ignored)
                                                         * In this state, `tc_sig' must be considered to be `[valid_if(false)]', and the
                                                         * thread that originally connected to  the signal mustn't directly  re-connect.
                                                         * When all (past) connections have entered this state, the associated signal is
                                                         * allowed to have it's backing memory be free'd!
                                                         * NOTE: THIS STATUS WILL NEVER APPEAR IN SIGNAL CONNECTION CHAINS! */
#define TASK_CONNECTION_STAT_SENT                0x0002 /* Signal was sent, and must be  forwarded if not received via  `task_waitfor()'
                                                         * In this state, the attached signal must  not be free'd, though this case  can
                                                         * easily be handled by broadcasting signals one last time before disconnecting,
                                                         * which can safely be done with `sig_broadcast_for_fini()'.
                                                         * Transitions to (with [lock(SMP_LOCK(tc_sig))]):
                                                         *   - TASK_CONNECTION_STAT_BROADCAST: Any thread called `sig_broadcast()'
                                                         *                                     on the attached signal. */
#ifndef CONFIG_NO_SMP
#define TASK_CONNECTION_STAT_FLOCK               0x0001 /* SMP lock (must be held when removing the associated connection from the signal) */
#endif /* !CONFIG_NO_SMP */
#define TASK_CONNECTION_STAT_FFINI               0x0002 /* For signal completion functions only: Signal was finalized. */
#define TASK_CONNECTION_STAT_FPOLL               0x0002 /* This is a POLL-based connection. */
#define TASK_CONNECTION_STAT_FMASK               0x0003 /* Mask of flags */
#define TASK_CONNECTION_STAT_COMPLETION          0x0004 /* Special type: This is actually a `struct sig_completion' */
#define TASK_CONNECTION_STAT_COMPLETION_FOR_POLL 0x0006 /* Special type: This is actually a `struct sig_completion' established for polling */

#define TASK_CONNECTION_STAT_ISDEAD(x) ((uintptr_t)(x) <= 1) /* Connection has been disconnected. (`tc_sig' may point to deallocated memory) */
#define TASK_CONNECTION_STAT_ISDONE(x) ((uintptr_t)(x) <= 3) /* Signal has been delivered. */
#define TASK_CONNECTION_STAT_ISSPEC(x) ((uintptr_t)(x) <= 7) /* Connection requires special treatment. */
#define TASK_CONNECTION_STAT_ISCOMP(x) ((uintptr_t)(x) >= 4) /* Connection is a `struct sig_completion' (assumes that `TASK_CONNECTION_STAT_ISSPEC() == true') */
#define TASK_CONNECTION_STAT_ISPOLL(x) ((uintptr_t)(x) & TASK_CONNECTION_STAT_FPOLL) /* Connection is poll-based. */
#define TASK_CONNECTION_STAT_ASCONS(x) ((struct task_connections *)((uintptr_t)(x) & ~3)) /* When `!TASK_CONNECTION_STAT_ISSPEC(x)', return the underlying `struct task_connections' */

struct task_connection {
	struct sig                  *tc_sig;     /* [1..1][const] The connected signal. */
	struct task_connection      *tc_connext; /* [0..1][lock(THIS_TASK)] Next connection established by the caller. */
	struct task_connection      *tc_signext; /* [0..1][lock(!PREEMPTION_ENABLED() && IF_SMP(SMP_LOCK(tc_sig)))]
	                                          * Next connection for the same signal. */
	union {
		struct task_connections *tc_cons; /* [1..1] Attached connection set/connection status.
		                                   * TASK_CONNECTION_STAT_FPOLL is set in case of a poll-connection. */
		WEAK uintptr_t           tc_stat; /* Connection status (one of `TASK_CONNECTION_STAT_*'). */
	};
};


#if CONFIG_TASK_STATIC_CONNECTIONS < 2
#error "Need at least 2 statically allocatable connections per task!"
#endif /* CONFIG_TASK_STATIC_CONNECTIONS < 2 */

struct task_connections {
	struct task_connections *tcs_prev;   /* [0..1][lock(PRIVATE(THIS_TASK))]
	                                      * [(!= NULL) == (this == &this_root_connections)]
	                                      * Previous set of active connections. */
	WEAK struct task        *tcs_thread; /* [0..1][lock(PRIVATE(THIS_TASK))]
	                                      * The thread to wake upon signal delivery. (may also be `NULL')
	                                      * This  field  is  usually  `NULL'  for  all  connection   sets
	                                      * `!= FORTASK(tcs_thread, this_connections)',  and  is  set  as
	                                      * equal  to  `THIS_TASK' for  `PERTASK(this_connections)'. Note
	                                      * that it is  guarantied that this  task-pointer remains  valid
	                                      * from the point of view  of potentially attached signal,  even
	                                      * after this field may be set to NULL/non-NULL, for as long  as
	                                      * the actual,  underlying  thread  no  longer  has  any  active
	                                      * connections.   (i.e.   has   called   `task_disconnectall()') */
	struct task_connection  *tcs_con;    /* [0..1][chain(->tc_connext)][lock(PRIVATE(THIS_TASK))]
	                                      * Chain of active connections. */
	struct sig              *tcs_dlvr;   /* [0..1][lock(WRITE_ONCE, CLEAR(PRIVATE))]
	                                      * The first  signal  that  got  delivered. */
	struct task_connection   tcs_static[CONFIG_TASK_STATIC_CONNECTIONS];
	                                     /* [*.in_use_if(.tc_sig != NULL)][lock(PRIVATE(THIS_TASK))]
	                                      * Statically allocated connections. Any connection that belongs
	                                      * to  this connections set, but points outside of this array is
	                                      * allocated dynamically using `kmalloc()', and as such, must be
	                                      * freed by `kfree()' */
};

/* Root connections set. */
DATDEF ATTR_PERTASK struct task_connections this_root_connections;
#define THIS_ROOT_CONNECTIONS (&PERTASK(this_root_connections))

/* [1..1][lock(PRIVATE(THIS_TASK))]  Current   set   of   in-use   connections.
 * Most of the time, this will simply point to `PERTASK(this_root_connections)' */
DATDEF ATTR_PERTASK struct task_connections *this_connections;
#define THIS_CONNECTIONS PERTASK_GET(this_connections)


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
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_pushconnections)(struct task_connections *__restrict cons);
FUNDEF NOBLOCK ATTR_RETNONNULL struct task_connections *
NOTHROW(FCALL task_popconnections)(void);




/* Connect the calling thread to a given signal.
 * NOTE: It  the caller was already connected to `target', a second connection
 *       will be established, and `task_disconnect()' must be called more than
 *       once. However, aside  from this, having  multiple connections to  the
 *       same signal has no other adverse side-effects.
 * NOTE: When  the signal  test expression is  able to throw  an exception, the
 *       caller of this function is  responsible to disconnect from the  signal
 *       afterwards. However, exceptions that may be thrown by `task_waitfor()'
 *       always guaranty that _all_ established connections have been  removed.
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
 * @throw: E_BADALLOC: Insufficient  memory  (only  when there  are  at least
 *                     `CONFIG_TASK_STATIC_CONNECTIONS' connections already). */
FUNDEF NONNULL((1)) void FCALL
task_connect(struct sig *__restrict target)
		THROWS(E_BADALLOC);

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
FUNDEF NONNULL((1)) void FCALL
task_connect_for_poll(struct sig *__restrict target)
		THROWS(E_BADALLOC);


/* Disconnect from a specific signal `target'
 * WARNING: If `target' was already  send to the calling  thread
 *          before it could  be disconnected  by this  function,
 *          the calling  thread will  continue  to remain  in  a
 *          signaled state, such  that the next  call to one  of
 *          the signal receive functions (e.g. `task_waitfor()')
 *          will not block.
 * @return: true:  Disconnected from `target'
 * @return: false: You weren't actually connected to `target' */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL task_disconnect)(struct sig *__restrict target);

/* Disconnect from all connected signals.
 * Signals with a state of `TASK_CONNECTION_STAT_SENT' will be forwarded. */
FUNDEF NOBLOCK void
NOTHROW(FCALL task_disconnectall)(void);

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
FUNDEF NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_receiveall)(void);

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
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_wasconnected)(void);

/* Check if the calling thread was connected to the given signal.
 * Always returns `false' when `target == NULL'. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_wasconnected_to)(struct sig const *target);

#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL
NOTHROW(FCALL task_wasconnected)(struct sig const *target)
		ASMNAME("task_wasconnected_to");
} /* extern "C++" */
#endif /* __cplusplus */


/* Check if there is a signal that was delivered,
 * disconnecting all other  connected signals  if
 * this was the case.
 * @return: NULL: No signal is available.
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
FUNDEF NOBLOCK WUNUSED struct sig *
NOTHROW(FCALL task_trywait)(void);

/* Wait for the first signal to be delivered, unconditionally
 * disconnecting   all    connected    signals    thereafter.
 * NOTE: Prior to fully starting to block, this function will call `task_serve()'
 * @param: abs_timeout:  The `ktime()' timeout for the wait.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 * @throw: * :           [task_waitfor] An error was thrown by an RPC function.
 *                       NOTE: In this case, `task_disconnectall()' will have been called.
 * @return: NULL: No signal  has  become  available  (never  returned
 *                when `KTIME_INFINITE' is passed for `abs_timeout').
 * @return: * :   The signal that was delivered (for `sig_altsend', the "sender" argument) */
FUNDEF BLOCKING struct sig *FCALL
task_waitfor(ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);

/* Same as `task_waitfor', but don't serve RPC functions. */
FUNDEF BLOCKING struct sig *FCALL
task_waitfor_norpc(ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_WOULDBLOCK);

/* Same as `task_waitfor', but only service NX RPCs, and return `NULL'
 * if there are pending RPCs that  are allowed to throw exception,  or
 * if preemption was disabled, and the operation would have blocked. */
FUNDEF BLOCKING WUNUSED struct sig *
NOTHROW(FCALL task_waitfor_nx)(ktime_t abs_timeout DFL(KTIME_INFINITE));

/* Same as  `task_waitfor',  but  don't serve  RPC  functions,  and  return
 * `NULL' if preemption was disabled, and the operation would have blocked. */
FUNDEF BLOCKING WUNUSED struct sig *
NOTHROW(FCALL task_waitfor_norpc_nx)(ktime_t abs_timeout DFL(KTIME_INFINITE));

#ifndef __sigset_t_defined
#define __sigset_t_defined
struct __sigset_struct;
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/* Same as `task_waitfor()', but uses `task_serve_with_sigmask()' instead of `task_serve()' */
FUNDEF BLOCKING NONNULL((1)) struct sig *FCALL
task_waitfor_with_sigmask(sigset_t const *__restrict sigmask,
                          ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);

#ifdef BUILDING_KERNEL_CORE
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_fix_task_connections)(struct task *__restrict self);
#endif /* BUILDING_KERNEL_CORE */

#endif /* __CC__ */


/*[[[config CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT: int = 4
 * Configuration option for standard synchronization  primitives.
 * Before connecting to a signal, try to yield a couple of  times
 * to try and get other threads to release some kind of lock,  as
 * `task_yield()' is a much faster operation than task_connect()+
 * task_waitfor(). Doing this may improve performance, especially
 * on single-core machines.
 * Note however that this option does not affect the behavior of
 * low-level  `struct sig' objects, but instead primitives found
 * in <sched/[...].h>, such as `struct mutex',  `struct rwlock',
 * `struct semaphore' and `struct shared_rwlock'
 * NOTE: The number that this is defined to describes the
 *       max  number of times `task_yield()' is attempted
 *       (implementing a kind-of spin-locking mechanism),
 *       before a signal is actually connected.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#undef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#define CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT 0
#elif !defined(CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT)
#define CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT 4
#elif (CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT + 0) <= 0
#undef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#define CONFIG_NO_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#define CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT 0
#endif /* ... */
/*[[[end]]]*/


/* Helper macro to implement spin-locking before connecting a signal:
 * >> while (!try_lock()) {
 * >>     TASK_POLL_BEFORE_CONNECT({
 * >>         if (try_lock())
 * >>             return true;
 * >>     });
 * >>     assert(!task_wasconnected());
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
#ifdef CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT
#ifndef __task_tryyield_defined
#define __task_tryyield_defined
FUNDEF NOBLOCK_IF(!PREEMPTION_ENABLED())
unsigned int NOTHROW(KCALL task_tryyield)(void);
#endif /* !__task_tryyield_defined */
#if CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 1
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 2
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 3
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 4
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 5
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#elif CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == 6
#define TASK_POLL_BEFORE_CONNECT(...) \
	do {                              \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
		if (task_tryyield() != 0)     \
			break;                    \
		__VA_ARGS__;                  \
	}	__WHILE0
#else /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT == ... */
#define TASK_POLL_BEFORE_CONNECT(...)                                             \
	do {                                                                          \
		unsigned int __poll_count = CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT; \
		do {                                                                      \
			if (task_tryyield() != 0)                                             \
				break;                                                            \
			__VA_ARGS__;                                                          \
		} while (--__poll_count);                                                 \
	}	__WHILE0
#endif /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT != ... */
#else /* CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT */
#define TASK_POLL_BEFORE_CONNECT(...) (void)0
#endif /* !CONFIG_KERNEL_SCHED_NUM_YIELD_BEFORE_CONNECT */
#endif /* __CC__ */


/************************************************************************/
/* SIGNAL WAITING HELPER MACROS                                         */
/************************************************************************/
#define _task_waituntil_ex_small(wait_if_false_expr, _connect, _task_waitfor) \
	do {                                                                      \
		_connect;                                                             \
		if ((wait_if_false_expr)) {                                           \
			task_disconnectall();                                             \
			break;                                                            \
		}                                                                     \
		_task_waitfor;                                                        \
	}	__WHILE1
#define _task_waituntil_ex_fast(wait_if_false_expr, _connect, _task_waitfor) \
	do {                                                                     \
		if ((wait_if_false_expr))                                            \
			break;                                                           \
		_connect;                                                            \
		if ((wait_if_false_expr)) {                                          \
			task_disconnectall();                                            \
			break;                                                           \
		}                                                                    \
		_task_waitfor;                                                       \
	}	__WHILE1
#ifdef __OPTIMIZE_SIZE__
#define _task_waituntil_ex _task_waituntil_ex_small
#else /* __OPTIMIZE_SIZE__ */
#define _task_waituntil_ex _task_waituntil_ex_fast
#endif /* !__OPTIMIZE_SIZE__ */

/* Wait for a given signal while/until a given expression becomes true. */
#define task_waituntil(signal, wait_if_false_expr)             _task_waituntil_ex(wait_if_false_expr, task_connect(signal), task_waitfor())
#define task_waitwhile(signal, wait_if_true_expr)              task_waituntil(signal, !(wait_if_true_expr))
#define task_waituntil_norpc(signal, wait_if_false_expr)       _task_waituntil_ex(wait_if_false_expr, task_connect(signal), task_waitfor_norpc())
#define task_waitwhile_norpc(signal, wait_if_true_expr)        task_waituntil_norpc(signal, !(wait_if_true_expr))
#define task_waituntil_small(signal, wait_if_false_expr)       _task_waituntil_ex_small(wait_if_false_expr, task_connect(signal), task_waitfor())
#define task_waitwhile_small(signal, wait_if_true_expr)        task_waituntil_small(signal, !(wait_if_true_expr))
#define task_waituntil_norpc_small(signal, wait_if_false_expr) _task_waituntil_ex_small(wait_if_false_expr, task_connect(signal), task_waitfor_norpc())
#define task_waitwhile_norpc_small(signal, wait_if_true_expr)  task_waituntil_norpc_small(signal, !(wait_if_true_expr))
#define task_waituntil_fast(signal, wait_if_false_expr)        _task_waituntil_ex_fast(wait_if_false_expr, task_connect(signal), task_waitfor())
#define task_waitwhile_fast(signal, wait_if_true_expr)         task_waituntil_fast(signal, !(wait_if_true_expr))
#define task_waituntil_norpc_fast(signal, wait_if_false_expr)  _task_waituntil_ex_fast(wait_if_false_expr, task_connect(signal), task_waitfor_norpc())
#define task_waitwhile_norpc_fast(signal, wait_if_true_expr)   task_waituntil_norpc_fast(signal, !(wait_if_true_expr))


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIG_H */
