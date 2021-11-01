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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_VFS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_VFS_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/types.h>
#include <sched/atomic64.h>
#include <sched/pertask.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/lockop.h>

#ifdef __CC__
DECL_BEGIN

struct path;
struct pathmount;
#ifndef __path_tailq_defined
#define __path_tailq_defined
TAILQ_HEAD(path_tailq, path);
#endif /* !__path_tailq_defined */
#ifndef __pathmount_list_defined
#define __pathmount_list_defined
LIST_HEAD(pathmount_list, pathmount);
#endif /* !__pathmount_list_defined */

#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */

#ifndef CONFIG_VFS_RECENT_MAX_DEFAULT
#define CONFIG_VFS_RECENT_MAX_DEFAULT 128
#endif /* !CONFIG_VFS_RECENT_MAX_DEFAULT */


/* # of different DOS drives. */
#define VFS_DRIVECOUNT  (('Z' - 'A') + 1)

/* VFS is the controller hub for mounting points and DOS drive roots,
 * as well  as keeper  of the  true filesystem  root mounting  point. */
struct vfs {
	WEAK refcnt_t             vf_refcnt;     /* Reference counter */
	WEAK refcnt_t             vf_weakrefcnt; /* Weak reference counter */
	REF struct path          *vf_root;       /* [1..1][lock(vf_rootlock)] True VFS root path. */
	struct atomic_rwlock      vf_rootlock;   /* Lock for `vf_root' */
	struct REF pathmount_list vf_mounts;     /* [0..n][lock(vf_mountslock)] List of mounting points. */
	struct atomic_lock        vf_mountslock; /* Lock for `vf_mounts' */
	struct REF path_tailq     vf_recent;     /* [0..n][lock(vf_recentlock)] List of recently used paths. */
	size_t                    vf_recentcnt;  /* [lock(vf_recentlock)] # of paths in `vf_recent' */
	WEAK size_t               vf_recentmax;  /* [lock(ATOMIC)] Max # of paths in `vf_recent'. When a new
	                                          * path becomes recently used that hasn't already been used
	                                          * recently, the least recently  used path is removed  from
	                                          * the cache if `vf_recentcnt >= vf_recentmax'. */
	struct atomic_lock        vf_recentlock; /* Lock for `vf_recent' */
	Toblockop_slist(vfs)      vf_recentlops; /* Lock operations for `vf_recentlock' */
	REF struct path          *vf_drives[VFS_DRIVECOUNT]; /* [0..1][lock(vf_driveslock)][*] DOS Drive roots. */
	struct atomic_rwlock      vf_driveslock; /* Lock for for DOS drives. */
};

#define vfs_free(self) __os_free(self)
DEFINE_WEAKREFCOUNT_FUNCTIONS(struct vfs, vf_weakrefcnt, vfs_free)

/* Destroy the given VFS controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vfs_destroy)(struct vfs *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct vfs, vf_refcnt, vfs_destroy)

/* Helper macros for working with `struct vfs::vf_rootlock' */
#define _vfs_rootlock_reap(self)        (void)0
#define vfs_rootlock_reap(self)         (void)0
#define vfs_rootlock_mustreap(self)     0
#define vfs_rootlock_write(self)        atomic_rwlock_write(&(self)->vf_rootlock)
#define vfs_rootlock_write_nx(self)     atomic_rwlock_write_nx(&(self)->vf_rootlock)
#define vfs_rootlock_trywrite(self)     atomic_rwlock_trywrite(&(self)->vf_rootlock)
#define vfs_rootlock_endwrite(self)     (atomic_rwlock_endwrite(&(self)->vf_rootlock), vfs_rootlock_reap(self))
#define _vfs_rootlock_endwrite(self)    atomic_rwlock_endwrite(&(self)->vf_rootlock)
#define vfs_rootlock_read(self)         atomic_rwlock_read(&(self)->vf_rootlock)
#define vfs_rootlock_read_nx(self)      atomic_rwlock_read_nx(&(self)->vf_rootlock)
#define vfs_rootlock_tryread(self)      atomic_rwlock_tryread(&(self)->vf_rootlock)
#define _vfs_rootlock_endread(self)     atomic_rwlock_endread(&(self)->vf_rootlock)
#define vfs_rootlock_endread(self)      (void)(atomic_rwlock_endread(&(self)->vf_rootlock) && (vfs_rootlock_reap(self), 0))
#define _vfs_rootlock_end(self)         atomic_rwlock_end(&(self)->vf_rootlock)
#define vfs_rootlock_end(self)          (void)(atomic_rwlock_end(&(self)->vf_rootlock) && (vfs_rootlock_reap(self), 0))
#define vfs_rootlock_upgrade(self)      atomic_rwlock_upgrade(&(self)->vf_rootlock)
#define vfs_rootlock_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->vf_rootlock)
#define vfs_rootlock_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->vf_rootlock)
#define vfs_rootlock_downgrade(self)    atomic_rwlock_downgrade(&(self)->vf_rootlock)
#define vfs_rootlock_reading(self)      atomic_rwlock_reading(&(self)->vf_rootlock)
#define vfs_rootlock_writing(self)      atomic_rwlock_writing(&(self)->vf_rootlock)
#define vfs_rootlock_canread(self)      atomic_rwlock_canread(&(self)->vf_rootlock)
#define vfs_rootlock_canwrite(self)     atomic_rwlock_canwrite(&(self)->vf_rootlock)
#define vfs_rootlock_waitread(self)     atomic_rwlock_waitread(&(self)->vf_rootlock)
#define vfs_rootlock_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->vf_rootlock)
#define vfs_rootlock_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->vf_rootlock)
#define vfs_rootlock_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->vf_rootlock)

