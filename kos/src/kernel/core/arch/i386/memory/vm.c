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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_VM_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_VM_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/tss.h>
#include <kernel/vm.h>
#include <sched/cpu.h>

#include <hybrid/atomic.h>

#include <asm/intrin.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>


DECL_BEGIN

INTDEF byte_t __kernel_text_startpage[];
INTDEF byte_t __kernel_text_endpage[];
INTDEF byte_t __kernel_text_numpages[];

INTDEF byte_t __kernel_rodata_startpage[];
INTDEF byte_t __kernel_rodata_endpage[];
INTDEF byte_t __kernel_rodata_numpages[];

INTDEF byte_t __kernel_data_startpage[];
INTDEF byte_t __kernel_data_endpage[];
INTDEF byte_t __kernel_data_numpages[];

INTDEF byte_t __kernel_pdata_startpage[];
INTDEF byte_t __kernel_pdata_endpage[];
INTDEF byte_t __kernel_pdata_numpages[];

INTDEF byte_t __kernel_xdata_startpage[];
INTDEF byte_t __kernel_xdata_endpage[];
INTDEF byte_t __kernel_xdata_numpages[];

INTDEF byte_t __kernel_bss_startpage[];
INTDEF byte_t __kernel_bss_endpage[];
INTDEF byte_t __kernel_bss_numpages[];

INTDEF byte_t __kernel_bootiob_startpage[] ASMNAME("__x86_iob_empty_vpageno");

#undef CONFIG_BOOTCPU_IOB_LIES_IN_BSS
#undef CONFIG_BOOTCPU_IOB_LIES_IN_DATA
#ifndef CONFIG_NO_SMP
#define CONFIG_BOOTCPU_IOB_LIES_IN_BSS 1
#else /* !CONFIG_NO_SMP */
#define CONFIG_BOOTCPU_IOB_LIES_IN_DATA 1
#endif /* CONFIG_NO_SMP */



/* The first mapping: a single page not mapped to anything, located at `0xc0000000'.
 * This page is used to ensure that iterating through user-memory can always be done
 * safely, after only the starting pointer has been checked, so long as at least 1
 * byte is read for every 4096 bytes being advanced. */
#define X86_KERNEL_VMMAPPING_CORE_TEXT        0 /* .text */
#define X86_KERNEL_VMMAPPING_CORE_RODATA      1 /* .rodata */
#ifdef CONFIG_BOOTCPU_IOB_LIES_IN_BSS
#define X86_KERNEL_VMMAPPING_CORE_DATA        2 /* .data */
#define X86_KERNEL_VMMAPPING_CORE_XDATA       3 /* .xdata / .xbss */
#define X86_KERNEL_VMMAPPING_CORE_BSS1        4 /* .bss */
#define X86_KERNEL_VMMAPPING_CORE_BSS2        5 /* .bss */
INTDEF byte_t __x86_kernel_bss_before_iob_pages[];
INTDEF byte_t __x86_kernel_bss_after_iob_pages[];
#define __kernel_bss1_startpage  __kernel_bss_startpage
#define __kernel_bss1_endpage    __kernel_bootiob_startpage
#define __kernel_bss1_numpages   __x86_kernel_bss_before_iob_pages
#define __kernel_bss2_startpage  (__kernel_bootiob_startpage + 2) /* 2: Number of pages in TSS.IOB */
#define __kernel_bss2_endpage    __kernel_bss_endpage
#define __kernel_bss2_numpages   (__x86_kernel_bss_after_iob_pages - 2)
#else /* CONFIG_BOOTCPU_IOB_LIES_IN_BSS */
#define X86_KERNEL_VMMAPPING_CORE_DATA1       2 /* .data */
#define X86_KERNEL_VMMAPPING_CORE_DATA2       3 /* .data */
#define X86_KERNEL_VMMAPPING_CORE_XDATA       4 /* .xdata / .xbss */
#define X86_KERNEL_VMMAPPING_CORE_BSS         5 /* .bss */
INTDEF byte_t __x86_kernel_data_before_iob_pages[];
INTDEF byte_t __x86_kernel_data_after_iob_pages[];
#define __kernel_data1_startpage  __kernel_data_startpage
#define __kernel_data1_endpage    __kernel_bootiob_startpage
#define __kernel_data1_numpages   __x86_kernel_data_before_iob_pages
#define __kernel_data2_startpage  (__kernel_bootiob_startpage + 2) /* 2: Number of pages in TSS.IOB */
#define __kernel_data2_endpage    __kernel_data_endpage
#define __kernel_data2_numpages   (__x86_kernel_data_after_iob_pages - 2)
#endif /* !CONFIG_BOOTCPU_IOB_LIES_IN_BSS */
#define X86_KERNEL_VMMAPPING_IDENTITY_RESERVE 6 /* A memory reservation made for the page directory identity mapping. */



