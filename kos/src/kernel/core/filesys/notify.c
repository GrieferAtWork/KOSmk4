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
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <linux/inotify.h>

#include <assert.h>
#include <errno.h>
#include <limits.h>
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

PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL dnotify_link_tree_delete)(struct dnotify_link *__restrict self,
                                        struct dnotify_link_slist *__restrict deadlinks,
                                        struct inotify_controller_slist *__restrict deadnotif) {
	struct dnotify_link *lhs, *rhs;
	struct inotify_controller *inot;
	struct mfile *file;
again:
	lhs = self->dnl_dirnode.rb_lhs;
	rhs = self->dnl_dirnode.rb_rhs;
	DBG_memset(&self->dnl_dirnode, 0xcc, sizeof(self->dnl_dirnode));

	/* Remove directory from the associated file (self->dnl_fil->inc_dirs) */
	inot = self->dnl_fil;
	file = inot->inc_file;
	assert(file);
	assert(file->mf_notify == inot);
	assert(!LIST_EMPTY(&inot->inc_dirs));
	LIST_REMOVE(self, dnl_fillink);
	DBG_memset(&self->dnl_fillink, 0xcc, sizeof(self->dnl_fillink));

	/* Check if anyone is still listening to this file. If not, clear it! */
	if (LIST_EMPTY(&inot->inc_dirs) && LIST_EMPTY(&inot->inc_listeners)) {
		assertf(!mfile_isdir(file) ||
		        (inotify_controller_asdnotify(inot)->dnc_files == NULL),
		        "Because `inc_listeners' was already NULL at the start, "
		        "there also shouldn't be any files in here (since files "
		        "are only linked when there are explicit listeners)");
		file->mf_notify = NULL; /* Remove link from file->notify_controller */
		incref(file);           /* Inherited by `inotify_controller_slist_destroyall()' */
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
NOTHROW(FCALL inotify_controller_slist_destroyall)(struct inotify_controller_slist *__restrict self) {
	struct inotify_controller *item;
	SLIST_FOREACH_SAFE (item, self, _inc_deadlnk) {
		REF struct mfile *file                = item->inc_file;
		struct mfile_stream_ops const *stream = file->mf_ops->mo_stream;
		if (stream->mso_notify_detach != NULL)
			(*stream->mso_notify_detach)(file, item->inc_fhnd);
		decref_unlikely(file);
		inotify_controller_free(item);
	}
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
					incref(file);           /* Inherited by `inotify_controller_slist_destroyall()' */
					SLIST_INSERT(&deadnotif, inot, _inc_deadlnk);
				}
			}
		}
		notify_lock_release();
		xdecref_unlikely(file); /* Inherited from `ent->nl_file' */
	}

	/* Clear all remaining unread events. */
	notify_lock_acquire();
	while (self->nf_eventc) {
		REF struct fdirent *name;
		assert(self->nf_eventr < self->nf_eventc);
		name = self->nf_eventv[self->nf_eventr].mfe_name;
		DBG_memset(&self->nf_eventv[self->nf_eventr], 0xcc,
		           sizeof(self->nf_eventv[self->nf_eventr]));
		--self->nf_eventc;
		++self->nf_eventr;
		self->nf_eventr %= self->nf_eventa;
		if (name) {
			notify_lock_release_br();
			decref(name);
			notify_lock_acquire_br();
		}
	}
	notify_lock_release();

	/* Free deleted objects. */
	sig_broadcast_for_fini(&self->nf_avail);
	dnotify_link_slist_destroyall(&deadlinks);
	inotify_controller_slist_destroyall(&deadnotif);
	kfree(self->nf_listenv);
	kfree(self);
}

/* Create a new notifyfd object.
 * @param: num_events: The max number of unread pending events (excluding the failsafe overflow-event) */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct notifyfd *KCALL
