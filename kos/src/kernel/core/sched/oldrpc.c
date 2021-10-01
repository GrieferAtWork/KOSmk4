/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_OLDRPC_C
#define GUARD_KERNEL_SRC_SCHED_OLDRPC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_RPC
#include <kernel/cache.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman/mpartmeta.h> /* mman_broadcastfutex() */
#include <kernel/printk.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <sys/wait.h>

#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <librpc/rpc.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/pointer.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

STATIC_ASSERT(TASK_WAKE_FWAITFOR == TASK_RPC_FWAITFOR);
STATIC_ASSERT(TASK_WAKE_FHIGHPRIO == TASK_RPC_FHIGHPRIO);

DEFINE_PREALLOCATION_CACHE(INTERN, rpcentry, struct rpc_entry, 128)
DEFINE_PREALLOCATION_CACHE_ALLOC_NX(INTERN, rpcentry, struct rpc_entry)
#define RPC_PENDING_TERMINATED ((struct rpc_entry *)-1)

/* [0..1][owned]
 * [lock(INSERT_FRONT(ATOMIC),CLEAR(THIS_TASK),INSERT_BACK(THIS_TASK))]
 * Chain of pending RPC functions.
 * When set to `RPC_PENDING_TERMINATED', no further RPC functions
 * may  be  scheduled   (this  is  done   during  task   cleanup) */
INTERN ATTR_PERTASK WEAK struct rpc_entry *this_rpcs_pending = NULL;
/* Amount of pending, synchronous RPCs (not counting non-interrupting user-RPCs) */
INTERN ATTR_PERTASK WEAK size_t this_rpc_pending_sync_count = 0;
/* Amount of pending, synchronous no-except RPCs (not counting non-interrupting user-RPCs) */
INTERN ATTR_PERTASK WEAK size_t this_rpc_pending_sync_count_nx = 0;


DEFINE_PERTASK_ONEXIT(cleanup_pending_rpcs);
PRIVATE ATTR_USED void
NOTHROW(KCALL cleanup_pending_rpcs)(void) {
	struct rpc_entry *chain, *next;
	/* Serve all remaining RPC functions, discarding all exceptions they may throw. */
	chain = ATOMIC_XCH(PERTASK(this_rpcs_pending), RPC_PENDING_TERMINATED);
	assert(chain != RPC_PENDING_TERMINATED);
	while (chain) {
		next = chain->re_next;
		TRY {
			task_rpc_exec_here_onexit(chain->re_func,
			                          chain->re_arg);
		} EXCEPT {
			/* Dump the exception if it is non-signaling */
			error_class_t cls = error_class();
			if (!ERRORCLASS_ISLOWPRIORITY(cls) &&
			    !ERRORCLASS_ISRTLPRIORITY(cls))
				error_printf("Unhandled exception in RPC function during thread termination");
		}
		rpcentry_free(chain);
		chain = next;
	}
}


DEFINE_PERTASK_FINI(fini_pending_rpcs);
PRIVATE ATTR_USED void
NOTHROW(KCALL fini_pending_rpcs)(struct task *__restrict thread) {
	struct rpc_entry *chain, *next;
	/* Serve all remaining RPC functions, discarding all exceptions they may throw.
	 * NOTE: Finding remaining RPCs at this point is _very_ unlikely,
	 *       and can only happen when:
	 * #1: The thread got a synchronous RPC delivered before it (would have) been started
	 * #2: The thread never ended up being started. */
	chain = FORTASK(thread, this_rpcs_pending);
	if likely(chain == RPC_PENDING_TERMINATED)
		return;
	while (chain) {
		next = chain->re_next;
		TRY {
			task_rpc_exec_here_onexit(chain->re_func,
			                          chain->re_arg);
		} EXCEPT {
			/* Dump the exception if it is non-signaling */
			error_class_t cls = error_class();
			if (!ERRORCLASS_ISLOWPRIORITY(cls) && !ERRORCLASS_ISRTLPRIORITY(cls))
				error_printf("Unhandled exception in RPC function during thread destroy");
		}
		rpcentry_free(chain);
		chain = next;
	}
}



LOCAL NOBLOCK void
NOTHROW(KCALL reinsert_pending_rpcs)(struct rpc_entry *__restrict chain,
                                     struct rpc_entry *__restrict chain_end) {
	struct rpc_entry *next;
	do {
		next = ATOMIC_READ(PERTASK(this_rpcs_pending));
		chain_end->re_next = next;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(PERTASK(this_rpcs_pending), next, chain));
}



