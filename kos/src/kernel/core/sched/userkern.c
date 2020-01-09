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

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <sched/cred.h>
#include <sched/pertask.h>
#include <sched/pid.h>

#include <compat/config.h>
#include <kos/bits/ukern-struct.h>
#include <kos/except-inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/ukern.h>

#ifdef __ARCH_HAVE_COMPAT
#include <hybrid/byteorder.h>

#include <kos/bits/ukern-struct32.h>
#include <kos/bits/ukern-struct64.h>
#endif /* __ARCH_HAVE_COMPAT */


DECL_BEGIN

/* These 2 functions must be overwritten to implement arch-specific behavior.
 * Mainly: To implement access to the register identity map structure. */
INTDEF NONNULL((1)) bool KCALL userkern_get_arch_specific_field(struct vio_args *__restrict args, uintptr_t offset, uintptr_t *__restrict presult);
INTDEF NONNULL((1)) bool KCALL userkern_set_arch_specific_field(struct vio_args *__restrict args, uintptr_t offset, uintptr_t value);
#ifdef __ARCH_HAVE_COMPAT
INTDEF NONNULL((1)) bool KCALL userkern_get_arch_specific_field_compat(struct vio_args *__restrict args, uintptr_t offset, __ARCH_COMPAT_UINTPTR_TYPE *__restrict presult);
INTDEF NONNULL((1)) bool KCALL userkern_set_arch_specific_field_compat(struct vio_args *__restrict args, uintptr_t offset, __ARCH_COMPAT_UINTPTR_TYPE value);
#endif /* __ARCH_HAVE_COMPAT */

#ifdef __INTELLISENSE__
#if __SIZEOF_POINTER__ == 4 || defined(__ARCH_HAVE_COMPAT)
PRIVATE NONNULL((1)) u32 KCALL userkern_segment_readl(struct vio_args *__restrict args, pos_t addr);
PRIVATE NONNULL((1)) void KCALL userkern_segment_writel(struct vio_args *__restrict args, pos_t addr, u32 value);
#endif /* __SIZEOF_POINTER__ == 4 || __ARCH_HAVE_COMPAT */
#if __SIZEOF_POINTER__ == 8 || defined(__ARCH_HAVE_COMPAT)
PRIVATE NONNULL((1)) u64 KCALL userkern_segment_readq(struct vio_args *__restrict args, pos_t addr);
PRIVATE NONNULL((1)) void KCALL userkern_segment_writeq(struct vio_args *__restrict args, pos_t addr, u64 value);
#endif /* __SIZEOF_POINTER__ == 8 || __ARCH_HAVE_COMPAT */
#else /* __INTELLISENSE__ */
DECL_END

#if __SIZEOF_POINTER__ == 4 || defined(__ARCH_HAVE_COMPAT)
#ifdef __ARCH_HAVE_COMPAT
#define USERKERN_STRUCT struct userkern32
#endif /* __ARCH_HAVE_COMPAT */
#define DEFINE_IO_READ 1
#define USERKERN_WIDTH 4
#include "userkern-rw.c.inl"
#ifdef __ARCH_HAVE_COMPAT
#define USERKERN_STRUCT struct userkern32
#endif /* __ARCH_HAVE_COMPAT */
#define DEFINE_IO_WRITE 1
#define USERKERN_WIDTH 4
#include "userkern-rw.c.inl"
#endif /* __SIZEOF_POINTER__ == 4 || __ARCH_HAVE_COMPAT */

#if __SIZEOF_POINTER__ == 8 || defined(__ARCH_HAVE_COMPAT)
#ifdef __ARCH_HAVE_COMPAT
#define USERKERN_STRUCT struct userkern64
#endif /* __ARCH_HAVE_COMPAT */
#define DEFINE_IO_READ 1
#define USERKERN_WIDTH 8
#include "userkern-rw.c.inl"
#ifdef __ARCH_HAVE_COMPAT
#define USERKERN_STRUCT struct userkern64
#endif /* __ARCH_HAVE_COMPAT */
#define DEFINE_IO_WRITE 1
#define USERKERN_WIDTH 8
#include "userkern-rw.c.inl"
#endif /* __SIZEOF_POINTER__ == 8 || __ARCH_HAVE_COMPAT */

DECL_BEGIN
#endif /* !__INTELLISENSE__ */


PRIVATE struct icpustate *KCALL
userkern_segment_call(struct vio_args *__restrict args,
                      struct icpustate *__restrict regs,
                      pos_t addr) {
	uintptr_t reladdr;
	uintptr_t base = get_userkern_base();
	if (!ADDR_ISKERN(base))
		goto err_invalid_addr;
#ifdef KERNELSPACE_HIGHMEM
	base -= KERNELSPACE_BASE;
#endif /* KERNELSPACE_HIGHMEM */
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
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)PAGEID_DECODE(args->va_access_pageid);
	THROW(E_SEGFAULT_UNMAPPED,
	      (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_USERCODE);
}



