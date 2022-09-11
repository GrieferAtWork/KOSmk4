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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/limits.h) */
/* (#) Portability: DJGPP         (/include/limits.h) */
/* (#) Portability: DragonFly BSD (/include/limits.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/limits.h) */
/* (#) Portability: FreeBSD       (/include/limits.h) */
/* (#) Portability: GNU C Library (/include/limits.h) */
/* (#) Portability: MSVC          (/include/limits.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/limits.h) */
/* (#) Portability: NetBSD        (/include/limits.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/limits.h) */
/* (#) Portability: OpenBSD       (/include/limits.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/limits.h) */
/* (#) Portability: PDCLib        (/include/limits.h) */
/* (#) Portability: diet libc     (/include/limits.h) */
/* (#) Portability: libc4/5       (/include/limits.h) */
/* (#) Portability: libc6         (/include/limits.h) */
/* (#) Portability: libcmini      (/include/limits.h) */
/* (#) Portability: mintlib       (/include/limits.h) */
/* (#) Portability: musl libc     (/include/limits.h) */
/* (#) Portability: uClibc        (/include/limits.h) */
#ifndef _LIMITS_H
#define _LIMITS_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

#include <asm/crt/limits.h>
#include <asm/os/limits.h>

/* You should really just always using 'MB_CUR_MAX'... */
#ifndef MB_LEN_MAX
#include <__crt.h>
#ifdef __CRT_DOS_PRIMARY
#define MB_LEN_MAX 5
#elif defined(__CRT_CYG_PRIMARY)
#include <newlib.h>
#define MB_LEN_MAX _MB_LEN_MAX
#else /* ... */
#define MB_LEN_MAX 16
#endif /* !... */
#endif /* !MB_LEN_MAX */

#ifndef CHAR_BIT
#define CHAR_BIT __CHAR_BIT__
#endif /* !CHAR_BIT */
#ifndef SCHAR_MIN
#define SCHAR_MIN __SCHAR_MIN__
#endif /* !SCHAR_MIN */
#ifndef SCHAR_MAX
#define SCHAR_MAX __SCHAR_MAX__
#endif /* !SCHAR_MAX */
#ifndef UCHAR_MAX
#define UCHAR_MAX __UCHAR_MAX__
#endif /* !UCHAR_MAX */
#ifndef CHAR_MIN
#define CHAR_MIN __CHAR_MIN__
#endif /* !CHAR_MIN */
#ifndef CHAR_MAX
#define CHAR_MAX __CHAR_MAX__
#endif /* !CHAR_MAX */
#ifndef SHRT_MIN
#define SHRT_MIN __SHRT_MIN__
#endif /* !SHRT_MIN */
#ifndef SHRT_MAX
#define SHRT_MAX __SHRT_MAX__
#endif /* !SHRT_MAX */
#ifndef USHRT_MAX
#define USHRT_MAX __USHRT_MAX__
#endif /* !USHRT_MAX */
#ifndef INT_MIN
#define INT_MIN __INT_MIN__
#endif /* !INT_MIN */
#ifndef INT_MAX
#define INT_MAX __INT_MAX__
#endif /* !INT_MAX */
#ifndef UINT_MAX
#define UINT_MAX __UINT_MAX__
#endif /* !UINT_MAX */
#ifndef LONG_MIN
#define LONG_MIN __LONG_MIN__
#endif /* !LONG_MIN */
#ifndef LONG_MAX
#define LONG_MAX __LONG_MAX__
#endif /* !LONG_MAX */
#ifndef ULONG_MAX
#define ULONG_MAX __ULONG_MAX__
#endif /* !ULONG_MAX */

#ifdef __USE_ISOC99
#if !defined(LLONG_MIN) && defined(__LONG_LONG_MIN__)
#define LLONG_MIN __LONG_LONG_MIN__
#endif /* !LLONG_MIN && __LONG_LONG_MIN__ */
#if !defined(LLONG_MAX) && defined(__LONG_LONG_MAX__)
#define LLONG_MAX __LONG_LONG_MAX__
#endif /* !LLONG_MAX && __LONG_LONG_MAX__ */
#if !defined(ULLONG_MAX) && defined(__ULONG_LONG_MAX__)
#define ULLONG_MAX __ULONG_LONG_MAX__
#endif /* !ULLONG_MAX && __ULONG_LONG_MAX__ */
#endif /* __USE_ISOC99 */

#ifdef __USE_ISOC17
#ifndef BOOL_MAX
#define BOOL_MAX 1
#endif /* !BOOL_MAX */
#ifndef BOOL_WIDTH
#define BOOL_WIDTH 1
#endif /* !BOOL_WIDTH */
#endif /* __USE_ISOC17 */

#ifdef __USE_GNU
#if !defined(LONG_LONG_MIN) && defined(__LONG_LONG_MIN__)
#define LONG_LONG_MIN __LONG_LONG_MIN__
#endif /* !LONG_LONG_MIN && __LONG_LONG_MIN__ */
#if !defined(LONG_LONG_MAX) && defined(__LONG_LONG_MAX__)
#define LONG_LONG_MAX __LONG_LONG_MAX__
#endif /* !LONG_LONG_MAX && __LONG_LONG_MAX__ */
#if !defined(ULONG_LONG_MAX) && defined(__ULONG_LONG_MAX__)
#define ULONG_LONG_MAX __ULONG_LONG_MAX__
#endif /* !ULONG_LONG_MAX && __ULONG_LONG_MAX__ */
#endif /* __USE_GNU */

#if (defined(__USE_GNU) || defined(__USE_ISOC17) || \
     defined(__STDC_WANT_IEC_60559_BFP_EXT__))
#ifndef CHAR_WIDTH
#define CHAR_WIDTH __SCHAR_WIDTH__
#endif /* !CHAR_WIDTH */
#ifndef SCHAR_WIDTH
#define SCHAR_WIDTH __SCHAR_WIDTH__
#endif /* !SCHAR_WIDTH */
#ifndef UCHAR_WIDTH
#define UCHAR_WIDTH __SCHAR_WIDTH__
#endif /* !UCHAR_WIDTH */
#ifndef SHRT_WIDTH
#define SHRT_WIDTH __SHRT_WIDTH__
#endif /* !SHRT_WIDTH */
#ifndef USHRT_WIDTH
#define USHRT_WIDTH __SHRT_WIDTH__
#endif /* !USHRT_WIDTH */
#ifndef INT_WIDTH
#define INT_WIDTH __INT_WIDTH__
#endif /* !INT_WIDTH */
#ifndef UINT_WIDTH
#define UINT_WIDTH __INT_WIDTH__
#endif /* !UINT_WIDTH */
#ifndef LONG_WIDTH
#define LONG_WIDTH __LONG_WIDTH__
#endif /* !LONG_WIDTH */
#ifndef ULONG_WIDTH
#define ULONG_WIDTH __LONG_WIDTH__
#endif /* !ULONG_WIDTH */
#ifndef LLONG_WIDTH
#define LLONG_WIDTH __LONG_LONG_WIDTH__
#endif /* !LLONG_WIDTH */
#ifndef ULLONG_WIDTH
#define ULLONG_WIDTH __LONG_LONG_WIDTH__
#endif /* !ULLONG_WIDTH */
#endif /* __USE_GNU || __USE_ISOC17 || __STDC_WANT_IEC_60559_BFP_EXT__ */


#ifdef __USE_DOS
#define _I8_MIN     __PRIVATE_MIN_S1
#define _I8_MAX     __PRIVATE_MAX_S1
#define _UI8_MAX    __PRIVATE_MIN_U1
#define _I16_MIN    __PRIVATE_MIN_S2
#define _I16_MAX    __PRIVATE_MAX_S2
#define _UI16_MAX   __PRIVATE_MIN_U2
#define _I32_MIN    __PRIVATE_MIN_S4
#define _I32_MAX    __PRIVATE_MAX_S4
#define _UI32_MAX   __PRIVATE_MIN_U4
#ifdef __PRIVATE_MIN_S8
#define _I64_MIN    __PRIVATE_MIN_S8
#define _I64_MAX    __PRIVATE_MAX_S8
#define _UI64_MAX   __PRIVATE_MIN_U8
#endif /* __PRIVATE_MIN_S8 */
#ifdef __PRIVATE_MIN_S16
#define _I128_MIN   __PRIVATE_MIN_S16
#define _I128_MAX   __PRIVATE_MAX_S16
#define _UI128_MAX  __PRIVATE_MAX_U16
#endif /* __PRIVATE_MIN_S16 */

