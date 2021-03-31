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

#include <kernel/mman/map.h>
#include <kernel/mman/unmapped.h>
#include <kernel/mman/mnode.h> /* __ALIGNOF_MNODE */
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/__pointer.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#define __ALIGNOF_MBNODE __ALIGNOF_INT64__
#if __ALIGNOF_MBNODE > __ALIGNOF_MNODE
#include <hybrid/__unaligned.h>
#endif /* __ALIGNOF_MBNODE > __ALIGNOF_MNODE */


#ifdef __CC__
DECL_BEGIN

struct unlockinfo;
struct mbnode;
struct mnode;
struct mman;
struct mexecinfo;

LIST_HEAD(mbnode_list, mbnode);
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


/* NOTE: Because a regular, old `struct mnode' doesn't contain the 64-bit `pos_t'
 *       field `mbn_filpos', the natural alignment of `struct mnode' may be  less
 *       than  that of `struct mbnode'. As such, we may need special work-arounds
 *       in order to safely access the `mbn_filpos' field of `struct mbnode'. */
#if __ALIGNOF_MBNODE > __ALIGNOF_MNODE
#define mnode_mbn_filpos_get(self)    ((pos_t)__hybrid_unaligned_get64(&(self)->mbn_filpos))
#define mnode_mbn_filpos_set(self, v) (__hybrid_unaligned_set64(&(self)->mbn_filpos, (u64)(v)))
#else /* __ALIGNOF_MBNODE > __ALIGNOF_MNODE */
#define mnode_mbn_filpos_get(self)    ((self)->mbn_filpos)
#define mnode_mbn_filpos_set(self, v) ((self)->mbn_filpos = (v))
#endif /* __ALIGNOF_MBNODE <= __ALIGNOF_MNODE */

