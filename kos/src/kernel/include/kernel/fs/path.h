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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_PATH_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_PATH_H 1

#include <kernel/compiler.h>

#ifndef __INTELLISENSE__
#include <kernel/fs/dirent.h>
#endif /* !__INTELLISENSE__ */
#include <kernel/types.h>

#include <hybrid/sched/__preemption.h>
#include <hybrid/sequence/list.h>

#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <bits/crt/format-printer.h>
#include <kos/lockop.h>
#include <kos/sched/shared-rwlock.h>

#ifndef CONFIG_NO_SMP
#ifndef __INTELLISENSE__
#include <sched/task.h>
#endif /* !__INTELLISENSE__ */
#include <hybrid/__atomic.h>
#endif /* !CONFIG_NO_SMP */

/* atflag_t values. */
#if !defined(AT_SYMLINK_NOFOLLOW) && defined(__AT_SYMLINK_NOFOLLOW)
#define AT_SYMLINK_NOFOLLOW __AT_SYMLINK_NOFOLLOW
#endif /* !AT_SYMLINK_NOFOLLOW && __AT_SYMLINK_NOFOLLOW */
#if !defined(AT_NO_AUTOMOUNT) && defined(__AT_NO_AUTOMOUNT)
#define AT_NO_AUTOMOUNT __AT_NO_AUTOMOUNT
#endif /* !AT_NO_AUTOMOUNT && __AT_NO_AUTOMOUNT */
#if !defined(AT_EMPTY_PATH) && defined(__AT_EMPTY_PATH)
#define AT_EMPTY_PATH __AT_EMPTY_PATH
#endif /* !AT_EMPTY_PATH && __AT_EMPTY_PATH */
#if !defined(AT_DOSPATH) && defined(__AT_DOSPATH)
#define AT_DOSPATH __AT_DOSPATH
#endif /* !AT_DOSPATH && __AT_DOSPATH */
#if !defined(AT_REMOVEREG) && defined(__AT_REMOVEREG)
#define AT_REMOVEREG __AT_REMOVEREG
#endif /* !AT_REMOVEREG && __AT_REMOVEREG */
#if !defined(AT_REMOVEDIR) && defined(__AT_REMOVEDIR)
#define AT_REMOVEDIR __AT_REMOVEDIR
#endif /* !AT_REMOVEDIR && __AT_REMOVEDIR */


/* Not available to user-space: ignore trailing slashes */
#define AT_IGNORE_TRAILING_SLASHES 0x10

/* Not available to user-space: path_print() should print a trailing slash */
#define AT_PATHPRINT_INCTRAIL      0x20 /* Include a trailing slash/backslash. */

/* Not available to user-space: path_print() may assume that `root' is reachable from `self' */
#define _AT_PATHPRINT_REACHABLE    0x40 /* Assume that `root' is reachable from `self' */


/* Special fd_t values. */
#if !defined(AT_FDCWD) && defined(__AT_FDCWD)
#define AT_FDCWD __AT_FDCWD
#endif /* !AT_FDCWD && __AT_FDCWD */
#if !defined(AT_FDROOT) && defined(__AT_FDROOT)
#define AT_FDROOT __AT_FDROOT
#endif /* !AT_FDROOT && __AT_FDROOT */


#ifdef __CC__
DECL_BEGIN

/* PATH/VFS data ownership diagram:
 *
 *    SUPER
 *      ^
 *      │
 *    MOUNT=PATH ──parent─> PATH ──parent─> PATH
 *      ^   │ ^              ^               ^ │
 *      │   │ │              │               │ │
 *      │   │ └─recent_cache─┴───────────────┘ │
 *      │   │       │                          │
 *      │   └─[*]─┐ │                          │
 *      │         v │                          │
 *     MOUNTS ─── VFS ──> ROOT <─────parent────┘
 *
 * [*] Weak reference (PATH->VFS)
 *
 * - PATH:         `struct path'
 * - MOUNT:        `struct pathmount'
 * - parent:       `struct path::p_parent'
 * - ROOT:         `struct path' (with `p_parent == NULL')
 * - VFS:          `struct vfs'
 * - MOUNTS:       `struct vfs::vf_mounts'
 * - recent_cache: `struct vfs::vf_recent'
 *
 */


struct fdirnode;
struct path;
struct vfs;
struct fdirent;


struct path_bucket {
	struct path *pb_path; /* [0..1][:p_cldlock] One of:
	                       *  - Child path
	                       *  - INTERNAL:`deleted_path' for deleted paths
	                       *  - `NULL' for sentinel. */
};


/* Flags for `struct path::p_flags' */
#define PATH_F_NORMAL  0x0000 /* Normal flags */
#define PATH_F_ISMOUNT 0x0001 /* [const] This path is a mounting point. */
#define PATH_F_ISROOT  0x0002 /* [const] This path is a hard-root (iow: doesn't have a parent). */
#define PATH_F_ISDRIVE 0x0004 /* [lock(:VFS->vf_driveslock)] The path is (at least one) DOS drive mount. */
#ifndef CONFIG_NO_SMP
#define _PATH_F_PLOCK  0x8000 /* SMP-lock for `p_parent' */
#endif /* !CONFIG_NO_SMP */


/* Marker for `struct path::p_cldlist': This path node has been deleted. */
#define PATH_CLDLIST_DELETED ((struct path_bucket *)-1)

