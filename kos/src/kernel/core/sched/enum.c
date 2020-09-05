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
#ifndef GUARD_KERNEL_SRC_SCHED_ENUM_C
#define GUARD_KERNEL_SRC_SCHED_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/rt.h> /* dbg_active */
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/enum.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <alloca.h>
#include <assert.h>
#include <stdbool.h>


DECL_BEGIN

#define ASSERT_POISON(expr) assert((expr) || kernel_poisoned())

#ifdef CONFIG_HAVE_DEBUGGER
#define IF_DEBUGGER_ACTIVE(...) \
	do {                        \
		if (dbg_active) {       \
			__VA_ARGS__;        \
		}                       \
	}	__WHILE0
#define IF_NOT_DEBUGGER_ACTIVE(...) \
	do {                            \
		if (!dbg_active) {          \
			__VA_ARGS__;            \
		}                           \
	}	__WHILE0
#else /* CONFIG_HAVE_DEBUGGER */
#define IF_HAVE_DEBUGGER(...)       (void)0
#define IF_NOT_DEBUGGER_ACTIVE(...) __VA_ARGS__
#endif /* !CONFIG_HAVE_DEBUGGER */

#define sync_read_if_not_dbg(x)    IF_NOT_DEBUGGER_ACTIVE(sync_read(x))
#define sync_endread_if_not_dbg(x) IF_NOT_DEBUGGER_ACTIVE(sync_endread(x))



#define INITIAL_TASK_STACK_BUFSIZE    128
#define INITIAL_TASKPID_STACK_BUFSIZE 4
#define MAX_STACK_BUFELEM             512

/* Drop references from all of the given task objects. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL decref_task_list)(/*inherit:ref(always)*/ REF struct task **list, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		decref_unlikely(list[i]);
}

/* Drop references from all of the given taskpid objects. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL decref_taskpid_list)(/*inherit:ref(always)*/ REF struct taskpid **list, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		decref_unlikely(list[i]);
}

/* Enumerate all of the given `task' objects, and decref() all of them. */
PRIVATE NONNULL((1, 3)) ssize_t KCALL
enum_task_list_and_decref(/*inherit:ref(always)*/ REF struct task **list,
                          size_t count, task_enum_cb_t cb, void *arg) {
	ssize_t temp, result = 0;
	size_t i = 0;
	TRY {
		while (i < count) {
			REF struct task *elem;
			elem = list[i];
			temp = (*cb)(arg, elem, FORTASK(elem, this_taskpid));
			if unlikely(temp < 0)
				goto err;
			++i; /* Inherit reference into `elem' */
			decref_unlikely(elem);
			result += temp;
		}
	} EXCEPT {
		/* Decref all remaining elements. */
		decref_task_list(list + i, count - i);
		RETHROW();
	}
	return result;
err:
	/* Decref all remaining elements. */
	decref_task_list(list + i, count - i);
	return temp;
}

PRIVATE NONNULL((1, 3)) ssize_t KCALL
enum_taskpid_list_and_decref(/*inherit:ref(always)*/ REF struct taskpid **list,
                             size_t count, task_enum_cb_t cb, void *arg) {
	ssize_t temp, result = 0;
	size_t i = 0;
	TRY {
		while (i < count) {
			REF struct taskpid *elem;
			elem = list[i];
			temp = (*cb)(arg, NULL, elem);
			if unlikely(temp < 0)
				goto err;
			++i; /* Inherit reference into `elem' */
			decref_unlikely(elem);
			result += temp;
		}
	} EXCEPT {
		/* Decref all remaining elements. */
		decref_taskpid_list(list + i, count - i);
		RETHROW();
	}
	return result;
err:
	/* Decref all remaining elements. */
	decref_taskpid_list(list + i, count - i);
	return temp;
}

/* Enumerate task/taskpid objects stored within `self', and
 * decref() _all_ of them, no matter what happens inside of `cb' */
PRIVATE NONNULL((1, 2)) ssize_t KCALL
task_list_buffer_enum_and_decref(/*inherit:ref(always)*/ struct task_list_buffer *__restrict self,
                                 task_enum_cb_t cb, void *arg) {
	ssize_t temp, result;
	/* Enumerate proper task objects. */
	TRY {
		result = enum_task_list_and_decref(self->tlb_task_buf,
		                                   self->tlb_task_len,
		                                   cb, arg);
	} EXCEPT {
		decref_taskpid_list(self->tlb_taskpid_buf,
		                    self->tlb_taskpid_len);
		RETHROW();
	}
	if unlikely(result < 0) {
		decref_taskpid_list(self->tlb_taskpid_buf,
		                    self->tlb_taskpid_len);
		goto done;
	}
	/* Enumerate taskpid objects. */
	temp = enum_taskpid_list_and_decref(self->tlb_taskpid_buf,
	                                    self->tlb_taskpid_len,
	                                    cb, arg);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}



