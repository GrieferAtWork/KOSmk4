/* HASH CRC-32:0x6735b773 */
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
#ifndef _UTMP_H
#define _UTMP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/types.h>
#include <bits/utmp.h>

/* Documentation taken from Glibc /usr/include/utmp.h */
/* Copyright (C) 1993-2016 Free Software Foundation, Inc.
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

/* Compatibility names for the strings of the canonical file names. */
#define UTMP_FILE      _PATH_UTMP
#define UTMP_FILENAME  _PATH_UTMP
#define WTMP_FILE      _PATH_WTMP
#define WTMP_FILENAME  _PATH_WTMP

#ifdef __CC__
#if defined(__CRT_HAVE_login_tty)
/* Make FD be the controlling terminal, stdin, stdout, and stderr;
 * then close FD. Returns 0 on success, nonzero on error */
__CDECLARE(,int,__NOTHROW_RPC_KOS,login_tty,(__fd_t __fd),(__fd))
#endif /* login_tty... */
#if defined(__CRT_HAVE_login)
/* Write the given entry into utmp and wtmp */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC_KOS,login,(struct utmp const *__entry),(__entry))
#endif /* login... */
#if defined(__CRT_HAVE_logout)
/* Write the utmp entry to say the user on UT_LINE has logged out */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_KOS,logout,(char const *__ut_line),(__ut_line))
#endif /* logout... */
#if defined(__CRT_HAVE_logwtmp)
/* Append to wtmp an entry for the current time and the given info */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_RPC_KOS,logwtmp,(char const *__ut_line, char const *__ut_name, char const *__ut_host),(__ut_line,__ut_name,__ut_host))
#endif /* logwtmp... */
#if defined(__CRT_HAVE_updwtmp)
/* Append entry UTMP to the wtmp-like file WTMP_FILE */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_RPC_KOS,updwtmp,(char const *__wtmp_file, struct utmp const *__utmp),(__wtmp_file,__utmp))
#endif /* updwtmp... */
#if defined(__CRT_HAVE_utmpname)
/* Change name of the utmp file to be examined */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_KOS,utmpname,(char const *__file),(__file))
#endif /* utmpname... */
#if defined(__CRT_HAVE_getutent)
/* Read next entry from a utmp-like file */
__CDECLARE(,struct utmp *,__NOTHROW_RPC_KOS,getutent,(void),())
#endif /* getutent... */
#if defined(__CRT_HAVE_setutent)
/* Reset the input stream to the beginning of the file */
__CDECLARE_VOID(,__NOTHROW_RPC_KOS,setutent,(void),())
#endif /* setutent... */
#if defined(__CRT_HAVE_endutent)
/* Close the current open file */
__CDECLARE_VOID(,__NOTHROW_NCX,endutent,(void),())
#endif /* endutent... */
#if defined(__CRT_HAVE_getutid)
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_type matching ID->ut_type */
__CDECLARE(__ATTR_NONNULL((1)),struct utmp *,__NOTHROW_RPC_KOS,getutid,(struct utmp const *__id),(__id))
#endif /* getutid... */
#if defined(__CRT_HAVE_getutline)
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_line matching LINE->ut_line */
__CDECLARE(__ATTR_NONNULL((1)),struct utmp *,__NOTHROW_RPC_KOS,getutline,(struct utmp const *__line),(__line))
#endif /* getutline... */
#if defined(__CRT_HAVE_pututline)
/* Write out entry pointed to by UTMP_PTR into the utmp file */
__CDECLARE(__ATTR_NONNULL((1)),struct utmp *,__NOTHROW_RPC_KOS,pututline,(struct utmp const *__utmp_ptr),(__utmp_ptr))
#endif /* pututline... */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_getutent_r)
/* Reentrant versions of the file for handling utmp files */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC_KOS,getutent_r,(struct utmp *__buffer, struct utmp **__result),(__buffer,__result))
#endif /* getutent_r... */
#if defined(__CRT_HAVE_getutid_r)
/* Reentrant versions of the file for handling utmp files */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC_KOS,getutid_r,(struct utmp const *__id, struct utmp *__buffer, struct utmp **__result),(__id,__buffer,__result))
#endif /* getutid_r... */
#if defined(__CRT_HAVE_getutline_r)
/* Reentrant versions of the file for handling utmp files */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC_KOS,getutline_r,(struct utmp const *__line, struct utmp *__buffer, struct utmp **__result),(__line,__buffer,__result))
#endif /* getutline_r... */
#endif /* __USE_MISC */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_UTMP_H */
