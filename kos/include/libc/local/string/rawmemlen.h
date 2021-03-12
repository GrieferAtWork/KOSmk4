/* HASH CRC-32:0x95f926c2 */
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
#ifndef __local_rawmemlen_defined
#define __local_rawmemlen_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: rawmemchr from string */
#ifndef __local___localdep_rawmemchr_defined
#define __local___localdep_rawmemchr_defined 1
#ifdef __CRT_HAVE_rawmemchr
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_rawmemchr,(void const *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
#elif defined(__CRT_HAVE___rawmemchr)
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_rawmemchr,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemchr.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memchr' with a search limit of `(size_t)-1' */
#define __localdep_rawmemchr __LIBC_LOCAL_NAME(rawmemchr)
#endif /* !... */
#endif /* !__local___localdep_rawmemchr_defined */
/* Same as `rawmemchr', but return the offset from `haystack', rather than the actual address. */
__LOCAL_LIBC(rawmemlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemlen))(void const *__restrict __haystack, int __needle) {
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_rawmemchr(__haystack, __needle) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rawmemlen_defined
#define __local___localdep_rawmemlen_defined 1
#define __localdep_rawmemlen __LIBC_LOCAL_NAME(rawmemlen)
#endif /* !__local___localdep_rawmemlen_defined */
#endif /* !__local_rawmemlen_defined */
