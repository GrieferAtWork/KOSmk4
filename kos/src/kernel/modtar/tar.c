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
#ifndef GUARD_MODTARFS_TAR_C
#define GUARD_MODTARFS_TAR_C 1
#define __WANT_FNODE_FSDATAINT
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "tar.h"
/**/

#include <kernel/compiler.h>

#include <kernel/driver-callbacks.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/mman/cc.h>
#include <sched/atomic64.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/wordbits.h>

#include <kos/dev.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <format-printer.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

static_assert(offsetof(struct tarhdr, th_type) == 156);
static_assert(offsetof(struct tarhdr, th_devmajor) == 329);
static_assert(sizeof(struct tarhdr) == 500);

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/************************************************************************/
/* Directory entry operators.                                           */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tardirent_v_destroy)(struct fdirent *__restrict self) {
	struct tardirent *me;
	me = container_of(self, struct tardirent, td_ent);
	decref(me->td_filp);
	kfree(me);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
tardirent_v_opennode(struct fdirent *__restrict self,
                     struct fdirnode *__restrict dir_)
		THROWS(E_BADALLOC, E_IOERROR, ...) {
	struct tardirnode *dir;
	struct tardirent *me;
	struct tarsuper *super;
	struct tarfdat *rfdat;
	struct tarfile *tfile;
	REF struct fnode *result;
	dir   = (struct tardirnode *)dir_;
	me    = container_of(self, struct tardirent, td_ent);
	super = container_of(dir->fn_super, struct tarsuper, ts_super);
	tfile = me->td_filp;

	/* Check if this file is already open. */
again:
	fsuper_nodes_read(&super->ts_super);
	result = fsuper_nodes_locate(&super->ts_super, me->td_ent.fd_ino);
	if (result) {
		if likely(tryincref(result)) {
			fsuper_nodes_endread(&super->ts_super);
			return result;
		}
		if (!fsuper_nodes_upgrade(&super->ts_super))
			result = fsuper_nodes_locate(&super->ts_super, me->td_ent.fd_ino);

		/* Remove already-deleted files from the superblock's file tree. */
		if (result) {
			assert(wasdestroyed(result));
			fsuper_nodes_removenode(&super->ts_super, result);
			result->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
			fsuper_nodes_downgrade(&super->ts_super);
		}
	}
	fsuper_nodes_endread(&super->ts_super);

	/* Construct a new file-node object. */
	switch (me->td_ent.fd_type) {

	case DT_DIR: {
		struct tardirnode *node;
		node = (struct tardirnode *)kmalloc(sizeof(struct tardirnode), GFP_NORMAL);
		node->mf_ops = &tardirnode_ops.dno_node.no_file;
		rfdat        = &node->tdn_fdat;
		result       = node;
	}	break;

	case DT_REG: {
		struct tarregnode *node;
		node = (struct tarregnode *)kmalloc(sizeof(struct tarregnode), GFP_NORMAL);
		node->mf_ops = &tarregnode_ops.rno_node.no_file;
		rfdat        = &node->trn_fdat;
		result       = node;
	}	break;

	case DT_LNK: {
		struct tarlnknode *node;
		node = (struct tarlnknode *)kmalloc(sizeof(struct tarlnknode), GFP_NORMAL);
		node->mf_ops = &tarlnknode_ops.lno_node.no_file;
		rfdat        = &node->tln_fdat;
		result       = node;
	}	break;

	case DT_CHR:
	case DT_BLK: {
		struct tardevnode *node;
		node = (struct tardevnode *)kmalloc(sizeof(struct tardevnode), GFP_NORMAL);
		node->mf_ops   = &tardevnode_ops.dvno_node.no_file;
		node->dn_devno = tarfile_getdevno(tfile);
		rfdat          = &node->tln_fdat;
		result         = node;
	}	break;

	default:
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
	}

	/* Fill in tar-specific fields. */
	rfdat->tfd_filp = incref(tfile);
	rfdat->tfd_name = tfile->tf_name;
	rfdat->tfd_nlen = (uint8_t)strlen(tfile->tf_name);
	assert(rfdat->tfd_nlen >= me->td_ent.fd_namelen);

	/* Fill in mem-file fields. */
	_mfile_init_common(result);
	_mfile_init_blockshift(result, TBLOCKSHIFT, super->ts_super.fs_root.mf_iobashift);
	result->mf_refcnt            = 2; /* +1: result, +1: MFILE_FN_GLOBAL_REF */
	result->mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	atomic64_init(&result->mf_filesize, tfile->tf_size);

	/* Setup default file flags. */
	result->mf_flags = (MFILE_F_READONLY | MFILE_FN_GLOBAL_REF | MFILE_F_NOATIME |
	                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_NOMTIME |
	                    MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY);
	result->mf_atime.tv_sec  = tfile->tf_mtim;
	result->mf_atime.tv_nsec = 0;
	result->mf_mtime.tv_sec  = tfile->tf_mtim;
	result->mf_mtime.tv_nsec = 0;
	result->mf_ctime.tv_sec  = tfile->tf_mtim;
	result->mf_ctime.tv_nsec = 0;
	result->mf_btime.tv_sec  = tfile->tf_mtim; /* XXX: Birthtime of mounted tar file? */
	result->mf_btime.tv_nsec = 0;

	/* Fill in file-node fields. */
	result->fn_nlink = 1;
	result->fn_mode  = tfile->tf_mode;
	result->fn_uid   = (uid_t)tfile->tf_uid;
	result->fn_gid   = (gid_t)tfile->tf_gid;
	result->fn_ino   = me->td_ent.fd_ino;
	if (me->td_ent.fd_type == DT_DIR) {
		/* Check if `tfile' is actually the descriptor for this directory. (or just some random file) */
		uint8_t parent_dir_size;
		char const *local_filename;
		parent_dir_size = dir->tdn_fdat.tfd_nlen;
		assertf(dir->tdn_fdat.tfd_filp == NULL ||
		        memcmp(dir->tdn_fdat.tfd_filp->tf_name, tfile->tf_name, parent_dir_size) == 0,
		        "dir->tdn_fdat.tfd_filp->tf_name = %q\n"
		        "tfile->tf_name                  = %q\n",
		        dir->tdn_fdat.tfd_filp->tf_name, tfile->tf_name);
		if (dir->tdn_fdat.tfd_filp != NULL) {
			assertf(tfile->tf_name[parent_dir_size] == '/',
			        "tfile->tf_name = %q", tfile->tf_name);
			++parent_dir_size; /* Skip '/' */
		} else {
			assert(parent_dir_size == 0);
		}
		local_filename = tfile->tf_name + parent_dir_size;
		assertf(memcmp(local_filename, me->td_ent.fd_name, me->td_ent.fd_namelen) == 0,
		        "local_filename     = %q\n"
		        "me->td_ent.fd_name = %q\n",
		        local_filename, me->td_ent.fd_name);

		/* If what we have isn't the actual directory file, then use stub defaults instead. */
		if (local_filename[me->td_ent.fd_namelen] != '\0') {
			/* Implicit directory... */
			rfdat->tfd_nlen = (uint8_t)(size_t)(&local_filename[me->td_ent.fd_namelen] - tfile->tf_name);
			result->fn_mode = S_IFDIR | 0555;
			result->fn_uid  = 0;
			result->fn_gid  = 0;
			mfile_tslock_acquire(&super->ts_super.fs_root);
			result->mf_atime = super->ts_super.fs_root.mf_btime;
			mfile_tslock_release(&super->ts_super.fs_root);
			result->mf_mtime = result->mf_atime;
			result->mf_ctime = result->mf_atime;
			result->mf_btime = result->mf_atime;
		}
		atomic64_init(&result->mf_filesize, (uint64_t)-1);
		result->mf_flags |= MFILE_FN_NODIRATIME;
	}
	assert(IFTODT(result->fn_mode) == me->td_ent.fd_type);

	/* Allow mmap and general raw io for regular files. */
	if (S_ISREG(result->fn_mode)) {
		result->mf_parts             = NULL;
		result->mf_changed.slh_first = NULL;
		result->mf_flags &= ~(MFILE_F_NOUSRIO | MFILE_F_NOUSRMMAP);
	}

	result->fn_super = incref(&super->ts_super);
	LIST_ENTRY_UNBOUND_INIT(&result->fn_changed);
	DBG_memset(&result->fn_supent, 0xcc, sizeof(result->fn_supent));
	result->fn_supent.rb_rhs = FSUPER_NODES_DELETED; /* Fully initialized below */
	LIST_ENTRY_UNBOUND_INIT(&result->fn_allnodes);   /* Fully initialized below */
	result->fn_fsdata = rfdat;

	/* Remember the newly constructed file-node. */
	TRY {
again_acquire_locks:
		fsuper_nodes_write(&super->ts_super);
		if (!fallnodes_tryacquire()) {
			fsuper_nodes_endwrite(&super->ts_super);
			fallnodes_waitfor();
			goto again_acquire_locks;
		}
	} EXCEPT {
		destroy(result);
		RETHROW();
	}

	/* Insert the new file into the superblock's file-node tree. */
	if unlikely(!fsuper_nodes_tryinsert(&super->ts_super, result)) {
		/* Some other thread created the file in the mean time! */
		REF struct fnode *new_result;
		new_result = fsuper_nodes_locate(&super->ts_super, result->fn_ino);
		assert(new_result);
		if unlikely(!tryincref(new_result))
			new_result = NULL;
		fsuper_nodes_endwrite(&super->ts_super);
		destroy(result);
		if likely(new_result)
			return new_result;
		goto again;
	}

	/* Also add the new file to the global list of all files. */
	fallnodes_insert(result);

	/* Release locks. */
	fallnodes_release();
	fsuper_nodes_endwrite(&super->ts_super);

	/* Return the new file-node. */
	return result;
}





/************************************************************************/
/* Common operators.                                                    */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ssize_t KCALL
tarnode_v_printlink(struct mfile *__restrict self, pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	struct fnode *me   = mfile_asnode(self);
	struct tarfdat *fd = me->fn_fsdata;
	ssize_t temp, result;
	result = (*printer)(arg, "inode:[tarfs:", 13);
	if unlikely(result < 0)
		goto done;
	temp = mfile_uprintlink(me->fn_super->fs_dev, printer, arg);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = format_printf(printer, arg, ":/%$s]",
	                     (size_t)fd->tfd_nlen,
	                     fd->tfd_name);
	if unlikely(temp < 0)
		goto err;
	result += temp;

done:
	return result;
err:
	return temp;
}





/************************************************************************/
/* Directory operators.                                                 */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tardir_v_destroy)(struct mfile *__restrict self) {
	struct tardirnode *me;
	me = (struct tardirnode *)fnode_asdir(self);
	decref(me->tdn_fdat.tfd_filp);
	fdirnode_v_destroy(self);
}