/* Function called by arch-specific assembly to serving a single, pending, synchronous RPC */
INTERN struct icpustate *FCALL
task_serve_one_impl(struct icpustate *__restrict state) {
	struct rpc_entry *chain, **piter, *iter, *my_entry;
	assert(PREEMPTION_ENABLED());
	assert(PERTASK_TEST(this_rpc_pending_sync_count));
	/* Service synchronous RPC functions. */
	chain = ATOMIC_XCH(PERTASK(this_rpcs_pending), NULL);
	piter = &chain;
	for (;;) {
		iter = *piter;
		assertf(iter != NULL, "Then why was the sync-RPC counter non-zero?");
		if ((iter->re_kind & RPC_KIND_MASK) == RPC_KIND_SYNC)
			break; /* Got a synchronous RPC which we must handle now. */
#if 0 /* Technically,  we'd need to  do this to prevent  an IDLE-loop when a        \
       * system call that isn't a cancelation point calls task_serve() while        \
       * a non-syscall user-space RPC has been scheduled.                           \
       * I say ~technically~, because (in theory) this isn't actually required:     \
       *  #1: By not being defined as cancellation point, the system call shouldn't \
       *      really  have the ability to block indefinitely (XXX: what about VIO?) \
       *  #2: By looping back to have the call be re-started, the component that is \
       *      blocking should eventually resolve itself.                            \
       */
		if ((iter->re_kind & RPC_KIND_INTERRUPT)
		    && !(iter->re_kind & RPC_KIND_NONSYSCALL)
		    && !is_cancelation_point(current_system_call()))
#else
		if ((iter->re_kind & RPC_KIND_INTERRUPT))
#endif
		{
			/* Set the `RPC_KIND_CANSERVE' flag for all user-sync RPCs.
			 * -> These types of RPCs can only be handled when returning to
			 *    user-space  _after_  their associated  thread  has called
			 *    task_serve() at least once whilst in kernel-space. */
			iter = chain;
			for (;;) {
				if (iter->re_kind & RPC_KIND_USER_SYNC)
					iter->re_kind |= RPC_KIND_CANSERVE;
				if (!iter->re_next)
					break;
				iter = iter->re_next;
			}
			/* Restore all RPCs we stole as pending. */
			reinsert_pending_rpcs(chain, iter);

			/* Need to return to user-space to service this one! */
			THROW(E_INTERRUPT_USER_RPC);
		}
		if (!iter->re_next)
			break;
		piter = &iter->re_next;
	}
	*piter   = iter->re_next;
	my_entry = iter;
	while (iter->re_next)
		iter = iter->re_next;
	/* Re-schedule all other  pending RPCs, so  they
	 * are visible in nested calls to `task_serve()' */
	reinsert_pending_rpcs(chain, iter);
	if (my_entry->re_kind & RPC_KIND_NOTHROW)
		ATOMIC_DEC(PERTASK(this_rpc_pending_sync_count_nx));
	ATOMIC_DEC(PERTASK(this_rpc_pending_sync_count));
	TRY {
		/* Service the RPC. */
		state = (*my_entry->re_func)(my_entry->re_arg,
		                             state,
		                             TASK_RPC_REASON_SYNC,
		                             NULL);
	} EXCEPT {
		assert(!(my_entry->re_kind & RPC_KIND_NOTHROW));
		rpcentry_free(my_entry);
		RETHROW();
	}
	rpcentry_free(my_entry);
	return state;
}

INTERN struct icpustate *
NOTHROW(FCALL task_serve_one_nx_impl)(struct icpustate *__restrict state) {
	struct rpc_entry *chain, **piter, *iter, *my_entry;
	assert(PREEMPTION_ENABLED());
	assert(PERTASK_TEST(this_rpc_pending_sync_count_nx));
	assert(PERTASK_TEST(this_rpc_pending_sync_count));
	/* Service synchronous RPC functions. */
	chain = ATOMIC_XCH(PERTASK(this_rpcs_pending), NULL);
	piter = &chain;
	for (;;) {
		iter = *piter;
		assertf(iter != NULL, "Then why was the sync-RPC counter non-zero?");
		if ((iter->re_kind & RPC_KIND_MASK) == RPC_KIND_SYNC &&
		    (iter->re_kind & RPC_KIND_NOTHROW))
			break; /* Got a synchronous RPC which we must handle now. */
		piter = &iter->re_next;
	}
	*piter   = iter->re_next;
	my_entry = iter;
	while (iter->re_next)
		iter = iter->re_next;
	/* Re-schedule all other  pending RPCs, so  they
	 * are visible in nested calls to `task_serve()' */
	reinsert_pending_rpcs(chain, iter);
	ATOMIC_DEC(PERTASK(this_rpc_pending_sync_count_nx));
	ATOMIC_DEC(PERTASK(this_rpc_pending_sync_count));
	assert(my_entry->re_kind & RPC_KIND_NOTHROW);
	/* Service the RPC. */
	state = (*my_entry->re_func)(my_entry->re_arg,
	                             state,
	                             TASK_RPC_REASON_SYNC,
	                             NULL);
	rpcentry_free(my_entry);
	return state;
}





/* Free a previously allocated RPC that hasn't been (successfully) delivered.
 * This function should be called as an alternative to  `task_deliver_rpc()',
 * as well as in the event that `task_deliver_rpc()' returned an error code. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_free_rpc)(struct rpc_entry *__restrict rpc) {
	rpcentry_free(rpc);
}



/* Deliver a given `rpc' to the specified `target' thread.
 * @param: target:   The target thread to which to deliver the RPC.
 * @param: rpc:      The rpc to-be delivered (inherited upon success; s.a. possible return values)
 * @param: priority: Set of `TASK_RPC_FNORMAL | TASK_RPC_FDONTWAKE | TASK_RPC_FHIGHPRIO | TASK_RPC_FWAITFOR'
 * @return: TASK_DELIVER_RPC_KERNTHREAD:  Failed to deliver the RPC: `rpc' is a USER-level RPC, and `target' is a kernel thread.
 * @return: TASK_DELIVER_RPC_TERMINATED:  Failed to deliver the RPC: The given `target' has already terminated.
 * @return: TASK_DELIVER_RPC_SUCCESS:     Successfully delivered RPC
 * @return: TASK_DELIVER_RPC_INTERRUPTED: Successfully delivered RPC (but `target' is the caller, and `rpc' is an interrupting
 *                                        USER-level RPC, and  the caller  should return to  user-space as  soon as  possible)
 *                                        NOTE: Only returned when  `task_alloc_user_[s]rpc[_nx]()' was used  to create  `rpc'
 *                                        NOTE: Propagation may be performed by throwing an `E_INTERRUPT_USER_RPC'  exception. */
