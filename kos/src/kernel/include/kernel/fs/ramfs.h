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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_RAMFS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_RAMFS_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/clnknode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

#define ramfs_lnknode            fclnknode /* Same type... */
#define _ramfs_lnknode_lnode_    _fclnknode_lnode_
#define _ramfs_lnknode_aslnknode _fclnknode_aslnknode
#define ramfs_lnknode_v_readlink fclnknode_v_readlink
#define ramfs_lnknode_v_linkstr  fclnknode_v_linkstr
#define ramfs_lnknode_v_destroy  fclnknode_v_destroy
#define _ramfs_lnknode_alloc     _fclnknode_alloc
#define _ramfs_lnknode_new       _fclnknode_new
#define _ramfs_lnknode_destroy   _fclnknode_destroy

#define ramfs_regnode              fregnode /* Same type... */
#define _ramfs_regnode_asnode      _fregnode_asnode
#define _ramfs_regnode_node_       _fregnode_node_
#define ramfs_regnode_getops       fregnode_getops
#define _ramfs_regnode_assert_ops_ _fregnode_assert_ops_
#define _ramfs_regnode_init        _fregnode_init
#define _ramfs_regnode_cinit       _fregnode_cinit
#define _ramfs_regnode_fini        _fregnode_fini


struct ramfs_dirent {
	/* TODO: Delete flag which, if set, causes this structure to decref() itself.
	 *       Also, when set, an encounter of this structure in `ramfs_dirdata' is
	 *       considered a no-op.  (NOTE: Async  self-removing can be  done via  a
	 *       lockop that can be overlay'd on-top of `rde_ent.fd_ino', since  this
	 *       sort of self-removal is only done once the refcnt of `rde_ent' drops
	 *       to 0). */
	/* TODO: LLRBTREE of files within the directory (root is in `ramfs_dirdata') */
	REF struct fnode *rde_node; /* [1..1][const] Bound file-node (NOTE: This field also holds a  reference
	                             * to `->fn_nlink', which is decremented when this structure is destroyed) */
	struct fdirent    rde_ent;  /* Underlying directory entry. */
};

/* Directory entry operators for instances of `ramfs_dirent' */
DATDEF struct fdirent_ops const ramfs_dirent_ops;
FUNDEF NOBLOCK NONNULL((1)) void /* == ramfs_dirent_ops.fdo_destroy */
NOTHROW(KCALL ramfs_dirent_v_destroy)(struct fdirent *__restrict self);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct fnode * /* == ramfs_dirent_ops.fdo_opennode */
NOTHROW(KCALL ramfs_dirent_v_opennode)(struct fdirent *__restrict self, struct fdirnode *__restrict dir);


/* Extended directory data. */
struct ramfs_dirdata {
	/* TODO: atomic_rwlock          tree_lock; */
	/* TODO: LOCKOPS                tree_lops; */
	/* TODO: LLRBROOT(ramfs_dirent) tree; */
	int placeholder;
};



struct ramfs_dirnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdirnode                    /* Underlying directory */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdirnode      rdn_dir; /* Underlying directory */
#endif /* __WANT_FS_INLINE_STRUCTURES */
	struct ramfs_dirdata rdn_dat; /* Directory data */
};

struct ramfs_super
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fsuper                     /* Underlying Superblock */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fsuper        rs_sup; /* Underlying Superblock */
#endif /* __WANT_FS_INLINE_STRUCTURES */
	struct ramfs_dirdata rs_dat; /* Directory data */
};






DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_RAMFS_H */
