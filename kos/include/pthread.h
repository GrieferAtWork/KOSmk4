/* HASH CRC-32:0xbc37331e */
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
#include <bits/types.h>
#include <kos/anno.h>

#include <endian.h>
#include <sched.h>
#include <time.h>

__SYSDECL_BEGIN

/* (some) documentation take from Glibc /usr/include/pthread.h: */
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
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


#if defined(__PTHREAD_CREATE_JOINABLE) || defined(__PTHREAD_CREATE_DETACHED)
/* Detach state. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_CREATE_JOINABLE
	PTHREAD_CREATE_JOINABLE = __PTHREAD_CREATE_JOINABLE,
#endif /* __PTHREAD_CREATE_JOINABLE */
#ifdef __PTHREAD_CREATE_DETACHED
	PTHREAD_CREATE_DETACHED = __PTHREAD_CREATE_DETACHED
#endif /* __PTHREAD_CREATE_DETACHED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_CREATE_JOINABLE
#define PTHREAD_CREATE_JOINABLE PTHREAD_CREATE_JOINABLE
#endif /* __PTHREAD_CREATE_JOINABLE */
#ifdef __PTHREAD_CREATE_DETACHED
#define PTHREAD_CREATE_DETACHED PTHREAD_CREATE_DETACHED
#endif /* __PTHREAD_CREATE_DETACHED */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_CREATE_JOINABLE
#define PTHREAD_CREATE_JOINABLE __PTHREAD_CREATE_JOINABLE
#endif /* __PTHREAD_CREATE_JOINABLE */
#ifdef __PTHREAD_CREATE_DETACHED
#define PTHREAD_CREATE_DETACHED __PTHREAD_CREATE_DETACHED
#endif /* __PTHREAD_CREATE_DETACHED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#if (defined(__PTHREAD_MUTEX_TIMED) || defined(__PTHREAD_MUTEX_RECURSIVE) ||     \
     defined(__PTHREAD_MUTEX_ERRORCHECK) || defined(__PTHREAD_MUTEX_ADAPTIVE) || \
     (defined(__USE_XOPEN2K) && (defined(__PTHREAD_MUTEX_STALLED) ||             \
                                 defined(__PTHREAD_MUTEX_ROBUST))))
/* Mutex types. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_MUTEX_TIMED
	PTHREAD_MUTEX_TIMED_NP      = __PTHREAD_MUTEX_TIMED,
#endif /* __PTHREAD_MUTEX_TIMED */
#ifdef __PTHREAD_MUTEX_RECURSIVE
	PTHREAD_MUTEX_RECURSIVE_NP  = __PTHREAD_MUTEX_RECURSIVE,
#endif /* __PTHREAD_MUTEX_RECURSIVE */
#ifdef __PTHREAD_MUTEX_ERRORCHECK
	PTHREAD_MUTEX_ERRORCHECK_NP = __PTHREAD_MUTEX_ERRORCHECK,
#endif /* __PTHREAD_MUTEX_ERRORCHECK */
#ifdef __PTHREAD_MUTEX_ADAPTIVE
	PTHREAD_MUTEX_ADAPTIVE_NP   = __PTHREAD_MUTEX_ADAPTIVE,
#endif /* __PTHREAD_MUTEX_ADAPTIVE */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifdef __PTHREAD_MUTEX_TIMED
	PTHREAD_MUTEX_NORMAL     = __PTHREAD_MUTEX_TIMED,
#endif /* __PTHREAD_MUTEX_TIMED */
#ifdef __PTHREAD_MUTEX_RECURSIVE
	PTHREAD_MUTEX_RECURSIVE  = __PTHREAD_MUTEX_RECURSIVE,
#endif /* __PTHREAD_MUTEX_RECURSIVE */
#ifdef __PTHREAD_MUTEX_ERRORCHECK
	PTHREAD_MUTEX_ERRORCHECK = __PTHREAD_MUTEX_ERRORCHECK,
#endif /* __PTHREAD_MUTEX_ERRORCHECK */
#ifdef __PTHREAD_MUTEX_TIMED
	PTHREAD_MUTEX_DEFAULT    = __PTHREAD_MUTEX_TIMED,
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#ifdef __PTHREAD_MUTEX_TIMED
	PTHREAD_MUTEX_FAST_NP = __PTHREAD_MUTEX_TIMED, /* For compatibility. */
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
	PTHREAD_MUTEX_STALLED    = __PTHREAD_MUTEX_STALLED, /* Robust mutex or not flags. */
	PTHREAD_MUTEX_STALLED_NP = __PTHREAD_MUTEX_STALLED, /* Robust mutex or not flags. */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
	PTHREAD_MUTEX_ROBUST     = __PTHREAD_MUTEX_ROBUST,  /* ... */
	PTHREAD_MUTEX_ROBUST_NP  = __PTHREAD_MUTEX_ROBUST,  /* ... */
#endif /* __PTHREAD_MUTEX_ROBUST */
#endif /* __USE_XOPEN2K */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_TIMED_NP      PTHREAD_MUTEX_TIMED_NP
#endif /* __PTHREAD_MUTEX_TIMED */
#ifdef __PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_RECURSIVE_NP  PTHREAD_MUTEX_RECURSIVE_NP
#endif /* __PTHREAD_MUTEX_RECURSIVE */
#ifdef __PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ERRORCHECK_NP PTHREAD_MUTEX_ERRORCHECK_NP
#endif /* __PTHREAD_MUTEX_ERRORCHECK */
#ifdef __PTHREAD_MUTEX_ADAPTIVE
#define PTHREAD_MUTEX_ADAPTIVE_NP   PTHREAD_MUTEX_ADAPTIVE_NP
#endif /* __PTHREAD_MUTEX_ADAPTIVE */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_NORMAL        PTHREAD_MUTEX_NORMAL
#endif /* __PTHREAD_MUTEX_TIMED */
#ifdef __PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_RECURSIVE     PTHREAD_MUTEX_RECURSIVE
#endif /* __PTHREAD_MUTEX_RECURSIVE */
#ifdef __PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ERRORCHECK    PTHREAD_MUTEX_ERRORCHECK
#endif /* __PTHREAD_MUTEX_ERRORCHECK */
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_DEFAULT       PTHREAD_MUTEX_DEFAULT
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_FAST_NP       PTHREAD_MUTEX_FAST_NP       /* For compatibility. */
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
#define PTHREAD_MUTEX_STALLED       PTHREAD_MUTEX_STALLED       /* Robust mutex or not flags. */
#define PTHREAD_MUTEX_STALLED_NP    PTHREAD_MUTEX_STALLED_NP    /* Robust mutex or not flags. */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
#define PTHREAD_MUTEX_ROBUST        PTHREAD_MUTEX_ROBUST        /* ... */
#define PTHREAD_MUTEX_ROBUST_NP     PTHREAD_MUTEX_ROBUST_NP     /* ... */
#endif /* __PTHREAD_MUTEX_ROBUST */
#endif /* __USE_XOPEN2K */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_TIMED_NP      __PTHREAD_MUTEX_TIMED
#endif /* __PTHREAD_MUTEX_TIMED */
#ifdef __PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_RECURSIVE_NP  __PTHREAD_MUTEX_RECURSIVE
#endif /* __PTHREAD_MUTEX_RECURSIVE */
#ifdef __PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ERRORCHECK_NP __PTHREAD_MUTEX_ERRORCHECK
#endif /* __PTHREAD_MUTEX_ERRORCHECK */
#ifdef __PTHREAD_MUTEX_ADAPTIVE
#define PTHREAD_MUTEX_ADAPTIVE_NP   __PTHREAD_MUTEX_ADAPTIVE
#endif /* __PTHREAD_MUTEX_ADAPTIVE */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_NORMAL        __PTHREAD_MUTEX_TIMED
#endif /* __PTHREAD_MUTEX_TIMED */
#ifdef __PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_RECURSIVE     __PTHREAD_MUTEX_RECURSIVE
#endif /* __PTHREAD_MUTEX_RECURSIVE */
#ifdef __PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ERRORCHECK    __PTHREAD_MUTEX_ERRORCHECK
#endif /* __PTHREAD_MUTEX_ERRORCHECK */
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_DEFAULT       __PTHREAD_MUTEX_TIMED
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#ifdef __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_FAST_NP       __PTHREAD_MUTEX_TIMED      /* For compatibility. */
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
#define PTHREAD_MUTEX_STALLED       __PTHREAD_MUTEX_STALLED    /* Robust mutex or not flags. */
#define PTHREAD_MUTEX_STALLED_NP    __PTHREAD_MUTEX_STALLED    /* Robust mutex or not flags. */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
#define PTHREAD_MUTEX_ROBUST        __PTHREAD_MUTEX_ROBUST     /* ... */
#define PTHREAD_MUTEX_ROBUST_NP     __PTHREAD_MUTEX_ROBUST     /* ... */
#endif /* __PTHREAD_MUTEX_ROBUST */
#endif /* __USE_XOPEN2K */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#if (defined(__PTHREAD_PRIO_NONE) || defined(__PTHREAD_PRIO_INHERIT) || \
     defined(__PTHREAD_PRIO_PROTECT))
