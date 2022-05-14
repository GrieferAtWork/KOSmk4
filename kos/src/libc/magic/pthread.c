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
%(c_prefix){
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/pthread.h) */
/* (#) Portability: FreeBSD       (/include/pthread.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/pthread.h) */
/* (#) Portability: MinGW         (/mingw-w64-libraries/winpthreads/include/pthread.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/pthread.h) */
/* (#) Portability: OpenBSD       (/include/pthread.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/pthread.h) */
/* (#) Portability: diet libc     (/include/pthread.h) */
/* (#) Portability: libc6         (/include/pthread.h) */
/* (#) Portability: musl libc     (/include/pthread.h) */
/* (#) Portability: uClibc        (/libpthread/nptl/sysdeps/pthread/pthread.h) */
}

%[define_decl_include("<bits/os/cpu_set.h>": ["struct __cpu_set_struct", "__cpu_mask_t"])]

%[define_decl_include_implication("<bits/crt/setjmp.h>" => ["<hybrid/typecore.h>", "<bits/os/sigset.h>"])]
%[define_decl_include("<bits/crt/setjmp.h>": ["struct __jmp_buf", "struct __sigjmp_buf"])]

%[define_decl_include_implication("<bits/crt/pthreadtypes.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/crt/pthreadtypes.h>": [
	"__pthread_key_t",
	"__pthread_once_t",
	"__pthread_t",
	"__pthread_attr_t",
	"__pthread_mutexattr_t",
	"__pthread_list_t",
	"__pthread_slist_t",
	"__pthread_mutex_t", "struct __pthread_mutex_s",
	"__pthread_condattr_t",
	"__pthread_cond_t", "struct __pthread_cond_s",
	"__pthread_rwlockattr_t",
	"__pthread_rwlock_t", "struct __pthread_rwlock_s",
	"__pthread_spinlock_t",
	"__pthread_barrierattr_t",
	"__pthread_barrier_t",
])]


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


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/pthreadvalues.h>
)]%[insert:prefix(
#include <bits/crt/pthreadtypes.h>
)]%[insert:prefix(
#include <bits/crt/setjmp.h>
)]%[insert:prefix(
#include <bits/os/cpu_set.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __USE_GLIBC
#include <endian.h>
#include <sched.h>
#include <time.h>
#endif /* __USE_GLIBC */

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


}

@@>> pthread_create(3)
@@Create a  new thread,  starting with  execution of  `start_routine'
@@getting passed `arg'. Creation attributed come from `attr'. The new
@@handle is stored in `*newthread'
@@@return: EOK:    Success
@@@return: EAGAIN: Insufficient resources, or operation-not-permitted
@@                 (read: `ENOMEM', but posix didn't want to use that
@@                 errno for whatever reason...)
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[crt_dos_impl_if(!defined(__LIBCCALL_IS_LIBDCALL)), crt_dos_variant]]
$errno_t pthread_create([[nonnull]] pthread_t *__restrict newthread, pthread_attr_t const *__restrict attr,
                        [[nonnull]] void *(LIBCCALL *start_routine)(void *arg), void *arg);

@@>> pthread_exit(3)
@@Terminate calling thread.
@@The registered cleanup handlers are called via exception handling
[[throws, noreturn, export_alias("thr_exit")]]
void pthread_exit(void *retval);

@@>> pthread_join(3)
@@Make calling thread wait for termination of the thread `pthread'.
@@The exit status of the  thread is stored in `*thread_return',  if
@@`thread_return' is not `NULL'.
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_join(pthread_t pthread, void **thread_return);

%#ifdef __USE_GNU
@@>> pthread_tryjoin_np(3)
@@Check whether thread `pthread' has terminated. If so return the
@@status of the thread in `*thread_return', if `thread_return' is
@@not `NULL'.
@@@return: EOK:   Success
@@@return: EBUSY: The thread has yet to terminate
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_tryjoin_np(pthread_t pthread, void **thread_return);

%struct timespec;
@@>> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
@@Make calling thread wait for termination of the thread `pthread',
@@but only until `timeout'. The exit status of the thread is stored
@@in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_timedjoin_np")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_timedjoin64_np")]]
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
[[cp, ignore, doc_alias("pthread_timedjoin_np"), nocrt, alias("pthread_timedjoin_np")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_timedjoin32_np(pthread_t pthread, void **thread_return,
                                struct timespec32 const *abstime);


[[cp, preferred_time64_variant_of(pthread_timedjoin_np), doc_alias("pthread_timedjoin_np")]]
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
@@Indicate  that the  thread `pthread' is  never to be  joined with `pthread_join(3)'.
@@The  resources  of   `pthread'  will   therefore  be  freed   immediately  when   it
@@terminates, instead of waiting for another thread to perform `pthread_join(3)' on it
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_detach(pthread_t pthread);

@@>> pthread_self(3)
@@Obtain the identifier of the current thread
@@@return: * : Handle for the calling thread
[[const, wunused, nothrow, export_alias("thrd_current", "thr_self")]]
[[decl_include("<bits/crt/pthreadtypes.h>")]]
pthread_t pthread_self();

@@>> pthread_equal(3)
@@Compare two thread identifiers
@@@return: 0 : Given threads are non-equal
@@@return: * : Given threads are equal
[[extern_inline, const, wunused, nothrow, export_alias("thrd_equal")]]
[[decl_include("<bits/crt/pthreadtypes.h>")]]
int pthread_equal(pthread_t thr1, pthread_t thr2) {
	return thr1 == thr2;
}

%
%/* Thread attribute handling. */
%
@@>> pthread_attr_init(3)
@@Initialize thread  attribute `*attr'  with default  attributes (detachstate  is
@@`PTHREAD_JOINABLE', scheduling policy is `SCHED_OTHER', no user-provided stack)
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_init([[nonnull]] pthread_attr_t *attr);

@@>> pthread_attr_destroy(3)
@@Destroy thread attribute `*attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_destroy([[nonnull]] pthread_attr_t *attr);

@@>> pthread_attr_getdetachstate(3)
@@Get   detach   state    attribute
@@@param: *detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getdetachstate([[nonnull]] pthread_attr_t const *attr,
                                     [[nonnull]] int *detachstate);

@@>> pthread_attr_setdetachstate(3)
@@Set   detach   state    attribute
@@@param: detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
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
@@Return in `*param' the scheduling parameters of `*attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getschedparam([[nonnull]] pthread_attr_t const *__restrict attr,
                                    [[nonnull]] struct sched_param *__restrict param);

@@>> pthread_attr_setschedparam(3)
@@Set scheduling parameters (priority, etc) in `*attr' according to `param'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `param'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setschedparam([[nonnull]] pthread_attr_t *__restrict attr,
                                    [[nonnull]] struct sched_param const *__restrict param);

