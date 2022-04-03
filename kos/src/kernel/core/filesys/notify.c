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
#ifndef GUARD_KERNEL_CORE_FILESYS_NOTIFY_C
#define GUARD_KERNEL_CORE_FILESYS_NOTIFY_C 1
#define __WANT_DNOTIFY_LINK__dnl_fildead
#define __WANT_DNOTIFY_LINK__dnl_rbword
#define __WANT_INOTIFY_CONTROLLER__inc_deadlnk
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_HAVE_FS_NOTIFY
#include <kernel/fs/dirent.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>

#include <kos/except.h>
#include <linux/inotify.h>

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE(name)           dnotify_link_tree_##name
#define RBTREE_T               struct dnotify_link
#define RBTREE_Tkey            struct fdirent const *
#define RBTREE_GETNODE(self)   (self)->dnl_dirnode
#define RBTREE_GETKEY(self)    (self)->dnl_ent
#define RBTREE_REDFIELD        _dnl_rbword
#define RBTREE_REDBIT          1
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

DECL_BEGIN

/* SMP-lock  for filesystem event notify. -- We use a global lock for this because
 * the alternative would be to set-up many smaller locks, each of which would also
 * need to have a  list of lock-ops, which  probably wouldn't actually make  stuff
 * faster since filesystem event notification is usually a brief process. */
#ifndef CONFIG_NO_SMP
PUBLIC struct atomic_lock notify_lock = ATOMIC_LOCK_INIT;
#endif /* !CONFIG_NO_SMP */

#ifndef __dnotify_link_slist_defined
#define __dnotify_link_slist_defined
SLIST_HEAD(dnotify_link_slist, dnotify_link);
#endif /* !__dnotify_link_slist_defined */


#ifndef __inotify_controller_slist_defined
#define __inotify_controller_slist_defined
SLIST_HEAD(inotify_controller_slist, inotify_controller);
#endif /* !__inotify_controller_slist_defined */

/* Clear all file->directory of files reachable from `self->dnc_files'. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL dnotify_controller_clearfiles)(struct dnotify_controller *__restrict self,
                                             struct dnotify_link_slist *__restrict deadlinks,
                                             struct inotify_controller_slist *__restrict deadnotif);

PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL dnotify_link_tree_delete)(struct dnotify_link *__restrict self,
                                        struct dnotify_link_slist *__restrict deadlinks,
                                        struct inotify_controller_slist *__restrict deadnotif) {
	struct dnotify_link *lhs, *rhs;
	struct inotify_controller *inot;
again:
	lhs = self->dnl_dirnode.rb_lhs;
	rhs = self->dnl_dirnode.rb_rhs;
	DBG_memset(&self->dnl_dirnode, 0xcc, sizeof(self->dnl_dirnode));

	/* Remove directory from the associated file (self->dnl_fil->inc_dirs) */
	inot = self->dnl_fil;
	assert(inot->inc_file);
	assert(inot->inc_file->mf_notify == inot);
	assert(!LIST_EMPTY(&inot->inc_dirs));
	LIST_REMOVE(self, dnl_fillink);
	DBG_memset(&self->dnl_fillink, 0xcc, sizeof(self->dnl_fillink));

	/* Check if anyone is still listening to this file. If not, clear it! */
	if (LIST_EMPTY(&inot->inc_dirs) && LIST_EMPTY(&inot->inc_listeners)) {
		assertf(!mfile_isdir(inot->inc_file) ||
		        (inotify_controller_asdnotify(inot)->dnc_files == NULL),
		        "Because `inc_listeners' was already NULL at the start, "
		        "there also shouldn't be any files in here (since files "
		        "are only linked when there are explicit listeners)");
		inot->inc_file->mf_notify = NULL; /* Remove link from file->notify_controller */
		DBG_memset(inot, 0xcc, sizeof(*inot));
		SLIST_INSERT(deadnotif, inot, _inc_deadlnk);
	}

	/* Add the deleted dnotify link to the dead list. */
	SLIST_INSERT(deadlinks, self, _dnl_fildead);

	/* Recursively delete all file links. */
	if (lhs) {
		if (rhs)
			dnotify_link_tree_delete(rhs, deadlinks, deadnotif);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}

