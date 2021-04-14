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
#ifndef GUARD_KERNEL_INCLUDE_FS_VFS_H
#define GUARD_KERNEL_INCLUDE_FS_VFS_H 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/cache.h>
#include <kernel/types.h>

#ifndef __INTELLISENSE__
#include <kernel/handle.h>
#endif /* !__INTELLISENSE__ */

#include <sched/atomic64.h>

#include <hybrid/__atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/crt/format-printer.h>
#include <kos/kernel/handle.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__

struct path;
struct vfs;
struct fs;
struct directory_entry;

struct mounted_path {
	struct path                *mp_path;     /* [1..1][const] The associated path. */
	REF struct directory_node  *mp_orig;     /* [0..1][lock(mp_path->p_lock)]  The  original  node  (for  when  this
	                                          * path is used as a mounting point) (or `NULL' for the VFS root path). */
	REF struct superblock      *mp_super;    /* [1..1][lock(mp_path->p_lock)][== :p_parent->i_super]
	                                          * The superblock being mounted. */
	LIST_ENTRY(path)            mp_fsmount;  /* [lock(mp_path->p_lock && mp_super->s_mount_lock)]
	                                          * [CHAIN(mp_super->s_mount)]
	                                          * Chain of mounting points of the associated super-block. */
	LIST_ENTRY(REF path)        mp_vfsmount; /* [lock(mp_path->p_lock && mp_path->p_vfs->v_mount_lock)]
	                                          * [CHAIN(mp_path->p_vfs->v_mount)]
	                                          * Chain of mounting points of the associated super-block. */
	struct path                *mp_pending;  /* Used to chain paths that are pending being unmounted,
	                                          * either  within  their associated  VFS  or superblock. */
};


#define PATH_DEFAULT_MASK 3
struct path {
	WEAK refcnt_t               p_refcnt;  /* Reference counter. */
	struct vfs                 *p_vfs;     /* [1..1][const][== this == p_path ? this : p_parent->p_vfs]
	                                        * The associated VFS descriptor. */
	REF struct path            *p_parent;  /* [0..1][const] Parent path, or NULL for FS-root. */
	struct atomic_rwlock        p_lock;    /* Lock for accessing this path component. */
	REF struct directory_node  *p_inode;   /* [0..1][lock(p_lock)] The associated directory (or `NULL' if the root-path is unmounted).
	                                        * NOTE: Query functions such as `path_child()' are allowed
	                                        *       to  assume  that  this field  is  always non-NULL. */
	struct mounted_path        *p_mount;   /* [0..1][lock(p_lock)][owned_if(!= &p_vfs->v_rootmount)] Mounting point data. */
	REF struct directory_entry *p_dirent;  /* [1..1][const] Name of this directory entry (empty for VFS root). */
	LIST_ENTRY(path)            p_dirnext; /* [0..1][lock(p_parent->p_lock)][valid_if(p_parent != NULL)]
	                                        * Next sibling directory  with the same  `p_dirent->de_hash' */
	size_t                      p_cldmask; /* [lock(p_lock)] Mask for the `p_cldlist' hash-map. */
	size_t                      p_cldsize; /* [lock(p_lock)] Amount of entires within the `p_cldlist' hash-map. */
	struct path               **p_cldlist; /* [0..1][lock(p_lock)][0..p_cldmask + 1][lock(p_lock)][owned] Child paths. */
	struct path                *p_delpend; /* [0..1][CHAIN(->p_delpend)][lock(p_lock)] Chain of paths that are pending removal from `p_cldlist'. */
	LIST_ENTRY(path)            p_recent;  /* [0..1][lock(p_vfs->v_recent_lock)] Chain of recently used paths. */
	size_t                      p_isdrive; /* [lock(p_vfs->v_drives_lock)] Non-zero   if  this  path  is  a  drive  root.
	                                        * This field represents the number of drives for which this path is the root. */
};

/* Path allocation functions. (using a cache, because of  how
 * often path objects can potentially be allocated and freed) */
DECLARE_PREALLOCATION_CACHE(FUNDEF, path, struct path)

/* Destroy (and free) a given path `self' */
FUNDEF NOBLOCK void NOTHROW(KCALL path_destroy)(struct path *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct path, p_refcnt, path_destroy)

/* Locking helper functions for `struct path::p_lock' */
FUNDEF void (KCALL path_lock_read)(struct path *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF void (KCALL path_lock_write)(struct path *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF bool (KCALL path_lock_upgrade)(struct path *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED bool NOTHROW(KCALL path_lock_read_nx)(struct path *__restrict self);
FUNDEF WUNUSED bool NOTHROW(KCALL path_lock_write_nx)(struct path *__restrict self);
FUNDEF WUNUSED unsigned int NOTHROW(KCALL path_lock_upgrade_nx)(struct path *__restrict self);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL path_lock_tryread)(struct path *__restrict self);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL path_lock_trywrite)(struct path *__restrict self);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL path_lock_tryupgrade)(struct path *__restrict self);
FUNDEF NOBLOCK void NOTHROW(KCALL path_lock_endread)(struct path *__restrict self);
FUNDEF NOBLOCK void NOTHROW(KCALL path_lock_endwrite)(struct path *__restrict self);
FUNDEF NOBLOCK void NOTHROW(KCALL path_lock_end)(struct path *__restrict self);
FUNDEF NOBLOCK void NOTHROW(KCALL path_lock_downgrade)(struct path *__restrict self);
FUNDEF NOBLOCK void NOTHROW(KCALL path_lock_tryservice)(struct path *__restrict self);
#define path_lock_reading(self)  sync_reading(&(self)->p_lock)
#define path_lock_writing(self)  sync_writing(&(self)->p_lock)
#define path_lock_canread(self)  sync_canread(&(self)->p_lock)
#define path_lock_canwrite(self) sync_canwrite(&(self)->p_lock)
__DEFINE_SYNC_RWLOCK(struct path,
                     path_lock_tryread,
                     path_lock_read,
                     path_lock_read_nx,
                     path_lock_endread,
                     path_lock_reading,
                     path_lock_canread,
                     path_lock_trywrite,
                     path_lock_write,
                     path_lock_write_nx,
                     path_lock_endwrite,
                     path_lock_writing,
                     path_lock_canwrite,
                     path_lock_end,
                     path_lock_tryupgrade,
                     path_lock_upgrade,
                     path_lock_upgrade_nx,
                     path_lock_downgrade)