notifyfd_new(unsigned int num_events) THROWS(E_BADALLOC) {
	REF struct notifyfd *result;
	result = (REF struct notifyfd *)kmalloc(offsetof(struct notifyfd, nf_eventv) +
	                                        ((num_events + 1) * sizeof(struct notifyfd_event)),
	                                        GFP_NORMAL);

	/* Initialize the new object. */
	result->nf_refcnt          = 1;
	result->_nf_blist.sle_next = NULL;
	result->nf_listenv         = NULL;
	result->nf_listenc         = 0;
	sig_init(&result->nf_avail);
	result->nf_eventr = 0;
	result->nf_eventc = 0;
	result->nf_eventa = num_events + 1;
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
 * NOTE: This function is only `BLOCKING' because `file->mf_ops->mo_stream_ops->mso_notify_attach'
 *       is  allowed  to  be `BLOCKING',  and  this function  may  need to  invoke  said operator!
 * NOTE: When `!mfile_canwatch(file)', the file's FD is immediately deleted and an `IN_IGNORED'
 *       event  is  generated,  though  the  returned  watch  descriptor  becomes  meaningless.
 * @param: mask_and_flags: Set of `IN_ALL_EVENTS', optionally or'd with:
 *          - IN_EXCL_UNLINK | IN_ONESHOT: Include as bits in `notify_listener::nl_mask'
 *          - IN_MASK_ADD:    Or valid bits from `mask' with any pre-existing watch events
 *          - IN_MASK_CREATE: Return `-EEXIST' if `file' is already being watched.
 * @return: * :      The watch descriptor (index into `self->nf_listenv')
 * @return: -EEXIST: `IN_MASK_CREATE' was given and `file' is already being monitored. */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
notifyfd_addwatch(struct notifyfd *__restrict self,
                  struct mfile *__restrict file,
                  uint32_t mask_and_flags)
		THROWS(E_BADALLOC) {
	struct notify_listener *ent;
	struct inotify_controller *ctrl = NULL;
	size_t ctrl_size = 0;
	unsigned int i, result;
	bool must_attach_directory = false;
	{
		RAII_FINALLY {
			if (ctrl) {
				struct mfile_stream_ops const *stream;
				stream = file->mf_ops->mo_stream;
				if (stream && stream->mso_notify_detach)
					(*stream->mso_notify_detach)(file, ctrl->inc_fhnd);
				kfree(ctrl);
			}
		};
again:
		notify_lock_acquire();
		result = self->nf_listenc;

		/* Check if `file' is already being watched. */
		for (i = 0; i < self->nf_listenc; ++i) {
			ent = &self->nf_listenv[i];
			if (ent->nl_file == file) {
				/* File is already being monitored. */
				result = (unsigned int)-EEXIST;
				if (!(mask_and_flags & IN_MASK_CREATE)) {
					result = i;
					/* Update watch mask */
					if (mask_and_flags & IN_MASK_ADD)
						mask_and_flags |= ent->nl_mask;
					goto set_ent_mask_and_done_release;
				}
				goto done_release;
			} else if (ent->nl_file == NULL) {
				if (result > i)
					result = i;
			}
		}

		/* Never allow slots that don't fit into a signed integer! */
#if __SIZEOF_SIZE_T__ > __SIZEOF_INT__
		if unlikely(result > (unsigned int)INT_MAX) {
			notify_lock_release_br();
			/* Yes: in theory there might be enough heap memory, but we
			 *      simply  fake that there  isn't enough, thus meaning
			 *      that  we don't have to add a new exception just for
			 *      this super-unlikely and special case. */
			THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
			      (result + 1) * sizeof(struct notify_listener));
		}
#endif /* __SIZEOF_SIZE_T__ > __SIZEOF_INT__ */

		/* Check if more slots must be allocated. */
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
				if (!ctrl) {
					void *file_cookie = NULL;
					/* Allocate a file cookie (if operators for it are defined) */
					{
						struct mfile_stream_ops const *stream;
						stream = file->mf_ops->mo_stream;
						if (stream && stream->mso_notify_attach)
							file_cookie = (*stream->mso_notify_attach)(file);
					}
					TRY {
						ctrl = (struct inotify_controller *)kmalloc(reqsize, GFP_NORMAL);
					} EXCEPT {
						struct mfile_stream_ops const *stream;
						stream = file->mf_ops->mo_stream;
						if (stream && stream->mso_notify_detach)
							(*stream->mso_notify_detach)(file, file_cookie);
						RETHROW();
					}
					ctrl->inc_fhnd = file_cookie;
				} else {
					ctrl = (struct inotify_controller *)krealloc(ctrl, reqsize, GFP_NORMAL);
				}
				ctrl_size = kmalloc_usable_size(ctrl);
				assert(ctrl_size >= reqsize);
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
			/*ctrl->inc_fhnd = file_cookie;*/ /* Already initialized during alloc */
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
set_ent_mask_and_done_release:
		ent->nl_mask = mask_and_flags & (IN_ALL_EVENTS | IN_ONESHOT | IN_EXCL_UNLINK);
		/* These events cannot be ignored */
		ent->nl_mask |= IN_UNMOUNT | IN_Q_OVERFLOW | IN_IGNORED;
done_release:
		notify_lock_release();
/*done:*/
	} /*FINALLY {
		if (ctrl)
			destroy(ctrl);
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


PRIVATE NOPREEMPT NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL notifyfd_postfsevent_raw_impl)(struct notifyfd *__restrict self,
                                             unsigned int wd, uint16_t mask,
                                             uint16_t cookie, struct fdirent *ent) {
	unsigned int slot_wd;
	struct notifyfd_event *slot;
	if (self->nf_eventc >= self->nf_eventa)
		return false; /* Already full */
	assert(!(wd & NOTIFYFD_EVENT_ISDIR_FLAG));
	assert(wd < self->nf_listenc);
	slot_wd = wd;
	if (ent ? (ent->fd_type == DT_DIR)
	        : mfile_isdir(self->nf_listenv[wd].nl_file))
		slot_wd |= NOTIFYFD_EVENT_ISDIR_FLAG;
	if (self->nf_eventc != 0) {
		/* Special case: linux documents that consecutive, identical events are merged. */
		slot = &self->nf_eventv[(self->nf_eventr + self->nf_eventc - 1) % self->nf_eventa];
		if (slot->nfe_wd == slot_wd && slot->mfe_mask == mask &&
		    slot->mfe_cookie == cookie && slot->mfe_name == ent)
			return false; /* Auto-merge identical events. */
	}

	slot = &self->nf_eventv[(self->nf_eventr + self->nf_eventc) % self->nf_eventa];
	++self->nf_eventc; /* Allocate one more event */
	if (self->nf_eventc >= self->nf_eventa) {
		/* Last slot allocated -> must fill with `IN_Q_OVERFLOW' */
		STATIC_ASSERT(!((unsigned int)INT_MAX & NOTIFYFD_EVENT_ISDIR_FLAG));
		slot->nfe_wd     = (unsigned int)INT_MAX; /* Don't set most significant bit! */
		slot->mfe_mask   = IN_Q_OVERFLOW;
		slot->mfe_cookie = 0;
		slot->mfe_name   = NULL;
	} else {
		/* Fill in the new slot. */
		slot->nfe_wd     = slot_wd;
		slot->mfe_mask   = mask;
		slot->mfe_cookie = cookie;
		slot->mfe_name   = xincref(ent);
	}
	return true;
}


/* Remove the watch descriptor `watchfd' (as previously returned by `notifyfd_addwatch')
 * @return: true:  Successfully deleted `watchfd'.
 * @return: false: The given `watchfd' was already deleted. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL notifyfd_rmwatch)(struct notifyfd *__restrict self,
                                unsigned int watchfd) {
	bool trim_listener_list = false;
	bool should_broadcast   = false;
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

	/* Notify watchfd deletion. */
	if (notifyfd_postfsevent_raw_impl(self, watchfd, IN_IGNORED, 0, NULL))
		should_broadcast = self->nf_eventc == 1;

	/* Actually delete the slot. */
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
			incref(file);           /* Inherited by `inotify_controller_slist_destroyall()' */
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
	inotify_controller_slist_destroyall(&deadnotif);

	/* Try to trim the list of listeners to a total of `watchfd' items */
	if (trim_listener_list)
		notifyfd_trytrim(self, watchfd);
	if (should_broadcast)
		sig_broadcast(&self->nf_avail);

	/* Return indicative of a file watch having been removed. */
	return file != NULL;
}



