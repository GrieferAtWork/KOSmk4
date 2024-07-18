/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_AIO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_AIO_H 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__preemption.h>
#include <hybrid/typecore.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sched/atomic-rwlock.h>
#endif /* !CONFIG_NO_SMP */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#include <libc/string.h>
#endif /* !NDEBUG && !NDEBUG_FINI */

#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

DECL_BEGIN

#ifdef __CC__

/* NOTE: Alright: I admit it: getting AIO right inside of drivers is hard.
 * However,  you can take a look at  these drivers, which use this design:
 *   - the Ne2k driver      /kos/src/kernel/modne2k  (async-job: yes)
 *   - the IDE/ATA driver   /kos/src/kernel/modide   (async-job: no)
 * To try and bring all of the information together, you may use the following flow-chart:
 *
 * ```
 *   ┌─── <ENTRY>
 *   │
 *   │                                      ┌────────────> [struct device]
 *   │                                      │              >> // [0..1][lock(ATOMIC)] Chain of scheduled AIO operations
 *   │                                      │              >> WEAK struct aio_handle *d_aio_pending;
 *   │                                      │              >> // [0..1][clear(ON_CANCEL)] The current AIO operation
 *   │                                      │              >> WEAK struct aio_handle *d_aio_current;
 *   │                                      │              >> // Signal broadcast when new AIO becomes available
 *   │                                      │              >> // Only needed if an async worker is used to start operations.
 *   │                                      │              >> struct sig              d_aio_avail;
 *   │                                      │       ┌────> APPEND(ent):
 *   │                                      │       │      >> do ent->ah_next = old = atomic_read(&d_aio_pending);
 *   │                                      │       │      >> while (!atomic_cmpxch_weak(&d_aio_pending, old, ent));
 *   │                                      │       │  ┌── >> if (!old) SIGNAL_PENDING_AIO_BECAME_AVAILABLE();
 *   │                                      │       │  │   RESTORE_ALL(ent):
 *   v                                      │       │  │   >> last = ent->ah_next[->ah_next...]; // While non-NULL
 * [AIO-USER-OPERATION]                     │       │  │   >> do last->ah_next = old = atomic_read(&d_aio_pending);
 * >> struct aio_handle_generic aio;        │       │  │   >> while (!atomic_cmpxch_weak(&d_aio_pending, old, ent));
 * >> aio_handle_generic_init(&aio);        │       │  ├── >> if (!old) SIGNAL_PENDING_AIO_BECAME_AVAILABLE();
 * >>                   ┌───────────────────┘       │  │   TAKEONE(bool (*pred)(struct aio_handle *ent)):
 * >>                   │                           │  │   >> ent = atomic_xch(&d_aio_pending, NULL);
 * >> async_operation(device, [...], &aio);  ──┐    │  │   >> for (r = ent; r && !(*pred)(r); r = r->ah_next);
 * >> TRY {                                    │    │  │   >> if (r) REMOVE_FROM_CHAIN(&ent, r);
 * >>     aio_handle_generic_await(&aio);      │    │  │   >> if (ent) RESTORE_ALL(ent);
 * >> } EXCEPT {                               │    │  │   >> return r;
 * >>     aio_handle_generic_fini(&aio);       │    │  │   REMOVE(ent):
 * >>     RETHROW();                           │    │  │   >> do {
 * >> }                                        │    │  │   >>     chain = atomic_xch(&d_aio_pending, NULL);
 * >> aio_handle_generic_fini(&aio);           │    │  │   >>     found = REMOVE_FROM_CHAIN(&chain, ent);
 *                                             │    │  │   >>     if (chain)
 *   ┌─────────────────────────────────────────┘    │  │   >>         RESTORE_ALL(chain);
 *   │                                              │  │   >> } while (!found);
 *   │                                              │  │
 *   │                                              │  └─> [SIGNAL_PENDING_AIO_BECAME_AVAILABLE(device)]
 *   │                                              │      NOTE: This part doesn't necessarily have to be implemented by
 *   │                                              │            an async-worker, so-long as the process of kick-starting
 *   │                                              │            the I/O operation doesn't take O(NUMBER_OF_IO_BYTES) long.
 *   │                                              │       In other words: DMA operations can be kick-started here, too.
 *   v                                              │       >> sig_broadcast(&device->d_aio_avail);
 * [async_operation(device, aio)]                   │                                   │
 * >> // Always need some COMMAND_DESCRIPTOR        └───────┐                           │
 * >> // The used id doesn't matter, though                 │                           │
 * >> aio->ah_data[0]    = incref(device);  ────────────────│───────────────────────────│──────────────┐
 * >> aio->ah_data[1]    = incref([COMMAND_DESCRIPTOR]);  ──│───────────────────────────│──────────┐   │
 * >> aio->ah_data[2..n] = ...;                             │                           │          │   │
 * >> aio_handle_init(aio, &device_async_aio_type);         │                           │          │   │
 * >> device->d_aio_pending.APPEND(aio);      │             │                           │          │   │
 *                             │              └─────────────│───────────────────────────│──────────│─┐ │
 *                             └────────────────────────────┘                           │          │ │ │
 *   ┌──────────────────────────────────────────────────────────────────────────────────┘          │ │ │
 *   v                                                                                             │ │ │
 * [ASYNC_WORKER(device)]                     ┌───> [async_connect(device)]                        │ │ │
 * >> struct async_worker_ops = {             │     >> task_connect_for_poll(&device->d_aio_avail);│ │ │
 * >>     .awo_connect = &async_connect, ─────┘                                                    │ │ │
 * >>     .awc_test    = &async_test, ────────────> [async_test(device)]                           │ │ │
 * >>     .awc_work    = &async_work, ────┐         >> return atomic_read(&device->d_aio_pending)  │ │ │
 * >> };                                  │         >>        != NULL;                             │ │ │
 *                                        │                                                        │ │ │
 *   ┌────────────────────────────────────┘                                                        │ │ │
 *   v                                                                                             │ │ │
 * [async_work(device)]                                                                            │ │ │
 * [ 0] >> for (;;) {                                                                              │ │ │
 * [ 1] >>     struct aio_handle *aio;                                                             │ │ │
 * [ 2] >>     [COMMAND_DESCRIPTOR] *cmd;   <──────────────────────────────────────────┬───────────┤ │ │
 * [ 3] >>     preemption_pushoff(&was);                                               │           │ │ │
 * [ 4] >>     // Take an AIO handle with a present command-descriptor                 │           │ │ │
 * [ 5] >>     // The command-descriptor is cleared during AIO-cancel!                 │   ┌───────│─┘ │
 * [ 6] >>     aio = device->d_aio_pending.TAKEONE([](ent) {                           │   │       │   │
 * [ 7] >>         // Inherit reference into `ent'                                     │   │ ┌─────│───┘
 * [ 8] >>         cmd = atomic_xch(&ent->ah_data[1], NULL);   <───────────────────────┤   │ │     │
 * [ 9] >>         return cmd != NULL;   <─────────────────────────────────────────────┤   │ │     │
 * [10] >>     });                                                                     │   │ │     │
 * [11] >>     atomic_write(&device->d_aio_current, aio);                              │   │ │     │
 * [12] >>     preemption_pop(&was);                                                   │   │ │     │
 * [13] >>     if (!aio) break;                                                        │   │ │     │
 * [14] >>     FINALLY_DECREF_LIKELY(cmd);   <─────────────────────────────────────────┤   │ │     │
 * [15] >>     // Allow cancelation between command-steps by testing `d_aio_current'   │   │ │     │
 * [16] >>     TRY {                                                                   │   │ │     │
 * [17] >>         while (atomic_read(&device->d_aio_current) != NULL) {               │   │ │     │
 * [18] >>             [COMMAND_DESCRIPTOR_DO_NEXT_STEP](cmd);   <─────────────────────┤   │ │     │
 * [19] >>             if ([COMMAND_DESCRIPTOR_FINISHED](cmd)) break;   <──────────────┘   │ │     │
 * [20] >>         }                                                                       │ │     │
 * [21] >>     } EXCEPT {                                                                  │ │     │
 * [22] >>         // Indicate AIO failure                                                 │ │     │
 * [23] >>         preemption_pushoff(&was);                                               │ │     │
 * [24] >>         aio = atomic_xch(&device->d_aio_current, NULL);                         │ │     │
 * [25] >>         if (aio) aio_handle_complete(aio, AIO_COMPLETION_FAILURE);              │ │     │
 * [26] >>         preemption_pop(&was);                                                   │ │     │
 * [27] >>         continue;                                                               │ │     │
 * [28] >>     }                                                                           │ │     │
 * [29] >>     // Indicate AIO success                                                     │ │     │
 * [30] >>     preemption_pushoff(&was);                                                   │ │     │
 * [31] >>     aio = atomic_xch(&device->d_aio_current, NULL);                             │ │     │
 * [32] >>     if (aio) aio_handle_complete(aio, AIO_COMPLETION_SUCCESS);                  │ │     │
 * [33] >>     else {                                                                      │ │     │
 * [34] >>         // Wait for [HWIO_CANCEL_CURRENT_OPERATION] in aio_cancel() to finish   │ │     │
 * [35] >>         [HWIO_WAIT_FOR_CANCEL_COMPLETION](device);                              │ │     │
 * [36] >>     }                                                                           │ │     │
 * [37] >>     preemption_pop(&was);                                                       │ │     │
 * [38] >> }                                                                               │ │     │
 *                                                                                         │ │     │
 *  ┌──────────────────────────────────────────────────────────────────────────────────────┘ │     │
 *  │                                                                                        │     │
 *  v                                                                                        │     │
 * [device_async_aio_type]               ┌───> [aio_fini(aio)]                               │     │
 * >> struct aio_handle_type = {         │     >> device = aio->ah_data[0];                  │     │
 * >>     .ht_fini     = &aio_fini,     ─┘     >> decref(device);           <────────────────┤     │
 * >>     .ht_cancel   = &aio_cancel,   ───┐                                                 │     │
 * >>     .ht_progress = &aio_progress  ─┐ │                                                 │     │
 * >> };                                 │ └─> [aio_cancel(aio)]                             │     │
 *                                       │     [ 0] >> device = aio->ah_data[0];   <─────────┘     │
 * ┌─────────────────────────────────────┘     [ 1] >> [COMMAND_DESCRIPTOR] *cmd;   <──────────────┤
 * │                                           [ 2] >> preemption_pushoff(&was);                   │
 * │                                           [ 3] >> cmd = atomic_xch(&aio->ah_data[1], NULL); <─┘
 * v                                           [ 4] >> if (cmd) {
 * [aio_progress(aio)]                         [ 5] >>     // Canceled before started
 * Optional, but in case of multi-step         [ 6] >>     decref_likely(cmd);
 * commands, this can easily be implemented    [ 7] >>     // Remove the entry from pending AIO. Having successfully
 * by keeping track of how many steps have     [ 8] >>     // cleared the command-pointer, we know that `async_work()'
 * already been completed, and how many        [ 9] >>     // hasn't gotten around to this AIO handle, yet.
 * are still left within the device itself,    [10] >>     d_aio_pending.REMOVE(ent);
 * alongside checking if `aio' matches the     [11] >>     preemption_pop(&was);
 * device's `d_aio_current' field.             [12] >>     goto do_cancel;
 *                                             [13] >> }
 *                                             [14] >> // If the cmd-pointer was already cleared, then the AIO operation is
 *                                             [15] >> // either currently in progress (i.e. the async-worker is executing
 *                                             [16] >> // `COMMAND_DESCRIPTOR_DO_NEXT_STEP()'), or the AIO operation was
 *                                             [17] >> // already completed or is/was canceled already.
 *                                             [18] >> if (atomic_cmpxch(&device->d_aio_current, aio, NULL)) {
 *                                             [19] >>     // Cancel the current operation on a hardware-level
 *                                             [20] >>     // Note that this function can assume that the async-worker thread
 *                                             [21] >>     // is currently inside of `[COMMAND_DESCRIPTOR_DO_NEXT_STEP]', and
 *                                             [22] >>     // will/has fall/en into `[HWIO_WAIT_FOR_CANCEL_COMPLETION]' shortly.
 *                                             [23] >>     [HWIO_CANCEL_CURRENT_OPERATION](device);
 *                                             [24] >>     preemption_pop(&was);
 *                                             [25] >>     goto do_cancel;
 *                                             [26] >> }
 *                                             [27] >> preemption_pop(&was);
 *                                             [28] >> return;
 *                                             [29] >>do_cancel:
 *                                             [30] >> aio_handle_complete(aio, AIO_COMPLETION_CANCEL);
 * ```
 *
 * HINT: SMP locks aren't required because `aio_handle_fini()' will
 *       wait  until the handle's completion function has returned!
 */


