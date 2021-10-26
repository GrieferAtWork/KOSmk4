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
#ifndef GUARD_MODPROCFS_PROCFS_C
#define GUARD_MODPROCFS_PROCFS_C 1

#include <kernel/compiler.h>

#include <kernel/driver-callbacks.h>
#include <kernel/fs/constdir.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/super.h>
#include <sched/tsc.h>

#include <linux/magic.h>

#include <assert.h>
#include <stddef.h>

/**/
#include "procfs.h"

DECL_BEGIN


/* Define entries for the root directory. */
#define ROOTENT(name, type, nodeptr, hash) \
	INTDEF struct constdirent PP_CAT2(procfs_root_dirent_, __LINE__);
#include "procfs.def"

/* NOTE: Files in this are sorted as lexicographically ascending. */
PRIVATE struct fdirent *const procfs_root_files[] = {
#define ROOTENT(name, type, nodeptr, hash) \
	constdirent_asent(&PP_CAT2(procfs_root_dirent_, __LINE__)),
#include "procfs.def"
};


PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_root_v_lookup(struct fdirnode *__restrict self,
                     struct flookup_info *__restrict info) {
	/* TODO */
}

PRIVATE NONNULL((1)) void KCALL
procfs_root_v_enum(struct fdirenum *__restrict result) {
	/* TODO: On linux, processes are enumerated by PID (TGID),
	 *       such that each read returns the process with  the
	 *       lowest getpid() that is still > than any  process
	 *       already enumerated  (read:  the  last  enumerated
	 *       process)
	 * Problem is that our `struct pidns' isn't designed with
	 * find-first-pid-greater-or-equal in mind, and doing so
	 * with the current impl is an O(N) operation... */
}



INTERN_CONST struct fsuper_ops const procfs_super_ops = {
	.so_fdir = {
		.dno_lookup = &procfs_root_v_lookup,
		.dno_enum   = &procfs_root_v_enum,
	},
};


/* Assign `tms' for timestamps. */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL initialize_timestamps)(struct fdirent *const *__restrict files, size_t count,
                                     struct timespec const *__restrict tms) {
	size_t i;
	for (i = 0; i < count; ++i) {
		struct fnode *node;
		struct constdirent *ent = fdirent_asconst(files[i]);
		assert(ent->cd_ops == &constdirent_ops);
		node = ent->cd_node;

		/* Assign timestamps. */
		node->mf_atime = *tms;
		node->mf_mtime = *tms;
		node->mf_ctime = *tms;

		/* Recurse on directories */
		if (node->mf_ops == &procfs_constdir_ops.dno_node.no_file) {
			struct constdir *dir = fnode_asconstdir(node);
			initialize_timestamps(dir->cd_entv, dir->cd_entc, tms);
		}
	}
}

/* Procfs driver initialization. */
PRIVATE DRIVER_INIT void KCALL procfs_init(void) {
	struct timespec now = realtime();
	/* Assign the current time as timestamp value to all statically allocated files. */
	initialize_timestamps(procfs_root_files,
	                      COMPILER_LENOF(procfs_root_files),
	                      &now);
	ffilesys_register(&procfs_filesys);
}

/* Procfs driver finalization. */
PRIVATE DRIVER_FINI void KCALL procfs_fini(void) {
	ffilesys_unregister(&procfs_filesys);
}


DECL_END

#endif /* !GUARD_MODPROCFS_PROCFS_C */
