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
#define __WANT_FNODE__fn_suplop
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/flat.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

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
	fflatdirnode_read(dir);

	/* Check for special case: `me' has been deleted. */
	if unlikely(fflatdirent_wasdeleted(me)) {
		fflatdirnode_endread(dir);
		return NULL;
	}
	super = fsuper_asflat(dir->fn_super);

	/* Look through the node-cache of `super' */
	if (!fsuper_nodes_tryread(&super->ffs_super)) {
		fflatdirnode_endread(dir);
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
				fflatdirnode_endread(dir);
				return result;
			}
		}

		if (!fsuper_nodes_tryupgrade(&super->ffs_super)) {
			fsuper_nodes_endread(&super->ffs_super);
			fflatdirnode_endread(dir);
			goto again;
		}

		/* Unlink dead/deleted nodes... */
		fsuper_nodes_removenode(&super->ffs_super, result);
		ATOMIC_WRITE(result->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
		fsuper_nodes_downgrade(&super->ffs_super);
	}

	/* Node doesn't exist in-cache. -> Create a new node. */
	_fsuper_nodes_endread(&super->ffs_super);

	/* Deal with nodes that async-add themselves to the cache. */
	if (fsuper_nodes_mustreap(&super->ffs_super)) {
		_fsuper_nodes_reap(&super->ffs_super);
		goto again;
	}

