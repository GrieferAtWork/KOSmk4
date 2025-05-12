/* HASH CRC-32:0x617cae96 */
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
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/pthread.h) */
/* (#) Portability: DragonFly BSD (/include/pthread.h) */
/* (#) Portability: FreeBSD       (/include/pthread.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/pthread.h) */
/* (#) Portability: GNU Hurd      (/usr/include/pthread.h) */
/* (#) Portability: MinGW         (/mingw-w64-libraries/winpthreads/include/pthread.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/pthread.h) */
/* (#) Portability: OpenBSD       (/include/pthread.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/pthread.h) */
/* (#) Portability: diet libc     (/include/pthread.h) */
/* (#) Portability: libc6         (/include/pthread.h) */
/* (#) Portability: musl libc     (/include/pthread.h) */
/* (#) Portability: uClibc        (/libpthread/nptl/sysdeps/pthread/pthread.h) */
#ifndef _PTHREAD_H
#define _PTHREAD_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/crt/setjmp.h>
#include <bits/os/cpu_set.h>
#include <bits/types.h>
#include <kos/anno.h>

#ifdef __INTELLISENSE__
#include <bits/types/size_t.h>
#endif /* __INTELLISENSE__ */

#ifdef __USE_GLIBC_BLOAT
#include <endian.h>
#include <sched.h>
#include <time.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Detach state. */
#ifndef __PTHREAD_ENUM_DETACH_STATE_DEFINED
#define __PTHREAD_ENUM_DETACH_STATE_DEFINED 1
#if ((!defined(PTHREAD_CREATE_JOINABLE) && defined(__PTHREAD_CREATE_JOINABLE)) || \
     (!defined(PTHREAD_CREATE_DETACHED) && defined(__PTHREAD_CREATE_DETACHED)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_CREATE_JOINABLE) && defined(__PTHREAD_CREATE_JOINABLE)
	PTHREAD_CREATE_JOINABLE = __PTHREAD_CREATE_JOINABLE,
#endif /* !PTHREAD_CREATE_JOINABLE && __PTHREAD_CREATE_JOINABLE */
#if !defined(PTHREAD_CREATE_DETACHED) && defined(__PTHREAD_CREATE_DETACHED)
	PTHREAD_CREATE_DETACHED = __PTHREAD_CREATE_DETACHED
#endif /* !PTHREAD_CREATE_DETACHED && __PTHREAD_CREATE_DETACHED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_CREATE_JOINABLE) && defined(__PTHREAD_CREATE_JOINABLE)
#define PTHREAD_CREATE_JOINABLE PTHREAD_CREATE_JOINABLE
#endif /* !PTHREAD_CREATE_JOINABLE && __PTHREAD_CREATE_JOINABLE */
#if !defined(PTHREAD_CREATE_DETACHED) && defined(__PTHREAD_CREATE_DETACHED)
#define PTHREAD_CREATE_DETACHED PTHREAD_CREATE_DETACHED
#endif /* !PTHREAD_CREATE_DETACHED && __PTHREAD_CREATE_DETACHED */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_CREATE_JOINABLE) && defined(__PTHREAD_CREATE_JOINABLE)
#define PTHREAD_CREATE_JOINABLE __PTHREAD_CREATE_JOINABLE
#endif /* !PTHREAD_CREATE_JOINABLE && __PTHREAD_CREATE_JOINABLE */
#if !defined(PTHREAD_CREATE_DETACHED) && defined(__PTHREAD_CREATE_DETACHED)
#define PTHREAD_CREATE_DETACHED __PTHREAD_CREATE_DETACHED
#endif /* !PTHREAD_CREATE_DETACHED && __PTHREAD_CREATE_DETACHED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __PTHREAD_CREATE_JOINABLE || __PTHREAD_CREATE_DETACHED */
#endif /* !__PTHREAD_ENUM_DETACH_STATE_DEFINED */



/* Mutex types. */
#ifndef __PTHREAD_ENUM_MUTEX_TYPE_DEFINED
#define __PTHREAD_ENUM_MUTEX_TYPE_DEFINED 1
#if ((!defined(PTHREAD_MUTEX_TIMED) && defined(__PTHREAD_MUTEX_TIMED)) ||                                 \
     (!defined(PTHREAD_MUTEX_RECURSIVE) && defined(__PTHREAD_MUTEX_RECURSIVE)) ||                         \
     (!defined(PTHREAD_MUTEX_ERRORCHECK) && defined(__PTHREAD_MUTEX_ERRORCHECK)) ||                       \
     (!defined(PTHREAD_MUTEX_ADAPTIVE) && defined(__PTHREAD_MUTEX_ADAPTIVE)) ||                           \
     (defined(__USE_XOPEN2K) && ((!defined(PTHREAD_MUTEX_STALLED) && defined(__PTHREAD_MUTEX_STALLED)) || \
                                 (!defined(PTHREAD_MUTEX_ROBUST) && defined(__PTHREAD_MUTEX_ROBUST)))))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_MUTEX_TIMED_NP) && defined(__PTHREAD_MUTEX_TIMED)
	PTHREAD_MUTEX_TIMED_NP      = __PTHREAD_MUTEX_TIMED,
#endif /* !PTHREAD_MUTEX_TIMED_NP && __PTHREAD_MUTEX_TIMED */
#if !defined(PTHREAD_MUTEX_RECURSIVE_NP) && defined(__PTHREAD_MUTEX_RECURSIVE)
	PTHREAD_MUTEX_RECURSIVE_NP  = __PTHREAD_MUTEX_RECURSIVE,
#endif /* !PTHREAD_MUTEX_RECURSIVE_NP && __PTHREAD_MUTEX_RECURSIVE */
#if !defined(PTHREAD_MUTEX_ERRORCHECK_NP) && defined(__PTHREAD_MUTEX_ERRORCHECK)
	PTHREAD_MUTEX_ERRORCHECK_NP = __PTHREAD_MUTEX_ERRORCHECK,
#endif /* !PTHREAD_MUTEX_ERRORCHECK_NP && __PTHREAD_MUTEX_ERRORCHECK */
#if !defined(PTHREAD_MUTEX_ADAPTIVE_NP) && defined(__PTHREAD_MUTEX_ADAPTIVE)
	PTHREAD_MUTEX_ADAPTIVE_NP   = __PTHREAD_MUTEX_ADAPTIVE,
#endif /* !PTHREAD_MUTEX_ADAPTIVE_NP && __PTHREAD_MUTEX_ADAPTIVE */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#if !defined(PTHREAD_MUTEX_NORMAL) && defined(__PTHREAD_MUTEX_TIMED)
	PTHREAD_MUTEX_NORMAL     = __PTHREAD_MUTEX_TIMED,
#endif /* !PTHREAD_MUTEX_NORMAL && __PTHREAD_MUTEX_TIMED */
#if !defined(PTHREAD_MUTEX_RECURSIVE) && defined(__PTHREAD_MUTEX_RECURSIVE)
	PTHREAD_MUTEX_RECURSIVE  = __PTHREAD_MUTEX_RECURSIVE,
#endif /* !PTHREAD_MUTEX_RECURSIVE && __PTHREAD_MUTEX_RECURSIVE */
#if !defined(PTHREAD_MUTEX_ERRORCHECK) && defined(__PTHREAD_MUTEX_ERRORCHECK)
	PTHREAD_MUTEX_ERRORCHECK = __PTHREAD_MUTEX_ERRORCHECK,
#endif /* !PTHREAD_MUTEX_ERRORCHECK && __PTHREAD_MUTEX_ERRORCHECK */
#if !defined(PTHREAD_MUTEX_DEFAULT) && defined(__PTHREAD_MUTEX_TIMED)
	PTHREAD_MUTEX_DEFAULT    = __PTHREAD_MUTEX_TIMED,
#endif /* !PTHREAD_MUTEX_DEFAULT && __PTHREAD_MUTEX_TIMED */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#if !defined(PTHREAD_MUTEX_FAST_NP) && defined(__PTHREAD_MUTEX_TIMED)
	PTHREAD_MUTEX_FAST_NP = __PTHREAD_MUTEX_TIMED, /* Compatibility alias. */
#endif /* !PTHREAD_MUTEX_FAST_NP && __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
#ifndef PTHREAD_MUTEX_STALLED
	PTHREAD_MUTEX_STALLED    = __PTHREAD_MUTEX_STALLED, /* Not a robust mutex. */
#endif /* !PTHREAD_MUTEX_STALLED */
#ifndef PTHREAD_MUTEX_STALLED_NP
	PTHREAD_MUTEX_STALLED_NP = __PTHREAD_MUTEX_STALLED, /* Not a robust mutex. */
#endif /* !PTHREAD_MUTEX_STALLED_NP */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
#ifndef PTHREAD_MUTEX_ROBUST
	PTHREAD_MUTEX_ROBUST     = __PTHREAD_MUTEX_ROBUST,  /* Robust mutex. */
#endif /* !PTHREAD_MUTEX_ROBUST */
#ifndef PTHREAD_MUTEX_ROBUST_NP
	PTHREAD_MUTEX_ROBUST_NP  = __PTHREAD_MUTEX_ROBUST,  /* Robust mutex. */
#endif /* !PTHREAD_MUTEX_ROBUST_NP */
#endif /* __PTHREAD_MUTEX_ROBUST */
#endif /* __USE_XOPEN2K */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_MUTEX_TIMED_NP) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_TIMED_NP      PTHREAD_MUTEX_TIMED_NP
#endif /* !PTHREAD_MUTEX_TIMED_NP && __PTHREAD_MUTEX_TIMED */
#if !defined(PTHREAD_MUTEX_RECURSIVE_NP) && defined(__PTHREAD_MUTEX_RECURSIVE)
#define PTHREAD_MUTEX_RECURSIVE_NP  PTHREAD_MUTEX_RECURSIVE_NP
#endif /* !PTHREAD_MUTEX_RECURSIVE_NP && __PTHREAD_MUTEX_RECURSIVE */
#if !defined(PTHREAD_MUTEX_ERRORCHECK_NP) && defined(__PTHREAD_MUTEX_ERRORCHECK)
#define PTHREAD_MUTEX_ERRORCHECK_NP PTHREAD_MUTEX_ERRORCHECK_NP
#endif /* !PTHREAD_MUTEX_ERRORCHECK_NP && __PTHREAD_MUTEX_ERRORCHECK */
#if !defined(PTHREAD_MUTEX_ADAPTIVE_NP) && defined(__PTHREAD_MUTEX_ADAPTIVE)
#define PTHREAD_MUTEX_ADAPTIVE_NP   PTHREAD_MUTEX_ADAPTIVE_NP
#endif /* !PTHREAD_MUTEX_ADAPTIVE_NP && __PTHREAD_MUTEX_ADAPTIVE */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#if !defined(PTHREAD_MUTEX_NORMAL) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_NORMAL        PTHREAD_MUTEX_NORMAL
#endif /* !PTHREAD_MUTEX_NORMAL && __PTHREAD_MUTEX_TIMED */
#if !defined(PTHREAD_MUTEX_RECURSIVE) && defined(__PTHREAD_MUTEX_RECURSIVE)
#define PTHREAD_MUTEX_RECURSIVE     PTHREAD_MUTEX_RECURSIVE
#endif /* !PTHREAD_MUTEX_RECURSIVE && __PTHREAD_MUTEX_RECURSIVE */
#if !defined(PTHREAD_MUTEX_ERRORCHECK) && defined(__PTHREAD_MUTEX_ERRORCHECK)
#define PTHREAD_MUTEX_ERRORCHECK    PTHREAD_MUTEX_ERRORCHECK
#endif /* !PTHREAD_MUTEX_ERRORCHECK && __PTHREAD_MUTEX_ERRORCHECK */
#if !defined(PTHREAD_MUTEX_DEFAULT) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_DEFAULT       PTHREAD_MUTEX_DEFAULT
#endif /* !PTHREAD_MUTEX_DEFAULT && __PTHREAD_MUTEX_TIMED */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#if !defined(PTHREAD_MUTEX_FAST_NP) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_FAST_NP       PTHREAD_MUTEX_FAST_NP       /* Compatibility alias. */
#endif /* !PTHREAD_MUTEX_FAST_NP && __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
#ifndef PTHREAD_MUTEX_STALLED
#define PTHREAD_MUTEX_STALLED       PTHREAD_MUTEX_STALLED       /* Not a robust mutex. */
#endif /* !PTHREAD_MUTEX_STALLED */
#ifndef PTHREAD_MUTEX_STALLED_NP
#define PTHREAD_MUTEX_STALLED_NP    PTHREAD_MUTEX_STALLED_NP    /* Not a robust mutex. */
#endif /* !PTHREAD_MUTEX_STALLED_NP */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
#ifndef PTHREAD_MUTEX_ROBUST
#define PTHREAD_MUTEX_ROBUST        PTHREAD_MUTEX_ROBUST        /* Robust mutex. */
#endif /* !PTHREAD_MUTEX_ROBUST */
#ifndef PTHREAD_MUTEX_ROBUST_NP
#define PTHREAD_MUTEX_ROBUST_NP     PTHREAD_MUTEX_ROBUST_NP     /* Robust mutex. */
#endif /* !PTHREAD_MUTEX_ROBUST_NP */
#endif /* __PTHREAD_MUTEX_ROBUST */
#endif /* __USE_XOPEN2K */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_MUTEX_TIMED_NP) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_TIMED_NP      __PTHREAD_MUTEX_TIMED
#endif /* !PTHREAD_MUTEX_TIMED_NP && __PTHREAD_MUTEX_TIMED */
#if !defined(PTHREAD_MUTEX_RECURSIVE_NP) && defined(__PTHREAD_MUTEX_RECURSIVE)
#define PTHREAD_MUTEX_RECURSIVE_NP  __PTHREAD_MUTEX_RECURSIVE
#endif /* !PTHREAD_MUTEX_RECURSIVE_NP && __PTHREAD_MUTEX_RECURSIVE */
#if !defined(PTHREAD_MUTEX_ERRORCHECK_NP) && defined(__PTHREAD_MUTEX_ERRORCHECK)
#define PTHREAD_MUTEX_ERRORCHECK_NP __PTHREAD_MUTEX_ERRORCHECK
#endif /* !PTHREAD_MUTEX_ERRORCHECK_NP && __PTHREAD_MUTEX_ERRORCHECK */
#if !defined(PTHREAD_MUTEX_ADAPTIVE_NP) && defined(__PTHREAD_MUTEX_ADAPTIVE)
#define PTHREAD_MUTEX_ADAPTIVE_NP   __PTHREAD_MUTEX_ADAPTIVE
#endif /* !PTHREAD_MUTEX_ADAPTIVE_NP && __PTHREAD_MUTEX_ADAPTIVE */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#if !defined(PTHREAD_MUTEX_NORMAL) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_NORMAL        __PTHREAD_MUTEX_TIMED
#endif /* !PTHREAD_MUTEX_NORMAL && __PTHREAD_MUTEX_TIMED */
#if !defined(PTHREAD_MUTEX_RECURSIVE) && defined(__PTHREAD_MUTEX_RECURSIVE)
#define PTHREAD_MUTEX_RECURSIVE     __PTHREAD_MUTEX_RECURSIVE
#endif /* !PTHREAD_MUTEX_RECURSIVE && __PTHREAD_MUTEX_RECURSIVE */
#if !defined(PTHREAD_MUTEX_ERRORCHECK) && defined(__PTHREAD_MUTEX_ERRORCHECK)
#define PTHREAD_MUTEX_ERRORCHECK    __PTHREAD_MUTEX_ERRORCHECK
#endif /* !PTHREAD_MUTEX_ERRORCHECK && __PTHREAD_MUTEX_ERRORCHECK */
#if !defined(PTHREAD_MUTEX_DEFAULT) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_DEFAULT       __PTHREAD_MUTEX_TIMED
#endif /* !PTHREAD_MUTEX_DEFAULT && __PTHREAD_MUTEX_TIMED */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#if !defined(PTHREAD_MUTEX_FAST_NP) && defined(__PTHREAD_MUTEX_TIMED)
#define PTHREAD_MUTEX_FAST_NP       __PTHREAD_MUTEX_TIMED      /* Compatibility alias. */
#endif /* !PTHREAD_MUTEX_FAST_NP && __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
#ifndef PTHREAD_MUTEX_STALLED
#define PTHREAD_MUTEX_STALLED       __PTHREAD_MUTEX_STALLED    /* Not a robust mutex. */
#endif /* !PTHREAD_MUTEX_STALLED */
#ifndef PTHREAD_MUTEX_STALLED_NP
#define PTHREAD_MUTEX_STALLED_NP    __PTHREAD_MUTEX_STALLED    /* Not a robust mutex. */
#endif /* !PTHREAD_MUTEX_STALLED_NP */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
#ifndef PTHREAD_MUTEX_ROBUST
#define PTHREAD_MUTEX_ROBUST        __PTHREAD_MUTEX_ROBUST     /* Robust mutex. */
#endif /* !PTHREAD_MUTEX_ROBUST */
#ifndef PTHREAD_MUTEX_ROBUST_NP
#define PTHREAD_MUTEX_ROBUST_NP     __PTHREAD_MUTEX_ROBUST     /* Robust mutex. */
#endif /* !PTHREAD_MUTEX_ROBUST_NP */
#endif /* __PTHREAD_MUTEX_ROBUST */
#endif /* __USE_XOPEN2K */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !__PTHREAD_ENUM_MUTEX_TYPE_DEFINED */


