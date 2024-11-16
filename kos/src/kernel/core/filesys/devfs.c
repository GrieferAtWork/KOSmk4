/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_C 1
#define __WANT_MFILE__mf_lop
#define __WANT_MFILE__mf_plop
#define __WANT_MFILE__mf_fsuperlop
#define __WANT_MFILE__mf_fsuperplop
#define __WANT_FNODE__fn_suplop
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/chrdev.h>
#include <kernel/fs/constdir.h>
#include <kernel/fs/devfs-spec.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/notify.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mfilemeta.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <sched/task.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>
#include <kos/sched/shared-rwlock.h>
#include <kos/uuid.h>
#include <sys/mkdev.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>

#include <format-printer.h>
#include <inttypes.h>
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

/* Devfs by-name tree operations. (For `devfs_byname_tree') */
#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_LOCATE
#define RBTREE(name)         devfs_bynametree_##name
#define RBTREE_T             struct device
#define RBTREE_Tkey          char const *
#define RBTREE_GETNODE(self) (self)->dv_byname_node
#define RBTREE_GETKEY(self)  device_getname(self)
#define RBTREE_REDFIELD      _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags
#define RBTREE_REDBIT        _MFILE_DEVFS_BYNAME_RED
#define RBTREE_CC            FCALL
#define RBTREE_NOTHROW       NOTHROW
#define RBTREE_DECL          FUNDEF
#define RBTREE_IMPL          PUBLIC
#define RBTREE_KEY_EQ(a, b)  (strcmp(a, b) == 0)
#define RBTREE_KEY_NE(a, b)  (strcmp(a, b) != 0)
#define RBTREE_KEY_LO(a, b)  (strcmp(a, b) < 0)
#define RBTREE_KEY_LE(a, b)  (strcmp(a, b) <= 0)
#define RBTREE_KEY_GR(a, b)  (strcmp(a, b) > 0)
#define RBTREE_KEY_GE(a, b)  (strcmp(a, b) >= 0)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* Helper macros for operating on `devfs_byname_tree' while holding the proper lock to `devfs_byname_lock' */
PUBLIC ATTR_PURE WUNUSED struct device *FCALL
devfs_byname_locate(NCX char const *name, u16 namelen)
		THROWS(E_SEGFAULT) {
	struct device *root = devfs_byname_tree;
	while (root) {
		int cmp = strcmpz(root->dv_dirent->dd_dirent.fd_name,
		                  name, namelen);
		if (cmp > 0) {
			root = root->dv_byname_node.rb_lhs;
			continue;
		}
		if (cmp < 0) {
			root = root->dv_byname_node.rb_rhs;
			continue;
		}
		break;
	}
	return root;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) struct device *FCALL
devfs_byname_caselocate_in(struct device *__restrict root,
                           NCX char const *name,
                           u16 namelen)
		THROWS(E_SEGFAULT) {
	struct devdirent *dent;
again:
	dent = root->dv_dirent;
	if (dent->dd_dirent.fd_namelen == namelen &&
	    memcasecmp(dent->dd_dirent.fd_name, name, namelen * sizeof(char)) == 0)
		return root;
	if (root->dv_byname_node.rb_lhs) {
		if (root->dv_byname_node.rb_rhs) {
			struct device *result;
			result = devfs_byname_caselocate_in(root->dv_byname_node.rb_rhs,
			                                    name, namelen);
			if (result)
				return result;
		}
		root = root->dv_byname_node.rb_lhs;
		goto again;
	}
	if (root->dv_byname_node.rb_rhs) {
		root = root->dv_byname_node.rb_rhs;
		goto again;
	}
	return NULL;
}

PUBLIC ATTR_PURE WUNUSED struct device *FCALL
devfs_byname_caselocate(NCX char const *name, u16 namelen)
		THROWS(E_SEGFAULT) {
	struct device *root = devfs_byname_tree;
	if likely(root != NULL)
		root = devfs_byname_caselocate_in(root, name, namelen);
	return root;
}



	/* [1..1] Destroy callback. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devdirent_v_destroy)(struct fdirent *__restrict self) {
	struct devdirent *me;
	me = container_of(self, struct devdirent, dd_dirent);
	kfree(me);
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
devdirent_v_opennode(struct fdirent *__restrict self,
                        struct fdirnode *__restrict dir) {
	struct devdirent *me;
	assert(dir == &devfs.fs_root);
	(void)dir;
	me = container_of(self, struct devdirent, dd_dirent);
	return (REF struct fnode *)awref_get(&me->dd_dev);
}


/* Operators for Instances of `struct devdirent' */
PUBLIC_CONST struct fdirent_ops const devdirent_ops = {
	.fdo_destroy  = &devdirent_v_destroy,
	.fdo_opennode = &devdirent_v_opennode,
};





PUBLIC struct ffilesys devfs_filesys = {
	.ffs_link = { .sle_next = &ramfs_filesys },
	.ffs_drv  = &drv_self,
	{ .ffs_single = &devfs },
	.ffs_flags = FFILESYS_F_SINGLE | FFILESYS_F_NODEV,
	/* .ffs_name = */ "devfs",
};


/* Special sub-directories of /dev/
 * - "./devfs-defs.c": definition
 * - "./devfs-spec.c": implementation */
INTDEF struct fdirnode devfs_block;
INTDEF struct fdirnode devfs_char;
INTDEF struct fdirnode devfs_cpu;
INTDEF struct fdirnode devfs_disk;

/* Directory entries for special /dev/ sub-directories. */
PRIVATE struct constdirent devfs_dirent_block =
CONSTDIRENT_INIT(&devfs_block, DEVFS_INO_BLOCK, DT_DIR, "block", /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0x7eeacfdd, 0x6b636f6c62, 0x75cfeae6, 0x6b636f6c62)/*[[[end]]]*/);
PRIVATE struct constdirent devfs_dirent_char =
CONSTDIRENT_INIT(&devfs_char, DEVFS_INO_CHAR, DT_DIR, "char", /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0x56cab7b, 0x72616863, 0x7eab6d02, 0x72616863)/*[[[end]]]*/);
PRIVATE struct constdirent devfs_dirent_cpu =
CONSTDIRENT_INIT(&devfs_cpu, DEVFS_INO_CPU, DT_DIR, "cpu", /*[[[fdirent_hash]]]*/0x757063/*[[[end]]]*/);
PRIVATE struct constdirent devfs_dirent_disk =
CONSTDIRENT_INIT(&devfs_disk, DEVFS_INO_DISK, DT_DIR, "disk", /*[[[fdirent_hash]]]*/FDIRENT_HASH_INIT(0xc70eb484, 0x6b736964, 0x87b50ec3, 0x6b736964)/*[[[end]]]*/);

/* List of special directory entries in /dev/
 * NOTE: This list _MUST_ be sorted lexicographically ascendingly! */
PRIVATE struct fdirent *const devfs_rootspec[] = {
	constdirent_asent(&devfs_dirent_block), /* "block" */
	constdirent_asent(&devfs_dirent_char),  /* "char" */
	constdirent_asent(&devfs_dirent_cpu),   /* "cpu" */
	constdirent_asent(&devfs_dirent_disk),  /* "disk" */
};

/* Check if a given directory entry is one of `devfs_rootspec' */
#define fdirent_isspec(x) ((x)->fd_ops == &constdirent_ops)

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) struct fdirent *KCALL
devfs_rootspec_lookup(struct flookup_info const *__restrict info)
		THROWS(E_SEGFAULT) {
	unsigned int lo, hi;
	lo = 0;
	hi = lengthof(devfs_rootspec);
	while (lo < hi) {
		struct fdirent *ent;
		size_t i;
		int cmp;
		i = (lo + hi) / 2;
		ent = devfs_rootspec[i];
		cmp = strcmpz(ent->fd_name, info->flu_name, info->flu_namelen);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			return ent;
		}
	}
	return NULL;
}





/* Lookup a device file by name, or fall back  to
 * searching the ramfs portion of the devfs root. */
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_super_v_lookup(struct fdirnode *__restrict self,
                     struct flookup_info *__restrict info) {
	struct device *node;
	REF struct fdirent *result;
	assert(self == &devfs.fs_root);

	/* Check if we can find a device with the specified name. */
	devfs_byname_read();
	node = devfs_byname_locate(info->flu_name, info->flu_namelen);
	if (!node && (info->flu_flags & AT_DOSPATH))
		node = devfs_byname_caselocate(info->flu_name, info->flu_namelen);
	if (node) {
		result = incref(&node->dv_dirent->dd_dirent);
		devfs_byname_endread();
		return result;
	}
	devfs_byname_endread();

	/* Check for special files. */
	result = devfs_rootspec_lookup(info);
	if (result)
		return incref(result);

	/* Fallback to searching through the ramfs portion. */
	return ramfs_dirnode_v_lookup(self, info);
}


#ifndef __fdirent_axref_defined
#define __fdirent_axref_defined
AXREF(fdirent_axref, fdirent);
#endif /* !__fdirent_axref_defined */

struct devfs_root_direnum
#ifdef __cplusplus
    : fdirenum                     /* Underlying enumerator */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirenum      drd_enum; /* Underlying enumerator */
#endif /* !__cplusplus */
	struct fdirent_axref drd_next; /* [0..1][lock(ATOMIC)] Next directory entry to enumerate.
	                                * Either a  `struct ramfs_dirent'  (ramfs_dirent_ops)  or
	                                * a `struct devdirent' (devdirent_ops).  The 2  directory
	                                * data sources `devfs_byname_tree' and `devfs.rs_dat' are
	                                * enumerated in succession (in that same order) */
};
#define fdirent_isdevfs(self) ((self)->fd_ops == &devdirent_ops)
#define fdirent_asdevfs(self) container_of(self, struct devdirent, dd_dirent)
#define fdirent_isramfs(self) ((self)->fd_ops == &ramfs_dirent_ops)
#define fdirent_asramfs(self) container_of(self, struct ramfs_dirent, rde_ent)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devfs_root_direnum_v_fini)(struct fdirenum *__restrict self) {
	struct devfs_root_direnum *me;
	me = (struct devfs_root_direnum *)self;
	axref_fini(&me->drd_next);
}


PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct device *
NOTHROW(FCALL device_fixdeleted)(struct devdirent const *__restrict self) {
	struct device *result = NULL;
	struct device *root;
	root = devfs_byname_tree;
	while (root) {
		int cmp = strcmpz(root->dv_dirent->dd_dirent.fd_name,
		                  self->dd_dirent.fd_name,
		                  self->dd_dirent.fd_namelen);
		if (cmp >= 0) {
			result = root;
			root   = root->dv_byname_node.rb_lhs;
		} else {
			root = root->dv_byname_node.rb_rhs;
		}
	}
	return result;
}