/* If `dir->mf_notify != NULL', ensure that `child_file->mf_notify' has
 * been allocated, and that it is linked in the dnotify child-file list
 * of `dir'.
 *
 * Always inherits a reference to `child_file' that is also always re-
 * returned.  - In case  of an allocation error,  this pointer will be
 * decref'd! */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct fnode *KCALL
dnotify_controller_bindchild(struct fdirnode *__restrict dir,
                             struct fdirent *__restrict child_dent,
                             /*inherit(always)*/ REF struct fnode *__restrict child_file)
		THROWS(E_BADALLOC, ...) {
	if likely(dir->mf_notify == NULL)
		return child_file; /* Nothing to do in this case! */
	return dnotify_controller_bindchild_slow(dir, child_dent, child_file);
}
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct fnode *KCALL
dnotify_controller_bindchild_slow(struct fdirnode *__restrict dir,
                                  struct fdirent *__restrict child_dent,
                                  /*inherit(always)*/ REF struct fnode *__restrict child_file)
		THROWS(E_BADALLOC, ...) {
	assert(!!mfile_isdir(child_file) == (child_dent->fd_type == DT_DIR));
	struct dnotify_link *link = NULL;
	/*if unlikely(dir->mf_notify == NULL)
		return child_file;*/
	RAII_FINALLY { dnotify_link_xfree(link); };
again:
	COMPILER_READ_BARRIER();
	if (child_file->mf_notify == NULL) {
		struct inotify_controller *ctrl;
allocate_missing_child_file_notify:
		/* Allocate the notify controller for `child_file' */
		COMPILER_READ_BARRIER();
		TRY {
			if (link == NULL) /* If there's no controller, we're also gonna need the link! */
				link = dnotify_link_alloc();
			if (mfile_isdir(child_file)) {
				struct dnotify_controller *dctrl;
				dctrl = dnotify_controller_alloc();
				dctrl->dnc_files = NULL;
				ctrl = dctrl;
			} else {
				ctrl = inotify_controller_alloc();
			}
			ctrl->inc_file = child_file;
			LIST_INIT(&ctrl->inc_listeners);
			/* Properly initialized properly below. */
			DBG_memset(&link->dnl_dirnode, 0xcc, sizeof(link->dnl_dirnode));
			DBG_memset(&link->dnl_dir, 0xcc, sizeof(link->dnl_dir));
			ctrl->inc_dirs.lh_first   = link;
			link->dnl_fillink.le_prev = &ctrl->inc_dirs.lh_first;
			link->dnl_fillink.le_next = NULL;
			link->dnl_fil             = ctrl;
			link->dnl_ent             = incref(child_dent);

			/* If the operator for it is defined, allocate a notify handle. */
			ctrl->inc_fhnd = NULL;
			{
				struct mfile_stream_ops const *stream;
				stream = child_file->mf_ops->mo_stream;
				if (stream && stream->mso_notify_attach) {
					TRY {
						ctrl->inc_fhnd = (*stream->mso_notify_attach)(child_file);
					} EXCEPT {
						decref_nokill(child_dent); /* From `link->dnl_ent' */
						inotify_controller_free(ctrl);
						RETHROW();
					}
				}
			}
		} EXCEPT {
			decref(child_file); /* Must inherit reference on error! */
			RETHROW();
		}

		/* Now try to install the notify-controller for `child_file' */
		notify_lock_acquire();
		COMPILER_READ_BARRIER();
		if unlikely(child_file->mf_notify != NULL ||
		            dir->mf_notify == NULL) {
			struct mfile_stream_ops const *stream;
			/* Race condition: someone else already created the controller in the mean time,
			 *                 or the directory's notify controller has since been  deleted. */
			notify_lock_release_br();
			stream = child_file->mf_ops->mo_stream;
			if (stream && stream->mso_notify_detach)
				(*stream->mso_notify_detach)(child_file, ctrl->inc_fhnd);
			decref_nokill(child_dent); /* From `link->dnl_ent' */
			DBG_memset(link, 0xcc, sizeof(*link));
			inotify_controller_free(ctrl);
			goto after_file_got_controller;
		}

		/* Install the controller and link it in the directory. */
		assert(dir->mf_notify->inc_file == dir);
		link->dnl_dir = inotify_controller_asdnotify(dir->mf_notify);
		assertf(!dnotify_link_tree_locate(link->dnl_dir->dnc_files, child_dent),
		        "Directory entry %$q already present when we know for a fact "
		        "that its associated file didn't have a notify controller...",
		        (size_t)child_dent->fd_namelen, child_dent->fd_name);
		dnotify_link_tree_insert(&link->dnl_dir->dnc_files, link);
		child_file->mf_notify = ctrl;
		notify_lock_release();

		/* And with that, everything has been  */
		return child_file;
	}
after_file_got_controller:

	/* At  this point  we know that  `child_file' (at one  point) had its
	 * notify controller allocated, and that `dir' also had a  controller
	 * at one point. -- Now we must check if `dir' is already referencing
	 * `child_file' in its notify controller, and if not: establish  that
	 * missing `link' (s.a. the `link' variable above) */
	notify_lock_acquire();
	COMPILER_READ_BARRIER();

	/* Check for race condition: notify controller of `dir' was deleted. */
	if unlikely(dir->mf_notify == NULL) {
		struct inotify_controller *cnot;
		cnot = child_file->mf_notify;
		if (cnot != NULL &&
		    LIST_EMPTY(&cnot->inc_dirs) &&
		    LIST_EMPTY(&cnot->inc_listeners)) {
			struct mfile_stream_ops const *stream;
			/* Nothing is using the notify controller of `child_file', but
			 * we still allocated it above. -- As such, we have to destroy
			 * it once again! */
			child_file->mf_notify = NULL;
			notify_lock_release_br();
			assert(cnot->inc_file == child_file);
			assert(!mfile_isdir(child_file) ||
			       (inotify_controller_asdnotify(cnot)->dnc_files == NULL));
			stream = child_file->mf_ops->mo_stream;
			if (stream && stream->mso_notify_detach)
				(*stream->mso_notify_detach)(child_file, cnot->inc_fhnd);
			inotify_controller_free(cnot);
		} else {
			notify_lock_release_br();
		}
		return child_file;
	}

	/* Check for race condition: the file's notify-controller was freed. */
	if unlikely(child_file->mf_notify == NULL) {
		notify_lock_release_br();
		goto allocate_missing_child_file_notify;
	}

	/* With both controllers  allocated, check  if
	 * the directory already references the child. */
	{
		struct dnotify_controller *dnot;
		struct inotify_controller *cnot;
		struct dnotify_link *clnk;
		dnot = inotify_controller_asdnotify(dir->mf_notify);
		cnot = child_file->mf_notify;
		clnk = dnotify_link_tree_locate(dnot->dnc_files, child_dent);
		if (clnk != NULL) {
			/* Directory is already referencing the child. */
			assert(dnotify_link_getdir(clnk) == dnot);
			assert(dnotify_link_getfil(clnk) == cnot);
			assert(dnotify_link_getent(clnk) == child_dent);
			goto done;
		}

		/* Directory isn't referencing the child yet,
		 * so  we  have  to  establish  that  `link'! */
		if (link == NULL) {
			/* Lazily allocate if needed. */
			notify_lock_release_br();
			TRY {
				link = dnotify_link_alloc();
			} EXCEPT {
				decref(child_file); /* Must inherit reference on error! */
				RETHROW();
			}
			goto again;
		}

		/* Use `link' to connect `dnot' with `cnot' */
		link->dnl_dir = dnot;
		LIST_INSERT_HEAD(&cnot->inc_dirs, link, dnl_fillink);
		link->dnl_fil = cnot;
		link->dnl_ent = incref(child_dent);
		dnotify_link_tree_insert(&dnot->dnc_files, link);
		link = NULL; /* Stolen, so don't free! */
	}

done:
	notify_lock_release();

	/* Always just re-return `child_file' */
	return child_file;
}


