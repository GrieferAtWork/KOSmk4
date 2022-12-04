/* HASH CRC-32:0x675bd706 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/pty.h) */
/* (#) Portability: GNU C Library (/login/pty.h) */
/* (#) Portability: diet libc     (/include/pty.h) */
/* (#) Portability: libc6         (/include/pty.h) */
/* (#) Portability: mintlib       (/include/pty.h) */
/* (#) Portability: musl libc     (/include/pty.h) */
/* (#) Portability: uClibc        (/include/pty.h) */
#ifndef _PTY_H
#define _PTY_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/types.h>
#include <sys/ioctl.h>

#include <termios.h>

#ifdef __CC__
__SYSDECL_BEGIN

struct termios;
struct winsize;

#if !defined(__openpty_defined) && defined(__CRT_HAVE_openpty)
#define __openpty_defined
/* >> openpty(2)
 * Create  a  new  ptty (psuedo  tty),  storing the  handles  for the
 * master/slave adapters in  `*amaster' and `*aslave'.  Additionally,
 * the caller  may specific  the  initial terminal  settings  `termp'
 * and  window size  `winp', as well  as a location  where the kernel
 * should store the  filename of  the PTY master  socket (as  already
 * returned in `*amaster'). Note that the max length of this filename
 * is implementation defined, with no way for the use to specify  how
 * much space is available in the passed buffer. As such, a  portable
 * application can only ever pass `NULL' for this value.
 *
 * On KOS, the value written to `name' is the absolute filename of
 * the master-device in the `/dev' filesystem, which usually means
 * that the written filename is something like `/dev/ptyp0'.
 *
 * NOTE: On KOS, this function is a system call, though in other
 *       operating system it is often implemented via `open(2)',
 *       possibly combined with `ioctl(2)'. */
__CDECLARE(__ATTR_IN_OPT(4) __ATTR_IN_OPT(5) __ATTR_OUT(1) __ATTR_OUT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,openpty,(__fd_t *__amaster, __fd_t *__aslave, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__aslave,__name,__termp,__winp))
#endif /* !__openpty_defined && __CRT_HAVE_openpty */
#ifndef __forkpty_defined
#define __forkpty_defined
#ifdef __CRT_HAVE_forkpty
/* >> forkpty(3)
 * A helper for combining `openpty(2)' with `fork(2)' and `login_tty(3)',
 * such  that  the newly  created PTY  is open  under all  std-handles in
 * the newly created child process.
 * Aside from this, this function returns the same as fork(2), that  is
 * it returns in  both the  parent and child  processes, returning  `0'
 * for the child, and the child's PID for the parent (or -1 in only the
 * parent if something went wrong) */
__CDECLARE(__ATTR_IN(3) __ATTR_IN(4) __ATTR_OUT(1) __ATTR_OUT_OPT(2),__pid_t,__NOTHROW_NCX,forkpty,(__fd_t *__amaster, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__name,__termp,__winp))
#else /* __CRT_HAVE_forkpty */
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_openpty) && (defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)) && (defined(__CRT_HAVE_login_tty) || (defined(__TIOCSCTTY) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid)) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2)))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit))
#include <libc/local/pty/forkpty.h>
/* >> forkpty(3)
 * A helper for combining `openpty(2)' with `fork(2)' and `login_tty(3)',
 * such  that  the newly  created PTY  is open  under all  std-handles in
 * the newly created child process.
 * Aside from this, this function returns the same as fork(2), that  is
 * it returns in  both the  parent and child  processes, returning  `0'
 * for the child, and the child's PID for the parent (or -1 in only the
 * parent if something went wrong) */
__NAMESPACE_LOCAL_USING_OR_IMPL(forkpty, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __ATTR_OUT(1) __ATTR_OUT_OPT(2) __pid_t __NOTHROW_NCX(__LIBCCALL forkpty)(__fd_t *__amaster, char *__name, struct termios const *__termp, struct winsize const *__winp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(forkpty))(__amaster, __name, __termp, __winp); })
#else /* __CRT_HAVE_openpty && (__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) && (__CRT_HAVE_login_tty || (__TIOCSCTTY && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2))) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) */
#undef __forkpty_defined
#endif /* !__CRT_HAVE_openpty || (!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close) || (!__CRT_HAVE_login_tty && (!__TIOCSCTTY || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || (!__CRT_HAVE_setsid && !__CRT_HAVE___setsid && !__CRT_HAVE___libc_setsid) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2))) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) */
#endif /* !__CRT_HAVE_forkpty */
#endif /* !__forkpty_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PTY_H */