struct aio_handle;
struct aio_handle_stat {
	size_t hs_completed; /* Amount of units (usually bytes) currently completed. */
	size_t hs_total;     /* Total amount of units (usually bytes) that are entailed by the operation. */
};

struct aio_handle_type {
	/* [1..1] Finalizer for this AIO handle. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *ht_fini)(struct aio_handle *__restrict self);

	/* [1..1] Cancel execution of the given AIO operation.
	 * NOTE: This function is required to _immediately_ cancel the operation associated
	 *       with  the given  handle, so long  as that operation  hasn't yet completed.
	 *       If  the first holds  true, the associated handle  function must be invoked
	 *       with `AIO_COMPLETION_CANCEL' before this operator may return.
	 * WARNING: This callback may only be invoked _once_! */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *ht_cancel)(struct aio_handle *__restrict self);

	/* [0..1] An optional operator which can be used to query the operation progress
	 *        in order to determine how much has already been done, and how much is
	 *        still left to be done.
	 * @param: stat: Filled in by this operator.
	 * @return: * :  One of `AIO_PROGRESS_STATUS_*' */
	NOBLOCK NONNULL_T((1, 2)) unsigned int
	NOTHROW_T(KCALL *ht_progress)(struct aio_handle *__restrict self,
	                              struct aio_handle_stat *__restrict stat);