/* """Extension""" Define something that belongs in <stdint.h> */
#ifndef __USE_DOS_CLEAN
#ifndef SIZE_MAX
#define SIZE_MAX __SIZE_MAX__
#endif  /* SIZE_MAX */
#endif /* !__USE_DOS_CLEAN */

#ifdef __USE_DOS_SLIB
#ifndef RSIZE_MAX
#define RSIZE_MAX __SSIZE_MAX__
#endif /* RSIZE_MAX */
#endif /* __USE_DOS_SLIB */
#endif /* __USE_DOS */

#undef __USE_ALL_LIMITS
#if defined(_ALL_LIMITS_SOURCE)
#define __USE_ALL_LIMITS 1
#endif /* _ALL_LIMITS_SOURCE */


/************************************************************************/
/* POSIX.1                                                              */
/************************************************************************/
#if defined(__USE_POSIX) || defined(__DEEMON__)
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
#ifndef _POSIX_TZNAME_MAX
#define _POSIX_TZNAME_MAX  6  /* Maximum length of a timezone name (element of `tzname'). */
#endif /* !_POSIX_TZNAME_MAX */
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
#ifndef _POSIX_TZNAME_MAX
#define _POSIX_TZNAME_MAX  3  /* Maximum length of a timezone name (element of `tzname'). */
#endif /* !_POSIX_TZNAME_MAX */
#endif /* !__USE_XOPEN2K */
#if !defined(__USE_XOPEN2K) || defined(__USE_GNU)
#ifndef _POSIX_FD_SETSIZE
#define _POSIX_FD_SETSIZE _POSIX_OPEN_MAX /* Number of descriptors that a process may examine with `pselect' or `select'. */
#endif /* !_POSIX_FD_SETSIZE */
#ifndef _POSIX_QLIMIT
#define _POSIX_QLIMIT     1               /* Maximum # of connections that can be queued on a socket. */
#endif /* !_POSIX_QLIMIT */
#ifndef _POSIX_HIWAT
#define _POSIX_HIWAT      _POSIX_PIPE_BUF /* Maximum # of bytes that can be buffered on a socket for send or receive. */
#endif /* !_POSIX_HIWAT */
#ifndef _POSIX_UIO_MAXIOV
#define _POSIX_UIO_MAXIOV 16              /* Maximum # of elements in an `iovec' array. */
#endif /* !_POSIX_UIO_MAXIOV */
#endif /* !__USE_XOPEN2K || __USE_GNU */

#ifndef _POSIX_SSIZE_MAX
#define _POSIX_SSIZE_MAX 32767  /* Largest value of a `ssize_t'. */
#endif /* !_POSIX_SSIZE_MAX */
#ifndef SSIZE_MAX
#define SSIZE_MAX __SSIZE_MAX__
#endif /* !SSIZE_MAX */

#ifdef __USE_KOS
#ifndef SSIZE_MIN
#define SSIZE_MIN __SSIZE_MIN__
#endif /* !SSIZE_MIN */
#endif /* __USE_KOS */

