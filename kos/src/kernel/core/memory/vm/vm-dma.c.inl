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
#include "vm.c"
#define DMA_NX     1
//#define DMA_ENUM   1
#define DMA_VECTOR 1
#endif

#include <kernel/aio.h>
#include <kernel/iovec.h>

DECL_BEGIN

#ifdef DMA_NX
#define FUNC0(x) x##_nx
#else /* DMA_NX */
#define FUNC0(x) x
#endif /* !DMA_NX */

#ifndef DID_ASSERT_SHARED_RWLOCK_RMASK
#define DID_ASSERT_SHARED_RWLOCK_RMASK 1
STATIC_ASSERT(SHARED_RWLOCK_RMASK >= (__ARCH_PAGEID_MAX + 1));
#endif /* !DID_ASSERT_SHARED_RWLOCK_RMASK */


#ifndef DMA_ENUM
/* Start DMAing on memory within the specified address range.
 * @param: prange:     A callback that is invoked for each affected physical memory range
 *                     Should this callback return `false', all previously acquired DMA
 *                     locks are released, and `vm_startdma[v][_nx]()' returns `0'
 * @param: preset:     A callback this is invoked when it was impossible to acquire all
 *                     necessary DMA locks simultaneously without causing a dead-lock.
 *                     This is then resolved by releasing all pre-existing locks, before
 *                     forceably acquiring+releasing the blocking lock (thus ensuring that
 *                     it has become available), before starting over.
 *                     This callback is then invoked just after all previously acquired
 *                     DMA locks have been released, but just before the blocking lock
 *                     is forceably acquired. - It's purpose is then to reset whatever
 *                     information was already gathered from then released ranges.
 * @param: arg:        Argument passed to `prange' and `preset' upon execution.
 * @param: lockvec:    Vector of DMA lock slots provided by the caller.
 * @param: lockcnt:    Number of available DMA lock slots (allocated length (not size) of `lockvec')
 * @param: vaddr:     [vm_startdma[_nx]] The base address where locking should start.
 * @param: num_bytes: [vm_startdma[_nx]] The number of continuous bytes that should be locked.
 * @param: vaddr_buf:       [vm_startdmav[_nx]] The scatter-gather list of virtual memory ranges to lock.
 * @param: for_writing:When true, unshare copy-on-write mappings of associated memory, allowing the
 *                     caller to then write to the acquired memory ranges without accidentally having
 *                     any changes made appear in PRIVATE mappings of the associated memory region.
 * @return: 0 :       `*prange' returned `false'
 * @return: 0 :        Some portion of the specified address range(s) doesn't actually map to a VM node.
 * @return: 0 :        Some portion of the specified address range(s) maps to a VM node reservation (no associated data part).
 * @return: 0 :        Some portion of the specified address range(s) maps to VIO memory, meaning there is no underlying physical memory.
 * @return: 0 :       [vm_startdma[v]_nx] The equivalent `vm_startdma[v]' would have thrown an exception
 * @return: <=lockcnt: The number of used DMA locks (SUCCESS)
 * @return: > lockcnt: The number of _REQUIRED_ DMA locks (FAILURE) (All locks that may have already been acqured will have already been released) */
#ifdef DMA_NX
#ifdef DMA_VECTOR
PUBLIC NONNULL((1, 2, 3, 5, 7)) size_t
NOTHROW(KCALL vm_startdmav_nx)(struct vm *__restrict effective_vm,
                               vm_dmarangefunc_t prange,
                               vm_dmaresetfunc_t preset, void *arg,
                               struct vm_dmalock *__restrict lockvec, size_t lockcnt,
                               struct aio_buffer const *__restrict vaddr_buf,
                               bool for_writing)
#else /* DMA_VECTOR */
PUBLIC NONNULL((1, 2, 3, 5)) size_t
NOTHROW(KCALL vm_startdma_nx)(struct vm *__restrict effective_vm,
                              vm_dmarangefunc_t prange,
                              vm_dmaresetfunc_t preset, void *arg,
                              struct vm_dmalock *__restrict lockvec,
                              size_t lockcnt, UNCHECKED void *vaddr,
                              size_t num_bytes, bool for_writing)