/* Mutex protocols. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_PRIO_NONE
	PTHREAD_PRIO_NONE    = __PTHREAD_PRIO_NONE,
#endif /* __PTHREAD_PRIO_NONE */
#ifdef __PTHREAD_PRIO_INHERIT
	PTHREAD_PRIO_INHERIT = __PTHREAD_PRIO_INHERIT,
#endif /* __PTHREAD_PRIO_INHERIT */
#ifdef __PTHREAD_PRIO_PROTECT
	PTHREAD_PRIO_PROTECT = __PTHREAD_PRIO_PROTECT,
#endif /* __PTHREAD_PRIO_PROTECT */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_PRIO_NONE
#define PTHREAD_PRIO_NONE    PTHREAD_PRIO_NONE
#endif /* __PTHREAD_PRIO_NONE */
#ifdef __PTHREAD_PRIO_INHERIT
#define PTHREAD_PRIO_INHERIT PTHREAD_PRIO_INHERIT
#endif /* __PTHREAD_PRIO_INHERIT */
#ifdef __PTHREAD_PRIO_PROTECT
#define PTHREAD_PRIO_PROTECT PTHREAD_PRIO_PROTECT
#endif /* __PTHREAD_PRIO_PROTECT */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_PRIO_NONE
#define PTHREAD_PRIO_NONE    __PTHREAD_PRIO_NONE
#endif /* __PTHREAD_PRIO_NONE */
#ifdef __PTHREAD_PRIO_INHERIT
#define PTHREAD_PRIO_INHERIT __PTHREAD_PRIO_INHERIT
#endif /* __PTHREAD_PRIO_INHERIT */
#ifdef __PTHREAD_PRIO_PROTECT
#define PTHREAD_PRIO_PROTECT __PTHREAD_PRIO_PROTECT
#endif /* __PTHREAD_PRIO_PROTECT */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

/* Read-write lock types. */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#if (defined(__PTHREAD_RWLOCK_PREFER_READER) || defined(__PTHREAD_RWLOCK_PREFER_WRITER) || \
     defined(__PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE) || defined(__PTHREAD_RWLOCK_PREFER_READER))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_RWLOCK_PREFER_READER
	PTHREAD_RWLOCK_PREFER_READER_NP              = __PTHREAD_RWLOCK_PREFER_READER,
#endif /* __PTHREAD_RWLOCK_PREFER_READER */
#ifdef __PTHREAD_RWLOCK_PREFER_WRITER
	PTHREAD_RWLOCK_PREFER_WRITER_NP              = __PTHREAD_RWLOCK_PREFER_WRITER,
#endif /* __PTHREAD_RWLOCK_PREFER_WRITER */
#ifdef __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE
	PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP = __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE,
#endif /* __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE */
#ifdef __PTHREAD_RWLOCK_PREFER_READER
	PTHREAD_RWLOCK_DEFAULT_NP                    = __PTHREAD_RWLOCK_PREFER_READER,
#endif /* __PTHREAD_RWLOCK_PREFER_READER */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_RWLOCK_PREFER_READER
#define PTHREAD_RWLOCK_PREFER_READER_NP              PTHREAD_RWLOCK_PREFER_READER_NP
#endif /* __PTHREAD_RWLOCK_PREFER_READER */
#ifdef __PTHREAD_RWLOCK_PREFER_WRITER
#define PTHREAD_RWLOCK_PREFER_WRITER_NP              PTHREAD_RWLOCK_PREFER_WRITER_NP
#endif /* __PTHREAD_RWLOCK_PREFER_WRITER */
#ifdef __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE
#define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP
#endif /* __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE */
#ifdef __PTHREAD_RWLOCK_PREFER_READER
#define PTHREAD_RWLOCK_DEFAULT_NP                    PTHREAD_RWLOCK_DEFAULT_NP
#endif /* __PTHREAD_RWLOCK_PREFER_READER */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_RWLOCK_PREFER_READER
#define PTHREAD_RWLOCK_PREFER_READER_NP              __PTHREAD_RWLOCK_PREFER_READER
#endif /* __PTHREAD_RWLOCK_PREFER_READER */
#ifdef __PTHREAD_RWLOCK_PREFER_WRITER
#define PTHREAD_RWLOCK_PREFER_WRITER_NP              __PTHREAD_RWLOCK_PREFER_WRITER
#endif /* __PTHREAD_RWLOCK_PREFER_WRITER */
#ifdef __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE
#define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE
#endif /* __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE */
#ifdef __PTHREAD_RWLOCK_PREFER_READER
#define PTHREAD_RWLOCK_DEFAULT_NP                    __PTHREAD_RWLOCK_PREFER_READER
#endif /* __PTHREAD_RWLOCK_PREFER_READER */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

/* Scheduler inheritance. */
#if (defined(__PTHREAD_INHERIT_SCHED) || \
     defined(__PTHREAD_EXPLICIT_SCHED))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_INHERIT_SCHED
	PTHREAD_INHERIT_SCHED  = __PTHREAD_INHERIT_SCHED,
#endif /* __PTHREAD_INHERIT_SCHED */
#ifdef __PTHREAD_EXPLICIT_SCHED
	PTHREAD_EXPLICIT_SCHED = __PTHREAD_EXPLICIT_SCHED
#endif /* __PTHREAD_EXPLICIT_SCHED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_INHERIT_SCHED
#define PTHREAD_INHERIT_SCHED  PTHREAD_INHERIT_SCHED
#endif /* __PTHREAD_INHERIT_SCHED */
#ifdef __PTHREAD_EXPLICIT_SCHED
#define PTHREAD_EXPLICIT_SCHED PTHREAD_EXPLICIT_SCHED
#endif /* __PTHREAD_EXPLICIT_SCHED */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_INHERIT_SCHED
#define PTHREAD_INHERIT_SCHED  __PTHREAD_INHERIT_SCHED
#endif /* __PTHREAD_INHERIT_SCHED */
#ifdef __PTHREAD_EXPLICIT_SCHED
#define PTHREAD_EXPLICIT_SCHED __PTHREAD_EXPLICIT_SCHED
#endif /* __PTHREAD_EXPLICIT_SCHED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Scope handling. */
#if (defined(__PTHREAD_SCOPE_SYSTEM) || \
     defined(__PTHREAD_SCOPE_PROCESS))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_SCOPE_SYSTEM
	PTHREAD_SCOPE_SYSTEM  = __PTHREAD_SCOPE_SYSTEM,
#endif /* __PTHREAD_SCOPE_SYSTEM */
#ifdef __PTHREAD_SCOPE_PROCESS
	PTHREAD_SCOPE_PROCESS = __PTHREAD_SCOPE_PROCESS
