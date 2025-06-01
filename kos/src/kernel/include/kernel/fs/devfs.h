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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_H 1

#include <kernel/compiler.h>

#include <kernel/fs/devnode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/super.h>
#include <kernel/types.h>

#include <hybrid/sequence/rbtree.h>

#include <bits/os/timespec.h>
#include <kos/aref.h>
#include <kos/uuid.h>
#include <kos/io.h> /* S_IFCHR, S_IFBLK */
#include <kos/kernel/paging.h>
#include <kos/lockop.h>
#include <sys/mkdev.h>


/* The  /dev filesystem contains files of a number of different types.
 * To differentiate between all of these, we use the least significant
 * few bits of the INO number. */
#define DEVFS_INONS_MASK 7 /* Mark for INO-NS */
#define DEVFS_INONS_RAM  0 /* Ramfs files */
#define DEVFS_INONS_SPEC 1 /* Fixed, special files (/dev/disk, /dev/block, etc...) */
#define DEVFS_INONS_DYN  2 /* Dynamically generated special files (/dev/char/1:1, etc...) */
#define DEVFS_INONS_DEV  7 /* Dynamically constructed device files */


/* Construct the INode number for a device file within `devfs.fs_nodes', given
 * that file's typing (`st_mode & S_IFMT' must be `S_IFCHR' or `S_IFBLK'),  as
 * well as the device number `st_rdev'. */
#if (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 8
#define devfs_devnode_makeino(st_mode, st_rdev) \
	((__CCAST(ino_t)(st_rdev) << 3) | (__CCAST(ino_t)((st_mode) & 0x4000) << 49) | __CCAST(ino_t)DEVFS_INONS_DEV)
#elif (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 4
#define devfs_devnode_makeino(st_mode, st_rdev) \
	((__CCAST(ino_t)(st_rdev) << 3) | (__CCAST(ino_t)((st_mode) & 0x4000) << 17) | __CCAST(ino_t)DEVFS_INONS_DEV)
#else /* ... */
#error "Unsupported configuration"
#endif /* !... */

#ifdef __CC__
DECL_BEGIN

struct device;
struct device_ops {
	struct fdevnode_ops do_node; /* FNode operators */
	/* More operators would go here... */
};


#ifndef __device_awref_defined
#define __device_awref_defined
AWREF(device_awref, device);
#endif /* !__device_awref_defined */

/* Directory entry descriptor for /dev/ device files */
struct devdirent {
	struct device_awref dd_dev;    /* [0..1] Weak reference to associated devfs node. */
	struct fdirent      dd_dirent; /* Underlying directory entry. */
};

/* Operators for Instances of `struct devdirent' */
DATDEF struct fdirent_ops const devdirent_ops;

#define devdirent_destroy(self) fdirent_destroy(&(self)->dd_dirent)
DEFINE_REFCNT_FUNCTIONS(struct devdirent, dd_dirent.fd_refcnt, devdirent_destroy)



struct device
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdevnode                        /* Underlying dev-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdevnode       dv_devnode; /* Underlying dev-node */
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
	 * >> if (atomic_fetchand(&somedev->mf_flags, ~MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)
	 * >>     decref(somedev);
	 * >> mfile_delete(somedev); // This also sets the `MFILE_F_DELETED' flag
	 * >> decref(somedev);
	 * >> // At this point, the device will lazily unload itself. */
	REF struct driver    *dv_driver;      /* [1..1][const] The kernel driver implementing this device. */
	REF struct devdirent *dv_dirent;      /* [1..1][lock(:devfs_byname_lock + _MFILE_F_SMP_TSLOCK)][const_if(wasdestroyed(this))]
	                                       * Device directory entry (including its name) */
	RBTREE_NODE(device)   dv_byname_node; /* [lock(:devfs_byname_lock)] By-name tree of devfs devices.
	                                       * When `.rb_lhs == DEVICE_BYNAME_DELETED', then this  entry
	                                       * has been deleted. */
#define DEVICE_BYNAME_DELETED ((struct device *)-1)
};

#ifdef __WANT_FS_INLINE_STRUCTURES
#define __struct_device_destroy(self) mfile_destroy(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(self))))
__DEFINE_REFCNT_FUNCTIONS(struct device, _device_devnode_ _fdevnode_node_ _fnode_file_ mf_refcnt, __struct_device_destroy)
#endif /* __WANT_FS_INLINE_STRUCTURES */

/* Default operators for `struct device_ops' */

