/* HASH CRC-32:0xe995b30e */
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
#ifndef __local_c32stok_defined
#define __local_c32stok_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32scspn from parts.uchar.string */
#ifndef __local___localdep_c32scspn_defined
#define __local___localdep_c32scspn_defined 1
#if defined(__CRT_HAVE_wcscspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32scspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_KOS$wcscspn)
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32scspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
#define __localdep_c32scspn (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *))&__LIBC_LOCAL_NAME(wcscspn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32scspn.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
#define __localdep_c32scspn __LIBC_LOCAL_NAME(c32scspn)
#endif /* !... */
#endif /* !__local___localdep_c32scspn_defined */
/* Dependency: c32sspn from parts.uchar.string */
#ifndef __local___localdep_c32sspn_defined
#define __local___localdep_c32sspn_defined 1
#if defined(__CRT_HAVE_wcsspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32sspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_KOS$wcsspn)
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32sspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
#define __localdep_c32sspn (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *))&__LIBC_LOCAL_NAME(wcsspn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32sspn.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
#define __localdep_c32sspn __LIBC_LOCAL_NAME(c32sspn)
#endif /* !... */
#endif /* !__local___localdep_c32sspn_defined */
__LOCAL_LIBC(c32stok) __ATTR_NONNULL((2, 3)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stok))(__CHAR32_TYPE__ *__str, __CHAR32_TYPE__ const *__restrict __delim, __CHAR32_TYPE__ **__restrict __save_ptr) {
	__CHAR32_TYPE__ *__end;
	if (!__str)
		__str = *__save_ptr;
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__str += __localdep_c32sspn(__str, __delim);
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__end = __str + __localdep_c32scspn(__str, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __str;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stok_defined
#define __local___localdep_c32stok_defined 1
#define __localdep_c32stok __LIBC_LOCAL_NAME(c32stok)
#endif /* !__local___localdep_c32stok_defined */
#endif /* !__local_c32stok_defined */
