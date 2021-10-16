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
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_C 1
#define __WANT_MFILE__mf_lop
#define __WANT_MFILE__mf_plop
#define __WANT_MFILE__mf_fsuperlop
#define __WANT_MFILE__mf_fsuperplop
#define __WANT_FS_INIT
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/allnodes.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/node.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/mman/driver.h>
#include <kernel/paging.h>
#include <sched/shared_rwlock.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/dev.h>
#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/guid.h>
#include <linux/magic.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Devfs by-name tree operations. (For `devfs_byname_tree') */
#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_LOCATE
#define RBTREE(name)           devfs_bynametree_##name
#define RBTREE_T               struct device
#define RBTREE_Tkey            char const *
#define RBTREE_GETNODE(self)   (self)->dv_byname_node
#define RBTREE_GETKEY(self)    device_getname(self)
#define RBTREE_ISRED(self)     ((self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags & _MFILE_DEVFS_BYNAME_RED)
#define RBTREE_SETRED(self)    (void)((self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= _MFILE_DEVFS_BYNAME_RED)
#define RBTREE_SETBLACK(self)  (void)((self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags &= ~_MFILE_DEVFS_BYNAME_RED)
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#define RBTREE_KEY_EQ(a, b)    (strcmp(a, b) == 0)
#define RBTREE_KEY_NE(a, b)    (strcmp(a, b) != 0)
#define RBTREE_KEY_LO(a, b)    (strcmp(a, b) < 0)
#define RBTREE_KEY_LE(a, b)    (strcmp(a, b) <= 0)
#define RBTREE_KEY_GR(a, b)    (strcmp(a, b) > 0)
#define RBTREE_KEY_GE(a, b)    (strcmp(a, b) >= 0)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* Helper macros for operating on `devfs_byname_tree' while holding the proper lock to `devfs_byname_lock' */
PUBLIC ATTR_PURE WUNUSED struct device *FCALL
devfs_byname_locate(USER CHECKED char const *name, u16 namelen)
		THROWS(E_SEGFAULT) {
	struct device *root = devfs_byname_tree;
	while (root) {
		int cmp = strcmpz(root->dv_dirent->fdd_dirent.fd_name,
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
                           USER CHECKED char const *name,
                           u16 namelen)
		THROWS(E_SEGFAULT) {
	struct fdevfsdirent *dent;
again:
	dent = root->dv_dirent;
	if (dent->fdd_dirent.fd_namelen == namelen &&
	    memcasecmp(dent->fdd_dirent.fd_name, name, namelen * sizeof(char)) == 0)
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
devfs_byname_caselocate(USER CHECKED char const *name, u16 namelen)
		THROWS(E_SEGFAULT) {
	struct device *root = devfs_byname_tree;
	if likely(root != NULL)
		root = devfs_byname_caselocate_in(root, name, namelen);
	return root;
}



	/* [1..1] Destroy callback. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fdevfsdirent_v_destroy)(struct fdirent *__restrict self) {
	struct fdevfsdirent *me;
	me = container_of(self, struct fdevfsdirent, fdd_dirent);
	kfree(me);
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
fdevfsdirent_v_opennode(struct fdirent *__restrict self,
                        struct fdirnode *__restrict dir) {
	STATIC_ASSERT(offsetof(struct device, dv_devnode.dn_node.fn_file) == 0);
	struct fdevfsdirent *me;
	assert(dir == &devfs.rs_sup.fs_root);
	(void)dir;
	me = container_of(self, struct fdevfsdirent, fdd_dirent);
	return (REF struct fnode *)awref_get(&me->fdd_dev);
}


/* Operators for Instances of `struct fdevfsdirent' */
PUBLIC struct fdirent_ops const fdevfsdirent_ops = {
	.fdo_destroy  = &fdevfsdirent_v_destroy,
	.fdo_opennode = &fdevfsdirent_v_opennode,
};





PUBLIC struct ffilesys devfs_filesys = {
	.ffs_link = { .le_next = &ramfs_filesys, .le_prev = &ffilesys_formats_list.lh_first },
	.ffs_drv  = &drv_self,
	{ .ffs_single = &devfs.rs_sup },
	.ffs_flags = FFILESYS_F_SINGLE,
	.ffs_name  = "devfs",
};


/* TODO:
 *       /dev/disk/by-id/        -- Symlinks for block-devices
 *       /dev/disk/by-label/     -- Symlinks for block-devices
 *       /dev/disk/by-partlabel/ -- Symlinks for block-devices
 *       /dev/disk/by-partuuid/  -- Symlinks for block-devices
 *       /dev/disk/by-path/      -- Symlinks for block-devices
 *       /dev/disk/by-uuid/      -- Symlinks for block-devices
 *       /dev/block/             -- Contains symlinks for the /dev device, such as 8:0 -> ../sda
 *       /dev/char/              -- Contains symlinks for the /dev device, such as 1:1 -> ../mem
 *       /dev/cpu/[id]/cpuid     -- A readable file to access `cpuid' data for a given CPU.
 * All of these should be implemented in "devfs.c" by dynamic means (similar to how /proc/ works)
 * Also  note that unlike the root directory, these special sub-directories are _NOT_ writable on
 * KOS. The files found within cannot be renamed, moved, deleted, etc. and no custom files can be
 * created  either. Only the root directory, and  any dynamically created sub-directory is usable
 * for the purpose of RAMFS.
 *
 * Enumeration here is done in O(N) by walking `devfs.rs_sup.fs_nodes'. The additional complexity
 * of adding individual trees/maps for each of these would be too great, though information about
 * what  filenames appear in these folders must still  be stored on a per-device basis. Also note
 * that some of those folders contain more than just partitions; namely: the actual root devices.
 *
 * TODO: The  devfs root directory node should have INO=1.  Because we use mask &7 for encoding
 *       different  INO namespaces (&7=0 for RAMFS, and &7=7 for by-name devices), we also need
 *       one more namespace for special directories like root, and another for dynamic files as
 *       those described above!
 *
 * NOTE: All of these special INodes actually _DONT_ appear in `devfs.rs_sup.fs_nodes'! This  can
 *       be achieved because INode access within the new fs is not done via `super_opennode' with
 *       the  associated inode number,  but instead via `fdirent_opennode()',  which hides all of
 *       the association details for fdirent->fnode mapping from prying eyes. Technically, it  is
 *       actually possible to create a filesystem that  _NEVER_ makes use of `fs_nodes', and  the
 *       only  reason why unique inode number ~should~ still be assigned is for the sake of user-
 *       space  and programs that rely on the POSIX-guarantied unique-ness of stat::st_dev:st_ino
 *
 */


/* Lookup a device file by name, or fall back  to
 * searching the ramfs portion of the devfs root. */
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_root_v_lookup(struct fdirnode *__restrict self,
                    struct flookup_info *__restrict info) {
	struct device *node;
	assert(self == &devfs.rs_sup.fs_root);

	/* Check if we can find a device with the specified name. */
	devfs_byname_read();
	node = devfs_byname_locate(info->flu_name, info->flu_namelen);
	if (!node && (info->flu_flags & FS_MODE_FDOSPATH))
		node = devfs_byname_caselocate(info->flu_name, info->flu_namelen);
	if (node) {
		REF struct fdirent *result;
		result = incref(&node->dv_dirent->fdd_dirent);
		devfs_byname_endread();
		return result;
	}
	devfs_byname_endread();

	/* Fallback to searching through the ramfs portion. */
	return ramfs_dirnode_v_lookup(self, info);
}

#define devfs_root_v_lookup_fnode fdirnode_v_lookup_fnode


#ifndef __fdirent_axref_defined
#define __fdirent_axref_defined
AXREF(fdirent_axref, fdirent);
#endif /* !__fdirent_axref_defined */

struct devfs_root_direnum {
	struct fdirenum_ops const *drd_ops;  /* [1..1][const] Operators. (== &devfs_root_direnum_ops) */
	struct fdirent_axref       drd_next; /* [0..1][lock(ATOMIC)] Next directory  entry to  enumerate.
	                                      * Either  a  `struct ramfs_dirent' (ramfs_dirent_ops)  or a
	                                      * `struct fdevfsdirent' (fdevfsdirent_ops). The 2 directory
	                                      * data sources `devfs_byname_tree'  and `devfs.rs_dat'  are
	                                      * enumerated in succession (in that same order) */
};
#define fdirent_isdevfs(self) ((self)->fd_ops == &fdevfsdirent_ops)
#define fdirent_asdevfs(self) container_of(self, struct fdevfsdirent, fdd_dirent)
#define fdirent_isramfs(self) ((self)->fd_ops == &ramfs_dirent_ops)
#define fdirent_asramfs(self) container_of(self, struct ramfs_dirent, rde_ent)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devfs_root_direnum_v_fini)(struct fdirenum *__restrict self) {
	struct devfs_root_direnum *me;
	me = (struct devfs_root_direnum *)self;
	axref_fini(&me->drd_next);
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fdirnode *
NOTHROW(KCALL devfs_root_direnum_v_getdir)(struct fdirenum *__restrict UNUSED(self)) {
	return mfile_asdir(incref(&devfs.rs_sup.fs_root.dn_node.fn_file));
}



PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct device *
NOTHROW(FCALL device_fixdeleted)(struct fdevfsdirent *__restrict self) {
	struct device *result = NULL;
	struct device *root;
	root = devfs_byname_tree;
	while (root) {
		int cmp = strcmpz(root->dv_dirent->fdd_dirent.fd_name,
		                  self->fdd_dirent.fd_name,
		                  self->fdd_dirent.fd_namelen);
		if (cmp >= 0) {
			result = root;
			root   = root->dv_byname_node.rb_lhs;
		} else {
			root = root->dv_byname_node.rb_rhs;
		}
	}
	return result;
}


/* Returns `NULL' if there is no next node */
PRIVATE WUNUSED NONNULL((1)) REF struct fdirent *KCALL
devfs_root_next(struct fdirent *__restrict self)
		THROWS(...) {
	REF struct fdirent *result = NULL;
	if (fdirent_isdevfs(self)) {
		struct fdevfsdirent *me;
		REF struct device *curr;
		me = fdirent_asdevfs(self);
		devfs_byname_read();
		curr = awref_get(&me->fdd_dev);
		if (curr == NULL) {
			struct device *next;
			next = device_fixdeleted(me);
			if (next == NULL)
				goto unlock_byname_and_return_first_ramfs;
			result = incref(&next->dv_dirent->fdd_dirent);
			devfs_byname_endread();
		} else {
			struct device *next;
			next = devfs_bynametree_nextnode(curr);
			if (next != NULL) {
				result = incref(&next->dv_dirent->fdd_dirent);
				devfs_byname_endread();
			} else {
				struct ramfs_dirent *first;
unlock_byname_and_return_first_ramfs:
				devfs_byname_endread();
				/* Return the first file from the ramfs portion. */
				shared_rwlock_read(&devfs.rs_dat.rdd_treelock);
				assertf(devfs.rs_dat.rdd_tree != RAMFS_DIRDATA_TREE_DELETED,
				        "The devfs root directory shouldn't be deletable");
				first = devfs.rs_dat.rdd_tree;
				if likely(first) {
					while (first->rde_treenode.rb_lhs)
						first = first->rde_treenode.rb_lhs;
					result = incref(&first->rde_ent);
				}
				shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
			}
		}
	} else {
		struct ramfs_dirent *me;
		assert(fdirent_isramfs(self));
		me = fdirent_asramfs(self);
		shared_rwlock_read(&devfs.rs_dat.rdd_treelock);
		COMPILER_READ_BARRIER();
		/* Check for special case: `self' was deleted. */
		if unlikely(me->rde_treenode.rb_lhs == RAMFS_DIRENT_TREENODE_DELETED) {
			/* Next node is the closest life entry with a name `>= me' */
			me = ramfs_dirent_fixdeleted(me, ramfs_super_asdir(&devfs));
		} else {
			assert(devfs.rs_dat.rdd_tree != RAMFS_DIRDATA_TREE_DELETED);
			/* Return a reference to the next node within the tree. */
			me = ramfs_direnttree_nextnode(me);
		}
		if (me != NULL)
			result = incref(&me->rde_ent);
		shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
	}
	return result;
}


PRIVATE NONNULL((1)) size_t KCALL
devfs_root_direnum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                             size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
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
		result = fdirenum_feedent(buf, bufsize, readdir_mode,
		                          ent->fd_ino,
		                          ent->fd_type,
		                          ent->fd_namelen,
		                          ent->fd_name);
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

PRIVATE WUNUSED REF struct fdirent *KCALL
devfs_root_first_ramfs_dirent(void) {
	REF struct fdirent *result = NULL;
	struct ramfs_dirent *ent;
	/* Start enumeration at the left-most node */
	shared_rwlock_read(&devfs.rs_dat.rdd_treelock);
	ent = devfs.rs_dat.rdd_tree;
	if likely(ent) {
		while (ent->rde_treenode.rb_lhs)
			ent = ent->rde_treenode.rb_lhs;
		result = incref(&ent->rde_ent);
	}
	shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
	return result;
}

PRIVATE WUNUSED REF struct fdirent *KCALL
devfs_root_first_dirent(void) {
	struct device *node;
	REF struct fdirent *firstent;
	devfs_byname_read();
	node = devfs_byname_tree;
	if likely(node) {
		while (node->dv_byname_node.rb_lhs)
			node = node->dv_byname_node.rb_lhs;
		firstent = incref(&node->dv_dirent->fdd_dirent);
		devfs_byname_endread();
	} else {
		devfs_byname_endread();
		firstent = devfs_root_first_ramfs_dirent();
	}
	return firstent;
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
		firstent = devfs_root_first_dirent();
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
	.deo_getdir  = &devfs_root_direnum_v_getdir,
	.deo_readdir = &devfs_root_direnum_v_readdir,
	.deo_seekdir = &devfs_root_direnum_v_seekdir,
};


PRIVATE NONNULL((1, 2)) void KCALL
devfs_root_v_enum(struct fdirnode *__restrict self,
                  struct fdirenum *__restrict result) {
	struct devfs_root_direnum *rt;
	REF struct fdirent *firstent;
	assert(self == &devfs.rs_sup.fs_root);
	(void)self;
	rt = (struct devfs_root_direnum *)result;
	firstent    = devfs_root_first_dirent();
	rt->drd_ops = &devfs_root_direnum_ops;
	axref_init(&rt->drd_next, firstent); /* Inherit reference. */
}


/* Special  handling  for  file  renaming  in  devfs, since
 * device files may not be moved out of the root directory. */
PRIVATE NONNULL((1, 2)) void KCALL
devfs_dirnode_v_rename(struct fdirnode *__restrict self,
                       struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DELETED) {
	if (info->frn_oldent->fd_ops != &ramfs_dirent_ops)
		THROW(E_FSERROR_READONLY);
	ramfs_dirnode_v_rename(self, info);
}


PUBLIC struct fdirnode_ops const devfs_dirnode_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &ramfs_dirnode_v_destroy,
			.mo_changed = &fnode_v_changed
		},
		.no_wrattr = &ramfs_dirnode_v_wrattr,
	},
	.dno_lookup       = &ramfs_dirnode_v_lookup,
	.dno_lookup_fnode = &ramfs_dirnode_v_lookup_fnode,
	.dno_enum         = &ramfs_dirnode_v_enum,
	.dno_mkfile       = &ramfs_dirnode_v_mkfile,
	.dno_unlink       = &ramfs_dirnode_v_unlink,
	.dno_rename       = &devfs_dirnode_v_rename,
};



