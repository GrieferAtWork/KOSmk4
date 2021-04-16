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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MPART_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MPART_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/types.h>
#include <misc/unlockinfo.h>
#include <sched/lockop.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/__minmax.h>
#include <hybrid/sched/__yield.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>

#include <libvio/api.h> /* LIBVIO_CONFIG_ENABLED */

#if defined(__WANT_MPART_INIT) && __SIZEOF_POS_T__ > __SIZEOF_POINTER__
#include <hybrid/byteorder.h>
#endif /* __WANT_MPART_INIT && __SIZEOF_POS_T__ > __SIZEOF_POINTER__ */

/* Possible values that an mpart block-status can take. */
#define MPART_BLOCK_ST_NDEF 0 /* Contents of backing memory are undefined. */
#define MPART_BLOCK_ST_INIT 1 /* Backing memory is currently being initialized.
                               * After transitioning to `LOAD', `mf_initdone' of the associated mem-file is broadcast.
                               * NOTE: A mem-part that contains at least 1 block with this status cannot be off-loaded
                               *       into  swap  until  the  transition  to  `MPART_BLOCK_ST_LOAD'  has  been  made.
                               *       This  is required  because this state  is used internally  when loading blocks.
                               * NOTE: This state is also used when syncing changed blocks, as it prevents further
                               *       modifications from being performed. */
#define MPART_BLOCK_ST_LOAD 2 /* Backing memory has been loaded. */
#define MPART_BLOCK_ST_CHNG 3 /* Backing memory has been changed. */
#define MPART_BLOCK_STBITS  2 /* # of bits needed to hold a single block-status. */

/* Return the common description of 2 block status values. */
#define MPART_BLOCK_COMMON(a, b) __hybrid_min2(a, b)


/* Possible values for `struct mpart::mp_flags' */
#define MPART_F_NORMAL         0x0000 /* Normal flags. */
#define MPART_F_LOCKBIT        0x0001 /* Lock-bit for this m-part */
#define MPART_F_MAYBE_BLK_INIT 0x0002 /* [lock(MPART_F_LOCKBIT)] There may be blocks with `MPART_BLOCK_ST_INIT'. */
#define MPART_F_GLOBAL_REF     0x0004 /* [lock(WRITE_ONCE)] `mpart_all_list' holds a reference to this part.
                                       * When memory is running low, and  the kernel tries to unload  unused
                                       * memory parts, it  will clear  this flag  for all  parts there  are.
                                       * Also note that this flag is cleared by default when the  associated
                                       * file's `mf_parts' field was/is set to `MFILE_PARTS_ANONYMOUS' */
/*efine MPART_F_               0x0008  * ... */
#define MPART_F_BLKST_INL      0x0010 /* [lock(MPART_F_LOCKBIT)][valid_if(MPART_ST_HASST)]
                                       * The  backing  block-state bitset  exists in-line. */
#define MPART_F_NOFREE         0x0020 /* [const] Don't page_free() backing physical memory or swap. */
/*efine MPART_F_               0x0040  * ... */
#define MPART_F_PERSISTENT     0x0080 /* [lock(CLEAR_ONCE)] The `MPART_F_GLOBAL_REF' flag  may not be  cleared to free  up
                                       * memory.  This flag is still cleared when the is being anonymized as the result of
                                       * a call to `mfile_delete()' or  `mfile_makeanon_subrange()'. The only place  where
                                       * this flag makes a difference, is when the global list of mem-parts is scanned for
                                       * parts which are no longer in-use, and  can be destroyed by deleting their  global
                                       * reference.  -  This flag  is set  by default  for  parts of  files that  have the
                                       * `MFILE_F_PERSISTENT' flag set. */
#define MPART_F_COREPART       0x0100 /* [const] Core part (free this part using `mcoreheap_free()' instead of `kfree()') */
#define MPART_F_CHANGED        0x0200 /* [lock(SET(MPART_F_LOCKBIT),
                                       *       CLEAR((:mfile::mf_lock && mp_meta->mpm_dmalocks == 0) ||
                                       *             (:mfile::mf_changed == MFILE_PARTS_ANONYMOUS)))]
                                       * [valid_if(:mfile::mf_changed != MFILE_PARTS_ANONYMOUS)]
                                       * Blocks of this  part (may)  have changed.  This flag  must be  cleared by  the
                                       * associated file after changes have been synced, or the file becomes anonymous. */
#define MPART_F_NOSPLIT        0x0400 /* [const] This mem-part cannot be split, and if doing so would be necessary,
                                       *         then the attempt will instead result in kernel panic. Similarly,
                                       *         this  flag   also  prevents   the   part  from   being   merged. */
#define MPART_F_NOMERGE        0x0800 /* [const] Don't allow this mem-part to be merged. */
#define MPART_F_MLOCK_FROZEN   0x1000 /* [lock(WRITE_ONCE)] The value of the `MPART_F_MLOCK' flag cannot be altered. */
#define MPART_F_MLOCK          0x2000 /* [lock(MPART_F_LOCKBIT)] Locked mem-part (the  part's state  cannot move  away
                                       * from INCORE). Unless `MPART_F_MLOCK_FROZEN' is set, this flag is set whenever
                                       * this part is mapped  by any mem-node that  has the `MNODE_F_MLOCK' flag  set,
                                       * and whenever a mem-node with the  `MNODE_F_MLOCK' flag set has is  destroyed,
                                       * or  has its  `MNODE_F_MLOCK' flag cleared,  all mappings of  the mem-part are
                                       * scanned in search  for other  locked mappings. If  any are  found, then  this
                                       * flag will remain set. If none are found, then this flag is cleared. */
#define MPART_F__RBRED         0x4000 /* [lock(:mfile::mf_lock)] Internal flag: This part is a red node. */
/*efine MPART_F_               0x8000  * ... */


/* Possible values for `struct mpart::mp_state' */
#define MPART_ST_VOID       0x0 /* [lock(MPART_F_LOCKBIT)] Part hasn't been accessed, yet. */
#define MPART_ST_SWP        0x1 /* [lock(MPART_F_LOCKBIT)] Part has been off-loaded into swap. */
#define MPART_ST_MEM        0x2 /* [lock(MPART_F_LOCKBIT)] Part has been allocated. */
#ifdef LIBVIO_CONFIG_ENABLED
#define MPART_ST_VIO        0x3 /* [const] Part is backed by VIO. */
#endif /* LIBVIO_CONFIG_ENABLED */
#define MPART_ST_SWP_SC     0x5 /* [lock(MPART_F_LOCKBIT)] Part has been off-loaded into swap (scattered). */
#define MPART_ST_MEM_SC     0x6 /* [lock(MPART_F_LOCKBIT)] Part has been allocated (scattered). */
#ifdef LIBVIO_CONFIG_ENABLED
#define MPART_ST_HASST(x)   ((x) != MPART_ST_VOID && (x) != MPART_ST_VIO)
#else /* LIBVIO_CONFIG_ENABLED */
#define MPART_ST_HASST(x)   ((x) != MPART_ST_VOID)
#endif /* !LIBVIO_CONFIG_ENABLED */
#define MPART_ST_INCORE(x)  ((x) >= MPART_ST_MEM && (x) != MPART_ST_SWP_SC)
#define MPART_ST_INMEM(x)   ((x) == MPART_ST_MEM || (x) == MPART_ST_MEM_SC)
#define MPART_ST_SCATTER(x) ((x)&4) /* Check if a scatter-list is being used. */


#ifdef __CC__
DECL_BEGIN

struct mpart;     /* Memory file part. */
struct mpartmeta; /* Memory file part meta-data. */
struct mfile;     /* Memory storage owner/descriptor. */
struct mnode;     /* Memory range descriptor. */
struct iov_buffer;
struct iov_physbuffer;

#ifndef __mnode_list_defined
#define __mnode_list_defined
LIST_HEAD(mnode_list, mnode);
#endif /* !__mnode_list_defined */