#ifndef __notifyfd_slist_defined
#define __notifyfd_slist_defined
SLIST_HEAD(notifyfd_slist, notifyfd);
#endif /* !__notifyfd_slist_defined */


/* Enqueue a filesystem event into `self'.
 * NOTE: The caller must be holding `notify_lock_acquire()'
 * @param: wd:     s.a. `struct inotify_event::ine_wd'
 * @param: mask:   s.a. `struct inotify_event::ine_mask'
 * @param: cookie: s.a. `struct inotify_event::ine_cookie'
 * @param: ent:    s.a. `struct inotify_event::ine_(len|name)' */
PRIVATE NOPREEMPT NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL notifyfd_postfsevent_impl)(struct notifyfd *__restrict self,
                                         struct REF notifyfd_slist *__restrict blist,
                                         unsigned int wd, uint16_t mask,
                                         uint16_t cookie, struct fdirent *ent) {
	/* Post the event. */
	if (!notifyfd_postfsevent_raw_impl(self, wd, mask, cookie, ent))
		return;

	/* If we just posted the first  event to the notifyfd, then  we
	 * must enqueue a call to  `sig_broadcast()'. We can't do  that
	 * call immediately because we're currently holding an SMP-lock */
	if (self->nf_eventc == 1) {
		/* Only enqueue for broadcast if the notifyfd isn't already pending
		 * a broadcast in the context of  some other thread that also  just
		 * send it an fs event.
		 * This prevents an unlikely race condition:
		 *   thread#1: Posts FS event
		 *   thread#1: Adds notifyfd to pending-broadcast list
		 *   thread#1: notify_lock_release();
		 *   thread#2: read(notifyfd) --> reads just-posted event
		 *   thread#3: Posts FS event
		 *   thread#3: -- We get here, but `self->_nf_blist.sle_next != NULL' because of thread#1
		 *   thread#3: ...
		 *   thread#3: notify_lock_release();
		 *             ...
		 *   thread#1: ATOMIC_WRITE(notifyfd->_nf_blist.sle_next, NULL);
		 *   thread#1: sig_broadcast(notifyfd)
		 *   thread#1: decref(notifyfd)
		 */
		if likely(self->_nf_blist.sle_next == NULL) {
			/* It  is possible to encounter already-destroyed notifyfd objects
			 * when posting events.  - That's OK  since the destroy  functions
			 * for these objects will wait for the global `notify_lock', prior
			 * to actually finalizing anything (other than the refcnt).
			 *
			 * And once the destroy function gets the lock, it will remove the
			 * notifyfd from all attached files,  meaning we wouldn't be  able
			 * to see it in its partially-destroyed form.
			 *
			 * However, since we want to enqueue the notifyfd for being woken
			 * due to having events be added,  this has to happen _after_  we
			 * released  our lock to `notify_lock', at which point we have to
			 * ensure that the object hasn't been destroyed yet.
			 *
			 * As such, we try to acquire a reference here and only broadcast
			 * the notifyfd object if it  wasn't already dead at this  point! */
			if (tryincref(self)) {
				self->_nf_blist.sle_next = blist->slh_first; /* Never `NULL'! */
				blist->slh_first         = self;
			}
		}
	}
}


