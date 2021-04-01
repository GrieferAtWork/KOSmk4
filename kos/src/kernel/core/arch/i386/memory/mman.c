/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MMAN_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MMAN_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define __WANT_MNODE_INIT
#define __WANT_MPART_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/mman/phys.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/async.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/x86/tss.h>

#include <hybrid/atomic.h>

#include <asm/farptr.h>
#include <asm/intrin.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>


DECL_BEGIN

INTDEF byte_t __kernel_text_start[];
INTDEF byte_t __kernel_text_startpage_p[];
INTDEF byte_t __kernel_text_end[];
INTDEF byte_t __kernel_text_size[];
INTDEF byte_t __kernel_text_numpages[];

INTDEF byte_t __kernel_rodata_start[];
INTDEF byte_t __kernel_rodata_startpage_p[];
INTDEF byte_t __kernel_rodata_end[];
INTDEF byte_t __kernel_rodata_size[];
INTDEF byte_t __kernel_rodata_numpages[];

INTDEF byte_t __kernel_data_start[];
INTDEF byte_t __kernel_data_startpage_p[];
INTDEF byte_t __kernel_data_end[];
INTDEF byte_t __kernel_data_size[];
INTDEF byte_t __kernel_data_numpages[];

INTDEF byte_t __kernel_pdata_start[];
INTDEF byte_t __kernel_pdata_start_p[];
INTDEF byte_t __kernel_pdata_startpage_p[];
INTDEF byte_t __kernel_pdata_end[];
INTDEF byte_t __kernel_pdata_end_p[];
INTDEF byte_t __kernel_pdata_endpage_p[];
INTDEF byte_t __kernel_pdata_size[];
INTDEF byte_t __kernel_pdata_numpages[];

INTDEF byte_t __kernel_xdata_start[];
INTDEF byte_t __kernel_xdata_startpage_p[];
INTDEF byte_t __kernel_xdata_end[];
INTDEF byte_t __kernel_xdata_size[];
INTDEF byte_t __kernel_xdata_numpages[];

INTDEF byte_t __kernel_bss_start[];
INTDEF byte_t __kernel_bss_startpage_p[];
INTDEF byte_t __kernel_bss_end[];
INTDEF byte_t __kernel_bss_size[];
INTDEF byte_t __kernel_bss_numpages[];

INTDEF byte_t __kernel_bootiob_start[] ASMNAME("__x86_iob_empty_base");
INTDEF byte_t __kernel_bootiob_startpage_p[] ASMNAME("__x86_iob_empty_page_p");

#undef CONFIG_BOOTCPU_IOB_LIES_IN_BSS
#undef CONFIG_BOOTCPU_IOB_LIES_IN_DATA
#ifndef CONFIG_NO_SMP
#define CONFIG_BOOTCPU_IOB_LIES_IN_BSS 1
#else /* !CONFIG_NO_SMP */
#define CONFIG_BOOTCPU_IOB_LIES_IN_DATA 1
#endif /* CONFIG_NO_SMP */



/* The first mapping: a single page not mapped to anything, located at `0xc0000000'.
 * This page is used to ensure that iterating through user-memory can always be done
 * safely,  after only the starting pointer has been  checked, so long as at least 1
 * byte is read for every 4096 bytes being advanced. */
