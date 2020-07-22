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
#ifdef __INTELLISENSE__
#include "exec-peb.c"
#if defined(__x86_64__) && 1
#define IN_POINTERSIZE 4
#define OU_POINTERSIZE 8
#else
#define IN_POINTERSIZE __SIZEOF_POINTER__
#define OU_POINTERSIZE __SIZEOF_POINTER__
#endif
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#if IN_POINTERSIZE == OU_POINTERSIZE && IN_POINTERSIZE == __SIZEOF_POINTER__
#define MY_VMB_ALLOC_PEB vmb_alloc_peb
#elif IN_POINTERSIZE == OU_POINTERSIZE && IN_POINTERSIZE == 4
#define MY_VMB_ALLOC_PEB vmb_alloc_peb32
#elif IN_POINTERSIZE == OU_POINTERSIZE && IN_POINTERSIZE == 8
#define MY_VMB_ALLOC_PEB vmb_alloc_peb64
#elif OU_POINTERSIZE == 8 && IN_POINTERSIZE == 4
#define MY_VMB_ALLOC_PEB vmb_alloc_peb64_p32
#elif OU_POINTERSIZE == 4 && IN_POINTERSIZE == 8
#define MY_VMB_ALLOC_PEB vmb_alloc_peb32_p64
#else /* OU_POINTERSIZE == ... && IN_POINTERSIZE == ... */
#error "Invalid IN/OU pointer size combination"
#endif /* OU_POINTERSIZE != ... || IN_POINTERSIZE != ... */

#if IN_POINTERSIZE == 4
#define IN_PTR __HYBRID_PTR32
#define IN_UIP uint32_t
#elif IN_POINTERSIZE == 8
#define IN_PTR __HYBRID_PTR64
#define IN_UIP uint64_t
#else /* IN_POINTERSIZE == ... */
#error "Invalid `IN_POINTERSIZE'"
#endif /* IN_POINTERSIZE != ... */

