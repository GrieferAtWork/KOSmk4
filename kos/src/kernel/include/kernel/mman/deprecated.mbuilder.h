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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MBUILDER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MBUILDER_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mm-map.h>
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#ifdef __CC__
DECL_BEGIN

struct unlockinfo;
struct mbnode;
struct mnode;
struct mman;
struct mman_execinfo_struct;

SLIST_HEAD(mbnode_slist, mbnode);

#ifndef __mnode_slist_defined
#define __mnode_slist_defined 1
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

#ifndef __mfile_ndef_defined
#define __mfile_ndef_defined 1
DATDEF struct mfile mfile_ndef;     /* Random, uninitialized, anonymous memory. */
#endif /* !__mfile_ndef_defined */

#ifndef __mfile_zero_defined
#define __mfile_zero_defined 1
DATDEF struct mfile mfile_zero;     /* Zero-initialized, anonymous memory. */
#endif /* !__mfile_zero_defined */

#ifndef __mpart_reladdr_t_defined
#define __mpart_reladdr_t_defined 1
typedef size_t mpart_reladdr_t;
#endif /* !__mpart_reladdr_t_defined */



struct mbnode {
	/* NOTE: This structure is (intentionally) binary-compatible
	 *       (for the most part) with `struct mnode'!
	 * This is because when the memory image constructed within
	 * an mbuilder is loaded into an mman, all of the builder's
	 * nodes become mnode objects! */
	uintptr_t                           mbn_flags;    /* mem-node flags (Set of `MNODE_F_*') */
	byte_t                             *mbn_minaddr;  /* [const] Lowest address mapped by this node. */
	byte_t                             *mbn_maxaddr;  /* [const] Greatest address mapped by this node. */
	RBTREE_NODE(struct mbnode)          mbn_mement;   /* [const] R/B tree entry of mman mappings. */
	REF struct mpart                   *mbn_part;     /* [0..1][const] The bound mem-part.
	                                                   * When set to NULL, then this node represents a reserved node. */
	REF struct path                    *mbn_fspath;   /* [0..1][const] Optional mapping path (only used for memory->disk mapping listings) */
	REF struct directory_entry         *mbn_fsname;   /* [0..1][const] Optional mapping name (only used for memory->disk mapping listings) */
	union {
		SLIST_ENTRY(mbnode)            _mbn_alloc;    /* Internal list of freshly allocated nodes. */
		struct mbnode                  *mbn_filnxt;   /* [0..1] Next node apart of the same file mapping.
		                                               * When non-NULL, you may assume that `mbnode_getendaddr(this) == mbnode_getaddr(mbn_filnxt)' */
		WEAK REF struct mman          *_mbn_mman;     /* s.a. `struct mnode::mn_mman' */
	};
	union {
		struct {
			SLIST_ENTRY(mbnode)         mbn_nxtuprt;  /* [0..1] Next builder node that references a unique `mbn_part'.
			                                           * If the same `mbn_part' is mapped more than once within
			                                           * the same `mbuilder', then this list will only ever contain
			                                           * exactly one of the nodes that are mapping said part. */
			/* The next 3 fields are [valid_if(this IN :mb_files)]
			 * If this is the case, our `mbn_filnxt' (if non-NULL) points
			 * to the second node that is being used to map this file. */
			SLIST_ENTRY(mbnode)         mbn_nxtfile;  /* [0..1] First node of the next separate file mapping. */
			REF struct mfile           *mbn_file;     /* [0..1][const] The file that is being mapped. */
			pos_t                       mbn_filpos;   /* [const] Absolute position of where `mbn_part' is (supposed)
			                                           * to start. Ignored when `mbn_file' is an anonymous file. */
		};
		struct {
			/* Fields from `struct mnode' */
			PAGEDIR_PAGEALIGNED mpart_reladdr_t _mbn_partoff;  /* s.a. `struct mnode::mn_partoff' */
			LIST_ENTRY(mnode)                   _mbn_link;     /* s.a. `struct mnode::mn_link' */
			LIST_ENTRY(mnode)                   _mbn_writable; /* s.a. `struct mnode::mn_writable' */
		};
	};
};

/* Get bounds for the given mem-node. */
#define mbnode_getminaddr(self) ((void *)(self)->mbn_minaddr)
#define mbnode_getmaxaddr(self) ((void *)(self)->mbn_maxaddr)
#define mbnode_getendaddr(self) ((void *)((self)->mbn_maxaddr + 1))
#define mbnode_getaddr(self)    ((void *)(self)->mbn_minaddr)
#define mbnode_getsize(self)    ((size_t)((self)->mbn_maxaddr - (self)->mbn_minaddr) + 1)
#define mbnode_iskern(self)     ADDR_ISKERN((self)->mbn_minaddr)
#define mbnode_isuser(self)     ADDR_ISUSER((self)->mbn_minaddr)
/* Return the part-relative min-/max-address that is being mapped. */
#define mbnode_getmapminaddr(self) ((mpart_reladdr_t)((self)->mbn_partoff))
#define mbnode_getmapmaxaddr(self) ((mpart_reladdr_t)((self)->mbn_partoff + ((size_t)((self)->mbn_maxaddr - (self)->mbn_minaddr))))
#define mbnode_getmapendaddr(self) ((mpart_reladdr_t)((self)->mbn_partoff + mbnode_getsize(self)))


