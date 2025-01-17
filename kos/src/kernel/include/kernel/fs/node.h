/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_NODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_NODE_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mfile.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <asm/os/stat.h> /* __S_IS*() macros */

/* File mode test macros. */
#if !defined(S_ISDIR) && defined(__S_ISDIR)
#define S_ISDIR(mode)  __S_ISDIR(mode)  /* Directory. */
#endif /* !S_ISDIR && __S_ISDIR */
#if !defined(S_ISCHR) && defined(__S_ISCHR)
#define S_ISCHR(mode)  __S_ISCHR(mode)  /* Character device. */
#endif /* !S_ISCHR && __S_ISCHR */
#if !defined(S_ISBLK) && defined(__S_ISBLK)
#define S_ISBLK(mode)  __S_ISBLK(mode)  /* Block device. */
#endif /* !S_ISBLK && __S_ISBLK */
#if !defined(S_ISDEV) && defined(__S_ISDEV)
#define S_ISDEV(mode)  __S_ISDEV(mode) /* S_ISCHR(mode) || S_ISBLK(mode) */
#endif /* !S_ISDEV && __S_ISDEV */
#if !defined(S_ISREG) && defined(__S_ISREG)
#define S_ISREG(mode)  __S_ISREG(mode)  /* Regular file. */
#endif /* !S_ISREG && __S_ISREG */
#if !defined(S_ISFIFO) && defined(__S_ISFIFO)
#define S_ISFIFO(mode) __S_ISFIFO(mode) /* FIFO. */
#endif /* !S_ISFIFO && __S_ISFIFO */
#if !defined(S_ISLNK) && defined(__S_ISLNK)
#define S_ISLNK(mode)  __S_ISLNK(mode)  /* Symbolic link. */
#endif /* !S_ISLNK && __S_ISLNK */
#if !defined(S_ISSOCK) && defined(__S_ISSOCK)
#define S_ISSOCK(mode) __S_ISSOCK(mode) /* Socket. */
#endif /* !S_ISSOCK && __S_ISSOCK */

#ifdef __CC__
DECL_BEGIN

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