#define AIO_PROGRESS_STATUS_PENDING    0x0000 /* The operation is still pending execution. */
#define AIO_PROGRESS_STATUS_INPROGRESS 0x0001 /* The operation is currently being performed. */
#define AIO_PROGRESS_STATUS_COMPLETED  0x0002 /* The operation has finished (either due to being canceled, failing, or succeeding)
                                               * Note however that when this  value is returned, it  is not guarantied whether  or
                                               * not the completion function has already been called, or has already returned. */

	/* [0..1] An optional operator for AIO protocols that can consume/produce variable
	 *        amounts of data (e.g. the USB protocol).
	 *        For such cases, this operator returns the actual amount of transferred
	 *        data  (in  bytes)  once  AIO  operation  has  completed  successfully.
	 *        Calling this  operator at  any time  other than  after the  completion
	 *        function  was  called with  `AIO_COMPLETION_SUCCESS'  causes undefined
	 *        behavior. */
	NOBLOCK WUNUSED_T NONNULL_T((1)) size_t
	NOTHROW_T(KCALL *ht_retsize)(struct aio_handle *__restrict self);
};



/* Possible values for `aio_completion_t::status' */
#define AIO_COMPLETION_SUCCESS  1 /* AIO operation has successfully completed. */
#define AIO_COMPLETION_CANCEL   2 /* AIO operation was canceled manually. */
#define AIO_COMPLETION_FAILURE  3 /* AIO operation has failed.
                                   * When this  status  is  passed,  `THIS_EXCEPTION_DATA'
                                   * has been  filled with  more details  on what  exactly
                                   * has went wrong, at which  point it is the  callback's
                                   * job to take  that information  and do with  it as  it
                                   * pleases (usually propagating it to whoever is waiting
                                   * for the operation to be  completed, or to dump it  to
                                   * the system log when no one is waiting) */

/* AIO completion callback. Guarantied to always be invoked _exactly_
 * once for  each AIO  operation started  at any  point before  then.
 * NOTE: This callback is _always_ invoked with preemption  disabled!
 * NOTE:  This callback _must_ _always_ invoke `aio_handle_release()'
 * @param: self:   The associated AIO operations handle.
 *                 When this function is invoked,  this handle has already  been
 *                 unbound from the  AIO-capable device's chain  of pending  AIO
 *                 commands, meaning that this  function is also responsible  to
 *                 either pass ownership of `self' to some waiter, or to destroy
 *                `self' on its own.
 * @param: status: One of `AIO_COMPLETION_*', explaining how the operation ended. */
typedef NOBLOCK NOPREEMPT NONNULL_T((1)) void
NOTHROW_T(FCALL *aio_completion_t)(struct aio_handle *__restrict self,
                                   unsigned int status);

/* Number of pointers available for drivers
 * to store data inline within AIO handles. */
#define AIO_HANDLE_DRIVER_POINTER_COUNT 6
#define AIO_HANDLE_ALIGNMENT __SIZEOF_POINTER__


/* Value written  to `ah_next'  after an  AIO handle's  `ah_func' callback  returns.
 * This is  required  to  prevent  a  race condition  where  one  CPU  is  currently
 * calling `ah_func' while another CPU is inside of the AIO's cancel+fini  sequence.
 * In this case, the cancel+fini sequence would have no way of waiting for the first
 * CPU to return  from `ah_func'  before moving  on to  deallocate the  aio_handle's
 * backing memory. */
#define AIO_HANDLE_NEXT_COMPLETED ((struct aio_handle *)-1)

struct ATTR_ALIGNED(AIO_HANDLE_ALIGNMENT) aio_handle {
#define AIO_HANDLE_HEAD                                                                                    \
	struct aio_handle            *ah_next; /* [0..1][lock(INTERNAL)]  Pointer  to  the  next  AIO  handle. \
	                                        * This  field is only used internally in order to easily chain \
	                                        * pending  AIO  operations. Filled  in  during device-specific \
	                                        * handle init, and set to `AIO_HANDLE_NEXT_COMPLETED' in order \
	                                        * to  allow the AIO handle to be destroyed after `ah_func' has \
	                                        * returned */                                                  \
	struct aio_handle_type const *ah_type; /* [1..1][lock(WRITE_ONCE_DURING_INIT)]                         \
	                                        * AIO usage type (set by a driver implementing AIO             \
	                                        * such that operations can continue even after the             \
	                                        * associated callbacks return). */                             \
	aio_completion_t              ah_func; /* [1..1][const] AIO completion callback. */                    \
	void *ah_data[AIO_HANDLE_DRIVER_POINTER_COUNT]; /* Driver/device-specific handle data pointers. */
