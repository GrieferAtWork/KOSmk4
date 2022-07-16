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
#ifndef GUARD_MODRTM_MEMORY_C
#define GUARD_MODRTM_MEMORY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "memory.h"

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/paging.h> /* PAGESIZE */
#include <kernel/printk.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/task.h>

#include <hybrid/__assert.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>

#include <kos/except/reason/inval.h>
#include <kos/nopf.h>

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "rtm.h"

#if !defined(NDEBUG) && 0
#define RTM_DEBUG(...) printk(KERN_DEBUG __VA_ARGS__)
#else /* !NDEBUG */
#define RTM_DEBUG(...) (void)0
#endif /* NDEBUG */


DECL_BEGIN

/* Max  amount of kernel heap memory that may be used by
 * a single instance of a `struct rtm_memory' structure. */
INTERN size_t rtm_memory_limit = 4 * PAGESIZE;

/* NOTE: The caller must be holding a read- or write-lock to `self' */
#define mpart_get_rtm_version(self) \
	((self)->mp_meta ? (self)->mp_meta->mpm_rtm_vers : 0)

#if !defined(NDEBUG) || 1
#define assert_rtm_memory_region(self) (void)0
#else /* !NDEBUG */
#define assert_rtm_memory_region(self)                    \
	assertf(kmalloc_usable_size(self) >=                  \
	        offsetof(struct rtm_memory_region, mr_data) + \
	        rtm_memory_region_getsize(self),              \
	        "Allocated region size is too small:\n"       \
	        "region: %p (%p..%p)\n"                       \
	        "usable_size:   %" PRIuSIZ "\n"               \
	        "required_size: %" PRIuSIZ "\n",              \
	        self, (self)->mr_addrlo, (self)->mr_addrhi,   \
	        kmalloc_usable_size(self),                    \
	        offsetof(struct rtm_memory_region, mr_data) + \
	        rtm_memory_region_getsize(self))
#endif /* NDEBUG */


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_free)(struct rtm_memory *__restrict self, void *ptr) {
	self->rm_mem_avl += kmalloc_usable_size(ptr);
	kfree(ptr);
}

/* Try to truncate `*pheap_pointer' to point to a heap block of only  `num_bytes'
 * bytes of memory, returning `true'  on success (`*pheap_pointer' now points  at
 * a heap block that is smaller than before, but still holds at least `num_bytes'
 * bytes of memory), or `false' (`*pheap_pointer'  could not be trucated and  has
 * been left unmodified)
 * NOTE: When `*pheap_pointer' is equal to `protected_pointer', always return `false' */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL rtm_memory_truncate)(struct rtm_memory *__restrict self,
                                   void **__restrict pheap_pointer,
                                   size_t num_bytes,
                                   void *protected_pointer) {
	void *heap_pointer;
	size_t oldavl, newavl;
	heap_pointer = *pheap_pointer;
	if (heap_pointer == protected_pointer)
		return false; /* Don't truncate this one! */
	oldavl = kmalloc_usable_size(heap_pointer);
	assertf(oldavl >= num_bytes,
	        "oldavl    = %" PRIuSIZ "\n"
	        "num_bytes = %" PRIuSIZ "\n",
	        oldavl, num_bytes);
	if (oldavl == num_bytes)
		return false; /* Can't possibly be truncated! */
	/* Try to truncate the pointer */
	heap_pointer = krealloc_nx(heap_pointer, num_bytes, GFP_NORMAL);
	if unlikely(!heap_pointer)
		return false; /* Shouldn't happen (tm) */
	*pheap_pointer = heap_pointer;
	newavl = kmalloc_usable_size(heap_pointer);
	assertf(newavl >= num_bytes,
	        "newavl    = %" PRIuSIZ "\n"
	        "num_bytes = %" PRIuSIZ "\n",
	        newavl, num_bytes);
	assertf(newavl <= oldavl,
	        "newavl = %" PRIuSIZ "\n"
	        "oldavl = %" PRIuSIZ "\n",
	        newavl, oldavl);
	if (newavl >= oldavl) /* Should actually be `newavl == oldavl'; is `>=' for safety */
		return false; /* Nothing's changed */
	/* Yes! We did actually manage to truncate the pointer! */
	self->rm_mem_avl += oldavl;
	self->rm_mem_avl -= newavl;
	return true;
}

#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
/* Try to reclaim memory from the given pending system call. */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL rtm_pending_syscall_reclaim)(struct rtm_memory *__restrict self,
                                           struct rtm_pending_syscall *__restrict sc,
                                           void *protected_pointer) {
	bool result = false;
	switch (sc->rps_kind) {

	case RTM_PENDING_SYSCALL_SYSLOG:
		result = rtm_memory_truncate(self,
		                             (void **)&sc->rps_syslog.rps_text,
		                             sc->rps_syslog.rps_size,
		                             protected_pointer);
		break;

	default:
		break;
	}
	return result;
}
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */


/* Try to reclaim unused memory by truncating heap pointers reachable from `self'
 * Note  however that a  heap pointer `protected_pointer'  will not be truncated! */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL rtm_memory_reclaim)(struct rtm_memory *__restrict self,
                                  void *protected_pointer) {
	size_t i;
	bool result;
	/* Reclaim memory from the region vector */
	result = rtm_memory_truncate(self, (void **)&self->rm_regionv,
	                             self->rm_regionc * sizeof(struct rtm_memory_region *),
	                             protected_pointer);
	/* Reclaim memory from individual regions */
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region **pregion;
		pregion = &self->rm_regionv[i];
		result |= rtm_memory_truncate(self,
		                              (void **)pregion,
		                              offsetof(struct rtm_memory_region, mr_data) +
		                              rtm_memory_region_getsize(*pregion),
		                              protected_pointer);
	}
#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
	if (self->rm_sysc) {
		for (i = 0; i < self->rm_sysc; ++i) {
			result |= rtm_pending_syscall_reclaim(self,
			                                      &self->rm_sysv[i],
			                                      protected_pointer);
		}
		result |= rtm_memory_truncate(self, (void **)&self->rm_sysv,
		                              self->rm_sysc * sizeof(struct rtm_pending_syscall),
		                              protected_pointer);
	}
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */
	return result;
}


/* Heap helpers that will automatically account for consumed heap memory. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
rtm_memory_malloc(struct rtm_memory *__restrict self,
                  size_t num_bytes) {
	void *result;
	size_t result_usable;
again:
	if unlikely(num_bytes > self->rm_mem_avl) {
		if (rtm_memory_reclaim(self, NULL))
			goto again;
do_throw_badalloc:
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		      num_bytes);
	}
	result        = kmalloc(num_bytes, GFP_NORMAL);
	result_usable = kmalloc_usable_size(result);
	if unlikely(result_usable > self->rm_mem_avl) {
		/* Must reclaim more memory! */
		if (!rtm_memory_reclaim(self, NULL)) {
do_free_result_and_throw_badalloc:
			kfree(result);
			num_bytes = result_usable;
			goto do_throw_badalloc;
		}
		/* Check if we've got sufficient memory now. */
		if (result_usable > self->rm_mem_avl)
			goto do_free_result_and_throw_badalloc;
	}
	self->rm_mem_avl -= result_usable;
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
rtm_memory_realloc(struct rtm_memory *__restrict self,
                   void *ptr, size_t num_bytes) {
	void *result;
	size_t old_bytes;
	size_t result_bytes;
	size_t missing;
	if (!ptr)
		return rtm_memory_malloc(self, num_bytes);
	old_bytes = kmalloc_usable_size(ptr);
	if (num_bytes <= old_bytes) {
		/* Still try to truncate the pointer. */
		if (old_bytes == num_bytes)
			return ptr;
		result = krealloc_nx(ptr, num_bytes, GFP_NORMAL);
		if unlikely(!result)
			return ptr; /* Shouldn't happen (tm) */
		result_bytes = kmalloc_usable_size(result);
		assert(result_bytes >= num_bytes);
		assert(result_bytes <= old_bytes);
		self->rm_mem_avl += old_bytes;
		self->rm_mem_avl -= result_bytes;
		return result;
	}
	missing = num_bytes - old_bytes;
again_check_missing:
	if unlikely(missing > self->rm_mem_avl) {
		if (rtm_memory_reclaim(self, ptr))
			goto again_check_missing;
do_throw_badalloc_missing:
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		      missing);
	}
