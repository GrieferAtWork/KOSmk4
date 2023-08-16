/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/__minmax.h>
#include <hybrid/sched/__yield.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/lockop.h>

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
#define MPART_F_GLOBAL_REF     0x0004 /* [lock(CLEAR(ATOMIC), SET(<WAS_SET_PREVIOUSLY> && MPART_F_LOCKBIT &&
                                       *                          !mpart_isanon(self) && mpart_all_acquired()))]
                                       * -> `mpart_all_list' holds a reference to this part.
                                       * When memory is running low, and the kernel tries to unload  unused
                                       * memory  parts, it  will clear this  flag for all  parts there are.
                                       * Also note that this flag is cleared by default when the associated
                                       * file's `mf_parts' field was/is set to `MFILE_PARTS_ANONYMOUS' */
/*efine MPART_F_               0x0008  * ... */
#define MPART_F_BLKST_INL      0x0010 /* [lock(MPART_F_LOCKBIT)] The backing block-state bitset exists in-line. */
#define MPART_F_NOFREE         0x0020 /* [const] Don't page_free() backing physical memory or swap. */
/*efine MPART_F_               0x0040  * ... */
/*efine MPART_F_               0x0080  * ... */
#define MPART_F_COREPART       0x0100 /* [const] Core part (free this part using `mcoreheap_free()' instead of `kfree()') */
#define MPART_F_CHANGED        0x0200 /* [lock(SET(MPART_F_LOCKBIT),
                                       *       CLEAR((MPART_F_LOCKBIT && mp_meta->mpm_dmalocks == 0) ||
                                       *             (mp_file->mf_changed == MFILE_PARTS_ANONYMOUS)))]
                                       * [valid_if(mp_file->mf_changed != MFILE_PARTS_ANONYMOUS)]
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

/* Possible values for `struct mpart::mp_xflags' */
#define MPART_XF_NORMAL           0x00
#define MPART_XF_MERGE_AFTER_DMA  0x01 /* [lock(ATOMIC)] Internally used: If set, DMA completion must clear
                                        * this flag and  call `mpart_merge()' (s.a.  `mpart_dma_dellock()') */
#define MPART_XF_TRIM_AFTER_DMA   0x02 /* [lock(ATOMIC)] Internally used: If set, DMA completion must clear
                                        * this flag  and call  `mpart_trim()' (s.a.  `mpart_dma_dellock()') */
#define MPART_XF_MERGE_AFTER_INIT 0x04 /* [lock(ATOMIC)] Internally used: If set, changing a block status from `MPART_BLOCK_ST_INIT' must call `mpart_trim()' */
#define MPART_XF_TRIM_AFTER_INIT  0x08 /* [lock(ATOMIC)] Internally used: If set, changing a block status from `MPART_BLOCK_ST_INIT' must call `mpart_merge()' */
/*efine MPART_XF_                 0x10  * ... */
#define MPART_XF_WILLMERGE        0x20 /* [lock(SET(ATOMIC), CLEAR(PART_WORKER))] Async worker must merge this part. */
#define MPART_XF_WILLTRIM         0x40 /* [lock(SET(ATOMIC), CLEAR(PART_WORKER))] Async worker must trim this part. */
#define MPART_XF_INJOBLIST        0x80 /* [lock(SET(ATOMIC), CLEAR(PART_WORKER))] Mem-part was added to the
                                        * async job list. This flag is cleared by an async worker that will
                                        * perform tasks indicated by `MPART_XF_WILL*' flags.
                                        * This flag can only be cleared by the async-job-worker for mem-parts,
                                        * and only after it has  been confirmed that none of  `MPART_XF_WILL*'
                                        * are still set. */



/* Possible values for `struct mpart::mp_state' */
#define MPART_ST_VOID       0x0 /* [lock(MPART_F_LOCKBIT)] Part hasn't been accessed, yet. */
#define MPART_ST_SWP        0x1 /* [lock(MPART_F_LOCKBIT)] Part has been off-loaded into swap. */
#define MPART_ST_MEM        0x2 /* [lock(MPART_F_LOCKBIT)] Part has been allocated. */
#ifdef LIBVIO_CONFIG_ENABLED
#define MPART_ST_VIO        0x3 /* [const] Part is backed by VIO. */
#endif /* LIBVIO_CONFIG_ENABLED */
#define MPART_ST_SWP_SC     0x5 /* [lock(MPART_F_LOCKBIT)] Part has been off-loaded into swap (scattered). */
#define MPART_ST_MEM_SC     0x6 /* [lock(MPART_F_LOCKBIT)] Part has been allocated (scattered). */
#define MPART_ST_INCORE(x)  ((x) >= MPART_ST_MEM && (x) != MPART_ST_SWP_SC)
#define MPART_ST_INMEM(x)   ((x) == MPART_ST_MEM || (x) == MPART_ST_MEM_SC)
#define MPART_ST_SCATTER(x) ((x) & 4)  /* Check if a scatter-list is being used. */
#define MPART_ST_WTSC(x)    ((x) | 4)  /* Return the scatter-variant of the given state. */
#define MPART_ST_NOSC(x)    ((x) & ~4) /* Return the non-scatter-variant of the given state. */


/* `struct mpart' offsets */
#define OFFSET_MCHUNK_START        0
#define OFFSET_MCHUNK_SIZE         __SIZEOF_PHYSPAGE_T__
#define SIZEOF_MCHUNK              (__SIZEOF_PHYSPAGE_T__ * 2)
#define ALIGNOF_MCHUNK             __ALIGNOF_PHYSPAGE_T__
#define OFFSET_MCHUNKVEC_V         0
#define OFFSET_MCHUNKVEC_C         __SIZEOF_POINTER__
#define SIZEOF_MCHUNKVEC           (__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__)
#define ALIGNOF_MCHUNKVEC          __ALIGNOF_POINTER__
#define OFFSET_MPART_REFCNT        0
#define OFFSET_MPART_FLAGS         __SIZEOF_POINTER__
#define OFFSET_MPART_XFLAGS        (__SIZEOF_POINTER__ + (__SIZEOF_POINTER__ / 2))
#define OFFSET_MPART_STATE         (__SIZEOF_POINTER__ + (__SIZEOF_POINTER__ / 2) + (__SIZEOF_POINTER__ / 4))
#define OFFSET_MPART__JOBLINK      (__SIZEOF_POINTER__ * 2)
#define OFFSET_MPART__JOBLINK_NEXT (__SIZEOF_POINTER__ * 2)
#define OFFSET_MPART_FILE          (__SIZEOF_POINTER__ * 3)
#define OFFSET_MPART_COPY          (__SIZEOF_POINTER__ * 4)
#define OFFSET_MPART_COPY_FIRST    (__SIZEOF_POINTER__ * 4)
#define OFFSET_MPART_SHARE         (__SIZEOF_POINTER__ * 5)
#define OFFSET_MPART_SHARE_FIRST   (__SIZEOF_POINTER__ * 5)
#ifdef __WANT_MPART__mp_nodlsts
#define OFFSET_MPART__NODLSTS (__SIZEOF_POINTER__ * 4)
#endif /* __WANT_MPART__mp_nodlsts */
#ifdef __WANT_MPART__mp_dtplop
#define OFFSET_MPART__DTPLOP (__SIZEOF_POINTER__ * 4)
#endif /* __WANT_MPART__mp_dtplop */
#ifdef __WANT_MPART__mp_anXplop
#define OFFSET_MPART__ANFPLOP (__SIZEOF_POINTER__ * 4)
#define OFFSET_MPART__ANPPLOP (__SIZEOF_POINTER__ * 4)
#endif /* __WANT_MPART__mp_anXplop */
#define OFFSET_MPART_LOCKOPS       (__SIZEOF_POINTER__ * 6)
#define OFFSET_MPART_ALLPARTS      (__SIZEOF_POINTER__ * 7)
#define OFFSET_MPART_ALLPARTS_NEXT (__SIZEOF_POINTER__ * 7)
#define OFFSET_MPART_ALLPARTS_PREV (__SIZEOF_POINTER__ * 8)
#ifdef __WANT_MPART__mp_lopall
#define OFFSET_MPART__LOPALL  (__SIZEOF_POINTER__ * 7)
#define OFFSET_MPART__PLOPALL (__SIZEOF_POINTER__ * 7)
#endif /* __WANT_MPART__mp_lopall */
#define OFFSET_MPART_CHANGED      (__SIZEOF_POINTER__ * 9)
#define OFFSET_MPART_CHANGED_NEXT (__SIZEOF_POINTER__ * 9)
#ifdef __WANT_MPART__mp_dead
#define OFFSET_MPART__DEAD      (__SIZEOF_POINTER__ * 9)
#define OFFSET_MPART__DEAD_NEXT (__SIZEOF_POINTER__ * 9)
#endif /* __WANT_MPART__mp_dead */
#define OFFSET_MPART_MINADDR    (__SIZEOF_POINTER__ * 10)
#define OFFSET_MPART_MAXADDR    (__SIZEOF_POINTER__ * 10 + 8)
#define OFFSET_MPART_FILENT     (__SIZEOF_POINTER__ * 10 + 16)
#define OFFSET_MPART_FILENT_PAR (__SIZEOF_POINTER__ * 10 + 16)
#define OFFSET_MPART_FILENT_LHS (__SIZEOF_POINTER__ * 11 + 16)
#define OFFSET_MPART_FILENT_RHS (__SIZEOF_POINTER__ * 12 + 16)
#ifdef __WANT_MPART__mp_trmlop
#define OFFSET_MPART___TRMLOP_PAD (__SIZEOF_POINTER__ * 10 + 16)
#define OFFSET_MPART__TRMLOP_MM   (__SIZEOF_POINTER__ * 11 + 16)
#define OFFSET_MPART__TRMPLOP_MM  (__SIZEOF_POINTER__ * 11 + 16)
#define OFFSET_MPART__TRMLOP_MP   (__SIZEOF_POINTER__ * 11 + 16)
#define OFFSET_MPART__TRMPLOP_MP  (__SIZEOF_POINTER__ * 11 + 16)
#endif /* __WANT_MPART__mp_trmlop */
#define OFFSET_MPART_BLKST_PTR (__SIZEOF_POINTER__ * 13 + 16)
#define OFFSET_MPART_BLKST_INL (__SIZEOF_POINTER__ * 13 + 16)
#define OFFSET_MPART_MEM       (__SIZEOF_POINTER__ * 14 + 16)
#define OFFSET_MPART_MEM       (__SIZEOF_POINTER__ * 14 + 16)
#define OFFSET_MPART_MEM_SC    (__SIZEOF_POINTER__ * 14 + 16)
#define OFFSET_MPART_SWP       (__SIZEOF_POINTER__ * 14 + 16)
#define OFFSET_MPART_SWP_SC    (__SIZEOF_POINTER__ * 14 + 16)
#define OFFSET_MPART_META      (__SIZEOF_POINTER__ * 14 + 16 + SIZEOF_MCHUNK)
#if __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__
#define OFFSET_MPART___PAD (__SIZEOF_POINTER__ * 15 + 16 + SIZEOF_MCHUNK)
#define SIZEOF_MPART       (OFFSET_MPART___PAD + (__ALIGNOF_POS_T__ - __ALIGNOF_POINTER__))
#else /* __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__ */
#define SIZEOF_MPART (__SIZEOF_POINTER__ * 15 + 16 + SIZEOF_MCHUNK)
#endif /* __ALIGNOF_POS_T__ <= __ALIGNOF_POINTER__ */
#define ALIGNOF_MPART __ALIGNOF_POS_T__