PRIVATE NONNULL((1, 2)) void KCALL
devfs_root_v_mkfile(struct fdirnode *__restrict self,
                    struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION) {
	REF struct ramfs_dirent *new_dirent;
	REF struct fnode *new_node;
	assert(self == &devfs.rs_sup.fs_root);
	(void)self;

	/* Check check for already-exists. */
#ifndef __OPTIMIZE_SIZE__
	{
		REF struct fdirent *old_dirent;
again_lookup:
		old_dirent = devfs_root_v_lookup(self, &info->mkf_lookup_info);
		if unlikely(old_dirent) {
			REF struct fnode *oldnode;
			TRY {
				oldnode = fdirent_opennode(old_dirent, &devfs.rs_sup.fs_root);
			} EXCEPT {
				decref_unlikely(old_dirent);
				RETHROW();
			}
			if unlikely(!oldnode)
				goto again_lookup; /* Deleted */
			info->mkf_dent  = old_dirent; /* Inherit reference */
			info->mkf_rnode = oldnode;    /* Inherit reference */
			info->mkf_flags |= FMKFILE_F_EXISTS;
			return;
		}
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Check for special case: not allowed to hard-link device files.
	 * Every device file can only ever have a single directory entry! */
	if ((info->mkf_fmode & S_IFMT) == 0 && S_ISDEV(info->mkf_hrdlnk.hl_node->fn_mode) &&
	    info->mkf_hrdlnk.hl_node->fn_file.mf_ops != &ramfs_devnode_ops.dno_node.no_file)
		THROW(E_FSERROR_TOO_MANY_HARD_LINKS);

create_ramfs_file:
	/* Allocate the new file-node */
	new_node = ramfs_dirnode_mknode_frominfo(self, info);

	/* We need special operators for directories (because
	 * device files cannot not be  moved out of the  root
	 * directory) */
	if (S_ISDIR(info->mkf_fmode)) {
		assert(new_node->fn_file.mf_ops == &ramfs_dirnode_ops.dno_node.no_file);
		new_node->fn_file.mf_ops = &devfs_dirnode_ops.dno_node.no_file;
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
			if (info->mkf_hash == FLOOKUP_INFO_HASH_UNSET) {
				info->mkf_hash = fdirent_hash(new_dirent->rde_ent.fd_name,
				                              new_dirent->rde_ent.fd_namelen);
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
			shared_rwlock_write(&devfs.rs_dat.rdd_treelock);
			{
				struct ramfs_dirent *old_dirent;
				assert(devfs.rs_dat.rdd_tree != RAMFS_DIRDATA_TREE_DELETED);
				old_dirent = ramfs_direnttree_locate(devfs.rs_dat.rdd_tree,
				                                     new_dirent->rde_ent.fd_name,
				                                     new_dirent->rde_ent.fd_namelen);
				if (!old_dirent && (info->mkf_flags & FMKFILE_F_NOCASE) && devfs.rs_dat.rdd_tree) {
					/* Do a case-insensitive search */
					old_dirent = _ramfs_direnttree_caselocate(devfs.rs_dat.rdd_tree,
					                                          new_dirent->rde_ent.fd_name,
					                                          new_dirent->rde_ent.fd_namelen);
				}
				if unlikely(old_dirent) {
					/* Special case: file already exists. */
					incref(&old_dirent->rde_ent);
					shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
					kfree(new_dirent);
					decref_likely(&new_node->fn_file);
					info->mkf_dent  = &old_dirent->rde_ent;
					info->mkf_rnode = mfile_asnode(incref(&old_dirent->rde_node->fn_file));
					info->mkf_flags |= FMKFILE_F_EXISTS;
					return;
				}
			}

			/* Must also acquire a  lock to the  devfs by-name tree.  But since we  don't
			 * actually intend on modifying it (and only need to make sure that no device
			 * with  the same name is added while we're in here), it's OK to only acquire
			 * a read-lock. */
			if (!devfs_byname_tryread()) {
				shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
				devfs_byname_read();
				devfs_byname_endread();
				goto again_acquire_lock_for_insert;
			}

			/* Check if there's already a device with the same name. */
			{
				struct device *existing_device;
				existing_device = devfs_byname_locate(new_dirent->rde_ent.fd_name,
				                                      new_dirent->rde_ent.fd_namelen);
				if (!existing_device && (info->mkf_flags & FMKFILE_F_NOCASE)) {
					existing_device = devfs_byname_caselocate(new_dirent->rde_ent.fd_name,
					                                          new_dirent->rde_ent.fd_namelen);
				}
				if (existing_device) {
					if unlikely(!tryincref(existing_device)) {
						devfs_byname_removenode(existing_device);
						existing_device->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
					} else {
						/* Special case: file already exists. */
						shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
						info->mkf_dent = incref(&existing_device->dv_dirent->fdd_dirent);
						devfs_byname_endread();
						info->mkf_rnode = &existing_device->dv_devnode.dn_node;
						kfree(new_dirent);
						decref_likely(&new_node->fn_file);
						info->mkf_flags |= FMKFILE_F_EXISTS;
						return;
					}
				}
			}

			if ((info->mkf_fmode & S_IFMT) != 0) {
				/* At this point, the following fields of `new_node' are still unbound:
				 *  - new_node->fn_allnodes
				 *  - new_node->fn_supent */
				assert(!LIST_ISBOUND(new_node, fn_allnodes));
				assert(new_node->fn_supent.rb_lhs == FSUPER_NODES_DELETED);
				assert(!(new_node->fn_file.mf_flags & MFILE_FN_GLOBAL_REF));
				assert(new_node->fn_file.mf_flags & MFILE_F_PERSISTENT);
				assert(new_node->fn_file.mf_refcnt == 1);
				if (!fsuper_nodes_trywrite(&devfs.rs_sup)) {
					devfs_byname_endread();
					shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
					while (!fsuper_nodes_canwrite(&devfs.rs_sup))
						task_yield();
					goto again_acquire_lock_for_insert;
				}
				if (!fallnodes_tryacquire()) {
					fsuper_nodes_endwrite(&devfs.rs_sup);
					devfs_byname_endread();
					shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
					while (!fallnodes_available())
						task_yield();
					goto again_acquire_lock_for_insert;
				}
				new_node->fn_file.mf_flags |= MFILE_FN_GLOBAL_REF;
				new_node->fn_file.mf_refcnt += 1; /* For `MFILE_FN_GLOBAL_REF' */
				COMPILER_BARRIER();

				/* Make the newly created node globally visible. */
				fsuper_nodes_insert(&devfs.rs_sup, new_node);
				LIST_INSERT_HEAD(&fallnodes_list, new_node, fn_allnodes);

				/* Release locks. */
				fallnodes_release();
				fsuper_nodes_endwrite(&devfs.rs_sup);
			} else {
				/* Hard link -> increment the nlink counter */
				mfile_tslock_acquire(&new_node->fn_file);
				ATOMIC_INC(new_node->fn_nlink);
				mfile_tslock_release(&new_node->fn_file);
			}

			/* Construct missing references for `new_dirent' */
			incref(&new_node->fn_file); /* For `new_dirent->rde_node' (or `info->mkf_rnode', depending on view) */

			/* Insert the new directory entry. */
			ramfs_direnttree_insert(&devfs.rs_dat.rdd_tree, new_dirent); /* Inherit reference */

			/* And with that, the "file" has been created! */
			devfs_byname_endread();
			shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
		} EXCEPT {
			kfree(new_dirent);
			RETHROW();
		}
	} EXCEPT {
		decref_likely(&new_node->fn_file);
		RETHROW();
	}
	info->mkf_dent  = &new_dirent->rde_ent; /* Inherit reference */
	info->mkf_rnode = new_node;             /* Inherit reference */
}


PRIVATE NONNULL((1, 2, 3)) void KCALL
devfs_root_v_unlink(struct fdirnode *__restrict self,
                    struct fdirent *__restrict entry,
                    struct fnode *__restrict file)
		THROWS(E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY, E_FSERROR_DELETED) {
	assert(self == &devfs.rs_sup.fs_root);
	(void)self;

	/* Check for device files. */
	assert(entry->fd_ops == &ramfs_dirent_ops ||
	       entry->fd_ops == &fdevfsdirent_ops);
	if (entry->fd_ops == &fdevfsdirent_ops) {
		struct fdevfsdirent *real_entry;
		struct device *real_file;
		real_entry = container_of(entry, struct fdevfsdirent, fdd_dirent);
		real_file  = container_of(file, struct device, dv_devnode.dn_node);
		if (real_file->dv_byname_node.rb_lhs == DEVICE_BYNAME_DELETED)
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		devfs_byname_write();
		COMPILER_READ_BARRIER();
		if (real_file->dv_dirent != real_entry || /* File was renamed */
		    real_file->dv_byname_node.rb_lhs == DEVICE_BYNAME_DELETED /* File was deleted */) {
			devfs_byname_endwrite();
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		}
		devfs_byname_removenode(real_file);
		real_file->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
		assert(awref_ptr(&real_entry->fdd_dev) == real_file);
		awref_clear(&real_entry->fdd_dev); /* Disconnect the directory entry from the device file. */
		devfs_byname_endwrite();

#if 0 /* No: user-space shouldn't have this power; Only ~true~ hardware device-disappeared,
       *     as well as driver-unload operations should be able to do something like  this! */
		device_delete(real_file);
#endif
	} else {
		ramfs_dirnode_v_unlink(self, entry, file);
	}
}




PRIVATE NONNULL((1, 2)) void KCALL
devfs_root_v_rename(struct fdirnode *__restrict self,
                    struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DELETED) {
	assert(self == &devfs.rs_sup.fs_root);
	assert(fdirent_isdevfs(info->frn_oldent) ||
	       fdirent_isramfs(info->frn_oldent));
	if (fdirent_isdevfs(info->frn_oldent)) {
		/* Rename device files */
		REF struct fdevfsdirent *old_dirent;
		REF struct fdevfsdirent *new_dirent;
		struct device *devfile;
		assert(info->frn_olddir == &devfs.rs_sup.fs_root);
		assert(fnode_isdevice(info->frn_file));
		devfile    = fnode_asdevice(info->frn_file);
		new_dirent = (REF struct fdevfsdirent *)kmalloc(offsetof(struct fdevfsdirent, fdd_dirent.fd_name) +
		                                                (info->frn_namelen + 1) * sizeof(char),
		                                                GFP_NORMAL);
		TRY {
			/* Fill in the new directory entry. */
			*(char *)mempcpy(new_dirent->fdd_dirent.fd_name, info->frn_name,
			                 info->frn_namelen, sizeof(char)) = '\0';

			/* Fill in other fields of the new directory entry. */
			if (info->frn_hash == FLOOKUP_INFO_HASH_UNSET) {
				info->frn_hash = fdirent_hash(new_dirent->fdd_dirent.fd_name,
				                              new_dirent->fdd_dirent.fd_namelen);
			}
			new_dirent->fdd_dirent.fd_refcnt  = 2; /* +1: info->mkf_dent, +1: devfile->dv_dirent */
			new_dirent->fdd_dirent.fd_ops     = &ramfs_dirent_ops;
			new_dirent->fdd_dirent.fd_hash    = info->frn_hash;
			new_dirent->fdd_dirent.fd_ino     = devfile->dv_devnode.dn_node.fn_ino; /* INO numbers are constant here. */
			new_dirent->fdd_dirent.fd_namelen = info->frn_namelen;
			new_dirent->fdd_dirent.fd_type    = IFTODT(devfile->dv_devnode.dn_node.fn_mode);
			awref_init(&new_dirent->fdd_dev, devfile);

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
		            &old_dirent->fdd_dirent != info->frn_oldent) {                  /* Renamed */
			devfs_byname_endwrite();
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		}

		/* Check if another device file with the same name already exists. */
		{
			struct device *existing_device;
			existing_device = devfs_byname_locate(new_dirent->fdd_dirent.fd_name,
			                                      new_dirent->fdd_dirent.fd_namelen);
			if (!existing_device && (info->frn_flags & FS_MODE_FDOSPATH)) {
				existing_device = devfs_byname_caselocate(new_dirent->fdd_dirent.fd_name,
				                                          new_dirent->fdd_dirent.fd_namelen);
			}
			if (existing_device) {
				if (wasdestroyed(existing_device)) {
					devfs_byname_removenode(existing_device);
					existing_device->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
				} else {
					devfs_byname_endwrite();
					kfree(new_dirent);
					THROW(E_FSERROR_FILE_ALREADY_EXISTS);
				}
			}
		}

		/* Remove the device file within the context of its old name. */
		devfs_byname_removenode(devfile);

		/* Set the new filename. */
		devfile->dv_dirent = new_dirent; /* Inherit reference (x2) */

		/* (Re-)insert the device file into the by-name tree (using the new filename) */
		devfs_byname_insert(devfile);

		/* Release lock. */
		devfs_byname_endwrite();

		/* Clear the back-link from `old_dirent' to the device file in question.
		 * As far as the directory entry  should be concerned, it's device  file
		 * has been deleted. */
		awref_clear(&old_dirent->fdd_dev);

		/* Inherited  from  `devfile->dv_dirent'  (nokill  because
		 * the caller still has a reference in `info->frn_oldent') */
		decref_nokill(old_dirent);

		/* Write-back results. */
		info->frn_dent = &new_dirent->fdd_dirent; /* Inherit reference */
	} else {
		struct ramfs_dirent *new_dirent;
		struct ramfs_dirnode *olddir = (struct ramfs_dirnode *)info->frn_olddir;
		struct ramfs_dirent *old_dirent;
		assert(info->frn_oldent->fd_ops == &ramfs_dirent_ops);

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
				                              new_dirent->rde_ent.fd_namelen);
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
			shared_rwlock_write(&devfs.rs_dat.rdd_treelock);
			if (!devfs_byname_tryread()) {
				shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
				devfs_byname_read();
				devfs_byname_endread();
				goto again_acquire_locks;
			}
		} EXCEPT {
			kfree(new_dirent);
			RETHROW();
		}
		assert(devfs.rs_dat.rdd_tree != RAMFS_DIRDATA_TREE_DELETED);

		/* Check if the file already exists. */
		if (ramfs_direnttree_locate(devfs.rs_dat.rdd_tree,
		                            new_dirent->rde_ent.fd_name,
		                            new_dirent->rde_ent.fd_namelen) ||
		    ((info->frn_flags & FS_MODE_FDOSPATH) && devfs.rs_dat.rdd_tree &&
		     _ramfs_direnttree_caselocate(devfs.rs_dat.rdd_tree,
		                                  new_dirent->rde_ent.fd_name,
		                                  new_dirent->rde_ent.fd_namelen))) {
unlock_and_throw_file_already_exists_error:
			devfs_byname_endread();
			shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
			kfree(new_dirent);
			THROW(E_FSERROR_FILE_ALREADY_EXISTS);
		}
		{
			struct device *existing_device;
			existing_device = devfs_byname_locate(new_dirent->rde_ent.fd_name,
			                                      new_dirent->rde_ent.fd_namelen);
			if (!existing_device && (info->frn_flags & FS_MODE_FDOSPATH)) {
				existing_device = devfs_byname_caselocate(new_dirent->rde_ent.fd_name,
				                                          new_dirent->rde_ent.fd_namelen);
			}
			if (existing_device) {
				if (!wasdestroyed(existing_device))
					goto unlock_and_throw_file_already_exists_error;
				/* Unlink destroyed device. */
				devfs_byname_removenode(existing_device);
				existing_device->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
			}
		}


		/* Acquire a lock to the old directory. */
		if (ramfs_super_asdir(&devfs) != olddir) {
			if (!shared_rwlock_trywrite(&olddir->rdn_dat.rdd_treelock)) {
				devfs_byname_endread();
				shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
				TRY {
					shared_rwlock_write(&olddir->rdn_dat.rdd_treelock);
				} EXCEPT {
					kfree(new_dirent);
					RETHROW();
				}
				shared_rwlock_endwrite(&olddir->rdn_dat.rdd_treelock);
				goto again_acquire_locks;
			}

			/* Check if the old directory has already been deleted. */
			if unlikely(olddir->rdn_dat.rdd_tree == RAMFS_DIRDATA_TREE_DELETED) {
				devfs_byname_endread();
				shared_rwlock_endwrite(&olddir->rdn_dat.rdd_treelock);
				shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
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
				shared_rwlock_endwrite(&olddir->rdn_dat.rdd_treelock);
			devfs_byname_endread();
			shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);
			kfree(new_dirent);
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		}

		/* Remove `old_dirent' from its tree. */
		ramfs_direnttree_removenode(&olddir->rdn_dat.rdd_tree, old_dirent);
		old_dirent->rde_treenode.rb_lhs = RAMFS_DIRENT_TREENODE_DELETED; /* Mark as deleted. */

		/* Insert the new directory entry into the new folder. */
		ramfs_direnttree_insert(&devfs.rs_dat.rdd_tree, new_dirent);

		/* For `new_dirent->rde_node' */
		incref(&info->frn_file->fn_file);

		/* Release locks */
		if (ramfs_super_asdir(&devfs) != olddir)
			shared_rwlock_endwrite(&olddir->rdn_dat.rdd_treelock);
		devfs_byname_endread();
		shared_rwlock_endwrite(&devfs.rs_dat.rdd_treelock);

		/* Inherited   from   `olddir->rdn_dat.rdd_tree'
		 * (nokill because caller still has a reference) */
		decref_nokill(old_dirent);

		/* Write-back results. */
		info->frn_dent = &new_dirent->rde_ent; /* Inherit reference */
	}
}