@@>> pthread_attr_getschedpolicy(3)
@@Return in `*policy' the scheduling policy of `*attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getschedpolicy([[nonnull]] pthread_attr_t const *__restrict attr,
                                     [[nonnull]] int *__restrict policy);

@@>> pthread_attr_setschedpolicy(3)
@@Set scheduling policy in `*attr' according to `policy'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `policy'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setschedpolicy([[nonnull]] pthread_attr_t *attr, int policy);

@@>> pthread_attr_getinheritsched(3)
@@Return in `*inherit' the scheduling inheritance mode of `*attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getinheritsched([[nonnull]] pthread_attr_t const *__restrict attr,
                                      [[nonnull]] int *__restrict inherit);

@@>> pthread_attr_setinheritsched(3)
@@Set scheduling inheritance mode in `*attr' according to `inherit'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `inherit'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setinheritsched([[nonnull]] pthread_attr_t *attr, int inherit);

@@>> pthread_attr_getscope(3)
@@Return in `*scope' the scheduling contention scope of `*attr'
@@@param:  scope: Filled with one of `PTHREAD_SCOPE_*'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_getscope([[nonnull]] pthread_attr_t const *__restrict attr,
                               [[nonnull]] int *__restrict scope);

@@>> pthread_attr_setscope(3)
@@Set scheduling contention scope in `*attr' according to `scope'
@@@param:  scope:  One of `PTHREAD_SCOPE_*'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `scope'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setscope([[nonnull]] pthread_attr_t *attr, int scope);


/************************************************************************/
/* Non-subsitutable CRT-variants used for local implementations         */
/************************************************************************/
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[ignore, nocrt, alias("pthread_attr_getstackaddr"), doc_alias("pthread_attr_getstackaddr")]]
$errno_t crt_pthread_attr_getstackaddr([[nonnull]] pthread_attr_t const *__restrict attr,
                                       [[nonnull]] void **__restrict stackaddr);
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[ignore, nocrt, alias("pthread_attr_setstackaddr"), doc_alias("pthread_attr_setstackaddr")]]
$errno_t crt_pthread_attr_setstackaddr([[nonnull]] pthread_attr_t *attr, void *stackaddr);
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[ignore, nocrt, alias("pthread_attr_getstacksize"), doc_alias("pthread_attr_getstacksize")]]
$errno_t crt_pthread_attr_getstacksize([[nonnull]] pthread_attr_t const *__restrict attr,
                                       [[nonnull]] size_t *__restrict stacksize);
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[ignore, nocrt, alias("pthread_attr_setstacksize"), doc_alias("pthread_attr_setstacksize")]]
$errno_t crt_pthread_attr_setstacksize([[nonnull]] pthread_attr_t *attr, size_t stacksize);
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[ignore, nocrt, alias("pthread_attr_getstack"), doc_alias("pthread_attr_getstack")]]
$errno_t crt_pthread_attr_getstack([[nonnull]] pthread_attr_t const *__restrict attr,
                                   [[nonnull]] void **__restrict stackaddr,
                                   [[nonnull]] size_t *__restrict stacksize);
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[ignore, nocrt, alias("pthread_attr_setstack"), doc_alias("pthread_attr_setstack")]]
$errno_t crt_pthread_attr_setstack([[nonnull]] pthread_attr_t *attr, void *stackaddr, size_t stacksize);
/************************************************************************/


