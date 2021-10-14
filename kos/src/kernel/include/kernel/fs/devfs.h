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
#include <kernel/types.h>

#include <hybrid/sequence/rbtree.h>

#include <kos/aref.h>
#include <kos/io.h>
#include <kos/kernel/paging.h>
#include <kos/lockop.h>

#ifdef __CC__
DECL_BEGIN

struct device;
struct device_ops {
	struct fdevnode_ops dfno_node; /* FNode operators */
	/* More operators would go here... */
};


/* Construct the INode number for a device file within `devfs.fs_nodes', given
 * that file's typing (`st_mode & S_IFMT' must be `S_IFCHR' or `S_IFBLK'),  as
 * well as the device number `st_rdev'. */
#if (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 8
#define devfs_devnode_makeino(st_mode, st_rdev) \
	(((ino_t)(st_rdev) << 3) | ((ino_t)((st_mode) & 0x4000) << 49) | (ino_t)7)
#elif (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 4
#define devfs_devnode_makeino(st_mode, st_rdev) \
	(((ino_t)(st_rdev) << 3) | ((ino_t)((st_mode) & 0x4000) << 17) | (ino_t)7)
#else /* ... */
#error "Unsupported configuration"
#endif /* !... */

AWREF(device_awref, device);

/* Directory entry descriptor for /dev/ device files */
struct fdevfsdirent {
	struct device_awref fdd_node;   /* [0..1] Weak reference to associated devfs node. */
	struct fdirent      fdd_dirent; /* Underlying directory entry. */
};

/* Operators for Instances of `struct fdevfsdirent' */
DATDEF struct fdirent_ops const fdevfsdirent_ops;

#define fdevfsdirent_destroy(self) fdirent_destroy(&(self)->fdd_dirent)
DEFINE_REFCOUNT_FUNCTIONS(struct fdevfsdirent, fdd_dirent.fd_refcnt, fdevfsdirent_destroy)



struct device
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdevnode                   /* Underlying dev-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdevnode dv_devnode; /* Underlying dev-node */
#define _device_asdevnode(x) &(x)->dv_devnode
#define _device_devnode_     dv_devnode.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _device_asdevnode(x) x
#define _device_devnode_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	/* NOTE: Devices files with the  `MFILE_F_DELETED' flag are not  enumerated
	 *       within `/dev/' or  other directories. As  such, "deleting" a  file
	 *       from the devfs is as simple as setting that flag. Furthermore, all
	 *       devfs files make use of  the `MFILE_FN_GLOBAL_REF' flag. No  other
	 *       global references exist for devfs device nodes, so to truly unload
	 *       a device, do:
	 * >> REF struct device *somedev = get_device();
	 * >> if (ATOMIC_FETCHAND(somedev->mf_flags, ~MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)
	 * >>     decref(somedev);
	 * >> mfile_delete(somedev); // This also sets the `MFILE_F_DELETED' flag
	 * >> decref(somedev);
	 * >> // At this point, the device will lazily unload itself. */
	REF struct driver       *dv_driver;      /* [1..1][const] The kernel driver implementing this device. */
	REF struct fdevfsdirent *dv_dirent;      /* [1..1][lock(:devfs_byname_lock)][const_if(wasdestroyed(this))]
	                                          * Device directory entry (including its name) */
	RBTREE_NODE(device)      dv_byname_node; /* [lock(:devfs_byname_lock)] By-name tree of devfs devices.
	                                          * When `.rb_lhs == DEVICE_BYNAME_DELETED', then this  entry
	                                          * has been deleted. */
#define DEVICE_BYNAME_DELETED ((struct device *)-1)
};

#ifdef __WANT_FS_INLINE_STRUCTURES
#define __device_destroy(self) mfile_destroy(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(self))))
__DEFINE_REFCOUNT_FUNCTIONS(struct device,
                            _device_devnode_ _fdevnode_node_ _fnode_file_ mf_refcnt,
                            __device_destroy)
#endif /* __WANT_FS_INLINE_STRUCTURES */

/* Default operators for `struct device_ops' */