#if 0
	/* Must increase the available memory. */
	result = krealloc_in_place(ptr, num_bytes, GFP_NORMAL);
	if (result) {
		/* Inplace relocation was successful! */
		assert(result == ptr);
		result_bytes = kmalloc_usable_size(result);
		assert(result_bytes >= num_bytes);
		assert(result_bytes > old_bytes);
		missing = result_bytes - old_bytes;
again_check_missing_after_inplace:
		if unlikely(missing > self->rm_mem_avl) {
			if (rtm_memory_reclaim(self, ptr))
				goto again_check_missing_after_inplace;
			/* (Try to) re-truncate the pointer to its previous size. */
			krealloc_in_place_nx(ptr, old_bytes, GFP_NORMAL);
			/* Allocation failed. */
			goto do_throw_badalloc_missing;
		}
		self->rm_mem_avl -= missing;
		return result;
	}
#endif
	/* The memory block is being extended, but cannot be done so in-place.
	 * -> Must allocate a new (larger) block to which we can then copy
	 *    the old block's data. */
	result = kmalloc(num_bytes, GFP_NORMAL);
	result_bytes = kmalloc_usable_size(result);
	assert(result_bytes >= num_bytes);
	assert(result_bytes > old_bytes);
	missing = result_bytes - old_bytes;
again_check_missing_after_malloc:
	if unlikely(missing > self->rm_mem_avl) {
		if (rtm_memory_reclaim(self, ptr))
			goto again_check_missing_after_malloc;
		kfree(result);
		/* Allocation failed. */
		goto do_throw_badalloc_missing;
	}
	/* Copy data into the new heap block. */
	memcpy(result, ptr, old_bytes);
	/* Free the old block */
	kfree(ptr);
	/* Return the new block */
	return result;
}


/* Helper  to resize a `struct rtm_memory_region', such that the
 * `mr_data' vector of the returned region is capable of holding
 * at least `mr_data_size_in_bytes' bytes of memory.
 * Note however that this function does not update `mr_addr(lo|hi)'
 * to  reflect  the  increased   size  of  the  `mr_data'   vector! */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct rtm_memory_region *FCALL
rtm_memory_realloc_region(struct rtm_memory *__restrict self,
                          struct rtm_memory_region *__restrict region,
                          size_t mr_data_size_in_bytes) {
	void *result;
	result = rtm_memory_realloc(self,
	                            region,
	                            offsetof(struct rtm_memory_region, mr_data) +
	                            mr_data_size_in_bytes);
	return (struct rtm_memory_region *)result;
}


#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
/* Finalize the given pending system call. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_pending_syscall_fini)(struct rtm_pending_syscall *__restrict self) {
	switch (self->rps_kind) {

	case RTM_PENDING_SYSCALL_SYSLOG:
		kfree(self->rps_syslog.rps_text);
		break;

	default:
		break;
	}
}
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */

/* Finalize a given `struct rtm_memory' */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_fini)(struct rtm_memory *__restrict self) {
	size_t i;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		region = self->rm_regionv[i];
		assert(region);
		/* Drop our reference to the accessed mpart */
		decref_unlikely(rtm_memory_region_getpart(region));
		kfree(region);
	}
	kfree(self->rm_regionv);
#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
	if (self->rm_sysc) {
		for (i = 0; i < self->rm_sysc; ++i)
			rtm_pending_syscall_fini(&self->rm_sysv[i]);
		kfree(self->rm_sysv);
	}
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */
}



#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS

/* Allocate a new entry for a pending system call in `self'
 * The returned entry isn't initialized yet, but is already
 * accounted for in `self->rm_sysc' */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct rtm_pending_syscall *FCALL
rtm_memory_schedule_syscall(struct rtm_memory *__restrict self) {
	struct rtm_pending_syscall *result;
	size_t avlsize, reqsize;
	result  = self->rm_sysv;
	avlsize = kmalloc_usable_size(result);
	reqsize = (self->rm_sysc + 1) * sizeof(struct rtm_pending_syscall);
	if (reqsize > avlsize) {
		result = (struct rtm_pending_syscall *)rtm_memory_realloc(self,
		                                                          result,
		                                                          reqsize);
		self->rm_sysv = result;
	}
	result += self->rm_sysc++;
	return result;
}


/* Schedule   a  pending  call  to  `sys_syslog()',  to-be  executed
 * unconditionally just before a true-return of `rtm_memory_apply()' */
INTERN NONNULL((1)) void FCALL
rtm_memory_schedule_sys_syslog(struct rtm_memory *__restrict self,
                               syscall_ulong_t level,
                               USER char const *str, size_t len) {
	struct rtm_pending_syscall *ent;
	char *str_copy;
	/* Verify that the `level' argument is valid. */
	if unlikely(level >= SYSLOG_LEVEL_COUNT) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SYSLOG_LEVEL,
		      level);
	}
	/* Allocate a local copy of `str...+=len' */
	str_copy = (char *)rtm_memory_malloc(self, len);
	TRY {
		/* Copy `str...+=len' into our local copy. */
		rtm_memory_read(self, str, str_copy, len);
		/* Allocate a new pending system call entry. */
		ent = rtm_memory_schedule_syscall(self);
	} EXCEPT {
		rtm_memory_free(self, str_copy);
		RETHROW();
	}
	/* Fill in the pending system call. */
	ent->rps_kind = RTM_PENDING_SYSCALL_SYSLOG;
	ent->rps_data = (uintptr_half_t)level;
	ent->rps_syslog.rps_text  = str_copy; /* Inherit */
	ent->rps_syslog.rps_size  = len;
}

/* Execute system calls that have been scheduled as pending.
 * Called  prior  to a  true-return  of `rtm_memory_apply()' */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL rtm_memory_exec_pending_syscalls)(struct rtm_memory const *__restrict self) {
	size_t i;
	for (i = 0; i < self->rm_sysc; ++i) {
		struct rtm_pending_syscall const *sc;
		sc = &self->rm_sysv[i];
		switch (sc->rps_kind) {

		case RTM_PENDING_SYSCALL_SYSLOG:
			syslog_printer((void *)(uintptr_t)sc->rps_data,
			               sc->rps_syslog.rps_text,
			               sc->rps_syslog.rps_size);
			break;

		default:
			break;
		}
	}
}
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */


#ifdef CONFIG_MODRTM_FAR_REGIONS
/* Mark the given `region' as changed whilst correctly accounting for far regions. */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL rtm_memory_mark_region_as_changed)(struct rtm_memory *__restrict self,
                                                 size_t region_index,
                                                 struct rtm_memory_region *__restrict region) {
	size_t i;
	struct rtm_memory_region *base_region;
	struct mpart *mypart;
	assert(region_index < self->rm_regionc);
	assert(self->rm_regionv[region_index] == region);
	if (rtm_memory_region_waschanged(region))
		return; /* Nothing to do here! */
	if (!rtm_memory_region_isfarregion(region)) {
		/* Simple case: this isn't a far region, so we can just mark it as changed. */
		rtm_memory_region_setchanged(region);
		return;
	}
	/* The complicated case: We're dealing with a far region.
	 * The rule that we must follow here is:
	 *    A  far  region  can  only  be  marked  as  changed  if the
	 *    associated base region has already been marked as changed.
	 * As such, we must first find our base region. */
	assert(self->rm_regionc >= 2);
	mypart = rtm_memory_region_getpart(region);
	if (region_index > 0) {
		i = region_index - 1;
		for (;;) {
			base_region = self->rm_regionv[i];
			if (rtm_memory_region_getpart(base_region) != mypart)
				break; /* The base region must be located above `region_index' */
			if (!rtm_memory_region_isfarregion(base_region))
				goto found_base_region;
			if (!i)
				break;
			--i;
		}
	}
	i = region_index + 1;
	for (;;) {
		assert(i < self->rm_regionc);
		base_region = self->rm_regionv[i];
		assert(rtm_memory_region_getpart(base_region) == mypart);
		if (!rtm_memory_region_isfarregion(base_region))
			break; /* Found it! */
		++i;
	}
found_base_region:
	/* With the base region found, check if it has already been marked as changed */
	if (rtm_memory_region_waschanged(base_region)) {
		/* The base region was already marked as changed.
		 * -> We can just mark ourself as changed, too. */
		rtm_memory_region_setchanged(region);
		return;
	}
	/* The last case: We are the first region from `base_region's set of
	 *                regions that has been modified. - As such, we  can
	 *                simply handle this case  by becoming the new  base
	 *                region! */
	base_region->mr_part = (REF void *)((uintptr_t)mypart | RTM_MEMORY_REGION_ISFARREGION_FLAG);
	region->mr_part      = (REF void *)((uintptr_t)mypart | RTM_MEMORY_REGION_CHANGED_FLAG);
}