#ifndef __OPTIMIZE_SIZE__
	/* Check if the nodes cache can be write-locked. - If not, then
	 * there's no point in doing any allocations since the  results
	 * are just going to be thrown away in any case! */
	if (!fsuper_nodes_canwrite(&super->ffs_super)) {
		fflatdirnode_endread(dir);
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
		fflatdirnode_endread(dir);
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
again_lockwrite_super_nodes:
	if (!fsuper_nodes_trywrite(&super->ffs_super)) {
		/* Nodes cache not available right now; unlock everything and try again. */
		fflatdirnode_endread(dir);
		DBG_memset(&result->fn_supent, 0xcc, sizeof(result->fn_supent));
		result->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
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
		if unlikely(existing != NULL) {
			if (tryincref(existing)) {
				if (existing->mf_flags & MFILE_F_DELETED) {
					decref_unlikely(existing);
				} else {
					/* Race condition: someone else must have been faster than us... */
					assert(IFTODT(existing->fn_mode) == me->fde_ent.fd_type);
					fsuper_nodes_endwrite(&super->ffs_super);
					fflatdirnode_endread(dir);
					DBG_memset(&result->fn_supent, 0xcc, sizeof(result->fn_supent));
					result->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
					LIST_ENTRY_UNBOUND_INIT(&result->fn_allnodes);
					result->mf_refcnt = 0;
					destroy(result);
					return existing;
				}
			}
			/* Unlink dead/deleted nodes... */
			fsuper_nodes_removenode(&super->ffs_super, existing);
			ATOMIC_WRITE(existing->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
		} /* if (existing != NULL) */
	} /* Scope... */

	/* Deal with nodes that async-add themselves to the cache. */
	if unlikely(fsuper_nodes_mustreap(&super->ffs_super)) {
		_fsuper_nodes_endwrite(&super->ffs_super);
		_fsuper_nodes_reap(&super->ffs_super);
		goto again_lockwrite_super_nodes;
	}

	/* Fill in remaining fields of the new node. */
	result->mf_flags |= MFILE_FN_GLOBAL_REF;
	result->mf_refcnt = 2; /* +1: return, +1: MFILE_FN_GLOBAL_REF */

	/* Don't need to keep holding onto this lock! */
	fflatdirnode_endread(dir);

	/* Insert into the nodes cache. */
	COMPILER_WRITE_BARRIER();
	fsuper_nodes_insert(&super->ffs_super, result); /* This initializes `result->fn_supent' */

	/* Make the new node globally visible whilst also initializing `fn_allnodes' */
	COMPILER_WRITE_BARRIER();
	fnode_init_addtoall(result);

	/* Release the  write-lock to  the nodes-cache  _AFTER_ we  made  a
	 * call to `fnode_init_addtoall()'. As documented by that function,
	 * it may _ONLY_ be called  for nodes that haven't become  globally
	 * visible yet, and the moment we have anything other than a  write
	 * lock  to  `super->ffs_super.fs_changednodes_lock',  anyone  else
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

#define destroy_partially_initialized_flatdirent xdestroy_partially_initialized_flatdirent
PRIVATE NOBLOCK void
NOTHROW(FCALL xdestroy_partially_initialized_flatdirent)(struct fflatdirent *self) {
	if (self) {
		self->fde_ent.fd_refcnt = 0;
		TAILQ_ENTRY_UNBOUND_INIT(&self->fde_bypos);
		destroy(self);
	}
}



/* Anonymize all mem-parts living beyond `threshold' */
PRIVATE NONNULL((1)) void
NOTHROW(KCALL fflatdirnode_anon_parts_after)(struct mfile *__restrict self,
                                             pos_t threshold) {
	(void)self;
	(void)threshold;
	COMPILER_IMPURE();
	/* XXX: Implement me? (Not strictly required, but still kind-of necessary function)
	 *      Without  this, the underlying mem-parts of large directories can't be freed
	 *      as files are removed from the directory.
	 * XXX: As a matter of  fact: this shouldn't only  happen when removing from  the
	 *      end of a directory; it should happen no matter where the removal is done,
	 *      and unload all parts bound to address ranges consisting only of gaps! */
}


/* Helper  wrapper for `fdnx_deleteent'  that will follow  up the call by
 * anonymizing any mpart-s of the mfile underlying `self' only containing
 * data after `fflatdirent_endaddr(ent)' */
PRIVATE NONNULL((1, 2)) void KCALL
fflatdirnode_delete_entry(struct fflatdirnode *__restrict self,
                          struct fflatdirent const *__restrict ent,
                          bool at_end_of_dir) {
	TRY {
		(*fflatdirnode_getops(self)->fdno_flat.fdnx_deleteent)(self, ent, at_end_of_dir);
	} EXCEPT {
		if (at_end_of_dir)
			fflatdirnode_anon_parts_after(self, fflatdirent_endaddr(ent));
		RETHROW();
	}
	if (at_end_of_dir)
		fflatdirnode_anon_parts_after(self, fflatdirent_endaddr(ent));
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
	fflatdirnode_read(me);
	TRY {
		/* Look through the known cache of directory entries. */
		result = fflatdirnode_fileslist_lookup(me, info);
		if (result) {
			incref(result);
			fflatdirnode_endread(me);
			return &result->fde_ent;
		}
	} EXCEPT {
		fflatdirnode_endread(me);
		RETHROW();
	}

	/* Check if the entire directory has already been read. */
	if (me->fdn_data.fdd_flags & FFLATDIR_F_EOF) {
		fflatdirnode_endread(me);
		return NULL;
	}

	/* Read more entries. */
	nextpos = 0;
	result  = TAILQ_LAST(&me->fdn_data.fdd_bypos);
	if (result)
		nextpos = fflatdirent_endaddr(result);

	/* Read the next entry. */
	TRY {
		struct fflatdirnode_ops const *ops;
		ops    = fflatdirnode_getops(me);
		result = (*ops->fdno_flat.fdnx_readdir)(me, nextpos);
	} EXCEPT {
		fflatdirnode_endread(me);
		RETHROW();
	}
	assert(!result || fflatdirent_basaddr(result) >= nextpos);

	/* Fill in missing fields. */
	if (result) {
		result->fde_ent.fd_hash = fdirent_hash(result->fde_ent.fd_name,
		                                       result->fde_ent.fd_namelen);
	}
	TRY {
		upgrade_status = fflatdirnode_upgrade(me);
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
			fflatdirnode_endwrite(me);
			xdestroy_partially_initialized_flatdirent(result);
			RETHROW();
		}
		if unlikely(new_result) {
			incref(new_result);
			fflatdirnode_endwrite(me);
			xdestroy_partially_initialized_flatdirent(result);
			return &new_result->fde_ent;
		}
		/* Check if the position from which we read was correct. */
		new_nextpos = 0;
		new_result  = TAILQ_LAST(&me->fdn_data.fdd_bypos);
		if (new_result)
			new_nextpos = fflatdirent_endaddr(new_result);
		if (nextpos != new_nextpos) {
			fflatdirnode_endwrite(me);
			xdestroy_partially_initialized_flatdirent(result);
			goto again;
		}
	}

	/* Remember the newly read directory entry (or mark EOF) */
handle_result_after_wrlock:
	if (!result) {
		me->fdn_data.fdd_flags |= FFLATDIR_F_EOF;
		fflatdirnode_endwrite(me);
		return NULL;
	}

	/* Prepare the files hash-vector for the addition of another file. */
	TRY {
		fflatdirnode_fileslist_rehash_before_insert(me);
	} EXCEPT {
		fflatdirnode_endwrite(me);
		destroy_partially_initialized_flatdirent(result);
		RETHROW();
	}

	/* Fill in missing fields of `result' */
	result->fde_ent.fd_refcnt = 2; /* +1: fdd_bypos, +1: return */

	/* Add the new directory entry to caches. */
	if unlikely(!fflatdirnode_fileslist_tryinsertent(me, result)) {
		/* oops. That's a duplicate entry... */
		struct fflatdirnode_ops const *ops;
		struct fflatdirent *next_result = NULL;
		ops = fflatdirnode_getops(me);
		TRY {
			next_result = (*ops->fdno_flat.fdnx_readdir)(me, fflatdirent_endaddr(result));
			assert(!next_result || fflatdirent_basaddr(next_result) >= fflatdirent_endaddr(result));
			if (next_result) {
				next_result->fde_ent.fd_hash = fdirent_hash(next_result->fde_ent.fd_name,
				                                            next_result->fde_ent.fd_namelen);
			}
			if (ops->fdno_flat.fdnx_deleteent && !(me->mf_flags & MFILE_F_READONLY)) {
				/* Delete any directory entry with a duplicate name.
				 * NOTE: Because duplicate names  shouldn't happen at  all,
				 *       don't bother trying to decrement the NLINK counter
				 *       in  this case; minimize further corruption by only
				 *       "fixing" imminent errors. */
				fflatdirnode_delete_entry(me, result, next_result == NULL);
			} else {
				nextpos = fflatdirent_endaddr(result);
			}
		} EXCEPT {
			fflatdirnode_endwrite(me);
			xdestroy_partially_initialized_flatdirent(next_result);
			destroy_partially_initialized_flatdirent(result);
			RETHROW();
		}
		destroy_partially_initialized_flatdirent(result);
		result = next_result;
		goto handle_result_after_wrlock;
	}

	TAILQ_INSERT_TAIL(&me->fdn_data.fdd_bypos, result, fde_bypos);

	/* Update `fdd_biggest_gap' in relation to `result' and its predecessor. */
	{
		pos_t gap = fflatdirent_basaddr(result) - nextpos;
		if (me->fdn_data.fdd_biggest_gap < gap) {
			me->fdn_data.fdd_biggest_gap = gap;
			me->fdn_data.fdd_biggest_suc = result;
		}
	}

	/* Release locks and we're done! */
	fflatdirnode_endwrite(me);
	return &result->fde_ent;
}


/* Unconditionally inherit a read-lock to `self' to:
 *  - Read another directory entry
 *  - Upgrade the lock to write and maybe check if the read entry was at the tail
 *    - If the read entry wasn't the last, release locks, destroy it, and return `false'
 *  - Append the new entry at the end of `self', and insert it into its hash-vector
 *  - Return `true', passing ownership of the (now write-)lock back to the caller.
 * @return: true:  Read-lock was upgraded & one more entry was added
 * @return: false: Read-lock was released & nothing was read */
PRIVATE NONNULL((1)) bool KCALL
fflatdirnode_readdir_and_upgrade(struct fflatdirnode *__restrict self) {
	pos_t nextpos;
	struct fflatdirent *ent;
	bool upgrade_status;
	nextpos = 0;
	ent     = TAILQ_LAST(&self->fdn_data.fdd_bypos);
	if (ent)
		nextpos = fflatdirent_endaddr(ent);
	TRY {
		struct fflatdirnode_ops const *ops;
		ops = fflatdirnode_getops(self);
		ent = (*ops->fdno_flat.fdnx_readdir)(self, nextpos);
	} EXCEPT {
		fflatdirnode_endread(self);
		RETHROW();
	}
	assert(!ent || fflatdirent_basaddr(ent) >= nextpos);
	/* Fill in missing fields. */
	if (ent) {
		ent->fde_ent.fd_hash = fdirent_hash(ent->fde_ent.fd_name,
		                                    ent->fde_ent.fd_namelen);
	}
	TRY {
		upgrade_status = fflatdirnode_upgrade(self);
	} EXCEPT {
		xdestroy_partially_initialized_flatdirent(ent);
		RETHROW();
	}
	if (!upgrade_status) {
		/* Lock was lost; check if what we did above was all correct. */
		pos_t new_nextpos = 0;
		struct fflatdirent *newent;
		newent = TAILQ_LAST(&self->fdn_data.fdd_bypos);
		if (newent)
			new_nextpos = fflatdirent_endaddr(newent);
		if (nextpos != new_nextpos) {
			fflatdirnode_endwrite(self);
			xdestroy_partially_initialized_flatdirent(ent);
			return false;
		}
	}

	/* Remember the newly read directory entry (or mark EOF) */
handle_ent_after_wrlock:
	if (!ent) {
		self->fdn_data.fdd_flags |= FFLATDIR_F_EOF;
		return;
	}

	/* Prepare the files hash-vector for the addition of another file. */
	TRY {
		fflatdirnode_fileslist_rehash_before_insert(self);
	} EXCEPT {
		fflatdirnode_endwrite(self);
		destroy_partially_initialized_flatdirent(ent);
		RETHROW();
	}

	/* Fill in missing fields of `ent' */
	ent->fde_ent.fd_refcnt = 1; /* +1: fdd_bypos */

	/* Add the new directory entry to caches. */
	if unlikely(!fflatdirnode_fileslist_tryinsertent(self, ent)) {
		/* oops. That's a duplicate entry... */
		struct fflatdirnode_ops const *ops;
		struct fflatdirent *next_ent = NULL;
		ops = fflatdirnode_getops(self);
		TRY {
			next_ent = (*ops->fdno_flat.fdnx_readdir)(self, fflatdirent_endaddr(ent));
			assert(!next_ent || fflatdirent_basaddr(next_ent) >= fflatdirent_endaddr(ent));
			if (next_ent) {
				next_ent->fde_ent.fd_hash = fdirent_hash(next_ent->fde_ent.fd_name,
				                                         next_ent->fde_ent.fd_namelen);
			}
			if (ops->fdno_flat.fdnx_deleteent && !(self->mf_flags & MFILE_F_READONLY)) {
				/* Delete any directory entry with a duplicate name.
				 * NOTE: Because duplicate names  shouldn't happen at  all,
				 *       don't bother trying to decrement the NLINK counter
				 *       in  this case; minimize further corruption by only
				 *       "fixing" imminent errors. */
				fflatdirnode_delete_entry(self, ent, next_ent == NULL);
			} else {
				nextpos = fflatdirent_endaddr(ent);
			}
		} EXCEPT {
			fflatdirnode_endwrite(self);
			xdestroy_partially_initialized_flatdirent(next_ent);
			destroy_partially_initialized_flatdirent(ent);
			RETHROW();
		}
		destroy_partially_initialized_flatdirent(ent);
		ent = next_ent;
		goto handle_ent_after_wrlock;
	}

	/* Insert into the by-position tree. */
	TAILQ_INSERT_TAIL(&self->fdn_data.fdd_bypos, ent, fde_bypos);

	/* Update `fdd_biggest_gap' in relation to `ent' and its predecessor. */
	{
		pos_t gap = fflatdirent_basaddr(ent) - nextpos;
		if (self->fdn_data.fdd_biggest_gap < gap) {
			self->fdn_data.fdd_biggest_gap = gap;
			self->fdn_data.fdd_biggest_suc = ent;
		}
	}
	return true;
}


/* Acquire a write-lock to `self' and make sure that the directory's been populated. */
PRIVATE NONNULL((1)) void KCALL
fflatdirnode_lockwrite_and_populate(struct fflatdirnode *__restrict self) {
again:
	fflatdirnode_write(self);
	COMPILER_READ_BARRIER();
	while (!(self->fdn_data.fdd_flags & FFLATDIR_F_EOF)) {
		fflatdirnode_downgrade(self);
		if (!fflatdirnode_readdir_and_upgrade(self))
			goto again;
	}
	assert(self->fdn_data.fdd_flags & FFLATDIR_F_EOF);
}

/* Acquire a read-lock to `self' and make sure that the directory's been populated. */
PRIVATE NONNULL((1)) void KCALL
fflatdirnode_lockread_and_populate(struct fflatdirnode *__restrict self) {
again:
	fflatdirnode_read(self);
	while (!(self->fdn_data.fdd_flags & FFLATDIR_F_EOF)) {
		if (!fflatdirnode_readdir_and_upgrade(self))
			goto again;
		fflatdirnode_downgrade(self);
	}
}


/* Create a new directory entry based on specs.
 * The caller must still initialize:
 *  - return->fde_ent.fd_refcnt
 *  - return->fde_bypos
 * ... as well as add it it `self->fdn_data.fdd_fileslist' */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct fflatdirent *
NOTHROW(KCALL fflatdirnode_mkent)(struct fflatdirnode *__restrict self,
                                  struct fmkfile_info *__restrict info,
                                  struct fnode *__restrict file) {
	struct fflatdirent *result;
	struct fflatdirnode_ops const *ops;
	ops = fflatdirnode_getops(self);
	/* Allocate the new entry. */
	if (ops->fdno_flat.fdnx_mkent) {
		result = (*ops->fdno_flat.fdnx_mkent)(self, info, file);
	} else {
		result = _fflatdirent_alloc(info->mkf_namelen);
		result->fde_ent.fd_ops = &fflatdirent_ops;
	}
	assert(result);
	/* Fill in missing fields. */
	result->fde_ent.fd_ino     = file->fn_ino;
	result->fde_ent.fd_namelen = info->mkf_namelen;
	result->fde_ent.fd_type    = IFTODT(file->fn_mode);
	*(char *)mempcpy(result->fde_ent.fd_name, info->mkf_name, info->mkf_namelen, sizeof(char)) = '\0';
	result->fde_ent.fd_hash = info->mkf_hash;
	if (info->mkf_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->mkf_name)) {
		/* Caller-given hash value isn't set, or cannot be trusted to be correct.
		 * -> Load our own hash-value! */
		result->fde_ent.fd_hash = fdirent_hash(result->fde_ent.fd_name,
		                                       result->fde_ent.fd_namelen);
		info->mkf_hash = result->fde_ent.fd_hash;
	}
	DBG_memset(&result->fde_pos, 0xcc, sizeof(result->fde_pos));
	DBG_memset(&result->fde_size, 0xcc, sizeof(result->fde_size));
	DBG_memset(&result->fde_bypos, 0xcc, sizeof(result->fde_bypos));
	return result;
}


