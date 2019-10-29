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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_C
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <kernel/swap.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/pid.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <alloca.h>
#include <assert.h>
#include <string.h>

#include "../corebase.h"
#include "vm-nodeapi.h"

#define POINTER_SET_BUFSIZE 4
#include <misc/pointer-set.h>

/* Implement the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_nodetree_##x
#define ATREE_FUN                INTDEF
#define ATREE_IMP                INTERN
#define ATREE_CALL               KCALL
#define Tkey                     vm_vpage_t
#define T                        struct vm_node
#define N_NODEPATH               vn_node
#define ATREE_LOCAL_SEMI0(Tkey)  VM_SEMI0
#define ATREE_LOCAL_LEVEL0(Tkey) VM_LEVEL0
#define ATREE_IMPLEMENTATION_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_IMPLEMENTATION_ONLY

/* Implement the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_parttree_##x
#define ATREE_FUN                INTDEF
#define ATREE_IMP                INTERN
#define ATREE_CALL               KCALL
#define Tkey                     vm_dpage_t
#define T                        struct vm_datapart
#define N_NODEPATH               dp_tree
#include <hybrid/sequence/atree-abi.h>


DECL_BEGIN

/* Reset VM-related locks while inside of the debugger. */
DEFINE_DBG_BZERO_OBJECT(vm_datablock_physical.db_lock);
DEFINE_DBG_BZERO_OBJECT(vm_datablock_anonymous.db_lock);
DEFINE_DBG_BZERO_OBJECT(vm_kernel.v_treelock);
DEFINE_DBG_BZERO_OBJECT(vm_kernel.v_tasklock);
DEFINE_DBG_BZERO_IF(THIS_VM != NULL, &THIS_VM->v_treelock, sizeof(((struct vm *)0)->v_treelock));
DEFINE_DBG_BZERO_IF(THIS_VM != NULL, &THIS_VM->v_tasklock, sizeof(((struct vm *)0)->v_tasklock));
DEFINE_DBG_BZERO_VECTOR(&vm_datablock_anonymous_zero_vec[0].db_lock,
                        COMPILER_LENOF(vm_datablock_anonymous_zero_vec),
                        sizeof(vm_datablock_anonymous_zero_vec[0].db_lock),
                        sizeof(vm_datablock_anonymous_zero_vec[0]));



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_free)(struct vm_datapart *__restrict self) {
	if (self->dp_flags & VM_DATAPART_FLAG_COREPRT) {
		vm_corepage_freepart(self);
	} else {
		kfree(self);
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_destroy)(struct vm_datapart *__restrict self,
                                   bool is_zero) {
	assert(!self->dp_crefs);
	assert(!self->dp_srefs);
	assert(!self->dp_stale);
	switch (self->dp_state) {

	case VM_DATAPART_STATE_INCORE:
	case VM_DATAPART_STATE_LOCKED:
		if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
			if (!(self->dp_flags & VM_DATAPART_FLAG_KEEPRAM)) {
				page_ffree(self->dp_ramdata.rd_block0.rb_start,
				           self->dp_ramdata.rd_block0.rb_size,
				           is_zero);
			}
		} else {
			if (!(self->dp_flags & VM_DATAPART_FLAG_KEEPRAM)) {
				size_t i;
				for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
					page_ffree(self->dp_ramdata.rd_blockv[i].rb_start,
					           self->dp_ramdata.rd_blockv[i].rb_size,
					           is_zero);
				}
			}
			kfree(self->dp_ramdata.rd_blockv);
		}
		break;

#ifndef CONFIG_NO_SWAP
	case VM_DATAPART_STATE_INSWAP:
		if (self->dp_swpdata.sd_blockv == &self->dp_swpdata.sd_block0) {
			if (!(self->dp_flags & VM_DATAPART_FLAG_KEEPRAM)) {
				swap_free(self->dp_swpdata.sd_block0.sb_start,
				          self->dp_swpdata.sd_block0.sb_size);
			}
		} else {
			if (!(self->dp_flags & VM_DATAPART_FLAG_KEEPRAM)) {
				size_t i;
				for (i = 0; i < self->dp_swpdata.sd_blockc; ++i) {
					swap_free(self->dp_swpdata.sd_blockv[i].sb_start,
					          self->dp_swpdata.sd_blockv[i].sb_size);
				}
			}
			kfree(self->dp_swpdata.sd_blockv);
		}
		break;
#endif /* !CONFIG_NO_SWAP */

	default: break;
	}
	if (self->dp_futex) {
		/* TODO */
	}
	if (self->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
		kfree(self->dp_pprop_p);
	xdecref(self->dp_block); /* May be NULL due to incomplete initialization... */
	vm_datapart_free(self);
}



#define VM_DATAPART_MUST_SERVICE_STALE(self) \
	(ATOMIC_READ((self)->dp_stale) != NULL)

PRIVATE NOBLOCK void
NOTHROW(KCALL vm_datapart_service_stale)(struct vm_datapart *__restrict self) {
	struct vm_node *chain, *next;
	chain = ATOMIC_XCH(self->dp_stale, NULL);
	while (chain) {
		next = chain->vn_byaddr.ln_next;
		assert(chain->vn_part == self);
		LLIST_REMOVE(chain, vn_link);
		weakdecref(chain->vn_vm); /* `weakincref()' in `vm_node_destroy()' */
		decref_unlikely(chain->vn_block);
		/*decref_nokill(self); // The reference to `vn_part' was already dropped! (s.a. `vm_node_destroy()') */
		vm_node_free(chain);
		chain = next;
	}
}


PUBLIC NONNULL((1)) void KCALL
vm_datapart_lock_read(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK) {
	sync_read(&self->dp_lock);
	if (VM_DATAPART_MUST_SERVICE_STALE(self) &&
	    sync_tryupgrade(self)) {
		vm_datapart_service_stale(self);
		sync_downgrade(self);
	}
}

PUBLIC NONNULL((1)) void KCALL
vm_datapart_lock_write(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK) {
	sync_write(&self->dp_lock);
	vm_datapart_service_stale(self);
}

PUBLIC NONNULL((1)) bool KCALL
vm_datapart_lock_upgrade(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool result = sync_upgrade(&self->dp_lock);
	vm_datapart_service_stale(self);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vm_datapart_lock_read_nx)(struct vm_datapart *__restrict self) {
	bool result = sync_read_nx(&self->dp_lock);
	if (result &&
	    VM_DATAPART_MUST_SERVICE_STALE(self) &&
	    sync_tryupgrade(self)) {
		vm_datapart_service_stale(self);
		sync_downgrade(self);
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vm_datapart_lock_write_nx)(struct vm_datapart *__restrict self) {
	bool result = sync_write_nx(&self->dp_lock);
	if (result)
		vm_datapart_service_stale(self);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL vm_datapart_lock_upgrade_nx)(struct vm_datapart *__restrict self) {
	unsigned int result;
	result = sync_upgrade_nx(&self->dp_lock);
	if (result)
		vm_datapart_service_stale(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) WUNUSED bool
NOTHROW(KCALL vm_datapart_lock_tryread)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_tryread(&self->dp_lock);
	if (result &&
	    VM_DATAPART_MUST_SERVICE_STALE(self) &&
	    sync_tryupgrade(self)) {
		vm_datapart_service_stale(self);
		sync_downgrade(self);
	}
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) WUNUSED bool
NOTHROW(KCALL vm_datapart_lock_trywrite)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_trywrite(&self->dp_lock);
	if (result)
		vm_datapart_service_stale(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) WUNUSED bool
NOTHROW(KCALL vm_datapart_lock_tryupgrade)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_tryupgrade(&self->dp_lock);
	if (result)
		vm_datapart_service_stale(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_lock_endwrite)(struct vm_datapart *__restrict self) {
again:
	sync_endwrite(&self->dp_lock);
	if unlikely(VM_DATAPART_MUST_SERVICE_STALE(self)) {
		if (sync_trywrite(&self->dp_lock)) {
			vm_datapart_service_stale(self);
			goto again;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_lock_endread)(struct vm_datapart *__restrict self) {
	sync_endread(&self->dp_lock);
again:
	if unlikely(VM_DATAPART_MUST_SERVICE_STALE(self)) {
		if (sync_trywrite(&self->dp_lock)) {
			vm_datapart_service_stale(self);
			sync_endwrite(&self->dp_lock);
			goto again;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_lock_end)(struct vm_datapart *__restrict self) {
	sync_end(&self->dp_lock);
again:
	if unlikely(VM_DATAPART_MUST_SERVICE_STALE(self)) {
		if (sync_trywrite(&self->dp_lock)) {
			vm_datapart_service_stale(self);
			sync_endwrite(&self->dp_lock);
			goto again;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_lock_downgrade)(struct vm_datapart *__restrict self) {
again:
	vm_datapart_service_stale(self);
	sync_downgrade(&self->dp_lock);
	if unlikely(VM_DATAPART_MUST_SERVICE_STALE(self)) {
		if (sync_tryupgrade(&self->dp_lock)) {
			vm_datapart_service_stale(self);
			goto again;
		}
	}
}

#ifndef __INTELLISENSE__
DECL_END

#define PART_RAM 1
#include "vm-alloc-free-part-data.c.inl"
#define PART_RAM 1
#define ALLOC_NX 1
#include "vm-alloc-free-part-data.c.inl"

#ifndef CONFIG_NO_SWAP
#define PART_SWAP 1
#include "vm-alloc-free-part-data.c.inl"
#define PART_SWAP 1
#define ALLOC_NX 1
#include "vm-alloc-free-part-data.c.inl"
#endif /* !CONFIG_NO_SWAP */

DECL_BEGIN
#endif


PRIVATE NOBLOCK void
NOTHROW(KCALL vm_set_fini)(struct pointer_set *__restrict self) {
	REF struct vm *v;
	POINTER_SET_FOREACH(v, self) {
		decref(v);
	}
	pointer_set_fini(self);
}

PRIVATE NOBLOCK void
NOTHROW(KCALL vm_set_clear)(struct pointer_set *__restrict self) {
	REF struct vm *v;
	POINTER_SET_FOREACH(v, self) {
		decref(v);
	}
	pointer_set_clear(self);
}




/* Collect all of the VMs that have mappings for `self'.
 * NOTE: The caller must be holding a read-lock on `self'
 * NOTE: Upon entry, `vms->ps_size == 0'
 * @return: == vms->ps_size: Successfully collected all VMs.
 * @return: > vms->ps_size:  Failed to allocate sufficient memory within
 *                           the pointer set to house all vm pointers.
 *                           The caller should unlock `self', then
 *                          `pointer_set_reset_rehash(vms,return)' to
 *                           allocate sufficient memory with the given
 *                           buffer, before re-attempting the call. */
PRIVATE NOBLOCK size_t
NOTHROW(KCALL vm_set_collect_from_datapart)(struct pointer_set *__restrict vms,
                                            struct vm_datapart *__restrict self) {
	struct vm_node *iter;
	size_t result = 0;
	unsigned int i;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assert(vms->ps_size == 0);
	for (i = 0; i < 2; ++i) {
		for (iter       = i ? self->dp_srefs : self->dp_crefs;
		     iter; iter = iter->vn_link.ln_next) {
			int error;
			REF struct vm *v = iter->vn_vm;
			assert(i ? (iter->vn_prot & VM_PROT_SHARED)
			         : !(iter->vn_prot & VM_PROT_SHARED) ||
			           wasdestroyed(v));
			if unlikely(!tryincref(v))
				continue; /* Dead VM (associated with an node that has become stale.) */
			error = pointer_set_insert_nx(vms,
			                              v,
			                              GFP_ATOMIC | GFP_LOCKED);
			if (error != POINTER_SET_INSERT_NX_SUCCESS)
				decref_unlikely(v);
			if (error == POINTER_SET_INSERT_NX_SUCCESS ||
			    error == POINTER_SET_INSERT_NX_FAILED)
				++result;
		}
	}
	assert(result >= vms->ps_size);
	if unlikely(result > vms->ps_size) {
		REF struct vm *v;
		POINTER_SET_FOREACH(v, vms) {
			decref_unlikely(v);
		}
	}
	return result;
}

PRIVATE NOBLOCK size_t
NOTHROW(KCALL vm_set_collect_from_datapart_crefs)(struct pointer_set *__restrict vms,
                                                  struct vm_datapart *__restrict self) {
	struct vm_node *iter;
	size_t result = 0;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assert(vms->ps_size == 0);
	for (iter       = self->dp_crefs;
	     iter; iter = iter->vn_link.ln_next) {
		int error;
		REF struct vm *v = iter->vn_vm;
		if unlikely(!tryincref(v))
			continue; /* Dead VM (associated with an node that has become stale.) */
		error = pointer_set_insert_nx(vms,
		                              v,
		                              GFP_ATOMIC | GFP_LOCKED);
		if (error != POINTER_SET_INSERT_NX_SUCCESS)
			decref_unlikely(v);
		if (error == POINTER_SET_INSERT_NX_SUCCESS ||
		    error == POINTER_SET_INSERT_NX_FAILED)
			++result;
	}
	assert(result >= vms->ps_size);
	if unlikely(result > vms->ps_size) {
		REF struct vm *v;
		POINTER_SET_FOREACH(v, vms) {
			decref_unlikely(v);
		}
	}
	return result;
}

/* Collect all nodes mapped as SHARED, who also have WRITE permissions. */
PRIVATE NOBLOCK size_t
NOTHROW(KCALL vm_set_collect_from_datapart_srefs_writable)(struct pointer_set *__restrict vms,
                                                           struct vm_datapart *__restrict self) {
	struct vm_node *iter;
	size_t result = 0;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assert(vms->ps_size == 0);
	for (iter       = self->dp_srefs;
	     iter; iter = iter->vn_link.ln_next) {
		int error;
		REF struct vm *v;
		assert(iter->vn_prot & VM_PROT_SHARED || wasdestroyed(iter->vn_vm));
		if (!(iter->vn_prot & VM_PROT_WRITE))
			continue; /* Not writable. */
		v = iter->vn_vm;
		if unlikely(!tryincref(v))
			continue; /* Dead VM (associated with an node that has become stale.) */
		error = pointer_set_insert_nx(vms,
		                              v,
		                              GFP_ATOMIC | GFP_LOCKED);
		if (error != POINTER_SET_INSERT_NX_SUCCESS)
			decref_unlikely(v);
		if (error == POINTER_SET_INSERT_NX_SUCCESS ||
		    error == POINTER_SET_INSERT_NX_FAILED)
			++result;
	}
	assert(result >= vms->ps_size);
	if unlikely(result > vms->ps_size) {
		REF struct vm *v;
		POINTER_SET_FOREACH(v, vms) {
			decref_unlikely(v);
		}
	}
	return result;
}



/* Try to acquire a write-lock to VMs that are apart of the given pointer set.
 * @return: * :   A pointer to the VM to which a write-lock could not be acquired.
 * @return: NULL: Successfully acquired a write-lock to all of the VMs. */
PRIVATE NOBLOCK struct vm *
NOTHROW(KCALL vm_set_locktrywrite_all)(struct pointer_set *__restrict self) {
	struct vm *v;
	size_t i;
	for (i = 0; i <= self->ps_mask; ++i) {
		struct vm *result;
		v = (struct vm *)self->ps_list[i];
		if (v == (struct vm *)POINTER_SET_SENTINAL)
			continue;
		if (sync_trywrite(v))
			continue;
		result = v;
		/* Release all of the locks that were already acquired. */
		while (i--) {
			v = (struct vm *)self->ps_list[i];
			if (v != (struct vm *)POINTER_SET_SENTINAL)
				sync_endwrite(v);
		}
		return result;
	}
	return NULL;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL vm_set_lockendwrite_all)(struct pointer_set *__restrict self) {
	struct vm *v;
	POINTER_SET_FOREACH(v, self) {
		sync_endwrite(v);
	}
}



LOCAL NOBLOCK WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL pprop_getbit)(uintptr_t const *__restrict base,
                            size_t index) {
	uintptr_t result;
	result = base[index / (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS)];
	index %= (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS);
	result >>= index * VM_DATAPART_PPP_BITS;
	return result & VM_DATAPART_PPP_MASK;
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pprop_setbit)(uintptr_t *__restrict base,
                            size_t index, uintptr_t value) {
	uintptr_t mask;
	assert(!(value & ~VM_DATAPART_PPP_MASK));
	base += index / (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS);
	index %= (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS);
	mask = (uintptr_t)VM_DATAPART_PPP_MASK << (index * VM_DATAPART_PPP_BITS);
	value <<= (index * VM_DATAPART_PPP_BITS);
	*base &= ~mask;
	*base |= value & mask;
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pprop_memcpy)(uintptr_t *__restrict dst_base,
                            uintptr_t const *__restrict src_base,
                            uintptr_t dst_offset,
                            uintptr_t src_offset,
                            size_t num_pages) {
	while (num_pages--) {
		uintptr_t value;
		value = pprop_getbit(src_base, src_offset);
		pprop_setbit(dst_base, dst_offset, value);
		++dst_offset;
		++src_offset;
	}
}



/* Map the given data part (which must be INCORE or LOCKED) into the current
 * page directory at the specified location, using the specified permissions.
 * NOTE: The caller is responsible to ensure that `self' doesn't change state
 *       or size, as well as to ensure that the given address range isn't already
 *       in use. - This function is merely a thin wrapper around `pagedir_map',
 *       which automatically allows for dealing with multi-part ram blocks.
 * NOTE: The caller is responsible to ensure that the target region of memory
 *       has been prepared in a prior call to `pagedir_prepare_map'
 * @param: perm: Set of `PAGEDIR_MAP_F*' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram)(struct vm_datapart *__restrict self,
                                   VIRT vm_vpage_t virt_page, u16 perm) {
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		pagedir_map(virt_page,
		            self->dp_ramdata.rd_block0.rb_size,
		            self->dp_ramdata.rd_block0.rb_start,
		            perm);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			pagedir_map(virt_page,
			            blocks[i].rb_size,
			            blocks[i].rb_start,
			            perm);
			virt_page += blocks[i].rb_size;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_p)(struct vm_datapart *__restrict self,
                                     PAGEDIR_P_SELFTYPE pdir,
                                     VIRT vm_vpage_t virt_page, u16 perm) {
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		pagedir_map_p(pdir,
		              virt_page,
		              self->dp_ramdata.rd_block0.rb_size,
		              self->dp_ramdata.rd_block0.rb_start,
		              perm);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			pagedir_map_p(pdir,
			              virt_page,
			              blocks[i].rb_size,
			              blocks[i].rb_start,
			              perm);
			virt_page += blocks[i].rb_size;
		}
	}
}


LOCAL NOBLOCK u16
NOTHROW(KCALL vm_datapart_get_page_permissions)(struct vm_datapart *__restrict self,
                                                size_t offset, u16 perm) {
	uintptr_t mode;
	unsigned int shift;
	shift = VM_DATABLOCK_PAGESHIFT(self->dp_block);
	if (shift == 0) {
		mode = VM_DATAPART_GETSTATE(self,
		                            (vm_dpage_t)offset);
		if (mode == VM_DATAPART_PPP_HASCHANGED)
			;
		else if (mode == VM_DATAPART_PPP_INITIALIZED) {
			if (self->dp_flags & VM_DATAPART_FLAG_TRKCHNG)
				perm &= ~PAGEDIR_MAP_FWRITE; /* Delete write, so we can track changes */
		} else                               /*if (mode == VM_DATAPART_PPP_UNINITIALIZED)*/
			perm &= ~(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC);
	} else {
		size_t i;
		vm_dpage_t start_offset;
		size_t count = (size_t)1 << shift;
		start_offset = (vm_dpage_t)offset << shift;
		for (i = 0; i < count; ++i) {
			mode = VM_DATAPART_GETSTATE(self, start_offset + i);
			if (mode == VM_DATAPART_PPP_HASCHANGED)
				;
			else if (mode == VM_DATAPART_PPP_INITIALIZED) {
				if (self->dp_flags & VM_DATAPART_FLAG_TRKCHNG)
					perm &= ~PAGEDIR_MAP_FWRITE; /* Delete write, so we can track changes */
			} else                               /*if (mode == VM_DATAPART_PPP_UNINITIALIZED)*/
				perm &= ~(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC);
		}
	}
	return perm;
}



/* Same as `vm_datapart_map_ram()', but automatically restrict permissions:
 *  - Pages not fully marked as changed are mapped as read-only, unless
 *    the `VM_DATAPART_FLAG_TRKCHNG' bit isn't set in `self'
 *  - Pages not fully initialized are mapped as invalid-access, meaning
 *    that a page-fault will be triggered upon first use of that memory.
 * @param: perm: Set of `PAGEDIR_MAP_F*' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_autoprop)(struct vm_datapart *__restrict self,
                                            VIRT vm_vpage_t virt_page, u16 perm) {
	size_t start_offset, offset, count;
	u16 use_perm, new_perm;
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		offset = 0;
		count  = self->dp_ramdata.rd_block0.rb_size;
		do {
			start_offset = offset;
			use_perm     = vm_datapart_get_page_permissions(self, offset, perm);
			for (++offset; offset < count; ++offset) {
				new_perm = vm_datapart_get_page_permissions(self, offset, perm);
				if (new_perm != use_perm)
					break;
			}
			pagedir_map(virt_page + start_offset,
			            offset - start_offset,
			            self->dp_ramdata.rd_block0.rb_start + start_offset,
			            use_perm);
		} while (offset < count);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		offset = 0;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			count = blocks[i].rb_size;
			do {
				start_offset = offset;
				use_perm     = vm_datapart_get_page_permissions(self, offset, perm);
				for (++offset; offset < count; ++offset) {
					new_perm = vm_datapart_get_page_permissions(self, offset, perm);
					if (new_perm != use_perm)
						break;
				}
				pagedir_map(virt_page + start_offset,
				            offset - start_offset,
				            blocks[i].rb_start + start_offset,
				            use_perm);
			} while (offset < count);
			assert(offset == count);
			assert(count == blocks[i].rb_size);
			virt_page += count;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_autoprop_p)(struct vm_datapart *__restrict self,
                                              PAGEDIR_P_SELFTYPE pdir,
                                              VIRT vm_vpage_t virt_page, u16 perm) {
	size_t start_offset, offset, count;
	u16 use_perm, new_perm;
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		offset = 0;
		count  = self->dp_ramdata.rd_block0.rb_size;
		do {
			start_offset = offset;
			use_perm     = vm_datapart_get_page_permissions(self, offset, perm);
			for (++offset; offset < count; ++offset) {
				new_perm = vm_datapart_get_page_permissions(self, offset, perm);
				if (new_perm != use_perm)
					break;
			}
			pagedir_map_p(pdir,
			              virt_page + start_offset,
			              offset - start_offset,
			              self->dp_ramdata.rd_block0.rb_start + start_offset,
			              use_perm);
		} while (offset < count);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		offset = 0;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			count = blocks[i].rb_size;
			do {
				start_offset = offset;
				use_perm     = vm_datapart_get_page_permissions(self, offset, perm);
				for (++offset; offset < count; ++offset) {
					new_perm = vm_datapart_get_page_permissions(self, offset, perm);
					if (new_perm != use_perm)
						break;
				}
				pagedir_map_p(pdir,
				              virt_page + start_offset,
				              offset - start_offset,
				              blocks[i].rb_start + start_offset,
				              use_perm);
			} while (offset < count);
			assert(offset == count);
			assert(count == blocks[i].rb_size);
			virt_page += count;
		}
	}
}


/* Enumerate physical memory of `self' within the given address range.
 * NOTE: The caller must be holding a read-lock on `self', as well as ensure
 *       that the given address range is in-bounds, that `self' is either
 *       INCORE or LOCKED, and that `num_bytes' is non-zero. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL vm_datapart_do_enumdma)(struct vm_datapart *__restrict self,
                                      vm_dmarangefunc_t prange, void *arg,
                                      size_t partrel_start, size_t num_bytes,
                                      struct vm_dmalock *__restrict lock) {
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assert(num_bytes != 0);
	assert(partrel_start + num_bytes > partrel_start);
	assert(partrel_start + num_bytes <= vm_datapart_numbytes(self));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	assert(lock->dl_part == self);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		/* Simple case: Single-block ram data. */
		(*prange)(arg,
		          VM_PPAGE2ADDR(self->dp_ramdata.rd_block0.rb_start) + partrel_start,
		          num_bytes,
		          lock);
	} else {
		size_t i, count;
		u64 blocksize;
		struct vm_ramblock *blocks;
		count  = self->dp_ramdata.rd_blockc;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0;; ++i) {
			assert(i < count);
			blocksize = (u64)blocks[i].rb_size * PAGESIZE;
			if ((u64)partrel_start < blocksize)
				break;
			partrel_start -= (size_t)blocksize;
		}
		blocksize -= partrel_start;
		for (;;) {
			size_t copysize = num_bytes;
			if ((u64)copysize > blocksize)
				copysize = (size_t)blocksize;
			(*prange)(arg,
			          VM_PPAGE2ADDR(blocks[i].rb_start) + partrel_start,
			          copysize,
			          lock);
			if (copysize >= num_bytes)
				break;
			num_bytes -= copysize;
			++i;
			assert(i < count);
			blocksize     = (u64)blocks[i].rb_size * PAGESIZE;
			partrel_start = 0;
		}
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_insert_ignore_missmatch)(struct vm_node *__restrict self) {
	struct vm_node **pinsert, *insert_before;
	struct vm *v = self->vn_vm;
	assert(v);
	assertf(VM_NODE_MIN(self) <= VM_NODE_MAX(self),
	        "Unordered node: MIN(%p) >= MAX(%p)",
	        VM_NODE_MINADDR(self), VM_NODE_MAXADDR(self));
	assertf(VM_NODE_MAX(self) <= VM_VPAGE_MAX,
	        "Mapping of node covering pages %p...%p is out-of-bounds",
	        VM_NODE_MIN(self), VM_NODE_MAX(self));
	assert(self->vn_block ? true : !self->vn_part);
#if 0
	assertf(!self->vn_part ||
	        VM_NODE_SIZE(self) == vm_datapart_numvpages(self->vn_part),
	        "Node size missmatch (%Iu != %Iu)",
	        VM_NODE_SIZE(self), vm_datapart_numvpages(self->vn_part));
#endif
	assert((v->v_tree != NULL) == (v->v_byaddr != NULL));
	assert(self->vn_vm == v);
	vm_nodetree_insert(&v->v_tree, self);
	/* Figure out where we need to insert the self. */
	pinsert = &v->v_byaddr;
	while ((insert_before = *pinsert) != NULL &&
	       (insert_before->vn_node.a_vmax < self->vn_node.a_vmin))
		pinsert = &insert_before->vn_byaddr.ln_next;
	assertf(!insert_before ||
	        self->vn_node.a_vmax < insert_before->vn_node.a_vmin,
	        "insert_before  = %p:%p...%p\n"
	        "self           = %p:%p...%p\n"
	        "self->vn_flags = %#.4I16x\n",
	        insert_before, VM_NODE_MINADDR(insert_before), VM_NODE_MAXADDR(insert_before),
	        self, VM_NODE_MINADDR(self), VM_NODE_MAXADDR(self),
	        self->vn_flags);
	/* Insert the self before `insert' at `pinsert' */
	self->vn_byaddr.ln_pself = pinsert;
	self->vn_byaddr.ln_next  = insert_before;
	if (insert_before)
		insert_before->vn_byaddr.ln_pself = &self->vn_byaddr.ln_next;
	*pinsert = self;
}


#ifndef __INTELLISENSE__
DECL_END

#define SPLIT_NX 1
#include "vm-datapart-split.c.inl"
#include "vm-datapart-split.c.inl"

DECL_BEGIN
#endif

/* Free RAM allocated by `vm_do_allocram(_nx)'
 * NOTE: This function assumes that the allocated memory hasn't been used, yet. */
PUBLIC NONNULL((1, 2)) NOBLOCK void
NOTHROW(KCALL vm_do_ccfreeram)(struct vm_ramblock *__restrict pblock0,
                               struct vm_ramblock *__restrict blocks) {
	if (blocks == pblock0) {
		page_ccfree(blocks->rb_start,
		            blocks->rb_size);
	} else {
		size_t i, count = *(size_t *)pblock0;
		for (i = 0; i < count; ++i) {
			page_ccfree(blocks[i].rb_start,
			            blocks[i].rb_size);
		}
		kfree(blocks);
	}
}

PUBLIC NONNULL((1, 2)) NOBLOCK void
NOTHROW(KCALL vm_do_ffreeram)(struct vm_ramblock *__restrict pblock0,
                              struct vm_ramblock *__restrict blocks,
                              bool is_zero) {
	if (blocks == pblock0) {
		page_ffree(blocks->rb_start,
		           blocks->rb_size,
		           is_zero);
	} else {
		size_t i, count = *(size_t *)pblock0;
		for (i = 0; i < count; ++i) {
			page_ffree(blocks[i].rb_start,
			           blocks[i].rb_size,
			           is_zero);
		}
		kfree(blocks);
	}
}

PUBLIC NONNULL((1, 2)) NOBLOCK void
NOTHROW(KCALL vm_do_freeram)(struct vm_ramblock *__restrict pblock0,
                             struct vm_ramblock *__restrict blocks) {
	if (blocks == pblock0) {
		page_free(blocks->rb_start,
		          blocks->rb_size);
	} else {
		size_t i, count = *(size_t *)pblock0;
		for (i = 0; i < count; ++i) {
			page_free(blocks[i].rb_start,
			          blocks[i].rb_size);
		}
		kfree(blocks);
	}
}


/* Similar to `vm_datapart_allocram()', but leave all locking & state changes up to the caller. */
PUBLIC NONNULL((1)) void KCALL
vm_datapart_do_allocram(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	self->dp_ramdata.rd_blockv = vm_do_allocram(&self->dp_ramdata.rd_block0,
	                                            vm_datapart_numvpages(self),
	                                            GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
}

PUBLIC NONNULL((1)) bool
NOTHROW(KCALL vm_datapart_do_allocram_nx)(struct vm_datapart *__restrict self,
                                          gfp_t flags) {
	struct vm_ramblock *blocks;
	blocks = vm_do_allocram_nx(&self->dp_ramdata.rd_block0,
	                           vm_datapart_numvpages(self),
	                           flags);
	if unlikely(!blocks)
		return false;
	self->dp_ramdata.rd_blockv = blocks;
	return true;
}


/* Copy the physical memory backing of `src' into `dst'.
 * The caller is responsible to ensure that both parts are INCORE or LOCKED,
 * as well as to provide for both parts to be properly locked. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_do_copyram)(struct vm_datapart *__restrict dst,
                                      struct vm_datapart *__restrict src) {
	assertf(dst->dp_state == VM_DATAPART_STATE_INCORE ||
	        dst->dp_state == VM_DATAPART_STATE_LOCKED,
	        "dst->dp_state = %Iu", (uintptr_t)dst->dp_state);
	assertf(src->dp_state == VM_DATAPART_STATE_INCORE ||
	        src->dp_state == VM_DATAPART_STATE_LOCKED,
	        "src->dp_state = %Iu", (uintptr_t)src->dp_state);
	assertf(vm_datapart_numvpages(dst) == vm_datapart_numvpages(src),
	        "vm_datapart_numvpages(dst) = %Iu\n"
	        "vm_datapart_numvpages(src) = %Iu\n",
	        vm_datapart_numvpages(dst),
	        vm_datapart_numvpages(src));
	if (src->dp_ramdata.rd_blockv == &src->dp_ramdata.rd_block0) {
		if (dst->dp_ramdata.rd_blockv == &dst->dp_ramdata.rd_block0) {
			/* SINGLE --> SINGLE */
			assert(dst->dp_ramdata.rd_block0.rb_size ==
			       src->dp_ramdata.rd_block0.rb_size);
			vm_copyinphys(VM_PPAGE2ADDR(dst->dp_ramdata.rd_block0.rb_start),
			              VM_PPAGE2ADDR(src->dp_ramdata.rd_block0.rb_start),
			              src->dp_ramdata.rd_block0.rb_size * PAGESIZE);
		} else {
			/* SINGLE --> MULTIPLE */
			size_t i;
			vm_ppage_t src_page;
			struct vm_ramblock *dst_blocks;
			src_page   = src->dp_ramdata.rd_block0.rb_start;
			dst_blocks = dst->dp_ramdata.rd_blockv;
			for (i = 0; i < dst->dp_ramdata.rd_blockc; ++i) {
				size_t num_pages;
				num_pages = dst_blocks[i].rb_size;
				vm_copyinphys(VM_PPAGE2ADDR(dst_blocks[i].rb_start),
				              VM_PPAGE2ADDR(src_page),
				              num_pages * PAGESIZE);
				src_page += num_pages;
			}
			assert(src->dp_ramdata.rd_block0.rb_start +
			       src->dp_ramdata.rd_block0.rb_size ==
			       src_page);
		}
	} else if (dst->dp_ramdata.rd_blockv == &dst->dp_ramdata.rd_block0) {
		/* MULTIPLE --> SINGLE */
		size_t i;
		vm_ppage_t dst_page;
		struct vm_ramblock *src_blocks;
		dst_page   = dst->dp_ramdata.rd_block0.rb_start;
		src_blocks = src->dp_ramdata.rd_blockv;
		for (i = 0; i < src->dp_ramdata.rd_blockc; ++i) {
			size_t num_pages;
			num_pages = src_blocks[i].rb_size;
			vm_copyinphys(VM_PPAGE2ADDR(dst_page),
			              VM_PPAGE2ADDR(src_blocks[i].rb_start),
			              num_pages * PAGESIZE);
			dst_page += num_pages;
		}
		assert(dst->dp_ramdata.rd_block0.rb_start +
		       dst->dp_ramdata.rd_block0.rb_size ==
		       dst_page);
	} else {
		/* MULTIPLE --> MULTIPLE */
		size_t dst_i, src_i, dst_count;
		struct vm_ramblock *dst_blocks;
		struct vm_ramblock *src_blocks;
		struct vm_ramblock src_block;
		dst_count  = dst->dp_ramdata.rd_blockc;
		dst_blocks = dst->dp_ramdata.rd_blockv;
		src_blocks = src->dp_ramdata.rd_blockv;
		src_i = 1, src_block = src_blocks[0];
		for (dst_i = 0; dst_i < dst_count; ++dst_i) {
			struct vm_ramblock b = dst_blocks[dst_i];
			while (b.rb_size) {
				size_t copy_size = b.rb_size;
				if (!src_block.rb_size) {
					assert(src_i < src->dp_ramdata.rd_blockc);
					src_block = src_blocks[src_i++];
				}
				assert(src_block.rb_size != 0);
				if (copy_size > src_block.rb_size)
					copy_size = src_block.rb_size;
				vm_copyinphys(VM_PPAGE2ADDR(b.rb_start),
				              VM_PPAGE2ADDR(src_block.rb_start),
				              copy_size * PAGESIZE);
				src_block.rb_start += copy_size;
				src_block.rb_size -= copy_size;
				b.rb_start += copy_size;
				b.rb_size -= copy_size;
			}
		}
		assert(dst_i == dst_count);
		assert(src_i == src->dp_ramdata.rd_blockc - 1 &&
		       src_block.rb_size == 0);
	}
}




