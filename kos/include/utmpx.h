/* HASH CRC-32:0x6df65d9c */
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
#ifndef _UTMPX_H
#define _UTMPX_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/db/utmpx.h>
#include <bits/types.h>
#include <sys/time.h>

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

#ifdef __USE_GNU
/* Compatibility names for the strings of the canonical file names.  */
#define UTMPX_FILE     _PATH_UTMPX
#define UTMPX_FILENAME _PATH_UTMPX
#define WTMPX_FILE     _PATH_WTMPX
#define WTMPX_FILENAME _PATH_WTMPX
#endif /* __USE_GNU */

#ifdef __CC__

#ifdef __USE_GNU
struct utmp;
#endif /* __USE_GNU */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

/* Open user accounting database */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setutxent,(void),())
/* Close user accounting database */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endutxent,(void),())
/* Get the next entry from the user accounting database */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,getutxent,(void),())
/* Get the user accounting database entry corresponding to ID */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,getutxid,(struct utmpx const *__id),(__id))
/* Get the user accounting database entry corresponding to LINE */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,getutxline,(struct utmpx const *__line),(__line))
/* Write the entry UTMPX into the user accounting database */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,pututxline,(struct utmpx const *__utmpx),(__utmpx))

#ifdef __USE_GNU
/* Change name of the utmpx file to be examined.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,utmpxname,(char const *__file),(__file))
/* Append entry UTMP to the wtmpx-like file WTMPX_FILE.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,updwtmpx,(char const *__wtmpx_file, struct utmpx const *__utmpx),(__wtmpx_file,__utmpx))
/* Copy the information in UTMPX to UTMP.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,getutmp,(struct utmpx const *__utmpx, struct utmp *__utmp),(__utmpx,__utmp))
/* Copy the information in UTMP to UTMPX.
 * This function is not part of POSIX and therefore no official cancellation point */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,getutmpx,(struct utmp const *__utmp, struct utmpx *__utmpx),(__utmp,__utmpx))
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_UTMPX_H */