#ifdef CONFIG_MODRTM_FAR_REGION_REMERGE
/* Try to merge 2 adjacent regions into a singular, new one. */
PRIVATE NONNULL((1, 3)) bool
NOTHROW(FCALL rtm_memory_try_merge_regions)(struct rtm_memory *__restrict self,
                                            size_t region_lo_index,
                                            struct rtm_memory_region *__restrict region_lo,
                                            struct rtm_memory_region *__restrict region_hi) {
	size_t losize, hisize, region_lo_oldavl, region_hi_oldavl;
	size_t effective_avail_without_merge, merged_avl;
	assert_rtm_memory_region(region_lo);
	assert_rtm_memory_region(region_hi);
	assert(self->rm_regionc >= 2);
	assert(region_lo_index + 1 < self->rm_regionc);
	assert(self->rm_regionv[region_lo_index + 0] == region_lo);
	assert(self->rm_regionv[region_lo_index + 1] == region_hi);
	assert((byte_t *)region_lo->mr_addrhi + 1 == (byte_t *)region_hi->mr_addrlo);
	assert(rtm_memory_region_getpart(region_lo) ==
	       rtm_memory_region_getpart(region_hi));
	losize = rtm_memory_region_getsize(region_lo);
	hisize = rtm_memory_region_getsize(region_hi);
	region_lo_oldavl = kmalloc_usable_size(region_lo);
	region_hi_oldavl = kmalloc_usable_size(region_hi);
	/* (try to) resize `region_lo' to allocate space for the missing `hisize' */
	region_lo = (struct rtm_memory_region *)krealloc_nx(region_lo,
	                                                    offsetof(struct rtm_memory_region, mr_data) +
	                                                    losize + hisize,
	                                                    GFP_NORMAL);
	if unlikely(!region_lo)
		return false; /* Merge optimization failed... */
	/* Make sure  that the  newly allocated  `region_lo' doesn't  have too  much
	 * overhead that would cause it to be too large for us to be allowed to use. */
	merged_avl = kmalloc_usable_size(region_lo);
	effective_avail_without_merge = self->rm_mem_avl +
	                                region_lo_oldavl +
	                                region_hi_oldavl;
	if unlikely(merged_avl > effective_avail_without_merge) {
		struct rtm_memory_region *downsized;
		/* The  reallocated `region_lo' is too large for us to be allowed to use it.
		 * Down-size it again (and hope that doing so frees up the illegal overhead) */
		downsized = (struct rtm_memory_region *)krealloc_nx(region_lo,
		                                                    offsetof(struct rtm_memory_region, mr_data) +
		                                                    losize,
		                                                    GFP_NORMAL);
		if unlikely(!downsized) {
			self->rm_regionv[region_lo_index] = region_lo;
			self->rm_mem_avl = 0; /* Prevent underflow... */
			return false;
		}
		self->rm_regionv[region_lo_index] = downsized;
		merged_avl = kmalloc_usable_size(downsized);
		self->rm_mem_avl += region_lo_oldavl;
		if unlikely(OVERFLOW_USUB(self->rm_mem_avl, merged_avl, &self->rm_mem_avl))
			self->rm_mem_avl = 0; /* Prevent underflow... */
		return false;
	}
	/* All right! The reallocated `region_lo' now has enough
	 *            storage  for  all  data  from  `region_hi'
	 * -> Now to copy over all of the data, as well as memory attributes. */
	memcpy(region_lo->mr_data + losize, region_hi->mr_data, hisize);
	region_lo->mr_addrhi = region_hi->mr_addrhi;
	/* If the deleted region was changed, force our region to be marked as changed */
	if (rtm_memory_region_waschanged(region_hi))
		rtm_memory_region_setchanged(region_lo);
	if (!rtm_memory_region_isfarregion(region_hi)) {
		assert(rtm_memory_region_isfarregion(region_lo));
		/* Become  the  base region  if  the deleted
		 * region used to be the base region before. */
		region_lo->mr_part = (REF void *)((uintptr_t)region_lo->mr_part & ~RTM_MEMORY_REGION_ISFARREGION_FLAG);
	}
	/* Drop the one reference to the associated part that was held by the deleted region.
	 * Since  our region uses  the same part, we  know that at  least 2 references _must_
	 * exist to said part, meaning that we can use `decref_nokill()' here! */
	decref_nokill(rtm_memory_region_getpart(region_hi));

	/* Free the old region_hi */
	kfree(region_hi);

	/* Update memory accounting and fix-up the list of regions. */
	self->rm_mem_avl = effective_avail_without_merge - merged_avl;
	self->rm_regionv[region_lo_index] = region_lo; /* Inherit */
	--self->rm_regionc;
	memmovedownc(&self->rm_regionv[region_lo_index + 1],
	             &self->rm_regionv[region_lo_index + 2],
	             self->rm_regionc - (region_lo_index + 1),
	             sizeof(struct rtm_memory_region *));
	return true;
}
#endif /* CONFIG_MODRTM_FAR_REGION_REMERGE */


#else /* CONFIG_MODRTM_FAR_REGIONS */
#define rtm_memory_mark_region_as_changed(self, region_index, region) \
	rtm_memory_region_setchanged(region)
#endif /* !CONFIG_MODRTM_FAR_REGIONS */


/* Copy `num_bytes' from `src', but throw an exception if VIO memory is accessed. */
PRIVATE void FCALL
rtm_memcpy_prefault(struct mman *__restrict effective_mm,
                    void *__restrict dst,
                    USER void const *src,
                    size_t num_bytes) {
	size_t copy_error;
	while ((copy_error = memcpy_nopf(dst, src, num_bytes)) != 0) {
		size_t copy_ok;
		assert(copy_error <= num_bytes);
		/* Account for data that could be copied. */
		copy_ok = num_bytes - copy_error;
		dst = (byte_t *)dst + copy_ok;
		src = (byte_t const *)src + copy_ok;
		num_bytes = copy_error;
		/* Prefault the missing area. */
		mman_forcefault(effective_mm, src, num_bytes,
		                MMAN_FAULT_F_NOVIO);
	}
}

/* Insert `region' into  `self' at  index `index',  or
 * free() it before re-throwing a bad-alloc exception. */
PRIVATE void FCALL
rtm_memory_insert_region(struct rtm_memory *__restrict self, size_t index,
                         /*inherit(always)*/ struct rtm_memory_region *__restrict region) {
	size_t avl_vector_size;
	size_t req_vector_size;
	avl_vector_size = kmalloc_usable_size(self->rm_regionv);
	req_vector_size = (self->rm_regionc + 1) * sizeof(struct rtm_memory_region *);
	if (req_vector_size > avl_vector_size) {
		/* Must increase the allocated vector size. */
		struct rtm_memory_region **newvec;
		TRY {
			newvec = (struct rtm_memory_region **)rtm_memory_realloc(self,
			                                                         self->rm_regionv,
			                                                         req_vector_size);
		} EXCEPT {
			decref(rtm_memory_region_getpart(region));
			rtm_memory_free(self, region);
			RETHROW();
		}
		self->rm_regionv = newvec;
	}
	assert(index <= self->rm_regionc);
	memmoveupc(&self->rm_regionv[index + 1],
	           &self->rm_regionv[index],
	           self->rm_regionc - index,
	           sizeof(struct rtm_memory_region *));
	self->rm_regionv[index] = region; /* Inherit */
	++self->rm_regionc;
	/* Assert that the region's address range is consistent with its neighbors. */
	assertf(index == 0 ||
	        self->rm_regionv[index - 1]->mr_addrhi < region->mr_addrlo,
	        "prev = %p...%p\n"
	        "curr = %p...%p\n",
	        self->rm_regionv[index - 1]->mr_addrlo,
	        self->rm_regionv[index - 1]->mr_addrhi,
	        region->mr_addrlo, region->mr_addrhi);
	assertf(index == self->rm_regionc - 1 ||
	        self->rm_regionv[index + 1]->mr_addrlo > region->mr_addrhi,
	        "curr = %p...%p\n"
	        "next = %p...%p\n",
	        region->mr_addrlo, region->mr_addrhi,
	        self->rm_regionv[index + 1]->mr_addrlo,
	        self->rm_regionv[index + 1]->mr_addrhi);
}


