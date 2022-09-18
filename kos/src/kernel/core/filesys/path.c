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
#ifndef GUARD_KERNEL_CORE_FILESYS_PATH_C
#define GUARD_KERNEL_CORE_FILESYS_PATH_C 1
#define __WANT_PATH__p_LOPS
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman/driver.h>
#include <kernel/personality.h>
#include <sched/cred.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/lockop.h>

#include <assert.h>
#include <ctype.h>
#include <malloca.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/*[[[config CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK! = 7]]]*/
#ifndef CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK
#define CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK 7
#endif /* !CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK */
/*[[[end]]]*/

/* Check if `child' is a descendant of `root' (including `child == root') */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL path_isdescendantof)(struct path *child,
                                   struct path const *root) {
#ifdef CONFIG_NO_SMP
	preemption_flag_t was;
	if (root == child)
		return true;
	if (path_isroot(child))
		return false;
	preemption_pushoff(&was);
	for (;;) {
		child = child->p_parent;
		if (root == child) {
			preemption_pop(&was);
			return true;
		}
		if (path_isroot(child))
			break;
	}
	preemption_pop(&was);
#else /* CONFIG_NO_SMP */
	REF struct path *iter;
	if (root == child)
		return true;
	if (path_isroot(child))
		return false;
	child = path_getparent(child);
	for (;;) {
		if (root == child) {
			decref_unlikely(child);
			return true;
		}
		if (path_isroot(child))
			break;
		iter = path_getparent(child);
		decref_unlikely(child);
		child = iter;
	}
	decref_unlikely(child);
#endif /* !CONFIG_NO_SMP */
	return false;
}

/* Return a pointer to the VFS associated with `self' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) struct vfs *
NOTHROW(FCALL _path_getvfs)(struct path *__restrict self) {
	if (!path_isroot(self)) {
#ifdef CONFIG_NO_SMP
		preemption_flag_t was;
		preemption_pushoff(&was);
		do {
			self = self->p_parent;
		} while (!path_isroot(self));
		preemption_pop(&was);
#else /* CONFIG_NO_SMP */
		struct vfs *result;
		self = path_getparent(self);
		while (!path_isroot(self)) {
			REF struct path *next;
			next = path_getparent(self);
			decref_unlikely(self);
			self = next;
		}
		/* Don't need to incref(_p_vfs) w/ a lock: paths aren't allowed to change VFS */
		result = self->_p_vfs;
		decref_unlikely(self);
		return result;