/* Update `self->fdn_data.fdd_biggest_gap' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fflatdirnode_update_biggest_gap)(struct fflatdirnode *__restrict self) {
	pos_t prev_end = 0;
	struct fflatdirent *ent;
	self->fdn_data.fdd_biggest_gap = 0;
	DBG_memset(&self->fdn_data.fdd_biggest_suc, 0xcc,
	           sizeof(self->fdn_data.fdd_biggest_suc));

	/* Scan gaps between directory entries. */
	TAILQ_FOREACH (ent, &self->fdn_data.fdd_bypos, fde_bypos) {
		pos_t delta;
		delta = fflatdirent_basaddr(ent) - prev_end;
		if (self->fdn_data.fdd_biggest_gap < delta) {
			self->fdn_data.fdd_biggest_gap = delta;
			self->fdn_data.fdd_biggest_suc = ent;
		}
		prev_end = fflatdirent_endaddr(ent);
	}
}

/* Helper wrapper for `fdnx_writedir' that automatically deal with stream
 * allocations, as well as the  insertion of `ent' into `fdd_bypos'.  The
 * caller must be holding a write-lock to `fdd_lock'.
 *
 * When `FFLATSUPER_FEAT_WRITEDIR_CHANGES_INO' is set, then this function is
 * allowed to make modifications to `ent->fde_ent.fd_ino' and `file->fn_ino' */
PRIVATE NONNULL((1, 2, 3)) void KCALL
fflatdirnode_addentry_to_stream(struct fflatdirnode *__restrict self,
                                REF struct fflatdirent *__restrict ent,
                                struct fnode *__restrict file) {
	struct fflatdirnode_ops const *ops;
	ops = fflatdirnode_getops(self);
	DBG_memset(&ent->fde_bypos, 0xcc, sizeof(ent->fde_bypos));

	/* Safety check for "." and ".." filenames. */
	if unlikely(ent->fde_ent.fd_namelen <= 2 && ent->fde_ent.fd_name[0] == '.' &&
	            (ent->fde_ent.fd_namelen == 1 || ent->fde_ent.fd_name[1] == '.'))
		THROW(E_FSERROR_ILLEGAL_PATH);

	if (self->fdn_data.fdd_biggest_gap != 0) {
		/* Try to insert into the largest. */
again_try_biggest_gap:
		ent->fde_size = (size_t)self->fdn_data.fdd_biggest_gap;
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
		if unlikely((pos_t)ent->fde_size != self->fdn_data.fdd_biggest_gap)
			ent->fde_size = (size_t)-1;
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
		assert(fflatdirent_basaddr(self->fdn_data.fdd_biggest_suc) >= self->fdn_data.fdd_biggest_gap);
		ent->fde_pos = fflatdirent_basaddr(self->fdn_data.fdd_biggest_suc) - self->fdn_data.fdd_biggest_gap;
		if ((*ops->fdno_flat.fdnx_writedir)(self, ent, file, false)) {
			/* Success! We were able to make use of (some) of the gap! */
			assert(fflatdirent_endaddr(ent) <= fflatdirent_basaddr(self->fdn_data.fdd_biggest_suc));

			/* Insert the new entry before `self->fdn_data.fdd_biggest_suc' */
			TAILQ_INSERT_BEFORE(self->fdn_data.fdd_biggest_suc, ent, fde_bypos);

			/* Update the size of our "biggest gap" */
			self->fdn_data.fdd_biggest_gap = fflatdirent_basaddr(self->fdn_data.fdd_biggest_suc) -
			                                 fflatdirent_endaddr(ent);

			/* Remember that our "biggest gap" may no longer be the biggest one of them. */
			self->fdn_data.fdd_flags |= FFLATDIR_F_GAP_NOTLARGEST;
			return;
		}

		/* If the saved "biggest gap" isn't necessary the largest one of them,
		 * search  for one that is larger, and if one was found that is larger
		 * than the needed stream space, use it. */
		if (self->fdn_data.fdd_flags & FFLATDIR_F_GAP_NOTLARGEST) {
			pos_t oldspace = self->fdn_data.fdd_biggest_gap;
			assert(oldspace != 0);
			fflatdirnode_update_biggest_gap(self);
			self->fdn_data.fdd_flags &= ~FFLATDIR_F_GAP_NOTLARGEST;
			assert(self->fdn_data.fdd_biggest_gap >= oldspace);
			if (self->fdn_data.fdd_biggest_gap > oldspace)
				goto again_try_biggest_gap;
		}
	}

	/* No gaps (or gaps too small) -> must always append at the end. */
	ent->fde_pos = 0;
	if (!TAILQ_EMPTY(&self->fdn_data.fdd_bypos)) {
		struct fflatdirent *last;
		last = TAILQ_LAST(&self->fdn_data.fdd_bypos);
		ent->fde_pos = fflatdirent_endaddr(last);
	}
	do {
		ent->fde_size = (size_t)-1; /* Infinite space at end-of-directory */
		/* writedir can still fail  because `ent->fde_pos' points into  a
		 * reserved area of the directory stream. In this case, this call
		 * will also update `ent->fde_pos' such that it points to the end
		 * of that area, so we can just repeat until it's non-reserved. */
	} while (!(*ops->fdno_flat.fdnx_writedir)(self, ent, file, true));

	assert(TAILQ_EMPTY(&self->fdn_data.fdd_bypos) ||
	       ent->fde_pos >= fflatdirent_endaddr(TAILQ_LAST(&self->fdn_data.fdd_bypos)));

	/* Append new entry at the end of the by-position  list.
	 * Note that we  don't update `fdd_biggest_gap'  because
	 * we know that there's no gap large enough for any more
	 * entries. */
	TAILQ_INSERT_TAIL(&self->fdn_data.fdd_bypos, ent, fde_bypos);
}


