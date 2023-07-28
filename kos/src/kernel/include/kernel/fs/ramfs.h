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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_RAMFS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_RAMFS_H 1

#include <kernel/compiler.h>

#include <kernel/fs/clnknode.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/fifonode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/regnode.h>
#include <kernel/fs/socknode.h>
#include <kernel/fs/super.h>
#include <kernel/types.h>

#include <hybrid/sequence/rbtree.h>

#include <kos/aref.h>
#include <kos/lockop.h>
#include <kos/sched/shared-rwlock.h>

#ifdef __CC__
DECL_BEGIN

#define ramfs_lnknode            clnknode /* Same type... */
#define _ramfs_lnknode_lnode_    _clnknode_lnode_
#define _ramfs_lnknode_aslnknode _clnknode_aslnknode
#define _ramfs_lnknode_alloc     _clnknode_alloc
#define _ramfs_lnknode_new       _clnknode_new
#define _ramfs_lnknode_destroy   _clnknode_destroy
DATDEF struct flnknode_ops const ramfs_lnknode_ops;
#define ramfs_lnknode_v_readlink clnknode_v_readlink
#define ramfs_lnknode_v_linkstr  clnknode_v_linkstr
#define ramfs_lnknode_v_wrattr   fnode_v_wrattr_noop
#define ramfs_lnknode_v_changed  clnknode_v_changed
#define ramfs_lnknode_v_destroy  clnknode_v_destroy


#define ramfs_regnode              fregnode /* Same type... */
#define _ramfs_regnode_asnode      _fregnode_asnode
#define _ramfs_regnode_node_       _fregnode_node_
#define ramfs_regnode_getops       fregnode_getops
#define _ramfs_regnode_assert_ops_ _fregnode_assert_ops_
#define _ramfs_regnode_init        _fregnode_init
#define _ramfs_regnode_cinit       _fregnode_cinit
#define _ramfs_regnode_fini        _fregnode_fini
DATDEF struct fregnode_ops const ramfs_regnode_ops;
#define ramfs_regnode_v_wrattr  fnode_v_wrattr_noop
#define ramfs_regnode_v_changed fregnode_v_changed
#define ramfs_regnode_v_destroy fregnode_v_destroy


#define ramfs_devnode              fdevnode /* Same type... */
#define _ramfs_devnode_asnode      _fdevnode_asnode
#define _ramfs_devnode_node_       _fdevnode_node_
#define ramfs_devnode_getops       fdevnode_getops
#define _ramfs_devnode_assert_ops_ _fdevnode_assert_ops_
#define _ramfs_devnode_init        _fdevnode_init
#define _ramfs_devnode_cinit       _fdevnode_cinit
#define _ramfs_devnode_fini        _fdevnode_fini
DATDEF struct fdevnode_ops const ramfs_devnode_ops;
#define ramfs_devnode_v_open    fdevnode_v_open
#define ramfs_devnode_v_ioctl   fdevnode_v_ioctl
#define ramfs_devnode_v_wrattr  fnode_v_wrattr_noop
#define ramfs_devnode_v_changed fdevnode_v_changed
#define ramfs_devnode_v_destroy fdevnode_v_destroy


#define ramfs_fifonode              ffifonode /* Same type... */
#define _ramfs_fifonode_asnode      _ffifonode_asnode
#define _ramfs_fifonode_node_       _ffifonode_node_
#define ramfs_fifonode_getops       ffifonode_getops
#define _ramfs_fifonode_assert_ops_ _ffifonode_assert_ops_
#define _ramfs_fifonode_init        _ffifonode_init
#define _ramfs_fifonode_cinit       _ffifonode_cinit
#define _ramfs_fifonode_fini        _ffifonode_fini
DATDEF struct ffifonode_ops const ramfs_fifonode_ops;
#define ramfs_fifonode_v_open     ffifonode_v_open
#define ramfs_fifonode_v_read     ffifonode_v_read
#define ramfs_fifonode_v_readv    ffifonode_v_readv
#define ramfs_fifonode_v_write    ffifonode_v_write
#define ramfs_fifonode_v_writev   ffifonode_v_writev
#define ramfs_fifonode_v_truncate ffifonode_v_truncate
#define ramfs_fifonode_v_stat     ffifonode_v_stat
#define ramfs_fifonode_v_ioctl    ffifonode_v_ioctl
#define ramfs_fifonode_v_wrattr   fnode_v_wrattr_noop
#define ramfs_fifonode_v_changed  ffifonode_v_changed
#define ramfs_fifonode_v_destroy  ffifonode_v_destroy


