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
#ifndef GUARD_KERNEL_CORE_FS_VFS_KERNEL_C
#define GUARD_KERNEL_CORE_FS_VFS_KERNEL_C 1
#define _KOS_SOURCE 1
#define __VFS_DEFINE_AS_C_STRUCTURE 1

#include <kernel/compiler.h>

#include <debugger/function.h>
#include <fs/vfs.h>

#include <bits/param.h>

DECL_BEGIN

/* The kernel's own filesystem / the filesystem used when running `/bin/init'. */
PUBLIC struct vfs vfs_kernel = {
	.v_path = {
		.p_refcnt   = 1,
		.p_vfs      = &vfs_kernel,
		.p_parent   = NULL,
		.p_lock     = ATOMIC_RWLOCK_INIT,
		.p_inode    = NULL,
		.p_mount    = NULL,
		.p_dirent   = NULL,
		.p_dirnext  = { NULL, NULL },
		.p_cldmask  = 0,
		.p_cldsize  = 0,
		.p_cldlist  = NULL,
		.p_delpend  = NULL,
		.p_recent   = { NULL, NULL }
	},
	.v_fscount      = 1,
	.v_rootmount    = { },
	.v_mount_lock   = ATOMIC_RWLOCK_INIT,
	.v_mount        = NULL,
	.v_recent_lock  = ATOMIC_RWLOCK_INIT,
	.v_recent_list  = NULL,
	.v_recent_back  = NULL,
	.v_recent_size  = 0,
	.v_recent_limit = VFS_DEFAULT_RECENT_LIMIT,
	.v_drives_lock  = ATOMIC_RWLOCK_INIT,
	.v_drives       = { NULL, }
};

PUBLIC struct fs fs_kernel = {
	.f_refcnt   = 3, /* GLOBAL, BOOT_IDLE, BOOT_TASK */
	.f_heapsize = sizeof(struct fs),
	.f_vfs      = &vfs_kernel,
	.f_pathlock = ATOMIC_RWLOCK_INIT,
	.f_root     = (struct path *)&vfs_kernel,
	.f_cwd      = (struct path *)&vfs_kernel,
	.f_dcwd     = { NULL, },
	.f_umask    = CONFIG_FS_UMASK_DEFAULT,
	.f_lnkmax   = MAXSYMLINKS,
	.f_fsuid    = 0,
	.f_fsgid    = 0,
	{{
		.f_atmask = FS_MODE_FALWAYS1MASK | (~FS_MODE_FALWAYS0MASK),
		.f_atflag = FS_MODE_FALWAYS1FLAG,
	}}
};

DEFINE_DBG_BZERO_OBJECT(vfs_kernel.v_path.p_lock);
DEFINE_DBG_BZERO_OBJECT(vfs_kernel.v_mount_lock);
DEFINE_DBG_BZERO_OBJECT(vfs_kernel.v_recent_lock);
DEFINE_DBG_BZERO_OBJECT(vfs_kernel.v_drives_lock);
DEFINE_DBG_BZERO_OBJECT(fs_kernel.f_pathlock);
DEFINE_DBG_BZERO_IF(THIS_FS != NULL && THIS_VFS != NULL,
                    &THIS_VFS->v_path.p_lock,
                    sizeof(vfs_kernel.v_path.p_lock));
DEFINE_DBG_BZERO_IF(THIS_FS != NULL && THIS_VFS != NULL,
                    &THIS_VFS->v_mount_lock,
                    sizeof(vfs_kernel.v_mount_lock));
DEFINE_DBG_BZERO_IF(THIS_FS != NULL && THIS_VFS != NULL,
                    &THIS_VFS->v_recent_lock,
                    sizeof(vfs_kernel.v_recent_lock));
DEFINE_DBG_BZERO_IF(THIS_FS != NULL && THIS_VFS != NULL,
                    &THIS_VFS->v_drives_lock,
                    sizeof(vfs_kernel.v_drives_lock));
DEFINE_DBG_BZERO_IF(THIS_FS != NULL,
                    &THIS_FS->f_pathlock,
                    sizeof(fs_kernel.f_pathlock));


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_VFS_KERNEL_C */