/* Mem-builder-node tree API. */
struct mbnode_tree_minmax {
	struct mbnode *mm_min; /* [0..1] Lowest branch. */
	struct mbnode *mm_max; /* [0..1] Greatest branch. */
};

FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mbnode *NOTHROW(FCALL mbnode_tree_locate)(/*nullable*/ struct mbnode *root, void const *key) ASMNAME("mnode_tree_locate");
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mbnode *NOTHROW(FCALL mbnode_tree_rlocate)(/*nullable*/ struct mbnode *root, void const *minkey, void const *maxkey) ASMNAME("mnode_tree_rlocate");
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mbnode_tree_insert)(struct mbnode **__restrict proot, struct mbnode *__restrict node) ASMNAME("mnode_tree_insert");
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL mbnode_tree_tryinsert)(struct mbnode **__restrict proot, struct mbnode *__restrict node) ASMNAME("mnode_tree_tryinsert");
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mbnode *NOTHROW(FCALL mbnode_tree_remove)(struct mbnode **__restrict proot, void const *key) ASMNAME("mnode_tree_remove");
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mbnode *NOTHROW(FCALL mbnode_tree_rremove)(struct mbnode **__restrict proot, void const *minkey, void const *maxkey) ASMNAME("mnode_tree_rremove");
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mbnode_tree_removenode)(struct mbnode **__restrict proot, struct mbnode *__restrict node) ASMNAME("mnode_tree_removenode");
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mbnode *NOTHROW(FCALL mbnode_tree_prevnode)(struct mbnode *__restrict self) ASMNAME("mnode_tree_prevnode");
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mbnode *NOTHROW(FCALL mbnode_tree_nextnode)(struct mbnode *__restrict self) ASMNAME("mnode_tree_nextnode");
FUNDEF NOBLOCK NONNULL((4)) void NOTHROW(FCALL mbnode_tree_minmaxlocate)(struct mbnode *root, void const *minkey, void const *maxkey, struct mbnode_tree_minmax *__restrict result) ASMNAME("mnode_tree_minmaxlocate");


struct mpart_pointer_set {
	size_t         mpps_mask; /* Allocated hash mask (power-of-2-minus-1) */
	struct mpart **mpps_list; /* [0..1][0..mpps_mask+1][owned] Hash-vector of mem-parts. */
};

struct mbuilder {
#ifdef __INTELLISENSE__
	struct mbnode             *mb_mappings; /* [0..n] Tree of mem-nodes. */
#else /* __INTELLISENSE__ */
	RBTREE_ROOT(struct mbnode) mb_mappings; /* [0..n] Tree of mem-nodes. */
#endif /* !__INTELLISENSE__ */
	struct mbnode_slist        mb_files;    /* [0..n][link(mbn_nxtfile)] List of file mappings. */
	struct mpart_pointer_set   mb_parts;    /* [0..n] Set of all of the unique parts used by the builder. */
	union {
		struct mbnode_slist    mb_fparts;   /* [0..n][link(_mbn_alloc)] List of free mem-nodes. */
		struct mnode_slist    _mb_fnodes;   /* [0..n][link(_mbn_alloc)] List of free mem-nodes. */
	};
};

/* Initialize the given mem-builder. */
#define MBUILDER_INIT \
	{ __NULLPTR, SLIST_HEAD_INITIALIZER(~), SLIST_HEAD_INITIALIZER(~) }
#define mbuilder_init(self)           \
	((self)->mb_mappings = __NULLPTR, \
	 SLIST_INIT(&(self)->mb_uparts),  \
	 SLIST_INIT(&(self)->mb_fparts))
#define mbuilder_cinit(self)                            \
	(__hybrid_assert((self)->mb_mappings == __NULLPTR), \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mb_uparts)),  \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mb_fparts)))

/* Finalize the given mem-builder. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_fini)(struct mbuilder *__restrict self);

/* Acquire locks to all of the parts being mapped by `self', and
 * ensure that all mappings within `self' are fully continuous.
 * If this cannot be done without blocking, invoke `unlock' (if
 * given), try to make it so that a repeated call will (eventually)
 * succeed, and return `false'.
 * Otherwise (if all locks have been acquired, and all mappings are
 * continuous), return `true'.
 * NOTE: If this function returns with an exception, `unlock' will
 *       also be invoked. */
FUNDEF NONNULL((1)) __BOOL FCALL
mbuilder_partlocks_acquire_or_unlock(struct mbuilder *__restrict self,
                                     struct unlockinfo *unlock)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Helper wrapper for `mbuilder_partlocks_acquire_or_unlock()' that
 * will keep on attempting the operation until it succeeds. */
FUNDEF NONNULL((1)) void FCALL
mbuilder_partlocks_acquire(struct mbuilder *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Release locks to all of the mapped mem-parts, as should have previously
 * been acquired during a call to `mbuilder_partlocks_acquire()' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_partlocks_release)(struct mbuilder *__restrict self);