#ifdef CONFIG_MODRTM_FAR_REGIONS
PRIVATE ATTR_RETNONNULL struct rtm_memory_region *FCALL
rtm_memory_create_far_region(struct rtm_memory *__restrict self,
                             size_t region_insert_index,
                             USER void *region_min,
                             USER void *region_max,
                             struct mman *__restrict effective_mm,
                             struct mpart *__restrict part,
                             uintptr_t version) {
	size_t region_size;
	struct rtm_memory_region *result;
	region_size = (size_t)((byte_t *)region_max -
	                       (byte_t *)region_min) +
	              1;
	result = (struct rtm_memory_region *)rtm_memory_malloc(self,
	                                                       offsetof(struct rtm_memory_region, mr_data) +
	                                                       region_size);
	/* Copy read data from main memory. */
	TRY {
		rtm_memcpy_prefault(effective_mm,
		                    result->mr_data,
		                    region_min,
		                    region_size);
	} EXCEPT {
		rtm_memory_free(self, result);
		RETHROW();
	}
	/* Fill in all of the remaining region meta-data */
	result->mr_addrlo = region_min;
	result->mr_addrhi = region_max;
	result->mr_part   = (REF void *)((uintptr_t)incref(part) | RTM_MEMORY_REGION_ISFARREGION_FLAG);
	result->mr_vers   = version;
	/* Insert the newly created region into the memory manager */
	rtm_memory_insert_region(self, region_insert_index, result); /* Inherit: result */
	return result;
}

#endif /* CONFIG_MODRTM_FAR_REGIONS */



/* Read/Write RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
PRIVATE NONNULL((1, 3)) void FCALL
rtm_memory_readwrite(struct rtm_memory *__restrict self, USER void *addr,
                     void *__restrict buf, size_t num_bytes, bool write)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	/* Step #1: Check if the given `addr' is apart of an existing region. */
	size_t i;
	if (!num_bytes)
		return; /* Nothing to do here! */
