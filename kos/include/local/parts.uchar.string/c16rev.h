/* HASH CRC-32:0x86d1b685 */
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
#ifndef __local_c16rev_defined
#define __local_c16rev_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memrevl from string */
#ifndef __local___localdep_memrevl_defined
#define __local___localdep_memrevl_defined 1
#ifdef __CRT_HAVE_memrevl
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrevl,(void *__restrict __base, __SIZE_TYPE__ __n_dwords),memrevl,(__base,__n_dwords))
#else /* __CRT_HAVE_memrevl */
__NAMESPACE_LOCAL_END
#include <local/string/memrevl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrevl __LIBC_LOCAL_NAME(memrevl)
#endif /* !__CRT_HAVE_memrevl */
#endif /* !__local___localdep_memrevl_defined */
/* Dependency: memrev from string */
#ifndef __local___localdep_memrev_defined
#define __local___localdep_memrev_defined 1
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
__NAMESPACE_LOCAL_END
#include <local/string/memrev.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrev __LIBC_LOCAL_NAME(memrev)
#endif /* !__CRT_HAVE_memrev */
#endif /* !__local___localdep_memrev_defined */
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
/* Dependency: memrevw from string */
#ifndef __local___localdep_memrevw_defined
#define __local___localdep_memrevw_defined 1
#ifdef __CRT_HAVE_memrevw
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memrevw,(void *__restrict __base, __SIZE_TYPE__ __n_words),memrevw,(__base,__n_words))
#else /* __CRT_HAVE_memrevw */
__NAMESPACE_LOCAL_END
#include <local/string/memrevw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrevw __LIBC_LOCAL_NAME(memrevw)
#endif /* !__CRT_HAVE_memrevw */
#endif /* !__local___localdep_memrevw_defined */
__LOCAL_LIBC(c16rev) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16rev))(__CHAR16_TYPE__ *__restrict __str) {
#if 2 == 2
	return (__CHAR16_TYPE__ *)__localdep_memrevw(__str, __localdep_c16len(__str));
#elif 2 == 4
	return (__CHAR16_TYPE__ *)__localdep_memrevl(__str, __localdep_c16len(__str));
#else /* ... */
	return (__CHAR16_TYPE__ *)__localdep_memrev(__str, __localdep_c16len(__str) * sizeof(__CHAR16_TYPE__));
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16rev_defined
#define __local___localdep_c16rev_defined 1
#define __localdep_c16rev __LIBC_LOCAL_NAME(c16rev)
#endif /* !__local___localdep_c16rev_defined */
#endif /* !__local_c16rev_defined */
