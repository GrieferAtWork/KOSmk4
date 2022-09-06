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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/syslimits.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/syslimits.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/syslimits.h) */
/* (#) Portability: FreeBSD       (/sys/sys/syslimits.h) */
/* (#) Portability: NetBSD        (/sys/sys/syslimits.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/syslimits.h) */
/* (#) Portability: OpenBSD       (/sys/sys/syslimits.h) */
#ifndef _SYS_SYSLIMITS_H
#define _SYS_SYSLIMITS_H 1

#include <__stdinc.h>
#include <features.h>

#ifdef __USE_POSIX
#include <hybrid/limitcore.h>

#include <asm/os/limits.h> /* Actual system limits */
#include <bits/types.h>

#undef __USE_ALL_LIMITS
#if defined(_ALL_LIMITS_SOURCE)
#define __USE_ALL_LIMITS 1
#endif /* _ALL_LIMITS_SOURCE */

#ifdef __USE_XOPEN2K
#ifndef _POSIX_CHILD_MAX
#define _POSIX_CHILD_MAX   25 /* Maximum simultaneous processes per real user ID. */
#endif /* !_POSIX_CHILD_MAX */
#ifndef _POSIX_NGROUPS_MAX
#define _POSIX_NGROUPS_MAX 8  /* Number of simultaneous supplementary group IDs per process. */
#endif /* !_POSIX_NGROUPS_MAX */
#ifndef _POSIX_OPEN_MAX
#define _POSIX_OPEN_MAX    20 /* Number of files one process can have open at once. */
#endif /* !_POSIX_OPEN_MAX */
#else /* !__USE_XOPEN2K */
#ifndef _POSIX_CHILD_MAX
#define _POSIX_CHILD_MAX   6  /* Maximum simultaneous processes per real user ID. */
#endif /* !_POSIX_CHILD_MAX */
#ifndef _POSIX_NGROUPS_MAX
#define _POSIX_NGROUPS_MAX 0  /* Number of simultaneous supplementary group IDs per process. */
#endif /* !_POSIX_NGROUPS_MAX */
#ifndef _POSIX_OPEN_MAX
#define _POSIX_OPEN_MAX    16 /* Number of files one process can have open at once. */
#endif /* !_POSIX_OPEN_MAX */
#endif /* !__USE_XOPEN2K */

#ifndef _POSIX_ARG_MAX
#define _POSIX_ARG_MAX    4096 /* Maximum length of arguments to `execve', including environment. */
#endif /* !_POSIX_ARG_MAX */
#ifndef _POSIX_LINK_MAX
#define _POSIX_LINK_MAX   8    /* Maximum link count of a file. */
#endif /* !_POSIX_LINK_MAX */
#ifndef _POSIX_MAX_CANON
#define _POSIX_MAX_CANON  255  /* Number of bytes in a terminal canonical input queue. */
#endif /* !_POSIX_MAX_CANON */
#ifndef _POSIX_MAX_INPUT
#define _POSIX_MAX_INPUT  255  /* Number of bytes for which space will be available in a terminal input queue. */
#endif /* !_POSIX_MAX_INPUT */
#ifndef _POSIX_NAME_MAX
#define _POSIX_NAME_MAX   14   /* Number of bytes in a filename. */
#endif /* !_POSIX_NAME_MAX */
#ifndef _POSIX_PATH_MAX
#define _POSIX_PATH_MAX   256  /* Number of bytes in a pathname. */
#endif /* !_POSIX_PATH_MAX */
#ifndef _POSIX_PIPE_BUF
#define _POSIX_PIPE_BUF   512  /* Number of bytes than can be written atomically to a pipe. */
#endif /* !_POSIX_PIPE_BUF */
#ifndef _POSIX_RE_DUP_MAX
#define _POSIX_RE_DUP_MAX 255  /* The # of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation. */
#endif /* !_POSIX_RE_DUP_MAX */

#ifndef __CHILD_MAX
#define __CHILD_MAX _POSIX_CHILD_MAX /* Maximum simultaneous processes per real user ID. */
#endif /* !__CHILD_MAX */
#ifndef __NGROUPS_MAX
#define __NGROUPS_MAX _POSIX_NGROUPS_MAX /* Number of simultaneous supplementary group IDs per process. */
#endif /* !__NGROUPS_MAX */
#ifndef __OPEN_MAX
#define __OPEN_MAX _POSIX_OPEN_MAX /* Number of files one process can have open at once. */
#endif /* !__OPEN_MAX */
#ifndef __ARG_MAX
#define __ARG_MAX _POSIX_ARG_MAX /* Maximum length of arguments to `execve', including environment. */
#endif /* !__ARG_MAX */
#ifndef __LINK_MAX
#define __LINK_MAX _POSIX_LINK_MAX /* Maximum link count of a file. */
#endif /* !__LINK_MAX */
#ifndef __MAX_CANON
#define __MAX_CANON _POSIX_MAX_CANON /* Number of bytes in a terminal canonical input queue. */
#endif /* !__MAX_CANON */
#ifndef __MAX_INPUT
#define __MAX_INPUT _POSIX_MAX_INPUT /* Number of bytes for which space will be available in a terminal input queue. */
#endif /* !__MAX_INPUT */
#ifndef __NAME_MAX
#define __NAME_MAX _POSIX_NAME_MAX /* Number of bytes in a filename. */
#endif /* !__NAME_MAX */
#ifndef __PATH_MAX
#define __PATH_MAX _POSIX_PATH_MAX /* Number of bytes in a pathname. */
#endif /* !__PATH_MAX */
#ifndef __PIPE_BUF
#define __PIPE_BUF _POSIX_PIPE_BUF /* Number of bytes than can be written atomically to a pipe. */
#endif /* !__PIPE_BUF */
#ifndef __RE_DUP_MAX
#define __RE_DUP_MAX _POSIX_RE_DUP_MAX /* The # of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation. */
#endif /* !__RE_DUP_MAX */


