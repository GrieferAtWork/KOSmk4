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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_HANDLE_C
#define GUARD_KERNEL_SRC_SCHED_TASK_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/mman.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <kos/hop/task.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

/* Task HOP functions */
DEFINE_HANDLE_REFCNT_FUNCTIONS(task, struct taskpid);
INTERN void KCALL
handle_task_stat(struct taskpid *__restrict self,
                 USER CHECKED struct stat *result) {
	memset(result, 0, sizeof(*result));
	/* TODO: st_ctim: Thread creation time? */
	/* TODO: st_atim: End of the latest quantum */
	/* TODO: st_mtim: Start of the latest quantum */
	(void)self;
}

INTERN void KCALL
handle_task_pollconnect(struct taskpid *__restrict self, poll_mode_t what) {
	/* POLLINMASK: Terminated */
	if (what & POLLINMASK)
		task_connect_for_poll(&self->tp_changed);
}

INTERN ATTR_PURE WUNUSED poll_mode_t KCALL
handle_task_polltest(struct taskpid *__restrict self, poll_mode_t what) {
	poll_mode_t result = 0;
	/* POLLINMASK: Terminated */
	if (what & POLLINMASK) {
		if (WIFEXITED(self->tp_status))
			result |= POLLINMASK;
	}
	return result;
}

