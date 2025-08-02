/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os"); // Optimize this file for size
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_CC_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_CC_C 1
#define __WANT_DRIVER__d_internals
#define __WANT_MPART__mp_dead
#define __WANT_MFILE__mf_deadnod
#define __WANT_PATH__p_dead
#define __WANT_CCINFO__ci_state
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/pty.h>
#include <dev/tty.h>
#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/fifonode.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handman.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/pipe.h>
#include <misc/unlockinfo.h>
#include <sched/enum.h>
#include <sched/epoll.h>
#include <sched/pertask.h>
#include <sched/pid.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sequence/list.h>

#include <kos/except.h>
#include <kos/kernel/handle.h>
#include <kos/types.h>
#include <network/socket.h>

#include <alloca.h>
#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libbuffer/linebuffer.h>
#include <libbuffer/ringbuffer.h>

/**/
#include "module-userelf.h" /* CONFIG_HAVE_KERNEL_USERELF_MODULES */

DECL_BEGIN

typedef ATTR_BLOCKLIKE_CC(info) NONNULL_T((1)) void
NOTHROW_T(KCALL *PSYSTEMCC)(struct ccinfo *__restrict info);

#define DOCC(expr)               \
	do {                         \
		expr;                    \
		if (ccinfo_isdone(info)) \
			return;              \
	}	__WHILE0



/* Cache-clear functions from around the kernel core... */
INTDEF ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_async_aio_handles)(struct ccinfo *__restrict info);
INTDEF ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_module_section_cache)(struct ccinfo *__restrict info);
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
INTDEF ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_rtld_fsfile)(struct ccinfo *__restrict info);
INTDEF ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_mman_module_cache)(struct mman *__restrict self,
                                           struct ccinfo *__restrict info);
#endif /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
INTDEF ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_slab_prealloc)(struct ccinfo *__restrict info);
/*...*/




/************************************************************************/
/* DRIVER                                                               */
/************************************************************************/
INTDEF ATTR_USED NOBLOCK NONNULL((1)) size_t /* from "driver.c" */
NOTHROW(FCALL dfc_freetree)(struct driver_fde_cache *__restrict tree);
PRIVATE ATTR_USED NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_driver_fdecache)(struct driver *__restrict self,
                                         struct ccinfo *__restrict info) {
	struct driver_fde_cache *tree;
	if (!driver_eh_frame_cache_trywrite(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!driver_eh_frame_cache_write_nx(self))
			return;
	}
	tree = self->d_eh_frame_cache;
	self->d_eh_frame_cache = NULL;
	driver_eh_frame_cache_endwrite(self);
	if (tree != NULL)
		ccinfo_account(info, dfc_freetree(tree));
}

/* Clear caches associated with a given driver. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_perdriver)(struct driver *__restrict self,
                                   struct ccinfo *__restrict info) {
	PSYSTEMCC func;
	DOCC(system_cc_driver_fdecache(self, info));

	/* Drivers are allowed to define custom clear-cache functions. */
	*(void **)&func = driver_dlsym_local(self, "drv_cc");
	if (func != NULL)
		DOCC((*func)(info));
}

/* Clear caches defined by drivers. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_drivers)(struct ccinfo *__restrict info) {
	size_t i;
	REF struct driver_loadlist *ll;
	/* Invoke the `drv_cc()' function of every loaded driver. */
	ll = get_driver_loadlist();
	for (i = 0; i < ll->dll_count; ++i) {
		REF struct driver *drv;
		drv = ll->dll_drivers[i];
		if (!tryincref(drv))
			continue; /* Dead driver... */
		system_cc_perdriver(drv, info);
		if (atomic_decfetch(&drv->md_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct driver));
			destroy(drv);
		}
		if (ccinfo_isdone(info))
			break;
	}
	if (atomic_decfetch(&ll->dll_refcnt) == 0) {
		ccinfo_account(info, offsetof(struct driver_loadlist, dll_drivers));
		ccinfo_account(info, ll->dll_count * sizeof(REF struct driver *));
		driver_loadlist_destroy(ll);
	}
}




/************************************************************************/
/* FS                                                                   */
/************************************************************************/

#ifndef __path_slist_defined
#define __path_slist_defined
SLIST_HEAD(path_slist, path);
#endif /* !__path_slist_defined */

/* Invoke cache-clear callbacks for the given mem-file. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_permfile)(struct mfile *__restrict self,
                                  struct ccinfo *__restrict info) {
	struct mfile_stream_ops const *ops;
	ops = self->mf_ops->mo_stream;
	if (ops && ops->mso_cc)
		DOCC((*ops->mso_cc)(self, info));
	if (mfile_isfifo(self)) {
		/* In this case, we can clear  */
		struct ffifonode *me = mfile_asfifo(self);
		DOCC(system_cc_ringbuffer(&me->ff_buffer, info));
	}
	if (mfile_istty(self)) {
		struct ttydev *me = mfile_astty(self);
		DOCC(system_cc_ringbuffer(&me->t_term.t_ibuf, info));
		DOCC(system_cc_linebuffer(&me->t_term.t_canon, info));
		DOCC(system_cc_linebuffer(&me->t_term.t_opend, info));
		DOCC(system_cc_linebuffer(&me->t_term.t_ipend, info));
		if (ttydev_isptyslave(me)) {
			struct ptyslave *ps = ttydev_asptyslave(me);
			DOCC(system_cc_ringbuffer(&ps->ps_obuf, info));
		}
	}
}

/* Rehash with the given list buffer */
INTDEF NOBLOCK NONNULL((1, 2)) void /* From "filesys/path.c" */
NOTHROW(FCALL path_cldlist_rehash_with)(struct path *__restrict self,
                                        struct path_bucket *__restrict new_list,
                                        size_t new_mask);

/* Trim buffer of `self->p_cldlist' */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_path_cldlist)(struct path *__restrict self,
                                      struct ccinfo *__restrict info) {
again:
	if (!path_cldlock_tryread(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!path_cldlock_read_nx(self))
			return;
	}
	if (self->p_cldlist != PATH_CLDLIST_DELETED) {
		if (self->p_cldused == 0) {
			/* Special case: can delete the entire list. */
			struct path_bucket *oldlist;
			oldlist         = self->p_cldlist;
			self->p_cldsize = 0;
			self->p_cldmask = 0;
			self->p_cldlist = path_empty_cldlist;
			path_cldlock_endread(self);
			if (oldlist != path_empty_cldlist) {
				ccinfo_account(info, kmalloc_usable_size(oldlist));
				kfree(oldlist);
			}
			return;
		} else {
			size_t minmask;
			/* Specifications require that `MASK >= USED', and be 2^N-1 */
			minmask = 1;
			while (minmask < self->p_cldused)
				minmask = (minmask << 1) | 1;
			assert(minmask <= self->p_cldmask);
			if (minmask < self->p_cldmask) {
				/* Try to allocate a smaller mask. */
				struct path_bucket *new_list;
				size_t old_usable;
				size_t new_usable;
				new_list = (struct path_bucket *)kmalloc_nx((minmask + 1) *
				                                            sizeof(struct path_bucket),
				                                            ccinfo_gfp(info) |
				                                            GFP_ATOMIC | GFP_CALLOC);
				if (!new_list) {
					path_cldlock_endread(self);
					if (ccinfo_noblock(info))
						return; /* nope... */

					/* Try a blocking allocation. */
					new_list = (struct path_bucket *)kmalloc_nx((minmask + 1) *
					                                            sizeof(struct path_bucket),
					                                            ccinfo_gfp(info) | GFP_CALLOC);
					if (!new_list)
						return; /* nope... */

					/* Re-acquire lock. */
					if (!path_cldlock_read_nx(self)) {
						kfree(new_list);
						return;
					}

					/* Check that `new_list'  is still allowed,  and
					 * is also more efficient that the existing one. */
					if unlikely(self->p_cldlist == PATH_CLDLIST_DELETED ||
					            self->p_cldused > minmask ||
					            self->p_cldmask <= minmask) {
						/* Installing our new list wouldn't make any sense; -> try again. */
						path_cldlock_endread(self);
						kfree(new_list);
						goto again;
					}
				}

				/* Figure out usable space */
				assertf(self->p_cldlist != path_empty_cldlist,
				        "This can't be, because `self->p_cldused != 0'");
				old_usable = kmalloc_usable_size(self->p_cldlist);
				new_usable = kmalloc_usable_size(new_list);

				/* Install the new list. (this also frees the old list) */
				path_cldlist_rehash_with(self, new_list, minmask);
				path_cldlock_endread(self);

				/* Account for freed memory. */
				if (old_usable > new_usable)
					ccinfo_account(info, old_usable - new_usable);
				return;
			}
		}
	}
	path_cldlock_endread(self);
}

PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_perpath_inherit_reference)(REF struct path *__restrict self,
                                                   struct ccinfo *__restrict info) {
again:
	system_cc_path_cldlist(self, info);
	if (ccinfo_isdone(info))
		goto done;
	system_cc_permfile(self->p_dir, info);
	if (ccinfo_isdone(info))
		goto done;

	/* Recursively clear caches of parent paths. */
	if (!path_isroot(self)) {
		REF struct path *parent = path_getparent(self);
		if (atomic_decfetch(&self->p_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct path));
			path_destroy(self);
		}
		self = parent;
		goto again;
	}
done:
	if (atomic_decfetch(&self->p_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct path));
		path_destroy(self);
	}
}

PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_perpath)(struct path *__restrict self,
                                 struct ccinfo *__restrict info) {
	system_cc_perpath_inherit_reference(incref(self), info);
}

/* Clear VFS recently-used-paths cache. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_vfs_recent_paths_unload)(struct vfs *__restrict self,
                                                 struct ccinfo *__restrict info) {
	struct path_slist deadpaths;
	struct path *iter;
	if (!vfs_recentlock_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!vfs_recentlock_acquire_nx(self))
			return;
	}
	SLIST_INIT(&deadpaths);

	/* We only remove paths  that are not externally  referenced.
	 * We could just remove  everything, but doing that  wouldn't
	 * do us any good since we can only report memory having been
	 * freed if we actually managed to destroy a path. */
	TAILQ_FOREACH_SAFE (iter, &self->vf_recent, p_recent) {
		if (!atomic_cmpxch(&iter->p_refcnt, 1, 0))
			continue; /* Remove from the recent cache wouldn't kill this one... */

		/* Remove from the recent cache. */
		assert(self->vf_recentcnt != 0);
		TAILQ_REMOVE(&self->vf_recent, iter, p_recent);
		--self->vf_recentcnt;
		SLIST_INSERT(&deadpaths, iter, _p_dead);
		ccinfo_account(info, sizeof(struct path));
		if (ccinfo_isdone(info))
			break;
	}
	vfs_recentlock_release(self);

	/* Destroy dead path objects. */
	while (!SLIST_EMPTY(&deadpaths)) {
		iter = SLIST_FIRST(&deadpaths);
		SLIST_REMOVE_HEAD(&deadpaths, _p_dead);
		path_destroy(iter);
	}
}

/* Invoke operators for paths in the recently-used-paths cache. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_vfs_recent_paths)(struct vfs *__restrict self,
                                          struct ccinfo *__restrict info) {
	REF struct path *iter;
	REF struct path *prev = NULL;
	size_t index          = 0;
	if (!vfs_recentlock_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!vfs_recentlock_acquire_nx(self))
			return;
	}
	iter = TAILQ_FIRST(&self->vf_recent);
	for (;;) {
		xincref(iter);
		vfs_recentlock_release(self);
		if (prev && atomic_decfetch(&prev->p_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct path));
			path_destroy(prev);
		}
		if (!iter)
			break;
		system_cc_perpath(iter, info);
		if (ccinfo_isdone(info))
			break;
		if (!vfs_recentlock_tryacquire(self)) {
			if (ccinfo_noblock(info))
				break;
			if (!vfs_recentlock_acquire_nx(self))
				break;
		}
		prev = iter;
		if (!TAILQ_ISBOUND(iter, p_recent)) {
			/* Find  the `index'th node in the global list.
			 * This is not failsafe (elements before `node'
			 * may have been removed, so `index' may not be
			 * correct), but it's better than nothing. */
			size_t i;
			iter = TAILQ_FIRST(&self->vf_recent);
			for (i = 0; iter && i < index; ++i) {
				iter = TAILQ_NEXT(iter, p_recent);
			}
			if (!iter) {
				vfs_recentlock_release(self);
				iter = prev;
				break;
			}
		}
		iter = TAILQ_NEXT(iter, p_recent);
		++index;
	}
	if (iter && atomic_decfetch(&iter->p_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct path));
		path_destroy(iter);
	}
}


/* Clear caches relating to mounting point paths. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_vfs_mounts)(struct vfs *__restrict self,
                                    struct ccinfo *__restrict info) {
	REF struct pathmount *iter;
	REF struct pathmount *prev = NULL;
	size_t index               = 0;
	if (!vfs_mountslock_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!vfs_mountslock_acquire_nx(self))
			return;
	}
	iter = LIST_FIRST(&self->vf_mounts);
	for (;;) {
		xincref(iter);
		vfs_mountslock_release(self);
		if (prev && atomic_decfetch(&prev->p_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct path));
			path_destroy(prev);
		}
		if (!iter)
			break;
		system_cc_perpath(iter, info);
		if (ccinfo_isdone(info))
			break;
		if (!vfs_mountslock_tryacquire(self)) {
			if (ccinfo_noblock(info))
				break;
			if (!vfs_mountslock_acquire_nx(self))
				break;
		}
		prev = iter;
		if (!LIST_ISBOUND(iter, pm_vsmount)) {
			/* Find  the `index'th node in the global list.
			 * This is not failsafe (elements before `node'
			 * may have been removed, so `index' may not be
			 * correct), but it's better than nothing. */
			size_t i;
			iter = LIST_FIRST(&self->vf_mounts);
			for (i = 0; iter && i < index; ++i) {
				iter = LIST_NEXT(iter, pm_vsmount);
			}
			if (!iter) {
				vfs_mountslock_release(self);
				iter = prev;
				break;
			}
		}
		iter = LIST_NEXT(iter, pm_vsmount);
		++index;
	}
	if (iter && atomic_decfetch(&iter->p_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct path));
		path_destroy(iter);
	}
}

