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
#ifndef GUARD_KERNEL_SRC_MEMORY_MEMINFO_C
#define GUARD_KERNEL_SRC_MEMORY_MEMINFO_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/memory.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libjson/generator.h>
#include <libjson/parser.h>

DECL_BEGIN


#define PAGES_PER_WORD  (BITS_PER_POINTER / PMEMZONE_BITSPERPAGE)

/* Mask of bits that are tested to determine if a page is free. */
#if PMEMZONE_ISFREEBIT == 0
#if __SIZEOF_POINTER__ == 4
#define PMEMBITSET_FREEMASK   __UINTPTR_C(0x55555555)
#else
#define PMEMBITSET_FREEMASK   __UINTPTR_C(0x5555555555555555)
#endif
#else
#if __SIZEOF_POINTER__ == 4
#define PMEMBITSET_FREEMASK   __UINTPTR_C(0xAAAAAAAA)
#else
#define PMEMBITSET_FREEMASK   __UINTPTR_C(0xAAAAAAAAAAAAAAAA)
#endif
#endif
#define PMEMBITSET_UNDFMASK   (~PMEMBITSET_FREEMASK)
STATIC_ASSERT_MSG(PMEMZONE_BITSPERPAGE == 2,"Must re-do the logic above");
STATIC_ASSERT((BITSOF(uintptr_t) % PMEMZONE_BITSPERPAGE) == 0);


PRIVATE ATTR_FREERODATA struct pmemzone const empty_mzone = {
	.mz_prev  = NULL,
	.mz_next  = NULL,
	.mz_start = 0,
	.mz_max   = 0,
	.mz_rmax  = 0,
	.mz_fmax  = 0,
	.mz_cfree = 0,
	.mz_qfree = 0,
	.mz_zero  = 0,
	.mz_free  = { 0, 0 },
};
PRIVATE ATTR_FREERODATA struct pmemzone const *const empty_mzone_vec[] = {
	[0] = &empty_mzone
};

PUBLIC ATTR_SECTION(".data.hot") struct pmem mzones = {
	.pm_zonec = COMPILER_LENOF(empty_mzone_vec),
	.pm_last  = (struct pmemzone *)&empty_mzone,
	.pm_zones = (struct pmemzone *const *)&empty_mzone_vec[0]
};

PUBLIC_CONST char const pmembank_type_names[PMEMBANK_TYPE_COUNT][16] = {
	/* [PMEMBANK_TYPE_UNDEF]     = */"undefined",
	/* [PMEMBANK_TYPE_RAM]       = */"ram",
	/* [PMEMBANK_TYPE_PRESERVE]  = */"preserve",
	/* [PMEMBANK_TYPE_ALLOCATED] = */"allocated",
	/* [PMEMBANK_TYPE_KFREE]     = */"kernel_free",
	/* [PMEMBANK_TYPE_KERNEL]    = */"kernel",
	/* [PMEMBANK_TYPE_NVS]       = */"nvs",
	/* [PMEMBANK_TYPE_DEVICE]    = */"device",
	/* [PMEMBANK_TYPE_BADRAM]    = */"badram",
};


INTDEF struct pmembank kernel_membanks_initial[];

LOCAL ATTR_FREETEXT void
NOTHROW(KCALL minfo_split_bank)(size_t bank_index, vm_phys_t start) {
	assertf(bank_index < minfo.mb_bankc,
	        "bank_index     = %Iu\n"
	        "minfo.mb_bankc = %Iu\n",
	        bank_index, minfo.mb_bankc);
	assertf(start > PMEMBANK_TYPE_START(kernel_membanks_initial[bank_index]),
	        "bank_index                                               = %Iu\n"
	        "start                                                    = " FORMAT_VM_PHYS_T "\n"
	        "PMEMBANK_TYPE_START(kernel_membanks_initial[bank_index]) = " FORMAT_VM_PHYS_T "\n"
	        "PMEMBANK_TYPE_MAX(kernel_membanks_initial[bank_index])   = " FORMAT_VM_PHYS_T "\n",
	        bank_index, start,
	        PMEMBANK_TYPE_START(kernel_membanks_initial[bank_index]),
	        PMEMBANK_TYPE_MAX(kernel_membanks_initial[bank_index]));
	assertf(start <= PMEMBANK_TYPE_MAX(kernel_membanks_initial[bank_index]),
	        "bank_index                                               = %Iu\n"
	        "start                                                    = " FORMAT_VM_PHYS_T "\n"
	        "PMEMBANK_TYPE_START(kernel_membanks_initial[bank_index]) = " FORMAT_VM_PHYS_T "\n"
	        "PMEMBANK_TYPE_MAX(kernel_membanks_initial[bank_index])   = " FORMAT_VM_PHYS_T "\n",
	        bank_index, start,
	        PMEMBANK_TYPE_START(kernel_membanks_initial[bank_index]),
	        PMEMBANK_TYPE_MAX(kernel_membanks_initial[bank_index]));
	memmove(&kernel_membanks_initial[bank_index + 1],
	        &kernel_membanks_initial[bank_index],
	        (minfo.mb_bankc - bank_index) *
	        sizeof(struct pmembank));
	kernel_membanks_initial[bank_index + 1].mb_start = start;
	++minfo.mb_bankc;
	kernel_membanks_initial[minfo.mb_bankc].mb_start = 0;
}

LOCAL ATTR_FREETEXT void
NOTHROW(KCALL minfo_delete_bank)(size_t bank_index) {
	--minfo.mb_bankc;
	memmove(&kernel_membanks_initial[bank_index],
	        &kernel_membanks_initial[bank_index + 1],
	        (minfo.mb_bankc - bank_index) *
	        sizeof(struct pmembank));
	kernel_membanks_initial[minfo.mb_bankc].mb_start = 0;
}