PUBLIC NOBLOCK NONNULL((1, 2)) int
NOTHROW(KCALL task_deliver_rpc)(struct task *__restrict target,
                                /*inherit(on_success)*/ struct rpc_entry *__restrict rpc,
                                uintptr_t priority) {
	uintptr_t target_flags;
	uintptr_t rpc_mode;
	struct rpc_entry *next;
	assertf(!(priority & ~(TASK_RPC_FWAITFOR | TASK_RPC_FDONTWAKE | TASK_RPC_FHIGHPRIO)),
	        "priority = %#" PRIxPTR, priority);
	target_flags = ATOMIC_READ(target->t_flags);

	/* Check if the target thread is currently -, or has already terminated. */
	if unlikely(target_flags & (TASK_FTERMINATING | TASK_FTERMINATED))
		return TASK_DELIVER_RPC_TERMINATED;
	rpc_mode = rpc->re_kind;
	if ((rpc_mode & RPC_KIND_MASK) != RPC_KIND_SYNC) {
		if unlikely(target_flags & TASK_FKERNTHREAD)
			return TASK_DELIVER_RPC_KERNTHREAD;
	}
	COMPILER_READ_BARRIER();

	/* Add the RPC entry to the target thread. */
	do {
		next = ATOMIC_READ(FORTASK(target, this_rpcs_pending));
		if unlikely(next == RPC_PENDING_TERMINATED)
			return TASK_DELIVER_RPC_TERMINATED;
		rpc->re_next = next;
	} while (!ATOMIC_CMPXCH_WEAK(FORTASK(target, this_rpcs_pending),
	                             next, rpc));

	/* Increment the target thread's counter for pending, synchronous  RPCs
	 * NOTE: Do this for synchronous RPC, and interrupting USER-level RPCs. */
	if ((rpc_mode & RPC_KIND_MASK) != RPC_KIND_USER) {
		/* `RPC_KIND_SYNC', `RPC_KIND_USER_INTR' or `RPC_KIND_USER_INTR_SYNC' */
		if (rpc_mode & RPC_KIND_NOTHROW)
			ATOMIC_INC(FORTASK(target, this_rpc_pending_sync_count_nx));
		ATOMIC_INC(FORTASK(target, this_rpc_pending_sync_count));
	}
	/* At this point our RPC has been scheduled and
	 * can potentially be  executed at any  moment. */

	/* Always  re-direct  user-space, since  any kind  of synchronous
	 * interrupt must be handled immediately if `target' is currently
	 * running from user-space! */
	task_redirect_usercode_rpc(target, priority);

	/* Throw an error to return to user-space if we're interrupting, and are sending this to ourself. */
	if ((rpc_mode & RPC_KIND_INTERRUPT) && target == THIS_TASK)
		return TASK_DELIVER_RPC_INTERRUPTED;

	/* Always return SUCCESS at this point, as a failed `task_redirect_usercode_rpc()'
	 * still  means that the RPC will be serviced,  since we managed to schedule it as
	 * pending (i.e. `this_rpcs_pending' wasn't `RPC_PENDING_TERMINATED'). */
	return TASK_DELIVER_RPC_SUCCESS;
}





/* Chain  of blocking cleanup functions (serviced every
 * time `task_serve()' or `task_serve_nx()' is  called)
 * Additionally, functions from this chain will also be
 * serviced by the IDLE thread, the same way any  other
 * IDLE job would be. */
PUBLIC ATTR_READMOSTLY WEAK void *blocking_cleanup_chain = NULL;


STATIC_ASSERT(BLOCKING_CLEANUP_SERVICE_NONE == TASK_SERVE_NX_NORMAL);
STATIC_ASSERT(BLOCKING_CLEANUP_SERVICE_XRPC == TASK_SERVE_NX_EXCEPT);
STATIC_ASSERT(BLOCKING_CLEANUP_SERVICE_DONE == TASK_SERVE_NX_DIDRUN);

/* Service blocking cleanup operations.
 * @return: * : One of `BLOCKING_CLEANUP_SERVICE_*' */
PUBLIC unsigned int
NOTHROW(FCALL blocking_cleanup_service)(void) {
	void *next, *chain;
	if likely(!ATOMIC_READ(blocking_cleanup_chain))
		goto did_service_none;
	chain = ATOMIC_XCH(blocking_cleanup_chain, NULL);
	if unlikely(!chain)
		goto did_service_none;
service_chain:
	for (;;) {
		next = (*(blocking_cleanup_t)chain)(chain, BLOCKING_CLEANUP_ACTION_SERVICE);
		if (!next)
			break;
		if (next == BLOCKING_CLEANUP_RETURN_XPENDING) {
			/* Must re-schedule all remaining operations, and service X-RPCs */
			if (!ATOMIC_CMPXCH(blocking_cleanup_chain, NULL, chain)) {
				void **pnext, *chain_end = chain;
				for (;;) {
					pnext = (void **)(*(blocking_cleanup_t)chain_end)(chain_end, BLOCKING_CLEANUP_ACTION_GETNEXT);
					assert(pnext != NULL);
					if (!*pnext)
						break;
					chain_end = *pnext;
				}
				do
					*pnext = next = ATOMIC_READ(blocking_cleanup_chain);
				while (!ATOMIC_CMPXCH_WEAK(blocking_cleanup_chain, next, chain));
#if 1 /* Can't hurt to do this none-the-less. */
				blocking_cleanup_prioritize();
#endif
			}
			return BLOCKING_CLEANUP_SERVICE_XRPC;
		}
		chain = next;
	}
	/* Check for additional functions to service. */
	chain = ATOMIC_XCH(blocking_cleanup_chain, NULL);
	if unlikely(chain)
		goto service_chain;
	return BLOCKING_CLEANUP_SERVICE_DONE;
did_service_none:
	return BLOCKING_CLEANUP_SERVICE_NONE;
}