/* Return codes for `vm_datapart_do_setcore[_nx]' */
#define VM_DATAPART_DO_SETCORE_SUCCESS          0
#define VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED 1
#define VM_DATAPART_DO_SETCORE_FAILED           2 /* (Only returned by *_nx variant: the lock was released, and the operation failed) */

/* Return codes for `vm_datapart_do_unshare_cow[_nx]' */
#define VM_DATAPART_DO_UNSHARE_COW_SUCCESS          0
#define VM_DATAPART_DO_UNSHARE_COW_SUCCESS_RELOCKED 1
#define VM_DATAPART_DO_UNSHARE_COW_CHANGED          2 /* The state has changed... */
#define VM_DATAPART_DO_UNSHARE_COW_FAILED           3 /* (Only returned by *_nx variant: the lock was released, and the operation failed) */

#ifdef __INTELLISENSE__
PRIVATE NONNULL((1)) unsigned int FCALL vm_datapart_do_setcore(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK, E_BADALLOC);
PRIVATE NONNULL((1)) unsigned int FCALL vm_datapart_do_unshare_cow(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK, E_BADALLOC);
PRIVATE NONNULL((1)) unsigned int NOTHROW(FCALL vm_datapart_do_setcore_nx)(struct vm_datapart *__restrict self);
PRIVATE NONNULL((1)) unsigned int NOTHROW(FCALL vm_datapart_do_unshare_cow_nx)(struct vm_datapart *__restrict self);
#else
DECL_END

#define EXLOCK_NX 1
#include "vm-datapart-exlock.c.inl"
#include "vm-datapart-exlock.c.inl"

DECL_BEGIN
#endif


/* Acquire a write-lock on `self', and ensure that the part's
 * state is set to the part being loaded as INCORE or LOCKED. */
PUBLIC NONNULL((1)) void FCALL
vm_datapart_lockwrite_setcore(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	sync_write(self);
	if (self->dp_state != VM_DATAPART_STATE_INCORE &&
	    self->dp_state != VM_DATAPART_STATE_LOCKED)
		vm_datapart_do_setcore(self);
	assert(sync_writing(self));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
}

/* A combination of `vm_datapart_lockwrite_unsharecow()' and `vm_datapart_lockwrite_setcore()'
 * Ensure that no copy-on-write mappings exist, and that `self' is to be in-core. */
PUBLIC NONNULL((1)) void FCALL
vm_datapart_lockwrite_setcore_unsharecow(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	sync_write(self);
again_checkstate:
	if (self->dp_state != VM_DATAPART_STATE_INCORE &&
	    self->dp_state != VM_DATAPART_STATE_LOCKED)
		vm_datapart_do_setcore(self);
	if (self->dp_crefs != NULL) {
		unsigned int error;
do_unshare_cow:
		error = vm_datapart_do_unshare_cow(self);
		if (error == VM_DATAPART_DO_UNSHARE_COW_CHANGED)
			goto again_checkstate;
		if (error == VM_DATAPART_DO_UNSHARE_COW_SUCCESS_RELOCKED) {
			COMPILER_READ_BARRIER();
			if unlikely(self->dp_state != VM_DATAPART_STATE_INCORE &&
			            self->dp_state != VM_DATAPART_STATE_LOCKED) {
				error = vm_datapart_do_setcore(self);
				if unlikely(error == VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED) {
					COMPILER_READ_BARRIER();
					if unlikely(self->dp_crefs != NULL)
						goto do_unshare_cow;
				}
			}
		}
	}
	assert(sync_writing(self));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	assert(self->dp_crefs == NULL);
}

/* Same as the functions above, but only need to acquire a read-lock. */
PUBLIC NONNULL((1)) void FCALL
vm_datapart_lockread_setcore(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	sync_read(self);
	if (self->dp_state != VM_DATAPART_STATE_INCORE &&
	    self->dp_state != VM_DATAPART_STATE_LOCKED) {
		if (sync_upgrade(self)) {
			vm_datapart_do_setcore(self);
		} else {
			COMPILER_READ_BARRIER();
			if likely(self->dp_state != VM_DATAPART_STATE_INCORE &&
			          self->dp_state != VM_DATAPART_STATE_LOCKED)
				vm_datapart_do_setcore(self);
		}
		sync_downgrade(self);
	}
	assert(sync_reading(self));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
}

PUBLIC NONNULL((1)) void FCALL
vm_datapart_lockread_setcore_unsharecow(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	sync_read(self);
	if ((self->dp_state != VM_DATAPART_STATE_INCORE &&
	     self->dp_state != VM_DATAPART_STATE_LOCKED) ||
	    self->dp_crefs != NULL) {
		sync_upgrade(self);
		COMPILER_READ_BARRIER();
again_checkstate:
		if (self->dp_state != VM_DATAPART_STATE_INCORE &&
		    self->dp_state != VM_DATAPART_STATE_LOCKED)
			vm_datapart_do_setcore(self);
		if (self->dp_crefs != NULL) {
			unsigned int error;
do_unshare_cow:
			error = vm_datapart_do_unshare_cow(self);
			if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_CHANGED)
				goto again_checkstate;
			if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_SUCCESS_RELOCKED) {
				COMPILER_READ_BARRIER();
				if unlikely(self->dp_state != VM_DATAPART_STATE_INCORE &&
				            self->dp_state != VM_DATAPART_STATE_LOCKED) {
					error = vm_datapart_do_setcore(self);
					if unlikely(error == VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED) {
						COMPILER_READ_BARRIER();
						if unlikely(self->dp_crefs != NULL)
							goto do_unshare_cow;
					}
				}
			}
		}
		sync_downgrade(self);
	}
	assert(sync_reading(self));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	assert(self->dp_crefs == NULL);
}


