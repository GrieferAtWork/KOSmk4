/* HASH CRC-32:0xa8f82f43 */
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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/utmpx.h) */
/* (#) Portability: FreeBSD       (/include/utmpx.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/utmpx.h) */
/* (#) Portability: NetBSD        (/include/utmpx.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/utmpx.h) */
/* (#) Portability: diet libc     (/include/utmpx.h) */
/* (#) Portability: libc6         (/include/utmpx.h) */
/* (#) Portability: musl libc     (/include/utmpx.h) */
/* (#) Portability: uClibc        (/include/utmpx.h) */
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


#ifdef __USE_GNU
/* Compatibility names for the strings of the canonical file names.  */
#if !defined(UTMPX_FILE) && defined(_PATH_UTMPX)
#define UTMPX_FILE     _PATH_UTMPX
#endif /* !UTMPX_FILE && _PATH_UTMPX */
#if !defined(UTMPX_FILENAME) && defined(_PATH_UTMPX)
#define UTMPX_FILENAME _PATH_UTMPX
#endif /* !UTMPX_FILENAME && _PATH_UTMPX */
#if !defined(WTMPX_FILE) && defined(_PATH_WTMPX)
#define WTMPX_FILE     _PATH_WTMPX
#endif /* !WTMPX_FILE && _PATH_WTMPX */
#if !defined(WTMPX_FILENAME) && defined(_PATH_WTMPX)
#define WTMPX_FILENAME _PATH_WTMPX
#endif /* !WTMPX_FILENAME && _PATH_WTMPX */
#endif /* __USE_GNU */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __USE_GNU
struct utmp;
#endif /* __USE_GNU */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

/* >> setutxent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setutxent,(void),())
/* >> endutxent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endutxent,(void),())
/* >> getutxent(3) */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,getutxent,(void),())
/* >> getutxid(3) */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,getutxid,(struct utmpx const *__id),(__id))
/* >> getutxline(3) */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,getutxline,(struct utmpx const *__line),(__line))
/* >> pututxline(3) */
__CDECLARE_OPT(,struct utmpx *,__NOTHROW_RPC,pututxline,(struct utmpx const *__utmpx),(__utmpx))

#ifdef __USE_GNU
/* >> utmpxname(3) */
__CDECLARE_OPT(,int,__NOTHROW_RPC,utmpxname,(char const *__file),(__file))
/* >> updwtmpx(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,updwtmpx,(char const *__wtmpx_file, struct utmpx const *__utmpx),(__wtmpx_file,__utmpx))
/* >> getutmp(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,getutmp,(struct utmpx const *__utmpx, struct utmp *__utmp),(__utmpx,__utmp))
/* >> getutmpx(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,getutmpx,(struct utmp const *__utmp, struct utmpx *__utmpx),(__utmp,__utmpx))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_UTMPX_H */