#ifndef __WANT_FS_INLINE_STRUCTURES
#ifndef __cplusplus
#define __WANT_FS_INLINE_STRUCTURES
#elif defined(__WANT_FS_INIT)
#define __WANT_FS_INLINE_STRUCTURES
#endif /* ... */
#endif /* !__WANT_FS_INLINE_STRUCTURES */



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
 *   mfile                                       # <kernel/mman/mfile.h>
 *   └─> fnode                                   # <kernel/fs/node.h>
 *       ├─> fregnode                            # <kernel/fs/regnode.h>: S_IFREG
 *       │   ├─> printnode                       # <kernel/fs/printnode.h>
 *       │   └─> [...]
 *       ├─> fdirnode                            # <kernel/fs/dirnode.h>: S_IFDIR
 *       │   ├─> fsuper                          # <kernel/fs/super.h>
 *       │   │   ├─> ramfs_super                 # <kernel/fs/ramfs.h>
 *       │   │   │   └─> devfs_super             # <kernel/fs/devfs.h>
 *       │   │   └─> flatsuper                   # <kernel/fs/flat.h>
 *       │   │       └─> [...]
 *       │   ├─> ramfs_dirnode
 *       │   ├─> flatdirnode                     # <kernel/fs/flat.h>
 *       │   │   └─> [...]
 *       │   └─> constdir                        # <kernel/fs/constdir.h>
 *       ├─> flnknode                            # <kernel/fs/lnknode.h>: S_IFLNK
 *       │   ├─> clnknode                        # <kernel/fs/clnknode.h>
 *       │   └─> [...]
 *       ├─> fdevnode                            # <kernel/fs/devnode.h>: S_IFBLK, S_IFCHR
 *       │   └─> device                          # <kernel/fs/devfs.h>:   Base class for device nodes within devfs
 *       │       ├─> blkdev                      # <kernel/fs/blkdev.h>:  S_IFBLK  (including partitions)
 *       │       │   └─> [...]
 *       │       └─> chrdev                      # <kernel/fs/chrdev.h>:  S_IFCHR
 *       │           ├─> ansittydev              # <dev/ansitty.h>
 *       │           │   └─> videodev            # <dev/video.h>
 *       │           │       └─> [...]
 *       │           ├─> ttydev                  # <dev/tty.h>
 *       │           │   ├─> mkttydev            # <dev/mktty.h>
 *       │           │   └─> ptyslave            # <dev/pty.h>
 *       │           ├─> ptymaster               # <dev/pty.h>
 *       │           ├─> kbddev                  # <dev/keyboard.h>
 *       │           │   └─> [...]
 *       │           ├─> mousedev                # <dev/mouse.h>
 *       │           └─> nicdev                  # <dev/nic.h>
 *       │               └─> [...]
 *       ├─> ffifonode                           # <kernel/fs/fifonode.h>: S_IFIFO
 *       └─> fsocknode                           # <kernel/fs/socknode.h>: S_IFSOCK
 * ```
 *
 * [...]: This means that more sub-classes are known to be defined in  drivers
 *        Note that this list may be incomplete, as drivers are able to create
 *        subclasses at any point in the above tree.
 *
 * Assumptions/expectations in regards to the configuration of different filesystem classes:
 *   - fnode:
 *      - [X] mo_changed == &fnode_v_changed;
 *   - fregnode:
 *      - [W] MFILE_F_DELETED || !mfile_isanon(self);
 *      - [W] !MFILE_F_NOUSRMMAP;
 *      - [W] !MFILE_F_NOUSRIO;
 *      - [W] !MFILE_F_FIXEDFILESIZE;
 *   - fdirnode:
 *      - [W] MFILE_F_DELETED || fn_nlink == 1;
 *      - [W] MFILE_F_NOUSRMMAP;
 *      - [W] MFILE_F_NOUSRIO;
 *      - [W] MFILE_F_FIXEDFILESIZE;
 *   - flnknode:
 *      - [W] MFILE_F_READONLY;
 *      - [W] MFILE_F_FIXEDFILESIZE;
 *      - [W] MFILE_F_NOUSRMMAP;
 *      - [W] MFILE_F_NOUSRIO;
 *   - ffifonode:
 *      - [W] mf_filesize == 0;
 *      - [W] mf_parts             == MFILE_PARTS_ANONYMOUS; // iow: mfile_isanon(self);
 *      - [W] mf_changed.slh_first == MFILE_PARTS_ANONYMOUS; // iow: mfile_isanon(self);
 *      - [W] MFILE_F_READONLY;
 *      - [W] MFILE_F_FIXEDFILESIZE;
 *      - [W] MFILE_F_NOUSRMMAP;
 *      - [W] MFILE_F_NOUSRIO;
 *   - fsocknode:
 *      - [W] mf_filesize == 0;
 *      - [W] mf_parts             == MFILE_PARTS_ANONYMOUS; // iow: mfile_isanon(self);
 *      - [W] mf_changed.slh_first == MFILE_PARTS_ANONYMOUS; // iow: mfile_isanon(self);
 *      - [W] MFILE_F_READONLY;
 *      - [W] MFILE_F_FIXEDFILESIZE;
 *      - [W] MFILE_F_NOUSRMMAP;
 *      - [W] MFILE_F_NOUSRIO;
 *   - blkdev:
 *      - [X] MFILE_F_FIXEDFILESIZE;
 *      - [X] mf_parts             != MFILE_PARTS_ANONYMOUS; // iow: !mfile_isanon(self);
 *      - [X] mf_changed.slh_first != MFILE_PARTS_ANONYMOUS; // iow: !mfile_isanon(self);
 *   - chrdev: (NOTE: The following [W] should really be understood as _very_ weak. There
 *                    may be good reasons for  `chrdev's to break these  expectations...)
 *      - [W] mf_filesize == 0;
 *      - [W] mf_parts             == MFILE_PARTS_ANONYMOUS; // iow: mfile_isanon(self);
 *      - [W] mf_changed.slh_first == MFILE_PARTS_ANONYMOUS; // iow: mfile_isanon(self);
 *      - [W] MFILE_F_NOUSRMMAP;
 *      - [W] MFILE_F_NOUSRIO;
 *      - [W] MFILE_F_FIXEDFILESIZE;
 *   - fsuper:
 *      - [W] MFILE_F_DELETED || fn_nlink == 1;
 *      - [W] MFILE_F_NOUSRMMAP;
 *      - [W] MFILE_F_NOUSRIO;
 *      - [W] MFILE_F_FIXEDFILESIZE;
 *      - [X] fn_super == self;
 *
 * Legend:
 *   [X]  eXlicitly enforced: this is a requirement that may not be validated
 *   [W]  Weakly enforced: never asserted and  should not be relied upon.  You
 *        may take this as a suggestion, but you may also deviate from it. But
 *        if you do, things might get strange... (Not undefined; _unexpected_)
 */


struct fsuper;
struct fnode;