#endif /* !CONFIG_NO_SMP */
	}
	return self->_p_vfs;
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC path_remove_from_supermounts_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                        struct fsuper *__restrict UNUSED(obj)) {
	struct path *me;
	REF struct fsuper *delsup;
	me     = container_of(self, struct path, _p_supplop);
	delsup = (REF struct fsuper *)me->p_dir; /* Hacky temporary storage... */
	path_free(me);

	/* If needed, also delete the superblock. */
	if (delsup) {
		REF struct driver *drv;
		fsuper_delete(delsup);
		drv = delsup->fs_sys->ffs_drv;
		decref(delsup);

		/* This reference was originally held by `path_asmount(me)->pm_fsmount' */
		decref_unlikely(drv);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC path_remove_from_supermounts_lop)(Toblockop(fsuper) *__restrict self,
                                                    struct fsuper *__restrict obj) {
	struct pathmount *me = container_of(self, struct pathmount, _p_suplop);
	COMPILER_READ_BARRIER();
	me->p_dir = NULL; /* Don't delete super by default */
	if likely(LIST_ISBOUND(me, pm_fsmount)) {
		LIST_REMOVE(me, pm_fsmount);
		DBG_memset(&me->pm_fsmount, 0xcc, sizeof(me->pm_fsmount));

		/* Special handling for when the list of mounting points becomes empty. */
		if (LIST_EMPTY(&obj->fs_mounts)) {
			ATOMIC_WRITE(obj->fs_mounts.lh_first, FSUPER_MOUNTS_DELETED);
			/* Delete the superblock & decref the backing driver (later) */
			me->p_dir = (REF struct fdirnode *)incref(obj); /* Hacky temporary storage... */
		} else {
			/* This reference was originally held by `path_asmount(me)->pm_fsmount'
			 * We  can use *_nokill  because other mounting  points still hold more
			 * references. */
			decref_nokill(obj->fs_sys->ffs_drv);
		}
	}
	me->_p_supplop.oplo_func = &path_remove_from_supermounts_postlop;
	return &me->_p_supplop;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC path_remove_from_parent_postlop)(Tobpostlockop(path) *__restrict self,
                                                   struct path *__restrict UNUSED(obj)) {
	struct path *me;
	REF struct fdirnode *dir;
	me = container_of(self, struct path, _p_pthplop);

	/* Only destroy the NAME field _AFTER_ our path was removed from it's  parent's
	 * child-tree. That way, anyone enumerating/scanning said tree is _always_ able
	 * to directly access the name of _any_ (non-NULL) child-path, and assume  that
	 * this name is still valid. (without having to do a tryincref() test) */
	decref_unlikely(me->p_name);
	DBG_memset(&me->p_name, 0xcc, sizeof(me->p_name));

	dir = me->p_dir;
	if (path_ismount(me)) {
		/* Special case: must remove our mounting point from the superblock.
		 * Also: if our mounting point ends up  being the last of them  all,
		 *       then we must also call `fsuper_delete()' in order to delete
		 *       the filesystem (anonymize all files and prevent creation of
		 *       new files, etc...) */
		struct pathmount *mount = path_asmount(me);
		COMPILER_READ_BARRIER();
		if likely(LIST_ISBOUND(mount, pm_fsmount)) {
			struct fsuper *super = dir->fn_super;
			if (fsuper_mounts_trywrite(super)) {
				COMPILER_READ_BARRIER();
				if likely(LIST_ISBOUND(mount, pm_fsmount)) {
					LIST_REMOVE(mount, pm_fsmount);
					DBG_memset(&mount->pm_fsmount, 0xcc, sizeof(mount->pm_fsmount));

					/* Special handling for when the list of mounting points becomes empty. */
					if (LIST_EMPTY(&super->fs_mounts)) {
						REF struct driver *drv;
						ATOMIC_WRITE(super->fs_mounts.lh_first, FSUPER_MOUNTS_DELETED);
						fsuper_mounts_endwrite(super);

						/* Delete the superblock */
						drv = super->fs_sys->ffs_drv;
						fsuper_delete(super);
						decref(dir);

						/* This reference was originally held by `path_asmount(mount)->pm_fsmount' */
						decref_unlikely(drv);
						path_free(me);
						return;
					} else {
						/* This reference was originally held by `path_asmount(mount)->pm_fsmount'
						 * We  can  use *_nokill  because other  mounting  points still  hold more
						 * references. */
						decref_nokill(super->fs_sys->ffs_drv);
					}
				}
				fsuper_mounts_endwrite(super);
			} else {
				/* Must remove the mounting point asynchronously. */
				me->_p_suplop.olo_func = &path_remove_from_supermounts_lop;
				oblockop_enqueue(&super->fs_mountslockops, &me->_p_suplop);
				_fsuper_mounts_reap(super);
				decref_unlikely(dir);
				return;
			}
		}
	}
	decref_unlikely(dir);
	path_free(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(path) *
NOTHROW(LOCKOP_CC path_remove_from_parent_lop)(Toblockop(path) *__restrict self,
                                               struct path *__restrict obj) {
	struct path *me = container_of(self, struct path, _p_pthlop);
	COMPILER_READ_BARRIER();
	if likely(obj->p_cldlist != PATH_CLDLIST_DELETED) {
		if (path_cldlist_remove(obj, me))
			path_cldlist_rehash_after_remove(obj);
	}
	me->_p_pthplop.oplo_func = &path_remove_from_parent_postlop;
	return &me->_p_pthplop;
}


/* Destroy a given path, automatically removing it from:
 *  - path_parent(self)->p_cldlist    (asynchronously via lockops in path_parent(self)->p_cldlops)
 *  - path_getsuper(self)->fs_mounts  (asynchronously via lockops in  path_getsuper(self)->fs_mountslockops.
 *                                    If this path was the last mounting point, also call `fsuper_delete()') */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL path_destroy)(struct path *__restrict self) {
	if (self->p_cldlist != PATH_CLDLIST_DELETED &&
	    self->p_cldlist != path_empty_cldlist)
		kfree(self->p_cldlist);
	DBG_memset(&self->p_cldused, 0xcc, sizeof(self->p_cldused));
	DBG_memset(&self->p_cldsize, 0xcc, sizeof(self->p_cldsize));
	DBG_memset(&self->p_cldmask, 0xcc, sizeof(self->p_cldmask));
	DBG_memset(&self->p_cldlist, 0xcc, sizeof(self->p_cldlist));

	if unlikely(path_isroot(self)) {
		/* Special case for VFS root path nodes. */
		WEAK REF struct vfs *myvfs = self->_p_vfs;
		DBG_memset(&self->_p_vfs, 0xcc, sizeof(self->_p_vfs));
		weakdecref(myvfs);
	} else {
		struct path *parent;

		/* Remove the path from its parent's child list (possibly asynchronously) */
		parent = self->p_parent;
		DBG_memset(&self->p_parent, 0xcc, sizeof(self->p_parent));
		if (parent != NULL) {
			COMPILER_READ_BARRIER();
			if likely(parent->p_cldlist != PATH_CLDLIST_DELETED) {
				if (path_cldlock_trywrite(parent)) {
					COMPILER_READ_BARRIER();
					if likely(parent->p_cldlist != PATH_CLDLIST_DELETED) {
						if (path_cldlist_remove(parent, self))
							path_cldlist_rehash_after_remove(parent);
					}
					path_cldlock_endwrite(parent);
				} else {
					/* Have to use lockops... */
					self->_p_pthlop.olo_func = &path_remove_from_parent_lop;
					oblockop_enqueue(&parent->p_cldlops, &self->_p_pthlop);
					_path_cldlock_reap(parent);
					decref_unlikely(parent);
					return;
				}
			}
			decref_unlikely(parent);
		}
	}
	path_remove_from_parent_postlop(&self->_p_pthplop, /*parent*/ self);
}


/* Empty hash-vector for `struct path::p_cldlist' */
DATDEF struct path_bucket const _path_empty_cldlist[1] ASMNAME("path_empty_cldlist");
PUBLIC_CONST struct path_bucket const _path_empty_cldlist[1] = { { NULL } };


/* Helper macros for working with `struct path::p_cldlock' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _path_cldlock_reap)(struct path *__restrict self) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      (&self->p_cldlops)
#define __LOCAL_obj       self
#define __LOCAL_type      path
#define __LOCAL_trylock() path_cldlock_trywrite(self)
#define __LOCAL_unlock()  _path_cldlock_endwrite(self)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}




/* Special path pointed-to by newly-allocated VFS */
INTERN struct path deleted_path = {
	.p_refcnt  = 1, /* +1: deleted_path */
	.p_flags   = PATH_F_NORMAL,
	{ .p_parent  = NULL }, /* Technically, this isn't allowed, but it's the best we can do. */
	.p_name    = &fdirent_empty,
	.p_dir     = &fsuper_unmounted.fs_root,
	.p_recent  = TAILQ_ENTRY_UNBOUND_INITIALIZER,
	.p_cldlock = SHARED_RWLOCK_INIT,
	.p_cldlops = SLIST_HEAD_INITIALIZER(deleted_path.p_cldlops),
	{{ 0, 0, 0 }},
	.p_cldlist = PATH_CLDLIST_DELETED,
};


/* Rehash with the given list buffer */
INTERN NOBLOCK NONNULL((1, 2)) void /* "INTERN" because used in "memory/mman/cc.c" */
NOTHROW(FCALL path_cldlist_rehash_with)(struct path *__restrict self,
                                        struct path_bucket *__restrict new_list,
                                        size_t new_mask) {
	/* Rehash existing entries. */
	uintptr_t i, j, perturb;
	assert(new_mask >= self->p_cldused);
	for (i = 0; i <= self->p_cldmask; ++i) {
		struct path_bucket *dst;
		struct path *pth;
		uintptr_t hash;
		pth = self->p_cldlist[i].pb_path;
		if (!pth || pth == &deleted_path)
			continue; /* Empty, or deleted. */
		hash = path_hashof(pth);
		j = perturb = hash & new_mask;
		for (;; path_hashnx(j, perturb)) {
			dst = &new_list[j & new_mask];
			if (!dst->pb_path)
				break;
		}
		dst->pb_path = pth; /* Rehash */
	}
	if (self->p_cldlist != path_empty_cldlist)
		kfree(self->p_cldlist);
	self->p_cldlist = new_list;
	self->p_cldmask = new_mask;
	self->p_cldsize = self->p_cldused; /* All deleted entries were removed... */
}


/* Ensure that sufficient space exists for the addition of another path to the child list
 * Caller must be holding a lock to `self'. */
PUBLIC NONNULL((1)) void FCALL
path_cldlist_rehash_before_insert(struct path *__restrict self)
		THROWS(E_BADALLOC) {
	if (((self->p_cldsize + 1) * 3) / 2 >= self->p_cldmask) {
		/* Must rehash! */
		struct path_bucket *new_list;
		size_t new_mask = CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK;
		size_t thresh   = ((self->p_cldused + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		new_list = (struct path_bucket *)kmalloc_nx((new_mask + 1) *
		                                            sizeof(struct path_bucket),
		                                            GFP_CALLOC);
		if unlikely(!new_list) {
			if ((self->p_cldsize + 1) <= self->p_cldmask)
				return;
			new_mask = CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK;
			while ((self->p_cldused + 1) > self->p_cldmask)
				new_mask = (new_mask << 1) | 1;
			new_list = (struct path_bucket *)kmalloc((new_mask + 1) *
			                                         sizeof(struct path_bucket),
			                                         GFP_CALLOC);
		}
		/* Rehash using the new list. */
		path_cldlist_rehash_with(self, new_list, new_mask);
		assert(self->p_cldused == self->p_cldsize);
	}
}

/* Try to rehash the child-path list of `self' following the removal of a child. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL path_cldlist_rehash_after_remove)(struct path *__restrict self) {
	if ((self->p_cldused < (self->p_cldmask / 3)) &&
	    self->p_cldmask > CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK) {
		/* Try to shrink the hash-vector's mask size. */
		size_t new_mask = CONFIG_KERNEL_PATH_CLDLIST_INITIAL_MASK;
		size_t thresh   = ((self->p_cldused + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		if (new_mask < self->p_cldmask) {
			/* Try to shrink */
			struct path_bucket *new_list;
			new_list = (struct path_bucket *)kmalloc_nx((new_mask + 1) *
			                                            sizeof(struct path_bucket),
			                                            GFP_ATOMIC | GFP_CALLOC);
			/* If the alloc worked, re-hash using `new_list' */
			if (new_list)
				path_cldlist_rehash_with(self, new_list, new_mask);
		}
	}
}

/* Remove `elem' from the child-list of `self'
 * @return: true:  Successfully removed.
 * @return: false: Wasn't actually a member. */
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL path_cldlist_remove)(struct path *__restrict self,
                                   struct path *__restrict elem) {
	uintptr_t hash, i, perturb;
	struct path_bucket *bucket;
	assert(self->p_cldlist != PATH_CLDLIST_DELETED);
	hash = path_hashof(elem);
	i = perturb = hash & self->p_cldmask;
	for (;; path_hashnx(i, perturb)) {
		bucket = &self->p_cldlist[i & self->p_cldmask];
		if (bucket->pb_path == NULL)
			return false; /* Not found... */
		if (bucket->pb_path == elem)
			break;
	}
	assert(self->p_cldlist != path_empty_cldlist);
	assert(self->p_cldused != 0);
	assert(self->p_cldsize != 0);
	assert(self->p_cldsize <= self->p_cldmask);
	bucket->pb_path = &deleted_path;
	--self->p_cldused;
	return true;
}

/* Same as `path_cldlist_remove()', but UD  if
 * `elem' isn't actually in `self's child list */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL path_cldlist_remove_force)(struct path *__restrict self,
                                         struct path *__restrict elem) {
	uintptr_t hash, i, perturb;
	struct path_bucket *bucket;
	assert(self->p_cldlist != PATH_CLDLIST_DELETED);
	assert(self->p_cldlist != path_empty_cldlist);
	assert(self->p_cldused != 0);
	assert(self->p_cldsize != 0);
	assert(self->p_cldsize <= self->p_cldmask);
	hash = path_hashof(elem);
	i = perturb = hash & self->p_cldmask;
	for (;; path_hashnx(i, perturb)) {
		bucket = &self->p_cldlist[i & self->p_cldmask];
		assert(bucket->pb_path != NULL);
		if (bucket->pb_path == elem)
			break;
	}
	bucket->pb_path = &deleted_path;
	--self->p_cldused;
}



/* Insert `elem' into the child-list of `self'
 * Caller must have made a call to `path_cldlist_rehash_before_insert()' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL path_cldlist_insert)(struct path *__restrict self,
                                   struct path *__restrict elem) {
	uintptr_t hash, i, perturb;
	struct path_bucket *ent;
	assert((self->p_cldsize + 1) <= self->p_cldmask);
	hash = path_hashof(elem);
	i = perturb = hash & self->p_cldmask;
	for (;; path_hashnx(i, perturb)) {
		struct path *pth;
		ent = &self->p_cldlist[i & self->p_cldmask];
		pth = ent->pb_path;
		if (!pth) {
			/* Found a free slot */
			++self->p_cldsize;
			break;
		}
		if (pth == &deleted_path)
			break; /* Re-use a previously deleted slot. */
	}
	ent->pb_path = elem;
	++self->p_cldused;
}



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
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct path *KCALL
path_lookupchild(struct path *__restrict self,
                 USER CHECKED /*utf-8*/ char const *name,
                 u16 namelen, uintptr_t namehash, atflag_t atflags)
		THROWS(E_FSERROR_DELETED, E_WOULDBLOCK, E_SEGFAULT) {
	REF struct path *result;
	path_cldlock_read(self);
	RAII_FINALLY { path_cldlock_endread(self); };
	result = path_lookupchild_withlock(self, name, namelen,
	                                   namehash, atflags);

	/* Try to get a reference to the path. */
	if (result != NULL) {
		if (tryincref(result)) {
			/* Still alive */
		} else {
			/* Even though it would also happen async,
			 * remove the  dead child-path  ourselves. */
			path_cldlist_remove_force(self, result);
			path_cldlist_rehash_after_remove(self);
			result = NULL;
		}
	}
	return result;
}

