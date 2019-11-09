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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_C
#define GUARD_KERNEL_SRC_SCHED_TASK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/debugger.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/panic.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <sys/wait.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#ifndef CONFIG_NO_DEBUGGER
#include "../memory/vm/vm-nodeapi.h"
#endif /* !CONFIG_NO_DEBUGGER */

DECL_BEGIN

INTDEF byte_t __kernel_pertask_start[];
INTDEF byte_t __kernel_pertask_size[];
STATIC_ASSERT(offsetof(struct task, t_self) == OFFSET_TASK_SELF);
STATIC_ASSERT(offsetof(struct task, t_refcnt) == OFFSET_TASK_REFCNT);
STATIC_ASSERT(offsetof(struct task, t_flags) == OFFSET_TASK_FLAGS);
STATIC_ASSERT(offsetof(struct task, t_cpu) == OFFSET_TASK_CPU);
STATIC_ASSERT(offsetof(struct task, t_vm) == OFFSET_TASK_VM);
STATIC_ASSERT(offsetof(struct task, t_vm_tasks) == OFFSET_TASK_VM_TASKS);
STATIC_ASSERT(offsetof(struct task, t_heapsz) == OFFSET_TASK_HEAPSZ);
STATIC_ASSERT(offsetof(struct task, t_sched.s_state) == OFFSET_TASK_SCHED_STATE);


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


PRIVATE ATTR_USED ATTR_SECTION(".data.pertask.head")
struct task task_header = {
	/* .t_self     = */NULL, /* Filled in by the initializer. */
	/* .t_refcnt   = */1,
	/* .t_flags    = */TASK_FNORMAL,
	/* .t_cpu      = */&_bootcpu,
	/* .t_vm       = */&vm_kernel,
	/* .t_vm_tasks = */LLIST_INITNODE,
	/* .t_heapsz   = */(size_t)__kernel_pertask_size,
	/* .t_sched    = */{
		/* .s_state = */NULL
	},
	/* .t_ctime = */{
		/* .q_jtime = */0,
		/* .q_qtime = */0,
		/* .q_qsize = */1
	},
	/* .t_atime = */{
		/* .q_jtime = */0,
		/* .q_qtime = */0,
		/* .q_qsize = */1
	}
};

INTDEF byte_t __kernel_boottask_stack_page[];
INTDEF byte_t __kernel_bootidle_stack_page[];

PUBLIC ATTR_PERTASK struct vm_datapart
__this_kernel_stack_part ASMNAME("_this_kernel_stack_part") = {
	/* .dp_refcnt = */1,
	/* .dp_lock   = */SHARED_RWLOCK_INIT,
	{/* .dp_tree = */{ NULL, NULL, 0, CEILDIV(KERNEL_STACKSIZE,PAGESIZE) - 1 }},
	/* .dp_crefs = */LLIST_INIT,
	/* .dp_srefs = */(struct vm_node *)&_this_kernel_stack,
	/* .dp_stale = */NULL,
	/* .dp_block = */&vm_datablock_anonymous,
#if CEILDIV(KERNEL_STACKSIZE,PAGESIZE) > (BITS_PER_POINTER / VM_DATAPART_PPP_BITS)
	/* .dp_flags = */VM_DATAPART_FLAG_HEAPPPP,
#else
	/* .dp_flags = */VM_DATAPART_FLAG_NORMAL,
#endif
	/* .dp_state = */VM_DATAPART_STATE_LOCKED,
	{
		/* .dp_ramdata = */{
			/* .rd_blockv = */&__this_kernel_stack_part.dp_ramdata.rd_block0,
			{
					/* .rd_block0 = */{
						/* .rb_start = */0, /* Filled later. */
						/* .rb_size  = */CEILDIV(KERNEL_STACKSIZE,PAGESIZE)
					}
			}
		}
	},
	{
#if CEILDIV(KERNEL_STACKSIZE,PAGESIZE) > (BITS_PER_POINTER / VM_DATAPART_PPP_BITS)
		/* .dp_pprop = */0,
#else
		/* .dp_pprop = */(uintptr_t)-1,
#endif
	},
};
PUBLIC ATTR_PERTASK struct vm_node
__this_kernel_stack ASMNAME("_this_kernel_stack") = {
	/* .vn_node      = */{ NULL, NULL, 0, 0 },
	/* .vn_byaddr    = */LLIST_INITNODE,
	/* .vn_prot      = */VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED,
	/* .vn_flags     = */VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED,
	/* .vn_vm        = */&vm_kernel,
	/* .vn_part      = */&__this_kernel_stack_part,
	/* .vn_block     = */&vm_datablock_anonymous,
	/* .vn_link      = */{ NULL, &LLIST_HEAD(__this_kernel_stack_part.dp_srefs) },
	/* .vn_guard     = */0
};


