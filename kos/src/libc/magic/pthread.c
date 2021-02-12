/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/pthread.h) */
/* (#) Portability: FreeBSD       (/include/pthread.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/pthread.h) */
/* (#) Portability: MinGW         (/mingw-w64-libraries/winpthreads/include/pthread.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/pthread.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/pthread.h) */
/* (#) Portability: diet libc     (/include/pthread.h) */
/* (#) Portability: musl libc     (/include/pthread.h) */
/* (#) Portability: uClibc        (/libpthread/nptl/sysdeps/pthread/pthread.h) */
}

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
%[define_replacement(cpu_set_t = "struct __cpu_set_struct")]

%[define_type_class(__pthread_t = "TIn(__SIZEOF_PTHREAD_T)")]
%[define_type_class(__pthread_key_t = "TIn(__SIZEOF_PTHREAD_KEY_T)")]
%[define_type_class(__pthread_once_t = "TIn(__SIZEOF_PTHREAD_ONCE_T)")]


%{
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

/* Detach state. */
#ifndef __PTHREAD_ENUM_DETACH_STATE_DEFINED
#define __PTHREAD_ENUM_DETACH_STATE_DEFINED 1
#if (defined(__PTHREAD_CREATE_JOINABLE) || \
     defined(__PTHREAD_CREATE_DETACHED))
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
#endif /* __PTHREAD_CREATE_JOINABLE || __PTHREAD_CREATE_DETACHED */
#endif /* !__PTHREAD_ENUM_DETACH_STATE_DEFINED */



/* Mutex types. */
#ifndef __PTHREAD_ENUM_MUTEX_TYPE_DEFINED
#define __PTHREAD_ENUM_MUTEX_TYPE_DEFINED 1
#if (defined(__PTHREAD_MUTEX_TIMED) || defined(__PTHREAD_MUTEX_RECURSIVE) ||     \
     defined(__PTHREAD_MUTEX_ERRORCHECK) || defined(__PTHREAD_MUTEX_ADAPTIVE) || \
     (defined(__USE_XOPEN2K) && (defined(__PTHREAD_MUTEX_STALLED) ||             \
                                 defined(__PTHREAD_MUTEX_ROBUST))))
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
	PTHREAD_MUTEX_FAST_NP = __PTHREAD_MUTEX_TIMED, /* Compatibility alias. */
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
	PTHREAD_MUTEX_STALLED    = __PTHREAD_MUTEX_STALLED, /* Not a robust mutex. */
	PTHREAD_MUTEX_STALLED_NP = __PTHREAD_MUTEX_STALLED, /* Not a robust mutex. */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
	PTHREAD_MUTEX_ROBUST     = __PTHREAD_MUTEX_ROBUST,  /* Robust mutex. */
	PTHREAD_MUTEX_ROBUST_NP  = __PTHREAD_MUTEX_ROBUST,  /* Robust mutex. */
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
#define PTHREAD_MUTEX_FAST_NP       PTHREAD_MUTEX_FAST_NP       /* Compatibility alias. */
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
#define PTHREAD_MUTEX_STALLED       PTHREAD_MUTEX_STALLED       /* Not a robust mutex. */
#define PTHREAD_MUTEX_STALLED_NP    PTHREAD_MUTEX_STALLED_NP    /* Not a robust mutex. */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
#define PTHREAD_MUTEX_ROBUST        PTHREAD_MUTEX_ROBUST        /* Robust mutex. */
#define PTHREAD_MUTEX_ROBUST_NP     PTHREAD_MUTEX_ROBUST_NP     /* Robust mutex. */
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
#define PTHREAD_MUTEX_FAST_NP       __PTHREAD_MUTEX_TIMED      /* Compatibility alias. */
#endif /* __PTHREAD_MUTEX_TIMED */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#ifdef __PTHREAD_MUTEX_STALLED
#define PTHREAD_MUTEX_STALLED       __PTHREAD_MUTEX_STALLED    /* Not a robust mutex. */
#define PTHREAD_MUTEX_STALLED_NP    __PTHREAD_MUTEX_STALLED    /* Not a robust mutex. */
#endif /* __PTHREAD_MUTEX_STALLED */
#ifdef __PTHREAD_MUTEX_ROBUST
#define PTHREAD_MUTEX_ROBUST        __PTHREAD_MUTEX_ROBUST     /* Robust mutex. */
#define PTHREAD_MUTEX_ROBUST_NP     __PTHREAD_MUTEX_ROBUST     /* Robust mutex. */
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
#if (defined(__PTHREAD_PRIO_NONE) || defined(__PTHREAD_PRIO_INHERIT) || \
     defined(__PTHREAD_PRIO_PROTECT))
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
#endif /* !__PTHREAD_ENUM_MUTEX_PRIO_DEFINED */
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
#ifndef __PTHREAD_ENUM_SCHED_INHERIT_DEFINED
#define __PTHREAD_ENUM_SCHED_INHERIT_DEFINED 1
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
#endif /* !__PTHREAD_ENUM_SCHED_INHERIT_DEFINED */

/* Scope handling. */
#ifndef __PTHREAD_ENUM_SCOPE_DEFINED
#define __PTHREAD_ENUM_SCOPE_DEFINED 1
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
#endif /* !__PTHREAD_ENUM_SCOPE_DEFINED */


/* Process shared or private flag. */
#ifndef __PTHREAD_ENUM_PROCESS_SHARED_DEFINED
#define __PTHREAD_ENUM_PROCESS_SHARED_DEFINED 1
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
#endif /* __PTHREAD_PROCESS_PRIVATE || __PTHREAD_PROCESS_SHARED */
#endif /* !__PTHREAD_ENUM_PROCESS_SHARED_DEFINED */


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
/* Special value returned by 'pthread_barrier_wait' for one of the threads
 * after  the  required  number  of  threads  have  called  this function. */
#ifdef __PTHREAD_BARRIER_SERIAL_THREAD
#define PTHREAD_BARRIER_SERIAL_THREAD __PTHREAD_BARRIER_SERIAL_THREAD
#endif /* __PTHREAD_BARRIER_SERIAL_THREAD */
#endif /* __USE_XOPEN2K */



#ifdef __CC__

/* Static initializer for `pthread_mutex_t'. */
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

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)

/* Static initializer for `pthread_rwlock_t'. */
#ifdef __PTHREAD_RWLOCK_INITIALIZER
#define PTHREAD_RWLOCK_INITIALIZER __PTHREAD_RWLOCK_INITIALIZER
#endif /* __PTHREAD_RWLOCK_INITIALIZER */
#ifdef __USE_GNU
#ifdef __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER
#define PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER
#endif /* __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER */
#endif /* __USE_GNU */
#endif  /* __USE_UNIX98 || __USE_XOPEN2K */

/* Static initializer for `pthread_cond_t'. */
#ifdef __PTHREAD_COND_INITIALIZER
#define PTHREAD_COND_INITIALIZER __PTHREAD_COND_INITIALIZER
#endif /* __PTHREAD_COND_INITIALIZER */

/* Cleanup callback buffers */
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

