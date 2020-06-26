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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_H 1

#include <kernel/compiler.h>

#include <kernel/arch/vm.h>
#include <kernel/driver-callbacks.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/types.h>
#include <sched/rwlock.h>
#include <sched/shared_rwlock.h>

#include <hybrid/__altint.h>
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/sequence/atree.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/pageid.h>
#include <compat/config.h>

#include <stdbool.h>

#include <libvio/access.h>

#ifdef __ARCH_HAVE_COMPAT
#include <hybrid/__pointer.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#ifndef CONFIG_NO_SWAP
#ifndef CONFIG_SWAP
#define CONFIG_SWAP 1
#elif (CONFIG_SWAP+0) == 0
#undef CONFIG_SWAP
#define CONFIG_NO_SWAP 1
#endif
#endif /* !CONFIG_NO_SWAP */


#ifdef __CC__
struct vm;
struct vm_node;
struct vm_datapart;
struct vm_datablock;
struct vm_futex_controller;
struct path;
struct directory_entry;

#ifndef __gfp_t_defined
#define __gfp_t_defined 1
typedef unsigned int gfp_t;
#endif /* !__gfp_t_defined */

#ifndef __pageid_t_defined
#define __pageid_t_defined 1
typedef __ARCH_PAGEID_TYPE pageid_t;
#endif /* !__pageid_t_defined */
#endif /* __CC__ */
#define PAGEID_ENCODE __ARCH_PAGEID_ENCODE
#define PAGEID_DECODE __ARCH_PAGEID_DECODE
#ifdef __ARCH_PAGEID_DECODE_USER
#define PAGEID_DECODE_USER(user_pageid) \
	(__hybrid_assert(__ARCH_PAGEID_DECODE_ISUSER(user_pageid)), __ARCH_PAGEID_DECODE_USER(user_pageid))
#else /* __ARCH_PAGEID_DECODE_USER */
#define PAGEID_DECODE_USER(user_pageid) __ARCH_PAGEID_DECODE(user_pageid)
#endif /* !__ARCH_PAGEID_DECODE_USER */
#ifdef __ARCH_PAGEID_DECODE_KERNEL
#define PAGEID_DECODE_KERNEL(kernel_pageid) \
	(__hybrid_assert(__ARCH_PAGEID_DECODE_ISKERNEL(kernel_pageid)), __ARCH_PAGEID_DECODE_KERNEL(kernel_pageid))
#else /* __ARCH_PAGEID_DECODE_KERNEL */
#define PAGEID_DECODE_KERNEL(kernel_pageid) __ARCH_PAGEID_DECODE(kernel_pageid)
#endif /* !__ARCH_PAGEID_DECODE_KERNEL */

/* Check if a given `pageid' or [startpageid,endpageid)
 * is consider apart of user- or kernel-space.
 * The *_PARTIAL functions check if the range has any overlapping
 * parts with the named address space, while the non-_PARTIAL functions
 * check that the entire range is apart of the named address space.
 * Note that the range-checking functions are allowed to assume that
 * `endpageid >= startpageid'. In the case where `endpageid == startpageid',
 * the range-checking functions behave identical to `ADDR_IS(KERN|USER)',
 * or in other words: will use `endpageid = startpageid+1' */
#ifdef KERNELSPACE_HIGHMEM
#define KERNELSPACE_MINPAGEID   PAGEID_ENCODE(KERNELSPACE_BASE)
#define KERNELSPACE_MAXPAGEID   __ARCH_PAGEID_MAX
#define PAGEID_ISKERN(pageid)                              (__CCAST(pageid_t)(pageid) >= PAGEID_ENCODE(KERNELSPACE_BASE))
#define PAGEID_ISUSER(pageid)                              (__CCAST(pageid_t)(pageid) < PAGEID_ENCODE(KERNELSPACE_BASE))
#define PAGEIDRANGE_ISKERN(startpageid, endpageid)         (__CCAST(pageid_t)(startpageid) >= PAGEID_ENCODE(KERNELSPACE_BASE))
#define PAGEIDRANGE_ISUSER(startpageid, endpageid)         (__CCAST(pageid_t)(endpageid) <= PAGEID_ENCODE(KERNELSPACE_BASE))
#define PAGEIDRANGE_ISKERN_PARTIAL(startpageid, endpageid) (__CCAST(pageid_t)(endpageid) > PAGEID_ENCODE(KERNELSPACE_BASE))
#define PAGEIDRANGE_ISUSER_PARTIAL(startpageid, endpageid) (__CCAST(pageid_t)(startpageid) < PAGEID_ENCODE(KERNELSPACE_BASE))
#elif defined(KERNELSPACE_LOWMEM)
#define KERNELSPACE_MINPAGEID   0
#define KERNELSPACE_MAXPAGEID   (PAGEID_ENCODE(KERNELSPACE_END) - 1)
#define PAGEID_ISKERN(pageid)                              (__CCAST(pageid_t)(pageid) < PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEID_ISUSER(pageid)                              (__CCAST(pageid_t)(pageid) >= PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEIDRANGE_ISKERN(startpageid, endpageid)         (__CCAST(pageid_t)(endpageid) <= PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEIDRANGE_ISUSER(startpageid, endpageid)         (__CCAST(pageid_t)(startpageid) >= PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEIDRANGE_ISKERN_PARTIAL(startpageid, endpageid) (__CCAST(pageid_t)(startpageid) < PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEIDRANGE_ISUSER_PARTIAL(startpageid, endpageid) (__CCAST(pageid_t)(endpageid) > PAGEID_ENCODE(KERNELSPACE_END))
#else
#define KERNELSPACE_MINPAGEID   PAGEID_ENCODE(KERNELSPACE_BASE)
#define KERNELSPACE_MAXPAGEID   (PAGEID_ENCODE(KERNELSPACE_END) - 1)
#define PAGEID_ISKERN(pageid)                              (__CCAST(pageid_t)(pageid) >= PAGEID_ENCODE(KERNELSPACE_BASE) && __CCAST(pageid_t)(pageid) < PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEID_ISUSER(pageid)                              (__CCAST(pageid_t)(pageid) < PAGEID_ENCODE(KERNELSPACE_BASE) && __CCAST(pageid_t)(pageid) >= PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEIDRANGE_ISKERN(startpageid, endpageid)         (__CCAST(pageid_t)(startpageid) >= PAGEID_ENCODE(KERNELSPACE_BASE) && __CCAST(pageid_t)(endpageid) <= PAGEID_ENCODE(KERNELSPACE_END))
#define PAGEIDRANGE_ISUSER(startpageid, endpageid)         (__CCAST(pageid_t)(startpageid) >= PAGEID_ENCODE(KERNELSPACE_END) || __CCAST(pageid_t)(endpageid) <= PAGEID_ENCODE(KERNELSPACE_BASE))
#define PAGEIDRANGE_ISKERN_PARTIAL(startpageid, endpageid) (__CCAST(pageid_t)(startpageid) < PAGEID_ENCODE(KERNELSPACE_END) || __CCAST(pageid_t)(endpageid) > PAGEID_ENCODE(KERNELSPACE_BASE))
#define PAGEIDRANGE_ISUSER_PARTIAL(startpageid, endpageid) (__CCAST(pageid_t)(startpageid) < PAGEID_ENCODE(KERNELSPACE_BASE) && __CCAST(pageid_t)(endpageid) > PAGEID_ENCODE(KERNELSPACE_END))
#endif


#ifdef __CC__
#ifndef __datapage_t_defined
#define __datapage_t_defined 1
__HYBRID_ALTINT_TYPEDEF(u64, datapage_t, false); /* Data part page number. */
#endif /* !__datapage_t_defined */

struct vm_ramblock {
	pageptr_t  rb_start; /* Starting page number of physical memory associated with the ram block. */
	size_t     rb_size;  /* Number of continuous physical memory pages used by this block. */
#if __SIZEOF_PAGEPTR_T__ > __SIZEOF_SIZE_T__
	byte_t     rb_pad[__SIZEOF_PAGEPTR_T__ - __SIZEOF_SIZE_T__];
#endif /* __SIZEOF_PAGEPTR_T__ > __SIZEOF_SIZE_T__ */
};

#ifndef CONFIG_NO_SWAP
#if __SIZEOF_VM_SPAGE_T__ == __SIZEOF_PAGEPTR_T__
#define VM_SWPBLOCK_EQUALS_RAMBLOCK 1
#endif /* __SIZEOF_VM_SPAGE_T__ == __SIZEOF_PAGEPTR_T__ */
struct vm_swpblock {
	vm_spage_t  sb_start; /* Starting page number of swap memory associated with the ram block. */
	size_t      sb_size;  /* Number of continuous swap memory pages used by this block. */
#if __SIZEOF_VM_SPAGE_T__ > __SIZEOF_SIZE_T__
	byte_t      sb_pad[__SIZEOF_VM_SPAGE_T__ - __SIZEOF_SIZE_T__];
#endif /* __SIZEOF_VM_SPAGE_T__ > __SIZEOF_SIZE_T__ */
};
#endif /* !CONFIG_NO_SWAP */


/* Callback for enumerating physical memory ranges for the purposes of DMA
 * @param: arg:       The same `arg' given to `vm_startdma[v][_nx]'
 * @param: paddr:     The physical memory base address of the range.
 * @param: num_bytes: The number of bytes found within the range.
 * @param: lock:      The lock used to lock the associated DMA range. */
typedef bool /*NOTHROW*/ (KCALL *vm_dmarangefunc_t)(void *arg, vm_phys_t paddr, size_t num_bytes,
                                                   struct vm_dmalock *__restrict lock);
typedef void /*NOTHROW*/ (KCALL *vm_dmaresetfunc_t)(void *arg);
#endif /* __CC__ */



/* VM datapart PageProPerty bits. */
#define VM_DATAPART_PPP_UNINITIALIZED 0x00 /* Page is uninitialized (TRANSITION -> VM_DATAPART_PPP_INITIALIZING) */
#define VM_DATAPART_PPP_INITIALIZING  0x01 /* Page is currently being initialized (TRANSITION -> VM_DATAPART_PPP_INITIALIZED, VM_DATAPART_PPP_UNINITIALIZED) */
#define VM_DATAPART_PPP_INITIALIZED   0x02 /* Page has been initialized (TRANSITION -> VM_DATAPART_PPP_HASCHANGED, VM_DATAPART_PPP_UNINITIALIZED) */
#define VM_DATAPART_PPP_HASCHANGED    0x03 /* Page has been modified post-initialization (TRANSITION -> VM_DATAPART_PPP_INITIALIZED, VM_DATAPART_PPP_UNINITIALIZED) */
#define VM_DATAPART_PPP_ISINITIALIZED(x) ((x) >= VM_DATAPART_PPP_INITIALIZED)
#define VM_DATAPART_PPP_MASK          0x03 /* Mask of per-page bits */
#define VM_DATAPART_PPP_BITS          2    /* # of bits associated with each page in the `dp_pprop' bitset */





#ifdef __CC__
struct vm_datapart {
	/* NOTE: The reference loop between `vm_datablock' <--> `vm_datapart' is
	 *       intentional, as it allows data parts to remain allocated as caches
	 *       which can easily be deallocated by making them anonymous, at which
	 *       point they become detached from their associated data block. */
	WEAK refcnt_t            dp_refcnt; /* Reference counter for this data part. */
	struct shared_rwlock     dp_lock;   /* Lock for this data part.
	                                     * NOTE: A shared lock is used, so-as to allow for preemption when
	                                     *       this lock is held for the purposes of DMA initialization. */
	union ATTR_PACKED {
		struct ATTR_PACKED {
			struct vm_datapart *a_min;      /* [0..1] Lower node. */
			struct vm_datapart *a_max;      /* [0..1] Upper node. */
			union ATTR_PACKED {
				uintptr_t       a_vmin_ptr; /* Lower bound. */
#ifdef __INTELLISENSE__
				struct { datapage_t a_vmin; /* Lower bound. */ };
#else /* __INTELLISENSE__ */
				datapage_t      a_vmin;     /* Lower bound. */
#endif /* !__INTELLISENSE__ */
			};
			union ATTR_PACKED {
				uintptr_t       a_vmax_ptr; /* Upper bound. */
#ifdef __INTELLISENSE__
				struct { datapage_t a_vmax; /* Upper bound. */ };
#else /* __INTELLISENSE__ */
				datapage_t      a_vmax;     /* Upper bound. */
#endif /* !__INTELLISENSE__ */
			};
		}                              dp_tree_ptr;
		ATREE_NODE(struct vm_datapart, datapage_t)
		                               dp_tree;   /* [lock(READ(dp_block || dp_lock))]
		                                           * [lock(WRITE(a_vmin,a_vmax:dp_block && dp_lock))]
		                                           * [lock(WRITE(a_min,a_max:dp_block))]
		                                           * Part tree. */
	};
	LLIST(struct vm_node)    dp_crefs;   /* [0..1][lock(dp_lock)] Chain of vm_node mappings this part in copy-on-write mode (VM_MAP_FPRIVATE). */
	LLIST(struct vm_node)    dp_srefs;   /* [0..1][lock(dp_lock)] Chain of vm_node mappings this part in write-shared mode (VM_MAP_FSHARED). */
	WEAK struct vm_node     *dp_stale;   /* [0..1][CHAIN(->vn_byaddr.ln_next)] Chain of nodes still bound to this node, but no longer mapped.
	                                      * NOTE: Each of these nodes is holding a reference to its associated VM via that VM's `v_weakrefcnt'
	                                      *       reference counter, which once it reaches 0, will cause the VM to be freed.
	                                      *       This is required to ensure that the VMs reachable via `dp_crefs/dp_srefs'->vn_vm
	                                      *       are still allocated, so-long as a lock to `dp_lock' is being held. */
	REF struct vm_datablock *dp_block;   /* [1..1][lock(dp_lock)] The associated data block (Points to `&vm_datablock_anonymous_zero_vec[*]' for anonymous/unshared parts) */
	uintptr_half_t           dp_flags;   /* Data part flags (Set of `VM_DATAPART_FLAG_*') */
#define VM_DATAPART_FLAG_NORMAL   0x0000 /* Normal datapart flags. */
#define VM_DATAPART_FLAG_LOCKED   0x0001 /* [lock(dp_lock)] Keep the data part locked in memory. (Any state
                                          * transition to `VM_DATAPART_STATE_INCORE' will instead transition
                                          * to `VM_DATAPART_STATE_LOCKED')
                                          * NOTE: This flag can be modified by user-space. */
#define VM_DATAPART_FLAG_CHANGED  0x0004 /* [lock(dp_lock,SET(READ(dp_lock)))] Set when any of the part's page property
                                          * bits are changed to indicate a modified page (cleared once all modified
                                          * pages have been saved once again (s.a. `vm_datablock_type::dt_savepart'))
                                          * NOTE: This flag is ignored when `VM_DATAPART_FLAG_TRKCHNG' is set.
                                          * NOTE: This flag may be set atomically while only holding a read-lock to `dp_lock' */
#define VM_DATAPART_FLAG_KEEPRAM  0x0800 /* [const] Don't page_free() RAM or swap_free() SWAP when the part is destroyed. */
#define VM_DATAPART_FLAG_TRKCHNG  0x1000 /* [lock(dp_lock)][config_if(== 0)][== 0 || == dp_block && dp_block->db_type->dt_savepart != NULL]
                                          * Changes made to this data part should be tracked.
                                          * This bit is cleared when the part gets anonymized, until which point it is
                                          * indicative of the associated block's support for saving modified parts. */
#define VM_DATAPART_FLAG_HEAPPPP  0x2000 /* [const] The page property vector is allocated on the heap (s.a. `dp_pprop_p'). */
#define VM_DATAPART_FLAG_COREPRT  0x4000 /* [const] This `struct vm_datapart' was allocated using the core-page allocator. */
#define VM_DATAPART_FLAG_KERNPRT  0x8000 /* [const] This `struct vm_datapart' is part of the kernel's static VM state.
                                          *         When set, the destruction of this data part results in kernel panic. */
	uintptr_half_t           dp_state;   /* [lock(dp_lock)] Data part state (One of `VM_DATAPART_STATE_*')
	                                      * [config_if(VM_DATAPART_STATE_VIOPRT)] The VIO-mode cannot be set
	                                      * after the fact, and cannot be changed to something else, either! */
#define VM_DATAPART_STATE_ABSENT  0x0000 /* The part has not been allocated. */
#define VM_DATAPART_STATE_INCORE  0x0001 /* The part is currently loaded into main memory. */
#define VM_DATAPART_STATE_LOCKED  0x0002 /* The part has been locked in main memory. */
#ifndef CONFIG_NO_SWAP
#define VM_DATAPART_STATE_INSWAP  0x0003 /* The part has been off-loaded into swap. */
#endif /* !CONFIG_NO_SWAP */
#ifdef LIBVIO_CONFIG_ENABLED
#define VM_DATAPART_STATE_VIOPRT  0x0004 /* The part is implemented via I/O. */
#endif /* LIBVIO_CONFIG_ENABLED */
#define VM_DATAPART_STATE_HASRAM(st) ((st) == VM_DATAPART_STATE_INCORE || (st) == VM_DATAPART_STATE_LOCKED)
	/* State-specific data part meta-information. */
	union {
		struct {
			struct vm_ramblock    *rd_blockv;  /* [lock(dp_lock)][1..rd_blockc][owned_if(. != &rd_block0)]
			                                    * Vector of ram blocks. */
			union {
				struct vm_ramblock rd_block0;  /* [lock(dp_lock)][valid_if(rd_blockv == &rd_block0)]
				                                * Inline-allocated space for a single memory block. */
				size_t             rd_blockc;  /* [lock(dp_lock)][!0][valid_if(rd_blockv != &rd_block0)]
				                                * Amount of ram blocks. */
			};
		}                          dp_ramdata; /* [VM_DATAPART_STATE_INCORE || VM_DATAPART_STATE_LOCKED] */
#ifndef CONFIG_NO_SWAP
		struct {
			struct vm_swpblock    *sd_blockv;  /* [lock(dp_lock)][1..sd_blockc][owned_if(. != &sd_block0)]
			                                    * Vector of swap blocks. */
			union {
				struct vm_swpblock sd_block0;  /* [lock(dp_lock)][valid_if(sd_blockv == &sd_block0)]
				                                * Inline-allocated space for a single swap block. */
				size_t             sd_blockc;  /* [lock(dp_lock)][!0][valid_if(sd_blockv != &sd_block0)]
				                                * Amount of swap blocks. */
			};
		}                          dp_swpdata; /* [VM_DATAPART_STATE_INSWAP] */
#endif /* !CONFIG_NO_SWAP */
	};
	union {                                    /* Bitset of per-page properties. */
		/* NOTE: Modifications to these property bitsets only require a read-lock on `dp_lock' */
		WEAK uintptr_t             dp_pprop;   /* [lock(READ(dp_lock))][valid_if(!VM_DATAPART_FLAG_HEAPPPP)] Inline bitset. */
		WEAK uintptr_t            *dp_pprop_p; /* [lock(READ(dp_lock))][0..CEILDIV(vm_datapart_numdpages(self),BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS)]
		                                        * [valid_if(VM_DATAPART_FLAG_HEAPPPP)][owned][lock(dp_lock)]
		                                        * Dynamically allocated bitset (or `NULL' when all pages have a state
		                                        * identical to `VM_DATAPART_PPP_INITIALIZED', and changes are not
		                                        * required for tracking, also requiring that `VM_DATAPART_FLAG_TRKCHNG'
		                                        * not be set) */
	};
	struct vm_futex_controller    *dp_futex;   /* [0..1][lock(dp_lock)][owned] Futex support controller.
	                                            * Lazily allocated/de-allocated as futex objects are being used.
	                                            * NOTE: For the duration of at least one futex object existing,
	                                            *       this field can be considered `[1..1][const]'
	                                            *       However, you still may not dereference this field from
	                                            *      `struct vm_futex::f_part' without first acquiring `dp_lock',
	                                            *       since there exists a chance that the associated is currently
	                                            *       being split, and that the futex is currently being moved
	                                            *       to the data part then responsible for the upper half of memory.
	                                            *       The only case where this does not apply is you dereference the
	                                            *      `f_part' pointer of a futex object with a reference counter of
	                                            *       ZERO(0), since this would guaranty that the futex will not be
	                                            *       carried over during a potential data-part split, as the process
	                                            *       of splitting a data part containing futex objects also involves
	                                            *       first acquiring references to all those futex objects in order
	                                            *       to ensure a consistent set of those futex objects that are
	                                            *       still alive (in other words: `vm_futex_destroy()' is allowed to,
	                                            *       and as a matter of fact: _is_ dereferencing this field) */
};

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_free)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_destroy)(struct vm_datapart *__restrict self,
                                   bool is_zero DFL(false));