#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
/* Mutex protocols. */
#ifndef __PTHREAD_ENUM_MUTEX_PRIO_DEFINED
#define __PTHREAD_ENUM_MUTEX_PRIO_DEFINED 1
#if ((!defined(PTHREAD_PRIO_NONE) && defined(__PTHREAD_PRIO_NONE)) ||    \
     (!defined(PTHREAD_PRIO_INHERIT) && defined(__PTHREAD_PRIO_INHERIT)) || \
     (!defined(PTHREAD_PRIO_PROTECT) && defined(__PTHREAD_PRIO_PROTECT)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_PRIO_NONE) && defined(__PTHREAD_PRIO_NONE)
	PTHREAD_PRIO_NONE    = __PTHREAD_PRIO_NONE,
#endif /* !PTHREAD_PRIO_NONE && __PTHREAD_PRIO_NONE */
#if !defined(PTHREAD_PRIO_INHERIT) && defined(__PTHREAD_PRIO_INHERIT)
	PTHREAD_PRIO_INHERIT = __PTHREAD_PRIO_INHERIT,
#endif /* !PTHREAD_PRIO_INHERIT && __PTHREAD_PRIO_INHERIT */
#if !defined(PTHREAD_PRIO_PROTECT) && defined(__PTHREAD_PRIO_PROTECT)
	PTHREAD_PRIO_PROTECT = __PTHREAD_PRIO_PROTECT,
#endif /* !PTHREAD_PRIO_PROTECT && __PTHREAD_PRIO_PROTECT */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_PRIO_NONE) && defined(__PTHREAD_PRIO_NONE)
#define PTHREAD_PRIO_NONE    PTHREAD_PRIO_NONE
#endif /* !PTHREAD_PRIO_NONE && __PTHREAD_PRIO_NONE */
#if !defined(PTHREAD_PRIO_INHERIT) && defined(__PTHREAD_PRIO_INHERIT)
#define PTHREAD_PRIO_INHERIT PTHREAD_PRIO_INHERIT
#endif /* !PTHREAD_PRIO_INHERIT && __PTHREAD_PRIO_INHERIT */
#if !defined(PTHREAD_PRIO_PROTECT) && defined(__PTHREAD_PRIO_PROTECT)
#define PTHREAD_PRIO_PROTECT PTHREAD_PRIO_PROTECT
#endif /* !PTHREAD_PRIO_PROTECT && __PTHREAD_PRIO_PROTECT */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_PRIO_NONE) && defined(__PTHREAD_PRIO_NONE)
#define PTHREAD_PRIO_NONE    __PTHREAD_PRIO_NONE
#endif /* !PTHREAD_PRIO_NONE && __PTHREAD_PRIO_NONE */
#if !defined(PTHREAD_PRIO_INHERIT) && defined(__PTHREAD_PRIO_INHERIT)
#define PTHREAD_PRIO_INHERIT __PTHREAD_PRIO_INHERIT
#endif /* !PTHREAD_PRIO_INHERIT && __PTHREAD_PRIO_INHERIT */
#if !defined(PTHREAD_PRIO_PROTECT) && defined(__PTHREAD_PRIO_PROTECT)
#define PTHREAD_PRIO_PROTECT __PTHREAD_PRIO_PROTECT
#endif /* !PTHREAD_PRIO_PROTECT && __PTHREAD_PRIO_PROTECT */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !__PTHREAD_ENUM_MUTEX_PRIO_DEFINED */
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

/* Read-write lock types. */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#if ((!defined(PTHREAD_RWLOCK_PREFER_READER) && defined(__PTHREAD_RWLOCK_PREFER_READER)) ||                           \
     (!defined(PTHREAD_RWLOCK_PREFER_WRITER) && defined(__PTHREAD_RWLOCK_PREFER_WRITER)) ||                           \
     (!defined(PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE) && defined(__PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE)) || \
     (!defined(PTHREAD_RWLOCK_PREFER_READER) && defined(__PTHREAD_RWLOCK_PREFER_READER)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_RWLOCK_PREFER_READER_NP) && defined(__PTHREAD_RWLOCK_PREFER_READER)
	PTHREAD_RWLOCK_PREFER_READER_NP              = __PTHREAD_RWLOCK_PREFER_READER,
#endif /* !PTHREAD_RWLOCK_PREFER_READER_NP && __PTHREAD_RWLOCK_PREFER_READER */
#if !defined(PTHREAD_RWLOCK_PREFER_WRITER_NP) && defined(__PTHREAD_RWLOCK_PREFER_WRITER)
	PTHREAD_RWLOCK_PREFER_WRITER_NP              = __PTHREAD_RWLOCK_PREFER_WRITER,
#endif /* !PTHREAD_RWLOCK_PREFER_WRITER_NP && __PTHREAD_RWLOCK_PREFER_WRITER */
#if !defined(PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP) && defined(__PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE)
	PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP = __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE,
#endif /* !PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP && __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE */
#if !defined(PTHREAD_RWLOCK_DEFAULT_NP) && defined(__PTHREAD_RWLOCK_PREFER_READER)
	PTHREAD_RWLOCK_DEFAULT_NP                    = __PTHREAD_RWLOCK_PREFER_READER,
#endif /* !PTHREAD_RWLOCK_DEFAULT_NP && __PTHREAD_RWLOCK_PREFER_READER */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_RWLOCK_PREFER_READER_NP) && defined(__PTHREAD_RWLOCK_PREFER_READER)
#define PTHREAD_RWLOCK_PREFER_READER_NP              PTHREAD_RWLOCK_PREFER_READER_NP
#endif /* !PTHREAD_RWLOCK_PREFER_READER_NP && __PTHREAD_RWLOCK_PREFER_READER */
#if !defined(PTHREAD_RWLOCK_PREFER_WRITER_NP) && defined(__PTHREAD_RWLOCK_PREFER_WRITER)
#define PTHREAD_RWLOCK_PREFER_WRITER_NP              PTHREAD_RWLOCK_PREFER_WRITER_NP
#endif /* !PTHREAD_RWLOCK_PREFER_WRITER_NP && __PTHREAD_RWLOCK_PREFER_WRITER */
#if !defined(PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP) && defined(__PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE)
#define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP
#endif /* !PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP && __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE */
#if !defined(PTHREAD_RWLOCK_DEFAULT_NP) && defined(__PTHREAD_RWLOCK_PREFER_READER)
#define PTHREAD_RWLOCK_DEFAULT_NP                    PTHREAD_RWLOCK_DEFAULT_NP
#endif /* !PTHREAD_RWLOCK_DEFAULT_NP && __PTHREAD_RWLOCK_PREFER_READER */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_RWLOCK_PREFER_READER_NP) && defined(__PTHREAD_RWLOCK_PREFER_READER)
#define PTHREAD_RWLOCK_PREFER_READER_NP              __PTHREAD_RWLOCK_PREFER_READER
#endif /* !PTHREAD_RWLOCK_PREFER_READER_NP && __PTHREAD_RWLOCK_PREFER_READER */
#if !defined(PTHREAD_RWLOCK_PREFER_WRITER_NP) && defined(__PTHREAD_RWLOCK_PREFER_WRITER)
#define PTHREAD_RWLOCK_PREFER_WRITER_NP              __PTHREAD_RWLOCK_PREFER_WRITER
#endif /* !PTHREAD_RWLOCK_PREFER_WRITER_NP && __PTHREAD_RWLOCK_PREFER_WRITER */
#if !defined(PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP) && defined(__PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE)
#define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE
#endif /* !PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP && __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE */
#if !defined(PTHREAD_RWLOCK_DEFAULT_NP) && defined(__PTHREAD_RWLOCK_PREFER_READER)
#define PTHREAD_RWLOCK_DEFAULT_NP                    __PTHREAD_RWLOCK_PREFER_READER
#endif /* !PTHREAD_RWLOCK_DEFAULT_NP && __PTHREAD_RWLOCK_PREFER_READER */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

/* Scheduler inheritance. */
#ifndef __PTHREAD_ENUM_SCHED_INHERIT_DEFINED
#define __PTHREAD_ENUM_SCHED_INHERIT_DEFINED 1
#if ((!defined(PTHREAD_INHERIT_SCHED) && defined(__PTHREAD_INHERIT_SCHED)) || \
     (!defined(PTHREAD_EXPLICIT_SCHED) && defined(__PTHREAD_EXPLICIT_SCHED)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_INHERIT_SCHED) && defined(__PTHREAD_INHERIT_SCHED)
	PTHREAD_INHERIT_SCHED  = __PTHREAD_INHERIT_SCHED,
#endif /* !PTHREAD_INHERIT_SCHED && __PTHREAD_INHERIT_SCHED */
#if !defined(PTHREAD_EXPLICIT_SCHED) && defined(__PTHREAD_EXPLICIT_SCHED)
	PTHREAD_EXPLICIT_SCHED = __PTHREAD_EXPLICIT_SCHED
#endif /* !PTHREAD_EXPLICIT_SCHED && __PTHREAD_EXPLICIT_SCHED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_INHERIT_SCHED) && defined(__PTHREAD_INHERIT_SCHED)
#define PTHREAD_INHERIT_SCHED  PTHREAD_INHERIT_SCHED
#endif /* !PTHREAD_INHERIT_SCHED && __PTHREAD_INHERIT_SCHED */
#if !defined(PTHREAD_EXPLICIT_SCHED) && defined(__PTHREAD_EXPLICIT_SCHED)
#define PTHREAD_EXPLICIT_SCHED PTHREAD_EXPLICIT_SCHED
#endif /* !PTHREAD_EXPLICIT_SCHED && __PTHREAD_EXPLICIT_SCHED */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_INHERIT_SCHED) && defined(__PTHREAD_INHERIT_SCHED)
#define PTHREAD_INHERIT_SCHED  __PTHREAD_INHERIT_SCHED
#endif /* !PTHREAD_INHERIT_SCHED && __PTHREAD_INHERIT_SCHED */
#if !defined(PTHREAD_EXPLICIT_SCHED) && defined(__PTHREAD_EXPLICIT_SCHED)
#define PTHREAD_EXPLICIT_SCHED __PTHREAD_EXPLICIT_SCHED
#endif /* !PTHREAD_EXPLICIT_SCHED && __PTHREAD_EXPLICIT_SCHED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !__PTHREAD_ENUM_SCHED_INHERIT_DEFINED */

/* Scope handling. */
#ifndef __PTHREAD_ENUM_SCOPE_DEFINED
#define __PTHREAD_ENUM_SCOPE_DEFINED 1
#if ((!defined(PTHREAD_SCOPE_SYSTEM) && defined(__PTHREAD_SCOPE_SYSTEM)) || \
     (!defined(PTHREAD_SCOPE_PROCESS) && defined(__PTHREAD_SCOPE_PROCESS)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_SCOPE_SYSTEM) && defined(__PTHREAD_SCOPE_SYSTEM)
	PTHREAD_SCOPE_SYSTEM  = __PTHREAD_SCOPE_SYSTEM,
#endif /* !PTHREAD_SCOPE_SYSTEM && __PTHREAD_SCOPE_SYSTEM */
#if !defined(PTHREAD_SCOPE_PROCESS) && defined(__PTHREAD_SCOPE_PROCESS)
	PTHREAD_SCOPE_PROCESS = __PTHREAD_SCOPE_PROCESS
#endif /* !PTHREAD_SCOPE_PROCESS && __PTHREAD_SCOPE_PROCESS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_SCOPE_SYSTEM) && defined(__PTHREAD_SCOPE_SYSTEM)
#define PTHREAD_SCOPE_SYSTEM  PTHREAD_SCOPE_SYSTEM
#endif /* !PTHREAD_SCOPE_SYSTEM && __PTHREAD_SCOPE_SYSTEM */
#if !defined(PTHREAD_SCOPE_PROCESS) && defined(__PTHREAD_SCOPE_PROCESS)
#define PTHREAD_SCOPE_PROCESS PTHREAD_SCOPE_PROCESS
#endif /* !PTHREAD_SCOPE_PROCESS && __PTHREAD_SCOPE_PROCESS */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_SCOPE_SYSTEM) && defined(__PTHREAD_SCOPE_SYSTEM)
#define PTHREAD_SCOPE_SYSTEM  __PTHREAD_SCOPE_SYSTEM
#endif /* !PTHREAD_SCOPE_SYSTEM && __PTHREAD_SCOPE_SYSTEM */
#if !defined(PTHREAD_SCOPE_PROCESS) && defined(__PTHREAD_SCOPE_PROCESS)
#define PTHREAD_SCOPE_PROCESS __PTHREAD_SCOPE_PROCESS
#endif /* !PTHREAD_SCOPE_PROCESS && __PTHREAD_SCOPE_PROCESS */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !__PTHREAD_ENUM_SCOPE_DEFINED */


/* Process shared or private flag. */
#ifndef __PTHREAD_ENUM_PROCESS_SHARED_DEFINED
#define __PTHREAD_ENUM_PROCESS_SHARED_DEFINED 1
#if ((!defined(PTHREAD_PROCESS_PRIVATE) && defined(__PTHREAD_PROCESS_PRIVATE)) || \
     (!defined(PTHREAD_PROCESS_SHARED) && defined(__PTHREAD_PROCESS_SHARED)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_PROCESS_PRIVATE) && defined(__PTHREAD_PROCESS_PRIVATE)
	PTHREAD_PROCESS_PRIVATE = __PTHREAD_PROCESS_PRIVATE,
#endif /* !PTHREAD_PROCESS_PRIVATE && __PTHREAD_PROCESS_PRIVATE */
#if !defined(PTHREAD_PROCESS_SHARED) && defined(__PTHREAD_PROCESS_SHARED)
	PTHREAD_PROCESS_SHARED  = __PTHREAD_PROCESS_SHARED
#endif /* !PTHREAD_PROCESS_SHARED && __PTHREAD_PROCESS_SHARED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_PROCESS_PRIVATE) && defined(__PTHREAD_PROCESS_PRIVATE)
#define PTHREAD_PROCESS_PRIVATE PTHREAD_PROCESS_PRIVATE
#endif /* !PTHREAD_PROCESS_PRIVATE && __PTHREAD_PROCESS_PRIVATE */
#if !defined(PTHREAD_PROCESS_SHARED) && defined(__PTHREAD_PROCESS_SHARED)
#define PTHREAD_PROCESS_SHARED  PTHREAD_PROCESS_SHARED
#endif /* !PTHREAD_PROCESS_SHARED && __PTHREAD_PROCESS_SHARED */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_PROCESS_PRIVATE) && defined(__PTHREAD_PROCESS_PRIVATE)
#define PTHREAD_PROCESS_PRIVATE __PTHREAD_PROCESS_PRIVATE
#endif /* !PTHREAD_PROCESS_PRIVATE && __PTHREAD_PROCESS_PRIVATE */
#if !defined(PTHREAD_PROCESS_SHARED) && defined(__PTHREAD_PROCESS_SHARED)
#define PTHREAD_PROCESS_SHARED  __PTHREAD_PROCESS_SHARED
#endif /* !PTHREAD_PROCESS_SHARED && __PTHREAD_PROCESS_SHARED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __PTHREAD_PROCESS_PRIVATE || __PTHREAD_PROCESS_SHARED */
#endif /* !__PTHREAD_ENUM_PROCESS_SHARED_DEFINED */


