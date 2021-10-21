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
#ifndef GUARD_KERNEL_CORE_FILESYS_FLAT_C
#define GUARD_KERNEL_CORE_FILESYS_FLAT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/flat.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except.h>

#include <assert.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Operators for `struct fflatdirent'. These are implemented
 * such that `fdo_opennode' invokes  `fflatsuper_opennode()' */
PUBLIC_CONST struct fdirent_ops const fflatdirent_ops = {
	.fdo_destroy  = &fflatdirent_v_destroy,
	.fdo_opennode = &fflatdirent_v_opennode,
};

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fflatdirent_v_destroy)(struct fdirent *__restrict self) {
	struct fflatdirent *me;
	me = fdirent_asflat(self);
	_fflatdirent_free(me);
}

PUBLIC WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
fflatdirent_v_opennode(struct fdirent *__restrict self,
                       struct fdirnode *__restrict dir_)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct fnode *result;
	struct fflatsuper *super;
	struct fflatdirent *me   = fdirent_asflat(self);
	struct fflatdirnode *dir = fdirnode_asflat(dir_);
again:
	fflatdirdata_read(&dir->fdn_data);

	/* Check for special case: `me' has been deleted. */
	if unlikely(fflatdirent_wasdeleted(me)) {
		fflatdirdata_endread(&dir->fdn_data);
		return NULL;
	}
	super = fsuper_asflat(dir->fn_super);

	/* Look through the node-cache of `super' */
	if (!fsuper_nodes_tryread(&super->ffs_super)) {
		fflatdirdata_endread(&dir->fdn_data);
		while (!fsuper_nodes_canread(&super->ffs_super))
			task_yield();
		goto again;
	}

	result = fsuper_nodes_locate(&super->ffs_super, me->fde_ent.fd_ino);
	if (result) {
		if (tryincref(result)) {
			if unlikely(result->mf_flags & MFILE_F_DELETED) {
				decref_unlikely(result);
			} else {
				/* Found it! (assert that the node's typing is correct) */
				assert(IFTODT(result->fn_mode) == me->fde_ent.fd_type);
				fsuper_nodes_endread(&super->ffs_super);
				fflatdirdata_endread(&dir->fdn_data);
				return result;
			}
		}

		if (!fsuper_nodes_tryupgrade(&super->ffs_super)) {
			fsuper_nodes_endread(&super->ffs_super);
			fflatdirdata_endread(&dir->fdn_data);
			goto again;
		}

		/* Unlink dead/deleted nodes... */
		fsuper_nodes_removenode(&super->ffs_super, result);
		ATOMIC_WRITE(result->fn_supent.rb_lhs, FSUPER_NODES_DELETED);
		fsuper_nodes_downgrade(&super->ffs_super);
	}

	/* Node doesn't exist in-cache. -> Create a new node. */
	fsuper_nodes_endread(&super->ffs_super);