#if __SIZEOF_POINTER__ >= 8
#ifndef CONFIG_VIO_HAS_QWORD
#error "Invalid configuration"
#endif /* !CONFIG_VIO_HAS_QWORD */
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, NULL, &userkern_segment_##name##q }
#elif defined(CONFIG_VIO_HAS_QWORD)
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l, NULL }
#else
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l }
#endif
#ifdef CONFIG_VIO_HAS_QWORD
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL, NULL }
#else /* CONFIG_VIO_HAS_QWORD */
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL }
#endif /* !CONFIG_VIO_HAS_QWORD */

/* VIO bindings for the kernel-reserve segment of user-space VMs */
PUBLIC struct vm_datablock_type_vio userkern_segment_vio = {
	/* .dtv_read   = */ INIT_OPERATION_PTR(read),
	/* .dtv_write  = */ INIT_OPERATION_PTR(write),
	/* .dtv_cmpxch = */ VM_DATABLOCK_TYPE_VIO_INIT_CMPXCH(NULL, NULL, NULL, NULL, NULL),
	/* .dtv_xch    = */ VM_DATABLOCK_TYPE_VIO_INIT_XCH(NULL, NULL, NULL, NULL),
	/* .dtv_add    = */ VM_DATABLOCK_TYPE_VIO_INIT_ADD(NULL, NULL, NULL, NULL),
	/* .dtv_sub    = */ VM_DATABLOCK_TYPE_VIO_INIT_SUB(NULL, NULL, NULL, NULL),
	/* .dtv_and    = */ VM_DATABLOCK_TYPE_VIO_INIT_AND(NULL, NULL, NULL, NULL),
	/* .dtv_or     = */ VM_DATABLOCK_TYPE_VIO_INIT_OR(NULL, NULL, NULL, NULL),
	/* .dtv_xor    = */ VM_DATABLOCK_TYPE_VIO_INIT_XOR(NULL, NULL, NULL, NULL),
	/* .dtv_call   = */ &userkern_segment_call
};
#undef INIT_OPERATION_PTR_NULL
#undef INIT_OPERATION_PTR

PUBLIC struct vm_datapart userkern_segment_part = {
	/* .dp_refcnt = */ 1,
	/* .dp_lock   = */ SHARED_RWLOCK_INIT,
	{
		/* .dp_tree_ptr = */ {
			/* .a_min = */ NULL,
			/* .a_max = */ NULL,
			{
				/* .a_vmin_ptr = */ 0
			},
			{
				/* .a_vmax_ptr = */ (KERNELSPACE_MAXPAGEID - KERNELSPACE_MINPAGEID)
			},
		}
	},
	/* .dp_crefs  = */ LLIST_INIT,
	/* .dp_srefs  = */ LLIST_INIT,
	/* .dp_stale  = */ NULL,
	/* .dp_block  = */ &userkern_segment_block,
	/* .dp_flags  = */ (VM_DATAPART_FLAG_LOCKED | VM_DATAPART_FLAG_CHANGED |
	                    VM_DATAPART_FLAG_KEEPRAM | VM_DATAPART_FLAG_HEAPPPP |
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




#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER >= 8
#ifndef CONFIG_VIO_HAS_QWORD
#error "Invalid configuration"
#endif /* !CONFIG_VIO_HAS_QWORD */
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, NULL, &userkern_segment_##name##q }
#elif defined(CONFIG_VIO_HAS_QWORD)
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l, NULL }
#else
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l }
#endif
#ifdef CONFIG_VIO_HAS_QWORD
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL, NULL }
#else /* CONFIG_VIO_HAS_QWORD */
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL }
#endif /* !CONFIG_VIO_HAS_QWORD */

#ifdef KERNELSPACE_HIGHMEM
#define COMPAT_ADDR_ISKERN(addr) (__CCAST(__UINTPTR_TYPE__)(addr) >= COMPAT_KERNELSPACE_BASE)
#define COMPAT_KERNELSPACE_MINPAGEID PAGEID_ENCODE(COMPAT_KERNELSPACE_BASE)
#define COMPAT_KERNELSPACE_MAXPAGEID __ARCH_PAGEID_MAX
#elif defined(KERNELSPACE_LOWMEM)
#define COMPAT_ADDR_ISKERN(addr) (__CCAST(__UINTPTR_TYPE__)(addr) < COMPAT_KERNELSPACE_END)
#define COMPAT_KERNELSPACE_MINPAGEID 0
#define COMPAT_KERNELSPACE_MAXPAGEID (PAGEID_ENCODE(COMPAT_KERNELSPACE_END) - 1)
#else
#define COMPAT_ADDR_ISKERN(addr) (__CCAST(__UINTPTR_TYPE__)(addr) >= COMPAT_KERNELSPACE_BASE && __CCAST(__UINTPTR_TYPE__)(addr) < COMPAT_KERNELSPACE_END)
#define COMPAT_KERNELSPACE_MINPAGEID PAGEID_ENCODE(COMPAT_KERNELSPACE_BASE)
#define COMPAT_KERNELSPACE_MAXPAGEID (PAGEID_ENCODE(COMPAT_KERNELSPACE_END) - 1)
#endif