#if OU_POINTERSIZE == 4
#define OU_PTR __HYBRID_PTR32
#define OU_UIP uint32_t
#elif OU_POINTERSIZE == 8
#define OU_PTR __HYBRID_PTR64
#define OU_UIP uint64_t
#else /* OU_POINTERSIZE == ... */
#error "Invalid `OU_POINTERSIZE'"
#endif /* OU_POINTERSIZE == !.. */


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
PUBLIC WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
MY_VMB_ALLOC_PEB(struct vmb *__restrict self,
                 size_t argc_inject, KERNEL char const *const *argv_inject,
                 USER UNCHECKED IN_PTR(char const) USER CHECKED const *argv,
                 USER UNCHECKED IN_PTR(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
#define ATOMIC_READ_IN_CHARP(p) \
	(USER UNCHECKED IN_PTR(char const))ATOMIC_READ(*(IN_UIP *)&(p))
#if OU_POINTERSIZE == __SIZEOF_POINTER__
	typedef struct process_peb peb_t;
#elif OU_POINTERSIZE == 4
	typedef struct process_peb32 peb_t;
#else
	typedef struct process_peb64 peb_t;
#endif
	size_t i;
	size_t argc_user;
	size_t envc_user;
	size_t strings_total_size;
	size_t peb_total_size;
	byte_t *peb_temp_base;
	PAGEDIR_PAGEALIGNED UNCHECKED void *result;
	struct vm_node *stolen_node;
	USER UNCHECKED IN_PTR(char const) string;
	USER UNCHECKED IN_PTR(char const) USER CHECKED const *iter;

again:
	argc_user          = 0;
	envc_user          = 0;
	strings_total_size = 0;

	/* Figure out how much memory we need to allocate */
	for (i = 0; i < argc_inject; ++i)
		strings_total_size += (strlen(argv_inject[i]) + 1) * sizeof(char);
	if likely((iter = argv) != NULL) {
		while ((string = ATOMIC_READ_IN_CHARP(*iter)) != NULL) {
			size_t temp;
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_size, temp, &strings_total_size))
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, (size_t)-1);
			++argc_user;
			++iter;
		}
	}
	if likely((iter = envp) != NULL) {
		while ((string = ATOMIC_READ_IN_CHARP(*iter)) != NULL) {
			size_t temp;
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_size, temp, &strings_total_size))
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, (size_t)-1);
			++envc_user;
			++iter;
		}
	}
	peb_total_size = (offsetafter(peb_t, pp_envp) +
	                  (argc_inject + argc_user + envc_user + 2) * OU_POINTERSIZE +
	                  strings_total_size);
	/* XXX: Check if `peb_total_size' is too large? (>= ARG_MAX) */

	/* Create a temporary kernel-space mapping for initializing the PEB */
	peb_total_size = CEIL_ALIGN(peb_total_size, PAGESIZE);
	peb_temp_base = (byte_t *)vm_map(&vm_kernel,
	                                 HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                                 peb_total_size,
	                                 PAGESIZE,
	                                 HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
	                                 &vm_datablock_anonymous_zero,
	                                 NULL,
	                                 NULL,
	                                 0,
	                                 VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED,
	                                 VM_NODE_FLAG_NORMAL,
	                                 0);
	TRY {
		byte_t *writer;
		USER OU_UIP *peb_argv;
		USER OU_UIP *peb_envp;
		USER peb_t *peb;
		size_t strings_total_copied;

		/* Initialize the PEB. */
		writer   = peb_temp_base + offsetafter(peb_t, pp_envp);
		peb_argv = (USER OU_UIP *)writer;
		writer += (argc_inject + argc_user + 1) * OU_POINTERSIZE;
		peb_envp = (USER OU_UIP *)writer;
		writer += (envc_user + 1) * OU_POINTERSIZE;
		peb = (USER peb_t *)peb_temp_base;
		peb->pp_argc = argc_inject + argc_user;
		peb->pp_argv = (USER OU_PTR(USER OU_PTR(char)))(OU_UIP)(uintptr_t)((byte_t *)peb_argv - (uintptr_t)peb_temp_base);
		peb->pp_envc = envc_user;
		peb->pp_envp = (USER OU_PTR(USER OU_PTR(char)))(OU_UIP)(uintptr_t)((byte_t *)peb_envp - (uintptr_t)peb_temp_base);

		/* Copy strings. */
		strings_total_copied = 0;
		for (i = 0; i < argc_inject; ++i) {
			size_t temp;
			temp = (strlen(argv_inject[i]) + 1) * sizeof(char);
			memcpy(writer, argv_inject[i], temp);
			peb_argv[i] = (OU_UIP)(uintptr_t)(writer - (uintptr_t)peb_temp_base);
			writer += temp;
			strings_total_copied += temp;
		}
		for (i = 0; i < argc_user; ++i) {
			size_t temp;
			string = ATOMIC_READ_IN_CHARP(argv[i]);
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_copied, temp, &strings_total_copied) ||
			            (strings_total_copied > strings_total_size))
				goto string_size_changed;
			memcpy(writer, string, temp);
			peb_argv[argc_inject + i] = (OU_UIP)(uintptr_t)(writer - (uintptr_t)peb_temp_base);
			writer += temp;
		}
		for (i = 0; i < envc_user; ++i) {
			size_t temp;
			string = ATOMIC_READ_IN_CHARP(envp[i]);
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_copied, temp, &strings_total_copied) ||
			            (strings_total_copied > strings_total_size))
				goto string_size_changed;
			memcpy(writer, string, temp);
			peb_envp[i] = (OU_UIP)(uintptr_t)(writer - (uintptr_t)peb_temp_base);
			writer += temp;
		}
		assert(strings_total_copied <= strings_total_size);

		/* If something about the amount of string data changed, start over */
		if unlikely(strings_total_copied > strings_total_size) {
string_size_changed:
			vm_unmap_kernel_ram(peb_temp_base,
			                    peb_total_size,
			                    false);
			goto again;
		}

		/* Figure out where we want to map the PEB within the VM builder. */
		/* TODO: Muse use `KERNEL_VMHINT_USER_PEB' depending on compatibility mode!
		 * >> KERNEL_VMHINT_USER_PEB(32|64) depending on IN_PTR(void)-size */
		result = vmb_getfree(self,
		                     HINT_GETADDR(KERNEL_VMHINT_USER_PEB),
		                     peb_total_size,
		                     PAGESIZE,
		                     HINT_GETMODE(KERNEL_VMHINT_USER_PEB));

		/* Relocate pointers within the PEB to make them absolute */
		peb->pp_argv = (OU_PTR(OU_PTR(char)))((OU_UIP)peb->pp_argv + (OU_UIP)(uintptr_t)result);
		peb->pp_envp = (OU_PTR(OU_PTR(char)))((OU_UIP)peb->pp_envp + (OU_UIP)(uintptr_t)result);
		for (i = 0; i < argc_inject + argc_user; ++i)
			peb_argv[i] += (OU_UIP)(uintptr_t)result;
		for (i = 0; i < envc_user; ++i)
			peb_envp[i] += (OU_UIP)(uintptr_t)result;

		/* Lock the kernel VM, so we can steal the PEB node. */
		sync_write(&vm_kernel);
		/* Ensure that the page directory is prepared to erase the temporary PEB mapping. */
		if unlikely(!pagedir_prepare_map(peb_temp_base, peb_total_size)) {
			sync_endwrite(&vm_kernel);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
	} EXCEPT {
		/* Delete the temporary PEB mapping as general-purpose kernel RAM. */
		vm_unmap_kernel_ram(peb_temp_base,
		                    peb_total_size,
		                    false);
		RETHROW();
	}
	/* Steal the node used to hold the PEB */
	stolen_node = vm_node_remove(&vm_kernel, peb_temp_base);
	/* Delete the temporary PEB mapping, and sync the address range.
	 * NOTE: Since the mapping was strictly private to us,
	 *       there is no need to sync this with another CPU! */
	pagedir_unmap(peb_temp_base, peb_total_size);
	pagedir_sync(peb_temp_base, peb_total_size);
	pagedir_unprepare_map(peb_temp_base, peb_total_size);
	sync_endwrite(&vm_kernel);

	/* Make sure that the PEB node has the expected state. */
	assert(stolen_node);
	assert(vm_node_getstartpageid(stolen_node) == PAGEID_ENCODE(peb_temp_base));
	assert(vm_node_getpagecount(stolen_node) == (peb_total_size / PAGESIZE));
	assert(stolen_node->vn_block == &vm_datablock_anonymous_zero);
	assert(stolen_node->vn_part);
	assert(!isshared(stolen_node->vn_part));
	assert(!wasdestroyed(stolen_node->vn_part));
	assert(!(stolen_node->vn_part->dp_flags & VM_DATAPART_FLAG_KERNPRT));
	assert(stolen_node->vn_part->dp_block == &vm_datablock_anonymous_zero);
	assert(stolen_node->vn_part->dp_srefs == stolen_node);
	assert(stolen_node->vn_part->dp_crefs == NULL);
	assert(stolen_node->vn_link.ln_pself == &stolen_node->vn_part->dp_srefs);
	assert(stolen_node->vn_link.ln_next == NULL);
	assert(stolen_node->vn_guard == 0);
	assert(stolen_node->vn_prot & VM_PROT_READ);
	assert(stolen_node->vn_prot & VM_PROT_WRITE);
	assert(stolen_node->vn_prot & VM_PROT_SHARED);
	assert(!(stolen_node->vn_flags & VM_NODE_FLAG_GROWSUP));
	assert(!(stolen_node->vn_flags & VM_NODE_FLAG_HINTED));
	assert(!(stolen_node->vn_flags & VM_NODE_FLAG_NOMERGE));
	assert(!(stolen_node->vn_flags & VM_NODE_FLAG_KERNPRT));

	/* Delete some unneeded/problematic flags. */
	stolen_node->vn_flags &= ~(VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_PARTITIONED);
	stolen_node->vn_prot = VM_PROT_READ | VM_PROT_WRITE;

	/* Delete the part->node link (no need for locking, since `vn_part' isn't shared) */
	stolen_node->vn_part->dp_srefs = NULL;
#ifndef NDEBUG
	memset(&stolen_node->vn_vm, 0xcc, sizeof(stolen_node->vn_vm));
	memset(&stolen_node->vn_link, 0xcc, sizeof(stolen_node->vn_link));
#endif /* !NDEBUG */

	/* Update the mapping location of the PEB memory node */
	stolen_node->vn_node.a_vmin = PAGEID_ENCODE(result);
	stolen_node->vn_node.a_vmax = PAGEID_ENCODE(result) + (peb_total_size / PAGESIZE) - 1;

	/* Load the stolen node into the VMB */
	vmb_node_insert(self, stolen_node);

	return result;
#undef ATOMIC_READ_IN_CHARP
}

DECL_END

#undef MY_VMB_ALLOC_PEB
#undef OU_PTR
#undef IN_PTR
#undef OU_UIP
#undef IN_UIP
#undef OU_POINTERSIZE
#undef IN_POINTERSIZE