/* Mount or unmount a given directory under the specified path.
 * NOTE: Calling `path_umount()' will automatically clear the caches of recently
 *       used  INodes and paths (`inode_recent_clear()' / `path_recent_clear()')
 * NOTE: When `path_umount()' removes the last mounting point for some filesystem,
 *      `superblock_set_unmounted()' is called on the associated superblock.
 * @param: override_existing: When true, override  an existing mounting  point.
 *                            Otherwise, throw `E_FSERROR_PATH_ALREADY_MOUNTED'
 *                            if the given path `self' is already mounted.
 * @throw: E_FSERROR_PATH_ALREADY_MOUNTED: When   `override_existing'   is  false,
 *                                         and `self' is already a mounting point.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED:
 *                            Cannot create new mounting points: `v_mount' has been set to `VFS_MOUNT_ILLEGAL',
 *                            or the superblock associated  with `node' has already  been set to be  unmounted. */
FUNDEF void KCALL path_mount(struct path *__restrict self,
                             struct directory_node *__restrict node,
                             bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_PATH_ALREADY_MOUNTED, E_FSERROR_DELETED, ...);
#ifdef __cplusplus
extern "C++" {
LOCAL NONNULL((1, 2)) void KCALL
path_mount(struct path *__restrict self,
           struct superblock_type *__restrict filesystem_mount_type,
           struct basic_block_device *filesystem_mount_device,
           uintptr_t filesystem_mount_flags DFL(SUPERBLOCK_FNORMAL),
           UNCHECKED USER char *filesystem_mount_args DFL(__NULLPTR),
           bool *pfilesystem_mount_new_superblock_created DFL(__NULLPTR),
           bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_PATH_ALREADY_MOUNTED, E_FSERROR_DELETED, ...) {
	REF struct superblock *sb;
	sb = superblock_open(filesystem_mount_type,
	                     filesystem_mount_device,
	                     filesystem_mount_flags,
	                     filesystem_mount_args,
	                     pfilesystem_mount_new_superblock_created);
	FINALLY_DECREF_UNLIKELY(sb);
	path_mount(self, sb, override_existing);
}

LOCAL NONNULL((1, 2)) void KCALL
path_mount(struct path *__restrict self,
           struct superblock_type *__restrict filesystem_mount_type,
           USER CHECKED char const *filesystem_mount_device,
           uintptr_t filesystem_mount_flags DFL(SUPERBLOCK_FNORMAL),
           UNCHECKED USER char *filesystem_mount_args DFL(__NULLPTR),
           bool *pfilesystem_mount_new_superblock_created DFL(__NULLPTR),
           bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_PATH_ALREADY_MOUNTED, E_FSERROR_DELETED, ...) {
	REF struct superblock *sb;
	sb = superblock_open(filesystem_mount_type,
	                     filesystem_mount_device,
	                     filesystem_mount_flags,
	                     filesystem_mount_args,
	                     pfilesystem_mount_new_superblock_created);
	FINALLY_DECREF_UNLIKELY(sb);
	path_mount(self, sb, override_existing);
}

LOCAL NONNULL((1, 2)) void KCALL
path_mount(struct path *__restrict self,
           struct superblock_type *__restrict filesystem_mount_type,
           uintptr_t filesystem_mount_flags DFL(SUPERBLOCK_FNORMAL),
           UNCHECKED USER char *filesystem_mount_args DFL(__NULLPTR),
           bool *pfilesystem_mount_new_superblock_created DFL(__NULLPTR),
           bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_PATH_ALREADY_MOUNTED, E_FSERROR_DELETED, ...) {
	REF struct superblock *sb;
	sb = superblock_open(filesystem_mount_type,
	                     filesystem_mount_flags,
	                     filesystem_mount_args,
	                     pfilesystem_mount_new_superblock_created);
	FINALLY_DECREF_UNLIKELY(sb);
	path_mount(self, sb, override_existing);
}

LOCAL NONNULL((1)) void KCALL
path_mount(struct path *__restrict self,
           USER CHECKED char const *filesystem_mount_type,
           struct basic_block_device *filesystem_mount_device,
           uintptr_t filesystem_mount_flags DFL(SUPERBLOCK_FNORMAL),
           UNCHECKED USER char *filesystem_mount_args DFL(__NULLPTR),
           bool *pfilesystem_mount_new_superblock_created DFL(__NULLPTR),
           bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_PATH_ALREADY_MOUNTED, E_FSERROR_DELETED, ...) {
	REF struct superblock *sb;
	sb = superblock_open(filesystem_mount_type,
	                     filesystem_mount_device,
	                     filesystem_mount_flags,
	                     filesystem_mount_args,
	                     pfilesystem_mount_new_superblock_created);
	FINALLY_DECREF_UNLIKELY(sb);
	path_mount(self, sb, override_existing);
}

LOCAL NONNULL((1)) void KCALL
path_mount(struct path *__restrict self,
           USER CHECKED char const *filesystem_mount_type,
           USER CHECKED char const *filesystem_mount_device,
           uintptr_t filesystem_mount_flags DFL(SUPERBLOCK_FNORMAL),
           UNCHECKED USER char *filesystem_mount_args DFL(__NULLPTR),
           bool *pfilesystem_mount_new_superblock_created DFL(__NULLPTR),
           bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_PATH_ALREADY_MOUNTED, E_FSERROR_DELETED, ...) {
	REF struct superblock *sb;
	sb = superblock_open(filesystem_mount_type,
	                     filesystem_mount_device,
	                     filesystem_mount_flags,
	                     filesystem_mount_args,
	                     pfilesystem_mount_new_superblock_created);
	FINALLY_DECREF_UNLIKELY(sb);
	path_mount(self, sb, override_existing);
}

LOCAL NONNULL((1)) void KCALL
path_mount(struct path *__restrict self,
           USER CHECKED char const *filesystem_mount_type,
           uintptr_t filesystem_mount_flags DFL(SUPERBLOCK_FNORMAL),
           UNCHECKED USER char *filesystem_mount_args DFL(__NULLPTR),
           bool *pfilesystem_mount_new_superblock_created DFL(__NULLPTR),
           bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_PATH_ALREADY_MOUNTED, E_FSERROR_DELETED, ...) {
	REF struct superblock *sb;
	sb = superblock_open(filesystem_mount_type,
	                     filesystem_mount_flags,
	                     filesystem_mount_args,
	                     pfilesystem_mount_new_superblock_created);
	FINALLY_DECREF_UNLIKELY(sb);
	path_mount(self, sb, override_existing);
}
}
#endif /* __cplusplus */