/* Noexcept variants of the above locking functions. */
PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(FCALL vm_datapart_lockwrite_setcore_nx)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_write_nx(self);
	if likely(result) {
		unsigned int error;
		if (self->dp_state != VM_DATAPART_STATE_INCORE &&
		    self->dp_state != VM_DATAPART_STATE_LOCKED) {
			error = vm_datapart_do_setcore_nx(self);
			if unlikely(error == VM_DATAPART_DO_SETCORE_FAILED)
				return false;
		}
		assert(sync_writing(self));
		assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
		       self->dp_state == VM_DATAPART_STATE_LOCKED);
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(FCALL vm_datapart_lockwrite_setcore_unsharecow_nx)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_write_nx(self);
	if likely(result) {
		unsigned int error;
again_checkstate:
		if (self->dp_state != VM_DATAPART_STATE_INCORE &&
		    self->dp_state != VM_DATAPART_STATE_LOCKED) {
			error = vm_datapart_do_setcore_nx(self);
			if (error == VM_DATAPART_DO_SETCORE_FAILED)
				return false;
		}
		if (self->dp_crefs != NULL) {
do_unshare_cow:
			error = vm_datapart_do_unshare_cow(self);
			if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_FAILED)
				return false;
			if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_CHANGED)
				goto again_checkstate;
			if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_SUCCESS_RELOCKED) {
				COMPILER_READ_BARRIER();
				if unlikely(self->dp_state != VM_DATAPART_STATE_INCORE &&
				            self->dp_state != VM_DATAPART_STATE_LOCKED) {
					error = vm_datapart_do_setcore(self);
					if unlikely(error == VM_DATAPART_DO_SETCORE_FAILED)
						return false;
					if unlikely(error == VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED) {
						COMPILER_READ_BARRIER();
						if unlikely(self->dp_crefs != NULL)
							goto do_unshare_cow;
					}
				}
			}
		}
		assert(sync_writing(self));
		assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
		       self->dp_state == VM_DATAPART_STATE_LOCKED);
		assert(self->dp_crefs == NULL);
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(FCALL vm_datapart_lockread_setcore_nx)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_read_nx(self);
	if likely(result) {
		unsigned int error;
		if (self->dp_state != VM_DATAPART_STATE_INCORE &&
		    self->dp_state != VM_DATAPART_STATE_LOCKED) {
			error = sync_upgrade_nx(self);
			if unlikely(!error)
				return false;
			if (error == 2) {
				error = vm_datapart_do_setcore_nx(self);
check_setcore_error:
				if unlikely(error == VM_DATAPART_DO_SETCORE_FAILED)
					return false;
			} else {
				COMPILER_READ_BARRIER();
				if likely(self->dp_state != VM_DATAPART_STATE_INCORE &&
				          self->dp_state != VM_DATAPART_STATE_LOCKED) {
					error = vm_datapart_do_setcore_nx(self);
					goto check_setcore_error;
				}
			}
			sync_downgrade(self);
		}
		assert(sync_reading(self));
		assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
		       self->dp_state == VM_DATAPART_STATE_LOCKED);
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(FCALL vm_datapart_lockread_setcore_unsharecow_nx)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_read_nx(self);
	if likely(result) {
		if ((self->dp_state != VM_DATAPART_STATE_INCORE &&
		     self->dp_state != VM_DATAPART_STATE_LOCKED) ||
		    self->dp_crefs != NULL) {
			unsigned int error;
			error = sync_upgrade_nx(self);
			if unlikely(!error)
				return false;
			COMPILER_READ_BARRIER();
again_checkstate:
			if (self->dp_state != VM_DATAPART_STATE_INCORE &&
			    self->dp_state != VM_DATAPART_STATE_LOCKED) {
				error = vm_datapart_do_setcore_nx(self);
				if unlikely(error == VM_DATAPART_DO_SETCORE_FAILED)
					return false;
			}
			if (self->dp_crefs != NULL) {
				unsigned int error;
do_unshare_cow:
				error = vm_datapart_do_unshare_cow_nx(self);
				if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_FAILED)
					return false;
				if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_CHANGED)
					goto again_checkstate;
				if unlikely(error == VM_DATAPART_DO_UNSHARE_COW_SUCCESS_RELOCKED) {
					COMPILER_READ_BARRIER();
					if unlikely(self->dp_state != VM_DATAPART_STATE_INCORE &&
					            self->dp_state != VM_DATAPART_STATE_LOCKED) {
						error = vm_datapart_do_setcore_nx(self);
						if unlikely(error == VM_DATAPART_DO_SETCORE_FAILED)
							return false;
						if unlikely(error == VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED) {
							COMPILER_READ_BARRIER();
							if unlikely(self->dp_crefs != NULL)
								goto do_unshare_cow;
						}
					}
				}
			}
			sync_downgrade(self);
		}
		assert(sync_reading(self));
		assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
		       self->dp_state == VM_DATAPART_STATE_LOCKED);
		assert(self->dp_crefs == NULL);
	}
	return result;
}





/* Return the address of a physical page at the given `vpage_offset'
 * The caller must be holding a read- or write-lock on `self',
 * as well as guaranty that the part is either INCORE or LOCKED. */
PUBLIC NOBLOCK NONNULL((1)) vm_ppage_t
NOTHROW(KCALL vm_datapart_pageaddr)(struct vm_datapart *__restrict self,
                                    size_t vpage_offset) {
	vm_ppage_t result;
	assertf(vpage_offset < vm_datapart_numvpages(self),
	        "vpage_offset                = %Iu\n"
	        "vm_datapart_numvpages(self) = %Iu\n",
	        vpage_offset, vm_datapart_numvpages(self));
	assertf(self->dp_ramdata.rd_blockv, "Unset `rd_blockv' in datapart at %p", self);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		result = self->dp_ramdata.rd_block0.rb_start + vpage_offset;
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0;; ++i) {
			if (vpage_offset < blocks[i].rb_size) {
				result = blocks[i].rb_start + vpage_offset;
				break;
			}
			vpage_offset -= blocks[i].rb_size;
		}
	}
	return result;
}


/* Ensure that the page at `vpage_offset' has been initialized
 * The caller must be holding a read- or write-lock on `self',
 * as well as guaranty that the part is either INCORE or LOCKED.
 * HINT: The easiest way to ensure this is through
 *       use of `vm_datapart_lockread_setcore()'
 * @param: vpage_offset: The offset of the page to load.
 *                       The caller must ensure that this is `< vm_datapart_numvpages(self)'
 * @param: pchanged: [IN]  If `true', mark the associated page as changed, instead of initialized.
 * @param: pchanged: [OUT] Set to true if all associated data-pages are marked as changed.
 * @throw: * : Only throws whatever exception may get thrown by `dt_loadpart', meaning that
 *             when the loadpart function is NOEXCEPT, then so is this function! */
PUBLIC NONNULL((1, 3)) vm_ppage_t KCALL
vm_datapart_loadpage(struct vm_datapart *__restrict self,
                     size_t vpage_offset,
                     bool *__restrict pchanged)
		THROWS(...) {
	unsigned int page_shift;
	vm_ppage_t result;
	uintptr_t page_state;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assertf(self->dp_state == VM_DATAPART_STATE_INCORE ||
	        self->dp_state == VM_DATAPART_STATE_LOCKED,
	        "self->dp_state = %Iu", (uintptr_t)self->dp_state);
	assertf(vpage_offset < vm_datapart_numvpages(self),
	        "vpage_offset                = %Iu\n"
	        "vm_datapart_numvpages(self) = %Iu\n",
	        vpage_offset, vm_datapart_numvpages(self));
	/* Figure out the address of the associated physical memory page. */
	result     = vm_datapart_pageaddr(self, vpage_offset);
	page_shift = VM_DATABLOCK_PAGESHIFT(self->dp_block);
	if (page_shift == 0) {
		/* No page shift --> Only a single bit to check/modify */
again_readstate:
		page_state = VM_DATAPART_GETSTATE(self, vpage_offset);
		switch (page_state) {

		case VM_DATAPART_PPP_UNINITIALIZED:
			/* It seems to fall upon us to initialize this page! */
			if (!VM_DATAPART_CMPXCHSTATE(self,
			                             (vm_dpage_t)vpage_offset,
			                             VM_DATAPART_PPP_UNINITIALIZED,
			                             VM_DATAPART_PPP_INITIALIZING))
				goto again_readstate;
			TRY {
				void (KCALL *dt_loadpart)(struct vm_datablock * __restrict,
				                          vm_dpage_t, vm_phys_t, size_t);
				/* Invoke a custom load protocol of the associated datablock. */
				dt_loadpart = self->dp_block->db_type->dt_loadpart;
				if likely(dt_loadpart) {
					assert(!wasdestroyed(self));
					(*dt_loadpart)(self->dp_block,
					               vm_datapart_startdpage(self) + vpage_offset,
					               VM_PPAGE2ADDR(result),
					               1);
					assert(!wasdestroyed(self));
				}
			} EXCEPT {
				VM_DATAPART_SETSTATE(self,
				                     (vm_dpage_t)vpage_offset,
				                     VM_DATAPART_PPP_UNINITIALIZED);
				RETHROW();
			}
			/* Update the part's state to either indicate change, or full initialization */
			if (*pchanged) {
				VM_DATAPART_SETSTATE(self,
				                     (vm_dpage_t)vpage_offset,
				                     VM_DATAPART_PPP_HASCHANGED);
				goto set_datapart_changed;
			}
			VM_DATAPART_SETSTATE(self,
			                     (vm_dpage_t)vpage_offset,
			                     VM_DATAPART_PPP_INITIALIZED);
			break;

		case VM_DATAPART_PPP_INITIALIZING:
			/* Wait for the initialization to be completed. */
			task_tryyield_or_pause();
			goto again_readstate;

		case VM_DATAPART_PPP_INITIALIZED:
			if (*pchanged) {
				if (!VM_DATAPART_CMPXCHSTATE(self,
				                             (vm_dpage_t)vpage_offset,
				                             VM_DATAPART_PPP_INITIALIZED,
				                             VM_DATAPART_PPP_HASCHANGED))
					goto again_readstate;
set_datapart_changed:
				if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) & VM_DATAPART_FLAG_CHANGED)) {
					void (KCALL *dt_changed)(struct vm_datablock * __restrict,
					                         struct vm_datapart * __restrict);
					dt_changed = self->dp_block->db_type->dt_changed;
					if (dt_changed)
						(*dt_changed)(self->dp_block, self);
				}
			}
			break;

		case VM_DATAPART_PPP_HASCHANGED:
			*pchanged = true;
			break;

		default: __builtin_unreachable();
		}
	} else {
		vm_dpage_t starting_data_page;
		size_t pagemask;
		unsigned int n_data_pages, addrshift;
		bool result_has_changed = false;
		pagemask                = VM_DATABLOCK_PAGEMASK(self->dp_block);
		addrshift               = VM_DATABLOCK_ADDRSHIFT(self->dp_block);
		starting_data_page      = (vm_dpage_t)vpage_offset << page_shift;
		n_data_pages            = 1 << page_shift;
		for (; n_data_pages; --n_data_pages, ++starting_data_page) {
again_readstate_multi:
			page_state = VM_DATAPART_GETSTATE(self, starting_data_page);
			switch (page_state) {

			case VM_DATAPART_PPP_UNINITIALIZED: {
				unsigned int i, num_init_pages;
				/* Try to initialize multiple consecutive parts all at once! */
				if (!VM_DATAPART_CMPXCHSTATE(self,
				                             starting_data_page,
				                             VM_DATAPART_PPP_UNINITIALIZED,
				                             VM_DATAPART_PPP_INITIALIZING))
					goto again_readstate_multi;
				num_init_pages = 1;
				assertf(starting_data_page < (vm_dpage_t)vm_datapart_numdpages(self),
				        "starting_data_page          = %I64p\n"
				        "vm_datapart_numdpages(self) = %I64p\n",
				        (u64)starting_data_page, (u64)vm_datapart_numdpages(self));
				assertf((starting_data_page + n_data_pages) <= (vm_dpage_t)vm_datapart_numdpages(self),
				        "starting_data_page          = %I64p\n"
				        "n_data_pages                = %u\n"
				        "vm_datapart_numdpages(self) = %I64p\n",
				        (u64)starting_data_page, n_data_pages, (u64)vm_datapart_numdpages(self));
				while (num_init_pages < n_data_pages &&
				       VM_DATAPART_CMPXCHSTATE(self,
				                               starting_data_page + num_init_pages,
				                               VM_DATAPART_PPP_UNINITIALIZED,
				                               VM_DATAPART_PPP_INITIALIZING))
					++num_init_pages;
				TRY {
					void (KCALL *dt_loadpart)(struct vm_datablock * __restrict,
					                          vm_dpage_t, vm_phys_t, size_t);
					/* Invoke a custom load protocol of the associated datablock. */
					dt_loadpart = self->dp_block->db_type->dt_loadpart;
					if likely(dt_loadpart) {
						assert(!wasdestroyed(self));
						(*dt_loadpart)(self->dp_block,
						               vm_datapart_startdpage(self) + starting_data_page,
						               VM_PPAGE2ADDR(result) + ((uintptr_t)(starting_data_page & pagemask) << addrshift),
						               num_init_pages);
						assert(!wasdestroyed(self));
					}
				} EXCEPT {
					for (i = 0; i < num_init_pages; ++i) {
						VM_DATAPART_SETSTATE(self,
						                     starting_data_page + i,
						                     VM_DATAPART_PPP_UNINITIALIZED);
					}
					RETHROW();
				}
				if (*pchanged) {
					for (i = 0; i < num_init_pages; ++i) {
						VM_DATAPART_SETSTATE(self,
						                     starting_data_page + i,
						                     VM_DATAPART_PPP_HASCHANGED);
					}
					result_has_changed = true;
					if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) &
					      VM_DATAPART_FLAG_CHANGED)) {
						void (KCALL *dt_changed)(struct vm_datablock * __restrict,
						                         struct vm_datapart * __restrict);
						dt_changed = self->dp_block->db_type->dt_changed;
						if (dt_changed)
							(*dt_changed)(self->dp_block, self);
					}
				} else {
					for (i = 0; i < num_init_pages; ++i) {
						VM_DATAPART_SETSTATE(self,
						                     starting_data_page + i,
						                     VM_DATAPART_PPP_INITIALIZED);
					}
				}
				if (num_init_pages >= n_data_pages)
					goto done_init;
				n_data_pages -= num_init_pages;
				starting_data_page += num_init_pages;
				goto again_readstate_multi;
			}	break;

			case VM_DATAPART_PPP_INITIALIZING:
				/* Wait for the initialization to be completed. */
				task_tryyield_or_pause();
				assertf(VM_DATAPART_GETSTATE(self, starting_data_page) != VM_DATAPART_PPP_INITIALIZING ||
				        !task_isonlythread() ||
				        VM_DATAPART_GETSTATE(self, starting_data_page) != VM_DATAPART_PPP_INITIALIZING,
				        "Dangling `VM_DATAPART_PPP_INITIALIZING' part with only a single running thread\n"
				        "self               = %p\n"
				        "self->dp_flags     = %#Ix\n"
				        "starting_data_page = %I64u (%#I64x)\n"
				        "%I$[hex]\n",
				        self, (uintptr_t)self->dp_flags, starting_data_page, starting_data_page, self->dp_flags & VM_DATAPART_FLAG_HEAPPPP ? (size_t)(!self->dp_pprop_p ? 0 : CEILDIV(vm_datapart_numdpages(self), BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) * sizeof(uintptr_t)) : (size_t)sizeof(uintptr_t), self->dp_flags & VM_DATAPART_FLAG_HEAPPPP ? (void *)self->dp_pprop_p : (void *)&self->dp_pprop);
				goto again_readstate_multi;

			case VM_DATAPART_PPP_HASCHANGED:
				result_has_changed = true;
				break;

			case VM_DATAPART_PPP_INITIALIZED:
				if (*pchanged) {
					if (!VM_DATAPART_CMPXCHSTATE(self,
					                             starting_data_page,
					                             VM_DATAPART_PPP_INITIALIZED,
					                             VM_DATAPART_PPP_HASCHANGED))
						goto again_readstate_multi;
					result_has_changed = true;
					if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) &
					      VM_DATAPART_FLAG_CHANGED)) {
						void (KCALL *dt_changed)(struct vm_datablock * __restrict,
						                         struct vm_datapart * __restrict);
						dt_changed = self->dp_block->db_type->dt_changed;
						if (dt_changed)
							(*dt_changed)(self->dp_block, self);
					}
				}
				break;

			default: __builtin_unreachable();
			}
		}
done_init:
		*pchanged = result_has_changed;
	}
	return result;
}


/* Similar to `vm_datapart_loadpage()', however instead used for accessing only a single data
 * page, rather than a whole virtual memory page. (used to implement `vm_datapart_do_(read|write)[p]') */
PUBLIC NONNULL((1)) vm_phys_t KCALL
vm_datapart_loaddatapage(struct vm_datapart *__restrict self,
                         vm_dpage_t dpage_offset, bool for_writing)
		THROWS(...) {
	struct vm_datablock *block;
	vm_phys_t result;
	uintptr_t page_state;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	assertf(dpage_offset < (vm_dpage_t)vm_datapart_numdpages(self),
	        "dpage_offset                = %I64u\n"
	        "vm_datapart_numdpages(self) = %I64u\n",
	        (u64)dpage_offset,
	        (u64)vm_datapart_numvpages(self));
	/* Figure out the address of the associated physical memory page. */
	block  = self->dp_block;
	result = (vm_phys_t)vm_datapart_pageaddr(self,
	                                         (size_t)(dpage_offset >> VM_DATABLOCK_PAGESHIFT(block))) *
	         PAGESIZE;
	result += (uintptr_t)(dpage_offset & VM_DATABLOCK_PAGEMASK(block)) << VM_DATABLOCK_ADDRSHIFT(block);
again_readstate:
	page_state = VM_DATAPART_GETSTATE(self, dpage_offset);
	switch (page_state) {

	case VM_DATAPART_PPP_UNINITIALIZED:
		/* It seems to fall upon us to initialize this page! */
		if (!VM_DATAPART_CMPXCHSTATE(self,
		                             (vm_dpage_t)dpage_offset,
		                             VM_DATAPART_PPP_UNINITIALIZED,
		                             VM_DATAPART_PPP_INITIALIZING))
			goto again_readstate;
		TRY {
			void (KCALL *dt_loadpart)(struct vm_datablock * __restrict,
			                          vm_dpage_t, vm_phys_t, size_t);
			/* Invoke a custom load protocol of the associated datablock. */
			dt_loadpart = block->db_type->dt_loadpart;
			if (dt_loadpart) {
				(*dt_loadpart)(block,
				               vm_datapart_startdpage(self) + dpage_offset,
				               result,
				               1);
			}
		} EXCEPT {
			VM_DATAPART_SETSTATE(self,
			                     (vm_dpage_t)dpage_offset,
			                     VM_DATAPART_PPP_UNINITIALIZED);
			RETHROW();
		}
		/* Update the part's state to either indicate change, or full initialization */
		if (for_writing) {
			VM_DATAPART_SETSTATE(self,
			                     (vm_dpage_t)dpage_offset,
			                     VM_DATAPART_PPP_HASCHANGED);
			goto set_datapart_changed;
		}
		VM_DATAPART_SETSTATE(self,
		                     (vm_dpage_t)dpage_offset,
		                     VM_DATAPART_PPP_INITIALIZED);
		break;

	case VM_DATAPART_PPP_INITIALIZING:
		/* Wait for the initialization to be completed. */
		task_tryyield_or_pause();
		goto again_readstate;

	case VM_DATAPART_PPP_INITIALIZED:
		if (for_writing) {
			if (!VM_DATAPART_CMPXCHSTATE(self,
			                             (vm_dpage_t)dpage_offset,
			                             VM_DATAPART_PPP_INITIALIZED,
			                             VM_DATAPART_PPP_HASCHANGED))
				goto again_readstate;
set_datapart_changed:
			if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) &
			      VM_DATAPART_FLAG_CHANGED)) {
				void (KCALL *dt_changed)(struct vm_datablock * __restrict,
				                         struct vm_datapart * __restrict);
				dt_changed = block->db_type->dt_changed;
				if (dt_changed)
					(*dt_changed)(block, self);
			}
		}
		break;

	case VM_DATAPART_PPP_HASCHANGED:
		break;

	default: __builtin_unreachable();
	}
	return result;
}



#ifndef __INTELLISENSE__
DECL_END
#undef DMA_NX
#undef DMA_ENUM
#undef DMA_VECTOR

#define DMA_VECTOR 1
#define DMA_NX     1
#define DMA_ENUM   1
#include "vm-dma.c.inl"
#define DMA_VECTOR 1
#define DMA_NX     1
#include "vm-dma.c.inl"
#define DMA_VECTOR 1
#define DMA_ENUM   1
#include "vm-dma.c.inl"
#define DMA_VECTOR 1
#include "vm-dma.c.inl"
#define DMA_NX     1
#define DMA_ENUM   1
#include "vm-dma.c.inl"
#define DMA_NX     1
#include "vm-dma.c.inl"
#define DMA_ENUM   1
#include "vm-dma.c.inl"
#include "vm-dma.c.inl"

DECL_BEGIN
#endif

/* Stop DMAing by releasing all of the specified DMA locks.
 * NOTE: The caller must ensure that `lockcnt == return(vm_startdma*())', and
 *       that the specified `lockvec' is either the exact same `lockvec' originally
 *       passed to `vm_startdma*()', or an identical memory copy of it. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vm_stopdma)(struct vm_dmalock *__restrict lockvec, size_t lockcnt) {
	size_t i;
	for (i = lockcnt; i--;)
		sync_endread(lockvec[i].dl_part);
	for (i = lockcnt; i--;)
		decref_unlikely(lockvec[i].dl_part);
}





PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datablock_destroy)(struct vm_datablock *__restrict self) {
	DEFINE_PUBLIC_SYMBOL(_this_trampoline_page,
	                     &_this_trampoline_node.vn_node.a_vmin,
	                     sizeof(vm_vpage_t));
	assertf(self->db_parts == NULL ||
	        self->db_parts == VM_DATABLOCK_ANONPARTS,
	        "Any remaining part should have kept us alive!\n"
	        "self->db_parts = %p\n",
	        self->db_parts);
	if (self->db_type->dt_destroy)
		(*self->db_type->dt_destroy)(self);
	else {
		kfree(self);
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datablock_lock_endwrite_parts)(struct vm_datapart *__restrict self) {
again:
	sync_endwrite(self);
	if (self->dp_tree.a_min) {
		if (self->dp_tree.a_max)
			vm_datablock_lock_endwrite_parts(self->dp_tree.a_max);
		self = self->dp_tree.a_min;
		goto again;
	}
	if (self->dp_tree.a_max) {
		self = self->dp_tree.a_max;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datablock_lock_decref_parts)(struct vm_datapart *__restrict self) {
	struct vm_datapart *minpart;
	struct vm_datapart *maxpart;
again:
	minpart = self->dp_tree.a_min;
	maxpart = self->dp_tree.a_max;
	decref_likely(self);
	if (minpart) {
		if (maxpart)
			vm_datablock_lock_endwrite_parts(maxpart);
		self = minpart;
		goto again;
	}
	if (maxpart) {
		self = maxpart;
		goto again;
	}
}


/* Try to acquire a write-lock to `self' and all parts reachable from
 * it. - If this acquisition fails for any of the parts, return a pointer
 * to that part. - Else return `NULL', which is indicative of a successful
 * acquisition of locks to all parts. */