PRIVATE NOPREEMPT NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL notify_listener_postfsevent_raw_impl)(struct notify_listener *__restrict self,
                                                    struct REF notifyfd_slist *__restrict blist,
                                                    uint16_t mask, uint16_t cookie, struct fdirent *ent) {
	struct notifyfd *notfd = self->nl_notfd;
	notifyfd_postfsevent_impl(notfd, blist,
	                          (unsigned int)(self - notfd->nf_listenv),
	                          mask, cookie, ent);
}

PRIVATE NOPREEMPT NOBLOCK NONNULL((1, 2, 6, 7)) void
NOTHROW(FCALL notify_listener_postfsevent_impl)(struct notify_listener *__restrict self,
                                                struct REF notifyfd_slist *__restrict blist,
                                                uint16_t mask, uint16_t cookie, struct fdirent *ent,
                                                struct dnotify_link_slist *__restrict deadlinks,
                                                struct inotify_controller_slist *__restrict deadnotif) {
	struct notifyfd *notfd;
	unsigned int wd;

	/* Check if the event is even being listened for. */
	if ((mask & self->nl_mask) == 0)
		return; /* Ignore event */
	notfd = self->nl_notfd;
	wd    = (unsigned int)(self - notfd->nf_listenv);
	notifyfd_postfsevent_impl(notfd, blist, wd, mask, cookie, ent);

	/* Handle IN_ONESHOT descriptors */
	if (self->nl_mask & IN_ONESHOT) {
		struct mfile *file = self->nl_file;
		struct inotify_controller *inot;
		notifyfd_postfsevent_impl(notfd, blist, wd, IN_IGNORED, 0, NULL);

		/* Actually delete the slot. */
		self->nl_file = NULL; /* Inherited by `file' // indicate deleted slot */
		DBG_memset(&self->nl_notfd, 0xcc, sizeof(self->nl_notfd));
		inot = file->mf_notify;
		assertf(inot, "Must be non-NULL because the listener "
		               "we're about to remove still exists");
		assertf(!LIST_EMPTY(&inot->inc_listeners),
		        "Can't be empty because we're about to remove an element");
		assertf(inot->inc_file == file, "Wrong file? (%p != %p)", inot->inc_file, file);
		LIST_REMOVE(self, nl_link);

		if (LIST_EMPTY(&inot->inc_listeners)) {
			/* If the file being monitored  is a directory, and  the
			 * listener we just removed was the last one to go, then
			 * we  have to clear the file->parent_directory links of
			 * all files currently loaded within that directory. */
			if (mfile_isdir(file)) {
				struct dnotify_controller *dnotif;
				dnotif = inotify_controller_asdnotify(inot);
				dnotify_controller_clearfiles(dnotif, deadlinks, deadnotif);
			}

			/* If the controller doesn't have any remaining listeners,
			 * both in terms  of per-file and  per-directory, then  we
			 * can safely delete it! */
			if (LIST_EMPTY(&inot->inc_dirs)) {
				file->mf_notify = NULL; /* Remove link from file->notify_controller */
				incref(file);           /* Inherited by `inotify_controller_slist_destroyall()' */
				SLIST_INSERT(deadnotif, inot, _inc_deadlnk);
			}
		}
	}
}


