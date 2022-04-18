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
%(c_prefix){
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
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(gid_t = __gid_t)]
%[default:section(".text.crt{|.dos}.database.group")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/db/group.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

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

}


@@>> getgrgid(3), getgrgid_r(3)
[[cp, decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
struct group *getgrgid($gid_t gid);

@@>> getgrnam(3), getgrnam_r(3)
[[cp, decl_include("<bits/crt/db/group.h>")]]
struct group *getgrnam([[nonnull]] char const *__restrict name);

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
@@>> setgrent(3)
[[cp]]
void setgrent();

@@>> endgrent(3)
[[cp_nokos]]
void endgrent();

@@>> getgrent(3), getgrent_r(3)
[[cp, decl_include("<bits/crt/db/group.h>")]]
struct group *getgrent();
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_GNU
@@>> putgrent(3)
[[cp, decl_include("<bits/crt/db/group.h>")]]
int putgrent([[nonnull]] struct group const *__restrict entry,
             [[nonnull]] $FILE *__restrict stream);
%#endif /* __USE_GNU */

%
%#ifdef __USE_POSIX
[[cp, doc_alias("getgrgid"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int getgrgid_r($gid_t gid, [[nonnull]] struct group *__restrict resultbuf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct group **__restrict result);

[[cp, doc_alias("getgrnam"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int getgrnam_r([[nonnull]] char const *__restrict name,
               [[nonnull]] struct group *__restrict resultbuf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct group **__restrict result);

%
%#ifdef __USE_GNU
[[cp, doc_alias("getgrent"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int getgrent_r([[nonnull]] struct group *__restrict resultbuf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct group **__restrict result);
%#endif /* __USE_GNU */

%
%#ifdef __USE_MISC
[[cp, doc_alias("fgetgrent"), decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int fgetgrent_r([[nonnull]] $FILE *__restrict stream,
                [[nonnull]] struct group *__restrict resultbuf,
                [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                [[nonnull]] struct group **__restrict result);
%#endif /* __USE_MISC */
%#endif /* __USE_POSIX */

%
%#ifdef __USE_MISC
@@>> fgetgrent(3), fgetgrent_r(3)
[[cp, decl_include("<bits/crt/db/group.h>")]]
struct group *fgetgrent([[nonnull]] $FILE *__restrict stream);

@@>> setgroups(2)
[[cp, guard, decl_include("<bits/types.h>")]]
[[export_alias("__setgroups", "__libc_setgroups")]]
int setgroups(size_t count, [[inp_opt(count)]] $gid_t const *groups);

@@>> getgrouplist(3)
[[cp, guard, decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int getgrouplist([[nonnull]] char const *user, $gid_t group,
                 [[outp(*ngroups)]] $gid_t *groups,
                 [[nonnull]] int *ngroups);

@@>> initgroups(3)
[[cp, guard, decl_include("<bits/crt/db/group.h>", "<bits/types.h>")]]
int initgroups([[nonnull]] char const *user, $gid_t group);
%#endif /* __USE_MISC */


%{

__SYSDECL_END
#endif /* __CC__ */

}
