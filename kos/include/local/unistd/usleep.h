/* HASH CRC-32:0xe885b680 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_usleep_defined
#define __local_usleep_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: __crtSleep from unistd */
#ifndef __local___localdep___crtSleep_defined
#define __local___localdep___crtSleep_defined 1
#ifdef __CRT_HAVE___crtSleep
/* Hidden function exported by DOS that allows for millisecond precision */
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep___crtSleep,(__UINT32_TYPE__ __msecs),__crtSleep,(__msecs))
#elif defined(__CRT_HAVE_delay)
/* Hidden function exported by DOS that allows for millisecond precision */
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep___crtSleep,(__UINT32_TYPE__ __msecs),delay,(__msecs))
#else /* ... */
#undef __local___localdep___crtSleep_defined
#endif /* !... */
#endif /* !__local___localdep___crtSleep_defined */
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__LOCAL_LIBC(usleep) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(usleep))(__useconds_t __useconds) {
	__localdep___crtSleep(__useconds / 1000l); /*USEC_PER_MSEC*/
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_usleep_defined
#define __local___localdep_usleep_defined 1
#define __localdep_usleep __LIBC_LOCAL_NAME(usleep)
#endif /* !__local___localdep_usleep_defined */
#else /* __CRT_HAVE___crtSleep || __CRT_HAVE_delay */
#undef __local_usleep_defined
#endif /* !__CRT_HAVE___crtSleep && !__CRT_HAVE_delay */
#endif /* !__local_usleep_defined */