/* Cancellation */
#if ((!defined(PTHREAD_CANCEL_ENABLE) && defined(__PTHREAD_CANCEL_ENABLE)) ||     \
     (!defined(PTHREAD_CANCEL_DISABLE) && defined(__PTHREAD_CANCEL_DISABLE)) ||   \
     (!defined(PTHREAD_CANCEL_DEFERRED) && defined(__PTHREAD_CANCEL_DEFERRED)) || \
     (!defined(PTHREAD_CANCEL_ASYNCHRONOUS) && defined(__PTHREAD_CANCEL_ASYNCHRONOUS)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(PTHREAD_CANCEL_ENABLE) && defined(__PTHREAD_CANCEL_ENABLE)
	PTHREAD_CANCEL_ENABLE       = __PTHREAD_CANCEL_ENABLE,
#endif /* !PTHREAD_CANCEL_ENABLE && __PTHREAD_CANCEL_ENABLE */
#if !defined(PTHREAD_CANCEL_DISABLE) && defined(__PTHREAD_CANCEL_DISABLE)
	PTHREAD_CANCEL_DISABLE      = __PTHREAD_CANCEL_DISABLE,
#endif /* !PTHREAD_CANCEL_DISABLE && __PTHREAD_CANCEL_DISABLE */
#if !defined(PTHREAD_CANCEL_DEFERRED) && defined(__PTHREAD_CANCEL_DEFERRED)
	PTHREAD_CANCEL_DEFERRED     = __PTHREAD_CANCEL_DEFERRED,
#endif /* !PTHREAD_CANCEL_DEFERRED && __PTHREAD_CANCEL_DEFERRED */
#if !defined(PTHREAD_CANCEL_ASYNCHRONOUS) && defined(__PTHREAD_CANCEL_ASYNCHRONOUS)
	PTHREAD_CANCEL_ASYNCHRONOUS = __PTHREAD_CANCEL_ASYNCHRONOUS
#endif /* !PTHREAD_CANCEL_ASYNCHRONOUS && __PTHREAD_CANCEL_ASYNCHRONOUS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTHREAD_CANCEL_ENABLE) && defined(__PTHREAD_CANCEL_ENABLE)
#define PTHREAD_CANCEL_ENABLE       PTHREAD_CANCEL_ENABLE
#endif /* !PTHREAD_CANCEL_ENABLE && __PTHREAD_CANCEL_ENABLE */
#if !defined(PTHREAD_CANCEL_DISABLE) && defined(__PTHREAD_CANCEL_DISABLE)
#define PTHREAD_CANCEL_DISABLE      PTHREAD_CANCEL_DISABLE
#endif /* !PTHREAD_CANCEL_DISABLE && __PTHREAD_CANCEL_DISABLE */
#if !defined(PTHREAD_CANCEL_DEFERRED) && defined(__PTHREAD_CANCEL_DEFERRED)
#define PTHREAD_CANCEL_DEFERRED     PTHREAD_CANCEL_DEFERRED
#endif /* !PTHREAD_CANCEL_DEFERRED && __PTHREAD_CANCEL_DEFERRED */
#if !defined(PTHREAD_CANCEL_ASYNCHRONOUS) && defined(__PTHREAD_CANCEL_ASYNCHRONOUS)
#define PTHREAD_CANCEL_ASYNCHRONOUS PTHREAD_CANCEL_ASYNCHRONOUS
#endif /* !PTHREAD_CANCEL_ASYNCHRONOUS && __PTHREAD_CANCEL_ASYNCHRONOUS */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTHREAD_CANCEL_ENABLE) && defined(__PTHREAD_CANCEL_ENABLE)
#define PTHREAD_CANCEL_ENABLE       __PTHREAD_CANCEL_ENABLE
#endif /* !PTHREAD_CANCEL_ENABLE && __PTHREAD_CANCEL_ENABLE */
#if !defined(PTHREAD_CANCEL_DISABLE) && defined(__PTHREAD_CANCEL_DISABLE)
#define PTHREAD_CANCEL_DISABLE      __PTHREAD_CANCEL_DISABLE
#endif /* !PTHREAD_CANCEL_DISABLE && __PTHREAD_CANCEL_DISABLE */
#if !defined(PTHREAD_CANCEL_DEFERRED) && defined(__PTHREAD_CANCEL_DEFERRED)
#define PTHREAD_CANCEL_DEFERRED     __PTHREAD_CANCEL_DEFERRED
#endif /* !PTHREAD_CANCEL_DEFERRED && __PTHREAD_CANCEL_DEFERRED */
#if !defined(PTHREAD_CANCEL_ASYNCHRONOUS) && defined(__PTHREAD_CANCEL_ASYNCHRONOUS)
#define PTHREAD_CANCEL_ASYNCHRONOUS __PTHREAD_CANCEL_ASYNCHRONOUS
#endif /* !PTHREAD_CANCEL_ASYNCHRONOUS && __PTHREAD_CANCEL_ASYNCHRONOUS */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#if !defined(PTHREAD_CANCELED) && defined(__PTHREAD_CANCELED)
#define PTHREAD_CANCELED __PTHREAD_CANCELED
#endif /* !PTHREAD_CANCELED && __PTHREAD_CANCELED */

/* Single execution handling. */
#if !defined(PTHREAD_ONCE_INIT) && defined(__PTHREAD_ONCE_INIT)
#define PTHREAD_ONCE_INIT __PTHREAD_ONCE_INIT
#endif /* !PTHREAD_ONCE_INIT && __PTHREAD_ONCE_INIT */

#ifdef __USE_XOPEN2K
/* Special value returned by 'pthread_barrier_wait' for one of the threads
 * after  the  required  number  of  threads  have  called  this function. */
#if !defined(PTHREAD_BARRIER_SERIAL_THREAD) && defined(__PTHREAD_BARRIER_SERIAL_THREAD)
#define PTHREAD_BARRIER_SERIAL_THREAD __PTHREAD_BARRIER_SERIAL_THREAD
#endif /* !PTHREAD_BARRIER_SERIAL_THREAD && __PTHREAD_BARRIER_SERIAL_THREAD */
#endif /* __USE_XOPEN2K */



#ifdef __CC__

/* Static initializer for `pthread_mutex_t'. */
#if !defined(PTHREAD_MUTEX_INITIALIZER) && defined(__PTHREAD_MUTEX_INITIALIZER)
#define PTHREAD_MUTEX_INITIALIZER               __PTHREAD_MUTEX_INITIALIZER
#endif /* !PTHREAD_MUTEX_INITIALIZER && __PTHREAD_MUTEX_INITIALIZER */
#ifdef __USE_GNU
#if !defined(PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP) && defined(__PTHREAD_RECURSIVE_MUTEX_INITIALIZER)
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP  __PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#endif /* !PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP && __PTHREAD_RECURSIVE_MUTEX_INITIALIZER */
#if !defined(PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP) && defined(__PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER
#endif /* !PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP && __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER */
#if !defined(PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP) && defined(__PTHREAD_ADAPTIVE_MUTEX_INITIALIZER)
#define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP   __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER
#endif /* !PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP && __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER */
#endif /* __USE_GNU */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)

/* Static initializer for `pthread_rwlock_t'. */
#if !defined(PTHREAD_RWLOCK_INITIALIZER) && defined(__PTHREAD_RWLOCK_INITIALIZER)
#define PTHREAD_RWLOCK_INITIALIZER __PTHREAD_RWLOCK_INITIALIZER
#endif /* !PTHREAD_RWLOCK_INITIALIZER && __PTHREAD_RWLOCK_INITIALIZER */
#ifdef __USE_GNU
#if !defined(PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP) && defined(__PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER)
#define PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER
#endif /* !PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP && __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER */
#endif /* __USE_GNU */
#endif  /* __USE_UNIX98 || __USE_XOPEN2K */

/* Static initializer for `pthread_cond_t'. */
#if !defined(PTHREAD_COND_INITIALIZER) && defined(__PTHREAD_COND_INITIALIZER)
#define PTHREAD_COND_INITIALIZER __PTHREAD_COND_INITIALIZER
#endif /* !PTHREAD_COND_INITIALIZER && __PTHREAD_COND_INITIALIZER */

/* Cleanup callback buffers */
struct _pthread_cleanup_buffer {
	void                          (*__routine)(void *); /* Function to call. */
	void                           *__arg;              /* Its argument. */
	int                             __canceltype;       /* Saved cancellation type. */
	struct _pthread_cleanup_buffer *__prev;             /* Chaining of cleanup functions. */
};

#ifndef __pthread_t_defined
#define __pthread_t_defined
typedef __pthread_t pthread_t;
#endif /* !__pthread_t_defined */
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined
typedef __pthread_attr_t pthread_attr_t;
#endif /* !__pthread_attr_t_defined */
#ifndef __pthread_mutex_t_defined
#define __pthread_mutex_t_defined
typedef __pthread_mutex_t pthread_mutex_t;
#endif /* !__pthread_mutex_t_defined */
#ifndef __pthread_mutexattr_t_defined
#define __pthread_mutexattr_t_defined
typedef __pthread_mutexattr_t pthread_mutexattr_t;
#endif /* !__pthread_mutexattr_t_defined */
#ifndef __pthread_cond_t_defined
#define __pthread_cond_t_defined
typedef __pthread_cond_t pthread_cond_t;
#endif /* !__pthread_cond_t_defined */
#ifndef __pthread_condattr_t_defined
#define __pthread_condattr_t_defined
typedef __pthread_condattr_t pthread_condattr_t;
#endif /* !__pthread_condattr_t_defined */
#ifndef __pthread_key_t_defined
#define __pthread_key_t_defined
typedef __pthread_key_t pthread_key_t;
#endif /* !__pthread_key_t_defined */
#ifndef __pthread_once_t_defined
#define __pthread_once_t_defined
typedef __pthread_once_t pthread_once_t;
#endif /* !__pthread_once_t_defined */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifndef __pthread_rwlock_t_defined
#define __pthread_rwlock_t_defined
typedef __pthread_rwlock_t pthread_rwlock_t;
#endif /* !__pthread_rwlock_t_defined */
#ifndef __pthread_rwlockattr_t_defined
#define __pthread_rwlockattr_t_defined
typedef __pthread_rwlockattr_t pthread_rwlockattr_t;
#endif /* !__pthread_rwlockattr_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_XOPEN2K
#ifndef __pthread_spinlock_t_defined
#define __pthread_spinlock_t_defined
typedef __pthread_spinlock_t pthread_spinlock_t;
#endif /* !__pthread_spinlock_t_defined */
#ifndef __pthread_barrier_t_defined
#define __pthread_barrier_t_defined
typedef __pthread_barrier_t pthread_barrier_t;
#endif /* !__pthread_barrier_t_defined */
#ifndef __pthread_barrierattr_t_defined
#define __pthread_barrierattr_t_defined
typedef __pthread_barrierattr_t pthread_barrierattr_t;
#endif /* !__pthread_barrierattr_t_defined */
#endif /* __USE_XOPEN2K */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

/* >> pthread_create(3)
 * Create a  new thread,  starting with  execution of  `start_routine'
 * getting passed `arg'. Creation attributed come from `attr'. The new
 * handle is stored in `*p_newthread'
 * @return: EOK:    Success
 * @return: EAGAIN: Insufficient resources, or operation-not-permitted
 *                  (read: `ENOMEM', but posix didn't want to use that
 *                  errno for whatever reason...) */
__CDECLARE_OPT(__ATTR_IN_OPT(2) __ATTR_OUT(1) __ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,pthread_create,(pthread_t *__restrict __p_newthread, pthread_attr_t const *__restrict __attr, void *(__LIBCCALL *__start_routine)(void *__arg), void *__arg),(__p_newthread,__attr,__start_routine,__arg))
#ifdef __CRT_HAVE_pthread_exit
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),,pthread_exit,(void *__retval),(__retval))
#elif defined(__CRT_HAVE_thr_exit)
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),,pthread_exit,(void *__retval),thr_exit,(__retval))
#elif defined(__CRT_HAVE_cthread_exit)
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),,pthread_exit,(void *__retval),cthread_exit,(__retval))
#endif /* ... */
/* >> pthread_join(3)
 * Make calling thread wait for termination of the thread  `self'.
 * The exit status of the thread is stored in `*thread_return', if
 * `thread_return' is not `NULL'.
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_join,(pthread_t __self, void **__thread_return),(__self,__thread_return))
#ifdef __USE_KOS
/* >> pthread_getresult_np(3)
 * Same as `pthread_join(3)', but don't destroy `self' at the end.
 * Instead, the caller must destroy `self' themselves via  another
 * call to `pthread_detach(3)'.
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_getresult_np,(pthread_t __self, void **__thread_return),(__self,__thread_return))
#endif /* __USE_KOS */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_tryjoin_np
/* >> pthread_tryjoin_np(3)
 * Check whether thread  `self' has terminated.  If so return  the
 * status of the thread in `*thread_return', if `thread_return' is
 * not `NULL'.
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
__CDECLARE(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_tryjoin_np,(pthread_t __self, void **__thread_return),(__self,__thread_return))
#elif defined(__CRT_HAVE_pthread_peekjoin_np)
/* >> pthread_tryjoin_np(3)
 * Check whether thread  `self' has terminated.  If so return  the
 * status of the thread in `*thread_return', if `thread_return' is
 * not `NULL'.
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
__CREDIRECT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_tryjoin_np,(pthread_t __self, void **__thread_return),pthread_peekjoin_np,(__self,__thread_return))
#endif /* ... */
struct timespec;
#ifndef __pthread_timedjoin_np_defined
#define __pthread_timedjoin_np_defined
#if defined(__CRT_HAVE_pthread_timedjoin_np) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __self, void **__thread_return, struct timespec const *__abstime),(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin64_np) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __self, void **__thread_return, struct timespec const *__abstime),pthread_timedjoin64_np,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE___pthread_timedjoin_np64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __self, void **__thread_return, struct timespec const *__abstime),__pthread_timedjoin_np64,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin64_np) || defined(__CRT_HAVE___pthread_timedjoin_np64) || defined(__CRT_HAVE_pthread_timedjoin_np)
#include <libc/local/pthread/pthread_timedjoin_np.h>
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_OUT_OPT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_timedjoin_np)(pthread_t __self, void **__thread_return, struct timespec const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin_np))(__self, __thread_return, __abstime); })
#else /* ... */
#undef __pthread_timedjoin_np_defined
#endif /* !... */
#endif /* !__pthread_timedjoin_np_defined */
#ifdef __USE_TIME64
#ifndef __pthread_timedjoin64_np_defined
#define __pthread_timedjoin64_np_defined
#if defined(__CRT_HAVE_pthread_timedjoin_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime),pthread_timedjoin_np,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin64_np)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime),(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE___pthread_timedjoin_np64)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime),__pthread_timedjoin_np64,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np)
#include <libc/local/pthread/pthread_timedjoin64_np.h>
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin64_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_OUT_OPT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_timedjoin64_np)(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin64_np))(__self, __thread_return, __abstime); })
#else /* ... */
#undef __pthread_timedjoin64_np_defined
#endif /* !... */
#endif /* !__pthread_timedjoin64_np_defined */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE_pthread_detach
/* >> pthread_detach(3)
 * Indicate that the thread `self' is  never to be joined with  `pthread_join(3)'.
 * The resources of `self' will therefore be freed immediately when it terminates,
 * instead of waiting for another thread to perform `pthread_join(3)' on it
 * @return: EOK: Success */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_detach,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_cthread_detach)
/* >> pthread_detach(3)
 * Indicate that the thread `self' is  never to be joined with  `pthread_join(3)'.
 * The resources of `self' will therefore be freed immediately when it terminates,
 * instead of waiting for another thread to perform `pthread_join(3)' on it
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_detach,(pthread_t __self),cthread_detach,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_self
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,pthread_t,__NOTHROW,pthread_self,(void),())
#elif defined(__CRT_HAVE_thrd_current)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,pthread_t,__NOTHROW,pthread_self,(void),thrd_current,())
#elif defined(__CRT_HAVE_thr_self)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,pthread_t,__NOTHROW,pthread_self,(void),thr_self,())
#elif defined(__CRT_HAVE_cthread_self)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,pthread_t,__NOTHROW,pthread_self,(void),cthread_self,())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_equal
/* >> pthread_equal(3)
 * Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,pthread_equal,(pthread_t __thr1, pthread_t __thr2),{ return __thr1 == __thr2; })
#elif defined(__CRT_HAVE_thrd_equal)
/* >> pthread_equal(3)
 * Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,pthread_equal,(pthread_t __thr1, pthread_t __thr2),thrd_equal,{ return __thr1 == __thr2; })
#else /* ... */
/* >> pthread_equal(3)
 * Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL pthread_equal)(pthread_t __thr1, pthread_t __thr2) { return __thr1 == __thr2; }
#endif /* !... */

/* Thread attribute handling. */

#ifdef __CRT_HAVE_pthread_attr_init
/* >> pthread_attr_init(3)
 * Initialize thread  attribute `*self'  with default  attributes (detachstate  is
 * `PTHREAD_JOINABLE', scheduling policy is `SCHED_OTHER', no user-provided stack)
 * @return: EOK: Success */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_init,(pthread_attr_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_attr_init)
/* >> pthread_attr_init(3)
 * Initialize thread  attribute `*self'  with default  attributes (detachstate  is
 * `PTHREAD_JOINABLE', scheduling policy is `SCHED_OTHER', no user-provided stack)
 * @return: EOK: Success */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_init,(pthread_attr_t *__self),__pthread_attr_init,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_attr_destroy
/* >> pthread_attr_destroy(3)
 * Destroy thread attribute `*self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_destroy,(pthread_attr_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_attr_destroy)
/* >> pthread_attr_destroy(3)
 * Destroy thread attribute `*self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_destroy,(pthread_attr_t *__self),__pthread_attr_destroy,(__self))
#endif /* ... */
/* >> pthread_attr_getdetachstate(3)
 * Get   detach   state    attribute
 * @param: *detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getdetachstate,(pthread_attr_t const *__restrict __self, int *__restrict __detachstate),(__self,__detachstate))
/* >> pthread_attr_setdetachstate(3)
 * Set   detach   state    attribute
 * @param: detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `detachstate' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setdetachstate,(pthread_attr_t *__self, int __detachstate),(__self,__detachstate))
/* >> pthread_attr_getguardsize(3)
 * Get the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getguardsize,(pthread_attr_t const *__restrict __self, size_t *__restrict __guardsize),(__self,__guardsize))
/* >> pthread_attr_setguardsize(3)
 * Set the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setguardsize,(pthread_attr_t *__self, size_t __guardsize),(__self,__guardsize))
/* >> pthread_attr_getschedparam(3)
 * Return in `*param' the scheduling parameters of `*self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getschedparam,(pthread_attr_t const *__restrict __self, struct sched_param *__restrict __param),(__self,__param))
/* >> pthread_attr_setschedparam(3)
 * Set scheduling parameters (priority, etc) in `*self' according to `param'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `param' */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setschedparam,(pthread_attr_t *__restrict __self, struct sched_param const *__restrict __param),(__self,__param))