#endif /* !DMA_VECTOR */
#else /* DMA_NX */
#ifdef DMA_VECTOR
PUBLIC NONNULL((1, 2, 3, 5, 7)) size_t KCALL
vm_startdmav(struct vm *__restrict effective_vm,
             vm_dmarangefunc_t prange,
             vm_dmaresetfunc_t preset, void *arg,
             struct vm_dmalock *__restrict lockvec, size_t lockcnt,
             struct aio_buffer const *__restrict vaddr_buf,
             bool for_writing)
#else /* DMA_VECTOR */
PUBLIC NONNULL((1, 2, 3, 5)) size_t KCALL
vm_startdma(struct vm *__restrict effective_vm,
            vm_dmarangefunc_t prange,
            vm_dmaresetfunc_t preset, void *arg,
            struct vm_dmalock *__restrict lockvec,
            size_t lockcnt, UNCHECKED void *vaddr,
            size_t num_bytes, bool for_writing)
#endif /* !DMA_VECTOR */
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#endif /* !DMA_NX */
#else /* !DMA_ENUM */
/* Similar to `vm_startdma[v][_nx]', however instead used to enumerate the DMA memory range individually.
 * @param: prange:     A callback that is invoked for each affected physical memory range
 *                     Should this callback return `false', enumeration will half and the
 *                     function will return the number of previously successfully enumerated
 *                     DMA bytes.
 * @param: arg:        Argument passed to `prange' upon execution.
 * @param: vaddr:     [vm_startdma[_nx]] The base address where locking should start.
 * @param: num_bytes: [vm_startdma[_nx]] The number of continuous bytes that should be locked.
 * @param: vaddr_buf:       [vm_startdmav[_nx]] The scatter-gather list of virtual memory ranges to lock.
 * @param: for_writing:When true, unshare copy-on-write mappings of associated memory, allowing the
 *                     caller to then write to the acquired memory ranges without accidentally having
 *                     any changes made appear in PRIVATE mappings of the associated memory region.
 * @return: * : The number of DMA bytes successfully enumerated (sum of
 *             `num_bytes' in all calls to `*prange', where `true' was returned)
 *              Upon full success, this is identical to the given `num_bytes' / `aio_buffer_size(vaddr_buf)',
 *              though for the same reasons that `vm_startdma[v][_nx]' can fail (s.a. its `@return: 0' cases),
 *              this may be less than that */
#ifdef DMA_NX
#ifdef DMA_VECTOR
PUBLIC NONNULL((1, 2, 4)) size_t
NOTHROW(KCALL vm_enumdmav_nx)(struct vm *__restrict effective_vm,
                              vm_dmarangefunc_t prange, void *arg,
                              struct aio_buffer const *__restrict vaddr_buf,
                              bool for_writing)
#else /* DMA_VECTOR */
PUBLIC NONNULL((1, 2)) size_t
NOTHROW(KCALL vm_enumdma_nx)(struct vm *__restrict effective_vm,
                             vm_dmarangefunc_t prange, void *arg,
                             UNCHECKED void *vaddr, size_t num_bytes,
                             bool for_writing)
#endif /* !DMA_VECTOR */
#else /* DMA_NX */
#ifdef DMA_VECTOR
PUBLIC NONNULL((1, 2, 4)) size_t KCALL
vm_enumdmav(struct vm *__restrict effective_vm,
            vm_dmarangefunc_t prange, void *arg,
            struct aio_buffer const *__restrict vaddr_buf,
            bool for_writing)
#else /* DMA_VECTOR */
PUBLIC NONNULL((1, 2)) size_t KCALL
vm_enumdma(struct vm *__restrict effective_vm,
           vm_dmarangefunc_t prange, void *arg,
           UNCHECKED void *vaddr, size_t num_bytes,
           bool for_writing)