struct mbnode {
	/* NOTE: This structure is (intentionally) binary-compatible
	 *       (for   the   most   part)   with    `struct mnode'!
	 * This is because when the memory image constructed within
	 * an mbuilder is loaded into an mman, all of the builder's
	 * nodes become mnode objects! */
	RBTREE_NODE(struct mbnode)          mbn_mement;   /* [const] R/B tree entry of mman mappings. */
	byte_t                             *mbn_minaddr;  /* [const] Lowest address mapped by this node. */
	byte_t                             *mbn_maxaddr;  /* [const] Greatest address mapped by this node. */
	uintptr_t                           mbn_flags;    /* mem-node flags (Set of `MNODE_F_*') */
	REF struct mpart                   *mbn_part;     /* [0..1][const] The bound mem-part.
	                                                   * When set to NULL, then this node represents a reserved node. */
	REF struct path                    *mbn_fspath;   /* [0..1][const] Optional mapping path (only used for memory->disk mapping listings) */
	REF struct directory_entry         *mbn_fsname;   /* [0..1][const] Optional mapping name (only used for memory->disk mapping listings) */
	union {
		WEAK REF struct mman          *_mbn_mman;     /* s.a. `struct mnode::mn_mman' */
		SLIST_ENTRY(mbnode)            _mbn_alloc;    /* Internal list of freshly allocated nodes. */
		struct mbnode                  *mbn_filnxt;   /* [0..1] Next node apart of the same file mapping.
		                                               * When non-NULL, you may assume that `mbnode_getendaddr(this) == mbnode_getaddr(mbn_filnxt)' */
	};
	union {
		struct {
			/* The 3 fields
			 *    - mbn_nxtfile
			 *    - mbn_file
			 *    - mbn_filpos
			 * are  [valid_if(this IN :mb_files)]. If this is the case,
			 * our `mbn_filnxt' (if non-NULL) points to the second node
			 * that is being used to map this file. */
			pos_t                       mbn_filpos;   /* [const] Absolute position of where `mbn_part' is (supposed)
			                                           * to start.  Ignored when  `mbn_file' is  an anonymous  file.
			                                           * NOTE: Access using `mnode_mbn_filpos_(get|set)' */
#if __SIZEOF_POS_T__ < (__SIZEOF_POINTER__ * 2)
			byte_t __mbn_pad[(__SIZEOF_POINTER__ * 2) - __SIZEOF_POS_T__];
#endif /* __SIZEOF_POS_T__ < (__SIZEOF_POINTER__ * 2) */
			SLIST_ENTRY(mbnode)         mbn_nxtfile;  /* [0..1] First node of the next separate file mapping. */
			LIST_ENTRY(mbnode)          mbn_nxtuprt;  /* [0..1] Next builder node that references a
			                                           *        unique `mbn_part' with a similar hash.
			                                           * NOTE: This field shares it's address with `_mbn_writable',
			                                           *       which is intentional, and important! */
			REF struct mfile           *mbn_file;     /* [0..1][const] The file that is being mapped. */
		};
		struct {
			/* Fields from `struct mnode' */
			PAGEDIR_PAGEALIGNED mpart_reladdr_t _mbn_partoff;  /* s.a. `struct mnode::mn_partoff' */
			LIST_ENTRY(mnode)                   _mbn_link;     /* s.a. `struct mnode::mn_link' */
			LIST_ENTRY(mnode)                   _mbn_writable; /* s.a. `struct mnode::mn_writable' */
			void                               *_mbn_module;   /* s.a. `struct mnode::_mn_module' */
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


#define MBNODE_PARTSET_NUMBUCKETS 16
struct mbnode_partset {
	/* [0..n][link(mbn_nxtuprt)][*] List of nodes
	 * mapping unique parts with a similar hash.. */
	struct mbnode_list mbps_set[MBNODE_PARTSET_NUMBUCKETS];
};

#define mbnode_partset_indexof(self, part) \
	(((uintptr_t)(part) >> 4) % MBNODE_PARTSET_NUMBUCKETS)
#define mbnode_partset_listof(self, part) \
	(&(self)->mbps_set[mbnode_partset_indexof(self, part)])

#define MPART_POINTER_SET_INIT \
	{ }
#define mbnode_partset_init(self) \
	__libc_memset((self)->mbps_set, 0, sizeof((self)->mbps_set))
#define mbnode_partset_cinit(self) \
	(void)0


struct rpc_entry;
struct mbuilder {
#ifdef __INTELLISENSE__
	struct mbnode             *mb_mappings; /* [0..n][owned] Tree of mem-nodes. */
	struct mnode              *mb_oldmap;   /* [0..n][owned] Old mem-node tree of the target mman. */
#else /* __INTELLISENSE__ */
	RBTREE_ROOT(struct mbnode) mb_mappings; /* [0..n][owned] Tree of mem-nodes. */
	RBTREE_ROOT(struct mnode)  mb_oldmap;   /* [0..n][owned] Old mem-node tree of the target mman. */
#endif /* !__INTELLISENSE__ */
	struct mbnode_partset      mb_uparts;   /* [0..n] Set of nodes mapping unique parts. */
	struct mbnode_slist        mb_files;    /* [0..n][link(mbn_nxtfile)] List of file mappings. */
	union {
		struct mbnode_slist   _mb_fbnodes;  /* [0..n][link(_mbn_alloc)] List of free mem-nodes. */
		struct mnode_slist    _mb_fnodes;   /* [0..n][link(_mbn_alloc)] List of free mem-nodes. */
	};
	struct rpc_entry          *mb_killrpc;  /* [0..n][link(re_next)]  List  of  pre-allocated  RPC
	                                         * descriptors, as used by `mbuilder_apply()' in order
	                                         * to  terminate threads using  the given target mman. */
};

/* Initialize the given mem-builder. */
#define MBUILDER_INIT                 \
	{                                 \
		__NULLPTR,                    \
		MPART_POINTER_SET_INIT,       \
		SLIST_HEAD_INITIALIZER(~),    \
		{                             \
			SLIST_HEAD_INITIALIZER(~) \
		},                            \
		__NULLPTR                     \
	}
#define mbuilder_init(self)                   \
	((self)->mb_mappings = __NULLPTR,         \
	 mbnode_partset_init(&(self)->mb_uparts), \
	 SLIST_INIT(&(self)->mb_files),           \
	 SLIST_INIT(&(self)->mb_fparts),          \
	 (self)->mb_killrpc = __NULLPTR)
#define mbuilder_cinit(self)                            \
	(__hybrid_assert((self)->mb_mappings == __NULLPTR), \
	 mbnode_partset_cinit(&(self)->mb_uparts),          \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mb_uparts)),  \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mb_fparts)),  \
	 __hybrid_assert((self)->mb_killrpc == __NULLPTR))