/*[[[deemon
@@List of (alwaysUseMinimum, name, posixName, posixMinimum, doc)
local limits = {
	(0, "CHILD_MAX",                    "", "_POSIX_CHILD_MAX",                            "Maximum simultaneous processes per real user ID."),
	(1, "NGROUPS_MAX",                  "", "_POSIX_NGROUPS_MAX",                          "Number of simultaneous supplementary group IDs per process."),
	(1, "OPEN_MAX",                     "", "_POSIX_OPEN_MAX",                             "Number of files one process can have open at once."),
	(0, "TZNAME_MAX",                   "", "_POSIX_TZNAME_MAX",                           "Maximum length of a timezone name (element of `tzname')."),
	(0, "AIO_LISTIO_MAX",               "_POSIX_AIO_LISTIO_MAX",               "2",        "Minimum # of operations in one list I/O call."),
	(0, "AIO_MAX",                      "_POSIX_AIO_MAX",                      "1",        "Minimal # of outstanding asynchronous I/O operations."),
	(1, "ARG_MAX",                      "_POSIX_ARG_MAX",                      "4096",     "Maximum length of arguments to `execve', including environment."),
	(0, "DELAYTIMER_MAX",               "_POSIX_DELAYTIMER_MAX",               "32",       "Minimal # of timer expiration overruns."),
	(0, "HOST_NAME_MAX",                "_POSIX_HOST_NAME_MAX",                "255",      "Maximum length of a host name (not including the terminating null) as returned by `gethostname(2)'."),
	(1, "LINK_MAX",                     "_POSIX_LINK_MAX",                     "8",        "Maximum link count of a file."),
	(0, "LOGIN_NAME_MAX",               "_POSIX_LOGIN_NAME_MAX",               "9",        "Maximum length of login name."),
	(1, "MAX_CANON",                    "_POSIX_MAX_CANON",                    "255",      "Number of bytes in a terminal canonical input queue."),
	(1, "MAX_INPUT",                    "_POSIX_MAX_INPUT",                    "255",      "Number of bytes for which space will be available in a terminal input queue."),
	(0, "MQ_OPEN_MAX",                  "_POSIX_MQ_OPEN_MAX",                  "8",        "Maximum # of message queues open for a process."),
	(0, "MQ_PRIO_MAX",                  "_POSIX_MQ_PRIO_MAX",                  "32",       "Maximum # of supported message priorities."),
	(1, "NAME_MAX",                     "_POSIX_NAME_MAX",                     "14",       "Number of bytes in a filename."),
	(0, "PATH_MAX",                     "_POSIX_PATH_MAX",                     "256",      "Number of bytes in a pathname. (Not defined by default because some programs\n * think `defined(MAX_PATH)' -> chdir(2) fails for paths longer than this)"),
	(0, "PIPE_BUF",                     "_POSIX_PIPE_BUF",                     "512",      "Number of bytes than can be written atomically to a pipe."),
	(1, "RE_DUP_MAX",                   "_POSIX_RE_DUP_MAX",                   "255",      "Max # of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation."),
	(1, "RTSIG_MAX",                    "_POSIX_RTSIG_MAX",                    "8",        "Minimal # of realtime signals reserved for the application."),
	(0, "SEM_NSEMS_MAX",                "_POSIX_SEM_NSEMS_MAX",                "256",      "<semaphore.h>: Number of semaphores a process can have."),
	(0, "SEM_VALUE_MAX",                "_POSIX_SEM_VALUE_MAX",                "32767",    "<semaphore.h>: Maximal value of a semaphore."),
	(0, "SIGQUEUE_MAX",                 "_POSIX_SIGQUEUE_MAX",                 "32",       "Number of pending realtime signals."),
	(0, "STREAM_MAX",                   "_POSIX_STREAM_MAX",                   "8",        "<stdio.h>: Number of streams a process can have open at once."),
	(0, "SYMLINK_MAX",                  "_POSIX_SYMLINK_MAX",                  "255",      "Max # of bytes in a symbolic link."),
	(1, "SYMLOOP_MAX",                  "_POSIX_SYMLOOP_MAX",                  "8",        "Max # of symbolic links that can be traversed in the resolution of a pathname in the absence of a loop."),
	(0, "TIMER_MAX",                    "_POSIX_TIMER_MAX",                    "32",       "Number of timer for a process."),
	(0, "TTY_NAME_MAX",                 "_POSIX_TTY_NAME_MAX",                 "9",        "Maximum # of characters in a tty name."),
	(0, "CLOCKRES_MIN",                 "_POSIX_CLOCKRES_MIN",                 "20000000", "Maximum clock resolution in nanoseconds."),
	(0, "THREAD_KEYS_MAX",              "_POSIX_THREAD_KEYS_MAX",              "128",      "<pthread.h>: Max # of data keys per process."),
	(0, "THREAD_DESTRUCTOR_ITERATIONS", "_POSIX_THREAD_DESTRUCTOR_ITERATIONS", "4",        "<pthread.h>: Max # of iterations of destructors for thread-specific data."),
	(0, "THREAD_THREADS_MAX",           "_POSIX_THREAD_THREADS_MAX",           "64",       "<pthread.h>: Max # of threads per process."),
};

local longestPosixNameLength    = limits.each[2].length > ...;
local longestPosixMinimumLength = (for (local x: limits) x[2] ? #x[3] : 0) > ...;

function escapedNameOf(name) {
	return {
		"THREAD_KEYS_MAX"              : "__PTHREAD_KEYS_MAX",
		"THREAD_DESTRUCTOR_ITERATIONS" : "__PTHREAD_DESTRUCTOR_ITERATIONS",
		"THREAD_THREADS_MAX"           : "__PTHREAD_THREADS_MAX",
	}.get(name, "__" + name);
}

print("/" "* Posix-mandated minimum limits. *" "/");
for (local none, none, posixName, posixMinimum, doc: limits) {
	if (!posixName)
		continue;
	print("#ifndef ", posixName);
	print("#define ", posixName, " " * (longestPosixNameLength - #posixName),
		" ", posixMinimum, " " * (longestPosixMinimumLength - #posixMinimum),
		" /" "* ", doc, " *" "/");
	print("#endif /" "* !", posixName, " *" "/");
}
print;
print;
print("/" "* Substitute unknown system/crt limits. *" "/");
for (local none, name, posixName, posixMinimum, doc: limits) {
	print("#ifndef ", escapedNameOf(name));
	print("#define ", escapedNameOf(name), " ",
		posixName ? posixName : posixMinimum,
		" /" "* ", doc, " *" "/");
	print("#endif /" "* !", escapedNameOf(name), " *" "/");
}
print;
print;
print("/" "* Actual implementation limits. *" "/");
for (local alwaysUseMinimum, name, posixName, posixMinimum, doc: limits) {
	print();
	print("/" "* ", doc, " *" "/");
	print("#ifndef ", name);
	print("#if defined(", escapedNameOf(name), ") && ", escapedNameOf(name), " != -1");
	print("#define ", name, " ", escapedNameOf(name));
	if (alwaysUseMinimum) {
		print("#else /" "* ", escapedNameOf(name), " && ", escapedNameOf(name), " != -1 *" "/");
		print("#define ", name, " ", posixName ? posixName : posixMinimum);
		print("#endif /" "* !", escapedNameOf(name), " || ", escapedNameOf(name), " == -1 *" "/");
	} else {
		print("#elif defined(__USE_ALL_LIMITS)");
		print("#define ", name, " ", posixName ? posixName : posixMinimum);
		print("#endif /" "* ... *" "/");
	}
	print("#endif /" "* !", name, " *" "/");
}
]]]*/
/* Posix-mandated minimum limits. */
#ifndef _POSIX_AIO_LISTIO_MAX
#define _POSIX_AIO_LISTIO_MAX               2        /* Minimum # of operations in one list I/O call. */
#endif /* !_POSIX_AIO_LISTIO_MAX */
#ifndef _POSIX_AIO_MAX
#define _POSIX_AIO_MAX                      1        /* Minimal # of outstanding asynchronous I/O operations. */
#endif /* !_POSIX_AIO_MAX */
#ifndef _POSIX_ARG_MAX
#define _POSIX_ARG_MAX                      4096     /* Maximum length of arguments to `execve', including environment. */
#endif /* !_POSIX_ARG_MAX */
#ifndef _POSIX_DELAYTIMER_MAX
#define _POSIX_DELAYTIMER_MAX               32       /* Minimal # of timer expiration overruns. */
#endif /* !_POSIX_DELAYTIMER_MAX */
#ifndef _POSIX_HOST_NAME_MAX
#define _POSIX_HOST_NAME_MAX                255      /* Maximum length of a host name (not including the terminating null) as returned by `gethostname(2)'. */
#endif /* !_POSIX_HOST_NAME_MAX */
#ifndef _POSIX_LINK_MAX
#define _POSIX_LINK_MAX                     8        /* Maximum link count of a file. */
#endif /* !_POSIX_LINK_MAX */
#ifndef _POSIX_LOGIN_NAME_MAX
#define _POSIX_LOGIN_NAME_MAX               9        /* Maximum length of login name. */
#endif /* !_POSIX_LOGIN_NAME_MAX */
#ifndef _POSIX_MAX_CANON
#define _POSIX_MAX_CANON                    255      /* Number of bytes in a terminal canonical input queue. */
#endif /* !_POSIX_MAX_CANON */
#ifndef _POSIX_MAX_INPUT
#define _POSIX_MAX_INPUT                    255      /* Number of bytes for which space will be available in a terminal input queue. */
#endif /* !_POSIX_MAX_INPUT */
#ifndef _POSIX_MQ_OPEN_MAX
#define _POSIX_MQ_OPEN_MAX                  8        /* Maximum # of message queues open for a process. */
#endif /* !_POSIX_MQ_OPEN_MAX */
#ifndef _POSIX_MQ_PRIO_MAX
#define _POSIX_MQ_PRIO_MAX                  32       /* Maximum # of supported message priorities. */
#endif /* !_POSIX_MQ_PRIO_MAX */
#ifndef _POSIX_NAME_MAX
#define _POSIX_NAME_MAX                     14       /* Number of bytes in a filename. */
#endif /* !_POSIX_NAME_MAX */
#ifndef _POSIX_PATH_MAX
#define _POSIX_PATH_MAX                     256      /* Number of bytes in a pathname. (Not defined by default because some programs
 * think `defined(MAX_PATH)' -> chdir(2) fails for paths longer than this) */
#endif /* !_POSIX_PATH_MAX */
#ifndef _POSIX_PIPE_BUF
#define _POSIX_PIPE_BUF                     512      /* Number of bytes than can be written atomically to a pipe. */
#endif /* !_POSIX_PIPE_BUF */
#ifndef _POSIX_RE_DUP_MAX
#define _POSIX_RE_DUP_MAX                   255      /* Max # of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation. */
#endif /* !_POSIX_RE_DUP_MAX */
#ifndef _POSIX_RTSIG_MAX
#define _POSIX_RTSIG_MAX                    8        /* Minimal # of realtime signals reserved for the application. */
#endif /* !_POSIX_RTSIG_MAX */
#ifndef _POSIX_SEM_NSEMS_MAX
#define _POSIX_SEM_NSEMS_MAX                256      /* <semaphore.h>: Number of semaphores a process can have. */
#endif /* !_POSIX_SEM_NSEMS_MAX */
#ifndef _POSIX_SEM_VALUE_MAX
#define _POSIX_SEM_VALUE_MAX                32767    /* <semaphore.h>: Maximal value of a semaphore. */
#endif /* !_POSIX_SEM_VALUE_MAX */
#ifndef _POSIX_SIGQUEUE_MAX
#define _POSIX_SIGQUEUE_MAX                 32       /* Number of pending realtime signals. */
#endif /* !_POSIX_SIGQUEUE_MAX */
#ifndef _POSIX_STREAM_MAX
#define _POSIX_STREAM_MAX                   8        /* <stdio.h>: Number of streams a process can have open at once. */
#endif /* !_POSIX_STREAM_MAX */
#ifndef _POSIX_SYMLINK_MAX
#define _POSIX_SYMLINK_MAX                  255      /* Max # of bytes in a symbolic link. */
#endif /* !_POSIX_SYMLINK_MAX */
#ifndef _POSIX_SYMLOOP_MAX
#define _POSIX_SYMLOOP_MAX                  8        /* Max # of symbolic links that can be traversed in the resolution of a pathname in the absence of a loop. */
#endif /* !_POSIX_SYMLOOP_MAX */
#ifndef _POSIX_TIMER_MAX
#define _POSIX_TIMER_MAX                    32       /* Number of timer for a process. */
#endif /* !_POSIX_TIMER_MAX */
#ifndef _POSIX_TTY_NAME_MAX
#define _POSIX_TTY_NAME_MAX                 9        /* Maximum # of characters in a tty name. */
#endif /* !_POSIX_TTY_NAME_MAX */
#ifndef _POSIX_CLOCKRES_MIN
#define _POSIX_CLOCKRES_MIN                 20000000 /* Maximum clock resolution in nanoseconds. */
#endif /* !_POSIX_CLOCKRES_MIN */
#ifndef _POSIX_THREAD_KEYS_MAX
#define _POSIX_THREAD_KEYS_MAX              128      /* <pthread.h>: Max # of data keys per process. */
#endif /* !_POSIX_THREAD_KEYS_MAX */
#ifndef _POSIX_THREAD_DESTRUCTOR_ITERATIONS
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS 4        /* <pthread.h>: Max # of iterations of destructors for thread-specific data. */
#endif /* !_POSIX_THREAD_DESTRUCTOR_ITERATIONS */
#ifndef _POSIX_THREAD_THREADS_MAX
#define _POSIX_THREAD_THREADS_MAX           64       /* <pthread.h>: Max # of threads per process. */
#endif /* !_POSIX_THREAD_THREADS_MAX */


/* Substitute unknown system/crt limits. */
#ifndef __CHILD_MAX
#define __CHILD_MAX _POSIX_CHILD_MAX /* Maximum simultaneous processes per real user ID. */
#endif /* !__CHILD_MAX */
#ifndef __NGROUPS_MAX
#define __NGROUPS_MAX _POSIX_NGROUPS_MAX /* Number of simultaneous supplementary group IDs per process. */
#endif /* !__NGROUPS_MAX */
#ifndef __OPEN_MAX
#define __OPEN_MAX _POSIX_OPEN_MAX /* Number of files one process can have open at once. */
#endif /* !__OPEN_MAX */
#ifndef __TZNAME_MAX
#define __TZNAME_MAX _POSIX_TZNAME_MAX /* Maximum length of a timezone name (element of `tzname'). */
#endif /* !__TZNAME_MAX */
#ifndef __AIO_LISTIO_MAX
#define __AIO_LISTIO_MAX _POSIX_AIO_LISTIO_MAX /* Minimum # of operations in one list I/O call. */
#endif /* !__AIO_LISTIO_MAX */
#ifndef __AIO_MAX
#define __AIO_MAX _POSIX_AIO_MAX /* Minimal # of outstanding asynchronous I/O operations. */
#endif /* !__AIO_MAX */
#ifndef __ARG_MAX
#define __ARG_MAX _POSIX_ARG_MAX /* Maximum length of arguments to `execve', including environment. */
#endif /* !__ARG_MAX */
#ifndef __DELAYTIMER_MAX
#define __DELAYTIMER_MAX _POSIX_DELAYTIMER_MAX /* Minimal # of timer expiration overruns. */
#endif /* !__DELAYTIMER_MAX */
#ifndef __HOST_NAME_MAX
#define __HOST_NAME_MAX _POSIX_HOST_NAME_MAX /* Maximum length of a host name (not including the terminating null) as returned by `gethostname(2)'. */
#endif /* !__HOST_NAME_MAX */
#ifndef __LINK_MAX
#define __LINK_MAX _POSIX_LINK_MAX /* Maximum link count of a file. */
#endif /* !__LINK_MAX */
#ifndef __LOGIN_NAME_MAX
#define __LOGIN_NAME_MAX _POSIX_LOGIN_NAME_MAX /* Maximum length of login name. */
#endif /* !__LOGIN_NAME_MAX */
#ifndef __MAX_CANON
#define __MAX_CANON _POSIX_MAX_CANON /* Number of bytes in a terminal canonical input queue. */
#endif /* !__MAX_CANON */
#ifndef __MAX_INPUT
#define __MAX_INPUT _POSIX_MAX_INPUT /* Number of bytes for which space will be available in a terminal input queue. */
#endif /* !__MAX_INPUT */
#ifndef __MQ_OPEN_MAX
#define __MQ_OPEN_MAX _POSIX_MQ_OPEN_MAX /* Maximum # of message queues open for a process. */
#endif /* !__MQ_OPEN_MAX */
#ifndef __MQ_PRIO_MAX
#define __MQ_PRIO_MAX _POSIX_MQ_PRIO_MAX /* Maximum # of supported message priorities. */
#endif /* !__MQ_PRIO_MAX */
#ifndef __NAME_MAX
#define __NAME_MAX _POSIX_NAME_MAX /* Number of bytes in a filename. */
#endif /* !__NAME_MAX */
#ifndef __PATH_MAX
#define __PATH_MAX _POSIX_PATH_MAX /* Number of bytes in a pathname. (Not defined by default because some programs
 * think `defined(MAX_PATH)' -> chdir(2) fails for paths longer than this) */
#endif /* !__PATH_MAX */
#ifndef __PIPE_BUF
#define __PIPE_BUF _POSIX_PIPE_BUF /* Number of bytes than can be written atomically to a pipe. */
#endif /* !__PIPE_BUF */
#ifndef __RE_DUP_MAX
#define __RE_DUP_MAX _POSIX_RE_DUP_MAX /* Max # of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation. */
#endif /* !__RE_DUP_MAX */
#ifndef __RTSIG_MAX
#define __RTSIG_MAX _POSIX_RTSIG_MAX /* Minimal # of realtime signals reserved for the application. */
#endif /* !__RTSIG_MAX */
#ifndef __SEM_NSEMS_MAX
#define __SEM_NSEMS_MAX _POSIX_SEM_NSEMS_MAX /* <semaphore.h>: Number of semaphores a process can have. */
#endif /* !__SEM_NSEMS_MAX */
#ifndef __SEM_VALUE_MAX
#define __SEM_VALUE_MAX _POSIX_SEM_VALUE_MAX /* <semaphore.h>: Maximal value of a semaphore. */
#endif /* !__SEM_VALUE_MAX */
#ifndef __SIGQUEUE_MAX
#define __SIGQUEUE_MAX _POSIX_SIGQUEUE_MAX /* Number of pending realtime signals. */
#endif /* !__SIGQUEUE_MAX */
#ifndef __STREAM_MAX
#define __STREAM_MAX _POSIX_STREAM_MAX /* <stdio.h>: Number of streams a process can have open at once. */
#endif /* !__STREAM_MAX */
#ifndef __SYMLINK_MAX
#define __SYMLINK_MAX _POSIX_SYMLINK_MAX /* Max # of bytes in a symbolic link. */
#endif /* !__SYMLINK_MAX */
#ifndef __SYMLOOP_MAX
#define __SYMLOOP_MAX _POSIX_SYMLOOP_MAX /* Max # of symbolic links that can be traversed in the resolution of a pathname in the absence of a loop. */
#endif /* !__SYMLOOP_MAX */
#ifndef __TIMER_MAX
#define __TIMER_MAX _POSIX_TIMER_MAX /* Number of timer for a process. */
#endif /* !__TIMER_MAX */
#ifndef __TTY_NAME_MAX
#define __TTY_NAME_MAX _POSIX_TTY_NAME_MAX /* Maximum # of characters in a tty name. */
#endif /* !__TTY_NAME_MAX */
#ifndef __CLOCKRES_MIN
#define __CLOCKRES_MIN _POSIX_CLOCKRES_MIN /* Maximum clock resolution in nanoseconds. */
#endif /* !__CLOCKRES_MIN */
#ifndef __PTHREAD_KEYS_MAX
#define __PTHREAD_KEYS_MAX _POSIX_THREAD_KEYS_MAX /* <pthread.h>: Max # of data keys per process. */
#endif /* !__PTHREAD_KEYS_MAX */
#ifndef __PTHREAD_DESTRUCTOR_ITERATIONS
#define __PTHREAD_DESTRUCTOR_ITERATIONS _POSIX_THREAD_DESTRUCTOR_ITERATIONS /* <pthread.h>: Max # of iterations of destructors for thread-specific data. */
#endif /* !__PTHREAD_DESTRUCTOR_ITERATIONS */
#ifndef __PTHREAD_THREADS_MAX
#define __PTHREAD_THREADS_MAX _POSIX_THREAD_THREADS_MAX /* <pthread.h>: Max # of threads per process. */
#endif /* !__PTHREAD_THREADS_MAX */


/* Actual implementation limits. */

/* Maximum simultaneous processes per real user ID. */
#ifndef CHILD_MAX
#if defined(__CHILD_MAX) && __CHILD_MAX != -1
#define CHILD_MAX __CHILD_MAX
#elif defined(__USE_ALL_LIMITS)
#define CHILD_MAX _POSIX_CHILD_MAX
#endif /* ... */
#endif /* !CHILD_MAX */

/* Number of simultaneous supplementary group IDs per process. */
#ifndef NGROUPS_MAX
#if defined(__NGROUPS_MAX) && __NGROUPS_MAX != -1
#define NGROUPS_MAX __NGROUPS_MAX
#else /* __NGROUPS_MAX && __NGROUPS_MAX != -1 */
#define NGROUPS_MAX _POSIX_NGROUPS_MAX
#endif /* !__NGROUPS_MAX || __NGROUPS_MAX == -1 */
#endif /* !NGROUPS_MAX */

/* Number of files one process can have open at once. */
#ifndef OPEN_MAX
#if defined(__OPEN_MAX) && __OPEN_MAX != -1
#define OPEN_MAX __OPEN_MAX
#else /* __OPEN_MAX && __OPEN_MAX != -1 */
#define OPEN_MAX _POSIX_OPEN_MAX
#endif /* !__OPEN_MAX || __OPEN_MAX == -1 */
#endif /* !OPEN_MAX */

/* Maximum length of a timezone name (element of `tzname'). */
#ifndef TZNAME_MAX
#if defined(__TZNAME_MAX) && __TZNAME_MAX != -1
#define TZNAME_MAX __TZNAME_MAX
#elif defined(__USE_ALL_LIMITS)
#define TZNAME_MAX _POSIX_TZNAME_MAX
#endif /* ... */
#endif /* !TZNAME_MAX */