struct fnode_perm_ops {
	/* [0..1] Get the owner of the  file-node. When this operator  is
	 * implemented,  the `fn_uid' and  `fn_gid' fields contain either
	 * invalid-, or fs-specific data. Furthermore, the file owner can
	 * not be changed, as though `MFILE_FN_ATTRREADONLY' was set. */
	BLOCKING NONNULL_T((1, 2, 3)) void
	(KCALL *npo_getown)(struct fnode *__restrict self,
	                    uid_t *__restrict powner,
	                    gid_t *__restrict pgroup)
			THROWS(E_IOERROR, ...);
};

struct fnode_ops {
	struct mfile_ops no_file; /* MFile operators */

	/* [0..1] Optional operator for freeing `self'
	 * - Called at the end of `fnode_v_destroy()'
	 * - When not defined, the system instead does `kfree(self)' */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *no_free)(struct fnode *__restrict self);

	/* [1..1] Write modified file attributes to disk (must be implemented as no-op for RAM filesystems)
	 * The following attributes must be saved by this function (note that in order to safely read these
	 * attributes, this function needs to acquire the `_MFILE_F_SMP_TSLOCK' lock of `self'):
	 *  - self->fn_nlink                    # Guarantied to be `<= fn_super->fs_feat.sf_link_max'
	 *  - self->fn_mode                     # Mode-bits which can't be encoded simply don't get saved!
	 *  - self->fn_uid                      # Guarantied allowed by `fsuper_validuid()'
	 *  - self->fn_gid                      # Guarantied allowed by `fsuper_validgid()'
	 *  - self->_fnode_file_ mf_filesize    # Guarantied to be `<= fn_super->fs_feat.sf_filesize_max'
	 *  - self->_fnode_file_ mf_atime       # Write to disk as would be truncated by `fsuper_truncate_atime()'
	 *  - self->_fnode_file_ mf_mtime       # Write to disk as would be truncated by `fsuper_truncate_mtime()'
	 *  - self->_fnode_file_ mf_ctime       # Write to disk as would be truncated by `fsuper_truncate_ctime()'
	 *  - self->_fnode_file_ mf_btime       # Write to disk as would be truncated by `fsuper_truncate_btime()' */
	BLOCKING NONNULL_T((1)) void
	(KCALL *no_wrattr)(struct fnode *__restrict self)
			THROWS(E_IOERROR, ...);

	/* [0..1] Permissions-related operators. */
	struct fnode_perm_ops const *no_perm;
};


/* No-op callback for `no_wrattr' (for RAM filesystems) */
FUNDEF NONNULL((1)) void
NOTHROW(KCALL fnode_v_wrattr_noop)(struct fnode *__restrict self);



/* Filesystem node. */
struct fnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : mfile                                  /* Underlying mem-file */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
	/* NOTE: `fn_file.mf_flags' may also contain `MFILE_FN_*' flags! */
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct mfile                fn_file;     /* Underlying mem-file */
#define _fnode_file_ fn_file.
#define _fnode_asfile(x) &(x)->fn_file
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fnode_file_     /* nothing */
#define _fnode_asfile(x) x
#endif /* !__WANT_FS_INLINE_STRUCTURES */
#ifdef __WANT_FS_INIT
#define FNODE_INIT_fn_nlink(fn_nlink)  fn_nlink
#define FNODE_INIT_fn_mode(fn_mode)    fn_mode
#define FNODE_INIT_fn_uid(fn_uid)      fn_uid
#define FNODE_INIT_fn_gid(fn_gid)      fn_gid
#define FNODE_INIT_fn_ino(fn_ino)      fn_ino
#define FNODE_INIT_fn_super(fn_super)  fn_super
#define FNODE_INIT_fn_allnodes         { LIST_ENTRY_UNBOUND_INITIALIZER }
#define FNODE_INIT_fn_allnodes_EX(...) { __VA_ARGS__ }
#define FNODE_INIT_fn_allsuper_EX(...) { .fn_allsuper = __VA_ARGS__ }
#endif /* __WANT_FS_INIT */
	nlink_t                     fn_nlink;    /* [lock(_MFILE_F_SMP_TSLOCK)][<= fn_super->fs_feat.sf_link_max] INode link counter. */
	mode_t                      fn_mode;     /* [lock(_MFILE_F_SMP_TSLOCK)] INode access mode (but note that file-type bits are [const]). */
	uid_t                       fn_uid;      /* [lock(_MFILE_F_SMP_TSLOCK)][valid_if(!npo_getown)] INode owner UID. */
	gid_t                       fn_gid;      /* [lock(_MFILE_F_SMP_TSLOCK)][valid_if(!npo_getown)] INode owner GID. */
	ino_t                       fn_ino;      /* [lock(_MFILE_F_SMP_TSLOCK + fn_super->fs_nodeslock)] INode         number.
	                                          * On some filesystems, this number may change when the file is renamed (e.g.
	                                          * FAT). As such, a lock is  required when reading/writing the INode  number! */
	REF_IF(!fnode_issuper(this))
	struct fsuper              *fn_super;    /* [1..1][const] Associated super-block. */