/* Returns the total number of usable pages of RAM */
INTERN ATTR_FREETEXT size_t
NOTHROW(KCALL minfo_usable_ram_pages)(void) {
	size_t result = 0, i;
	for (i = 0; i < minfo.mb_bankc; ++i) {
		if (minfo.mb_banks[i].mb_type == PMEMBANK_TYPE_RAM)
			result += PMEMBANK_TYPE_NUMPAGES(minfo.mb_banks[i]);
	}
	return result;
}

/* Add information about a new member bank / region. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL minfo_addbank)(vm_phys_t start, vm_phys_t size, u16 type) {
	vm_phys_t max;
	size_t i;
	assert(minfo.mb_banks == kernel_membanks_initial);
	assert(type < PMEMBANK_TYPE_COUNT);
	if (!size)
		return;
	if (OVERFLOW_UADD(start, size - 1, &max))
		max = (vm_phys_t)-1;
	printk(FREESTR(KERN_INFO "Adding memory bank at " FORMAT_VM_PHYS_T "..." FORMAT_VM_PHYS_T " (%s)\n"),
	       start, max, pmembank_type_names[type]);
	i = 0;
	while ((assert(i < minfo.mb_bankc),
	        start > PMEMBANK_TYPE_MAX(kernel_membanks_initial[i])))
		++i;
continue_type_checks:
	assert(start >= PMEMBANK_TYPE_MIN(kernel_membanks_initial[i]));
	assert(start <= PMEMBANK_TYPE_MAX(kernel_membanks_initial[i]));
	while (type <= kernel_membanks_initial[i].mb_type) {
		start = PMEMBANK_TYPE_END(kernel_membanks_initial[i]);
		if (start - 1 >= max)
			return;
		++i;
		assert(i < minfo.mb_bankc);
	}
	assert(type >= kernel_membanks_initial[i].mb_type);
	if (start != PMEMBANK_TYPE_MIN(kernel_membanks_initial[i])) {
		/* Must split the bank at this position. */
		minfo_split_bank(i, start);
		++i;
	}
	assert(start == PMEMBANK_TYPE_MIN(kernel_membanks_initial[i]));
	if (max <= PMEMBANK_TYPE_MAX(kernel_membanks_initial[i])) {
		if (max < PMEMBANK_TYPE_MAX(kernel_membanks_initial[i]))
			minfo_split_bank(i, max + 1);
		kernel_membanks_initial[i].mb_type = type;
		if (i != 0 && kernel_membanks_initial[i - 1].mb_type == type) {
			minfo_delete_bank(i);
			--i;
		}
		if (kernel_membanks_initial[i + 1].mb_type == type)
			minfo_delete_bank(i + 1);
	} else {
		kernel_membanks_initial[i].mb_type = type;
		if (i != 0 && kernel_membanks_initial[i - 1].mb_type == type) {
			minfo_delete_bank(i);
			--i;
		}
		assert(kernel_membanks_initial[i].mb_type == type);
		++i;
		start = PMEMBANK_TYPE_MIN(kernel_membanks_initial[i]);
		assert(start <= max);
		goto continue_type_checks;
	}
}



#define PMEMBANK_TYPE_SHOULD_ZONE(x) ((x) >= PMEMBANK_TYPE_RAM && (x) <= PMEMBANK_TYPE_KFREE)


PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL pmemzone_init_bit)(struct pmemzone *__restrict self,
                                  pageptr_t pageno, uintptr_t mask) {
	unsigned int j;
	size_t i;
	uintptr_t bitmask;
	i       = (size_t)(pageno / PAGES_PER_WORD);
	j       = (unsigned int)(pageno & (PAGES_PER_WORD - 1));
	bitmask = (uintptr_t)(PMEMZONE_ISFREEMASK | PMEMZONE_ISUNDFMASK) << (j * PMEMZONE_BITSPERPAGE);
	self->mz_free[i] &= ~bitmask;
	self->mz_free[i] |= (mask & bitmask);
}

PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL pmemzone_init_bits)(struct pmemzone *__restrict self,
                                  pageptr_t start, pagecnt_t num_pages,
                                  uintptr_t mask) {
#if 0
	printk(FREESTR(KERN_DEBUG "INIT: %I64p...%I64p as %Ix\n"),
	       (u64)VM_PPAGE2ADDR(start),
	       (u64)VM_PPAGE2ADDR(start + num_pages) - 1, mask);
#endif
	assert(start >= self->mz_start);
	assert(start + num_pages >= start);
	assertf(!num_pages || start + num_pages - 1 <= self->mz_max,
	        "start                 = " FORMAT_PAGEPTR_T "\n"
	        "num_pages             = " FORMAT_PAGEPTR_T "\n"
	        "start + num_pages - 1 = " FORMAT_PAGEPTR_T "\n"
	        "self->mz_max          = " FORMAT_PAGEPTR_T "\n",
	        start, num_pages, start + num_pages - 1, self->mz_max);
	start -= self->mz_start;
	while (start & (PAGES_PER_WORD - 1)) {
		if (!num_pages)
			return;
		pmemzone_init_bit(self, start, mask);
		++start;
		--num_pages;
	}
#if __SIZEOF_POINTER__ == 4
	memsetl(&self->mz_free[(uintptr_t)(start / PAGES_PER_WORD)],
	        mask, num_pages / PAGES_PER_WORD);
#else /* __SIZEOF_POINTER__ == 4 */
	memsetq(&self->mz_free[(uintptr_t)(start / PAGES_PER_WORD)],
	        mask, num_pages / PAGES_PER_WORD);
#endif /* __SIZEOF_POINTER__ != 4 */
	start += num_pages & ~(PAGES_PER_WORD - 1);
	num_pages %= PAGES_PER_WORD;
	while (num_pages) {
		pmemzone_init_bit(self, start, mask);
		++start;
		--num_pages;
	}
}


