/* HASH CRC-32:0xd7815f52 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fdopen_unlocked_defined
#define __local_fdopen_unlocked_defined
#include <__crt.h>
#if defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fdopen_defined
#define __local___localdep_fdopen_defined
#ifdef __CRT_HAVE_fdopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__fdopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),_fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__IO_fdopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),_IO_fdopen,(__fd,__modes))
#else /* ... */
#undef __local___localdep_fdopen_defined
#endif /* !... */
#endif /* !__local___localdep_fdopen_defined */
#ifndef __local___localdep_unlock_stream_defined
#define __local___localdep_unlock_stream_defined
#ifdef __CRT_HAVE_unlock_stream
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_unlock_stream,(__FILE *__fp),unlock_stream,(__fp))
#else /* __CRT_HAVE_unlock_stream */
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/unlock_stream.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unlock_stream __LIBC_LOCAL_NAME(unlock_stream)
#endif /* !__CRT_HAVE_unlock_stream */
#endif /* !__local___localdep_unlock_stream_defined */
__LOCAL_LIBC(fdopen_unlocked) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fdopen_unlocked))(__fd_t __fd, char const *__mode) {
	__FILE *__result = (__NAMESPACE_LOCAL_SYM __localdep_fdopen)(__fd, __mode);
	if (__result)
		(__NAMESPACE_LOCAL_SYM __localdep_unlock_stream)(__result);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fdopen_unlocked_defined
#define __local___localdep_fdopen_unlocked_defined
#define __localdep_fdopen_unlocked __LIBC_LOCAL_NAME(fdopen_unlocked)
#endif /* !__local___localdep_fdopen_unlocked_defined */
#else /* __CRT_HAVE_fdopen || __CRT_HAVE__fdopen || __CRT_HAVE__IO_fdopen */
#undef __local_fdopen_unlocked_defined
#endif /* !__CRT_HAVE_fdopen && !__CRT_HAVE__fdopen && !__CRT_HAVE__IO_fdopen */
#endif /* !__local_fdopen_unlocked_defined */
