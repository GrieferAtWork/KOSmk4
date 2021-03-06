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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FNODE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/mman/mfile.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <kos/io.h>

#ifdef __CC__
DECL_BEGIN

/*
 * ==== Introduction to the new filesystem API ====
 *
 * It should be getting  obvious by now: the  new filesystem API is  greatly
 * unifying component-access across different API-layers, such as by merging
 * different operator-tables into a single, common table that is extended by
 * sub-classes as needed, as well as further abstraction and  simplification
 * of old APIs.
 *
 * The main difference to  the old system is  probably the strict adherence  to
 * the  fact that no  API-level operator callbacks should  ever be called while
 * holding any kind of lock, meaning that the new system will be able to follow
 * the  lock-less/async design philosophy  that can already  be seen (and felt)
 * within the new memory manager  which recently took the  place of the old  VM
 * system.
 *
 */

struct fnode;
struct fregnode;
struct fdirnode;
struct fsuper;
struct flnknode;
struct ffifonode;
struct fsocknode;
struct fdevnode;
struct blkdev;
struct chrdev;


/* Filesystem/device type-tree:
 *
 * ```
 *   mfile
 *     |
 *     +---> fnode                                 (TODO: replacement for `struct inode')
 *             |
 *             +----> fregnode  (S_IFREG)          (TODO: replacement for `struct regular_node')
 *             |
 *             +----> fdirnode  (S_IFDIR)          (TODO: replacement for `struct directory_node')
 *             |        |
 *             |        +-----> fsuper             (TODO: replacement for `struct superblock')
 *             |
 *             +----> flnknode  (S_IFLNK)          (TODO: replacement for `struct symlink_node')
 *             |
 *             +----> ffifonode (S_IFIFO)          (TODO: replacement for `struct fifo_node')
 *             |
 *             +----> fsocknode (S_IFSOCK)         (TODO: replacement for `struct socket_node')
 *             |
 *             +----> fdevnode
 *                      |
 *                      +-----> blkdev  (S_IFBLK)  (TODO: replacement for `struct block_device')
 *                      |
 *                      +-----> chrdev  (S_IFCHR)  (TODO: replacement for `struct character_device')
 * ```
 *
 * Assumptions/expectations in regards to the configuration of different filesystem classes:
 *   - fnode:
 *      - always: mo_changed == &fnode_changed;
 *   - fregnode:
 *      - always: MFILE_F_DELETED || !mfile_isanon(self);
 *      - always: !MFILE_F_NOUSRMMAP;
 *      - always: !MFILE_F_NOUSRIO;
 *      - always: !MFILE_F_FIXEDFILESIZE;
 *   - fdirnode:
 *      - always: fn_nlink == 1;
 *      - always: mf_filesize == (pos_t)-1;
 *      - always: MFILE_F_FIXEDFILESIZE;
 *      - always: MFILE_F_NOUSRMMAP;
 *      - always: MFILE_F_NOUSRIO;
 *   - flnknode:
 *      - always: mf_filesize == 0;
 *      - always: MFILE_F_READONLY;
 *      - always: MFILE_F_FIXEDFILESIZE;
 *      - always: MFILE_F_NOUSRMMAP;
 *      - always: MFILE_F_NOUSRIO;
 *      - always: mfile_isanon(self);
 *   - ffifonode:
 *      - always: mf_filesize == 0;
 *      - always: MFILE_F_READONLY;
 *      - always: MFILE_F_FIXEDFILESIZE;
 *      - always: MFILE_F_NOUSRMMAP;
 *      - always: MFILE_F_NOUSRIO;
 *      - always: mfile_isanon(self);
 *   - fsocknode:
 *      - always: mf_filesize == 0;
 *      - always: MFILE_F_READONLY;
 *      - always: MFILE_F_FIXEDFILESIZE;
 *      - always: MFILE_F_NOUSRMMAP;
 *      - always: MFILE_F_NOUSRIO;
 *      - always: mfile_isanon(self);
 *   - blkdev:
 *      - always: MFILE_F_FIXEDFILESIZE;
 *   - chrdev:
 *      - usually: mf_filesize == 0;
 *      - usually: MFILE_F_NOUSRMMAP;
 *      - usually: MFILE_F_FIXEDFILESIZE;
 *      - usually: mfile_isanon(self);
 *      - usually: implements(mso_pread)  { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
 *      - usually: implements(mso_pwrite) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
 *   - fsuper:
 *      - always: fn_super == self;
 *
 *
 * Data model:
 *
 *               fnode  <------(REF_IF([*].mf_flags & MFILE_FN_GLOBAL_REF))------ GLOBAL:fallnodes_list
 *                | ^
 *                | |
 *             REF| |REF_IF([*].mf_flags & MFILE_F_PERSISTENT)
 *                | |
 *                v |
 *               fsuper <------(REF_IF([*].mf_flags & MFILE_FN_GLOBAL_REF))------ GLOBAL:fallsuper_list
 *
 */


struct fsuper;
struct fnode;