/**/
	AIO_HANDLE_HEAD
	/* ... Handle-specific data goes here. */
};

/* Callback that _must_ be  invoked from every possible  `ah_func'-callback.
 * After this callback  has been  invoked, the  async handle  itself may  no
 * longer be  accessed, and  some other  thread/cpu polling  the AIO  handle
 * to become completed can resume execution after this callback was invoked.
 *
 * Note that any other resources that may be released alongside the async
 * handle itself must be released _after_ this callback has been invoked.
 *
 * This  also means  that an implementation  of `ah_func' cannot  use the normal
 * sig_broadcast() function, but rather the special sig_broadcast_cleanup_nopr()
 * function that can be used to release the AIO handle before destroying threads
 * who's refcnt dropped to zero _after_ this callback was invoked.
 *
 * This is required to prevent deadlock scenarios such as the following:
 *      Setup: #1: Create a socket with an in-progress, async connect() operation
 *             #2: Terminate the process that created the socket
 *             #3: The socket's connect() operation completes
 *
 *      _asyncjob_main()
 *      aio_handle_complete_nopr()          // The connect() operation has completed
 *      aio_handle_generic_func()           // == ah_func  (note: this one must also invoke `aio_handle_release()')
 *      sig_broadcast()                     // Wrong usage here (s.a. `struct sig_cleanup_callback')
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
 *
 * Solution: AIO completion functions, while allowed to decref() arbitrary objects, are
 *           only allowed to do so after already having called  `aio_handle_release()',
 *           or when the object being decref'd doesn't actually end up being destroyed. */
#define aio_handle_release(self)                      \
	(__hybrid_atomic_store(&(self)->ah_next,          \
	                       AIO_HANDLE_NEXT_COMPLETED, \
	                       __ATOMIC_RELEASE))


/* No-op AIO handle type (intended for synchronous operations) */
DATDEF struct aio_handle_type aio_noop_type;

/* No-op  AIO handle type  (intended for synchronous operations)
 * Just like `aio_noop_type', but this one implements the retval
 * operator, which unconditionally returns  `(size_t)ah_data[0]' */
DATDEF struct aio_handle_type aio_noop_retval_type;


/* Initialize the given AIO handle with a type-specific v-table.
 * Must be called by all functions taking an `/ *out* / struct aio_handle *...'
 * argument for the purpose of initializing said AIO handle.
 * NOTE: After a call to this function,  the caller is responsible to  initialize
 *       the `self->ah_next' field with some non-AIO_HANDLE_NEXT_COMPLETED value. */
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_handle_init)(struct aio_handle *__restrict self,
                               struct aio_handle_type const *__restrict typ) {
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
	__libc_memset(&self->ah_next, 0xcc, sizeof(self->ah_next));
#endif /* !NDEBUG && !NDEBUG_FINI */
	self->ah_type = typ;
}

/* Helper wrapper for:
 * >> aio_handle_init(self, &aio_noop_type);
 * >> aio_handle_complete(self, status); */
#define aio_handle_init_noop(self, status)  \
	(aio_handle_init(self, &aio_noop_type), \
	 aio_handle_complete(self, status))

/* Helper wrapper for:
 * >> aio_handle_init(self, &aio_noop_retval_type);
 * >> self->ah_data[0] = (void *)(uintptr_t)(size_t)val;
 * >> aio_handle_complete(self, AIO_COMPLETION_SUCCESS); */
#define aio_handle_init_noop_retval(self, val)              \
	(aio_handle_init(self, &aio_noop_retval_type),          \
	 (self)->ah_data[0] = (void *)(uintptr_t)(size_t)(val), \
	 aio_handle_complete(self, AIO_COMPLETION_SUCCESS))


/* Finalize a fully initialized AIO handle.
 * WARNING: The caller must ensure that the AIO handle's completion  function
 *          was invoked prior to calling  this function. The simplest way  of
 *          doing this is by inserting a call to `aio_handle_cancel()' before
 *          a call to this function. */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_fini)(struct aio_handle *__restrict self) {
#ifndef CONFIG_NO_SMP
	/* Make sure that no other thread is still inside of `ah_func' */
	while (__hybrid_atomic_load(&self->ah_next, __ATOMIC_ACQUIRE) != AIO_HANDLE_NEXT_COMPLETED)
		__hybrid_preemption_tryyield();
#endif /* !CONFIG_NO_SMP */
	(*self->ah_type->ht_fini)(self);
}