/* Same as `path_lookupchild()', but caller must be holding a lock `path_cldlock_read(self)' */
PUBLIC WUNUSED NONNULL((1)) struct path *KCALL
path_lookupchild_withlock(struct path *__restrict self,
                          USER CHECKED /*utf-8*/ char const *name,
                          u16 namelen, uintptr_t namehash, atflag_t atflags)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT) {
	uintptr_t i, perturb;

	/* Check if this directory has been deleted. */
	if unlikely(self->p_cldlist == PATH_CLDLIST_DELETED)
		THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);

	/* Search through the hash-table. */
	assert(self->p_cldsize <= self->p_cldmask);
	i = perturb = namehash & self->p_cldmask;
	for (;; path_hashnx(i, perturb)) {
		struct path *result;
		result = self->p_cldlist[i & self->p_cldmask].pb_path;
		if (!result)
			break; /* No such monitor... */
		if (result->p_name->fd_hash != namehash)
			continue; /* Wrong hash */
		if unlikely(result->p_name->fd_namelen != namelen)
			continue; /* Wrong name length */
		if unlikely(bcmp(result->p_name->fd_name, name, namelen, sizeof(char)) != 0)
			continue; /* Wrong name */
		if unlikely(result == &deleted_path)
			continue; /* Prevent any chance of *this* happening... */
		/* Found it! */
		return result;
	}

	/* If requested, also perform a case-insensitive search */
	if (atflags & AT_DOSPATH) {
		for (i = 0; i <= self->p_cldmask; ++i) {
			struct path *result = self->p_cldlist[i].pb_path;
			if (!result)
				continue;
			if unlikely(result->p_name->fd_namelen != namelen)
				continue; /* Wrong name length */
			if unlikely(memcasecmp(result->p_name->fd_name, name, namelen * sizeof(char)) != 0)
				continue; /* Wrong name */
			if unlikely(result == &deleted_path)
				continue; /* Prevent any chance of *this* happening... */
			/* Found it! */
			return result;
		}
	}

	/* Nope; don't know anything about this one... */
	return NULL;
}

PUBLIC WUNUSED NONNULL((1)) REF struct path *KCALL
path_lookupchildref_withlock(struct path *__restrict self,
                             /*utf-8*/ USER CHECKED char const *name,
                             u16 namelen, uintptr_t namehash,
                             atflag_t atflags)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT) {
	REF struct path *result;
	result = path_lookupchild_withlock(self, name, namelen,
	                                   namehash, atflags);
	/* Try to get a reference to the path. */
	if (result != NULL) {
		if (tryincref(result)) {
			/* Still alive */
		} else {
			/* Even though it would also happen async,
			 * remove the  dead child-path  ourselves. */
			path_cldlist_remove_force(self, result);
			path_cldlist_rehash_after_remove(self);
			result = NULL;
		}
	}
	return result;
}




/* Create a new child of `self' with for the given `dir' and `dent',
 * whilst making sure that no other path with the same name  already
 * exists (in accordance to `atflags') */
PRIVATE BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 3, 4)) REF struct path *KCALL
path_makechild(struct path *__restrict self, atflag_t atflags,
               /*inherit(on_success)*/ REF struct fdirnode *__restrict dir,
               /*inherit(on_success)*/ REF struct fdirent *__restrict dent)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct path *result;
	/* It's a directory! -> Create a new path child! */
	result = _path_alloc();

	/* Initialize... */
	result->p_refcnt = 1;
	result->p_flags  = PATH_F_NORMAL;
	result->p_parent = self; /* incref'd later */
	result->p_name   = dent; /* Inherit reference (on_success) */
	result->p_dir    = dir;  /* Inherit reference (on_success) */
	TAILQ_ENTRY_UNBOUND_INIT(&result->p_recent);
	shared_rwlock_init(&result->p_cldlock);
	SLIST_INIT(&result->p_cldlops);
	result->p_cldused = 0;
	result->p_cldsize = 0;
	result->p_cldmask = 0;
	result->p_cldlist = path_empty_cldlist;

	/* Try to cache the new path element. */
	TRY {
		struct path *existing;
		path_cldlock_write(self);

		/* Check if the a path with an identical name showed in the mean time... */
		TRY {
			existing = path_lookupchild_withlock(self, dent->fd_name, dent->fd_namelen,
			                                     dent->fd_hash, atflags);
		} EXCEPT {
			path_cldlock_endwrite(self);
			RETHROW();
		}
		if unlikely(existing != NULL) {
			if (!tryincref(existing)) {
				/* Race condition: another thread must have created it in the mean time... */
				path_cldlock_endwrite(self);
				_path_free(result);
				decref_unlikely(dir);
				decref_unlikely(dent);
				return existing;
			}
			/* The existing path is  dead; remove it ourselves  even
			 * though it should also have been able to it by itself. */
			path_cldlist_remove_force(self, existing);

			/* Don't rehash since we're about to add another element again! */
		} else {
			/* Nothing in here already; but ensure that there's enough space for one more entry! */
			path_cldlist_rehash_before_insert(self);
		}

		/* All right! let's add this new entry! */
		path_cldlist_insert(self, result);
	} EXCEPT {
		_path_free(result);
		RETHROW();
	}

	incref(self); /* For `result->p_parent' */
	path_cldlock_endwrite(self);
	return result;
}



PRIVATE BLOCKING ATTR_NOINLINE WUNUSED NONNULL((1, 2, 3, 4)) REF struct path *KCALL
path_readlink_and_walk(struct path *__restrict self,
                       u32 *__restrict premaining_symlinks,
                       struct flnknode *__restrict lnk,
                       size_t *__restrict pbufsize, atflag_t atflags)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	size_t reqsize, bufsize;
	char *buf;
	bufsize = *pbufsize;
	buf     = (char *)malloca(bufsize);
	RAII_FINALLY { freea(buf); };
	reqsize = flnknode_readlink(lnk, buf, bufsize);
	if (reqsize >= bufsize) {
		/* Need more space */
		*pbufsize = reqsize + 1;
		return NULL;
	}

	/* NUL-terminate buffer. */
	buf[reqsize] = '\0';

	/* Do the walk */
	return path_traverse_ex(self, premaining_symlinks, buf, NULL, NULL, atflags);
}


/* Check if `self' is visible from `fs_getroot(THIS_FS)' */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
is_path_visible(struct path *__restrict self) THROWS(E_WOULDBLOCK) {
	REF struct path *root;
	bool result;
	root   = fs_getroot(THIS_FS);
	result = path_isdescendantof(self, root);
	decref_unlikely(root);
	return result;
}


/* Walk a given symlink */
PRIVATE BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
path_walklink(/*inherit(always)*/ REF struct path *__restrict self,
              u32 *__restrict premaining_symlinks,
              /*inherit(always)*/ REF struct flnknode *__restrict lnk, atflag_t atflags)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	REF struct path *result;
	size_t bufsize;
	struct flnknode_ops const *ops;
again:
	FINALLY_DECREF_UNLIKELY(self);
	FINALLY_DECREF_UNLIKELY(lnk);
	ops = flnknode_getops(lnk);

	/* If defined, try to make use of `lno_walklink'.
	 * - To reiterate the documentation of `lno_walklink':
	 *   for "/proc/[PID]/fd/[FDNO]",  this returns  paths
	 *   as would also be used during `openat(2)'. */
	if (ops->lno_walklink != NULL) {
		result = (*ops->lno_walklink)(lnk, premaining_symlinks);
		if (result) {
			/* Verify that `result' is still  reachable from the current POSIX  root.
			 * You  might argue that this doesn't need to be done, but I would beg to
			 * differ, since you  could still  get here  when trying  to use  another
			 * process's file table to access directories that supposed to be hidden.
			 *
			 * Of  course, at the point point where  you can access some other proc's
			 * file descriptor table, you could also just open() such a file and then
			 * use that file with the openat()  system calls, but don't forget:  this
			 * operator isn't  just for  /proc/[PID]/fd/[FDNO] (which  is private  to
			 * the  owning process; iow:  mode_t: 0400), but  also for other per-proc
			 * directories like `/proc/[PID]/cwd',  which _ARENT_ process-private  as
			 * far as I know... */
			TRY {
				if (is_path_visible(result))
					return result;
			} EXCEPT {
				decref_unlikely(result);
				RETHROW();
			}

			/* Path isn't visible -> do normal symlink expansion! */
			decref_unlikely(result);
		}
	}

	/* We can also try  to use this  operator, in which  case we need  to
	 * construct a child-path of the expanded file (if it's a directory),
	 * or traverse it as another symlink  (if it's another one of  those) */
	if (ops->lno_expandlink != NULL) {
		REF struct fnode *open_node;
		REF struct path *open_path;
		REF struct fdirent *open_dirent;
		open_node = (*ops->lno_expandlink)(lnk, &open_path, &open_dirent,
		                                   premaining_symlinks);
		if (open_node != NULL) {
			FINALLY_DECREF_UNLIKELY(open_dirent);
			TRY {
				if (is_path_visible(open_path)) {
					if (fnode_islnk(open_node)) {
						/* Check that we're allowed to walk a symlink. */
						if unlikely(*premaining_symlinks == 0)
							THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS);
						--*premaining_symlinks;
						lnk  = fnode_aslnk(open_node); /* Inherit reference */
						self = open_path;              /* Inherit reference */
						goto again;
					}
					if (fnode_isdir(open_node)) {
						/* Try to find `open_dirent' within `open_path' */
						REF struct path *result;
						struct fdirnode *dir;
						dir    = fnode_asdir(open_node);
						result = path_lookupchild(open_path,
						                          open_dirent->fd_name,
						                          open_dirent->fd_namelen,
						                          open_dirent->fd_hash, 0);
						if (result != NULL) {
							if likely(result->p_dir == dir) {
								decref_unlikely(open_node);
								decref_unlikely(open_path);
								return result; /* Inherit reference */
							}
							decref_unlikely(result);
						} else {
							/* Create the missing child-path. */
							result = path_makechild(self, atflags, dir, open_dirent);
							decref_unlikely(open_node);
							decref_unlikely(open_path);
							return result;
						}
					}

					/* Neither a symlink, or a directory.
					 *
					 * But still fallthru to the fallback readlink+traverse handling! */
				}
			} EXCEPT {
				decref_unlikely(open_node);
				decref_unlikely(open_path);
				RETHROW();
			}
			decref_unlikely(open_node);
			decref_unlikely(open_path);
		}
	}

	/* Direct link text access */
	if (ops->lno_linkstr != NULL) {
		char const *str = (*ops->lno_linkstr)(lnk);
		return path_traverse_ex(self, premaining_symlinks, str, NULL, NULL, atflags);
	}

	/* Fallback: must read link contents into temporary buffer. */
	bufsize = 256;
	do {
		result = path_readlink_and_walk(self, premaining_symlinks,
		                                lnk, &bufsize, atflags);
	} while (!result);
	return result;
}