/* Delete a filesystem mounting point. */
FUNDEF void KCALL path_umount(struct path *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR_NOT_A_MOUNTING_POINT, E_IOERROR, ...);

/* Atomically  move  a  mounting  point  from  `src'  to  `dst'
 * NOTE: The caller must ensure that `dst->p_vfs == src->p_vfs' */
FUNDEF void KCALL path_movemount(struct path *__restrict dst,
                                 struct path *__restrict src,
                                 bool override_existing DFL(true))
		THROWS(E_WOULDBLOCK, E_FSERROR_NOT_A_MOUNTING_POINT,
		       E_FSERROR_PATH_ALREADY_MOUNTED, E_IOERROR, ...);

/* Indicate  that  `self' has  been  used recently,  allowing  the path  to  be cached
 * such that it will remain allocated for a while, even when not referenced elsewhere.
 * NOTE: When `self->p_vfs->v_fscount' is ZERO(0) upon entry, or drops to ZERO(0) before
 *       returning,  `self'  will  not  be  cached  as  recently  used,  and  the   call
 *       behaves as a no-op.
 * NOTE: Always re-returns `self' */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct path *
NOTHROW(KCALL path_recent)(struct path *__restrict self);

/* Clear the cache of recently used paths. */
FUNDEF NOBLOCK void NOTHROW(KCALL path_recent_clear)(struct vfs *__restrict v);



/* Print the location of a given path. */
FUNDEF NONNULL((1, 2, 5)) ssize_t KCALL
path_printex(struct path *__restrict self,
             __pformatprinter printer, void *arg,
             unsigned int mode,
             struct path *__restrict root);
#define PATH_PRINT_MODE_NORMAL   0x00000000 /* Print the path normally. */
#define PATH_PRINT_MODE_INCTRAIL 0x00000001 /* Include a trailing slash/backslash. */
#define PATH_PRINT_MODE_DOSPATH  0x00100000 /* Print the path as a DOS-path (including drive letters).
                                             * NOTE: In this mode,  if the path  reaches `root' before  a
                                             *       DOS drive is encountered, the path will be pre-fixed
                                             *       with  `\\unix\', indicative of  it being relative to
                                             *       the UNIX filesystem root. */
#define PATH_PRINT_MODE_EXCDRIVE 0x00000002 /* Exclude the name of the associated drive in `PATH_PRINT_MODE_DOSPATH' mode. */
#define PATH_PRINT_MODE_CANREACH 0x00000004 /* Assume that `root' is reachable from `self' */

/* Same as path_printex() with `PATH_PRINT_MODE_INCTRAIL',
 * and using the current FS-mode & root. */
FUNDEF NONNULL((1, 2)) ssize_t KCALL
path_print(struct path *__restrict self,
           __pformatprinter printer, void *arg);


/* Print the location of a given path+entry.
 * @param: mode: Set of `PATH_PRINT_MODE_DOSPATH|PATH_PRINT_MODE_EXCDRIVE' */
FUNDEF NONNULL((1, 4)) ssize_t KCALL
path_printentex(struct path *__restrict self,
                USER CHECKED char const *dentry_name, u16 dentry_namelen,
                __pformatprinter printer, void *arg,
                unsigned int mode,
                struct path *__restrict root);
/* Same as path_printentex(), using the current FS-mode & root. */
FUNDEF NONNULL((1, 4)) ssize_t KCALL
path_printent(struct path *__restrict self,
              USER CHECKED char const *dentry_name, u16 dentry_namelen,
              __pformatprinter printer, void *arg);




/* Helper functions for printing a path into a user-space buffer.
 * @return: * : The required buffer size (including a trailing NUL-character) */
FUNDEF NONNULL((3, 7)) size_t KCALL path_sprintentex(USER CHECKED char *buffer, size_t buflen, struct path *__restrict self, USER CHECKED char const *dentry_name, u16 dentry_namelen, unsigned int mode, struct path *__restrict root) THROWS(E_SEGFAULT);
FUNDEF NONNULL((3)) size_t KCALL path_sprintent(USER CHECKED char *buffer, size_t buflen, struct path *__restrict self, USER CHECKED char const *dentry_name, u16 dentry_namelen) THROWS(E_SEGFAULT);
FUNDEF NONNULL((3, 5)) size_t KCALL path_sprintex(USER CHECKED char *buffer, size_t buflen, struct path *__restrict self, unsigned int mode, struct path *__restrict root) THROWS(E_SEGFAULT);
FUNDEF NONNULL((3)) size_t KCALL path_sprint(USER CHECKED char *buffer, size_t buflen, struct path *__restrict self) THROWS(E_SEGFAULT);

