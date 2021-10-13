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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/devnode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/ramfs.h>
#include <kernel/types.h>

#include <hybrid/sequence/rbtree.h>

#include <kos/aref.h>
#include <kos/io.h>
#include <kos/lockop.h>

#ifdef __CC__
DECL_BEGIN

struct fdevfsnode;
struct fdevfsnode_ops {
	struct fdevnode_ops dfno_node; /* FNode operators */
	/* More operators would go here... */
};


/* Construct the INode number for a device file within `devfs.fs_nodes', given
 * that file's typing (`st_mode & S_IFMT' must be `S_IFCHR' or `S_IFBLK'),  as
 * well as the device number `st_rdev'. */
#if (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 8
#define devfs_devnode_makeino(st_mode, st_rdev) \
	((ino_t)(st_rdev) | ((ino_t)((st_mode) & 0x4000) << 49))
#elif (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 4
#define devfs_devnode_makeino(st_mode, st_rdev) \
	((ino_t)(st_rdev) | ((ino_t)((st_mode) & 0x4000) << 17))
#else /* ... */
#error "Unsupported configuration"
#endif /* !... */

AWREF(fdevfsnode_awref, fdevfsnode);

/* Directory entry descriptor for /dev/ device files */
struct fdevfsdirent {
	struct fdevfsnode_awref fdd_node;   /* [0..1] Weak reference to associated devfs node. */
	struct fdirent          fdd_dirent; /* Underlying directory entry. */
};

/* Operators for Instances of `struct fdevfsdirent' */
DATDEF struct fdirent_ops const fdevfsdirent_ops;

#define fdevfsdirent_destroy(self) fdirent_destroy(&(self)->fdd_dirent)
DEFINE_REFCOUNT_FUNCTIONS(struct fdevfsdirent, fdd_dirent.fd_refcnt, fdevfsdirent_destroy)



struct fdevfsnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdevnode                   /* Underlying dev-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdevnode dfn_devnode; /* Underlying dev-node */
#define _fdevfsnode_asdevnode(x) &(x)->dfn_devnode
#define _fdevfsnode_devnode_     dfn_devnode.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fdevfsnode_asdevnode(x) x
#define _fdevfsnode_devnode_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	/* NOTE: Devices files with the  `MFILE_F_DELETED' flag are not  enumerated
	 *       within `/dev/' or  other directories. As  such, "deleting" a  file
	 *       from the devfs is as simple as setting that flag. Furthermore, all
	 *       devfs files make use of the `MFILE_F_PERSISTENT' flag and possibly
	 *       the  `MFILE_FN_GLOBAL_REF' flag. No  other global references exist
	 *       for devfs device nodes, so to truly unload a device, do:
	 * >> REF struct fdevfsnode *somedev = get_device();
	 * >> ATOMIC_OR(somedev->mf_flags, MFILE_F_DELETED);
	 * >> if (ATOMIC_FETCHAND(somedev->mf_flags, ~MFILE_F_PERSISTENT) & MFILE_F_PERSISTENT)
	 * >>     decref(somedev);
	 * >> if (ATOMIC_FETCHAND(somedev->mf_flags, ~MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)
	 * >>     decref(somedev);
	 * >> decref(somedev);
	 * >> // At this point, the device will lazily unload itself. */
	REF struct fdevfsdirent *dfn_dirent;      /* [1..1][lock(:devfs_byname_lock)] Device directory entry (including its name) */
	RBTREE_NODE(fdevfsnode)  dfn_byname_node; /* [lock(:devfs_byname_lock)] By-name tree of devfs devices. */
};


/* Default operators for `struct fdevfsnode_ops' */