#ifndef __pthread_t_defined
#define __pthread_t_defined 1
typedef __pthread_t pthread_t;
#endif /* !__pthread_t_defined */
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined 1
typedef __pthread_attr_t pthread_attr_t;
#endif /* !__pthread_attr_t_defined */
#ifndef __pthread_mutex_t_defined
#define __pthread_mutex_t_defined 1
typedef __pthread_mutex_t pthread_mutex_t;
#endif /* !__pthread_mutex_t_defined */
#ifndef __pthread_mutexattr_t_defined
#define __pthread_mutexattr_t_defined 1
typedef __pthread_mutexattr_t pthread_mutexattr_t;
#endif /* !__pthread_mutexattr_t_defined */
#ifndef __pthread_cond_t_defined
#define __pthread_cond_t_defined 1
typedef __pthread_cond_t pthread_cond_t;
#endif /* !__pthread_cond_t_defined */
#ifndef __pthread_condattr_t_defined
#define __pthread_condattr_t_defined 1
typedef __pthread_condattr_t pthread_condattr_t;
#endif /* !__pthread_condattr_t_defined */
#ifndef __pthread_key_t_defined
#define __pthread_key_t_defined 1
typedef __pthread_key_t pthread_key_t;
#endif /* !__pthread_key_t_defined */
#ifndef __pthread_once_t_defined
#define __pthread_once_t_defined 1
typedef __pthread_once_t pthread_once_t;
#endif /* !__pthread_once_t_defined */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifndef __pthread_rwlock_t_defined
#define __pthread_rwlock_t_defined 1
typedef __pthread_rwlock_t pthread_rwlock_t;
#endif /* !__pthread_rwlock_t_defined */
#ifndef __pthread_rwlockattr_t_defined
#define __pthread_rwlockattr_t_defined 1
typedef __pthread_rwlockattr_t pthread_rwlockattr_t;
#endif /* !__pthread_rwlockattr_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_XOPEN2K
#ifndef __pthread_spinlock_t_defined
#define __pthread_spinlock_t_defined 1
typedef __pthread_spinlock_t pthread_spinlock_t;
#endif /* !__pthread_spinlock_t_defined */
#ifndef __pthread_barrier_t_defined
#define __pthread_barrier_t_defined 1
typedef __pthread_barrier_t pthread_barrier_t;
#endif /* !__pthread_barrier_t_defined */
#ifndef __pthread_barrierattr_t_defined
#define __pthread_barrierattr_t_defined 1
typedef __pthread_barrierattr_t pthread_barrierattr_t;
#endif /* !__pthread_barrierattr_t_defined */
#endif /* __USE_XOPEN2K */


}

%[define_type_class(__pthread_start_routine_t = "TP")]
%[define(DEFINE_PTHREAD_START_ROUTINE_T =
@@pp_ifndef ____pthread_start_routine_t_defined@@
#define ____pthread_start_routine_t_defined 1
typedef void *(__LIBKCALL *__pthread_start_routine_t)(void *);
@@pp_endif@@
)]

@@>> pthread_create(3)
@@Create a new thread, starting with execution of START-ROUTINE
@@getting passed ARG. Creation attributed come from ATTR. The new
@@handle is stored in *NEWTHREAD
@@@return: EOK:    Success
@@@return: EAGAIN: Insufficient resources, or operation-not-permitted
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[decl_prefix(DEFINE_PTHREAD_START_ROUTINE_T)]]
$errno_t pthread_create([[nonnull]] pthread_t *__restrict newthread, pthread_attr_t const *__restrict attr,
                        [[nonnull]] __pthread_start_routine_t start_routine, void *__restrict arg);

@@>> pthread_exit(3)
@@Terminate calling thread.
@@The registered cleanup handlers are called via exception handling
[[throws, noreturn]]
void pthread_exit(void *retval);

@@>> pthread_join(3)
@@Make calling thread wait for termination of the thread THREAD. The
@@exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
@@is not NULL
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_join(pthread_t pthread, void **thread_return);

%#ifdef __USE_GNU
@@>> pthread_tryjoin_np(3)
@@Check whether thread THREAD has terminated. If yes return the status of
@@the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL
@@@return: EOK:   Success
@@@return: EBUSY: The thread has yet to terminate
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_tryjoin_np(pthread_t pthread, void **thread_return);

%struct timespec;
@@>> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
@@Make calling thread wait for termination of the thread THREAD, but only
@@until TIMEOUT. The exit status of the thread is stored in
@@*THREAD_RETURN, if THREAD_RETURN is not NULL.
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
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
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_timedjoin32_np(pthread_t pthread, void **thread_return,
                                struct timespec32 const *abstime);


