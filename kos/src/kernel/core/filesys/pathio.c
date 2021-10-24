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
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <sched/task.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/io.h>
#include <kos/lockop.h>

#include <assert.h>
#include <fcntl.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */



/* Check if the given flag is a user-space AT_* flag */
#define IS_USER_ATFLAG(x)          \
	((x) == AT_SYMLINK_NOFOLLOW || \
	 (x) == AT_NO_AUTOMOUNT ||     \
	 (x) == AT_EMPTY_PATH ||       \
	 (x) == AT_DOSPATH ||          \
	 (x) == AT_REMOVEREG ||        \
	 (x) == AT_REMOVEDIR ||        \
	 (x) == AT_EACCESS ||          \
	 (x) == AT_SYMLINK_FOLLOW ||   \
	 (x) == AT_SYMLINK_REGULAR ||  \
	 (x) == AT_CHANGE_CTIME ||     \
	 (x) == AT_READLINK_REQSIZE || \
	 (x) == AT_ALTPATH)

/* Assert that custom AT_* codes don't overlap with standard ones, and aren't equal to each other. */
STATIC_ASSERT(!IS_USER_ATFLAG(AT_RENAME_NOREPLACE));
STATIC_ASSERT(!IS_USER_ATFLAG(AT_RENAME_EXCHANGE));
STATIC_ASSERT(!IS_USER_ATFLAG(AT_RENAME_MOVETODIR));
STATIC_ASSERT(!IS_USER_ATFLAG(__RENAME_WHITEOUT));
STATIC_ASSERT(!IS_USER_ATFLAG(AT_IGNORE_TRAILING_SLASHES));
STATIC_ASSERT(!IS_USER_ATFLAG(AT_PATHPRINT_INCTRAIL));
STATIC_ASSERT(!IS_USER_ATFLAG(_AT_PATHPRINT_REACHABLE));
STATIC_ASSERT(AT_RENAME_NOREPLACE != AT_RENAME_EXCHANGE);
STATIC_ASSERT(AT_RENAME_NOREPLACE != AT_RENAME_MOVETODIR);
STATIC_ASSERT(AT_RENAME_NOREPLACE != __RENAME_WHITEOUT);
STATIC_ASSERT(AT_RENAME_NOREPLACE != AT_IGNORE_TRAILING_SLASHES);
STATIC_ASSERT(AT_RENAME_NOREPLACE != AT_PATHPRINT_INCTRAIL);
STATIC_ASSERT(AT_RENAME_NOREPLACE != _AT_PATHPRINT_REACHABLE);
STATIC_ASSERT(AT_RENAME_EXCHANGE != AT_RENAME_MOVETODIR);
STATIC_ASSERT(AT_RENAME_EXCHANGE != __RENAME_WHITEOUT);
STATIC_ASSERT(AT_RENAME_EXCHANGE != AT_IGNORE_TRAILING_SLASHES);
STATIC_ASSERT(AT_RENAME_EXCHANGE != AT_PATHPRINT_INCTRAIL);
STATIC_ASSERT(AT_RENAME_EXCHANGE != _AT_PATHPRINT_REACHABLE);
STATIC_ASSERT(AT_RENAME_MOVETODIR != __RENAME_WHITEOUT);
STATIC_ASSERT(AT_RENAME_MOVETODIR != AT_IGNORE_TRAILING_SLASHES);
STATIC_ASSERT(AT_RENAME_MOVETODIR != AT_PATHPRINT_INCTRAIL);
STATIC_ASSERT(AT_RENAME_MOVETODIR != _AT_PATHPRINT_REACHABLE);
STATIC_ASSERT(__RENAME_WHITEOUT != AT_IGNORE_TRAILING_SLASHES);
STATIC_ASSERT(__RENAME_WHITEOUT != AT_PATHPRINT_INCTRAIL);
STATIC_ASSERT(__RENAME_WHITEOUT != _AT_PATHPRINT_REACHABLE);
STATIC_ASSERT(AT_IGNORE_TRAILING_SLASHES != AT_PATHPRINT_INCTRAIL);
STATIC_ASSERT(AT_IGNORE_TRAILING_SLASHES != _AT_PATHPRINT_REACHABLE);
STATIC_ASSERT(AT_PATHPRINT_INCTRAIL != _AT_PATHPRINT_REACHABLE);
#undef IS_USER_ATFLAG




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

/* Mark `self' as deleted before unlocking it and asynchronously removing it from the recent-cache. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL path_delete_and_unlock)(struct path *__restrict self) {
	struct path_bucket *old_buckets;

	/* Mark `self' as having been deleted. */
	old_buckets = self->p_cldlist;
	self->p_cldlist = PATH_CLDLIST_DELETED;
	DBG_memset(&self->p_cldused, 0xcc, sizeof(self->p_cldused));
	DBG_memset(&self->p_cldsize, 0xcc, sizeof(self->p_cldsize));
	DBG_memset(&self->p_cldmask, 0xcc, sizeof(self->p_cldmask));
	path_cldlock_endwrite(self);
	if (old_buckets != PATH_CLDLIST_DELETED &&
		old_buckets != path_empty_cldlist)
		kfree(old_buckets);

	/* Remove `self' from the recent-cache of the VFS. (Possibly through use of a LOP) */
	path_remove_from_recent(self);
}



INTDEF struct path deleted_path; /* from "./path.c" */

/* Release a lock as previously acquired by `path_tryincref_and_trylock_whole_tree()'. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL path_decref_and_unlock_whole_tree)(REF struct path *__restrict self) {
	size_t mask;
	struct path_bucket *buckets;
	mask    = self->p_cldmask;
	buckets = self->p_cldlist;
	if (buckets != PATH_CLDLIST_DELETED) {
		size_t i;
		for (i = 0; i <= mask; ++i) {
			struct path *child = buckets[i].pb_path;
			if (child && child != &deleted_path && !wasdestroyed(child)) {
				path_decref_and_unlock_whole_tree(child);
				decref_unlikely(self);
			}
		}
	}
	path_cldlock_endwrite(self);
}

/* Acquire a lock to `self' and all child-paths reachable from there.
 * @return: * : Reference to path that was blocking. */