again:
	i = 0;
	BSEARCH_RANGE (i, self->rm_regionv, self->rm_regionc,
	                                    ->mr_addrlo,
	                                    ->mr_addrhi,
	               addr) {
		struct rtm_memory_region *region;
		size_t avail_bytes;
		byte_t *rdat;
		/* Found it! */
		region = self->rm_regionv[i];
again_rw_region:
		assert(addr >= region->mr_addrlo);
		assert(addr <= region->mr_addrhi);
		avail_bytes = 1 + (size_t)((byte_t *)region->mr_addrhi -
		                           (byte_t *)addr);
		/* Start by copying whatever amount of data has already been loaded. */
		rdat = region->mr_data + (size_t)((byte_t *)addr -
		                                  (byte_t *)region->mr_addrlo);
		if likely(avail_bytes >= num_bytes) {
			/* All data is already available */
			if (write) {
				memcpy(rdat, buf, num_bytes);
				buf = (byte_t *)buf + avail_bytes;
				rtm_memory_mark_region_as_changed(self, i, region);
			} else {
				buf = mempcpy(buf, rdat, num_bytes);
			}
			return;
		}
		if (write) {
			memcpy(rdat, buf, avail_bytes);
			buf = (byte_t *)buf + avail_bytes;
			rtm_memory_mark_region_as_changed(self, i, region);
		} else {
			buf = mempcpy(buf, rdat, avail_bytes);
		}
		addr = (USER byte_t *)addr + avail_bytes;
		num_bytes -= avail_bytes;
		/* Some data is still missing.
		 * -> Check if the next region starts where the current left off.
		 *    If it does  (start there,  that is), then  we can  continue
		 *    accessing data from it. */
		if ((i + 1) < self->rm_regionc) {
			struct rtm_memory_region *next_region;
			next_region = self->rm_regionv[i + 1];
			if (next_region->mr_addrlo == (byte_t *)region->mr_addrhi + 1) {
				/* Yes! -> Continue accessing from this region! */
				region = next_region;
				++i;
				goto again_rw_region;
			}
		}
	}
	/* No region is associated with `addr'!
	 * -> Must allocate a new one, or try to extend an existing one.
	 *
	 * But first off: Check that the given `addr' is valid when `rm_chkuser' is set. */
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
	if likely(self->rm_chkuser)
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
	{
		if (write) {
			validate_writable(addr, num_bytes);
		} else {
			validate_readable(addr, num_bytes);
		}
	}
	{
		struct mman *effective_mm;
		struct mnode *node;
		struct mpart *part;
		struct rtm_memory_region *region;
		size_t j, access_bytes;
		/* Next, acquire a lock to the effective MMan */
#ifdef KERNELSPACE_HIGHMEM
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
		effective_mm = &mman_kernel;
		if (ADDR_ISUSER(addr))
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
		{
			size_t maxsize;
			effective_mm = THIS_MMAN;
			/* Check if the entire address range is apart of user-space. */
			maxsize = (size_t)((byte_t *)KERNELSPACE_BASE - (byte_t *)addr);
			if unlikely(num_bytes > maxsize) {
				/* Split the read into 2 segments. */
				rtm_memory_readwrite(self,
				                     (byte_t *)KERNELSPACE_BASE,
				                     (byte_t *)buf + maxsize,
				                     num_bytes - maxsize,
				                     write);
				num_bytes = maxsize;
			}
#ifdef ADDR_IS_NONCANON
			if (ADDR_IS_NONCANON((byte_t *)addr + num_bytes - 1)) {
				uintptr_t context;
				context = E_SEGFAULT_CONTEXT_FAULT |
				          E_SEGFAULT_CONTEXT_NONCANON |
				          E_SEGFAULT_CONTEXT_USERCODE;
				if (write)
					context |= E_SEGFAULT_CONTEXT_WRITING;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
				if unlikely(!self->rm_chkuser)
					context &= ~E_SEGFAULT_CONTEXT_USERCODE;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
				THROW(E_SEGFAULT_UNMAPPED,
				      (byte_t *)addr + num_bytes - 1,
				      context);
			}
#endif /* ADDR_IS_NONCANON */
		}
#else /* KERNELSPACE_HIGHMEM */
		effective_mm = THIS_MMAN;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
		if (ADDR_ISKERN(addr)) {
			size_t maxsize;
			if unlikely((byte_t *)addr + num_bytes < (byte_t *)addr) {
				uintptr_t context;
				context = E_SEGFAULT_CONTEXT_FAULT |
				          E_SEGFAULT_CONTEXT_USERCODE;
				if (write)
					context |= E_SEGFAULT_CONTEXT_WRITING;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
				if unlikely(!self->rm_chkuser)
					context &= ~E_SEGFAULT_CONTEXT_USERCODE;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
				THROW(E_SEGFAULT_UNMAPPED, 0, context);
			}
			effective_mm = &mman_kernel;
			/* Check if the entire address range is apart of kernel-space. */
			maxsize = (size_t)((byte_t *)KERNELSPACE_END - (byte_t *)addr);
			if unlikely(num_bytes > maxsize) {
#ifdef ADDR_IS_NONCANON
				if (ADDR_IS_NONCANON((byte_t *)KERNELSPACE_END) {
					uintptr_t context;
					context = E_SEGFAULT_CONTEXT_FAULT |
					          E_SEGFAULT_CONTEXT_NONCANON |
					          E_SEGFAULT_CONTEXT_USERCODE;
					if (write)
						context |= E_SEGFAULT_CONTEXT_WRITING;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
					if unlikely(!self->rm_chkuser)
						context &= ~E_SEGFAULT_CONTEXT_USERCODE;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
					THROW(E_SEGFAULT_UNMAPPED,
					      (byte_t *)KERNELSPACE_END,
					      context);
				}
#endif /* ADDR_IS_NONCANON */
				/* Split the read into 2 segments. */
				rtm_memory_readwrite(self,
				                     (byte_t *)KERNELSPACE_END,
				                     (byte_t *)buf + maxsize,
				                     num_bytes - maxsize,
				                     write);
				num_bytes = maxsize;
			}
		}
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
#endif /* !KERNELSPACE_HIGHMEM */
		/* Force the address range to be faulted. */
		mman_forcefault(effective_mm, addr, num_bytes,
		                MMAN_FAULT_F_NOVIO);
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
again_lock_effective_mman:
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
		mman_lock_read(effective_mm);
		/* Locate the mnode that is backing the storage for `addr' */
		node = mman_mappings_locate(effective_mm, addr);
		/* Verify address permissions. */
#ifdef LIBVIO_CONFIG_ENABLED
		if unlikely(!node || (part = node->mn_part) == NULL ||
		            part->mp_state == MPART_ST_VIO)
#else /* LIBVIO_CONFIG_ENABLED */
		if unlikely(!node || (part = node->mn_part) == NULL)
#endif /* !LIBVIO_CONFIG_ENABLED */
		{
			uintptr_t context;
			context = E_SEGFAULT_CONTEXT_FAULT |
			          E_SEGFAULT_CONTEXT_USERCODE;
#ifdef LIBVIO_CONFIG_ENABLED
			if (node && node->mn_part &&
			    node->mn_part->mp_state == MPART_ST_VIO)
				context |= E_SEGFAULT_CONTEXT_VIO;
#endif /* LIBVIO_CONFIG_ENABLED */
			mman_lock_endread(effective_mm);
			/* Unmapped address! */
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			if unlikely(!self->rm_chkuser)
				context &= ~E_SEGFAULT_CONTEXT_USERCODE;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			if (write)
				context |= E_SEGFAULT_CONTEXT_WRITING;
			THROW(E_SEGFAULT_UNMAPPED, addr, context);
		}
		/* NOTE: For write-access, we assert both read+write, since any write operation in RTM-mode is
		 *       the equivalent of a read-compare-exchange operation, meaning that in order to perform
		 *       a write, we literally and figuratively have to perform a read first! */
		if unlikely(write ? (node->mn_flags & (MNODE_F_PREAD | MNODE_F_PWRITE)) !=
		                     /*            */ (MNODE_F_PREAD | MNODE_F_PWRITE)
		                  : (node->mn_flags & MNODE_F_PREAD) == 0) {
			uintptr_t context;
			mman_lock_endread(effective_mm);
			/* Unmapped address! */
			context = E_SEGFAULT_CONTEXT_USERCODE;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			if unlikely(!self->rm_chkuser)
				context &= ~E_SEGFAULT_CONTEXT_USERCODE;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			if (write) {
				THROW(E_SEGFAULT_READONLY, addr,
				      E_SEGFAULT_CONTEXT_WRITING |
				      context);
			} else {
				THROW(E_SEGFAULT_NOTREADABLE, addr,
				      context);
			}
		}
		/* Figure out how many bytes we actually want to access from `node' */
		access_bytes = (size_t)((byte_t const *)mnode_getendaddr(node) -
		                        (byte_t const *)addr);
		if (access_bytes > num_bytes)
			access_bytes = num_bytes;
		/* Check for some additional region with which the  given
		 * address range may overlap at some later point in time.
		 * HINT: `i'  is  still left  initialized by  the `BSEARCH_RANGE()'
		 *       above, and currently points at where the region for `addr'
		 *       would have been (if it  existed), or at the region  before
		 *       that index. */
		if (i >= self->rm_regionc) {
			assertf(i == 0,
			        "i                = %" PRIuSIZ "\n"
			        "self->rm_regionc = %" PRIuSIZ "\n",
			        i, self->rm_regionc);
		} else {
			struct rtm_memory_region *next_region;
			next_region = self->rm_regionv[i];
			if (next_region->mr_addrhi < addr) {
				/* `i' points before the should-be index. */
				++i;
				/* And now `i' points at the should-be index. */
				if (i < self->rm_regionc) {
#ifndef NDEBUG
					next_region = self->rm_regionv[i];
#endif /* !NDEBUG */
					goto verify_access_range;
				}
			} else {
				size_t distance_to_next_region;
verify_access_range:
				assertf(next_region->mr_addrlo > addr,
				        "addr                   = %p\n"
				        "next_region->mr_addrlo = %p\n"
				        "next_region->mr_addrhi = %p\n",
				        addr,
				        next_region->mr_addrlo,
				        next_region->mr_addrhi);
				distance_to_next_region = (size_t)((byte_t *)next_region->mr_addrlo -
				                                   (byte_t *)addr);
				if (access_bytes > distance_to_next_region)
					access_bytes = distance_to_next_region;
			}
		}
		/* Access  permissions have been  confirmed, and we  now know that we're
		 * really dealing with a proper memory mapping that is able to represent
		 * actual memory. (rather than some other kind of mapping)
		 *
		 * At this point, we must check for some other RTM region that way already
		 * exist for `part',  since the RTM  region list may  only ever contain  a
		 * single  region for any given mpart, and  because every data part can be
		 * mapped an arbitrary number  of times within a  single MMan, we have  to
		 * make sure that no other region already describes this one! */
		for (j = 0; j < self->rm_regionc; ++j) {
			struct mnode *aliasing_node;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			struct mman *aliasing_node_mm;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			size_t access_offset_into_node;
			byte_t *aliasing_region_node_start;
			region = self->rm_regionv[j];
			if likely(rtm_memory_region_getpart(region) != part)
				continue;
			/* Welp... There's an overlap with this region's mpart. */
			assert((byte_t *)region->mr_addrhi < (byte_t *)addr ||
			       (byte_t *)region->mr_addrlo > (byte_t *)addr + access_bytes - 1);
#ifdef CONFIG_MODRTM_FAR_REGIONS
			/* In order to properly deal with far regions, we must select the region
			 * that is closest to the accessed address range, so we may then  either
			 * extend it, or create yet another far region.
			 * Right now, `j' points at the first `region' apart of a  variable-sized
			 * far region range, so if `addr' is greater than its end, we should look
			 * forward for a closer region. */
			if (addr > region->mr_addrhi) {
				for (;;) {
					size_t next_j;
					size_t distance_to_prev;
					size_t distance_to_next;
					struct rtm_memory_region *next_region;
					next_j = j + 1;
					if (next_j >= self->rm_regionc)
						break;
					next_region = self->rm_regionv[next_j];
					if (rtm_memory_region_getpart(next_region) != part)
						break; /* Not one of ours. */
					if (addr > next_region->mr_addrhi) {
						/* Access is still located above this region! */
						region = next_region;
						j      = next_j;
						continue;
					}
					/* The access happens between `region' and `next_region' */
					assert((byte_t *)region->mr_addrhi < (byte_t *)addr);
					assert((byte_t *)next_region->mr_addrlo > (byte_t *)addr + access_bytes - 1);
					/* Figure out which one of `region' and `next_region' is closer
					 * to the  address  range  that  is  actually  being  accessed. */
					distance_to_prev = (size_t)((byte_t *)addr - ((byte_t *)region->mr_addrhi + 1));
					distance_to_next = (size_t)((byte_t *)next_region->mr_addrlo - ((byte_t *)addr + access_bytes));
					if (distance_to_next < distance_to_prev) {
						/* Use `next_region' instead! */
						region = next_region;
						j      = next_j;
					}
					break;
				}
			}
#endif /* CONFIG_MODRTM_FAR_REGIONS */
			/* Check  if this region  is mapped by the  same mnode. -  If it is, then
			 * we have to extend this region to also contain `addr...+=access_bytes'.
			 * Otherwise,  we  have to  perform an  address  translation so  that the
			 * access  instead happens for  this region's mapping.  (At least we know
			 * that if  the  data  parts  are  identical,  then  both  of  the  mnode
			 * mappings  will  have identical  sizes, since  the size  of a  mnode is
			 * always identical to the size of an associated mpart!) */
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			aliasing_node_mm = &mman_kernel;
			if (ADDR_ISUSER(region->mr_addrlo))
				aliasing_node_mm = THIS_MMAN;
			if likely(aliasing_node_mm == effective_mm)
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			{
				aliasing_node = mman_mappings_locate(effective_mm, region->mr_addrlo);
				if (aliasing_node == node) {
					size_t old_region_size;
					mman_lock_endread(effective_mm);
					/* Extend node to encompass `addr...+=access_bytes' */
					old_region_size = rtm_memory_region_getsize(region);
					if (addr < region->mr_addrlo) {
						/* Extend downwards */
						size_t missing_bytes;
						missing_bytes = (size_t)((byte_t *)region->mr_addrlo - (byte_t *)addr);
						assert(missing_bytes);
#ifdef CONFIG_MODRTM_FAR_REGIONS
						/* Check if we should create a far region instead of extending an existing region. */
						if ((byte_t *)addr + access_bytes < (byte_t *)region->mr_addrlo) {
							size_t filler_bytes;
							filler_bytes = (size_t)((byte_t *)region->mr_addrlo - ((byte_t *)addr + access_bytes));
							if (filler_bytes >= CONFIG_MODRTM_FAR_REGION_CREATION_THRESHOLD) {
								/* Create a new far region. */
do_create_far_region:
								i = j; /* Index may later be needed by `rtm_memory_mark_region_as_changed()' */
								region = rtm_memory_create_far_region(self, j,
								                                      (byte_t *)addr,
								                                      (byte_t *)addr + access_bytes - 1,
								                                      effective_mm, part,
								                                      region->mr_vers);
								goto do_access_region;
							}
						}
#endif /* CONFIG_MODRTM_FAR_REGIONS */
						region = rtm_memory_realloc_region(self, region,
						                                   old_region_size +
						                                   missing_bytes);
						/* Shift region data to account of newly allocated space. */
						memmoveup(region->mr_data + missing_bytes,
						          region->mr_data, old_region_size);
						region->mr_addrlo = (byte_t *)region->mr_addrlo - missing_bytes;
						self->rm_regionv[j] = region; /* Inherit */
						assert_rtm_memory_region(region);
						/* Fill in the missing area. */
						TRY {
							rtm_memcpy_prefault(effective_mm,
							                    region->mr_data,
							                    region->mr_addrlo,
							                    missing_bytes);
						} EXCEPT {
							/* Failed to load region data.
							 * -> Since we're extending downwards, `region' now contains a hole  of
							 *    uninitialized data. But since RTM regions must be continuous, the
							 *    only thing we can do to recover is discard everything we're  just
							 *    did to extend `region' and try again from the start... */
							memmovedown(region->mr_data,
							            region->mr_data + missing_bytes,
							            old_region_size);
							region->mr_addrlo = (byte_t *)region->mr_addrlo + missing_bytes;
							RETHROW();
						}
						assert((byte_t *)addr == (byte_t *)region->mr_addrlo);
#if defined(CONFIG_MODRTM_FAR_REGIONS) && defined(CONFIG_MODRTM_FAR_REGION_REMERGE)
						/* With far regions, check for the case where we've run into another region. */
						if (j > 0) {
							struct rtm_memory_region *lower_region;
							lower_region = self->rm_regionv[j - 1];
							if (rtm_memory_region_getpart(lower_region) == part &&
							    (byte_t *)lower_region->mr_addrhi + 1 == (byte_t *)region->mr_addrlo &&
							    (rtm_memory_region_waschanged(lower_region) ==
							     (write || rtm_memory_region_waschanged(region)))) {
								/* Yes! Do try to merge these two regions. */
								if (rtm_memory_try_merge_regions(self, j - 1, lower_region, region))
									goto again;
								region = self->rm_regionv[j];
							}
						}
#endif /* CONFIG_MODRTM_FAR_REGIONS && CONFIG_MODRTM_FAR_REGION_REMERGE */
					} else {
						/* Extend upwards */
						size_t missing_bytes;
						USER byte_t *missing_addr_start;
						assertf((byte_t *)addr + access_bytes - 1 > region->mr_addrhi,
						        "addr + .... - 1    = %p\n"
						        "region->mr_addrhi  = %p\n",
						        (byte_t *)addr + access_bytes - 1,
						        region->mr_addrhi);
						missing_bytes = (size_t)(((byte_t *)addr + access_bytes) -
						                         ((byte_t *)region->mr_addrhi + 1));
						assert(missing_bytes);
#ifdef CONFIG_MODRTM_FAR_REGIONS
						/* Check if we should create a far region instead of extending an existing region. */
						if (addr > region->mr_addrhi) {
							size_t filler_bytes;
							filler_bytes = (size_t)((byte_t *)addr - ((byte_t *)region->mr_addrhi + 1));
							if (filler_bytes >= CONFIG_MODRTM_FAR_REGION_CREATION_THRESHOLD) {
								/* Create a new far region. */
								++j; /* Insert above `region' */
								goto do_create_far_region;
							}
						}
#endif /* CONFIG_MODRTM_FAR_REGIONS */
						region = rtm_memory_realloc_region(self, region,
						                                   old_region_size +
						                                   missing_bytes);
						missing_addr_start = (USER byte_t *)region->mr_addrhi + 1;
						region->mr_addrhi  = (byte_t *)region->mr_addrhi + missing_bytes;
						assert((byte_t *)region->mr_addrhi ==
						       (byte_t *)region->mr_addrlo + old_region_size + missing_bytes - 1);
						self->rm_regionv[j] = region; /* Inherit */
						assert_rtm_memory_region(region);
						/* Fill in the missing area. */
						TRY {
							rtm_memcpy_prefault(effective_mm,
							                    region->mr_data + old_region_size,
							                    missing_addr_start,
							                    missing_bytes);
						} EXCEPT {
							/* Re-truncate the region so we can at least
							 * account for what  we were  able to  copy! */
							region->mr_addrhi = (byte_t *)region->mr_addrhi - missing_bytes;
							RETHROW();
						}
						assert((byte_t *)addr + access_bytes - 1 == (byte_t *)region->mr_addrhi);
#if defined(CONFIG_MODRTM_FAR_REGIONS) && defined(CONFIG_MODRTM_FAR_REGION_REMERGE)
						/* With far regions, check for the case where we've run into another region. */
						if ((j + 1) < self->rm_regionc) {
							struct rtm_memory_region *upper_region;
							upper_region = self->rm_regionv[j + 1];
							if (rtm_memory_region_getpart(upper_region) == part &&
							    (byte_t *)region->mr_addrhi + 1 == (byte_t *)upper_region->mr_addrlo &&
							    (rtm_memory_region_waschanged(upper_region) ==
							     (write || rtm_memory_region_waschanged(region)))) {
								/* Yes! Do try to merge these two regions. */
								rtm_memory_try_merge_regions(self, j, region, upper_region);
								region = self->rm_regionv[j];
							}
						}

#endif /* CONFIG_MODRTM_FAR_REGIONS && CONFIG_MODRTM_FAR_REGION_REMERGE */
					}
#ifdef CONFIG_MODRTM_FAR_REGIONS
					/* Far region set-modified code requires that `self->rm_regionv[i] == region' */
					i = j;
#endif /* CONFIG_MODRTM_FAR_REGIONS */
					goto do_access_region;
				}
			}
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			else {
				if unlikely(!mman_lock_tryread(aliasing_node_mm)) {
					mman_lock_endread(effective_mm);
					mman_lock_waitread(aliasing_node_mm);
					goto again_lock_effective_mman;
				}
				aliasing_node = mman_mappings_locate(effective_mm, region->mr_addrlo);
			}
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			assert(aliasing_node != node);
			/* Figure out access offsets so we can translate `addr' */
			access_offset_into_node    = (size_t)((byte_t *)addr - (byte_t *)mnode_getendaddr(node));
			aliasing_region_node_start = (byte_t *)mnode_getendaddr(aliasing_node);
			RTM_DEBUG("[rtm] Region redirect: data from %p...%p is already mapped at %p...%p (map %p -> %p)\n",
			          mnode_getminaddr(node), mnode_getmaxaddr(node),
			          mnode_getminaddr(aliasing_node), mnode_getmaxaddr(aliasing_node),
			          addr, aliasing_region_node_start + access_offset_into_node);
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			if unlikely(aliasing_node_mm != effective_mm)
				mman_lock_endread(aliasing_node_mm);
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			mman_lock_endread(effective_mm);
			/* Calculate the translated address for the aliasing mapping, and try again. */
			addr = aliasing_region_node_start +
			       access_offset_into_node;
			goto again;
		}
		incref(part); /* To-be inherited by the new RTM region. */
		mman_lock_endread(effective_mm);
		/* Create a new RTM region. */
		TRY {
			region = (struct rtm_memory_region *)rtm_memory_malloc(self,
			                                                       offsetof(struct rtm_memory_region, mr_data) +
			                                                       access_bytes);
		} EXCEPT {
			decref(part);
			RETHROW();
		}
		region->mr_addrlo = (byte_t *)addr;
		region->mr_addrhi = (byte_t *)addr + access_bytes - 1;
		region->mr_part   = part; /* Inherit reference */
		region->mr_vers = 0;
		if (ATOMIC_READ(part->mp_meta) != NULL) {
			/* Check for non-zero version counter. */
			struct mpartmeta *ftx;
			TRY {
				mpart_lock_acquire(part);
			} EXCEPT {
				rtm_memory_free(self, region);
				decref(part);
				RETHROW();
			}
			ftx = ATOMIC_READ(part->mp_meta);
			if likely(ftx != NULL)
				region->mr_vers = ftx->mpm_rtm_vers;
			mpart_lock_release(part);
		}
		/* Insert `region' into the vector at index `i' */
		rtm_memory_insert_region(self, i, region); /* Inherit: region */
		/* Populate the accessed `region' with data from the MMan
		 * NOTE: We use `memcpy_nopf()' for this to  ensure that the current memory  state
		 *       remains consistent with what was set-up by the `mman_forcefault()' above. */
		{
			size_t copy_error;
			copy_error = memcpy_nopf(region->mr_data,
			                         addr,
			                         access_bytes);
			if unlikely(copy_error != 0) {
				/* The last `copy_error' bytes could not be copied... */
				size_t copy_ok;
				assert(copy_error <= access_bytes);
				copy_ok = access_bytes - copy_error;
				if (!copy_ok) {
					/* Nothing was copied (remove `region' from the vector) */
					--self->rm_regionc;
					memmovedownc(&self->rm_regionv[i],
					             &self->rm_regionv[i + 1],
					             self->rm_regionc - i,
					             sizeof(struct rtm_memory_region *));
					rtm_memory_free(self, region);
					decref(part);
				} else {
					/* At  least ~something~ was copied (Update `region' to
					 * only contain the portion that was _actually_ copied) */
					region->mr_addrhi = (byte_t *)addr + copy_ok - 1;
				}
				goto again;
			}
		}
do_access_region:
		assert_rtm_memory_region(region);
		assertf((byte_t *)addr >= (byte_t *)region->mr_addrlo &&
		        (byte_t *)addr + access_bytes - 1 <= (byte_t *)region->mr_addrhi,
		        "access: %p...%p\n"
		        "region: %p...%p\n",
		        (byte_t *)addr, (byte_t *)addr + access_bytes - 1,
		        region->mr_addrlo, region->mr_addrhi);
		{
			byte_t *rdat;
			rdat = region->mr_data + (size_t)((byte_t *)addr -
			                                  (byte_t *)region->mr_addrlo);
			/* Copy accessed data. */
			if (write) {
				memcpy(rdat, buf, access_bytes);
				rtm_memory_mark_region_as_changed(self, i, region);
			} else {
				memcpy(buf, rdat, access_bytes);
			}
		}
		/* Check if we're done, and if we aren't, continue
		 * reading  after  what  has  already  been  read. */
		if (access_bytes >= num_bytes)
			return;
		addr = (byte_t *)addr + access_bytes;
		buf  = (byte_t *)buf + access_bytes;
		num_bytes -= access_bytes;
		goto again;
	}
}