PRIVATE NOPREEMPT NOBLOCK NONNULL((1, 2, 6, 7)) void
NOTHROW(FCALL inotify_controller_postfsevent_impl)(struct inotify_controller *__restrict self,
                                                   struct REF notifyfd_slist *__restrict blist,
                                                   uint16_t fil_mask, uint16_t dir_mask, uint16_t cookie,
                                                   struct dnotify_link_slist *__restrict deadlinks,
                                                   struct inotify_controller_slist *__restrict deadnotif) {
	/* Post file events. */
	if (fil_mask != 0) {
		struct notify_listener *listener;
		LIST_FOREACH_SAFE (listener, &self->inc_listeners, nl_link) {
			notify_listener_postfsevent_impl(listener, blist, fil_mask, cookie,
			                                 NULL, deadlinks, deadnotif);
		}
	}

	/* Post directory events. */
	if (dir_mask != 0) {
		struct dnotify_link *link;
		LIST_FOREACH_SAFE (link, &self->inc_dirs, dnl_fillink) {
			struct notify_listener *listener;
			struct dnotify_controller *dir = link->dnl_dir;
			LIST_FOREACH_SAFE (listener, &dir->inc_listeners, nl_link) {
				notify_listener_postfsevent_impl(listener, blist, fil_mask, cookie,
				                                 link->dnl_ent, deadlinks, deadnotif);
			}
		}
	}
}



/* Empty-marker for a BLIST (NOTE: The "b" stands for "broadcast") */
#define BLIST_EMPTY_MARKER ((REF struct notifyfd *)-1) /* Must be non-NULL! */

/* Broadcast the avail-signals of all elements from `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL blist_serve)(struct REF notifyfd_slist *__restrict self) {
	while (self->slh_first != BLIST_EMPTY_MARKER) {
		REF struct notifyfd *nfd;
		nfd             = self->slh_first;
		self->slh_first = nfd->_nf_blist.sle_next;
		COMPILER_READ_BARRIER();

		/* Allow other threads to enqueue further broadcasts for this notifyfd */
		ATOMIC_WRITE(nfd->_nf_blist.sle_next, NULL);

		/* Perform the broadcast we are meant to perform. */
		sig_broadcast(&nfd->nf_avail);

		/* Drop the reference we were given to do the broadcast. */
		decref_unlikely(nfd);
	}
}



