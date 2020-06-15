/* HASH CRC-32:0x8777b509 */
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
#ifndef __local_clearerr_s_defined
#define __local_clearerr_s_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_clearerr) || defined(__CRT_HAVE_clearerr_unlocked)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: clearerr from stdio */
#ifndef __local___localdep_clearerr_defined
#define __local___localdep_clearerr_defined 1
#if defined(__CRT_HAVE_clearerr_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_clearerr,(__FILE *__restrict __stream),clearerr_unlocked,(__stream))
#elif defined(__CRT_HAVE_clearerr)
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_clearerr,(__FILE *__restrict __stream),clearerr,(__stream))
#elif defined(__CRT_HAVE_clearerr_unlocked)
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_clearerr,(__FILE *__restrict __stream),clearerr_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_clearerr_defined
#endif /* !... */
#endif /* !__local___localdep_clearerr_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(clearerr_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(clearerr_s))(__FILE *__restrict __stream) {
	if (!__stream) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	__localdep_clearerr(__stream);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_clearerr_s_defined
#define __local___localdep_clearerr_s_defined 1
#define __localdep_clearerr_s __LIBC_LOCAL_NAME(clearerr_s)
#endif /* !__local___localdep_clearerr_s_defined */
#else /* __CRT_HAVE_clearerr || __CRT_HAVE_clearerr_unlocked */
#undef __local_clearerr_s_defined
#endif /* !__CRT_HAVE_clearerr && !__CRT_HAVE_clearerr_unlocked */
#endif /* !__local_clearerr_s_defined */
