/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_SPEC_H
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_SPEC_H 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>

#include <kos/aref.h>

DECL_BEGIN

INTDEF struct mfile_stream_ops const devfs_spec_v_stream_ops_with_boottime;

struct devicelink_dirent {
	char const        *dld_pfx; /* [1..1][const] Prefix for link strings. */
	REF struct device *dld_dev; /* [1..1][const] Pointed-to device. */
	struct fdirent     dld_ent; /* Underlying directory entry */
};

INTDEF struct fdirent_ops const devicelink_dirent_ops;

/* Construct a new directory entry for a device symlink.
 * The caller must still initialize `return->dld_ent.fd_name' and `fd_hash' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((2, 3)) REF struct devicelink_dirent *KCALL
devicelink_dirent_new(u16 namelen, char const *pfx, struct device *__restrict dev);


#ifndef __fnode_axref_defined
#define __fnode_axref_defined
AXREF(fnode_axref, fnode);
#endif /* !__fnode_axref_defined */

/* Base structure for the enumeration of devices. */
struct devenum: fdirenum {
	struct fnode_axref de_nextfil; /* [0..1] Next device to enumerate. */
};
#define devenum_after(prev) fsuper_nodeafter(&devfs, prev)
LOCAL NONNULL((1)) void
NOTHROW(FCALL devenum_init)(struct devenum *__restrict self) {
	REF struct fnode *dev = devenum_after(__NULLPTR);
	axref_init(&self->de_nextfil, dev);
}

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devenum_v_fini)(struct fdirenum *__restrict self);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL
devenum_v_seekdir(struct fdirenum *__restrict self, off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...);


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_SPEC_H */