#define ramfs_socknode              fsocknode /* Same type... */
#define _ramfs_socknode_asnode      _fsocknode_asnode
#define _ramfs_socknode_node_       _fsocknode_node_
#define ramfs_socknode_getops       fsocknode_getops
#define _ramfs_socknode_assert_ops_ _fsocknode_assert_ops_
#define _ramfs_socknode_init        _fsocknode_init
#define _ramfs_socknode_cinit       _fsocknode_cinit
#define _ramfs_socknode_fini        _fsocknode_fini
DATDEF struct fsocknode_ops const ramfs_socknode_ops;
#define ramfs_socknode_v_open     fsocknode_v_open
#define ramfs_socknode_v_ioctl    fsocknode_v_ioctl
#define ramfs_socknode_v_wrattr   fnode_v_wrattr_noop
#define ramfs_socknode_v_changed  fsocknode_v_changed
#define ramfs_socknode_v_destroy  fsocknode_v_destroy



struct ramfs_dirent {
	uintptr_t                     rde_isred;    /* [lock(:rdn_dat.rdd_lock)] Red/black word (0: black; 1: red) */
#ifdef __WANT_RAMFS_DIRENT__rde_dead
	union {
		RBTREE_NODE(REF ramfs_dirent)      rde_treenode; /* ... (see below) */
		struct {
			void *_rde_pad[2];                           /* Padding... */
			SLIST_ENTRY(REF ramfs_dirent) _rde_dead;     /* Used internally. */
		};
	};
#else /* __WANT_RAMFS_DIRENT__rde_dead */
	RBTREE_NODE(REF ramfs_dirent) rde_treenode; /* [0..1][lock(:rdn_dat.rdd_lock)] File tree.
	                                             * When `.rb_lhs == RAMFS_DIRENT_TREENODE_DELETED', then this dirent has been deleted. */
#endif /* !__WANT_RAMFS_DIRENT__rde_dead */
#define RAMFS_DIRENT_TREENODE_DELETED ((REF struct ramfs_dirent *)-1)
	REF struct fnode             *rde_node;     /* [1..1][const] Bound file-node (NOTE: This field also holds a  reference
	                                             * to `->fn_nlink', which is decremented when this structure is "unlinked"
	                                             * from its containing directory `rde_dir') */
	struct fdirent                rde_ent;      /* Underlying directory entry. */
};

/* Directory entry operators for instances of `ramfs_dirent' */
DATDEF struct fdirent_ops const ramfs_dirent_ops;
FUNDEF NOBLOCK NONNULL((1)) void /* == ramfs_dirent_ops.fdo_destroy */
NOTHROW(KCALL ramfs_dirent_v_destroy)(struct fdirent *__restrict self);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct fnode * /* == ramfs_dirent_ops.fdo_opennode */
NOTHROW(KCALL ramfs_dirent_v_opennode)(struct fdirent *__restrict self, struct fdirnode *__restrict dir);
#define _struct_ramfs_dirent_destroy(self) ramfs_dirent_v_destroy(&(self)->rde_ent)
DEFINE_REFCNT_FUNCTIONS(struct ramfs_dirent, rde_ent.fd_refcnt, _struct_ramfs_dirent_destroy)


/* Extended directory data. */
struct ramfs_dirnode;
struct ramfs_dirdata {
	struct shared_rwlock           rdd_lock; /* Lock for `rdd_tree' */
#ifdef __INTELLISENSE__
#ifdef __cplusplus
	_Toblockop_slist<struct ramfs_dirnode>
	                               rdd_lops; /* [0..n] Lockops for `rdd_lock' */
#else /* __cplusplus */
	struct oblockop_slist          rdd_lops; /* [0..n] Lockops for `rdd_lock' */
#endif /* !__cplusplus */
#else /* __INTELLISENSE__ */
	Toblockop_slist(ramfs_dirnode) rdd_lops; /* [0..n] Lockops for `rdd_lock' */
#endif /* !__INTELLISENSE__ */
	RBTREE_ROOT(REF ramfs_dirent)  rdd_tree; /* [0..n][lock(rdd_lock)] Files in this directory (using the filename as key). */
};

#define ramfs_dirdata_init(self)            \
	(shared_rwlock_init(&(self)->rdd_lock), \
	 SLIST_INIT(&(self)->rdd_lops),         \
	 (self)->rdd_tree = __NULLPTR)
#define ramfs_dirdata_cinit(self)                     \
	(shared_rwlock_cinit(&(self)->rdd_lock),          \
	 __hybrid_assert(SLIST_EMPTY(&(self)->rdd_lops)), \
	 __hybrid_assert((self)->rdd_tree == __NULLPTR))
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ramfs_dirdata_fini)(struct ramfs_dirdata *__restrict self);

