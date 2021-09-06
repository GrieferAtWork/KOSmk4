/* HASH CRC-32:0x8684e379 */
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
#ifndef __local_c32scspn_defined
#define __local_c32scspn_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32schr_defined
#define __local___localdep_c32schr_defined 1
#if defined(__CRT_HAVE_wcschr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32schr,(__CHAR32_TYPE__ const *__restrict __haystack, __CHAR32_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif defined(__CRT_HAVE_KOS$wcschr)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32schr,(__CHAR32_TYPE__ const *__restrict __haystack, __CHAR32_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcschr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32schr (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __CHAR32_TYPE__))&__LIBC_LOCAL_NAME(wcschr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32schr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32schr __LIBC_LOCAL_NAME(c32schr)
#endif /* !... */
#endif /* !__local___localdep_c32schr_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32scspn) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32scspn))(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject) {
	__CHAR32_TYPE__ const *__iter = __haystack;
	while (*__iter && !__localdep_c32schr(__reject, *__iter))
		++__iter;
	return (__SIZE_TYPE__)(__iter - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32scspn_defined
#define __local___localdep_c32scspn_defined 1
#define __localdep_c32scspn __LIBC_LOCAL_NAME(c32scspn)
#endif /* !__local___localdep_c32scspn_defined */
#endif /* !__local_c32scspn_defined */
