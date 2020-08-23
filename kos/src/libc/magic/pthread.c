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

%[default:section(".text.crt{|.dos}.sched.pthread")]
%[define_replacement(clockid_t = __clockid_t)]
%[define_replacement(pthread_t = __pthread_t)]
%[define_replacement(pthread_attr_t = __pthread_attr_t)]
%[define_replacement(pthread_mutex_t = __pthread_mutex_t)]
%[define_replacement(pthread_mutexattr_t = __pthread_mutexattr_t)]
%[define_replacement(pthread_cond_t = __pthread_cond_t)]
%[define_replacement(pthread_condattr_t = __pthread_condattr_t)]
%[define_replacement(pthread_key_t = __pthread_key_t)]
%[define_replacement(pthread_once_t = __pthread_once_t)]
%[define_replacement(pthread_rwlock_t = __pthread_rwlock_t)]
%[define_replacement(pthread_rwlockattr_t = __pthread_rwlockattr_t)]
%[define_replacement(pthread_spinlock_t = __pthread_spinlock_t)]
%[define_replacement(pthread_barrier_t = __pthread_barrier_t)]
%[define_replacement(pthread_barrierattr_t = __pthread_barrierattr_t)]
%[define_replacement(cpu_set_t = __cpu_set_t)]

%[define_type_class(__pthread_t = "TIn(__SIZEOF_PTHREAD_T)")]
%[define_type_class(__pthread_key_t = "TIn(__SIZEOF_PTHREAD_KEY_T)")]
%[define_type_class(__pthread_once_t = "TIn(__SIZEOF_PTHREAD_ONCE_T)")]


%{
#include <features.h>

#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadinit.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/crt/setjmp.h>
#include <bits/types.h>
#include <kos/anno.h>

#include <endian.h>
#include <sched.h>
#include <time.h>

__SYSDECL_BEGIN

/* Comments and definitions are derived from GNU C /usr/include/pthread.h: */
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
typedef void *(*__pthread_start_routine_t)(void *);
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


}

%[define_type_class(__pthread_start_routine_t = "TP")]
%[define(DEFINE_PTHREAD_START_ROUTINE_T =
@@pp_ifndef ____pthread_start_routine_t_defined@@
#define ____pthread_start_routine_t_defined 1
typedef void *(*__pthread_start_routine_t)(void *);
@@pp_endif@@
)]

@@Create a new thread, starting with execution of START-ROUTINE
@@getting passed ARG. Creation attributed come from ATTR. The new
@@handle is stored in *NEWTHREAD
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/types.h>")]]
[[decl_prefix(DEFINE_PTHREAD_START_ROUTINE_T)]]
$errno_t pthread_create([[nonnull]] pthread_t *__restrict newthread, pthread_attr_t const *__restrict attr,
                        [[nonnull]] __pthread_start_routine_t start_routine, void *__restrict arg);

@@Terminate calling thread.
@@The registered cleanup handlers are called via exception handling
[[throws, ATTR_NORETURN]]
void pthread_exit(void *retval);

@@Make calling thread wait for termination of the thread THREAD. The
@@exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
@@is not NULL
[[cp, decl_include("<bits/crt/pthreadtypes.h>", "<bits/types.h>")]]
$errno_t pthread_join(pthread_t pthread, void **thread_return);

%#ifdef __USE_GNU
@@Check whether thread THREAD has terminated. If yes return the status of
@@the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/types.h>")]]
$errno_t pthread_tryjoin_np(pthread_t pthread, void **thread_return);

