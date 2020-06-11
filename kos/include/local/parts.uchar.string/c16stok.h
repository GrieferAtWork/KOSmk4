/* HASH CRC-32:0xcb0ae451 */
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
#ifndef __local_c16stok_defined
#define __local_c16stok_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16sspn from parts.uchar.string */
#ifndef __local___localdep_c16sspn_defined
#define __local___localdep_c16sspn_defined 1
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16sspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sspn (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *))&__LIBC_LOCAL_NAME(wcsspn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16sspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sspn __LIBC_LOCAL_NAME(c16sspn)
#endif /* !... */
#endif /* !__local___localdep_c16sspn_defined */
/* Dependency: c16scspn from parts.uchar.string */
#ifndef __local___localdep_c16scspn_defined
#define __local___localdep_c16scspn_defined 1
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16scspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16scspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16scspn (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *))&__LIBC_LOCAL_NAME(wcscspn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16scspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16scspn __LIBC_LOCAL_NAME(c16scspn)
#endif /* !... */
#endif /* !__local___localdep_c16scspn_defined */
__LOCAL_LIBC(c16stok) __ATTR_NONNULL((2, 3)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16stok))(__CHAR16_TYPE__ *__string, __CHAR16_TYPE__ const *__restrict __delim, __CHAR16_TYPE__ **__restrict __save_ptr) {
	__CHAR16_TYPE__ *__end;
	if (!__string)
		__string = *__save_ptr;
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__string += __localdep_c16sspn(__string, __delim);
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__end = __string + __localdep_c16scspn(__string, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __string;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __string;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16stok_defined
#define __local___localdep_c16stok_defined 1
#define __localdep_c16stok __LIBC_LOCAL_NAME(c16stok)
#endif /* !__local___localdep_c16stok_defined */
#endif /* !__local_c16stok_defined */
