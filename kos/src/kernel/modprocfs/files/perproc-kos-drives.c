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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_KOS_DRIVES_C
#define GUARD_MODPROCFS_FILES_PERPROC_KOS_DRIVES_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN


INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_Kos_Drives_Lookup(struct directory_node *__restrict self,
                                 CHECKED USER /*utf-8*/ char const *__restrict name,
                                 u16 namelen, uintptr_t UNUSED(hash), fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	upid_t pid;
	REF struct task *thread;
	unsigned char driveid;
	REF struct directory_entry *result;
	if (namelen != 1)
		goto err;
	driveid = (unsigned char)ATOMIC_READ(name[0]);
	if (!(driveid >= 'a' && driveid <= 'z')) {
		if (!(mode & FS_MODE_FDOSPATH))
			goto err;
		if (!(driveid >= 'A' && driveid <= 'Z'))
			goto err;
		driveid -= 'A';
		driveid += 'a';
	}
	driveid -= 'a';
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto err;
	{
		struct fs *threadfs;
		struct vfs *threadvfs;
		FINALLY_DECREF_UNLIKELY(thread);
		threadfs = FORTASK(thread, this_fs);
		if unlikely(!threadfs)
			goto err;
		threadvfs = threadfs->f_vfs;
		if (!ATOMIC_READ(threadvfs->v_drives[driveid]))
			goto err;
	}
	/* This is a bound drive! */
	result = directory_entry_alloc(1);
	result->de_ino     = PROCFS_INOMAKE_DRIVE(pid, driveid);
	result->de_type    = DT_LNK;
	result->de_name[0] = 'a' + driveid;
	result->de_hash    = directory_entry_hash(result->de_name, 1);
	return result;
err:
	return NULL;
}

INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_Kos_Dcwd_Lookup(struct directory_node *__restrict self,
                               CHECKED USER /*utf-8*/ char const *__restrict name,
                               u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	REF struct directory_entry *result;
	result = ProcFS_PerProc_Kos_Drives_Lookup(self, name, namelen, hash, mode);
	if (result) {
		result->de_ino &= ~PROCFS_INO_TYPEMASK;
		result->de_ino |= (ino_t)PROCFS_INOTYPE_DCWD << PROCFS_INO_TYPESHFT;
	}
	return result;
}

PRIVATE u32 KCALL get_bound_drives(upid_t pid) {
	u32 result = 0;
	REF struct task *thread;
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto done;
	{
		size_t i;
		struct fs *threadfs;
		struct vfs *threadvfs;
		FINALLY_DECREF_UNLIKELY(thread);
		threadfs = FORTASK(thread, this_fs);
		if unlikely(!threadfs)
			goto done;
		threadvfs = threadfs->f_vfs;
		for (i = 0; i < VFS_DRIVECOUNT; ++i) {
			if (ATOMIC_READ(threadvfs->v_drives[i]) != NULL)
				result |= (u32)1 << i;
		}
	}
done:
	return result;
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Kos_Drives_Enum(struct directory_node *__restrict self,
                               directory_enum_callback_t callback,
                               void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	upid_t pid;
	u32 drives;
	size_t i;
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	drives = get_bound_drives(pid);
	for (i = 0; i < VFS_DRIVECOUNT; ++i) {
		char buf[1];
		if (!(drives & ((u32)1 << i)))
			continue;
		buf[0] = 'a' + i;
		(*callback)(arg, buf, 1, DT_LNK,
		            PROCFS_INOMAKE_DRIVE(pid, i));
	}
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Kos_Dcwd_Enum(struct directory_node *__restrict self,
                             directory_enum_callback_t callback,
                             void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	upid_t pid;
	u32 drives;
	size_t i;
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	drives = get_bound_drives(pid);
	for (i = 0; i < VFS_DRIVECOUNT; ++i) {
		char buf[1];
		if (!(drives & ((u32)1 << i)))
			continue;
		buf[0] = 'a' + i;
		(*callback)(arg, buf, 1, DT_LNK,
		            PROCFS_INOMAKE_DCWD(pid, i));
	}
}


INTERN struct inode_type ProcFS_PerProc_Kos_Drives_Type = {
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
				/* .o_lookup = */ &ProcFS_PerProc_Kos_Drives_Lookup,
				/* .o_enum   = */ &ProcFS_PerProc_Kos_Drives_Enum,
			}
		}
	}
};