INTDEF struct vm_datapart x86_kernel_vm_parts[];
INTDEF struct vm_node x86_kernel_vm_nodes[];
INTDEF struct vm_node x86_vmnode_transition_reserve;


#define INIT_DATAPART(self, dp_srefs_, startpage, numpages)                                      \
	{                                                                                            \
		/* .dp_refcnt = */ 2, /* 2 == 1(myself) + 1(node) */                                     \
		/* .dp_lock   = */ SHARED_RWLOCK_INIT,                                                   \
		{                                                                                        \
			/* .dp_tree_ptr = */ { NULL, NULL, 0, (size_t)(numpages) - 1 }                       \
		},                                                                                       \
		/* .dp_crefs = */ LLIST_INIT,                                                            \
		/* .dp_srefs = */ dp_srefs_,                                                             \
		/* .dp_stale = */ NULL,                                                                  \
		/* .dp_block = */ &vm_datablock_anonymous,                                               \
		/* .dp_flags = */ VM_DATAPART_FLAG_KERNPRT | VM_DATAPART_FLAG_HEAPPPP,                   \
		/* .dp_state = */ VM_DATAPART_STATE_LOCKED,                                              \
		{                                                                                        \
			/* .dp_ramdata = */ {                                                                \
				/* .rd_blockv = */ &(self).dp_ramdata.rd_block0,                                 \
				{                                                                                \
					/* .rd_block0 = */ {                                                         \
						/* .rb_start = */ (vm_ppage_t)(uintptr_t)(startpage) - KERNEL_BASE_PAGE, \
						/* .rb_size  = */ (size_t)(numpages)                                     \
					}                                                                            \
				}                                                                                \
			}                                                                                    \
		}                                                                                        \
	}

INTERN struct vm_datapart x86_kernel_vm_parts[6] = {
#define DO_INIT_DATAPART(id, startpage, numpages) \
	INIT_DATAPART(x86_kernel_vm_parts[id], &x86_kernel_vm_nodes[id], startpage, numpages)
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_TEXT, __kernel_text_startpage, __kernel_text_numpages),
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_RODATA, __kernel_rodata_startpage, __kernel_rodata_numpages),
#ifdef X86_KERNEL_VMMAPPING_CORE_DATA
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_DATA, __kernel_data_startpage, __kernel_data_numpages),
#else /* X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_DATA1, __kernel_data1_startpage, __kernel_data1_numpages),
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_DATA2, __kernel_data2_startpage, __kernel_data2_numpages),
#endif /* !X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_XDATA, __kernel_xdata_startpage, __kernel_xdata_numpages),
#ifdef X86_KERNEL_VMMAPPING_CORE_BSS
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_BSS, __kernel_bss_startpage, __kernel_bss_numpages),
#else /* X86_KERNEL_VMMAPPING_CORE_BSS */
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_BSS1, __kernel_bss1_startpage, __kernel_bss1_numpages),
	DO_INIT_DATAPART(X86_KERNEL_VMMAPPING_CORE_BSS2, __kernel_bss2_startpage, __kernel_bss2_numpages),
#endif /* !X86_KERNEL_VMMAPPING_CORE_BSS */
#undef DO_INIT_DATAPART
};


