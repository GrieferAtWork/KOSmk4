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
#ifndef GUARD_KERNEL_SRC_SCHED_USERKERN_C
#define GUARD_KERNEL_SRC_SCHED_USERKERN_C 1

#include <kernel/compiler.h>

#include <sched/userkern.h>
#ifndef CONFIG_NO_USERKERN_SEGMENT
#ifndef CONFIG_USERKERN_SEGMENT_IMPLEMENTATION_IS_ARCH_SPECIFIC

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <sched/pertask.h>
#include <sched/pid.h>
#include <sched/cred.h>

#include <kos/ukern.h>

DECL_BEGIN

/* These 2 functions must be overwritten to implement arch-specific behavior.
 * Mainly: To implement access to the register identity map structure. */
INTDEF NONNULL((1)) bool KCALL
userkern_get_arch_specific_field(struct vio_args *__restrict args,
                                 uintptr_t offset, uintptr_t *__restrict presult);
INTDEF NONNULL((1)) bool KCALL
userkern_set_arch_specific_field(struct vio_args *__restrict args,
                                 uintptr_t offset, uintptr_t value);


INTERN NONNULL((1)) uintptr_t KCALL
userkern_segment_read(struct vio_args *__restrict args,
                      vm_daddr_t addr) {
	uintptr_t result;
	uintptr_t reladdr;
	uintptr_t base = get_userkern_base();
	if (!ADDR_IS_KERNEL(base))
		goto err_invalid_addr;
#ifdef HIGH_MEMORY_KERNEL
	base -= KERNEL_BASE;
#endif /* HIGH_MEMORY_KERNEL */
	if ((uintptr_t)addr < base)
		goto err_invalid_addr;
	reladdr = (uintptr_t)addr - base;
	switch (reladdr) {

	case offsetof(struct userkern, uk_base):
		result = base;
		break;

	case offsetof(struct userkern, uk_tid):
		result = task_gettid();
		break;

	case offsetof(struct userkern, uk_pid):
		result = task_getpid();
		break;

	case offsetof(struct userkern, uk_ppid): {
		REF struct task *parent;
		result = 0;
		parent = task_getprocessparent();
		if likely(parent) {
			result = task_getpid_of(parent);
			decref(parent);
		}
	}	break;

	case offsetof(struct userkern, uk_pgid): {
		REF struct task *leader;
		leader = task_getprocessgroupleader();
		result = task_getpid_of(leader);
		decref(leader);
	}	break;

	case offsetof(struct userkern, uk_sid): {
		REF struct task *leader;
		leader = task_getsessionleader();
		result = task_getpid_of(leader);
		decref(leader);
	}	break;

	case offsetof(struct userkern, uk_uid):
		result = cred_getuid();
		break;

	case offsetof(struct userkern, uk_gid):
		result = cred_getgid();
		break;

	case offsetof(struct userkern, uk_euid):
		result = cred_geteuid();
		break;

	case offsetof(struct userkern, uk_egid):
		result = cred_getegid();
		break;

	case offsetof(struct userkern, uk_suid):
		result = cred_getsuid();
		break;

	case offsetof(struct userkern, uk_sgid):
		result = cred_getsgid();
		break;

	default:
		if unlikely(!userkern_get_arch_specific_field(args, reladdr, &result)) {
			if (reladdr < sizeof(struct userkern)) {
				addr -= (vm_daddr_t)args->va_access_partoff;
				addr += (vm_daddr_t)args->va_access_pageaddr * PAGESIZE;
				THROW(E_SEGFAULT_NOTREADABLE,
				      (uintptr_t)addr,
				      E_SEGFAULT_CONTEXT_USERCODE);
			}
			goto err_invalid_addr;
		}
		break;
	}
	return result;
err_invalid_addr:
	addr -= (vm_daddr_t)args->va_access_partoff;
	addr += (vm_daddr_t)args->va_access_pageaddr * PAGESIZE;
	THROW(E_SEGFAULT_UNMAPPED,
	      (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_USERCODE);
}


INTERN NONNULL((1)) void KCALL
userkern_segment_write(struct vio_args *__restrict args,
                       vm_daddr_t addr, uintptr_t value) {
	uintptr_t reladdr;
	uintptr_t base = get_userkern_base();
	if (!ADDR_IS_KERNEL(base))
		goto err_invalid_addr;
#ifdef HIGH_MEMORY_KERNEL
	base -= KERNEL_BASE;
#endif /* HIGH_MEMORY_KERNEL */
	if ((uintptr_t)addr < base)
		goto err_invalid_addr;
	reladdr = (uintptr_t)addr - base;
	switch (reladdr) {

	case offsetof(struct userkern, uk_base):
		/* Re-assign the base address of the user-thread segment. */
		if (!ADDR_IS_KERNEL(value))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE,
			      value);
		set_userkern_base(value);
		break;

	case offsetof(struct userkern, uk_ppid):
		if (value != 0)
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_USERKERN_PPID,
			      value);
		task_detach(task_getprocess());
		break;

	case offsetof(struct userkern, uk_pgid): {
		struct task *caller;
		caller = THIS_TASK;
		if (value == 0)
			task_setprocessgroupleader(THIS_TASK, caller);
		else {
			unsigned int error;
			REF struct task *group;
			group = pidns_lookup_task(THIS_PIDNS, value);
			{
				FINALLY_DECREF_UNLIKELY(group);
				error = task_setprocessgroupleader(caller, group);
			}
			if (error == TASK_SETPROCESSGROUPLEADER_EXITED)
				THROW(E_PROCESS_EXITED, (upid_t)value);
			if (error == TASK_SETPROCESSGROUPLEADER_LEADER) {
				THROW(E_ILLEGAL_PROCESS_OPERATION,
				      (upid_t)0,
				      E_ILLEGAL_PROCESS_OPERATION_SETPGID_LEADER,
				      (upid_t)value);
			}
		}
	}	break;

	case offsetof(struct userkern, uk_sid): {
		struct task *caller;
		caller = THIS_TASK;
		if (value != 0 &&
		    value != task_gettid_of(THIS_TASK) &&
		    value != task_getpid_of(THIS_TASK))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_USERKERN_SID,
			      value);
		task_setsessionleader(caller,
		                      caller,
		                      NULL,
		                      NULL,
		                      NULL);
	}	break;

	case offsetof(struct userkern, uk_uid):
		cred_setuid(value);
		break;

	case offsetof(struct userkern, uk_gid):
		cred_setgid(value);
		break;

	case offsetof(struct userkern, uk_euid):
		cred_seteuid(value);
		break;

	case offsetof(struct userkern, uk_egid):
		cred_setegid(value);
		break;

	case offsetof(struct userkern, uk_suid):
		cred_setsuid(value);
		break;

	case offsetof(struct userkern, uk_sgid):
		cred_setsgid(value);
		break;

	default:
		if unlikely(!userkern_set_arch_specific_field(args, reladdr, value)) {
			if (reladdr < sizeof(struct userkern)) {
				addr -= (vm_daddr_t)args->va_access_partoff;
				addr += (vm_daddr_t)args->va_access_pageaddr * PAGESIZE;
				THROW(E_SEGFAULT_READONLY,
				      (uintptr_t)addr,
				      E_SEGFAULT_CONTEXT_USERCODE);
			}
		}
		break;
	}
	return;