/* Special function to post `IN_IGNORED', as well as delete all watch-descriptors of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_postfs_ignored)(struct mfile *__restrict self) {
	struct REF notifyfd_slist blist;
	struct dnotify_link_slist deadlinks;
	struct inotify_controller_slist deadnotif;
	struct inotify_controller *notif;
	assert(!wasdestroyed(self));
	COMPILER_READ_BARRIER();
	if (self->mf_notify == NULL)
		return;
	SLIST_INIT(&deadlinks);
	SLIST_INIT(&deadnotif);
	blist.slh_first = BLIST_EMPTY_MARKER;
	notify_lock_acquire();
	COMPILER_READ_BARRIER();
	notif = self->mf_notify;
	if (notif != NULL) {
		struct notify_listener *listen;
		struct dnotify_link *link;
		assert(notif->inc_file == self);
		LIST_FOREACH_SAFE (listen, &notif->inc_listeners, nl_link) {
			assert(listen->nl_file == self);
			notify_listener_postfsevent_raw_impl(listen, &blist, IN_IGNORED, 0, NULL);
			listen->nl_file = NULL; /* Mark as deleted. */
			decref_nokill(self);    /* Reference stolen from `listen->nl_file' */
			/* XXX: Somehow try to truncate the watch-fd vector of `listen->nl_notfd'?
			 *      We can't just  do so unconditionally  because not even  GFP_ATOMIC
			 *      realloc is smp-lock-safe (and we're currently holding an SMP-lock) */
			DBG_memset(&listen->nl_notfd, 0xcc, sizeof(listen->nl_notfd));
			DBG_memset(&listen->nl_link, 0xcc, sizeof(listen->nl_link));
		}
		DBG_memset(&notif->inc_listeners, 0xcc, sizeof(notif->inc_listeners));

		/* Also sever all connections to containing directories. */
		LIST_FOREACH_SAFE (link, &notif->inc_dirs, dnl_fillink) {
			assert(dnotify_link_getfil(link) == notif);
			dnotify_link_tree_removenode(&dnotify_link_getdir(link)->dnc_files, link);
			DBG_memset(&link->dnl_dirnode, 0xcc, sizeof(link->dnl_dirnode));
			SLIST_INSERT(&deadlinks, link, _dnl_fildead); /* Destroy later... */
		}

		/* If the file itself is a directory, then we must also clear
		 * the file->containing_directory links from all child files. */
		if (mfile_isdir(self)) {
			struct dnotify_controller *dnotif;
			dnotif = inotify_controller_asdnotify(notif);
			dnotify_controller_clearfiles(dnotif, &deadlinks, &deadnotif);
		}

		/* Add the file's own notify controller to the free list. */
		self->mf_notify = NULL; /* Steal (destroyed in `inotify_controller_slist_destroyall()') */
		incref(self);           /* Inherited by `inotify_controller_slist_destroyall()' */
		SLIST_INSERT(&deadnotif, notif, _inc_deadlnk);
	}
	notify_lock_release();

	/* Free deleted objects. */
	dnotify_link_slist_destroyall(&deadlinks);
	inotify_controller_slist_destroyall(&deadnotif);
	blist_serve(&blist);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_postfsevent_impl)(struct mfile *__restrict self,
                                      uint16_t fil_mask, uint16_t dir_mask,
                                      uint16_t cookie) {
	struct REF notifyfd_slist blist = { BLIST_EMPTY_MARKER };
	struct dnotify_link_slist deadlinks;
	struct inotify_controller_slist deadnotif;
	COMPILER_READ_BARRIER();
	if (self->mf_notify == NULL)
		return;
	SLIST_INIT(&deadlinks);
	SLIST_INIT(&deadnotif);
	notify_lock_acquire();
	COMPILER_READ_BARRIER();
	if (self->mf_notify != NULL) {
		inotify_controller_postfsevent_impl(self->mf_notify, &blist,
		                                    fil_mask, dir_mask, cookie,
		                                    &deadlinks, &deadnotif);
	}
	notify_lock_release();

	/* Free deleted objects. */
	dnotify_link_slist_destroyall(&deadlinks);
	inotify_controller_slist_destroyall(&deadnotif);
	blist_serve(&blist);
}