#endif /* __PTHREAD_SCOPE_PROCESS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_SCOPE_SYSTEM
#define PTHREAD_SCOPE_SYSTEM  PTHREAD_SCOPE_SYSTEM
#endif /* __PTHREAD_SCOPE_SYSTEM */
#ifdef __PTHREAD_SCOPE_PROCESS
#define PTHREAD_SCOPE_PROCESS PTHREAD_SCOPE_PROCESS
#endif /* __PTHREAD_SCOPE_PROCESS */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_SCOPE_SYSTEM
#define PTHREAD_SCOPE_SYSTEM  __PTHREAD_SCOPE_SYSTEM
#endif /* __PTHREAD_SCOPE_SYSTEM */
#ifdef __PTHREAD_SCOPE_PROCESS
#define PTHREAD_SCOPE_PROCESS __PTHREAD_SCOPE_PROCESS
#endif /* __PTHREAD_SCOPE_PROCESS */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Process shared or private flag. */
#if (defined(__PTHREAD_PROCESS_PRIVATE) || \
     defined(__PTHREAD_PROCESS_SHARED))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_PROCESS_PRIVATE
	PTHREAD_PROCESS_PRIVATE = __PTHREAD_PROCESS_PRIVATE,
#endif /* __PTHREAD_PROCESS_PRIVATE */
#ifdef __PTHREAD_PROCESS_SHARED
	PTHREAD_PROCESS_SHARED  = __PTHREAD_PROCESS_SHARED
#endif /* __PTHREAD_PROCESS_SHARED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_PROCESS_PRIVATE
#define PTHREAD_PROCESS_PRIVATE PTHREAD_PROCESS_PRIVATE
#endif /* __PTHREAD_PROCESS_PRIVATE */
#ifdef __PTHREAD_PROCESS_SHARED
#define PTHREAD_PROCESS_SHARED  PTHREAD_PROCESS_SHARED
#endif /* __PTHREAD_PROCESS_SHARED */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_PROCESS_PRIVATE
#define PTHREAD_PROCESS_PRIVATE __PTHREAD_PROCESS_PRIVATE
#endif /* __PTHREAD_PROCESS_PRIVATE */
#ifdef __PTHREAD_PROCESS_SHARED
#define PTHREAD_PROCESS_SHARED  __PTHREAD_PROCESS_SHARED
#endif /* __PTHREAD_PROCESS_SHARED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Cancellation */
#if (defined(__PTHREAD_CANCEL_ENABLE) || \
     defined(__PTHREAD_CANCEL_DISABLE) || \
     defined(__PTHREAD_CANCEL_DEFERRED) || \
     defined(__PTHREAD_CANCEL_ASYNCHRONOUS))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __PTHREAD_CANCEL_ENABLE
	PTHREAD_CANCEL_ENABLE       = __PTHREAD_CANCEL_ENABLE,
#endif /* __PTHREAD_CANCEL_ENABLE */
#ifdef __PTHREAD_CANCEL_DISABLE
	PTHREAD_CANCEL_DISABLE      = __PTHREAD_CANCEL_DISABLE,
#endif /* __PTHREAD_CANCEL_DISABLE */
#ifdef __PTHREAD_CANCEL_DEFERRED
	PTHREAD_CANCEL_DEFERRED     = __PTHREAD_CANCEL_DEFERRED,
#endif /* __PTHREAD_CANCEL_DEFERRED */
#ifdef __PTHREAD_CANCEL_ASYNCHRONOUS
	PTHREAD_CANCEL_ASYNCHRONOUS = __PTHREAD_CANCEL_ASYNCHRONOUS
#endif /* __PTHREAD_CANCEL_ASYNCHRONOUS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTHREAD_CANCEL_ENABLE
#define PTHREAD_CANCEL_ENABLE       PTHREAD_CANCEL_ENABLE
#endif /* __PTHREAD_CANCEL_ENABLE */
#ifdef __PTHREAD_CANCEL_DISABLE
#define PTHREAD_CANCEL_DISABLE      PTHREAD_CANCEL_DISABLE
#endif /* __PTHREAD_CANCEL_DISABLE */
#ifdef __PTHREAD_CANCEL_DEFERRED
#define PTHREAD_CANCEL_DEFERRED     PTHREAD_CANCEL_DEFERRED
#endif /* __PTHREAD_CANCEL_DEFERRED */
#ifdef __PTHREAD_CANCEL_ASYNCHRONOUS
#define PTHREAD_CANCEL_ASYNCHRONOUS PTHREAD_CANCEL_ASYNCHRONOUS
#endif /* __PTHREAD_CANCEL_ASYNCHRONOUS */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTHREAD_CANCEL_ENABLE
#define PTHREAD_CANCEL_ENABLE       __PTHREAD_CANCEL_ENABLE
#endif /* __PTHREAD_CANCEL_ENABLE */
#ifdef __PTHREAD_CANCEL_DISABLE
#define PTHREAD_CANCEL_DISABLE      __PTHREAD_CANCEL_DISABLE
#endif /* __PTHREAD_CANCEL_DISABLE */
#ifdef __PTHREAD_CANCEL_DEFERRED
#define PTHREAD_CANCEL_DEFERRED     __PTHREAD_CANCEL_DEFERRED
#endif /* __PTHREAD_CANCEL_DEFERRED */
#ifdef __PTHREAD_CANCEL_ASYNCHRONOUS
#define PTHREAD_CANCEL_ASYNCHRONOUS __PTHREAD_CANCEL_ASYNCHRONOUS
#endif /* __PTHREAD_CANCEL_ASYNCHRONOUS */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#ifdef __PTHREAD_CANCELED
#define PTHREAD_CANCELED __PTHREAD_CANCELED
#endif /* __PTHREAD_CANCELED */

/* Single execution handling. */
#ifdef __PTHREAD_ONCE_INIT
#define PTHREAD_ONCE_INIT __PTHREAD_ONCE_INIT
#endif /* __PTHREAD_ONCE_INIT */

#ifdef __USE_XOPEN2K
/* Value returned by 'pthread_barrier_wait' for one of the threads
 * after the required number of threads have called this function.
 * -1 is distinct from 0 and all errno constants */
#ifdef __PTHREAD_BARRIER_SERIAL_THREAD
#define PTHREAD_BARRIER_SERIAL_THREAD __PTHREAD_BARRIER_SERIAL_THREAD
#endif /* __PTHREAD_BARRIER_SERIAL_THREAD */
#endif /* __USE_XOPEN2K */



#ifdef __CC__

#ifdef __PTHREAD_MUTEX_INITIALIZER
#define PTHREAD_MUTEX_INITIALIZER               __PTHREAD_MUTEX_INITIALIZER
#endif /* __PTHREAD_MUTEX_INITIALIZER */
#ifdef __USE_GNU
#ifdef __PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP  __PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#endif /* __PTHREAD_RECURSIVE_MUTEX_INITIALIZER */
#ifdef __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER
#endif /* __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER */
#ifdef __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER
#define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP   __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER
#endif /* __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER */
#endif /* __USE_GNU */

/* Read-write lock types. */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)

/* Read-write lock initializers. */
#ifdef __PTHREAD_RWLOCK_INITIALIZER
#define PTHREAD_RWLOCK_INITIALIZER __PTHREAD_RWLOCK_INITIALIZER
#endif /* __PTHREAD_RWLOCK_INITIALIZER */
#ifdef __USE_GNU
#ifdef __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER
#define PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER
#endif /* __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER */
#endif /* __USE_GNU */
#endif  /* __USE_UNIX98 || __USE_XOPEN2K */

/* Conditional variable handling. */
#ifdef __PTHREAD_COND_INITIALIZER
#define PTHREAD_COND_INITIALIZER __PTHREAD_COND_INITIALIZER
#endif /* __PTHREAD_COND_INITIALIZER */

/* Cleanup buffers */
struct _pthread_cleanup_buffer {
	void                          (*__routine)(void *); /* Function to call. */
	void                           *__arg;              /* Its argument. */
	int                             __canceltype;       /* Saved cancellation type. */
	struct _pthread_cleanup_buffer *__prev;             /* Chaining of cleanup functions. */
};

