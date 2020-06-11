/* HASH CRC-32:0xbd068bcc */
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
#ifndef __local_c16sncpy_defined
#define __local_c16sncpy_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16memset from parts.uchar.string */
#ifndef __local___localdep_c16memset_defined
#define __local___localdep_c16memset_defined 1
#if defined(__CRT_HAVE_wmemset) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,__localdep_c16memset,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16memset,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,__localdep_c16memset,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$memsetw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16memset,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wmemset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16memset (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ *, __CHAR16_TYPE__, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wmemset))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16memset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16memset __LIBC_LOCAL_NAME(c16memset)
#endif /* !... */
#endif /* !__local___localdep_c16memset_defined */
/* Dependency: c16snlen from parts.uchar.string */
#ifndef __local___localdep_c16snlen_defined
#define __local___localdep_c16snlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16snlen (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16snlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16snlen __LIBC_LOCAL_NAME(c16snlen)
#endif /* !... */
#endif /* !__local___localdep_c16snlen_defined */
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
__LOCAL_LIBC(c16sncpy) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16sncpy))(__CHAR16_TYPE__ *__restrict __buf, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __buflen) {
	__SIZE_TYPE__ __srclen = __localdep_c16snlen(__src, __buflen);
	__localdep_c16memcpy(__buf, __src, __srclen);
	__localdep_c16memset(__buf+__srclen, '\0', __buflen - __srclen);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16sncpy_defined
#define __local___localdep_c16sncpy_defined 1
#define __localdep_c16sncpy __LIBC_LOCAL_NAME(c16sncpy)
#endif /* !__local___localdep_c16sncpy_defined */
#endif /* !__local_c16sncpy_defined */
