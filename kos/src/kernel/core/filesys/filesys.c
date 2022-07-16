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
#ifndef GUARD_KERNEL_CORE_FILESYS_FILESYS_C
#define GUARD_KERNEL_CORE_FILESYS_FILESYS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/aref.h>
#include <kos/except.h>

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* Global set of registered filesystem formats. */
PUBLIC struct ffilesys_slist ffilesys_formats_list = { .slh_first = &devfs_filesys };
PUBLIC struct atomic_lock ffilesys_formats_lock   = ATOMIC_LOCK_INIT;
PUBLIC struct lockop_slist ffilesys_formats_lops  = SLIST_HEAD_INITIALIZER(ffilesys_formats_lops);

struct aio_multihandle;

PRIVATE NONNULL((1, 5)) void KCALL
throw_readonly_v_saveblocks(struct mfile *__restrict UNUSED(self), pos_t UNUSED(addr),
                            physaddr_t UNUSED(buf), size_t num_bytes,
                            struct aio_multihandle *__restrict UNUSED(aio)) {
	if likely(num_bytes != 0)
		THROW(E_FSERROR_READONLY);
}


PRIVATE BLOCKING NONNULL((1, 5)) void KCALL
unaligned_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                       physaddr_t buf, size_t num_bytes,
                       struct aio_multihandle *__restrict UNUSED(aio)) {
	mfile_readall_p(self, buf, num_bytes, addr);
}

PRIVATE BLOCKING NONNULL((1, 5)) void KCALL
unaligned_v_saveblocks(struct mfile *__restrict self, pos_t addr,
                       physaddr_t buf, size_t num_bytes,
                       struct aio_multihandle *__restrict UNUSED(aio)) {
	mfile_writeall_p(self, buf, num_bytes, addr);
}



/* Set of files for which mounting is currently in progress. */
PRIVATE size_t /*       */ mount_in_progress_count = 0;        /* [lock(mount_in_progress_lock)] # of files with in-progress mounts */
PRIVATE REF struct mfile **mount_in_progress_list  = NULL;     /* [1..1][0..mount_in_progress_count][owned][lock(mount_in_progress_lock)] List of files with in-progress mounts */
PRIVATE struct sig /*   */ mount_in_progress_rmsig = SIG_INIT; /* Broadcast when a file is removed from `mount_in_progress_list' */
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_lock mount_in_progress_lock = ATOMIC_LOCK_INIT; /* SMP-lock for `mount_in_progress_list' */
#endif /* !CONFIG_NO_SMP */
#define mount_in_progress_lock_acquire_br() atomic_lock_acquire_smp_b(&mount_in_progress_lock)
#define mount_in_progress_lock_release_br() atomic_lock_release_smp_b(&mount_in_progress_lock)
#define mount_in_progress_lock_acquire()    atomic_lock_acquire_smp(&mount_in_progress_lock)
#define mount_in_progress_lock_release()    atomic_lock_release_smp(&mount_in_progress_lock)

/* Check if  `mount_in_progress_list'  contains  `dev'.  The
 * caller must be holding a lock to `mount_in_progress_lock' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mount_in_progress_contains)(struct mfile *__restrict dev) {
	size_t i;
	for (i = 0; i < mount_in_progress_count; ++i) {
		if (mount_in_progress_list[i] == dev)
			return true;
	}
	return false;
}

/* Search  for a pre-existing superblock that uses `dev'.
 * The caller must be holding a lock to `fallsuper_list'. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct fsuper *
NOTHROW(FCALL find_existing_superblock)(struct mfile *__restrict dev) {
	struct fsuper *iter;
	LIST_FOREACH (iter, &fallsuper_list, fs_root.fn_allsuper) {
		if (ATOMIC_READ(iter->fs_dev) != dev)
			continue;

		/* Make sure that this superblock hasn't been destroyed yet,
		 * and also hasn't  been marked as  unmounted. If either  of
		 * these  is the case, then act like we didn't see anything. */
		if (ATOMIC_READ(iter->fs_mounts.lh_first) == FSUPER_MOUNTS_DELETED)
			continue; /* Can no longer be mounted. */

		if unlikely(!tryincref(iter)) {
			/* Already marked as destroyed (highly unlikely
			 * since `fs_mounts' wasn't marked as  deleted) */
			continue;
		}

		/* Return a pre-existing superblock that is using `dev' */
		return iter;
	}
	return NULL;
}