/* Check if the given AIO handle's callback has already been invoked. */
LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL aio_handle_completed)(struct aio_handle const *__restrict self) {
	return __hybrid_atomic_load(&self->ah_next, __ATOMIC_ACQUIRE) == AIO_HANDLE_NEXT_COMPLETED;
}

/* Cancel  an   in-progress  or   finished  AIO   operation.
 * This function can be called any number of times,  however
 * additional invocations after the first one become no-ops.
 * NOTE: This function _must_ be called before `aio_handle_fini()'
 *       in  any path  where it is  unknown if the  AIO handle has
 *       already completed (this usually means  that it has to  be
 *       called in all EXCEPT-paths that finalize some handle) */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_cancel)(struct aio_handle *__restrict self) {
	if likely(!aio_handle_completed(self))
		(*self->ah_type->ht_cancel)(self);
}

/* ONLY CALL THIS FUNCTION FROM WITHIN DRIVERS!
 * Signal AIO completion and mark the AIO handle as  completed
 * by setting its ah_next field to `AIO_HANDLE_NEXT_COMPLETED'
 * WARNING: Any further access to any of the members of `self' becomes
 *          illegal after the first can to this function! As such, the
 *          semantics of this function as  far as the `self'  argument
 *          goes are `inherit(always)'
 * WARNING: It could already be implied by the previous  warning,
 *          however just to state it as clear as possible: _ONLY_
 *          call this function _ONCE_ for any given AIO handle!
 * @param: status: One of `AIO_COMPLETION_*' */
LOCAL NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(KCALL aio_handle_complete_nopr)(/*inherit(always)*/ struct aio_handle *__restrict self,
                                        unsigned int status) {
	__hybrid_assert(!__hybrid_preemption_ison());
	__hybrid_assert(!aio_handle_completed(self));
	/* Invoke the completion callback */
	(*self->ah_func)(self, status);
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_complete)(/*inherit(always)*/ struct aio_handle *__restrict self,
                                   unsigned int status) {
	__hybrid_preemption_flag_t was;
	/* Ensure that the call to the completion function, as well as the
	 * sub-sequent write of `AIO_HANDLE_NEXT_COMPLETED' to  `ah_next'.
	 * This must be done to guaranty SMP-ATOMIC NONBLOCK-semantics  in
	 * `aio_handle_fini()' */
	__hybrid_preemption_pushoff(&was);
	__hybrid_assert(!aio_handle_completed(self));
	/* Invoke the completion callback */
	(*self->ah_func)(self, status);
	__hybrid_preemption_pop(&was);
}






/* AIO execution order:
 * >> struct aio_handle_generic handle;
 * >> aio_handle_generic_init(&handle);
 * >> // NOTE: Don't put `block_device_aread_sector()' inside of the TRY!
 * >> //       Initialization done by `aio_handle_generic_init()' is only
 * >> //       preliminary, and only the initialization done by actually
 * >> //       using the AIO handle with some the async I/O function will
 * >> //       actually initialize it to the point where it must be
 * >> //       finalized.
 * >> //       If you were to call `aio_handle_generic_fini(...)' on a
 * >> //       handle that hasn't actually be used with any sort of async
 * >> //       I/O function, you'd end up with undefined behavior!
 * >> block_device_aread_sector(dev, phys_dest, virt_dest, 2, 0, &handle);
 * >> aio_handle_generic_await(&handle);
 */

/* A general purpose AIO handle that can be used for synchronizing for completion. */
struct ATTR_ALIGNED(AIO_HANDLE_ALIGNMENT) aio_handle_generic
#ifdef __cplusplus
	: aio_handle
#endif /* __cplusplus */
{
#ifndef __cplusplus
	AIO_HANDLE_HEAD
#endif /* !__cplusplus */
	struct sig            hg_signal; /* Signal broadcast when `ah_func' is called. */
	unsigned int          hg_status; /* Acknowledged AIO completion status (or 0 if still in progress) */
	struct exception_data hg_error;  /* [valid_if(hg_status == AIO_COMPLETION_FAILURE)] AIO failure error. */
};

#define aio_handle_generic_fini(self) \
	(aio_handle_fini(self),           \
	 sig_broadcast_for_fini(&(self)->hg_signal))

/* Callback for `aio_handle_generic' */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL aio_handle_generic_func)(struct aio_handle *__restrict self,
                                       unsigned int status);

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_generic_init)(struct aio_handle_generic *__restrict self) {
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
	__libc_memset(self, 0xcc, sizeof(*self));
#endif /* !NDEBUG && !NDEBUG_FINI */
	self->ah_func   = &aio_handle_generic_func;
	self->hg_status = 0;
	sig_init(&self->hg_signal);
}

#define aio_handle_generic_hascompleted(self) \
	(__hybrid_atomic_load(&(self)->hg_status, __ATOMIC_ACQUIRE) != 0)

/* Check if the AIO operation failed, and propagate the error if it did. */
__COMPILER_EIDECLARE(NONNULL((1)), void, , KCALL, aio_handle_generic_checkerror,
                     (struct aio_handle_generic *__restrict self) THROWS(E_IOERROR, ...), {
	if unlikely(self->hg_status == AIO_COMPLETION_FAILURE) {
		__libc_memcpy(&THIS_EXCEPTION_DATA,
		              &self->hg_error, sizeof(self->hg_error));
		except_throw_current();
	}
})

/* Connect to the given AIO handle. */
#define aio_handle_generic_connect_for_poll(self) \
	task_connect_for_poll(&(self)->hg_signal)
__COMPILER_EIDECLARE(NONNULL((1)), bool, , KCALL, aio_handle_generic_poll,
                     (struct aio_handle_generic *__restrict self) THROWS(E_BADALLOC), {
	if (aio_handle_generic_hascompleted(self))
		return true;
	aio_handle_generic_connect_for_poll(self);
	return aio_handle_generic_hascompleted(self);
})


