/* HASH CRC-32:0x22a4336c */
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
#ifndef __local_c16nrev_defined
#define __local_c16nrev_defined 1
#include <__crt.h>
/* Dependency: "memrevw" from "string" */
#ifndef ____localdep_memrevw_defined
#define ____localdep_memrevw_defined 1
#ifdef __CRT_HAVE_memrevw
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memrevw,(void *__restrict __base, __SIZE_TYPE__ __n_words),memrevw,(__base,__n_words))
#else /* LIBC: memrevw */
#include <local/string/memrevw.h>
#define __localdep_memrevw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevw))
#endif /* memrevw... */
#endif /* !____localdep_memrevw_defined */

/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_c16nlen_defined
#define ____localdep_c16nlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16nlen (*(__SIZE_TYPE__(__LIBCCALL*)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen)))
#else /* LIBC: c16nlen */
#include <local/wchar/c16nlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16nlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen))
#endif /* c16nlen... */
#endif /* !____localdep_c16nlen_defined */

/* Dependency: "memrevl" from "string" */
#ifndef ____localdep_memrevl_defined
#define ____localdep_memrevl_defined 1
#ifdef __CRT_HAVE_memrevl
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrevl,(void *__restrict __base, __SIZE_TYPE__ __n_dwords),memrevl,(__base,__n_dwords))
#else /* LIBC: memrevl */
#include <local/string/memrevl.h>
#define __localdep_memrevl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevl))
#endif /* memrevl... */
#endif /* !____localdep_memrevl_defined */

/* Dependency: "memrev" from "string" */
#ifndef ____localdep_memrev_defined
#define ____localdep_memrev_defined 1
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* LIBC: memrev */
#include <local/string/memrev.h>
#define __localdep_memrev (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))
#endif /* memrev... */
#endif /* !____localdep_memrev_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16nrev) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16nrev))(__CHAR16_TYPE__ *__restrict __str,
                                                     __SIZE_TYPE__ __maxlen) {
#line 1349 "kos/src/libc/magic/wchar.c"
#if __SIZEOF_WCHAR_T__ == 2
	return (__CHAR16_TYPE__ *)__localdep_memrevw(__str, __localdep_c16nlen(__str, __maxlen));
#elif __SIZEOF_WCHAR_T__ == 4
	return (__CHAR16_TYPE__ *)__localdep_memrevl(__str, __localdep_c16nlen(__str, __maxlen));
#else
	return (__CHAR16_TYPE__ *)__localdep_memrev(__str, __localdep_c16nlen(__str, __maxlen) * sizeof(__CHAR16_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16nrev_defined */
