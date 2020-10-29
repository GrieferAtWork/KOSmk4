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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_C
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/hook.h>
#include <debugger/rt.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <kernel/swap.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>
#include <kernel/vm/phys.h>
#include <sched/cpu.h>
#include <sched/pid.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <alloca.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>

#include <libvio/api.h>

#include "../corebase.h"
#include "vm-nodeapi.h"

#define POINTER_SET_BUFSIZE 4
#include <misc/pointer-set.h>

/* Implement the ABI for the address tree used by vm. */
#define ATREE(x)                 vm_nodetree_##x
#define ATREE_FUN                INTDEF
#define ATREE_IMP                INTERN
#define ATREE_CALL               KCALL
#define ATREE_NOTHROW            NOTHROW
#define Tkey                     pageid_t
#define T                        struct vm_node
#define N_NODEPATH               vn_node
#define ATREE_LOCAL_SEMI0(Tkey)  VM_SEMI0
#define ATREE_LOCAL_LEVEL0(Tkey) VM_LEVEL0
#define ATREE_IMPLEMENTATION_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_IMPLEMENTATION_ONLY

/* Implement the ABI for the address tree used by vm. */
#define ATREE(x)      vm_parttree_##x
#define ATREE_FUN     INTDEF
#define ATREE_IMP     INTERN
#define ATREE_CALL    KCALL
#define ATREE_NOTHROW NOTHROW
#define Tkey          datapage_t
#define T             struct vm_datapart
#define N_NODEPATH    dp_tree
#define ATREE_IMPLEMENTATION_ONLY 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_IMPLEMENTATION_ONLY


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

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_futextree_clear_part_pointers)(struct vm_futex *__restrict self) {
again:
	self->f_part.clear();
	if (self->f_tree.a_min) {
		if (self->f_tree.a_max)
			vm_futextree_clear_part_pointers(self->f_tree.a_max);
		self = self->f_tree.a_min;
		goto again;
	}
	if (self->f_tree.a_max) {
		self = self->f_tree.a_max;
		goto again;
	}
}

/* Delete the `f_part' pointers of all `struct vm_futex' objects
 * that can still be reached from the given address tree. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_futex_controller_destroy)(struct vm_futex_controller *__restrict self) {
	/* Clear part pointers */
	if (self->fc_tree)
		vm_futextree_clear_part_pointers(self->fc_tree);
	/* Free the controller object. */
	vm_futex_controller_free(self);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_destroy)(struct vm_datapart *__restrict self,
                                   bool is_zero) {
	assert(!sync_writing(self));
	assert(!sync_reading(self));
	assert(!self->dp_crefs);
	assert(!self->dp_srefs);
	assert(!self->dp_stale);
	shared_rwlock_broadcast_for_fini(&self->dp_lock);
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
	/* Destroy any associated futex controller (if one still exists) */
	if (self->dp_futex)
		vm_futex_controller_destroy(self->dp_futex);
	if (self->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
		kfree(self->dp_pprop_p);
	xdecref(self->dp_block); /* May be NULL due to incomplete initialization... */
	vm_datapart_free(self);
}

/* (possibly) delete the futex controller of `self' if it is no longer in use. */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_maybe_delete_futex_controller)(struct vm_datapart *__restrict self);

#define VM_DATAPART_MUST_SERVICE_STALE(self)  \
	(ATOMIC_READ((self)->dp_stale) != NULL || \
	 (self->dp_futex && ATOMIC_READ((self)->dp_futex->fc_dead) != NULL))