/* Wait for an AIO handle to be completed. If the calling thread is interrupted,
 * or the given `abs_timeout' expires, the AIO operation will have already  been
 * canceled by the time this function returns. */
#ifdef TRY
__COMPILER_EIDECLARE(NONNULL((1)), bool, , KCALL, aio_handle_generic_waitfor_or_cancel,
                     (struct aio_handle_generic *__restrict self,
                      ktime_t abs_timeout DFL(KTIME_INFINITE)) THROWS(E_WOULDBLOCK, ...), {
	__hybrid_assert(!task_wasconnected());
	while (!aio_handle_generic_hascompleted(self)) {
		TRY {
			aio_handle_generic_connect_for_poll(self);
			if unlikely(aio_handle_generic_hascompleted(self)) {
				task_disconnectall();
				break;
			}
			if (!task_waitfor(abs_timeout)) {
				aio_handle_cancel(self);
				return false;
			}
		} EXCEPT {
			aio_handle_cancel(self);
			RETHROW();
		}
	}
	return true;
})
#else /* TRY */
FUNDEF NONNULL((1)) bool KCALL
aio_handle_generic_waitfor_or_cancel(struct aio_handle_generic *__restrict self,
                                     ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_WOULDBLOCK, ...);
#endif /* !TRY */

/* Convenience wrapper for:
 * >> result = aio_handle_generic_waitfor_or_cancel(self, abs_timeout);
 * >> if (result)
 * >>     aio_handle_generic_checkerror(self);
 * >> return result;
 *
 * This function will do everything necessary to:
 * - Ensure completion of `self'
 * - Cancel `self' in case the calling thread is interrupted, or `abs_timeout' expires
 * - When there was no timeout, check if `self' encountered an error, and propagate it
 * - Finalize the AIO controller `self' */
__COMPILER_EIDECLARE(NONNULL((1)), void, , KCALL, aio_handle_generic_await,
                     (struct aio_handle_generic *__restrict self)
                     THROWS(E_WOULDBLOCK, ...), {
	aio_handle_generic_waitfor_or_cancel(self, KTIME_INFINITE);
	aio_handle_generic_checkerror(self);
})
__COMPILER_EIDECLARE(NONNULL((1)), bool, , KCALL, aio_handle_generic_await_timed,
                     (struct aio_handle_generic *__restrict self, ktime_t abs_timeout)
                     THROWS(E_WOULDBLOCK, ...), {
	bool result = aio_handle_generic_waitfor_or_cancel(self, abs_timeout);
	if likely(result)
		aio_handle_generic_checkerror(self);
	return result;
})
#ifdef __cplusplus
extern "C++" {
__COMPILER_EIREDIRECT(NONNULL((1)), bool, , KCALL, aio_handle_generic_await,
                      (struct aio_handle_generic *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK, ...),
                      aio_handle_generic_await_timed, {
	return aio_handle_generic_await_timed(self, abs_timeout);
})
} /* extern "C++" */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_aio_handle_generic_await_1 (aio_handle_generic_await)
#define __PRIVATE_aio_handle_generic_await_2 (aio_handle_generic_await_timed)
#define aio_handle_generic_await(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_aio_handle_generic_await_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* ... */





struct aio_multihandle;
struct refcountable;
struct ATTR_ALIGNED(AIO_HANDLE_ALIGNMENT) aio_handle_multiple
#ifdef __cplusplus
	: aio_handle
#endif /* __cplusplus */
{
#ifndef __cplusplus
	AIO_HANDLE_HEAD
#endif /* __cplusplus */
#define AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED_IS_ZERO 1
#define AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED   ((struct aio_multihandle *)0)  /* Unused entry */
#define AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE ((struct aio_multihandle *)-1) /* Completed/Canceled entry */
	struct aio_multihandle  *hg_controller; /* [0..1][lock(WRITE_ONCE(AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE))]
	                                         * Associated controller. Set to `AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE'
	                                         * after this handle's operation has completed. */
	REF struct refcountable *hg_obj;        /* [0..1][const] An object that is decref'd upon completion of this handle. */
};

/* Callback for `aio_handle_multiple' */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL aio_handle_multiple_func)(struct aio_handle *__restrict self,
                                        unsigned int status);

/* Callback for `aio_multihandle' (called under the same context as `aio_completion_t') */
typedef NOBLOCK NOPREEMPT NONNULL_T((1)) void
NOTHROW_T(FCALL *aio_multiple_completion_t)(struct aio_multihandle *__restrict self,
                                            unsigned int status);
#define AIO_MULTIHANDLE_IVECLIMIT  2    /* Max number of inline-allocated handles. */
#define AIO_MULTIHANDLE_XVECLIMIT  8    /* Max number of heap-allocated handles per extension. */

#define AIO_MULTIHANDLE_STATUS_RELEASED   0x20000000 /* FLAG: The multi-handle was released. */
#define AIO_MULTIHANDLE_STATUS_FAILED     0x40000000 /* FLAG: Set once if an operation unrelated to I/O failed. */
#define AIO_MULTIHANDLE_STATUS_ALLRUNNING 0x80000000 /* FLAG: Set once all commands have been issued. */
#define AIO_MULTIHANDLE_STATUS_STATUSMASK 0x0f000000 /* Mask for the most significant run status. */
#define AIO_MULTIHANDLE_STATUS_STATUSSHFT 24         /* Shift for the most significant run status. */
#define AIO_MULTIHANDLE_STATUS_RUNMASK    0x00ffffff /* Mask for the number of running handles. */


struct aio_multihandle_extension {
	struct aio_multihandle_extension *ame_next; /* [0..1][owned] Next extension. */
	struct aio_handle_multiple        ame_handles[AIO_MULTIHANDLE_XVECLIMIT]; /* Associated handles. */
};