DEFINE_REFCOUNT_FUNCTIONS(struct vm_datapart, dp_refcnt, vm_datapart_destroy);


/* Decrement the reference counter of `self', and try to merge it with sibling data parts.
 * This functionality is combined with a decref() since a data part can only be merged when
 * it is only visible from within its own data block, or for any VM mapping, the latter only
 * allowing the part to the merged if _all_ mappings are laid out in a way that has the part
 * be mapped alongside its closest siblings in a continuous memory mapping.
 * Note that a data part will never be merged if it has any outside references which would
 * keep it being visible outside the small region that is controllable by the part itself.
 * These references are: `self->dp_block->db_parts*' (1), `self->dp_crefs*' (n) and `self->dp_srefs*' (n)
 *                        Should references exist beyond those explainable via these pointers, plus
 *                        one additional reference that is gifted to this function by its caller, merging
 *                        will not be done.
 * If merging is impossible for any other reason (blocking locks, insufficient memory, etc.), the
 * operation will stop, and the function behaves identical to a regular `decref(self)' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_decref_and_merge)(REF struct vm_datapart *__restrict self);


FUNDEF NONNULL((1)) void KCALL vm_datapart_lock_read(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void KCALL vm_datapart_lock_write(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) bool KCALL vm_datapart_lock_upgrade(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(KCALL vm_datapart_lock_read_nx)(struct vm_datapart *__restrict self);
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(KCALL vm_datapart_lock_write_nx)(struct vm_datapart *__restrict self);
FUNDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(KCALL vm_datapart_lock_upgrade_nx)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) WUNUSED bool NOTHROW(KCALL vm_datapart_lock_tryread)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) WUNUSED bool NOTHROW(KCALL vm_datapart_lock_trywrite)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) WUNUSED bool NOTHROW(KCALL vm_datapart_lock_tryupgrade)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_datapart_lock_endwrite)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_datapart_lock_endread)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_datapart_lock_end)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_datapart_lock_downgrade)(struct vm_datapart *__restrict self);
#define vm_datapart_lock_reading(self)   shared_rwlock_reading(&(self)->dp_lock)
#define vm_datapart_lock_writing(self)   shared_rwlock_writing(&(self)->dp_lock)
#define vm_datapart_lock_canread(self)   shared_rwlock_canread(&(self)->dp_lock)
#define vm_datapart_lock_canwrite(self)  shared_rwlock_canwrite(&(self)->dp_lock)
#define vm_datapart_lock_pollread(self)  shared_rwlock_pollread(&(self)->dp_lock)
#define vm_datapart_lock_pollwrite(self) shared_rwlock_pollwrite(&(self)->dp_lock)

/* Define C++ sync API hooks. */
__DEFINE_SYNC_RWLOCK(struct vm_datapart,
                     vm_datapart_lock_tryread,
                     vm_datapart_lock_read,
                     vm_datapart_lock_read_nx,
                     vm_datapart_lock_endread,
                     vm_datapart_lock_reading,
                     vm_datapart_lock_canread,
                     vm_datapart_lock_trywrite,
                     vm_datapart_lock_write,
                     vm_datapart_lock_write_nx,
                     vm_datapart_lock_endwrite,
                     vm_datapart_lock_writing,
                     vm_datapart_lock_canwrite,
                     vm_datapart_lock_end,
                     vm_datapart_lock_tryupgrade,
                     vm_datapart_lock_upgrade,
                     vm_datapart_lock_upgrade_nx,
                     vm_datapart_lock_downgrade)
__DEFINE_SYNC_POLL(struct vm_datapart,
                   vm_datapart_lock_pollread,
                   vm_datapart_lock_pollwrite)



#ifdef __INTELLISENSE__
/* The size of the given datapart, either in data-pages, or in virt-pages.
 * NOTE: The caller must be holding a read-lock on `self', or `self' must not be shared.
 * DATA-PAGES: Usually same as `virt-pages', but often 512-bytes large for files.
 * VIRT-PAGES: Same as `pageid_t' (PAGESIZE-bytes large) */
NOBLOCK size_t NOTHROW(KCALL vm_datapart_numbytes)(struct vm_datapart const *__restrict self);  /* TODO: Fix-up users of this macro that cast the return value to u64 */
NOBLOCK size_t NOTHROW(KCALL vm_datapart_numdpages)(struct vm_datapart const *__restrict self); /* TODO: Fix-up users of this macro that cast the return value to u64 */
NOBLOCK size_t NOTHROW(KCALL vm_datapart_numvpages)(struct vm_datapart const *__restrict self);
NOBLOCK pos_t NOTHROW(KCALL vm_datapart_minbyte)(struct vm_datapart const *__restrict self);
NOBLOCK datapage_t NOTHROW(KCALL vm_datapart_mindpage)(struct vm_datapart const *__restrict self);
NOBLOCK vm_vpage64_t NOTHROW(KCALL vm_datapart_minvpage)(struct vm_datapart const *__restrict self);
NOBLOCK pos_t NOTHROW(KCALL vm_datapart_maxbyte)(struct vm_datapart const *__restrict self);
NOBLOCK datapage_t NOTHROW(KCALL vm_datapart_maxdpage)(struct vm_datapart const *__restrict self);
NOBLOCK vm_vpage64_t NOTHROW(KCALL vm_datapart_maxvpage)(struct vm_datapart const *__restrict self);
NOBLOCK pos_t NOTHROW(KCALL vm_datapart_startbyte)(struct vm_datapart const *__restrict self);
NOBLOCK datapage_t NOTHROW(KCALL vm_datapart_startdpage)(struct vm_datapart const *__restrict self);
NOBLOCK vm_vpage64_t NOTHROW(KCALL vm_datapart_startvpage)(struct vm_datapart const *__restrict self);
NOBLOCK pos_t NOTHROW(KCALL vm_datapart_endbyte)(struct vm_datapart const *__restrict self);
NOBLOCK datapage_t NOTHROW(KCALL vm_datapart_enddpage)(struct vm_datapart const *__restrict self);
NOBLOCK vm_vpage64_t NOTHROW(KCALL vm_datapart_endvpage)(struct vm_datapart const *__restrict self);
#else /* __INTELLISENSE__ */
#define vm_datapart_numbytes(self)   ((size_t)(((self)->dp_tree.a_vmax - (self)->dp_tree.a_vmin) + 1) << VM_DATABLOCK_ADDRSHIFT((self)->dp_block))
#define vm_datapart_numdpages(self)  ((size_t)(((self)->dp_tree.a_vmax - (self)->dp_tree.a_vmin) + 1))
#define vm_datapart_numvpages(self)  ((size_t)(((self)->dp_tree.a_vmax - (self)->dp_tree.a_vmin) + 1) >> VM_DATABLOCK_PAGESHIFT((self)->dp_block))
#define vm_datapart_minbyte(self)    ((pos_t)(self)->dp_tree.a_vmin << VM_DATABLOCK_ADDRSHIFT((self)->dp_block))
#define vm_datapart_mindpage(self)   ((datapage_t)(self)->dp_tree.a_vmin)
#define vm_datapart_minvpage(self)   ((vm_vpage64_t)(self)->dp_tree.a_vmin >> VM_DATABLOCK_PAGESHIFT((self)->dp_block))
#define vm_datapart_maxbyte(self)    ((((pos_t)(self)->dp_tree.a_vmax + 1) << VM_DATABLOCK_ADDRSHIFT((self)->dp_block)) - 1)
#define vm_datapart_maxdpage(self)   ((datapage_t)(self)->dp_tree.a_vmax)
#define vm_datapart_maxvpage(self)   ((vm_vpage64_t)((self)->dp_tree.a_vmax >> VM_DATABLOCK_PAGESHIFT((self)->dp_block)))
#define vm_datapart_startbyte(self)  vm_datapart_minbyte(self)
#define vm_datapart_startdpage(self) vm_datapart_mindpage(self)
#define vm_datapart_startvpage(self) vm_datapart_minvpage(self)
#define vm_datapart_endbyte(self)    (((pos_t)(self)->dp_tree.a_vmax + 1) << VM_DATABLOCK_ADDRSHIFT((self)->dp_block))
#define vm_datapart_enddpage(self)   ((datapage_t)(self)->dp_tree.a_vmax + 1)
#define vm_datapart_endvpage(self)   (vm_datapart_maxvpage(self) + 1)
#endif /* !__INTELLISENSE__ */


/* Allocate/free ram/swap data for the given data part.
 * NOTE: The caller must be holding a write-lock to `self'
 * NOTE: When the functions return by throwing an error,
 *       the caller's write-lock to `self' will have already
 *       been released!
 * NOTE: When allocating, these functions will set the part's
 *       state to either INCORE, LOCKED or INSWAP upon success.
 * @return: * : One of VM_DATAPART_ALLOC_*. */
FUNDEF NONNULL((1)) unsigned int KCALL vm_datapart_allocram(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NONNULL((1)) unsigned int KCALL vm_datapart_allocswap(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NONNULL((1)) unsigned int NOTHROW(KCALL vm_datapart_allocram_nx)(struct vm_datapart *__restrict self, gfp_t flags);
FUNDEF NONNULL((1)) unsigned int NOTHROW(KCALL vm_datapart_allocswap_nx)(struct vm_datapart *__restrict self, gfp_t flags);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_datapart_freeram)(struct vm_datapart *__restrict self, bool is_zero DFL(false));
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_datapart_freeswap)(struct vm_datapart *__restrict self);
#define VM_DATAPART_ALLOC_FAILURE        0 /* Failed to allocate memory (Only returned by `*_nx' variants). */
#define VM_DATAPART_ALLOC_SUCCESS        1 /* Successfully allocated memory. */
#define VM_DATAPART_ALLOC_SUCCESS_RELOCK 2 /* Successfully allocated memory, but `self' was unlocked temporarily */
#define VM_DATAPART_ALLOC_CHANGED_RELOCK 3 /* Following a re-lock, the state of `self' is no longer `VM_DATAPART_STATE_ABSENT'
                                            * In this case, the caller re-inherits a new lock to `self', but the part's state
                                            * is not what they would have expected it to be. */

/* Similar to `vm_datapart_allocram()', but leave all locking & state changes up to the caller. */
FUNDEF NONNULL((1)) void KCALL
vm_datapart_do_allocram(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NONNULL((1)) NOBLOCK_IF(flags & GFP_ATOMIC) bool
NOTHROW(KCALL vm_datapart_do_allocram_nx)(struct vm_datapart *__restrict self, gfp_t flags);
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_do_ccfreeram)(struct vm_datapart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_do_ffreeram)(struct vm_datapart *__restrict self, bool is_zero);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_do_freeram)(struct vm_datapart *__restrict self);
#else /* __INTELLISENSE__ */
#define vm_datapart_do_ccfreeram(self) \
	vm_do_ccfreeram(&(self)->dp_ramdata.rd_block0, (self)->dp_ramdata.rd_blockv)
#define vm_datapart_do_ffreeram(self, is_zero) \
	vm_do_ffreeram(&(self)->dp_ramdata.rd_block0, (self)->dp_ramdata.rd_blockv, is_zero)
#define vm_datapart_do_freeram(self) \
	vm_do_freeram(&(self)->dp_ramdata.rd_block0, (self)->dp_ramdata.rd_blockv)
#endif /* !__INTELLISENSE__ */

/* Copy the physical memory backing of `src' into `dst'.
 * The caller is responsible to ensure that both parts are INCORE or LOCKED,
 * as well as to provide for both parts to be properly locked. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_do_copyram)(struct vm_datapart *__restrict dst,
                                      struct vm_datapart *__restrict src);

/* Allocate physical memory (intended for use by datablocks)
 * @param: pblock0:   A pointer to a union of `struct vm_ramblock *' and `size_t *',
 *                    the first of which will be filled if the allocation was possible
 *                    using only a single chunk of physical memory (and `return == pblock0').
 *                    In case more than 1 ramblock was needed, a pointer to a heap-allocated
 *                    vector of ram-blocks is returned, and it's length is written to
 *                   `*(size_t *)pblock0'
 * @param: num_pages: The total number of physical pages of memory that need to be allocated.
 * @param: flags:     Heap flags used for allocating the heap vector when more than 1 block is used.
 *                    NOTE: It is recommended to pass `GFP_LOCKED | GFP_PREFLT | GFP_VCBASE'
 * @return: pblock0:  A single block was used.
 * @return: * :       A pointer to a kmalloc()-allocated heap vector of used ram blocks.
 * @return: NULL:    [vm_do_allocram_nx] Failed to allocate physical memory, or the required heap vector. */
FUNDEF NONNULL((1)) ATTR_RETNONNULL NOBLOCK_IF(flags & GFP_ATOMIC) struct vm_ramblock *KCALL
vm_do_allocram(struct vm_ramblock *__restrict pblock0, pagecnt_t num_pages, gfp_t flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NONNULL((1)) NOBLOCK_IF(flags & GFP_ATOMIC) struct vm_ramblock *
NOTHROW(KCALL vm_do_allocram_nx)(struct vm_ramblock *__restrict pblock0,
                                 pagecnt_t num_pages, gfp_t flags);
/* Free RAM allocated by `vm_do_allocram(_nx)'
 * NOTE: This function assumes that the allocated memory hasn't been used, yet. */
FUNDEF NONNULL((1, 2)) NOBLOCK void
NOTHROW(KCALL vm_do_ccfreeram)(struct vm_ramblock *__restrict pblock0,
                               struct vm_ramblock *__restrict blocks);
FUNDEF NONNULL((1, 2)) NOBLOCK void
NOTHROW(KCALL vm_do_ffreeram)(struct vm_ramblock *__restrict pblock0,
                              struct vm_ramblock *__restrict blocks,
                              bool is_zero);
FUNDEF NONNULL((1, 2)) NOBLOCK void
NOTHROW(KCALL vm_do_freeram)(struct vm_ramblock *__restrict pblock0,
                             struct vm_ramblock *__restrict blocks);

/* Map the given data part (which must be INCORE or LOCKED) into the current
 * page directory at the specified location, using the specified permissions.
 * NOTE: The caller is responsible to ensure that `self' doesn't change state
 *       or size, as well as to ensure that the given address range isn't already
 *       in use. - This function is merely a thin wrapper around `pagedir_map',
 *       which automatically allows for dealing with multi-part ram blocks.
 * NOTE: The caller is responsible to ensure that the target region of memory
 *       has been prepared in a prior call to `pagedir_prepare_map'
 * @param: perm: Set of `PAGEDIR_MAP_F*' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram)(struct vm_datapart *__restrict self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr, u16 perm);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_p)(struct vm_datapart *__restrict self,
                                     PAGEDIR_P_SELFTYPE pdir,
                                     PAGEDIR_PAGEALIGNED VIRT void *addr, u16 perm);

/* Same as `vm_datapart_map_ram()', but automatically restrict permissions:
 *  - Pages not fully marked as changed are mapped as read-only, unless
 *    the `VM_DATAPART_FLAG_TRKCHNG' bit isn't set in `self'
 *  - Pages not fully initialized are mapped as invalid-access, meaning
 *    that a page-fault will be triggered upon first use of that memory.
 * @param: perm: Set of `PAGEDIR_MAP_F*' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_autoprop)(struct vm_datapart *__restrict self,
                                            PAGEDIR_PAGEALIGNED VIRT void *addr,
                                            u16 perm);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_map_ram_autoprop_p)(struct vm_datapart *__restrict self,
                                              PAGEDIR_P_SELFTYPE pdir,
                                              PAGEDIR_PAGEALIGNED VIRT void *addr,
                                              u16 perm);


/* Check if the given datapart `self' has modified
 * data pages within the specified address range.
 * NOTE: The caller must be holding any kind of lock that prevents `self'
 *       from having its length changed (aka. a VM-tree read-lock of a VM
 *       that is mapping `self', a read-lock to `self', or a read-lock to
 *       the associated data-block, so-long as `self' hasn't been anonymized) */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL vm_datapart_haschanged)(struct vm_datapart *__restrict self,
                                      size_t partrel_min_dpage DFL(0),
                                      size_t partrel_max_dpage DFL((size_t)-1));

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
FUNDEF NONNULL((1)) size_t KCALL
vm_datapart_sync(struct vm_datapart *__restrict self,
                 size_t partrel_min_dpage DFL(0),
                 size_t partrel_max_dpage DFL((size_t)-1),
                 bool recheck_modifications_before_remap DFL(false))
		THROWS(E_WOULDBLOCK, ...);


/* Directly copy memory to/from the given buffer and `self'
 * NOTE: These functions automatically deal with page properties, such
 *       that `vm_datapart_do_read()' will ensure INITIALIZED pages, whilst
 *       `vm_datapart_do_write()' ensures HASCHANGED pages (so-long as the
 *       TRACKCHANGES bit is set)
 * NOTE: The caller must be holding a read-lock to `self', as well as ensure
 *       that `self' is either INCORE or LOCKED */
FUNDEF NONNULL((1)) void KCALL vm_datapart_do_read(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, size_t src_offset) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vm_datapart_do_write(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, size_t dst_offset) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vm_datapart_do_read_phys(struct vm_datapart *__restrict self, vm_phys_t dst, size_t num_bytes, size_t src_offset) THROWS(...);
FUNDEF NONNULL((1)) void KCALL vm_datapart_do_write_phys(struct vm_datapart *__restrict self, vm_phys_t src, size_t num_bytes, size_t dst_offset) THROWS(...);

/* Same as `vm_datapart_do_read()' / `vm_datapart_do_write()', but copy memory
 * into the supplied user-space buffer `dst' / `src' using `memcpy_nopf()', meaning
 * that these functions will never cause the given buffer to become faulted, or invoke
 * VIO callbacks in case the given buffer is a VIO memory mapping.
 * @return: * : The number of trailing bytes from the given buffer that could not be
 *              accessed (i.e. memcpy_nopf() returned non-zero upon attempting to access
 *              them). When this is non-zero, then the caller should manually access the
 *              affected byte (_after_ releasing their lock on `self'), then proceed to
 *              re-acquire the lock on `self', before manually reading/writing the single
 *              byte previously read/allocated, before finally moving on to reading/writing
 *              into the remainder of the original buffer, once again allowing for user-space
 *              memory faults. */
FUNDEF NONNULL((1)) size_t KCALL vm_datapart_do_read_nopf(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, size_t src_offset) THROWS(...);
FUNDEF NONNULL((1)) size_t KCALL vm_datapart_do_write_nopf(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, size_t dst_offset) THROWS(...);


/* Read/write data to/from the given data part.
 * NOTE: When given a virtual memory buffer, these functions automatically
 *       check if the memory backing that buffer could potentially overlap
 *       with `self', in which case reading is performed using an intermediate
 *       buffer, so-as to prevent a possible dead-lock when `self' is already
 *       locked, whilst a #PF caused by writing to the target buffer attempts
 *       to acquire another lock to `self'
 * NOTE: The caller must _NOT_ be holding any lock to `self', the associated
 *       block, or any VM-tree when calling this function.
 * @param: split_bytes: The number of bytes after which to split the part in
 *                      order to minimize the memory impact of copy-on-write.
 *                      Usually the same as `num_bytes'
 * @return: * : The number of read/written bytes (limited by `num_bytes',
 *              and `vm_datapart_numbytes(self) - (src|dst)_offset'). */
