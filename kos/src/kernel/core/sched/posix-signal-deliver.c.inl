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
#ifdef __INTELLISENSE__
#include "posix-signal.c"
//#define DELIVER_NX 1
#endif

#ifdef DELIVER_NX
#define FUNC(x)       x##_nx
#define IFELSE(x, nx) nx
#define NOTHROW_NX    NOTHROW
#else /* DELIVER_NX */
#define FUNC(x)       x
#define IFELSE(x, nx) x
#define NOTHROW_NX    /* nothing */
#endif /* !DELIVER_NX */

DECL_BEGIN


#ifdef DELIVER_NX
/* Noexcept variant of `task_raisesignalthread()'
 * @return: * : One of `TASK_RAISESIGNALTHREAD_NX_*' */
PUBLIC NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) int
NOTHROW(KCALL task_raisesignalthread_nx)(struct task *__restrict target,
                                         USER CHECKED siginfo_t *info,
                                         gfp_t rpc_flags)
#else /* DELIVER_NX */
/* Raise a posix signal within a given thread `target'
 * @return: true:   Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false:  The given thread `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `NSIG'
 * @throw: E_INTERRUPT_USER_RPC:        `target' is the calling thread, and the signal isn't being blocked at the moment. */
PUBLIC NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) bool KCALL
task_raisesignalthread(struct task *__restrict target,
                       USER CHECKED siginfo_t *info,
                       gfp_t rpc_flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT)
#endif /* !DELIVER_NX */
{
	IFELSE(bool, int) result;
	struct sigqueue_entry *entry;
	/* The signal is being masked.
	 * Allocate a queue entry which is going to be scheduled. */
	entry = (struct sigqueue_entry *)FUNC(kmalloc)(sizeof(struct sigqueue_entry),
	                                               rpc_flags);
#ifdef DELIVER_NX
	if unlikely(!entry)
		return TASK_RAISESIGNALTHREAD_NX_BADALLOC;
#endif /* DELIVER_NX */
	TRY {
		memcpy(&entry->sqe_info, info, sizeof(siginfo_t));
	} EXCEPT {
		kfree(entry);
		IFELSE(RETHROW(), return TASK_RAISESIGNALTHREAD_NX_SEGFAULT);
	}
	if unlikely(entry->sqe_info.si_signo <= 0 || entry->sqe_info.si_signo >= NSIG) {
		kfree(entry);
		IFELSE(THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		             E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		             entry->sqe_info.si_signo),
		       return TASK_RAISESIGNALTHREAD_NX_BADSIGNO);
	}
	/* Check if the signal is being masked. */
	if (sigmask_ismasked_in(target, entry->sqe_info.si_signo)) {
		/* Schedule the signal as pending within the target thread. */
		struct sigqueue *pending;
		struct sigqueue_entry *next;
		pending = &FORTASK(target, this_sigqueue);
		do {
			next = ATOMIC_READ(pending->sq_queue);
			if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED) {
				/* The target thread can no longer receive signals! */
				kfree(entry);
				return false;
			}
			entry->sqe_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(pending->sq_queue, next, entry));
		/* Only one thread can ever handle the signal, so use `sig_send()' */
		sig_send(&pending->sq_newsig);
		/* Check if the signal is still being masked. - If it isn't, it may have gotten
		 * unmasked before we inserted our new signal into the queue, in which case the
		 * target thread may not know about it. - Because of this, send an RPC to have
		 * the target thread manually check for unmasked signals. */
		if unlikely(!sigmask_ismasked_in(target, entry->sqe_info.si_signo)) {
			/* The signal got unmasked */
#ifdef DELIVER_NX
			STATIC_ASSERT(TASK_RAISESIGNALTHREAD_NX_SUCCESS == TASK_SCHEDULE_USER_RPC_SUCCESS);
			STATIC_ASSERT(TASK_RAISESIGNALTHREAD_NX_INTERRUPTED == TASK_SCHEDULE_USER_RPC_INTERRUPTED);
			STATIC_ASSERT(TASK_RAISESIGNALTHREAD_NX_BADALLOC == TASK_SCHEDULE_USER_RPC_BADALLOC);
			STATIC_ASSERT(TASK_RAISESIGNALTHREAD_NX_TERMINATED == TASK_SCHEDULE_USER_RPC_TERMINATED);
			STATIC_ASSERT(TASK_RAISESIGNALTHREAD_NX_KERNTHREAD == TASK_SCHEDULE_USER_RPC_KERNTHREAD);
			result = task_schedule_user_rpc_nx(target,
			                                   &task_sigmask_check_rpc_handler,
			                                   NULL,
			                                   TASK_USER_RPC_FINTR,
			                                   rpc_flags);
#else /* DELIVER_NX */
			result = task_schedule_user_rpc(target,
			                                &task_sigmask_check_rpc_handler,
			                                NULL,
			                                TASK_USER_RPC_FINTR,
			                                rpc_flags);
#endif /* !DELIVER_NX */
			return result;
			
		}
		/* The target thread will handle the signal as soon as it gets unmasked! */
		return true;
	}
	/* Deliver an RPC. */
