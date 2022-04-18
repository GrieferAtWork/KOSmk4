/* HASH CRC-32:0x3320e392 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/grp.h) */
/* (#) Portability: DJGPP         (/include/grp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/grp.h) */
/* (#) Portability: FreeBSD       (/include/grp.h) */
/* (#) Portability: GNU C Library (/grp/grp.h) */
/* (#) Portability: NetBSD        (/include/grp.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/grp.h) */
/* (#) Portability: OpenBSD       (/include/grp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/grp.h) */
/* (#) Portability: diet libc     (/include/grp.h) */
/* (#) Portability: libbsd        (/include/bsd/grp.h) */
/* (#) Portability: libc4/5       (/include/grp.h) */
/* (#) Portability: libc6         (/include/grp.h) */
/* (#) Portability: mintlib       (/include/grp.h) */
/* (#) Portability: musl libc     (/include/grp.h) */
/* (#) Portability: uClibc        (/include/grp.h) */
#ifndef _GRP_H
#define _GRP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/db/group.h>
#include <bits/types.h>

#if defined(__USE_POSIX) && defined(__USE_MISC)
#define NSS_BUFLEN_GROUP 1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

/* >> getgrgid(3), getgrgid_r(3) */
__CDECLARE_OPT(,struct group *,__NOTHROW_RPC,getgrgid,(__gid_t __gid),(__gid))
/* >> getgrnam(3), getgrnam_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct group *,__NOTHROW_RPC,getgrnam,(char const *__restrict __name),(__name))

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* >> setgrent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setgrent,(void),())
/* >> endgrent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endgrent,(void),())
/* >> getgrent(3), getgrent_r(3) */
__CDECLARE_OPT(,struct group *,__NOTHROW_RPC,getgrent,(void),())
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_GNU
/* >> putgrent(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,putgrent,(struct group const *__restrict __entry, __FILE *__restrict __stream),(__entry,__stream))
#endif /* __USE_GNU */

#ifdef __USE_POSIX
/* >> getgrgid(3), getgrgid_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3, 5)),int,__NOTHROW_RPC,getgrgid_r,(__gid_t __gid, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__gid,__resultbuf,__buffer,__buflen,__result))
/* >> getgrnam(3), getgrnam_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,getgrnam_r,(char const *__restrict __name, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__name,__resultbuf,__buffer,__buflen,__result))

#ifdef __USE_GNU
/* >> getgrent(3), getgrent_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 4)),int,__NOTHROW_RPC,getgrent_r,(struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__resultbuf,__buffer,__buflen,__result))
#endif /* __USE_GNU */

#ifdef __USE_MISC
/* >> fgetgrent(3), fgetgrent_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,fgetgrent_r,(__FILE *__restrict __stream, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__stream,__resultbuf,__buffer,__buflen,__result))
#endif /* __USE_MISC */
#endif /* __USE_POSIX */

#ifdef __USE_MISC
/* >> fgetgrent(3), fgetgrent_r(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct group *,__NOTHROW_RPC,fgetgrent,(__FILE *__restrict __stream),(__stream))
#ifndef __setgroups_defined
#define __setgroups_defined
#ifdef __CRT_HAVE_setgroups
/* >> setgroups(2) */
__CDECLARE(,int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),(__count,__groups))
#elif defined(__CRT_HAVE___setgroups)
/* >> setgroups(2) */
__CREDIRECT(,int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),__setgroups,(__count,__groups))
#elif defined(__CRT_HAVE___libc_setgroups)
/* >> setgroups(2) */
__CREDIRECT(,int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),__libc_setgroups,(__count,__groups))
#else /* ... */
#undef __setgroups_defined
#endif /* !... */
#endif /* !__setgroups_defined */
#if !defined(__getgrouplist_defined) && defined(__CRT_HAVE_getgrouplist)
#define __getgrouplist_defined
/* >> getgrouplist(3) */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),int,__NOTHROW_RPC,getgrouplist,(char const *__user, __gid_t __group, __gid_t *__groups, int *__ngroups),(__user,__group,__groups,__ngroups))
#endif /* !__getgrouplist_defined && __CRT_HAVE_getgrouplist */
#if !defined(__initgroups_defined) && defined(__CRT_HAVE_initgroups)
#define __initgroups_defined
/* >> initgroups(3) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,initgroups,(char const *__user, __gid_t __group),(__user,__group))
#endif /* !__initgroups_defined && __CRT_HAVE_initgroups */
#endif /* __USE_MISC */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_GRP_H */