PRIVATE WUNUSED REF struct fdirent *KCALL
devfs_root_first_ramfs_dirent(void) {
	REF struct fdirent *result = NULL;
	struct ramfs_dirent *ent;
	/* Start enumeration at the left-most node */
	ramfs_dirnode_read(&devfs_rootdir);
	ent = devfs.rs_dat.rdd_tree;
	if likely(ent) {
		while (ent->rde_treenode.rb_lhs)
			ent = ent->rde_treenode.rb_lhs;
		result = incref(&ent->rde_ent);
	}
	ramfs_dirnode_endread(&devfs_rootdir);
	return result;
}

PRIVATE WUNUSED REF struct fdirent *KCALL
devfs_root_first_device_dirent(void) {
	struct device *node;
	REF struct fdirent *firstent;
	devfs_byname_read();
	node = devfs_byname_tree;
	if likely(node) {
		while (node->dv_byname_node.rb_lhs)
			node = node->dv_byname_node.rb_lhs;
		firstent = incref(&node->dv_dirent->dd_dirent);
		devfs_byname_endread();
	} else {
		devfs_byname_endread();
		firstent = devfs_root_first_ramfs_dirent();
	}
	return firstent;
}


/* Returns `NULL' if there is no next node */
PRIVATE WUNUSED NONNULL((1)) REF struct fdirent *KCALL
devfs_root_next(struct fdirent *__restrict self)
		THROWS(...) {
	REF struct fdirent *result = NULL;
	if (fdirent_isspec(self)) {
		unsigned int i;
		for (i = 0; i < lengthof(devfs_rootspec) - 1; ++i) {
			if (devfs_rootspec[i] == self)
				return incref(devfs_rootspec[i + 1]);
		}
		result = devfs_root_first_device_dirent();
	} else if (fdirent_isdevfs(self)) {
		struct devdirent *me;
		REF struct device *curr;
		me = fdirent_asdevfs(self);
		devfs_byname_read();
		curr = awref_get(&me->dd_dev);
		if (curr == NULL) {
			struct device *next;
			next = device_fixdeleted(me);
			if (next != NULL) {
				result = incref(&next->dv_dirent->dd_dirent);
				devfs_byname_endread();
			} else {
				devfs_byname_endread();
				result = devfs_root_first_ramfs_dirent();
			}
		} else {
			struct device *next;
			next = devfs_bynametree_nextnode(curr);
			if (next != NULL) {
				result = incref(&next->dv_dirent->dd_dirent);
				_devfs_byname_endread();
				decref_unlikely(curr);
				devfs_byname_reap();
			} else {
				_devfs_byname_endread();
				decref_unlikely(curr);
				devfs_byname_reap();
				result = devfs_root_first_ramfs_dirent();
			}
		}
	} else {
		struct ramfs_dirent *me;
		assert(fdirent_isramfs(self));
		me = fdirent_asramfs(self);
		ramfs_dirnode_read(&devfs_rootdir);
		COMPILER_READ_BARRIER();
		/* Check for special case: `self' was deleted. */
		if unlikely(me->rde_treenode.rb_lhs == RAMFS_DIRENT_TREENODE_DELETED) {
			/* Next node is the closest life entry with a name `>= me' */
			me = ramfs_dirent_fixdeleted(me, ramfs_super_asdir(&devfs));
		} else {
			/* Return a reference to the next node within the tree. */
			me = ramfs_direnttree_nextnode(me);
		}
		if (me != NULL)
			result = incref(&me->rde_ent);
		ramfs_dirnode_endread(&devfs_rootdir);
	}
	return result;
}


PRIVATE NONNULL((1)) size_t KCALL
devfs_root_direnum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                             size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(...) {
	ssize_t result;
	REF struct fdirent *ent;
	struct devfs_root_direnum *me;
	me = (struct devfs_root_direnum *)self;
again:
	ent = axref_get(&me->drd_next);
	if (!ent)
		return 0; /* End of directory */
	{
		REF struct fdirent *next;
		FINALLY_DECREF_UNLIKELY(ent);

		/* Feed the entry to the user-buffer */
		result = fdirenum_feedent_fast(buf, bufsize, readdir_mode, ent);
		if (result < 0)
			return (size_t)~result; /* Don't advance directory position. */

		/* Advance the enumerator to the next entry. */
		next = devfs_root_next(ent);
		if (!axref_cmpxch_inherit_new(&me->drd_next, ent, next)) {
			/* Race condition: some other thread modified our `rde_next' before
			 * we were able to modify it. As such, we must re-attempt the read. */
			xdecref_unlikely(next); /* Reference _NOT_ inherited by `axref_cmpxch_inherit_new()' */
			goto again;
		}
	}
	return (size_t)result;
}

