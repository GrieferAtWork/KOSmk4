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
#ifndef GUARD_KERNEL_CORE_FILESYS_FILESYS_C
#define GUARD_KERNEL_CORE_FILESYS_FILESYS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/super.h>
#include <kernel/printk.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except.h>

#include <assert.h>
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



/* Open  a new superblock and return it.  This function is a high-level wrapper
 * around `ffs_open()' that does all of the fixed initialization of fields left
 * uninitialized by `ffs_open()' itself,  with the exception of  `fn_allsuper',
 * which is initialized as `LIST_ENTRY_UNBOUND_INIT()'.
 *
 * The returned superblock is _only_ visible to the caller, unless it's a  singleton
 * superblock  (`FFILESYS_F_SINGLE'; iow:  is `devfs'),  in which  case the returned
 * superblock is fully initialized and its fields must _NOT_ be modified willy-nilly
 * by the caller.
 *
 * @return: * : isshared(return):  `FFILESYS_F_SINGLE' was set, and `return' must NOT
 *                                 be modified under a false assumption of you  being
 *                                 the only one using the superblock!
 * @return: * : !isshared(return): A new superblock was opened. The superblock has yet to
 *                                 be made globally  visible, and if  mounting should  be
 *                                 aborted, you can simply destroy() (or decref()) it.
 * @return: NULL: `FFILESYS_F_NODEV' isn't set, and `dev' cannot be mounted as a
 *                filesystem of this type. */
PUBLIC WUNUSED NONNULL((1)) REF struct fsuper *FCALL
ffilesys_open(struct ffilesys *__restrict self,
              struct blkdev *dev, UNCHECKED USER char *args)
		THROWS(E_BADALLOC) {
	REF struct fsuper *result;
	/* Check for special case: singleton */
	if (self->ffs_flags & FFILESYS_F_SINGLE)
		return incref(self->ffs_single);

	if (self->ffs_flags & FFILESYS_F_NODEV) {
		dev = NULL; /* Must be NULL in call */
	} else {
		assert(dev); /* Must be non-NULL in call */
	}

	/* Open the superblock */
	result = (*self->ffs_open)(self, dev, args);
	if (result != NULL) {
		printk(KERN_INFO "[fs] Created %s-superblock\n", self->ffs_name);

		/* Fill in fields as documented by `ffs_open' */
		assert(result->fs_root.mf_ops && ADDR_ISKERN(result->fs_root.mf_ops));
		assert(result->fs_root.mf_ops->mo_destroy != NULL);
		assertf(!(result->fs_root.mf_flags & ~(MFILE_F_READONLY | MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
		                                       MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE |
		                                       MFILE_F_NOATIME | MFILE_F_NOMTIME | MFILE_FN_NODIRATIME |
		                                       MFILE_F_STRICTATIME | MFILE_F_LAZYTIME |
		                                       MFILE_F_PERSISTENT | MFILE_FN_ATTRREADONLY)),
		        "Only flags from this set may be set by fs-specific superblock open functions");
		assert(ADDR_ISKERN(result->fs_root.mf_ops->mo_destroy));
		result->fs_root.mf_refcnt = 1;
		atomic_rwlock_init(&result->fs_root.mf_lock);
		sig_init(&result->fs_root.mf_initdone);
		SLIST_INIT(&result->fs_root.mf_lockops);
		SLIST_INIT(&result->fs_root.mf_changed);
		result->fs_root.mf_part_amask = MAX(PAGESIZE, 1 << result->fs_root.mf_blockshift) - 1;
		result->fs_root.mf_trunclock = 0;
		/*atomic64_init(&result->fs_root.mf_filesize, (uint64_t)-1);*/ /* Allowed to have custom values. */
		result->fs_root.mf_atime = realtime();
		result->fs_root.mf_mtime = result->fs_root.mf_atime;
		result->fs_root.mf_ctime = result->fs_root.mf_atime;
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
		result->fs_dev = (REF struct blkdev *)xincref(dev);
		LIST_INIT(&result->fs_changednodes);
		atomic_lock_init(&result->fs_changednodes_lock);
		SLIST_INIT(&result->fs_changednodes_lops);
		LIST_ENTRY_UNBOUND_INIT(&result->fs_changedsuper);
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
ffilesys_next(struct ffilesys *prev) {
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
 * @return: * :   @assume(!isshared(return));
 *                A new superblock was opened. The superblock has yet to
 *                be made globally  visible, and if  mounting should  be
 *                aborted, you can simply destroy() (or decref()) it.
 * @return: NULL: `dev' doesn't contain any known filesystem. */
PUBLIC WUNUSED NONNULL((1)) REF struct fsuper *FCALL
ffilesys_opendev(struct blkdev *dev, UNCHECKED USER char *args)
		THROWS(E_BADALLOC) {
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
				result = ffilesys_open(iter, dev, args);
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
