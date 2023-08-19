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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MNODE_H 1

#include <kernel/compiler.h>

#include <kernel/arch/paging.h> /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/sched/__preemption.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <asm/os/mman.h>

#ifdef __WANT_MNODE__mn_ilink
#include <hybrid/__assert.h>
#endif /* __WANT_MNODE__mn_ilink */

/* Values for `struct mnode::mn_flags' */
#define MNODE_F_NORMAL     0x00000000 /* Normal flags. */
#define MNODE_F_PEXEC      0x00000001 /* [lock(mn_mman->mm_lock)] Data can be executed. */
#define MNODE_F_PWRITE     0x00000002 /* [lock(mn_mman->mm_lock)] Data can be written. */
#define MNODE_F_PREAD      0x00000004 /* [lock(mn_mman->mm_lock)] Data can be read. */
/*efine MNODE_F_           0x00000008  * ... */
#define MNODE_F_PDENYWRITE 0x00000010 /* [lock(mn_mman->mm_lock)] mprotect(2) isn't allowed to turn on `MNODE_F_PWRITE'. */
#define MNODE_F_PMASK      0x00000017 /* Mask of basic protection flags. */
#define MNODE_F_SHARED     0x00000020 /* [lock(mn_mman->mm_lock || mn_part)]
                                       * Changes made by this memory mapping are shared.
                                       * When not set, attempting to write to this node will instead
                                       * replace `mn_part' with an identical, but anonymous copy:
                                       * >>     // Is the part accessible from its file?
                                       * >>     self->mn_part->mp_file->mf_parts != MFILE_PARTS_ANONYMOUS ||
                                       * >>
                                       * >>     // Is there some part that wants shared access to the part?
                                       * >>     !LIST_EMPTY(&self->mn_part->mp_share) ||
                                       * >>
                                       * >>     // Are there any other nodes with copy-on-write for this part?
                                       * >>     (LIST_FIRST(&self->mn_part->mp_copy) != self ||
                                       * >>      LIST_NEXT(self, mn_link) != NULL)
                                       * If any of these checks succeed, then `mn_part' is replaced with
                                       * the  required  private  copy, thus  allowing  for copy-on-write */
#define MNODE_F_UNMAPPED   0x00000040 /* [lock(mn_mman->mm_lock && WRITE_ONCE)] Set after the node got unmapped.
                                       * NOTE: You should never see this flag on any node still part of an mman's node-tree!
                                       *       However,  you  may see  it  when finding  nodes  via an  mpart's  node lists. */
#define MNODE_F_MPREPARED  0x00000080 /* [lock(mn_mman->mm_lock)]
                                       * For its entire lifetime, the backing page directory storage of this mem-node
                                       * is kept prepared. Note that this flag is _NOT_ inherited during fork()! As a
                                       * matter of fact: userspace isn't allowed to make use of this flag. */
#define MNODE_F_COREPART   0x00000100 /* [const] Core part (free this node using `mcoreheap_free()' instead of `kfree()') */
#define MNODE_F_KERNPART   0x00000200 /* [const] This node describes part of the static kernel core and must
                                       *         not be modified or removed (by conventional means). Attempting
                                       *         to do so anyways will result in kernel panic. */