#ifndef ____pthread_start_routine_t_defined
#define ____pthread_start_routine_t_defined 1
typedef void *(__LIBKCALL *__pthread_start_routine_t)(void *);
#endif /* !____pthread_start_routine_t_defined */

typedef __pthread_t pthread_t;
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined 1
typedef __pthread_attr_t pthread_attr_t;
#endif /* !__pthread_attr_t_defined */
typedef __pthread_mutex_t pthread_mutex_t;
typedef __pthread_mutexattr_t pthread_mutexattr_t;
typedef __pthread_cond_t pthread_cond_t;
typedef __pthread_condattr_t pthread_condattr_t;
typedef __pthread_key_t pthread_key_t;
typedef __pthread_once_t pthread_once_t;
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
typedef __pthread_rwlock_t pthread_rwlock_t;
typedef __pthread_rwlockattr_t pthread_rwlockattr_t;
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_XOPEN2K
typedef __pthread_spinlock_t pthread_spinlock_t;
typedef __pthread_barrier_t pthread_barrier_t;
typedef __pthread_barrierattr_t pthread_barrierattr_t;
#endif /* __USE_XOPEN2K */


/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD
 * @return: EOK:    Success
 * @return: EAGAIN: Insufficient resources, or operation-not-permitted */
__CDECLARE_OPT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,pthread_create,(pthread_t *__restrict __newthread, pthread_attr_t const *__restrict __attr, __pthread_start_routine_t __start_routine, void *__restrict __arg),(__newthread,__attr,__start_routine,__arg))
/* Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CDECLARE_VOID_OPT(__ATTR_NORETURN,__THROWING,pthread_exit,(void *__retval),(__retval))
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL
 * @return: EOK: Success */
__CDECLARE_OPT(,__errno_t,__NOTHROW_RPC,pthread_join,(pthread_t __pthread, void **__thread_return),(__pthread,__thread_return))
#ifdef __USE_GNU
/* Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_tryjoin_np,(pthread_t __pthread, void **__thread_return),(__pthread,__thread_return))
struct timespec;
#if defined(__CRT_HAVE_pthread_timedjoin64_np) && defined(__USE_TIME_BITS64)
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(,__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __pthread, void **__thread_return, struct timespec const *__abstime),pthread_timedjoin64_np,(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np) && !defined(__USE_TIME_BITS64)
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(,__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __pthread, void **__thread_return, struct timespec const *__abstime),(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin64_np) || defined(__CRT_HAVE_pthread_timedjoin_np)
#include <local/pthread/pthread_timedjoin_np.h>
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_RPC(__LIBCCALL pthread_timedjoin_np)(pthread_t __pthread, void **__thread_return, struct timespec const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin_np))(__pthread, __thread_return, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_timedjoin64_np
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(,__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __pthread, void **__thread_return, struct timespec64 const *__abstime),(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(,__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __pthread, void **__thread_return, struct timespec64 const *__abstime),pthread_timedjoin_np,(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np)
#include <local/pthread/pthread_timedjoin64_np.h>
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin64_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_RPC(__LIBCCALL pthread_timedjoin64_np)(pthread_t __pthread, void **__thread_return, struct timespec64 const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin64_np))(__pthread, __thread_return, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it
 * @return: EOK: Success */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_detach,(pthread_t __pthread),(__pthread))
#ifdef __CRT_HAVE_pthread_self
/* Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CDECLARE(__ATTR_CONST,pthread_t,__NOTHROW_NCX,pthread_self,(void),())
#elif defined(__CRT_HAVE_thrd_current)
/* Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST,pthread_t,__NOTHROW_NCX,pthread_self,(void),thrd_current,())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_equal
/* Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
__CEIDECLARE(__ATTR_CONST,int,__NOTHROW_NCX,pthread_equal,(pthread_t __thr1, pthread_t __thr2),{ return __thr1 == __thr2; })
#elif defined(__CRT_HAVE_thrd_equal)
/* Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
__CEIREDIRECT(__ATTR_CONST,int,__NOTHROW_NCX,pthread_equal,(pthread_t __thr1, pthread_t __thr2),thrd_equal,{ return __thr1 == __thr2; })
#else /* ... */
/* Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
__LOCAL __ATTR_CONST int __NOTHROW_NCX(__LIBCCALL pthread_equal)(pthread_t __thr1, pthread_t __thr2) { return __thr1 == __thr2; }
#endif /* !... */

/* Thread attribute handling. */

/* Initialize thread attribute *ATTR with default attributes (detachstate is
 * PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack)
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_init,(pthread_attr_t *__attr),(__attr))
/* Destroy thread attribute *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_destroy,(pthread_attr_t *__attr),(__attr))
/* Get detach state attribute
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getdetachstate,(pthread_attr_t const *__attr, int *__detachstate),(__attr,__detachstate))
/* Set detach state attribute
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `detachstate' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setdetachstate,(pthread_attr_t *__attr, int __detachstate),(__attr,__detachstate))
/* Get the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getguardsize,(pthread_attr_t const *__attr, size_t *__guardsize),(__attr,__guardsize))
/* Set the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setguardsize,(pthread_attr_t *__attr, size_t __guardsize),(__attr,__guardsize))
/* Return in *PARAM the scheduling parameters of *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getschedparam,(pthread_attr_t const *__restrict __attr, struct sched_param *__restrict __param),(__attr,__param))
/* Set scheduling parameters (priority, etc) in *ATTR according to PARAM
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `param' */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_setschedparam,(pthread_attr_t *__restrict __attr, struct sched_param const *__restrict __param),(__attr,__param))
/* Return in *POLICY the scheduling policy of *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getschedpolicy,(pthread_attr_t const *__restrict __attr, int *__restrict __policy),(__attr,__policy))
/* Set scheduling policy in *ATTR according to POLICY
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `policy' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setschedpolicy,(pthread_attr_t *__attr, int __policy),(__attr,__policy))
/* Return in *INHERIT the scheduling inheritance mode of *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getinheritsched,(pthread_attr_t const *__restrict __attr, int *__restrict __inherit),(__attr,__inherit))
/* Set scheduling inheritance mode in *ATTR according to INHERIT
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `inherit' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setinheritsched,(pthread_attr_t *__attr, int __inherit),(__attr,__inherit))
/* Return in *SCOPE the scheduling contention scope of *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getscope,(pthread_attr_t const *__restrict __attr, int *__restrict __scope),(__attr,__scope))
/* Set scheduling contention scope in *ATTR according to SCOPE
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `scope' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setscope,(pthread_attr_t *__attr, int __scope),(__attr,__scope))
/* Return the previously set address for the stack
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use pthread_attr_getstack()") __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getstackaddr,(pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr),(__attr,__stackaddr))
/* Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use pthread_attr_setstack()") __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setstackaddr,(pthread_attr_t *__attr, void *__stackaddr),(__attr,__stackaddr))
/* Return the currently used minimal stack size
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_attr_getstacksize,(pthread_attr_t const *__restrict __attr, size_t *__restrict __stacksize),(__attr,__stacksize))
/* Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setstacksize,(pthread_attr_t *__attr, size_t __stacksize),(__attr,__stacksize))
#ifdef __USE_XOPEN2K
/* Return the previously set address for the stack
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,pthread_attr_getstack,(pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr, size_t *__restrict __stacksize),(__attr,__stackaddr,__stacksize))
/* The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_attr_setstack,(pthread_attr_t *__attr, void *__stackaddr, size_t __stacksize),(__attr,__stackaddr,__stacksize))
#endif /* __USE_XOPEN2K */
#ifdef __USE_GNU
/* Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existant CPU
 * @return: ENOMEM: Insufficient memory */
