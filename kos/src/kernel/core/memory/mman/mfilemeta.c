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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILEMETA_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILEMETA_C 1
#define __WANT_DNOTIFY_LINK__dnl_fildead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/notify.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mfilemeta.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#ifndef __dnotify_link_slist_defined
#define __dnotify_link_slist_defined
SLIST_HEAD(dnotify_link_slist, dnotify_link);
#endif /* !__dnotify_link_slist_defined */
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */

/* Add `key' to the set of read-locks of `self' (caller must ensure that there is sufficient space)
 * @return: true:  Key added to set
 * @return: false: Key was already present in set */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL mfilemeta_flock_rl_addkey)(struct mfilemeta *__restrict self,
                                         mfile_flock_key_t key) {
	size_t i, perturb, hash;
	struct mfile_flock_rl_item *result_slot;
	/* Check for special case: the read-lock table is empty. */
	if (self->mfm_flock.mffl_rl_used <= 0)
		return false;

	hash = mfile_flock_key_gethash(key);
	i = perturb = mfile_flock_rl_hashst(&self->mfm_flock, hash);
	result_slot = NULL;
	for (;; mfile_flock_rl_hashnx(i, perturb)) {
		struct mfile_flock_rl_item *item;
		mfile_flock_key_t ikey;
		item = mfile_flock_rl_hashit(&self->mfm_flock, i);
		ikey = item->mfflri_key;
		if (ikey == MFILE_FLOCK_KEY_DELETED) {
			if (result_slot == NULL)
				result_slot = item;
			continue;
		}
		if (ikey == MFILE_FLOCK_KEY_SENTINEL) {
			if (result_slot == NULL)
				result_slot = item;
			break;
		}
		if (ikey == key)
			return false; /* Key was already present! */
	}

	/* Insert the key into `result_slot' */
	assert(result_slot);
	assert(result_slot->mfflri_key == MFILE_FLOCK_KEY_SENTINEL ||
	       result_slot->mfflri_key == MFILE_FLOCK_KEY_DELETED);
	if (result_slot->mfflri_key == MFILE_FLOCK_KEY_SENTINEL)
		++self->mfm_flock.mffl_rl_size;
	++self->mfm_flock.mffl_rl_used;
	result_slot->mfflri_key = key;
	return true;
}

/* Check if `key' is linked to a read-lock. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mfilemeta_flock_rl_haskey)(struct mfilemeta const *__restrict self,
                                         mfile_flock_key_t key) {
	size_t i, perturb, hash;
	/* Check for special case: the read-lock table is empty. */
	if (self->mfm_flock.mffl_rl_used <= 0)
		return false;

	hash = mfile_flock_key_gethash(key);
	i = perturb = mfile_flock_rl_hashst(&self->mfm_flock, hash);
	for (;; mfile_flock_rl_hashnx(i, perturb)) {
		struct mfile_flock_rl_item const *item;
		mfile_flock_key_t ikey;
		item = mfile_flock_rl_hashit(&self->mfm_flock, i);
		ikey = item->mfflri_key;
		if (ikey == MFILE_FLOCK_KEY_DELETED)
			continue; /* Skip already-deleted keys. */
		if (ikey == MFILE_FLOCK_KEY_SENTINEL)
			break; /* No such key... */
		if (ikey == key)
			return true; /* Found the key! */
	}
	return false;
}

