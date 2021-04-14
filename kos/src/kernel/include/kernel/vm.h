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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_H 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/dma.h>
#include <kernel/mman/enum.h>
#include <kernel/mman/event.h>
#include <kernel/mman/exec.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/mman/ramfile.h>
#include <kernel/mman/rw.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>

#define VM_PROT_NONE         MNODE_F_NORMAL
#define VM_PROT_EXEC         MNODE_F_PEXEC
#define VM_PROT_WRITE        MNODE_F_PWRITE
#define VM_PROT_READ         MNODE_F_PREAD
#define VM_PROT_SHARED       MNODE_F_SHARED
#define VM_NODE_FLAG_NORMAL  MNODE_F_NORMAL
#define VM_NODE_FLAG_NOMERGE MNODE_F_NOMERGE

#ifdef __CC__
#include <kos/except.h>
DECL_BEGIN

__DEFINE_SYNC_MUTEX(struct mpart,
                    mpart_lock_tryacquire,
                    mpart_lock_acquire,
                    mpart_lock_acquire_nx,
                    mpart_lock_release,
                    mpart_lock_acquired,
                    mpart_lock_available)


#ifdef TRY
FORCELOCAL WUNUSED NONNULL((1, 4)) bool
vm_mapat(struct vm *__restrict self,
         PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
         PAGEDIR_PAGEALIGNED size_t num_bytes,
         struct vm_datablock *__restrict data DFL(&mfile_zero),
         struct path *fspath DFL(__NULLPTR),
         struct directory_entry *fsname DFL(__NULLPTR),
         PAGEDIR_PAGEALIGNED pos_t data_start_offset DFL(0),
         uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
         uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL), uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	(void)guard;
	TRY {
		mman_map(self, addr, num_bytes, prot,
		         MAP_FIXED | MAP_FIXED_NOREPLACE | flag,
		         data, fspath, fsname, data_start_offset);
	} EXCEPT {
		if (was_thrown(E_BADALLOC_ADDRESS_ALREADY_EXISTS))
			return false;
		RETHROW();
	}
	return true;
}

FORCELOCAL WUNUSED NONNULL((1, 4)) bool
vm_mapat_subrange(struct vm *__restrict self,
                  PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                  PAGEDIR_PAGEALIGNED size_t num_bytes,
                  struct vm_datablock *__restrict data DFL(&mfile_zero),
                  struct path *fspath DFL(__NULLPTR),
                  struct directory_entry *fsname DFL(__NULLPTR),
                  PAGEDIR_PAGEALIGNED pos_t data_start_offset DFL(0),
                  PAGEDIR_PAGEALIGNED pos_t data_subrange_minoffset DFL(0),
                  PAGEDIR_PAGEALIGNED pos_t data_subrange_numbytes DFL((pos_t)-1),
                  uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
                  uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
                  uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	(void)guard;
	TRY {
		mman_map_subrange(self, addr, num_bytes, prot, MAP_FIXED | MAP_FIXED_NOREPLACE | flag,
		                  data, fspath, fsname, data_subrange_minoffset + data_start_offset,
		                  data_subrange_minoffset,
		                  data_subrange_minoffset + data_subrange_numbytes - 1);
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


#define vm_map(self, hint, num_bytes, min_alignment, getfree_mode, data, \
               fspath, fsname, data_start_offset, prot, flag, guard)     \
	mman_map(self, hint, num_bytes, prot, (getfree_mode) | (flag),       \
	         data, fspath, fsname, data_start_offset, min_alignment)
#define vm_map_subrange(self, hint, num_bytes, min_alignment, getfree_mode, data,   \
                        fspath, fsname, data_start_offset, data_subrange_minoffset, \
                        data_subrange_numbytes, prot, flag, guard)                  \
	mman_map_subrange(self, hint, num_bytes, prot, (getfree_mode) | (flag),         \
	                  data, fspath, fsname,                                         \
	                  (data_subrange_minoffset) + (data_start_offset),              \
	                  data_subrange_minoffset,                                      \
	                  (data_subrange_minoffset) + (data_subrange_numbytes)-1,       \
	                  min_alignment)

#define vm_exec_assert_regular(self)    (void)0 /* TODO: This should be exposed in <fs/node.h>! */
#define vm_isused(self, addr, num_bytes) (mman_mappings_rlocate(self, addr, (byte_t *)(addr) + (num_bytes)-1) != __NULLPTR)

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_H */