/* Clear all file->directory of files reachable from `self->dnc_files'. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL dnotify_controller_clearfiles)(struct dnotify_controller *__restrict self,
                                             struct dnotify_link_slist *__restrict deadlinks,
                                             struct inotify_controller_slist *__restrict deadnotif) {
	if (self->dnc_files == NULL)
		return; /* Nothing to do here! */
	dnotify_link_tree_delete(self->dnc_files, deadlinks, deadnotif);
	self->dnc_files = NULL;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dnotify_link_slist_destroyall)(struct dnotify_link_slist *__restrict self) {
	struct dnotify_link *item;
	SLIST_FOREACH_SAFE (item, self, _dnl_fildead)
		dnotify_link_destroy(item);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL inotify_controller_slist_freeall)(struct inotify_controller_slist *__restrict self) {
	struct inotify_controller *item;
	SLIST_FOREACH_SAFE (item, self, _inc_deadlnk)
		inotify_controller_free(item);
}


/* Destroy a given notifyfd object. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL notifyfd_destroy)(struct notifyfd *__restrict self) {
	struct dnotify_link_slist deadlinks;
	struct inotify_controller_slist deadnotif;
	unsigned int i;
	SLIST_INIT(&deadlinks);
	SLIST_INIT(&deadnotif);
	for (i = 0; i < self->nf_listenc; ++i) {
		struct notify_listener *ent;
		REF struct mfile *file;
		ent = &self->nf_listenv[i];
		if (!ent->nl_file)
			continue; /* Deleted! */
		assert(ent->nl_notfd == self);

		/* Unlink listener */
		notify_lock_acquire();
		COMPILER_READ_BARRIER();
		if ((file = ent->nl_file) != NULL) {
			struct inotify_controller *inot;
			DBG_memset(&ent->nl_file, 0xcc, sizeof(ent->nl_file));
			inot = file->mf_notify;
			assertf(inot, "Must be non-NULL because the listener "
			               "we're about to remove still exists");
			assertf(!LIST_EMPTY(&inot->inc_listeners),
			        "Can't be empty because we're about to remove an element");
			assertf(inot->inc_file == file, "Wrong file? (%p != %p)", inot->inc_file, file);
			LIST_REMOVE(ent, nl_link);
			if (LIST_EMPTY(&inot->inc_listeners)) {
				/* If the file being monitored  is a directory, and  the
				 * listener we just removed was the last one to go, then
				 * we  have to clear the file->parent_directory links of
				 * all files currently loaded within that directory. */
				if (mfile_isdir(file)) {
					struct dnotify_controller *dnotif;
					dnotif = inotify_controller_asdnotify(inot);
					dnotify_controller_clearfiles(dnotif, &deadlinks, &deadnotif);
				}

				/* If the controller doesn't have any remaining listeners,
				 * both in terms  of per-file and  per-directory, then  we
				 * can safely delete it! */
				if (LIST_EMPTY(&inot->inc_dirs)) {
					file->mf_notify = NULL; /* Remove link from file->notify_controller */
					DBG_memset(inot, 0xcc, sizeof(*inot));
					SLIST_INSERT(&deadnotif, inot, _inc_deadlnk);
				}
			}
		}
		notify_lock_release();
		xdecref_unlikely(file); /* Inherited from `ent->nl_file' */
	}

	/* Free deleted objects. */
	dnotify_link_slist_destroyall(&deadlinks);
	inotify_controller_slist_freeall(&deadnotif);
	kfree(self->nf_listenv);
	kfree(self);
}

/* Create a new notifyfd object. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct notifyfd *KCALL
notifyfd_new(void) THROWS(E_BADALLOC) {
	REF struct notifyfd *result;
	result = (REF struct notifyfd *)kmalloc(sizeof(struct notifyfd), GFP_NORMAL);

	/* Initialize the new object. */
	result->nf_refcnt  = 1;
	result->nf_listenv = NULL;
	result->nf_listenc = 0;

	return result;
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL notify_listener_relocate)(struct notify_listener *__restrict oldlist,
                                        struct notify_listener *__restrict newlist,
                                        unsigned int count) {
	unsigned int fd;
	memcpy(newlist, oldlist, count, sizeof(struct notify_listener));
	for (fd = 0; fd < count; ++fd) {
		if (newlist[fd].nl_file == NULL)
			continue;
		assert(newlist[fd].nl_link.le_prev);
		assert(*newlist[fd].nl_link.le_prev == &oldlist[fd]);
		*newlist[fd].nl_link.le_prev = &newlist[fd];
		if (newlist[fd].nl_link.le_next) {
			assert(newlist[fd].nl_link.le_next->nl_link.le_prev == &oldlist[fd].nl_link.le_next);
			newlist[fd].nl_link.le_next->nl_link.le_prev = &newlist[fd].nl_link.le_next;
		}
	}
}