#define X86_KERNEL_VMMAPPING_CORE_TEXT        0 /* .text */
#define X86_KERNEL_VMMAPPING_CORE_RODATA      1 /* .rodata */
#ifdef CONFIG_BOOTCPU_IOB_LIES_IN_BSS
#define X86_KERNEL_VMMAPPING_CORE_DATA        2 /* .data */
#define X86_KERNEL_VMMAPPING_CORE_XDATA       3 /* .xdata / .xbss */
#define X86_KERNEL_VMMAPPING_CORE_BSS1        4 /* .bss */
#define X86_KERNEL_VMMAPPING_CORE_BSS2        5 /* .bss */
INTDEF byte_t __x86_kernel_bss_before_iob_size[];
INTDEF byte_t __x86_kernel_bss_before_iob_pages[];
INTDEF byte_t __x86_kernel_bss_after_iob_size[];
INTDEF byte_t __x86_kernel_bss_after_iob_pages[];
#define __kernel_bss1_start       __kernel_bss_start
#define __kernel_bss1_startpage_p __kernel_bss_startpage_p
#define __kernel_bss1_end         __kernel_bootiob_start
#define __kernel_bss1_size        __x86_kernel_bss_before_iob_size
#define __kernel_bss1_numpages    __x86_kernel_bss_before_iob_pages
#define __kernel_bss2_start       (__kernel_bootiob_start + 2 * PAGESIZE) /* 2: Number of pages in TSS.IOB */
#define __kernel_bss2_startpage_p (__kernel_bootiob_startpage_p + 2)      /* 2: Number of pages in TSS.IOB */
#define __kernel_bss2_end         __kernel_bss_end
#define __kernel_bss2_size        (__x86_kernel_bss_after_iob_size - 2 * PAGESIZE)
#define __kernel_bss2_numpages    (__x86_kernel_bss_after_iob_pages - 2)
#else /* CONFIG_BOOTCPU_IOB_LIES_IN_BSS */
#define X86_KERNEL_VMMAPPING_CORE_DATA1       2 /* .data */
#define X86_KERNEL_VMMAPPING_CORE_DATA2       3 /* .data */
#define X86_KERNEL_VMMAPPING_CORE_XDATA       4 /* .xdata / .xbss */
#define X86_KERNEL_VMMAPPING_CORE_BSS         5 /* .bss */
INTDEF byte_t __x86_kernel_data_before_iob_size[];
INTDEF byte_t __x86_kernel_data_before_iob_pages[];
INTDEF byte_t __x86_kernel_data_after_iob_size[];
INTDEF byte_t __x86_kernel_data_after_iob_pages[];
#define __kernel_data1_start       __kernel_data_start
#define __kernel_data1_startpage_p __kernel_data_startpage_p
#define __kernel_data1_end         __kernel_bootiob_start
#define __kernel_data1_size        __x86_kernel_data_before_iob_size
#define __kernel_data1_numpages    __x86_kernel_data_before_iob_pages
#define __kernel_data2_start       (__kernel_bootiob_start + 2 * PAGESIZE) /* 2: Number of pages in TSS.IOB */
#define __kernel_data2_startpage_p (__kernel_bootiob_startpage_p + 2)      /* 2: Number of pages in TSS.IOB */
#define __kernel_data2_end         __kernel_data_end
#define __kernel_data2_size        (__x86_kernel_data_after_iob_size - 2 * PAGESIZE)
#define __kernel_data2_numpages    (__x86_kernel_data_after_iob_pages - 2)
#endif /* !CONFIG_BOOTCPU_IOB_LIES_IN_BSS */
#define X86_KERNEL_VMMAPPING_IDENTITY_RESERVE 6 /* A memory reservation made for the page directory identity mapping. */



INTDEF struct mpart x86_kernel_vm_parts[];
INTDEF struct mnode x86_kernel_vm_nodes[];
INTDEF struct mnode x86_vmnode_transition_reserve;

#define INIT_MPART(self, node, pageptr, num_pages, num_bytes)                 \
	{                                                                         \
		MPART_INIT_mp_refcnt(2), /* 2 == 1(myself) + 1(node) */               \
		MPART_INIT_mp_flags(MPART_F_NOSPLIT | MPART_F_NOMERGE |               \
		                    MPART_F_MLOCK_FROZEN | MPART_F_MLOCK |            \
		                    MPART_F_NOFREE),                                  \
		MPART_INIT_mp_state(MPART_ST_MEM),                                    \
		MPART_INIT_mp_file(&mfile_ndef),                                      \
		MPART_INIT_mp_copy(LIST_HEAD_INITIALIZER(self.mp_copy)),              \
		MPART_INIT_mp_share(node),                                            \
		MPART_INIT_mp_lockops(SLIST_HEAD_INITIALIZER(self.mp_lockops)),       \
		MPART_INIT_mp_allparts(LIST_ENTRY_UNBOUND_INITIALIZER),               \
		MPART_INIT_mp_minaddr(0),                                             \
		MPART_INIT_mp_maxaddr((num_bytes)-1),                                 \
		MPART_INIT_mp_changed({}),                                            \
		MPART_INIT_mp_filent({}),                                             \
		MPART_INIT_mp_blkst_ptr(NULL),                                        \
		MPART_INIT_mp_mem((physpage_t)(pageptr), (physpagecnt_t)(num_pages)), \
		MPART_INIT_mp_meta(NULL)                                              \
	}

