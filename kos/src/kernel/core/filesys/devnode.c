/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVNODE_C
#define GUARD_KERNEL_CORE_FILESYS_DEVNODE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/handle.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Default  operator  for opening  fdevnode files.  This will
 * lookup the associated `dn_devno' within `devfs' and return
 * the file that one points to. */
PUBLIC NONNULL((1, 2)) void KCALL
fdevnode_v_open(struct mfile *__restrict self,
                struct handle *__restrict hand,
                struct path *access_path,
                struct fdirent *access_dent,
                oflag_t oflags)
		THROWS(E_WOULDBLOCK, E_NO_DEVICE) {
	ino_t devfs_ino;
	REF struct device *node;
	struct fdevnode *me = (struct fdevnode *)self;
	assert(hand->h_type == HANDLE_TYPE_MFILE);
	assert(hand->h_data == me);
	assert((me->fn_mode & S_IFMT) == S_IFCHR ||
	       (me->fn_mode & S_IFMT) == S_IFBLK);

	/* Construct the INO number used for *true* (non-aliasing) device files */
	devfs_ino = devfs_devnode_makeino(me->fn_mode, me->dn_devno);

	/* Lookup the device file within devfs */
	fsuper_nodes_read(&devfs);
	assert(devfs.fs_nodes != FSUPER_NODES_DELETED);
	node = fnode_asdevice(fsuper_nodes_locate(&devfs, devfs_ino));
	if (node && !tryincref(node))
		node = NULL;
	fsuper_nodes_endread(&devfs);

	/* Handle with lookup failures */
	if unlikely(!node) {
		static_assert(E_NO_DEVICE_KIND_BLKDEV == S_IFBLK);
		static_assert(E_NO_DEVICE_KIND_CHRDEV == S_IFCHR);
		THROW(E_NO_DEVICE, me->fn_mode & S_IFMT, me->dn_devno);
	}

	/* Fill in the reference to the *true* file being opened. */
	assert(fnode_isdevice(node));
	hand->h_data = incref(node); /* Inherit reference */
	decref_nokill(me);           /* Drop old reference from `hand->h_data' */

	/* Open the pointed-to device. */
	FINALLY_DECREF_UNLIKELY(node);
	mfile_open(node, hand, access_path, access_dent, oflags);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVNODE_C */
