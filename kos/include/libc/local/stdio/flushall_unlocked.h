/* HASH CRC-32:0x1d58f9e */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_flushall_unlocked_defined
#define __local_flushall_unlocked_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fflush_unlocked_defined
#define __local___localdep_fflush_unlocked_defined
#ifdef __CRT_HAVE_fflush_unlocked
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush_unlocked,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush_unlocked,(__FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush_unlocked,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush_unlocked,(__FILE *__stream),_IO_fflush,(__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fflush_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fflush_unlocked __LIBC_LOCAL_NAME(fflush_unlocked)
#endif /* !... */
#endif /* !__local___localdep_fflush_unlocked_defined */
__LOCAL_LIBC(flushall_unlocked) int
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(flushall_unlocked))(void) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fflush_unlocked)(__NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_flushall_unlocked_defined
#define __local___localdep_flushall_unlocked_defined
#define __localdep_flushall_unlocked __LIBC_LOCAL_NAME(flushall_unlocked)
#endif /* !__local___localdep_flushall_unlocked_defined */
#endif /* !__local_flushall_unlocked_defined */