#ifdef __CC__
DECL_BEGIN

struct mpart;     /* Memory file part. */
struct mpartmeta; /* Memory file part meta-data. */
struct mfile;     /* Memory storage owner/descriptor. */
struct mnode;     /* Memory range descriptor. */
struct iov_buffer;
struct iov_physbuffer;

#ifndef __pagedir_prot_t_defined
#define __pagedir_prot_t_defined
typedef u16 pagedir_prot_t;
#endif /* !__pagedir_prot_t_defined */

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
#if __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__
#define __SIZEOF_MPART 88
#else /* __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__ */
#define __SIZEOF_MPART 84
#endif /* __ALIGNOF_POS_T__ <= __ALIGNOF_POINTER__ */
#elif __SIZEOF_POINTER__ == 8
#define __SIZEOF_MPART 152
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
//	MPART_INIT_mp_changed({}),
//	MPART_INIT_mp_minaddr(0),
//	MPART_INIT_mp_maxaddr(FILLME - 1),
//	MPART_INIT_mp_filent({}),
//	MPART_INIT_mp_blkst_ptr(NULL),
//	MPART_INIT_mp_mem(FILLME, CEILDIV(FILLME, PAGESIZE)),
//	MPART_INIT_mp_meta(NULL)
#endif

/*
 * === Addressing in swap data ===
 *
 * Unlike memory MPART_ST_MEM-like memory,  MPART_ST_SWP-like
 * memory isn't necessarily continuous. - Instead, only pages
 * containing at least 1 byte that's been modified are really
 * present in swap (as determined by the status of the blocks
 * associated with those pages).
 *
 * As such, the address of the swap-page belonging to a given
 * part-relative address is calculated as:
 *
 *    in: mpart_reladdr_t reladdr;
 *    >> PARTREL_PAGEADDR = reladdr / PAGESIZE;
 *    >> SWAP_PAGE_OFFSET = 0;
 *    >> for (i = 0; i < PARTREL_PAGEADDR; ++i) {
 *    >>     if (PARTREL_PAGE_CONTAINS_MODIFIED_BLOCKS(i))
 *    >>         ++SWAP_PAGE_OFFSET;
 *    >> }
 *    >> if (mp_state == MPART_ST_SWP)
 *    >>     return mp_swp.mc_start + SWAP_PAGE_OFFSET;
 *    >> if (mp_state == MPART_ST_SWP_SC)
 *    >>     return ...; // Like `MPART_ST_SWP'
 *    This transformation from a page-index into an offset into
 *    the (possibly non-continuous) swap vector of the part can
 *    be done with `mpart_page2swap()'.
 *
 *
 * FIXME: The currently implementation of `mpart_split()',  and
 *        `mpart_setcore_or_unlock()' don't do the whole  align
 *        to whole pages  thing, but rather:  assume that  swap
 *        space is a tightly packed sequence of modified bytes,
 *        rather than pages containing modified bytes!
 */




struct mpart {
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_refcnt(mp_refcnt) mp_refcnt
#define MPART_INIT_mp_flags(mp_flags)   mp_flags, 0
#define MPART_INIT_mp_state(mp_state)   mp_state, __NULLPTR
#define MPART_INIT_mp_file(mp_file)     mp_file
#endif /* __WANT_MPART_INIT */
	WEAK refcnt_t                 mp_refcnt;    /* Reference counter. */
	uintptr_half_t                mp_flags;     /* Memory part flags (set of `MPART_F_*') */
	uintptr_quarter_t             mp_xflags;    /* Extended  memory part flags (set of `MPART_XF_*')
	                                             * These  are used internally, and this field should
	                                             * _always_ be set to `MPART_XF_NORMAL' during init. */
	uintptr_quarter_t             mp_state;     /* [lock(MPART_F_LOCKBIT)]
	                                             * [const_if(EXISTS(MPART_BLOCK_ST_INIT) ||
	                                             *           mp_meta->mpm_dmalocks != 0)]
	                                             * Memory part state (one of `MPART_ST_*') */
	SLIST_ENTRY(REF mpart)       _mp_joblink;   /* [lock(ATOMIC)][valid_if(MPART_XF_INJOBLIST)]
	                                             * Link entry in the fallback list of mem-parts with  jobs
	                                             * that require steps which unconditionally block or can't
	                                             * be performed immediately due to lack of system  memory.
	                                             * s.a. `MPART_XF_WILL*' */
	REF struct mfile             *mp_file;      /* [1..1][lock(MPART_F_LOCKBIT)][const_if(EXISTS(MPART_BLOCK_ST_INIT))]
	                                             * The associated file. (Cannot be altered as long as any `MPART_BLOCK_ST_INIT' blocks exist) */
	/* WARNING: The  following  2 lists  may contain  already-destroyed nodes.
	 *          To check if a  node has been destroyed,  you may check if  the
	 *          pointed-to  `mn_mman' was destroyed, since that field normally
	 *          only contains a weak reference, meaning that if the underlying
	 *          MMAN  got destroyed, then it will have attempted to unbind all
	 *          of its remaining nodes, and those that it couldn't unbind will
	 *          have been set-up as lockops in `mp_lockops'. */
#ifdef __WANT_MPART_INIT
#if defined(__WANT_MPART__mp_nodlsts) || defined(__WANT_MPART__mp_dtplop) || defined(__WANT_MPART__mp_anXplop)
#define MPART_INIT_mp_copy(...)    {{ __VA_ARGS__
#define MPART_INIT_mp_share(...)   __VA_ARGS__ }}
#else /* __WANT_MPART__mp_nodlsts || __WANT_MPART__mp_dtplop || __WANT_MPART__mp_anXplop */
#define MPART_INIT_mp_copy(...)    __VA_ARGS__
#define MPART_INIT_mp_share(...)   __VA_ARGS__
#endif /* !__WANT_MPART__mp_nodlsts && !__WANT_MPART__mp_dtplop && !__WANT_MPART__mp_anXplop */
#define MPART_INIT_mp_lockops(...) __VA_ARGS__
#endif /* __WANT_MPART_INIT */
#if defined(__WANT_MPART__mp_nodlsts) || defined(__WANT_MPART__mp_dtplop) || defined(__WANT_MPART__mp_anXplop)
	union {
		struct {
			struct mnode_list     mp_copy;      /* [0..n][lock(MPART_F_LOCKBIT)] List of copy-on-write mappings. */
			struct mnode_list     mp_share;     /* [0..n][lock(MPART_F_LOCKBIT)] List of shared mappings. */
		};
#ifdef __WANT_MPART__mp_nodlsts
		struct mnode_list        _mp_nodlsts[2]; /* Node lists. */
#endif /* __WANT_MPART__mp_nodlsts */
#ifdef __WANT_MPART__mp_dtplop
		struct postlockop        _mp_dtplop;     /* Used internally */
#endif /* __WANT_MPART__mp_dtplop */
#ifdef __WANT_MPART__mp_anXplop
		Tobpostlockop(mfile)     _mp_anfplop;
		Tobpostlockop(mpart)     _mp_anpplop;
#endif /* __WANT_MPART__mp_anXplop */
	};
#else /* __WANT_MPART__mp_nodlsts || __WANT_MPART__mp_dtplop || __WANT_MPART__mp_anXplop */
	struct mnode_list             mp_copy;      /* [0..n][lock(MPART_F_LOCKBIT)] List of copy-on-write mappings. */
	struct mnode_list             mp_share;     /* [0..n][lock(MPART_F_LOCKBIT)] List of shared mappings. */
#endif /* !__WANT_MPART__mp_nodlsts && !__WANT_MPART__mp_dtplop && !__WANT_MPART__mp_anXplop */
	Toblockop_slist(mpart)        mp_lockops;   /* [0..n][lock(ATOMIC)] List of lock operations. (s.a. `mpart_lockops_reap()') */
#ifdef __WANT_MPART__mp_lopall
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_allparts(mp_allparts) { mp_allparts }
#endif /* __WANT_MPART_INIT */
	union {
		LIST_ENTRY(mpart)         mp_allparts;  /* [lock(:mpart_all_lock)]
		                                         * Chain of all mem-parts in existence. (may be unbound for certain parts) */
		struct lockop            _mp_lopall;    /* Lock-op used for async insertion of the part into the all-parts list. */
		struct postlockop        _mp_plopall;   /* *ditto* */
	};
#else /* __WANT_MPART__mp_lopall */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_allparts(mp_allparts) mp_allparts
#endif /* __WANT_MPART_INIT */
	LIST_ENTRY(mpart)             mp_allparts;  /* [0..1][lock(:mpart_all_lock)]
	                                             * Chain of all mem-parts in existence. (may be unbound for certain parts) */
#endif /* !__WANT_MPART__mp_lopall */
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
		pos_t                     mp_maxaddr;   /* [lock(LIKE(mp_minaddr))][const_if(like(mp_minaddr))]
		                                         * In-file max address of this  part. (NOTE: when 1  is
		                                         * added, also aligned like `mp_minaddr' must be)
		                                         * NOTE: May be set to `mp_minaddr - 1' if the part is empty (which  may
		                                         *       happen if the part's original contents have since been added to
		                                         *       a neighboring part; s.a. `mpart_merge()') */
	};
