/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_RAMFS_C
#define GUARD_KERNEL_CORE_FILESYS_RAMFS_C 1
#define __WANT_MFILE__mf_ramdirplop
#define __WANT_MFILE__mf_ramdirlop
#define __WANT_MFILE__mf_deadrament
#define __WANT_RAMFS_DIRENT__rde_dead
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/clnknode.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/user.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <linux/magic.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE_OMIT_LOCATE
#define RBTREE_OMIT_REMOVE
#define RBTREE(name)               ramfs_direnttree_##name
#define RBTREE_T                   struct ramfs_dirent
#define RBTREE_Tkey                USER CHECKED char const *
#define RBTREE_GETNODE(self)       (self)->rde_treenode
#define RBTREE_GETKEY(self)        (self)->rde_ent.fd_name
#define RBTREE_REDFIELD            rde_isred
#define RBTREE_CC                  FCALL
#define RBTREE_NOTHROW             NOTHROW
#define RBTREE_NOTHROW_U           /* nothing */
#define RBTREE_DECL                FUNDEF
#define RBTREE_IMPL                PUBLIC
#define RBTREE_KEY_EQ(a, b)        (strcmp(a, b) == 0)
#define RBTREE_KEY_NE(a, b)        (strcmp(a, b) != 0)
#define RBTREE_KEY_LO(a, b)        (strcmp(a, b) < 0)
#define RBTREE_KEY_LE(a, b)        (strcmp(a, b) <= 0)
#define RBTREE_KEY_GR(a, b)        (strcmp(a, b) > 0)
#define RBTREE_KEY_GE(a, b)        (strcmp(a, b) >= 0)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

INTDEF NONNULL((1)) void /* From "memory/mman/mfile.c" */
NOTHROW(KCALL mfile_zero_loadpages)(struct mfile *__restrict self,
                                    pos_t addr, physaddr_t buf, size_t num_bytes,
                                    struct aio_multihandle *__restrict aio);

PUBLIC_CONST struct flnknode_ops const ramfs_lnknode_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &ramfs_lnknode_v_destroy,
			.mo_changed = &ramfs_lnknode_v_changed,
		},
		.no_wrattr = &ramfs_lnknode_v_wrattr,
	},
	.lno_readlink = &ramfs_lnknode_v_readlink,
	.lno_linkstr  = &ramfs_lnknode_v_linkstr,
};

PUBLIC_CONST struct fregnode_ops const ramfs_regnode_ops = {
	.rno_node = {
		.no_file = {
			.mo_destroy    = &ramfs_regnode_v_destroy,
			.mo_loadblocks = &mfile_zero_loadpages,
			.mo_changed    = &ramfs_regnode_v_changed,
		},
		.no_wrattr = &ramfs_regnode_v_wrattr,
	},
};

PRIVATE struct mfile_stream_ops const ramfs_devnode_v_stream_ops = {
	.mso_open  = &ramfs_devnode_v_open,
	.mso_ioctl = &ramfs_devnode_v_ioctl,
};
PUBLIC_CONST struct fdevnode_ops const ramfs_devnode_ops = {
	.dvno_node = {
		.no_file = {
			.mo_destroy = &ramfs_devnode_v_destroy,
			.mo_changed = &ramfs_devnode_v_changed,
			.mo_stream  = &ramfs_devnode_v_stream_ops,
		},
		.no_wrattr = &ramfs_devnode_v_wrattr,
	},
};


PRIVATE struct mfile_stream_ops const ramfs_fifonode_v_stream_ops = {
	.mso_open     = &ramfs_fifonode_v_open,
	.mso_read     = &ramfs_fifonode_v_read,
	.mso_readv    = &ramfs_fifonode_v_readv,
	.mso_write    = &ramfs_fifonode_v_write,
	.mso_writev   = &ramfs_fifonode_v_writev,
	.mso_truncate = &ramfs_fifonode_v_truncate,
	.mso_stat     = &ramfs_fifonode_v_stat,
	.mso_ioctl    = &ramfs_fifonode_v_ioctl,
};
PUBLIC_CONST struct ffifonode_ops const ramfs_fifonode_ops = {
	.fno_node = {
		.no_file = {
			.mo_destroy = &ramfs_fifonode_v_destroy,
			.mo_changed = &ramfs_fifonode_v_changed,
			.mo_stream  = &ramfs_fifonode_v_stream_ops,
		},
		.no_wrattr = &ramfs_fifonode_v_wrattr,
	},
};


PRIVATE struct mfile_stream_ops const ramfs_socknode_v_stream_ops = {
	.mso_open  = &ramfs_socknode_v_open,
	.mso_ioctl = &ramfs_socknode_v_ioctl,
};
PUBLIC_CONST struct fsocknode_ops const ramfs_socknode_ops = {
	.suno_node = {
		.no_file = {
			.mo_destroy = &ramfs_socknode_v_destroy,
			.mo_changed = &ramfs_socknode_v_changed,
			.mo_stream  = &ramfs_socknode_v_stream_ops,
		},
		.no_wrattr = &ramfs_socknode_v_wrattr,
	},
};



/* Directory entry operators for instances of `ramfs_dirent' */
PUBLIC_CONST struct fdirent_ops const ramfs_dirent_ops = {
	.fdo_destroy  = &ramfs_dirent_v_destroy,
	.fdo_opennode = &ramfs_dirent_v_opennode,
};

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct ramfs_dirent *me;
	me = container_of(self, struct ramfs_dirent, rde_ent);
	decref(me->rde_node);
	kfree(me);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct fnode *
NOTHROW(KCALL ramfs_dirent_v_opennode)(struct fdirent *__restrict self,
                                       struct fdirnode *__restrict UNUSED(dir)) {
	struct ramfs_dirent *me;
	me = container_of(self, struct ramfs_dirent, rde_ent);
	return (REF struct fnode *)incref(me->rde_node);
}



/* Directory enumeration operators for `struct ramfs_direnum' */
PUBLIC_CONST struct fdirenum_ops const ramfs_direnum_ops = {
	.deo_fini    = &ramfs_direnum_v_fini,
	.deo_readdir = &ramfs_direnum_v_readdir,
	.deo_seekdir = &ramfs_direnum_v_seekdir,
};

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_direnum_v_fini)(struct fdirenum *__restrict self) {
	struct ramfs_direnum *me = (struct ramfs_direnum *)self;
	axref_fini(&me->rde_next);
}



/* Given a dirent `self' that has been deleted (RAMFS_DIRENT_TREENODE_DELETED),
 * return a pointer  to the first  dirent in `dir'  that has a  lexicographical
 * order `>= self'. The caller must be holding `dir->rdn_dat.rdd_lock' */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) struct ramfs_dirent *
NOTHROW(FCALL ramfs_dirent_fixdeleted)(struct ramfs_dirent *__restrict self,
                                       struct ramfs_dirnode *__restrict dir) {
	struct ramfs_dirent *result = NULL;
	struct ramfs_dirent *root;
	assert(self->rde_treenode.rb_lhs == RAMFS_DIRENT_TREENODE_DELETED);
	root = dir->rdn_dat.rdd_tree;
	while (root) {
		int cmp = strcmpz(root->rde_ent.fd_name,
		                  self->rde_ent.fd_name,
		                  self->rde_ent.fd_namelen);
		if (cmp >= 0) {
			result = root;
			root   = root->rde_treenode.rb_lhs;
		} else {
			root = root->rde_treenode.rb_rhs;
		}
	}
	return result;
}