FUNDEF NONNULL((1)) size_t KCALL vm_datapart_read(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, size_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL vm_datapart_write(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, size_t split_bytes, size_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL vm_datapart_read_phys(struct vm_datapart *__restrict self, vm_phys_t dst, size_t num_bytes, size_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) size_t KCALL vm_datapart_write_phys(struct vm_datapart *__restrict self, vm_phys_t src, size_t num_bytes, size_t split_bytes, size_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL vm_datapart_readv(struct vm_datapart *__restrict self, struct aio_buffer const *__restrict buf, size_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL vm_datapart_writev(struct vm_datapart *__restrict self, struct aio_buffer const *__restrict buf, size_t split_bytes, size_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL vm_datapart_readv_phys(struct vm_datapart *__restrict self, struct aio_pbuffer const *__restrict buf, size_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL vm_datapart_writev_phys(struct vm_datapart *__restrict self, struct aio_pbuffer const *__restrict buf, size_t split_bytes, size_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as the `vm_datapart_(read|write)', however make the assumption that the
 * memory backing is `safe' (i.e. access could never cause a #PF attempting to
 * acquire a lock to `self' when doing so is impossible; i.e. `dst'/`src' are
 * guarantied to not be apart of a mapping of `self', or be otherwise accessed
 * by code called from a page-fault handler) */
FUNDEF NONNULL((1, 2)) size_t KCALL vm_datapart_read_unsafe(struct vm_datapart *__restrict self, void *__restrict dst, size_t num_bytes, size_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL vm_datapart_write_unsafe(struct vm_datapart *__restrict self, void const *__restrict src, size_t num_bytes, size_t split_bytes, size_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);

/* Read/Write memory to/from the given data part without causing a #PF due
 * to access made to the given `dst'/`src' buffers (s.a. `memcpy_nopf()').
 * @assume(num_bytes <= SSIZE_MAX);
 * @return: >= 0:
 *     Successfully transferred all possible data in regards to the actual size
 *     of `self' encountered when the lock associated with it was held. This may
 *     be less than num_bytes' in case the data part ended up being smaller that
 *     the given buffer, where it should be noted that a data part can shrink at
 *     any time that its lock isn't being held due to possibly getting split by
 *     another thread.
 * @return: < 0:
 *     Failed to read/write the last `-return' bytes of the given buffer,
 *     as accessing them triggers a #PF for the range:
 *         `(dst|src) + (num_bytes - (size_t)(-return)) ... (dst|src) + num_bytes - 1'
 *     As such, the first `num_bytes - (size_t)(-return)' bytes were successfully
 *     read/written, and the caller should not attempt to read/write them again, but
 *     should instead manually read/write at least 1 byte starting at:
 *         `((byte_t *)(dst|src))[num_bytes - (size_t)(-return)]'
 *     using a temporary buffer, in order to allow the associated memory mapping to
 *     be faulted while not holding any locks to VM control structures, also allowing
 *     for the proper handling in case the memory associated with `dst'/`src' is backed
 *     by a VIO memory mapping. */
FUNDEF NONNULL((1, 2)) ssize_t KCALL
vm_datapart_read_nopf(struct vm_datapart *__restrict self,
                      USER CHECKED void *dst, size_t num_bytes,
                      size_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) ssize_t KCALL
vm_datapart_write_nopf(struct vm_datapart *__restrict self,
                       USER CHECKED void const *src, size_t num_bytes,
                       size_t split_bytes, size_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Perform I/O using an intermediate buffer, thus solving the deadlock
 * scenario possible when using `vm_datapart_(read|write)_unsafe', as
 * well as to perform the faulting/vio-interaction needed when a call
 * to `vm_datapart_(read|write)_nopf()' returned a negative value.
 * Even though they can, these functions should _not_ be used to transfer
 * a data part in its entirety, since they rely on a limited-size buffer
 * allocated on the kernel stack, meaning that their use requires the
 * indirection of an intermediate memory location.
 * In general, raw I/O on data parts should always be performed with the
 * help of `vm_datapart_(read|write)()', which will automatically try to
 * call the `*_nopf()' function, and fall back for a limited number of
 * bytes to making use of `vm_datapart_(read|write)_buffered()' for handling
 * VIO, as well as faulting memory mappings. (s.a. `vm_prefault()')
 * @return: * : The number of read/written bytes (limited by `num_bytes',
 *              and `vm_datapart_numbytes(self) - (src|dst)_offset'). */
FUNDEF NONNULL((1)) size_t KCALL
vm_datapart_read_buffered(struct vm_datapart *__restrict self,
                          USER CHECKED void *dst, size_t num_bytes,
                          size_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL
vm_datapart_write_buffered(struct vm_datapart *__restrict self,
                           USER CHECKED void const *src, size_t num_bytes,
                           size_t split_bytes, size_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);


/* Enumerate physical memory of `self' within the given address range.
 * NOTE: The caller must be holding a read-lock on `self', as well as ensure
 *       that the given address range is in-bounds, that `self' is either
 *       INCORE or LOCKED, and that `num_bytes' is non-zero. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL vm_datapart_do_enumdma)(struct vm_datapart *__restrict self,
                                      vm_dmarangefunc_t prange, void *arg,
                                      size_t partrel_start, size_t num_bytes,
                                      struct vm_dmalock *__restrict lock);



/* Split the given datapart after `vpage_offset' pages of virtual memory.
 * Additionally, map new nodes within all VMs in with `self' is mapped as part of.
 * NOTE: The caller must not be holding locks to _any_ of those VMs or the given data part itself.
 * @return: * :   A reference to the new upper-half of `self', starting
 *                after `vpage_offset' pages at the end of `self'
 * @return: NULL: The given `vpage_offset >= vm_datapart_numvpages(self)' */
FUNDEF NONNULL((1)) REF struct vm_datapart *KCALL
vm_datapart_split(struct vm_datapart *__restrict self, size_t vpage_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as `vm_datapart_split()', but don't throw an exception if something goes
 * wrong. - Instead, return `VM_DATAPART_SPLIT_NX_FAILED', though `NULL' is still
 * returned in the event that `vpage_offset' is too large. */
FUNDEF NONNULL((1)) REF struct vm_datapart *
NOTHROW(KCALL vm_datapart_split_nx)(struct vm_datapart *__restrict self,
                                    size_t vpage_offset);
#define VM_DATAPART_SPLIT_NX_FAILED ((REF struct vm_datapart *)-1)




/* Acquire a write-lock on `self', and ensure that the part's
 * state is set to the part being loaded as INCORE or LOCKED. */
FUNDEF NONNULL((1)) void FCALL
vm_datapart_lockwrite_setcore(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
/* Acquire a write-lock on `self', and ensure that pages are in-core, and that
 * copy-on-write mappings have been unshared (that is: ensure that `self->dp_crefs == NULL'). */
FUNDEF NONNULL((1)) void FCALL
vm_datapart_lockwrite_setcore_unsharecow(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as the functions above, but only need to acquire a read-lock. */
FUNDEF NONNULL((1)) void (FCALL vm_datapart_lockread_setcore)(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NONNULL((1)) void (FCALL vm_datapart_lockread_setcore_unsharecow)(struct vm_datapart *__restrict self) THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Noexcept variants of the above locking functions. */
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL vm_datapart_lockwrite_setcore_nx)(struct vm_datapart *__restrict self);
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL vm_datapart_lockwrite_setcore_unsharecow_nx)(struct vm_datapart *__restrict self);
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL vm_datapart_lockread_setcore_nx)(struct vm_datapart *__restrict self);
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL vm_datapart_lockread_setcore_unsharecow_nx)(struct vm_datapart *__restrict self);


/* Return the address of a physical page at the given `vpage_offset'
 * The caller must be holding a read- or write-lock on `self',
 * as well as guaranty that the part is either INCORE or LOCKED. */
FUNDEF NOBLOCK NONNULL((1)) pageptr_t
NOTHROW(KCALL vm_datapart_pageaddr)(struct vm_datapart *__restrict self,
                                    size_t vpage_offset);

/* Ensure that the page at `vpage_offset' has been initialized
 * The caller must be holding a read- or write-lock on `self',
 * as well as guaranty that the part is either INCORE or LOCKED.
 * Alternatively, they may also use this function when `!isshared(self)'
 * HINT: The easiest way to ensure this is through
 *       use of `vm_datapart_lockread_setcore()'
 * @param: vpage_offset: The offset of the page to load.
 *                       The caller must ensure that this is `< vm_datapart_numvpages(self)'
 * @param: pchanged: [IN]  If `true', mark the associated page as changed, instead of initialized.
 * @param: pchanged: [OUT] Set to true if all associated data-pages are marked as changed.
 * @return: * : The underlying physical page of memory that is bound to `vpage_offset'
 * @throw: * :  Only throws whatever exception may get thrown by `dt_loadpart', meaning that
 *              when the loadpart function is NOEXCEPT, then so is this function! */
FUNDEF NONNULL((1, 3)) pageptr_t KCALL
vm_datapart_loadpage(struct vm_datapart *__restrict self,
                     size_t vpage_offset,
                     bool *__restrict pchanged)
		THROWS(...);

/* Similar to `vm_datapart_loadpage()', however instead used for accessing only a single data
 * page, rather than a whole virtual memory page. (used to implement `vm_datapart_do_(read|write)[p]') */
FUNDEF NONNULL((1)) vm_phys_t KCALL
vm_datapart_loaddatapage(struct vm_datapart *__restrict self,
                         size_t dpage_offset, bool for_writing)
		THROWS(...);



/* Get the state of a page (one of `VM_DATAPART_PPP_*') */
LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL vm_datapart_getstate)(struct vm_datapart const *__restrict self,
                                    size_t relative_datapageid) {
	__hybrid_assert(relative_datapageid < vm_datapart_numdpages(self));
	if (!(self->dp_flags & VM_DATAPART_FLAG_HEAPPPP)) {
		uintptr_t word;
		word = __hybrid_atomic_load(self->dp_pprop, __ATOMIC_ACQUIRE);
		word >>= relative_datapageid * VM_DATAPART_PPP_BITS;
		return word & VM_DATAPART_PPP_MASK;
	} else {
		uintptr_t word;
		size_t index;
		unsigned int shift;
		if (!self->dp_pprop_p)
			return VM_DATAPART_PPP_HASCHANGED;
		index = /* */ (size_t)(relative_datapageid / (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS));
		shift = (unsigned int)(relative_datapageid % (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS));
		word = __hybrid_atomic_load(self->dp_pprop_p[index], __ATOMIC_ACQUIRE);
		word >>= shift * VM_DATAPART_PPP_BITS;
		return word & VM_DATAPART_PPP_MASK;
	}
}

/* Returns true if the per-page state of `self' is writable. */
LOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(KCALL vm_datapart_isstatewritable)(struct vm_datapart const *__restrict self) {
	if (!(self->dp_flags & VM_DATAPART_FLAG_HEAPPPP))
		return 1;
	return self->dp_pprop_p != NULL;
}

/* Set the state of a page. */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_setstate)(struct vm_datapart *__restrict self,
                                    size_t relative_datapageid,
                                    unsigned int state) {
	__hybrid_assert(!(state & ~VM_DATAPART_PPP_MASK));
	__hybrid_assert(relative_datapageid < vm_datapart_numdpages(self));
	if (!(self->dp_flags & VM_DATAPART_FLAG_HEAPPPP)) {
		uintptr_t valmask, newmask, oldword;
		unsigned int shift;
		shift   = (unsigned int)relative_datapageid * VM_DATAPART_PPP_BITS;
		valmask = (uintptr_t)VM_DATAPART_PPP_MASK << shift;
		newmask = (uintptr_t)state << shift;
		do {
			oldword = __hybrid_atomic_load(self->dp_pprop, __ATOMIC_ACQUIRE);
		} while (!__hybrid_atomic_cmpxch_weak(self->dp_pprop,
		                                      oldword, (oldword & ~valmask) | newmask,
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	} else {
		size_t index;
		unsigned int shift;
		uintptr_t valmask, newmask, oldword;
		__hybrid_assert(self->dp_pprop_p);
		index = /* */ (size_t)(relative_datapageid / (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS));
		shift = (unsigned int)(relative_datapageid % (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS));
		shift *= VM_DATAPART_PPP_BITS;
		valmask = (uintptr_t)VM_DATAPART_PPP_MASK << shift;
		newmask = (uintptr_t)state << shift;
		do {
			oldword = __hybrid_atomic_load(self->dp_pprop_p[index], __ATOMIC_ACQUIRE);
		} while (!__hybrid_atomic_cmpxch_weak(self->dp_pprop_p[index],
		                                      oldword, (oldword & ~valmask) | newmask,
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	}
}

/* Atomically compare-exchange the state of a page,
 * returning true/false if the exchange was successful. */
LOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(KCALL vm_datapart_cmpxchstate)(struct vm_datapart *__restrict self,
                                       size_t relative_datapageid,
                                       unsigned int oldval,
                                       unsigned int newval) {
	__hybrid_assert(!(oldval & ~VM_DATAPART_PPP_MASK));
	__hybrid_assert(!(newval & ~VM_DATAPART_PPP_MASK));
	__hybrid_assert(relative_datapageid < vm_datapart_numdpages(self));
	if (!(self->dp_flags & VM_DATAPART_FLAG_HEAPPPP)) {
		unsigned int shift;
		uintptr_t valmask, oldmask, newmask, oldword;
		shift   = (unsigned int)relative_datapageid * VM_DATAPART_PPP_BITS;
		valmask = (uintptr_t)VM_DATAPART_PPP_MASK << shift;
		oldmask = (uintptr_t)oldval << shift;
		newmask = (uintptr_t)newval << shift;
		do {
			oldword = __hybrid_atomic_load(self->dp_pprop, __ATOMIC_ACQUIRE);
			if ((oldword & valmask) != oldmask)
				return 0;
		} while (!__hybrid_atomic_cmpxch_weak(self->dp_pprop,
		                                      oldword, (oldword & ~valmask) | newmask,
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	} else {
		size_t index;
		unsigned int shift;
		uintptr_t valmask, oldmask, newmask, value;
		__hybrid_assert(self->dp_pprop_p);
		index = /* */ (size_t)(relative_datapageid / (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS));
		shift = (unsigned int)(relative_datapageid % (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS));
		shift *= VM_DATAPART_PPP_BITS;
		valmask = (uintptr_t)VM_DATAPART_PPP_MASK << shift;
		oldmask = (uintptr_t)oldval << shift;
		newmask = (uintptr_t)newval << shift;
		do {
			value = __hybrid_atomic_load(self->dp_pprop_p[index], __ATOMIC_ACQUIRE);
			if ((value & valmask) != oldmask)
				return 0;
		} while (!__hybrid_atomic_cmpxch_weak(self->dp_pprop_p[index],
		                                      value, (value & ~valmask) | newmask,
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	}
	return 1;
}







#ifndef __poll_mode_t_defined
#define __poll_mode_t_defined 1
typedef unsigned int poll_mode_t; /* Set of `POLL*' */
#endif /* !poll_mode_t_defined */

struct vm_datablock_type {
	/* [0..1] Finalize + free the given data-block. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/ (KCALL *dt_destroy)(struct vm_datablock *__restrict self);
	/* [0..1] Initialize the given data part (called whenever a new part is created)
	 * NOTE: This function isn't required to do anything, and may assume that the
	 *       given part is already fully initialized as ABSENT, with the proper
	 *       address range already assigned.
	 * This function is mainly intended to assign physical memory ranges for data blocks
	 * that directly map physical memory into virtual memory, allowing them to use this
	 * function to assign the proper memory ranges. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/ (KCALL *dt_initpart)(struct vm_datapart *__restrict part);
	/* [0..1] Initialize the data buffer.
	 * @assume(num_data_pages != 0);
	 * @assume(IS_ALIGNED(buffer, VM_DATABLOCK_PAGESIZE(self)));
	 * NOTE: `num_data_pages' refers to data-pages, not physical pages! */
	NONNULL((1)) void (KCALL *dt_loadpart)(struct vm_datablock *__restrict self, datapage_t start, vm_phys_t buffer, size_t num_data_pages);
	/* [0..1] Save the given data buffer.
	 * @assume(num_data_pages != 0);
	 * @assume(IS_ALIGNED(buffer, VM_DATABLOCK_PAGESIZE(self)));
	 * NOTE: `num_data_pages' refers to data-pages, not physical pages! */
	NONNULL((1)) void (KCALL *dt_savepart)(struct vm_datablock *__restrict self, datapage_t start, vm_phys_t buffer, size_t num_data_pages);
	/* [0..1] Called the first time the `VM_DATAPART_FLAG_CHANGED' flag is set for `part'.
	 * WARNING: While this function is allowed to block and throw exceptions,
	 *          you should rather think of it as being required to be NOBLOCK,
	 *          as it may be called from within the page-fault handler. */
	NONNULL((1, 2)) void (KCALL *dt_changed)(struct vm_datablock *__restrict self, struct vm_datapart *__restrict part);
	/* TODO: `dt_accessed'  (invoked whenever a part is loaded into the core)
	 *        Meant to update the `st_atime' field of a memory-mapped file. */

	/* [0..1] Optional operators for when read(2) or write(2) is used with
	 *        a file descriptor pointing to a vm_datablock of this type.
	 * These callbacks are used by UVIO datablocks to implement the
	 * server/client architecture for user-space driven VIO emulation. */
	WUNUSED NONNULL((1)) size_t
	(KCALL *dt_handle_read)(struct vm_datablock *__restrict self,
	                        USER CHECKED void *dst,
	                        size_t num_bytes, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1)) size_t
	(KCALL *dt_handle_write)(struct vm_datablock *__restrict self,
	                         USER CHECKED void const *src,
	                         size_t num_bytes, iomode_t mode) THROWS(...);
	/* [0..1] Same as above, but used when polling for data being available.
	 * When not implemented (i.e. when set to `NULL'), poll is implemented for
	 * the datablock through use of `rwlock_poll(read|write)(&self->db_lock)' */
	WUNUSED NONNULL((1)) poll_mode_t
	(KCALL *dt_handle_poll)(struct vm_datablock *__restrict self,
	                        poll_mode_t what) THROWS(...);
};


/* Value for `db_parts' when all parts are not tracked as shared, but are instead
 * newly allocated each time they are accessed through `vm_paged_datablock_locatepart()'. */
#define VM_DATABLOCK_ANONPARTS      ((struct vm_datapart *)-1)
#define VM_DATABLOCK_ANONPARTS_INIT VM_DATABLOCK_ANONPARTS


#ifdef LIBVIO_CONFIG_ENABLED
struct vio_operators;
#endif /* LIBVIO_CONFIG_ENABLED */

struct vm_datablock {
	/* An infinite-length data block descriptor, used to refer
	 * to the contents, and represent ownership of memory, both
	 * shared, and private.
	 * Its most important distinction is its ability to track all
	 * nodes that are mapping some portion of it, as well as its
	 * use by the filesystem, as every file-INode contains a
	 * vm_datablock that is used to address the INode's file
	 * contents when mapped in memory. */
	WEAK refcnt_t                       db_refcnt; /* Reference counter. */
	struct rwlock                       db_lock;   /* Lock for this data block.
	                                                * HINT: You can poll the signal of this lock if you wish to wait
	                                                *       for changes in parts where changes must be tracked. */
	struct vm_datablock_type const     *db_type;   /* [1..1][const] The type descriptor for this datablock. */
#ifdef LIBVIO_CONFIG_ENABLED
	struct vio_operators const         *db_vio;    /* [0..1][const] VIO callbacks (or NULL if the datablock doesn't use VIO). */
#endif /* LIBVIO_CONFIG_ENABLED */
	REF LLIST(struct vm_datapart)       db_parts;  /* [0..1][lock(db_lock)] The first part of this datablock.
	                                                * NOTE: When set to `VM_DATABLOCK_ANONPARTS', new parts are always
	                                                *       allocated anonymously, and never added to the actual datablock.
	                                                * NOTE: Due the process of anonymizing a data block, this field is set
	                                                *       to `VM_DATABLOCK_ANONPARTS', as is done when (e.g.) the associated
	                                                *       file gets deleted. */
	/* Page index conversion.
	 * NOTE: This can entirely be ignored for most data
	 *       blocks which simply fill in these members as:
	 * >> db_pageshift = 0;
	 * >> db_addrshift = PAGESHIFT;
	 * >> db_pagealign = 1;
	 * >> db_pagemask  = 0;
	 * >> db_pagesize  = PAGESIZE; */
	unsigned int              db_pageshift; /* [const][<= PAGESHIFT] Shift applied to page indices for converting between
	                                         * `pageid_t' and `datapage_t', or `uintptr_t' and `pos_t' or `pos_t'.
	                                         * -> Since loading file data is most efficient when done in blocks,
	                                         *    which are usually 512 bytes large, it would be a waste if any
	                                         *    form of file access that wishes to use VM data-blocks as access
	                                         *    mechanism would always have to load whole pages (usually 4096
	                                         *    bytes) when it is known that this much isn't actually needed.
	                                         * -> In this case, `db_pageshift' could be set to `3', because
	                                         *   (512 << 3) == 4096, thus allowing the page-property vectors
	                                         *    to still have 512-byte precision, while faulting whole pages
	                                         *    simply require to load 8 continuous blocks at once. */
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
	unsigned int              db_addrshift; /* [const][== PAGESHIFT - db_pageshift]
	                                         * Shift that must be applied to convert between `datapage_t' and `pos_t' or `pos_t' or `uintptr_t'. */
	size_t                    db_pagealign; /* [const][== 1 << db_pageshift]
	                                         * The minimum alignment for the `vm_datapart_startdpage()' / `vm_datapart_enddpage()'
	                                         * of any data part found within this data block.
	                                         * The start, end and size (in data-pages) of any part must therefor be aligned by this. */
	size_t                    db_pagemask;  /* [const][== (1 << db_pageshift) - 1]
	                                         * The mask of bits that must be zero for the start, end and size (in data-pages) of any data-part. */
	size_t                    db_pagesize;  /* [const][== PAGESIZE >> db_pageshift]
	                                         * The size of a single data page (in bytes). */
#endif /* !CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
};


#ifdef LIBVIO_CONFIG_ENABLED
#define VM_DATABLOCK_INIT(type, parts, pageshift) \
	{                                             \
		/* .db_refcnt = */ 1,                     \
		/* .db_lock   = */ RWLOCK_INIT,           \
		/* .db_type   = */ type,                  \
		/* .db_vio    = */ NULL,                  \
		/* .db_parts  = */ parts,                 \
		VM_DATABLOCK_INIT_PAGEINFO(pageshift)     \
	}
#define VM_DATABLOCK_INIT_VIO_EX(type, vio, parts, pageshift) \
	{                                                         \
		/* .db_refcnt = */ 1,                                 \
		/* .db_lock   = */ RWLOCK_INIT,                       \
		/* .db_type   = */ type,                              \
		/* .db_vio    = */ vio,                               \
		/* .db_parts  = */ parts,                             \
		VM_DATABLOCK_INIT_PAGEINFO(pageshift)                 \
	}
#define VM_DATABLOCK_INIT_VIO(vio) \
	VM_DATABLOCK_INIT_VIO_EX(&vm_datablock_anonymous_type, vio, NULL, 0)
#else /* LIBVIO_CONFIG_ENABLED */
#define VM_DATABLOCK_INIT(type, parts, pageshift) \
	{                                             \
		/* .db_refcnt = */ 1,                     \
		/* .db_lock   = */ RWLOCK_INIT,           \
		/* .db_type   = */ type,                  \
		/* .db_parts  = */ parts,                 \
		VM_DATABLOCK_INIT_PAGEINFO(pageshift)     \
	}
#endif /* !LIBVIO_CONFIG_ENABLED */


#define VM_DATABLOCK_PAGESHIFT(x) ((x)->db_pageshift)
#ifdef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
#define VM_DATABLOCK_INIT_PAGEINFO(pageshift) \
	/* .db_pageshift = */ (pageshift)
#else /* CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
#define VM_DATABLOCK_INIT_PAGEINFO(pageshift)             \
	/* .db_pageshift = */ (pageshift),                    \
	/* .db_addrshift = */ PAGESHIFT - (pageshift),        \
	/* .db_pagealign = */ (size_t)1 << (pageshift),       \
	/* .db_pagemask  = */ ((size_t)1 << (pageshift)) - 1, \
	/* .db_pagesize  = */ (size_t)PAGESIZE >> (pageshift)
#define VM_DATABLOCK_ADDRSHIFT(x) ((x)->db_addrshift) /* pos_t >> this == datapage_t */
#define VM_DATABLOCK_PAGEALIGN(x) ((x)->db_pagealign)
#define VM_DATABLOCK_PAGEMASK(x)  ((x)->db_pagemask)
#define VM_DATABLOCK_PAGESIZE(x)  ((x)->db_pagesize)
#endif /* !CONFIG_VM_DATABLOCK_MIN_PAGEINFO */

#ifndef VM_DATABLOCK_ADDRSHIFT
#define VM_DATABLOCK_ADDRSHIFT(x) (PAGESHIFT - VM_DATABLOCK_PAGESHIFT(x))
#endif /* !VM_DATABLOCK_ADDRSHIFT */
#ifndef VM_DATABLOCK_PAGEALIGN
#define VM_DATABLOCK_PAGEALIGN(x) ((size_t)1 << VM_DATABLOCK_PAGESHIFT(x))
#endif /* !VM_DATABLOCK_PAGEALIGN */
#ifndef VM_DATABLOCK_PAGEMASK
#define VM_DATABLOCK_PAGEMASK(x)  (((size_t)1 << VM_DATABLOCK_PAGESHIFT(x)) - 1)
#endif /* !VM_DATABLOCK_PAGEMASK */
#ifndef VM_DATABLOCK_PAGESIZE
#define VM_DATABLOCK_PAGESIZE(x)  ((size_t)PAGESIZE >> VM_DATABLOCK_PAGESHIFT(x))
#endif /* !VM_DATABLOCK_PAGESIZE */


/* Convert between different address types.
 *    datapage_t DPAGE: DataPAGE (usually identical to sector numbers)
 *    pageid_t  VPAGE: VirtualPAGE (Virtual page number, referring to the host's understanding of PAGESIZE)
 *    pos_t     DADDR: DataADDRess (alias for `pos_t', used to specific exact in-file positions)
 *    uintptr_t VADDR: VirtualADDRess (Virtual memory address. - Same as `DADDR', but intended for memory addressing) */
#ifdef __INTELLISENSE__
#define VM_DATABLOCK_DPAGE2DADDR VM_DATABLOCK_DPAGE2DADDR
#define VM_DATABLOCK_DPAGE2VADDR VM_DATABLOCK_DPAGE2VADDR
#define VM_DATABLOCK_DATAPAGE2PAGEID VM_DATABLOCK_DATAPAGE2PAGEID
#define VM_DATABLOCK_DADDR2DPAGE VM_DATABLOCK_DADDR2DPAGE
#define VM_DATABLOCK_VADDR2DPAGE VM_DATABLOCK_VADDR2DPAGE
#define VM_DATABLOCK_PAGEID2DATAPAGE VM_DATABLOCK_PAGEID2DATAPAGE
pos_t VM_DATABLOCK_DPAGE2DADDR(struct vm_datablock const *__restrict self, datapage_t dpage);
uintptr_t VM_DATABLOCK_DPAGE2VADDR(struct vm_datablock const *__restrict self, datapage_t dpage);
pageid_t VM_DATABLOCK_DATAPAGE2PAGEID(struct vm_datablock const *__restrict self, datapage_t dpage);
datapage_t VM_DATABLOCK_DADDR2DPAGE(struct vm_datablock const *__restrict self, pos_t daddr);
datapage_t VM_DATABLOCK_VADDR2DPAGE(struct vm_datablock const *__restrict self, uintptr_t vaddr);
datapage_t VM_DATABLOCK_PAGEID2DATAPAGE(struct vm_datablock const *__restrict self, pageid_t vpage);
#else /* __INTELLISENSE__ */
#define VM_DATABLOCK_DPAGE2DADDR(self, dpage)     ((pos_t)(dpage) << VM_DATABLOCK_ADDRSHIFT(self))
#define VM_DATABLOCK_DPAGE2VADDR(self, dpage)     ((uintptr_t)(dpage) << VM_DATABLOCK_ADDRSHIFT(self))
#define VM_DATABLOCK_DATAPAGE2PAGEID(self, dpage) ((pageid_t)(dpage) >> VM_DATABLOCK_PAGESHIFT(self))
#define VM_DATABLOCK_DADDR2DPAGE(self, daddr)     ((datapage_t)(daddr) >> VM_DATABLOCK_ADDRSHIFT(self))
#define VM_DATABLOCK_VADDR2DPAGE(self, vaddr)     ((datapage_t)(vaddr) >> VM_DATABLOCK_ADDRSHIFT(self))
#define VM_DATABLOCK_PAGEID2DATAPAGE(self, vpage) ((datapage_t)(vpage) << VM_DATABLOCK_PAGESHIFT(self))
#endif /* !__INTELLISENSE__ */

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datablock_destroy)(struct vm_datablock *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct vm_datablock,db_refcnt,vm_datablock_destroy);

DATDEF struct vm_datablock __devfs_datablock ASMNAME("devfs");

/* Devfs locking functions */
FUNDEF void KCALL devfs_lock_read(void) THROWS(E_BADALLOC, E_INTERRUPT, ...);
FUNDEF void KCALL devfs_lock_write(void) THROWS(E_INTERRUPT, ...);
FUNDEF bool KCALL devfs_lock_upgrade(void) THROWS(E_WOULDBLOCK, E_INTERRUPT, ...);
FUNDEF bool NOTHROW(KCALL devfs_lock_read_nx)(void);
FUNDEF bool NOTHROW(KCALL devfs_lock_write_nx)(void);
FUNDEF unsigned int NOTHROW(KCALL devfs_lock_upgrade_nx)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL devfs_lock_tryread)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL devfs_lock_trywrite)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL devfs_lock_tryupgrade)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL devfs_lock_endwrite)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL devfs_lock_endread)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL devfs_lock_end)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL devfs_lock_downgrade)(void);

/* Locking functions for data blocks */
#define vm_datablock_lock_read(self)       (unlikely((self) == &__devfs_datablock) ? devfs_lock_read() : (void)rwlock_read(&(self)->db_lock))
#define vm_datablock_lock_write(self)      (unlikely((self) == &__devfs_datablock) ? devfs_lock_write() : (void)rwlock_write(&(self)->db_lock))
#define vm_datablock_lock_upgrade(self)    (unlikely((self) == &__devfs_datablock) ? devfs_lock_upgrade() : rwlock_upgrade(&(self)->db_lock))
#define vm_datablock_lock_read_nx(self)    (unlikely((self) == &__devfs_datablock) ? devfs_lock_read_nx() : rwlock_read_nx(&(self)->db_lock))
#define vm_datablock_lock_write_nx(self)   (unlikely((self) == &__devfs_datablock) ? devfs_lock_write_nx() : rwlock_write_nx(&(self)->db_lock))
#define vm_datablock_lock_upgrade_nx(self) (unlikely((self) == &__devfs_datablock) ? devfs_lock_upgrade_nx() : rwlock_upgrade_nx(&(self)->db_lock))
#define vm_datablock_lock_tryread(self)    (unlikely((self) == &__devfs_datablock) ? devfs_lock_tryread() : rwlock_tryread(&(self)->db_lock))
#define vm_datablock_lock_trywrite(self)   (unlikely((self) == &__devfs_datablock) ? devfs_lock_trywrite() : rwlock_trywrite(&(self)->db_lock))
#define vm_datablock_lock_tryupgrade(self) (unlikely((self) == &__devfs_datablock) ? devfs_lock_tryupgrade() : rwlock_tryupgrade(&(self)->db_lock))
#define vm_datablock_lock_endwrite(self)   (unlikely((self) == &__devfs_datablock) ? devfs_lock_endwrite() : rwlock_endwrite(&(self)->db_lock))
#define vm_datablock_lock_endread(self)    (unlikely((self) == &__devfs_datablock) ? devfs_lock_endread() : rwlock_endread(&(self)->db_lock))
#define vm_datablock_lock_end(self)        (unlikely((self) == &__devfs_datablock) ? devfs_lock_end() : rwlock_end(&(self)->db_lock))
#define vm_datablock_lock_downgrade(self)  (unlikely((self) == &__devfs_datablock) ? devfs_lock_downgrade() : rwlock_downgrade(&(self)->db_lock))
#define vm_datablock_lock_reading(self)    rwlock_reading(&(self)->db_lock)
#define vm_datablock_lock_writing(self)    rwlock_writing(&(self)->db_lock)
#define vm_datablock_lock_canread(self)    rwlock_canread(&(self)->db_lock)
#define vm_datablock_lock_canwrite(self)   rwlock_canwrite(&(self)->db_lock)
#define vm_datablock_lock_pollread(self)   rwlock_pollread(&(self)->db_lock)
#define vm_datablock_lock_pollwrite(self)  rwlock_pollwrite(&(self)->db_lock)

/* Define C++ sync API hooks. */
__DEFINE_SYNC_RWLOCK(struct vm_datablock,
                     vm_datablock_lock_tryread,
                     vm_datablock_lock_read,
                     vm_datablock_lock_read_nx,
                     vm_datablock_lock_endread,
                     vm_datablock_lock_reading,
                     vm_datablock_lock_canread,
                     vm_datablock_lock_trywrite,
                     vm_datablock_lock_write,
                     vm_datablock_lock_write_nx,
                     vm_datablock_lock_endwrite,
                     vm_datablock_lock_writing,
                     vm_datablock_lock_canwrite,
                     vm_datablock_lock_end,
                     vm_datablock_lock_tryupgrade,
                     vm_datablock_lock_upgrade,
                     vm_datablock_lock_upgrade_nx,
                     vm_datablock_lock_downgrade)
__DEFINE_SYNC_POLL(struct vm_datablock,
                   vm_datablock_lock_pollread,
                   vm_datablock_lock_pollwrite)



/* Anonymize the given data block `self' (tearing down its part tree, and
 * changing all of the nodes to be bound to `vm_datablock_anonymous_zero_vec[*]',
 * meaning that any future memory access will yield all ZEROes)
 * This in turn will resolve all of the reference loops between every
 * part reachable from `db_parts', which then point back via their `dp_block'
 * pointer, essentially getting rid of all of the data block's self-references.
 * NOTE: The caller should _NOT_ already be holding a lock to `self'!
 *       Doing so may cause this function to dead-lock, as it would be unable
 *       to perform a single-lock wait operation in case some other thread is
 *       already holding a lock to one of the parts, whilst trying to acquire
 *       a lock to the associated block, without would already be held by the
 *       caller.
 * HINT: This function is used to detach file mappings when a file gets
 *       deleted, or when an entire superblock block is unmounted.
 * @return: true:  The given datablock has now become anonymous.
 * @return: false: The given datablock had already been anonymized.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked. */
FUNDEF NONNULL((1)) bool KCALL
vm_datablock_anonymize(struct vm_datablock *__restrict self)
		THROWS(E_WOULDBLOCK);

/* TODO: `vm_datablock_anonymize_range()' -- Same as `vm_datablock_anonymize()',
 *        but only anonymize data parts within a given data-page range.
 *     -> This function would then be used to unshare data parts when an
 *        INode is truncated. */


/* Undo the effects of `vm_datablock_anonymize()',
 * once again allowing `self' to carry data parts. */
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL vm_datablock_deanonymize)(struct vm_datablock *__restrict self);
#else /* __INTELLISENSE__ */
#define vm_datablock_deanonymize(self)                               \
	__hybrid_atomic_cmpxch((self)->db_parts, VM_DATABLOCK_ANONPARTS, \
	                       NULL, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !__INTELLISENSE__ */

/* Check if `self' is an anonymous datablock */
#define vm_datablock_isanonymous(self) \
	(__hybrid_atomic_load((self)->db_parts, __ATOMIC_ACQUIRE) == VM_DATABLOCK_ANONPARTS)


/* Synchronize all modified data pages within the specified address range.
 * When called, this function will go through all data parts of `self', and
 * save any changed data pages using `self->db_type->dt_savepart'
 * @return: * : The number of saved data pages. */
FUNDEF NONNULL((1)) datapage_t KCALL
vm_datablock_sync(struct vm_datablock *__restrict self,
                  datapage_t minpage DFL((datapage_t)0),
                  datapage_t maxpage DFL((datapage_t)-1))
		THROWS(E_WOULDBLOCK, ...);

/* Check if there are changed parts within the specified address range.
 * NOTE: The caller must be holding a read-lock on `self' */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL vm_datablock_haschanged)(struct vm_datablock *__restrict self,
                                       datapage_t minpage DFL((datapage_t)0),
                                       datapage_t maxpage DFL((datapage_t)-1));


/* Construct a new datapart for the given address range.
 * NOTES:
 *  - The data part is _not_ inserted into the part-tree of `self',
 *    and it is the caller's task to do so, or to ensure that the
 *    given datablock is anonymous.
 *  - The data part is created as `VM_DATAPART_STATE_ABSENT', or
 *    `VM_DATAPART_STATE_VIOPRT' in the event that the data part
 *    refers to a VIO mapping. Additionally, all data pages are
 *    initialized as `VM_DATAPART_PPP_UNINITIALIZED'. */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_createpart(struct vm_datablock *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t start_offset,
                        PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
LOCAL ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_paged_datablock_createpart(struct vm_datablock *__restrict self,
                              vm_vpage64_t pageno, size_t num_vpages)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	return vm_datablock_createpart(self,
	                               (pos_t)pageno * PAGESIZE,
	                               num_vpages * PAGESIZE);
}

/* Lookup and return a reference the data part containing the given `start_offset'
 * NOTE: When `self' is an anonymous data block (`self->db_parts == VM_DATABLOCK_ANONPARTS'),
 *       the the returned data part will be allocated anonymously as well, meaning that
 *       it will not be shared (`!isshared(return)'), and not be re-returned when the
 *       call is repeated with the same arguments passed once again. */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_locatepart(struct vm_datablock *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t start_offset,
                        PAGEDIR_PAGEALIGNED size_t num_bytes_hint)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
LOCAL ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_paged_datablock_locatepart(struct vm_datablock *__restrict self,
                              vm_vpage64_t pageno, size_t num_vpages_hint)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	return vm_datablock_locatepart(self,
	                               (pos_t)pageno * PAGESIZE,
	                               num_vpages_hint * PAGESIZE);
}

/* Same as `vm_paged_datablock_locatepart()', but ensure that the returned datapart
 * starts at exactly at `start_offset', and that it doesn't have span more than
 * `max_num_bytes' pages of virtual memory (though it may still span less than that) */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_datablock_locatepart_exact(struct vm_datablock *__restrict self,
                              PAGEDIR_PAGEALIGNED pos_t start_offset,
                              PAGEDIR_PAGEALIGNED size_t max_num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
LOCAL ATTR_RETNONNULL NONNULL((1)) REF struct vm_datapart *KCALL
vm_paged_datablock_locatepart_exact(struct vm_datablock *__restrict self,
                                    vm_vpage64_t pageno, size_t max_num_vpages)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	return vm_datablock_locatepart_exact(self,
	                                     (pos_t)pageno * PAGESIZE,
	                                     max_num_vpages * PAGESIZE);
}


/* Read/Write directory to/form a given VM datablock.
 * NOTE: When given a virtual memory buffer, these functions automatically
 *       check if the memory backing that buffer could potentially overlap
 *       with memory from `self', in which case reading is performed using
 *       an intermediate buffer, so-as to prevent a possible dead-lock.
 * NOTE: The caller must _NOT_ be holding any lock to `self', or any of its
 *       data parts, or even any VM-tree when calling this function.
 * WARNING: None of these functions do any bound-checks!
 *          In other words, it is up to `dt_loadpart()' to still initialize
 *          memory past the end of a file properly (usually by zero-initializing it)
 * @return: * : The number of transferred bytes. */
FUNDEF NONNULL((1)) void KCALL vm_datablock_read(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vm_datablock_write(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vm_datablock_read_phys(struct vm_datablock *__restrict self, vm_phys_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL vm_datablock_write_phys(struct vm_datablock *__restrict self, vm_phys_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_readv(struct vm_datablock *__restrict self, struct aio_buffer const *__restrict buf, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_writev(struct vm_datablock *__restrict self, struct aio_buffer const *__restrict buf, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_readv_phys(struct vm_datablock *__restrict self, struct aio_pbuffer const *__restrict buf, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_writev_phys(struct vm_datablock *__restrict self, struct aio_pbuffer const *__restrict buf, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as the `vm_datablock_(read|write)', however make the assumption that the
 * memory backing is `safe' (i.e. access could never cause a #PF attempting to
 * acquire a lock to `self' when doing so is impossible) */
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_read_unsafe(struct vm_datablock *__restrict self, void *__restrict dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_write_unsafe(struct vm_datablock *__restrict self, void const *__restrict src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);


#ifdef LIBVIO_CONFIG_ENABLED
/* Perform datablock access through VIO callbacks. */
FUNDEF NONNULL((1)) void KCALL vm_datablock_vio_read(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vm_datablock_vio_write(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vm_datablock_vio_read_phys(struct vm_datablock *__restrict self, vm_phys_t dst, size_t num_bytes, pos_t src_offset) THROWS(...);
FUNDEF NONNULL((1)) void KCALL vm_datablock_vio_write_phys(struct vm_datablock *__restrict self, vm_phys_t src, size_t num_bytes, pos_t dst_offset) THROWS(...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_vio_readv(struct vm_datablock *__restrict self, struct aio_buffer const *__restrict buf, pos_t src_offset) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_vio_writev(struct vm_datablock *__restrict self, struct aio_buffer const *__restrict buf, pos_t dst_offset) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_vio_readv_phys(struct vm_datablock *__restrict self, struct aio_pbuffer const *__restrict buf, pos_t src_offset) THROWS(...);
FUNDEF NONNULL((1, 2)) void KCALL vm_datablock_vio_writev_phys(struct vm_datablock *__restrict self, struct aio_pbuffer const *__restrict buf, pos_t dst_offset) THROWS(...);
#endif /* LIBVIO_CONFIG_ENABLED */



/* Builtin data blocks */

/* Provide direct access to physical memory (the `pos_t' is actually the `vm_phys_t'). */
DATDEF struct vm_datablock vm_datablock_physical;
DATDEF struct vm_datablock_type vm_datablock_physical_type;

/* Provide random, uninitialized memory. */
DATDEF struct vm_datablock vm_datablock_anonymous;
DATDEF struct vm_datablock_type vm_datablock_anonymous_type;

/* Provide zero-initialized memory (alias for `&vm_datablock_anonymous_zero_vec[0]'). */
DATDEF struct vm_datablock vm_datablock_anonymous_zero;
DATDEF struct vm_datablock_type vm_datablock_anonymous_zero_type;

/* Same as `vm_datablock_anonymous_zero', however the index refers to the intended pageshift.
 * This is required so that `vm_datablock_anonymize()' doesn't have to deal with initializing
 * partially initialized physical pages of data parts, with even though could be done noexcept,
 * could only done so for parts that are either absent, or have been allocated as INCORE/LOCKED.
 * It can't however be done NOEXCEPT for INSWAP parts, as those would first have to be loaded
 * from swap, which in itself might cause an `E_IOERROR', which the function wouldn't know how
 * to deal with. - So instead, it simply re-assigns an anonymous data part with the same pageshift
 * as was originally used by the original data block, further simplifying anonymization as this
 * way it doesn't entail any changes made to a part's address range or data-page encoding. */
DATDEF struct vm_datablock vm_datablock_anonymous_zero_vec[PAGESHIFT + 1];
DATDEF struct vm_datablock_type vm_datablock_anonymous_zero_type_vec[PAGESHIFT + 1];




struct vm_ramfile {
	/* RAM File (a datablock type that can be used to represent a
	 * limited segment of physical RAM available as a generic data
	 * block) - This type of data block is used to safely load dynamic
	 * loaders into user-space memory. */
	struct vm_datablock rf_block; /* The underlying ram block. */
	struct vm_ramblock  rf_data;  /* [const] The ram data of the file. */
};

/* The datablock type used by `vm_ramfile' */
DATDEF struct vm_datablock_type vm_ramfile_type;

#define VM_RAMFILE_INIT(/*pageptr_t*/ start, /*size_t*/ num_pages) \
	{ VM_DATABLOCK_INIT(&vm_ramfile_type, NULL, 0), /* .rf_data = */ { start, num_pages } }





#define VM_PROT_NONE    0x00 /* No access */
#define VM_PROT_EXEC    0x01 /* Executable */
#define VM_PROT_WRITE   0x02 /* Writable */
#define VM_PROT_READ    0x04 /* Readable */
#define VM_PROT_PRIVATE 0x00 /* The mapping is private (copy-on-write) */
#define VM_PROT_LOOSE   0x10 /* The mapping is deleted during VM unshare (aka. during `clone(~CLONE_VM)' / `fork()') */
#define VM_PROT_SHARED  0x20 /* The mapping is shared (modifications are global/persistent) */


#define VM_NODE_FLAG_NORMAL       0x0000 /* Normal node flags */
#define VM_NODE_FLAG_PREPARED     0x0001 /* The node has been prepared within the associated page directory. */
/* TODO: Remove `VM_NODE_FLAG_PARTITIONED' */
#define VM_NODE_FLAG_PARTITIONED  0x0002 /* Set if the node has been split when the associated data part was split.
                                          * This flag affects how the page directory is un-prepared when the node
                                          * gets unmapped. When set, associated memory must be unmapped as:
                                          * >> pagedir_prepare_map(vm_node_getstart(self), vm_node_getsize(self)); // NOTE: This may cause an error!
                                          * >> pagedir_unmap(vm_node_getstart(self), vm_node_getsize(self));
                                          * >> pagedir_unprepare_map(vm_node_getstart(self), vm_node_getsize(self));
                                          * When not set, associated memory can simply be unmapped as:
                                          * >> pagedir_unmap(vm_node_getstart(self), vm_node_getsize(self));
                                          * >> pagedir_unprepare_map(vm_node_getstart(self), vm_node_getsize(self)); */
#define VM_NODE_FLAG_GROWSUP      0x0004 /* When guarding, the node grows up rather than down. */
#define VM_NODE_FLAG_HINTED       0x1000 /* [const] Uninitialized pages apart of this node hint towards it.
                                          * This flag is set for memory mapping that can be initialized atomically.
                                          * When set the following restrictions are applied:
                                          *  - node->vn_prot & VM_PROT_SHARED
                                          *  - node->vn_flags & VM_NODE_FLAG_PREPARED
                                          *  - !(node->vn_flags & VM_NODE_FLAG_PARTITIONED)
                                          *  - node->vn_vm == &vm_kernel
                                          *  - node->vn_part != NULL
                                          *  - node->vn_block != NULL
                                          *  - node->vn_guard == 0
                                          *  - node->vn_part->dp_srefs == node
                                          *  - node->vn_link.ln_pself == &node->vn_part->dp_srefs
                                          *  - node->vn_link.ln_next == NULL
                                          *  - node->vn_part->dp_crefs == NULL
                                          *  - !isshared(node->vn_part)
                                          *  - node->vn_part->dp_block == node->vn_block
                                          *  - node->vn_block->db_parts == VM_DATABLOCK_ANONPARTS
                                          *  - node->vn_part->dp_flags & VM_DATAPART_FLAG_LOCKED
                                          *  - node->vn_part->dp_state == VM_DATAPART_STATE_LOCKED
                                          * Additionally, this `struct vm_node' must be hinted towards by the
                                          * entirety of its associated page directory mapping range, with all
                                          * of these requirements put together allowing memory mapped by the
                                          * node to be initialized without ever needing to block, making it
                                          * suitable for initialization of `GFP_LOCKED' heap memory. */
#define VM_NODE_FLAG_NOMERGE      0x2000 /* [const] This node was allocated by custom means and must not be merged with its neighbors! */
#define VM_NODE_FLAG_COREPRT      0x4000 /* [const] The part was allocated as a corebase datapart. (see /src/memory/corebase.h) */
#define VM_NODE_FLAG_KERNPRT      0x8000 /* [const] This node describes part of the static kernel core and must
                                          *         not be modified or removed. Attempting to do so anyways will
                                          *         result in kernel panic. */

struct vm_node {
	ATREE_NODE(struct vm_node, pageid_t)
	                            vn_node;   /* [lock(vn_vm->v_treelock,OWNER)] VM Node controller. */
	LLIST_NODE(struct vm_node)  vn_byaddr; /* [lock(vn_vm->v_treelock,OWNER)][const_if(VM_NODE_FLAG_KERNPRT)] Order chain of nodes mapped within #vn_vm. */
	uintptr_half_t              vn_prot;   /* [lock(vn_vm->v_treelock,OWNER)][const_if(VM_NODE_FLAG_KERNPRT)] VM Node protection (Set of `VM_PROT_*'). */
	uintptr_half_t              vn_flags;  /* [lock(vn_vm->v_treelock,OWNER)][const_if(VM_NODE_FLAG_KERNPRT)] VM Node flags (Set of `VM_FLAG_F*'). */
	struct vm                  *vn_vm;     /* [1..1][const] The associated VM */
	REF struct vm_datapart     *vn_part;   /* [0..1][lock(vn_vm->v_treelock)][const_if(VM_NODE_FLAG_HINTED || VM_NODE_FLAG_KERNPRT)]
	                                        * NOTE: When `vn_block' is `NULL', then this field is _required_ to be `NULL'
	                                        * The mapped part (or `NULL' if this VM Node describes a reserved memory region) */
	REF struct vm_datablock    *vn_block;  /* [0..1][const] The mapped part (or `NULL' if this VM Node describes a reserved memory region) */
	REF struct path            *vn_fspath; /* [0..1][const] Optional mapping path (only used for memory->disk mapping listings) */
	REF struct directory_entry *vn_fsname; /* [0..1][const] Optional mapping name (only used for memory->disk mapping listings) */
	LLIST_NODE(struct vm_node)  vn_link;   /* [lock(vn_vm->v_treelock && vn_part)] Chain of nodes in either
	                                        * `vn_part->dp_crefs' or `vn_part->dp_srefs'.
	                                        * Which chain is used depends on the `VM_PROT_SHARED' bit. */
	uintptr_t                   vn_guard;  /* [const] An associated guard descriptor, used to implement lazy stack growth.
	                                        * When `0', the node acts normally and guard behavior is disabled.
	                                        * When `1', any access made to the node results in an `E_STACK_OVERFLOW' exception being generated.
	                                        * Otherwise, accessing any page apart of this node will cause a new 1-page large node to be
	                                        * created either below or above this one (depending on `VM_NODE_FLAG_GROWSUP'), with that
	                                        * node being created with `vn_guard' decremented by one.
	                                        * If the `vn_guard' value of the new node is `1', `vn_part' of that node is set to `NULL'.
	                                        * Otherwise, the node is initialized to map to the proper data part above of below the
	                                        * one that this node is mapped to.
	                                        * When a node is split due to a call to `vm_datapart_split()', only the upper (w/ VM_NODE_FLAG_GROWSUP)
	                                        * or lower (w/o VM_NODE_FLAG_GROWSUP) node will retain its `vn_guard' setting, while the other
	                                        * will have this field set to 0. */
	/* TODO: Memory breakpoint support (any memory access is emulated using VIO) */
};


/* Free a given VM node (the method used depending on
 * `self->vn_flags & VM_NODE_FLAG_COREPRT') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_free)(struct vm_node *__restrict self);

/* Destroy a given node. - This will finalize the following fields:
 *  - vn_fspath
 *  - vn_fsname
 *  - vn_block
 *  - vn_part
 *  - vn_link */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_destroy)(struct vm_node *__restrict self);


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
 * NOTE: The caller is expected to be holding a lock to the `vm_datapart'
 *       that is being mapped by the given node `self'.
 * @return: * : One of `VM_NODE_UPDATE_WRITE_ACCESS_*' */
FUNDEF NOBLOCK unsigned int
NOTHROW(KCALL vm_node_update_write_access)(struct vm_node *__restrict self);
#define VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS          0 /* Success (or no-op when `self' isn't mapped with write-access) */
#define VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK       1 /* ERROR: The operation would have blocked (The caller must blocking-wait for `sync_write(self->vn_vm)') */
#define VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK_TASKS 2 /* ERROR: The operation would have blocked (The caller must blocking-wait for `vm_tasklock_read(self)') */
#define VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC         3 /* ERROR: Failed to prepare the underlying page directory for making modifications to the associated mapping. */

/* Same as `vm_node_update_write_access()', but the caller
 * is already holding a write-lock to `locked_vm' */
FUNDEF NOBLOCK unsigned int
NOTHROW(KCALL vm_node_update_write_access_locked_vm)(struct vm_node *__restrict self,
                                                     struct vm *__restrict locked_vm);

#ifdef __INTELLISENSE__
/* Return the address range bounds of the given VM node. */
#define vm_node_getmin   vm_node_getmin
#define vm_node_getmax   vm_node_getmax
#define vm_node_getstart vm_node_getstart
#define vm_node_getend   vm_node_getend
#define vm_node_getsize  vm_node_getsize
PAGEDIR_PAGEALIGNED UNCHECKED void *(vm_node_getmin)(struct vm_node const *__restrict self);
void *(vm_node_getmax)(struct vm_node const *__restrict self);
PAGEDIR_PAGEALIGNED UNCHECKED void *(vm_node_getstart)(struct vm_node const *__restrict self);
PAGEDIR_PAGEALIGNED UNCHECKED void *(vm_node_getend)(struct vm_node const *__restrict self);
PAGEDIR_PAGEALIGNED size_t (vm_node_getsize)(struct vm_node const *__restrict self); /* in bytes */

/* Return the internal page-indices used for mapping the given VM node. */
#define vm_node_getminpageid vm_node_getminpageid
#define vm_node_getmaxpageid vm_node_getmaxpageid
#define vm_node_getstartpageid vm_node_getstartpageid
#define vm_node_getendpageid vm_node_getendpageid
#define vm_node_getpagecount vm_node_getpagecount
pageid_t (vm_node_getminpageid)(struct vm_node const *__restrict self);
pageid_t (vm_node_getmaxpageid)(struct vm_node const *__restrict self);
pageid_t (vm_node_getstartpageid)(struct vm_node const *__restrict self);
pageid_t (vm_node_getendpageid)(struct vm_node const *__restrict self);
size_t (vm_node_getpagecount)(struct vm_node const *__restrict self);

/* Check if the given VM Node points into user- or kernel-space. */
#define vm_node_isuserspace   vm_node_isuserspace
#define vm_node_iskernelspace vm_node_iskernelspace
bool (vm_node_isuserspace)(struct vm_node const *__restrict self);
bool (vm_node_iskernelspace)(struct vm_node const *__restrict self);
#else /* __INTELLISENSE__ */
#define vm_node_getmin(self)     PAGEID_DECODE((self)->vn_node.a_vmin)
#define vm_node_getmax(self)     ((void *)((byte_t *)PAGEID_DECODE((self)->vn_node.a_vmax) + PAGESIZE - 1))
#define vm_node_getstart(self)   PAGEID_DECODE((self)->vn_node.a_vmin)
#define vm_node_getend(self)     PAGEID_DECODE((self)->vn_node.a_vmax + 1)
#define vm_node_getsize(self)        ((size_t)(((self)->vn_node.a_vmax - (self)->vn_node.a_vmin) + 1) * PAGESIZE)

#define vm_node_getminpageid(self)   ((self)->vn_node.a_vmin)
#define vm_node_getmaxpageid(self)   ((self)->vn_node.a_vmax)
#define vm_node_getstartpageid(self) ((self)->vn_node.a_vmin)
#define vm_node_getpagecount(self)   ((size_t)(((self)->vn_node.a_vmax - (self)->vn_node.a_vmin) + 1))
#define vm_node_getendpageid(self)   ((self)->vn_node.a_vmax + 1)

#ifdef KERNELSPACE_HIGHMEM
#define vm_node_isuserspace(self)    (vm_node_getmaxpageid(self) < PAGEID_ENCODE(KERNELSPACE_BASE))
#define vm_node_iskernelspace(self)  (vm_node_getmaxpageid(self) >= PAGEID_ENCODE(KERNELSPACE_BASE))
#else /* KERNELSPACE_HIGHMEM */
#define vm_node_isuserspace(self)    (vm_node_getminpageid(self) > PAGEID_ENCODE(KERNELSPACE_END))
#define vm_node_iskernelspace(self)  (vm_node_getminpageid(self) <= PAGEID_ENCODE(KERNELSPACE_END))
#endif /* !KERNELSPACE_HIGHMEM */
#endif /* !__INTELLISENSE__ */

#define VM_NODE_HASNEXT(self, vm) ((self)->vn_byaddr.ln_next != NULL)
#define VM_NODE_HASPREV(self, vm) ((self)->vn_byaddr.ln_pself != &LLIST_HEAD((vm)->v_byaddr))
#define VM_NODE_NEXT(self)        ((self)->vn_byaddr.ln_next)
#define VM_NODE_PREV(self)        __COMPILER_CONTAINER_OF((self)->vn_byaddr.ln_pself,struct vm_node,vn_byaddr.ln_next)

struct vm {
	/* Top-level controller for virtual memory bindings. */
#ifndef __VM_INTERNAL_EXCLUDE_PAGEDIR
	pagedir_t                  v_pagedir;       /* [lock(v_treelock)] The page directory associated with the VM. */
#endif /* !__VM_INTERNAL_EXCLUDE_PAGEDIR */
	union {
		PHYS pagedir_t        *v_pdir_phys_ptr; /* [1..1][const] Physical pointer of the page directory */
#ifdef __INTELLISENSE__
		struct { PHYS vm_phys_t v_pdir_phys;    /* [1..1][const] Physical pointer of the page directory */ };
#else /* __INTELLISENSE__ */
		PHYS vm_phys_t         v_pdir_phys;     /* [1..1][const] Physical pointer of the page directory */
#endif /* !__INTELLISENSE__ */
	};
	WEAK refcnt_t              v_refcnt;        /* Reference counter */
	WEAK refcnt_t              v_weakrefcnt;    /* Weak reference counter */
	ATREE_HEAD(struct vm_node) v_tree;          /* [lock(v_treelock)] Tree of mapped nodes. */
	LLIST(struct vm_node)      v_byaddr;        /* [lock(v_treelock)] By-address ordered list of nodes. */
	size_t                     v_heap_size;     /* [const] Size of the heap pointer used to allocated this VM. */
	struct atomic_rwlock       v_treelock;      /* Lock for this VM */
	LLIST(struct task)         v_tasks;         /* [0..1][lock(v_tasklock)] Chain of threads using this VM.
	                                             * WARNING: This chain may contain terminated tasks,
	                                             *          tasks that haven't yet started, or even tasks
	                                             *          with a reference counter of ZERO(0)! */
	struct atomic_rwlock       v_tasklock;      /* Lock for `v_tasks' */
	WEAK REF struct task      *v_deltasks;      /* [0..1][CHAIN(->t_sched.s_running.sr_runnxt)]
	                                             * Chain of tasks that are pending deletion from `v_tasks',
	                                             * as well as follow-up `heap_free()' of the task in question.
	                                             * NOTE: All other components of the task will have already been destroyed. */
	struct vm_node             v_kernreserve;   /* A special RESERVED-like node that is used by user-space VMs
	                                             * to cover the entire kernel-space, preventing user-space from
	                                             * accidentally overwriting it, without the need of adding too
	                                             * many special-case exceptions to various VM-related functions.
	                                             * NOTE: For the kernel-VM itself, this node is unused. */
};

DATDEF struct vm vm_kernel;

/* The VM that is currently active within the calling thread */
DATDEF ATTR_PERTASK REF struct vm *this_vm;
#define THIS_VM  PERTASK_GET(this_vm)
#define PERVM(x) (*(__typeof__(&(x)))((uintptr_t)THIS_VM + (uintptr_t)&(x)))

FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_free)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_destroy)(struct vm *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct vm, v_refcnt, vm_destroy);
DEFINE_WEAKREFCOUNT_FUNCTIONS(struct vm, v_weakrefcnt, vm_free);

/* Allocate and initialize a new, empty VM for user-space. */
FUNDEF ATTR_RETNONNULL REF struct vm *KCALL vm_alloc(void) THROWS(E_BADALLOC, ...);

/* Clone the given VM `self'
 * NOTE: The clone operation is performed atomically, meaning that
 *       this function guaranties that at one point both `self' and
 *       the returned VM contained perfectly identical mappings, even
 *       if during the course of this function operating the mappings
 *       contained within `self' are being changed.
 * @param: keep_loose_mappings: When false (default), don't clone mappings marked as `VM_PROT_LOOSE'
 * @return: * : A reference to the newly cloned VM (with a reference counter of `1'). */
FUNDEF ATTR_RETNONNULL REF struct vm *KCALL
vm_clone(struct vm *__restrict self,
         bool keep_loose_mappings DFL(false))
		THROWS(E_BADALLOC, ...);


/* Set the VM active within the calling thread, as well as
 * change page directories to make use of the new VM before
 * returning.
 * NOTE: The caller must NOT be holding a lock to either
 *       the old or new VM's list of tasks. */
FUNDEF void KCALL task_setvm(struct vm *__restrict newvm) THROWS(E_WOULDBLOCK);

/* Return the active VM of the given `thread' */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct vm *KCALL
task_getvm(struct task *__restrict thread) THROWS(E_WOULDBLOCK);



/* Acquire locks to the tree of the kernel VM */
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) bool KCALL vm_kernel_treelock_writef(gfp_t flags) THROWS(E_WOULDBLOCK);
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) WUNUSED bool NOTHROW(KCALL vm_kernel_treelock_writef_nx)(gfp_t flags);
FUNDEF void KCALL vm_kernel_treelock_write(void) THROWS(E_WOULDBLOCK);
FUNDEF void KCALL vm_kernel_treelock_read(void) THROWS(E_WOULDBLOCK);
FUNDEF bool KCALL vm_kernel_treelock_upgrade(void) THROWS(E_WOULDBLOCK);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL vm_kernel_treelock_trywrite)(void);
FUNDEF WUNUSED bool NOTHROW(KCALL vm_kernel_treelock_write_nx)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_endwrite)(void);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL vm_kernel_treelock_tryread)(void);
FUNDEF WUNUSED bool NOTHROW(KCALL vm_kernel_treelock_read_nx)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_endread)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_end)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_downgrade)(void);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL vm_kernel_treelock_tryupgrade)(void);
FUNDEF WUNUSED unsigned int NOTHROW(KCALL vm_kernel_treelock_upgrade_nx)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_tryservice)(void);