#define INIT_NODE_RESERVE(self, min, max, prot, part)                                           \
	{                                                                                           \
		/* .vn_node   = */ { NULL, NULL, min, max },                                            \
		/* .vn_byaddr = */ LLIST_INITNODE,                                                      \
		/* .vn_prot   = */ prot | VM_PROT_SHARED,                                               \
		/* .vn_flags  = */ VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_KERNPRT, \
		/* .vn_vm     = */ &vm_kernel,                                                          \
		/* .vn_part   = */ NULL,                                                                \
		/* .vn_block  = */ NULL,                                                                \
		/* .vn_link   = */ LLIST_INITNODE,                                                      \
		/* .vn_guard  = */ 0                                                                    \
	}
#define INIT_NODE(self, min, max, prot, part)                                                   \
	{                                                                                           \
		/* .vn_node   = */ { NULL, NULL, min, max },                                            \
		/* .vn_byaddr = */ LLIST_INITNODE,                                                      \
		/* .vn_prot   = */ prot | VM_PROT_SHARED,                                               \
		/* .vn_flags  = */ VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_KERNPRT, \
		/* .vn_vm     = */ &vm_kernel,                                                          \
		/* .vn_part   = */ &(part),                                                             \
		/* .vn_block  = */ &vm_datablock_anonymous,                                             \
		/* .vn_link   = */ { NULL, &LLIST_HEAD((part).dp_srefs) },                              \
		/* .vn_guard  = */ 0                                                                    \
	}


INTERN struct vm_node x86_vmnode_transition_reserve =
	INIT_NODE_RESERVE(x86_vmnode_transition_reserve,
	                 (vm_vpage_t)KERNEL_BASE_PAGE,
	                 (vm_vpage_t)KERNEL_BASE_PAGE,
	                  VM_PROT_NONE,
	                  kernel_vm_single_reserved_page);

INTERN struct vm_node x86_kernel_vm_nodes[8] = {
#define DO_INIT_NODE(id, startpage, endpage, prot) \
	INIT_NODE(x86_kernel_vm_nodes[id],             \
	          (vm_vpage_t)(uintptr_t)(startpage),  \
	          (vm_vpage_t)(uintptr_t)(endpage)-1,  \
	          prot,                                \
	          x86_kernel_vm_parts[id])
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_TEXT, __kernel_text_startpage, __kernel_text_endpage, VM_PROT_READ | VM_PROT_EXEC),
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_RODATA, __kernel_rodata_startpage, __kernel_rodata_endpage, VM_PROT_READ),
#ifdef X86_KERNEL_VMMAPPING_CORE_DATA
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_DATA, __kernel_data_startpage, __kernel_data_endpage, VM_PROT_READ | VM_PROT_WRITE),
#else /* X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_DATA1, __kernel_data1_startpage, __kernel_data1_endpage, VM_PROT_READ | VM_PROT_WRITE),
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_DATA2, __kernel_data2_startpage, __kernel_data2_endpage, VM_PROT_READ | VM_PROT_WRITE),
#endif /* !X86_KERNEL_VMMAPPING_CORE_DATA */
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_XDATA, __kernel_xdata_startpage, __kernel_xdata_endpage, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC),
#ifdef X86_KERNEL_VMMAPPING_CORE_BSS
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_BSS, __kernel_bss_startpage, __kernel_bss_endpage, VM_PROT_READ | VM_PROT_WRITE),
#else /* X86_KERNEL_VMMAPPING_CORE_BSS */
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_BSS1, __kernel_bss1_startpage, __kernel_bss1_endpage, VM_PROT_READ | VM_PROT_WRITE),
	DO_INIT_NODE(X86_KERNEL_VMMAPPING_CORE_BSS2, __kernel_bss2_startpage, __kernel_bss2_endpage, VM_PROT_READ | VM_PROT_WRITE),
#endif /* !X86_KERNEL_VMMAPPING_CORE_BSS */
#undef DO_INIT_NODE

	/* [X86_KERNEL_VMMAPPING_IDENTITY_RESERVE] = */