/*efine MNODE_F_           0x00000400  * ... */
/*efine MNODE_F_           0x00000800  * ... */
#define MNODE_F_MHINT      0x00001000 /* [lock(CLEAR_ONCE)]
                                       * The page directory is set-up to hint towards this node, allowing it
                                       * to still be initialized lazily, but without the need to acquire any
                                       * sort of lock. For this, the following invariants are assumed:
                                       *  - ADDRRANGE_ISKERN(mnode_getaddr(this), mnode_getendaddr(this))
                                       *  - mn_mman == &mman_kernel
                                       *  - mn_part != NULL
                                       *  - mn_link.le_prev == &(mn_flags & MNODE_F_SHARED ? mn_part->mp_share : mn_part->mp_copy).lh_first
                                       *  - *mn_link.le_prev == this
                                       *  - mn_link.le_next == NULL
                                       *  - (mn_flags & MNODE_F_SHARED ? mn_part->mp_copy : mn_part->mp_share).lh_first == NULL
                                       *  - !isshared(mn_part) // Not strictly enforced, but assumed. - You are allowed to
                                       *                       // reference the part elsewhere, but you mustn't change it.
                                       *  - NOBLOCK(mn_part->mp_file->mf_ops->mo_loadblocks)
                                       *  - NOTHROW(mn_part->mp_file->mf_ops->mo_loadblocks)
                                       *  - mn_part->mp_file->mf_blockshift == PAGESHIFT
                                       *  - mn_part->mp_file->mf_parts == MFILE_PARTS_ANONYMOUS
                                       *  - MPART_ST_INMEM(mn_part->mp_state)
                                       * You may force  a node  to no longer  be hinted  by ensuring that  all of  its
                                       * pages have been accessed at least once (read-only access is enough for this),
                                       * and  (in  SMP-only)  waited until  `mman_kernel_hintinit_inuse'  became zero.
                                       * Afterwards, you may  clear this  flag. But also  note that  before then,  you
                                       * must also be aware of the fact that requirements imposed by `MNODE_F_NOSPLIT'
                                       * and `MNODE_F_NOMERGE' also apply to nodes that are hinted! */
#define MNODE_F_MLOCK      0x00002000 /* [lock(mn_part->MPART_F_LOCKBIT)] Lock backing memory (see `MPART_F_MLOCK' for how this flag works) */
#define MNODE_F__RBRED     0x00004000 /* [lock(mn_mman->mm_lock)] Internal flag: This node is red in the mman-mappings R/B tree. */
#define MBNODE_F_POPULATE  0x00008000 /* Used internally by `struct mbnode' */
#define MBNODE_F_NONBLOCK  0x00010000 /* Used internally by `struct mbnode' */
/*efine MNODE_F_           0x00020000  * ... */
#define MNODE_F_NOSPLIT    0x00040000 /* [const] Don't allow this mem-node to be split. */
#define MNODE_F_NOMERGE    0x00080000 /* [const] Don't allow this mem-node to be merged. When set, this flag
                                       *         guaranties that munmap() will _always_ succeed without ever
                                       *         resulting in an `E_BADALLOC' exception. */
/*efine MNODE_F_           0x00100000  * ... */
/*efine MNODE_F_           0x00200000  * ... */
/*efine MNODE_F_           0x00400000  * ... */
/*efine MNODE_F_           0x00800000  * ... */
#define MNODE_F_NOCORE     0x01000000 /* [lock(mn_mman->mm_lock)] Don't include in coredumps. */
/*efine MNODE_F_           0x01000000  * ... */
/*efine MNODE_F_           0x02000000  * ... */
/*efine MNODE_F_           0x04000000  * ... */
/*efine MNODE_F_           0x08000000  * ... */
/*efine MNODE_F_           0x10000000  * ... */
/*efine MNODE_F_           0x20000000  * ... */
/*efine MNODE_F_           0x40000000  * ... */
#define MNODE_F__REACH     0x80000000 /* Used internally by the memory leak detector. */


/* Expand to `MNODE_F_MPREPARED' if kernel-space is automatically prepared.
 * Otherwise,  expand  to  `0'.  May   be  used  by  static   initializers. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
#define _MNODE_F_MPREPARED_KERNEL 0
#else /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
#define _MNODE_F_MPREPARED_KERNEL MNODE_F_MPREPARED
#endif /* !ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */


/* `struct mnode' offsets */
#define OFFSET_MNODE_MEMENT     0
#define OFFSET_MNODE_MEMENT_PAR 0
#define OFFSET_MNODE_MEMENT_LHS __SIZEOF_POINTER__
#define OFFSET_MNODE_MEMENT_RHS (__SIZEOF_POINTER__ * 2)
#ifdef __WANT_MNODE__mn_dead
#define OFFSET_MNODE__DEAD 0
#endif /* __WANT_MNODE__mn_dead */
#define OFFSET_MNODE_MINADDR (__SIZEOF_POINTER__ * 3)
#define OFFSET_MNODE_MAXADDR (__SIZEOF_POINTER__ * 4)
#define OFFSET_MNODE_FLAGS   (__SIZEOF_POINTER__ * 5)
#define OFFSET_MNODE_PART    (__SIZEOF_POINTER__ * 6)
#define OFFSET_MNODE_FSPATH  (__SIZEOF_POINTER__ * 7)
#define OFFSET_MNODE_FSNAME  (__SIZEOF_POINTER__ * 8)
#define OFFSET_MNODE_MMAN    (__SIZEOF_POINTER__ * 9)
#ifdef __WANT_MNODE__mn_alloc
#define OFFSET_MNODE__ALLOC (__SIZEOF_POINTER__ * 9)
#endif /* __WANT_MNODE__mn_alloc */
#define OFFSET_MNODE_PARTOFF       (__SIZEOF_POINTER__ * 10)
#define OFFSET_MNODE_LINK          (__SIZEOF_POINTER__ * 11)
#define OFFSET_MNODE_LINK_NEXT     (__SIZEOF_POINTER__ * 11)
#define OFFSET_MNODE_LINK_PREV     (__SIZEOF_POINTER__ * 12)
#define OFFSET_MNODE_WRITABLE      (__SIZEOF_POINTER__ * 13)
#define OFFSET_MNODE_WRITABLE_NEXT (__SIZEOF_POINTER__ * 13)
#define OFFSET_MNODE_WRITABLE_PREV (__SIZEOF_POINTER__ * 14)
#ifdef __WANT_MNODE__mn_ilink
#define OFFSET_MNODE__ISWRITABLE   (__SIZEOF_POINTER__ * 13)
#define OFFSET_MNODE__ILINK        (__SIZEOF_POINTER__ * 14)
#endif /* __WANT_MNODE__mn_ilink */
#define OFFSET_MNODE_MODULE (__SIZEOF_POINTER__ * 15)
#define SIZEOF_MNODE        (__SIZEOF_POINTER__ * 16)
#define ALIGNOF_MNODE       __ALIGNOF_POINTER__

#ifdef __CC__
DECL_BEGIN

struct mpart; /* Memory file part. */
struct mnode; /* Memory range descriptor. */
struct mman;  /* Memory manager. */

struct path;
struct fdirent;

#ifndef __mpart_reladdr_t_defined
#define __mpart_reladdr_t_defined
typedef size_t mpart_reladdr_t;
#endif /* !__mpart_reladdr_t_defined */

#define __ALIGNOF_MNODE __SIZEOF_POINTER__
#if __SIZEOF_POINTER__ == 4
#define __SIZEOF_MNODE 64
#elif __SIZEOF_POINTER__ == 8
#define __SIZEOF_MNODE 128
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported pointer size"
#endif /* __SIZEOF_POINTER__ != ... */

