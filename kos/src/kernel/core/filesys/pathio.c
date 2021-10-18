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
#ifndef GUARD_KERNEL_CORE_FILESYS_PATHIO_C
#define GUARD_KERNEL_CORE_FILESYS_PATHIO_C 1
#define __WANT_PATH__p_LOPS
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/io.h>
#include <kos/lockop.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC path_remove_from_recent_postlop)(Tobpostlockop(vfs) *__restrict self,
                                                   struct vfs *__restrict obj) {
	REF struct path *me;
	me = container_of(self, struct path, _p_vfsplop);
	decref(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(vfs) *
NOTHROW(LOCKOP_CC path_remove_from_recent_lop)(Toblockop(vfs) *__restrict self,
                                               struct vfs *__restrict obj) {
	REF struct path *me = container_of(self, struct path, _p_vfslop);
	COMPILER_READ_BARRIER();
	if likely(TAILQ_ISBOUND(me, p_recent)) {
		assert(obj->vf_recentcnt != 0);
		TAILQ_UNBIND(&obj->vf_recent, me, p_recent);
		--obj->vf_recentcnt;
		decref_nokill(me);
	}
	me->_p_vfsplop.oplo_func = &path_remove_from_recent_postlop;
	return &me->_p_vfsplop;
}

/* Remove `self' from the recent-cache of the associated VFS (possibly asynchronously)
 * This  function must be  called after doing `self->p_cldlist = PATH_CLDLIST_DELETED' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL path_remove_from_recent)(struct path *__restrict self) {
	COMPILER_READ_BARRIER();
	if (TAILQ_ISBOUND(self, p_recent)) {
		/* Lookup the proper VFS context. */
		struct vfs *pathvfs = _path_getvfs(self);
		if likely(tryincref(pathvfs)) {
			if (vfs_recentlock_tryacquire(pathvfs)) {
				COMPILER_READ_BARRIER();
				if (TAILQ_ISBOUND(self, p_recent)) {
					assert(pathvfs->vf_recentcnt != 0);
					TAILQ_UNBIND(&pathvfs->vf_recent, self, p_recent);
					--pathvfs->vf_recentcnt;
					decref_nokill(self);
				}
				vfs_recentlock_release(pathvfs);
			} else {
				/* Must use lock operations to do the removal! */
				incref(self); /* Inherited by `path_remove_from_recent_lop' */
				self->_p_vfslop.olo_func = &path_remove_from_recent_lop;
				oblockop_enqueue(&pathvfs->vf_recentlops, &self->_p_vfslop);
				_vfs_recentlock_reap(pathvfs);
			}
			decref_unlikely(pathvfs);
		}
	}
}


/* High-level implementation of `unlink(2)' / `rmdir(2)'.
 * @param: atflags: At least one of `AT_REMOVEREG | AT_REMOVEDIR', optionally
 *                  or'd with `AT_DOSPATH' (other flags are silently ignored)
 * @throw: E_WOULDBLOCK:                                Preemption is disabled, and operation would have blocked.
 * @throw: E_SEGFAULT:                                  Faulty pointer
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: `self' has already been deleted.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: `name' has already been deleted.
 * @throw: E_FSERROR_ACCESS_DENIED:                     Missing W/X permissions for `self'
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR: `name' is S_IFREG, but `AT_REMOVEREG' isn't given
 * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_UNLINK:  `name' is S_IFDIR, but `AT_REMOVEDIR' isn't given
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:               `name' refers to a mounting point
 * @throw: E_FSERROR_FILE_NOT_FOUND:                    `name' could not be found
 * @throw: E_FSERROR_READONLY:                          ...
 * @throw: E_IOERROR:                                   ...
 * @throw: E_BADALLOC:                                  ... */