#endif /* !DMA_VECTOR */
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#endif /* !DMA_NX */
#endif /* DMA_ENUM */
{
	size_t vpage_offset;
	uintptr_half_t state;
	size_t result;
#ifndef DMA_ENUM
	size_t lock_used;
#endif /* !DMA_ENUM */
#ifdef DMA_VECTOR
	struct aio_buffer_entry ent;
#ifdef __INTELLISENSE__
	UNCHECKED void *vaddr;
	size_t num_bytes;
#else
#define vaddr     ent.ab_base
#define num_bytes ent.ab_size
#endif
#ifndef DMA_ENUM
again:
#endif /* !DMA_ENUM */
	result = 0;
#ifndef DMA_ENUM
	lock_used = 0;
#endif /* !DMA_ENUM */
#ifdef DMA_NX
	if unlikely(!sync_read_nx(effective_vm))
		return 0;
#else /* DMA_NX */
	sync_read(effective_vm);
#endif /* !DMA_NX */
	AIO_BUFFER_FOREACH(ent, vaddr_buf)
#else /* DMA_VECTOR */
#ifndef DMA_ENUM
again:
#endif /* !DMA_ENUM */
	result    = 0;
#ifndef DMA_ENUM
	lock_used = 0;
#endif /* !DMA_ENUM */
#ifdef DMA_NX
	if unlikely(!sync_read_nx(effective_vm))
		return 0;
#else /* DMA_NX */
	sync_read(effective_vm);
#endif /* !DMA_NX */
#endif /* !DMA_VECTOR */
	if likely(num_bytes) {
		vm_nodetree_minmax_t minmax;
		pageid_t minpage, maxpage;
		struct vm_node *node;
		struct vm_datapart *part;
#ifdef DMA_ENUM
again_reset:
#endif /* DMA_ENUM */
#ifndef DMA_ENUM
		assert(!lockcnt || lockvec != NULL);
#endif /* !DMA_ENUM */
		minmax.mm_min = minmax.mm_max = NULL;
		minpage                       = PAGEID_ENCODE((byte_t *)vaddr);
		maxpage                       = PAGEID_ENCODE((byte_t *)vaddr + num_bytes - 1);
		vm_nodetree_minmaxlocate(effective_vm->v_tree, minpage, maxpage, &minmax);
		assert((minmax.mm_min != NULL) == (minmax.mm_max != NULL));
		if unlikely(!minmax.mm_min)
			goto err_unmapped;
		if unlikely(minpage < minmax.mm_min_min)
			goto err_unmapped;
		if unlikely(maxpage > minmax.mm_max_max)
			goto err_unmapped;
		/* Enumerate all of the nodes within the associated address range.
		 * We must ensure that all nodes are mapped consecutively, and without gaps,
		 * as well as not be reserved, or VIO mappings. */
		if (minmax.mm_min == minmax.mm_max) {
			/* Simple case: the entire range is mapped by a single node.
			 * -> In this case, we already have everything we need, and
			 *    there is no need for enumeration. */
			node = minmax.mm_min;
			part = node->vn_part;
			if unlikely(!part)
				goto err_unmapped;
			assertf(!wasdestroyed(part),
			        "Node %p at %p-%p points at destroyed data part at %p",
			        node, vm_node_getmin(node), vm_node_getmax(node), part);
			if unlikely(!sync_tryread(part)) {
				/* Need to blocking wait for the lock, then try again. */
wait_for_part_and_try_again:
				incref(part);
#ifndef DMA_ENUM
				while (lock_used--)
					vm_dmalock_release(&lockvec[lock_used]);
#endif /* !DMA_ENUM */
				sync_endread(effective_vm);
#ifdef DMA_NX
				if unlikely(!sync_read_nx(part)) {
					decref(part);
					return 0;
				}
#else /* DMA_NX */
				TRY {
					sync_read(part);
				} EXCEPT {
					decref(part);
					RETHROW();
				}
#endif /* !DMA_NX */
				sync_endread(part);
				decref(part);
				goto again_reset;
			}
			state = ATOMIC_READ(part->dp_state);
#ifdef CONFIG_VIO
			if (state == VM_DATAPART_STATE_VIOPRT) {
				sync_endread(part);
				goto err_unmapped;
			}
#endif /* CONFIG_VIO */
			if (state != VM_DATAPART_STATE_INCORE &&
			    state != VM_DATAPART_STATE_LOCKED) {
loadcore_part_and_try_again:
				incref(part);
#ifndef DMA_ENUM
				while (lock_used--)
					vm_dmalock_release(&lockvec[lock_used]);
#endif /* !DMA_ENUM */
				sync_endread(effective_vm);
#ifdef DMA_NX
				if unlikely(!vm_datapart_lockread_setcore_nx(part)) {
					decref(part);
					return 0;
				}
#else /* DMA_NX */
				TRY {
					vm_datapart_lockread_setcore(part);
				} EXCEPT {
					decref(part);
					RETHROW();
				}
#endif /* !DMA_NX */
				sync_endread(part);
				decref(part);
				goto again_reset;
			}
			if (for_writing &&
			    (node->vn_prot & VM_PROT_SHARED ? ATOMIC_READ(part->dp_crefs) != NULL : (ATOMIC_READ(part->dp_crefs) != node || node->vn_link.ln_next))) {
				/* Check if we should split the part, so-as to allow our page
				 * range to better fit the requested range of parts once we have
				 * to unshare copy-on-write references. */
				if (minpage > minmax.mm_min_min) {
					vpage_offset = (size_t)(minpage - minmax.mm_min_min);
split_part_and_try_again:
					incref(part);
					sync_endread(part);
#ifndef DMA_ENUM
					while (lock_used--)
						vm_dmalock_release(&lockvec[lock_used]);
#endif /* !DMA_ENUM */
					sync_endread(effective_vm);
#ifdef DMA_NX
					{
						REF struct vm_datapart *newpart;
						newpart = vm_datapart_split_nx(part, vpage_offset);
						if unlikely(newpart == VM_DATAPART_SPLIT_NX_FAILED) {
							vm_datapart_decref_and_merge(part);
							return 0;
						}
						decref(part);
					}
					goto again_reset;
#else /* DMA_NX */
					TRY {
						xdecref(vm_datapart_split(part, vpage_offset));
					} EXCEPT {
						vm_datapart_decref_and_merge(part);
						RETHROW();
					}
					decref(part);
					goto again_reset;
#endif /* !DMA_NX */
				}
				if (maxpage < minmax.mm_max_max) {
					vpage_offset = (size_t)(maxpage - minmax.mm_min_min) + 1;
					goto split_part_and_try_again;
				}
				/* With the part now properly sized, unshare copy-on-write mappings! */
unshare_copy_on_write_for_part:
				incref(part);
				sync_endread(part);
#ifndef DMA_ENUM
				while (lock_used--)
					vm_dmalock_release(&lockvec[lock_used]);
#endif /* !DMA_ENUM */
				sync_endread(effective_vm);
#ifdef DMA_NX
				if (!vm_datapart_lockread_setcore_unsharecow_nx(part)) {
					vm_datapart_decref_and_merge(part);
					return 0;
				}
#else /* DMA_NX */
				TRY {
					vm_datapart_lockread_setcore_unsharecow(part);
				} EXCEPT {
					vm_datapart_decref_and_merge(part);
					RETHROW();
				}
#endif /* !DMA_NX */
				sync_endread(part);
				decref(part);
				goto again_reset;
			}
			/* All right! the part is now fully prepared for us to do our' thing! */
			assert(sync_reading(part));
			assert(part->dp_state == VM_DATAPART_STATE_INCORE ||
			       part->dp_state == VM_DATAPART_STATE_LOCKED);
#ifdef DMA_ENUM
			{
				struct vm_dmalock lock;
				lock.dl_part = part;
				vm_datapart_do_enumdma(part,
				                       prange,
				                       arg,
				                       (size_t)((byte_t *)vaddr - (byte_t *)vm_node_getstart(node)),
				                       num_bytes,
				                       &lock);
			}
			sync_endread(part);
			decref(part);
			result += num_bytes;
#else /* DMA_ENUM */
			if (result < lockcnt) {
				assert(result == lock_used);
				lockvec[lock_used].dl_part = incref(part); /* Inherit reference + lock */
				vm_datapart_do_enumdma(part,
				                       prange,
				                       arg,
				                       (size_t)((byte_t *)vaddr - (byte_t *)vm_node_getstart(node)),
				                       num_bytes,
				                       &lockvec[lock_used]);
				++lock_used;
				result = lock_used;
			} else {
				sync_endread(part);
				decref(part);
				/* Release all locks which were already acquired. */
				while (lock_used) {
					--lock_used;
					vm_dmalock_release(&lockvec[lock_used]);
				}
				/* Keep on counting how many locks it would take. */
				++result;
			}
#endif /* !DMA_ENUM */
		} else {
			/* Multi-node memory range */
			node = minmax.mm_min;
			for (;;) {
				pageid_t node_minpage;
				pageid_t node_maxpage;
				size_t noderel_startaddr;
				size_t noderel_num_bytes;

				part = node->vn_part;
				if unlikely(!part)
					goto err_unmapped;
				assertf(!wasdestroyed(part),
				        "Node %p at %p-%p points at destroyed data part at %p",
				        node, vm_node_getmin(node), vm_node_getmax(node), part);
#ifdef CONFIG_VIO
				if unlikely(ATOMIC_READ(part->dp_state) == VM_DATAPART_STATE_VIOPRT)
					goto err_unmapped;
#endif /* CONFIG_VIO */
				if unlikely(!sync_tryread(part)) /* NOTE: It's OK if we get duplicate locks here! */
					goto wait_for_part_and_try_again;
				state = ATOMIC_READ(part->dp_state);
#ifdef CONFIG_VIO
				if (state == VM_DATAPART_STATE_VIOPRT) {
					sync_endread(part);
					goto err_unmapped;
				}
#endif /* CONFIG_VIO */
				if (state != VM_DATAPART_STATE_INCORE &&
				    state != VM_DATAPART_STATE_LOCKED)
					goto loadcore_part_and_try_again;
				node_minpage = vm_node_getminpageid(node);
				node_maxpage = vm_node_getmaxpageid(node);
				if (for_writing &&
				    (node->vn_prot & VM_PROT_SHARED
				     ? ATOMIC_READ(part->dp_crefs) != NULL
				     : (ATOMIC_READ(part->dp_crefs) != node ||
				        node->vn_link.ln_next))) {
					/* Check if we should split the part, so-as to allow our page
					 * range to better fit the requested range of parts once we have
					 * to unshare copy-on-write references. */
					if (minpage > node_minpage) {
						assert(node == minmax.mm_min);
						vpage_offset = (size_t)(minpage - node_minpage);
						goto split_part_and_try_again;
					}
					if (maxpage < node_maxpage) {
						assert(node == minmax.mm_max);
						vpage_offset = (size_t)(maxpage - node_minpage) + 1;
						goto split_part_and_try_again;
					}
					/* With the part now properly sized, unshare copy-on-write mappings! */
					goto unshare_copy_on_write_for_part;
				}
				/* All right! the part is now fully prepared for us to do our' thing! */
				assert(sync_reading(part));
				assert(part->dp_state == VM_DATAPART_STATE_INCORE ||
				       part->dp_state == VM_DATAPART_STATE_LOCKED);
				noderel_startaddr = node == minmax.mm_min
				                    ? (size_t)((byte_t *)vaddr - (byte_t *)vm_node_getmin(node))
				                    : 0;
				noderel_num_bytes = vm_node_getsize(node);
				if (node == minmax.mm_max)
					noderel_num_bytes = (size_t)(((byte_t *)vaddr + num_bytes) - (byte_t *)vm_node_getmin(node));
#ifdef DMA_ENUM
				{
					struct vm_dmalock lock;
					lock.dl_part = part;
					vm_datapart_do_enumdma(part,
					                       prange,
					                       arg,
					                       noderel_startaddr,
					                       noderel_num_bytes,
					                       &lock);
				}
				sync_endread(part);
				decref(part);
				result += noderel_num_bytes;
#else /* DMA_ENUM */
				if (result < lockcnt) {
					lockvec[lock_used].dl_part = incref(part); /* Inherit reference + lock */
					vm_datapart_do_enumdma(part,
					                       prange,
					                       arg,
					                       noderel_startaddr,
					                       noderel_num_bytes,
					                       &lockvec[lock_used]);
					++lock_used;
					result = lock_used;
				} else {
					sync_endread(part);
					decref(part);
					/* Release all locks which were already acquired. */
					while (lock_used) {
						--lock_used;
						vm_dmalock_release(&lockvec[lock_used]);
					}
					/* Keep on counting how many locks it would take. */
					++result;
				}
#endif /* !DMA_ENUM */
				if (node == minmax.mm_max)
					break;
				{
					struct vm_node *next;
					next = node->vn_byaddr.ln_next;
					/* Make sure that the node form a continuous line of memory! */
					if (vm_node_getstartpageid(next) != vm_node_getendpageid(node))
						goto err_unmapped;
					node = next;
				}
			}
		}
	}
	sync_endread(effective_vm);
	return result;
#ifndef DMA_ENUM
again_reset:
	(*preset)(arg);
	goto again;
#endif /* !DMA_ENUM */
err_unmapped:
	sync_endread(effective_vm);
#ifndef DMA_ENUM
	while (lock_used--)
		vm_dmalock_release(&lockvec[lock_used]);
#endif /* !DMA_ENUM */
	return 0;
#undef num_bytes
#undef vaddr
}


DECL_END

#undef FUNC0
#undef DMA_VECTOR
#undef DMA_ENUM
#undef DMA_NX