/* Minimum # of operations in one list I/O call. */
#ifndef AIO_LISTIO_MAX
#if defined(__AIO_LISTIO_MAX) && __AIO_LISTIO_MAX != -1
#define AIO_LISTIO_MAX __AIO_LISTIO_MAX
#elif defined(__USE_ALL_LIMITS)
#define AIO_LISTIO_MAX _POSIX_AIO_LISTIO_MAX
#endif /* ... */
#endif /* !AIO_LISTIO_MAX */

/* Minimal # of outstanding asynchronous I/O operations. */
#ifndef AIO_MAX
#if defined(__AIO_MAX) && __AIO_MAX != -1
#define AIO_MAX __AIO_MAX
#elif defined(__USE_ALL_LIMITS)
#define AIO_MAX _POSIX_AIO_MAX
#endif /* ... */
#endif /* !AIO_MAX */

/* Maximum length of arguments to `execve', including environment. */
#ifndef ARG_MAX
#if defined(__ARG_MAX) && __ARG_MAX != -1
#define ARG_MAX __ARG_MAX
#else /* __ARG_MAX && __ARG_MAX != -1 */
#define ARG_MAX _POSIX_ARG_MAX
#endif /* !__ARG_MAX || __ARG_MAX == -1 */
#endif /* !ARG_MAX */