PRIVATE NONNULL((1)) pos_t KCALL
devfs_root_direnum_v_seekdir(struct fdirenum *__restrict self,
                             off_t offset, unsigned int whence)
		THROWS(...) {
	struct devfs_root_direnum *me;
	me = (struct devfs_root_direnum *)self;
	/* XXX: This right here is conforming, but it would be nice
	 *      to also  allow all  of the  other seek  operations. */
	if (offset == 0 && whence == SEEK_SET) {
		REF struct fdirent *firstent;
		firstent = incref(devfs_rootspec[0]);
		axref_set_inherit(&me->drd_next, firstent);
	} else {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return 0;
}

PRIVATE struct fdirenum_ops const devfs_root_direnum_ops = {
	.deo_fini    = &devfs_root_direnum_v_fini,
	.deo_readdir = &devfs_root_direnum_v_readdir,
	.deo_seekdir = &devfs_root_direnum_v_seekdir,
};


#define devfs_super_v_enumsz sizeof(struct devfs_root_direnum)

PRIVATE NONNULL((1)) void KCALL
devfs_super_v_enum(struct fdirenum *__restrict result) {
	struct devfs_root_direnum *rt;
	REF struct fdirent *firstent;
	assert(result->de_dir == &devfs.fs_root);
	rt = (struct devfs_root_direnum *)result;
	firstent   = incref(devfs_rootspec[0]);
	rt->de_ops = &devfs_root_direnum_ops;
	axref_init(&rt->drd_next, firstent); /* Inherit reference. */
}


/* Special  handling  for  file  renaming  in  devfs, since
 * device files may not be moved out of the root directory. */
PRIVATE NONNULL((1, 2)) unsigned int KCALL
devfs_dirnode_v_rename(struct fdirnode *__restrict self,
                       struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_DELETED) {
	if (!fdirent_isramfs(info->frn_oldent))
		THROW(E_FSERROR_READONLY);
	return ramfs_dirnode_v_rename(self, info);
}



PUBLIC_CONST struct fdirnode_ops const devfs_dirnode_ops = {
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
	.dno_rename = &devfs_dirnode_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	.dno_attach_notify = &ramfs_dirnode_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
};



PRIVATE NONNULL((1, 2)) unsigned int KCALL
devfs_super_v_mkfile(struct fdirnode *__restrict self,
                     struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION) {
	REF struct ramfs_dirent *new_dirent;
	REF struct fnode *new_node;
	assert(self == &devfs.fs_root);
	(void)self;

	/* Check if the caller's name referrs to one of the special files. */
	{
		struct fdirent *old_dirent;
		old_dirent = devfs_rootspec_lookup(&info->mkf_lookup_info);
		if unlikely(old_dirent != NULL) {
			info->mkf_dent  = incref(old_dirent);
			info->mkf_rnode = mfile_asnode(incref(fdirent_asconst(old_dirent)->cd_node));
			return FDIRNODE_MKFILE_EXISTS;
		}
	}

	/* Check check for already-exists. */
#ifndef __OPTIMIZE_SIZE__
	{
		REF struct fdirent *old_dirent;
again_lookup:
		old_dirent = devfs_super_v_lookup(self, &info->mkf_lookup_info);
		if unlikely(old_dirent) {
			REF struct fnode *oldnode;
			TRY {
				oldnode = fdirent_opennode(old_dirent, &devfs.fs_root);
			} EXCEPT {
				decref_unlikely(old_dirent);
				RETHROW();
			}
			if unlikely(!oldnode)
				goto again_lookup; /* Deleted */
			info->mkf_dent  = old_dirent; /* Inherit reference */
			info->mkf_rnode = oldnode;    /* Inherit reference */
			return FDIRNODE_MKFILE_EXISTS;
		}
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Check for special case: not allowed to hard-link device files.
	 * Every device file can only ever have a single directory entry! */
	if ((info->mkf_fmode & S_IFMT) == 0 && S_ISDEV(info->mkf_hrdlnk.hl_node->fn_mode) &&
	    info->mkf_hrdlnk.hl_node->mf_ops != &ramfs_devnode_ops.dvno_node.no_file)
		THROW(E_FSERROR_TOO_MANY_HARD_LINKS);

/*create_ramfs_file:*/
	/* Allocate the new file-node */
	new_node = ramfs_dirnode_mknode_frominfo(self, info);

	/* We need special operators for directories (because
	 * device files cannot not be  moved out of the  root
	 * directory) */
	if (S_ISDIR(info->mkf_fmode)) {
		assert(new_node->mf_ops == &ramfs_dirnode_ops.dno_node.no_file);
		new_node->mf_ops = &devfs_dirnode_ops.dno_node.no_file;
	}

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
			new_dirent->rde_ent.fd_refcnt  = 2; /* +1: info->mkf_dent, +1: devfs.rs_dat.rdd_tree */
			new_dirent->rde_ent.fd_ops     = &ramfs_dirent_ops;
			new_dirent->rde_ent.fd_hash    = info->mkf_hash;
			new_dirent->rde_ent.fd_ino     = new_node->fn_ino;
			new_dirent->rde_ent.fd_namelen = info->mkf_namelen;
			new_dirent->rde_ent.fd_type    = IFTODT(info->mkf_fmode);
			new_dirent->rde_node           = new_node;

			/* Insert the new file */
again_acquire_lock_for_insert:
			ramfs_dirnode_write(&devfs_rootdir);
			{
				struct ramfs_dirent *old_dirent;
				old_dirent = ramfs_direnttree_locate(devfs.rs_dat.rdd_tree,
				                                     new_dirent->rde_ent.fd_name,
				                                     new_dirent->rde_ent.fd_namelen);
				if (!old_dirent && (info->mkf_flags & AT_DOSPATH) && devfs.rs_dat.rdd_tree) {
					/* Do a case-insensitive search */
					old_dirent = _ramfs_direnttree_caselocate(devfs.rs_dat.rdd_tree,
					                                          new_dirent->rde_ent.fd_name,
					                                          new_dirent->rde_ent.fd_namelen);
				}
				if unlikely(old_dirent) {
					/* Special case: file already exists. */
					incref(&old_dirent->rde_ent);
					ramfs_dirnode_endwrite(&devfs_rootdir);
					kfree(new_dirent);
					decref_likely(new_node);
					info->mkf_dent  = &old_dirent->rde_ent;
					info->mkf_rnode = mfile_asnode(incref(old_dirent->rde_node));
					return FDIRNODE_MKFILE_EXISTS;
				}
			}

			/* Must also acquire a  lock to the  devfs by-name tree.  But since we  don't
			 * actually intend on modifying it (and only need to make sure that no device
			 * with  the same name is added while we're in here), it's OK to only acquire
			 * a read-lock. */
			if (!devfs_byname_tryread()) {
				ramfs_dirnode_endwrite(&devfs_rootdir);
				devfs_byname_waitread();
				goto again_acquire_lock_for_insert;
			}

			/* Check if there's already a device with the same name. */
			{
				struct device *existing_device;
				existing_device = devfs_byname_locate(new_dirent->rde_ent.fd_name,
				                                      new_dirent->rde_ent.fd_namelen);
				if (!existing_device && (info->mkf_flags & AT_DOSPATH)) {
					existing_device = devfs_byname_caselocate(new_dirent->rde_ent.fd_name,
					                                          new_dirent->rde_ent.fd_namelen);
				}
				if (existing_device) {
					if unlikely(!tryincref(existing_device)) {
						if (!devfs_byname_tryupgrade()) {
							ramfs_dirnode_endwrite(&devfs_rootdir);
							devfs_byname_endread();
							devfs_byname_waitwrite();
							goto again_acquire_lock_for_insert;
						}
						devfs_byname_removenode(existing_device);
						existing_device->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
						devfs_byname_downgrade();
					} else {
						/* Special case: file already exists. */
						ramfs_dirnode_endwrite(&devfs_rootdir);
						info->mkf_dent = incref(&existing_device->dv_dirent->dd_dirent);
						devfs_byname_endread();
						info->mkf_rnode = existing_device;
						kfree(new_dirent);
						decref_likely(new_node);
						return FDIRNODE_MKFILE_EXISTS;
					}
				}
			}

			/* Ensure that we've got write permissions for `devfs.fs_root' */
			TRY {
				fnode_access(&devfs.fs_root, W_OK);
			} EXCEPT {
				ramfs_dirnode_endwrite(&devfs_rootdir);
				devfs_byname_endread();
				RETHROW();
			}

			if ((info->mkf_fmode & S_IFMT) != 0) {
				/* At this point, the following fields of `new_node' are still unbound:
				 *  - new_node->fn_allnodes
				 *  - new_node->fn_supent */
				assert(!LIST_ISBOUND(new_node, fn_allnodes));
				assert(new_node->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
				assert(!(new_node->mf_flags & MFILE_FN_GLOBAL_REF));
				assert(new_node->mf_flags & MFILE_F_PERSISTENT);
				assert(new_node->mf_refcnt == 1);
				if (!fsuper_nodes_trywrite(&devfs)) {
					devfs_byname_endread();
					ramfs_dirnode_endwrite(&devfs_rootdir);
					fsuper_nodes_waitwrite(&devfs);
					goto again_acquire_lock_for_insert;
				}
				if (!fallnodes_tryacquire()) {
					fsuper_nodes_endwrite(&devfs);
					devfs_byname_endread();
					ramfs_dirnode_endwrite(&devfs_rootdir);
					fallnodes_waitfor();
					goto again_acquire_lock_for_insert;
				}
				new_node->mf_flags |= MFILE_FN_GLOBAL_REF;
				new_node->mf_refcnt += 1; /* For `MFILE_FN_GLOBAL_REF' */
				COMPILER_BARRIER();

				/* Make the newly created node globally visible. */
				fsuper_nodes_insert(&devfs, new_node);
				fallnodes_insert(new_node);

				/* Release locks. */
				fallnodes_release();
				fsuper_nodes_endwrite(&devfs);
			} else {
				/* Hard link -> increment the nlink counter */
				mfile_tslock_acquire(new_node);
				atomic_inc(&new_node->fn_nlink);
				mfile_tslock_release(new_node);
				mfile_inotify_attrib(new_node); /* Post `IN_ATTRIB' */
			}

			/* Construct missing references for `new_dirent' */
			incref(new_node); /* For `new_dirent->rde_node' (or `info->mkf_rnode', depending on view) */

			/* Insert the new directory entry. */
			ramfs_direnttree_insert(&devfs_rootdir.rdn_dat.rdd_tree, new_dirent); /* Inherit reference */

			/* And with that, the "file" has been created! */
			devfs_byname_endread();
			ramfs_dirnode_endwrite(&devfs_rootdir);
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


PRIVATE NONNULL((1, 2, 3)) unsigned int KCALL
devfs_super_v_unlink(struct fdirnode *__restrict self,
                     struct fdirent *__restrict entry,
                     struct fnode *__restrict file)
		THROWS(E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY, E_FSERROR_DELETED) {
	assert(self == &devfs.fs_root);
	(void)self;

	/* Check for device files. */
	if (fdirent_isdevfs(entry)) {
		struct devdirent *real_entry;
		struct device *real_file;
		real_entry = container_of(entry, struct devdirent, dd_dirent);
		real_file  = fnode_asdevice(file);
		if (real_file->dv_byname_node.rb_lhs == DEVICE_BYNAME_DELETED)
			return FDIRNODE_UNLINK_DELETED;
		devfs_byname_write();
		COMPILER_READ_BARRIER();
		if (real_file->dv_dirent != real_entry || /* File was renamed */
		    real_file->dv_byname_node.rb_lhs == DEVICE_BYNAME_DELETED /* File was deleted */) {
			devfs_byname_endwrite();
			return FDIRNODE_UNLINK_DELETED;
		}
		devfs_byname_removenode(real_file);
		real_file->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
		assert(awref_ptr(&real_entry->dd_dev) == real_file);
		awref_clear(&real_entry->dd_dev); /* Disconnect the directory entry from the device file. */
		devfs_byname_endwrite();

#if 0 /* No: user-space shouldn't have this power; Only ~true~ hardware device-disappeared,
       *     as well as driver-unload operations should be able to do something like  this! */
		device_delete(real_file);
#endif

		return FDIRNODE_UNLINK_SUCCESS;
	}

	/* Only call the normal ramfs unlink function for ramfs directory entries.
	 * If  the entry belongs to `devfs_rootspec', then indicate that the entry
	 * cannot be removed. */
	if (!fdirent_isramfs(entry))
		THROW(E_FSERROR_READONLY);

	return ramfs_dirnode_v_unlink(self, entry, file);
}




PRIVATE NONNULL((1, 2)) unsigned int KCALL
devfs_super_v_rename(struct fdirnode *__restrict self,
                     struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_DELETED) {
	assert(self == &devfs.fs_root);
	if (info->frn_flags & AT_RENAME_EXCHANGE)
		THROW(E_NOT_IMPLEMENTED_TODO); /* TODO */
	if (fdirent_isdevfs(info->frn_oldent)) {
		/* Rename device files */
		REF struct devdirent *old_dirent;
		REF struct devdirent *new_dirent;
		struct device *devfile;
		assert(info->frn_olddir == &devfs.fs_root);
		assert(fnode_isdevice(info->frn_file));
		devfile    = fnode_asdevice(info->frn_file);
		new_dirent = (REF struct devdirent *)kmalloc(offsetof(struct devdirent, dd_dirent.fd_name) +
		                                                (info->frn_namelen + 1) * sizeof(char),
		                                                GFP_NORMAL);
		TRY {
			/* Fill in the new directory entry. */
			*(char *)mempcpy(new_dirent->dd_dirent.fd_name, info->frn_name,
			                 info->frn_namelen, sizeof(char)) = '\0';

			/* Fill in other fields of the new directory entry. */
			if (info->frn_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->frn_name)) {
				info->frn_hash = fdirent_hash(new_dirent->dd_dirent.fd_name,
				                              info->frn_namelen);
			}
			new_dirent->dd_dirent.fd_refcnt  = 2; /* +1: info->mkf_dent, +1: devfile->dv_dirent */
			new_dirent->dd_dirent.fd_ops     = &devdirent_ops;
			new_dirent->dd_dirent.fd_hash    = info->frn_hash;
			new_dirent->dd_dirent.fd_ino     = devfile->fn_ino; /* INO numbers are constant here. */
			new_dirent->dd_dirent.fd_namelen = info->frn_namelen;
			new_dirent->dd_dirent.fd_type    = IFTODT(devfile->fn_mode);
			awref_init(&new_dirent->dd_dev, devfile);

			/* Lock the by-name tree */
			devfs_byname_write();
		} EXCEPT {
			kfree(new_dirent);
			RETHROW();
		}

		/* Check if the given filename is still up-to-date for  the
		 * device file, and that the file hasn't been deleted, yet. */
		COMPILER_READ_BARRIER();
		old_dirent = devfile->dv_dirent;
		if unlikely(devfile->dv_byname_node.rb_lhs == DEVICE_BYNAME_DELETED || /* Deleted */
		            old_dirent != fdirent_asdevfs(info->frn_oldent)) {         /* Renamed */
			devfs_byname_endwrite();
			kfree(new_dirent);
			return FDIRNODE_RENAME_DELETED;
		}

		/* Check if another device file with the same name already exists. */
		{
			struct device *existing_device;
			existing_device = devfs_byname_locate(new_dirent->dd_dirent.fd_name,
			                                      new_dirent->dd_dirent.fd_namelen);
			if (!existing_device && (info->frn_flags & AT_DOSPATH)) {
				existing_device = devfs_byname_caselocate(new_dirent->dd_dirent.fd_name,
				                                          new_dirent->dd_dirent.fd_namelen);
			}
			if (existing_device) {
				if (info->frn_repfile != existing_device) {
					if (!tryincref(existing_device)) {
						devfs_byname_removenode(existing_device);
						existing_device->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
					} else {
						info->frn_repfile = existing_device; /* Inherit reference */
						devfs_byname_endwrite();
						kfree(new_dirent);
						return FDIRNODE_RENAME_EXISTS;
					}
				} else {
					/* TODO: Remove `existing_device' */
					devfs_byname_endwrite();
					THROW(E_NOT_IMPLEMENTED_TODO);
				}
			} else {
				/* TODO: Must also check for ramfs files! */
				if (info->frn_repfile != NULL) {
					devfs_byname_endwrite();
					kfree(new_dirent);
					return FDIRNODE_RENAME_EXISTS;
				}
			}
		}

		/* Remove the device file within the context of its old name. */
		devfs_byname_removenode(devfile);

		/* Set the new filename. */
		mfile_tslock_acquire(devfile);   /* Also need TSLOCK to write `dv_dirent' */
		devfile->dv_dirent = new_dirent; /* Inherit reference (x2) */
		mfile_tslock_release(devfile);

		/* (Re-)insert the device file into the by-name tree (using the new filename) */
		devfs_byname_insert(devfile);

		/* Release lock. */
		devfs_byname_endwrite();

		/* Clear the back-link from `old_dirent' to the device file in question.
		 * As far as the directory entry  should be concerned, it's device  file
		 * has been deleted. */
		awref_clear(&old_dirent->dd_dev);

		/* Inherited  from  `devfile->dv_dirent'  (nokill  because
		 * the caller still has a reference in `info->frn_oldent') */
		decref_nokill(old_dirent);

		/* Write-back results. */
		info->frn_dent = &new_dirent->dd_dirent; /* Inherit reference */
	} else if (!fdirent_isramfs(info->frn_oldent)) {
		/* Only call the normal ramfs unlink function for ramfs directory entries.
		 * If  the entry belongs to `devfs_rootspec', then indicate that the entry
		 * cannot be removed. */
		THROW(E_FSERROR_READONLY);
	} else {
		struct ramfs_dirent *new_dirent;
		struct ramfs_dirnode *olddir = (struct ramfs_dirnode *)info->frn_olddir;
		struct ramfs_dirent *old_dirent;

		/* Allocate the new directory entry. */
		new_dirent = (REF struct ramfs_dirent *)kmalloc(offsetof(struct ramfs_dirent, rde_ent.fd_name) +
		                                                (info->frn_namelen + 1) * sizeof(char),
		                                                GFP_NORMAL);
		TRY {
			/* Fill in the new directory entry. */
			*(char *)mempcpy(new_dirent->rde_ent.fd_name, info->frn_name,
			                 info->frn_namelen, sizeof(char)) = '\0';

			/* Fill in other fields of the new directory entry. */
			if (info->frn_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->frn_name)) {
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
			ramfs_dirnode_write(&devfs_rootdir);
			if (!devfs_byname_tryread()) {
				ramfs_dirnode_endwrite(&devfs_rootdir);
				devfs_byname_waitread();
				goto again_acquire_locks;
			}
		} EXCEPT {
			kfree(new_dirent);
			RETHROW();
		}

		/* Check if the file already exists. */
		{
			struct ramfs_dirent *existing;
			existing = ramfs_direnttree_locate(devfs.rs_dat.rdd_tree,
			                                   new_dirent->rde_ent.fd_name,
			                                   new_dirent->rde_ent.fd_namelen);
			if (!existing && (info->frn_flags & AT_DOSPATH) && devfs.rs_dat.rdd_tree) {
				existing = _ramfs_direnttree_caselocate(devfs.rs_dat.rdd_tree,
				                                        new_dirent->rde_ent.fd_name,
				                                        new_dirent->rde_ent.fd_namelen);
			}
			if (existing) {
				devfs_byname_endread();
				if (info->frn_repfile != existing->rde_node) {
					info->frn_dent    = incref(&existing->rde_ent);
					info->frn_repfile = mfile_asnode(incref(existing->rde_node));
					ramfs_dirnode_endwrite(&devfs_rootdir);
					kfree(new_dirent);
					return FDIRNODE_RENAME_EXISTS;
				}
				/* TODO: Remove `existing' */
				ramfs_dirnode_endwrite(&devfs_rootdir);
				THROW(E_NOT_IMPLEMENTED_TODO);
			} else if (info->frn_repfile != NULL) {
				ramfs_dirnode_endwrite(&devfs_rootdir);
				info->frn_repfile = NULL;
				info->frn_dent    = NULL;
				kfree(new_dirent);
				return FDIRNODE_RENAME_EXISTS;
			}
		}

		{
			struct device *existing_device;
			existing_device = devfs_byname_locate(new_dirent->rde_ent.fd_name,
			                                      new_dirent->rde_ent.fd_namelen);
			if (!existing_device && (info->frn_flags & AT_DOSPATH)) {
				existing_device = devfs_byname_caselocate(new_dirent->rde_ent.fd_name,
				                                          new_dirent->rde_ent.fd_namelen);
			}
			if (existing_device) {
				if (info->frn_repfile != existing_device) {
					if (!tryincref(existing_device)) {
						if (!devfs_byname_tryupgrade()) {
							devfs_byname_endread();
							ramfs_dirnode_endwrite(&devfs_rootdir);
							TRY {
								devfs_byname_write();
							} EXCEPT {
								kfree(new_dirent);
								RETHROW();
							}
							devfs_byname_endwrite();
							goto again_acquire_locks;
						}
						devfs_byname_removenode(existing_device);
						existing_device->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
						devfs_byname_downgrade();
					} else {
						ramfs_dirnode_endwrite(&devfs_rootdir);
						info->frn_dent    = incref(&existing_device->dv_dirent->dd_dirent);
						info->frn_repfile = existing_device; /* Inherit reference */
						devfs_byname_endread();
						kfree(new_dirent);
						return FDIRNODE_RENAME_EXISTS;
					}
				} else {
					/* TODO: Remove `existing_device' */
					devfs_byname_endread();
					ramfs_dirnode_endwrite(&devfs_rootdir);
					THROW(E_NOT_IMPLEMENTED_TODO);
				}
			} else if (info->frn_repfile != NULL) {
				devfs_byname_endread();
				ramfs_dirnode_endwrite(&devfs_rootdir);
				kfree(new_dirent);
				info->frn_repfile = NULL;
				info->frn_dent    = NULL;
				return FDIRNODE_RENAME_EXISTS;
			}
		}

		/* Acquire a lock to the old directory. */
		if (ramfs_super_asdir(&devfs) != olddir) {
			if (!ramfs_dirnode_trywrite(olddir)) {
				devfs_byname_endread();
				ramfs_dirnode_endwrite(&devfs_rootdir);
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
				devfs_byname_endread();
				ramfs_dirnode_endwrite(olddir);
				ramfs_dirnode_endwrite(&devfs_rootdir);
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
			if (ramfs_super_asdir(&devfs) != olddir)
				ramfs_dirnode_endwrite(olddir);
			devfs_byname_endread();
			ramfs_dirnode_endwrite(&devfs_rootdir);
			kfree(new_dirent);
			return FDIRNODE_RENAME_DELETED;
		}

		/* Remove `old_dirent' from its tree. */
		ramfs_direnttree_removenode(&olddir->rdn_dat.rdd_tree, old_dirent);
		old_dirent->rde_treenode.rb_lhs = RAMFS_DIRENT_TREENODE_DELETED; /* Mark as deleted. */

		/* Insert the new directory entry into the new folder. */
		ramfs_direnttree_insert(&devfs_rootdir.rdn_dat.rdd_tree, new_dirent);

		/* For `new_dirent->rde_node' */
		incref(info->frn_file);

		/* Release locks */
		if (ramfs_super_asdir(&devfs) != olddir)
			ramfs_dirnode_endwrite(olddir);
		devfs_byname_endread();
		ramfs_dirnode_endwrite(&devfs_rootdir);

		/* Inherited   from   `olddir->rdn_dat.rdd_tree'
		 * (nokill because caller still has a reference) */
		decref_nokill(old_dirent);

		/* Write-back results. */
		info->frn_dent = &new_dirent->rde_ent; /* Inherit reference */
	}
	return FDIRNODE_RENAME_SUCCESS;
}



#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
/* Return values for `devfs_super_dirent_traced()' */
#define DEVFS_SUPER_DIRENT_TRACED_NO    0 /* Not traced */
#define DEVFS_SUPER_DIRENT_TRACED_YES   1 /* Is traced */
#define DEVFS_SUPER_DIRENT_TRACED_NOCON 2 /* Directory doesn't have a notify controller. */

/* Check if `ent' is traced by `self's notify controller
 * @return: * : One of `DEVFS_SUPER_DIRENT_TRACED_*' */
PRIVATE NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL devfs_device_traced)(struct device const *__restrict dev) {
	struct dnotify_controller *dnot;
	struct dnotify_link *link;
	notify_lock_acquire();
	if unlikely(devfs.fs_root.mf_meta == NULL ||
	            devfs.fs_root.mf_meta->mfm_notify == NULL) {
		notify_lock_release_br();
		return DEVFS_SUPER_DIRENT_TRACED_NOCON; /* Controller was deleted :( */
	}
	dnot = inotify_controller_asdnotify(devfs.fs_root.mf_meta->mfm_notify);
	link = dnotify_link_tree_locate(dnot->dnc_files, &dev->dv_dirent->dd_dirent);
	notify_lock_release();
	return link ? DEVFS_SUPER_DIRENT_TRACED_YES
	            : DEVFS_SUPER_DIRENT_TRACED_NO;
}

PRIVATE BLOCKING NONNULL((1)) bool KCALL
devfs_super_v_attach_notify_impl(struct device *__restrict iter) {
	unsigned int state;
again:

	/* Check the tracing-state of this entry. */
	state = devfs_device_traced(iter);
	if (state == DEVFS_SUPER_DIRENT_TRACED_YES) {
		/* Already being tracked; nothing to do here! */
	} else {
		if (state == DEVFS_SUPER_DIRENT_TRACED_NOCON)
			return false; /* No controller --> no need to search for more files! */
		incref(iter);
		TRY {
			iter = (struct device *)dnotify_controller_bindchild(&devfs.fs_root,
			                                                     &iter->dv_dirent->dd_dirent,
			                                                     iter);
		} EXCEPT {
			devfs_byname_endread();
			/*decref_nokill(iter);*/ /* Inherited by `dnotify_controller_bindchild()' on error */
			RETHROW();
		}
		decref_nokill(iter);
	}

	/* Recursively scan the entire tree. */
	if (iter->dv_byname_node.rb_lhs) {
		if (iter->dv_byname_node.rb_rhs) {
			if (!devfs_super_v_attach_notify_impl(iter->dv_byname_node.rb_rhs))
				return false;
		}
		iter = iter->dv_byname_node.rb_lhs;
		goto again;
	}
	if (iter->dv_byname_node.rb_rhs) {
		iter = iter->dv_byname_node.rb_rhs;
		goto again;
	}
	return true;
}

PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_super_v_attach_notify(struct fdirnode *__restrict self)
		THROWS(E_BADALLOC, ...) {
	assert(self == &devfs.fs_root);
	/* Load files from the ramfs portion */
	ramfs_dirnode_v_attach_notify(self);

	/* Load actual device files. */
	devfs_byname_read();
	if (devfs_byname_tree != NULL)
		devfs_super_v_attach_notify_impl(devfs_byname_tree);
	devfs_byname_endread();
}
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */


#define devfs_super_v_changed    ramfs_super_v_changed
#define devfs_super_v_open       ramfs_super_v_open
#define devfs_super_v_wrattr     ramfs_super_v_wrattr
#define devfs_super_v_ioctl      ramfs_super_v_ioctl

INTDEF NONNULL((1)) void KCALL /* From "./null.c" */
nullfile_v_stat(struct mfile *__restrict self,
                NCX struct stat *result);

PRIVATE NONNULL((1)) void KCALL /* From "./null.c" */
devfs_super_v_stat(struct mfile *__restrict self,
                   NCX struct stat *result) {
	fdirnode_v_stat(self, result); /* stat("/dev") has normal dir-based stat behavior */
	nullfile_v_stat(self, result); /* stat("/dev") returns `boottime' timestamps! */
}

PRIVATE struct mfile_stream_ops const devfs_super_v_stream_ops = {
	.mso_open  = &devfs_super_v_open,
	.mso_stat  = &devfs_super_v_stat,
	.mso_ioctl = &devfs_super_v_ioctl,
};

/* INTERN because needed in "./devfsdefs.c" */
INTERN_CONST struct fsuper_ops const devfs_super_ops = {
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy = (typeof_field(struct mfile_ops, mo_destroy))(void *)-1, /* Must never be called */
				.mo_changed = &devfs_super_v_changed,
				.mo_stream  = &devfs_super_v_stream_ops,
			},
			.no_free   = (typeof_field(struct fnode_ops, no_free))(void *)-1, /* Must never be called */
			.no_wrattr = &devfs_super_v_wrattr,
		},
		.dno_lookup = &devfs_super_v_lookup,
		.dno_enumsz = devfs_super_v_enumsz,
		.dno_enum   = &devfs_super_v_enum,
		.dno_mkfile = &devfs_super_v_mkfile,
		.dno_unlink = &devfs_super_v_unlink,
		.dno_rename = &devfs_super_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
		.dno_attach_notify = &devfs_super_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	},
};



