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

#include <kernel/compat.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <sched/cred.h>
#include <sched/pertask.h>
#include <sched/pid.h>

#include <kos/bits/ukern-struct.h>
#include <kos/except-inval.h>
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
PRIVATE NONNULL((1)) u32 KCALL userkern_segment_readl(struct vio_args *__restrict args, vm_daddr_t addr);
PRIVATE NONNULL((1)) void KCALL userkern_segment_writel(struct vio_args *__restrict args, vm_daddr_t addr, u32 value);
#endif /* __SIZEOF_POINTER__ == 4 || __ARCH_HAVE_COMPAT */
#if __SIZEOF_POINTER__ == 8 || defined(__ARCH_HAVE_COMPAT)
PRIVATE NONNULL((1)) u64 KCALL userkern_segment_readq(struct vio_args *__restrict args, vm_daddr_t addr);
PRIVATE NONNULL((1)) void KCALL userkern_segment_writeq(struct vio_args *__restrict args, vm_daddr_t addr, u64 value);
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


#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define IS32(x) (icpustate_iscompat(x))
#else /* __ARCH_COMPAT_SIZEOF_POINTER == 4 */
#define IS32(x) (!icpustate_iscompat(x))
#endif /* !__ARCH_COMPAT_SIZEOF_POINTER != 4 */


PRIVATE NONNULL((1)) u32 KCALL
userkern_segment_readl_real(struct vio_args *__restrict args, vm_daddr_t addr) {
	if (IS32(args->va_state)) {
		/* 32-bit */
		return userkern_segment_readl(args, addr);
	} else {
		/* 64-bit */
		return (u32)userkern_segment_readq(args, addr);
	}
}
PRIVATE NONNULL((1)) u64 KCALL
userkern_segment_readq_real(struct vio_args *__restrict args, vm_daddr_t addr) {
	if (IS32(args->va_state)) {
		/* 32-bit */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return (u64)userkern_segment_readl(args, addr) |
		       (u64)userkern_segment_readl(args, addr + 4) << 32;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		return (u64)userkern_segment_readl(args, addr) << 32 |
		       (u64)userkern_segment_readl(args, addr + 4);
#else
#error "Unsupported endian"
#endif
	} else {
		/* 64-bit */
		return userkern_segment_readq(args, addr);
	}
}

PRIVATE NONNULL((1)) void KCALL
userkern_segment_writel_real(struct vio_args *__restrict args,
                             vm_daddr_t addr, u32 value) {
	if (IS32(args->va_state)) {
		/* 32-bit */
		userkern_segment_writel(args, addr, value);
	} else {
		/* 64-bit */
		userkern_segment_writeq(args, addr, value);
	}
}

PRIVATE NONNULL((1)) void KCALL
userkern_segment_writeq_real(struct vio_args *__restrict args,
                             vm_daddr_t addr, u64 value) {
	if (IS32(args->va_state)) {
		/* 32-bit */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		userkern_segment_writel(args, addr, (u32)value);
		userkern_segment_writel(args, addr + 4, (u32)(value >> 32));
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		userkern_segment_writel(args, addr, (u32)(value >> 32));
		userkern_segment_writel(args, addr + 4, (u32)value);
#else
#error "Unsupported endian"
#endif
	} else {
		/* 64-bit */
		userkern_segment_writeq(args, addr, value);
	}
}

#endif /* __ARCH_HAVE_COMPAT */


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



#ifdef __ARCH_HAVE_COMPAT
#ifndef CONFIG_VIO_HAS_QWORD
#error "Invalid configuration"
#endif /* !CONFIG_VIO_HAS_QWORD */
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l_real, &userkern_segment_##name##q_real }
#elif __SIZEOF_POINTER__ >= 8
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
				/* .a_vmax_ptr = */ KERNEL_NUM_PAGES - 1
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


DECL_END

#endif /* !CONFIG_NO_USERKERN_SEGMENT */


#endif /* !GUARD_KERNEL_SRC_SCHED_USERKERN_C */