/* Remove `ent' from the `fdd_bypos' list, and possibly update `fdd_biggest_gap' */
PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL fflatdirnode_remove_from_bypos)(struct fflatdirnode *__restrict self,
                                              /*out_ref*/ struct fflatdirent *__restrict ent) {
	struct fflatdirent *prev, *next;
	assert(TAILQ_ISBOUND(ent, fde_bypos));

	/* Load neighbors */
	prev = TAILQ_PREV(ent, fde_bypos);
	next = TAILQ_NEXT(ent, fde_bypos);

	/* Remove from list.
	 * NOTE: We use UNBIND instead of REMOVE so `ent' becomes marked as deleted.
	 *       s.a. `fflatdirent_wasdeleted()' */
	TAILQ_UNBIND(&self->fdn_data.fdd_bypos, ent, fde_bypos);

	/* If both a predecessor and successor exist,
	 * then update the delta for the largest gap. */
	if (prev && next) {
		pos_t prev_end = fflatdirent_endaddr(prev);
		pos_t next_bas = fflatdirent_basaddr(next);
		pos_t free_delta;
		assert(prev_end <= fflatdirent_basaddr(ent));
		assert(fflatdirent_endaddr(ent) <= next_bas);
		free_delta = next_bas - prev_end;
		if (self->fdn_data.fdd_biggest_gap < free_delta) {
			self->fdn_data.fdd_biggest_gap = free_delta;
			self->fdn_data.fdd_biggest_suc = next;
		}
	} else if (self->fdn_data.fdd_biggest_suc == ent) {
		if (next) {
			/* Special case: first entry in directory was removed, and
			 * the largest gap in the directory stream also existed at
			 * before the first entry.
			 *
			 * In this case the gap grows until the start of the old
			 * second; new first entry `next'. */
			assert(self->fdn_data.fdd_biggest_gap == ent->fde_pos);
			self->fdn_data.fdd_biggest_gap = next->fde_pos;
			self->fdn_data.fdd_biggest_suc = next;
		} else {
			/* Special case: last entry in directory was removed,  and
			 * the largest gap  existed just before  said last  entry.
			 * In this case the gap disappears entirely before the dir
			 * also shrunk as a result. */
			self->fdn_data.fdd_biggest_gap = 0;
			DBG_memset(&self->fdn_data.fdd_biggest_suc, 0xcc,
			           sizeof(self->fdn_data.fdd_biggest_suc));
		}
	}
	assertf(self->fdn_data.fdd_biggest_suc != ent ||
	        self->fdn_data.fdd_biggest_gap == 0,
	        "If `ent' really had been the successor of the "
	        "biggest gap, then this removal should have made the "
	        "gap even larger, in which case above code should have "
	        "already updated the biggest-gap data pointers.");
}





PUBLIC WUNUSED NONNULL((1, 2)) unsigned int KCALL
fflatdirnode_v_mkfile(struct fdirnode *__restrict self,
                      struct fmkfile_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION) {
	REF struct fnode *node;
	REF struct fflatdirent *ent;
	REF struct fdirent *existing;
	struct fflatdirnode_ops const *ops;
	struct fflatdirnode *me;
	me  = fdirnode_asflat(self);
	ops = fflatdirnode_getops(me);

	/* Quick check if the named file already exists. (before we do any  allocations)
	 * In case it doesn't already exist, this *should* also pre-load the entire dir,
	 * though that cache may be dropped before we get to add the new file below. */
again_lookup_existing:
	existing = fflatdirnode_v_lookup(self, &info->mkf_lookup_info);
	if (existing) {
handle_existing:
		TRY {
			node = fdirent_opennode(existing, me);
		} EXCEPT {
			decref_unlikely(existing);
			RETHROW();
		}
		/* Check for race condition: `existing' was already deleted. */
		if unlikely(!node) {
			decref_unlikely(existing);
			goto again_lookup_existing;
		}
		info->mkf_dent  = existing; /* Inherit reference */
		info->mkf_rnode = node;     /* Inherit reference */
		return FDIRNODE_MKFILE_EXISTS;
	}

	/* Check that we're able to write new entries. */
	if unlikely(!ops->fdno_flat.fdnx_writedir)
		THROW(E_FSERROR_READONLY);

	/* Create the new node, or use the given one for hardlinks. */
	if (info->mkf_fmode == 0) {
		node = info->mkf_hrdlnk.hl_node;

		/* Check if creating a hardlink is even possible at this point. */
		mfile_tslock_acquire(node);
		if unlikely(node->fn_nlink >= me->fn_super->fs_feat.sf_link_max) {
			mfile_tslock_release_br(node);
			THROW(E_FSERROR_TOO_MANY_HARD_LINKS);
		}
		mfile_tslock_release(node);
		incref(node);
	} else {
		/* Construct the new file-node object. */
		node = (ops->fdno_flat.fdnx_mkfile)(me, info);

		/* Initialize missing fields as per the specs. */
		node->mf_flags |= MFILE_FN_GLOBAL_REF;
		self->mf_flags |= me->mf_flags & (MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOMTIME);
		node->mf_refcnt     = 2; /* +1: MFILE_FN_GLOBAL_REF, +1: info->mkf_rnode */
		node->mf_lock       = ATOMIC_RWLOCK_INIT;
		node->mf_initdone   = SIG_INIT;
		node->mf_lockops    = SLIST_HEAD_INITIALIZER(~);
		node->mf_changed    = SLIST_HEAD_INITIALIZER(~);
		node->mf_part_amask = MAX(PAGESIZE, 1 << node->mf_blockshift) - 1;
		node->mf_trunclock  = 0;
		node->mf_atime      = info->mkf_creat.c_atime;
		node->mf_mtime      = info->mkf_creat.c_mtime;
		node->mf_ctime      = info->mkf_creat.c_ctime;
		node->fn_nlink      = 1;
		node->fn_mode       = info->mkf_fmode;
		node->fn_uid        = info->mkf_creat.c_owner;
		node->fn_gid        = info->mkf_creat.c_group;
		node->fn_super      = incref(me->fn_super);
		node->fn_changed    = LIST_ENTRY_UNBOUND_INITIALIZER;
		DBG_memset(&node->fn_supent, 0xcc, sizeof(node->fn_supent)); /* Initialized later */
		node->fn_supent.rb_rhs = FSUPER_NODES_DELETED;               /* Loaded later... */
		LIST_ENTRY_UNBOUND_INIT(&self->fn_allnodes);
	}
	TRY {
		/* Construct the new directory entry. */
		ent = fflatdirnode_mkent(me, info, node);
		ent->fde_ent.fd_refcnt = 2; /* +1: fdd_bypos, +1: info->mkf_dent */
		TRY {
			/* Acquire  a write-lock & make sure to populate the entire directory.
			 * There mustn't be any entry on-disk that isn't also loaded into  the
			 * cache. Otherwise, we might be unable to properly prevent duplicates */
			fflatdirnode_lockwrite_and_populate(me);
			TRY {
				struct fflatdirent *existing_ent;

				/* Check for an existing file. */
				{
					struct flookup_info existing_info;
					existing_info.flu_name    = ent->fde_ent.fd_name;
					existing_info.flu_hash    = ent->fde_ent.fd_hash;
					existing_info.flu_namelen = ent->fde_ent.fd_namelen;
					existing_info.flu_flags   = info->mkf_flags;
					existing_ent = fflatdirnode_fileslist_lookup(me, &existing_info);
				}
				if unlikely(existing_ent) {
					/* File already exists. */
					incref(existing_ent);
					fflatdirnode_endwrite(me);
					existing = &existing_ent->fde_ent; /* Inherit reference */

					/* Destroy partially constructed objects. */
					destroy_partially_initialized_flatdirent(ent);
					decref_likely(node);

					/* Deal with `existing' */
					goto handle_existing;
				}

				/* Prepare the directory hash-vector for the addition of a new element. */
				fflatdirnode_fileslist_rehash_before_insert(me);

				/* Insert the new directory entry into the hash-vector. */
				fflatdirnode_fileslist_insertent(me, ent);
				TRY {
					/* Write directory entries for new node+ent */
					fflatdirnode_addentry_to_stream(me, ent, node);

					/* Ensure that `fdnx_deleteent' is available in case we end up needing it. */
					assertf(ops->fdno_flat.fdnx_deleteent != NULL,
					        "As per specs, `fdnx_deleteent' is mandatory when `fdnx_writedir' is provided, "
					        "the later already having been asserted above by `E_FSERROR_READONLY'");

					/* Deal with hardlinks. */
					if (info->mkf_fmode == 0) {
						bool nlink_ok;
						mfile_tslock_acquire(node);
						nlink_ok = false;
						if likely(node->fn_nlink < me->fn_super->fs_feat.sf_link_max) {
							++node->fn_nlink;
							nlink_ok = true;
						}
						mfile_tslock_release(node);
						if likely(nlink_ok) {
							/* Indicate that attributes of `node' have changed. */
							mfile_changed(node, MFILE_F_ATTRCHANGED);
						} else {
							TRY {
								fflatdirnode_delete_entry(me, ent, TAILQ_NEXT(ent, fde_bypos) == NULL);
							} EXCEPT {
								/* _Always_ remove `ent' from the `fdd_bypos' list. */
								fflatdirnode_remove_from_bypos(me, ent);
								RETHROW();
							}
							/* Remove `ent' from the `fdd_bypos' list. */
							fflatdirnode_remove_from_bypos(me, ent);
							THROW(E_FSERROR_TOO_MANY_HARD_LINKS);
						}
					} else {
						/* Invoke the `fdnx_allocfile' operator (if defined). */
						if (ops->fdno_flat.fdnx_allocfile) {
							TRY {
								(*ops->fdno_flat.fdnx_allocfile)(me, ent, node);
							} EXCEPT {
								/* Invoke the `fdnx_deleteent' operator to (try) remove the previously written entry.
								 * Note the use of  nested exceptions, as `fdnx_deleteent'  is also allowed to  throw
								 * its own exceptions. */
								NESTED_TRY {
									fflatdirnode_delete_entry(me, ent, TAILQ_NEXT(ent, fde_bypos) == NULL);
								} EXCEPT {
									/* _Always_ remove `ent' from the `fdd_bypos' list. */
									fflatdirnode_remove_from_bypos(me, ent);
									RETHROW();
								}
								/* Remove `ent' from the `fdd_bypos' list. */
								fflatdirnode_remove_from_bypos(me, ent);
								RETHROW();
							}
						}
					}
				} EXCEPT {
					/* Remove `ent' from the hash-vector. */
					fflatdirnode_fileslist_removeent(me, ent);
					fflatdirnode_fileslist_rehash_after_remove(me);
					RETHROW();
				}
			} EXCEPT {
				fflatdirnode_endwrite(me);
				RETHROW();
			}

			/* Add the new node to the nodes list of `me->fn_super',
			 * as  well  as  to  the  global  list  of  all   nodes. */
			assert(node->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
			assert(!(node->mf_flags & MFILE_F_DELETED));
			assert(!LIST_ISBOUND(node, fn_allnodes));
			fnode_init_addtosuper_and_all(node);

			/* Release lock */
			fflatdirnode_endwrite(me);
		} EXCEPT {
			destroy_partially_initialized_flatdirent(ent);
			RETHROW();
		}
	} EXCEPT {
		decref_likely(node);
		RETHROW();
	}
	info->mkf_rnode = node;          /* Inherit reference */
	info->mkf_dent  = &ent->fde_ent; /* Inherit reference */
	return FDIRNODE_MKFILE_SUCCESS;
}


PUBLIC WUNUSED NONNULL((1, 2, 3)) unsigned int KCALL
fflatdirnode_v_unlink(struct fdirnode *__restrict self,
                      struct fdirent *__restrict entry,
                      struct fnode *__restrict file)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY) {
	struct fflatdirnode_ops const *ops;
	struct fflatdirnode *me;
	struct fflatdirent *ent;
	me  = fdirnode_asflat(self);
	ops = fflatdirnode_getops(me);
	ent = fdirent_asflat(entry);

	/* Lock the directory. */
again:
	fflatdirnode_write(me);

again_locked:
	/* Check if `entry' has already been deleted. */
	if (!TAILQ_ISBOUND(ent, fde_bypos)) {
		fflatdirnode_endwrite(me);
		return FDIRNODE_UNLINK_DELETED;
	}

	/* Check if we're able to delete entries. */
	if unlikely(!ops->fdno_flat.fdnx_deleteent) {
		fflatdirnode_endwrite(me);
		THROW(E_FSERROR_READONLY);
	}

	/* In order to pass the correct value for `fdnx_deleteent::at_end_of_dir', we
	 * first need to check if `ent' really is the last entry of the directory, or
	 * if there might still be more entries after it. */
	if (TAILQ_NEXT(ent, fde_bypos) == NULL && !(me->fdn_data.fdd_flags & FFLATDIR_F_EOF)) {
		fflatdirnode_downgrade(me);
		if (fflatdirnode_readdir_and_upgrade(me))
			goto again_locked;
		goto again;
	}

	/* Ask the FS-specific implementation to delete file entries. */
	TRY {
		fflatdirnode_delete_entry(me, ent, TAILQ_NEXT(ent, fde_bypos) == NULL);
	} EXCEPT {
		fflatdirnode_endwrite(me);
		RETHROW();
	}

	/* Remove the directory relating to `entry' */
	fflatdirnode_fileslist_removeent(me, ent);
	fflatdirnode_fileslist_rehash_after_remove(me);
	fflatdirnode_remove_from_bypos(me, ent);
	fflatdirnode_endwrite(me);

	/* Decrement the NLINK counter of `file' */
	{
		bool deleted;
		mfile_tslock_acquire(file);
		assert(file->fn_nlink != 0);
		--file->fn_nlink;
		deleted = file->fn_nlink == 0;
		mfile_tslock_release(file);
		if (deleted) {
			/* Last link went away -> must delete the file. */
			fnode_delete(file);

			/* If defined, also invoke the custom file-deleted operator.
			 * As  you can see, even if this operator throws, the unlink
			 * will not become undone. As a matter of fact, there is  no
			 * way to undo the delete without out-of-scope data races! */
			if (ops->fdno_flat.fdnx_deletefile != NULL)
				(*ops->fdno_flat.fdnx_deletefile)(me, ent, file);
		}
	} /* Scope... */

	return FDIRNODE_UNLINK_SUCCESS;
}




PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL release_locks_for_rename)(struct fflatdirnode *nd,
                                        struct fflatdirnode *od) {
	if (od != nd)
		fflatdirnode_endwrite(od);
	fflatdirnode_endwrite(nd);
}

PRIVATE NONNULL((1, 2, 3)) void FCALL
maybe_update_parent(struct fflatdirnode *__restrict file,
                    struct fflatdirnode *__restrict oldparent,
                    struct fflatdirnode *__restrict newparent) {
	struct fflatdirnode_ops const *ofile_ops;
	ofile_ops = fflatdirnode_getops(file);
	if (ofile_ops->fdno_flat.fdnx_parentchanged != NULL)
		(*ofile_ops->fdno_flat.fdnx_parentchanged)(file, oldparent, newparent);
}

PUBLIC WUNUSED NONNULL((1, 2)) unsigned int KCALL
fflatdirnode_v_rename(struct fdirnode *__restrict self,
                      struct frename_info *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY) {
	struct fmkfile_info mki;
	struct fflatdirnode *nd    = fdirnode_asflat(self);
	struct fflatdirnode *od    = fdirnode_asflat(info->frn_olddir);
	struct fflatdirent *oldent = fdirent_asflat(info->frn_oldent);
again:
	/* Need  a write-lock to the new directory, as well as to make sure that
	 * all  directory entries from  the new directory have  been read (so we
	 * can make sure that no entry matching the new filename already exists) */
	fflatdirnode_lockwrite_and_populate(nd);
	if (od != nd) {
		/* Must also acquire a write-lock to the old directory `od' */
		if (!fflatdirnode_trywrite(od)) {
			fflatdirnode_endwrite(nd);
			fflatdirnode_write(od);
			fflatdirnode_endwrite(od);
			goto again;
		}
	}

	/* Check if `oldent' was deleted. */
	if unlikely(fflatdirent_wasdeleted(oldent)) {
		release_locks_for_rename(nd, od);
		return FDIRNODE_RENAME_DELETED;
	}

	/* Because it's kind-of complicated, get `AT_RENAME_EXCHANGE' out of the way */
	if (info->frn_flags & AT_RENAME_EXCHANGE) {
		assert(info->frn_repfile);
		/* When exchanging files, we must ensure that `od' has also been populated. */
		if (!(od->fdn_data.fdd_flags & FFLATDIR_F_EOF)) {
			assertf(od != nd, "else, fflatdirnode_lockwrite_and_populate(nd) would have already set `FFLATDIR_F_EOF'");
			fflatdirnode_endwrite(nd);
			fflatdirnode_lockwrite_and_populate(od);
			fflatdirnode_endwrite(od);
			goto again;
		}
		TRY {
			struct fflatdirnode_ops const *od_ops, *nd_ops;
			struct fflatdirent *newent;
			struct fnode *ofile = info->frn_file;
			struct fnode *nfile = info->frn_repfile;
			struct fflatdirent *new_oent; /* New directory entry for `ofile' */
			struct fflatdirent *new_nent; /* New directory entry for `nfile' */

			/* Lookup the other directory entry of the exchange. */
			newent = fflatdirnode_fileslist_lookup(nd, &info->frn_lookup_info);
			if unlikely(!newent) {
				release_locks_for_rename(nd, od);

				/* The exchange target was deleted (tell so the  caller)
				 * We indicate this with an EXISTS error saying that the
				 * existing file is `NULL' (which differs from the  non-
				 * NULL caller-given `frn_repfile'; asserted above) */
				info->frn_repfile = NULL;
				info->frn_dent    = NULL;
				return FDIRNODE_RENAME_EXISTS;
			}

			/* Check that the Inode pointed-to by the directory matches
			 * the Inode with which the exchange is supposed to happen. */
			if unlikely(newent->fde_ent.fd_ino != nfile->fn_ino ||
			            newent->fde_ent.fd_type != IFTODT(nfile->fn_mode)) {
				info->frn_dent = incref(&newent->fde_ent);
				goto err_exists_fill_in_repnode;
			}

			/* Handles still appear up-to-date. - Let's do this! */
			od_ops = fflatdirnode_getops(od);
			nd_ops = fflatdirnode_getops(nd);

			/* Check that both directories support required operators. */
			if (!od_ops->fdno_flat.fdnx_writedir || !nd_ops->fdno_flat.fdnx_writedir)
				THROW(E_FSERROR_READONLY);

			assert(od_ops->fdno_flat.fdnx_deleteent);
			assert(nd_ops->fdno_flat.fdnx_deleteent);

			/* NOTE: Can never re-use directory entries because of custom `fdnx_mkent',
			 *       and because the old entries  may be externally visible, and  we're
			 *       not allowed to change their [const] fields.
			 * In theory, we could re-use them when there is no custom `fdnx_mkent',
			 * and `isshared()' indicates no untracable references, but we don't  do
			 * that for the sake of simplicity. */
			DBG_memset(&mki.mkf_dent, 0xcc, sizeof(mki.mkf_dent));
			DBG_memset(&mki.mkf_rnode, 0xcc, sizeof(mki.mkf_rnode));
			mki.mkf_name           = newent->fde_ent.fd_name;
			mki.mkf_hash           = newent->fde_ent.fd_hash;
			mki.mkf_namelen        = newent->fde_ent.fd_namelen;
			mki.mkf_flags          = 0;
			mki.mkf_fmode          = 0;
			mki.mkf_hrdlnk.hl_node = ofile;
			new_oent = fflatdirnode_mkent(nd, &mki, ofile); /* New entry in `nd' (for `ofile') */
			TRY {
				DBG_memset(&mki.mkf_dent, 0xcc, sizeof(mki.mkf_dent));
				DBG_memset(&mki.mkf_rnode, 0xcc, sizeof(mki.mkf_rnode));
				mki.mkf_name    = oldent->fde_ent.fd_name;
				mki.mkf_hash    = oldent->fde_ent.fd_hash;
				mki.mkf_namelen = oldent->fde_ent.fd_namelen;
				assert(mki.mkf_flags == 0);
				assert(mki.mkf_fmode == 0);
				mki.mkf_hrdlnk.hl_node = nfile;
				new_nent = fflatdirnode_mkent(od, &mki, nfile); /* New entry in `od' (for `nfile') */
				TRY {
					/* At this point, all high-level allocations have been made.
					 * -> Time to modify the actual directory streams:
					 *
					 *  - Create `new_nent' in `od' (fdnx_writedir)
					 *  - Create `new_oent' in `nd' (fdnx_writedir)   (on except: Delete `new_nent' in `od' (fdnx_deleteent))
					 *  - Delete `oldent' in `od' (fdnx_deleteent)    (on except: Delete `new_oent' in `nd' (fdnx_deleteent),
					 *                                                            Delete `new_nent' in `od' (fdnx_deleteent))
					 *  - Delete `newent' in `nd' (fdnx_deleteent)    (on except: Create  `oldent'  in  `od'  (fdnx_writedir)
					 *                                                            Delete `new_oent' in `nd' (fdnx_deleteent),
					 *                                                            Delete `new_nent' in `od' (fdnx_deleteent))
					 * -- CUT: Errors after this point will not cause the operation to be undone
					 *  - if (fnode_isdir(ofile)) fdnx_parentchanged(ofile, od, nd);
					 *  - if (fnode_isdir(nfile)) fdnx_parentchanged(nfile, nd, od);
					 */
					new_nent->fde_ent.fd_refcnt = 2;
					fflatdirnode_addentry_to_stream(od, new_nent, nfile);
					TRY {
						new_oent->fde_ent.fd_refcnt = 2;
						fflatdirnode_addentry_to_stream(nd, new_oent, ofile);
						TRY {
							fflatdirnode_delete_entry(od, oldent, TAILQ_NEXT(oldent, fde_bypos) == NULL);
							fflatdirnode_remove_from_bypos(od, oldent);
							decref_nokill(oldent); /* Returned by `fflatdirnode_remove_from_bypos()' */
							TRY {
								fflatdirnode_delete_entry(nd, newent, TAILQ_NEXT(newent, fde_bypos) == NULL);
								fflatdirnode_remove_from_bypos(nd, newent);
							} EXCEPT {
								{
									NESTED_EXCEPTION;
									TRY {
										/* Try to re-add to the old directory, but if that fails,
										 * admit defeat and get rid  of the file (even though  it
										 * should stay, we've got no way to make it do that) */
										fflatdirnode_addentry_to_stream(od, oldent, ofile);
									} EXCEPT {
										fflatdirnode_fileslist_removeent(od, oldent);
										fflatdirnode_fileslist_rehash_after_remove(od);
										RETHROW();
									}
									incref(oldent); /* Used by `fflatdirnode_addentry_to_stream()' */
								}
								RETHROW();
							}
						} EXCEPT {
							{
								NESTED_EXCEPTION;
								RAII_FINALLY { fflatdirnode_remove_from_bypos(nd, new_oent); };
								fflatdirnode_delete_entry(nd, new_oent, TAILQ_NEXT(new_oent, fde_bypos) == NULL);
							}
							RETHROW();
						}
					} EXCEPT {
						{
							NESTED_EXCEPTION;
							RAII_FINALLY { fflatdirnode_remove_from_bypos(od, new_nent); };
							fflatdirnode_delete_entry(od, new_nent, TAILQ_NEXT(new_nent, fde_bypos) == NULL);
						}
						RETHROW();
					}

					/* Update files from hash-vectors. */
					fflatdirnode_fileslist_removeent(od, oldent);
					fflatdirnode_fileslist_removeent(nd, newent);
					fflatdirnode_fileslist_insertent(od, new_nent);
					fflatdirnode_fileslist_insertent(nd, new_oent);

					/* Update the directory entry for the old file (which has now become the new file) */
					assert(&oldent->fde_ent == info->frn_oldent);
					decref_unlikely(newent);               /* Inherited from `fflatdirnode_remove_from_bypos(nd, newent);' */
					decref_unlikely(oldent);               /* Stolen from `info->frn_oldent' */
					info->frn_oldent = &new_nent->fde_ent; /* Inherit reference */
					info->frn_dent   = &new_oent->fde_ent; /* Inherit reference */
				} EXCEPT {
					destroy_partially_initialized_flatdirent(new_oent);
					RETHROW();
				}
			} EXCEPT {
				destroy_partially_initialized_flatdirent(new_oent);
				RETHROW();
			}

			/* Invoke `fdnx_parentchanged' if directories were renamed */
			if (od != nd) {
				if (fnode_isdir(ofile)) {
					TRY {
						maybe_update_parent(fnode_asflatdir(ofile), od, nd);
					} EXCEPT {
						if (fnode_isdir(nfile)) {
							NESTED_EXCEPTION;
							maybe_update_parent(fnode_asflatdir(nfile), nd, od);
						}
						RETHROW();
					}
				}
				if (fnode_isdir(nfile))
					maybe_update_parent(fnode_asflatdir(nfile), nd, od);
			}
		} EXCEPT {
			release_locks_for_rename(nd, od);
			RETHROW();
		}
		release_locks_for_rename(nd, od);
		return FDIRNODE_RENAME_SUCCESS;
	}

	/* Even without exchange, we'll need to  know if `oldent' is the  last
	 * entry from `od', so if that isn't know at the moment, read one more
	 * entry now that we can still easily release locks. */
	if (TAILQ_NEXT(oldent, fde_bypos) == NULL && !(od->fdn_data.fdd_flags & FFLATDIR_F_EOF)) {
		assertf(od != nd, "else, fflatdirnode_lockwrite_and_populate(nd) would have already set `FFLATDIR_F_EOF'");
		fflatdirnode_endwrite(nd);
		fflatdirnode_downgrade(od);
		if (fflatdirnode_readdir_and_upgrade(od))
			fflatdirnode_endwrite(od);
		goto again;
	}

	TRY {
		/* Check for an existing file. */
		struct fflatdirent *newent;
		struct fflatdirent *existing;
		existing = fflatdirnode_fileslist_lookup(nd, &info->frn_lookup_info);
		if (existing) {
			/* Check if we're really supposed to override this file. */
			if unlikely(!info->frn_repfile ||
			            existing->fde_ent.fd_ino != info->frn_repfile->fn_ino ||
			            existing->fde_ent.fd_type != IFTODT(info->frn_repfile->fn_mode)) {
				info->frn_dent = incref(&existing->fde_ent);
				goto err_exists_fill_in_repnode;
			}
		} else {
			if (info->frn_repfile != NULL) {
				/* Nope: there's nothing here already... */
				info->frn_repfile = NULL;
				release_locks_for_rename(nd, od);
				return FDIRNODE_RENAME_EXISTS;
			}
		}

		/* Create a new directory for the file after it's been renamed. */
		DBG_memset(&mki.mkf_dent, 0xcc, sizeof(mki.mkf_dent));
		DBG_memset(&mki.mkf_rnode, 0xcc, sizeof(mki.mkf_rnode));
		if (existing) {
			mki.mkf_name    = existing->fde_ent.fd_name;
			mki.mkf_hash    = existing->fde_ent.fd_hash;
			mki.mkf_namelen = existing->fde_ent.fd_namelen;
		} else {
			mki.mkf_name    = info->frn_name;
			mki.mkf_hash    = info->frn_hash;
			mki.mkf_namelen = info->frn_namelen;
		}
		mki.mkf_flags          = 0;
		mki.mkf_fmode          = 0;
		mki.mkf_hrdlnk.hl_node = info->frn_file;
		newent = fflatdirnode_mkent(nd, &mki, info->frn_file);
		TRY {
			/* +1: fflatdirnode_addentry_to_stream(nd, newent, info->frn_file),
			 * +1: info->frn_dent */
			newent->fde_ent.fd_refcnt = 2;

			/* If nothing gets overwritten, we'll need to rehash for the later-added file. */
			if (!existing)
				fflatdirnode_fileslist_rehash_before_insert(nd);

			/* Add the new entry to the target directory. */
			fflatdirnode_addentry_to_stream(nd, newent, info->frn_file);

			/* If present, delete the pre-existing file in `nd' */
			if (existing) {
				TRY {
					/* Remove the directory relating to `entry' */
					fflatdirnode_delete_entry(nd, existing, TAILQ_NEXT(existing, fde_bypos) == NULL);
				} EXCEPT {
					{
						NESTED_EXCEPTION;
						RAII_FINALLY { fflatdirnode_remove_from_bypos(nd, newent); };
						fflatdirnode_delete_entry(nd, newent, TAILQ_NEXT(newent, fde_bypos) == NULL);
					}
					RETHROW();
				}
			}
		} EXCEPT {
			destroy_partially_initialized_flatdirent(newent);
			RETHROW();
		}
		/* Point of no return --- From this on, we don't try to undo the rename if an error happens. */

		/* _Always_ remove `oldent' from `od' on the cache-level. */
		RAII_FINALLY {
			fflatdirnode_remove_from_bypos(od, oldent);
			fflatdirnode_fileslist_removeent(od, oldent);
			fflatdirnode_fileslist_rehash_after_remove(od);
			decref_nokill(oldent); /* Inherited from `fflatdirnode_remove_from_bypos()' */
		};

		/* If present, delete the pre-existing file in `nd' */
		if (existing) {
			bool deleted;
			fflatdirnode_fileslist_removeent(nd, existing);
			fflatdirnode_remove_from_bypos(nd, existing);
			FINALLY_DECREF_UNLIKELY(existing); /* Inherited from `fflatdirnode_remove_from_bypos(nd, existing);' */

			/* Decrement the NLINK counter of `info->frn_repfile' */
			mfile_tslock_acquire(info->frn_repfile);
			assert(info->frn_repfile->fn_nlink != 0);
			--info->frn_repfile->fn_nlink;
			deleted = info->frn_repfile->fn_nlink == 0;
			mfile_tslock_release(info->frn_repfile);
			if (deleted) {
				struct fflatdirnode_ops const *ops;
				/* Last link went away -> must delete the file. */
				fnode_delete(info->frn_repfile);

				/* If defined, also invoke the custom file-deleted operator.
				 * As  you can see, even if this operator throws, the rename
				 * will not become undone. As a matter of fact, there is  no
				 * way to undo the rename without risk of more exceptions! */
				ops = fflatdirnode_getops(nd);
				if (ops->fdno_flat.fdnx_deletefile != NULL) {
					TRY {
						(*ops->fdno_flat.fdnx_deletefile)(nd, existing, info->frn_repfile);
					} EXCEPT {
						decref_unlikely(newent);
						{
							NESTED_EXCEPTION;
							/* Remove `oldent' from `od' on the fs-level */
							TRY {
								fflatdirnode_delete_entry(od, oldent, TAILQ_NEXT(oldent, fde_bypos) == NULL);
							} EXCEPT {
								if (fnode_isdir(info->frn_file)) {
									NESTED_EXCEPTION;
									maybe_update_parent(fnode_asflatdir(info->frn_file), od, nd);
								}
								RETHROW();
							}
							if (fnode_isdir(info->frn_file))
								maybe_update_parent(fnode_asflatdir(info->frn_file), od, nd);
						}
						RETHROW();
					}
				}
			}
		}

		/* Remove `oldent' from `od' on the fs-level */
		TRY {
			fflatdirnode_delete_entry(od, oldent, TAILQ_NEXT(oldent, fde_bypos) == NULL);
		} EXCEPT {
			decref_unlikely(newent);
			if (fnode_isdir(info->frn_file)) {
				NESTED_EXCEPTION;
				maybe_update_parent(fnode_asflatdir(info->frn_file), od, nd);
			}
			RETHROW();
		}
		if (fnode_isdir(info->frn_file))
			maybe_update_parent(fnode_asflatdir(info->frn_file), od, nd);
		info->frn_dent = &newent->fde_ent; /* Inherit reference */
	} EXCEPT {
		release_locks_for_rename(nd, od);
		RETHROW();
	}
	release_locks_for_rename(nd, od);
	return FDIRNODE_RENAME_SUCCESS;
err_exists_fill_in_repnode:
	release_locks_for_rename(nd, od);
	TRY {
		info->frn_repfile = fflatdirent_v_opennode(info->frn_dent, nd);
	} EXCEPT {
		decref_unlikely(info->frn_dent);
		DBG_memset(&info->frn_dent, 0xcc, sizeof(info->frn_dent));
		RETHROW();
	}
	/* Check for (rare) race condition: deleted since we released the lock above. */
	if unlikely(!info->frn_repfile) {
		decref_unlikely(info->frn_dent);
		info->frn_dent = NULL;
	}
	return FDIRNODE_RENAME_EXISTS;
}