#ifndef __mpart_list_defined
#define __mpart_list_defined
LIST_HEAD(mpart_list, mpart);
#endif /* !__mpart_list_defined */

#ifndef __mnode_slist_defined
#define __mnode_slist_defined
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

#ifndef __mpart_slist_defined
#define __mpart_slist_defined
SLIST_HEAD(mpart_slist, mpart);
#endif /* !__mpart_slist_defined */

/* Block-index within some given mem-file. */
#ifndef __mfile_block_t_defined
#define __mfile_block_t_defined
typedef pos_t mfile_block_t;
#endif /* !__mfile_block_t_defined */

#ifndef __mpart_reladdr_t_defined
#define __mpart_reladdr_t_defined
typedef size_t mpart_reladdr_t;
#endif /* !__mpart_reladdr_t_defined */


struct mchunk {
	physpage_t    mc_start; /* Starting page number of physical memory associated with the ram block. */
	physpagecnt_t mc_size;  /* Number of continuous physical memory pages used by this block. */
};
struct mchunkvec {
	struct mchunk *ms_v;    /* [1..ms_c][owned] Vector of mem-chunks */
	size_t         ms_c;    /* [!0] # of mem-chunks */
};


#define __ALIGNOF_MPART __ALIGNOF_INT64__
#if __SIZEOF_POINTER__ == 4
#define __SIZEOF_MPART 80
#elif __SIZEOF_POINTER__ == 8
#define __SIZEOF_MPART 144
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported pointer size"
#endif /* __SIZEOF_POINTER__ != ... */

#if 0 /* Static initializer template: */
//	MPART_INIT_mp_refcnt(FILLME),
//	MPART_INIT_mp_flags(MPART_F_NOSPLIT | MPART_F_NOMERGE |
//	                    MPART_F_MLOCK_FROZEN | MPART_F_MLOCK),
//	MPART_INIT_mp_state(MPART_ST_MEM),
//	MPART_INIT_mp_file(&mfile_ndef),
//	MPART_INIT_mp_copy(LIST_HEAD_INITIALIZER(FILLME.mp_copy)),
//	MPART_INIT_mp_share(LIST_HEAD_INITIALIZER(FILLME.mp_share)),
//	MPART_INIT_mp_lockops(SLIST_HEAD_INITIALIZER(FILLME.mp_lockops)),
//	MPART_INIT_mp_allparts(LIST_ENTRY_UNBOUND_INITIALIZER),
//	MPART_INIT_mp_minaddr(0),
//	MPART_INIT_mp_maxaddr(FILLME - 1),
//	MPART_INIT_mp_changed({}),
//	MPART_INIT_mp_filent({}),
//	MPART_INIT_mp_blkst_ptr(NULL),
//	MPART_INIT_mp_mem(FILLME, CEILDIV(FILLME, PAGESIZE)),
//	MPART_INIT_mp_meta(NULL)
#endif