/* Destructor  (asynchronously  removes  itself  from
 * `devfs_byname_tree' and does `decref(dfn_dirent)') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fdevfsnode_v_destroy)(struct mfile *__restrict self);



/* Return a pointer to device-node operators of `self' */
#define fdevfsnode_getops(self) \
	((struct fdevfsnode_ops const *)__COMPILER_REQTYPE(struct fdevfsnode const *, self)->_fdevfsnode_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#define _fdevfsnode_assert_ops_(ops) \
	_fdevnode_assert_ops_(&(ops)->dfno_node)

/* Return a pointer to the name of the given devfs device node.
 * NOTE: The caller must be holding a lock to `devfs_byname_lock'! */
#define fdevfsnode_getname(self)    ((self)->dfn_dirent->fdd_dirent.fd_name)
#define fdevfsnode_getnamelen(self) ((self)->dfn_dirent->fdd_dirent.fd_namelen)


/* The /dev/ filesystem superblock */
DATDEF struct ramfs_super devfs;
DATDEF struct ffilesys devfs_filesys;

/* By-name lookup of devices in /dev/ */
DATDEF struct atomic_rwlock devfs_byname_lock;    /* Lock for `devfs_byname_tree' */
DATDEF struct lockop_slist devfs_byname_lops;     /* Lock operations for `devfs_byname_lock' */
DATDEF RBTREE_ROOT(fdevfsnode) devfs_byname_tree; /* [0..n][lock(devfs_byname_lock)] By-name tree of device files. */

/* Lock accessor helpers for `devfs_byname_lock' and `devfs_byname_tree' */
#define devfs_byname_reap()       lockop_reap_atomic_rwlock(&devfs_byname_lops, &devfs_byname_lock)
#define _devfs_byname_reap()      _lockop_reap_atomic_rwlock(&devfs_byname_lops, &devfs_byname_lock)
#define devfs_byname_write()      atomic_rwlock_write(&devfs_byname_lock)
#define devfs_byname_write_nx()   atomic_rwlock_write_nx(&devfs_byname_lock)
#define devfs_byname_trywrite()   atomic_rwlock_trywrite(&devfs_byname_lock)
#define devfs_byname_endwrite()   (atomic_rwlock_endwrite(&devfs_byname_lock), devfs_byname_reap())
#define _devfs_byname_endwrite()  atomic_rwlock_endwrite(&devfs_byname_lock)
#define devfs_byname_read()       atomic_rwlock_read(&devfs_byname_lock)
#define devfs_byname_read_nx()    atomic_rwlock_read_nx(&devfs_byname_lock)
#define devfs_byname_tryread()    atomic_rwlock_tryread(&devfs_byname_lock)
#define _devfs_byname_endread()   atomic_rwlock_endread(&devfs_byname_lock)
#define devfs_byname_endread()    (void)(atomic_rwlock_endread(&devfs_byname_lock) && (devfs_byname_reap(), 0))
#define _devfs_byname_end()       atomic_rwlock_end(&devfs_byname_lock)
#define devfs_byname_end()        (void)(atomic_rwlock_end(&devfs_byname_lock) && (devfs_byname_reap(), 0))
#define devfs_byname_upgrade()    atomic_rwlock_upgrade(&devfs_byname_lock)
#define devfs_byname_upgrade_nx() atomic_rwlock_upgrade_nx(&devfs_byname_lock)
#define devfs_byname_tryupgrade() atomic_rwlock_tryupgrade(&devfs_byname_lock)
#define devfs_byname_downgrade()  atomic_rwlock_downgrade(&devfs_byname_lock)
#define devfs_byname_reading()    atomic_rwlock_reading(&devfs_byname_lock)
#define devfs_byname_writing()    atomic_rwlock_writing(&devfs_byname_lock)
#define devfs_byname_canread()    atomic_rwlock_canread(&devfs_byname_lock)
#define devfs_byname_canwrite()   atomic_rwlock_canwrite(&devfs_byname_lock)

/* Devfs by-name tree operations. (For `devfs_byname_tree') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((2)) struct fdevfsnode *NOTHROW(FCALL devfs_bynametree_locate)(/*nullable*/ struct fdevfsnode *root, char const *__restrict key);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL devfs_bynametree_insert)(struct fdevfsnode **__restrict proot, struct fdevfsnode *__restrict node);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL devfs_bynametree_removenode)(struct fdevfsnode **__restrict proot, struct fdevfsnode *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct fdevfsnode *NOTHROW(FCALL devfs_bynametree_prevnode)(struct fdevfsnode const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct fdevfsnode *NOTHROW(FCALL devfs_bynametree_nextnode)(struct fdevfsnode const *__restrict self);

/* Helper macros for operating on `devfs_byname_tree' while holding the proper lock to `devfs_byname_lock' */
#define devfs_byname_locate(name)     devfs_bynametree_locate(devfs_byname_tree, name)
#define devfs_byname_insert(node)     devfs_bynametree_insert(&devfs_byname_tree, node)
#define devfs_byname_removenode(node) devfs_bynametree_removenode(&devfs_byname_tree, node)


/* Register a given device `self' within global control structures:
 *  - devfs_byname_tree
 *  - devfs.fs_nodes
 *  - fallnodes_list
 * This function never creates  additional references for `self',  but
 * leaves the job of setting up  global references (though use of  the
 * flags `MFILE_FN_GLOBAL_REF' and `MFILE_F_PERSISTENT') to the caller */
FUNDEF NONNULL((1)) unsigned int FCALL
devbuilder_register(struct fdevfsnode *__restrict self)
		THROWS(E_WOULDBLOCK);
#define DEVBUILDER_REGISTER_SUCCESS      0 /* Success. */
#define DEVBUILDER_REGISTER_EXISTS_DEVNO 1 /* Another device with the same mode+devno already exists. */
#define DEVBUILDER_REGISTER_EXISTS_NAME  2 /* Another device with the same name already exists. */



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_H */