struct fnode_ops {
#define FNODE_OPS_FIELDS(prefix, T)   MFILE_OPS_FIELDS(prefix, T)
#define _fnode_ops_firstfield(prefix) _mfile_ops_firstfield(prefix)
#define _fnode_ops_extract(ops)       ((struct fnode_ops const *)&(ops)->_fnode_ops_firstfield(no_))
#define fnode_ops_as_mfile_ops(ops)   ((struct mfile_ops const *)&(ops)->_mfile_ops_firstfield(no_))

	/* Operators... */
	FNODE_OPS_FIELDS(no_, struct fnode);
};

/* Filesystem node. */
struct fnode
#ifdef __cplusplus
    : mfile                             /* Underlying mem-file */
#endif /* __cplusplus */
{
	/* NOTE: `fn_file.mf_flags' may also contain `MFILE_FN_*' flags! */
#ifndef __cplusplus
	struct mfile                fn_file;     /* Underlying mem-file */
#endif /* !__cplusplus */
	nlink_t                     fn_nlink;    /* [lock(ATOMIC)] INode link counter. */
	mode_t                      fn_mode;     /* [lock(ATOMIC)] INode access mode (but note that file-type bits are [const]). */
	ino_t                       fn_ino;      /* [lock(_MFILE_F_SMP_TSLOCK)] INode number.
	                                          * On some filesystems, this number may change when the file is renamed (e.g. FAT)
	                                          * As   such,  a  lock   is  required  when   reading/writing  the  INode  number! */
	REF struct fsuper          *fn_super;    /* [1..1][const] Associated super-block. */
	SLIST_ENTRY(REF fnode)      fn_changed;  /* [lock(ATOMIC)][LIST(fn_super->fsp_changed)]
	                                          * [valid_if(!fsuper_datachanged_isanon(fn_super) &&
	                                          *           !mfile_isanon(self) && (MFILE_F_CHANGED | MFILE_F_ATTRCHANGED)]
	                                          * Link entry in the list of changed file-nodes. */
	LLRBTREE_NODE(fnode)        fn_supent;   /* [lock(fn_super->fs_nodeslock)][LIST(fn_super->fs_nodes)]
	                                          * Tree entry within the  super block's tree of  file-nodes.
	                                          * When  `rb_lhs' is set to `FSUPER_NODES_DELETED', then the
	                                          * file-node  is no longer apart of the super's tree of file
	                                          * nodes. In this case, the `MFILE_F_PERSISTENT' flag may be
	                                          * assumed to have already been cleared. */
	union {
		LIST_ENTRY(fnode)       fn_allnodes; /* [0..1][lock(:fnode_all_lock)][valid_if(!fnode_issuper(self))]
		                                      * Link entry within  the global  list of all  file nodes.  When
		                                      * `MFILE_FN_GLOBAL_REF' is set,  then the global  list holds  a
		                                      * reference to this node. */
		LIST_ENTRY(fsuper)      fn_allsuper; /* [0..1][lock(:fsuper_all_lock)][valid_if(fnode_issuper(self))]
		                                      * Link entry within the global  list of all super blocks.  When
		                                      * `MFILE_FN_GLOBAL_REF' is set,  then the global  list holds  a
		                                      * reference to this node. */
	};
};


/* Helper functions that must be invoked after `fn_nlink' or `fn_mode' was changed. */
#define fnode_nlink_changed(self) mfile_changed(self, MFILE_F_ATTRCHANGED)
#define fnode_mode_changed(self)  mfile_changed(self, MFILE_F_ATTRCHANGED)

/* Return a pointer to file-node operators of `self' */
#define fnode_getops(self) \
	((struct fnode_ops const *)__COMPILER_REQTYPE(struct fnode const *, self)->mf_ops)

#ifdef NDEBUG
#define _fnode_assert_ops_(ops) /* nothing */
#else /* NDEBUG */
#define _fnode_assert_ops_(ops) (ops)->no_changed == &fnode_v_changed,
#endif /* !NDEBUG */

/* Initialize common+basic fields. The caller must still initialize:
 *  - mf_parts, mf_flags, mf_filesize, mf_atime, mf_mtime, mf_ctime
 *  - fn_nlink, fn_ino, fn_mode, fn_allnodes, fn_supent
 * @param: struct fnode     *self:  File-node to initialize.
 * @param: struct fnode_ops *ops:   File-node operators.
 * @param: struct fsuper    *super: Filesystem superblock. */
#define _fnode_init(self, ops, super)                     \
	(_fnode_assert_ops_(ops)                              \
	 _mfile_init_common(self),                            \
	 (self)->mf_ops        = fnode_ops_as_mfile_ops(ops), \
	 (self)->mf_blockshift = (super)->mf_blockshift,      \
	 (self)->mf_part_amask = (super)->mf_part_amask,      \
	 (self)->fn_super      = incref(super))