@@>> pthread_attr_getstackaddr(3)
@@Return the previously set address for the stack
@@@return: EOK: Success
[[deprecated("Use pthread_attr_getstack()")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[userimpl, requires_function(crt_pthread_attr_getstack)]]
$errno_t pthread_attr_getstackaddr([[nonnull]] pthread_attr_t const *__restrict attr,
                                   [[nonnull]] void **__restrict stackaddr) {
	size_t stacksize;
	return crt_pthread_attr_getstack(attr, stackaddr, &stacksize);
}


@@>> pthread_attr_setstackaddr(3)
@@Set the starting address  of the stack of  the thread to be  created.
@@Depending on whether the stack grows up or down the value must either
@@be higher or  lower than  all the address  in the  memory block.  The
@@minimal size of the block must be `PTHREAD_STACK_MIN'
@@@return: EOK:    Success
@@@return: EINVAL: The stack isn't suitably aligned
[[deprecated("Use pthread_attr_setstack()")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[userimpl, requires_function(pthread_attr_getstack, crt_pthread_attr_setstack)]]
$errno_t pthread_attr_setstackaddr([[nonnull]] pthread_attr_t *attr, void *stackaddr) {
	errno_t result;
	size_t stacksize;
@@pp_if $has_function(crt_pthread_attr_getstacksize)@@
	result = crt_pthread_attr_getstacksize(attr, &stacksize);
@@pp_else@@
	void *_old_stackaddr;
	result = pthread_attr_getstack(attr, &_old_stackaddr, &stacksize);
@@pp_endif@@
	if likely(result == 0)
		result = crt_pthread_attr_setstack(attr, stackaddr, stacksize);
	return result;
}

@@>> pthread_attr_getstacksize(3)
@@Return the currently used minimal stack size
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[userimpl, requires_function(crt_pthread_attr_getstack)]]
$errno_t pthread_attr_getstacksize([[nonnull]] pthread_attr_t const *__restrict attr,
                                   [[nonnull]] size_t *__restrict stacksize) {
	void *stackaddr;
	return crt_pthread_attr_getstack(attr, &stackaddr, stacksize);
}

@@>> pthread_attr_setstacksize(3)
@@Add information about the minimum  stack size needed for the  thread
@@to be started. This size must never be less than `PTHREAD_STACK_MIN'
@@and must also not exceed the system limits
@@@return: EOK:    Success
@@@return: EINVAL: `stacksize' is too small
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[userimpl, requires_function(pthread_attr_getstack, crt_pthread_attr_setstack)]]
$errno_t pthread_attr_setstacksize([[nonnull]] pthread_attr_t *attr, size_t stacksize) {
	errno_t result;
	void *stackaddr;
@@pp_if $has_function(crt_pthread_attr_getstackaddr)@@
	result = crt_pthread_attr_getstackaddr(attr, &stackaddr);
@@pp_else@@
	size_t _old_stacksize;
	result = pthread_attr_getstack(attr, &stackaddr, &_old_stacksize);
@@pp_endif@@
	if likely(result == 0)
		result = crt_pthread_attr_setstack(attr, stackaddr, stacksize);
	return result;
}

%#ifdef __USE_XOPEN2K
@@>> pthread_attr_getstack(3)
@@Return the previously set address for the stack
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[userimpl, requires_function(crt_pthread_attr_getstackaddr, crt_pthread_attr_getstacksize)]]
$errno_t pthread_attr_getstack([[nonnull]] pthread_attr_t const *__restrict attr,
                               [[nonnull]] void **__restrict stackaddr,
                               [[nonnull]] size_t *__restrict stacksize) {
	errno_t result;
	result = crt_pthread_attr_getstackaddr(attr, stackaddr);
	if likely(result == 0)
		result = crt_pthread_attr_getstacksize(attr, stacksize);
	return result;
}


@@>> pthread_attr_setstack(3)
@@The following two interfaces are intended to replace the last two. They
@@require setting the address as well as the size since only setting  the
@@address will make the implementation on some architectures impossible
@@@return: EOK:    Success
@@@return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[userimpl, requires_function(crt_pthread_attr_setstackaddr, crt_pthread_attr_setstacksize)]]
$errno_t pthread_attr_setstack([[nonnull]] pthread_attr_t *attr,
                               void *stackaddr, size_t stacksize) {
	errno_t result;
	result = crt_pthread_attr_setstackaddr(attr, stackaddr);
	if likely(result == 0)
		result = crt_pthread_attr_setstacksize(attr, stacksize);
	return result;
}
%#endif /* __USE_XOPEN2K */

%#ifdef __USE_GNU
%#ifndef __cpu_set_t_defined
%#define __cpu_set_t_defined
%typedef struct __cpu_set_struct cpu_set_t;
%#endif /* !__cpu_set_t_defined */


@@>> pthread_attr_setaffinity_np(3)
@@Thread  created with attribute `attr' will be limited
@@to run only on the processors represented in `cpuset'
@@@return: EOK:    Success
@@@return: EINVAL: The given set contains a non-existant CPU
@@@return: ENOMEM: Insufficient memory
[[decl_include("<bits/types.h>", "<bits/os/cpu_set.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_attr_setaffinity_np([[nonnull]] pthread_attr_t *attr, size_t cpusetsize,
                                     [[nonnull]] cpu_set_t const *cpuset);

@@>> pthread_attr_getaffinity_np(3)
@@Get bit set in `cpuset' representing the processors
@@threads created with `attr' can run on
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
@@Initialize thread  attribute `*attr'  with attributes  corresponding to  the
@@already running thread `pthread'. It shall be called on uninitialized `attr'
@@and destroyed with `pthread_attr_destroy(3)' when no longer needed
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getattr_np(pthread_t pthread, [[nonnull]] pthread_attr_t *attr);
%#endif /* __USE_GNU */

%
%/* Functions for scheduling control. */
%
@@>> pthread_setschedparam(3)
@@Set the scheduling parameters for `target_thread' according to `policy' and `*param'
@@@return: EOK:    Success
@@@return: EPERM:  The caller isn't allowed to specify `policy' and `param'
@@@return: ESRCH:  `pthread' has already exited
@@@return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/sched.h>")]]
$errno_t pthread_setschedparam(pthread_t target_thread, int policy,
                               [[nonnull]] struct sched_param const *param);

@@>> pthread_getschedparam(3)
@@Return in `*policy' and `*param' the scheduling parameters for `target_thread'
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/sched.h>")]]
$errno_t pthread_getschedparam(pthread_t target_thread,
                               [[nonnull]] int *__restrict policy,
                               [[nonnull]] struct sched_param *__restrict param);

@@>> pthread_setschedprio(3)
@@Set the scheduling priority for `target_thread'
@@@return: EOK:    Success
@@@return: EPERM:  The caller isn't allowed to specify `prio'
@@@return: ESRCH:  `pthread' has already exited
@@@return: EINVAL: Invalid/unsupported `prio'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setschedprio(pthread_t target_thread, int prio);


%#ifdef __USE_GNU
@@>> pthread_getname_np(3)
@@Get thread name visible in the kernel and its interfaces
@@@return: EOK:    Success
@@@return: ERANGE: The given `buflen' is too small
[[export_alias("pthread_get_name_np")]] /* OpenBSD-specific name */
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getname_np(pthread_t target_thread,
                            [[outp(buflen)]] char *buf,
                            size_t buflen);

@@>> pthread_setname_np(3)
@@Set thread name visible in the kernel and its interfaces
@@@return: EOK:    Success
@@@return: ERANGE: The given `name' is too long
[[export_alias("pthread_set_name_np")]] /* OpenBSD-specific name */
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setname_np(pthread_t target_thread,
                            [[nonnull]] const char *name);
%#endif /* __USE_GNU */


%#ifdef __USE_KOS
@@>> pthread_gettid_np(3)
@@Return the TID of the given `target_thread'.
@@If the given `target_thread' has already terminated, 0 is returned
@@@return: * : The TID of the given thread
@@@return: 0 : The given `target_thread' has already terminated
[[guard, pure, wunused]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$pid_t pthread_gettid_np(pthread_t target_thread);

@@>> pthread_mainthread_np(3)
@@Obtain the identifier of the main thread
@@@return: * : Handle for the main thread
[[wunused, const, nothrow, decl_include("<bits/crt/pthreadtypes.h>")]]
pthread_t pthread_mainthread_np(void);

%struct rpc_context;

@@>> pthread_rpc_exec(3)
@@Schedule an RPC for `target_thread' to-be executed the next  time
@@it makes a call to a cancellation-point system call (or interrupt
@@an active system call, should one such currently be in progress).
@@  - RPCs are also executed by `pthread_testcancel(3)'
@@  - The `struct rpc_context' structure is defined in `<kos/rpc.h>'
@@@return: 0:      Success
@@@return: ENOMEM: Insufficient system memory
@@@return: ESRCH:  The given `target_thread' has already terminated
[[cp, nodos, wunused]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rpc_exec(pthread_t target_thread,
                          void (LIBKCALL *func)(struct rpc_context *__restrict ctx, void *cookie),
                          void *cookie);
%#endif /* __USE_KOS */


%#ifdef __USE_UNIX98
@@>> pthread_getconcurrency(3)
@@Determine level of concurrency
@@@return: * : The current concurrency level
[[export_alias("thr_getconcurrency")]]
[[pure]] int pthread_getconcurrency();

@@>> pthread_setconcurrency(3)
@@Set new concurrency level to `level'
@@@return: EOK:    Success
@@@return: EINVAL: The given `level' is negative
[[decl_include("<bits/types.h>")]]
[[export_alias("thr_setconcurrency")]]
$errno_t pthread_setconcurrency(int level);
%#endif /* __USE_UNIX98 */

%#ifdef __USE_GNU
@@>> pthread_yield(3), thrd_yield(3), sched_yield(2)
@@Yield  the processor to another thread or process.
@@This function is similar to the POSIX `sched_yield' function but
@@might  be differently implemented in the case of a m-on-n thread
@@implementation
@@@return: EOK: Success
[[decl_include("<bits/types.h>")]]
$errno_t pthread_yield(void) = sched_yield;

@@>> pthread_setaffinity_np(3)
@@Limit specified thread `pthread' to run only on the processors represented in `cpuset'
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/os/cpu_set.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_setaffinity_np(pthread_t pthread, size_t cpusetsize,
                                [[nonnull]] cpu_set_t const *cpuset);

@@>> pthread_getaffinity_np(3)
@@Get bit set in `cpuset' representing the processors `pthread' can run on
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/os/cpu_set.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getaffinity_np(pthread_t pthread, size_t cpusetsize,
                                [[nonnull]] cpu_set_t *cpuset);
%#endif /* __USE_GNU */



%
%/* Functions for handling initialization. */
%

@@>> pthread_once(3)
@@Guarantee that the initialization function `init_routine' will be called
@@only  once,  even if  pthread_once is  executed  several times  with the
@@same `once_control' argument. `once_control' must  point to a static  or
@@extern variable initialized to `PTHREAD_ONCE_INIT'.
@@@return: EOK: Success
[[throws, export_alias("call_once")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[impl_include("<asm/crt/pthreadvalues.h>", "<hybrid/__atomic.h>")]]
[[impl_include("<hybrid/sched/__yield.h>", "<asm/os/errno.h>")]]
[[impl_include("<kos/asm/futex.h>")]]
$errno_t pthread_once([[nonnull]] pthread_once_t *once_control,
                      [[nonnull]] void (LIBCCALL *init_routine)(void)) {
#undef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
@@pp_if $has_function(futex_wakeall)@@
@@pp_if __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__ && $has_function(futex_waitwhile)@@
#define __PRIVATE_PTHREAD_ONCE_USES_FUTEX
@@pp_elif $has_function(lfutex64) && defined(@LFUTEX_WAIT_WHILE_EX@)@@
#define __PRIVATE_PTHREAD_ONCE_USES_FUTEX
@@pp_endif@@
@@pp_endif@@

	/*
	 * Internal state values for pthread_once():
	 *  - __PTHREAD_ONCE_INIT + 0: Not yet called
	 *  - __PTHREAD_ONCE_INIT + 1: Currently being called
	 *  - __PTHREAD_ONCE_INIT + 2: Was called
	 * #ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
	 *  - __PTHREAD_ONCE_INIT + 3: Currently being called, and other threads are waiting
	 * #endif
	 *
	 */
	pthread_once_t status;
again:
	status = __hybrid_atomic_cmpxch_val(*once_control,
	                                    __PTHREAD_ONCE_INIT,
	                                    __PTHREAD_ONCE_INIT + 1,
	                                    __ATOMIC_SEQ_CST,
	                                    __ATOMIC_SEQ_CST);
	if (status == __PTHREAD_ONCE_INIT) {
		/* To comply with POSIX, we  must be able to roll-back  our
		 * initialization when `init_routine' "cancels" our thread. */
@@pp_ifdef __cplusplus@@
		@try@ {
			(*init_routine)();
		} @catch@ (...) {
			/* roll-back... */
@@pp_ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX@@
			if (__hybrid_atomic_xch(*once_control, __PTHREAD_ONCE_INIT,
			                        __ATOMIC_RELEASE) == __PTHREAD_ONCE_INIT + 3)
				futex_wakeall((lfutex_t *)once_control);
@@pp_else@@
			__hybrid_atomic_store(*once_control,
			                      __PTHREAD_ONCE_INIT,
			                      __ATOMIC_RELEASE);
@@pp_endif@@
@@pp_if $has_function(except_rethrow)@@
			except_rethrow();
@@pp_else@@
			@throw@;
@@pp_endif@@
		}
@@pp_else@@
		(*init_routine)();
@@pp_endif@@

		/* Remember that the function was called. */
@@pp_if defined(__PRIVATE_PTHREAD_ONCE_USES_FUTEX) && $has_function(futex_wakeall)@@
		if (__hybrid_atomic_xch(*once_control, __PTHREAD_ONCE_INIT + 2,
		                        __ATOMIC_RELEASE) == __PTHREAD_ONCE_INIT + 3)
			futex_wakeall((lfutex_t *)once_control);
@@pp_else@@
		__hybrid_atomic_store(*once_control,
		                      __PTHREAD_ONCE_INIT + 2,
		                      __ATOMIC_RELEASE);
@@pp_endif@@
	} else if (status != __PTHREAD_ONCE_INIT + 2) {
@@pp_ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX@@
		if unlikely(status != __PTHREAD_ONCE_INIT + 1 &&
		            status != __PTHREAD_ONCE_INIT + 3)
@@pp_else@@
		if unlikely(status != __PTHREAD_ONCE_INIT + 1)
@@pp_endif@@
		{
			/* Quote(https://man7.org/linux/man-pages/man3/pthread_once.3p.html):
			 * """
			 * If  an implementation  detects that  the value  specified by the
			 * once_control argument  to pthread_once()  does  not refer  to  a
			 * pthread_once_t object  initialized by  PTHREAD_ONCE_INIT, it  is
			 * recommended that the function should fail and report an [EINVAL]
			 * error.
			 * """
			 */
@@pp_ifdef EINVAL@@
			return EINVAL;
@@pp_else@@
			return 1;
@@pp_endif@@
		}

		/* Wait for some other thread to finish init_routine() */
@@pp_ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX@@
		if (status == __PTHREAD_ONCE_INIT + 1) {
			/* Request a futex-wake call once initialization
			 * completes  in  whatever thread  is  doing it. */
			if (!__hybrid_atomic_cmpxch(*once_control,
			                            __PTHREAD_ONCE_INIT + 1,
			                            __PTHREAD_ONCE_INIT + 3,
			                            __ATOMIC_SEQ_CST,
			                            __ATOMIC_SEQ_CST))
				goto again;
		}
@@pp_if __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__ && $has_function(futex_waitwhile)@@
		futex_waitwhile((lfutex_t *)once_control, __PTHREAD_ONCE_INIT + 3);
@@pp_else@@
		{
			static pthread_once_t const _init_marker = __PTHREAD_ONCE_INIT + 3;
			lfutex64((lfutex_t *)once_control, @LFUTEX_WAIT_WHILE_EX@,
			         (lfutex_t)&_init_marker, (struct timespec64 const *)NULL,
			         sizeof(pthread_once_t));
		}
@@pp_endif@@
@@pp_else@@
		do {
			__hybrid_yield();
		} while (__hybrid_atomic_load(*once_control, __ATOMIC_ACQUIRE) ==
		         __PTHREAD_ONCE_INIT + 1);
@@pp_endif@@

		/* Must re-check the once-status, since another thread may have
		 * rolled back completion  in case its  call to  `init_routine'
		 * resulted in an exception being called. (or to speak in terms
		 * of POSIX, caused its thread to be "canceled") */
		goto again;
	}
	return 0;