#else /* __WANT_MPART_INIT && __SIZEOF_POS_T__ > __SIZEOF_POINTER__ */
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_minaddr (pos_t)
#define MPART_INIT_mp_maxaddr (pos_t)
#endif /* __WANT_MPART_INIT */
	PAGEDIR_PAGEALIGNED pos_t     mp_minaddr;   /* [lock(READ (MPART_F_LOCKBIT || mp_meta->mpm_ftxlock || mp_file->mf_lock || ANY(mp_copy, mp_share)->mn_mman->mm_lock),
	                                             *       WRITE(MPART_F_LOCKBIT && mp_meta->mpm_ftxlock && mp_file->mf_lock && ALL(mp_copy, mp_share)->mn_mman->mm_lock))]
	                                             *                                \------------------/    \--------------/
	                                             *                                 Only if allocated      Only if not anon!
	                                             * [const_if(EXISTS(MPART_BLOCK_ST_INIT) ||
	                                             *           mp_meta->mpm_dmalocks != 0)]
	                                             * In-file starting address of this part.
	                                             * Aligned by PAGESIZE, and the associated file's block-size. */
	pos_t                         mp_maxaddr;   /* [lock(LIKE(mp_minaddr))][const_if(like(mp_minaddr))]
	                                             * In-file max address of this  part. (NOTE: when 1  is
	                                             * added, also aligned like `mp_minaddr' must be)
	                                             * NOTE: May be set to `mp_minaddr - 1' if the part is empty (which  may
	                                             *       happen if the part's original contents have since been added to
	                                             *       a neighboring part; s.a. `mpart_merge()')
	                                             * NOTE: The  difference between this and `mp_minaddr' must
	                                             *       not be greater than `SIZE_MAX' (aka. `(size_t)-1') */
#endif /* !__WANT_MPART_INIT || __SIZEOF_POS_T__ <= __SIZEOF_POINTER__ */
#ifdef __WANT_MPART_INIT
#ifdef __WANT_MPART__mp_trmlop
#define MPART_INIT_mp_filent(...) { __VA_ARGS__ }
#else /* __WANT_MPART__mp_trmlop */
#define MPART_INIT_mp_filent(...) __VA_ARGS__
#endif /* !__WANT_MPART__mp_trmlop */
#endif /* __WANT_MPART_INIT */
#ifdef __WANT_MPART__mp_trmlop
	union {
		RBTREE_NODE(mpart)        mp_filent;    /* [lock(READ (MPART_F_LOCKBIT || mp_file->mf_lock),
		                                         *       WRITE(MPART_F_LOCKBIT && mp_file->mf_lock))]
		                                         * [valid_if(!mpart_isanon(self))]
		                                         * Entry with the associated file's tree. */
		struct { /* [valid_if(mpart_isanon(self))] */
			void               *__mp_trmlop_pad; /* Always `(void *)-1' */
			union {
				Toblockop(mman)      _mp_trmlop_mm;  /* Used internally by `mpart_trim()' */
				Tobpostlockop(mman)  _mp_trmplop_mm; /* Used internally by `mpart_trim()' */
				Toblockop(mpart)     _mp_trmlop_mp;  /* Used internally by `mpart_trim()' */
				Tobpostlockop(mpart) _mp_trmplop_mp; /* Used internally by `mpart_trim()' */
			};
		};
	};
#else /* __WANT_MPART__mp_trmlop */
	RBTREE_NODE(mpart)            mp_filent;    /* [lock(READ (MPART_F_LOCKBIT || mp_file->mf_lock),
	                                             *       WRITE(MPART_F_LOCKBIT && mp_file->mf_lock))]
	                                             * [valid_if(!mpart_isanon(self))]
	                                             * Entry with the associated file's tree. */