/* Return the ramfs directory node containing a given `struct ramfs_dirdata' */
#define ramfs_dirdata_asdir(self) \
	COMPILER_CONTAINER_OF(self, struct ramfs_dirnode, rdn_dat)

/* Helpers for accessing `rdd_lock' */
#define /*        */ _ramfs_dirdata_lock_reap(self)        _oblockop_reap_shared_rwlock(&(self)->rdd_lops, &(self)->rdd_lock, ramfs_dirdata_asdir(self))
#define /*        */ ramfs_dirdata_lock_reap(self)         oblockop_reap_shared_rwlock(&(self)->rdd_lops, &(self)->rdd_lock, ramfs_dirdata_asdir(self))
#define /*        */ ramfs_dirdata_lock_mustreap(self)     oblockop_mustreap(&(self)->rdd_lops)
#define /*BLOCKING*/ ramfs_dirdata_lock_write(self)        shared_rwlock_write(&(self)->rdd_lock)
#define /*BLOCKING*/ ramfs_dirdata_lock_write_nx(self)     shared_rwlock_write_nx(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_trywrite(self)     shared_rwlock_trywrite(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_endwrite(self)     (shared_rwlock_endwrite(&(self)->rdd_lock), ramfs_dirdata_lock_reap(self))
#define /*        */ _ramfs_dirdata_lock_endwrite(self)    shared_rwlock_endwrite(&(self)->rdd_lock)
#define /*BLOCKING*/ ramfs_dirdata_lock_read(self)         shared_rwlock_read(&(self)->rdd_lock)
#define /*BLOCKING*/ ramfs_dirdata_lock_read_nx(self)      shared_rwlock_read_nx(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_tryread(self)      shared_rwlock_tryread(&(self)->rdd_lock)
#define /*        */ _ramfs_dirdata_lock_endread(self)     shared_rwlock_endread(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_endread(self)      (void)(shared_rwlock_endread(&(self)->rdd_lock) && (ramfs_dirdata_lock_reap(self), 0))
#define /*        */ _ramfs_dirdata_lock_end(self)         shared_rwlock_end(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_end(self)          (void)(shared_rwlock_end(&(self)->rdd_lock) && (ramfs_dirdata_lock_reap(self), 0))
#define /*BLOCKING*/ ramfs_dirdata_lock_upgrade(self)      shared_rwlock_upgrade(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_tryupgrade(self)   shared_rwlock_tryupgrade(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_downgrade(self)    shared_rwlock_downgrade(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_reading(self)      shared_rwlock_reading(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_writing(self)      shared_rwlock_writing(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_canread(self)      shared_rwlock_canread(&(self)->rdd_lock)
#define /*        */ ramfs_dirdata_lock_canwrite(self)     shared_rwlock_canwrite(&(self)->rdd_lock)
#define /*BLOCKING*/ ramfs_dirdata_lock_waitread(self)     shared_rwlock_waitread(&(self)->rdd_lock)
#define /*BLOCKING*/ ramfs_dirdata_lock_waitwrite(self)    shared_rwlock_waitwrite(&(self)->rdd_lock)
#define /*BLOCKING*/ ramfs_dirdata_lock_waitread_nx(self)  shared_rwlock_waitread_nx(&(self)->rdd_lock)
#define /*BLOCKING*/ ramfs_dirdata_lock_waitwrite_nx(self) shared_rwlock_waitwrite_nx(&(self)->rdd_lock)


/* Ramfs directory by-name tree operations. (For `struct ramfs_dirdata::rdd_tree') */
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL ramfs_direnttree_insert)(struct ramfs_dirent **__restrict proot, struct ramfs_dirent *__restrict node);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL ramfs_direnttree_removenode)(struct ramfs_dirent **__restrict proot, struct ramfs_dirent *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct ramfs_dirent *NOTHROW(FCALL ramfs_direnttree_prevnode)(struct ramfs_dirent const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct ramfs_dirent *NOTHROW(FCALL ramfs_direnttree_nextnode)(struct ramfs_dirent const *__restrict self);
FUNDEF ATTR_PURE WUNUSED struct ramfs_dirent *FCALL ramfs_direnttree_locate(/*nullable*/ struct ramfs_dirent *root, NCX char const *key, size_t keylen) THROWS(E_SEGFAULT);
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) struct ramfs_dirent *FCALL _ramfs_direnttree_caselocate(struct ramfs_dirent *__restrict root, NCX char const *key, size_t keylen) THROWS(E_SEGFAULT);
#define ramfs_direnttree_caselocate(root, key, keylen) ((root) ? _ramfs_direnttree_caselocate(root, key, keylen) : __NULLPTR)



/* Enumeration of ramfs directories. */
struct ramfs_dirent;
AXREF(ramfs_dirent_axref, ramfs_dirent);
struct ramfs_direnum
#ifdef __cplusplus
    : fdirenum                           /* Underlying enumerator */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirenum            rde_enum; /* Underlying enumerator */
#endif /* !__cplusplus */
	struct ramfs_dirent_axref  rde_next; /* [0..1][lock(ATOMIC)] Next directory entry to enumerate. */
	/* NOTE: The deleted-file-problem is solved for ramfs since we can enumerate the contents of
	 *       a  directory in alphabetical order (thanks to  the R/B-tree). When it's the current
	 *       file that got deleted, then we can still find the *correct* "next" file to yield by
	 *       searching for the next-greater node within the  tree that comes after the one  that
	 *       was deleted. Since compare is done lexicographically, and we've still got access to
	 *       the name of  the deleted file,  this is essentially  handled by "skipping"  deleted
	 *       files! */
};

