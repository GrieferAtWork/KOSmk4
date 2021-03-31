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

#define datapage_t                                    mfile_block_t
#define VM_DATAPART_PPP_UNINITIALIZED                 MPART_BLOCK_ST_NDEF
#define VM_DATAPART_PPP_INITIALIZING                  MPART_BLOCK_ST_INIT
#define VM_DATAPART_PPP_INITIALIZED                   MPART_BLOCK_ST_LOAD
#define VM_DATAPART_PPP_HASCHANGED                    MPART_BLOCK_ST_CHNG
#define VM_DATAPART_PPP_BITS                          MPART_BLOCK_STBITS
#define VM_DATAPART_FLAG_NORMAL                       MPART_F_NORMAL
#define VM_DATAPART_FLAG_LOCKED                       MPART_F_MLOCK
#define VM_DATAPART_FLAG_CHANGED                      MPART_F_CHANGED
#define VM_DATAPART_FLAG_KEEPRAM                      MPART_F_NOFREE
#define VM_DATAPART_FLAG_COREPRT                      MPART_F_COREPART
#define VM_DATAPART_FLAG_KERNPRT                      MPART_F_NOSPLIT
#define VM_DATAPART_STATE_ABSENT                      MPART_ST_VOID
#define VM_DATAPART_STATE_INCORE                      MPART_ST_MEM
#define VM_DATAPART_STATE_INSWAP                      MPART_ST_SWP
#define VM_DATAPART_STATE_VIOPRT                      MPART_ST_VIO
#define dp_refcnt                                     mp_refcnt
#define dp_crefs                                      mp_copy.lh_first
#define dp_srefs                                      mp_share.lh_first
#define dp_block                                      mp_file
#define dp_flags                                      mp_flags
#define dp_state                                      mp_state
#define dp_pprop                                      mp_blkst_inl
#define dp_pprop_p                                    mp_blkst_ptr
#define dp_futex                                      mp_meta
#define vm_datapart_free(...)                         mpart_free(__VA_ARGS__)
#define vm_datapart_destroy(...)                      mpart_destroy(__VA_ARGS__)
#define vm_datapart_numbytes(...)                     mpart_getsize(__VA_ARGS__)
#define vm_datapart_minbyte(...)                      mpart_getminaddr(__VA_ARGS__)
#define vm_datapart_maxbyte(...)                      mpart_getmaxaddr(__VA_ARGS__)
#define vm_datapart_startbyte(...)                    mpart_getminaddr(__VA_ARGS__)
#define vm_datapart_endbyte(...)                      mpart_getendaddr(__VA_ARGS__)
#define vm_datapart_sync(self, ...)                   (mpart_sync(self), 0)
#define vm_datapart_lockwrite_setcore(...)            mpart_lock_acquire_and_setcore(__VA_ARGS__)
#define vm_datapart_lockwrite_setcore_unsharecow(...) mpart_lock_acquire_and_setcore_unsharecow(__VA_ARGS__)
#define vm_datapart_lockread_setcore(...)             mpart_lock_acquire_and_setcore(__VA_ARGS__)
#define vm_datapart_lockread_setcore_unsharecow(...)  mpart_lock_acquire_and_setcore_unsharecow(__VA_ARGS__)
#define vm_datapart_getstate(...)                     mpart_getblockstate(__VA_ARGS__)
#define vm_datapart_setstate(...)                     mpart_setblockstate(__VA_ARGS__)
#define vm_datapart_isstatewritable(...)              mpart_hasblockstate(__VA_ARGS__)
#define db_refcnt                                     mf_refcnt
#define db_lock                                       mf_lock
#define db_type                                       mf_ops
#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
#define db_vio                                        mf_vio
#else /* CONFIG_MFILE_LEGACY_VIO_OPS */
#define db_vio                                        mf_ops->mo_vio
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */
#define db_parts                                      mf_parts
#define db_addrshift                                  mf_blockshift
#define vm_datablock_destroy(...)                     mfile_destroy(__VA_ARGS__)
#define vm_datablock_anonymize(...)                   (mfile_delete(__VA_ARGS__), 1)
#define vm_datablock_isanonymous(...)                 mfile_isanon(__VA_ARGS__)
#define vm_datablock_sync(...)                        mfile_sync(__VA_ARGS__)
#define vm_datablock_locatepart(...)                  mfile_getpart(__VA_ARGS__)
#define vm_datablock_haschanged(self)                 mfile_haschanged(self)
#define vm_datablock_physical                         mfile_phys
#define vm_datablock_physical_type                    mfile_phys_ops
#define vm_datablock_anonymous                        mfile_ndef
#define vm_datablock_anonymous_type                   mfile_ndef_ops
#define vm_datablock_anonymous_zero                   mfile_zero
#define vm_datablock_anonymous_zero_type              mfile_zero_ops
#define VM_PROT_NONE                                  MNODE_F_NORMAL
#define VM_PROT_EXEC                                  MNODE_F_PEXEC
#define VM_PROT_WRITE                                 MNODE_F_PWRITE
#define VM_PROT_READ                                  MNODE_F_PREAD
#define VM_PROT_PRIVATE                               MNODE_F_NORMAL
#define VM_PROT_SHARED                                MNODE_F_SHARED
#define VM_NODE_FLAG_NORMAL                           MNODE_F_NORMAL
#define VM_NODE_FLAG_PREPARED                         MNODE_F_MPREPARED
#define VM_NODE_FLAG_HINTED                           MNODE_F_MHINT
#define VM_NODE_FLAG_NOMERGE                          MNODE_F_NOMERGE
#define VM_NODE_FLAG_COREPRT                          MNODE_F_COREPART
#define VM_NODE_FLAG_KERNPRT                          MNODE_F_KERNPART
#define vn_prot                                       mn_flags
#define vn_flags                                      mn_flags
#define vn_vm                                         mn_mman
#define vn_part                                       mn_part
#define vn_block                                      mn_part->mp_file
#define vn_fspath                                     mn_fspath
#define vn_fsname                                     mn_fsname
#define vn_link                                       mn_link
#define vm_node_free(...)                             mnode_free(__VA_ARGS__)
#define vm_node_destroy(...)                          mnode_destory(__VA_ARGS__)
#define vm_node_update_write_access(...)              mnode_clear_write(__VA_ARGS__)
#define vm_node_update_write_access_locked_vm(...)    mnode_clear_write_locked_p(__VA_ARGS__)
#define VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS           MNODE_CLEAR_WRITE_SUCCESS
#define VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK        MNODE_CLEAR_WRITE_WOULDBLOCK
#define VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC          MNODE_CLEAR_WRITE_BADALLOC
#define vm_node_setminaddr(self, v)                   ((self)->mn_minaddr = (v))
#define vm_node_setmaxaddr(self, v)                   ((self)->mn_maxaddr = (v))
#define vm_node_getminaddr(...)                       mnode_getminaddr(__VA_ARGS__)
#define vm_node_getmaxaddr(...)                       mnode_getmaxaddr(__VA_ARGS__)
#define vm_node_getaddr(...)                          mnode_getaddr(__VA_ARGS__)
#define vm_node_getendaddr(...)                       mnode_getendaddr(__VA_ARGS__)
#define vm_node_getsize(...)                          mnode_getsize(__VA_ARGS__)
#define vm_node_isuserspace(...)                      mnode_iskern(__VA_ARGS__)
#define vm_node_iskernelspace(...)                    mnode_isuser(__VA_ARGS__)
#define VM_NODE_HASNEXT(self, vm)                     (mnode_tree_nextnode(self) != __NULLPTR)
#define VM_NODE_HASPREV(self, vm)                     (mnode_tree_prevnode(self) != __NULLPTR)
#define VM_NODE_NEXT(self)                            mnode_tree_nextnode(self)
#define VM_NODE_PREV(self)                            mnode_tree_prevnode(self)
#define v_pagedir                                     mm_pagedir
#define v_pdir_phys                                   mm_pagedir_p
#define v_refcnt                                      mm_refcnt
#define v_weakrefcnt                                  mm_weakrefcnt
#define v_tree                                        mm_mappings
#define v_treelock                                    mm_lock
#define v_tasks                                       mm_threads
#define v_tasklock                                    mm_threadslock
#define vm_kernel                                     mman_kernel
#define vm_free(...)                                  mman_free(__VA_ARGS__)
#define vm_destroy(...)                               mman_destroy(__VA_ARGS__)
#define vm_alloc(...)                                 mman_new(__VA_ARGS__)
#define task_setvm(...)                               task_setmman(__VA_ARGS__)
#define task_getvm(...)                               task_getmman(__VA_ARGS__)
#define vm_sync(...)                                  mman_sync_p(__VA_ARGS__)
#define vm_syncone(...)                               mman_syncone_p(__VA_ARGS__)
#define vm_syncall(...)                               mman_syncall_p(__VA_ARGS__)
#define this_vm_sync(...)                             mman_sync(__VA_ARGS__)
#define this_vm_syncone(...)                          mman_syncone(__VA_ARGS__)
#define this_vm_syncall(...)                          mman_syncall(__VA_ARGS__)
#define vm_supersync(...)                             mman_supersync(__VA_ARGS__)
#define vm_supersyncone(...)                          mman_supersyncone(__VA_ARGS__)
#define vm_supersyncall(...)                          mman_supersyncall(__VA_ARGS__)
#define VM_FORCEFAULT_FLAG_READ                       MMAN_FAULT_F_NORMAL
#define VM_FORCEFAULT_FLAG_WRITE                      MMAN_FAULT_F_WRITE
#define VM_FORCEFAULT_FLAG_NOVIO                      MMAN_FAULT_F_NOVIO
#define vm_prefault(addr, num_bytes, for_writing)     mman_prefault(addr, num_bytes, (for_writing) ? MMAN_FAULT_F_WRITE : MMAN_FAULT_F_NORMAL)
#define vm_forcefault(...)                            mman_forcefault(__VA_ARGS__)
#define vm_forcefault_p(...)                          mman_forcefault(__VA_ARGS__)
#define vm_kernel_treelock_writef(flags)              (((flags)&GFP_ATOMIC) ? mman_lock_trywrite(&mman_kernel) : (mman_lock_write(&mman_kernel), 1))
#define vm_kernel_treelock_writef_nx(flags)           (((flags)&GFP_ATOMIC) ? mman_lock_trywrite(&mman_kernel) : mman_lock_write_nx(&mman_kernel))
#define vm_kernel_treelock_write()                    mman_lock_write(&mman_kernel)
#define vm_kernel_treelock_read()                     mman_lock_read(&mman_kernel)
#define vm_kernel_treelock_trywrite()                 mman_lock_trywrite(&mman_kernel)
#define vm_kernel_treelock_write_nx()                 mman_lock_write_nx(&mman_kernel)
#define vm_kernel_treelock_endwrite()                 mman_lock_endwrite(&mman_kernel)
#define vm_kernel_treelock_tryread()                  mman_lock_tryread(&mman_kernel)
#define vm_kernel_treelock_read_nx()                  mman_lock_read_nx(&mman_kernel)
#define vm_kernel_treelock_endread()                  mman_lock_endread(&mman_kernel)
#define vm_kernel_treelock_writing()                  mman_lock_writing(&mman_kernel)
#define vm_kernel_treelock_reading()                  mman_lock_reading(&mman_kernel)
#define vm_kernel_treelock_end()                      mman_lock_end(&mman_kernel)
#define vm_kernel_treelock_tryservice()               mman_lockops_reap(&mman_kernel)
#define vm_treelock_write(self)                       mman_lock_write(self)
#define vm_treelock_write_nx(self)                    mman_lock_write_nx(self)
#define vm_treelock_trywrite(self)                    mman_lock_trywrite(self)
#define vm_treelock_endwrite(self)                    mman_lock_endwrite(self)
#define vm_treelock_read(self)                        mman_lock_read(self)
#define vm_treelock_read_nx(self)                     mman_lock_read_nx(self)
#define vm_treelock_tryread(self)                     mman_lock_tryread(self)
#define vm_treelock_endread(self)                     mman_lock_endread(self)
#define vm_treelock_end(self)                         mman_lock_end(self)
#define vm_treelock_reading(self)                     mman_lock_reading(self)
#define vm_treelock_writing(self)                     mman_lock_writing(self)
#define vm_treelock_canread(self)                     mman_lock_canread(self)
#define vm_treelock_canwrite(self)                    mman_lock_canwrite(self)
#define vm_tasklock_read(self)                        mman_threadslock_acquire(self)
#define vm_tasklock_write(self)                       mman_threadslock_acquire(self)
#define vm_tasklock_upgrade(self)                     1
#define vm_tasklock_read_nx(self)                     mman_threadslock_acquire(self)
#define vm_tasklock_write_nx(self)                    mman_threadslock_acquire(self)
#define vm_tasklock_upgrade_nx(self)                  mman_threadslock_acquire(self)
#define vm_tasklock_endwrite(self)                    mman_threadslock_release(self)
#define vm_tasklock_endread(self)                     mman_threadslock_release(self)
#define vm_tasklock_end(self)                         mman_threadslock_release(self)
#define vm_tasklock_downgrade(self)                   (void)0
#define vm_tasklock_tryservice(self)                  (void)0
#define vm_tasklock_reading(self)                     mman_threadslock_acquired(self)
#define vm_tasklock_writing(self)                     mman_threadslock_acquired(self)
#define VM_DATABLOCK_ADDRSHIFT(x)                     ((x)->mf_blockshift)
#define VM_DATABLOCK_PAGESHIFT(x)                     (PAGESHIFT - (x)->mf_blockshift)
#define VM_DATABLOCK_PAGEALIGN(x)                     ((size_t)1 << VM_DATABLOCK_PAGESHIFT(x))
#define VM_DATABLOCK_PAGEMASK(x)                      (((size_t)1 << VM_DATABLOCK_PAGESHIFT(x)) - 1)
#define VM_DATABLOCK_PAGESIZE(x)                      ((size_t)PAGESIZE >> VM_DATABLOCK_PAGESHIFT(x))
#define rf_block                                      mrf_file
#define rf_data                                       mrf_part.mp_mem
#define dt_destroy                                    mo_destroy
#define dt_initpart                                   mo_initpart
#define dt_loadpart                                   mo_loadpart
#define dt_savepart                                   mo_savepart
#define dt_changed                                    mo_changed
#define vm_datapart_decref_and_merge(self)            decref(self)

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
         struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
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
                  struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
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

