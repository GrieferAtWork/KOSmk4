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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/mntent.h) */
/* (#) Portability: DJGPP         (/include/mntent.h) */
/* (#) Portability: GNU C Library (/misc/mntent.h) */
/* (#) Portability: diet libc     (/include/mntent.h) */
/* (#) Portability: musl libc     (/include/mntent.h) */
/* (#) Portability: uClibc        (/include/mntent.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.mntent")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <paths.h>
)]%{

#include <bits/crt/db/mntent.h>

/* Filename for the mounting-point table (/etc/fstab) */
#define MNTTAB _PATH_MNTTAB /* Deprecated alias. */

/* Filename for currently mounted filesystems (/proc/self/mounts) */
#define MOUNTED _PATH_MOUNTED /* Deprecated alias. */

/* Some filesystem type names. */
#define MNTTYPE_IGNORE "ignore" /* Ignore this entry. */
#define MNTTYPE_NFS    "nfs"    /* Network file system. */
#define MNTTYPE_SWAP   "swap"   /* Swap device. */

/* Some filesystem mount options. */
#define MNTOPT_DEFAULTS "defaults" /* Default options */
#define MNTOPT_RO       "ro"       /* Read-only file access.            (s.a. `ST_RDONLY') */
#define MNTOPT_RW       "rw"       /* Read/write file access.           (s.a. `ST_RDONLY') */
#define MNTOPT_SUID     "suid"     /* Allow `S_ISUID' and `S_ISGID'.    (s.a. `ST_NOSUID') */
#define MNTOPT_NOSUID   "nosuid"   /* Disallow `S_ISUID' and `S_ISGID'. (s.a. `ST_NOSUID') */
#define MNTOPT_NOAUTO   "noauto"   /* Don't auto-mount.                 (s.a. `mount -a') */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __FILE_defined
#define __FILE_defined 1
typedef __FILE FILE;
#endif /* !__FILE_defined */

}


@@>> setmntent(3)
[[cp, export_alias("__setmntent")]]
$FILE *setmntent([[nonnull]] char const *file,
                 [[nonnull]] char const *mode);

@@>> getmntent(3), getmntent_r(3)
[[cp, decl_include("<bits/crt/db/mntent.h>")]]
struct mntent *getmntent([[nonnull]] $FILE *stream);

%
%#ifdef __USE_MISC
[[decl_include("<features.h>", "<bits/crt/db/mntent.h>")]]
[[cp, doc_alias(getmntent), export_alias("__getmntent_r")]]
struct mntent *getmntent_r([[nonnull]] $FILE *__restrict stream,
                           [[nonnull]] struct mntent *__restrict result,
                           [[inp(bufsize)]] char *__restrict buffer,
                           __STDC_INT_AS_SIZE_T bufsize);
%#endif /* __USE_MISC */
%


@@>> addmntent(3)
[[cp, decl_include("<bits/crt/db/mntent.h>")]]
int addmntent([[nonnull]] $FILE *__restrict stream,
              [[nonnull]] struct mntent const *__restrict mnt);

@@>> endmntent(3)
[[cp_nokos, alias(fclose), export_alias("__endmntent")]]
int endmntent([[nonnull]] $FILE *stream);

@@>> hasmntopt(3)
@@Check if `mnt->mnt_opts' contains an option matching `opt'.
@@@return: * :   Address of the `opt'-string in `mnt->mnt_opts'
@@@return: NULL: No option `opt' found in `mnt->mnt_opts'
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

__SYSDECL_END
#endif /* __CC__ */

}