/* Acquire locks to the tree of the given VM */
#define vm_treelock_write(self)      ((self) == &vm_kernel ? vm_kernel_treelock_write() : atomic_rwlock_write(&(self)->v_treelock))
#define vm_treelock_write_nx(self)   ((self) == &vm_kernel ? vm_kernel_treelock_write_nx() : atomic_rwlock_write_nx(&(self)->v_treelock))
#define vm_treelock_trywrite(self)   ((self) == &vm_kernel ? vm_kernel_treelock_trywrite() : atomic_rwlock_trywrite(&(self)->v_treelock))
#define vm_treelock_endwrite(self)   ((self) == &vm_kernel ? vm_kernel_treelock_endwrite() : atomic_rwlock_endwrite(&(self)->v_treelock))
#define vm_treelock_read(self)       ((self) == &vm_kernel ? vm_kernel_treelock_read() : atomic_rwlock_read(&(self)->v_treelock))
#define vm_treelock_read_nx(self)    ((self) == &vm_kernel ? vm_kernel_treelock_read_nx() : atomic_rwlock_read_nx(&(self)->v_treelock))
#define vm_treelock_tryread(self)    ((self) == &vm_kernel ? vm_kernel_treelock_tryread() : atomic_rwlock_tryread(&(self)->v_treelock))
#define vm_treelock_endread(self)    ((self) == &vm_kernel ? vm_kernel_treelock_endread() : (void)atomic_rwlock_endread(&(self)->v_treelock))
#define vm_treelock_end(self)        ((self) == &vm_kernel ? vm_kernel_treelock_end() : (void)atomic_rwlock_end(&(self)->v_treelock))
#define vm_treelock_upgrade(self)    ((self) == &vm_kernel ? vm_kernel_treelock_upgrade() : atomic_rwlock_upgrade(&(self)->v_treelock))
#define vm_treelock_upgrade_nx(self) ((self) == &vm_kernel ? vm_kernel_treelock_upgrade_nx() : atomic_rwlock_upgrade_nx(&(self)->v_treelock))
#define vm_treelock_tryupgrade(self) ((self) == &vm_kernel ? vm_kernel_treelock_tryupgrade() : atomic_rwlock_tryupgrade(&(self)->v_treelock))
#define vm_treelock_downgrade(self)  ((self) == &vm_kernel ? vm_kernel_treelock_downgrade() : atomic_rwlock_downgrade(&(self)->v_treelock))
#define vm_treelock_reading(self)    atomic_rwlock_reading(&(self)->v_treelock)
#define vm_treelock_writing(self)    atomic_rwlock_writing(&(self)->v_treelock)
#define vm_treelock_canread(self)    atomic_rwlock_canread(&(self)->v_treelock)
#define vm_treelock_canwrite(self)   atomic_rwlock_canwrite(&(self)->v_treelock)

