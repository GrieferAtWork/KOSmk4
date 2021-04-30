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
#ifndef GUARD_KERNEL_CORE_FILESYS_FDIRNODE_LINEAR_C
#define GUARD_KERNEL_CORE_FILESYS_FDIRNODE_LINEAR_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/fdirnode-linear.h>
#include <kernel/fs/fdirnode.h>
#include <kernel/malloc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>

#include <assert.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

/* Finalize the given linear directory controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL flindirdat_fini)(struct flindirdat *__restrict self) {
	REF struct flindirent *iter, *next;
	assert(LIST_EMPTY(&self->ldd_enum));
	iter = TAILQ_FIRST(&self->ldd_bypos);
	while (iter) {
		next = TAILQ_NEXT(iter, fld_bypos);
		decref_likely(iter);
		iter = next;
	}
	kfree(self->ldd_byname_tab);
	DBG_memset(self, 0xcc, sizeof(*self));
}


/* Default callback for `flindirnode_ops::ldno_destory'
 * If  overwritten, sub-classes _must_ invoke this one! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL flindirnode_v_destroy)(struct flindirnode *__restrict self) {
	flindirdat_fini(&self->ldn_dat);
	fdirnode_v_destroy(self);
}








/************************************************************************/
/* LOOKUP                                                               */
/************************************************************************/

PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL lindir_hashmap_insert)(struct flindirbucket *__restrict tab, size_t msk,
                                     struct flindirent *__restrict ent) {
	struct flindirbucket *bucket;
	bucket = &tab[ent->fld_hash & msk];
	SLIST_INSERT(&bucket->ldb_entires, ent, fld_byname);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL lindir_rehash)(struct flindirbucket *__restrict newtab, size_t newmsk,
                             struct flindirbucket const *oldtab, size_t oldmsk) {
	size_t i;
	bzero(newtab, newmsk + 1, sizeof(struct flindirbucket));
	if (!oldtab)
		return; /* Nothing to rehash! */
	for (i = 0; i <= oldmsk; ++i) {
		struct flindirent *iter, *next;
		iter = SLIST_FIRST(&oldtab[i].ldb_entires);
		while (iter) {
			next = SLIST_NEXT(iter, fld_byname);
			lindir_hashmap_insert(newtab, newmsk, iter);
			iter = next;
		}
	}
}

/* Read the next directory entry after `pos', insert it into the map
 * of `self', and  (always) release a  read-lock from `self'  before
 * returning. */
PRIVATE NONNULL((1)) void FCALL
lindir_readmore_and_endread(struct flindirnode *__restrict self) {
	REF struct flindirent *ent;
	pos_t pos = 0;
	if likely(!TAILQ_EMPTY(&self->ldn_dat.ldd_bypos))
		pos = TAILQ_LAST(&self->ldn_dat.ldd_bypos)->fld_maxpos + 1;
	TRY {
		ent = (*flindirnode_getops(self)->ldno_linreaddir)(self, pos);
	} EXCEPT {
		sync_endread(&self->ldn_dat.ldd_flock);
		RETHROW();
	}
	if unlikely(!ent) {
		/* EOF */
		sync_upgrade(&self->ldn_dat.ldd_flock);
		self->ldn_dat.ldd_loaded = true;
		sync_endwrite(&self->ldn_dat.ldd_flock);
		return;
	}
	assert(ent->fld_maxpos >= ent->fld_minpos);
	assert(ent->fld_minpos >= pos);
	TRY {
		/* Upgrade to a write-lock. */
		if (!sync_upgrade(&self->ldn_dat.ldd_flock)) {
			if unlikely(!TAILQ_EMPTY(&self->ldn_dat.ldd_bypos) &&
			            pos <= TAILQ_LAST(&self->ldn_dat.ldd_bypos)->fld_maxpos) {
				/* We didn't actually read the last entry!
				 * Discard   `ent'   and   try    again... */
				sync_endread(&self->ldn_dat.ldd_flock);
				ent->fld_ent.fd_refcnt = 0;
				destroy(ent);
				return;
			}
		}

		/* Rehash the directory entry map if necessary. */
		if (self->ldn_dat.ldd_byname_siz >= self->ldn_dat.ldd_byname_msk) {
			/* Try to re-hash the table. */
			size_t newmsk = (self->ldn_dat.ldd_byname_msk << 1) | 1;
			struct flindirbucket *newtab;
			while (self->ldn_dat.ldd_byname_siz >= newmsk)
				newmsk = (newmsk << 1) | 1;
			if (newmsk < 15)
				newmsk = 15;
			newtab = (struct flindirbucket *)kmalloc_nx((newmsk + 1) * sizeof(struct flindirbucket), GFP_NORMAL);
			if (!newtab && !self->ldn_dat.ldd_byname_tab) {
				newmsk = 0;
				TRY {
					newtab = (struct flindirbucket *)kmalloc(1 * sizeof(struct flindirbucket), GFP_NORMAL);
				} EXCEPT {
					sync_endwrite(&self->ldn_dat.ldd_flock);
					RETHROW();
				}
			}

			/* Re-hash the old table. */
			lindir_rehash(self->ldn_dat.ldd_byname_tab,
			              self->ldn_dat.ldd_byname_msk,
			              newtab, newmsk);

			/* Write-back the new table. */
			kfree(self->ldn_dat.ldd_byname_tab);
			self->ldn_dat.ldd_byname_msk = newmsk;
			self->ldn_dat.ldd_byname_tab = newtab;
		}
	} EXCEPT {
		ent->fld_ent.fd_refcnt = 0;
		destroy(ent);
		RETHROW();
	}
	/* Insert the new entry into the bypos-list. */
	ent->fld_ent.fd_refcnt = 1;
	TAILQ_INSERT_TAIL(&self->ldn_dat.ldd_bypos, ent, fld_bypos); /* Inherit reference */

	/* Insert the new entry into the hash-table. */
	{
		struct flindirbucket *bucket;
		bucket = &self->ldn_dat.ldd_byname_tab[ent->fld_hash & self->ldn_dat.ldd_byname_msk];
		SLIST_INSERT(&bucket->ldb_entires, ent, fld_byname);
		++self->ldn_dat.ldd_byname_siz;
	}
	sync_endwrite(&self->ldn_dat.ldd_flock);
}