/* Begin  opening a superblock for `dev'. If another superblock that has
 * yet to be marked as unmounted `FSUPER_MOUNTS_DELETED') already exists
 * that is mounting `dev', then  return a reference to that  superblock.
 * Otherwise, return `NULL'. If another mount operation is currently  in
 * progress for `dev', wait for that  one to finish before checking  for
 * existing superblocks for `dev' */
PRIVATE BLOCKING NONNULL((1)) REF struct fsuper *FCALL
fsuper_open_begin(struct mfile *__restrict dev)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	REF struct fsuper *existing;
	REF struct mfile **new_list;

	/* Must simultaneously acquire locks to `fallsuper_list' and `mount_in_progress_list'.
	 * Because  `mount_in_progress_list' uses an SMP-lock, we can safely acquire the later
	 * in a blocking manner after having already acquired the former. */
again:
	fallsuper_acquire();

	/* Check if one of the superblocks from the global list is using `dev' */
	existing = find_existing_superblock(dev);
	if unlikely(existing) {
		fallsuper_release();
		return existing;
	}

	/* Now acquire  the secondary  lock to  `mount_in_progress_list' (while  still
	 * holding a lock to `fallsuper_list', so-as to guaranty interlocked semantics
	 * when  it comes to  new superblocks being  added to `fallsuper_list', before
	 * being removed from `mount_in_progress_list' via `ffilesys_open_done()')
	 *
	 * Again: this can't deadlock because `mount_in_progress_lock' is an SMP-lock! */
	mount_in_progress_lock_acquire();
	if (mount_in_progress_contains(dev)) {
		mount_in_progress_lock_release_br();
		fallsuper_release();
		goto waitfor_dev_inprogress_end;
	}

	/* Reallocate the list of devices for which a mount is in progress. */
	new_list = (REF struct mfile **)krealloc_nx(mount_in_progress_list,
	                                            (mount_in_progress_count + 1) *
	                                            sizeof(REF struct mfile *),
	                                            GFP_ATOMIC);
	if (!new_list) {
		size_t newcount;
		newcount = mount_in_progress_count + 1;
		mount_in_progress_lock_release_br();
		fallsuper_release();

		/* Blocking-allocate a new list. */
		new_list = (REF struct mfile **)kmalloc(newcount * sizeof(REF struct mfile *), GFP_NORMAL);

again_lock_with_new_list:
		TRY {
			fallsuper_acquire();
		} EXCEPT {
			kfree(new_list);
			RETHROW();
		}

		/* Re-check for no pre-existing superblock. */
		existing = find_existing_superblock(dev);
		if unlikely(existing) {
			fallsuper_release();
			kfree(new_list);
			return existing;
		}

		/* Re-acquire a lock to the in-progress list. */
		mount_in_progress_lock_acquire_br();

		/* Re-check that the operation isn't already in-progress. */
		if unlikely(mount_in_progress_contains(dev)) {
			mount_in_progress_lock_release_br();
			fallsuper_release();
			kfree(new_list);
			goto waitfor_dev_inprogress_end;
		}

		/* Re-check that `newcount == mount_in_progress_count + 1' */
		if unlikely(newcount != mount_in_progress_count + 1) {
			newcount = mount_in_progress_count + 1;
			mount_in_progress_lock_release_br();
			fallsuper_release();
			TRY {
				new_list = (REF struct mfile **)krealloc(new_list,
				                                         newcount * sizeof(REF struct mfile *),
				                                         GFP_NORMAL);
			} EXCEPT {
				kfree(new_list);
				RETHROW();
			}
			goto again_lock_with_new_list;
		}

		/* Save the newly up-sized list. */
		mount_in_progress_list = new_list;
	}

	/* Append the new device. */
	new_list[mount_in_progress_count] = incref(dev);
	mount_in_progress_list            = new_list;
	++mount_in_progress_count;
	mount_in_progress_lock_release();
	fallsuper_release();

	/* Indicate that there was no already in-progress mount operation. */
	return NULL;