#undef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
}

%
%/* Functions for handling cancellation.
% * Note that these functions are explicitly not marked to not throw an
% * exception in C++ code. If cancellation is implemented by unwinding
% * this is necessary to have the compiler generate the unwind information. */


@@>> pthread_setcancelstate(3)
@@Set  cancelability  state   of  current   thread  to   `state',
@@returning old state in `*oldstate' if `oldstate' is not `NULL'.
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `state'
[[decl_include("<bits/types.h>")]]
$errno_t pthread_setcancelstate(int state, [[nullable]] int *oldstate);

@@>> pthread_setcanceltype(3)
@@Set cancellation state of current thread to `type',
@@returning the old type in `*oldtype' if `oldtype' is not `NULL'.
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `type'
[[guard, decl_include("<bits/types.h>")]]
$errno_t pthread_setcanceltype(int type, [[nullable]] int *oldtype);

@@>> pthread_cancel(3)
@@Cancel `pthread' immediately or at the next possibility
@@@return: EOK:   Success
@@@return: ESRCH: `pthread' has already exited
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_cancel(pthread_t pthread);

@@>> pthread_testcancel(3)
@@Test for pending cancellation for the current thread and terminate the
@@thread as per `pthread_exit(PTHREAD_CANCELED)' if it has been canceled
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
#endif /* !__cplusplus */
}

%#else /* __GNUC__ && __EXCEPTIONS */

%{
/* Install  a cleanup handler: `routine' will be called with arguments `arg'
 * when  the thread is  canceled or calls  pthread_exit. `routine' will also
 * be called with arguments `arg' when the matching `pthread_cleanup_pop(3)'
 * is executed with non-zero `execute' argument.
 * pthread_cleanup_push and `pthread_cleanup_pop(3)' are macros and must
 * always be used in matching pairs at the same nesting level of braces. */
}
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