PRIVATE NOBLOCK void
NOTHROW(KCALL vm_datapart_service_stale)(struct vm_datapart *__restrict self) {
	struct vm_node *chain, *next;
	struct vm_futex_controller *fc;
	chain = ATOMIC_XCH(self->dp_stale, NULL);
	while (chain) {
		next = chain->vn_byaddr.ln_next;
		assert(chain->vn_part == self);
		LLIST_REMOVE(chain, vn_link);
		weakdecref(chain->vn_vm); /* `weakincref()' in `vm_node_destroy()' */
		/*decref_nokill(self); // The reference to `vn_part' was already dropped! (s.a. `vm_node_destroy()') */
		vm_node_free(chain);
		chain = next;
	}
	if ((fc = self->dp_futex) != NULL) {
		/* Also check for servicing dead futex objects. */
		struct vm_futex *dead, *next;
		dead = ATOMIC_XCH(fc->fc_dead, NULL);
		if (dead) {
			while (dead) {
				next = dead->f_ndead;
#ifdef NDEBUG
				vm_futextree_remove(&fc->fc_tree, dead->f_tree.a_vaddr,
				                    fc->fc_semi0, fc->fc_leve0);
#else /* NDEBUG */
				{
					struct vm_futex *removed;
					removed = vm_futextree_remove_at(&fc->fc_tree,
					                                 dead->f_tree.a_vaddr,
					                                 fc->fc_semi0,
					                                 fc->fc_leve0);
					assertf(removed == dead, "%p != %p (addr: %p)",
					        removed, dead, dead->f_tree.a_vaddr);
				}
#endif /* !NDEBUG */
				vm_futex_free(dead);
				dead = next;
			}
			/* Check if we should (possibly) delete the futex controller. */
			vm_datapart_maybe_delete_futex_controller(self);
		}
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

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
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

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vm_datapart_lock_trywrite)(struct vm_datapart *__restrict self) {
	bool result;
	result = sync_trywrite(&self->dp_lock);
	if (result)
		vm_datapart_service_stale(self);
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
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
 *                          `pointer_set_clear_and_rehash(vms,return)' to
 *                           allocate sufficient memory with the given
 *                           buffer, before re-attempting the call. */
PRIVATE NOBLOCK size_t
NOTHROW(KCALL vm_set_collect_from_datapart)(struct pointer_set *__restrict vms,
                                            struct vm_datapart *__restrict self) {
	struct vm_node *iter;
	size_t result = 0;
	unsigned int i;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	assert(vms->ps_size == 0);
	for (i = 0; i < 2; ++i) {
		for (iter       = i ? self->dp_srefs : self->dp_crefs;
		     iter; iter = iter->vn_link.ln_next) {
			int error;
			REF struct vm *v = iter->vn_vm;
			assert((i ? (iter->vn_prot & VM_PROT_SHARED)
			          : !(iter->vn_prot & VM_PROT_SHARED)) ||
			       wasdestroyed(v));
			if unlikely(!tryincref(v))
				continue; /* Dead VM (associated with an node that has become stale.) */
			error = pointer_set_insert_nx(vms,
			                              v, /* Inherit reference */
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
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
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
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
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
		while (i) {
			--i;
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



LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
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
                                   PAGEDIR_PAGEALIGNED VIRT void *addr, u16 perm) {
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		pagedir_map(addr,
		            self->dp_ramdata.rd_block0.rb_size * PAGESIZE,
		            physpage2addr(self->dp_ramdata.rd_block0.rb_start),
		            perm);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			pagedir_map(addr,
			            blocks[i].rb_size * PAGESIZE,
			            physpage2addr(blocks[i].rb_start),
			            perm);
			addr = (byte_t *)addr + blocks[i].rb_size * PAGESIZE;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_p)(struct vm_datapart *__restrict self,
                                     pagedir_phys_t pdir,
                                     PAGEDIR_PAGEALIGNED VIRT void *addr, u16 perm) {
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		pagedir_map_p(pdir,
		              addr,
		              self->dp_ramdata.rd_block0.rb_size * PAGESIZE,
		              physpage2addr(self->dp_ramdata.rd_block0.rb_start),
		              perm);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			pagedir_map_p(pdir,
			              addr,
			              blocks[i].rb_size * PAGESIZE,
			              physpage2addr(blocks[i].rb_start),
			              perm);
			addr = (byte_t *)addr + blocks[i].rb_size * PAGESIZE;
		}
	}
}


LOCAL NOBLOCK ATTR_PURE WUNUSED u16
NOTHROW(KCALL vm_datapart_get_page_permissions)(struct vm_datapart const *__restrict self,
                                                size_t vpage_offset, u16 perm) {
	uintptr_t mode;
	unsigned int shift;
	shift = VM_DATABLOCK_PAGESHIFT(self->dp_block);
	if (shift == 0) {
		mode = vm_datapart_getstate(self, vpage_offset);
		if (mode == VM_DATAPART_PPP_HASCHANGED)
			;
		else if (mode == VM_DATAPART_PPP_INITIALIZED) {
			if (self->dp_flags & VM_DATAPART_FLAG_TRKCHNG)
				perm &= ~PAGEDIR_MAP_FWRITE; /* Delete write, so we can track changes */
		} else                               /*if (mode == VM_DATAPART_PPP_UNINITIALIZED)*/
			perm &= ~(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC);
	} else {
		size_t i, start_offset;
		size_t count = (size_t)1 << shift;
		start_offset = vpage_offset << shift;
		for (i = 0; i < count; ++i) {
			mode = vm_datapart_getstate(self, start_offset + i);
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
                                            PAGEDIR_PAGEALIGNED VIRT void *addr,
                                            u16 perm) {
	size_t start_offset, vpage_offset, count;
	u16 use_perm, new_perm;
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		vpage_offset = 0;
		count  = self->dp_ramdata.rd_block0.rb_size;
		do {
			start_offset = vpage_offset;
			use_perm     = vm_datapart_get_page_permissions(self, vpage_offset, perm);
			for (++vpage_offset; vpage_offset < count; ++vpage_offset) {
				new_perm = vm_datapart_get_page_permissions(self, vpage_offset, perm);
				if (new_perm != use_perm)
					break;
			}
			pagedir_map((byte_t *)addr + (start_offset * PAGESIZE),
			            (vpage_offset - start_offset) * PAGESIZE,
			            physpage2addr(self->dp_ramdata.rd_block0.rb_start + start_offset),
			            use_perm);
		} while (vpage_offset < count);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		vpage_offset = 0;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			count = blocks[i].rb_size;
			do {
				start_offset = vpage_offset;
				use_perm     = vm_datapart_get_page_permissions(self, vpage_offset, perm);
				for (++vpage_offset; vpage_offset < count; ++vpage_offset) {
					new_perm = vm_datapart_get_page_permissions(self, vpage_offset, perm);
					if (new_perm != use_perm)
						break;
				}
				pagedir_map((byte_t *)addr + (start_offset * PAGESIZE),
				            (vpage_offset - start_offset) * PAGESIZE,
				            physpage2addr(blocks[i].rb_start + start_offset),
				            use_perm);
			} while (vpage_offset < count);
			assert(vpage_offset == count);
			assert(count == blocks[i].rb_size);
			addr = (byte_t *)addr + count * PAGESIZE;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_autoprop_p)(struct vm_datapart *__restrict self,
                                              pagedir_phys_t pdir,
                                              PAGEDIR_PAGEALIGNED VIRT void *addr,
                                              u16 perm) {
	size_t start_offset, vpage_offset, count;
	u16 use_perm, new_perm;
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		assert(vm_datapart_numvpages(self) == self->dp_ramdata.rd_block0.rb_size);
		vpage_offset = 0;
		count  = self->dp_ramdata.rd_block0.rb_size;
		do {
			start_offset = vpage_offset;
			use_perm     = vm_datapart_get_page_permissions(self, vpage_offset, perm);
			for (++vpage_offset; vpage_offset < count; ++vpage_offset) {
				new_perm = vm_datapart_get_page_permissions(self, vpage_offset, perm);
				if (new_perm != use_perm)
					break;
			}
			pagedir_map_p(pdir,
			              (byte_t *)addr + (start_offset * PAGESIZE),
			              (vpage_offset - start_offset) * PAGESIZE,
			              physpage2addr(self->dp_ramdata.rd_block0.rb_start + start_offset),
			              use_perm);
		} while (vpage_offset < count);
	} else {
		size_t i;
		struct vm_ramblock *blocks;
		vpage_offset = 0;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0; i < self->dp_ramdata.rd_blockc; ++i) {
			count = blocks[i].rb_size;
			do {
				start_offset = vpage_offset;
				use_perm     = vm_datapart_get_page_permissions(self, vpage_offset, perm);
				for (++vpage_offset; vpage_offset < count; ++vpage_offset) {
					new_perm = vm_datapart_get_page_permissions(self, vpage_offset, perm);
					if (new_perm != use_perm)
						break;
				}
				pagedir_map_p(pdir,
				              (byte_t *)addr + (start_offset * PAGESIZE),
				              (vpage_offset - start_offset) * PAGESIZE,
				              physpage2addr(blocks[i].rb_start + start_offset),
				              use_perm);
			} while (vpage_offset < count);
			assert(vpage_offset == count);
			assert(count == blocks[i].rb_size);
			addr = (byte_t *)addr + count * PAGESIZE;
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
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	assert(num_bytes != 0);
	assert(partrel_start + num_bytes > partrel_start);
	assert(partrel_start + num_bytes <= vm_datapart_numbytes(self));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	assert(lock->dl_part == self);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		/* Simple case: Single-block ram data. */
		(*prange)(arg,
		          physpage2addr(self->dp_ramdata.rd_block0.rb_start) + partrel_start,
		          num_bytes,
		          lock);
	} else {
		size_t i, count, blocksize;
		struct vm_ramblock *blocks;
		count  = self->dp_ramdata.rd_blockc;
		blocks = self->dp_ramdata.rd_blockv;
		for (i = 0;; ++i) {
			assert(i < count);
			blocksize = blocks[i].rb_size * PAGESIZE;
			if (partrel_start < blocksize)
				break;
			partrel_start -= blocksize;
		}
		blocksize -= partrel_start;
		for (;;) {
			size_t copysize = num_bytes;
			if (copysize > blocksize)
				copysize = blocksize;
			(*prange)(arg,
			          physpage2addr(blocks[i].rb_start) + partrel_start,
			          copysize,
			          lock);
			if (copysize >= num_bytes)
				break;
			num_bytes -= copysize;
			++i;
			assert(i < count);
			blocksize     = blocks[i].rb_size * PAGESIZE;
			partrel_start = 0;
		}
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_insert_ignore_missmatch)(struct vm_node *__restrict self) {
	struct vm_node **pinsert, *insert_before;
	struct vm *v = self->vn_vm;
	assert(v);
	assertf(vm_node_getminpageid(self) <= vm_node_getmaxpageid(self),
	        "Unordered node: MIN(%p) >= MAX(%p)",
	        vm_node_getmin(self), vm_node_getmax(self));
	assertf(vm_node_getmaxpageid(self) <= __ARCH_PAGEID_MAX,
	        "Mapping of node covering pages %p-%p is out-of-bounds",
	        vm_node_getminpageid(self), vm_node_getmaxpageid(self));
	assert(self->vn_block ? true : !self->vn_part);
#if 0
	assertf(!self->vn_part ||
	        vm_node_getpagecount(self) == vm_datapart_numvpages(self->vn_part),
	        "Node size missmatch (%" PRIuSIZ " != %" PRIuSIZ ")",
	        vm_node_getpagecount(self), vm_datapart_numvpages(self->vn_part));
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
	        "insert_before  = %p (%p-%p)\n"
	        "self           = %p (%p-%p)\n"
	        "self->vn_flags = %#x\n",
	        insert_before,
	        vm_node_getmin(insert_before),
	        vm_node_getmax(insert_before),
	        self,
	        vm_node_getmin(self),
	        vm_node_getmax(self),
	        (unsigned int)self->vn_flags);
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
/**/
#include "vm-datapart-split.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */

/* Free RAM allocated by `vm_do_allocram(_nx)'
 * NOTE: This function assumes that the allocated memory hasn't been used, yet. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
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

PUBLIC NOBLOCK NONNULL((1, 2)) void
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

PUBLIC NOBLOCK NONNULL((1, 2)) void
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
	        "dst->dp_state = %" PRIuSIZ "", (uintptr_t)dst->dp_state);
	assertf(src->dp_state == VM_DATAPART_STATE_INCORE ||
	        src->dp_state == VM_DATAPART_STATE_LOCKED,
	        "src->dp_state = %" PRIuSIZ "", (uintptr_t)src->dp_state);
	assertf(vm_datapart_numvpages(dst) == vm_datapart_numvpages(src),
	        "vm_datapart_numvpages(dst) = %" PRIuSIZ "\n"
	        "vm_datapart_numvpages(src) = %" PRIuSIZ "\n",
	        vm_datapart_numvpages(dst),
	        vm_datapart_numvpages(src));
	if (src->dp_ramdata.rd_blockv == &src->dp_ramdata.rd_block0) {
		if (dst->dp_ramdata.rd_blockv == &dst->dp_ramdata.rd_block0) {
			/* SINGLE --> SINGLE */
			assert(dst->dp_ramdata.rd_block0.rb_size ==
			       src->dp_ramdata.rd_block0.rb_size);
			vm_copypagesinphys(physpage2addr(dst->dp_ramdata.rd_block0.rb_start),
			                   physpage2addr(src->dp_ramdata.rd_block0.rb_start),
			                   src->dp_ramdata.rd_block0.rb_size);
		} else {
			/* SINGLE --> MULTIPLE */
			size_t i;
			physpage_t src_page;
			struct vm_ramblock *dst_blocks;
			src_page   = src->dp_ramdata.rd_block0.rb_start;
			dst_blocks = dst->dp_ramdata.rd_blockv;
			for (i = 0; i < dst->dp_ramdata.rd_blockc; ++i) {
				size_t num_pages;
				num_pages = dst_blocks[i].rb_size;
				vm_copypagesinphys(physpage2addr(dst_blocks[i].rb_start),
				                   physpage2addr(src_page),
				                   num_pages);
				src_page += num_pages;
			}
			assert(src->dp_ramdata.rd_block0.rb_start +
			       src->dp_ramdata.rd_block0.rb_size ==
			       src_page);
		}
	} else if (dst->dp_ramdata.rd_blockv == &dst->dp_ramdata.rd_block0) {
		/* MULTIPLE --> SINGLE */
		size_t i;
		physpage_t dst_page;
		struct vm_ramblock *src_blocks;
		dst_page   = dst->dp_ramdata.rd_block0.rb_start;
		src_blocks = src->dp_ramdata.rd_blockv;
		for (i = 0; i < src->dp_ramdata.rd_blockc; ++i) {
			size_t num_pages;
			num_pages = src_blocks[i].rb_size;
			vm_copypagesinphys(physpage2addr(dst_page),
			                   physpage2addr(src_blocks[i].rb_start),
			                   num_pages);
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
				size_t pagecount = b.rb_size;
				if (!src_block.rb_size) {
					assert(src_i < src->dp_ramdata.rd_blockc);
					src_block = src_blocks[src_i++];
				}
				assert(src_block.rb_size != 0);
				if (pagecount > src_block.rb_size)
					pagecount = src_block.rb_size;
				vm_copypagesinphys(physpage2addr(b.rb_start),
				                   physpage2addr(src_block.rb_start),
				                   pagecount);
				src_block.rb_start += pagecount;
				src_block.rb_size -= pagecount;
				b.rb_start += pagecount;
				b.rb_size -= pagecount;
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
#else /* __INTELLISENSE__ */
DECL_END

#define EXLOCK_NX 1
#include "vm-datapart-exlock.c.inl"
/**/
#include "vm-datapart-exlock.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */


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
PUBLIC NOBLOCK NONNULL((1)) physpage_t
NOTHROW(KCALL vm_datapart_pageaddr)(struct vm_datapart *__restrict self,
                                    size_t vpage_offset) {
	physpage_t result;
	assertf(vpage_offset < vm_datapart_numvpages(self),
	        "vpage_offset                = %" PRIuSIZ "\n"
	        "vm_datapart_numvpages(self) = %" PRIuSIZ "\n",
	        vpage_offset, vm_datapart_numvpages(self));
	assertf(self->dp_ramdata.rd_blockv,
	        "Unset `rd_blockv' in datapart at %p",
	        self);
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
PUBLIC NONNULL((1, 3)) physpage_t KCALL
vm_datapart_loadpage(struct vm_datapart *__restrict self,
                     size_t vpage_offset,
                     bool *__restrict pchanged)
		THROWS(...) {
	unsigned int page_shift;
	physpage_t result;
	uintptr_t page_state;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	assertf(self->dp_state == VM_DATAPART_STATE_INCORE ||
	        self->dp_state == VM_DATAPART_STATE_LOCKED,
	        "self->dp_state = %" PRIuPTR,
	        (uintptr_t)self->dp_state);
	assertf(vpage_offset < vm_datapart_numvpages(self),
	        "vpage_offset                = %" PRIuSIZ "\n"
	        "vm_datapart_numvpages(self) = %" PRIuSIZ "\n",
	        vpage_offset, vm_datapart_numvpages(self));
	/* Figure out the address of the associated physical memory page. */
	result     = vm_datapart_pageaddr(self, vpage_offset);
	page_shift = VM_DATABLOCK_PAGESHIFT(self->dp_block);
	if (page_shift == 0) {
		/* No page shift --> Only a single bit to check/modify */
again_readstate:
		page_state = vm_datapart_getstate(self, vpage_offset);
		switch (page_state) {

		case VM_DATAPART_PPP_UNINITIALIZED:
			/* It seems to fall upon us to initialize this page! */
			if (!vm_datapart_cmpxchstate(self,
			                             vpage_offset,
			                             VM_DATAPART_PPP_UNINITIALIZED,
			                             VM_DATAPART_PPP_INITIALIZING))
				goto again_readstate;
			TRY {
				void (KCALL *dt_loadpart)(struct vm_datablock *__restrict,
				                          datapage_t, physaddr_t, size_t);
				/* Invoke a custom load protocol of the associated datablock. */
				dt_loadpart = self->dp_block->db_type->dt_loadpart;
				if likely(dt_loadpart) {
					assert(!wasdestroyed(self));
					(*dt_loadpart)(self->dp_block,
					               vm_datapart_startdpage(self) + vpage_offset,
					               physpage2addr(result),
					               1);
					assert(!wasdestroyed(self));
				}
			} EXCEPT {
				vm_datapart_setstate(self,
				                     vpage_offset,
				                     VM_DATAPART_PPP_UNINITIALIZED);
				RETHROW();
			}
			/* Update the part's state to either indicate change, or full initialization */
			if (*pchanged) {
				vm_datapart_setstate(self,
				                     vpage_offset,
				                     VM_DATAPART_PPP_HASCHANGED);
				goto set_datapart_changed;
			}
			vm_datapart_setstate(self,
			                     vpage_offset,
			                     VM_DATAPART_PPP_INITIALIZED);
			break;

		case VM_DATAPART_PPP_INITIALIZING:
			/* Wait for the initialization to be completed. */
			task_tryyield_or_pause();
			goto again_readstate;

		case VM_DATAPART_PPP_INITIALIZED:
			if (*pchanged) {
				if (!vm_datapart_cmpxchstate(self,
				                             vpage_offset,
				                             VM_DATAPART_PPP_INITIALIZED,
				                             VM_DATAPART_PPP_HASCHANGED))
					goto again_readstate;
set_datapart_changed:
				if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) & VM_DATAPART_FLAG_CHANGED)) {
					void (KCALL *dt_changed)(struct vm_datablock *__restrict,
					                         struct vm_datapart *__restrict);
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
		size_t pagemask, starting_data_page;
		unsigned int n_data_pages, addrshift;
		bool result_has_changed = false;
		pagemask                = VM_DATABLOCK_PAGEMASK(self->dp_block);
		addrshift               = VM_DATABLOCK_ADDRSHIFT(self->dp_block);
		starting_data_page      = vpage_offset << page_shift;
		n_data_pages            = 1 << page_shift;
		for (; n_data_pages; --n_data_pages, ++starting_data_page) {
again_readstate_multi:
			page_state = vm_datapart_getstate(self, starting_data_page);
			switch (page_state) {

			case VM_DATAPART_PPP_UNINITIALIZED: {
				unsigned int i, num_init_pages;
				/* Try to initialize multiple consecutive parts all at once! */
				if (!vm_datapart_cmpxchstate(self,
				                             starting_data_page,
				                             VM_DATAPART_PPP_UNINITIALIZED,
				                             VM_DATAPART_PPP_INITIALIZING))
					goto again_readstate_multi;
				num_init_pages = 1;
				assertf(starting_data_page < vm_datapart_numdpages(self),
				        "starting_data_page          = %" PRIuPTR "\n"
				        "vm_datapart_numdpages(self) = %" PRIuSIZ "\n",
				        starting_data_page, vm_datapart_numdpages(self));
				assertf((starting_data_page + n_data_pages) <= vm_datapart_numdpages(self),
				        "starting_data_page          = %" PRIuPTR "\n"
				        "n_data_pages                = %u\n"
				        "vm_datapart_numdpages(self) = %" PRIuSIZ "\n",
				        starting_data_page, n_data_pages, vm_datapart_numdpages(self));
				while (num_init_pages < n_data_pages &&
				       vm_datapart_cmpxchstate(self,
				                               starting_data_page + num_init_pages,
				                               VM_DATAPART_PPP_UNINITIALIZED,
				                               VM_DATAPART_PPP_INITIALIZING))
					++num_init_pages;
				TRY {
					void (KCALL *dt_loadpart)(struct vm_datablock *__restrict,
					                          datapage_t, physaddr_t, size_t);
					/* Invoke a custom load protocol of the associated datablock. */
					dt_loadpart = self->dp_block->db_type->dt_loadpart;
					if likely(dt_loadpart) {
						assert(!wasdestroyed(self));
						(*dt_loadpart)(self->dp_block,
						               vm_datapart_startdpage(self) + starting_data_page,
						               physpage2addr(result) + ((uintptr_t)(starting_data_page & pagemask) << addrshift),
						               num_init_pages);
						assert(!wasdestroyed(self));
					}
				} EXCEPT {
					for (i = 0; i < num_init_pages; ++i) {
						vm_datapart_setstate(self,
						                     starting_data_page + i,
						                     VM_DATAPART_PPP_UNINITIALIZED);
					}
					RETHROW();
				}
				if (*pchanged) {
					for (i = 0; i < num_init_pages; ++i) {
						vm_datapart_setstate(self,
						                     starting_data_page + i,
						                     VM_DATAPART_PPP_HASCHANGED);
					}
					result_has_changed = true;
					if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) &
					      VM_DATAPART_FLAG_CHANGED)) {
						void (KCALL *dt_changed)(struct vm_datablock *__restrict,
						                         struct vm_datapart *__restrict);
						dt_changed = self->dp_block->db_type->dt_changed;
						if (dt_changed)
							(*dt_changed)(self->dp_block, self);
					}
				} else {
					for (i = 0; i < num_init_pages; ++i) {
						vm_datapart_setstate(self,
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
				goto again_readstate_multi;

			case VM_DATAPART_PPP_HASCHANGED:
				result_has_changed = true;
				break;

			case VM_DATAPART_PPP_INITIALIZED:
				if (*pchanged) {
					if (!vm_datapart_cmpxchstate(self,
					                             starting_data_page,
					                             VM_DATAPART_PPP_INITIALIZED,
					                             VM_DATAPART_PPP_HASCHANGED))
						goto again_readstate_multi;
					result_has_changed = true;
					if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) &
					      VM_DATAPART_FLAG_CHANGED)) {
						void (KCALL *dt_changed)(struct vm_datablock *__restrict,
						                         struct vm_datapart *__restrict);
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
PUBLIC NONNULL((1)) physaddr_t KCALL
vm_datapart_loaddatapage(struct vm_datapart *__restrict self,
                         size_t dpage_offset, bool for_writing)
		THROWS(...) {
	struct vm_datablock *block;
	physaddr_t result;
	uintptr_t page_state;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	assertf(dpage_offset < vm_datapart_numdpages(self),
	        "dpage_offset                = %" PRIuSIZ "\n"
	        "vm_datapart_numdpages(self) = %" PRIuSIZ "\n",
	        dpage_offset,
	        vm_datapart_numvpages(self));
	/* Figure out the address of the associated physical memory page. */
	block  = self->dp_block;
	result = (physaddr_t)vm_datapart_pageaddr(self,
	                                         (size_t)(dpage_offset >> VM_DATABLOCK_PAGESHIFT(block))) *
	         PAGESIZE;
	result += (uintptr_t)(dpage_offset & VM_DATABLOCK_PAGEMASK(block)) << VM_DATABLOCK_ADDRSHIFT(block);
again_readstate:
	page_state = vm_datapart_getstate(self, dpage_offset);
	switch (page_state) {

	case VM_DATAPART_PPP_UNINITIALIZED:
		/* It seems to fall upon us to initialize this page! */
		if (!vm_datapart_cmpxchstate(self,
		                             dpage_offset,
		                             VM_DATAPART_PPP_UNINITIALIZED,
		                             VM_DATAPART_PPP_INITIALIZING))
			goto again_readstate;
		TRY {
			void (KCALL *dt_loadpart)(struct vm_datablock *__restrict,
			                          datapage_t, physaddr_t, size_t);
			/* Invoke a custom load protocol of the associated datablock. */
			dt_loadpart = block->db_type->dt_loadpart;
			if (dt_loadpart) {
				(*dt_loadpart)(block,
				               vm_datapart_startdpage(self) + dpage_offset,
				               result,
				               1);
			}
		} EXCEPT {
			vm_datapart_setstate(self,
			                     dpage_offset,
			                     VM_DATAPART_PPP_UNINITIALIZED);
			RETHROW();
		}
		/* Update the part's state to either indicate change, or full initialization */
		if (for_writing) {
			vm_datapart_setstate(self,
			                     dpage_offset,
			                     VM_DATAPART_PPP_HASCHANGED);
			goto set_datapart_changed;
		}
		vm_datapart_setstate(self,
		                     dpage_offset,
		                     VM_DATAPART_PPP_INITIALIZED);
		break;

	case VM_DATAPART_PPP_INITIALIZING:
		/* Wait for the initialization to be completed. */
		task_tryyield_or_pause();
		goto again_readstate;

	case VM_DATAPART_PPP_INITIALIZED:
		if (for_writing) {
			if (!vm_datapart_cmpxchstate(self,
			                             dpage_offset,
			                             VM_DATAPART_PPP_INITIALIZED,
			                             VM_DATAPART_PPP_HASCHANGED))
				goto again_readstate;
set_datapart_changed:
			if (!(ATOMIC_FETCHOR(self->dp_flags, VM_DATAPART_FLAG_CHANGED) &
			      VM_DATAPART_FLAG_CHANGED)) {
				void (KCALL *dt_changed)(struct vm_datablock *__restrict,
				                         struct vm_datapart *__restrict);
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
/**/
#include "vm-dma.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */

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
	if unlikely(!sync_trywrite(self))
		return self;
	if (self->dp_tree.a_min) {
		result = vm_datablock_lock_trywrite_parts(self->dp_tree.a_min);
		if unlikely(result)
			goto err_self;
	}
	if (self->dp_tree.a_max) {
		result = vm_datablock_lock_trywrite_parts(self->dp_tree.a_max);
		if unlikely(result) {
			if (self->dp_tree.a_min)
				vm_datablock_lock_endwrite_parts(self->dp_tree.a_min);
			goto err_self;
		}
	}
	return NULL;
err_self:
	sync_endwrite(self);
	return result; /* Propagate faulting part. */
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
#ifdef LIBVIO_CONFIG_ENABLED
	/* Unset VIO parts! */
	assert((self->dp_state == VM_DATAPART_STATE_VIOPRT) ==
	       (block->db_vio != NULL));
	if (self->dp_state == VM_DATAPART_STATE_VIOPRT)
		self->dp_state = VM_DATAPART_STATE_ABSENT;
#endif /* LIBVIO_CONFIG_ENABLED */
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
                                      size_t partrel_min_dpage,
                                      size_t partrel_max_dpage) {
	size_t i;
	assert(partrel_min_dpage <= partrel_max_dpage);
	assert(partrel_max_dpage < vm_datapart_numdpages(self));
	for (i = partrel_min_dpage; i <= partrel_max_dpage; ++i) {
		uintptr_t state;
		state = vm_datapart_getstate(self, i);
		if (state == VM_DATAPART_PPP_HASCHANGED)
			return true;
	}
	return false;
}



PRIVATE NOBLOCK NONNULL((1)) struct vm_datapart *
NOTHROW(KCALL vm_datablock_findchanged)(struct vm_datapart *__restrict tree,
                                        datapage_t minpage, datapage_t maxpage,
                                        size_t *__restrict ppartrel_minpage,
                                        size_t *__restrict ppartrel_maxpage,
                                        ATREE_SEMI_T(datapage_t) addr_semi,
                                        ATREE_LEVEL_T addr_level) {
again:
	if ((ATOMIC_READ(tree->dp_flags) & VM_DATAPART_FLAG_CHANGED) &&
	    minpage <= vm_datapart_maxdpage(tree) &&
	    maxpage >= vm_datapart_mindpage(tree)) {
		size_t partrel_minpage, partrel_maxpage;
		/* Check this one. */
		if (minpage <= vm_datapart_mindpage(tree) &&
		    maxpage >= vm_datapart_maxdpage(tree)) {
			/* There ought to have been some changes made to this part! */
			partrel_minpage = 0;
			partrel_maxpage = vm_datapart_numdpages(tree) - 1;
		} else {
			datapage_t partmin, partmax;
			partmin = vm_datapart_mindpage(tree);
			partmax = vm_datapart_maxdpage(tree);
			if (maxpage < partmax)
				partrel_maxpage = (size_t)(maxpage - partmin);
			else {
				partrel_maxpage = vm_datapart_numdpages(tree) - 1;
			}
			if (minpage >= partmin)
				partrel_minpage = (size_t)(minpage - partmin);
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
			ATREE_SEMI_T(datapage_t)
			temp_semi                = addr_semi;
			ATREE_LEVEL_T temp_level = addr_level;
			ATREE_WALKMAX(datapage_t, temp_semi, temp_level);
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
		ATREE_WALKMIN(datapage_t, addr_semi, addr_level);
		tree = tree->dp_tree.a_min;
		goto again;
	} else if (maxpage >= addr_semi && tree->dp_tree.a_max) {
		/* Recursively continue searching right. */
		ATREE_WALKMAX(datapage_t, addr_semi, addr_level);
		tree = tree->dp_tree.a_max;
		goto again;
	}
	return NULL;
}


LOCAL NONNULL((1)) void KCALL
vm_datapart_do_savepart(struct vm_datapart *__restrict self, struct vm_datablock *__restrict block,
                        NONNULL((1)) void(KCALL *dt_savepart)(struct vm_datablock *__restrict,
                                                              datapage_t, physaddr_t, size_t),
                        size_t partrel_min_dpage, size_t partrel_num_dpage)
		THROWS(...) {
	unsigned int addrshift;
	assert(dt_savepart == block->db_type->dt_savepart);
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	addrshift = VM_DATABLOCK_ADDRSHIFT(block);
	if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
		(*dt_savepart)(block,
		               vm_datapart_mindpage(self) + partrel_min_dpage,
		               physpage2addr(self->dp_ramdata.rd_block0.rb_start) +
		               ((physaddr_t)partrel_min_dpage << addrshift),
		               partrel_num_dpage);
	} else {
		size_t i, dpage_pos = partrel_min_dpage;
		struct vm_ramblock *blocks = self->dp_ramdata.rd_blockv;
		for (i = 0;; ++i) {
			size_t block_dpages;
			assert(i < self->dp_ramdata.rd_blockc);
			block_dpages = blocks[i].rb_size << VM_DATABLOCK_PAGESHIFT(block);
			if (partrel_min_dpage <= block_dpages)
				break;
			partrel_min_dpage -= (size_t)block_dpages;
		}
		while (partrel_num_dpage) {
			size_t block_dpages;
			assert(i < self->dp_ramdata.rd_blockc);
			block_dpages = blocks[i].rb_size << VM_DATABLOCK_PAGESHIFT(block);
			block_dpages -= partrel_min_dpage;
			if (block_dpages > partrel_num_dpage)
				block_dpages = partrel_num_dpage;
			(*dt_savepart)(block,
			               vm_datapart_mindpage(self) + dpage_pos,
			               physpage2addr(blocks[i].rb_start) +
			               ((physaddr_t)partrel_min_dpage << addrshift),
			               (size_t)block_dpages); /* XXX: Overflow? */
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
 *                                       NOTE: This is merely a hint, and only affects the
 *                                             performance of this function. - It is ignored
 *                                             when no SHARED memory mappings exist, and should
 *                                             only be set to TRUE when the caller hasn't already
 *                                             been told in one way or another that there
 *                                             probably are changed pages within the given range.
 * @return: * : The number of saved data pages. */
PUBLIC NONNULL((1)) size_t KCALL
vm_datapart_sync(struct vm_datapart *__restrict self,
                 size_t partrel_min_dpage,
                 size_t partrel_max_dpage,
                 bool recheck_modifications_before_remap)
		THROWS(E_WOULDBLOCK, ...) {
	struct vm_datablock *block;
	size_t result = 0;
	struct pointer_set vms;
#ifdef LIBVIO_CONFIG_ENABLED
	if unlikely(ATOMIC_READ(self->dp_state) == VM_DATAPART_STATE_VIOPRT)
		goto done_return_now;
#endif /* LIBVIO_CONFIG_ENABLED */
	pointer_set_init(&vms);
again_lock_datapart:
	TRY {
		void (KCALL *dt_savepart)(struct vm_datablock *__restrict,
		                          datapage_t, physaddr_t, size_t);
		size_t vms_count;
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
		if (partrel_max_dpage >= vm_datapart_numdpages(self))
			partrel_max_dpage = vm_datapart_numdpages(self) - 1;
		/* Check if the range to sync is still non-empty. */
		if unlikely(partrel_max_dpage < partrel_min_dpage)
			goto done_unlock;
		if (recheck_modifications_before_remap &&
		    self->dp_srefs != NULL) {
			if (partrel_min_dpage == 0 &&
			    partrel_max_dpage >= vm_datapart_numdpages(self))
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
			pointer_set_clear_and_rehash(&vms, vms_count, GFP_LOCKED);
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
			struct vm *myvm = THIS_VM;
			struct vm_node *node;
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
				if unlikely(!(v == myvm || vm_node_iskernelspace(node)
				              ? pagedir_prepare_map(vm_node_getstart(node),
				                                    vm_node_getsize(node))
				              : pagedir_prepare_map_p(v->v_pdir_phys,
				                                      vm_node_getstart(node),
				                                      vm_node_getsize(node)))) {
					vm_set_lockendwrite_all(&vms);
					sync_endread(self);
					/*vm_set_clear(&vms); // Done by the EXCEPT below */
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
				}
				/* Don't propagate write permissions (those are lazily re-added during the next write-
				 * attempt, which will once again mark our part as changed once we're all set & done) */
				perm = node->vn_prot & (VM_PROT_EXEC | VM_PROT_READ);
				if (v != &vm_kernel)
					perm |= PAGEDIR_MAP_FUSER;
				if (v == myvm || vm_node_iskernelspace(node)) {
					vm_datapart_map_ram_autoprop(self,
					                             vm_node_getstart(node),
					                             perm);
				} else {
					vm_datapart_map_ram_autoprop_p(self,
					                               v->v_pdir_phys,
					                               vm_node_getstart(node),
					                               perm);
				}
				/* Synchronize the page directory for address range mapped by the node. */
				/* FIXME: `vm_sync()' can throw E_WOULDBLOCK!
				 *        Instead, we must acquire task chain locks alongside node tree locks above! */
				vm_sync(v, vm_node_getstart(node), vm_node_getsize(node));
			}
		}
		/* Unlock all of the affected VMs */
		vm_set_lockendwrite_all(&vms);

		/* At this point, we can finally go through the range given to us by
		 * the caller, searching for any page that has been marked as CHANGED. */
		TRY {
			size_t i, count;
			for (i = partrel_min_dpage; i <= partrel_max_dpage;) {
				if (vm_datapart_getstate(self, i) != VM_DATAPART_PPP_HASCHANGED) {
					++i;
					continue;
				}
				/* Search for continuous strips of modified pages. */
				count = 1;
				while (i + count <= partrel_max_dpage &&
				       vm_datapart_getstate(self, i) == VM_DATAPART_PPP_HASCHANGED)
					++count;
				/* Actually save the data backing of the given range. */
				vm_datapart_do_savepart(self,
				                        block,
				                        dt_savepart,
				                        i,
				                        count);
				/* Go through and change all of the associated pages from CHANGED to INITIALIZED.
				 * NOTE: Some of them may have already changed in this manner, in case some other
				 *       thread is/has also synced our part. (after all: we only have a read-lock) */
				for (; count--; ++i) {
					if (vm_datapart_cmpxchstate(self, i,
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
		    partrel_max_dpage >= vm_datapart_numdpages(self) - 1) {
			/* Upgrade to a write-lock so we can re-check if all pages are
			 * still marked as INITIALIZED, rather than CHANGED. */
			if likely(sync_upgrade(self) ||
			          !(ATOMIC_READ(self->dp_flags) & VM_DATAPART_FLAG_CHANGED)) {
				size_t i;
				partrel_max_dpage = vm_datapart_numdpages(self);
				for (i = 0; i < partrel_max_dpage; ++i) {
					if unlikely(vm_datapart_getstate(self, i) == VM_DATAPART_PPP_HASCHANGED)
						goto done_unlock_write; /* Further changes happened in the mean time. */
				}
				/* Unset the CHANGED bit, now that we're certain there aren't any further changes. */
				ATOMIC_AND(self->dp_flags, ~VM_DATAPART_FLAG_CHANGED);
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
#ifdef LIBVIO_CONFIG_ENABLED
done_return_now:
#endif /* LIBVIO_CONFIG_ENABLED */
	return result;
}




/* Synchronize all modified data pages within the specified address range.
 * When called, this function will go through all data parts of `self', and
 * save any changed data pages using `self->db_type->dt_savepart'
 * @return: * : The number of saved data pages. */
PUBLIC NONNULL((1)) datapage_t KCALL
vm_datablock_sync(struct vm_datablock *__restrict self,
                  datapage_t minpage, datapage_t maxpage)
		THROWS(E_WOULDBLOCK, ...) {
	datapage_t result = 0;
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
		size_t temp, partrel_minpage, partrel_maxpage;
		struct vm_datapart *part;
		/* Search for modified parts within the given range. */
		part = vm_datablock_findchanged(self->db_parts,
		                                minpage,
		                                maxpage,
		                                &partrel_minpage,
		                                &partrel_maxpage,
		                                ATREE_SEMI0(datapage_t),
		                                ATREE_LEVEL0(datapage_t));
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
NOTHROW(KCALL vm_datablock_haschanged)(struct vm_datablock *__restrict self,
                                       datapage_t minpage, datapage_t maxpage) {
	struct vm_datapart *part;
	size_t partrel_minpage;
	size_t partrel_maxpage;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	/* Search for modified parts within the given range. */
	part = vm_datablock_findchanged(self->db_parts,
	                                minpage,
	                                maxpage,
	                                &partrel_minpage,
	                                &partrel_maxpage,
	                                ATREE_SEMI0(datapage_t),
	                                ATREE_LEVEL0(datapage_t));
	return part != NULL;
}




/* Construct a new datapart for the given address range.
 * NOTES:
 *  - The data part is _not_ inserted into the part-tree of `self',
 *    and it is the caller's task to do so, or to ensure that the
 *    given datablock is anonymous.
 *  - The data part is created as `VM_DATAPART_STATE_ABSENT', or
 *    `VM_DATAPART_STATE_VIOPRT' in the event that the data part
 *    refers to a VIO mapping. Additionally, all data pages are
 *    initialized as `VM_DATAPART_PPP_UNINITIALIZED'. */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_createpart(struct vm_datablock *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t start_offset,
                        PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct vm_datapart *result;
	datapage_t data_pageno;
	size_t num_dpages;
	assert((start_offset & PAGEMASK) == 0);
	assert((num_bytes & PAGEMASK) == 0);
	assert(num_bytes != 0);
	assert(start_offset + num_bytes > start_offset);
	data_pageno = VM_DATABLOCK_DADDR2DPAGE(self, start_offset);
	num_dpages  = num_bytes >> VM_DATABLOCK_ADDRSHIFT(self);
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
		ppp_size = CEILDIV(num_dpages,
		                   BITSOF(uintptr_t) /
		                   VM_DATAPART_PPP_BITS) *
		           sizeof(uintptr_t);
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
#ifdef LIBVIO_CONFIG_ENABLED
	if (self->db_vio)
		result->dp_state = VM_DATAPART_STATE_VIOPRT;
#endif /* LIBVIO_CONFIG_ENABLED */
	result->dp_block = incref(self);
	if (self->db_type->dt_initpart)
		(*self->db_type->dt_initpart)(result);
	return result;
}


PRIVATE ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_do_locatepart(struct vm_datablock *__restrict self,
                           PAGEDIR_PAGEALIGNED pos_t start_offset,
                           PAGEDIR_PAGEALIGNED size_t num_bytes_hint)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	vm_parttree_minmax_t minmax;
	REF struct vm_datapart *result;
	size_t num_dpages;
	uintptr_t *ppp;
	datapage_t data_pageno;
	assert((start_offset & PAGEMASK) == 0);
	assert((num_bytes_hint & PAGEMASK) == 0);
	assert(num_bytes_hint != 0);
	assert(start_offset + num_bytes_hint > start_offset);
	data_pageno = VM_DATABLOCK_DADDR2DPAGE(self, start_offset);
	num_dpages  = num_bytes_hint >> VM_DATABLOCK_ADDRSHIFT(self);
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
#ifdef LIBVIO_CONFIG_ENABLED
	if (self->db_vio)
		result->dp_state = VM_DATAPART_STATE_VIOPRT;
#endif /* LIBVIO_CONFIG_ENABLED */
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
	return vm_datablock_createpart(self,
	                               start_offset,
	                               num_bytes_hint);
}



/* Lookup and return a reference the data part containing the given `start_offset'
 * NOTE: When `self' is an anonymous data block (`self->db_parts == VM_DATABLOCK_ANONPARTS'),
 *       the the returned data part will be allocated anonymously as well, meaning that
 *       it will not be shared (`!isshared(return)'), and not be re-returned when the
 *       call is repeated with the same arguments passed once again. */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_locatepart(struct vm_datablock *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t start_offset,
                        PAGEDIR_PAGEALIGNED size_t num_bytes_hint)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct vm_datapart *result;
	assert(!task_wasconnected());
	if (ATOMIC_READ(self->db_parts) == VM_DATABLOCK_ANONPARTS) {
		result = vm_datablock_createpart(self,
		                                 start_offset,
		                                 num_bytes_hint);
	} else {
		result = vm_datablock_do_locatepart(self,
		                                    start_offset,
		                                    num_bytes_hint);
	}
	assertf((vm_datapart_startdpage(result) & VM_DATABLOCK_PAGEMASK(self)) == 0,
	        "Invalid data part (start at %#" PRIx64 ", end at %#" PRIx64 ")\n",
	        (u64)vm_datapart_startdpage(result),
	        (u64)vm_datapart_enddpage(result));
	return result;
}

/* Same as `vm_paged_datablock_locatepart()', but ensure that the returned datapart
 * starts at exactly at `start_offset', and that it doesn't have span more than
 * `max_num_bytes' pages of virtual memory (though it may still span less than that) */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_locatepart_exact(struct vm_datablock *__restrict self,
                              PAGEDIR_PAGEALIGNED pos_t start_offset,
                              PAGEDIR_PAGEALIGNED size_t max_num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct vm_datapart *result;
	REF struct vm_datapart *new_result;
	pageid64_t start_page, part_start_page;
	size_t max_pages;
	assert((start_offset & PAGEMASK) == 0);
	assert((max_num_bytes & PAGEMASK) == 0);
	assert(!task_wasconnected());
	/* Check for special case: anonymous data block tree. */
	if (ATOMIC_READ(self->db_parts) == VM_DATABLOCK_ANONPARTS) {
		result = vm_datablock_createpart(self,
		                                 start_offset,
		                                 max_num_bytes);
		goto done;
	}
again:
	result = vm_datablock_do_locatepart(self,
	                                    start_offset,
	                                    max_num_bytes);
	start_page      = (pageid64_t)(start_offset / PAGESIZE);
	part_start_page = vm_datapart_minvpage(result);
	assert(start_page >= part_start_page);
	if (start_page > part_start_page) {
		TRY {
			/* Split the part, so we get the portion that starts where we want it to! */
			new_result = vm_datapart_split(result,
			                               (size_t)(start_page - part_start_page));
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
	assert(vm_datapart_minvpage(result) == start_page);
	max_pages = max_num_bytes / PAGESIZE;
	/* Make sure that the returned data part isn't larger than `max_pages'
	 * This is once again achieved by splitting the part if it is larger, but
	 * discarding the high part and keeping the low one, instead of using the
	 * high part as we did above when ensuring that the part starts where we
	 * need it to. */
	{
		size_t num_vpages;
again_check_result_num_vpages:
		num_vpages = vm_datapart_numvpages(result);
		if (num_vpages > max_pages) {
			TRY {
				/* Split the part, so we get the portion that starts where we want it to! */
				new_result = vm_datapart_split(result, max_pages);
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
	        "Invalid data part (start at %#" PRIx64 ", end at %#" PRIx64 ")\n",
	        (u64)vm_datapart_startdpage(result),
	        (u64)vm_datapart_enddpage(result));
	return result;
}



#ifndef __INTELLISENSE__
DECL_END

#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_UNSAFE

#define DEFINE_IO_READ 1
#define DEFINE_IO_UNSAFE 1
#include "vm-datablock-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_UNSAFE 1
#include "vm-datablock-read-write-base.c.inl"

#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"

#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#include "vm-datablock-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#include "vm-datablock-read-write-base.c.inl"

#define DEFINE_IO_READ 1
#define DEFINE_IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_VECTOR 1
#include "vm-datablock-read-write-base.c.inl"

#define DEFINE_IO_READ 1
#include "vm-datablock-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#include "vm-datablock-read-write-base.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */



/* Free a given VM node (the method used depending on
 * `self->vn_flags & VM_NODE_FLAG_COREPRT') */
PUBLIC NOBLOCK NONNULL((1)) void
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
 *  - vn_fspath
 *  - vn_fsname
 *  - vn_block
 *  - vn_part
 *  - vn_link */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_destroy)(struct vm_node *__restrict self) {
	xdecref(self->vn_fspath);
	xdecref(self->vn_fsname);
	if (self->vn_block) {
		struct vm_datapart *part = self->vn_part;
		assert(self->vn_vm != NULL);
		/* If the memory mapping of `self' is still prepared, unprepare it now. */
		if (self->vn_flags & VM_NODE_FLAG_PREPARED) {
#ifndef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (self->vn_vm != &vm_kernel) /* Preparations are meaningless within kernel-space. */
#endif /* !ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			{
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if (self->vn_vm == THIS_VM || PAGEID_ISKERN(vm_node_getstartpageid(self)))
#else /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				if (self->vn_vm == THIS_VM)
#endif /* !ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				{
					pagedir_unprepare_map_p(self->vn_vm->v_pdir_phys,
					                        vm_node_getstart(self),
					                        vm_node_getsize(self));
				} else {
					pagedir_unprepare_map(vm_node_getstart(self),
					                      vm_node_getsize(self));
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





LOCAL void KCALL log_updating_access_rights(struct vm_node *__restrict self) {
	printk(KERN_DEBUG "[vm] Update access rights of %p-%p\n",
	       vm_node_getmin(self), vm_node_getmax(self));
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
	void *addr;
	size_t size;
	if (!(self->vn_prot & VM_PROT_WRITE))
		return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
	if (!sync_trywrite(self->vn_vm))
		return VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK;
	/* Just delete the mapping, so it has to be re-created, at which
	 * point all of the intended copy-on-write mechanics will take
	 * place. */
	addr = vm_node_getstart(self);
	size = vm_node_getsize(self);
	log_updating_access_rights(self);
	if (self->vn_vm == THIS_VM) {
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map(addr, size)) {
				sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef ARCH_PAGEDIR_HAVE_UNWRITE
		pagedir_unwrite(addr, size);
#else /* ARCH_PAGEDIR_HAVE_UNWRITE */
		pagedir_unmap(addr, size);
#endif /* !ARCH_PAGEDIR_HAVE_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map(addr, size);
	} else {
		pagedir_phys_t pdir = self->vn_vm->v_pdir_phys;
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map_p(pdir, addr, size)) {
				sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef ARCH_PAGEDIR_HAVE_UNWRITE
		pagedir_unwrite_p(pdir, addr, size);
#else /* ARCH_PAGEDIR_HAVE_UNWRITE */
		pagedir_unmap_p(pdir, addr, size);
#endif /* !ARCH_PAGEDIR_HAVE_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map_p(pdir, addr, size);
	}
	vm_sync(self->vn_vm, addr, size);
	sync_endwrite(self->vn_vm);
	return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
}

/* Same as `vm_node_update_write_access()', but the caller
 * is already holding a write-lock to `locked_vm' */
PUBLIC NOBLOCK unsigned int
NOTHROW(KCALL vm_node_update_write_access_locked_vm)(struct vm_node *__restrict self,
                                                     struct vm *__restrict locked_vm) {
	void *addr;
	size_t size;
	if (!(self->vn_prot & VM_PROT_WRITE))
		return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
	if (self->vn_vm != locked_vm && !sync_trywrite(self->vn_vm))
		return VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK;

	/* Just delete the mapping, so it has to be re-created, at which
	 * point all of the intended copy-on-write mechanics will take
	 * place. */
	addr = vm_node_getstart(self);
	size = vm_node_getsize(self);
	log_updating_access_rights(self);
	if (self->vn_vm == THIS_VM) {
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map(addr, size)) {
				if (self->vn_vm != locked_vm)
					sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef ARCH_PAGEDIR_HAVE_UNWRITE
		pagedir_unwrite(addr, size);
#else /* ARCH_PAGEDIR_HAVE_UNWRITE */
		pagedir_unmap(addr, size);
#endif /* !ARCH_PAGEDIR_HAVE_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map(addr, size);
	} else {
		pagedir_phys_t pdir = self->vn_vm->v_pdir_phys;
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED)) {
			if (!pagedir_prepare_map_p(pdir, addr, size)) {
				if (self->vn_vm != locked_vm)
					sync_endwrite(self->vn_vm);
				return VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC;
			}
		}
		/* By simply deleting the write-permission bit when it is set,
		 * we can drastically reduce the number of required #PFs */
#ifdef ARCH_PAGEDIR_HAVE_UNWRITE
		pagedir_unwrite_p(pdir, addr, size);
#else /* ARCH_PAGEDIR_HAVE_UNWRITE */
		pagedir_unmap_p(pdir, addr, size);
#endif /* !ARCH_PAGEDIR_HAVE_UNWRITE */
		if (!(self->vn_flags & VM_NODE_FLAG_PREPARED))
			pagedir_unprepare_map_p(pdir, addr, size);
	}
	vm_sync(self->vn_vm, addr, size);
	if (self->vn_vm != locked_vm)
		sync_endwrite(self->vn_vm);
	return VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS;
}


/* Insert the given node into its associated VM (self->vn_vm)
 * NOTE: The caller must be holding a write-lock to the associated VM. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_insert)(struct vm_node *__restrict self) {
	struct vm_node **pinsert, *insert_before;
	struct vm *v = self->vn_vm;
	assert(v);
	assertf(vm_node_getminpageid(self) <= vm_node_getmaxpageid(self),
	        "Unordered node: MIN(%p) >= MAX(%p)",
	        vm_node_getmin(self), vm_node_getmax(self));
	assertf(vm_node_getmaxpageid(self) <= __ARCH_PAGEID_MAX,
	        "Mapping of node covering pages %p-%p is out-of-bounds",
	        vm_node_getminpageid(self), vm_node_getmaxpageid(self));
	assertf(self->vn_block ? true : !self->vn_part,
	        "Node has a data part, but no data block\n"
	        "self = %p (%p-%p)\n"
	        "self->vn_part                 = %p\n"
	        "self->vn_block                = %p\n"
	        "self->vn_part->dp_block       = %p\n"
	        "self->vn_part->dp_tree.a_vmin = %" PRIu64 "(%#" PRIx64 ")\n"
	        "self->vn_part->dp_tree.a_vmax = %" PRIu64 "(%#" PRIx64 ")\n",
	        self, vm_node_getmin(self), vm_node_getmax(self),
	        self->vn_part, self->vn_block, self->vn_part->dp_block,
	        self->vn_part->dp_tree.a_vmin, self->vn_part->dp_tree.a_vmin,
	        self->vn_part->dp_tree.a_vmax, self->vn_part->dp_tree.a_vmax);
	assertf(!self->vn_part ||
	        (vm_datapart_mindpage(self->vn_part) <=
	         vm_datapart_maxdpage(self->vn_part)),
	        "Data part contains bad data page bounds\n"
	        "self = %p (%p-%p)\n"
	        "self->vn_part                 = %p\n"
	        "self->vn_block                = %p\n"
	        "self->vn_part->dp_block       = %p\n"
	        "self->vn_part->dp_tree.a_vmin = %" PRIu64 "(%#" PRIx64 ")\n"
	        "self->vn_part->dp_tree.a_vmax = %" PRIu64 "(%#" PRIx64 ")\n",
	        self, vm_node_getmin(self), vm_node_getmax(self),
	        self->vn_part, self->vn_block, self->vn_part->dp_block,
	        self->vn_part->dp_tree.a_vmin, self->vn_part->dp_tree.a_vmin,
	        self->vn_part->dp_tree.a_vmax, self->vn_part->dp_tree.a_vmax);
	assertf(!self->vn_part || !wasdestroyed(self->vn_part),
	        "Data part has a reference counter equal to 0\n"
	        "self = %p (%p-%p)\n"
	        "self->vn_part                 = %p\n"
	        "self->vn_block                = %p\n"
	        "self->vn_part->dp_block       = %p\n"
	        "self->vn_part->dp_tree.a_vmin = %" PRIu64 "(%#" PRIx64 ")\n"
	        "self->vn_part->dp_tree.a_vmax = %" PRIu64 "(%#" PRIx64 ")\n",
	        self, vm_node_getmin(self), vm_node_getmax(self),
	        self->vn_part, self->vn_block, self->vn_part->dp_block,
	        self->vn_part->dp_tree.a_vmin, self->vn_part->dp_tree.a_vmin,
	        self->vn_part->dp_tree.a_vmax, self->vn_part->dp_tree.a_vmax);
	assertf(!self->vn_block || !wasdestroyed(self->vn_block),
	        "Data block has a reference counter equal to 0\n"
	        "self = %p (%p-%p)\n"
	        "self->vn_part  = %p\n"
	        "self->vn_block = %p\n",
	        self, vm_node_getmin(self), vm_node_getmax(self),
	        self->vn_part, self->vn_block, self->vn_part->dp_block);
	assertf(!self->vn_part ||
	        (self->vn_part->dp_block == self->vn_block ||
	         self->vn_part->dp_block == &vm_datablock_anonymous ||
	         (self->vn_part->dp_block >= vm_datablock_anonymous_zero_vec &&
	          self->vn_part->dp_block < COMPILER_ENDOF(vm_datablock_anonymous_zero_vec))),
	        "Data part uses a different block than node\n"
	        "self = %p (%p-%p)\n"
	        "self->vn_part                 = %p\n"
	        "self->vn_block                = %p\n"
	        "self->vn_part->dp_block       = %p\n"
	        "self->vn_part->dp_tree.a_vmin = %" PRIu64 "(%#" PRIx64 ")\n"
	        "self->vn_part->dp_tree.a_vmax = %" PRIu64 "(%#" PRIx64 ")\n"
	        "vm_datablock_anonymous_zero_vec = { %p-%p }\n",
	        self, vm_node_getmin(self), vm_node_getmax(self),
	        self->vn_part, self->vn_block, self->vn_part->dp_block,
	        self->vn_part->dp_tree.a_vmin, self->vn_part->dp_tree.a_vmin,
	        self->vn_part->dp_tree.a_vmax, self->vn_part->dp_tree.a_vmax,
	        (byte_t *)vm_datablock_anonymous_zero_vec,
	        (byte_t *)COMPILER_ENDOF(vm_datablock_anonymous_zero_vec) - 1);
	assertf(!self->vn_part ||
	        vm_node_getpagecount(self) == vm_datapart_numvpages(self->vn_part),
	        "Node size missmatch (%" PRIuSIZ "(%#" PRIxSIZ ") != %" PRIuSIZ "(%#" PRIxSIZ "))\n"
	        "self = %p (%p-%p)\n"
	        "self->vn_part                         = %p\n"
	        "self->vn_part->dp_block               = %p\n"
	        "self->vn_part->dp_tree.a_vmin         = %" PRIu64 "(%#" PRIx64 ")\n"
	        "self->vn_part->dp_tree.a_vmax         = %" PRIu64 "(%#" PRIx64 ")\n"
	        "self->vn_part->dp_block->db_pageshift = %u\n",
	        vm_node_getpagecount(self), vm_node_getpagecount(self),
	        vm_datapart_numvpages(self->vn_part), vm_datapart_numvpages(self->vn_part),
	        self, vm_node_getmin(self), vm_node_getmax(self),
	        self->vn_part, self->vn_part->dp_block,
	        self->vn_part->dp_tree.a_vmin, self->vn_part->dp_tree.a_vmin,
	        self->vn_part->dp_tree.a_vmax, self->vn_part->dp_tree.a_vmax,
	        self->vn_part->dp_block->db_pageshift);
	assert((v->v_tree != NULL) == (v->v_byaddr != NULL));
	vm_nodetree_insert(&v->v_tree, self);
	/* Figure out where we need to insert the self. */
	pinsert = &v->v_byaddr;
	while ((insert_before = *pinsert) != NULL &&
	       (insert_before->vn_node.a_vmax < self->vn_node.a_vmin))
		pinsert = &insert_before->vn_byaddr.ln_next;
	assertf(!insert_before ||
	        self->vn_node.a_vmax < insert_before->vn_node.a_vmin,
	        "insert_before  = %p (%p-%p)\n"
	        "self           = %p (%p-%p)\n"
	        "self->vn_flags = %#x\n",
	        insert_before, vm_node_getmin(insert_before), vm_node_getmax(insert_before),
	        self, vm_node_getmin(self), vm_node_getmax(self),
	        (unsigned int)self->vn_flags);
	/* Insert the self before `insert' at `pinsert' */
	self->vn_byaddr.ln_pself = pinsert;
	self->vn_byaddr.ln_next  = insert_before;
	if (insert_before)
		insert_before->vn_byaddr.ln_pself = &self->vn_byaddr.ln_next;
	*pinsert = self;
}

PUBLIC NOBLOCK NONNULL((1)) struct vm_node *
NOTHROW(KCALL vm_paged_node_remove)(struct vm *__restrict effective_vm, pageid_t page) {
	struct vm_node *result;
	assert(sync_writing(effective_vm) || !isshared(effective_vm) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	result = vm_nodetree_remove(&effective_vm->v_tree, page);
	if likely(result)
		LLIST_REMOVE(result, vn_byaddr);
	return result;
}


#if 0
PRIVATE void KCALL
vm_assert_at(struct vm_node *__restrict node,
             ATREE_SEMI_T(pageid_t) addr_semi,
             ATREE_LEVEL_T addr_level) {
	pageid_t addr_min;
	pageid_t addr_max;
again:
	addr_min = ATREE_MAPMIN(pageid_t, addr_semi, addr_level);
	addr_max = ATREE_MAPMAX(pageid_t, addr_semi, addr_level);
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
			pageid_t next_semi;
			ATREE_LEVEL_T next_level;
			next_semi  = addr_semi;
			next_level = addr_level;
			ATREE_WALKMAX(pageid_t, next_semi, next_level);
			vm_assert_at(node->vn_node.a_max, next_semi, next_level);
		}
		ATREE_WALKMIN(pageid_t, addr_semi, addr_level);
		node = node->vn_node.a_min;
		goto again;
	}
	if (node->vn_node.a_max) {
		ATREE_WALKMAX(pageid_t, addr_semi, addr_level);
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
 * NOTE: The caller must be holding a read-lock on `self'. */
PUBLIC NOBLOCK struct vm_node *
NOTHROW(FCALL vm_getnodeofpageid)(struct vm *__restrict self, pageid_t page) {
#if 0
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
#endif
	return vm_nodetree_locate(self->v_tree, page);
}


/* Check if some part of the given address range is currently in use.
 * NOTE: The caller must be holding a read-lock on `self'. */
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL vm_paged_isused)(struct vm *__restrict self,
                               pageid_t min_page,
                               pageid_t max_page) {
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	return vm_nodetree_rlocate(self->v_tree,
	                           min_page,
	                           max_page) != NULL;
}




/* Find the first node with `vm_node_getminpageid(return) >= min_page_index'
 * If no such node exists, return `NULL' instead.
 * NOTE: The caller must be holding a read-lock to `self'. */
PUBLIC NOBLOCK WUNUSED struct vm_node *
NOTHROW(KCALL vm_find_first_node_greater_equal)(struct vm *__restrict self,
                                                pageid_t min_page_index) {
	struct vm_node *result;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	for (result = self->v_byaddr; result;
	     result = result->vn_byaddr.ln_next) {
		if (vm_node_getminpageid(result) >= min_page_index)
			break;
	}
	return result;
}

/* Find the last node with `vm_node_getmaxpageid(return) <= max_page_index'
 * If no such node exists, return `NULL' instead.
 * NOTE: The caller must be holding a read-lock to `self'. */
PUBLIC NOBLOCK WUNUSED struct vm_node *
NOTHROW(KCALL vm_find_last_node_lower_equal)(struct vm *__restrict self,
                                             pageid_t max_page_index) {
	struct vm_node *result = NULL;
	struct vm_node *iter;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1) || dbg_active);
	for (iter = self->v_byaddr; iter;
	     iter = iter->vn_byaddr.ln_next) {
		if (vm_node_getmaxpageid(iter) <= max_page_index)
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
#endif /* !__INTELLISENSE__ */


#ifndef __INTELLISENSE__
DECL_END
#define VM_DEFINE_UNMAP 1
#include "vm-unmap_protect.c.inl"
#define VM_DEFINE_PROTECT 1
#include "vm-unmap_protect.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */




/* Sync changes made to file mappings within the given address
 * range with on-disk file images. (s.a. `vm_datablock_sync()')
 * NOTE: Memory ranges that aren't actually mapped are simply ignored.
 * @return: * : The number of sychronozed bytes. (yes: those are bytes and not pages) */
PUBLIC u64 FCALL
vm_paged_syncmem(struct vm *__restrict self,
                 pageid_t minpage,
				 pageid_t maxpage)
		THROWS(E_WOULDBLOCK, ...) {
	u64 result = 0;
	vm_nodetree_minmax_t minmax;
again:
	sync_read(self);
	minmax.mm_min = minmax.mm_max = NULL;
	vm_nodetree_minmaxlocate(self->v_tree,
	                         minpage,
	                         maxpage,
	                         &minmax);
	assert((minmax.mm_min != NULL) ==
	       (minmax.mm_max != NULL));
	if (minmax.mm_min) {
		struct vm_node *iter;
		for (iter = minmax.mm_min;;) {
			REF struct vm_datapart *part;
			pageid_t node_minpageid, node_maxpageid;
			pageid_t used_minpageid, used_maxpageid;
			size_t partrel_minpageid, partrel_maxpageid;
			size_t partrel_mindatapage, partrel_maxdatapage;
			size_t num_synced_datapages;
			unsigned int addrshift;
			if ((part = iter->vn_part) == NULL)
				goto no_changes_in_node;
#ifdef LIBVIO_CONFIG_ENABLED
			if unlikely(ATOMIC_READ(part->dp_state) == VM_DATAPART_STATE_VIOPRT)
				goto no_changes_in_node;
#endif /* LIBVIO_CONFIG_ENABLED */
			if (!(ATOMIC_READ(part->dp_flags) & VM_DATAPART_FLAG_CHANGED))
				goto no_changes_in_node;
			node_minpageid = vm_node_getminpageid(iter);
			node_maxpageid = vm_node_getmaxpageid(iter);
			used_minpageid = node_minpageid;
			used_maxpageid = node_maxpageid;
			if (used_minpageid < minpage)
				used_minpageid = minpage;
			if (used_maxpageid > maxpage)
				used_maxpageid = maxpage;
			partrel_minpageid   = (size_t)(used_minpageid - node_minpageid);
			partrel_maxpageid   = (size_t)(used_maxpageid - node_minpageid);
			partrel_mindatapage = partrel_minpageid << VM_DATABLOCK_PAGESHIFT(iter->vn_block);
			partrel_maxdatapage = ((partrel_maxpageid + 1) << VM_DATABLOCK_PAGESHIFT(iter->vn_block)) - 1;
			/* Do a full check for any changes within the given range.
			 * If there are none, don't unlock the VM, but simply continue
			 * searching for any changes that may need to be synced. */
			if (!vm_datapart_haschanged(part, partrel_mindatapage, partrel_maxdatapage))
				goto no_changes_in_node;
			/* Acquire a reference to the data part. */
			incref(part);
			addrshift = VM_DATABLOCK_ADDRSHIFT(iter->vn_block);
			sync_endread(self);
			{
				FINALLY_DECREF_UNLIKELY(part);
				/* Sync changes that happened within this datapart. */
				num_synced_datapages = vm_datapart_sync(part,
				                                        partrel_mindatapage,
				                                        partrel_maxdatapage);
			}
			/* Keep track of the number of actually synced bytes.
			 * We use bytes for this as it represents a common base-line
			 * in terms of `VM_DATABLOCK_PAGESHIFT()' vs. `PAGESIZE' */
			result += (u64)num_synced_datapages << addrshift;
			/* NOTE: We don't do a check `if (used_maxpage >= maxpage) break;', because
			 *       the associated data part may have been truncated or replaced with
			 *       a different mapping since we've unlocked the VM, meaning that in
			 *       order to safely sync everything, we can only really truncate the
			 *       start of the search area. */
			if (minpage < used_minpageid)
				minpage = used_minpageid;
			goto again;
no_changes_in_node:
			if (iter == minmax.mm_max)
				break;
			iter = iter->vn_byaddr.ln_next;
		}
	}
	sync_endread(self);
	return result;
}


DECL_END

#ifndef __INTELLISENSE__
#include "vm-unmap-kernel-ram.c.inl"
/**/
#include "vm-service-tasklock.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_C */