PRIVATE WUNUSED NONNULL((1)) REF struct path *
NOTHROW(FCALL path_tryincref_and_trylock_whole_tree)(struct path *__restrict self) {
	size_t i, mask;
	struct path_bucket *buckets;
	if (!path_cldlock_trywrite(self))
		return incref(self);
	mask    = self->p_cldmask;
	buckets = self->p_cldlist;
	if (buckets != PATH_CLDLIST_DELETED) {
		size_t i;
		for (i = 0; i <= mask; ++i) {
			REF struct path *result;
			struct path *child = buckets[i].pb_path;
			if (!child)
				continue;
			if (child == &deleted_path)
				continue;
			if (!tryincref(child))
				continue;
			/* Recursion... */
			result = path_tryincref_and_trylock_whole_tree(child);
			if unlikely(result) {
				/* Release locks already acquired */
				while (i--) {
					child = buckets[i].pb_path;
					if (!child || child == &deleted_path)
						continue;
					if (!wasdestroyed(child))
						path_decref_and_unlock_whole_tree(child);
				}
				path_cldlock_endwrite(self);
				return result;
			}
		}
	}
	return NULL;
}

/* Release a lock as previously acquired by `path_tryincref_and_trylock_whole_tree()'. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL path_decref_and_delete_and_unlock_whole_tree)(struct path *__restrict self) {
	size_t old_mask;
	struct path_bucket *old_buckets;

	/* Mark `self' as having been deleted. */
	old_mask        = self->p_cldmask;
	old_buckets     = self->p_cldlist;
	self->p_cldlist = PATH_CLDLIST_DELETED;

	/* Remove children that have already been destroyed. */
	if (old_buckets != PATH_CLDLIST_DELETED &&
	    old_buckets != path_empty_cldlist) {
		size_t i;
		for (i = 0; i <= old_mask; ++i) {
			struct path *child = old_buckets[i].pb_path;
			if (child && wasdestroyed(child))
				old_buckets[i].pb_path = NULL;
		}
		kfree(old_buckets);
	}
	DBG_memset(&self->p_cldused, 0xcc, sizeof(self->p_cldused));
	DBG_memset(&self->p_cldsize, 0xcc, sizeof(self->p_cldsize));
	DBG_memset(&self->p_cldmask, 0xcc, sizeof(self->p_cldmask));
	path_cldlock_endwrite(self);
	/* Remove `self' from the recent-cache of the VFS. (Possibly through use of a LOP) */
	path_remove_from_recent(self);
	decref(self);

	if (old_buckets != PATH_CLDLIST_DELETED &&
	    old_buckets != path_empty_cldlist) {
		/* Recursively mark child paths as deleted (and also unlock them) */
		size_t i;
		for (i = 0; i <= old_mask; ++i) {
			struct path *child = old_buckets[i].pb_path;
			if (!child || child == &deleted_path)
				continue;
			path_decref_and_delete_and_unlock_whole_tree(child);
		}
		kfree(old_buckets);
	}
}







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
PUBLIC NONNULL((1)) void KCALL
path_remove(struct path *__restrict self,
            /*utf-8*/ USER CHECKED char const *name, u16 namelen, atflag_t atflags,
            /*out[1..1]_opt*/ REF struct fnode **pdeleted_node,
            /*out[1..1]_opt*/ REF struct fdirent **pdeleted_dirent,
            /*out[0..1]_opt*/ REF struct path **pdeleted_path)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_READONLY, E_IOERROR, E_BADALLOC, ...) {
	unsigned int status;
	uintptr_t namehash;
	struct path *existing_path;
	REF struct fdirent *dent;
	REF struct fnode *node;

	/* Assert permissions */
	fnode_access(self->p_dir, W_OK | X_OK);

	namehash = fdirent_hash(name, namelen);
again_acquire_cldlock:
	path_cldlock_write(self);
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
			REF struct path *blocking_path;

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

			/* Acquire locks to this entire path-tree. */
			blocking_path = path_tryincref_and_trylock_whole_tree(existing_path);
			if unlikely(blocking_path) {
				/* Wait for the existing path to become available. */
				path_cldlock_endwrite(self);
				decref_unlikely(existing_path);
				FINALLY_DECREF_UNLIKELY(blocking_path);
				path_cldlock_write(blocking_path);
				path_cldlock_endwrite(blocking_path);
				goto again_acquire_cldlock;
			}

			/* Do the fs-level unlink (or rather: rmdir) */
			TRY {
				status = fdirnode_unlink(self->p_dir,
				                         existing_path->p_name,
				                         existing_path->p_dir);
			} EXCEPT {
				path_decref_and_unlock_whole_tree(existing_path);
				decref_unlikely(existing_path);
				path_cldlock_endwrite(self);
				RETHROW();
			}
			assert(status == FDIRNODE_UNLINK_SUCCESS ||
			       status == FDIRNODE_UNLINK_DELETED);
			if (status == FDIRNODE_UNLINK_DELETED) {
				path_decref_and_unlock_whole_tree(existing_path);
				decref_unlikely(existing_path);
				path_cldlock_endwrite(self);
				goto again_acquire_cldlock;
			}

			/* Remove the deleted `existing_path' from `self' */
			path_cldlist_remove_force(self, existing_path);
			path_cldlist_rehash_after_remove(self);
			path_cldlock_endwrite(self);

			/* Mark `existing_path' (and its entire sub-tree) as having been deleted. */
			if (pdeleted_dirent)
				*pdeleted_dirent = incref(existing_path->p_name);
			path_decref_and_delete_and_unlock_whole_tree(existing_path);

			/* Write-back information about what got deleted (if requested) */
			if (pdeleted_node)
				*pdeleted_node = mfile_asnode(incref(existing_path->p_dir));
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
again_lookup_dent:
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
		if unlikely(!node) {
			decref_unlikely(dent);
			goto again_lookup_dent;
		}
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
					status = fdirnode_unlink(self->p_dir, dent, node);
				} EXCEPT {
					path_cldlock_endread(self);
					RETHROW();
				}
				path_cldlock_endread(self);
			} else {
				if (!(atflags & AT_REMOVEREG))
					THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR);

				/* Remove something that isn't a directory. */
				status = fdirnode_unlink(self->p_dir, dent, node);
			}
		} EXCEPT {
			decref_unlikely(node);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(dent);
		RETHROW();
	}
	assert(status == FDIRNODE_UNLINK_SUCCESS ||
	       status == FDIRNODE_UNLINK_DELETED);
	if (status == FDIRNODE_UNLINK_DELETED) {
		decref_unlikely(node);
		decref_unlikely(dent);
		goto again_lookup_dent;
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






/* Acquire locks for 2 paths */
PRIVATE NONNULL((1, 2)) void KCALL
twopaths_acquire_locks(struct path *a, struct path *b)
		THROWS(E_WOULDBLOCK) {
again:
	path_cldlock_write(a);
	if (b != a) {
		if (!path_cldlock_trywrite(b)) {
			path_cldlock_endwrite(a);
			path_cldlock_write(b);
			if (!path_cldlock_trywrite(a)) {
				path_cldlock_endwrite(b);
				goto again;
			}
		}
	}
}

/* Release locks from 2 paths */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL twopaths_release_locks)(struct path *a, struct path *b) {
	if (b != a)
		path_cldlock_endwrite(b);
	path_cldlock_endwrite(a);
}




