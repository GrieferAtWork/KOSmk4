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
#ifndef GUARD_MODPROCFS_FILES_ROOT_C
#define GUARD_MODPROCFS_FILES_ROOT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <sched/enum.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

PRIVATE NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_RootDirectory_Lookup(struct directory_node *__restrict self,
                            CHECKED USER /*utf-8*/ char const *__restrict name,
                            u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	assert(self->i_fsdata == (struct inode_data *)&ProcFS_RootDirectory_FsData);
	/* Evaluate running process PIDs */
	if likely(namelen != 0) {
		char ch = ATOMIC_READ(name[0]);
		if (ch >= '1' && ch <= '9') {
			REF struct task *thread;
			upid_t pidno = (upid_t)(ch - '0');
			size_t i;
			for (i = 1; i < namelen; ++i) {
				ch = ATOMIC_READ(name[i]);
				if unlikely(!(ch >= '0' && ch <= '9'))
					goto notapid;
				pidno *= 10;
				pidno += (upid_t)(ch - '0');
			}
			thread = pidns_trylookup_task(THIS_PIDNS, pidno);
			if likely(thread) {
				REF struct directory_entry *result;
				decref_unlikely(thread);
				result = directory_entry_alloc(namelen);
#ifdef NDEBUG
				sprintf(result->de_name, "%u", (unsigned int)pidno);
#else /* NDEBUG */
				{
					size_t temp;
					temp = sprintf(result->de_name, "%u", (unsigned int)pidno);
					assert(temp == namelen);
				}
#endif /* !NDEBUG */
				/* NOTE: We can't actually trust user-space that `hash' is valid, since
				 *       the user may have changed the string in the mean time... */
				result->de_hash = directory_entry_hash(result->de_name, namelen);
				result->de_ino  = PROCFS_INOMAKE_PERPROC(pidno, PROCFS_PERPROC_ROOT);
				result->de_type = DT_DIR;
				return result;
			}
		}
	}
notapid:
	return ProcFS_Singleton_Directory_Lookup(self, name, namelen, hash, mode);
}

INTERN ssize_t KCALL
ProcFS_EnumProcessCallback(void *arg,
                           struct task *UNUSED(thread),
                           struct taskpid *tpid) {
	size_t len;
	pid_t pid;
	char namebuf[32];
	ProcFS_EnumProcessCallback_Data *data;
	if unlikely(!tpid)
		return 0; /* Shouldn't happen... */
	data = (ProcFS_EnumProcessCallback_Data *)arg;
	/* Print the process's PID, so it can be enumerated. */
	pid = tpid->tp_pids[data->epc_ns_ind];
	len = sprintf(namebuf, "%u", pid);
	(*data->epc_cb)(data->epc_arg, namebuf, len, DT_DIR,
	                PROCFS_INOMAKE_PERPROC(pid, PROCFS_PERPROC_ROOT));
	return 0;
}


PRIVATE NONNULL((1, 2)) void KCALL
ProcFS_RootDirectory_Enum(struct directory_node *__restrict self,
                          directory_enum_callback_t callback,
                          void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	ProcFS_EnumProcessCallback_Data data;
	struct pidns *ns;
	assert(self->i_fsdata == (struct inode_data *)&ProcFS_RootDirectory_FsData);

	/* Enumerate running process PIDs */
	ns               = THIS_PIDNS;
	data.epc_cb      = callback;
	data.epc_arg     = arg;
	data.epc_ns_ind  = ns->pn_indirection;
	task_enum_processes(&ProcFS_EnumProcessCallback, &data, ns);

	/* Enumerate always-present files. */
	ProcFS_Singleton_Directory_Enum(self, callback, arg);
}



INTERN struct inode_type ProcFS_RootDirectory_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_Singleton_LoadAttr,
		/* .a_saveattr = */ &ProcFS_Singleton_SaveAttr,
	},
	/* .it_file = */ {
	},
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_RootDirectory_Lookup,
				/* .o_enum   = */ &ProcFS_RootDirectory_Enum,
			}
		}
	}
};


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_ROOT_C */