PUBLIC NONNULL((1)) void KCALL
path_remove(struct path *__restrict self,
            USER CHECKED /*utf-8*/ char const *name, u16 namelen, atflag_t atflags,
            /*out[1..1]_opt*/ REF struct fnode **pdeleted_node,
            /*out[1..1]_opt*/ REF struct fdirent **pdeleted_dirent,
            /*out[0..1]_opt*/ REF struct path **pdeleted_path)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_DELETED, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_FILE_NOT_FOUND, E_FSERROR_READONLY,
		       E_IOERROR, E_BADALLOC, ...) {
	uintptr_t namehash;
	struct path *existing_path;
	REF struct fdirent *dent;
	REF struct fnode *node;

	/* Assert permissions */
	fnode_access(self->p_dir, W_OK | X_OK);

	namehash = fdirent_hash(name, namelen);
again_acquire_cldlock:
	path_cldlock_write(self);

	/* Check if `self' has been deleted. */
	if unlikely(self->p_cldlist == PATH_CLDLIST_DELETED) {
		path_cldlock_endwrite(self);
		THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);
	}

	TRY {
		/* Check if we're to remove a child path. */
		existing_path = path_lookupchild_withlock(self, name, namelen,
		                                          namehash, atflags);
	} EXCEPT {
		path_cldlock_endwrite(self);
		RETHROW();
	}
	if (existing_path) {
		assert(existing_path != self);
		if (!tryincref(existing_path)) {
			/* Existing path is being destroyed and is probably trying to remove
			 * itself right now, but  since we need it  gone _now_, just do  the
			 * removal for it! */
			path_cldlist_remove_force(self, existing_path);
		} else {
			struct path_bucket *old_buckets;

			/* Check if we're even allowed to remove directories. */
			if (!(atflags & AT_REMOVEDIR)) {
				path_cldlock_endwrite(self);
				decref_unlikely(existing_path);

				/* Welp... better use rmdir(2) next time... */
				THROW(E_FSERROR_IS_A_DIRECTORY, E_FILESYSTEM_IS_A_DIRECTORY_UNLINK);
			}

			/* Check if it's a mounting point. */
			if unlikely(path_ismount(existing_path)) {
				path_cldlock_endwrite(self);
				decref_unlikely(existing_path);

				/* You'll have to use `path_umount()' */
				THROW(E_FSERROR_IS_A_MOUNTING_POINT);
			}

			/* Ok: so this is where it gets a little bit complicated:
			 *  - We have to acquire another lock to the child path
			 *  - Then, while holding locks to both paths, invoke the
			 *    underlying fdirnode's unlink operator
			 *  - Once that operator returns with success, mark the
			 *    child  path's  `p_cldlist = PATH_CLDLIST_DELETED'
			 *  - Release locks and we're done
			 *
			 * All of the is-directory-empty checking is done on  the
			 * FS-layer, and we  can't safely assume  that the  child
			 * path's child-table being non-empty means that the real
			 * directory is also  non-empty: filesystems are  allowed
			 * to remove files and directories for reasons other than
			 * explicit unlink/rmdir calls.
			 * This is especially important for stuff like procfs! */
			if (path_cldlock_trywrite(existing_path)) {
				/* Wait for the existing path to become available. */
				path_cldlock_endwrite(self);
				FINALLY_DECREF_UNLIKELY(existing_path);
				path_cldlock_write(existing_path);
				path_cldlock_endwrite(existing_path);
				goto again_acquire_cldlock;
			}

			/* Do the fs-level unlink (or rather: rmdir) */
			TRY {
				fdirnode_unlink(self->p_dir,
				                existing_path->p_name,
				                existing_path->p_dir);
			} EXCEPT {
				path_cldlock_endwrite(existing_path);
				path_cldlock_endwrite(self);
				RETHROW();
			}

			/* Remove the deleted `existing_path' from `self' */
			path_cldlist_remove_force(self, existing_path);
			path_cldlist_rehash_after_remove(self);
			path_cldlock_endwrite(self);

			/* Mark `existing_path' as having been deleted. */
			old_buckets = existing_path->p_cldlist;
			existing_path->p_cldlist = PATH_CLDLIST_DELETED;
			DBG_memset(&existing_path->p_cldused, 0xcc, sizeof(existing_path->p_cldused));
			DBG_memset(&existing_path->p_cldsize, 0xcc, sizeof(existing_path->p_cldsize));
			DBG_memset(&existing_path->p_cldmask, 0xcc, sizeof(existing_path->p_cldmask));
			path_cldlock_endwrite(existing_path);
			if (old_buckets != PATH_CLDLIST_DELETED &&
			    old_buckets != path_empty_cldlist)
				kfree(old_buckets);

			/* Remove `existing_path' from the recent-cache of the VFS. (Possibly through use of a LOP) */
			path_remove_from_recent(existing_path);

			/* Write-back information about what got deleted (if requested) */
			if (pdeleted_node)
				*pdeleted_node = mfile_asnode(incref(existing_path->p_dir));
			if (pdeleted_dirent)
				*pdeleted_dirent = incref(existing_path->p_name);
			if (pdeleted_path)
				*pdeleted_path = existing_path;
			else {
				decref(existing_path);
			}
			return;
		}
	}
	path_cldlock_endwrite(self);

	/* Consult the filesystem about what the caller wants to delete. */
	{
		struct flookup_info info;
		info.flu_name    = name;
		info.flu_hash    = namehash;
		info.flu_namelen = namelen;
		info.flu_flags   = atflags;

		/* Do the lookup */
		dent = fdirnode_lookup(self->p_dir, &info);
	}

	/* Whatever you're trying to delete, it's doesn't exist... */
	if unlikely(!dent)
		THROW(E_FSERROR_FILE_NOT_FOUND);

	/* Load the file-node associated with `node' */
	TRY {
		node = fdirent_opennode(dent, self->p_dir);
		if unlikely(!node)
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		TRY {
			/* Check if we're even allowed  to delete `node', and in  the
			 * case of `node' being  a directory, re-acquire a  read-lock
			 * to `self' to ensure that it hasn't appeared in-cache since
			 * we checked earlier,  and won't appear  until FS says  that
			 * it's  done deleting the file (at which point we can assume
			 * that later fdirnode_lookup() calls will no longer indicate
			 * that the file still exists) */
			if (fnode_isdir(node)) {
				if (!(atflags & AT_REMOVEDIR))
					THROW(E_FSERROR_IS_A_DIRECTORY, E_FILESYSTEM_IS_A_DIRECTORY_UNLINK);
				path_cldlock_read(self);

				/* double-check that nothing with this name exists in-cache. */
				if unlikely(path_lookupchild_withlock(self, name, namelen, namehash, 0) != NULL) {
					path_cldlock_endread(self);
					decref_unlikely(node);
					decref_unlikely(dent);
					goto again_acquire_cldlock; /* Let's try again... */
				}

				/* Ask the filesystem to remove the directory. */
				TRY {
					fdirnode_unlink(self->p_dir, dent, node);
				} EXCEPT {
					path_cldlock_endread(self);
					RETHROW();
				}
				path_cldlock_endread(self);
			} else {
				/* Remove something that isn't a directory. */
				fdirnode_unlink(self->p_dir, dent, node);
			}
		} EXCEPT {
			decref_unlikely(node);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(dent);
		RETHROW();
	}

	/* Write-back information about what got deleted (if requested) */
	if (pdeleted_node)
		*pdeleted_node = node;
	else {
		decref_unlikely(node);
	}
	if (pdeleted_dirent)
		*pdeleted_dirent = dent;
	else {
		decref_unlikely(dent);
	}
	if (pdeleted_path)
		*pdeleted_path = NULL; /* Wasn't a path that got removed... */
}








