/* HASH CRC-32:0x99804816 */
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
#ifndef __local_wcpncpy_defined
#define __local_wcpncpy_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcsnlen from wchar */
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* __CRT_HAVE_wcsnlen */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !__CRT_HAVE_wcsnlen */
#endif /* !__local___localdep_wcsnlen_defined */
/* Dependency: wmemcpy from wchar */
#ifndef __local___localdep_wmemcpy_defined
#define __local___localdep_wmemcpy_defined 1
#ifdef __CRT_HAVE_wmemcpy
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/string/memcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *__restrict, __WCHAR_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(memcpyw))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/string/memcpyl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *__restrict, __WCHAR_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(memcpyl))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/wmemcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy __LIBC_LOCAL_NAME(wmemcpy)
#endif /* !... */
#endif /* !__local___localdep_wmemcpy_defined */
/* Dependency: wmemset from wchar */
#ifndef __local___localdep_wmemset_defined
#define __local___localdep_wmemset_defined 1
#ifdef __CRT_HAVE_wmemset
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/string/memsetw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemset (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *, __WCHAR_TYPE__, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(memsetw))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/string/memsetl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemset (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *, __WCHAR_TYPE__, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(memsetl))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/wmemset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemset __LIBC_LOCAL_NAME(wmemset)
#endif /* !... */
#endif /* !__local___localdep_wmemset_defined */
__LOCAL_LIBC(wcpncpy) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcpncpy))(__WCHAR_TYPE__ *__restrict __buf, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __buflen) {
	__SIZE_TYPE__ __srclen = __localdep_wcsnlen(__src, __buflen);
	__localdep_wmemcpy(__buf, __src, __srclen);
	__localdep_wmemset(__buf + __srclen, '\0', (__SIZE_TYPE__)(__buflen - __srclen));
	return __buf + __srclen;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcpncpy_defined
#define __local___localdep_wcpncpy_defined 1
#define __localdep_wcpncpy __LIBC_LOCAL_NAME(wcpncpy)
#endif /* !__local___localdep_wcpncpy_defined */
#endif /* !__local_wcpncpy_defined */