/* Special return values for `fdirnode_rename_in_path()' */
#define FDIRNODE_RENAME_IN_PATH_SUCCESS ((REF struct path *)FDIRNODE_RENAME_SUCCESS)
#define FDIRNODE_RENAME_IN_PATH_EXISTS  ((REF struct path *)FDIRNODE_RENAME_EXISTS)
#define FDIRNODE_RENAME_IN_PATH_DELETED ((REF struct path *)FDIRNODE_RENAME_DELETED)
STATIC_ASSERT(!ADDR_ISKERN(FDIRNODE_RENAME_IN_PATH_SUCCESS));
STATIC_ASSERT(!ADDR_ISKERN(FDIRNODE_RENAME_IN_PATH_EXISTS));
STATIC_ASSERT(!ADDR_ISKERN(FDIRNODE_RENAME_IN_PATH_DELETED));

PRIVATE WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
fdirnode_exchange_paths(struct path *oldpath, struct path *newpath,
                        struct frename_info *__restrict info)
		THROWS(...) {
	REF struct path *status;
	REF struct path *oldpath_subpath_with_oldname = NULL;
	REF struct path *newpath_subpath_with_newname = NULL;
	TRY {
		uintptr_t oldnamehash, newnamehash;
		char const *oldname, *newname;
		u16 oldnamelen, newnamelen;
		REF struct path *blocking_path;

		/* Load old/new name variables. */
		oldnamehash = info->frn_oldent->fd_hash;
		oldname     = info->frn_oldent->fd_name;
		oldnamelen  = info->frn_oldent->fd_namelen;
		newnamehash = info->frn_hash;
		newname     = info->frn_name;
		newnamelen  = info->frn_namelen;

		/* Lookup paths. */
		oldpath_subpath_with_oldname = path_lookupchildref_withlock(oldpath, oldname, oldnamelen, oldnamehash, info->frn_flags);
		newpath_subpath_with_newname = path_lookupchildref_withlock(newpath, newname, newnamelen, newnamehash, info->frn_flags);

		/* Check for special case: rename to unchanged name within same directory. */
		if unlikely(oldpath == newpath && oldpath_subpath_with_oldname &&
		            oldpath_subpath_with_oldname == newpath_subpath_with_newname) {
			decref_unlikely(oldpath_subpath_with_oldname);
			decref_unlikely(newpath_subpath_with_newname);
			return FDIRNODE_RENAME_IN_PATH_SUCCESS;
		}

		/* Integrity checks: none of these paths should be identical. */
		assert(oldpath_subpath_with_oldname != newpath_subpath_with_newname ||
		       (!oldpath_subpath_with_oldname && !newpath_subpath_with_newname));

		/* If path caches exist for the 2 files being exchanged, then
		 * must make sure to allocate enough memory within the  resp.
		 * target paths where they'll be moved to. */
		if (oldpath != newpath) {
			if (oldpath_subpath_with_oldname)
				path_cldlist_rehash_before_insert(newpath); /* Must move sub-path `oldpath_subpath_with_oldname' from `oldpath' to `newpath' */
			if (newpath_subpath_with_newname)
				path_cldlist_rehash_before_insert(oldpath); /* Must move sub-path `newpath_subpath_with_newname' from `newpath' to `oldpath' */
		}
		/* Invoke the FS-level rename operation */
		status = (REF struct path *)fdirnode_rename(newpath->p_dir, info);
	} EXCEPT {
		if (oldpath_subpath_with_oldname)
			path_cldlist_rehash_after_remove(newpath);
		if (newpath_subpath_with_newname)
			path_cldlist_rehash_after_remove(oldpath);
		xdecref_unlikely(oldpath_subpath_with_oldname);
		xdecref_unlikely(newpath_subpath_with_newname);
		RETHROW();
	}

	/* Must perform previously prepared path transformations on success. */
	if (status == FDIRNODE_RENAME_IN_PATH_SUCCESS) {
		/* Deltas for child paths added/removed in terms of available space. */
		int oldpath_child_delta = 0;
		int newpath_child_delta = 0;
		if (oldpath != newpath) {
			if (oldpath_subpath_with_oldname)
				++newpath_child_delta;
			if (newpath_subpath_with_newname)
				++oldpath_child_delta;
		}

		/* Start by removing paths. This must  be done before we can  proceed
		 * to add paths since the paths that get removed here may share names
		 * with those we'll be adding below.  Also: these are the same  paths
		 * as those we're re-adding below. */
		if (oldpath_subpath_with_oldname) {
			path_cldlist_remove_force(oldpath, oldpath_subpath_with_oldname);
			++oldpath_child_delta;
		}
		if (newpath_subpath_with_newname) {
			path_cldlist_remove_force(newpath, newpath_subpath_with_newname);
			++newpath_child_delta;
		}

		/* (Re-)add paths to the proper parents, and update their parent pointers. */
		if (oldpath_subpath_with_oldname) {
			REF struct fdirent *oldname;
			/* Assign new name to the path. */
			oldname = oldpath_subpath_with_oldname->p_name; /* Inherit reference. */
			oldpath_subpath_with_oldname->p_name = incref(info->frn_dent);
			path_cldlist_insert(newpath, oldpath_subpath_with_oldname);
			decref_unlikely(oldname);
			--newpath_child_delta;
			path_plock_acquire(oldpath_subpath_with_oldname);
			assert(oldpath_subpath_with_oldname->p_parent == oldpath);
			oldpath_subpath_with_oldname->p_parent = incref(newpath);
			path_plock_release(oldpath_subpath_with_oldname);
			decref_nokill(oldpath);
		}
		if (newpath_subpath_with_newname) {
			REF struct fdirent *oldname;
			/* Assign new name to the path. */
			oldname = newpath_subpath_with_newname->p_name; /* Inherit reference. */
			newpath_subpath_with_newname->p_name = incref(info->frn_oldent);
			path_cldlist_insert(oldpath, newpath_subpath_with_newname);
			decref_unlikely(oldname);
			--oldpath_child_delta;
			path_plock_acquire(newpath_subpath_with_newname);
			assert(newpath_subpath_with_newname->p_parent == newpath);
			newpath_subpath_with_newname->p_parent = incref(oldpath);
			path_plock_release(newpath_subpath_with_newname);
			decref_nokill(newpath);
		}
		assert(newpath_child_delta >= 0);
		assert(oldpath_child_delta >= 0);

		/* Truncate child lists if not all slots ended up being used. */
		if (newpath_child_delta > 0)
			path_cldlist_rehash_after_remove(newpath);
		if (oldpath_child_delta > 0)
			path_cldlist_rehash_after_remove(oldpath);
	} else {
		if (oldpath_subpath_with_oldname)
			path_cldlist_rehash_after_remove(newpath);
		if (newpath_subpath_with_newname)
			path_cldlist_rehash_after_remove(oldpath);
	}
	xdecref_unlikely(oldpath_subpath_with_oldname);
	xdecref_unlikely(newpath_subpath_with_newname);
	return status;
}