/* Try to find some thread that can be used to service blocking cleanup
 * operations, potentially  waking  it  up so  it  will  service  them.
 * If no such that can be found, return without doing anything.
 * -> This function  is merely  used to  prevent blocking  cleanup
 *    operations from blocking  indefinitely, by explicitly  going
 *    out of our way to get some other thread to do the dirty work
 *    for us. */
PUBLIC NOBLOCK void
NOTHROW(FCALL blocking_cleanup_prioritize)(void) {
	/* TODO: Wake up random threads until none are left, one of them woke
	 *       up,  or  `blocking_cleanup_chain'  has  been  set  to `NULL' */
}



#if defined(__ARCH_WANT_SYSCALL_RPC_SCHEDULE) || \
    defined(__ARCH_WANT_COMPAT_SYSCALL_RPC_SCHEDULE)

/* The task has terminated in the mean time.
 * may  be   send  through   `rpc_completed' */
#define USER_RPC_SIGALT_TERMINATED (__CCAST(struct sig *)(-1))

struct user_rpc_data {
	WEAK refcnt_t                rpc_refcnt;    /* Reference counter. */
	USER CHECKED   byte_t const *rpc_program;   /* [1..1] The program to execute */
	USER UNCHECKED void        **rpc_arguments; /* [?..1] Arguments passed to the program. */
	syscall_ulong_t              rpc_flags;     /* RPC schedule flags (set of `RPC_SCHEDULE_FLAG_*') */
	struct sig                   rpc_completed; /* Signal broadcast  */
};
DEFINE_REFCOUNT_FUNCTIONS(struct user_rpc_data, rpc_refcnt, kfree)

#ifdef KERNELSPACE_HIGHMEM
#define UNUSED_FUTEX_POINTER ((uintptr_t *)KERNELSPACE_BASE)
#else /* KERNELSPACE_HIGHMEM */
#define UNUSED_FUTEX_POINTER ((uintptr_t *)KERNEL_CEILING - 1)
#endif /* !KERNELSPACE_HIGHMEM */