/* Destructor (asynchronously  removes  itself  from
 * `devfs_byname_tree' and does `decref(dv_dirent)') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL device_v_destroy)(struct mfile *__restrict self);



/* Return a pointer to device-node operators of `self' */
#define device_getops(self) \
	((struct device_ops const *)__COMPILER_REQTYPE(struct device const *, self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#define _device_assert_ops_(ops) \
	_fdevnode_assert_ops_(&(ops)->dfno_node)

/* Return a pointer to the name of the given devfs device node.
 * NOTE: The caller must be holding a lock to `devfs_byname_lock'! */
#define device_getname(self)    ((self)->dv_dirent->fdd_dirent.fd_name)
#define device_getnamelen(self) ((self)->dv_dirent->fdd_dirent.fd_namelen)



/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_part_amask
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_atime
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_mtime
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ctime
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->_device_devnode_ _fdevnode_node_ fn_ino
 *  - self->_device_devnode_ _fdevnode_node_ fn_mode (with something or'd with S_IFCHR or S_IFBLK)
 *  - self->_device_devnode_ dn_devno
 *  - self->dv_driver
 *  - self->dv_dirent
 *  - self->dv_byname_node
 * @param: struct device     *self:  Regular node to initialize.
 * @param: struct device_ops *ops:   Regular file operators. */
#define _device_init(self, ops)                                                                         \
	(_device_assert_ops_(ops) _fnode_init_common(_device_asdevnode(_fdevnode_asnode(self))),            \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops = &(ops)->dfno_node.dno_node.no_file, \
	 (self)->_device_devnode_ _fdevnode_node_ fn_super            = incref(&_devfs_super),              \
	 (self)->_device_devnode_ fn_nlink                            = 1,                                  \
	 (self)->_device_devnode_ fn_uid                              = 0,                                  \
	 (self)->_device_devnode_ fn_gid                              = 0)
#define _device_cinit(self, ops)                                                                         \
	(_device_assert_ops_(ops) _fnode_cinit_common(_device_asdevnode(_fdevnode_asnode(self))),           \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops = &(ops)->dfno_node.dno_node.no_file, \
	 (self)->_device_devnode_ _fdevnode_node_ fn_super            = incref(&_devfs_super),              \
	 (self)->_device_devnode_ fn_nlink                            = 1,                                  \
	 __hybrid_assert((self)->_device_devnode_ fn_uid == 0),                                             \
	 __hybrid_assert((self)->_device_devnode_ fn_gid == 0))

/* Finalize a partially initialized `struct device' (as initialized by `_device_init()') */
#define _device_fini(self) decref_nokill(&_devfs_super)






/* The /dev/ filesystem superblock */
struct ramfs_super; /* From `<kernel/fs/ramfs.h>' */
DATDEF struct ramfs_super devfs;
DATDEF struct fsuper _devfs_super ASMNAME("devfs");
DATDEF struct ffilesys devfs_filesys;

/* By-name lookup of devices in /dev/ */
struct shared_rwlock;
DATDEF struct shared_rwlock devfs_byname_lock;    /* Lock for `devfs_byname_tree' */
DATDEF struct lockop_slist devfs_byname_lops;     /* Lock operations for `devfs_byname_lock' */
DATDEF RBTREE_ROOT(device) devfs_byname_tree; /* [0..n][lock(devfs_byname_lock)] By-name tree of device files. */

/* Lock accessor helpers for `devfs_byname_lock' and `devfs_byname_tree' */
FUNDEF NOBLOCK void KCALL _devfs_byname_reap(void);
#ifdef __OPTIMIZE_SIZE__
#define devfs_byname_reap() _devfs_byname_reap()
#else /* __OPTIMIZE_SIZE__ */
#define devfs_byname_reap() (void)(!lockop_mustreap(&devfs_byname_lops) || (_devfs_byname_reap(), 0))
#endif /* !__OPTIMIZE_SIZE__ */
#define devfs_byname_write()      shared_rwlock_write(&devfs_byname_lock)
#define devfs_byname_write_nx()   shared_rwlock_write_nx(&devfs_byname_lock)
#define devfs_byname_trywrite()   shared_rwlock_trywrite(&devfs_byname_lock)
#define devfs_byname_endwrite()   (shared_rwlock_endwrite(&devfs_byname_lock), devfs_byname_reap())
#define _devfs_byname_endwrite()  shared_rwlock_endwrite(&devfs_byname_lock)
#define devfs_byname_read()       shared_rwlock_read(&devfs_byname_lock)
#define devfs_byname_read_nx()    shared_rwlock_read_nx(&devfs_byname_lock)
#define devfs_byname_tryread()    shared_rwlock_tryread(&devfs_byname_lock)
#define _devfs_byname_endread()   shared_rwlock_endread(&devfs_byname_lock)
#define devfs_byname_endread()    (void)(shared_rwlock_endread(&devfs_byname_lock) && (devfs_byname_reap(), 0))
#define _devfs_byname_end()       shared_rwlock_end(&devfs_byname_lock)
#define devfs_byname_end()        (void)(shared_rwlock_end(&devfs_byname_lock) && (devfs_byname_reap(), 0))
#define devfs_byname_upgrade()    shared_rwlock_upgrade(&devfs_byname_lock)
#define devfs_byname_upgrade_nx() shared_rwlock_upgrade_nx(&devfs_byname_lock)
#define devfs_byname_tryupgrade() shared_rwlock_tryupgrade(&devfs_byname_lock)
#define devfs_byname_downgrade()  shared_rwlock_downgrade(&devfs_byname_lock)
#define devfs_byname_reading()    shared_rwlock_reading(&devfs_byname_lock)
#define devfs_byname_writing()    shared_rwlock_writing(&devfs_byname_lock)
#define devfs_byname_canread()    shared_rwlock_canread(&devfs_byname_lock)
#define devfs_byname_canwrite()   shared_rwlock_canwrite(&devfs_byname_lock)

/* Devfs by-name tree operations. (For `devfs_byname_tree') */
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL devfs_bynametree_insert)(struct device **__restrict proot, struct device *__restrict node);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL devfs_bynametree_removenode)(struct device **__restrict proot, struct device *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct device *NOTHROW(FCALL devfs_bynametree_prevnode)(struct device const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct device *NOTHROW(FCALL devfs_bynametree_nextnode)(struct device const *__restrict self);

/* Helper macros for operating on `devfs_byname_tree' while holding the proper lock to `devfs_byname_lock' */
FUNDEF ATTR_PURE WUNUSED struct device *FCALL
devfs_byname_locate(USER CHECKED char const *name, u16 namelen) THROWS(E_SEGFAULT);
FUNDEF ATTR_PURE WUNUSED struct device *FCALL
devfs_byname_caselocate(USER CHECKED char const *name, u16 namelen) THROWS(E_SEGFAULT);
#define devfs_byname_insert(node)     devfs_bynametree_insert(&devfs_byname_tree, node)
#define devfs_byname_removenode(node) devfs_bynametree_removenode(&devfs_byname_tree, node)


/* Register a given device `self' within global control structures:
 *  - devfs_byname_tree
 *  - devfs.fs_nodes
 *  - fallnodes_list
 * This  function never creates additional references for `self',
 * but leaves the job of setting up global references (though use
 * of the flags `MFILE_FN_GLOBAL_REF') to the caller */
FUNDEF NONNULL((1)) unsigned int FCALL
device_register(struct device *__restrict self)
		THROWS(E_WOULDBLOCK);
#define DEVBUILDER_REGISTER_SUCCESS      0 /* Success. */
#define DEVBUILDER_REGISTER_EXISTS_DEVNO 1 /* Another device with the same mode+devno already exists. */
#define DEVBUILDER_REGISTER_EXISTS_NAME  2 /* Another device with the same name already exists. */


/* Unregister a given device node from /dev/ and devfs's inode tree, and proceed
 * to call `mfile_delete()'. This process is done asynchronously and can be used
 * to  delete device files  in situations where  devices disappear, or something
 * similar happened.
 *
 * Also note that what this function does, userspace can do as well by issuing
 * a call to `unlink("/dev/<device-file-name>")' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL device_delete)(struct device *__restrict self);


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_H */