INTERN syscall_slong_t KCALL
handle_task_hop(struct taskpid *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode) {
	switch (cmd) {

	case HOP_TASK_JOIN: {
		size_t struct_size;
		USER CHECKED struct hop_task_join *data;
		validate_readwrite(arg, sizeof(struct hop_task_join));
		data        = (struct hop_task_join *)arg;
		struct_size = ATOMIC_READ(data->tj_struct_size);
		if (struct_size != sizeof(struct hop_task_join))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_task_join), struct_size);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		COMPILER_BARRIER();
		if (WIFEXITED(self->tp_status)) {
			ATOMIC_WRITE(data->tj_status, (u32)self->tp_status.w_status);
		} else {
			ktime_t abs_timeout;
			struct timespec ts;
			COMPILER_READ_BARRIER();
			ts.tv_sec  = data->tj_reltimeout_sec;
			ts.tv_nsec = data->tj_reltimeout_nsec;
			COMPILER_READ_BARRIER();
			abs_timeout = relktime_from_user_rel(&ts);
			if (abs_timeout != 0)
				abs_timeout += ktime();
again_waitfor:
			task_connect_for_poll(&self->tp_changed);
			COMPILER_READ_BARRIER();
			if (WIFEXITED(self->tp_status)) {
				task_disconnectall();
				ATOMIC_WRITE(data->tj_status, (u32)self->tp_status.w_status);
				break;
			}
			if (!task_waitfor(abs_timeout)) {
				task_disconnectall();
				ATOMIC_WRITE(data->tj_status, 0);
				return -ETIMEDOUT; /* Timeout */
			}
			assert(!task_wasconnected());
			if (WIFEXITED(self->tp_status)) {
				ATOMIC_WRITE(data->tj_status, (u32)self->tp_status.w_status);
				break;
			}
			goto again_waitfor;
		}
	}	break;

	case HOP_TASK_GETTID:
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		return taskpid_getpid(self, THIS_PIDNS);

	case HOP_TASK_GETPID: {
		upid_t result;
		REF struct task *thread;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		result = task_getpid_of_s(thread);
		decref_unlikely(thread);
		return result;
	}	break;

	case HOP_TASK_GETPPID: {
		upid_t result;
		REF struct task *thread;
		REF struct task *parent;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		parent = task_getprocessparent_of(thread);
		if unlikely(!parent)
			result = 0;
		else {
			result = task_gettid_of_s(parent);
			decref_unlikely(parent);
		}
		return result;
	}	break;

	case HOP_TASK_GETPGID: {
		upid_t result;
		REF struct task *thread;
		REF struct taskpid *leader;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		leader = task_getprocessgroupleaderpid_of(thread);
		result = taskpid_getpid_s(leader);
		decref_unlikely(leader);
		return result;
	}	break;

	case HOP_TASK_GETSID: {
		upid_t result;
		REF struct task *thread;
		REF struct taskpid *leader;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		leader = task_getsessionleaderpid_of(thread);
		result = taskpid_getpid_s(leader);
		decref_unlikely(leader);
		return result;
	}	break;

	case HOP_TASK_OPEN_PROCESS: {
		REF struct task *thread;
		struct handle leader;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		leader.h_type = HANDLE_TYPE_TASK;
		leader.h_mode = mode;
		leader.h_data = task_getprocesspid_of(thread);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, leader);
	}	break;

	case HOP_TASK_OPEN_PROCESS_PARENT: {
		REF struct task *thread;
		struct handle parent;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		parent.h_type = HANDLE_TYPE_TASK;
		parent.h_mode = mode;
		parent.h_data = task_getprocessparentpid_of(thread);
		if unlikely(!parent.h_data)
			THROW(E_NO_SUCH_PROCESS);
		FINALLY_DECREF_UNLIKELY((struct taskpid *)parent.h_data);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, parent);
	}	break;

	case HOP_TASK_OPEN_PROCESS_GROUP_LEADER: {
		REF struct task *thread;
		struct handle leader;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		leader.h_type = HANDLE_TYPE_TASK;
		leader.h_mode = mode;
		leader.h_data = task_getprocessgroupleaderpid_of(thread);
		FINALLY_DECREF_UNLIKELY((struct taskpid *)leader.h_data);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, leader);
	}	break;

	case HOP_TASK_OPEN_SESSION_LEADER: {
		REF struct task *thread;
		struct handle leader;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		leader.h_type = HANDLE_TYPE_TASK;
		leader.h_mode = mode;
		leader.h_data = task_getsessionleaderpid_of(thread);
		FINALLY_DECREF_UNLIKELY((struct taskpid *)leader.h_data);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, leader);
	}	break;

	case HOP_TASK_IS_PROCESS_LEADER: {
		REF struct task *thread;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		return task_isprocessleader_p(thread) ? 1 : 0;
	}	break;

	case HOP_TASK_IS_PROCESS_GROUP_LEADER: {
		REF struct task *thread;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		return task_isprocessgroupleader_p(thread) ? 1 : 0;
	}	break;

	case HOP_TASK_IS_SESSION_LEADER: {
		REF struct task *thread;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		return task_issessionleader_p(thread) ? 1 : 0;
	}	break;

	case HOP_TASK_DETACH: {
		REF struct task *thread;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		return task_detach(thread) ? 1 : 0;
	}	break;

	case HOP_TASK_DETACH_CHILDREN: {
		REF struct task *thread;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		thread = taskpid_gettask(self);
		if unlikely(!thread)
			goto err_exited;
		FINALLY_DECREF_UNLIKELY(thread);
		return task_detach_children(task_getprocess_of(thread));
	}	break;

	case HOP_TASK_SETPROCESSGROUPLEADER: {
		REF struct task *thread;
		REF struct task *leader;
		REF struct taskpid *leader_pid;
		REF struct taskpid *old_group_leader;
		REF struct taskpid *new_group_leader;
		unsigned int error;
		size_t struct_size;
		USER CHECKED struct hop_task_setprocessgroupleader *data;
		STATIC_ASSERT(HOP_TASK_SETPROCESSGROUPLEADER_SUCCESS == TASK_SETPROCESSGROUPLEADER_SUCCESS);
		STATIC_ASSERT(HOP_TASK_SETPROCESSGROUPLEADER_LEADER == TASK_SETPROCESSGROUPLEADER_LEADER);
		STATIC_ASSERT(HOP_TASK_SETPROCESSGROUPLEADER_EXITED == TASK_SETPROCESSGROUPLEADER_EXITED);
		validate_readwrite(arg, sizeof(struct hop_task_setprocessgroupleader));
		data        = (struct hop_task_setprocessgroupleader *)arg;
		struct_size = ATOMIC_READ(data->tspgl_struct_size);
		if (struct_size != sizeof(struct hop_task_setprocessgroupleader))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_task_setprocessgroupleader), struct_size);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		COMPILER_BARRIER();
		{
			thread = taskpid_gettask(self);
			if unlikely(!thread)
				goto err_exited;
			FINALLY_DECREF_UNLIKELY(thread);
			{
				leader_pid = handle_get_taskpid(ATOMIC_READ(data->tspgl_leader));
				FINALLY_DECREF_UNLIKELY(leader_pid);
				leader = taskpid_gettask(leader_pid);
				if unlikely(!leader)
					return HOP_TASK_SETPROCESSGROUPLEADER_EXITED;
			}
			FINALLY_DECREF_UNLIKELY(leader);
			error = task_setprocessgroupleader(thread,
			                                   leader,
			                                   &old_group_leader,
			                                   &new_group_leader);
			if (error != TASK_SETPROCESSGROUPLEADER_SUCCESS)
				return error;
		}
		FINALLY_DECREF_UNLIKELY(old_group_leader);
		FINALLY_DECREF_UNLIKELY(new_group_leader);
		{
			USER UNCHECKED struct hop_openfd *fd;
			fd = ATOMIC_READ(data->tspgl_old_leader);
			if (fd) {
				struct handle temp;
				temp.h_type = HANDLE_TYPE_TASK;
				temp.h_mode = mode;
				temp.h_data = old_group_leader;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->tspgl_new_leader);
			if (fd) {
				struct handle temp;
				temp.h_type = HANDLE_TYPE_TASK;
				temp.h_mode = mode;
				temp.h_data = new_group_leader;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_TASK_SETSESSIONLEADER: {
		REF struct task *thread;
		REF struct task *leader;
		REF struct taskpid *old_group_leader;
		REF struct taskpid *old_session_leader;
		REF struct taskpid *new_session_leader;
		unsigned int error;
		size_t struct_size;
		USER CHECKED struct hop_task_setsessionleader *data;
		STATIC_ASSERT(HOP_TASK_SETSESSIONLEADER_SUCCESS == TASK_SETSESSIONLEADER_SUCCESS);
		STATIC_ASSERT(HOP_TASK_SETSESSIONLEADER_LEADER == TASK_SETSESSIONLEADER_LEADER);
		validate_readwrite(arg, sizeof(struct hop_task_setsessionleader));
		data        = (struct hop_task_setsessionleader *)arg;
		struct_size = ATOMIC_READ(data->tssl_struct_size);
		if (struct_size != sizeof(struct hop_task_setsessionleader))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_task_setsessionleader), struct_size);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		COMPILER_BARRIER();
		{
			thread = taskpid_gettask(self);
			if unlikely(!thread)
				goto err_exited;
			FINALLY_DECREF_UNLIKELY(thread);
			leader = handle_get_task(ATOMIC_READ(data->tssl_leader));
			FINALLY_DECREF_UNLIKELY(leader);
			error = task_setsessionleader(thread,
			                              leader,
			                              &old_group_leader,
			                              &old_session_leader,
			                              &new_session_leader);
			if (error != TASK_SETSESSIONLEADER_SUCCESS)
				return error;
		}
		FINALLY_DECREF_UNLIKELY(old_group_leader);
		FINALLY_DECREF_UNLIKELY(old_session_leader);
		FINALLY_DECREF_UNLIKELY(new_session_leader);
		{
			USER UNCHECKED struct hop_openfd *fd;
			fd = ATOMIC_READ(data->tssl_old_grp_leader);
			if (fd) {
				struct handle temp;
				temp.h_type = HANDLE_TYPE_TASK;
				temp.h_mode = mode;
				temp.h_data = old_group_leader;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->tssl_old_leader);
			if (fd) {
				struct handle temp;
				temp.h_type = HANDLE_TYPE_TASK;
				temp.h_mode = mode;
				temp.h_data = old_session_leader;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->tssl_new_leader);
			if (fd) {
				struct handle temp;
				temp.h_type = HANDLE_TYPE_TASK;
				temp.h_mode = mode;
				temp.h_data = new_session_leader;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
err_exited:
	THROW(E_PROCESS_EXITED,
	      taskpid_getpid(self, THIS_PIDNS));
}


INTERN NONNULL((1)) REF void *KCALL
handle_task_tryas(struct taskpid *__restrict self,
                  uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {

	case HANDLE_TYPE_MMAN:
		if (self != THIS_TASKPID)
			break;
		return incref(THIS_MMAN);

	case HANDLE_TYPE_FS:
		if (self != THIS_TASKPID)
			break;
		return incref(THIS_FS);

	case HANDLE_TYPE_PIDNS:
		if (self != THIS_TASKPID)
			break;
		return incref(THIS_PIDNS);

	default: break;
	}
	return NULL;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_HANDLE_C */