struct mpart {
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_refcnt(mp_refcnt) mp_refcnt
#define MPART_INIT_mp_flags(mp_flags)   mp_flags
#define MPART_INIT_mp_state(mp_state)   mp_state
#endif /* __WANT_MPART_INIT */
	WEAK refcnt_t                 mp_refcnt;    /* Reference counter. */
	uintptr_half_t                mp_flags;     /* Memory part flags (set of `MPART_F_*') */
	uintptr_half_t                mp_state;     /* [lock(MPART_F_LOCKBIT)]
	                                             * [const_if(EXISTS(MPART_BLOCK_ST_INIT) ||
	                                             *           mp_meta->mpm_dmalocks != 0)]
	                                             * Memory part state (one of `MPART_ST_*') */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_file(mp_file) mp_file
#endif /* __WANT_MPART_INIT */
	REF struct mfile             *mp_file;      /* [1..1][lock(MPART_F_LOCKBIT)][const_if(EXISTS(MPART_BLOCK_ST_INIT))]
	                                             * The associated file. (Cannot be altered as long as any `MPART_BLOCK_ST_INIT' blocks exist) */
	/* WARNING: The  following  2  lists  may  contain  already-destroyed nodes.
	 *          To check if  a node  has been destroyed,  you may  check if  the
	 *          pointed-to `mn_mman' was  destroyed, since  that field  normally
	 *          only contains a weak reference,  meaning that if the  underlying
	 *          MMAN got destroyed, then it will have attempted to unbind all of
	 *          its remaining  nodes, and  those that  it couldn't  unbind  will
	 *          have  been added to the dead-nodes chain of the associated part. */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_copy(...)    __VA_ARGS__
#define MPART_INIT_mp_share(...)   __VA_ARGS__
#define MPART_INIT_mp_lockops(...) __VA_ARGS__
#endif /* __WANT_MPART_INIT */
	struct mnode_list             mp_copy;      /* [0..n][lock(MPART_F_LOCKBIT)] List of copy-on-write mappings. */
	struct mnode_list             mp_share;     /* [0..n][lock(MPART_F_LOCKBIT)] List of shared mappings. */
	Toblockop_slist(struct mpart) mp_lockops;   /* [0..n][lock(ATOMIC)] List of lock operations. (s.a. `mpart_lockops_reap()') */
#ifdef __WANT_MPART__mp_newglobl
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_allparts(mp_allparts) { mp_allparts }
#endif /* __WANT_MPART_INIT */
	union {
		LIST_ENTRY(mpart)         mp_allparts;  /* [lock(:mpart_all_lock)][valid_if(mp_state != MPART_ST_VIO)]
		                                         * Chain of all mem-parts in existence. (may be unbound for certain parts)
		                                         * NOTE: For  VIO  parts,  this  list entry  is  initialized  as  unbound! */
		SLIST_ENTRY(REF mpart)   _mp_newglobl;  /* Used internally to enqueue new parts into the global list of parts. */
	};
#else /* __WANT_MPART__mp_newglobl */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_allparts(mp_allparts) mp_allparts
#endif /* __WANT_MPART_INIT */
	LIST_ENTRY(mpart)             mp_allparts;  /* [0..1][lock(:mpart_all_lock)][valid_if(mp_state != MPART_ST_VIO)]
	                                             * Chain of all mem-parts in existence. (may be unbound for certain parts)
	                                             * NOTE: For VIO parts, this list entry is initialized as unbound! */
#endif /* !__WANT_MPART__mp_newglobl */
#if defined(__WANT_MPART_INIT) && __SIZEOF_POS_T__ > __SIZEOF_POINTER__
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _MPART_INIT_ADDR(val) { { (uintptr_t)(val), 0 } }
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define _MPART_INIT_ADDR(val) { { 0, (uintptr_t)(val) } }
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#define MPART_INIT_mp_minaddr _MPART_INIT_ADDR
#define MPART_INIT_mp_maxaddr _MPART_INIT_ADDR
	union {
		uintptr_t                _mp_static_minaddr[__SIZEOF_POS_T__ / __SIZEOF_POINTER__];
		PAGEDIR_PAGEALIGNED pos_t mp_minaddr;   /* [lock(READ (MPART_F_LOCKBIT || mp_meta->mpm_ftxlock || mp_file->mf_lock || ANY(mp_copy, mp_share)->mn_mman->mm_lock),
		                                         *       WRITE(MPART_F_LOCKBIT && mp_meta->mpm_ftxlock && mp_file->mf_lock && ALL(mp_copy, mp_share)->mn_mman->mm_lock))]
		                                         *                                \------------------/    \--------------/
		                                         *                                 Only if allocated      Only if not anon!
		                                         * [const_if(EXISTS(MPART_BLOCK_ST_INIT) ||
		                                         *           mp_meta->mpm_dmalocks != 0)]
		                                         * In-file starting address of this part.
		                                         * Aligned by PAGESIZE, and the associated file's block-size. */
	};
	union {
		uintptr_t                _mp_static_maxaddr[__SIZEOF_POS_T__ / __SIZEOF_POINTER__];
		pos_t                     mp_maxaddr;   /* [lock(like(mp_minaddr))][const_if(like(mp_minaddr))]
		                                         * In-file max address of this  part. (NOTE: when 1  is
		                                         * added, also aligned like `mp_minaddr' must be) */
	};
#else /* __WANT_MPART_INIT && __SIZEOF_POS_T__ > __SIZEOF_POINTER__ */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_minaddr (pos_t)
#define MPART_INIT_mp_maxaddr (pos_t)
#endif /* __WANT_MPART_INIT */
	/* TODO: Change all system components such that everything is able to deal with `mp_minaddr' being altered! */
	PAGEDIR_PAGEALIGNED pos_t     mp_minaddr;   /* [lock(READ (MPART_F_LOCKBIT || mp_meta->mpm_ftxlock || mp_file->mf_lock || ANY(mp_copy, mp_share)->mn_mman->mm_lock),
	                                             *       WRITE(MPART_F_LOCKBIT && mp_meta->mpm_ftxlock && mp_file->mf_lock && ALL(mp_copy, mp_share)->mn_mman->mm_lock))]
	                                             *                                \------------------/    \--------------/
	                                             *                                 Only if allocated      Only if not anon!
	                                             * [const_if(EXISTS(MPART_BLOCK_ST_INIT) ||
	                                             *           mp_meta->mpm_dmalocks != 0)]
	                                             * In-file starting address of this part.
	                                             * Aligned by PAGESIZE, and the associated file's block-size. */
	pos_t                         mp_maxaddr;   /* [lock(like(mp_minaddr))][const_if(like(mp_minaddr))]
	                                             * In-file max address of this  part. (NOTE: when 1  is
	                                             * added, also aligned like `mp_minaddr' must be) */
#endif /* !__WANT_MPART_INIT || __SIZEOF_POS_T__ <= __SIZEOF_POINTER__ */
#ifdef __WANT_MPART__mp_dead
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_changed(...) { __VA_ARGS__ }
#endif /* __WANT_MPART_INIT */
	union {
		SLIST_ENTRY(REF mpart)    mp_changed;   /* [lock(ATOMIC)][valid_if(mp_file->mf_ops->mo_saveblocks &&
		                                         *                         !mpart_isanon(self) && MPART_F_CHANGED)]
		                                         * Per-file chain of mem-parts that have changed.
		                                         * When  the  associated  file  supports  the  `mo_saveblocks', then
		                                         * whenever the `MPART_F_CHANGED' flag is set, this part is inserted
		                                         * into its file's `mf_changed' list.
		                                         * Also note that  changed mem-parts  are kept alive  by the  associated
		                                         * file, since this list contains references, rather than weak pointers. */
		SLIST_ENTRY(mpart)       _mp_dead;      /* [lock(ATOMIC)] Chain of dead parts. */
	};
#else /* __WANT_MPART__mp_dead */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_changed(...) __VA_ARGS__
#endif /* __WANT_MPART_INIT */
	SLIST_ENTRY(REF mpart)        mp_changed;   /* [lock(ATOMIC)][valid_if(mp_file->mf_ops->mo_saveblocks &&
	                                             *                         !mpart_isanon(self) && MPART_F_CHANGED)]
	                                             * Per-file chain of mem-parts that have changed.
	                                             * When  the  associated  file  supports  the  `mo_saveblocks', then
	                                             * whenever the `MPART_F_CHANGED' flag is set, this part is inserted
	                                             * into its file's `mf_changed' list.
	                                             * Also note that  changed mem-parts  are kept alive  by the  associated
	                                             * file, since this list contains references, rather than weak pointers. */
#endif /* !__WANT_MPART__mp_dead */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_filent(...) __VA_ARGS__
#endif /* __WANT_MPART_INIT */
	RBTREE_NODE(struct mpart)     mp_filent;    /* [lock(READ (MPART_F_LOCKBIT || mp_file->mf_lock),
	                                             *       WRITE(MPART_F_LOCKBIT && mp_file->mf_lock))]
	                                             * [valid_if(!mpart_isanon(self))]
	                                             * Entry with the associated file's tree. */
	union {
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_blkst_ptr(mp_blkst_ptr) { mp_blkst_ptr }
#define MPART_INIT_mp_blkst_inl(mp_blkst_inl) { (uintptr_t *)(uintptr_t)(mp_blkst_inl) }
#endif /* __WANT_MPART_INIT */
		/* Block-state bitset. Note that the size of a block is measured in bytes,
		 * may be smaller than a single page, and its actual size is fixed, and is
		 * described by the associated mfile. (s.a. `MPART_BLOCK_ST_*') */
		uintptr_t                *mp_blkst_ptr; /* [lock(MPART_F_LOCKBIT)][0..1][lock(MPART_F_LOCKBIT || EXISTS(MPART_BLOCK_ST_INIT))]
		                                         * [valid_if(MPART_ST_HASST && !MPART_F_BLKST_INL)]
		                                         * NOTE: When set to `NULL', then monitoring the part for changes becomes
		                                         *       impossible, and the caller should  act as though all parts  were
		                                         *       using `MPART_BLOCK_ST_CHNG' as their state.
		                                         *       This is usually only done for parts where write-monitoring
		                                         *       doesn't  really  make  any  sense,  such  as `mfile_phys'.
		                                         * NOTE: Changing the state of block that used to be `MPART_BLOCK_ST_INIT' to
		                                         *       anything else may be done atomically, and without holding any locks. */
		uintptr_t                 mp_blkst_inl; /* [lock(MPART_F_LOCKBIT)]
		                                         * [valid_if(MPART_ST_HASST && MPART_F_BLKST_INL)] */
	};
	union {
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_mem(mc_start, mc_size) { { mc_start, mc_size } }
#endif /* __WANT_MPART_INIT */
		/* NOTE: Everything in here is implicitly:
		 * [lock(MPART_F_LOCKBIT)]
		 * [const_if(EXISTS(MPART_BLOCK_ST_INIT) || mp_meta->mpm_dmalocks != 0)] */

		/* NOTE: When `mchunkvec'  is used,  individual chunks  are always  chosen  such
		 *       that  a whole blocks  are always contained within  a single chunk, even
		 *       when the size of a  block is larger than the  size of a page (in  which
		 *       case multiple physical pages are required to represent a single block)! */
		struct mchunk             mp_mem;       /* [valid_if(MPART_ST_MEM)] Physically allocated memory */
		struct mchunkvec          mp_mem_sc;    /* [valid_if(MPART_ST_MEM_SC)] Scattered memory */
		/* NOTE: Unlike  mem-data, swap data  only contains blocks that  have their state set
		 *       to `MPART_BLOCK_ST_CHNG', meaning that the total number of swap pages equals
		 *       the ceil-aligned number of pages needed to represent as many blocks as there
		 *       are MPART_BLOCK_ST_CHNG-entries in the status-bitset.
		 * With this in mind, swap data is tightly packed, such that only modified blocks are
		 * ever actually written to swap.
		 *
		 * Also note that swap storage should not be used for mem-parts who's file supports
		 * the `mo_saveblocks' operator. In that case it is still possible to off-load such
		 * parts  into swap, but doing so is pointless.  If the intend is to free up unused
		 * memory, then  you  should  instead write-back  modified  files  (possibly  using
		 * `mpart_lock_acquire_and_setcore_unwrite_sync') and  only  use  swap  memory  (of
		 * changed blocks) if the part is still marked as changed.
		 * Unchanged,  but allocated blocks can simply be  freed, and you are allowed to
		 * assume that any unchanged block can always be re-constructed at a later point
		 * in time by making use of the `mo_loadblocks' operator.
		 *
		 * Also note that  parts with  the `MPART_F_NOFREE' flag  set should  never be  off-
		 * loaded into swap: If not only because doing so wouldn't actually free up physical
		 * memory, doing so  might actually  cause problems (since  `MPART_F_NOFREE' is  set
		 * by special files such as `mfile_phys')
		 */
		struct mchunk             mp_swp;       /* [valid_if(MPART_ST_SWP)] Physically allocated swap */
		struct mchunkvec          mp_swp_sc;    /* [valid_if(MPART_ST_SWP_SC)] Scattered swap */
	};
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_meta(mp_meta) { mp_meta }
#endif /* __WANT_MPART_INIT */
	struct mpartmeta             *mp_meta;      /* [0..1][owned][lock(WRITE_ONCE)] Runtime meta-data for futex and RTM support. */
};


