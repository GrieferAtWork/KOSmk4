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
#ifndef __GUARD_HYBRID_SCHED___GETTID_H
#define __GUARD_HYBRID_SCHED___GETTID_H 1

#include <__stdinc.h>

#ifdef __KOS__
#ifdef __KERNEL__
#ifndef __KOS_VERSION__
#define __KOS_VERSION__ 200 /* Legacy model. */
#endif /* !__KOS_VERSION__ */

#if __KOS_VERSION__ >= 400
#include <sched/pertask.h> /* THIS_TASK */
#elif __KOS_VERSION__ >= 300
#include <sched/task.h> /* THIS_TASK */
#else /* __KOS_VERSION__ >= ... */
#include <sched/percpu.h> /* THIS_TASK */
#endif /* __KOS_VERSION__ < ... */

#define __HYBRID_SIZEOF_TID__           __SIZEOF_POINTER__
#define __HYBRID_GETTID_INVALID_IS_ZERO 1
#define __HYBRID_GETTID_INVALID         __NULLPTR
#define __HYBRID_GETTID_PRINTF_FMT      "%p"
#define __HYBRID_GETTID_PRINTF_ARG(x)   x
#ifdef __CC__
#define __hybrid_gettid() THIS_TASK
#define __hybrid_tid_t    struct task *
#endif /* __CC__ */

#else /* __KERNEL__ */

#if (__KOS_VERSION__ >= 400) && \
    (defined(__x86_64__) || defined(__i386__))
#include <asm/intrin.h>

/* Use the ELF thread-self pointer! */
#ifdef __CC__
__DECL_BEGIN
#define __hybrid_tid_t void *
#ifdef __x86_64__
#define __hybrid_gettid() __rdfsptr(0)
#else /* __x86_64__ */
#define __hybrid_gettid() __rdgsptr(0)
/* TODO: `__hybrid_gettid_iscaller(p) --> cmpl %gs:0, <p>' */
#endif /* !__x86_64__ */
__DECL_END
#endif /* __CC__ */

#define __HYBRID_SIZEOF_TID__           __SIZEOF_POINTER__
#define __HYBRID_GETTID_PRINTF_FMT      "%p"
#define __HYBRID_GETTID_PRINTF_ARG(x)   (void *)(x)
#define __HYBRID_GETTID_INVALID_IS_ZERO 1
#define __HYBRID_GETTID_INVALID         0

#else /* Mk4 + X86 */
#include <__crt.h>
#include <bits/types.h>

#define __HYBRID_SIZEOF_TID__           __SIZEOF_PID_T__
#if __HYBRID_SIZEOF_TID__ <= __SIZEOF_INT__
#define __HYBRID_GETTID_PRINTF_FMT     "%u"
#define __HYBRID_GETTID_PRINTF_ARG(x)  (unsigned int)(x)
#else
#define __HYBRID_GETTID_PRINTF_FMT     "%llu"
#define __HYBRID_GETTID_PRINTF_ARG(x)  (unsigned long long)(x)
#endif
#if 1
#define __HYBRID_GETTID_INVALID_IS_ZERO 1 /* Not always, but good enough? */
#define __HYBRID_GETTID_INVALID         0
#else
#define __HYBRID_GETTID_INVALID       (-1)
#endif

#ifdef __CC__
#define __hybrid_tid_t __pid_t
__DECL_BEGIN
__CREDIRECT(__ATTR_CONST,__pid_t,__NOTHROW,__hybrid_gettid,(void),gettid,())
#define __hybrid_gettid __hybrid_gettid
__DECL_END
#endif /* __CC__ */
#endif /* ... */

#endif /* !__KERNEL__ */
#elif (defined(__DOS_COMPAT__) && !defined(__CRT_KOS)) || \
      (defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || defined(__WINDOWS__) || \
       defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) || \
       defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
       defined(_WIN32_WCE) || defined(WIN32_WCE))
#define __HYBRID_SIZEOF_TID__           4
#define __HYBRID_GETTID_INVALID_IS_ZERO 1
#define __HYBRID_GETTID_INVALID         0
#define __HYBRID_GETTID_PRINTF_FMT      "%u"
#define __HYBRID_GETTID_PRINTF_ARG(x)   (unsigned int)(x)

#ifdef __CC__
#include <hybrid/typecore.h>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4559) /* Suppress warning about our addition of `ATTR_CONST' */
#endif /* _MSC_VER */
__DECL_BEGIN
#define __hybrid_tid_t __ULONG32_TYPE__
extern __ATTR_CONST __ATTR_DLLIMPORT __ULONG32_TYPE__ (__ATTR_STDCALL GetCurrentThreadId)(void);
__DECL_END
#ifdef _MSC_VER
#pragma warning(pop)
#endif /* !_MSC_VER */
#define __hybrid_gettid() GetCurrentThreadId()
#endif /* __CC__ */