/* Returns `NULL' if there is no next node */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct ramfs_dirent *KCALL
ramfs_dirent_next(struct ramfs_dirent *__restrict self,
                  struct ramfs_dirnode *__restrict dir)
		THROWS(...) {
	REF struct ramfs_dirent *result;
	ramfs_dirnode_read(dir);
	COMPILER_READ_BARRIER();
	/* Check for special case: `self' was deleted. */
	if unlikely(self->rde_treenode.rb_lhs == RAMFS_DIRENT_TREENODE_DELETED) {
		/* Next node is the closest life entry with a name `>= self' */
		result = ramfs_dirent_fixdeleted(self, dir);
	} else {
		/* Return a reference to the next node within the tree. */
		result = ramfs_direnttree_nextnode(self);
	}
	xincref(result);
	ramfs_dirnode_endread(dir);
	return result;
}

PUBLIC BLOCKING NONNULL((1)) size_t KCALL
ramfs_direnum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                        size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_WOULDBLOCK, ...) {
	ssize_t result;
	REF struct ramfs_dirent *ent;
	struct ramfs_direnum *me = (struct ramfs_direnum *)self;
again:
	ent = axref_get(&me->rde_next);
	if (!ent)
		return 0; /* End of directory */
	{
		REF struct ramfs_dirent *next;
		FINALLY_DECREF_UNLIKELY(ent);
		/* Feed the entry to the user-buffer */
		result = fdirenum_feedent_fast(buf, bufsize, readdir_mode, &ent->rde_ent);
		if (result < 0)
			return (size_t)~result; /* Don't advance directory position. */

		/* Advance the enumerator to the next entry. */
		next = ramfs_dirent_next(ent, (struct ramfs_dirnode *)me->de_dir);
		if (!axref_cmpxch_inherit_new(&me->rde_next, ent, next)) {
			/* Race condition: some other thread modified our `rde_next' before
			 * we were able to modify it. As such, we must re-attempt the read. */
			xdecref_unlikely(next); /* Reference _NOT_ inherited by `axref_cmpxch_inherit_new()' */
			goto again;
		}
	}
	return (size_t)result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL ramfs_dirent_tree_count)(struct ramfs_dirent const *__restrict self) {
	size_t result = 0;
again:
	++result;
	if (self->rde_treenode.rb_lhs) {
		if (self->rde_treenode.rb_rhs)
			result += ramfs_dirent_tree_count(self->rde_treenode.rb_rhs);
		self = self->rde_treenode.rb_lhs;
		goto again;
	}
	if (self->rde_treenode.rb_rhs) {
		self = self->rde_treenode.rb_rhs;
		goto again;
	}
	return result;
}

/* Return the # of directory entries within `self'. Caller must be holding the lock. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL ramfs_dir_count_entries)(struct ramfs_dirnode const *__restrict self) {
	size_t result = 0;
	struct ramfs_dirent const *root;
	root = self->rdn_dat.rdd_tree;
	if (root != NULL)
		result = ramfs_dirent_tree_count(root);
	return result;
}

PUBLIC BLOCKING NONNULL((1)) pos_t KCALL
ramfs_direnum_v_seekdir(struct fdirenum *__restrict self,
                        off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	pos_t result;
	REF struct ramfs_dirent *oldent;
	REF struct ramfs_dirent *newent;
	struct ramfs_direnum *me  = (struct ramfs_direnum *)self;
	struct ramfs_dirnode *dir = (struct ramfs_dirnode *)me->de_dir;
again:
	oldent = axref_get(&me->rde_next);
	TRY {
		ramfs_dirnode_read(dir);
	} EXCEPT {
		xdecref_unlikely(oldent);
		RETHROW();
	}
	switch (whence) {

	case SEEK_SET: {
		result = 0;
		newent = dir->rdn_dat.rdd_tree;
		if (newent != NULL) {
			pos_t delta = (pos_t)offset;
			while (newent->rde_treenode.rb_lhs)
				newent = newent->rde_treenode.rb_lhs;
			while (delta--) {
				newent = ramfs_direnttree_nextnode(newent);
				++result;
				if (!newent)
					break;
			}
		}
	}	break;

	case SEEK_CUR: {
		newent = oldent;
		/* Fix deleted nodes. */
		if (newent && newent->rde_treenode.rb_lhs == RAMFS_DIRENT_TREENODE_DELETED)
			newent = ramfs_dirent_fixdeleted(newent, dir);
do_seek_cur:
		if (offset <= 0) {
			struct ramfs_dirent *pred;
			pos_t delta = (pos_t)-offset;
			if (!newent) {
				/* Old position is at the end of the directory. */
				if (delta == 0)
					goto do_seek_end; /* Stay at end of directory. */
				newent = dir->rdn_dat.rdd_tree;
				if unlikely(newent == NULL) {
					/* Directory is empty (or was deleted) */
					newent = NULL;
					result = 0;
					break;
				}
				while (newent->rde_treenode.rb_rhs)
					newent = newent->rde_treenode.rb_rhs;
				--delta; /* Because `newent' currently points at the last entry (rather than at the end) */
			}
			/* Seek backwards */
			while (delta--) {
				pred = ramfs_direnttree_prevnode(newent);
				if (!pred)
					break;
				newent = pred;
			}

			/* Set `result = NUMBER_OF_NODES_BEFORE(newent)' */
			for (result = 0, pred = newent;;) {
				pred = ramfs_direnttree_prevnode(pred);
				if (!pred)
					break;
				++result;
			}
		} else {
			struct ramfs_dirent *pred;
			pos_t delta = (pos_t)offset;
			/* Positive seek offset.
			 * Start by counting the # of nodes leading up to `newent' */
			for (result = 0, pred = newent;;) {
				pred = ramfs_direnttree_prevnode(pred);
				if (!pred)
					break;
				++result;
			}

			/* Now advance `delta' times (but stop if we reach the end) */
			do {
				++result;
				newent = ramfs_direnttree_nextnode(newent);
			} while (newent && --delta);
		}
	}	break;

do_seek_end:
	case SEEK_END: {
		if (offset >= 0) {
			/* Set `newent = NULL' and count the # of entries in the directory. */
			newent = NULL;
			result = (pos_t)ramfs_dir_count_entries(dir);
		} else {
			/* Seek relative to the end of the directory. */
			newent = NULL;
			goto do_seek_cur;
		}
	}	break;

	default:
		ramfs_dirnode_endread(dir);
		xdecref_unlikely(oldent);
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
		break;
	}
	xincref(newent);
	ramfs_dirnode_endread(dir);
	xdecref_unlikely(oldent); /* Returned by `axref_get()' */
	if (!axref_cmpxch_inherit_new(&me->rde_next, oldent, newent)) {
		xdecref_unlikely(newent); /* Not inherited on cmpxch failure. */
		goto again;
	}
	return result;
}