/* Clear caches relating to DOS drive paths. */
PRIVATE ATTR_NOINLINE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_vfs_drives)(struct vfs *__restrict self,
                                    struct ccinfo *__restrict info) {
	REF struct path *paths[lengthof(self->vf_drives)];
	unsigned int i;
	if (!vfs_driveslock_tryread(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!vfs_driveslock_read_nx(self))
			return;
	}
	for (i = 0; i < lengthof(self->vf_drives); ++i)
		paths[i] = xincref(self->vf_drives[i]);
	vfs_driveslock_endread(self);
	for (i = 0; i < lengthof(self->vf_drives); ++i) {
		if (!paths[i])
			continue;
		system_cc_perpath_inherit_reference(paths[i], info);
		if (ccinfo_isdone(info)) {
			for (; i < lengthof(self->vf_drives); ++i) {
				if (!paths[i])
					continue;
				if (atomic_decfetch(&paths[i]->p_refcnt) == 0) {
					ccinfo_account(info, sizeof(struct path));
					path_destroy(paths[i]);
				}
			}
			break;
		}
	}
}

/* Clear caches relating to the vfs root path. */
PRIVATE ATTR_NOINLINE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_vfs_root)(struct vfs *__restrict self,
                                  struct ccinfo *__restrict info) {
	REF struct path *root;
	if (!vfs_rootlock_tryread(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!vfs_rootlock_read_nx(self))
			return;
	}
	/* Might be NULL if rootfs not yet mounted during early boot... */
	root = xincref(self->vf_root);
	vfs_rootlock_endread(self);
	if likely(root != NULL)
		system_cc_perpath_inherit_reference(root, info);
}

/* Clear per-vfs caches. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_pervfs)(struct vfs *__restrict self,
                                struct ccinfo *__restrict info) {
	DOCC(system_cc_vfs_recent_paths_unload(self, info));
	DOCC(system_cc_vfs_recent_paths(self, info));
	DOCC(system_cc_vfs_mounts(self, info));
	DOCC(system_cc_vfs_drives(self, info));
	DOCC(system_cc_vfs_root(self, info));
}

/* Clear per-fs caches. */
PRIVATE ATTR_NOINLINE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_fs_paths)(struct fs *__restrict self,
                                  struct ccinfo *__restrict info) {
	REF struct path *paths[2 + lengthof(self->fs_dcwd)];
	unsigned int i;
	if (!fs_pathlock_tryread(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!fs_pathlock_read_nx(self))
			return;
	}
	paths[0] = xincref(self->fs_root);
	paths[1] = xincref(self->fs_cwd);
	for (i = 0; i < lengthof(self->fs_dcwd); ++i)
		paths[2 + i] = xincref(self->fs_dcwd[i]);
	fs_pathlock_endread(self);
	for (i = 0; i < lengthof(paths); ++i) {
		if (!paths[i])
			continue;
		system_cc_perpath_inherit_reference(paths[i], info);
		if (ccinfo_isdone(info)) {
			for (; i < lengthof(paths); ++i) {
				if (!paths[i])
					continue;
				if (atomic_decfetch(&paths[i]->p_refcnt) == 0) {
					ccinfo_account(info, sizeof(struct path));
					path_destroy(paths[i]);
				}
			}
			break;
		}
	}
}

PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_perfs)(struct fs *__restrict self,
                               struct ccinfo *__restrict info) {
	DOCC(system_cc_pervfs(self->fs_vfs, info));
	DOCC(system_cc_fs_paths(self, info));
}






/************************************************************************/
/* HANDLES                                                              */
/************************************************************************/

/* Clear buffers associated with a given handle object. */
PUBLIC ATTR_BLOCKLIKE_CC(info) NONNULL((2, 3)) void
NOTHROW(KCALL system_cc_handle)(uintptr_half_t handle_typ,
                                void *__restrict handle_ptr,
                                struct ccinfo *__restrict info) {
	switch (handle_typ) {

	case HANDLE_TYPE_MFILE: {
		struct mfile *me = (struct mfile *)handle_ptr;
		DOCC(system_cc_permfile(me, info));
	}	break;

	case HANDLE_TYPE_PATH: {
		struct path *me = (struct path *)handle_ptr;
		DOCC(system_cc_perpath(me, info));
	}	break;

	case HANDLE_TYPE_FILEHANDLE:
	case HANDLE_TYPE_TEMPHANDLE:
	case HANDLE_TYPE_FIFOHANDLE: {
		struct filehandle *me = (struct filehandle *)handle_ptr;
		DOCC(system_cc_permfile(me->fh_file, info));
		DOCC(system_cc_perpath(me->fh_path, info));
	}	break;

	case HANDLE_TYPE_DIRHANDLE: {
		struct dirhandle *me = (struct dirhandle *)handle_ptr;
		DOCC(system_cc_permfile(me->dh_enum.de_dir, info));
		DOCC(system_cc_perpath(me->dh_path, info));
	}	break;

	case HANDLE_TYPE_SOCKET: {
		struct socket *me = (struct socket *)handle_ptr;
		/* TODO: Clear socket-level buffers */
		(void)me;
	}	break;

	case HANDLE_TYPE_EPOLL: {
		struct epoll_controller *me = (struct epoll_controller *)handle_ptr;
		/* TODO: Truncate `me->ec_list' */
		(void)me;
	}	break;

	case HANDLE_TYPE_PIPE_READER:
	case HANDLE_TYPE_PIPE_WRITER: {
		static_assert(offsetof(struct pipe_reader, pr_pipe) ==
		              offsetof(struct pipe_writer, pw_pipe));
		handle_ptr = ((struct pipe_reader *)handle_ptr)->pr_pipe;
	}	ATTR_FALLTHROUGH
	case HANDLE_TYPE_PIPE: {
		struct pipe *me = (struct pipe *)handle_ptr;
		DOCC(system_cc_ringbuffer(&me->p_buffer, info));
	}	break;

	default:
		break;
	}
}

INTDEF ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void /* From "fd/handman.c" */
NOTHROW(KCALL system_cc_perhman)(struct handman *__restrict self,
                                 struct ccinfo *__restrict info);




/************************************************************************/
/* MMAN                                                                 */
/************************************************************************/
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_mman_execinfo)(struct mman *__restrict self,
                                       struct ccinfo *__restrict info) {
	REF struct mfile *exec_file;
	REF struct path *exec_path;
	struct mexecinfo *ei;
	ei = &FORMMAN(self, thismman_execinfo);
	if (!mman_lock_tryread(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!mman_lock_read_nx(self))
			return;
	}
	exec_file = xincref(ei->mei_file);
	exec_path = xincref(ei->mei_path);
	mman_lock_endread(self);
	if (exec_file) {
		system_cc_permfile(exec_file, info);
		if (atomic_decfetch(&exec_file->mf_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct mfile));
			mfile_destroy(exec_file);
		}
	}
	if (exec_path) {
		if (!ccinfo_isdone(info)) {
			system_cc_perpath_inherit_reference(exec_path, info);
		} else {
			if (atomic_decfetch(&exec_path->p_refcnt) == 0) {
				ccinfo_account(info, sizeof(struct path));
				path_destroy(exec_path);
			}
		}
	}
}

/* Clear per-mman caches. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_permman)(struct mman *__restrict self,
                                 struct ccinfo *__restrict info) {
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
	DOCC(system_cc_mman_module_cache(self, info));
#endif /* CONFIG_HAVE_KERNEL_USERELF_MODULES */

	/* Files relating to exec-info */
	DOCC(system_cc_mman_execinfo(self, info));
}



/************************************************************************/
/* THREAD                                                               */
/************************************************************************/