struct aio_multihandle {
	aio_multiple_completion_t  am_func;    /* [1..1][const] AIO completion callback. */
	REF struct refcountable   *am_obj;     /* [0..1] When non-NULL incref'd and passed to newly created AIO handles.
	                                        * Can be used for additional cleanup  (such as DMA locks) when  specific
	                                        * sub-sets of handles complete. */
	WEAK uintptr_t             am_status;  /* Set of `AIO_MULTIHANDLE_STATUS_*'. */
	struct exception_data      am_error;   /* [lock(WRITE_ONCE)] AIO failure error. */
	struct aio_multihandle_extension
	                          *am_ext;     /* [0..1][owned] Vector of additional, heap-allocated handles. */
	struct aio_handle_multiple am_ivec[AIO_MULTIHANDLE_IVECLIMIT];
	                                       /* Small inline vector for the first couple of handles. */
	/* ... Additional data can go here. */
};

/* Must be called from `aio_multihandle_init::func' in order
 * to release the  multi-handle and allow  it to be  free'd.
 *
 * This is the multihandle analog for `aio_handle_release()' */
#define aio_multihandle_release(self)                    \
	(__hybrid_atomic_or(&(self)->am_status,              \
	                    AIO_MULTIHANDLE_STATUS_RELEASED, \
	                    __ATOMIC_SEQ_CST))


/* Initialize the given AIO multi-handle */
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_multihandle_init)(struct aio_multihandle *__restrict self,
                                    aio_multiple_completion_t func) {
	unsigned int i;
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
	__libc_memset(&self->am_error, 0xcc, sizeof(self->am_error));
	__libc_memset(self->am_ivec, 0xcc, sizeof(self->am_ivec));
#endif /* !NDEBUG && !NDEBUG_FINI */
	self->am_obj    = __NULLPTR;
	self->am_func   = func;
	self->am_status = (uintptr_t)AIO_COMPLETION_SUCCESS << AIO_MULTIHANDLE_STATUS_STATUSSHFT;
	self->am_ext    = __NULLPTR;
	for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i)
		self->am_ivec[i].hg_controller = AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED;
}

/* Finalize the given AIO multi-handle */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_fini)(struct aio_multihandle *__restrict self);


/* Handle the current exception using the given AIO multi-handle.
 * NOTE:  This function will also call `aio_multihandle_cancel()' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_fail)(struct aio_multihandle *__restrict self);

/* Allocate handles for the purpose of AIO completion.
 * WARNING: Don't free a handle after you already started using it in the context of an AIO parameter.
 * NOTE: `aio_multihandle_allochandle()' calls `aio_multihandle_fail()' upon
 *       error, before returning  propagating an error  / returning  `NULL'. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct aio_handle *KCALL
aio_multihandle_allochandle(struct aio_multihandle *__restrict self)
		THROWS(E_BADALLOC);
FUNDEF WUNUSED NONNULL((1)) struct aio_handle *
NOTHROW(KCALL aio_multihandle_allochandle_nx)(struct aio_multihandle *__restrict self);

/* Cancel   all   currently  running   handles   of  `self'
 * NOTE: May be called multiple times without causing harm. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_cancel)(struct aio_multihandle *__restrict self);

/* Indicate that no further handles will be allocated, meaning that `self->am_func'
 * is  now allowed to be called once  all initiated operations have finished (which
 * may be immediately).
 * WARNING: This function should not be called more than once! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_done)(struct aio_multihandle *__restrict self);



/* AIO  multihandle   syncing  execution   order:
 * >> struct aio_multihandle_generic multihandle;
 * >> aio_multihandle_generic_init(&multihandle);
 * >> TRY {
 * >>     block_device_aread_sector(dev, dst1, 2, 0, aio_multihandle_allochandle(&multihandle));
 * >>     block_device_aread_sector(dev, dst2, 2, 8, aio_multihandle_allochandle(&multihandle));
 * >> } EXCEPT {
 * >>     aio_multihandle_fail(&multihandle);
 * >> }
 * >> aio_multihandle_done(&multihandle);
 * >> RAII_FINALLY { aio_multihandle_generic_fini(&multihandle); };
 * >> aio_multihandle_generic_await(&multihandle);
 */

/* Generic  multi-handle  that  is  capable  of  being  used  as  a  signal   source.
 * This is to `aio_multihandle' the same that `aio_handle_generic' is to `aio_handle' */
struct aio_multihandle_generic
#ifdef __cplusplus
    : aio_multihandle
#define _aio_multihandle_generic_base_ /* nothing */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct aio_multihandle mg_base;   /* The underlying multi-handle. */
#define _aio_multihandle_generic_base_ mg_base.
#endif /* !__cplusplus */
	struct sig             mg_signal; /* Signal broadcast upon completion. */
};

FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL aio_multihandle_generic_func)(struct aio_multihandle *__restrict self,
                                            unsigned int status);

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_generic_init)(struct aio_multihandle_generic *__restrict self) {
#ifdef __cplusplus
	aio_multihandle_init(self, &aio_multihandle_generic_func);
#else /* __cplusplus */
	aio_multihandle_init(&self->mg_base, &aio_multihandle_generic_func);
#endif /* !__cplusplus */
	sig_init(&self->mg_signal);
}

#define aio_multihandle_generic_fini(self) \
	aio_multihandle_fini(self)

/* NOTE: Returns `false' if `aio_multihandle_done' hasn't been called, yet. */
#define aio_multihandle_generic_hascompleted(self)                                                                                \
	(((self)->_aio_multihandle_generic_base_ am_status & (AIO_MULTIHANDLE_STATUS_ALLRUNNING | AIO_MULTIHANDLE_STATUS_RUNMASK)) == \
	 AIO_MULTIHANDLE_STATUS_ALLRUNNING)