/* Directory enumeration operators for `struct ramfs_direnum' */
DATDEF struct fdirenum_ops const ramfs_direnum_ops;
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_direnum_v_fini)(struct fdirenum *__restrict self);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL
ramfs_direnum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                        size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
		THROWS(E_SEGFAULT, E_WOULDBLOCK, ...);
FUNDEF BLOCKING NONNULL((1)) pos_t KCALL
ramfs_direnum_v_seekdir(struct fdirenum *__restrict self,
                        off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

/* Given a dirent `self' that has been deleted (RAMFS_DIRENT_TREENODE_DELETED),
 * return a pointer  to the first  dirent in `dir'  that has a  lexicographical
 * order `>= self'. The caller must be holding `dir->rdn_dat.rdd_lock' */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) struct ramfs_dirent *
NOTHROW(FCALL ramfs_dirent_fixdeleted)(struct ramfs_dirent *__restrict self,
                                       struct ramfs_dirnode *__restrict dir);



struct ramfs_dirnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdirnode                    /* Underlying directory */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdirnode      rdn_dir; /* Underlying directory */
#endif /* __WANT_FS_INLINE_STRUCTURES */
	struct ramfs_dirdata rdn_dat; /* Directory data */
};

/* Helpers for accessing `rdn_dat.rdd_lock' */
#define /*        */ _ramfs_dirnode_reap(self)        _ramfs_dirdata_lock_reap(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_reap(self)         ramfs_dirdata_lock_reap(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_mustreap(self)     ramfs_dirdata_lock_mustreap(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_write(self)        ramfs_dirdata_lock_write(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_write_nx(self)     ramfs_dirdata_lock_write_nx(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_trywrite(self)     ramfs_dirdata_lock_trywrite(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_endwrite(self)     ramfs_dirdata_lock_endwrite(&(self)->rdn_dat)
#define /*        */ _ramfs_dirnode_endwrite(self)    _ramfs_dirdata_lock_endwrite(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_read(self)         ramfs_dirdata_lock_read(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_read_nx(self)      ramfs_dirdata_lock_read_nx(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_tryread(self)      ramfs_dirdata_lock_tryread(&(self)->rdn_dat)
#define /*        */ _ramfs_dirnode_endread(self)     _ramfs_dirdata_lock_endread(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_endread(self)      ramfs_dirdata_lock_endread(&(self)->rdn_dat)
#define /*        */ _ramfs_dirnode_end(self)         _ramfs_dirdata_lock_end(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_end(self)          ramfs_dirdata_lock_end(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_upgrade(self)      ramfs_dirdata_lock_upgrade(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_tryupgrade(self)   ramfs_dirdata_lock_tryupgrade(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_downgrade(self)    ramfs_dirdata_lock_downgrade(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_reading(self)      ramfs_dirdata_lock_reading(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_writing(self)      ramfs_dirdata_lock_writing(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_canread(self)      ramfs_dirdata_lock_canread(&(self)->rdn_dat)
#define /*        */ ramfs_dirnode_canwrite(self)     ramfs_dirdata_lock_canwrite(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_waitread(self)     ramfs_dirdata_lock_waitread(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_waitwrite(self)    ramfs_dirdata_lock_waitwrite(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_waitread_nx(self)  ramfs_dirdata_lock_waitread_nx(&(self)->rdn_dat)
#define /*BLOCKING*/ ramfs_dirnode_waitwrite_nx(self) ramfs_dirdata_lock_waitwrite_nx(&(self)->rdn_dat)