/* Remove `key' from the set of read-lock keys. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mfilemeta_flock_rl_remkey)(struct mfilemeta *__restrict self,
                                         mfile_flock_key_t key) {
	size_t i, perturb, hash;
	/* Check for special case: the read-lock table is empty. */
	if (self->mfm_flock.mffl_rl_used <= 0)
		return false;

	hash = mfile_flock_key_gethash(key);
	i = perturb = mfile_flock_rl_hashst(&self->mfm_flock, hash);
	for (;; mfile_flock_rl_hashnx(i, perturb)) {
		struct mfile_flock_rl_item *item;
		mfile_flock_key_t ikey;
		item = mfile_flock_rl_hashit(&self->mfm_flock, i);
		ikey = item->mfflri_key;
		if (ikey == MFILE_FLOCK_KEY_DELETED)
			continue; /* Skip already-deleted keys. */
		if (ikey == MFILE_FLOCK_KEY_SENTINEL)
			return false; /* No such key... */
		if (ikey == key) {
			/* Found the key! */
			item->mfflri_key = MFILE_FLOCK_KEY_DELETED;
			break;
		}
	}
	assert(self->mfm_flock.mffl_rl_used);
	assert(self->mfm_flock.mffl_rl_size);
	assert(self->mfm_flock.mffl_rl_mask);
	--self->mfm_flock.mffl_rl_used;
	return true;
}


/* Try to trim unused space from the read-key set of `self' */
#define mfilemeta_flock_trim_rdkeys_and_unlock_klock(self) \
	_mfilemeta_flock_trim_rdkeys_and_unlock_klock(self, __hpsmp_pflag)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(FCALL _mfilemeta_flock_trim_rdkeys_and_unlock_klock)(struct mfilemeta *__restrict self,
                                                             __hybrid_preemption_flag_t __hpsmp_pflag) {
	/* TODO */
	mfile_flock_klock_release_br(&self->mfm_flock);
}


PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(FCALL mfile_flock_rl_item_rehash)(struct mfile_flock_rl_item *__restrict dst, size_t dst_mask,
                                          struct mfile_flock_rl_item *__restrict src, size_t src_mask) {
	size_t src_i;
	for (src_i = 0; src_i <= src_mask; ++src_i) {
		struct mfile_flock_rl_item *dst_slot;
		size_t i, perturb, hash;
		mfile_flock_key_t key;
		key  = src[src_i].mfflri_key;
		hash = mfile_flock_key_gethash(key);
		i = perturb = hash & dst_mask;
		dst_slot = NULL;
		for (;; mfile_flock_rl_hashnx(i, perturb)) {
			dst_slot = &dst[i & dst_mask];
			if (dst_slot->mfflri_key == MFILE_FLOCK_KEY_SENTINEL)
				break;
			assertf(dst_slot->mfflri_key != key,
			        "Duplicate key %p in src set",
			        key);
		}
		dst_slot->mfflri_key = key;
	}
}


/* Ensure that there is enough space for at least 1 more read-key in `self->mfm_flock'
 * @param: p_freeme: [in|out] Pointer to a memory location that will be kfree'd later.
 * @return: true:  Success (there is sufficient space)
 * @return: false: Success (there is sufficient space *now*, but the lock to `self' was briefly released) */
#define mfilemeta_flock_require_1_rdkey_or_unlock_klock(self, p_freeme) \
	_mfilemeta_flock_require_1_rdkey_or_unlock_klock(self, p_freeme, __hpsmp_pflag)