waitfor_dev_inprogress_end:
	/* Wait for an in-progress mount operation on `dev' to finish. */
	task_connect(&mount_in_progress_rmsig);
	mount_in_progress_lock_acquire();
	if unlikely(!mount_in_progress_contains(dev)) {
		mount_in_progress_lock_release_br();
		task_disconnectall();
		goto again;
	}
	mount_in_progress_lock_release();
	task_waitfor();
	goto again;
}

/* Must be called  after `ffilesys_open()'  returns with  `*pnewly_created = true'
 * while a non-NULL `dev' was given (the same `dev' also passed to this function),
 * and after the newly created superblock  has been added to `fallsuper_list',  or
 * was destroyed in case the open was aborted.
 *
 * This function will indicate that the given `dev' is no longer in the process of
 * being opened, allowing future/concurrent attempts  at opening this device as  a
 * superblock from no longer blocking. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ffilesys_open_done)(struct mfile *__restrict dev) {
	mount_in_progress_lock_acquire();
	assertf(mount_in_progress_count != 0, "No mounts in progress for _any_ files");
	if likely(mount_in_progress_count == 1) {
		REF struct mfile **old_list;
		/* Likely case: no concurrent mounting operations. */
		assertf(mount_in_progress_list[0] == dev,
		        "You're not the device for which a mount is in progress!");
		old_list = mount_in_progress_list;
		mount_in_progress_list  = NULL;
		mount_in_progress_count = 0;
		mount_in_progress_lock_release_br();

		/* Free the dynamically allocated list. */
		kfree(old_list);
		goto done;
	} else {
		size_t i;
		/* Find the index of `dev' */
		for (i = 0;; ++i) {
			assertf(i < mount_in_progress_count,
			        "That's not one of the devices for which a mount is in progress!");
			if (mount_in_progress_list[i] == dev)
				break;
		}
		/* Shift the list to get rid of `dev' */
		--mount_in_progress_count;
		memmovedown(&mount_in_progress_list[i],
		            &mount_in_progress_list[i + 1],
		            mount_in_progress_count - i,
		            sizeof(REF struct mfile *));
	}
	mount_in_progress_lock_release();

done:
	/* Wake up anything who might be waiting for opening to be done. */
	sig_broadcast(&mount_in_progress_rmsig);

	/* Reference from `mount_in_progress_list' (*_nokill because caller still has another ref) */
	decref_nokill(dev);
}