PRIVATE WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
fdirnode_replace_paths(struct path *oldpath, struct path *newpath,
                       struct frename_info *__restrict info)
		THROWS(...) {
	REF struct path *status;
	REF struct path *move_path = NULL; /* [0..1] Path that is being moved */
	REF struct path *ovrd_path = NULL; /* [0..1] Path that gets overwritten. */
	TRY {
		uintptr_t oldnamehash, newnamehash;
		char const *oldname, *newname;
		u16 oldnamelen, newnamelen;

		/* Load old/new name variables. */
		oldnamehash = info->frn_oldent->fd_hash;
		oldname     = info->frn_oldent->fd_name;
		oldnamelen  = info->frn_oldent->fd_namelen;
		newnamehash = info->frn_hash;
		newname     = info->frn_name;
		newnamelen  = info->frn_namelen;

		/* Look through the path cache for the paths being renamed. */
		if (fnode_isdir(info->frn_file))
			move_path = path_lookupchildref_withlock(oldpath, oldname, oldnamelen, oldnamehash, info->frn_flags);
		ovrd_path = path_lookupchildref_withlock(newpath, newname, newnamelen, newnamehash, info->frn_flags);
		if unlikely(ovrd_path && ovrd_path == move_path) {
			/* Special case: nothing is actually being renamed. */
			decref_unlikely(move_path);
			decref_unlikely(ovrd_path);
			return FDIRNODE_RENAME_IN_PATH_SUCCESS;
		}

		/* If there's a path that'll get overwritten, then we must lock its entire tree beforehand. */
		if (ovrd_path) {
			REF struct path *blocking_path;
			blocking_path = path_tryincref_and_trylock_whole_tree(ovrd_path);
			if unlikely(blocking_path != NULL) {
/*waitfor_blocking_path:*/
				xdecref_unlikely(move_path);
				xdecref_unlikely(ovrd_path);
				return blocking_path;
			}
		} else {
			/* If no path gets overwritten, then we must prepare `newpath' for the addition of another child. */
			if (move_path)
				path_cldlist_rehash_before_insert(newpath);
		}

		TRY {
			/* Invoke the FS-level rename operation */
			status = (REF struct path *)fdirnode_rename(newpath->p_dir, info);
		} EXCEPT {
			if (ovrd_path) {
				path_decref_and_unlock_whole_tree(ovrd_path);
			} else if (move_path) {
				path_cldlist_rehash_after_remove(newpath);
			}
			RETHROW();
		}
	} EXCEPT {
		xdecref_unlikely(move_path);
		xdecref_unlikely(ovrd_path);
		RETHROW();
	}
	if (status == FDIRNODE_RENAME_IN_PATH_SUCCESS) {
		/* Perform the path transformation that were prepared above. */
		if (ovrd_path) {
			path_cldlist_remove_force(newpath, ovrd_path);           /* Remove path that gets overwritten */
			path_decref_and_delete_and_unlock_whole_tree(ovrd_path); /* Mark overwritten tree as deleted. */
			if (!move_path)
				path_cldlist_rehash_after_remove(newpath);
		}
		if (move_path) {
			REF struct fdirent *oldname;
			/* Move the renamed path to its new home. */
			path_cldlist_remove_force(oldpath, move_path);

			/* Assign new name to the path. */
			oldname = move_path->p_name; /* Inherit reference. */
			move_path->p_name = incref(info->frn_dent);
			path_cldlist_insert(newpath, move_path);
			decref_unlikely(oldname);

			/* Rehash the old path following the removing of the moved path. */
			path_cldlist_rehash_after_remove(oldpath);
		}
	} else {
		if (ovrd_path) {
			path_decref_and_unlock_whole_tree(ovrd_path);
		} else if (move_path) {
			path_cldlist_rehash_after_remove(newpath);
		}
	}
	xdecref_unlikely(move_path);
	xdecref_unlikely(ovrd_path);
	return status;
}



/* Find the mounting point of `subpath' and acquire _PATH_F_PLOCK for all paths
 * leading up to  the mounting  point (including `subpath',  but excluding  the
 * mounting point itself).
 * #ifndef CONFIG_NO_SMP
 * If any of the locks couldn't be acquired immediately, return `NULL'
 * #endif
 * If `movedir' is encounted, return `FINDMOUNT_AND_PLOCK_TREE_NOPR_MOVE2CHILD' */
#define FINDMOUNT_AND_PLOCK_TREE_NOPR_MOVE2CHILD ((struct path *)-1)
PRIVATE NOPREEMPT NOBLOCK WUNUSED NONNULL((1)) struct path *
NOTHROW(FCALL findmount_and_plock_tree_nopr)(struct path *__restrict subpath,
                                             struct fdirnode *__restrict movedir) {
	struct path *result;
	if (subpath->p_dir == movedir)
		return FINDMOUNT_AND_PLOCK_TREE_NOPR_MOVE2CHILD;
	if (path_ismount(subpath))
		return subpath;
	if (!path_plock_tryacquire_nopr(subpath))
		return NULL;
	result = findmount_and_plock_tree_nopr(subpath->p_parent, movedir);
#ifndef CONFIG_NO_SMP
	if (result == NULL || result == FINDMOUNT_AND_PLOCK_TREE_NOPR_MOVE2CHILD)
		path_plock_release_nopr(subpath);
#endif /* !CONFIG_NO_SMP */
	return result;
}