/* High-level  implementation of the `rename(2)' system call.
 * This function also handles the case where `newname' refers
 * to a pre-existing  directory, in which  case `oldname'  is
 * moved into said directory, though will keep its name after
 * the process has completed.
 * @param: atflags: Set of `0 | AT_DOSPATH' (other flags are silently ignored)
 * @throw: E_WOULDBLOCK:                                Preemption is disabled, and operation would have blocked.
 * @throw: E_SEGFAULT:                                  Faulty pointer
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: Either `oldpath' or `newpath' have already been deleted.
 * @throw: E_FSERROR_ACCESS_DENIED:                     Missing write permissions for old/new directory
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:               `oldname' refers to a mounting point
 * @throw: E_FSERROR_FILE_NOT_FOUND:                    `oldname' could not be found
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:                 Paths point to different filesystems
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS:               `newname'  already exists and isn't directory, or is
 *                                                      is a directory and already contains a file `oldname'
 * @throw: E_FSERROR_ILLEGAL_PATH:                      `newnamelen == 0'
 * @throw: E_FSERROR_ILLEGAL_PATH:                      newname isn't a valid filename for the target filesystem
 * @throw: E_FSERROR_DIRECTORY_MOVE_TO_CHILD:           The move would make a directory become a child of itself
 * @throw: E_FSERROR_DISK_FULL:                         ...
 * @throw: E_FSERROR_READONLY:                          ...
 * @throw: E_IOERROR:                                   ...
 * @throw: E_BADALLOC:                                  ... */
PUBLIC NONNULL((1, 4)) void KCALL
path_rename(struct path *__restrict oldpath, USER CHECKED /*utf-8*/ char const *oldname, u16 oldnamelen,
            struct path *__restrict newpath, USER CHECKED /*utf-8*/ char const *newname, u16 newnamelen,
            atflag_t atflags,
            /*out[1..1]_opt*/ REF struct fnode **prenamed_node,
            /*out[1..1]_opt*/ REF struct fdirent **pold_dirent,
            /*out[1..1]_opt*/ REF struct fdirent **pnew_dirent,
            /*out[0..1]_opt*/ REF struct path **pdeleted_path)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_DELETED, E_FSERROR_ACCESS_DENIED, E_FSERROR_IS_A_MOUNTING_POINT,
		       E_FSERROR_FILE_NOT_FOUND, E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_DIRECTORY_MOVE_TO_CHILD, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_IOERROR, E_BADALLOC, ...) {
	/* TODO */
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_PATHIO_C */