/* Open  a new superblock and return it.  This function is a high-level wrapper
 * around `ffs_open()' that does all of the fixed initialization of fields left
 * uninitialized by `ffs_open()' itself,  with the exception of  `fn_allsuper',
 * which is initialized as `LIST_ENTRY_UNBOUND_INIT()'.
 *
 * The returned superblock is _only_ visible to the caller, unless it's a singleton
 * superblock (`FFILESYS_F_SINGLE'), in which case the returned superblock is fully
 * initialized and its fields must _NOT_ be modified willy-nilly by the caller.
 *
 * WARNING: To safely deal with driver references in the case of singleton superblocks,
 *          the reference that is keeping `self'  alive (which is actually a  reference
 *          to  the backing driver)  may only be dropped  _AFTER_ path_mount() was used
 *          to mount the superblock (since the successful creation of a mounting  point
 *          will be holding a driver reference via `pathmount::pm_fsmount').
 *
 * NOTE: This function takes care to ensure that any given `dev' only ever gets
 *       mounted under a singular filesystem type (an existing fsuper for `dev'
 *       will always  be re-returned  unless its  `fs_mounts' had  been set  to
 *       `FSUPER_MOUNTS_DELETED').  If an existing  fsuper uses filesystem type
 *       other than `self', return `NULL'.
 *
 * @param: pnewly_created: Set to  true/false indicative  of  a new  superblock  having
 *                         been  opened.  When  set to  true,  `!isshared(return)', and
 *                         the caller must complete opening via `ffilesys_open_done()'.
 * @return: * :   The superblock that was opened.
 * @return: NULL: `FFILESYS_F_NODEV' isn't set, and `dev' cannot be mounted as a
 *                filesystem of this type.
 * @throw: E_FSERROR_MOUNT_UNSUPPORTED_DEVICE: `dev' cannot be used to mount superblocks.
 * @throw: E_FSERROR_CORRUPTED_FILE_SYSTEM:    The filesystem type was matched, but the on-disk
 *                                             filesystem  doesn't appear to make any sense. It
 *                                             looks like it's been corrupted... :( */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) REF struct fsuper *FCALL
