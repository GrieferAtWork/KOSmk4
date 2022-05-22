/* HASH CRC-32:0xa4b0b76e */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/utmp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/utmp.h) */
/* (#) Portability: GNU C Library (/login/utmp.h) */
/* (#) Portability: NetBSD        (/include/utmp.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/utmp.h) */
/* (#) Portability: OpenBSD       (/include/utmp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/utmp.h) */
/* (#) Portability: diet libc     (/include/utmp.h) */
/* (#) Portability: libc4/5       (/include/utmp.h) */
/* (#) Portability: libc6         (/include/utmp.h) */
/* (#) Portability: mintlib       (/include/utmp.h) */
/* (#) Portability: musl libc     (/include/utmp.h) */
/* (#) Portability: uClibc        (/include/utmp.h) */
#ifndef _UTMP_H
#define _UTMP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/crt/db/utmp.h>
#include <bits/types.h>

#include <paths.h>

#ifdef __USE_GLIBC
#include <sys/time.h>
#include <sys/types.h>
#endif /* __USE_GLIBC */

/* Compatibility names for the strings of the canonical file names. */
#define UTMP_FILE     _PATH_UTMP
#define UTMP_FILENAME _PATH_UTMP
#define WTMP_FILE     _PATH_WTMP
#define WTMP_FILENAME _PATH_WTMP

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __login_tty_defined
#define __login_tty_defined
#ifdef __CRT_HAVE_login_tty
/* >> login_tty(3)
 * Set the given `fd' as the controlling terminal, stdin,
 * stdout,   and  stderr.  Afterwards,  `fd'  is  closed.
 * @return: 0 : Success
 * @return: * : Error */
__CDECLARE(,int,__NOTHROW_RPC_KOS,login_tty,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_login_tty */
#include <asm/os/tty.h>
#if defined(__TIOCSCTTY) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid)) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close))
#include <libc/local/utmp/login_tty.h>
/* >> login_tty(3)
 * Set the given `fd' as the controlling terminal, stdin,
 * stdout,   and  stderr.  Afterwards,  `fd'  is  closed.
 * @return: 0 : Success
 * @return: * : Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(login_tty, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC_KOS(__LIBCCALL login_tty)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(login_tty))(__fd); })
#else /* __TIOCSCTTY && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) */
#undef __login_tty_defined
#endif /* !__TIOCSCTTY || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || (!__CRT_HAVE_setsid && !__CRT_HAVE___setsid && !__CRT_HAVE___libc_setsid) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close) */
#endif /* !__CRT_HAVE_login_tty */
#endif /* !__login_tty_defined */
#if !defined(__login_defined) && defined(__CRT_HAVE_login)
#define __login_defined
/* >> login(3) */
__CDECLARE_VOID(__ATTR_IN(1),__NOTHROW_RPC_KOS,login,(struct utmp const *__entry),(__entry))
#endif /* !__login_defined && __CRT_HAVE_login */
#if !defined(__logout_defined) && defined(__CRT_HAVE_logout)
#define __logout_defined
/* >> logout(3) */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC_KOS,logout,(char const *__ut_line),(__ut_line))
#endif /* !__logout_defined && __CRT_HAVE_logout */
#if !defined(__logwtmp_defined) && defined(__CRT_HAVE_logwtmp)
#define __logwtmp_defined
/* >> logwtmp(3) */
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),__NOTHROW_RPC_KOS,logwtmp,(char const *__ut_line, char const *__ut_name, char const *__ut_host),(__ut_line,__ut_name,__ut_host))
#endif /* !__logwtmp_defined && __CRT_HAVE_logwtmp */
/* >> updwtmp(3) */
__CDECLARE_VOID_OPT(__ATTR_IN(1) __ATTR_IN(2),__NOTHROW_RPC_KOS,updwtmp,(char const *__wtmp_file, struct utmp const *__utmp),(__wtmp_file,__utmp))
/* >> utmpname(3) */
__CDECLARE_OPT(__ATTR_IN(1),int,__NOTHROW_RPC_KOS,utmpname,(char const *__file),(__file))
/* >> getutent(3), getutent_r(3) */
__CDECLARE_OPT(,struct utmp *,__NOTHROW_RPC_KOS,getutent,(void),())
/* >> setutent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_KOS,setutent,(void),())
/* >> endutent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,endutent,(void),())
/* >> getutid(3), getutid_r(3) */
__CDECLARE_OPT(__ATTR_IN(1),struct utmp *,__NOTHROW_RPC_KOS,getutid,(struct utmp const *__id),(__id))
/* >> getutline(3), getutline_r(3) */
__CDECLARE_OPT(__ATTR_IN(1),struct utmp *,__NOTHROW_RPC_KOS,getutline,(struct utmp const *__line),(__line))
#ifdef __CRT_HAVE_pututline
/* >> pututline(3) */
__CDECLARE(__ATTR_IN(1),struct utmp *,__NOTHROW_RPC_KOS,pututline,(struct utmp const *__utmp_ptr),(__utmp_ptr))
#elif defined(__CRT_HAVE__pututline)
/* >> pututline(3) */
__CREDIRECT(__ATTR_IN(1),struct utmp *,__NOTHROW_RPC_KOS,pututline,(struct utmp const *__utmp_ptr),_pututline,(__utmp_ptr))
#endif /* ... */

#ifdef __USE_MISC
/* >> getutent(3), getutent_r(3) */
__CDECLARE_OPT(__ATTR_OUT(1) __ATTR_OUT(2),int,__NOTHROW_RPC_KOS,getutent_r,(struct utmp *__buffer, struct utmp **__result),(__buffer,__result))
/* >> getutid(3), getutid_r(3) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC_KOS,getutid_r,(struct utmp const *__id, struct utmp *__buffer, struct utmp **__result),(__id,__buffer,__result))
/* >> getutline(3), getutline_r(3) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC_KOS,getutline_r,(struct utmp const *__line, struct utmp *__buffer, struct utmp **__result),(__line,__buffer,__result))
#endif /* __USE_MISC */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_UTMP_H */