#ifdef X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE
		INIT_NODE_RESERVE(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE],
		                  (vm_vpage_t)0, /* Calculated below */
		                  (vm_vpage_t)0, /* Calculated below */
		                  VM_PROT_NONE,
		                  x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE]),
#else /* X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE */
		INIT_NODE_RESERVE(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE],
		                  (vm_vpage_t)(X86_VM_KERNEL_PDIR_RESERVED_BASE / PAGESIZE), /* TODO: This needs to be dynamically selected based on PAE-support */
		                  (vm_vpage_t)(X86_VM_KERNEL_PDIR_RESERVED_BASE + X86_VM_KERNEL_PDIR_RESERVED_SIZE - PAGESIZE) / PAGESIZE,
		                  VM_PROT_NONE,
		                  x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE]),
#endif /* !X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE */
};

/* The components for the PADDR=VADDR sections, also known as the .pdata sections. */
INTDEF struct vm_datapart x86_vm_part_pdata;
INTDEF struct vm_node x86_vm_node_pdata;

INTERN struct vm_datapart x86_vm_part_pdata =
	INIT_DATAPART(x86_vm_part_pdata, &x86_vm_node_pdata,
	              __kernel_pdata_startpage, __kernel_pdata_numpages);
INTERN struct vm_node x86_vm_node_pdata =
	INIT_NODE(x86_vm_node_pdata,
	          (vm_vpage_t)((uintptr_t)__kernel_pdata_startpage - KERNEL_BASE_PAGE),
	          (vm_vpage_t)((uintptr_t)__kernel_pdata_endpage - (KERNEL_BASE_PAGE + 1)),
	           VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC,
	           x86_vm_part_pdata);



/* The components for initializing the initial mapping of the .free section.
 * These are handled on their own, as they are part of the .free section, thus
 * allowing them to be deleted once .free gets removed. */
INTDEF struct vm_datapart x86_kernel_vm_part_free;
INTDEF struct vm_node x86_kernel_vm_node_free;

INTDEF byte_t __kernel_free_startpage[];
INTDEF byte_t __kernel_free_endpage[];
INTDEF byte_t __kernel_free_numpages[];

INTERN ATTR_FREEDATA struct vm_datapart x86_kernel_vm_part_free =
	INIT_DATAPART(x86_kernel_vm_part_free, &x86_kernel_vm_node_free,
	              __kernel_free_startpage, __kernel_free_numpages);
INTERN ATTR_FREEDATA struct vm_node x86_kernel_vm_node_free =
	INIT_NODE(x86_kernel_vm_node_free,
	          (vm_vpage_t)((uintptr_t)__kernel_free_startpage),
	          (vm_vpage_t)((uintptr_t)__kernel_free_endpage - 1),
	          VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC,
	          x86_kernel_vm_part_free);


INTDEF struct vm_datapart kernel_vm_part_pagedata;
INTDEF struct vm_node kernel_vm_node_pagedata;
INTERN struct vm_datapart kernel_vm_part_pagedata =
	INIT_DATAPART(kernel_vm_part_pagedata, &kernel_vm_node_pagedata,
	              0 /* Filled later */, 0 /* Filled later */);
INTERN struct vm_node kernel_vm_node_pagedata =
	INIT_NODE(kernel_vm_node_pagedata, 0, 0,
	          VM_PROT_READ | VM_PROT_WRITE,
	          kernel_vm_part_pagedata);

INTDEF struct vm_datapart x86_vm_part_lapic;
INTDEF struct vm_node x86_vm_node_lapic;
INTERN struct vm_datapart x86_vm_part_lapic =
	INIT_DATAPART(x86_vm_part_lapic, &x86_vm_node_lapic,
	              0 /* (possibly) Filled later */,
	              0 /* (possibly) Filled later */);
INTERN struct vm_node x86_vm_node_lapic =
	INIT_NODE(x86_vm_node_lapic, 0, 0,
	          VM_PROT_READ | VM_PROT_WRITE,
	          x86_vm_part_lapic);