/* >> pthread_attr_getschedpolicy(3)
 * Return in `*policy' the scheduling policy of `*self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getschedpolicy,(pthread_attr_t const *__restrict __self, int *__restrict __policy),(__self,__policy))
/* >> pthread_attr_setschedpolicy(3)
 * Set scheduling policy in `*self' according to `policy'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `policy' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setschedpolicy,(pthread_attr_t *__self, int __policy),(__self,__policy))
/* >> pthread_attr_getinheritsched(3)
 * Return in `*inherit' the scheduling inheritance mode of `*self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getinheritsched,(pthread_attr_t const *__restrict __self, int *__restrict __inherit),(__self,__inherit))
/* >> pthread_attr_setinheritsched(3)
 * Set scheduling inheritance mode in `*self' according to `inherit'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `inherit' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setinheritsched,(pthread_attr_t *__self, int __inherit),(__self,__inherit))
/* >> pthread_attr_getscope(3)
 * Return in `*scope' the scheduling contention scope of `*self'
 * @param:  scope: Filled with one of `PTHREAD_SCOPE_*'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getscope,(pthread_attr_t const *__restrict __self, int *__restrict __scope),(__self,__scope))
/* >> pthread_attr_setscope(3)
 * Set scheduling contention scope in `*self' according to `scope'
 * @param:  scope:  One of `PTHREAD_SCOPE_*'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `scope' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setscope,(pthread_attr_t *__self, int __scope),(__self,__scope))
#ifdef __CRT_HAVE_pthread_attr_getstackaddr
/* >> pthread_attr_getstackaddr(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
__CDECLARE(__ATTR_DEPRECATED("Use pthread_attr_getstack()") __ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getstackaddr,(pthread_attr_t const *__restrict __self, void **__restrict __stackaddr),(__self,__stackaddr))
#elif defined(__CRT_HAVE_pthread_attr_getstack)
#include <libc/local/pthread/pthread_attr_getstackaddr.h>
/* >> pthread_attr_getstackaddr(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_getstackaddr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Use pthread_attr_getstack()") __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_getstackaddr)(pthread_attr_t const *__restrict __self, void **__restrict __stackaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_getstackaddr))(__self, __stackaddr); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_attr_setstackaddr
/* >> pthread_attr_setstackaddr(3)
 * Set the starting address  of the stack of  the thread to be  created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or  lower than  all the address  in the  memory block.  The
 * minimal size of the block must be `PTHREAD_STACK_MIN'
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
__CDECLARE(__ATTR_DEPRECATED("Use pthread_attr_setstack()") __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setstackaddr,(pthread_attr_t *__self, void *__stackaddr),(__self,__stackaddr))
#elif (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize))) && defined(__CRT_HAVE_pthread_attr_setstack)
#include <libc/local/pthread/pthread_attr_setstackaddr.h>
/* >> pthread_attr_setstackaddr(3)
 * Set the starting address  of the stack of  the thread to be  created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or  lower than  all the address  in the  memory block.  The
 * minimal size of the block must be `PTHREAD_STACK_MIN'
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_setstackaddr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Use pthread_attr_setstack()") __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_setstackaddr)(pthread_attr_t *__self, void *__stackaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_setstackaddr))(__self, __stackaddr); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_attr_getstacksize
/* >> pthread_attr_getstacksize(3)
 * Return the currently used minimal stack size
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getstacksize,(pthread_attr_t const *__restrict __self, size_t *__restrict __stacksize),(__self,__stacksize))
#elif defined(__CRT_HAVE_pthread_attr_getstack)
#include <libc/local/pthread/pthread_attr_getstacksize.h>
/* >> pthread_attr_getstacksize(3)
 * Return the currently used minimal stack size
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_getstacksize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_getstacksize)(pthread_attr_t const *__restrict __self, size_t *__restrict __stacksize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_getstacksize))(__self, __stacksize); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_attr_setstacksize
/* >> pthread_attr_setstacksize(3)
 * Add information about the minimum  stack size needed for the  thread
 * to be started. This size must never be less than `PTHREAD_STACK_MIN'
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setstacksize,(pthread_attr_t *__self, size_t __stacksize),(__self,__stacksize))
#elif (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize))) && defined(__CRT_HAVE_pthread_attr_setstack)
#include <libc/local/pthread/pthread_attr_setstacksize.h>
/* >> pthread_attr_setstacksize(3)
 * Add information about the minimum  stack size needed for the  thread
 * to be started. This size must never be less than `PTHREAD_STACK_MIN'
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_setstacksize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_setstacksize)(pthread_attr_t *__self, size_t __stacksize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_setstacksize))(__self, __stacksize); })
#endif /* ... */
#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pthread_attr_getstack
/* >> pthread_attr_getstack(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3),__errno_t,__NOTHROW_NCX,pthread_attr_getstack,(pthread_attr_t const *__restrict __self, void **__restrict __stackaddr, size_t *__restrict __stacksize),(__self,__stackaddr,__stacksize))
#elif defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize)
#include <libc/local/pthread/pthread_attr_getstack.h>
/* >> pthread_attr_getstack(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_getstack, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_getstack)(pthread_attr_t const *__restrict __self, void **__restrict __stackaddr, size_t *__restrict __stacksize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_getstack))(__self, __stackaddr, __stacksize); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_attr_setstack
/* >> pthread_attr_setstack(3)
 * The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting  the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setstack,(pthread_attr_t *__self, void *__stackaddr, size_t __stacksize),(__self,__stackaddr,__stacksize))
#elif defined(__CRT_HAVE_pthread_attr_setstackaddr) && defined(__CRT_HAVE_pthread_attr_setstacksize)
#include <libc/local/pthread/pthread_attr_setstack.h>
/* >> pthread_attr_setstack(3)
 * The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting  the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_setstack, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_setstack)(pthread_attr_t *__self, void *__stackaddr, size_t __stacksize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_setstack))(__self, __stackaddr, __stacksize); })
#endif /* ... */
#endif /* __USE_XOPEN2K */
#ifdef __USE_GNU
#ifndef __cpu_set_t_defined
#define __cpu_set_t_defined
typedef struct __cpu_set_struct cpu_set_t;
#endif /* !__cpu_set_t_defined */
#ifndef __pthread_attr_setaffinity_np_defined
#define __pthread_attr_setaffinity_np_defined
#ifdef __CRT_HAVE_pthread_attr_setaffinity_np
/* >> pthread_attr_setaffinity_np(3)
 * Set cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existent CPU
 * @return: ENOMEM: Insufficient memory */
__CDECLARE(__ATTR_INOUT(1) __ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,pthread_attr_setaffinity_np,(pthread_attr_t *__self, size_t __cpusetsize, cpu_set_t const *__cpuset),(__self,__cpusetsize,__cpuset))
#elif defined(__CRT_HAVE___pthread_attr_setaffinity_np)
/* >> pthread_attr_setaffinity_np(3)
 * Set cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existent CPU
 * @return: ENOMEM: Insufficient memory */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,pthread_attr_setaffinity_np,(pthread_attr_t *__self, size_t __cpusetsize, cpu_set_t const *__cpuset),__pthread_attr_setaffinity_np,(__self,__cpusetsize,__cpuset))
#else /* ... */
#undef __pthread_attr_setaffinity_np_defined
#endif /* !... */
#endif /* !__pthread_attr_setaffinity_np_defined */
#if !defined(__pthread_attr_getaffinity_np_defined) && defined(__CRT_HAVE_pthread_attr_getaffinity_np)
#define __pthread_attr_getaffinity_np_defined
/* >> pthread_attr_getaffinity_np(3)
 * Get cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,pthread_attr_getaffinity_np,(pthread_attr_t const *__self, size_t __cpusetsize, cpu_set_t *__cpuset),(__self,__cpusetsize,__cpuset))
#endif /* !__pthread_attr_getaffinity_np_defined && __CRT_HAVE_pthread_attr_getaffinity_np */
/* >> pthread_getattr_default_np(3)
 * Get the default attributes used by `pthread_create(3)' when given `NULL' for its `attr' argument.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CDECLARE_OPT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_getattr_default_np,(pthread_attr_t *__attr),(__attr))
/* >> pthread_setattr_default_np(3)
 * Set the default attributes to be used by `pthread_create(3)' when given `NULL' for its `attr' argument.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CDECLARE_OPT(__ATTR_IN(1),__errno_t,__NOTHROW_NCX,pthread_setattr_default_np,(pthread_attr_t const *__attr),(__attr))
#ifdef __CRT_HAVE_pthread_getattr_np
/* >> pthread_getattr_np(3)
 * Initialize thread attribute `*attr' with attributes corresponding to  the
 * already running thread `self'. It shall be called on uninitialized `attr'
 * and destroyed with `pthread_attr_destroy(3)' when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CDECLARE(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_getattr_np,(pthread_t __self, pthread_attr_t *__attr),(__self,__attr))
#elif defined(__CRT_HAVE_pthread_attr_get_np)
/* >> pthread_getattr_np(3)
 * Initialize thread attribute `*attr' with attributes corresponding to  the
 * already running thread `self'. It shall be called on uninitialized `attr'
 * and destroyed with `pthread_attr_destroy(3)' when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CREDIRECT(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_getattr_np,(pthread_t __self, pthread_attr_t *__attr),pthread_attr_get_np,(__self,__attr))
#endif /* ... */
#endif /* __USE_GNU */

/* Functions for scheduling control. */

/* >> pthread_setschedparam(3)
 * Set the scheduling parameters for `self' according to `policy' and `*param'
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `policy' and `param'
 * @return: ESRCH:  `self' has already exited
 * @return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy' */
__CDECLARE_OPT(__ATTR_IN(3),__errno_t,__NOTHROW_NCX,pthread_setschedparam,(pthread_t __self, int __policy, struct sched_param const *__param),(__self,__policy,__param))
/* >> pthread_getschedparam(3)
 * Return in `*policy' and `*param' the scheduling parameters for `self'
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
__CDECLARE_OPT(__ATTR_OUT(2) __ATTR_OUT(3),__errno_t,__NOTHROW_NCX,pthread_getschedparam,(pthread_t __self, int *__restrict __policy, struct sched_param *__restrict __param),(__self,__policy,__param))
/* >> pthread_setschedprio(3)
 * Set the scheduling priority for `self'
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `prio'
 * @return: ESRCH:  `self' has already exited
 * @return: EINVAL: Invalid/unsupported `prio' */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_setschedprio,(pthread_t __self, int __prio),(__self,__prio))
#ifdef __USE_GNU
#ifndef __pthread_getname_np_defined
#define __pthread_getname_np_defined
#ifdef __CRT_HAVE_pthread_getname_np
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CDECLARE(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_getname_np,(pthread_t __self, char *__buf, size_t __buflen),(__self,__buf,__buflen))
#elif defined(__CRT_HAVE_pthread_get_name_np)
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_getname_np,(pthread_t __self, char *__buf, size_t __buflen),pthread_get_name_np,(__self,__buf,__buflen))
#else /* ... */
#undef __pthread_getname_np_defined
#endif /* !... */
#endif /* !__pthread_getname_np_defined */
#ifndef __pthread_setname_np_defined
#define __pthread_setname_np_defined
#ifdef __CRT_HAVE_pthread_setname_np
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CDECLARE(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_setname_np,(pthread_t __self, const char *__name),(__self,__name))
#elif defined(__CRT_HAVE_pthread_set_name_np)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_setname_np,(pthread_t __self, const char *__name),pthread_set_name_np,(__self,__name))
#elif defined(__CRT_HAVE_cthread_set_name)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_setname_np,(pthread_t __self, const char *__name),cthread_set_name,(__self,__name))
#else /* ... */
#undef __pthread_setname_np_defined
#endif /* !... */
#endif /* !__pthread_setname_np_defined */
#endif /* __USE_GNU */
#ifdef __USE_KOS
#ifndef __pthread_gettid_np_defined
#define __pthread_gettid_np_defined
#ifdef __CRT_HAVE_pthread_gettid_np
/* >> pthread_gettid_np(3)
 * Return the TID of the given `self'.
 * If `self' has already terminated, 0 is returned
 * @return: * : The TID of the given thread
 * @return: 0 : The given `self' has already terminated */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,pthread_gettid_np,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_pthread_getunique_np)
#include <libc/local/pthread/pthread_gettid_np.h>
/* >> pthread_gettid_np(3)
 * Return the TID of the given `self'.
 * If `self' has already terminated, 0 is returned
 * @return: * : The TID of the given thread
 * @return: 0 : The given `self' has already terminated */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_gettid_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __pid_t __NOTHROW_NCX(__LIBCCALL pthread_gettid_np)(pthread_t __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_gettid_np))(__self); })
#else /* ... */
#undef __pthread_gettid_np_defined
#endif /* !... */
#endif /* !__pthread_gettid_np_defined */
#if !defined(__pthread_getpidfd_np_defined) && defined(__CRT_HAVE_pthread_getpidfd_np)
#define __pthread_getpidfd_np_defined
/* >> pthread_getpidfd_np(3)
 * Return a PIDfd for `self'. If not already allocated, allocate a PIDfd  lazily.
 * To  guaranty that a PIDfd is available for a given thread, you can make use of
 * `pthread_attr_setpidfdallocated_np()' to have `pthread_create(3)' allocate the
 * PIDfd for you.
 * @return: EOK:    Success: the PIDfd of the given thread was stored in `*p_pidfd'
 * @return: ESRCH:  The given `self' has already terminated (only when not already allocated)
 * @return: EMFILE: Too many open files (process) (only when not already allocated)
 * @return: ENFILE: Too many open files (system) (only when not already allocated)
 * @return: ENOMEM: Insufficient memory (only when not already allocated) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_getpidfd_np,(pthread_t __self, __fd_t *__restrict __p_pidfd),(__self,__p_pidfd))
#endif /* !__pthread_getpidfd_np_defined && __CRT_HAVE_pthread_getpidfd_np */
/* >> pthread_attr_setpidfdallocated_np(3)
 * Specify if `pthread_create(3)' should allocate a PIDfd for new  threads.
 * Said PIDfd can be retrieved (or lazily allocated when not pre-allocated)
 * via `pthread_getpidfd_np(3)'
 * @param: allocated: 0=no (default) or 1=yes
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `allocated' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setpidfdallocated_np,(pthread_attr_t *__self, int __allocated),(__self,__allocated))
/* >> pthread_attr_getpidfdallocated_np(3)
 * Write 0=no or  1=yes to `*allocated',  indicative of  `pthread_create(3)'
 * automatically allocating a PIDfd descriptor for the newly spawned thread.
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getpidfdallocated_np,(pthread_attr_t const *__restrict __self, int *__restrict __allocated),(__self,__allocated))
/* >> pthread_mainthread_np(3)
 * Obtain the identifier of the main thread
 * @return: * : Handle for the main thread */
__CDECLARE_OPT(__ATTR_CONST __ATTR_WUNUSED,pthread_t,__NOTHROW,pthread_mainthread_np,(void),())
struct rpc_context;
/* >> pthread_rpc_exec(3)
 * Schedule an RPC for `self' to-be  executed the next time it  makes
 * a call to a cancellation-point system call (or interrupt an active
 * system call, should one currently be in progress).
 *   - RPCs are also executed by `pthread_testcancel(3)'
 *   - The `struct rpc_context' structure is defined in `<kos/rpc.h>'
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient system memory
 * @return: ESRCH:  The given thread `self' has already terminated */
__CDECLARE_OPT(__ATTR_WUNUSED,__errno_t,__NOTHROW_RPC,pthread_rpc_exec,(pthread_t __self, void (__LIBKCALL *__func)(struct rpc_context *__restrict __ctx, void *__cookie), void *__cookie),(__self,__func,__cookie))
#endif /* __USE_KOS */
#ifdef __USE_UNIX98
#ifdef __CRT_HAVE_pthread_getconcurrency
/* >> pthread_getconcurrency(3)
 * Determine level of concurrency
 * @return: * : The current concurrency level */
__CDECLARE(__ATTR_PURE,int,__NOTHROW_NCX,pthread_getconcurrency,(void),())
#elif defined(__CRT_HAVE_thr_getconcurrency)
/* >> pthread_getconcurrency(3)
 * Determine level of concurrency
 * @return: * : The current concurrency level */
__CREDIRECT(__ATTR_PURE,int,__NOTHROW_NCX,pthread_getconcurrency,(void),thr_getconcurrency,())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_setconcurrency
/* >> pthread_setconcurrency(3)
 * Set new concurrency level to `level'
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_setconcurrency,(int __level),(__level))
#elif defined(__CRT_HAVE_thr_setconcurrency)
/* >> pthread_setconcurrency(3)
 * Set new concurrency level to `level'
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_setconcurrency,(int __level),thr_setconcurrency,(__level))
#endif /* ... */
#endif /* __USE_UNIX98 */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sched_yield
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),sched_yield,())
#elif defined(__CRT_HAVE_thrd_yield)
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),thrd_yield,())
#elif defined(__CRT_HAVE_pthread_yield)
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),())
#elif defined(__CRT_HAVE___sched_yield)
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE___libc_sched_yield)
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),__libc_sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),yield,())
#elif defined(__CRT_HAVE_thr_yield)
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),thr_yield,())
#elif defined(__CRT_HAVE_cthread_yield)
/* >> pthread_yield(3), thrd_yield(3), sched_yield(2), cthread_yield(3)
 * Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might  be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),cthread_yield,())
#endif /* ... */
#if !defined(__pthread_setaffinity_np_defined) && defined(__CRT_HAVE_pthread_setaffinity_np)
#define __pthread_setaffinity_np_defined
/* >> pthread_setaffinity_np(3)
 * Limit specified thread `self' to run only on the processors represented in `cpuset'
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
__CDECLARE(__ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,pthread_setaffinity_np,(pthread_t __self, size_t __cpusetsize, cpu_set_t const *__cpuset),(__self,__cpusetsize,__cpuset))
#endif /* !__pthread_setaffinity_np_defined && __CRT_HAVE_pthread_setaffinity_np */
#if !defined(__pthread_getaffinity_np_defined) && defined(__CRT_HAVE_pthread_getaffinity_np)
#define __pthread_getaffinity_np_defined
/* >> pthread_getaffinity_np(3)
 * Get bit set in `cpuset' representing the processors `self' can run on
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
__CDECLARE(__ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,pthread_getaffinity_np,(pthread_t __self, size_t __cpusetsize, cpu_set_t *__cpuset),(__self,__cpusetsize,__cpuset))
#endif /* !__pthread_getaffinity_np_defined && __CRT_HAVE_pthread_getaffinity_np */
#endif /* __USE_GNU */