/* Return a pointer to the tarfile with the lowest  disk-position
 * who's filename still matches `tf->tf_name...+=dirlen_plus_one'
 *
 * @param: tf:              Template tarfile
 * @param: indexof_tf:      The index of `tf' within `self->ts_filev'
 * @param: dirlen_plus_one: The # of characters to match from `tf' */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct tarfile *FCALL
tarsuper_find_first_subtree_file(struct tarsuper const *__restrict self,
                                 struct tarfile *__restrict tf,
                                 size_t indexof_tf,
                                 uint8_t dirlen_plus_one) {
	struct tarfile *result = tf;
	size_t i;
	for (i = indexof_tf; i--; task_serve()) {
		struct tarfile *ot = self->ts_filev[i];
		if (memcmp(ot->tf_name, tf->tf_name, dirlen_plus_one * sizeof(char)) != 0)
			break;
		if (result->tf_pos > ot->tf_pos)
			result = ot;
	}
	for (i = indexof_tf + 1; i < self->ts_filec; ++i, task_serve()) {
		struct tarfile *ot = self->ts_filev[i];
		if (memcmp(ot->tf_name, tf->tf_name, dirlen_plus_one * sizeof(char)) != 0)
			break;
		if (result->tf_pos > ot->tf_pos)
			result = ot;
	}
	return result;
}


PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
tardir_v_lookup(struct fdirnode *__restrict self,
                struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	struct tarfile *tf;
	char filename[256]; /* TAR cannot contain filenames longer than this, even with USTAR */
	struct tardirnode *me  = (struct tardirnode *)self;
	struct tarsuper *super = container_of(me->fn_super, struct tarsuper, ts_super);
	char const *prefix_str;
	uint8_t prefix_len;
	size_t filename_len;

	/* Figure out the prefix for the requested filename. */
	prefix_str = me->tdn_fdat.tfd_name;
	prefix_len = me->tdn_fdat.tfd_nlen;

	/* Figure out the absolute on-disk filename that is*/
	filename_len = snprintf(filename, COMPILER_LENOF(filename), "%$s%s%$s",
	                        (size_t)prefix_len, prefix_str,
	                        me->tdn_fdat.tfd_filp ? "/" : "",
	                        (size_t)info->flu_namelen, info->flu_name);
	if unlikely(filename_len >= COMPILER_LENOF(filename))
		return NULL; /* Filename is too long and can't appear in a tar archive. */

	/* Acquire a read-lock to `me->ts_lock' */
again:
	tarsuper_read(super);

	/* Search  through `me->ts_filev' for a files that starts with the requested
	 * prefix. If one is found that matches `filename' use that one.  Otherwise,
	 * if one is found that starts with `filename + "/"', use that one, and have
	 * the file reference a directory. */
	TRY {
		size_t lo, hi;
		lo = 0;
		hi = super->ts_filec;
		while (lo < hi) {
			size_t i;
			int cmp;
			i   = (lo + hi) / 2;
			tf  = super->ts_filev[i];
			/* Compare based on requested filename prefix. */
			cmp = memcmp(tf->tf_name, filename, filename_len * sizeof(char));
			if (cmp < 0) {
				lo = i + 1;
			} else if (cmp > 0) {
				hi = i;
			} else {
				/* Same prefix: check what comes after. */
				char after;
				after = tf->tf_name[filename_len];
				if (after == '\0')
					goto incref_and_return_tf; /* Found an exact match! */
				if (after == '/') {
					/* Implicit directory. - Check if there is an explicit entry for it also. */
					hi = i; /* We're looking for a trailing '\0', which would come before '/' */
					while (lo < hi) {
						struct tarfile *tf2;
						size_t i2;
						i2  = (lo + hi) / 2;
						tf2 = super->ts_filev[i2];
						/* Compare based on requested filename prefix. */
						cmp = memcmp(tf2->tf_name, filename, (filename_len + 1) * sizeof(char));
						if (cmp < 0) {
							lo = i2 + 1;
						} else if (cmp > 0) {
							hi = i2;
						} else {
							tf = tf2; /* Explicit entry _does_ exist! */
							goto incref_and_return_tf;
						}
					}
					/* Must  always  use the  _first_ file  that  describes some  implicit directory!
					 * This must be done to guaranty consistency of implicit-directory INode numbers. */
					if (tf->tf_name[filename_len] == '/')
						tf = tarsuper_find_first_subtree_file(super, tf, i, filename_len + 1);
					goto incref_and_return_tf;
				}
				if (after > MAX_C('\0', '/')) {
					hi = i;
				} else if (after < MIN_C('\0', '/')) {
					lo = i + 1;
				} else {
					/* Special case: the file we're looking for may exist as either
					 *               a direct file ('\0'  tail), or as a  directory
					 *               ('/' tail). In this case, first search for the
					 *               direct variant before checking the dir-one. */
					size_t lo2, hi2;
					lo2 = lo;
					hi2 = hi;
					++filename_len; /* Include trailing NUL in compare */
					while (lo2 < hi2) {
						size_t i2;
						i2 = (lo2 + hi2) / 2;
						tf = super->ts_filev[i2];
						/* Compare based on requested filename prefix. */
						cmp = memcmp(tf->tf_name, filename, filename_len * sizeof(char));
						if (cmp < 0) {
							lo2 = i2 + 1;
						} else if (cmp > 0) {
							hi2 = i2;
						} else {
							/* Found a variant without a trailing '/' */
							goto incref_and_return_tf;
						}
					}
					--filename_len;

					/* Use the normal code path to search for the trailing-/ variant. */
					lo = i + 1;
				}
			}
		}

		/* When AT_DOSPATH is given, load min/max bounds of `prefix_str...+=prefix_len',
		 * as  in: the first and last already-loaded file apart of the parent dir. Then,
		 * walk  all those files  and strcasecmp() their  `basename(3)' to the requested
		 * filename. */
		if (info->flu_flags & AT_DOSPATH) {
			char const *basename; /* basename(3) of the queried file. */
			size_t dirlen;        /* Length of the directory prefix in `filename' */
			dirlen   = filename_len - info->flu_namelen;
			basename = filename + dirlen;
			lo = 0;
			hi = super->ts_filec;
			while (lo < hi) {
				size_t i;
				int cmp;
				i   = (lo + hi) / 2;
				tf  = super->ts_filev[i];
				cmp = memcmp(tf->tf_name, filename, dirlen * sizeof(char));
				if (cmp > 0) {
					hi = i;
				} else if (cmp < 0) {
					lo = i + 1;
				} else {
					lo = i;
					hi = i + 1;
					break;
				}
			}
			if (lo < hi) {
				size_t i;
				/* Search for the requested file below and above. */
				for (i = lo;;) {
					tf = super->ts_filev[i];
					if (memcmp(tf->tf_name, filename, dirlen * sizeof(char)) != 0)
						break;
					/* Check trailing name. */
					if (memcasecmp(tf->tf_name + dirlen, basename, info->flu_namelen * sizeof(char)) == 0) {
						if (tf->tf_name[filename_len] == '\0')
							goto incref_and_return_tf;
						if (tf->tf_name[filename_len] == '/') {
							/* Must  always  use the  _first_ file  that  describes some  implicit directory!
							 * This must be done to guaranty consistency of implicit-directory INode numbers. */
							tf = tarsuper_find_first_subtree_file(super, tf, i, filename_len + 1);
							goto incref_and_return_tf;
						}
					}
					if (i == 0)
						break;
					--i;
					task_serve();
				}
				for (i = hi; i < super->ts_filec; ++i) {
					tf = super->ts_filev[i];
					if (memcmp(tf->tf_name, filename, dirlen * sizeof(char)) != 0)
						break;
					/* Check trailing name. */
					if (memcasecmp(tf->tf_name + dirlen, basename, info->flu_namelen * sizeof(char)) == 0) {
						if (tf->tf_name[filename_len] == '\0')
							goto incref_and_return_tf;
						if (tf->tf_name[filename_len] == '/') {
							/* Must  always  use the  _first_ file  that  describes some  implicit directory!
							 * This must be done to guaranty consistency of implicit-directory INode numbers. */
							tf = tarsuper_find_first_subtree_file(super, tf, i, filename_len + 1);
							goto incref_and_return_tf;
						}
					}
					task_serve();
				}
			}
		}
	} EXCEPT {
		tarsuper_endread(super);
		RETHROW();
	}

	/* Keep on scanning  for the requested  file via  `tarsuper_readdir_or_unlock()'.
	 * When that function returns `TARSUPER_READDIR_EOF', give up. When that function
	 * returns `TARSUPER_READDIR_AGAIN', start over by re-acquiring the read-lock and
	 * scanning for the requested file. */
again_readdir:
	tf = tarsuper_readdir_or_unlock(super);

	/* Check for special return values. */
	if (tf == TARSUPER_READDIR_EOF)
		return NULL; /* No such file :( */
	if (tf == TARSUPER_READDIR_AGAIN)
		goto again; /* Lock was lost... */

	/* Check if `tf' is the requested file. (No TRY needed, because `filename' is allocated on the stack) */
	if (memcmp(tf->tf_name, filename, filename_len * sizeof(char)) == 0 &&
	    (tf->tf_name[filename_len] == '\0' || tf->tf_name[filename_len] == '/')) {
incref_and_return_tf:
		incref(tf);
		tarsuper_endread(super);
		goto return_tf;
	}

	/* Also do the case-insensitive compare. (if necessary) */
	if (info->flu_flags & AT_DOSPATH) {
		char const *basename; /* basename(3) of the queried file. */
		size_t dirlen;        /* Length of the directory prefix in `filename' */
		dirlen   = filename_len - info->flu_namelen;
		basename = filename + dirlen;
		if (memcmp(tf->tf_name, filename, dirlen * sizeof(char)) == 0 &&
		    memcasecmp(tf->tf_name + dirlen, basename, info->flu_namelen * sizeof(char)) == 0 &&
		    (tf->tf_name[filename_len] == '\0' || tf->tf_name[filename_len] == '/'))
			goto incref_and_return_tf;
	}

	/* Read more files... */
	goto again_readdir;
	{
		REF struct tardirent *result;
return_tf:
		TRY {
			result = (REF struct tardirent *)kmalloc(offsetof(struct tardirent, td_ent.fd_name) +
			                                         (info->flu_namelen + 1) * sizeof(char),
			                                         GFP_NORMAL);
		} EXCEPT {
			decref_unlikely(tf);
			RETHROW();
		}

		/* Fill in the new directory entry. */
		result->td_filp          = tf; /* Inherit reference */
		result->td_ent.fd_refcnt = 1;
		result->td_ent.fd_ops    = &tardirent_ops;
		result->td_ent.fd_ino    = tarfile_getino(tf);
		result->td_ent.fd_type   = IFTODT(tf->tf_mode);
		assert(tf->tf_name[filename_len] == '\0' ||
		       tf->tf_name[filename_len] == '/');
		if (tf->tf_name[filename_len] == '/') {
			result->td_ent.fd_type = DT_DIR; /* Implicit directory */
			result->td_ent.fd_ino  = tarfile_getdirino(tf, filename_len);
		}
		result->td_ent.fd_namelen = info->flu_namelen;
		memcpy(result->td_ent.fd_name,
		       filename + filename_len - result->td_ent.fd_namelen,
		       result->td_ent.fd_namelen + 1, sizeof(char));
		result->td_ent.fd_hash = fdirent_hash(result->td_ent.fd_name, result->td_ent.fd_namelen);

		return &result->td_ent;
	}
}





struct tardirenum: fdirenum {
	/* Enumerate files based  on `tf_pos'  (iow: disk  position)
	 * For this purpose, we seekdir() simply alters the absolute
	 * on-disk  position, and readdir() yields the first tarfile
	 * that  has a name  that starts with the  prefix of the dir
	 * being enumerated, followed by a '/', and doesn't  contain
	 * any additional '/'s thereafter.
	 *
	 * - Use  `ts_nfile' to determine if all files until the min disk
	 *   address of the next file to-be read have already been loaded
	 * - Use `ts_bypos' to enumerate files based on disk-order
	 * - Use `ts_filev' to narrow down files within the current dir. */
	struct tarsuper *tde_super;   /* [1..1][const] Superblock. */
	atomic64_t       tde_pos;     /* [lock(ATOMIC)] Lower bound for next file to yield. */
	char const      *tde_dirname; /* [0..tde_dirsize][const] Required filename prefix. (excluding a trailing '/') */
	uint8_t          tde_dirsize; /* [const] Length of `tde_dirname'. */
};

LOCAL NONNULL((1)) void FCALL
tarsuper_serve_or_unlock(struct tarsuper *__restrict self) {
	TRY {
		task_serve();
	} EXCEPT {
		tarsuper_endread(self);
		RETHROW();
	}
}

/* Return the first file at a position `>= pos' that starts with the
 * string in `self->tde_dirname...+=self->tde_dirsize', followed  by
 * a '/'. Returns `NULL' if no such file exists. Locking logic:
 * @return: * :                     No lock was ever released
 * @return: TARSUPER_READDIR_EOF:   Read-lock released
 * @return: TARSUPER_READDIR_AGAIN: Read-lock released */