PRIVATE struct icpustate *FCALL
user_rpc_callback(void *arg, struct icpustate *__restrict state,
                  unsigned int reason,
                  struct rpc_syscall_info const *sc_info) {
	struct user_rpc_data *data;
	struct exception_data old_except;
	data = (struct user_rpc_data *)arg;
	memcpy(&old_except, &THIS_EXCEPTION_DATA, sizeof(old_except));
	TRY {
		uintptr_t *futex_pointer = UNUSED_FUTEX_POINTER;
		/* Make sure that the arguments pointer is located in user-space.
		 * NOTE: The pointer isn't required to be loaded in user-space
		 *       if the  program doesn't  make use  of any  arguments. */
		if unlikely(!ADDR_ISUSER(data->rpc_arguments)) {
#ifdef KERNELSPACE_HIGHMEM
			data->rpc_arguments = NULL;
#else /* KERNELSPACE_HIGHMEM */
			data->rpc_arguments = (void **)-1;
#endif /* !KERNELSPACE_HIGHMEM */
		}
		assert(reason == TASK_RPC_REASON_ASYNCUSER ||
		       reason == TASK_RPC_REASON_SYSCALL ||
		       reason == TASK_RPC_REASON_SHUTDOWN);
#define SET_STATUS(code)                                 \
		do {                                             \
			if (futex_pointer != UNUSED_FUTEX_POINTER) { \
				ATOMIC_STORE(*futex_pointer, code);      \
				mman_broadcastfutex(futex_pointer);      \
			}                                            \
		} __WHILE0
		TRY {
			if (reason == TASK_RPC_REASON_SHUTDOWN) {
				/* Special case: We can't service the RPC because we're being terminated. */
				SET_STATUS(RPC_STATUS_TERMINATED);
				sig_altbroadcast(&data->rpc_completed,
				                 USER_RPC_SIGALT_TERMINATED);
			} else {
				byte_t const *reader;
				byte_t opcode, operand;
				struct rpc_register_state program_state;
				unsigned int i;
				uintptr_t rpc_reason;
				/* Figure out what to tell the user as RPC reason. */
				if (reason != TASK_RPC_REASON_SYSCALL)
					rpc_reason = RPC_REASON_ASYNC; /* Not a system call --> Indicate ASYNC */
				else if (data->rpc_flags & RPC_SCHEDULE_FLAG_SYSRESTART)
					rpc_reason = RPC_REASON_SYSCALL; /* Always restart --> Indicate SYSCALL */
				else if (data->rpc_flags & RPC_SCHEDULE_FLAG_NOSYSRESTART)
					rpc_reason = RPC_REASON_ASYNC; /* Never restart --> Indicate ASYNC */
				else if (kernel_syscall_restartmode(sc_info) != SYSCALL_RESTART_MODE_DONT)
					rpc_reason = RPC_REASON_SYSCALL; /* AUTO+MUST --> Indicate system call */
				else {
					rpc_reason = RPC_REASON_ASYNC; /* DONT --> Indicate Async */
				}
				i = 0;
				reader = (byte_t *)data->rpc_program;
				RPC_REGISTER_STATE_INIT_ICPUSTATE(program_state, state);
next_opcode:
				opcode = ATOMIC_READ(*reader);
				++reader;
				operand = opcode & 0x1f;
				opcode &= ~0x1f;
				if (!opcode)
					opcode = operand;
				switch (opcode) {
#define RPC_NEXT_ARGUMENT() (uintptr_t) ATOMIC_READ(data->rpc_arguments[i++])

#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define RPC_PUSH(val)                                                                             \
				(RPC_REGISTER_STATE_SP(program_state) -= sizeof(void *),                          \
				 validate_writable((void *)RPC_REGISTER_STATE_SP(program_state), sizeof(void *)), \
				 *(void **)RPC_REGISTER_STATE_SP(program_state) = (void *)(val))
#define RPC_PUSH_V(buf, siz)                                                           \
				(RPC_REGISTER_STATE_SP(program_state) -= (siz),                        \
				 validate_writable((void *)RPC_REGISTER_STATE_SP(program_state), siz), \
				 memcpy((void *)RPC_REGISTER_STATE_SP(program_state), buf, siz))
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define RPC_PUSH(val)                                                                             \
				(validate_writable((void *)RPC_REGISTER_STATE_SP(program_state), sizeof(void *)), \
				 *(void **)RPC_REGISTER_STATE_SP(program_state) = (uintptr_t)(val),               \
				 RPC_REGISTER_STATE_SP(program_state) += sizeof(uintptr_t))
#define RPC_PUSH_V(buf, siz)                                                           \
				(validate_writable((void *)RPC_REGISTER_STATE_SP(program_state), siz), \
				 memcpy((void *)RPC_REGISTER_STATE_SP(program_state), buf, siz),       \
				 RPC_REGISTER_STATE_SP(program_state) += (siz))
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
#if RPC_REGISTER_COUNT < 0x1f
#define VERIFY_REGISTER(id)                             \
				if unlikely((id) >= RPC_REGISTER_COUNT) \
					goto err_illegal_opcode
#endif /* RPC_REGISTER_COUNT < 0x1f */
#define LOAD_REGISTER(id)                                           \
				if (!RPC_REGISTER_STATE_ISVALID(program_state, id)) \
					RPC_REGISTER_STATE_SETREG(program_state, id, rpc_register_state_getreg_icpustate(state, id))


				case RPC_PROGRAM_OP_resume:
					/* Resume execution. */
					break;

				case RPC_PROGRAM_OP_stftx:
					if (data->rpc_flags & RPC_SCHEDULE_FLAG_STATUSFUTEX) {
						/* Load the futex pointer from the first argument. */
						futex_pointer = (uintptr_t *)RPC_NEXT_ARGUMENT();
						validate_writable(futex_pointer, sizeof(uintptr_t));
					}
					break;

				case RPC_PROGRAM_OP_psha:
					RPC_PUSH(RPC_NEXT_ARGUMENT());
					goto next_opcode;

				case RPC_PROGRAM_OP_psh_rsn:
					RPC_PUSH(rpc_reason);
					goto next_opcode;

				case RPC_PROGRAM_OP_psh_sys:
					if ((rpc_reason & RPC_REASON_CONTEXTMASK) == RPC_REASON_SYSCALL) {
						/* If the reason is an interrupted system call, push system call information. */
						assert(reason == TASK_RPC_REASON_SYSCALL);
						assert(sc_info);
						RPC_PUSH_V(sc_info, sizeof(rpc_syscall_info));
					}
					goto next_opcode;

				case RPC_PROGRAM_OP_rep_psha:
				case RPC_PROGRAM_OP_rep_stftx_psha: {
					uintptr_t count;
					count = RPC_NEXT_ARGUMENT();
					if (opcode == RPC_PROGRAM_OP_rep_stftx_psha &&
					    (data->rpc_flags & RPC_SCHEDULE_FLAG_STATUSFUTEX)) {
						/* Load the futex pointer from the first argument. */
						futex_pointer = (uintptr_t *)RPC_NEXT_ARGUMENT();
						validate_writable(futex_pointer, sizeof(uintptr_t));
					}
					validate_readablem(data->rpc_arguments + i, count, sizeof(void *));
					RPC_PUSH_V(data->rpc_arguments + i, count * sizeof(void *));
					i += count;
					goto next_opcode;
				}	break;

				case RPC_PROGRAM_OP_mov: {
					byte_t src, dst;
					uintptr_t temp;
					src = ATOMIC_READ(*reader);
					++reader;
					if unlikely((src & ~0x1f) != RPC_PROGRAM_OP_nop)
						goto err_illegal_opcode;
					src &= 0x1f;
					VERIFY_REGISTER(src);
					dst = ATOMIC_READ(*reader);
					if ((dst & ~0x1f) == RPC_PROGRAM_OP_nop) {
						++reader;
						dst &= 0x1f;
						VERIFY_REGISTER(dst);
					} else {
						dst = src;
					}
					temp = rpc_register_state_getreg_icpustate(state, src);
					RPC_REGISTER_STATE_SETREG(program_state, dst, temp);
					goto next_opcode;
				}	break;

				case RPC_PROGRAM_OP_xita:
				case RPC_PROGRAM_OP_xipa: {
					uintptr_t code;
					code = RPC_NEXT_ARGUMENT();
					/* Exit thread / exit process */
					if (opcode == RPC_PROGRAM_OP_xipa)
						THROW(E_EXIT_PROCESS, W_EXITCODE(code & 0xff, 0));
					THROW(E_EXIT_THREAD, W_EXITCODE(code & 0xff, 0));
				}
				break;

				case RPC_PROGRAM_OP_ifthen: {
					byte_t a, b, c, d;
					a = ATOMIC_READ(*reader);
					if unlikely((a & ~0x1f) != RPC_PROGRAM_OP_nop)
						goto err_illegal_opcode;
					++reader;
					a &= 0x1f;
					VERIFY_REGISTER(a);
					b = ATOMIC_READ(*reader);
					if unlikely((b & ~0x1f) != RPC_PROGRAM_OP_nop) {
						/* RPC_PROGRAM_OP_zero */
						RPC_REGISTER_STATE_SETREG(program_state, a, 0);
						goto next_opcode;
					}
					++reader;
					b &= 0x1f;
					VERIFY_REGISTER(b);
					c = ATOMIC_READ(*reader);
					if unlikely((c & ~0x1f) != RPC_PROGRAM_OP_nop) {
						c = b;
						d = a;
					} else {
						++reader;
						c &= 0x1f;
						VERIFY_REGISTER(c);
						d = ATOMIC_READ(*reader);
						if unlikely((d & ~0x1f) != RPC_PROGRAM_OP_nop) {
							d = a;
						} else {
							++reader;
							d &= 0x1f;
							VERIFY_REGISTER(d);
						}
					}
					/* a = b ? c : d */
					LOAD_REGISTER(b);
					LOAD_REGISTER(c);
					LOAD_REGISTER(d);
					RPC_REGISTER_STATE_SETREG(program_state, a,
					                          RPC_REGISTER_STATE_GETREG(program_state, b) != 0
					                          ? RPC_REGISTER_STATE_GETREG(program_state, c)
					                          : RPC_REGISTER_STATE_GETREG(program_state, d));
				}	goto next_opcode;


				case RPC_PROGRAM_OP_add:
				case RPC_PROGRAM_OP_sub: {
					byte_t dst, src;
					uintptr_t rhs_value, lhs_value;
					dst = ATOMIC_READ(*reader);
					if unlikely((dst & ~0x1f) != RPC_PROGRAM_OP_nop)
						goto err_illegal_opcode;
					++reader;
					dst &= 0x1f;
					VERIFY_REGISTER(dst);
					src = ATOMIC_READ(*reader);
					if ((src & ~0x1f) != RPC_PROGRAM_OP_nop) { /* binary operation */
						rhs_value = RPC_NEXT_ARGUMENT();
						/* Calculate the result of the operation */
						LOAD_REGISTER(dst);
						lhs_value = RPC_REGISTER_STATE_GETREG(program_state, dst);
					} else { /* trinary operation */
						++reader;
						src &= 0x1f;
						VERIFY_REGISTER(src);
						LOAD_REGISTER(src);
						lhs_value = RPC_REGISTER_STATE_GETREG(program_state, src);
						src       = ATOMIC_READ(*reader);
						if ((src & ~0x1f) != RPC_PROGRAM_OP_nop) /* Argument operand */
							rhs_value = RPC_NEXT_ARGUMENT();
						else { /* Register operand */
							++reader;
							src &= 0x1f;
							VERIFY_REGISTER(src);
							LOAD_REGISTER(src);
							rhs_value = RPC_REGISTER_STATE_GETREG(program_state, src);
							if (opcode == RPC_PROGRAM_OP_sub) {
								byte_t op_d;
								op_d = ATOMIC_READ(*reader);
								if ((op_d & ~0x1f) == RPC_PROGRAM_OP_nop) {
									/* Make sure we don't need to deal with divide-by-zero */
									++reader;
									op_d &= 0x1f;
									switch (op_d) {
									case RPC_PROGRAM_OP_ARITH_MUL & 0x1f:
										lhs_value *= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_DIV & 0x1f:
										if unlikely(!rhs_value) {
err_divide_by_zero:
											SET_STATUS(RPC_STATUS_BADARGUMENTS);
											goto done_program_noapply;
										}
										lhs_value /= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_MOD & 0x1f:
										if unlikely(!rhs_value)
											goto err_divide_by_zero;
										lhs_value %= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_SHL & 0x1f:
										lhs_value <<= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_SHR & 0x1f:
										lhs_value >>= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_SAR & 0x1f:
										lhs_value = (intptr_t)lhs_value >> rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_AND & 0x1f:
										lhs_value &= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_ANDN & 0x1f:
										lhs_value &= ~rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_OR & 0x1f:
										lhs_value |= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_ORN & 0x1f:
										lhs_value |= ~rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_XOR & 0x1f:
										lhs_value ^= rhs_value;
										goto do_save_lhs_value;
									case RPC_PROGRAM_OP_ARITH_XORN & 0x1f:
										lhs_value ^= ~rhs_value;
										goto do_save_lhs_value;
									default: goto err_illegal_opcode;
									}
									__builtin_unreachable();
								}
							}
						}
					}
					lhs_value = opcode == RPC_PROGRAM_OP_add
					            ? lhs_value + rhs_value
					            : lhs_value - rhs_value;
do_save_lhs_value:
					/* Save the result */
					RPC_REGISTER_STATE_SETREG(program_state, dst, lhs_value);
				}	goto next_opcode;

				case RPC_PROGRAM_OP_padd:
				case RPC_PROGRAM_OP_psub: {
					byte_t src;
					uintptr_t lhs_value, rhs_value;
					src = ATOMIC_READ(*reader);
					++reader;
					if unlikely((src & ~0x1f) != RPC_PROGRAM_OP_nop)
						goto err_illegal_opcode;
					src &= 0x1f;
					VERIFY_REGISTER(src);
					LOAD_REGISTER(src);
					lhs_value = RPC_REGISTER_STATE_GETREG(program_state, src);
					src       = ATOMIC_READ(*reader);
					if ((src & ~0x1f) != RPC_PROGRAM_OP_nop) {
						rhs_value = RPC_NEXT_ARGUMENT();
					} else {
						++reader;
						src &= 0x1f;
						VERIFY_REGISTER(src);
						LOAD_REGISTER(src);
						rhs_value = RPC_REGISTER_STATE_GETREG(program_state, src);
						if (opcode == RPC_PROGRAM_OP_psub) {
							src = ATOMIC_READ(*reader);
							if ((src & ~0x1f) == RPC_PROGRAM_OP_nop) {
								++reader;
								src &= 0x1f;
								switch (src) {
								case RPC_PROGRAM_OP_ARITH_MUL & 0x1f:
									lhs_value *= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_DIV & 0x1f:
									if unlikely(!rhs_value)
										goto err_divide_by_zero;
									lhs_value /= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_MOD & 0x1f:
									if unlikely(!rhs_value)
										goto err_divide_by_zero;
									lhs_value %= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_SHL & 0x1f:
									lhs_value <<= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_SHR & 0x1f:
									lhs_value >>= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_SAR & 0x1f:
									lhs_value = (intptr_t)lhs_value >> rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_AND & 0x1f:
									lhs_value &= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_ANDN & 0x1f:
									lhs_value &= ~rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_OR & 0x1f:
									lhs_value |= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_ORN & 0x1f:
									lhs_value |= ~rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_XOR & 0x1f:
									lhs_value ^= rhs_value;
									goto do_push_lhs_value;
								case RPC_PROGRAM_OP_ARITH_XORN & 0x1f:
									lhs_value ^= ~rhs_value;
									goto do_push_lhs_value;
								default: goto err_illegal_opcode;
								}
								__builtin_unreachable();
							}
						}
					}
					lhs_value = opcode == RPC_PROGRAM_OP_padd
					            ? lhs_value + rhs_value
					            : lhs_value - rhs_value;
do_push_lhs_value:
					RPC_PUSH(lhs_value);
				}	goto next_opcode;


				case RPC_PROGRAM_OP_pshr:
					/* push old register */
					VERIFY_REGISTER(operand);
					RPC_PUSH(rpc_register_state_getreg_icpustate(state, operand));
					goto next_opcode;

				case RPC_PROGRAM_OP_plda:
					/* push old register + load new register */
					VERIFY_REGISTER(operand);
					RPC_PUSH(rpc_register_state_getreg_icpustate(state, operand));
					ATTR_FALLTHROUGH
				case RPC_PROGRAM_OP_loda:
					/* load new register */
					VERIFY_REGISTER(operand);
					RPC_REGISTER_STATE_SETREG(program_state,
					                          operand,
					                          RPC_NEXT_ARGUMENT());
					goto next_opcode;

				case RPC_PROGRAM_OP_lod_rsn:
					/* load reason code into register */
					VERIFY_REGISTER(operand);
					RPC_REGISTER_STATE_SETREG(program_state,
					                          operand,
					                          rpc_reason);
					goto next_opcode;

				case RPC_PROGRAM_OP_nop:
					/* No-op / operand for a previous instruction */
					goto next_opcode;

				default:
err_illegal_opcode:
					SET_STATUS(RPC_STATUS_BADPROGRAM);
					break;
#undef RPC_NEXT_ARGUMENT
#undef RPC_PUSH_V
#undef RPC_PUSH
				}
				{
					struct icpustate *final_state;
					/* Apply the final program state. */
					final_state = rpc_register_state_apply_icpustate(&program_state,
					                                                 state);
					SET_STATUS(likely(final_state) ? RPC_STATUS_SERVICED
					                               : RPC_STATUS_BADARGUMENTS);
					if likely(final_state)
						state = final_state;
done_program_noapply:
					/* Broadcast completion. */
					sig_broadcast(&data->rpc_completed);
				}
			}
		} EXCEPT {
			SET_STATUS(RPC_STATUS_BADPOINTER);
			RETHROW();
		}
#undef SET_STATUS
	} EXCEPT {
		error_class_t cls;
		/* Always indicate completion. */
		sig_broadcast(&data->rpc_completed);
		/* Propagate RTL-priority exceptions (such as E_EXIT_THREAD) */
		cls = error_class();
		if (ERRORCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		goto restore_old_except;
	}
done:
	decref_likely(data);
	return state;
restore_old_except:
	memcpy(&THIS_EXCEPTION_DATA, &old_except, sizeof(old_except));
	goto done;
}


#define RPC_SCHEDULE_VALID_SYNCFLAGS                                  \
	(RPC_SCHEDULE_SYNC | RPC_SCHEDULE_FLAG_NONSYSCALL |               \
	 RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX | \
	 RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART |  \
	 RPC_SCHEDULE_FLAG_WAITSMPACK | RPC_SCHEDULE_FLAG_DONTWAKE |      \
	 RPC_SCHEDULE_FLAG_HIGHPRIO)

#define RPC_SCHEDULE_VALID_ASYNCFLAGS                                 \
	(RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NOINTERRUPT |             \
	 RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX | \
	 RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART |  \
	 RPC_SCHEDULE_FLAG_WAITSMPACK | RPC_SCHEDULE_FLAG_DONTWAKE |      \
	 RPC_SCHEDULE_FLAG_HIGHPRIO)

#ifdef __ARCH_WANT_SYSCALL_RPC_SCHEDULE
DEFINE_SYSCALL4(syscall_slong_t, rpc_schedule,
                pid_t, target, syscall_ulong_t, flags,
                USER UNCHECKED uint8_t const *, program,
                USER UNCHECKED void **, arguments) {
	REF struct task *thread;
	bool success;
	struct user_rpc_data *args_packet;
	uintptr_t rpc_mode;
	VALIDATE_FLAGSET(flags,
	                 flags & RPC_SCHEDULE_ASYNC ? RPC_SCHEDULE_VALID_ASYNCFLAGS
	                                            : RPC_SCHEDULE_VALID_SYNCFLAGS,
	                 E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_FLAGS);
	if ((flags & (RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART)) ==
	    (RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART)) {
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_FLAGS,
		      flags,
		      RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART,
		      RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART);
	}
	/* Make sure that program pointer is valid. */
	validate_readable(program, 1);
	thread = pidns_lookup_task(THIS_PIDNS, target);
	FINALLY_DECREF_UNLIKELY(thread);
	args_packet = (struct user_rpc_data *)kmalloc(sizeof(struct user_rpc_data),
	                                              GFP_PREFLT);
	args_packet->rpc_program   = (USER CHECKED byte_t const *)program;
	args_packet->rpc_arguments = arguments;
	args_packet->rpc_flags     = flags;
	args_packet->rpc_refcnt    = 2;
	sig_init(&args_packet->rpc_completed);

	{
		STATIC_ASSERT(TASK_RPC_FWAITFOR == RPC_SCHEDULE_FLAG_WAITSMPACK);
		STATIC_ASSERT(TASK_RPC_FDONTWAKE == RPC_SCHEDULE_FLAG_DONTWAKE);
		STATIC_ASSERT(TASK_RPC_FHIGHPRIO == RPC_SCHEDULE_FLAG_HIGHPRIO);
		/* Inherit 1-on-1 flags directly. */
		rpc_mode = flags & (RPC_SCHEDULE_FLAG_WAITSMPACK |
		                    RPC_SCHEDULE_FLAG_DONTWAKE |
		                    RPC_SCHEDULE_FLAG_HIGHPRIO);
	}
	if (!(flags & RPC_SCHEDULE_ASYNC)) {
		/* Sync */
		rpc_mode |= (TASK_USER_RPC_FINTR | TASK_USER_RPC_FSYNC);
		if (flags & RPC_SCHEDULE_FLAG_NONSYSCALL)
			rpc_mode |= TASK_USER_RPC_FNONSYSCALL;
	} else {
		/* Async */
		if (!(flags & RPC_SCHEDULE_FLAG_NOINTERRUPT))
			rpc_mode |= TASK_USER_RPC_FINTR;
	}
	if (flags & RPC_SCHEDULE_FLAG_WAITFORSTART) {
		TRY {
			task_connect_for_poll(&args_packet->rpc_completed);
		} EXCEPT {
			destroy(args_packet);
			RETHROW();
		}
	}
	TRY {
		/* Actually schedule the RPC using the kernel-interface */
		success = task_schedule_user_rpc(thread,
		                                 &user_rpc_callback,
		                                 args_packet,
		                                 rpc_mode,
		                                 GFP_PREFLT);
	} EXCEPT {
		if (flags & RPC_SCHEDULE_FLAG_WAITFORSTART)
			task_disconnectall();
		/* In the case of the caller being the target thread, the RPC
		 * callback was successfully scheduled, and we mustn't drop a
		 * second reference from the argument packet. */
		if (was_thrown(E_INTERRUPT_USER_RPC))
			decref_nokill(args_packet); /* target == caller */
		else {
			destroy(args_packet); /* Failed to allocate an RPC */
		}
		RETHROW();
	}
	/* Check if we were able to schedule an RPC.
	 * If we weren't, immediately indicate that the target thread has terminated. */
	if unlikely(!success) {
		if (flags & RPC_SCHEDULE_FLAG_WAITFORSTART)
			task_disconnectall();
		destroy(args_packet);
		return 1;
	}
	if (flags & RPC_SCHEDULE_FLAG_WAITFORSTART) {
		struct sig *status;
		/* Check for special case: target == caller
		 * If the user passes `RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NOINTERRUPT',
		 * then `task_schedule_user_rpc()' will have returned indicating success. */
		if (thread == THIS_TASK) {
			task_disconnectall();
		} else {
			/* Must wait for the RPC to be received by the target thread. */
			TRY {
				status = task_waitfor();
			} EXCEPT {
				decref(args_packet);
				RETHROW();
			}
			/* Check if the  RPC was able  to execute its  transformation-program.
			 * If the RPC was invoked because the target was terminating, it  will
			 * have  broadcast  a status  message  of `USER_RPC_SIGALT_TERMINATED'
			 * to  us, which we can then re-interpret  to inform the user that the
			 * target thread has terminated before it could service the given RPC. */
			if (status == USER_RPC_SIGALT_TERMINATED) {
				decref(args_packet);
				return 1;
			}
		}
	}
	decref(args_packet);
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_RPC_SCHEDULE */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RPC_SCHEDULE
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rpc_schedule,
                       pid_t, target, syscall_ulong_t, flags,
                       USER UNCHECKED uint8_t const *, program,
                       USER UNCHECKED compat_ptr(void) *, arguments) {
	(void)target;
	(void)flags;
	(void)program;
	(void)arguments;
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RPC_SCHEDULE */
#endif /* rpc_schedule... */





/************************************************************************/
/* rpc_service()                                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RPC_SERVICE
DEFINE_SYSCALL0(syscall_slong_t, rpc_service) {
	return task_serve() ? 1 : 0;
}
#endif /* __ARCH_WANT_SYSCALL_RPC_SERVICE */



DECL_END


#ifndef __INTELLISENSE__
#define RPC_SERVE_ALL 1
#include "oldrpc-serveuser.c.inl"
/**/
#include "oldrpc-serveuser.c.inl"

/* User RPCs */
#define RPC_USER      1
#include "oldrpc-schedule-impl.c.inl"
#define RPC_NOEXCEPT  1
#define RPC_USER      1
#include "oldrpc-schedule-impl.c.inl"

/* Non-user RPCs */
#include "oldrpc-schedule-impl.c.inl"
#define RPC_NOEXCEPT  1
#include "oldrpc-schedule-impl.c.inl"
#endif
#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_SRC_SCHED_OLDRPC_C */
