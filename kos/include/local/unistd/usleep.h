/* HASH CRC-32:0x95cd0a10 */
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
#ifndef __local_usleep_defined
#if (defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay))
#define __local_usleep_defined 1
/* Dependency: "__crtSleep" from "unistd" */
#ifndef ____localdep___crtSleep_defined
#define ____localdep___crtSleep_defined 1
#if defined(__CRT_HAVE___crtSleep)
/* Hidden function exported by DOS that allows for millisecond precision */
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep___crtSleep,(__UINT32_TYPE__ __msecs),__crtSleep,(__msecs))
#elif defined(__CRT_HAVE_delay)
/* Hidden function exported by DOS that allows for millisecond precision */
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep___crtSleep,(__UINT32_TYPE__ __msecs),delay,(__msecs))
#else /* LIBC: __crtSleep */
#undef ____localdep___crtSleep_defined
#endif /* __crtSleep... */
#endif /* !____localdep___crtSleep_defined */

__NAMESPACE_LOCAL_BEGIN
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__LOCAL_LIBC(usleep) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(usleep))(__useconds_t __useconds) {
#line 1093 "kos/src/libc/magic/unistd.c"
	__localdep___crtSleep(__useconds / 1000l); /*USEC_PER_MSEC*/
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay)) */
#endif /* !__local_usleep_defined */