PRIVATE WUNUSED NONNULL((1)) struct tarfile *FCALL
tardirenum_peekfile_raw(struct tardirenum const *__restrict self, pos_t pos) {
	/* First of: make sure that the disk has been loaded until at least after `pos' */
	struct tarsuper *super = self->tde_super;
	struct tarfile *tf;
	if (pos < super->ts_nfile) {
		/* Search through already-loaded file with the required
		 * prefix for  the first  one that  comes after  `pos'. */
		size_t lo, hi;
		lo = 0;
		hi = super->ts_filec;
		while (lo < hi) {
			size_t i;
			int cmp;
			i   = (lo + hi) / 2;
			tf  = super->ts_filev[i];
			cmp = memcmp(tf->tf_name, self->tde_dirname, self->tde_dirsize * sizeof(char));
			if (cmp > 0) {
				hi = i;
			} else if (cmp < 0) {
				lo = i + 1;
			} else {
				lo = i;
				hi = i + 1;
				break;
			}
		}
		if (lo < hi) {
			size_t i;
			/* Search for the requested file below and above. */
			tf = NULL;
			for (i = lo;;) {
				struct tarfile *ntf;
				ntf = super->ts_filev[i];
				if (memcmp(ntf->tf_name, self->tde_dirname, self->tde_dirsize * sizeof(char)) != 0)
					break;
				if ((self->tde_dirsize == 0 ||
				     ntf->tf_name[self->tde_dirsize] == '/') &&
				    tarfile_gethpos(ntf) >= pos) {
					if (tarfile_gethpos(ntf) == pos)
						return ntf; /* Perfect match; can't get any better than this! */
					if (!tf || tarfile_gethpos(tf) > tarfile_gethpos(ntf))
						tf = ntf;
				}
				if (i == 0)
					break;
				--i;
				tarsuper_serve_or_unlock(super);
			}
			for (i = hi; i < super->ts_filec; ++i) {
				struct tarfile *ntf;
				ntf = super->ts_filev[i];
				if (memcmp(ntf->tf_name, self->tde_dirname, self->tde_dirsize * sizeof(char)) != 0)
					break;
				if ((self->tde_dirsize == 0 ||
				     ntf->tf_name[self->tde_dirsize] == '/') &&
				    tarfile_gethpos(ntf) >= pos) {
					if (tarfile_gethpos(ntf) == pos)
						return ntf; /* Perfect match; can't get any better than this! */
					if (!tf || tarfile_gethpos(tf) > tarfile_gethpos(ntf))
						tf = ntf;
				}
				tarsuper_serve_or_unlock(super);
			}

			/* Because we know that all files leading up to `pos' are loaded,
			 * we can just  return the lowest  in-range file detected  above. */
			if (tf != NULL)
				return tf;
		}
	}

	/* Skip all directory entries which we don't care about. */
	do {
		tf = tarsuper_readdir_or_unlock(super);
		if (tf == TARSUPER_READDIR_EOF || tf == TARSUPER_READDIR_AGAIN)
			return tf;
	} while (tarfile_gethpos(tf) < pos);

	/* Check newly read directory entries. */
	for (;;) {
		/* Check if `tf' matches. */
		assert(tarfile_gethpos(tf) >= pos);
		if (memcmp(tf->tf_name, self->tde_dirname, self->tde_dirsize * sizeof(char)) == 0 &&
		    (self->tde_dirsize == 0 || tf->tf_name[self->tde_dirsize] == '/'))
			break; /* Got one! */

		/* Read the next entry. */
		tf = tarsuper_readdir_or_unlock(super);
		if (tf == TARSUPER_READDIR_EOF || tf == TARSUPER_READDIR_AGAIN)
			break;
		tarsuper_serve_or_unlock(super);
	}
	return tf;
}


/* Same as  `tardirenum_peekfile_raw()', but  includes special  handling
 * to only enumerate the first file from chains of sub-directories, such
 * that when enumerating "/usr", a file "/usr/bin/env" may be enumerated
 * only  if no other file with a lower position exists that is also pre-
 * fixed with "/usr/", or equals "/usr". */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2, 3, 4)) struct tarfile *FCALL
tardirenum_peekfile(struct tardirenum const *__restrict self,
                    pos_t *__restrict p_pos,
                    char const **__restrict p_basename,
                    uint8_t *__restrict p_baselen) {
	struct tarfile *result;
again:
	result = tardirenum_peekfile_raw(self, *p_pos);
	if (result != TARSUPER_READDIR_EOF && result != TARSUPER_READDIR_AGAIN) {
		size_t lo, hi;
		char const *basename;
		char const *baseend;
		struct tarsuper *super;
		struct tarfile *tf;
		uint8_t prefix_len;
		basename = result->tf_name + self->tde_dirsize;
		if (self->tde_dirsize != 0)
			++basename;
		baseend = strchrnul(basename, '/');
		assert(tarfile_gethpos(result) >= *p_pos);
		assert(self->tde_super->ts_nfile > *p_pos);
		assert(*baseend == '\0' || *baseend == '/');

		/* Write-back additional arguments */
		*p_basename = basename;
		*p_baselen  = (uint8_t)(size_t)(baseend - basename);

		/* Check if we should really enumerate this file. */
		if (*baseend == '\0' && !S_ISDIR(result->tf_mode))
			return result; /* Immediate sub-file (that isn't a directory) -> always enumerate! */

		/* `result' must be enumerated as some kind of directory.
		 * In  this case, check that other file with a lower disk
		 * position than `result->tf_pos' exists that also starts
		 * with the string `result->tf_name...baseend'.
		 *
		 * Because we're still holding a lock to the  superblock,
		 * we know that any such file _must_ be loaded right now,
		 * since `tardirenum_peekfile_raw()'  would  have  loaded
		 * all files leading up to `result', which is  guarantied
		 * to be located at `>= *p_pos' */
		super      = self->tde_super;
		prefix_len = (uint8_t)((size_t)(baseend - result->tf_name));
		lo         = 0;
		hi         = super->ts_filec;
		while (lo < hi) {
			size_t i;
			int cmp;
			i   = (lo + hi) / 2;
			tf  = super->ts_filev[i];
			cmp = memcmp(tf->tf_name, result->tf_name, prefix_len);
			if (cmp > 0) {
				hi = i;
			} else if (cmp < 0) {
				lo = i + 1;
			} else {
				lo = i;
				hi = i + 1;
				break;
			}
		}
		if (lo < hi) {
			size_t i;
			/* Search for the requested file below and above. */
			for (i = lo;;) {
				tf = super->ts_filev[i];
				if (memcmp(tf->tf_name, result->tf_name, prefix_len * sizeof(char)) != 0)
					break;
				tarsuper_serve_or_unlock(super);
				if ((tf->tf_name[prefix_len] == '\0' ||
				     tf->tf_name[prefix_len] == '/') &&
				    tarfile_gethpos(tf) < tarfile_gethpos(result)) {
					/* This file would have already enumerated this directory!
					 * To more quickly reduce the effective on-disk ranges, we
					 * skip all adjacent on-disk  files that would also  match
					 * the given prefix. */
skip_already_enumerated_directory:
					for (;;) {
						struct tarfile *next;
						next = TAILQ_NEXT(result, tf_bypos);
						if (!next)
							break;
						if (memcmp(next->tf_name, result->tf_name, prefix_len * sizeof(char)) != 0 ||
						    (next->tf_name[prefix_len] != '\0' && next->tf_name[prefix_len] != '/'))
							break; /* Part of different sub-tree */
						tarsuper_serve_or_unlock(super);
						result = next;
					}
					*p_pos = tarfile_getnexthdr(result);
					goto again;
				}
				if (i == 0)
					break;
				--i;
			}
			for (i = hi; i < super->ts_filec; ++i) {
				tf = super->ts_filev[i];
				if (memcmp(tf->tf_name, result->tf_name, prefix_len * sizeof(char)) != 0)
					break;
				tarsuper_serve_or_unlock(super);
				if ((tf->tf_name[prefix_len] == '\0' ||
				     tf->tf_name[prefix_len] == '/') &&
				    tarfile_gethpos(tf) < tarfile_gethpos(result))
					goto skip_already_enumerated_directory;
			}
		}
		/* No  other  file  exists  at  a  lower  position  that  has  the  same   prefix.
		 * In other words: we really _are_ supposed to enumerate this file as a directory! */
	}
	return result;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tardirenum_v_fini)(struct fdirenum *__restrict self) {
	/* No-op */
	(void)self;
}


/* Suppress incorrect warning about `tf_basename' / `tf_baselen' being uninitialized (no: they're not!) */
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif /* __GNUC__ */


PRIVATE BLOCKING NONNULL((1)) size_t KCALL
tardirenum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                     size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	REF struct tarfile *tf;
	struct tardirenum *me  = (struct tardirenum *)self;
	struct tarsuper *super = container_of(me->de_dir->fn_super, struct tarsuper, ts_super);
	pos_t oldpos, newpos;
	char const *tf_basename;
	uint8_t tf_baselen;
	ssize_t result;

again:
	/* Load position. */
	oldpos = (pos_t)atomic64_read(&me->tde_pos);
	newpos = oldpos;

	/* Query next file to enumerate. */