#ifdef __WANT_FNODE__fn_chnglop
	union {
		LIST_ENTRY(REF fnode)   fn_changed;  /* [0..1][lock(fn_super->fs_changednodes_lock)][LIST(fn_super->fs_changednodes)]
		                                      * Link entry in the list of changed file-nodes. */
		Toblockop(fsuper)      _fn_chnglop;  /* Used internally... */
	};
#ifdef __WANT_FS_INIT
#define FNODE_INIT_fn_changed         { LIST_ENTRY_UNBOUND_INITIALIZER }
#define FNODE_INIT_fn_changed_EX(...) { __VA_ARGS__ }
#endif /* __WANT_FS_INIT */
#else /* __WANT_FNODE__fn_chnglop */
	LIST_ENTRY(REF fnode)       fn_changed;  /* [0..1][lock(fn_super->fs_changednodes_lock)][LIST(fn_super->fs_changednodes)]
	                                          * Link entry in the list of changed file-nodes. */
#ifdef __WANT_FS_INIT
#define FNODE_INIT_fn_changed         LIST_ENTRY_UNBOUND_INITIALIZER
#define FNODE_INIT_fn_changed_EX(...) __VA_ARGS__
#endif /* __WANT_FS_INIT */
#endif /* !__WANT_FNODE__fn_chnglop */
#ifdef __WANT_FNODE__fn_suplop
	union {
		Toblockop(fsuper)      _fn_suplop;   /* Used for `fnode_add2sup_lop' */
		LLRBTREE_NODE(fnode)    fn_supent;   /* ... */
	};
#ifdef __WANT_FS_INIT
#define FNODE_INIT_fn_supent           { { __NULLPTR, FSUPER_NODES_DELETED } }
#define FNODE_INIT_fn_supent_EX(...)   { __VA_ARGS__ }
#endif /* __WANT_FS_INIT */
#else /* __WANT_FNODE__fn_suplop */
#ifdef __WANT_FS_INIT
#define FNODE_INIT_fn_supent           { __NULLPTR, FSUPER_NODES_DELETED }
#define FNODE_INIT_fn_supent_EX(...)   __VA_ARGS__
#endif /* __WANT_FS_INIT */
	LLRBTREE_NODE(fnode)        fn_supent;   /* [lock(fn_super->fs_nodeslock)][LIST(fn_super->fs_nodes)]
	                                          * Tree entry within the  super block's tree of  file-nodes.
	                                          * When  `rb_rhs' is set to `FSUPER_NODES_DELETED', then the
	                                          * file-node  is no longer apart of the super's tree of file
	                                          * nodes. In this case, the `MFILE_F_PERSISTENT' flag may be
	                                          * assumed to have already been cleared. */
#endif /* !__WANT_FNODE__fn_suplop */
#ifdef __WANT_FS_INIT
#define FNODE_INIT_fn_allnodes { LIST_ENTRY_UNBOUND_INITIALIZER }
#endif /* __WANT_FS_INIT */
	union {
		LIST_ENTRY(fnode)       fn_allnodes; /* [0..1][lock(:fnode_all_lock && REMOVE_ONCE)][valid_if(!fnode_issuper(self))]
		                                      * Link entry within the global list of all file nodes. When `MFILE_FN_GLOBAL_REF'
		                                      * is set, then the global  list holds a reference to  this node. (Even when  this
		                                      * link isn't bound) */
		LIST_ENTRY(fsuper)      fn_allsuper; /* [0..1][lock(:fsuper_all_lock && REMOVE_ONCE)][valid_if(fnode_issuper(self))]
		                                      * Link entry within the global list of all super blocks. When `MFILE_FN_GLOBAL_REF'
		                                      * is set, then  the global list  holds a reference  to this node.  (Even when  this
		                                      * link isn't bound) */
#ifdef __WANT_FNODE__fn_alllop
		struct lockop _fn_alllop; /* Lock operator used for async add-to-all-nodes */
#endif /* __WANT_FNODE__fn_alllop */
	};
#ifndef FNODE_FSDATA_T
#define FNODE_FSDATA_T void
#endif /* !FNODE_FSDATA_T */
#ifdef __WANT_FNODE_FSDATAINT
	union {
		uintptr_t      fn_fsdataint; /* Fs-specific data word as integer. */
		FNODE_FSDATA_T*fn_fsdata;    /* ... */
	};
