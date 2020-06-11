/* HASH CRC-32:0xe7dbc971 */
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
#ifndef __local_memlen_defined
#define __local_memlen_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memend from string */
#ifndef __local___localdep_memend_defined
#define __local___localdep_memend_defined 1
#ifdef __fast_memend_defined
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING(memend)
#define __localdep_memend __LIBC_FAST_NAME(memend)
#elif defined(__CRT_HAVE_memend)
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memend __LIBC_LOCAL_NAME(memend)
#endif /* !... */
#endif /* !__local___localdep_memend_defined */
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
__LOCAL_LIBC(memlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memlen))(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) {
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_memend(__haystack, __needle, __n_bytes) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memlen_defined
#define __local___localdep_memlen_defined 1
#define __localdep_memlen __LIBC_LOCAL_NAME(memlen)
#endif /* !__local___localdep_memlen_defined */
#endif /* !__local_memlen_defined */
