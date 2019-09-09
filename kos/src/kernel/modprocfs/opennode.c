/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_OPENNODE_C
#define GUARD_MODPROCFS_OPENNODE_C 1
#define CONFIG_WANT_FS_AS_STRUCT 1

#include <kernel/compiler.h>
#include <kernel/driver.h>

#include "procfs.h"

DECL_BEGIN


INTERN NONNULL((1, 2, 3, 4)) void KCALL
ProcFS_OpenNode(struct superblock *__restrict self,
                struct inode *__restrict node,
                struct directory_node *__restrict UNUSED(parent_directory),
                struct directory_entry *__restrict UNUSED(parent_directory_entry))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	THROW(E_NOT_IMPLEMENTED_TODO);
}


DECL_END

#endif /* !GUARD_MODPROCFS_OPENNODE_C */
