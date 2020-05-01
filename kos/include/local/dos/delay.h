/* HASH CRC-32:0x695cc4c6 */
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
/* Dependency: "usleep" from "unistd" */
#ifndef ____localdep_usleep_defined
#define ____localdep_usleep_defined 1
#ifdef __CRT_HAVE_usleep
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_usleep,(__useconds_t __useconds),usleep,(__useconds))
#elif defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay)
#include <local/unistd/usleep.h>
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
#define __localdep_usleep (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(usleep))
#else /* CUSTOM: usleep */
#undef ____localdep_usleep_defined
#endif /* usleep... */
#endif /* !____localdep_usleep_defined */

__NAMESPACE_LOCAL_BEGIN
/* Sleep for `mill' milliseconds (1/1.000 seconds) */
__LOCAL_LIBC(delay) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(delay))(unsigned int __mill) {
#line 81 "kos/src/libc/magic/dos.c"
	__localdep_usleep((__useconds_t)__mill * 1000);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_delay_defined */