#ifndef CONFIG_NO_DEBUGGER

#if 0 /* TODO */
/* Re-configure the stack of the current task to point to be descriptive
 * of the debugger stack, instead of the actual kernel-space stack. */
PRIVATE ATTR_COLDBSS struct vm_node dbg_saved_kernel_stack;
PRIVATE ATTR_USED void KCALL
debug_this_kernel_stack_init(void) {
	struct vm_node *my_stack;
	my_stack = (struct vm_node *)THIS_KERNEL_STACK;
	memcpy(&dbg_saved_kernel_stack, my_stack, sizeof(struct vm_node));
	if (dbg_saved_kernel_stack.vn_vm) {
		vm_nodetree_remove(&dbg_saved_kernel_stack.vn_vm->v_tree,
		                   dbg_saved_kernel_stack.vn_node.a_vmin);
		if (dbg_saved_kernel_stack.vn_byaddr.ln_pself)
			LLIST_REMOVE(my_stack, vn_byaddr);
	}
	if (dbg_saved_kernel_stack.vn_part) {
		if (dbg_saved_kernel_stack.vn_link.ln_pself)
			*dbg_saved_kernel_stack.vn_link.ln_pself = &dbg_saved_kernel_stack;
		if (dbg_saved_kernel_stack.vn_link.ln_next)
			dbg_saved_kernel_stack.vn_link.ln_next->vn_link.ln_pself = &dbg_saved_kernel_stack.vn_link.ln_next;
	}
}

INTDEF byte_t __kernel_debug_stack[];
PRIVATE ATTR_USED void KCALL
debug_this_kernel_stack_reset(void) {
	struct vm_node *my_stack;
	my_stack                     = (struct vm_node *)THIS_KERNEL_STACK;
	my_stack->vn_node.a_vmin     = (vm_vpage_t)VM_ADDR2PAGE((uintptr_t)__kernel_debug_stack);
	my_stack->vn_node.a_vmax     = my_stack->vn_node.a_vmin + KERNEL_DEBUG_STACKSIZE / PAGESIZE;
	my_stack->vn_node.a_min      = NULL;
	my_stack->vn_node.a_max      = NULL;
	my_stack->vn_byaddr.ln_pself = NULL;
	my_stack->vn_byaddr.ln_next  = NULL;
	my_stack->vn_prot            = VM_PROT_SHARED | VM_PROT_READ | VM_PROT_WRITE;
	my_stack->vn_flags           = VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_NOMERGE;
	my_stack->vn_vm              = &vm_kernel;
	my_stack->vn_part            = NULL;
	my_stack->vn_block           = NULL;
	my_stack->vn_link.ln_pself   = NULL;
	my_stack->vn_link.ln_next    = NULL;
	my_stack->vn_guard           = 0;
}
PRIVATE ATTR_USED void KCALL
debug_this_kernel_stack_fini(void) {
	struct vm_node *my_stack;
	my_stack = (struct vm_node *)THIS_KERNEL_STACK;
	memcpy(my_stack, &dbg_saved_kernel_stack, sizeof(struct vm_node));
	if (dbg_saved_kernel_stack.vn_part) {
		if (dbg_saved_kernel_stack.vn_link.ln_pself)
			*dbg_saved_kernel_stack.vn_link.ln_pself = my_stack;
		if (dbg_saved_kernel_stack.vn_link.ln_next)
			dbg_saved_kernel_stack.vn_link.ln_next->vn_link.ln_pself = &my_stack->vn_link.ln_next;
	}
	if (dbg_saved_kernel_stack.vn_vm)
		vm_node_insert(my_stack);
}
DEFINE_DBG_INIT(debug_this_kernel_stack_init);
DEFINE_DBG_RESET(debug_this_kernel_stack_reset);
DEFINE_DBG_FINI(debug_this_kernel_stack_fini);
#endif