/* Allocate heap buffers */
PRIVATE NONNULL((1)) void KCALL
task_list_buffer_alloc_heap_buffers(struct task_list_buffer *__restrict self)
		THROWS(E_BADALLOC) {
	self->tlb_task_buf = (REF struct task **)kmalloc(self->tlb_task_len *
	                                                 sizeof(REF struct task *),
	                                                 GFP_NORMAL);
	self->tlb_taskpid_buf = NULL;
	if (self->tlb_taskpid_len) {
		TRY {
			self->tlb_taskpid_buf = (REF struct taskpid **)kmalloc(self->tlb_taskpid_len *
			                                                       sizeof(REF struct taskpid *),
			                                                       GFP_NORMAL);
		} EXCEPT {
			kfree(self->tlb_task_buf);
			RETHROW();
		}
	}
}

/* Reallocate heap buffers */
PRIVATE NONNULL((1)) void KCALL
task_list_buffer_realloc_heap_buffers(struct task_list_buffer *__restrict self)
		THROWS(E_BADALLOC) {
	self->tlb_task_buf = (REF struct task **)krealloc(self->tlb_task_buf,
                                                      self->tlb_task_len *
	                                                  sizeof(REF struct task *),
	                                                  GFP_NORMAL);
	if (self->tlb_taskpid_len) {
		self->tlb_taskpid_buf = (REF struct taskpid **)krealloc(self->tlb_taskpid_buf,
		                                                        self->tlb_taskpid_len *
		                                                        sizeof(REF struct taskpid *),
		                                                        GFP_NORMAL);
	}
}

/* Free heap buffers */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_list_buffer_free_heap_buffers)(struct task_list_buffer *__restrict self) {
	kfree(self->tlb_task_buf);
	kfree(self->tlb_taskpid_buf);
}



struct task_enum_list_cb_data {
	struct task_list_buffer *el_buf;          /* [1..1] The underlying buffer. */
	size_t                   el_used_task;    /* # of used/needed elements in `buf->tlb_task_buf' */
	size_t                   el_used_taskpid; /* # of used/needed elements in `buf->tlb_taskpid_buf' */
};

PRIVATE NOBLOCK ssize_t
NOTHROW(KCALL task_enum_list_cb)(void *arg,
                                 struct task *thread,
                                 struct taskpid *pid) {
	struct task_enum_list_cb_data *data;
	struct task_list_buffer *buf;
	data = (struct task_enum_list_cb_data *)arg;
	buf  = data->el_buf;
	/* Determine what kind of thread is being enumerated. */
	if (thread) {
		if (data->el_used_task < buf->tlb_task_len)
			buf->tlb_task_buf[data->el_used_task] = incref(thread);
		++data->el_used_task;
	} else {
		assert(pid);
		if (data->el_used_taskpid < buf->tlb_taskpid_len)
			buf->tlb_taskpid_buf[data->el_used_taskpid] = incref(pid);
		++data->el_used_taskpid;
	}
	return 0;
}

struct task_enum_list_taskonly_cb_data {
	REF struct task **el_buf;  /* [1..1] The underlying buffer. */
	size_t            el_size; /* Available buffer size */
	size_t            el_used; /* # of used/needed elements in `el_buf' */
};

PRIVATE NOBLOCK ssize_t
NOTHROW(KCALL task_enum_list_taskonly_cb)(void *arg,
                                          struct task *thread,
                                          struct taskpid *UNUSED(pid)) {
	struct task_enum_list_taskonly_cb_data *data;
	data = (struct task_enum_list_taskonly_cb_data *)arg;
	/* Determine what kind of thread is being enumerated. */
	assert(thread);
	if (data->el_used < data->el_size)
		data->el_buf[data->el_used] = incref(thread);
	++data->el_used;
	return 0;
}






/************************************************************************/
/* These functions are the same as those above, however these may only be used
 * when `cb' is NOBLOCK+NOEXCEPT, as these may invoke said function while non-
 * reentrant, internal locks are held.                                  */
