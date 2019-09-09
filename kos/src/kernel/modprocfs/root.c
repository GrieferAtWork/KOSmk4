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
#ifndef GUARD_MODPROCFS_ROOT_C
#define GUARD_MODPROCFS_ROOT_C 1
#define CONFIG_WANT_FS_AS_STRUCT 1

#include <kernel/compiler.h>
#include <kernel/driver.h>

#include "procfs.h"

DECL_BEGIN


PRIVATE NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_RootDirectory_Lookup(struct directory_node *__restrict self,
                            CHECKED USER /*utf-8*/ char const *__restrict name,
                            u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	return NULL;
}

PRIVATE NONNULL((1, 2)) void KCALL
ProcFS_RootDirectory_Enum(struct directory_node *__restrict node,
                          directory_enum_callback_t callback,
                          void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	(*callback)(arg, "test", 4, DT_DIR, 0);
}



INTERN struct inode_type ProcFS_RootDirectory_Type =
INIT_DIRECTORY_TYPE(&ProcFS_RootDirectory_Lookup,
                    &ProcFS_RootDirectory_Enum);

DECL_END

#endif /* !GUARD_MODPROCFS_ROOT_C */