/* Apply all of the mappings from `self' onto `target', whilst simultaneously deleting
 * any memory mapping still present within `target' (except for the kernel-reserve node)
 * This function is guarantied to operate atomically in a way that allows the caller
 * to assume that no memory mappings (or anything else for that matter) changes if the
 * function fails and returns by throwing an error, and that everything happens exactly
 * as intended if it returns normally.
 * NOTE: Upon success, `self' will have been finalized.
 * @param: self:   The VM Builder object from which to take mappings to-be applied to `target'
 *                 Upon success, the contents of `self' are left undefined and must either be
 *                 re-initialized, or not be attempted to be finalized.
 * @param: target: The target VM to which to apply the new memory mappings.
 *                 Upon success, this VM will only contain the mappings from `self', with all
 *                 of its old mappings having been deleted.
 *                 NOTE: This argument must not be the kernel VM
 * @param: additional_actions: Additional actions to be atomically performed alongside
 *                 the application of the new memory mappings (set of `VMB_APPLY_AA_*') */
FUNDEF NONNULL((1, 2)) void KCALL
mbuilder_apply_and_fini(struct mbuilder *__restrict self,
                        struct mman *__restrict target,
                        unsigned int additional_actions,
                        struct mman_execinfo_struct *execinfo DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK);
#define MBUILDER_APPLY_AA_NOTHING      0x0000 /* No additional actions */
#define MBUILDER_APPLY_AA_TERMTHREADS  0x0001 /* Terminate all threads using `target', excluding the caller.
                                               * If the calling thread isn't using `target', simply terminate
                                               * all threads that are using `target' */
#define MBUILDER_APPLY_AA_SETEXECINFO  0x0002 /* Set the given `execinfo' for the given VM */





/************************************************************************/
/* Functions for populating MBUILDER                                    */
/************************************************************************/

/* Try to find a suitable, unmapped address range
 * Behaves exactly the same as `mman_getunmapped_nx()' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) void *
NOTHROW(FCALL mbuilder_getunmapped_nx)(struct mbuilder *__restrict self,
                                       void *addr, size_t num_bytes, unsigned int flags,
                                       size_t min_alignment DFL(PAGESIZE));

/* Same as `mbuilder_getunmapped_nx()', but never return `MMAN_GETUNMAPPED_ERROR'.
 * Instead, the given mman is unlocked on error, and an exception is thrown.
 * Behaves exactly the same as `mman_getunmapped_or_unlock()', except that there
 * aren't any locks involved. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED void *FCALL
mbuilder_getunmapped(struct mbuilder *__restrict self,
                     void *addr, size_t num_bytes, unsigned int flags,
                     size_t min_alignment DFL(PAGESIZE))
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* Map a given file into the specified mbuilder.
 * Behaves exactly the same as `mman_map()' */
FUNDEF NONNULL((1, 6)) void *KCALL
mbuilder_map(struct mbuilder *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int prot DFL(PROT_READ | PROT_WRITE | PROT_SHARED),
             unsigned int flags DFL(0),
             struct mfile *__restrict file DFL(&mfile_zero),
             struct path *file_fspath DFL(__NULLPTR),
             struct directory_entry *file_fsname DFL(__NULLPTR),
             pos_t file_pos DFL(0),
             size_t min_alignment DFL(PAGESIZE))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);

/* Same as `mbuilder_map()', but only allow pages entirely contained within
 * the file-relative address range `file_map_minaddr...file_map_maxaddr'
 * to be mapped. Attempting to map file contents beyond this range will
 * instead result in `&mfile_zero' getting mapped instead.
 * Behaves exactly the same as `mman_map_subrange()' */
FUNDEF NONNULL((1, 6)) void *KCALL
mbuilder_map_subrange(struct mbuilder *__restrict self,
                      UNCHECKED void *hint, size_t num_bytes,
                      unsigned int prot DFL(PROT_READ | PROT_WRITE | PROT_SHARED),
                      unsigned int flags DFL(0),
                      struct mfile *__restrict file DFL(&mfile_zero),
                      struct path *file_fspath DFL(__NULLPTR),
                      struct directory_entry *file_fsname DFL(__NULLPTR),
                      pos_t file_pos DFL(0),
                      pos_t file_map_minaddr DFL(0),
                      pos_t file_map_maxaddr DFL((pos_t)-1),
                      size_t min_alignment DFL(PAGESIZE))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* Same as `mbuilder_map()', but instead of actually mapping something, leave the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * Behaves exactly the same as `mman_map_res()' */
FUNDEF NONNULL((1)) void *KCALL
mbuilder_map_res(struct mbuilder *__restrict self,
                 UNCHECKED void *hint, size_t num_bytes,
                 unsigned int flags DFL(0),
                 size_t min_alignment DFL(PAGESIZE))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);



DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MBUILDER_H */