ffilesys_open(struct ffilesys *__restrict self, bool *__restrict pnewly_created,
              struct mfile *dev, UNCHECKED USER char *args)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_MOUNT_UNSUPPORTED_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, ...) {
	REF struct fsuper *result;
	/* Check for special case: singleton */
	if (self->ffs_flags & FFILESYS_F_SINGLE) {
		*pnewly_created = false;
		assertf(ATOMIC_READ(self->ffs_single->fs_mounts.lh_first) != FSUPER_MOUNTS_DELETED,
		        "Singleton superblocks shouldn't be able to get marked as mounts-DELETED");
		return incref(self->ffs_single);
	}

	/* Open the superblock */
	if (self->ffs_flags & FFILESYS_F_NODEV) {
		dev    = NULL; /* Must be NULL in call */
		result = (*self->ffs_open)(self, dev, args);
	} else {
		REF struct fsuper *existing;
		assert(dev); /* Must be non-NULL in call */
		assert(dev->mf_iobashift <= dev->mf_blockshift);

		/* Need a device that implements at least a custom read-blocks operator,
		 * doesn't override the mmap or pread operators, and is set-up to  allow
		 * for user-I/O. */
		if unlikely(dev->mf_ops->mo_loadblocks == NULL) {
err_cannot_open_file:
			THROW(E_FSERROR_MOUNT_UNSUPPORTED_DEVICE);
		}
		if (dev->mf_ops->mo_stream != NULL) {
			if unlikely(dev->mf_ops->mo_stream->mso_pread != NULL ||
			            dev->mf_ops->mo_stream->mso_preadv != NULL ||
			            dev->mf_ops->mo_stream->mso_pwrite != NULL ||
			            dev->mf_ops->mo_stream->mso_pwritev != NULL)
				goto err_cannot_open_file;
			if unlikely(dev->mf_ops->mo_stream->mso_mmap)
				goto err_cannot_open_file;
		}
		if unlikely(dev->mf_flags & (MFILE_F_NOUSRIO | MFILE_F_NOUSRMMAP))
			goto err_cannot_open_file;

		/* Start opening a superblock */
		existing = fsuper_open_begin(dev);
		if unlikely(existing != NULL) {
			/* Another superblock is already mounting `dev' */
			if (existing->fs_sys == self) {
				*pnewly_created = false;
				return existing;
			}

			/* Different filesystem type -> indicate that
			 * a  different type is needed to open `dev'! */
			decref_unlikely(existing);
			return NULL;
		}

		TRY {
			/* With a device, we must ensure that it's size isn't
			 * truncated when trying to open it as a  superblock.
			 *
			 * This can simply be done by holding a trunc-lock,
			 * which  will be inherited  by the superblock upon
			 * success. */
			mfile_lock_write(dev);
			mfile_trunclock_inc(dev);
			mfile_lock_endwrite(dev);
			TRY {
				result = (*self->ffs_open)(self, dev, args);
			} EXCEPT {
				/* Release the trunc-lock if an exception was thrown. */
				mfile_trunclock_dec(dev);
				RETHROW();
			}
		} EXCEPT {
			ffilesys_open_done(dev);
			RETHROW();
		}
		if (result == NULL) {
			ffilesys_open_done(dev);

			/* Release the trunc-lock if the device couldn't be opened. */
			mfile_trunclock_dec(dev);
		}
	}

	if (result != NULL) {
		assert(result->fs_root.mf_iobashift <= result->fs_root.mf_blockshift);
		if (dev) {
			if (mfile_isdevice(dev)) {
				struct device *ddev = mfile_asdevice(dev);
				device_getname_lock_acquire(ddev);
				printk(KERN_INFO "[fs] Created %s-superblock bound to \"/dev/%#q\"\n",
					   self->ffs_name, device_getname(ddev));
				device_getname_lock_release(ddev);
			} else {
				printk(KERN_INFO "[fs] Created %s-superblock bound to [mfile]\n",
				       self->ffs_name);
			}

			/* Assign load-/save-blocks operators. */
			if unlikely(result->fs_root.mf_blockshift < dev->mf_blockshift ||
			            result->fs_root.mf_iobashift < dev->mf_iobashift) {
				printk(KERN_WARNING "[fs] %s-superblock sector-size/align (%" PRIuSIZ ", %" PRIuSIZ ") is less "
				                    "restrictive than device sector-size/align (%" PRIuSIZ ", v): "
				                    "direct I/O not possible\n",
				       self->ffs_name,
				       mfile_getblocksize(&result->fs_root), (size_t)1 << result->fs_root.mf_iobashift,
				       mfile_getblocksize(dev), (size_t)1 << dev->mf_iobashift);
				result->fs_loadblocks = &unaligned_v_loadblocks;
				result->fs_saveblocks = &unaligned_v_saveblocks;
			} else {
				result->fs_loadblocks = dev->mf_ops->mo_loadblocks;
				result->fs_saveblocks = dev->mf_ops->mo_saveblocks;
				if unlikely(result->fs_saveblocks == NULL)
					result->fs_saveblocks = &throw_readonly_v_saveblocks;
			}
		} else {
			printk(KERN_INFO "[fs] Created %s-superblock\n",
			       self->ffs_name);
			DBG_memset(&result->fs_loadblocks, 0xcc, sizeof(result->fs_loadblocks));
			DBG_memset(&result->fs_saveblocks, 0xcc, sizeof(result->fs_saveblocks));
		}

		/* Fill in fields as documented by `ffs_open' */
		assert(result->fs_root.mf_ops && ADDR_ISKERN(result->fs_root.mf_ops));
		assert(result->fs_root.mf_ops->mo_destroy != NULL);
		assertf(!(result->fs_root.mf_flags & ~(MFILE_F_READONLY | MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
		                                       MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE |
		                                       MFILE_F_NOATIME | MFILE_F_NOMTIME | MFILE_FN_NODIRATIME |
		                                       MFILE_F_STRICTATIME | MFILE_F_LAZYTIME | MFILE_F_PERSISTENT |
		                                       MFILE_FN_ATTRREADONLY | MFILE_F_ROFLAGS)),
		        "Only flags from this set may be set by fs-specific superblock open functions");
		assert(ADDR_ISKERN(result->fs_root.mf_ops->mo_destroy));
		result->fs_root.mf_refcnt = 1;
		atomic_rwlock_init(&result->fs_root.mf_lock);
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
		result->fs_root.mf_notify = NULL;
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
		sig_init(&result->fs_root.mf_initdone);
		SLIST_INIT(&result->fs_root.mf_lockops);
		SLIST_INIT(&result->fs_root.mf_changed);
		result->fs_root.mf_part_amask = MAX(PAGESIZE, 1 << result->fs_root.mf_blockshift) - 1;
		result->fs_root.mf_trunclock = 0;
		/*atomic64_init(&result->fs_root.mf_filesize, (uint64_t)-1);*/ /* Allowed to have custom values. */
		result->fs_root.mf_atime = realtime();
		result->fs_root.mf_mtime = result->fs_root.mf_atime;
		result->fs_root.mf_ctime = result->fs_root.mf_atime;
		result->fs_root.mf_btime = result->fs_root.mf_atime;
		result->fs_root.fn_nlink = 1;
		assert(S_ISDIR(result->fs_root.fn_mode)); /* Only . */
		result->fs_root.fn_uid   = 0;
		result->fs_root.fn_gid   = 0;
		result->fs_root.fn_super = result;
		LIST_ENTRY_UNBOUND_INIT(&result->fs_root.fn_changed);
		result->fs_root.fn_supent.rb_lhs = NULL;
		result->fs_root.fn_supent.rb_rhs = NULL;
		LIST_ENTRY_UNBOUND_INIT(&result->fs_root.fn_allsuper); /* Must eventually be initialized by the caller */
		result->fs_nodes = &result->fs_root;
		atomic_rwlock_init(&result->fs_nodeslock);
		SLIST_INIT(&result->fs_nodeslockops);
		LIST_INIT(&result->fs_mounts);
		atomic_rwlock_init(&result->fs_mountslock);
		SLIST_INIT(&result->fs_mountslockops);
		result->fs_sys = incref(self);
		result->fs_dev = xincref(dev); /* Also inherits the trunc-lock created above. */
		LIST_INIT(&result->fs_changednodes);
		atomic_lock_init(&result->fs_changednodes_lock);
		SLIST_INIT(&result->fs_changednodes_lops);
		LIST_ENTRY_UNBOUND_INIT(&result->fs_changedsuper);
		*pnewly_created = true;
	}
	return result;
}