#if 0 /* Static initializer template: */
//	MNODE_INIT_mn_mement({}),
//	MNODE_INIT_mn_minaddr(FILL_ME),
//	MNODE_INIT_mn_maxaddr(FILL_ME - 1),
//	MNODE_INIT_mn_flags(MNODE_F_PWRITE | MNODE_F_PREAD |
//	                    MNODE_F_SHARED    |    MNODE_F_NOSPLIT    |
//	                    MNODE_F_NOMERGE   |   MNODE_F_KERNPART    |
//	                    _MNODE_F_MPREPARED_KERNEL | MNODE_F_MLOCK),
//	MNODE_INIT_mn_part(FILL_ME),
//	MNODE_INIT_mn_fspath(NULL),
//	MNODE_INIT_mn_fsname(NULL),
//	MNODE_INIT_mn_mman(&mman_kernel),
//	MNODE_INIT_mn_partoff(0),
//	MNODE_INIT_mn_link({ NULL, FILL_ME }),
//	MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),
//	MNODE_INIT_mn_module(NULL)
#endif

struct module;
struct mnode {
	/* WARNING: Because  mem-nodes  aren't reference  counter, they  are always
	 *          implicitly owned by the associated  mman, such that you  really
	 *          need to be holding a lock to that mman (or some other lock that
	 *          will prevent the node from being  destroyed, such as a lock  to
	 *          the part that is being mapped), else you have no guaranty  that
	 *          the node won't just be free'd, and you'll end up accessing dead
	 *          memory! */
#ifdef __INTELLISENSE__
	typedef RBTREE_NODE(mnode) _rbtree_node_mnode;
	typedef SLIST_ENTRY(mnode) _slist_entry_mnode;
	typedef LIST_ENTRY(mnode) _list_entry_mnode;
#ifdef __WANT_MNODE__mn_dead
	union {
		_rbtree_node_mnode              mn_mement;   /* [lock(mn_mman->mm_lock)] R/B tree entry of mman mappings. */
		_slist_entry_mnode             _mn_dead;     /* [lock(ATOMIC)] Internal chain of dead nodes */
	};
#else /* __WANT_MNODE__mn_dead */
	_rbtree_node_mnode                  mn_mement;   /* [lock(mn_mman->mm_lock)] R/B tree entry of mman mappings. */
#endif /* !__WANT_MNODE__mn_dead */
	VIRT/*PAGEDIR_PAGEALIGNED */byte_t *mn_minaddr;  /* [const] Lowest address mapped by this node. */
	VIRT byte_t                        *mn_maxaddr;  /* [const] Greatest address mapped by this node. (+1, and it's `PAGEDIR_PAGEALIGNED') */
	uintptr_t                           mn_flags;    /* mem-node flags (Set of `MNODE_F_*') */
	/*REF*/ struct mpart               *mn_part;     /* [0..1][const][valid_if(!MNODE_F_UNMAPPED && !wasdestroyed(mn_mman))]
	                                                  * The bound mem-part. When set to NULL, then this node represents a reserved node. */
	/*REF*/ struct path                *mn_fspath;   /* [0..1][const] Optional mapping path (only used for memory->disk mapping listings) */
	/*REF*/ struct fdirent             *mn_fsname;   /* [0..1][const] Optional mapping name (only used for memory->disk mapping listings) */
#ifdef __WANT_MNODE__mn_alloc
	union {
		/*WEAK REF*/ struct mman       *mn_mman;     /* [1..1][const] Associated memory manager.
		                                              * NOTE: This only becomes a weak reference when `wasdestroyed(self->mn_mman)' is true,
		                                              *       and  the node  has to be  inserted into the  associated part's dead-node-list.
		                                              *       Unless this has happened, this is just a regular, old pointer! */
		_slist_entry_mnode             _mn_alloc;    /* Internal list of freshly allocated nodes. */
	};
#else /* __WANT_MNODE__mn_alloc */
	/*WEAK REF*/ struct mman           *mn_mman;     /* [1..1][const] Associated memory manager.
	                                                  * NOTE: This only becomes a weak reference when `wasdestroyed(self->mn_mman)' is true,
	                                                  *       and  the node  has to be  inserted into the  associated part's dead-node-list.
	                                                  *       Unless this has happened, this is just a regular, old pointer! */
#endif /* !__WANT_MNODE__mn_alloc */
	/*PAGEDIR_PAGEALIGNED*/ mpart_reladdr_t
	                                    mn_partoff;  /* [lock(mn_mman->mm_lock)][valid_if(mn_part)] Offset into `mn_part', to where the maping starts. */
	_list_entry_mnode                   mn_link;     /* [lock(mn_part->MPART_F_LOCKBIT)][valid_if(mn_part)] Entry for `mp_copy' or `mp_share' */
#ifdef __WANT_MNODE__mn_ilink
	union {
		_list_entry_mnode               mn_writable; /* [lock(mn_mman->mm_lock)][valid_if(mn_part)]  Chain  of nodes  that (may)
		                                              * contain pages that  are current mapped  with write-access enabled.  This
		                                              * list is used to speed up the clearing of write-access of modified memory
		                                              * mappings when copying  a memory  manager as  part of  fork(2). For  this
		                                              * purpose, this list contains all memory nodes that request  write-access,
		                                              * and have actually been mapped  with write-access enabled (which  happens
		                                              * lazily upon first access).
		                                              * Nodes  are  removed  from this  list  by `mnode_clear_write(_locked)'.
		                                              * NOTE: This entry left as UNBOUND until the node is mapped as writable. */
		struct {
			void                      *_mn_iswritable; /* [0..1] Non-NULL if `mn_writable' is meant to be bound. */
			_slist_entry_mnode         _mn_ilink;    /* Internal link pointer. */
		};
	};
#else /* __WANT_MNODE__mn_ilink */
	_list_entry_mnode                   mn_writable; /* [lock(mn_mman->mm_lock)][valid_if(mn_part)]  Chain  of nodes  that (may)
	                                                  * contain pages that  are current mapped  with write-access enabled.  This
	                                                  * list is used to speed up the clearing of write-access of modified memory
	                                                  * mappings when copying  a memory  manager as  part of  fork(2). For  this
	                                                  * purpose, this list contains all memory nodes that request  write-access,
	                                                  * and have actually been mapped  with write-access enabled (which  happens
	                                                  * lazily upon first access).
	                                                  * Nodes  are  removed  from this  list  by `mnode_clear_write(_locked)'.
	                                                  * NOTE: This entry left as UNBOUND until the node is mapped as writable. */
#endif /* !__WANT_MNODE__mn_ilink */
#else /* __INTELLISENSE__ */
#ifdef __WANT_MNODE__mn_dead
	union {
		RBTREE_NODE(mnode)              mn_mement;   /* [lock(mn_mman->mm_lock)] R/B tree entry of mman mappings. */
		SLIST_ENTRY(mnode)             _mn_dead;     /* [lock(ATOMIC)] Internal chain of dead nodes */
	};
#else /* __WANT_MNODE__mn_dead */
	RBTREE_NODE(mnode)                  mn_mement;   /* [lock(mn_mman->mm_lock)] R/B tree entry of mman mappings. */
#endif /* !__WANT_MNODE__mn_dead */
	VIRT PAGEDIR_PAGEALIGNED byte_t    *mn_minaddr;  /* [const] Lowest address mapped by this node. */
	VIRT byte_t                        *mn_maxaddr;  /* [const] Greatest address mapped by this node. (+1, and it's `PAGEDIR_PAGEALIGNED') */
	uintptr_t                           mn_flags;    /* mem-node flags (Set of `MNODE_F_*') */
	REF struct mpart                   *mn_part;     /* [0..1][const][valid_if(!MNODE_F_UNMAPPED && !wasdestroyed(mn_mman))]
	                                                  * The bound mem-part. When set to NULL, then this node represents a reserved node. */
	REF struct path                    *mn_fspath;   /* [0..1][const] Optional mapping path (only used for memory->disk mapping listings) */
	REF struct fdirent                 *mn_fsname;   /* [0..1][const] Optional mapping name (only used for memory->disk mapping listings) */
#ifdef __WANT_MNODE__mn_alloc
	union {
		WEAK REF struct mman           *mn_mman;     /* [1..1][const] Associated memory manager.
		                                              * NOTE: This only becomes a weak reference when `wasdestroyed(self->mn_mman)' is true,
		                                              *       and  the node  has to be  inserted into the  associated part's dead-node-list.
		                                              *       Unless this has happened, this is just a regular, old pointer! */
		SLIST_ENTRY(mnode)             _mn_alloc;    /* Internal list of freshly allocated nodes. */
	};
#else /* __WANT_MNODE__mn_alloc */
	WEAK REF struct mman               *mn_mman;     /* [1..1][const] Associated memory manager.
	                                                  * NOTE: This only becomes a weak reference when `wasdestroyed(self->mn_mman)' is true,
	                                                  *       and  the node  has to be  inserted into the  associated part's dead-node-list.
	                                                  *       Unless this has happened, this is just a regular, old pointer! */
#endif /* !__WANT_MNODE__mn_alloc */
	PAGEDIR_PAGEALIGNED mpart_reladdr_t mn_partoff;  /* [lock(mn_mman->mm_lock)][valid_if(mn_part)] Offset into `mn_part', to where the maping starts. */
	LIST_ENTRY(mnode)                   mn_link;     /* [lock(mn_part->MPART_F_LOCKBIT)][valid_if(mn_part)] Entry for `mp_copy' or `mp_share' */
#ifdef __WANT_MNODE__mn_ilink
	union {
		LIST_ENTRY(mnode)               mn_writable; /* [lock(mn_mman->mm_lock)][valid_if(mn_part)]  Chain  of nodes  that (may)
		                                              * contain pages that  are current mapped  with write-access enabled.  This
		                                              * list is used to speed up the clearing of write-access of modified memory
		                                              * mappings when copying  a memory  manager as  part of  fork(2). For  this
		                                              * purpose, this list contains all memory nodes that request  write-access,
		                                              * and have actually been mapped  with write-access enabled (which  happens
		                                              * lazily upon first access).
		                                              * Nodes  are  removed  from this  list  by `mnode_clear_write(_locked)'.
		                                              * NOTE: This entry left as UNBOUND until the node is mapped as writable. */
		struct {
			void                      *_mn_iswritable; /* [0..1] Non-NULL if `mn_writable' is meant to be bound. */
			SLIST_ENTRY(mnode)         _mn_ilink;    /* Internal link pointer. */
		};
	};
#else /* __WANT_MNODE__mn_ilink */
	LIST_ENTRY(mnode)                   mn_writable; /* [lock(mn_mman->mm_lock)][valid_if(mn_part)]  Chain  of nodes  that (may)
	                                                  * contain pages that  are current mapped  with write-access enabled.  This
	                                                  * list is used to speed up the clearing of write-access of modified memory
	                                                  * mappings when copying  a memory  manager as  part of  fork(2). For  this
	                                                  * purpose, this list contains all memory nodes that request  write-access,
	                                                  * and have actually been mapped  with write-access enabled (which  happens
	                                                  * lazily upon first access).
	                                                  * Nodes  are  removed  from this  list  by `mnode_clear_write(_locked)'.
	                                                  * NOTE: This entry left as UNBOUND until the node is mapped as writable. */
#endif /* !__WANT_MNODE__mn_ilink */
#endif /* !__INTELLISENSE__ */
	WEAK struct module                 *mn_module;   /* [0..1][lock(mn_mman->mm_lock)] Node executable module binding. (s.a. <kernel/mman/module.h>)
	                                                  * The  module pointed-to by this field is weak, in that the pointed-to object may have already
	                                                  * been destroyed. For this purpose,  the module actually getting  destroyed will result in  it
	                                                  * going over all nodes in its address range, and clearing all of its self-pointers. */
};