PUBLIC NOBLOCK NONNULL((1)) struct vm_datapart *
NOTHROW(KCALL vm_datablock_lock_trywrite_parts)(struct vm_datapart *__restrict self) {
	struct vm_datapart *result;
	if (!sync_trywrite(self))
		return self;
	if (self->dp_tree.a_min) {
		result = vm_datablock_lock_trywrite_parts(self->dp_tree.a_max);
		if (result) {
			sync_endwrite(self);
			return result; /* Propagate faulting part. */
		}
	}
	if (self->dp_tree.a_max) {
		result = vm_datablock_lock_trywrite_parts(self->dp_tree.a_max);
		if (result) {
			if (self->dp_tree.a_min)
				vm_datablock_lock_endwrite_parts(self->dp_tree.a_min);
			sync_endwrite(self);
			return result; /* Propagate faulting part. */
		}
	}
	return NULL;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_anonymize_tree)(struct vm_datapart *__restrict self,
                                          struct vm_datablock *__restrict block) {
again:
	assert(self->dp_block == block);
	assert(!(self->dp_flags & VM_DATAPART_FLAG_KERNPRT));
	decref_nokill(block); /* self->dp_block */
	assert(block->db_pageshift <= PAGESHIFT);
	self->dp_block = incref(&vm_datablock_anonymous_zero_vec[block->db_pageshift]);
#ifdef CONFIG_VIO
	/* Unset VIO parts! */
	assert((self->dp_state == VM_DATAPART_STATE_VIOPRT) ==
	       (block->db_vio != NULL));
	if (self->dp_state == VM_DATAPART_STATE_VIOPRT)
		self->dp_state = VM_DATAPART_STATE_ABSENT;
#endif /* CONFIG_VIO */
	self->dp_flags &= ~(VM_DATAPART_FLAG_CHANGED | VM_DATAPART_FLAG_TRKCHNG);
	if (self->dp_tree.a_min) {
		if (self->dp_tree.a_max)
			vm_datapart_anonymize_tree(self->dp_tree.a_max, block);
		self = self->dp_tree.a_min;
		goto again;
	}
	if (self->dp_tree.a_max) {
		self = self->dp_tree.a_max;
		goto again;
	}
}


/* Anonymize the given data block `self' (tearing down its part tree,
 * and changing all of the nodes to be bound to `vm_datablock_anonymous')
 * This in turn will resolve all of the reference loops between every
 * part reachable from `db_parts', which then point back via their `dp_block'
 * pointer, essentially getting rid of all of the data block's self-references.
 * NOTE: The caller should _NOT_ already be holding a lock to `self'!
 *       Doing so may cause this function to dead-lock, as it would be unable
 *       to perform a single-lock wait operation in case some other thread is
 *       already holding a lock to one of the parts, whilst trying to acquire
 *       a lock to the associated block, without would already be held by the
 *       caller.
 * @return: true:  The given datablock has now become anonymous.
 * @return: false: The given datablock had already been anonymized.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked. */
PUBLIC NONNULL((1)) bool KCALL
vm_datablock_anonymize(struct vm_datablock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct vm_datapart *chain;
again:
	sync_write(self);
	chain = self->db_parts;
	if (chain == VM_DATABLOCK_ANONPARTS) {
		/* Block has already been anonymized! */
		sync_endwrite(self);
		return false;
	}
	if (chain == NULL) {
		/* Simple case: There aren't any parts which would have to be anonymized. */
		goto done;
	}
	/* Here comes the part part: We need to acquire a write-lock
	 * to _each_ _and_ _every_ _one_ of our parts before we can
	 * proceed. - If doing this fails for any one of them, we must
	 * get rid of all locks already acquired, and manually acquire
	 * a blocking lock on that part, so-as to ensure that the lock
	 * is available, then release that lock and start over, hoping
	 * that we'll get better luck that run around. */
	chain = vm_datablock_lock_trywrite_parts(chain);
	if (chain) {
		/* Well. - This didn't go exactly as planned. - Time to
		 * wait for this part to become available, then try again. */
		incref(chain); /* Keep the part alive while not holding a lock to `self' */
		sync_endwrite(self);
		TRY {
			sync_write(chain);
		} EXCEPT {
			decref_unlikely(chain);
			RETHROW();
		}
		sync_endwrite(chain);
		decref_unlikely(chain);
		goto again;
	}
	chain = self->db_parts;
	/* All right! we're holding a lock to each and every one of
	 * the parts. - Now we can actually move on to anonymize them! */
	vm_datapart_anonymize_tree(chain, self);
	vm_datablock_lock_endwrite_parts(chain);
	/* Drop all of the references we've stolen before. */
	vm_datablock_lock_decref_parts(chain);
done:
	self->db_parts = VM_DATABLOCK_ANONPARTS;
	sync_endwrite(self);
	return true;
}


/* Check if the given datapart `self' has modified
 * data pages within the specified address range.
 * NOTE: The caller must be holding any kind of lock that prevents `self'
 *       from having its length changed (aka. a VM-tree read-lock of a VM
 *       that is mapping `self', a read-lock to `self', or a read-lock to
 *       the associated data-block, so-long as `self' hasn't been anonymized) */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL vm_datapart_haschanged)(struct vm_datapart *__restrict self,
                                      vm_dpage_t partrel_min_dpage,
                                      vm_dpage_t partrel_max_dpage) {
	vm_dpage_t i;
	assert((u64)partrel_min_dpage <= (u64)partrel_max_dpage);
	assert((u64)partrel_max_dpage < vm_datapart_numdpages(self));
	for (i = partrel_min_dpage; i <= partrel_max_dpage; ++i) {
		uintptr_t state;
		state = VM_DATAPART_GETSTATE(self, i);
		if (state == VM_DATAPART_PPP_HASCHANGED)
			return true;
	}
	return false;
}



PUBLIC NOBLOCK NONNULL((1)) struct vm_datapart *
NOTHROW(KCALL vm_datablock_findchanged)(struct vm_datapart *__restrict tree,
                                        vm_dpage_t minpage, vm_dpage_t maxpage,
                                        vm_dpage_t *__restrict ppartrel_minpage,
                                        vm_dpage_t *__restrict ppartrel_maxpage,
                                        ATREE_SEMI_T(vm_dpage_t) addr_semi,
                                        ATREE_LEVEL_T addr_level) {
again:
	if ((ATOMIC_READ(tree->dp_flags) & VM_DATAPART_FLAG_CHANGED) &&
	    minpage <= vm_datapart_maxdpage(tree) &&
	    maxpage >= vm_datapart_mindpage(tree)) {
		vm_dpage_t partrel_minpage, partrel_maxpage;
		/* Check this one. */
		if (minpage <= vm_datapart_mindpage(tree) &&
		    maxpage >= vm_datapart_maxdpage(tree)) {
			/* There ought to have been some changes made to this part! */
			partrel_minpage = 0;
			partrel_maxpage = (vm_dpage_t)vm_datapart_numdpages(tree) - 1;
		} else {
			partrel_minpage = vm_datapart_mindpage(tree);
			partrel_maxpage = vm_datapart_maxdpage(tree);
			if (maxpage < partrel_maxpage)
				partrel_maxpage = maxpage - partrel_minpage;
			else {
				partrel_maxpage = (vm_dpage_t)vm_datapart_numdpages(tree) - 1;
			}
			if (minpage >= partrel_minpage)
				partrel_minpage = minpage - partrel_minpage;
			else {
				partrel_minpage = 0;
			}
			/* Partial overlap: Check if there are changes in the requested region. */
			if (!vm_datapart_haschanged(tree,
			                            partrel_minpage,
			                            partrel_maxpage))
				goto do_next_node;
		}
		/* At least one portion of this part has been changed, and must be synced! */
		*ppartrel_minpage = partrel_minpage;
		*ppartrel_maxpage = partrel_maxpage;
		return tree;
	}
do_next_node:
	if (minpage < addr_semi && tree->dp_tree.a_min) {
		/* Recursively continue searching left. */
		if (maxpage >= addr_semi && tree->dp_tree.a_max) {
			struct vm_datapart *result;
			ATREE_SEMI_T(vm_dpage_t)
			temp_semi                = addr_semi;
			ATREE_LEVEL_T temp_level = addr_level;
			ATREE_WALKMAX(vm_dpage_t, temp_semi, temp_level);
			result = vm_datablock_findchanged(tree->dp_tree.a_max,
			                                  minpage,
			                                  maxpage,
			                                  ppartrel_minpage,
			                                  ppartrel_maxpage,
			                                  temp_semi,
			                                  temp_level);
			if (result)
				return result;
		}
		ATREE_WALKMIN(vm_dpage_t, addr_semi, addr_level);
		tree = tree->dp_tree.a_min;
		goto again;
	} else if (maxpage >= addr_semi && tree->dp_tree.a_max) {
		/* Recursively continue searching right. */
		ATREE_WALKMAX(vm_dpage_t, addr_semi, addr_level);
		tree = tree->dp_tree.a_max;
		goto again;
	}
	return NULL;
}


LOCAL NONNULL((1)) void KCALL
vm_datapart_do_savepart(struct vm_datapart *__restrict self, struct vm_datablock *__restrict block,
                        NONNULL((1)) void(KCALL *dt_savepart)(struct vm_datablock *__restrict,
                                                              vm_dpage_t, vm_phys_t, size_t),
                        vm_dpage_t partrel_min_dpage, u64 partrel_num_dpage)
		THROWS(...) {
	unsigned int addrshift;
	assert(dt_savepart == block->db_type->dt_savepart);
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	addrshift = VM_DATABLOCK_ADDRSHIFT(block);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		(*dt_savepart)(block,
		               vm_datapart_mindpage(self) + partrel_min_dpage,
		               VM_PPAGE2ADDR(self->dp_ramdata.rd_block0.rb_start) +
		               ((u64)partrel_min_dpage << addrshift),
		               (size_t)partrel_num_dpage);            /* XXX: Overflow? */
	} else {
		size_t i;
		vm_dpage_t dpage_pos       = partrel_min_dpage;
		struct vm_ramblock *blocks = self->dp_ramdata.rd_blockv;
		for (i = 0;; ++i) {
			u64 block_dpages;
			assert(i < self->dp_ramdata.rd_blockc);
			block_dpages = (u64)blocks[i].rb_size << VM_DATABLOCK_PAGESHIFT(block);
			if (partrel_min_dpage <= (vm_dpage_t)block_dpages)
				break;
			partrel_min_dpage -= (vm_dpage_t)block_dpages;
		}
		while (partrel_num_dpage) {
			u64 block_dpages;
			assert(i < self->dp_ramdata.rd_blockc);
			block_dpages = (u64)blocks[i].rb_size << VM_DATABLOCK_PAGESHIFT(block);
			block_dpages -= (u64)partrel_min_dpage;
			if (block_dpages > partrel_num_dpage)
				block_dpages = partrel_num_dpage;
			(*dt_savepart)(block,
			               vm_datapart_mindpage(self) + dpage_pos,
			               VM_PPAGE2ADDR(blocks[i].rb_start) +
			               ((u64)partrel_min_dpage << addrshift),
			               (size_t)block_dpages);                 /* XXX: Overflow? */
			partrel_min_dpage = 0;
			dpage_pos += block_dpages;
			partrel_num_dpage -= block_dpages;
		}
	}
}


/* Synchronize all modified pages within the given part-relative address range.
 * If the given part-relative address range is out-size of the bounds of `self'
 * after a lock to `self' has been acquired, then that range is truncated first.
 * NOTE: The caller should not be holding any kind of lock to either `self' or its data block.
 * NOTE: If the data block associated with `self' does not implement a `dt_savepart'
 *       function, or if `self' doesn't have the CHANGED flag set, the function immediately
 *       returns `0'.
 * NOTE: Once done, this function will transition the state of all saved data pages
 *       from `VM_DATAPART_PPP_HASCHANGED' back to `VM_DATAPART_PPP_INITIALIZED'
 *       Also note that during this process, any memory mapping of `self' which may
 *       have previously become writable due to the associated part having been
 *       changed to be HASCHANGED will be re-mapped as read-only, so-as to allow
 *       it to transition back to `VM_DATAPART_PPP_HASCHANGED' the next time a
 *       write is performed to such a region of memory.
 * NOTE: If the saved address range spans the entirety of `self', then this function
 *       will also unset the CHANGED bit of `self'
 * @param: recheck_modifications_before_remap: When true and `self' has some SHARED memory
 *                                             mappings, re-check that there are actually
 *                                             changed pages within the given address range
 *                                             before doing all of the work associated with
 *                                             re-mapping all shared mappings as read-only.
 * @return: * : The number of saved data pages. */
PUBLIC NONNULL((1)) vm_dpage_t KCALL
vm_datapart_sync(struct vm_datapart *__restrict self,
                 vm_dpage_t partrel_min_dpage,
                 vm_dpage_t partrel_max_dpage,
                 bool recheck_modifications_before_remap)
		THROWS(E_WOULDBLOCK, ...) {
	struct vm_datablock *block;
	vm_dpage_t result = 0;
	struct pointer_set vms;
#ifdef CONFIG_VIO
	if unlikely(ATOMIC_READ(self->dp_state) == VM_DATAPART_STATE_VIOPRT)
		goto done_return_now;
#endif /* CONFIG_VIO */
	pointer_set_init(&vms);
again_lock_datapart:
	TRY {
		void (KCALL *dt_savepart)(struct vm_datablock * __restrict,
		                          vm_dpage_t, vm_phys_t, size_t);
		size_t vms_count;
		struct vm_node *node;
		vm_datapart_lockread_setcore(self);
		assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
		       self->dp_state == VM_DATAPART_STATE_LOCKED);
		if (!(self->dp_flags & VM_DATAPART_FLAG_CHANGED))
			goto done_unlock;
		block       = self->dp_block;
		dt_savepart = block->db_type->dt_savepart;
		if unlikely(!dt_savepart)
			goto done_unlock;
		/* Truncate the specified address range. */
		if (partrel_max_dpage >= (vm_dpage_t)vm_datapart_numdpages(self))
			partrel_max_dpage = (vm_dpage_t)vm_datapart_numdpages(self) - 1;
		/* Check if the range to sync is still non-empty. */
		if unlikely(partrel_max_dpage < partrel_min_dpage)
			goto done_unlock;
		if (recheck_modifications_before_remap &&
		    self->dp_srefs != NULL) {
			if (partrel_min_dpage == 0 &&
			    partrel_max_dpage >= (vm_dpage_t)vm_datapart_numdpages(self))
				; /* The request spans the entirety of `self', meaning that due to the presence
				   * of the CHANGED flag (which is checked above), we must assume that at least
				   * some pages do have actually been modified (though it still is possible that
				   * those pages have since already been synced individually, leaving the CHANGED
				   * flag dangling without any actual modified pages) */
			else {
				/* Check if pages within the given range have been modified. */
				if (!vm_datapart_haschanged(self,
				                            partrel_min_dpage,
				                            partrel_max_dpage))
					goto done_unlock;
			}
		}
		/* Step #1: Go through all SHARED mappings of `self', and re-map
		 *          all of them to become read-only, so-as to prevent
		 *          further modifications to the backing data before we
		 *          actually start syncing that data (we don't want any
		 *          modifications to get lost during the time of us writing
		 *          existing changes, and us re-mapping as read-only, which
		 *          is why we must re-map as read-only first) */
		vms_count = vm_set_collect_from_datapart_srefs_writable(&vms, self);
		if unlikely(vms_count > vms.ps_size) {
			sync_endread(self);
			pointer_set_reset_rehash(&vms, vms_count, GFP_LOCKED);
			goto again_lock_datapart;
		}

		/* Now try to acquire write-locks to all of the affected VMs */
		{
			REF struct vm *blocking_vm;
			blocking_vm = vm_set_locktrywrite_all(&vms);
			if unlikely(blocking_vm) {
				incref(blocking_vm);
				sync_endread(self);
				vm_set_clear(&vms);
				TRY {
					sync_write(blocking_vm);
				} EXCEPT {
					decref(blocking_vm);
					RETHROW();
				}
				sync_endwrite(blocking_vm);
				decref(blocking_vm);
				goto again_lock_datapart;
			}
		}
		/* Re-map all writable nodes to become read-only. */
		assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
		       self->dp_state == VM_DATAPART_STATE_LOCKED);
		/* Check for stale nodes, so-as to ensure that we're not accidentally updating an unmapped node. */
		if unlikely(VM_DATAPART_MUST_SERVICE_STALE(self)) {
			vm_set_lockendwrite_all(&vms);
			sync_endwrite(self);
			vm_set_clear(&vms);
			goto again_lock_datapart;
		}
		{
			REF struct vm *myvm = THIS_VM;
			for (node = self->dp_srefs; node; node = node->vn_link.ln_next) {
				struct vm *v;
				u16 perm;
				assert(node->vn_prot & VM_PROT_SHARED ||
				       wasdestroyed(node->vn_vm));
				if (!(node->vn_prot & VM_PROT_WRITE))
					continue;
				assert(node->vn_part == self);
				v = node->vn_vm;
				if unlikely(wasdestroyed(v))
					continue;
				/* Make sure that the associated page mapping has been prepared. */
				if unlikely(!(v == myvm || PRANGE_IS_KERNEL(VM_NODE_START(node), VM_NODE_END(node))
				              ? pagedir_prepare_map(VM_NODE_START(node), VM_NODE_SIZE(node))
				              : pagedir_prepare_map_p(PAGEDIR_P_SELFOFVM(v),
				                                      VM_NODE_START(node),
				                                      VM_NODE_SIZE(node)))) {
					vm_set_lockendwrite_all(&vms);
					sync_endread(self);
					/*vm_set_clear(&vms); // Done by the EXCEPT below */
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
				}
				/* Don't propagate write permissions (those are lazily re-added during the next write-
				 * attempt, which will once again mark our part as changed once we're all set & done) */
				perm = node->vn_prot & (VM_PROT_EXEC | VM_PROT_READ);
				if (v != &vm_kernel)
					perm |= PAGEDIR_MAP_FUSER;
				if (v == myvm || PRANGE_IS_KERNEL(VM_NODE_START(node), VM_NODE_END(node))) {
					vm_datapart_map_ram_autoprop(self, VM_NODE_START(node), perm);
				} else {
					vm_datapart_map_ram_autoprop_p(self, PAGEDIR_P_SELFOFVM(v), VM_NODE_START(node), perm);
				}
				/* Synchronize the page directory for address range mapped by the node. */
				/* FIXME: `vm_sync()' can throw E_WOULDBLOCK!
				 *        Instead, we must acquire task chain locks alongside node tree locks above! */
				vm_sync(v, VM_NODE_START(node), VM_NODE_SIZE(node));
			}
		}
		/* Unlock all of the affected VMs */
		vm_set_lockendwrite_all(&vms);

		/* At this point, we can finally go through the range given to us by
		 * the caller, searching for any page that has been marked as CHANGED. */
		TRY {
			vm_dpage_t i;
			u64 count;
			for (i = partrel_min_dpage; i <= partrel_max_dpage;) {
				if (VM_DATAPART_GETSTATE(self, i) != VM_DATAPART_PPP_HASCHANGED) {
					++i;
					continue;
				}
				/* Search for continuous strips of modified pages. */
				count = 1;
				while (i + count <= partrel_max_dpage &&
				       VM_DATAPART_GETSTATE(self, i) == VM_DATAPART_PPP_HASCHANGED)
					++count;
				/* Actually save the data backing of the given range. */
				vm_datapart_do_savepart(self,
				                        block,
				                        dt_savepart,
				                        i,
				                        count);
				/* Go through and change all of the associated pages from CHANGED to INITIALIZED.
				 * NOTE: Some of them may have already changed in this manner, in case some other
				 *       thread is/has also synced our part. */
				for (; count--; ++i) {
					if (VM_DATAPART_CMPXCHSTATE(self, i,
					                            VM_DATAPART_PPP_HASCHANGED,
					                            VM_DATAPART_PPP_INITIALIZED))
						++result; /* Track the number of parts which we've actually synced */
				}
			}
		} EXCEPT {
			sync_endread(self);
			RETHROW();
		}
		assert(vm_datapart_numdpages(self) != 0);
		if (partrel_min_dpage == 0 &&
		    partrel_max_dpage >= (vm_dpage_t)vm_datapart_numdpages(self) - 1) {
			/* Upgrade to a write-lock so we can re-check if all pages are
			 * still marked as INITIALIZED, rather than CHANGED. */
			if likely(sync_upgrade(self) ||
			          !(ATOMIC_READ(self->dp_flags) & VM_DATAPART_FLAG_CHANGED)) {
				vm_dpage_t i;
				partrel_max_dpage = (vm_dpage_t)vm_datapart_numdpages(self);
				for (i = 0; i < partrel_max_dpage; ++i) {
					if unlikely(VM_DATAPART_GETSTATE(self, i) == VM_DATAPART_PPP_HASCHANGED)
						goto done_unlock_write; /* Further changes happened in the mean time. */
				}
				/* Unset the CHANGED bit, now that we're certain there aren't any further changes. */
				ATOMIC_FETCHAND(self->dp_flags, ~VM_DATAPART_FLAG_CHANGED);
			}
done_unlock_write:
			sync_endwrite(self);
		} else {
done_unlock:
			sync_endread(self);
		}
	} EXCEPT {
		vm_set_fini(&vms);
		RETHROW();
	}
	vm_set_fini(&vms);