#endif /* !__WANT_MPART__mp_trmlop */
	union {
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_blkst_ptr(mp_blkst_ptr) { mp_blkst_ptr }
#define MPART_INIT_mp_blkst_inl(mp_blkst_inl) { (uintptr_t *)(uintptr_t)(mp_blkst_inl) }
#endif /* __WANT_MPART_INIT */
		/* Block-state bitset. Note that the size of a block is measured in bytes,
		 * may be smaller than a single page, and its actual size is fixed, and is
		 * described by the associated mfile. (s.a. `MPART_BLOCK_ST_*') */
		uintptr_t                *mp_blkst_ptr; /* [lock(MPART_F_LOCKBIT)][0..1][lock(MPART_F_LOCKBIT || EXISTS(MPART_BLOCK_ST_INIT))]
		                                         * [valid_if(!MPART_F_BLKST_INL)]
		                                         * NOTE: When set to `NULL', then monitoring the part for changes becomes
		                                         *       impossible, and the caller should  act as though all parts  were
		                                         *       using `MPART_BLOCK_ST_CHNG' as their state.
		                                         *       This is usually only done for parts where write-monitoring
		                                         *       doesn't  really  make  any  sense,  such  as `mfile_phys'.
		                                         * NOTE: Changing the state of block that used to be `MPART_BLOCK_ST_INIT' to
		                                         *       anything else may be done atomically, and without holding any locks.
		                                         * NOTE: When the part state is `MPART_ST_VOID' and this bitset is `NULL', then
		                                         *       the intended  meaning is  that all  blocks are  `MPART_BLOCK_ST_NDEF'. */
		uintptr_t                 mp_blkst_inl; /* [lock(MPART_F_LOCKBIT)]
		                                         * [valid_if(MPART_F_BLKST_INL)] */
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
		struct mchunk             mp_mem;    /* [valid_if(MPART_ST_MEM)] Physically allocated memory */
		struct mchunkvec          mp_mem_sc; /* [valid_if(MPART_ST_MEM_SC)] Scattered memory */
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
		 * `mpart_lock_acquire_and_setcore_denywrite_sync') and  only use  swap memory  (of
		 * changed blocks) if the part is still marked as changed.
		 * Unchanged,  but allocated blocks can simply be  freed, and you are allowed to
		 * assume that any unchanged block can always be re-constructed at a later point
		 * in time by making use of the `mo_loadblocks' operator.
		 *
		 * Also note that  parts with  the `MPART_F_NOFREE' flag  set should  never be  off-
		 * loaded into swap: If not only because doing so wouldn't actually free up physical
		 * memory, doing so might actually cause problems (since `MPART_F_NOFREE' is set  by
		 * special files such as `mfile_phys')
		 */
		struct mchunk             mp_swp;    /* [valid_if(MPART_ST_SWP)] Physically allocated swap */
		struct mchunkvec          mp_swp_sc; /* [valid_if(MPART_ST_SWP_SC)] Scattered swap */
	};
#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_meta(mp_meta) mp_meta
#endif /* __WANT_MPART_INIT */
	struct mpartmeta             *mp_meta;      /* [0..1][owned][lock(READ(ATOMIC), WRITE(ONCE && MPART_F_LOCKBIT))]
	                                             * Runtime meta-data for futex and RTM support. */
#if __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__
	byte_t __mp_pad[__ALIGNOF_POS_T__ - __ALIGNOF_POINTER__];
#endif /* __ALIGNOF_POS_T__ > __ALIGNOF_POINTER__ */
};


#ifdef __WANT_MPART_INIT
#define MPART_INIT_mp_filent_asanon() MPART_INIT_mp_filent({  })
#define MPART_INIT_PHYS(file, first_page, page_count, num_bytes)   \
	{                                                              \
		MPART_INIT_mp_refcnt(1),                                   \
		MPART_INIT_mp_flags(MPART_F_NOFREE | MPART_F_NOSPLIT |     \
		                    MPART_F_MLOCK | MPART_F_MLOCK_FROZEN), \
		MPART_INIT_mp_state(MPART_ST_MEM),                         \
		MPART_INIT_mp_file(file),                                  \
		MPART_INIT_mp_copy(LIST_HEAD_INITIALIZER(~)),              \
		MPART_INIT_mp_share(LIST_HEAD_INITIALIZER(~)),             \
		MPART_INIT_mp_lockops(SLIST_HEAD_INITIALIZER(~)),          \
		MPART_INIT_mp_allparts(LIST_ENTRY_UNBOUND_INITIALIZER),    \
		MPART_INIT_mp_changed({}),                                 \
		MPART_INIT_mp_minaddr(0),                                  \
		MPART_INIT_mp_maxaddr((num_bytes)-1),                      \
		MPART_INIT_mp_filent_asanon(),                             \
		MPART_INIT_mp_blkst_ptr(__NULLPTR),                        \
		MPART_INIT_mp_mem(first_page, page_count),                 \
		MPART_INIT_mp_meta(__NULLPTR)                              \
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


#ifndef NDEBUG
/* Assert the integrity of the given mem-part and associated nodes.
 * The caller must be holding a lock to `self'. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_assert_integrity)(struct mpart *__restrict self);
#else /* !NDEBUG */
#define mpart_assert_integrity(self) (void)0
#endif /* NDEBUG */


/* Check   if  `self'  is  anonymous  (that  is:  `self !in self->mp_file->mf_parts')
 * Note that as long as you're holding a lock to `self', you may make the assumption:
 *    `(!wasdestroyed(self) && !mpart_isanon(self)) -> !mfile_isanon(self->mp_file)'
 * Even when you're not actually holding a lock to the associated file.
 * NOTE: You may also assume that once some given mem-part becomes anonymous, it will
 *       never become non-anonymous again (i.e. anonymous parts can't be  re-attached
 *       to mem-files!)
 * NOTE: Also note that the `rb_lhs' and  `rb_rhs' fields of anonymous mem-parts  are
 *       still  used internally by  `mpart_trim()' (which only  serves a function for
 *       anonymous mem-parts, which normally don't use those 2 fields), which is also
 *       the  reason why `_mpart_init_asanon()'  still fills in  `rb_rhs' as NULL, as
 *       this is a requirement for `mpart_trim()' to function correctly. */
#define mpart_isanon(self)        ((self)->mp_filent.rb_par == (struct mpart *)-1)
#define mpart_isanon_atomic(self) (__hybrid_atomic_load(&(self)->mp_filent.rb_par, __ATOMIC_ACQUIRE) == (struct mpart *)-1)

/* Fill in `self->mp_filent' such that `self' is marked as an anonymous mem-part.
 * NOTE: `rb_rhs' must be filled in with `NULL' as an indicator for `mpart_trim()'! */
#ifdef NDEBUG
#define _mpart_init_asanon(self)                          \
	(void)((self)->mp_filent.rb_par = (struct mpart *)-1, \
	       (self)->mp_filent.rb_rhs = __NULLPTR)
#elif __SIZEOF_POINTER__ == 4
#define _mpart_init_asanon(self)                                              \
	(void)((self)->mp_filent.rb_par = (struct mpart *)-1,                     \
	       (self)->mp_filent.rb_lhs = (struct mpart *)__UINT32_C(0xcccccccc), \
	       (self)->mp_filent.rb_rhs = __NULLPTR)
#elif __SIZEOF_POINTER__ == 8
#define _mpart_init_asanon(self)                                                      \
	(void)((self)->mp_filent.rb_par = (struct mpart *)-1,                             \
	       (self)->mp_filent.rb_lhs = (struct mpart *)__UINT64_C(0xcccccccccccccccc), \
	       (self)->mp_filent.rb_rhs = __NULLPTR)
#else /* __SIZEOF_POINTER__ == ... */
#define _mpart_init_asanon(self)                          \
	(void)((self)->mp_filent.rb_par = (struct mpart *)-1, \
	       (self)->mp_filent.rb_rhs = __NULLPTR)
#endif /* __SIZEOF_POINTER__ != ... */


/* Reference counting control for `struct mpart' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mpart_free)(struct mpart *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mpart_destroy)(struct mpart *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct mpart, mp_refcnt, mpart_destroy)
#define mpart_xfree(self) (void)(!(self) || (mpart_free(self), 1))


/* Reap lock operations enqueued for execution when `self' can be locked. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mpart_lockops_reap)(struct mpart *__restrict self);
#define mpart_lockops_mustreap(self) (__hybrid_atomic_load(&(self)->mp_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mpart_lockops_reap(self) _mpart_lockops_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mpart_lockops_reap(self) (void)(!mpart_lockops_mustreap(self) || (_mpart_lockops_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */

/* Lock accessor helpers for `struct mpart' */
#define mpart_lock_tryacquire(self) \
	(!(__hybrid_atomic_fetchor(&(self)->mp_flags, MPART_F_LOCKBIT, __ATOMIC_ACQUIRE) & MPART_F_LOCKBIT))
#define mpart_lock_release(self)                                                 \
	(__hybrid_atomic_and(&(self)->mp_flags, ~MPART_F_LOCKBIT, __ATOMIC_ACQUIRE), \
	 mpart_lockops_reap(self))
#define _mpart_lock_release(self) \
	(__hybrid_atomic_and(&(self)->mp_flags, ~MPART_F_LOCKBIT, __ATOMIC_ACQUIRE))
#define mpart_lock_acquired(self)  (__hybrid_atomic_load(&(self)->mp_flags, __ATOMIC_ACQUIRE) & MPART_F_LOCKBIT)
#define mpart_lock_available(self) (!(__hybrid_atomic_load(&(self)->mp_flags, __ATOMIC_ACQUIRE) & MPART_F_LOCKBIT))

FORCELOCAL NONNULL((1)) void
mpart_lock_acquire(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK) {
	while (!mpart_lock_tryacquire(self))
		__hybrid_yield();
}
FORCELOCAL WUNUSED NONNULL((1)) __BOOL
NOTHROW(mpart_lock_acquire_nx)(struct mpart *__restrict self) {
	while (!mpart_lock_tryacquire(self)) {
		if (!__hybrid_yield_nx())
			return 0;
	}
	return 1;
}
FORCELOCAL NONNULL((1)) void
mpart_lock_waitfor(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK) {
	while (!mpart_lock_available(self))
		__hybrid_yield();
}
FORCELOCAL WUNUSED NONNULL((1)) __BOOL
NOTHROW(mpart_lock_waitfor_nx)(struct mpart *__restrict self) {
	while (!mpart_lock_available(self)) {
		if (!__hybrid_yield_nx())
			return 0;
	}
	return 1;
}





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
 *       and    will   pass   that   value   onto   `mfile_alloc_physmem_nocc()'! */
FUNDEF NONNULL((1)) void FCALL
mpart_ll_allocmem(struct mpart *__restrict self,
                  size_t total_pages)
		THROWS(E_BADALLOC);
/* TODO: `mpart_ll_allocmem()' should be able to take hints as to the physical
 *       addresses that we'd prefer it to allocate. - That way, the caller may
 *       specify the physical addresses of neighboring mappings during  alloc,
 *       allowing pagedir mappings to be more linear than they'd otherwise be. */


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
                  NCX void const *src,
                  size_t num_bytes)
		THROWS(E_SEGFAULT);

/* Low-level bzero-if-!page_iszero() the given address range.
 * The  caller must ensure that `offset...+=num_bytes' is in-
 * bounds of the given mem-part! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mpart_ll_bzeromemcc)(struct mpart *__restrict self,
                                   mpart_reladdr_t offset,
                                   size_t num_bytes);

/* Reset the `page_iszero()' for physical memory of `self'.
 * -> This is helper wrapper around `page_resetzero()'. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mpart_ll_resetzero)(struct mpart *__restrict self);

/* Low-level populate the given address range by loading it from disk.
 * No bounds check is  done by this function,  and the caller must  be
 * holding a trunc-lock to the file associated with `self'! */