/* Read RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTERN NONNULL((1, 3)) void FCALL
rtm_memory_read(struct rtm_memory *__restrict self, USER void const *addr,
                void *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	rtm_memory_readwrite(self,
	                     (USER void *)addr,
	                     buf,
	                     num_bytes,
	                     false);
}

/* Write RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTERN NONNULL((1, 3)) void FCALL
rtm_memory_write(struct rtm_memory *__restrict self, USER void *addr,
                 void const *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	rtm_memory_readwrite(self,
	                     addr,
	                     (void *)buf,
	                     num_bytes,
	                     true);
}







PRIVATE void FCALL
prefault_memory_for_writing(struct mman *__restrict mymm,
                            USER void *addr, size_t num_bytes) {
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
	mman_forcefault(ADDR_ISKERN(addr) ? &mman_kernel
	                                  : mymm,
	                addr, num_bytes,
	                MMAN_FAULT_F_WRITE |
	                MMAN_FAULT_F_NOVIO);
#else /* !CONFIG_MODRTM_USERSPACE_ONLY */
	mman_forcefault(mymm, addr, num_bytes,
	                MMAN_FAULT_F_WRITE |
	                MMAN_FAULT_F_NOVIO);
#endif /* CONFIG_MODRTM_USERSPACE_ONLY */
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_endwrite_modified_parts)(struct rtm_memory const *__restrict self,
                                                  size_t i) {
	while (i) {
		struct rtm_memory_region *region;
		--i;
		region = self->rm_regionv[i];
		if (rtm_memory_region_waschanged_and_no_farregion(region))
			mpart_lock_release(rtm_memory_region_getpart(region));
	}
}


