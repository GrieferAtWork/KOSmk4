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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include "rpc.h"

DECL_BEGIN

/* Flags for `struct rpc_entry::re_kind'
 * HINT (relation of flags/functions in the sense of semantics):
 *   == INTERNAL =======    == KERNEL-API ===========    == USER-API ====================
 *   RPC_KIND_INTERRUPT     TASK_USER_RPC_FINTR          ~RPC_SCHEDULE_FLAG_NOINTERRUPT
 *   RPC_KIND_USER_SYNC     TASK_USER_RPC_FSYNC          RPC_SCHEDULE_SYNC, ~RPC_SCHEDULE_ASYNC
 *   RPC_KIND_NONSYSCALL    TASK_USER_RPC_FNONSYSCALL    RPC_SCHEDULE_FLAG_NONSYSCALL
 *   RPC_KIND_NOTHROW       TASK_USER_RPC_FNOTHROW
 *                          <task_waitfor(re_done)>      RPC_SCHEDULE_FLAG_WAITFORSTART
 *                          TASK_RPC_FWAITFOR            RPC_SCHEDULE_FLAG_WAITSMPACK
 *                          TASK_RPC_FDONTWAKE           RPC_SCHEDULE_FLAG_DONTWAKE
 *                          TASK_RPC_FHIGHPRIO           RPC_SCHEDULE_FLAG_HIGHPRIO
 *                          TASK_RPC_FLOWPRIO            RPC_SCHEDULE_FLAG_LOWPRIO
 */
#define RPC_KIND_SYNC            0x0000 /* Synchronous RPC */
#define RPC_KIND_USER            0x0001 /* User RPC (service before returning to user-space) */
#define RPC_KIND_INTERRUPT       0x0002 /* Interrupting user RPC (throw an `E_INTERRUPT_USER_RPC') */
#define RPC_KIND_USER_INTR       0x0003 /* Interrupting user RPC (== RPC_KIND_USER | RPC_KIND_INTERRUPT) */
#define RPC_KIND_USER_SYNC       0x0004 /* Synchronous user-level RPC (Only service before user-space, and after a call to `task_serve()') */
#define RPC_KIND_USER_INTR_SYNC  0x0007 /* Synchronous user-level RPC (== RPC_KIND_USER | RPC_KIND_INTERRUPT | RPC_KIND_USER_SYNC) */
#define RPC_KIND_MASK            0x000f /* Mask for the RPC kind. */
#define RPC_KIND_NOTHROW         0x0010 /* FLAG: Non-throwing RPC */
#define RPC_KIND_NONSYSCALL      0x0400 /* FLAG: (for `RPC_KIND_USER_INTR_SYNC'): The RPC may be serviced for reasons other than `TASK_RPC_REASON_SYSCALL' */
#define RPC_KIND_CANSERVE        0x0800 /* FLAG: (for `RPC_KIND_USER_INTR_SYNC'): The thread did invoke `task_serve()' (set internally ) */

#ifdef __CC__
struct rpc_entry {
	struct rpc_entry *re_next; /* [0..1][const] Next pending RPC function. */
	task_rpc_t        re_func; /* [1..1][const][valid_if(!RPC_KIND_SRPC)] RPC function. */
	void             *re_arg;  /* [?..?][const] RPC argument. */
	uintptr_t         re_kind; /* [const] The kind of RPC (One of `RPC_KIND_*'). */
};


