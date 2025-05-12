/* HASH CRC-32:0x9adc48d0 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: DragonFly BSD (/include/readpassphrase.h) */
/* (#) Portability: FreeBSD       (/include/readpassphrase.h) */
/* (#) Portability: OpenBSD       (/include/readpassphrase.h) */
/* (#) Portability: libbsd        (/include/bsd/readpassphrase.h) */
#ifndef _READPASSPHRASE_H
#define _READPASSPHRASE_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/crt/readpassphrase.h>
#include <hybrid/typecore.h>

#ifdef __INTELLISENSE__
#include <bits/types/size_t.h>
#endif /* __INTELLISENSE__ */


/* Flags for use with `readpassphrase(3)::flags' */
#if !defined(RPP_ECHO_OFF) && defined(__RPP_ECHO_OFF)
#define RPP_ECHO_OFF    __RPP_ECHO_OFF    /* Disable echo. */
#endif /* !RPP_ECHO_OFF && __RPP_ECHO_OFF */
#if !defined(RPP_ECHO_ON) && defined(__RPP_ECHO_ON)
#define RPP_ECHO_ON     __RPP_ECHO_ON     /* Don't disable echo (but leave it on). */
#endif /* !RPP_ECHO_ON && __RPP_ECHO_ON */
#if !defined(RPP_REQUIRE_TTY) && defined(__RPP_REQUIRE_TTY)
#define RPP_REQUIRE_TTY __RPP_REQUIRE_TTY /* Error out if `!isatty()' */
#endif /* !RPP_REQUIRE_TTY && __RPP_REQUIRE_TTY */
#if !defined(RPP_FORCELOWER) && defined(__RPP_FORCELOWER)
#define RPP_FORCELOWER  __RPP_FORCELOWER  /* Force all input to be lower-case. */
#endif /* !RPP_FORCELOWER && __RPP_FORCELOWER */
#if !defined(RPP_FORCEUPPER) && defined(__RPP_FORCEUPPER)
#define RPP_FORCEUPPER  __RPP_FORCEUPPER  /* Force all input to be upper-case. */
#endif /* !RPP_FORCEUPPER && __RPP_FORCEUPPER */
#if !defined(RPP_SEVENBIT) && defined(__RPP_SEVENBIT)
#define RPP_SEVENBIT    __RPP_SEVENBIT    /* Mask input with `0x7f' */
#endif /* !RPP_SEVENBIT && __RPP_SEVENBIT */
#if !defined(RPP_STDIN) && defined(__RPP_STDIN)
#define RPP_STDIN       __RPP_STDIN       /* Use `STDIN_FILENO' as input and `STDERR_FILENO' as output, rather than `/dev/tty' */
#endif /* !RPP_STDIN && __RPP_STDIN */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __CRT_HAVE_readpassphrase
/* >> readpassphrase(3)
 * @param: flags: Set of `RPP_*' (from `<readpassphrase.h>')
 * @return: buf:  Success
 * @return: NULL: Error (s.a. `errno') */
__CDECLARE(__ATTR_IN_OPT(1) __ATTR_OUTS(2, 3),char *,__NOTHROW_NCX,readpassphrase,(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags),(__prompt,__buf,__bufsize,__flags))
#else /* __CRT_HAVE_readpassphrase */
#include <asm/os/stdio.h>
#if defined(__STDIN_FILENO) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read))
#include <libc/local/readpassphrase/readpassphrase.h>
/* >> readpassphrase(3)
 * @param: flags: Set of `RPP_*' (from `<readpassphrase.h>')
 * @return: buf:  Success
 * @return: NULL: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(readpassphrase, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_OUTS(2, 3) char *__NOTHROW_NCX(__LIBCCALL readpassphrase)(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readpassphrase))(__prompt, __buf, __bufsize, __flags); })
#endif /* __STDIN_FILENO && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) */
#endif /* !__CRT_HAVE_readpassphrase */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_READPASSPHRASE_H */