#else /* __WANT_FNODE_FSDATAINT */
	FNODE_FSDATA_T    *fn_fsdata; /* [?..?][lock(?)] Optional,  fs-specific data  pointer or  data-word.
	                               * Since the different standard sub-classes of `fnode' have  different
	                               * struct sizes, it is normally quite difficult for filesystems to add
	                               * additional  data fields common to _all_ nodes (since the offset for
	                               * such data would be different for every node type). This is what you
	                               * can use this field for: have it point to somewhere else in the node
	                               * structure,  preferably to a fs-specific data blob which can then be
	                               * shared by _all_ nodes allocated for your filesystem. */
#endif /* !__WANT_FNODE_FSDATAINT */
};

#ifdef __WANT_FNODE__fn_alllop
/* For use with `_fn_alllop': asynchronously add the node to the list of all nodes.
 * This function needs to be exposed publicly because it being set requires special
 * care if set during custom fnode destructors.
 * Note that the default `fnode_v_destroy()' includes correct handling for this. */
FUNDEF NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC fnode_addtoall_lop)(struct lockop *__restrict self);
#endif /* __WANT_FNODE__fn_alllop */

#ifdef __WANT_FNODE__fn_suplop
/* For use with `_fn_suplop': The node is currently adding itself to the superblock
 * by  means of an asynchronous operation. NOTE: This lock operator unconditionally
 * inherits a reference  to `container_of(self, struct fnode, _fn_suplop)', and  as
 * such  you may assume that a fnode which  has been destroyed would no longer make
 * use of this.
 *
 * However, in situations where `fsuper_nodes_removenode(node)' is called, you  must
 * first check  if  `node->_fn_suplop.olo_func == &fnode_add2sup_lop',  and  if  so,
 * must  release your lock to the superblock before reacquiring it in order to allow
 * the node to fully add itself to the superblock's node tree so that you may safely
 * remove it later.
 *
 * Similarly, `fsuper_nodes_locate()' or `fsuper_nodes_remove()' returning NULL when
 * `fsuper_nodes_mustreap()' does not necessarily mean  that the node you're  trying
 * to lookup/remove doesn't exist; it may just be trying to add itself right now. */
FUNDEF NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC fnode_add2sup_lop)(Toblockop(fsuper) *__restrict self,
                                     struct fsuper *__restrict obj);
#endif /* __WANT_FNODE__fn_suplop */

/* Add the given node `self'  to the list of all  nodes. The caller must  ensure
 * that this function is _NOT_ called such that it would violate the REMOVE_ONCE
 * constraint  of `fn_allnodes'. Iow:  don't call this  function when `self' has
 * already become globally visible by some other means.
 *
 * This function can be used to initialize:
 *  - self->fn_allnodes
 * ... but  may only be called once _all_ other fields of `self' have already been
 *     initialized, and only if `self' isn't globally visible by some other means. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_init_addtoall)(struct fnode *__restrict self);

/* The async combination of adding `self' to its superblock's node tree, as  well
 * as to the global list of all nodes. The caller must ensure that `self->fn_ino'
 * isn't already in use any  other file-node. If another  node with the same  INO
 * number  already exists, said other node is  first removed from the INode tree.
 *
 * This function can be used to initialize:
 *  - self->fn_supent
 *  - self->fn_allnodes
 * ... but  may only be called once _all_ other fields of `self' have already been
 *     initialized, and only if `self' isn't globally visible by some other means,
 *     though the fields initialized  by this are pretty  much the only fields  by
 *     which nodes *normally* become globally visible. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_init_addtosuper_and_all)(struct fnode *__restrict self);


/* Return a pointer to file-node operators of `self' */
#define fnode_getops(self)                                                                       \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct fnode const *, self)->_fnode_file_ mf_ops, \
	                        struct fnode_ops, no_file)

#ifdef NDEBUG
#define _fnode_assert_ops_(ops) /* nothing */
#else /* NDEBUG */
#define _fnode_assert_ops_(ops) __hybrid_assert((ops)->no_file.mo_changed == &fnode_v_changed),
#endif /* !NDEBUG */

/* Common initializes for everything derived from `struct fnode' */
#define _fnode_init_common(self)              \
	(_mfile_init_common(_fnode_asfile(self)), \
	 LIST_ENTRY_UNBOUND_INIT(&(self)->fn_changed))
