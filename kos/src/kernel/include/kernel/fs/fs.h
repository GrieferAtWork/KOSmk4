/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FS_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/atomic64.h>
#include <sched/pertask.h>

#include <hybrid/sched/atomic-rwlock.h>

#ifdef __CC__
DECL_BEGIN

struct vfs;
struct path;
struct task;

typedef union {
	struct {
		WEAK u32    f_atmask; /* File system operations mode mask (Set of negated `AT_*'). */
		WEAK u32    f_atflag; /* File system operations mode flags (Set of negated `AT_*'). */
	};
	WEAK u64        f_mode;   /* File system operations mode. */
	WEAK atomic64_t f_atom;   /* File system operations mode. */
} fs_mask_t;


/* # of different DOS drives. */
#ifndef VFS_DRIVECOUNT
#define VFS_DRIVECOUNT (('Z' - 'A') + 1)
#endif /* !VFS_DRIVECOUNT */

/* Default value for `struct fs::fs_umask' */
#define FS_DEFAULT_UMASK 0022 /* S_IWGRP|S_IWOTH */

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
	                                               * NOTE: When `NULL', use `fs_vfs->vf_drives[INDEX]' instead. */
	WEAK mode_t          fs_umask;                /* [lock(ATOMIC)] The currently effective UMASK.
	                                               * NOTE: All bits not masked by `0777' _MUST_ always be ZERO(0)! */
	WEAK u32             fs_lnkmax;               /* The max number of symbolic links allowed during resolution of a path.
	                                               * This field defaults to `SYMLOOP_MAX'. */
	fs_mask_t            fs_mode;                 /* Filesystem mode */
};

/* Destroy the given FS controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fs_destroy)(struct fs *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct fs, fs_refcnt, fs_destroy)


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
NOTHROW(FCALL task_setfs_inherit)(/*inherit(always)*/ REF struct fs *__restrict newfs);
#define task_setfs(newfs) task_setfs_inherit(incref(newfs))

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

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FS_H */
