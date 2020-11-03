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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_C
#define GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>

#include "vm-nodeapi.h"

#define ATREE(x)      vm_futextree_##x
#define ATREE_FUN     INTDEF
#define ATREE_IMP     INTERN
#define ATREE_CALL    KCALL
#define ATREE_NOTHROW NOTHROW
#define Tkey          uintptr_t
#define T             struct vm_futex
#define N_NODEPATH    f_tree
#define ATREE_IMPLEMENTATION_ONLY 1
#define ATREE_SINGLE 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_IMPLEMENTATION_ONLY
#undef ATREE_SINGLE

DECL_BEGIN

/* (possibly) delete the futex controller of `self' if it is no longer in use. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_maybe_delete_futex_controller)(struct vm_datapart *__restrict self) {
	struct vm_futex_controller *fc;
	assert(self);
	assert(sync_writing(self));
	fc = self->dp_futex;
	assert(fc);
	if (fc->fc_tree != NULL)
		return; /* Still in use -> Can't destroy. */
#ifdef ARCH_VM_HAVE_RTM
	if (fc->fc_rtm_vers != 0)
		return; /* Custom RTM version has been set -> Can't destroy. */
#endif /* ARCH_VM_HAVE_RTM */
	/* XXX: This right here doesn't ~need~ to be done.
	 *      We could also just keep the futex controller alive, so that it
	 *      may be re-used by future futex operations. In essence, we'd need
	 *      a heuristic on the likelihood of further futex allocations being
	 *      done within this data part. */
#if 1
	self->dp_futex = NULL;
	vm_futex_controller_free(fc);
#endif
}


/* Destroy the given futex due to its reference counter having reached zero. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_futex_destroy)(struct vm_futex *__restrict self) {
	REF struct vm_datapart *part;
	struct vm_futex_controller *fc;
	assert(wasdestroyed(self));

	/* As a precaution, broadcast the futex's signal to wake up any thread
	 * that may still be listening, thus ensuring that futex objects comply
	 * with the extension of `struct sig's behavior of allowing task_waitfor()
	 * on signal objects that may have already been destroyed by the time that
	 * task_waitfor() gets called. */
	sig_broadcast_for_fini(&self->f_signal);

	/* Try to lock the associated data part. */
	part = self->f_part.get();
	if (!part) {
		/* No associated part
		 * -> Our atree-leaf was already invalid to begin with,
		 *    so there is no need to unlink ourself from anywhere. */
		vm_futex_free(self);
		return;
	}

	/* NOTE: Normally, one would not be allowed to access `dp_futex' without first
	 *       acquiring a lock to the data parts `dp_lock' lock. However due to a
	 *       special ruling concerning the translocation of dead futex objects in
	 *       the event of a data part being split, as well as the fact that right
	 *       now _we_ _are_ a dead futex that is still contained within the
	 *       controller's futex tree, we _can_ actually dereference this field,
	 *       which is also something that we have to do in order to add ourself
	 *       to the set of dead futex objects in case we can't acquire a lock
	 *       to the datapart below. */
	fc = part->dp_futex;
	assert(fc);

	/* Since the data part still exists, we must manually attempt to
	 * remove ourself from the tree of existing futex objects. */
	if (!sync_trywrite(part)) {
		/* Failed to acquire a lock to the associated part.
		 * In this case, make use of the chain of dead futex objects (`fc_dead'),
		 * and have whoever is holding the lock perform the actual cleanup. */
		struct vm_futex *next;
		do {
			next = ATOMIC_READ(fc->fc_dead);
			self->f_ndead = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(fc->fc_dead, next, self));
		/* Try to service the datapart in case it became available in the mean time,
		 * thus ensuring that us being added to the chain of dead futex objects is
		 * done in an interlocked manner in regards to holding a lock to the data
		 * part. (Reminding: acquiring a lock to a datapart will automatically service
		 * dead futex objects, which at this point includes us) */
		if (sync_trywrite(part))
			sync_endwrite(part);
		return;
	}

	/* Successfully acquired a lock to the data part.
	 * -> At this point, we must remove ourself from the tree of known futex objects. */
#ifdef NDEBUG
	vm_futextree_remove(&fc->fc_tree, self->f_tree.a_vaddr,
	                    fc->fc_semi0, fc->fc_leve0);
#else /* NDEBUG */
	{
		struct vm_futex *removed;
		removed = vm_futextree_remove_at(&fc->fc_tree,
		                                 self->f_tree.a_vaddr,
		                                 fc->fc_semi0,
		                                 fc->fc_leve0);
		assert(removed == self);
	}
