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
#ifndef GUARD_KERNEL_CORE_FILESYS_SOCKNODE_C
#define GUARD_KERNEL_CORE_FILESYS_SOCKNODE_C 1

#include <kernel/compiler.h>

#include <kernel/fs/node.h>
#include <kernel/fs/socknode.h>
#include <kernel/mman/mfile.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/types.h>
#include <network/unix-socket.h>

DECL_BEGIN

/* Default operator for opening fsocknode files. This will  unconditionally
 * throw `E_ILLEGAL_IO_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK' */
PUBLIC NONNULL((1, 2)) void KCALL
fsocknode_v_open(struct mfile *__restrict self,
                 /*in|out*/ REF struct handle *__restrict hand,
                 struct path *access_path,
                 struct fdirent *access_dent,
                 oflag_t oflags)
		THROWS(E_ILLEGAL_IO_OPERATION) {
	(void)self;
	(void)hand;
	(void)access_path;
	(void)access_dent;
	(void)oflags;
	THROW(E_ILLEGAL_IO_OPERATION,
	      E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fsocknode_v_destroy)(struct mfile *__restrict self) {
	struct fsocknode *me = mfile_assock(self);
	unix_server_fini(&me->sun_server);
	fnode_v_destroy(self);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_SOCKNODE_C */