PUBLIC ATTR_PURE WUNUSED struct ramfs_dirent *FCALL
ramfs_direnttree_locate(/*nullable*/ struct ramfs_dirent *root,
                        USER CHECKED char const *key,
                        size_t keylen) THROWS(E_SEGFAULT) {
	while (root) {
		int cmp = strcmpz(root->rde_ent.fd_name, key, keylen);
		if (cmp > 0) {
			root = root->rde_treenode.rb_lhs;
			continue;
		}
		if (cmp < 0) {
			root = root->rde_treenode.rb_rhs;
			continue;
		}
		break;
	}
	return root;
}

PUBLIC ATTR_PURE WUNUSED NONNULL((1)) struct ramfs_dirent *FCALL
_ramfs_direnttree_caselocate(struct ramfs_dirent *__restrict root,
                             USER CHECKED char const *key, size_t keylen)
		THROWS(E_SEGFAULT) {
again:
	if (root->rde_ent.fd_namelen == keylen &&
	    memcasecmp(root->rde_ent.fd_name, key, keylen * sizeof(char)) == 0)
		return root;

	if (root->rde_treenode.rb_lhs) {
		if (root->rde_treenode.rb_rhs) {
			struct ramfs_dirent *result;
			result = _ramfs_direnttree_caselocate(root->rde_treenode.rb_rhs,
			                                      key, keylen);
			if (result)
				return result;
		}
		root = root->rde_treenode.rb_lhs;
		goto again;
	}
	if (root->rde_treenode.rb_rhs) {
		root = root->rde_treenode.rb_rhs;
		goto again;
	}
	return NULL;
}


/* Directory operators for `struct ramfs_dirnode' */
PUBLIC_CONST struct fdirnode_ops const ramfs_dirnode_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &ramfs_dirnode_v_destroy,
			.mo_changed = &ramfs_dirnode_v_changed,
			.mo_stream  = &ramfs_dirnode_v_stream_ops,
		},
		.no_wrattr = &ramfs_dirnode_v_wrattr,
	},
	.dno_lookup = &ramfs_dirnode_v_lookup,
	.dno_enumsz = ramfs_dirnode_v_enumsz,
	.dno_enum   = &ramfs_dirnode_v_enum,
	.dno_mkfile = &ramfs_dirnode_v_mkfile,
	.dno_unlink = &ramfs_dirnode_v_unlink,
	.dno_rename = &ramfs_dirnode_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	.dno_attach_notify = &ramfs_dirnode_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
};

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) struct ramfs_dirent *KCALL
ramfs_dirdata_lookup(struct ramfs_dirnode const *__restrict self,
                     struct flookup_info const *__restrict info) {
	struct ramfs_dirent *result;
	result = ramfs_direnttree_locate(self->rdn_dat.rdd_tree,
	                                 info->flu_name,
	                                 info->flu_namelen);
	if (!result) {
		if ((info->flu_flags & AT_DOSPATH) && self->rdn_dat.rdd_tree) {
			/* Do a case-insensitive search */
			result = _ramfs_direnttree_caselocate(self->rdn_dat.rdd_tree,
			                                      info->flu_name,
			                                      info->flu_namelen);
		}
	}
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ramfs_dirdata_droptree)(REF struct ramfs_dirent *__restrict tree) {
	REF struct ramfs_dirent *lhs, *rhs;
again:
	lhs = tree->rde_treenode.rb_lhs;
	rhs = tree->rde_treenode.rb_rhs;
	ATOMIC_WRITE(tree->rde_treenode.rb_lhs, RAMFS_DIRENT_TREENODE_DELETED);
	decref_unlikely(tree);
	if (lhs) {
		if (rhs)
			ramfs_dirdata_droptree(rhs);
		tree = lhs;
		goto again;
	}
	if (rhs) {
		tree = rhs;
		goto again;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ramfs_dirdata_fini)(struct ramfs_dirdata *__restrict self) {
	if unlikely(self->rdd_tree != NULL)
		ramfs_dirdata_droptree(self->rdd_tree);
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_dirnode_v_destroy)(struct mfile *__restrict self) {
	struct ramfs_dirnode *me = (struct ramfs_dirnode *)mfile_asdir(self);
	ramfs_dirdata_fini(&me->rdn_dat);
	fnode_v_destroy(self);
}

PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
ramfs_dirnode_v_lookup(struct fdirnode *__restrict self,
                       struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK, ...) {
	REF struct fdirent *ret = NULL;
	struct ramfs_dirent *result;
	struct ramfs_dirnode *me;
	me = (struct ramfs_dirnode *)self;
	ramfs_dirnode_read(me);
	RAII_FINALLY { ramfs_dirnode_endread(me); };
	result = ramfs_dirdata_lookup(me, info);
	if (result != NULL)
		ret = incref(&result->rde_ent);
	return ret;
}

PUBLIC NONNULL((1)) void KCALL
ramfs_dirnode_v_enum(struct fdirenum *__restrict result) {
	struct ramfs_dirnode *me;
	struct ramfs_direnum *rt;
	rt = (struct ramfs_direnum *)result;
	me = (struct ramfs_dirnode *)rt->de_dir;
	/* Fill in information */
	ramfs_dirnode_read(me);
	if (me->rdn_dat.rdd_tree != NULL) {
		struct ramfs_dirent *ent;
		/* Start enumeration at the left-most node */
		ent = me->rdn_dat.rdd_tree;
		while (ent->rde_treenode.rb_lhs)
			ent = ent->rde_treenode.rb_lhs;
		incref(ent);
		ramfs_dirnode_endread(me);
		axref_init(&rt->rde_next, ent);
	} else {
		ramfs_dirnode_endread(me);
		axref_init(&rt->rde_next, NULL);
	}
	rt->de_ops = &ramfs_direnum_ops;
}


/* Construct a new fully initialized, but not globally visible, as in:
 *   - return->fn_supent.rb_rhs == FSUPER_NODES_DELETED;
 *   - !LIST_ISBOUND(return, fn_allnodes);
 * ... node for use by ramfs file systems and return it.
 * When `(info->mkf_fmode & S_IFMT) == 0', blindly re-return `info->mkf_hrdlnk.hl_node'
 *
 * The  caller can always  assume that the  returned file-node can be
 * decref'd normally for the  purpose of (possible) destruction,  and
 * that `(info->mkf_fmode & S_IFMT) != 0' implies `!isshared(return)' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
ramfs_dirnode_mknode_frominfo(struct fdirnode *__restrict self,
                              struct fmkfile_info *__restrict info)
		THROWS(E_BADALLOC, E_FSERROR_UNSUPPORTED_OPERATION) {
	REF struct fnode *result;

	/* Allocate the new file-node */
	switch (info->mkf_fmode & S_IFMT) {

	case 0: /* Special case: hard-link */
		return (REF struct fnode *)incref(info->mkf_hrdlnk.hl_node);

	case S_IFDIR: {
		struct ramfs_dirnode *node;
		node = (struct ramfs_dirnode *)kmalloc(sizeof(struct ramfs_dirnode), GFP_NORMAL);
		_fdirnode_init(node, &ramfs_dirnode_ops, self->fn_super);
		node->mf_parts             = MFILE_PARTS_ANONYMOUS;
		node->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
		ramfs_dirdata_init(&node->rdn_dat);
		result = node;
	}	break;

	case S_IFCHR:
	case S_IFBLK: {
		struct fdevnode *node;
		node = (struct fdevnode *)kmalloc(sizeof(struct fdevnode), GFP_NORMAL);
		_fdevnode_init(node, &ramfs_devnode_ops, self->fn_super);
		node->dn_devno = info->mkf_creat.c_rdev;
		result = node;
	}	break;

	case S_IFREG: {
		struct fregnode *node;
		node = (struct fregnode *)kmalloc(sizeof(struct fregnode), GFP_NORMAL);
		_fregnode_init(node, &ramfs_regnode_ops, self->fn_super);
		atomic64_init(&node->mf_filesize, 0);
		result = node;
	}	break;

	case S_IFLNK:
		result = _clnknode_new(self->fn_super,
		                       info->mkf_creat.c_symlink.s_text,
		                       info->mkf_creat.c_symlink.s_size);
		result->mf_ops = &ramfs_lnknode_ops.lno_node.no_file;
		break;

	case S_IFIFO: {
		struct ffifonode *node;
		node = (struct ffifonode *)kmalloc(sizeof(struct ffifonode), GFP_NORMAL);
		_ffifonode_init(node, &ramfs_fifonode_ops, self->fn_super);
		result = node;
	}	break;

	case S_IFSOCK: {
		struct fsocknode *node;
		node = (struct fsocknode *)kmalloc(sizeof(struct fsocknode), GFP_NORMAL);
		_fsocknode_init(node, &ramfs_socknode_ops, self->fn_super);
		result = node;
	}	break;

	default:
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
		break;
	}

	/* skew_kernel_pointer() guaranties  that the  least significant  3 bits  are
	 * unmodified, and `devfs_devnode_makeino()' is designed to set those 3  bits
	 * to all 1s. This way we prevent possible collisions between the  namespaces
	 * within devfs (following the assumption that at least the least significant
	 * bit should be `0' for `new_node' as the result of alignment). */
	result->fn_ino = (ino_t)skew_kernel_pointer(result);
	assertf(((uintptr_t)result->fn_ino & 7) != 7, "%p", result);

	/* Fill in generic file-creation information. */
	result->fn_mode  = info->mkf_fmode;
	result->mf_atime = info->mkf_creat.c_atime;
	result->mf_mtime = info->mkf_creat.c_mtime;
	result->mf_ctime = info->mkf_creat.c_ctime;
	result->mf_btime = info->mkf_creat.c_btime;
	result->fn_uid   = info->mkf_creat.c_owner;
	result->fn_gid   = info->mkf_creat.c_group;
	result->fn_nlink = 1;
	LIST_ENTRY_UNBOUND_INIT(&result->fn_allnodes);
	result->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
	return result;
}



