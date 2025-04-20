/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "mbuilder-peb.c"
#if defined(__x86_64__) && 1
#define IN_POINTERSIZE 4
#define OU_POINTERSIZE 8
#else
#define IN_POINTERSIZE __SIZEOF_POINTER__
#define OU_POINTERSIZE __SIZEOF_POINTER__
#endif
#endif /* __INTELLISENSE__ */

#include <kernel/compiler.h>

#include <kernel/compat.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/user.h>

#include <hybrid/__pointer.h>
#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#include <kos/except.h>
#include <kos/exec/peb.h>
#include <kos/kernel/paging.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#include <kos/exec/bits/peb32.h>
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#include <kos/exec/bits/peb64.h>
#endif /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#if IN_POINTERSIZE == OU_POINTERSIZE && IN_POINTERSIZE == __SIZEOF_POINTER__
#define MY_MBUILDER_ALLOC_PEB mbuilder_alloc_peb
#elif IN_POINTERSIZE == OU_POINTERSIZE && IN_POINTERSIZE == 4
#define MY_MBUILDER_ALLOC_PEB mbuilder_alloc_peb32
#elif IN_POINTERSIZE == OU_POINTERSIZE && IN_POINTERSIZE == 8
#define MY_MBUILDER_ALLOC_PEB mbuilder_alloc_peb64
#elif OU_POINTERSIZE == 8 && IN_POINTERSIZE == 4
#define MY_MBUILDER_ALLOC_PEB mbuilder_alloc_peb64_p32
#elif OU_POINTERSIZE == 4 && IN_POINTERSIZE == 8
#define MY_MBUILDER_ALLOC_PEB mbuilder_alloc_peb32_p64
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


/* Allocate   a  PEB   (Process  Environment   Block)  within   the  given  MBuilder,
 * initializing  its  contents  with  the  strings  from  the  given  argv+envp pair.
 * This function is called from `mman_exec()' after the remainder of the application,
 * as well as the dynamic linker have already been loaded into memory.
 * @param: argc_inject: The number of arguments from `argv_inject' to inject
 *                      at the beginning of the user-space argc/argv vector.
 * @param: argv_inject: Vector of arguments to inject at the beginning of
 *                      the user-space argc/argv vector.
 * @param: argv:        User-space pointer to a NULL-terminated vector of argument strings
 * @param: envp:        User-space pointer to a NULL-terminated vector of environment strings
 * @return: * :         Page index of the PEB (to-be passed to the user-space program) */
