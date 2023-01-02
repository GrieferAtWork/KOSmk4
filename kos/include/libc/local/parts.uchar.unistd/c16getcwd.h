/* HASH CRC-32:0xaf9ac88b */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16getcwd_defined
#define __local_c16getcwd_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16len_defined
#define __local___localdep_c16len_defined
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_DOS$wcslen)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16len __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict),__SIZE_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict),wcslen)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16len.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16len __LIBC_LOCAL_NAME(c16len)
#endif /* !... */
#endif /* !__local___localdep_c16len_defined */
#ifndef __local___localdep_convert_mbstoc16_defined
#define __local___localdep_convert_mbstoc16_defined
#if defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_convert_mbstoc16,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_mbstowcs)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_convert_mbstoc16,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif (defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_mbstowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_mbstoc16 __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(char const *__restrict),__CHAR16_TYPE__ *(__LIBDCALL&)(char const *__restrict),convert_mbstowcs)
#elif (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_mbstoc16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_mbstoc16 __LIBC_LOCAL_NAME(convert_mbstoc16)
#else /* ... */
#undef __local___localdep_convert_mbstoc16_defined
#endif /* !... */
#endif /* !__local___localdep_convert_mbstoc16_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_getcwd_defined
#define __local___localdep_getcwd_defined
#ifdef __CRT_HAVE_getcwd
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),getcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),_getcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_getcwd_defined
#endif /* !... */
#endif /* !__local___localdep_getcwd_defined */
#ifndef __local___localdep_memcpyw_defined
#define __local___localdep_memcpyw_defined
#ifdef __CRT_HAVE_memcpyw
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcpy) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyw __LIBC_LOCAL_NAME(memcpyw)
#endif /* !... */
#endif /* !__local___localdep_memcpyw_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16getcwd) __ATTR_OUTS(1, 2) __CHAR16_TYPE__ *
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16getcwd))(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize) {
	char *__utf8_result;
	__CHAR16_TYPE__ *__result;
	__SIZE_TYPE__ __result_len;
	__utf8_result = (__NAMESPACE_LOCAL_SYM __localdep_getcwd)(__NULLPTR, 0);
	if __unlikely(!__utf8_result)
		return __NULLPTR;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_convert_mbstoc16)(__utf8_result);
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_result);
	if __unlikely(!__result)
		return __NULLPTR;
	__result_len = (__NAMESPACE_LOCAL_SYM __localdep_c16len)(__result) + 1;
	if (!__buf) {
		__CHAR16_TYPE__ *__new_result;
		if (!__bufsize)
			return __result;
		if (__bufsize < __result_len) {
#ifdef __ERANGE
			(void)__libc_seterrno(__ERANGE);
#else /* __ERANGE */
			(void)__libc_seterrno(1);
#endif /* !__ERANGE */
			__buf = __NULLPTR;
			goto __done;
		}
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
		__new_result = (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __bufsize * 2);
		if __unlikely(!__new_result) {
			__buf = __NULLPTR;
			goto __done;
		}
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
		__new_result = __result;
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
		return __new_result;
	}
	if (__bufsize < __result_len) {
#ifdef __ERANGE
		(void)__libc_seterrno(__ERANGE);
#else /* __ERANGE */
		(void)__libc_seterrno(1);
#endif /* !__ERANGE */
		__buf = __NULLPTR;
		goto __done;
	}
	__buf = (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memcpyw)(__buf, __result, __result_len);
__done:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16getcwd_defined
#define __local___localdep_c16getcwd_defined
#define __localdep_c16getcwd __LIBC_LOCAL_NAME(c16getcwd)
#endif /* !__local___localdep_c16getcwd_defined */
#else /* (__CRT_HAVE_getcwd || __CRT_HAVE__getcwd) && ((__CRT_HAVE_convert_mbstowcs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcs || ((__CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_convert_mbstowcsn && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (((__CRT_HAVE_format_waprintf_printer && __SIZEOF_WCHAR_T__ == 2 && __C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) || __CRT_HAVE_DOS$format_waprintf_printer || (__CRT_HAVE_format_waprintf_alloc && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_format_waprintf_pack && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
#undef __local_c16getcwd_defined
#endif /* (!__CRT_HAVE_getcwd && !__CRT_HAVE__getcwd) || ((!__CRT_HAVE_convert_mbstowcs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcs && ((!__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_convert_mbstowcsn || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (((!__CRT_HAVE_format_waprintf_printer || __SIZEOF_WCHAR_T__ != 2 || !__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) && !__CRT_HAVE_DOS$format_waprintf_printer && (!__CRT_HAVE_format_waprintf_alloc || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_format_waprintf_pack || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
#endif /* !__local_c16getcwd_defined */