%{
/* Remove a cleanup handler installed by the matching `pthread_cleanup_push(3)'.
 * If `execute' is non-zero, the handler function is called. */
}
%#define pthread_cleanup_pop(execute)                                                \
%			do {                                                                    \
%			} __WHILE0; /* Empty to allow label before `pthread_cleanup_pop(3)'. */ \
%		} __WHILE0;                                                                 \
%		__pthread_unregister_cancel(&__cancel_buf);                                 \
%		if (execute)                                                                \
%			(*__cancel_routine)(__cancel_arg);                                      \
%	}	__WHILE0

[[decl_prefix(DEFINE___cleanup_fct_attribute)]]
[[attribute(__cleanup_fct_attribute)]]
void __pthread_unregister_cancel([[nonnull]] __pthread_unwind_buf_t *buf);

%#ifdef __USE_GNU
%{
/* Install a cleanup handler as `pthread_cleanup_push(3)' does, but
 * also saves the current cancellation type and sets it to deferred
 * cancellation. */
}
%#define pthread_cleanup_push_defer_np(routine, arg)                                                           \
%	do {                                                                                                      \
%		__pthread_unwind_buf_t __cancel_buf;                                                                  \
%		void (__LIBKCALL *__cancel_routine)(void *) = (routine);                                              \
%		void *__cancel_arg = (arg);                                                                           \
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

%{
/* Remove a cleanup handler as `pthread_cleanup_pop(3)' does, but also
 * restores the cancellation type that was in effect when the matching
 * `pthread_cleanup_push_defer(3)' was called. */
}
%#define pthread_cleanup_pop_restore_np(execute)                                     \
%			do {                                                                    \
%			} __WHILE0; /* Empty to allow label before `pthread_cleanup_pop(3)'. */ \
%		} __WHILE0;                                                                 \
%		__pthread_unregister_cancel_restore(&__cancel_buf);                         \
%		if (execute)                                                                \
%			(*__cancel_routine)(__cancel_arg);                                      \
%	}	__WHILE0

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
[[alias("sigsetjmp"), no_crt_impl, decl_prefix(struct __jmp_buf_tag;)]]
int __sigsetjmp([[nonnull]] struct __jmp_buf_tag *env, int savemask);

%
%
%/************************************************************************/
%/* pthread_mutex_t                                                      */
%/************************************************************************/
%

@@>> pthread_mutex_init(3)
@@Initialize the given `mutex'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_init([[nonnull]] pthread_mutex_t *mutex,
                            pthread_mutexattr_t const *mutexattr);

@@>> pthread_mutex_destroy(3)
@@Destroy  the  given `mutex'
@@@return: EOK: Success
[[export_alias("mtx_destroy")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_destroy([[nonnull]] pthread_mutex_t *mutex);

@@>> pthread_mutex_trylock(3)
@@Try locking the given `mutex'
@@@return: EOK:   Success
@@@return: EBUSY: The  mutex  has  already  been   locked
@@                In case of  a recursive mutex,  another
@@                thread was the one to acquire the lock.
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_trylock([[nonnull]] pthread_mutex_t *mutex);

@@>> pthread_mutex_lock(3)
@@Lock  the  given `mutex'
@@@return: EOK: Success
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutex_lock([[nonnull]] pthread_mutex_t *mutex);

%#ifdef __USE_XOPEN2K
@@>> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
@@Wait until lock becomes available, or specified time passes
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_mutex_timedlock")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_mutex_timedlock64")]]
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
[[cp, doc_alias("pthread_mutex_timedlock"), ignore, nocrt, alias("pthread_mutex_timedlock")]]
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_mutex_timedlock32([[nonnull]] pthread_mutex_t *__restrict mutex,
                                   [[nonnull]] struct timespec const *__restrict abstime);

[[cp, preferred_time64_variant_of(pthread_mutex_timedlock), doc_alias("pthread_mutex_timedlock")]]
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
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_mutex_reltimedlock_np")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_mutex_reltimedlock64_np")]]
[[userimpl, requires($has_function(pthread_mutex_reltimedlock32_np) || $has_function(pthread_mutex_reltimedlock64_np))]]
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
[[cp, doc_alias("pthread_mutex_reltimedlock_np"), ignore, nocrt, alias("pthread_mutex_reltimedlock_np")]]
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_mutex_reltimedlock32_np([[nonnull]] pthread_mutex_t *__restrict mutex,
                                         [[nonnull]] struct timespec const *__restrict reltime);

