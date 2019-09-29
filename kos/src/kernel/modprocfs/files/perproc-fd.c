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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_FD_C
#define GUARD_MODPROCFS_FILES_PERPROC_FD_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <sched/pid.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN


INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_Fd_Lookup(struct directory_node *__restrict self,
                         CHECKED USER /*utf-8*/ char const *__restrict name,
                         u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	(void)self;
	(void)name;
	(void)namelen;
	(void)hash;
	(void)mode;
	/* TODO */
	return NULL;
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Fd_Enum(struct directory_node *__restrict self,
                       directory_enum_callback_t callback,
                       void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	(void)self;
	(void)callback;
	(void)arg;
	/* TODO */
}


INTERN struct inode_type ProcFS_PerProc_Fd_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ NULL,
		/* .a_saveattr = */ NULL,
	},
	/* .it_file = */ {
	},
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_PerProc_Fd_Lookup,
				/* .o_enum   = */ &ProcFS_PerProc_Fd_Enum,
			}
		}
	}
};


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_FD_C */