#endif /* !CONFIG_NO_DEBUGGER */




typedef void (KCALL *pertask_init_t)(struct task *__restrict self);
INTDEF pertask_init_t __kernel_pertask_init_start[];
INTDEF pertask_init_t __kernel_pertask_init_end[];
INTDEF FREE void KCALL kernel_initialize_scheduler_arch(void);

LOCAL ATTR_FREETEXT void
NOTHROW(KCALL initialize_predefined_vm_trampoline)(struct task *__restrict self,
                                                   vm_vpage_t vpage) {
	FORTASK(self, _this_trampoline_node).vn_node.a_vmin = vpage;
	FORTASK(self, _this_trampoline_node).vn_node.a_vmax = vpage;
	/* Load the trampoline node into the kernel VM. */
	assert(FORTASK(self, _this_trampoline_node).vn_vm == &vm_kernel);
	vm_node_insert(&FORTASK(self, _this_trampoline_node));
}

#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
/* Prepare 2 consecutive (and 2-page aligned) pages of virtual
 * memory for the purpose of doing the initial prepare required
 * for `THIS_TRAMPOLINE_PAGE' of `_boottask' and also `_bootidle' */
INTDEF NOBLOCK FREE vm_vpage_t
NOTHROW(FCALL kernel_initialize_boot_trampolines)(void);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */


INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_scheduler)(void) {
	vm_vpage_t boot_trampoline_pages;
	DEFINE_PUBLIC_SYMBOL(_this_task, offsetof(struct task, t_self), sizeof(struct task));
	DEFINE_PUBLIC_SYMBOL(_this_cpu, offsetof(struct task, t_cpu), sizeof(struct cpu *));
	DEFINE_PUBLIC_SYMBOL(_this_vm, offsetof(struct task, t_vm), sizeof(struct vm *));
	DEFINE_INTERN_SYMBOL(_this_sched_state, offsetof(struct task, t_sched.s_state), sizeof(struct scpustate *));
	DEFINE_INTERN_SYMBOL(_this_sched_runprv, offsetof(struct task, t_sched.s_running.sr_runprv), sizeof(struct task *));
	DEFINE_INTERN_SYMBOL(_this_sched_runnxt, offsetof(struct task, t_sched.s_running.sr_runnxt), sizeof(struct task *));
	DEFINE_INTERN_SYMBOL(_this_cpu_id, offsetof(struct cpu, c_id), sizeof(cpuid_t));
	DEFINE_INTERN_SYMBOL(_this_cpu_current, offsetof(struct cpu, c_current), sizeof(struct task *));
	DEFINE_INTERN_SYMBOL(_this_cpu_override, offsetof(struct cpu, c_override), sizeof(struct task *));
	DEFINE_INTERN_SYMBOL(_this_cpu_pending, offsetof(struct cpu, c_pending), sizeof(struct task *));
	assert(_boottask.t_refcnt == 1);
	assert(_bootidle.t_refcnt == 1);

	/* Figure out where to put the initial trampolines for _boottask and _bootidle */
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	boot_trampoline_pages = kernel_initialize_boot_trampolines();
#else /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	boot_trampoline_pages = vm_getfree(&vm_kernel,
	                                   (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_TRAMPOLINE),
	                                   /* num_pages: */ 2,
	                                   /* alignment: */ 1,
	                                   HINT_GETMODE(KERNEL_VMHINT_TRAMPOLINE));