/* Clear per-thread caches. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_pertask)(struct task *__restrict self,
                                 struct ccinfo *__restrict info) {
	/* Clear per-mman caches. */
	{
		REF struct mman *threadmm;
		threadmm = task_getmman(self);
		system_cc_permman(threadmm, info);
		if (atomic_decfetch(&threadmm->mm_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct mman));
			mman_destroy(threadmm);
		}
	}
	if (ccinfo_isdone(info))
		return;

	/* Clear per-fs caches. */
	if (atomic_read(&FORTASK(self, this_fs)) != NULL) { /* Should never be NULL (but lets be safe) */
		REF struct fs *threadfs;
		threadfs = task_getfs(self);
		system_cc_perfs(threadfs, info);
		if (atomic_decfetch(&threadfs->fs_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct fs));
			fs_destroy(threadfs);
		}
	}
	if (ccinfo_isdone(info))
		return;

	/* Clear per-handle-manager caches. */
	if (atomic_read(&FORTASK(self, this_handman)) != NULL) { /* Should never be NULL (but lets be safe) */
		REF struct handman *threadhm;
		threadhm = task_gethandman(self);
		system_cc_perhman(threadhm, info);
		if (atomic_decfetch(&threadhm->hm_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct handman));
			handman_destroy(threadhm);
		}
	}
	if (ccinfo_isdone(info))
		return;

	/* TODO: There are probably more per-task things we could try doing. */
}

PRIVATE NOBLOCK NONNULL((1, 2)) ssize_t
NOTHROW(TASK_ENUM_CC system_cc_pertask_cb)(void *arg, struct task *__restrict thread) {
	struct ccinfo *info = (struct ccinfo *)arg;
	system_cc_pertask(thread, info);
	if (ccinfo_isdone(info))
		return -1; /* Stop enumeration */
	return 0;
}


PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_root_pidtree)(struct taskpid *__restrict pid,
                                      struct ccinfo *__restrict info) {
	REF struct task *thread;
again:
	thread = taskpid_gettask(pid);
	if likely(thread) {
		system_cc_pertask(thread, info);
		if (atomic_decfetch(&thread->t_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct task)); /* ... */
			task_destroy(thread);
		}
		if (ccinfo_isdone(info))
			return;
	}
	if (pid->tp_pids[0].tps_link.rb_lhs) {
		if (pid->tp_pids[0].tps_link.rb_rhs) {
			system_cc_root_pidtree(pid->tp_pids[0].tps_link.rb_rhs, info);
			if (ccinfo_isdone(info))
				return;
		}
		pid = pid->tp_pids[0].tps_link.rb_lhs;
		goto again;
	}
	if (pid->tp_pids[0].tps_link.rb_rhs) {
		pid = pid->tp_pids[0].tps_link.rb_rhs;
		goto again;
	}
}


/* Gather up to `count' threads starting at `*p_minpid', which is
 * updated to 1+ the last PID enumerated. The return value is the
 * number  of threads stored in `buf'. -- When less than `count',
 * that means that all threads were enumerated. */
PRIVATE NOBLOCK NONNULL((1, 3, 4)) size_t
NOTHROW(KCALL pidns_root_gather_threads)(REF struct task **buf, size_t count,
                                         pid_t *__restrict p_minpid,
                                         struct ccinfo *__restrict info) {
	size_t result = 0;
	pid_t minpid  = *p_minpid;
	while (result < count && minpid >= 0) {
		REF struct taskpid *npid;
		REF struct task *thread;
		npid = pidns_lookupnext_locked(&pidns_root, minpid);
		if (!npid)
			break; /* Done enumerating */
		if (OVERFLOW_SADD(npid->tp_pids[0].tps_pid, 1, &minpid))
			minpid = -1;
		thread = taskpid_gettask(npid);
		if (atomic_decfetch(&npid->tp_refcnt) == 0) {
			ccinfo_account(info, _taskpid_sizeof(npid->tp_ns));
			taskpid_destroy(npid);
		}
		/* Append the associated thread (if still alive) to the result list. */
		if (thread != NULL)
			buf[result++] = thread; /* Inherit reference */
	}
	*p_minpid = minpid;
	return result;
}

/* NOTE: This function inherits a lock to `pidns_root'
 * NOTE: This function assumes `!ccinfo_noblock(info)' */
PRIVATE ATTR_NOINLINE NONNULL((1)) bool
NOTHROW(KCALL system_cc_root_pidns_chunkwise)(struct ccinfo *__restrict info) {
	pid_t minpid = 0;
	size_t i, chunksize, count;
	REF struct task **chunkbase;
	/* Figure out how large we want the chunk to be. */
	chunksize = get_stack_avail() / (2 * sizeof(REF struct task *));

	/* No need to make the chunk larger than the # of threads in the root namespace. */
	if (chunksize > pidns_root.pn_size)
		chunksize = pidns_root.pn_size;

	/* Also apply some more limits for sanity. */
	if (chunksize > 4096)
		chunksize = 4096;
	if (chunksize < 4)
		chunksize = 4;

	/* Allocate our chunk buffer (on the stack) */
	chunkbase = (REF struct task **)alloca(chunksize * sizeof(REF struct task *));

	/* Gather threads from the root namespace. */
again_gather:
	count = pidns_root_gather_threads(chunkbase, chunksize, &minpid, info);
	pidns_endread(&pidns_root);

	/* Work through the list of gathered threads. */
	for (i = 0; i < count; ++i) {
		REF struct task *thread = chunkbase[i];
		if (!ccinfo_isdone(info))
			system_cc_pertask(thread, info);
		if (atomic_decfetch(&thread->t_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct task)); /* ... */
			task_destroy(thread);
		}
	}

	/* Gather more threads if that's what we should do. */
	if (count >= chunksize && !ccinfo_isdone(info)) {
		if (!pidns_read_nx(&pidns_root))
			return false;
		goto again_gather;
	}
	return true;
}

/* Enumerate threads and call `system_cc_pertask()'. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_threads)(struct ccinfo *__restrict info) {
	if (pidns_tryread(&pidns_root)) {
		/* Enumerate threads via the root PID namespace. */
do_enum_root_pidns:
		if (ccinfo_noblock(info)) {
			/* Do the enumeration whilst keeping a lock to the PID namespace. */
			if likely(pidns_root.pn_tree != NULL)
				system_cc_root_pidtree(pidns_root.pn_tree, info);
			pidns_endread(&pidns_root);
		} else {
			/* Enumerate by PID to collect threads in batches, which are then
			 * processed before resuming executing with the next greater PID. */
			if (!system_cc_root_pidns_chunkwise(info))
				goto do_enum_nonblocking;
		}
	} else if (ccinfo_noblock(info)) {
		/* Not allowed to block -> can enumerate threads using the non-blocking method. */
do_enum_nonblocking:
		system_enum_threads_nb(&system_cc_pertask_cb, info);
	} else {
		gfp_t saved_gfp;

		/* Try to do a blocking-wait for the root PID namespace. */
		if (pidns_read_nx(&pidns_root))
			goto do_enum_root_pidns;

		/* Force a non-blocking thread enumeration */
		saved_gfp = info->ci_gfp;
		info->ci_gfp |= GFP_ATOMIC;
		system_enum_threads_nb(&system_cc_pertask_cb, info);
		info->ci_gfp = saved_gfp;
	}
}




/************************************************************************/
/* HEAP                                                                 */
/************************************************************************/

/* Trim the given heap. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_heap)(struct heap *__restrict self,
                              struct ccinfo *__restrict info) {
	ccinfo_account(info, heap_trim(self, 0, ccinfo_gfp(info)));
}

#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
INTDEF ATTR_WEAK struct heap trace_heap;
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */


