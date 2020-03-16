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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PHYS2VIRT64_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PHYS2VIRT64_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/phys2virt64.h>

#ifdef CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC

#include <kernel/arch/cpuid.h>
#include <kernel/boot.h>
#include <kernel/except.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <assert.h>

#define KiB(n) ((n) * 1024)
#define MiB(n) ((n) * 1024 * 1024)
#define GiB(n) ((n) * 1024 * 1024 * 1024)

/* Need at least 2 control vectors to allow for the case
 * where an unaligned physical memory access happens to
 * cross a 1GiB boundary, in which case 2 vectors are
 * needed to allow the request to complete successfully. */
#if (!defined(CONFIG_PHYS2VIRT_IDENTITY_MINALLOC) || \
     (CONFIG_PHYS2VIRT_IDENTITY_MINALLOC + 0) < 2)
#undef CONFIG_PHYS2VIRT_IDENTITY_MINALLOC
#define CONFIG_PHYS2VIRT_IDENTITY_MINALLOC 2
#endif /* !CONFIG_PHYS2VIRT_IDENTITY_MINALLOC */

DECL_BEGIN

/* Make sure that the phys2virt segment is located within kernel-share memory. */
STATIC_ASSERT(P64_PDIR_VEC4INDEX(KERNEL_PHYS2VIRT_BASE) >= 256);

/* End address of the phys2virt segment. */
#define KERNEL_PHYS2VIRT_END (KERNEL_PHYS2VIRT_BASE + KERNEL_PHYS2VIRT_SIZE)

/* Set of `P64_PAGE_FGLOBAL' and `P64_PAGE_FNOEXEC', depending
 * on which (if any) of these flags are supported by the host. */
PRIVATE u64 p64_page_fglobal_and_p64_page_fnoexec;

/* [const] Base-address of `metadata_size' continuous bytes of physical
 *         memory, allocated for the purpose of maintaining phys2virt meta-data. */
PRIVATE PAGEDIR_PAGEALIGNED vm_phys_t metadata_base;

/* [const] The total size of `metadata_base' */
PRIVATE PAGEDIR_PAGEALIGNED size_t metadata_size = 0;

/* [lock(!PREEMPTION && SMP(metadata_lock))]
 * # of free trailing bytes in `metadata_base' */
PRIVATE PAGEDIR_PAGEALIGNED size_t metadata_avail = 0;

#ifndef CONFIG_NO_SMP
/* Lock that must be held while modifying phys2virt mappings on an SMP machine. */
PRIVATE struct atomic_rwlock metadata_lock = ATOMIC_RWLOCK_INIT;
#endif /* !CONFIG_NO_SMP */




INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_phys2virt64)(void) {
	INTDEF u64 used_pxx_page_fglobal; /* s.a. `paging64.c.inl' */
	p64_page_fglobal_and_p64_page_fnoexec = used_pxx_page_fglobal; /* `P64_PAGE_FGLOBAL' or `0' */
	if (X86_HAVE_EXECUTE_DISABLE)
		p64_page_fglobal_and_p64_page_fnoexec |= P64_PAGE_FNOEXEC;
	/* Check if 1GiB pages are possible.
	 * If they are, configure physident using them.
	 * Otherwise, pre-allocate up to `CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC'
	 * pages of physical memory to-be used for dynamic mapping of
	 * E1-vectors allocated by `x86_phys2virt64_require()' */
	if (X86_HAVE_1GIB_PAGES) {
		/* 1GiB pages are stored in E3-vector entries.
		 * Since all E3-vectors within kernel-space are pre-allocated to
		 * ensure consistency of the kernel-share segment, don't even have
		 * to allocate _any_ memory here! (all of the allocations have
		 * already been done during the assembly bootstrap) */
		unsigned int vec4;
		union p64_pdir_e3 e3;
		printk(FREESTR(KERN_INFO "[p2v] Use 1GiB pages for the phys2virt memory segment\n"));
		e3.p_word = P64_PAGE_FPRESENT |
		            P64_PAGE_FWRITE |
		            P64_PAGE_FACCESSED |
		            P64_PAGE_FDIRTY |
		            P64_PAGE_F1GIB |
		            p64_page_fglobal_and_p64_page_fnoexec;
		for (vec4 = P64_PDIR_VEC4INDEX(KERNEL_PHYS2VIRT_BASE);
		     vec4 < P64_PDIR_VEC4INDEX(KERNEL_PHYS2VIRT_END); ++vec4) {
			unsigned int vec3;
			for (vec3 = 0; vec3 < 512; ++vec3) {
				P64_PDIR_E3_IDENTITY[vec4][vec3].p_word = e3.p_word;
				e3.p_word += GiB(1);
			}
		}
		COMPILER_WRITE_BARRIER();
		/* override `x86_phys2virt64_require()' to become a no-op */
		((byte_t *)&x86_phys2virt64_require)[0] = 0xc3; /* ret */
	} else {
		pageptr_t pp;
		printk(FREESTR(KERN_INFO "[p2v] Use 2MiB pages for the phys2virt memory segment\n"));
		/* TODO: Add a kernel commandline option to select how much
		 *       memory should be reserved for the phys2virt mapping! */
		metadata_size = CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC * PAGESIZE;
		pp = page_malloc(CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC);
		if unlikely(pp == PAGEPTR_INVALID) {
			/* Try again with less memory... */
			metadata_size = CONFIG_PHYS2VIRT_IDENTITY_MINALLOC * PAGESIZE;
			pp = page_malloc(CONFIG_PHYS2VIRT_IDENTITY_MINALLOC);
			if unlikely(pp == PAGEPTR_INVALID)
				kernel_panic(FREESTR("Failed to allocate phys2virt control pages"));
		}
		metadata_base  = page2addr(pp);
		metadata_avail = metadata_size;
		/* Register the phys2virt VM node. */
		vm_node_insert(&x86_phys2virt64_node);
	}
}