PRIVATE WUNUSED NONNULL((1, 2)) bool FCALL
_mfilemeta_flock_require_1_rdkey_or_unlock_klock(struct mfilemeta *__restrict self,
                                                 void **__restrict p_freeme,
                                                 __hybrid_preemption_flag_t __hpsmp_pflag)
		THROWS(E_BADALLOC) {
	bool result = true;
again:

	/* Check for special case: the read-key set is currently empty. */
	if (self->mfm_flock.mffl_rl_elem == NULL) {
		struct mfile_flock_rl_item *elem;
		assert(self->mfm_flock.mffl_rl_mask == 0);
		assert(self->mfm_flock.mffl_rl_size == 0);
		assert(self->mfm_flock.mffl_rl_used == 0);
		mfile_flock_klock_release_br(&self->mfm_flock);
		result = false;
		elem = (struct mfile_flock_rl_item *)kmalloc(2 * sizeof(struct mfile_flock_rl_item),
		                                             GFP_CALLOC);
		mfile_flock_klock_acquire_br(&self->mfm_flock);
		if (self->mfm_flock.mffl_rl_elem != NULL) {
			mfile_flock_klock_release_br(&self->mfm_flock);
			kfree(elem);
			mfile_flock_klock_acquire_br(&self->mfm_flock);
			goto again;
		}
		self->mfm_flock.mffl_rl_elem = elem;
		self->mfm_flock.mffl_rl_mask = 1;
		self->mfm_flock.mffl_rl_size = 0;
		self->mfm_flock.mffl_rl_used = 0;
	} else if (self->mfm_flock.mffl_rl_used < self->mfm_flock.mffl_rl_mask) {
		/* Simple case: there is still enough space for 1 more key */
	} else {
		/* Need to allocate a new hash-vector. */
		struct mfile_flock_rl_item *new_elem;
		size_t new_mask = 1;
		size_t old_used = self->mfm_flock.mffl_rl_used;
		while (old_used >= new_mask)
			new_mask = (new_mask << 1) | 1;
		mfile_flock_klock_release_br(&self->mfm_flock);
		result   = false;
		new_elem = (struct mfile_flock_rl_item *)kmalloc((new_mask + 1) *
		                                                 sizeof(struct mfile_flock_rl_item),
		                                                 GFP_CALLOC);
		if (*p_freeme != NULL) {
			kfree(*p_freeme);
			*p_freeme = NULL;
		}
		mfile_flock_klock_acquire_br(&self->mfm_flock);
		if (old_used != self->mfm_flock.mffl_rl_used) {
			mfile_flock_klock_release_br(&self->mfm_flock);
			kfree(new_elem);
			mfile_flock_klock_acquire_br(&self->mfm_flock);
			goto again;
		}

		/* Re-hash the key-set into the new hash-vector. */
		mfile_flock_rl_item_rehash(new_elem, new_mask,
		                           self->mfm_flock.mffl_rl_elem,
		                           self->mfm_flock.mffl_rl_mask);

		/* Remember the old hash-vector so it's free'd later. */
		*p_freeme = self->mfm_flock.mffl_rl_elem;

		/* Install the new hash-vector, which is known to have
		 * space for 1 extra read-key. */
		self->mfm_flock.mffl_rl_mask = new_mask;
		self->mfm_flock.mffl_rl_elem = new_elem;
		self->mfm_flock.mffl_rl_size = self->mfm_flock.mffl_rl_used;
	}
	return result;
}

/* Try to acquire a read-lock using `key' (also succeeds if `key' already holds a read-lock)
 * @return: true:  Success
 * @return: false: Operation would block */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
mfilemeta_flock_tryread(struct mfilemeta *__restrict self,
                        mfile_flock_key_t key)
		THROWS(E_BADALLOC) {
	void *freeme = NULL;
	mfile_flock_klock_acquire(&self->mfm_flock);
again:

	/* Check for special case: caller is holding a write-lock. */
	if (self->mfm_flock.mffl_wr_key == key) {
		/* Make sure that there is sufficient space for one more key in the read-key set. */
		if (!mfilemeta_flock_require_1_rdkey_or_unlock_klock(self, &freeme))
			goto again;
do_downgrade_writelock:
#ifdef NDEBUG
		(void)mfilemeta_flock_rl_addkey(self, key);
#else /* NDEBUG */
		bool already_present = mfilemeta_flock_rl_addkey(self, key);
		assertf(!already_present, "Then how can this also be the write-lock key?");
#endif /* !NDEBUG */
		self->mfm_flock.mffl_wr_key = MFILE_FLOCK_KEY_NONE;
		mfilemeta_flock_trim_rdkeys_and_unlock_klock(self);
		shared_rwlock_downgrade(&self->mfm_flock.mffl_flock);
		goto success;
	}

	/* Try to acquire a read-lock (note that this is an SMP-safe
	 * operation, so we don't  even need to drop  `mffl_klock'!) */
	if (!shared_rwlock_tryread(&self->mfm_flock.mffl_flock)) {
		mfilemeta_flock_trim_rdkeys_and_unlock_klock(self);
		kfree(freeme);
		return false;
	}

	/* Make sure there is enough space to add one more read-descriptor. */
	if (!mfilemeta_flock_require_1_rdkey_or_unlock_klock(self, &freeme)) {
		/* The internal k-lock had to be dropped temporarily.
		 * -> Check if we suddenly became the owner of a write-lock (unlikely) */
		if unlikely(self->mfm_flock.mffl_wr_key == key)
			goto do_downgrade_writelock;
		freeme = NULL;
	}

	/* Add the caller's key to the read-set. */
	if (!mfilemeta_flock_rl_addkey(self, key)) {
		/* Special case (unlikely): caller is already holding a read-key.
		 * -> In this case, trim the extra space we allocated, and drop the second read-lock we took. */
		mfilemeta_flock_trim_rdkeys_and_unlock_klock(self);
		shared_rwlock_endread(&self->mfm_flock.mffl_flock);
		goto success;
	}

	/* Read-lock successfully acquired! */
	mfile_flock_klock_release(&self->mfm_flock);
success:
	kfree(freeme);
	return true;
}


