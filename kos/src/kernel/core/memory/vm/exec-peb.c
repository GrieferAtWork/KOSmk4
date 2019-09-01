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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_EXEC_PEB_C
#define GUARD_KERNEL_SRC_MEMORY_VM_EXEC_PEB_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/vm/builder.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/process.h>

#include <stddef.h>
#include <string.h>

#define HINT_ADDR(x,y) x
#define HINT_MODE(x,y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


DECL_BEGIN

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
PUBLIC WUNUSED NONNULL((1)) vm_vpage_t KCALL
vmb_alloc_peb(struct vmb *__restrict self,
              size_t argc_inject, KERNEL char const *const *argv_inject,
              USER UNCHECKED char const *USER CHECKED const *argv,
              USER UNCHECKED char const *USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	size_t i;
	size_t argc_user;
	size_t envc_user;
	size_t strings_total_size;
	size_t peb_total_size;
	size_t peb_total_pages;
	byte_t *peb_temp_base;
	vm_vpage_t peb_temp_page;
	vm_vpage_t result;
	struct vm_node *stolen_node;
	USER UNCHECKED char const *string;
	USER UNCHECKED char const *USER CHECKED const *iter;

again:
	argc_user          = 0;
	envc_user          = 0;
	strings_total_size = 0;

	/* Figure out how much memory we need to allocate */
	for (i = 0; i < argc_inject; ++i)
		strings_total_size += (strlen(argv_inject[i]) + 1) * sizeof(char);
	if likely((iter = argv) != NULL) {
		while ((string = ATOMIC_READ(*iter)) != NULL) {
			size_t temp;
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_size, temp, &strings_total_size))
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, VM_VPAGE_MAX);
			++argc_user;
			++iter;
		}
	}
	if likely((iter = envp) != NULL) {
		while ((string = ATOMIC_READ(*iter)) != NULL) {
			size_t temp;
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_size, temp, &strings_total_size))
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, VM_VPAGE_MAX);
			++envc_user;
			++iter;
		}
	}
	peb_total_size = (offsetafter(struct process_peb, pp_envp) +
	                  (argc_inject + argc_user + envc_user + 2) * sizeof(USER char *) +
	                  strings_total_size);
	/* XXX: Check if `peb_total_size' is too large? */

	/* Create a temporary kernel-space mapping for initializing the PEB */
	peb_total_pages = CEILDIV(peb_total_size, PAGESIZE);
	peb_temp_page = vm_map(&vm_kernel,
	                       (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                       peb_total_pages,
	                       1,
	                       HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
	                       &vm_datablock_anonymous_zero,
	                       0,
	                       VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED,
	                       VM_NODE_FLAG_NORMAL,
	                       0);
	peb_temp_base = (byte_t *)VM_PAGE2ADDR(peb_temp_page);
	TRY {
		byte_t *writer;
		size_t i;
		USER uintptr_t *peb_argv;
		USER uintptr_t *peb_envp;
		size_t strings_total_copied;

		/* Initialize the PEB. */
		writer   = peb_temp_base + offsetafter(struct process_peb, pp_envp);
		peb_argv = (USER uintptr_t *)writer;
		writer += (argc_inject + argc_user + 1) * sizeof(USER char *);
		peb_envp = (USER uintptr_t *)writer;
		writer += (envc_user + 1) * sizeof(USER char *);
		((struct process_peb *)peb_temp_base)->pp_argc                = argc_inject + argc_user;
		*(uintptr_t *)&((struct process_peb *)peb_temp_base)->pp_argv = (uintptr_t)peb_argv - (uintptr_t)peb_temp_base;
		((struct process_peb *)peb_temp_base)->pp_envc                = envc_user;
		*(uintptr_t *)&((struct process_peb *)peb_temp_base)->pp_envp = (uintptr_t)peb_envp - (uintptr_t)peb_temp_base;

		/* Copy strings. */
		strings_total_copied = 0;
		for (i = 0; i < argc_inject; ++i) {
			size_t temp;
			temp = (strlen(argv_inject[i]) + 1) * sizeof(char);
			memcpy(writer, argv_inject[i], temp);
			peb_argv[i] = (uintptr_t)writer - (uintptr_t)peb_temp_base;
			writer += temp;
			strings_total_copied += temp;
		}
		for (i = 0; i < argc_user; ++i) {
			size_t temp;
			string = ATOMIC_READ(argv[i]);
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_copied, temp, &strings_total_copied) ||
			            (strings_total_copied > strings_total_size))
				goto string_size_changed;
			memcpy(writer, string, temp);
			peb_argv[argc_inject + i] = (uintptr_t)writer - (uintptr_t)peb_temp_base;
			writer += temp;
		}
		for (i = 0; i < envc_user; ++i) {
			size_t temp;
			string = ATOMIC_READ(envp[i]);
			validate_readable(string, 1);
			temp = (strlen(string) + 1) * sizeof(char);
			if unlikely(OVERFLOW_UADD(strings_total_copied, temp, &strings_total_copied) ||
			            (strings_total_copied > strings_total_size))
				goto string_size_changed;
			memcpy(writer, string, temp);
			peb_envp[i] = (uintptr_t)writer - (uintptr_t)peb_temp_base;
			writer += temp;
		}
		assert(strings_total_copied <= strings_total_size);

		/* If something about the amount of string data changed, start over */
		if unlikely(strings_total_copied > strings_total_size) {
string_size_changed:
			vm_unmap_kernel_ram(peb_temp_page,
			                    peb_total_pages,
			                    false);
			goto again;
		}

		/* Figure out where we want to map the PEB within the VM builder. */
		result = vmb_getfree(self,
		                     (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_USER_PEB),
		                     peb_total_pages,
		                     1,
		                     HINT_GETMODE(KERNEL_VMHINT_USER_PEB));

		{
			uintptr_t relbase;
			relbase = (uintptr_t)VM_PAGE2ADDR(result);
			/* Relocate pointers within the PEB to make them absolute */
			*(uintptr_t *)&((struct process_peb *)peb_temp_base)->pp_argv += relbase;
			*(uintptr_t *)&((struct process_peb *)peb_temp_base)->pp_envp += relbase;
			for (i = 0; i < argc_inject + argc_user; ++i)
				peb_argv[i] += relbase;
			for (i = 0; i < envc_user; ++i)
				peb_envp[i] += relbase;
		}

		/* Lock the kernel VM, so we can steal the PEB node. */
		sync_write(&vm_kernel);
		/* Ensure that the page directory is prepared to erase the temporary PEB mapping. */
		if unlikely(!pagedir_prepare_map(peb_temp_page, peb_total_pages)) {
			sync_endwrite(&vm_kernel);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
		}
	} EXCEPT {
		/* Delete the temporary PEB mapping as general-purpose kernel RAM. */
		vm_unmap_kernel_ram(peb_temp_page,
		                    peb_total_pages,
		                    false);
		RETHROW();
	}
	/* Steal the node used to hold the PEB */
	stolen_node = vm_node_remove(&vm_kernel, peb_temp_page);
	/* Delete the temporary PEB mapping, and sync the address range.
	 * NOTE: Since the mapping was strictly private to us,
	 *       there is no need to sync this with another CPU! */
	pagedir_unmap(peb_temp_page, peb_total_pages);
	pagedir_sync(peb_temp_page, peb_total_pages);
	pagedir_unprepare_map(peb_temp_page, peb_total_pages);
	sync_endwrite(&vm_kernel);

	/* Make sure that the PEB node has the expected state. */
	assert(stolen_node);
	assert(VM_NODE_START(stolen_node) == peb_temp_page);
	assert(VM_NODE_SIZE(stolen_node) == peb_total_pages);
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
#endif

	/* Update the mapping location of the PEB memory node */
	stolen_node->vn_node.a_vmin = result;
	stolen_node->vn_node.a_vmax = result + peb_total_pages - 1;

	/* Load the stolen node into the VMB */
	vmb_node_insert(self, stolen_node);

	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_EXEC_PEB_C */