/* Minimal # of timer expiration overruns. */
#ifndef DELAYTIMER_MAX
#if defined(__DELAYTIMER_MAX) && __DELAYTIMER_MAX != -1
#define DELAYTIMER_MAX __DELAYTIMER_MAX
#elif defined(__USE_ALL_LIMITS)
#define DELAYTIMER_MAX _POSIX_DELAYTIMER_MAX
#endif /* ... */
#endif /* !DELAYTIMER_MAX */

/* Maximum length of a host name (not including the terminating null) as returned by `gethostname(2)'. */
#ifndef HOST_NAME_MAX
#if defined(__HOST_NAME_MAX) && __HOST_NAME_MAX != -1
#define HOST_NAME_MAX __HOST_NAME_MAX
#elif defined(__USE_ALL_LIMITS)
#define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#endif /* ... */
#endif /* !HOST_NAME_MAX */

/* Maximum link count of a file. */
#ifndef LINK_MAX
#if defined(__LINK_MAX) && __LINK_MAX != -1
#define LINK_MAX __LINK_MAX
#else /* __LINK_MAX && __LINK_MAX != -1 */
#define LINK_MAX _POSIX_LINK_MAX
#endif /* !__LINK_MAX || __LINK_MAX == -1 */
#endif /* !LINK_MAX */

/* Maximum length of login name. */
#ifndef LOGIN_NAME_MAX
#if defined(__LOGIN_NAME_MAX) && __LOGIN_NAME_MAX != -1
#define LOGIN_NAME_MAX __LOGIN_NAME_MAX
#elif defined(__USE_ALL_LIMITS)
#define LOGIN_NAME_MAX _POSIX_LOGIN_NAME_MAX
#endif /* ... */
#endif /* !LOGIN_NAME_MAX */

/* Number of bytes in a terminal canonical input queue. */
#ifndef MAX_CANON
#if defined(__MAX_CANON) && __MAX_CANON != -1
#define MAX_CANON __MAX_CANON
#else /* __MAX_CANON && __MAX_CANON != -1 */
#define MAX_CANON _POSIX_MAX_CANON
#endif /* !__MAX_CANON || __MAX_CANON == -1 */
#endif /* !MAX_CANON */

/* Number of bytes for which space will be available in a terminal input queue. */
#ifndef MAX_INPUT
#if defined(__MAX_INPUT) && __MAX_INPUT != -1
#define MAX_INPUT __MAX_INPUT
#else /* __MAX_INPUT && __MAX_INPUT != -1 */
#define MAX_INPUT _POSIX_MAX_INPUT
#endif /* !__MAX_INPUT || __MAX_INPUT == -1 */
#endif /* !MAX_INPUT */

/* Maximum # of message queues open for a process. */
#ifndef MQ_OPEN_MAX
#if defined(__MQ_OPEN_MAX) && __MQ_OPEN_MAX != -1
#define MQ_OPEN_MAX __MQ_OPEN_MAX
#elif defined(__USE_ALL_LIMITS)
#define MQ_OPEN_MAX _POSIX_MQ_OPEN_MAX
#endif /* ... */
#endif /* !MQ_OPEN_MAX */

/* Maximum # of supported message priorities. */
#ifndef MQ_PRIO_MAX
#if defined(__MQ_PRIO_MAX) && __MQ_PRIO_MAX != -1
#define MQ_PRIO_MAX __MQ_PRIO_MAX
#elif defined(__USE_ALL_LIMITS)
#define MQ_PRIO_MAX _POSIX_MQ_PRIO_MAX
#endif /* ... */
#endif /* !MQ_PRIO_MAX */

/* Number of bytes in a filename. */
#ifndef NAME_MAX
#if defined(__NAME_MAX) && __NAME_MAX != -1
#define NAME_MAX __NAME_MAX
#else /* __NAME_MAX && __NAME_MAX != -1 */
#define NAME_MAX _POSIX_NAME_MAX
#endif /* !__NAME_MAX || __NAME_MAX == -1 */
#endif /* !NAME_MAX */

/* Number of bytes in a pathname. (Not defined by default because some programs
 * think `defined(MAX_PATH)' -> chdir(2) fails for paths longer than this) */
#ifndef PATH_MAX
#if defined(__PATH_MAX) && __PATH_MAX != -1
#define PATH_MAX __PATH_MAX
#elif defined(__USE_ALL_LIMITS)
#define PATH_MAX _POSIX_PATH_MAX
#endif /* ... */
#endif /* !PATH_MAX */

/* Number of bytes than can be written atomically to a pipe. */
#ifndef PIPE_BUF
#if defined(__PIPE_BUF) && __PIPE_BUF != -1
#define PIPE_BUF __PIPE_BUF
#elif defined(__USE_ALL_LIMITS)
#define PIPE_BUF _POSIX_PIPE_BUF
#endif /* ... */
#endif /* !PIPE_BUF */

/* Max # of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation. */
#ifndef RE_DUP_MAX
#if defined(__RE_DUP_MAX) && __RE_DUP_MAX != -1
#define RE_DUP_MAX __RE_DUP_MAX
#else /* __RE_DUP_MAX && __RE_DUP_MAX != -1 */
#define RE_DUP_MAX _POSIX_RE_DUP_MAX
#endif /* !__RE_DUP_MAX || __RE_DUP_MAX == -1 */
#endif /* !RE_DUP_MAX */