/* Trim system heaps. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_heaps)(struct ccinfo *__restrict info) {
	size_t i;
	for (i = 0; i < __GFP_HEAPCOUNT; ++i)
		DOCC(system_cc_heap(&kernel_heaps[i], info));
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
	if (&trace_heap != NULL)
		DOCC(system_cc_heap(&trace_heap, info));
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
}




/************************************************************************/
/* FILE/FILESYSTEM CACHES (including preloaded file data!)              */
/************************************************************************/

PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL ccinfo_account_mpart)(struct ccinfo *__restrict info,
                                    struct mpart *__restrict part) {
	/* TODO: Account for physical/swap space owned by `part' */
	(void)part;
	ccinfo_account(info, sizeof(struct mpart));
}

/* Clear unreferenced (cached) mem-parts from the global part list. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_allparts_unload_unused)(struct ccinfo *__restrict info) {
	struct mpart *iter;
	struct mpart_slist deadlist;
	SLIST_INIT(&deadlist);
again:
	if (!mpart_all_tryacquire()) {
		if (ccinfo_noblock(info))
			goto done;
		if (!mpart_all_acquire_nx())
			goto done;
	}

	/* Enumerate all mem-parts. */
	TAILQ_FOREACH_SAFE (iter, &mpart_all_list, mp_allparts) {
		if (!(iter->mp_flags & MPART_F_GLOBAL_REF))
			continue; /* Can't be decref'd */
		if (atomic_read(&iter->mp_refcnt) != 1)
			continue; /* External references exist, or already destroyed. */

		/* Try to unload this mem-part. */
		if (!mpart_lock_tryacquire(iter)) {
			bool waitfor_ok;
			if (ccinfo_noblock(info))
				continue;
			if (!tryincref(iter))
				continue;
			mpart_all_release();
			waitfor_ok = mpart_lock_waitfor_nx(iter);
			if (atomic_decfetch(&iter->mp_refcnt) == 0) {
				ccinfo_account_mpart(info, iter);
				SLIST_INSERT(&deadlist, iter, _mp_dead);
			}
			if (!waitfor_ok)
				goto done;
			if (ccinfo_isdone(info))
				goto done;
			goto again;
		}

		/* Only unload parts of non-persistent files. */
		if (iter->mp_file->mf_flags & MFILE_F_PERSISTENT)
			goto part_not_unloaded;

		if (!(atomic_fetchand(&iter->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)) /* Inherit reference */
			goto part_not_unloaded;
		if (!atomic_cmpxch(&iter->mp_refcnt, 1, 0)) {
			if (!(atomic_fetchor(&iter->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)) /* Inherit reference */
				goto part_not_unloaded;
			/* Someone else set the GLOBAL_REF bit in the mean time?
			 * Anyways: since they did, they're would have had to incref() the part
			 *          to do so, so we have to decref() it since we were unable to
			 *          have the part re-inherit its original global reference. */
			if (atomic_decfetch(&iter->mp_refcnt) != 0)
				goto part_not_unloaded;
		}

		/* Part got destroyed! */
		assert(!(atomic_read(&iter->mp_flags) & MPART_F_GLOBAL_REF));
		SLIST_INSERT(&deadlist, iter, _mp_dead);
		ccinfo_account_mpart(info, iter);
		if (ccinfo_isdone(info))
			break;
		continue;
part_not_unloaded:
		mpart_lock_release(iter);
	}

	mpart_all_release();

	/* Properly destroy any dead mem-parts. */
done:
	while (!SLIST_EMPTY(&deadlist)) {
		iter = SLIST_FIRST(&deadlist);
		SLIST_REMOVE_HEAD(&deadlist, _mp_dead);
		mpart_destroy(iter);
	}
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL unlock_mpart_all)(struct unlockinfo *__restrict self) {
	(void)self;
	mpart_all_release();
}

/* Trim unmapped parts of (cached) mem-parts from the global part list. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_allparts_trim_unused)(struct ccinfo *__restrict info,
                                              unsigned int trim_mode) {
#if !defined(NDEBUG) && 0
#define LOCAL_kmalloc_leaks(...) (ccinfo_noblock(info) ? (void)0 : assertf(!kmalloc_leaks(), __VA_ARGS__))
#else
#define LOCAL_kmalloc_leaks(...) (void)0
#endif
	bool did_clear_trimmed = false;
	struct mpart *iter;
	struct mpart_slist deadlist;
	struct unlockinfo unlock;
	struct mpart_trim_data data;
	SLIST_INIT(&deadlist);
	unlock.ui_unlock = &unlock_mpart_all;
	mpart_trim_data_init(&data, info, &unlock, NULL, trim_mode);
	LOCAL_kmalloc_leaks(NULL);
again:
	if (!mpart_all_tryacquire()) {
		if (ccinfo_noblock(info))
			goto done;
		if (!mpart_all_acquire_nx())
			goto done;
	}

	if (!did_clear_trimmed) {
		TAILQ_FOREACH (iter, &mpart_all_list, mp_allparts)
			atomic_and(&iter->mp_flags, ~MPART_F__TRIMMED);
		did_clear_trimmed = true;
	}

	/* Enumerate all mem-parts. */
	TAILQ_FOREACH_SAFE (iter, &mpart_all_list, mp_allparts) {
		unsigned int error;

		/* Check if we already trimmed this part. */
		if (atomic_read(&iter->mp_flags) & MPART_F__TRIMMED)
			continue;

		/* Make sure that the part is still alive. */
		if (!tryincref(iter))
			continue;

		/* Do the actual job of trying to trim the mem-part. */
		error = mpart_trim_or_unlock_nx(iter, &data);
		if (atomic_decfetch(&iter->mp_refcnt) == 0) {
			ccinfo_account_mpart(info, iter);
			SLIST_INSERT(&deadlist, iter, _mp_dead);
		}
		if (error == MPART_NXOP_ST_RETRY) {
			LOCAL_kmalloc_leaks("iter = %p", iter);
			goto again; /* Locks were released for temporary error -> start over */
		}
		if (error == MPART_NXOP_ST_ERROR) {
			LOCAL_kmalloc_leaks("iter = %p", iter);
			goto done; /* Locks were released for hard error -> stop trying to do stuff */
		}
		assert(error == MPART_NXOP_ST_SUCCESS);
		if (ccinfo_isdone(info))
			break;
		atomic_or(&iter->mp_flags, MPART_F__TRIMMED);
	}
	mpart_all_release();
	LOCAL_kmalloc_leaks(NULL);
done:
	mpart_trim_data_fini(&data);

	/* Properly destroy any dead mem-parts. */
	while (!SLIST_EMPTY(&deadlist)) {
		iter = SLIST_FIRST(&deadlist);
		SLIST_REMOVE_HEAD(&deadlist, _mp_dead);
		mpart_destroy(iter);
	}
#undef LOCAL_kmalloc_leaks
}


#ifndef __fnode_slist_defined
#define __fnode_slist_defined
SLIST_HEAD(fnode_slist, fnode);
#endif /* !__fnode_slist_defined */