/* Search for a specific child path within `self', _OR_ store a reference
 * to  the INode of `self' within `*pparent_inode' when NULL is returned.
 * In the case where non-NULL is returned, `*pparent_inode' is left in an undefined state. */
FUNDEF REF struct path *KCALL
path_getchild_or_parent_inode(struct path *__restrict self,
                              USER CHECKED /*utf-8*/ char const *name,
                              u16 namelen, uintptr_t namehash,
                              REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
FUNDEF REF struct path *KCALL
path_getcasechild_or_parent_inode(struct path *__restrict self,
                                  USER CHECKED /*utf-8*/ char const *name,
                                  u16 namelen, uintptr_t namehash,
                                  REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);

/* Same as `path_getchild_or_parent_inode()', but _always_ store a reference
 * to  the  INode   of  the  given   path  `self'  within   `*pparent_inode' */
FUNDEF REF struct path *KCALL
path_getchild_and_parent_inode(struct path *__restrict self,
                               USER CHECKED /*utf-8*/ char const *name,
                               u16 namelen, uintptr_t namehash,
                               REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
FUNDEF REF struct path *KCALL
path_getcasechild_and_parent_inode(struct path *__restrict self,
                                   USER CHECKED /*utf-8*/ char const *name,
                                   u16 namelen, uintptr_t namehash,
                                   REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);

/* Create or lookup the path or a given `child_dir' within `self'
 * NOTE: This function  is meant  to be  used to  instantiate paths  that could  not
 *       be found before (aka.: those for which `path_(case)child()' returned false) */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct path *KCALL
path_newchild(struct path *__restrict self,
              struct directory_node *__restrict child_dir,
              struct directory_entry *__restrict child_entry)
		THROWS(E_BADALLOC);


/* Remove an entry from a given path.
 * @param: mode:                  Set of `DIRECTORY_REMOVE_F*', or which at least one of
 *                               `DIRECTORY_REMOVE_FREGULAR' or `DIRECTORY_REMOVE_FDIRECTORY'
 *                                must be given.
 * @param: hash:                  The result of `directory_entry_hash(name,namelen)'
 * @param: premoved_inode:        Upon success, store a reference to the removed INode here.
 * @param: premoved_dirent:       Upon success, store a reference to the removed INode's directory entry here.
 * @param: pcontaining_directory: Upon success, store a reference to the directory node from which an element got removed here.
 *                                Since   `self->p_inode'   can   arbitrarily   change   due   to   mounting,   this   is   the
 *                                only save  way  to  determine  the  exact directory  from  which  the  element  got  removed.
 * @param: premoved_path:         Upon success, store a reference to the removed path here (or `NULL' if it wasn't
 *                                a directory that  got removed, or  if that  directory didn't have  a path  node)
 * @return: * : Set of `DIRECTORY_REMOVE_STATUS_*'
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified file was already deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (self was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_FILE_NOT_FOUND:      The specified `name' could not be found
 * @throw: E_FSERROR_ACCESS_DENIED:       `DIRECTORY_REMOVE_FCHKACCESS' was set, and the calling thread is not allowed to delete the file.
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR:  The given `name' refers to a regular file, but `DIRECTORY_REMOVE_FREGULAR' isn't set
 * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_UNLINK:   The given `name' refers to a directory, but `DIRECTORY_REMOVE_FDIRECTORY' isn't set
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:                                 The given `name' refers to a mounting point
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY:                                 Attempted to remove a non-empty directory.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_UNLINK: Cannot unlink files within `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RMDIR:  Cannot remove sub-directories of `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:  Cannot truncate non-empty files to 0 bytes in order to delete their data
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
FUNDEF NONNULL((1, 2)) unsigned int KCALL
path_remove(struct path *__restrict self,
            CHECKED USER /*utf-8*/ char const *__restrict name, u16 namelen, uintptr_t hash,
            unsigned int mode DFL(DIRECTORY_REMOVE_FREGULAR | DIRECTORY_REMOVE_FDIRECTORY),
            /*out*/ REF struct inode **premoved_inode DFL(__NULLPTR),
            /*out*/ REF struct directory_entry **premoved_dirent DFL(__NULLPTR),
            /*out*/ REF struct directory_node **pcontaining_directory DFL(__NULLPTR),
            /*out*/ REF struct path **premoved_path DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_FILE_NOT_FOUND, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_NOT_A_DIRECTORY, E_FSERROR_IS_A_DIRECTORY,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...);


/* Rename/move an entry from one path to another.
 * NOTE: This function will try to emulate an unsupported `rename()' using `link()' + `unlink()'
 * @param: mode: Set of `DIRECTORY_RENAME_F*'
 * @param: source_namehash:   The result of `directory_entry_hash(source_name,source_namelen)'
 * @param: psource_dirent:    When non-NULL, store a reference to the source directory entry here.
 * @param: ptarget_dirent:    When non-NULL, store a reference to the target directory entry here.
 * @param: psource_inode:     When non-NULL, store a reference to the source INode here.
 * @param: ptarget_inode:     When non-NULL, store a reference to the target INode here.
 * @param: psource_directory: When non-NULL, store a reference to the source directory from which an element got removed here.
 * @param: ptarget_directory: When non-NULL, store a reference to the target directory to which an element got added here.
 * @param: premoved_path:     When non-NULL, store a reference to the removed child-path
 *                            of `source_path' here, or `NULL'  if no path got  removed.
 * @return: * : Set of `DIRECTORY_RENAME_STATUS_*', though never `DIRECTORY_RENAME_STATUS_REMOUNT'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RENAME: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified source file was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`source_directory' or `target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:  The given `source_name' refers to a mounting point when a child directory is being removed, and `source_path' is given
 * @throw: E_FSERROR_FILE_NOT_FOUND:      `source_name' wasn't found
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:   [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...] (Only when emulated using `link()' + `unlink()')
 * @throw: E_FSERROR_DIRECTORY_MOVE_TO_CHILD: [...]
 * @throw: E_FSERROR_ACCESS_DENIED:       [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
FUNDEF NONNULL((1, 2, 5, 6)) unsigned int KCALL
path_rename(struct path *__restrict source_path,
            CHECKED USER /*utf-8*/ char const *__restrict source_name,
            u16 source_namelen,
            uintptr_t source_namehash,
            struct path *__restrict target_path,
            CHECKED USER /*utf-8*/ char const *__restrict target_name,
            u16 target_namelen,
            unsigned int mode DFL(DIRECTORY_RENAME_FNORMAL),
            /*out*/ REF struct directory_entry **psource_dirent DFL(__NULLPTR),
            /*out*/ REF struct directory_entry **ptarget_dirent DFL(__NULLPTR),
            /*out*/ REF struct inode **psource_inode DFL(__NULLPTR),
            /*out*/ REF struct inode **ptarget_inode DFL(__NULLPTR),
            /*out*/ REF struct directory_node **psource_directory DFL(__NULLPTR),
            /*out*/ REF struct directory_node **ptarget_directory DFL(__NULLPTR),
            /*out*/ REF struct path **premoved_path DFL(__NULLPTR))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_DIRECTORY_MOVE_TO_CHILD, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_READONLY,
		       E_IOERROR, E_SEGFAULT, ...);



