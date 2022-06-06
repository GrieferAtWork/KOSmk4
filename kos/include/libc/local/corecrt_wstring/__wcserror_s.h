/* HASH CRC-32:0xb00e6df3 */
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
#ifndef __local___wcserror_s_defined
#define __local___wcserror_s_defined
#include <__crt.h>
#include <libc/errno.h>
#if defined(__CRT_HAVE___wcserror) || ((defined(__CRT_HAVE__strerror) || defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___wcserror_defined
#define __local___localdep___wcserror_defined
#ifdef __CRT_HAVE___wcserror
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep___wcserror,(__WCHAR_TYPE__ const *__message),__wcserror,(__message))
#elif (defined(__CRT_HAVE__strerror) || defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstring/__wcserror.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___wcserror __LIBC_LOCAL_NAME(__wcserror)
#else /* ... */
#undef __local___localdep___wcserror_defined
#endif /* !... */
#endif /* !__local___localdep___wcserror_defined */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined
#ifdef __CRT_HAVE_wcslen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __str),wcslen,(__str))
#else /* __CRT_HAVE_wcslen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__CRT_HAVE_wcslen */
#endif /* !__local___localdep_wcslen_defined */
#ifndef __local___localdep_wmemcpy_defined
#define __local___localdep_wmemcpy_defined
#ifdef __CRT_HAVE_wmemcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy __NAMESPACE_LOCAL_TYPEHAX(__WCHAR_TYPE__ *(__LIBCCALL*)(__WCHAR_TYPE__ *__restrict,__WCHAR_TYPE__ const *__restrict,__SIZE_TYPE__),__WCHAR_TYPE__ *(__LIBCCALL&)(__WCHAR_TYPE__ *__restrict,__WCHAR_TYPE__ const *__restrict,__SIZE_TYPE__),memcpyw)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy __NAMESPACE_LOCAL_TYPEHAX(__WCHAR_TYPE__ *(__LIBCCALL*)(__WCHAR_TYPE__ *__restrict,__WCHAR_TYPE__ const *__restrict,__SIZE_TYPE__),__WCHAR_TYPE__ *(__LIBCCALL&)(__WCHAR_TYPE__ *__restrict,__WCHAR_TYPE__ const *__restrict,__SIZE_TYPE__),memcpyl)
#else /* __SIZEOF_WCHAR_T__ == 4 */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wmemcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcpy __LIBC_LOCAL_NAME(wmemcpy)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif /* !... */
#endif /* !__local___localdep_wmemcpy_defined */
__LOCAL_LIBC(__wcserror_s) __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__wcserror_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__message) {
	__WCHAR_TYPE__ *__msg  = (__NAMESPACE_LOCAL_SYM __localdep___wcserror)(__message);
	__SIZE_TYPE__ __msglen;
	if (!__msg) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	__msglen = (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__msg) + 1;
	if (__msglen >= __buflen) {
#ifdef __ERANGE
		return __ERANGE;
#else /* __ERANGE */
		return 1;
#endif /* !__ERANGE */
	}
	(void)(__NAMESPACE_LOCAL_SYM __localdep_wmemcpy)(__buf, __msg, __msglen);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___wcserror_s_defined
#define __local___localdep___wcserror_s_defined
#define __localdep___wcserror_s __LIBC_LOCAL_NAME(__wcserror_s)
#endif /* !__local___localdep___wcserror_s_defined */
#else /* __CRT_HAVE___wcserror || ((__CRT_HAVE__strerror || __CRT_HAVE__strerror_s || __libc_geterrno) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local___wcserror_s_defined
#endif /* !__CRT_HAVE___wcserror && ((!__CRT_HAVE__strerror && !__CRT_HAVE__strerror_s && !__libc_geterrno) || (!__CRT_HAVE_convert_mbstowcs && !__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local___wcserror_s_defined */