INTERN struct inode_type ProcFS_PerProc_Kos_DrivesCwd_Type = {
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
				/* .o_lookup = */ &ProcFS_PerProc_Kos_Dcwd_Lookup,
				/* .o_enum   = */ &ProcFS_PerProc_Kos_Dcwd_Enum,
			}
		}
	}
};


INTDEF NONNULL((1)) size_t KCALL
ProcFS_PerProc_FsLink_Printer(struct symlink_node *__restrict self,
                              USER CHECKED /*utf-8*/ char *buf,
                              size_t bufsize,
                              ptrdiff_t offsetof_path_from_fs);


PRIVATE NONNULL((1)) size_t KCALL
ProcFS_PerProc_Kos_Drives_Entry_Readlink(struct symlink_node *__restrict self,
                                         USER CHECKED /*utf-8*/ char *buf,
                                         size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t result;
	upid_t pid;
	unsigned char drive_id;
	REF struct task *thread;
	REF struct path *drive_root;
	pid      = (upid_t)(self->i_fileino & PROCFS_INOTYPE_DCWD_PIDMASK);
	drive_id = (unsigned char)((self->i_fileino & PROCFS_INOTYPE_DCWD_DRVMASK) >> PROCFS_INOTYPE_DCWD_DRVSHIFT);
	assert(drive_id < VFS_DRIVECOUNT);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto err;
	{
		struct fs *threadfs;
		struct vfs *threadvfs;
		FINALLY_DECREF_UNLIKELY(thread);
		threadfs = FORTASK(thread, this_fs);
		if unlikely(!threadfs)
			goto err;
		threadvfs = threadfs->f_vfs;
		sync_read(&threadvfs->v_drives_lock);
		drive_root = xincref(threadvfs->v_drives[drive_id]);
		sync_endread(&threadvfs->v_drives_lock);
	}
	if unlikely(!drive_root)
		goto err;
	{
		FINALLY_DECREF_UNLIKELY(drive_root);
		result = path_sprint(buf, bufsize, drive_root);
	}
	return result;
err:
	return snprintf(buf, bufsize, "/");
}

PRIVATE NONNULL((1)) size_t KCALL
ProcFS_PerProc_Kos_Dcwd_Entry_Readlink(struct symlink_node *__restrict self,
                                       USER CHECKED /*utf-8*/ char *buf,
                                       size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t result;
	upid_t pid;
	unsigned char drive_id;
	REF struct task *thread;
	REF struct path *drive_pwd;
	pid      = (upid_t)(self->i_fileino & PROCFS_INOTYPE_DRIVE_PIDMASK);
	drive_id = (unsigned char)((self->i_fileino & PROCFS_INOTYPE_DRIVE_DRVMASK) >> PROCFS_INOTYPE_DRIVE_DRVSHIFT);
	assert(drive_id < VFS_DRIVECOUNT);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto err;
	{
		struct fs *threadfs;
		FINALLY_DECREF_UNLIKELY(thread);
		threadfs = FORTASK(thread, this_fs);
		if unlikely(!threadfs)
			goto err;
		sync_read(&threadfs->f_pathlock);
		drive_pwd = xincref(threadfs->f_dcwd[drive_id]);
		sync_endread(&threadfs->f_pathlock);
		if unlikely(!drive_pwd) {
			struct vfs *threadvfs;
			threadvfs = threadfs->f_vfs;
			sync_read(&threadvfs->v_drives_lock);
			drive_pwd = xincref(threadvfs->v_drives[drive_id]);
			sync_endread(&threadvfs->v_drives_lock);
			if unlikely(!drive_pwd)
				goto err;
		}
	}
	{
		FINALLY_DECREF_UNLIKELY(drive_pwd);
		result = path_sprint(buf, bufsize, drive_pwd);
	}
	return result;
err:
	return snprintf(buf, bufsize, "/");
}



INTERN struct inode_type ProcFS_PerProc_Kos_Drives_Entry_Type = {
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
			/* .sl_readlink_dynamic = */ &ProcFS_PerProc_Kos_Drives_Entry_Readlink
		}
	}
};

INTERN struct inode_type ProcFS_PerProc_Kos_Dcwd_Entry_Type = {
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
			/* .sl_readlink_dynamic = */ &ProcFS_PerProc_Kos_Dcwd_Entry_Readlink
		}
	}
};



DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_KOS_DRIVES_C */