/* Minimal # of realtime signals reserved for the application. */
#ifndef RTSIG_MAX
#if defined(__RTSIG_MAX) && __RTSIG_MAX != -1
#define RTSIG_MAX __RTSIG_MAX
#else /* __RTSIG_MAX && __RTSIG_MAX != -1 */
#define RTSIG_MAX _POSIX_RTSIG_MAX
#endif /* !__RTSIG_MAX || __RTSIG_MAX == -1 */
#endif /* !RTSIG_MAX */

/* <semaphore.h>: Number of semaphores a process can have. */
#ifndef SEM_NSEMS_MAX
#if defined(__SEM_NSEMS_MAX) && __SEM_NSEMS_MAX != -1
#define SEM_NSEMS_MAX __SEM_NSEMS_MAX
#elif defined(__USE_ALL_LIMITS)
#define SEM_NSEMS_MAX _POSIX_SEM_NSEMS_MAX
#endif /* ... */
#endif /* !SEM_NSEMS_MAX */

/* <semaphore.h>: Maximal value of a semaphore. */
#ifndef SEM_VALUE_MAX
#if defined(__SEM_VALUE_MAX) && __SEM_VALUE_MAX != -1
#define SEM_VALUE_MAX __SEM_VALUE_MAX
#elif defined(__USE_ALL_LIMITS)
#define SEM_VALUE_MAX _POSIX_SEM_VALUE_MAX
#endif /* ... */
#endif /* !SEM_VALUE_MAX */

/* Number of pending realtime signals. */
#ifndef SIGQUEUE_MAX
#if defined(__SIGQUEUE_MAX) && __SIGQUEUE_MAX != -1
#define SIGQUEUE_MAX __SIGQUEUE_MAX
#elif defined(__USE_ALL_LIMITS)
#define SIGQUEUE_MAX _POSIX_SIGQUEUE_MAX
#endif /* ... */
#endif /* !SIGQUEUE_MAX */

/* <stdio.h>: Number of streams a process can have open at once. */
#ifndef STREAM_MAX
#if defined(__STREAM_MAX) && __STREAM_MAX != -1
#define STREAM_MAX __STREAM_MAX
#elif defined(__USE_ALL_LIMITS)
#define STREAM_MAX _POSIX_STREAM_MAX
#endif /* ... */
#endif /* !STREAM_MAX */

/* Max # of bytes in a symbolic link. */
#ifndef SYMLINK_MAX
#if defined(__SYMLINK_MAX) && __SYMLINK_MAX != -1
#define SYMLINK_MAX __SYMLINK_MAX
#elif defined(__USE_ALL_LIMITS)
#define SYMLINK_MAX _POSIX_SYMLINK_MAX
#endif /* ... */
#endif /* !SYMLINK_MAX */

/* Max # of symbolic links that can be traversed in the resolution of a pathname in the absence of a loop. */
#ifndef SYMLOOP_MAX
#if defined(__SYMLOOP_MAX) && __SYMLOOP_MAX != -1
#define SYMLOOP_MAX __SYMLOOP_MAX
#else /* __SYMLOOP_MAX && __SYMLOOP_MAX != -1 */
#define SYMLOOP_MAX _POSIX_SYMLOOP_MAX
#endif /* !__SYMLOOP_MAX || __SYMLOOP_MAX == -1 */
#endif /* !SYMLOOP_MAX */

/* Number of timer for a process. */
#ifndef TIMER_MAX
#if defined(__TIMER_MAX) && __TIMER_MAX != -1
#define TIMER_MAX __TIMER_MAX
#elif defined(__USE_ALL_LIMITS)
#define TIMER_MAX _POSIX_TIMER_MAX
#endif /* ... */
#endif /* !TIMER_MAX */

/* Maximum # of characters in a tty name. */
#ifndef TTY_NAME_MAX
#if defined(__TTY_NAME_MAX) && __TTY_NAME_MAX != -1
#define TTY_NAME_MAX __TTY_NAME_MAX
#elif defined(__USE_ALL_LIMITS)
#define TTY_NAME_MAX _POSIX_TTY_NAME_MAX
#endif /* ... */
#endif /* !TTY_NAME_MAX */

/* Maximum clock resolution in nanoseconds. */
#ifndef CLOCKRES_MIN
#if defined(__CLOCKRES_MIN) && __CLOCKRES_MIN != -1
#define CLOCKRES_MIN __CLOCKRES_MIN
#elif defined(__USE_ALL_LIMITS)
#define CLOCKRES_MIN _POSIX_CLOCKRES_MIN
#endif /* ... */
#endif /* !CLOCKRES_MIN */

/* <pthread.h>: Max # of data keys per process. */
#ifndef THREAD_KEYS_MAX
#if defined(__PTHREAD_KEYS_MAX) && __PTHREAD_KEYS_MAX != -1
#define THREAD_KEYS_MAX __PTHREAD_KEYS_MAX
#elif defined(__USE_ALL_LIMITS)
#define THREAD_KEYS_MAX _POSIX_THREAD_KEYS_MAX
#endif /* ... */
#endif /* !THREAD_KEYS_MAX */

/* <pthread.h>: Max # of iterations of destructors for thread-specific data. */
#ifndef THREAD_DESTRUCTOR_ITERATIONS
#if defined(__PTHREAD_DESTRUCTOR_ITERATIONS) && __PTHREAD_DESTRUCTOR_ITERATIONS != -1
#define THREAD_DESTRUCTOR_ITERATIONS __PTHREAD_DESTRUCTOR_ITERATIONS
#elif defined(__USE_ALL_LIMITS)
#define THREAD_DESTRUCTOR_ITERATIONS _POSIX_THREAD_DESTRUCTOR_ITERATIONS
#endif /* ... */
#endif /* !THREAD_DESTRUCTOR_ITERATIONS */

/* <pthread.h>: Max # of threads per process. */
#ifndef THREAD_THREADS_MAX
#if defined(__PTHREAD_THREADS_MAX) && __PTHREAD_THREADS_MAX != -1
#define THREAD_THREADS_MAX __PTHREAD_THREADS_MAX
#elif defined(__USE_ALL_LIMITS)
#define THREAD_THREADS_MAX _POSIX_THREAD_THREADS_MAX
#endif /* ... */
#endif /* !THREAD_THREADS_MAX */
//[[[end]]]

/* <pthread.h>: Max # of data keys per process. */
#ifndef PTHREAD_KEYS_MAX
#if __PTHREAD_KEYS_MAX != -1
#define PTHREAD_KEYS_MAX __PTHREAD_KEYS_MAX
#elif defined(__USE_ALL_LIMITS)
#define PTHREAD_KEYS_MAX _POSIX_THREAD_KEYS_MAX
#endif /* ... */
#endif /* !PTHREAD_KEYS_MAX */

/* <pthread.h>: Minimum size for a thread. */
#ifndef PTHREAD_STACK_MIN
#if __PTHREAD_STACK_MIN != -1
#define PTHREAD_STACK_MIN __PTHREAD_STACK_MIN
#elif defined(__USE_ALL_LIMITS)
#define PTHREAD_STACK_MIN 16384
#endif /* ... */
#endif /* !PTHREAD_STACK_MIN */

/* <pthread.h>: Max # of iterations of destructors for thread-specific data. */
#ifndef PTHREAD_DESTRUCTOR_ITERATIONS
#if __PTHREAD_DESTRUCTOR_ITERATIONS != -1
#define PTHREAD_DESTRUCTOR_ITERATIONS __PTHREAD_DESTRUCTOR_ITERATIONS
#elif defined(__USE_ALL_LIMITS)
#define PTHREAD_DESTRUCTOR_ITERATIONS _POSIX_THREAD_DESTRUCTOR_ITERATIONS
#endif /* ... */
#endif /* !PTHREAD_DESTRUCTOR_ITERATIONS */

/* <pthread.h>: Max # of threads per process. */
#ifndef PTHREAD_THREADS_MAX
#if __PTHREAD_THREADS_MAX != -1
#define PTHREAD_THREADS_MAX __PTHREAD_THREADS_MAX
#elif defined(__USE_ALL_LIMITS)
#define PTHREAD_THREADS_MAX _POSIX_THREAD_THREADS_MAX
#endif /* ... */
#endif /* !PTHREAD_THREADS_MAX */

