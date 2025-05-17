/* HASH CRC-32:0x83ec5d2c */
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
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/wait.h) */
/* (#) Portability: DJGPP         (/include/sys/wait.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/wait.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/wait.h) */
/* (#) Portability: FreeBSD       (/sys/sys/wait.h) */
/* (#) Portability: GNU C Library (/posix/sys/wait.h) */
/* (#) Portability: NetBSD        (/sys/sys/wait.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/wait.h) */
/* (#) Portability: OpenBSD       (/sys/sys/wait.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/wait.h) */
/* (#) Portability: diet libc     (/include/sys/wait.h) */
/* (#) Portability: libc4/5       (/include/sys/wait.h) */
/* (#) Portability: mintlib       (/include/sys/wait.h) */
/* (#) Portability: musl libc     (/include/sys/wait.h) */
/* (#) Portability: uClibc        (/include/sys/wait.h) */
#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/wait.h>
#include <bits/types.h>
#include <parts/waitmacros.h>

#ifdef __INTELLISENSE__
#include <bits/types/pid_t.h>
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <bits/types/siginfo_t.h>
#include <bits/types/id_t.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */
#endif /* __INTELLISENSE__ */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <bits/os/siginfo.h> /* `struct __siginfo_struct' */
#include <bits/os/sigval.h>  /* `union sigval' */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

/* susv4-2018: Inclusion of the <sys/wait.h> header may also
 *             make visible  all  symbols  from  <signal.h>. */
#ifdef __USE_POSIX_BLOAT
#include <signal.h>
/* susv4-2018: Issue 7: The requirement  for <sys/wait.h>  to  define the  rusage  structure
 *                      as described  in <sys/resource.h>  is removed,  and <sys/wait.h>  is
 *                      no longer allowed to make visible all symbols from <sys/resource.h>. */
#ifndef __USE_XOPEN2K8
#include <sys/resource.h>
#endif /* "__USE_XOPEN2K8 */
#endif /* __USE_POSIX_BLOAT */


/* Macros for constructing wait status values. */
#ifdef __USE_MISC
#if !defined(WCOREFLAG) && defined(__WCOREFLAG)
#define WCOREFLAG __WCOREFLAG
#endif /* !WCOREFLAG && __WCOREFLAG */
#if !defined(WCOREDUMP) && defined(__WCOREDUMP)
#define WCOREDUMP(status) __WCOREDUMP(__WAIT_INT(status))
#endif /* !WCOREDUMP && __WCOREDUMP */
#if !defined(W_EXITCODE) && defined(__W_EXITCODE)
#define W_EXITCODE(ret, sig) __W_EXITCODE(ret, sig)
#endif /* !W_EXITCODE && __W_EXITCODE */
#if !defined(W_STOPCODE) && defined(__W_STOPCODE)
#define W_STOPCODE(sig) __W_STOPCODE(sig)
#endif /* !W_STOPCODE && __W_STOPCODE */

#if !defined(WAIT_ANY) && defined(__WAIT_ANY)
#define WAIT_ANY __WAIT_ANY /* Any process. */
#endif /* !WAIT_ANY && __WAIT_ANY */
#if !defined(WAIT_MYPGRP) && defined(__WAIT_MYPGRP)
#define WAIT_MYPGRP __WAIT_MYPGRP /* Any process in my process group. */
#endif /* !WAIT_MYPGRP && __WAIT_MYPGRP */
#endif /* __USE_MISC */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

#ifdef __CRT_HAVE_wait
/* >> wait(2)
 * Wait for any child process (same as `waitpid(-1, STAT_LOC, 0);') */
__CDECLARE(,__pid_t,__NOTHROW_RPC,wait,(__WAIT_STATUS __stat_loc),(__stat_loc))
#elif defined(__CRT_HAVE___wait)
/* >> wait(2)
 * Wait for any child process (same as `waitpid(-1, STAT_LOC, 0);') */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,wait,(__WAIT_STATUS __stat_loc),__wait,(__stat_loc))
#endif /* ... */
#ifdef __CRT_HAVE_waitpid
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE(,__pid_t,__NOTHROW_RPC,waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),(__pid,__stat_loc,__options))
#elif defined(__CRT_HAVE___waitpid)
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),__waitpid,(__pid,__stat_loc,__options))
#endif /* ... */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef __id_t_defined
#define __id_t_defined
typedef __id_t id_t;
#endif /* !__id_t_defined */
#ifdef __CRT_HAVE_waitid
/* >> waitid(2)
 * @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED',
 *                  optionally     or'd     with     `WNOHANG | WNOWAIT' */