PRIVATE struct fsuper_ops const devfs_ops = {
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy = (void (KCALL *)(struct mfile *__restrict))(void *)(uintptr_t)-1, /* Must never be called */
				.mo_changed = &fnode_v_changed,
			},
			.no_wrattr = &fnode_v_wrattr_noop,
		},
		.dno_lookup       = &devfs_root_v_lookup,
		.dno_lookup_fnode = &devfs_root_v_lookup_fnode,
		.dno_enum         = &devfs_root_v_enum,
		.dno_mkfile       = &devfs_root_v_mkfile,
		.dno_unlink       = &devfs_root_v_unlink,
		.dno_rename       = &devfs_root_v_rename,
	},
};

/* The /dev/ filesystem superblock */
extern struct fnode _devfs__fs_nodes__INIT[];
PUBLIC struct ramfs_super devfs = {
	.rs_sup = {
		.fs_nodes           = _devfs__fs_nodes__INIT,
		.fs_nodeslock       = ATOMIC_RWLOCK_INIT,
		.fs_nodeslockops    = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_nodeslockops),
		.fs_mounts          = LIST_HEAD_INITIALIZER(devfs.rs_sup.fs_mounts),
		.fs_mountslock      = ATOMIC_RWLOCK_INIT,
		.fs_mountslockops   = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_mountslockops),
		.fs_sys             = &devfs_filesys,
		.fs_dev             = NULL,
		.fs_feat = {
			.sf_filesize_max       = (pos_t)-1,
			.sf_uid_max            = (uid_t)-1,
			.sf_gid_max            = (gid_t)-1,
			.sf_symlink_max        = (pos_t)-1,
			.sf_link_max           = (nlink_t)-1,
			.sf_magic              = DEVFS_SUPER_MAGIC,
			.sf_rec_incr_xfer_size = PAGESIZE,
			.sf_rec_max_xfer_size  = PAGESIZE,
			.sf_rec_min_xfer_size  = PAGESIZE,
			.sf_rec_xfer_align     = PAGESIZE,
			.sf_name_max           = (u16)-1,
			.sf_filesizebits       = BITSOF(pos_t),
		},
		.fs_changednodes_lock = ATOMIC_LOCK_INIT,
		.fs_changednodes_lops = SLIST_HEAD_INITIALIZER(devfs.rs_sup.fs_changednodes_lops),
		.fs_changednodes      = LIST_HEAD_INITIALIZER(devfs.rs_sup.fs_changednodes),
		.fs_changedsuper      = LIST_ENTRY_UNBOUND_INITIALIZER,
		.fs_root = {
			.dn_node = {
				.fn_file = {
					MFILE_INIT_mf_refcnt(2), /* +1: devfs, +1: MFILE_FN_GLOBAL_REF */
					MFILE_INIT_mf_ops(&devfs_ops.so_fdir.dno_node.no_file),
					MFILE_INIT_mf_lock,
					MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_initdone,
					MFILE_INIT_mf_lockops,
					MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
					MFILE_INIT_mf_blockshift(PAGESHIFT),
					MFILE_INIT_mf_flags(MFILE_FS_NOSUID | MFILE_FN_GLOBAL_REF | MFILE_FS_NOEXEC |
					                    MFILE_F_NOATIME | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
					                    MFILE_F_NOMTIME | MFILE_F_PERSISTENT | MFILE_F_FIXEDFILESIZE |
					                    MFILE_FM_ATTRREADONLY),
					MFILE_INIT_mf_trunclock,
					MFILE_INIT_mf_filesize((uint64_t)-1),
					/* TODO: Have an initializer that copies `boottime' into these 3! */
					MFILE_INIT_mf_atime(0, 0),
					MFILE_INIT_mf_mtime(0, 0),
					MFILE_INIT_mf_ctime(0, 0),
				},
				FNODE_INIT_fn_nlink(1),
				FNODE_INIT_fn_mode(S_IFDIR | 0755),
				FNODE_INIT_fn_uid(0), /* root */
				FNODE_INIT_fn_gid(0), /* root */
				FNODE_INIT_fn_ino(0), /* Fixed INO for root directory */
				FNODE_INIT_fn_super(&devfs.rs_sup),
				FNODE_INIT_fn_changed,
				FNODE_INIT_fn_supent,
				FNODE_INIT_fn_allsuper_EX({ NULL, &fallsuper_list.lh_first }),
			},
			.dn_parent = NULL,
		},
	},
	.rs_dat = {
		/* TODO */
	},
};