#ifndef __OPTIMIZE_SIZE__
	/* Check if the nodes cache can be write-locked. - If not, then
	 * there's no point in doing any allocations since the  results
	 * are just going to be thrown away in any case! */
	if (!fsuper_nodes_canwrite(&super->ffs_super)) {
		fflatdirdata_endread(&dir->fdn_data);
		goto waitfor_super_nodes_lock;
#define NEED_waitfor_super_nodes_lock
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Invoke the superblock's `ffso_makenode' operator. */
	TRY {
		struct fflatsuper_ops const *ops;
		ops    = fflatsuper_getops(super);
		result = (*ops->ffso_makenode)(super, me, dir);
	} EXCEPT {
		fflatdirdata_endread(&dir->fdn_data);
		RETHROW();
	}

	/* Do common auxiliary initialization for both the success- and retry paths. */
	assertf(!(result->mf_flags & (MFILE_F_READONLY | MFILE_F_NOUSRMMAP |
	                              MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE |
	                              MFILE_FM_ATTRREADONLY)),
	        "As per documentation, `ffso_makenode()' may only set these flags!");
	result->mf_flags |= dir->mf_flags & (MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOMTIME);
	atomic_rwlock_init(&result->mf_lock);
	sig_init(&result->mf_initdone);
	SLIST_INIT(&result->mf_lockops);
	SLIST_INIT(&result->mf_changed);
	result->mf_part_amask = MAX(PAGESIZE, 1 << result->mf_blockshift) - 1;
	result->mf_trunclock  = 0;
	result->fn_ino        = me->fde_ent.fd_ino;
	result->fn_super      = incref(dir->_fdirnode_node_ fn_super);
	LIST_ENTRY_UNBOUND_INIT(&result->fn_changed);

	/* Re-acquire a lock to the nodes cache. */
	if (!fsuper_nodes_trywrite(&super->ffs_super)) {
		/* Nodes cache not available right now; unlock everything and try again. */
		fflatdirdata_endread(&dir->fdn_data);
		DBG_memset(&result->fn_supent, 0xcc, sizeof(result->fn_supent));
		result->fn_supent.rb_lhs = FSUPER_NODES_DELETED;
		LIST_ENTRY_UNBOUND_INIT(&result->fn_allnodes);
		result->mf_refcnt = 0;
		destroy(result);
#ifdef NEED_waitfor_super_nodes_lock
#undef NEED_waitfor_super_nodes_lock
waitfor_super_nodes_lock:
#endif /* NEED_waitfor_super_nodes_lock */
		while (!fsuper_nodes_canwrite(&super->ffs_super))
			task_yield();
		goto again;
	}

	/* Re-check that no node with this INode number already exists in-cache. */
	{
		struct fnode *existing;
		existing = fsuper_nodes_locate(&super->ffs_super, me->fde_ent.fd_ino);
		if unlikely(existing) {
			if (tryincref(existing)) {
				if (existing->mf_flags & MFILE_F_DELETED) {
					decref_unlikely(existing);
				} else {
					/* Race condition: someone else must have been faster than us... */
					assert(IFTODT(existing->fn_mode) == me->fde_ent.fd_type);
					fsuper_nodes_endwrite(&super->ffs_super);
					fflatdirdata_endread(&dir->fdn_data);
					DBG_memset(&result->fn_supent, 0xcc, sizeof(result->fn_supent));
					result->fn_supent.rb_lhs = FSUPER_NODES_DELETED;
					LIST_ENTRY_UNBOUND_INIT(&result->fn_allnodes);
					result->mf_refcnt = 0;
					destroy(result);
					return existing;
				}
			}
			/* Unlink dead/deleted nodes... */
			fsuper_nodes_removenode(&super->ffs_super, existing);
			ATOMIC_WRITE(existing->fn_supent.rb_lhs, FSUPER_NODES_DELETED);
		}
	}

	/* Fill in remaining fields of the new node. */
	result->mf_flags |= MFILE_FN_GLOBAL_REF;
	result->mf_refcnt = 2; /* +1: return, +1: MFILE_FN_GLOBAL_REF */

	/* Don't need to keep holding onto this lock! */
	fflatdirdata_endread(&dir->fdn_data);

	/* Insert into the nodes cache. */
	COMPILER_WRITE_BARRIER();
	fsuper_nodes_insert(&super->ffs_super, result); /* This initializes `result->fn_supent' */

	/* Make the new node globally visible whilst also initializing `fn_allnodes' */
	COMPILER_WRITE_BARRIER();
	fnode_init_add2all(result);

	/* Release  the write-lock  to the  nodes-cache _AFTER_  we made a
	 * call to `fnode_init_add2all()'. As documented by that function,
	 * it  may _ONLY_ be called for nodes that haven't become globally
	 * visible yet, and the moment we have anything other than a write
	 * lock to  `super->ffs_super.fs_changednodes_lock',  anyone  else
	 * will be able to find the new node via that cache! */
	fsuper_nodes_endwrite(&super->ffs_super);
	return result;
}







