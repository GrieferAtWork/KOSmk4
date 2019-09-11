/* HASH 0xd6a44fe5 */
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
#ifndef __local_flushall_unlocked_defined
#define __local_flushall_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "fflush_unlocked" from "stdio" */
#ifndef ____localdep_fflush_unlocked_defined
#define ____localdep_fflush_unlocked_defined 1
#if defined(__CRT_HAVE_fflush_unlocked)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),fflush_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),fflush,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fflush_nolock)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),_fflush_nolock,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),fflush,(__stream)) __THROWS(...)
#else /* LIBC: fflush */
#include <local/stdio/fflush.h>
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fflush_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush))
#endif /* fflush_unlocked... */
#endif /* !____localdep_fflush_unlocked_defined */

/* Dependency: "_flushall" from "stdio" */
#ifndef ____localdep__flushall_defined
#define ____localdep__flushall_defined 1
#if defined(__CRT_HAVE__flushall)
__CREDIRECT(,int,,__localdep__flushall,(void),_flushall,()) __THROWS(...)
#else /* LIBC: _flushall */
#include <local/stdio/_flushall.h>
#define __localdep__flushall (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_flushall))
#endif /* _flushall... */
#endif /* !____localdep__flushall_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(flushall_unlocked) int
(__LIBCCALL __LIBC_LOCAL_NAME(flushall_unlocked))(void) __THROWS(...) {
#line 1745 "kos/src/libc/magic/stdio.c"
#if defined(__CRT_HAVE_fflush_unlocked) || defined(__CRT_HAVE__fflush_nolock)
	return __localdep_fflush_unlocked(__NULLPTR);
#else
	return __localdep__flushall();
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_flushall_unlocked_defined */