struct path {
	WEAK refcnt_t             p_refcnt;  /* Reference counter */
	uintptr_t                 p_flags;   /* Path flags (set of `PATH_F_*') */
	union {
		REF struct path      *p_parent;  /* [1..1][lock(RD(p_parent->p_cldlock || _PATH_F_PLOCK),
		                                  *             WR(p_parent->p_cldlock && _PATH_F_PLOCK))] // old p_parent during WR
		                                  * Parent path. */
		WEAK REF struct vfs *_p_vfs;     /* [1..1][const] VFS context of this path-tree. */
	};
	REF struct fdirent       *p_name;    /* [1..1][lock(RD(p_parent->p_cldlock || _PATH_F_PLOCK),
		                                  *             WR(p_parent->p_cldlock && _PATH_F_PLOCK))]
		                                  * Name of this directory (`fdirent_empty' for root directory). */
	REF struct fdirnode      *p_dir;     /* [1..1][const] Directory to which this path refers. An unmounted
	                                      * root directory  has this  set to  `fdirnode_unmounted.fs_root'. */
#ifdef __WANT_PATH__p_dead
	union {
		TAILQ_ENTRY(REF path) p_recent;  /* [0..1][lock(:VFS->vf_recent_lock)] Cache entry for recently used paths.
		                                  * NOTE: Once a path has been marked as deleted (p_cldlist = PATH_CLDLIST_DELETED),
		                                  *       it should be removed  from the recent  cache by use  of a lock  operation.
		                                  *       For this purpose, it is the responsibility of whoever marked the paths  as
		                                  *       deleted (PATH_CLDLIST_DELETED) to initialize this lock operation! */
		SLIST_ENTRY(path)    _p_dead;    /* Used internally... */
	};
#else /* __WANT_PATH__p_dead */
	TAILQ_ENTRY(REF path)     p_recent;  /* [0..1][lock(:VFS->vf_recent_lock)] Cache entry for recently used paths.
	                                      * NOTE: Once a path has been marked as deleted (p_cldlist = PATH_CLDLIST_DELETED),
	                                      *       it should be removed  from the recent  cache by use  of a lock  operation.
	                                      *       For this purpose, it is the responsibility of whoever marked the paths  as
	                                      *       deleted (PATH_CLDLIST_DELETED) to initialize this lock operation! */
#endif /* !__WANT_PATH__p_dead */
	struct shared_rwlock      p_cldlock; /* Lock for this path. */
	Toblockop_slist(path)     p_cldlops; /* Lock operations for `p_cldlock'. */
#ifdef __WANT_PATH__p_LOPS
	union {
		struct {
			size_t        p_cldused; /* [valid_if(p_cldlist != PATH_CLDLIST_DELETED)][lock(p_cldlock)] Amount of used (non-NULL and non-deleted) child paths */
			size_t        p_cldsize; /* [valid_if(p_cldlist != PATH_CLDLIST_DELETED)][lock(p_cldlock)] Amount of (non-NULL) child paths */
			size_t        p_cldmask; /* [valid_if(p_cldlist != PATH_CLDLIST_DELETED)][lock(p_cldlock)] Hash-mask for `p_cldlist' */
		};
		Toblockop(path)       _p_pthlop;   /* Used internally for async remove from `p_parent->p_cldlist' */
		Tobpostlockop(path)   _p_pthplop;  /* Used internally for async remove from `p_parent->p_cldlist' */
		Toblockop(fsuper)     _p_suplop;   /* Used internally for async remove from `path_getsuper(this)->fs_mounts' */
		Tobpostlockop(fsuper) _p_supplop;  /* Used internally for async remove from `path_getsuper(this)->fs_mounts' */
		Toblockop(vfs)        _p_vfslop;   /* Used internally for async remove from `struct vfs::vf_recent' */
		Tobpostlockop(vfs)    _p_vfsplop;  /* Used internally for async remove from `struct vfs::vf_recent' */
	};
#else /* __WANT_PATH__p_LOPS */
	size_t                p_cldused; /* [valid_if(p_cldlist != PATH_CLDLIST_DELETED)][lock(p_cldlock)] Amount of used (non-NULL and non-deleted) child paths */
	size_t                p_cldsize; /* [valid_if(p_cldlist != PATH_CLDLIST_DELETED)][lock(p_cldlock)] Amount of (non-NULL) child paths */
	size_t                p_cldmask; /* [valid_if(p_cldlist != PATH_CLDLIST_DELETED)][lock(p_cldlock)] Hash-mask for `p_cldlist' */
#endif /* !__WANT_PATH__p_LOPS */
	struct path_bucket   *p_cldlist; /* [1..p_cldmask+1][owned][lock(p_cldlock)]  Hash-vector  of child
	                                  * paths. Set to `PATH_CLDLIST_DELETED' when this path was deleted */
};

/* Allocate normal paths */
#define _path_alloc() ((struct path *)kmalloc(sizeof(struct path), GFP_NORMAL))
#define _path_free(p) kfree(p)

/* Hash-vector iteration helper macros */
#define path_hashof(self)       ((self)->p_name->fd_hash)
#define path_hashnx(i, perturb) ((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)

/* Return the superblock associated with a given path */
#define path_getsuper(self) ((self)->p_dir->_fdirnode_node_ fn_super)
#define path_ismount(self)  ((self)->p_flags & PATH_F_ISMOUNT)
#define path_asmount(self)  ((struct pathmount *)(self))
#define path_isdrive(self)  ((self)->p_flags & PATH_F_ISDRIVE) /* Caller must be holding `_path_getvfs(self)->vf_driveslock' */
#define path_isroot(self)   ((self)->p_flags & PATH_F_ISROOT)