[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(pthread_mutex_reltimedlock_np), doc_alias("pthread_mutex_reltimedlock_np")]]
[[userimpl, requires($has_function(pthread_mutex_reltimedlock32_np))]]
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
@@Unlock  the  given `mutex'
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
@@Set the priority ceiling of `mutex' to `prioceiling',
@@return old priority  ceiling value in  `*old_ceiling'
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
@@Initialize mutex attribute object `attr' with default
@@attributes    (kind    is   `PTHREAD_MUTEX_TIMED_NP')
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_init([[nonnull]] pthread_mutexattr_t *attr);


@@>> pthread_mutexattr_destroy(3)
@@Destroy mutex attribute object `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_destroy([[nonnull]] pthread_mutexattr_t *attr);

@@>> pthread_mutexattr_getpshared(3)
@@Get the process-shared flag of the mutex attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_getpshared([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                      [[nonnull]] int *__restrict pshared);

@@>> pthread_mutexattr_setpshared(3)
@@Set the process-shared flag of the mutex attribute `attr'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `pshared'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_setpshared([[nonnull]] pthread_mutexattr_t *attr, int pshared);


%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
@@>> pthread_mutexattr_gettype(3)
@@Return in `*kind' the mutex kind attribute in `*attr'
@@@return: EOK: Success
[[export_alias("pthread_mutexattr_getkind_np")]] /* OpenBSD-specific name */
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_gettype([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                   [[nonnull]] int *__restrict kind);

@@>> pthread_mutexattr_settype(3)
@@Set  the mutex kind attribute in `*attr' to `kind' (either `PTHREAD_MUTEX_NORMAL',
@@`PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `kind'
[[export_alias("pthread_mutexattr_setkind_np")]] /* OpenBSD-specific name */
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_settype([[nonnull]] pthread_mutexattr_t *attr, int kind);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

@@>> pthread_mutexattr_getprotocol(3)
@@Return in `*protocol' the mutex protocol attribute in `*attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_getprotocol([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                       [[nonnull]] int *__restrict protocol);

@@>> pthread_mutexattr_setprotocol(3)
@@Set  the  mutex protocol  attribute  in `*attr'  to  `protocol' (either
@@`PTHREAD_PRIO_NONE', `PTHREAD_PRIO_INHERIT', or `PTHREAD_PRIO_PROTECT')
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `protocol'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_setprotocol([[nonnull]] pthread_mutexattr_t *attr, int protocol);

@@>> pthread_mutexattr_getprioceiling(3)
@@Return in `*prioceiling' the mutex prioceiling attribute in `*attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_getprioceiling([[nonnull]] pthread_mutexattr_t const *__restrict attr,
                                          [[nonnull]] int *__restrict prioceiling);

@@>> pthread_mutexattr_setprioceiling(3)
@@Set the mutex prioceiling attribute in `*attr' to `prioceiling'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `prioceiling'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_mutexattr_setprioceiling([[nonnull]] pthread_mutexattr_t *attr, int prioceiling);

%#ifdef __USE_XOPEN2K
@@>> pthread_mutexattr_getrobust(3)
@@Get the robustness flag of the mutex attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[export_alias("pthread_mutexattr_getrobust_np")]]
$errno_t pthread_mutexattr_getrobust([[nonnull]] pthread_mutexattr_t const *attr,
                                     [[nonnull]] int *robustness);

@@>> pthread_mutexattr_setrobust(3)
@@Set the robustness flag of the mutex attribute `attr'
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
@@Initialize read-write lock `rwlock' using attributes `attr',
@@or use the default values if later is `NULL'.
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_init([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                             pthread_rwlockattr_t const *__restrict attr);

@@>> pthread_rwlock_destroy(3)
@@Destroy read-write lock `rwlock'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_destroy([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_rdlock(3)
@@Acquire read lock for `rwlock'
@@@return: EOK:     Success
@@@return: EAGAIN:  The maximum # of read-locks has been acquired
@@@return: EDEADLK: You're already holding a write-lock
@@@return: EDEADLK: [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
@@                  You're already holding a read-lock
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_rdlock([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_tryrdlock(3)
@@Try to acquire read lock for `rwlock'
@@@return: EOK:    Success
@@@return: EBUSY:  A read-lock cannot be acquired at the moment,
@@                 because a write-lock  is already being  held.
@@@return: EAGAIN: The maximum # of read-locks has been acquired
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_tryrdlock([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_wrlock(3)
@@Acquire write lock for `rwlock'
@@@return: EOK:     Success
@@@return: EDEADLK: You're already holding a read-lock
@@@return: EDEADLK: [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
@@                  You're already holding a write-lock
[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_wrlock([[nonnull]] pthread_rwlock_t *rwlock);

@@>> pthread_rwlock_trywrlock(3)
@@Try to acquire write lock for `rwlock'
@@@return: EOK:   Success
@@@return: EBUSY: A write-lock cannot be acquired at the moment,
@@                because read-locks  are  already  being  held.
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_trywrlock([[nonnull]] pthread_rwlock_t *rwlock);

%#ifdef __USE_XOPEN2K
@@>> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
@@Try to acquire read lock for `rwlock' or return after the specified time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
@@@return: EAGAIN:    The maximum # of read-locks has been acquired
@@@return: EDEADLK:   You're already holding a write-lock
@@@return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
@@                    You're already holding a read-lock
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_timedrdlock")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_timedrdlock64")]]
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

@@>> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
@@Try to acquire write lock for `rwlock' or return after the specified time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
@@@return: EDEADLK:   You're already holding a read-lock
@@@return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
@@                    You're already holding a write-lock
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_timedwrlock")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_timedwrlock64")]]
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
[[cp, doc_alias("pthread_rwlock_timedrdlock"), ignore, nocrt, alias("pthread_rwlock_timedrdlock")]]
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_timedrdlock32([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec32 const *__restrict abstime);
[[cp, doc_alias("pthread_rwlock_timedwrlock"), wunused, ignore, nocrt, alias("pthread_rwlock_timedwrlock")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_timedwrlock32([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                      [[nonnull]] struct timespec32 const *__restrict abstime);

[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(pthread_rwlock_timedrdlock), doc_alias("pthread_rwlock_timedrdlock")]]
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

[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(pthread_rwlock_timedwrlock), doc_alias("pthread_rwlock_timedwrlock")]]
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

%#ifdef __USE_SOLARIS
@@>> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
@@Try to acquire  read lock  for `rwlock' or  return after  the specified  time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `reltime' is invalid
@@@return: ETIMEDOUT: The given `reltime' has expired
@@@return: EAGAIN:    The maximum # of read-locks has been acquired
@@@return: EDEADLK:   You're already holding a write-lock
@@@return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
@@                    You're already holding a read-lock
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_reltimedrdlock_np")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_reltimedrdlock64_np")]]
[[userimpl, requires($has_function(pthread_rwlock_reltimedrdlock32_np) || $has_function(pthread_rwlock_reltimedrdlock64_np))]]
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
@@Try to acquire  write lock for  `rwlock' or return  after the specified  time
@@@return: EOK:       Success
@@@return: EINVAL:    The given `reltime' is invalid
@@@return: ETIMEDOUT: The given `reltime' has expired
@@@return: EDEADLK:   You're already holding a read-lock
@@@return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
@@                    You're already holding a write-lock
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_reltimedwrlock_np")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_rwlock_reltimedwrlock64_np")]]
[[userimpl, requires($has_function(pthread_rwlock_reltimedwrlock32_np) || $has_function(pthread_rwlock_reltimedwrlock64_np))]]
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
[[cp, doc_alias("pthread_rwlock_reltimedrdlock_np"), ignore, nocrt, alias("pthread_rwlock_reltimedrdlock_np")]]
[[wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_reltimedrdlock32_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                            [[nonnull]] struct timespec32 const *__restrict reltime);
[[cp, doc_alias("pthread_rwlock_reltimedwrlock_np"), wunused, ignore, nocrt, alias("pthread_rwlock_reltimedwrlock_np")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_rwlock_reltimedwrlock32_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                            [[nonnull]] struct timespec32 const *__restrict reltime);

[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(pthread_rwlock_reltimedrdlock_np), doc_alias("pthread_rwlock_reltimedrdlock_np")]]
[[userimpl, requires_function(pthread_rwlock_reltimedrdlock32_np)]]
$errno_t pthread_rwlock_reltimedrdlock64_np([[nonnull]] pthread_rwlock_t *__restrict rwlock,
                                            [[nonnull]] struct timespec64 const *__restrict reltime) {
	$errno_t result;
	struct timespec32 reltime32;
	reltime32.tv_sec  = (time32_t)reltime->tv_sec;
	reltime32.tv_nsec = reltime->tv_nsec;
	result = pthread_rwlock_reltimedrdlock32_np(rwlock, &reltime32);
	return result;
}

[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(pthread_rwlock_reltimedwrlock_np), doc_alias("pthread_rwlock_reltimedwrlock_np")]]
[[userimpl, requires_function(pthread_rwlock_reltimedwrlock32_np)]]
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
@@Unlock `rwlock'
@@@return: EOK:   Success
@@@return: EPERM: You're not holding a read- or write-lock
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlock_unlock([[nonnull]] pthread_rwlock_t *rwlock);

%
%
%/************************************************************************/
%/* pthread_rwlockattr_t                                                 */
%/************************************************************************/
%

@@>> pthread_rwlockattr_init(3)
@@Initialize attribute object `attr' with default values
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_init([[nonnull]] pthread_rwlockattr_t *attr);

