/* HASH CRC-32:0x8af686b2 */
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
#ifndef __local_flushall_unlocked_defined
#define __local_flushall_unlocked_defined 1
#include <__crt.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fflush_unlocked from stdio */
#ifndef __local___localdep_fflush_unlocked_defined
#define __local___localdep_fflush_unlocked_defined 1
#ifdef __CRT_HAVE_fflush_unlocked
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,__localdep_fflush_unlocked,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,__localdep_fflush_unlocked,(__FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,__localdep_fflush_unlocked,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,__localdep_fflush_unlocked,(__FILE *__stream),_IO_fflush,(__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fflush_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
#define __localdep_fflush_unlocked __LIBC_LOCAL_NAME(fflush_unlocked)
#endif /* !... */
#endif /* !__local___localdep_fflush_unlocked_defined */
__LOCAL_LIBC(flushall_unlocked) int
(__LIBCCALL __LIBC_LOCAL_NAME(flushall_unlocked))(void) __THROWS(...) {
	return __localdep_fflush_unlocked(__NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_flushall_unlocked_defined
#define __local___localdep_flushall_unlocked_defined 1
#define __localdep_flushall_unlocked __LIBC_LOCAL_NAME(flushall_unlocked)
#endif /* !__local___localdep_flushall_unlocked_defined */
#endif /* !__local_flushall_unlocked_defined */
