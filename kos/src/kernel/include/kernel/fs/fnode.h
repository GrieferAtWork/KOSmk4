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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FNODE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/mman/mfile.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Filesystem node. */
struct fnode
#ifdef __cplusplus
    : mfile               /* Underlying mem-file */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct mfile fn_file; /* Underlying mem-file */
#endif /* !__cplusplus */

};

/*
 * TODO: Type-tree:
 *
 *   mfile                                          (replacement for `struct vm_datablock')
 *     |
 *     +-- -> fnode                                 (replacement for `struct inode')
 *              |
 *              +----> fregnode  (S_IFREG)          (replacement for `struct regular_node')
 *              |
 *              +----> fdirnode  (S_IFDIR)          (replacement for `struct directory_node')
 *              |
 *              +----> flnknode  (S_IFLNK)          (replacement for `struct symlink_node')
 *              |
 *              +----> fsocknode (S_IFSOCK)         (replacement for `struct socket_node')
 *              |
 *              +----> fdevnode
 *                       |
 *                       +-----> blkdev  (S_IFBLK)  (replacement for `struct block_device')
 *                       |
 *                       +-----> chrdev  (S_IFCHR)  (replacement for `struct character_device')
 *
 * XXX: should blkdev be mmap-able? Should it behave as expected,
 *      meaning that drivers should simply be able to mmap relevant
 *      parts of disk images into memory? How would sync(2)-ing work?
 *   -> Testing on linux, it seems you're able to mmap(2) block
 *      devices, such as disks. So it stands to reason that kos
 *      should allow you to do the same...
 * Only problem is: The absolute on-disk address of a page-aligned
 *                  file position (e.g. `0'), may itself not be page-
 *                  aligned itself.
 *             iow: File I/O _has_ to by-pass the mem-part tree of
 *                  the underlying block-device.
 */

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FNODE_H */
