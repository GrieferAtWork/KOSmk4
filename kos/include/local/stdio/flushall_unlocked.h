/* HASH CRC-32:0x61525f3f */
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
#ifndef __local_flushall_unlocked_defined
#define __local_flushall_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "fflush_unlocked" from "stdio" */
#ifndef ____localdep_fflush_unlocked_defined
#define ____localdep_fflush_unlocked_defined 1
#ifdef __CRT_HAVE_fflush_unlocked
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),fflush_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fflush_nolock)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),_fflush_nolock,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),fflush,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,,__localdep_fflush_unlocked,(__FILE *__stream),_IO_fflush,(__stream)) __THROWS(...)
#else /* LIBC: fflush_unlocked */
#include <local/stdio/fflush_unlocked.h>
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fflush_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush_unlocked))
#endif /* fflush_unlocked... */
#endif /* !____localdep_fflush_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(flushall_unlocked) int
(__LIBCCALL __LIBC_LOCAL_NAME(flushall_unlocked))(void) __THROWS(...) {
#line 1828 "kos/src/libc/magic/stdio.c"
	return __localdep_fflush_unlocked(__NULLPTR);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_flushall_unlocked_defined */
