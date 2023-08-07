/* HASH CRC-32:0xada31ce3 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: NetBSD  (/include/util.h) */
/* (#) Portability: OpenBSD (/lib/libutil/util.h) */
#ifndef _UTIL_H
#define _UTIL_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */


#include <features.h>

#include <asm/crt/util.h>
#include <bits/types.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>
#include <termios.h>


__SYSDECL_BEGIN

/* Options for the `dflags' argument to `opendev(3)' */
#if !defined(OPENDEV_PART) && defined(__OPENDEV_PART)
#define OPENDEV_PART __OPENDEV_PART /* Attempt to open a raw partition during expansion. */
#endif /* !OPENDEV_PART && __OPENDEV_PART */
#if !defined(OPENDEV_BLCK) && defined(__OPENDEV_BLCK)
#define OPENDEV_BLCK __OPENDEV_BLCK /* Open a block device (rather than a character device). */
#endif /* !OPENDEV_BLCK && __OPENDEV_BLCK */

/* Options for the `flags' argument to `fparseln(3)' */
#if !defined(FPARSELN_UNESCESC) && defined(__FPARSELN_UNESCESC)
#define FPARSELN_UNESCESC  __FPARSELN_UNESCESC  /* Remove escape before an escaped escape. */
#endif /* !FPARSELN_UNESCESC && __FPARSELN_UNESCESC */
#if !defined(FPARSELN_UNESCCONT) && defined(__FPARSELN_UNESCCONT)
#define FPARSELN_UNESCCONT __FPARSELN_UNESCCONT /* Remove escape before an escaped continuation. */
#endif /* !FPARSELN_UNESCCONT && __FPARSELN_UNESCCONT */
#if !defined(FPARSELN_UNESCCOMM) && defined(__FPARSELN_UNESCCOMM)
#define FPARSELN_UNESCCOMM __FPARSELN_UNESCCOMM /* Remove escape before an escaped comment. */
#endif /* !FPARSELN_UNESCCOMM && __FPARSELN_UNESCCOMM */
#if !defined(FPARSELN_UNESCREST) && defined(__FPARSELN_UNESCREST)
#define FPARSELN_UNESCREST __FPARSELN_UNESCREST /* Remove escape before some other character.*/
#endif /* !FPARSELN_UNESCREST && __FPARSELN_UNESCREST */
#if !defined(FPARSELN_UNESCALL) && defined(__FPARSELN_UNESCALL)
#define FPARSELN_UNESCALL __FPARSELN_UNESCALL /* Remove all escape prefixes */
#endif /* !FPARSELN_UNESCALL && __FPARSELN_UNESCALL */

#ifdef __CC__
struct utmp;
struct termios;
struct winsize;
struct iovec;

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


#if !defined(__login_defined) && defined(__CRT_HAVE_login)
#define __login_defined
/* >> login(3) */
__CDECLARE_VOID(__ATTR_IN(1),__NOTHROW_RPC_KOS,login,(struct utmp const *__entry),(__entry))
#endif /* !__login_defined && __CRT_HAVE_login */
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
/* >> opendev(3)
 * @param: dflags: Set of `0 | OPENDEV_PART | OPENDEV_BLCK' */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(4),__fd_t,__NOTHROW_RPC,opendev,(char const *__path, __oflag_t __oflags, __STDC_INT_AS_UINT_T __dflags, char **__realpath),(__path,__oflags,__dflags,__realpath))
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
#ifndef __fparseln_defined
#define __fparseln_defined
#ifdef __CRT_HAVE_fparseln
/* >> fparseln(3)
 * Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line,  that must  be `free(3)'ed by  the caller once  they are done
 *                  using it.
 *                  If the result would be empty  as the result of `feof(stream)'  upon
 *                  return of this function, `strdup("")' will be returned. (i.e.  NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),char *,__NOTHROW_CB,fparseln,(__FILE *__stream, size_t *__plen, size_t *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags),(__stream,__plen,__plineno,__delim,__flags))
#elif (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/util/fparseln.h>
/* >> fparseln(3)
 * Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line,  that must  be `free(3)'ed by  the caller once  they are done
 *                  using it.
 *                  If the result would be empty  as the result of `feof(stream)'  upon
 *                  return of this function, `strdup("")' will be returned. (i.e.  NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fparseln, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3) char *__NOTHROW_CB(__LIBCCALL fparseln)(__FILE *__stream, size_t *__plen, size_t *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fparseln))(__stream, __plen, __plineno, __delim, __flags); })
#else /* ... */
#undef __fparseln_defined
#endif /* !... */
#endif /* !__fparseln_defined */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_UTIL_H */
