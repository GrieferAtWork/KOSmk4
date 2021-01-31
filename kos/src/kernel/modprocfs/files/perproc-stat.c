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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_STAT_C
#define GUARD_MODPROCFS_FILES_PERPROC_STAT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/mman.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/mnode.h>
#include <sched/cpu.h>
#include <sched/pid-ctty.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/dev.h>
#include <sys/wait.h>

#include <format-printer.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>

#include "../procfs.h"

DECL_BEGIN

/*
	pid: 1
	comm: (systemd)
	state: S
	ppid: 0
	pgrp: 1
	session: 1
	tty_nr: 0
	tpgid: -1
	flags: 4194560
	minflt: 505178
	cminflt: 167031994
	majflt: 108
	cmajflt: 38154
	utime: 168810
	stime: 60596
	cutime: 4379031
	cstime: 1098750
	priority: 20
	nice: 0
	num_threads: 1
	itrealvalue: 0
	starttime: 4
	vsize: 25808896
	rss: 1050
	rsslim: 4294967295
	startcode: 4988928
	endcode: 6447492
	startstack: 3213975232
	kstkesp: 3213971568
	kstkeip: 3078032433
	signal: 0
	blocked: 671173123
	sigignore: 4096
	sigcatch: 1260
	wchan: 1
	nswap: 0
	cnswap: 0
	exit_signal: 17
	processor: 1
	rt_priority: 0
	policy: 0
	delayacct_blkio_ticks: 2823
	guest_time: 0
	cguest_time: 0
	start_data: 6453408
	end_data: 6530008
	start_brk: 13393920
	arg_start: 3213983519
	arg_end: 3213983566
	env_start: 3213983566
	env_end: 3213983719
	exit_code: 0
*/


/* Return the total # of bytes of mapped memory from `self'. */
PRIVATE NOBLOCK ATTR_PURE NONNULL((1, 2)) size_t
NOTHROW(FCALL mnode_tree_get_total_mapped_bytes)(struct mnode const *root,
                                                 struct mnode const *skipme) {
	size_t result = 0;
again:
	if (root != skipme)
		result += mnode_getsize(root);
#ifdef CONFIG_USE_NEW_VM
	if (root->mn_mement.rb_lhs) {
		if (root->mn_mement.rb_rhs)
			result += mnode_tree_get_total_mapped_bytes(root->mn_mement.rb_rhs, skipme);
		root = root->mn_mement.rb_lhs;
		goto again;
	}
	if (root->mn_mement.rb_rhs) {
		root = root->mn_mement.rb_rhs;
		goto again;
	}
#else /* CONFIG_USE_NEW_VM */
	if (root->vn_node.a_min) {
		if (root->vn_node.a_max)
			result += mnode_tree_get_total_mapped_bytes(root->vn_node.a_max, skipme);
		root = root->vn_node.a_min;
		goto again;
	}
	if (root->vn_node.a_max) {
		root = root->vn_node.a_max;
		goto again;
	}
#endif /* !CONFIG_USE_NEW_VM */
	return result;
}

PRIVATE NOBLOCK ATTR_PURE NONNULL((1)) size_t
NOTHROW(FCALL mman_get_total_mapped_bytes)(struct mman const *__restrict self) {
	if unlikely(!self->mm_mappings)
		return 0;
#ifdef CONFIG_USE_NEW_VM
	return mnode_tree_get_total_mapped_bytes(self->mm_mappings,
	                                         &FORMMAN(self, thismman_kernel_reservation));
#else /* CONFIG_USE_NEW_VM */
	return mnode_tree_get_total_mapped_bytes(self->mm_mappings,
	                                         vm_get_kernreserve_node(self));
#endif /* !CONFIG_USE_NEW_VM */
}


