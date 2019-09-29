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
#ifndef GUARD_MODPROCFS_FILES_ROOT_C
#define GUARD_MODPROCFS_FILES_ROOT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <sched/pid.h>
#include <hybrid/atomic.h>
#include <assert.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

#undef CONFIG_PROCFS_ALLOW_ROOT_TID
#ifndef CONFIG_PROCFS_DISALLOW_ROOT_TID
#define CONFIG_PROCFS_ALLOW_ROOT_TID 1
#endif /* !CONFIG_PROCFS_DISALLOW_ROOT_TID */


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
#ifndef CONFIG_PROCFS_ALLOW_ROOT_TID
			REF struct task *thread;
#endif /* !CONFIG_PROCFS_ALLOW_ROOT_TID */
			upid_t pidno = (upid_t)(ch - '0');
			size_t i;
			for (i = 1; i < namelen; ++i) {
				ch = ATOMIC_READ(name[i]);
				if unlikely(!(ch >= '0' && ch <= '9'))
					goto notapid;
				pidno *= 10;
				pidno += (upid_t)(ch - '0');
			}
#ifndef CONFIG_PROCFS_ALLOW_ROOT_TID
			thread = pidns_trylookup_task(THIS_PIDNS, pidno);
			if likely(thread)
#endif /* !CONFIG_PROCFS_ALLOW_ROOT_TID */
			{
#ifndef CONFIG_PROCFS_ALLOW_ROOT_TID
				bool isproc;
				isproc = task_isprocessleader_p(thread);
				decref_unlikely(thread);
				if (isproc)
#endif /* !CONFIG_PROCFS_ALLOW_ROOT_TID */
				{
					REF struct directory_entry *result;
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
	}
notapid:
	return ProcFS_Singleton_Directory_Lookup(self, name, namelen, hash, mode);
}

PRIVATE NONNULL((1, 2)) void KCALL
enumpid(directory_enum_callback_t callback,
        void *arg, upid_t pid) {
	char namebuf[32];
	size_t len = sprintf(namebuf, "%u", pid);
	(*callback)(arg, namebuf, len, DT_DIR,
	            PROCFS_INOMAKE_PERPROC(pid, PROCFS_PERPROC_ROOT));
}

PRIVATE NONNULL((1, 2)) void KCALL
ProcFS_RootDirectory_Enum(struct directory_node *__restrict self,
                          directory_enum_callback_t callback,
                          void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	assert(self->i_fsdata == (struct inode_data *)&ProcFS_RootDirectory_FsData);
	/* Enumerate running process PIDs */
	{
		upid_t pidbuf[64];
		size_t i, pidlen = 0;
		struct pidns *ns = THIS_PIDNS;
		sync_read(ns);
		for (i = 0; i <= ns->pn_mask; ++i) {
			struct taskpid *tpid;
			REF struct task *thread;
			upid_t pid;
			tpid = ns->pn_list[i].pe_pid;
			if (tpid == NULL)
				continue;
			if (tpid == PIDNS_ENTRY_DELETED)
				continue;
			thread = taskpid_gettask(tpid);
			if (!thread)
				continue;
			pid = tpid->tp_pids[ns->pn_indirection];
			if (!task_isprocessleader_p(thread))
				pid = 0;
			{
				refcnt_t refcnt;
				do {
					refcnt = ATOMIC_READ(thread->t_refcnt);
					if (refcnt == 1)
						goto unlock_and_flush_pids;
				} while (!ATOMIC_CMPXCH_WEAK(thread->t_refcnt, refcnt, refcnt - 1));
			}
			if (!pid)
				continue;
			if (pidlen >= COMPILER_LENOF(pidbuf)) {
unlock_and_flush_pids:
				/* Enumerate all cached pids */
				sync_endread(ns);
				{
					FINALLY_DECREF(thread);
					while (pidlen) {
						--pidlen;
						enumpid(callback, arg, pidbuf[pidlen]);
					}
					if (pid)
						enumpid(callback, arg, pid);
				}
				pidlen = 0;
				sync_read(ns);
				continue;
			}
			pidbuf[pidlen] = pid;
			++pidlen;
		}
		sync_endread(ns);
		/* Enumerate all remaining pids */
		while (pidlen) {
			--pidlen;
			enumpid(callback, arg, pidbuf[pidlen]);
		}
	}
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