#endif /* !CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Construct the trampoline node for the predefined tasks. */
	initialize_predefined_vm_trampoline(&_boottask, boot_trampoline_pages + 0);
	initialize_predefined_vm_trampoline(&_bootidle, boot_trampoline_pages + 1);

	*(uintptr_t *)&FORTASK(&_boottask, __this_kernel_stack).vn_part += (uintptr_t)&_boottask;
	*(uintptr_t *)&FORTASK(&_boottask, __this_kernel_stack).vn_link.ln_pself += (uintptr_t)&_boottask;
	*(uintptr_t *)&FORTASK(&_boottask, __this_kernel_stack).vn_node.a_vmin = (uintptr_t)__kernel_boottask_stack_page;
	*(uintptr_t *)&FORTASK(&_boottask, __this_kernel_stack).vn_node.a_vmax = (uintptr_t)__kernel_boottask_stack_page + CEILDIV(KERNEL_STACKSIZE, PAGESIZE) - 1;
	*(uintptr_t *)&FORTASK(&_boottask, __this_kernel_stack_part).dp_srefs += (uintptr_t)&_boottask;
	*(uintptr_t *)&FORTASK(&_boottask, __this_kernel_stack_part).dp_ramdata.rd_blockv += (uintptr_t)&_boottask;
	*(uintptr_t *)&FORTASK(&_boottask, __this_kernel_stack_part).dp_ramdata.rd_block0.rb_start = VM_ADDR2PAGE((uintptr_t)__kernel_boottask_stack_page - KERNEL_BASE);

	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack).vn_part += (uintptr_t)&_bootidle;
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack).vn_link.ln_pself += (uintptr_t)&_bootidle;
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack_part).dp_srefs += (uintptr_t)&_bootidle;
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack).vn_node.a_vmin = (uintptr_t)__kernel_bootidle_stack_page;
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack).vn_node.a_vmax = (uintptr_t)__kernel_bootidle_stack_page + CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE) - 1;
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack_part).dp_ramdata.rd_blockv += (uintptr_t)&_bootidle;
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack_part).dp_ramdata.rd_block0.rb_start = VM_ADDR2PAGE((uintptr_t)__kernel_bootidle_stack_page - KERNEL_BASE);
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack_part).dp_tree.a_vmax                = CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE) - 1;
	*(uintptr_t *)&FORTASK(&_bootidle, __this_kernel_stack_part).dp_ramdata.rd_block0.rb_size  = CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE);

	FORTASK(&_boottask, _this_fs)             = &fs_kernel;
	FORTASK(&_bootidle, _this_fs)             = &fs_kernel;
	FORTASK(&_boottask, _this_handle_manager) = &handle_manager_kernel;
	FORTASK(&_bootidle, _this_handle_manager) = &handle_manager_kernel;

	/* The stack of IDLE threads is executable in order to allow for hacking around .free restrictions. */
	FORTASK(&_bootidle, __this_kernel_stack).vn_prot = (VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ);

	vm_kernel.v_tasks             = &_boottask;
	_boottask.t_vm_tasks.ln_pself = &vm_kernel.v_tasks;
	_boottask.t_vm_tasks.ln_next  = &_bootidle;
	_bootidle.t_vm_tasks.ln_pself = &_boottask.t_vm_tasks.ln_next;
	_boottask.t_refcnt            = 2; /* +1: scheduler chain, +1: public symbol `_boottask' */
	_bootidle.t_refcnt            = 2; /* +1: scheduler chain, +1: public symbol `_bootidle' */

	_boottask.t_flags                     = TASK_FSTARTED | TASK_FRUNNING;
	_bootidle.t_flags                     = TASK_FSTARTED | TASK_FKEEPCORE;
	_boottask.t_sched.s_running.sr_runnxt = &_boottask;
	_boottask.t_sched.s_running.sr_runprv = &_boottask;
	_boottask.t_self                      = &_boottask;
	_bootidle.t_self                      = &_bootidle;
	_bootcpu.c_current                    = &_boottask;

	kernel_initialize_scheduler_arch();
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_scheduler_callbacks)(void) {
	/* Execute initializers for the boot & idle thread. */
	pertask_init_t *iter;
	iter = __kernel_pertask_init_start;
	for (; iter < __kernel_pertask_init_end; ++iter) {
		(**iter)(&_boottask);
		(**iter)(&_bootidle);
	}
}