%struct timespec;
@@Make calling thread wait for termination of the thread THREAD, but only
@@until TIMEOUT. The exit status of the thread is stored in
@@*THREAD_RETURN, if THREAD_RETURN is not NULL.
[[cp, decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pthread_timedjoin64_np")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pthread_timedjoin_np")]]
[[userimpl, requires($has_function(pthread_timedjoin32_np) || $has_function(pthread_timedjoin64_np))]]
$errno_t pthread_timedjoin_np(pthread_t pthread, void **thread_return,
                              struct timespec const *abstime) {
@@pp_if $has_function(pthread_timedjoin32_np)@@
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_timedjoin32_np(pthread, thread_return, &abstime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 abstime64;
	abstime64.tv_sec  = (time64_t)abstime->tv_sec;
	abstime64.tv_nsec = abstime->tv_nsec;
	result = pthread_timedjoin64_np(pthread, thread_return, &abstime32);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, ignore, doc_alias(pthread_timedjoin_np), nocrt, alias("pthread_timedjoin_np")]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
$errno_t pthread_timedjoin32_np(pthread_t pthread, void **thread_return,
                                struct timespec32 const *abstime);


[[cp, time64_variant_of(pthread_timedjoin_np)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires_function(pthread_timedjoin32_np)]]
$errno_t pthread_timedjoin64_np(pthread_t pthread, void **thread_return,
                                struct timespec64 const *abstime) {
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_timedjoin32_np(pthread, thread_return, &abstime32);
	return result;
}

%#endif /* __USE_TIME64 */
%#endif /* __USE_GNU */

@@Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
@@The resources of THREAD will therefore be freed immediately when it
@@terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it
[[decl_include("<bits/types.h>")]]
$errno_t pthread_detach(pthread_t pthread);

@@Obtain the identifier of the current thread
[[ATTR_CONST, export_alias("thrd_current")]]
pthread_t pthread_self();

@@Compare two thread identifiers
[[inline, ATTR_CONST, export_alias("thrd_equal")]]
int pthread_equal(pthread_t thr1, pthread_t thr2) {
	return thr1 == thr2;
}

%
%/* Thread attribute handling. */
%
@@Initialize thread attribute *ATTR with default attributes
@@(detachstate is PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack)
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_init([[nonnull]] pthread_attr_t *attr);

@@Destroy thread attribute *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_destroy([[nonnull]] pthread_attr_t *attr);

@@Get detach state attribute
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getdetachstate([[nonnull]] pthread_attr_t const *attr,
                                     [[nonnull]] int *detachstate);

@@Set detach state attribute
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setdetachstate([[nonnull]] pthread_attr_t *attr, int detachstate);

@@Get the size of the guard area created for stack overflow protection
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getguardsize([[nonnull]] pthread_attr_t const *attr,
                                   [[nonnull]] size_t *guardsize);

@@Set the size of the guard area created for stack overflow protection
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setguardsize([[nonnull]] pthread_attr_t *attr, size_t guardsize);

@@Return in *PARAM the scheduling parameters of *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getschedparam([[nonnull]] pthread_attr_t const *__restrict attr,
                                    [[nonnull]] struct sched_param *__restrict param);

@@Set scheduling parameters (priority, etc) in *ATTR according to PARAM
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setschedparam([[nonnull]] pthread_attr_t *__restrict attr,
                                    [[nonnull]] struct sched_param const *__restrict param);

@@Return in *POLICY the scheduling policy of *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getschedpolicy([[nonnull]] pthread_attr_t const *__restrict attr,
                                     [[nonnull]] int *__restrict policy);

@@Set scheduling policy in *ATTR according to POLICY
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setschedpolicy([[nonnull]] pthread_attr_t *attr, int policy);

@@Return in *INHERIT the scheduling inheritance mode of *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getinheritsched([[nonnull]] pthread_attr_t const *__restrict attr,
                                      [[nonnull]] int *__restrict inherit);

@@Set scheduling inheritance mode in *ATTR according to INHERIT
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setinheritsched([[nonnull]] pthread_attr_t *attr, int inherit);

@@Return in *SCOPE the scheduling contention scope of *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getscope([[nonnull]] pthread_attr_t const *__restrict attr,
                               [[nonnull]] int *__restrict scope);

@@Set scheduling contention scope in *ATTR according to SCOPE
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setscope([[nonnull]] pthread_attr_t *attr, int scope);

@@Return the previously set address for the stack
[[deprecated("Use pthread_attr_getstack()")]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getstackaddr([[nonnull]] pthread_attr_t const *__restrict attr,
                                   [[nonnull]] void **__restrict stackaddr);


@@Set the starting address of the stack of the thread to be created.
@@Depending on whether the stack grows up or down the value must either
@@be higher or lower than all the address in the memory block. The
@@minimal size of the block must be PTHREAD_STACK_MIN
[[deprecated("Use pthread_attr_setstack()")]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setstackaddr([[nonnull]] pthread_attr_t *attr, void *stackaddr);

@@Return the currently used minimal stack size
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getstacksize([[nonnull]] pthread_attr_t const *__restrict attr,
                                   [[nonnull]] size_t *__restrict stacksize);

@@Add information about the minimum stack size needed for the thread
@@to be started. This size must never be less than PTHREAD_STACK_MIN
@@and must also not exceed the system limits
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setstacksize([[nonnull]] pthread_attr_t *attr, size_t stacksize);

%#ifdef __USE_XOPEN2K
@@Return the previously set address for the stack
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getstack([[nonnull]] pthread_attr_t const *__restrict attr,
                               [[nonnull]] void **__restrict stackaddr,
                               [[nonnull]] size_t *__restrict stacksize);

@@The following two interfaces are intended to replace the last two. They
@@require setting the address as well as the size since only setting the
@@address will make the implementation on some architectures impossible
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setstack([[nonnull]] pthread_attr_t *attr, void *stackaddr, size_t stacksize);
%#endif /* __USE_XOPEN2K */

%#ifdef __USE_GNU
@@Thread created with attribute ATTR will be limited to run only on
@@the processors represented in CPUSET
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_setaffinity_np([[nonnull]] pthread_attr_t *attr, size_t cpusetsize,
                                     [[nonnull]] cpu_set_t const *cpuset);

@@Get bit set in CPUSET representing the processors threads created with ATTR can run on
[[decl_include("<bits/types.h>")]]
$errno_t pthread_attr_getaffinity_np([[nonnull]] pthread_attr_t const *attr, size_t cpusetsize,
                                     [[nonnull]] cpu_set_t *cpuset);

@@Get the default attributes used by pthread_create in this process
[[decl_include("<bits/types.h>")]]
$errno_t pthread_getattr_default_np([[nonnull]] pthread_attr_t *attr);

@@Set the default attributes to be used by pthread_create in this process
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setattr_default_np([[nonnull]] pthread_attr_t const *attr);

@@Initialize thread attribute *ATTR with attributes corresponding to the
@@already running thread THREAD. It shall be called on uninitialized ATTR
@@and destroyed with pthread_attr_destroy when no longer needed
[[decl_include("<bits/types.h>")]]
$errno_t pthread_getattr_np(pthread_t pthread, [[nonnull]] pthread_attr_t *attr);
%#endif /* __USE_GNU */

%
%/* Functions for scheduling control. */
%
@@Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setschedparam(pthread_t target_thread, int policy,
                               [[nonnull]] struct sched_param const *param);

@@Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD
[[decl_include("<bits/types.h>")]]
$errno_t pthread_getschedparam(pthread_t target_thread,
                               [[nonnull]] int *__restrict policy,
                               [[nonnull]] struct sched_param *__restrict param);

@@Set the scheduling priority for TARGET_THREAD
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setschedprio(pthread_t target_thread, int prio);


%#ifdef __USE_GNU
@@Get thread name visible in the kernel and its interfaces
[[decl_include("<bits/types.h>")]]
$errno_t pthread_getname_np(pthread_t target_thread,
                            [[outp(buflen)]] char *buf,
                            size_t buflen);

@@Set thread name visible in the kernel and its interfaces
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setname_np(pthread_t target_thread,
                            [[nonnull]] const char *name);
%#endif /* __USE_GNU */


%#ifdef __USE_KOS
@@Return the TID of the given `target_thread'
@@If the given `target_thread' has already terminated, 0 is returned
[[guard, wunused, ATTR_CONST]]
$pid_t pthread_gettid_np(pthread_t target_thread);
%#endif /* __USE_KOS */


%#ifdef __USE_UNIX98
@@Determine level of concurrency
[[ATTR_PURE]]
int pthread_getconcurrency();

@@Set new concurrency level to LEVEL
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setconcurrency(int level);
%#endif /* __USE_UNIX98 */

%#ifdef __USE_GNU
@@Yield the processor to another thread or process.
@@This function is similar to the POSIX `sched_yield' function but
@@might be differently implemented in the case of a m-on-n thread
@@implementation
pthread_yield(*) = sched_yield;

@@Limit specified thread THREAD to run only on the processors represented in CPUSET
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setaffinity_np(pthread_t pthread, size_t cpusetsize,
                                [[nonnull]] cpu_set_t const *cpuset);

@@Get bit set in CPUSET representing the processors THREAD can run on
[[decl_include("<bits/types.h>")]]
$errno_t pthread_getaffinity_np(pthread_t pthread, size_t cpusetsize,
                                [[nonnull]] cpu_set_t *cpuset);
%#endif /* __USE_GNU */


%
%#ifndef ____pthread_once_routine_t_defined
%#define ____pthread_once_routine_t_defined 1
%typedef void (__LIBKCALL *__pthread_once_routine_t)(void);
%#endif /* !____pthread_once_routine_t_defined */
%[define_type_class(__pthread_once_routine_t = "TP")]

%[define(DEFINE_PTHREAD_ONCE_ROUTINE_T =
@@pp_ifndef ____pthread_once_routine_t_defined@@
#define ____pthread_once_routine_t_defined 1
typedef void (__LIBKCALL *__pthread_once_routine_t)(void);
@@pp_endif@@
)]


%
%/* Functions for handling initialization. */
%

@@Guarantee that the initialization function INIT_ROUTINE will be called
@@only once, even if pthread_once is executed several times with the
@@same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
@@extern variable initialized to PTHREAD_ONCE_INIT.
[[throws, export_alias("call_once")]]
[[decl_prefix(DEFINE_PTHREAD_ONCE_ROUTINE_T)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/types.h>")]]
[[impl_include("<asm/crt/pthreadvalues.h>", "<hybrid/__atomic.h>")]]
$errno_t pthread_once([[nonnull]] pthread_once_t *once_control,
                      [[nonnull]] __pthread_once_routine_t init_routine) {
	if (__hybrid_atomic_xch(*once_control, __PTHREAD_ONCE_INIT + 1,
	                        __ATOMIC_SEQ_CST) == __PTHREAD_ONCE_INIT) {
		/* Since init_routine() can't indicate failure, we only need a bi-state
		 * control word, as we don't need any sort of is-executing state, and
		 * can directly go from not-executed to was-executed. */
		(*init_routine)();
	}
	return 0;
}

%
%/* Functions for handling cancellation.
% * Note that these functions are explicitly not marked to not throw an
% * exception in C++ code. If cancellation is implemented by unwinding
% * this is necessary to have the compiler generate the unwind information. */


@@Set cancelability state of current thread to STATE,
@@returning old state in *OLDSTATE if OLDSTATE is not NULL
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setcancelstate(int state, [[nullable]] int *oldstate);

@@Set cancellation state of current thread to TYPE, returning the old
@@type in *OLDTYPE if OLDTYPE is not NULL
[[guard, decl_include("<bits/types.h>")]]
$errno_t pthread_setcanceltype(int type, [[nullable]] int *oldtype);

@@Cancel THREAD immediately or at the next possibility
[[decl_include("<bits/types.h>")]]
$errno_t pthread_cancel(pthread_t pthread);

@@Test for pending cancellation for the current thread and terminate
@@the thread as per pthread_exit(PTHREAD_CANCELED) if it has been canceled
[[cp]]
void pthread_testcancel();


%
%/* Cancellation handling with integration into exception handling. */

%{
typedef struct {
	struct {
		struct __jmp_buf __cancel_jmp_buf;
		int              __mask_was_saved;
	}                    __cancel_jmp_buf[1];
	void                *__pad[4];
} __pthread_unwind_buf_t __attribute__((__aligned__)); /* XXX: Portable attribute? */

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
}


%#if defined(__GNUC__) && defined(__EXCEPTIONS)
%{
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
}

@@Function called to call the cleanup handler. As an extern inline
@@function the compiler is free to decide inlining the change when
@@needed or fall back on the copy which must exist somewhere else
void __pthread_cleanup_routine([[nonnull]] struct __pthread_cleanup_frame *frame) {
	if (frame->__do_it)
		(*frame->__cancel_routine)(frame->__cancel_arg);
}

%{
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
}

%#else /* __GNUC__ && __EXCEPTIONS */

%/* Install a cleanup handler: ROUTINE will be called with arguments ARG
% * when the thread is canceled or calls pthread_exit. ROUTINE will also
% * be called with arguments ARG when the matching pthread_cleanup_pop
% * is executed with non-zero EXECUTE argument.
% * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
% * be used in matching pairs at the same nesting level of braces. */
%#define pthread_cleanup_push(routine, arg)                                                                    \
%	do {                                                                                                      \
%		__pthread_unwind_buf_t __cancel_buf;                                                                  \
%		void (__LIBKCALL *__cancel_routine)(void *) = (routine);                                              \
%		void *__cancel_arg                          = (arg);                                                  \
%		int __not_first_call = __sigsetjmp((struct __jmp_buf_tag *)(void *)__cancel_buf.__cancel_jmp_buf, 0); \
%		if __unlikely(__not_first_call) {                                                                     \
%			(*__cancel_routine)(__cancel_arg);                                                                \
%			__pthread_unwind_next(&__cancel_buf);                                                             \
%			__builtin_unreachable();                                                                          \
%		}                                                                                                     \
%		__pthread_register_cancel(&__cancel_buf);                                                             \
%		do {
%

%[define(DEFINE___cleanup_fct_attribute =
#ifndef __cleanup_fct_attribute
#define __cleanup_fct_attribute /* nothing */
#endif /* !__cleanup_fct_attribute */
)]


[[decl_prefix(DEFINE___cleanup_fct_attribute)]]
[[attribute(__cleanup_fct_attribute)]]
__pthread_register_cancel:(__pthread_unwind_buf_t *buf);

%/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
% * If EXECUTE is non-zero, the handler function is called. */
%#define pthread_cleanup_pop(execute)                                           \
%			do {                                                               \
%			} __WHILE0; /* Empty to allow label before pthread_cleanup_pop. */ \
%		} __WHILE0;                                                            \
%		__pthread_unregister_cancel(&__cancel_buf);                            \
%		if (execute)                                                           \
%			(*__cancel_routine)(__cancel_arg);                                 \
%	} __WHILE0

[[decl_prefix(DEFINE___cleanup_fct_attribute)]]
[[attribute(__cleanup_fct_attribute)]]
void __pthread_unregister_cancel([[nonnull]] __pthread_unwind_buf_t *buf);

%#ifdef __USE_GNU
%/* Install a cleanup handler as pthread_cleanup_push does, but also
% * saves the current cancellation type and sets it to deferred
% * cancellation. */
%#define pthread_cleanup_push_defer_np(routine, arg)                                                           \
%	do {                                                                                                      \
%		__pthread_unwind_buf_t __cancel_buf;                                                                  \
%		void (__LIBKCALL *__cancel_routine)(void *) = (routine);                                              \
%		void *__cancel_arg               = (arg);                                                             \
%		int __not_first_call = __sigsetjmp((struct __jmp_buf_tag *)(void *)__cancel_buf.__cancel_jmp_buf, 0); \
%		if __unlikely(__not_first_call) {                                                                     \
%			__cancel_routine(__cancel_arg);                                                                   \
%			__pthread_unwind_next(&__cancel_buf);                                                             \
%			__builtin_unreachable();                                                                          \
%		}                                                                                                     \
%		__pthread_register_cancel_defer(&__cancel_buf);                                                       \
%		do {

[[decl_prefix(DEFINE___cleanup_fct_attribute)]]
[[attribute(__cleanup_fct_attribute)]]
void __pthread_register_cancel_defer([[nonnull]] __pthread_unwind_buf_t *buf);

%/* Remove a cleanup handler as pthread_cleanup_pop does, but also
% * restores the cancellation type that was in effect when the matching
% * pthread_cleanup_push_defer was called. */
%#define pthread_cleanup_pop_restore_np(execute)                                \
%			do {                                                               \
%			} __WHILE0; /* Empty to allow label before pthread_cleanup_pop. */ \
%		} __WHILE0;                                                            \
%		__pthread_unregister_cancel_restore(&__cancel_buf);                    \
%		if (execute)                                                           \
%			(*__cancel_routine)(__cancel_arg);                                 \
%	} __WHILE0

[[decl_prefix(DEFINE___cleanup_fct_attribute)]]
[[attribute(__cleanup_fct_attribute)]]
void __pthread_unregister_cancel_restore([[nonnull]] __pthread_unwind_buf_t *buf);
%#endif /* __USE_GNU */

@@Internal interface to initiate cleanup
[[ATTR_WEAK]] /* XXX:[if(!defined(SHARED)), ATTR_WEAK] */
[[decl_prefix(DEFINE___cleanup_fct_attribute)]]
[[attribute(__cleanup_fct_attribute)]]
void __pthread_unwind_next([[nonnull]] __pthread_unwind_buf_t *buf);

%#endif /* !__GNUC__ || !__EXCEPTIONS */

%
%/* Function used in the macros. */
%struct __jmp_buf_tag;
[[alias(sigsetjmp), no_crt_impl, decl_prefix(struct __jmp_buf_tag;)]]
int __sigsetjmp([[nonnull]] struct __jmp_buf_tag *env, int savemask);

%
%/* Mutex handling. */
%
@@Initialize a mutex
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutex_init([[nonnull]] pthread_mutex_t *mutex,
                            pthread_mutexattr_t const *mutexattr);

@@Destroy a mutex
[[export_alias("mtx_destroy")]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutex_destroy([[nonnull]] pthread_mutex_t *mutex);

@@Try locking a mutex
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutex_trylock([[nonnull]] pthread_mutex_t *mutex);

@@Lock a mutex
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutex_lock([[nonnull]] pthread_mutex_t *mutex);

%#ifdef __USE_XOPEN2K
@@Wait until lock becomes available, or specified time passes
[[cp, decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(pthread_mutex_timedlock64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(pthread_mutex_timedlock)]]
[[userimpl, requires($has_function(pthread_mutex_timedlock32) || $has_function(pthread_mutex_timedlock64))]]
$errno_t pthread_mutex_timedlock([[nonnull]] pthread_mutex_t *__restrict mutex,
                                 [[nonnull]] struct timespec const *__restrict abstime) {
@@pp_if $has_function(pthread_mutex_timedlock32)@@
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_mutex_timedlock32(mutex, &abstime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 abstime64;
	abstime64.tv_sec  = (time64_t)abstime->tv_sec;
	abstime64.tv_nsec = abstime->tv_nsec;
	result = pthread_mutex_timedlock64(mutex, &abstime64);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, doc_alias(pthread_mutex_timedlock), ignore, nocrt, alias(pthread_mutex_timedlock)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
$errno_t pthread_mutex_timedlock32([[nonnull]] pthread_mutex_t *__restrict mutex,
                                   [[nonnull]] struct timespec const *__restrict abstime);

[[cp, doc_alias(pthread_mutex_timedlock), time64_variant_of(pthread_mutex_timedlock)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires($has_function(pthread_mutex_timedlock32))]]
$errno_t pthread_mutex_timedlock64([[nonnull]] pthread_mutex_t *__restrict mutex,
                                   [[nonnull]] struct timespec64 const *__restrict abstime) {
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_mutex_timedlock32(mutex, &abstime32);
	return result;
}

%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K */

@@Unlock a mutex
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutex_unlock([[nonnull]] pthread_mutex_t *mutex);

@@Get the priority ceiling of MUTEX
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutex_getprioceiling([[nonnull]] pthread_mutex_t const *__restrict mutex,
                                      [[nonnull]] int *__restrict prioceiling);

@@Set the priority ceiling of MUTEX to PRIOCEILING, return old
@@priority ceiling value in *OLD_CEILING
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutex_setprioceiling([[nonnull]] pthread_mutex_t *__restrict mutex, int prioceiling,
                                      [[nonnull]] int *__restrict old_ceiling);

%#ifdef __USE_XOPEN2K8
@@Declare the state protected by MUTEX as consistent
[[decl_include("<bits/types.h>"), export_alias("pthread_mutex_consistent_np")]]
$errno_t pthread_mutex_consistent([[nonnull]] pthread_mutex_t *mutex);
%#ifdef __USE_GNU
%[insert:function(pthread_mutex_consistent_np = pthread_mutex_consistent)]
%#endif /* __USE_GNU */
%#endif /* __USE_XOPEN2K8 */

%
%/* Functions for handling mutex attributes. */


@@Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP)
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_init([[nonnull]] pthread_mutexattr_t *attr);


@@Destroy mutex attribute object ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_destroy([[nonnull]] pthread_mutexattr_t *attr);

@@Get the process-shared flag of the mutex attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_getpshared([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                      [[nonnull]] int *__restrict pshared);

@@Set the process-shared flag of the mutex attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_setpshared([[nonnull]] pthread_mutexattr_t *attr, int pshared);


%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
@@Return in *KIND the mutex kind attribute in *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_gettype([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                   [[nonnull]] int *__restrict kind);

@@Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
@@PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT)
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_settype([[nonnull]] pthread_mutexattr_t *attr, int kind);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

@@Return in *PROTOCOL the mutex protocol attribute in *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_getprotocol([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                       [[nonnull]] int *__restrict protocol);

@@Set the mutex protocol attribute in *ATTR to PROTOCOL (either
@@PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT)
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_setprotocol([[nonnull]] pthread_mutexattr_t *attr, int protocol);

@@Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_getprioceiling([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                          [[nonnull]] int *__restrict prioceiling);

@@Set the mutex prioceiling attribute in *ATTR to PRIOCEILING
[[decl_include("<bits/types.h>")]]
$errno_t pthread_mutexattr_setprioceiling([[nonnull]] pthread_mutexattr_t *attr, int prioceiling);

%#ifdef __USE_XOPEN2K
@@Get the robustness flag of the mutex attribute ATTR
[[decl_include("<bits/types.h>"), export_alias("pthread_mutexattr_getrobust_np")]]
$errno_t pthread_mutexattr_getrobust([[nonnull]] pthread_mutexattr_t const *attr,
                                     [[nonnull]] int *robustness);

@@Set the robustness flag of the mutex attribute ATTR
[[decl_include("<bits/types.h>"), export_alias("pthread_mutexattr_setrobust_np")]]
$errno_t pthread_mutexattr_setrobust([[nonnull]] pthread_mutexattr_t *attr, int robustness);

%#ifdef __USE_GNU
%[insert:function(pthread_mutexattr_getrobust_np = pthread_mutexattr_getrobust)]
%[insert:function(pthread_mutexattr_setrobust_np = pthread_mutexattr_setrobust)]
%#endif /* __USE_GNU */
%#endif /* __USE_XOPEN2K */


%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
%/* Functions for handling read-write locks. */

@@Initialize read-write lock RWLOCK using attributes ATTR,
@@or use the default values if later is NULL
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlock_init([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                        pthread_rwlockattr_t const *__restrict attr);

@@Destroy read-write lock RWLOCK
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlock_destroy([[nonnull]] pthread_rwlock_t *rwlock);

@@Acquire read lock for RWLOCK
[[cp, decl_include("<bits/types.h>")]]
$errno_t pthread_rwlock_rdlock([[nonnull]] pthread_rwlock_t *rwlock);

@@Try to acquire read lock for RWLOCK
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlock_tryrdlock([[nonnull]] pthread_rwlock_t *rwlock);

%#ifdef __USE_XOPEN2K

@@Try to acquire read lock for RWLOCK or return after specfied time
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedrdlock64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedrdlock")]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires($has_function(pthread_rwlock_timedrdlock32) || $has_function(pthread_rwlock_timedrdlock64))]]
$errno_t pthread_rwlock_timedrdlock([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                    [[nonnull]] struct timespec const *__restrict abstime) {
@@pp_if $has_function(pthread_rwlock_timedrdlock32)@@
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_rwlock_timedrdlock32(rwlock, &abstime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 abstime64;
	abstime64.tv_sec  = (time64_t)abstime->tv_sec;
	abstime64.tv_nsec = abstime->tv_nsec;
	result = pthread_rwlock_timedrdlock64(rwlock, &abstime32);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64

[[cp, doc_alias(pthread_rwlock_timedrdlock), ignore, nocrt, alias("pthread_rwlock_timedrdlock")]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
$errno_t pthread_rwlock_timedrdlock32([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec32 const *__restrict abstime);

[[cp, doc_alias(pthread_rwlock_timedrdlock), time64_variant_of(pthread_rwlock_timedrdlock)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires_function(pthread_rwlock_timedrdlock32)]]
$errno_t pthread_rwlock_timedrdlock64([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec64 const *__restrict abstime) {
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_rwlock_timedrdlock32(rwlock, &abstime32);
	return result;
}


%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K */

@@Acquire write lock for RWLOCK
[[cp, decl_include("<bits/types.h>")]]
$errno_t pthread_rwlock_wrlock([[nonnull]] pthread_rwlock_t *rwlock);

@@Try to acquire write lock for RWLOCK
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlock_trywrlock([[nonnull]] pthread_rwlock_t *rwlock);

%#ifdef __USE_XOPEN2K

@@Try to acquire write lock for RWLOCK or return after specfied time
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedwrlock64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedwrlock")]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires($has_function(pthread_rwlock_timedwrlock32) || $has_function(pthread_rwlock_timedwrlock64))]]
$errno_t pthread_rwlock_timedwrlock([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                    [[nonnull]] struct timespec const *__restrict abstime) {
@@pp_if $has_function(pthread_rwlock_timedwrlock32)@@
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_rwlock_timedwrlock32(rwlock, &abstime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 abstime64;
	abstime64.tv_sec  = (time64_t)abstime->tv_sec;
	abstime64.tv_nsec = abstime->tv_nsec;
	result = pthread_rwlock_timedwrlock64(rwlock, &abstime32);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64

[[cp, doc_alias(pthread_rwlock_timedwrlock), ignore, nocrt, alias("pthread_rwlock_timedwrlock")]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
$errno_t pthread_rwlock_timedwrlock32([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec32 const *__restrict abstime);

[[cp, doc_alias(pthread_rwlock_timedwrlock)]]
[[time64_variant_of(pthread_rwlock_timedwrlock)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires_function(pthread_rwlock_timedwrlock32)]]
$errno_t pthread_rwlock_timedwrlock64([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec64 const *__restrict abstime) {
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_rwlock_timedwrlock32(rwlock, &abstime32);
	return result;
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K */

@@Unlock RWLOCK
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlock_unlock([[nonnull]] pthread_rwlock_t *rwlock);

%
%/* Functions for handling read-write lock attributes. */

@@Initialize attribute object ATTR with default values
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlockattr_init([[nonnull]] pthread_rwlockattr_t *attr);

@@Destroy attribute object ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlockattr_destroy([[nonnull]] pthread_rwlockattr_t *attr);

@@Return current setting of process-shared attribute of ATTR in PSHARED
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlockattr_getpshared([[nonnull]] pthread_rwlockattr_t const *__restrict attr,
                                       [[nonnull]] int *__restrict pshared);

@@Set process-shared attribute of ATTR to PSHARED
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlockattr_setpshared([[nonnull]] pthread_rwlockattr_t *attr, int pshared);

@@Return current setting of reader/writer preference
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlockattr_getkind_np([[nonnull]] pthread_rwlockattr_t const *__restrict attr,
                                  [[nonnull]] int *__restrict pref);

@@Set reader/write preference
[[decl_include("<bits/types.h>")]]
$errno_t pthread_rwlockattr_setkind_np([[nonnull]] pthread_rwlockattr_t *attr, int pref);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%/* Functions for handling conditional variables. */

@@Initialize condition variable COND using attributes ATTR, or use
@@the default values if later is NULL
[[decl_include("<bits/types.h>")]]
$errno_t pthread_cond_init([[nonnull]] pthread_cond_t *__restrict cond,
                      [[nullable]] pthread_condattr_t const *__restrict cond_attr);

@@Destroy condition variable COND
[[export_alias("cnd_destroy"), decl_include("<bits/types.h>")]]
$errno_t pthread_cond_destroy([[nonnull]] pthread_cond_t *cond);

@@Wake up one thread waiting for condition variable COND
[[decl_include("<bits/types.h>")]]
$errno_t pthread_cond_signal([[nonnull]] pthread_cond_t *cond);

@@Wake up all threads waiting for condition variables COND
[[decl_include("<bits/types.h>")]]
$errno_t pthread_cond_broadcast([[nonnull]] pthread_cond_t *cond);

@@Wait for condition variable COND to be signaled or broadcast.
@@MUTEX is assumed to be locked before.
[[cp, decl_include("<bits/types.h>")]]
$errno_t pthread_cond_wait([[nonnull]] pthread_cond_t *__restrict cond,
                      [[nonnull]] pthread_mutex_t *__restrict mutex);

@@Wait for condition variable COND to be signaled or broadcast until
@@ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
@@absolute time specification; zero is the beginning of the epoch
@@(00:00:00 GMT, January 1, 1970).
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(pthread_cond_timedwait64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(pthread_cond_timedwait)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires($has_function(pthread_cond_timedwait32) || $has_function(pthread_cond_timedwait64))]]
$errno_t pthread_cond_timedwait([[nonnull]] pthread_cond_t *__restrict cond,
                                [[nonnull]] pthread_mutex_t *__restrict mutex,
                                [[nonnull]] struct timespec const *__restrict abstime) {
@@pp_if $has_function(pthread_cond_timedwait32)@@
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_cond_timedwait32(cond, mutex, &abstime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 abstime64;
	abstime64.tv_sec  = (time64_t)abstime->tv_sec;
	abstime64.tv_nsec = abstime->tv_nsec;
	result = pthread_cond_timedwait64(cond, mutex, &abstime64);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, ignore, nocrt, alias("pthread_cond_timedwait")]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
$errno_t pthread_cond_timedwait32([[nonnull]] pthread_cond_t *__restrict cond,
                                  [[nonnull]] pthread_mutex_t *__restrict mutex,
                                  [[nonnull]] struct timespec32 const *__restrict abstime);

[[cp, doc_alias("pthread_cond_timedwait"), time64_variant_of(pthread_cond_timedwait)]]
[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/timespec.h>", "<bits/types.h>")]]
[[userimpl, requires_function(pthread_cond_timedwait32)]]
$errno_t pthread_cond_timedwait64([[nonnull]] pthread_cond_t *__restrict cond,
                                  [[nonnull]] pthread_mutex_t *__restrict mutex,
                                  [[nonnull]] struct timespec64 const *__restrict abstime) {
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_cond_timedwait32(cond, mutex, &abstime32);
	return result;
}

%#endif /* __USE_TIME64 */


%
%/* Functions for handling condition variable attributes. */

@@Initialize condition variable attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_condattr_init([[nonnull]] pthread_condattr_t *attr);

@@Destroy condition variable attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_condattr_destroy([[nonnull]] pthread_condattr_t *attr);

@@Get the process-shared flag of the condition variable attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_condattr_getpshared([[nonnull]] pthread_condattr_t const *__restrict attr,
                                     [[nonnull]] int *__restrict pshared);

@@Set the process-shared flag of the condition variable attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_condattr_setpshared([[nonnull]] pthread_condattr_t *attr, int pshared);

%#ifdef __USE_XOPEN2K

@@Get the clock selected for the condition variable attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_condattr_getclock([[nonnull]] pthread_condattr_t const *__restrict attr,
                              [[nonnull]] $clockid_t *__restrict clock_id);

@@Set the clock selected for the condition variable attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_condattr_setclock([[nonnull]] pthread_condattr_t *attr, $clockid_t clock_id);
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_XOPEN2K
%/* Functions to handle spinlocks. */


@@Initialize the spinlock LOCK. If PSHARED is nonzero the
@@spinlock can be shared between different processes
[[impl_include("<hybrid/__atomic.h>"), decl_include("<bits/types.h>")]]
$errno_t pthread_spin_init([[nonnull]] pthread_spinlock_t *lock, int pshared) {
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}

@@Destroy the spinlock LOCK
[[decl_include("<bits/types.h>")]]
$errno_t pthread_spin_destroy([[nonnull]] pthread_spinlock_t *lock) {
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}

@@Wait until spinlock LOCK is retrieved
[[impl_include("<hybrid/__atomic.h>", "<hybrid/sched/__yield.h>")]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_spin_lock([[nonnull]] pthread_spinlock_t *lock) {
	while (pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}

@@Try to lock spinlock LOCK
[[impl_include("<hybrid/__atomic.h>", "<parts/errno.h>")]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_spin_trylock([[nonnull]] pthread_spinlock_t *lock) {
	if (__hybrid_atomic_xch(*lock, 1, __ATOMIC_ACQUIRE) == 0)
		return 0;
@@pp_ifdef EBUSY@@
	return EBUSY;
@@pp_elif defined(EWOULDBLOCK)@@
	return EWOULDBLOCK;
@@pp_elif defined(EAGAIN)@@
	return EAGAIN;
@@pp_else@@
	return 1;
@@pp_endif@@
}

@@Release spinlock LOCK
[[impl_include("<hybrid/__atomic.h>")]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_spin_unlock([[nonnull]] pthread_spinlock_t *lock) {
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELEASE);
	return 0;
}


%
%/* Functions to handle barriers. */

@@Initialize BARRIER with the attributes in ATTR.
@@The barrier is opened when COUNT waiters arrived
[[decl_include("<bits/types.h>")]]
$errno_t pthread_barrier_init([[nonnull]] pthread_barrier_t *__restrict barrier,
                              [[inp(count)]] pthread_barrierattr_t const *__restrict attr,
                              unsigned int count);

@@Destroy a previously dynamically initialized barrier BARRIER
[[decl_include("<bits/types.h>")]]
$errno_t pthread_barrier_destroy([[nonnull]] pthread_barrier_t *barrier);

@@Wait on barrier BARRIER
[[cp, decl_include("<bits/types.h>")]]
$errno_t pthread_barrier_wait([[nonnull]] pthread_barrier_t *barrier);

@@Initialize barrier attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_barrierattr_init([[nonnull]] pthread_barrierattr_t *attr);

@@Destroy previously dynamically initialized barrier attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_barrierattr_destroy([[nonnull]] pthread_barrierattr_t *attr);

@@Get the process-shared flag of the barrier attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_barrierattr_getpshared([[nonnull]] pthread_barrierattr_t const *__restrict attr,
                                        [[nonnull]] int *__restrict pshared);

@@Set the process-shared flag of the barrier attribute ATTR
[[decl_include("<bits/types.h>")]]
$errno_t pthread_barrierattr_setpshared([[nonnull]] pthread_barrierattr_t *attr, int pshared);

%#endif /* __USE_XOPEN2K */

%
%/* Functions for handling thread-specific data. */


%{
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
}
%[define_type_class(__pthread_destr_function_t = "TP")]


@@Create a key value identifying a location in the thread-specific
@@data area. Each thread maintains a distinct thread-specific data
@@area. DESTR_FUNCTION, if non-NULL, is called with the value
@@associated to that key when the key is destroyed.
@@DESTR_FUNCTION is not called if the value associated is NULL when
@@the key is destroyed
[[decl_prefix(
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
)]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_key_create([[nonnull]] pthread_key_t *key,
                            [[nullable]] __pthread_destr_function_t destr_function);

@@Destroy KEY
[[decl_include("<bits/types.h>"), export_alias("tss_delete")]]
$errno_t pthread_key_delete(pthread_key_t key);

@@Return current value of the thread-specific data slot identified by KEY
[[wunused, export_alias("tss_get")]]
void *pthread_getspecific(pthread_key_t key);

@@Store POINTER in the thread-specific data slot identified by KEY
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setspecific(pthread_key_t key, void const *pointer);

%#ifdef __USE_XOPEN2K
@@Get ID of CPU-time clock for thread THREAD_ID
[[decl_include("<bits/types.h>")]]
$errno_t pthread_getcpuclockid(pthread_t pthread_id, [[nonnull]] $clockid_t *clock_id);
%#endif /* __USE_XOPEN2K */

%
%#ifndef ____pthread_atfork_func_t_defined
%#define ____pthread_atfork_func_t_defined 1
%typedef void (__LIBKCALL *__pthread_atfork_func_t)(void);
%#endif /* !____pthread_atfork_func_t_defined */
%[define_type_class(__pthread_atfork_func_t = "TP")]

%[define(DEFINE_PTHREAD_ATFORK_FUNC_T =
@@pp_ifndef ____pthread_atfork_func_t_defined@@
#define ____pthread_atfork_func_t_defined 1
typedef void (__LIBKCALL *__pthread_atfork_func_t)(void);
@@pp_endif@@
)]


@@Install handlers to be called when a new process is created with FORK.
@@The PREPARE handler is called in the parent process just before performing
@@FORK. The PARENT handler is called in the parent process just after FORK.
@@The CHILD handler is called in the child process. Each of the three
@@handlers can be NULL, meaning that no handler needs to be called at that
@@point.
@@PTHREAD_ATFORK can be called several times, in which case the PREPARE
@@handlers are called in LIFO order (last added with PTHREAD_ATFORK,
@@first called before FORK), and the PARENT and CHILD handlers are called
@@in FIFO (first added, first called)
[[guard, decl_prefix(DEFINE_PTHREAD_ATFORK_FUNC_T), decl_include("<bits/types.h>")]]
$errno_t pthread_atfork([[nullable]] __pthread_atfork_func_t prepare,
                        [[nullable]] __pthread_atfork_func_t parent,
                        [[nullable]] __pthread_atfork_func_t child);

%[default:section(".text.crt{|.dos}.sched.pthread_ext")]

%
%
%/* Some more functions from winpthread. */
[[impl_include("<bits/sched.h>")]]
[[decl_include("<features.h>")]]
[[requires_function(sched_getaffinity)]]
__STDC_INT_AS_SIZE_T pthread_num_processors_np() {
	cpu_set_t cset;
	if unlikely(sched_getaffinity(0, sizeof(cset), &cset) != 0)
		return 1;
	return (__STDC_INT_AS_SIZE_T)__CPU_COUNT_S(sizeof(cset), &cset);
}

[[decl_include("<bits/types.h>")]]
[[impl_include("<bits/sched.h>", "<parts/errno.h>")]]
[[requires_function(sched_setaffinity)]]
$errno_t pthread_set_num_processors_np(int n) {
	int i, result;
	cpu_set_t cset;
	if (n < 1) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	__CPU_ZERO_S(sizeof(cset), &cset);
	for (i = 0; i < n; ++i) {
		if (!__CPU_SET_S(i, sizeof(cset), &cset))
			break;
	}
	result = sched_setaffinity(0, sizeof(cset), &cset);
	if unlikely(result != 0)
		result = __libc_geterrno_or(1);
	return result;
}


%#ifdef __USE_BSD
@@Returns 1 if the calling thread is the main() thread (i.e. the
@@thread that was started by the kernel in order to execute the
@@calling program), and 0 otherwise. Additionally, -1 is returned
@@if the calling thread "hasn't been initialized", though this
@@isn't a case that can actually happen under KOS's implementation.
[[ATTR_CONST, export_alias("thr_main")]]
[[requires_function(gettid, getpid)]]
int pthread_main_np() {
	return gettid() == getpid();
}
%#endif /* __USE_BSD */


%{
#endif /* __CC__ */

__SYSDECL_END

}