/* Define C++ sync API hooks. */
__DEFINE_SYNC_RWLOCK(struct vm,
                     vm_treelock_tryread,
                     vm_treelock_read,
                     vm_treelock_read_nx,
                     vm_treelock_endread,
                     vm_treelock_reading,
                     vm_treelock_canread,
                     vm_treelock_trywrite,
                     vm_treelock_write,
                     vm_treelock_write_nx,
                     vm_treelock_endwrite,
                     vm_treelock_writing,
                     vm_treelock_canwrite,
                     vm_treelock_end,
                     vm_treelock_tryupgrade,
                     vm_treelock_upgrade,
                     vm_treelock_upgrade_nx,
                     vm_treelock_downgrade)


FUNDEF NONNULL((1)) void KCALL vm_tasklock_read(struct vm *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void KCALL vm_tasklock_write(struct vm *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) bool KCALL vm_tasklock_upgrade(struct vm *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(KCALL vm_tasklock_read_nx)(struct vm *__restrict self);
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(KCALL vm_tasklock_write_nx)(struct vm *__restrict self);
FUNDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(KCALL vm_tasklock_upgrade_nx)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) WUNUSED bool NOTHROW(KCALL vm_tasklock_tryread)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) WUNUSED bool NOTHROW(KCALL vm_tasklock_trywrite)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) WUNUSED bool NOTHROW(KCALL vm_tasklock_tryupgrade)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_tasklock_endwrite)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_tasklock_endread)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_tasklock_end)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_tasklock_downgrade)(struct vm *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL vm_tasklock_tryservice)(struct vm *__restrict self);
#define vm_tasklock_reading(self) atomic_rwlock_reading(&(self)->v_tasklock)
#define vm_tasklock_writing(self) atomic_rwlock_writing(&(self)->v_tasklock)