/* Expand a child path of `self' and re-return the new path.
 *   - If caller doesn't have EXEC permission for `self', THROW(E_FSERROR_ACCESS_DENIED)
 *   - If the path is marked as `PATH_CLDLIST_DELETED', THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);
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
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct path *KCALL
path_expandchild(struct path *__restrict self, u32 *__restrict premaining_symlinks,
                 USER CHECKED /*utf-8*/ char const *name,
                 u16 namelen, uintptr_t namehash, atflag_t atflags)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...) {
	REF struct fdirent *dent;
	REF struct fnode *node;

	/* First up: check if we've got EXEC permissions. */
	fnode_access(self->p_dir, R_OK | X_OK);

	/* TODO: Optional per-directory operator: `dno_expandchild' that can
	 * be implemented by certain directories to directly return the path
	 * objects for named children.
	 *
	 * Could be used by procfs to forgo the creation of temporary files
	 * during per-process path traversal. */


	/* Do a normal lookup for child nodes. */
	{
		REF struct path *result;
		result = path_lookupchild(self, name, namelen, namehash, atflags);
		if (result != NULL)
			return result;
	}

	/* Entry isn't pre-cached; time to query the directory itself */
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
	if unlikely(!dent)
		THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DIR);

	/* Open the associated node. */
	TRY {
		node = fdirent_opennode(dent, self->p_dir);
		if unlikely(!node) {
			decref_unlikely(dent);
			goto again_lookup_dent;
		}
		TRY {
			/* Check what we're dealing with. */
			if (fnode_isdir(node))
				return path_makechild(self, atflags, fnode_asdir(node), dent);
		} EXCEPT {
			decref_unlikely(node);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(dent);
		RETHROW();
	}
	decref_unlikely(dent);

	/* Check for symbolic links. */
	if (fnode_islnk(node)) {

		/* Check that we're allowed to walk a symlink. */
		if unlikely(*premaining_symlinks == 0) {
			decref_unlikely(node);
			THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS);
		}
		--*premaining_symlinks;

		/* Walk a symbolic link. */
		return path_walklink(incref(self), premaining_symlinks,
		                     fnode_aslnk(node), /* inherit:node */
		                     atflags & AT_NO_AUTOMOUNT);
	}

	/* Got something other than a directory... */
	decref_unlikely(node);
	THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_WALK);
}




PRIVATE BLOCKING ATTR_NOINLINE WUNUSED NONNULL((1, 2, 3, 4)) REF struct fnode *KCALL
path_readlink_and_walknode(struct path *__restrict self,
                           u32 *__restrict premaining_symlinks,
                           struct flnknode *__restrict lnk,
                           size_t *__restrict pbufsize,
                           /*out[1..1]_opt*/ REF struct path **presult_path,
                           /*out[1..1]_opt*/ REF struct fdirent **presult_dirent,
                           atflag_t atflags)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	size_t reqsize, bufsize;
	char *buf;
	bufsize = *pbufsize;
	buf     = (char *)malloca(bufsize);
	RAII_FINALLY { freea(buf); };
	reqsize = flnknode_readlink(lnk, buf, bufsize);
	if (reqsize >= bufsize) {
		/* Need more space */
		*pbufsize = reqsize + 1;
		return NULL;
	}

	/* NUL-terminate buffer. */
	buf[reqsize] = '\0';

	/* Do the walk */
	return path_traversefull_ex(self, premaining_symlinks, buf,
	                            atflags, presult_path, presult_dirent);
}

/* Walk a given symlink */
PRIVATE BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5)) REF struct fnode *KCALL
path_walklinknode(struct path *__restrict self,
                  u32 *__restrict premaining_symlinks,
                  struct flnknode *__restrict lnk,
                  /*out[1..1]_opt*/ REF struct path **__restrict presult_path,
                  /*out[1..1]_opt*/ REF struct fdirent **__restrict presult_dirent,
                  atflag_t atflags)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	REF struct fnode *result;
	size_t bufsize;
	struct flnknode_ops const *ops;
	ops = flnknode_getops(lnk);

	/* If defined, try to make use of `lno_expandlink'.
	 * - To reiterate the documentation of `lno_expandlink':
	 *   for "/proc/[PID]/exe", this returns info from `thismman_execinfo' */
	if (ops->lno_expandlink) {
		result = (*ops->lno_expandlink)(lnk, presult_path, presult_dirent,
		                                premaining_symlinks);
		if (result) {
			/* Verify that `*presult_path' is reachable from `fs_getroot()' */
			TRY {
				if (is_path_visible(*presult_path))
					return result;
			} EXCEPT {
				decref_unlikely(*presult_path);
				decref_unlikely(*presult_dirent);
				decref_unlikely(result);
				RETHROW();
			}

			/* Fallback: if the path isn't visible, do a normal link expansion. */
			decref_unlikely(*presult_path);
			decref_unlikely(*presult_dirent);
			decref_unlikely(result);
		}
	}

	/* Direct link text access */
	if (ops->lno_linkstr != NULL) {
		char const *str = (*ops->lno_linkstr)(lnk);
		return path_traversefull_ex(self, premaining_symlinks, str,
		                            atflags, presult_path, presult_dirent);
	}

	/* Fallback: must read link contents into temporary buffer. */
	bufsize = 256;
	do {
		result = path_readlink_and_walknode(self, premaining_symlinks, lnk, &bufsize,
		                                    presult_path, presult_dirent, atflags);
	} while (!result);
	return result;
}


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
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
path_expandchildnode(struct path *__restrict self, u32 *__restrict premaining_symlinks,
                     USER CHECKED /*utf-8*/ char const *name,
                     u16 namelen, uintptr_t namehash, atflag_t atflags,
                     /*out[1..1]_opt*/ REF struct path **presult_path,
                     /*out[1..1]_opt*/ REF struct fdirent **presult_dirent)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, ...) {
	REF struct fnode *result;
	REF struct fdirent *dent;

	/* First up: check if we've got EXEC permissions. */
	fnode_access(self->p_dir, R_OK | X_OK);

	/* Do a normal lookup for child nodes. */
	{
		REF struct path *pth;
		path_cldlock_read(self);
		TRY {
			pth = path_lookupchild_withlock(self, name, namelen,
			                                namehash, atflags);
		} EXCEPT {
			path_cldlock_endread(self);
			RETHROW();
		}
		/* Try to get a reference to the path. */
		if (pth != NULL) {
			if (tryincref(pth)) {
				/* Still alive */
				if (presult_dirent)
					*presult_dirent = incref(pth->p_name);
				path_cldlock_endread(self);
				result = mfile_asnode(incref(pth->p_dir));
				if (presult_path)
					*presult_path = incref(self);
				decref_unlikely(pth);
				return result;
			} else {
				/* Even though it would also happen async,
				 * remove the  dead child-path  ourselves. */
				path_cldlist_remove_force(self, pth);
				path_cldlist_rehash_after_remove(self);
			}
		}
		path_cldlock_endread(self);
	}

	/* Time to query the directory itself */
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
	if unlikely(!dent)
		THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DIR);

	/* Open the associated node. */
	TRY {
		result = fdirent_opennode(dent, self->p_dir);
		if unlikely(!result) {
			decref_unlikely(dent);
			goto again_lookup_dent;
		}
	} EXCEPT {
		decref_unlikely(dent);
		RETHROW();
	}

	/* Deal with symlink nodes (in case we're supposed to expand them) */
	if (fnode_islnk(result) && !(atflags & AT_SYMLINK_NOFOLLOW)) {
		REF struct flnknode *lnk;
		incref(self);
		do {
			FINALLY_DECREF_UNLIKELY(self);
			lnk = fnode_aslnk(result);
			decref_unlikely(dent);
			FINALLY_DECREF_UNLIKELY(lnk);

			/* Check that we're allowed to walk a symlink. */
			if unlikely(*premaining_symlinks == 0)
				THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS);
			--*premaining_symlinks;

			/* NOTE: Set `AT_SYMLINK_NOFOLLOW' to prevent stack-recursive
			 *       expansion of symbolic links in the last element.  To
			 *       preserve stack space, we must just do that locally! */
			result = path_walklinknode(self, premaining_symlinks, lnk,
			                           (REF struct path **)&self, &dent,
			                           (atflags & AT_NO_AUTOMOUNT) |
			                           AT_SYMLINK_NOFOLLOW);
		} while (fnode_islnk(result));

		/* Write-back results. */
		if (presult_path) {
			*presult_path = self; /* Inherit reference */
		} else {
			decref_unlikely(self);
		}
		if (presult_dirent) {
			*presult_dirent = dent; /* Inherit reference */
		} else {
			decref_unlikely(dent);
		}
		return result;
	}

	/* Default case: return the pointed-to node. */
	if (presult_path)
		*presult_path = incref(self);
	if (presult_dirent) {
		*presult_dirent = dent; /* Inherit reference */
	} else {
		decref_unlikely(dent);
	}
	return result;
}




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
 *  - AT_EMPTY_PATH:              `upath'  may be an empty string, which causes
 *                                `cwd ? cwd : THIS_FS->fs_cwd' to be returned.
 *  - AT_IGNORE_TRAILING_SLASHES: Ignore trailing slashes
 *  - Other flags are silently ignored. */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((2)) REF struct path *KCALL