/* Helper macros for `struct fsuper::vf_mountslock' */
#define _vfs_mountslock_reap(self)      (void)0
#define vfs_mountslock_reap(self)       (void)0
#define vfs_mountslock_mustreap(self)   0
#define vfs_mountslock_tryacquire(self) atomic_lock_tryacquire(&(self)->vf_mountslock)
#define vfs_mountslock_acquire(self)    atomic_lock_acquire(&(self)->vf_mountslock)
#define vfs_mountslock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->vf_mountslock)
#define _vfs_mountslock_release(self)   atomic_lock_release(&(self)->vf_mountslock)
#define vfs_mountslock_release(self)    (atomic_lock_release(&(self)->vf_mountslock), vfs_mountslock_reap(self))
#define vfs_mountslock_acquired(self)   atomic_lock_acquired(&(self)->vf_mountslock)
#define vfs_mountslock_available(self)  atomic_lock_available(&(self)->vf_mountslock)
#define vfs_mountslock_waitfor(self)    atomic_lock_waitfor(&(self)->vf_mountslock)
#define vfs_mountslock_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->vf_mountslock)

/* Helper macros for `struct fsuper::vf_recentlock' */
#define _vfs_recentlock_reap(self)      _oblockop_reap_atomic_lock(&(self)->vf_recentlops, &(self)->vf_recentlock, self)
#define vfs_recentlock_reap(self)       oblockop_reap_atomic_lock(&(self)->vf_recentlops, &(self)->vf_recentlock, self)
#define vfs_recentlock_mustreap(self)   oblockop_mustreap(&(self)->vf_recentlops)
#define vfs_recentlock_tryacquire(self) atomic_lock_tryacquire(&(self)->vf_recentlock)
#define vfs_recentlock_acquire(self)    atomic_lock_acquire(&(self)->vf_recentlock)
#define vfs_recentlock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->vf_recentlock)
#define _vfs_recentlock_release(self)   atomic_lock_release(&(self)->vf_recentlock)
#define vfs_recentlock_release(self)    (atomic_lock_release(&(self)->vf_recentlock), vfs_recentlock_reap(self))
#define vfs_recentlock_acquired(self)   atomic_lock_acquired(&(self)->vf_recentlock)
#define vfs_recentlock_available(self)  atomic_lock_available(&(self)->vf_recentlock)
#define vfs_recentlock_waitfor(self)    atomic_lock_waitfor(&(self)->vf_recentlock)
#define vfs_recentlock_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->vf_recentlock)