/* Default operators for `struct fflatdirnode'-derived directories. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fflatdirnode_v_destroy)(struct mfile *__restrict self) {
	struct fflatdirnode *me = mfile_asflatdir(self);
	fflatdirdata_fini(&me->fdn_data);
	fflatdirnode_v_destroy(self);
}

PRIVATE NOBLOCK void
NOTHROW(FCALL xdestroy_partially_initialized_flatdirent)(struct fflatdirent *self) {
	if (self) {
		self->fde_ent.fd_refcnt = 0;
		TAILQ_ENTRY_UNBOUND_INIT(&self->fde_bypos);
		destroy(self);
	}
}

PUBLIC WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
fflatdirnode_v_lookup(struct fdirnode *__restrict self,
                      struct flookup_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR) {
	bool upgrade_status;
	pos_t nextpos;
	REF struct fflatdirent *result;
	struct fflatdirnode *me = fdirnode_asflat(self);
again:
	fflatdirdata_read(&me->fdn_data);
	TRY {
		/* Look through the known cache of directory entries. */
		result = fflatdirnode_fileslist_lookup(me, info);
		if (result) {
			incref(result);
			fflatdirdata_endread(&me->fdn_data);
			return &result->fde_ent;
		}
	} EXCEPT {
		fflatdirdata_endread(&me->fdn_data);
		RETHROW();
	}

	/* Check if the entire directory has already been read. */
	if (me->fdn_data.fdd_goteof) {
		fflatdirdata_endread(&me->fdn_data);
		return NULL;
	}

	/* Read more entries. */
	nextpos = 0;
	result  = TAILQ_LAST(&me->fdn_data.fdd_bypos);
	if (result)
		nextpos = result->fde_pos + result->fde_size;

	/* Read the next entry. */
	TRY {
		struct fflatdirnode_ops const *ops;
		ops    = fflatdirnode_getops(me);
		result = (*ops->fdno_flat.fdnx_readdir)(me, nextpos);
	} EXCEPT {
		fflatdirdata_endread(&me->fdn_data);
		RETHROW();
	}
	assert(!result || result->fde_pos >= nextpos);

	/* Fill in missing fields. */
	result->fde_ent.fd_hash = fdirent_hash(result->fde_ent.fd_name, result->fde_ent.fd_namelen);
	TRY {
		upgrade_status = fflatdirdata_upgrade(&me->fdn_data);
	} EXCEPT {
		xdestroy_partially_initialized_flatdirent(result);
		RETHROW();
	}
	if (!upgrade_status) {
		/* Lock was lost; check if what we did above was all correct. */
		pos_t new_nextpos;
		REF struct fflatdirent *new_result;
		TRY {
			new_result = fflatdirnode_fileslist_lookup(me, info);
		} EXCEPT {
			fflatdirdata_endwrite(&me->fdn_data);
			xdestroy_partially_initialized_flatdirent(result);
			RETHROW();
		}
		if unlikely(new_result) {
			incref(new_result);
			fflatdirdata_endwrite(&me->fdn_data);
			xdestroy_partially_initialized_flatdirent(result);
			return &new_result->fde_ent;
		}
		/* Check if the position from which we read was correct. */
		new_nextpos = 0;
		new_result  = TAILQ_LAST(&me->fdn_data.fdd_bypos);
		if (new_result)
			new_nextpos = new_result->fde_pos + new_result->fde_size;
		if (nextpos != new_nextpos) {
			fflatdirdata_endwrite(&me->fdn_data);
			xdestroy_partially_initialized_flatdirent(result);
			goto again;
		}
	}

	/* Remember the newly read directory entry (or mark EOF) */
	if (!result) {
		me->fdn_data.fdd_goteof = true;
		fflatdirdata_endwrite(&me->fdn_data);
		return NULL;
	}
	/* Prepare the files hash-vector for the addition of another file. */
	TRY {
		fflatdirnode_fileslist_rehash_before_insert(me);
	} EXCEPT {
		fflatdirdata_endwrite(&me->fdn_data);
		xdestroy_partially_initialized_flatdirent(result);
		RETHROW();
	}

	/* Fill in missing fields of `result' */
	result->fde_ent.fd_refcnt = 2; /* +1: fdd_bypos, +1: return */

	/* Add the new directory entry to caches. */
	TAILQ_INSERT_TAIL(&me->fdn_data.fdd_bypos, result, fde_bypos);
	fflatdirnode_fileslist_insertent(me, result);

	/* Release locks and we're done! */
	fflatdirdata_endwrite(&me->fdn_data);
	return &result->fde_ent;
}


PUBLIC NONNULL((1)) void KCALL
fflatdirnode_v_enum(struct fdirenum *__restrict result) {
	struct fflatdirnode *me = fdirnode_asflat(result->de_dir);

	/* TODO */
}


PUBLIC WUNUSED NONNULL((1, 2)) unsigned int KCALL
fflatdirnode_v_mkfile(struct fdirnode *__restrict self,
                      struct fmkfile_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION) {
	struct fflatdirnode *me = fdirnode_asflat(self);
	/* TODO */
}


PUBLIC WUNUSED NONNULL((1, 2, 3)) unsigned int KCALL
fflatdirnode_v_unlink(struct fdirnode *__restrict self,
                      struct fdirent *__restrict entry,
                      struct fnode *__restrict file)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY) {
	struct fflatdirnode *me = fdirnode_asflat(self);
	/* TODO */
}