/* Default operators for `struct device_ops' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC device_v_destroy_postlop)(struct postlockop *__restrict self) {
	struct device *me;
	me = container_of(self, struct device, _mf_plop);
	decref_likely(me->dv_dirent);
	fdevnode_v_destroy(me);
}
PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC device_v_destroy_lop)(struct lockop *__restrict self) {
	struct device *me;
	me = container_of(self, struct device, _mf_lop);
	if (me->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED)
		devfs_byname_removenode(me);
	me->_mf_plop.plo_func = &device_v_destroy_postlop;
	return &me->_mf_plop;
}


/* Destructor (asynchronously  removes  itself  from
 * `devfs_byname_tree' and does `decref(dv_dirent)') */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL device_v_destroy)(struct mfile *__restrict self) {
	struct device *me;
	me = mfile_asdevice(self);
	assert(me->fn_super == &devfs);
	assert(me->dv_dirent);

	/* Drop reference to associated driver. */
	decref_unlikely(me->dv_driver);

	/* Clear the weak reference held by our /dev/-directory entry. */
	awref_clear(&me->dv_dirent->dd_dev);

	/* Must remove `me' from `devfs_byname_tree' */
	if (atomic_read(&me->dv_byname_node.rb_lhs) != DEVICE_BYNAME_DELETED) {
		if (devfs_byname_trywrite()) {
			COMPILER_READ_BARRIER();
			if (me->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED)
				devfs_byname_removenode(me);
			devfs_byname_endwrite();
		} else {
			/* Use a lock-op to do the removal */
			me->_mf_lop.lo_func = &device_v_destroy_lop;
			lockop_enqueue(&devfs_byname_lops, &me->_mf_lop);
			_devfs_byname_reap();
			return;
		}
	}

	decref_likely(me->dv_dirent);
	fdevnode_v_destroy(me);
}


