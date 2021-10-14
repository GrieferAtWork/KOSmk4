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
#ifndef GUARD_KERNEL_CORE_FILESYS_NULL_C
#define GUARD_KERNEL_CORE_FILESYS_NULL_C 1
#define __WANT_FS_INIT

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/devfs.h>
#include <kos/dev.h>

DECL_BEGIN

#define MKDEV_mem     MKDEV(1, 1)
#define MKDEV_kmem    MKDEV(1, 2)
#define MKDEV_null    MKDEV(1, 3)
#define MKDEV_port    MKDEV(1, 4)
#define MKDEV_zero    MKDEV(1, 5)
#define MKDEV_full    MKDEV(1, 7)
#define MKDEV_random  MKDEV(1, 8)
#define MKDEV_urandom MKDEV(1, 9)
#define MKDEV_kmsg    MKDEV(1, 11)


#define DEFINE_DIRENT(name, hash)                                        \
	PRIVATE struct fdevfsdirent dirent_dev_##name = {                    \
		.fdd_node   = AWREF_INIT(&dev_##name),                           \
		.fdd_dirent = {                                                  \
			.fd_refcnt  = 2, /* +1: dirent_dev_##name, +1: dev_##name */ \
			.fd_ops     = &fdevfsdirent_ops,                             \
			.fd_ino     = devfs_devnode_makeino(S_IFCHR, MKDEV_##name),  \
			.fd_hash    = hash,                                          \
			.fd_namelen = COMPILER_STRLEN(#name),                        \
			.fd_type    = DT_CHR,                                        \
			.fd_name    = #name,                                         \
		}                                                                \
	}
DEFINE_DIRENT(mem, 42);

PRIVATE struct fdevfsdirent dirent_dev_mem;     /* /dev/mem     (aka. `mfile_phys') */
PRIVATE struct fdevfsdirent dirent_dev_kmem;    /* /dev/kmem */
PRIVATE struct fdevfsdirent dirent_dev_null;    /* /dev/null */
PRIVATE struct fdevfsdirent dirent_dev_port;    /* /dev/port */
PRIVATE struct fdevfsdirent dirent_dev_zero;    /* /dev/zero    (aka. `mfile_zero') */
PRIVATE struct fdevfsdirent dirent_dev_full;    /* /dev/full */
PRIVATE struct fdevfsdirent dirent_dev_random;  /* /dev/random */
PRIVATE struct fdevfsdirent dirent_dev_urandom; /* /dev/urandom */
PRIVATE struct fdevfsdirent dirent_dev_kmsg;    /* /dev/kmsg */


/* /dev/mem (aka. `mfile_phys') */
PUBLIC struct device dev_mem = {
	.dv_devnode = {
	},
	.dv_driver = &drv_self,
	.dv_dirent = ,

};



/* /dev/kmem */
PUBLIC struct device dev_kmem = {
	.
};



/* /dev/null */
PUBLIC struct device dev_null = {
	.
};



/* /dev/port */
PUBLIC struct device dev_port = {
	.
};



/* /dev/zero (aka. `mfile_zero') */
PUBLIC struct device dev_zero = {
	.
};



/* /dev/full */
PUBLIC struct device dev_full = {
	.
};



/* /dev/random */
PUBLIC struct device dev_random = {
	.
};



/* /dev/urandom */
PUBLIC struct device dev_urandom = {
	.
};



/* /dev/kmsg */
PUBLIC struct device dev_kmsg = {
	.
};


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_NULL_C */