INTERN NONNULL((1)) ssize_t KCALL
ProcFS_PerProc_Stat_Printer(struct regular_node *__restrict self,
                            pformatprinter printer, void *arg) {
	upid_t pid;
	REF struct taskpid *tpid;
	REF struct task *thread = NULL;
	REF struct vm *mm = NULL;
	struct pidns *myns = THIS_PIDNS;
	pid  = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	tpid = pidns_trylookup(myns, pid);
	FINALLY_XDECREF_UNLIKELY(tpid);
	if likely(tpid)
		thread = taskpid_gettask(tpid);
	FINALLY_XDECREF_UNLIKELY(thread);
	if (thread)
		mm = task_getmman(thread);
	FINALLY_XDECREF_UNLIKELY(mm);
	if (format_printf(printer, arg,
	                  "%" PRIuN(__SIZEOF_PID_T__) " (", pid) < 0)
		goto done;
	if (mm) {
		REF struct directory_entry *exec_dent;
		sync_read(mm);
		exec_dent = xincref(FORMMAN(mm, thismman_execinfo).mei_dent);
		sync_endread(mm);
		if (!exec_dent)
			goto no_exec;
		FINALLY_DECREF_UNLIKELY(exec_dent);
		if ((*printer)(arg, exec_dent->de_name, exec_dent->de_namelen) < 0)
			goto done;
	} else {
no_exec:
		if ((*printer)(arg, "?", 1) < 0)
			goto done;
	}
	if ((*printer)(arg, ") ", 2) < 0)
		goto done;
	{
		char state;
		if (thread) {
			uintptr_t flags;
			flags = ATOMIC_READ(thread->t_flags);
			if (flags & TASK_FRUNNING)
				state = 'R'; /* Running */
			else if (flags & (TASK_FSUSPENDED | TASK_FGDB_STOPPED))
				state = 'T'; /* Stopped */
			else if (flags & TASK_FSTARTED)
				state = 'S'; /* Sleeping */
			else {
				/* XXX: 'W' For waking??? */
				state = 'P'; /* Parked? */
			}
		} else if (tpid) {
			state = 'Z'; /* Zombie */
		} else {
			state = 'X'; /* Dead */
		}
		if ((*printer)(arg, &state, 1) < 0)
			goto done;
	}
	if (thread) {
		REF struct task *parent;
		parent = task_getprocessparent_of(thread);
		if unlikely(!parent)
			goto noparent;
		FINALLY_DECREF_UNLIKELY(parent);
		if (format_printf(printer, arg, " %" PRIuN(__SIZEOF_PID_T__) " ",
		                  task_gettid_of_s(parent)) < 0)
			goto done;
	} else {
noparent:
		if ((*printer)(arg, " 0 ", 3) < 0)
			goto done;
	}
	if (thread) {
		REF struct task *group;
		group = task_getprocessgroupleader_of(thread);
		if unlikely(!group)
			goto nogroup;
		FINALLY_DECREF_UNLIKELY(group);
		if (format_printf(printer, arg, "%" PRIuN(__SIZEOF_PID_T__) " ",
		                  task_gettid_of_s(group)) < 0)
			goto done;
	} else {
nogroup:
		if ((*printer)(arg, "0 ", 2) < 0)
			goto done;
	}
	if (thread) {
		REF struct task *session;
		REF struct ttybase_device *ctty;
		REF struct taskpid *fproc;
		dev_t tty_devno;
		u32 tty_devno_encoded;
		session = task_getsessionleader_of(thread);
		if unlikely(!session)
			goto nosession;
		FINALLY_DECREF_UNLIKELY(session);
		if (format_printf(printer, arg, "%" PRIuN(__SIZEOF_PID_T__) " ",
		                  task_gettid_of_s(session)) < 0)
			goto done;
		ctty = __TASK_CTTY_FIELD(session).get();
		if (!ctty)
			goto noctty;
		FINALLY_DECREF_UNLIKELY(ctty);
		tty_devno = character_device_devno(ctty);
		tty_devno_encoded = ((MAJOR(tty_devno) & 0xff) << 8) |
		                    ((MINOR(tty_devno) & 0xff) |
		                     (MINOR(tty_devno) & 0xffff00) << 8);
		if (format_printf(printer, arg, "%" PRIu32 " ",
		                  tty_devno_encoded) < 0)
			goto done;
		fproc = ctty->t_fproc.get();
		if (!fproc)
			goto nofproc;
		FINALLY_DECREF_UNLIKELY(fproc);
		if (format_printf(printer, arg, "%" PRIuN(__SIZEOF_PID_T__) " ",
		                  taskpid_getpid_s(fproc)) < 0)
			goto done;
	} else {
nosession:
		if ((*printer)(arg, "0 ", 2) < 0)
			goto done;
noctty:
		if ((*printer)(arg, "0 ", 2) < 0)
			goto done;
nofproc:
		if ((*printer)(arg, "-1 ", 3) < 0)
			goto done;
	}
	if ((*printer)(arg, "0 ", 2) < 0)
		goto done; /* Flags? */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: minflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: cminflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: majflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: cmajflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: utime */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: stime */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: cutime */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: cstime */
	if ((*printer)(arg, "20 ", 2) < 0)
		goto done; /* TODO: priority */
	if ((*printer)(arg, "0 ", 2) < 0)
		goto done; /* TODO: nice */
	/* num_threads */
	if (mm) {
		size_t thread_count = 0;
		struct task *iter;
#ifdef CONFIG_USE_NEW_VM
		mman_threadslock_acquire(mm);
		LIST_FOREACH (iter, &mm->mm_threads, t_mman_tasks) {
			++thread_count;
		}
		mman_threadslock_release(mm);
#else /* CONFIG_USE_NEW_VM */
		sync_read(&mm->v_tasklock);
		LIST_FOREACH (iter, &mm->v_tasks, t_mman_tasks) {
			++thread_count;
		}
		sync_endread(&mm->v_tasklock);
#endif /* !CONFIG_USE_NEW_VM */
		if (format_printf(printer, arg, "%" PRIuSIZ " ",
		                  thread_count) < 0)
			goto done;
	} else {
		if ((*printer)(arg, "1 ", 2) < 0)
			goto done;
	}
	if ((*printer)(arg, "0 ", 2) < 0)
		goto done; /* itrealvalue */
	/* starttimes */
	if ((*printer)(arg, "0 ", 2) < 0)
		goto done;
	if (mm) {
		size_t vsize;
		sync_read(mm);
		vsize = mman_get_total_mapped_bytes(mm);
		sync_endread(mm);
		if (format_printf(printer, arg, "%" PRIuSIZ " ", vsize) < 0)
			goto done;
	} else {
		if ((*printer)(arg, "0 ", 2) < 0)
			goto done; /* vsize */
	}
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: rss */
	if ((*printer)(arg, "1 ", 2) < 0)
		goto done; /* TODO: rsslim */
#ifdef KERNELSPACE_HIGHMEM
	if ((*printer)(arg, "0 ", 2) < 0)
		goto done; /* TODO: startcode */
	if (format_printf(printer, arg, "%" PRIuPTR " ", KERNELSPACE_BASE) < 0)
		goto done; /* TODO: endcode */
#else /* KERNELSPACE_HIGHMEM */
	if (format_printf(printer, arg, "%" PRIuPTR " ", KERNEL_CEILING) < 0)
		goto done; /* TODO: startcode */
	if (format_printf(printer, arg, "%" PRIuPTR " ", (void *)-1) < 0)
		goto done; /* TODO: endcode */
#endif /* !KERNELSPACE_HIGHMEM */
	if (format_printf(printer, arg, "%" PRIuPTR " ", (void *)1234) < 0)
		goto done; /* TODO: startstack */
	if (format_printf(printer, arg, "%" PRIuPTR " ", (void *)1234) < 0)
		goto done; /* TODO: kstkesp */
	if (format_printf(printer, arg, "%" PRIuPTR " ", (void *)1234) < 0)
		goto done; /* TODO: kstkeip */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: signal */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: blocked */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: sigignore */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: sigcatch */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: wchan */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: nswap */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: cnswap */
	if (format_printf(printer, arg, "%" PRIuN(__SIZEOF_SIGNO_T__) " ", SIGCLD) < 0)
		goto done; /* exit_signal */
	if (format_printf(printer, arg, "%u ",
	                  thread ? (unsigned int)thread->t_cpu->c_id
	                         : (unsigned int)_bootcpu.c_id) < 0)
		goto done; /* processor */
	if (format_printf(printer, arg, "%u ", 0) < 0)
		goto done; /* TODO: rt_priority */
	if (format_printf(printer, arg, "%u ", 0) < 0)
		goto done; /* TODO: policy */
	if (format_printf(printer, arg, "%I64u ", (u64)0) < 0)
		goto done; /* TODO: delayacct_blkio_ticks */
	if (format_printf(printer, arg, "%Iu ", 0) < 0)
		goto done; /* TODO: guest_time */
	if (format_printf(printer, arg, "%Id ", 0) < 0)
		goto done; /* TODO: cguest_time */
#ifdef KERNELSPACE_HIGHMEM
	if ((*printer)(arg, "0 ", 2) < 0)
		goto done; /* TODO: start_data */
	if (format_printf(printer, arg, "%" PRIuPTR " ", KERNELSPACE_BASE) < 0)
		goto done; /* TODO: end_data */
#else /* KERNELSPACE_HIGHMEM */
	if (format_printf(printer, arg, "%" PRIuPTR " ", KERNEL_CEILING) < 0)
		goto done; /* TODO: start_data */
	if (format_printf(printer, arg, "%" PRIuPTR " ", (void *)-1) < 0)
		goto done; /* TODO: end_data */
#endif /* !KERNELSPACE_HIGHMEM */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* start_brk... (NOTE: This is maintained by libc, so we can't actually know this one...) */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: arg_start */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: arg_end */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: env_start */
	if (format_printf(printer, arg, "%" PRIuPTR " ", 0) < 0)
		goto done; /* TODO: env_end */
	if (format_printf(printer, arg, "%u ",
	                  tpid ? tpid->tp_status.w_status
	                       : W_EXITCODE(0, 0)) < 0)
		goto done; /* exit_code */
done:
	return 0;
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_STAT_C */
