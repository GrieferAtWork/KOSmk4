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
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/wordbits.h>

#include <kos/dev.h>
#include <kos/except.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

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
	result = fsuper_nodes_locate(&super->ts_super, (ino_t)tfile->tf_pos);
	if (result) {
		if likely(tryincref(result)) {
			fsuper_nodes_endread(&super->ts_super);
			return result;
		}
		if (!fsuper_nodes_upgrade(&super->ts_super))
			result = fsuper_nodes_locate(&super->ts_super, (ino_t)tfile->tf_pos);

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
		node->mf_ops   = &tardevnode_ops.dno_node.no_file;
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
	assert(me->td_ent.fd_namelen >= rfdat->tfd_nlen);

	/* Fill in mem-file fields. */
	__mfile_init_wrlockpc(result)
	_mfile_init_common(result);
	_mfile_init_blockshift(result, TARFS_BLOCKSHIFT, super->ts_super.fs_root.mf_iobashift);
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

	/* Fill in file-node fields. */
	result->fn_nlink = 1;
	result->fn_mode  = tfile->tf_mode;
	result->fn_uid   = (uid_t)tfile->tf_uid;
	result->fn_gid   = (gid_t)tfile->tf_gid;
	result->fn_ino   = (ino_t)(pos_t)tfile->tf_pos;
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
		assertf(tfile->tf_name[parent_dir_size] == '/',
		        "tfile->tf_name = %q", tfile->tf_name);
		++parent_dir_size; /* Skip '/' */
		local_filename = tfile->tf_name + parent_dir_size;
		assertf(memcmp(local_filename, me->td_ent.fd_name, me->td_ent.fd_namelen) == 0,
		        "local_filename     = %q\n"
		        "me->td_ent.fd_name = %q\n",
		        local_filename, me->td_ent.fd_name);

		/* If what we have isn't the actual directory file, then use stub defaults instead. */
		if (local_filename[me->td_ent.fd_namelen] != '\0') {
			/* Implicit directory... */
			result->fn_mode = S_IFDIR | 0555;
			result->fn_uid  = 0;
			result->fn_gid  = 0;
			mfile_tslock_acquire(&super->ts_super.fs_root);
			result->mf_atime = super->ts_super.fs_root.mf_ctime;
			result->mf_mtime = super->ts_super.fs_root.mf_ctime;
			result->mf_ctime = super->ts_super.fs_root.mf_ctime;
			mfile_tslock_release(&super->ts_super.fs_root);
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
	} else if (S_ISLNK(result->fn_mode)) {
		/* Use the symlink text length as filesize. */
		atomic64_init(&result->mf_filesize, strlen(tarfile_getlnkstr(tfile)));
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
/* Directory operators.                                                 */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tardir_v_destroy)(struct mfile *__restrict self) {
	struct tardirnode *me;
	me = (struct tardirnode *)fnode_asdir(self);
	decref(me->tdn_fdat.tfd_filp);
	fdirnode_v_destroy(self);
}


PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
tardir_v_lookup(struct fdirnode *__restrict self,
                struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	char filename[256];
	struct tardirnode *me = (struct tardirnode *)self;
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

	/* TODO: Acquire a read-lock to `me->ts_lock' */
	/* TODO: Search  through `me->ts_filev' for a files that starts with the requested
	 *       prefix. If one is found that matches `filename' use that one.  Otherwise,
	 *       if one is found that starts with `filename + "/"', use that one, and have
	 *       the file reference a directory. */
	/* TODO: When AT_DOSPATH is given, load min/max bounds of `prefix_str...+=prefix_len',
	 *       as  in: the first and last already-loaded file apart of the parent dir. Then,
	 *       walk  all those files  and strcasecmp() their  `basename(3)' to the requested
	 *       filename. */
	/* TODO: Keep on scanning for  the requested file via  `tarsuper_readdir_or_endread()'.
	 *       When that function returns `TARSUPER_READDIR_EOF', give up. When that function
	 *       returns `TARSUPER_READDIR_AGAIN', start over by re-acquiring the read-lock and
	 *       scanning for the requested file. */

	(void)me;
	(void)info;
	(void)filename;
	(void)filename_len;

	THROW(E_NOT_IMPLEMENTED_TODO);
}

struct tardirenum: fdirenum {
	/* TODO: Enumerate files based  on `tf_pos'  (iow: disk  position)
	 *       For this purpose, we seekdir() simply alters the absolute
	 *       on-disk  position, and readdir() yields the first tarfile
	 *       that  has a name  that starts with the  prefix of the dir
	 *       being enumerated, doesn't contain any additional '/'s.
	 * - Use  `ts_nfile' to determine if all files until the min disk
	 *   address of the next file to-be read have already been loaded
	 * - Use `ts_bypos' to enumerate files based on disk-order
	 * - Use `ts_filev' to narrow down files within the current dir.
	 */
};

PRIVATE BLOCKING NONNULL((1)) void KCALL
tardir_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	struct tardirenum *rt = (struct tardirenum *)result;
	/* TODO */
	(void)rt;
	THROW(E_NOT_IMPLEMENTED_TODO);
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
	fsuper_dev_rdsectors_async(&super->ts_super,
	                           me->trn_fdat.tfd_filp->tf_pos + addr,
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

PRIVATE BLOCKING ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char const *KCALL
tarlnk_v_linkstr(struct flnknode *__restrict self)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct tarlnknode *me;
	me = (struct tarlnknode *)fnode_aslnk(self);
	return tarfile_getlnkstr(me->tln_fdat.tfd_filp);
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





/************************************************************************/
/* Operator tables.                                                     */
/************************************************************************/
INTERN_CONST struct fdirent_ops const tardirent_ops = {
	.fdo_destroy  = &tardirent_v_destroy,
	.fdo_opennode = &tardirent_v_opennode,
};

INTERN_CONST struct fdirnode_ops const tardirnode_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &tardir_v_destroy,
			.mo_changed = &fdirnode_v_changed,
			.mo_stream  = &fdirnode_v_stream_ops,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.dno_lookup = &tardir_v_lookup,
	.dno_enumsz = sizeof(struct tardirenum),
	.dno_enum   = &tardir_v_enum,
};

INTERN_CONST struct fregnode_ops const tarregnode_ops = {
	.rno_node = {
		.no_file = {
			.mo_destroy    = &tarreg_v_destroy,
			.mo_loadblocks = &tarreg_v_loadblocks,
			.mo_changed    = &fregnode_v_changed,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
};

INTERN_CONST struct flnknode_ops const tarlnknode_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &tarlnk_v_destroy,
			.mo_changed = &flnknode_v_changed,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.lno_linkstr = &tarlnk_v_linkstr,
};

INTERN_CONST struct fdevnode_ops const tardevnode_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &tarreg_v_destroy,
			.mo_changed = &fregnode_v_changed,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
};

INTERN_CONST struct fsuper_ops const tarsuper_ops = {
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy = &tarsuper_v_destroy,
				.mo_changed = &fsuper_v_changed,
				.mo_stream  = &fsuper_v_stream_ops,
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
INTERN WUNUSED struct tarfile *FCALL
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
	is_ustar   = memcmp(self->th_ustar, "ustar", 6) == 0;
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
	mode = (uint16_t)decode_oct(self->th_mode, COMPILER_LENOF(self->th_mode));
	if (mode & ~07777)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	/* Figure out the correct file size. */
	fsize       = (uint32_t)decode_oct(self->th_size, COMPILER_LENOF(self->th_size));
	*p_filesize = fsize;

	/* Figure out the proper file mode. */
	switch (self->th_type) {

	case TARHDR_TYPE_REG3:
		if (!is_ustar)
			return NULL;
		ATTR_FALLTHROUGH
	case TARHDR_TYPE_REG:  /* Normal file */
	case TARHDR_TYPE_REG2: /* Regular file (alias) */
		if (!is_ustar && (fstr_start < fstr_end &&
		                  fstr_end[-1] == '/')) {
			--fstr_end;
			mode |= S_IFDIR;
		} else {
			mode |= S_IFREG;
		}
		break;

	case TARHDR_TYPE_HRD:
		mode |= 0;
		break;

	case TARHDR_TYPE_SYM:
		mode |= S_IFLNK;
		break;

	case TARHDR_TYPE_CHR:
		if (!is_ustar)
			return NULL;
		mode |= S_IFCHR;
		break;

	case TARHDR_TYPE_BLK:
		if (!is_ustar)
			return NULL;
		mode |= S_IFBLK;
		break;

	case TARHDR_TYPE_DIR:
		if (!is_ustar)
			return NULL;
		mode |= S_IFDIR;
		break;

	case TARHDR_TYPE_FIFO:
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
			/* Special case: we allow an empty name for the root directory (though we ignore it). */
			if (!S_ISDIR(mode))
				return NULL;

			/* Empty filename (not allowed) */
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
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



/* Read a new tarfile descriptor  at `self->ts_nfile', or endread  `self'.
 * The new file is automatically inserted into `self->ts_filev', for which
 * this function will temporarily upgrade  to a write-lock. When doing  so
 * would  block, the caller's read-lock is released, and a blocking write-
 * lock is acquired which is  then used to insert  the new file, prior  to
 * the  function returning `TARSUPER_READDIR_AGAIN'  (to indicate the loss
 * of the read-lock).
 *
 * Locking logic:
 * @return: * :                     No lock was ever released
 * @return: TARSUPER_READDIR_EOF:   Read-lock released
 * @return: TARSUPER_READDIR_AGAIN: Read-lock released */
INTERN BLOCKING WUNUSED struct tarfile *FCALL
tarsuper_readdir_or_endread(struct tarsuper *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	/* TODO */
	shared_rwlock_endread(&self->ts_lock); /* TODO: Use a designated macro for working with the lock! */
	THROW(E_NOT_IMPLEMENTED_TODO);
}








PRIVATE WUNUSED NONNULL((1, 2)) struct fsuper *KCALL
tarfs_open(struct ffilesys *__restrict UNUSED(filesys),
           struct mfile *dev, UNCHECKED USER char *UNUSED(args)) {
	struct tarsuper *result;
	struct tarhdr *hdr;
	struct tarfile *firstfile;
	uint32_t first_filesize;
	if (mfile_getblocksize(dev) <= TARFS_BLOCKSIZE) {
		hdr = (struct tarhdr *)aligned_alloca(TARFS_BLOCKSIZE, TARFS_BLOCKSIZE);
		mfile_rdblocks(dev, 0, pagedir_translate(hdr), TARFS_BLOCKSIZE);
	} else {
		hdr = (struct tarhdr *)alloca(sizeof(struct tarhdr));
		mfile_readall(dev, hdr, sizeof(struct tarhdr), 0);
	}

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
	if (firstfile)
		firstfile->tf_pos = (pos_t)TARFS_BLOCKSIZE;
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
	result->ts_filev[0]      = firstfile;
	result->ts_filec         = firstfile ? 1 : 0;
	result->ts_nfile         = (pos_t)(TARFS_BLOCKSIZE + CEIL_ALIGN(first_filesize, TARFS_BLOCKSIZE));
	result->ts_fdat.tfd_filp = NULL;
	result->ts_fdat.tfd_name = NULL;
	result->ts_fdat.tfd_nlen = 0;

	/* Initialize the superblock. */
	result->ts_super.fs_root.mf_ops               = &tarsuper_ops.so_fdir.dno_node.no_file;
	result->ts_super.fs_root.mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->ts_super.fs_root.mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	result->ts_super.fs_root.mf_blockshift        = TARFS_BLOCKSHIFT;
	result->ts_super.fs_root.mf_iobashift         = dev->mf_iobashift;
	atomic64_init(&result->ts_super.fs_root.mf_filesize, (uint64_t)-1);
	result->ts_super.fs_root.mf_atime = realtime();
	result->ts_super.fs_root.mf_mtime = result->ts_super.fs_root.mf_atime;
	result->ts_super.fs_root.mf_ctime = result->ts_super.fs_root.mf_atime;

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
	result->ts_super.fs_feat.sf_rec_incr_xfer_size = TARFS_BLOCKSIZE;
	result->ts_super.fs_feat.sf_rec_max_xfer_size  = TARFS_BLOCKSIZE;
	result->ts_super.fs_feat.sf_rec_min_xfer_size  = TARFS_BLOCKSIZE;
	result->ts_super.fs_feat.sf_rec_xfer_align     = TARFS_BLOCKSIZE;
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
INTERN ATTR_FREETEXT void KCALL kernel_initialize_tarfs_driver(void)
#else  /* CONFIG_BUILDING_KERNEL_CORE */
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