__CDECLARE_OPT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,pthread_attr_setaffinity_np,(pthread_attr_t *__attr, size_t __cpusetsize, cpu_set_t const *__cpuset),(__attr,__cpusetsize,__cpuset))
/* Get bit set in CPUSET representing the processors threads created with ATTR can run on
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
__CDECLARE_OPT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,pthread_attr_getaffinity_np,(pthread_attr_t const *__attr, size_t __cpusetsize, cpu_set_t *__cpuset),(__attr,__cpusetsize,__cpuset))
/* Get the default attributes used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_getattr_default_np,(pthread_attr_t *__attr),(__attr))
/* Set the default attributes to be used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_setattr_default_np,(pthread_attr_t const *__attr),(__attr))
/* Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,pthread_getattr_np,(pthread_t __pthread, pthread_attr_t *__attr),(__pthread,__attr))
#endif /* __USE_GNU */

/* Functions for scheduling control. */

/* Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `policy' and `param'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy' */
__CDECLARE_OPT(__ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,pthread_setschedparam,(pthread_t __target_thread, int __policy, struct sched_param const *__param),(__target_thread,__policy,__param))
/* Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3)),__errno_t,__NOTHROW_NCX,pthread_getschedparam,(pthread_t __target_thread, int *__restrict __policy, struct sched_param *__restrict __param),(__target_thread,__policy,__param))
/* Set the scheduling priority for TARGET_THREAD
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `prio'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `prio' */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_setschedprio,(pthread_t __target_thread, int __prio),(__target_thread,__prio))
#ifdef __USE_GNU
/* Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,pthread_getname_np,(pthread_t __target_thread, char *__buf, size_t __buflen),(__target_thread,__buf,__buflen))
/* Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,pthread_setname_np,(pthread_t __target_thread, const char *__name),(__target_thread,__name))
#endif /* __USE_GNU */
#ifdef __USE_KOS
#ifndef __pthread_gettid_np_defined
#define __pthread_gettid_np_defined 1
#ifdef __CRT_HAVE_pthread_gettid_np
/* Return the TID of the given `target_thread'.
 * If the given `target_thread' has already terminated, 0 is returned
 * @return: * : The PID OF the given thread
 * @return: 0 : The given `target_thread' has already terminated */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,pthread_gettid_np,(pthread_t __target_thread),(__target_thread))
#else /* __CRT_HAVE_pthread_gettid_np */
#undef __pthread_gettid_np_defined
#endif /* !__CRT_HAVE_pthread_gettid_np */
#endif /* !__pthread_gettid_np_defined */
#endif /* __USE_KOS */
#ifdef __USE_UNIX98
/* Determine level of concurrency
 * @return: * : The current concurrency level */
__CDECLARE_OPT(__ATTR_PURE,int,__NOTHROW_NCX,pthread_getconcurrency,(void),())
/* Set new concurrency level to LEVEL
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_setconcurrency,(int __level),(__level))
#endif /* __USE_UNIX98 */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sched_yield
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),sched_yield,())
#elif defined(__CRT_HAVE_thrd_yield)
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),thrd_yield,())
#elif defined(__CRT_HAVE_pthread_yield)
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),())
#elif defined(__CRT_HAVE___sched_yield)
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_yield,(void),yield,())
#endif /* ... */
/* Limit specified thread THREAD to run only on the processors represented in CPUSET
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
__CDECLARE_OPT(__ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,pthread_setaffinity_np,(pthread_t __pthread, size_t __cpusetsize, cpu_set_t const *__cpuset),(__pthread,__cpusetsize,__cpuset))
/* Get bit set in CPUSET representing the processors THREAD can run on
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
__CDECLARE_OPT(__ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,pthread_getaffinity_np,(pthread_t __pthread, size_t __cpusetsize, cpu_set_t *__cpuset),(__pthread,__cpusetsize,__cpuset))
#endif /* __USE_GNU */

#ifndef ____pthread_once_routine_t_defined
#define ____pthread_once_routine_t_defined 1
typedef void (__LIBKCALL *__pthread_once_routine_t)(void);
#endif /* !____pthread_once_routine_t_defined */

/* Functions for handling initialization. */

#ifdef __CRT_HAVE_pthread_once
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT.
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1, 2)),__errno_t,__THROWING,pthread_once,(pthread_once_t *__once_control, __pthread_once_routine_t __init_routine),(__once_control,__init_routine))
#elif defined(__CRT_HAVE_call_once)
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT.
 * @return: EOK: Success */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__THROWING,pthread_once,(pthread_once_t *__once_control, __pthread_once_routine_t __init_routine),call_once,(__once_control,__init_routine))
#else /* ... */
#include <local/pthread/pthread_once.h>
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT.
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_once, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __errno_t (__LIBCCALL pthread_once)(pthread_once_t *__once_control, __pthread_once_routine_t __init_routine) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_once))(__once_control, __init_routine); })
#endif /* !... */

/* Functions for handling cancellation.
 * Note that these functions are explicitly not marked to not throw an
 * exception in C++ code. If cancellation is implemented by unwinding
 * this is necessary to have the compiler generate the unwind information. */
/* Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `state' */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_setcancelstate,(int __state, int *__oldstate),(__state,__oldstate))
#ifndef __pthread_setcanceltype_defined
#define __pthread_setcanceltype_defined 1
#ifdef __CRT_HAVE_pthread_setcanceltype
/* Set cancellation state of current thread to TYPE,
 * returning the old type in *OLDTYPE if OLDTYPE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `type' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_setcanceltype,(int __type, int *__oldtype),(__type,__oldtype))
#else /* __CRT_HAVE_pthread_setcanceltype */
#undef __pthread_setcanceltype_defined
#endif /* !__CRT_HAVE_pthread_setcanceltype */
#endif /* !__pthread_setcanceltype_defined */
/* Cancel THREAD immediately or at the next possibility
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_cancel,(pthread_t __pthread),(__pthread))
/* Test for pending cancellation for the current thread and terminate
 * the thread as per pthread_exit(PTHREAD_CANCELED) if it has been canceled */
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
#ifdef __cplusplus
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

/* Install a cleanup handler: ROUTINE will be called with arguments ARG
 * when the thread is canceled or calls pthread_exit. ROUTINE will also
 * be called with arguments ARG when the matching pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used in matching pairs at the same nesting level of braces. */
#define pthread_cleanup_push(routine, arg) \
	do {                                   \
		__pthread_cleanup_class __clframe(routine, arg)

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If EXECUTE is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)  \
		__clframe.__setdoit(execute); \
	} __WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)      \
	do {                                                 \
		__pthread_cleanup_class __clframe(routine, arg); \
		__clframe.__defer()

/* Remove a cleanup handler as pthread_cleanup_pop does, but also
 * restores the cancellation type that was in effect when the matching
 * pthread_cleanup_push_defer was called. */
#define pthread_cleanup_pop_restore_np(execute) \
		__clframe.__restore();                  \
		__clframe.__setdoit(execute);           \
	} __WHILE0
#endif /* __USE_GNU */
#else /* __cplusplus */
#ifdef __CRT_HAVE___pthread_cleanup_routine
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_cleanup_routine,(struct __pthread_cleanup_frame *__frame),(__frame))
#else /* __CRT_HAVE___pthread_cleanup_routine */
#include <local/pthread/__pthread_cleanup_routine.h>
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
__NAMESPACE_LOCAL_USING_OR_IMPL(__pthread_cleanup_routine, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL __pthread_cleanup_routine)(struct __pthread_cleanup_frame *__frame) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__pthread_cleanup_routine))(__frame); })
#endif /* !__CRT_HAVE___pthread_cleanup_routine */
/* Install a cleanup handler: ROUTINE will be called with arguments ARG
 * when the thread is canceled or calls pthread_exit. ROUTINE will also
 * be called with arguments ARG when the matching pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used in matching pairs at the same nesting level of braces. */
#define pthread_cleanup_push(routine, arg)                          \
	do {                                                            \
		struct __pthread_cleanup_frame __clframe                    \
		__attribute__((__cleanup__(__pthread_cleanup_routine))) = { \
			.__cancel_routine = (routine),                          \
			.__cancel_arg = (arg),                                  \
			.__do_it = 1                                            \
		};

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If EXECUTE is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)   \
		__clframe.__do_it = (execute); \
	} __WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the current cancellation type and sets it to deferred
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

