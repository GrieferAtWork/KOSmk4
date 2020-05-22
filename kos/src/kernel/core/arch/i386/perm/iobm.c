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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IOBM_C
#define GUARD_KERNEL_CORE_ARCH_I386_IOBM_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <misc/atomic-ref.h>
#include <sched/cpu.h>
#include <sched/pertask.h>
#include <sched/task.h>
#include <sched/x86/iobm.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

/* [0..1][lock(WRITE_ONCE)]
 * The I/O permissions bitmap of the calling thread.
 * Lazily allocated during `ioperm()' and `#PF' (s.a. documentation in <sched/tss.h>) */
PUBLIC ATTR_PERTASK REF struct ioperm_bitmap *this_x86_ioperm_bitmap = NULL;

/* [0..1][lock(THIS_CPU && !PREEMPTION_ENABLED())]
 * The I/O permissions bitmap currently active within the calling CPU.
 * Set to `NULL' during preemption; Filled in during the first #PF that ended
 * up being caused by the CPU trying to access the I/O permissions bitmap. */
PUBLIC ATTR_PERCPU struct ioperm_bitmap *thiscpu_x86_ioperm_bitmap = NULL;

/* Check if `self' is currently mapped with write permissions within the calling CPU.
 * If this is the case, get rid of those write permissions, but keep the ioperm bitmap
 * itself mapped as read-only (used to implement copy-on-write during clone() in order
 * to prevent a race condition when user-space calls `clone()' followed by `ioperm()',
 * where we need to prevent the `ioperm()' call from potentially modifying the I/O
 * permissions bitmap of the child thread, which it otherwise would if the child thread
 * got scheduled on a different CPU, or hasn't yet received its first quantum) */
LOCAL NOBLOCK void
NOTHROW(KCALL ioperm_bitmap_unset_write_access)(struct ioperm_bitmap *__restrict self) {
	struct cpu *mycpu;
	pflag_t was = PREEMPTION_PUSHOFF();
	mycpu = THIS_CPU;
	if (FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == self) {
		/* Re-map, and only include read permissions. */
		pagedir_map(FORCPU(mycpu, thiscpu_x86_iob),
		            2 * PAGESIZE,
		            self->ib_pages,
		            PAGEDIR_MAP_FREAD);
	}
	PREEMPTION_POP(was);
}

INTERN NOBLOCK void
NOTHROW(KCALL fini_this_ioperm_bitmap)(struct task *__restrict self) {
	REF struct ioperm_bitmap *iob;
	iob = FORTASK(self, this_x86_ioperm_bitmap);
	if (iob) {
		assert(iob->ib_share >= 1);
		ATOMIC_FETCHDEC(iob->ib_share);
		decref_likely(iob);
	}
}
DEFINE_PERTASK_FINI(fini_this_ioperm_bitmap);

INTERN NOBLOCK void
NOTHROW(KCALL clone_this_ioperm_bitmap)(struct task *__restrict new_thread,
                                        uintptr_t UNUSED(flags)) {
	struct ioperm_bitmap *iob;
	/* The ioperm() permissions bitmap is always inherited by child threads!
	 * Only the iopl() level is not inherited in certain cases (as
	 * configurable via `/proc/sys/x86/keepiopl/(clone|exec|fork)') */
	iob = THIS_X86_IOPERM_BITMAP;
	/* unlikely, since this isn't really something that modern applications
	 * commonly make use of! */
	if unlikely(iob) {
		assert(iob->ib_share >= 1);
		incref(iob);
		/* Unset write-access if this is the first time the IOB is getting shared. */
		if (ATOMIC_FETCHINC(iob->ib_share) == 1)
			ioperm_bitmap_unset_write_access(iob);
		FORTASK(new_thread, this_x86_ioperm_bitmap) = iob;
		/* So-as to ensure that */

	}
}
DEFINE_PERTASK_CLONE(clone_this_ioperm_bitmap);



/* Destroy the given I/O permissions bitmap. */
PUBLIC NOBLOCK void
NOTHROW(FCALL ioperm_bitmap_destroy)(struct ioperm_bitmap *__restrict self) {
	assert(PERCPU(thiscpu_x86_ioperm_bitmap) != self);
	page_free(addr2page(self->ib_pages), 2);
	kfree(self);
}

PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC NOBLOCK_IF(flags & GFP_ATOMIC)
REF struct ioperm_bitmap *KCALL ioperm_bitmap_allocf(gfp_t flags) THROWS(E_BADALLOC) {
	pageptr_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc(sizeof(struct ioperm_bitmap), flags);
	iob = page_malloc(2);
	if unlikely(iob == PAGEPTR_INVALID) {
		kfree(result);
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 2 * PAGESIZE);
	}
	/* Fill both pages of memory with all ones (indicating that I/O access is denied) */
	result->ib_pages  = page2addr(iob);
	result->ib_refcnt = 1;
	result->ib_share  = 1;
	vm_memsetphyspages(result->ib_pages, 0xff, 2);
	return result;
}

PUBLIC WUNUSED ATTR_MALLOC NOBLOCK_IF(flags & GFP_ATOMIC)
REF struct ioperm_bitmap *NOTHROW(KCALL ioperm_bitmap_allocf_nx)(gfp_t flags) {
	pageptr_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc_nx(sizeof(struct ioperm_bitmap), flags);
	if likely(result) {
		iob = page_malloc(2);
		if unlikely(iob == PAGEPTR_INVALID) {
			kfree(result);
			return NULL;
		}
		/* Fill both pages of memory with all ones (indicating that I/O access is denied) */
		result->ib_pages  = page2addr(iob);
		result->ib_refcnt = 1;
		result->ib_share  = 1;
		vm_memsetphyspages(result->ib_pages, 0xff, 2);
	}
	return result;
}

/* Allocate a new io permissions bitmap with all permission bits set to disallow access. */
PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC REF struct ioperm_bitmap *KCALL
ioperm_bitmap_alloc(void) THROWS(E_BADALLOC) {
	return ioperm_bitmap_allocf(GFP_LOCKED | GFP_PREFLT);
}




/* Create a copy of the given I/O permissions bitmap. */
PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC NOBLOCK_IF(flags & GFP_ATOMIC) REF struct ioperm_bitmap *KCALL
ioperm_bitmap_copyf(struct ioperm_bitmap const *__restrict self, gfp_t flags) THROWS(E_BADALLOC) {
	pageptr_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc(sizeof(struct ioperm_bitmap), flags);
	iob = page_malloc(2);
	if unlikely(iob == PAGEPTR_INVALID) {
		kfree(result);
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 2 * PAGESIZE);
	}
	/* Copy I/O permission bits. */
	result->ib_pages  = page2addr(iob);
	result->ib_refcnt = 1;
	result->ib_share  = 1;
	vm_copypagesinphys(result->ib_pages, self->ib_pages, 2);
	return result;
}

PUBLIC WUNUSED ATTR_MALLOC NOBLOCK_IF(flags & GFP_ATOMIC) REF struct ioperm_bitmap *
NOTHROW(KCALL ioperm_bitmap_copyf_nx)(struct ioperm_bitmap const *__restrict self, gfp_t flags) {
	pageptr_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc_nx(sizeof(struct ioperm_bitmap), flags);
	if likely(result) {
		iob = page_malloc(2);
		if unlikely(iob == PAGEPTR_INVALID) {
			kfree(result);
			return NULL;
		}
		/* Copy I/O permission bits. */
		result->ib_pages  = page2addr(iob);
		result->ib_refcnt = 1;
		result->ib_share  = 1;
		vm_copypagesinphys(result->ib_pages, self->ib_pages, 2);
	}
	return result;
}

PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC REF struct ioperm_bitmap *KCALL
ioperm_bitmap_copy(struct ioperm_bitmap const *__restrict self) THROWS(E_BADALLOC) {
	return ioperm_bitmap_copyf(self, GFP_LOCKED | GFP_PREFLT);
}