/* Helpers for working with the PLOCK (ParentLOCK) of paths. */
#ifndef CONFIG_NO_SMP
#define path_plock_tryacquire_nopr(self) \
	(!(__hybrid_atomic_fetchor((self)->p_flags, _PATH_F_PLOCK, __ATOMIC_SEQ_CST) & _PATH_F_PLOCK))
#define path_plock_release_nopr(self) \
	__hybrid_atomic_and((self)->p_flags, ~_PATH_F_PLOCK, __ATOMIC_SEQ_CST)
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(path_plock_acquire_nopr)(struct path *__restrict self) {
#ifndef __INTELLISENSE__
	while (!path_plock_tryacquire_nopr(self))
		task_pause();
#endif /* !__INTELLISENSE__ */
}
#else /* !CONFIG_NO_SMP */
#define path_plock_tryacquire_nopr(self) 1
#define path_plock_acquire_nopr(self)    (void)0
#define path_plock_release_nopr(self)    (void)0
#endif /* CONFIG_NO_SMP */
#define path_plock_acquire(self) __hybrid_preemption_acquire_smp(path_plock_tryacquire_nopr(self))
#define path_plock_release(self) __hybrid_preemption_release_smp(path_plock_release_nopr(self))

#ifdef __INTELLISENSE__
NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fdirent *
NOTHROW(FCALL path_getname)(struct path *__restrict self);
NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *
NOTHROW(FCALL path_getparent)(struct path *__restrict self);
NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL path_get_parent_and_name)(struct path *__restrict self,
                                        /*out[1..1]_ref*/ REF struct path **__restrict p_parent,
                                        /*out[1..1]_ref*/ REF struct fdirent **__restrict p_name);
#else /* __INTELLISENSE__ */
LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fdirent *
NOTHROW(FCALL path_getname)(struct path *__restrict self) {
	REF struct fdirent *result;
	path_plock_acquire(self);
	result = incref(self->p_name);
	path_plock_release(self);
	return result;
}

LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *
NOTHROW(FCALL path_getparent)(struct path *__restrict self) {
	REF struct path *result;
	path_plock_acquire(self);
	result = incref(self->p_parent);
	path_plock_release(self);
	return result;
}

LOCAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL path_get_parent_and_name)(struct path *__restrict self,
                                        /*out[1..1]_ref*/ REF struct path **__restrict p_parent,
                                        /*out[1..1]_ref*/ REF struct fdirent **__restrict p_name) {
	path_plock_acquire(self);
	*p_parent = incref(self->p_parent);
	*p_name   = incref(self->p_name);
	path_plock_release(self);
}
#endif /* !__INTELLISENSE__ */




/* Check if `child' is a descendant of `root' (including `child == root') */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL
NOTHROW(FCALL path_isdescendantof)(struct path *child,
                                   struct path const *root);

/* Return a pointer to the VFS associated with `self' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct vfs *
NOTHROW(FCALL _path_getvfs)(struct path *__restrict self);


/* Destroy a given path, automatically removing it from:
 *  - self->p_parent->p_cldlist       (asynchronously via lockops in self->p_parent->p_cldlops)
 *  - path_getsuper(self)->fs_mounts  (asynchronously via lockops in path_getsuper(self)->fs_mountslockops.
 *                                    If  this path  was the  last mounting  point, call `fsuper_delete()') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL path_destroy)(struct path *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct path, p_refcnt, path_destroy)


/* Special superblock (and directory) set for unmounted filesystem root paths.
 * Iow: this may  be set  in `struct path::p_dir'  for paths  that  are
 *      root dirs, as is the case when `struct path::p_parent == NULL'. */
DATDEF struct ramfs_super fsuper_unmounted;
DATDEF struct fdirent fdirent_empty;
DATDEF struct fdirent_ops const fdirent_empty_ops;
#define fdirnode_unmounted fsuper_unmounted._ramfs_super_super_ fs_root

/* Empty hash-vector for `struct path::p_cldlist' */
DATDEF struct path_bucket const _path_empty_cldlist[1] ASMNAME("path_empty_cldlist");
#define path_empty_cldlist ((struct path_bucket *)_path_empty_cldlist)

