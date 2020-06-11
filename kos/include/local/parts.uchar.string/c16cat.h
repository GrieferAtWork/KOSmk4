/* HASH CRC-32:0xbfcf5e69 */
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
#ifndef __local_c16cat_defined
#define __local_c16cat_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16end from parts.uchar.string */
#ifndef __local___localdep_c16end_defined
#define __local___localdep_c16end_defined 1
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,__localdep_c16end,(__CHAR16_TYPE__ const *__restrict __string),wcsend,(__string))
#elif defined(__CRT_HAVE_DOS$wcsend)
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16end,(__CHAR16_TYPE__ const *__restrict __string),wcsend,(__string))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcslen(STR)' */
#define __localdep_c16end (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcsend))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16end.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcslen(STR)' */
#define __localdep_c16end (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(c16end))
#endif /* !... */
#endif /* !__local___localdep_c16end_defined */
/* Dependency: c16len from parts.uchar.string */
#ifndef __local___localdep_c16len_defined
#define __local___localdep_c16len_defined 1
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16len (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcslen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16len.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16len __LIBC_LOCAL_NAME(c16len)
#endif /* !... */
#endif /* !__local___localdep_c16len_defined */
/* Dependency: c16memcpy from parts.uchar.string */
#ifndef __local___localdep_c16memcpy_defined
#define __local___localdep_c16memcpy_defined 1
#if defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,__localdep_c16memcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16memcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,__localdep_c16memcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memcpyw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16memcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wmemcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16memcpy (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ *__restrict, __CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wmemcpy))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16memcpy __LIBC_LOCAL_NAME(c16memcpy)
#endif /* !... */
#endif /* !__local___localdep_c16memcpy_defined */
__LOCAL_LIBC(c16cat) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16cat))(__CHAR16_TYPE__ *__restrict __buf, __CHAR16_TYPE__ const *__restrict __src) {
	__localdep_c16memcpy(__localdep_c16end(__buf), __src, __localdep_c16len(__src) + 1);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16cat_defined
#define __local___localdep_c16cat_defined 1
#define __localdep_c16cat __LIBC_LOCAL_NAME(c16cat)
#endif /* !__local___localdep_c16cat_defined */
#endif /* !__local_c16cat_defined */