/* Clear unreferenced (cached) files nodes from the global file-node-list. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_allnodes_unload_unused)(struct ccinfo *__restrict info) {
	struct fnode *iter;
	struct fnode_slist deadlist;
	SLIST_INIT(&deadlist);
again:
	if (!fallnodes_tryacquire()) {
		if (ccinfo_noblock(info))
			goto done;
		if (!fallnodes_acquire_nx())
			goto done;
	}

	/* Enumerate all file nodes. */
	/* TODO: Would be better to enumerate from least-recent to most-recent
	 *       Though for this, we should probably chance the list type from
	 *       `LIST_*' to `TAILQ_*' (which has a O(1) *_LAST operation). */
	LIST_FOREACH_SAFE (iter, &fallnodes_list, fn_allnodes) {
		if ((iter->mf_flags & (MFILE_FN_GLOBAL_REF | MFILE_F_PERSISTENT)) != MFILE_FN_GLOBAL_REF)
			goto nextnode; /* Can't be unloaded via decref */
		if (atomic_read(&iter->mf_refcnt) != 1)
			goto nextnode; /* External references exist, or already destroyed. */

		/* Try to unload this file. */
		if (!mfile_lock_trywrite(iter)) {
			bool waitfor_ok;
			if (!tryincref(iter))
				goto nextnode;
			mpart_all_release();
			waitfor_ok = mfile_lock_waitwrite_nx(iter);
			if (atomic_decfetch(&iter->mf_refcnt) == 0) {
				ccinfo_account(info, sizeof(struct mfile));
				SLIST_INSERT(&deadlist, iter, _mf_deadnod);
			}
			if (!waitfor_ok)
				goto done;
			if (ccinfo_isdone(info))
				goto done;
			goto again;
		}
		mfile_tslock_acquire(iter);
		if (!(atomic_fetchand(&iter->mf_flags, ~MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)) { /* inherit reference */
			mfile_tslock_release_br(iter);
			mfile_lock_endwrite(iter);
			goto nextnode;
		}
		if (!atomic_cmpxch(&iter->mf_refcnt, 1, 0)) {
			if (!(atomic_fetchor(&iter->mf_flags, MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)) { /* inherit reference */
				mfile_tslock_release_br(iter);
				mfile_lock_endwrite(iter);
				goto nextnode;
			}
			if (atomic_decfetch(&iter->mf_refcnt) != 0) {
				mfile_tslock_release_br(iter);
				mfile_lock_endwrite(iter);
				goto nextnode;
			}
		}

		/* Yes: must destroy this file. */
		mfile_tslock_release_pronly(iter);
		SLIST_INSERT(&deadlist, iter, _mf_deadnod);
		ccinfo_account(info, sizeof(struct mfile));
		if (ccinfo_isdone(info))
			break;
nextnode:
		;
	}
	fallnodes_release();

	/* Properly destroy any dead files. */
done:
	while (!SLIST_EMPTY(&deadlist)) {
		iter = SLIST_FIRST(&deadlist);
		SLIST_REMOVE_HEAD(&deadlist, _mf_deadnod);
		mfile_destroy(iter);
	}
}


/* Free unused space from `self'. */
PUBLIC ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_ringbuffer)(struct ringbuffer *__restrict self,
                                    struct ccinfo *__restrict info) {
	if (!ringbuffer_lock_trywrite(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!ringbuffer_lock_write_nx(self))
			return;
	}
	if (self->rb_avail < self->rb_size) {
		if (self->rb_avail != 0) {
			heapptr_t newbuf;
			/* If necessary, defragment the buffer. */
			if (self->rb_rptr) {
				do {
					/* Shift buffer space so that all  data is stored at the  start,
					 * which in turn will allow us to realloc the buffer as a whole. */
					byte_t temp;
					temp = self->rb_data[0];
					memmovedown(self->rb_data,
					            self->rb_data + 1,
					            self->rb_size - 1);
					self->rb_data[self->rb_size - 1] = temp;
					--self->rb_rptr;
				} while (self->rb_rptr);
			}
			self->rb_rdtot = 0;

			/* Resize the buffer. */
			newbuf = heap_realloc_nx(&kernel_default_heap,
			                          self->rb_data,
			                          self->rb_size,
			                          self->rb_avail,
			                          GFP_ATOMIC | ccinfo_gfp(info),
			                          GFP_NORMAL);
			if likely(heapptr_getsiz(newbuf) != 0) {
				assert(heapptr_getsiz(newbuf) >= self->rb_avail);
				if (self->rb_size > heapptr_getsiz(newbuf))
					ccinfo_account(info, self->rb_size - heapptr_getsiz(newbuf));
				self->rb_data = (byte_t *)heapptr_getptr(newbuf);
				self->rb_size = heapptr_getsiz(newbuf);
			}
		} else /*if (self->rb_size != 0)*/ {
			byte_t *buf_data;
			size_t buf_size;
			/* Free an unused buffer */
			buf_data       = self->rb_data;
			buf_size       = self->rb_size;
			self->rb_data  = NULL;
			self->rb_size  = 0;
			self->rb_rptr  = 0;
			self->rb_rdtot = 0;
			ringbuffer_lock_endwrite(self);

			/* free the buffer as a whole. */
			heap_free(&kernel_default_heap, buf_data, buf_size, GFP_NORMAL);
			ccinfo_account(info, buf_size);
			return;
		}
	}
	ringbuffer_lock_endwrite(self);
}

/* Free unused space from `self'. */
PUBLIC ATTR_BLOCKLIKE_CC(info) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_linebuffer)(struct linebuffer *__restrict self,
                                    struct ccinfo *__restrict info) {
	if (!linebuffer_lock_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!linebuffer_lock_acquire_nx(self))
			return;
	}
	if (self->lb_line.lc_size == 0) {
		struct linecapture oldline;
		oldline                = self->lb_line;
		self->lb_line.lc_base  = NULL;
		self->lb_line.lc_alloc = 0;
		linebuffer_lock_release(self);
		if (oldline.lc_alloc != 0) {
			ccinfo_account(info, oldline.lc_alloc);
			linecapture_fini(&oldline);
		}
		return;
	} else if (self->lb_line.lc_size < self->lb_line.lc_alloc) {
		heapptr_t newline;
		/* Truncate buffer. */
		newline = heap_realloc_nx(&kernel_default_heap,
		                          self->lb_line.lc_base,
		                          self->lb_line.lc_alloc,
		                          self->lb_line.lc_size,
		                          GFP_ATOMIC | ccinfo_gfp(info),
		                          GFP_NORMAL);
		if (heapptr_getsiz(newline) != 0) {
			if (self->lb_line.lc_alloc > heapptr_getsiz(newline))
				ccinfo_account(info, self->lb_line.lc_alloc - heapptr_getsiz(newline));
			self->lb_line.lc_base  = (byte_t *)heapptr_getptr(newline);
			self->lb_line.lc_alloc = heapptr_getsiz(newline);
		}
	}
	linebuffer_lock_release(self);
}


/* Invoke cache-clear callbacks for all file-nodes. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_allnodes)(struct ccinfo *__restrict info) {
	REF struct fnode *node;
	REF struct fnode *prev = NULL;
	size_t index           = 0;
	if (!fallnodes_tryacquire()) {
		if (ccinfo_noblock(info))
			return;
		if (!fallnodes_acquire_nx())
			return;
	}
	node = LIST_FIRST(&fallnodes_list);
	for (;;) {
		while (node && !tryincref(node))
			node = LIST_NEXT(node, fn_allnodes);
		fallnodes_release();
		if (prev && atomic_decfetch(&prev->mf_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct fnode));
			mfile_destroy(prev);
		}
		if (!node)
			break;
		system_cc_permfile(node, info);
		if (ccinfo_isdone(info))
			break;
		if (!fallnodes_tryacquire()) {
			if (ccinfo_noblock(info))
				break;
			if (!fallnodes_acquire_nx())
				break;
		}
		prev = node;
		if (!LIST_ISBOUND(node, fn_allnodes)) {
			/* Find  the `index'th node in the global list.
			 * This is not failsafe (elements before `node'
			 * may have been removed, so `index' may not be
			 * correct), but it's better than nothing. */
			size_t i;
			node = LIST_FIRST(&fallnodes_list);
			for (i = 0; node && i < index; ++i) {
				node = LIST_NEXT(node, fn_allnodes);
			}
			if (!node) {
				fallnodes_release();
				node = prev;
				break;
			}
		}
		node = LIST_NEXT(node, fn_allnodes);
		++index;
	}
	if (node && atomic_decfetch(&node->mf_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct fnode));
		mfile_destroy(node);
	}
}