FUNDEF BLOCKING NONNULL((1)) void KCALL
mpart_ll_populate(struct mpart *__restrict self,
                  mpart_reladdr_t blockaligned_offset,
                  size_t blockaligned_num_bytes);


/* Return  the # of pages containing MPART_BLOCK_ST_CHNG-
 * blocks that can be found within `[0,partrel_pageaddr)'
 *
 * This function should be used to convert from part-rel
 * offsets  into in-swap-data offsets when `self's state
 * indicates that the part is currently located in swap. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) physpagecnt_t
NOTHROW(FCALL mpart_page2swap)(struct mpart const *__restrict self,
                               physpagecnt_t partrel_pageaddr);



/************************************************************************/
/* MPart API to lock a part, alongside doing some other operations.     */
/************************************************************************/

/************************************************************************
 * Lock-less mem-part status assertion/goal-approaching functions
 * All of these work on the principle:
 *   #1: Check if the wanted condition has already been met
 *       If so, return `true'
 *   #2: Check if (additional) data that is needed to meet the
 *       condition  has been  given to  us by  the caller (via
 *       the `data' argument, as may have also been  allocated
 *       during previous attempts)
 *   #3: If any (needed) data is missing, try to allocate that data.
 *       Do  this using non-except GFP_ATOMIC and other non-blocking
 *       operations.
 *   #4: If data cannot be allocated using non-blocking operations,
 *       release the lock  that is held  by `self' (and  `*unlock')
 *       and  re-attempt  the  allocation  with  exception-enabled,
 *       blocking operations.
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



/* Possible return values for:
 * - mpart_initdone_or_unlock_nx
 * - mpart_nodma_or_unlock_nx
 * - mpart_trim_or_unlock_nx
 */
#define MPART_NXOP_ST_SUCCESS 0 /* Success (locks are still held) */
#define MPART_NXOP_ST_RETRY   1 /* Try again (all locks were released) */
#define MPART_NXOP_ST_ERROR   2 /* Hard error (all locks were released; DON'T try again) */



/* Ensure that `!mpart_hasblocksstate_init(self)' */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mpart_initdone_or_unlock(struct mpart *__restrict self,
                         struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_initdone_or_unlock_nx)(struct mpart *__restrict self,
                                           struct unlockinfo *unlock);

/* Ensure that `self->mp_meta == NULL || self->mp_meta->mpm_dmalocks == 0' */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mpart_nodma_or_unlock(struct mpart *__restrict self,
                      struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_nodma_or_unlock_nx)(struct mpart *__restrict self,
                                        struct unlockinfo *unlock);
#define mpart_is_nodma(self) \
	(!(self)->mp_meta || __hybrid_atomic_load(&(self)->mp_meta->mpm_dmalocks, __ATOMIC_ACQUIRE) == 0)

/* Ensure that `self->mp_meta != NULL' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mpart_hasmeta_or_unlock(struct mpart *__restrict self,
                        struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Simplified cache-clear state for `system_cc_s' */
#ifndef __ccstate_t_defined
#define __ccstate_t_defined
typedef uint32_t ccstate_t;
#define CCSTATE_INIT       0
#define ccstate_init(self) (void)(*(self) = CCSTATE_INIT)
#endif /* !__ccstate_t_defined */

struct mpart_setcore_data {
	uintptr_t           *scd_bitset;      /* [0..1][owned] Block-status bitset. */
	unsigned int         scd_copy_state;  /* One of `MPART_ST_VOID', `MPART_ST_MEM' or `MPART_ST_MEM_SC' */
	ccstate_t            scd_ccstate;     /* CC-state for `system_cc_s' */
	union {
		struct mchunk    scd_copy_mem;    /* [valid_if(scd_copy_state == MPART_ST_MEM)][owned] */
		struct mchunkvec scd_copy_mem_sc; /* [valid_if(scd_copy_state == MPART_ST_MEM_SC)][owned] */
	};
};
#define MPART_SETCORE_DATA_INIT                     \
	{                                               \
		__NULLPTR, MPART_ST_VOID, CCSTATE_INIT, { } \
	}
#define mpart_setcore_data_init(self)              \
	(void)((self)->scd_bitset     = __NULLPTR,     \
	       (self)->scd_copy_state = MPART_ST_VOID, \
	       ccstate_init(&(self)->scd_ccstate))

/* Finalize data needed for `mpart_setcore_or_unlock()' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setcore_data_fini)(struct mpart_setcore_data *__restrict self);

/* Ensure that `MPART_ST_INCORE(self->mp_state)' */
FUNDEF BLOCKING WUNUSED NONNULL((1, 3)) __BOOL FCALL
mpart_setcore_or_unlock(struct mpart *__restrict self,
                        struct unlockinfo *unlock,
                        struct mpart_setcore_data *__restrict data)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Ensure that all blocks (within the given range of blocks)
 * are either `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG'
 * The caller must ensure that...
 *   - ... the given address range is in-bounds!
 *   - ... MPART_ST_INCORE(self->mp_state)
 * If they don't, then this function will cause an assertion failure! */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mpart_load_or_unlock(struct mpart *__restrict self,
                     struct unlockinfo *unlock,
                     mpart_reladdr_t partrel_offset,
                     size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

struct mpart_unsharecow_data {
	struct mpart_setcore_data ucd_ucmem; /* Data for unshare. */
	struct mpart             *ucd_copy;  /* [0..1] The duplicate of the original mem-part. */
};
#define MPART_UNSHARECOW_DATA_INIT \
	{ MPART_SETCORE_DATA_INIT, __NULLPTR }
#define mpart_unsharecow_data_init(self)                \
	(void)(mpart_setcore_data_init(&(self)->ucd_ucmem), \
	       (self)->ucd_copy = __NULLPTR)
#define mpart_unsharecow_data_fini(self) \
	(__os_free((self)->ucd_copy),        \
	 mpart_setcore_data_fini(&(self)->ucd_ucmem))

#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */


/* Ensure that `LIST_EMPTY(&self->mp_copy)' (while only considering nodes
 * which   may   be   overlapping   with   the   given   address   range)
 * NOTE: The  caller must first ensure that `MPART_ST_INCORE(self->mp_state)',
 *       otherwise this function will result in an internal assertion failure.
 * NOTE: The `LIST_EMPTY(&self->mp_copy)' mustn't be seen ~too~ strictly, as
 *       the list is still allowed to contain dead nodes that are about  to,
 *       or have already been added as lock-ops to `mp_lockops'.
 *       However, the mmans of all nodes still apart of the mp_copy list have
 *       already been destroyed, such that  no alive copy-nodes still  exist! */
FUNDEF BLOCKING WUNUSED NONNULL((1, 3)) __BOOL FCALL
mpart_unsharecow_or_unlock(struct mpart *__restrict self,
                           struct unlockinfo *unlock,
                           struct mpart_unsharecow_data *__restrict data,
                           mpart_reladdr_t partrel_offset, size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


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
                          struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY);
/************************************************************************/


/* Acquire a lock until:
 *  - mpart_initdone_or_unlock(self, ...) */
FUNDEF BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_initdone(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Acquire a lock until:
 *  - mpart_initdone_or_unlock(self, ...)
 *  - mpart_nodma_or_unlock(self, ...) */
FUNDEF BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_initdone_nodma(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...) */
FUNDEF BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_load_or_unlock(self, ...)    // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be loaded)
 *
 * HINT: This function is used to implement `mpart_read()' */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mpart_lock_acquire_and_setcore_load(struct mpart *__restrict self,
                                    pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_unsharecow_or_unlock(self, ...)  // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be unshared/loaded)
 *
 * HINT: This function is used to implement `mman_startdma()' */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mpart_lock_acquire_and_setcore_unsharecow(struct mpart *__restrict self,
                                          pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

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
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mpart_lock_acquire_and_setcore_unsharecow_load(struct mpart *__restrict self,
                                               pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

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
FUNDEF BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore_denywrite_nodma(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


/* Get/Set the state of the index'd block `partrel_block_index' from the part's block-state bitset.
 * NOTE: The caller is responsible to ensure that `partrel_block_index' is
 *       located in-bounds.
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
 * @param: st:  One of `MPART_BLOCK_ST_*'
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

/* Perform extra actions after clearing `MPART_BLOCK_ST_INIT' states in `self'. */
#define mpart_setblockstate_initdone_extrahooks(self)                                          \
	(__hybrid_atomic_load(&(self)->mp_xflags, __ATOMIC_ACQUIRE) & (MPART_XF_MERGE_AFTER_INIT | \
	                                                               MPART_XF_TRIM_AFTER_INIT)   \
	 ? _mpart_setblockstate_initdone_extrahooks(incref(self))                                  \
	 : (void)0)
#define mpart_setblockstate_initdone_extrahooks_and_decref(self)                               \
	(__hybrid_atomic_load(&(self)->mp_xflags, __ATOMIC_ACQUIRE) & (MPART_XF_MERGE_AFTER_INIT | \
	                                                               MPART_XF_TRIM_AFTER_INIT)   \
	 ? _mpart_setblockstate_initdone_extrahooks(self)                                          \
	 : decref(self))
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mpart_setblockstate_initdone_extrahooks)(REF struct mpart *__restrict self);

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