#ifdef CONFIG_VIO
done_return_now:
#endif /* CONFIG_VIO */
	return result;
}




/* Synchronize all modified data pages within the specified address range.
 * When called, this function will go through all data parts of `self', and
 * save any changed data pages using `self->db_type->dt_savepart'
 * @return: * : The number of saved data pages. */
PUBLIC NONNULL((1)) vm_dpage_t KCALL
vm_datablock_sync(struct vm_datablock *__restrict self,
                  vm_dpage_t minpage, vm_dpage_t maxpage)
		THROWS(E_WOULDBLOCK, ...) {
	vm_dpage_t result = 0;
	if unlikely(!self->db_type->dt_savepart)
		goto done; /* No save function -> No syncing */
	if unlikely(maxpage < minpage)
		goto done; /* Nothing to sync here! */
again:
	sync_read(self);
	if unlikely(self->db_parts == NULL ||
	            self->db_parts == VM_DATABLOCK_ANONPARTS) {
		/* No parts reachable! */
		sync_endread(self);
	} else {
		vm_dpage_t temp;
		vm_dpage_t partrel_minpage;
		vm_dpage_t partrel_maxpage;
		struct vm_datapart *part;
		/* Search for modified parts within the given range. */
		part = vm_datablock_findchanged(self->db_parts,
		                                minpage,
		                                maxpage,
		                                &partrel_minpage,
		                                &partrel_maxpage,
		                                ATREE_SEMI0(vm_dpage_t),
		                                ATREE_LEVEL0(vm_dpage_t));
		if (!part) {
			sync_endread(self);
			goto done;
		}
		incref(part);
		sync_endread(self);
		/* Sync this part! */
		TRY {
			temp = vm_datapart_sync(part,
			                        partrel_minpage,
			                        partrel_maxpage,
			                        false);
		} EXCEPT {
			decref(part);
			RETHROW();
		}
		result += temp;
		decref(part);
		/* Search for more parts which may have changed. */
		goto again;
	}
done:
	return result;
}


/* Check if there are changed parts within the specified address range.
 * NOTE: The caller must be holding a read-lock on `self' */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL vm_datablock_haschanges)(struct vm_datablock *__restrict self,
                                       vm_dpage_t minpage, vm_dpage_t maxpage) {
	struct vm_datapart *part;
	vm_dpage_t partrel_minpage;
	vm_dpage_t partrel_maxpage;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	/* Search for modified parts within the given range. */
	part = vm_datablock_findchanged(self->db_parts,
	                                minpage,
	                                maxpage,
	                                &partrel_minpage,
	                                &partrel_maxpage,
	                                ATREE_SEMI0(vm_dpage_t),
	                                ATREE_LEVEL0(vm_dpage_t));
	return part != NULL;
}




PRIVATE ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_do_createpart(struct vm_datablock *__restrict self,
                           vm_vpage64_t pageno, size_t num_vpages)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct vm_datapart *result;
	vm_dpage_t data_pageno;
	size_t num_dpages;
	data_pageno = (vm_dpage_t)pageno << VM_DATABLOCK_PAGESHIFT(self);
	num_dpages  = num_vpages << VM_DATABLOCK_PAGESHIFT(self);
	/* This one's considerably simpler, because we don't have to juggle around
	 * holding a lock to `self', since there are no other parts which our's may
	 * potentially collide with! */
	result = (REF struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
	                                           GFP_CALLOC | GFP_LOCKED |
	                                           GFP_PREFLT | GFP_VCBASE);
	if (num_dpages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
		assert(result->dp_pprop == 0);
#if VM_DATAPART_FLAG_NORMAL != 0
		result->dp_flags = VM_DATAPART_FLAG_NORMAL;
#else /* VM_DATAPART_FLAG_NORMAL != 0 */
		assert(result->dp_flags == VM_DATAPART_FLAG_NORMAL);
#endif /* VM_DATAPART_FLAG_NORMAL == 0 */
	} else {
		/* Need to allocate a page property bitset as part of the heap! */
		uintptr_t *ppp;
		size_t ppp_size;
		ppp_size = CEILDIV(num_dpages, BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) * sizeof(uintptr_t);
		TRY {
			ppp = (uintptr_t *)kmalloc(ppp_size,
			                           GFP_CALLOC | GFP_LOCKED |
			                           GFP_PREFLT | GFP_VCBASE);
		} EXCEPT {
			kffree(result, GFP_CALLOC);
			RETHROW();
		}
		result->dp_flags = (VM_DATAPART_FLAG_NORMAL |
		                    VM_DATAPART_FLAG_HEAPPPP);
		result->dp_pprop_p = ppp;
	}
	result->dp_refcnt = 1;
	shared_rwlock_cinit(&result->dp_lock);
	result->dp_tree.a_vmin = data_pageno;
	result->dp_tree.a_vmax = data_pageno + num_dpages - 1;
	assert(result->dp_crefs == NULL);
	assert(result->dp_srefs == NULL);
	assert(result->dp_stale == NULL);
	assert(result->dp_futex == NULL);
#if VM_DATAPART_STATE_ABSENT != 0
	result->dp_state = VM_DATAPART_STATE_ABSENT;
#else /* VM_DATAPART_STATE_ABSENT != 0 */
	assert(result->dp_state == VM_DATAPART_STATE_ABSENT);
#endif /* VM_DATAPART_STATE_ABSENT == 0 */
#ifdef CONFIG_VIO
	if (self->db_vio)
		result->dp_state = VM_DATAPART_STATE_VIOPRT;
#endif /* CONFIG_VIO */
	result->dp_block = incref(self);
	if (self->db_type->dt_initpart)
		(*self->db_type->dt_initpart)(result);
	return result;
}


PRIVATE ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_do_locatepart(struct vm_datablock *__restrict self,
                           vm_vpage64_t pageno, size_t num_vpages_hint)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	vm_parttree_minmax_t minmax;
	REF struct vm_datapart *result;
	size_t num_dpages;
	uintptr_t *ppp;
	vm_dpage_t data_pageno;
	assert(self->db_parts != VM_DATABLOCK_ANONPARTS);
	data_pageno = (vm_dpage_t)pageno << VM_DATABLOCK_PAGESHIFT(self);
	num_dpages  = (size_t)num_vpages_hint << VM_DATABLOCK_PAGESHIFT(self);
	sync_read(self);
	/* Step #1: Check if there is a part containing the given page number! */
	COMPILER_READ_BARRIER();
	if unlikely(self->db_parts == VM_DATABLOCK_ANONPARTS)
		goto create_anon_endread;
	minmax.mm_min = minmax.mm_max = NULL;
	vm_parttree_minmaxlocate(self->db_parts,
	                         data_pageno,
	                         data_pageno + num_dpages - 1,
	                         &minmax);
	if (minmax.mm_min) {
		if (vm_datapart_mindpage(minmax.mm_min) <= data_pageno) {
			assert(vm_datapart_maxdpage(minmax.mm_min) >= data_pageno);
			incref(minmax.mm_min);
			sync_endread(self);
			return minmax.mm_min;
		}
		/* Step #2: Since there is no part there, check if there is some other part
		 *          above that may be limiting how large we can make our new part. */
		assert(minmax.mm_max);
		assert(vm_datapart_mindpage(minmax.mm_max) >= data_pageno);
		assert(vm_datapart_mindpage(minmax.mm_max) <= data_pageno + num_dpages - 1);
		/* Limit the size of the new part, so-as not to overlap
		 * with another part that might follow after */
		num_dpages = (size_t)(vm_datapart_mindpage(minmax.mm_max) - data_pageno);
	} else {
		assert(!minmax.mm_max);
	}
	if unlikely(!sync_upgrade(self)) {
		/* Need to check again! */
		COMPILER_READ_BARRIER();
		if unlikely(self->db_parts == VM_DATABLOCK_ANONPARTS)
			goto create_anon_endwrite;
		minmax.mm_min = minmax.mm_max = NULL;
		vm_parttree_minmaxlocate(self->db_parts,
		                         data_pageno,
		                         data_pageno + num_dpages - 1,
		                         &minmax);
		if (minmax.mm_min) {
			if (vm_datapart_mindpage(minmax.mm_min) <= data_pageno) {
				assert(vm_datapart_maxdpage(minmax.mm_min) >= data_pageno);
				incref(minmax.mm_min);
				sync_endwrite(self);
				return minmax.mm_min;
			}
			/* Step #2: Since there is no part there, check if there is some other part
			 *          above that may be limiting how large we can make our new part. */
			assert(minmax.mm_max);
			assert(vm_datapart_mindpage(minmax.mm_max) >= data_pageno);
			assert(vm_datapart_mindpage(minmax.mm_max) <= data_pageno + num_dpages - 1);
			/* Limit the size of the new part, so-as not to overlap
			 * with another part that might follow after */
			num_dpages = (size_t)(vm_datapart_mindpage(minmax.mm_max) - data_pageno);
		} else {
			assert(!minmax.mm_max);
		}
	}

	/* No part matching the given range exists. - We must create that part for ourself! */
	result = (REF struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
	                                              GFP_CALLOC | GFP_LOCKED |
	                                              GFP_ATOMIC | GFP_PREFLT | GFP_VCBASE);
	if (!result) {
		/* Need to allocate the new part whilst blocking (so we need to unlock `self' first...) */
		sync_endwrite(self);
		result = (REF struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
		                                           GFP_CALLOC | GFP_LOCKED |
		                                           GFP_PREFLT | GFP_VCBASE);
		TRY {
			sync_write(self);
		} EXCEPT {
			kffree(result, GFP_CALLOC);
			RETHROW();
		}
		/* Must search the given range once again! */
		COMPILER_READ_BARRIER();
		if unlikely(self->db_parts == VM_DATABLOCK_ANONPARTS)
			goto create_anon_endwrite_freer;
		minmax.mm_min = minmax.mm_max = NULL;
		vm_parttree_minmaxlocate(self->db_parts,
		                         data_pageno,
		                         data_pageno + num_dpages - 1,
		                         &minmax);
		if (minmax.mm_min) {
			if (vm_datapart_mindpage(minmax.mm_min) <= data_pageno) {
				assert(vm_datapart_maxdpage(minmax.mm_min) >= data_pageno);
				incref(minmax.mm_min);
				sync_endwrite(self);
				kffree(result, GFP_CALLOC);
				return minmax.mm_min;
			}
			/* Step #2: Since there is no part there, check if there is some other part
			 *          above that may be limiting how large we can make our new part. */
			assert(minmax.mm_max);
			assert(vm_datapart_mindpage(minmax.mm_max) >= data_pageno);
			assert(vm_datapart_mindpage(minmax.mm_max) <= data_pageno + num_dpages - 1);
			/* Limit the size of the new part, so-as not to overlap
			 * with another part that might follow after */
			num_dpages = (size_t)(vm_datapart_mindpage(minmax.mm_max) - data_pageno);
		} else {
			assert(!minmax.mm_max);
		}
	}
	/* At this point, we've got the new part. - Time to initialize it! */
	result->dp_refcnt = 2; /* +1 for return, +1 for `self->db_partss' */
	shared_rwlock_cinit(&result->dp_lock);
#if VM_DATAPART_FLAG_NORMAL != 0
	result->dp_flags = VM_DATAPART_FLAG_NORMAL;
#else /* VM_DATAPART_FLAG_NORMAL != 0 */
	assert(result->dp_flags == VM_DATAPART_FLAG_NORMAL);
#endif /* VM_DATAPART_FLAG_NORMAL == 0 */
	if (num_dpages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
set_inline_ppp:
		assert(result->dp_pprop == 0);
	} else {
		/* Need to allocate a page property bitset as part of the heap! */
		size_t ppp_size;
		ppp_size = CEILDIV(num_dpages,
		                   BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) *
		           sizeof(uintptr_t);
		ppp = (uintptr_t *)kmalloc_nx(ppp_size,
		                              GFP_ATOMIC | GFP_CALLOC |
		                              GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		if (!ppp) {
			/* Need to block while allocating... */
			sync_endwrite(self);
			TRY {
				ppp = (uintptr_t *)kmalloc(ppp_size,
				                           GFP_CALLOC | GFP_LOCKED |
				                           GFP_PREFLT | GFP_VCBASE);
				TRY {
					sync_write(self);
				} EXCEPT {
					kffree(ppp, GFP_CALLOC);
					RETHROW();
				}
			} EXCEPT {
				kfree(result);
				RETHROW();
			}
			/* Must search the given range once again! */
			COMPILER_READ_BARRIER();
			if unlikely(self->db_parts == VM_DATABLOCK_ANONPARTS)
				goto create_anon_endwrite_freer_ppp;
			minmax.mm_min = minmax.mm_max = NULL;
			vm_parttree_minmaxlocate(self->db_parts,
			                         data_pageno,
			                         data_pageno + num_dpages - 1,
			                         &minmax);
			if (minmax.mm_min) {
				if (vm_datapart_mindpage(minmax.mm_min) <= data_pageno) {
					assert(vm_datapart_maxdpage(minmax.mm_min) >= data_pageno);
					incref(minmax.mm_min);
					sync_endwrite(self);
					kffree(ppp, GFP_CALLOC);
					kfree(result);
					return minmax.mm_min;
				}
				/* Step #2: Since there is no part there, check if there is some other part
				 *          above that may be limiting how large we can make our new part. */
				assert(minmax.mm_max);
				assert(vm_datapart_mindpage(minmax.mm_max) >= data_pageno);
				assert(vm_datapart_mindpage(minmax.mm_max) <= data_pageno + num_dpages - 1);
				/* Limit the size of the new part, so-as not to overlap
				 * with another part that might follow after */
				num_dpages = (size_t)(vm_datapart_mindpage(minmax.mm_max) - data_pageno);
				if (num_dpages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
					kffree(ppp, GFP_CALLOC);
					goto set_inline_ppp;
				}
				ppp_size = CEILDIV(num_dpages, BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) * sizeof(uintptr_t);
				{
					uintptr_t *new_ppp;
					/* Try to release unused memory. */
					new_ppp = (uintptr_t *)krealloc_nx(ppp, ppp_size,
					                                   GFP_ATOMIC | GFP_CALLOC | GFP_PREFLT |
					                                   GFP_LOCKED | GFP_VCBASE);
					if likely(new_ppp)
						ppp = new_ppp;
				}
			} else {
				assert(!minmax.mm_max);
			}
		}
		result->dp_flags = (VM_DATAPART_FLAG_NORMAL |
		                    VM_DATAPART_FLAG_HEAPPPP);
		result->dp_pprop_p = ppp;
	}
	result->dp_tree.a_vmin = data_pageno;
	result->dp_tree.a_vmax = data_pageno + num_dpages - 1;
	assert(result->dp_crefs == NULL);
	assert(result->dp_srefs == NULL);
	assert(result->dp_stale == NULL);
	result->dp_block = incref(self);
#if VM_DATAPART_STATE_ABSENT != 0
	result->dp_state = VM_DATAPART_STATE_ABSENT;
#else /* VM_DATAPART_FLAG_NORMAL != 0 */
	assert(result->dp_state == VM_DATAPART_STATE_ABSENT);
#endif /* VM_DATAPART_FLAG_NORMAL == 0 */
#ifdef CONFIG_VIO
	if (self->db_vio)
		result->dp_state = VM_DATAPART_STATE_VIOPRT;
#endif /* CONFIG_VIO */
	if (self->db_type->dt_initpart)
		(*self->db_type->dt_initpart)(result);
	/* Finally, insert the new part into the data tree. */
	vm_parttree_insert(&self->db_parts, result); /* Inherit reference */
	sync_endwrite(self);
	return result; /* Inherit reference */
create_anon_endwrite_freer_ppp:
	kfree(ppp);
create_anon_endwrite_freer:
	kfree(result);
create_anon_endwrite:
	sync_downgrade(self);
create_anon_endread:
	sync_endread(self);
	return vm_datablock_do_createpart(self, pageno, num_vpages_hint);
}



/* Lookup and return a reference the data part containing the given `pageno'
 * NOTE: When `self' is an anonymous data block (`self->db_parts == VM_DATABLOCK_ANONPARTS'),
 *       the the returned data part will be allocated anonymously as well, meaning that
 *       it will not be shared (`!isshared(return)'), and not be re-returned when the
 *       call is repeated with the same arguments passed once again. */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_locatepart(struct vm_datablock *__restrict self,
                        vm_vpage64_t pageno, size_t num_vpages_hint)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct vm_datapart *result;
	if (ATOMIC_READ(self->db_parts) == VM_DATABLOCK_ANONPARTS) {
		result = vm_datablock_do_createpart(self,
		                                    pageno,
		                                    num_vpages_hint);
	} else {
		result = vm_datablock_do_locatepart(self,
		                                    pageno,
		                                    num_vpages_hint);
	}
	assertf((vm_datapart_startdpage(result) & VM_DATABLOCK_PAGEMASK(self)) == 0,
	        "Invalid data part (start at %#I64x, end at %#I64x)\n",
	        (u64)vm_datapart_startdpage(result),
	        (u64)vm_datapart_enddpage(result));
	return result;
}

/* Same as `vm_datablock_locatepart()', but ensure that the returned datapart
 * starts at exactly at `pageno', and that it doesn't have span more than
 * `max_num_vpages' pages of virtual memory (though it may still span less than that) */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_locatepart_exact(struct vm_datablock *__restrict self,
                                      vm_vpage64_t pageno, size_t max_num_vpages)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct vm_datapart *result;
	REF struct vm_datapart *new_result;
	vm_vpage64_t start_page;
	/* Check for special case: anonymous data block tree. */
	if (ATOMIC_READ(self->db_parts) == VM_DATABLOCK_ANONPARTS) {
		result = vm_datablock_do_createpart(self,
		                                    pageno,
		                                    max_num_vpages);
		goto done;
	}
again:
	result = vm_datablock_do_locatepart(self,
	                                    pageno,
	                                    max_num_vpages);
	start_page = vm_datapart_minvpage(result);
	assert(pageno >= start_page);
	if (pageno > start_page) {
		TRY {
			/* Split the part, so we get the portion that starts where we want it to! */
			new_result = vm_datapart_split(result,
			                               (size_t)(pageno - start_page));
		} EXCEPT {
			vm_datapart_decref_and_merge(result);
			RETHROW();
		}
		decref_unlikely(result);
		if (!new_result) {
			/* The data-part got truncated in the mean time...
			 * -> Try again! */
			goto again;
		}
		/* Got it now! */
		result = new_result;
	}
	assert(vm_datapart_minvpage(result) == pageno);

	/* Make sure that the returned data part isn't larger than `max_num_vpages'
	 * This is once again achieved by splitting the part if it is larger, but
	 * discarding the high part and keeping the low one, instead of using the
	 * high part as we did above when ensuring that the part starts where we
	 * need it to. */
	{
		size_t num_vpages;
again_check_result_num_vpages:
		num_vpages = vm_datapart_numvpages(result);
		if (num_vpages > max_num_vpages) {
			TRY {
				/* Split the part, so we get the portion that starts where we want it to! */
				new_result = vm_datapart_split(result, max_num_vpages);
			} EXCEPT {
				vm_datapart_decref_and_merge(result);
				RETHROW();
			}
			if (!new_result)
				goto again_check_result_num_vpages;
			decref_unlikely(new_result);
		}
	}
done:
	assertf((vm_datapart_startdpage(result) & VM_DATABLOCK_PAGEMASK(self)) == 0,
	        "Invalid data part (start at %#I64x, end at %#I64x)\n",
	        (u64)vm_datapart_startdpage(result),
	        (u64)vm_datapart_enddpage(result));
	return result;
}



#ifndef __INTELLISENSE__
DECL_END

#undef IO_READ
#undef IO_WRITE
#undef IO_PHYS
#undef IO_VECTOR
#undef IO_UNSAFE
#undef IO_BUFFERED

#define IO_READ 1
#define IO_UNSAFE 1
#include "vm-datablock-read-write-base.c.inl"
#define IO_WRITE 1
#define IO_UNSAFE 1
#include "vm-datablock-read-write-base.c.inl"

#define IO_READ 1
#define IO_BUFFERED 1
#include "vm-datablock-read-write-base.c.inl"
#define IO_WRITE 1
#define IO_BUFFERED 1
#include "vm-datablock-read-write-base.c.inl"

#define IO_READ 1
#define IO_PHYS 1
#define IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"
#define IO_WRITE 1
#define IO_PHYS 1
#define IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"

#define IO_READ 1
#define IO_PHYS 1
#include "vm-datablock-read-write-base.c.inl"
#define IO_WRITE 1
#define IO_PHYS 1
#include "vm-datablock-read-write-base.c.inl"