struct fflatdirenum {
	FDIRENUM_HEADER
	REF struct fflatdirent *ffde_next; /* [0..1][lock(SMP(ffde_lock))] Next entry to read.
	                                    * When NULL, load the next entry with a position `>= ffde_pos' */
	pos_t                   ffde_pos;  /* [valid_if(!ffde_next)][lock(SMP(ffde_lock))] Next position. */
#ifndef CONFIG_NO_SMP
	struct atomic_lock      ffde_lock; /* Lock for the above. */
#endif /* !CONFIG_NO_SMP */
};
#define fdirenum_asflat(self) ((struct fflatdirenum *)(self))

#ifdef CONFIG_NO_SMP
#define fflatdirenum_lock_acquire_nopr(self) (void)0
#define fflatdirenum_lock_release_nopr(self) (void)0
#else /* CONFIG_NO_SMP */
#define fflatdirenum_lock_acquire_nopr(self) atomic_lock_acquire_nopr(&(self)->ffde_lock)
#define fflatdirenum_lock_release_nopr(self) atomic_lock_release(&(self)->ffde_lock)
#endif /* !CONFIG_NO_SMP */
#define fflatdirenum_lock_acquire(self)      \
	do {                                     \
		pflag_t _was = PREEMPTION_PUSHOFF(); \
		fflatdirenum_lock_acquire_nopr(self)
#define fflatdirenum_lock_release_br(self)     \
		(fflatdirenum_lock_release_nopr(self), \
		 PREEMPTION_POP(_was))
#define fflatdirenum_lock_release(self)     \
		fflatdirenum_lock_release_br(self); \
	}	__WHILE0


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fflatdirenum_v_fini)(struct fdirenum *__restrict self) {
	struct fflatdirenum *me = fdirenum_asflat(self);
	xdecref(me->ffde_next);
}