/* Finalize the given mem-builder. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_fini)(struct mbuilder *__restrict self);


/* Insert or remove a raw mem-node `fmnode' from self.
 * This function does:
 *  - assert(fmnode->mbn_part != NULL);
 *  - assert(fmnode->mbn_file != NULL);
 *  - fmnode->mbn_filnxt = NULL;       // Only  single-nde   initial   mappings   are   supported.
 *                                     // Additional  required nodes are added lazily if necessary
 *                                     // via the re-flow mechanism that is done as part of a call
 *                                     // to `mbuilder_partlocks_acquire_or_unlock()'
 *  - SLIST_INSERT(&self->mb_files, fmnode, mbn_nxtfile);
 *  - LIST_INSERT_HEAD(mbnode_partset_listof(&self->mb_uparts,
 *                                           fmnode->mbn_part),
 *                     fmnode, mbn_nxtuprt);
 *  - mbnode_tree_insert(&self->mb_mappings, fmnode);
 * As such, the caller must initialize:
 *  - fmnode->mbn_minaddr  (Mapping min address)
 *  - fmnode->mbn_maxaddr  (Mapping max address)
 *  - fmnode->mbn_flags    (Mapping flags)
 *  - fmnode->mbn_part     (as some part from `fmnode->mbn_file')
 *  - fmnode->mbn_fspath   (optional: filesystem path)
 *  - fmnode->mbn_fsname   (optional: filesystem name)
 *  - fmnode->mbn_filpos   (Wanted in-file mapping address)
 *  - fmnode->mbn_file     (The actual file being mapped) */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_insert_fmnode)(struct mbuilder *__restrict self,
                                      struct mbnode *__restrict fmnode);
/* Remove `fmnode' from `self'. - Asserts that no secondary nodes have
 * been allocated for use with `fmnode' (as could happen if the caller
 * uses `mbuilder_partlocks_acquire_or_unlock()' between a prior  call
 * to `mbuilder_insert_fmnode()' and the call to this function) */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_remove_fmnode)(struct mbuilder *__restrict self,
                                      struct mbnode *__restrict fmnode);


/* Acquire  locks to all  of the parts being  mapped by `self', and
 * ensure that  all mappings  within `self'  are fully  continuous.
 * If  this cannot  be done  without blocking,  invoke `unlock' (if
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
 * will  keep  on  attempting  the  operation  until  it  succeeds. */
FUNDEF NONNULL((1)) void FCALL
mbuilder_partlocks_acquire(struct mbuilder *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Release locks to all of the mapped mem-parts, as should have previously
 * been   acquired   during  a   call   to  `mbuilder_partlocks_acquire()' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_partlocks_release)(struct mbuilder *__restrict self);


/* Apply all of the mappings from  `self' onto `target', whilst simultaneously  deleting
 * any memory mapping still present within `target' (except for the kernel-reserve node)
 * NOTES:
 *  - When calling this function, the caller must ensure that:
 *     - mbuilder_partlocks_acquire(self)    (was called)
 *     - mman_lock_acquired(target)
 *  - Upon return, this function will have released all of the part-locks originally
 *    acquired  by `mbuilder_partlocks_acquire()', however the mman-lock to `target'
 *    will  _not_ have been released yet, and the caller must release that lock once
 *    they've finished doing other additional builder-apply operations.
 *  - This  function  doesn't  actually  modify  the  page  directory  of   `target'.
 *    The caller is responsible for doing this by calling `pagedir_unmap_userspace()'
 * @param: self:   The mman Builder object from which to take mappings to-be applied to `target'
 *                 Upon success, the contents  of `self' are left  undefined and must either  be
 *                 re-initialized, or not be attempted to be finalized.
 * @param: target: The target mman to which to apply the new memory mappings.
 *                 Upon success, this mman will only contain the mappings from `self', with all
 *                 of its old mappings having been deleted.
 *                 NOTE: This argument must not be the kernel mman */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_apply_impl)(struct mbuilder *__restrict self,
                                   struct mman *__restrict target);