#endif /* !NDEBUG */
	/* (possibly) destroy the futex controller. */
	vm_datapart_maybe_delete_futex_controller(part);
	/* Unlock the associated data apart. */
	sync_endwrite(part);
	/* After having removed ourself from the data part, free ourself. */
	vm_futex_free(self);
	/* Drop the reference previously acquired for the given data part. */
	decref_unlikely(part);
}


/* Fill in `fc_semi0' and `fc_leve0' of `self' with appropriate values. */
LOCAL NONNULL((1, 2)) void
NOTHROW(KCALL vm_futex_controller_init)(struct vm_futex_controller *__restrict self,
                                        struct vm_datapart *__restrict part) {
	(void)part;
	/* TODO: Calculate best-fit semi/level values. */
	self->fc_semi0 = ATREE_SEMI0(uintptr_t);
	self->fc_leve0 = ATREE_LEVEL0(uintptr_t);
}




/* Return a reference to the futex associated with `datapart_offset' bytes into the given data part.
 * If no such futex already exists, use this chance to allocate it, as well as a potentially
 * missing `vm_futex_controller' when `self->dp_futex' was `NULL' when this function was called.
 * @return: * : A reference to the futex associated with `datapart_offset'
 * @return: VM_DATAPART_GETFUTEX_OUTOFRANGE:
 *              The given `datapart_offset' is greater than `vm_datapart_numbytes(self)', which
 *              may be the case even if you checked before that it wasn't (or simply
 *              used `vm_paged_datablock_locatepart()' in order to lookup the associated part),
 *              because there always exists the possibility that any data part gets split
 *              into multiple smaller parts. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vm_futex *
(KCALL vm_datapart_getfutex)(struct vm_datapart *__restrict self, uintptr_t datapart_offset)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct vm_futex *result;
	struct vm_futex_controller *fc;
again:
	if (!ATOMIC_READ(self->dp_futex)) {
		/* Allocate the controller. */
do_alloc_fc:
		fc = vm_futex_controller_alloc();
		vm_futex_controller_init(fc, self);
		TRY {
			sync_write(self);
		} EXCEPT {
			vm_futex_controller_free(fc);
			RETHROW();
		}
		if unlikely(ATOMIC_READ(self->dp_futex) != NULL) {
			vm_futex_controller_free(fc);
			fc = self->dp_futex;
		} else {
			self->dp_futex = fc;
		}
#if 1
		/* We can't use the normal `sync_downgrade(self)' here, since that may
		 * call into `vm_datapart_service_stale()', which is allowed to invoke
		 * `vm_datapart_maybe_delete_futex_controller()', which in turn could
		 * think that given the fact that `fc' is currently empty, it may as
		 * well get rid of it for that reason.
		 * In other words: `sync_downgrade(self)' would be allowed to `kfree(fc)',
		 *                 which would end up with a fault in `vm_futextree_locate_at()'
		 *                 caused by the attempt to access kfree()'d memory. */
		sync_downgrade(&self->dp_lock);
#else
		sync_downgrade(self);
