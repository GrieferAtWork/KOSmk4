/* HASH CRC-32:0x2b55d26a */
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
#ifndef __local_c32sncat_defined
#define __local_c32sncat_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32memcpy from parts.uchar.string */
#ifndef __local___localdep_c32memcpy_defined
#define __local___localdep_c32memcpy_defined 1
#if defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__LIBKCALL,__localdep_c32memcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32memcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__LIBKCALL,__localdep_c32memcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memcpyl)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32memcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wmemcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32memcpy (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ *__restrict, __CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wmemcpy))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32memcpy __LIBC_LOCAL_NAME(c32memcpy)
#endif /* !... */
#endif /* !__local___localdep_c32memcpy_defined */
/* Dependency: c32send from parts.uchar.string */
#ifndef __local___localdep_c32send_defined
#define __local___localdep_c32send_defined 1
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__LIBKCALL,__localdep_c32send,(__CHAR32_TYPE__ const *__restrict __string),wcsend,(__string))
#elif defined(__CRT_HAVE_DOS$wcsend)
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32send,(__CHAR32_TYPE__ const *__restrict __string),wcsend,(__string))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcslen(STR)' */
#define __localdep_c32send (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcsend))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32send.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcslen(STR)' */
#define __localdep_c32send (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(c32send))
#endif /* !... */
#endif /* !__local___localdep_c32send_defined */
/* Dependency: c32snlen from parts.uchar.string */
#ifndef __local___localdep_c32snlen_defined
#define __local___localdep_c32snlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,__localdep_c32snlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32snlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32snlen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32snlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32snlen __LIBC_LOCAL_NAME(c32snlen)
#endif /* !... */
#endif /* !__local___localdep_c32snlen_defined */
__LOCAL_LIBC(c32sncat) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32sncat))(__CHAR32_TYPE__ *__restrict __buf, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __buflen) {
	__SIZE_TYPE__ __srclen = __localdep_c32snlen(__src, __buflen);
	__CHAR32_TYPE__ *__dst = __localdep_c32send(__buf);
	__localdep_c32memcpy(__dst, __src, __srclen);
	__dst[__srclen] = '\0';
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32sncat_defined
#define __local___localdep_c32sncat_defined 1
#define __localdep_c32sncat __LIBC_LOCAL_NAME(c32sncat)
#endif /* !__local___localdep_c32sncat_defined */
#endif /* !__local_c32sncat_defined */