/* VM part/node for describing the page data structures */
INTDEF struct vm_datapart kernel_vm_part_pagedata;
INTDEF struct vm_node kernel_vm_node_pagedata;

#if defined(__i386__) || defined(__x86_64__)
INTDEF byte_t __kernel_start[];
#endif

PRIVATE ATTR_FREETEXT PHYS vm_ppage_t KCALL
minfo_allocate_part_pagedata(size_t num_bytes) {
	/* Q: Huh? Candy? What are you talking about
	 * A: Candy -> Candi -> Candidate */
	size_t i, candy_bank = (size_t)-1;
	vm_ppage_t candy        = (vm_ppage_t)-1;
	vm_ppage_t candy_weight = (vm_ppage_t)-1;
#if defined(__i386__) || defined(__x86_64__)
	bool allow_beneath_kernel = false;
again:
#endif
	assert(minfo.mb_banks == kernel_membanks_initial);
	for (i = 0; i < minfo.mb_bankc; ++i) {
		vm_phys_t bytes_avail;
		vm_ppage_t waste;
		vm_ppage_t bank_alloc_page;
		if (kernel_membanks_initial[i].mb_type != PMEMBANK_TYPE_RAM)
			continue; /* Not suitable for our purposes */
		bytes_avail = PMEMBANK_TYPE_SIZE(kernel_membanks_initial[i]);
		if unlikely(bytes_avail < (vm_phys_t)num_bytes)
			continue; /* Too small in general (even without alignment) */
		bank_alloc_page = (vm_ppage_t)((PMEMBANK_TYPE_END(kernel_membanks_initial[i]) - num_bytes) / PAGESIZE);
		if unlikely(bank_alloc_page < PMEMBANK_TYPE_STARTPAGE(kernel_membanks_initial[i]))
			continue; /* Too small with alignment */
#if defined(__i386__) || defined(__x86_64__)
		/* Try not to allocate beneath the kernel, so-as not to use up low memory,
		 * which is already in short supply, and which we'll still be needing for
		 * initialization of APIC/SMP trampoline code, or other real-mode/BIOS related
		 * stuff that can only exist below the physical 1MiB (16-bit 0xffff) mark. */
		if unlikely(bank_alloc_page <= (vm_ppage_t)VM_ADDR2PAGE((uintptr_t)__kernel_start - KERNEL_BASE) &&
		            !allow_beneath_kernel)
			continue;
#endif /* __i386__ || __x86_64__ */

#if __SIZEOF_VM_PHYS_T__ > __SIZEOF_POINTER__
		/* Make sure the allocation end doesn't exceed mapped physical memory. */
		if ((VM_PPAGE2ADDR(bank_alloc_page) + num_bytes - 1) >= (vm_phys_t)(uintptr_t)-1) {
			vm_phys_t bank_alloc_addr;
			bank_alloc_addr = (vm_phys_t)(uintptr_t)-1 - (num_bytes - 1);
			bank_alloc_addr &= ~(PAGESIZE - 1);
			if (bank_alloc_addr < PMEMBANK_TYPE_START(kernel_membanks_initial[i]))
				break; /* Bank doesn't cover the last possible mapping location. */
			waste = (vm_ppage_t)-2; /* A lot of waste this way... */
		} else
#endif
		{
			/* See how much memory we're wasting with this allocation. */
			assert(PMEMBANK_TYPE_END(kernel_membanks_initial[i]) >=
			       (VM_PPAGE2ADDR(bank_alloc_page) + num_bytes));
			waste = (vm_ppage_t)(PMEMBANK_TYPE_END(kernel_membanks_initial[i]) -
			                     (VM_PPAGE2ADDR(bank_alloc_page) + num_bytes));
#if 0
			{
				/* Subtract the number of bytes used by this, that would otherwise go unused from `waste'
				 * (i.e. `NUMBER_OF_BYTES_UNSED_OF(PAGE_ALIGNED_BANK_END ... BYTE_ALIGNED_BANK_END)') */
				vm_phys_t gain_min;
				vm_phys_t gain_end;
				gain_end = PMEMBANK_TYPE_END(kernel_membanks_initial[i]);
				if ((gain_end & (PAGESIZE - 1)) != 0) {
					vm_phys_t used_end;
					size_t gain;
					gain_min = gain_end & ~(PAGESIZE - 1);
					used_end = VM_PPAGE2ADDR(bank_alloc_page) + num_bytes;
					assert(used_end >= gain_min && used_end <= gain_end);
					gain = (size_t)(used_end - gain_min);
					if (gain > candy_weight)
						gain = candy_weight;
					candy_weight -= gain;
				}
			}
#endif
		}
		/* Check if this page is better suited. */
		if (waste <= candy_weight) {
			candy        = bank_alloc_page;
			candy_weight = waste;
			candy_bank   = i;
		}
	}
	if unlikely(candy_bank >= minfo.mb_bankc) {
#if defined(__i386__) || defined(__x86_64__)
		/* Try again, but this time allow allocations beneath the kernel! */
		if unlikely(!allow_beneath_kernel) {
			allow_beneath_kernel = true;
			goto again;
		}
#endif
		for (i = 0; i < minfo.mb_bankc; ++i) {
			if (minfo.mb_banks[i].mb_type == PMEMBANK_TYPE_UNDEF)
				continue;
			printk(FREESTR(KERN_EMERG "Bank #%Iu: %I64p-%I64p [%s] (%Iu (%#Ix) bytes / %Iu (%#Ix) pages)\n"),
			       (size_t)i,
			       (u64)PMEMBANK_TYPE_MIN(minfo.mb_banks[i]),
			       (u64)PMEMBANK_TYPE_MAX(minfo.mb_banks[i]),
			       pmembank_type_names[minfo.mb_banks[i].mb_type],
			       (size_t)PMEMBANK_TYPE_SIZE(minfo.mb_banks[i]),
			       (size_t)PMEMBANK_TYPE_SIZE(minfo.mb_banks[i]),
			       (size_t)PMEMBANK_TYPE_NUMPAGES(minfo.mb_banks[i]),
			       (size_t)PMEMBANK_TYPE_NUMPAGES(minfo.mb_banks[i]));
		}
		kernel_panic(FREESTR("Failed to locate sufficient memory to allocate "
		                     "RAM control structures (requiring %Iu bytes)\n"),
		             num_bytes);
	}
	/* Reserve memory from the candy-bank. */
	{
		vm_phys_t candy_phys     = VM_PPAGE2ADDR(candy);
		vm_phys_t candy_phys_max = candy_phys + num_bytes - 1;
		assert(candy_phys >= PMEMBANK_TYPE_MIN(kernel_membanks_initial[candy_bank]));
		assert(candy_phys_max <= PMEMBANK_TYPE_MAX(kernel_membanks_initial[candy_bank]));
		assert(kernel_membanks_initial[candy_bank].mb_type == PMEMBANK_TYPE_RAM);
		if (candy_phys_max < PMEMBANK_TYPE_MAX(kernel_membanks_initial[candy_bank])) {
			/* Split the bank above to keep information about unused memory. */
			++minfo.mb_bankc; /* Inc before to account for trailing sentinel bank. */
			memmove(&kernel_membanks_initial[candy_bank + 1],
			        &kernel_membanks_initial[candy_bank],
			        (minfo.mb_bankc - candy_bank) *
			        sizeof(struct pmembank));
			kernel_membanks_initial[candy_bank + 1].mb_start = candy_phys_max + 1;
		}
		assert(candy_phys_max == PMEMBANK_TYPE_MAX(kernel_membanks_initial[candy_bank]));
		assert(candy_phys >= PMEMBANK_TYPE_MIN(kernel_membanks_initial[candy_bank]));
		if (candy_phys == PMEMBANK_TYPE_MIN(kernel_membanks_initial[candy_bank])) {
			kernel_membanks_initial[candy_bank].mb_type = PMEMBANK_TYPE_ALLOCATED;
		} else {
			++minfo.mb_bankc; /* Inc before to account for trailing sentinel bank. */
			memmove(&kernel_membanks_initial[candy_bank + 1],
			        &kernel_membanks_initial[candy_bank],
			        (minfo.mb_bankc - candy_bank) *
			        sizeof(struct pmembank));
			kernel_membanks_initial[candy_bank + 1].mb_start = candy_phys;
			kernel_membanks_initial[candy_bank + 1].mb_type  = PMEMBANK_TYPE_ALLOCATED;
		}
	}
	return candy;
}


