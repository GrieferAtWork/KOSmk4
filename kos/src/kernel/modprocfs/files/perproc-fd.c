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

#include <dev/block.h>
#include <dev/char.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/pipe.h>
#include <fs/vfs.h>
#include <sched/eventfd.h>
#include <sched/signalfd.h>
#include <kernel/handle.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <kos/kernel/handle.h>

#include <assert.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

struct wall_clock;

INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_Fd_Lookup(struct directory_node *__restrict self,
                         CHECKED USER /*utf-8*/ char const *__restrict name,
                         u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	/* Evaluate running process PIDs */
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
				struct handle_manager *hman;
				hman = FORTASK(thread, _this_handle_manager);
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
	struct handle_manager *hman;
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		return;
	FINALLY_DECREF_UNLIKELY(thread);
	hman = FORTASK(thread, _this_handle_manager);
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
				continue; /* Unused / Sentinal */
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
		hnd = handle_lookupin(fdno, FORTASK(thread, _this_handle_manager));
		TRY {
			switch (hnd.h_type) {

			case HANDLE_TYPE_DATABLOCK: {
				struct vm_datablock *b = (struct vm_datablock *)hnd.h_data;
				if (vm_datablock_isinode(b)) {
					result = snprintf(buf, bufsize, "anon_inode:[inode:%I64u]",
					                  ((struct inode *)b)->i_fileino);
				} else {
					result = snprintf(buf, bufsize, "anon_inode:[datablock:%Iu]", b);
				}
			}	break;

			case HANDLE_TYPE_BLOCKDEVICE: {
				struct block_device *dev = (struct block_device *)hnd.h_data;
				result = snprintf(buf, bufsize, "/dev/%s", dev->bd_name);
			}	break;

			case HANDLE_TYPE_DIRECTORYENTRY: {
				struct directory_entry *ent = (struct directory_entry *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[directory_entry:%$s]",
				                  ent->de_namelen, ent->de_name);
			}	break;

			case HANDLE_TYPE_FILE: {
				struct file *f = (struct file *)hnd.h_data;
				if (f->f_path && f->f_dirent) {
					result = path_sprintent(buf, bufsize,
					                        f->f_path,
					                        f->f_dirent);
				} else {
					result = snprintf(buf, bufsize, "anon_inode:[file:inode:%I64u]",
					                  f->f_node->i_fileino);
				}
			}	break;

			case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
				struct oneshot_directory_file *f = (struct oneshot_directory_file *)hnd.h_data;
				if (f->d_path && f->d_dirent) {
					result = path_sprintent(buf, bufsize,
					                        f->d_path,
					                        f->d_dirent);
				} else {
					result = snprintf(buf, bufsize, "anon_inode:[oneshot_directory_file:inode:%I64u]",
					                  f->d_node->i_fileino);
				}
			}	break;

			case HANDLE_TYPE_PATH: {
				struct path *p = (struct path *)hnd.h_data;
				result = path_sprint(buf, bufsize, p);
			}	break;

			case HANDLE_TYPE_FS: {
				struct fs *f = (struct fs *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[fs:%Iu]", f);
			}	break;

			case HANDLE_TYPE_VM: {
				struct vm *f = (struct vm *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[vm:%Iu]", f);
			}	break;

			case HANDLE_TYPE_TASK: {
				struct taskpid *t = (struct taskpid *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[task:%u]", taskpid_getpid_s(t));
			}	break;

			case HANDLE_TYPE_CLOCK: {
				struct wall_clock *c = (struct wall_clock *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[wall_clock:%Iu]", c);
			}	break;

			case HANDLE_TYPE_DRIVER: {
				struct driver *d = (struct driver *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[driver:%s]",
				                  d->d_filename ? d->d_filename
				                                : d->d_name);
			}	break;

			case HANDLE_TYPE_PIPE: {
				struct pipe *p = (struct pipe *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[pipe:%Iu]", p);
			}	break;

			case HANDLE_TYPE_PIPE_READER: {
				struct pipe_reader *p = (struct pipe_reader *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[reader:pipe:%Iu]", p->pr_pipe);
			}	break;

			case HANDLE_TYPE_PIPE_WRITER: {
				struct pipe_writer *p = (struct pipe_writer *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[writer:pipe:%Iu]", p->pw_pipe);
			}	break;

			case HANDLE_TYPE_PIDNS: {
				struct pidns *ns = (struct pidns *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[pidns:%Iu]", ns);
			}	break;

			case HANDLE_TYPE_DRIVER_STATE: {
				struct driver_state *st = (struct driver_state *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[driver_state:%Iu]", st);
			}	break;

			case HANDLE_TYPE_CHARACTERDEVICE: {
				struct character_device *dev = (struct character_device *)hnd.h_data;
				result = snprintf(buf, bufsize, "/dev/%s", dev->cd_name);
			}	break;

			case HANDLE_TYPE_EVENTFD_FENCE: {
				struct eventfd *efd = (struct eventfd *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[eventfd:fence:%Iu]", efd);
			}	break;

			case HANDLE_TYPE_EVENTFD_SEMA: {
				struct eventfd *efd = (struct eventfd *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[eventfd:semaphore:%Iu]", efd);
			}	break;

			case HANDLE_TYPE_SIGNALFD: {
				struct signalfd *sfd = (struct signalfd *)hnd.h_data;
				result = snprintf(buf, bufsize, "anon_inode:[signalfd:%Iu]", sfd);
			}	break;

			default:
				result = snprintf(buf, bufsize, "anon_inode:[%s]",
				                  handle_typename(hnd));
				break;
			}
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

INTERN struct inode_type ProcFS_PerProc_Fd_Entry_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ NULL,
		/* .a_saveattr = */ NULL,
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