#define IO_READ 1
#define IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"
#define IO_WRITE 1
#define IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"

#define IO_READ 1
#include "vm-datablock-read-write-base.c.inl"
#define IO_WRITE 1
#include "vm-datablock-read-write-base.c.inl"

DECL_BEGIN
#endif



/* Free a given VM node (the method used depending on
 * `self->vn_flags & VM_NODE_FLAG_COREPRT') */
PUBLIC NOBLOCK void
NOTHROW(KCALL vm_node_free)(struct vm_node *__restrict self) {
	DEFINE_PUBLIC_SYMBOL(vm_datablock_anonymous_zero,
	                     &vm_datablock_anonymous_zero_vec[0],
	                     sizeof(vm_datablock_anonymous_zero));
	if (self->vn_flags & VM_NODE_FLAG_COREPRT) {
		vm_corepage_freepart(self);
	} else {
		kfree(self);
	}
}

/* Destroy a given node. - This will finalize the following fields:
 *  - vn_block
 *  - vn_part
 *  - vn_link */
PUBLIC NOBLOCK void
NOTHROW(KCALL vm_node_destroy)(struct vm_node *__restrict self) {
	if (self->vn_block) {
		struct vm_datapart *part = self->vn_part;
		assert(self->vn_vm != NULL);
		/* If the memory mapping of `self' is still prepared, unprepare it now. */
		if (self->vn_flags & VM_NODE_FLAG_PREPARED) {
#ifndef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (self->vn_vm != &vm_kernel) /* Preparations are meaningless within kernel-space. */
#endif /* !CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			{
				if (self->vn_vm == THIS_VM
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				    || PAGE_IS_KERNEL(VM_NODE_START(self))
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				    ) {
					pagedir_unprepare_map_p(PAGEDIR_P_SELFOFVM(self->vn_vm),
					                        VM_NODE_START(self),
					                        VM_NODE_SIZE(self));
				} else {
					pagedir_unprepare_map(VM_NODE_START(self),
					                      VM_NODE_SIZE(self));
				}
			}
		}
		if (part) {
			assertf(part->dp_block == self->vn_block ||
			        part->dp_block == &vm_datablock_anonymous ||
			        (part->dp_block >= vm_datablock_anonymous_zero_vec &&
			         part->dp_block < COMPILER_ENDOF(vm_datablock_anonymous_zero_vec)),
			        "part->dp_block = %p\n"
			        "self->vn_block = %p\n",
			        part->dp_block, self->vn_block);
			if (sync_trywrite(part)) {
				/* Unlink the given node. */
				LLIST_REMOVE(self, vn_link);
				sync_endwrite(part);
			} else {
				struct vm_node *next;
				REF struct vm_datablock *block;
				block = self->vn_block;
				COMPILER_READ_BARRIER();
				weakincref(self->vn_vm); /* This reference is stored in the `dp_stale' chain. */
				/* Schedule the node as being stack within the given datapart. */
				do {
					next = ATOMIC_READ(part->dp_stale);
					self->vn_byaddr.ln_next = next;
				} while (!ATOMIC_CMPXCH_WEAK(part->dp_stale, next, self));
				COMPILER_WRITE_BARRIER();
				/* Make sure that stale data has been serviced, in case the lock became
				 * available while we were scheduling ourself as being stale. */
				if unlikely(sync_trywrite(&part->dp_lock)) {
					vm_datapart_service_stale(part);
					sync_endwrite(&part->dp_lock);
				}
				vm_datapart_decref_and_merge(part); /* decref(vn_part) */
				decref_unlikely(block);
				return;
			}
			vm_datapart_decref_and_merge(part); /* decref(vn_part) */
		}
		decref_unlikely(self->vn_block);
	} else {
		assert(!self->vn_part);
	}
	vm_node_free(self);
}





struct partnode_pair {
	REF struct vm_datapart *pn_part; /* [1..1] The associated part (NOTE: This pointer also holds a write-lock to this part). */
	struct vm_node         *pn_node; /* [1..1][owned] The associated node. */
};

struct partnode_pair_vector {
	size_t                pv_cnt;    /* Amount of used pairs. */
	size_t                pv_alc;    /* Amount of allocated pairs. */
	struct partnode_pair *pv_vec;    /* [0..pv_cnt|ALLOC(pv_alc)][owned_if(!= pv_buf)]
	                                  * Vector of part-node pairs. */
	struct partnode_pair  pv_buf[2]; /* A small, statically allocated buffer of pairs. */
};

/* Try to acquire write-locks to all of th parts contained within `self'
 * If this fails for one of these parts, unlock all parts previously locked,
 * and return a pointer to the blocking part. */
PRIVATE NOBLOCK struct vm_datapart *
NOTHROW(KCALL partnode_pair_vector_trywrite_parts)(struct partnode_pair_vector *__restrict self) {
	size_t i;
	for (i = 0; i < self->pv_cnt; ++i) {
		struct vm_datapart *part;
		part = self->pv_vec[i].pn_part;
		if (!sync_trywrite(part)) {
			while (i--)
				sync_endwrite(self->pv_vec[i].pn_part);
			return part;
		}
	}
	return NULL;
}

/* Release write-locks to all of the parts contained within `self' */
PRIVATE NOBLOCK void
NOTHROW(KCALL partnode_pair_vector_endwrite_parts)(struct partnode_pair_vector *__restrict self) {
	size_t i = self->pv_cnt;
	while (i--)
		sync_endwrite(self->pv_vec[i].pn_part);
}

/* Same as `partnode_pair_vector_reserve1_nx()', but allow for exceptions, as well as blocking */
PRIVATE void KCALL
partnode_pair_vector_reserve1(struct partnode_pair_vector *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	assert(self->pv_cnt <= self->pv_alc);
	if (self->pv_cnt >= self->pv_alc) {
		/* Must allocate more pairs. */
		size_t new_alloc = self->pv_alc + 4;
		struct partnode_pair *new_vector;
		new_vector = self->pv_vec == self->pv_buf
		             ? (struct partnode_pair *)kmalloc_nx(new_alloc * sizeof(struct partnode_pair),
		                                                  GFP_LOCKED | GFP_PREFLT | GFP_VCBASE)
		             : (struct partnode_pair *)krealloc_nx(self->pv_vec,
		                                                   new_alloc * sizeof(struct partnode_pair),
		                                                   GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		if (!new_vector) {
			new_alloc  = self->pv_cnt + 1;
			new_vector = self->pv_vec == self->pv_buf
			             ? (struct partnode_pair *)kmalloc(new_alloc * sizeof(struct partnode_pair),
			                                               GFP_LOCKED | GFP_PREFLT | GFP_VCBASE)
			             : (struct partnode_pair *)krealloc(self->pv_vec,
			                                                new_alloc * sizeof(struct partnode_pair),
			                                                GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		}
		if (self->pv_vec == self->pv_buf)
			memcpy(new_vector, self->pv_buf, self->pv_cnt * sizeof(struct partnode_pair));
		self->pv_alc = new_alloc;
		self->pv_vec = new_vector;
	}
}

/* Add the given `part' to the part vector, as well as allocate an associated node. */
PRIVATE void KCALL
partnode_pair_vector_addpart(struct partnode_pair_vector *__restrict self,
                             /*inherit(on_success)*/ REF struct vm_datapart *__restrict part)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *new_node;
	partnode_pair_vector_reserve1(self);
	new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                     GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	self->pv_vec[self->pv_cnt].pn_node = new_node; /* Inherit */
	self->pv_vec[self->pv_cnt].pn_part = part;     /* Inherit reference */
	++self->pv_cnt;
}

PRIVATE void KCALL
partnode_pair_vector_insertpart(struct partnode_pair_vector *__restrict self, size_t index,
                                /*inherit(on_success)*/ REF struct vm_datapart *__restrict part)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *new_node;
	assert(index <= self->pv_cnt);
	partnode_pair_vector_reserve1(self);
	new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                     GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	memmove(&self->pv_vec[index + 1],
	        &self->pv_vec[index],
	        (self->pv_cnt - index) * sizeof(struct partnode_pair));
	self->pv_vec[index].pn_node = new_node; /* Inherit */
	self->pv_vec[index].pn_part = part;     /* Inherit reference */
	++self->pv_cnt;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL partnode_pair_vector_fini)(struct partnode_pair_vector *__restrict self) {
	size_t i;
	assert(self->pv_cnt <= self->pv_alc);
	i = self->pv_cnt;
	while (i--)
		sync_endwrite(self->pv_vec[i].pn_part);
	i = self->pv_cnt;
	while (i--)
		decref_unlikely(self->pv_vec[i].pn_part);
	i = self->pv_cnt;
	while (i--)
		kfree(self->pv_vec[i].pn_node);
	if (self->pv_vec != self->pv_buf)
		kfree(self->pv_vec);
}

LOCAL void KCALL log_updating_access_rights(struct vm_node *__restrict self) {
	printk(KERN_DEBUG "[vm] Update access rights of %p...%p [pid:%u]\n",
	       VM_NODE_MINADDR(self), VM_NODE_MAXADDR(self),
	       task_getroottid_s());
}


/* Delete the mapping `self' for the purpose of re-loading
 * write permissions in on the following scenarios:
 *  - mmap(MAP_PRIVATE):
 *    The first mapping of a data part that is already being SHARED by
 *    any number of other mappings. - In this case, all existing SHARED
 *    mappings need to have their write-access updated, so-as to allow
 *    the copy-on-write mapping to be unshared after the next write.
 *    -> `vm_node_update_write_access()' needs to be called for every
 *        pre-existing SHARED memory mapping.
 *  - mmap(MAP_PRIVATE):
 *    The second mapping of an anonymous datapart (aka. the first datapart
 *    had been granted write-access since it was the sole owner owner of
 *    the underlying anonymous memory)
 *    -> `vm_node_update_write_access()' needs to be called for the
 *        pre-existing PRIVATE memory mapping.
 * @return: * : One of `VM_NODE_UPDATE_WRITE_ACCESS_*' */
PUBLIC NOBLOCK unsigned int
NOTHROW(KCALL vm_node_update_write_access)(struct vm_node *__restrict self) {
	vm_vpage_t min;
	size_t cnt;
	if (!(self->vn_prot & VM_PROT_WRITE))
		return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
	if (!sync_trywrite(self->vn_vm))
		return VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK;
	if (!vm_sync_trybegin(self->vn_vm)) {
		sync_endwrite(self->vn_vm);
		return VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK_TASKS;
	}
	/* Just delete the mapping, so it has to be re-created, at which
	 * point all of the intended copy-on-write mechanics will take
	 * place. */
	min = VM_NODE_MIN(self);
	cnt = VM_NODE_SIZE(self);
	log_updating_access_rights(self);
	if (self->vn_vm == THIS_VM) {
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map(min, cnt)) {
				vm_sync_abort(self->vn_vm);
				sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
		pagedir_unwrite(min, cnt);
#else /* CONFIG_HAVE_PAGEDIR_UNWRITE */
		pagedir_unmap(min, cnt);
#endif /* !CONFIG_HAVE_PAGEDIR_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map(min, cnt);
	} else {
		PAGEDIR_P_SELFTYPE pdir = PAGEDIR_P_SELFOFVM(self->vn_vm);
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map_p(pdir, min, cnt)) {
				vm_sync_abort(self->vn_vm);
				sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
		pagedir_unwrite_p(pdir, min, cnt);
#else /* CONFIG_HAVE_PAGEDIR_UNWRITE */
		pagedir_unmap_p(pdir, min, cnt);
#endif /* !CONFIG_HAVE_PAGEDIR_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map_p(pdir, min, cnt);
	}
	vm_sync_end(self->vn_vm, min, cnt);
	sync_endwrite(self->vn_vm);
	return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
}

/* Same as `vm_node_update_write_access()', but the caller
 * is already holding a write-lock to `locked_vm' */
PUBLIC NOBLOCK unsigned int
NOTHROW(KCALL vm_node_update_write_access_locked_vm)(struct vm_node *__restrict self,
                                                     struct vm *__restrict locked_vm) {
	vm_vpage_t min;
	size_t cnt;
	if (!(self->vn_prot & VM_PROT_WRITE))
		return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
	if (self->vn_vm != locked_vm && !sync_trywrite(self->vn_vm))
		return VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK;
	if (!vm_sync_trybegin(self->vn_vm)) {
		if (self->vn_vm != locked_vm)
			sync_endwrite(self->vn_vm);
		return VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK_TASKS;
	}

	/* Just delete the mapping, so it has to be re-created, at which
	 * point all of the intended copy-on-write mechanics will take
	 * place. */
	min = VM_NODE_MIN(self);
	cnt = VM_NODE_SIZE(self);
	log_updating_access_rights(self);
	if (self->vn_vm == THIS_VM) {
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map(min, cnt)) {
				vm_sync_abort(self->vn_vm);
				if (self->vn_vm != locked_vm)
					sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
		pagedir_unwrite(min, cnt);
#else /* CONFIG_HAVE_PAGEDIR_UNWRITE */
		pagedir_unmap(min, cnt);
#endif /* !CONFIG_HAVE_PAGEDIR_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map(min, cnt);
	} else {
		PAGEDIR_P_SELFTYPE pdir = PAGEDIR_P_SELFOFVM(self->vn_vm);
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map_p(pdir, min, cnt)) {
				vm_sync_abort(self->vn_vm);
				if (self->vn_vm != locked_vm)
					sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
		pagedir_unwrite_p(pdir, min, cnt);
#else /* CONFIG_HAVE_PAGEDIR_UNWRITE */
		pagedir_unmap_p(pdir, min, cnt);
#endif /* !CONFIG_HAVE_PAGEDIR_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map_p(pdir, min, cnt);
	}
	vm_sync_end(self->vn_vm, min, cnt);
	if (self->vn_vm != locked_vm)
		sync_endwrite(self->vn_vm);
	return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
}


/* Collect and lock all parts required to span the given range of memory
 * within the specified data block, before acquiring a write-lock to all
 * of those parts and re-check that they still span the entirety of the
 * given memory range within `data'. Afterwards, acquire a write-lock to
 * the given `effective_vm', before returning to the caller with locks held
 * to all of the indicated data parts, as well as the given VM, allowing
 * them to then use those parts in order to create a mapping of them within
 * the given VM.
 * NOTE: For every part that is acquired, this function also allocates 1
 *      `struct vm_node' object which must also be inherited by the caller,
 *       essentially off-loading all of the hard preparation work required
 *       to map some region of a datablock into memory, as well as thread-safe
 *       acquisition of all of the required locks. */
PRIVATE void KCALL
vm_collect_and_lock_parts_and_vm(struct partnode_pair_vector *__restrict info,
                                 struct vm *__restrict effective_vm,
                                 struct vm_datablock *__restrict data,
                                 vm_vpage64_t data_start_vpage,
                                 size_t num_pages,
                                 uintptr_half_t prot)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	if (ATOMIC_READ(data->db_parts) == VM_DATABLOCK_ANONPARTS) {
		/* Simple case: We can allocate the part in its entirety, all from the get-go! */
		info->pv_vec            = info->pv_buf;
		info->pv_cnt            = 1;
		info->pv_buf[0].pn_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
		                                                    GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		TRY {
			/* Create the associated part.
			 * NOTE: Because we're the ones creating it, we don't have to look
			 *       out for splitting parts, or anything in that manner. */
			info->pv_buf[0].pn_part = vm_datablock_do_createpart(data,
			                                                     data_start_vpage,
			                                                     num_pages);
			/* The caller wants us to give them some write-lock, so let's given them one! */
			shared_rwlock_init_write(&info->pv_buf[0].pn_part->dp_lock);
			TRY {
				sync_write(effective_vm);
			} EXCEPT {
				destroy(info->pv_buf[0].pn_part);
				RETHROW();
			}
		} EXCEPT {
			kfree(info->pv_buf[0].pn_node);
			RETHROW();
		}
		return;
	}
	info->pv_vec = info->pv_buf;
	info->pv_cnt = 0;
	info->pv_alc = COMPILER_LENOF(info->pv_buf);
	TRY {
		REF struct vm_datapart *part;
		size_t total_pages;
		/* Step #1: Collect all of the required parts. */
		part = vm_datablock_locatepart_exact(data,
		                                     data_start_vpage,
		                                     num_pages);
		TRY {
			partnode_pair_vector_addpart(info, part);
		} EXCEPT {
			vm_datapart_decref_and_merge(part);
			RETHROW();
		}
#define vm_datapart_numvpages_atomic(self)                                           \
	((size_t)((ATOMIC_READ((self)->dp_tree.a_vmax) - (self)->dp_tree.a_vmin) + 1) >> \
	 VM_DATABLOCK_PAGESHIFT((self)->dp_block))
		/* Load additional parts which may span the specified range. */
		total_pages = vm_datapart_numvpages_atomic(part);
		while (total_pages < num_pages) {
			part = vm_datablock_locatepart_exact(data,
			                                     data_start_vpage + total_pages,
			                                     num_pages - total_pages);
			TRY {
				partnode_pair_vector_addpart(info, part);
			} EXCEPT {
				vm_datapart_decref_and_merge(part);
				RETHROW();
			}
			/* NOTE: The reference to `part' was inherited by `partnode_pair_vector_addpart()' */
			total_pages += vm_datapart_numvpages_atomic(part);
		}
		assert(total_pages == num_pages);
		/* We've now (presumably) gathered all of the necessary pages
		 * Now it's time to lock all of them and check to make sure that
		 * no gaps have formed prior to us acquiring locks to all of them. */
again_lock_all_parts:
		for (;;) {
			part = partnode_pair_vector_trywrite_parts(info);
			if likely(!part)
				break;
			sync_write(part);
			sync_endwrite(part);
		}
		/* With all of the necessary locks no held, check if they still form
		 * a continuous range of parts that span the entirety of requested
		 * address range. */
		{
			size_t i;
			COMPILER_READ_BARRIER();
			for (i = 0; i < info->pv_cnt; ++i) {
				vm_vpage64_t part_end, req_part_end;
				req_part_end = i == info->pv_cnt - 1
				               ? data_start_vpage + num_pages
				               : vm_datapart_startvpage(info->pv_vec[i + 1].pn_part);
				part_end = vm_datapart_endvpage(info->pv_vec[i].pn_part);
				assert(part_end <= req_part_end);
				if (part_end >= req_part_end)
					continue; /* Continuous */
				/* There's a part missing between `part_end' and `req_part_end' */
				partnode_pair_vector_endwrite_parts(info);
				part = vm_datablock_locatepart_exact(data, part_end,
				                                     (size_t)(req_part_end - part_end));
				TRY {
					partnode_pair_vector_insertpart(info, i + 1, part);
				} EXCEPT {
					vm_datapart_decref_and_merge(part);
					RETHROW();
				}
				/* Re-acquire locks to all of the necessary parts. */
				goto again_lock_all_parts;
			}
			if (!(prot & VM_PROT_SHARED)) {
				/* When the caller is mapping with write-permissions, must
				 * delete write permissions for other mappings:
				 * >> if (prot & VM_PROT_SHARED) {
				 * >>  LLIST_INSERT(part->dp_srefs,node,vn_link);
				 * >> } else {
				 * >>  // The addition of the first copy-on-write mapping requires
				 * >>  // that all existing SHARED memory mappings be updated to
				 * >>  // not include write permissions in their page directories.
				 * >>  // That way, a #PF will be triggered which will then unshare
				 * >>  // our own data part, preventing writes to the shared mapping
				 * >>  // from leaking into private mappings.
				 * >>  if (part->dp_crefs == NULL)
				 * >>      PAGEDIR_REMOVE_WRITE_FOR_ALL(part->dp_srefs);
				 * >>  else if (NEXT(part->dp_crefs) == NULL &&
				 * >>           ATOMIC_READ(part->dp_block->db_parts) == VM_DATABLOCK_ANONPARTS) {
				 * >>      // If this is the second copy-on-write mapping of an anonymous data part,
				 * >>      // then the first one may have had write permissions which must now be
				 * >>      // unshared (this is the case for general purpose RAM during fork())
				 * >>      PAGEDIR_REMOVE_WRITE_FOR_ONE(part->dp_crefs);
				 * >>  }
				 * >>  LLIST_INSERT(part->dp_crefs,node,vn_link);
				 * >> } */
				for (i = 0; i < info->pv_cnt; ++i) {
					struct vm_datapart *part;
					unsigned int error;
					REF struct vm *blocking_vm;
					part = info->pv_vec[i].pn_part;
					if (part->dp_crefs == NULL) {
						struct vm_node *iter;
						/* The addition of the first copy-on-write mapping requires
						 * that all existing SHARED memory mappings be updated to
						 * not include write permissions in their page directories.
						 * That way, a #PF will be triggered which will then unshare
						 * our own data part, preventing writes to the shared mapping
						 * from leaking into private mappings. */
						for (iter = part->dp_srefs; iter;
						     iter = iter->vn_link.ln_next) {
							error = vm_node_update_write_access(iter);
							if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
								blocking_vm = iter->vn_vm;
								goto handle_remove_write_error;
							}
						}
					} else if (part->dp_crefs->vn_link.ln_next == NULL &&
					           /* If this is the second copy-on-write mapping of an anonymous data part,
					            * then the first one may have had write permissions which must now be
					            * unshared (this is the case for general purpose RAM during fork()) */
					           ATOMIC_READ(part->dp_block->db_parts) == VM_DATABLOCK_ANONPARTS) {
						error = vm_node_update_write_access(part->dp_crefs);
						if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
							blocking_vm = part->dp_crefs->vn_vm;
handle_remove_write_error:
							if (error == VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC) {
								partnode_pair_vector_endwrite_parts(info);
								THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
							}
							if (!tryincref(blocking_vm))
								blocking_vm = NULL;
							partnode_pair_vector_endwrite_parts(info);
							assert(error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK ||
							       error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK_TASKS);
							if (blocking_vm) {
								FINALLY_DECREF_UNLIKELY(blocking_vm);
								if (error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK_TASKS) {
									vm_tasklock_read(blocking_vm);
									vm_tasklock_endread(blocking_vm);
								} else {
									sync_write(blocking_vm);
									sync_endwrite(blocking_vm);
								}
							}
							goto again_lock_all_parts;
						}
					}
				}
			}
		}
		/* And we're done! - We've got a lock to a continuous range of data parts,
		 * so now all that's still missing is getting a lock on the given `effective_vm'
		 * If this fails, we simply have to do some more lock juggling, before re-locking
		 * all of the associated data parts and re-checking for gaps. */
		if (!sync_trywrite(effective_vm)) {
			partnode_pair_vector_endwrite_parts(info);
			sync_write(effective_vm);
			sync_endwrite(effective_vm);
			goto again_lock_all_parts;
		}
	} EXCEPT {
		partnode_pair_vector_fini(info);
		RETHROW();
	}
}



