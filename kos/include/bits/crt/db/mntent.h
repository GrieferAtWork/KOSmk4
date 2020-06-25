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
#ifndef _BITS_CRT_DB_MNTENT_H
#define _BITS_CRT_DB_MNTENT_H 1

#include <__stdinc.h>

__SYSDECL_BEGIN

#ifdef __CC__

/* Structure describing a mount table entry.  */
struct mntent {
	char *mnt_fsname; /* Device or server for filesystem. */
	char *mnt_dir;    /* Directory mounted on. */
	char *mnt_type;   /* Type of filesystem: ufs, nfs, etc. */
	char *mnt_opts;   /* Comma-separated options for fs. */
	int   mnt_freq;   /* Dump frequency (in days). */
	int   mnt_passno; /* Pass number for `fsck'. */
};

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_CRT_DB_MNTENT_H */