/* Device files can be casted  into PATH and DIRENT  objects,
 * returning the mounting point for /dev/ and the name of the
 * device file. (Note that this even continues to work if the
 * device file has been unlink(2)'d from /dev/!) */
PUBLIC WUNUSED NONNULL((1)) REF void *KCALL
device_v_tryas(struct mfile *__restrict self,
               uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	struct device *me = mfile_asdevice(self);
	switch (wanted_type) {

	case HANDLE_TYPE_PATH:
		return vfs_mount_location(THIS_VFS, &devfs.fs_root);

	case HANDLE_TYPE_DIRENT: {
		REF struct fdirent *result;
		device_getname_lock_acquire(me);
		result = incref(&me->dv_dirent->dd_dirent);
		device_getname_lock_release(me);
		return result;
	}	break;

	default:
		break;
	}
	return NULL;
}

/* Device stream operators (simply only devices `.mso_tryas = &device_v_tryas') */
PUBLIC_CONST struct mfile_stream_ops const device_v_stream_ops = {
	.mso_ioctl = &device_v_ioctl,
	.mso_tryas = &device_v_tryas,
};





/* Return a reference to the filename of `self' */
PUBLIC NOBLOCK ATTR_PURE ATTR_RETNONNULL WUNUSED REF struct devdirent *
NOTHROW(FCALL device_getdevfsfilename)(struct device *__restrict self) {
	REF struct devdirent *result;
	device_getname_lock_acquire(self);
	result = incref(self->dv_dirent);
	device_getname_lock_release(self);
	return result;
}






/* By-name lookup of devices in /dev/ */
PUBLIC struct shared_rwlock devfs_byname_lock = SHARED_RWLOCK_INIT;
PUBLIC struct lockop_slist devfs_byname_lops  = SLIST_HEAD_INITIALIZER(devfs_byname_lops);
extern struct device _devfs_byname_tree__INIT[];
PUBLIC RBTREE_ROOT(device) devfs_byname_tree = _devfs_byname_tree__INIT;



/* Log the event of a new device having gotten registered. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL devfs_log_new_device)(struct device *__restrict self) {
	assert(self->fn_ino == devfs_devnode_makeino(self->fn_mode, self->dn_devno));
	printk(KERN_TRACE "[devfs] New %s-device "
	                  "%#" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                  "%#" PRIxN(__SIZEOF_MINOR_T__) ":"
	                  "%q%s\n",
	       device_ischr(self) ? "chr" : "blk",
	       major(self->dn_devno), minor(self->dn_devno),
	       self->dv_dirent->dd_dirent.fd_name,
	       self->dv_byname_node.rb_lhs == DEVICE_BYNAME_DELETED ? " [deleted]" : "");
}




/* Register a given device `self' within global control structures:
 *  - devfs_byname_tree
 *  - devfs.fs_nodes
 *  - fallnodes_list
 * This  function never creates additional references for `self',
 * but leaves the job of setting up global references (though use
 * of the flags `MFILE_FN_GLOBAL_REF') to the caller
 *
 * This function initializes (before making `self' globally visible):
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->dv_byname_node
 * @return: * : One of `DEVICE_TRYREGISTER_*' */
PUBLIC WUNUSED NONNULL((1)) unsigned int FCALL
device_tryregister(struct device *__restrict self)
		THROWS(E_WOULDBLOCK) {
	unsigned int result;
	assert(self->fn_ino ==
	       devfs_devnode_makeino(self->fn_mode,
	                             self->dn_devno));

	/* Acquire all required locks. */
	_device_register_lock_acquire(true);

	/* With all required locks held, check if this device already exists. */
	if (_device_register_inuse_name(self->dv_dirent->dd_dirent.fd_name,
	                                self->dv_dirent->dd_dirent.fd_namelen)) {
		result = DEVICE_TRYREGISTER_EXISTS_NAME;
		goto done;
	}

	/* Also check in devfs's INode tree. */
	if (_device_register_inuse_ino(self->fn_ino)) {
		result = DEVICE_TRYREGISTER_EXISTS_DEVNO;
		goto done;
	}

	/* Doesn't exist yet -> register our new one! */
	fsuper_nodes_insert(&devfs, self);
	devfs_byname_insert(self);
	fallnodes_insert(self);
	devfs_log_new_device(self);

	/* Indicate success */
	result = DEVICE_TRYREGISTER_SUCCESS;

done:
	/* Release all locks */
	_device_register_lock_release(true);
	return result;
}


/* The following are used internally to implement `device_register()' */
PUBLIC void FCALL
_device_register_lock_acquire(bool allnodes)
		THROWS(E_WOULDBLOCK) {
again:
	devfs_byname_write();
	if (!fsuper_nodes_trywrite(&devfs)) {
		devfs_byname_endwrite();
		fsuper_nodes_waitwrite(&devfs);
		goto again;
	}
	if (!ramfs_dirnode_tryread(&devfs_rootdir)) {
		fsuper_nodes_endwrite(&devfs);
		devfs_byname_endwrite();
		ramfs_dirnode_waitread(&devfs_rootdir);
		goto again;
	}
	if (allnodes && !fallnodes_tryacquire()) {
		ramfs_dirnode_endread(&devfs_rootdir);
		fsuper_nodes_endwrite(&devfs);
		devfs_byname_endwrite();
		fallnodes_waitfor();
		goto again;
	}
}

PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL _device_register_inuse_name)(char const *__restrict name, u16 len) {
	struct device *existing;

	/* Check if this device already exists. */
	existing = devfs_byname_locate(name, len);
	if (existing != NULL) {
		if (!wasdestroyed(existing))
			return true;

		/* Unlink destroyed device. */
		devfs_byname_removenode(existing);
		existing->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
	}

	/* Also check if a custom file with the same name exists within /dev/ */
	if (ramfs_direnttree_locate(devfs.rs_dat.rdd_tree, name, len) != NULL)
		return true;

	return false;
}

PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL _device_register_inuse_ino)(ino_t ino) {
	struct fnode *existing;
	assert(devfs.fs_nodes != FSUPER_NODES_DELETED);
	existing = fsuper_nodes_locate(&devfs, ino);
	if likely(!existing)
		return false;
	if (wasdestroyed(existing)) {
		/* Unlink destroyed device. */
		fsuper_nodes_removenode(&devfs, existing);
		atomic_write(&existing->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
		return false;
	}
	return true;
}

PUBLIC NOBLOCK void
NOTHROW(FCALL _device_register_lock_release)(bool allnodes) {
	/* Release all locks */
	COMPILER_BARRIER();
	if (allnodes)
		_fallnodes_release();
	_ramfs_dirnode_endread(&devfs_rootdir);
	_fsuper_nodes_endwrite(&devfs);
	_devfs_byname_endwrite();

	/* Reap locks */
	if (allnodes)
		fallnodes_reap();
	ramfs_dirnode_reap(&devfs_rootdir);
	fsuper_nodes_reap(&devfs);
	devfs_byname_reap();
}



/* Same as `device_tryregister()', but automatically handle duplicate dev_t and names:
 *  - If  the device's name already exists, mark the device's file as having been deleted,
 *    and don't add it to the by-name tree. As such, the device won't appear in /dev/, and
 *    accessing it will only be possible by creating a device node using its dev_t
 *  - If the device's `dev_t dn_devno'  (read: `ino_t fn_ino') already exists,  increment
 *    the device number by 1 and re-generate the `fn_ino', then try to add it once again.
 *
 * This function initializes (before making `self' globally visible):
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF; # and accompanying `++self->mf_refcnt'
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->dv_byname_node */
PUBLIC NONNULL((1)) void FCALL
device_register(struct device *__restrict self)
		THROWS(E_WOULDBLOCK) {
	assert(self->fn_ino ==
	       devfs_devnode_makeino(self->fn_mode,
	                             self->dn_devno));
	/* Acquire all required locks. */
	_device_register_lock_acquire(true);

	/* With all required locks held, check if this device already exists. */
	if unlikely(_device_register_inuse_name(self->dv_dirent->dd_dirent.fd_name,
	                                        self->dv_dirent->dd_dirent.fd_namelen)) {
		self->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
	} else {
		devfs_byname_insert(self); /* Add to the by-name tree. */
	}

	/* Try to add the device to the nodes tree. */
	while (_device_register_inuse_ino(self->fn_ino)) {
		/* Create a new device number */
		++self->dn_devno;
		self->fn_ino = devfs_devnode_makeino(self->fn_mode,
		                                     self->dn_devno);
	}
	/* Add to the inode tree (for lookup by dev_t) */
	fsuper_nodes_insert(&devfs, self);

	/* Insert into the all-nodes list. */
	fallnodes_insert(self);

	/* Create the global reference (if not created already). */
	if (!(self->mf_flags & MFILE_FN_GLOBAL_REF)) {
		self->mf_flags |= MFILE_FN_GLOBAL_REF;
		++self->mf_refcnt; /* For `MFILE_FN_GLOBAL_REF' (in `fallnodes_list') */
	}

	/* Release all locks */
	devfs_log_new_device(self);
	_device_register_lock_release(true);
}


struct devdirent_printer_data {
	struct devdirent *fpd_ent; /* [0..fpd_len*][owned] entry. */
	size_t            fpd_avl; /* Unused length. */
	size_t            fpd_pos; /* Write offset. */
};

PRIVATE ssize_t FORMATPRINTER_CC
devdirent_printer(void *arg, char const *__restrict text, size_t textlen) {
	struct devdirent_printer_data *me;
	me = (struct devdirent_printer_data *)arg;
	if (textlen > me->fpd_avl) {
		me->fpd_ent = (struct devdirent *)krealloc(me->fpd_ent,
		                                           me->fpd_pos + textlen + 1,
		                                           GFP_NORMAL);
		me->fpd_avl = ((kmalloc_usable_size(me->fpd_ent) / sizeof(char)) - 1) - me->fpd_pos;
	}
	memcpy((char *)me->fpd_ent + me->fpd_pos, text, textlen, sizeof(char));
	me->fpd_pos += textlen;
	me->fpd_avl -= textlen;
	return (ssize_t)textlen;
}


PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct devdirent *FCALL
devdirent_vnewf(char const *__restrict format, va_list args)
		THROWS(E_BADALLOC) {
	struct devdirent_printer_data dat;
	dat.fpd_ent = (struct devdirent *)kmalloc(offsetof(struct devdirent, dd_dirent.fd_name) +
	                                          (16 + 1) * sizeof(char), GFP_NORMAL);
	dat.fpd_pos = offsetof(struct devdirent, dd_dirent.fd_name);
	dat.fpd_avl = ((kmalloc_usable_size(dat.fpd_ent) / sizeof(char)) - 1) - dat.fpd_pos;
	TRY {
		/* Print the format string into the directory entry. */
		format_vprintf(&devdirent_printer, &dat, format, args);
	} EXCEPT {
		kfree(dat.fpd_ent);
		RETHROW();
	}

	/* Free unused memory. */
	if (dat.fpd_avl) {
		struct devdirent *fin;
		fin = (struct devdirent *)krealloc_nx(dat.fpd_ent,
		                                      dat.fpd_pos + 1,
		                                      GFP_NORMAL);
		if likely(fin)
			dat.fpd_ent = fin;
	}

	/* Make sure that the name isn't too long. */
	dat.fpd_pos -= offsetof(struct devdirent, dd_dirent.fd_name);
	if unlikely(dat.fpd_pos > UINT16_MAX) {
		kfree(dat.fpd_ent);
		THROW(E_FSERROR_ILLEGAL_PATH);
	}

	/* Fill in generic fields of the directory entry. */
	dat.fpd_ent->dd_dirent.fd_namelen = (u16)dat.fpd_pos;
	dat.fpd_ent->dd_dirent.fd_refcnt  = 1;
	dat.fpd_ent->dd_dirent.fd_ops     = &devdirent_ops;
	dat.fpd_ent->dd_dirent.fd_hash = fdirent_hash(dat.fpd_ent->dd_dirent.fd_name,
	                                              dat.fpd_ent->dd_dirent.fd_namelen);
	dat.fpd_ent->dd_dirent.fd_name[dat.fpd_pos] = '\0';

	/* Rest of init is done by caller. */
	return dat.fpd_ent;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct devdirent *VCALL
devdirent_newf(char const *__restrict format, ...)
		THROWS(E_BADALLOC) {
	va_list args;
	REF struct devdirent *result;
	va_start(args, format);
	RAII_FINALLY { va_end(args); };
	result = devdirent_vnewf(format, args);
	return result;
}



/* Helper wrapper for `device_register()' that sets a custom device name, and initialize:
 *  - self->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;      # and accompanying `++self->mf_refcnt'
 *  - self->_device_devnode_ _fdevnode_node_ fn_ino                 = devfs_devnode_makeino(fn_mode, dn_devno);
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes            = ...; # s.a. `device_register()'
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent              = ...; # s.a. `device_register()'
 *  - self->_device_devnode_ dn_devno                               = devno;
 *  - self->dv_byname_node                                          = ...; # s.a. `device_register()'
 *  - self->dv_dirent                                               = MAKE_DEVICE_NAME(format, ...); */
PUBLIC NONNULL((1)) void VCALL
device_registerf(struct device *__restrict self, dev_t devno,
                 char const *__restrict format, ...)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	va_list args;
	va_start(args, format);
	RAII_FINALLY { va_end(args); };
	device_vregisterf(self, devno, format, args);
}

PUBLIC NONNULL((1)) void KCALL
device_vregisterf(struct device *__restrict self, dev_t devno,
                  char const *__restrict format, __builtin_va_list args)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct devdirent *name;
	assert(S_ISCHR(self->fn_mode) || S_ISBLK(self->fn_mode));
	self->dn_devno = devno;
	self->fn_ino   = devfs_devnode_makeino(self->fn_mode, devno);

	/* Allocate device name based on format_printf() */
	name = devdirent_vnewf(format, args);

	/* Fill in missing fields of the directory entry. */
	awref_init(&name->dd_dev, self);
	name->dd_dirent.fd_ino  = self->fn_ino;
	name->dd_dirent.fd_type = IFTODT(self->fn_mode);

	self->dv_dirent = name; /* Inherit reference */
	TRY {
		device_register(self);
	} EXCEPT {
		kfree(name);
		RETHROW();
	}
}










/************************************************************************/
/* Helpers for `device_delete()'                                        */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_allnodes_postlop)(struct postlockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, _mf_plop);

	/* At this point, all of the global hooks of `me' have been  removed.
	 * The rest of the deletion work relates only to the underlying mfile
	 * and includes stuff  like anonymizing any  bound mem-parts  (should
	 * the device include direct mmap capabilities) */
	mfile_delete_impl(me); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC device_delete_remove_from_allnodes_lop)(struct lockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, _mf_lop);
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_allnodes)) {
		fallnodes_remove(me);
		LIST_ENTRY_UNBOUND_INIT(&me->fn_allnodes);
	}
	me->_mf_plop.plo_func = &device_delete_remove_from_allnodes_postlop; /* Inherit reference */
	return &me->_mf_plop;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_changed_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                             struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs);
	(void)obj;
	me = container_of(self, struct device, _mf_fsuperplop);

	/* Remove from `fallnodes_list'. */
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_allnodes)) {
		COMPILER_READ_BARRIER();
		if (fallnodes_tryacquire()) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(me, fn_allnodes)) {
				fallnodes_remove(me);
				LIST_ENTRY_UNBOUND_INIT(&me->fn_allnodes);
			}
			COMPILER_READ_BARRIER();
			fallnodes_release();
		} else {
			me->_mf_lop.lo_func = &device_delete_remove_from_allnodes_lop; /* Inherit reference */
			lockop_enqueue(&fallnodes_lockops, &me->_mf_lop);
			_fallnodes_reap();
			return;
		}
	}
	device_delete_remove_from_allnodes_postlop(&me->_mf_plop); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC device_delete_remove_from_changed_lop)(Toblockop(fsuper) *__restrict self,
                                                         struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs);
	(void)obj;
	me = container_of(self, struct device, _mf_fsuperlop);
	if (LIST_ISBOUND(me, fn_changed)) {
		LIST_UNBIND(me, fn_changed);
		decref_nokill(me); /* Reference from the `fn_changed' list. */
	}

	me->_mf_fsuperplop.oplo_func = &device_delete_remove_from_changed_postlop; /* Inherit reference */
	return &me->_mf_fsuperplop;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_byino_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                           struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs);
	(void)obj;
	me = container_of(self, struct device, _mf_fsuperplop);

	/* Remove from `devfs.fs_changednodes'. */
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, fn_changed)) {
		COMPILER_READ_BARRIER();
		if (fsuper_changednodes_tryacquire(&devfs)) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(me, fn_changed)) {
				LIST_UNBIND(me, fn_changed);
				decref_nokill(me); /* Reference from the `fn_changed' list. */
			}
			COMPILER_READ_BARRIER();
			fsuper_changednodes_release(&devfs);
		} else {
			me->_mf_fsuperlop.olo_func = &device_delete_remove_from_changed_lop; /* Inherit reference */
			oblockop_enqueue(&devfs.fs_changednodes_lops, &me->_mf_fsuperlop);
			_fsuper_changednodes_reap(&devfs);
			return;
		}
	}

	device_delete_remove_from_changed_postlop(&me->_mf_fsuperplop,
	                                          &devfs); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC device_delete_remove_from_byino_lop)(Toblockop(fsuper) *__restrict self,
                                                       struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs);
	(void)obj;
	me = container_of(self, struct device, _mf_fsuperlop);
	COMPILER_READ_BARRIER();
	if (me->fn_supent.rb_rhs != FSUPER_NODES_DELETED) {
		if unlikely(me->_fn_suplop.olo_func == &fnode_add2sup_lop) {
			/* Device is still being async-added to the nodes tree.
			 * In this case, we must wait for it to finish doing so
			 * before trying to repeat the remove-from-tree lop. */
			me->_mf_fsuperlop.olo_func = &device_delete_remove_from_byino_lop;
			oblockop_enqueue(&devfs.fs_nodeslockops, &me->_mf_fsuperlop); /* Retry later... */
			return NULL;
		}
		fsuper_nodes_removenode(&devfs, me);
		atomic_write(&me->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
	}
	me->_mf_fsuperplop.oplo_func = &device_delete_remove_from_byino_postlop; /* Inherit reference */
	return &me->_mf_fsuperplop;
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_byname_postlop)(struct postlockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, _mf_plop);
	fnode_delete_impl(me); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC device_delete_remove_from_byname_lop)(struct lockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, _mf_lop);
	COMPILER_READ_BARRIER();
	if (me->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED) {
		devfs_byname_removenode(me);
		me->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
	}
	me->_mf_plop.plo_func = &device_delete_remove_from_byname_postlop; /* Inherit reference */
	return &me->_mf_plop;
}