/* Helper macros for working with `struct path::p_cldlock' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _path_cldlock_reap)(struct path *__restrict self);
#ifdef __OPTIMIZE_SIZE__
#define path_cldlock_reap(self) _path_cldlock_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define path_cldlock_reap(self) (void)(!lockop_mustreap(&(self)->p_cldlops) || (_path_cldlock_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */
#define /*BLOCKING*/ path_cldlock_write(self)        shared_rwlock_write(&(self)->p_cldlock)
#define /*BLOCKING*/ path_cldlock_write_nx(self)     shared_rwlock_write_nx(&(self)->p_cldlock)
#define /*        */ path_cldlock_trywrite(self)     shared_rwlock_trywrite(&(self)->p_cldlock)
#define /*        */ path_cldlock_endwrite(self)     (shared_rwlock_endwrite(&(self)->p_cldlock), path_cldlock_reap(self))
#define /*        */ _path_cldlock_endwrite(self)    shared_rwlock_endwrite(&(self)->p_cldlock)
#define /*BLOCKING*/ path_cldlock_read(self)         shared_rwlock_read(&(self)->p_cldlock)
#define /*BLOCKING*/ path_cldlock_read_nx(self)      shared_rwlock_read_nx(&(self)->p_cldlock)
#define /*        */ path_cldlock_tryread(self)      shared_rwlock_tryread(&(self)->p_cldlock)
#define /*        */ _path_cldlock_endread(self)     shared_rwlock_endread(&(self)->p_cldlock)
#define /*        */ path_cldlock_endread(self)      (void)(shared_rwlock_endread(&(self)->p_cldlock) && (path_cldlock_reap(self), 0))
#define /*        */ _path_cldlock_end(self)         shared_rwlock_end(&(self)->p_cldlock)
#define /*        */ path_cldlock_end(self)          (void)(shared_rwlock_end(&(self)->p_cldlock) && (path_cldlock_reap(self), 0))
#define /*BLOCKING*/ path_cldlock_upgrade(self)      shared_rwlock_upgrade(&(self)->p_cldlock)
#define /*        */ path_cldlock_tryupgrade(self)   shared_rwlock_tryupgrade(&(self)->p_cldlock)
#define /*        */ path_cldlock_downgrade(self)    shared_rwlock_downgrade(&(self)->p_cldlock)
#define /*        */ path_cldlock_reading(self)      shared_rwlock_reading(&(self)->p_cldlock)
#define /*        */ path_cldlock_writing(self)      shared_rwlock_writing(&(self)->p_cldlock)
#define /*        */ path_cldlock_canread(self)      shared_rwlock_canread(&(self)->p_cldlock)
#define /*        */ path_cldlock_canwrite(self)     shared_rwlock_canwrite(&(self)->p_cldlock)
#define /*BLOCKING*/ path_cldlock_waitread(self)     shared_rwlock_waitread(&(self)->p_cldlock)
#define /*BLOCKING*/ path_cldlock_waitwrite(self)    shared_rwlock_waitwrite(&(self)->p_cldlock)
#define /*BLOCKING*/ path_cldlock_waitread_nx(self)  shared_rwlock_waitread_nx(&(self)->p_cldlock)
#define /*BLOCKING*/ path_cldlock_waitwrite_nx(self) shared_rwlock_waitwrite_nx(&(self)->p_cldlock)

/* Remove `elem' from the child-list of `self'
 * @return: true:  Successfully removed.
 * @return: false: Wasn't actually a member. */
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL path_cldlist_remove)(struct path *__restrict self,
                                   struct path *__restrict elem);
/* Same as `path_cldlist_remove()', but UD  if
 * `elem' isn't actually in `self's child list */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL path_cldlist_remove_force)(struct path *__restrict self,
                                         struct path *__restrict elem);

/* Try to rehash the child-path list of `self' following the removal of a child. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL path_cldlist_rehash_after_remove)(struct path *__restrict self);

/* Ensure that sufficient space exists for the addition of another path to the child list
 * Caller must be holding a lock to `self'. */
FUNDEF NONNULL((1)) void FCALL
path_cldlist_rehash_before_insert(struct path *__restrict self)
		THROWS(E_BADALLOC);

/* Insert `elem' into the child-list of `self'
 * Caller must have made a call to `path_cldlist_rehash_before_insert()' */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL path_cldlist_insert)(struct path *__restrict self,
                                   struct path *__restrict elem);



/* Lookup a child with a given path, but don't construct new child paths
 * via directory lookup. If something like that is wanted, you must make
 * use of `path_expandchild()' and friends below.
 * @param: atflags: Set of `0 | AT_DOSPATH' (other flags are silently ignored)
 * @return: * :     Reference to a known path-child.
 * @return: NULL:   No such child is part of the child hashset. Though this
 *                  doesn't necessarily mean that no such child exists;  it
 *                  may just not  have been loaded  yet; iow: you  probably
 *                  should  use `fdirnode_lookup()' to determine if the dir
 *                  of `self' contains the named file.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: `self' was marked as `PATH_CLDLIST_DELETED' */
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct path *KCALL
path_lookupchild(struct path *__restrict self,
                 /*utf-8*/ USER CHECKED char const *name,
                 u16 namelen, uintptr_t namehash,
                 atflag_t atflags DFL(0))
		THROWS(E_FSERROR_DELETED, E_WOULDBLOCK, E_SEGFAULT);
/* Same as `path_lookupchild()', but caller must be holding a lock `path_cldlock_read(self)' */
FUNDEF WUNUSED NONNULL((1)) struct path *KCALL
path_lookupchild_withlock(struct path *__restrict self,
                          /*utf-8*/ USER CHECKED char const *name,
                          u16 namelen, uintptr_t namehash,
                          atflag_t atflags DFL(0))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) REF struct path *KCALL
path_lookupchildref_withlock(struct path *__restrict self,
                             /*utf-8*/ USER CHECKED char const *name,
                             u16 namelen, uintptr_t namehash,
                             atflag_t atflags DFL(0))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT);



/* Expand a child path of `self' and re-return the new path.
 *   - If caller doesn't have EXEC permission for `self', THROW(E_FSERROR_ACCESS_DENIED)
 *   - If the path is marked as `PATH_CLDLIST_DELETED', THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DIR);
 *   - If the named child is a member of the child-list of `self', return that member.
 *   - Make a call to `fdirnode_lookup()' and inspect the returned node:
 *   - If NULL, `THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DIR);'
 *   - If it's a directory, create a new  child for it and return said  child.
 *     If at this point another child with identical name already exists, then
 *     the existing child is returned instead.
 *   - If it's a symlink, `*premaining_symlinks == 0' means to
 *     `THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS)'.
 *     Otherwise, expand the symlink's contents as a POSIX  path
 *     string (when the path starts  with "/", the current  root
 *     dir is used, and relative paths are expanded with `self')
 *     Finally, return the pointed-to path. (s.a. path_traverse)
 *   - If it's anything else, THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_WALK)
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_NO_AUTOMOUNT' (other flags are silently ignored)
 * @throw: E_WOULDBLOCK:                      Preemption is disabled, and operation would have blocked.
 * @throw: E_SEGFAULT:                        The given `name' is faulty.
 * @throw: E_FSERROR_ACCESS_DENIED:           Not allowed to traverse `self' of a dir walked by the symlink
 * @throw: E_FSERROR_PATH_NOT_FOUND:E_FILESYSTEM_PATH_NOT_FOUND_DIR: `self' doesn't have a child `name...+=namelen'
 * @throw: E_FSERROR_TOO_MANY_SYMBOLIC_LINKS: Too many symbolic link encountered during expansion
 * @throw: E_FSERROR_NOT_A_DIRECTORY:         The named child isn't a directory or symlink (or the symlink expands to a non-directory)
 * @throw: E_IOERROR:                         ...
 * @throw: E_BADALLOC:                        ... */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct path *KCALL