/* Default operators for `struct device_ops' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC device_v_destroy_postlop)(struct postlockop *__restrict self) {
	struct device *me;
	DEFINE_PUBLIC_SYMBOL(devfs_rootdir, &devfs.rs_sup.fs_root, sizeof(struct ramfs_dirnode));
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_plop);
	decref_likely(me->dv_dirent);
	fdevnode_v_destroy(&me->dv_devnode.dn_node.fn_file);
}
PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC device_v_destroy_lop)(struct lockop *__restrict self) {
	struct device *me;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_lop);
	if (me->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED)
		devfs_byname_removenode(me);
	me->dv_devnode.dn_node.fn_file._mf_plop.plo_func = &device_v_destroy_postlop;
	return &me->dv_devnode.dn_node.fn_file._mf_plop;
}


/* Destructor (asynchronously  removes  itself  from
 * `devfs_byname_tree' and does `decref(dv_dirent)') */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL device_v_destroy)(struct mfile *__restrict self) {
	struct device *me;
	me = mfile_asdevice(self);
	assert(me->dv_devnode.dn_node.fn_super == &devfs.rs_sup);
	assert(me->dv_dirent);

	/* Drop reference to associated driver. */
	decref_unlikely(me->dv_driver);

	/* Clear the weak reference held by our /dev/-directory entry. */
	awref_clear(&me->dv_dirent->fdd_dev);

	/* Must remove `me' from `devfs_byname_tree' */
	if (ATOMIC_READ(me->dv_byname_node.rb_lhs) != DEVICE_BYNAME_DELETED) {
		if (devfs_byname_trywrite()) {
			COMPILER_READ_BARRIER();
			if (me->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED)
				devfs_byname_removenode(me);
			devfs_byname_endwrite();
		} else {
			/* Use a lock-op to do the removal */
			me->dv_devnode.dn_node.fn_file._mf_lop.lo_func = &device_v_destroy_lop;
			lockop_enqueue(&devfs_byname_lops, &me->dv_devnode.dn_node.fn_file._mf_lop);
			_devfs_byname_reap();
			return;
		}
	}

	decref_likely(me->dv_dirent);
	fdevnode_v_destroy(&me->dv_devnode.dn_node.fn_file);
}