/* Map the memory region into the given VM.
 * The caller may invoke `vm_sync()' after changes have been made.
 * @param: prot:   Set of `VM_PROT_*'.
 * @param: flag:   Set of `VM_NODE_FLAG_*'.
 * @param: data_start_vpage: The memory page index where mapping of `data' starts.
 * @param: guard:  If non-zero, repetition limit for a guard mapping.
 *                 Set to 0 if the mapping should include a guard.
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
PUBLIC bool KCALL
vm_mapat(struct vm *__restrict effective_vm,
         vm_vpage_t page_index, size_t num_pages,
         struct vm_datablock *__restrict data,
         vm_vpage64_t data_start_vpage, uintptr_half_t prot,
         uintptr_half_t flag, uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	size_t i;
	struct partnode_pair_vector parts;
	assert(!(flag & (VM_NODE_FLAG_COREPRT | VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_HINTED | VM_NODE_FLAG_GROWSUP)));
	assert(!(prot & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)));
	if unlikely(!num_pages)
		return true;
	/* Load parts & acquire locks. */
	vm_collect_and_lock_parts_and_vm(&parts,
	                                 effective_vm,
	                                 data,
	                                 data_start_vpage,
	                                 num_pages,
	                                 prot);
	/* The rest of this function is already NOEXCEPT at this point.
	 * However, we still need to check that the indicated range isn't
	 * already being used by some other mapping! */
	if unlikely(vm_nodetree_rlocate(effective_vm->v_tree,
	                                page_index,
	                                page_index + num_pages - 1)) {
		/* It _is_ already being used... */
		sync_endwrite(effective_vm);
		partnode_pair_vector_fini(&parts);
		return false;
	}
	printk(KERN_DEBUG "Map %p...%p against %Iu data parts\n",
	       VM_PAGE2ADDR(page_index),
	       VM_PAGE2ADDR(page_index + num_pages) - 1,
	       parts.pv_cnt);
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare_map(page_index, num_pages)) {
			sync_endwrite(effective_vm);
			partnode_pair_vector_fini(&parts);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
		}
	}

	/* Now to use what we were given, and initialize the memory mapping! */
	assert(parts.pv_cnt != 0);
	for (i = 0; i < parts.pv_cnt; ++i) {
		struct vm_datapart *part;
		struct vm_node *node;
		size_t part_pages;
		part = parts.pv_vec[i].pn_part;
		node = parts.pv_vec[i].pn_node;
		assert(sync_writing(part));
		assert(node);

		/* Initialize the given node. */
		part_pages           = vm_datapart_numvpages(part);
		node->vn_node.a_vmin = page_index;
		node->vn_node.a_vmax = page_index + part_pages - 1;
		node->vn_prot        = prot;
		node->vn_flags       = flag & VM_NODE_FLAG_PREPARED;
		node->vn_vm          = effective_vm;
		node->vn_part        = part; /* Inherit reference */
		node->vn_block       = incref(data);
		node->vn_guard       = 0;
		if (prot & VM_PROT_SHARED) {
			LLIST_INSERT(part->dp_srefs, node, vn_link);
		} else {
			LLIST_INSERT(part->dp_crefs, node, vn_link);
		}
		/* Map the given node into its associated VM */
		vm_node_insert(node);
		/* Release the write-lock from parts, as they are mapped. */
		sync_endwrite(part);
		page_index += part_pages;
	}

	/* Apply a guard to the appropriate page. */
	if (guard != 0) {
		if (flag & VM_NODE_FLAG_GROWSUP) {
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_guard = guard;
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_flags |= VM_NODE_FLAG_GROWSUP;
		} else {
			parts.pv_vec[0].pn_node->vn_guard = guard;
		}
	}
	sync_endwrite(effective_vm);
	if (parts.pv_vec != parts.pv_buf)
		kfree(parts.pv_vec);
	return true;
}


/* Create a memory reservation mapping at the given address.
 * @param: flag: Set of `VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE'
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
PUBLIC bool KCALL
vm_mapresat(struct vm *__restrict effective_vm,
            vm_vpage_t page_index, size_t num_pages,
            uintptr_half_t flag)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *node;
	assert(!(flag & ~(VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE)));
	if unlikely(!num_pages)
		return true;
	node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                 GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	node->vn_node.a_vmin = page_index;
	node->vn_node.a_vmax = page_index + num_pages - 1;
	node->vn_prot        = VM_PROT_NONE;
	node->vn_flags       = flag;
	node->vn_vm          = effective_vm;
	node->vn_part        = NULL;
	node->vn_block       = NULL;
#ifndef NDEBUG
	memset(&node->vn_link, 0xcc, sizeof(node->vn_link));
#endif
	node->vn_guard = 0;
	TRY {
		sync_write(effective_vm);
	} EXCEPT {
		kfree(node);
		RETHROW();
	}
	/* Check if the specified range is already in use. */
	if unlikely(vm_nodetree_rlocate(effective_vm->v_tree,
	                                page_index,
	                                page_index + num_pages - 1)) {
		sync_endwrite(effective_vm);
		kfree(node);
		return false;
	}
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare_map(page_index, num_pages)) {
			sync_endwrite(effective_vm);
			kfree(node);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
		}
	}
	/* Insert the new node into the given VM. */
	vm_node_insert(node);
	sync_endwrite(effective_vm);
	return true;
}



/* A combination of `vm_getfree' + `vm_mapat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target. */
PUBLIC vm_vpage_t KCALL
vm_map(struct vm *__restrict effective_vm,
       vm_vpage_t hint, size_t num_pages,
       size_t min_alignment_in_pages,
       unsigned int getfree_mode,
       struct vm_datablock *__restrict data,
       vm_vpage64_t data_start_vpage, uintptr_half_t prot,
       uintptr_half_t flag, uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	size_t i;
	vm_vpage_t result, offset;
	struct partnode_pair_vector parts;
	uintptr_t version = 0;
	assert(!(flag & (VM_NODE_FLAG_COREPRT | VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_HINTED)));
	assert(!(prot & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)));
	if unlikely(!num_pages)
		num_pages = 1;
again:
	/* Load parts & acquire locks. */
	vm_collect_and_lock_parts_and_vm(&parts,
	                                 effective_vm,
	                                 data,
	                                 data_start_vpage,
	                                 num_pages,
	                                 prot);
	/* The rest of this function is already NOEXCEPT at this point.
	 * However, we still need to check that the indicated range isn't
	 * already being used by some other mapping! */
	result = vm_getfree(effective_vm,
	                    hint,
	                    num_pages,
	                    min_alignment_in_pages,
	                    getfree_mode);
	if unlikely(result == VM_GETFREE_ERROR) {
		/* It _is_ already being used... */
		sync_endwrite(effective_vm);
		partnode_pair_vector_fini(&parts);
		if (system_clearcaches_s(&version))
			goto again;
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		      num_pages);
	}
	assertf(!vm_isused(effective_vm, result, result + num_pages - 1),
	        "result             = %p (%p)\n"
	        "num_pages          = %Iu\n"
	        "result + num_pages = %p (%p)\n",
	        VM_PAGE2ADDR(result), result, num_pages,
	        VM_PAGE2ADDR(result + num_pages), result + num_pages);

	printk(KERN_DEBUG "Map %p...%p against %Iu data parts\n",
	       VM_PAGE2ADDR(result),
	       VM_PAGE2ADDR(result + num_pages) - 1,
	       parts.pv_cnt);
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare_map(result, num_pages)) {
			sync_endwrite(effective_vm);
			partnode_pair_vector_fini(&parts);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
		}
	}

	/* Now to use what we were given, and initialize the memory mapping! */
	assert(parts.pv_cnt != 0);
	offset = result;
	for (i = 0; i < parts.pv_cnt; ++i) {
		struct vm_datapart *part;
		struct vm_node *node;
		size_t part_pages;
		part = parts.pv_vec[i].pn_part;
		node = parts.pv_vec[i].pn_node;
		assert(sync_writing(part));
		assert(node);

		/* Initialize the given node. */
		part_pages = vm_datapart_numvpages(part);
		assertf(offset + part_pages <= result + num_pages,
		        "offset              = %p (%p)\n"
		        "part_pages          = %Iu\n"
		        "result              = %p (%p)\n"
		        "num_pages           = %Iu\n"
		        "offset + part_pages = %p (%p)\n"
		        "result + num_pages  = %p (%p)\n",
		        VM_PAGE2ADDR(offset), offset, part_pages,
		        VM_PAGE2ADDR(result), result, num_pages,
		        VM_PAGE2ADDR(offset + part_pages), offset + part_pages,
		        VM_PAGE2ADDR(result + num_pages), result + num_pages);
		assertf(!vm_isused(effective_vm, offset, offset + part_pages - 1),
		        "offset              = %p (%p)\n"
		        "part_pages          = %Iu\n"
		        "result              = %p (%p)\n"
		        "num_pages           = %Iu\n"
		        "offset + part_pages = %p (%p)\n"
		        "result + num_pages  = %p (%p)\n",
		        VM_PAGE2ADDR(offset), offset, part_pages,
		        VM_PAGE2ADDR(result), result, num_pages,
		        VM_PAGE2ADDR(offset + part_pages), offset + part_pages,
		        VM_PAGE2ADDR(result + num_pages), result + num_pages);

		node->vn_node.a_vmin = offset;
		node->vn_node.a_vmax = offset + part_pages - 1;
		node->vn_prot        = prot;
		node->vn_flags       = flag & VM_NODE_FLAG_PREPARED;
		node->vn_vm          = effective_vm;
		node->vn_part        = part; /* Inherit reference */
		node->vn_block       = incref(data);
		node->vn_guard       = 0;
		if (prot & VM_PROT_SHARED) {
			LLIST_INSERT(part->dp_srefs, node, vn_link);
		} else {
			LLIST_INSERT(part->dp_crefs, node, vn_link);
		}
		/* Map the given node into its associated VM */
		vm_node_insert(node);
		/* Release the write-lock from parts, as they are mapped. */
		sync_endwrite(part);
		offset += part_pages;
	}
	assertf(offset == result + num_pages,
	        "offset             = %p\n"
	        "result + num_pages = %p\n"
	        "result             = %p\n"
	        "num_pages          = %Iu\n",
	        offset, result + num_pages,
	        result, num_pages);

	/* Apply a guard to the appropriate page. */
	if (guard != 0) {
		if (flag & VM_NODE_FLAG_GROWSUP) {
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_guard = guard;
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_flags |= VM_NODE_FLAG_GROWSUP;
		} else {
			parts.pv_vec[0].pn_node->vn_guard = guard;
		}
	}
	sync_endwrite(effective_vm);
	if (parts.pv_vec != parts.pv_buf)
		kfree(parts.pv_vec);
	return result;
}


/* Same as `vm_map()', but only allowed pages between `data_subrange_minvpage ... data_subrange_maxvpage'
 * to be mapped from `data'. - Any attempted to map data from outside that range will instead cause
 * memory from `vm_datablock_anonymous_zero' to be mapped.
 * Additionally, `data_start_vpage' is an offset from `data_subrange_minvpage' */
PUBLIC vm_vpage_t KCALL
vm_map_subrange(struct vm *__restrict effective_vm,
                vm_vpage_t hint,
                size_t num_pages,
                size_t min_alignment_in_pages,
                unsigned int getfree_mode,
                struct vm_datablock *__restrict data,
                vm_vpage64_t data_start_vpage,
                vm_vpage64_t data_subrange_minvpage,
                vm_vpage64_t data_subrange_maxvpage,
                uintptr_half_t prot,
                uintptr_half_t flag,
                uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	vm_vpage64_t data_minmappage, data_maxmappage;
	size_t num_pages_with_guard;
	if unlikely(!num_pages)
		num_pages = 1;
	if (OVERFLOW_UADD(data_subrange_minvpage, data_start_vpage, &data_minmappage) ||
		data_minmappage > data_subrange_maxvpage) {
		/* The entire range is out-of-bounds.
		 * Map everything as ANON+ZERO */
		return vm_map(effective_vm,
		              hint,
		              num_pages,
		              min_alignment_in_pages,
		              getfree_mode,
		              &vm_datablock_anonymous_zero,
		              0,
		              prot,
		              flag,
		              guard);
	}
	num_pages_with_guard = num_pages;
	if (guard > 1)
		num_pages_with_guard += guard - 1;
	assert(num_pages_with_guard != 0);
	if (OVERFLOW_UADD(data_minmappage, num_pages_with_guard - 1, &data_maxmappage) ||
	    data_maxmappage > data_subrange_maxvpage) {
		size_t num_datapages, num_zeropages, zeropages_offset;
		struct partnode_pair zeropart;
		num_datapages    = (size_t)(data_subrange_maxvpage - data_minmappage) + 1;
		zeropages_offset = num_datapages;
		num_zeropages    = num_pages - num_datapages;
		assert(num_datapages != 0);
		assert(num_zeropages != 0);
		if (num_datapages > num_pages)
			num_datapages = num_pages; /* This can happen due to the presence of a guard. */
		/* Must map as 2 parts:
		 * A total of `num_datapages' from data+data_minmappage, followed by
		 * a total of `num_zeropages' from `&vm_datablock_anonymous_zero'.
		 * To prevent race conditions, we must map both of these at the same time!
		 * TODO: Must also account for `guard', as well as its direction!
		 *       Note that cases exist where both mappings need a custom guard descriptor.
		 */
		/* TODO: This part should happen in a common helper-method shared with vm_mapat_subrange() */
#if 1
		THROW(E_NOT_IMPLEMENTED_TODO);
#else
		/* Start by allocating the node+datapart for `num_zeropages' */
		zeropart.pn_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
		                                             GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		TRY {
			zeropart.pn_part = vm_datablock_do_createpart(&vm_datablock_anonymous_zero,
			                                              0,
			                                              num_zeropages);
		} EXCEPT {
			kfree(zeropart.pn_node);
			RETHROW();
		}
#endif
	}

	/* The entire mapping fits into the allowed mapping-range of the given data-block.
	 * -> We can just map the memory normally. */
	return vm_map(effective_vm,
	              hint,
	              num_pages,
	              min_alignment_in_pages,
	              getfree_mode,
	              data,
	              data_minmappage,
	              prot,
	              flag,
	              guard);
}




/* Same as `vm_mapat()', but only allowed pages between `data_subrange_minvpage ... data_subrange_maxvpage'
 * to be mapped from `data'. - Any attempted to map data from outside that range will instead cause
 * memory from `vm_datablock_anonymous_zero' to be mapped.
 * Additionally, `data_start_vpage' is an offset from `data_subrange_minvpage' */
PUBLIC bool KCALL
vm_mapat_subrange(struct vm *__restrict effective_vm,
                  vm_vpage_t page_index, size_t num_pages,
                  struct vm_datablock *__restrict data,
                  vm_vpage64_t data_start_vpage,
                  vm_vpage64_t data_subrange_minvpage,
                  vm_vpage64_t data_subrange_maxvpage,
                  uintptr_half_t prot,
                  uintptr_half_t flag,
                  uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	vm_vpage64_t data_minmappage, data_maxmappage;
	size_t num_pages_with_guard;
	if unlikely(!num_pages)
		num_pages = 1;
	if (OVERFLOW_UADD(data_subrange_minvpage, data_start_vpage, &data_minmappage) ||
		data_minmappage > data_subrange_maxvpage) {
		/* The entire range is out-of-bounds.
		 * Map everything as ANON+ZERO */
		return vm_mapat(effective_vm,
		                page_index,
		                num_pages,
		                &vm_datablock_anonymous_zero,
		                0,
		                prot,
		                flag,
		                guard);
	}
	num_pages_with_guard = num_pages;
	if (guard > 1)
		num_pages_with_guard += guard - 1;
	assert(num_pages_with_guard != 0);
	if (OVERFLOW_UADD(data_minmappage, num_pages_with_guard - 1, &data_maxmappage) ||
	    data_maxmappage > data_subrange_maxvpage) {
		size_t num_datapages, num_zeropages, zeropages_offset;
		struct partnode_pair zeropart;
		num_datapages    = (size_t)(data_subrange_maxvpage - data_minmappage) + 1;
		zeropages_offset = num_datapages;
		num_zeropages    = num_pages - num_datapages;
		assert(num_datapages != 0);
		assert(num_zeropages != 0);
		if (num_datapages > num_pages)
			num_datapages = num_pages; /* This can happen due to the presence of a guard. */
		/* Must map as 2 parts:
		 * A total of `num_datapages' from data+data_minmappage, followed by
		 * a total of `num_zeropages' from `&vm_datablock_anonymous_zero'.
		 * To prevent race conditions, we must map both of these at the same time!
		 * TODO: Must also account for `guard', as well as its direction!
		 *       Note that cases exist where both mappings need a custom guard descriptor.
		 */
		/* TODO: This part should happen in a common helper-method shared with vm_map_subrange() */
#if 1
		THROW(E_NOT_IMPLEMENTED_TODO);
#else
		/* Start by allocating the node+datapart for `num_zeropages' */
		zeropart.pn_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
		                                             GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		TRY {
			zeropart.pn_part = vm_datablock_do_createpart(&vm_datablock_anonymous_zero,
			                                              0,
			                                              num_zeropages);
		} EXCEPT {
			kfree(zeropart.pn_node);
			RETHROW();
		}
#endif
	}

	/* The entire mapping fits into the allowed mapping-range of the given data-block.
	 * -> We can just map the memory normally. */
	return vm_mapat(effective_vm,
	                page_index,
	                num_pages,
	                data,
	                data_minmappage,
	                prot,
	                flag,
	                guard);
}




/* A combination of `vm_getfree' + `vm_mapresat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target. */
PUBLIC vm_vpage_t KCALL
vm_mapres(struct vm *__restrict effective_vm,
          vm_vpage_t hint, size_t num_pages,
          size_t min_alignment_in_pages,
          unsigned int getfree_mode, uintptr_half_t flag) {
	struct vm_node *node;
	vm_vpage_t result;
	uintptr_t version = 0;
	assert(!(flag & ~(VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE)));
	if unlikely(!num_pages)
		num_pages = 1;
	node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                 GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	node->vn_prot  = VM_PROT_NONE;
	node->vn_flags = flag;
	node->vn_vm    = effective_vm;
	node->vn_part  = NULL;
	node->vn_block = NULL;
#ifndef NDEBUG
	memset(&node->vn_link, 0xcc, sizeof(node->vn_link));
#endif
	node->vn_guard = 0;
again_lock_vm:
	TRY {
		sync_write(effective_vm);
	} EXCEPT {
		kfree(node);
		RETHROW();
	}
	/* Figure out a suitable mapping location */
	result = vm_getfree(effective_vm,
	                    hint,
	                    num_pages,
	                    min_alignment_in_pages,
	                    getfree_mode);
	if unlikely(result == VM_GETFREE_ERROR) {
		/* It _is_ already being used... */
		sync_endwrite(effective_vm);
		if (system_clearcaches_s(&version))
			goto again_lock_vm;
		kfree(node);
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		      num_pages);
	}

	node->vn_node.a_vmin = result;
	node->vn_node.a_vmax = result + num_pages - 1;
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare_map(result, num_pages)) {
			sync_endwrite(effective_vm);
			kfree(node);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
		}
	}
	/* Insert the new node into the given VM. */
	vm_node_insert(node);
	sync_endwrite(effective_vm);
	return result;
}