path_expandchild(struct path *__restrict self, u32 *__restrict premaining_symlinks,
                 /*utf-8*/ USER CHECKED char const *name,
                 u16 namelen, uintptr_t namehash, atflag_t atflags DFL(0))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...);

/* Same as `path_expandchild()', but instead of requiring the pointed-to
 * file to be a directory or symlink, simply return the pointed-to file,
 * which may be anything.
 *
 * NOTE: By default, this function will never return a symlink node, but
 *       will instead dereference and expand it recursively. If this  is
 *       not intended, you may pass `AT_SYMLINK_NOFOLLOW', in which case
 *       this trailing symlink isn't expanded.
 *
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_NO_AUTOMOUNT | AT_SYMLINK_NOFOLLOW' (other flags are silently ignored)
 */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
path_expandchildnode(struct path *__restrict self, u32 *__restrict premaining_symlinks,
                     /*utf-8*/ USER CHECKED char const *name,
                     u16 namelen, uintptr_t namehash, atflag_t atflags DFL(0),
                     /*out[1..1]_opt*/ REF struct path **presult_path DFL(__NULLPTR),
                     /*out[1..1]_opt*/ REF struct fdirent **presult_dirent DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, ...);


/* Traverse  a full filesystem `upath', which may be relative or absolute,
 * and follow DOS or UNIX semantics, based on `atflags & AT_DOSPATH'. When
 * requested via `plastseg != NULL',  a pointer to  the last  path-segment
 * is stored in `*plastseg' and `*plastlen'.
 *  - Path segments are separated by '/' (or alternatively '\\' when `AT_DOSPATH' is given)
 *  - When no last segment exists within `upath', but one was requested, then
 *    `*plastlen = 0' is written, and the sequence's final path is  returned.
 *  - When `plastseg == NULL' the path is  always fully traversed, and the  last
 *    element is required to be a directory (as implied by a `struct path' being
 *    returned).
 * Examples:
 *  - upath = ""             --> return=$cwd;          lastseg=""    (when `AT_EMPTY_PATH' isn't given, this isn't allowed)
 *  - upath = "."            --> return=$cwd;          lastseg=""
 *  - upath = "foo"          --> return=$cwd;          lastseg="foo"
 *  - upath = "./foo"        --> return=$cwd;          lastseg="foo"
 *  - upath = "foo/"         --> return=$cwd/foo;      lastseg=""    (without AT_IGNORE_TRAILING_SLASHES)
 *  - upath = "foo/"         --> return=$cwd;          lastseg="foo" (with AT_IGNORE_TRAILING_SLASHES)
 *  - upath = "foo/."        --> return=$cwd/foo;      lastseg=""
 *  - upath = "foo/bar/.."   --> return=$cwd/foo;      lastseg=""    (No unwinding in this case!)
 * When `AT_DOSPATH' isn't given:
 *  - upath = "/."           --> return=$root;         lastseg=""
 *  - upath = "/"            --> return=$root;         lastseg=""
 *  - upath = "/.."          --> return=$root;         lastseg=""
 *  - upath = "/foo"         --> return=$root;         lastseg="foo"
 * When `AT_DOSPATH' is given:
 *  - upath = "C:"           --> return=$cwd[C];       lastseg=""
 *  - upath = "C:foo"        --> return=$cwd[C];       lastseg="foo"
 *  - upath = "C:foo\\"      --> return=$cwd[C]\\foo;  lastseg=""    (without AT_IGNORE_TRAILING_SLASHES)
 *  - upath = "C:foo\\"      --> return=$cwd[C];       lastseg="foo" (with AT_IGNORE_TRAILING_SLASHES)
 *  - upath = "C:foo\\bar"   --> return=$cwd[C]\\foo;  lastseg="bar"
 *  - upath = "C:\\"         --> return=$root[C];      lastseg=""
 *  - upath = "C:\\foo"      --> return=$root[C];      lastseg="foo"
 *  - upath = "C:\\foo\\"    --> return=$root[C]\\foo; lastseg=""    (without AT_IGNORE_TRAILING_SLASHES)
 *  - upath = "C:\\foo\\"    --> return=$root[C];      lastseg="foo" (with AT_IGNORE_TRAILING_SLASHES)
 *  - upath = "C:\\foo\\bar" --> return=$root[C]\\foo; lastseg="bar"
 * Irregardless of `AT_DOSPATH', `upath' starting with "\\\\unix\\" has special semantics:
 *  - upath = "\\\\unix\\"         --> return=$root;         lastseg=""
 *  - upath = "\\\\unix\\foo"      --> return=$root;         lastseg="foo"
 *  - upath = "\\\\unix\\foo/bar"  --> return=$root/foo;     lastseg="bar"
 *  - upath = "\\\\unix\\foo\\bar" --> return=$root/foo;     lastseg="bar"
 *  - upath = "\\\\unix\\."        --> return=$cwd;          lastseg=""
 *  - upath = "\\\\unix\\.\\foo"   --> return=$cwd;          lastseg="foo"
 *  - upath = "\\\\unix\\./foo"    --> return=$cwd;          lastseg="foo"
 *  - upath = "\\\\unix\\.."       --> return=$cwd/..;       lastseg=""
 *  - upath = "\\\\unix\\..\\foo"  --> return=$cwd/..;       lastseg="foo"
 *  - upath = "\\\\unix\\../foo"   --> return=$cwd/..;       lastseg="foo"
 *
 * [*] For $cwd, use `cwd ? cwd : THIS_FS->fs_cwd'
 * [*] For $root, use `THIS_FS->fs_root'
 *
 * @param: atflags: Set of:
 *  - AT_DOSPATH:                 Use DOS path semantics
 *  - AT_NO_AUTOMOUNT:            Currently ignored
 *  - AT_EMPTY_PATH:              `upath'  may be an  empty string, which cases
 *                                `cwd ? cwd : THIS_FS->fs_cwd' to be returned.
 *  - AT_IGNORE_TRAILING_SLASHES: Ignore trailing slashes
 *  - Other flags are silently ignored. */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((2)) REF struct path *KCALL