#define _fnode_cinit_common(self)              \
	(_mfile_cinit_common(_fnode_asfile(self)), \
	 __hybrid_assert(!LIST_ISBOUND(self, fn_changed)))


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_fnode_file_ mf_parts
 *  - self->_fnode_file_ mf_changed
 *  - self->_fnode_file_ mf_flags
 *  - self->_fnode_file_ mf_filesize
 *  - self->_fnode_file_ mf_atime
 *  - self->_fnode_file_ mf_mtime
 *  - self->_fnode_file_ mf_ctime
 *  - self->_fnode_file_ mf_btime
 *  - self->fn_uid
 *  - self->fn_gid
 *  - self->fn_nlink
 *  - self->fn_ino
 *  - self->fn_mode
 *  - self->fn_allnodes
 *  - self->fn_supent
 * @param: struct fnode     *self:  File-node to initialize.
 * @param: struct fnode_ops *ops:   File-node operators.
 * @param: struct fsuper    *super: Filesystem superblock. */
#define _fnode_init(self, ops, super)                                                                  \
	(_fnode_assert_ops_(ops) _fnode_init_common(self),                                                 \
	 (self)->_fnode_file_ mf_ops        = &(ops)->no_file,                                             \
	 (self)->_fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->fn_super                   = incref(super))
#define _fnode_cinit(self, ops, super)                                                                 \
	(_fnode_assert_ops_(ops) _fnode_cinit_common(self),                                                \
	 (self)->_fnode_file_ mf_ops        = &(ops)->no_file,                                             \
	 (self)->_fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->fn_super                   = incref(super))
/* Finalize a partially initialized `struct fnode' (as initialized by `_fnode_init()') */
#define _fnode_fini(self) decref_nokill((self)->fn_super)

/* Mandatory callback for all types derived from `struct fnode',
 * for  use with `mf_ops->mo_changed'.  MUST NOT BE OVERWRITTEN! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fnode_v_changed)(struct mfile *__restrict self,
                               uintptr_t old_flags, uintptr_t new_flags);

/* File-node  destroy callback. Must be set in `mo_destroy',
 * but may be overwritten by sub-classes, in which case this
 * function must be called as the last thing done within the
 * sub-class destroy-operator. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fnode_v_destroy)(struct mfile *__restrict self);
#define fnode_v_ioctl mfile_v_ioctl


/* Get the uid/gid of a given file-node. These functions respect `npo_getown' */
FUNDEF BLOCKING NONNULL((1)) uid_t KCALL fnode_getuid(struct fnode *__restrict self);
FUNDEF BLOCKING NONNULL((1)) gid_t KCALL fnode_getgid(struct fnode *__restrict self);
FUNDEF BLOCKING NONNULL((1, 2, 3)) void KCALL
fnode_getugid(struct fnode *__restrict self,
              uid_t *__restrict puid,
              gid_t *__restrict pgid);


/* High-level file-node functions */

/* Change permissions, SUID/SGID and the sticky bit of the given INode (flagsmask: 07777)
 * The new file mode is calculated as `(old_mode & perm_mask) | perm_flag', before  being
 * masked by what the underlying filesystem is capable of representing.
 * @return: * : The old file mode
 * @throw: E_FSERROR_READONLY:    The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
 * @throw: E_INSUFFICIENT_RIGHTS: `check_permissions' is true and you're not allowed to do this. */
FUNDEF BLOCKING NONNULL((1)) mode_t KCALL
fnode_chmod(struct fnode *__restrict self, mode_t perm_mask,
            mode_t perm_flag, __BOOL check_permissions DFL(1))
		THROWS(E_FSERROR_READONLY, E_INSUFFICIENT_RIGHTS);

/* Change the owner and group of the given file. NOTE: either attribute is only
 * altered when  `owner != (uid_t)-1'  and  `group != (gid_t)-1'  respectively.
 * @throw: E_FSERROR_READONLY:    The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
 * @throw: E_INSUFFICIENT_RIGHTS: `check_permissions' is true and you're not allowed to do this.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID:uid: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID:gid: [...] */
FUNDEF NONNULL((1)) void KCALL
fnode_chown(struct fnode *__restrict self, uid_t owner, gid_t group,
            NCX uid_t *pold_owner DFL(__NULLPTR),
            NCX gid_t *pold_group DFL(__NULLPTR),
            __BOOL check_permissions DFL(1))
		THROWS(E_SEGFAULT, E_FSERROR_READONLY, E_INSUFFICIENT_RIGHTS, E_INVALID_ARGUMENT_BAD_VALUE);

/* Change all non-NULL the timestamp that are given.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: The `MFILE_F_DELETED' is set.
 * @throw: E_FSERROR_READONLY: The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
 * @return: true:  File attributes were changed.
 * @return: false: File attributes remain unchanged (ctime wasn't updated). */
