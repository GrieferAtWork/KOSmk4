/* HASH CRC-32:0x715306cc */
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
#ifndef __local_fdreopen_unlocked_defined
#define __local_fdreopen_unlocked_defined 1
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_fdreopen) || defined(__CRT_HAVE_fdreopen64) || defined(__CRT_HAVE_fdreopen_unlocked) || defined(__CRT_HAVE_fdreopen64_unlocked)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fdreopen_defined
#define __local___localdep_fdreopen_defined 1
#if defined(__CRT_HAVE_fdreopen64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,__localdep_fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64_unlocked,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,__localdep_fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen_unlocked,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,__localdep_fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,__localdep_fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen64)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,__localdep_fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen_unlocked)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,__localdep_fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen_unlocked,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen64_unlocked)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,__localdep_fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64_unlocked,(__fd,__modes,__stream))
#else /* ... */
#undef __local___localdep_fdreopen_defined
#endif /* !... */
#endif /* !__local___localdep_fdreopen_defined */
__LOCAL_LIBC(fdreopen_unlocked) __ATTR_NONNULL((2, 3)) __FILE *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fdreopen_unlocked))(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream) {
	return __localdep_fdreopen(__fd, __modes, __stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fdreopen_unlocked_defined
#define __local___localdep_fdreopen_unlocked_defined 1
#define __localdep_fdreopen_unlocked __LIBC_LOCAL_NAME(fdreopen_unlocked)
#endif /* !__local___localdep_fdreopen_unlocked_defined */
#else /* __CRT_HAVE_fdreopen || __CRT_HAVE_fdreopen64 || __CRT_HAVE_fdreopen_unlocked || __CRT_HAVE_fdreopen64_unlocked */
#undef __local_fdreopen_unlocked_defined
#endif /* !__CRT_HAVE_fdreopen && !__CRT_HAVE_fdreopen64 && !__CRT_HAVE_fdreopen_unlocked && !__CRT_HAVE_fdreopen64_unlocked */
#endif /* !__local_fdreopen_unlocked_defined */
