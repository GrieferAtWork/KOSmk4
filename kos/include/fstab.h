/* HASH CRC-32:0xf6dbb870 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/fstab.h) */
/* (#) Portability: DJGPP         (/include/fstab.h) */
/* (#) Portability: GNU C Library (/misc/fstab.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/fstab.h) */
/* (#) Portability: diet libc     (/include/fstab.h) */
/* (#) Portability: libc4/5       (/include/fstab.h) */
/* (#) Portability: libc6         (/include/fstab.h) */
/* (#) Portability: mintlib       (/include/fstab.h) */
/* (#) Portability: musl libc     (/include/fstab.h) */
/* (#) Portability: uClibc        (/include/fstab.h) */
#ifndef _FSTAB_H
#define _FSTAB_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <paths.h>
#include <bits/crt/db/fstab.h>

/************************************************************************/
/* <fstab.h>: An alternate interface/wrapper for <mntent.h>             */
/************************************************************************/

/* The filename of the fstab database file. (s.a. `_PATH_MNTTAB') */
#ifdef _PATH_MNTTAB
#define _PATH_FSTAB _PATH_MNTTAB
#define FSTAB       _PATH_MNTTAB /* Deprecated macro */
#endif /* _PATH_MNTTAB */

/* Possible values for `struct fstab::fs_type' */
#define FSTAB_RW "rw" /* read+write */
#define FSTAB_RQ "rq" /* read+write with quotas */
#define FSTAB_RO "ro" /* read-only */
#define FSTAB_SW "sw" /* swap */
#define FSTAB_XX "xx" /* ??? */

#ifdef __CC__
__SYSDECL_BEGIN

/* >> setfsent(3)
 * Open the fstab database and rewind to its start
 * @return: 1 : Success
 * @return: 0 : Error (s.a. `errno') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,setfsent,(void),())
/* >> endfsent(3)
 * Close the fstab database. */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,endfsent,(void),())
/* >> getfsent(3)
 * If necessary, open the fstab database, before reading+returning the next entry.
 * @return: * :   Pointer to a statically allocated fstab entry
 * @return: NULL: [errno = <unchanged>] All entries have been read
 * @return: NULL: [errno = *] Error */
__CDECLARE_OPT(__ATTR_WUNUSED,struct fstab *,__NOTHROW_NCX,getfsent,(void),())
#ifdef __CRT_HAVE_getfsspec
/* >> getfsspec(3)
 * Find and return the fstab entry with `strcmp(ent->fs_spec, special_file) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `special_file'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `special_file'
 * @return: NULL: [errno = *] Error */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),struct fstab *,__NOTHROW_NCX,getfsspec,(const char *__special_file),(__special_file))
#elif defined(__CRT_HAVE_getfsent) && defined(__CRT_HAVE_setfsent)
#include <libc/local/fstab/getfsspec.h>
/* >> getfsspec(3)
 * Find and return the fstab entry with `strcmp(ent->fs_spec, special_file) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `special_file'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `special_file'
 * @return: NULL: [errno = *] Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(getfsspec, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct fstab *__NOTHROW_NCX(__LIBCCALL getfsspec)(const char *__special_file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getfsspec))(__special_file); })
#endif /* ... */
#ifdef __CRT_HAVE_getfsfile
/* >> getfsfile(3)
 * Find and return the fstab entry with `strcmp(ent->fs_file, mount_point) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `mount_point'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `mount_point'
 * @return: NULL: [errno = *] Error */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),struct fstab *,__NOTHROW_NCX,getfsfile,(const char *__mount_point),(__mount_point))
#elif defined(__CRT_HAVE_getfsent) && defined(__CRT_HAVE_setfsent)
#include <libc/local/fstab/getfsfile.h>
/* >> getfsfile(3)
 * Find and return the fstab entry with `strcmp(ent->fs_file, mount_point) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `mount_point'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `mount_point'
 * @return: NULL: [errno = *] Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(getfsfile, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct fstab *__NOTHROW_NCX(__LIBCCALL getfsfile)(const char *__mount_point) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getfsfile))(__mount_point); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_FSTAB_H */