/************************************************************************/

#define DO(expr)            do { if ((temp = (expr)) < 0) goto err; result += temp; } __WHILE0
#define CB(task_, taskpid_) DO((*cb)(arg, task_, taskpid_))
#define CB_THREAD(task_)    CB(task_, FORTASK(task_, this_taskpid))


PRIVATE NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(FCALL task_enum_mycpu_nb)(task_enum_cb_t cb, void *arg,
                                  struct cpu *__restrict c)
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result;
	struct task *first, *thread, *idle;
	/* Start out by enumerating our IDLE thread. */
	idle   = &FORCPU(c, thiscpu_idle);
	result = (*cb)(arg, idle, NULL);
	if unlikely(result < 0)
		goto done;

	/* Now walk the running-thread-loop */
	thread = first = c->c_current;
	do {
		if (thread != idle)
			CB_THREAD(thread);
	} while ((thread = thread->t_sched.s_running.sr_runnxt) != first);

#ifndef CONFIG_NO_SMP
	/* Now go through all of the pending threads. */
	for (thread = c->c_pending;
	     thread && thread != CPU_PENDING_ENDOFCHAIN;
	     thread = thread->t_sched.s_pending.ss_pennxt) {
		ASSERT_POISON(thread != idle);
		CB_THREAD(thread);
	}
#endif /* !CONFIG_NO_SMP */

	/* Finally, enumerate sleeping threads. */
	for (thread = c->c_sleeping; thread;
	     thread = thread->t_sched.s_asleep.ss_tmonxt) {
		if (thread != idle)
			CB_THREAD(thread);
	}
done:
	return result;
err:
	return temp;
}

#ifndef CONFIG_NO_SMP
#if CPU_IPI_ARGCOUNT < 4
#error "Need at least 4 IPI pointers!"
#endif /* CPU_IPI_ARGCOUNT < 4 */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) /*ATTR_NOTHROW*/ struct icpustate *
NOTHROW(FCALL task_enum_cpu_ipi)(struct icpustate *__restrict state, void *args[CPU_IPI_ARGCOUNT]) {
	task_enum_cb_t cb;
	void *cb_arg;
	ssize_t *presult;
	cb       = (task_enum_cb_t)args[0];
	cb_arg   = args[1];
	presult  = (ssize_t *)args[2];
	*presult = task_enum_mycpu_nb(cb, cb_arg, THIS_CPU);
	COMPILER_BARRIER();
	args[3] = (void *)1; /* Indicate callback completion. */
	COMPILER_BARRIER();
	return state;
}
#endif /* !CONFIG_NO_SMP */


/* Enumerate all threads running, sleeping, or pending on `c'
 * Threads that have terminated, or haven't been started are not
 * enumerated by this function. */
PUBLIC NOBLOCK NONNULL((1, 3)) ssize_t
NOTHROW(KCALL task_enum_cpu_nb)(task_enum_cb_t cb, void *arg,
                                struct cpu *__restrict c) {
	ssize_t result;
#ifdef CONFIG_NO_SMP
	result = task_enum_mycpu(cb, arg, c);
#else /* CONFIG_NO_SMP */
	uintptr_t old_flags;
	/* Don't need any of this IPI stuff when already in debugger-mode! */
	IF_DEBUGGER_ACTIVE(return task_enum_mycpu_nb(cb, arg, c));
	old_flags = ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FKEEPCORE);
	if (c == THIS_CPU) {
		result = task_enum_mycpu_nb(cb, arg, c);
		if (!(old_flags & TASK_FKEEPCORE))
			ATOMIC_FETCHAND(THIS_TASK->t_flags, ~TASK_FKEEPCORE);
	} else if (!cpu_isrunning(c)) {
cpu_not_running:
		/* The CPU only contains a single thread: it's IDLE thread. */
		result = (*cb)(arg, &FORCPU(c, thiscpu_idle), NULL);
	} else {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)cb;
		args[1] = arg;
		args[2] = (void *)&result;
		args[3] = NULL; /* becomes non-NULL upon completion. */
		while (!cpu_sendipi(c, &task_enum_cpu_ipi, args, CPU_IPI_FWAITFOR)) {
			if (!cpu_isrunning(c))
				goto cpu_not_running;
			/* Wait until we can send the IPI */
			task_pause();
		}
		/* Wait for the IPI to complete. */
		while (ATOMIC_LOAD(args[3]) == NULL)
			task_pause();
		/* Done! */
	}