DATDEF ATTR_PERTASK struct vm_datapart __this_kernel_stack_part ASMNAME("_this_kernel_stack_part");
DATDEF ATTR_PERTASK struct vm_node __this_kernel_stack ASMNAME("_this_kernel_stack");

INTERN NOBLOCK void
NOTHROW(KCALL task_destroy_raw_impl)(struct task *__restrict self) {
	struct vm_node *node;
	assertf(self != &_boottask &&
	        self != &_bootidle,
	        "Cannot destroy the BOOT or IDLE task of CPU0\n"
	        "self       = %p\n"
	        "&_boottask = %p\n"
	        "&_bootidle = %p\n",
	        self, &_boottask, &_bootidle);
	assert(sync_writing(&vm_kernel.v_treelock));

	/* Unlink + unmap the trampoline node. */
	node = vm_node_remove(&vm_kernel, FORTASK(self, _this_trampoline_node).vn_node.a_vmin);
	assertf(node == &FORTASK(self, _this_trampoline_node),
	        "node                                 = %p\n"
	        "&FORTASK(self,_this_trampoline_node) = %p\n"
	        "self                                 = %p\n",
	        node, &FORTASK(self, _this_trampoline_node), self);
	pagedir_unmapone(node->vn_node.a_vmin);
	pagedir_syncone(node->vn_node.a_vmin);
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_mapone(node->vn_node.a_vmin);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Unlink + unmap the stack node. */
	node = vm_node_remove(&vm_kernel, FORTASK(self, __this_kernel_stack).vn_node.a_vmin);
	assertf(node == &FORTASK(self, __this_kernel_stack),
	        "node                               = %p\n"
	        "&FORTASK(self,__this_kernel_stack) = %p\n"
	        "self                               = %p\n",
	        node, &FORTASK(self, __this_kernel_stack), self);
	pagedir_unmap(VM_NODE_START(node), VM_NODE_SIZE(node));
	pagedir_sync(VM_NODE_START(node), VM_NODE_SIZE(node));
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_map(VM_NODE_START(node), VM_NODE_SIZE(node));
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Deallocate the kernel stack. */
	vm_datapart_do_freeram(&FORTASK(self, __this_kernel_stack_part));

	{
		REF struct vm *myvm = self->t_vm;
		COMPILER_READ_BARRIER();
		if (self->t_vm_tasks.ln_pself) {
			struct task *next;
			if (vm_tasklock_trywrite(myvm)) {
				LLIST_REMOVE(self, t_vm_tasks);
				vm_tasklock_endwrite(myvm);
				goto do_free_self;
			}
			/* Truncate the task structure so that it will only still
			 * contain the per-vm task chain, as well as the next link. */
			self->t_heapsz = heap_truncate(&kernel_locked_heap,
			                               self,
			                               self->t_heapsz,
			                               MAX(MAX(COMPILER_OFFSETAFTER(struct task, t_vm_tasks),
			                                       COMPILER_OFFSETAFTER(struct task, t_sched)),
			                                   COMPILER_OFFSETAFTER(struct task, t_heapsz)),
			                               GFP_NORMAL);
			/* Schedule our task for pending removal within its associated VM.
			 * The next time someone acquires a lock to the VM's task-chain,
			 * we will be removed automatically, and finally freed. */
			cpu_assert_integrity();
			do {
				next = ATOMIC_READ(myvm->v_deltasks);
				self->t_sched.s_running.sr_runnxt = next;
			} while (!ATOMIC_CMPXCH_WEAK(myvm->v_deltasks, next, self));
			cpu_assert_integrity();
			vm_tasklock_tryservice(myvm);
		} else {
do_free_self:
			heap_free(&kernel_locked_heap, self, self->t_heapsz, GFP_NORMAL);
		}
		decref(myvm);
	}
}