STATIC_ASSERT(VM_PROT_EXEC  == PAGEDIR_MAP_FEXEC);
STATIC_ASSERT(VM_PROT_WRITE == PAGEDIR_MAP_FWRITE);
STATIC_ASSERT(VM_PROT_READ  == PAGEDIR_MAP_FREAD);

INTDEF byte_t __kernel_boottask_stack_guard[];

PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL simple_insert_and_activate)(struct vm_node *__restrict node,
                                          u16 prot) {
	struct vm_datapart *part;
	assert(node->vn_vm == &vm_kernel);
	assertf(node->vn_part->dp_ramdata.rd_blockv == &node->vn_part->dp_ramdata.rd_block0,
	        "node->vn_part->dp_ramdata.rd_blockv  = %p\n"
	        "&node->vn_part->dp_ramdata.rd_block0 = %p\n",
	        node->vn_part->dp_ramdata.rd_blockv,
	        &node->vn_part->dp_ramdata.rd_block0);
	vm_node_insert(node);
	part = node->vn_part;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare_map(node->vn_node.a_vmin,
	                         part->dp_ramdata.rd_block0.rb_start)) {
		kernel_panic(FREESTR("Failed to prepare kernel mapping at %p...%p\n"),
		             (uintptr_t)VM_PAGE2ADDR(node->vn_node.a_vmin),
		             (uintptr_t)VM_PAGE2ADDR(node->vn_node.a_vmin + part->dp_ramdata.rd_block0.rb_start) - 1);
	}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_map(node->vn_node.a_vmin,
	            part->dp_ramdata.rd_block0.rb_size,
	            part->dp_ramdata.rd_block0.rb_start,
	            prot);
	assertf(part->dp_ramdata.rd_blockv == &part->dp_ramdata.rd_block0,
	        "part->dp_ramdata.rd_blockv  = %p\n"
	        "&part->dp_ramdata.rd_block0 = %p\n",
	        part->dp_ramdata.rd_blockv,
	        &part->dp_ramdata.rd_block0);
}


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

DATDEF VIRT byte_t volatile *_x86_lapicbase ASMNAME("x86_lapicbase");


INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_kernel_vm)(void) {
#ifdef X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE
	{
		/* Calculate the PDIR Identity reservation at runtime. */
		vm_vpage_t min = (vm_vpage_t)(X86_VM_KERNEL_PDIR_RESERVED_BASE / PAGESIZE);
		vm_vpage_t max = (vm_vpage_t)(X86_VM_KERNEL_PDIR_RESERVED_BASE +
		                              X86_VM_KERNEL_PDIR_RESERVED_SIZE -
		                              PAGESIZE) /
		                 PAGESIZE;
		x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE].vn_node.a_vmin = min;
		x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_IDENTITY_RESERVE].vn_node.a_vmax = max;
	}
