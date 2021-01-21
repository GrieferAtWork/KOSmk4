/* HASH CRC-32:0x411a88b8 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/mntent.h) */
/* (#) Portability: DJGPP         (/include/mntent.h) */
/* (#) Portability: GNU C Library (/misc/mntent.h) */
/* (#) Portability: diet libc     (/include/mntent.h) */
/* (#) Portability: musl libc     (/include/mntent.h) */
/* (#) Portability: uClibc        (/include/mntent.h) */
#ifndef _MNTENT_H
#define _MNTENT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <paths.h>

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

#ifdef __CRT_HAVE_setmntent
/* >> setmntent(3) */
__CDECLARE(__ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),(__file,__mode))
#elif defined(__CRT_HAVE___setmntent)
/* >> setmntent(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),__setmntent,(__file,__mode))
#endif /* ... */
/* >> getmntent(3), getmntent_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct mntent *,__NOTHROW_RPC,getmntent,(__FILE *__stream),(__stream))

#ifdef __USE_MISC
#ifdef __CRT_HAVE_getmntent_r
/* >> getmntent(3), getmntent_r(3) */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),struct mntent *,__NOTHROW_RPC,getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),(__stream,__result,__buffer,__bufsize))
#elif defined(__CRT_HAVE___getmntent_r)
/* >> getmntent(3), getmntent_r(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),struct mntent *,__NOTHROW_RPC,getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),__getmntent_r,(__stream,__result,__buffer,__bufsize))
#endif /* ... */
#endif /* __USE_MISC */

/* >> addmntent(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,addmntent,(__FILE *__restrict __stream, struct mntent const *__restrict __mnt),(__stream,__mnt))
#ifdef __CRT_HAVE_endmntent
/* >> endmntent(3) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE_fclose)
/* >> endmntent(3) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),fclose,(__stream))
#elif defined(__CRT_HAVE___endmntent)
/* >> endmntent(3) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),__endmntent,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_hasmntopt
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,hasmntopt,(struct mntent const *__mnt, char const *__opt),(__mnt,__opt))
#else /* __CRT_HAVE_hasmntopt */
#include <libc/local/mntent/hasmntopt.h>
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
__NAMESPACE_LOCAL_USING_OR_IMPL(hasmntopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL hasmntopt)(struct mntent const *__mnt, char const *__opt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hasmntopt))(__mnt, __opt); })
#endif /* !__CRT_HAVE_hasmntopt */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_MNTENT_H */