/* Load  the bounds of the longest consecutive physical memory address range
 * that starts at `partrel_offset', has been populated with meaningful data,
 * and contains at least 1 byte (and at most `num_bytes' bytes).
 *
 * Note that `result->mppl_size < num_bytes' for multiple reasons:
 *  - The end of the given mem-part `self' is reached
 *  - Backing physical memory of `self' is scattered, and the next
 *    byte is apart of the  next (discontinuous) chunk of  memory.
 *  - The next block located at the end of the returned range isn't
 *    already loaded in-core. (that is:  doesn't have a state  that
 *    was set to `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG')
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
 * While `mpart_memaddr_for_read()' requires that all blocks that overlap
 * with the returned range have  a state of either  `MPART_BLOCK_ST_LOAD'
 * or `MPART_BLOCK_ST_CHNG', this function only requires this for the 0-2
 * blocks that only partially overlap with the returned range.
 *
 * All of the blocks that fully overlap with the returned range are
 * only required to not have a state set to  `MPART_BLOCK_ST_INIT'.
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
 * For this purpose, this function will:
 *  - Set the state of all blocks that fully overlap with the given
 *    address range  to  `MPART_BLOCK_ST_CHNG',  (after  internally
 *    asserting  that their old state wasn't `MPART_BLOCK_ST_INIT')
 *  - Of the 0-2 blocks that only overlap partially with the given
 *    address  range,  make   the  following  state   transitions:
 *     - MPART_BLOCK_ST_LOAD -> MPART_BLOCK_ST_CHNG
 *     - MPART_BLOCK_ST_CHNG -> MPART_BLOCK_ST_CHNG  (i.e. no-op)
 *     - MPART_BLOCK_ST_INIT: Internal assertion failure
 *     - MPART_BLOCK_ST_NDEF:
 *       - If the partially overlapped block isn't the last (iow: right-most)
 *         block (meaning  that the  given address  range partially  overlaps
 *         with its beginning), then an internal assertion fails.
 *       - If the partially overlapped block _is_ the last block,  then
 *         it's state also remains unaltered, and this function returns
 *         the offset from `partrel_offset' to that block's start.
 *
 * If this function manages change any at least 1 block to `MPART_BLOCK_ST_CHNG'
 * when that block  wasn't already marked  as such, and  if the associated  file
 * implements the `mo_saveblocks' operator,  then set the MPART_F_CHANGED  flag.
 * If  that flag wasn't  set before, then add  a new reference  to `self' to the
 * list of changed parts of the associated file (unless the file's list of parts
 * marked as changed was set to `mf_changed = MFILE_PARTS_ANONYMOUS').
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
 * containing block has transitioned to one of `MPART_BLOCK_ST_LOAD'  or
 * `MPART_BLOCK_ST_CHNG')
 * The given `loc->mppl_size' is a hint as to how many consecutive blocks
 * this function should attempt to load, though it will only ever load  a
 * single cluster of consecutive blocks that starts with an uninitialized
 * block containing `partrel_offset' */
FUNDEF BLOCKING NONNULL((1, 3)) void FCALL
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

/* Return a direct pointer to the physical address at `partrel_offset'.
 * The  # of bytes which can be  read from this address directly depend
 * on  the alignment of `partrel_offset'. (s.a. `mpart_memaddr_direct') */
FUNDEF NOBLOCK NONNULL((1)) physaddr_t
NOTHROW(FCALL mpart_getphysaddr)(struct mpart *__restrict self,
                                 mpart_reladdr_t partrel_offset);

/* Mark all blocks that overlap with the given address range as CHNG.
 * For this purpose, the caller must ensure that:
 * >> !OVERFLOW_UADD(partrel_offset, num_bytes, &endaddr) && endaddr <= mpart_getsize(self)
 *
 * If any of the blocks  within the given range had  yet to be marked as  CHNG,
 * and the associated file is not anonymous, and implements the `mo_saveblocks'
 * operator, and the  `MPART_F_CHANGED' flag had  yet to be  set for the  given
 * part, then set  the `MPART_F_CHANGED'  flag and add  `self' to  the list  of
 * changed parts of its associated file (unless the file's list of parts marked
 * as changed was set to `mf_changed = MFILE_PARTS_ANONYMOUS').
 * NOTE: The caller must be holding a lock to `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_changed)(struct mpart *__restrict self,
                             mpart_reladdr_t partrel_offset,
                             size_t num_bytes);




/* Split the given mem-part `self' (which  should be a member of  `file')
 * after `offset' bytes from the start of backing file. For this purpose,
 * the given `offset' should  be `> mpart_getminaddr(self)', and must  be
 * both page- and block-aligned.
 * @return: NULL: The given `offset' is outside  the bounds of file  memory
 *                represented by `part'. The caller should handle this case
 *                by re-checking for a missing part, and creating that part
 *                if it cannot be found.
 * @return: * :   A reference to a part that (at one point) began at `offset' */