#ifdef __WANT_MNODE_INIT
#ifdef __WANT_MNODE__mn_dead
#define MNODE_INIT_mn_mement(...)         { __VA_ARGS__ }
#else /* __WANT_MNODE__mn_dead */
#define MNODE_INIT_mn_mement(...)         __VA_ARGS__
#endif /* !__WANT_MNODE__mn_dead */
#define MNODE_INIT_mn_minaddr(mn_minaddr) (byte_t *)(mn_minaddr)
#define MNODE_INIT_mn_maxaddr(mn_maxaddr) (byte_t *)(mn_maxaddr)
#define MNODE_INIT_mn_flags(mn_flags)     mn_flags
#define MNODE_INIT_mn_part(mn_part)       mn_part
#define MNODE_INIT_mn_fspath(mn_fspath)   mn_fspath
#define MNODE_INIT_mn_fsname(mn_fsname)   mn_fsname
#ifdef __WANT_MNODE__mn_alloc
#define MNODE_INIT_mn_mman(mn_mman)       { mn_mman }
#else /* __WANT_MNODE__mn_alloc */
#define MNODE_INIT_mn_mman(mn_mman)       mn_mman
#endif /* !__WANT_MNODE__mn_alloc */
#define MNODE_INIT_mn_partoff(mn_partoff) mn_partoff
#define MNODE_INIT_mn_link(...)           __VA_ARGS__
#ifdef __WANT_MNODE__mn_ilink
#define MNODE_INIT_mn_writable(...)       { __VA_ARGS__ }
#else /* __WANT_MNODE__mn_ilink */
#define MNODE_INIT_mn_writable(...)       __VA_ARGS__
#endif /* !__WANT_MNODE__mn_ilink */
#define MNODE_INIT_mn_module(mn_module)   mn_module
#endif /* __WANT_MNODE_INIT */



