/* HASH CRC-32:0x542d83ef */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SHADOW_H
#define _SHADOW_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <paths.h>

/* Documentation taken from Glibc /usr/include/shadow.h */
/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

/* Paths to the user database files.  */
#define SHADOW _PATH_SHADOW

#ifdef __CC__

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

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


/* Structure of the password file.  */
struct spwd {
	char             *sp_namp;    /* Login name. */
	char             *sp_pwdp;    /* Encrypted password. */
	__LONGPTR_TYPE__  sp_lstchg;  /* Date of last change. */
	__LONGPTR_TYPE__  sp_min;     /* Minimum number of days between changes. */
	__LONGPTR_TYPE__  sp_max;     /* Maximum number of days between changes. */
	__LONGPTR_TYPE__  sp_warn;    /* Number of days to warn user to change the password. */
	__LONGPTR_TYPE__  sp_inact;   /* Number of days the account may be inactive. */
	__LONGPTR_TYPE__  sp_expire;  /* Number of days since 1970-01-01 until account expires. */
	__ULONGPTR_TYPE__ sp_flag;    /* Reserved. */
};

#if defined(__CRT_HAVE_setspent)
/* Open database for reading.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE_VOID(,__NOTHROW_RPC,setspent,(void),())
#endif /* setspent... */
#if defined(__CRT_HAVE_endspent)
/* Close database. */
__CDECLARE_VOID(,__NOTHROW_RPC_NOKOS,endspent,(void),())
#endif /* endspent... */
#if defined(__CRT_HAVE_getspent)
/* Get next entry from database, perhaps after opening the file.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE(,struct spwd *,__NOTHROW_RPC,getspent,(void),())
#endif /* getspent... */
#if defined(__CRT_HAVE_getspnam)
/* Get shadow entry matching NAME.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1)),struct spwd *,__NOTHROW_RPC,getspnam,(char const *__restrict __name),(__name))
#endif /* getspnam... */
#if defined(__CRT_HAVE_sgetspent)
/* Read shadow entry from STRING.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1)),struct spwd *,__NOTHROW_RPC,sgetspent,(char const *__restrict __string),(__string))
#endif /* sgetspent... */
#if defined(__CRT_HAVE_fgetspent)
/* Read next shadow entry from STREAM.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1)),struct spwd *,__NOTHROW_RPC,fgetspent,(__FILE *__restrict __stream),(__stream))
#endif /* fgetspent... */
#if defined(__CRT_HAVE_putspent)
/* Write line containing shadow password entry to stream.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,putspent,(struct spwd const *__restrict __p, __FILE *__restrict __stream),(__p,__stream))
#endif /* putspent... */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_getspent_r)
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),int,__NOTHROW_RPC,getspent_r,(struct spwd *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct spwd **__restrict __result),(__result_buf,__buffer,__buflen,__result))
#endif /* getspent_r... */
#if defined(__CRT_HAVE_getspnam_r)
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,getspnam_r,(char const *__restrict __name, struct spwd *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct spwd **__restrict __result),(__name,__result_buf,__buffer,__buflen,__result))
#endif /* getspnam_r... */
#if defined(__CRT_HAVE_sgetspent_r)
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,sgetspent_r,(char const *__restrict __string, struct spwd *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct spwd **__restrict __result),(__string,__result_buf,__buffer,__buflen,__result))
#endif /* sgetspent_r... */
#if defined(__CRT_HAVE_fgetspent_r)
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,fgetspent_r,(__FILE *__restrict __stream, struct spwd *__restrict __result_buf, char *__restrict __buffer, size_t __buflen, struct spwd **__restrict __result),(__stream,__result_buf,__buffer,__buflen,__result))
#endif /* fgetspent_r... */
#endif /* __USE_MISC */

/* The simple locking functionality provided here is not suitable for multi-threaded applications.  */

#if defined(__CRT_HAVE_lckpwdf)
/* Protect password file against multi writers */
__CDECLARE(,int,__NOTHROW_RPC_KOS,lckpwdf,(void),())
#endif /* lckpwdf... */
#if defined(__CRT_HAVE_ulckpwdf)
/* Unlock password file */
__CDECLARE(,int,__NOTHROW_NCX,ulckpwdf,(void),())
#endif /* ulckpwdf... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SHADOW_H */