LOCAL NOBLOCK void
NOTHROW(KCALL ioperm_bitmap_maskbyte)(struct ioperm_bitmap *__restrict self,
                                      size_t byte_index, u8 byte_mask, u8 byte_flag) {
	u8 *byte, oldval;
	struct vm_ptram pt = VM_PTRAM_INIT;
	byte = vm_ptram_map(&pt, self->ib_pages + byte_index);
	do {
		oldval = ATOMIC_READ(*byte);
	} while (!ATOMIC_CMPXCH_WEAK(*byte, oldval, (oldval & byte_mask) | byte_flag));
	vm_ptram_fini(&pt);
}

LOCAL NOBLOCK void
NOTHROW(KCALL ioperm_bitmap_maskbyte_c)(struct ioperm_bitmap *__restrict self,
                                        size_t byte_index,
                                        unsigned int minbit,
                                        unsigned int bitcnt,
                                        bool turn_on) {
	u8 bitmask;
	assert((minbit + bitcnt) <= 8);
	bitmask = (u8)(((1 << bitcnt) - 1) << minbit);
	ioperm_bitmap_maskbyte(self, byte_index, ~bitmask,
	                       turn_on ? 0 : bitmask);
}

/* Turn permission bits for a given range on/off. */
PUBLIC NOBLOCK void
NOTHROW(KCALL ioperm_bitmap_setrange)(struct ioperm_bitmap *__restrict self,
                                      u16 minport, u16 maxport, bool turn_on) {
	size_t minbyte, maxbyte;
	unsigned int minbit, bitcnt;
	assert(!wasdestroyed(self));
	assert(maxport >= minport);
	minbyte = FLOORDIV(minport, 8);
	maxbyte = CEILDIV(maxport + 1, 8) - 1;
	assert(maxbyte >= minbyte);
	if (maxbyte == minbyte) {
		/* Special case: only a single byte is getting modified. */
		minbit = minport & 7;
		bitcnt = (maxport - minport) + 1;
		/* Update the bitmap mask. */
		ioperm_bitmap_maskbyte_c(self, minbyte,
		                         minbit, bitcnt,
		                         turn_on);
		return;
	}
	/* Update the bitsets for the first and last affected bitset byte */
	minbit = minport & 7;
	ioperm_bitmap_maskbyte_c(self, minbyte, minbit, 8 - minbit, turn_on);
	ioperm_bitmap_maskbyte_c(self, maxbyte, 0, (maxport & 7) + 1, turn_on);
	/* Fill in all intermediate bytes. */
	if (minbyte + 1 < maxbyte) {
		vm_memsetphys(self->ib_pages + minbyte,
		              turn_on ? 0x00 : 0xff,
		              (maxbyte - minbyte) - 1);
	}
}




INTDEF byte_t __x86_iob_empty_base[];
PUBLIC struct ioperm_bitmap ioperm_bitmap_empty = {
	/* .ib_refcnt = */ 1, /* _ioperm_bitmap_empty */
	/* .ib_share  = */ 2, /* Prevent modifications */
	/* .ib_pages  = */ {
		{ (uintptr_t)__x86_iob_empty_base - KERNEL_CORE_BASE
#if __SIZEOF_VM_PHYS_T__ > __SIZEOF_POINTER__
		, 0
#endif /* __SIZEOF_VM_PHYS_T__ > __SIZEOF_POINTER__ */
		}
	}
};



INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_iobm)(void) {
	/* Fill the contents of the empty IOB vector with all FFh bytes,
	 * thus setting the access permissions of all I/O ports as restricted. */
#ifdef __x86_64__
	memsetq(__x86_iob_empty_base, UINT64_C(0xffffffffffffffff), 8192 / 8);
#else /* __x86_64__ */
	memsetl(__x86_iob_empty_base, UINT32_C(0xffffffff), 8192 / 4);
#endif /* !__x86_64__ */
	/* Prepare the IOB region for lazy memory mappings. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare_map(__x86_iob_empty_base, 2 * PAGESIZE))
		kernel_panic(FREESTR("Failed to prepare _bootcpu.tss.iob"));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	/* Unmap the initial IOB of the boot CPU. */
	pagedir_unmap(__x86_iob_empty_base, 2 * PAGESIZE);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IOBM_C */