/* Remove a cleanup handler as pthread_cleanup_pop does, but also
 * restores the cancellation type that was in effect when the matching
 * pthread_cleanup_push_defer was called. */
#define pthread_cleanup_pop_restore_np(execute)                     \
		(void)pthread_setcanceltype(__clframe.__cancel_type, NULL); \
		__clframe.__do_it = (execute);                              \
	} __WHILE0

#endif /* __USE_GNU */
#endif /* !__cplusplus */
#else /* __GNUC__ && __EXCEPTIONS */
/* Install a cleanup handler: ROUTINE will be called with arguments ARG
 * when the thread is canceled or calls pthread_exit. ROUTINE will also
 * be called with arguments ARG when the matching pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used in matching pairs at the same nesting level of braces. */
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
/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If EXECUTE is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)                                           \
			do {                                                               \
			} __WHILE0; /* Empty to allow label before pthread_cleanup_pop. */ \
		} __WHILE0;                                                            \
		__pthread_unregister_cancel(&__cancel_buf);                            \
		if (execute)                                                           \
			(*__cancel_routine)(__cancel_arg);                                 \
	} __WHILE0
__CDECLARE_VOID_OPT(__cleanup_fct_attribute __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_unregister_cancel,(__pthread_unwind_buf_t *__buf),(__buf))
#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)                                                           \
	do {                                                                                                      \
		__pthread_unwind_buf_t __cancel_buf;                                                                  \
		void (__LIBKCALL *__cancel_routine)(void *) = (routine);                                              \
		void *__cancel_arg               = (arg);                                                             \
		int __not_first_call = __sigsetjmp((struct __jmp_buf_tag *)(void *)__cancel_buf.__cancel_jmp_buf, 0); \
		if __unlikely(__not_first_call) {                                                                     \
			__cancel_routine(__cancel_arg);                                                                   \
			__pthread_unwind_next(&__cancel_buf);                                                             \
			__builtin_unreachable();                                                                          \
		}                                                                                                     \
		__pthread_register_cancel_defer(&__cancel_buf);                                                       \
		do {
__CDECLARE_VOID_OPT(__cleanup_fct_attribute __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_register_cancel_defer,(__pthread_unwind_buf_t *__buf),(__buf))
/* Remove a cleanup handler as pthread_cleanup_pop does, but also
 * restores the cancellation type that was in effect when the matching
 * pthread_cleanup_push_defer was called. */
#define pthread_cleanup_pop_restore_np(execute)                                \
			do {                                                               \
			} __WHILE0; /* Empty to allow label before pthread_cleanup_pop. */ \
		} __WHILE0;                                                            \
		__pthread_unregister_cancel_restore(&__cancel_buf);                    \
		if (execute)                                                           \
			(*__cancel_routine)(__cancel_arg);                                 \
	} __WHILE0
__CDECLARE_VOID_OPT(__cleanup_fct_attribute __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_unregister_cancel_restore,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* __USE_GNU */
/* Internal interface to initiate cleanup */
__CDECLARE_VOID_OPT(__ATTR_WEAK __cleanup_fct_attribute __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_unwind_next,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* !__GNUC__ || !__EXCEPTIONS */

/* Function used in the macros. */
struct __jmp_buf_tag;
#ifdef __CRT_HAVE___sigsetjmp
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigsetjmp,(struct __jmp_buf_tag *__env, int __savemask),(__env,__savemask))
#elif defined(__CRT_HAVE_sigsetjmp)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigsetjmp,(struct __jmp_buf_tag *__env, int __savemask),sigsetjmp,(__env,__savemask))
#endif /* ... */

/* Mutex handling. */

/* Initialize a mutex
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_init,(pthread_mutex_t *__mutex, pthread_mutexattr_t const *__mutexattr),(__mutex,__mutexattr))
#ifdef __CRT_HAVE_pthread_mutex_destroy
/* Destroy a mutex
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_destroy,(pthread_mutex_t *__mutex),(__mutex))
#elif defined(__CRT_HAVE_mtx_destroy)
/* Destroy a mutex
 * @return: EOK: Success */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_destroy,(pthread_mutex_t *__mutex),mtx_destroy,(__mutex))
#endif /* ... */
/* Try locking a mutex
 * @return: EOK:   Success
 * @return: EBUSY: The mutex has already been locked
 *                 In case of a recursive mutex, another
 *                 thread was the one to acquire the lock. */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_trylock,(pthread_mutex_t *__mutex),(__mutex))
/* Lock a mutex
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_RPC,pthread_mutex_lock,(pthread_mutex_t *__mutex),(__mutex))
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_mutex_timedlock64) && defined(__USE_TIME_BITS64)
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock,(pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_mutex_timedlock64,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock) && !defined(__USE_TIME_BITS64)
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock,(pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock64) || defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <local/pthread/pthread_mutex_timedlock.h>
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_timedlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_mutex_timedlock)(pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_timedlock))(__mutex, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_mutex_timedlock64
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock64,(pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_mutex_timedlock64,(pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),pthread_mutex_timedlock,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <local/pthread/pthread_mutex_timedlock64.h>
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_timedlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_mutex_timedlock64)(pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_timedlock64))(__mutex, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */
/* Unlock a mutex
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_unlock,(pthread_mutex_t *__mutex),(__mutex))
/* Get the priority ceiling of MUTEX
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutex_getprioceiling,(pthread_mutex_t const *__restrict __mutex, int *__restrict __prioceiling),(__mutex,__prioceiling))
/* Set the priority ceiling of MUTEX to PRIOCEILING,
 * return old priority ceiling value in *OLD_CEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_setprioceiling,(pthread_mutex_t *__restrict __mutex, int __prioceiling, int *__restrict __old_ceiling),(__mutex,__prioceiling,__old_ceiling))
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_pthread_mutex_consistent
/* Declare the state protected by MUTEX as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent,(pthread_mutex_t *__mutex),(__mutex))
#elif defined(__CRT_HAVE_pthread_mutex_consistent_np)
/* Declare the state protected by MUTEX as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent,(pthread_mutex_t *__mutex),pthread_mutex_consistent_np,(__mutex))
#endif /* ... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_mutex_consistent
/* Declare the state protected by MUTEX as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent_np,(pthread_mutex_t *__mutex),pthread_mutex_consistent,(__mutex))
#elif defined(__CRT_HAVE_pthread_mutex_consistent_np)
/* Declare the state protected by MUTEX as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutex_consistent_np,(pthread_mutex_t *__mutex),(__mutex))
#endif /* ... */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K8 */

/* Functions for handling mutex attributes. */
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP)
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_init,(pthread_mutexattr_t *__attr),(__attr))
/* Destroy mutex attribute object ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_destroy,(pthread_mutexattr_t *__attr),(__attr))
/* Get the process-shared flag of the mutex attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getpshared,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
/* Set the process-shared flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setpshared,(pthread_mutexattr_t *__attr, int __pshared),(__attr,__pshared))
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
/* Return in *KIND the mutex kind attribute in *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_gettype,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __kind),(__attr,__kind))
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_settype,(pthread_mutexattr_t *__attr, int __kind),(__attr,__kind))
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
/* Return in *PROTOCOL the mutex protocol attribute in *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getprotocol,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __protocol),(__attr,__protocol))
/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `protocol' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setprotocol,(pthread_mutexattr_t *__attr, int __protocol),(__attr,__protocol))
/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getprioceiling,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __prioceiling),(__attr,__prioceiling))
/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setprioceiling,(pthread_mutexattr_t *__attr, int __prioceiling),(__attr,__prioceiling))
#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pthread_mutexattr_getrobust
/* Get the robustness flag of the mutex attribute ATTR
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust,(pthread_mutexattr_t const *__attr, int *__robustness),(__attr,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_getrobust_np)
/* Get the robustness flag of the mutex attribute ATTR
 * @return: EOK: Success */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust,(pthread_mutexattr_t const *__attr, int *__robustness),pthread_mutexattr_getrobust_np,(__attr,__robustness))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_setrobust