/* Map the memory region into the given VM.
 * The caller may invoke `vm_paged_sync()' after changes have been made.
 * @param: prot:   Set of `VM_PROT_*'.
 * @param: flag:   Set of `VM_NODE_FLAG_*'.
 * @param: data_start_vpage: The memory page index where mapping of `data' starts.
 * @param: fspath: Optional mapping path (only used for memory->disk mapping listings)
 * @param: fsname: Optional mapping name (only used for memory->disk mapping listings)
 * @param: guard:  If non-zero, repetition limit for a guard mapping.
 *                 Set to 0 if the mapping shouldn't include a guard.
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
FUNDEF WUNUSED NONNULL((1, 4)) bool KCALL
vm_mapat(struct vm *__restrict self,
         PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
         PAGEDIR_PAGEALIGNED size_t num_bytes,
         struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
         struct path *fspath DFL(__NULLPTR),
         struct directory_entry *fsname DFL(__NULLPTR),
         PAGEDIR_PAGEALIGNED pos_t data_start_offset DFL(0),
         uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
         uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
         uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
LOCAL WUNUSED NONNULL((1, 4)) bool KCALL
vm_paged_mapat(struct vm *__restrict self,
               pageid_t page_index, size_t num_pages,
               struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
               struct path *fspath DFL(__NULLPTR),
               struct directory_entry *fsname DFL(__NULLPTR),
               vm_vpage64_t data_start_vpage DFL(0),
               uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
               uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
               uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	return vm_mapat(self, PAGEID_DECODE(page_index),
	                num_pages * PAGESIZE,
	                data, fspath, fsname,
	                (pos_t)data_start_vpage * PAGESIZE,
	                prot, flag, guard);
}

/* Same as `vm_paged_mapat()', but only allowed pages between `data_subrange_minvpage ... data_subrange_maxvpage'
 * to be mapped from `data'. - Any attempted to map data from outside that range will instead cause
 * memory from `vm_datablock_anonymous_zero' to be mapped.
 * Additionally, `data_start_vpage' is an offset from `data_subrange_minvpage'
 * @param: fspath: Optional mapping path (only used for memory->disk mapping listings)
 * @param: fsname: Optional mapping name (only used for memory->disk mapping listings) */
FUNDEF WUNUSED NONNULL((1, 4)) bool KCALL
vm_paged_mapat_subrange(struct vm *__restrict self,
                        pageid_t page_index, size_t num_pages,
                        struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
                        struct path *fspath DFL(__NULLPTR),
                        struct directory_entry *fsname DFL(__NULLPTR),
                        vm_vpage64_t data_start_vpage DFL(0),
                        vm_vpage64_t data_subrange_minvpage DFL(0),
                        vm_vpage64_t data_subrange_maxvpage DFL((vm_vpage64_t)-1),
                        uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
                        uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
                        uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);

LOCAL WUNUSED NONNULL((1, 4)) bool KCALL
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
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	__hybrid_assert((data_start_offset & PAGEMASK) == 0);
	__hybrid_assert((data_subrange_minoffset & PAGEMASK) == 0);
	__hybrid_assert((data_subrange_numbytes & PAGEMASK) == 0);
	return vm_paged_mapat_subrange(self,
	                               PAGEID_ENCODE(addr),
	                               num_bytes / PAGESIZE,
	                               data, fspath, fsname,
	                               (vm_vpage64_t)(data_start_offset / PAGESIZE),
	                               (vm_vpage64_t)(data_subrange_minoffset / PAGESIZE),
	                               (vm_vpage64_t)((data_subrange_minoffset + data_subrange_numbytes - 1) / PAGESIZE),
	                               prot, flag, guard);
}

/* Create a memory reservation mapping at the given address.
 * @param: flag: Set of `VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE'
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
FUNDEF WUNUSED NONNULL((1)) bool KCALL
vm_mapresat(struct vm *__restrict self,
            PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
            PAGEDIR_PAGEALIGNED size_t num_bytes,
            uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC);





/* Determine a suitable, free memory location for `num_pages'
 * aligned by a multiple of `min_alignment_in_pages' pages.
 * Search happens as follows:
 *   #1: Search according to `VM_GETFREE_ABOVE/VM_GETFREE_BELOW'
 *       Additionally, check for surrounding nodes which are set
 *       up as GUARD nodes. - If such a node is found, it's size
 *       is considered to have reached its maximum potential for
 *       this purpose (limited by how often `vn_guard' can be
 *       decremented, as well as any other memory mapping it may
 *       run into before then)
 *       If a this process yields only a single candidate, that
 *       candidate is returned as result.
 *       If a this process yields more than 1 candidate, the one chosen
 *       depends on `VM_GETFREE_ABOVE / VM_GETFREE_BELOW / VM_GETFREE_ASLR'
 *        - VM_GETFREE_ABOVE: The candidate with the lowest memory address is used
 *        - VM_GETFREE_BELOW: The candidate with the greatest memory address is used
 *        - VM_GETFREE_ABOVE + VM_GETFREE_ASLR:
 *          Return the `x = rand() / RAND_MAX; x*x*NUM_CANDIDATES'th candidate
 *        - VM_GETFREE_BELOW + VM_GETFREE_ASLR:
 *          Return the `x = 1 - (rand() / RAND_MAX); x*x*NUM_CANDIDATES'th candidate
 *   #2: Repeat step #1, but ignore the potentials of GUARD nodes.
 *   #3: Return `VM_PAGED_GETFREE_ERROR'
 * NOTE: The caller must be holding a read-lock to `self'.
 * @param: mode:                   Set of `VM_GETFREE_F*'
 * @param: hint:                   A hint used as base when searching for free memory ranges.
 * @param: min_alignment_in_pages: The minimum alignment required from the returned pointer (or `1')
 * @return: VM_PAGED_GETFREE_ERROR: No more virtual memory available. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) pageid_t
NOTHROW(KCALL vm_paged_getfree)(struct vm *__restrict self,
                                pageid_t hint, size_t num_pages,
                                size_t min_alignment_in_pages,
                                unsigned int mode);
#define VM_GETFREE_ABOVE  0x0000 /* Search for viable, free mappings that are `>= hint' */
#define VM_GETFREE_BELOW  0x0001 /* Search for viable, free mappings that are `<= hint-num_pages'  */
#define VM_GETFREE_STRICT 0x0002 /* After a search for free space failed to yielding a viable memory
                                  * location in accordance to `VM_GETFREE_ABOVE|VM_GETFREE_BELOW',
                                  * do _NOT_ re-attempt the search into the other direction. */
#define VM_GETFREE_ASLR   0x0004 /* Randomize return values (see above) */
/* TODO: Flag `VM_GETFREE_USER'  --  When `self' is `&vm_kernel', allow returned pointers
 *       to be apart of user-space, as opposed to only ever returning kernel-space pointers. */
#define VM_PAGED_GETFREE_ERROR  (__CCAST(pageid_t)(__ARCH_PAGEID_MAX + 1))


#define VM_GETFREE_ERROR ((void *)-1)
LOCAL NOBLOCK WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *
NOTHROW(KCALL vm_getfree)(struct vm *__restrict self,
                          PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
                          PAGEDIR_PAGEALIGNED size_t num_bytes,
                          PAGEDIR_PAGEALIGNED size_t min_alignment,
                          unsigned int mode) {
	pageid_t result;
	__hybrid_assert(((uintptr_t)hint & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	__hybrid_assert((min_alignment & PAGEMASK) == 0);
	result = vm_paged_getfree(self, PAGEID_ENCODE(hint),
	                    num_bytes / PAGESIZE,
	                    min_alignment / PAGESIZE, mode);
	if (result == VM_PAGED_GETFREE_ERROR)
		return VM_GETFREE_ERROR;
	return PAGEID_DECODE(result);
}



/* Get/set ASLR-disabled (defaults to `false'; can also be
 * enabled by passing `noaslr' on the kernel commandline)
 * When enabled, the `VM_GETFREE_ASLR' is simply ignored
 * when passed to either `vm_paged_getfree()' or `vmb_paged_getfree()'
 * @return: * : The state of ASLR_DISABLED prior to the call being made. */
FUNDEF bool NOTHROW(KCALL vm_get_aslr_disabled)(void);
FUNDEF bool NOTHROW(KCALL vm_set_aslr_disabled)(bool new_disabled);



/* Find the first node with `vm_node_getminpageid(return) >= min_page_index'
 * If no such node exists, return `NULL' instead.
 * NOTE: The caller must be holding a read-lock to `effective_vm'. */
FUNDEF NOBLOCK WUNUSED struct vm_node *
NOTHROW(KCALL vm_find_first_node_greater_equal)(struct vm *__restrict effective_vm,
                                                pageid_t min_page_index);

/* Find the last node with `vm_node_getmaxpageid(return) <= max_page_index'
 * If no such node exists, return `NULL' instead.
 * NOTE: The caller must be holding a read-lock to `effective_vm'. */
FUNDEF NOBLOCK WUNUSED struct vm_node *
NOTHROW(KCALL vm_find_last_node_lower_equal)(struct vm *__restrict effective_vm,
                                             pageid_t max_page_index);


/* A combination of `vm_paged_getfree' + `vm_paged_mapat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target.
 * @param: fspath: Optional mapping path (only used for memory->disk mapping listings)
 * @param: fsname: Optional mapping name (only used for memory->disk mapping listings) */
FUNDEF WUNUSED NONNULL((1, 6)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vm_map(struct vm *__restrict self,
       PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
       PAGEDIR_PAGEALIGNED size_t num_bytes,
       PAGEDIR_PAGEALIGNED size_t min_alignment DFL(PAGESIZE),
       unsigned int getfree_mode DFL(VM_GETFREE_ABOVE | VM_GETFREE_ASLR),
       struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
       struct path *fspath DFL(__NULLPTR),
       struct directory_entry *fsname DFL(__NULLPTR),
       PAGEDIR_PAGEALIGNED pos_t data_start_offset DFL(0),
       uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
       uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
       uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);

LOCAL pageid_t KCALL
vm_paged_map(struct vm *__restrict self,
             pageid_t hint,
             size_t num_pages,
             size_t min_alignment_in_pages DFL(1),
             unsigned int getfree_mode DFL(VM_GETFREE_ABOVE | VM_GETFREE_ASLR),
             struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
             struct path *fspath DFL(__NULLPTR),
             struct directory_entry *fsname DFL(__NULLPTR),
             vm_vpage64_t data_start_vpage DFL(0),
             uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
             uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
             uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	void *result;
	result = vm_map(self,
	                PAGEID_DECODE(hint),
	                num_pages * PAGESIZE,
	                min_alignment_in_pages * PAGESIZE,
	                getfree_mode, data, fspath, fsname,
	                (pos_t)data_start_vpage * PAGESIZE,
	                prot, flag, guard);
	return PAGEID_ENCODE(result);
}

/* Same as `vm_paged_map()', but only allowed pages between `data_subrange_minvpage ... data_subrange_maxvpage'
 * to be mapped from `data'. - Any attempted to map data from outside that range will instead cause
 * memory from `vm_datablock_anonymous_zero' to be mapped.
 * Additionally, `data_start_vpage' is an offset from `data_subrange_minvpage'
 * @param: fspath: Optional mapping path (only used for memory->disk mapping listings)
 * @param: fsname: Optional mapping name (only used for memory->disk mapping listings) */
FUNDEF pageid_t KCALL
vm_paged_map_subrange(struct vm *__restrict self,
                      pageid_t hint,
                      size_t num_pages,
                      size_t min_alignment_in_pages DFL(1),
                      unsigned int getfree_mode DFL(VM_GETFREE_ABOVE | VM_GETFREE_ASLR),
                      struct vm_datablock *__restrict data DFL(&vm_datablock_anonymous_zero),
                      struct path *fspath DFL(__NULLPTR),
                      struct directory_entry *fsname DFL(__NULLPTR),
                      vm_vpage64_t data_start_vpage DFL(0),
                      vm_vpage64_t data_subrange_minvpage DFL(0),
                      vm_vpage64_t data_subrange_maxvpage DFL((vm_vpage64_t)-1),
                      uintptr_half_t prot DFL(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED),
                      uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL),
                      uintptr_t guard DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
LOCAL PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vm_map_subrange(struct vm *__restrict self,
                PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
                PAGEDIR_PAGEALIGNED size_t num_bytes,
                PAGEDIR_PAGEALIGNED size_t min_alignment DFL(PAGESIZE),
                unsigned int getfree_mode DFL(VM_GETFREE_ABOVE | VM_GETFREE_ASLR),
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
	pageid_t result;
	__hybrid_assert(((uintptr_t)hint & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	__hybrid_assert((min_alignment & PAGEMASK) == 0);
	__hybrid_assert((data_start_offset & PAGEMASK) == 0);
	__hybrid_assert((data_subrange_minoffset & PAGEMASK) == 0);
	__hybrid_assert((data_subrange_numbytes & PAGEMASK) == 0);
	result = vm_paged_map_subrange(self,
	                               PAGEID_ENCODE(hint),
	                               num_bytes / PAGESIZE,
	                               min_alignment / PAGESIZE,
	                               getfree_mode,
	                               data, fspath, fsname,
	                               (vm_vpage64_t)(data_start_offset / PAGESIZE),
	                               (vm_vpage64_t)(data_subrange_minoffset / PAGESIZE),
	                               (vm_vpage64_t)((data_subrange_minoffset + data_subrange_numbytes - 1) / PAGESIZE),
	                               prot, flag, guard);
	return PAGEID_DECODE(result);
}



/* A combination of `vm_paged_getfree' + `vm_mapresat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target. */
FUNDEF UNCHECKED void *KCALL
vm_mapres(struct vm *__restrict self,
          PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
          PAGEDIR_PAGEALIGNED size_t num_bytes,
          PAGEDIR_PAGEALIGNED size_t min_alignment DFL(PAGESIZE),
          unsigned int getfree_mode DFL(VM_GETFREE_ABOVE | VM_GETFREE_ASLR),
          uintptr_half_t flag DFL(VM_NODE_FLAG_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC);



#define VM_UNMAP_NOTHING          0x0000 /* Unmap nothing */
#define VM_UNMAP_NORMAL           0x0001 /* Unmap normal nodes (`vn_guard == 0 && vn_part != NULL') */
#define VM_UNMAP_GUARD            0x0002 /* Unmap guard nodes (nodes with `vn_guard != 0') */
#define VM_UNMAP_RESERVE          0x0004 /* Unmap reserved regions of memory (nodes with `vn_part == NULL') */
#define VM_UNMAP_SEGFAULTIFUNUSED 0x2000 /* When set, throw an `E_SEGFAULT_UNMAPPED' exception with the lowest address
                                          * of the first segment of memory apart of the given range that isn't mapped
                                          * to some node that's allowed to be unmapped. This check is done such that
                                          * it happens before any memory may get unmapped, meaning that when given,
                                          * the function will only succeed when the entire range can be unmapped at
                                          * once, and fail with an E_SEGFAULT otherwise.
                                          * When not set, unmapped portions of the given address range are simply ignored,
                                          * and will not count towards the return value's meaning of the number of unmapped
                                          * pages of memory. */
#define VM_UNMAP_NOSPLIT          0x4000 /* Don't split nodes in order to be able to partially unmap one of them.
                                          * Instead, only unmap whole nodes, or nothing at all. */
#define VM_UNMAP_NOKERNPART       0x8000 /* Instead of causing kernel panic when attempting to unmap
                                          * a kernel part, simply ignore the request (this flag is set
                                          * when user-space tries to unmap memory) */
#define VM_UNMAP_ANYTHING         0x0fff /* Unmap anything */

/* Unmap all memory mappings within the given address range.
 * @param: addr:      The base address at which to start unmapping memory.
 * @param: num_bytes: The number of continuous bytes of memory to unmap, starting at `addr'
 * @param: how:       What memory may be unmapped, and how that memory should be unmapped (Set of `VM_UNMAP_*')
 * @return: * :       The actual number of unmapped bytes of memory (when `VM_UNMAP_SEGFAULTIFUNUSED'
 *                    is given, this is always equal to `num_bytes') */
FUNDEF size_t KCALL
vm_unmap(struct vm *__restrict self,
         PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
         PAGEDIR_PAGEALIGNED size_t num_bytes,
         unsigned int how DFL(VM_UNMAP_ANYTHING))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);



/* Update access protection flags within the given address range.
 * @param: addr:       The base address at which to start changing protection.
 * @param: num_bytes:  The number of continuous bytes of memory to change, starting at `addr'
 * @param: prot_mask:  Mask of protection bits that should be kept (Set of `VM_PROT_*').
 * @param: prot_flags: Set of protection bits that should be added (Set of `VM_PROT_*').
 * @param: how:        What memory may be updated, and how that memory should be updated (Set of `VM_UNMAP_*')
 * @return: * :        The actual number of updated bytes of memory (when `VM_UNMAP_SEGFAULTIFUNUSED'
 *                     is given, this is always equal to `num_bytes') */
FUNDEF size_t KCALL
vm_protect(struct vm *__restrict self,
           PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
           PAGEDIR_PAGEALIGNED size_t num_bytes,
           uintptr_t prot_mask, uintptr_t prot_flags,
           unsigned int how DFL(VM_UNMAP_ANYTHING))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);



/* Insert the given node into its associated VM (self->vn_vm)
 * NOTE: The caller must be holding a write-lock to the associated VM. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_node_insert)(struct vm_node *__restrict self);

/* Remove a given node from the specified VM.
 * NOTE: The caller must be holding a write-lock to the associated VM. */
FUNDEF NOBLOCK NONNULL((1)) struct vm_node *
NOTHROW(KCALL vm_paged_node_remove)(struct vm *__restrict self, pageid_t page);

LOCAL NOBLOCK NONNULL((1)) struct vm_node *
NOTHROW(KCALL vm_node_remove)(struct vm *__restrict self,
                              UNCHECKED void *addr) {
	return vm_paged_node_remove(self, PAGEID_ENCODE(addr));
}

/* Without blocking, unmap the given range of kernel RAM. */
FUNDEF NOBLOCK void
NOTHROW(FCALL vm_unmap_kernel_ram)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes,
                                   bool is_zero);
LOCAL NOBLOCK void
NOTHROW(FCALL vm_paged_unmap_kernel_ram)(pageid_t page_index,
                                         size_t num_pages,
                                         bool is_zero) {
	vm_unmap_kernel_ram(PAGEID_DECODE(page_index),
	                    num_pages * PAGESIZE,
	                    is_zero);
}


/* Get the node associated with the given `page'
 * NOTE: The caller must be holding a read-lock on `self'. */
FUNDEF NOBLOCK WUNUSED struct vm_node *
NOTHROW(FCALL vm_getnodeofpageid)(struct vm *__restrict self,
                                  __ARCH_PAGEID_TYPE page);
LOCAL NOBLOCK WUNUSED struct vm_node *
NOTHROW(FCALL vm_getnodeofaddress)(struct vm *__restrict self,
                                   UNCHECKED void *addr) {
	return vm_getnodeofpageid(self, PAGEID_ENCODE(addr));
}


/* Check if some part of the given address range is currently in use.
 * NOTE: The caller must be holding a read-lock on `self'. */
FUNDEF NOBLOCK WUNUSED bool
NOTHROW(FCALL vm_paged_isused)(struct vm *__restrict self,
                               pageid_t min_page, pageid_t max_page);
LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL vm_isused)(struct vm *__restrict self,
                         PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                         PAGEDIR_PAGEALIGNED size_t num_bytes) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	return vm_paged_isused(self,
	                       PAGEID_ENCODE((byte_t *)addr),
	                       PAGEID_ENCODE((byte_t *)addr + num_bytes - 1));
}