#endif /* X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE */

	/* Unmap everything before the kernel. */
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (pagedir_prepare_map((vm_vpage_t)KERNEL_BASE_PAGE,
	                        ((uintptr_t)__kernel_text_startpage - KERNEL_BASE_PAGE)))
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	{
		pagedir_unmap((vm_vpage_t)KERNEL_BASE_PAGE,
		              ((uintptr_t)__kernel_text_startpage - KERNEL_BASE_PAGE));
	}
	assert(kernel_vm_node_pagedata.vn_node.a_vmin != 0);

	/* Insert kernel-space memory nodes into the kernel VM, and re-map memory as needed. */
	vm_node_insert(&x86_vmnode_transition_reserve);
	/* NOTE: Map the .text and .rodata sections as writable for now, so-as to allow initialization
	 *       code to modify itself, as well as otherwise constant data structures. */
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
	vm_node_insert(&kernel_vm_node_pagedata);

	/* Insert the mapping for the physical identity (.pdata) section.
	 * The contents of this section are mainly required for SMP initialization,
	 * though can also be used for other things that require being placed at a
	 * known physical memory location. */
	if (!pagedir_prepare_map((vm_vpage_t)__kernel_pdata_startpage - KERNEL_BASE_PAGE,
	                         (size_t)__kernel_pdata_numpages))
		kernel_panic(FREESTR("Failed to prepare kernel VM for mapping .pdata\n"));
	simple_insert_and_activate(&x86_vm_node_pdata, PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
#ifndef NDEBUG
	{
		u32 virt_word, phys_word;
		virt_word = *(u32 *)VM_PAGE2ADDR((vm_vpage_t)__kernel_pdata_startpage);
		phys_word = *(u32 *)VM_PAGE2ADDR((vm_vpage_t)__kernel_pdata_startpage - KERNEL_BASE_PAGE);
		assert(virt_word == phys_word);
	}
#endif /* !NDEBUG */

	/* Map the LAPIC into the kernel VM. */
	if (x86_vm_part_lapic.dp_tree.a_vmax >= x86_vm_part_lapic.dp_tree.a_vmin) {
		assert(vm_datapart_numdpages(&x86_vm_part_lapic) ==
		       x86_vm_part_lapic.dp_ramdata.rd_block0.rb_size);
		x86_vm_node_lapic.vn_node.a_vmin = vm_getfree(&vm_kernel,
		                                                (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_LAPIC),
		                                                vm_datapart_numdpages(&x86_vm_part_lapic), 1,
		                                                HINT_GETMODE(KERNEL_VMHINT_LAPIC));
		if unlikely(x86_vm_node_lapic.vn_node.a_vmin == VM_GETFREE_ERROR)
			kernel_panic(FREESTR("Failed to map the LAPIC somewhere\n"));
		x86_vm_node_lapic.vn_node.a_vmax = x86_vm_node_lapic.vn_node.a_vmin;
		x86_vm_node_lapic.vn_node.a_vmax += vm_datapart_numdpages(&x86_vm_part_lapic) - 1;
		simple_insert_and_activate(&x86_vm_node_lapic,
		                           PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
		/* Remember where we mapped the LAPIC */
		_x86_lapicbase += (uintptr_t)VM_PAGE2ADDR(x86_vm_node_lapic.vn_node.a_vmin);
	}

	{
		/* Unmap unused memory above the kernel. */
		struct vm_node *iter = &x86_kernel_vm_node_free;
		for (;;) {
			vm_vpage_t pagedata_prev_end;
			vm_vpage_t pagedata_next_min;
			pagedata_prev_end = VM_NODE_END(iter);
			iter = iter->vn_byaddr.ln_next;
			if (!iter)
				break; /* The previous node should have been `X86_KERNEL_VMMAPPING_IDENTITY_RESERVE' at this point. */
			pagedata_next_min = VM_NODE_MIN(iter);
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (pagedir_prepare_map(pagedata_prev_end, (size_t)(pagedata_next_min - pagedata_prev_end)))
				pagedir_unmap(pagedata_prev_end, (size_t)(pagedata_next_min - pagedata_prev_end));
#else /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			pagedir_unmap(pagedata_prev_end, (size_t)(pagedata_next_min - pagedata_prev_end));
#endif /* !CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		}
	}
	/* All right! that's our entire kernel VM all cleaned up! */
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_kernel_vm_readonly)(void) {
	/* Go through all kernel VM mappings, and make everything that's been
	 * mapped as writable, but should actually be read-only, truly read-only.
	 * This affects the kernel's .text and .rodata section, which previously
	 * allowed self-modifying code to replace itself with an optimized/more
	 * appropriate version. */
	pagedir_map(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_TEXT].vn_node.a_vmin,
	            x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_CORE_TEXT].dp_ramdata.rd_block0.rb_size,
	            x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_CORE_TEXT].dp_ramdata.rd_block0.rb_start,
	            PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD);
	pagedir_map(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_RODATA].vn_node.a_vmin,
	            x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_CORE_RODATA].dp_ramdata.rd_block0.rb_size,
	            x86_kernel_vm_parts[X86_KERNEL_VMMAPPING_CORE_RODATA].dp_ramdata.rd_block0.rb_start,
	            PAGEDIR_MAP_FREAD);
	assert(!pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_TEXT].vn_node.a_vmin));
	assert(!pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_RODATA].vn_node.a_vmin));