FORCELOCAL WUNUSED NONNULL((1)) bool
vm_mapresat(struct vm *__restrict self,
            PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
            PAGEDIR_PAGEALIGNED size_t num_bytes,
            uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	TRY {
		mman_map_res(self, addr, num_bytes,
		             MAP_FIXED | MAP_FIXED_NOREPLACE |
		             flag);
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


#define VM_GETFREE_ASLR  0 /* Enabled by default. */
#define VM_GETFREE_ABOVE MAP_GROWSUP
#define VM_GETFREE_BELOW MAP_GROWSDOWN
#define VM_GETFREE_ERROR MAP_FAILED
#define vm_getfree(self, hint, num_bytes, min_alignment, mode) \
	mman_findunmapped(self, hint, num_bytes, mode, min_alignment)
#define vm_get_aslr_disabled() (mman_getunmapped_extflags & MAP_NOASLR)
#define vm_set_aslr_disabled(v)                                                        \
	((v) ? __hybrid_atomic_or(mman_getunmapped_extflags, MAP_NOASLR, __ATOMIC_SEQ_CST) \
	     : __hybrid_atomic_and(mman_getunmapped_extflags, ~MAP_NOASLR, __ATOMIC_SEQ_CST))
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
#define vm_mapres(self, hint, num_bytes, min_alignment, getfree_mode, flag) \
	mman_map_res(self, hint, num_bytes, (getfree_mode) | (flag), min_alignment)

#define VM_UNMAP_NORMAL           0
#define VM_UNMAP_GUARD            0
#define VM_UNMAP_RESERVE          0
#define VM_UNMAP_ANYTHING         0
#define VM_UNMAP_SEGFAULTIFUNUSED MMAN_UNMAP_FAULTIFUNUSED
#define VM_UNMAP_NOSPLIT          MMAN_UNMAP_NOSPLIT
#define VM_UNMAP_NOKERNPART       MMAN_UNMAP_NOKERNPART
#define vm_unmap(...)             mman_unmap(__VA_ARGS__)
#define vm_protect(...)           mman_protect(__VA_ARGS__)
#define vm_syncmem(self, addr, num_bytes) \
	(mman_syncmem(self, addr, num_bytes), (u64)0)
#define vm_read_nopf(...)               mman_read_nopf(__VA_ARGS__)
#define vm_write_nopf(...)              mman_write_nopf(__VA_ARGS__)
#define vm_memset_nopf(...)             mman_memset_nopf(__VA_ARGS__)
#define vm_read(...)                    mman_read(__VA_ARGS__)
#define vm_write(...)                   mman_write(__VA_ARGS__)
#define vm_memset(...)                  mman_memset(__VA_ARGS__)
#define dl_part                         mdl_part
#define vm_dmalock_release(...)         mman_dmalock_release(__VA_ARGS__)
#define vm_startdma(effective_vm, prange, preset, arg, lockvec, lockcnt, vaddr, num_bytes, for_writing) \
	mman_startdma(effective_vm, prange, arg, lockvec, lockcnt, vaddr, num_bytes, for_writing)
#define vm_startdmav(effective_vm, prange, preset, arg, lockvec, lockcnt, vaddr_buf, for_writing) \
	mman_startdmav(effective_vm, prange, arg, lockvec, lockcnt, vaddr_buf, for_writing)
#define vm_enumdma(...)                 mman_enumdma(__VA_ARGS__)
#define vm_enumdmav(...)                mman_enumdmav(__VA_ARGS__)
#define vm_stopdma(...)                 mman_stopdma(__VA_ARGS__)
#define vm_exec(...)                    mman_exec(__VA_ARGS__)
#define vm_exec_assert_regular(self)    (void)0 /* TODO: This should be exposed in <fs/node.h>! */
#define vm_mapinfo                      mmapinfo
#define vmi_min                         mmi_min
#define vmi_max                         mmi_max
#define vmi_prot                        mmi_flags
#define vmi_block                       mmi_file
#define vmi_offset                      mmi_offset
#define vmi_fspath                      mmi_fspath
#define vmi_fsname                      mmi_fsname
#define vmi_index                       mmi_index
#define vm_mapinfo_size                 mmapinfo_size
#define vm_enum_callback_t              mman_enum_callback_t
#define vm_enum(...)                    mman_enum(__VA_ARGS__)
#define vm_kernel_pending_operation     lockop
#define vm_kernel_pending_cb_t          lockop_callback_t
#define vkpo_next                       lo_link.sle_next
#define vkpo_exec                       lo_func
#define vm_kernel_pending_operations    mman_kernel_lockops.slh_first
#define VM_KERNEL_PENDING_CB_RETURN_T   struct postlockop *
#define VM_KERNEL_PENDING_CB_RETURN     return __NULLPTR
#define VM_KERNEL_PENDING_CB_CC         FCALL
#define vm_onexec_callbacks             mman_onexec_callbacks
#define vm_oninit_callbacks             mman_oninit_callbacks
#define vm_onfini_callbacks             mman_onfini_callbacks
#define vm_onclone_callbacks            mman_onclone_callbacks
#ifdef CONFIG_BUILDING_KERNEL_CORE
#define DEFINE_PERVM_ONEXEC DEFINE_PERMMAN_ONEXEC
#define DEFINE_PERVM_INIT   DEFINE_PERMMAN_INIT
#define DEFINE_PERVM_FINI   DEFINE_PERMMAN_FINI
#define DEFINE_PERVM_CLONE  DEFINE_PERMMAN_CLONE
#endif /* CONFIG_BUILDING_KERNEL_CORE */

/* Misc. functions */
#define vm_datapart_map_ram(self, addr, perm)                  mpart_mmap_force(self, addr, mpart_getsize(self), 0, perm)
#define vm_datapart_map_ram_p(self, pdir, addr, perm)          mpart_mmap_force_p(self, pdir, addr, mpart_getsize(self), 0, perm)
#define vm_datapart_map_ram_autoprop(self, addr, perm)         mpart_mmap(self, addr, mpart_getsize(self), 0, perm)
#define vm_datapart_map_ram_autoprop_p(self, pdir, addr, perm) mpart_mmap_p(self, pdir, addr, mpart_getsize(self), 0, perm)
#define vm_getnodeofaddress(self, addr)                        mnode_tree_locate((self)->mm_mappings, addr)
#define vm_isused(self, addr, num_bytes)                       (mnode_tree_rlocate((self)->mm_mappings, addr, (byte_t *)(addr) + (num_bytes)-1) != __NULLPTR)
#define vm_node_insert(self)                                   mnode_tree_insert(&(self)->mn_mman->mm_mappings, self)
#define vm_node_remove(self, addr)                             COMPILER_UNUSED(mnode_tree_remove(&(self)->mm_mappings, addr))
#define vm_unmap_kernel_ram(addr, num_bytes, is_zero)          mman_unmap_kram(addr, num_bytes, (is_zero) ? GFP_CALLOC : 0)
#define vm_unmap_kernel_mapping_locked(addr, num_bytes)        mman_unmap_kram_locked(addr, num_bytes)
#define vm_get_kernreserve_node(self)                          (&FORMMAN(self, thismman_kernel_reservation))
#define vm_datapart_do_allocram(self)                          mpart_ll_allocmem(self, mpart_getsize(self) / PAGESIZE)
#define vm_datapart_do_ccfreeram(self)                         mpart_ll_ccfreemem(self)
#define vm_datapart_do_freeram(self)                           mpart_ll_freemem(self)
#define vm_datapart_freeram(self)                              mpart_ll_freemem(self)

#define vm_datablock_deanonymize(self) (void)0 /* TODO: Function was always racy, and isn't supported anymore */
#define VM_DATABLOCK_INIT_VIO_EX       MFILE_INIT_VIO_EX
#define VM_DATABLOCK_INIT_VIO          MFILE_INIT_VIO

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_H */
