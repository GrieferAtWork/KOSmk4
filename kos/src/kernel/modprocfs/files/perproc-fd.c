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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_FD_C
#define GUARD_MODPROCFS_FILES_PERPROC_FD_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/pipe.h>
#include <fs/vfs.h>
#include <kernel/handle.h>
#include <sched/eventfd.h>
#include <sched/pid.h>
#include <sched/signalfd.h>

#include <hybrid/atomic.h>

#include <kos/kernel/handle.h>

#include <assert.h>
#include <format-printer.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

struct wall_clock;

INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_Fd_Lookup(struct directory_node *__restrict self,
                         CHECKED USER /*utf-8*/ char const *__restrict name,
                         u16 namelen, uintptr_t UNUSED(hash), fsmode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	/* Evaluate file descriptor number */
	if likely(namelen != 0) {
		char ch = ATOMIC_READ(name[0]);
		if ((ch >= '1' && ch <= '9') || (ch == '0' && namelen == 1)) {
			REF struct task *thread;
			unsigned int fdno = (unsigned int)(ch - '0');
			size_t i;
			upid_t pid;
			for (i = 1; i < namelen; ++i) {
				ch = ATOMIC_READ(name[i]);
				if unlikely(!(ch >= '0' && ch <= '9'))
					goto notanfd;
				fdno *= 10;
				fdno += (unsigned int)(ch - '0');
			}
			pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
			thread = pidns_trylookup_task(THIS_PIDNS, pid);
			if likely(thread) {
				REF struct handle_manager *hman;
				hman = task_gethandlemanager(thread);
				FINALLY_DECREF_UNLIKELY(hman);
				if (handle_existsin(fdno, hman)) {
					REF struct directory_entry *result;
					result = directory_entry_alloc(namelen);
#ifdef NDEBUG
					sprintf(result->de_name, "%u", (unsigned int)fdno);
#else /* NDEBUG */
					{
						size_t temp;
						temp = sprintf(result->de_name, "%u", (unsigned int)fdno);
						assert(temp == namelen);
					}
#endif /* !NDEBUG */
					/* NOTE: We can't actually trust user-space that `hash' is valid, since
					 *       the user may have changed the string in the mean time... */
					result->de_hash = directory_entry_hash(result->de_name, namelen);
					result->de_ino  = PROCFS_INOMAKE_FD(pid, fdno);
					result->de_type = DT_LNK;
					return result;
				}
			}
		}
	}
notanfd:
	return NULL;
}