INTERN struct mpart x86_kernel_vm_parts[6] = {
#define DO_INIT_DATAPART(id, startpage, num_pages, num_bytes) \
	INIT_MPART(x86_kernel_vm_parts[id], &x86_kernel_vm_nodes[id], startpage, num_pages, num_bytes)
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_TEXT,   __kernel_text_startpage_p,   __kernel_text_numpages,   __kernel_text_size),
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_RODATA, __kernel_rodata_startpage_p, __kernel_rodata_numpages, __kernel_rodata_size),
#ifdef X86_KERNEL_VMMAPPING_CORE_DATA
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_DATA,   __kernel_data_startpage_p,   __kernel_data_numpages,   __kernel_data_size),
#else /* X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_DATA1,  __kernel_data1_startpage_p,  __kernel_data1_numpages,  __kernel_data1_size),
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_DATA2,  __kernel_data2_startpage_p,  __kernel_data2_numpages,  __kernel_data2_size),
#endif /* !X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_XDATA,  __kernel_xdata_startpage_p,  __kernel_xdata_numpages,  __kernel_xdata_size),
#ifdef X86_KERNEL_VMMAPPING_CORE_BSS
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_BSS,    __kernel_bss_startpage_p,    __kernel_bss_numpages,    __kernel_bss_size),
#else /* X86_KERNEL_VMMAPPING_CORE_BSS */
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_BSS1,   __kernel_bss1_startpage_p,   __kernel_bss1_numpages,   __kernel_bss1_size),
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_BSS2,   __kernel_bss2_startpage_p,   __kernel_bss2_numpages,   __kernel_bss2_size),
#endif /* !X86_KERNEL_VMMAPPING_CORE_BSS */
#undef DO_INIT_DATAPART
};


#define INIT_MNODE_RESERVE(self, minaddr, maxaddr, prot)                \
	{                                                                   \
		MNODE_INIT_mn_mement({}),                                       \
		MNODE_INIT_mn_minaddr(minaddr),                                 \
		MNODE_INIT_mn_maxaddr(maxaddr),                                 \
		MNODE_INIT_mn_flags((prot) | MNODE_F_SHARED | MNODE_F_NOSPLIT | \
		                    MNODE_F_NOMERGE | MNODE_F_KERNPART |        \
		                    _MNODE_F_MPREPARED_KERNEL | MNODE_F_MLOCK), \
		MNODE_INIT_mn_part(NULL),                                       \
		MNODE_INIT_mn_fspath(NULL),                                     \
		MNODE_INIT_mn_fsname(NULL),                                     \
		MNODE_INIT_mn_mman(&mman_kernel),                               \
		MNODE_INIT_mn_partoff(0),                                       \
		MNODE_INIT_mn_link(LIST_ENTRY_UNBOUND_INITIALIZER),             \
		MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),         \
		MNODE_INIT_mn_module(NULL)                                      \
	}