/* Traverse  a  relative  path,  starting   at  `cwd'  and  walking  until   the
 * requested  path was found,  or until a missing  path segment was encountered.
 * This function  will automatically  deal with  `.' and  `..' segments,  always
 * accepting `/' between directories, and  `\\' when `FS_MODE_FDOSPATH' is  set.
 * Additionally, symbolic links are followed, with the final path segment stored
 * in the provided output  arguments, with `*plastlen' set  to 0 when the  final
 * segment  was  empty  and  `FS_MODE_FIGNORE_TRAILING_SLASHES'  wasn't  set, or
 * when  the entire  input path is  empty and `FS_MODE_FEMPTY_PATH'  was set, or
 * if the last  segment of the  input path  was one of  `.' or `..',  or if  the
 * input path  referred  to  the root  path,  or  a drive  root  (`/'  or  `C:')
 * Additionally,  when `plastseg' itself is `NULL', always walk the entire path.
 *     INPUT      |  RETURN  |  LASTSEG
 *    ------------+----------+------------
 *     ""         |  "."     |  ""         (Throws `E_FSERROR_ILLEGAL_PATH' unless `FS_MODE_FEMPTY_PATH' is set)
 *     "/"        |  "/"     |  ""
 *     "C:"       |  "C:"    |  ""
 *     ".."       |  "./.."  |  ""
 *     "."        |  "."     |  ""
 *     "foo"      |  "."     |  "foo"
 *     "foo/bar"  |  "./foo" |  "bar"
 *     "/foo"     |  "/"     |  "foo"
 *    ------------+----------+------------
 *
 * @param: mode: Set of `FS_MODE_FDOSPATH | FS_MODE_FIGNORE_TRAILING_SLASHES |
 *                       FS_MODE_FEMPTY_PATH | FS_MODE_FSYMLINK_NOFOLLOW'
 *               NOTE: `FS_MODE_FSYMLINK_NOFOLLOW' only has an effect when no last-seg pointers
 *                      were given, in which case the last segment being a symlink will cause an
 *                     `E_FSERROR_TOO_MANY_SYMBOLIC_LINKS' exception to be thrown.
 * @param: premaining_symlinks: [in|out] When non-NULL, load/store the amount of remaining
 *                              symbolic link indirection  which the path  may have  still
 *                              traversed during evaluation (aka.:  the limit on how  many
 *                              symbolic links may still be traversed during further  path
 *                              walks)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH:
 *                                            One of the accessed directory INodes had been deleted.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED:
 *                                            One of the accessed directory INodes had been unmounted.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                                            Failed to read entries from one of the traversed directories.
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_WALK:
 *                                            Attempted to traverse something other than a directory, or symbolic link
 * @throw: E_FSERROR_PATH_NOT_FOUND:          An addressed path could not be found.
 * @throw: E_FSERROR_ILLEGAL_PATH:            The final path segment is longer than `0xffff'
 * @throw: E_SEGFAULT:                        Failed to access the given `upath'
 * @throw: E_FSERROR_ACCESS_DENIED:           Attempted to traverse a directory without privilege.
 * @throw: E_FSERROR_TOO_MANY_SYMBOLIC_LINKS: Too many symbolic links were encountered.
 * @throw: E_IOERROR:                         [...] */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