/* By-name lookup of devices in /dev/ */
PUBLIC struct shared_rwlock devfs_byname_lock = SHARED_RWLOCK_INIT;
PUBLIC struct lockop_slist devfs_byname_lops  = SLIST_HEAD_INITIALIZER(devfs_byname_lops);
extern struct device _devfs_byname_tree__INIT[];
PUBLIC RBTREE_ROOT(device) devfs_byname_tree = _devfs_byname_tree__INIT;

/* Lock accessor helpers for `devfs_byname_lock' and `devfs_byname_tree' */
PUBLIC NOBLOCK void KCALL _devfs_byname_reap(void) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      (&devfs_byname_lops)
#define __LOCAL_trylock() devfs_byname_trywrite()
#define __LOCAL_unlock()  _devfs_byname_endwrite()
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
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
PUBLIC NONNULL((1)) unsigned int FCALL
device_tryregister(struct device *__restrict self)
		THROWS(E_WOULDBLOCK) {
	unsigned int result;
	assert(self->dv_devnode.dn_node.fn_ino ==
	       devfs_devnode_makeino(self->dv_devnode.dn_node.fn_mode,
	                             self->dv_devnode.dn_devno));

	/* Acquire all required locks. */
again:
	devfs_byname_write();
	if (!fsuper_nodes_trywrite(&devfs.rs_sup)) {
		devfs_byname_endwrite();
		while (!fsuper_nodes_canwrite(&devfs.rs_sup))
			task_yield();
		goto again;
	}
	if (!fallnodes_tryacquire()) {
		fsuper_nodes_endwrite(&devfs.rs_sup);
		devfs_byname_endwrite();
		while (!fallnodes_available())
			task_yield();
		goto again;
	}
	if (!shared_rwlock_tryread(&devfs.rs_dat.rdd_treelock)) {
		fallnodes_release();
		fsuper_nodes_endwrite(&devfs.rs_sup);
		devfs_byname_endwrite();
		shared_rwlock_read(&devfs.rs_dat.rdd_treelock);
		shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
		goto again;
	}

	/* With all required locks held, check if this device already exists. */
	{
		struct device *existing;
		existing = devfs_byname_locate(self->dv_dirent->fdd_dirent.fd_name,
		                               self->dv_dirent->fdd_dirent.fd_namelen);
		if (existing != NULL) {
			if (!wasdestroyed(existing)) {
				result = DEVICE_TRYREGISTER_EXISTS_NAME;
				goto done;
			}

			/* Unlink destroyed device. */
			devfs_byname_removenode(existing);
			existing->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
		}
	}

	/* Also check if a custom file with the same name exists within /dev/ */
	if (ramfs_direnttree_locate(devfs.rs_dat.rdd_tree,
	                            self->dv_dirent->fdd_dirent.fd_name,
	                            self->dv_dirent->fdd_dirent.fd_namelen) != NULL) {
		result = DEVICE_TRYREGISTER_EXISTS_NAME;
		goto done;
	}

	/* Also check in devfs's INode tree. */
	{
		struct fnode *existing;
		assert(devfs.rs_sup.fs_nodes != FSUPER_NODES_DELETED);
		existing = fsuper_nodes_locate(&devfs.rs_sup, self->dv_devnode.dn_node.fn_ino);
		if (existing != NULL) {
			if (!wasdestroyed(&existing->fn_file)) {
				result = DEVICE_TRYREGISTER_EXISTS_DEVNO;
				goto done;
			}
			/* Unlink destroyed device. */
			fsuper_nodes_removenode(&devfs.rs_sup, existing);
			ATOMIC_WRITE(existing->fn_supent.rb_lhs, FSUPER_NODES_DELETED);
		}
	}

	/* Doesn't exist yet -> register our new one! */
	fsuper_nodes_insert(&devfs.rs_sup, &self->dv_devnode.dn_node);
	devfs_byname_insert(self);
	LIST_INSERT_HEAD(&fallnodes_list, &self->dv_devnode.dn_node, fn_allnodes);

	/* Indicate success */
	result = DEVICE_TRYREGISTER_SUCCESS;

done:
	/* Release all locks */
	COMPILER_BARRIER();
	shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
	fallnodes_release();
	fsuper_nodes_endwrite(&devfs.rs_sup);
	devfs_byname_endwrite();
	return result;
}