/* Set the robustness flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust,(pthread_mutexattr_t *__attr, int __robustness),(__attr,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_setrobust_np)
/* Set the robustness flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust,(pthread_mutexattr_t *__attr, int __robustness),pthread_mutexattr_setrobust_np,(__attr,__robustness))
#endif /* ... */
#endif /* __USE_XOPEN2K */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_mutexattr_getrobust
/* Get the robustness flag of the mutex attribute ATTR
 * @return: EOK: Success */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust_np,(pthread_mutexattr_t const *__attr, int *__robustness),pthread_mutexattr_getrobust,(__attr,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_getrobust_np)
/* Get the robustness flag of the mutex attribute ATTR
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getrobust_np,(pthread_mutexattr_t const *__attr, int *__robustness),(__attr,__robustness))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_setrobust
/* Set the robustness flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust_np,(pthread_mutexattr_t *__attr, int __robustness),pthread_mutexattr_setrobust,(__attr,__robustness))
#elif defined(__CRT_HAVE_pthread_mutexattr_setrobust_np)
/* Set the robustness flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setrobust_np,(pthread_mutexattr_t *__attr, int __robustness),(__attr,__robustness))
#endif /* ... */
#endif /* __USE_GNU */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
/* Functions for handling read-write locks. */
/* Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlock_init,(pthread_rwlock_t *__restrict __rwlock, pthread_rwlockattr_t const *__restrict __attr),(__rwlock,__attr))
/* Destroy read-write lock RWLOCK
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlock_destroy,(pthread_rwlock_t *__rwlock),(__rwlock))
/* Acquire read lock for RWLOCK
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_RPC,pthread_rwlock_rdlock,(pthread_rwlock_t *__rwlock),(__rwlock))
/* Try to acquire read lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A read-lock cannot be acquired at the moment,
 *                 because a write-lock is already being held. */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlock_tryrdlock,(pthread_rwlock_t *__rwlock),(__rwlock))
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_rwlock_timedrdlock64) && defined(__USE_TIME_BITS64)
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),pthread_rwlock_timedrdlock64,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock) && !defined(__USE_TIME_BITS64)
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock64) || defined(__CRT_HAVE_pthread_rwlock_timedrdlock)
#include <local/pthread/pthread_rwlock_timedrdlock.h>
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedrdlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedrdlock))(__rwlock, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_rwlock_timedrdlock64
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedrdlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),pthread_rwlock_timedrdlock,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock)
#include <local/pthread/pthread_rwlock_timedrdlock64.h>
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedrdlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedrdlock64))(__rwlock, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */
/* Acquire write lock for RWLOCK
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_RPC,pthread_rwlock_wrlock,(pthread_rwlock_t *__rwlock),(__rwlock))
/* Try to acquire write lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks are already being held. */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlock_trywrlock,(pthread_rwlock_t *__rwlock),(__rwlock))
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_rwlock_timedwrlock64) && defined(__USE_TIME_BITS64)
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),pthread_rwlock_timedwrlock64,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock) && !defined(__USE_TIME_BITS64)
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock64) || defined(__CRT_HAVE_pthread_rwlock_timedwrlock)
#include <local/pthread/pthread_rwlock_timedwrlock.h>
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedwrlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock))(__rwlock, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_rwlock_timedwrlock64
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_rwlock_timedwrlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),pthread_rwlock_timedwrlock,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock)
#include <local/pthread/pthread_rwlock_timedwrlock64.h>
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedwrlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock64))(__rwlock, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */
/* Unlock RWLOCK
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlock_unlock,(pthread_rwlock_t *__rwlock),(__rwlock))

/* Functions for handling read-write lock attributes. */
/* Initialize attribute object ATTR with default values
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_init,(pthread_rwlockattr_t *__attr),(__attr))
/* Destroy attribute object ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_destroy,(pthread_rwlockattr_t *__attr),(__attr))
/* Return current setting of process-shared attribute of ATTR in PSHARED
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_getpshared,(pthread_rwlockattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
/* Set process-shared attribute of ATTR to PSHARED
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pthread' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_setpshared,(pthread_rwlockattr_t *__attr, int __pshared),(__attr,__pshared))
/* Return current setting of reader/writer preference
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_getkind_np,(pthread_rwlockattr_t const *__restrict __attr, int *__restrict __pref),(__attr,__pref))
/* Set reader/write preference
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pref' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_rwlockattr_setkind_np,(pthread_rwlockattr_t *__attr, int __pref),(__attr,__pref))
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

/* Functions for handling conditional variables. */
/* Initialize condition variable COND using attributes
 * ATTR, or use the default values if later is NULL
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_cond_init,(pthread_cond_t *__restrict __cond, pthread_condattr_t const *__restrict __cond_attr),(__cond,__cond_attr))
#ifdef __CRT_HAVE_pthread_cond_destroy
/* Destroy condition variable COND
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_cond_destroy,(pthread_cond_t *__cond),(__cond))
#elif defined(__CRT_HAVE_cnd_destroy)
/* Destroy condition variable COND
 * @return: EOK: Success */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_cond_destroy,(pthread_cond_t *__cond),cnd_destroy,(__cond))
#endif /* ... */
/* Wake up one thread waiting for condition variable COND
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_cond_signal,(pthread_cond_t *__cond),(__cond))
/* Wake up all threads waiting for condition variables COND
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_cond_broadcast,(pthread_cond_t *__cond),(__cond))
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before.
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,pthread_cond_wait,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex),(__cond,__mutex))
#if defined(__CRT_HAVE_pthread_cond_timedwait64) && defined(__USE_TIME_BITS64)
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_cond_timedwait64,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait) && !defined(__USE_TIME_BITS64)
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64) || defined(__CRT_HAVE_pthread_cond_timedwait)
#include <local/pthread/pthread_cond_timedwait.h>
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_timedwait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_cond_timedwait)(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_timedwait))(__cond, __mutex, __abstime); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_cond_timedwait64
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait64,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,pthread_cond_timedwait64,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait)
#include <local/pthread/pthread_cond_timedwait64.h>
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_timedwait64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_cond_timedwait64)(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_timedwait64))(__cond, __mutex, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */

/* Functions for handling condition variable attributes. */
/* Initialize condition variable attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_condattr_init,(pthread_condattr_t *__attr),(__attr))
/* Destroy condition variable attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_condattr_destroy,(pthread_condattr_t *__attr),(__attr))
/* Get the process-shared flag of the condition variable attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_condattr_getpshared,(pthread_condattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
/* Set the process-shared flag of the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_condattr_setpshared,(pthread_condattr_t *__attr, int __pshared),(__attr,__pshared))
#ifdef __USE_XOPEN2K
/* Get the clock selected for the condition variable attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_condattr_getclock,(pthread_condattr_t const *__restrict __attr, __clockid_t *__restrict __clock_id),(__attr,__clock_id))
/* Set the clock selected for the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `clock_id' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_condattr_setclock,(pthread_condattr_t *__attr, __clockid_t __clock_id),(__attr,__clock_id))
#endif /* __USE_XOPEN2K */

