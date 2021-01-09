/* HASH CRC-32:0xdaf13733 */
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
#ifndef __local_pthread_main_np_defined
#define __local_pthread_main_np_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_gettid) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getpid from unistd */
#ifndef __local___localdep_getpid_defined
#define __local___localdep_getpid_defined 1
#ifdef __CRT_HAVE_getpid
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__getpid,())
#else /* ... */
#undef __local___localdep_getpid_defined
#endif /* !... */
#endif /* !__local___localdep_getpid_defined */
/* Dependency: gettid from unistd */
#ifndef __local___localdep_gettid_defined
#define __local___localdep_gettid_defined 1
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),gettid,())
#endif /* !__local___localdep_gettid_defined */
/* >> pthread_main_np(3)
 * Returns 1 if the calling thread is the main() thread (i.e. the
 * thread that was started by the kernel in order to execute the
 * calling program), and 0 otherwise. Additionally, -1 is returned
 * if the calling thread "hasn't been initialized", though this
 * isn't a case that can actually happen under KOS's implementation. */
__LOCAL_LIBC(pthread_main_np) __ATTR_CONST int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pthread_main_np))(void) {
	return __localdep_gettid() == __localdep_getpid();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_main_np_defined
#define __local___localdep_pthread_main_np_defined 1
#define __localdep_pthread_main_np __LIBC_LOCAL_NAME(pthread_main_np)
#endif /* !__local___localdep_pthread_main_np_defined */
#else /* __CRT_HAVE_gettid && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid) */
#undef __local_pthread_main_np_defined
#endif /* !__CRT_HAVE_gettid || (!__CRT_HAVE_getpid && !__CRT_HAVE__getpid && !__CRT_HAVE___getpid) */
#endif /* !__local_pthread_main_np_defined */