#define _fnode_cinit(self, ops, super)                    \
	(_fnode_assert_ops_(ops)                              \
	 _mfile_cinit_common(self),                           \
	 (self)->mf_ops        = fnode_ops_as_mfile_ops(ops), \
	 (self)->mf_blockshift = (super)->mf_blockshift,      \
	 (self)->mf_part_amask = (super)->mf_part_amask,      \
	 (self)->fn_super      = incref(super))
/* Finalize a partially initialized `struct fnode' (as initialized by `_fnode_init()') */
#define _fnode_fini(self)     decref_nokill((self)->fn_super)

/* Mandatory callback for all types derived from `struct fnode',
 * for  use with `mf_ops->mo_changed'.  MUST NOT BE OVERWRITTEN! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fnode_v_changed)(struct fnode *__restrict self,
                               uintptr_t old_flags, uintptr_t new_flags);

/* File-node  destroy callback. Must be set in `mo_destroy',
 * but may be overwritten by sub-classes, in which case this
 * function must be called as the last thing done within the
 * sub-class destroy-operator. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fnode_v_destroy)(struct fnode *__restrict self);



/* Check if a given `struct fnode *self' is one of its many sub-classes. */
#define fnode_isreg(self)    S_ISREG((self)->fn_mode)
#define fnode_isdir(self)    S_ISDIR((self)->fn_mode)
#define fnode_issuper(self)  ((struct fnode *)&(self)->fn_super->fs_root == (self))
#define fnode_islnk(self)    S_ISLNK((self)->fn_mode)
#define fnode_isfifo(self)   S_ISFIFO((self)->fn_mode)
#define fnode_issock(self)   S_ISSOCK((self)->fn_mode)
#define fnode_isdev(self)    S_ISDEV((self)->fn_mode)
#define fnode_isblkdev(self) S_ISCHR((self)->fn_mode)
#define fnode_ischrdev(self) S_ISBLK((self)->fn_mode)
#define fnode_asreg(self)    ((struct fregnode *)(self))
#define fnode_asdir(self)    ((struct fdirnode *)(self))
#define fnode_assuper(self)  __COMPILER_CONTAINER_OF((struct fdirnode *)(self), struct fsuper, fs_root)
#define fnode_aslnk(self)    ((struct flnknode *)(self))
#define fnode_asfifo(self)   ((struct ffifonode *)(self))
#define fnode_assock(self)   ((struct fsocknode *)(self))
#define fnode_asdev(self)    ((struct fdevnode *)(self))
#define fnode_asblkdev(self) ((struct blkdev *)(self))
#define fnode_aschrdev(self) ((struct chrdev *)(self))

/* Check if a given `struct mfile *self' is one of its many sub-classes. */
#define mfile_isfnode(self)   ((self)->mf_ops->mo_changed == &fnode_changed)
#define mfile_isreg(self)     (mfile_isfnode(self) && fnode_isreg((struct fnode *)(self)))
#define mfile_isdir(self)     (mfile_isfnode(self) && fnode_isdir((struct fnode *)(self)))
#define mfile_issuper(self)   (mfile_isfnode(self) && fnode_issuper((struct fnode *)(self)))
#define mfile_islnk(self)     (mfile_isfnode(self) && fnode_islnk((struct fnode *)(self)))
#define mfile_isfifo(self)    (mfile_isfnode(self) && fnode_isfifo((struct fnode *)(self)))
#define mfile_issock(self)    (mfile_isfnode(self) && fnode_issock((struct fnode *)(self)))
#define mfile_isdev(self)     (mfile_isfnode(self) && fnode_isdev((struct fnode *)(self)))
#define mfile_isblkdev(self)  (mfile_isfnode(self) && fnode_isblkdev((struct fnode *)(self)))
#define mfile_ischrdev(self)  (mfile_isfnode(self) && fnode_ischrdev((struct fnode *)(self)))
#define mfile_asf(self)       ((struct fnode *)(self))
#define mfile_asreg(self)     ((struct fregnode *)(self))
#define mfile_asdir(self)     ((struct fdirnode *)(self))
#define mfile_assuper(self)   __COMPILER_CONTAINER_OF((struct fdirnode *)(self), struct fsuper, fs_root)
#define mfile_aslnk(self)     ((struct flnknode *)(self))
#define mfile_assock(self)    ((struct fsocknode *)(self))
#define mfile_asdev(self)     ((struct fdevnode *)(self))
#define mfile_asblkdev(self)  ((struct blkdev *)(self))
#define mfile_aschrdev(self)  ((struct chrdev *)(self))


/* Filenode tree operations. (for `struct fsuper::fs_nodes') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct fnode *NOTHROW(FCALL fnode_tree_locate)(/*nullable*/ struct fnode *root, ino_t key);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL fnode_tree_insert)(struct fnode **__restrict proot, struct fnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct fnode *NOTHROW(FCALL fnode_tree_remove)(struct fnode **__restrict proot, ino_t key);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL fnode_tree_removenode)(struct fnode **__restrict proot, struct fnode *__restrict node);



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FNODE_H */