/* Verify that the given address range is writable
 * without  any   chance  of   triggering  a   #PF */
PRIVATE NOBLOCK ATTR_PURE NONNULL((1)) bool
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
	/* TODO: This function needs a re-write in order to make use of `mpm_dmalocks'
	 *       when writing to mem-parts, rather than keeping ahold of the much  too
	 *       powerful `MPART_F_LOCKBIT' in order to accomplish the same! */

#ifdef CONFIG_MODRTM_USERSPACE_ONLY
#define effective_mm mymm
#endif /* CONFIG_MODRTM_USERSPACE_ONLY */
	struct mman *mymm;
	size_t i;
	bool must_allocate_missing_futex_controllers;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
	bool has_modified_kern;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
	bool has_modified_user;
	mymm  = THIS_MMAN;
again_forcefault:
	/* Step #1: prefault the address ranges of all modified regions. */
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		region = self->rm_regionv[i];
		assert(region);
		if (!rtm_memory_region_waschanged(region))
			continue; /* Not modified... */
		/* Prefault memory. */
		prefault_memory_for_writing(mymm, region->mr_addrlo,
		                            rtm_memory_region_getsize(region));
	}

	/* Step #2: Acquire tx-locks to all of the modified data parts, and
	 *          verify that accessed  data parts  are still  up-to-date */
again_acquire_region_locks:
	must_allocate_missing_futex_controllers = false;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		struct mpart *part;
		region = self->rm_regionv[i];
		part   = rtm_memory_region_getpart(region);
		{
			struct mnode *node;
			size_t node_size_after_addr;
			byte_t *region_start_addr;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			struct mman *effective_mm = mymm;
			if unlikely(ADDR_ISKERN(region->mr_addrlo))
				effective_mm = &mman_kernel;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			region_start_addr = (byte_t *)region->mr_addrlo;
			if unlikely(!mman_lock_tryread(effective_mm)) {
				rtm_memory_endwrite_modified_parts(self, i);
				mman_lock_waitread(effective_mm);
				goto again_acquire_region_locks;
			}
			node = mman_mappings_locate(mymm, region_start_addr);
			if unlikely(!node || node->mn_part != part) {
				mman_lock_endread(effective_mm);
				goto partially_release_locks_and_retry;
			}
			/* Make sure that the node has sufficient memory after `region->mr_addrlo'
			 * to  account   for  at   least   `region->mr_size'  bytes   of   memory. */
			node_size_after_addr = (size_t)mnode_getendaddr(node);
			mman_lock_endread(effective_mm);
			node_size_after_addr -= (uintptr_t)region_start_addr;
			node_size_after_addr += PAGESIZE - ((uintptr_t)region->mr_addrlo & PAGEMASK);
			if unlikely(rtm_memory_region_getsize(region) > node_size_after_addr)
				goto partially_release_locks_and_retry;
		}
#ifdef CONFIG_MODRTM_FAR_REGIONS
		if (rtm_memory_region_isfarregion(region)) {
			/* Far regions are checked implicitly through an adjacent base region. */
		} else