/* Try to prefault memory for the given address range within the current VM.
 * This function is intended to be used in conjunction with `memcpy_nopf()',
 * as well as functions using it in order to speed up the lock-copy-unlock-do_buffered_io-repeat
 * cycle by potentially allowing the caller to skip having to perform buffered I/O
 * in cases where the backing memory can be made to be backed by real, physical memory,
 * as opposed to not being mapped at all, or being mapped by VIO memory.
 * NOTE: This function should only be used as a hint for figuring out how buffered I/O should
 *       be performed in face of a memory range that cannot be accessed by `memcpy_nopf()'.
 *       In practice, this means that code using it should be aware that as far as the reliable
 *       semantics of this function go, one valid implementation could simply look like this:
 *       >> PUBLIC size_t FCALL
 *       >> vm_prefault(USER CHECKED void const *addr, size_t num_bytes, bool for_writing)
 *       >>         THROWS(E_WOULDBLOCK, E_BADALLOC) {
 *       >>     assert(num_bytes != 0);
 *       >>     (void)addr;
 *       >>     (void)num_bytes;
 *       >>     (void)for_writing;
 *       >>     // Always return 1, indicating a the necessity of performing just a bit of
 *       >>     // buffered I/O, which will automatically fault at least some memory on access,
 *       >>     // as well as handle the case of VIO memory being accessed.
 *       >>     return 1;
 *       >> }
 * NOTE: For a valid usage example of this function, you may look at the implementation of
 *       the `vm_datapart_(read|write)()' function pair, which uses it in order to determine
 *       the number of bytes that must be processed using `vm_datapart_(read|write)_buffered()'
 * @param: for_writing: When true, make sure that memory within the associated gets
 *                      faulted such that copy-on-write operations are carried out.
 *                      Otherwise, only make sure that memory from the given range
 *                      can be read from (though again: even this is only to be taken
 *                      as a hint. - This function is allowed to just do nothing if
 *                      it wants to)
 * @assume(num_bytes != 0);
 * @return: 0 :
 *     At least 1 page of memory (the one containing `addr') was faulted.
 *     In this case, the caller can immediately go back to performing direct I/O,
 *     though the possibility exists that either due to the backing physical memory
 *     for the given address range being swapped out, or this function choosing not
 *     to prefault the given range in its entirety, more transfer errors may still
 *     occur as memory from the given range is accessed using `memcpy_nopf()'.
 *     Another possible reason for more transfer errors could be a VIO, or unmapped
 *     segment of memory starting further into the given range.
 * @return: >= 1 && <= num_bytes:
 *     In this case, the return value indicates the number of bytes that could not
 *     be faulted (either because not being mapped, or due to being mapped to VIO) */
FUNDEF size_t FCALL vm_prefault(USER CHECKED void const *addr,
                                size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Flags for `vm_forcefault()' */
#define VM_FORCEFAULT_FLAG_READ  0x0000 /* Prefault for the purpose of a future read operation. */
#define VM_FORCEFAULT_FLAG_WRITE 0x0001 /* Prefault for the purpose of a future write operation. */
#define VM_FORCEFAULT_FLAG_NOVIO 0x0002 /* Throw an `E_SEGFAULT' exception when a VIO mapping is encountered. */

/* Force all bytes within the given address range to be faulted for either reading
 * or writing. If any page within the specified range isn't mapped, throw an E_SEGFAULT
 * exception. Otherwise, ensure that copy-on-write is invoked when `VM_FORCEFAULT_FLAG_WRITE'
 * is set, and that irregardless of `VM_FORCEFAULT_FLAG_WRITE', physical memory is allocated
 * for any mapping that can be made to be backed by RAM.
 * Any VIO mappings within the specified range are simply ignored (and will not count
 * towards the returned value), unless `VM_FORCEFAULT_FLAG_NOVIO' is set
 * @return: * : The total number of bytes that become faulted as the result of this
 *              function being called. Note that even if you may be expecting that some
 *              specified address within the range wasn't faulted before, you must still
 *              allow for this function to return `0', since there always exists a
 *              possibility of some other thread changing the backing mappings, or
 *              faulting the mappings themself.
 *              As such, the return value should only be used for probability optimizations,
 *              as well as profiling, but not for the purpose of actual logic decisions.
 * NOTE: This function will also update the page directory mappings for any dataparts
 *       that get faulted during its invocation, meaning that use of `memcpy_nopf()'
 *       within the indicated address range (whilst still checking it for errors for
 *       the even of the mapping changing, or the mapping being a VIO mapping) becomes
 *       possible immediately, without having to force any soft of additional memory
 *       access (note though that this only applies to the page directory of `self',
 *       though also note that if some datapart within the range was already faulted, its
 *       page directory mapping in `self' will still be updated). */
FUNDEF size_t FCALL
vm_paged_forcefault(struct vm *__restrict self,
                    pageid_t minpageid,
                    pageid_t maxpageid,
                    unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
LOCAL size_t FCALL
vm_forcefault(struct vm *__restrict self,
              PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
              PAGEDIR_PAGEALIGNED size_t num_bytes,
              unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	return vm_paged_forcefault(self,
	                           PAGEID_ENCODE((byte_t *)addr),
	                           PAGEID_ENCODE((byte_t *)addr + num_bytes - 1),
	                           flags);
}


/* Lock and (possibly) unshare some given datapart for the purpose of performing
 * writes to its backing memory in the context of the given vm `self'.
 * This funciton is used by the #PF handler, `vm_write()', `vm_prefault()' and `vm_forcefault()'
 * whenever memory is accessed in a way that it is necessary to perform a write.
 * @param: self:              The VM inside of which `node' is mapped.
 * @param: ppart:             [in|out] A reference to the effective part being accessed (may be modified during unsharing)
 * @param: addr:              The access that is being accessed.
 * @param: node:              A pointer to the node that is being accessed. Note that since no lock is held to
 *                            `self' when this function is called, this pointer may already no longer be valid!
 * @param: node_prot:         The original value of `node->vn_prot'
 * @param: node_vpage_offset: Page-offset into `node' to the first page to which write-access is actually required.
 *                            This must be equal to `PAGEID_ENCODE(addr) - vm_node_getstartpageid(node)'
 * @param: node_vpage_count:  The max number of consecutive pages for which write-access is required. For most
 *                            kinds of memory accesses (including #PF-related ones), this argument is simply `1'
 * @param: pdid_unshare:      When non-NULL, set to `true' if the caller should try to merge `part' during decref(),
 *                            as the result of this function having actually performed an unshare.
 * @return: * : The number of consecutive pages loaded for write-access.
 *              In this case, a read-lock on `part' is passed to the caller.
 *              This is always at most `node_vpage_count'
 * @return: 0 : `node' is no longer valid (must re-attempt its lookup)
 *              In this case, no lock on `part' is passed to the caller. */
FUNDEF size_t KCALL
vm_lock_and_unshare_datapart_for_writing(struct vm *__restrict self,
                                         REF struct vm_datapart **__restrict ppart,
                                         USER void *addr,
                                         WEAK struct vm_node *node,
                                         uintptr_half_t node_prot,
                                         size_t node_vpage_offset,
                                         size_t node_vpage_count,
                                         bool *pdid_unshare);


/* Sync changes made to file mappings within the given address
 * range with on-disk file images. (s.a. `vm_datablock_sync()')
 * NOTE: Memory ranges that aren't actually mapped are simply ignored.
 * @return: * : The number of sychronozed bytes. (yes: those are bytes and not pages) */
FUNDEF u64 FCALL
vm_paged_syncmem(struct vm *__restrict self,
                 pageid_t minpage DFL((pageid_t)0),
                 pageid_t maxpage DFL((pageid_t)-1))
		THROWS(E_WOULDBLOCK, ...);
LOCAL u64 FCALL
vm_syncmem(struct vm *__restrict self,
           PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
           PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	return vm_paged_syncmem(self,
	                        PAGEID_ENCODE((byte_t *)addr),
	                        PAGEID_ENCODE((byte_t *)addr + num_bytes - 1));
}


/* Synchronize changes to `self' in the given address range.
 * In SMP, this function will automatically communicate changes to other
 * CPUs making use of the same VM, and doing this synchronously.
 * If the given address range is located within the kernel
 * share-segment, or if `vm_syncall()' was called, a
 * did-change RPC is broadcast to all other CPUs. */
FUNDEF void FCALL vm_paged_sync(struct vm *__restrict self, pageid_t page_index, size_t num_pages) THROWS(E_WOULDBLOCK);
FUNDEF void FCALL vm_paged_syncone(struct vm *__restrict self, pageid_t page_index) THROWS(E_WOULDBLOCK);
FUNDEF void FCALL vm_syncall(struct vm *__restrict self) THROWS(E_WOULDBLOCK);
LOCAL void FCALL
vm_sync(struct vm *__restrict self,
        PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
        PAGEDIR_PAGEALIGNED size_t num_bytes) THROWS(E_WOULDBLOCK) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	vm_paged_sync(self,
	              PAGEID_ENCODE((byte_t *)addr),
	              num_bytes / PAGESIZE);
}
LOCAL void FCALL
vm_syncone(struct vm *__restrict self, UNCHECKED void *addr) THROWS(E_WOULDBLOCK) {
	vm_paged_syncone(self, PAGEID_ENCODE((byte_t *)addr));
}

/* Sync functions for when the caller is already holding a lock to the VM's set of running tasks. */
FUNDEF NOBLOCK void NOTHROW(FCALL vm_paged_sync_locked)(struct vm *__restrict self, pageid_t page_index, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(FCALL vm_paged_syncone_locked)(struct vm *__restrict self, pageid_t page_index);
FUNDEF NOBLOCK void NOTHROW(FCALL vm_syncall_locked)(struct vm *__restrict self);
LOCAL void FCALL
vm_sync_locked(struct vm *__restrict self,
               PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes) THROWS(E_WOULDBLOCK) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	vm_paged_sync_locked(self,
	                     PAGEID_ENCODE((byte_t *)addr),
	                     num_bytes / PAGESIZE);
}
LOCAL void FCALL
vm_syncone_locked(struct vm *__restrict self, UNCHECKED void *addr) THROWS(E_WOULDBLOCK) {
	vm_paged_syncone_locked(self, PAGEID_ENCODE((byte_t *)addr));
}

/* Begin/end syncing page directory mappings:
 * >> pagedir_prepare_map_p(my_vm, start, count);                       // Prepare      (make sure that `pagedir_unmap_p()' will succeed)
 * >> vm_sync_begin(my_vm);                                             // Lock         (make sure we'll be able to sync)
 * >> pagedir_unmap_p(PAGEDIR_P_SELFOFVM(my_vm), start, count);         // Unmap        (Actually delete page mappings)
 * >> vm_paged_sync_end(my_vm, start, count);                           // Unlock+sync  (Make sure that all CPUs got the message about pages having gone away)
 * >> pagedir_unprepare_map_p(PAGEDIR_P_SELFOFVM(my_vm), start, count); // Free         (Clean up memory used to describe the mapping)
 * This order to calls is required to prevent problems at a
 * point in time when those problems could no longer be handled,
 * since the regular vm_paged_sync() functions may throw an E_WOULDBLOCK
 * exception when failing to acquire a lock to `v_tasklock', which
 * is required in order to gather the set of CPUs containing tasks
 * which may need to be synced as well. */
/* TODO: The whole VM sync mechanims was made too complicated.
 *       Instead of forcing a lock to the VM's thread list, we could
 *       instead simply broadcast a TLB shootdown to all CPUs when we
 *       cannot acquire a lock to the task list. That way, the task
 *       list lock doesn't need to be held by the caller, and `vm_sync_begin()'
 *       can fall away entirely! */
#ifdef __INTELLISENSE__
FUNDEF void KCALL vm_sync_begin(struct vm *__restrict effective_vm) THROWS(E_WOULDBLOCK);
FUNDEF bool NOTHROW(KCALL vm_sync_begin_nx)(struct vm *__restrict effective_vm);
FUNDEF NOBLOCK bool NOTHROW(KCALL vm_sync_trybegin)(struct vm *__restrict effective_vm);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_sync_abort)(struct vm *__restrict effective_vm);
#elif defined(CONFIG_NO_SMP)
#define vm_sync_begin(effective_vm)    (void)0
#define vm_sync_begin_nx(effective_vm)  true
#define vm_sync_trybegin(effective_vm)  true
#define vm_sync_abort(effective_vm)    (void)0
#else
#define vm_sync_begin(effective_vm)    vm_tasklock_read(effective_vm)
#define vm_sync_begin_nx(effective_vm) vm_tasklock_read_nx(effective_vm)
#define vm_sync_trybegin(effective_vm) vm_tasklock_tryread(effective_vm)
#define vm_sync_abort(effective_vm)    vm_tasklock_endread(effective_vm)
#endif
FUNDEF NOBLOCK void NOTHROW(FCALL vm_paged_sync_end)(struct vm *__restrict effective_vm, pageid_t page_index, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(FCALL vm_paged_sync_endone)(struct vm *__restrict effective_vm, pageid_t page_index);
FUNDEF NOBLOCK void NOTHROW(FCALL vm_sync_endall)(struct vm *__restrict effective_vm);
LOCAL NOBLOCK void
NOTHROW(FCALL vm_sync_end)(struct vm *__restrict self,
                           PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                           PAGEDIR_PAGEALIGNED size_t num_bytes) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	vm_paged_sync_end(self,
	                  PAGEID_ENCODE((byte_t *)addr),
	                  num_bytes / PAGESIZE);
}
LOCAL NOBLOCK void
NOTHROW(FCALL vm_sync_endone)(struct vm *__restrict self, UNCHECKED void *addr) {
	vm_paged_sync_endone(self, PAGEID_ENCODE((byte_t *)addr));
}


/* Similar to the user-variants above, however sync a kernel-VM range instead,
 * and causing the did-change RPC to be broadcast to _all_ CPUs, instead of
 * having to figure out the specific sub-set of CPUs that would be affected. */
FUNDEF NOBLOCK void NOTHROW(FCALL vm_paged_kernel_sync)(pageid_t page_index, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(FCALL vm_paged_kernel_syncone)(pageid_t page_index);
FUNDEF NOBLOCK void NOTHROW(FCALL vm_kernel_syncall)(void);

LOCAL NOBLOCK void
NOTHROW(FCALL vm_kernel_sync)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes) {
	__hybrid_assert(((uintptr_t)addr & PAGEMASK) == 0);
	__hybrid_assert((num_bytes & PAGEMASK) == 0);
	vm_paged_kernel_sync(PAGEID_ENCODE((byte_t *)addr),
	                     num_bytes / PAGESIZE);
}
LOCAL NOBLOCK void
NOTHROW(FCALL vm_kernel_syncone)(UNCHECKED void *addr) {
	vm_paged_kernel_syncone(PAGEID_ENCODE((byte_t *)addr));
}

