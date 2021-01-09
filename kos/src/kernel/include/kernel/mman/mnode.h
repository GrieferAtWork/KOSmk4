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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MNODE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <kernel/paging.h>

/* Values for `struct mnode::mn_flags' */
#define MNODE_F_NORMAL   0x0000 /* Normal flags. */
#define MNODE_F_PEXEC    0x0001 /* Data can be executed. */
#define MNODE_F_PWRITE   0x0002 /* Data can be written. */
#define MNODE_F_PREAD    0x0004 /* Data can be read. */
#define MNODE_F_SHARED   0x0020 /* Changes made by this memory mapping are shared.
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
                                 * the required private copy, thus allowing for copy-on-write */
#define MNODE_F_MLOCK    0x0100 /* [lock(mn_part->MPART_F_LOCKBIT)] Lock backing memory (see `MPART_F_MLOCK' for how this flag works) */
#define MNODE_F_NO_SPLIT 0x1000 /* [const] Don't allow this mem-node to be split. */
#define MNODE_F_NO_MERGE 0x2000 /* [const] Don't allow this mem-node to be merged. When set, this flag
                                 *         guaranties that munmap() will _always_ succeed without ever
                                 *         resulting in an `E_BADALLOC' exception. */
#define MNODE_F_COREPART 0x4000 /* [const] Core part (affects how this mnode is freed) */
#define MNODE_F__RBRED   0x8000 /* [lock(mn_mman->mm_lock)] Internal flag: This part is a red node. */

#ifdef __CC__
DECL_BEGIN

struct mpart; /* Memory file part. */
struct mnode; /* Memory range descriptor. */
struct mman;  /* Memory manager. */

struct path;
struct directory_entry;

#ifndef __mpart_reladdr_t_defined
#define __mpart_reladdr_t_defined 1
typedef size_t mpart_reladdr_t;
#endif /* !__mpart_reladdr_t_defined */

struct mnode {
	/* WARNING: Because mem-nodes aren't reference counter, they are always
	 *          implicitly owned by the associated mman, such that you really
	 *          need to be holding a lock to that mman (or some other lock that
	 *          will prevent the node from being destroyed, such as a lock to
	 *          the part that is being mapped), else you have no guaranty that
	 *          the node won't just be free'd, and you'll end up accessing dead
	 *          memory! */
	union {
		SLIST_ENTRY(mnode)             _mn_alloc;    /* Internal list of freshly allocated nodes. */
		uintptr_t                       mn_flags;    /* mem-node flags (Set of `MNODE_F_*') */
	};
	byte_t                             *mn_minaddr;  /* [const] Lowest address mapped by this node. */
	byte_t                             *mn_maxaddr;  /* [const] Greatest address mapped by this node. */
	union {
		SLIST_ENTRY(mnode)             _mn_dead;     /* [lock(ATOMIC)] Chain of dead nodes (for use with `struct mpart::mp_deadnodes') */
		RBTREE_NODE(struct mnode)       mn_mement;   /* [lock(mn_mman->mm_lock)] R/B tree entry of mman mappings. */
	};
	WEAK REF struct mman               *mn_mman;     /* [1..1][const] Associated memory manager.
	                                                  * NOTE: This only becomes a weak reference when `mnode_wasdestroyed(self)' is true!
	                                                  *       Before that point, this is just a regular, old pointer! */
	REF struct mpart                   *mn_part;     /* [0..1][const] The bound mem-part.
	                                                  * When set to NULL, then this node represents a reserved node. */
	PAGEDIR_PAGEALIGNED mpart_reladdr_t mn_partoff;  /* [lock(mn_mman->mm_lock)] Offset into `mn_part', to where the maping starts. */
	LIST_ENTRY(mnode)                   mn_link;     /* [lock(mn_part->MPART_F_LOCKBIT)] Entry for `mp_copy' or `mp_share' */
	LIST_ENTRY(mnode)                   mn_writable; /* [lock(mn_mman->mm_lock)] Chain of nodes that (may) contain pages that
	                                                  * are current mapped with write-access enabled. This list is used to speed
	                                                  * up the clearing of write-access of modified memory mappings when copying
	                                                  * a memory manager as part of fork(2). For this purpose, this list contains
	                                                  * all memory nodes that request write-access, and have actually been mapped
	                                                  * with write-access enabled (which happens lazily upon first access)
	                                                  * Nodes are removed from this list by `mnode_clear_write(_locked)'.
	                                                  * NOTE: This entry left as UNBOUND until the node is mapped as writable. */
	REF struct path                    *mn_fspath;   /* [0..1][const] Optional mapping path (only used for memory->disk mapping listings) */
	REF struct directory_entry         *mn_fsname;   /* [0..1][const] Optional mapping name (only used for memory->disk mapping listings) */
};

/* Check if the given mem-node was destroyed. */
#define mnode_wasdestroyed(self) wasdestroyed((self)->mn_mman)

#if (PAGEDIR_MAP_FEXEC == MNODE_F_PEXEC && \
     PAGEDIR_MAP_FREAD == MNODE_F_PREAD && \
     PAGEDIR_MAP_FWRITE == MNODE_F_PWRITE)
#define mnode_getperm(self)                                                  \
	(((self)->mn_flags & (MNODE_F_PEXEC | MNODE_F_PREAD | MNODE_F_PWRITE)) | \
	 (ADDR_ISUSER(mnode_getmaxaddr(self)) ? PAGEDIR_MAP_FUSER : 0))
#else
#error TODO
#endif