/* Try to acquire a write-lock using `key' (also succeeds if `key' already holds a write-lock)
 * @return: true:  Success
 * @return: false: Operation would block */
PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mfilemeta_flock_trywrite)(struct mfilemeta *__restrict self,
                                        mfile_flock_key_t key) {
	mfile_flock_klock_acquire(&self->mfm_flock);

	/* Check for special case: caller is already holding a write-lock. */
	if (self->mfm_flock.mffl_wr_key == key)
		goto success; /* No-op */

	/* Check if this is an upgrade-style operation. */
	if (mfilemeta_flock_rl_haskey(self, key)) {
		if (!shared_rwlock_tryupgrade(&self->mfm_flock.mffl_flock)) {
			mfile_flock_klock_release_br(&self->mfm_flock);
			return false; /* Operation would block */
		}

		/* Remove the read-key */
		(void)mfilemeta_flock_rl_remkey(self, key);

		/* Check if this caused the read-key set to become empty. */
		if (self->mfm_flock.mffl_rl_used == 0) {
			struct mfile_flock_rl_item *elem;

			/* Remember the key as being the owner of a write-lock. */
			assert(self->mfm_flock.mffl_wr_key == MFILE_FLOCK_KEY_NONE);
			self->mfm_flock.mffl_wr_key = key;

			/* No more read keys -> free the key set. */
			elem = self->mfm_flock.mffl_rl_elem;
			self->mfm_flock.mffl_rl_size = 0;
			self->mfm_flock.mffl_rl_mask = 0;
			self->mfm_flock.mffl_rl_elem = NULL;
			mfile_flock_klock_release_br(&self->mfm_flock);
			kfree(elem);
			return true;
		}
		/* Remember the key as being the owner of a write-lock. */
		assert(self->mfm_flock.mffl_wr_key == MFILE_FLOCK_KEY_NONE);
		self->mfm_flock.mffl_wr_key = key;
		mfilemeta_flock_trim_rdkeys_and_unlock_klock(self);
		return true;
	}

	/* No read-key present -> caller wants to directly switch to write-mode. */
	if (!shared_rwlock_trywrite(&self->mfm_flock.mffl_flock)) {
		mfile_flock_klock_release_br(&self->mfm_flock);
		return false;
	}

	/* Remember the key as being the owner of a write-lock. */
	assert(self->mfm_flock.mffl_wr_key == MFILE_FLOCK_KEY_NONE);
	self->mfm_flock.mffl_wr_key = key;
success:
	mfile_flock_klock_release(&self->mfm_flock);
	return true;
}

