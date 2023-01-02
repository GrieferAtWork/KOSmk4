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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/_pthreadtypes.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/_pthreadtypes.h) */
/* (#) Portability: FreeBSD       (/sys/sys/_pthreadtypes.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/_pthreadtypes.h) */
#ifndef _SYS__PTHREADTYPES_H
#define _SYS__PTHREADTYPES_H 1

#include <__stdinc.h>

#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/posix_opt.h> /* Pthread feature macros */
#include <sys/sched.h>

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
#endif /* !__PTHREAD_ENUM_MUTEX_TYPE_DEFINED */


#ifdef __CC__
__DECL_BEGIN

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
#ifndef __pthread_barrier_t_defined
#define __pthread_barrier_t_defined
typedef __pthread_barrier_t pthread_barrier_t;
#endif /* !__pthread_barrier_t_defined */
#ifndef __pthread_barrierattr_t_defined
#define __pthread_barrierattr_t_defined
typedef __pthread_barrierattr_t pthread_barrierattr_t;
#endif /* !__pthread_barrierattr_t_defined */
#ifndef __pthread_spinlock_t_defined
#define __pthread_spinlock_t_defined
typedef __pthread_spinlock_t pthread_spinlock_t;
#endif /* !__pthread_spinlock_t_defined */
#ifndef __pthread_rwlock_t_defined
#define __pthread_rwlock_t_defined
typedef __pthread_rwlock_t pthread_rwlock_t;
#endif /* !__pthread_rwlock_t_defined */
#ifndef __pthread_rwlockattr_t_defined
#define __pthread_rwlockattr_t_defined
typedef __pthread_rwlockattr_t pthread_rwlockattr_t;
#endif /* !__pthread_rwlockattr_t_defined */

#ifdef __PTHREAD_MUTEX_INITIALIZER
#define _PTHREAD_MUTEX_INITIALIZER __PTHREAD_MUTEX_INITIALIZER
#endif /* __PTHREAD_MUTEX_INITIALIZER */
#ifdef __PTHREAD_COND_INITIALIZER
#define _PTHREAD_COND_INITIALIZER __PTHREAD_COND_INITIALIZER
#endif /* __PTHREAD_COND_INITIALIZER */
#ifdef __PTHREAD_ONCE_INIT
#define PTHREAD_ONCE_INIT __PTHREAD_ONCE_INIT
#endif /* __PTHREAD_ONCE_INIT */
#ifdef __PTHREAD_RWLOCK_INITIALIZER
#define _PTHREAD_RWLOCK_INITIALIZER __PTHREAD_RWLOCK_INITIALIZER
#endif /* __PTHREAD_RWLOCK_INITIALIZER */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS__PTHREADTYPES_H */