PUBLIC WUNUSED NONNULL((1)) UNCHECKED void *KCALL
MY_MBUILDER_ALLOC_PEB(struct mbuilder_norpc *__restrict self,
                      size_t argc_inject, KERNEL char const *const *argv_inject,
                      NCX UNCHECKED IN_PTR(char const) NCX const *argv,
                      NCX UNCHECKED IN_PTR(char const) NCX const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
#define read_once_in_charp(p) \
	(NCX UNCHECKED IN_PTR(char const))read_once((IN_UIP *)(p))
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
	struct mbnode *stolen_node;
	NCX UNCHECKED IN_PTR(char const) string;
	NCX UNCHECKED IN_PTR(char const) NCX const *iter;

again:
	argc_user          = 0;
	envc_user          = 0;
	strings_total_size = 0;

	/* Figure out how much memory we need to allocate */
	for (i = 0; i < argc_inject; ++i)
		strings_total_size += (strlen(argv_inject[i]) + 1) * sizeof(char);
	if likely((iter = argv) != NULL) {
		while ((string = read_once_in_charp(iter)) != NULL) {
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
		while ((string = read_once_in_charp(iter)) != NULL) {
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
	peb_temp_base = (byte_t *)mman_map(&mman_kernel,
	                                   MHINT_GETADDR(KERNEL_MHINT_TEMPORARY),
	                                   peb_total_size,
	                                   PROT_READ | PROT_WRITE | PROT_SHARED,
	                                   MHINT_GETMODE(KERNEL_MHINT_TEMPORARY) |
	                                   MAP_PREPARED | MAP_NOMERGE | MAP_NOSPLIT,
	                                   &mfile_zero,
	                                   NULL,
	                                   NULL,
	                                   0,
	                                   PAGESIZE);
	TRY {
		byte_t *writer;
		NCX OU_UIP *peb_argv;
		NCX OU_UIP *peb_envp;
		NCX peb_t *peb;
		size_t strings_total_copied;

		/* Initialize the PEB. */
		writer   = peb_temp_base + offsetafter(peb_t, pp_envp);
		peb_argv = (NCX OU_UIP *)writer;
		writer += (argc_inject + argc_user + 1) * OU_POINTERSIZE;
		peb_envp = (NCX OU_UIP *)writer;
		writer += (envc_user + 1) * OU_POINTERSIZE;
		peb = (NCX peb_t *)peb_temp_base;
		peb->pp_argc = argc_inject + argc_user;
		peb->pp_argv = (NCX OU_PTR(NCX OU_PTR(char)))(OU_UIP)(uintptr_t)((byte_t *)peb_argv - (uintptr_t)peb_temp_base);
		peb->pp_envc = envc_user;
		peb->pp_envp = (NCX OU_PTR(NCX OU_PTR(char)))(OU_UIP)(uintptr_t)((byte_t *)peb_envp - (uintptr_t)peb_temp_base);

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
			string = read_once_in_charp(&argv[i]);
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
			string = read_once_in_charp(&envp[i]);
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
			mman_unmap_kram(peb_temp_base,
			                peb_total_size,
			                GFP_NORMAL);
			goto again;
		}

		/* Figure out where we want to map the PEB within the VM builder. */
		/* TODO: Muse use `KERNEL_MHINT_USER_PEB' depending on compatibility mode!
		 * >> KERNEL_MHINT_USER_PEB(32|64) depending on IN_PTR(void)-size */
		result = mbuilder_findunmapped(self, MHINT_GETADDR(KERNEL_MHINT_USER_PEB),
		                               peb_total_size,
		                               MHINT_GETMODE(KERNEL_MHINT_USER_PEB));

		/* Relocate pointers within the PEB to make them absolute */
		peb->pp_argv = (OU_PTR(OU_PTR(char)))((OU_UIP)peb->pp_argv + (OU_UIP)(uintptr_t)result);
		peb->pp_envp = (OU_PTR(OU_PTR(char)))((OU_UIP)peb->pp_envp + (OU_UIP)(uintptr_t)result);
		for (i = 0; i < argc_inject + argc_user; ++i)
			peb_argv[i] += (OU_UIP)(uintptr_t)result;
		for (i = 0; i < envc_user; ++i)
			peb_envp[i] += (OU_UIP)(uintptr_t)result;

		/* Lock the kernel VM, so we can steal the PEB node. */
		mman_lock_write(&mman_kernel);

		/* Ensure that the page directory is prepared to erase the temporary PEB mapping. */
		if unlikely(!pagedir_prepare(peb_temp_base, peb_total_size)) {
			mman_lock_endwrite(&mman_kernel);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
	} EXCEPT {
		/* Delete the temporary PEB mapping as general-purpose kernel RAM. */
		mman_unmap_kram(peb_temp_base,
		                peb_total_size,
		                GFP_NORMAL);
		RETHROW();
	}

	/* Steal the node used to hold the PEB */
	stolen_node = (struct mbnode *)mnode_tree_remove(&mman_kernel.mm_mappings, peb_temp_base);
	if likely(LIST_ISBOUND((struct mnode *)stolen_node, mn_writable))
		LIST_REMOVE((struct mnode *)stolen_node, mn_writable);

	/* Delete the temporary PEB mapping, and sync the address range.
	 * NOTE: Since  the mapping was  strictly private to us,
	 *       there is no need to sync this with another CPU! */
	pagedir_unmap(peb_temp_base, peb_total_size);
	pagedir_sync(peb_temp_base, peb_total_size);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare(peb_temp_base, peb_total_size);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	mman_lock_endwrite(&mman_kernel);

	/* Make sure that the PEB node has the expected state. */
	assert(stolen_node);
	assert(mbnode_getminaddr(stolen_node) == peb_temp_base);
	assert(mbnode_getsize(stolen_node) == peb_total_size);
	assert(stolen_node->_mbn_module == NULL);
	assert(stolen_node->mbn_part);
	assert(stolen_node->mbn_part->mp_share.lh_first == (struct mnode *)stolen_node);

	/* Delete some unneeded/problematic flags. */

	/* Delete the part->node link (no need for locking, since `mn_part' isn't shared) */
	stolen_node->mbn_part->mp_share.lh_first = NULL; /* XXX: Unsafe (but ignore since this whole API is deprecated) */
	stolen_node->mbn_minaddr = (byte_t *)result;
	stolen_node->mbn_maxaddr = (byte_t *)result + peb_total_size - 1;
	stolen_node->mbn_flags   = MNODE_F_PREAD | MNODE_F_PWRITE;
	stolen_node->mbn_file    = incref(&mfile_zero);
	mnode_mbn_filpos_set(stolen_node, 0);

	/* Load the stolen node into the MBUILDER */
	mbuilder_insert_fmnode(self, stolen_node);

	return result;
#undef read_once_in_charp
}

DECL_END

#undef MY_MBUILDER_ALLOC_PEB
#undef OU_PTR
#undef IN_PTR
#undef OU_UIP
#undef IN_UIP
#undef OU_POINTERSIZE
#undef IN_POINTERSIZE