#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_filent_asanon() MPART_INIT_mp_filent({  })
#define MPART_INIT_PHYS(file, first_page, page_count, num_bytes)     \
	{                                                                \
		MPART_INIT_mp_refcnt(1),                                     \
		MPART_INIT_mp_flags(MPART_F_NOFREE | MPART_F_NOSPLIT |       \
		                    MPART_F_MLOCK | MPART_F_MLOCK_FROZEN),   \
		MPART_INIT_mp_state(MPART_ST_MEM),                           \
		MPART_INIT_mp_file(file),                                    \
		MPART_INIT_mp_copy(LIST_HEAD_INITIALIZER(~)),                \
		MPART_INIT_mp_share(LIST_HEAD_INITIALIZER(~)),               \
		MPART_INIT_mp_lockops(SLIST_HEAD_INITIALIZER(~)),            \
		MPART_INIT_mp_allparts(LIST_ENTRY_UNBOUND_INITIALIZER),      \
		MPART_INIT_mp_minaddr(0),                                    \
		MPART_INIT_mp_maxaddr((num_bytes)-1),                        \
		MPART_INIT_mp_changed({}),                                   \
		MPART_INIT_mp_filent_asanon(),                               \
		MPART_INIT_mp_blkst_ptr(__NULLPTR),                          \
		MPART_INIT_mp_mem(first_page, page_count),                   \
		MPART_INIT_mp_meta(__NULLPTR)                                \
	}
#endif /* __WANT_MPART_INIT */



/* Get bounds for the given mem-node. */
#define mpart_getminaddr(self) (self)->mp_minaddr                                      /* WARNING: This one requires a lock! */
#define mpart_getmaxaddr(self) (self)->mp_maxaddr                                      /* WARNING: This one requires a lock! */
#define mpart_getendaddr(self) ((self)->mp_maxaddr + 1)                                /* WARNING: This one requires a lock! */
#define mpart_getsize(self)    ((size_t)((self)->mp_maxaddr - (self)->mp_minaddr) + 1) /* WARNING: This one requires a lock! */

#define mpart_getminblock(self, file)   (mfile_block_t)(mpart_getminaddr(self) >> (file)->mf_blockshift) /* WARNING: This one requires a lock! */
#define mpart_getmaxblock(self, file)   (mfile_block_t)(mpart_getmaxaddr(self) >> (file)->mf_blockshift) /* WARNING: This one requires a lock! */
#define mpart_getendblock(self, file)   (mfile_block_t)(mpart_getendaddr(self) >> (file)->mf_blockshift) /* WARNING: This one requires a lock! */
#define mpart_getblockcount(self, file) (size_t)(mpart_getsize(self) >> (file)->mf_blockshift)           /* WARNING: This one requires a lock! */


/* Check   if  `self'  is  anonymous  (that  is:  `self !in self->mp_file->mf_parts')
 * Note that as long as you're holding a lock to `self', you may make the assumption:
 *    `(!wasdestroyed(self) && !mpart_isanon(self)) -> !mfile_isanon(self->mp_file)'
 * Even when you're not actually holding a lock to the associated file. */
#define mpart_isanon(self) ((self)->mp_filent.rb_par == (struct mpart *)-1)

