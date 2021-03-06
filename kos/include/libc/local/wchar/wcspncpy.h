/* HASH CRC-32:0xe0f1f1f2 */
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
#ifndef __local_wcspncpy_defined
#define __local_wcspncpy_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcsnlen from wchar */
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#else /* __CRT_HAVE_wcsnlen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
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
#include <libc/local/string/memcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *__restrict, __WCHAR_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(memcpyw))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *__restrict, __WCHAR_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(memcpyl))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wmemcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy __LIBC_LOCAL_NAME(wmemcpy)
#endif /* !... */
#endif /* !__local___localdep_wmemcpy_defined */
/* Dependency: wmempset from wchar */
#ifndef __local___localdep_wmempset_defined
#define __local___localdep_wmempset_defined 1
#ifdef __CRT_HAVE_wmempset
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmempset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw) && __SIZEOF_WCHAR_T__ == 2
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmempset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl) && __SIZEOF_WCHAR_T__ == 4
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmempset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempsetw.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as wmemset, but return a pointer after the last written character */
#define __localdep_wmempset (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *, __WCHAR_TYPE__, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(mempsetw))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempsetl.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as wmemset, but return a pointer after the last written character */
#define __localdep_wmempset (*(__WCHAR_TYPE__ *(__LIBCCALL *)(__WCHAR_TYPE__ *, __WCHAR_TYPE__, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(mempsetl))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wmempset.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as wmemset, but return a pointer after the last written character */
#define __localdep_wmempset __LIBC_LOCAL_NAME(wmempset)
#endif /* !... */
#endif /* !__local___localdep_wmempset_defined */
/* Same as wcsncpy, but return a pointer after the last written character */
__LOCAL_LIBC(wcspncpy) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcspncpy))(__WCHAR_TYPE__ *__restrict __buf, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __buflen) {
	__SIZE_TYPE__ __srclen = __localdep_wcsnlen(__src, __buflen);
	__localdep_wmemcpy(__buf, __src, __srclen);
	return __localdep_wmempset(__buf + __srclen, '\0', __buflen - __srclen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcspncpy_defined
#define __local___localdep_wcspncpy_defined 1
#define __localdep_wcspncpy __LIBC_LOCAL_NAME(wcspncpy)
#endif /* !__local___localdep_wcspncpy_defined */
#endif /* !__local_wcspncpy_defined */