again_lock_super:
	tarsuper_read(super);
	tf = tardirenum_peekfile(me, &newpos, &tf_basename, &tf_baselen);

	/* Check for special return values. */
	if (tf == TARSUPER_READDIR_EOF)
		return 0; /* EOF */
	if (tf == TARSUPER_READDIR_AGAIN)
		goto again_lock_super; /* Try again */

	/* Got a file! we're supposed to enumerate! */
	incref(tf);
	tarsuper_endread(super);

	/* Enumerate the file. */
	{
		unsigned char typ;
		ino_t ino;
		typ = IFTODT(tf->tf_mode);
		ino = tarfile_getino(tf);
		if (tf_basename[tf_baselen] != '\0') {
			typ = DT_DIR; /* Implicit directory */
			ino = tarfile_getdirino(tf, (uint8_t)(size_t)((tf_basename + tf_baselen) - tf->tf_name));
		}
		FINALLY_DECREF_UNLIKELY(tf);
		newpos = tarfile_getnexthdr(tf);
		result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
		                             ino, typ, tf_baselen,
		                             tf_basename);
	}
	if (result < 0)
		return (size_t)~result; /* Don't yield! */

	/* Save the new disk position. */
	if (!atomic64_cmpxch(&me->tde_pos, (uint64_t)oldpos, (uint64_t)newpos))
		goto again; /* Race condition: someone else did another read in the meantime. */
	return (size_t)result;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */


PRIVATE BLOCKING NONNULL((1)) pos_t KCALL
tardirenum_v_seekdir(struct fdirenum *__restrict self,
                     off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...) {
	struct tardirenum *me  = (struct tardirenum *)self;
	uint64_t newpos;
	switch (whence) {

	case SEEK_SET:
		newpos = (uint64_t)(pos_t)offset;
		break;

	case SEEK_CUR: {
		/* This is the only case where the new file position depends on the
		 * old, also making it the only  case where we need CAS  semantics. */
		uint64_t oldpos;
		do {
			oldpos = atomic64_read(&me->tde_pos);
			newpos = oldpos + (int64_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!atomic64_cmpxch(&me->tde_pos, oldpos, newpos));
		goto done;
	}	break;

	case SEEK_END: {
		uint64_t filesize;
		/* Max size is the size of the disk. */
		filesize = atomic64_read(&me->tde_super->ts_super.fs_dev->mf_filesize);
		newpos   = filesize + (int64_t)offset;
		if unlikely(offset < 0 ? newpos > filesize
		                       : newpos < filesize)
			THROW(E_OVERFLOW);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
		break;
	}

	/* Write-back the new file position. */
	atomic64_write(&me->tde_pos, newpos);
done:
	return (pos_t)newpos;
}

PRIVATE struct fdirenum_ops const tardirenum_ops = {
	.deo_fini    = &tardirenum_v_fini,
	.deo_readdir = &tardirenum_v_readdir,
	.deo_seekdir = &tardirenum_v_seekdir,
};


PRIVATE BLOCKING NONNULL((1)) void KCALL
tardir_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	struct tardirenum *rt  = (struct tardirenum *)result;
	struct tardirnode *dir = (struct tardirnode *)rt->de_dir;
	/* Fill in fields. */
	rt->de_ops    = &tardirenum_ops;
	rt->tde_super = container_of(rt->de_dir->fn_super, struct tarsuper, ts_super);
	atomic64_init(&rt->tde_pos, 0);
	rt->tde_dirname = dir->tdn_fdat.tfd_name;
	rt->tde_dirsize = dir->tdn_fdat.tfd_nlen;
}





/************************************************************************/
/* Regular file operators.                                              */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tarreg_v_destroy)(struct mfile *__restrict self) {
	struct tarregnode *me;
	me = (struct tarregnode *)fnode_asreg(self);
	decref(me->trn_fdat.tfd_filp);
	fregnode_v_destroy(self);
}

PRIVATE BLOCKING NONNULL((1, 5)) void KCALL
tarreg_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                    physaddr_t buf, size_t num_bytes,
                    struct aio_multihandle *__restrict aio) {
	struct tarregnode *me  = (struct tarregnode *)mfile_asreg(self);
	struct tarsuper *super = container_of(me->fn_super, struct tarsuper, ts_super);
	fsuper_dev_rdsectors_async_chk(&super->ts_super,
	                               tarfile_getdpos(me->trn_fdat.tfd_filp) + addr,
	                               buf, num_bytes, aio);
}





/************************************************************************/
/* Symlink link operators.                                              */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tarlnk_v_destroy)(struct mfile *__restrict self) {
	struct tarlnknode *me;
	me = (struct tarlnknode *)fnode_aslnk(self);
	decref(me->tln_fdat.tfd_filp);
	flnknode_v_destroy(self);
}

PRIVATE BLOCKING ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char const *KCALL
tarlnk_v_linkstr(struct flnknode *__restrict self)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	char const *result;
	struct tarlnknode *me;
	me     = (struct tarlnknode *)fnode_aslnk(self);
	result = tarfile_getlnkstr(me->tln_fdat.tfd_filp);

	/* Use the symlink text length as filesize. */
	atomic64_write(&me->mf_filesize, strlen(result));
	return result;
}





/************************************************************************/
/* Superblock operators.                                                */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tarsuper_v_destroy)(struct mfile *__restrict self) {
	size_t i;
	struct tarsuper *me;
	me = container_of(fnode_assuper(self), struct tarsuper, ts_super);
	assert(!me->ts_fdat.tfd_filp);
	for (i = 0; i < me->ts_filec; ++i)
		decref_likely(me->ts_filev[i]);
	kfree(me->ts_filev);
	fsuper_v_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tarsuper_v_free)(struct fnode *__restrict self) {
	struct tarsuper *me;
	me = container_of(fnode_assuper(self), struct tarsuper, ts_super);
	kfree(me);
}

PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL tarsuper_v_cc)(struct mfile *__restrict self,
                             struct ccinfo *__restrict info) {
	size_t i;
	struct tarfile_slist deadfiles;
	struct tarsuper *me;
	SLIST_INIT(&deadfiles);
	me = container_of(mfile_assuper(self), struct tarsuper, ts_super);

	if (!tarsuper_trywrite(me)) {
		if (ccinfo_noblock(info))
			return; /* Not allowed to block :( */
		if (!tarsuper_write_nx(me))
			return; /* Cannot acquire lock... */
	}

	/* Remove all tar files that are not being used from the file list. */
	for (i = 0; i < me->ts_filec;) {
		struct tarfile *tf;
		tf = me->ts_filev[i];
		if (!ATOMIC_CMPXCH(tf->tf_refcnt, 1, 0)) {
			++i;
			continue;
		}

		/* Delete this file. */
		TAILQ_REMOVE(&me->ts_bypos, tf, tf_bypos);
		SLIST_INSERT(&deadfiles, tf, _tf_dead);
		if (me->ts_nfile > tarfile_gethpos(tf))
			me->ts_nfile = tarfile_gethpos(tf); /* Keep track of the first missing file. */
		--me->ts_filec;
		memmovedown(&me->ts_filev[i],
		            &me->ts_filev[i + 1],
		            me->ts_filec - i,
		            sizeof(me->ts_filev[i]));
	}

	/* Free unused memory from the file table. */
	if (!SLIST_EMPTY(&deadfiles)) {
		size_t old_usable;
		REF struct tarfile **newlist;
		old_usable = kmalloc_usable_size(me->ts_filev);
		/* Truncate the list */
		newlist = me->ts_filev;
		newlist = (REF struct tarfile **)krealloc_nx(newlist,
		                                             me->ts_filec * sizeof(REF struct tarfile *),
		                                             GFP_NORMAL);
		if likely(newlist) {
			size_t new_usable;
			new_usable   = kmalloc_usable_size(newlist);
			me->ts_filev = newlist;
			assert(old_usable >= new_usable);
			ccinfo_account(info, old_usable - new_usable);
		}
	}
	tarsuper_endwrite(me);

	/* Destroy files that we removed from the table. */
	while (!SLIST_EMPTY(&deadfiles)) {
		struct tarfile *tf;
		tf = SLIST_FIRST(&deadfiles);
		SLIST_REMOVE_HEAD(&deadfiles, _tf_dead);
		ccinfo_account(info, kmalloc_usable_size(tf));
		tarfile_destroy(tf);
	}
}






/************************************************************************/
/* Operator tables.                                                     */
/************************************************************************/
INTERN_CONST struct fdirent_ops const tardirent_ops = {
	.fdo_destroy  = &tardirent_v_destroy,
	.fdo_opennode = &tardirent_v_opennode,
};

PRIVATE struct mfile_stream_ops const tardirnode_v_stream_ops = {
	.mso_open      = &fdirnode_v_open,
	.mso_stat      = &fdirnode_v_stat,
	.mso_ioctl     = &fdirnode_v_ioctl,
	.mso_printlink = &tarnode_v_printlink,
};