__CDECLARE(__ATTR_OUT_OPT(3),int,__NOTHROW_RPC,waitid,(idtype_t __idtype, id_t __id, siginfo_t *__infop, __STDC_INT_AS_UINT_T __options),(__idtype,__id,__infop,__options))
#elif defined(__CRT_HAVE___waitid)
/* >> waitid(2)
 * @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED',
 *                  optionally     or'd     with     `WNOHANG | WNOWAIT' */
__CREDIRECT(__ATTR_OUT_OPT(3),int,__NOTHROW_RPC,waitid,(idtype_t __idtype, id_t __id, siginfo_t *__infop, __STDC_INT_AS_UINT_T __options),__waitid,(__idtype,__id,__infop,__options))
#endif /* ... */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
struct rusage;
#if defined(__CRT_HAVE_wait3) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_RPC,wait3,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait3) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_RPC,wait3,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),__wait3,(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait3_64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_RPC,wait3,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),wait3_64,(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait3_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_RPC,wait3,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),__wait3_time64,(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait3_64) || defined(__CRT_HAVE___wait3_time64) || defined(__CRT_HAVE_wait3) || defined(__CRT_HAVE___wait3)
#include <libc/local/sys.wait/wait3.h>
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wait3, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(3) __pid_t __NOTHROW_RPC(__LIBCCALL wait3)(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wait3))(__stat_loc, __options, __usage); })
#endif /* ... */
#ifdef __USE_TIME64
struct rusage64;
#if defined(__CRT_HAVE_wait3) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_NCX,wait3_64,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),wait3,(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait3) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_NCX,wait3_64,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),__wait3,(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait3_64)
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_NCX,wait3_64,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait3_time64)
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(3),__pid_t,__NOTHROW_NCX,wait3_64,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),__wait3_time64,(__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait3) || defined(__CRT_HAVE___wait3)
#include <libc/local/sys.wait/wait3_64.h>
/* >> wait3(2), wait3_64(2)
 * Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wait3_64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(3) __pid_t __NOTHROW_NCX(__LIBCCALL wait3_64)(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wait3_64))(__stat_loc, __options, __usage); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_wait4) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,wait4,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait4) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,wait4,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),__wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___libc_wait4) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,wait4,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),__libc_wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4_64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,wait4,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),wait4_64,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait4_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,wait4,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage),__wait4_time64,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4_64) || defined(__CRT_HAVE___wait4_time64) || defined(__CRT_HAVE_wait4) || defined(__CRT_HAVE___wait4) || defined(__CRT_HAVE___libc_wait4)
#include <libc/local/sys.wait/wait4.h>
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wait4, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(4) __pid_t __NOTHROW_RPC(__LIBCCALL wait4)(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wait4))(__pid, __stat_loc, __options, __usage); })
#endif /* ... */
#ifdef __USE_TIME64
struct rusage64;
#if defined(__CRT_HAVE_wait4) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait4) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),__wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___libc_wait4) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),__libc_wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4_64)
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait4_time64)
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage),__wait4_time64,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4) || defined(__CRT_HAVE___wait4) || defined(__CRT_HAVE___libc_wait4)
#include <libc/local/sys.wait/wait4_64.h>
/* >> wait4(2), wait4_64(2)
 * Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wait4_64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(4) __pid_t __NOTHROW_NCX(__LIBCCALL wait4_64)(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage64 *__usage) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wait4_64))(__pid, __stat_loc, __options, __usage); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_MISC */

#ifdef __USE_KOS
/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the  thread from turning into  a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling  thread from  the set of  running children  within
 *     its own process.  Note however  that when this  is done  by the  main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the  calling   process   the   same  way   a   double-fork   would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads  of the calling process,  essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * The given `pid' must be:
 *   - A thread without the caller's process
 *   - A child process of the caller's process
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had  already
 *       be called.
 * @return: -ECHILD:         `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED: No such  thread/process exists,  or  the thread  isn't  isn't
 *                           a thread in your process, or a child process of your process. */
__CDECLARE_OPT(,int,__NOTHROW_NCX,detach,(__pid_t __pid),(__pid))
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_WAIT_H */
