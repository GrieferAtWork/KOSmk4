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
#ifndef GUARD_MODRTM_MEMORY_C
#define GUARD_MODRTM_MEMORY_C 1
#define _KOS_SOURCE 1

#include "memory.h"

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/paging.h> /* PAGESIZE */
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>
#include <sched/task.h>

#include <hybrid/__assert.h>
#include <hybrid/atomic.h>

#include <assert.h>

#include "rtm.h"

DECL_BEGIN

/* Max amount of kernel heap memory that may be used by
 * a single instance of a `struct rtm_memory' structure. */
INTERN size_t rtm_memory_limit = 4 * PAGESIZE;


/* Finalize a given `struct rtm_memory' */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_fini)(struct rtm_memory *__restrict self) {
	size_t i;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		region = self->rm_regionv[i];
		assert(region);
		/* Drop our reference to the accessed datapart */
		decref_unlikely(rtm_memory_region_getpart(region));
		kfree(region);
	}
	kfree(self->rm_regionv);
}

/* Read RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTERN NONNULL((1, 3)) void FCALL
rtm_memory_read(struct rtm_memory *__restrict self, USER void const *addr,
                void *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	(void)self;
	(void)addr;
	(void)buf;
	(void)num_bytes;
	/* TODO */
	THROW(E_NOT_IMPLEMENTED);
}

/* Write RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTERN NONNULL((1, 3)) void FCALL
rtm_memory_write(struct rtm_memory *__restrict self, USER void *addr,
                 void const *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	(void)self;
	(void)addr;
	(void)buf;
	(void)num_bytes;
	/* TODO */
	THROW(E_NOT_IMPLEMENTED);
}







#ifdef VM_FORCEFAULT_FLAG_NOVIO
#define VM_FORCEFAULT_FLAG_NOVIO_OPT VM_FORCEFAULT_FLAG_NOVIO
#else /* VM_FORCEFAULT_FLAG_NOVIO */
#define VM_FORCEFAULT_FLAG_NOVIO_OPT 0
#endif /* !VM_FORCEFAULT_FLAG_NOVIO */

PRIVATE void FCALL
prefault_memory_for_writing(USER void *addr, size_t num_bytes) {
	vm_forcefault(ADDR_ISKERN(addr) ? &vm_kernel
	                                : THIS_VM,
	              addr, num_bytes,
	              VM_FORCEFAULT_FLAG_WRITE |
	              VM_FORCEFAULT_FLAG_NOVIO_OPT);
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_endwrite_modified_parts)(struct rtm_memory const *__restrict self,
                                                  size_t i) {
	while (i) {
		struct rtm_memory_region *region;
		--i;
		region = self->rm_regionv[i];
		if (rtm_memory_region_waschanged(region))
			sync_endwrite(rtm_memory_region_getpart(region));
	}
}


/* NOTE: The caller must be holding a read- or write-lock to `self' */
#define vm_datapart_get_rtm_version(self) \
	((self)->dp_futex ? (self)->dp_futex->fc_rtm_vers : 0)

/* Verify that the given address range is writable
 * without any chance of triggering a #PF */
PRIVATE ATTR_PURE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL rtm_verify_writable_nopf)(USER CHECKED void *addr,
                                        size_t num_bytes) {
	num_bytes += (uintptr_t)addr & PAGEMASK;
	for (;;) {
		if (!pagedir_iswritable(addr))
			return false;
		if (num_bytes <= PAGESIZE)
			break;
		num_bytes -= PAGESIZE;
		addr = (byte_t *)addr + PAGESIZE;
	}
	return true;
}


/* Atomically verify RTM version integrity, as well as apply RTM memory modifications.
 * @return: true:  Memory successfully applied
 * @return: false: Version of memory inconsistency detected (try again) */
INTERN NONNULL((1)) bool FCALL
rtm_memory_apply(struct rtm_memory const *__restrict self) {
	struct vm *myvm;
	size_t i;
	bool must_allocate_missing_futex_controllers;
	bool has_modified_kern;
	bool has_modified_user;
	myvm  = THIS_VM;
again_forcefault:
	/* Step #1: prefault the address ranges of all modified regions. */
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		region = self->rm_regionv[i];
		assert(region);
		if (!rtm_memory_region_waschanged(region))
			continue; /* Not modified... */
		/* Prefault memory. */
		prefault_memory_for_writing(region->mr_addr,
		                            region->mr_size);
	}

	/* Step #2: Acquire tx-locks to all of the modified data parts, and
	 *          verify that accessed data parts are still up-to-date */