/* Return a reference to the first directory entry at a position `>= pos'
 * If no such entry exists, return `NULL' instead. */
PRIVATE WUNUSED NONNULL((1)) REF struct fflatdirent *KCALL
fflatdirnode_entafter(struct fflatdirnode *__restrict self, pos_t pos)
		THROWS(...) {
	REF struct fflatdirent *result;
again:
	fflatdirnode_read(self);
again_locked:
	result = TAILQ_LAST(&self->fdn_data.fdd_bypos);
	if (result && fflatdirent_basaddr(result) >= pos) {
		/* The requested entry has already been loaded. */
		if (pos <= fflatdirent_endaddr(result) / 2) {
			/* Scan from the front */
			result = TAILQ_FIRST(&self->fdn_data.fdd_bypos);
			for (;;) {
				assert(result);
				if (fflatdirent_basaddr(result) >= pos)
					break;
				result = TAILQ_NEXT(result, fde_bypos);
			}
		} else {
			/* Scan from the back */
			while (TAILQ_PREV(result, fde_bypos) &&
			       fflatdirent_basaddr(TAILQ_PREV(result, fde_bypos)) >= pos)
				result = TAILQ_PREV(result, fde_bypos);
		}
		/* At this point, `result' is the first entry with a position >= pos! */
		incref(result);
		fflatdirnode_endread(self);
		return result;
	}

	/* If EOF has been reached, then the requested entry doesn't exist. */
	if (self->fdn_data.fdd_flags & FFLATDIR_F_EOF) {
		fflatdirnode_endread(self);
		return NULL;
	}

	/* Load more entries. */
	if (!fflatdirnode_readdir_and_upgrade(self))
		goto again;
	fflatdirnode_downgrade(self);
	goto again_locked;
}

