/* HASH CRC-32:0xcdf64caa */
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
#ifndef __local_raise_defined
#define __local_raise_defined
#include <__crt.h>
#if ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpid_defined
#define __local___localdep_getpid_defined
#ifdef __CRT_HAVE_getpid
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__getpid,())
#elif defined(__CRT_HAVE___libc_getpid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__libc_getpid,())
#else /* ... */
#undef __local___localdep_getpid_defined
#endif /* !... */
#endif /* !__local___localdep_getpid_defined */
#ifndef __local___localdep_kill_defined
#define __local___localdep_kill_defined
#ifdef __CRT_HAVE_kill
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),kill,(__pid,__signo))
#elif defined(__CRT_HAVE___kill)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),__kill,(__pid,__signo))
#elif defined(__CRT_HAVE___libc_kill)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),__libc_kill,(__pid,__signo))
#else /* ... */
#undef __local___localdep_kill_defined
#endif /* !... */
#endif /* !__local___localdep_kill_defined */
#ifndef __local___localdep_pthread_kill_defined
#define __local___localdep_pthread_kill_defined
#ifdef __CRT_HAVE_pthread_kill
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_kill,(__pthread_t __pthread, __signo_t __signo),pthread_kill,(__pthread,__signo))
#elif defined(__CRT_HAVE_thr_kill)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_kill,(__pthread_t __pthread, __signo_t __signo),thr_kill,(__pthread,__signo))
#else /* ... */
#undef __local___localdep_pthread_kill_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_kill_defined */
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
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(raise) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(raise))(__signo_t __signo) {
#if (defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))
	__errno_t __error;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_kill)((__NAMESPACE_LOCAL_SYM __localdep_pthread_self)(), __signo);
	if __unlikely(__error != __EOK)
		__error = (__errno_t)__libc_seterrno(__error);
	return (int)__error;
#else /* (__CRT_HAVE_pthread_kill || __CRT_HAVE_thr_kill) && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self) */
	return (__NAMESPACE_LOCAL_SYM __localdep_kill)((__NAMESPACE_LOCAL_SYM __localdep_getpid)(), __signo);
#endif /* (!__CRT_HAVE_pthread_kill && !__CRT_HAVE_thr_kill) || (!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_raise_defined
#define __local___localdep_raise_defined
#define __localdep_raise __LIBC_LOCAL_NAME(raise)
#endif /* !__local___localdep_raise_defined */
#else /* ((__CRT_HAVE_pthread_kill || __CRT_HAVE_thr_kill) && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self)) || ((__CRT_HAVE_kill || __CRT_HAVE___kill || __CRT_HAVE___libc_kill) && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid || __CRT_HAVE___libc_getpid)) */
#undef __local_raise_defined
#endif /* ((!__CRT_HAVE_pthread_kill && !__CRT_HAVE_thr_kill) || (!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self)) && ((!__CRT_HAVE_kill && !__CRT_HAVE___kill && !__CRT_HAVE___libc_kill) || (!__CRT_HAVE_getpid && !__CRT_HAVE__getpid && !__CRT_HAVE___getpid && !__CRT_HAVE___libc_getpid)) */
#endif /* !__local_raise_defined */