/* Construct memory zones from memory info. */
INTERN ATTR_FREETEXT void NOTHROW(KCALL minfo_makezones)(void) {
	/* This function is quite the nuisance, and doing it right is quite difficult.
	 *  - We need to (dynamically) create some very large bitsets to hold information
	 *    about what physical memory has been allocated.
	 *  - Information about this currently stems from temporary data vectors that are
	 *    hacked to overlap with the far end of the boot task's stack, with information
	 *    about where to allocate these bitsets also originating from that same vector.
	 *  - We must allocate all of this memory in physically linear pages, as we can't
	 *    afford to have this information split across different parts of memory, as
	 *    we only got 1 VM node/datapart (kernel_vm_(part|node)_pagedata) to describe this.
	 *  - We can't just willy-nilly start using available ram, as it may contain important
	 *    data structures left by the BIOS or BOOT loader! (so we must also look out for
	 *    memory preservations)
	 */
	size_t i, zone_count = 0, req_bytes = 0;
	size_t req_pages;
	byte_t *buffer;

	/* First off: figure out exactly how many bytes we need for everything! */
	assert(minfo.mb_banks == kernel_membanks_initial);
	/* NOTE: Allocate memory for +3 banks because the necessary allocation
	 *       below may add up to +2 additional banks, with the 3rd bank
	 *       being required as a trailing sentinel bank to terminate the
	 *       known address space. */
	req_bytes = (minfo.mb_bankc + 3) * sizeof(struct pmembank);
	for (i = 0; i < minfo.mb_bankc; ++i) {
		pageptr_t bank_start_page, bank_end_page;
		assertf(kernel_membanks_initial[i].mb_type < PMEMBANK_TYPE_COUNT,
		        "kernel_membanks_initial[i].mb_type = %u",
		        kernel_membanks_initial[i].mb_type);
		if (!PMEMBANK_TYPE_SHOULD_ZONE(kernel_membanks_initial[i].mb_type))
			continue;
		bank_start_page = PMEMBANK_TYPE_STARTPAGE(kernel_membanks_initial[i]);
		/* Scan ahead to merge adjacent, zoned memory banks. */
		while (i + 1 < minfo.mb_bankc &&
		       PMEMBANK_TYPE_SHOULD_ZONE(kernel_membanks_initial[i + 1].mb_type))
			++i;
		bank_end_page = PMEMBANK_TYPE_ENDPAGE(kernel_membanks_initial[i]);
		if unlikely(!(bank_start_page <= bank_end_page - 1))
			continue; /* Zonable area isn't large enough */
		++zone_count;
		req_bytes += PMEMZONE_SIZEOF(bank_end_page - bank_start_page);
	}
	printk(FREESTR(KERN_DEBUG "Using %Iu memory zones\n"), zone_count);

	/* Also include the vector of memory zone pointers later found in `mzones.pm_zones' */
	req_bytes += zone_count * sizeof(struct pmemzone *);

	/* Now that we now exactly how much memory will be required for physical
	 * memory management, as well as relocating the meminfo vector, we must
	 * search for a piece of available ram that is large enough to accomplish
	 * this for us.
	 * For this, we prefer using banked memory that is not aligned by whole
	 * pages, as it would otherwise go unused forever, since page_malloc()
	 * is not capable of allocating sub-page memory. */
	req_pages = (req_bytes + (PAGESIZE - 1)) / PAGESIZE;
	kernel_vm_part_pagedata.dp_ramdata.rd_block0.rb_start = minfo_allocate_part_pagedata(req_bytes);
	printk(FREESTR(KERN_DEBUG "Allocate paging control structures at "
	               FORMAT_VM_PHYS_T "..." FORMAT_VM_PHYS_T " (%Iu bytes in %Iu pages)\n"),
	       VM_PPAGE2ADDR(kernel_vm_part_pagedata.dp_ramdata.rd_block0.rb_start),
	       VM_PPAGE2ADDR(kernel_vm_part_pagedata.dp_ramdata.rd_block0.rb_start) + req_bytes - 1,
	       req_bytes, req_pages);
	kernel_vm_part_pagedata.dp_ramdata.rd_block0.rb_size = req_pages;
	kernel_vm_part_pagedata.dp_tree.a_vmax = (vm_dpage_t)(req_pages - 1);
	kernel_vm_node_pagedata.vn_node.a_vmin = (vm_vpage_t)(kernel_vm_part_pagedata.dp_ramdata.rd_block0.rb_start +
                                                          KERNEL_BASE_PAGE);
	kernel_vm_node_pagedata.vn_node.a_vmax = kernel_vm_node_pagedata.vn_node.a_vmin + req_pages - 1;
	buffer = (byte_t *)VM_PAGE2ADDR(kernel_vm_node_pagedata.vn_node.a_vmin);
	/* With the required buffer now allocated, we can move on to populating it with data.
	 * NOTE: Since `minfo_allocate_part_pagedata()' only changed pages marked as `PMEMBANK_TYPE_RAM'
	 *       to become `PMEMBANK_TYPE_ALLOCATED', both of which have the same properties when it
	 *       comes to `PMEMBANK_TYPE_SHOULD_ZONE()', there should not be any change to how many
	 *       zones will be required, or where those zones will be located at! */
	/* Start by allocating the zone vector. */
	mzones.pm_zonec = zone_count;
	mzones.pm_zones = (struct pmemzone **)buffer;
	buffer += zone_count * sizeof(struct pmemzone *);
	/* Now move on to generate the memory zones themself. */
	zone_count = 0;
	for (i = 0; i < minfo.mb_bankc; ++i) {
		pageptr_t bank_start_page, bank_end_page;
		pageptr_t prev_init_end;
		struct pmemzone *zone;
		size_t zone_bank_start;
		assertf(kernel_membanks_initial[i].mb_type < PMEMBANK_TYPE_COUNT,
		        "kernel_membanks_initial[i].mb_type = %u",
		        kernel_membanks_initial[i].mb_type);
		if (!PMEMBANK_TYPE_SHOULD_ZONE(kernel_membanks_initial[i].mb_type))
			continue;
		bank_start_page = PMEMBANK_TYPE_STARTPAGE(kernel_membanks_initial[i]);
		/* Scan ahead to merge adjacent, zoned memory banks. */
		zone_bank_start = i;
		while (i + 1 < minfo.mb_bankc &&
		       PMEMBANK_TYPE_SHOULD_ZONE(kernel_membanks_initial[i + 1].mb_type))
			++i;
		bank_end_page = PMEMBANK_TYPE_ENDPAGE(kernel_membanks_initial[i]);
		if unlikely(!(bank_start_page <= bank_end_page - 1))
			continue; /* Zonable area isn't large enough */
		/* Allocate and remember the new zone. */
		zone = (struct pmemzone *)buffer;
		buffer += PMEMZONE_SIZEOF(bank_end_page - bank_start_page);
		((struct pmemzone **)mzones.pm_zones)[zone_count] = zone;
		if (zone_count == 0) {
			zone->mz_prev = NULL;
		} else {
			zone->mz_prev = mzones.pm_zones[zone_count - 1];
			zone->mz_prev->mz_next = zone;
		}
		++zone_count;
		zone->mz_start = bank_start_page;
		zone->mz_max   = bank_end_page - 1;
		zone->mz_rmax  = (bank_end_page - 1) - bank_start_page;
		zone->mz_fmax  = zone->mz_rmax;
		zone->mz_cfree = 0;
		zone->mz_qfree = 0;
		zone->mz_zero  = 0;
		prev_init_end  = bank_start_page;
		do {
			uintptr_t init_mask;
			pagecnt_t size;
			pageptr_t startpage, endpage;
			startpage = PMEMBANK_TYPE_STARTPAGE(minfo.mb_banks[zone_bank_start]);
			endpage   = PMEMBANK_TYPE_ENDPAGE(minfo.mb_banks[zone_bank_start]);
			if unlikely(startpage >= endpage) {
				/* Special case: Memory zone too small to fit even a single whole page.
				 * [output] MEMORY 0000000000BC3000...0000000000BC4FFF (kernel_free)
				 * [output] MEMORY 0000000000BC5000...0000000000BC5033 (ram)
				 * [output] MEMORY 0000000000BC5034...0000000000BC5052 (preserve)
				 * [output] MEMORY 0000000000BC5053...0000000007FDFFFF (ram)
				 * In this case, we can assume that at least some portion of the page is
				 * considered to not be ~normal~ RAM. - So because of this, we do pretty
				 * much assume that all pages (at least partially) touched by this mapping
				 * are entirely undefined (which may not necessarily be so, but is the
				 * safest thing which we can do). */
				startpage = (pageptr_t)FLOORDIV(PMEMBANK_TYPE_MIN(minfo.mb_banks[zone_bank_start]), PAGESIZE);
				endpage   = (pageptr_t)CEILDIV(PMEMBANK_TYPE_MAX(minfo.mb_banks[zone_bank_start]), PAGESIZE);
				if unlikely(startpage < bank_start_page)
					startpage = bank_start_page;
				if unlikely(endpage > bank_end_page)
					endpage   = bank_end_page;
				init_mask = PMEMBITSET_UNDFMASK;
			} else {
				init_mask = minfo.mb_banks[zone_bank_start].mb_type == PMEMBANK_TYPE_RAM
				            ? (PMEMBITSET_FREEMASK | PMEMBITSET_UNDFMASK)
				            : (0);
			}
			assert(startpage <= endpage);
			if (prev_init_end < startpage) {
				/* Initialize intermittent pages as undefined. */
				pmemzone_init_bits(zone,
				                   prev_init_end,
				                   (pagecnt_t)(startpage - prev_init_end),
				                   PMEMBITSET_UNDFMASK);
			}
			size = (pagecnt_t)(endpage - startpage);
			pmemzone_init_bits(zone,
			                   startpage,
			                   size,
			                   init_mask);
			if (init_mask)
				zone->mz_cfree += size;
			prev_init_end = startpage + size;
		} while (zone_bank_start++ < i);
		assert(prev_init_end <= bank_end_page);
		/* Initialize trailing pages as undefined. */
		pmemzone_init_bits(zone,
		                   prev_init_end,
		                   (pagecnt_t)(bank_end_page - prev_init_end),
		                   PMEMBITSET_UNDFMASK);
		assert(zone->mz_start == bank_start_page);
		assert(zone->mz_max == bank_end_page - 1);
		assert(zone->mz_rmax == (bank_end_page - 1) - bank_start_page);
		assertf(zone->mz_fmax == zone->mz_rmax,
		        "zone->mz_fmax = %Iu\n"
		        "zone->mz_rmax = %Iu",
		        zone->mz_fmax,
		        zone->mz_rmax);
		assertf(zone->mz_cfree <= (pagecnt_t)zone->mz_rmax + 1,
		        "zone->mz_cfree = %Iu\n"
		        "zone->mz_rmax  = %Iu",
		        (size_t)zone->mz_cfree,
		        (size_t)zone->mz_rmax);
		printk(FREESTR(KERN_INFO "Define memory zone %Iu at " FORMAT_VM_PHYS_T "..." FORMAT_VM_PHYS_T " (%Iu/%Iu free pages)\n"),
		       (size_t)(zone_count - 1),
		       VM_PPAGE2ADDR(zone->mz_start),
		       VM_PPAGE2ADDR(bank_end_page) - 1,
		       (size_t)zone->mz_cfree,
		       (size_t)zone->mz_rmax + 1);
		zone->mz_qfree = zone->mz_cfree; /* Everything is undefined in the beginning */
		zone->mz_free[PMEMZONE_LENGTHOF_BITSET((size_t)zone->mz_rmax + 1)] = 0; /* mz_zero2 */
	}
	assert(zone_count == mzones.pm_zonec);
	/* Finish up by setting the last-zone pointer. */
	mzones.pm_last          = mzones.pm_zones[zone_count - 1];
	mzones.pm_last->mz_next = NULL;
	/* Now just allocate the last part as the relocated memory information vector. */
	minfo.mb_banks = (struct pmembank *)buffer;
	assertf((vm_virt_t)(buffer + (minfo.mb_bankc + 1) * sizeof(struct pmembank)) <=
	        VM_PAGE2ADDR(kernel_vm_node_pagedata.vn_node.a_vmin) + req_bytes,
	        "Too little memory allocated for memory construct structures\n"
	        "buffer     = %p\n"
	        "buffer_min = %p\n"
	        "buffer_max = %p\n",
	        (vm_virt_t)(buffer + (minfo.mb_bankc + 1) * sizeof(struct pmembank)),
	        VM_PAGE2ADDR(kernel_vm_node_pagedata.vn_node.a_vmin),
	        VM_PAGE2ADDR(kernel_vm_node_pagedata.vn_node.a_vmin) + req_bytes - 1);
	memcpy(buffer, kernel_membanks_initial,
	       (minfo.mb_bankc + 1) * sizeof(struct pmembank));
}


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