path_traverse_ex(struct fs *__restrict filesystem,
                 struct path *cwd,
                 struct path *root,
                 USER CHECKED /*utf-8*/ char const *upath,
                 USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                 u16 *plastlen DFL(__NULLPTR),
                 fsmode_t mode DFL(FS_MODE_FNORMAL),
                 u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traverse(struct fs *__restrict filesystem,
              USER CHECKED /*utf-8*/ char const *upath,
              USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
              u16 *plastlen DFL(__NULLPTR),
              fsmode_t mode DFL(FS_MODE_FNORMAL),
              u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
path_traversen_ex(struct fs *__restrict filesystem,
                  struct path *cwd,
                  struct path *root,
                  USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                  USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                  u16 *plastlen DFL(__NULLPTR),
                  fsmode_t mode DFL(FS_MODE_FNORMAL),
                  u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traversen(struct fs *__restrict filesystem,
               USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
               USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
               u16 *plastlen DFL(__NULLPTR),
               fsmode_t mode DFL(FS_MODE_FNORMAL),
               u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traverse_at(struct fs *__restrict filesystem, unsigned int dirfd,
                 USER CHECKED /*utf-8*/ char const *upath,
                 USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                 u16 *plastlen DFL(__NULLPTR),
                 fsmode_t mode DFL(FS_MODE_FNORMAL),
                 u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traversen_at(struct fs *__restrict filesystem, unsigned int dirfd,
                  USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                  USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                  u16 *plastlen DFL(__NULLPTR),
                  fsmode_t mode DFL(FS_MODE_FNORMAL),
                  u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);


/* Traverse the entirety of a given `upath', returning the point-to node,
 * as well as optionally related components.
 * @param: follow_final_link: When true, follow symbolic links contained within the final path component. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct inode *KCALL
path_traversefull_ex(struct fs *__restrict filesystem,
                     struct path *cwd,
                     struct path *root,
                     USER CHECKED /*utf-8*/ char const *upath,
                     bool follow_final_link DFL(true),
                     fsmode_t mode DFL(FS_MODE_FNORMAL),
                     u32 *premaining_symlinks DFL(__NULLPTR),
                     REF struct path **pcontaining_path DFL(__NULLPTR),
                     REF struct directory_node **pcontaining_directory DFL(__NULLPTR),
                     REF struct directory_entry **pcontaining_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversefull_at(struct fs *__restrict filesystem, unsigned int dirfd,
                     USER CHECKED /*utf-8*/ char const *upath,
                     bool follow_final_link DFL(true),
                     fsmode_t mode DFL(FS_MODE_FNORMAL),
                     u32 *premaining_symlinks DFL(__NULLPTR),
                     REF struct path **pcontaining_path DFL(__NULLPTR),
                     REF struct directory_node **pcontaining_directory DFL(__NULLPTR),
                     REF struct directory_entry **pcontaining_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversefull(struct fs *__restrict filesystem,
                  USER CHECKED /*utf-8*/ char const *upath,
                  bool follow_final_link DFL(true),
                  fsmode_t mode DFL(FS_MODE_FNORMAL),
                  u32 *premaining_symlinks DFL(__NULLPTR),
                  REF struct path **pcontaining_path DFL(__NULLPTR),
                  REF struct directory_node **pcontaining_directory DFL(__NULLPTR),
                  REF struct directory_entry **pcontaining_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct inode *KCALL
path_traversenfull_ex(struct fs *__restrict filesystem,
                      struct path *cwd,
                      struct path *root,
                      USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                      bool follow_final_link DFL(true),
                      fsmode_t mode DFL(FS_MODE_FNORMAL),
                      u32 *premaining_symlinks DFL(__NULLPTR),
                      REF struct path **pcontaining_path DFL(__NULLPTR),
                      REF struct directory_node **pcontaining_directory DFL(__NULLPTR),
                      REF struct directory_entry **pcontaining_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversenfull_at(struct fs *__restrict filesystem, unsigned int dirfd,
                      USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                      bool follow_final_link DFL(true),
                      fsmode_t mode DFL(FS_MODE_FNORMAL),
                      u32 *premaining_symlinks DFL(__NULLPTR),
                      REF struct path **pcontaining_path DFL(__NULLPTR),
                      REF struct directory_node **pcontaining_directory DFL(__NULLPTR),
                      REF struct directory_entry **pcontaining_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversenfull(struct fs *__restrict filesystem,
                   USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                   bool follow_final_link DFL(true),
                   fsmode_t mode DFL(FS_MODE_FNORMAL),
                   u32 *premaining_symlinks DFL(__NULLPTR),
                   REF struct path **pcontaining_path DFL(__NULLPTR),
                   REF struct directory_node **pcontaining_directory DFL(__NULLPTR),
                   REF struct directory_entry **pcontaining_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);



/* Same as the functions above, but also mark the returned path as recently used. */
#ifdef __INTELLISENSE__
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
path_traverse_ex_recent(struct fs *__restrict filesystem,
                        struct path *cwd,
                        struct path *root,
                        USER CHECKED /*utf-8*/ char const *upath,
                        USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                        u16 *plastlen DFL(__NULLPTR),
                        fsmode_t mode DFL(FS_MODE_FNORMAL),
                        u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traverse_recent(struct fs *__restrict filesystem,
                     USER CHECKED /*utf-8*/ char const *upath,
                     USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                     u16 *plastlen DFL(__NULLPTR),
                     fsmode_t mode DFL(FS_MODE_FNORMAL),
                     u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
path_traversen_ex_recent(struct fs *__restrict filesystem,
                         struct path *cwd,
                         struct path *root,
                         USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                         USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                         u16 *plastlen DFL(__NULLPTR),
                         fsmode_t mode DFL(FS_MODE_FNORMAL),
                         u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traversen_recent(struct fs *__restrict filesystem,
                      USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                      USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                      u16 *plastlen DFL(__NULLPTR),
                      fsmode_t mode DFL(FS_MODE_FNORMAL),
                      u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traverse_at_recent(struct fs *__restrict filesystem, unsigned int dirfd,
                        USER CHECKED /*utf-8*/ char const *upath,
                        USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                        u16 *plastlen DFL(__NULLPTR),
                        fsmode_t mode DFL(FS_MODE_FNORMAL),
                        u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traversen_at_recent(struct fs *__restrict filesystem, unsigned int dirfd,
                         USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                         USER CHECKED /*utf-8*/ char const **plastseg DFL(__NULLPTR),
                         u16 *plastlen DFL(__NULLPTR),
                         fsmode_t mode DFL(FS_MODE_FNORMAL),
                         u32 *premaining_symlinks DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...);
#else /* __INTELLISENSE__ */
#define path_traverse_ex_recent(...)  path_recent(path_traverse_ex(__VA_ARGS__))
#define path_traverse_recent(...)     path_recent(path_traverse(__VA_ARGS__))
#define path_traversen_ex_recent(...) path_recent(path_traversen_ex(__VA_ARGS__))
#define path_traversen_recent(...)    path_recent(path_traversen(__VA_ARGS__))
#define path_traverse_at_recent(...)  path_recent(path_traverse_at(__VA_ARGS__))
#define path_traversen_at_recent(...) path_recent(path_traversen_at(__VA_ARGS__))
#endif /* !__INTELLISENSE__ */






#define VFS_DEFAULT_RECENT_LIMIT 256

struct vfs
#if defined(__cplusplus) && !defined(__VFS_DEFINE_AS_C_STRUCTURE)
	: public path
#endif
{
#if !defined(__cplusplus) || defined(__VFS_DEFINE_AS_C_STRUCTURE)
	struct path            v_path;        /* The underlying path. */
#endif
	WEAK refcnt_t          v_fscount;     /* The number of file systems using this VFS as root.
	                                       * NOTE: New  mounting  points can  only be  defined when
	                                       *       this number is  non-zero, and  once this  number
	                                       *       drops down to zero, all existing mounting points
	                                       *       must be removed.
	                                       * NOTE: When accessing `v_mount' by use of `v_mount_lock',
	                                       *       the caller is required  to be holding a  reference
	                                       *       to this field. */
	struct mounted_path    v_rootmount;   /* Mounting point data for the VFS root.
	                                       * Usually   set   in    `super.p_mount' */
	struct atomic_rwlock   v_mount_lock;  /* Lock for all mounting points within this VFS (`v_mount') */
	REF struct path       *v_mount;       /* [0..1][CHAIN(->p_mount->mp_vfsmount)][lock(v_mount_lock)] Chain of pointing points.
	                                       * WARNING: This  chain  may  contain  paths with  a  reference  counter  of  ZERO(0).
	                                       * NOTE: Set to `VFS_MOUNT_ILLEGAL' when mounting becomes illegal. */
#define VFS_MOUNT_ILLEGAL ((struct path *)-1)
	struct atomic_lock     v_recent_lock; /* Lock for recently used paths. */
	REF struct path       *v_recent_list; /* [0..1][lock(v_recent_lock)] Cache of recently used paths. */
	REF struct path       *v_recent_back; /* [0..1][lock(v_recent_lock)] Cache of recently used paths. */
	size_t                 v_recent_size; /* [lock(v_recent_lock)] Number of cached, recently used paths. */
	size_t                 v_recent_limit;/* [lock(v_recent_lock)] Max number of recently used paths. */
#define VFS_DRIVECOUNT  (('Z' - 'A') + 1)
	struct atomic_rwlock   v_drives_lock; /* Lock for accessing DOS drive mounting points. */
	REF struct path       *v_drives[VFS_DRIVECOUNT]; /* [0..1][lock(v_drives_lock)][*]  Root  paths   for  DOS   drives.
	                                                  * Each is set to `VFS_MOUNT_ILLEGAL' once binding becomes illegal. */
};

/* Increment/decrement the `v_fscount' reference counter. */
#define vfs_inc_fscount(x) __hybrid_atomic_inc((x)->v_fscount, __ATOMIC_SEQ_CST)
#define vfs_dec_fscount(x) (void)(__hybrid_atomic_decfetch((x)->v_fscount, __ATOMIC_SEQ_CST) || (vfs_clearmounts(x), 0))

/* Called when `v_fscount' reaches ZERO(0): Clear all remaining mounting points.
 * NOTE:   This   function   also   sets   `v_mount'   to   `VFS_MOUNT_ILLEGAL'. */
FUNDEF NOBLOCK void NOTHROW(KCALL vfs_clearmounts)(struct vfs *__restrict self);

/* Allocate a new VFS object */
FUNDEF ATTR_RETNONNULL ATTR_MALLOC WUNUSED
REF struct vfs *KCALL vfs_alloc(void) THROWS(E_BADALLOC);

/* Clone the given VFS */
FUNDEF ATTR_RETNONNULL ATTR_MALLOC WUNUSED REF struct vfs *KCALL
vfs_clone(struct vfs *__restrict self) THROWS(E_BADALLOC);

#define CONFIG_FS_UMASK_DEFAULT   022 /* S_IWGRP|S_IWOTH */

typedef union {
	struct {
		WEAK u32    f_atmask; /* File system operations mode mask (Set of negated `FS_MODE_F*'). */
		WEAK u32    f_atflag; /* File system operations mode flags (Set of negated `FS_MODE_F*'). */
	};
	WEAK u64        f_mode;   /* File system operations mode. */
	WEAK atomic64_t f_atom;   /* File system operations mode. */
} fs_mask_t;


struct fs {
	WEAK refcnt_t        f_refcnt;               /* Reference counter. */
	size_t               f_heapsize;             /* Allocated heap size. */
	REF struct vfs      *f_vfs;                  /* [1..1][const] The underlying VFS.
	                                              * NOTE: This pointer also holds a reference to `->v_fscount' */
	struct atomic_rwlock f_pathlock;             /* Lock for accessing dynamic filesystem paths (cwd, root, drive-local CWDs) */
	REF struct path     *f_root;                 /* [1..1][lock(f_pathlock)] Root directory. */
	REF struct path     *f_cwd;                  /* [1..1][lock(f_pathlock)] Current working directory. */
	REF struct path     *f_dcwd[VFS_DRIVECOUNT]; /* [0..1][lock(f_pathlock)][*]  Per-drive  working directories.
	                                              * NOTE: When `NULL', `f_vfs->v_drives[INDEX]' is used instead. */
	WEAK mode_t          f_umask;                /* The currently effective UMASK.
	                                              * NOTE: All bits not masked by `0777' _MUST_ always be ZERO(0)! */
	WEAK u32             f_lnkmax;               /* The max number of symbolic links allowed during resolution of a path.
	                                              * This field defaults to `SYMLOOP_MAX'. */
	fs_mask_t            f_mode;                 /* Filesystem mode */
	/* TODO: Get rid of these 2. - Use uid/gid from cred instead! */
	uid_t                f_fsuid;                /* Filesystem user ID */
	gid_t                f_fsgid;                /* Filesystem group ID */
};

/* Destroy (and free) a given fs `self' */
FUNDEF NOBLOCK void NOTHROW(KCALL fs_destroy)(struct fs *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct fs, f_refcnt, fs_destroy)

/* Allocate a new FS object. */
FUNDEF ATTR_RETNONNULL ATTR_MALLOC WUNUSED
REF struct fs *KCALL fs_alloc(void) THROWS(E_BADALLOC);

/* Clone the given FS
 * @param: clone_vfs: When true, clone the VFS, else share the same one. */
FUNDEF ATTR_RETNONNULL ATTR_MALLOC WUNUSED REF struct fs *KCALL
fs_clone(struct fs *__restrict self, bool clone_vfs) THROWS(E_BADALLOC);

/* The kernel's own filesystem / the filesystem used when running `/bin/init'. */
DATDEF struct fs fs_kernel;
DATDEF struct vfs vfs_kernel;


struct handle;

/* Back-end implementation of `sys_open()' and friends.
 * WARNING: This function does _NOT_ validate `oflags', `mode' or `fsmode'!
 *          Invalid flags are silently ignored.
 * WARNING: This function does _NOT_ fill in `return.h_mode'
 * @param: oflags: Set of `O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK |
 *                         O_DIRECTORY | O_CREAT | O_EXCL | O_NOATIME |
 *                         O_PATH   |  O_TMPFILE  |  O_SYMLINK  |  O_*'
 * @param: fsmode: Set of `0 | FS_MODE_FDOSPATH | FS_MODE_FEMPTY_PATH |
 *                         FS_MODE_FSYMLINK_NOFOLLOW' */
FUNDEF WUNUSED NONNULL((1, 2, 3)) REF struct handle KCALL
fs_open_ex(struct fs *__restrict filesystem,
           struct path *cwd, struct path *root,
           USER CHECKED /*utf-8*/ char const *upath,
           oflag_t oflags, mode_t mode DFL(644),
           fsmode_t fsmode DFL(FS_MODE_FNORMAL));

/* A somplified wrapper for `fs_open_ex()'
 * WARNING: This function does _NOT_ validate `oflags' or `fsmode'!
 *          Invalid flags are silently ignored.
 * WARNING: This function does _NOT_ fill in `return.h_mode'
 * @param: oflags: Set of `O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK |
 *                         O_DIRECTORY | O_CREAT | O_EXCL | O_NOATIME |
 *                         O_PATH | O_TMPFILE | O_SYMLINK | O_DOSPATH |
 *                         O_NOFOLLOW | O_*' */
FUNDEF WUNUSED NONNULL((1)) REF struct handle KCALL
fs_open(struct fs *__restrict filesystem, unsigned int dirfd,
        USER CHECKED /*utf-8*/ char const *upath,
        oflag_t oflags, mode_t mode DFL(644));

#ifdef __cplusplus
extern "C++" {
#ifdef __INTELLISENSE__
LOCAL WUNUSED NONNULL((1)) REF struct handle KCALL
fs_open(struct fs *__restrict filesystem,
        USER CHECKED /*utf-8*/ char const *upath,
        oflag_t oflags, mode_t mode DFL(644));
LOCAL WUNUSED REF struct handle KCALL
fs_open(USER CHECKED /*utf-8*/ char const *upath,
        oflag_t oflags, mode_t mode DFL(644));
#else /* __INTELLISENSE__ */
LOCAL WUNUSED NONNULL((1)) REF struct handle KCALL
fs_open(struct fs *__restrict filesystem,
        USER CHECKED /*utf-8*/ char const *upath,
        oflag_t oflags, mode_t mode DFL(644)) {
	return fs_open(filesystem, HANDLE_SYMBOLIC_FDCWD,
	               upath, oflags, mode);
}

LOCAL WUNUSED REF struct handle KCALL
fs_open(USER CHECKED /*utf-8*/ char const *upath,
        oflag_t oflags, mode_t mode DFL(644)) {
	return fs_open(&fs_kernel, HANDLE_SYMBOLIC_FDCWD,
	               upath, oflags, mode);
}
#endif /* !__INTELLISENSE__ */
}
#endif /* __cplusplus */



/* [1..1][lock(read(THIS_TASK || INTERN(lock)), write(THIS_TASK && INTERN(lock)))]
 * Per-thread filesystem information.
 * NOTE: Initialized to NULL. - Must be initialized before the task is started. */
DATDEF ATTR_PERTASK REF struct fs *this_fs;
#define THIS_FS  PERTASK_GET(this_fs)
#define THIS_VFS (PERTASK_GET(this_fs)->f_vfs)

/* Return the filesystem controller of the given thread. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *
NOTHROW(FCALL task_getfs)(struct task *__restrict thread);

/* Exchange the filesystem controller of the calling thread. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *
NOTHROW(FCALL task_setfs)(struct fs *__restrict newfs);



#define fs_getuid(f) (f)->f_fsuid /* TODO: Remove this */
#define fs_getgid(f) (f)->f_fsgid /* TODO: Remove this */

LOCAL NOBLOCK WUNUSED fsmode_t
NOTHROW(KCALL fs_getmode_for)(struct fs *__restrict self, atflag_t flags) {
	fs_mask_t mode;
	mode.f_mode = atomic64_read(&self->f_mode.f_atom);
	return (flags & mode.f_atmask) | mode.f_atflag;
}

LOCAL NOBLOCK WUNUSED fsmode_t
NOTHROW(KCALL fs_getmode)(atflag_t flags) {
	return fs_getmode_for(THIS_FS, flags);
}


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_FS_VFS_H */
