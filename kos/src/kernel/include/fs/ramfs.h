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
#ifndef GUARD_KERNEL_INCLUDE_FS_RAMFS_H
#define GUARD_KERNEL_INCLUDE_FS_RAMFS_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include <kernel/fs/ramfs.h>
#else /* CONFIG_USE_NEW_FS */
#include <fs/node.h>
#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

/* Ramfs filesystem types. */
DATDEF struct superblock_type ramfs_type;
DATDEF struct inode_type ramfs_dev_type;
DATDEF struct inode_type ramfs_fifo_type;
DATDEF struct inode_type ramfs_socket_type;
DATDEF struct inode_type ramfs_regular_type;
DATDEF struct inode_type ramfs_directory_type;
DATDEF struct inode_type ramfs_symlink_type;

/* The builtin filesystem that is mounted under
 * /dev.  This is a singleton instance of ramfs */
DATDEF struct superblock devfs;

/* Without blocking, remove an INode from the
 * root  directory  of  the  /dev  filesystem
 * NOTE: This  function  is  used  to  remove  the automatically
 *       created /dev INodes for every detected block-device, or
 *       character-device when that  device is being  destroyed.
 * WARNING: Do not use this function to remove directory
 *          nodes from `/dev'. - Doing so may not  clear
 *          the directory from recent-path caches in VFS
 *          mappings of the /dev filesystem.
 * NOTE: If the given node/entry have already been removed,
 *       then this function is a no-op. */
FUNDEF NOBLOCK void
NOTHROW(KCALL devfs_remove)(struct inode *__restrict node,
                            struct fdirent *__restrict entry);

/* Insert a new device node into /dev, using `name' as the
 * filename  of  the   file  to-be   placed  under   /dev.
 * NOTE: The  caller  is responsible  to ensure  that `name'
 *       is a valid filename, suitable to a directory entry.
 * @param: name:         The name of the file to-be placed under /dev
 * @param: kind:         The type of file to create (either `S_IFCHR' or `S_IFBLK')
 * @param: devno:        The character- or block-device number that should be referenced
 * @param: pdevfs_node:  When non-NULL, upon success place a reference to the created INode in here
 * @param: pdevfs_entry: When non-NULL, upon success place a reference to the created directory entry in here
 * @return: true:  Successfully created a new entry under /dev
 * @return: false: A file matching `name' already exists.
 *                 In this case, both `*pdevfs_node' and `*pdevfs_entry'
 *                 (if   given)   will   have   been   set   to  `NULL'. */
FUNDEF bool KCALL
devfs_insert(USER CHECKED char const *name,
             mode_t kind, dev_t devno,
             REF struct inode **pdevfs_node,
             REF struct fdirent **pdevfs_entry)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);


#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_FS_RAMFS_H */