#ifdef __WANT_MPART__mp_nodlsts
/* Helper macro the return a pointer to the relevant mem-node list
 * head of a given mem-part,  given `mnodeflags' which may or  may
 * not include the `MNODE_F_SHARED' flag. */
#if MNODE_F_SHARED == 0x0001
#define mpart_getnodlst_from_mnodeflags(self, mnodeflags) (&(self)->_mp_nodlsts[(mnodeflags) & MNODE_F_SHARED])
#elif MNODE_F_SHARED == 0x0020
#define mpart_getnodlst_from_mnodeflags(self, mnodeflags) (&(self)->_mp_nodlsts[((mnodeflags) & MNODE_F_SHARED) >> 5])
#else /* MNODE_F_SHARED == ... */
#define mpart_getnodlst_from_mnodeflags(self, mnodeflags) ((mnodeflags) & MNODE_F_SHARED ? &(self)->mp_share : &(self)->mp_copy)
#endif /* MNODE_F_SHARED != ... */
#if __PROT_SHARED == 0x0001
#define mpart_getnodlst_from_prot(self, prot) (&(self)->_mp_nodlsts[(prot) & __PROT_SHARED])
#elif __PROT_SHARED == 0x0020
#define mpart_getnodlst_from_prot(self, prot) (&(self)->_mp_nodlsts[((prot) & __PROT_SHARED) >> 5])
#else /* __PROT_SHARED == ... */
#define mpart_getnodlst_from_prot(self, prot) ((prot) & __PROT_SHARED ? &(self)->mp_share : &(self)->mp_copy)
#endif /* __PROT_SHARED != ... */
#endif /* __WANT_MPART__mp_nodlsts */




/* Begin/end  allow free use of `_mn_ilink' of `self'.
 * The caller must be holding a lock to the associated
 * mman, which must not  be released before all  ilink
 * fields are deactivated via  `mnode_use_ilink_end()' */
#ifdef __WANT_MNODE__mn_ilink
#define mnode_use_ilink_begin(self)                                                                    \
	((self)->mn_writable.le_prev != __NULLPTR                                                          \
	 ? (void)((*(self)->mn_writable.le_prev = (self)->mn_writable.le_next) != __NULLPTR                \
	          ? (void)((self)->mn_writable.le_next->mn_writable.le_prev = (self)->mn_writable.le_prev) \
	          : (void)0)                                                                               \
	 : (void)0)
#define mnode_use_ilink_end(self)                                                                       \
	((self)->_mn_iswritable != __NULLPTR                                                                \
	 ? (void)(((self)->mn_writable.le_next = (self)->mn_mman->mm_writable.lh_first) != __NULLPTR        \
	          ? (void)(__hybrid_assert((self)->mn_writable.le_next->mn_writable.le_prev ==              \
	                                   &(self)->mn_mman->mm_writable.lh_first),                         \
	                   (self)->mn_writable.le_next->mn_writable.le_prev = &(self)->mn_writable.le_next) \
	          : (void)0,                                                                                \
	          *((self)->mn_writable.le_prev = &(self)->mn_mman->mm_writable.lh_first) = (self))         \
	 : (void)0)