/* Helper macros for working with `struct vfs::vf_driveslock' */
#define _vfs_driveslock_reap(self)        (void)0
#define vfs_driveslock_reap(self)         (void)0
#define vfs_driveslock_mustreap(self)     0
#define vfs_driveslock_write(self)        atomic_rwlock_write(&(self)->vf_driveslock)
#define vfs_driveslock_write_nx(self)     atomic_rwlock_write_nx(&(self)->vf_driveslock)
#define vfs_driveslock_trywrite(self)     atomic_rwlock_trywrite(&(self)->vf_driveslock)
#define vfs_driveslock_endwrite(self)     (atomic_rwlock_endwrite(&(self)->vf_driveslock), vfs_driveslock_reap(self))
#define _vfs_driveslock_endwrite(self)    atomic_rwlock_endwrite(&(self)->vf_driveslock)
#define vfs_driveslock_read(self)         atomic_rwlock_read(&(self)->vf_driveslock)
#define vfs_driveslock_read_nx(self)      atomic_rwlock_read_nx(&(self)->vf_driveslock)
#define vfs_driveslock_tryread(self)      atomic_rwlock_tryread(&(self)->vf_driveslock)
#define _vfs_driveslock_endread(self)     atomic_rwlock_endread(&(self)->vf_driveslock)
#define vfs_driveslock_endread(self)      (void)(atomic_rwlock_endread(&(self)->vf_driveslock) && (vfs_driveslock_reap(self), 0))
#define _vfs_driveslock_end(self)         atomic_rwlock_end(&(self)->vf_driveslock)
#define vfs_driveslock_end(self)          (void)(atomic_rwlock_end(&(self)->vf_driveslock) && (vfs_driveslock_reap(self), 0))
#define vfs_driveslock_upgrade(self)      atomic_rwlock_upgrade(&(self)->vf_driveslock)
#define vfs_driveslock_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->vf_driveslock)
#define vfs_driveslock_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->vf_driveslock)
#define vfs_driveslock_downgrade(self)    atomic_rwlock_downgrade(&(self)->vf_driveslock)
#define vfs_driveslock_reading(self)      atomic_rwlock_reading(&(self)->vf_driveslock)
#define vfs_driveslock_writing(self)      atomic_rwlock_writing(&(self)->vf_driveslock)
#define vfs_driveslock_canread(self)      atomic_rwlock_canread(&(self)->vf_driveslock)
#define vfs_driveslock_canwrite(self)     atomic_rwlock_canwrite(&(self)->vf_driveslock)
#define vfs_driveslock_waitread(self)     atomic_rwlock_waitread(&(self)->vf_driveslock)
#define vfs_driveslock_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->vf_driveslock)
#define vfs_driveslock_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->vf_driveslock)
#define vfs_driveslock_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->vf_driveslock)


/* Default kernel and /bin/init VFS controller. */
DATDEF struct vfs vfs_kernel;

/* (try) to add the given path `self' to the cache of recently used paths.
 * If the  lock to  `path_vfs->vf_recentlock' cannot  be acquired  without
 * blocking, simply do nothing.
 * @return: * : Always re-returns `self'. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct path *
NOTHROW(FCALL vfs_recent)(struct vfs *__restrict path_vfs,
                          struct path *__restrict self);

/* Return  a reference to the mounting point that comes after `prev'
 * When `prev == NULL',  return the  first  mount point.  Note  that
 * when `prev' has been unloaded, this function will also return the
 * first (still-registered) mounting point. */
FUNDEF WUNUSED NONNULL((1)) REF struct pathmount *FCALL
vfs_mounts_next(struct vfs *__restrict self,
                struct pathmount *prev)
		THROWS(E_WOULDBLOCK);

struct fdirnode;

/* Return the path used to mount the given `dir' within `self'.
 * If the given directory doesn't have a mounting point  within
 * the given VFS `self', return `NULL' */
FUNDEF WUNUSED NONNULL((1, 2)) REF struct pathmount *FCALL
vfs_mount_location(struct vfs *__restrict self,
                   struct fdirnode *__restrict dir)
		THROWS(E_WOULDBLOCK);






typedef union {
	struct {
		WEAK u32    f_atmask; /* File system operations mode mask (Set of negated `AT_*'). */
		WEAK u32    f_atflag; /* File system operations mode flags (Set of negated `AT_*'). */
	};
	WEAK u64        f_mode;   /* File system operations mode. */
	WEAK atomic64_t f_atom;   /* File system operations mode. */
} fs_mask_t;



/* Default value for `struct fs::fs_umask' */
#define CONFIG_FS_UMASK_DEFAULT 0022 /* S_IWGRP|S_IWOTH */

/* FS is the high-level filesystem controller that expands upon VFS by
 * adding commonly thought-of as "per-process" variables such as  PWD,
 * CHROOT, UMASK, and other configuration variables, as well as  DOS's
 * per-drive PWD directories. */
struct fs {
	WEAK refcnt_t        fs_refcnt;               /* Reference counter. */
	REF struct vfs      *fs_vfs;                  /* [1..1][const] The underlying VFS. */
	struct atomic_rwlock fs_pathlock;             /* Lock for accessing dynamic filesystem paths (cwd, root, drive-local CWDs) */
	REF struct path     *fs_root;                 /* [1..1][lock(fs_pathlock)] Root directory. */
	REF struct path     *fs_cwd;                  /* [1..1][lock(fs_pathlock)] Current working directory. */
	REF struct path     *fs_dcwd[VFS_DRIVECOUNT]; /* [0..1][lock(fs_pathlock)][*] Per-drive working directories.
	                                               * NOTE: When `NULL', use `f_vfs->v_drives[INDEX]' instead. */
	WEAK mode_t          fs_umask;                /* [lock(ATOMIC)] The currently effective UMASK.
	                                               * NOTE: All bits not masked by `0777' _MUST_ always be ZERO(0)! */
	WEAK u32             fs_lnkmax;               /* The max number of symbolic links allowed during resolution of a path.
	                                               * This field defaults to `SYMLOOP_MAX'. */
	fs_mask_t            fs_mode;                 /* Filesystem mode */
};