/* Directory operators for `struct ramfs_dirnode' */
DATDEF struct fdirnode_ops const ramfs_dirnode_ops;
#define ramfs_dirnode_v_changed fdirnode_v_changed
#define ramfs_dirnode_v_wrattr  fnode_v_wrattr_noop
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_dirnode_v_destroy)(struct mfile *__restrict self);
#define ramfs_dirnode_v_open       fdirnode_v_open
#define ramfs_dirnode_v_stat       fdirnode_v_stat
#define ramfs_dirnode_v_stream_ops fdirnode_v_stream_ops
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
ramfs_dirnode_v_lookup(struct fdirnode *__restrict self,
                       struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK, ...);
FUNDEF NONNULL((1)) void KCALL
ramfs_dirnode_v_enum(struct fdirenum *__restrict result);
#define ramfs_dirnode_v_enumsz sizeof(struct ramfs_direnum)
FUNDEF BLOCKING NONNULL((1, 2)) unsigned int KCALL
ramfs_dirnode_v_mkfile(struct fdirnode *__restrict self,
                       struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DELETED,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...);
FUNDEF BLOCKING NONNULL((1, 2, 3)) unsigned int KCALL
ramfs_dirnode_v_unlink(struct fdirnode *__restrict self,
                       struct fdirent *__restrict entry,
                       struct fnode *__restrict file)
		THROWS(E_FSERROR_DIRECTORY_NOT_EMPTY, ...);
FUNDEF BLOCKING NONNULL((1, 2)) unsigned int KCALL
ramfs_dirnode_v_rename(struct fdirnode *__restrict self,
                       struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, ...);
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
FUNDEF BLOCKING NONNULL((1)) void KCALL
ramfs_dirnode_v_attach_notify(struct fdirnode *__restrict self)
		THROWS(E_BADALLOC, ...);
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */



/* Construct a new fully initialized, but not globally visible, as in:
 *   - return->fn_supent.rb_rhs == FSUPER_NODES_DELETED;
 *   - !LIST_ISBOUND(return, fn_allnodes);
 * ... node for use by ramfs file systems and return it.
 * When `(info->mkf_fmode & S_IFMT) == 0', blindly re-return `info->mkf_hrdlnk.hl_node'
 *
 * The  caller can always  assume that the  returned file-node can be
 * decref'd normally for the  purpose of (possible) destruction,  and
 * that `(info->mkf_fmode & S_IFMT) != 0' implies `!isshared(return)' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
ramfs_dirnode_mknode_frominfo(struct fdirnode *__restrict self,
                              struct fmkfile_info *__restrict info)
		THROWS(E_BADALLOC, E_FSERROR_UNSUPPORTED_OPERATION);



struct ramfs_super
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fsuper                     /* Underlying Superblock */
#define _ramfs_super_super_     /* nothing */
#define _ramfs_super_assuper(x) x
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fsuper        rs_sup; /* Underlying Superblock */
#define _ramfs_super_super_     rs_sup.
#define _ramfs_super_assuper(x) &(x)->rs_sup
#endif /* __WANT_FS_INLINE_STRUCTURES */
	struct ramfs_dirdata rs_dat; /* Directory data */
};

/* Return the root directory of a ramfs superblock as a ramfs_dirnode */
#define ramfs_super_asdir(self) \
	((struct ramfs_dirnode *)&(self)->_ramfs_super_super_ fs_root)


DATDEF struct fsuper_ops const ramfs_super_ops;
#define ramfs_super_v_free       fsuper_v_free
#define ramfs_super_v_changed    fsuper_v_changed
#define ramfs_super_v_open       ramfs_dirnode_v_open
#define ramfs_super_v_stream_ops ramfs_dirnode_v_stream_ops
#define ramfs_super_v_ioctl      fsuper_v_ioctl
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_super_v_destroy)(struct mfile *__restrict self);
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_super_v_delete)(REF struct fsuper *__restrict self);
#define ramfs_super_v_wrattr        ramfs_dirnode_v_wrattr
#define ramfs_super_v_lookup        ramfs_dirnode_v_lookup
#define ramfs_super_v_enumsz        ramfs_dirnode_v_enumsz
#define ramfs_super_v_enum          ramfs_dirnode_v_enum
#define ramfs_super_v_mkfile        ramfs_dirnode_v_mkfile
#define ramfs_super_v_unlink        ramfs_dirnode_v_unlink
#define ramfs_super_v_rename        ramfs_dirnode_v_rename
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#define ramfs_super_v_attach_notify ramfs_dirnode_v_attach_notify
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */

/* Top-level ram filesystem descriptor. */
DATDEF struct ffilesys ramfs_filesys;

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_RAMFS_H */
