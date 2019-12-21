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

#include <kos/exec/peb.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
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
PUBLIC WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
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
	byte_t *peb_temp_base;
	PAGEDIR_PAGEALIGNED UNCHECKED void *result;
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
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, (size_t)-1);
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
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, (size_t)-1);
			++envc_user;
			++iter;
		}
	}
	peb_total_size = (offsetafter(struct process_peb, pp_envp) +
	                  (argc_inject + argc_user + envc_user + 2) * sizeof(USER char *) +
	                  strings_total_size);
	/* XXX: Check if `peb_total_size' is too large? */

	/* Create a temporary kernel-space mapping for initializing the PEB */
	peb_total_size = CEIL_ALIGN(peb_total_size, PAGESIZE);
	peb_temp_base = (byte_t *)vm_map(&vm_kernel,
	                                 HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                                 peb_total_size,
	                                 PAGESIZE,
	                                 HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
	                                 &vm_datablock_anonymous_zero,
	                                 0,
	                                 VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED,
	                                 VM_NODE_FLAG_NORMAL,
	                                 0);
	TRY {
		byte_t *writer;
		USER uintptr_t *peb_argv;
		USER uintptr_t *peb_envp;
		USER struct process_peb *peb;
		size_t strings_total_copied;

		/* Initialize the PEB. */
		writer   = peb_temp_base + offsetafter(struct process_peb, pp_envp);
		peb_argv = (USER uintptr_t *)writer;
		writer += (argc_inject + argc_user + 1) * sizeof(USER char *);
		peb_envp = (USER uintptr_t *)writer;
		writer += (envc_user + 1) * sizeof(USER char *);
		peb = (USER struct process_peb *)peb_temp_base;
		peb->pp_argc = argc_inject + argc_user;
		peb->pp_argv = (char **)((byte_t *)peb_argv - (uintptr_t)peb_temp_base);
		peb->pp_envc = envc_user;
		peb->pp_envp = (char **)((byte_t *)peb_envp - (uintptr_t)peb_temp_base);

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
			vm_unmap_kernel_ram(peb_temp_base,
			                     peb_total_size,
			                     false);
			goto again;
		}

		/* Figure out where we want to map the PEB within the VM builder. */
		result = vmb_getfree(self,
		                     HINT_GETADDR(KERNEL_VMHINT_USER_PEB),
		                     peb_total_size,
		                     PAGESIZE,
		                     HINT_GETMODE(KERNEL_VMHINT_USER_PEB));

		/* Relocate pointers within the PEB to make them absolute */
		peb->pp_argv = (char **)((byte_t *)peb->pp_argv + (uintptr_t)result);
		peb->pp_envp = (char **)((byte_t *)peb->pp_envp + (uintptr_t)result);
		for (i = 0; i < argc_inject + argc_user; ++i)
			peb_argv[i] += (uintptr_t)result;
		for (i = 0; i < envc_user; ++i)
			peb_envp[i] += (uintptr_t)result;

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
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_EXEC_PEB_C */
