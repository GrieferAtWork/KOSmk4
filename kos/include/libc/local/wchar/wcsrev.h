/* HASH CRC-32:0x8b0d7df */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcsrev_defined
#define __local_wcsrev_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memrev_defined
#define __local___localdep_memrev_defined
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrev.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrev __LIBC_LOCAL_NAME(memrev)
#endif /* !__CRT_HAVE_memrev */
#endif /* !__local___localdep_memrev_defined */
#ifndef __local___localdep_memrevl_defined
#define __local___localdep_memrevl_defined
#ifdef __CRT_HAVE_memrevl
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrevl,(void *__restrict __base, __SIZE_TYPE__ __n_dwords),memrevl,(__base,__n_dwords))
#else /* __CRT_HAVE_memrevl */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrevl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrevl __LIBC_LOCAL_NAME(memrevl)
#endif /* !__CRT_HAVE_memrevl */
#endif /* !__local___localdep_memrevl_defined */
#ifndef __local___localdep_memrevw_defined
#define __local___localdep_memrevw_defined
#ifdef __CRT_HAVE_memrevw
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memrevw,(void *__restrict __base, __SIZE_TYPE__ __n_words),memrevw,(__base,__n_words))
#else /* __CRT_HAVE_memrevw */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrevw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrevw __LIBC_LOCAL_NAME(memrevw)
#endif /* !__CRT_HAVE_memrevw */
#endif /* !__local___localdep_memrevw_defined */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined
#ifdef __CRT_HAVE_wcslen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __str),wcslen,(__str))
#else /* __CRT_HAVE_wcslen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__CRT_HAVE_wcslen */
#endif /* !__local___localdep_wcslen_defined */
__LOCAL_LIBC(wcsrev) __ATTR_RETNONNULL __ATTR_INOUT(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsrev))(__WCHAR_TYPE__ *__restrict __str) {
#if __SIZEOF_WCHAR_T__ == 2
	return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memrevw)(__str, (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__str));
#elif __SIZEOF_WCHAR_T__ == 4
	return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memrevl)(__str, (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__str));
#else /* ... */
	return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memrev)(__str, (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__str) * sizeof(__WCHAR_TYPE__));
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsrev_defined
#define __local___localdep_wcsrev_defined
#define __localdep_wcsrev __LIBC_LOCAL_NAME(wcsrev)
#endif /* !__local___localdep_wcsrev_defined */
#endif /* !__local_wcsrev_defined */
