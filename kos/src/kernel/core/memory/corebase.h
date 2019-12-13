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
#ifndef GUARD_KERNEL_SRC_MEMORY_COREBASE_H
#define GUARD_KERNEL_SRC_MEMORY_COREBASE_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/vm.h>

#include <hybrid/sync/atomic-rwlock.h>

DECL_BEGIN

union vm_corepart {
	struct vm_datapart cp_part; /* DATA-part */
	struct vm_node     cp_node; /* NODE-part */
};


#define VM_COREPARTS_PER_PAGE_UNADJUSTED \
	(PAGESIZE / sizeof(union vm_corepart))

struct vm_corepage;
struct vm_corepage_controller {
	/* [0..1][lock(vm_corepage_lock)] Previous corepage.
	 * NOTE: When `NULL', the corepage is either the initial
	 *       one, or doesn't contain any free parts, and also
	 *       isn't apart of the `vm_corepage_head' chain. */
	struct vm_corepage *cpc_prev;
	/* [lock(vm_corepage_lock)] Bitset for corebase parts currently in use (0 = free; 1 = used). */
	uintptr_t           cpc_used[((((VM_COREPARTS_PER_PAGE_UNADJUSTED + 7) / 8) +
	                               (sizeof(void *) - 1)) & ~(sizeof(void *) - 1)) /
	                                sizeof(void *)];
};

#define VM_COREPAIRS_PER_PAGE \
	((PAGESIZE - sizeof(struct vm_corepage_controller)) / sizeof(union vm_corepart))
STATIC_ASSERT_MSG(VM_COREPAIRS_PER_PAGE >= 4,
                  "VM controller structures are too large to sustain themself");

/* A single memory page containing everything required to
 * allocate at least 2 datapart/node pairs (or 4 of either).
 * Must fit into `PAGESIZE' bytes.
 * This way, a corepage can be used to both replicate itself, as
 * well as be used to allocate additional pages for the purposes
 * of general purpose heap.
 * The first corepage is allocated statically, as part of the
 * kernel's .bss */
struct vm_corepage {
	/* The free VM parts of this page. */
	union vm_corepart             cp_parts[VM_COREPAIRS_PER_PAGE];
	/* Page controller. */
	struct vm_corepage_controller cp_ctrl;
};

/* Returns the COREPAGE that a given `x' is apart of. */
#define VM_COREPAGE_OF(x) ((struct vm_corepage *)((uintptr_t)(x) & ~(PAGESIZE - 1)))


/* Core page controller globals. */
INTDEF struct atomic_rwlock vm_corepage_lock; /* Lock for the corepage subsystem. */
INTDEF struct vm_corepage  *vm_corepage_head; /* [1..1] Pointer to the first page containing free elements. */
INTDEF size_t               vm_corepage_free; /* [>= 2] Amount of free parts.
                                               * NOTE: At all times, there must at least be 2 available
                                               *       parts, so-as to allow for self-replication. */

/* Free a `struct vm_datapart' or `struct vm_node', previously
 * allocated using the core pair allocator functions below. */
INTDEF void NOTHROW(KCALL vm_corepage_freepart)(void *__restrict part);



struct vm_corepair_ptr {
	struct vm_datapart *cp_part; /* [1..1] The allocated data part. */
	struct vm_node     *cp_node; /* [1..1] The allocated node. */
};

/* Allocate a new core pair.
 * NOTE: When `nothrow' is true, and the function fails,
 *       the returned corepair contains NULL-pointers.
 * NOTE: Upon success, the returned core pairs are zero-initialized,
 *       with the exception of having their respective core-part flag
 *       bits set to 1.
 * @param: flags: Set of `GFP_*' (Uses `GFP_ATOMIC') */
INTDEF struct vm_corepair_ptr KCALL vm_corepair_alloc(gfp_t flags, bool nothrow);




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_COREBASE_H */
