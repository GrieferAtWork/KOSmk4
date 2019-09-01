/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_SCHED___YIELD_H
#define __GUARD_HYBRID_SCHED___YIELD_H 1

#include "../../__stdinc.h"
#include <hybrid/typecore.h>

__DECL_BEGIN

#ifdef __CC__
#ifndef __hybrid_yield
#if defined(__KERNEL__) && defined(__KOS__)
#ifndef __KOS_VERSION__
#define __KOS_VERSION__ 200 /* Legacy model. */
#endif

#ifndef __task_yield_defined
#define __task_yield_defined 1
#if __KOS_VERSION__ < 300
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
/* Yield the remainder of the caller's quantum to the next
 * scheduled task (no-op if no task to switch to exists).
 * HINT: All registers but EAX are preserved across a call to this function.
 * @return: -EOK:       Another task was executed before this function returned.
 * @return: -EAGAIN:    There was no other task to switch to. */
__PUBDEF errno_t (__KCALL task_yield)(void);

#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_GCC_ASM) && \
   (!defined(__x86_64__) || defined(CONFIG_BUILDING_KERNEL_CORE)) && \
     defined(__i386__)
/* Take advantage of the fact that `task_yield()' doesn't clobber anything. */
#define task_yield() \
 __XBLOCK({ register errno_t __y_err; \
            __asm__ __volatile__("call task_yield\n" : "=a" (__y_err)); \
            __XRETURN __y_err; \
 })
#endif
#define __hybrid_yield() task_yield()
#elif __KOS_VERSION__ >= 400
#include <__crt.h>
#if defined(__CRT_HAVE_task_yield) && defined(__CRT_HAVE_task_yield_nx)
#ifdef THROWS
__PUBDEF void (__KCALL task_yield)(void) THROWS(E_WOULDBLOCK_PREEMPTED);
#else /* THROWS */
__PUBDEF void (__KCALL task_yield)(void);
#endif /* !THROWS */
__PUBDEF __BOOL __NOTHROW(__KCALL task_yield_nx)(void);
#define __hybrid_yield()    task_yield()
#define __hybrid_yield_nx() task_yield_nx()
#else /* __CRT_HAVE_task_yield */
#undef __task_yield_defined
#endif /* !__CRT_HAVE_task_yield */
#else
__PUBDEF void (__KCALL task_yield)(void);
#define __hybrid_yield() task_yield()
#endif
#endif /* !__task_yield_defined */
#elif defined(__BUILDING_LIBC) && defined(__KOS__)
__INTDEF int (__ATTR_CDECL libc_sched_yield)(void);
#define __hybrid_yield() libc_sched_yield()
#elif defined(__KOS_SYSTEM_HEADERS__) && __KOS_VERSION__ >= 400
#include <__crt.h>
#if defined(__CRT_HAVE_sched_yield)
__NAMESPACE_INT_BEGIN
__LIBC int (__LIBCCALL sched_yield)(void);
__NAMESPACE_INT_END
#define __hybrid_yield() (__NAMESPACE_INT_SYM sched_yield)()
#elif defined(__CRT_HAVE___sched_yield)
__NAMESPACE_INT_BEGIN
__LIBC int (__LIBCCALL __sched_yield)(void);
__NAMESPACE_INT_END
#define __hybrid_yield() (__NAMESPACE_INT_SYM __sched_yield)()
#elif defined(__CRT_HAVE_pthread_yield)
__NAMESPACE_INT_BEGIN
__LIBC int (__LIBCCALL pthread_yield)(void);
__NAMESPACE_INT_END
#define __hybrid_yield() (__NAMESPACE_INT_SYM pthread_yield)()
#elif defined(__CRT_HAVE___pthread_yield)
__NAMESPACE_INT_BEGIN
__LIBC int (__LIBCCALL __pthread_yield)(void);
__NAMESPACE_INT_END
#define __hybrid_yield() (__NAMESPACE_INT_SYM __pthread_yield)()
#elif defined(__NO_has_include) || __has_include(<kos/syscalls.h>)
#include <kos/syscalls.h>
#if __CRT_HAVE_SC(sched_yield)
#define __hybrid_yield()  sys_sched_yield()
#endif
#endif
#elif (defined(__DOS_COMPAT__) && !defined(__CRT_KOS)) || \
      (defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || defined(__WINDOWS__) || \
       defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) || \
       defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
       defined(_WIN32_WCE) || defined(WIN32_WCE))
__NAMESPACE_INT_BEGIN
__IMPDEF __ULONG32_TYPE__ __ATTR_STDCALL SleepEx(__ULONG32_TYPE__ __msec, __INT32_TYPE__ __alertable);
#define __hybrid_yield() ((__NAMESPACE_INT_SYM SleepEx)(20,0))
__NAMESPACE_INT_END
#elif defined(__linux__) || defined(__linux) || defined(linux) || \
      defined(__LINUX__) || defined(__LINUX) || defined(LINUX) || \
      __has_include(<sched.h>)
#include <sched.h>
#define __hybrid_yield() sched_yield()
#elif __has_include(<pthread.h>) || \
     (defined(__unix__) || defined(__unix) || defined(unix))
#include <pthread.h>
#define __hybrid_yield() pthread_yield()
#endif

#ifndef __hybrid_yield
#define __NO_hybrid_yield 1
#define __hybrid_yield() (void)0
#endif /* !__hybrid_yield */
#endif /* !__hybrid_yield */

#ifndef __hybrid_yield_nx
#ifndef __NO_hybrid_yield
#define __hybrid_yield_nx() (__hybrid_yield(),1)
#else
#define __NO_hybrid_yield_nx 1
#define __hybrid_yield_nx() 1
#endif
#endif /* !__hybrid_yield_nx */
#endif /* __CC__ */

__DECL_END

#endif /* !__GUARD_HYBRID_SCHED___YIELD_H */