PUBLIC BLOCKING NONNULL((1, 2)) unsigned int KCALL
ramfs_dirnode_v_mkfile(struct fdirnode *__restrict self,
                       struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DELETED,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...) {
	struct ramfs_dirent *old_dirent;
	REF struct ramfs_dirent *new_dirent;
	REF struct fnode *new_node;
	struct ramfs_dirnode *me;
	me = (struct ramfs_dirnode *)self;

#ifndef __OPTIMIZE_SIZE__
	ramfs_dirnode_read(me);
	/* Check for an existing file before doing any allocations */
	TRY {
		if unlikely(me->mf_flags & MFILE_F_DELETED)
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);
		old_dirent = ramfs_dirdata_lookup(me, &info->mkf_lookup_info);
	} EXCEPT {
		ramfs_dirnode_endread(me);
		RETHROW();
	}
	if unlikely(old_dirent) {
		info->mkf_dent = incref(&old_dirent->rde_ent);
		ramfs_dirnode_endread(me);
		info->mkf_rnode = (REF struct fnode *)incref(old_dirent->rde_node);
		return FDIRNODE_MKFILE_EXISTS;
	}
	ramfs_dirnode_endread(me);
#endif /* !__OPTIMIZE_SIZE__ */

	/* Allocate the new file-node */
	new_node = ramfs_dirnode_mknode_frominfo(self, info);

	/* Construct the new directory entry. */
	TRY {
		new_dirent = (REF struct ramfs_dirent *)kmalloc(offsetof(struct ramfs_dirent, rde_ent.fd_name) +
		                                                (info->mkf_namelen + 1) * sizeof(char),
		                                                GFP_NORMAL);
		TRY {
			/* Fill in the new directory entry. */
			*(char *)mempcpy(new_dirent->rde_ent.fd_name, info->mkf_name,
			                 info->mkf_namelen, sizeof(char)) = '\0';

			/* Fill in other fields of the new directory entry. */
			if (info->mkf_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->mkf_name)) {
				info->mkf_hash = fdirent_hash(new_dirent->rde_ent.fd_name,
				                              info->mkf_namelen);
			}
			new_dirent->rde_ent.fd_refcnt  = 2; /* +1: info->mkf_dent, +1: me->rdn_dat.rdd_tree */
			new_dirent->rde_ent.fd_ops     = &ramfs_dirent_ops;
			new_dirent->rde_ent.fd_hash    = info->mkf_hash;
			new_dirent->rde_ent.fd_ino     = new_node->fn_ino;
			new_dirent->rde_ent.fd_namelen = info->mkf_namelen;
			new_dirent->rde_ent.fd_type    = IFTODT(info->mkf_fmode);
			new_dirent->rde_node           = new_node;

			/* Insert the new file */
again_acquire_lock_for_insert:
			ramfs_dirnode_write(me);
			if unlikely(me->mf_flags & MFILE_F_DELETED) {
				ramfs_dirnode_endwrite(me);
				THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);
			}
			old_dirent = ramfs_direnttree_locate(me->rdn_dat.rdd_tree,
			                                     new_dirent->rde_ent.fd_name,
			                                     new_dirent->rde_ent.fd_namelen);
			if (!old_dirent && (info->mkf_flags & AT_DOSPATH) && me->rdn_dat.rdd_tree) {
				/* Do a case-insensitive search */
				old_dirent = _ramfs_direnttree_caselocate(me->rdn_dat.rdd_tree,
				                                           new_dirent->rde_ent.fd_name,
				                                           new_dirent->rde_ent.fd_namelen);
			}
			if unlikely(old_dirent) {
				/* Special case: file already exists. */
				incref(&old_dirent->rde_ent);
				ramfs_dirnode_endwrite(me);
				kfree(new_dirent);
				decref_likely(new_node);
				info->mkf_dent  = &old_dirent->rde_ent;
				info->mkf_rnode = (REF struct fnode *)incref(old_dirent->rde_node);
				return FDIRNODE_MKFILE_EXISTS;
			}

			/* Ensure that we've got write permissions for `me' */
			TRY {
				fnode_access(me, W_OK);
			} EXCEPT {
				ramfs_dirnode_endwrite(me);
				kfree(new_dirent);
				decref_likely(new_node);
				RETHROW();
			}

			if ((info->mkf_fmode & S_IFMT) != 0) {
				struct fsuper *super = self->fn_super;
				/* At this point, the following fields of `new_node' are still unbound:
				 *  - new_node->fn_allnodes
				 *  - new_node->fn_supent */
				assert(!LIST_ISBOUND(new_node, fn_allnodes));
				assert(new_node->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
				assert(!(new_node->mf_flags & MFILE_FN_GLOBAL_REF));
				assert(new_node->mf_flags & MFILE_F_PERSISTENT);
				assert(new_node->mf_refcnt == 1);
				if (!fsuper_nodes_trywrite(super)) {
					ramfs_dirnode_endwrite(me);
					fsuper_nodes_waitwrite(super);
					goto again_acquire_lock_for_insert;
				}
				/* Check if the filesystem has been deleted. */
				if unlikely(super->fs_nodes == FSUPER_NODES_DELETED) {
					fsuper_nodes_endwrite(super);
					ramfs_dirnode_endwrite(me);
					THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_UNMOUNTED);
				}
				if (!fallnodes_tryacquire()) {
					fsuper_nodes_endwrite(super);
					ramfs_dirnode_endwrite(me);
					fallnodes_waitfor();
					goto again_acquire_lock_for_insert;
				}
				new_node->mf_flags |= MFILE_FN_GLOBAL_REF;
				new_node->mf_refcnt += 1; /* For `MFILE_FN_GLOBAL_REF' */
				COMPILER_BARRIER();

				/* Make the newly created node globally visible. */
				fsuper_nodes_insert(super, new_node);
				fallnodes_insert(new_node);

				/* Release locks. */
				fallnodes_release();
				fsuper_nodes_endwrite(super);
			} else {
				/* Hard link -> increment the nlink counter */
				mfile_tslock_acquire(new_node);
				++new_node->fn_nlink;
				mfile_tslock_release(new_node);
				mfile_inotify_attrib(new_node); /* Post `IN_ATTRIB' */
			}

			/* Construct missing references for `new_dirent' */
			incref(new_node); /* For `new_dirent->rde_node' (or `info->mkf_rnode', depending on view) */

			/* Insert the new directory entry. */
			ramfs_direnttree_insert(&me->rdn_dat.rdd_tree, new_dirent); /* Inherit reference */

			/* And with that, the "file" has been created! */
			ramfs_dirnode_endwrite(me);
		} EXCEPT {
			kfree(new_dirent);
			RETHROW();
		}
	} EXCEPT {
		decref_likely(new_node);
		RETHROW();
	}
	info->mkf_dent  = &new_dirent->rde_ent; /* Inherit reference */
	info->mkf_rnode = new_node;             /* Inherit reference */
	return FDIRNODE_MKFILE_SUCCESS;
}