#endif /* !CONFIG_NO_SMP */
	return result;
}



/* Enumerate all threads found anywhere on the system.
 * This is the same as calling `task_enum_cpu()' for all CPUs */
PUBLIC NONNULL((1)) ssize_t KCALL
task_enum_all_nb(task_enum_cb_t cb, void *arg)
		THROWS(E_WOULDBLOCK) {
	ssize_t result;
#ifdef CONFIG_NO_SMP
	result = task_enum_cpu_nb(cb, arg, &_bootcpu);
#else /* CONFIG_NO_SMP */
	ssize_t temp;
	cpuid_t i;
	result = 0;
	for (i = 0; i < cpu_count; ++i) {
		temp = task_enum_cpu_nb(cb, arg, cpu_vector[i]);
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}
#endif /* !CONFIG_NO_SMP */
	return result;
}



struct task_enum_filter_data {
	task_enum_cb_t ef_cb;  /* [1..1] The underlying callback */
	void          *ef_arg; /* Argument for `ef_cb' */
};

PRIVATE ssize_t KCALL
task_enum_filter_user_cb(void *arg,
                         struct task *thread,
                         struct taskpid *pid) {
	struct task_enum_filter_data *data;
	data = (struct task_enum_filter_data *)arg;
	/* Filter non-user threads. */
	if (!thread || (thread->t_flags & TASK_FKERNTHREAD) != 0)
		return 0;
	return (*data->ef_cb)(data->ef_arg, thread, pid);
}

PRIVATE ssize_t KCALL
task_enum_filter_kernel_cb(void *arg,
                           struct task *thread,
                           struct taskpid *pid) {
	struct task_enum_filter_data *data;
	data = (struct task_enum_filter_data *)arg;
	/* Filter non-kernel threads. */
	if (!thread || (thread->t_flags & TASK_FKERNTHREAD) == 0)
		return 0;
	return (*data->ef_cb)(data->ef_arg, thread, pid);
}


PUBLIC NONNULL((1)) ssize_t KCALL
task_enum_user_nb(task_enum_cb_t cb, void *arg) THROWS(E_WOULDBLOCK) {
	ssize_t result;
	struct task_enum_filter_data data;
	data.ef_cb  = cb;
	data.ef_arg = arg;
	/* Enumerate all threads, but filter anything that isn't a user thread. */
	result = task_enum_all_nb(&task_enum_filter_user_cb, &data);
	return result;
}


PUBLIC NONNULL((1)) ssize_t KCALL
task_enum_kernel_nb(task_enum_cb_t cb, void *arg) THROWS(E_WOULDBLOCK) {
	ssize_t result;
	struct task_enum_filter_data data;
	data.ef_cb  = cb;
	data.ef_arg = arg;
	/* Enumerate all threads, but filter anything that isn't a kernel thread. */
	result = task_enum_all_nb(&task_enum_filter_kernel_cb, &data);
	return result;
}


/* Enumerate all threads apart of the same process as `proc'
 * If `proc' is a kernel-space thread, same as `task_enum_kernel()' */
