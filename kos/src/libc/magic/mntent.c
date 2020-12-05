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
%{
/* (#) Portability: Cygwin        (/winsup/cygwin/include/mntent.h) */
/* (#) Portability: DJGPP         (/include/mntent.h) */
/* (#) Portability: GNU C Library (/misc/mntent.h) */
/* (#) Portability: diet libc     (/include/mntent.h) */
/* (#) Portability: musl libc     (/include/mntent.h) */
/* (#) Portability: uClibc        (/include/mntent.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.mntent")]

%{
#include <features.h>
#include <paths.h>

#include <bits/crt/db/mntent.h>

/* Disclaimer: Documentation is taken from Glibc /usr/include/mntent.h */
/* Utilities for reading/writing fstab, mtab, etc.
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


__SYSDECL_BEGIN

/* File listing canonical interesting mount points.  */
#define MNTTAB _PATH_MNTTAB /* Deprecated alias.  */

/* File listing currently active mount points.  */
#define MOUNTED _PATH_MOUNTED /* Deprecated alias.  */

/* General filesystem types.  */
#define MNTTYPE_IGNORE "ignore" /* Ignore this entry.  */
#define MNTTYPE_NFS    "nfs"    /* Network file system.  */
#define MNTTYPE_SWAP   "swap"   /* Swap device.  */

/* Generic mount options.  */
#define MNTOPT_DEFAULTS "defaults" /* Use all default options.  */
#define MNTOPT_RO       "ro"       /* Read only.  */
#define MNTOPT_RW       "rw"       /* Read/write.  */
#define MNTOPT_SUID     "suid"     /* Set uid allowed.  */
#define MNTOPT_NOSUID   "nosuid"   /* No set uid allowed.  */
#define MNTOPT_NOAUTO   "noauto"   /* Do not auto mount. */

#ifdef __CC__

#ifndef __FILE_defined
#define __FILE_defined 1
typedef __FILE FILE;
#endif /* !__FILE_defined */

}


@@Prepare to begin reading and/or writing mount table
@@entries from the beginning of FILE.  MODE is as for `fopen'
[[cp, export_alias("__setmntent")]]
$FILE *setmntent([[nonnull]] char const *file,
                 [[nonnull]] char const *mode);

@@Read one mount table entry from STREAM.  Returns a pointer to storage
@@reused on the next call, or null for EOF or error (use feof/ferror to check)
[[cp, decl_include("<bits/crt/db/mntent.h>")]]
struct mntent *getmntent([[nonnull]] $FILE *stream);

%
%#ifdef __USE_MISC
@@Reentrant version of the above function
[[decl_include("<features.h>", "<bits/crt/db/mntent.h>")]]
[[cp, export_alias("__getmntent_r")]]
struct mntent *getmntent_r([[nonnull]] $FILE *__restrict stream,
                           [[nonnull]] struct mntent *__restrict result,
                           [[inp(bufsize)]] char *__restrict buffer,
                           __STDC_INT_AS_SIZE_T bufsize);
%#endif /* __USE_MISC */

%
@@Write the mount table entry described by MNT to STREAM.
@@Return zero on success, nonzero on failure
[[cp, decl_include("<bits/crt/db/mntent.h>")]]
int addmntent([[nonnull]] $FILE *__restrict stream,
              [[nonnull]] struct mntent const *__restrict mnt);

@@Close a stream opened with `setmntent'
[[cp_nokos, alias(fclose), export_alias("__endmntent")]]
int endmntent([[nonnull]] $FILE *stream);

@@Search MNT->mnt_opts for an option matching OPT.
@@Returns the address of the substring, or null if none found
[[wunused, ATTR_PURE, decl_include("<bits/crt/db/mntent.h>")]]
char *hasmntopt([[nullable]] struct mntent const *mnt,
                [[nullable]] char const *opt) {
	char *str;
	if likely(mnt && opt && (str = mnt->@mnt_opts@) != NULL) {
		size_t optlen = strlen(opt);
		while (*str) {
			if (memcmp(str, opt, optlen * sizeof(char)) == 0 &&
			    (str[optlen] == ',' || str[optlen] == '\0'))
				return str;
			str = strchrnul(str, ',');
		}
	}
	return NULL;
}



%{

#endif /* __CC__ */

__SYSDECL_END

}