/* Terminate all threads bound to `target', other than the calling
 * thread by sending an RPC that throws an E_EXIT_THREAD exception
 * to each of them.
 * For this  purpose, first  pre-allocate a  set of  RPC  descriptors
 * for  every  target  thread,  before  sending  them  all  at  once.
 * If  the allocation cannot  be done without  blocking, do the usual
 * unlock+return_false. Otherwise, when this function returns `true',
 * then you know that no thread  other than yourself is still  making
 * any use of the given `target' mman.
 *
 * NOTE: This function is used to implement `MBUILDER_APPLY_AA_TERMTHREADS'
 *
 * Locking logic:
 *   in:   mbuilder_partlocks_acquire(self) && mman_lock_acquired(target) && HELD(unlock)
 *   out:  return == true:
 *           - mbuilder_partlocks_release(self);
 *           - mman_lock_acquired(target) && HELD(unlock)
 *         return == false || EXCEPT:
 *           - mbuilder_partlocks_release(self);
 *           - mman_lock_release(target);
 *           - unlock(); */
FUNDEF NONNULL((1, 2)) __BOOL KCALL
mbuilder_termthreads_or_unlock(struct mbuilder *__restrict self,
                               struct mman *__restrict target,
                               struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK);


/* Slightly   simplified   version   of   `mbuilder_apply_or_unlock()'
 * that should be called while not already holding any locks, and will
 * automatically acquire necessary locks, do the requested calls,  and
 * finally release all locks acquired,  and still held at that  point.
 * @param: additional_actions: Additional actions to be atomically performed
 *                             alongside  the  setting of  the  new mem-node
 *                             mappings (set of `MBUILDER_APPLY_AA_*') */
FUNDEF NONNULL((1, 2)) void KCALL
mbuilder_apply(struct mbuilder *__restrict self,
               struct mman *__restrict target,
               unsigned int additional_actions,
               struct mexecinfo *execinfo DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK);
#define MBUILDER_APPLY_AA_NOTHING      0x0000 /* No additional actions */
#define MBUILDER_APPLY_AA_TERMTHREADS  0x0001 /* Terminate  all threads using `target', excluding the caller.
                                               * If the calling thread isn't using `target', simply terminate
                                               * all threads that are using `target' */
#define MBUILDER_APPLY_AA_SETEXECINFO  0x0002 /* Set the given `execinfo' for the given mman.
                                               * When `execinfo' is `NULL', delete exec info. */






/************************************************************************/
/* Functions for populating MBUILDER                                    */
/************************************************************************/

/* MBuilder-version of `mman_findunmapped()' */
#ifdef __INTELLISENSE__
NOBLOCK WUNUSED NONNULL((1)) void *
NOTHROW(mbuilder_findunmapped)(struct mbuilder *__restrict self, void *addr,
                              size_t num_bytes, unsigned int flags,
                              size_t min_alignment DFL(PAGESIZE));
#else /* __INTELLISENSE__ */
#define mbuilder_findunmapped(self, ...) \
	mman_findunmapped_in_usertree((struct mnode **)&(self)->mb_mappings, __VA_ARGS__)
#endif /* !__INTELLISENSE__ */