/* Maximum amount by which a process can decrease its asynchronous I/O priority level. */
#ifndef AIO_PRIO_DELTA_MAX
#if __AIO_PRIO_DELTA_MAX != -1
#define AIO_PRIO_DELTA_MAX __AIO_PRIO_DELTA_MAX
#elif defined(__USE_ALL_LIMITS)
#define AIO_PRIO_DELTA_MAX 0
#endif /* ... */
#endif /* !AIO_PRIO_DELTA_MAX */
#endif /* __USE_POSIX */



/************************************************************************/
/* POSIX.2                                                              */
/************************************************************************/
#if defined(__USE_POSIX2) || defined(__DEEMON__)
#ifndef _POSIX2_RE_DUP_MAX
#define _POSIX2_RE_DUP_MAX 255 /* The  maximum  number  of  repeated  occurrences  of  a   regular
                                * expression permitted when using the interval notation `\{M,N\}'. */
#endif /* !_POSIX2_RE_DUP_MAX */

/* The  maximum  number  of  repeated  occurrences  of  a   regular
 * expression permitted when using the interval notation `\{M,N\}'. */
#ifndef RE_DUP_MAX
#ifndef __RE_DUP_MAX
#define __RE_DUP_MAX _POSIX2_RE_DUP_MAX
#endif /* !__RE_DUP_MAX */
#if __RE_DUP_MAX != -1
#define RE_DUP_MAX __RE_DUP_MAX
#elif defined(__USE_ALL_LIMITS)
#define RE_DUP_MAX _POSIX2_RE_DUP_MAX
#endif /* ... */
#endif /* !RE_DUP_MAX */


/*[[[deemon
@@List of (name, posixName, posixMinimum, doc)
local limits = {
	(0, "BC_BASE_MAX",        "_POSIX2_BC_BASE_MAX",        "99",   "The maximum `ibase' and `obase' values allowed by the `bc' utility."),
	(0, "BC_DIM_MAX",         "_POSIX2_BC_DIM_MAX",         "2048", "The maximum number of elements allowed in an array by the `bc' utility."),
	(0, "BC_SCALE_MAX",       "_POSIX2_BC_SCALE_MAX",       "99",   "The maximum `scale' value allowed by the `bc' utility."),
	(0, "BC_STRING_MAX",      "_POSIX2_BC_STRING_MAX",      "1000", "The maximum length of a string constant accepted by the `bc' utility."),
	(0, "COLL_WEIGHTS_MAX",   "_POSIX2_COLL_WEIGHTS_MAX",   "2",    "The maximum number of weights that can be assigned to an entry of the LC_COLLATE `order' keyword in the locale definition file."),
	(0, "EXPR_NEST_MAX",      "_POSIX2_EXPR_NEST_MAX",      "32",   "The maximum number of expressions that can be nested within parentheses by the `expr' utility."),
	(1, "LINE_MAX",           "_POSIX2_LINE_MAX",           "2048", "The maximum length, in bytes, of an input line."),
	(0, "CHARCLASS_NAME_MAX", "_POSIX2_CHARCLASS_NAME_MAX", "14",   "The maximum number of bytes in a character class name.  We have no fixed limit, 2048 is a high number."),
};

local longestPosixNameLength    = limits.each[2].length > ...;
local longestPosixMinimumLength = (for (local x: limits) x[2] ? #x[3] : 0) > ...;

print("/" "* Posix-mandated minimum limits. *" "/");
for (local none, none, posixName, posixMinimum, doc: limits) {
	if (!posixName)
		continue;
	print("#ifndef ", posixName);
	print("#define ", posixName, " " * (longestPosixNameLength - #posixName),
		" ", posixMinimum, " " * (longestPosixMinimumLength - #posixMinimum),
		" /" "* ", doc, " *" "/");
	print("#endif /" "* !", posixName, " *" "/");
}
print;
print;
print("/" "* Substitute unknown system/crt limits. *" "/");
for (local none, name, posixName, posixMinimum, doc: limits) {
	print("#ifndef __", name);
	print("#define __", name, " ",
		posixName ? posixName : posixMinimum,
		" /" "* ", doc, " *" "/");
	print("#endif /" "* !__", name, " *" "/");
}
print;
print;
print("/" "* Actual implementation limits. *" "/");
for (local alwaysUseMinimum, name, posixName, posixMinimum, doc: limits) {
	print();
	print("/" "* ", doc, " *" "/");
	print("#ifndef ", name);
	print("#if __", name, " != -1");
	print("#define ", name, " __", name);
	if (alwaysUseMinimum) {
		print("#else /" "* __", name, " != -1 *" "/");
		print("#define ", name, " ", posixName ? posixName : posixMinimum);
		print("#endif /" "* __", name, " == -1 *" "/");
	} else {
		print("#elif defined(__USE_ALL_LIMITS)");
		print("#define ", name, " ", posixName ? posixName : posixMinimum);
		print("#endif /" "* ... *" "/");
	}
	print("#endif /" "* !", name, " *" "/");
}
]]]*/
/* Posix-mandated minimum limits. */
#ifndef _POSIX2_BC_BASE_MAX
#define _POSIX2_BC_BASE_MAX        99   /* The maximum `ibase' and `obase' values allowed by the `bc' utility. */
#endif /* !_POSIX2_BC_BASE_MAX */
#ifndef _POSIX2_BC_DIM_MAX
#define _POSIX2_BC_DIM_MAX         2048 /* The maximum number of elements allowed in an array by the `bc' utility. */
#endif /* !_POSIX2_BC_DIM_MAX */
#ifndef _POSIX2_BC_SCALE_MAX
#define _POSIX2_BC_SCALE_MAX       99   /* The maximum `scale' value allowed by the `bc' utility. */
#endif /* !_POSIX2_BC_SCALE_MAX */
#ifndef _POSIX2_BC_STRING_MAX
#define _POSIX2_BC_STRING_MAX      1000 /* The maximum length of a string constant accepted by the `bc' utility. */
#endif /* !_POSIX2_BC_STRING_MAX */
#ifndef _POSIX2_COLL_WEIGHTS_MAX
#define _POSIX2_COLL_WEIGHTS_MAX   2    /* The maximum number of weights that can be assigned to an entry of the LC_COLLATE `order' keyword in the locale definition file. */
#endif /* !_POSIX2_COLL_WEIGHTS_MAX */
#ifndef _POSIX2_EXPR_NEST_MAX
#define _POSIX2_EXPR_NEST_MAX      32   /* The maximum number of expressions that can be nested within parentheses by the `expr' utility. */
#endif /* !_POSIX2_EXPR_NEST_MAX */
#ifndef _POSIX2_LINE_MAX
#define _POSIX2_LINE_MAX           2048 /* The maximum length, in bytes, of an input line. */
#endif /* !_POSIX2_LINE_MAX */
#ifndef _POSIX2_CHARCLASS_NAME_MAX
#define _POSIX2_CHARCLASS_NAME_MAX 14   /* The maximum number of bytes in a character class name.  We have no fixed limit, 2048 is a high number. */
#endif /* !_POSIX2_CHARCLASS_NAME_MAX */


/* Substitute unknown system/crt limits. */
#ifndef __BC_BASE_MAX
#define __BC_BASE_MAX _POSIX2_BC_BASE_MAX /* The maximum `ibase' and `obase' values allowed by the `bc' utility. */
#endif /* !__BC_BASE_MAX */
#ifndef __BC_DIM_MAX
#define __BC_DIM_MAX _POSIX2_BC_DIM_MAX /* The maximum number of elements allowed in an array by the `bc' utility. */
#endif /* !__BC_DIM_MAX */
#ifndef __BC_SCALE_MAX
#define __BC_SCALE_MAX _POSIX2_BC_SCALE_MAX /* The maximum `scale' value allowed by the `bc' utility. */
#endif /* !__BC_SCALE_MAX */
#ifndef __BC_STRING_MAX
#define __BC_STRING_MAX _POSIX2_BC_STRING_MAX /* The maximum length of a string constant accepted by the `bc' utility. */
#endif /* !__BC_STRING_MAX */
#ifndef __COLL_WEIGHTS_MAX
#define __COLL_WEIGHTS_MAX _POSIX2_COLL_WEIGHTS_MAX /* The maximum number of weights that can be assigned to an entry of the LC_COLLATE `order' keyword in the locale definition file. */
#endif /* !__COLL_WEIGHTS_MAX */
#ifndef __EXPR_NEST_MAX
#define __EXPR_NEST_MAX _POSIX2_EXPR_NEST_MAX /* The maximum number of expressions that can be nested within parentheses by the `expr' utility. */
#endif /* !__EXPR_NEST_MAX */
#ifndef __LINE_MAX
#define __LINE_MAX _POSIX2_LINE_MAX /* The maximum length, in bytes, of an input line. */
#endif /* !__LINE_MAX */
#ifndef __CHARCLASS_NAME_MAX
#define __CHARCLASS_NAME_MAX _POSIX2_CHARCLASS_NAME_MAX /* The maximum number of bytes in a character class name.  We have no fixed limit, 2048 is a high number. */
#endif /* !__CHARCLASS_NAME_MAX */


