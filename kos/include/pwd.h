/* HASH CRC-32:0x8899461e */
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
#ifndef _PWD_H
#define _PWD_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

/* Documentation taken from Glibc /usr/include/pwd.h */
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
/* Reasonable value for the buffer sized used in the
 * reentrant functions below. But better use `sysconf'. */
#define NSS_BUFLEN_PASSWD  1024
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
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __passwd_defined
#define __passwd_defined 1
struct passwd {
	char   *pw_name;   /* Username. */
	char   *pw_passwd; /* Password. */
	__uid_t pw_uid;    /* User ID. */
	__gid_t pw_gid;    /* Group ID. */
	char   *pw_gecos;  /* Real name. */
	char   *pw_dir;    /* Home directory. */
	char   *pw_shell;  /* Shell program. */
};
#endif /* !__passwd_defined */

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

#ifdef __CRT_HAVE_getpwuid
__CDECLARE(,struct passwd *,__NOTHROW_RPC,getpwuid,(__uid_t __uid),(__uid))
#endif /* getpwuid... */
#ifdef __CRT_HAVE_getpwnam
__CDECLARE(__ATTR_NONNULL((1)),struct passwd *,__NOTHROW_RPC,getpwnam,(char const *__name),(__name))
#endif /* getpwnam... */
#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_setpwent
/* Rewind the password-file stream */
__CDECLARE_VOID(,__NOTHROW_RPC,setpwent,(void),())
#endif /* setpwent... */
#ifdef __CRT_HAVE_endpwent
/* Close the password-file stream */
__CDECLARE_VOID(,__NOTHROW_RPC_NOKOS,endpwent,(void),())
#endif /* endpwent... */
#ifdef __CRT_HAVE_getpwent
/* Read an entry from the password-file stream, opening it if necessary */
__CDECLARE(,struct passwd *,__NOTHROW_RPC,getpwent,(void),())
#endif /* getpwent... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */
#ifdef __CRT_HAVE_getpwuid
/* Search for an entry with a matching user ID */
__CDECLARE(,struct passwd *,__NOTHROW_RPC,getpwuid,(__uid_t __uid),(__uid))
#endif /* getpwuid... */
#ifdef __CRT_HAVE_getpwnam
/* Search for an entry with a matching username */
__CDECLARE(__ATTR_NONNULL((1)),struct passwd *,__NOTHROW_RPC,getpwnam,(const char *__name),(__name))
#endif /* getpwnam... */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_fgetpwent
/* Read an entry from STREAM */
__CDECLARE(__ATTR_NONNULL((1)),struct passwd *,__NOTHROW_RPC,fgetpwent,(__FILE *__restrict __stream),(__stream))
#endif /* fgetpwent... */
#ifdef __CRT_HAVE_putpwent
/* Write the given entry onto the given stream */
__CDECLARE(,int,__NOTHROW_RPC,putpwent,(struct passwd const *__restrict __p, __FILE *__restrict __f),(__p,__f))
#endif /* putpwent... */
#endif /* __USE_MISC */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_getpwuid_r
/* Search for an entry with a matching user ID */
__CDECLARE(__ATTR_NONNULL((2, 3, 5)),int,__NOTHROW_RPC,getpwuid_r,(__uid_t ____uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(____uid,__resultbuf,__buffer,__buflen,__result))
#endif /* getpwuid_r... */
#ifdef __CRT_HAVE_getpwnam_r
/* Search for an entry with a matching username */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,getpwnam_r,(const char *__restrict __name, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__name,__resultbuf,__buffer,__buflen,__result))
#endif /* getpwnam_r... */
#ifdef __USE_MISC
#ifdef __CRT_HAVE_getpwent_r
/* Read an entry from the password-file stream, opening it if necessary */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),int,__NOTHROW_RPC,getpwent_r,(struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__resultbuf,__buffer,__buflen,__result))
#endif /* getpwent_r... */
#ifdef __CRT_HAVE_fgetpwent_r
/* Read an entry from STREAM */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,fgetpwent_r,(__FILE *__restrict __stream, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__stream,__resultbuf,__buffer,__buflen,__result))
#endif /* fgetpwent_r... */
#endif /* __USE_MISC */
#endif	/* __USE_POSIX */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_getpw
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
__CDECLARE(,int,__NOTHROW_RPC,getpw,(__uid_t __uid, char *__buffer),(__uid,__buffer))
#endif /* getpw... */
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PWD_H */
