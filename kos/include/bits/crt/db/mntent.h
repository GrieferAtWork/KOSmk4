/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_DB_MNTENT_H
#define _BITS_CRT_DB_MNTENT_H 1

#include <__stdinc.h>

#ifdef __CC__
__DECL_BEGIN

/*
 * C structure for describing a mounted filesystem
 * entry  from  /etc/fstab  or  /proc/self/mounts.
 *
 * Every line that isn't empty, or a comment will match:
 *
 *    mnt_fsname mnt_dir mnt_type mnt_opts mnt_freq mnt_passno
 *
 * For processing, libc uses `fparseln()' with default with `delim = "\0\0#"'
 *
 * FILES:
 *   - /proc/self/mounts       (Currently mounted filesystems)
 *   - /etc/fstab              (Filesystems mounted by /bin/init)
 *   - /etc/mtab               (Alias for /proc/self/mounts)
 */
struct mntent {
	char *mnt_fsname; /* [1..1] Device or server for filesystem. */
	char *mnt_dir;    /* [1..1] Directory mounted on. */
	char *mnt_type;   /* [1..1] Type of filesystem: ufs, nfs, etc. */
	char *mnt_opts;   /* [1..1] Comma-separated options for fs. */
	int   mnt_freq;   /* Dump frequency (in days). */
	int   mnt_passno; /* Pass number for `fsck'. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_MNTENT_H */