path_traverse_ex(struct path *cwd, u32 *__restrict premaining_symlinks,
                 USER CHECKED /*utf-8*/ char const *upath,
                 /*out_opt*/ USER CHECKED /*utf-8*/ char const **plastseg,
                 /*out_opt*/ u16 *plastlen, atflag_t atflags)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY, E_IOERROR,
		       E_BADALLOC, ...) {
	/* Flags for the purpose of selecting which slashes we accept (AT_DOSPATH) */
	atflag_t sep_atflags = atflags;

	/* NOTE: You're allowed to assume that `path_isdescendantof(cwd, root_ref)',
	 *       so-long as both are non-NULL. */
	REF struct path *cwd_ref  = NULL; /* Backup reference for `cwd' */
	REF struct path *root_ref = NULL; /* Lazily initialized: current root directory */
	REF struct path *result;

	/* Check if this is a universal unix pathname. */
	if unlikely(upath[0] == '\\' && upath[1] == '\\' &&
	            0 == ((atflags & AT_DOSPATH) ? memcasecmp(upath + 2, "unix", 4 * sizeof(char))
	                                         : bcmp(upath + 2, "unix", 4, sizeof(char))) &&
	            upath[6] == '\\') {
		char ch;
		upath += COMPILER_STRLEN("\\\\unix\\");
		ch = upath[0];

		/* Directory-element resolution _always_ happens
		 * as case-sensitive, but  we still accept  '\\'
		 * as an alias for '/'  in the remainder of  the
		 * path. */
		atflags &= ~AT_DOSPATH;
		sep_atflags |= AT_DOSPATH;
		if (ch == '.' && (ch = upath[1], ch == '/' || ch == '\\')) {
			/* Relative to current directory */
			upath += 2;
		} else {
			/* Relative to root directory */
			root_ref = fs_getroot(THIS_FS);
			cwd_ref  = incref(root_ref);
			cwd      = root_ref;
		}
	} else {
		unsigned char firstch;
		firstch = upath[0];
		COMPILER_READ_BARRIER();
		if (firstch == 0) {
			/* Special case: Empty path */
			if (atflags & AT_EMPTY_PATH) {
				if (plastlen)
					*plastlen = 0;
				return incref(cwd);
			}
			THROW(E_FSERROR_ILLEGAL_PATH);
		}
		if (atflags & AT_DOSPATH) {
			/* Check for DOS path drive prefixes. */
			if (isalpha(firstch) && upath[1] == ':') {
				char maybe_sep;
				firstch = toupper(firstch);
				assert(firstch >= 'A' && firstch <= 'Z');
				firstch -= 'A';
				upath += 2;
				maybe_sep = *upath;
				COMPILER_READ_BARRIER();
				if (maybe_sep == '/' || maybe_sep == '\\') {
					struct vfs *myvfs;
					/* Path is relative to drive root */
do_drive_root_rel:
					myvfs = THIS_VFS;
					vfs_driveslock_read(myvfs);
					root_ref = myvfs->vf_drives[firstch];
					if (!root_ref) {
						vfs_driveslock_endread(myvfs);
						THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DRIVE);
					}
					ATOMIC_ADD(root_ref->p_refcnt, 2); /* +1: root_ref, +1: cwd_ref */
					cwd_ref = root_ref;
					vfs_driveslock_endread(myvfs);
				} else {
					struct fs *myfs = THIS_FS;
					/* Path is relative to drive cwd */
					fs_pathlock_read(myfs);
					cwd_ref = myfs->fs_dcwd[firstch];
					if (!cwd_ref) {
						fs_pathlock_endread(myfs);
						goto do_drive_root_rel;
					}
					incref(cwd_ref);
					fs_pathlock_endread(myfs);
				}
				cwd = cwd_ref;
			} else if (firstch == '/' || firstch == '\\') {
				/* Relative  to root of current drive (that is:
				 * the closest path  which is a  drive, or  the
				 * calling thread's root directory as fallback) */
				struct fs *myfs = THIS_FS;
				fs_pathlock_read(myfs);
				if (!cwd) {
					cwd = myfs->fs_cwd;
				} else {
					/* Make sure that `cwd' is still a child of our current root. */
					if unlikely(!path_isdescendantof(cwd, myfs->fs_root)) {
						fs_pathlock_endread(myfs);
						THROW(E_FSERROR_PATH_NOT_FOUND,
						      E_FILESYSTEM_PATH_NOT_FOUND_DIR);
					}
				}
				root_ref = myfs->fs_root;
				incref(cwd);
				while (cwd != root_ref && !path_isdrive(cwd)) {
					REF struct path *nextcwd;
					assert(!path_isroot(cwd));
					nextcwd = path_getparent(cwd);
					decref_unlikely(cwd);
					cwd = nextcwd;
				}
				incref(cwd);
				fs_pathlock_endread(myfs);
				root_ref = cwd_ref = cwd;
			}
		} else {
			/* Check if the path is absolute. */
			if (firstch == '/') {
				/* Path must be interpreted relative to root directory. */
				root_ref = fs_getroot(THIS_FS);
				cwd_ref  = incref(root_ref);
				cwd      = root_ref;
				++upath;
			}
		}
	}

	/* The main loop for processing path segments. */
	TRY {
		char ch;
		size_t seg_len;
		USER CHECKED /*utf-8*/ char const *seg_str;

		/* Load the next path-segment. */
next_segment:
		seg_str = upath;
		if (sep_atflags & AT_DOSPATH) {
			for (;;) {
				ch = *upath;
				COMPILER_READ_BARRIER();
				if (!ch || ch == '/' || ch == '\\')
					break;
				++upath;
			}
			seg_len = (size_t)(upath - seg_str);
			if (ch == '/' || ch == '\\') {
				for (;;) {
					ch = *upath;
					COMPILER_READ_BARRIER();
					if (ch != '/' && ch != '\\')
						break;
					++upath;
				}

				/* Skip the `ch == '\0'' check below if trailing slashes aren't ignored. */
				if (!(atflags & AT_IGNORE_TRAILING_SLASHES))
					goto do_walk_segment;
			}
		} else {
			for (;;) {
				ch = *upath;
				COMPILER_READ_BARRIER();
				if (!ch || ch == '/')
					break;
				++upath;
			}
			seg_len = (size_t)(upath - seg_str);
			if (ch == '/') {
				for (;;) {
					ch = *upath;
					COMPILER_READ_BARRIER();
					if (ch != '/')
						break;
					++upath;
				}

				/* Skip the `ch == '\0'' check below if trailing slashes aren't ignored. */
				if (!(atflags & AT_IGNORE_TRAILING_SLASHES))
					goto do_walk_segment;
			}
		}

		/* Check if we've reached the end of the user-string. */
		if (ch == '\0') {
			if unlikely(seg_len > UINT16_MAX) {
throw_segment_too_long:
				THROW(E_FSERROR_ILLEGAL_PATH);
			}

			/* Last segment reached. */
			if (plastlen) {
				/* Certain segment names cannot be used as last-segments. */
				if (seg_len == 1 && seg_str[0] == '.')
					goto do_pwd_segment;
				if (seg_len == 2 && seg_str[0] == '.' && seg_str[1] == '.')
					goto do_par_segment;
				*plastseg = seg_str;
				*plastlen = (u16)seg_len;
				goto done;
			}
			if (!seg_len)
				goto done;
		}
do_walk_segment:

		/* Verify that the segment isn't too long. */
		if unlikely(seg_len > UINT16_MAX)
			goto throw_segment_too_long;

		switch (seg_len) {
		case 0:
			/* Empty segment (ignore) */
			break;

		case 1:
			if (seg_str[0] == '.') {
do_pwd_segment:
				break; /* Current directory reference... */
			}
			goto normal_segment;

		case 2:
			if (seg_str[0] == '.' && seg_str[1] == '.') {
do_par_segment:
				/* Parent directory reference...
				 * When we haven't loaded the root yet, this can get kind-of complicated
				 * since we have to verify that some custom caller-given cwd is actually
				 * reachable from the current UNIX chroot() directory.
				 *
				 * If it isn't, then we throw `E_FSERROR_PATH_NOT_FOUND:E_FILESYSTEM_PATH_NOT_FOUND_DIR' */
				if (!root_ref) {
					if (!cwd) {
						struct fs *myfs = THIS_FS;
						fs_pathlock_read(myfs);
						cwd_ref = incref(myfs->fs_cwd);
						if (atflags & AT_DOSPATH) {
							/* `root_ref' must become the first directory before the unix
							 * chroot that is  a dos  drive, or the  unix chroot  itself. */
							root_ref = cwd_ref;
							incref(root_ref);
							while (root_ref != myfs->fs_root && !path_isdrive(root_ref)) {
								REF struct path *next_root_ref;
								assert(!path_isroot(root_ref));
								next_root_ref = path_getparent(root_ref);
								decref_unlikely(root_ref);
								root_ref = next_root_ref;
							}
						} else {
							root_ref = incref(myfs->fs_root);
						}
						fs_pathlock_endread(myfs);
						cwd = cwd_ref;
					} else if (atflags & AT_DOSPATH) {
						struct fs *myfs = THIS_FS;
						fs_pathlock_read(myfs);

						/* Verify that `cwd' is reachable from the root */
						if unlikely(!path_isdescendantof(cwd, myfs->fs_root)) {
							fs_pathlock_endread(myfs);
							goto throw_not_found_after_bad_descendant;
						}

						/* `root_ref' must become the first directory before the unix
						 * chroot that is  a dos  drive, or the  unix chroot  itself. */
						root_ref = cwd;
						incref(root_ref);
						while (root_ref != myfs->fs_root && !path_isdrive(root_ref)) {
							REF struct path *next_root_ref;
							assert(!path_isroot(root_ref));
							next_root_ref = path_getparent(root_ref);
							decref_unlikely(root_ref);
							root_ref = next_root_ref;
						}
						fs_pathlock_endread(myfs);
					} else {
						root_ref = fs_getroot(THIS_FS);

						/* Verify that `cwd' is reachable from the root */
						if unlikely(!path_isdescendantof(cwd, root_ref)) {
throw_not_found_after_bad_descendant:
							THROW(E_FSERROR_PATH_NOT_FOUND,
							      E_FILESYSTEM_PATH_NOT_FOUND_DIR);
						}
					}
				} else {
					if unlikely(!cwd)
						cwd = cwd_ref = fs_getroot(THIS_FS);
				}

				/* Walk up the directory tree (but stop once we've reached the root) */
				if (cwd != root_ref) {
					REF struct path *nextcwd;
					assert(!path_isroot(cwd));
					nextcwd = path_getparent(cwd);
					xdecref_unlikely(cwd_ref);
					cwd = cwd_ref = nextcwd;
				}
				break;
			}
			goto normal_segment;

		default: {
			REF struct path *nextpath;
normal_segment:
			if (!cwd)
				cwd = cwd_ref = fs_getcwd(THIS_FS);

			/* Expand the named path child. */
			nextpath = path_expandchild(cwd, premaining_symlinks, seg_str, seg_len,
			                            fdirent_hash(seg_str, seg_len), atflags);
			xdecref(cwd_ref);
			cwd = cwd_ref = nextpath;
		}	break;

		}

		/* Do the next path segment. */
		goto next_segment;

done:
		/* Return the current working directory */
		result = cwd;
		if (result) {
			incref(result);
		} else {
			result = fs_getcwd(THIS_FS);
		}
	} EXCEPT {
		xdecref(cwd_ref);
		xdecref(root_ref);
		RETHROW();
	}
	xdecref(cwd_ref);
	xdecref(root_ref);
	return result;
}