/* Invoke cache-clear callbacks for all superblocks. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_allsuper)(struct ccinfo *__restrict info) {
	REF struct fsuper *super;
	REF struct fsuper *prev = NULL;
	size_t index            = 0;
	if (!fallsuper_tryacquire()) {
		if (ccinfo_noblock(info))
			return;
		if (!fallsuper_acquire_nx())
			return;
	}
	super = LIST_FIRST(&fallsuper_list);
	for (;;) {
		while (super && !tryincref(super))
			super = LIST_NEXT(super, fs_root.fn_allsuper);
		fallsuper_release();
		if (prev && atomic_decfetch(&prev->fs_root.mf_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct fsuper));
			mfile_destroy(&prev->fs_root);
		}
		if (!super)
			break;
		system_cc_permfile(&super->fs_root, info);
		if (ccinfo_isdone(info))
			break;
		if (!fallsuper_tryacquire()) {
			if (ccinfo_noblock(info))
				break;
			if (!fallsuper_acquire_nx())
				break;
		}
		prev = super;
		if (!LIST_ISBOUND(super, fs_root.fn_allsuper)) {
			/* Find  the `index'th super in the global list.
			 * This is not failsafe (elements before `super'
			 * may have been removed, so `index' may not  be
			 * correct), but it's better than nothing. */
			size_t i;
			super = LIST_FIRST(&fallsuper_list);
			for (i = 0; super && i < index; ++i) {
				super = LIST_NEXT(super, fs_root.fn_allsuper);
			}
			if (!super) {
				fallsuper_release();
				super = prev;
				break;
			}
		}
		super = LIST_NEXT(super, fs_root.fn_allsuper);
		++index;
	}
	if (super && atomic_decfetch(&super->fs_root.mf_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct fsuper));
		mfile_destroy(&super->fs_root);
	}
}





/* Clear all system caches according to `info'. */
PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(FCALL system_cc_impl)(struct ccinfo *__restrict info) {
	DOCC(system_cc_drivers(info));                                             /* Invoke clear-cache operators from drivers */
	DOCC(system_cc_threads(info));                                             /* Clear caches relating to per-thread fields */
	DOCC(system_cc_async_aio_handles(info));                                   /* ... */
	DOCC(system_cc_allparts_unload_unused(info));                              /* Unload cached, but unused mem-parts */
	DOCC(system_cc_allparts_trim_unused(info, MPART_TRIM_MODE_UNMAPPED));      /* Unload cached, but unused blocks of mem-parts */
	DOCC(system_cc_allparts_trim_unused(info, MPART_TRIM_MODE_UNINITIALIZED)); /* Unload allocated, but uninitialized blocks of mem-parts */
	DOCC(system_cc_allnodes_unload_unused(info));                              /* Unload cached, but unused files */
	DOCC(system_cc_allnodes(info));                                            /* Invoke the clear-cache operator for all files */
	DOCC(system_cc_allsuper(info));                                            /* Invoke the clear-cache operator for all superblocks */
	DOCC(system_cc_permman(&mman_kernel, info));                               /* In case more can be done now... */
	DOCC(system_cc_perfs(&fs_kernel, info));                                   /* In case not done already... */
	DOCC(system_cc_module_section_cache(info));                                /* Clear pre-loaded module sections (e.g. .debug_info, etc...) */
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
	DOCC(system_cc_rtld_fsfile(info));
#endif /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
	DOCC(system_cc_slab_prealloc(info));
	DOCC(system_cc_heaps(info));

	/* TODO: It'd be better to re-attempt the caller's failing operation
	 *       after  every step (i.e. from within `ccinfo_isdone()'), and
	 *       also to gradually do more  and more the more attempts  have
	 *       already elapsed (rather than  doing almost nothing for  the
	 *       first half  of  attempts,  and then  *everything*  for  the
	 *       second half)
	 * However, re-attempting the caller's operation must be done in a
	 * context  where the attempt never tries to block, since doing so
	 * would dead-lock (or there must be 2 ways of doing the  attempt,
	 * where one is allowed to block, and the other isn't; this  would
	 * probably be the best way to do it too, since it would make this
	 * retry system safe based on `info->ci_gfp') */

	/* Unload initialized, but unchanged blocks of non-anonymous mem-parts */
	DOCC(system_cc_allparts_trim_unused(info, MPART_TRIM_MODE_UNCHANGED));

	/* Only do stuff that causes writes to disk when `GFP_NOSWAP' isn't set. */
	if (!(info->ci_gfp & GFP_NOSWAP)) {
		/* Write all modified blocks of non-anonymous mem-parts to disk */
		DOCC(system_cc_allparts_trim_unused(info, MPART_TRIM_MODE_UNCHANGED |
		                                          MPART_TRIM_FLAG_SYNC));

		/* Write all modified blocks of non-anonymous mem-parts to disk,
		 * and all  modified  blocks  of anonymous  mem-parts  to  swap. */
		DOCC(system_cc_allparts_trim_unused(info, MPART_TRIM_MODE_UNCHANGED |
		                                          MPART_TRIM_FLAG_SYNC |
		                                          MPART_TRIM_FLAG_SWAP));
	}

	/* TODO: There a couple more things we can do to free up physical memory:
	 *  - We can  also do  `pagedir_unmap_userspace()' for  every user-space  mman
	 *    out there, and let mappings re-populate themselves upon the next access.
	 *    - However, this should only be done as a last resort, since if the free'd
	 *      memory then gets  allocated again, *all*  user-space programs are  just
	 *      going to crash because they'd be unable to restore their mappings.
	 *    - Also: /bin/init should be exempt from this, since it crashing would
	 *      just cause the kernel to panic anyways.
	 */

	/* Reap system heaps one more time. */
	DOCC(system_cc_slab_prealloc(info));
	DOCC(system_cc_heaps(info));
}


PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(FCALL system_cc_impl_wrapper)(struct ccinfo *__restrict info) {
#if 0
	if (ccinfo_noblock(info)) {
		system_cc_impl(info);
	} else
#endif
	{
		/* Allow for exception nesting inside of `system_cc()' */
		NESTED_EXCEPTION;

		/* Preserve task connections (technically only necessary when not noblock,
		 * but  better be safe and always do this, so cc-code is allowed to assume
		 * that the hosting thread doesn't have any connections) */
		struct taskcons saved;
		task_pushcons(&saved);

		/* Call the actual cc-implementation */
		system_cc_impl(info);

		/* Context restore... */
		assert(!task_isconnected());
		task_popcons();
	}
}




/************************************************************************/
/* High-level wrappers                                                  */
/************************************************************************/

/* [lock(ATOMIC)][const_if(cc_inside == 0)]
 * Current system cache version. */
PRIVATE unsigned int cc_version = 0;

/* [lock(ATOMIC)] # of threads currently clearing caches. */
PRIVATE uintptr_t cc_inside = 0;

