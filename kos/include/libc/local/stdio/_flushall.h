/* HASH CRC-32:0x3fb300d6 */
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
#ifndef __local__flushall_defined
#define __local__flushall_defined 1
#include <__crt.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fflush_defined
#define __local___localdep_fflush_defined 1
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_fflush_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__THROWING,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__THROWING,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
__CREDIRECT(,int,__THROWING,__localdep_fflush,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
__CREDIRECT(,int,__THROWING,__localdep_fflush,(__FILE *__stream),_IO_fflush,(__stream))
#elif defined(__CRT_HAVE_fflush_unlocked)
__CREDIRECT(,int,__THROWING,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
__CREDIRECT(,int,__THROWING,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fflush.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fflush __LIBC_LOCAL_NAME(fflush)
#endif /* !... */
#endif /* !__local___localdep_fflush_defined */
__LOCAL_LIBC(_flushall) int
(__LIBCCALL __LIBC_LOCAL_NAME(_flushall))(void) __THROWS(...) {
	return __localdep_fflush(__NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__flushall_defined
#define __local___localdep__flushall_defined 1
#define __localdep__flushall __LIBC_LOCAL_NAME(_flushall)
#endif /* !__local___localdep__flushall_defined */
#endif /* !__local__flushall_defined */