/* Default callback for `flindirnode_ops::ldno_*' */
PUBLIC WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
flindirnode_v_lookup(struct flindirnode *__restrict self,
                     struct flookup_info *__restrict info) {
	REF struct flindirent *result;
	struct flindirbucket *bucket;
again:
	sync_read(&self->ldn_dat.ldd_flock);
	bucket = &self->ldn_dat.ldd_byname_tab[info->flu_hash & self->ldn_dat.ldd_byname_msk];
	result = SLIST_FIRST(&bucket->ldb_entires);

	/* Search through this list. */
	for (; result; result = SLIST_NEXT(result, fld_byname)) {
		if (result->fld_hash != info->flu_hash)
			continue;
		if (result->fld_ent.fd_namelen != info->flu_namelen)
			continue;
		TRY {
			if (memcmp(result->fld_ent.fd_name, info->flu_name,
			           info->flu_namelen * sizeof(char)) != 0)
				continue;
		} EXCEPT {
			sync_endread(&self->ldn_dat.ldd_flock);
			RETHROW();
		}
		/* Found it! */
		incref(result);
		sync_endread(&self->ldn_dat.ldd_flock);
		return &result->fld_ent;
	}

	if (info->flu_flags & FS_MODE_FDOSPATH) {
		/* Search through all entires, but ignore ASCII casing. */
		TAILQ_FOREACH (result, &self->ldn_dat.ldd_bypos, fld_bypos) {
			if (result->fld_ent.fd_namelen != info->flu_namelen)
				continue;
			TRY {
				if (memcasecmp(result->fld_ent.fd_name, info->flu_name,
				               info->flu_namelen * sizeof(char)) != 0)
					continue;
			} EXCEPT {
				sync_endread(&self->ldn_dat.ldd_flock);
				RETHROW();
			}
			/* Found it! */
			incref(result);
			sync_endread(&self->ldn_dat.ldd_flock);
			return &result->fld_ent;
		}
	}

	/* Try to load more entries. */
	if (!self->ldn_dat.ldd_loaded) {
		lindir_readmore_and_endread(self);
		goto again;
	}

	/* Not found... */
	sync_endread(&self->ldn_dat.ldd_flock);
	return NULL;
}
/************************************************************************/






/************************************************************************/
/* ENUM                                                                 */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ldenum_fini)(struct flindirenum *__restrict self) {
	REF struct flindirnode *dir;
	dir = self->lde_dir;

	/* Remove from the list of iterators. */
	mfile_tslock_acquire(dir);
	LIST_REMOVE(self, lde_all);
	mfile_tslock_release(dir);

	decref_unlikely(dir);
}



