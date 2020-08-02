/* HASH CRC-32:0x644fe861 */
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
#ifndef __local_wcspcpy_defined
#define __local_wcspcpy_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcslen from wchar */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined 1
#ifdef __CRT_HAVE_wcslen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#else /* __CRT_HAVE_wcslen */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__CRT_HAVE_wcslen */
#endif /* !__local___localdep_wcslen_defined */
/* Dependency: wmempcpy from wchar */
#ifndef __local___localdep_wmempcpy_defined
#define __local___localdep_wmempcpy_defined 1
#ifdef __CRT_HAVE_wmempcpy
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmempcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmempcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmempcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/string/mempcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmempcpy (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *__restrict, __WCHAR_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(mempcpyw))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/string/mempcpyl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmempcpy (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *__restrict, __WCHAR_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(mempcpyl))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/wmempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmempcpy __LIBC_LOCAL_NAME(wmempcpy)
#endif /* !... */
#endif /* !__local___localdep_wmempcpy_defined */
/* Same as wcscpy, but return a pointer after the last written character */
__LOCAL_LIBC(wcspcpy) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcspcpy))(__WCHAR_TYPE__ *__restrict __buf, __WCHAR_TYPE__ const *__restrict __src) {
	return __localdep_wmempcpy(__buf, __src, __localdep_wcslen(__src) + 1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcspcpy_defined
#define __local___localdep_wcspcpy_defined 1
#define __localdep_wcspcpy __LIBC_LOCAL_NAME(wcspcpy)
#endif /* !__local___localdep_wcspcpy_defined */
#endif /* !__local_wcspcpy_defined */