#endif
	} else {
		sync_read(self);
		if ((fc = self->dp_futex) == NULL) {
			sync_endread(self);
			goto do_alloc_fc;
		}
	}
	/* Verify the bounds of the given data part. */
	if unlikely(datapart_offset > vm_datapart_numbytes(self)) {
		sync_endread(self);
		return VM_DATAPART_GETFUTEX_OUTOFRANGE;
	}
	/* Search for an existing futex. */
	result = vm_futextree_locate_at(fc->fc_tree,
	                                datapart_offset,
	                                fc->fc_semi0,
	                                fc->fc_leve0);
	if (result) {
		bool refok;
		/* Futex already exists (try to get a reference) */
		refok = tryincref(result);
		sync_endread(self);
		if likely(refok)
			return result;
yield_and_again:
		/* The existing futex is currently dying.
		 * -> Try to yield to whomever is controlling the destruction. */
		task_yield();
		goto again;
	}
	/* The futex is missing (allocate it now) */
	result = vm_futex_allocf_nx(GFP_ATOMIC);
	if (!result) {
		/* Must perform the allocation while blocking. */

#if 0 /* This may `sync_endread(self)' may kfree() an empty futex controller. */
		sync_endread(self);
		result = vm_futex_alloc();
#else /* We don't want it to do that. Instead, we do this: */
		sync_endread(&self->dp_lock);
		TRY {
			result = vm_futex_alloc();
		} EXCEPT {
			if (sync_trywrite(self)) {
				vm_datapart_maybe_delete_futex_controller(self);
				sync_endwrite(self);
			}
			RETHROW();
		}
#endif
		TRY {
			sync_write(self);
		} EXCEPT {
			vm_futex_free(result);
			RETHROW();
		}
		goto do_recheck_existing_futex_and_controller;
	} else {
		bool lock_was_kept;
		TRY {
			lock_was_kept = sync_upgrade(self);
		} EXCEPT {
			vm_futex_free(result);
			RETHROW();
		}
		if (!lock_was_kept) {
			struct vm_futex *new_result;
			/* Re-check that there is still a controller and no existing futex. */
do_recheck_existing_futex_and_controller:
			fc = self->dp_futex;
			if unlikely(!fc) {
				/* Must allocate the controller. */
				fc = vm_futex_controller_allocf_nx(GFP_ATOMIC);
				if (fc) {
					vm_futex_controller_init(fc, self);
					self->dp_futex = fc;
				} else {
					/* Must allocate the controller while blocking. */
					sync_endwrite(self);
					TRY {
						fc = vm_futex_controller_alloc();
						TRY {
							sync_write(self);
						} EXCEPT {
							vm_futex_controller_free(fc);
							RETHROW();
						}
					} EXCEPT {
						vm_futex_free(result);
						RETHROW();
					}
					if unlikely(self->dp_futex) {
						vm_futex_controller_free(fc);
						fc = self->dp_futex;
					} else {
						self->dp_futex = fc;
						vm_futex_controller_init(fc, self);
					}
				}
			}
			/* At this point, we've got an allocated controller,
			 * as well as a freshly allocated new futex, as well
			 * as a write-lock on `self'.
			 * However, we must still re-check if the futex already exists. */
			assert(fc);
			assert(result);
			new_result = vm_futextree_locate_at(fc->fc_tree,
			                                    datapart_offset,
			                                    fc->fc_semi0,
			                                    fc->fc_leve0);
			if unlikely(new_result) {
				/* Return an existing futex, or wait for an existing futex to go away. */
				bool refok;
				refok = tryincref(new_result);
				sync_endwrite(self);
				vm_futex_free(result);
				if (refok)
					return new_result;
				goto yield_and_again;
			}
		}
	}
	/* At this point, we...
	 *  ... have got a freshly allocated futex in `result'
	 *  ... know that there is no pre-existing futex for `datapart_offset'
	 *  ... know that a futex controller has been allocated
	 *  ... are holding a lock to `self'
	 * In other words, this is the part where we initialize a new futex. */
	result->f_refcnt = 1; /* The reference we'll eventually return */
	xatomic_weaklyref_init(&result->f_part, self);
	result->f_tree.a_vaddr = datapart_offset;
	sig_init(&result->f_signal);
	/* Insert the new futex into the tree. */
	vm_futextree_insert_at(&fc->fc_tree,
	                       result,
	                       fc->fc_semi0,
	                       fc->fc_leve0);
	/* And we're done! Now just to release the lock held on `self' */
	sync_endwrite(self);
	/* Return the newly allocated futex. */
	return result;
}


/* Same as `vm_datapart_getfutex()', but don't allocate a new
 * futex object if none already exists for the given `datapart_offset'
 * @return: * :   A reference to the futex bound to the given `datapart_offset'
 * @return: NULL: No futex exists for the given `datapart_offset', even though `datapart_offset'
 *                was located within the bounds of the given data part at
 *                the time of the call being made.
 * @return: VM_DATAPART_GETFUTEX_OUTOFRANGE:
 *               The given `datapart_offset' is greater than `vm_datapart_numbytes(self)'
 *               s.a. `vm_datapart_getfutex()' */
PUBLIC WUNUSED NONNULL((1)) REF struct vm_futex *
(KCALL vm_datapart_getfutex_existing)(struct vm_datapart *__restrict self,
                                      uintptr_t datapart_offset)
		THROWS(E_WOULDBLOCK) {
	REF struct vm_futex *result;
	struct vm_futex_controller *fc;
	sync_read(self);
	fc = self->dp_futex;
	if unlikely(!fc) {
		result = NULL;
		goto done_check_oob;
	}
	/* Lookup the futex within the futex tree. */
	result = vm_futextree_locate_at(fc->fc_tree,
	                                datapart_offset,
	                                fc->fc_semi0,
	                                fc->fc_leve0);
	if (result) {
		/* Try to acquire a reference to the futex. */
		if unlikely(!tryincref(result))
			result = NULL;
	} else {
		/* Check if we didn't find anything because the address is out-of-bounds. */
done_check_oob:
		if unlikely(datapart_offset >= vm_datapart_numbytes(self))
			result = VM_DATAPART_GETFUTEX_OUTOFRANGE;
	}
	sync_endread(self);
	return result;
}

