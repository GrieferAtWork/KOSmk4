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
#ifndef __GUARD_HYBRID_SCHED___YIELD_H
#define __GUARD_HYBRID_SCHED___YIELD_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __CC__
#ifndef __hybrid_yield

#if defined(__KERNEL__) && defined(__KOS__)
/************************************************************************/
/* KOS Kernel                                                           */
/************************************************************************/

#ifndef __KOS_VERSION__
#define __KOS_VERSION__ 200 /* Legacy model. */
#endif /* !__KOS_VERSION__ */

#if __KOS_VERSION__ >= 400
/************************************************************************/
/* KOS mk4                                                              */
/************************************************************************/

#ifdef __INTELLISENSE__
__DECL_BEGIN
void (__hybrid_yield)(void);
__BOOL (__hybrid_yield_nx)(void);
__DECL_END
#define __hybrid_yield    __hybrid_yield
#define __hybrid_yield_nx __hybrid_yield_nx
#else /* __INTELLISENSE__ */
#include <sched/task.h>
#define __hybrid_yield    task_yield
#define __hybrid_yield_nx task_yield_nx
#endif /* !__INTELLISENSE__ */

#elif __KOS_VERSION__ >= 300
/************************************************************************/
/* KOS mk3                                                              */
/************************************************************************/

__DECL_BEGIN
#ifndef __task_yield_defined
#define __task_yield_defined
__PUBDEF void (__KCALL task_yield)(void);
#endif /* !__task_yield_defined */
#define __hybrid_yield task_yield
__DECL_END

#elif __KOS_VERSION__ >= 200
/************************************************************************/
/* KOS mk2                                                              */
/************************************************************************/

__DECL_BEGIN
#ifndef __errno_t_defined
#define __errno_t_defined
typedef int errno_t;
#endif /* !__errno_t_defined */

#ifndef __task_yield_defined
#define __task_yield_defined
/* Yield the remainder of the caller's quantum to the next
 * scheduled task (no-op if no task to switch to  exists).
 * HINT: All registers but EAX are preserved across a call to this function.
 * @return: -EOK:       Another task was executed before this function returned.
 * @return: -EAGAIN:    There was no other task to switch to. */
__PUBDEF errno_t (__KCALL task_yield)(void);

#if (!defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_GCC_ASM) &&      \
     (!defined(__x86_64__) || defined(CONFIG_BUILDING_KERNEL_CORE)) && \
     defined(__i386__))
/* Take advantage of the fact that `task_yield()' doesn't clobber anything. */
#define task_yield()                             \
	__XBLOCK({                                   \
		register errno_t __y_err;                \
		__asm__ __volatile__("call task_yield\n" \
		                     : "=a"(__y_err));   \
		__XRETURN __y_err;                       \
	})
#endif /* ... */
#endif /* !__task_yield_defined */
#define __hybrid_yield task_yield
__DECL_END
#endif

#elif defined(sched_yield) || defined(__sched_yield_defined)
#define __hybrid_yield sched_yield
#elif defined(__sched_yield) || defined(____sched_yield_defined)
#define __hybrid_yield __sched_yield
#elif defined(pthread_yield) || defined(__pthread_yield_defined)
#define __hybrid_yield pthread_yield
#elif defined(__pthread_yield) || defined(____pthread_yield_defined)
#define __hybrid_yield __pthread_yield
#elif defined(thrd_yield) || defined(__thrd_yield_defined)
#define __hybrid_yield thrd_yield
#elif defined(__thrd_yield) || defined(____thrd_yield_defined)
#define __hybrid_yield __thrd_yield
#elif defined(__BUILDING_LIBC) && defined(__KOS__)
/************************************************************************/
/* LIBC                                                                 */
/************************************************************************/

#ifdef __WANT_INLINE_SYSCALLS
#include <kos/syscalls.h>
#if __CRT_HAVE_SC(sched_yield)
#define __hybrid_yield sys_sched_yield
#endif /* __CRT_HAVE_SC(sched_yield) */
#endif /* __WANT_INLINE_SYSCALLS */
#ifndef __hybrid_yield
#include <__crt.h>
__DECL_BEGIN
__INTDEF int (__LIBCCALL libc_sched_yield)(void);
__DECL_END
#define __hybrid_yield libc_sched_yield
#endif /* !__hybrid_yield */

#elif defined(__KOS_SYSTEM_HEADERS__) && __KOS_VERSION__ >= 400
/************************************************************************/
/* KOS mk4 user-space application                                       */
/************************************************************************/