/* Chain of tasks that are pending destruction.
 * Linked via `t_sched.s_running.sr_runnxt' */
INTERN ATTR_READMOSTLY WEAK struct task *vm_pending_destroy_tasks = NULL;

typedef void (KCALL *pertask_fini_t)(struct task *__restrict self);
INTDEF pertask_fini_t __kernel_pertask_fini_start[];
INTDEF pertask_fini_t __kernel_pertask_fini_end[];

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_destroy)(struct task *__restrict self) {
	pertask_fini_t *iter;
	/* Run task finalizers. */
	iter = __kernel_pertask_fini_start;
	for (; iter < __kernel_pertask_fini_end; ++iter)
		(**iter)(self);
	if (vm_kernel_treelock_trywrite()) {
		task_destroy_raw_impl(self);
		vm_kernel_treelock_endwrite();
	} else {
		struct task *next;
		/* Schedule the task to-be destroyed later. */
		cpu_assert_integrity();
		do {
			next = ATOMIC_READ(vm_pending_destroy_tasks);
			self->t_sched.s_running.sr_runnxt = next;
		} while (!ATOMIC_CMPXCH_WEAK(vm_pending_destroy_tasks, next, self));
		cpu_assert_integrity();
		vm_kernel_treelock_tryservice();
	}
}

PUBLIC WUNUSED ATTR_MALLOC ATTR_RETNONNULL REF struct task *
(KCALL task_alloc)(struct vm *__restrict task_vm) THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct task *result;
	struct heapptr resptr;
	/* Allocate a new task structure. */
	resptr = heap_alloc(&kernel_locked_heap,
	                    (size_t)__kernel_pertask_size,
	                    GFP_LOCKED | GFP_PREFLT);
	result = (REF struct task *)resptr.hp_ptr;
	/* Copy the per-task initialization template. */
	memcpy(result, __kernel_pertask_start, (size_t)__kernel_pertask_size);
	result->t_heapsz = resptr.hp_siz;
	result->t_self   = result;
	incref(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack).vn_block */
	incref(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack_part).dp_block */
	*(uintptr_t *)&FORTASK(result, __this_kernel_stack).vn_part += (uintptr_t)result;
	*(uintptr_t *)&FORTASK(result, __this_kernel_stack).vn_link.ln_pself += (uintptr_t)result;
	*(uintptr_t *)&FORTASK(result, __this_kernel_stack_part).dp_srefs += (uintptr_t)result;
	TRY {
		vm_datapart_do_allocram(&FORTASK(result, __this_kernel_stack_part));
		TRY {
			vm_vpage_t stack_page;
			vm_vpage_t trampoline_page;
			uintptr_t version = 0;
again_lock_vm:
			vm_kernel_treelock_write();
			stack_page = vm_getfree(&vm_kernel,
			                        (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_KERNSTACK),
			                        CEILDIV(KERNEL_STACKSIZE, PAGESIZE), 1,
			                        HINT_GETMODE(KERNEL_VMHINT_KERNSTACK));
			if unlikely(stack_page == VM_GETFREE_ERROR) {
				vm_kernel_treelock_endwrite();
				if (system_clearcaches_s(&version))
					goto again_lock_vm;
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
				      (uintptr_t)CEILDIV(KERNEL_STACKSIZE, PAGESIZE));
			}
			FORTASK(result, __this_kernel_stack).vn_node.a_vmin = stack_page;
			FORTASK(result, __this_kernel_stack).vn_node.a_vmax = stack_page + CEILDIV(KERNEL_STACKSIZE, PAGESIZE) - 1;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepare_map(stack_page, CEILDIV(KERNEL_STACKSIZE, PAGESIZE))) {
				vm_kernel_treelock_endwrite();
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, (uintptr_t)1);
			}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_node_insert(&FORTASK(result, __this_kernel_stack));

			/* Map the trampoline node. */
			trampoline_page = vm_getfree(&vm_kernel,
			                             (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_TRAMPOLINE), 1, 1,
			                             HINT_GETMODE(KERNEL_VMHINT_TRAMPOLINE));
			if unlikely(trampoline_page == VM_GETFREE_ERROR) {
				vm_node_remove(&vm_kernel, stack_page);
				vm_kernel_treelock_endwrite();
				if (system_clearcaches_s(&version))
					goto again_lock_vm;
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, (uintptr_t)1);
			}
			FORTASK(result, _this_trampoline_node).vn_node.a_vmin = trampoline_page;
			FORTASK(result, _this_trampoline_node).vn_node.a_vmax = trampoline_page;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepare_mapone(trampoline_page))
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, (uintptr_t)1);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			/* Load the trampoline node into the kernel VM. */
			vm_node_insert(&FORTASK(result, _this_trampoline_node));

			/* Map the stack into memory */
			vm_datapart_map_ram(&FORTASK(result, __this_kernel_stack_part), stack_page,
			                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			vm_kernel_treelock_endwrite();
		} EXCEPT {
			vm_datapart_do_ccfreeram(&FORTASK(result, __this_kernel_stack_part));
			RETHROW();
		}
	} EXCEPT {
		decref_nokill(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack_part).dp_block */
		decref_nokill(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack).vn_block */
		heap_free(&kernel_locked_heap,
		          resptr.hp_ptr,
		          resptr.hp_siz,
		          GFP_NORMAL);
		RETHROW();
	}

	result->t_vm = task_vm;
	incref(task_vm);

	/* Run custom initializers. */
	TRY {
		pertask_init_t *iter;
		assert(!result->t_vm_tasks.ln_pself);

		/* Insert the new task into the VM */
		vm_tasklock_write(task_vm);
		LLIST_INSERT(task_vm->v_tasks, result, t_vm_tasks);
		vm_tasklock_endwrite(task_vm);

		iter = __kernel_pertask_init_start;
		for (; iter < __kernel_pertask_init_end; ++iter)
			(**iter)(result);
	} EXCEPT {
		ATOMIC_WRITE(result->t_refcnt, 0);
		/* Destroy the task if an initializer threw another exception. */
		task_destroy(result);
		RETHROW();
	}
	return result;
}


