/* HASH CRC-32:0xf24eed24 */
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
#ifndef __local_c32spncpy_defined
#define __local_c32spncpy_defined 1
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
/* Dependency: c32mempset from parts.uchar.string */
#ifndef __local___localdep_c32mempset_defined
#define __local___localdep_c32mempset_defined 1
#if defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wmemset, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__LIBKCALL,__localdep_c32mempset,(__CHAR32_TYPE__ *__dst, __CHAR32_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32mempset,(__CHAR32_TYPE__ *__dst, __CHAR32_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wmemset, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__LIBKCALL,__localdep_c32mempset,(__CHAR32_TYPE__ *__dst, __CHAR32_TYPE__ __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempsetl)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32mempset,(__CHAR32_TYPE__ *__dst, __CHAR32_TYPE__ __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wmempset.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as wmemset, but return a pointer after the last written character */
#define __localdep_c32mempset (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ *, __CHAR32_TYPE__, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wmempset))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32mempset.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as wmemset, but return a pointer after the last written character */
#define __localdep_c32mempset __LIBC_LOCAL_NAME(c32mempset)
#endif /* !... */
#endif /* !__local___localdep_c32mempset_defined */
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
/* Same as wcsncpy, but return a pointer after the last written character */
__LOCAL_LIBC(c32spncpy) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32spncpy))(__CHAR32_TYPE__ *__restrict __buf, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __buflen) {
	__SIZE_TYPE__ __srclen = __localdep_c32snlen(__src, __buflen);
	__localdep_c32memcpy(__buf, __src, __srclen);
	return __localdep_c32mempset(__buf+__srclen, '\0', __buflen - __srclen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32spncpy_defined
#define __local___localdep_c32spncpy_defined 1
#define __localdep_c32spncpy __LIBC_LOCAL_NAME(c32spncpy)
#endif /* !__local___localdep_c32spncpy_defined */
#endif /* !__local_c32spncpy_defined */