#ifdef __USE_XOPEN2K
/* Functions to handle spinlocks. */
#ifdef __CRT_HAVE_pthread_spin_init
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_spin_init,(pthread_spinlock_t *__lock, int __pshared),(__lock,__pshared))
#else /* __CRT_HAVE_pthread_spin_init */
#include <local/pthread/pthread_spin_init.h>
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_init)(pthread_spinlock_t *__lock, int __pshared) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_init))(__lock, __pshared); })
#endif /* !__CRT_HAVE_pthread_spin_init */
#ifdef __CRT_HAVE_pthread_spin_destroy
/* Destroy the spinlock LOCK
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_spin_destroy,(pthread_spinlock_t *__lock),(__lock))
#else /* __CRT_HAVE_pthread_spin_destroy */
#include <local/pthread/pthread_spin_destroy.h>
/* Destroy the spinlock LOCK
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_destroy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_destroy)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_destroy))(__lock); })
#endif /* !__CRT_HAVE_pthread_spin_destroy */
#ifdef __CRT_HAVE_pthread_spin_lock
/* Wait until spinlock LOCK is retrieved
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_spin_lock,(pthread_spinlock_t *__lock),(__lock))
#else /* __CRT_HAVE_pthread_spin_lock */
#include <local/pthread/pthread_spin_lock.h>
/* Wait until spinlock LOCK is retrieved
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_lock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_lock)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_lock))(__lock); })
#endif /* !__CRT_HAVE_pthread_spin_lock */
#ifdef __CRT_HAVE_pthread_spin_trylock
/* Try to lock spinlock LOCK
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_spin_trylock,(pthread_spinlock_t *__lock),(__lock))
#else /* __CRT_HAVE_pthread_spin_trylock */
#include <local/pthread/pthread_spin_trylock.h>
/* Try to lock spinlock LOCK
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_trylock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_trylock)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_trylock))(__lock); })
#endif /* !__CRT_HAVE_pthread_spin_trylock */
#ifdef __CRT_HAVE_pthread_spin_unlock
/* Release spinlock LOCK
 * @return: EOK: Success */
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_spin_unlock,(pthread_spinlock_t *__lock),(__lock))
#else /* __CRT_HAVE_pthread_spin_unlock */
#include <local/pthread/pthread_spin_unlock.h>
/* Release spinlock LOCK
 * @return: EOK: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_unlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_spin_unlock)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_unlock))(__lock); })
#endif /* !__CRT_HAVE_pthread_spin_unlock */

/* Functions to handle barriers. */
/* Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_barrier_init,(pthread_barrier_t *__restrict __barrier, pthread_barrierattr_t const *__restrict __attr, unsigned int __count),(__barrier,__attr,__count))
/* Destroy a previously dynamically initialized barrier BARRIER
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_barrier_destroy,(pthread_barrier_t *__barrier),(__barrier))
/* Wait on barrier BARRIER
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_RPC,pthread_barrier_wait,(pthread_barrier_t *__barrier),(__barrier))
/* Initialize barrier attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_barrierattr_init,(pthread_barrierattr_t *__attr),(__attr))
/* Destroy previously dynamically initialized barrier attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_barrierattr_destroy,(pthread_barrierattr_t *__attr),(__attr))
/* Get the process-shared flag of the barrier attribute ATTR
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,pthread_barrierattr_getpshared,(pthread_barrierattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
/* Set the process-shared flag of the barrier attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_barrierattr_setpshared,(pthread_barrierattr_t *__attr, int __pshared),(__attr,__pshared))
#endif /* __USE_XOPEN2K */

/* Functions for handling thread-specific data. */
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CDECLARE_OPT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_key_create,(pthread_key_t *__key, __pthread_destr_function_t __destr_function),(__key,__destr_function))
#ifdef __CRT_HAVE_pthread_key_delete
/* Destroy KEY
 * @return: EOK: Success */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_key_delete,(pthread_key_t __key),(__key))
#elif defined(__CRT_HAVE_tss_delete)
/* Destroy KEY
 * @return: EOK: Success */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_key_delete,(pthread_key_t __key),tss_delete,(__key))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_getspecific
/* Return current value of the thread-specific data slot identified by KEY
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL', or no value has been bound, yet */
__CDECLARE(__ATTR_WUNUSED,void *,__NOTHROW_NCX,pthread_getspecific,(pthread_key_t __key),(__key))
#elif defined(__CRT_HAVE_tss_get)
/* Return current value of the thread-specific data slot identified by KEY
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL', or no value has been bound, yet */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,pthread_getspecific,(pthread_key_t __key),tss_get,(__key))
#endif /* ... */
/* Store POINTER in the thread-specific data slot identified by KEY
 * @return: EOK:    Success
 * @return: ENOMEM: `pointer' is non-NULL, `key' had yet to be allowed for the
 *                  calling thread, and an attempt to allocate it just now failed */
__CDECLARE_OPT(,__errno_t,__NOTHROW_NCX,pthread_setspecific,(pthread_key_t __key, void const *__pointer),(__key,__pointer))
#ifdef __USE_XOPEN2K
/* Get ID of CPU-time clock for thread THREAD_ID
 * @return: EOK: Success */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,pthread_getcpuclockid,(pthread_t __pthread_id, __clockid_t *__clock_id),(__pthread_id,__clock_id))
#endif /* __USE_XOPEN2K */

#ifndef ____pthread_atfork_func_t_defined
#define ____pthread_atfork_func_t_defined 1
typedef void (__LIBKCALL *__pthread_atfork_func_t)(void);
#endif /* !____pthread_atfork_func_t_defined */
#ifndef __pthread_atfork_defined
#define __pthread_atfork_defined 1
#ifdef __CRT_HAVE_pthread_atfork
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_atfork,(__pthread_atfork_func_t __prepare, __pthread_atfork_func_t __parent, __pthread_atfork_func_t __child),(__prepare,__parent,__child))
#else /* __CRT_HAVE_pthread_atfork */
#undef __pthread_atfork_defined
#endif /* !__CRT_HAVE_pthread_atfork */
#endif /* !__pthread_atfork_defined */


/* Some more functions from winpthread. */
#ifdef __CRT_HAVE_pthread_num_processors_np
/* @return: * : The number of cpus that the calling thread is able to run on */
__CDECLARE(,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,pthread_num_processors_np,(void),())
#elif defined(__CRT_HAVE_sched_getaffinity)
#include <local/pthread/pthread_num_processors_np.h>
/* @return: * : The number of cpus that the calling thread is able to run on */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_num_processors_np, __FORCELOCAL __ATTR_ARTIFICIAL __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL pthread_num_processors_np)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_num_processors_np))(); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_set_num_processors_np
/* Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_set_num_processors_np,(int __n),(__n))
#elif defined(__CRT_HAVE_sched_setaffinity)
#include <local/pthread/pthread_set_num_processors_np.h>
/* Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_set_num_processors_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL pthread_set_num_processors_np)(int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_set_num_processors_np))(__n); })
#endif /* ... */
#ifdef __USE_BSD
#ifdef __CRT_HAVE_pthread_main_np
/* Returns 1 if the calling thread is the main() thread (i.e. the
 * thread that was started by the kernel in order to execute the
 * calling program), and 0 otherwise. Additionally, -1 is returned
 * if the calling thread "hasn't been initialized", though this
 * isn't a case that can actually happen under KOS's implementation. */
__CDECLARE(__ATTR_CONST,int,__NOTHROW_NCX,pthread_main_np,(void),())
#elif defined(__CRT_HAVE_thr_main)
/* Returns 1 if the calling thread is the main() thread (i.e. the
 * thread that was started by the kernel in order to execute the
 * calling program), and 0 otherwise. Additionally, -1 is returned
 * if the calling thread "hasn't been initialized", though this
 * isn't a case that can actually happen under KOS's implementation. */
__CREDIRECT(__ATTR_CONST,int,__NOTHROW_NCX,pthread_main_np,(void),thr_main,())
#elif defined(__CRT_HAVE_gettid) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid))
#include <local/pthread/pthread_main_np.h>
/* Returns 1 if the calling thread is the main() thread (i.e. the
 * thread that was started by the kernel in order to execute the
 * calling program), and 0 otherwise. Additionally, -1 is returned
 * if the calling thread "hasn't been initialized", though this
 * isn't a case that can actually happen under KOS's implementation. */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_main_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST int __NOTHROW_NCX(__LIBCCALL pthread_main_np)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_main_np))(); })
#endif /* ... */
#endif /* __USE_BSD */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PTHREAD_H */