path_traverse_ex(struct path *cwd, u32 *__restrict premaining_symlinks,
                 /*utf-8*/ USER CHECKED char const *upath,
                 /*out_opt*/ /*utf-8*/ USER CHECKED char const **plastseg DFL(__NULLPTR),
                 /*out_opt*/ u16 *plastlen DFL(__NULLPTR), atflag_t atflags DFL(0))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY, E_IOERROR,
		       E_BADALLOC, ...);

/* Same as `path_traverse_ex',  but automatically keep  track of symlinks,  as
 * well as pass `cwd = fd_cwd == AT_FDCWD ? NULL : handles_lookuppath(fd_cwd)' */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct path *KCALL
path_traverse(fd_t fd_cwd, /*utf-8*/ USER CHECKED char const *upath,
              /*out_opt*/ /*utf-8*/ USER CHECKED char const **plastseg DFL(__NULLPTR),
              /*out_opt*/ u16 *plastlen DFL(__NULLPTR), atflag_t atflags DFL(0))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...);
#ifdef __INTELLISENSE__
#define path_traverse_ex_r path_traverse_ex
#define path_traverse_r    path_traverse
#else /* __INTELLISENSE__ */
#define path_traverse_ex_r(...) vfs_recent(THIS_VFS, path_traverse_ex(__VA_ARGS__))
#define path_traverse_r(...)    vfs_recent(THIS_VFS, path_traverse(__VA_ARGS__))
#endif /* !__INTELLISENSE__ */



/* Helper wrapper that combines `path_traverse_ex()' with `path_expandchildnode()'
 * @param: atflags: Set of: `AT_DOSPATH | AT_NO_AUTOMOUNT | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW' */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct fnode *KCALL
path_traversefull_ex(struct path *cwd, u32 *__restrict premaining_symlinks,
                     /*utf-8*/ USER CHECKED char const *upath, atflag_t atflags DFL(0),
                     /*out[1..1]_opt*/ REF struct path **presult_path DFL(__NULLPTR),
                     /*out[1..1]_opt*/ REF struct fdirent **presult_dirent DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...);

/* Helper wrapper that combines `path_traverse()' with `path_expandchildnode()'
 * @param: atflags: Set of: `AT_DOSPATH | AT_NO_AUTOMOUNT | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW' */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct fnode *KCALL
path_traversefull(fd_t fd_cwd, /*utf-8*/ USER CHECKED char const *upath, atflag_t atflags DFL(0),
                  /*out[1..1]_opt*/ REF struct path **presult_path DFL(__NULLPTR),
                  /*out[1..1]_opt*/ REF struct fdirent **presult_dirent DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...);


/* High-level implementation of `unlink(2)' / `rmdir(2)'.
 * @param: atflags: At least one of `AT_REMOVEREG | AT_REMOVEDIR', optionally
 *                  or'd with `AT_DOSPATH' (other flags are silently ignored)
 * @throw: E_WOULDBLOCK:                  Preemption is disabled, and operation would have blocked.
 * @throw: E_SEGFAULT:                    Faulty pointer
 * @throw: E_FSERROR_ACCESS_DENIED:       Missing W/X permissions for `self'
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR: `name' is S_IFREG, but `AT_REMOVEREG' isn't given
 * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_UNLINK:  `name' is S_IFDIR, but `AT_REMOVEDIR' isn't given
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT: `name' refers to a mounting point
 * @throw: E_FSERROR_FILE_NOT_FOUND:      `name' could not be found
 * @throw: E_FSERROR_READONLY:            ...
 * @throw: E_IOERROR:                     ...
 * @throw: E_BADALLOC:                    ... */
FUNDEF BLOCKING NONNULL((1)) void KCALL
path_remove(struct path *__restrict self,
            /*utf-8*/ USER CHECKED char const *name, u16 namelen, atflag_t atflags DFL(0),
            /*out[1..1]_opt*/ REF struct fnode **pdeleted_node DFL(__NULLPTR),
            /*out[1..1]_opt*/ REF struct fdirent **pdeleted_dirent DFL(__NULLPTR),
            /*out[0..1]_opt*/ REF struct path **pdeleted_path DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_READONLY, E_IOERROR, E_BADALLOC, ...);


