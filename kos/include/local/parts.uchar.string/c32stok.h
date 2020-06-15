/* HASH CRC-32:0x35db5d12 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32stok_defined
#define __local_c32stok_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32scspn from parts.uchar.string */
#ifndef __local___localdep_c32scspn_defined
#define __local___localdep_c32scspn_defined 1
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32scspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_KOS$wcscspn)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32scspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32scspn (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *))&__LIBC_LOCAL_NAME(wcscspn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32scspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32scspn __LIBC_LOCAL_NAME(c32scspn)
#endif /* !... */
#endif /* !__local___localdep_c32scspn_defined */
/* Dependency: c32sspn from parts.uchar.string */
#ifndef __local___localdep_c32sspn_defined
#define __local___localdep_c32sspn_defined 1
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32sspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_KOS$wcsspn)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32sspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32sspn (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *))&__LIBC_LOCAL_NAME(wcsspn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32sspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32sspn __LIBC_LOCAL_NAME(c32sspn)
#endif /* !... */
#endif /* !__local___localdep_c32sspn_defined */
__LOCAL_LIBC(c32stok) __ATTR_NONNULL((2, 3)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stok))(__CHAR32_TYPE__ *__string, __CHAR32_TYPE__ const *__restrict __delim, __CHAR32_TYPE__ **__restrict __save_ptr) {
	__CHAR32_TYPE__ *__end;
	if (!__string)
		__string = *__save_ptr;
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__string += __localdep_c32sspn(__string, __delim);
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__end = __string + __localdep_c32scspn(__string, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __string;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __string;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stok_defined
#define __local___localdep_c32stok_defined 1
#define __localdep_c32stok __LIBC_LOCAL_NAME(c32stok)
#endif /* !__local___localdep_c32stok_defined */
#endif /* !__local_c32stok_defined */