/* Unregister a given device node from /dev/ and devfs's inode tree, and proceed
 * to call `mfile_delete()'. This process is done asynchronously and can be used
 * to  delete device files  in situations where  devices disappear, or something
 * similar happened. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL device_delete)(struct device *__restrict self) {
	uintptr_t old_flags;
	assert(self->fn_super == &devfs);

	/* Mark the device as deleted (and make available use of the file fields) */
	mfile_tslock_acquire(self);
	old_flags = atomic_fetchor(&self->mf_flags,
	                           MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
	                           MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
	                           MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY |
	                           MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_READONLY);
	mfile_tslock_release(self);

	/* Delete global reference to the device. */
	if ((old_flags & MFILE_FN_GLOBAL_REF) &&
	    (atomic_fetchand(&self->mf_flags, ~(MFILE_FN_GLOBAL_REF)) & MFILE_FN_GLOBAL_REF))
		decref_nokill(self);

	/* Also clear the PERSISTENT flag */
	if (old_flags & MFILE_F_PERSISTENT)
		atomic_and(&self->mf_flags, ~MFILE_F_PERSISTENT);

	if (old_flags & MFILE_F_DELETED)
		return; /* Already deleted, or deletion already in progress. */
	sig_broadcast(&self->mf_initdone);

	incref(self);

	/* Remove from the /dev/ filesystem */
	if (atomic_read(&self->dv_byname_node.rb_lhs) != DEVICE_BYNAME_DELETED) {
		if (devfs_byname_trywrite()) {
			COMPILER_READ_BARRIER();
			if (self->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED) {
				devfs_byname_removenode(self);
				self->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
			}
			devfs_byname_endwrite();
		} else {
			self->_mf_lop.lo_func = &device_delete_remove_from_byname_lop; /* Inherit reference */
			lockop_enqueue(&devfs_byname_lops, &self->_mf_lop);
			_devfs_byname_reap();
			return;
		}
	}
	device_delete_remove_from_byname_postlop(&self->_mf_plop); /* Inherit reference */
}




/************************************************************************/
/* Device lookup                                                        */
/************************************************************************/

/* Lookup a device within devfs, given its INode number.
 * @return: NULL: No such device. */
PUBLIC WUNUSED REF struct device *FCALL
device_lookup_byino(ino_t ino) THROWS(E_WOULDBLOCK) {
	REF struct device *result;
	fsuper_nodes_read(&devfs);
	assert(devfs.fs_nodes != FSUPER_NODES_DELETED);
	result = (REF struct device *)fsuper_nodes_locate(&devfs, ino);
	if (result && !tryincref(result))
		result = NULL; /* Device already destroyed */
	fsuper_nodes_endread(&devfs);
	return result;
}
PUBLIC WUNUSED REF struct device *
NOTHROW(FCALL device_lookup_byino_nx)(ino_t ino) {
	REF struct device *result;
	if (!fsuper_nodes_read_nx(&devfs))
		return NULL;
	assert(devfs.fs_nodes != FSUPER_NODES_DELETED);
	result = (REF struct device *)fsuper_nodes_locate(&devfs, ino);
	if (result && !tryincref(result))
		result = NULL; /* Device already destroyed */
	fsuper_nodes_endread(&devfs);
	return result;
}


/* Lookup a device within devfs, given its name (and possibly type).
 * @param: name:    NUL-terminated device name string.
 * @param: st_mode: Either `0', `S_IFCHR' or `S_IFBLK'
 * @return: NULL: No such device. */
PUBLIC WUNUSED REF struct device *FCALL
device_lookup_byname(NCX char const *name,
                     size_t namelen, mode_t st_mode)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	REF struct device *result;
	if unlikely(namelen > UINT16_MAX)
		return NULL; /* No device could have this long a name. */
	devfs_byname_read();
	RAII_FINALLY {
		devfs_byname_endread();
	};
	result = devfs_byname_locate(name, namelen);
	if (result && st_mode != 0 &&
	    (result->fn_mode & S_IFMT) != (st_mode & S_IFMT))
		result = NULL; /* Wrong mode */
	if (result && !tryincref(result))
		result = NULL; /* Device already destroyed */
	return result;
}


PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) struct blkdev *
NOTHROW(FCALL devfs_find_partuuid)(struct fnode const *__restrict root,
                                   uuid_t const *__restrict uuid,
                                   struct blkdev *result) {
again:
	if (fnode_isblkpart(root)) {
		struct blkdev *dev;
		dev = fnode_asblkdev(root);
		if (bcmp(&dev->bd_partinfo.bp_efi_partuuid, uuid, sizeof(uuid_t)) == 0)
			result = result ? (struct blkdev *)-1 : dev;
	}
	if (root->fn_supent.rb_lhs) {
		if (root->fn_supent.rb_rhs)
			result = devfs_find_partuuid(root->fn_supent.rb_rhs, uuid, result);
		root = root->fn_supent.rb_lhs;
		goto again;
	}
	if (root->fn_supent.rb_rhs) {
		root = root->fn_supent.rb_rhs;
		goto again;
	}
	return result;
}

/* Lookup a block device partition  by its `bp_efi_partuuid'. Also  make
 * sure that in the event of a partition being found, no other partition
 * exists that has the same UUID. If anything other than exactly 1  part
 * is found, return `NULL'. */
PUBLIC WUNUSED NONNULL((1)) REF struct blkdev *FCALL
device_lookup_bypartuuid(uuid_t const *__restrict uuid)
		THROWS(E_WOULDBLOCK) {
	REF struct blkdev *result;
	fsuper_nodes_read(&devfs);
	result = NULL;
	assert(devfs.fs_nodes != FSUPER_NODES_DELETED);
	if likely(devfs.fs_nodes != NULL) {
		result = devfs_find_partuuid(devfs.fs_nodes, uuid, NULL);
		if (result == (REF struct blkdev *)-1)
			result = NULL; /* Ambiguous */
	}
	if (result && !tryincref(result))
		result = NULL;
	fsuper_nodes_endread(&devfs);
	return result;
}

/* Slightly more advanced version of `device_lookup_byname()':
 *  #1: If str starts with "/dev/": string += 5; stringlen -= 5;
 *  #2: Pass `string' to `device_lookup_byname()', and re-return if non-NULL
 *  #3: if `!S_ISCHR(st_mode)' and `string' matches FORMAT_UUID_T, decode a
 *      UUID and make use of `device_lookup_bypartuuid'.
 *  #4: if `st_mode != 0', do `sscanf(string, "%u:%u")' for a major/minor
 *      pair, construct a dev_t, and pass to `device_lookup_bydev()', and
 *      re-return if non-NULL
 *  #5: If all else failed, return `NULL' */
FUNDEF WUNUSED REF struct device *FCALL
device_lookup_bystring(NCX char const *string,
                       size_t stringlen, mode_t st_mode)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	REF struct device *result;
	static char const devfs_prefix[] = "/dev/";
	if (stringlen >= COMPILER_STRLEN(devfs_prefix) &&
	    bcmp(string, devfs_prefix, COMPILER_STRLEN(devfs_prefix), sizeof(char)) == 0) {
		string += COMPILER_STRLEN(devfs_prefix);
		stringlen -= COMPILER_STRLEN(devfs_prefix);
	}
	result = device_lookup_byname(string, stringlen, st_mode);
	if (result != NULL)
		goto done;
	if (!S_ISCHR(st_mode) && stringlen == UUID_STRLEN) {
		uuid_t uuid;
		if (uuid_fromstr(string, &uuid)) {
			result = (REF struct device *)device_lookup_bypartuuid(&uuid);
			if (result != NULL)
				goto done;
		}
	}

	/* sscanf for a valid device ID */
	if (st_mode != 0 && stringlen < 128) {
		major_t major;
		minor_t minor;
		char text[128];
		*(char *)mempcpy(text, string, stringlen, sizeof(char)) = '\0';
		if (sscanf(text, "%u:%u", &major, &minor) == 2) {
			dev_t devno;
			devno  = makedev(major, minor);
			result = device_lookup_bydev(st_mode, devno);
			if (result != NULL)
				goto done;
		}
	}

done:
	return result;
}




