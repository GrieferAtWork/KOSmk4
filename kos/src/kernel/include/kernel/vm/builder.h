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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_BUILDER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_BUILDER_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <kernel/vm.h>

#include <hybrid/__assert.h>

#include <asm/pageid.h>
#include <compat/config.h> /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/* A small, helper-type for safely constructing and applying a VM state.
 * Mainly intended for constructing a VM state for the purpose of serving
 * an exec() system call.
 * NOTE: This type is meant to be used locally, which is why it doesn't
 *       provide for any sort of locking in and on its own.
 * WARNING: vmb objects are _NOT_ thread-safe! */
struct vmb {
	/* NOTE: Any `struct vm_node' pointed to by `vmb' has
	 *       the following overrides applied to it:
	 *       [OVERRIDE(.vn_vm,[?..?])]:
	 *         - The actual VM of the node isn't yet known (obviously)
	 *       [OVERRIDE(.vn_part,[REF][1..1])]:
	 *         - The node is always bound to some data-part.
	 *       [OVERRIDE(.vn_block,[REF][1..1])]:
	 *         - The node is always bound to some data-block.
	 *       [OVERRIDE(.vn_link,[?..?])]:
	 *         - The node isn't linked as a valid mapping of the part
	 *         - As such, prior to being applied to the target VM, a race condition
	 *           exists where a node's part has been split, causing the node's size
	 *           to no longer match the part's size.
	 *           In this case, prior to actually being applied, more nodes are created
	 *           by `vmb_apply()', in order to ensure that any mapped node results in
	 *           a continuous mapping of memory.
	 */
	ATREE_HEAD(struct vm_node) v_tree;          /* [0..1] Tree of mapped nodes. */
	LLIST(struct vm_node)      v_byaddr;        /* [0..1] By-address ordered list of nodes. */
};

#define VMB_INIT { NULL, LLIST_INIT }

/* Initialize a given VM Builder. */
#ifdef __INTELLISENSE__
LOCAL NOBLOCK void NOTHROW(KCALL vmb_init)(struct vmb *__restrict self);
#else /* __INTELLISENSE__ */
#define vmb_init(self)  ((self)->v_tree = NULL,(self)->v_byaddr = NULL)
#endif /* !__INTELLISENSE__ */

/* Finalize a given VM Builder.
 * NOTE: This function may not be called after a successful call to `vmb_apply()'!
 * >> struct vmb v;
 * >> vmb_init(&v);
 * >> TRY {
 * >>     // Create mappings
 * >>     vmb_paged_map(&v,...);
 * >>     ...
 * >>
 * >>     // Apply mappings
 * >>     vmb_apply(&v,...);
 * >> } EXCEPT {
 * >>     vmb_fini(&v);
 * >>     RETHROW();
 * >> }
 * >> // Don't finalize `v' after `vmb_apply()' has succeeded
 */
FUNDEF NOBLOCK void NOTHROW(KCALL vmb_fini)(struct vmb *__restrict self);



/* Map the memory region into the given VM Builder.
 * @param: prot:   Set of `VM_PROT_*'.
 * @param: flag:   Set of `VM_NODE_FLAG_*'.
 * @param: data_start_vpage: The memory page index where mapping of `data' starts.
 * @param: guard:  If non-zero, repetition limit for a guard mapping.
 *                 Set to 0 if the mapping should include a guard.
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
FUNDEF bool KCALL
vmb_paged_mapat(struct vmb *__restrict self,
                pageid_t page_index, size_t num_pages,
                struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
                vm_vpage64_t data_start_vpage DFL(0),
                uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
                uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
                uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
LOCAL bool KCALL
vmb_mapat(struct vmb *__restrict self,
          PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
          PAGEDIR_PAGEALIGNED size_t num_bytes,
          struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
          PAGEDIR_PAGEALIGNED pos_t data_start_offset DFL(0),
          uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
          uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
          uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	__hybrid_assert((data_start_offset & PAGEMASK) == 0);
	return vmb_paged_mapat(self, PAGEID_ENCODE(addr),
	                 num_bytes / PAGESIZE, data,
	                 (vm_vpage64_t)(data_start_offset / PAGESIZE),
	                 prot, flag, guard);
}


/* Determine a suitable, free memory location for `num_pages'
 * aligned by a multiple of `min_alignment_in_pages' pages.
 * Search happens as follows:
 *   #1: Search according to `VM_GETFREE_ABOVE/VM_GETFREE_BELOW'
 *       Additionally, check for surrounding nodes which are set
 *       up as GUARD nodes. - If such a node is found, it's size
 *       is considered to have reached its maximum potential for
 *       this purpose (limited by how often `vn_guard' can be
 *       decremented, as well as any other memory mapping it may
 *       run into before then)
 *       If a this process yields only a single candidate, that
 *       candidate is returned as result.
 *       If a this process yields more than 1 candidate, the one chosen
 *       depends on `VM_GETFREE_ABOVE / VM_GETFREE_BELOW / VM_GETFREE_ASLR'
 *        - VM_GETFREE_ABOVE: The candidate with the lowest memory address is used
 *        - VM_GETFREE_BELOW: The candidate with the greatest memory address is used
 *        - VM_GETFREE_ABOVE + VM_GETFREE_ASLR:
 *          Return the `x = rand() / RAND_MAX; x*x*NUM_CANDIDATES'th candidate
 *        - VM_GETFREE_BELOW + VM_GETFREE_ASLR:
 *          Return the `x = 1 - (rand() / RAND_MAX); x*x*NUM_CANDIDATES'th candidate
 *   #2: Repeat step #1, but ignore the potentials of GUARD nodes.
 *   #3: Return `VM_PAGED_GETFREE_ERROR'
 * @param: mode:                   Set of `VM_GETFREE_F*'
 * @param: hint:                   A hint used as base when searching for free memory ranges.
 * @param: min_alignment_in_pages: The minimum alignment required from the returned pointer (or `1')
 * @return: VM_PAGED_GETFREE_ERROR:      No more virtual memory available. */