#endif /* __WANT_MNODE__mn_ilink */




/* Return mem-node paging  permissions, irregardless of  copy-on-write
 * semantics. - That is: allow write whenever the node requests write,
 * no matter who else might also be using the underlying mem-part. */
#if (PAGEDIR_PROT_EXEC == MNODE_F_PEXEC && \
     PAGEDIR_PROT_READ == MNODE_F_PREAD && \
     PAGEDIR_PROT_WRITE == MNODE_F_PWRITE)
#define mnode_getperm_force(self) \
	((self)->mn_flags & (MNODE_F_PEXEC | MNODE_F_PREAD | MNODE_F_PWRITE))
#else /* ... */
#define mnode_getperm_force(self)                                   \
	((((self)->mn_flags & MNODE_F_PEXEC) ? PAGEDIR_PROT_EXEC : 0) | \
	 (((self)->mn_flags & MNODE_F_PREAD) ? PAGEDIR_PROT_READ : 0) | \
	 (((self)->mn_flags & MNODE_F_PWRITE) ? PAGEDIR_PROT_WRITE : 0))
#endif /* !... */

/* Get bounds for the given mem-node. */
#define mnode_getminaddr(self) ((void *)(self)->mn_minaddr)
#define mnode_getmaxaddr(self) ((void *)(self)->mn_maxaddr)
#define mnode_getendaddr(self) ((void *)((self)->mn_maxaddr + 1))
#define mnode_getaddr(self)    ((void *)(self)->mn_minaddr)
#define mnode_getsize(self)    ((size_t)((self)->mn_maxaddr - (self)->mn_minaddr) + 1)
#define mnode_iskern(self)     ADDRRANGE_ISKERN((self)->mn_minaddr, (self)->mn_maxaddr + 1)
#define mnode_isuser(self)     ADDRRANGE_ISUSER((self)->mn_minaddr, (self)->mn_maxaddr + 1)
#define mnode_containsaddr(self, addr)                     \
	((uintptr_t)(addr) >= (uintptr_t)(self)->mn_minaddr && \
	 (uintptr_t)(addr) <= (uintptr_t)(self)->mn_maxaddr)

/* Return the part-relative min-/max-address that is being mapped. */
#define mnode_getpartaddr(self)    ((mpart_reladdr_t)((self)->mn_partoff))
#define mnode_getpartminaddr(self) ((mpart_reladdr_t)((self)->mn_partoff))
#define mnode_getpartmaxaddr(self) ((mpart_reladdr_t)((self)->mn_partoff + ((size_t)((self)->mn_maxaddr - (self)->mn_minaddr))))
#define mnode_getpartendaddr(self) ((mpart_reladdr_t)((self)->mn_partoff + mnode_getsize(self)))
#define mnode_ismapping(self, partrel_minaddr, partrel_maxaddr) \
	((partrel_maxaddr) >= mnode_getpartminaddr(self) &&         \
	 (partrel_minaddr) <= mnode_getpartmaxaddr(self))

/* Return the file-absolute min-/max-address that is being mapped. (caller must ensure a non-NULL `mn_part') */
#define mnode_getfileaddr(self)    (mpart_getminaddr((self)->mn_part) + (self)->mn_partoff)
#define mnode_getfileminaddr(self) (mpart_getminaddr((self)->mn_part) + (self)->mn_partoff)
#define mnode_getfilemaxaddr(self) (mpart_getminaddr((self)->mn_part) + (self)->mn_partoff + (size_t)((self)->mn_maxaddr - (self)->mn_minaddr))
#define mnode_getfileendaddr(self) (mpart_getminaddr((self)->mn_part) + (self)->mn_partoff + (size_t)((self)->mn_maxaddr - (self)->mn_minaddr) + 1)

/* Return the file-absolute address mapped at `vaddr' */
#define mnode_getfileaddrat(self, vaddr) (mnode_getfileaddr(self) + ((byte_t *)(vaddr) - (self)->mn_minaddr))
#define mnode_getpartaddrat(self, vaddr) (mnode_getpartaddr(self) + ((byte_t *)(vaddr) - (self)->mn_minaddr))


/* Free/destroy a given mem-node */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mnode_free)(struct mnode *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mnode_destroy)(struct mnode *__restrict self);
#define mnode_xfree(self) (void)(!(self) || (mnode_free(self), 1))



/* Clear page-directory-level write-access to `self'. This function must  be
 * called for all writable memory mappings of a MMAN when the MMAN is cloned
 * or a copy-on-write  mapping is created  for an already-shared  `mn_part':
 * >> mmap() {
 * >>     ...
 * >>     if (flags & MNODE_F_SHARED) {
 * >>         ...
 * >>     } else {
 * >>         if (part->mp_copy == NULL) {
 * >>             LIST_FOREACH (node, &part->mp_share, mn_link) {
 * >>                 mnode_clear_write(node);
 * >>             }
 * >>         } else if (LIST_NEXT(part->mp_copy, mn_link) != NULL &&
 * >>                    mpart_isanon(part)) {
 * >>             // This is what would happen during a fork()
 * >>             mnode_clear_write(part->mp_copy);
 * >>         }
 * >>     }
 * >> }
 * NOTE: This function is designed to be called while the caller is
 *       already holding a lock to the node's associated  mem-part.
 * @return: * : One of `MNODE_CLEAR_WRITE_*' */