/* Same as `path_traverse_ex',  but automatically keep  track of symlinks,  as
 * well as pass `cwd = fd_cwd == AT_FDCWD ? NULL : handles_lookuppath(fd_cwd)' */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED REF struct path *KCALL
path_traverse(fd_t fd_cwd, USER CHECKED /*utf-8*/ char const *upath,
              /*out_opt*/ USER CHECKED /*utf-8*/ char const **plastseg,
              /*out_opt*/ u16 *plastlen, atflag_t atflags)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...) {
	REF struct path *used_cwd;
	u32 remaining_symlinks = ATOMIC_READ(THIS_FS->fs_lnkmax);
	if likely(fd_cwd == AT_FDCWD)
		return path_traverse_ex(NULL, &remaining_symlinks, upath, plastseg, plastlen, atflags);
	used_cwd = handles_lookuppath(fd_cwd);
	FINALLY_DECREF_UNLIKELY(used_cwd);
	return path_traverse_ex(used_cwd, &remaining_symlinks, upath, plastseg, plastlen, atflags);
}



/* Helper wrapper that combines `path_traverse_ex()' with `path_expandchildnode()'
 * @param: atflags: Set of: `AT_DOSPATH | AT_NO_AUTOMOUNT | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW' */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED REF struct fnode *KCALL
path_traversefull_ex(struct path *cwd, u32 *__restrict premaining_symlinks,
                     USER CHECKED /*utf-8*/ char const *upath, atflag_t atflags,
                     /*out[1..1]_opt*/ REF struct path **presult_path,
                     /*out[1..1]_opt*/ REF struct fdirent **presult_dirent)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...) {
	REF struct fnode *result;
	REF struct path *rpath;
	USER CHECKED /*utf-8*/ char const *lastseg;
	u16 lastlen;

	/* Traverse everything except for the last path component. */
	rpath = path_traverse_ex_r(cwd, premaining_symlinks, upath, &lastseg, &lastlen, atflags);

	/* Check for special case: no last segment. */
	if (lastlen == 0) {
		result = mfile_asnode(incref(rpath->p_dir));
		if (presult_dirent)
			*presult_dirent = incref(&fdirent_empty);
		if (presult_path) {
			*presult_path = rpath; /* Inherit reference */
		} else {
			decref_unlikely(rpath);
		}
		return result;
	}

	/* Walk the final element of the path. */
	FINALLY_DECREF_UNLIKELY(rpath);
	return path_expandchildnode(rpath, premaining_symlinks, lastseg, lastlen,
	                            fdirent_hash(lastseg, lastlen), atflags,
	                            presult_path, presult_dirent);
}



/* Helper wrapper that combines `path_traverse()' with `path_expandchildnode()'
 * @param: atflags: Set of: `AT_DOSPATH | AT_NO_AUTOMOUNT | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW' */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED REF struct fnode *KCALL
path_traversefull(fd_t fd_cwd, USER CHECKED /*utf-8*/ char const *upath, atflag_t atflags,
                  /*out[1..1]_opt*/ REF struct path **presult_path,
                  /*out[1..1]_opt*/ REF struct fdirent **presult_dirent)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_FSERROR_ACCESS_DENIED, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_FSERROR_NOT_A_DIRECTORY,
		       E_IOERROR, E_BADALLOC, ...) {
	REF struct path *used_cwd;
	u32 remaining_symlinks = ATOMIC_READ(THIS_FS->fs_lnkmax);
	if likely(fd_cwd == AT_FDCWD)
		return path_traversefull_ex(NULL, &remaining_symlinks, upath, atflags, presult_path, presult_dirent);
	used_cwd = handles_lookuppath(fd_cwd);
	FINALLY_DECREF_UNLIKELY(used_cwd);
	return path_traversefull_ex(used_cwd, &remaining_symlinks, upath, atflags, presult_path, presult_dirent);
}









/************************************************************************/
/* open(2)                                                              */
/************************************************************************/

PRIVATE BLOCKING NONNULL((1, 2, 3, 4, 5)) unsigned int KCALL
create_symlink_target_with_text(struct path *__restrict symlink_path,
                                u32 *__restrict premaining_symlinks,
                                char const *__restrict text,
                                struct fmkfile_info *__restrict creat_info,
                                REF struct path **__restrict presult_path,
                                atflag_t atflags) {
	unsigned int status;
	REF struct path *result_path;
	result_path = path_traverse_ex(symlink_path, premaining_symlinks, text,
	                               &creat_info->mkf_name,
	                               &creat_info->mkf_namelen, atflags);
	/* (Try to) create the pointed-to file. */
	TRY {
		status = fdirnode_mkfile(result_path->p_dir, creat_info);
	} EXCEPT {
		decref_unlikely(result_path);
		RETHROW();
	}
	*presult_path = result_path; /* Inherit reference. */
	return status;
}


#define CREATE_SYMLINK_TARGET_WITH_BUFSIZ_MORE ((unsigned int)-1)
PRIVATE BLOCKING ATTR_NOINLINE NONNULL((1, 2, 3, 4, 5, 6)) unsigned int KCALL
create_symlink_target_with_bufsiz(struct path *__restrict symlink_path,
                                  u32 *__restrict premaining_symlinks,
                                  struct flnknode *__restrict lnk,
                                  struct fmkfile_info *__restrict creat_info,
                                  REF struct path **__restrict presult_path,
                                  size_t *__restrict pbufsize, atflag_t atflags) {
	size_t reqsize, bufsize;
	char *buf;
	bufsize = *pbufsize;
	buf     = (char *)malloca(bufsize);
	RAII_FINALLY { freea(buf); };
	reqsize = flnknode_readlink(lnk, buf, bufsize);
	if (reqsize >= bufsize) {
		/* Need more space */
		*pbufsize = reqsize + 1;
		return CREATE_SYMLINK_TARGET_WITH_BUFSIZ_MORE;
	}

	/* NUL-terminate buffer. */
	buf[reqsize] = '\0';

	/* Do the walk */
	return create_symlink_target_with_text(symlink_path, premaining_symlinks,
	                                       buf, creat_info, presult_path, atflags);
}