/* High-level  implementation of the `rename(2)' system call.
 * This function also handles the case where `newname' refers
 * to a pre-existing  directory, in which  case `oldname'  is
 * moved into said directory, though will keep its name after
 * the process has completed.
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
 *                          AT_RENAME_MOVETODIR' (other flags are silently ignored)
 *                  NOTE: `AT_RENAME_MOVETODIR' supersedes the absence of `AT_RENAME_NOREPLACE'
 * @throw: E_WOULDBLOCK:                      Preemption is disabled, and operation would have blocked.
 * @throw: E_SEGFAULT:                        Faulty pointer
 * @throw: E_FSERROR_ACCESS_DENIED:           Missing write permissions for old/new directory
 * @throw: E_FSERROR_FILE_NOT_FOUND:          `oldname' could not be found
 * @throw: E_FSERROR_FILE_NOT_FOUND:          `newname' could not be found and `AT_RENAME_EXCHANGE' was given
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:       Paths point to different filesystems
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RENAME: ...
 * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_RENAME: ...
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS:     `AT_RENAME_NOREPLACE' was given and `newname' already exists.
 *                                            When `AT_RENAME_MOVETODIR' is also given: ... and isn't  dir,
 *                                            or is is a directory and already contains a file `oldname'
 * @throw: E_FSERROR_ILLEGAL_PATH:            newname isn't a valid filename for the target filesystem
 * @throw: E_FSERROR_DIRECTORY_MOVE_TO_CHILD: The move would make a directory become a child of itself
 * @throw: E_FSERROR_DISK_FULL:               ...
 * @throw: E_FSERROR_READONLY:                ...
 * @throw: E_IOERROR:                         ...
 * @throw: E_BADALLOC:                        ... */
FUNDEF BLOCKING NONNULL((1, 4)) void KCALL
path_rename(struct path *oldpath, /*utf-8*/ USER CHECKED char const *oldname, u16 oldnamelen,
            struct path *newpath, /*utf-8*/ USER CHECKED char const *newname, u16 newnamelen,
            atflag_t atflags DFL(0), __BOOL check_permissions DFL(1),
            /*out[1..1]_opt*/ REF struct fdirent **pold_dirent DFL(__NULLPTR),
            /*out[1..1]_opt*/ REF struct fdirent **pnew_dirent DFL(__NULLPTR),
            /*out[1..1]_opt*/ REF struct fnode **prenamed_node DFL(__NULLPTR),
            /*out[0..1]_opt*/ REF struct fnode **preplaced_node DFL(__NULLPTR),
            /*out[1..1]_opt*/ REF struct path **ptarget_path DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_PATH_NOT_FOUND, E_FSERROR_ACCESS_DENIED, E_FSERROR_IS_A_MOUNTING_POINT,
		       E_FSERROR_FILE_NOT_FOUND, E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_DIRECTORY_MOVE_TO_CHILD, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_IOERROR, E_BADALLOC, ...);




/* Print a human-readable representation of a given path `self':
 * @param: atflags: Set of:
 *   - AT_PATHPRINT_INCTRAIL:   Print a trailing backslash unless one was already printed
 *                              by  the path itself (as is the case when printing `root')
 *   - AT_DOSPATH:              Print the path as a DOS-path (including drive letters).
 *                              NOTE: In this mode,  if the path  reaches `root' before  a
 *                                    DOS drive is encountered, the path will be pre-fixed
 *                                    with "\\\\unix\\", indicative  of it being  relative
 *                                    to the UNIX filesystem root.
 *   - _AT_PATHPRINT_REACHABLE: Assume that `root' is reachable from `self'. When this  flag
 *                              isn't given, a check is made for `self' being reachable, and
 *                              if it turns out that it isn't, "\\\\?\\" is printed, and the
 *                              function returns immediately.
 * @param: root: When non-NULL, stop printing with this path is reached. Otherwise,
 *               print the entire path-tree until the *true* filesystem root  path,
 *               which is the one with a NULL parent pointer. */
FUNDEF NONNULL((1, 2)) ssize_t KCALL
path_print(struct path *__restrict self, __pformatprinter printer, void *arg,
           atflag_t atflags DFL(0), struct path *root DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);

/* Helper  wrapper for `path_print' that follows up the call by printing
 * the given `dentry_name...+=dentry_namelen'. You should always include
 * `AT_PATHPRINT_INCTRAIL'  when calling this function; else the printed
 * path may be invalid. */
FUNDEF NONNULL((1, 4)) ssize_t KCALL
path_printent(struct path *__restrict self,
              USER CHECKED char const *dentry_name, u16 dentry_namelen,
              __pformatprinter printer, void *arg,
              atflag_t atflags DFL(AT_PATHPRINT_INCTRAIL),
              struct path *root DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT);


/* Helper functions for printing a path into a user-space buffer.
 * @return: * : The required buffer size (including a trailing NUL-character) */