FUNDEF NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write)(struct mnode *__restrict self);
#define MNODE_CLEAR_WRITE_SUCCESS    0 /* Success (or no-op when `self' wasn't mapped with write-access, or the associated mman was destroyed) */
#define MNODE_CLEAR_WRITE_WOULDBLOCK 1 /* ERROR: The operation would have blocked (The caller must blocking-wait for `mman_lock_canwrite(self->mmn_mman)') */
#define MNODE_CLEAR_WRITE_BADALLOC   2 /* ERROR: Failed to prepare the underlying page directory for making modifications to the associated mapping. */

/* Same as `mnode_clear_write', but the caller is already holding a lock to `mm',
 * and  this  function  will  never  return  with `MNODE_CLEAR_WRITE_WOULDBLOCK'.
 * NOTE: Unlike with `mnode_clear_write', when calling this function,
 *       the caller must ensure that:
 *        - !wasdestroyed(mm)
 *        - mman_lock_acquired(mm)
 *        - self->mn_part != NULL
 *        - LIST_ISBOUND(self, mn_writable)
 * Also note that the caller is responsible to sync `mm' before unlocking it! */
FUNDEF NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked_p)(struct mnode *__restrict self,
                                          struct mman *__restrict mm);

/* Same as  `mnode_clear_write_locked_p()',  but  directly
 * operate on the current page directory / memory manager. */
FUNDEF NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked)(struct mnode *__restrict self);

/* Split `lonode' (which contains `addr_where_to_split') at that address.  If
 * this cannot be done without blocking, unlock and eventually return `false' */
FUNDEF WUNUSED NONNULL((1, 2)) __BOOL FCALL
mnode_split_or_unlock(struct mman *__restrict self,
                      struct mnode *__restrict lonode,
                      PAGEDIR_PAGEALIGNED void const *addr_where_to_split,
                      struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* While  holding a lock  to `self->mn_mman', try to  merge the given node
 * with its successor/predecessor node, without releasing the lock to  the
 * associated mman. If it is found that `self' is mergeable, but that this
 * cannot be done  without blocking, `self->mn_mman'  is set-up such  that
 * the merge operation will be performed asynchronously.
 * @return: * : The new, merged node (which may have a different min-addr
 *              that the original node `self'). Also note that this  node
 *              may or may not be equal to `self', and that it's min- and
 *              max-addr fields may be  different from those that  `self'
 *              had upon entry, irregardless of `self' being re-returned.
 *              As  a matter of fact `*self' becomes invalid after a call
 *              to this function! */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge)(struct mnode *__restrict self);

/* Same as `mnode_merge()', but the  caller must also be holding  a
 * lock to `self->mn_part' (which may  be assumed to be  non-NULL).
 * Upon return, the lock to `self->mn_part' may have been released,
 * because of which case the caller  must alway inherits a lock  to
 * `return->mn_part'. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge_with_partlock)(struct mnode *__restrict self);


/* Mark the given mman as potentially containing mergeable  mem-nodes.
 * These nodes will (eventually) be merged asynchronously, but may not
 * be merged immediately (though they might be merged immediately).
 * NOTE: The caller isn't required to be holding a lock to `self', but
 *       if they are, this function is still going to be non-blocking,
 *       and the node-merging process  will simply happen _after_  the
 *       caller releases their lock. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes)(struct mman *__restrict self);

/* Same as `mman_mergenodes()', but the caller _must_ be holding a lock
 * to the given mman `self'! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes_locked)(struct mman *__restrict self);

/* Helper wrapper to try to merge all nodes within the given range. The
 * caller must be holding a lock to `self' when calling this  function. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_mergenodes_inrange)(struct mman *__restrict self,
                                       void const *minaddr,
                                       void const *maxaddr);


struct mpart_trim_data;

/* Apply a given `advise' to `self' and return `true', or release a
 * lock to `self->mn_mman' and return `false' (in which case `data'
 * may have been modified)
 * @param: advice: The advice to apply (one of `MADV_*', except `MADV_POPULATE_*')
 *                 Unsupported advices are silently ignored.
 * @return: true:  Success (locks are still held)
 * @return: false: Error (locks were released)
 * @THROW: Error (locks were released) */
FUNDEF WUNUSED NONNULL((1, 2)) bool FCALL
mnode_advise_or_unlock(struct mnode *__restrict self,
                       struct mpart_trim_data *__restrict data,
                       unsigned int advice)
		THROWS(E_BADALLOC);



/* Helper structure for `mnode_tree_minmaxlocate()' */
struct mnode_tree_minmax {
	struct mnode *mm_min; /* [0..1] Lowest branch. */
	struct mnode *mm_max; /* [0..1] Greatest branch. */
};

/* Mem-node tree API. All of these functions require that
 * the caller be holding a  lock to the associated  mman. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mnode *NOTHROW(FCALL mnode_tree_locate)(/*nullable*/ struct mnode *root, VIRT void const *key);
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mnode *NOTHROW(FCALL mnode_tree_rlocate)(/*nullable*/ struct mnode *root, VIRT void const *minkey, VIRT void const *maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mnode_tree_insert)(struct mnode **__restrict proot, struct mnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL mnode_tree_tryinsert)(struct mnode **__restrict proot, struct mnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_remove)(struct mnode **__restrict proot, VIRT void const *key);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_rremove)(struct mnode **__restrict proot, VIRT void const *minkey, VIRT void const *maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mnode_tree_removenode)(struct mnode **__restrict proot, struct mnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_prevnode)(struct mnode const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_nextnode)(struct mnode const *__restrict self);
FUNDEF NOBLOCK NONNULL((4)) void NOTHROW(FCALL mnode_tree_minmaxlocate)(struct mnode *root, VIRT void const *minkey, VIRT void const *maxkey, struct mnode_tree_minmax *__restrict result);