#ifdef X86_KERNEL_VMMAPPING_CORE_DATA
	assert(pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA].vn_node.a_vmin));
#else /* X86_KERNEL_VMMAPPING_CORE_DATA */
	assert(pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA1].vn_node.a_vmin));
	assert(pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_DATA2].vn_node.a_vmin));
#endif /* !X86_KERNEL_VMMAPPING_CORE_DATA */
	assert(pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_XDATA].vn_node.a_vmin));
#ifdef X86_KERNEL_VMMAPPING_CORE_BSS
	assert(pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS].vn_node.a_vmin));
#else /* X86_KERNEL_VMMAPPING_CORE_BSS */
	assert(pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS1].vn_node.a_vmin));
	assert(pagedir_iswritable(x86_kernel_vm_nodes[X86_KERNEL_VMMAPPING_CORE_BSS2].vn_node.a_vmin));
#endif /* !X86_KERNEL_VMMAPPING_CORE_BSS */

	/* Get rid of the page guarding the end of the boot-task stack. */
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (pagedir_prepare_mapone((vm_vpage_t)__kernel_boottask_stack_guard))
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	{
		pagedir_unmapone((vm_vpage_t)__kernel_boottask_stack_guard);
	}
}


/* The actual page ranges that should be released as general-purpose RAM. */
INTDEF byte_t __kernel_pfree_startpage[];
INTDEF byte_t __kernel_pfree_endpage[];
INTDEF byte_t __kernel_pfree_numpages[];

/* This function can't be made apart of the .free section, because if it was,
 * it could potentially override itself, crashing in a spectacular manner.
 * However, there still is another place we can (and are) able to put it,
 * that place being at the far end of the boot cpu's #DF handler stack.
 * Under normal circumstances, early boot should never cause a double fault,
 * and when it does, we probably won't get here, either.
 * And even if we do, this function only gets overwritten when the #DF handler
 * used practically the entirety of its stack.
 * As a trade-off, this function's text cannot be larger than `KERNEL_DF_STACKSIZE'
 * bytes, and should it ever grow larger than that, a linker error will occur! */
INTERN ATTR_SECTION(".text.xdata.x86.free_unloader") ATTR_NORETURN
void KCALL x86_kernel_unload_free_and_jump_to_userspace(void) {
#if 1
	vm_node_remove(&vm_kernel, (vm_vpage_t)__kernel_free_startpage);

	/* Unmap the entire .free section (in the kernel page directory)
	 * NOTE: Make sure not to unmap the first couple of pages which
	 *       are now used by the relocated BRK data. */
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (pagedir_prepare_map((vm_vpage_t)__kernel_free_startpage,
	                        (size_t)__kernel_free_numpages))
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	{
		pagedir_unmap((vm_vpage_t)__kernel_free_startpage,
		              (size_t)__kernel_free_numpages);
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		pagedir_unprepare_map((vm_vpage_t)__kernel_free_startpage,
		                      (size_t)__kernel_free_numpages);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	}

	/* Release all pages of the .free section, as well as those
	 * previously used by BRK data to the physical memory allocator. */
	page_free((pageptr_t)((vm_vpage_t)__kernel_pfree_startpage - KERNEL_CORE_PAGE),
	          (size_t)__kernel_pfree_numpages);

	/* TODO: Go through memory information and find the first `PMEMBANK_TYPE_KFREE'
	 *       bank, then split it into a `PMEMBANK_TYPE_KERNEL' / `PMEMBANK_TYPE_RAM'
	 *       pair, with the first part having a size of `brk_size', while the second
	 *       part uses the remainder as RAM.
	 *       NOTE: If the `PMEMBANK_TYPE_KFREE' bank is smaller than `brk_size',
	 *             extend it beforehand.
	 * TODO: This should be done beforehand by another function that is apart of the
	 *       .free section. That way, we can keep this function a bit smaller! */

	printk("UNLOAD_FREE successfully completed!\n");

	/* TODO: Jump to user-space. */
	for (;;)
		__hlt();
#endif
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_VM_C */