/* Actual implementation limits. */

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

/* The maximum number of bytes in a character class name.  We have no fixed limit, 2048 is a high number. */
#ifndef CHARCLASS_NAME_MAX
#if __CHARCLASS_NAME_MAX != -1
#define CHARCLASS_NAME_MAX __CHARCLASS_NAME_MAX
#elif defined(__USE_ALL_LIMITS)
#define CHARCLASS_NAME_MAX _POSIX2_CHARCLASS_NAME_MAX
#endif /* ... */
#endif /* !CHARCLASS_NAME_MAX */
//[[[end]]]
#endif /* __USE_POSIX2 */



/************************************************************************/
/* X/OPEN                                                               */
/************************************************************************/
#if defined(__USE_XOPEN) || defined(__USE_NETBSD) || defined(__DEEMON__)
#include <asm/pagesize.h>

/* System memory page size */
#if !defined(PAGESIZE) && !defined(__ARCH_PAGESIZE)
#define PAGESIZE __ARCH_PAGESIZE
#endif /* !PAGESIZE && __ARCH_PAGESIZE */

/* System memory page size */
#if !defined(PAGE_SIZE) && !defined(__ARCH_PAGESIZE)
#define PAGE_SIZE __ARCH_PAGESIZE
#endif /* !PAGE_SIZE && __ARCH_PAGESIZE */

#if !defined(NZERO) && defined(__NZERO)
#define NZERO __NZERO /* Default process priority. */
#endif /* !NZERO && __NZERO */

#ifndef WORD_BIT
#if __INT_MAX__ == __INT8_MAX__
#define WORD_BIT 8 /* Number of bits in a word of type `int'. */
#elif __INT_MAX__ == __INT16_MAX__
#define WORD_BIT 16 /* Number of bits in a word of type `int'. */
#elif __INT_MAX__ == __INT32_MAX__
#define WORD_BIT 32 /* Number of bits in a word of type `int'. */
#elif __INT_MAX__ == __INT64_MAX__
#define WORD_BIT 64 /* Number of bits in a word of type `int'. */
#else /* __INT_MAX__ == ... */
#define WORD_BIT (__SIZEOF_INT__ * 8) /* Number of bits in a word of type `int'. */
#endif /* __INT_MAX__ != ... */
#endif /* !WORD_BIT */

#ifndef LONG_BIT
#if __LONG_MAX__ == __INT8_MAX__
#define LONG_BIT 8 /* Number of bits in a word of type `long int'. */
#elif __LONG_MAX__ == __INT16_MAX__
#define LONG_BIT 16 /* Number of bits in a word of type `long int'. */
#elif __LONG_MAX__ == __INT32_MAX__
#define LONG_BIT 32 /* Number of bits in a word of type `long int'. */
#elif __LONG_MAX__ == __INT64_MAX__
#define LONG_BIT 64 /* Number of bits in a word of type `long int'. */
#else /* __LONG_MAX__ == ... */
#define LONG_BIT (__SIZEOF_INT__ * 8) /* Number of bits in a word of type `long int'. */
#endif /* __LONG_MAX__ != ... */
#endif /* !LONG_BIT */

/* X/Open-mandated minimum limits. */
#ifndef _XOPEN_IOV_MAX
#define _XOPEN_IOV_MAX 16 /* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#endif /* !_XOPEN_IOV_MAX */


/* Substitute unknown system/crt limits. */
#ifndef __IOV_MAX
#define __IOV_MAX _XOPEN_IOV_MAX /* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#endif /* !__IOV_MAX */
#ifndef __NL_ARGMAX
#define __NL_ARGMAX 4096 /* [default:_POSIX_ARG_MAX] Maximum number of positional arguments (e.g. "%1$d") in calls to `printf' or `scanf'. */
#endif /* !__NL_ARGMAX */
#ifndef __NL_LANGMAX
#define __NL_LANGMAX 2048 /* <libintl.h>: Maximum number of bytes in a `LANG' name. */
#endif /* !__NL_LANGMAX */
#ifndef __NL_MSGMAX
#define __NL_MSGMAX __INT_MAX__ /* Maximum message number. */
#endif /* !__NL_MSGMAX */
#ifndef __NL_NMAX
#define __NL_NMAX __INT_MAX__ /* Maximum number of bytes in N-to-1 collation mapping. */
#endif /* !__NL_NMAX */
#ifndef __NL_SETMAX
#define __NL_SETMAX __INT_MAX__ /* Maximum set number. */
#endif /* !__NL_SETMAX */
#ifndef __NL_TEXTMAX
#define __NL_TEXTMAX __INT_MAX__ /* Maximum number of bytes in a message. */
#endif /* !__NL_TEXTMAX */


/* Actual implementation limits. */

/* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#ifndef IOV_MAX
#if __IOV_MAX != -1
#define IOV_MAX __IOV_MAX
#else /* __IOV_MAX != -1 */
#define IOV_MAX _XOPEN_IOV_MAX
#endif /* __IOV_MAX == -1 */
#endif /* !IOV_MAX */

/* [default:_POSIX_ARG_MAX] Maximum number of positional arguments (e.g. "%1$d") in calls to `printf' or `scanf'. */
#ifndef NL_ARGMAX
#if __NL_ARGMAX != -1
#define NL_ARGMAX __NL_ARGMAX
#elif defined(__USE_ALL_LIMITS)
#define NL_ARGMAX 4096
#endif /* ... */
#endif /* !NL_ARGMAX */

/* [default:_POSIX2_LINE_MAX] <libintl.h>: Maximum number of bytes in a `LANG' name. */
#ifndef NL_LANGMAX
#if __NL_LANGMAX != -1
#define NL_LANGMAX __NL_LANGMAX
#elif defined(__USE_ALL_LIMITS)
#define NL_LANGMAX 2048
#endif /* ... */
#endif /* !NL_LANGMAX */

/* Maximum message number. */
#ifndef NL_MSGMAX
#if __NL_MSGMAX != -1
#define NL_MSGMAX __NL_MSGMAX
#elif defined(__USE_ALL_LIMITS)
#define NL_MSGMAX __INT_MAX__
#endif /* ... */
#endif /* !NL_MSGMAX */

/* Maximum number of bytes in N-to-1 collation mapping. */
#ifndef NL_NMAX
#if __NL_NMAX != -1
#define NL_NMAX __NL_NMAX
#elif defined(__USE_ALL_LIMITS)
#define NL_NMAX __INT_MAX__
#endif /* ... */
#endif /* !NL_NMAX */

/* Maximum set number. */
#ifndef NL_SETMAX
#if __NL_SETMAX != -1
#define NL_SETMAX __NL_SETMAX
#elif defined(__USE_ALL_LIMITS)
#define NL_SETMAX __INT_MAX__
#endif /* ... */
#endif /* !NL_SETMAX */

/* Maximum number of bytes in a message. */
#ifndef NL_TEXTMAX
#if __NL_TEXTMAX != -1
#define NL_TEXTMAX __NL_TEXTMAX
#elif defined(__USE_ALL_LIMITS)
#define NL_TEXTMAX __INT_MAX__
#endif /* ... */
#endif /* !NL_TEXTMAX */

#endif /* __USE_XOPEN || __USE_NETBSD */

#endif /* !_LIMITS_H */