/* Must write references to `creat_info->mkf_dent' and `creat_info->mkf_rnode' */
PRIVATE BLOCKING NONNULL((1, 2, 3, 4, 5)) unsigned int KCALL
create_symlink_target(struct path *__restrict symlink_path,
                      u32 *__restrict premaining_symlinks,
                      struct flnknode *__restrict lnk,
                      struct fmkfile_info *__restrict creat_info,
                      REF struct path **__restrict presult_path,
                      atflag_t atflags) {
	unsigned int result;
	size_t bufsize;
	struct flnknode_ops const *ops;
	ops = flnknode_getops(lnk);

	/* Direct link text access */
	if (ops->lno_linkstr != NULL) {
		char const *str = (*ops->lno_linkstr)(lnk);
		return create_symlink_target_with_text(symlink_path, premaining_symlinks,
		                                       str, creat_info, presult_path, atflags);
	}

	/* Fallback: must read link contents into temporary buffer. */
	bufsize = 256;
	do {
		result = create_symlink_target_with_bufsiz(symlink_path, premaining_symlinks,
		                                           lnk, creat_info, presult_path,
		                                           &bufsize, atflags);
	} while (result == CREATE_SYMLINK_TARGET_WITH_BUFSIZ_MORE);
	return result;
}



/* Sets of `R_OK | W_OK' corresponding to the specified access-mode. */
PUBLIC_CONST unsigned int const fnode_access_accmode[O_ACCMODE + 1] = {
	[O_RDONLY] = R_OK,
	[O_WRONLY] = W_OK,
	[O_RDWR]   = W_OK | R_OK,
};


/* Open (or create) a file, the same way user-space open(2) works. */
PUBLIC BLOCKING WUNUSED NONNULL((2)) REF struct handle KCALL
path_open_ex(struct path *cwd, u32 *__restrict premaining_symlinks,
             USER CHECKED char const *filename,
             oflag_t oflags, mode_t mode) {
	atflag_t atflags;
	REF struct handle result;
	if (oflags & O_CREAT) {
		if (has_personality(KP_OPEN_CREAT_CHECK_MODE)) {
			if unlikely(mode & ~07777) {
				THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
				      E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE,
				      mode, ~07777 /*, 0*/);
			}
		}
		/* Unconditionally mask mode flags. */
		mode &= 07777;
	}

#ifdef __O_ACCMODE_INVALID
	if ((oflags & O_ACCMODE) == __O_ACCMODE_INVALID) {
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG,
		      oflags, O_ACCMODE, __O_ACCMODE_INVALID);
	}
#endif /* __O_ACCMODE_INVALID */

	/* Convert `oflags' into `atflags' */
#if (O_NOFOLLOW == AT_SYMLINK_NOFOLLOW && O_DOSPATH == AT_DOSPATH)
	atflags = oflags & (AT_SYMLINK_NOFOLLOW | AT_DOSPATH);
#elif O_NOFOLLOW == AT_SYMLINK_NOFOLLOW
	atflags = oflags & AT_SYMLINK_NOFOLLOW;
	if (oflags & O_DOSPATH)
		atflags |= AT_DOSPATH;
#elif O_DOSPATH == AT_DOSPATH
	atflags = oflags & AT_DOSPATH;
	if (oflags & O_NOFOLLOW)
		atflags |= AT_SYMLINK_NOFOLLOW;
#else /* ... */
	atflags = 0;
	if (oflags & O_NOFOLLOW)
		atflags |= AT_SYMLINK_NOFOLLOW;
	if (oflags & O_DOSPATH)
		atflags |= AT_DOSPATH;
#endif /* !... */

	/* Transform `atflags' based on local fs overrides. */
	atflags = fs_atflags(atflags);

	/* Figure out how the open() should be performed. */
	if (oflags & O_PATH) {
		/* Only need to lookup the resulting path object. */
		if (oflags & ~(O_ACCMODE | O_APPEND | O_NONBLOCK | O_SYNC |
		               O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
		               O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC |
		               O_CLOFORK | O_PATH | O_DOSPATH)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG,
			      oflags,
			      ~(O_ACCMODE | O_APPEND | O_NONBLOCK | O_SYNC |
			        O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
			        O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC |
			        O_CLOFORK | O_PATH | O_DOSPATH),
			      O_PATH | (oflags & O_DIRECTORY));
		}
		result.h_type = HANDLE_TYPE_PATH;
		result.h_data = path_traverse_ex(cwd, premaining_symlinks,
		                                 filename, NULL, NULL, atflags);

		/* Set access mode. */
		result.h_mode = IO_FROM_OPENFLAG(oflags);
	} else if (oflags & O_CREAT) {
		REF struct filehandle *rhand;
		REF struct path *access_path;
		struct fmkfile_info info;
		VALIDATE_FLAGSET(oflags,
		                 O_ACCMODE | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND |
		                 O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
		                 O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH |
		                 O_TMPFILE | O_DOSPATH,
		                 E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG);
		access_path = path_traverse_ex(cwd, premaining_symlinks, filename,
		                               &info.mkf_name, &info.mkf_namelen, atflags);
		TRY {
			info.mkf_hash          = FLOOKUP_INFO_HASH_UNSET;
			info.mkf_flags         = atflags;
			info.mkf_fmode         = S_IFREG | mode;
			info.mkf_creat.c_owner = cred_getfsuid();
			info.mkf_creat.c_group = cred_getfsgid();
			info.mkf_creat.c_atime = realtime();
			info.mkf_creat.c_mtime = info.mkf_creat.c_atime;
			info.mkf_creat.c_ctime = info.mkf_creat.c_atime;
			info.mkf_creat.c_btime = info.mkf_creat.c_atime;

#if 0 /* This can't be asserted here and instead happens while holding fs-specific
       * locks, after having learned that  the file to-be created doesn't  already
       * exist. (s.a. `struct fdirnode_ops::dno_mkfile') */
			fnode_access(access_path->p_dir, W_OK);
#endif

			/* Allocate the resulting file handle _before_ creating the file,
			 * so  no file is created in the  event that the handle cannot be
			 * allocated. */
			rhand = (REF struct filehandle *)kmalloc(sizeof(struct filehandle), GFP_NORMAL);
			TRY {
				unsigned int status;
				status = fdirnode_mkfile(access_path->p_dir, &info);
				if (status != FDIRNODE_MKFILE_SUCCESS) {
					assert(status == FDIRNODE_MKFILE_EXISTS);
					/* Check for special case: `info.mkf_rnode' is a symlink */
					if (fnode_islnk(info.mkf_rnode) && !(atflags & AT_SYMLINK_NOFOLLOW)) {
						/* Dereference and create pointed-to filename. */
						REF struct path *new_access_path;
						REF struct flnknode *lnknode;
						struct flnknode_ops const *lnknode_ops;
again_deref_lnknode:
						lnknode = fnode_aslnk(info.mkf_rnode); /* Inherit reference */
						FINALLY_DECREF_UNLIKELY(lnknode);
						DBG_memset(&info.mkf_rnode, 0xcc, sizeof(info.mkf_rnode));

						{
							FINALLY_DECREF_UNLIKELY(info.mkf_dent);

							/* Decrement the remaining-links counter. */
							if (!*premaining_symlinks)
								THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS);
							--*premaining_symlinks;

							/* Check for `lno_openlink' support */
							lnknode_ops = flnknode_getops(lnknode);
							if (lnknode_ops->lno_openlink &&
							    (*lnknode_ops->lno_openlink)(lnknode, &result, access_path,
							                                 info.mkf_dent, oflags)) {
								decref_unlikely(access_path);
								kfree(rhand);
								result.h_mode = IO_FROM_OPENFLAG(oflags);
								if unlikely(oflags & O_EXCL) {
									handle_decref(result);
									THROW(E_FSERROR_FILE_ALREADY_EXISTS); /* create-exclusive */
								}
								return result;
							}
						} /* Scope... */

						/* We can also make use of the `lno_expandlink' operator (if it's defined)
						 * This  is  essentially the  optimization  for `open("/proc/[PID]/exe")'. */
						if (lnknode_ops->lno_expandlink != NULL) {
							REF struct fnode *open_file;
							REF struct path *open_path;
							REF struct fdirent *open_dirent;
							open_file = (*lnknode_ops->lno_expandlink)(lnknode, &open_path, &open_dirent,
							                                           premaining_symlinks);
							if (open_file != NULL) {
								bool isvisible;
								TRY {
									if unlikely(oflags & O_EXCL)
										THROW(E_FSERROR_FILE_ALREADY_EXISTS); /* create-exclusive */
									isvisible = is_path_visible(open_path);
								} EXCEPT {
									decref_unlikely(open_path);
									decref_unlikely(open_dirent);
									decref_unlikely(open_file);
									RETHROW();
								}
								if (isvisible) {
									struct mfile_stream_ops const *stream;
									/* Check if we were really supposed to open the file via a FILEHANDLE. */
									stream = open_file->mf_ops->mo_stream;
									if (!stream ||
									    stream->mso_open == &mfile_v_open ||
									    (!stream->mso_read && !stream->mso_readv &&
									     !stream->mso_write && !stream->mso_writev)) {
										/* Yes: open the file via the already-created filehandle */
										decref_unlikely(access_path);
										info.mkf_rnode = open_file;   /* Inherit reference */
										info.mkf_dent  = open_dirent; /* Inherit reference */
										access_path    = open_path;   /* Inherit reference */
										goto open_created_file;
									}
									FINALLY_DECREF_UNLIKELY(open_file);
									FINALLY_DECREF_UNLIKELY(open_path);
									FINALLY_DECREF_UNLIKELY(open_dirent);

									/* Must invoke a custom open operator. */
									result.h_mode = IO_FROM_OPENFLAG(oflags);
									result.h_type = HANDLE_TYPE_MFILE;
									result.h_data = incref(open_file);
									TRY {
										mfile_open(open_file, &result, open_path, open_dirent, oflags);
										/* Clear a regular file if O_TRUNC was given. */
										if ((oflags & O_TRUNC) != 0 &&
										    (oflags & O_ACCMODE) != O_RDONLY &&
										    fnode_isreg(open_file))
											mfile_utruncate(open_file, 0);
									} EXCEPT {
										decref(result);
										RETHROW();
									}
									decref_unlikely(access_path);
									kfree(rhand);
									return result;
								} /* if (isvisible) */
								decref_unlikely(open_path);
								decref_unlikely(open_dirent);
								decref_unlikely(open_file);
							} /* if (open_file != NULL) */
						}     /* if (lnknode_ops->lno_expandlink != NULL) */

						/* Create the pointed-to file. */
						status = create_symlink_target(access_path, premaining_symlinks, lnknode, &info,
						                               &new_access_path, atflags & AT_NO_AUTOMOUNT);
						decref_unlikely(access_path);
						access_path = new_access_path;
						/* Keep on dereferencing paths until we get a LOOP error, or hit a non-symlink node. */
						if (status == FDIRNODE_MKFILE_EXISTS && fnode_islnk(info.mkf_rnode))
							goto again_deref_lnknode;
					}
					if (status != FDIRNODE_MKFILE_SUCCESS) {
						assert(status == FDIRNODE_MKFILE_EXISTS);
						TRY {
							if (oflags & O_EXCL)
								THROW(E_FSERROR_FILE_ALREADY_EXISTS); /* create-exclusive */
							/* Clear a regular file if O_TRUNC was given. */
							if ((oflags & O_TRUNC) && (oflags & O_ACCMODE) != O_RDONLY &&
							    fnode_isreg(info.mkf_rnode))
								mfile_utruncate(info.mkf_rnode, 0);
						} EXCEPT {
							decref_unlikely(info.mkf_dent);
							decref_unlikely(info.mkf_rnode);
							RETHROW();
						}
					}
				}
			} EXCEPT {
				kfree(rhand);
				RETHROW();
			}
		} EXCEPT {
			decref_unlikely(access_path);
			RETHROW();
		}

		/* Fill in the new access handle. */