@@>> pthread_rwlockattr_destroy(3)
@@Destroy attribute object  `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_destroy([[nonnull]] pthread_rwlockattr_t *attr);

@@>> pthread_rwlockattr_getpshared(3)
@@Return current setting of process-shared attribute of `attr' in `*pshared'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_rwlockattr_getpshared([[nonnull]] pthread_rwlockattr_t const *__restrict attr,
                                       [[nonnull]] int *__restrict pshared);

@@>> pthread_rwlockattr_setpshared(3)
@@Set process-shared attribute of `attr' to `pshared'
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
@@Set     reader/write     preference
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
@@`attr', or use the default values if later is `NULL'.
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
@@until `abstime'.  `mutex'  is  assumed to  be  locked  before.
@@`abstime' is  an  absolute  time specification;  zero  is  the
@@beginning of the epoch (00:00:00 GMT, January 1, 1970).
@@@return: EOK:       Success
@@@return: EINVAL:    The given `abstime' is invalid
@@@return: ETIMEDOUT: The given `abstime' has expired
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_cond_timedwait")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_cond_timedwait64")]]
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
[[cp, wunused, doc_alias("pthread_cond_timedwait")]]
[[ignore, nocrt, alias("pthread_cond_timedwait")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_cond_timedwait32([[nonnull]] pthread_cond_t *__restrict cond,
                                  [[nonnull]] pthread_mutex_t *__restrict mutex,
                                  [[nonnull]] struct timespec32 const *__restrict abstime);

[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(pthread_cond_timedwait), doc_alias("pthread_cond_timedwait")]]
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

%#ifdef __USE_SOLARIS
@@>> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
@@Wait for  condition  variable  `cond' to  be  signaled  or  broadcast
@@until `reltime'. `mutex' is assumed to be locked before.
@@@return: EOK:       Success
@@@return: EINVAL:    The given `reltime' is invalid
@@@return: ETIMEDOUT: The given `reltime' has expired
[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_cond_reltimedwait_np")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pthread_cond_reltimedwait64_np")]]
[[userimpl, requires($has_function(pthread_cond_reltimedwait32_np) || $has_function(pthread_cond_reltimedwait64_np))]]
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
[[cp, wunused, doc_alias("pthread_cond_reltimedwait_np")]]
[[ignore, nocrt, alias("pthread_cond_reltimedwait_np")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
$errno_t pthread_cond_reltimedwait32_np([[nonnull]] pthread_cond_t *__restrict cond,
                                        [[nonnull]] pthread_mutex_t *__restrict mutex,
                                        [[nonnull]] struct timespec32 const *__restrict reltime);

[[cp, wunused, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(pthread_cond_reltimedwait_np), doc_alias("pthread_cond_reltimedwait_np")]]
[[userimpl, requires_function(pthread_cond_reltimedwait32_np)]]
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
@@Initialize condition variable attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_init([[nonnull]] pthread_condattr_t *attr);

@@>> pthread_condattr_destroy(3)
@@Destroy condition variable attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_destroy([[nonnull]] pthread_condattr_t *attr);

@@>> pthread_condattr_getpshared(3)
@@Get the process-shared flag of the condition variable attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_getpshared([[nonnull]] pthread_condattr_t const *__restrict attr,
                                     [[nonnull]] int *__restrict pshared);

@@>> pthread_condattr_setpshared(3)
@@Set the process-shared flag of the condition variable attribute `attr'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid/unsupported `pshared'
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_setpshared([[nonnull]] pthread_condattr_t *attr, int pshared);

%#ifdef __USE_XOPEN2K

@@>> pthread_condattr_getclock(3)
@@Get the clock selected for the condition variable attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_condattr_getclock([[nonnull]] pthread_condattr_t const *__restrict attr,
                                   [[nonnull]] $clockid_t *__restrict clock_id);

@@>> pthread_condattr_setclock(3)
@@Set the clock selected for the condition variable attribute `attr'
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
@@Initialize the spinlock `lock'. If `pshared' is nonzero
@@the  spinlock can be shared between different processes
@@@return: EOK: Success
[[impl_include("<hybrid/__atomic.h>")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_spin_init([[nonnull]] pthread_spinlock_t *lock, int pshared) {
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}

@@>> pthread_spin_destroy(3)
@@Destroy the spinlock `lock'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_spin_destroy([[nonnull]] pthread_spinlock_t *lock) {
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}

@@>> pthread_spin_lock(3)
@@Wait until spinlock `lock' is retrieved
@@@return: EOK: Success
[[impl_include("<hybrid/__atomic.h>", "<hybrid/sched/__yield.h>")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_spin_lock([[nonnull]] pthread_spinlock_t *lock) {
	while (pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}

@@>> pthread_spin_trylock(3)
@@Try to lock spinlock `lock'
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
@@Release  spinlock  `lock'
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
@@Initialize `barrier' with the attributes in `attr'.
@@The  barrier is opened when `count' waiters arrived
@@@return: EOK:    Success
@@@return: EINVAL: The given `count' is ZERO(0)
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrier_init([[nonnull]] pthread_barrier_t *__restrict barrier,
                              [[nullable]] pthread_barrierattr_t const *__restrict attr,
                              unsigned int count);

@@>> pthread_barrier_destroy(3)
@@Destroy the given (previously dynamically initialized) `barrier'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrier_destroy([[nonnull]] pthread_barrier_t *barrier);

@@>> pthread_barrier_wait(3)
@@Wait on the given `barrier'
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
@@Initialize barrier attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrierattr_init([[nonnull]] pthread_barrierattr_t *attr);

@@>> pthread_barrierattr_destroy(3)
@@Destroy previously dynamically initialized barrier attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrierattr_destroy([[nonnull]] pthread_barrierattr_t *attr);

@@>> pthread_barrierattr_getpshared(3)
@@Get the process-shared flag of the barrier attribute `attr'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_barrierattr_getpshared([[nonnull]] pthread_barrierattr_t const *__restrict attr,
                                        [[nonnull]] int *__restrict pshared);

@@>> pthread_barrierattr_setpshared(3)
@@Set the process-shared flag of the barrier attribute `attr'
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


%[define_type_class(__pthread_destr_function_t = "TP")]


@@>> pthread_key_create(3)
@@Create a key value identifying a location in the thread-specific
@@data area. Each thread maintains a distinct thread-specific data
@@area. `destr_function', if non-`NULL', is called with the  value
@@associated to that key when the key is destroyed.
@@`destr_function' is not called if the value associated is `NULL'
@@when the key is destroyed
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory to create the key
[[nodos, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[export_alias("thr_keycreate")]]
$errno_t pthread_key_create([[nonnull]] pthread_key_t *key,
                            [[nullable]] void (LIBKCALL *destr_function)(void *value));
/* TODO: dos support for `pthread_key_create' (it's in cygwin, so it can exist on DOS!) */


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
@@Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
@@using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
@@make  sure that  even in the  event of multiple  simultaneous threads calling
@@this function, only one will create the  key, and all others will wait  until
@@the key has been  created. Once the  key was created,  further calls to  this
@@function will no longer block, but simply return immediately.
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory to create the key
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[impl_include("<hybrid/__atomic.h>"), export_alias("thr_keycreate_once")]]
[[nodos, requires_function(pthread_key_create)]] /* TODO: dos support for `pthread_key_create_once_np' */
$errno_t pthread_key_create_once_np([[nonnull]] pthread_key_t *key,
                                    [[nullable]] void (LIBKCALL *destr_function)(void *)) {
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
	error = pthread_key_create(&kv, destr_function);
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

	/* Success: key has been created */
	return 0;
}
%#endif /* __USE_SOLARIS */

@@>> pthread_key_delete(3)
@@Destroy the given  `key'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid `key'
[[export_alias("tss_delete")]]
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_key_delete(pthread_key_t key);

@@>> pthread_getspecific(3)
@@Return current value of the thread-specific data slot identified by `key'
@@@return: * :   The value currently associated with `key' in the calling thread
@@@return: NULL: The current value is `NULL'
@@@return: NULL: No value has been bound, yet
@@@return: NULL: Invalid `key'
[[wunused, userimpl, export_alias("tss_get")]]
[[decl_include("<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_getspecificptr_np)]]
void *pthread_getspecific(pthread_key_t key) {
	void **slot = pthread_getspecificptr_np(key);
	return likely(slot) ? *slot : NULL;
}

@@>> pthread_setspecific(3)
@@Store POINTER in the thread-specific data slot identified by `key'
@@@return: EOK:    Success
@@@return: EINVAL: Invalid `key'
@@@return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
@@                 calling  thread, and an attempt to allocate it just now failed
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[export_alias("thr_setspecific")]]
$errno_t pthread_setspecific(pthread_key_t key, void const *pointer);

%#ifdef __USE_KOS
@@>> pthread_getspecificptr_np(3)
@@Return a pointer to the per-thread storage location associated with `key'
@@@return: * :   The address read/written by `pthread_getspecific()' / `pthread_setspecific()'
@@@return: NULL: `key' had yet to be allocated for the calling thread,
@@               and an  attempt  to  allocate  it  just  now  failed.
@@@return: NULL: Invalid `key'.
[[wunused, decl_include("<bits/crt/pthreadtypes.h>")]]
void **pthread_getspecificptr_np(pthread_key_t key);
%#endif /* __USE_KOS */

%#ifdef __USE_XOPEN2K
@@>> pthread_getcpuclockid(3)
@@Get the ID of CPU-time clock for thread `pthread'
@@@return: EOK: Success
[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t pthread_getcpuclockid(pthread_t pthread, [[nonnull]] $clockid_t *clock_id);
%#endif /* __USE_XOPEN2K */


@@>> pthread_atfork(3)
@@Install handlers to be called when a new process is created with  `fork(2)'.
@@The `prepare' handler is called in the parent process just before performing
@@`fork(2)'. The `parent' handler is called  in the parent process just  after
@@`fork(2)'.  The `child' handler is called in  the child process. Each of the
@@three  handlers can be `NULL', meaning that no handler needs to be called at
@@that point.
@@`pthread_atfork(3)' can be called several times, in which case the `prepare'
@@handlers are  called in  LIFO order  (last added  with  `pthread_atfork(3)',
@@first  called before `fork(2)'),  and the `parent'  and `child' handlers are
@@called in FIFO order (first added -> first called)
@@@return: EOK:    Success
@@@return: ENOMEM: Insufficient memory to register callbacks
[[guard, decl_include("<bits/types.h>")]]
$errno_t pthread_atfork([[nullable]] void (LIBCCALL *prepare)(void),
                        [[nullable]] void (LIBCCALL *parent)(void),
                        [[nullable]] void (LIBCCALL *child)(void));

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
@@Returns  1 if the  calling thread is the  main() thread (i.e. the
@@thread  that was  started by the  kernel in order  to execute the
@@calling program), and 0  otherwise. Additionally, -1 is  returned
@@if the  calling  thread  "hasn't been initialized",  though  this
@@isn't a case that can actually happen under KOS's implementation.
[[const, nothrow, guard, export_alias("thr_main")]]
[[requires($has_function(pthread_equal, pthread_mainthread_np, pthread_self) ||
           $has_function(gettid, getpid))]]
int pthread_main_np() {
@@pp_if $has_function(pthread_equal, pthread_mainthread_np, pthread_self)@@
	return pthread_equal(pthread_mainthread_np(), pthread_self());
@@pp_else@@
	return gettid() == getpid();
@@pp_endif@@
}
%#endif /* __USE_BSD */






%{
#endif /* __CC__ */

__SYSDECL_END

}