/* Get bounds for the given mem-node. */
#define mnode_getminaddr(self) ((void *)(self)->mn_minaddr)
#define mnode_getmaxaddr(self) ((void *)(self)->mn_maxaddr)
#define mnode_getendaddr(self) ((void *)((self)->mn_maxaddr + 1))
#define mnode_getaddr(self)    ((void *)(self)->mn_minaddr)
#define mnode_getsize(self)    ((size_t)((self)->mn_maxaddr - (self)->mn_minaddr) + 1)
#define mnode_iskern(self)     ADDR_ISKERN((self)->mn_minaddr)
#define mnode_isuser(self)     ADDR_ISUSER((self)->mn_minaddr)
/* Return the part-relative min-/max-address that is being mapped. */
#define mnode_getmapminaddr(self) ((mpart_reladdr_t)((self)->mn_partoff))
#define mnode_getmapmaxaddr(self) ((mpart_reladdr_t)((self)->mn_partoff + ((size_t)((self)->mn_maxaddr - (self)->mn_minaddr))))
#define mnode_getmapendaddr(self) ((mpart_reladdr_t)((self)->mn_partoff + mnode_getsize(self)))


/* Free/destroy a given mem-node */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mnode_free)(struct mnode *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mnode_destroy)(struct mnode *__restrict self);



/* Clear page-directory-level write-access to `self'. This function must be
 * called for all writable memory mappings of a MMAN when the MMAN is cloned or
 * a copy-on-write mapping is created for an already-shared `mn_part':
 * >> mmap() {
 * >>     ...
 * >>     if (flags & MNODE_F_SHARED) {
 * >>         ...
 * >>     } else {
 * >>         if (part->mp_copy == NULL) {
 * >>             LIST_FOREACH(node, &part->mp_share, mn_link) {
 * >>                 mnode_clear_write(node);
 * >>             }
 * >>         } else if (LIST_NEXT(part->mp_copy, mn_link) != NULL &&
 * >>                    mfile_isanon(file)) {
 * >>             // This is what would happen during a fork()
 * >>             mnode_clear_write(part->mp_copy);
 * >>         }
 * >>     }
 * >> }
 * NOTE: This function is designed to be called while the caller is already
 *       holding a lock to the node's associated mem-part.
 * @return: * : One of `MNODE_CLEAR_WRITE_*' */
FUNDEF NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write)(struct mnode *__restrict self);
#define MNODE_CLEAR_WRITE_SUCCESS    0 /* Success (or no-op when `self' wasn't mapped with write-access, or the associated mman was destroyed) */
#define MNODE_CLEAR_WRITE_WOULDBLOCK 1 /* ERROR: The operation would have blocked (The caller must blocking-wait for `sync_write(self->mmn_mman)') */
#define MNODE_CLEAR_WRITE_BADALLOC   2 /* ERROR: Failed to prepare the underlying page directory for making modifications to the associated mapping. */

/* Same as `mnode_clear_write', but the caller is already holding a lock to `mm',
 * and this function will never return with `MNODE_CLEAR_WRITE_WOULDBLOCK'.
 * NOTE: Unlike with `mnode_clear_write', when calling this function,
 *       the caller must ensure that:
 *        - !wasdestroyed(mm)
 *        - !mman_lock_acquired(mm)
 *        - self->mn_part != NULL
 *        - LIST_ISBOUND(self, mn_writable)
 * Also note that the caller is responsible to sync `mm' before unlocking it! */
FUNDEF NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked)(struct mnode *__restrict self,
                                        struct mman *__restrict mm);

/* Same as `mnode_clear_write_locked()', but directory operate on
 * the current page directory. */
FUNDEF NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mnode_clear_write_locked_local)(struct mnode *__restrict self);

/* While holding a lock to `self->mn_mman' and `self->mn_part', try
 * to merge the given node with its successor/predecessor node, without
 * releasing any of the locks still held.
 * @return: * : The new, merged node (which may have a different min-addr
 *              that the original node `self'). Also note that this node
 *              may or may not be equal to `self', and that it's min- and
 *              max-addr fields may be different from those that `self'
 *              had upon entry, irregardless of `self' being re-returned.
 *              As a matter of fact `*self' becomes invalid after a call
 *              to this function! */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge)(struct mnode *__restrict self);


/* Mem-node tree API. All of these functions require that the caller
 * be holding a lock to the associated mman. */
struct mnode_tree_minmax {
	struct mnode *mm_min; /* [0..1] Lowest branch. */
	struct mnode *mm_max; /* [0..1] Greatest branch. */
};

FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mnode *NOTHROW(FCALL mnode_tree_locate)(/*nullable*/ struct mnode *root, void const *key);
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mnode *NOTHROW(FCALL mnode_tree_rlocate)(/*nullable*/ struct mnode *root, void const *minkey, void const *maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mnode_tree_insert)(struct mnode **__restrict proot, struct mnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL mnode_tree_tryinsert)(struct mnode **__restrict proot, struct mnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_remove)(struct mnode **__restrict proot, void const *key);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_rremove)(struct mnode **__restrict proot, void const *minkey, void const *maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mnode_tree_removenode)(struct mnode **__restrict proot, struct mnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_prevnode)(struct mnode *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mnode *NOTHROW(FCALL mnode_tree_nextnode)(struct mnode *__restrict self);
FUNDEF NOBLOCK NONNULL((4)) void NOTHROW(FCALL mnode_tree_minmaxlocate)(struct mnode *root, void const *minkey, void const *maxkey, struct mnode_tree_minmax *__restrict result);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MNODE_H */