/* Like the functions above, but operator on a given `struct mfile *self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_postfsevent)(struct mfile *__restrict self,
                                 uint16_t mask) {
	mfile_postfsevent_impl(self, mask, mask, 0);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_postfsfilevent)(struct mfile *__restrict self,
                                    uint16_t mask) {
	mfile_postfsevent_impl(self, mask, 0, 0);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_postfsdirevent)(struct mfile *__restrict self,
                                    uint16_t mask) {
	mfile_postfsevent_impl(self, 0, mask, 0);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_postfsdirevent2)(struct mfile *__restrict self,
                                     uint16_t mask, uint16_t cookie) {
	mfile_postfsevent_impl(self, 0, mask, cookie);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_postfsevent_ex)(struct mfile *__restrict self,
                                    uint16_t fil_mask, uint16_t dir_mask) {
	mfile_postfsevent_impl(self, fil_mask, dir_mask, 0);
}




/************************************************************************/
/* HANDLE OPERATORS FOR `HANDLE_TYPE_NOTIFYFD' (struct notifyfd)        */
/************************************************************************/
DEFINE_HANDLE_REFCNT_FUNCTIONS(notifyfd, struct notifyfd);

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_notifyfd_read_nonblock(struct notifyfd *__restrict self,
                              USER CHECKED void *dst,
                              size_t num_bytes) THROWS(...) {
	USER CHECKED struct inotify_event *uevent;
	struct notifyfd_event ne;
	struct notifyfd_event *slot;
	size_t reqsize;
	uint32_t umask;

	/* Load the next-pending event. */
again:
	notify_lock_acquire();
	COMPILER_READ_BARRIER();
	if (self->nf_eventc == 0) {
		notify_lock_release_br();
		return 0; /* Nothing pending... */
	}
	slot = &self->nf_eventv[self->nf_eventr];
	memcpy(&ne, slot, sizeof(ne));
	xincref(ne.mfe_name);
	notify_lock_release();
	FINALLY_XDECREF_UNLIKELY(ne.mfe_name);

	/* Calculate the required buffer size for this slot. */
	reqsize = offsetof(struct inotify_event, ine_name);
	if (ne.mfe_name != NULL)
		reqsize += (ne.mfe_name->fd_namelen + 1) * sizeof(char);

	/* Check if the user-provided buffer is large enough. */
	if (reqsize > num_bytes) {
		/* Linux documents `EINVAL' for this case, but our usual `E_BUFFER_TOO_SMALL'
		 * translates to `ERANGE'. As such, we need to use a custom sub-class.  *ugh* */
		THROW(_E_BUFFER_TOO_SMALL_EINVAL, reqsize, num_bytes);
	}

	/* Copy the entry to user-space. */
	uevent = (USER CHECKED struct inotify_event *)dst;
	umask  = ne.mfe_mask;
	if (ne.nfe_wd & NOTIFYFD_EVENT_ISDIR_FLAG)
		umask |= IN_ISDIR;
	UNALIGNED_SET((uint32_t *)&uevent->ine_wd, ((uint32_t)ne.nfe_wd & ~NOTIFYFD_EVENT_ISDIR_FLAG));
	UNALIGNED_SET(&uevent->ine_mask, umask);
	UNALIGNED_SET(&uevent->ine_cookie, (uint32_t)ne.mfe_cookie);
	if (ne.mfe_name) {
		UNALIGNED_SET(&uevent->ine_len, (u32)(ne.mfe_name->fd_namelen + 1));
		memcpy(uevent->ine_name, ne.mfe_name->fd_name,
		       ne.mfe_name->fd_namelen + 1, sizeof(char));
	} else {
		UNALIGNED_SET(&uevent->ine_len, 0);
	}

	/* Consume the entry from the pending-events list. */
	notify_lock_acquire();
	COMPILER_READ_BARRIER();
	slot = &self->nf_eventv[self->nf_eventr];
	if unlikely(self->nf_eventc == 0 || memcmp(&ne, slot, sizeof(ne)) != 0) {
		/* Race condition: event was already read by another thread. --> try again */
		notify_lock_release_br();
		goto again;
	}
	--self->nf_eventc;
	++self->nf_eventr;
	self->nf_eventr %= self->nf_eventa;
	notify_lock_release();

	/* Return the required buffer size back to user-space. */
	return reqsize;
}


INTERN BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_notifyfd_read(struct notifyfd *__restrict self, USER CHECKED void *dst,
                     size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	while ((result = handle_notifyfd_read_nonblock(self, dst, num_bytes)) == 0) {
		if (mode & IO_NONBLOCK) {
			if (mode & IO_NODATAZERO)
				break;
			THROW(E_WOULDBLOCK);
		}
		task_connect(&self->nf_avail);
		TRY {
			result = handle_notifyfd_read_nonblock(self, dst, num_bytes);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		task_waitfor();
	}
	return result;
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_notifyfd_pollconnect(struct notifyfd *__restrict self,
                            poll_mode_t what) THROWS(...) {
	if (what & POLLSELECT_READFDS)
		task_connect_for_poll(&self->nf_avail);
}

INTERN BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_notifyfd_polltest(struct notifyfd *__restrict self,
                         poll_mode_t what) THROWS(...) {
	poll_mode_t result = 0;
	if (ATOMIC_READ(self->nf_eventc) != 0)
		result |= POLLSELECT_READFDS;
	return result & what;
}






DECL_END
#endif /* CONFIG_HAVE_FS_NOTIFY */

#endif /* !GUARD_KERNEL_CORE_FILESYS_NOTIFY_C */