#ifdef DELIVER_NX
	result = task_schedule_user_rpc_nx(target,
	                                   &task_signal_rpc_handler,
	                                   entry,
	                                   TASK_USER_RPC_FINTR,
	                                   rpc_flags);
	if unlikely(!TASK_SCHEDULE_USER_RPC_WASOK(result))
		kfree(entry);
#else /* DELIVER_NX */
	TRY {
		result = task_schedule_user_rpc(target,
		                                &task_signal_rpc_handler,
		                                entry,
		                                TASK_USER_RPC_FINTR,
		                                rpc_flags);
	} EXCEPT {
		if (!was_thrown(E_INTERRUPT_USER_RPC))
			kfree(entry);
		RETHROW();
	}
	if (!result)
		kfree(entry);
#endif /* !DELIVER_NX */
	return result;

}




/* Find a thread within the process lead by `process_leader' that isn't masking `kernel_signo'
 * If no such thread exists, return `NULL' instead. */
PRIVATE IFELSE(REF struct task *, int)
NOTHROW_NX(KCALL FUNC(find_thread_in_process_with_unmasked_signal))(struct task *__restrict process_leader,
                                                                    u32 kernel_signo
#ifdef DELIVER_NX
                                                                    , REF struct task **presult
#endif /* DELIVER_NX */
                                                                    )
#ifndef DELIVER_NX
		THROWS(E_WOULDBLOCK)
#endif /* !DELIVER_NX */
{
	struct taskgroup *group;
	struct taskpid *cpid;
	assert(!(process_leader->t_flags & TASK_FKERNTHREAD));
	/* First check: is the leader masking the signal? */
	if (!sigmask_ismasked_in(process_leader, kernel_signo)) {
		return IFELSE(incref(process_leader), (*presult = incref(process_leader), 0));
	}
	group = &FORTASK(process_leader, this_taskgroup);
#ifdef DELIVER_NX
	if (!sync_read_nx(&group->tg_proc_threads_lock))
		return TASK_RAISESIGNALTHREAD_NX_WOULDBLOCK;
#else /* DELIVER_NX */
	sync_read(&group->tg_proc_threads_lock);
#endif /* !DELIVER_NX */
	cpid = ATOMIC_READ(group->tg_proc_threads);
	if unlikely(cpid == TASKGROUP_TG_PROC_THREADS_TERMINATED) {
		sync_endread(&group->tg_proc_threads_lock);
		/* Terminated thread... */
		return IFELSE(NULL, 1);
	}
	for (; cpid; cpid = cpid->tp_siblings.ln_next) {
		REF struct task *child;
		child = cpid->tp_thread.get();
		if (!child)
			continue;
		/* Only consider child _threads_ (not child processes) */
		if (task_getprocess_of(child) == process_leader) {
			/* Check if the thread is masking the given signal. */
			if (!sigmask_ismasked_in(child, kernel_signo)) {
				sync_endread(&group->tg_proc_threads_lock);
				return IFELSE(child, (*presult = child, 0));
			}
			decref_unlikely(child);
		}
	}
	sync_endread(&group->tg_proc_threads_lock);
	/* The signal is being masked everywhere. */
	return IFELSE(NULL, 1);
}