/* read/write memory to/form the address space of a given VM
 * Note that these functions behave similar to memcpy_nopf(), in that they
 * will only ever copy _true_ RAM, and never access VIO or cause LOA/COW.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
FUNDEF NOBLOCK size_t
NOTHROW(KCALL vm_read_nopf)(struct vm *__restrict self, UNCHECKED void const *addr,
                            USER CHECKED void *buf, size_t num_bytes);
FUNDEF NOBLOCK size_t
NOTHROW(KCALL vm_write_nopf)(struct vm *__restrict self, UNCHECKED void *addr,
                             USER CHECKED void const *buf, size_t num_bytes);
FUNDEF NOBLOCK size_t
NOTHROW(KCALL vm_memset_nopf)(struct vm *__restrict self, UNCHECKED void *addr,
                              int byte, size_t num_bytes);


/* High-level read/write memory to/from the given `src_vm'.
 * These functions do all the things necessary to read/write memory
 * the same way a regular memory access would, including LOA/COW, as
 * well as properly accessing VIO.
 * @param: force_readable_source:      When true, force `addr' to be readable, ignoring `VM_PROT_READ'
 * @param: force_writable_destination: When true, force `addr' to be writable, invoking COW as needed.  */
FUNDEF void KCALL
vm_read(struct vm *__restrict self,
        UNCHECKED void const *addr, USER CHECKED void *buf,
        size_t num_bytes, bool force_readable_source DFL(false))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
FUNDEF void KCALL
vm_write(struct vm *__restrict self,
         UNCHECKED void *addr, USER CHECKED void const *buf,
         size_t num_bytes, bool force_writable_destination DFL(false))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
/* Same as `vm_write()', but implement memset() semantics instead. */
FUNDEF void KCALL
vm_memset(struct vm *__restrict self,
          UNCHECKED void *addr, int byte, size_t num_bytes,
          bool force_writable_destination DFL(false))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);




#ifndef CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF
/* Copy memory from `src' to `dst', but stop if any sort of #PF happens,
 * regardless of that #PF being handable or not (aka: load-on-access, or
 * copy-on-write will never be triggered by this function, and the same
 * also goes for VIO)
 * This function can be used to copy user-space memory whilst holding an
 * atomic lock, allowing the caller to handle the PF by handling the next
 * data byte/word/etc. individually after releasing the atomic lock, thus
 * allowing a necessary #PF to run its course without the caller holding
 * an atomic lock.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory ranges are:
 *               - `dst + num_bytes - return ... dst + num_bytes - 1'
 *               - `src + num_bytes - return ... src + num_bytes - 1' */
FUNDEF NOBLOCK WUNUSED size_t
NOTHROW(KCALL memcpy_nopf)(USER CHECKED void *dst,
                           USER CHECKED void const *src,
                           size_t num_bytes);
#endif /* !CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF
/* Same as memcpy_nopf(), but implements memset() functionality */
FUNDEF NOBLOCK WUNUSED size_t
NOTHROW(KCALL memset_nopf)(USER CHECKED void *dst,
                           int byte,
                           size_t num_bytes);
#endif /* !CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF
/* Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
FUNDEF NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memeq_nopf)(USER CHECKED void const *lhs,
                          USER CHECKED void const *rhs,
                          size_t num_bytes);
/* Same as `memeq_nopf()', but the function may assume that only `user_buffer' can be faulty. */
FUNDEF NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memeq_ku_nopf)(KERNEL void const *kernel_buffer,
                             USER CHECKED void const *user_buffer,
                             size_t num_bytes);
#else /* !CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF */
#ifndef memeq_ku_nopf
#define memeq_ku_nopf  memeq_nopf
#endif /* !memeq_ku_nopf */
#endif /* CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_READBWLQ_NOPF
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on error */
#define readb_nopf(addr, presult) (memcpy_nopf(presult, addr, 1) == 0)
#define readw_nopf(addr, presult) (memcpy_nopf(presult, addr, 2) == 0)
#define readl_nopf(addr, presult) (memcpy_nopf(presult, addr, 4) == 0)
#define readq_nopf(addr, presult) (memcpy_nopf(presult, addr, 8) == 0)
#endif /* !CONFIG_VM_ARCH_DEFINES_READBWLQ_NOPF */

#ifndef CONFIG_VM_ARCH_DEFINES_WRITEBWLQ_NOPF
/* Try to write `value' into a possibly faulty `addr'
 * Return `true' on success, `false' on error */
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writeb_nopf)(USER CHECKED void *addr, u8 value) { return memcpy_nopf(addr, &value, 1) == 0; }
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writew_nopf)(USER CHECKED void *addr, u16 value) { return memcpy_nopf(addr, &value, 2) == 0; }
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writel_nopf)(USER CHECKED void *addr, u32 value) { return memcpy_nopf(addr, &value, 4) == 0; }
LOCAL NOBLOCK WUNUSED bool NOTHROW(KCALL writeq_nopf)(USER CHECKED void *addr, u64 value) { return memcpy_nopf(addr, &value, 8) == 0; }
#endif /* !CONFIG_VM_ARCH_DEFINES_WRITEBWLQ_NOPF */


/* Descriptor for a lock held for the purposes of DMA */
struct vm_dmalock {
	REF struct vm_datapart *dl_part; /* [1..1] The data part to which a read-lock is being held. */
};

/* Release the given DMA lock */
#ifdef __INTELLISENSE__
NOBLOCK NONNULL((1)) void
NOTHROW(vm_dmalock_release)(struct vm_dmalock *__restrict self);
#else /* __INTELLISENSE__ */
#define vm_dmalock_release(x) \
	(sync_endread((x)->dl_part), decref_unlikely((x)->dl_part))
#endif /* !__INTELLISENSE__ */




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
 * @param: buf:       [vm_startdmav[_nx]] The scatter-gather list of virtual memory ranges to lock.
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
FUNDEF NONNULL((1, 2, 3, 5)) size_t KCALL
vm_startdma(struct vm *__restrict effective_vm,
            vm_dmarangefunc_t prange, vm_dmaresetfunc_t preset, void *arg,
            struct vm_dmalock *__restrict lockvec, size_t lockcnt,
            UNCHECKED void *vaddr, size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2, 3, 5, 7)) size_t KCALL
vm_startdmav(struct vm *__restrict effective_vm,
             vm_dmarangefunc_t prange, vm_dmaresetfunc_t preset, void *arg,
             struct vm_dmalock *__restrict lockvec, size_t lockcnt,
             struct aio_buffer const *__restrict vaddr_buf, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2, 3, 5)) size_t
NOTHROW(KCALL vm_startdma_nx)(struct vm *__restrict effective_vm,
                              vm_dmarangefunc_t prange, vm_dmaresetfunc_t preset, void *arg,
                              struct vm_dmalock *__restrict lockvec, size_t lockcnt,
                              UNCHECKED void *vaddr, size_t num_bytes, bool for_writing);
FUNDEF NONNULL((1, 2, 3, 5, 7)) size_t
NOTHROW(KCALL vm_startdmav_nx)(struct vm *__restrict effective_vm,
                               vm_dmarangefunc_t prange, vm_dmaresetfunc_t preset, void *arg,
                               struct vm_dmalock *__restrict lockvec, size_t lockcnt,
                               struct aio_buffer const *__restrict vaddr_buf, bool for_writing);

/* Similar to `vm_startdma[v][_nx]', however instead used to enumerate the DMA memory range individually.
 * @param: prange:     A callback that is invoked for each affected physical memory range
 *                     Should this callback return `false', enumeration will half and the
 *                     function will return the number of previously successfully enumerated
 *                     DMA bytes.
 * @param: arg:        Argument passed to `prange' upon execution.
 * @param: vaddr:     [vm_startdma[_nx]] The base address where locking should start.
 * @param: num_bytes: [vm_startdma[_nx]] The number of continuous bytes that should be locked.
 * @param: buf:       [vm_startdmav[_nx]] The scatter-gather list of virtual memory ranges to lock.
 * @param: for_writing:When true, unshare copy-on-write mappings of associated memory, allowing the
 *                     caller to then write to the acquired memory ranges without accidentally having
 *                     any changes made appear in PRIVATE mappings of the associated memory region.
 * @return: * : The number of DMA bytes successfully enumerated (sum of
 *             `num_bytes' in all calls to `*prange', where `true' was returned)
 *              Upon full success, this is identical to the given `num_bytes' / `aio_buffer_size(buf)',
 *              though for the same reasons that `vm_startdma[v][_nx]' can fail (s.a. `@return: 0' cases),
 *              this may be less than that */
FUNDEF NONNULL((1, 2)) size_t KCALL
vm_enumdma(struct vm *__restrict effective_vm,
           vm_dmarangefunc_t prange, void *arg,
           UNCHECKED void *vaddr, size_t num_bytes,
           bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2, 4)) size_t KCALL
vm_enumdmav(struct vm *__restrict effective_vm,
            vm_dmarangefunc_t prange, void *arg,
            struct aio_buffer const *__restrict vaddr_buf,
            bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) size_t
NOTHROW(KCALL vm_enumdma_nx)(struct vm *__restrict effective_vm,
                             vm_dmarangefunc_t prange, void *arg,
                             UNCHECKED void *vaddr, size_t num_bytes,
                             bool for_writing);
FUNDEF NONNULL((1, 2, 4)) size_t
NOTHROW(KCALL vm_enumdmav_nx)(struct vm *__restrict effective_vm,
                              vm_dmarangefunc_t prange, void *arg,
                              struct aio_buffer const *__restrict vaddr_buf,
                              bool for_writing);


/* Stop DMAing by releasing all of the specified DMA locks.
 * NOTE: The caller must ensure that `lockcnt == return(vm_startdma*())', and
 *       that the specified `lockvec' is either the exact same `lockvec' originally
 *       passed to `vm_startdma*()', or an identical memory copy of it. */
FUNDEF NONNULL((1)) NOBLOCK void
NOTHROW(FCALL vm_stopdma)(struct vm_dmalock *__restrict lockvec, size_t lockcnt);

struct path;
struct directory_entry;
struct regular_node;

/* Load an executable binary `exec_node' into a temporary, emulated VM.
 * If this succeeds, clear all of the mappings from `effective_vm', and
 * replace them with the contents of the temporary, emulated VM (such
 * that the entire process of mapping the new contents is always able
 * to either seamlessly restore the old memory mappings, or not even
 * touch them at all upon error)
 * -> This function is used to implement the exec() family of system calls
 *    in such that exec() is always able to allow the calling program to
 *    handle load errors (at least so long as those errors aren't caused
 *    by the executable's initialization, such as missing libraries)
 * NOTE: Upon successful return, all threads using the given `effective_vm' (excluding
 *       the caller themself if they are using the VM, too) will have been terminated.
 * @param: effective_vm: The VM into which to map the executable.
 *                       This must not be the kernel VM, which causes an assertion failure.
 * @param: user_state:   The user-space CPU state to update upon success in a manner that
 *                       proper execution of the loaded binary is possible.
 *                       Note however that in the case of a dynamic binary, a dynamic linker
 *                       may be injected to perform dynamic linking whilst already in user-space.
 * @param: exec_path:    Filesystem path for the directory inside of which `exec_node' is located.
 * @param: exec_dentry:  Directory entry containing the filename of `exec_node'
 * @param: exec_node:    The filesystem node which should be loaded as an executable binary.
 * @param: argc_inject:  The number of arguments from `argv_inject' to inject at the beginning of the user-space argc/argv vector.
 * @param: argv_inject:  Vector of arguments to inject at the beginning of the user-space argc/argv vector.
 * @param: argv:         NULL-terminated vector of arguments to-be passed to program being loaded.
 * @param: envp:         NULL-terminated vector of environment variables to-be passed to program being loaded.
 * @return: * :          A pointer to the user-space register state to-be loaded in order to start
 *                       execution of the newly loaded binary (usually equal to `user_state')
 * @throw: E_BADALLOC:   Insufficient memory
 * @throw: E_SEGFAULT:   The given `argv', `envp', or one of their pointed-to strings is faulty
 * @throw: E_NOT_EXECUTABLE: The given `exec_node' was not recognized as an acceptable binary. */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5)) struct icpustate *KCALL
vm_exec(struct vm *__restrict effective_vm,
        struct icpustate *__restrict user_state,
        struct path *__restrict exec_path,
        struct directory_entry *__restrict exec_dentry,
        struct regular_node *__restrict exec_node,
        size_t argc_inject, KERNEL char const *const *argv_inject,
#ifdef __ARCH_HAVE_COMPAT
        USER CHECKED void const *argv,
        USER CHECKED void const *envp,
        bool argv_is_compat
#else /* __ARCH_HAVE_COMPAT */
        USER UNCHECKED char const *USER CHECKED const *argv,
        USER UNCHECKED char const *USER CHECKED const *envp
#endif /* !__ARCH_HAVE_COMPAT */
        )
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR);

#if defined(__ARCH_HAVE_COMPAT) && defined(__cplusplus)
extern "C++" {
LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5)) struct icpustate *KCALL
vm_exec(struct vm *__restrict effective_vm,
        struct icpustate *__restrict user_state,
        struct path *__restrict exec_path,
        struct directory_entry *__restrict exec_dentry,
        struct regular_node *__restrict exec_node,
        size_t argc_inject, KERNEL char const *const *argv_inject,
        USER UNCHECKED char const *USER CHECKED const *argv,
        USER UNCHECKED char const *USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	return vm_exec(effective_vm, user_state, exec_path,
	               exec_dentry, exec_node, argc_inject,
	               argv_inject, argv, envp, false);
}
}
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5)) struct icpustate *KCALL
vm_exec32(struct vm *__restrict effective_vm,
          struct icpustate *__restrict user_state,
          struct path *__restrict exec_path,
          struct directory_entry *__restrict exec_dentry,
          struct regular_node *__restrict exec_node,
          size_t argc_inject, KERNEL char const *const *argv_inject,
          USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *argv,
          USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	return vm_exec(effective_vm, user_state, exec_path,
	               exec_dentry, exec_node, argc_inject,
	               argv_inject, argv, envp, true);
}
#else /* __ARCH_COMPAT_SIZEOF_POINTER == 4 */
#define vm_exec32 vm_exec
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != 4 */

#if __ARCH_COMPAT_SIZEOF_POINTER == 8
LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5)) struct icpustate *KCALL
vm_exec64(struct vm *__restrict effective_vm,
          struct icpustate *__restrict user_state,
          struct path *__restrict exec_path,
          struct directory_entry *__restrict exec_dentry,
          struct regular_node *__restrict exec_node,
          size_t argc_inject, KERNEL char const *const *argv_inject,
          USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *argv,
          USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	return vm_exec(effective_vm, user_state, exec_path,
	               exec_dentry, exec_node, argc_inject,
	               argv_inject, argv, envp, true);
}
#else /* __ARCH_COMPAT_SIZEOF_POINTER == 8 */
#define vm_exec64 vm_exec
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != 8 */
#endif /* __ARCH_HAVE_COMPAT && __cplusplus */


/* Assert that `self' is a regular node for the purpose of being used as the
 * file to-be executed in an exec() system call, by throwing one of the annotated
 * exceptions if this isn't the case. */
FUNDEF NONNULL((1)) void KCALL
vm_exec_assert_regular(struct inode *__restrict self)
		THROWS(E_FSERROR_IS_A_DIRECTORY,
		       E_FSERROR_IS_A_SYMBOLIC_LINK,
		       E_NOT_EXECUTABLE_NOT_REGULAR);



struct vm_mapinfo {
	/* VM Memory mapping information (as passed to `vm_enum_callback_t') */
	UNCHECKED void             *vmi_min;    /* Address of the lowest mapped byte */
	UNCHECKED void             *vmi_max;    /* [> vmi_min] Address of the greatest mapped byte */
	uintptr_half_t              vmi_prot;   /* VM Node protection (Set of `VM_PROT_*'). */
	REF struct vm_datablock    *vmi_block;  /* [0..1] Mapped data block (or NULL of reserved memory mappings) */
	pos_t                       vmi_offset; /* Byte-offset into `vmi_block', where the mapping at `vmi_min' starts. */
	REF struct path            *vmi_fspath; /* [0..1] Mapped object filesystem path (or NULL if unknown or N/A) */
	REF struct directory_entry *vmi_fsname; /* [0..1] Mapped object filesystem name (or NULL if unknown or N/A) */
	size_t                      vmi_index;  /* ID of the first `struct vm_node' that this area is apart of.
	                                         * For this purpose, node-ids are counted such that the first node
	                                         * that either overlaps, or comes after `enum_minaddr' has `vmi_index=0'.
	                                         * This counter is used to generate INode numbers for `/proc/[pid]/map_files/...' */
};
#define vm_mapinfo_size(self) ((size_t)((byte_t *)(self)->vmi_max - (byte_t *)(self)->vmi_min) + 1)


/* Callback for `vm_enum()'
 * @param: arg:   The argument (cookie) originally passed to `vm_enum()'
 * @param: info:  Information about the mapping range being enumerated.
 * @return: >= 0: Continue enumeration and add the result to the sum eventually returned by `vm_enum()'
 * @return: < 0:  Halt enumeration immediatly by having `vm_enum()' re-return this same value. */
typedef ssize_t (FCALL *vm_enum_callback_t)(void *arg, struct vm_mapinfo *__restrict info);

/* Enumerate all mappings contained within the given `enum_minaddr...enum_maxaddr'
 * address range within the given VM `self'. This function will automatically re-
 * assemble memory mappings that had previously been split into multiple nodes,
 * such that adjacent `struct vm_node's that describe a contiguous memory mapping
 * do not appear as individual, separate nodes.
 * @param: cb:           A callback that should be invoked for every mapped memory region
 *                       contained with the given address range `enum_minaddr' ... `enum_maxaddr'
 *                       The sum of return values returned by this callback will eventually be
 *                       returned by this function, unless `cb()' returns a negative value, which
 *                       will cause enumeration to halt immediately, and that same value to be
 *                       propagated to the caller.
 *                       Note that mappings are enumerated in strictly ascending order, and that
 *                       this function guaranties that even in the modifications being made to the
 *                       given `self' while enumeration takes place, the `vmi_min' of all future
 *                       mappings will always be `> vmi_max' of every already/currently enumerated
 *                       mapping.
 * @param: arg:          An argument (cookie) to-be passed to `cb()'
 * @param: enum_minaddr: The starting address of mappings to-be enumerated, such that any mapping
 *                       that overlap with `enum_minaddr ... enum_maxaddr' will be enumerated.
 * @param: enum_maxaddr: Same as `enum_minaddr', but specifies the max address of any enumerated
 *                       mapping. */
FUNDEF ssize_t KCALL
vm_enum(struct vm *__restrict self, vm_enum_callback_t cb, void *arg,
#ifdef USERSPACE_END
        UNCHECKED void *enum_minaddr DFL((UNCHECKED void *)0),
        UNCHECKED void *enum_maxaddr DFL((UNCHECKED void *)(USERSPACE_END - 1))
#else /* USERSPACE_END */
        UNCHECKED void *enum_minaddr DFL((UNCHECKED void *)USERSPACE_START),
        UNCHECKED void *enum_maxaddr DFL((UNCHECKED void *)-1)
#endif /* !USERSPACE_END */
        );





/* List of callbacks that should be invoked after vm_exec()
 * These are called alongside stuff like `handle_manager_cloexec()'
 * NOTE: The passed vm is always `THIS_VM', and is never `&vm_kernel' */
DATDEF CALLBACK_LIST(void KCALL(void)) vm_onexec_callbacks;
/* VM initialization/finalization callbacks. */
DATDEF CALLBACK_LIST(void FCALL(struct vm *)) vm_oninit_callbacks;
DATDEF CALLBACK_LIST(void FCALL(struct vm *)) vm_onfini_callbacks;
DATDEF CALLBACK_LIST(void FCALL(struct vm * /*newvm*/, struct vm * /*oldvm*/)) vm_onclone_callbacks;

#ifdef CONFIG_BUILDING_KERNEL_CORE
/* >> void KCALL func(void);
 * Invoked before returning to user-space after a new application was loaded. */
#define DEFINE_PERVM_ONEXEC(func)  DEFINE_CALLBACK(".rodata.callback.pervm.onexec", func)
/* >> void KCALL func(struct vm *__restrict self); */
#define DEFINE_PERVM_INIT(func)    DEFINE_CALLBACK(".rodata.callback.pervm.init", func)
/* >> NOBLOCK void NOTHROW(KCALL func)(struct vm *__restrict self); */
#define DEFINE_PERVM_FINI(func)    DEFINE_CALLBACK(".rodata.callback.pervm.fini", func)
/* >> NOBLOCK void KCALL func(struct vm *__restrict newvm, struct vm *__restrict oldvm); */
#define DEFINE_PERVM_CLONE(func)   DEFINE_CALLBACK(".rodata.callback.pervm.clone", func)
#endif /* CONFIG_BUILDING_KERNEL_CORE */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_H */