PUBLIC NONNULL((1)) __BOOL KCALL
mfile_chtime(struct mfile *__restrict self,
             struct timespec const *new_atime,
             struct timespec const *new_mtime,
             struct timespec const *new_btime)
		THROWS(E_FSERROR_READONLY);



/* Clear the `MFILE_F_ATTRCHANGED' flag and  remove `self' from the  associated
 * superblock's list of changed nodes. If this succeeds, invoke the `no_wrattr'
 * operator. If said operator returns  with an exception, set the  attr-changed
 * flag once again by means of `mfile_changed(self, MFILE_F_ATTRCHANGED)' */
FUNDEF BLOCKING NONNULL((1)) void KCALL
fnode_syncattr(struct fnode *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);

/* Clear the `MFILE_F_ATTRCHANGED' flag and remove `self' from the associated
 * superblock's list of changed nodes. If this succeeds, invoke `mfile_sync'.
 * If said function returns with an exception, set the attr-changed flag once
 * again by means of `mfile_changed(self, MFILE_F_ATTRCHANGED)' */
FUNDEF BLOCKING NONNULL((1)) void KCALL
fnode_syncdata(struct fnode *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);


/* Check if the calling thread is allowed to access `self' as described by `type'
 * @param: type:   Set of `R_OK | W_OK | X_OK' (all specified types must be allowed)
 * @return: true:  Access granted
 * @return: false: Access denied. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL fnode_mayaccess)(struct fnode *__restrict self,
                               unsigned int type);

/* Helper wrapper for `fnode_mayaccess()' that asserts access
 * and throws `E_FSERROR_ACCESS_DENIED' is access was denied.
 * @param: type: Set of `R_OK | W_OK | X_OK' (all specified types must be allowed)
 * @return:                         Access granted
 * @throw: E_FSERROR_ACCESS_DENIED: Access denied. */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
fnode_access(struct fnode *__restrict self, unsigned int type)
		THROWS(E_WOULDBLOCK, E_FSERROR_ACCESS_DENIED);


/* Perform all of the async work needed for deleting `self' as the result of `fn_nlink == 0'
 * This function will do the following (asynchronously if necessary)
 *  - Set flags: MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
 *               MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
 *               MFILE_F_FIXEDFILESIZE    |    MFILE_FN_ATTRREADONLY     |
 *               MFILE_F_NOUSRMMAP |  MFILE_F_NOUSRIO  |  MFILE_F_READONLY
 *    If `MFILE_F_DELETED' was already set, none of the below are done!
 *  - Unlink `self->fn_supent' (if bound)
 *  - Unlink `self->fn_changed' (if bound)
 *  - Unlink `self->fn_allnodes' (if bound)
 *  - Call `mfile_delete()' (technically `mfile_delete_impl()') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_delete)(struct fnode *__restrict self);

/* Internal implementation of `fnode_delete()' (don't call this one
 * unless you know that you're doing; otherwise, you may cause race
 * conditions that can result in data corruption) */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL fnode_delete_strt)(struct fnode *__restrict self);
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL fnode_delete_strt_with_tslock)(struct fnode *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_delete_impl)(/*inherit(always)*/ REF struct fnode *__restrict self);



/* Check if a given `struct fnode *self' is one of its many sub-classes. */
#define fnode_isreg(self)     S_ISREG((self)->fn_mode)
#define fnode_isdir(self)     S_ISDIR((self)->fn_mode)
#define fnode_issuper(self)   (_fdirnode_asnode(&(self)->fn_super->fs_root) == (self))
#define fnode_islnk(self)     S_ISLNK((self)->fn_mode)
#define fnode_isfifo(self)    S_ISFIFO((self)->fn_mode)
#define fnode_issock(self)    S_ISSOCK((self)->fn_mode)
#define fnode_isdevnode(self) S_ISDEV((self)->fn_mode)
#define fnode_isdevice(self)  (S_ISDEV((self)->fn_mode) && (self)->fn_super == _ramfs_super_assuper(&devfs) && (self)->_fnode_file_ mf_ops != &ramfs_devnode_ops.dvno_node.no_file)
#define fnode_ischrdev(self)  (S_ISCHR((self)->fn_mode) && (self)->fn_super == _ramfs_super_assuper(&devfs) && (self)->_fnode_file_ mf_ops != &ramfs_devnode_ops.dvno_node.no_file)
#define fnode_isblkdev(self)  (S_ISBLK((self)->fn_mode) && (self)->fn_super == _ramfs_super_assuper(&devfs) && (self)->_fnode_file_ mf_ops != &ramfs_devnode_ops.dvno_node.no_file)
#define fnode_isblkroot(self) (fnode_isblkdev(self) && !fnode_isblkpart(self))
#define fnode_isblkpart(self) mfile_isblkpart(_fnode_asfile(self))
#define fnode_asreg(self)     ((struct fregnode *)(self))
#define fnode_asdir(self)     ((struct fdirnode *)(self))
#define fnode_assuper(self)   __COMPILER_CONTAINER_OF(fnode_asdir(self), struct fsuper, fs_root)
#define fnode_aslnk(self)     ((struct flnknode *)(self))
#define fnode_asfifo(self)    ((struct ffifonode *)(self))
#define fnode_assock(self)    ((struct fsocknode *)(self))
#define fnode_asdevnode(self) ((struct fdevnode *)(self))
#define fnode_asdevice(self)  ((struct device *)(self))
#define fnode_aschrdev(self)  ((struct chrdev *)(self))
#define fnode_asblkdev(self)  ((struct blkdev *)(self))