#if 0
typedef void (KCALL *pertask_clone_t)(struct task *__restrict new_thread, uintptr_t flags);
INTDEF pertask_clone_t __kernel_pertask_clone_start[];
INTDEF pertask_clone_t __kernel_pertask_clone_end[];


/* High-level kernel interface for the clone(2) system call.
 * @param: clone_flags: Set of `TASK_CLONE_*' */
PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1, 2)) REF struct task *
(KCALL task_clone)(uintptr_t clone_flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct task *result;
	if (clone_flags & TASK_CLONE_VM) {
		result = task_alloc(THIS_VM);
	} else {
		REF struct vm *result_vm;
		result_vm = vm_clone(THIS_VM, false);
		FINALLY_DECREF_UNLIKELY(result_vm);
		result = task_alloc(result_vm);
	}
	TRY {
		/* Invoke additional callbacks. */
		{
			pertask_clone_t *iter;
			for (iter = __kernel_pertask_clone_start;
			     iter < __kernel_pertask_clone_end; ++iter)
				(**iter)(result, clone_flags);
		}
	} EXCEPT {
		decref_likely(result);
		RETHROW();
	}
	return result;
}
#endif



DEFINE_SYSCALL1(void, exit, syscall_ulong_t, exit_code) {
	THROW(E_EXIT_THREAD, W_EXITCODE(exit_code & 0xff, 0));
}
DEFINE_SYSCALL1(void, exit_group, syscall_ulong_t, exit_code) {
	THROW(E_EXIT_PROCESS, W_EXITCODE(exit_code & 0xff, 0));
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_C */