/* Add a new watch (listener) for `file' to `self'
 * @param: mask: Set of `IN_ALL_EVENTS', optionally or'd with:
 *                - IN_EXCL_UNLINK | IN_ONESHOT: Include as bits in `notify_listener::nl_mask'
 *                - IN_MASK_ADD:    Or valid bits from `mask' with any pre-existing watch events
 *                - IN_MASK_CREATE: Return `-EEXIST' if `file' is already being watched.
 * @return: * :      The watch descriptor (index into `self->nf_listenv')
 * @return: -EEXIST: `IN_MASK_CREATE' was given and `file' is already being monitored. */
PUBLIC WUNUSED NONNULL((1, 2)) unsigned int KCALL
notifyfd_addwatch(struct notifyfd *__restrict self,
                  struct mfile *__restrict file,
                  uint32_t mask)
		THROWS(E_BADALLOC) {
	struct notify_listener *ent;
	struct inotify_controller *ctrl = NULL;
	size_t ctrl_size = 0;
	unsigned int i, result;
	bool must_attach_directory = false;
	{
		RAII_FINALLY { kfree(ctrl); };
again:
		notify_lock_acquire();
		result = self->nf_listenc;

		/* Check if `file' is already being watched. */
		for (i = 0; i < self->nf_listenc; ++i) {
			ent = &self->nf_listenv[i];
			if (ent->nl_file == file) {
				/* File is already being monitored. */
				result = (unsigned int)-EEXIST;
				if (!(mask & IN_MASK_CREATE)) {
					result = i;
					/* Update watch mask */
					if (mask & IN_MASK_ADD)
						mask |= ent->nl_mask;
					ent->nl_mask = mask & (IN_ALL_EVENTS | IN_ONESHOT | IN_EXCL_UNLINK);
				}
				goto done_release;
			} else if (ent->nl_file == NULL) {
				if (result > i)
					result = i;
			}
		}
		if (result >= self->nf_listenc) {
			struct notify_listener *newlist;
			struct notify_listener *oldlist;
			unsigned int newsize;
			notify_lock_release_br();

			/* must allocate more slots. */
			newlist = (struct notify_listener *)kmalloc((result + 1) *
			                                            sizeof(struct notify_listener),
			                                            GFP_NORMAL | GFP_CALLOC);
			newsize = kmalloc_usable_size(newlist) / sizeof(struct notify_listener);
			assert(newsize > result);

			/* Install the new list. */
			notify_lock_acquire_br();
			if (newsize <= self->nf_listenc) {
				/* Race condition: size changed in the mean time. */
				notify_lock_release_br();
				kfree(newlist);
				goto again;
			}

			/* Relocate linked list links to point to `newlist' */
			oldlist = self->nf_listenv;
			notify_listener_relocate(oldlist, newlist, self->nf_listenc);

			/* Install the new list */
			self->nf_listenv = newlist;
			self->nf_listenc = newsize;

			/* Free the old list. */
			notify_lock_release_br();
			kfree(oldlist);

			/* Start over now that the list is known to be larger! */
			goto again;
		}

		/* Ensure that the file's got a controller. */
		if (file->mf_notify == NULL) {
			size_t reqsize = sizeof(struct inotify_controller);
			if (mfile_isdir(file))
				reqsize = sizeof(struct dnotify_controller);
			if (ctrl_size < reqsize) {
				/* Must allocate a larger controller. */
				notify_lock_release_br();
				ctrl      = (struct inotify_controller *)krealloc(ctrl, reqsize, GFP_NORMAL);
				ctrl_size = kmalloc_usable_size(ctrl);
				goto again;
			}
			if (mfile_isdir(file)) {
				struct dnotify_controller *dctrl;
				dctrl = inotify_controller_asdnotify(ctrl);
				dctrl->dnc_files      = NULL; /* Initialized later. */
				must_attach_directory = true; /* Instruct to fill `dctrl->dnc_files' later. */
			}

			/* Install `ctrl' as notification controller for `file' */
			LIST_INIT(&ctrl->inc_dirs);
			LIST_INIT(&ctrl->inc_listeners);
			ctrl->inc_file  = file;
			file->mf_notify = ctrl;

			/* Steal the controller. */
			ctrl      = NULL;
			ctrl_size = 0;
		}

		/* Register `ent' as a listener of `file->mf_notify' */
		ent = &self->nf_listenv[result];
		LIST_INSERT_HEAD(&file->mf_notify->inc_listeners, ent, nl_link);
		ent->nl_notfd = self;
		ent->nl_file  = incref(file);
		ent->nl_mask  = mask & (IN_ALL_EVENTS | IN_ONESHOT | IN_EXCL_UNLINK);
done_release:
		notify_lock_release();
/*done:*/
	} /*FINALLY {
		kfree(ctrl);
	}*/

	if (must_attach_directory) {
		assert(mfile_isdir(file));
		/* Attach `file->mf_notify' to currently-loaded files in the directory:
		 * >> struct dnotify_controller *dnotify;
		 * >> dnotify = inotify_controller_asdnotify(file->mf_notify);
		 * >> FOREACH (struct fdirent *child_dirent,
		 * >>          struct fnode   *child_inode:
		 * >>          ENUMATE_LOADED_CHILD_INODES(mfile_asdir(file))) {
		 * >>     struct dnotify_link *link;
		 * >>     if (dnotify_link_tree_locate(dnotify->dnc_files, child_dirent) != NULL)
		 * >>         continue;
		 * >>     ENSURE_ALLOCATED(child_inode->mf_notify);
		 * >>     link = dnotify_link_alloc();
		 * >>     link->dnl_dir = dnotify;
		 * >>     link->dnl_fil = child_inode;
		 * >>     LIST_INSERT(&child_inode->mf_notify->inc_dirs, link, dnl_fillink);
		 * >>     link->dnl_ent = incref(child_dirent);
		 * >>     dnotify_link_tree_insert(&dnotify->dnc_files, link);
		 * >> }
		 * NOTE: Locking of `notify_lock' is omitted from the above pseudo-code! */
		/* TODO: fdirnode_ops::dno_attach_notify(mfile_asdir(file)) */
	}
	return result;
}