/* Relocate `minfo', as well as `mzones' data to a more appropriate location
 * after `minfo_makezones()' has been called, and the kernel VM has been
 * cleaned from unused memory mappings.
 * Before this function is called, all memory information still resides at a
 * location where its physical address is relative to its virtual, just like
 * any other kernel data. However, that since can literally be anywhere in
 * virtual memory, it can easily (and accidentally) interfere with memory
 * layout expectancies of other early-boot systems.
 * Because of this, we try to relocate memory information into higher memory
 * as soon as this becomes possible, thus keeping it from randomly showing up
 * and causing problems for other code. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL minfo_relocate_appropriate)(void) {
	size_t num_pages;
	vm_vpage_t dest, old_page;
	ptrdiff_t relocation_offset;
	num_pages = VM_NODE_SIZE(&kernel_vm_node_pagedata);
	dest = vm_getfree(&vm_kernel,
	                  (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_PHYSINFO), num_pages, 1,
	                  HINT_GETMODE(KERNEL_VMHINT_PHYSINFO));
	if unlikely(dest == VM_GETFREE_ERROR) {
		printk(FREESTR(KERN_ERR "Failed to relocate memory information\n"));
		return;
	}
	printk(FREESTR(KERN_DEBUG "Relocate RAM control structures to %p...%p\n"),
	       (uintptr_t)VM_PAGE2ADDR(dest),
	       (uintptr_t)VM_PAGE2ADDR(dest + num_pages) - 1);

	/* Pop the node concerning the memory information, so we can modify it. */
