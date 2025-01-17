/* HASH CRC-32:0x2b29239c */
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
#ifndef __local_rawmemrxlenw_defined
#define __local_rawmemrxlenw_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rawmemrxchrw_defined
#define __local___localdep_rawmemrxchrw_defined
#ifdef __CRT_HAVE_rawmemrxchrw
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemrxchrw,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxchrw */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemrxchrw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rawmemrxchrw __LIBC_LOCAL_NAME(rawmemrxchrw)
#endif /* !__CRT_HAVE_rawmemrxchrw */
#endif /* !__local___localdep_rawmemrxchrw_defined */
__LOCAL_LIBC(rawmemrxlenw) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemrxlenw))(void const *__restrict __haystack, __UINT16_TYPE__ __needle) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_rawmemrxchrw)(__haystack, __needle) - (__UINT16_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rawmemrxlenw_defined
#define __local___localdep_rawmemrxlenw_defined
#define __localdep_rawmemrxlenw __LIBC_LOCAL_NAME(rawmemrxlenw)
#endif /* !__local___localdep_rawmemrxlenw_defined */
#endif /* !__local_rawmemrxlenw_defined */
