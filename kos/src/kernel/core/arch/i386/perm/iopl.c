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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IOPL_C
#define GUARD_KERNEL_CORE_ARCH_I386_IOPL_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/panic.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/private.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/x86/eflags-mask.h>
#include <sched/x86/iopl.h>

#include <hybrid/unaligned.h>
#include <hybrid/wordbits.h>

#include <asm/cpu-flags.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <errno.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* When true, iopl() is kept after fork() (w/o CLONE_THREAD) */
PUBLIC bool x86_iopl_keep_after_fork = false;

/* When true, iopl() is kept after clone() (w/ CLONE_THREAD) */
PUBLIC bool x86_iopl_keep_after_clone = true;

INTERN ATTR_FREETEXT void KCALL
x86_init_keepiopl(char const *__restrict arg) {
	for (;;) {
		char const *next;
		size_t len;
		bool setstate = true;
		next = strchrnul(arg, ',');
		len  = (size_t)(next - arg);
		if (len >= 2 && UNALIGNED_GET16((u16 const *)arg) == ENCODE_INT16('n', 'o')) {
			setstate = false;
			len -= 2;
			arg += 2;
		}
		if (len == 4 && UNALIGNED_GET32((u32 const *)arg) == ENCODE_INT32('f', 'o', 'r', 'k')) {
			x86_iopl_keep_after_fork = setstate;
		} else if (len == 4 && UNALIGNED_GET32((u32 const *)arg) == ENCODE_INT32('e', 'x', 'e', 'c')) {
			union x86_user_eflags_mask_union *mask;
			mask = (union x86_user_eflags_mask_union *)&x86_exec_eflags_mask;
			mask->uem_mask &= ~EFLAGS_IOPLMASK;
			if (setstate) /* Keep iopl() during exec() */
				mask->uem_mask |= EFLAGS_IOPLMASK;
		} else if (len == 5 && UNALIGNED_GET32((u32 const *)arg) == ENCODE_INT32('c', 'l', 'o', 'n') && arg[4] == 'e') {
			x86_iopl_keep_after_clone = setstate;
		} else {
			kernel_panic(FREESTR("Unknown argument %$q for `keepiopl'"),
			             len, arg);
		}
		if (!*next)
			break;
		arg = next + 1;
	}
}

DEFINE_CMDLINE_PARAM(x86_init_keepiopl, "keepiopl");

PRIVATE NOBLOCK NONNULL((2)) void
NOTHROW(FCALL cpl_getiopl_impl)(void *buf, struct task *__restrict thread) {
	struct irregs_user *irregs;
	irregs = x86_get_irregs(thread);
	if (thread == THIS_TASK) {
		*(uintptr_t *)buf = irregs_getpflags(irregs);
	} else {
		*(uintptr_t *)buf = irregs->ir_Pflags;
	}
}

struct set_iopl_args {
	union {
		unsigned int ia_new_iopl; /* IN:  The new iopl() value */
		unsigned int ia_old_iopl; /* OUT: The old iopl() value */
	};
	union {
		bool ia_allow_iopl_change; /* `true' if iopl() changes are allowed. */
		bool ia_was_set;           /* Set to true/false indicating if iopl() was set. (though not necessary changed) */
	};
};

PRIVATE NOBLOCK NONNULL((2)) void
NOTHROW(FCALL cpl_setiopl_impl)(void *buf, struct task *__restrict thread) {
	struct set_iopl_args *args;
	struct irregs_user *irregs;
	uintptr_t old_pflags, new_pflags;
	unsigned int old_iopl;
	bool allow_change, was_set;
	irregs = x86_get_irregs(thread);
	args   = (struct set_iopl_args *)buf;
	allow_change = args->ia_allow_iopl_change;
	old_pflags = thread == THIS_TASK
	             ? irregs_getpflags(irregs)
	             : irregs->ir_Pflags;
	old_iopl   = EFLAGS_GTIOPL(old_pflags);
	if (old_iopl == args->ia_new_iopl) {
		was_set = true;
	} else if (!allow_change) {
		was_set = false;
	} else {
		new_pflags = (old_pflags & ~EFLAGS_IOPLMASK) | EFLAGS_IOPL(args->ia_new_iopl);
		was_set = true;
		if (thread == THIS_TASK) {
			irregs_setpflags(irregs, new_pflags);
		} else {
			irregs->ir_Pflags = new_pflags;
		}
	}
	args->ia_old_iopl = old_iopl;
	args->ia_was_set  = was_set;
}

/* Get/Set the iopl() value of the given thread.
 * @return: * : All functions return the iopl() active prior to the call being made. */
PUBLIC unsigned int KCALL
x86_getiopl(struct task *__restrict thread) {
	uintptr_t pflags;
	cpu_private_function_call(thread, &cpl_getiopl_impl, &pflags);
	return EFLAGS_GTIOPL(pflags);
}

PUBLIC unsigned int KCALL
x86_setiopl(struct task *__restrict thread,
            unsigned int new_iopl,
            bool check_creds) {
	struct set_iopl_args args;
again:
	args.ia_new_iopl          = new_iopl;
	args.ia_allow_iopl_change = !check_creds || capable(CAP_SYS_RAWIO);
	cpu_private_function_call(thread, &cpl_setiopl_impl, &args);
	if (!args.ia_was_set) {
		require(CAP_SYS_RAWIO);
		goto again;
	}
	return args.ia_old_iopl;
}



INTERN struct icpustate *FCALL
sys_iopl_impl(struct icpustate *__restrict state,
              syscall_ulong_t level) {
	uintptr_t pflags;
	syscall_ulong_t old_level;
	if (level > 3) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_IOPL_LEVEL,
		      level);
	}
	pflags    = icpustate_getpflags(state);
	old_level = EFLAGS_GTIOPL(pflags);
	/* Only require HWIO permissions when raising the IOPL level. */
	if (level > old_level)
		require(CAP_SYS_RAWIO);
	/* Set the new PFLAGS value to reflect
	 * the updated IOPL permissions level. */
	pflags = (pflags & ~EFLAGS_IOPLMASK) | EFLAGS_IOPL(level);
	icpustate_setpflags(state, pflags);
	gpregs_setpax(&state->ics_gpregs, -EOK);
	return state;
}


PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_iopl_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	ctx->rc_state = sys_iopl_impl(ctx->rc_state, ctx->rc_scinfo.rsi_regs[0]);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL1(errno_t, iopl, syscall_ulong_t, level) {
	(void)level;

	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_iopl_rpc, NULL);
	__builtin_unreachable();
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IOPL_C */