FUNDEF BLOCKING NONNULL((1)) REF struct mpart *FCALL
mpart_split(struct mpart *__restrict self,
            PAGEDIR_PAGEALIGNED pos_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Sync changes made to the given mem-part.
 * @return: * : The total # of bytes that were synced.
 * NOTE: The caller is responsible for adding/removing the part to/from
 *       the associated file's list of changed parts! */
FUNDEF BLOCKING NONNULL((1)) size_t FCALL
mpart_sync(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as `mpart_sync()', but keep on holding onto the lock to `self' */
FUNDEF BLOCKING NONNULL((1)) size_t FCALL
mpart_lock_acquire_and_setcore_denywrite_sync(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


/* (Re-)map the given mem-part into a page directory.
 * The caller must ensure:
 *   - mpart_lock_acquired(self)               (unless `self' was accessed from a hinted node,
 *                                              or the caller knows that `self' can't be accessed
 *                                              from the outside world)
 *   - pagedir_prepare_p(self, addr, size)     (was called)
 *
 * NOTES:
 *   - When  mapping  blocks not  marked  as `MPART_BLOCK_ST_CHNG',
 *     the `PAGEDIR_PROT_WRITE' prot-flag is automatically cleared.
 *   - When mapping blocks marked as `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT',
 *     the `PAGEDIR_PROT_EXEC', `PAGEDIR_PROT_READ'  and `PAGEDIR_PROT_WRITE'  prot-
 *     flags are automatically cleared.
 *
 * @return: * : The union of permissions actually applied to all  pages.
 *              This may be used to figure out if write permissions were
 *              actually given to any of the requested pages. */
FUNDEF NOBLOCK NONNULL((1)) pagedir_prot_t
NOTHROW(FCALL mpart_mmap_p)(struct mpart const *__restrict self, pagedir_phys_t pdir,
                            PAGEDIR_PAGEALIGNED void *addr,
                            PAGEDIR_PAGEALIGNED size_t size,
                            PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                            pagedir_prot_t prot);

/* Same as `mpart_mmap_p()', but always map into the current page directory. */
FUNDEF NOBLOCK NONNULL((1)) pagedir_prot_t
NOTHROW(FCALL mpart_mmap)(struct mpart const *__restrict self,
                          PAGEDIR_PAGEALIGNED void *addr,
                          PAGEDIR_PAGEALIGNED size_t size,
                          PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                          pagedir_prot_t prot);

/* Similar to `mpart_mmap_p()', but force the given `prot' for all pages, no
 * matter  what the block-status  bitset of `self' might  say of the matter. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap_force_p)(struct mpart const *__restrict self, pagedir_phys_t pdir,
                                  PAGEDIR_PAGEALIGNED void *addr,
                                  PAGEDIR_PAGEALIGNED size_t size,
                                  PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                  pagedir_prot_t prot);

/* Same as `mpart_mmap_force_p()', but always map into the current page directory. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap_force)(struct mpart const *__restrict self,
                                PAGEDIR_PAGEALIGNED void *addr,
                                PAGEDIR_PAGEALIGNED size_t size,
                                PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                pagedir_prot_t prot);

/* For use with `MNODE_F_MHINT':
 *  - Ensure that the pages (== block) at the given `offset'
 *    has been marked as `MPART_BLOCK_ST_CHNG', invoking the
 *    block loader from the associated file if necessary.
 *  - Afterwards, map the associated page to `addr' within
 *    the   current   page   directory,   using    `prot'.
 * This function is used to implement handling of hinted
 * mem-nodes   when  encountered  by  the  #PF  handler. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL mpart_hinted_mmap)(struct mpart *__restrict self,
                                 PAGEDIR_PAGEALIGNED void *addr,
                                 PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                 pagedir_prot_t prot);

/* Convenience wrapper for `mpart_hinted_mmap()' */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL mnode_hinted_mmap)(struct mnode *__restrict self,
                                 PAGEDIR_PAGEALIGNED void *fault_page);



/* Try to merge `self' with neighboring parts from the associated file.
 * @return: * : A pointer to the (possibly merged) mem-part. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mpart_merge)(REF struct mpart *__restrict self);

/* Same as `mpart_merge()',  but the caller  is holding a  lock
 * to `self' upon entry, and will be holding a lock to `return'
 * upon exit. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mpart_merge_locked)(REF struct mpart *__restrict self);



/* If `self' is an anonymous mem-part, asynchronously acquire a
 * lock to `self' and compare the min/max-addr bounds of `self'
 * against the portions that are actually mapped by  mem-nodes.
 * If it is found that leading/trailing portions of `self'  are
 * not mapped by  any mem-node, trim  those parts from  `self'.
 * If there are holes within `self' of pages not mapped by  any
 * mem-nodes,  asynchronously split `self', and update nodes in
 * order to get rid of the relevant ranges.
 * This function should  be called  whenever mem-node  mappings
 * of `self' have been removed, in order to drop the references
 * that were originally held by those nodes.
 * NOTE: When `self' isn't anonymous, simply `decref(self)'!
 * NOTE: This function usually doesn't need to be called directly.
 *       Instead, it is  called from  `mnode_destroy()' to  decref
 *       the associated part after the node has been removed  from
 *       the list of node-mappings of `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim)(/*inherit(always)*/ REF struct mpart *__restrict self);

struct ccinfo;

/* Possible mpart-trim levels. */
#define MPART_TRIM_MODE_UNMAPPED      0   /* Trim unmapped blocks (when the part isn't anonymous, don't trim blocks
                                           * with status `MPART_BLOCK_ST_CHNG') of the given mem-part (this is also
                                           * what `mpart_trim()' does, except that it *only* trims parts if they're
                                           * anonymous, meaning it can just ignore `MPART_BLOCK_ST_CHNG') */
#define MPART_TRIM_MODE_UNINITIALIZED 1   /* Trim  uninitialized blocks of the given mem-part  (even if mappings exist for them.
                                           * Since  those blocks aren't initialized, we can assume that they don't appear in any
                                           * page directory, meaning they can be unloaded safely). Parts that are not mapped are
                                           * unmapped also (just as with `MPART_TRIM_MODE_UNMAPPED')
                                           * NOTE: When `MPART_F_MLOCK' is set this behaves the same as `MPART_TRIM_MODE_UNMAPPED' */
#define MPART_TRIM_MODE_UNCHANGED     2   /* Trim all blocks that don't have status `MPART_BLOCK_ST_CHNG'
                                           * Any blocks that are initialized+mapped will be unmapped such
                                           * that they are loaded once again during the next access.
                                           * NOTE: When `MPART_F_MLOCK' is set this behaves the same as `MPART_TRIM_MODE_UNMAPPED' */
#define MPART_TRIM_MODEMASK           0x3 /* Mask of mode bits */
#define MPART_TRIM_FLAG_SYNC          0x4 /* FLAG: Blocks that normally couldn't be  unloaded because they are marked  as
                                           *       `MPART_BLOCK_ST_CHNG' can now also be unloaded. This is done by rather
                                           *       than skipping such blocks, they are  written back to disk (any  errors
                                           *       that during this are discarded before returning `MPART_NXOP_ST_ERROR')
                                           *       and marking the block as `MPART_BLOCK_ST_LOAD' and treating it as such
                                           * NOTE: When the part is anonymous, or the file doesn't implement the `mo_saveblocks'
                                           *       operator, this flag is simply ignored.
                                           * NOTE: When the part has the `MPART_F_MLOCK' flag, this flag is ignored. */
#define MPART_TRIM_FLAG_SWAP          0x8 /* FLAG: Blocks that normally couldn't be  unloaded because they are marked  as
                                           *       `MPART_BLOCK_ST_CHNG' can now also be unloaded. This is done by rather
                                           *       than  skipping such blocks,  they are split  into a separate mem-part,
                                           *       then written to swap (any errors that during this are discarded before
                                           *       trying to re-merge the split part and returning `MPART_NXOP_ST_ERROR')
                                           *       The part is then marked as `MPART_ST_VOID'
                                           * NOTE: When the part isn't anonymous, and the file implements the `mo_saveblocks'
                                           *       operator, this flag is simply ignored.
                                           * NOTE: When the part has the `MPART_F_MLOCK' flag, this flag is ignored. */

struct mpart_trim_data {
	struct mpart      *mtd_parts[2];  /* [0..1][owned] Extra mem-parts as may be needed. */
	struct mpartmeta  *mtd_metas[2];  /* [0..1][owned] Extra mem-part-meta controllers as may be needed. */
	uintptr_t         *mtd_blkst_ptr; /* [0..1][owned] Pre-allocated block-state vector. */
	struct ccinfo     *mtd_ccinfo;    /* [1..1][const] Cache-clearing information. */
	struct unlockinfo *mtd_unlock;    /* [0..1][const] Extra stuff to unlock */
	unsigned int       mtd_mode;      /* [const] Trim mode (s.a. `MPART_TRIM_MODE_*' and `MPART_TRIM_FLAG_*') */
};
#define mpart_trim_data_init(self, info, unlock, mode) \
	(void)((self)->mtd_parts[0]  = __NULLPTR,          \
	       (self)->mtd_parts[1]  = __NULLPTR,          \
	       (self)->mtd_metas[0]  = __NULLPTR,          \
	       (self)->mtd_metas[1]  = __NULLPTR,          \
	       (self)->mtd_blkst_ptr = __NULLPTR,          \
	       (self)->mtd_ccinfo    = (info),             \
	       (self)->mtd_unlock    = (unlock),           \
	       (self)->mtd_mode      = (mode))
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim_data_fini)(struct mpart_trim_data *__restrict self);

/* Synchronous version of `mpart_trim()' (that is also able to trim non-anonymous parts)
 * This function is specifically designed to-be used by `system_cc()' (in case you  were
 * wondering about the meaning of `data->mtd_ccinfo')
 * NOTE: The caller must be holding a lock to `self' when calling this function.
 * NOTE: This  function operates with respect to `ccinfo_noblock(data->mtd_ccinfo)',
 *       in that it will operate as a  no-op whenever something comes up that  would
 *       need to block, in which case `MPART_NXOP_ST_SUCCESS' is returned (emulating
 *       the behavior when  `self' was  trimmed, or  nothing about  `self' could  be
 *       trimmed)
 * @param: data: [in|out] Storage  area for dynamically allocated memory. Note that
 *                        unlike usually, this  data-area does  NOT become  invalid
 *                        when this function succeeds. Even  more so, it may  still
 *                        contain dynamically allocated memory that can be used for
 *                        further trim operations!
 * @return: MPART_NXOP_ST_SUCCESS: Success (all locks were kept)
 * @return: MPART_NXOP_ST_RETRY:   Failed (`data->mtd_unlock' and `mpart_lock_release(self)' was released)
 * @return: MPART_NXOP_ST_ERROR:   Non-recoverable error (OOM or yield-failure). Don't try again. */
FUNDEF NOBLOCK_IF(ccinfo_noblock(data->mtd_ccinfo)) WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mpart_trim_or_unlock_nx)(struct mpart *__restrict self,
                                       struct mpart_trim_data *__restrict data);




/* Try to allocate a new async job to  do `what', but if that fails use a  fallback
 * global  async job to do the same thing. _DONT_ call this function directly! This
 * function is used as the fallback-path when one of mpart named mem-part functions
 * can't be completed without  blocking, meaning that it  needs to be finished  via
 * async means. - If  you were to  call this function  directly, that initial  non-
 * blocking  attempt  would not  be  performed, which  would  introduce unnecessary
 * overhead  in the  case where the  operation could have  been done synchronously.
 * When multiple operations are scheduled at the same time, they will be  performed
 * in the following order:
 *  - MPART_XF_WILLMERGE:  `mpart_merge()'
 *  - MPART_XF_WILLTRIM:   `mpart_trim()'
 * @param: what: Set of `MPART_XF_WILLMERGE | MPART_XF_WILLTRIM' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_start_asyncjob)(/*inherit(always)*/ REF struct mpart *__restrict self,
                                    uintptr_quarter_t what);





/* Check if the given `addr...+=num_bytes' sub-range (which _must_ be
 * entirely  contained within the portion of `self' that is mapped by
 * the given `node')  can be given  write-access by `node',  assuming
 * that `node' is a copy-on-write mapping of `self'.
 *
 * For this purpose, direct write-access is only granted when the given
 * sub-range is not visible anywhere else (iow: when `node' effectively
 * has exclusive ownership of that range):
 *   - mpart_isanon(self)                                     // The part must be anon (else: changes would
 *                                                            // be visible when read(2)-ing from its file)
 *   - self->mp_share.filter(MAPS(addr, num_bytes)) == []     // No shared memory mappings
 *   - self->mp_copy .filter(MAPS(addr, num_bytes)) == [node] // Exactly 1 copy-on-write mapping, that is `node' */
#define mpart_iscopywritable(self, addr, num_bytes, node) \
	(mpart_isanon(self) &&                                \
	 ((LIST_EMPTY(&(self)->mp_share) &&                   \
	   LIST_FIRST(&(self)->mp_copy) == (node) &&          \
	   LIST_NEXT(node, mn_link) == __NULLPTR) ||          \
	  _mpart_iscopywritable(self, addr, num_bytes, node)))
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 4)) __BOOL
NOTHROW(FCALL _mpart_iscopywritable)(struct mpart const *__restrict self,
                                     mpart_reladdr_t addr, size_t num_bytes,
                                     struct mnode const *__restrict node);