#ifdef NDEBUG
	vm_node_remove(&vm_kernel, kernel_vm_node_pagedata.vn_node.a_vmin);
#else /* NDEBUG */
	{
		struct vm_node *node;
		node = vm_node_remove(&vm_kernel, kernel_vm_node_pagedata.vn_node.a_vmin);
		assert(node == &kernel_vm_node_pagedata);
	}
#endif /* !NDEBUG */
	old_page = kernel_vm_node_pagedata.vn_node.a_vmin;
	relocation_offset = (ptrdiff_t)(dest - old_page) * PAGESIZE;
	kernel_vm_node_pagedata.vn_node.a_vmin = dest;
	kernel_vm_node_pagedata.vn_node.a_vmax = dest + num_pages - 1;
	vm_node_insert(&kernel_vm_node_pagedata);
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if unlikely(!pagedir_prepare_map(kernel_vm_node_pagedata.vn_node.a_vmin, num_pages)) {
		printk(FREESTR(KERN_ERR "Failed to prepare VM for relocated memory "
		                        "information at " FORMAT_VM_PPAGE_T "+%Iu\n"),
		       kernel_vm_node_pagedata.vn_node.a_vmin, num_pages);
		return;
	}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	assert(vm_datapart_numdpages(&kernel_vm_part_pagedata) == num_pages);
	assert(kernel_vm_part_pagedata.dp_ramdata.rd_block0.rb_size == num_pages);
	/* Remove the page directory mapping. */
	pagedir_unmap(old_page, num_pages);
	/* Create a new page directory mapping. */
	pagedir_map(kernel_vm_node_pagedata.vn_node.a_vmin, num_pages,
	            kernel_vm_part_pagedata.dp_ramdata.rd_block0.rb_start,
	            PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
	/* Now apply relocations. */
#define REL(x) (*(uintptr_t *)&(x) += relocation_offset)
	REL(minfo.mb_banks);
	REL(mzones.pm_last);
	REL(mzones.pm_zones);
	{
		size_t i;
		for (i = 0; i < mzones.pm_zonec; ++i) {
			REL(mzones.pm_zones[i]);
			REL(mzones.pm_zones[i]->mz_prev);
			REL(mzones.pm_zones[i]->mz_next);
		}
	}
	/* Reset the pointers for the first/last zone in
	 * order to terminate the chain at both ends. */
	mzones.pm_zones[0]->mz_prev = NULL;
	mzones.pm_last->mz_next     = NULL;
#undef REL
}


