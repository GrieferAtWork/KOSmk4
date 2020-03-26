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
#ifndef GUARD_KERNEL_SRC_SCHED_USERKERN_C
#define GUARD_KERNEL_SRC_SCHED_USERKERN_C 1

#include <kernel/compiler.h>

#include <sched/userkern.h>
#ifndef CONFIG_NO_USERKERN_SEGMENT

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/vm.h>
#include <sched/cred.h>
#include <sched/pertask.h>
#include <sched/pid.h>

#include <compat/config.h>
#include <kos/bits/ukern-struct.h>
#include <kos/except/inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/ukern.h>

#include <libvio/vio.h>

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
PRIVATE NONNULL((1)) u32 KCALL userkern_segment_readl(struct vio_args *__restrict args, vio_addr_t addr);
PRIVATE NONNULL((1)) void KCALL userkern_segment_writel(struct vio_args *__restrict args, vio_addr_t addr, u32 value);
#endif /* __SIZEOF_POINTER__ == 4 || __ARCH_HAVE_COMPAT */
#if __SIZEOF_POINTER__ == 8 || defined(__ARCH_HAVE_COMPAT)
PRIVATE NONNULL((1)) u64 KCALL userkern_segment_readq(struct vio_args *__restrict args, vio_addr_t addr);
PRIVATE NONNULL((1)) void KCALL userkern_segment_writeq(struct vio_args *__restrict args, vio_addr_t addr, u64 value);
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


PRIVATE void KCALL
userkern_segment_call(struct vio_args *__restrict args,
                      vio_addr_t addr) {
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
	args->va_state = syscall_emulate_callback(args->va_state,
	                                          USERKERN_SYSCALL_DECODE(reladdr),
	                                          (reladdr & USERKERN_SYSCALL_EXCEPTBIT) != 0);
	return;
err_invalid_addr:
	THROW(E_SEGFAULT_UNMAPPED,
	      vio_args_faultaddr(args, addr),
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_EXEC |
	      E_SEGFAULT_CONTEXT_USERCODE);
}



#if __SIZEOF_POINTER__ >= 8
#ifndef LIBVIO_CONFIG_HAVE_QWORD
#error "Invalid configuration"
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, NULL, &userkern_segment_##name##q }
#elif defined(LIBVIO_CONFIG_HAVE_QWORD)
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l, NULL }
#else
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l }
#endif
#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL, NULL }
#else /* LIBVIO_CONFIG_HAVE_QWORD */
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL }
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */

/* VIO bindings for the kernel-reserve segment of user-space VMs */
PUBLIC struct vio_operators userkern_segment_vio =
VIO_OPERATORS_INIT_EX(INIT_OPERATION_PTR(read),
                      INIT_OPERATION_PTR(write),
                      VIO_CALLBACK_INIT_CMPXCH(NULL, NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_XCH(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_ADD(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_SUB(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_AND(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_OR(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_XOR(NULL, NULL, NULL, NULL),
                      &userkern_segment_call);
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
#ifndef LIBVIO_CONFIG_HAVE_QWORD
#error "Invalid configuration"
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, NULL, &userkern_segment_##name##q }
#elif defined(LIBVIO_CONFIG_HAVE_QWORD)
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l, NULL }
#else
#define INIT_OPERATION_PTR(name) \
	{ NULL, NULL, &userkern_segment_##name##l }
#endif
#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL, NULL }
#else /* LIBVIO_CONFIG_HAVE_QWORD */
#define INIT_OPERATION_PTR_NULL { NULL, NULL, NULL }
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */

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



PRIVATE void KCALL
userkern_segment_call_compat(struct vio_args *__restrict args,
                             vio_addr_t addr) {
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
	args->va_state = syscall_emulate_callback_compat(args->va_state,
	                                                 USERKERN_SYSCALL_DECODE(reladdr),
	                                                 (reladdr & USERKERN_SYSCALL_EXCEPTBIT) != 0);
	return;
err_invalid_addr:
	THROW(E_SEGFAULT_UNMAPPED,
	      vio_args_faultaddr(args, addr),
	      E_SEGFAULT_CONTEXT_FAULT |
	      E_SEGFAULT_CONTEXT_USERCODE);
}

PUBLIC struct vio_operators userkern_segment_vio_compat =
VIO_OPERATORS_INIT_EX(INIT_OPERATION_PTR(read),
                      INIT_OPERATION_PTR(write),
                      VIO_CALLBACK_INIT_CMPXCH(NULL, NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_XCH(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_ADD(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_SUB(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_AND(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_OR(NULL, NULL, NULL, NULL),
                      VIO_CALLBACK_INIT_XOR(NULL, NULL, NULL, NULL),
                      &userkern_segment_call_compat);
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