PUBLIC BLOCKING NONNULL((1, 2, 3)) unsigned int KCALL
ramfs_dirnode_v_unlink(struct fdirnode *__restrict self,
                       struct fdirent *__restrict entry,
                       struct fnode *__restrict file)
		THROWS(E_FSERROR_DIRECTORY_NOT_EMPTY, ...) {
	struct ramfs_dirent *known_entry;
	struct ramfs_dirnode *me = (struct ramfs_dirnode *)self;
again:
	ramfs_dirnode_write(me);

	/* Check that `entry' is still correct. */
	known_entry = ramfs_direnttree_locate(me->rdn_dat.rdd_tree,
	                                      entry->fd_name,
	                                      entry->fd_namelen);
	if unlikely(&known_entry->rde_ent != entry) {
		ramfs_dirnode_endwrite(me);
		return FDIRNODE_UNLINK_DELETED;
	}
	/* When `file' is a directory, we must interlock
	 * marking it as deleted with the removal of its
	 * entry. */
	if (fnode_isdir(file)) {
		bool delete_started;
		struct ramfs_dirnode *filedir;
		assert(mfile_isanon(file));
		assert(file->fn_nlink == 1);
		assert(file->mf_ops == &ramfs_dirnode_ops.dno_node.no_file);
		filedir = (struct ramfs_dirnode *)mfile_asdir(file);
		assert(filedir != self);
		if (!ramfs_dirnode_trywrite(filedir)) {
			ramfs_dirnode_endwrite(me);
			ramfs_dirnode_waitwrite(filedir);
			goto again;
		}
		/* Assert that `file' is an empty directory. */
		if (filedir->rdn_dat.rdd_tree != NULL) {
			ramfs_dirnode_endwrite(filedir);
			ramfs_dirnode_endwrite(me);
			/* Non-empty directory! */
			THROW(E_FSERROR_DIRECTORY_NOT_EMPTY);
		}

		/* Mark the directory as deleted. */
		delete_started = fnode_delete_strt(filedir);
		ramfs_dirnode_endwrite(filedir);

		/* Remove entry from our directory tree. */
		ramfs_direnttree_removenode(&me->rdn_dat.rdd_tree, known_entry);
		known_entry->rde_treenode.rb_lhs = RAMFS_DIRENT_TREENODE_DELETED; /* Mark as deleted. */
		ramfs_dirnode_endwrite(me);
		decref_nokill(known_entry); /* From `me->rdn_dat.rdd_tree' */

		if (delete_started) {
			incref(filedir);
			fnode_delete_impl(filedir);
		}
	} else {
		bool last_link_went_away;
		ramfs_direnttree_removenode(&me->rdn_dat.rdd_tree, known_entry);
		known_entry->rde_treenode.rb_lhs = RAMFS_DIRENT_TREENODE_DELETED; /* Mark as deleted. */
		ramfs_dirnode_endwrite(me);
		decref_nokill(known_entry); /* From `me->rdn_dat.rdd_tree' */

		/* For non-directory files, must decrement the NLINK counter. */
		mfile_tslock_acquire(file);
		assert(file->fn_nlink >= 1);
		--file->fn_nlink;
		last_link_went_away = file->fn_nlink == 0;
		if (last_link_went_away)
			last_link_went_away = fnode_delete_strt_with_tslock(file);
		mfile_tslock_release(file);
		mfile_inotify_attrib(file); /* Post `IN_ATTRIB' */

		/* Delete the file (make all mem-parts anonymous) */
		if (last_link_went_away) {
			incref(file);
			fnode_delete_impl(file);
		}
	}
	return FDIRNODE_UNLINK_SUCCESS;
}