/* - Clear all currently used phys2virt metadata vectors,
 * - Set `metadata_avail' to `metadata_size'
 * - Broadcast an INVLPG IPI to all CPUs that are currently online. */
LOCAL NOBLOCK NOPREEMPT void
NOTHROW(KCALL metadata_clearall)(void) {
	unsigned int vec4;
	for (vec4 = P64_PDIR_VEC4INDEX(KERNEL_PHYS2VIRT_BASE);
	     vec4 < P64_PDIR_VEC4INDEX(KERNEL_PHYS2VIRT_END); ++vec4) {
		unsigned int vec3;
		for (vec3 = 0; vec3 < 512; ++vec3) {
			union p64_pdir_e3 e3;
			e3.p_word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
			assertf(!(e3.p_word & P64_PAGE_F1GIB),
			        "x86_phys2virt64_require() should be a no-op if 1GiB "
			        "pages were actually supported, so we shouldn't be "
			        "able to get here if that was the case!");
			if (!(e3.p_word & P64_PAGE_FPRESENT))
				continue; /* Not allocated. */
			assertf((e3.p_word & P64_PAGE_FVECTOR) >= (u64)metadata_base &&
			        (e3.p_word & P64_PAGE_FVECTOR) < (u64)metadata_base + metadata_size,
			        "E2-vector at phys:%I64p from phys2virt segment isn't apart of "
			        "the metadata page vector at %I64p-%I64p",
			        (u64)(e3.p_word & P64_PAGE_FVECTOR),
			        (u64)metadata_base,
			        (u64)metadata_base + metadata_size - 1);
			/* Mark the E3-vector as absent. */
			ATOMIC_WRITE(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word, P64_PAGE_ABSENT);
		}
	}
	COMPILER_WRITE_BARRIER();
	metadata_avail = metadata_size;
	COMPILER_WRITE_BARRIER();
	/* Flush paging caches on all CPUs that are currently online.
	 * Technically, we'd only need to do this for the phys2virt address
	 * ranges. However, there sadly isn't any instruction that would allow
	 * us to do this, so it's easier to just blindly invalidate everything. */
	vm_kernel_syncall();
}


/* Ensure that the given `addr', which must be located
 * inside of [KERNEL_PHYS2VIRT_MIN, KERNEL_PHYS2VIRT_MAX]
 * is mapped against its designated physical address.
 * This function is called from within the #PF handler
 * when a kernel-originating fault happens for an address
 * within that range.
 * NOTE: When called before `x86_initialize_phys2virt64()',
 *       this function may throw an E_SEGFAULT. Afterwards,
 *       this function is unconditionally NOTHROW! */
