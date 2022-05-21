/* HASH CRC-32:0xc7dd608c */
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
#ifndef __local_memrlenw_defined
#define __local_memrlenw_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memrendw_defined
#define __local___localdep_memrendw_defined
#ifdef __CRT_HAVE_memrendw
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__needle,__n_words))
#else /* __CRT_HAVE_memrendw */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrendw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrendw __LIBC_LOCAL_NAME(memrendw)
#endif /* !__CRT_HAVE_memrendw */
#endif /* !__local___localdep_memrendw_defined */
__LOCAL_LIBC(memrlenw) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrlenw))(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_memrendw)(__haystack, __needle, __n_words) - (__UINT16_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrlenw_defined
#define __local___localdep_memrlenw_defined
#define __localdep_memrlenw __LIBC_LOCAL_NAME(memrlenw)
#endif /* !__local___localdep_memrlenw_defined */
#endif /* !__local_memrlenw_defined */