/* Deliver the given signal `info' to some thread apart of the process lead by `process_leader'
 * If all threads are masking the given signal, schedule the signal as pending for the process.
 * @return: true / TASK_RAISESIGNALTHREAD_NX_SUCCESS:     Success (either delivered, or scheduled as pending).
 * @return: false / TASK_RAISESIGNALTHREAD_NX_TERMINATED: The given process has terminated.
 * @return: TASK_RAISESIGNALTHREAD_NX_*:                  An error occurred. * */
PRIVATE IFELSE(bool, int)
NOTHROW_NX(KCALL FUNC(deliver_signal_to_some_thread_in_process))(struct task *__restrict process_leader,
                                                                 /*inherit(always)*/ struct sigqueue_entry *__restrict info,
                                                                 gfp_t rpc_flags)
#ifndef DELIVER_NX
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC)
#endif /* !DELIVER_NX */
{
	IFELSE(bool, int) result;
	REF struct task *target;
	struct process_sigqueue *procqueue;
	u32 kernel_signo;
	assert(!(process_leader->t_flags & TASK_FKERNTHREAD));
	assert(!(info->sqe_info.si_signo <= 0 || info->sqe_info.si_signo >= NSIG));
	if unlikely(ATOMIC_READ(process_leader->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED)) {
		kfree(info);
		/* No possible receiver in a terminating process. */
		return IFELSE(false, TASK_RAISESIGNALTHREAD_NX_TERMINATED);
	}

	/* Search the process for a thread that isn't masking the signal.
	 * If we can find one, send the signal to it by using a
	 * `task_process_signal_rpc_handler' PRC to have it handled.
	 *
	 * If we can't find one, schedule the signal as pending and re-check
	 * all threads. - If at this point we find one that isn't masking it,
	 * we must deliver a `task_sigmask_check_rpc_handler' RPC to it so it
	 * can be the one to handle the signal. */
	kernel_signo = info->sqe_info.si_signo;
	COMPILER_READ_BARRIER();
#ifdef DELIVER_NX
	result = find_thread_in_process_with_unmasked_signal_nx(process_leader,
	                                                        kernel_signo,
	                                                        &target);
	if (result < 0) {
		kfree(info);
		return result; /* Error */
	}
	if (result == 0) {
		result = task_schedule_user_rpc_nx(target,
		                                   &task_process_signal_rpc_handler,
		                                   info,
		                                   TASK_USER_RPC_FINTR,
		                                   rpc_flags);
		decref_unlikely(target);
		if (!TASK_SCHEDULE_USER_RPC_WASOK(result))
			kfree(info);
		return result;
	}
#else /* DELIVER_NX */
	TRY {
		target = find_thread_in_process_with_unmasked_signal(process_leader,
		                                                     kernel_signo);
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
	if (target) {
		FINALLY_DECREF_UNLIKELY(target);
		TRY {
			result = task_schedule_user_rpc(target,
			                                &task_process_signal_rpc_handler,
			                                info,
			                                TASK_USER_RPC_FINTR,
			                                rpc_flags);
		} EXCEPT {
			if (!was_thrown(E_INTERRUPT_USER_RPC))
				kfree(info);
			RETHROW();
		}
		if unlikely(!result)
			kfree(info);
		return result;
	}
#endif /* !DELIVER_NX */

	/* No thread seems to exist that isn't masking the given signal.
	 * Schedule the signal as pending within the process signal queue. */
	procqueue = &FORTASK(process_leader, this_taskgroup.tg_proc_signals);
#ifdef DELIVER_NX
	if (!sync_write_nx(procqueue)) {
		kfree(info);
		return TASK_RAISESIGNALTHREAD_NX_WOULDBLOCK;
	}
#else /* DELIVER_NX */
	TRY {
		sync_write(procqueue);
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
#endif /* !DELIVER_NX */
	{
		struct sigqueue_entry *next;
		do {
			next = ATOMIC_READ(procqueue->psq_queue.sq_queue);
			if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED) {
				/* The target process has terminated. */
				sync_endwrite(procqueue);
				kfree(info);
				return IFELSE(false, TASK_RAISESIGNALTHREAD_NX_TERMINATED);
			}
			info->sqe_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(procqueue->psq_queue.sq_queue,
		                             next, info));
	}
	sync_endwrite(procqueue);
	/* Signal the arrival of a new pending signal.
	 * Only one thread can ever handle the signal, so use `sig_send()' */
	sig_send(&procqueue->psq_queue.sq_newsig);
again_find_late_target:
	/* Check for a potential target thread one more time. */
	if unlikely(ATOMIC_READ(process_leader->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED))
		return IFELSE(false, TASK_RAISESIGNALTHREAD_NX_TERMINATED); /* No possible receiver in a terminating process. */

#ifdef DELIVER_NX
	result = find_thread_in_process_with_unmasked_signal_nx(process_leader,
	                                                        kernel_signo,
	                                                        &target);
	if (result == 0) {
		/* Deliver a `task_sigmask_check_rpc_handler' RPC to the target thread. */
		result = task_schedule_user_rpc_nx(target,
		                                   &task_sigmask_check_rpc_handler,
		                                   NULL,
		                                   TASK_USER_RPC_FINTR,
		                                   rpc_flags);
		decref_unlikely(target);
		if (result == TASK_SCHEDULE_USER_RPC_TERMINATED)
			goto again_find_late_target;
	}
	result = TASK_RAISESIGNALTHREAD_NX_SUCCESS;
#else /* DELIVER_NX */
	target = find_thread_in_process_with_unmasked_signal(process_leader,
	                                                     kernel_signo);
	if (target) {
		/* Deliver a `task_sigmask_check_rpc_handler' RPC to the target thread. */
		FINALLY_DECREF_UNLIKELY(target);
		if unlikely(!task_schedule_user_rpc(target,
		                                    &task_sigmask_check_rpc_handler,
		                                    NULL,
		                                    TASK_USER_RPC_FINTR,
		                                    rpc_flags)) {
			/* The chosen target has terminated. - Try to find another candidate. */
			goto again_find_late_target;
		}
	}
#endif /* !DELIVER_NX */
	return IFELSE(true, result);
}


/* Raise a posix signal within a given process that `target' is apart of
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @return: false: The given process `target' is a kernel thread.
 * @return: * :    One of `TASK_RAISESIGNALTHREAD_NX_*' 
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `NSIG'
 * @throw: E_INTERRUPT_USER_RPC:         The calling thread is apart of the same process,
 *                                       and the signal isn't being blocked at the moment. */
PUBLIC NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) IFELSE(bool, int)
NOTHROW_NX(KCALL FUNC(task_raisesignalprocess))(struct task *__restrict target,
                                                USER CHECKED siginfo_t *info,
                                                gfp_t rpc_flags)