/* Same as `device_tryregister()', but automatically handle duplicate dev_t and names:
 *  - If  the device's name already exists, mark the device's file as having been deleted,
 *    and don't add it to the by-name tree. As such, the device won't appear in /dev/, and
 *    accessing it will only be possible by creating a device node using its dev_t
 *  - If the device's `dev_t dn_devno'  (read: `ino_t fn_ino') already exists,  increment
 *    the device number by 1 and re-generate the `fn_ino', then try to add it once again.
 *
 * This function initializes (before making `self' globally visible):
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->dv_byname_node */
PUBLIC NONNULL((1)) void FCALL
device_register(struct device *__restrict self)
		THROWS(E_WOULDBLOCK) {
	assert(self->dv_devnode.dn_node.fn_ino ==
	       devfs_devnode_makeino(self->dv_devnode.dn_node.fn_mode,
	                             self->dv_devnode.dn_devno));
	/* Acquire all required locks. */
again:
	devfs_byname_write();
	if (!fsuper_nodes_trywrite(&devfs.rs_sup)) {
		devfs_byname_endwrite();
		while (!fsuper_nodes_canwrite(&devfs.rs_sup))
			task_yield();
		goto again;
	}
	if (!fallnodes_tryacquire()) {
		fsuper_nodes_endwrite(&devfs.rs_sup);
		devfs_byname_endwrite();
		while (!fallnodes_available())
			task_yield();
		goto again;
	}
	if (!shared_rwlock_tryread(&devfs.rs_dat.rdd_treelock)) {
		fallnodes_release();
		fsuper_nodes_endwrite(&devfs.rs_sup);
		devfs_byname_endwrite();
		shared_rwlock_read(&devfs.rs_dat.rdd_treelock);
		shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
		goto again;
	}

	/* With all required locks held, check if this device already exists. */
	{
		struct device *existing;
		existing = devfs_byname_locate(self->dv_dirent->fdd_dirent.fd_name,
		                               self->dv_dirent->fdd_dirent.fd_namelen);
		if (existing != NULL) {
			if (!wasdestroyed(existing)) {
				self->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
				goto done_add2byname;
			}
			/* Unlink destroyed device. */
			devfs_byname_removenode(existing);
			existing->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
		}
	}

	/* Also check if a custom file with the same name exists within /dev/ */
	if (ramfs_direnttree_locate(devfs.rs_dat.rdd_tree,
	                            self->dv_dirent->fdd_dirent.fd_name,
	                            self->dv_dirent->fdd_dirent.fd_namelen) != NULL) {
		self->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
		goto done_add2byname;
	}

	/* Add to the by-name tree. */
	devfs_byname_insert(self);
done_add2byname:

	/* Try to add the device to the nodes tree. */
	for (;;) {
		struct fnode *existing;
		assert(devfs.rs_sup.fs_nodes != FSUPER_NODES_DELETED);
		existing = fsuper_nodes_locate(&devfs.rs_sup, self->dv_devnode.dn_node.fn_ino);
		if likely(!existing)
			break;
		if (wasdestroyed(&existing->fn_file)) {
			/* Unlink destroyed device. */
			fsuper_nodes_removenode(&devfs.rs_sup, existing);
			ATOMIC_WRITE(existing->fn_supent.rb_lhs, FSUPER_NODES_DELETED);
			break;
		}

		/* Create a new device number */
		++self->dv_devnode.dn_devno;
		self->dv_devnode.dn_node.fn_ino = devfs_devnode_makeino(self->dv_devnode.dn_node.fn_mode,
		                                                        self->dv_devnode.dn_devno);
	}
	/* Add to the inode tree (for lookup by dev_t) */
	fsuper_nodes_insert(&devfs.rs_sup, &self->dv_devnode.dn_node);

	/* Insert into the all-nodes list. */
	LIST_INSERT_HEAD(&fallnodes_list, &self->dv_devnode.dn_node, fn_allnodes);

done:
	/* Release all locks */
	COMPILER_BARRIER();
	shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
	fallnodes_release();
	fsuper_nodes_endwrite(&devfs.rs_sup);
	devfs_byname_endwrite();
}