#define INIT_MNODE(self, minaddr, maxaddr, prot, part)                  \
	{                                                                   \
		MNODE_INIT_mn_mement({}),                                       \
		MNODE_INIT_mn_minaddr(minaddr),                                 \
		MNODE_INIT_mn_maxaddr(maxaddr),                                 \
		MNODE_INIT_mn_flags((prot) | MNODE_F_SHARED | MNODE_F_NOSPLIT | \
		                    MNODE_F_NOMERGE | MNODE_F_KERNPART |        \
		                    _MNODE_F_MPREPARED_KERNEL | MNODE_F_MLOCK), \
		MNODE_INIT_mn_part(&(part)),                                    \
		MNODE_INIT_mn_fspath(NULL),                                     \
		MNODE_INIT_mn_fsname(NULL),                                     \
		MNODE_INIT_mn_mman(&mman_kernel),                               \
		MNODE_INIT_mn_partoff(0),                                       \
		MNODE_INIT_mn_link({ NULL, &(part).mp_share.lh_first }),        \
		MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),         \
		MNODE_INIT_mn_module(NULL)                                      \
	}


/* Special VM node used to describe the memory reservation at the user-/kernel-space split. */
INTERN struct mnode x86_vmnode_transition_reserve =
INIT_MNODE_RESERVE(x86_vmnode_transition_reserve,
                  KERNELSPACE_BASE,
                  KERNELSPACE_BASE + PAGESIZE - 1,
                  VM_PROT_NONE);

INTERN struct mnode x86_kernel_vm_nodes[8] = {
#define DO_INIT_NODE_EX(id, startaddr, endaddr, prot) INIT_MNODE(x86_kernel_vm_nodes[id], startaddr, (endaddr)-1, prot, x86_kernel_vm_parts[id])
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_TEXT,   __kernel_text_start,   __kernel_text_end,   MNODE_F_PEXEC | MNODE_F_PREAD),
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_RODATA, __kernel_rodata_start, __kernel_rodata_end, MNODE_F_PREAD),
#ifdef X86_KERNEL_VMMAPPING_CORE_DATA
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_DATA,   __kernel_data_start,   __kernel_data_end,   MNODE_F_PWRITE | MNODE_F_PREAD),
#else /* X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_DATA1,  __kernel_data1_start,  __kernel_data1_end,  MNODE_F_PWRITE | MNODE_F_PREAD),
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_DATA2,  __kernel_data2_start,  __kernel_data2_end,  MNODE_F_PWRITE | MNODE_F_PREAD),
#endif /* !X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_XDATA,  __kernel_xdata_start,  __kernel_xdata_end,  MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD),
#ifdef X86_KERNEL_VMMAPPING_CORE_BSS
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_BSS,    __kernel_bss_start,    __kernel_bss_end,    MNODE_F_PWRITE | MNODE_F_PREAD),
#else /* X86_KERNEL_VMMAPPING_CORE_BSS */
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_BSS1,   __kernel_bss1_start,   __kernel_bss1_end,   MNODE_F_PWRITE | MNODE_F_PREAD),
	DO_INIT_NODE_EX(X86_KERNEL_VMMAPPING_CORE_BSS2,   __kernel_bss2_start,   __kernel_bss2_end,   MNODE_F_PWRITE | MNODE_F_PREAD),
#endif /* !X86_KERNEL_VMMAPPING_CORE_BSS */

	/* [X86_KERNEL_VMMAPPING_IDENTITY_RESERVE] = */
#ifdef X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE
	INIT_MNODE_RESERVE(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE],
	                   0, /* Calculated below */
	                   0, /* Calculated below */
	                   VM_PROT_NONE),
#else /* X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE */
	INIT_MNODE_RESERVE(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE],
	                   X86_MMAN_KERNEL_PDIR_RESERVED_BASE,
	                   X86_MMAN_KERNEL_PDIR_RESERVED_BASE + X86_MMAN_KERNEL_PDIR_RESERVED_SIZE - 1,
	                   VM_PROT_NONE),
#endif /* !X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE */
};

/* The components for the PADDR=VADDR sections, also known as the .pdata sections. */
INTDEF struct mpart x86_pdata_mpart;
INTDEF struct mnode x86_pdata_mnode;

INTERN struct mpart x86_pdata_mpart =
INIT_MPART(x86_pdata_mpart, &x86_pdata_mnode,
           __kernel_pdata_startpage_p,
           __kernel_pdata_numpages,
           __kernel_pdata_size);