/* Functions for handling initialization. */

#ifdef __CRT_HAVE_pthread_once
/* >> pthread_once(3)
 * Guarantee that the initialization function `init_routine' will be called
 * only  once,  even if  pthread_once is  executed  several times  with the
 * same `once_control' argument. `once_control' must  point to a static  or
 * extern variable initialized to `PTHREAD_ONCE_INIT'.
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1) __ATTR_NONNULL((2)),__errno_t,__NOTHROW_CB,pthread_once,(pthread_once_t *__once_control, void (__LIBCCALL *__init_routine)(void)),(__once_control,__init_routine))
#elif defined(__CRT_HAVE_call_once)
/* >> pthread_once(3)
 * Guarantee that the initialization function `init_routine' will be called
 * only  once,  even if  pthread_once is  executed  several times  with the
 * same `once_control' argument. `once_control' must  point to a static  or
 * extern variable initialized to `PTHREAD_ONCE_INIT'.
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),__errno_t,__NOTHROW_CB,pthread_once,(pthread_once_t *__once_control, void (__LIBCCALL *__init_routine)(void)),call_once,(__once_control,__init_routine))
#elif defined(__CRT_HAVE___pthread_once)
/* >> pthread_once(3)
 * Guarantee that the initialization function `init_routine' will be called
 * only  once,  even if  pthread_once is  executed  several times  with the
 * same `once_control' argument. `once_control' must  point to a static  or
 * extern variable initialized to `PTHREAD_ONCE_INIT'.
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),__errno_t,__NOTHROW_CB,pthread_once,(pthread_once_t *__once_control, void (__LIBCCALL *__init_routine)(void)),__pthread_once,(__once_control,__init_routine))
#else /* ... */
#include <libc/local/pthread/pthread_once.h>
/* >> pthread_once(3)
 * Guarantee that the initialization function `init_routine' will be called
 * only  once,  even if  pthread_once is  executed  several times  with the
 * same `once_control' argument. `once_control' must  point to a static  or
 * extern variable initialized to `PTHREAD_ONCE_INIT'.
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_once, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) __errno_t __NOTHROW_CB(__LIBCCALL pthread_once)(pthread_once_t *__once_control, void (__LIBCCALL *__init_routine)(void)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_once))(__once_control, __init_routine); })
#endif /* !... */

/* Functions for handling cancellation.
 * Note that these functions are explicitly not marked to not throw an
 * exception in C++ code. If cancellation is implemented by unwinding
 * this is necessary to have the compiler generate the unwind information. */
/* >> pthread_setcancelstate(3)
 * Set  cancelability  state   of  current   thread  to   `state',
 * returning old state in `*oldstate' if `oldstate' is not `NULL'.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `state' */
__CDECLARE_OPT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_setcancelstate,(int __state, int *__oldstate),(__state,__oldstate))
#if !defined(__pthread_setcanceltype_defined) && defined(__CRT_HAVE_pthread_setcanceltype)
#define __pthread_setcanceltype_defined
/* >> pthread_setcanceltype(3)
 * Set cancellation state of current thread to `type',
 * returning the old type in `*oldtype' if `oldtype' is not `NULL'.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `type' */
__CDECLARE(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_setcanceltype,(int __type, int *__oldtype),(__type,__oldtype))
#endif /* !__pthread_setcanceltype_defined && __CRT_HAVE_pthread_setcanceltype */
/* >> pthread_cancel(3)
 * Cancel `self' immediately or at the next possibility
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_cancel,(pthread_t __self),(__self))
/* >> pthread_testcancel(3)
 * Test for pending cancellation for the current thread and terminate the
 * thread as per `pthread_exit(PTHREAD_CANCELED)' if it has been canceled */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,pthread_testcancel,(void),())

/* Cancellation handling with integration into exception handling. */
typedef struct __ATTR_ALIGNED(__ALIGNOF_MAX_ALIGN_T__) {
	struct {
		struct __jmp_buf __cancel_jmp_buf;
		int              __mask_was_saved;
	}                    __cancel_jmp_buf[1];
	void                *__pad[4];
} __pthread_unwind_buf_t;

/* No special attributes by default. */
#ifndef __cleanup_fct_attribute
#define __cleanup_fct_attribute /* nothing */
#endif /* !__cleanup_fct_attribute */

/* Structure to hold the cleanup handler information. */
struct __pthread_cleanup_frame {
	void (__LIBKCALL *__cancel_routine)(void *);
	void             *__cancel_arg;
	int               __do_it;
	int               __cancel_type;
};
#if defined(__GNUC__) && defined(__EXCEPTIONS)
#if defined(__cplusplus) && !defined(__CHECKER__)
/* Class to handle cancellation handler invocation. */
class __pthread_cleanup_class {
	void (__LIBKCALL *__cancel_routine)(void *);
	void             *__cancel_arg;
	int               __do_it;
	int               __cancel_type;
public:
	__CXX_CLASSMEMBER __pthread_cleanup_class (void (__LIBKCALL *__fct)(void *), void *__arg)
		: __cancel_routine(__fct), __cancel_arg(__arg), __do_it(1)
	{ }
	__CXX_CLASSMEMBER ~__pthread_cleanup_class() {
		if (__do_it)
			(*__cancel_routine)(__cancel_arg);
	}
	__CXX_CLASSMEMBER void __setdoit(int __newval) {
		__do_it = __newval;
	}
#ifdef __pthread_setcanceltype_defined
	__CXX_CLASSMEMBER void __defer() { pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &__cancel_type); }
	__CXX_CLASSMEMBER void __restore() const { pthread_setcanceltype(__cancel_type, 0); }
#endif /* __pthread_setcanceltype_defined */
};

/* Install a cleanup handler: `routine' will be called with arguments `arg'
 * when the thread is canceled  or calls pthread_exit. `routine' will  also
 * be called  with arguments  `arg' when  the matching  pthread_cleanup_pop
 * is executed with non-zero `execute' argument.
 * `pthread_cleanup_push(3)' and `pthread_cleanup_pop(3)' are macros and must
 * always be used  in matching  pairs at the  same nesting  level of  braces. */
#define pthread_cleanup_push(routine, arg) \
	do {                                   \
		__pthread_cleanup_class __clframe(routine, arg)

/* Remove a cleanup handler installed by the matching `pthread_cleanup_push(3)'.
 * If `execute' is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)  \
		__clframe.__setdoit(execute); \
	}	__WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as `pthread_cleanup_push(3)' does, but
 * also saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)      \
	do {                                                 \
		__pthread_cleanup_class __clframe(routine, arg); \
		__clframe.__defer()

/* Remove a cleanup handler as `pthread_cleanup_pop(3)' does, but also
 * restores the cancellation type that was in effect when the matching
 * `pthread_cleanup_push_defer(3)' was called. */
#define pthread_cleanup_pop_restore_np(execute) \
		__clframe.__restore();                  \
		__clframe.__setdoit(execute);           \
	}	__WHILE0
#endif /* __USE_GNU */
#else /* __cplusplus && !__CHECKER__ */
#ifdef __CRT_HAVE___pthread_cleanup_routine
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
__CEIDECLARE(__ATTR_INOUT(1),void,__NOTHROW_NCX,__pthread_cleanup_routine,(struct __pthread_cleanup_frame *__frame),{ if (__frame->__do_it) (*__frame->__cancel_routine)(__frame->__cancel_arg); })
#else /* __CRT_HAVE___pthread_cleanup_routine */
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
__LOCAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __pthread_cleanup_routine)(struct __pthread_cleanup_frame *__frame) { if (__frame->__do_it) (*__frame->__cancel_routine)(__frame->__cancel_arg); }
#endif /* !__CRT_HAVE___pthread_cleanup_routine */
/* Install  a cleanup handler: `routine' will be called with arguments `arg'
 * when  the thread is  canceled or calls  pthread_exit. `routine' will also
 * be called with arguments `arg' when the matching `pthread_cleanup_pop(3)'
 * is executed with non-zero `execute' argument.
 * `pthread_cleanup_push(3)' and `pthread_cleanup_pop(3)' are macros and must
 * always be used  in matching  pairs at the  same nesting  level of  braces. */
#define pthread_cleanup_push(routine, arg)                          \
	do {                                                            \
		struct __pthread_cleanup_frame __clframe                    \
		__attribute__((__cleanup__(__pthread_cleanup_routine))) = { \
			.__cancel_routine = (routine),                          \
			.__cancel_arg = (arg),                                  \
			.__do_it = 1                                            \
		};

/* Remove a cleanup handler installed by the matching `pthread_cleanup_push(3)'.
 * If `execute' is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)   \
		__clframe.__do_it = (execute); \
	}	__WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as `pthread_cleanup_push(3)' does, but
 * also saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)                 \
	do {                                                            \
		struct __pthread_cleanup_frame __clframe                    \
		__attribute__((__cleanup__(__pthread_cleanup_routine))) = { \
			.__cancel_routine = (routine),                          \
			.__cancel_arg = (arg),                                  \
			.__do_it = 1                                            \
		};                                                          \
		(void)pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &__clframe.__cancel_type)

/* Remove a cleanup handler as `pthread_cleanup_pop(3)' does, but also
 * restores the cancellation type that was in effect when the matching
 * `pthread_cleanup_push_defer(3)' was called. */
#define pthread_cleanup_pop_restore_np(execute)                          \
		(void)pthread_setcanceltype(__clframe.__cancel_type, __NULLPTR); \
		__clframe.__do_it = (execute);                                   \
	}	__WHILE0

#endif /* __USE_GNU */
#endif /* !__cplusplus || __CHECKER__ */
#else /* __GNUC__ && __EXCEPTIONS */
/* Install  a cleanup handler: `routine' will be called with arguments `arg'
 * when  the thread is  canceled or calls  pthread_exit. `routine' will also
 * be called with arguments `arg' when the matching `pthread_cleanup_pop(3)'
 * is executed with non-zero `execute' argument.
 * pthread_cleanup_push and `pthread_cleanup_pop(3)' are macros and must
 * always be used in matching pairs at the same nesting level of braces. */
#define pthread_cleanup_push(routine, arg)                                                                    \
	do {                                                                                                      \
		__pthread_unwind_buf_t __cancel_buf;                                                                  \
		void (__LIBKCALL *__cancel_routine)(void *) = (routine);                                              \
		void *__cancel_arg                          = (arg);                                                  \
		int __not_first_call = __sigsetjmp((struct __jmp_buf_tag *)(void *)__cancel_buf.__cancel_jmp_buf, 0); \
		if __unlikely(__not_first_call) {                                                                     \
			(*__cancel_routine)(__cancel_arg);                                                                \
			__pthread_unwind_next(&__cancel_buf);                                                             \
			__builtin_unreachable();                                                                          \
		}                                                                                                     \
		__pthread_register_cancel(&__cancel_buf);                                                             \
		do {

__CDECLARE_VOID_OPT(__cleanup_fct_attribute,__NOTHROW_NCX,__pthread_register_cancel,(__pthread_unwind_buf_t *__buf),(__buf))
/* Remove a cleanup handler installed by the matching `pthread_cleanup_push(3)'.
 * If `execute' is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)                                                \
			do {                                                                    \
			} __WHILE0; /* Empty to allow label before `pthread_cleanup_pop(3)'. */ \
		} __WHILE0;                                                                 \
		__pthread_unregister_cancel(&__cancel_buf);                                 \
		if (execute)                                                                \
			(*__cancel_routine)(__cancel_arg);                                      \
	}	__WHILE0
__CDECLARE_VOID_OPT(__cleanup_fct_attribute __ATTR_INOUT(1),__NOTHROW_NCX,__pthread_unregister_cancel,(__pthread_unwind_buf_t *__buf),(__buf))
#ifdef __USE_GNU
/* Install a cleanup handler as `pthread_cleanup_push(3)' does, but
 * also saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)                                                           \
	do {                                                                                                      \
		__pthread_unwind_buf_t __cancel_buf;                                                                  \
		void (__LIBKCALL *__cancel_routine)(void *) = (routine);                                              \
		void *__cancel_arg = (arg);                                                                           \
		int __not_first_call = __sigsetjmp((struct __jmp_buf_tag *)(void *)__cancel_buf.__cancel_jmp_buf, 0); \
		if __unlikely(__not_first_call) {                                                                     \
			__cancel_routine(__cancel_arg);                                                                   \
			__pthread_unwind_next(&__cancel_buf);                                                             \
			__builtin_unreachable();                                                                          \
		}                                                                                                     \
		__pthread_register_cancel_defer(&__cancel_buf);                                                       \
		do {
__CDECLARE_VOID_OPT(__cleanup_fct_attribute __ATTR_INOUT(1),__NOTHROW_NCX,__pthread_register_cancel_defer,(__pthread_unwind_buf_t *__buf),(__buf))
/* Remove a cleanup handler as `pthread_cleanup_pop(3)' does, but also
 * restores the cancellation type that was in effect when the matching
 * `pthread_cleanup_push_defer(3)' was called. */
#define pthread_cleanup_pop_restore_np(execute)                                     \
			do {                                                                    \
			} __WHILE0; /* Empty to allow label before `pthread_cleanup_pop(3)'. */ \
		} __WHILE0;                                                                 \
		__pthread_unregister_cancel_restore(&__cancel_buf);                         \
		if (execute)                                                                \
			(*__cancel_routine)(__cancel_arg);                                      \
	}	__WHILE0
__CDECLARE_VOID_OPT(__cleanup_fct_attribute __ATTR_INOUT(1),__NOTHROW_NCX,__pthread_unregister_cancel_restore,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* __USE_GNU */
/* Internal interface to initiate cleanup */
__CDECLARE_VOID_OPT(__ATTR_WEAK __cleanup_fct_attribute __ATTR_INOUT(1),__NOTHROW_NCX,__pthread_unwind_next,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* !__GNUC__ || !__EXCEPTIONS */

/* Function used in the macros. */
struct __jmp_buf_tag;
#ifdef __CRT_HAVE___sigsetjmp
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,__sigsetjmp,(struct __jmp_buf_tag *__env, int __savemask),(__env,__savemask))
#elif defined(__CRT_HAVE_sigsetjmp)
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__sigsetjmp,(struct __jmp_buf_tag *__env, int __savemask),sigsetjmp,(__env,__savemask))
#endif /* ... */


/************************************************************************/
/* pthread_mutex_t                                                      */
/************************************************************************/

#ifdef __CRT_HAVE_pthread_mutex_init
/* >> pthread_mutex_init(3)
 * Initialize the given mutex `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_init,(pthread_mutex_t *__self, pthread_mutexattr_t const *__mutexattr),(__self,__mutexattr))
#elif defined(__CRT_HAVE___pthread_mutex_init)
/* >> pthread_mutex_init(3)
 * Initialize the given mutex `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_init,(pthread_mutex_t *__self, pthread_mutexattr_t const *__mutexattr),__pthread_mutex_init,(__self,__mutexattr))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutex_destroy
/* >> pthread_mutex_destroy(3)
 * Destroy the given mutex `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_destroy,(pthread_mutex_t *__self),(__self))
#elif defined(__CRT_HAVE_mtx_destroy)
/* >> pthread_mutex_destroy(3)
 * Destroy the given mutex `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_destroy,(pthread_mutex_t *__self),mtx_destroy,(__self))
#elif defined(__CRT_HAVE___pthread_mutex_destroy)
/* >> pthread_mutex_destroy(3)
 * Destroy the given mutex `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_destroy,(pthread_mutex_t *__self),__pthread_mutex_destroy,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutex_trylock
/* >> pthread_mutex_trylock(3)
 * Try locking the given mutex `self'
 * @return: EOK:   Success
 * @return: EBUSY: The  mutex  has  already  been   locked
 *                 In case of  a recursive mutex,  another
 *                 thread was the one to acquire the lock. */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_trylock,(pthread_mutex_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_mutex_trylock)