/* Lookup a futex at a given address that is offset from the start of a given
 * data block. Note though the possibly unintended behavior which applies when
 * the given `vm_datablock' is anonymous at the time of the call being made.
 * WARNING: Using this function when `self' has been, or always was anonymous, will
 *          cause the data part associated with the returned futex to also be anonymous,
 *          meaning that the part would get freshly allocated, and repeated calls with
 *          the same arguments would not yield the same futex object!
 *       -> As such, in the most common case of a futex lookup where you wish to find
 *          the futex associated with some given address, the process would be to
 *          determine the `vm_node' of the address, and using that node then determine
 *          the associated vm_datapart, and relative offset into that datapart. If a lookup
 *          of the futex then returns `VM_DATAPART_GETFUTEX_OUTOFRANGE', loop back around
 *          and once again lookup the `vm_node'.
 *       -> In the end, there exists no API also found on linux that would make use of this
 *          function, however on KOS it is possible to access this function through use of
 *          the HANDLE_TYPE_DATABLOCK-specific hop() function `HOP_DATABLOCK_OPEN_FUTEX[_EXISTING]'
 * @return: * : The futex associated with the given `offset' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vm_futex *
(KCALL vm_datablock_getfutex)(struct vm_datablock *__restrict self, pos_t offset)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct vm_futex *result;
	REF struct vm_datapart *part;
	pos_t partrel_addr;
again:
	/* Lookup the datapart that should contain the associated futex. */
	part = vm_datablock_locatepart(self, (pos_t)FLOOR_ALIGN(offset, PAGESIZE), PAGESIZE);
	partrel_addr = (pos_t)(offset - vm_datapart_minbyte(part));
#if __SIZEOF_POINTER__ < __FS_SIZEOF(OFF)
	/* Make sure that the part-relative address offset
	 * doesn't overflow. If it does, force a split! */
	if (partrel_addr > (pos_t)(uintptr_t)-1) {
		REF struct vm_datapart *used_part;
		TRY {
			used_part = vm_datablock_locatepart_exact(self,
			                                          (pos_t)FLOOR_ALIGN(offset, PAGESIZE),
			                                          PAGESIZE);
		} EXCEPT {
			decref_unlikely(part);
			RETHROW();
		}
		decref_unlikely(part);
		part         = used_part;
		partrel_addr = (pos_t)(offset - vm_datapart_minbyte(part));
	}
	assert(partrel_addr <= (pos_t)(uintptr_t)-1);
#endif /* __SIZEOF_POINTER__ < __FS_SIZEOF(OFF) */
	{
		FINALLY_DECREF_UNLIKELY(part);
		/* Using the datapart, lookup the futex. */
		result = vm_datapart_getfutex(part, (uintptr_t)partrel_addr);
		/* Handle the special case of the data part being split and truncated before
		 * we were able to acquire a reference to the associated futex (if any) */
		if unlikely(result == VM_DATAPART_GETFUTEX_OUTOFRANGE)
			goto again;
	}
	return result;
}

/* Same as `vm_datablock_getfutex()', but don't allocate a new
 * futex object if none already exists for the given `offset'
 * @return: * : The futex associated with the given `offset'
 * @return: NULL: No futex exists for the given address. */