/* Check if any of the FDs from [startfd,endfd) are in use. */
PRIVATE ATTR_PURE NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL notifyfd_anyused)(struct notifyfd const *__restrict self,
                                unsigned int startfd, unsigned int endfd) {
	unsigned int fd;
	for (fd = startfd; fd < endfd; ++fd) {
		if (notifyfd_fdused(self, fd))
			return true;
	}
	return false;
}

/* Try to trim the fd-vector of `self' to `newcount'. If doing so
 * is impossible (slots above this threshold are used, or  memory
 * cannot be allocated), simply do nothing. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL notifyfd_trytrim)(struct notifyfd *__restrict self,
                                unsigned int newcount) {
	struct notify_listener *newlist;
	struct notify_listener *oldlist;
	unsigned int used_newcount;
	newlist = (struct notify_listener *)kmalloc_nx(newcount * sizeof(struct notify_listener), GFP_ATOMIC);
	if (!newlist)
		return; /* Failed to allocate truncated list. */
	used_newcount = kmalloc_usable_size(newlist) / sizeof(struct notify_listener);
	assert(used_newcount >= newcount);

	/* Acquire lock */
	notify_lock_acquire();

	/* Verify that we've allowed to install `newlist */
	if (/* Existing list is already smaller (so can't _trim_ to `newcount') */
	    self->nf_listenc < newcount ||
	    /* Also make sure that none of the slots we've about to delete are used. */
	    notifyfd_anyused(self, newcount, self->nf_listenc)) {
		notify_lock_release_br();
		/* Unable to trim :( */
		kfree(newlist);
		return;
	}

	/* Install the new list */
	oldlist = self->nf_listenv;
	notify_listener_relocate(oldlist, newlist, self->nf_listenc);
	self->nf_listenv = newlist;
	self->nf_listenc = used_newcount;

	/* Release lock */
	notify_lock_release();

	/* Free the old list. */
	kfree(oldlist);
}


