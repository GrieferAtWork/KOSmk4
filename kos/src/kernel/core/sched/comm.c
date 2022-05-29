/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_COMM_C
#define GUARD_KERNEL_SRC_SCHED_COMM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <sched/comm.h>

#ifdef CONFIG_HAVE_TASK_COMM
#include <kernel/malloc.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sig.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <kos/except.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* [lock(PRIVATE(THIS_TASK))]
 * Task command name.
 * - Set to the basename() of the executable during exec()
 * - Inherited during clone()
 * - Read/write using /proc/[pid]/comm
 * - Guarantied to be NUL-terminated */
PUBLIC ATTR_PERTASK ATTR_ALIGN(char) this_comm[TASK_COMM_LEN] = "";

/* Get the command name of an arbitrary thread */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_getcomm_of)(struct task const *__restrict self,
                               char buf[TASK_COMM_LEN]) {
	char const *name = FORTASK(self, this_comm);
	unsigned int i;
again:
	memcpy(buf, name, TASK_COMM_LEN, sizeof(char));
	COMPILER_READ_BARRIER();
	/* For the duration of changing the name, a thread sets all
	 * characters to `0xff'  (which as a  byte can't appear  in
	 * proper UTF-8 as defined by the standard) */
	for (i = 0; i < TASK_COMM_LEN; ++i) {
		if (buf[i] == (char)0xff) {
			preemption_tryyield();
			goto again;
		}
	}
}


#define TASK_SETCOMM_RPC_ST_PENDING 0x00 /* Operation is pending */
#define TASK_SETCOMM_RPC_ST_WORKING 0x01 /* Operation is in progress (and can no longer be aborted) */
#define TASK_SETCOMM_RPC_ST_DONE    0x02 /* Operation has finished */
#define TASK_SETCOMM_RPC_ST_DEAD    0x03 /* Operation was aborted, or thread is dead. */
struct task_setcomm_rpc: pending_rpc_head {
	WEAK refcnt_t tscr_refcnt;              /* Reference counter. */
	struct sig    tscr_done;                /* Broadcast when setcomm finishes. */
	unsigned int  tscr_state;               /* One of `TASK_SETCOMM_RPC_ST_*' */
	char          tscr_name[TASK_COMM_LEN]; /* The new name that should be set. */
};
DEFINE_REFCNT_FUNCTIONS(struct task_setcomm_rpc, tscr_refcnt, kfree)

PRIVATE NONNULL((1, 2)) void
NOTHROW(PRPC_EXEC_CALLBACK_CC task_setcomm_rpcfun)(struct rpc_context *__restrict ctx,
                                                   void *cookie) {
	REF struct task_setcomm_rpc *me;
	me = (REF struct task_setcomm_rpc *)cookie;
	if (ctx->rc_context == RPC_REASONCTX_SHUTDOWN) {
		ATOMIC_WRITE(me->tscr_state, TASK_SETCOMM_RPC_ST_DEAD);
	} else if (ATOMIC_CMPXCH(me->tscr_state,
	                         TASK_SETCOMM_RPC_ST_PENDING,
	                         TASK_SETCOMM_RPC_ST_WORKING)) {
		task_setcomm(me->tscr_name);
		ATOMIC_WRITE(me->tscr_state, TASK_SETCOMM_RPC_ST_DONE);
	}
	sig_broadcast(&me->tscr_done);
	decref(me);
}


/* Set the command name of an arbitrary thread
 * NOTES:
 *  - `name' must be NUL-terminated and not longer than `TASK_COMM_LEN'!
 *    When `name[TASK_COMM_LEN-1]' isn't NUL,  it will be replaced  with
 *    that character in `this_comm'
 *  - `name' must not contain any 0xff bytes. If any byte with that value
 *    is encountered, it will be replaced by `0x00'
 * @return: true:  Success
 * @return: false: Thread has already exited */