PUBLIC NONNULL((1, 3)) ssize_t KCALL
task_enum_process_threads_nb(task_enum_cb_t cb, void *arg,
                             struct task *__restrict proc)
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result;
	struct taskgroup *group;
	struct taskpid *threadlist;
	/* Retrieve the process leader of `proc' */
	proc = task_getprocess_of(proc);

	/* Check for special case: this is a kernel thread.
	 * In this case, we must enumerate all system-wide kernel threads. */
	if unlikely(proc->t_flags & TASK_FKERNTHREAD)
		return task_enum_kernel_nb(cb, arg);

	/* Enumerate the process leader. */
	result = (*cb)(arg, proc, FORTASK(proc, this_taskpid));
	if unlikely(result < 0)
		goto done;

	/* Lock the process's thread list. */
	group = &FORTASK(proc, this_taskgroup);
	sync_read_if_not_dbg(&group->tg_proc_threads_lock);
	/* Enumerate threads. */
	threadlist = group->tg_proc_threads;
	if (threadlist != TASKGROUP_TG_PROC_THREADS_TERMINATED) {
		for (; threadlist; threadlist = threadlist->tp_siblings.ln_next) {
			REF struct task *thread;
			thread = taskpid_gettask(threadlist);
			if (!thread)
				continue;
			/* Only enumerate threads. - Don't enumerate child processes. */
			temp = task_getprocess_of(thread) == proc
			       ? (*cb)(arg, thread, threadlist)
			       : 0;
			decref_unlikely(thread);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	sync_endread_if_not_dbg(&group->tg_proc_threads_lock);
done:
	return result;
err:
	sync_endread_if_not_dbg(&group->tg_proc_threads_lock);
	return temp;
}


/* Same as `task_enum_process_threads()', but don't enumerate `task_getprocess_of(proc)' */
PUBLIC NONNULL((1, 3)) ssize_t KCALL
task_enum_process_worker_threads_nb(task_enum_cb_t cb, void *arg,
                                    struct task *__restrict proc)
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result = 0;
	struct taskgroup *group;
	struct taskpid *threadlist;
	/* Retrieve the process leader of `proc' */
	proc = task_getprocess_of(proc);

	/* Check for special case: this is a kernel thread.
	 * In this case, we must enumerate all system-wide kernel threads. */
	if unlikely(proc->t_flags & TASK_FKERNTHREAD)
		return task_enum_kernel_nb(cb, arg);

	/* Lock the process's thread list. */
	group = &FORTASK(proc, this_taskgroup);
	sync_read_if_not_dbg(&group->tg_proc_threads_lock);
	/* Enumerate threads. */
	threadlist = group->tg_proc_threads;
	if (threadlist != TASKGROUP_TG_PROC_THREADS_TERMINATED) {
		for (; threadlist; threadlist = threadlist->tp_siblings.ln_next) {
			REF struct task *thread;
			thread = taskpid_gettask(threadlist);
			if (!thread)
				continue;
			/* Only enumerate threads. - Don't enumerate child processes. */
			temp = task_getprocess_of(thread) == proc
			       ? (*cb)(arg, thread, threadlist)
			       : 0;
			decref_unlikely(thread);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	sync_endread_if_not_dbg(&group->tg_proc_threads_lock);
	return result;
err:
	sync_endread_if_not_dbg(&group->tg_proc_threads_lock);
	return temp;
}


/* Enumerate all children of the given `proc'. (i.e. the threads
 * that `proc' can `wait(2)' for). This also includes threads that
 * could also be enumerated using `task_enum_process_threads()'
 * Note however that this function will not enumerate `proc' itself,
 * and when `proc' is a kernel-thread, nothing will be enumerated.
 * @throws: E_BADALLOC: Only outside of debugger-mode: Failed to
 *                      allocate memory for intermediate buffers. */
PUBLIC NONNULL((1, 3)) ssize_t KCALL
task_enum_process_children_nb(task_enum_cb_t cb, void *arg,
                              struct task *__restrict proc)
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result = 0;
	struct taskgroup *group;
	struct taskpid *threadlist;
	/* Retrieve the process leader of `proc' */
	proc = task_getprocess_of(proc);

	/* Check for special case: this is a kernel thread. */
	if unlikely(proc->t_flags & TASK_FKERNTHREAD)
		goto done;

	/* Lock the process's thread list. */
	group = &FORTASK(proc, this_taskgroup);
	sync_read_if_not_dbg(&group->tg_proc_threads_lock);
	/* Enumerate threads. */
	threadlist = group->tg_proc_threads;
	if (threadlist != TASKGROUP_TG_PROC_THREADS_TERMINATED) {
		for (; threadlist; threadlist = threadlist->tp_siblings.ln_next) {
			REF struct task *thread;
			thread = taskpid_gettask(threadlist);
			temp = (*cb)(arg, thread, threadlist);
			xdecref_unlikely(thread);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	sync_endread_if_not_dbg(&group->tg_proc_threads_lock);
done:
	return result;
err:
	sync_endread_if_not_dbg(&group->tg_proc_threads_lock);
	return temp;
}


PUBLIC NONNULL((1, 3)) ssize_t KCALL
task_enum_procgroup_processes_nb(task_enum_cb_t cb, void *arg,
                                 struct task *__restrict proc)
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result;
	struct taskgroup *group;
	struct task *threadlist;
	/* Retrieve the process group leader of `proc' */
	proc = task_getprocessgroupleader_of(proc);
	FINALLY_DECREF_UNLIKELY(proc);

	/* Check for special case: this is a kernel thread.
	 * In this case, we must enumerate all system-wide kernel threads. */
	if unlikely(proc->t_flags & TASK_FKERNTHREAD)
		return task_enum_kernel_nb(cb, arg);

	/* Enumerate the process group leader. */
	result = (*cb)(arg, proc, FORTASK(proc, this_taskpid));
	if unlikely(result < 0)
		goto done;

	/* Lock the process's thread list. */
	group = &FORTASK(proc, this_taskgroup);
	sync_read_if_not_dbg(&group->tg_pgrp_processes_lock);
	/* Enumerate process group member processes. */
	for (threadlist = group->tg_pgrp_processes; threadlist;
	     threadlist = FORTASK(threadlist, this_taskgroup).tg_proc_group_siblings.ln_next) {
		ASSERT_POISON(threadlist != proc);
		CB_THREAD(threadlist);
	}
	sync_endread_if_not_dbg(&group->tg_pgrp_processes_lock);
done:
	return result;
err:
	sync_endread_if_not_dbg(&group->tg_pgrp_processes_lock);
	return temp;
}


/* Similar to `task_enum_user()': Enumerate the leaders of running
 * user-space processes, as visible by `ns'. These are identical to
 * what will show up under `/proc' */
PUBLIC NONNULL((1, 3)) ssize_t KCALL
task_enum_processes_nb(task_enum_cb_t cb, void *arg,
                       struct pidns *__restrict ns)
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result = 0;
	size_t i, mask;
	struct pidns_entry *list;
	sync_read_if_not_dbg(ns);
	mask = ns->pn_mask;
	list = ns->pn_list;
	for (i = 0; i <= mask; ++i) {
		struct taskpid *pid;
		REF struct task *thread;
		pid = list[i].pe_pid;
		if (!pid)
			continue; /* Unused entry */
		if (pid == PIDNS_ENTRY_DELETED)
			continue; /* Deleted entry */
		thread = taskpid_gettask(pid);
		if (!thread)
			continue;
		temp = task_isprocessleader_p(thread)
		       ? (*cb)(arg, thread, pid)
		       : 0;
		decref_unlikely(thread);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	sync_endread_if_not_dbg(ns);
	return result;
err:
	sync_endread_if_not_dbg(ns);
	return temp;
}


/* Similar to `task_enum_processes()', but don't just enumerate
 * threads that are process leaders, but all threads from `ns' */
PUBLIC NONNULL((1, 3)) ssize_t KCALL
task_enum_namespace_nb(task_enum_cb_t cb, void *arg,
                       struct pidns *__restrict ns)
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result = 0;
	size_t i, mask;
	struct pidns_entry *list;
	sync_read_if_not_dbg(ns);
	mask = ns->pn_mask;
	list = ns->pn_list;
	for (i = 0; i <= mask; ++i) {
		struct taskpid *pid;
		REF struct task *thread;
		pid = list[i].pe_pid;
		if (!pid)
			continue; /* Unused entry */
		if (pid == PIDNS_ENTRY_DELETED)
			continue; /* Deleted entry */
		thread = taskpid_gettask(pid);
		temp   = (*cb)(arg, thread, pid);
		xdecref_unlikely(thread);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	sync_endread_if_not_dbg(ns);
	return result;
err:
	sync_endread_if_not_dbg(ns);
	return temp;
}


/* Enumerate all threads that are using `v' as their active VM. */
PUBLIC NONNULL((1, 3)) ssize_t KCALL
task_enum_vm_nb(task_enum_cb_t cb, void *arg,
                struct vm *__restrict v)
		THROWS(E_WOULDBLOCK) {
	struct task *thread;
	ssize_t temp, result = 0;
	IF_NOT_DEBUGGER_ACTIVE(vm_tasklock_read(v));
	for (thread = v->v_tasks; thread;
	     thread = thread->t_vm_tasks.ln_next) {
		/* Enumerate the thread. */
		CB_THREAD(thread);
	}
	IF_NOT_DEBUGGER_ACTIVE(vm_tasklock_endread(v));
	return result;
err:
	IF_NOT_DEBUGGER_ACTIVE(vm_tasklock_endread(v));
	return temp;
}






DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_task_enum_all 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_user 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_process_threads 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_process_worker_threads 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_process_children 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_procgroup_processes 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_processes 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_namespace 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_kernel 1
#include "enum-wrapper.c.inl"

#define DEFINE_task_enum_cpu 1
#include "enum-wrapper.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_SCHED_ENUM_C */