INTERN_CONST struct fdirnode_ops const tardirnode_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &tardir_v_destroy,
			.mo_changed = &fdirnode_v_changed,
			.mo_stream  = &tardirnode_v_stream_ops,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.dno_lookup = &tardir_v_lookup,
	.dno_enumsz = sizeof(struct tardirenum),
	.dno_enum   = &tardir_v_enum,
};

PRIVATE struct mfile_stream_ops const tarregnode_v_stream_ops = {
	.mso_printlink = &tarnode_v_printlink,
};

INTERN_CONST struct fregnode_ops const tarregnode_ops = {
	.rno_node = {
		.no_file = {
			.mo_destroy    = &tarreg_v_destroy,
			.mo_loadblocks = &tarreg_v_loadblocks,
			.mo_changed    = &fregnode_v_changed,
			.mo_stream     = &tarregnode_v_stream_ops,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
};

PRIVATE struct mfile_stream_ops const tarlnknode_v_stream_ops = {
	.mso_stat      = &flnknode_v_stat_readlink_size,
	.mso_printlink = &tarnode_v_printlink,
};

INTERN_CONST struct flnknode_ops const tarlnknode_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &tarlnk_v_destroy,
			.mo_changed = &flnknode_v_changed,
			.mo_stream  = &tarlnknode_v_stream_ops,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.lno_readlink = &flnknode_v_readlink_default,
	.lno_linkstr  = &tarlnk_v_linkstr,
};

#define tardevnode_v_stream_ops tarregnode_v_stream_ops
INTERN_CONST struct fdevnode_ops const tardevnode_ops = {
	.dvno_node = {
		.no_file = {
			.mo_destroy = &tarreg_v_destroy,
			.mo_changed = &fregnode_v_changed,
			.mo_stream  = &tardevnode_v_stream_ops,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
};

/* Default stream operators for directories (using `fdirnode_v_open') */
PRIVATE struct mfile_stream_ops const tarsuper_v_stream_ops = {
	.mso_open      = &fsuper_v_open,
	.mso_stat      = &fsuper_v_stat,
	.mso_ioctl     = &fsuper_v_ioctl,
	.mso_printlink = &tarnode_v_printlink,
	.mso_cc        = &tarsuper_v_cc,
};

INTERN_CONST struct fsuper_ops const tarsuper_ops = {
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy = &tarsuper_v_destroy,
				.mo_changed = &fsuper_v_changed,
				.mo_stream  = &tarsuper_v_stream_ops,
			},
			.no_free   = &tarsuper_v_free,
			.no_wrattr = &fnode_v_wrattr_noop,
		},
		.dno_lookup = &tardir_v_lookup,
		.dno_enumsz = sizeof(struct tardirenum),
		.dno_enum   = &tardir_v_enum,
	},
};







/************************************************************************/
/* Tar-specific APIs                                                    */
/************************************************************************/

PRIVATE WUNUSED uint32_t FCALL
decode_oct(char const *str, size_t len)
		THROWS(E_FSERROR_CORRUPTED_FILE_SYSTEM) {
	uint32_t result = 0;
	while (len--) {
		char ch = *str++;
		if (ch >= '0' && ch <= '7') {
			result <<= 3;
			result |= ch - '0';
		} else if (isspace(ch) || ch == '\0') {
			break;
		} else {
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		}
	}
	return result;
}

/* Allocate a new tarfile descriptor. The caller must still fill in `return->tf_pos'
 * Returns `NULL' for unknown file types (that  will only be defined in the  future) */