PRIVATE struct icpustate *KCALL
userkern_segment_call_compat(struct vio_args *__restrict args,
                             struct icpustate *__restrict regs,
                             pos_t addr) {
	uintptr_t reladdr;
	uintptr_t base = get_compat_userkern_base();
	if (!COMPAT_ADDR_ISKERN(base))
		goto err_invalid_addr;
#ifdef KERNELSPACE_HIGHMEM
	base -= COMPAT_KERNELSPACE_BASE;
#endif /* KERNELSPACE_HIGHMEM */
	if ((uintptr_t)addr < base)
		goto err_invalid_addr;
	reladdr = (uintptr_t)addr - base;
	if (!USERKERN_SYSCALL_ISVALID(reladdr))
		goto err_invalid_addr;
	/* System call invocation. */
	regs = syscall_emulate_callback_compat(regs,
	                                       USERKERN_SYSCALL_DECODE(reladdr),
	                                       (reladdr & USERKERN_SYSCALL_EXCEPTBIT) != 0);
	return regs;
err_invalid_addr:
	addr -= (pos_t)args->va_access_partoff;
	addr += (pos_t)PAGEID_DECODE(args->va_access_pageid);
	THROW(E_SEGFAULT_UNMAPPED,
	      (uintptr_t)addr,
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_USERCODE);
}

PUBLIC struct vm_datablock_type_vio userkern_segment_vio_compat = {
	/* .dtv_read   = */ INIT_OPERATION_PTR(read),
	/* .dtv_write  = */ INIT_OPERATION_PTR(write),
	/* .dtv_cmpxch = */ VM_DATABLOCK_TYPE_VIO_INIT_CMPXCH(NULL, NULL, NULL, NULL, NULL),
	/* .dtv_xch    = */ VM_DATABLOCK_TYPE_VIO_INIT_XCH(NULL, NULL, NULL, NULL),
	/* .dtv_add    = */ VM_DATABLOCK_TYPE_VIO_INIT_ADD(NULL, NULL, NULL, NULL),
	/* .dtv_sub    = */ VM_DATABLOCK_TYPE_VIO_INIT_SUB(NULL, NULL, NULL, NULL),
	/* .dtv_and    = */ VM_DATABLOCK_TYPE_VIO_INIT_AND(NULL, NULL, NULL, NULL),
	/* .dtv_or     = */ VM_DATABLOCK_TYPE_VIO_INIT_OR(NULL, NULL, NULL, NULL),
	/* .dtv_xor    = */ VM_DATABLOCK_TYPE_VIO_INIT_XOR(NULL, NULL, NULL, NULL),
	/* .dtv_call   = */ &userkern_segment_call_compat
};
#undef INIT_OPERATION_PTR_NULL
#undef INIT_OPERATION_PTR

PUBLIC struct vm_datapart userkern_segment_part_compat = {
	/* .dp_refcnt = */ 1,
	/* .dp_lock   = */ SHARED_RWLOCK_INIT,
	{
		/* .dp_tree_ptr = */ {
			/* .a_min = */ NULL,
			/* .a_max = */ NULL,
			{
				/* .a_vmin_ptr = */ 0
			},
			{
				/* .a_vmax_ptr = */ (COMPAT_KERNELSPACE_MAXPAGEID - COMPAT_KERNELSPACE_MINPAGEID)
			},
		}
	},
	/* .dp_crefs  = */ LLIST_INIT,
	/* .dp_srefs  = */ LLIST_INIT,
	/* .dp_stale  = */ NULL,
	/* .dp_block  = */ &userkern_segment_block_compat,
	/* .dp_flags  = */ (VM_DATAPART_FLAG_LOCKED | VM_DATAPART_FLAG_CHANGED |
	                    VM_DATAPART_FLAG_KEEPRAM | VM_DATAPART_FLAG_HEAPPPP |
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

PUBLIC struct vm_datablock userkern_segment_block_compat = {
	/* .db_refcnt = */ 2, /* +1: `userkern_segment_block', +1: `userkern_segment_part.dp_block' */
	/* .db_lock   = */ RWLOCK_INIT,
	/* .db_type   = */ &vm_datablock_anonymous_type,
	/* .db_vio    = */ &userkern_segment_vio_compat,
	/* .db_parts  = */ &userkern_segment_part_compat,
	VM_DATABLOCK_INIT_PAGEINFO(0)
};
#endif /* __ARCH_HAVE_COMPAT */


DECL_END

#endif /* !CONFIG_NO_USERKERN_SEGMENT */


#endif /* !GUARD_KERNEL_SRC_SCHED_USERKERN_C */