/* Allocate an RPC entry for later delivery without having to deal with the possibility
 * of a bad allocation at that later point in time. (s.a. `task_deliver_rpc()')
 * These functions behave identical to their `task_schedule_*' counterparts from <sched/rpc.h>,
 * except that the caller is not required to specify the eventual target thread just yet.
 * NOTE: Prior to commiting an RPC allocation by one of these functions through `task_deliver_rpc()',
 *       the caller is free to make use of the returned RPC's `re_next' field for whatever purpose
 *       they deem useful, allowing the caller to allocate a number of RPCs at once, without
 *       having to set up a secondary vector for storing them before using them.
 *    -> The main purpose of these APIs is to provide a means of pre-allocating synchronous
 *       RPC descriptors beforehand, allowing them to later be used in a scenario where code
 *       would no longer be capable of dealing with a bad allocation error that should normally
 *       arise if the regular `task_schedule_*' functions were to be used.
 * NOTE: The *_nx variants return `NULL' if the allocation failed. */
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_user_rpc)(task_rpc_t func,
                            void *arg DFL(__NULLPTR),
                            uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_USER_RPC_FNORMAL),
                            gfp_t rpc_gfp DFL(GFP_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED ATTR_MALLOC NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_user_rpc_nx)(task_rpc_t func,
                                      void *arg DFL(__NULLPTR),
                                      uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_USER_RPC_FNORMAL),
                                      gfp_t rpc_gfp DFL(GFP_NORMAL));
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_synchronous_rpc)(task_rpc_t func,
                                   void *arg DFL(__NULLPTR),
                                   uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_SYNC_RPC_FNORMAL),
                                   gfp_t rpc_gfp DFL(GFP_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED ATTR_MALLOC NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_synchronous_rpc_nx)(task_rpc_t func,
                                             void *arg DFL(__NULLPTR),
                                             uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_SYNC_RPC_FNORMAL),
                                             gfp_t rpc_gfp DFL(GFP_NORMAL));


/* Free a previously allocated RPC that hasn't been (successfully) delivered.
 * This function should be called as an alternative to `task_deliver_rpc()',
 * as well as in the event that `task_deliver_rpc()' returned an error code. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_free_rpc)(struct rpc_entry *__restrict rpc);



/* Deliver a given `rpc' to the specified `target' thread.
 * @param: target:   The target thread to which to deliver the RPC.
 * @param: rpc:      The rpc to-be delivered (inherited upon success; s.a. possible return values)
 * @param: priority: Set of `TASK_RPC_FNORMAL | TASK_RPC_FDONTWAKE | TASK_RPC_FHIGHPRIO | TASK_RPC_FLOWPRIO | TASK_RPC_FWAITFOR'
 * @return: TASK_DELIVER_RPC_KERNTHREAD:  Failed to deliver the RPC: `rpc' is a USER-level RPC, and `target' is a kernel thread.
 * @return: TASK_DELIVER_RPC_TERMINATED:  Failed to deliver the RPC: The given `target' has already terminated.
 * @return: TASK_DELIVER_RPC_SUCCESS:     Successfully delivered RPC
 * @return: TASK_DELIVER_RPC_INTERRUPTED: Successfully delivered RPC (but `target' is the caller, and `rpc' is an interrupting
 *                                        USER-level RPC, and the caller should return to user-space as soon as possible)
 *                                        NOTE: Only returned when `task_alloc_user_[s]rpc[_nx]()' was used to create `rpc'
 *                                        NOTE: Propagation may be performed by throwing an `E_INTERRUPT_USER_RPC' exception. */
FUNDEF NOBLOCK NONNULL((1, 2)) int
NOTHROW(KCALL task_deliver_rpc)(struct task *__restrict target,
                                /*inherit(on_success)*/ struct rpc_entry *__restrict rpc,
                                uintptr_t priority DFL(TASK_RPC_FNORMAL));
#endif /* __CC__ */

#define TASK_DELIVER_RPC_KERNTHREAD  TASK_SCHEDULE_USER_RPC_KERNTHREAD  /* Only for USER-RPCs: The target thread is a kernel thread that never reaches user-space. */
#define TASK_DELIVER_RPC_TERMINATED  TASK_SCHEDULE_USER_RPC_TERMINATED  /* The target thread has already terminated. */
#define TASK_DELIVER_RPC_SUCCESS     TASK_SCHEDULE_USER_RPC_SUCCESS     /* The RPC was successfully delivered. */
#define TASK_DELIVER_RPC_INTERRUPTED TASK_SCHEDULE_USER_RPC_INTERRUPTED /* Only for USER-RPCs: The calling thread is the same as the target, and `TASK_USER_RPC_FINTR' was set
                                                                         * NOTE: This return value still indicates success! */
#define TASK_DELIVER_RPC_WASOK(x)    TASK_SCHEDULE_USER_RPC_WASOK(x)


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H */
