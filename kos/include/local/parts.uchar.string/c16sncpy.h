/* HASH CRC-32:0xcfc87d09 */
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
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16snlen from parts.uchar.string */
#ifndef __local___localdep_c16snlen_defined
#define __local___localdep_c16snlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
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
/* Dependency: memcpyw from string */
#ifndef __local___localdep_memcpyw_defined
#define __local___localdep_memcpyw_defined 1
#ifdef __CRT_HAVE_memcpyw
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 2
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcpy) && defined(__LIBCCALL_IS_LIBDCALL)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memcpyw.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw __LIBC_LOCAL_NAME(memcpyw)
#endif /* !... */
#endif /* !__local___localdep_memcpyw_defined */
/* Dependency: memsetw from string */
#ifndef __local___localdep_memsetw_defined
#define __local___localdep_memsetw_defined 1
#ifdef __CRT_HAVE_memsetw
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 2
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemset) && defined(__LIBCCALL_IS_LIBDCALL)
/* Fill memory with a given word */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemset,(__dst,__word,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memsetw.h>
__NAMESPACE_LOCAL_BEGIN
/* Fill memory with a given word */
#define __localdep_memsetw __LIBC_LOCAL_NAME(memsetw)
#endif /* !... */
#endif /* !__local___localdep_memsetw_defined */
__LOCAL_LIBC(c16sncpy) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16sncpy))(__CHAR16_TYPE__ *__restrict __buf, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __buflen) {
	__SIZE_TYPE__ __srclen = __localdep_c16snlen(__src, __buflen);
	(__CHAR16_TYPE__ *)__localdep_memcpyw(__buf, __src, __srclen);
	(__CHAR16_TYPE__ *)__localdep_memsetw(__buf+__srclen, '\0', __buflen - __srclen);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16sncpy_defined
#define __local___localdep_c16sncpy_defined 1
#define __localdep_c16sncpy __LIBC_LOCAL_NAME(c16sncpy)
#endif /* !__local___localdep_c16sncpy_defined */
#endif /* !__local_c16sncpy_defined */
