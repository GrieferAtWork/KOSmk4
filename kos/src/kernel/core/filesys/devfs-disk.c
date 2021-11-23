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
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_DISK_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_DISK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs-disk.h>
#include <kernel/fs/devfs-spec.h>
#include <kernel/fs/devfs.h>

#include <stddef.h>

/**/
#include "devfs-spec.h"

DECL_BEGIN

/* TODO */




/************************************************************************/
/* /dev/disk                                                            */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_disk_v_lookup(struct fdirnode *__restrict UNUSED(self),
                    struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	/* TODO */
	(void)info;
	COMPILER_IMPURE();
	return NULL;
}

struct disk_enum: fdirenum {
	/* TODO */
};

PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_disk_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	result->de_ops = &fdirenum_empty_ops;
}

INTERN_CONST struct fdirnode_ops const devfs_disk_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = (void(KCALL *)(struct mfile *__restrict))(void *)-1,
			.mo_changed = &fdirnode_v_changed,
			.mo_stream  = &devfs_spec_v_stream_ops_with_boottime,
		},
		.no_free   = (void(KCALL *)(struct fnode *__restrict))(void *)-1,
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.dno_lookup = &devfs_disk_v_lookup,
	.dno_enumsz = sizeof(struct disk_enum),
	.dno_enum   = &devfs_disk_v_enum,
};

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_DISK_C */