PUBLIC NOBLOCK NOPREEMPT void KCALL x86_phys2virt64_require(void *addr) {
	unsigned int vec4, vec3;
	union p64_pdir_e3 e3;
	vm_phys_t new_e3_word;
	assert(!PREEMPTION_ENABLED());
	assertf((uintptr_t)addr >= KERNEL_PHYS2VIRT_MIN &&
	        (uintptr_t)addr <= KERNEL_PHYS2VIRT_MAX,
	        "addr = %p", addr);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	assert(vec4 >= 256);
	assert(P64_PDIR_E4_IDENTITY[vec4].p_vec3.v_present);
#ifndef CONFIG_NO_SMP
	while (!sync_tryread(&metadata_lock))
		task_pause();
again_read_e3_word:
#endif /* !CONFIG_NO_SMP */
	/* Check for unlikely case:
	 *    This is a sporadic pagefault, or some other CPU
	 *    already allocated the same 1GiB page vector. */
	e3.p_word = ATOMIC_READ(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word);
	if unlikely(e3.p_vec2.v_present)
		goto done;
	/* If no metadata is available, clear all phys2virt mappings */
	if unlikely(!metadata_avail) {
		/* Check for special case: No metadata has ever been allocated... */
		if unlikely(!metadata_size) {
#ifndef CONFIG_NO_SMP
			sync_endread(&metadata_lock);
#endif /* !CONFIG_NO_SMP */
			THROW(E_SEGFAULT_UNMAPPED, addr);
		}
		metadata_clearall();
	}
	assert(metadata_avail);
	assert(IS_ALIGNED(metadata_base, PAGESIZE));
	assert(IS_ALIGNED(metadata_avail, PAGESIZE));
	new_e3_word = metadata_base + metadata_size - metadata_avail;
	assert(IS_ALIGNED(new_e3_word, PAGESIZE));
	metadata_avail -= PAGESIZE;
	/* Create a temporary mapping of `PHYS:e3_word',
	 * using the current thread's VM trampoline. */
	{
		unsigned int vec2;
		pagedir_pushval_t pushval;
		union p64_pdir_e2 e2, *e2_vector;
		e2_vector = (union p64_pdir_e2 *)THIS_TRAMPOLINE_BASE;
		pushval   = pagedir_push_mapone(e2_vector, new_e3_word, PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
		pagedir_syncone(e2_vector);
		/* Figure out which physical memory range should be mapped.
		 * We're going to fill in 512 * 2MiB pages, totaling 1GiB
		 * of physical memory.
		 * Thus, use the relative offset from the start of the
		 * phys2virt segment, then floor-align that offset by 1GiB. */
		e2.p_word = (uintptr_t)addr - KERNEL_PHYS2VIRT_BASE;
		e2.p_word &= ~(GiB(1) - 1);
		/* Set control flags */
		e2.p_word |= P64_PAGE_FPRESENT | P64_PAGE_FWRITE |
		             P64_PAGE_FACCESSED | P64_PAGE_FDIRTY |
		             P64_PAGE_F2MIB |
		             p64_page_fglobal_and_p64_page_fnoexec;
		for (vec2 = 0; vec2 < 512; ++vec2) {
			e2_vector[vec2].p_word = e2.p_word;
			e2.p_word += MiB(2);
		}
		pagedir_pop_mapone(e2_vector, pushval);
	}
	new_e3_word |= P64_PAGE_FPRESENT | P64_PAGE_FWRITE |
	               P64_PAGE_FACCESSED | P64_PAGE_FDIRTY |
	               p64_page_fglobal_and_p64_page_fnoexec;
	/* Insert the fully initialized E2 vector into its proper entry. */
#ifdef CONFIG_NO_SMP
	COMPILER_WRITE_BARRIER();
	P64_PDIR_E3_IDENTITY[vec4][vec3].p_word = new_e3_word;
	COMPILER_WRITE_BARRIER();
#else /* CONFIG_NO_SMP */
	/* Guard against page directory modifications from other CPUs */
	if unlikely(!ATOMIC_CMPXCH(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word,
	                           e3.p_word, new_e3_word)) {
		/* Release previously allocated meta-data. */
		metadata_avail += PAGESIZE;
		goto again_read_e3_word;
	}
#endif /* !CONFIG_NO_SMP */
	printk(FREESTR(KERN_DEBUG "[p2v] Setup identity mapping at %p-%p\n"),
	       (byte_t *)P64_PDIR_VECADDR(vec4, vec3, 0, 0),
	       (byte_t *)P64_PDIR_VECADDR(vec4, vec3, 511, 511) + PAGESIZE - 1);
done:
#ifndef CONFIG_NO_SMP
	sync_endread(&metadata_lock);
#endif /* !CONFIG_NO_SMP */
	;
}

/* A special VM node (that isn't linked to any backing data part,
 * and is thus a so-called ~reserved~ memory mapping), but is checked
 * for by the #PF handler, where it indicates an access made to the
 * physical identity area.
 * Separately, this node's presence within the kernel VM prevents
 * anything else from being mapped into the physical identity range. */
PUBLIC struct vm_node x86_phys2virt64_node = {
	/* .vn_node = */ {
		NULL,
		NULL,
		PAGEID_ENCODE(KERNEL_PHYS2VIRT_MIN),
		PAGEID_ENCODE(KERNEL_PHYS2VIRT_MAX)
	},
	/* .vn_byaddr = */ LLIST_INITNODE,
	/* .vn_prot   = */ VM_PROT_READ | VM_PROT_WRITE,
	/* .vn_flags  = */ VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_NOMERGE,
	/* .vn_vm     = */ &vm_kernel,
	/* .vn_part   = */ NULL,                   /* Reserved mapping */
	/* .vn_block  = */ &vm_datablock_physical, /* Physical memory mapping */
	/* .vn_link   = */ LLIST_INITNODE,
	/* .vn_guard  = */ 0
};


DECL_END
#endif /* CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PHYS2VIRT64_C */