INTERN struct mnode x86_pdata_mnode =
INIT_MNODE(x86_pdata_mnode,
           __kernel_pdata_start_p,
           __kernel_pdata_end_p - 1,
           MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD,
           x86_pdata_mpart);



/* The components for initializing the  initial mapping of the .free  section.
 * These are handled on their own, as they are part of the .free section, thus
 * allowing them to be deleted once .free gets removed. */
INTDEF struct mpart x86_kernel_vm_part_free;
INTDEF struct mnode x86_kernel_vm_node_free;

INTDEF byte_t __kernel_free_start[];
INTDEF byte_t __kernel_free_startpage_p[];
INTDEF byte_t __kernel_free_end[];
INTDEF byte_t __kernel_free_size[];
INTDEF byte_t __kernel_free_numpages[];

INTERN ATTR_FREEDATA struct mpart x86_kernel_vm_part_free =
INIT_MPART(x86_kernel_vm_part_free, &x86_kernel_vm_node_free,
           __kernel_free_startpage_p,
           __kernel_free_numpages,
           __kernel_free_size);
INTERN ATTR_FREEDATA struct mnode x86_kernel_vm_node_free =
INIT_MNODE(x86_kernel_vm_node_free,
           __kernel_free_start,
           __kernel_free_end - 1,
           MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD,
           x86_kernel_vm_part_free);


INTDEF struct mpart kernel_meminfo_mpart;
INTDEF struct mnode kernel_meminfo_mnode;
INTERN struct mpart kernel_meminfo_mpart =
INIT_MPART(kernel_meminfo_mpart, &kernel_meminfo_mnode,
           0 /* Filled later */,
           0 /* Filled later */,
           0 /* Filled later */);
INTERN struct mnode kernel_meminfo_mnode =
INIT_MNODE(kernel_meminfo_mnode, 0, 0,
           MNODE_F_PWRITE | MNODE_F_PREAD,
           kernel_meminfo_mpart);

INTDEF struct mpart x86_lapic_mpart;
INTDEF struct mnode x86_lapic_mnode;
INTERN struct mpart x86_lapic_mpart =
INIT_MPART(x86_lapic_mpart, &x86_lapic_mnode,
           0 /* (possibly) Filled later */,
           0 /* (possibly) Filled later */,
           0 /* (possibly) Filled later */);
INTERN struct mnode x86_lapic_mnode =
INIT_MNODE(x86_lapic_mnode, 0, 0,
           MNODE_F_PWRITE | MNODE_F_PREAD,
           x86_lapic_mpart);



STATIC_ASSERT(MNODE_F_PEXEC == PAGEDIR_MAP_FEXEC);
STATIC_ASSERT(MNODE_F_PWRITE == PAGEDIR_MAP_FWRITE);
STATIC_ASSERT(MNODE_F_PREAD == PAGEDIR_MAP_FREAD);

#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
INTDEF byte_t __kernel_boottask_stack_guard[];
INTDEF byte_t __kernel_asyncwork_stack_guard[];
INTDEF byte_t __kernel_bootidle_stack_guard[];
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL simple_insert_and_activate)(struct mnode *__restrict node,
                                          u16 prot) {
	struct mpart *part;
	void *addr;
	assert(node->vn_vm == &vm_kernel);
	vm_node_insert(node);
	part = node->vn_part;
	assertf(mnode_getsize(node) == mpart_getsize(part),
	        "mnode_getsize: %#" PRIxSIZ "\n"
	        "mpart_getsize: %#" PRIxSIZ "\n",
	        mnode_getsize(node), mpart_getsize(part));
	addr = mnode_getaddr(node);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare(addr, part->mp_mem.mc_size * PAGESIZE)) {
		kernel_panic(FREESTR("Failed to prepare kernel mapping at %p...%p\n"),
		             mnode_getminaddr(node), mnode_getmaxaddr(node));
	}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_map(addr, part->mp_mem.mc_size * PAGESIZE,
	            physpage2addr(part->mp_mem.mc_start), prot);
}


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

