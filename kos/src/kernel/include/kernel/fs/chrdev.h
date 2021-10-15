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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_CHRDEV_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_CHRDEV_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/devfs.h>

#ifdef __CC__
DECL_BEGIN

struct chrdev;
struct chrdev_ops {
	struct device_ops cdo_dev; /* Device operators */
	/* More operators would go here... */
};


struct chrdev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : device              /* Underlying device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct device cd_dev; /* Underlying device */
#define _chrdev_asdev(x) &(x)->cd_dev
#define _chrdev_dev_     cd_dev.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _chrdev_asdev(x) x
#define _chrdev_dev_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
};

/* Return a pointer to character-device operators of `self' */
#define chrdev_getops(self) \
	((struct chrdev_ops const *)__COMPILER_REQTYPE(struct chrdev const *, self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags
 *  - self->_chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent
 *  - self->_chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino  (as `devfs_devnode_makeino(S_IFCHR, dn_devno)')
 *  - self->_chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode (with something or'd with S_IFCHR)
 *  - self->_chrdev_dev_ _device_devnode_ dn_devno
 *  - self->_chrdev_dev_ dv_driver
 *  - self->_chrdev_dev_ dv_dirent
 *  - self->_chrdev_dev_ dv_byname_node
 * @param: struct chrdev     *self: Character device to initialize.
 * @param: struct chrdev_ops *ops:  Character device operators. */
#define _chrdev_init(self, ops)                                                                                \
	(_device_init(_chrdev_asdev(self), &(ops)->cdo_dev),                                                       \
	 (self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts      = MFILE_PARTS_ANONYMOUS, \
	 (self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift = PAGESHIFT,             \
	 (self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_part_amask = PAGEMASK,              \
	 atomic64_init(&(self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize, 0))
#define _chrdev_cinit(self, ops)                                                                               \
	(_device_cinit(_chrdev_asdev(self), &(ops)->cdo_dev),                                                      \
	 (self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts      = MFILE_PARTS_ANONYMOUS, \
	 (self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift = PAGESHIFT,             \
	 (self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_part_amask = PAGEMASK,              \
	 atomic64_cinit(&(self)->_chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize, 0))

/* Finalize a partially initialized `struct chrdev' (as initialized by `_chrdev_init()') */
#define _chrdev_fini(self) _device_fini(_chrdev_asdev(self))

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_CHRDEV_H */