PUBLIC BLOCKING NONNULL((1, 2)) unsigned int KCALL
ramfs_dirnode_v_rename(struct fdirnode *__restrict self,
                       struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, ...) {
	struct ramfs_dirent *new_dirent;
	struct ramfs_dirnode *me     = (struct ramfs_dirnode *)self;
	struct ramfs_dirnode *olddir = (struct ramfs_dirnode *)info->frn_olddir;
	struct ramfs_dirent *old_dirent;
	assert(info->frn_oldent->fd_ops == &ramfs_dirent_ops);
	if (info->frn_flags & AT_RENAME_EXCHANGE)
		THROW(E_NOT_IMPLEMENTED_TODO); /* TODO */

#ifndef __OPTIMIZE_SIZE__
	/* Check for an existing file before doing any allocations */
	ramfs_dirnode_read(me);
	{
		struct ramfs_dirent *existing;
		RAII_FINALLY { ramfs_dirnode_endread(me); };
		if unlikely(me->mf_flags & MFILE_F_DELETED)
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);
		existing = ramfs_dirdata_lookup(me, &info->frn_lookup_info);
		if unlikely(existing) {
			if (info->frn_repfile != existing->rde_node) {
				info->frn_dent    = incref(&existing->rde_ent);
				info->frn_repfile = mfile_asnode(incref(existing->rde_node));
				return FDIRNODE_RENAME_EXISTS;
			}
		} else if (info->frn_repfile != NULL) {
			info->frn_repfile = NULL;
			return FDIRNODE_RENAME_EXISTS;
		}
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Allocate the new directory entry. */
	new_dirent = (REF struct ramfs_dirent *)kmalloc(offsetof(struct ramfs_dirent, rde_ent.fd_name) +
	                                                (info->frn_namelen + 1) * sizeof(char),
	                                                GFP_NORMAL);
	TRY {
		/* Fill in the new directory entry. */
		*(char *)mempcpy(new_dirent->rde_ent.fd_name, info->frn_name,
		                 info->frn_namelen, sizeof(char)) = '\0';

		/* Fill in other fields of the new directory entry. */
		if (info->frn_hash == FLOOKUP_INFO_HASH_UNSET) {
			info->frn_hash = fdirent_hash(new_dirent->rde_ent.fd_name,
			                              info->frn_namelen);
		}
		new_dirent->rde_ent.fd_refcnt  = 2; /* +1: info->mkf_dent, +1: me->rdn_dat.rdd_tree */
		new_dirent->rde_ent.fd_ops     = &ramfs_dirent_ops;
		new_dirent->rde_ent.fd_hash    = info->frn_hash;
		new_dirent->rde_ent.fd_ino     = info->frn_file->fn_ino; /* INO numbers are constant here. */
		new_dirent->rde_ent.fd_namelen = info->frn_namelen;
		new_dirent->rde_ent.fd_type    = IFTODT(info->frn_file->fn_mode);
		new_dirent->rde_node           = info->frn_file; /* incref'd later! */
	} EXCEPT {
		kfree(new_dirent);
		RETHROW();
	}

	/* Acquire locks. */
again_acquire_locks:
	TRY {
		ramfs_dirnode_write(me);
	} EXCEPT {
		kfree(new_dirent);
		RETHROW();
	}
	if unlikely(me->mf_flags & MFILE_F_DELETED) {
		ramfs_dirnode_endwrite(me);
		kfree(new_dirent);
		THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);
	}

	/* Check if the file already exists. */
	{
		struct ramfs_dirent *existing;
		existing = ramfs_direnttree_locate(me->rdn_dat.rdd_tree,
		                                   new_dirent->rde_ent.fd_name,
		                                   new_dirent->rde_ent.fd_namelen);
		if (!existing && (info->frn_flags & AT_DOSPATH) && me->rdn_dat.rdd_tree) {
			existing = _ramfs_direnttree_caselocate(me->rdn_dat.rdd_tree,
			                                        new_dirent->rde_ent.fd_name,
			                                        new_dirent->rde_ent.fd_namelen);
		}
		if (existing) {
			if (info->frn_repfile != existing->rde_node) {
				info->frn_dent    = incref(&existing->rde_ent);
				info->frn_repfile = mfile_asnode(incref(existing->rde_node));
				ramfs_dirnode_endwrite(me);
				kfree(new_dirent);
				return FDIRNODE_RENAME_EXISTS;
			}
			/* TODO: Remove `existing' */
			ramfs_dirnode_endwrite(me);
			THROW(E_NOT_IMPLEMENTED_TODO);
		} else if (info->frn_repfile != NULL) {
			ramfs_dirnode_endwrite(me);
			info->frn_repfile = NULL;
			return FDIRNODE_RENAME_EXISTS;
		}
	}

	/* Acquire a lock to the old directory. */
	if (me != olddir) {
		if (!ramfs_dirnode_trywrite(olddir)) {
			ramfs_dirnode_endwrite(me);
			TRY {
				ramfs_dirnode_write(olddir);
			} EXCEPT {
				kfree(new_dirent);
				RETHROW();
			}
			ramfs_dirnode_endwrite(olddir);
			goto again_acquire_locks;
		}

		/* Check if the old directory has already been deleted. */
		if unlikely(olddir->mf_flags & MFILE_F_DELETED) {
			ramfs_dirnode_endwrite(olddir);
			ramfs_dirnode_endwrite(me);
			kfree(new_dirent);
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_PATH);
		}
	}

	/* Check if the file still exists within the  old
	 * directory, and if so, remove it from said dir. */
	old_dirent = container_of(info->frn_oldent, struct ramfs_dirent, rde_ent);
	if (ramfs_direnttree_locate(olddir->rdn_dat.rdd_tree,
	                            old_dirent->rde_ent.fd_name,
	                            old_dirent->rde_ent.fd_namelen) != old_dirent) {
		if (me != olddir)
			ramfs_dirnode_endwrite(olddir);
		ramfs_dirnode_endwrite(me);
		kfree(new_dirent);
		return FDIRNODE_RENAME_DELETED;
	}

	/* Remove `old_dirent' from its tree. */
	ramfs_direnttree_removenode(&olddir->rdn_dat.rdd_tree, old_dirent);
	old_dirent->rde_treenode.rb_lhs = RAMFS_DIRENT_TREENODE_DELETED; /* Mark as deleted. */

	/* Insert the new directory entry into the new folder. */
	ramfs_direnttree_insert(&me->rdn_dat.rdd_tree, new_dirent);

	/* For `new_dirent->rde_node' */
	incref(info->frn_file);

	/* Release locks */
	if (me != olddir)
		ramfs_dirnode_endwrite(olddir);
	ramfs_dirnode_endwrite(me);

	/* Inherited   from   `olddir->rdn_dat.rdd_tree'
	 * (nokill because caller still has a reference) */
	decref_nokill(old_dirent);

	/* Write-back results. */
	info->frn_dent = &new_dirent->rde_ent; /* Inherit reference */
	return FDIRNODE_RENAME_SUCCESS;
}


#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
/* Return values for `ramfs_dirnode_dirent_traced()' */
#define RAMFS_DIRNODE_DIRENT_TRACED_NO    0 /* Not traced */
#define RAMFS_DIRNODE_DIRENT_TRACED_YES   1 /* Is traced */
#define RAMFS_DIRNODE_DIRENT_TRACED_NOCON 2 /* Directory doesn't have a notify controller. */

/* Check if `ent' is traced by `self's notify controller
 * @return: * : One of `RAMFS_DIRNODE_DIRENT_TRACED_*' */
PRIVATE NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(FCALL ramfs_dirnode_dirent_traced)(struct ramfs_dirnode const *__restrict self,
                                           struct ramfs_dirent const *__restrict ent) {
	struct dnotify_controller *dnot;
	struct dnotify_link *link;
	notify_lock_acquire();
	if unlikely(self->mf_notify == NULL) {
		notify_lock_release_br();
		return RAMFS_DIRNODE_DIRENT_TRACED_NOCON; /* Controller was deleted :( */
	}
	dnot = inotify_controller_asdnotify(self->mf_notify);
	link = dnotify_link_tree_locate(dnot->dnc_files, &ent->rde_ent);
	notify_lock_release();
	return link ? RAMFS_DIRNODE_DIRENT_TRACED_YES
	            : RAMFS_DIRNODE_DIRENT_TRACED_NO;
}

