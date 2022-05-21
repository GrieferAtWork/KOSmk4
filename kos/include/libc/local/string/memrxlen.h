/* HASH CRC-32:0x2bb63cee */
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
#ifndef __local_memrxlen_defined
#define __local_memrxlen_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memrxend_defined
#define __local___localdep_memrxend_defined
#ifdef __CRT_HAVE_memrxend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrxend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrxend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrxend __LIBC_LOCAL_NAME(memrxend)
#endif /* !__CRT_HAVE_memrxend */
#endif /* !__local___localdep_memrxend_defined */
__LOCAL_LIBC(memrxlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrxlen))(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) {
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memrxend)(__haystack, __needle, __n_bytes) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrxlen_defined
#define __local___localdep_memrxlen_defined
#define __localdep_memrxlen __LIBC_LOCAL_NAME(memrxlen)
#endif /* !__local___localdep_memrxlen_defined */
#endif /* !__local_memrxlen_defined */