/* Maximum length of arguments to `execve', including environment. */
#ifndef ARG_MAX
#if __ARG_MAX != -1
#define ARG_MAX __ARG_MAX
#else /* __ARG_MAX != -1 */
#define ARG_MAX _POSIX_ARG_MAX
#endif /* __ARG_MAX == -1 */
#endif /* !ARG_MAX */

/* Maximum simultaneous processes per real user ID. */
#ifndef CHILD_MAX
#if __CHILD_MAX != -1
#define CHILD_MAX __CHILD_MAX
#elif defined(__USE_ALL_LIMITS)
#define CHILD_MAX _POSIX_CHILD_MAX
#endif /* ... */
#endif /* !CHILD_MAX */

/* Maximum link count of a file. */
#ifndef LINK_MAX
#if __LINK_MAX != -1
#define LINK_MAX __LINK_MAX
#else /* __LINK_MAX != -1 */
#define LINK_MAX _POSIX_LINK_MAX
#endif /* __LINK_MAX == -1 */
#endif /* !LINK_MAX */

/* Number of bytes in a terminal canonical input queue. */
#ifndef MAX_CANON
#if __MAX_CANON != -1
#define MAX_CANON __MAX_CANON
#else /* __MAX_CANON != -1 */
#define MAX_CANON _POSIX_MAX_CANON
#endif /* __MAX_CANON == -1 */
#endif /* !MAX_CANON */

/* Number of bytes for which space will be available in a terminal input queue. */
#ifndef MAX_INPUT
#if __MAX_INPUT != -1
#define MAX_INPUT __MAX_INPUT
#else /* __MAX_INPUT != -1 */
#define MAX_INPUT _POSIX_MAX_INPUT
#endif /* __MAX_INPUT == -1 */
#endif /* !MAX_INPUT */

/* Number of bytes in a filename. */
#ifndef NAME_MAX
#if __NAME_MAX != -1
#define NAME_MAX __NAME_MAX
#else /* __NAME_MAX != -1 */
#define NAME_MAX _POSIX_NAME_MAX
#endif /* __NAME_MAX == -1 */
#endif /* !NAME_MAX */

/* Number of simultaneous supplementary group IDs per process. */
#ifndef NGROUPS_MAX
#if __NGROUPS_MAX != -1
#define NGROUPS_MAX __NGROUPS_MAX
#else /* __NGROUPS_MAX != -1 */
#define NGROUPS_MAX _POSIX_NGROUPS_MAX
#endif /* __NGROUPS_MAX == -1 */
#endif /* !NGROUPS_MAX */

/* Number of files one process can have open at once. */
#ifndef OPEN_MAX
#if __OPEN_MAX != -1
#define OPEN_MAX __OPEN_MAX
#else /* __OPEN_MAX != -1 */
#define OPEN_MAX _POSIX_OPEN_MAX
#endif /* __OPEN_MAX == -1 */
#endif /* !OPEN_MAX */

/* Number of bytes in a pathname. */
#ifndef PATH_MAX
#if __PATH_MAX != -1
#define PATH_MAX __PATH_MAX
#else /* __PATH_MAX != -1 */
#define PATH_MAX _POSIX_PATH_MAX
#endif /* __PATH_MAX == -1 */
#endif /* !PATH_MAX */

/* Number of bytes than can be written atomically to a pipe. */
#ifndef PIPE_BUF
#if __PIPE_BUF != -1
#define PIPE_BUF __PIPE_BUF
#elif defined(__USE_ALL_LIMITS)
#define PIPE_BUF _POSIX_PIPE_BUF
#endif /* ... */
#endif /* !PIPE_BUF */

/* The maximum `ibase' and `obase' values allowed by the `bc' utility. */
#ifndef BC_BASE_MAX
#if __BC_BASE_MAX != -1
#define BC_BASE_MAX __BC_BASE_MAX
#elif defined(__USE_ALL_LIMITS)
#define BC_BASE_MAX _POSIX2_BC_BASE_MAX
#endif /* ... */
#endif /* !BC_BASE_MAX */

