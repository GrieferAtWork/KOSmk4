/* HASH CRC-32:0xe7681a36 */
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
#ifndef __local_rawmemrlen_defined
#define __local_rawmemrlen_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rawmemrchr_defined
#define __local___localdep_rawmemrchr_defined 1
#ifdef __CRT_HAVE_rawmemrchr
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_rawmemrchr,(void const *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrchr */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemrchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rawmemrchr __LIBC_LOCAL_NAME(rawmemrchr)
#endif /* !__CRT_HAVE_rawmemrchr */
#endif /* !__local___localdep_rawmemrchr_defined */
__LOCAL_LIBC(rawmemrlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemrlen))(void const *__restrict __haystack, int __needle) {
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_rawmemrchr(__haystack, __needle) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rawmemrlen_defined
#define __local___localdep_rawmemrlen_defined 1
#define __localdep_rawmemrlen __LIBC_LOCAL_NAME(rawmemrlen)
#endif /* !__local___localdep_rawmemrlen_defined */
#endif /* !__local_rawmemrlen_defined */