DATDEF VIRT byte_t volatile *x86_lapicbase_ ASMNAME("x86_lapicbase");

PRIVATE NOBLOCK ATTR_FREETEXT void
NOTHROW(FCALL pagedir_unmap_and_sync_one)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	pagedir_unmapone(addr);
	pagedir_syncone(addr);
}

INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_mman_kernel)(void) {
#ifdef X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE
	{
		/* Calculate the PDIR Identity reservation at runtime. */
		byte_t *minaddr, *maxaddr;
		minaddr = (byte_t *)(X86_MMAN_KERNEL_PDIR_RESERVED_BASE);
		maxaddr = (byte_t *)(X86_MMAN_KERNEL_PDIR_RESERVED_BASE + X86_MMAN_KERNEL_PDIR_RESERVED_SIZE - 1);
		vm_node_setminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE], minaddr);
		vm_node_setmaxaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE], maxaddr);
	}
#endif /* X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE */

	/* Unmap everything before the kernel. */
	if (pagedir_kernelprepare((void *)KERNEL_CORE_BASE,
	                          (uintptr_t)__kernel_text_start - KERNEL_CORE_BASE)) {
		pagedir_unmap((void *)KERNEL_CORE_BASE,
		              (uintptr_t)__kernel_text_start - KERNEL_CORE_BASE);
		pagedir_kernelunprepare((void *)KERNEL_CORE_BASE,
		                        (uintptr_t)__kernel_text_start - KERNEL_CORE_BASE);
	}
	assert(mnode_getminaddr(&kernel_meminfo_mnode) != (byte_t *)0);

	/* Insert kernel-space memory nodes into the kernel VM, and re-map memory as needed. */
	vm_node_insert(&x86_vmnode_transition_reserve);
	/* NOTE: Map the .text and .rodata sections as writable for now, so-as to allow initialization
	 *       code   to   modify  itself,   as  well   as   otherwise  constant   data  structures. */
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_TEXT], PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_RODATA], PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#ifdef X86_KERNEL_VMMAPPING_CORE_DATA
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA], PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#else /* X86_KERNEL_VMMAPPING_CORE_DATA */
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA1], PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA2], PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#endif /* !X86_KERNEL_VMMAPPING_CORE_DATA */
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_XDATA], PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#ifdef X86_KERNEL_VMMAPPING_CORE_BSS
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS], PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#else /* X86_KERNEL_VMMAPPING_CORE_BSS */
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS1], PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
	simple_insert_and_activate(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS2], PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#endif /* !X86_KERNEL_VMMAPPING_CORE_BSS */
	vm_node_insert(&FORCPU(&_bootcpu, thiscpu_x86_iobnode));
	vm_node_insert(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE]);
	vm_node_insert(&x86_kernel_vm_node_free);
	vm_node_insert(&kernel_meminfo_mnode);

	/* Insert  the  mapping  for   the  physical  identity  (.pdata)   section.
	 * The contents of this section are mainly required for SMP initialization,
	 * though  can also be used for other things that require being placed at a
	 * known physical memory location. */
	if (!pagedir_prepare(__kernel_pdata_start - KERNEL_CORE_BASE, (size_t)__kernel_pdata_size))
		kernel_panic(FREESTR("Failed to prepare kernel VM for mapping .pdata\n"));
	simple_insert_and_activate(&x86_pdata_mnode, PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#ifndef NDEBUG
	{
		u32 virt_word, phys_word;
		virt_word = *(u32 *)(__kernel_pdata_start);
		phys_word = *(u32 *)(__kernel_pdata_start - KERNEL_CORE_BASE);
		assert(virt_word == phys_word);
	}
#endif /* !NDEBUG */

	/* Map the LAPIC into the kernel VM. */
	assert(mpart_getsize(&x86_lapic_mpart) == x86_lapic_mpart.mp_mem.mc_size * PAGESIZE);
	if (x86_lapic_mpart.mp_mem.mc_size != 0) {
		byte_t *lapic_addr;
		lapic_addr = (byte_t *)mman_findunmapped(&mman_kernel,
		                                         HINT_GETADDR(KERNEL_VMHINT_LAPIC),
		                                         mpart_getsize(&x86_lapic_mpart),
		                                         HINT_GETMODE(KERNEL_VMHINT_LAPIC));
		if unlikely(lapic_addr == MAP_FAILED)
			kernel_panic(FREESTR("Failed to map the LAPIC somewhere\n"));
		x86_lapic_mnode.mn_minaddr = lapic_addr;
		x86_lapic_mnode.mn_maxaddr = lapic_addr + x86_lapic_mpart.mp_mem.mc_size * PAGESIZE - 1;
		simple_insert_and_activate(&x86_lapic_mnode, PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
		/* Remember where we mapped the LAPIC */
		x86_lapicbase_ += (uintptr_t)lapic_addr;
	}

	{
		/* Unmap unused memory above the kernel. */
		struct mnode *iter = &x86_kernel_vm_node_free;
		for (;;) {
			void *pagedata_prev_end;
			void *pagedata_next_min;
			size_t num_bytes;
			pagedata_prev_end = mnode_getendaddr(iter);
			iter = mnode_tree_nextnode(iter);
#ifdef __x86_64__
			/* Since the 64-bit page directory identity mapping isn't located
			 * at the end of the kernel address space, we also have to  unmap
			 * memory following the last mapping. */
			if (!iter) {
				pagedata_next_min = (void *)0;
			} else {
				pagedata_next_min = vm_node_getaddr(iter);
			}
#else /* __x86_64__ */
			if (!iter)
				break; /* The previous node should have been `X86_KERNEL_VMMAPPING_IDENTITY_RESERVE' at this point. */
			pagedata_next_min = vm_node_getaddr(iter);
#endif /* !__x86_64__ */
			num_bytes = (size_t)((byte_t *)pagedata_next_min - (byte_t *)pagedata_prev_end);
			if (pagedir_kernelprepare(pagedata_prev_end, num_bytes)) {
				pagedir_unmap(pagedata_prev_end, num_bytes);
				pagedir_kernelunprepare(pagedata_prev_end, num_bytes);
			}
#ifdef __x86_64__
			if (!iter)
				break;
#endif /* !__x86_64__ */
		}
	}

	/* Clear the trampoline mappings of the 3 initial threads.
	 * Before this point, they were (likely) still filled in with the original
	 * physical memory identity mapping containing  the kernel core image,  or
	 * may have also not been mapped at all (in which case this is a no-op)
	 * s.a.: the comment inside of `vm_copyfromphys_noidentity_partial()' in `boot/acpi.c' */
	pagedir_unmap_and_sync_one(FORTASK(&_boottask, this_trampoline));
	pagedir_unmap_and_sync_one(FORTASK(&_bootidle, this_trampoline));
	pagedir_unmap_and_sync_one(FORTASK(&_asyncwork, this_trampoline));
	/* All right! that's our entire kernel VM all cleaned up! */
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_mman_kernel_rdonly)(void) {
	/* Go through all  kernel VM  mappings, and make  everything that's  been
	 * mapped as writable, but should actually be read-only, truly read-only.
	 * This affects the kernel's .text and .rodata section, which  previously
	 * allowed self-modifying code to  replace itself with an  optimized/more
	 * appropriate version. */
	pagedir_map(mnode_getaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_TEXT]),
	            mnode_getsize(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_TEXT]),
	            physpage2addr(x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_CORE_TEXT].mp_mem.mc_start),
	            PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD);
	pagedir_map(mnode_getaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_RODATA]),
	            mnode_getsize(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_RODATA]),
	            physpage2addr(x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_CORE_RODATA].mp_mem.mc_start),
	            PAGEDIR_MAP_FREAD);
	assert(!pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_TEXT])));
	assert(!pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_RODATA])));