/* Remove the watch descriptor `watchfd' (as previously returned by `notifyfd_addwatch')
 * @return: true:  Successfully deleted `watchfd'.
 * @return: false: The given `watchfd' was already deleted. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL notifyfd_rmwatch)(struct notifyfd *__restrict self,
                                unsigned int watchfd) {
	bool trim_listener_list = false;
	struct dnotify_link_slist deadlinks;
	struct inotify_controller_slist deadnotif;
	struct notify_listener *ent;
	struct inotify_controller *inot;
	REF struct mfile *file = NULL;
	SLIST_INIT(&deadlinks);
	SLIST_INIT(&deadnotif);
	notify_lock_acquire();
	if unlikely(watchfd >= self->nf_listenc)
		goto done; /* Invalid fd */
	ent  = &self->nf_listenv[watchfd];
	file = ent->nl_file;
	if unlikely(file == NULL)
		goto done; /* Fd was already deleted */
	ent->nl_file = NULL; /* Inherited by `file' // indicate deleted slot */
	assert(ent->nl_notfd == self);
	DBG_memset(&ent->nl_notfd, 0xcc, sizeof(ent->nl_notfd));
	inot = file->mf_notify;
	assertf(inot, "Must be non-NULL because the listener "
	               "we're about to remove still exists");
	assertf(!LIST_EMPTY(&inot->inc_listeners),
	        "Can't be empty because we're about to remove an element");
	assertf(inot->inc_file == file, "Wrong file? (%p != %p)", inot->inc_file, file);
	LIST_REMOVE(ent, nl_link);

	if (LIST_EMPTY(&inot->inc_listeners)) {
		/* If the file being monitored  is a directory, and  the
		 * listener we just removed was the last one to go, then
		 * we  have to clear the file->parent_directory links of
		 * all files currently loaded within that directory. */
		if (mfile_isdir(file)) {
			struct dnotify_controller *dnotif;
			dnotif = inotify_controller_asdnotify(inot);
			dnotify_controller_clearfiles(dnotif, &deadlinks, &deadnotif);
		}

		/* If the controller doesn't have any remaining listeners,
		 * both in terms  of per-file and  per-directory, then  we
		 * can safely delete it! */
		if (LIST_EMPTY(&inot->inc_dirs)) {
			file->mf_notify = NULL; /* Remove link from file->notify_controller */
			DBG_memset(inot, 0xcc, sizeof(*inot));
			SLIST_INSERT(&deadnotif, inot, _inc_deadlnk);
		}
	}

	/* If all  watch fds  >=  `watchfd' are  marked  as
	 * deleted, then try to trim the list of listeners. */
	trim_listener_list = !notifyfd_anyused(self, watchfd + 1, self->nf_listenc);
	if (trim_listener_list) {
		/* Alter `watchfd' to become the new required count. */
		while (watchfd > 0 && self->nf_listenv[watchfd - 1].nl_file == NULL)
			--watchfd;
		if (watchfd == 0) {
			struct notify_listener *oldlist;
			/* Special case: the last watchfd went away. */
			oldlist = self->nf_listenv;
			self->nf_listenc = 0;
			self->nf_listenv = NULL;
			notify_lock_release_br();
			trim_listener_list = false;
			kfree(oldlist);
			goto done_postlock;
		}
	}

done:
	notify_lock_release();
done_postlock:

	/* Free deleted objects. */
	dnotify_link_slist_destroyall(&deadlinks);
	inotify_controller_slist_freeall(&deadnotif);
	xdecref_unlikely(file);

	/* Try to trim the list of listeners to a total of `watchfd' items */
	if (trim_listener_list)
		notifyfd_trytrim(self, watchfd);

	/* Return indicative of a file watch having been removed. */
	return file != NULL;
}



DECL_END
#endif /* CONFIG_HAVE_FS_NOTIFY */

#endif /* !GUARD_KERNEL_CORE_FILESYS_NOTIFY_C */