/* The maximum number of elements allowed in an array by the `bc' utility. */
#ifndef BC_DIM_MAX
#if __BC_DIM_MAX != -1
#define BC_DIM_MAX __BC_DIM_MAX
#elif defined(__USE_ALL_LIMITS)
#define BC_DIM_MAX _POSIX2_BC_DIM_MAX
#endif /* ... */
#endif /* !BC_DIM_MAX */

/* The maximum `scale' value allowed by the `bc' utility. */
#ifndef BC_SCALE_MAX
#if __BC_SCALE_MAX != -1
#define BC_SCALE_MAX __BC_SCALE_MAX
#elif defined(__USE_ALL_LIMITS)
#define BC_SCALE_MAX _POSIX2_BC_SCALE_MAX
#endif /* ... */
#endif /* !BC_SCALE_MAX */

/* The maximum length of a string constant accepted by the `bc' utility. */
#ifndef BC_STRING_MAX
#if __BC_STRING_MAX != -1
#define BC_STRING_MAX __BC_STRING_MAX
#elif defined(__USE_ALL_LIMITS)
#define BC_STRING_MAX _POSIX2_BC_STRING_MAX
#endif /* ... */
#endif /* !BC_STRING_MAX */

/* The maximum number of weights that can be assigned to an entry of the LC_COLLATE `order' keyword in the locale definition file. */
#ifndef COLL_WEIGHTS_MAX
#if __COLL_WEIGHTS_MAX != -1
#define COLL_WEIGHTS_MAX __COLL_WEIGHTS_MAX
#elif defined(__USE_ALL_LIMITS)
#define COLL_WEIGHTS_MAX _POSIX2_COLL_WEIGHTS_MAX
#endif /* ... */
#endif /* !COLL_WEIGHTS_MAX */

/* The maximum number of expressions that can be nested within parentheses by the `expr' utility. */
#ifndef EXPR_NEST_MAX
#if __EXPR_NEST_MAX != -1
#define EXPR_NEST_MAX __EXPR_NEST_MAX
#elif defined(__USE_ALL_LIMITS)
#define EXPR_NEST_MAX _POSIX2_EXPR_NEST_MAX
#endif /* ... */
#endif /* !EXPR_NEST_MAX */

/* The maximum length, in bytes, of an input line. */
#ifndef LINE_MAX
#if __LINE_MAX != -1
#define LINE_MAX __LINE_MAX
#else /* __LINE_MAX != -1 */
#define LINE_MAX _POSIX2_LINE_MAX
#endif /* __LINE_MAX == -1 */
#endif /* !LINE_MAX */

/* The # of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation. */
#ifndef RE_DUP_MAX
#if __RE_DUP_MAX != -1
#define RE_DUP_MAX __RE_DUP_MAX
#else /* __RE_DUP_MAX != -1 */
#define RE_DUP_MAX _POSIX_RE_DUP_MAX
#endif /* __RE_DUP_MAX == -1 */
#endif /* !RE_DUP_MAX */

#if defined(__USE_POSIX199506) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_NETBSD)
#define _POSIX_LOGIN_NAME_MAX 9 /* Maximum length of login name. */
#ifndef __LOGIN_NAME_MAX
#define __LOGIN_NAME_MAX _POSIX_LOGIN_NAME_MAX /* Maximum length of login name. */
#endif /* !__LOGIN_NAME_MAX */

/* Maximum length of login name. */
#ifndef LOGIN_NAME_MAX
#if __LOGIN_NAME_MAX != -1
#define LOGIN_NAME_MAX __LOGIN_NAME_MAX
#elif defined(__USE_ALL_LIMITS)
#define LOGIN_NAME_MAX _POSIX_LOGIN_NAME_MAX
#endif /* ... */
#endif /* !LOGIN_NAME_MAX */
#endif /* __USE_POSIX199506 || __USE_XOPEN_EXTENDED || __USE_NETBSD */


#ifndef GID_MAX
#define GID_MAX __PRIVATE_MAX_S(__SIZEOF_GID_T__) /* Max value for `gid_t' */
#endif /* !GID_MAX */
#ifndef UID_MAX
#define UID_MAX __PRIVATE_MAX_S(__SIZEOF_UID_T__) /* Max value for `uid_t' */
#endif /* !UID_MAX */


#if defined(__USE_XOPEN) || defined(__USE_NETBSD)
#ifndef _XOPEN_IOV_MAX
#define _XOPEN_IOV_MAX 16 /* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#endif /* !_XOPEN_IOV_MAX */

/* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#ifndef IOV_MAX
#if __IOV_MAX != -1
#define IOV_MAX __IOV_MAX
#else /* __IOV_MAX != -1 */
#define IOV_MAX _XOPEN_IOV_MAX
#endif /* __IOV_MAX == -1 */
#endif /* !IOV_MAX */

#if !defined(NZERO) && defined(__NZERO)
#define NZERO __NZERO /* Default process priority. */
#endif /* !NZERO && __NZERO */
#endif /* __USE_XOPEN || __USE_NETBSD */

#endif /* __USE_POSIX */

#endif /* !_SYS_SYSLIMITS_H */