PRIVATE NONNULL((1)) size_t KCALL
fflatdirenum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                       size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
		THROWS(...) {
	ssize_t result;
	pos_t oldpos, real_oldpos;
	struct fflatdirnode *dir;
	REF struct fflatdirent *ent, *oldent;
	struct fflatdirenum *me;
	me  = fdirenum_asflat(self);
	dir = fdirnode_asflat(me->de_dir);
again:
	fflatdirenum_lock_acquire(me);
	ent    = me->ffde_next;
	oldpos = me->ffde_pos;
	if (ent) {
		incref(ent);
		oldpos = fflatdirent_basaddr(ent);
	}
	fflatdirenum_lock_release(me);
	if (!ent) {
		/* load directory entries, or find the one most suitable for `oldpos' */
next_next_ent:
		ent = fflatdirnode_entafter(dir, oldpos);
	} else if (fflatdirent_wasdeleted_atomic(ent)) {
		decref_unlikely(ent);
		goto next_next_ent;
	}

	/* Yield `ent' to user-space. */
	FINALLY_DECREF_UNLIKELY(ent);
	result = fdirenum_feedent(buf, bufsize, readdir_mode, ent->fde_ent.fd_ino,
	                          ent->fde_ent.fd_type, ent->fde_ent.fd_namelen,
	                          ent->fde_ent.fd_name);
	if (result < 0)
		return (size_t)~result;

	/* Yield to the next entry. */
	fflatdirnode_read(dir);
	fflatdirenum_lock_acquire(me);
	real_oldpos = me->ffde_pos;
	oldent      = me->ffde_next; /* Inherit reference (on success) */
	if (oldent)
		real_oldpos = fflatdirent_basaddr(oldent);

	/* Check if the enumerator position changed during the read. */
	if unlikely(oldpos != real_oldpos) {
		fflatdirenum_lock_release_br(me);
		fflatdirnode_endread(dir);
		goto again;
	}

	/* Update the enumerator position. */
	me->ffde_pos = fflatdirent_endaddr(ent);
	if unlikely(fflatdirent_wasdeleted(ent)) {
		me->ffde_next = NULL;
	} else {
		me->ffde_next = TAILQ_NEXT(ent, fde_bypos);
		if (me->ffde_next) {
			incref(me->ffde_next);
			DBG_memset(&me->ffde_pos, 0xcc, sizeof(me->ffde_pos));
		}
	}
	fflatdirenum_lock_release(me);
	fflatdirnode_endread(dir);
	xdecref_unlikely(oldent);
	return (size_t)result;
}

PRIVATE NONNULL((1)) pos_t KCALL
fflatdirenum_v_seekdir(struct fdirenum *__restrict self,
                       off_t offset, unsigned int whence)
		THROWS(...) {
	pos_t oldpos, newpos;
	struct fflatdirenum *me = fdirenum_asflat(self);
	fflatdirenum_lock_acquire(me);
	oldpos = me->ffde_pos;
	if (me->ffde_next)
		oldpos = fflatdirent_basaddr(me->ffde_next);
	fflatdirenum_lock_release(me);
again_switch:
	switch (whence) {

	case SEEK_SET:
		newpos = (pos_t)offset;
		break;

	case SEEK_CUR:
		newpos = oldpos + (pos_t)offset;
		if unlikely(offset < 0 ? newpos > oldpos
		                       : newpos < oldpos)
			THROW(E_OVERFLOW);
		break;

	case SEEK_END: {
		/* Must lock the directory to get the absolute end position. */
		pos_t dirsiz = 0;
		struct fflatdirent *last;
		struct fflatdirnode *dir = fdirnode_asflat(me->de_dir);
		fflatdirnode_lockread_and_populate(dir);
		last = TAILQ_LAST(&dir->fdn_data.fdd_bypos);
		if (last)
			dirsiz = fflatdirent_endaddr(last);
		fflatdirnode_endread(dir);
		newpos = dirsiz + (pos_t)offset;
		if unlikely(offset < 0 ? newpos > dirsiz
		                       : newpos < dirsiz)
			THROW(E_OVERFLOW);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	fflatdirenum_lock_acquire(me);
	if (whence == SEEK_CUR) {
		/* Check if the old position changed. */
		pos_t real_oldpos = me->ffde_pos;
		if (me->ffde_next)
			real_oldpos = fflatdirent_basaddr(me->ffde_next);
		if (oldpos != real_oldpos) {
			fflatdirenum_lock_release_br(me);
			oldpos = real_oldpos;
			goto again_switch;
		}
	}
	if (newpos != oldpos) {
		REF struct fflatdirent *ent;
		/* Position changed. */
		ent = me->ffde_next;
		me->ffde_next = NULL;
		me->ffde_pos  = newpos;
		fflatdirenum_lock_release_br(me);
		xdecref_unlikely(ent);
		return newpos;
	}
	fflatdirenum_lock_release(me);
	return newpos;
}


/* Flat directory enumeration operators. */
PRIVATE struct fdirenum_ops const fflatdirenum_ops = {
	.deo_fini    = &fflatdirenum_v_fini,
	.deo_readdir = &fflatdirenum_v_readdir,
	.deo_seekdir = &fflatdirenum_v_seekdir,
};

PUBLIC NONNULL((1)) void KCALL
fflatdirnode_v_enum(struct fdirenum *__restrict result) {
	struct fflatdirenum *rt = (struct fflatdirenum *)result;
	struct fflatdirnode *me = fdirnode_asflat(rt->de_dir);

	/* Fill in the enumerator. */
#ifndef CONFIG_NO_SMP
	atomic_lock_init(&rt->ffde_lock);
#endif /* !CONFIG_NO_SMP */
	rt->ffde_pos = 0;
	fflatdirnode_read(me);
	rt->ffde_next = xincref(TAILQ_FIRST(&me->fdn_data.fdd_bypos));
	fflatdirnode_endread(me);
	rt->de_ops = &fflatdirenum_ops;
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
		assertf(!(pth->fde_ent.fd_hash == hash &&
		          pth->fde_ent.fd_namelen == ent->fde_ent.fd_namelen &&
		          memcmp(pth->fde_ent.fd_name, ent->fde_ent.fd_name,
		                 ent->fde_ent.fd_namelen * sizeof(char)) == 0),
		        "Duplicate entry: %$q",
		        (size_t)ent->fde_ent.fd_namelen, ent->fde_ent.fd_name);
	}
	bucket->ffdb_ent = ent;
	++self->fdn_data.fdd_filesused;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL fflatdirnode_fileslist_tryinsertent)(struct fflatdirnode *__restrict self,
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
		if (pth->fde_ent.fd_hash == hash &&
		    pth->fde_ent.fd_namelen == ent->fde_ent.fd_namelen &&
		    memcmp(pth->fde_ent.fd_name, ent->fde_ent.fd_name,
		           ent->fde_ent.fd_namelen * sizeof(char)) == 0)
			return false; /* Duplicate! */
	}
	bucket->ffdb_ent = ent;
	++self->fdn_data.fdd_filesused;
	return true;
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





/* Default operators for `struct fflatsuper'-derived superblocks. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fflatsuper_v_destroy)(struct mfile *__restrict self) {
	struct fflatsuper *me = mfile_asflatsuper(self);
	STATIC_ASSERT((offsetof(struct fflatsuper, ffs_rootdata) -
	               offsetof(struct fflatsuper, ffs_super.fs_root)) ==
	              offsetof(struct fflatdirnode, fdn_data));
	fflatdirdata_fini(&me->ffs_rootdata);
	fsuper_v_destroy(self);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FLAT_C */