/* tryincref() filesystem types starting with `start', and return
 * a reference to the first that's not been destroyed (if a  type
 * has been destroyed, try the next via `ffs_link') */
PRIVATE WUNUSED REF struct ffilesys *
NOTHROW(FCALL incref_first_nondestroyed)(struct ffilesys *__restrict start) {
	while (!tryincref(start)) {
		start = SLIST_NEXT(start, ffs_link);
		if (!start)
			break;
	}
	return start;
}

/* Return a reference to the filesystem type that comes after `prev'
 * When `prev == NULL', return the first filesystem type. Note  that
 * when `prev' has been unloaded, this function will also return the
 * first (still-registered) filesystem type. */
PUBLIC WUNUSED REF struct ffilesys *FCALL
ffilesys_next(struct ffilesys *prev) THROWS(E_WOULDBLOCK) {
	REF struct ffilesys *result;
	atomic_lock_acquire(&ffilesys_formats_lock);
	result = SLIST_FIRST(&ffilesys_formats_list);
	if (prev != NULL) {
		/* Return successor of `prev'; if not bound; return first.
		 * -> We can't rely on the link since the filesystem may
		 *    have since been  removed from the  global list  of
		 *    known filesystems. */
		bool ismember = false;
		SLIST_CONTAINS(&ffilesys_formats_list, prev, ffs_link, { ismember = true; });
		if (ismember)
			result = SLIST_NEXT(prev, ffs_link);
	}
	if likely(result != NULL)
		result = incref_first_nondestroyed(result);
	atomic_lock_release(&ffilesys_formats_lock);
	return result;
}