#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
do_dump_blkdev(struct blkdev *__restrict self,
               size_t longest_device_name,
               size_t longest_driver_name) {
	uint64_t total_bytes_adj = (uint64_t)blkdev_getsize(self);
	char const *total_bytes_name = DBGSTR("b");
	if (total_bytes_adj >= (uint64_t)1024 * 1024 * 1024) {
		total_bytes_adj /= (uint64_t)1024 * 1024 * 1024;
		total_bytes_name = DBGSTR("GiB");
	} else if (total_bytes_adj >= (uint64_t)1024 * 1024) {
		total_bytes_adj /= (uint64_t)1024 * 1024;
		total_bytes_name = DBGSTR("MiB");
	} else if (total_bytes_adj >= (uint64_t)1024) {
		total_bytes_adj /= (uint64_t)1024;
		total_bytes_name = DBGSTR("KiB");
	}
	dbg_printf(DBGSTR("/dev/" AC_WHITE("%-*s") "  "
	                  "%3.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                  "%-3.2" PRIxN(__SIZEOF_MINOR_T__) "  "
	                  "%*-s  "
	                  "%5" PRIu64 "%s  "
	                  "%-11" PRIu64 "  "
	                  "%" PRIuSIZ "\n"),
	           (unsigned int)longest_device_name,
	           device_getname(self),
	           major(self->dn_devno), minor(self->dn_devno),
	           (unsigned int)longest_driver_name,
	           self->dv_driver->d_name,
	           total_bytes_adj, total_bytes_name,
	           (uint64_t)blkdev_getsectorcount(self),
	           (size_t)blkdev_getsectorsize(self));
	if (blkdev_ispart(self)) {
		if (self->bd_partinfo.bp_active)
			dbg_print(DBGSTR("\tactive: " AC_WHITE("true") "\n"));
		if (self->bd_partinfo.bp_mbr_sysno != 0)
			dbg_printf(DBGSTR("\tsysno: " AC_WHITE("%#" PRIx8) "\n"), self->bd_partinfo.bp_mbr_sysno);
		if (*self->bd_partinfo.bp_efi_name != '\0')
			dbg_printf(DBGSTR("\tname: " AC_WHITE("%q") "\n"), self->bd_partinfo.bp_efi_name);
		if (memxchr(&self->bd_partinfo.bp_efi_typeuuid, 0, sizeof(self->bd_partinfo.bp_efi_typeuuid)))
			dbg_printf(DBGSTR("\ttypeuuid: " AC_WHITE(FORMAT_UUID_T) "\n"), FORMAT_UUID_T_ARGS(self->bd_partinfo.bp_efi_typeuuid));
		if (memxchr(&self->bd_partinfo.bp_efi_partuuid, 0, sizeof(self->bd_partinfo.bp_efi_partuuid)))
			dbg_printf(DBGSTR("\tpartuuid: " AC_WHITE(FORMAT_UUID_T) "\n"), FORMAT_UUID_T_ARGS(self->bd_partinfo.bp_efi_partuuid));
	} else {
		if (*self->bd_rootinfo.br_ata_serial_no != '\0')
			dbg_printf(DBGSTR("\tserial_no: " AC_WHITE("%q") "\n"), self->bd_rootinfo.br_ata_serial_no);
		if (*self->bd_rootinfo.br_ata_fw_rev != '\0')
			dbg_printf(DBGSTR("\tfw_rev: " AC_WHITE("%q") "\n"), self->bd_rootinfo.br_ata_fw_rev);
		if (*self->bd_rootinfo.br_ata_model != '\0')
			dbg_printf(DBGSTR("\tmodel: " AC_WHITE("%q") "\n"), self->bd_rootinfo.br_ata_model);
//		if (*self->bd_rootinfo.br_mbr_diskuid != '\0')
//			dbg_printf(DBGSTR("\tdiskuid: " AC_WHITE("%q") "\n"), self->bd_rootinfo.br_mbr_diskuid);
		if (memxchr(&self->bd_rootinfo.br_efi_uuid, 0, sizeof(self->bd_rootinfo.br_efi_uuid)))
			dbg_printf(DBGSTR("\tuuid: " AC_WHITE(FORMAT_UUID_T) "\n"), FORMAT_UUID_T_ARGS(self->bd_rootinfo.br_efi_uuid));
	}
}

PRIVATE ATTR_DBGTEXT void KCALL
dump_blkdev(struct fnode *__restrict self,
            size_t longest_device_name,
            size_t longest_driver_name) {
again:
	if (fnode_isblkroot(self)) {
		struct blkdev *me = fnode_asblkdev(self);
		struct blkdev *part;
		do_dump_blkdev(me,
		                     longest_device_name,
		                     longest_driver_name);
		LIST_FOREACH (part, &me->bd_rootinfo.br_parts, bd_partinfo.bp_partlink) {
			do_dump_blkdev(part, longest_device_name, longest_driver_name);
		}
	}
	if (self->fn_supent.rb_lhs) {
		if (self->fn_supent.rb_rhs) {
			dump_blkdev(self->fn_supent.rb_rhs,
			                  longest_device_name,
			                  longest_driver_name);
		}
		self = self->fn_supent.rb_lhs;
		goto again;
	}
	if (self->fn_supent.rb_rhs) {
		self = self->fn_supent.rb_rhs;
		goto again;
	}
}

PRIVATE ATTR_DBGTEXT void KCALL
gather_longest_name_lengths(struct fnode *__restrict self, mode_t mode,
                            size_t *__restrict pmax_device_namelen,
                            size_t *__restrict pmax_driver_namelen) {
again:
	if (fnode_isdevice(self) && (self->fn_mode & S_IFMT) == mode) {
		struct device *me = fnode_asdevice(self);
		size_t namelen;
		namelen = me->dv_dirent->dd_dirent.fd_namelen;
		if (*pmax_device_namelen < namelen)
			*pmax_device_namelen = namelen;
		namelen = strlen(me->dv_driver->d_name);
		if (*pmax_driver_namelen < namelen)
			*pmax_driver_namelen = namelen;
	}
	if (self->fn_supent.rb_lhs) {
		if (self->fn_supent.rb_rhs) {
			gather_longest_name_lengths(self->fn_supent.rb_rhs, mode,
			                            pmax_device_namelen,
			                            pmax_driver_namelen);
		}
		self = self->fn_supent.rb_lhs;
		goto again;
	}
	if (self->fn_supent.rb_rhs) {
		self = self->fn_supent.rb_rhs;
		goto again;
	}
}

DBG_COMMAND(lsblk,
            "lsblk\n"
            "\tList all defined block devices\n") {
	size_t longest_device_name = COMPILER_STRLEN("name");
	size_t longest_driver_name = COMPILER_STRLEN("driver");
	if (devfs.fs_nodes) {
		gather_longest_name_lengths(devfs.fs_nodes, S_IFBLK,
		                            &longest_device_name,
		                            &longest_driver_name);
	}
	dbg_print(DBGSTR("     name"));
	if (longest_device_name > COMPILER_STRLEN("name"))
		format_repeat(&dbg_printer, NULL, ' ', longest_device_name - COMPILER_STRLEN("name"));
	dbg_print(DBGSTR("  devno    driver"));
	if (longest_driver_name > COMPILER_STRLEN("driver"))
		format_repeat(&dbg_printer, NULL, ' ', longest_driver_name - COMPILER_STRLEN("driver"));
	dbg_print(DBGSTR("  size      sectors      sector-size\n"));
	if (devfs.fs_nodes) {
		dump_blkdev(devfs.fs_nodes,
		            longest_device_name,
		            longest_driver_name);
	}
	return 0;
}

DECL_END

#include <dev/keyboard.h>
#include <dev/mouse.h>
#include <dev/pty.h>
#include <dev/tty.h>

DECL_BEGIN

PRIVATE ATTR_DBGTEXT void KCALL
do_dump_chrdev(struct chrdev *__restrict self,
               size_t longest_device_name,
               size_t longest_driver_name) {
	char const *kind;
	struct mfile_stream_ops const *ops;
	if (chrdev_istty(self)) {
		kind = ttydev_isptyslave((struct ttydev *)self)
		       ? DBGSTR("pty")
		       : DBGSTR("tty");
	} else if (chrdev_iskbd(self)) {
		kind = DBGSTR("keyboard");
	} else if (chrdev_ismouse(self)) {
		kind = DBGSTR("mouse");
	} else {
		kind = DBGSTR("other");
	}
	dbg_printf(DBGSTR("/dev/" AC_WHITE("%-*s") "  "
	                  "%3.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                  "%-3.2" PRIxN(__SIZEOF_MINOR_T__) "  "
	                  "%*-s  %-8s  "),
	           (unsigned int)longest_device_name,
	           self->dv_dirent->dd_dirent.fd_name,
	           major(self->dn_devno), minor(self->dn_devno),
	           (unsigned int)longest_driver_name,
	           self->dv_driver->d_name,
	           kind);
	ops = self->mf_ops->mo_stream;
	dbg_putc((ops->mso_read || ops->mso_readv) ? 'r' : '-');
	dbg_putc((ops->mso_write || ops->mso_writev) ? 'w' : '-');
	dbg_putc((ops->mso_pread || ops->mso_preadv) ? 'R' : '-');
	dbg_putc((ops->mso_pwrite || ops->mso_pwritev) ? 'W' : '-');
	dbg_putc(ops->mso_ioctl ? 'i' : '-');
	dbg_putc(ops->mso_mmap ? 'm' : '-');
	dbg_putc(ops->mso_stat ? 't' : '-');
	dbg_putc((ops->mso_pollconnect || ops->mso_polltest) ? 'p' : '-');
	dbg_putc('\n');
}

PRIVATE ATTR_DBGTEXT void KCALL
dump_chrdev(struct fnode *__restrict self,
            size_t longest_device_name,
            size_t longest_driver_name) {
again:
	if (fnode_ischrdev(self)) {
		do_dump_chrdev(fnode_aschrdev(self),
		                         longest_device_name,
		                         longest_driver_name);
	}
	if (self->fn_supent.rb_lhs) {
		if (self->fn_supent.rb_rhs) {
			dump_chrdev(self->fn_supent.rb_rhs,
			                      longest_device_name,
			                      longest_driver_name);
		}
		self = self->fn_supent.rb_lhs;
		goto again;
	}
	if (self->fn_supent.rb_rhs) {
		self = self->fn_supent.rb_rhs;
		goto again;
	}
}

DBG_COMMAND(lschr,
            "lschr\n"
            "\tList all defined character devices\n"
            "\tfeatures:\n"
            "\t\t" AC_WHITE("r") ": Supports " AC_WHITE("read") "\n"
            "\t\t" AC_WHITE("w") ": Supports " AC_WHITE("write") "\n"
            "\t\t" AC_WHITE("R") ": Supports " AC_WHITE("pread") "\n"
            "\t\t" AC_WHITE("W") ": Supports " AC_WHITE("pwrite") "\n"
            "\t\t" AC_WHITE("i") ": Supports " AC_WHITE("ioctl") "\n"
            "\t\t" AC_WHITE("m") ": Supports " AC_WHITE("mmap") "\n"
            "\t\t" AC_WHITE("t") ": Supports " AC_WHITE("stat") "\n"
            "\t\t" AC_WHITE("p") ": Supports " AC_WHITE("poll") "\n") {
	size_t longest_device_name = COMPILER_STRLEN("name");
	size_t longest_driver_name = COMPILER_STRLEN("driver");
	if (devfs.fs_nodes) {
		gather_longest_name_lengths(devfs.fs_nodes, S_IFCHR,
		                            &longest_device_name,
		                            &longest_driver_name);
	}
	dbg_print(DBGSTR("     name"));
	if (longest_device_name > COMPILER_STRLEN("name"))
		format_repeat(&dbg_printer, NULL, ' ', longest_device_name - COMPILER_STRLEN("name"));
	dbg_print(DBGSTR("  devno    driver"));
	if (longest_driver_name > COMPILER_STRLEN("driver"))
		format_repeat(&dbg_printer, NULL, ' ', longest_driver_name - COMPILER_STRLEN("driver"));
	dbg_print(DBGSTR("  kind      features\n"));
	if (devfs.fs_nodes) {
		dump_chrdev(devfs.fs_nodes,
		            longest_device_name,
		            longest_driver_name);
	}
	return 0;
}

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_C */
