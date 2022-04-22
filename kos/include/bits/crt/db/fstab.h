/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_DB_FSTAB_H
#define _BITS_CRT_DB_FSTAB_H 1

#include <__stdinc.h>

#ifdef __CC__
__DECL_BEGIN

/* Same as `struct mntent', but has an additional field `fs_type' that
 * is set to one of  `FSTAB_*' (see <fstab.h>), based on  `fs_mntops'. */
struct fstab {
	char       *fs_spec;    /* [1..1] Device or server for filesystem.   (s.a. `struct mntent::mnt_fsname') */
	char       *fs_file;    /* [1..1] Directory mounted on.              (s.a. `struct mntent::mnt_dir') */
	char       *fs_vfstype; /* [1..1] Type of filesystem: ufs, nfs, etc. (s.a. `struct mntent::mnt_type') */
	char       *fs_mntops;  /* [1..1] Comma-separated options for fs.    (s.a. `struct mntent::mnt_opts') */
	char const *fs_type;    /* [1..1] One of `FSTAB_*', based on `fs_mntops' */
	int         fs_freq;    /* Dump frequency (in days).                 (s.a. `struct mntent::mnt_freq') */
	int         fs_passno;  /* Pass number for `fsck'.                   (s.a. `struct mntent::mnt_passno') */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_FSTAB_H */
