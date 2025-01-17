/* HASH CRC-32:0x2c65a5ea */
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
#ifndef __local_rawmemrlenq_defined
#define __local_rawmemrlenq_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rawmemrchrq_defined
#define __local___localdep_rawmemrchrq_defined
#ifdef __CRT_HAVE_rawmemrchrq
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemrchrq,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrchrq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemrchrq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rawmemrchrq __LIBC_LOCAL_NAME(rawmemrchrq)
#endif /* !__CRT_HAVE_rawmemrchrq */
#endif /* !__local___localdep_rawmemrchrq_defined */
__LOCAL_LIBC(rawmemrlenq) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemrlenq))(void const *__restrict __haystack, __UINT64_TYPE__ __needle) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_rawmemrchrq)(__haystack, __needle) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rawmemrlenq_defined
#define __local___localdep_rawmemrlenq_defined
#define __localdep_rawmemrlenq __LIBC_LOCAL_NAME(rawmemrlenq)
#endif /* !__local___localdep_rawmemrlenq_defined */
#endif /* !__local_rawmemrlenq_defined */