PRIVATE BLOCKING NONNULL((1, 2)) bool KCALL
ramfs_dirnode_v_attach_notify_impl(struct ramfs_dirnode *__restrict self,
                                   struct ramfs_dirent *__restrict iter) {
	unsigned int state;
again:

	/* Check the tracing-state of this entry. */
	state = ramfs_dirnode_dirent_traced(self, iter);
	if (state == RAMFS_DIRNODE_DIRENT_TRACED_YES) {
		/* Already being tracked; nothing to do here! */
	} else {
		REF struct fnode *node;
		if (state == RAMFS_DIRNODE_DIRENT_TRACED_NOCON)
			return false; /* No controller --> no need to search for more files! */
		/* Bind the node. Note that we don't have to release `ramfs_dirnode_endread(self)'
		 * for this because `ramfs_dirnode_endread(self)' references a shared lock  (which
		 * is less restrictive  than atomic locks  and can be  held while doing  something
		 * like `kmalloc()') */
		node = mfile_asnode(incref(iter->rde_node));
		TRY {
			node = dnotify_controller_bindchild(self, &iter->rde_ent, node);
		} EXCEPT {
			ramfs_dirnode_endread(self);
			/*decref_nokill(node);*/ /* Inherited by `dnotify_controller_bindchild()' on error */
			RETHROW();
		}
		assert(node == iter->rde_node);
		decref_nokill(node);
	}

	/* Recursively scan the entire tree. */
	if (iter->rde_treenode.rb_lhs) {
		if (iter->rde_treenode.rb_rhs) {
			if (!ramfs_dirnode_v_attach_notify_impl(self, iter->rde_treenode.rb_rhs))
				return false;
		}
		iter = iter->rde_treenode.rb_lhs;
		goto again;
	}
	if (iter->rde_treenode.rb_rhs) {
		iter = iter->rde_treenode.rb_rhs;
		goto again;
	}
	return true;
}

PUBLIC BLOCKING NONNULL((1)) void KCALL
ramfs_dirnode_v_attach_notify(struct fdirnode *__restrict self)
		THROWS(E_BADALLOC, ...) {
	struct ramfs_dirnode *me = (struct ramfs_dirnode *)self;
	ramfs_dirnode_read(me);
	/* Enumerate loaded directory entries. */
	if (me->rdn_dat.rdd_tree != NULL)
		ramfs_dirnode_v_attach_notify_impl(me, me->rdn_dat.rdd_tree);
	ramfs_dirnode_endread(me);
}
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_super_v_destroy)(struct mfile *__restrict self) {
	struct ramfs_super *me = (struct ramfs_super *)mfile_assuper(self);
	ramfs_dirdata_fini(&me->rs_dat);
	fsuper_v_destroy(self);
}





/************************************************************************/
/* RAMFS SUPERBLOCK UNMOUNTING HELPERS                                  */
/************************************************************************/

/* Recursively delete all files from a ramfs filesystem. Once that
 * is done, finish by with  `mfile_delete_impl(&super->fs_root);'.
 *
 * If necessary, files are deleted asynchronously.
 * @return: true:  Synchronous delete
 * @return: false: Asynchronous delete */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(KCALL ramfs_delete_all_files)(struct ramfs_dirnode *dir,
                                      /*inherit(always)*/ REF struct ramfs_super *super);
static_assert(offsetof(struct ramfs_dirent, _rde_dead) ==
              offsetof(struct ramfs_dirent, rde_treenode.rb_rhs),
              "This ensures that .rb_lhs == RAMFS_DIRENT_TREENODE_DELETED can still "
              "be used as normal, together with the fact that the containing dir has "
              "been deleted, which combines into giving us free reign over `rb_rhs'");



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC ramfs_dirnode_delall_postlop)(Tobpostlockop(ramfs_dirnode) *__restrict self,
                                                struct ramfs_dirnode *__restrict UNUSED(obj)) {
	REF struct ramfs_super *me;
	me = container_of(self, struct ramfs_super, fs_root._mf_ramdirplop);

	/* Reap deleted ramfs directory entries, and recursively
	 * clear  our any that reference more ramfs directories. */
	while (!SLIST_EMPTY(&me->fs_root._mf_deadrament)) {
		REF struct ramfs_dirent *ent;
		ent = SLIST_FIRST(&me->fs_root._mf_deadrament);
		assert(ent->rde_treenode.rb_lhs == RAMFS_DIRENT_TREENODE_DELETED);
		assert(ent->rde_node->mf_flags & MFILE_F_DELETED);

		/* Check if this is a directory. */
		if (ent->rde_node->mf_ops == &ramfs_dirnode_ops.dno_node.no_file) {
			if (!ramfs_delete_all_files((struct ramfs_dirnode *)mfile_asdir(ent->rde_node), me))
				return; /* The rest of cleanup will happen asynchronously! */
		} else {
			assertf(!fnode_isdir(ent->rde_node),
			        "If it were a directory, then its operators "
			        "should have indicated a `ramfs_dirnode'!");
		}

		/* Remove the directory entry from the list of dead entries.
		 * Note that it may not necessarily be the first of the list
		 * anymore, as `ramfs_delete_all_files()' may have  inserted
		 * some more entries when recursively deleting directories. */
		SLIST_REMOVE(&me->fs_root._mf_deadrament, ent, _rde_dead);

		/* Drop our reference to the directory entry (which we originally
		 * stole from  the  associated  directory's  `rdn_dat.rdd_tree'). */
		decref_likely(ent);
	}

	/* Finish up by completing deletion of the mem-
	 * file  underlying  the ramfs  root directory.
	 *
	 * This also inherits our reference to `me'! */
	mfile_delete_impl(&me->fs_root);
}