/************************************************************************/
/* Helpers for `device_delete()'                                        */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_allnodes_postlop)(struct postlockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_plop);

	/* At this point, all of the global hooks of `me' have been  removed.
	 * The rest of the deletion work relates only to the underlying mfile
	 * and includes stuff  like anonymizing any  bound mem-parts  (should
	 * the device include direct mmap capabilities) */
	mfile_delete_impl(&me->dv_devnode.dn_node.fn_file); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC device_delete_remove_from_allnodes_lop)(struct lockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_lop);
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(&me->dv_devnode.dn_node, fn_allnodes))
		LIST_UNBIND(&me->dv_devnode.dn_node, fn_allnodes);
	me->dv_devnode.dn_node.fn_file._mf_plop.plo_func = &device_delete_remove_from_allnodes_postlop; /* Inherit reference */
	return &me->dv_devnode.dn_node.fn_file._mf_plop;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_changed_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                             struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs.rs_sup);
	(void)obj;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_fsuperplop);

	/* Remove from `fallnodes_list'. */
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(&me->dv_devnode.dn_node, fn_allnodes)) {
		COMPILER_READ_BARRIER();
		if (fallnodes_tryacquire()) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(&me->dv_devnode.dn_node, fn_allnodes))
				LIST_UNBIND(&me->dv_devnode.dn_node, fn_allnodes);
			COMPILER_READ_BARRIER();
			fallnodes_release();
		} else {
			me->dv_devnode.dn_node.fn_file._mf_lop.lo_func = &device_delete_remove_from_allnodes_lop; /* Inherit reference */
			lockop_enqueue(&fallnodes_lockops, &me->dv_devnode.dn_node.fn_file._mf_lop);
			_fallnodes_reap();
			return;
		}
	}
	device_delete_remove_from_allnodes_postlop(&me->dv_devnode.dn_node.fn_file._mf_plop); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC device_delete_remove_from_changed_lop)(Toblockop(fsuper) *__restrict self,
                                                         struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs.rs_sup);
	(void)obj;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_fsuperlop);
	if (LIST_ISBOUND(&me->dv_devnode.dn_node, fn_changed)) {
		LIST_UNBIND(&me->dv_devnode.dn_node, fn_changed);
		decref_nokill(me); /* Reference from the `fn_changed' list. */
	}

	me->dv_devnode.dn_node.fn_file._mf_fsuperplop.oplo_func = &device_delete_remove_from_changed_postlop; /* Inherit reference */
	return &me->dv_devnode.dn_node.fn_file._mf_fsuperplop;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_byino_postlop)(Tobpostlockop(fsuper) *__restrict self,
                                                           struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs.rs_sup);
	(void)obj;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_fsuperplop);

	/* Remove from `devfs.rs_sup.fs_changednodes'. */
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(&me->dv_devnode.dn_node, fn_changed)) {
		COMPILER_READ_BARRIER();
		if (fsuper_changednodes_tryacquire(&devfs.rs_sup)) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(&me->dv_devnode.dn_node, fn_changed)) {
				LIST_UNBIND(&me->dv_devnode.dn_node, fn_changed);
				decref_nokill(me); /* Reference from the `fn_changed' list. */
			}
			COMPILER_READ_BARRIER();
			fsuper_changednodes_release(&devfs.rs_sup);
		} else {
			me->dv_devnode.dn_node.fn_file._mf_fsuperlop.olo_func = &device_delete_remove_from_changed_lop; /* Inherit reference */
			oblockop_enqueue(&devfs.rs_sup.fs_changednodes_lops, &me->dv_devnode.dn_node.fn_file._mf_fsuperlop);
			_fsuper_changednodes_reap(&devfs.rs_sup);
			return;
		}
	}

	device_delete_remove_from_changed_postlop(&me->dv_devnode.dn_node.fn_file._mf_fsuperplop,
	                                          &devfs.rs_sup); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(fsuper) *
NOTHROW(LOCKOP_CC device_delete_remove_from_byino_lop)(Toblockop(fsuper) *__restrict self,
                                                       struct fsuper *__restrict obj) {
	REF struct device *me;
	assert(obj == &devfs.rs_sup);
	(void)obj;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_fsuperlop);
	COMPILER_READ_BARRIER();
	if (me->dv_devnode.dn_node.fn_supent.rb_lhs != FSUPER_NODES_DELETED) {
		fsuper_nodes_removenode(&devfs.rs_sup, &me->dv_devnode.dn_node);
		ATOMIC_WRITE(me->dv_devnode.dn_node.fn_supent.rb_lhs, FSUPER_NODES_DELETED);
	}
	me->dv_devnode.dn_node.fn_file._mf_fsuperplop.oplo_func = &device_delete_remove_from_byino_postlop; /* Inherit reference */
	return &me->dv_devnode.dn_node.fn_file._mf_fsuperplop;
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC device_delete_remove_from_byname_postlop)(struct postlockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_plop);

	/* Remove from the devfs's INode tree. */
	if (ATOMIC_READ(me->dv_devnode.dn_node.fn_supent.rb_lhs) != FSUPER_NODES_DELETED) {
		if (fsuper_nodes_trywrite(&devfs.rs_sup)) {
			COMPILER_READ_BARRIER();
			if (me->dv_devnode.dn_node.fn_supent.rb_lhs != FSUPER_NODES_DELETED) {
				fsuper_nodes_removenode(&devfs.rs_sup, &me->dv_devnode.dn_node);
				ATOMIC_WRITE(me->dv_devnode.dn_node.fn_supent.rb_lhs, FSUPER_NODES_DELETED);
			}
			fsuper_nodes_endwrite(&devfs.rs_sup);
		} else {
			me->dv_devnode.dn_node.fn_file._mf_fsuperlop.olo_func = &device_delete_remove_from_byino_lop; /* Inherit reference */
			oblockop_enqueue(&devfs.rs_sup.fs_nodeslockops, &me->dv_devnode.dn_node.fn_file._mf_fsuperlop);
			_fsuper_nodes_reap(&devfs.rs_sup);
			return;
		}
	}
	device_delete_remove_from_byino_postlop(&me->dv_devnode.dn_node.fn_file._mf_fsuperplop,
	                                        &devfs.rs_sup); /* Inherit reference */
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC device_delete_remove_from_byname_lop)(struct lockop *__restrict self) {
	REF struct device *me;
	me = container_of(self, struct device, dv_devnode.dn_node.fn_file._mf_lop);
	COMPILER_READ_BARRIER();
	if (me->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED) {
		devfs_byname_removenode(me);
		me->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
	}
	me->dv_devnode.dn_node.fn_file._mf_plop.plo_func = &device_delete_remove_from_byname_postlop; /* Inherit reference */
	return &me->dv_devnode.dn_node.fn_file._mf_plop;
}


