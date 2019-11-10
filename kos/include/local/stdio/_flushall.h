/* HASH CRC-32:0xb2e51ee */
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
#ifndef __local__flushall_defined
#define __local__flushall_defined 1
#include <kos/anno.h>
/* Dependency: "fflush" from "stdio" */
#ifndef ____localdep_fflush_defined
#define ____localdep_fflush_defined 1
#if defined(__CRT_HAVE_fflush_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fflush_nolock) && (defined(__USE_STDIO_UNLOCKED))
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fflush)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),fflush,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_fflush)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),_IO_fflush,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fflush_unlocked)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fflush_nolock)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream)) __THROWS(...)
#else /* LIBC: fflush */
#include <local/stdio/fflush.h>
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
#define __localdep_fflush (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush))
#endif /* fflush... */
#endif /* !____localdep_fflush_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_flushall) int
(__LIBCCALL __LIBC_LOCAL_NAME(_flushall))(void) __THROWS(...) {
#line 2197 "kos/src/libc/magic/stdio.c"
	return __localdep_fflush(__NULLPTR);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__flushall_defined */