open_created_file:
		rhand->fh_refcnt = 1;
		rhand->fh_file   = info.mkf_rnode; /* Inherit reference */
		rhand->fh_path   = access_path;    /* Inherit reference */
		rhand->fh_dirent = info.mkf_dent;  /* Inherit reference */
		atomic64_init(&rhand->fh_offset, 0);

		/* Initialize result handle. */
		result.h_mode = IO_FROM_OPENFLAG(oflags);
		result.h_data = rhand; /* Inherit reference. */
		result.h_type = HANDLE_TYPE_FILEHANDLE;
	} else {
		REF struct fnode *file;
		REF struct path *access_path;
		REF struct fdirent *access_dent;
		if (oflags & O_DIRECTORY) {
			if (oflags & ~(O_ACCMODE | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK |
			               O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
			               O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC |
			               O_CLOFORK | O_PATH | O_TMPFILE | O_DOSPATH)) {
				THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
				      E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG,
				      oflags,
				      ~(O_ACCMODE | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC |
				        O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW |
				        O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | O_DOSPATH),
				      O_DIRECTORY);
			}
		} else {
			VALIDATE_FLAGSET(oflags,
			                 O_ACCMODE | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND |
			                 O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
			                 O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK |
			                 O_PATH | O_TMPFILE | O_DOSPATH,
			                 E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG);
		}

		/* Open the named node */
		file = path_traversefull_ex(cwd, premaining_symlinks, filename,
		                            atflags | AT_SYMLINK_NOFOLLOW,
		                            &access_path, &access_dent);
again_handle_traversed_file:
		FINALLY_DECREF_UNLIKELY(file);
		FINALLY_DECREF_UNLIKELY(access_path);
		FINALLY_DECREF_UNLIKELY(access_dent);
		if (fnode_islnk(file)) {
			struct flnknode_ops const *lnknode_ops;
			struct flnknode *lnknode = fnode_aslnk(file);

			/* Check that we're allowed to walk a symlink. */
			if unlikely(atflags & AT_SYMLINK_NOFOLLOW)
				THROW(E_FSERROR_IS_A_SYMBOLIC_LINK, E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN);
			if unlikely(*premaining_symlinks == 0)
				THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS);
			--*premaining_symlinks;

			/* Check for `lno_openlink' support */
			lnknode_ops = flnknode_getops(lnknode);
			if (lnknode_ops->lno_openlink &&
			    (*lnknode_ops->lno_openlink)(lnknode, &result, access_path,
			                                 access_dent, oflags)) {
				result.h_mode = IO_FROM_OPENFLAG(oflags);
				return result;
			}

			/* We can also make use of the `lno_expandlink' operator (if it's defined)
			 * This  is  essentially the  optimization  for `open("/proc/[PID]/exe")'. */
			if (lnknode_ops->lno_expandlink != NULL) {
				REF struct fnode *open_file;
				REF struct path *open_path;
				REF struct fdirent *open_dirent;
				open_file = (*lnknode_ops->lno_expandlink)(lnknode, &open_path, &open_dirent,
				                                           premaining_symlinks);
				if (open_file != NULL) {
					FINALLY_DECREF_UNLIKELY(open_file);
					FINALLY_DECREF_UNLIKELY(open_path);
					FINALLY_DECREF_UNLIKELY(open_dirent);
					if (is_path_visible(open_path)) {
						/* Must invoke a custom open operator. */
						result.h_mode = IO_FROM_OPENFLAG(oflags);
						result.h_type = HANDLE_TYPE_MFILE;
						result.h_data = incref(open_file);
						TRY {
							mfile_open(open_file, &result, open_path, open_dirent, oflags);
							/* Clear a regular file if O_TRUNC was given. */
							if ((oflags & O_TRUNC) != 0 &&
							    (oflags & O_ACCMODE) != O_RDONLY &&
							    fnode_isreg(open_file))
								mfile_utruncate(open_file, 0);
						} EXCEPT {
							decref(result);
							RETHROW();
						}
						return result;
					} /* if (isvisible) */
				}     /* if (open_file != NULL) */
			}         /* if (lnknode_ops->lno_expandlink != NULL) */

			/* Do normal expansion of symlink nodes. */
			file = path_walklinknode(access_path, premaining_symlinks,
			                         lnknode, &access_path, &access_dent,
			                         (atflags & AT_NO_AUTOMOUNT) | AT_SYMLINK_NOFOLLOW);
			goto again_handle_traversed_file;
		}

		/* Deal with `O_DIRECTORY' */
		if ((oflags & O_DIRECTORY) && !fnode_isdir(file))
			THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_OPEN);

		/* Verify that the caller is allowed to access this file. */
		fnode_access(file, fnode_access_accmode[oflags & O_ACCMODE]);

		/* Initialize result handle. */
		result.h_mode = IO_FROM_OPENFLAG(oflags);
		result.h_type = HANDLE_TYPE_MFILE;
		result.h_data = incref(file);

		/* Invoke custom open operators (and create a `struct filehandle' if necessary). */
		TRY {
			mfile_open(file, &result, access_path, access_dent, oflags);

			/* Clear a regular file if O_TRUNC was given. */
			if ((oflags & O_TRUNC) != 0 &&
			    (oflags & O_ACCMODE) != O_RDONLY &&
			    fnode_isreg(file))
				mfile_utruncate(file, 0);
		} EXCEPT {
			decref(result);
			RETHROW();
		}
	}

	return result;
}


PUBLIC BLOCKING WUNUSED REF struct handle KCALL
path_open(fd_t fd_cwd, USER CHECKED char const *filename,
          oflag_t oflags, mode_t mode) {
	REF struct path *used_cwd;
	u32 remaining_symlinks = ATOMIC_READ(THIS_FS->fs_lnkmax);
	if likely(fd_cwd == AT_FDCWD)
		return path_open_ex(NULL, &remaining_symlinks, filename, oflags, mode);
	used_cwd = handles_lookuppath(fd_cwd);
	FINALLY_DECREF_UNLIKELY(used_cwd);
	return path_open_ex(used_cwd, &remaining_symlinks, filename, oflags, mode);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_PATH_C */
