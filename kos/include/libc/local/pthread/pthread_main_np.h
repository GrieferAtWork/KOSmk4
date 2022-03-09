/* HASH CRC-32:0x55f2574 */
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
#if (defined(__CRT_HAVE_gettid) || defined(__CRT_HAVE___threadid) || defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid))
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
#ifndef __local___localdep_gettid_defined
#define __local___localdep_gettid_defined
#ifdef __CRT_HAVE_gettid
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),gettid,())
#elif defined(__CRT_HAVE___threadid)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),__threadid,())
#elif defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_gettid,(void),?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ,())
#else /* ... */
#undef __local___localdep_gettid_defined
#endif /* !... */
#endif /* !__local___localdep_gettid_defined */
__LOCAL_LIBC(pthread_main_np) __ATTR_CONST int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pthread_main_np))(void) {
	return (__NAMESPACE_LOCAL_SYM __localdep_gettid)() == (__NAMESPACE_LOCAL_SYM __localdep_getpid)();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_main_np_defined
#define __local___localdep_pthread_main_np_defined
#define __localdep_pthread_main_np __LIBC_LOCAL_NAME(pthread_main_np)
#endif /* !__local___localdep_pthread_main_np_defined */
#else /* (__CRT_HAVE_gettid || __CRT_HAVE___threadid || __CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ) && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid || __CRT_HAVE___libc_getpid) */
#undef __local_pthread_main_np_defined
#endif /* (!__CRT_HAVE_gettid && !__CRT_HAVE___threadid && !__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ) || (!__CRT_HAVE_getpid && !__CRT_HAVE__getpid && !__CRT_HAVE___getpid && !__CRT_HAVE___libc_getpid) */
#endif /* !__local_pthread_main_np_defined */