FUNDEF NOBLOCK WUNUSED pageid_t
NOTHROW(KCALL vmb_paged_getfree)(struct vmb *__restrict self,
                                 pageid_t hint, size_t num_pages,
                                 size_t min_alignment_in_pages,
                                 unsigned int mode);
LOCAL NOBLOCK WUNUSED PAGEDIR_PAGEALIGNED UNCHECKED void *
NOTHROW(KCALL vmb_getfree)(struct vmb *__restrict self,
                           PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                           PAGEDIR_PAGEALIGNED size_t min_alignment,
                           unsigned int mode) {
	pageid_t result;
	__hybrid_assert(((uintptr_t)hint & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	__hybrid_assert((min_alignment & PAGEMASK) == 0);
	result = vmb_paged_getfree(self,
	                     PAGEID_ENCODE(hint),
	                     num_bytes / PAGESIZE,
	                     min_alignment / PAGESIZE,
	                     mode);
	return __ARCH_PAGEID_DECODE(result);
}


/* A combination of `vmb_paged_getfree' + `vmb_paged_mapat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target. */
FUNDEF pageid_t KCALL
vmb_paged_map(struct vmb *__restrict self,
              pageid_t hint,
              size_t num_pages,
              size_t min_alignment_in_pages DFL(1),
              unsigned int getfree_mode DFL(VM_GETFREE_ABOVE | VM_GETFREE_ASLR),
              struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
              vm_vpage64_t data_start_vpage DFL(0),
              uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
              uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
              uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
LOCAL PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_map(struct vmb *__restrict self,
        PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
        PAGEDIR_PAGEALIGNED size_t num_bytes,
        PAGEDIR_PAGEALIGNED size_t min_alignment DFL(PAGESIZE),
        unsigned int getfree_mode DFL(VM_GETFREE_ABOVE | VM_GETFREE_ASLR),
        struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
        pos_t data_start_offset DFL(0),
        uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
        uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
        uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	pageid_t result;
	__hybrid_assert(((uintptr_t)hint & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	__hybrid_assert((min_alignment & PAGEMASK) == 0);
	__hybrid_assert((data_start_offset & PAGEMASK) == 0);
	result = vmb_paged_map(self, PAGEID_ENCODE(hint),
	                 num_bytes / PAGESIZE,
	                 min_alignment / PAGESIZE, getfree_mode,
	                 data, (vm_vpage64_t)(data_start_offset / PAGESIZE),
	                 prot, flag, guard);
	return __ARCH_PAGEID_DECODE(result);
}



/* Allocate a PEB (Process Environment Block) within the given VMB,
 * initializing its contents with the strings from the given argv+envp pair.
 * This function is called from `vm_exec()' after the remainder of the application,
 * as well as the dynamic linker have already been loaded into memory.
 * @param: argc_inject: The number of arguments from `argv_inject' to inject
 *                      at the beginning of the user-space argc/argv vector.
 * @param: argv_inject: Vector of arguments to inject at the beginning of
 *                      the user-space argc/argv vector.
 * @param: argv:        User-space pointer to a NULL-terminated vector of argument strings
 * @param: envp:        User-space pointer to a NULL-terminated vector of environment strings
 * @return: * :         Page index of the PEB (to-be passed to the user-space program) */
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_alloc_peb(struct vmb *__restrict self,
              size_t argc_inject, KERNEL char const *const *argv_inject,
              USER UNCHECKED char const *USER CHECKED const *argv,
              USER UNCHECKED char const *USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define vmb_alloc_peb64     vmb_alloc_peb
#define vmb_alloc_peb64_p64 vmb_alloc_peb
#define vmb_alloc_peb32_p32 vmb_alloc_peb32
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_alloc_peb32(struct vmb *__restrict self,
                size_t argc_inject, KERNEL char const *const *argv_inject,
                USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *argv,
                USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_alloc_peb32_p64(struct vmb *__restrict self,
                    size_t argc_inject, KERNEL char const *const *argv_inject,
                    USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *argv,
                    USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_alloc_peb64_p32(struct vmb *__restrict self,
                    size_t argc_inject, KERNEL char const *const *argv_inject,
                    USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *argv,
                    USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define vmb_alloc_peb32     vmb_alloc_peb
#define vmb_alloc_peb64_p64 vmb_alloc_peb64
#define vmb_alloc_peb32_p32 vmb_alloc_peb
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_alloc_peb64(struct vmb *__restrict self,
                size_t argc_inject, KERNEL char const *const *argv_inject,
                USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *argv,
                USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_alloc_peb64_p32(struct vmb *__restrict self,
                    size_t argc_inject, KERNEL char const *const *argv_inject,
                    USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *argv,
                    USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vmb_alloc_peb32_p64(struct vmb *__restrict self,
                    size_t argc_inject, KERNEL char const *const *argv_inject,
                    USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *argv,
                    USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
#else
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif
#endif /* __ARCH_HAVE_COMPAT */


/* Insert the given node into the specified VM Builder */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vmb_node_insert)(struct vmb *__restrict self,
                               struct vm_node *__restrict node);

/* Remove a given node from the specified VM Builder. */
FUNDEF NOBLOCK NONNULL((1)) struct vm_node *
NOTHROW(KCALL vmb_node_remove)(struct vmb *__restrict self,
                               pageid_t page);

/* Get the node associated with the given `page' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct vm_node *
NOTHROW(FCALL vmb_getnodeofpageid)(struct vmb const *__restrict self, pageid_t page);

LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct vm_node *
NOTHROW(FCALL vmb_getnodeofaddress)(struct vmb const *__restrict self, UNCHECKED void *addr) {
	return vmb_getnodeofpageid(self, PAGEID_ENCODE(addr));
}

/* Check if some part of the given address range is currently in use. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL vmb_paged_isused)(struct vmb const *__restrict self,
                                pageid_t min_page,
                                pageid_t max_page);

/* Find the first node with `vm_node_getminpageid(return) >= min_page_index'
 * If no such node exists, return `NULL' instead. */
FUNDEF NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) struct vm_node *
NOTHROW(KCALL vmb_find_first_node_greater_equal)(struct vmb const *__restrict self,
                                                 pageid_t min_page_index);

/* Find the last node with `vm_node_getmaxpageid(return) <= max_page_index'
 * If no such node exists, return `NULL' instead. */
FUNDEF NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) struct vm_node *
NOTHROW(KCALL vmb_find_last_node_lower_equal)(struct vmb const *__restrict self,
                                              pageid_t max_page_index);


struct vm_execinfo_struct;

/* Apply all of the mappings from `self' onto `target', whilst simultaneously deleting
 * any memory mapping still present within `target' (except for the kernel-reserve node)
 * This function is guarantied to operate atomically in a way that allows the caller
 * to assume that no memory mappings (or anything else for that matter) changes if the
 * function fails and returns by throwing an error, and that everything happens exactly
 * as intended if it returns normally.
 * @param: self:   The VM Builder object from which to take mappings to-be applied to `target'
 *                 Upon success, the contents of `self' are left undefined and must either be
 *                 re-initialized, or not be attempted to be finalized.
 * @param: target: The target VM to which to apply the new memory mappings.
 *                 Upon success, this VM will only contain the mappings from `self', with all
 *                 of its old mappings having been deleted.
 *                 NOTE: This argument must not be the kernel VM
 * @param: additional_actions: Additional actions to be atomically performed alongside
 *                 the application of the new memory mappings (set of `VMB_APPLY_AA_*') */
FUNDEF void KCALL
vmb_apply(struct vmb *__restrict self,
          struct vm *__restrict target,
          unsigned int additional_actions,
          struct vm_execinfo_struct *execinfo DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK);
#define VMB_APPLY_AA_NOTHING      0x0000
#define VMB_APPLY_AA_TERMTHREADS  0x0001 /* Terminate all threads using `target', excluding the caller.
                                          * If the calling thread isn't using `target', simply terminate
                                          * all threads that are using `target' */
#define VMB_APPLY_AA_SETEXECINFO  0x0002 /* Set the given `execinfo' for the given VM */



/* Overlay mappings from `self' onto `target'
 * This operation is performed atomically, though will fail if `target'
 * already contains mappings at addressed described by `self'.
 * @return: true:  The overlay was successful.
 * @return: false: The given `target' already contains
 *                 mappings with conflicting address ranges. */
FUNDEF bool KCALL
vmb_overlay(struct vmb *__restrict self,
            struct vm *__restrict target)
		THROWS(E_BADALLOC, E_WOULDBLOCK);


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_BUILDER_H */
