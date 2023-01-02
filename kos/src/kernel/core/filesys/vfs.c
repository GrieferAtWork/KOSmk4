/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_VFS_C
#define GUARD_KERNEL_CORE_FILESYS_VFS_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirnode.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>
#include <kernel/malloc.h>
#include <sched/task.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/* Destroy the given VFS controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vfs_destroy)(struct vfs *__restrict self) {

	/* Decref DOS drive roots. */
	{
		unsigned int i;
		for (i = 0; i < lengthof(self->vf_drives); ++i)
			xdecref(self->vf_drives[i]);
	}

	/* Decref all paths from the recent cache. */
	{
		REF struct path *iter;
		TAILQ_FOREACH_SAFE (iter, &self->vf_recent, p_recent)
			decref(iter);
	}

	/* Decref all remaining mounting points. */
	{
		REF struct pathmount *iter;
		LIST_FOREACH_SAFE (iter, &self->vf_mounts, pm_vsmount)
			decref(iter);
	}

	/* Decref the root path node. */
	decref_likely(self->vf_root);
	weakdecref_likely(self);
}


/*[[[config CONFIG_KERNEL_VFS_RECENT_MAX_DEFAULT! = 128]]]*/
#ifndef CONFIG_KERNEL_VFS_RECENT_MAX_DEFAULT
#define CONFIG_KERNEL_VFS_RECENT_MAX_DEFAULT 128
#endif /* !CONFIG_KERNEL_VFS_RECENT_MAX_DEFAULT */
/*[[[end]]]*/


/* Default kernel and /bin/init VFS controller. */
PUBLIC struct vfs vfs_kernel = {
	.vf_refcnt     = 2, /* +1: vfs_kernel, +1: fs_kernel.fs_vfs */
	.vf_weakrefcnt = 1,
	.vf_root       = NULL, /* Yes: this shouldn't  be  NULL,  but  this  gets
	                        * initialized when the initial rootfs is mounted. */
	.vf_rootlock   = ATOMIC_RWLOCK_INIT,
	.vf_mounts     = LIST_HEAD_INITIALIZER(vfs_kernel.vf_mounts),
	.vf_mountslock = ATOMIC_LOCK_INIT,
	.vf_recent     = TAILQ_HEAD_INITIALIZER(vfs_kernel.vf_recent),
	.vf_recentcnt  = 0,
	.vf_recentmax  = CONFIG_KERNEL_VFS_RECENT_MAX_DEFAULT,
	.vf_recentlock = ATOMIC_LOCK_INIT,
	.vf_recentlops = SLIST_HEAD_INITIALIZER(vfs_kernel.vf_recentlops),
	.vf_drives     = { NULL, },
	.vf_driveslock = ATOMIC_RWLOCK_INIT,
};


/* (try) to add the given path `self' to the cache of recently used paths.
 * If the  lock to  `path_vfs->vf_recentlock' cannot  be acquired  without
 * blocking, simply do nothing.
 * @return: * : Always re-returns `self'. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct path *
NOTHROW(FCALL vfs_recent)(struct vfs *__restrict path_vfs,
                          struct path *__restrict self) {
	if (!vfs_recentlock_tryacquire(path_vfs))
		goto done;
	assert(_path_getvfs(self) == path_vfs);

	/* If `self' is already apart of the recent-cache, move to the front. */
	if (TAILQ_ISBOUND(self, p_recent)) {
		if (TAILQ_FIRST(&path_vfs->vf_recent) != self) {
			TAILQ_REMOVE(&path_vfs->vf_recent, self, p_recent);
			TAILQ_INSERT_HEAD(&path_vfs->vf_recent, self, p_recent);
		}
	} else {
		/* Check if `self' may even  be added to the  cache.
		 * For this purpose, `MFILE_FN_FLEETING' is  tested,
		 * which is set for per-process folders of /proc  in
		 * order to prevent these folders from being cached. */
		if (self->p_dir->mf_flags & MFILE_FN_FLEETING)
			goto done_unlock;

		/* Add new path to recent cache. */
		incref(self);
		TAILQ_INSERT_HEAD(&path_vfs->vf_recent, self, p_recent);

		/* Check if a parent-path of `self' are already in-cache.
		 * If so, replace that parent with `self'. */
		if (!path_isroot(self)) {
			REF struct path *iter;
			iter = path_getparent(self);
			for (;;) {
				REF struct path *next;
				if (TAILQ_ISBOUND(iter, p_recent)) {
					TAILQ_UNBIND(&path_vfs->vf_recent, iter, p_recent);
					vfs_recentlock_release(path_vfs);
					/* Drop old reference */
					decref_nokill(iter);
					decref(iter);
					goto done;
				}
				if (path_isroot(iter)) {
					decref_unlikely(iter);
					break;
				}
				next = path_getparent(iter);
				decref_unlikely(iter);
				iter = next;
			}
		}

		/* Update # of live recent paths */
		if (path_vfs->vf_recentcnt >= path_vfs->vf_recentmax) {
			/* Must remove the least recently used path from the the cache. */
			REF struct path *oldpath;
			oldpath = TAILQ_LAST(&path_vfs->vf_recent);
			TAILQ_UNBIND(&path_vfs->vf_recent, oldpath, p_recent);
			vfs_recentlock_release(path_vfs);
			/* Drop old reference */
			decref(oldpath);
			goto done;
		} else {
			/* Wholly new element within the recent cache. */
			++path_vfs->vf_recentcnt;
		}
	}
done_unlock:
	vfs_recentlock_release(path_vfs);
done:
	return self;
}



/* Return  a reference to the mounting point that comes after `prev'
 * When `prev == NULL',  return the  first  mount point.  Note  that
 * when `prev' has been unloaded, this function will also return the
 * first (still-registered) mounting point. */
PUBLIC WUNUSED NONNULL((1)) REF struct pathmount *FCALL
vfs_mounts_next(struct vfs *__restrict self,
                struct pathmount *prev)
		THROWS(E_WOULDBLOCK) {
	REF struct pathmount *result;
	assert(!prev || _path_getvfs(prev) == self);
	vfs_mountslock_acquire(self);
	if (prev && LIST_ISBOUND(prev, pm_vsmount)) {
		result = LIST_NEXT(prev, pm_vsmount);
	} else {
		result = LIST_FIRST(&self->vf_mounts);
	}
	xincref(result);
	vfs_mountslock_release(self);
	return result;
}



/* Return the path used to mount the given `dir' within `self'.
 * If the given directory doesn't have a mounting point  within
 * the given VFS `self', return `NULL' */
PUBLIC WUNUSED NONNULL((1, 2)) REF struct pathmount *FCALL
vfs_mount_location(struct vfs *__restrict self,
                   struct fdirnode *__restrict dir)
		THROWS(E_WOULDBLOCK) {
	REF struct pathmount *result;
	vfs_mountslock_acquire(self);
	LIST_FOREACH (result, &self->vf_mounts, pm_vsmount) {
		if (result->p_dir == dir) {
			incref(result);
			break;
		}
	}
	vfs_mountslock_release(self);
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_VFS_C */