PUBLIC WUNUSED NONNULL((1, 2)) unsigned int KCALL
fflatdirnode_v_rename(struct fdirnode *__restrict self,
                      struct frename_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY) {
	struct fflatdirnode *me = fdirnode_asflat(self);
	/* TODO */
}



/* Finalize the given flat directory data container. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fflatdirdata_fini)(struct fflatdirdata *__restrict self) {
	REF struct fflatdirent *iter;

	/* Drop references from cached directory entries. */
	TAILQ_FOREACH_SAFE (iter, &self->fdd_bypos, fde_bypos)
		decref_unlikely(iter);

	/* Free the hash-vector (if dynamically allocated) */
	if (self->fdd_fileslist != fflatdir_empty_buckets)
		kfree(self->fdd_fileslist);
}


#ifndef CONFIG_FFLATDIR_FILESLIST_INITIAL_MASK
#define CONFIG_FFLATDIR_FILESLIST_INITIAL_MASK 7
#endif /* !CONFIG_FFLATDIR_FILESLIST_INITIAL_MASK */

PRIVATE struct fflatdirent deleted_flat_dirent = {
	.fde_pos   = 0,
	.fde_size  = 0,
	.fde_bypos = TAILQ_ENTRY_UNBOUND_INITIALIZER,
	.fde_ent = {
		.fd_refcnt  = 1,
		.fd_ops     = &fdirent_empty_ops,
		.fd_ino     = 0,
		.fd_hash    = FDIRENT_EMPTY_HASH,
		.fd_namelen = 0,
		.fd_type    = DT_UNKNOWN,
		.fd_name    = "",
	},
};

DATDEF struct fflatdir_bucket const _fflatdir_empty_buckets[1] ASMNAME("fflatdir_empty_buckets");
PUBLIC_CONST struct fflatdir_bucket const _fflatdir_empty_buckets[1] = { { NULL } };

