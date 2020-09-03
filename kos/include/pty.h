/* HASH CRC-32:0xebea3de9 */
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
#ifndef _PTY_H
#define _PTY_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <termios.h>
#include <bits/types.h>
#include <sys/ioctl.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/pty.h */
/* Functions for pseudo TTY handling.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

#ifdef __CC__

struct termios;
struct winsize;

#ifndef __openpty_defined
#define __openpty_defined 1
#ifdef __CRT_HAVE_openpty
/* Create pseudo tty master slave pair with NAME and set terminal
 * attributes according to TERMP and WINP and return handles for
 * both ends in AMASTER and ASLAVE */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,openpty,(__fd_t *__amaster, __fd_t *__aslave, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__aslave,__name,__termp,__winp))
#else /* __CRT_HAVE_openpty */
#undef __openpty_defined
#endif /* !__CRT_HAVE_openpty */
#endif /* !__openpty_defined */
#ifndef __forkpty_defined
#define __forkpty_defined 1
#ifdef __CRT_HAVE_forkpty
/* Create child process and establish the slave pseudo
 * terminal as the child's controlling terminal */
__CDECLARE(__ATTR_NONNULL((1)),__pid_t,__NOTHROW_NCX,forkpty,(__fd_t *__amaster, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__name,__termp,__winp))
#elif defined(__CRT_HAVE_openpty) && (defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)) && defined(__CRT_HAVE_login_tty) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit))
#include <libc/local/pty/forkpty.h>
/* Create child process and establish the slave pseudo
 * terminal as the child's controlling terminal */
__NAMESPACE_LOCAL_USING_OR_IMPL(forkpty, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __pid_t __NOTHROW_NCX(__LIBCCALL forkpty)(__fd_t *__amaster, char *__name, struct termios const *__termp, struct winsize const *__winp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(forkpty))(__amaster, __name, __termp, __winp); })
#else /* ... */
#undef __forkpty_defined
#endif /* !... */
#endif /* !__forkpty_defined */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PTY_H */