#ifdef X86_KERNEL_VMMAPPING_CORE_DATA
	assert(pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA])));
#else /* X86_KERNEL_VMMAPPING_CORE_DATA */
	assert(pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA1])));
	assert(pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA2])));
#endif /* !X86_KERNEL_VMMAPPING_CORE_DATA */
	assert(pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_XDATA])));
#ifdef X86_KERNEL_VMMAPPING_CORE_BSS
	assert(pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS])));
#else /* X86_KERNEL_VMMAPPING_CORE_BSS */
	assert(pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS1])));
	assert(pagedir_iswritable(mnode_getminaddr(&x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS2])));
#endif /* !X86_KERNEL_VMMAPPING_CORE_BSS */

#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	/* Get rid of the page guarding the end of the boot-task stack. */
	if (pagedir_kernelprepareone(__kernel_boottask_stack_guard)) {
		pagedir_unmapone(__kernel_boottask_stack_guard);
		pagedir_kernelunprepareone(__kernel_boottask_stack_guard);
	}
	if (pagedir_kernelprepareone(__kernel_asyncwork_stack_guard)) {
		pagedir_unmapone(__kernel_asyncwork_stack_guard);
		pagedir_kernelunprepareone(__kernel_asyncwork_stack_guard);
	}
	if (pagedir_kernelprepareone(__kernel_bootidle_stack_guard)) {
		pagedir_unmapone(__kernel_bootidle_stack_guard);
		pagedir_kernelunprepareone(__kernel_bootidle_stack_guard);
	}
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
}