/* Fill in `self->mp_filent' such that `self' is marked as an anonymous mem-part. */
#ifdef NDEBUG
#define _mpart_init_asanon(self) (void)((self)->mp_filent.rb_par = (struct mpart *)-1)
#elif __SIZEOF_POINTER__ == 4
#define _mpart_init_asanon(self)                                              \
	(void)((self)->mp_filent.rb_par = (struct mpart *)-1,                     \
	       (self)->mp_filent.rb_lhs = (struct mpart *)__UINT32_C(0xcccccccc), \
	       (self)->mp_filent.rb_rhs = (struct mpart *)__UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define _mpart_init_asanon(self)                                                      \
	(void)((self)->mp_filent.rb_par = (struct mpart *)-1,                             \
	       (self)->mp_filent.rb_lhs = (struct mpart *)__UINT64_C(0xcccccccccccccccc), \
	       (self)->mp_filent.rb_rhs = (struct mpart *)__UINT64_C(0xcccccccccccccccc))
#else /* __SIZEOF_POINTER__ == ... */
#define _mpart_init_asanon(self) (void)((self)->mp_filent.rb_par = (struct mpart *)-1)
#endif /* __SIZEOF_POINTER__ != ... */


/* Reference counting control for `struct mpart' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mpart_free)(struct mpart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mpart_destroy)(struct mpart *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct mpart, mp_refcnt, mpart_destroy)


/* Reap lock operations enqueued for execution when `self' can be locked. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mpart_lockops_reap)(struct mpart *__restrict self);
#define mpart_lockops_mustreap(self) (__hybrid_atomic_load((self)->mp_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mpart_lockops_reap(self) _mpart_lockops_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mpart_lockops_reap(self) (void)(!mpart_lockops_mustreap(self) || (_mpart_lockops_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */

/* Lock accessor helpers for `struct mpart' */
#define mpart_lock_tryacquire(self) \
	(!(__hybrid_atomic_fetchor((self)->mp_flags, MPART_F_LOCKBIT, __ATOMIC_SEQ_CST) & MPART_F_LOCKBIT))
#define mpart_lock_release(self)                                                \
	(__hybrid_atomic_and((self)->mp_flags, ~MPART_F_LOCKBIT, __ATOMIC_SEQ_CST), \
	 mpart_lockops_reap(self))
#define mpart_lock_release_f(self) \
	(__hybrid_atomic_and((self)->mp_flags, ~MPART_F_LOCKBIT, __ATOMIC_SEQ_CST))
FORCELOCAL NONNULL((1)) void FCALL
mpart_lock_acquire(struct mpart *__restrict self) {
	while (!mpart_lock_tryacquire(self))
		__hybrid_yield();
}

FORCELOCAL NONNULL((1)) __BOOL FCALL
mpart_lock_acquire_nx(struct mpart *__restrict self) {
	while (!mpart_lock_tryacquire(self)) {
		if (!__hybrid_yield_nx())
			return 0;
	}
	return 1;
}
#define mpart_lock_acquired(self)  (__hybrid_atomic_load((self)->mp_flags, __ATOMIC_ACQUIRE) & MPART_F_LOCKBIT)
#define mpart_lock_available(self) (!(__hybrid_atomic_load((self)->mp_flags, __ATOMIC_ACQUIRE) & MPART_F_LOCKBIT))

/*
__DEFINE_SYNC_MUTEX(struct mpart,
                    mpart_lock_tryacquire,
                    mpart_lock_acquire,
                    mpart_lock_acquire_nx,
                    mpart_lock_release,
                    mpart_lock_acquired,
                    mpart_lock_available)
*/





/* Mem-part tree API. All of these functions require that the caller
 * be holding a lock to the associated file. */
struct mpart_tree_minmax {
	struct mpart *mm_min; /* [0..1] Lowest branch. */
	struct mpart *mm_max; /* [0..1] Greatest branch. */
};
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mpart *NOTHROW(FCALL mpart_tree_locate)(/*nullable*/ struct mpart *root, pos_t key);
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mpart *NOTHROW(FCALL mpart_tree_rlocate)(/*nullable*/ struct mpart *root, pos_t minkey, pos_t maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mpart_tree_insert)(struct mpart **__restrict proot, struct mpart *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL mpart_tree_tryinsert)(struct mpart **__restrict proot, struct mpart *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mpart *NOTHROW(FCALL mpart_tree_remove)(struct mpart **__restrict proot, pos_t key);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mpart *NOTHROW(FCALL mpart_tree_rremove)(struct mpart **__restrict proot, pos_t minkey, pos_t maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mpart_tree_removenode)(struct mpart **__restrict proot, struct mpart *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mpart *NOTHROW(FCALL mpart_tree_prevnode)(struct mpart const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mpart *NOTHROW(FCALL mpart_tree_nextnode)(struct mpart const *__restrict self);
FUNDEF NOBLOCK NONNULL((4)) void NOTHROW(FCALL mpart_tree_minmaxlocate)(struct mpart *root, pos_t minkey, pos_t maxkey, struct mpart_tree_minmax *__restrict result);



/************************************************************************/
/* Low-level mpart APIs                                                 */
/************************************************************************/

/* Initialize  `self->mp_state' and `self->mp_mem' or `self->mp_mem_sc', such
 * that `self'  points to  exactly `total_pages'  pages of  physical  memory.
 * This  function is init-only  and doesn't care about  locks or the whatever
 * the given `self' may point to, meaning it should not be called when `self'
 * was already fully initialized.
 * NOTE: This function assumes that `self->mp_file' has already been initialized,
 *       and will pass that value onto `mfile_alloc_physmem()'! */
FUNDEF NONNULL((1)) void FCALL
mpart_ll_allocmem(struct mpart *__restrict self,
                  size_t total_pages)
		THROWS(E_BADALLOC);

/* Free backing memory using `page_free()'.  When an mchunkvec was  used,
 * also kfree that vector. Requires that `MPART_ST_INMEM(self->mp_state)' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_ll_freemem)(struct mpart *__restrict self);

/* Free backing memory using `page_ccfree()'. When an mchunkvec was used,
 * also kfree that vector. Requires that `MPART_ST_INMEM(self->mp_state)' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_ll_ccfreemem)(struct mpart *__restrict self);

/* Low-level write to  the backing memory  of the  given
 * part. Requires that  `MPART_ST_INMEM(self->mp_state)'
 * The caller must ensure that `offset...+=num_bytes' is
 * in-bounds of the given mem-part! */
FUNDEF NONNULL((1)) void KCALL
mpart_ll_writemem(struct mpart *__restrict self,
                  mpart_reladdr_t offset,
                  void const *__restrict src,
                  size_t num_bytes)
		THROWS(E_SEGFAULT);
/* Low-level bzero-if-!page_iszero() the given address range.
 * The  caller must ensure that `offset...+=num_bytes' is in-
 * bounds of the given mem-part! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mpart_ll_bzeromemcc)(struct mpart *__restrict self,
                                   mpart_reladdr_t offset,
                                   size_t num_bytes);




/************************************************************************/
/* MPart API to lock a part, alongside doing some other operations.     */
/************************************************************************/

/************************************************************************
 * Lock-less mem-part status assertion/goal-approaching functions
 * All of these work on the principle:
 *   #1: Check if the wanted condition has already been met
 *       If so, return `true'
 *   #2: Check if we've (additional)  data needed to meet  the
 *       condition  has been  given to  us by  the caller (via
 *       the `data' argument, and as allocated during previous
 *       attempts)
 *   #3: If any (needed) data is missing, try to allocate that data.
 *       Do  this using non-except GFP_ATOMIC and other non-blocking
 *       operations.
 *   #4: If  data cannot be allocated using non-blocking operations,
 *       release  the lock that is held by `self' and re-attempt the
 *       allocation  with  exception-enabled,  blocking  operations.
 *       Remember the freshly allocated data (so that it may be used
 *       during another attempt) and return `false'
 *   #5: With all required data allocated, and the lock to the
 *       given mem-part still held, satisfy the requested goal
 *       in a non-blocking (and thus: atomic) fashion.
 *   #6: Return true, indicating that the goal has been met.
 *
 * Usage:
 * >> struct mpart_CONDITION_data data;
 * >> mpart_lock_acquire(self);
 * >> if (CONDITION(self))
 * >>     return;
 * >> mpart_setcore_data_init(&data);
 * >> TRY {
 * >>     while (!mpart_CONDITION_or_unlock(self, &data))
 * >>         mpart_lock_acquire(self);
 * >> } EXCEPT {
 * >>     mpart_CONDITION_data_fini(&data);
 * >>     RETHROW();
 * >> }
 * >> // NOTE: Don't call `mpart_CONDITION_data_fini(&data);' here!
 * >> //       s.a.: `undefined(out(data))'
 *
 * As such, all of these functions follow the locking logic:
 *   - return == true:   assume(REQUESTED_CONDITION_MET);
 *                       assume(mpart_lock_acquired(self));
 *                       undefined(out(data));        (If a `data' argument is present)
 *   - return == false:  mpart_lock_release(self);
 *   - EXCEPT:           mpart_lock_release(self);
 ************************************************************************/

/* Ensure that `!mpart_hasblocksstate_init(self)' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_initdone_or_unlock(struct mpart *__restrict self,
                         struct unlockinfo *unlock);

/* Ensure that `self->mp_meta->mpm_dmalocks == 0' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_nodma_or_unlock(struct mpart *__restrict self,
                      struct unlockinfo *unlock);

/* Ensure that `self->mp_meta != NULL' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_hasmeta_or_unlock(struct mpart *__restrict self,
                        struct unlockinfo *unlock);


struct mpart_setcore_data {
	uintptr_t           *scd_bitset;      /* [0..1][owned] Block-status bitset. */
	unsigned int         scd_copy_state;  /* One of `MPART_ST_VOID', `MPART_ST_MEM' or `MPART_ST_MEM_SC' */
	union {
		struct mchunk    scd_copy_mem;    /* [valid_if(scd_copy_state == MPART_ST_MEM)][owned] */
		struct mchunkvec scd_copy_mem_sc; /* [valid_if(scd_copy_state == MPART_ST_MEM_SC)][owned] */
	};
};
#define MPART_SETCORE_DATA_INIT       \
	{                                 \
		__NULLPTR, MPART_ST_VOID, { } \
	}
#define mpart_setcore_data_init(self)          \
	(void)((self)->scd_bitset     = __NULLPTR, \
	       (self)->scd_copy_state = MPART_ST_VOID)

/* Finalize data needed for `mpart_setcore_or_unlock()' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setcore_data_fini)(struct mpart_setcore_data *__restrict self);

/* Ensure that `MPART_ST_INCORE(self->mp_state)' */
FUNDEF WUNUSED NONNULL((1, 3)) __BOOL FCALL
mpart_setcore_or_unlock(struct mpart *__restrict self,
                        struct unlockinfo *unlock,
                        struct mpart_setcore_data *__restrict data);

/* Ensure that all blocks (within the given range of blocks)
 * are either `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG'
 * The caller must ensure that...
 *   - ... the given address range is in-bounds!
 *   - ... MPART_ST_INCORE(self->mp_state)
 * If they don't, then this function will cause an assertion failure! */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_load_or_unlock(struct mpart *__restrict self,
                     struct unlockinfo *unlock,
                     mpart_reladdr_t partrel_offset,
                     size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

struct mpart_unsharecow_data {
	struct mpart_setcore_data ucd_ucmem; /* Data for unshare. */
	struct mpart             *ucd_copy;  /* [0..1] The duplicate of the original mem-part. */
};
#define MPART_UNSHARECOW_DATA_INIT \
	{ MPART_SETCORE_DATA_INIT, __NULLPTR }
#define mpart_unsharecow_data_init(self)                \
	(void)(mpart_setcore_data_init(&(self)->ucd_ucmem), \
	       (self)->ucd_copy = __NULLPTR)
#define mpart_unsharecow_data_fini(self)          \
	(kfree((self)->ucd_copy),                     \
	 mpart_setcore_data_fini(&(self)->ucd_ucmem))

/* Ensure that `LIST_EMPTY(&self->mp_copy)' (while only considering nodes
 * which   may   be   overlapping   with   the   given   address   range)
 * NOTE: The  caller must first ensure that `MPART_ST_INCORE(self->mp_state)',
 *       otherwise this function will result in an internal assertion failure.
 * NOTE: The `LIST_EMPTY(&self->mp_copy)' mustn't be seen ~too~ strictly, as
 *       the list is still allowed to contain dead nodes that are about  to,
 *       or have already been added to the dead nodes list.
 *       However, the mmans of all nodes still apart of the mp_copy list have
 *       already been destroyed, such that  no alive copy-nodes still  exist! */
FUNDEF WUNUSED NONNULL((1, 3)) __BOOL FCALL
mpart_unsharecow_or_unlock(struct mpart *__restrict self,
                           struct unlockinfo *unlock,
                           struct mpart_unsharecow_data *__restrict data,
                           mpart_reladdr_t partrel_offset, size_t num_bytes);


/* Ensure that:
 * >> LIST_FOREACH (node, &self->mp_share, mn_link)
 * >>     mnode_clear_write(node) == MNODE_CLEAR_WRITE_SUCCESS
 * Note that when `!mpart_isanon(self)', any nodes apart of `mp_copy' wouldn't
 * have gotten write-access to begin with (since this requires such a node  to
 * create its own private copy  of `self'), so it  is sufficient to only  deny
 * write access  to MNODE_F_SHARED-nodes  in order  to ensure  that no  memory
 * mappings exist that may still have write-access! */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_denywrite_or_unlock(struct mpart *__restrict self,
                          struct unlockinfo *unlock);
/************************************************************************/


/* Acquire a lock until:
 *  - mpart_initdone_or_unlock(self, ...) */
FUNDEF NONNULL((1)) void FCALL
mpart_lock_acquire_and_initdone(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Acquire a lock until:
 *  - mpart_initdone_or_unlock(self, ...)
 *  - mpart_nodma_or_unlock(self, ...) */
FUNDEF NONNULL((1)) void FCALL
mpart_lock_acquire_and_initdone_nodma(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...) */
FUNDEF NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_load_or_unlock(self, ...)    // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be loaded)
 *
 * HINT: This function is used to implement `mpart_read()' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_lock_acquire_and_setcore_load(struct mpart *__restrict self,
                                    pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_unsharecow_or_unlock(self, ...)  // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be unshared/loaded)
 *
 * HINT: This function is used to implement `mman_startdma()' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_lock_acquire_and_setcore_unsharecow(struct mpart *__restrict self,
                                          pos_t filepos, size_t split_hint)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_load_or_unlock(self, ...)        // Based on the given address range
 *  - mpart_unsharecow_or_unlock(self, ...)  // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be unshared/loaded)
 *
 * HINT: This function is used to implement `mman_startdma()' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_lock_acquire_and_setcore_unsharecow_load(struct mpart *__restrict self,
                                               pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as `mpart_lock_acquire_and_setcore()', but also ensure that no DMA locks
 * are  still being held, and that all shared mappings of the given mem-part are
 * no longer mapped with write permissions:
 * >> LIST_FOREACH (node, &self->mp_share, mn_link) {
 * >>     mnode_clear_write(node);
 * >> }
 * Note that copy-on-write (i.e. `&self->mp_copy')  nodes don't need to be  updated.
 * But also note that copy-on-write mappings usually prevent each other from gaining
 * write access, simply  by co-existing. Furthermore,  copy-on-write mappings  can't
 * gain write-access to underlying mem-parts if  those parts might be accessed  from
 * the outside world (which is the case when `!mpart_isanon(self)').
 *
 * In other words: The only case where there may still be a node associated with
 * `self' that has write-access, applies when:
 *   >> mpart_isanon(self) &&                        // Mem-part is anonymous
 *   >> LIST_EMPTY(&self->mp_share) &&               // No secondary shared mappings
 *   >> !LIST_EMPTY(&self->mp_copy) &&               // There is a copy-on-write mapping
 *   >> (LIST_NEXT(LIST_FIRST(&self->mp_copy), mn_link) == NULL) // There is exactly 1 copy-on-write mapping
 * In this case, the node described by `LIST_FIRST(&self->mp_copy)' may still have
 * write-access,  and continue to  modify the backing memory  of `self' after this
 * function was called.
 *
 * However, the purpose of  this function is to  be used by `mpart_sync()',  where
 * syncing an anonymous file wouldn't really make much sense (where the file being
 * anonymous is one  of the  conditions for  a writable  copy-on-write mapping  to
 * continue to exist) */
FUNDEF NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore_unwrite_nodma(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Get/Set the state of the index'd block `partrel_block_index' from the part's block-state bitset.
 * NOTE: The  caller is responsible  to ensure that mem-part  is in a state
 *       where the bitset is valid (iow: `MPART_ST_HASST(self->mp_state)'),
 *       and that `partrel_block_index' is located in-bounds.
 * NOTE: The caller must be holding a lock to `self', unless the intend is to
 *       change the state of a  block that used to be  `MPART_BLOCK_ST_INIT',
 *       in which case `mpart_setblockstate()' may be called without  holding
 *       a lock to `self'
 *       But also note that after transitioning away from `MPART_BLOCK_ST_INIT',
 *       the caller must  broadcast the  `mf_initdone' signal of  the file  that
 *       was used to initialize the part.
 * NOTE: When  calling  `mpart_setblockstate()'  to  set  `MPART_BLOCK_ST_INIT',
 *       then the caller is also responsible to set the `MPART_F_MAYBE_BLK_INIT'
 *       flag! But  note that  that flag  should  _NOT_ be  cleared by  the  one
 *       who  originally  set  it,  since  other  (unrelated)  blocks  may exist
 *       that still make use of the `MPART_BLOCK_ST_CHNG' state!
 * WARNING: These functions are allowed to assume that `mpart_hasblockstate(self)'.
 *          If this cannot be guarantied,  then these functions mustn't be  called!
 * @param: at:  One of `MPART_BLOCK_ST_*'
 * @return: * : *ditto* */
FUNDEF NOBLOCK ATTR_PURE NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_getblockstate)(struct mpart const *__restrict self,
                                   size_t partrel_block_index);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setblockstate)(struct mpart *__restrict self,
                                   size_t partrel_block_index,
                                   unsigned int st);
#define mpart_hasblockstate(self) \
	((self)->mp_blkst_ptr != __NULLPTR || ((self)->mp_flags & MPART_F_BLKST_INL))

/* Check if the given mem-part contains blocks with `MPART_BLOCK_ST_INIT'.
 * For this purpose, if the `MPART_F_MAYBE_BLK_INIT' flag isn't set,  then
 * this function immediately returns `false'.
 * Otherwise, all blocks of the part are searched, and if one is found that
 * uses the `MPART_BLOCK_ST_INIT'  state, return  `true'. Otherwise,  clear
 * the `MPART_F_MAYBE_BLK_INIT' flag and return `false'.
 * NOTE: The caller must be holding a lock to `self' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL mpart_hasblocksstate_init)(struct mpart *__restrict self);


struct mpart_physloc {
	physaddr_t mppl_addr; /* Starting physical memory address. */
	size_t     mppl_size; /* Total size (in bytes) */
};

/* Load the bounds of the longest consecutive physical memory address range
 * that starts at `partrel_offset', has been populated with meaningful data
 * and   contains  at  least  1  byte  (and  at  most  `num_bytes'  bytes).
 * Note  that   `result->mppl_size < num_bytes'   for   multiple   reasons:
 *   - The end of the given mem-part `self' is reached
 *   - Backing physical memory of `self' is scattered, and the next
 *     byte is apart of the  next (discontinuous) chunk of  memory.
 *   - The next block located at the end of the returned range isn't
 *     already loaded in-core. (that is:  doesn't have a state  that
 *     was set to `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG')
 *
 * NOTE: The caller must be holding a lock to `self'
 * NOTE: The caller is responsible to ensure that `MPART_ST_INMEM(self->mp_state)'
 *       before calling this function.
 * NOTE: If necessary, the  length of  the returned  range may  be truncated  in
 *       order to accommodate the requirements on the state of contained blocks.
 *
 * @return: true:  Success
 * @return: false: Error: At least  one accessed  block  has a  state  that
 *                        is `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL mpart_memaddr_for_read)(struct mpart *__restrict self,
                                      mpart_reladdr_t partrel_offset, size_t num_bytes,
                                      struct mpart_physloc *__restrict result);

/* Same as `mpart_memaddr()', but have a looser requirement in regards to
 * the current state of blocks that are entirely contained within the to-
 * be returned address range.
 *
 * While  `mpart_memaddr_for_read()' requires that  all blocks that overlap
 * with the returned range have a state of are either `MPART_BLOCK_ST_LOAD'
 * or `MPART_BLOCK_ST_CHNG', this function only  requires this for the  0-2
 * blocks that only partially overlap with the returned range.
 *
 * All of the blocks that fully overlap with the returned range are only
 * required  to  not   have  a  state   set  to   `MPART_BLOCK_ST_INIT'.
 *
 * @return: true:  Success
 * @return: false: Error: At least  one fully  accessed  block has  a  state
 *                        that  is  `MPART_BLOCK_ST_INIT', or  at  least one
 *                        of the 0-2 border blocks  has a state that is  one
 *                        of `MPART_BLOCK_ST_INIT', or `MPART_BLOCK_ST_NDEF' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL mpart_memaddr_for_write)(struct mpart *__restrict self,
                                       mpart_reladdr_t partrel_offset, size_t num_bytes,
                                       struct mpart_physloc *__restrict result);

/* Commit modifications made to the given backing address range.
 * For this purpose, this function:
 *   - Set the state of all blocks that fully overlap with the given
 *     address range  to  `MPART_BLOCK_ST_CHNG',  (after  internally
 *     asserting  that their old state wasn't `MPART_BLOCK_ST_INIT')
 *   - Of the 0-2 blocks that only overlap partially with the given
 *     address  range,  make   the  following  state   transitions:
 *      - MPART_BLOCK_ST_LOAD -> MPART_BLOCK_ST_CHNG
 *      - MPART_BLOCK_ST_CHNG -> MPART_BLOCK_ST_CHNG  (i.e. no-op)
 *      - MPART_BLOCK_ST_INIT: Internal assertion failure
 *      - MPART_BLOCK_ST_NDEF:
 *        - If the partially overlapped block isn't the last (iow: right-most)
 *          block (meaning  that the  given address  range partially  overlaps
 *          with its beginning), then an internal assertion fails.
 *        - If the partially overlapped block _is_ the last block,  then
 *          it's state also remains unaltered, and this function returns
 *          the offset from `partrel_offset' to that block's start.
 *
 * If this function manages change any at least 1 block to `MPART_BLOCK_ST_CHNG'
 * when that block  wasn't already marked  as such, and  if the associated  file
 * implements the `mo_saveblocks' operator,  then set the MPART_F_CHANGED  flag.
 * If  that flag wasn't  set before, then add  a new reference  to `self' to the
 * list of changed parts of the associated file.
 *
 * @return: * : The   #   of  successfully   committed  bytes.
 *              Usually the same as `num_bytes', but see above */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL mpart_memaddr_for_write_commit)(struct mpart *__restrict self,
                                              mpart_reladdr_t partrel_offset,
                                              size_t num_bytes);

/* Whilst inheriting a lock to `self' from the caller (which is _always_
 * released before this function returns), make sure that the first byte
 * pointed to `partrel_offset' has been loaded for reading (that is: the
 * the containing block has transitioned to one of `MPART_BLOCK_ST_LOAD'
 * or `MPART_BLOCK_ST_CHNG')
 * The given `loc->mppl_size' is a hint as to how many consecutive blocks
 * this function should attempt to load, though it will only ever load  a
 * single cluster of consecutive blocks that starts with an uninitialized
 * block containing `partrel_offset' */
FUNDEF NONNULL((1, 3)) void FCALL
mpart_memload_and_unlock(struct mpart *__restrict self,
                         mpart_reladdr_t partrel_offset,
                         struct mpart_physloc const *__restrict loc,
                         struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, ...);

/* Directly return physical backing  memory containing the byte  `partrel_offset',
 * without looking at the associated block-state at all. The caller is responsible
 * to ensure that `MPART_ST_INMEM(self->mp_state)' before calling this function.
 * NOTE: The caller must be holding a lock to `self' (which is allowed to be a DMA lock)
 * NOTE: This function may also assume that at least the first byte (that
 *       is: the byte described by `partrel_offset') is in-bounds of the
 *       given mem-part `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_memaddr_direct)(struct mpart *__restrict self,
                                    mpart_reladdr_t partrel_offset,
                                    struct mpart_physloc *__restrict result);

/* Mark all blocks that overlap with the given address range as CHNG.
 * For this purpose, the caller must ensure that:
 * >> !OVERFLOW_UADD(partrel_offset, num_bytes, &endaddr) && endaddr <= mpart_getsize(self)
 * If  any  of  the  blocks  within  the  given  range  had  yet  to  be  marked  as  CHNG,
 * and  the  associated  file  is   not  anonymous,  and  implements  the   `mo_saveblocks'
 * operator, and  the  `MPART_F_CHANGED'  flag had  yet  to  be set  for  the  given  part,
 * then  set  the  `MPART_F_CHANGED'   flag  and  add  `self'   to  the  list  of   changed
 * parts of its associated file.
 * NOTE: The caller must be holding a lock to `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_changed)(struct mpart *__restrict self,
                             mpart_reladdr_t partrel_offset,
                             size_t num_bytes);




/* Split  the given mem-part  `self' (which should be  a member of `file')
 * after `offset' bytes from the start of backing file. For this  purpose,
 * the given `offset' should be `> mpart_getminaddr(self)', and both page-
 * and block-aligned.
 * @return: NULL: The  given `offset' is  greater than the  size of the part
 *                at the time the request was made. The caller should handle
 *                this case by re-checking for a missing part, and  creating
 *                that part if it cannot be found.
 * @return: * :   A reference to a part that begins at `self->mp_minaddr + offset' */
FUNDEF NONNULL((1)) REF struct mpart *FCALL
mpart_split(struct mpart *__restrict self,
            PAGEDIR_PAGEALIGNED pos_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Sync changes made to the given mem-part.
 * @return: * : The total # of bytes that were synced.
 * NOTE: The caller is responsible for adding/removing the part to/from
 *       the associated file's list of changed parts! */
FUNDEF NOBLOCK NONNULL((1)) size_t FCALL
mpart_sync(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as `mpart_sync()', but keep on holding onto the lock to `self' */
FUNDEF NOBLOCK NONNULL((1)) size_t FCALL
mpart_lock_acquire_and_setcore_unwrite_sync(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* (Re-)map the given mem-part into a page directory.
 * The caller must ensure:
 *   - mpart_lock_acquired(self)               (unless `self' was accessed from a hinted node,
 *                                              or the caller knows that `self' can't be accessed
 *                                              from the outside world)
 *   - pagedir_prepare_p(self, addr, size)     (was called)
 *
 * NOTES:
 *   - When  mapping  blocks not  marked  as `MPART_BLOCK_ST_CHNG',
 *     the `PAGEDIR_MAP_FWRITE' perm-flag is automatically cleared.
 *   - When mapping blocks marked as `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT',
 *     the `PAGEDIR_MAP_FEXEC', `PAGEDIR_MAP_FREAD'  and `PAGEDIR_MAP_FWRITE'  perm-
 *     flags are automatically cleared.
 *
 * @return: * : The union of permissions actually applied to all  pages.
 *              This may be used to figure out if write permissions were
 *              actually given to any of the requested pages. */
FUNDEF NOBLOCK NONNULL((1)) u16
NOTHROW(FCALL mpart_mmap_p)(struct mpart *__restrict self, pagedir_phys_t pdir,
                            PAGEDIR_PAGEALIGNED void *addr,
                            PAGEDIR_PAGEALIGNED size_t size,
                            PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                            u16 perm);

/* Same as `mpart_mmap_p()', but always map into the current page directory. */
FUNDEF NOBLOCK NONNULL((1)) u16
NOTHROW(FCALL mpart_mmap)(struct mpart *__restrict self,
                          PAGEDIR_PAGEALIGNED void *addr,
                          PAGEDIR_PAGEALIGNED size_t size,
                          PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                          u16 perm);

/* Similar to `mpart_mmap_p()', but force the given `perm' for all pages, no
 * matter  what the block-status  bitset of `self' might  say of the matter. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap_force_p)(struct mpart *__restrict self, pagedir_phys_t pdir,
                                  PAGEDIR_PAGEALIGNED void *addr,
                                  PAGEDIR_PAGEALIGNED size_t size,
                                  PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                  u16 perm);

/* Same as `mpart_mmap_force_p()', but always map into the current page directory. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap_force)(struct mpart *__restrict self,
                                PAGEDIR_PAGEALIGNED void *addr,
                                PAGEDIR_PAGEALIGNED size_t size,
                                PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                u16 perm);

/* For use with `MNODE_F_MHINT':
 *  - Ensure that the pages (== block) at the given `offset'
 *    has been marked as `MPART_BLOCK_ST_CHNG', invoking the
 *    block loader from the associated file if necessary.
 *  - Afterwards, map the associated page to `addr' within
 *    the   current   page   directory,   using    `perm'.
 * This function is used to implement handling of hinted
 * mem-nodes   when  encountered  by  the  #PF  handler. */
FUNDEF NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_hinted_mmap)(struct mpart *__restrict self,
                                 PAGEDIR_PAGEALIGNED void *addr,
                                 PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                 u16 perm);

/* Convenience wrapper for `mpart_hinted_mmap()' */
FUNDEF NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_hinted_mmap)(struct mnode *__restrict self,
                                 PAGEDIR_PAGEALIGNED void *fault_page);



/* TODO: =============== BEGIN_DEPRECATED ===============
 *
 * Mem-part read/write  functions  don't  include  file-size/read-only/etc.  checks.
 * Instead, all code  should make  use of `mfile_read'  and `mfile_write'  (etc...).
 * But  note that these functions should only  be removed from the public interface,
 * as they're actually used in the implementation of `mfile_read' and `mfile_write'! */

/* Read/write raw data to/from a given mem-part.
 * @return: * : The # of bytes that were transfered. May be less than `num_bytes' if the part
 *              is too small, or if  the given `filepos' lies  outside of the part's  bounds. */
FUNDEF NONNULL((1)) size_t KCALL mpart_read(struct mpart *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL mpart_write(struct mpart *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL mpart_read_p(struct mpart *__restrict self, physaddr_t dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) size_t KCALL mpart_write_p(struct mpart *__restrict self, physaddr_t src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_readv(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_writev(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_readv_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_writev_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as the above, but these use an intermediate (stack) buffer for  transfer.
 * As such, these functions are called by the above when `memcpy_nopf()' produces
 * transfer errors that cannot be resolved by `mman_prefault()' */
FUNDEF NONNULL((1)) size_t KCALL _mpart_buffered_read(struct mpart *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL _mpart_buffered_write(struct mpart *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL _mpart_buffered_readv(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL _mpart_buffered_writev(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);


/* Perform I/O while holding  a lock to `self'.  If this isn't possible,  then
 * unlock all locks,  try to  work towards  that goal,  and return  `0'. If  a
 * virtual buffer is given,  and that buffer cannot  be faulted (e.g.: it  may
 * be backed by VIO, or may even be faulty), return `(size_t)-1', after having
 * released all locks, which is  indicative that the caller should  re-attempt
 * the operation with buffered I/O.
 * Locking logic:
 *    IN:                   mpart_lock_acquired(self);
 *    EXCEPT:               mpart_lock_release(self); unlock();
 *    return == 0:          mpart_lock_release(self); unlock();
 *    return == (size_t)-1: mpart_lock_release(self); unlock();  (never returned by *_p variants)
 *    return == *:          mpart_lock_acquired(self);
 * Upon success, return the (non-zero) # of transfered bytes.
 * The caller must ensure that:
 *    >> num_bytes != 0
 *    >> MPART_ST_INCORE(self->mp_state)   // Can be ensured by `mpart_setcore_or_unlock()'
 *    >> mpart_unsharecow_or_unlock(...)   // Only for `mpart_write*', and only within the target address range
 */
FUNDEF NONNULL((1)) size_t KCALL mpart_read_or_unlock(struct mpart *__restrict self, USER CHECKED void *dst, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL mpart_write_or_unlock(struct mpart *__restrict self, USER CHECKED void const *src, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL mpart_read_or_unlock_p(struct mpart *__restrict self, physaddr_t dst, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) size_t KCALL mpart_write_or_unlock_p(struct mpart *__restrict self, physaddr_t src, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_readv_or_unlock(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_writev_or_unlock(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_readv_or_unlock_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL mpart_writev_or_unlock_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
/* TODO: =============== END_DEPRECATED =============== */



/* Lock for `mpart_all_list' */
DATDEF struct atomic_lock mpart_all_lock;
#define mpart_all_lock_tryacquire() atomic_lock_tryacquire(&mpart_all_lock)
#define mpart_all_lock_acquire()    atomic_lock_acquire(&mpart_all_lock)
#define mpart_all_lock_acquire_nx() atomic_lock_acquire_nx(&mpart_all_lock)
#define mpart_all_lock_release()    (atomic_lock_release(&mpart_all_lock), mpart_all_reap())
#define mpart_all_lock_acquired()   atomic_lock_acquired(&mpart_all_lock)
#define mpart_all_lock_available()  atomic_lock_available(&mpart_all_lock)

/* [0..n][CHAIN(mp_allparts)][lock(mpart_all_lock)]
 * List of all memory parts currently in use. List head indices are `MPART_ALL_LIST_*'
 * NOTE: This list holds a reference to every contain part that wasn't already
 *       destroyed,    and    has   the    `MPART_F_GLOBAL_REF'    flag   set. */
DATDEF struct mpart_list mpart_all_list;

/* TODO: Instead of having a dead- and pending- list, use a single, common lockop list! */

/* [0..n][CHAIN(_mp_dead)][lock(ATOMIC)]
 * List of dead parts that have yet to be removed from `mpart_all_list'.
 * This list must be cleared whenever the caller has released a lock to `mpart_all_lock'.
 * For this purpose, you may simply use `mpart_all_reap()' */
DATDEF struct mpart_slist mpart_all_dead;

/* [0..n][CHAIN(_mp_newglobl)][lock(ATOMIC)]
 * Similar  to `mpart_all_dead', but  this is a list  of references to parts
 * that should be added to `mpart_all_list' once the lock becomes available.
 *
 * Because  these  are references,  mpart_destroy() remains  NOBLOCK, because
 * by  the time a mem-part is destroyed, it  is know that it can't be pending
 * to-be added to the global list of parts anymore. (because it being pending
 * would have otherwise prevented it from being destroyed) */
DATDEF struct REF mpart_slist mpart_all_pending;

/* Add the given mpart `self' to the global list of parts.
 * This  function   will  initialize   `self->mp_allparts' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_all_list_insert)(struct mpart *__restrict self);

/* Try to reap all dead memory-parts from `mpart_all_dead'.
 * This function must be called after releasing a lock from `mpart_all_lock' */
FUNDEF NOBLOCK void NOTHROW(FCALL _mpart_all_reap)(void);
#define mpart_all_mustreap()                                                          \
	(__hybrid_atomic_load(mpart_all_dead.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR || \
	 __hybrid_atomic_load(mpart_all_pending.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mpart_all_reap() _mpart_all_reap()
#else /* __OPTIMIZE_SIZE__ */
#define mpart_all_reap() (void)(!mpart_all_mustreap() || (_mpart_all_reap(), 0))
#endif /* !__OPTIMIZE_SIZE__ */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MPART_H */