/* Max # of attempts before unconditional give-up. ("/proc/kos/cc-max-attempts")
 *
 * This  limit is needed in order to prevent infinite loops due to a piece of code
 * that  tries (and fails) to allocate a large amount of memory, but before it can
 * do that, it succeeds in allocating a  small amount of memory that somehow  ends
 * up in some sort of cache (a great example is the unwind-cache of drivers, which
 * is used by trace-malloc, which in turn is used every time you do `kmalloc()') */
PUBLIC ATTR_READMOSTLY uint16_t system_cc_maxattempts = 64;


/* Clear global system caches.
 * @param: info: [in|out] Specification on how caches should be cleared.
 * @return: true:  At least something (may) have become available
 *                 since the last time you tried to clear caches.
 * @return: false: Nothing could be cleared :( */
PUBLIC ATTR_BLOCKLIKE_CC(info) NONNULL((1)) bool
NOTHROW(FCALL system_cc)(struct ccinfo *__restrict info) {
	struct task *caller = THIS_TASK;
	uint16_t version;
	uintptr_t inside;

	/* Check if we're allowed to clear system caches.
	 * -> If not, then immediatly return `false'. */
	if unlikely(info->ci_gfp & GFP_NOCLRC)
		return false;

	/* Set the number of  accounted bytes to `0'  (this
	 * gets increased as we clear more and more caches) */
	info->ci_bytes = 0;

	/* Always set these flags when doing system-cache-clear operations:
	 * - GFP_NOCLRC: Lower the chance of recursive calls to `system_cc'
	 * - GFP_NOTRIM: We manually trim kernel heaps near the end of cc,
	 *               so by trying not to do so automatically over  the
	 *               course of other cc operations, our final count of
	 *               cleared bytes will be more accurate. */
	info->ci_gfp |= GFP_NOCLRC | GFP_NOTRIM;

	/* Mask invalid bits (and bits that wouldn't make sense, like `GFP_LOCKED' or `GFP_CALLOC') */
	info->ci_gfp &= GFP_PREFLT | GFP_NOCLRC | GFP_NOMMAP |
	                GFP_NOTRIM | GFP_ATOMIC | GFP_NOOVER |
	                GFP_NOSWAP | GFP_MCHEAP | GFP_BLOCKING;

	/* Safety-check: if preemption is disabled right now,
	 * then  we can *only*  operate in non-blocking mode. */
	if (!preemption_ison()) {
		info->ci_gfp &= ~GFP_BLOCKING;
		info->ci_gfp |= GFP_ATOMIC;
	}

	/* Safety-check: prevent recursion in case a call to `system_cc()'
	 *               is already in progress within the calling thread. */
	if (caller->t_flags & _TASK_FSYSTEMCC)
		return false;

	/* Check if we're supposed to give up */
	if (info->ci_attempt == (uint16_t)-1) {
		/* Special indicator for infinite attempts. */

		/* If not specified, try to free as much memory as possible */
		if (info->ci_minbytes == 0)
			info->ci_minbytes = (size_t)-1;
	} else {
		uint16_t maxattempts = system_cc_maxattempts;
		if (info->ci_attempt >= maxattempts)
			return false; /* D:  -- Oh no! */
		++info->ci_attempt;

		/* If  not specified, for the first half of our attempts, we
		 * try to free at least 1  byte each iteration, but for  the
		 * second half of attempts, we try to free as much as we can
		 * possibly free. */
		if (info->ci_minbytes == 0) {
			/* Once we're past half the allowed number of  attempts,
			 * be a little more aggressive with how we clear caches. */
			if (info->ci_attempt >= (maxattempts >> 1)) {
				info->ci_minbytes = (size_t)-1;
			} else {
				info->ci_minbytes = 1;
			}
		}
	}

	/* Start out by trying to clear system caches ourselves. */
	atomic_inc(&cc_inside);

	/* Keep the `_TASK_FSYSTEMCC' flag set whilst actually doing cc operations */
	atomic_or(&caller->t_flags, _TASK_FSYSTEMCC);
	system_cc_impl_wrapper(info);
	atomic_and(&caller->t_flags, ~_TASK_FSYSTEMCC);

	/* Check if we already managed to release some memory */
	if (info->ci_bytes != 0) {
		/* Since something  was cleared,  indicate
		 * that by incrementing the cache version. */
		info->ci_version = atomic_fetchinc(&cc_version);
		atomic_dec(&cc_inside);
		return true;
	}
	version = atomic_read(&cc_version);
	inside  = atomic_decfetch(&cc_inside);

	/* If other threads are clearing caches, we try to yield to them. */
	if (inside != 0) {
		unsigned int n;
		for (n = 0; n < 256; ++n) {
			unsigned int yield_error;
			yield_error = task_tryyield_or_pause();
			if (atomic_read(&cc_inside) < inside)
				break;
			if (yield_error != TASK_TRYYIELD_SUCCESS)
				break; /* Cannot yield... */
		}
		return true;
	}

	/* Fix zero-version (which is used to indicate the first cc-attempt) */
	if (version == 0) {
		atomic_inc(&cc_inside);
		version = atomic_incfetch(&cc_version);
		atomic_dec(&cc_inside);
	}

	/* If the cache version changed since the
	 * last clear-attempt, indicate  success. */
	if (info->ci_version != version) {
		info->ci_version = version;
		return true;
	}

	/* Looks like there's nothing we can really do: no other thread  is
	 * clearing caches, and nothing became free since the last time our
	 * caller tried to clear caches.
	 * -> Memory just can't be forced to become available :( */
	return false;
}

/* Helper  wrapper  for  `system_cc()'  that   throws
 * `E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY' on error. */
PUBLIC ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void FCALL
system_cc_virtual_memory(struct ccinfo *__restrict info)
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY) {
	if unlikely(!system_cc(info)) {
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		      info->ci_bytes);
	}
}

/* Simplified cache-clear functions that always try to free at least 1
 * byte,  but will get more aggressive as  attempts go on. This is the
 * preferred way of  doing cache-clear operations  and should be  used
 * like this:
 * >>     ccstate_t ccstate = CCSTATE_INIT;
 * >> again:
 * >>     result = try_allocate();
 * >>     if (!result)
 * >>         goto nomem;
 * >>     return result;
 * >> nomem:
 * >>     if (system_cc_s(&ccstate))
 * >>         goto again;
 * >>     THROW(E_BADALLOC);
 * Note that nesting within `try_allocate()'  is OK, though should  be
 * avoided for the sake of performance and more effective cc-handling. */
PUBLIC ATTR_BLOCKLIKE_GFP(gfp) ATTR_COLD WUNUSED ATTR_INOUT(1) bool
NOTHROW(FCALL system_cc_s_ex)(ccstate_t *__restrict p_state, gfp_t gfp) {
	struct ccinfo cci;
	ccinfo_init(&cci, gfp, 0);
	cci._ci_state = *p_state;
	if (system_cc(&cci) && cci.ci_bytes == 0)
		cci.ci_bytes = 1;
	*p_state = cci._ci_state;
	return cci.ci_bytes != 0;
}

PUBLIC ATTR_COLD WUNUSED ATTR_INOUT(1) bool
NOTHROW(FCALL system_cc_s)(ccstate_t *__restrict p_state) {
	return system_cc_s_ex(p_state, 0);
}

PUBLIC NOBLOCK ATTR_COLD WUNUSED ATTR_INOUT(1) bool
NOTHROW(FCALL system_cc_s_noblock)(ccstate_t *__restrict p_state) {
	return system_cc_s_ex(p_state, GFP_ATOMIC);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_CC_C */