/* Acquire an flock-based lock to `self'. Note that an existing lock for `key'
 * is  always overwritten (when one already exists), and that if a lock of the
 * same type already exists for `key', the call is a no-op.
 * @param: self: The file on which to acquire the lock
 * @param: how:  One of `LOCK_SH', `LOCK_EX', optionally or'd with `LOCK_NB'
 * @param: key:  Lock key (needs to be passed to `mfile_flock_release')
 * @throws: E_WOULDBLOCK: The operation would block, and `LOCK_NB' was given
 * @throws: E_INTERRUPT:  [...]
 * @throws: E_BADALLOC:   [...]
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_FLOCK_COMMAND: [...] */
PUBLIC BLOCKING_IF(!(how & LOCK_NB)) NONNULL((1)) void FCALL
mfile_flock_acquire(struct mfile *__restrict self,
                    syscall_ulong_t how,
                    mfile_flock_key_t key)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC,
		       E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	struct mfilemeta *meta = mfile_getmeta(self);
	assert(key != MFILE_FLOCK_KEY_SENTINEL);
	assert(key != MFILE_FLOCK_KEY_DELETED);
	switch (how) {

	case LOCK_SH:
		/* Block-acquire a read-lock */
		assert(!task_wasconnected());
		while (!mfilemeta_flock_tryread(meta, key)) {
			task_connect(&meta->mfm_flock.mffl_flock.sl_rdwait);
			if unlikely(mfilemeta_flock_tryread(meta, key)) {
				task_disconnectall();
				break;
			}

			/* Wait for a reader to get woken. */
			task_waitfor();
		}
		break;

	case LOCK_SH | LOCK_NB:
		/* Try to acquire a read-lock */
		if (!mfilemeta_flock_tryread(meta, key))
			THROW(E_WOULDBLOCK);
		break;

	case LOCK_EX:
		/* Block-acquire a write-lock */
		assert(!task_wasconnected());
		while (!mfilemeta_flock_trywrite(meta, key)) {
			task_connect(&meta->mfm_flock.mffl_flock.sl_wrwait);
			if unlikely(mfilemeta_flock_trywrite(meta, key)) {
				task_disconnectall();
				break;
			}

			/* Wait for a writer to get woken. */
			task_waitfor();
		}
		break;

	case LOCK_EX | LOCK_NB:
		/* Try to acquire a write-lock */
		if (!mfilemeta_flock_trywrite(meta, key))
			THROW(E_WOULDBLOCK);
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_FLOCK_COMMAND,
		      how);
	}
}


/* Release an flock-based lock to `self'.
 * @return: true:  Lock was released
 * @return: false: No lock exists for `key' (note that this is a no-op in `LOCK_UN') */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mfile_flock_release)(struct mfile *__restrict self,
                                   mfile_flock_key_t key) {
	struct mfilemeta *meta = self->mf_meta;
	if unlikely(!meta)
		return false;
	assert(key != MFILE_FLOCK_KEY_SENTINEL);
	assert(key != MFILE_FLOCK_KEY_DELETED);
	mfile_flock_klock_acquire(&meta->mfm_flock);

	/* Check if `key' is the owner of a write-lock */
	if (meta->mfm_flock.mffl_wr_key == key) {
		meta->mfm_flock.mffl_wr_key = MFILE_FLOCK_KEY_NONE;
		mfile_flock_klock_release_br(&meta->mfm_flock);
		shared_rwlock_endwrite(&meta->mfm_flock.mffl_flock);
		return true;
	}

	/* Check if `key' is the owner of a read-lock */
	if (mfilemeta_flock_rl_remkey(meta, key)) {
		/* Special case: all read-locks are gone (clear the table). */
		if (meta->mfm_flock.mffl_rl_used == 0) {
			struct mfile_flock_rl_item *elem;
			elem = meta->mfm_flock.mffl_rl_elem;
			meta->mfm_flock.mffl_rl_size = 0;
			meta->mfm_flock.mffl_rl_mask = 0;
			meta->mfm_flock.mffl_rl_elem = NULL;
			mfile_flock_klock_release_br(&meta->mfm_flock);
			kfree(elem);
		} else {
			mfilemeta_flock_trim_rdkeys_and_unlock_klock(meta);
		}
		shared_rwlock_endread(&meta->mfm_flock.mffl_flock);
		return true;
	}

	/* No lock linked to `key' */
	mfile_flock_klock_release(&meta->mfm_flock);
	return false;
}