/* Unregister a given device node from /dev/ and devfs's inode tree, and proceed
 * to call `mfile_delete()'. This process is done asynchronously and can be used
 * to  delete device files  in situations where  devices disappear, or something
 * similar happened. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL device_delete)(struct device *__restrict self) {
	uintptr_t old_flags;
	assert(self->dv_devnode.dn_node.fn_super == &devfs.rs_sup);

	/* Delete global reference to the device. */
	if (ATOMIC_FETCHAND(self->dv_devnode.dn_node.fn_file.mf_flags, ~(MFILE_FN_GLOBAL_REF |
	                                                                 MFILE_F_PERSISTENT)) &
	    MFILE_FN_GLOBAL_REF)
		decref_nokill(&self->dv_devnode.dn_node.fn_file);

	/* Mark the device as deleted (and make available use of the file fields) */
	mfile_tslock_acquire(&self->dv_devnode.dn_node.fn_file);
	old_flags = ATOMIC_FETCHOR(self->dv_devnode.dn_node.fn_file.mf_flags,
	                           MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_F_NOMTIME |
	                           MFILE_F_CHANGED | MFILE_F_ATTRCHANGED | MFILE_F_FIXEDFILESIZE |
	                           MFILE_FM_ATTRREADONLY | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
	                           MFILE_FS_NOSUID | MFILE_FS_NOEXEC | MFILE_F_READONLY);
	if (old_flags & MFILE_F_PERSISTENT)
		ATOMIC_AND(self->dv_devnode.dn_node.fn_file.mf_flags, ~MFILE_F_PERSISTENT); /* Also clear the PERSISTENT flag */
	mfile_tslock_release(&self->dv_devnode.dn_node.fn_file);

	if (old_flags & MFILE_F_DELETED)
		return; /* Already deleted, or deletion already in progress. */

	incref(self);

	/* Remove from the /dev/ filesystem */
	if (ATOMIC_READ(self->dv_byname_node.rb_lhs) != DEVICE_BYNAME_DELETED) {
		if (devfs_byname_trywrite()) {
			COMPILER_READ_BARRIER();
			if (self->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED) {
				devfs_byname_removenode(self);
				self->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
			}
			devfs_byname_endwrite();
		} else {
			self->dv_devnode.dn_node.fn_file._mf_lop.lo_func = &device_delete_remove_from_byname_lop; /* Inherit reference */
			lockop_enqueue(&devfs_byname_lops, &self->dv_devnode.dn_node.fn_file._mf_lop);
			_devfs_byname_reap();
			return;
		}
	}
	device_delete_remove_from_byname_postlop(&self->dv_devnode.dn_node.fn_file._mf_plop); /* Inherit reference */
}




/************************************************************************/
/* Device lookup                                                        */
/************************************************************************/

/* Lookup a device within devfs, given its INode number.
 * @return: NULL: No such device. */
PUBLIC WUNUSED REF struct device *FCALL
device_lookup_byino(ino_t ino) THROWS(E_WOULDBLOCK) {
	REF struct device *result;
	fsuper_nodes_read(&devfs.rs_sup);
	result = (REF struct device *)fsuper_nodes_locate(&devfs.rs_sup, ino);
	if (result && !tryincref(result))
		result = NULL; /* Device already destroyed */
	fsuper_nodes_endread(&devfs.rs_sup);
	return result;
}

/* Lookup a device within devfs, given its name (and possibly type).
 * @param: name:    NUL-terminated device name string.
 * @param: st_mode: Either `0', `S_IFCHR' or `S_IFBLK'
 * @return: NULL: No such device. */
PUBLIC WUNUSED REF struct device *FCALL
device_lookup_byname(USER CHECKED char const *name,
                     size_t namelen, mode_t st_mode)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	REF struct device *result;
	if unlikely(namelen > UINT16_MAX)
		return NULL; /* No device could have this long a name. */
	devfs_byname_read();
	TRY {
		result = devfs_byname_locate(name, namelen);
	} EXCEPT {
		devfs_byname_endread();
		RETHROW();
	}
	if (result && st_mode != 0 &&
	    (result->dv_devnode.dn_node.fn_mode & S_IFMT) != (st_mode & S_IFMT))
		result = NULL; /* Wrong mode */
	if (result && !tryincref(result))
		result = NULL; /* Device already destroyed */
	devfs_byname_endread();
	return result;
}


PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) struct blkdev *
NOTHROW(FCALL devfs_find_partguid)(struct fnode *__restrict root,
                                   guid_t const *__restrict guid,
                                   struct blkdev *result) {
again:
	if (fnode_isblkpart(root)) {
		struct blkdev *dev;
		dev = fnode_asblkdev(root);
		if (memcmp(&dev->bd_partinfo.bp_efi_partguid, guid, sizeof(guid_t)) == 0)
			result = result ? (struct blkdev *)-1 : dev;
	}
	if (root->fn_supent.rb_lhs) {
		if (root->fn_supent.rb_rhs)
			result = devfs_find_partguid(root->fn_supent.rb_rhs, guid, result);
		root = root->fn_supent.rb_lhs;
		goto again;
	}
	if (root->fn_supent.rb_rhs) {
		root = root->fn_supent.rb_rhs;
		goto again;
	}
	return result;
}

/* Lookup a block device partition  by its `bp_efi_partguid'. Also  make
 * sure that in the event of a partition being found, no other partition
 * exists that has the same GUID. If anything other than exactly 1  part
 * is found, return `NULL'. */
PUBLIC WUNUSED NONNULL((1)) REF struct blkdev *FCALL
device_lookup_bypartguid(guid_t const *__restrict guid)
		THROWS(E_WOULDBLOCK) {
	REF struct blkdev *result;
	fsuper_nodes_read(&devfs.rs_sup);
	result = NULL;
	assert(devfs.rs_sup.fs_nodes != FSUPER_NODES_DELETED);
	if likely(devfs.rs_sup.fs_nodes != NULL) {
		result = devfs_find_partguid(devfs.rs_sup.fs_nodes, guid, NULL);
		if (result == (REF struct blkdev *)-1)
			result = NULL; /* Ambiguous */
	}
	if (result && !tryincref(&result->bd_dev))
		result = NULL;
	fsuper_nodes_endread(&devfs.rs_sup);
	return result;
}

/* Slightly more advanced version of `device_lookup_byname()':
 *  #1: If str starts with "/dev/": string += 5; stringlen -= 5;
 *  #2: Pass `string' to `device_lookup_byname()', and re-return if non-NULL
 *  #3: if `!S_ISCHR(st_mode)' and `string' matches FORMAT_GUID_T, decode a
 *      GUID and make use of `device_lookup_bypartguid'.
 *  #4: if `st_mode != 0',  do `sscanf(string, "%u:%u")'  for a  MAJOR/MINOR
 *      pair, construct a dev_t, and pass to `device_lookup_bydev()', and
 *      re-return if non-NULL
 *  #5: If all else failed, return `NULL' */
FUNDEF WUNUSED REF struct device *FCALL
device_lookup_bystring(USER CHECKED char const *string,
                       size_t stringlen, mode_t st_mode)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	REF struct device *result;
	static char const devfs_prefix[] = "/dev/";
	if (stringlen >= COMPILER_STRLEN(devfs_prefix) &&
	    memcmp(string, devfs_prefix, COMPILER_STRLEN(devfs_prefix) * sizeof(char)) == 0) {
		string += COMPILER_STRLEN(devfs_prefix);
		stringlen -= COMPILER_STRLEN(devfs_prefix);
	}
	result = device_lookup_byname(string, stringlen, st_mode);
	if (result != NULL)
		goto done;
	if (!S_ISCHR(st_mode) && stringlen == GUID_STRLEN) {
		guid_t guid;
		if (guid_fromstr(string, &guid)) {
			result = (REF struct device *)device_lookup_bypartguid(&guid);
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
			devno  = MKDEV(major, minor);
			result = device_lookup_bydev(st_mode, devno);
			if (result != NULL)
				goto done;
		}
	}

done:
	return result;
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_C */