/* The actual page ranges that should be released as general-purpose RAM. */
INTDEF byte_t __kernel_pfree_startpage_p[];
INTDEF byte_t __kernel_pfree_endpage_p[];
INTDEF byte_t __kernel_pfree_numpages[];

/* This function can't be made apart of the .free section, because if it was,
 * it could potentially  override itself, crashing  in a spectacular  manner.
 * However, there still is  another place we  can (and are)  able to put  it,
 * that place being  at the  far end  of the  boot cpu's  #DF handler  stack.
 * Under  normal circumstances, early boot should never cause a double fault,
 * and when it does, we probably won't get here, either.
 * And even if we do, this function only gets overwritten when the #DF handler
 * used practically the entirety of its stack.
 * As a trade-off, this function's text cannot be larger than `KERNEL_DF_STACKSIZE'
 * bytes, and should  it ever grow  larger than  that, a linker  error will  occur! */
INTERN ATTR_SECTION(".text.xdata.x86.free_unloader") ATTR_NORETURN
void KCALL x86_kernel_unload_free_and_jump_to_userspace(void) {
#if 1
	vm_node_remove(&vm_kernel, __kernel_free_start);

	/* Unmap the entire .free section (in the kernel page directory)
	 * NOTE: Make sure not to unmap the first couple of pages which
	 *       are now used by the relocated BRK data. */
	if (pagedir_kernelprepare(__kernel_free_start, (size_t)__kernel_free_size)) {
		pagedir_unmap(__kernel_free_start, (size_t)__kernel_free_size);
		pagedir_kernelunprepare(__kernel_free_start, (size_t)__kernel_free_size);
	}

	/* Release all  pages of  the .free  section, as  well as  those
	 * previously used by BRK data to the physical memory allocator. */
	page_free((physpage_t)__kernel_pfree_startpage_p,
	          (size_t)__kernel_pfree_numpages);

	/* TODO: Go through memory information and find the first  `PMEMBANK_TYPE_KFREE'
	 *       bank, then split it into a `PMEMBANK_TYPE_KERNEL' / `PMEMBANK_TYPE_RAM'
	 *       pair, with the first part having a size of `brk_size', while the second
	 *       part uses the remainder as RAM.
	 *       NOTE: If the `PMEMBANK_TYPE_KFREE' bank is smaller than `brk_size',
	 *             extend it beforehand.
	 * TODO: This should be done beforehand by another function that is apart of the
	 *       .free  section.  That way,  we can  keep this  function a  bit smaller! */

	printk("UNLOAD_FREE successfully completed!\n");

	/* TODO: Jump to user-space. */
	for (;;)
		__hlt();
#endif
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MMAN_C */
