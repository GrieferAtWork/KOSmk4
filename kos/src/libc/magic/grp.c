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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(gid_t = __gid_t)]
%[default_impl_section(.text.crt.database.group)]

%{
#include <features.h>
#include <bits/types.h>


/* Documentation taken from Glibc /usr/include/grp.h */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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

#if defined(__USE_POSIX) && defined(__USE_MISC)
#define NSS_BUFLEN_GROUP    1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __group_defined
#define __group_defined 1
struct group {
	char   *gr_name;   /* Group name. */
	char   *gr_passwd; /* Password. */
	__gid_t gr_gid;    /* Group ID. */
	char  **gr_mem;    /* Member list. */
};
#endif /* !__group_defined */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

}


@@Search for an entry with a matching group ID
[[cp]] getgrgid:($gid_t gid) -> struct group *;

@@Search for an entry with a matching group name
[[cp]] getgrnam:([[nonnull]] char const *__restrict name) -> struct group *;

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
@@Rewind the group-file stream
[[cp]] setgrent:();

@@Close the group-file stream
[cp_nokos] endgrent:();

@@Read an entry from the group-file stream, opening it if necessary
[[cp]] getgrent:() -> struct group *;
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_GNU
@@Write the given entry onto the given stream
[[cp]] putgrent:([[nonnull]] struct group const *__restrict entry,
               [[nonnull]] $FILE *__restrict stream) -> int;
%#endif /* __USE_GNU */

%
%#ifdef __USE_POSIX
[doc_alias(getgrgid)][[cp]]
getgrgid_r:($gid_t gid, [[nonnull]] struct group *__restrict resultbuf,
            [[outp(buflen)]] char *__restrict buffer, size_t buflen,
            [[nonnull]] struct group **__restrict result) -> int;
[doc_alias(getgrnam)][[cp]]
getgrnam_r:([[nonnull]] char const *__restrict name,
            [[nonnull]] struct group *__restrict resultbuf,
            [[outp(buflen)]] char *__restrict buffer, size_t buflen,
            [[nonnull]] struct group **__restrict result) -> int;

%
%#ifdef __USE_GNU
[doc_alias(getgrent)][[cp]]
getgrent_r:([[nonnull]] struct group *__restrict resultbuf,
            [[outp(buflen)]] char *__restrict buffer, size_t buflen,
            [[nonnull]] struct group **__restrict result) -> int;
%#endif /* __USE_GNU */

%
%#ifdef __USE_MISC
[doc_alias(fgetgrent)][[cp]]
fgetgrent_r:([[nonnull]] $FILE *__restrict stream,
             [[nonnull]] struct group *__restrict resultbuf,
             [[outp(buflen)]] char *__restrict buffer, size_t buflen,
             [[nonnull]] struct group **__restrict result) -> int;
%#endif /* __USE_MISC */
%#endif /* __USE_POSIX */

%
%#ifdef __USE_MISC
@@Read a group entry from STREAM
[[cp]] fgetgrent:([[nonnull]] $FILE *__restrict stream) -> struct group *;

@@Set the group set for the current user to GROUPS (N of them)
[[cp]] setgroups:(size_t count, [inp_opt(count)] $gid_t const *groups) -> int;

@@Store at most *NGROUPS members of the group set for USER into
@@*GROUPS. Also include GROUP. The actual number of groups found is
@@returned in *NGROUPS.  Return -1 if the if *NGROUPS is too small
[[cp]] getgrouplist:([[nonnull]] char const *user, $gid_t group,
                   [outp(*ngroups)] $gid_t *groups, [[nonnull]] int *ngroups) -> int;

@@Initialize the group set for the current user
@@by reading the group database and using all groups
@@of which USER is a member. Also include GROUP.
[[cp]] initgroups:([[nonnull]] char const *user, $gid_t group) -> int;
%#endif /* __USE_MISC */


%{
#endif /* __CC__ */

__SYSDECL_END

}