FUNDEF BLOCKING NONNULL((1, 2)) bool FCALL
task_setcomm_of(struct task *__restrict self, char const *__restrict name)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC) {
	unsigned int status;
	REF struct task_setcomm_rpc *rpc;
	assert(!task_wasconnected());
	if (self == THIS_TASK) {
		/* Special (and much simpler) case: change our own name */
		task_setcomm(name);
		return true;
	}
	rpc = (struct task_setcomm_rpc *)kmalloc(sizeof(struct task_setcomm_rpc), GFP_NORMAL);
	rpc->prh_flags   = RPC_CONTEXT_KERN | RPC_CONTEXT_NOEXCEPT | _RPC_CONTEXT_DONTFREE;
	rpc->prh_func    = &task_setcomm_rpcfun;
	rpc->tscr_refcnt = 2; /* +1: `rpc', +1: `task_setcomm_rpcfun' */
	rpc->tscr_state  = TASK_SETCOMM_RPC_ST_PENDING;
	sig_init(&rpc->tscr_done);
	memcpy(rpc->tscr_name, name, TASK_COMM_LEN, sizeof(char));
	COMPILER_BARRIER();
	task_connect(&rpc->tscr_done);

	/* Send the RPC to the given thread */
	if (!task_rpc_schedule(self, rpc)) {
		/* Thread already exited. */
		task_disconnectall();
		kfree(rpc);
		return false;
	}

	/* Because `this_comm' can only be changed by `THIS_TASK', we have to
	 * send  an RPC to the given `self' that will apply the new name. But
	 * because we're supposed to be a synchronous operation, we also have
	 * to wait for that RPC to complete. */
	FINALLY_DECREF(rpc);
	TRY {
		for (;;) {
			task_waitfor();
			status = ATOMIC_READ(rpc->tscr_state);
			if (status != TASK_SETCOMM_RPC_ST_PENDING &&
			    status != TASK_SETCOMM_RPC_ST_WORKING)
				break;
			task_connect(&rpc->tscr_done);
		}
	} EXCEPT {
		/* Try to abort the rename operation. */
		if (!ATOMIC_CMPXCH(rpc->tscr_state,
		                   TASK_SETCOMM_RPC_ST_PENDING,
		                   TASK_SETCOMM_RPC_ST_DEAD) &&
		    was_thrown(E_INTERRUPT_USER_RPC))
			goto force_wait_for;
		RETHROW();
	}

	/* Success is indicated by `task_setcomm_rpcfun()' */
	return status == TASK_SETCOMM_RPC_ST_DONE;
force_wait_for:
	while (ATOMIC_READ(rpc->tscr_state) == TASK_SETCOMM_RPC_ST_WORKING)
		preemption_tryyield();
	return true;
}


/* Same as `task_setcomm_of()', but set for the calling thread. */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL task_setcomm)(char const *__restrict name) {
	preemption_flag_t was;
	size_t len;
	char *nameptr = PERTASK(this_comm);
	char used_newname[TASK_COMM_LEN];
	size_t namelen = strnlen(name, TASK_COMM_LEN - 1);
	memcpy(used_newname, name, namelen, sizeof(char));
	used_newname[namelen] = '\0';
	len = strlen(used_newname);
	len = memlen(used_newname, 0xff, len * sizeof(char)) / sizeof(char); /* Treat 0xff the same as 0x00 */

	/* Force all characters after the first 0x00 or 0xff to become 0x00 */
	bzero(used_newname + len, TASK_COMM_LEN - len, sizeof(char));

	/* This is how we change the task name:
	 * - We  disable preemption, thus  only making it possible
	 *   for other CPUs to potentially read our thread's name.
	 * - We then set all characters  to 0xff. -- If another  CPU
	 *   now uses `task_getcomm_of()', that function will notice
	 *   the 0xff bytes and keep on looping until they disappear
	 * - We then fill in the new task name. We know that the new
	 *   name doesn't contain 0xff, so once all characters  have
	 *   been written, other CPUs will stop seeing them and know
	 *   that the new name is now complete
	 * ---
	 * This way we can set our own name without blocking, and any
	 * thread  is able to  read the name  of another thread, also
	 * without blocking (since waiting for another CPU in SMP can
	 * be considered as non-blocking) */
	preemption_pushoff(&was);
	COMPILER_BARRIER();
	memset(nameptr, 0xff, TASK_COMM_LEN, sizeof(char));
	COMPILER_BARRIER();
	memcpy(nameptr, used_newname, TASK_COMM_LEN, sizeof(char));
	COMPILER_BARRIER();
	preemption_pop(&was);

}



DECL_END
#endif /* CONFIG_HAVE_TASK_COMM */

#endif /* !GUARD_KERNEL_SRC_SCHED_COMM_C */