/* >> pthread_mutex_trylock(3)
 * Try locking the given mutex `self'
 * @return: EOK:   Success
 * @return: EBUSY: The  mutex  has  already  been   locked
 *                 In case of  a recursive mutex,  another
 *                 thread was the one to acquire the lock. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_trylock,(pthread_mutex_t *__self),__pthread_mutex_trylock,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutex_lock
/* >> pthread_mutex_lock(3)
 * Lock the given mutex `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_lock,(pthread_mutex_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_mutex_lock)
/* >> pthread_mutex_lock(3)
 * Lock the given mutex `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_lock,(pthread_mutex_t *__self),__pthread_mutex_lock,(__self))
#endif /* ... */
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_mutex_timedlock) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock,(pthread_mutex_t *__restrict __self, struct timespec const *__restrict __abstime),(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock,(pthread_mutex_t *__restrict __self, struct timespec const *__restrict __abstime),pthread_mutex_timedlock64,(__self,__abstime))
#elif defined(__CRT_HAVE___pthread_mutex_timedlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock,(pthread_mutex_t *__restrict __self, struct timespec const *__restrict __abstime),__pthread_mutex_timedlock64,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock64) || defined(__CRT_HAVE___pthread_mutex_timedlock64) || defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <libc/local/pthread/pthread_mutex_timedlock.h>
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_timedlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_mutex_timedlock)(pthread_mutex_t *__restrict __self, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_timedlock))(__self, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_pthread_mutex_timedlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock64,(pthread_mutex_t *__restrict __self, struct timespec64 const *__restrict __abstime),pthread_mutex_timedlock,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock64)
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock64,(pthread_mutex_t *__restrict __self, struct timespec64 const *__restrict __abstime),(__self,__abstime))
#elif defined(__CRT_HAVE___pthread_mutex_timedlock64)
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock64,(pthread_mutex_t *__restrict __self, struct timespec64 const *__restrict __abstime),__pthread_mutex_timedlock64,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <libc/local/pthread/pthread_mutex_timedlock64.h>
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_timedlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_mutex_timedlock64)(pthread_mutex_t *__restrict __self, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_timedlock64))(__self, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */
#ifdef __USE_SOLARIS
#if defined(__CRT_HAVE_pthread_mutex_reltimedlock_np) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_reltimedlock_np,(pthread_mutex_t *__restrict __self, struct timespec const *__restrict __reltime),(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_mutex_reltimedlock64_np) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_reltimedlock_np,(pthread_mutex_t *__restrict __self, struct timespec const *__restrict __reltime),pthread_mutex_reltimedlock64_np,(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_mutex_reltimedlock64_np) || defined(__CRT_HAVE_pthread_mutex_reltimedlock_np)
#include <libc/local/pthread/pthread_mutex_reltimedlock_np.h>
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_reltimedlock_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_mutex_reltimedlock_np)(pthread_mutex_t *__restrict __self, struct timespec const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_reltimedlock_np))(__self, __reltime); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_pthread_mutex_reltimedlock_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_reltimedlock64_np,(pthread_mutex_t *__restrict __self, struct timespec64 const *__restrict __reltime),pthread_mutex_reltimedlock_np,(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_mutex_reltimedlock64_np)
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_mutex_reltimedlock64_np,(pthread_mutex_t *__restrict __self, struct timespec64 const *__restrict __reltime),(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_mutex_reltimedlock_np)
#include <libc/local/pthread/pthread_mutex_reltimedlock64_np.h>
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_reltimedlock64_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_mutex_reltimedlock64_np)(pthread_mutex_t *__restrict __self, struct timespec64 const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_reltimedlock64_np))(__self, __reltime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_SOLARIS */
#ifdef __CRT_HAVE_pthread_mutex_unlock
/* >> pthread_mutex_unlock(3)
 * Unlock the given mutex `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_unlock,(pthread_mutex_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_mutex_unlock)
/* >> pthread_mutex_unlock(3)
 * Unlock the given mutex `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_unlock,(pthread_mutex_t *__self),__pthread_mutex_unlock,(__self))
#endif /* ... */
/* >> pthread_mutex_getprioceiling(3)
 * Get the priority ceiling of `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutex_getprioceiling,(pthread_mutex_t const *__restrict __self, int *__restrict __prioceiling),(__self,__prioceiling))
/* >> pthread_mutex_setprioceiling(3)
 * Set the priority ceiling of `self' to `prioceiling',
 * return  old priority ceiling value in `*old_ceiling'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
__CDECLARE_OPT(__ATTR_INOUT(1) __ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,pthread_mutex_setprioceiling,(pthread_mutex_t *__restrict __self, int __prioceiling, int *__restrict __old_ceiling),(__self,__prioceiling,__old_ceiling))
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_pthread_mutex_consistent
/* >> pthread_mutex_consistent(3)
 * Declare the state protected by `self' as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent,(pthread_mutex_t *__self),(__self))
#elif defined(__CRT_HAVE_pthread_mutex_consistent_np)
/* >> pthread_mutex_consistent(3)
 * Declare the state protected by `self' as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent,(pthread_mutex_t *__self),pthread_mutex_consistent_np,(__self))
#endif /* ... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_mutex_consistent
/* >> pthread_mutex_consistent(3)
 * Declare the state protected by `self' as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent_np,(pthread_mutex_t *__self),pthread_mutex_consistent,(__self))
#elif defined(__CRT_HAVE_pthread_mutex_consistent_np)
/* >> pthread_mutex_consistent(3)
 * Declare the state protected by `self' as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent_np,(pthread_mutex_t *__self),(__self))
#endif /* ... */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K8 */


/************************************************************************/
/* pthread_mutexattr_t                                                  */
/************************************************************************/

#ifdef __CRT_HAVE_pthread_mutexattr_init
/* >> pthread_mutexattr_init(3)
 * Initialize mutex attribute object `self' with default
 * attributes    (kind    is   `PTHREAD_MUTEX_TIMED_NP')
 * @return: EOK: Success */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_init,(pthread_mutexattr_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_mutexattr_init)
/* >> pthread_mutexattr_init(3)
 * Initialize mutex attribute object `self' with default
 * attributes    (kind    is   `PTHREAD_MUTEX_TIMED_NP')
 * @return: EOK: Success */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_init,(pthread_mutexattr_t *__self),__pthread_mutexattr_init,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_destroy
/* >> pthread_mutexattr_destroy(3)
 * Destroy mutex attribute object `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_destroy,(pthread_mutexattr_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_mutexattr_destroy)
/* >> pthread_mutexattr_destroy(3)
 * Destroy mutex attribute object `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_destroy,(pthread_mutexattr_t *__self),__pthread_mutexattr_destroy,(__self))
#endif /* ... */
/* >> pthread_mutexattr_getpshared(3)
 * Get the process-shared flag of the mutex attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getpshared,(pthread_mutexattr_t const *__restrict __self, int *__restrict __pshared),(__self,__pshared))
/* >> pthread_mutexattr_setpshared(3)
 * Set the process-shared flag of the mutex attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setpshared,(pthread_mutexattr_t *__self, int __pshared),(__self,__pshared))
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifdef __CRT_HAVE_pthread_mutexattr_gettype
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_gettype,(pthread_mutexattr_t const *__restrict __self, int *__restrict __kind),(__self,__kind))
#elif defined(__CRT_HAVE_pthread_mutexattr_getkind_np)
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_gettype,(pthread_mutexattr_t const *__restrict __self, int *__restrict __kind),pthread_mutexattr_getkind_np,(__self,__kind))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_settype
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*self' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_settype,(pthread_mutexattr_t *__self, int __kind),(__self,__kind))
#elif defined(__CRT_HAVE_pthread_mutexattr_setkind_np)
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*self' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_settype,(pthread_mutexattr_t *__self, int __kind),pthread_mutexattr_setkind_np,(__self,__kind))
#elif defined(__CRT_HAVE___pthread_mutexattr_settype)
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*self' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_settype,(pthread_mutexattr_t *__self, int __kind),__pthread_mutexattr_settype,(__self,__kind))
#endif /* ... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
/* >> pthread_mutexattr_getprotocol(3)
 * Return in `*protocol' the mutex protocol attribute in `*self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getprotocol,(pthread_mutexattr_t const *__restrict __self, int *__restrict __protocol),(__self,__protocol))
/* >> pthread_mutexattr_setprotocol(3)
 * Set  the  mutex protocol  attribute  in `*self'  to  `protocol' (either
 * `PTHREAD_PRIO_NONE', `PTHREAD_PRIO_INHERIT', or `PTHREAD_PRIO_PROTECT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `protocol' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setprotocol,(pthread_mutexattr_t *__self, int __protocol),(__self,__protocol))
/* >> pthread_mutexattr_getprioceiling(3)
 * Return in `*prioceiling' the mutex prioceiling attribute in `*self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getprioceiling,(pthread_mutexattr_t const *__restrict __self, int *__restrict __prioceiling),(__self,__prioceiling))
/* >> pthread_mutexattr_setprioceiling(3)
 * Set the mutex prioceiling attribute in `*self' to `prioceiling'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setprioceiling,(pthread_mutexattr_t *__self, int __prioceiling),(__self,__prioceiling))
#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pthread_mutexattr_getrobust
/* >> pthread_mutexattr_getrobust(3)
 * Get the robustness flag of the mutex attribute `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust,(pthread_mutexattr_t const *__restrict __self, int *__restrict __robustness),(__self,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_getrobust_np)
/* >> pthread_mutexattr_getrobust(3)
 * Get the robustness flag of the mutex attribute `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust,(pthread_mutexattr_t const *__restrict __self, int *__restrict __robustness),pthread_mutexattr_getrobust_np,(__self,__robustness))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_setrobust
/* >> pthread_mutexattr_setrobust(3)
 * Set the robustness flag of the mutex attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust,(pthread_mutexattr_t *__self, int __robustness),(__self,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_setrobust_np)
/* >> pthread_mutexattr_setrobust(3)
 * Set the robustness flag of the mutex attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust,(pthread_mutexattr_t *__self, int __robustness),pthread_mutexattr_setrobust_np,(__self,__robustness))
#endif /* ... */
#endif /* __USE_XOPEN2K */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_mutexattr_getrobust
/* >> pthread_mutexattr_getrobust(3)
 * Get the robustness flag of the mutex attribute `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust_np,(pthread_mutexattr_t const *__restrict __self, int *__restrict __robustness),pthread_mutexattr_getrobust,(__self,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_getrobust_np)
/* >> pthread_mutexattr_getrobust(3)
 * Get the robustness flag of the mutex attribute `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust_np,(pthread_mutexattr_t const *__restrict __self, int *__restrict __robustness),(__self,__robustness))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_setrobust
/* >> pthread_mutexattr_setrobust(3)
 * Set the robustness flag of the mutex attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust_np,(pthread_mutexattr_t *__self, int __robustness),pthread_mutexattr_setrobust,(__self,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_setrobust_np)
/* >> pthread_mutexattr_setrobust(3)
 * Set the robustness flag of the mutex attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust_np,(pthread_mutexattr_t *__self, int __robustness),(__self,__robustness))
#endif /* ... */
#endif /* __USE_GNU */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)


/************************************************************************/
/* pthread_rwlock_t                                                     */
/************************************************************************/

#ifdef __CRT_HAVE_pthread_rwlock_init
/* >> pthread_rwlock_init(3)
 * Initialize read-write lock `self' using attributes `attr',
 * or  use   the  default   values   if  later   is   `NULL'.
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN_OPT(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_init,(pthread_rwlock_t *__restrict __self, pthread_rwlockattr_t const *__restrict __attr),(__self,__attr))
#elif defined(__CRT_HAVE___pthread_rwlock_init)
/* >> pthread_rwlock_init(3)
 * Initialize read-write lock `self' using attributes `attr',
 * or  use   the  default   values   if  later   is   `NULL'.
 * @return: EOK: Success */
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_init,(pthread_rwlock_t *__restrict __self, pthread_rwlockattr_t const *__restrict __attr),__pthread_rwlock_init,(__self,__attr))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_rwlock_destroy
/* >> pthread_rwlock_destroy(3)
 * Destroy read-write lock `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_destroy,(pthread_rwlock_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_rwlock_destroy)
/* >> pthread_rwlock_destroy(3)
 * Destroy read-write lock `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_destroy,(pthread_rwlock_t *__self),__pthread_rwlock_destroy,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_rwlock_rdlock
/* >> pthread_rwlock_rdlock(3)
 * Acquire read lock for `self'
 * @return: EOK:     Success
 * @return: EAGAIN:  The maximum # of read-locks has been acquired
 * @return: EDEADLK: You're already holding a write-lock
 * @return: EDEADLK: [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a read-lock */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_rdlock,(pthread_rwlock_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_rwlock_rdlock)
/* >> pthread_rwlock_rdlock(3)
 * Acquire read lock for `self'
 * @return: EOK:     Success
 * @return: EAGAIN:  The maximum # of read-locks has been acquired
 * @return: EDEADLK: You're already holding a write-lock
 * @return: EDEADLK: [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a read-lock */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_rdlock,(pthread_rwlock_t *__self),__pthread_rwlock_rdlock,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_rwlock_tryrdlock
/* >> pthread_rwlock_tryrdlock(3)
 * Try to acquire read lock for `self'
 * @return: EOK:    Success
 * @return: EBUSY:  A read-lock cannot be acquired at the moment,
 *                  because a write-lock  is already being  held.
 * @return: EAGAIN: The maximum # of read-locks has been acquired */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_tryrdlock,(pthread_rwlock_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_rwlock_tryrdlock)
/* >> pthread_rwlock_tryrdlock(3)
 * Try to acquire read lock for `self'
 * @return: EOK:    Success
 * @return: EBUSY:  A read-lock cannot be acquired at the moment,
 *                  because a write-lock  is already being  held.
 * @return: EAGAIN: The maximum # of read-locks has been acquired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_tryrdlock,(pthread_rwlock_t *__self),__pthread_rwlock_tryrdlock,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_rwlock_wrlock
/* >> pthread_rwlock_wrlock(3)
 * Acquire write lock for `self'
 * @return: EOK:     Success
 * @return: EDEADLK: You're already holding a read-lock
 * @return: EDEADLK: [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a write-lock */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_wrlock,(pthread_rwlock_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_rwlock_wrlock)
/* >> pthread_rwlock_wrlock(3)
 * Acquire write lock for `self'
 * @return: EOK:     Success
 * @return: EDEADLK: You're already holding a read-lock
 * @return: EDEADLK: [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a write-lock */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_wrlock,(pthread_rwlock_t *__self),__pthread_rwlock_wrlock,(__self))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_rwlock_trywrlock
/* >> pthread_rwlock_trywrlock(3)
 * Try to acquire write lock for `self'
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks  are  already  being  held. */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_trywrlock,(pthread_rwlock_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_rwlock_trywrlock)
/* >> pthread_rwlock_trywrlock(3)
 * Try to acquire write lock for `self'
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks  are  already  being  held. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_trywrlock,(pthread_rwlock_t *__self),__pthread_rwlock_trywrlock,(__self))
#endif /* ... */
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_rwlock_timedrdlock) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime),(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime),pthread_rwlock_timedrdlock64,(__self,__abstime))
#elif defined(__CRT_HAVE___pthread_rwlock_timedrdlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime),__pthread_rwlock_timedrdlock64,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock64) || defined(__CRT_HAVE___pthread_rwlock_timedrdlock64) || defined(__CRT_HAVE_pthread_rwlock_timedrdlock)
#include <libc/local/pthread/pthread_rwlock_timedrdlock.h>
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedrdlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedrdlock))(__self, __abstime); })
#endif /* ... */
#if defined(__CRT_HAVE_pthread_rwlock_timedwrlock) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime),(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime),pthread_rwlock_timedwrlock64,(__self,__abstime))
#elif defined(__CRT_HAVE___pthread_rwlock_timedwrlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime),__pthread_rwlock_timedwrlock64,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock64) || defined(__CRT_HAVE___pthread_rwlock_timedwrlock64) || defined(__CRT_HAVE_pthread_rwlock_timedwrlock)
#include <libc/local/pthread/pthread_rwlock_timedwrlock.h>
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedwrlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock))(__self, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_pthread_rwlock_timedrdlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock64,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime),pthread_rwlock_timedrdlock,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock64)
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock64,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime),(__self,__abstime))
#elif defined(__CRT_HAVE___pthread_rwlock_timedrdlock64)
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock64,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime),__pthread_rwlock_timedrdlock64,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock)
#include <libc/local/pthread/pthread_rwlock_timedrdlock64.h>
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedrdlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedrdlock64))(__self, __abstime); })
#endif /* ... */
#if defined(__CRT_HAVE_pthread_rwlock_timedwrlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock64,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime),pthread_rwlock_timedwrlock,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock64)
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock64,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime),(__self,__abstime))
#elif defined(__CRT_HAVE___pthread_rwlock_timedwrlock64)
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock64,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime),__pthread_rwlock_timedwrlock64,(__self,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock)
#include <libc/local/pthread/pthread_rwlock_timedwrlock64.h>
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `self' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedwrlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock64))(__self, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */
#ifdef __USE_SOLARIS
#if defined(__CRT_HAVE_pthread_rwlock_reltimedrdlock_np) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedrdlock_np,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __reltime),(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedrdlock64_np) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedrdlock_np,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __reltime),pthread_rwlock_reltimedrdlock64_np,(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedrdlock64_np) || defined(__CRT_HAVE_pthread_rwlock_reltimedrdlock_np)
#include <libc/local/pthread/pthread_rwlock_reltimedrdlock_np.h>
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_reltimedrdlock_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_reltimedrdlock_np)(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_reltimedrdlock_np))(__self, __reltime); })
#endif /* ... */
#if defined(__CRT_HAVE_pthread_rwlock_reltimedwrlock_np) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedwrlock_np,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __reltime),(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedwrlock64_np) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedwrlock_np,(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __reltime),pthread_rwlock_reltimedwrlock64_np,(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedwrlock64_np) || defined(__CRT_HAVE_pthread_rwlock_reltimedwrlock_np)
#include <libc/local/pthread/pthread_rwlock_reltimedwrlock_np.h>
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_reltimedwrlock_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_reltimedwrlock_np)(pthread_rwlock_t *__restrict __self, struct timespec const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_reltimedwrlock_np))(__self, __reltime); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_pthread_rwlock_reltimedrdlock_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedrdlock64_np,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __reltime),pthread_rwlock_reltimedrdlock_np,(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedrdlock64_np)
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedrdlock64_np,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __reltime),(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedrdlock_np)
#include <libc/local/pthread/pthread_rwlock_reltimedrdlock64_np.h>
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to  acquire read  lock for  `self'  or return  after the  specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_reltimedrdlock64_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_reltimedrdlock64_np)(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_reltimedrdlock64_np))(__self, __reltime); })
#endif /* ... */
#if defined(__CRT_HAVE_pthread_rwlock_reltimedwrlock_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedwrlock64_np,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __reltime),pthread_rwlock_reltimedwrlock_np,(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedwrlock64_np)
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_rwlock_reltimedwrlock64_np,(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __reltime),(__self,__reltime))
#elif defined(__CRT_HAVE_pthread_rwlock_reltimedwrlock_np)
#include <libc/local/pthread/pthread_rwlock_reltimedwrlock64_np.h>
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to  acquire write  lock for  `self' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_reltimedwrlock64_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_reltimedwrlock64_np)(pthread_rwlock_t *__restrict __self, struct timespec64 const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_reltimedwrlock64_np))(__self, __reltime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_SOLARIS */
#ifdef __CRT_HAVE_pthread_rwlock_unlock
/* >> pthread_rwlock_unlock(3)
 * Unlock `self'
 * @return: EOK:   Success
 * @return: EPERM: You're not holding a read- or write-lock */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_unlock,(pthread_rwlock_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_rwlock_unlock)
