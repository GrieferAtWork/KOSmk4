/* HASH CRC-32:0x6eb747d2 */
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
#ifndef __local_pthread_main_np_defined
#define __local_pthread_main_np_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_pthread_mainthread_np) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))) || ((defined(__CRT_HAVE_gettid) || defined(__CRT_HAVE___threadid) || defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpid_defined
#define __local___localdep_getpid_defined
#ifdef __CRT_HAVE_getpid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__getpid,())
#elif defined(__CRT_HAVE___libc_getpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__libc_getpid,())
#else /* ... */
#undef __local___localdep_getpid_defined
#endif /* !... */
#endif /* !__local___localdep_getpid_defined */
#ifndef __local___localdep_gettid_defined
#define __local___localdep_gettid_defined
#ifdef __CRT_HAVE_gettid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),gettid,())
#elif defined(__CRT_HAVE___threadid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),__threadid,())
#elif defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ,())
#else /* ... */
#undef __local___localdep_gettid_defined
#endif /* !... */
#endif /* !__local___localdep_gettid_defined */
#ifndef __local___localdep_pthread_equal_defined
#define __local___localdep_pthread_equal_defined
#ifdef __CRT_HAVE_pthread_equal
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_pthread_equal,(__pthread_t __thr1, __pthread_t __thr2),pthread_equal,{ return __thr1 == __thr2; })
#elif defined(__CRT_HAVE_thrd_equal)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_pthread_equal,(__pthread_t __thr1, __pthread_t __thr2),thrd_equal,{ return __thr1 == __thr2; })
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_pthread_equal)(__pthread_t __thr1, __pthread_t __thr2) { return __thr1 == __thr2; }
#endif /* !... */
#endif /* !__local___localdep_pthread_equal_defined */
#if !defined(__local___localdep_pthread_mainthread_np_defined) && defined(__CRT_HAVE_pthread_mainthread_np)
#define __local___localdep_pthread_mainthread_np_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_mainthread_np,(void),pthread_mainthread_np,())
#endif /* !__local___localdep_pthread_mainthread_np_defined && __CRT_HAVE_pthread_mainthread_np */
#ifndef __local___localdep_pthread_self_defined
#define __local___localdep_pthread_self_defined
#ifdef __CRT_HAVE_pthread_self
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),pthread_self,())
#elif defined(__CRT_HAVE_thrd_current)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),thrd_current,())
#elif defined(__CRT_HAVE_thr_self)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),thr_self,())
#elif defined(__CRT_HAVE_cthread_self)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),cthread_self,())
#else /* ... */
#undef __local___localdep_pthread_self_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_self_defined */
__LOCAL_LIBC(pthread_main_np) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pthread_main_np))(void) {
#if defined(__CRT_HAVE_pthread_mainthread_np) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))
	return (__NAMESPACE_LOCAL_SYM __localdep_pthread_equal)((__NAMESPACE_LOCAL_SYM __localdep_pthread_mainthread_np)(), (__NAMESPACE_LOCAL_SYM __localdep_pthread_self)());
#else /* __CRT_HAVE_pthread_mainthread_np && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self) */
	return (__NAMESPACE_LOCAL_SYM __localdep_gettid)() == (__NAMESPACE_LOCAL_SYM __localdep_getpid)();
#endif /* !__CRT_HAVE_pthread_mainthread_np || (!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_main_np_defined
#define __local___localdep_pthread_main_np_defined
#define __localdep_pthread_main_np __LIBC_LOCAL_NAME(pthread_main_np)
#endif /* !__local___localdep_pthread_main_np_defined */
#else /* (__CRT_HAVE_pthread_mainthread_np && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self)) || ((__CRT_HAVE_gettid || __CRT_HAVE___threadid || __CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ) && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid || __CRT_HAVE___libc_getpid)) */
#undef __local_pthread_main_np_defined
#endif /* (!__CRT_HAVE_pthread_mainthread_np || (!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self)) && ((!__CRT_HAVE_gettid && !__CRT_HAVE___threadid && !__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ) || (!__CRT_HAVE_getpid && !__CRT_HAVE__getpid && !__CRT_HAVE___getpid && !__CRT_HAVE___libc_getpid)) */
#endif /* !__local_pthread_main_np_defined */