/* Destroy the given FS controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fs_destroy)(struct fs *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct fs, fs_refcnt, fs_destroy)


/* Helper macros for working with `struct fs::fs_pathlock' */
#define _fs_pathlock_reap(self)        (void)0
#define fs_pathlock_reap(self)         (void)0
#define fs_pathlock_write(self)        atomic_rwlock_write(&(self)->fs_pathlock)
#define fs_pathlock_write_nx(self)     atomic_rwlock_write_nx(&(self)->fs_pathlock)
#define fs_pathlock_trywrite(self)     atomic_rwlock_trywrite(&(self)->fs_pathlock)
#define fs_pathlock_endwrite(self)     (atomic_rwlock_endwrite(&(self)->fs_pathlock), fs_pathlock_reap(self))
#define _fs_pathlock_endwrite(self)    atomic_rwlock_endwrite(&(self)->fs_pathlock)
#define fs_pathlock_read(self)         atomic_rwlock_read(&(self)->fs_pathlock)
#define fs_pathlock_read_nx(self)      atomic_rwlock_read_nx(&(self)->fs_pathlock)
#define fs_pathlock_tryread(self)      atomic_rwlock_tryread(&(self)->fs_pathlock)
#define _fs_pathlock_endread(self)     atomic_rwlock_endread(&(self)->fs_pathlock)
#define fs_pathlock_endread(self)      (void)(atomic_rwlock_endread(&(self)->fs_pathlock) && (fs_pathlock_reap(self), 0))
#define _fs_pathlock_end(self)         atomic_rwlock_end(&(self)->fs_pathlock)
#define fs_pathlock_end(self)          (void)(atomic_rwlock_end(&(self)->fs_pathlock) && (fs_pathlock_reap(self), 0))
#define fs_pathlock_upgrade(self)      atomic_rwlock_upgrade(&(self)->fs_pathlock)
#define fs_pathlock_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->fs_pathlock)
#define fs_pathlock_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->fs_pathlock)
#define fs_pathlock_downgrade(self)    atomic_rwlock_downgrade(&(self)->fs_pathlock)
#define fs_pathlock_reading(self)      atomic_rwlock_reading(&(self)->fs_pathlock)
#define fs_pathlock_writing(self)      atomic_rwlock_writing(&(self)->fs_pathlock)
#define fs_pathlock_canread(self)      atomic_rwlock_canread(&(self)->fs_pathlock)
#define fs_pathlock_canwrite(self)     atomic_rwlock_canwrite(&(self)->fs_pathlock)
#define fs_pathlock_waitread(self)     atomic_rwlock_waitread(&(self)->fs_pathlock)
#define fs_pathlock_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->fs_pathlock)
#define fs_pathlock_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->fs_pathlock)
#define fs_pathlock_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->fs_pathlock)

/* Default kernel and /bin/init FS controller. */
DATDEF struct fs fs_kernel;

/* [1..1][lock(PRIVATE(THIS_TASK))] Filesystem controller for the current thread.
 * Even  though this pointer can be modified by the thread itself, it must not be
 * altered from within any kind of RPC. Lots of filesystem functionality  assumes
 * that this pointer cannot changed over  the course of some operation.  However,
 * it  is OK for this pointer to change  outside the context of any FS operation,
 * such as a top-level system call. */
DATDEF ATTR_PERTASK REF struct fs *this_fs;
#define THIS_FS        PERTASK_GET(this_fs)
#define THIS_VFS       (THIS_FS->fs_vfs)


/* Return the filesystem controller of the given thread. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *
NOTHROW(FCALL task_getfs)(struct task *__restrict thread);
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vfs *
NOTHROW(FCALL task_getvfs)(struct task *__restrict thread);

/* Exchange the filesystem controller of the calling thread. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *
NOTHROW(FCALL task_setfs)(struct fs *__restrict newfs);


/* Clone the given FS
 * @param: clone_vfs: When true, also clone the VFS, else share the same one. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *KCALL
fs_clone(struct fs *__restrict self, bool clone_vfs) THROWS(E_BADALLOC);


/* Return currently set CWD/ROOT of the given filesystem. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *FCALL
fs_getcwd(struct fs *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *FCALL
fs_getroot(struct fs *__restrict self) THROWS(E_WOULDBLOCK);

EIDECLARE(ATTR_PURE WUNUSED,atflag_t,NOTHROW,FCALL,fs_atflags,(atflag_t atflags),{
	fs_mask_t mask;
	mask.f_mode = atomic64_read(&THIS_FS->fs_mode.f_atom);
	return (atflags & mask.f_atmask) | mask.f_atflag;
});



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_VFS_H */