/* >> pthread_rwlock_unlock(3)
 * Unlock `self'
 * @return: EOK:   Success
 * @return: EPERM: You're not holding a read- or write-lock */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlock_unlock,(pthread_rwlock_t *__self),__pthread_rwlock_unlock,(__self))
#endif /* ... */


/************************************************************************/
/* pthread_rwlockattr_t                                                 */
/************************************************************************/

/* >> pthread_rwlockattr_init(3)
 * Initialize attribute object `self' with default values
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_init,(pthread_rwlockattr_t *__self),(__self))
/* >> pthread_rwlockattr_destroy(3)
 * Destroy attribute object  `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_destroy,(pthread_rwlockattr_t *__self),(__self))
/* >> pthread_rwlockattr_getpshared(3)
 * Return current setting of process-shared attribute of `self' in `*pshared'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_getpshared,(pthread_rwlockattr_t const *__restrict __self, int *__restrict __pshared),(__self,__pshared))
/* >> pthread_rwlockattr_setpshared(3)
 * Set process-shared attribute of `self' to `pshared'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_setpshared,(pthread_rwlockattr_t *__self, int __pshared),(__self,__pshared))
/* >> pthread_rwlockattr_getkind_np(3)
 * Return current setting of reader/writer preference
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_getkind_np,(pthread_rwlockattr_t const *__restrict __self, int *__restrict __pref),(__self,__pref))
/* >> pthread_rwlockattr_setkind_np(3)
 * Set     reader/write     preference
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pref' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_setkind_np,(pthread_rwlockattr_t *__self, int __pref),(__self,__pref))
#endif /* __USE_UNIX98 || __USE_XOPEN2K */


/************************************************************************/
/* pthread_cond_t                                                       */
/************************************************************************/

#ifdef __CRT_HAVE_pthread_cond_init
/* >> pthread_cond_init(3)
 * Initialize condition variable `self' using attributes
 * `attr', or use the default values if later is `NULL'.
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN_OPT(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_cond_init,(pthread_cond_t *__restrict __self, pthread_condattr_t const *__restrict __cond_attr),(__self,__cond_attr))
#elif defined(__CRT_HAVE___pthread_cond_init)
/* >> pthread_cond_init(3)
 * Initialize condition variable `self' using attributes
 * `attr', or use the default values if later is `NULL'.
 * @return: EOK: Success */
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_cond_init,(pthread_cond_t *__restrict __self, pthread_condattr_t const *__restrict __cond_attr),__pthread_cond_init,(__self,__cond_attr))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_cond_destroy
/* >> pthread_cond_destroy(3)
 * Destroy condition variable `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_cond_destroy,(pthread_cond_t *__self),(__self))
#elif defined(__CRT_HAVE_cnd_destroy)
/* >> pthread_cond_destroy(3)
 * Destroy condition variable `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_cond_destroy,(pthread_cond_t *__self),cnd_destroy,(__self))
#elif defined(__CRT_HAVE___pthread_cond_destroy)
/* >> pthread_cond_destroy(3)
 * Destroy condition variable `self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_cond_destroy,(pthread_cond_t *__self),__pthread_cond_destroy,(__self))
#endif /* ... */
/* >> pthread_cond_signal(3)
 * Wake up one thread waiting for condition variable `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_cond_signal,(pthread_cond_t *__self),(__self))
/* >> pthread_cond_broadcast(3)
 * Wake up all threads waiting for condition variables `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_cond_broadcast,(pthread_cond_t *__self),(__self))
/* >> pthread_cond_wait(3)
 * Wait for condition variable `self' to be signaled or broadcast.
 * `mutex' is assumed to be locked before.
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_wait,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex),(__self,__mutex))
#if defined(__CRT_HAVE_pthread_cond_timedwait) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),(__self,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_cond_timedwait64,(__self,__mutex,__abstime))
#elif defined(__CRT_HAVE___pthread_cond_timedwait64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),__pthread_cond_timedwait64,(__self,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64) || defined(__CRT_HAVE___pthread_cond_timedwait64) || defined(__CRT_HAVE_pthread_cond_timedwait)
#include <libc/local/pthread/pthread_cond_timedwait.h>
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_timedwait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_cond_timedwait)(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_timedwait))(__self, __mutex, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_pthread_cond_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait64,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),pthread_cond_timedwait,(__self,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64)
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait64,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),(__self,__mutex,__abstime))
#elif defined(__CRT_HAVE___pthread_cond_timedwait64)
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait64,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),__pthread_cond_timedwait64,(__self,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait)
#include <libc/local/pthread/pthread_cond_timedwait64.h>
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `self' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_timedwait64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_cond_timedwait64)(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_timedwait64))(__self, __mutex, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#ifdef __USE_SOLARIS
#if defined(__CRT_HAVE_pthread_cond_reltimedwait_np) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_reltimedwait_np,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __reltime),(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_reltimedwait64_np) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_reltimedwait_np,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __reltime),pthread_cond_reltimedwait64_np,(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_reltimedwait64_np) || defined(__CRT_HAVE_pthread_cond_reltimedwait_np)
#include <libc/local/pthread/pthread_cond_reltimedwait_np.h>
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_reltimedwait_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_cond_reltimedwait_np)(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_reltimedwait_np))(__self, __mutex, __reltime); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_pthread_cond_reltimedwait_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_reltimedwait64_np,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __reltime),pthread_cond_reltimedwait_np,(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_reltimedwait64_np)
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,pthread_cond_reltimedwait64_np,(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __reltime),(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_reltimedwait_np)
#include <libc/local/pthread/pthread_cond_reltimedwait64_np.h>
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `self' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_reltimedwait64_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_cond_reltimedwait64_np)(pthread_cond_t *__restrict __self, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __reltime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_reltimedwait64_np))(__self, __mutex, __reltime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_SOLARIS */


/************************************************************************/
/* pthread_condattr_t                                                   */
/************************************************************************/

/* >> pthread_condattr_init(3)
 * Initialize condition variable attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_condattr_init,(pthread_condattr_t *__self),(__self))
/* >> pthread_condattr_destroy(3)
 * Destroy condition variable attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_condattr_destroy,(pthread_condattr_t *__self),(__self))
/* >> pthread_condattr_getpshared(3)
 * Get the process-shared flag of the condition variable attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_condattr_getpshared,(pthread_condattr_t const *__restrict __self, int *__restrict __pshared),(__self,__pshared))
/* >> pthread_condattr_setpshared(3)
 * Set the process-shared flag of the condition variable attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_condattr_setpshared,(pthread_condattr_t *__self, int __pshared),(__self,__pshared))
#ifdef __USE_XOPEN2K
/* >> pthread_condattr_getclock(3)
 * Get the clock selected for the condition variable attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_condattr_getclock,(pthread_condattr_t const *__restrict __self, __clockid_t *__restrict __clock_id),(__self,__clock_id))
/* >> pthread_condattr_setclock(3)
 * Set the clock selected for the condition variable attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `clock_id' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_condattr_setclock,(pthread_condattr_t *__self, __clockid_t __clock_id),(__self,__clock_id))
#endif /* __USE_XOPEN2K */


#ifdef __USE_XOPEN2K
/************************************************************************/
/* pthread_spinlock_t                                                   */
/************************************************************************/

#ifdef __CRT_HAVE_pthread_spin_init
/* >> pthread_spin_init(3)
 * Initialize the spinlock `self'. If `pshared' is nonzero
 * the  spinlock can be shared between different processes
 * @return: EOK: Success */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_spin_init,(pthread_spinlock_t *__self, int __pshared),(__self,__pshared))
#else /* __CRT_HAVE_pthread_spin_init */
#include <libc/local/pthread/pthread_spin_init.h>
/* >> pthread_spin_init(3)
 * Initialize the spinlock `self'. If `pshared' is nonzero
 * the  spinlock can be shared between different processes
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_init)(pthread_spinlock_t *__self, int __pshared) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_init))(__self, __pshared); })
#endif /* !__CRT_HAVE_pthread_spin_init */
#ifdef __CRT_HAVE_pthread_spin_destroy
/* >> pthread_spin_destroy(3)
 * Destroy the spinlock `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_spin_destroy,(pthread_spinlock_t *__self),(__self))
#else /* __CRT_HAVE_pthread_spin_destroy */
#include <libc/local/pthread/pthread_spin_destroy.h>
/* >> pthread_spin_destroy(3)
 * Destroy the spinlock `self'
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_destroy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_destroy)(pthread_spinlock_t *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_destroy))(__self); })
#endif /* !__CRT_HAVE_pthread_spin_destroy */
#ifdef __CRT_HAVE_pthread_spin_lock
/* >> pthread_spin_lock(3)
 * Wait until spinlock `self' is retrieved
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_spin_lock,(pthread_spinlock_t *__self),(__self))
#else /* __CRT_HAVE_pthread_spin_lock */
#include <libc/local/pthread/pthread_spin_lock.h>
/* >> pthread_spin_lock(3)
 * Wait until spinlock `self' is retrieved
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_lock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_lock)(pthread_spinlock_t *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_lock))(__self); })
#endif /* !__CRT_HAVE_pthread_spin_lock */
#ifdef __CRT_HAVE_pthread_spin_trylock
/* >> pthread_spin_trylock(3)
 * Try to lock spinlock `self'
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_spin_trylock,(pthread_spinlock_t *__self),(__self))
#else /* __CRT_HAVE_pthread_spin_trylock */
#include <libc/local/pthread/pthread_spin_trylock.h>
/* >> pthread_spin_trylock(3)
 * Try to lock spinlock `self'
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_trylock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_trylock)(pthread_spinlock_t *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_trylock))(__self); })
#endif /* !__CRT_HAVE_pthread_spin_trylock */
#ifdef __CRT_HAVE_pthread_spin_unlock
/* >> pthread_spin_unlock(3)
 * Release  spinlock  `self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_spin_unlock,(pthread_spinlock_t *__self),(__self))
#else /* __CRT_HAVE_pthread_spin_unlock */
#include <libc/local/pthread/pthread_spin_unlock.h>
/* >> pthread_spin_unlock(3)
 * Release  spinlock  `self'
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_unlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_unlock)(pthread_spinlock_t *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_unlock))(__self); })
#endif /* !__CRT_HAVE_pthread_spin_unlock */


/************************************************************************/
/* pthread_barrier_t                                                    */
/************************************************************************/

#ifdef __CRT_HAVE_pthread_barrier_init
/* >> pthread_barrier_init(3)
 * Initialize `self' with  the attributes in  `attr'.
 * The barrier is opened when `count' waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
__CDECLARE(__ATTR_IN_OPT(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_barrier_init,(pthread_barrier_t *__restrict __self, pthread_barrierattr_t const *__restrict __attr, unsigned int __count),(__self,__attr,__count))
#elif defined(__CRT_HAVE___pthread_barrier_init)
/* >> pthread_barrier_init(3)
 * Initialize `self' with  the attributes in  `attr'.
 * The barrier is opened when `count' waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_barrier_init,(pthread_barrier_t *__restrict __self, pthread_barrierattr_t const *__restrict __attr, unsigned int __count),__pthread_barrier_init,(__self,__attr,__count))
#endif /* ... */
/* >> pthread_barrier_destroy(3)
 * Destroy the given (previously dynamically initialized) `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_barrier_destroy,(pthread_barrier_t *__self),(__self))
#ifdef __CRT_HAVE_pthread_barrier_wait
/* >> pthread_barrier_wait(3)
 * Wait on  the given  `self'
 * @return: 0 :                            Success
 * @return: PTHREAD_BARRIER_SERIAL_THREAD: Success, and you were picked to be the "serialization" thread. */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_barrier_wait,(pthread_barrier_t *__self),(__self))
#elif defined(__CRT_HAVE___pthread_barrier_wait)
/* >> pthread_barrier_wait(3)
 * Wait on  the given  `self'
 * @return: 0 :                            Success
 * @return: PTHREAD_BARRIER_SERIAL_THREAD: Success, and you were picked to be the "serialization" thread. */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,pthread_barrier_wait,(pthread_barrier_t *__self),__pthread_barrier_wait,(__self))
#endif /* ... */


/************************************************************************/
/* pthread_barrierattr_t                                                */
/************************************************************************/

/* >> pthread_barrierattr_init(3)
 * Initialize barrier attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_barrierattr_init,(pthread_barrierattr_t *__self),(__self))
/* >> pthread_barrierattr_destroy(3)
 * Destroy previously dynamically initialized barrier attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_barrierattr_destroy,(pthread_barrierattr_t *__self),(__self))
/* >> pthread_barrierattr_getpshared(3)
 * Get the process-shared flag of the barrier attribute `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_barrierattr_getpshared,(pthread_barrierattr_t const *__restrict __self, int *__restrict __pshared),(__self,__pshared))
/* >> pthread_barrierattr_setpshared(3)
 * Set the process-shared flag of the barrier attribute `self'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_barrierattr_setpshared,(pthread_barrierattr_t *__self, int __pshared),(__self,__pshared))
#endif /* __USE_XOPEN2K */


/************************************************************************/
/* pthread_key_t                                                        */
/************************************************************************/

#ifdef __CRT_HAVE_pthread_key_create
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the  value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_key_create,(pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),(__key,__destr_function))
#elif defined(__CRT_HAVE_thr_keycreate)
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the  value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_key_create,(pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),thr_keycreate,(__key,__destr_function))
#elif defined(__CRT_HAVE___pthread_key_create)
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the  value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_key_create,(pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *___value)),__pthread_key_create,(__key,__destr_function))
#endif /* ... */
#ifdef __USE_SOLARIS
#ifndef PTHREAD_ONCE_KEY_NP
#ifdef __PTHREAD_ONCE_KEY_NP
#define PTHREAD_ONCE_KEY_NP __PTHREAD_ONCE_KEY_NP
#else /* __PTHREAD_ONCE_KEY_NP */
#define PTHREAD_ONCE_KEY_NP ((pthread_key_t)-1)
#endif /* !__PTHREAD_ONCE_KEY_NP */
#endif /* !PTHREAD_ONCE_KEY_NP */
#ifdef __CRT_HAVE_pthread_key_create_once_np
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_key_create_once_np,(pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)),(__key,__destr_function))
#elif defined(__CRT_HAVE_thr_keycreate_once)
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,pthread_key_create_once_np,(pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)),thr_keycreate_once,(__key,__destr_function))
#elif defined(__CRT_HAVE_pthread_key_create) || defined(__CRT_HAVE_thr_keycreate) || defined(__CRT_HAVE___pthread_key_create)
#include <libc/local/pthread/pthread_key_create_once_np.h>
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_key_create_once_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_key_create_once_np)(pthread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_key_create_once_np))(__key, __destr_function); })
#endif /* ... */
#endif /* __USE_SOLARIS */
#ifdef __CRT_HAVE_pthread_key_delete
/* >> pthread_key_delete(3)
 * Destroy the given  `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_key_delete,(pthread_key_t __key),(__key))
#elif defined(__CRT_HAVE_tss_delete)
/* >> pthread_key_delete(3)
 * Destroy the given  `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_key_delete,(pthread_key_t __key),tss_delete,(__key))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_getspecific
/* >> pthread_getspecific(3)
 * Return current value of the thread-specific data slot identified by `key'
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL'
 * @return: NULL: No value has been bound, yet
 * @return: NULL: Invalid `key' */