/* Destroy the given mfile meta-data `self' that was originally allocated & initialized for `file' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfilemeta_destroy)(struct mfilemeta *self,
                                 struct mfile *file) {
	(void)file;

	/* Clean up a notify controller if one is attached to the file. */
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	if (self->mfm_notify != NULL) {
		struct inotify_controller *notify;
		struct dnotify_link_slist deadlinks;
		COMPILER_READ_BARRIER();
		SLIST_INIT(&deadlinks);
		notify_lock_acquire();
		if ((notify = self->mfm_notify) != NULL) {
			assertf(LIST_EMPTY(&notify->inc_listeners),
			        "Per-file listeners should have kept us "
			        "alive via `notify_listener::nl_file'");
			assertf(!LIST_EMPTY(&notify->inc_dirs),
			        "If this was also empty, then the notify "
			        "controller should have already been freed!");
			assertf(notify->inc_file == file,
			        "Notify contrller of different file? (%p != %p)",
			        notify->inc_file, file);

			/* Remove the file from watched directories that contain it. */
			do {
				struct dnotify_link *link;
				link = LIST_FIRST(&notify->inc_dirs);
				assertf(dnotify_link_getfil(link) == notify,
				        "%p != %p",
				        dnotify_link_getfil(link), notify);
				LIST_REMOVE(link, dnl_fillink);
				dnotify_link_tree_removenode(&link->dnl_dir->dnc_files, link);
				DBG_memset(&link->dnl_dir, 0xcc, sizeof(link->dnl_dir));
				SLIST_INSERT(&deadlinks, link, _dnl_fildead);
			} while (!LIST_EMPTY(&notify->inc_dirs));
		}
		notify_lock_release();
		if (notify) {
			struct mfile_stream_ops const *stream;
			stream = file->mf_ops->mo_stream;
			/* Detach the notify file handle (if that operator is defined) */
			if (stream && stream->mso_notify_detach)
				(*stream->mso_notify_detach)(file, notify->inc_fhnd);
			inotify_controller_free(notify);
		}
		while (!SLIST_EMPTY(&deadlinks)) {
			struct dnotify_link *link;
			link = SLIST_FIRST(&deadlinks);
			SLIST_REMOVE_HEAD(&deadlinks, _dnl_fildead);
			dnotify_link_destroy(link);
		}
	}
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */

	/* Assert that there  are no more  flock keys  (since
	 * flock locks should have kept the file alive, whose
	 * destruction *must* have lead us here) */
	assert(self->mfm_flock.mffl_flock.sl_lock == 0);
	assert(self->mfm_flock.mffl_wr_key == MFILE_FLOCK_KEY_NONE);
	assert(self->mfm_flock.mffl_rl_mask == 0);
	assert(self->mfm_flock.mffl_rl_size == 0);
	assert(self->mfm_flock.mffl_rl_used == 0);
	assert(self->mfm_flock.mffl_rl_elem == NULL);

	/* Free the file meta-data controller. */
	mfilemeta_free(self);
}


/* Ensure that `self->mf_meta' has been allocated, which is then returned. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mfilemeta *FCALL
mfile_getmeta(struct mfile *__restrict self) THROWS(E_BADALLOC) {
	struct mfilemeta *result;
	/* Check if already allocated. */
	result = atomic_read(&self->mf_meta);
	if (result != NULL)
		return result;

	/* Allocate lazily */
	result = mfilemeta_alloc();
	mfilemeta_init(result, self);

	/* Install into the given file. */
	if likely(atomic_cmpxch(&self->mf_meta, NULL, result))
		return result;

	/* Race condition: another thread allocated also, and was faster than us! */
#ifdef MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT
	mfilemeta_free(result);
#else /* MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT */
	mfilemeta_destroy(result, self);
#endif /* !MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT */
	result = atomic_read(&self->mf_meta);
	assert(result != NULL);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILEMETA_C */
