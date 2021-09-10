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
#ifndef GUARD_KERNEL_CORE_FILESYS_FDIRNODE_C
#define GUARD_KERNEL_CORE_FILESYS_FDIRNODE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/fdirent.h>
#include <kernel/fs/fdirnode.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/* Default operators for `fdirnode_ops::dno_*' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fdirnode_v_destroy)(struct fdirnode *__restrict self) {
	decref_unlikely(self->dn_parent);
	fnode_v_destroy(self);
}

/* Lookup the INode associated with a given name within `self'.
 * @return: NULL: No entry exists that is matching the given name. */
PUBLIC WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
fdirnode_lookup_fnode(struct fdirnode *__restrict self,
                      struct flookup_info *__restrict info) {
	struct fdirnode_ops const *ops;
	REF struct fdirent *dirent;
	REF struct fnode *result;
	ops = fdirnode_getops(self);
	if (ops->dno_lookup_fnode)
		return (*ops->dno_lookup_fnode)(self, info);
	assert(ops->dno_lookup);
	dirent = (*ops->dno_lookup)(self, info);
	if (!dirent)
		return NULL;
	{
		FINALLY_DECREF_UNLIKELY(dirent);
		result = (*dirent->fd_ops->fdo_opennode)(dirent, self);
	}
	return result;
}


/* Create new files within a given directory.
 * If another  file with  the same  name already  existed,  then
 * `FMKFILE_F_EXISTS' is set, and that file is returned instead.
 * @throw: E_FSERROR_ILLEGAL_PATH:        `info->mkf_name' contains bad characters
 * @throw: E_FSERROR_DISK_FULL:           Disk full
 * @throw: E_FSERROR_READONLY:            Read-only filesystem (or unsupported operation)
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: ... */
PUBLIC NONNULL((1, 2)) void FCALL
fdirnode_mkfile(struct fdirnode *__restrict self,
                struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS) {
	struct fdirnode_ops const *ops;
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_mkfile)
		THROW(E_FSERROR_READONLY);
	(*ops->dno_mkfile)(self, info);
}

/* Delete the specified file from this directory
 * @throw: E_FSERROR_FILE_NOT_FOUND:      The file had  already been deleted,  or
 *                                        renamed (it no longer exists as `entry'
 *                                        within `self').
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY: `file' is a non-empty directory.
 * @throw: E_FSERROR_READONLY:            Read-only filesystem (or unsupported operation)
 * @throw: E_FSERROR_DELETED:             The given `entry' was already deleted */
PUBLIC NONNULL((1, 2)) void FCALL
fdirnode_unlink(struct fdirnode *__restrict self,
                struct fdirent *__restrict entry,
                struct fnode *__restrict file)
		THROWS(E_FSERROR_FILE_NOT_FOUND, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY, E_FSERROR_DELETED) {
	struct fdirnode_ops const *ops;
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_unlink)
		THROW(E_FSERROR_READONLY);
	(*ops->dno_unlink)(self, entry, file);
}

/* Rename/move the specified file from one location to another
 * @throw: E_FSERROR_ILLEGAL_PATH:            `info->frn_name' contains bad characters
 * @throw: E_FSERROR_DISK_FULL:               Disk full
 * @throw: E_FSERROR_READONLY:                Read-only filesystem
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS:     `info->frn_name' already exists
 * @throw: E_FSERROR_DELETED:                 The given `entry' was already deleted
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:       ...
 * @throw: E_FSERROR_DIRECTORY_MOVE_TO_CHILD: ... */
PUBLIC NONNULL((1, 2)) void FCALL
fdirnode_rename(struct fdirnode *__restrict self,
                struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DELETED, E_FSERROR_CROSS_DEVICE_LINK,
		       E_FSERROR_DIRECTORY_MOVE_TO_CHILD) {
	struct fdirnode_ops const *ops;
	struct fdirnode *olddir, *iter;
	/* Make sure that `self' isn't a child-directory of `info->frn_olddir',
	 * or belongs to a different superblock. */
	olddir = info->frn_olddir;
	if unlikely(self->fn_super != olddir->fn_super)
		THROW(E_FSERROR_CROSS_DEVICE_LINK);
	iter = self;
	do {
		if unlikely(iter == olddir)
			THROW(E_FSERROR_DIRECTORY_MOVE_TO_CHILD);
	} while ((iter = iter->dn_parent) != NULL);

	/* Do the low-level rename operation */
	ops = fdirnode_getops(self);
	if unlikely(!ops->dno_rename)
		THROW(E_FSERROR_READONLY);
	(*ops->dno_rename)(self, info);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FDIRNODE_C */
