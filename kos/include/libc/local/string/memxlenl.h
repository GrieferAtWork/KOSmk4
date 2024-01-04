/* HASH CRC-32:0xad981e73 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memxlenl_defined
#define __local_memxlenl_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memxendl_defined
#define __local___localdep_memxendl_defined
#ifdef __CRT_HAVE_memxendl
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memxendl,(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memxendl */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memxendl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memxendl __LIBC_LOCAL_NAME(memxendl)
#endif /* !__CRT_HAVE_memxendl */
#endif /* !__local___localdep_memxendl_defined */
__LOCAL_LIBC(memxlenl) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memxlenl))(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_memxendl)(__haystack, __needle, __n_dwords) - (__UINT32_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memxlenl_defined
#define __local___localdep_memxlenl_defined
#define __localdep_memxlenl __LIBC_LOCAL_NAME(memxlenl)
#endif /* !__local___localdep_memxlenl_defined */
#endif /* !__local_memxlenl_defined */