#elif defined(__unix__) || defined(__unix) || defined(unix)

#include <unistd.h>

#ifdef SYS_gettid
#ifdef __SIZEOF_PID_T__
#define __HYBRID_SIZEOF_TID__ __SIZEOF_PID_T__
#elif defined(__SIZEOF_PID_T)
#define __HYBRID_SIZEOF_TID__ __SIZEOF_PID_T
#else /* ... */
#define __HYBRID_SIZEOF_TID__ __SIZEOF_INT__
__STATIC_ASSERT_MSG(sizeof(pid_t) == __HYBRID_SIZEOF_TID__, "Please adjust");
#endif /* !... */
#if __HYBRID_SIZEOF_TID__ <= __SIZEOF_INT__
#define __HYBRID_GETTID_PRINTF_FMT    "%u"
#define __HYBRID_GETTID_PRINTF_ARG(x) (unsigned int)(x)
#else /* __HYBRID_SIZEOF_TID__ <= __SIZEOF_INT__ */
#define __HYBRID_GETTID_PRINTF_FMT    "%llu"
#define __HYBRID_GETTID_PRINTF_ARG(x) (unsigned long long)(x)
#endif /* __HYBRID_SIZEOF_TID__ > __SIZEOF_INT__ */
#define __hybrid_tid_t                  pid_t
#define __hybrid_gettid()               syscall(SYS_gettid)
#define __HYBRID_GETTID_INVALID_IS_ZERO 1
#define __HYBRID_GETTID_INVALID         0
#endif /* !SYS_gettid */

#endif /* ... */


#ifndef __hybrid_gettid
#if __has_include(<pthread.h>) || defined(__unix__) || defined(__unix) || defined(unix)
#include <pthread.h>
#ifdef __SIZEOF_PTHREAD_T__
#define __HYBRID_SIZEOF_TID__  __SIZEOF_PTHREAD_T__
#elif defined(__SIZEOF_PTHREAD_T)
#define __HYBRID_SIZEOF_TID__  __SIZEOF_PTHREAD_T
#else /* ... */
#include <hybrid/typecore.h>
#define __HYBRID_SIZEOF_TID__  __SIZEOF_POINTER__
__STATIC_ASSERT_MSG(sizeof(pthread_t) == __HYBRID_SIZEOF_TID__, "Please adjust");
#endif /* !... */
#define __hybrid_tid_t pthread_t
#if __HYBRID_SIZEOF_TID__ <= __SIZEOF_POINTER__
#if __HYBRID_SIZEOF_TID__ <= __SIZEOF_INT__
#define __HYBRID_GETTID_PRINTF_FMT     "%u"
#define __HYBRID_GETTID_PRINTF_ARG(x)  (unsigned int)(x)
#else /* __HYBRID_SIZEOF_TID__ <= __SIZEOF_INT__ */
#define __HYBRID_GETTID_PRINTF_FMT     "%llu"
#define __HYBRID_GETTID_PRINTF_ARG(x)  (unsigned long long)(x)
#endif /* __HYBRID_SIZEOF_TID__ > __SIZEOF_INT__ */
#else /* __HYBRID_SIZEOF_TID__ <= __SIZEOF_POINTER__ */
#define __HYBRID_GETTID_PRINTF_FMT     "%u?"
#define __HYBRID_GETTID_PRINTF_ARG(x)   0u
#endif /* __HYBRID_SIZEOF_TID__ > __SIZEOF_POINTER__ */

#define __hybrid_gettid()               pthread_self()
#define __HYBRID_GETTID_INVALID_IS_ZERO 1 /* Not always, but good enough? */
#define __HYBRID_GETTID_INVALID         0
#define __hybrid_gettid_equal(a, b)     pthread_equal(a, b)
#else /* ... */
#include <hybrid/typecore.h>

#define __HYBRID_SIZEOF_TID__           __SIZEOF_INT__
#define __HYBRID_GETTID_INVALID_IS_ZERO 1 /* Not always, but good enough? */
#define __HYBRID_GETTID_INVALID         0
#define __HYBRID_GETTID_PRINTF_FMT      "%u"
#define __HYBRID_GETTID_PRINTF_ARG(x)   (unsigned int)(x)
#ifdef __CC__
#define __hybrid_tid_t    int
#define __hybrid_gettid() 1 /* ??? */
#endif /* __CC__ */
#endif /* !... */
#endif /* !__hybrid_gettid */

#ifndef __hybrid_gettid_equal
#define __hybrid_gettid_equal(a, b) ((a) == (b))
#endif /* !__hybrid_gettid_equal */

#ifndef __hybrid_gettid_iscaller
#define __hybrid_gettid_iscaller(tid) \
	__hybrid_gettid_equal(__hybrid_gettid(), tid)
#endif /* !__hybrid_gettid_iscaller */


#endif /* !__GUARD_HYBRID_SYNC_THREADID_H */