PRIVATE NONNULL((1, 2)) void KCALL
enum_fd(directory_enum_callback_t callback,
        void *arg, upid_t pid, unsigned int fd) {
	char buf[32];
	size_t len = sprintf(buf, "%u", fd);
	(*callback)(arg, buf, len, DT_LNK,
	            PROCFS_INOMAKE_FD(pid, fd));
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Fd_Enum(struct directory_node *__restrict self,
                       directory_enum_callback_t callback,
                       void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	upid_t pid;
	unsigned int buf[64];
	size_t buflen = 0;
	REF struct task *thread;
	REF struct handle_manager *hman;
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		return;
	FINALLY_DECREF_UNLIKELY(thread);
	hman = task_gethandlemanager(thread);
	FINALLY_DECREF_UNLIKELY(hman);
	sync_read(&hman->hm_lock);
	if (hman->hm_mode == HANDLE_MANAGER_MODE_LINEAR) {
		unsigned int i;
		for (i = 0; i < hman->hm_linear.hm_alloc; ++i) {
			if (hman->hm_linear.hm_vector[i].h_type == HANDLE_TYPE_UNDEFINED)
				continue;
			if (buflen >= COMPILER_LENOF(buf)) {
				sync_endread(&hman->hm_lock);
				while (buflen) {
					--buflen;
					enum_fd(callback, arg, pid, buf[buflen]);
				}
				enum_fd(callback, arg, pid, i);
				buflen = 0;
				sync_read(&hman->hm_lock);
				COMPILER_READ_BARRIER();
				if (hman->hm_mode == HANDLE_MANAGER_MODE_LINEAR)
					continue;
				break;
			}
			buf[buflen] = i;
			++buflen;
		}
	} else {
		unsigned int i;
		for (i = 0; i <= hman->hm_hashvector.hm_hashmsk; ++i) {
			unsigned int fd;
			fd = hman->hm_hashvector.hm_hashvec[i].hh_handle_id;
			if (fd == HANDLE_HASHENT_SENTINEL_ID)
				continue; /* Unused / Sentinel */
			if (hman->hm_hashvector.hm_hashvec[i].hh_vector_index == (unsigned int)-1)
				continue; /* Deleted */
			if (buflen >= COMPILER_LENOF(buf)) {
				sync_endread(&hman->hm_lock);
				while (buflen) {
					--buflen;
					enum_fd(callback, arg, pid, buf[buflen]);
				}
				enum_fd(callback, arg, pid, fd);
				buflen = 0;
				sync_read(&hman->hm_lock);
				COMPILER_READ_BARRIER();
				if (hman->hm_mode != HANDLE_MANAGER_MODE_LINEAR)
					continue;
				break;
			}
			buf[buflen] = fd;
			++buflen;
		}
	}
	sync_endread(&hman->hm_lock);
	while (buflen) {
		--buflen;
		enum_fd(callback, arg, pid, buf[buflen]);
	}
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


PRIVATE NONNULL((1)) size_t KCALL
ProcFS_PerProc_Fd_Entry_Readlink(struct symlink_node *__restrict self,
                                 USER CHECKED /*utf-8*/ char *buf,
                                 size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t result;
	upid_t pid;
	unsigned int fdno;
	REF struct task *thread;
	REF struct handle hnd;
	pid  = (upid_t)(self->i_fileino & PROCFS_INOTYPE_FD_PIDMASK);
	fdno = (unsigned int)((self->i_fileino & PROCFS_INOTYPE_FD_FDMASK) >> PROCFS_INOTYPE_FD_FDSHIFT);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto err;
	{
		FINALLY_DECREF_UNLIKELY(thread);
		{
			REF struct handle_manager *hman;
			hman = task_gethandlemanager(thread);
			FINALLY_DECREF_UNLIKELY(hman);
			hnd = handle_lookupin(fdno, hman);
		}
		TRY {
			struct format_snprintf_data data;
			data.sd_buffer = buf;
			data.sd_bufsiz = bufsize;
			result = (size_t)handle_print(&hnd,
			                              &format_snprintf_printer,
			                              &data);
		} EXCEPT {
			decref_unlikely(hnd);
			RETHROW();
		}
		decref_unlikely(hnd);
	}
	return result;
err:
	return snprintf(buf, bufsize, "anon_inode:[?]");
}

PRIVATE NONNULL((1, 3, 4, 5)) REF struct handle KCALL
ProcFS_PerProc_Fd_Entry_Open(struct inode *__restrict self,
                             oflag_t UNUSED(oflags),
                             struct path *UNUSED(containing_path),
                             struct directory_node *UNUSED(containing_directory),
                             struct directory_entry *UNUSED(containing_dirent))
		THROWS(...) {
	upid_t pid;
	unsigned int fdno;
	REF struct handle result;
	REF struct handle_manager *hman;
	REF struct task *thread;
	pid  = (upid_t)(self->i_fileino & PROCFS_INOTYPE_FD_PIDMASK);
	fdno = (unsigned int)((self->i_fileino & PROCFS_INOTYPE_FD_FDMASK) >> PROCFS_INOTYPE_FD_FDSHIFT);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		THROW(E_NO_SUCH_PROCESS, pid);
	FINALLY_DECREF_UNLIKELY(thread);
	hman = task_gethandlemanager(thread);
	FINALLY_DECREF_UNLIKELY(hman);
	result = handle_lookupin(fdno, hman);
	return result;
}



INTERN struct inode_type ProcFS_PerProc_Fd_Entry_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr   = */ NULL,
		/* .a_saveattr   = */ NULL,
		/* .a_maskattr   = */ NULL,
		/* .a_ioctl      = */ NULL,
		/* .a_clearcache = */ NULL,
		/* .a_open       = */ &ProcFS_PerProc_Fd_Entry_Open
	},
	/* .it_file = */ {
	},
	{
		 .it_symlink = {
			/* .sl_readlink = */ NULL,
			/* .sl_readlink_dynamic = */ &ProcFS_PerProc_Fd_Entry_Readlink
		}
	}
};



DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_FD_C */