/* Check if a given `struct mfile *self' is one of its many sub-classes. */
#define mfile_isnode(self)    ((self)->mf_ops->mo_changed == &fnode_v_changed)
#define mfile_isreg(self)     (mfile_isnode(self) && fnode_isreg(mfile_asnode(self)))
#define mfile_isdir(self)     (mfile_isnode(self) && fnode_isdir(mfile_asnode(self)))
#define mfile_issuper(self)   (mfile_isnode(self) && fnode_issuper(mfile_asnode(self)))
#define mfile_islnk(self)     (mfile_isnode(self) && fnode_islnk(mfile_asnode(self)))
#define mfile_isfifo(self)    (mfile_isnode(self) && fnode_isfifo(mfile_asnode(self)))
#define mfile_issock(self)    (mfile_isnode(self) && fnode_issock(mfile_asnode(self)))
#define mfile_isdevnode(self) (mfile_isnode(self) && fnode_isdevnode(mfile_asnode(self)))
#define mfile_isdevice(self)  (mfile_isnode(self) && fnode_isdevice(mfile_asnode(self)))
#define mfile_ischrdev(self)  (mfile_isnode(self) && fnode_ischrdev(mfile_asnode(self)))
#define mfile_isblkdev(self)  (mfile_isnode(self) && fnode_isblkdev(mfile_asnode(self)))
#define mfile_isblkroot(self) (mfile_isnode(self) && fnode_isblkroot(mfile_asnode(self)))
#define mfile_isblkpart(self) ((self)->mf_ops == &blkpart_ops.bdo_dev.do_node.dvno_node.no_file)
#define mfile_asnode(self)    ((struct fnode *)(self))
#define mfile_asreg(self)     fnode_asreg(mfile_asnode(self))
#define mfile_asdir(self)     fnode_asdir(mfile_asnode(self))
#define mfile_assuper(self)   fnode_assuper(mfile_asnode(self))
#define mfile_aslnk(self)     fnode_aslnk(mfile_asnode(self))
#define mfile_asfifo(self)    fnode_asfifo(mfile_asnode(self))
#define mfile_assock(self)    fnode_assock(mfile_asnode(self))
#define mfile_asdevnode(self) fnode_asdevnode(mfile_asnode(self))
#define mfile_asdevice(self)  fnode_asdevice(mfile_asnode(self))
#define mfile_aschrdev(self)  fnode_aschrdev(mfile_asnode(self))
#define mfile_asblkdev(self)  fnode_asblkdev(mfile_asnode(self))

/* Filenode tree operations. (for `struct fsuper::fs_nodes') */
struct fnode_tree_minmax {
	struct fnode *mm_min; /* [0..1] Lowest branch. */
	struct fnode *mm_max; /* [0..1] Greatest branch. */
};

FUNDEF NOBLOCK ATTR_PURE WUNUSED struct fnode *NOTHROW(FCALL fnode_tree_locate)(/*nullable*/ struct fnode *root, ino_t key);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL fnode_tree_tryinsert)(struct fnode **__restrict proot, struct fnode *__restrict node);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL fnode_tree_insert)(struct fnode **__restrict proot, struct fnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct fnode *NOTHROW(FCALL fnode_tree_remove)(struct fnode **__restrict proot, ino_t key);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL fnode_tree_removenode)(struct fnode **__restrict proot, struct fnode *__restrict node);
FUNDEF NOBLOCK NONNULL((4)) void NOTHROW(FCALL fnode_tree_minmaxlocate)(struct fnode *root, ino_t minkey, ino_t maxkey, struct fnode_tree_minmax *__restrict result);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_NODE_H */