PRIVATE NONNULL((1)) size_t KCALL
ldenum_readdir(struct flindirenum *__restrict self, USER CHECKED struct dirent *buf,
               size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
		THROWS(...) {
	REF struct flindirent *ent;
	struct flindirnode *dir = self->lde_dir;
	size_t result;
	pos_t pos;
again:
	sync_read(&dir->ldn_dat.ldd_flock);
	ent = ATOMIC_READ(self->lde_ent);
	pos = (pos_t)atomic64_read(&self->lde_pos);
	if (!ent || !tryincref(ent)) {
		/* Load the an entry `ent' such that:
		 *     pos <= ent->fld_maxpos
		 *     pos > ent->PREV->fld_maxpos
		 */
		ent = TAILQ_LAST(&dir->ldn_dat.ldd_bypos);
		if unlikely(!ent) {
			/* Load directory entries. */
			goto loadmore;
		} else if (pos < ent->fld_minpos) {
			pos_t before, after;
			before = pos;
			after  = ent->fld_minpos - pos;
			/* Scan towards the requested entry. */
			if (before < after) {
				/* Scan from the front. */
				ent = TAILQ_FIRST(&dir->ldn_dat.ldd_bypos);
				while (pos > ent->fld_maxpos)
					ent = TAILQ_NEXT(ent, fld_bypos);
			} else {
				/* Scan from the back. */
				while (pos < ent->fld_minpos)
					ent = TAILQ_PREV(ent, fld_bypos);
			}
			assert(pos <= ent->fld_maxpos);
			assert(TAILQ_PREV(ent, fld_bypos) == NULL ||
			       pos > TAILQ_PREV(ent, fld_bypos)->fld_maxpos);
		} else {
loadmore:
			if (dir->ldn_dat.ldd_loaded) {
				sync_endread(&dir->ldn_dat.ldd_flock);
				return 0; /* EOF */
			}
			/* Load entries until the one that includes `pos',
			 * or until the end  of the directory is  reached. */
			lindir_readmore_and_endread(dir);
			goto again;
		}
	}

	/* Figure out how much data to write to user-space. */
	result = (offsetof(struct dirent, d_name)) +
	         (ent->fld_ent.fd_namelen + 1) * sizeof(char);
	if (bufsize >= offsetof(struct dirent, d_name)) {
		bufsize -= offsetof(struct dirent, d_name);
		if (bufsize >= (size_t)(ent->fld_ent.fd_namelen + 1) * sizeof(char)) {
			bufsize = (size_t)(ent->fld_ent.fd_namelen + 1) * sizeof(char);
			if likely((readdir_mode & READDIR_MODEMASK) != READDIR_PEEK) {
do_advance_ent:
				ATOMIC_WRITE(self->lde_ent, TAILQ_NEXT(ent, fld_bypos));
				if unlikely(!atomic64_cmpxch(&self->lde_pos, (u64)pos, (u64)ent->fld_maxpos + 1))
					goto again_discard_ent;
			}
		} else {
			if ((readdir_mode & READDIR_MODEMASK) == READDIR_CONTINUE)
				goto do_advance_ent;
		}
		sync_endread(&dir->ldn_dat.ldd_flock);
		COMPILER_WRITE_BARRIER();
		FINALLY_DECREF_UNLIKELY(ent);
		buf->d_ino    = (__ino64_t)ent->fld_ent.fd_ino;
		buf->d_type   = ent->fld_ent.fd_type;
		buf->d_namlen = ent->fld_ent.fd_namelen;
		memcpy(buf->d_name, ent->fld_ent.fd_name, bufsize);
	} else {
		if ((readdir_mode & READDIR_MODEMASK) == READDIR_CONTINUE) {
			/* Always advance! */
			ATOMIC_WRITE(self->lde_ent, TAILQ_NEXT(ent, fld_bypos));
			if unlikely(!atomic64_cmpxch(&self->lde_pos, (u64)pos, (u64)ent->fld_maxpos + 1))
				goto again_discard_ent;
		}
		sync_endread(&dir->ldn_dat.ldd_flock);
		decref_unlikely(ent);
	}
	return result;
again_discard_ent:
	sync_endread(&dir->ldn_dat.ldd_flock);
	decref_unlikely(ent);
	goto again;
}


PRIVATE NONNULL((1)) pos_t KCALL
ldenum_seekdir(struct flindirenum *__restrict self,
               off_t offset, unsigned int whence)
		THROWS(...) {
	pos_t oldpos, newpos;
	struct flindirnode *dir = self->lde_dir;
again:
	oldpos = (pos_t)atomic64_read(&self->lde_pos);
	switch (whence) {

	case SEEK_SET:
		newpos = (pos_t)offset;
		break;

	case SEEK_CUR:
		newpos = oldpos + (pos_t)offset;
		if unlikely(offset < 0 ? newpos > oldpos
		                       : newpos < oldpos) {
err_overflow:
			sync_endread(&dir->ldn_dat.ldd_flock);
			THROW(E_OVERFLOW);
		}
		break;

	case SEEK_END: {
		pos_t size;
		if (!ATOMIC_READ(dir->ldn_dat.ldd_loaded)) {
			sync_read(&dir->ldn_dat.ldd_flock);
			if (!dir->ldn_dat.ldd_loaded) {
				lindir_readmore_and_endread(dir);
			} else {
				sync_endread(&dir->ldn_dat.ldd_flock);
			}
			goto again;
		}
		size = 0;
		if likely(!TAILQ_EMPTY(&dir->ldn_dat.ldd_bypos))
			size = TAILQ_LAST(&dir->ldn_dat.ldd_bypos)->fld_maxpos + 1;
		if unlikely(OVERFLOW_USUB(size, (pos_t)-offset, &newpos))
			goto err_overflow;
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	ATOMIC_WRITE(self->lde_ent, NULL);
	/* Set the new file position. */
	if (!atomic64_cmpxch(&self->lde_pos, (u64)oldpos, (u64)newpos))
		goto again;
	return newpos;
}


PRIVATE struct fdirenum_ops const ldenum_ops = {
	.deo_fini    = (NOBLOCK NONNULL((1)) void /*NOTHROW*/ (KCALL *)(struct fdirenum *__restrict))&ldenum_fini,
	.deo_readdir = (NONNULL((1)) size_t (KCALL *)(struct fdirenum *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t) THROWS(...))&ldenum_readdir,
	.deo_seekdir = (NONNULL((1)) pos_t (KCALL *)(struct fdirenum *__restrict, off_t, unsigned int) THROWS(...))&ldenum_seekdir
};

STATIC_ASSERT(sizeof(struct flindirenum) <= sizeof(struct fdirenum));
STATIC_ASSERT(offsetof(struct flindirenum, lde_ops) == offsetof(struct fdirenum, de_ops));
PUBLIC NONNULL((1, 2)) void KCALL
flindirnode_v_enum(struct flindirnode *__restrict self,
                   struct fdirenum *__restrict result) {
	struct flindirenum *res;
	res = (struct flindirenum *)result;

	res->lde_ops = &ldenum_ops;
	res->lde_dir = (REF struct flindirnode *)incref(self);
	atomic64_init(&res->lde_pos, 0);
	res->lde_ent = NULL;

	/* Add the new enumerator to the list of all enumerators. */
	mfile_tslock_acquire(self);
	LIST_INSERT_HEAD(&self->ldn_dat.ldd_enum, res, lde_all);
	mfile_tslock_release(self);
}
/************************************************************************/






/************************************************************************/
/* MODIFICATIONS                                                        */
/************************************************************************/

/* Load all on-disk entries of `self', and acquire a write-lock */
PRIVATE NONNULL((1)) void FCALL
lindir_loadall_and_write(struct flindirnode *__restrict self) {
again:
	sync_write(&self->ldn_dat.ldd_flock);
	if (!self->ldn_dat.ldd_loaded) {
		sync_downgrade(&self->ldn_dat.ldd_flock);
		lindir_readmore_and_endread(self);
		goto again;
	}
}

PUBLIC NONNULL((1, 2)) void KCALL
flindirnode_v_mkfile(struct flindirnode *__restrict self,
                     struct fmkfile_info *__restrict info) {
	lindir_loadall_and_write(self);
	/* TODO */
	sync_endwrite(&self->ldn_dat.ldd_flock);
}

PUBLIC NONNULL((1, 2, 3)) void KCALL
flindirnode_v_unlink(struct flindirnode *__restrict self,
                     struct fdirent *__restrict entry,
                     struct fnode *__restrict file) {
	lindir_loadall_and_write(self);
	/* TODO */
	sync_endwrite(&self->ldn_dat.ldd_flock);
}

PUBLIC NONNULL((1, 2)) void KCALL
flindirnode_v_rename(struct flindirnode *__restrict self,
                     struct frename_info *__restrict info) {
	lindir_loadall_and_write(self);
	/* TODO */
	sync_endwrite(&self->ldn_dat.ldd_flock);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FDIRNODE_LINEAR_C */
