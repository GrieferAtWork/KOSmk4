/* HASH CRC-32:0x471b1b9d */
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
#ifndef __local_c32srev_defined
#define __local_c32srev_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32slen from parts.uchar.string */
#ifndef __local___localdep_c32slen_defined
#define __local___localdep_c32slen_defined 1
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_KOS$wcslen)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcslen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32slen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen __LIBC_LOCAL_NAME(c32slen)
#endif /* !... */
#endif /* !__local___localdep_c32slen_defined */
/* Dependency: memrev from string */
#ifndef __local___localdep_memrev_defined
#define __local___localdep_memrev_defined 1
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrev.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrev __LIBC_LOCAL_NAME(memrev)
#endif /* !__CRT_HAVE_memrev */
#endif /* !__local___localdep_memrev_defined */
/* Dependency: memrevl from string */
#ifndef __local___localdep_memrevl_defined
#define __local___localdep_memrevl_defined 1
#ifdef __CRT_HAVE_memrevl
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrevl,(void *__restrict __base, __SIZE_TYPE__ __n_dwords),memrevl,(__base,__n_dwords))
#else /* __CRT_HAVE_memrevl */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrevl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrevl __LIBC_LOCAL_NAME(memrevl)
#endif /* !__CRT_HAVE_memrevl */
#endif /* !__local___localdep_memrevl_defined */
/* Dependency: memrevw from string */
#ifndef __local___localdep_memrevw_defined
#define __local___localdep_memrevw_defined 1
#ifdef __CRT_HAVE_memrevw
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memrevw,(void *__restrict __base, __SIZE_TYPE__ __n_words),memrevw,(__base,__n_words))
#else /* __CRT_HAVE_memrevw */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrevw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrevw __LIBC_LOCAL_NAME(memrevw)
#endif /* !__CRT_HAVE_memrevw */
#endif /* !__local___localdep_memrevw_defined */
__LOCAL_LIBC(c32srev) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32srev))(__CHAR32_TYPE__ *__restrict __str) {



	return (__CHAR32_TYPE__ *)__localdep_memrevl(__str, __localdep_c32slen(__str));



}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32srev_defined
#define __local___localdep_c32srev_defined 1
#define __localdep_c32srev __LIBC_LOCAL_NAME(c32srev)
#endif /* !__local___localdep_c32srev_defined */
#endif /* !__local_c32srev_defined */