/* Check if the AIO operation failed, and propagate the error if it did. */
__COMPILER_EIDECLARE(NONNULL((1)), void, , KCALL, aio_multihandle_generic_checkerror,
                     (struct aio_multihandle_generic *__restrict self) THROWS(E_IOERROR, ...), {
	if unlikely((self->_aio_multihandle_generic_base_ am_status & AIO_MULTIHANDLE_STATUS_STATUSMASK) ==
	           ((uintptr_t)AIO_COMPLETION_FAILURE << AIO_MULTIHANDLE_STATUS_STATUSSHFT)) {
		__libc_memcpy(&THIS_EXCEPTION_DATA,
		              &self->_aio_multihandle_generic_base_ am_error,
		              sizeof(self->_aio_multihandle_generic_base_ am_error));
		except_throw_current();
	}
})

/* Connect to the given AIO multihandle. */
#define aio_multihandle_generic_connect_for_poll(self) \
	task_connect_for_poll(&(self)->mg_signal)
__COMPILER_EIDECLARE(NONNULL((1)), bool, , KCALL, aio_multihandle_generic_poll,
                     (struct aio_multihandle_generic *__restrict self) THROWS(E_BADALLOC), {
	if (aio_multihandle_generic_hascompleted(self))
		return true;
	aio_multihandle_generic_connect_for_poll(self);
	return aio_multihandle_generic_hascompleted(self);
})


/* Wait for an AIO handle to be completed. If the calling thread is interrupted,
 * or the given `abs_timeout' expires, the AIO operation will have already  been
 * canceled by the time this function returns. */
#ifdef TRY
__COMPILER_EIDECLARE(NONNULL((1)), bool, , KCALL, aio_multihandle_generic_waitfor_or_cancel,
                     (struct aio_multihandle_generic *__restrict self,
                      ktime_t abs_timeout DFL(KTIME_INFINITE)) THROWS(E_WOULDBLOCK, ...), {
	__hybrid_assert(!task_wasconnected());
	while (!aio_multihandle_generic_hascompleted(self)) {
		TRY {
			aio_multihandle_generic_connect_for_poll(self);
			if unlikely(aio_multihandle_generic_hascompleted(self)) {
				task_disconnectall();
				break;
			}
			if (!task_waitfor(abs_timeout)) {
				aio_multihandle_cancel(self);
				return false;
			}
		} EXCEPT {
			aio_multihandle_cancel(self);
			RETHROW();
		}
	}
	return true;
})
#else /* TRY */
FUNDEF NONNULL((1)) bool KCALL
aio_multihandle_generic_waitfor_or_cancel(struct aio_multihandle_generic *__restrict self,
                                     ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_WOULDBLOCK, ...);
#endif /* !TRY */

/* Convenience wrapper for:
 * >> result = aio_multihandle_generic_waitfor_or_cancel(self, abs_timeout);
 * >> if (result)
 * >>     aio_multihandle_generic_checkerror(self);
 * >> return result;
 *
 * This function will do everything necessary to:
 * - Ensure completion of `self'
 * - Cancel `self' in case the calling thread is interrupted, or `abs_timeout' expires
 * - When there was no timeout, check if `self' encountered an error, and propagate it
 * - Finalize the AIO controller `self' */
__COMPILER_EIDECLARE(NONNULL((1)), void, , KCALL, aio_multihandle_generic_await,
                     (struct aio_multihandle_generic *__restrict self)
                     THROWS(E_WOULDBLOCK, ...), {
	aio_multihandle_generic_waitfor_or_cancel(self, KTIME_INFINITE);
	aio_multihandle_generic_checkerror(self);
})
__COMPILER_EIDECLARE(NONNULL((1)), bool, , KCALL, aio_multihandle_generic_await_timed,
                     (struct aio_multihandle_generic *__restrict self, ktime_t abs_timeout)
                     THROWS(E_WOULDBLOCK, ...), {
	bool result = aio_multihandle_generic_waitfor_or_cancel(self, abs_timeout);
	if likely(result)
		aio_multihandle_generic_checkerror(self);
	return result;
})
#ifdef __cplusplus
extern "C++" {
__COMPILER_EIREDIRECT(NONNULL((1)), bool, , KCALL, aio_multihandle_generic_await,
                      (struct aio_multihandle_generic *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK, ...),
                      aio_multihandle_generic_await_timed, {
	return aio_multihandle_generic_await_timed(self, abs_timeout);
})
} /* extern "C++" */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_aio_multihandle_generic_await_1 (aio_multihandle_generic_await)
#define __PRIVATE_aio_multihandle_generic_await_2 (aio_multihandle_generic_await_timed)
#define aio_multihandle_generic_await(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_aio_multihandle_generic_await_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* ... */




/* Allocate and return a special AIO handle that can be used just like any other,
 * however will clean-up itself after  the usual init+complete+fini cycle of  any
 * given AIO handle. This allows the caller to use this handle to detach themself
 * from any async-operation such that the  operation will either succeed or  fail
 * at an arbitrary point in the future, potentially long after the caller started
 * the operation. To-be used as follows:
 * >> void nic_background_send(struct nicdev const *__restrict self,
 * >>                          struct nic_packet *__restrict packet) {
 * >>     struct aio_handle *aio;
 * >>     aio = aio_handle_async_alloc();
 * >>     TRY {
 * >>         // This call essentially behaves as `inherit(on_success)' for `aio'
 * >>         (*self->nd_ops.nd_send)(self, packet, aio);
 * >>     } EXCEPT {
 * >>         aio_handle_async_free(aio);
 * >>         RETHROW();
 * >>     }
 * >> }
 * NOTE: When  the AIO operation completes with `AIO_COMPLETION_FAILURE', and
 *       `func' was NULL, then an error message is written to the system log.
 * @param: func: [0..1] An optional function that is invoked upon completion. */
FUNDEF ATTR_RETNONNULL WUNUSED struct aio_handle *KCALL
aio_handle_async_alloc(aio_completion_t func DFL(__NULLPTR)) THROWS(E_BADALLOC);

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_async_free)(struct aio_handle *__restrict self);

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_AIO_H */