err_invalid_addr:
	addr -= (vm_daddr_t)args->va_access_partoff;
	addr += (vm_daddr_t)args->va_access_pageaddr * PAGESIZE;
	THROW(E_SEGFAULT_UNMAPPED,
	      (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_USERCODE);
}



PRIVATE struct icpustate *KCALL
userkern_segment_call(struct vio_args *__restrict args,
                      struct icpustate *__restrict regs,
                      vm_daddr_t addr) {
	uintptr_t reladdr;
	uintptr_t base = get_userkern_base();
	if (!ADDR_IS_KERNEL(base))
		goto err_invalid_addr;
#ifdef HIGH_MEMORY_KERNEL
	base -= KERNEL_BASE;
#endif /* HIGH_MEMORY_KERNEL */
	if ((uintptr_t)addr < base)
		goto err_invalid_addr;
	reladdr = (uintptr_t)addr - base;
	if (!USERKERN_SYSCALL_ISVALID(reladdr))
		goto err_invalid_addr;
	/* System call invocation. */
	regs = syscall_emulate_callback(regs,
	                                USERKERN_SYSCALL_DECODE(reladdr),
	                                (reladdr & USERKERN_SYSCALL_EXCEPTBIT) != 0);
	return regs;
err_invalid_addr:
	addr -= (vm_daddr_t)args->va_access_partoff;
	addr += (vm_daddr_t)args->va_access_pageaddr * PAGESIZE;
	THROW(E_SEGFAULT_UNMAPPED,
	      (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_USERCODE);
}



#if __SIZEOF_POINTER__ >= 8
#ifndef CONFIG_VIO_HAS_QWORD
#error "Invalid configuration"
#endif
#define INIT_OPERATION_PTR(fun) { NULL, NULL, NULL, fun }
#elif defined(CONFIG_VIO_HAS_QWORD)
#define INIT_OPERATION_PTR(fun) { NULL, NULL, fun, NULL }
#else
#define INIT_OPERATION_PTR(fun) { NULL, NULL, fun }
#endif

/* VIO bindings for the kernel-reserve segment of user-space VMs */
PUBLIC struct vm_datablock_type_vio userkern_segment_vio = {
	/* .dtv_read   = */ INIT_OPERATION_PTR(&userkern_segment_read),
	/* .dtv_write  = */ INIT_OPERATION_PTR(&userkern_segment_write),
	/* .dtv_cmpxch = */ INIT_OPERATION_PTR(NULL),
	/* .dtv_xch    = */ INIT_OPERATION_PTR(NULL),
	/* .dtv_add    = */ INIT_OPERATION_PTR(NULL),
	/* .dtv_sub    = */ INIT_OPERATION_PTR(NULL),
	/* .dtv_and    = */ INIT_OPERATION_PTR(NULL),
	/* .dtv_or     = */ INIT_OPERATION_PTR(NULL),
	/* .dtv_xor    = */ INIT_OPERATION_PTR(NULL),
	/* .dtv_call   = */ &userkern_segment_call
};
#undef INIT_OPERATION_PTR

PUBLIC struct vm_datapart userkern_segment_part = {
	/* .dp_refcnt = */ 1,
	/* .dp_lock   = */ SHARED_RWLOCK_INIT,
	{
		/* .dp_tree_ptr = */ {
			/* .a_min = */ NULL,
			/* .a_max = */ NULL,
			{ /* .a_vmin_ptr = */ 0 },
			{ /* .a_vmax_ptr = */ KERNEL_NUM_PAGES - 1 },
		}
	},
	/* .dp_crefs  = */ LLIST_INIT,
	/* .dp_srefs  = */ LLIST_INIT,
	/* .dp_stale  = */ NULL,
	/* .dp_block  = */ &userkern_segment_block,
	/* .dp_flags  = */ (VM_DATAPART_FLAG_LOCKED |
	                   VM_DATAPART_FLAG_CHANGED |
	                   VM_DATAPART_FLAG_KEEPRAM |
	                   VM_DATAPART_FLAG_HEAPPPP |
	                   VM_DATAPART_FLAG_KERNPRT),
	/* .dp_state  = */ VM_DATAPART_STATE_VIOPRT,
	{
		/* .dp_ramdata = */ {
			/* .rd_blockv = */ NULL,
			{
				/* .rd_block0 = */ {
					/* .rb_start = */ 0,
					/* .rb_size  = */ 0
				}
			}
		}
	},
	{
		/* .dp_pprop_p = */ 0
	},
	/* .dp_futex = */ NULL
};

PUBLIC struct vm_datablock userkern_segment_block = {
	/* .db_refcnt = */ 2, /* +1: `userkern_segment_block', +1: `userkern_segment_part.dp_block' */
	/* .db_lock   = */ RWLOCK_INIT,
	/* .db_type   = */ &vm_datablock_anonymous_type,
	/* .db_vio    = */ &userkern_segment_vio,
	/* .db_parts  = */ &userkern_segment_part,
	VM_DATABLOCK_INIT_PAGEINFO(0)
};


DECL_END

#endif /* !CONFIG_USERKERN_SEGMENT_IMPLEMENTATION_IS_ARCH_SPECIFIC */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */


#endif /* !GUARD_KERNEL_SRC_SCHED_USERKERN_C */
