/* HASH CRC-32:0x7e1392ab */
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
#ifndef __local_c32cspn_defined
#define __local_c32cspn_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32chr_defined
#define __local___localdep_c32chr_defined
#if defined(__CRT_HAVE_wcschr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32chr,(__CHAR32_TYPE__ const *__restrict __haystack, __CHAR32_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif defined(__CRT_HAVE_KOS$wcschr)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32chr,(__CHAR32_TYPE__ const *__restrict __haystack, __CHAR32_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcschr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32chr __NAMESPACE_LOCAL_TYPEHAX(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__),__CHAR32_TYPE__ *(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__),wcschr)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32chr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32chr __LIBC_LOCAL_NAME(c32chr)
#endif /* !... */
#endif /* !__local___localdep_c32chr_defined */
__LOCAL_LIBC(c32cspn) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32cspn))(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject) {
	__CHAR32_TYPE__ const *__iter = __haystack;
	while (*__iter && !(__NAMESPACE_LOCAL_SYM __localdep_c32chr)(__reject, *__iter))
		++__iter;
	return (__SIZE_TYPE__)(__iter - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32cspn_defined
#define __local___localdep_c32cspn_defined
#define __localdep_c32cspn __LIBC_LOCAL_NAME(c32cspn)
#endif /* !__local___localdep_c32cspn_defined */
#endif /* !__local_c32cspn_defined */