[[cp, time64_variant_of(pthread_timedjoin_np), doc_alias(pthread_timedjoin_np)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
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

@@>> pthread_detach(3)
@@Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
@@The resources of THREAD will therefore be freed immediately when it
@@terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_detach(pthread_t pthread);

@@>> pthread_self(3)
@@Obtain the identifier of the current thread
@@@return: * : Handle for the calling thread
[[const, nothrow, export_alias("thrd_current")]]
pthread_t pthread_self();

@@>> pthread_equal(3)
@@Compare two thread identifiers
@@@return: 0 : Given threads are non-equal
@@@return: * : Given threads are equal
[[extern_inline, const, nothrow, export_alias("thrd_equal")]]
[[decl_include("<bits/crt/pthreadtypes.h>")]]
int pthread_equal(pthread_t thr1, pthread_t thr2) {
	return thr1 == thr2;
}

%
%/* Thread attribute handling. */
%
@@>> pthread_attr_init(3)
@@Initialize thread attribute *ATTR with default attributes (detachstate is
@@PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack)
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_init([[nonnull]] pthread_attr_t *attr);

@@>> pthread_attr_destroy(3)
@@Destroy thread attribute *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_destroy([[nonnull]] pthread_attr_t *attr);

@@>> pthread_attr_getdetachstate(3)
@@Get detach state attribute
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getdetachstate([[nonnull]] pthread_attr_t const *attr,
                                     [[nonnull]] int *detachstate);

@@>> pthread_attr_setdetachstate(3)
@@Set detach state attribute
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `detachstate'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setdetachstate([[nonnull]] pthread_attr_t *attr, int detachstate);

@@>> pthread_attr_getguardsize(3)
@@Get the size of the guard area created for stack overflow protection
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getguardsize([[nonnull]] pthread_attr_t const *attr,
                                   [[nonnull]] size_t *guardsize);

@@>> pthread_attr_setguardsize(3)
@@Set the size of the guard area created for stack overflow protection
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setguardsize([[nonnull]] pthread_attr_t *attr, size_t guardsize);

@@>> pthread_attr_getschedparam(3)
@@Return in *PARAM the scheduling parameters of *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getschedparam([[nonnull]] pthread_attr_t const *__restrict attr,
                                    [[nonnull]] struct sched_param *__restrict param);

@@>> pthread_attr_setschedparam(3)
@@Set scheduling parameters (priority, etc) in *ATTR according to PARAM
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `param'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setschedparam([[nonnull]] pthread_attr_t *__restrict attr,
                                    [[nonnull]] struct sched_param const *__restrict param);

@@>> pthread_attr_getschedpolicy(3)
@@Return in *POLICY the scheduling policy of *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getschedpolicy([[nonnull]] pthread_attr_t const *__restrict attr,
                                     [[nonnull]] int *__restrict policy);

@@>> pthread_attr_setschedpolicy(3)
@@Set scheduling policy in *ATTR according to POLICY
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `policy'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setschedpolicy([[nonnull]] pthread_attr_t *attr, int policy);

@@>> pthread_attr_getinheritsched(3)
@@Return in *INHERIT the scheduling inheritance mode of *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getinheritsched([[nonnull]] pthread_attr_t const *__restrict attr,
                                      [[nonnull]] int *__restrict inherit);

@@>> pthread_attr_setinheritsched(3)
@@Set scheduling inheritance mode in *ATTR according to INHERIT
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `inherit'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setinheritsched([[nonnull]] pthread_attr_t *attr, int inherit);

@@>> pthread_attr_getscope(3)
@@Return in *SCOPE the scheduling contention scope of *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getscope([[nonnull]] pthread_attr_t const *__restrict attr,
                               [[nonnull]] int *__restrict scope);

@@>> pthread_attr_setscope(3)
@@Set scheduling contention scope in *ATTR according to SCOPE
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `scope'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setscope([[nonnull]] pthread_attr_t *attr, int scope);

@@>> pthread_attr_getstackaddr(3)
@@Return the previously set address for the stack
@@@return: EOK: Success
[[deprecated("Use pthread_attr_getstack()")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getstackaddr([[nonnull]] pthread_attr_t const *__restrict attr,
                                   [[nonnull]] void **__restrict stackaddr);


@@>> pthread_attr_setstackaddr(3)
@@Set the starting address of the stack of the thread to be created.
@@Depending on whether the stack grows up or down the value must either
@@be higher or lower than all the address in the memory block. The
@@minimal size of the block must be PTHREAD_STACK_MIN
@@@return: EOK:    Success
@@@return: EINVAL: The stack isn't suitably aligned
[[deprecated("Use pthread_attr_setstack()")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setstackaddr([[nonnull]] pthread_attr_t *attr, void *stackaddr);

@@>> pthread_attr_getstacksize(3)
@@Return the currently used minimal stack size
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getstacksize([[nonnull]] pthread_attr_t const *__restrict attr,
                                   [[nonnull]] size_t *__restrict stacksize);

@@>> pthread_attr_setstacksize(3)
@@Add information about the minimum stack size needed for the thread
@@to be started. This size must never be less than PTHREAD_STACK_MIN
@@and must also not exceed the system limits
@@@return: EOK:    Success
@@@return: EINVAL: `stacksize' is too small
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setstacksize([[nonnull]] pthread_attr_t *attr, size_t stacksize);

%#ifdef __USE_XOPEN2K
@@>> pthread_attr_getstack(3)
@@Return the previously set address for the stack
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getstack([[nonnull]] pthread_attr_t const *__restrict attr,
                               [[nonnull]] void **__restrict stackaddr,
                               [[nonnull]] size_t *__restrict stacksize);

@@>> pthread_attr_setstack(3)
@@The following two interfaces are intended to replace the last two. They
@@require setting the address as well as the size since only setting the
@@address will make the implementation on some architectures impossible
@@@return: EOK:    Success
@@@return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setstack([[nonnull]] pthread_attr_t *attr, void *stackaddr, size_t stacksize);
%#endif /* __USE_XOPEN2K */

%#ifdef __USE_GNU
@@>> pthread_attr_setaffinity_np(3)
@@Thread created with attribute ATTR will be limited to run only on
@@the processors represented in CPUSET
@@@return: EOK:    Success
@@@return: EINVAL: The given set contains a non-existant CPU
@@@return: ENOMEM: Insufficient memory
[[decl_include("<bits/types.h>", "<bits/os/cpu_set.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setaffinity_np([[nonnull]] pthread_attr_t *attr, size_t cpusetsize,
                                     [[nonnull]] cpu_set_t const *cpuset);

@@>> pthread_attr_getaffinity_np(3)
@@Get bit set in CPUSET representing the processors threads created with ATTR can run on
@@@return: EOK:    Success
@@@return: EINVAL: `cpusetsize' is too small
[[decl_include("<bits/types.h>", "<bits/os/cpu_set.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getaffinity_np([[nonnull]] pthread_attr_t const *attr, size_t cpusetsize,
                                     [[nonnull]] cpu_set_t *cpuset);

@@>> pthread_getattr_default_np(3)
@@Get the default attributes used by pthread_create in this process
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getattr_default_np([[nonnull]] pthread_attr_t *attr);

@@>> pthread_setattr_default_np(3)
@@Set the default attributes to be used by pthread_create in this process
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setattr_default_np([[nonnull]] pthread_attr_t const *attr);

@@>> pthread_getattr_np(3)
@@Initialize thread attribute *ATTR with attributes corresponding to the
@@already running thread THREAD. It shall be called on uninitialized ATTR
@@and destroyed with pthread_attr_destroy when no longer needed
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getattr_np(pthread_t pthread, [[nonnull]] pthread_attr_t *attr);
%#endif /* __USE_GNU */

%
%/* Functions for scheduling control. */
%
@@>> pthread_gettid_np(3)
@@Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM
@@@return: EOK:    Success
@@@return: EPERM:  The caller isn't allowed to specify `policy' and `param'
@@@return: ESRCH:  `pthread' has already exited
@@@return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setschedparam(pthread_t target_thread, int policy,
                               [[nonnull]] struct sched_param const *param);

@@>> pthread_gettid_np(3)
@@Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getschedparam(pthread_t target_thread,
                               [[nonnull]] int *__restrict policy,
                               [[nonnull]] struct sched_param *__restrict param);

@@>> pthread_gettid_np(3)
@@Set the scheduling priority for TARGET_THREAD
@@@return: EOK:    Success
@@@return: EPERM:  The caller isn't allowed to specify `prio'
@@@return: ESRCH:  `pthread' has already exited
@@@return: EINVAL: Invalid/unsupported `prio'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setschedprio(pthread_t target_thread, int prio);


%#ifdef __USE_GNU
@@>> pthread_gettid_np(3)
@@Get thread name visible in the kernel and its interfaces
@@@return: EOK:    Success
@@@return: ERANGE: The given `buflen' is too small
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getname_np(pthread_t target_thread,
                            [[outp(buflen)]] char *buf,
                            size_t buflen);

@@>> pthread_gettid_np(3)
@@Set thread name visible in the kernel and its interfaces
@@@return: EOK:    Success
@@@return: ERANGE: The given `name' is too long
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setname_np(pthread_t target_thread,
                            [[nonnull]] const char *name);
%#endif /* __USE_GNU */


%#ifdef __USE_KOS
@@>> pthread_gettid_np(3)
@@Return the TID of the given `target_thread'.
@@If the given `target_thread' has already terminated, 0 is returned
@@@return: * : The PID OF the given thread
@@@return: 0 : The given `target_thread' has already terminated
[[guard, wunused, pure]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$pid_t pthread_gettid_np(pthread_t target_thread);
%#endif /* __USE_KOS */


%#ifdef __USE_UNIX98
@@>> pthread_getconcurrency(3)
@@Determine level of concurrency
@@@return: * : The current concurrency level
[[pure]] int pthread_getconcurrency();

@@>> pthread_setconcurrency(3)
@@Set new concurrency level to LEVEL
@@@return: EOK:    Success
@@@return: EINVAL: The given `level' is negative
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setconcurrency(int level);
%#endif /* __USE_UNIX98 */

%#ifdef __USE_GNU
@@>> pthread_yield(3), thrd_yield(3), sched_yield(2)
@@Yield the processor to another thread or process.
@@This function is similar to the POSIX `sched_yield' function but
@@might be differently implemented in the case of a m-on-n thread
@@implementation
@@@return: EOK: Success
[[decl_include("<bits/types.h>")]]
$errno_t pthread_yield(void) = sched_yield;

@@>> pthread_setaffinity_np(3)
@@Limit specified thread THREAD to run only on the processors represented in CPUSET
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/os/cpu_set.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setaffinity_np(pthread_t pthread, size_t cpusetsize,
                                [[nonnull]] cpu_set_t const *cpuset);

@@>> pthread_getaffinity_np(3)
@@Get bit set in CPUSET representing the processors THREAD can run on
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/os/cpu_set.h>", "<bits/crt/pthreadtypes.h>")]]
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

@@>> pthread_once(3)
@@Guarantee that the initialization function INIT_ROUTINE will be called
@@only once, even if pthread_once is executed several times with the
@@same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
@@extern variable initialized to PTHREAD_ONCE_INIT.
@@@return: EOK: Success
[[throws, export_alias("call_once")]]
[[decl_prefix(DEFINE_PTHREAD_ONCE_ROUTINE_T)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[impl_include("<asm/crt/pthreadvalues.h>", "<hybrid/__atomic.h>", "<hybrid/sched/__yield.h>")]]
$errno_t pthread_once([[nonnull]] pthread_once_t *once_control,
                      [[nonnull]] __pthread_once_routine_t init_routine) {
	pthread_once_t status;
	status = __hybrid_atomic_cmpxch_val(*once_control,
	                                    __PTHREAD_ONCE_INIT,
	                                    __PTHREAD_ONCE_INIT + 1,
	                                    __ATOMIC_SEQ_CST,
	                                    __ATOMIC_SEQ_CST);
	if (status == __PTHREAD_ONCE_INIT) {
		(*init_routine)();
		__hybrid_atomic_store(*once_control,
		                      __PTHREAD_ONCE_INIT + 2,
		                      __ATOMIC_RELEASE);
	} else if (status != __PTHREAD_ONCE_INIT + 2) {
		/* Wait for some other thread to finish init_routine() */
		do {
			__hybrid_yield();
		} while (__hybrid_atomic_load(*once_control, __ATOMIC_ACQUIRE) !=
		         __PTHREAD_ONCE_INIT + 2);
	}
	return 0;
}

%
%/* Functions for handling cancellation.
% * Note that these functions are explicitly not marked to not throw an
% * exception in C++ code. If cancellation is implemented by unwinding
% * this is necessary to have the compiler generate the unwind information. */


@@>> pthread_setcancelstate(3)
@@Set cancelability state of current thread to STATE,
@@returning old state in *OLDSTATE if OLDSTATE is not NULL
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `state'
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setcancelstate(int state, [[nullable]] int *oldstate);

@@>> pthread_setcanceltype(3)
@@Set cancellation state of current thread to TYPE,
@@returning the old type in *OLDTYPE if OLDTYPE is not NULL
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `type'
[[guard, decl_include("<bits/types.h>")]]
$errno_t pthread_setcanceltype(int type, [[nullable]] int *oldtype);

@@>> pthread_cancel(3)
@@Cancel THREAD immediately or at the next possibility
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_cancel(pthread_t pthread);

@@>> pthread_testcancel(3)
@@Test for pending cancellation for the current thread and terminate
@@the thread as per pthread_exit(PTHREAD_CANCELED) if it has been canceled
[[cp]]
void pthread_testcancel();


%
%/* Cancellation handling with integration into exception handling. */

%{
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
 * be called with arguments  ARG when the matching  pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used  in  matching  pairs  at the  same  nesting  level  of  braces. */
#define pthread_cleanup_push(routine, arg) \
	do {                                   \
		__pthread_cleanup_class __clframe(routine, arg)

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If   EXECUTE   is   non-zero,   the   handler   function   is    called. */
#define pthread_cleanup_pop(execute)  \
		__clframe.__setdoit(execute); \
	} __WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the  current cancellation  type and  sets it  to  deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)      \
	do {                                                 \
		__pthread_cleanup_class __clframe(routine, arg); \
		__clframe.__defer()

/* Remove a  cleanup handler  as  pthread_cleanup_pop does,  but  also
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
[[extern_inline]]
void __pthread_cleanup_routine([[nonnull]] struct __pthread_cleanup_frame *frame) {
	if (frame->__do_it)
		(*frame->__cancel_routine)(frame->__cancel_arg);
}

%{
/* Install a cleanup handler: ROUTINE will be called with arguments ARG
 * when the thread is canceled or calls pthread_exit. ROUTINE will also
 * be called with arguments  ARG when the matching  pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used  in  matching  pairs  at the  same  nesting  level  of  braces. */
#define pthread_cleanup_push(routine, arg)                          \
	do {                                                            \
		struct __pthread_cleanup_frame __clframe                    \
		__attribute__((__cleanup__(__pthread_cleanup_routine))) = { \
			.__cancel_routine = (routine),                          \
			.__cancel_arg = (arg),                                  \
			.__do_it = 1                                            \
		};

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If   EXECUTE   is   non-zero,   the   handler   function   is    called. */
#define pthread_cleanup_pop(execute)   \
		__clframe.__do_it = (execute); \
	} __WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the  current cancellation  type and  sets it  to  deferred
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

/* Remove a  cleanup handler  as  pthread_cleanup_pop does,  but  also
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
void __pthread_register_cancel(__pthread_unwind_buf_t *buf);

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
%
%/************************************************************************/
%/* pthread_mutex_t                                                      */
%/************************************************************************/
%

@@>> pthread_mutex_init(3)
@@Initialize a mutex
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_init([[nonnull]] pthread_mutex_t *mutex,
                            pthread_mutexattr_t const *mutexattr);

@@>> pthread_mutex_destroy(3)
@@Destroy a mutex
@@@return: EOK: Success
[[export_alias("mtx_destroy")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_destroy([[nonnull]] pthread_mutex_t *mutex);

@@>> pthread_mutex_trylock(3)
@@Try locking a mutex
@@@return: EOK:   Success
@@@return: EBUSY: The mutex has already been locked
@@                In case of a recursive mutex, another
@@                thread was the one to acquire the lock.
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_trylock([[nonnull]] pthread_mutex_t *mutex);

@@>> pthread_mutex_lock(3)
@@Lock a mutex
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_lock([[nonnull]] pthread_mutex_t *mutex);

%#ifdef __USE_XOPEN2K
@@>> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
@@Wait until lock becomes available, or specified time passes
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, wunused, userimpl, no_crt_self_import]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(pthread_mutex_timedlock64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(pthread_mutex_timedlock)]]
[[requires($has_function(pthread_mutex_timedlock32) ||
           $has_function(pthread_mutex_timedlock64))]]
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
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_mutex_timedlock32([[nonnull]] pthread_mutex_t *__restrict mutex,
                                   [[nonnull]] struct timespec const *__restrict abstime);

[[cp, doc_alias(pthread_mutex_timedlock), time64_variant_of(pthread_mutex_timedlock)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires($has_function(pthread_mutex_timedlock32))]]
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

%#ifdef __USE_SOLARIS
@@>> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
@@Wait until lock becomes available, or specified amount of time has passed
@@@return: EOK:       Success
@@@return: EINVAL:    The given `reltime' is invalid
@@@return: ETIMEDOUT: The given `reltime' has expired
[[cp, wunused, userimpl, no_crt_self_import]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(pthread_mutex_reltimedlock64_np)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(pthread_mutex_reltimedlock_np)]]
[[requires($has_function(pthread_mutex_reltimedlock32_np) ||
           $has_function(pthread_mutex_reltimedlock64_np))]]
$errno_t pthread_mutex_reltimedlock_np([[nonnull]] pthread_mutex_t *__restrict mutex,
                                       [[nonnull]] struct timespec const *__restrict reltime) {
@@pp_if $has_function(pthread_mutex_reltimedlock32_np)@@
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_mutex_reltimedlock32_np(mutex, &reltime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 reltime64;
	reltime64.tv_sec  = (time64_t)reltime->tv_sec;
	reltime64.tv_nsec = reltime->tv_nsec;
	result = pthread_mutex_reltimedlock64_np(mutex, &reltime64);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, doc_alias(pthread_mutex_reltimedlock_np), ignore, nocrt, alias(pthread_mutex_reltimedlock_np)]]
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_mutex_reltimedlock32_np([[nonnull]] pthread_mutex_t *__restrict mutex,
                                         [[nonnull]] struct timespec const *__restrict reltime);

[[cp, doc_alias(pthread_mutex_reltimedlock_np), time64_variant_of(pthread_mutex_reltimedlock_np)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires($has_function(pthread_mutex_reltimedlock32_np))]]
$errno_t pthread_mutex_reltimedlock64_np([[nonnull]] pthread_mutex_t *__restrict mutex,
                                         [[nonnull]] struct timespec64 const *__restrict reltime) {
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_mutex_reltimedlock32_np(mutex, &reltime32);
	return result;
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_SOLARIS */



@@>> pthread_mutex_unlock(3)
@@Unlock a mutex
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_unlock([[nonnull]] pthread_mutex_t *mutex);

@@>> pthread_mutex_getprioceiling(3)
@@Get the priority ceiling of `mutex'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_getprioceiling([[nonnull]] pthread_mutex_t const *__restrict mutex,
                                      [[nonnull]] int *__restrict prioceiling);

@@>> pthread_mutex_setprioceiling(3)
@@Set the priority ceiling of `mutex' to PRIOCEILING,
@@return old priority ceiling value in *OLD_CEILING
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `prioceiling'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_setprioceiling([[nonnull]] pthread_mutex_t *__restrict mutex, int prioceiling,
                                      [[nullable]] int *__restrict old_ceiling);

%#ifdef __USE_XOPEN2K8
@@>> pthread_mutex_consistent(3)
@@Declare the state protected by `mutex' as consistent
@@@return: EOK:    Success
@@@return: EINVAL: Not a robust mutex
@@@return: EINVAL: Mutex was already in a consistent state
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[export_alias("pthread_mutex_consistent_np")]]
$errno_t pthread_mutex_consistent([[nonnull]] pthread_mutex_t *mutex);

%#ifdef __USE_GNU
%[insert:function(pthread_mutex_consistent_np = pthread_mutex_consistent)]
%#endif /* __USE_GNU */
%#endif /* __USE_XOPEN2K8 */

%
%
%/************************************************************************/
%/* pthread_mutexattr_t                                                  */
%/************************************************************************/
%

@@>> pthread_mutexattr_init(3)
@@Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP)
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_init([[nonnull]] pthread_mutexattr_t *attr);


@@>> pthread_mutexattr_destroy(3)
@@Destroy mutex attribute object ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_destroy([[nonnull]] pthread_mutexattr_t *attr);

@@>> pthread_mutexattr_getpshared(3)
@@Get the process-shared flag of the mutex attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_getpshared([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                      [[nonnull]] int *__restrict pshared);

@@>> pthread_mutexattr_setpshared(3)
@@Set the process-shared flag of the mutex attribute ATTR
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `pshared'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_setpshared([[nonnull]] pthread_mutexattr_t *attr, int pshared);


%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
@@>> pthread_mutexattr_gettype(3)
@@Return in *KIND the mutex kind attribute in *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_gettype([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                   [[nonnull]] int *__restrict kind);

@@>> pthread_mutexattr_settype(3)
@@Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
@@PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT)
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `kind'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_settype([[nonnull]] pthread_mutexattr_t *attr, int kind);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

@@>> pthread_mutexattr_getprotocol(3)
@@Return in *PROTOCOL the mutex protocol attribute in *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_getprotocol([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                       [[nonnull]] int *__restrict protocol);

@@>> pthread_mutexattr_setprotocol(3)
@@Set the mutex protocol attribute in *ATTR to PROTOCOL (either
@@PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT)
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `protocol'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_setprotocol([[nonnull]] pthread_mutexattr_t *attr, int protocol);

@@>> pthread_mutexattr_getprioceiling(3)
@@Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_getprioceiling([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                          [[nonnull]] int *__restrict prioceiling);

@@>> pthread_mutexattr_setprioceiling(3)
@@Set the mutex prioceiling attribute in *ATTR to PRIOCEILING
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `prioceiling'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_setprioceiling([[nonnull]] pthread_mutexattr_t *attr, int prioceiling);

%#ifdef __USE_XOPEN2K
@@>> pthread_mutexattr_getrobust(3)
@@Get the robustness flag of the mutex attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[export_alias("pthread_mutexattr_getrobust_np")]]
$errno_t pthread_mutexattr_getrobust([[nonnull]] pthread_mutexattr_t const *attr,
                                     [[nonnull]] int *robustness);

@@>> pthread_mutexattr_setrobust(3)
@@Set the robustness flag of the mutex attribute ATTR
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `robustness'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[export_alias("pthread_mutexattr_setrobust_np")]]
$errno_t pthread_mutexattr_setrobust([[nonnull]] pthread_mutexattr_t *attr, int robustness);
%#endif /* __USE_XOPEN2K */

%#ifdef __USE_GNU
%[insert:function(pthread_mutexattr_getrobust_np = pthread_mutexattr_getrobust)]
%[insert:function(pthread_mutexattr_setrobust_np = pthread_mutexattr_setrobust)]
%#endif /* __USE_GNU */


%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)

%
%
%/************************************************************************/
%/* pthread_rwlock_t                                                     */
%/************************************************************************/
%

@@>> pthread_rwlock_init(3)
@@Initialize read-write lock RWLOCK using attributes ATTR,
@@or use the default values if later is NULL
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_init([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                             pthread_rwlockattr_t const *__restrict attr);

@@>> pthread_rwlock_destroy(3)
@@Destroy read-write lock RWLOCK
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_destroy([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_rdlock(3)
@@Acquire read lock for RWLOCK
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_rdlock([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_tryrdlock(3)
@@Try to acquire read lock for RWLOCK
@@@return: EOK:   Success
@@@return: EBUSY: A read-lock cannot be acquired at the moment,
@@                because a write-lock is already being held.
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_tryrdlock([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_wrlock(3)
@@Acquire write lock for RWLOCK
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_wrlock([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_trywrlock(3)
@@Try to acquire write lock for RWLOCK
@@@return: EOK:   Success
@@@return: EBUSY: A write-lock cannot be acquired at the moment,
@@                because read-locks are already being held.
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_trywrlock([[nonnull]] pthread_rwlock_t *rwlock);

%#ifdef __USE_XOPEN2K
@@>> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
@@Try to acquire read lock for `rwlock' or return after the specified time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, userimpl, wunused, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedrdlock64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedrdlock")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[requires($has_function(pthread_rwlock_timedrdlock32) ||
           $has_function(pthread_rwlock_timedrdlock64))]]
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

@@>> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
@@Try to acquire write lock for `rwlock' or return after the specified time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, wunused, userimpl, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedwrlock64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_timedwrlock")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[requires($has_function(pthread_rwlock_timedwrlock32) ||
           $has_function(pthread_rwlock_timedwrlock64))]]
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
[[cp, doc_alias(pthread_rwlock_timedrdlock), ignore, nocrt, alias("pthread_rwlock_timedrdlock")]]
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_timedrdlock32([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec32 const *__restrict abstime);
[[cp, doc_alias(pthread_rwlock_timedwrlock), wunused, ignore, nocrt, alias("pthread_rwlock_timedwrlock")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_timedwrlock32([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec32 const *__restrict abstime);

[[cp, doc_alias(pthread_rwlock_timedrdlock), time64_variant_of(pthread_rwlock_timedrdlock)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires_function(pthread_rwlock_timedrdlock32)]]
$errno_t pthread_rwlock_timedrdlock64([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec64 const *__restrict abstime) {
	$errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = pthread_rwlock_timedrdlock32(rwlock, &abstime32);
	return result;
}

[[cp, doc_alias(pthread_rwlock_timedwrlock), time64_variant_of(pthread_rwlock_timedwrlock)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires_function(pthread_rwlock_timedwrlock32)]]
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

%#ifdef __USE_SOLARIS
@@>> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
@@Try to acquire read lock for `rwlock' or return after the specified time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `reltime' is invalid
@@@return: ETIMEDOUT: The given `reltime' has expired
[[cp, userimpl, wunused, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_reltimedrdlock64_np")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_reltimedrdlock_np")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[requires($has_function(pthread_rwlock_reltimedrdlock32_np) ||
           $has_function(pthread_rwlock_reltimedrdlock64_np))]]
$errno_t pthread_rwlock_reltimedrdlock_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                          [[nonnull]] struct timespec const *__restrict reltime) {
@@pp_if $has_function(pthread_rwlock_reltimedrdlock32_np)@@
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_rwlock_reltimedrdlock32_np(rwlock, &reltime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 reltime64;
	reltime64.tv_sec  = (time64_t)reltime->tv_sec;
	reltime64.tv_nsec = reltime->tv_nsec;
	result = pthread_rwlock_reltimedrdlock64_np(rwlock, &reltime32);
	return result;
@@pp_endif@@
}

@@>> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
@@Try to acquire write lock for `rwlock' or return after the specified time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `reltime' is invalid
@@@return: ETIMEDOUT: The given `reltime' has expired
[[cp, wunused, userimpl, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_reltimedwrlock64_np")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pthread_rwlock_reltimedwrlock_np")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[requires($has_function(pthread_rwlock_reltimedwrlock32_np) ||
           $has_function(pthread_rwlock_reltimedwrlock64_np))]]
$errno_t pthread_rwlock_reltimedwrlock_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                          [[nonnull]] struct timespec const *__restrict reltime) {
@@pp_if $has_function(pthread_rwlock_reltimedwrlock32_np)@@
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_rwlock_reltimedwrlock32_np(rwlock, &reltime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 reltime64;
	reltime64.tv_sec  = (time64_t)reltime->tv_sec;
	reltime64.tv_nsec = reltime->tv_nsec;
	result = pthread_rwlock_reltimedwrlock64_np(rwlock, &reltime32);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, doc_alias(pthread_rwlock_reltimedrdlock_np), ignore, nocrt, alias("pthread_rwlock_reltimedrdlock_np")]]
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_reltimedrdlock32_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                            [[nonnull]] struct timespec32 const *__restrict reltime);
[[cp, doc_alias(pthread_rwlock_reltimedwrlock_np), wunused, ignore, nocrt, alias("pthread_rwlock_reltimedwrlock_np")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_reltimedwrlock32_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                            [[nonnull]] struct timespec32 const *__restrict reltime);

[[cp, doc_alias(pthread_rwlock_reltimedrdlock_np), time64_variant_of(pthread_rwlock_reltimedrdlock_np)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires_function(pthread_rwlock_reltimedrdlock32_np)]]
$errno_t pthread_rwlock_reltimedrdlock64_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                            [[nonnull]] struct timespec64 const *__restrict reltime) {
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_rwlock_reltimedrdlock32_np(rwlock, &reltime32);
	return result;
}

[[cp, doc_alias(pthread_rwlock_reltimedwrlock_np), time64_variant_of(pthread_rwlock_reltimedwrlock_np)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires_function(pthread_rwlock_reltimedwrlock32_np)]]
$errno_t pthread_rwlock_reltimedwrlock64_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                            [[nonnull]] struct timespec64 const *__restrict reltime) {
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_rwlock_reltimedwrlock32_np(rwlock, &reltime32);
	return result;
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_SOLARIS */

@@>> pthread_rwlock_unlock(3)
@@Unlock RWLOCK
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_unlock([[nonnull]] pthread_rwlock_t *rwlock);

%
%
%/************************************************************************/
%/* pthread_rwlockattr_t                                                 */
%/************************************************************************/
%

@@>> pthread_rwlockattr_init(3)
@@Initialize attribute object ATTR with default values
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_init([[nonnull]] pthread_rwlockattr_t *attr);

@@>> pthread_rwlockattr_destroy(3)
@@Destroy attribute object ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_destroy([[nonnull]] pthread_rwlockattr_t *attr);

@@>> pthread_rwlockattr_getpshared(3)
@@Return current setting of process-shared attribute of ATTR in PSHARED
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_getpshared([[nonnull]] pthread_rwlockattr_t const *__restrict attr,
                                       [[nonnull]] int *__restrict pshared);

@@>> pthread_rwlockattr_setpshared(3)
@@Set process-shared attribute of ATTR to PSHARED
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `pthread'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_setpshared([[nonnull]] pthread_rwlockattr_t *attr, int pshared);

@@>> pthread_rwlockattr_getkind_np(3)
@@Return current setting of reader/writer preference
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_getkind_np([[nonnull]] pthread_rwlockattr_t const *__restrict attr,
                                       [[nonnull]] int *__restrict pref);

@@>> pthread_rwlockattr_setkind_np(3)
@@Set reader/write preference
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `pref'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_setkind_np([[nonnull]] pthread_rwlockattr_t *attr, int pref);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%
%/************************************************************************/
%/* pthread_cond_t                                                       */
%/************************************************************************/
%

@@>> pthread_cond_init(3)
@@Initialize condition variable `cond' using attributes
@@ATTR, or use the default values if later is NULL
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_cond_init([[nonnull]] pthread_cond_t *__restrict cond,
                           [[nullable]] pthread_condattr_t const *__restrict cond_attr);

@@>> pthread_cond_destroy(3)
@@Destroy condition variable `cond'
@@@return: EOK: Success
[[export_alias("cnd_destroy")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_cond_destroy([[nonnull]] pthread_cond_t *cond);

@@>> pthread_cond_signal(3)
@@Wake up one thread waiting for condition variable `cond'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_cond_signal([[nonnull]] pthread_cond_t *cond);

@@>> pthread_cond_broadcast(3)
@@Wake up all threads waiting for condition variables `cond'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_cond_broadcast([[nonnull]] pthread_cond_t *cond);

@@>> pthread_cond_wait(3)
@@Wait for condition variable `cond' to be signaled or broadcast.
@@`mutex' is assumed to be locked before.
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_cond_wait([[nonnull]] pthread_cond_t *__restrict cond,
                           [[nonnull]] pthread_mutex_t *__restrict mutex);

@@>> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
@@Wait for condition variable `cond' to be signaled or broadcast
@@until `abstime'. `mutex' is assumed to be locked before.
@@`abstime' is an absolute time specification; zero is the
@@beginning of the epoch (00:00:00 GMT, January 1, 1970).
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, wunused, userimpl, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(pthread_cond_timedwait64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(pthread_cond_timedwait)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[requires($has_function(pthread_cond_timedwait32) ||
           $has_function(pthread_cond_timedwait64))]]
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
[[cp, wunused, doc_alias(pthread_cond_timedwait)]]
[[ignore, nocrt, alias("pthread_cond_timedwait")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_cond_timedwait32([[nonnull]] pthread_cond_t *__restrict cond,
                                  [[nonnull]] pthread_mutex_t *__restrict mutex,
                                  [[nonnull]] struct timespec32 const *__restrict abstime);

[[cp, doc_alias(pthread_cond_timedwait), time64_variant_of(pthread_cond_timedwait)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires_function(pthread_cond_timedwait32)]]
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

%#ifdef __USE_SOLARIS
@@>> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
@@Wait for condition variable `cond' to be signaled or broadcast
@@until `reltime'. `mutex' is assumed to be locked before.
@@@return: EOK:       Success
@@@return: EINVAL:    The given `reltime' is invalid
@@@return: ETIMEDOUT: The given `reltime' has expired
[[cp, wunused, userimpl, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(pthread_cond_reltimedwait64_np)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(pthread_cond_reltimedwait_np)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[requires($has_function(pthread_cond_reltimedwait32_np) ||
           $has_function(pthread_cond_reltimedwait64_np))]]
$errno_t pthread_cond_reltimedwait_np([[nonnull]] pthread_cond_t *__restrict cond,
                                      [[nonnull]] pthread_mutex_t *__restrict mutex,
                                      [[nonnull]] struct timespec const *__restrict reltime) {
@@pp_if $has_function(pthread_cond_reltimedwait32_np)@@
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_cond_reltimedwait32_np(cond, mutex, &reltime32);
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 reltime64;
	reltime64.tv_sec  = (time64_t)reltime->tv_sec;
	reltime64.tv_nsec = reltime->tv_nsec;
	result = pthread_cond_reltimedwait64_np(cond, mutex, &reltime64);
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, wunused, doc_alias(pthread_cond_reltimedwait_np)]]
[[ignore, nocrt, alias("pthread_cond_reltimedwait_np")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_cond_reltimedwait32_np([[nonnull]] pthread_cond_t *__restrict cond,
                                        [[nonnull]] pthread_mutex_t *__restrict mutex,
                                        [[nonnull]] struct timespec32 const *__restrict reltime);

[[cp, doc_alias(pthread_cond_reltimedwait_np), time64_variant_of(pthread_cond_reltimedwait_np)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[wunused, userimpl, requires_function(pthread_cond_reltimedwait32_np)]]
$errno_t pthread_cond_reltimedwait64_np([[nonnull]] pthread_cond_t *__restrict cond,
                                        [[nonnull]] pthread_mutex_t *__restrict mutex,
                                        [[nonnull]] struct timespec64 const *__restrict reltime) {
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_cond_reltimedwait32_np(cond, mutex, &reltime32);
	return result;
}

%#endif /* __USE_TIME64 */
%#endif /* __USE_SOLARIS */


%
%
%/************************************************************************/
%/* pthread_condattr_t                                                   */
%/************************************************************************/
%

@@>> pthread_condattr_init(3)
@@Initialize condition variable attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_init([[nonnull]] pthread_condattr_t *attr);

@@>> pthread_condattr_destroy(3)
@@Destroy condition variable attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_destroy([[nonnull]] pthread_condattr_t *attr);

@@>> pthread_condattr_getpshared(3)
@@Get the process-shared flag of the condition variable attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_getpshared([[nonnull]] pthread_condattr_t const *__restrict attr,
                                     [[nonnull]] int *__restrict pshared);

@@>> pthread_condattr_setpshared(3)
@@Set the process-shared flag of the condition variable attribute ATTR
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `pshared'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_setpshared([[nonnull]] pthread_condattr_t *attr, int pshared);

%#ifdef __USE_XOPEN2K

@@>> pthread_condattr_getclock(3)
@@Get the clock selected for the condition variable attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_getclock([[nonnull]] pthread_condattr_t const *__restrict attr,
                                   [[nonnull]] $clockid_t *__restrict clock_id);

@@>> pthread_condattr_setclock(3)
@@Set the clock selected for the condition variable attribute ATTR
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `clock_id'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_setclock([[nonnull]] pthread_condattr_t *attr, $clockid_t clock_id);
%#endif /* __USE_XOPEN2K */

%
%
%#ifdef __USE_XOPEN2K
%/************************************************************************/
%/* pthread_spinlock_t                                                   */
%/************************************************************************/
%


@@>> pthread_spin_init(3)
@@Initialize the spinlock LOCK. If PSHARED is nonzero the
@@spinlock can be shared between different processes
@@@return: EOK: Success
[[impl_include("<hybrid/__atomic.h>")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_spin_init([[nonnull]] pthread_spinlock_t *lock, int pshared) {
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}

@@>> pthread_spin_destroy(3)
@@Destroy the spinlock LOCK
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_spin_destroy([[nonnull]] pthread_spinlock_t *lock) {
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}

@@>> pthread_spin_lock(3)
@@Wait until spinlock LOCK is retrieved
@@@return: EOK: Success
[[impl_include("<hybrid/__atomic.h>", "<hybrid/sched/__yield.h>")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_spin_lock([[nonnull]] pthread_spinlock_t *lock) {
	while (pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}

@@>> pthread_spin_trylock(3)
@@Try to lock spinlock LOCK
@@@return: EOK:   Success
@@@return: EBUSY: Lock has already been acquired
[[wunused, impl_include("<hybrid/__atomic.h>", "<libc/errno.h>")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
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

@@>> pthread_spin_unlock(3)
@@Release spinlock LOCK
@@@return: EOK: Success
[[impl_include("<hybrid/__atomic.h>")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_spin_unlock([[nonnull]] pthread_spinlock_t *lock) {
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELEASE);
	return 0;
}


%
%
%/************************************************************************/
%/* pthread_barrier_t                                                    */
%/************************************************************************/
%


@@>> pthread_barrier_init(3)
@@Initialize BARRIER with the attributes in ATTR.
@@The barrier is opened when COUNT waiters arrived
@@@return: EOK:    Success
@@@return: EINVAL: The given `count' is ZERO(0)
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrier_init([[nonnull]] pthread_barrier_t *__restrict barrier,
                              [[inp(count)]] pthread_barrierattr_t const *__restrict attr,
                              unsigned int count);

@@>> pthread_barrier_destroy(3)
@@Destroy a previously dynamically initialized barrier BARRIER
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrier_destroy([[nonnull]] pthread_barrier_t *barrier);

@@>> pthread_barrier_wait(3)
@@Wait on barrier BARRIER
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrier_wait([[nonnull]] pthread_barrier_t *barrier);

%
%
%/************************************************************************/
%/* pthread_barrierattr_t                                                */
%/************************************************************************/
%

@@>> pthread_barrierattr_init(3)
@@Initialize barrier attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrierattr_init([[nonnull]] pthread_barrierattr_t *attr);

@@>> pthread_barrierattr_destroy(3)
@@Destroy previously dynamically initialized barrier attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrierattr_destroy([[nonnull]] pthread_barrierattr_t *attr);

@@>> pthread_barrierattr_getpshared(3)
@@Get the process-shared flag of the barrier attribute ATTR
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrierattr_getpshared([[nonnull]] pthread_barrierattr_t const *__restrict attr,
                                        [[nonnull]] int *__restrict pshared);

@@>> pthread_barrierattr_setpshared(3)
@@Set the process-shared flag of the barrier attribute ATTR
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `pshared'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrierattr_setpshared([[nonnull]] pthread_barrierattr_t *attr, int pshared);

%#endif /* __USE_XOPEN2K */

%
%
%/************************************************************************/
%/* pthread_key_t                                                        */
%/************************************************************************/
%


%{
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
}
%[define_type_class(__pthread_destr_function_t = "TP")]


@@>> pthread_key_create(3)
@@Create a key value identifying a location in the thread-specific
@@data area. Each thread maintains a distinct thread-specific data
@@area. DESTR_FUNCTION, if non-NULL, is called with the value
@@associated to that key when the key is destroyed.
@@DESTR_FUNCTION is not called if the value associated is NULL when
@@the key is destroyed
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory to create the key
[[decl_prefix(
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_key_create([[nonnull]] pthread_key_t *key,
                            [[nullable]] __pthread_destr_function_t destr_function);


%#ifdef __USE_SOLARIS
%{
#ifndef PTHREAD_ONCE_KEY_NP
#ifdef __PTHREAD_ONCE_KEY_NP
#define PTHREAD_ONCE_KEY_NP __PTHREAD_ONCE_KEY_NP
#else /* __PTHREAD_ONCE_KEY_NP */
#define PTHREAD_ONCE_KEY_NP ((pthread_key_t)-1)
#endif /* !__PTHREAD_ONCE_KEY_NP */
#endif /* !PTHREAD_ONCE_KEY_NP */
}

@@>> pthread_key_create_once_np(3)
@@Same as `pthread_key_create()', but the given `key' must be pre-initialized
@@using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
@@make sure that even in the event of multiple simultaneous threads calling
@@this function, only one will create the key, and all others will wait until
@@the key has been created. Once the key was created, further calls to this
@@function will no longer block, but simply return immediately.
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory to create the key
[[decl_prefix(
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBKCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */
)]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[impl_include("<hybrid/__atomic.h>")]]
[[requires_function(pthread_key_create)]]
$errno_t pthread_key_create_once_np([[nonnull]] pthread_key_t *key,
                                    [[nullable]] __pthread_destr_function_t destr_function) {
	pthread_key_t kv;
	errno_t error;
again:
	kv = __hybrid_atomic_load(*key, __ATOMIC_ACQUIRE);
@@pp_ifdef __PTHREAD_ONCE_KEY_NP@@
	if (kv != __PTHREAD_ONCE_KEY_NP)
@@pp_else@@
	if (kv != (pthread_key_t)-1)
@@pp_endif@@
	{
		return 0; /* Already initialized. */
	}

	/* Try to do the init ourselves. */
	error = pthread_key_create(key, destr_function);
	if unlikely(error != 0)
		return error; /* Error... */

	/* Try to save the results. */
@@pp_ifdef __PTHREAD_ONCE_KEY_NP@@
	if unlikely(!__hybrid_atomic_cmpxch(*key, __PTHREAD_ONCE_KEY_NP, kv,
	                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
@@pp_else@@
	if unlikely(!__hybrid_atomic_cmpxch(*key, (pthread_key_t)-1, kv,
	                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
@@pp_endif@@
	{
		/* Someone else was faster. - Destroy our version of the key,  and
		 * try again in order to use the other key that was created in the
		 * mean time. */
@@pp_if $has_function(pthread_key_delete)@@
		pthread_key_delete(kv);
@@pp_endif@@
		goto again;
	}
	return 0;
}
%#endif /* __USE_SOLARIS */

@@>> pthread_key_delete(3)
@@Destroy KEY
@@@return: EOK:    Success
@@@return: EINVAL: Invalid `key'
[[export_alias("tss_delete")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_key_delete(pthread_key_t key);

@@>> pthread_getspecific(3)
@@Return current value of the thread-specific data slot identified by KEY
@@@return: * :   The value currently associated with `key' in the calling thread
@@@return: NULL: The current value is `NULL'
@@@return: NULL: No value has been bound, yet
@@@return: NULL: Invalid `key'
[[wunused, export_alias("tss_get")]]
[[decl_include("<bits/crt/pthreadtypes.h>")]]
void *pthread_getspecific(pthread_key_t key);

@@>> pthread_setspecific(3)
@@Store POINTER in the thread-specific data slot identified by KEY
@@@return: EOK:    Success
@@@return: EINVAL: Invalid `key'
@@@return: ENOMEM: `pointer' is non-NULL, `key' had yet to be allowed for the
@@                 calling thread, and an attempt to allocate it just now failed
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setspecific(pthread_key_t key, void const *pointer);

%#ifdef __USE_XOPEN2K
@@>> pthread_getcpuclockid(3)
@@Get ID of CPU-time clock for thread THREAD_ID
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getcpuclockid(pthread_t pthread, [[nonnull]] $clockid_t *clock_id);
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


@@>> pthread_atfork(3)
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
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory to register callbacks
[[guard, decl_prefix(DEFINE_PTHREAD_ATFORK_FUNC_T)]]
[[decl_include("<bits/types.h>")]]
$errno_t pthread_atfork([[nullable]] __pthread_atfork_func_t prepare,
                        [[nullable]] __pthread_atfork_func_t parent,
                        [[nullable]] __pthread_atfork_func_t child);

%[default:section(".text.crt{|.dos}.sched.pthread_ext")]

%
%
%/* Some more functions from winpthread. */

@@>> pthread_num_processors_np(3)
@@@return: * : The number of cpus that the calling thread is able to run on
[[impl_include("<bits/os/cpu_set.h>")]]
[[decl_include("<features.h>")]]
[[requires_function(sched_getaffinity)]]
__STDC_INT_AS_SIZE_T pthread_num_processors_np() {
	cpu_set_t cset;
	if unlikely(sched_getaffinity(0, sizeof(cset), &cset) != 0)
		return 1;
	return (__STDC_INT_AS_SIZE_T)__CPU_COUNT_S(sizeof(cset), &cset);
}

@@>> pthread_set_num_processors_np(3)
@@Restrict the calling thread to only run on the first `n' cpus
@@@return: EOK:    Success
@@@return: EINVAL: `n' was specified as less than `1'
@@@return: * :     Same as `errno' after a call to `sched_setaffinity(2)'
[[decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/cpu_set.h>", "<libc/errno.h>")]]
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
@@>> pthread_main_np(3)
@@Returns 1 if the calling thread is the main() thread (i.e. the
@@thread that was started by the kernel in order to execute the
@@calling program), and 0 otherwise. Additionally, -1 is returned
@@if the calling thread "hasn't been initialized", though this
@@isn't a case that can actually happen under KOS's implementation.
[[const, nothrow, export_alias("thr_main")]]
[[requires_function(gettid, getpid)]]
int pthread_main_np() {
	return gettid() == getpid();
}
%#endif /* __USE_BSD */






%{
#endif /* __CC__ */

__SYSDECL_END

}
