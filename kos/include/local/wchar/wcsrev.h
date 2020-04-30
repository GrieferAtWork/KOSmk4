/* HASH CRC-32:0xf9c3f9fa */
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
#ifndef __local_wcsrev_defined
#define __local_wcsrev_defined 1
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

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_wcslen_defined
#define ____localdep_wcslen_defined 1
#ifdef __std___localdep_wcslen_defined
__NAMESPACE_STD_USING(__localdep_wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#else /* LIBC: wcslen */
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_wcslen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#endif /* wcslen... */
#endif /* !____localdep_wcslen_defined */

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
__LOCAL_LIBC(wcsrev) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsrev))(__WCHAR_TYPE__ *__restrict __str) {
#line 1817 "kos/src/libc/magic/wchar.c"
#if __SIZEOF_WCHAR_T__ == 2
	return (__WCHAR_TYPE__ *)__localdep_memrevw(__str, __localdep_wcslen(__str));
#elif __SIZEOF_WCHAR_T__ == 4
	return (__WCHAR_TYPE__ *)__localdep_memrevl(__str, __localdep_wcslen(__str));
#else
	return (__WCHAR_TYPE__ *)__localdep_memrev(__str, __localdep_wcslen(__str) * sizeof(__WCHAR_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsrev_defined */
