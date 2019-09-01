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
#ifdef __INTELLISENSE__
#include "rpc.c"
//#define RPC_SIMPLE    1
//#define RPC_NOEXCEPT  1
#define RPC_USER      1
#endif

DECL_BEGIN


#ifndef RPC_NOEXCEPT
#define SUCCESS_RETURN_VALUE  true
#elif defined(RPC_USER)
#define SUCCESS_RETURN_VALUE  TASK_SCHEDULE_USER_RPC_SUCCESS
#else
#define SUCCESS_RETURN_VALUE  TASK_SCHEDULE_SYNCHRONOUS_RPC_SUCCESS
#endif

#ifndef RPC_NOEXCEPT
#define TARGET_HAS_TERMINATED_RETURN_VALUE  false
#elif defined(RPC_USER)
#define TARGET_HAS_TERMINATED_RETURN_VALUE  TASK_SCHEDULE_USER_RPC_TERMINATED
#else
#define TARGET_HAS_TERMINATED_RETURN_VALUE  TASK_SCHEDULE_SYNCHRONOUS_RPC_TERMINATED
#endif

#ifdef RPC_SIMPLE
#define RPC_FUNCTION_ARGS   struct task *__restrict target, task_srpc_t func, void *arg, uintptr_t mode, struct sig *completed, gfp_t rpc_gfp
#define RPC_ALLOC_ARGS      task_srpc_t func, void *arg, uintptr_t mode, struct sig *completed, gfp_t rpc_gfp
#else
#define RPC_FUNCTION_ARGS   struct task *__restrict target, task_rpc_t func, void *arg, uintptr_t mode, struct sig *completed, gfp_t rpc_gfp
#define RPC_ALLOC_ARGS      task_rpc_t func, void *arg, uintptr_t mode, struct sig *completed, gfp_t rpc_gfp
#endif



#ifdef RPC_USER
/* Schedule a synchronous RPC to be serviced by `target'
 * WARNING: When `target' is the calling thread, `func'
 *          will be executed before this function returns.
 * @param: mode:   Set of `TASK_RPC_F* | TASK_USER_RPC_F*'
 * @return: true:  The RPC has been scheduled.
 * @return: false: The RPC could not be scheduled, because
 *                `target' has terminated, or is terminating.
 * @return: false: The target thread has the `TASK_FKERNTHREAD' flag
 *                 set, meaning it can never return to user-space,
 *                 since it only exists in kernel-space. */
#if defined(RPC_SIMPLE) && defined(RPC_NOEXCEPT)
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) int
NOTHROW(KCALL task_schedule_user_srpc_nx)(RPC_FUNCTION_ARGS)
#elif defined(RPC_SIMPLE)
PUBLIC NONNULL((1, 2)) bool (KCALL task_schedule_user_srpc)(RPC_FUNCTION_ARGS)
#elif defined(RPC_NOEXCEPT)
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) int
NOTHROW(KCALL task_schedule_user_rpc_nx)(RPC_FUNCTION_ARGS)
#else /* ... */
PUBLIC NONNULL((1, 2)) bool (KCALL task_schedule_user_rpc)(RPC_FUNCTION_ARGS)
#endif /* !... */
#else /* RPC_USER */
/* Schedule a synchronous RPC to be serviced by `target'
 * NOTE: When `target' is the calling thread, the RPC will
 *       still be serviced the next time `task_serve()' is
 *       called, or in case `task_exit()' is called before
 *       then, it will be serviced at that point.
 * @param: mode:   Set of `TASK_RPC_F* | TASK_SYNC_RPC_F*'
 * @return: true:  The RPC has been scheduled.
 * @return: false: The RPC could not be scheduled, because
 *                `target' has terminated, or is terminating. */