INTERN WUNUSED NONNULL((1, 2)) struct tarfile *FCALL
tarfile_new(struct tarhdr const *__restrict self,
            uint32_t *__restrict p_filesize)
		THROWS(E_FSERROR_CORRUPTED_FILE_SYSTEM) {
	uint16_t mode;
	struct tarfile *result;
	bool is_ustar;
	char const *pstr_start, *pstr_end;
	char const *fstr_start, *fstr_end;
	size_t descsiz;
	uint32_t fsize;
	is_ustar   = memcmp(self->th_ustar, TMAGIC, TMAGLEN) == 0;
	pstr_start = NULL;
	pstr_end   = NULL;
	fstr_start = self->th_filename;
	fstr_end   = strnend(fstr_start, COMPILER_LENOF(self->th_filename));
	if (is_ustar) {
		pstr_start = self->th_filepfx;
		pstr_end   = strnend(pstr_start, COMPILER_LENOF(self->th_filepfx));
		while (pstr_start < pstr_end) {
			if (pstr_start[0] == '/') {
				pstr_start += 1;
			} else if ((pstr_start + 1) < pstr_end &&
			           pstr_start[0] == '.' &&
			           pstr_start[1] == '/') {
				pstr_start += 2;
			} else {
				break;
			}
		}
		if (pstr_start + 1 == pstr_end &&
		    pstr_start[0] == '.' &&
		    fstr_start[0] == '/') {
			++pstr_start;
			++fstr_start;
		}
	}
	while (fstr_start < fstr_end) {
		if (fstr_start[0] == '/') {
			fstr_start += 1;
		} else if ((fstr_start + 1) < fstr_end &&
		           fstr_start[0] == '.' &&
		           fstr_start[1] == '/') {
			fstr_start += 2;
		} else {
			break;
		}
	}

	/* Decode file mode. */
	mode = (uint16_t)decode_oct(self->th_mode, COMPILER_LENOF(self->th_mode));

#if 1
	/* From https://www.gnu.org/software/tar/manual/html_node/Standard.html:
	 * """
	 *     Modes which are not supported by the operating system
	 *     restoring  files  from the  archive will  be ignored.
	 * """ */
	mode &= 07777;
#else
	if (mode & ~07777)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
#endif

	/* Figure out the correct file size. */
	fsize       = (uint32_t)decode_oct(self->th_size, COMPILER_LENOF(self->th_size));
	*p_filesize = fsize;

	/* Figure out the proper file mode. */
	switch (self->th_type[0]) {

	case TCONTTYPE:
		if (!is_ustar)
			return NULL;
		ATTR_FALLTHROUGH
	case TREGTYPE:  /* Normal file */
	case TAREGTYPE: /* Regular file (alias) */
		if (!is_ustar && (fstr_start < fstr_end &&
		                  fstr_end[-1] == '/')) {
			--fstr_end;
			mode |= S_IFDIR;
		} else {
			mode |= S_IFREG;
		}
		break;

	case TLNKTYPE:
		mode |= 0;
		break;

	case TSYMTYPE:
		mode |= S_IFLNK;
		break;

	case TCHRTYPE:
		if (!is_ustar)
			return NULL;
		mode |= S_IFCHR;
		break;

	case TBLKTYPE:
		if (!is_ustar)
			return NULL;
		mode |= S_IFBLK;
		break;

	case TDIRTYPE:
		if (!is_ustar)
			return NULL;
		mode |= S_IFDIR;
		break;

	case TFIFOTYPE:
		if (!is_ustar)
			return NULL;
		mode |= S_IFIFO;
		break;

	default:
		return NULL;
	}

	/* Verify the filename. */
	if (fstr_start < fstr_end) {
		while (fstr_end[-1] == '/') {
			if (!S_ISDIR(mode))
				THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
			--fstr_end;
			if (fstr_start >= fstr_end)
				goto handle_empty_fstr;
		}
	} else {
handle_empty_fstr:
		if (pstr_start < pstr_end) {
			while (pstr_end[-1] == '/') {
				if (!S_ISDIR(mode))
					THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
				--pstr_end;
				if (pstr_start >= pstr_end)
					goto handle_empty_name;
			}
		} else {
handle_empty_name:
			/* Special case: we allow an empty name for the root
			 *               directory (though  we  ignore  it).
			 * NOTE: This also handles  tar files with  trailing
			 *       NUL bytes present after all preceding files
			 *       have been enumerated. */
			return NULL;
		}
	}

	/* Figure out extended tarfile fields. */
	descsiz = offsetof(struct tarfile, tf_name) +
	          ((fstr_end - fstr_start) +
	           (pstr_end - pstr_start) + 1);
	switch (mode & S_IFMT) {

	case 0: {
		char const *ref_start;
		char const *ref_end;
		size_t offsetof_lnkname;
		ref_start = self->th_lnkname;
		ref_end   = strnend(ref_start, COMPILER_LENOF(self->th_lnkname));
		while (ref_start < ref_end) {
			if (ref_start[0] == '/') {
				++ref_start;
			} else if ((ref_start + 1) < ref_end &&
			           ref_start[0] == '.' &&
			           ref_start[1] == '/') {
				ref_start += 2;
			} else {
				break;
			}
		}
		if unlikely(ref_start >= ref_end)
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

		/* Allocate file descriptor. */
		offsetof_lnkname = descsiz;
		descsiz += ((size_t)(ref_end - ref_start) + 1) * sizeof(char);
		result = (struct tarfile *)kmalloc(descsiz, GFP_NORMAL);

		/* Copy linked file name. */
		*(char *)mempcpy((byte_t *)result + offsetof_lnkname, ref_start,
		                 (size_t)(ref_end - ref_start), sizeof(char)) = '\0';
		goto fill_common_fields;
	}	break;

	case S_IFBLK:
	case S_IFCHR: {
		uint32_t major, minor;
		size_t offsetof_devno;
		major = (uint32_t)decode_oct(self->th_devmajor, COMPILER_LENOF(self->th_devmajor));
		minor = (uint32_t)decode_oct(self->th_devminor, COMPILER_LENOF(self->th_devminor));
		if unlikely(major > (uint32_t)((1 << MAJORBITS) - 1) ||
		            minor > (uint32_t)((1 << MINORBITS) - 1))
			return NULL; /* Unsupported device number :( */
		descsiz        = CEIL_ALIGN(descsiz, 4);
		offsetof_devno = descsiz;
		descsiz += 4;
		result = (struct tarfile *)kmalloc(descsiz, GFP_NORMAL);

		/* Fill in device number. */
		*(uint32_t *)((byte_t *)result + offsetof_devno) = (uint32_t)MKDEV(major, minor);
		goto fill_common_fields;
	}	break;

	case S_IFLNK: {
		char const *lnk_start;
		char const *lnk_end;
		size_t offsetof_lnkname;
		lnk_start = self->th_lnkname;
		lnk_end   = strnend(lnk_start, COMPILER_LENOF(self->th_lnkname));

		/* Allocate file descriptor. */
		offsetof_lnkname = descsiz;
		descsiz += ((size_t)(lnk_end - lnk_start) + 1) * sizeof(char);
		result = (struct tarfile *)kmalloc(descsiz, GFP_NORMAL);

		/* Copy symbolic link text. */
		*(char *)mempcpy((byte_t *)result + offsetof_lnkname, lnk_start,
		                 (size_t)(lnk_end - lnk_start), sizeof(char)) = '\0';
		goto fill_common_fields;
	}	break;

	default:
		break;
	}

	/* Allocate file descriptor. */
	result = (struct tarfile *)kmalloc(descsiz, GFP_NORMAL);

	/* Decode other fields. */
fill_common_fields:
	TRY {
		result->tf_mtim = (int32_t)decode_oct(self->th_mtime, COMPILER_LENOF(self->th_mtime));
		result->tf_uid  = (uint16_t)decode_oct(self->th_uid, COMPILER_LENOF(self->th_uid));
		result->tf_gid  = (uint16_t)decode_oct(self->th_gid, COMPILER_LENOF(self->th_gid));
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	result->tf_refcnt = 1;
	result->tf_mode   = mode;
	result->tf_size   = fsize;

	/* Construct the filename. */
	*(char *)mempcpy(mempcpy(result->tf_name, pstr_start,
	                         (size_t)(pstr_end - pstr_start),
	                         sizeof(char)),
	                 fstr_start,
	                 (size_t)(fstr_end - fstr_start),
	                 sizeof(char)) = '\0';
	return result;
}



/* Insert a given file `tf' into `self' */
INTERN NONNULL((1, 2)) void FCALL
tarsuper_insertfile(struct tarsuper *__restrict self,
                    REF struct tarfile *__restrict tf)
		THROWS(E_BADALLOC) {
	size_t avail, lo, hi;

	/* Make sure that the file vector has sufficient space */
	avail = kmalloc_usable_size(self->ts_filev);
	avail /= sizeof(REF struct tarfile *);
	if (avail < self->ts_filec + 1) {
		/* Must allocate more file space. */
		size_t newalloc;
		REF struct tarfile **newlist;
		newalloc = avail * 2;
		if unlikely(!newalloc)
			newalloc = 32;
		newlist = (REF struct tarfile **)krealloc_nx(self->ts_filev,
		                                             newalloc * sizeof(REF struct tarfile *),
		                                             GFP_NORMAL);
		if (!newlist) {
			newalloc = self->ts_filec + 1;
			newlist = (REF struct tarfile **)krealloc(self->ts_filev,
			                                          newalloc * sizeof(REF struct tarfile *),
			                                          GFP_NORMAL);
		}
		self->ts_filev = newlist;
	}

	/* NOTHROW FROM HERE ON! */

	/* Insert into the by-position list. */
	if unlikely(TAILQ_EMPTY(&self->ts_bypos)) {
		TAILQ_INSERT_HEAD(&self->ts_bypos, tf, tf_bypos);
	} else if likely(tf->tf_pos >= TAILQ_LAST(&self->ts_bypos)->tf_pos) {
		/* Most likely case: insert at the back. */
		TAILQ_INSERT_TAIL(&self->ts_bypos, tf, tf_bypos);
	} else if unlikely(tf->tf_pos <= TAILQ_FIRST(&self->ts_bypos)->tf_pos) {
		/* Special case: insert in the front. */
		TAILQ_INSERT_HEAD(&self->ts_bypos, tf, tf_bypos);
	} else {
		struct tarfile *pred;
		pred = TAILQ_LAST(&self->ts_bypos);
		/* Find the file after which to insert `tf' */
		do {
			pred = TAILQ_PREV(pred, tf_bypos);
		} while (tf->tf_pos < pred->tf_pos);
		TAILQ_INSERT_AFTER(&self->ts_bypos, pred, tf, tf_bypos);
	}

	/* Insert into the by-name list. */
	lo = 0;
	hi = self->ts_filec;
	while (lo < hi) {
		size_t i;
		struct tarfile *ot;
		int cmp;
		i   = (lo + hi) / 2;
		ot  = self->ts_filev[i];
		cmp = strcmp(ot->tf_name, tf->tf_name);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			break;
		}
	}

	/* Insert at `lo' */
	memmoveup(&self->ts_filev[lo + 1],
	          &self->ts_filev[lo],
	          self->ts_filec - lo,
	          sizeof(REF struct tarfile *));
	self->ts_filev[lo] = tf; /* Inherit reference. */
	++self->ts_filec;
}


/* Read a new tarfile descriptor  at `self->ts_nfile', or endread  `self'.
 * The new file is automatically inserted into `self->ts_filev', for which
 * this function will temporarily upgrade  to a write-lock. When doing  so
 * would  block, the caller's read-lock is released, and a blocking write-
 * lock is acquired which is  then used to insert  the new file, prior  to
 * the  function returning `TARSUPER_READDIR_AGAIN'  (to indicate the loss
 * of the read-lock).
 *
 * When the tarfile descriptor at `self->ts_nfile' had already been loaded,
 * that one will just be re-returned.
 *
 * Locking logic:
 * @return: * :                     No lock was ever released
 * @return: TARSUPER_READDIR_EOF:   Read-lock released
 * @return: TARSUPER_READDIR_AGAIN: Read-lock released */