/* Helper functions for adding/removing directory entries  to the files list of  `self'
 * These functions _ONLY_ modify `fdd_fileslist' and friends; the caller is responsible
 * for `fdd_bypos', as well as to be holding a lock to `self->fdn_data.fdd_lock'. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL fflatdirnode_fileslist_removeent)(struct fflatdirnode *__restrict self,
                                                struct fflatdirent *__restrict ent) {
	uintptr_t hash, i, perturb;
	struct fflatdir_bucket *bucket;
	assert(self->fdn_data.fdd_fileslist != fflatdir_empty_buckets);
	assert(self->fdn_data.fdd_filesused != 0);
	assert(self->fdn_data.fdd_filessize != 0);
	assert((self->fdn_data.fdd_filessize + 1) <= self->fdn_data.fdd_filesmask);
	hash = fflatdirent_hashof(ent);
	i = perturb = hash & self->fdn_data.fdd_filesmask;
	for (;; fflatdirent_hashnx(i, perturb)) {
		bucket = &self->fdn_data.fdd_fileslist[i & self->fdn_data.fdd_filesmask];
		assert(bucket->ffdb_ent != NULL);
		if (bucket->ffdb_ent == ent)
			break;
	}
	bucket->ffdb_ent = &deleted_flat_dirent;
	--self->fdn_data.fdd_filesused;
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL fflatdirnode_fileslist_insertent)(struct fflatdirnode *__restrict self,
                                                struct fflatdirent *__restrict ent) {
	uintptr_t hash, i, perturb;
	struct fflatdir_bucket *bucket;
	assert((self->fdn_data.fdd_filessize + 1) <= self->fdn_data.fdd_filesmask);
	hash = fflatdirent_hashof(ent);
	i = perturb = hash & self->fdn_data.fdd_filesmask;
	for (;; fflatdirent_hashnx(i, perturb)) {
		struct fflatdirent *pth;
		bucket = &self->fdn_data.fdd_fileslist[i & self->fdn_data.fdd_filesmask];
		pth    = bucket->ffdb_ent;
		if (!pth) {
			/* Found a free slot */
			++self->fdn_data.fdd_filessize;
			break;
		}
		if (pth == &deleted_flat_dirent)
			break; /* Re-use a previously deleted slot. */
	}
	bucket->ffdb_ent = ent;
	++self->fdn_data.fdd_filesused;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fflatdirnode_fileslist_rehash_with)(struct fflatdirnode *__restrict self,
                                                  struct fflatdir_bucket *__restrict new_list,
                                                  size_t new_mask) {
	/* Rehash existing entries. */
	uintptr_t i, j, perturb;
	assert(new_mask >= self->fdn_data.fdd_filesused);
	for (i = 0; i <= self->fdn_data.fdd_filesmask; ++i) {
		struct fflatdir_bucket *dst;
		struct fflatdirent *pth;
		uintptr_t hash;
		pth = self->fdn_data.fdd_fileslist[i].ffdb_ent;
		if (!pth || pth == &deleted_flat_dirent)
			continue; /* Empty, or deleted. */
		hash = fflatdirent_hashof(pth);
		j = perturb = hash & new_mask;
		for (;; fflatdirent_hashnx(j, perturb)) {
			dst = &new_list[j & new_mask];
			if (!dst->ffdb_ent)
				break;
		}
		dst->ffdb_ent = pth; /* Rehash */
	}
	kfree(self->fdn_data.fdd_fileslist);
	self->fdn_data.fdd_fileslist = new_list;
	self->fdn_data.fdd_filesmask = new_mask;
	self->fdn_data.fdd_filessize = self->fdn_data.fdd_filesused; /* All deleted entries were removed... */
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fflatdirnode_fileslist_rehash_after_remove)(struct fflatdirnode *__restrict self) {
	if ((self->fdn_data.fdd_filesused < (self->fdn_data.fdd_filesmask / 3)) &&
	    self->fdn_data.fdd_filesmask > CONFIG_FFLATDIR_FILESLIST_INITIAL_MASK) {
		/* Try to shrink the hash-vector's mask size. */
		size_t new_mask = CONFIG_FFLATDIR_FILESLIST_INITIAL_MASK;
		size_t thresh   = ((self->fdn_data.fdd_filesused + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		if (new_mask < self->fdn_data.fdd_filesmask) {
			/* Try to shrink */
			struct fflatdir_bucket *new_list;
			new_list = (struct fflatdir_bucket *)kmalloc_nx((new_mask + 1) *
			                                                sizeof(struct fflatdir_bucket),
			                                                GFP_ATOMIC | GFP_CALLOC);
			/* If the alloc worked, re-hash using `new_list' */
			if (new_list)
				fflatdirnode_fileslist_rehash_with(self, new_list, new_mask);
		}
	}
}

PUBLIC NONNULL((1)) void FCALL
fflatdirnode_fileslist_rehash_before_insert(struct fflatdirnode *__restrict self)
		THROWS(E_BADALLOC) {
	if (((self->fdn_data.fdd_filessize + 1) * 3) / 2 >= self->fdn_data.fdd_filesmask) {
		/* Must rehash! */
		struct fflatdir_bucket *new_list;
		size_t new_mask = CONFIG_FFLATDIR_FILESLIST_INITIAL_MASK;
		size_t thresh   = ((self->fdn_data.fdd_filesused + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		new_list = (struct fflatdir_bucket *)kmalloc_nx((new_mask + 1) *
		                                                sizeof(struct fflatdir_bucket),
		                                                GFP_CALLOC);
		if unlikely(!new_list) {
			if ((self->fdn_data.fdd_filessize + 1) <= self->fdn_data.fdd_filesmask)
				return;
			new_mask = CONFIG_FFLATDIR_FILESLIST_INITIAL_MASK;
			while ((self->fdn_data.fdd_filesused + 1) > self->fdn_data.fdd_filesmask)
				new_mask = (new_mask << 1) | 1;
			new_list = (struct fflatdir_bucket *)kmalloc((new_mask + 1) *
			                                             sizeof(struct fflatdir_bucket),
			                                             GFP_CALLOC);
		}
		/* Rehash using the new list. */
		fflatdirnode_fileslist_rehash_with(self, new_list, new_mask);
		assert(self->fdn_data.fdd_filesused == self->fdn_data.fdd_filessize);
	}
}

/* Lookup the named entry, returning `NULL' if not found. */
PUBLIC NOBLOCK NONNULL((1, 2)) struct fflatdirent *FCALL
fflatdirnode_fileslist_lookup(struct fflatdirnode *__restrict self,
                              struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT) {
	uintptr_t i, perturb;

	/* Search through the hash-table. */
	if (info->flu_hash == FLOOKUP_INFO_HASH_UNSET)
		info->flu_hash = fdirent_hash(info->flu_name, info->flu_namelen);

	assert((self->fdn_data.fdd_filessize + 1) <= self->fdn_data.fdd_filesmask);
	i = perturb = info->flu_hash & self->fdn_data.fdd_filesmask;
	for (;; fflatdirent_hashnx(i, perturb)) {
		struct fflatdirent *result;
		result = self->fdn_data.fdd_fileslist[i & self->fdn_data.fdd_filesmask].ffdb_ent;
		if (!result)
			break; /* No such monitor... */
		if (result->fde_ent.fd_hash != info->flu_hash)
			continue; /* Wrong hash */
		if unlikely(result->fde_ent.fd_namelen != info->flu_namelen)
			continue; /* Wrong name length */
		if unlikely(memcmp(result->fde_ent.fd_name, info->flu_name,
		                   info->flu_namelen * sizeof(char)) != 0)
			continue; /* Wrong name */
		if unlikely(result == &deleted_flat_dirent)
			continue; /* Prevent any chance of *this* happening... */
		/* Found it! */
		return result;
	}

	/* If requested, also perform a case-insensitive search */
	if (info->flu_flags & AT_DOSPATH) {
		for (i = 0; i <= self->fdn_data.fdd_filesmask; ++i) {
			struct fflatdirent *result = self->fdn_data.fdd_fileslist[i].ffdb_ent;
			if (!result)
				continue;
			if unlikely(result->fde_ent.fd_namelen != info->flu_namelen)
				continue; /* Wrong name length */
			if unlikely(memcasecmp(result->fde_ent.fd_name, info->flu_name,
			                       info->flu_namelen * sizeof(char)) != 0)
				continue; /* Wrong name */
			if unlikely(result == &deleted_flat_dirent)
				continue; /* Prevent any chance of *this* happening... */
			/* Found it! */
			return result;
		}
	}

	/* Nope; don't know anything about this one... */
	return NULL;
}

/* Remove the named entry, returning `NULL' if not found.
 * Same as `fflatdirnode_fileslist_lookup' + `fflatdirnode_fileslist_removeent' */
PUBLIC NOBLOCK NONNULL((1, 2)) struct fflatdirent *FCALL
fflatdirnode_fileslist_remove(struct fflatdirnode *__restrict self,
                              struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT) {
	uintptr_t i, perturb;

	/* Search through the hash-table. */
	if (info->flu_hash == FLOOKUP_INFO_HASH_UNSET)
		info->flu_hash = fdirent_hash(info->flu_name, info->flu_namelen);

	assert((self->fdn_data.fdd_filessize + 1) <= self->fdn_data.fdd_filesmask);
	i = perturb = info->flu_hash & self->fdn_data.fdd_filesmask;
	for (;; fflatdirent_hashnx(i, perturb)) {
		struct fflatdir_bucket *bucket;
		struct fflatdirent *result;
		bucket = &self->fdn_data.fdd_fileslist[i & self->fdn_data.fdd_filesmask];
		result = bucket->ffdb_ent;
		if (!result)
			break; /* No such monitor... */
		if (result->fde_ent.fd_hash != info->flu_hash)
			continue; /* Wrong hash */
		if unlikely(result->fde_ent.fd_namelen != info->flu_namelen)
			continue; /* Wrong name length */
		if unlikely(memcmp(result->fde_ent.fd_name, info->flu_name,
		                   info->flu_namelen * sizeof(char)) != 0)
			continue; /* Wrong name */
		if unlikely(result == &deleted_flat_dirent)
			continue; /* Prevent any chance of *this* happening... */
		/* Found it! */
		bucket->ffdb_ent = &deleted_flat_dirent;
		--self->fdn_data.fdd_filesused;
		return result;
	}

	/* If requested, also perform a case-insensitive search */
	if (info->flu_flags & AT_DOSPATH) {
		for (i = 0; i <= self->fdn_data.fdd_filesmask; ++i) {
			struct fflatdir_bucket *bucket;
			struct fflatdirent *result;
			bucket = &self->fdn_data.fdd_fileslist[i];
			result = bucket->ffdb_ent;
			if (!result)
				continue;
			if unlikely(result->fde_ent.fd_namelen != info->flu_namelen)
				continue; /* Wrong name length */
			if unlikely(memcasecmp(result->fde_ent.fd_name, info->flu_name,
			                       info->flu_namelen * sizeof(char)) != 0)
				continue; /* Wrong name */
			if unlikely(result == &deleted_flat_dirent)
				continue; /* Prevent any chance of *this* happening... */
			/* Found it! */
			bucket->ffdb_ent = &deleted_flat_dirent;
			--self->fdn_data.fdd_filesused;
			return result;
		}
	}

	/* Nope; don't know anything about this one... */
	return NULL;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FLAT_C */
