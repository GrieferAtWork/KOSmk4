/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FS_SPECIAL_NODE_C
#define GUARD_KERNEL_CORE_FS_SPECIAL_NODE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/special-node.h>

DECL_BEGIN

/* Mandatory finalizier that must be called by `struct inode_type::it_fini'
 * of any INode that is `S_ISFIFO()'. This function must be called by
 * file-system specific overrides for `struct inode_type::it_fini', and should
 * be linked in as part of the `struct inode_type::it_directory::d_mknod'
 * callback. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fifo_node_fini)(struct inode *__restrict self) {
	struct fifo_node *me;
	me = (struct fifo_node *)self;
	fifo_fini(&me->f_fifo);
}

/* Same as `fifo_node_fini()', but for `S_ISSOCK()' nodes. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL socket_node_fini)(struct inode *__restrict self) {
	struct socket_node *me;
	me = (struct socket_node *)self;
	unix_server_fini(&me->s_server);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_SPECIAL_NODE_C */