/* Release all memory previously marked as `PMEMBANK_TYPE_PRESERVE' or
 * `PMEMBANK_TYPE_ALLOCATED', and page_free() all whole pages touched
 * by mappings of type `PMEMBANK_TYPE_PRESERVE' (unless the same page
 * also contains another mapping of type `PMEMBANK_TYPE_ALLOCATED').
 * Afterwards, transform memory information for either type of memory
 * bank into `PMEMBANK_TYPE_RAM', and (when possible) merge adjacent
 * banks of identical typing. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL minfo_release_presevations)(void) {
	size_t i, num_banks = 0;
	pagecnt_t num_released    = 0;
	pageptr_t freed_pages_end = 0;
	for (i = 0; i < minfo.mb_bankc; ++i) {
		/* Search for PRESERVE and ALLOCATED memory banks. */
		u16 type;
		type = minfo.mb_banks[i].mb_type;
		if (type == PMEMBANK_TYPE_PRESERVE) {
			pageptr_t minpage;
			pageptr_t maxpage;
			/* Figure out how many page we're allowed to free */
			minpage = i == 0
			          ? 0
			          : minfo.mb_banks[i - 1].mb_type == PMEMBANK_TYPE_RAM
			            ? (pageptr_t)FLOORDIV(minfo.mb_banks[i].mb_start, PAGESIZE)
			            : (pageptr_t)CEILDIV(minfo.mb_banks[i].mb_start, PAGESIZE);
			if (i == minfo.mb_bankc - 1) {
				maxpage = (pageptr_t)-1;
			} else if (minfo.mb_banks[i + 1].mb_type == PMEMBANK_TYPE_RAM) {
				size_t j = i + 1;
				/* Scan ahead to make sure that all memory banks overlapping with the page
				 * at `maxpage' are either `PMEMBANK_TYPE_RAM' or `PMEMBANK_TYPE_PRESERVE' */
				maxpage = (pageptr_t)CEILDIV(minfo.mb_banks[i + 1].mb_start, PAGESIZE) - 1;
				while (j < minfo.mb_bankc - 1 &&
				       (((pageptr_t)CEILDIV(minfo.mb_banks[j + 1].mb_start, PAGESIZE) - 1) == maxpage)) {
					if (minfo.mb_banks[j + 1].mb_type == PMEMBANK_TYPE_RAM ||
					    minfo.mb_banks[j + 1].mb_type == PMEMBANK_TYPE_PRESERVE)
						++j;
					else {
						goto use_floordiv_maxpage;
					}
				}
			} else {
use_floordiv_maxpage:
				maxpage = (pageptr_t)FLOORDIV(minfo.mb_banks[i + 1].mb_start, PAGESIZE) - 1;
			}
			if (minpage < freed_pages_end)
				minpage = freed_pages_end; /* Prevent problems resulting from very small reserved pages */
			if (minpage <= maxpage) {
				pagecnt_t temp;
				temp = (pagecnt_t)(maxpage - minpage) + 1;
				printk(FREESTR(KERN_DEBUG "Free preseved memory at %I64p...%I64p\n"),
				       (u64)VM_PPAGE2ADDR(minpage),
				       (u64)VM_PPAGE2ADDR(maxpage + 1) - 1);
				page_free(minpage, temp);
				freed_pages_end = maxpage + 1;
				num_released += temp;
				++num_banks;
			}
			/* Convert this mapping into RAM */
			minfo.mb_banks[i].mb_type = PMEMBANK_TYPE_RAM;
		} else if (type == PMEMBANK_TYPE_ALLOCATED) {
			/* Convert this mapping into RAM */
			minfo.mb_banks[i].mb_type = PMEMBANK_TYPE_RAM;
		}
	}
	printk(FREESTR(KERN_INFO "Released %Iu pages of preserved memory from %Iu banks\n"),
	       (size_t)num_released, num_banks);
	/* Merge adjacent memory banks. */
	for (i = 1; i < minfo.mb_bankc;) {
		if (minfo.mb_banks[i - 1].mb_type != minfo.mb_banks[i].mb_type) {
			++i;
			continue;
		}
		/* Delete the bank at `minfo.mb_banks[i]',
		 * thus merging it with its predecessor. */
		--minfo.mb_bankc;
		memmove(&minfo.mb_banks[i],
		        &minfo.mb_banks[i + 1],
		        (minfo.mb_bankc - i) *
		        sizeof(struct pmembank));
	}
}