/* Helper wrapper for `ffilesys_open()' that blindly goes through all  filesystem
 * types and tries to open `dev' with each of those needing a device, that aren't
 * singleton filesystems.
 * @param: pnewly_created: Set to  true/false indicative  of  a new  superblock  having
 *                         been  opened.  When  set to  true,  `!isshared(return)', and
 *                         the caller must complete opening via `ffilesys_open_done()'.
 * @return: * :   The superblock that was opened.
 * @return: NULL: `dev' doesn't contain any known filesystem. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct fsuper *FCALL
ffilesys_opendev(bool *__restrict pnewly_created,
                 struct mfile *__restrict dev, UNCHECKED USER char *args)
		THROWS(E_BADALLOC, E_FSERROR_MOUNT_UNSUPPORTED_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, ...) {
	REF struct ffilesys *iter, *next;
	/* Enumerate filesystem types. */
	for (iter = NULL;;) {
		{
			FINALLY_XDECREF_UNLIKELY(iter);
			next = ffilesys_next(iter);
		}
		if (!next)
			break;
		iter = next;
		if (!(iter->ffs_flags & (FFILESYS_F_NODEV | FFILESYS_F_SINGLE))) {
			REF struct fsuper *result;
			TRY {
				/* Try to open with this filesystem type. */
				result = ffilesys_open(iter, pnewly_created, dev, args);
			} EXCEPT {
				decref_unlikely(iter);
				RETHROW();
			}
			if (result) {
				decref_unlikely(iter);
				return result;
			}
		}
	}
	return NULL;
}



/* Lookup a filesystem type, given its name.
 * @return: * :   The named filesystem type.
 * @return: NULL: No such filesystem. */
PUBLIC WUNUSED NONNULL((1)) REF struct ffilesys *FCALL
ffilesys_byname(USER CHECKED char const *name, size_t namelen)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	REF struct ffilesys *iter, *next;
	for (iter = NULL;;) {
		{
			FINALLY_XDECREF_UNLIKELY(iter);
			next = ffilesys_next(iter);
		}
		if (!next)
			break;
		iter = next;
		TRY {
			if (strcmpz(iter->ffs_name, name, namelen) == 0)
				return iter; /* Inherit reference */
		} EXCEPT {
			decref_unlikely(iter);
			RETHROW();
		}
	}
	return NULL;
}





/* Register a given filesystem format.
 * @return: true:  Success.
 * @return: false: The format was already registered. */
PUBLIC NONNULL((1)) bool FCALL
ffilesys_register(struct ffilesys *__restrict self)
		THROWS(E_WOULDBLOCK) {
	ffilesys_formats_acquire();
	SLIST_CONTAINS(&ffilesys_formats_list, self, ffs_link, {
		ffilesys_formats_release();
		return false;
	});
	self->_ffs_lop.lo_func = NULL; /* Needed for `ffilesys_unregister()' */
	SLIST_INSERT_HEAD(&ffilesys_formats_list, self, ffs_link);
	incref(self);
	ffilesys_formats_release();
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC ffilesys_unregister_postlop)(struct postlockop *__restrict self) {
	REF struct ffilesys *me;
	me = container_of(self, struct ffilesys, _ffs_plop);
	decref_unlikely(me);
}
PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC ffilesys_unregister_lop)(struct lockop *__restrict self) {
	REF struct ffilesys *me;
	me = container_of(self, struct ffilesys, _ffs_lop);
	SLIST_REMOVE(&ffilesys_formats_list, me, ffs_link);
	me->_ffs_plop.plo_func = &ffilesys_unregister_postlop;
	return &me->_ffs_plop;
}


/* Unregister a given filesystem format.
 * @return: true:  Success.
 * @return: false: The format wasn't registered. */
PUBLIC NONNULL((1)) bool
NOTHROW(FCALL ffilesys_unregister)(struct ffilesys *__restrict self) {
	if (!ATOMIC_CMPXCH(self->_ffs_lop.lo_func, NULL, &ffilesys_unregister_lop))
		return false;
	if (ffilesys_formats_tryacquire()) {
		SLIST_REMOVE(&ffilesys_formats_list, self, ffs_link);
		ffilesys_formats_release();
		decref_unlikely(self);
	} else {
		/* Remove asynchronously */
		lockop_enqueue(&ffilesys_formats_lops, &self->_ffs_lop);
		_ffilesys_formats_reap();
	}
	return true;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FILESYS_C */