__CDECLARE(__ATTR_WUNUSED,void *,__NOTHROW_NCX,pthread_getspecific,(pthread_key_t __key),(__key))
#elif defined(__CRT_HAVE_tss_get)
/* >> pthread_getspecific(3)
 * Return current value of the thread-specific data slot identified by `key'
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL'
 * @return: NULL: No value has been bound, yet
 * @return: NULL: Invalid `key' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,pthread_getspecific,(pthread_key_t __key),tss_get,(__key))
#elif defined(__CRT_HAVE___pthread_getspecific)
/* >> pthread_getspecific(3)
 * Return current value of the thread-specific data slot identified by `key'
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL'
 * @return: NULL: No value has been bound, yet
 * @return: NULL: Invalid `key' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,pthread_getspecific,(pthread_key_t __key),__pthread_getspecific,(__key))
#elif defined(__CRT_HAVE_pthread_getspecificptr_np)
#include <libc/local/pthread/pthread_getspecific.h>
/* >> pthread_getspecific(3)
 * Return current value of the thread-specific data slot identified by `key'
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL'
 * @return: NULL: No value has been bound, yet
 * @return: NULL: Invalid `key' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_getspecific, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED void *__NOTHROW_NCX(__LIBCCALL pthread_getspecific)(pthread_key_t __key) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_getspecific))(__key); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_setspecific
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
__CDECLARE(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,pthread_setspecific,(pthread_key_t __key, void const *__pointer),(__key,__pointer))
#elif defined(__CRT_HAVE_thr_setspecific)
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
__CREDIRECT(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,pthread_setspecific,(pthread_key_t __key, void const *__pointer),thr_setspecific,(__key,__pointer))
#elif defined(__CRT_HAVE___pthread_setspecific)
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
__CREDIRECT(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,pthread_setspecific,(pthread_key_t __key, void const *__pointer),__pthread_setspecific,(__key,__pointer))
#endif /* ... */
#ifdef __USE_KOS
/* >> pthread_getspecificptr_np(3)
 * Return a pointer to the per-thread storage location associated with `key'
 * @return: * :   The address read/written by `pthread_getspecific()' / `pthread_setspecific()'
 * @return: NULL: `key' had yet to be allocated for the calling thread,
 *                and an  attempt  to  allocate  it  just  now  failed.
 * @return: NULL: Invalid `key'. */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED,void **,__NOTHROW_NCX,pthread_getspecificptr_np,(pthread_key_t __key),(__key))
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K
/* >> pthread_getcpuclockid(3)
 * Get the ID of CPU-time clock for thread `self'
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_getcpuclockid,(pthread_t __self, __clockid_t *__clock_id),(__self,__clock_id))
#endif /* __USE_XOPEN2K */
#ifndef __pthread_atfork_defined
#define __pthread_atfork_defined
#ifdef __CRT_HAVE_pthread_atfork
/* >> pthread_atfork(3)
 * Install handlers to be called when a new process is created with  `fork(2)'.
 * The `prepare' handler is called in the parent process just before performing
 * `fork(2)'. The `parent' handler is called  in the parent process just  after
 * `fork(2)'.  The `child' handler is called in  the child process. Each of the
 * three  handlers can be `NULL', meaning that no handler needs to be called at
 * that point.
 * `pthread_atfork(3)' can be called several times, in which case the `prepare'
 * handlers are  called in  LIFO order  (last added  with  `pthread_atfork(3)',
 * first  called before `fork(2)'),  and the `parent'  and `child' handlers are
 * called in FIFO order (first added -> first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_atfork,(void (__LIBCCALL *__prepare)(void), void (__LIBCCALL *__parent)(void), void (__LIBCCALL *__child)(void)),(__prepare,__parent,__child))
#elif defined(__CRT_HAVE___pthread_atfork)
/* >> pthread_atfork(3)
 * Install handlers to be called when a new process is created with  `fork(2)'.
 * The `prepare' handler is called in the parent process just before performing
 * `fork(2)'. The `parent' handler is called  in the parent process just  after
 * `fork(2)'.  The `child' handler is called in  the child process. Each of the
 * three  handlers can be `NULL', meaning that no handler needs to be called at
 * that point.
 * `pthread_atfork(3)' can be called several times, in which case the `prepare'
 * handlers are  called in  LIFO order  (last added  with  `pthread_atfork(3)',
 * first  called before `fork(2)'),  and the `parent'  and `child' handlers are
 * called in FIFO order (first added -> first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_atfork,(void (__LIBCCALL *__prepare)(void), void (__LIBCCALL *__parent)(void), void (__LIBCCALL *__child)(void)),__pthread_atfork,(__prepare,__parent,__child))
#else /* ... */
#undef __pthread_atfork_defined
#endif /* !... */
#endif /* !__pthread_atfork_defined */


/* Some more functions from winpthread. */
#ifdef __CRT_HAVE_pthread_num_processors_np
/* >> pthread_num_processors_np(3)
 * @return: * : The number of cpus that the calling thread is able to run on */
__CDECLARE(__ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,pthread_num_processors_np,(void),())
#elif defined(__CRT_HAVE_sched_getaffinity)
#include <libc/local/pthread/pthread_num_processors_np.h>
/* >> pthread_num_processors_np(3)
 * @return: * : The number of cpus that the calling thread is able to run on */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_num_processors_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL pthread_num_processors_np)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_num_processors_np))(); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_set_num_processors_np
/* >> pthread_set_num_processors_np(3)
 * Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_set_num_processors_np,(int __n),(__n))
#elif defined(__CRT_HAVE_sched_setaffinity)
#include <libc/local/pthread/pthread_set_num_processors_np.h>
/* >> pthread_set_num_processors_np(3)
 * Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_set_num_processors_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL pthread_set_num_processors_np)(int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_set_num_processors_np))(__n); })
#endif /* ... */
#ifdef __USE_BSD
#ifndef __pthread_main_np_defined
#define __pthread_main_np_defined
#ifdef __CRT_HAVE_pthread_main_np
/* >> pthread_main_np(3)
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,pthread_main_np,(void),())
#elif defined(__CRT_HAVE_thr_main)
/* >> pthread_main_np(3)
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,pthread_main_np,(void),thr_main,())
#elif (defined(__CRT_HAVE_pthread_mainthread_np) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))) || ((defined(__CRT_HAVE_gettid) || defined(__CRT_HAVE___threadid) || defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ) || defined(__CRT_HAVE_pthread_getthreadid_np)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
#include <libc/local/pthread/pthread_main_np.h>
/* >> pthread_main_np(3)
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_main_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL pthread_main_np)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_main_np))(); })
#else /* ... */
#undef __pthread_main_np_defined
#endif /* !... */
#endif /* !__pthread_main_np_defined */
#endif /* __USE_BSD */


/* KOS-specific pthread extensions. */
#ifdef __USE_KOS
/* >> pthread_attr_setstartsuspended_np(3)
 * Specify if `pthread_create(3)' should start the thread in a suspended state.
 * @param: start_suspended: 0=no (default) or 1=yes
 * @see pthread_resume_np, pthread_continue_np
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `start_suspended' */
__CDECLARE_OPT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setstartsuspended_np,(pthread_attr_t *__restrict __self, int __start_suspended),(__self,__start_suspended))
/* >> pthread_attr_getpidfdallocated_np(3)
 * Write 0=no or 1=yes to `*start_suspended', indicative of `pthread_create(3)'
 * starting  newly spawned thread  in a suspended  state (requiring the creator
 * to resume the thread at least once before execution actually starts)
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_getstartsuspended_np,(pthread_attr_t const *__restrict __self, int *__start_suspended),(__self,__start_suspended))
/* >> pthread_suspend2_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code. The counter's old value is optionally stored  in
 * `p_old_suspend_counter' (when non-NULL)
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume2_np(3)')
 *
 * @see pthread_suspend_np, pthread_resume2_np, pthread_resume_np, pthread_continue_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
__CDECLARE_OPT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_suspend2_np,(pthread_t __self, __UINT32_TYPE__ *__p_old_suspend_counter),(__self,__p_old_suspend_counter))
/* >> pthread_resume2_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1). The
 * counter's old  value is  optionally stored  in `p_old_suspend_counter'  (when
 * non-NULL).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CDECLARE_OPT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_resume2_np,(pthread_t __self, __UINT32_TYPE__ *__p_old_suspend_counter),(__self,__p_old_suspend_counter))
/* >> pthread_attach_np(3)
 * Attach  to `self' for a second time. After a call to this function, `pthread_detach(3)'
 * must be called one extra time before the thread descriptor `self' is actually destroyed */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,pthread_attach_np,(pthread_t __self),(__self))
/* >> pthread_enumthreads_np(3)
 * Enumerate all threads created by `pthread_create(3)' by invoking `cb' once for each of them.
 * Only threads whose descriptors have yet to be destroyed are enumerated, and care is taken to
 * ensure that the `thrd' passed  to `cb' cannot be destroyed  while inside of `cb'. Also  note
 * that `cb' is allowed to call `pthread_attach_np(3)' to re-attach previously detached  thread
 * descriptors (assuming that those descriptors haven't been destroyed, yet)
 * @return: * :     A call to `cb' returned a value other than `EOK', and enumeration was halted
 * @return: EOK:    All threads were enumerated by being passed to `cb'
 * @return: ENOMEM: Insufficient memory to allocate a required, internal buffer */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_enumthreads_np,(__errno_t (__LIBKCALL *__cb)(void *__cookie, pthread_t __thrd), void *__cookie),(__cb,__cookie))
/* >> pthread_attachtid_np(3)
 * Return a descriptor for a (potentially, previously detached) thread `tid'.
 * This function cannot be used to attach threads created by means other than
 * via `pthread_create(3)', and also won't work  for threads not part of  the
 * calling process.
 * Semantically, this function is equivalent to calling `pthread_enumthreads_np(3)'
 * in  other  to  find the  correct  thread, then  using  `pthread_attach_np(3)' to
 * (re-)attach a reference to its descriptor.
 *
 * @return: EOK:    Success. In this case, the caller must use `pthread_detach(3)'
 *                  in  order  to   release  the  new   reference  to   `*result'.
 * @return: EINVAL: Invalid `tid' (is `0' or negative)
 * @return: ESRCH:  Descriptor for thread with `tid' has already been destroyed,
 *                  or didn't exist  (within the calling  process) in the  first
 *                  place. */
__CDECLARE_OPT(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attachtid_np,(__pid_t __tid, pthread_t *__restrict __result),(__tid,__result))
/* >> pthread_attachpidfd_np(3)
 * Similar to `pthread_attachtid_np(3)', but search for a thread that has an
 * allocated PIDfd descriptor (as returned by `pthread_getpidfd_np(3)'), and
 * (re-)attach that thread's descriptor.  Only the original file  descriptor
 * returned by `pthread_getpidfd_np(3)' is  understood by this function.  If
 * you `dup(2)' that descriptor and try to pass the duplicate, this function
 * will be unable to locate your descriptor.
 *
 * @return: EOK:    Success. In this case, the caller must use `pthread_detach(3)'
 *                  in  order  to   release  the  new   reference  to   `*result'.
 * @return: EINVAL: Invalid `pidfd' (is negative)
 * @return: ESRCH:  Descriptor for thread with `pidfd' has already been  destroyed,
 *                  or  didn't  exist (within  the  calling process)  in  the first
 *                  place, or the given `pidfd' is not what was originally returned
 *                  by  `pthread_getpidfd_np(3)'  (but is  the result  of `dup(2)') */
__CDECLARE_OPT(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attachpidfd_np,(__fd_t __pidfd, pthread_t *__restrict __result),(__pidfd,__result))
#endif /* __USE_KOS */


/* TODO: Figure out if these extensions should also appear under other `__USE_*' configurations */
#ifdef __USE_KOS
#ifndef __pthread_continue_np_defined
#define __pthread_continue_np_defined
#ifdef __CRT_HAVE_pthread_continue_np
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_continue_np,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_thr_continue)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_continue_np,(pthread_t __self),thr_continue,(__self))
#elif defined(__CRT_HAVE_pthread_unsuspend_np)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_continue_np,(pthread_t __self),pthread_unsuspend_np,(__self))
#else /* ... */
#undef __pthread_continue_np_defined
#endif /* !... */
#endif /* !__pthread_continue_np_defined */
#ifndef __pthread_attr_setcreatesuspend_np_defined
#define __pthread_attr_setcreatesuspend_np_defined
#ifdef __CRT_HAVE_pthread_attr_setcreatesuspend_np
/* >> pthread_attr_setcreatesuspend_np(3)
 * Setup `self' such that created threads start in a "suspended" state,
 * requiring a call to one of the following function to actually start:
 *  - `pthread_continue_np(3)' (or `pthread_unsuspend_np(3)')
 *  - `pthread_resume_np(3)'
 *  - `pthread_resume_all_np(3)'
 * Alias for `pthread_attr_setstartsuspended_np(self, 1)'
 * @return: EOK: Always returned */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setcreatesuspend_np,(pthread_attr_t *__restrict __self),(__self))
#elif defined(__CRT_HAVE_pthread_attr_setstartsuspended_np)
#include <libc/local/pthread/pthread_attr_setcreatesuspend_np.h>
/* >> pthread_attr_setcreatesuspend_np(3)
 * Setup `self' such that created threads start in a "suspended" state,
 * requiring a call to one of the following function to actually start:
 *  - `pthread_continue_np(3)' (or `pthread_unsuspend_np(3)')
 *  - `pthread_resume_np(3)'
 *  - `pthread_resume_all_np(3)'
 * Alias for `pthread_attr_setstartsuspended_np(self, 1)'
 * @return: EOK: Always returned */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_setcreatesuspend_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_setcreatesuspend_np)(pthread_attr_t *__restrict __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_setcreatesuspend_np))(__self); })
#else /* ... */
#undef __pthread_attr_setcreatesuspend_np_defined
#endif /* !... */
#endif /* !__pthread_attr_setcreatesuspend_np_defined */
#ifndef __pthread_suspend_np_defined
#define __pthread_suspend_np_defined
#ifdef __CRT_HAVE_pthread_suspend_np
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_suspend_np,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_thr_suspend)
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_suspend_np,(pthread_t __self),thr_suspend,(__self))
#elif defined(__CRT_HAVE_pthread_suspend2_np)
#include <libc/local/pthread/pthread_suspend_np.h>
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_suspend_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL pthread_suspend_np)(pthread_t __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_suspend_np))(__self); })
#else /* ... */
#undef __pthread_suspend_np_defined
#endif /* !... */
#endif /* !__pthread_suspend_np_defined */
#ifndef __pthread_resume_np_defined
#define __pthread_resume_np_defined
#ifdef __CRT_HAVE_pthread_resume_np
/* >> pthread_suspend_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_resume_np,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_pthread_resume2_np)
#include <libc/local/pthread/pthread_resume_np.h>
/* >> pthread_suspend_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_resume_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL pthread_resume_np)(pthread_t __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_resume_np))(__self); })
#else /* ... */
#undef __pthread_resume_np_defined
#endif /* !... */
#endif /* !__pthread_resume_np_defined */
#ifndef __pthread_unsuspend_np_defined
#define __pthread_unsuspend_np_defined
#ifdef __CRT_HAVE_pthread_continue_np
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_unsuspend_np,(pthread_t __self),pthread_continue_np,(__self))
#elif defined(__CRT_HAVE_thr_continue)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_unsuspend_np,(pthread_t __self),thr_continue,(__self))
#elif defined(__CRT_HAVE_pthread_unsuspend_np)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_unsuspend_np,(pthread_t __self),(__self))
#else /* ... */
#undef __pthread_unsuspend_np_defined
#endif /* !... */
#endif /* !__pthread_unsuspend_np_defined */
#ifndef __pthread_suspend_all_np_defined
#define __pthread_suspend_all_np_defined
#ifdef __CRT_HAVE_pthread_suspend_all_np
/* >> pthread_suspend_all_np(3)
 * Calls  `pthread_suspend_np(3)' once for every running thread but the calling one
 * After a call to this function, the calling thread is the only one running within
 * the current process (at least of those created by `pthread_create(3)')
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume_all_np(3)')
 *
 * @return: EOK:       Success
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter of some thread can't go any higher */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_suspend_all_np,(void),())
#elif defined(__CRT_HAVE_pthread_single_np)
/* >> pthread_suspend_all_np(3)
 * Calls  `pthread_suspend_np(3)' once for every running thread but the calling one
 * After a call to this function, the calling thread is the only one running within
 * the current process (at least of those created by `pthread_create(3)')
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume_all_np(3)')
 *
 * @return: EOK:       Success
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter of some thread can't go any higher */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_suspend_all_np,(void),pthread_single_np,())
#else /* ... */
#undef __pthread_suspend_all_np_defined
#endif /* !... */
#endif /* !__pthread_suspend_all_np_defined */
#ifndef __pthread_resume_all_np_defined
#define __pthread_resume_all_np_defined
#ifdef __CRT_HAVE_pthread_resume_all_np
/* >> pthread_resume_all_np(3)
 * Calls `pthread_continue_np(3)' once for every running thread but the calling one.
 * This  function  essentially reverses  the effects  of `pthread_suspend_all_np(3)' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_resume_all_np,(void),())
#elif defined(__CRT_HAVE_pthread_multi_np)
/* >> pthread_resume_all_np(3)
 * Calls `pthread_continue_np(3)' once for every running thread but the calling one.
 * This  function  essentially reverses  the effects  of `pthread_suspend_all_np(3)' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_resume_all_np,(void),pthread_multi_np,())
#else /* ... */
#undef __pthread_resume_all_np_defined
#endif /* !... */
#endif /* !__pthread_resume_all_np_defined */
#endif /* __USE_KOS */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PTHREAD_H */