/* Delete all files from the given file-tree. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL delete_file_tree)(REF struct ramfs_dirent *__restrict self,
                                struct ramfs_super *__restrict super) {
	REF struct ramfs_dirent *lhs, *rhs;
again:
	lhs = self->rde_treenode.rb_lhs;
	rhs = self->rde_treenode.rb_rhs;
	DBG_memset(&self->rde_treenode, 0xcc, sizeof(self->rde_treenode));

	/* Mark as deleted. */
	self->rde_treenode.rb_lhs = RAMFS_DIRENT_TREENODE_DELETED;

	/* Add to the list of dead files. */
	SLIST_INSERT(&super->fs_root._mf_deadrament, self, _rde_dead);

	if (lhs) {
		if (rhs)
			delete_file_tree(rhs, super);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(ramfs_dirnode) *
NOTHROW(LOCKOP_CC ramfs_dirnode_delall_lop)(Toblockop(ramfs_dirnode) *__restrict self,
                                            struct ramfs_dirnode *__restrict dir) {
	REF struct ramfs_super *me;
	me = container_of(self, struct ramfs_super, fs_root._mf_ramdirlop);
	if (dir->rdn_dat.rdd_tree != NULL) {
		delete_file_tree(dir->rdn_dat.rdd_tree, me);
		dir->rdn_dat.rdd_tree = NULL;
	}

	/* References from ramfs directory entries are dropped during post. */
	me->fs_root._mf_ramdirplop.oplo_func = &ramfs_dirnode_delall_postlop;
	return &me->fs_root._mf_ramdirplop;
}


/* Recursively delete all files from a ramfs filesystem. Once that
 * is done, finish by with  `mfile_delete_impl(&super->fs_root);'.
 *
 * If necessary, files are deleted asynchronously.
 * @return: true:  Synchronous delete
 * @return: false: Asynchronous delete */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(KCALL ramfs_delete_all_files)(struct ramfs_dirnode *dir,
                                      /*inherit(always)*/ REF struct ramfs_super *super) {
	assert(dir->mf_flags & MFILE_F_DELETED);
	if (ATOMIC_READ(dir->rdn_dat.rdd_tree) != NULL) {
		if (ramfs_dirnode_trywrite(dir)) {
			COMPILER_READ_BARRIER();
			if (dir->rdn_dat.rdd_tree != NULL) {
				delete_file_tree(dir->rdn_dat.rdd_tree, super);
				dir->rdn_dat.rdd_tree = NULL;
			}
			ramfs_dirnode_endwrite(dir);
		} else {
			/* Must use a lock-op to lock `dir' */
			super->fs_root._mf_ramdirlop.olo_func = &ramfs_dirnode_delall_lop;
			oblockop_enqueue(&dir->rdn_dat.rdd_lops, &super->fs_root._mf_ramdirlop);
			_ramfs_dirnode_reap(dir);
			/* Indicate async delete (reaping  of
			 * `super->fs_root._mf_deadrament' is
			 * done async) */
			return false;
		}
	}
	/* Indicate  sync  delete  (caller  must
	 * reap `super->fs_root._mf_deadrament') */
	return true;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ramfs_super_v_delete)(REF struct fsuper *__restrict self) {
	/* When deleting a ramfs superblock, we must recursively go through all
	 * directories  reachable from `self->fs_root',  lock their file trees,
	 * and delete all contained files.
	 *
	 * Otherwise, we'll end up with memory leaks because of the reference loop:
	 *
	 * ```
	 *   ramfs_super::rs_dat::rdd_tree
	 *       ^                  │
	 *       │                  │
	 *       └────┐             v
	 *            │         ramfs_dirent::rde_node
	 *   fnode::fn_super                    │
	 *     ^                                │
	 *     │                                │
	 *     └────────────────────────────────┘
	 * ```
	 *
	 * Without this, following would leak memory:
	 *     $ mkdir /tmp/subfs
	 *     $ mount -t ramfs - /tmp/subfs
	 *     $ echo hi > /tmp/subfs/myfile.txt
	 *     $ umount /tmp/subfs
	 *     $ leaks
	 * Output indicates 3 Memory leaks:
	 *  - ramfs_super:  "/tmp/subfs"
	 *  - ramfs_dirent: "/tmp/subfs/myfile.txt"
	 *  - fregnode:     "/tmp/subfs/myfile.txt"
	 * Which makes sense as these are the 3 objects apart of the loop above.
	 *
	 * Solution: Delete all files from a ramfs superblock during
	 *           the  delete following an umount(2) system call. */
	REF struct ramfs_super *me;
	me = (REF struct ramfs_super *)self;
	SLIST_INIT(&me->fs_root._mf_deadrament);

	/* Kick-start the sync/async file deletion process. */
	if (ramfs_delete_all_files(ramfs_super_asdir(me), me)) {
		/* The root directory was cleared synchronously (reap deleted files) */
		ramfs_dirnode_delall_postlop(&me->fs_root._mf_ramdirplop,
		                             ramfs_super_asdir(me));
	}
}


PUBLIC_CONST struct fsuper_ops const ramfs_super_ops = {
	.so_delete = &ramfs_super_v_delete,
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy = &ramfs_super_v_destroy,
				.mo_changed = &ramfs_super_v_changed,
				.mo_stream  = &ramfs_super_v_stream_ops,
			},
			.no_free   = &ramfs_super_v_free,
			.no_wrattr = &ramfs_super_v_wrattr,
		},
		.dno_lookup = &ramfs_super_v_lookup,
		.dno_enumsz = ramfs_super_v_enumsz,
		.dno_enum   = &ramfs_super_v_enum,
		.dno_mkfile = &ramfs_super_v_mkfile,
		.dno_unlink = &ramfs_super_v_unlink,
		.dno_rename = &ramfs_super_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
		.dno_attach_notify = &ramfs_super_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	},
};

PRIVATE WUNUSED NONNULL((1)) REF struct fsuper *KCALL
ramfs_open(struct ffilesys *__restrict UNUSED(filesys),
           struct mfile *UNUSED(dev),
           UNCHECKED USER char *UNUSED(args)) {
	static_assert((offsetof(struct ramfs_super, rs_dat) -
	               offsetof(struct ramfs_super, fs_root)) ==
	              offsetof(struct ramfs_dirnode, rdn_dat));
	REF struct ramfs_super *result;
	/* Allocate superblock */
	result = (REF struct ramfs_super *)kmalloc(sizeof(struct ramfs_super),
	                                           GFP_NORMAL);

	/* Ramfs-specific fields */
	ramfs_dirdata_init(&result->rs_dat);

	/* Generic fields. */
	result->fs_root.mf_ops               = &ramfs_super_ops.so_fdir.dno_node.no_file;
	result->fs_root.mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->fs_root.mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	result->fs_root.mf_iobashift         = PAGESHIFT;
	result->fs_root.mf_blockshift        = PAGESHIFT;
	result->fs_root.mf_flags             = MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE | MFILE_F_PERSISTENT;
	result->fs_root.fn_ino               = (ino_t)skew_kernel_pointer(&result->fs_root);
	result->fs_root.mf_atime             = realtime();
	result->fs_root.mf_mtime             = result->fs_root.mf_atime;
	result->fs_root.mf_ctime             = result->fs_root.mf_atime;
	result->fs_root.mf_btime             = result->fs_root.mf_atime;
	result->fs_root.fn_mode              = S_IFDIR | 0777;
	result->fs_root.fn_nlink             = 1;
	result->fs_root.fn_uid               = 0;
	result->fs_root.fn_gid               = 0;
	atomic64_init(&result->fs_root.mf_filesize, (uint64_t)-1);

	/* Fill in filesystem features. */
	result->fs_feat.sf_filesize_max       = (pos_t)-1;
	result->fs_feat.sf_uid_max            = (uid_t)-1;
	result->fs_feat.sf_gid_max            = (gid_t)-1;
	result->fs_feat.sf_symlink_max        = (pos_t)-1;
	result->fs_feat.sf_link_max           = (nlink_t)-1;
	result->fs_feat.sf_magic              = RAMFS_MAGIC;
	result->fs_feat.sf_rec_incr_xfer_size = PAGESIZE;
	result->fs_feat.sf_rec_max_xfer_size  = PAGESIZE;
	result->fs_feat.sf_rec_min_xfer_size  = PAGESIZE;
	result->fs_feat.sf_rec_xfer_align     = PAGESIZE;
	result->fs_feat.sf_name_max           = (u16)-1;
	result->fs_feat.sf_filesizebits       = BITSOF(pos_t);

	/* Done! */
	return result;
}


/* Top-level ram filesystem descriptor. */
PUBLIC struct ffilesys ramfs_filesys = {
	.ffs_link = { .sle_next = NULL },
	.ffs_drv  = &drv_self,
	{ .ffs_open = &ramfs_open },
	.ffs_flags = FFILESYS_F_NODEV,
	/* .ffs_name = */ "ramfs",
};




DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_RAMFS_C */
