/* HASH CRC-32:0x565bc14b */
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
#ifndef __local_delay_defined
#define __local_delay_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: usleep from unistd */
#ifndef __local___localdep_usleep_defined
#define __local___localdep_usleep_defined 1
#ifdef __CRT_HAVE_usleep
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_usleep,(__useconds_t __useconds),usleep,(__useconds))
#elif defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay)
__NAMESPACE_LOCAL_END
#include <local/unistd/usleep.h>
__NAMESPACE_LOCAL_BEGIN
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
#define __localdep_usleep __LIBC_LOCAL_NAME(usleep)
#else /* ... */
#undef __local___localdep_usleep_defined
#endif /* !... */
#endif /* !__local___localdep_usleep_defined */
/* Sleep for `mill' milliseconds (1/1.000 seconds) */
__LOCAL_LIBC(delay) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(delay))(unsigned int __mill) {
	__localdep_usleep((__useconds_t)__mill * 1000);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_delay_defined
#define __local___localdep_delay_defined 1
#define __localdep_delay __LIBC_LOCAL_NAME(delay)
#endif /* !__local___localdep_delay_defined */
#endif /* !__local_delay_defined */