#ifndef CONFIG_NO_SMP
PRIVATE NOPREEMPT NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL findmount_and_punlock_tree_nopr)(struct path *__restrict subpath) {
	if (path_ismount(subpath))
		return;
	findmount_and_punlock_tree_nopr(subpath->p_parent);
	path_plock_release_nopr(subpath);
}
#else /* !CONFIG_NO_SMP */
#define findmount_and_punlock_tree_nopr(subpath) (void)0
#endif /* CONFIG_NO_SMP */

#define IS_PART_OF_DIFFERENT_MOUNT_NOPR_NO    0 /* No: it's the same tree */
#define IS_PART_OF_DIFFERENT_MOUNT_NOPR_YES   1 /* Yes: it's the different tree */
#ifndef CONFIG_NO_SMP
#define IS_PART_OF_DIFFERENT_MOUNT_NOPR_RETRY 2 /* SMP lock was blocking; yield and try again */
#endif /* !CONFIG_NO_SMP */
PRIVATE NOPREEMPT NOBLOCK WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW(FCALL is_part_of_different_mount_nopr)(struct path *oldpath,
                                               struct path *newpath,
                                               struct path *mount) {
	unsigned int result;
	if (oldpath == mount)
		return IS_PART_OF_DIFFERENT_MOUNT_NOPR_NO; /* Same mount tree. */
	if (path_ismount(oldpath)) {
		/* Reached another mounting point before `mount' -> Different mount-tree! */
		return IS_PART_OF_DIFFERENT_MOUNT_NOPR_YES;
	}
#ifndef CONFIG_NO_SMP
	if (!path_plock_tryacquire_nopr(oldpath)) {
		/* There are 2 reasons why `oldpath' can't be locked:
		 *  #1: Because it's  already locked  as the  result of  being  one
		 *      of the directories between `newpath' and `mount' (including
		 *      `newpath',  but excluding `mount'  since the later wouldn't
		 *      be blocking, and has already  been checked above). In  this
		 *      case  we must tell  our caller that yes:  the 2 given paths
		 *      are part of the same  mounting tree, and we're not  dealing
		 *      with a move-to-child scenario.
		 *      >> IS_PART_OF_DIFFERENT_MOUNT_NOPR_NO
		 *  #2: Another CPU is holding the SMP lock. This is the case  when
		 *      we don't find `oldpath' within the already-locked tree, and
		 *      this case must be handled by releasing all of our SMP locks
		 *      and  telling our caller  to wait for  whatever other CPU is
		 *      currently holding this blocking lock.
		 *      >> IS_PART_OF_DIFFERENT_MOUNT_NOPR_RETRY */
		struct path *iter;
		for (iter = newpath; iter != mount; iter = iter->p_parent) {
			/* The 2 parent chains re-join before the mounting point, and
			 * the reason why we couldn't get the lock if because it  was
			 * already acquired in `findmount_and_plock_tree_nopr()' */
			if (oldpath == iter)
				return IS_PART_OF_DIFFERENT_MOUNT_NOPR_NO;
		}
		return IS_PART_OF_DIFFERENT_MOUNT_NOPR_RETRY;
	}
#endif /* !CONFIG_NO_SMP */
	result = is_part_of_different_mount_nopr(oldpath->p_parent, newpath, mount);
	path_plock_release_nopr(oldpath);
	return result;
}

PRIVATE NOBLOCK WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL check_move_to_child)(struct path *__restrict oldpath,
                                   struct path *__restrict newpath,
                                   struct fdirnode *__restrict movedir) {
	pflag_t was;
	struct path *mount;
	unsigned int result;
#ifndef CONFIG_NO_SMP
again:
#endif /* !CONFIG_NO_SMP */
	was   = PREEMPTION_PUSHOFF();
	mount = findmount_and_plock_tree_nopr(newpath, movedir);
	if (mount == FINDMOUNT_AND_PLOCK_TREE_NOPR_MOVE2CHILD) {
		/* Yes: this is a move-to-child scenario. */
		PREEMPTION_POP(was);
		return true;
	}
#ifndef CONFIG_NO_SMP
	if (!mount) {
		PREEMPTION_POP(was);
		task_tryyield_or_pause();
		goto again;
	}
#endif /* !CONFIG_NO_SMP */

	/* With the mounting point root deduced, also check that
	 * `oldpath' is part of the same mount tree.  Otherwise,
	 * we have no  way of guarantying  the on-disk  relation
	 * between `oldpath/movedir' and `newpath' */
	result = is_part_of_different_mount_nopr(oldpath, newpath, mount);
	findmount_and_punlock_tree_nopr(newpath);
	PREEMPTION_POP(was);
#ifndef CONFIG_NO_SMP
	if (result == IS_PART_OF_DIFFERENT_MOUNT_NOPR_RETRY) {
		/* Wait for a blocking lock to (hopefully) go away. */
		task_tryyield_or_pause();
		goto again;
	}
#endif /* !CONFIG_NO_SMP */
	return result != IS_PART_OF_DIFFERENT_MOUNT_NOPR_NO;
}


/* Returns one of `FDIRNODE_RENAME_IN_PATH_*', or a reference pointer to
 * a `struct path' which the caller should wait for to become available,
 * before restarting the rename operation. */