INTERN BLOCKING ATTR_NOINLINE WUNUSED NONNULL((1)) struct tarfile *FCALL
tarsuper_readdir_or_unlock(struct tarsuper *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	bool was_lock_lost = false;
	pos_t pos;
	struct tarhdr *hdr;
	struct tarfile *tf;
	uint32_t hdrsize;

	/* Allocate buffer for the tar header. */
	hdr = (struct tarhdr *)aligned_alloca(TBLOCKSIZE, TBLOCKSIZE);

	/* Check for special case: the next file may already been loaded. */
again:
	pos = self->ts_nfile;
	if (!TAILQ_EMPTY(&self->ts_bypos)) {
		tf = TAILQ_LAST(&self->ts_bypos);
		if (tarfile_gethpos(tf) >= pos) {
			while (tarfile_gethpos(tf) > pos) {
				tf = TAILQ_PREV(tf, tf_bypos);
				if (!tf)
					break;
			}
			if (tf && tarfile_gethpos(tf) == pos) {
				/* Update position for next file. */
				if (!was_lock_lost && !tarsuper_upgrade(self)) {
					was_lock_lost = true;
					goto again;
				}
				self->ts_nfile = tarfile_getnexthdr(tf);
				goto return_tf_after_wrlock;
			}
		}
	}

	TRY {
		pos_t endpos;
again_rdhdr:
		/* Check for end-of-file. */
		if (OVERFLOW_UADD(pos, TBLOCKSIZE, &endpos) ||
		    endpos > atomic64_read(&self->ts_super.fs_dev->mf_filesize)) {
			tarsuper_endread(self);
			return TARSUPER_READDIR_EOF;
		}

		/* Read the next file header.
		 * We don't have to use the *_chk variant here since we already check for bounds! */
		fsuper_dev_rdsectors(&self->ts_super, pos, pagedir_translate(hdr), TBLOCKSIZE);

		/* Decode into the associated file. */
		tf      = tarfile_new(hdr, &hdrsize);
		hdrsize = CEIL_ALIGN(hdrsize, TBLOCKSIZE);
		if (!tf) {
			/* Unknown file type (must skip) */
			pos += TBLOCKSIZE;
			pos += hdrsize;
			goto again_rdhdr;
		}
	} EXCEPT {
		tarsuper_endread(self);
		RETHROW();
	}

	/* Upgrade to a write-lock. */
	if (!was_lock_lost) {
		bool upgrade_ok;
		TRY {
			upgrade_ok = tarsuper_upgrade(self);
		} EXCEPT {
			destroy(tf);
			RETHROW();
		}
		if (!upgrade_ok) {
			was_lock_lost = true;
			destroy(tf);
			goto again;
		}
	}

	/* Fill in missing fields of `tf' */
	pos += TBLOCKSIZE;
	tf->tf_pos = pos; /* data-position */

	/* Insert `tf' into relevant data-structures.
	 * NOTE: This also inherits the reference to `tf' */
	TRY {
		tarsuper_insertfile(self, tf);
	} EXCEPT {
		tarsuper_endwrite(self);
		destroy(tf);
		RETHROW();
	}

	/* Advance to the next file. */
	pos += hdrsize;
	self->ts_nfile = pos;

	/* Downgrade back to a read-lock and return `tf' */
return_tf_after_wrlock:
	tarsuper_downgrade(self);
	if (was_lock_lost) {
		/* If the lock was lost, must release all locks and return AGAIN */
		tarsuper_endread(self);
		tf = TARSUPER_READDIR_AGAIN;
	}
	return tf;
}








PRIVATE WUNUSED NONNULL((1, 2)) struct fsuper *KCALL
tarfs_open(struct ffilesys *__restrict UNUSED(filesys),
           struct mfile *dev, UNCHECKED USER char *UNUSED(args)) {
	struct tarsuper *result;
	struct tarhdr *hdr;
	struct tarfile *firstfile;
	uint32_t first_filesize;
	(mfile_getblockshift(dev) <= TBLOCKSHIFT)
	? (hdr = (struct tarhdr *)aligned_alloca(TBLOCKSIZE, TBLOCKSIZE),
	   mfile_rdblocks(dev, 0, pagedir_translate(hdr), TBLOCKSIZE))
	: (hdr = (struct tarhdr *)alloca(sizeof(struct tarhdr)),
	   mfile_readall(dev, hdr, sizeof(struct tarhdr), 0));

	/* To determine if this really is a tar file, we try to load the first file. */
	TRY {
		firstfile = tarfile_new(hdr, &first_filesize);
	} EXCEPT {
		if (was_thrown(E_FSERROR_CORRUPTED_FILE_SYSTEM))
			return NULL; /* Nope: not a tar filesystem! */
		RETHROW();
	}

	/* Seeing how we were able to decode the first file, we'll assume that this
	 * really is a tar filesystem, such that any decode errors from this  point
	 * on are treated as corrupted-filesystem errors, rather than  not-a-tar-fs
	 * errors. */
	TRY {
		result = (struct tarsuper *)kmalloc(sizeof(struct tarsuper), GFP_NORMAL);
		TRY {
			result->ts_filev = (REF struct tarfile **)kmalloc_nx(32 * sizeof(REF struct tarfile *), GFP_NORMAL);
			if unlikely(!result->ts_filev)
				result->ts_filev = (REF struct tarfile **)kmalloc(1 * sizeof(REF struct tarfile *), GFP_NORMAL);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}
	} EXCEPT {
		if (firstfile)
			tarfile_destroy(firstfile);
		RETHROW();
	}

	/* Initialize tarfs-specific fields. */
	shared_rwlock_init(&result->ts_lock);
	result->ts_filec = 0;
	result->ts_nfile = (pos_t)(TBLOCKSIZE + CEIL_ALIGN(first_filesize, TBLOCKSIZE));
	TAILQ_INIT(&result->ts_bypos);
	result->ts_fdat.tfd_filp = NULL;
	result->ts_fdat.tfd_name = NULL;
	result->ts_fdat.tfd_nlen = 0;

	/* Remember the first file. */
	if (firstfile != NULL) {
		firstfile->tf_pos   = (pos_t)TBLOCKSIZE; /* data-position */
		result->ts_filev[0] = firstfile;
		result->ts_filec    = 1;
		TAILQ_INSERT_HEAD(&result->ts_bypos, firstfile, tf_bypos);
	}

	/* Initialize the superblock. */
	result->ts_super.fs_root.mf_ops               = &tarsuper_ops.so_fdir.dno_node.no_file;
	result->ts_super.fs_root.mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->ts_super.fs_root.mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	result->ts_super.fs_root.mf_blockshift        = TBLOCKSHIFT;
	result->ts_super.fs_root.mf_iobashift         = dev->mf_iobashift;
	atomic64_init(&result->ts_super.fs_root.mf_filesize, (uint64_t)-1);
	result->ts_super.fs_root.mf_atime = realtime();
	result->ts_super.fs_root.mf_mtime = result->ts_super.fs_root.mf_atime;
	result->ts_super.fs_root.mf_ctime = result->ts_super.fs_root.mf_atime;
	result->ts_super.fs_root.mf_btime = result->ts_super.fs_root.mf_atime;

	/* Set-up appropriate flags. */
	result->ts_super.fs_root.mf_flags = MFILE_F_READONLY | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE |
	                                    MFILE_F_NOATIME | MFILE_F_NOMTIME | MFILE_FN_NODIRATIME | MFILE_FN_ATTRREADONLY;
	result->ts_super.fs_root.fn_mode  = S_IFDIR | 0555;
	result->ts_super.fs_root.fn_ino   = 0;
	result->ts_super.fs_root.fn_nlink = 1;
	result->ts_super.fs_root.fn_uid   = 0;
	result->ts_super.fs_root.fn_gid   = 0;

	/* Filesystem features. */
	result->ts_super.fs_feat.sf_filesize_max       = (pos_t)UINT32_MAX;
	result->ts_super.fs_feat.sf_uid_max            = (uid_t)UINT16_MAX;
	result->ts_super.fs_feat.sf_gid_max            = (gid_t)UINT16_MAX;
	result->ts_super.fs_feat.sf_symlink_max        = (pos_t)100;
	result->ts_super.fs_feat.sf_link_max           = (nlink_t)-1;
	result->ts_super.fs_feat.sf_magic              = ENCODE_INT32('t', 'a', 'r', 0); /* <linux/magic.h> doesn't have a constant for this, so we improvise... */
	result->ts_super.fs_feat.sf_rec_incr_xfer_size = TBLOCKSIZE;
	result->ts_super.fs_feat.sf_rec_max_xfer_size  = TBLOCKSIZE;
	result->ts_super.fs_feat.sf_rec_min_xfer_size  = TBLOCKSIZE;
	result->ts_super.fs_feat.sf_rec_xfer_align     = TBLOCKSIZE;
	result->ts_super.fs_feat.sf_name_max           = 255;
	result->ts_super.fs_feat.sf_filesizebits       = 32;
	return &result->ts_super;
}


PRIVATE struct ffilesys tarfs_filesys = {
	.ffs_drv = &drv_self,
	{ .ffs_open = &tarfs_open },
	.ffs_flags = FFILESYS_F_NORMAL,
	/* .ffs_name = */ "tar",
};


#ifdef CONFIG_BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_tar_driver(void)
#else /* CONFIG_BUILDING_KERNEL_CORE */
PRIVATE DRIVER_INIT ATTR_FREETEXT void KCALL init(void)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
{
	ffilesys_register(&tarfs_filesys);
}

#ifndef CONFIG_BUILDING_KERNEL_CORE
PRIVATE DRIVER_FINI void KCALL fini(void) {
	ffilesys_unregister(&tarfs_filesys);
}
#endif /* !CONFIG_BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_MODTARFS_TAR_C */
