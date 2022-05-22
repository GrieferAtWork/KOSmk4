/* HASH CRC-32:0xfca28bab */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memrlen_defined
#define __local_memrlen_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memrend_defined
#define __local___localdep_memrend_defined
#ifdef __CRT_HAVE_memrend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrend __LIBC_LOCAL_NAME(memrend)
#endif /* !__CRT_HAVE_memrend */
#endif /* !__local___localdep_memrend_defined */
__LOCAL_LIBC(memrlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrlen))(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) {
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memrend)(__haystack, __needle, __n_bytes) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrlen_defined
#define __local___localdep_memrlen_defined
#define __localdep_memrlen __LIBC_LOCAL_NAME(memrlen)
#endif /* !__local___localdep_memrlen_defined */
#endif /* !__local_memrlen_defined */