PRIVATE WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
fdirnode_rename_in_path(struct path *oldpath, struct path *newpath,
                        struct frename_info *__restrict info)
		THROWS(...) {
	REF struct path *status;
	assert(!(info->frn_flags & AT_RENAME_EXCHANGE) || info->frn_repfile);

	/* Check for E_FSERROR_CROSS_DEVICE_LINK */
	assert(info->frn_olddir->fn_super == info->frn_file->fn_super);
	if unlikely(newpath->p_dir->fn_super != info->frn_olddir->fn_super)
		THROW(E_FSERROR_CROSS_DEVICE_LINK);

	/* Check for E_FSERROR_DIRECTORY_MOVE_TO_CHILD. For this purpose,
	 * we don't allow moving files across different mounting  points,
	 * meaning that we assert that `oldpath' and `newpath' share  the
	 * same common mounting point, and  that none of the parent's  of
	 * `newpath' (along  the chain  leading to  the nearest  mounting
	 * point) are actually pointing at `fnode_asdir(info->frn_file)'.
	 *
	 * Also  note that in regards to _PATH_F_PLOCK, we need to acquire
	 * _all_ locks along the chain of `oldpath' and `newpath'  leading
	 * back to the associated filesystem  root are locked at the  same
	 * time.  Otherwise, there's a race condition with moving a dir at
	 * the same time as moving the destination dir into a child of the
	 * first directory. */
	if (fnode_isdir(info->frn_file) && oldpath != newpath) {
		if unlikely(check_move_to_child(oldpath, newpath, fnode_asdir(info->frn_file)))
			THROW(E_FSERROR_DIRECTORY_MOVE_TO_CHILD);
	}

	/* Deal with replacement files. */
	if (info->frn_repfile) {
		if (!(info->frn_flags & AT_RENAME_EXCHANGE)) {
			bool old_isdir, new_isdir;
			/* Check that we're not replacing a directory with a regular file, or the opposite. */
			old_isdir = fnode_isdir(info->frn_file);
			new_isdir = fnode_isdir(info->frn_repfile);
			if unlikely(old_isdir != new_isdir) {
				if (!old_isdir) {
					THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_RENAME);
				} else {
					THROW(E_FSERROR_IS_A_DIRECTORY, E_FILESYSTEM_IS_A_DIRECTORY_RENAME);
				}
			}
		}
	}

	/* Deal with the path cache. */
	if (fnode_isdir(info->frn_file) || (info->frn_repfile && fnode_isdir(info->frn_repfile))) {
		/* Special case: we may need to shift around path caches. */
		char *newname_copy         = NULL;
		char const *orig_info_name = info->frn_name;
		TRY {
			if (!ADDR_ISKERN(orig_info_name)) {
				/* Prevent problems relating to user-space changing backing memory. */
				newname_copy = (char *)kmalloc((info->frn_namelen + 1) * sizeof(char), GFP_NORMAL);
				*(char *)mempcpy(newname_copy, orig_info_name, info->frn_namelen, sizeof(char)) = '\0';
				info->frn_name = newname_copy;
				info->frn_hash = fdirent_hash(newname_copy, info->frn_namelen);
			} else if (info->frn_hash == FLOOKUP_INFO_HASH_UNSET) {
				info->frn_hash = fdirent_hash(info->frn_name, info->frn_namelen);
			}
			if (info->frn_flags & AT_RENAME_EXCHANGE) {
				/* do cache transformations for: exchange path */
				incref(info->frn_oldent);
				TRY {
					status = fdirnode_exchange_paths(oldpath, newpath, info);
				} EXCEPT {
					decref_unlikely(info->frn_oldent);
					RETHROW();
				}
				decref_unlikely(info->frn_oldent);
			} else {
				/* do cache transformations for: replace path */
				status = fdirnode_replace_paths(oldpath, newpath, info);
			}
		} EXCEPT {
			info->frn_name = orig_info_name;
			kfree(newname_copy);
			RETHROW();
		}
		info->frn_name = orig_info_name;
		kfree(newname_copy);
	} else {
		/* Invoke the FS-level rename operation */
		status = (REF struct path *)fdirnode_rename(newpath->p_dir, info);
	}

	return (REF struct path *)status;
}



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
PUBLIC NONNULL((1, 4)) void KCALL
path_rename(struct path *oldpath, /*utf-8*/ USER CHECKED char const *oldname, u16 oldnamelen,
            struct path *newpath, /*utf-8*/ USER CHECKED char const *newname, u16 newnamelen,
            atflag_t atflags, bool check_permissions,
            /*out[1..1]_opt*/ REF struct fdirent **pold_dirent,
            /*out[1..1]_opt*/ REF struct fdirent **pnew_dirent,
            /*out[1..1]_opt*/ REF struct fnode **prenamed_node,
            /*out[0..1]_opt*/ REF struct fnode **preplaced_node,
            /*out[1..1]_opt*/ REF struct path **ptarget_path)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_DIRECTORY_MOVE_TO_CHILD,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, E_BADALLOC, ...) {
	REF struct path *status;
	struct frename_info info;
	REF struct fdirent *exchange_newname_dirent; /* [0..1] */
	REF struct fnode *exchange_newname_node;     /* [0..1] */
	REF struct fnode *replaced_node;             /* [0..1] */
	REF struct path *newpath_ref;                /* [0..1] */

	info.frn_flags = atflags;
again_acquire_lock:
	exchange_newname_dirent = NULL;
	exchange_newname_node   = NULL;
	replaced_node           = NULL;
	newpath_ref             = NULL;

	/* Assert permissions. */
	if (check_permissions) {
		fnode_access(oldpath->p_dir, W_OK);
		fnode_access(newpath->p_dir, W_OK);
	}

	twopaths_acquire_locks(oldpath, newpath);
	TRY {
		/* Don't do any replacements by default. */
		info.frn_repfile = NULL;

		/* Load the replacement file in EXCHANGE-mode */
		if (info.frn_flags & AT_RENAME_EXCHANGE) {
			info.frn_lookup_info.flu_name    = newname;
			info.frn_lookup_info.flu_namelen = newnamelen;
			info.frn_lookup_info.flu_hash    = FLOOKUP_INFO_HASH_UNSET;
again_lookup_newent:
			exchange_newname_dirent = fdirnode_lookup(newpath->p_dir, &info.frn_lookup_info);
			if unlikely(!exchange_newname_dirent)
				THROW(E_FSERROR_FILE_NOT_FOUND);
			exchange_newname_node = fdirent_opennode(exchange_newname_dirent, newpath->p_dir);
			if unlikely(!exchange_newname_node)
				goto again_lookup_newent;
			info.frn_repfile = exchange_newname_node;
		}

		info.frn_name    = oldname;
		info.frn_namelen = oldnamelen;
		info.frn_hash    = FLOOKUP_INFO_HASH_UNSET;
		DBG_memset(&info.frn_dent, 0xcc, sizeof(info.frn_dent));

again_lookup_oldent:
		/* Looking `oldname' within its directory. */
		info.frn_olddir = oldpath->p_dir;
		info.frn_oldent = fdirnode_lookup(info.frn_olddir, &info.frn_lookup_info);
		if unlikely(!info.frn_oldent)
			THROW(E_FSERROR_FILE_NOT_FOUND);

		/* NOTE: Can't  use `FINALLY_DECREF_UNLIKELY()' since that one will
		 *       decref the object originally given it, and not whatever is
		 *       set at the time of the FINALLY being unwound.
		 * As such, simply use RAII with a lambda function.
		 *
		 * NOTE: `info.frn_oldent' might change in case of `AT_RENAME_EXCHANGE',
		 *       where the field becomes [in|out]  REF. Because it's [const]  in
		 *       all other cases, we can simply always decref whatever is stored
		 *       within once this statement goes out-of-scope. */
		/*FINALLY_DECREF_UNLIKELY(info.frn_oldent);*/
		RAII_FINALLY {
			decref_unlikely(*&info.frn_oldent);
		};

		/* Open the node associated with `frn_oldent' */
		info.frn_file = fdirent_opennode(info.frn_oldent, info.frn_olddir);
		if unlikely(!info.frn_file)
			goto again_lookup_oldent;
		FINALLY_DECREF_UNLIKELY(info.frn_file);

		info.frn_name    = newname;
		info.frn_namelen = newnamelen;
		info.frn_hash    = FLOOKUP_INFO_HASH_UNSET;
		if (exchange_newname_dirent) {
set_rename_newname_for_exchange:
			info.frn_name    = exchange_newname_dirent->fd_name;
			info.frn_namelen = exchange_newname_dirent->fd_namelen;
			info.frn_hash    = exchange_newname_dirent->fd_hash;
		}

again_rename:
		DBG_memset(&info.frn_dent, 0xcc, sizeof(info.frn_dent));

		/* Do the rename operation. */
		status = fdirnode_rename_in_path(oldpath, newpath, &info);

		if (status != FDIRNODE_RENAME_IN_PATH_SUCCESS) {
			if (status == FDIRNODE_RENAME_IN_PATH_DELETED)
				goto again_lookup_oldent; /* Race condition; -> repeat the lookup */
			if (status != FDIRNODE_RENAME_IN_PATH_EXISTS) {
				/* Wait for a given path to become available. */
				assert(ADDR_ISKERN(status));
				goto waitfor_status_writelock;
			}
			assert(info.frn_dent && !wasdestroyed(info.frn_dent));
			assert(info.frn_repfile && !wasdestroyed(info.frn_repfile));
			if (info.frn_flags & AT_RENAME_EXCHANGE) {
				/* Update exchange information. */
				assert(exchange_newname_dirent != info.frn_dent);
				decref_unlikely(exchange_newname_dirent);
				decref_unlikely(exchange_newname_node);
				exchange_newname_dirent = info.frn_dent;    /* Inherit reference */
				exchange_newname_node   = info.frn_repfile; /* Inherit reference */
				if unlikely(!exchange_newname_dirent)
					THROW(E_FSERROR_FILE_NOT_FOUND); /* Exchange target got deleted. */
				if unlikely(!exchange_newname_node) {
					/* Very strange case, but another race condition relating to partially deleted files.
					 * Just  start over from scratch and pick up on the error wherever it truly happened. */
					twopaths_release_locks(oldpath, newpath);
					xdecref_unlikely(newpath_ref);
					xdecref_unlikely(exchange_newname_dirent);
					xdecref_unlikely(replaced_node);
					goto again_acquire_lock;
				}
				goto set_rename_newname_for_exchange;
			}

			/* File already exists -> check if it's a directory for move-to-directory. */
			if (fnode_isdir(info.frn_repfile) && (info.frn_flags & AT_RENAME_MOVETODIR)) {
				/* Perform a move-to-directory operation. */
				assert(!newpath_ref);
				FINALLY_DECREF_UNLIKELY(info.frn_dent);

				TRY {
					/* Assert read+exec access for the new directory. */
					if (check_permissions)
						fnode_access(info.frn_repfile, W_OK);

					/* Lookup or create the path for `info.frn_dent' */
					newpath_ref = path_lookupchildref_withlock(newpath,
					                                           info.frn_dent->fd_name,
					                                           info.frn_dent->fd_namelen,
					                                           info.frn_dent->fd_hash,
					                                           info.frn_flags);
					if (newpath_ref) {
						/* move-to-dir with mounting points would result in cross-device links. */
						if unlikely(path_ismount(newpath_ref))
							THROW(E_FSERROR_CROSS_DEVICE_LINK);
						decref_unlikely(info.frn_repfile);

						/* Acquire a write-lock to `newpath_ref' */
						if (newpath_ref != oldpath && !path_cldlock_trywrite(newpath_ref))
							goto waitfor_newpath_ref_writelock;
					} else {
						path_cldlist_rehash_before_insert(newpath);
						TRY {
							newpath_ref = _path_alloc();
						} EXCEPT {
							path_cldlist_rehash_after_remove(newpath);
							RETHROW();
						}
						newpath_ref->p_refcnt = 1;
						newpath_ref->p_flags  = PATH_F_NORMAL;
						newpath_ref->p_parent = incref(newpath);
						newpath_ref->p_name   = incref(info.frn_dent);
						newpath_ref->p_dir    = fnode_asdir(info.frn_repfile); /* Inherit reference */
						TAILQ_ENTRY_UNBOUND_INIT(&newpath_ref->p_recent);
						shared_rwlock_init_write(&newpath_ref->p_cldlock); /* We start out with a write-lock! */
						SLIST_INIT(&newpath_ref->p_cldlops);
						newpath_ref->p_cldused = 0;
						newpath_ref->p_cldsize = 0;
						newpath_ref->p_cldmask = 0;
						newpath_ref->p_cldlist = path_empty_cldlist;

						/* Insert into `newpath's child-list */
						path_cldlist_insert(newpath, newpath_ref);
					}
				} EXCEPT {
					decref_unlikely(info.frn_repfile);
					RETHROW();
				}

				/* Drop our own newpath-write-lock (we've got a ne one for `newpath_ref') */
				if (newpath != oldpath)
					path_cldlock_endwrite(newpath);

				/* Use this path from now on! */
				newpath = newpath_ref;

				/* The filename within the target directory is the original name of the file. */
				info.frn_name    = info.frn_oldent->fd_name;
				info.frn_namelen = info.frn_oldent->fd_namelen;
				info.frn_hash    = info.frn_oldent->fd_hash;
				info.frn_repfile = NULL;

				/* Don't allow recursive move-to-dir */
				info.frn_flags &= ~AT_RENAME_MOVETODIR;
				goto again_rename;
			}

			/* File already exists -> check if we're allowed to replace it. */
			if (info.frn_flags & AT_RENAME_NOREPLACE) {
				decref_unlikely(info.frn_dent);
				decref_unlikely(info.frn_repfile);
				THROW(E_FSERROR_FILE_ALREADY_EXISTS);
			}

			/* Reattempt the rename for the purpose of doing a file replacement */
			decref_unlikely(info.frn_dent);
			xdecref_unlikely(replaced_node);
			replaced_node = info.frn_repfile; /* Inherit reference */
			goto again_rename;
		}
		/* Success! */
		twopaths_release_locks(oldpath, newpath);
		if (pold_dirent)
			*pold_dirent = incref(info.frn_oldent);
		if (prenamed_node)
			*prenamed_node = mfile_asnode(incref(info.frn_file));
	} EXCEPT {
		twopaths_release_locks(oldpath, newpath);
		xdecref_unlikely(newpath_ref);
		xdecref_unlikely(exchange_newname_dirent);
		xdecref_unlikely(exchange_newname_node);
		xdecref_unlikely(replaced_node);
		RETHROW();
	}
	if (pnew_dirent)
		*pnew_dirent = info.frn_dent; /* Inherit reference */
	else {
		decref_unlikely(info.frn_dent);
	}
	if (preplaced_node)
		*preplaced_node = info.frn_repfile; /* Inherit reference */
	else {
		xdecref(info.frn_repfile);
	}
	if (newpath_ref) {
		if (ptarget_path) {
			*ptarget_path = newpath_ref; /* Inherit reference */
		} else {
			decref_unlikely(newpath_ref);
		}
	} else {
		if (ptarget_path)
			*ptarget_path = incref(newpath);
	}
	xdecref_unlikely(exchange_newname_dirent);
	xdecref_unlikely(exchange_newname_node);
	return;
	{
waitfor_newpath_ref_writelock:
		twopaths_release_locks(oldpath, newpath);
		FINALLY_DECREF_UNLIKELY(newpath_ref);
		path_cldlock_write(newpath_ref);
		path_cldlock_endwrite(newpath_ref);
	}
	goto again_acquire_lock;
	{
waitfor_status_writelock:
		twopaths_release_locks(oldpath, newpath);
		FINALLY_DECREF_UNLIKELY(status);
		path_cldlock_write(status);
		path_cldlock_endwrite(status);
	}
	goto again_acquire_lock;
}







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
PUBLIC NONNULL((1, 2)) ssize_t KCALL
path_print(struct path *__restrict self, __pformatprinter printer,
           void *arg, atflag_t atflags, struct path *root) {
	ssize_t result;
	if (!(atflags & _AT_PATHPRINT_REACHABLE)) {
		/* Check that `self' is a descendant of `root' */
		if (root && !path_isdescendantof(self, root)) {
			result = (*printer)(arg, "\\\\?\\", 4);
			goto done;
		}
		atflags |= _AT_PATHPRINT_REACHABLE;
	}
	if ((atflags & AT_DOSPATH) && path_isdrive(self)) {
		unsigned int i;
		struct vfs *path_vfs = _path_getvfs(self);
		vfs_driveslock_read(path_vfs);
		for (i = 0; i < COMPILER_LENOF(path_vfs->vf_drives); ++i) {
			if (path_vfs->vf_drives[i] == self)
				break;
		}
		vfs_driveslock_endread(path_vfs);
		if (i < COMPILER_LENOF(path_vfs->vf_drives)) {
			char buf[3];
			buf[0] = 'A' + i;
			buf[1] = ':';
			buf[2] = '\\';
			result = (*printer)(arg, buf, (atflags & AT_PATHPRINT_INCTRAIL) ? 3 : 2);
			goto done;
		}
	}
	if (self != root && !path_isroot(self)) {
		REF struct path *parent;
		/* Recursively print our parent first (with a trailing slash). */
		parent = path_getparent(self);
		FINALLY_DECREF_UNLIKELY(parent);
		result = path_print(parent, printer, arg,
		                    atflags | AT_PATHPRINT_INCTRAIL,
		                    root);
	} else {
		/* UNIX root directory. */
		if (atflags & AT_DOSPATH) {
			result = (*printer)(arg, "\\\\unix\\", 7);
		} else {
			result = (*printer)(arg, "/", 1);
		}
		goto done;
	}
	if unlikely(result < 0)
		goto done;

	/* Print the name of this directory. */
	{
		ssize_t temp;
		temp = (*printer)(arg, self->p_name->fd_name, self->p_name->fd_namelen);
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}
	/* Print a trailing slash (if needed). */
	if (atflags & AT_PATHPRINT_INCTRAIL) {
		ssize_t temp;
		temp = (*printer)(arg, (atflags & AT_DOSPATH) ? "\\" : "/", 1);
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}
done:
	return result;
}