/* MBuilder-version of `mman_getunmapped_or_unlock()' (without the unlock-part)
 * But  note  that unlike  `mman_getunmapped_or_unlock()', this  version always
 * acts  as though  `MAP_FIXED_NOREPLACE' was  given when  `MAP_FIXED' is used.
 * After  all: there  is no functionality  for removing nodes  from an mbuilder
 * once they've been added. Not because  this would be impossible, but  because
 * such functionality is never required.
 * Also: This function never returns `MAP_FAILED'! */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED void *FCALL
mbuilder_getunmapped(struct mbuilder *__restrict self, void *addr,
                     size_t num_bytes, unsigned int flags,
                     size_t min_alignment DFL(PAGESIZE))
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* MBuilder-version of `mman_map()' */
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

/* MBuilder-version of `mman_map_subrange()' */
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

/* MBuilder-version of `mman_map_res()' */
FUNDEF NONNULL((1)) void *KCALL
mbuilder_map_res(struct mbuilder *__restrict self,
                 UNCHECKED void *hint, size_t num_bytes,
                 unsigned int flags DFL(0),
                 size_t min_alignment DFL(PAGESIZE))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* TODO: The PEB API is deprecated, and at some point in the future,
 *       process startup information will  be passed via the  main()
 *       thread's stack! */

/* Allocate  a  PEB  (Process  Environment   Block)  within  the  given   MBuilder,
 * initializing  its  contents  with the  strings  from the  given  argv+envp pair.
 * This function is called from `vm_exec()' after the remainder of the application,
 * as well as the dynamic linker have already been loaded into memory.
 * @param: argc_inject: The number of arguments from `argv_inject' to inject
 *                      at the beginning of the user-space argc/argv vector.
 * @param: argv_inject: Vector of arguments to inject at the beginning of
 *                      the user-space argc/argv vector.
 * @param: argv:        User-space pointer to a NULL-terminated vector of argument strings
 * @param: envp:        User-space pointer to a NULL-terminated vector of environment strings
 * @return: * :         Page index of the PEB (to-be passed to the user-space program) */
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
mbuilder_alloc_peb(struct mbuilder *__restrict self,
                   size_t argc_inject, KERNEL char const *const *argv_inject,
                   USER UNCHECKED char const *USER CHECKED const *argv,
                   USER UNCHECKED char const *USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define mbuilder_alloc_peb64     mbuilder_alloc_peb
#define mbuilder_alloc_peb64_p64 mbuilder_alloc_peb
#define mbuilder_alloc_peb32_p32 mbuilder_alloc_peb32
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
mbuilder_alloc_peb32(struct mbuilder *__restrict self,
                     size_t argc_inject, KERNEL char const *const *argv_inject,
                     USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *argv,
                     USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
mbuilder_alloc_peb32_p64(struct mbuilder *__restrict self,
                         size_t argc_inject, KERNEL char const *const *argv_inject,
                         USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *argv,
                         USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
mbuilder_alloc_peb64_p32(struct mbuilder *__restrict self,
                         size_t argc_inject, KERNEL char const *const *argv_inject,
                         USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *argv,
                         USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define mbuilder_alloc_peb32     mbuilder_alloc_peb
#define mbuilder_alloc_peb64_p64 mbuilder_alloc_peb64
#define mbuilder_alloc_peb32_p32 mbuilder_alloc_peb
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
mbuilder_alloc_peb64(struct mbuilder *__restrict self,
                     size_t argc_inject, KERNEL char const *const *argv_inject,
                     USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *argv,
                     USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
mbuilder_alloc_peb64_p32(struct mbuilder *__restrict self,
                         size_t argc_inject, KERNEL char const *const *argv_inject,
                         USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *argv,
                         USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
mbuilder_alloc_peb32_p64(struct mbuilder *__restrict self,
                         size_t argc_inject, KERNEL char const *const *argv_inject,
                         USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *argv,
                         USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);
#else
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif
#endif /* __ARCH_HAVE_COMPAT */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MBUILDER_H */