#if defined(RPC_SIMPLE) && defined(RPC_NOEXCEPT)
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) int
NOTHROW(KCALL task_schedule_synchronous_srpc_nx)(RPC_FUNCTION_ARGS)
#elif defined(RPC_SIMPLE)
PUBLIC NONNULL((1, 2)) bool (KCALL task_schedule_synchronous_srpc)(RPC_FUNCTION_ARGS)
#elif defined(RPC_NOEXCEPT)
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) int
NOTHROW(KCALL task_schedule_synchronous_rpc_nx)(RPC_FUNCTION_ARGS)
#else /* ... */
PUBLIC NONNULL((1, 2)) bool (KCALL task_schedule_synchronous_rpc)(RPC_FUNCTION_ARGS)
#endif /* !... */
#endif /* !RPC_USER */
#ifndef RPC_NOEXCEPT
#ifdef RPC_USER
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC)
#else /* RPC_USER */
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !RPC_USER */
#endif /* !RPC_NOEXCEPT */
{
	struct rpc_entry *entry, *next;
	uintptr_t target_flags;
#ifdef RPC_USER
	assertf(!(mode & TASK_USER_RPC_FSYNC) || (mode & TASK_USER_RPC_FINTR),
	        "The `TASK_USER_RPC_FSYNC' flag can only be used with `TASK_USER_RPC_FINTR'");
	assertf(!(mode & TASK_USER_RPC_FNONSYSCALL) || (mode & TASK_USER_RPC_FSYNC),
	        "The `TASK_USER_RPC_FNONSYSCALL' flag can only be used with `TASK_USER_RPC_FSYNC'");
#endif /* RPC_USER */
	target_flags = ATOMIC_READ(target->t_flags);

	/* Check if the target thread is currently -, or has already terminated. */
	if unlikely(target_flags & (TASK_FTERMINATING | TASK_FTERMINATED))
		return TARGET_HAS_TERMINATED_RETURN_VALUE;

#ifdef RPC_USER
	if unlikely(target_flags & TASK_FKERNTHREAD) {
#ifdef RPC_NOEXCEPT
		return TASK_SCHEDULE_USER_RPC_KERNTHREAD;
#else /* RPC_NOEXCEPT */
		return false; /* The target thread is a kernel-thread, so it can't service user-level RPCs */
#endif /* !RPC_NOEXCEPT */
	}
#endif /* RPC_USER */

	/* Schedule a new RPC entry for the target thread. */
#ifdef RPC_NOEXCEPT
	entry = rpcentry_alloc_nx(rpc_gfp);
	if unlikely(!entry) {
#ifdef RPC_USER
		return TASK_SCHEDULE_USER_RPC_BADALLOC;
#else /* RPC_USER */
		return TASK_SCHEDULE_SYNCHRONOUS_RPC_BADALLOC;
#endif /* !RPC_USER */
	}
#else /* RPC_NOEXCEPT */
	entry = rpcentry_alloc(rpc_gfp);
#endif /* !RPC_NOEXCEPT */

#ifdef RPC_SIMPLE
	entry->re_sfunc = func;
#else /* RPC_SIMPLE */
	entry->re_func = func;
#endif /*!RPC_SIMPLE */
	entry->re_arg  = arg;
	entry->re_done = completed;
#ifdef RPC_USER
#if RPC_KIND_USER_INTR == (RPC_KIND_USER | TASK_USER_RPC_FINTR) &&                            \
    RPC_KIND_USER_INTR_SYNC == (RPC_KIND_USER | TASK_USER_RPC_FINTR | TASK_USER_RPC_FSYNC) && \
    RPC_KIND_NONSYSCALL == TASK_USER_RPC_FNONSYSCALL &&                                       \
    TASK_USER_RPC_FNOTHROW == RPC_KIND_NOTHROW
	entry->re_kind = (RPC_KIND_USER |
#ifdef RPC_SIMPLE
	                  RPC_KIND_SRPC |
#endif /* RPC_SIMPLE */
	                  (mode & (TASK_USER_RPC_FINTR |
	                           TASK_USER_RPC_FSYNC |
	                           TASK_USER_RPC_FNONSYSCALL |
	                           TASK_USER_RPC_FNOTHROW)));
#else
	entry->re_kind = RPC_KIND_USER
#ifdef RPC_SIMPLE
	                 |
	                 RPC_KIND_SRPC
#endif /* RPC_SIMPLE */
	                 ;
	if (mode & TASK_USER_RPC_FINTR)
		entry->re_kind |= RPC_KIND_USER_INTR;
	if (mode & TASK_USER_RPC_FSYNC)
		entry->re_kind |= RPC_KIND_USER_SYNC;
	if (mode & TASK_USER_RPC_FNONSYSCALL)
		entry->re_kind |= RPC_KIND_NONSYSCALL;
	if (mode & TASK_USER_RPC_FNOTHROW)
		entry->re_kind |= RPC_KIND_NOTHROW;
#endif
#else /* RPC_USER */
#if TASK_SYNC_RPC_FNOTHROW == RPC_KIND_NOTHROW
	entry->re_kind = RPC_KIND_SYNC | (mode & RPC_KIND_NOTHROW);
#else
	entry->re_kind = RPC_KIND_SYNC;
	if (mode & TASK_SYNC_RPC_FNOTHROW)
		entry->re_kind |= RPC_KIND_NOTHROW;
#endif
#endif /* !RPC_USER */

	/* Add the RPC entry to the target thread. */
	do {
		next = ATOMIC_READ(FORTASK(target, _this_pending_rpcs));
		if unlikely(next == RPC_PENDING_TERMINATED) {
			/* The thread has terminated while we were allocating the RPC. */
			rpcentry_free(entry);
			return TARGET_HAS_TERMINATED_RETURN_VALUE;
		}
		entry->re_next = next;
	} while (!ATOMIC_CMPXCH_WEAK(FORTASK(target, _this_pending_rpcs), next, entry));

	/* Increment the target thread's counter for pending, synchronous RPCs */
#ifdef RPC_USER
	if (mode & TASK_USER_RPC_FINTR) {
		if (mode & TASK_USER_RPC_FNOTHROW)
			ATOMIC_FETCHINC(FORTASK(target, _this_pending_sync_count_nx));
		ATOMIC_FETCHINC(FORTASK(target, _this_pending_sync_count));
	}
#else /* RPC_USER */
	if (mode & TASK_SYNC_RPC_FNOTHROW)
		ATOMIC_FETCHINC(FORTASK(target, _this_pending_sync_count_nx));
	ATOMIC_FETCHINC(FORTASK(target, _this_pending_sync_count));
#endif /* !RPC_USER */

	/* At this point our RPC has been scheduled and
	 * can potentially be executed at any moment. */

	/* Wake up the target thread by using a sporadic wake-up. */
#ifdef RPC_USER
	task_redirect_usercode_rpc(target, mode & TASK_WAKE_FMASK);

	/* Throw an error to return to user-space if we're interrupting, and are sending this to ourself. */
	if ((mode & TASK_USER_RPC_FINTR) && target == THIS_TASK) {
#ifdef RPC_NOEXCEPT
		return TASK_SCHEDULE_USER_RPC_INTERRUPTED;
#else /* RPC_NOEXCEPT */
		THROW(E_INTERRUPT_USER_RPC);
#endif /* !RPC_NOEXCEPT */
	}

	/* Always return SUCCESS at this point, as a failed `task_redirect_usercode_rpc()' still
	 * means that the RPC will be serviced, since we managed to schedule it as
	 * pending (i.e. `_this_pending_rpcs' wasn't `RPC_PENDING_TERMINATED'). */
	return SUCCESS_RETURN_VALUE;
#else /* RPC_USER */
	task_wake(target, mode & TASK_WAKE_FMASK);

	/* Always return SUCCESS at this point, as a failed `task_wake()' still means
	 * that the RPC will be serviced, since we managed to schedule it as
	 * pending (i.e. `_this_pending_rpcs' wasn't `RPC_PENDING_TERMINATED'). */
	return SUCCESS_RETURN_VALUE;
#endif /* !RPC_USER */
}


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
#ifdef RPC_USER
#ifdef RPC_NOEXCEPT
#ifdef RPC_SIMPLE
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED ATTR_MALLOC NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_user_srpc_nx)(RPC_ALLOC_ARGS)
#else /* RPC_SIMPLE */
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED ATTR_MALLOC NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_user_rpc_nx)(RPC_ALLOC_ARGS)
#endif /* !RPC_SIMPLE */
#else /* RPC_NOEXCEPT */
#ifdef RPC_SIMPLE
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_user_srpc)(RPC_ALLOC_ARGS)
#else /* RPC_SIMPLE */
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_user_rpc)(RPC_ALLOC_ARGS)
#endif /* !RPC_SIMPLE */
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !RPC_NOEXCEPT */
#else /* RPC_USER */
#ifdef RPC_NOEXCEPT
#ifdef RPC_SIMPLE
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED ATTR_MALLOC NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_synchronous_srpc_nx)(RPC_ALLOC_ARGS)
#else /* RPC_SIMPLE */
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED ATTR_MALLOC NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_synchronous_rpc_nx)(RPC_ALLOC_ARGS)
#endif /* !RPC_SIMPLE */
#else /* RPC_NOEXCEPT */
#ifdef RPC_SIMPLE
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_synchronous_srpc)(RPC_ALLOC_ARGS)
#else /* RPC_SIMPLE */
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_synchronous_rpc)(RPC_ALLOC_ARGS)
#endif /* !RPC_SIMPLE */
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !RPC_NOEXCEPT */
#endif /* !RPC_USER */
{
	struct rpc_entry *result;
#ifdef RPC_USER
	assertf(!(mode & TASK_USER_RPC_FSYNC) || (mode & TASK_USER_RPC_FINTR),
	        "The `TASK_USER_RPC_FSYNC' flag can only be used with `TASK_USER_RPC_FINTR'");
	assertf(!(mode & TASK_USER_RPC_FNONSYSCALL) || (mode & TASK_USER_RPC_FSYNC),
	        "The `TASK_USER_RPC_FNONSYSCALL' flag can only be used with `TASK_USER_RPC_FSYNC'");
#endif /* RPC_USER */
	assert(func);
#ifdef RPC_NOEXCEPT
	result = rpcentry_alloc_nx(rpc_gfp);
	if unlikely(!result)
		goto done;
#else /* RPC_NOEXCEPT */
	result          = rpcentry_alloc(rpc_gfp);
#endif /* !RPC_NOEXCEPT */

#ifdef RPC_SIMPLE
	result->re_sfunc = func;
#else /* RPC_SIMPLE */
	result->re_func = func;
#endif /* !RPC_SIMPLE */
	result->re_arg  = arg;
	result->re_done = completed;
#ifdef RPC_USER
#if RPC_KIND_USER_INTR == (RPC_KIND_USER | TASK_USER_RPC_FINTR) &&                            \
    RPC_KIND_USER_INTR_SYNC == (RPC_KIND_USER | TASK_USER_RPC_FINTR | TASK_USER_RPC_FSYNC) && \
    RPC_KIND_NONSYSCALL == TASK_USER_RPC_FNONSYSCALL &&                                       \
    TASK_USER_RPC_FNOTHROW == RPC_KIND_NOTHROW
	result->re_kind = (RPC_KIND_USER |
#ifdef RPC_SIMPLE
	                   RPC_KIND_SRPC |
#endif /* RPC_SIMPLE */
	                   (mode & (TASK_USER_RPC_FINTR |
	                            TASK_USER_RPC_FSYNC |
	                            TASK_USER_RPC_FNONSYSCALL |
	                            TASK_USER_RPC_FNOTHROW)));
#else
	result->re_kind = RPC_KIND_USER
#ifdef RPC_SIMPLE
	                  |
	                  RPC_KIND_SRPC
#endif /* RPC_SIMPLE */
	                  ;
	if (mode & TASK_USER_RPC_FINTR)
		result->re_kind |= RPC_KIND_USER_INTR;
	if (mode & TASK_USER_RPC_FSYNC)
		result->re_kind |= RPC_KIND_USER_SYNC;
	if (mode & TASK_USER_RPC_FNONSYSCALL)
		entry->re_kind |= RPC_KIND_NONSYSCALL;
	if (mode & TASK_USER_RPC_FNOTHROW)
		result->re_kind |= RPC_KIND_NOTHROW;
#endif
#else /* RPC_USER */
#if TASK_SYNC_RPC_FNOTHROW == RPC_KIND_NOTHROW
	result->re_kind = RPC_KIND_SYNC | (mode & RPC_KIND_NOTHROW);
#else
	result->re_kind = RPC_KIND_SYNC;
	if (mode & TASK_SYNC_RPC_FNOTHROW)
		result->re_kind |= RPC_KIND_NOTHROW;
#endif
#endif /* !RPC_USER */

#ifdef RPC_NOEXCEPT
done:
#endif /* RPC_NOEXCEPT */
	return result;
}


#undef TARGET_HAS_TERMINATED_RETURN_VALUE
#undef SUCCESS_RETURN_VALUE

#undef RPC_ALLOC_ARGS
#undef RPC_FUNCTION_ARGS
#undef RPC_NOEXCEPT
#undef RPC_SIMPLE
#undef RPC_USER


DECL_END
