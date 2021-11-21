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
#ifndef GUARD_KERNEL_INCLUDE_FS_VFS_H
#define GUARD_KERNEL_INCLUDE_FS_VFS_H 1

#include <kernel/compiler.h>

/* TODO: Deprecated header! */
#include <kernel/fs/fs.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>

/* struct path */
#define p_dirent p_name

/* struct vfs */
#define v_drives_lock vf_driveslock
#define v_drives      vf_drives

/* struct fs */
/*#define f_refcnt   fs_refcnt*/
#define f_vfs      fs_vfs
#define f_pathlock fs_pathlock
#define f_root     fs_root
#define f_cwd      fs_cwd
#define f_dcwd     fs_dcwd
#define f_umask    fs_umask
#define f_lnkmax   fs_lnkmax
#define f_mode     fs_mode

#endif /* !GUARD_KERNEL_INCLUDE_FS_VFS_H */