/* Helper macros for operating on the mappings tree of a given mman. */
#define mman_mappings_locate(self, key)                          mnode_tree_locate((self)->mm_mappings, key)
#define mman_mappings_rlocate(self, minkey, maxkey)              mnode_tree_rlocate((self)->mm_mappings, minkey, maxkey)
#define mman_mappings_insert(self, node)                         mnode_tree_insert(&(self)->mm_mappings, node)
#define mman_mappings_tryinsert(self, node)                      mnode_tree_tryinsert(&(self)->mm_mappings, node)
#define mman_mappings_remove(self, key)                          mnode_tree_remove(&(self)->mm_mappings, key)
#define mman_mappings_rremove(self, minkey, maxkey)              mnode_tree_rremove(&(self)->mm_mappings, minkey, maxkey)
#define mman_mappings_removenode(self, node)                     mnode_tree_removenode(&(self)->mm_mappings, node)
#define mman_mappings_minmaxlocate(self, minkey, maxkey, result) mnode_tree_minmaxlocate((self)->mm_mappings, minkey, maxkey, result)


/* A special per-MMAN node that is  used to cover the kernel  core
 * with a reservation within user-space memory manager. Within the
 * kernel mman itself, this field is undefined. */
DATDEF ATTR_PERMMAN struct mnode thismman_kernel_reservation;


#ifndef CONFIG_NO_SMP
/* Atomic counter for how many CPUs are currently initializing hinted pages (s.a. `MNODE_F_MHINT').
 * This counter behaves similar to the in-use counter found in <kos/aref.h>, and is needed in order
 * to  allow for syncing  of internal re-trace operations  in `mman_unmap_kram_locked()' with other
 * CPUs having previously started initializing hinted pages.
 *
 * For more information on the data race solved by this counter, see the detailed explanation
 * of `mman_kernel_hintinit_inuse' within `mman_unmap_kram_locked()' */
DATDEF WEAK unsigned int mman_kernel_hintinit_inuse;
#define mman_kernel_hintinit_inuse_inc() __hybrid_atomic_inc(&mman_kernel_hintinit_inuse, __ATOMIC_ACQUIRE)
#define mman_kernel_hintinit_inuse_dec() __hybrid_atomic_dec(&mman_kernel_hintinit_inuse, __ATOMIC_RELEASE)
#define mman_kernel_hintinit_inuse_waitfor()                     \
	do {                                                         \
		while (__hybrid_atomic_load(&mman_kernel_hintinit_inuse, \
		                            __ATOMIC_ACQUIRE) != 0)      \
			__hybrid_preemption_tryyield_nopr();                 \
	}	__WHILE0
#else /* !CONFIG_NO_SMP */
#define mman_kernel_hintinit_inuse_inc()     (void)0
#define mman_kernel_hintinit_inuse_dec()     (void)0
#define mman_kernel_hintinit_inuse_waitfor() (void)0
#endif /* CONFIG_NO_SMP */


/* Helper macros to perform pagedir_* operations on the address range of a given `mnode' */
#define mnode_pagedir_kernelprepare(self)              pagedir_kernelprepare(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_kernelunprepare(self)            pagedir_kernelunprepare(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_prepare(self)                    pagedir_prepare(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_unprepare(self)                  pagedir_unprepare(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_maphint(self, hint)              pagedir_maphint(mnode_getaddr(self), mnode_getsize(self), hint)
#define mnode_pagedir_map(self, phys, perm)            pagedir_map(mnode_getaddr(self), mnode_getsize(self), phys, perm)
#define mnode_pagedir_unmap(self)                      pagedir_unmap(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_denywrite(self)                  pagedir_denywrite(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_sync(self)                       pagedir_sync(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_sync_smp(self)                   pagedir_sync_smp(mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_prepare_p(pagedir, self)         pagedir_prepare_p(pagedir, mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_unprepare_p(pagedir, self)       pagedir_unprepare_p(pagedir, mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_maphint_p(pagedir, self, hint)   pagedir_maphint_p(pagedir, mnode_getaddr(self), mnode_getsize(self), hint)
#define mnode_pagedir_map_p(pagedir, self, phys, perm) pagedir_map_p(pagedir, mnode_getaddr(self), mnode_getsize(self), phys, perm)
#define mnode_pagedir_unmap_p(pagedir, self)           pagedir_unmap_p(pagedir, mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_denywrite_p(pagedir, self)       pagedir_denywrite_p(pagedir, mnode_getaddr(self), mnode_getsize(self))
#define mnode_pagedir_sync_smp_p(pagedir, self)        pagedir_sync_smp_p(pagedir, mnode_getaddr(self), mnode_getsize(self))
#define mnode_mman_sync(self)                          mman_sync(mnode_getaddr(self), mnode_getsize(self))
#define mnode_mman_sync_p(self)                        mman_sync_p((self)->mn_mman, mnode_getaddr(self), mnode_getsize(self))
#define mnode_mman_supersync(self)                     mman_supersync(mnode_getaddr(self), mnode_getsize(self))


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MNODE_H */