#ifndef DELIVER_NX
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT)
#endif /* !DELIVER_NX */
{
	struct sigqueue_entry *entry;
	IFELSE(bool, int) result;
	target = task_getprocess_of(target);
	if unlikely(target->t_flags & TASK_FKERNTHREAD)
		return IFELSE(false, TASK_RAISESIGNALTHREAD_NX_KERNTHREAD);
	/* Allocate the queue entry for the given signal. */
	entry = (struct sigqueue_entry *)FUNC(kmalloc)(sizeof(struct sigqueue_entry),
	                                               rpc_flags);
#ifdef DELIVER_NX
	if unlikely(!entry)
		return TASK_RAISESIGNALTHREAD_NX_BADALLOC;
#endif /* DELIVER_NX */
	TRY {
		memcpy(&entry->sqe_info, info, sizeof(siginfo_t));
		if unlikely(entry->sqe_info.si_signo <= 0 || entry->sqe_info.si_signo >= NSIG) {
			IFELSE(THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			             E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
			             entry->sqe_info.si_signo),
			       kfree(entry);
			       return TASK_RAISESIGNALTHREAD_NX_BADSIGNO);
		}
	} EXCEPT {
		kfree(entry);
		IFELSE(RETHROW(), return TASK_RAISESIGNALTHREAD_NX_SEGFAULT);
	}
	result = FUNC(deliver_signal_to_some_thread_in_process)(target,
	                                                        entry,
	                                                        rpc_flags);
	return result;
}

DECL_END

#undef NOTHROW_NX
#undef IFELSE
#undef FUNC
#undef DELIVER_NX