again_acquire_region_locks:
	must_allocate_missing_futex_controllers = false;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		struct vm_datapart *part;
		region = self->rm_regionv[i];
		part   = rtm_memory_region_getpart(region);
		{
			struct vm_node *node;
			struct vm *effective_vm = myvm;
			size_t node_size_after_addr;
			pageid_t region_start_page;
			if (ADDR_ISKERN(region->mr_addr))
				effective_vm = &vm_kernel;
			region_start_page = PAGEID_ENCODE(region->mr_addr);
			node = vm_getnodeofpageid(myvm, region_start_page);
			if unlikely(!node || node->vn_part != part) {
				sync_endread(effective_vm);
				goto partially_release_locks_and_retry;
			}
			/* Make sure that the node has sufficient memory after `region->mr_addr'
			 * to account for at least `region->mr_size' bytes of memory. */
			node_size_after_addr = vm_node_getendpageid(node);
			sync_endread(effective_vm);
			node_size_after_addr -= region_start_page;
			node_size_after_addr *= PAGESIZE;
			node_size_after_addr += PAGESIZE - ((uintptr_t)region->mr_addr & PAGEMASK);
			if (region->mr_size > node_size_after_addr)
				goto partially_release_locks_and_retry;
		}
		if (rtm_memory_region_waschanged(region)) {
			struct vm_futex_controller *fxc;
			if (!sync_trywrite(part)) {
				rtm_memory_endwrite_modified_parts(self, i);
				/* Poll until the lock becomes available. - _then_ try acquiring locks again */
				while (!sync_canwrite(part))
					task_yield();
				goto again_acquire_region_locks;
			}
			/* Verify that the version of this region did not change */
			fxc = part->dp_futex;
			if (fxc) {
				if (fxc->fc_rtm_vers != region->mr_vers) {
endwrite_par_and_release_locks_and_retry:
					sync_endwrite(part);
					goto partially_release_locks_and_retry;
				}
			} else {
				if (region->mr_vers != 0)
					goto endwrite_par_and_release_locks_and_retry;
				/* We need to allocate this missing futex controller down below */
				must_allocate_missing_futex_controllers = true;
			}
		} else {
			if (!sync_tryread(part)) {
				rtm_memory_endwrite_modified_parts(self, i);
				/* Poll until the lock becomes available. - _then_ try acquiring locks again */
				while (!sync_canread(part))
					task_yield();
				goto again_acquire_region_locks;
			}
			/* Verify that the version of this region did not change */
			if (vm_datapart_get_rtm_version(part) != region->mr_vers) {
				sync_endread(part);
				goto partially_release_locks_and_retry;
			}
			sync_endread(part);
		}
	}
	if (must_allocate_missing_futex_controllers) {
		/* Allocate missing futex controllers. */
		for (i = 0; i < self->rm_regionc; ++i) {
			struct rtm_memory_region *region;
			struct vm_datapart *part;
			struct vm_futex_controller *ftx;
			region = self->rm_regionv[i];
			if (!rtm_memory_region_waschanged(region))
				continue;
			part = rtm_memory_region_getpart(region);
			ftx  = part->dp_futex;
			if (ftx)
				continue; /* Already allocated. */
			/* Must allocate the missing controller.
			 * Note that we're holding a couple of non-recursive locks
			 * at the moment, so we must be careful not to do a blocking
			 * memory allocation! */
			ftx = vm_futex_controller_allocf_nx(GFP_ATOMIC);
			if unlikely(!ftx) {
				/* The difficult case:
				 * In this case, we must release all of our beautiful locks, :(
				 * just so we can do a blocking heap allocation. And once
				 * that's done we'll have to start over with acquiring all
				 * of the necessary locks... */
				rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
#ifndef __OPTIMIZE_SIZE__
again_allocate_ftx_controller_for_part:
#endif /* !__OPTIMIZE_SIZE__ */
				ftx = vm_futex_controller_alloc();
				/* Try to install `ftx' into `part' */
				TRY {
					sync_write(part);
				} EXCEPT {
					vm_futex_controller_free(ftx);
					RETHROW();
				}
				if likely(!part->dp_futex) {
					/* Install the new controller. */
					part->dp_futex = ftx;
					sync_endwrite(part);
				} else {
					/* Race condition: Someone else already installed a controller. */
					sync_endwrite(part);
					vm_futex_controller_free(ftx);
				}
#ifndef __OPTIMIZE_SIZE__
				/* While we're at it, also try to look head if there are
				 * more modified regions with parts that are lacking their
				 * futex controllers. Because if there are more, then we
				 * can just fill in their controllers all at once, without
				 * having to fill them in one-at-a-time. */
				for (++i; i < self->rm_regionc; ++i) {
					region = self->rm_regionv[i];
					if (!rtm_memory_region_waschanged(region))
						continue; /* Not needed */
					part = rtm_memory_region_getpart(region);
					if (ATOMIC_READ(part->dp_futex))
						continue; /* Already allocated */
					/* Allocate another controller for this one! */
					goto again_allocate_ftx_controller_for_part;
				}
#endif /* !__OPTIMIZE_SIZE__ */
				goto again_acquire_region_locks;
			}
			part->dp_futex = ftx;
		}
	}

	/* Step #3: Verify that all modified in-memory data ranges can be
	 *          written to without any chance of triggering a pagefault. */
	has_modified_kern = false;
	has_modified_user = false;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		struct vm_datapart *part;
		struct vm *effective_vm;
		region = self->rm_regionv[i];
		if (!rtm_memory_region_waschanged(region))
			continue; /* Unchanged region. */
		part = rtm_memory_region_getpart(region);
		assert(sync_writing(part));
		effective_vm = myvm;
		if (ADDR_ISKERN(region->mr_addr))
			effective_vm = &vm_kernel;
		if (effective_vm == &vm_kernel) {
			/* Ensure that we've for a read-lock to the kernel's VM */
			if (!has_modified_kern) {
				if (!sync_tryread(&vm_kernel))
					goto again_acquire_region_locks_for_vm_lock;
				has_modified_kern = true;
			}
		} else {
			/* Ensure that we've for a read-lock to the user's VM */
			if (!has_modified_user) {
				if (!sync_tryread(effective_vm)) {
again_acquire_region_locks_for_vm_lock:
					rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
					while (!sync_canread(effective_vm))
						task_yield();
					goto again_acquire_region_locks;
				}
				has_modified_user = true;
			}
		}
		/* Verify that the backing memory of the accessed range is still writable.
		 * This was originally asserted by `prefault_memory_for_writing()' above,
		 * which we'd have to jump back to if memory isn't writable any more. */
		if unlikely(!rtm_verify_writable_nopf(region->mr_addr,
		                                      region->mr_size)) {
			if (has_modified_kern)
				sync_endwrite(&vm_kernel);
			if (has_modified_user)
				sync_endwrite(myvm);
			rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
			goto again_forcefault;
		}
	}
	/* ===== Point of no return =====
	 * After this point, we can no longer rewind to try again! */

	/* Step #4: Apply modifications, update version counters, and release locks */
	assert(i == self->rm_regionc);
	while (i) {
		struct rtm_memory_region *region;
		struct vm_datapart *part;
		--i;
		region = self->rm_regionv[i];
		if (!rtm_memory_region_waschanged(region))
			continue; /* Unchanged region. */
		part = rtm_memory_region_getpart(region);
		assert(sync_writing(part));
		/* Copy modified memory.
		 * NOTE: We've verified that all of this memory can be written without
		 *       causing a pagefault in step #3, and we know that the associated
		 *       mappings won't have changed in the mean time because we're still
		 *       holding locks to their corresponding VMs! */
#ifdef NDEBUG
		memcpy(region->mr_addr,
		       region->mr_data,
		       region->mr_size);
#else /* NDEBUG */
		{
			size_t error;
			error = memcpy_nopf(region->mr_addr,
			                    region->mr_data,
			                    region->mr_size);
			assertf(error == 0,
			        "But we're asserted that all of this should be writable...\n"
			        "region->mr_addr = %p\n"
			        "region->mr_data = %p\n"
			        "region->mr_size = %Iu\n"
			        "error           = %Iu\n",
			        region->mr_addr,
			        region->mr_data,
			        region->mr_size,
			        error);
		}
#endif /* !NDEBUG */
		/* Increment the RTM version counter of this part. */
		assert(part->dp_futex);
		++part->dp_futex->fc_rtm_vers;
		COMPILER_BARRIER();
		/* Release our lock to this part. */
		sync_endwrite(part);
	}
	if (has_modified_kern)
		sync_endwrite(&vm_kernel);
	if (has_modified_user)
		sync_endwrite(myvm);
	return true;
partially_release_locks_and_retry:
	rtm_memory_endwrite_modified_parts(self, i);
	return false;
}


DECL_END

#endif /* !GUARD_MODRTM_MEMORY_C */