PUBLIC WUNUSED NONNULL((1)) REF struct vm_futex *
(KCALL vm_datablock_getfutex_existing)(struct vm_datablock *__restrict self, pos_t offset)
		THROWS(E_WOULDBLOCK) {
	REF struct vm_futex *result;
	REF struct vm_datapart *part;
	/* An anonymous data-block can't refer to any existing
	 * data parts, so there can't be any existing futex objects! */
again:
	if unlikely(ATOMIC_READ(self->db_parts) == VM_DATABLOCK_ANONPARTS)
		return NULL;
	sync_read(self);
	COMPILER_READ_BARRIER();
	if unlikely(self->db_parts == VM_DATABLOCK_ANONPARTS) {
		sync_endread(self);
		return NULL;
	}
	part = vm_parttree_locate(self->db_parts,
	                          VM_DATABLOCK_DADDR2DPAGE(self, offset));
	if (!part) {
		/* No part exists for the given address. */
		sync_endread(self);
		return NULL;
	}
	incref(part);
	sync_endread(self);
	/* Got the associated data part! */
	{
		pos_t partrel_addr;
		FINALLY_DECREF_UNLIKELY(part);
		partrel_addr = (pos_t)(offset - vm_datapart_minbyte(part));
#if __SIZEOF_POINTER__ < __FS_SIZEOF(OFF)
		/* Make sure that the part-relative address offset doesn't overflow. */
		if (partrel_addr > (pos_t)(uintptr_t)-1) {
			result = NULL;
		} else
#endif /* __SIZEOF_POINTER__ < __FS_SIZEOF(OFF) */
		{
			result = vm_datapart_getfutex_existing(part,
			                                       (uintptr_t)partrel_addr);
		}
	}
	/* Handle the special case of the data part being split and truncated before
	 * we were able to acquire a reference to the associated futex (if any) */
	if unlikely(result == VM_DATAPART_GETFUTEX_OUTOFRANGE)
		goto again;
	return result;
}

/* Return the futex object that is associated with the given virtual memory address.
 * In the event that `addr' isn't  */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vm_futex *
(KCALL vm_getfutex)(struct vm *__restrict effective_vm, UNCHECKED void *addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT) {
	struct vm_node *node;
	REF struct vm_futex *result;
	REF struct vm_datapart *part;
	void *node_minaddr;
again:
	sync_read(effective_vm);
	node = vm_getnodeofaddress(effective_vm, addr);
	if unlikely(!node || (part = node->vn_part) == NULL) {
		sync_endread(effective_vm);
		THROW(E_SEGFAULT_UNMAPPED,
		      addr,
		      E_SEGFAULT_CONTEXT_FAULT);
	}
	node_minaddr = vm_node_getmin(node);
	incref(part);
	sync_endread(effective_vm);
	{
		uintptr_t partrel_addr;
		FINALLY_DECREF_UNLIKELY(part);
		partrel_addr = (uintptr_t)((byte_t *)addr - (byte_t *)node_minaddr);
		/* Lookup the futex within the detected data part. */
		result = vm_datapart_getfutex(part, partrel_addr);
	}
	/* Handle the special case of the data part being split and truncated before
	 * we were able to acquire a reference to the associated futex (if any) */
	if unlikely(result == VM_DATAPART_GETFUTEX_OUTOFRANGE)
		goto again;
	return result;
}

/* Same as `vm_getfutex()', but don't allocate a new
 * futex object if none already exists for the given `addr'
 * @return: * : The futex associated with the given `addr'
 * @return: NULL: No futex exists for the given address. */
PUBLIC WUNUSED NONNULL((1)) REF struct vm_futex *
(KCALL vm_getfutex_existing)(struct vm *__restrict effective_vm, UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	struct vm_node *node;
	REF struct vm_futex *result;
	REF struct vm_datapart *part;
	void *node_minaddr;
again:
	sync_read(effective_vm);
	node = vm_getnodeofaddress(effective_vm, addr);
	if unlikely(!node || (part = node->vn_part) == NULL) {
		sync_endread(effective_vm);
		THROW(E_SEGFAULT_UNMAPPED,
		      addr,
		      E_SEGFAULT_CONTEXT_FAULT);
	}
	node_minaddr = vm_node_getmin(node);
	incref(part);
	sync_endread(effective_vm);
	{
		uintptr_t partrel_addr;
		FINALLY_DECREF_UNLIKELY(part);
		partrel_addr = (uintptr_t)((byte_t *)addr - (byte_t *)node_minaddr);
		/* Lookup the futex within the detected data part. */
		result = vm_datapart_getfutex_existing(part, partrel_addr);
	}
	/* Handle the special case of the data part being split and truncated before
	 * we were able to acquire a reference to the associated futex (if any) */
	if unlikely(result == VM_DATAPART_GETFUTEX_OUTOFRANGE)
		goto again;
	return result;
}

/* Broadcast to all thread waiting for a futex at `futex_address' within the current VM */
PUBLIC void FCALL
vm_futex_broadcast(UNCHECKED void *futex_address)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	REF struct vm_futex *f;
	struct vm *effective_vm = THIS_VM;
	if (ADDR_ISKERN(futex_address))
		effective_vm = &vm_kernel;
	/* Lookup a futex at the given address. */
	f = vm_getfutex_existing(effective_vm, futex_address);
	if (f) {
		sig_broadcast(&f->f_signal);
		decref_unlikely(f);
	}
}





DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_C */