/* Insert the given node into its associated VM (self->vn_vm)
 * NOTE: The caller must be holding a write-lock to the associated VM. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_insert)(struct vm_node *__restrict self) {
	struct vm_node **pinsert, *insert_before;
	struct vm *v = self->vn_vm;
	assert(v);
	assertf(VM_NODE_MIN(self) <= VM_NODE_MAX(self),
	        "Unordered node: MIN(%p) >= MAX(%p)",
	        VM_NODE_MINADDR(self), VM_NODE_MAXADDR(self));
	assertf(VM_NODE_MAX(self) <= VM_VPAGE_MAX,
	        "Mapping of node covering pages %p...%p is out-of-bounds",
	        VM_NODE_MIN(self), VM_NODE_MAX(self));
	assert(self->vn_block ? true : !self->vn_part);
	assertf(!self->vn_part ||
	        VM_NODE_SIZE(self) == vm_datapart_numvpages(self->vn_part),
	        "Node size missmatch (%Iu != %Iu)",
	        VM_NODE_SIZE(self), vm_datapart_numvpages(self->vn_part));
	assert((v->v_tree != NULL) == (v->v_byaddr != NULL));
	vm_nodetree_insert(&v->v_tree, self);
	/* Figure out where we need to insert the self. */
	pinsert = &v->v_byaddr;
	while ((insert_before = *pinsert) != NULL &&
	       (insert_before->vn_node.a_vmax < self->vn_node.a_vmin))
		pinsert = &insert_before->vn_byaddr.ln_next;
	assertf(!insert_before ||
	        self->vn_node.a_vmax < insert_before->vn_node.a_vmin,
	        "insert_before  = %p:%p...%p\n"
	        "self           = %p:%p...%p\n"
	        "self->vn_flags = %#.4I16x\n",
	        insert_before, VM_NODE_MINADDR(insert_before), VM_NODE_MAXADDR(insert_before),
	        self, VM_NODE_MINADDR(self), VM_NODE_MAXADDR(self),
	        self->vn_flags);
	/* Insert the self before `insert' at `pinsert' */
	self->vn_byaddr.ln_pself = pinsert;
	self->vn_byaddr.ln_next  = insert_before;
	if (insert_before)
		insert_before->vn_byaddr.ln_pself = &self->vn_byaddr.ln_next;
	*pinsert = self;
}

PUBLIC NOBLOCK NONNULL((1)) struct vm_node *
NOTHROW(KCALL vm_node_remove)(struct vm *__restrict effective_vm, vm_vpage_t page) {
	struct vm_node *result;
	assert(sync_writing(effective_vm) || !isshared(effective_vm) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	result = vm_nodetree_remove(&effective_vm->v_tree, page);
	if likely(result)
		LLIST_REMOVE(result, vn_byaddr);
	return result;
}


#if 0
PRIVATE void KCALL
vm_assert_at(struct vm_node *__restrict node,
             ATREE_SEMI_T(vm_vpage_t) addr_semi,
             ATREE_LEVEL_T addr_level) {
	vm_vpage_t addr_min;
	vm_vpage_t addr_max;
again:
	addr_min = ATREE_MAPMIN(vm_vpage_t, addr_semi, addr_level);
	addr_max = ATREE_MAPMAX(vm_vpage_t, addr_semi, addr_level);
	assertf(node->vn_node.a_vmin <= node->vn_node.a_vmax,
	        "Branch has invalid min/max configuration (min(%p) > max(%p)) (semi %p; level %u)",
	        (node->vn_node.a_vmin),
	        (node->vn_node.a_vmax),
	        (addr_semi), addr_level);
	assertf(node->vn_node.a_vmin >= addr_min,
	        "Unexpected branch min key (%p < %p; max: %p; semi %p; level %u)",
	        (node->vn_node.a_vmin), (addr_min),
	        (node->vn_node.a_vmax),
	        (addr_semi), addr_level);
	assertf(node->vn_node.a_vmax <= addr_max,
	        "Unexpected branch max key (%p > %p; min: %p; semi %p; level %u)",
	        (node->vn_node.a_vmax), (addr_max),
	        (node->vn_node.a_vmin),
	        (addr_semi), addr_level);
	if (node->vn_node.a_min) {
		if (node->vn_node.a_max) {
			vm_vpage_t next_semi;
			ATREE_LEVEL_T next_level;
			next_semi  = addr_semi;
			next_level = addr_level;
			ATREE_WALKMAX(vm_vpage_t, next_semi, next_level);
			vm_assert_at(node->vn_node.a_max, next_semi, next_level);
		}
		ATREE_WALKMIN(vm_vpage_t, addr_semi, addr_level);
		node = node->vn_node.a_min;
		goto again;
	}
	if (node->vn_node.a_max) {
		ATREE_WALKMAX(vm_vpage_t, addr_semi, addr_level);
		node = node->vn_node.a_max;
		goto again;
	}
}

INTERN void KCALL vm_assert(void) {
	if (vm_kernel.v_tree)
		vm_assert_at(vm_kernel.v_tree, VM_SEMI0, VM_LEVEL0);
}
#endif


/* Get the node associated with the given `page'
 * NOTE: The caller must be holding a read-lock on `effective_vm'. */
PUBLIC NOBLOCK struct vm_node *
NOTHROW(FCALL vm_getnodeof)(struct vm *__restrict effective_vm, vm_vpage_t page) {
#if 0
	assert(sync_reading(effective_vm) || !isshared(effective_vm) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
#endif
	return vm_nodetree_locate(effective_vm->v_tree,
	                          page);
}


/* Check if some part of the given address range is currently in use.
 * NOTE: The caller must be holding a read-lock on `effective_vm'. */
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL vm_isused)(struct vm *__restrict effective_vm,
                         vm_vpage_t min_page,
                         vm_vpage_t max_page) {
	assert(sync_reading(effective_vm) || !isshared(effective_vm) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	return vm_nodetree_rlocate(effective_vm->v_tree,
	                           min_page,
	                           max_page) != NULL;
}




/* Find the first node with `VM_NODE_MIN(return) >= min_page_index'
 * If no such node exists, return `NULL' instead.
 * NOTE: The caller must be holding a read-lock to `effective_vm'. */
PUBLIC NOBLOCK WUNUSED struct vm_node *
NOTHROW(KCALL vm_find_first_node_greater_equal)(struct vm *__restrict effective_vm,
                                                vm_vpage_t min_page_index) {
	struct vm_node *result;
	assert(sync_reading(effective_vm) || !isshared(effective_vm) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	for (result = effective_vm->v_byaddr; result;
	     result = result->vn_byaddr.ln_next) {
		if (VM_NODE_MIN(result) >= min_page_index)
			break;
	}
	return result;
}

/* Find the last node with `VM_NODE_MAX(return) <= max_page_index'
 * If no such node exists, return `NULL' instead.
 * NOTE: The caller must be holding a read-lock to `effective_vm'. */
PUBLIC NOBLOCK WUNUSED struct vm_node *
NOTHROW(KCALL vm_find_last_node_lower_equal)(struct vm *__restrict effective_vm,
                                             vm_vpage_t max_page_index) {
	struct vm_node *result = NULL;
	struct vm_node *iter;
	assert(sync_reading(effective_vm) || !isshared(effective_vm) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	for (iter = effective_vm->v_byaddr; iter;
	     iter = iter->vn_byaddr.ln_next) {
		if (VM_NODE_MAX(iter) <= max_page_index)
			result = iter;
		else {
			break;
		}
	}
	return result;
}

#ifndef __INTELLISENSE__
DECL_END
#define VM_GETFREE_VM 1
#include "vm-getfree-impl.c.inl"
DECL_BEGIN
#endif


#ifndef __INTELLISENSE__
DECL_END
#define VM_DEFINE_UNMAP 1
#include "vm-unmap_protect.c.inl"
#define VM_DEFINE_PROTECT 1
#include "vm-unmap_protect.c.inl"
DECL_BEGIN
#endif






/* A data part used to describe a single, reserved page. */
INTERN ATTR_PERTASK struct vm_node _this_trampoline_node = {
	/* .vn_node   = */ { NULL, NULL, 0, 0 },
	/* .vn_byaddr = */ LLIST_INITNODE,
	/* .vn_prot   = */ VM_PROT_PRIVATE,
	/* .vn_flags  = */ VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED,
	/* .vn_vm     = */ &vm_kernel,
	/* .vn_part   = */ NULL,
	/* .vn_block  = */ NULL,
	/* .vn_link   = */ { NULL, NULL },
	/* .vn_guard  = */ 0
};


PUBLIC NONNULL((1)) void KCALL
vm_copyfromphys(USER CHECKED void *dst,
                PHYS vm_phys_t src,
                size_t num_bytes)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(src);
			page_bytes = PAGESIZE - (src & (PAGESIZE - 1));
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FREAD);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FREAD);
			}
			pagedir_syncone(tramp);
			/* Copy memory. */
			memcpy(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (PAGESIZE - 1))),
			       page_bytes);
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			src += page_bytes;
			dst = (byte_t *)dst + page_bytes;
		}
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NONNULL((2)) void KCALL
vm_copytophys(PHYS vm_phys_t dst,
              USER CHECKED void const *src,
              size_t num_bytes)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
			page_bytes = PAGESIZE - (dst & (PAGESIZE - 1));
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FWRITE);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FWRITE);
			}
			pagedir_syncone(tramp);
			/* Copy memory. */
			memcpy((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (PAGESIZE - 1))), src,
			       page_bytes);
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			dst += page_bytes;
			src = (void *)((byte_t *)src + page_bytes);
		}
	} EXCEPT {
		/* Try-catch is required, because `src' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_copyinphys)(PHYS vm_phys_t dst,
                             PHYS vm_phys_t src,
                             size_t num_bytes) {
	/* Copy data using a temporary buffer. */
	byte_t *buffer;
	size_t bufsize;
	if unlikely(!num_bytes)
		return;
	bufsize = stack_avail() / 2;
	if (bufsize > 512 * sizeof(void *))
		bufsize -= 512 * sizeof(void *);
	else {
		bufsize = 128 * sizeof(void *);
	}
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	else {
		if unlikely(!bufsize)
			bufsize = pagedir_pagesize();
		/* XXX: Try to acquire a lock to the kernel VM and try to temporarily
		 *      make use of some unused region of virtual memory to temporarily
		 *      map both `dst' and `src', allowing us to transfer data directly.
		 *   -> Since access to both source and target buffers is known not to
		 *      cause any visible side-effects in terms of special behavior such
		 *      as page-faults, or VIO memory access, doing this is possible in
		 *      this case, though this wouldn't be possible in the case of
		 *      copy(to|from)phys, as those operate with virtual buffers which
		 *      may have side-effects. */
	}
	assert(bufsize != 0);
	buffer = (byte_t *)alloca(bufsize);
	for (;;) {
		size_t transfer_size;
		transfer_size = bufsize;
		if (transfer_size > num_bytes)
			transfer_size = num_bytes;
		vm_copyfromphys(buffer, src, transfer_size);
		vm_copytophys(dst, buffer, transfer_size);
		if (transfer_size >= num_bytes)
			break;
		dst += transfer_size;
		src += transfer_size;
		num_bytes -= transfer_size;
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_memsetphys)(PHYS vm_phys_t dst, int byte, size_t num_bytes) {
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	for (;;) {
		vm_ppage_t pageaddr;
		size_t page_bytes;
		pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
		page_bytes = PAGESIZE - (dst & (PAGESIZE - 1));
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp, pageaddr,
			                             PAGEDIR_MAP_FWRITE);
		} else {
			pagedir_mapone(tramp, pageaddr,
			               PAGEDIR_MAP_FWRITE);
		}
		pagedir_syncone(tramp);
		/* Copy memory. */
		memset((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (PAGESIZE - 1))), byte,
		       page_bytes);
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		dst += page_bytes;
	}
	pagedir_pop_mapone(tramp, backup);
}

#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_one)(struct icpustate *__restrict state,
                              void *args[CPU_IPI_ARGCOUNT]) {
	pagedir_syncone((vm_vpage_t)(uintptr_t)args[0]);
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb)(struct icpustate *__restrict state,
                          void *args[CPU_IPI_ARGCOUNT]) {
	pagedir_sync((vm_vpage_t)(uintptr_t)args[0],
	             (size_t)(uintptr_t)args[1]);
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_all)(struct icpustate *__restrict state,
                              void *args[CPU_IPI_ARGCOUNT]) {
	pagedir_syncall();
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_one_for)(struct icpustate *__restrict state,
                                  void *args[CPU_IPI_ARGCOUNT]) {
	if (THIS_VM == (struct vm *)args[0])
		pagedir_syncone((vm_vpage_t)(uintptr_t)args[1]);
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_for)(struct icpustate *__restrict state,
                              void *args[CPU_IPI_ARGCOUNT]) {
	if (THIS_VM == (struct vm *)args[0])
		pagedir_sync((vm_vpage_t)(uintptr_t)args[1],
		             (size_t)(uintptr_t)args[2]);
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_all_for)(struct icpustate *__restrict state,
                                  void *args[CPU_IPI_ARGCOUNT]) {
	if (THIS_VM == (struct vm *)args[0])
		pagedir_syncall();
	return state;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
/* Synchronize changes to `effective_vm' in the given address range.
 * In SMP, this function will automatically communicate changes to other
 * CPUs making use of the same VM, and doing this synchronously.
 * If the given address range is located within the kernel
 * share-segment, or if `vm_syncall()' was called, a
 * did-change RPC is broadcast to all other CPUs. */
PUBLIC void FCALL
vm_sync(struct vm *__restrict effective_vm,
        vm_vpage_t page_index, size_t num_pages)
		THROWS(E_WOULDBLOCK) {
	if unlikely(effective_vm == &vm_kernel) {
		vm_kernel_sync(page_index, num_pages);
		return;
	}
	vm_tasklock_read(effective_vm);
	vm_sync_end(effective_vm, page_index, num_pages);
}

PUBLIC void FCALL
vm_syncone(struct vm *__restrict effective_vm,
           vm_vpage_t page_index)
		THROWS(E_WOULDBLOCK) {
	if unlikely(effective_vm == &vm_kernel) {
		vm_kernel_syncone(page_index);
		return;
	}
	vm_tasklock_read(effective_vm);
	vm_sync_endone(effective_vm, page_index);
}

PUBLIC void FCALL
vm_syncall(struct vm *__restrict effective_vm)
		THROWS(E_WOULDBLOCK) {
	if unlikely(effective_vm == &vm_kernel) {
		vm_kernel_syncall();
		return;
	}
	vm_tasklock_read(effective_vm);
	vm_sync_endall(effective_vm);
}

/* Sync functions for when the caller is already holding a lock to the VM's set of running tasks. */
PUBLIC NOBLOCK void
NOTHROW(FCALL vm_sync_locked)(struct vm *__restrict effective_vm,
                              vm_vpage_t page_index, size_t num_pages) {
	if unlikely(effective_vm == &vm_kernel) {
		vm_kernel_sync(page_index, num_pages);
	} else {
		cpuset_t targets;
		struct task *thread;
		void *args[CPU_IPI_ARGCOUNT];
		CPUSET_CLEAR(targets);
		LLIST_FOREACH(thread, effective_vm->v_tasks, t_vm_tasks) {
			cpuid_t cid;
			cid = ATOMIC_READ(thread->t_cpu)->c_id;
			CPUSET_INSERT(targets, cid);
		}
		args[0] = (void *)effective_vm;
		args[1] = (void *)(uintptr_t)page_index;
		args[2] = (void *)(uintptr_t)num_pages;
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb_for,
		                   args,
		                   CPU_IPI_FWAITFOR);
	}
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_syncone_locked)(struct vm *__restrict effective_vm,
                                 vm_vpage_t page_index) {
	if unlikely(effective_vm == &vm_kernel) {
		vm_kernel_syncone(page_index);
	} else {
		cpuset_t targets;
		struct task *thread;
		void *args[CPU_IPI_ARGCOUNT];
		CPUSET_CLEAR(targets);
		LLIST_FOREACH(thread, effective_vm->v_tasks, t_vm_tasks) {
			cpuid_t cid;
			cid = ATOMIC_READ(thread->t_cpu)->c_id;
			CPUSET_INSERT(targets, cid);
		}
		args[0] = (void *)effective_vm;
		args[1] = (void *)(uintptr_t)page_index;
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb_one_for,
		                   args,
		                   CPU_IPI_FWAITFOR);
	}
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_syncall_locked)(struct vm *__restrict effective_vm) {
	if unlikely(effective_vm == &vm_kernel) {
		vm_kernel_syncall();
	} else {
		cpuset_t targets;
		struct task *thread;
		void *args[CPU_IPI_ARGCOUNT];
		CPUSET_CLEAR(targets);
		LLIST_FOREACH(thread, effective_vm->v_tasks, t_vm_tasks) {
			cpuid_t cid;
			cid = ATOMIC_READ(thread->t_cpu)->c_id;
			CPUSET_INSERT(targets, cid);
		}
		args[0] = (void *)effective_vm;
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb_all_for,
		                   args,
		                   CPU_IPI_FWAITFOR);
	}
}



/* Begin/end syncing page directory mappings:
 * >> pagedir_prepare_map_p(my_vm, start, count);                       // Prepare      (make sure that `pagedir_unmap_p()' will succeed)
 * >> vm_sync_begin(my_vm);                                             // Lock         (make sure we'll be able to sync)
 * >> pagedir_unmap_p(PAGEDIR_P_SELFOFVM(my_vm), start, count);         // Unmap        (Actually delete page mappings)
 * >> vm_sync_end(my_vm, start, count);                                 // Unlock+sync  (Make sure that all CPUs got the message about pages having gone away)
 * >> pagedir_unprepare_map_p(PAGEDIR_P_SELFOFVM(my_vm), start, count); // Free         (Clean up memory used to describe the mapping)
 * This order to calls is required to prevent problems at a
 * point in time when those problems could no longer be handled,
 * since the regular vm_sync() functions may throw an E_WOULDBLOCK
 * exception when failing to acquire a lock to `v_tasklock', which
 * is required in order to gather the set of CPUs containing tasks
 * which may need to be synced as well. */
PUBLIC ATTR_FLATTEN NOBLOCK void
NOTHROW(FCALL vm_sync_end)(struct vm *__restrict effective_vm,
                           vm_vpage_t page_index, size_t num_pages) {
	vm_sync_locked(effective_vm, page_index, num_pages);
	vm_tasklock_endread(effective_vm);
}

PUBLIC ATTR_FLATTEN NOBLOCK void
NOTHROW(FCALL vm_sync_endone)(struct vm *__restrict effective_vm,
                              vm_vpage_t page_index) {
	vm_syncone_locked(effective_vm, page_index);
	vm_tasklock_endread(effective_vm);
}

PUBLIC ATTR_FLATTEN NOBLOCK void
NOTHROW(FCALL vm_sync_endall)(struct vm *__restrict effective_vm) {
	vm_syncall_locked(effective_vm);
	vm_tasklock_endread(effective_vm);
}

#else /* !CONFIG_NO_SMP */

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_sync)(struct vm *__restrict effective_vm,
                       vm_vpage_t page_index, size_t num_pages) {
	if (effective_vm == THIS_VM ||
	    effective_vm == &vm_kernel)
		pagedir_sync(page_index, num_pages);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_syncone)(struct vm *__restrict effective_vm,
                          vm_vpage_t page_index) {
	if (effective_vm == THIS_VM ||
	    effective_vm == &vm_kernel)
		pagedir_syncone(page_index);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_syncall)(struct vm *__restrict effective_vm) {
	if (effective_vm == THIS_VM ||
	    effective_vm == &vm_kernel)
		pagedir_syncall();
}

DEFINE_PUBLIC_ALIAS(vm_sync_end, vm_sync);
DEFINE_PUBLIC_ALIAS(vm_sync_endone, vm_syncone);
DEFINE_PUBLIC_ALIAS(vm_sync_endall, vm_syncall);
DEFINE_PUBLIC_ALIAS(vm_sync_locked, vm_sync);
DEFINE_PUBLIC_ALIAS(vm_syncone_locked, vm_syncone);
DEFINE_PUBLIC_ALIAS(vm_syncall_locked, vm_syncall);

#endif /* CONFIG_NO_SMP */



/* Similar to the user-variants above, however sync a kernel-VM range instead,
 * and causing the did-change RPC to be broadcast to _all_ CPUs, instead of
 * having to figure out the specific sub-set of CPUs that would be affected. */
PUBLIC NOBLOCK void
NOTHROW(FCALL vm_kernel_sync)(vm_vpage_t page_index, size_t num_pages) {
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)(uintptr_t)page_index;
		args[1] = (void *)(uintptr_t)num_pages;
		cpu_broadcastipi(&ipi_invtlb, args, CPU_IPI_FWAITFOR);
	}
#else /* !CONFIG_NO_SMP */
	pagedir_sync(page_index, num_pages);
#endif /* CONFIG_NO_SMP */
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_kernel_syncone)(vm_vpage_t page_index) {
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)(uintptr_t)page_index;
		cpu_broadcastipi(&ipi_invtlb_one, args, CPU_IPI_FWAITFOR);
	}
#else /* !CONFIG_NO_SMP */
	pagedir_syncone(page_index);
#endif /* CONFIG_NO_SMP */
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_kernel_syncall)(void) {
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
		cpu_broadcastipi(&ipi_invtlb_all, args, CPU_IPI_FWAITFOR);
	}
#else /* !CONFIG_NO_SMP */
	pagedir_syncall();
#endif /* CONFIG_NO_SMP */
}


DECL_END

#ifndef __INTELLISENSE__
#include "vm-unmap-kernel-ram.c.inl"
#include "vm-service-tasklock.c.inl"
#endif

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_C */