#include <__crt.h>
#ifdef __CRT_HAVE_sched_yield
#undef sched_yield
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__CDECLARE(,int,__NOTHROW,sched_yield,(void),())
__NAMESPACE_INT_END __DECL_END
#define __hybrid_yield (__NAMESPACE_INT_SYM sched_yield)
#elif defined(__CRT_HAVE___sched_yield)
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__CDECLARE(,int,__NOTHROW,__sched_yield,(void),())
__NAMESPACE_INT_END __DECL_END
#define __hybrid_yield (__NAMESPACE_INT_SYM __sched_yield)
#elif defined(__CRT_HAVE_pthread_yield)
#undef pthread_yield
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__CDECLARE(,int,__NOTHROW,pthread_yield,(void),())
__NAMESPACE_INT_END __DECL_END
#define __hybrid_yield (__NAMESPACE_INT_SYM pthread_yield)
#elif defined(__CRT_HAVE___pthread_yield)
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__CDECLARE(,int,__NOTHROW,__pthread_yield,(void),())
__NAMESPACE_INT_END __DECL_END
#define __hybrid_yield (__NAMESPACE_INT_SYM __pthread_yield)
#elif defined(__CRT_HAVE_yield)
#undef yield
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__CDECLARE(,int,__NOTHROW,yield,(void),())
__NAMESPACE_INT_END __DECL_END
#define __hybrid_yield (__NAMESPACE_INT_SYM yield)
#elif defined(__CRT_HAVE_thrd_yield)
#undef yield
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__CDECLARE_VOID(,__NOTHROW,thrd_yield,(void),())
__NAMESPACE_INT_END __DECL_END
#define __hybrid_yield (__NAMESPACE_INT_SYM thrd_yield)
#elif defined(__CRT_HAVE_thr_yield)
#undef yield
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__CDECLARE_VOID(,__NOTHROW,thr_yield,(void),())
__NAMESPACE_INT_END __DECL_END
#define __hybrid_yield (__NAMESPACE_INT_SYM thr_yield)
#elif defined(__NO_has_include) || __has_include(<kos/syscalls.h>)
#include <kos/syscalls.h>
#if __CRT_HAVE_SC(sched_yield)
#define __hybrid_yield sys_sched_yield
#endif /* __CRT_HAVE_SC(sched_yield) */
#endif /* ... */
#elif defined(__WINNT__)
/************************************************************************/
/* Windows                                                              */
/************************************************************************/
__DECL_BEGIN __NAMESPACE_INT_BEGIN
__IMPDEF __ULONG32_TYPE__ __ATTR_STDCALL SleepEx(__ULONG32_TYPE__ __msec, __INT32_TYPE__ __alertable);
#define __hybrid_yield() ((__NAMESPACE_INT_SYM SleepEx)(0, 0))
__NAMESPACE_INT_END __DECL_END
#elif (defined(__linux__) && (__has_include(<sched.h>) || defined(__NO_has_include)))
/************************************************************************/
/* Linux                                                                */
/************************************************************************/
#include <sched.h>
#define __hybrid_yield sched_yield
#elif (__has_include(<pthread.h>) || (defined(__unix__) && defined(__NO_has_include)))
/************************************************************************/
/* PThread                                                              */
/************************************************************************/
#include <pthread.h>
#define __hybrid_yield pthread_yield
#elif (__has_include(<threads.h>) ||                                  \
       (defined(__NO_has_include) && !defined(__STDC_NO_THREADS__) && \
        defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L))
/************************************************************************/
/* C11 Threads                                                          */
/************************************************************************/
#include <threads.h>
#define __hybrid_yield thrd_yield
#else /* Implementation... */
#if (__has_include(<unistd.h>) || \
     (defined(__unix__) && defined(__NO_has_include)))
/************************************************************************/
/* Generic, direct syscall                                              */
/************************************************************************/
#include <unistd.h>
#ifdef SYS_sched_yield
#define __hybrid_yield() syscall(SYS_sched_yield)
#elif defined(__NR_sched_yield)
#define __hybrid_yield() syscall(__NR_sched_yield)
#endif /* ... */
#endif /* Unistd... */
#endif /* !Implementation... */

/* If not possible to define in any other way, fall back to a no-op */
#ifndef __hybrid_yield
#define __NO_hybrid_yield 1
#define __hybrid_yield() (void)0
#endif /* !__hybrid_yield */
#endif /* !__hybrid_yield */

#ifndef __hybrid_yield_nx
#ifndef __NO_hybrid_yield
#define __hybrid_yield_nx() (__hybrid_yield(), 1)
#else /* !__NO_hybrid_yield */
#define __NO_hybrid_yield_nx 1
#define __hybrid_yield_nx() 1
#endif /* __NO_hybrid_yield */
#endif /* !__hybrid_yield_nx */
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_SCHED___YIELD_H */