/* Helper  wrapper for `path_print' that follows up the call by printing
 * the given `dentry_name...+=dentry_namelen'. You should always include
 * `AT_PATHPRINT_INCTRAIL'  when calling this function; else the printed
 * path may be invalid. */
PUBLIC NONNULL((1, 4)) ssize_t KCALL
path_printent(struct path *__restrict self,
              USER CHECKED char const *dentry_name, u16 dentry_namelen,
              __pformatprinter printer, void *arg, atflag_t atflags,
              struct path *root) {
	ssize_t result;
	result = path_print(self, printer, arg, atflags, root);
	if likely(result >= 0) {
		ssize_t temp;
		temp = (*printer)(arg, dentry_name, dentry_namelen);
		if likely(temp >= 0) {
			result += temp;
		} else {
			result = temp;
		}
	}
	return result;
}



/* Helper functions for printing a path into a user-space buffer.
 * @return: * : The required buffer size (including a trailing NUL-character) */
PUBLIC NONNULL((1)) size_t KCALL
path_sprint(struct path *__restrict self, USER CHECKED char *buffer, size_t buflen,
            atflag_t atflags, struct path *root) THROWS(E_SEGFAULT) {
	size_t result;
	struct format_snprintf_data data;
	format_snprintf_init(&data, buffer, buflen);
	result = (size_t)path_print(self, &format_snprintf_printer,
	                            &data, atflags, root);
	if (result < buflen)
		buffer[result] = '\0';
	++result;
	return result;
}

PUBLIC NONNULL((1)) size_t KCALL
path_sprintent(struct path *__restrict self,
               USER CHECKED char const *dentry_name, u16 dentry_namelen,
               USER CHECKED char *buffer, size_t buflen,
               atflag_t atflags, struct path *root) THROWS(E_SEGFAULT) {
	size_t result;
	struct format_snprintf_data data;
	format_snprintf_init(&data, buffer, buflen);
	result = (size_t)path_printent(self, dentry_name, dentry_namelen,
	                               &format_snprintf_printer, &data,
	                               atflags, root);
	if (result < buflen)
		buffer[result] = '\0';
	++result;
	return result;
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_PATHIO_C */