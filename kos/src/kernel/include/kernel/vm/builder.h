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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_BUILDER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_BUILDER_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mbuilder.h>


#define VMB_INIT       MBUILDER_INIT
#define vmb_init(self) mbuilder_init(self)
#define vmb_fini(self) mbuilder_fini(self)
#define WANT_VMB_FINI_AFTER_SUCCESSFUL_APPLY

#ifdef __CC__
#include <kos/except.h>
DECL_BEGIN

#ifdef TRY
FORCELOCAL WUNUSED NONNULL((1, 4)) bool
vmb_mapat(struct mbuilder *__restrict self,
          PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
          PAGEDIR_PAGEALIGNED size_t num_bytes,
          struct mfile *__restrict data DFL(&mfile_zero),
          struct path *fspath DFL(__NULLPTR),
          struct directory_entry *fsname DFL(__NULLPTR),
          PAGEDIR_PAGEALIGNED pos_t data_start_offset DFL(0),
          uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
          uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
          uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	(void)guard;
	TRY {
		mbuilder_map(self, addr, num_bytes, prot,
		             MAP_FIXED | MAP_FIXED_NOREPLACE | flag,
		             data, fspath, fsname, data_start_offset);
	} EXCEPT {
		if (was_thrown(E_BADALLOC_ADDRESS_ALREADY_EXISTS))
			return false;
		RETHROW();
	}
	return true;
}
#endif /* TRY */

DECL_END
#endif /* __CC__ */

#define vmb_getfree(self, hint, num_bytes, min_alignment, mode) \
	mbuilder_findunmapped(self, hint, num_bytes, mode, min_alignment)
#define vmb_map(self, hint, num_bytes, min_alignment, getfree_mode, data, \
                fspath, fsname, data_start_offset, prot, flag, guard)     \
	mbuilder_map(self, hint, num_bytes, prot, (getfree_mode) | (flag),    \
	             data, fspath, fsname, data_start_offset, min_alignment)
#define vmb_getnodeofaddress(self, addr) \
	((struct vm_node *)mbnode_tree_locate((self)->mb_mappings, addr))
#define vmb_apply(...) mbuilder_apply(__VA_ARGS__)
#define VMB_APPLY_AA_NOTHING      MBUILDER_APPLY_AA_NOTHING
#define VMB_APPLY_AA_TERMTHREADS  MBUILDER_APPLY_AA_TERMTHREADS
#define VMB_APPLY_AA_SETEXECINFO  MBUILDER_APPLY_AA_SETEXECINFO
#define vmb_alloc_peb(...)        mbuilder_alloc_peb(__VA_ARGS__)
#ifdef __ARCH_HAVE_COMPAT
#define vmb_alloc_peb32(...)     mbuilder_alloc_peb32(__VA_ARGS__)
#define vmb_alloc_peb64_p64(...) mbuilder_alloc_peb64_p64(__VA_ARGS__)
#define vmb_alloc_peb32_p32(...) mbuilder_alloc_peb32_p32(__VA_ARGS__)
#define vmb_alloc_peb64(...)     mbuilder_alloc_peb64(__VA_ARGS__)
#define vmb_alloc_peb64_p32(...) mbuilder_alloc_peb64_p32(__VA_ARGS__)
#define vmb_alloc_peb32_p64(...) mbuilder_alloc_peb32_p64(__VA_ARGS__)
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_BUILDER_H */