struct json_ram_definition {
	uint64_t    rd_start;
	uint64_t    rd_size;
	char const *rd_type;
};

PRIVATE ATTR_FREERODATA byte_t const json_ram_definition_codec[] = {
	JGEN_BEGINOBJECT,
		JGEN_FIELD, 's', 't', 'a', 'r', 't', 0, JGEN_INTO, JSON_OFFSETOF(struct json_ram_definition, rd_start), JSON_TYPE_UINT64,
		JGEN_FIELD, 's', 'i', 'z', 'e',      0, JGEN_INTO, JSON_OFFSETOF(struct json_ram_definition, rd_size), JSON_TYPE_UINT64,
		JGEN_FIELD, 't', 'y', 'p', 'e',      0, JGEN_INTO, JSON_OFFSETOF(struct json_ram_definition, rd_type), JSON_TYPE_STRING_OR_NULL,
	JGEN_END,
	JGEN_TERM
};


PRIVATE ATTR_USED ATTR_FREETEXT void KCALL
kernel_handle_ram_cmdline(char *__restrict arg) {
	struct json_parser parser;
	unsigned int json_error;
	json_parser_init(&parser, arg, strend(arg));
	json_error = json_parser_enterarray(&parser);
	if (json_error != JSON_ERROR_OK)
		goto parser_error;
	for (;;) {
		struct json_ram_definition ramdef;
		u16 bank_type;
		json_error = json_decode(&parser, json_ram_definition_codec, &ramdef);
		if (json_error != JSON_ERROR_OK)
			goto parser_error;
		if (!ramdef.rd_type)
			bank_type = PMEMBANK_TYPE_RAM;
		else {
			/* Translate the bank type. */
			for (bank_type = 0;
			     bank_type < COMPILER_LENOF(pmembank_type_names); ++bank_type) {
				if (strcmp(ramdef.rd_type, pmembank_type_names[bank_type]) == 0)
					goto got_bank_type;
			}
			printk(FREESTR(KERN_ERR "[cmdline] Unknown ram type %q"), ramdef.rd_type);
			goto next_definition;
		}
got_bank_type:
		minfo_addbank((vm_phys_t)ramdef.rd_start,
		              (vm_phys_t)ramdef.rd_size,
		              bank_type);
next_definition:
		if (*parser.jp_pos != ',')
			break;
		json_parser_yield(&parser);
	}
	json_error = json_parser_leavearray(&parser);
	if (json_error != JSON_ERROR_OK)
		goto parser_error;
	return;
parser_error:
	printk(FREESTR(KERN_ERR "[cmdline][error=%d] Malformed `ram' argument %q\n"),
	       json_error, arg);
}

/* 'ram=[{ "type": "ram", "start": 0x1000000, "size": 0x4000 }, { ... }]'
 * The ram commandline parameter uses json to encode additional
 * ranges of physical ram, using the following scheme:
[
	{
		"type"  : ONE_OF { <pmembank_type_names> } DEFAULT "ram",
		"start" : uint64_t REQUIRED,
		"size"  : uint64_t REQUIRED
	}
]
 */
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(kernel_handle_ram_cmdline,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_FUNC,
                                            "ram");


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MEMINFO_C */