FUNDEF NONNULL((1)) size_t KCALL
path_sprint(struct path *__restrict self, USER CHECKED char *buffer, size_t buflen,
            atflag_t atflags DFL(0), struct path *root DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
FUNDEF NONNULL((1)) size_t KCALL
path_sprintent(struct path *__restrict self,
               USER CHECKED char const *dentry_name, u16 dentry_namelen,
               USER CHECKED char *buffer, size_t buflen,
               atflag_t atflags DFL(AT_PATHPRINT_INCTRAIL),
               struct path *root DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
/* Like above, but don't print a trailing NUL and return length w/o said NUL
 * @return: * : The required buffer size (excluding a trailing NUL, which also isn't printed) */
FUNDEF NONNULL((1)) size_t KCALL
path_sprint_without_nul(struct path *__restrict self, USER CHECKED char *buffer, size_t buflen,
                        atflag_t atflags DFL(0), struct path *root DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
FUNDEF NONNULL((1)) size_t KCALL
path_sprintent_without_nul(struct path *__restrict self,
                           USER CHECKED char const *dentry_name, u16 dentry_namelen,
                           USER CHECKED char *buffer, size_t buflen,
                           atflag_t atflags DFL(AT_PATHPRINT_INCTRAIL),
                           struct path *root DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_SEGFAULT);





/* Mounting point descriptor. */
struct pathmount
#ifdef __cplusplus
    : path                           /* Underlying path */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct path          pm_path;    /* Underlying path */
#define _pathmount_path_ pm_path.
#else /* !__cplusplus */
#define _pathmount_path_ /* nothing */
#endif /* __cplusplus */
	LIST_ENTRY(pathmount)     pm_fsmount; /* [0..1][lock(path_getsuper(this)->fs_mountslock)] Link entry in the
	                                       * associated superblock's list  of mounting points.  This link  also
	                                       * holds a reference to `self->p_dir->fn_super->fs_sys->ffs_drv'. */
	LIST_ENTRY(REF pathmount) pm_vsmount; /* [0..1][lock(:VFS->vf_mountslock)]
	                                       * Link entry in the list of mounting points defined by the owning VFS. */
};


/* Allocate mounting point paths */
#define _pathmount_alloc_atomic_nx() ((struct pathmount *)kmalloc_nx(sizeof(struct pathmount), GFP_ATOMIC))
#define _pathmount_alloc()           ((struct pathmount *)kmalloc(sizeof(struct pathmount), GFP_NORMAL))
#define _pathmount_free(p)           kfree(p)

#if 1 /* For now... */
#define path_free(p) kfree(p)
#else
#define path_free(p) (path_ismount(p) ? _pathmount_free(p) : _path_free(p))
#endif


/* Replace `self' with a mounting point for `dir'. If appropriate, the
 * caller is responsible for checking  for an existing mounting  point
 * (by  use of `path_ismount(self)'), if such a case isn't allowed, as
 * usually handled by throwing `E_FSERROR_PATH_ALREADY_MOUNTED'.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH:
 *         `self' has a parent which has been marked as `PATH_CLDLIST_DELETED',
 *         or `self' is a VFS root path who's VFS controller has been destroyed
 *         or altered to point to some other path.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED:
 *         The superblock of `dir' indicate `FSUPER_MOUNTS_DELETED'
 * @param: umount_flags: Same flags as  taken by  `path_umount()::umount_flags'.
 *                       These flags are used to describe the used behavior when
 *                       `self' is already a mounting point, or a mounting point
 *                       exists somewhere on a child-path of `self'.
 * @return: * :   The  new  path  node  replacing   `self'  and  pointing  to   `dir'.
 *                This path node is also referenced by `_path_getvfs(self)->vf_mounts'
 *                and has replaced `self' within the filesystem hierarchy, though  any
 *                path-relative filesystem operations that use some existing reference
 *                to `self' will continue to operate  with the old path `self'  (since
 *                the old path didn't get modified but replaced with a newly allocated
 *                path).
 * @return: NULL: `dir' can no longer be mounted because:
 *                `dir->fn_super->fs_mounts.lh_first == FSUPER_MOUNTS_DELETED' */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct pathmount *KCALL
path_mount(struct path *__restrict self,
           struct fdirnode *__restrict dir,
           uintptr_t umount_flags DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_DELETED, ...);

/* Unmount the  a given  path `self',  as well  as  all
 * child-paths of it which may also be mounting points.
 * @param: umount_flags: Set of `0 | MNT_DETACH' (other flags are silently ignored)
 *          - MNT_DETACH: Allow  unlinked `struct pathmount' to lazily unbind themselves
 *                        from `struct fsuper::fs_mounts' of associated superblocks.  As
 *                        a result, a superblock unmounted  in this manner continues  to
 *                        be fully accessible to anyone that references some `path' from
 *                        which a mounting  point (such as  `self') is reachable.  Else,
 *                        any affect `struct path_mount' will be unbinding itself lazily
 *                        during `path_destroy()'.
 *                        Reminder: Once `struct fsuper::fs_mounts' becomes empty, a call
 *                                  to  `fsuper_delete()' causes any futher file activity
 *                                  to cease.
 * @return: true:  `self' was unmounted.
 * @return: false: `self' had already been unmounted. */
FUNDEF BLOCKING NONNULL((1)) __BOOL KCALL
path_umount(struct pathmount *__restrict self, uintptr_t umount_flags DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);



/* Open (or create) a file, the same way user-space open(2) works. */
FUNDEF BLOCKING WUNUSED NONNULL((2)) REF struct handle KCALL
path_open_ex(struct path *cwd, u32 *__restrict premaining_symlinks,
             USER CHECKED char const *filename,
             oflag_t oflags, mode_t mode DFL(0));
FUNDEF BLOCKING WUNUSED REF struct handle KCALL
path_open(fd_t fd_cwd, USER CHECKED char const *filename,
          oflag_t oflags, mode_t mode DFL(0));

/* Sets of `R_OK | W_OK' corresponding to the specified access-mode. */
DATDEF unsigned int const fnode_access_accmode[__O_ACCMODE + 1];


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_PATH_H */