/* Check if there are no copy-on-write nodes for the given address range
 * This must be ensured before shared write-access can be granted to the
 * specified  range, and if this isn't the case, the copy-on-write nodes
 * for said range must be unshared via `mpart_unsharecow_or_unlock()' */
#define mpart_issharewritable(self, addr, num_bytes) \
	(LIST_EMPTY(&(self)->mp_copy) || _mpart_issharewritable(self, addr, num_bytes))
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL _mpart_issharewritable)(struct mpart const *__restrict self,
                                      mpart_reladdr_t addr, size_t num_bytes);


/* Helper wrappers for the above functions. */
#define mpart_iswritable(self, addr, num_bytes, node)                                 \
	((node)->mn_flags & MNODE_F_SHARED ? mpart_issharewritable(self, addr, num_bytes) \
	                                   : mpart_iscopywritable(self, addr, num_bytes, node))
#define mnode_iscopywritable(self)  mpart_iscopywritable((self)->mn_part, mnode_getpartaddr(self), mnode_getsize(self), self)
#define mnode_issharewritable(self) mpart_issharewritable((self)->mn_part, mnode_getpartaddr(self), mnode_getsize(self))
#define mnode_iswritable(self)      mpart_iswritable((self)->mn_part, mnode_getpartaddr(self), mnode_getsize(self), self)


/* A slightly smarter equivalent of:
 * >> pagedir_prot_t perm;
 * >> perm = mnode_getprot(node);
 * >> perm = mpart_mmap(self, addr, size, offset);
 * >> return perm;
 * However, unlike that piece of code, this one determines if write
 * access can be granted on a per-page basis (see the documentation
 * of `mpart_iscopywritable()'  and  `mpart_issharewritable()'  for
 * when write-access can be given)
 * @return: * : The union (or aka. |-ed together) set of `PAGEDIR_PROT_*'
 *              flags  used to  map pages  from the  given address range. */
FUNDEF NOBLOCK NONNULL((1, 5)) pagedir_prot_t
NOTHROW(FCALL mpart_mmap_node)(struct mpart const *__restrict self,
                               PAGEDIR_PAGEALIGNED void *addr,
                               PAGEDIR_PAGEALIGNED size_t size,
                               PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                               struct mnode const *__restrict node);

/* Same as `mpart_mmap_node()', but map into the given page directory. */
FUNDEF NOBLOCK NONNULL((1, 6)) pagedir_prot_t
NOTHROW(FCALL mpart_mmap_node_p)(struct mpart const *__restrict self,
                                 pagedir_phys_t pdir,
                                 PAGEDIR_PAGEALIGNED void *addr,
                                 PAGEDIR_PAGEALIGNED size_t size,
                                 PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                 struct mnode const *__restrict node);




/* WARNING: Mem-part  read/write functions don't include file-size/read-only/etc. checks.
 *          Instead, all code should make use of `mfile_read' and `mfile_write' (etc...).
 * Only  call these functions while you can guaranty that the backing file can't be
 * truncated in the mean time (s.a.: `struct mfile::mf_trunclock'), unless you want
 * I/O to happen irregardless of file size. */


/* Read/write raw data to/from a given mem-part.
 * @return: * : The # of bytes that were transferred. May be less than `num_bytes' if the part
 *              is too small, or  if the given  `filepos' lies outside  of the part's  bounds. */
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_read(struct mpart *__restrict self, NCX void *dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_write(struct mpart *__restrict self, NCX void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_read_p(struct mpart *__restrict self, physaddr_t dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_write_p(struct mpart *__restrict self, physaddr_t src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_readv(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_writev(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_readv_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_writev_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as the above, but these use an intermediate (stack) buffer for  transfer.
 * As such, these functions are called by the above when `memcpy_nopf()' produces
 * transfer errors that cannot be resolved by `mman_prefault()' */
FUNDEF BLOCKING NONNULL((1)) size_t KCALL _mpart_buffered_read(struct mpart *__restrict self, NCX void *dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL _mpart_buffered_write(struct mpart *__restrict self, NCX void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL _mpart_buffered_readv(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL _mpart_buffered_writev(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);


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
 * Upon success, return the (non-zero) # of transferred bytes.
 * The caller must ensure that:
 *    >> num_bytes != 0
 *    >> MPART_ST_INCORE(self->mp_state)   // Can be ensured by `mpart_setcore_or_unlock()'
 *    >> mpart_unsharecow_or_unlock(...)   // Only for `mpart_write*', and only within the target address range */
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_read_or_unlock(struct mpart *__restrict self, NCX void *dst, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_write_or_unlock(struct mpart *__restrict self, NCX void const *src, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_read_or_unlock_p(struct mpart *__restrict self, physaddr_t dst, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mpart_write_or_unlock_p(struct mpart *__restrict self, physaddr_t src, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_readv_or_unlock(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_writev_or_unlock(struct mpart *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_readv_or_unlock_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mpart_writev_or_unlock_p(struct mpart *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, mpart_reladdr_t offset, struct unlockinfo *unlock) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);




/* Lock for `mpart_all_list' */
DATDEF struct atomic_lock mpart_all_lock;
#define _mpart_all_reap()      _lockop_reap_atomic_lock(&mpart_all_lops, &mpart_all_lock)
#define mpart_all_reap()       lockop_reap_atomic_lock(&mpart_all_lops, &mpart_all_lock)
#define mpart_all_tryacquire() atomic_lock_tryacquire(&mpart_all_lock)
#define mpart_all_acquire()    atomic_lock_acquire(&mpart_all_lock)
#define mpart_all_acquire_nx() atomic_lock_acquire_nx(&mpart_all_lock)
#define mpart_all_release()    (atomic_lock_release(&mpart_all_lock), mpart_all_reap())
#define mpart_all_release_f()  atomic_lock_release(&mpart_all_lock)
#define mpart_all_acquired()   atomic_lock_acquired(&mpart_all_lock)
#define mpart_all_available()  atomic_lock_available(&mpart_all_lock)
#define mpart_all_waitfor()    atomic_lock_waitfor(&mpart_all_lock)
#define mpart_all_waitfor_nx() atomic_lock_waitfor_nx(&mpart_all_lock)

/* [0..n][CHAIN(mp_allparts)][lock(mpart_all_lock)]
 * List of all memory parts currently in use. List head indices are `MPART_ALL_LIST_*'
 * NOTE: This list holds a reference to every contain part that wasn't
 *       already destroyed, and has the `MPART_F_GLOBAL_REF' flag set. */
DATDEF struct mpart_list mpart_all_list;

#ifndef CONFIG_NO_MPART_ALL_SIZE
/* [lock(mpart_all_lock)] The # of parts stored in `mpart_all_list' */
DATDEF size_t mpart_all_size;
#define _mpart_all_size_inc() (void)++mpart_all_size
#define _mpart_all_size_dec() (void)--mpart_all_size
#else /* !CONFIG_NO_MPART_ALL_SIZE */
#define _mpart_all_size_inc() (void)0
#define _mpart_all_size_dec() (void)0
#endif /* CONFIG_NO_MPART_ALL_SIZE */

/* Direct insert/remove a given part from `mpart_all_list'
 * The caller must be holding a  lock to `mpart_all_lock'! */
#define _mpart_all_list_insert(part) (LIST_INSERT_HEAD(&mpart_all_list, part, mp_allparts), _mpart_all_size_inc())
#define _mpart_all_list_remove(part) (_mpart_all_size_dec(), LIST_REMOVE(part, mp_allparts))

/* Return the # of items stored in `mpart_all_list' */
#ifdef CONFIG_NO_MPART_ALL_SIZE
#define _mpart_all_getsize() \
	LIST_COUNT(&mpart_all_list, mp_allparts)
#define mpart_all_getsize()                                   \
	({                                                        \
		size_t __mac_res;                                     \
		mpart_all_acquire();                                  \
		LIST_COUNT(&mpart_all_list, &__mac_res, mp_allparts); \
		mpart_all_release();                                  \
		__mac_res;                                            \
	})
#else /* CONFIG_NO_MPART_ALL_SIZE */
#define _mpart_all_getsize() ((size_t)mpart_all_size)
#define mpart_all_getsize()  __hybrid_atomic_load(&mpart_all_size, __ATOMIC_ACQUIRE)
#endif /* !CONFIG_NO_MPART_ALL_SIZE */


/* [0..n][lock(ATOMIC)] List of lock-ops for `mpart_all_list' */
DATDEF struct lockop_slist mpart_all_lops;

/* Add the given mpart `self'  to the global list of  parts.
 * This function will initialize `self->mp_allparts', though
 * may do so asynchronously (meaning  that the part may  not
 * have  been added to  the all-parts list  yet, even if you
 * acquire a lock to said  list immediately after call  this
 * function) */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_all_list_insert)(struct mpart *__restrict self);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MPART_H */
