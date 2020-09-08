/* HASH CRC-32:0x8fda8d31 */
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

/*#include <sys/types.h>*/
/*#include <stdio.h>*/
/*#include <pwd.h>*/
/*#include <termios.h>*/

__SYSDECL_BEGIN

/* Options for the `dflags' argument to `opendev(3)' */
#ifdef __OPENDEV_PART
#define OPENDEV_PART __OPENDEV_PART /* Attempt to open a raw partition during expansion. */
#endif /* __OPENDEV_PART */
#ifdef __OPENDEV_BLCK
#define OPENDEV_BLCK __OPENDEV_BLCK /* Open a block device (rather than a character device). */
#endif /* __OPENDEV_BLCK */

/* Options for the `flags' argument to `fparseln(3)' */
#ifdef __FPARSELN_UNESCESC
#define FPARSELN_UNESCESC  __FPARSELN_UNESCESC  /* Remove escape before an escaped escape. */
#endif /* __FPARSELN_UNESCESC */
#ifdef __FPARSELN_UNESCCONT
#define FPARSELN_UNESCCONT __FPARSELN_UNESCCONT /* Remove escape before an escaped continuation. */
#endif /* __FPARSELN_UNESCCONT */
#ifdef __FPARSELN_UNESCCOMM
#define FPARSELN_UNESCCOMM __FPARSELN_UNESCCOMM /* Remove escape before an escaped comment. */
#endif /* __FPARSELN_UNESCCOMM */
#ifdef __FPARSELN_UNESCREST
#define FPARSELN_UNESCREST __FPARSELN_UNESCREST /* Remove escape before some other character.*/
#endif /* __FPARSELN_UNESCREST */
#ifdef __FPARSELN_UNESCALL
#define FPARSELN_UNESCALL __FPARSELN_UNESCALL /* Remove all escape prefixes */
#endif /* __FPARSELN_UNESCALL */

#ifdef __CC__
struct utmp;
struct termios;
struct winsize;
struct iovec;

#ifndef __FILE_defined
#define __FILE_defined 1
typedef __FILE FILE;
#endif /* !__FILE_defined */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


#ifndef __login_defined
#define __login_defined 1
#ifdef __CRT_HAVE_login
/* Write the given entry into utmp and wtmp */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC_KOS,login,(struct utmp const *__entry),(__entry))
#else /* __CRT_HAVE_login */
#undef __login_defined
#endif /* !__CRT_HAVE_login */
#endif /* !__login_defined */
#ifndef __login_tty_defined
#define __login_tty_defined 1
#ifdef __CRT_HAVE_login_tty
/* Make FD be the controlling terminal, stdin, stdout, and stderr;
 * then close FD. Returns 0 on success, nonzero on error */
__CDECLARE(,int,__NOTHROW_RPC_KOS,login_tty,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_login_tty */
#undef __login_tty_defined
#endif /* !__CRT_HAVE_login_tty */
#endif /* !__login_tty_defined */
#ifndef __logout_defined
#define __logout_defined 1
#ifdef __CRT_HAVE_logout
/* Write the utmp entry to say the user on UT_LINE has logged out */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_KOS,logout,(char const *__ut_line),(__ut_line))
#else /* __CRT_HAVE_logout */
#undef __logout_defined
#endif /* !__CRT_HAVE_logout */
#endif /* !__logout_defined */
#ifndef __logwtmp_defined
#define __logwtmp_defined 1
#ifdef __CRT_HAVE_logwtmp
/* Append to wtmp an entry for the current time and the given info */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_RPC_KOS,logwtmp,(char const *__ut_line, char const *__ut_name, char const *__ut_host),(__ut_line,__ut_name,__ut_host))
#else /* __CRT_HAVE_logwtmp */
#undef __logwtmp_defined
#endif /* !__CRT_HAVE_logwtmp */
#endif /* !__logwtmp_defined */
/* @param: dflags: Set of `0 | OPENDEV_PART | OPENDEV_BLCK' */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,opendev,(char const *__path, __oflag_t __oflags, __STDC_INT_AS_UINT_T __dflags, char **__realpath),(__path,__oflags,__dflags,__realpath))
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
#ifdef __CRT_HAVE_fparseln
/* Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line, that must be `free(3)'ed by the caller once they are done
 *                  using it.
 *                  If the result would be empty as the result of `feof(stream)' upon
 *                  return of this function, `strdup("")' will be returned. (i.e. NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,fparseln,(FILE *__stream, size_t *__plen, size_t *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags),(__stream,__plen,__plineno,__delim,__flags))
#elif (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && defined(__CRT_HAVE_realloc)
#include <libc/local/util/fparseln.h>
/* Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line, that must be `free(3)'ed by the caller once they are done
 *                  using it.
 *                  If the result would be empty as the result of `feof(stream)' upon
 *                  return of this function, `strdup("")' will be returned. (i.e. NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fparseln, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_RPC(__LIBCCALL fparseln)(FILE *__stream, size_t *__plen, size_t *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fparseln))(__stream, __plen, __plineno, __delim, __flags); })
#endif /* ... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_UTIL_H */