#endif /* CONFIG_MODRTM_FAR_REGIONS */
		if (rtm_memory_region_waschanged(region)) {
			struct mpartmeta *fxc;
			if (!mpart_lock_tryacquire(part)) {
				rtm_memory_endwrite_modified_parts(self, i);
				/* Wait until the lock becomes available. - _then_ try acquiring locks again */
				mpart_lock_waitfor(part);
				goto again_acquire_region_locks;
			}
			/* Verify that the version of this region did not change */
			fxc = part->mp_meta;
			if (fxc) {
				if (fxc->mpm_rtm_vers != region->mr_vers) {
endwrite_par_and_release_locks_and_retry:
					mpart_lock_release(part);
					goto partially_release_locks_and_retry;
				}
			} else {
				if (region->mr_vers != 0)
					goto endwrite_par_and_release_locks_and_retry;
				/* We need to allocate this missing futex controller down below */
				must_allocate_missing_futex_controllers = true;
			}
		} else {
			if unlikely(!mpart_lock_tryacquire(part)) {
				rtm_memory_endwrite_modified_parts(self, i);
				/* Wait until the lock becomes available. - _then_ try acquiring locks again */
				mpart_lock_waitfor(part);
				goto again_acquire_region_locks;
			}
			/* Verify that the version of this region did not change */
			if (mpart_get_rtm_version(part) != region->mr_vers) {
				mpart_lock_release(part);
				goto partially_release_locks_and_retry;
			}
			mpart_lock_release(part);
		}
	}
	if (must_allocate_missing_futex_controllers) {
		/* Allocate missing futex controllers. */
		for (i = 0; i < self->rm_regionc; ++i) {
			struct rtm_memory_region *region;
			struct mpart *part;
			struct mpartmeta *ftx;
			region = self->rm_regionv[i];
			if (!rtm_memory_region_waschanged_and_no_farregion(region))
				continue;
			part = rtm_memory_region_getpart(region);
			ftx  = part->mp_meta;
			if (ftx)
				continue; /* Already allocated. */
			/* Must allocate the missing controller.
			 * Note that we're holding  a couple of non-recursive  locks
			 * at the moment, so we must be careful not to do a blocking
			 * memory allocation! */
			ftx = (struct mpartmeta *)kmalloc_nx(sizeof(struct mpartmeta), GFP_ATOMIC | GFP_CALLOC);
			if unlikely(!ftx) {
				/* The difficult case:
				 * In this case, we must release all of our beautiful locks, :(
				 * just  so  we can  do a  blocking  heap allocation.  And once
				 * that's done  we'll have  to start  over with  acquiring  all
				 * of the necessary locks... */
				rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
#ifndef __OPTIMIZE_SIZE__
again_allocate_ftx_controller_for_part:
#endif /* !__OPTIMIZE_SIZE__ */
				ftx = (struct mpartmeta *)kmalloc(sizeof(struct mpartmeta), GFP_CALLOC);
				/* Try to install `ftx' into `part' */
				TRY {
					mpart_lock_acquire(part);
				} EXCEPT {
					kfree(ftx);
					RETHROW();
				}
				if likely(!part->mp_meta) {
					/* Install the new controller. */
					part->mp_meta = ftx;
					mpart_lock_release(part);
				} else {
					/* Race condition: Someone else already installed a controller. */
					mpart_lock_release(part);
					kfree(ftx);
				}
#ifndef __OPTIMIZE_SIZE__
				/* While we're at it, also try  to look head if there  are
				 * more modified regions with parts that are lacking their
				 * futex controllers. Because if  there are more, then  we
				 * can just fill in their controllers all at once, without
				 * having to fill them in one-at-a-time. */
				for (++i; i < self->rm_regionc; ++i) {
					region = self->rm_regionv[i];
					if (!rtm_memory_region_waschanged_and_no_farregion(region))
						continue; /* Not needed */
					part = rtm_memory_region_getpart(region);
					if (ATOMIC_READ(part->mp_meta))
						continue; /* Already allocated */
					/* Allocate another controller for this one! */
					goto again_allocate_ftx_controller_for_part;
				}
#endif /* !__OPTIMIZE_SIZE__ */
				goto again_acquire_region_locks;
			}
			part->mp_meta = ftx;
		}
	}

	/* Step #3: Verify that all  modified in-memory data  ranges can  be
	 *          written to without any chance of triggering a pagefault. */
	has_modified_user = false;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
	has_modified_kern = false;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		struct mpart *part;
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
		struct mman *effective_mm;
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
		region = self->rm_regionv[i];
		if (!rtm_memory_region_waschanged(region))
			continue; /* Unchanged region. */
		part = rtm_memory_region_getpart(region);
		assert(mpart_lock_acquired(part));
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
		effective_mm = mymm;
		if unlikely(ADDR_ISKERN(region->mr_addrlo))
			effective_mm = &mman_kernel;
		if unlikely(effective_mm == &mman_kernel) {
			/* Ensure that we've for a read-lock to the kernel's MMan */
			if (!has_modified_kern) {
				if unlikely(!mman_lock_tryread(&mman_kernel))
					goto again_acquire_region_locks_for_mman_lock;
				has_modified_kern = true;
			}
		} else
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
		{
			/* Ensure that we've for a read-lock to the user's MMan */
			if (!has_modified_user) {
				if unlikely(!mman_lock_tryread(effective_mm)) {
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
again_acquire_region_locks_for_mman_lock:
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
					rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
					mman_lock_waitread(effective_mm);
					goto again_acquire_region_locks;
				}
				has_modified_user = true;
			}
		}
		/* Verify that the backing memory of the accessed range is still writable.
		 * This  was originally asserted by `prefault_memory_for_writing()' above,
		 * which we'd have to jump back to if memory isn't writable any more. */
		if unlikely(!rtm_verify_writable_nopf(region->mr_addrlo,
		                                      rtm_memory_region_getsize(region))) {
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
			if unlikely(has_modified_kern)
				mman_lock_endread(&mman_kernel);
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
			if (has_modified_user)
				mman_lock_endread(mymm);
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
		struct mpart *part;
		--i;
		region = self->rm_regionv[i];
		if (!rtm_memory_region_waschanged(region))
			continue; /* Unchanged region. */
		part = rtm_memory_region_getpart(region);
		assertf(mpart_lock_acquired(part),
		        "No lock held for part %p (used by region %p...%p)",
		        part, region->mr_addrlo, region->mr_addrhi);
		/* Copy modified memory.
		 * NOTE: We've  verified that all  of this memory  can be written without
		 *       causing a pagefault in step #3, and we know that the  associated
		 *       mappings won't have changed in the mean time because we're still
		 *       holding locks to their corresponding MMans! */
#ifdef NDEBUG
		memcpy(region->mr_addrlo,
		       region->mr_data,
		       rtm_memory_region_getsize(region));
#else /* NDEBUG */
		{
			size_t error;
			error = memcpy_nopf(region->mr_addrlo,
			                    region->mr_data,
			                    rtm_memory_region_getsize(region));
			assertf(error == 0,
			        "But we're asserted that all of this should be writable...\n"
			        "region->mr_addrlo = %p\n"
			        "region->mr_addrhi = %p\n"
			        "region->mr_data   = %p\n"
			        "SIZE(region)      = %" PRIuSIZ "\n"
			        "error             = %" PRIuSIZ "\n",
			        region->mr_addrlo,
			        region->mr_addrhi,
			        region->mr_data,
			        rtm_memory_region_getsize(region),
			        error);
		}
#endif /* !NDEBUG */
		/* Increment the RTM version counter of this part. */
		assert(part->mp_meta);
#ifdef CONFIG_MODRTM_FAR_REGIONS
		/* Only increase the version counter if this isn't an aliasing far region! */
		if (!rtm_memory_region_isfarregion(region))
#endif /* CONFIG_MODRTM_FAR_REGIONS */
		{
			++part->mp_meta->mpm_rtm_vers;
		}
		COMPILER_BARRIER();
		/* Release our lock to this part. */
#ifndef CONFIG_MODRTM_FAR_REGIONS
		mpart_lock_release(part);
#endif /* !CONFIG_MODRTM_FAR_REGIONS */
	}
#ifdef CONFIG_MODRTM_FAR_REGIONS
	/* With far regions, we must release mpart locks during a second
	 * pass,  as far  regions may  re-use locks  of adjacent mparts! */
	i = self->rm_regionc;
	while (i) {
		struct rtm_memory_region *region;
		struct mpart *part;
		--i;
		region = self->rm_regionv[i];
		if (!rtm_memory_region_waschanged_and_no_farregion(region))
			continue; /* Unchanged region. */
		part = rtm_memory_region_getpart(region);
		assertf(mpart_lock_acquired(part),
		        "No lock held for part %p (used by region %p...%p)",
		        part, region->mr_addrlo, region->mr_addrhi);
		mpart_lock_release(part);
	}
#endif /* CONFIG_MODRTM_FAR_REGIONS */

#ifndef CONFIG_MODRTM_USERSPACE_ONLY
	if unlikely(has_modified_kern)
		mman_lock_endread(&mman_kernel);
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
	if (has_modified_user)
		mman_lock_endread(mymm);
#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
	rtm_memory_exec_pending_syscalls(self);
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */
	return true;
partially_release_locks_and_retry:
	rtm_memory_endwrite_modified_parts(self, i);
	return false;
#ifdef CONFIG_MODRTM_USERSPACE_ONLY
#undef effective_mm
#endif /* CONFIG_MODRTM_USERSPACE_ONLY */
}


DECL_END

#endif /* !GUARD_MODRTM_MEMORY_C */