/* Destructor (asynchronously  removes  itself  from
 * `devfs_byname_tree' and does `decref(dv_dirent)') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL device_v_destroy)(struct mfile *__restrict self);
#define device_v_wrattr  fnode_v_wrattr_noop
#define device_v_changed fdevnode_v_changed
#define device_v_ioctl   fdevnode_v_ioctl
/* Device files can be casted  into PATH and DIRENT  objects,
 * returning the mounting point for /dev/ and the name of the
 * device file. (Note that this even continues to work if the
 * device file has been unlink(2)'d from /dev/!) */
FUNDEF WUNUSED NONNULL((1)) REF void *KCALL
device_v_tryas(struct mfile *__restrict self,
               uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK);
/* Device stream operators (simply only devices `.mso_tryas = &device_v_tryas') */
DATDEF struct mfile_stream_ops const device_v_stream_ops;

/* Helper macros. */
#define device_isblk(self) S_ISBLK((self)->_device_devnode_ _fdevnode_node_ fn_mode)
#define device_ischr(self) S_ISCHR((self)->_device_devnode_ _fdevnode_node_ fn_mode)
#define device_asblk(self) ((struct blkdev *)(self))
#define device_aschr(self) ((struct chrdev *)(self))

/* Return a pointer to device-node operators of `self' */
#define device_getops(self) \
	((struct device_ops const *)__COMPILER_REQTYPE(struct device const *, self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#define _device_assert_ops_(ops) \
	_fdevnode_assert_ops_(&(ops)->do_node)

/* Return a pointer to the name of the given devfs device node.
 * NOTE: The caller must be holding a lock to `devfs_byname_lock' or `_MFILE_F_SMP_TSLOCK'! */
#define device_getname(self)    ((self)->dv_dirent->dd_dirent.fd_name)
#define device_getnamelen(self) ((self)->dv_dirent->dd_dirent.fd_namelen)
#define device_getdevno(self)   ((self)->_device_devnode_ dn_devno)
#define device_getmajor(self)   major(device_getdevno(self))
#define device_getminor(self)   minor(device_getdevno(self))

/* Helpers for acquiring a non-blocking SMP-lock for `device_getname()' */
#define device_getname_lock_acquire      mfile_tslock_acquire
#define device_getname_lock_release      mfile_tslock_release
#define device_getname_lock_acquire_nopr mfile_tslock_acquire_nopr
#define device_getname_lock_release_nopr mfile_tslock_release_nopr
#define device_getname_lock_acquire_br   mfile_tslock_acquire_br
#define device_getname_lock_release_br   mfile_tslock_release_br
#define device_getname_lock_tryacquire   mfile_tslock_tryacquire

/* Return a reference to the filename of `self' */
FUNDEF NOBLOCK ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct devdirent *
NOTHROW(FCALL device_getdevfsfilename)(struct device *__restrict self);
#define device_getfilename(self) (&device_getdevfsfilename(self)->dd_dirent)

#ifndef __realtime_defined
#define __realtime_defined
FUNDEF NOBLOCK WUNUSED struct timespec NOTHROW(KCALL realtime)(void);
#endif /* !__realtime_defined */



/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_changed
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_iobashift
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_part_amask
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes  # s.a. `device_registerf()'
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent    # s.a. `device_registerf()'
 *  - self->_device_devnode_ _fdevnode_node_ fn_ino       # s.a. `device_registerf()'
 *  - self->_device_devnode_ _fdevnode_node_ fn_mode      # Something or'd with S_IFCHR or S_IFBLK
 *  - self->_device_devnode_ dn_devno                     # s.a. `device_registerf()'
 *  - self->dv_driver                                     # As `incref(&drv_self)'
 *  - self->dv_dirent                                     # s.a. `device_registerf()'
 *  - self->dv_byname_node                                # s.a. `device_registerf()'
 * @param: struct device     *self:  Device to initialize.
 * @param: struct device_ops *ops:   Device operators. */
#define _device_init(self, ops)                                                                        \
	(_device_assert_ops_(ops) _fnode_init_common(_device_asdevnode(_fdevnode_asnode(self))),           \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops = &(ops)->do_node.dvno_node.no_file, \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_atime =                                  \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_mtime =                                  \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ctime =                                  \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_btime = realtime(),                      \
	 (self)->_device_devnode_ _fdevnode_node_ fn_super              = incref(&_devfs_super),           \
	 (self)->_device_devnode_ fn_nlink                              = 1,                               \
	 (self)->_device_devnode_ fn_uid                                = 0,                               \
	 (self)->_device_devnode_ fn_gid                                = 0)
#define _device_cinit(self, ops)                                                                       \
	(_device_assert_ops_(ops) _fnode_cinit_common(_device_asdevnode(_fdevnode_asnode(self))),          \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops = &(ops)->do_node.dvno_node.no_file, \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_atime =                                  \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_mtime =                                  \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ctime =                                  \
	 (self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_btime = realtime(),                      \
	 (self)->_device_devnode_ _fdevnode_node_ fn_super              = incref(&_devfs_super),           \
	 (self)->_device_devnode_ fn_nlink                              = 1,                               \
	 __hybrid_assert((self)->_device_devnode_ fn_uid == 0),                                            \
	 __hybrid_assert((self)->_device_devnode_ fn_gid == 0))

/* Finalize a partially initialized `struct device' (as initialized by `_device_init()') */
#define _device_fini(self) decref_nokill(&_devfs_super)






/* The /dev/ filesystem superblock */
struct ramfs_super; /* From `<kernel/fs/ramfs.h>' */
DATDEF struct ramfs_super devfs;
#define devfs_rootdir (*ramfs_super_asdir(&devfs))
DATDEF struct fsuper _devfs_super ASMNAME("devfs");
DATDEF struct ffilesys devfs_filesys;

/* By-name lookup of devices in /dev/ */
struct shared_rwlock;
DATDEF struct shared_rwlock devfs_byname_lock; /* Lock for `devfs_byname_tree' */
DATDEF struct lockop_slist devfs_byname_lops;  /* Lock operations for `devfs_byname_lock' */
DATDEF RBTREE_ROOT(device) devfs_byname_tree;  /* [0..n][lock(devfs_byname_lock)] By-name tree of device files. */

/* Lock accessor helpers for `devfs_byname_lock' and `devfs_byname_tree' */
FUNDEF NOBLOCK void NOTHROW(KCALL _devfs_byname_reap)(void);
#ifdef __OPTIMIZE_SIZE__
#define devfs_byname_reap() _devfs_byname_reap()
#else /* __OPTIMIZE_SIZE__ */
#define devfs_byname_reap() (void)(!lockop_mustreap(&devfs_byname_lops) || (_devfs_byname_reap(), 0))
#endif /* !__OPTIMIZE_SIZE__ */
#define /*BLOCKING*/ devfs_byname_write()        shared_rwlock_write(&devfs_byname_lock)
#define /*BLOCKING*/ devfs_byname_write_nx()     shared_rwlock_write_nx(&devfs_byname_lock)
#define /*        */ devfs_byname_trywrite()     shared_rwlock_trywrite(&devfs_byname_lock)
#define /*        */ devfs_byname_endwrite()     (shared_rwlock_endwrite(&devfs_byname_lock), devfs_byname_reap())
#define /*        */ _devfs_byname_endwrite()    shared_rwlock_endwrite(&devfs_byname_lock)
#define /*BLOCKING*/ devfs_byname_read()         shared_rwlock_read(&devfs_byname_lock)
#define /*BLOCKING*/ devfs_byname_read_nx()      shared_rwlock_read_nx(&devfs_byname_lock)
#define /*        */ devfs_byname_tryread()      shared_rwlock_tryread(&devfs_byname_lock)
#define /*        */ _devfs_byname_endread()     shared_rwlock_endread(&devfs_byname_lock)
#define /*        */ devfs_byname_endread()      (void)(shared_rwlock_endread(&devfs_byname_lock) && (devfs_byname_reap(), 0))
#define /*        */ _devfs_byname_end()         shared_rwlock_end(&devfs_byname_lock)
#define /*        */ devfs_byname_end()          (void)(shared_rwlock_end(&devfs_byname_lock) && (devfs_byname_reap(), 0))
#define /*BLOCKING*/ devfs_byname_upgrade()      shared_rwlock_upgrade(&devfs_byname_lock)
#define /*        */ devfs_byname_tryupgrade()   shared_rwlock_tryupgrade(&devfs_byname_lock)
#define /*        */ devfs_byname_downgrade()    shared_rwlock_downgrade(&devfs_byname_lock)
#define /*        */ devfs_byname_reading()      shared_rwlock_reading(&devfs_byname_lock)
#define /*        */ devfs_byname_writing()      shared_rwlock_writing(&devfs_byname_lock)
#define /*        */ devfs_byname_canread()      shared_rwlock_canread(&devfs_byname_lock)
#define /*        */ devfs_byname_canwrite()     shared_rwlock_canwrite(&devfs_byname_lock)
#define /*BLOCKING*/ devfs_byname_waitread()     shared_rwlock_waitread(&devfs_byname_lock)
#define /*BLOCKING*/ devfs_byname_waitwrite()    shared_rwlock_waitwrite(&devfs_byname_lock)
#define /*BLOCKING*/ devfs_byname_waitread_nx()  shared_rwlock_waitread_nx(&devfs_byname_lock)
#define /*BLOCKING*/ devfs_byname_waitwrite_nx() shared_rwlock_waitwrite_nx(&devfs_byname_lock)


/* Devfs by-name tree operations. (For `devfs_byname_tree') */
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL devfs_bynametree_insert)(struct device **__restrict proot, struct device *__restrict node);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL devfs_bynametree_removenode)(struct device **__restrict proot, struct device *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct device *NOTHROW(FCALL devfs_bynametree_prevnode)(struct device const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct device *NOTHROW(FCALL devfs_bynametree_nextnode)(struct device const *__restrict self);

/* Helper macros for operating on `devfs_byname_tree' while holding the proper lock to `devfs_byname_lock' */
FUNDEF ATTR_PURE WUNUSED struct device *FCALL
devfs_byname_locate(NCX char const *name, u16 namelen)
		THROWS(E_SEGFAULT);
FUNDEF ATTR_PURE WUNUSED struct device *FCALL
devfs_byname_caselocate(NCX char const *name, u16 namelen)
		THROWS(E_SEGFAULT);
#define devfs_byname_insert(node)     devfs_bynametree_insert(&devfs_byname_tree, node)
#define devfs_byname_removenode(node) devfs_bynametree_removenode(&devfs_byname_tree, node)


/* Register a given device `self' within global control structures:
 *  - devfs_byname_tree
 *  - devfs.fs_nodes
 *  - fallnodes_list
 * This  function never creates  additional references for `self',
 * but leaves the job of setting up global references (through use
 * of the `MFILE_FN_GLOBAL_REF' flag) to the caller.
 *
 * This function initializes (before making `self' globally visible):
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->dv_byname_node
 * @return: * : One of `DEVICE_TRYREGISTER_*' */
FUNDEF WUNUSED NONNULL((1)) unsigned int FCALL
device_tryregister(struct device *__restrict self)
		THROWS(E_WOULDBLOCK);
#define DEVICE_TRYREGISTER_SUCCESS      0 /* Success. */
#define DEVICE_TRYREGISTER_EXISTS_DEVNO 1 /* Another device with the same mode+devno already exists. */
#define DEVICE_TRYREGISTER_EXISTS_NAME  2 /* Another device with the same name already exists. */

/* Same as `device_tryregister()', but automatically handle duplicate dev_t and names:
 *  - If  the device's name already exists, mark the device's file as having been deleted,
 *    and don't add it to the by-name tree. As such, the device won't appear in /dev/, and
 *    accessing it will only be possible by creating a device node using its dev_t
 *  - If the device's `dev_t dn_devno'  (read: `ino_t fn_ino') already exists,  increment
 *    the device number by 1 and re-generate the `fn_ino', then try to add it once again.
 *
 * This function initializes (before making `self' globally visible):
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF; # and accompanying `++self->mf_refcnt'
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->dv_byname_node */
FUNDEF NONNULL((1)) void FCALL
device_register(struct device *__restrict self)
		THROWS(E_WOULDBLOCK);

/* The following are used internally to implement `device_register()' */
FUNDEF void FCALL _device_register_lock_acquire(__BOOL allnodes) THROWS(E_WOULDBLOCK);
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL _device_register_inuse_name)(char const *__restrict name, u16 len);
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(FCALL _device_register_inuse_ino)(ino_t ino);
FUNDEF NOBLOCK void NOTHROW(FCALL _device_register_lock_release)(__BOOL allnodes);


/* Helper wrapper for `device_register()' that sets a custom device name, and initialize:
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;      # and accompanying `++self->mf_refcnt'
 *  - self->_device_devnode_ _fdevnode_node_ fn_ino                 = devfs_devnode_makeino(fn_mode, dn_devno);
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes            = ...; # s.a. `device_register()'
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent              = ...; # s.a. `device_register()'
 *  - self->_device_devnode_ dn_devno                               = devno;
 *  - self->dv_byname_node                                          = ...; # s.a. `device_register()'
 *  - self->dv_dirent                                               = MAKE_DEVICE_NAME(format, ...); */
FUNDEF NONNULL((1)) void VCALL
device_registerf(struct device *__restrict self, dev_t devno,
                 char const *__restrict format, ...)
		THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF NONNULL((1)) void KCALL
device_vregisterf(struct device *__restrict self, dev_t devno,
                  char const *__restrict format, __builtin_va_list args)
		THROWS(E_BADALLOC, E_WOULDBLOCK);


/* Allocate a new devfs directory entry from the given format arguments.
 * The caller must still initialize:
 *  - return->dd_dev
 *  - return->dd_dirent.fd_ino
 *  - return->dd_dirent.fd_type */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct devdirent *FCALL
devdirent_vnewf(char const *__restrict format, __builtin_va_list args)
		THROWS(E_BADALLOC);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct devdirent *VCALL
devdirent_newf(char const *__restrict format, ...)
		THROWS(E_BADALLOC);


/* Unregister a given device node from /dev/ and devfs's inode tree, and proceed
 * to call `mfile_delete()'. This process is done asynchronously and can be used
 * to  delete device files  in situations where  devices disappear, or something
 * similar happened. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL device_delete)(struct device *__restrict self);


/* Lookup a device within devfs, given its INode number.
 * @return: NULL: No such device. */
FUNDEF WUNUSED REF struct device *FCALL
device_lookup_byino(ino_t ino) THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED REF struct device *
NOTHROW(FCALL device_lookup_byino_nx)(ino_t ino);

/* Lookup a device within devfs, given its device type and device number.
 * @param: st_mode: Either `S_IFCHR' or `S_IFBLK'
 * @param: st_rdev: Real device number (`makedev(...)')
 * @return: NULL: No such device. */
#define device_lookup_bydev(st_mode, st_rdev) \
	device_lookup_byino(devfs_devnode_makeino(st_mode, st_rdev))
#define device_lookup_bydev_nx(st_mode, st_rdev) \
	device_lookup_byino_nx(devfs_devnode_makeino(st_mode, st_rdev))

/* Helpers to lookup block/character devices. */
#define blkdev_lookup_bydev(st_rdev)    ((REF struct blkdev *)device_lookup_bydev(S_IFBLK, st_rdev))
#define chrdev_lookup_bydev(st_rdev)    ((REF struct chrdev *)device_lookup_bydev(S_IFCHR, st_rdev))
#define blkdev_lookup_bydev_nx(st_rdev) ((REF struct blkdev *)device_lookup_bydev_nx(S_IFBLK, st_rdev))
#define chrdev_lookup_bydev_nx(st_rdev) ((REF struct chrdev *)device_lookup_bydev_nx(S_IFCHR, st_rdev))

/* Lookup a device within devfs, given its name (and possibly type).
 * @param: name:    NUL-terminated device name string.
 * @param: st_mode: Either `0', `S_IFCHR' or `S_IFBLK'
 * @return: NULL: No such device. */
FUNDEF WUNUSED REF struct device *FCALL
device_lookup_byname(NCX char const *name,
                     size_t namelen, mode_t st_mode DFL(0))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

struct blkdev;

/* Lookup a block device partition  by its `bp_efi_partuuid'. Also  make
 * sure that in the event of a partition being found, no other partition
 * exists that has the same UUID. If anything other than exactly 1  part
 * is found, return `NULL'. */
FUNDEF WUNUSED NONNULL((1)) REF struct blkdev *FCALL
device_lookup_bypartuuid(uuid_t const *__restrict uuid)
		THROWS(E_WOULDBLOCK);

/* Slightly more advanced version of `device_lookup_byname()':
 *  #1: If str starts with "/dev/": string += 5; stringlen -= 5;
 *  #2: Pass `string' to `device_lookup_byname()', and re-return if non-NULL
 *  #3: if `!S_ISCHR(st_mode)' and `string' matches FORMAT_UUID_T, decode a
 *      UUID and make use of `device_lookup_bypartuuid'.
 *  #4: if `st_mode != 0', do `sscanf(string, "%u:%u")' for a major/minor
 *      pair, construct a dev_t, and pass to `device_lookup_bydev()', and
 *      re-return if non-NULL
 *  #5: If all else failed, return `NULL' */
FUNDEF WUNUSED REF struct device *FCALL
device_lookup_bystring(NCX char const *string,
                       size_t stringlen, mode_t st_mode DFL(0))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_H */
