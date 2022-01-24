/* HASH CRC-32:0xfe18b91 */
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
#ifndef __local_c16sethostname_defined
#define __local_c16sethostname_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_sethostname) || defined(__CRT_HAVE___sethostname) || defined(__CRT_HAVE___libc_sethostname)) && ((defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_c16tombsn_defined
#define __local___localdep_convert_c16tombsn_defined
#if defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c16tombsn,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif defined(__CRT_HAVE_DOS$convert_wcstombsn)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c16tombsn,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombsn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c16tombsn __NAMESPACE_LOCAL_TYPEHAX(char *(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__,__SIZE_TYPE__ *),char *(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__,__SIZE_TYPE__ *),convert_wcstombsn)
#elif defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_c16tombsn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c16tombsn __LIBC_LOCAL_NAME(convert_c16tombsn)
#else /* ... */
#undef __local___localdep_convert_c16tombsn_defined
#endif /* !... */
#endif /* !__local___localdep_convert_c16tombsn_defined */
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
#ifndef __local___localdep_sethostname_defined
#define __local___localdep_sethostname_defined
#ifdef __CRT_HAVE_sethostname
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sethostname,(char const *__name, __SIZE_TYPE__ __len),sethostname,(__name,__len))
#elif defined(__CRT_HAVE___sethostname)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sethostname,(char const *__name, __SIZE_TYPE__ __len),__sethostname,(__name,__len))
#elif defined(__CRT_HAVE___libc_sethostname)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sethostname,(char const *__name, __SIZE_TYPE__ __len),__libc_sethostname,(__name,__len))
#else /* ... */
#undef __local___localdep_sethostname_defined
#endif /* !... */
#endif /* !__local___localdep_sethostname_defined */
__LOCAL_LIBC(c16sethostname) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16sethostname))(__CHAR16_TYPE__ const *__name, __SIZE_TYPE__ __len) {
	int __result;
	char *__utf8_name;
	__SIZE_TYPE__ __utf8_len;
	__utf8_name = (__NAMESPACE_LOCAL_SYM __localdep_convert_c16tombsn)(__name, __len, &__utf8_len);
	if __unlikely(!__utf8_name)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_sethostname)(__utf8_name, __utf8_len);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_name);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16sethostname_defined
#define __local___localdep_c16sethostname_defined
#define __localdep_c16sethostname __LIBC_LOCAL_NAME(c16sethostname)
#endif /* !__local___localdep_c16sethostname_defined */
#else /* (__CRT_HAVE_sethostname || __CRT_HAVE___sethostname || __CRT_HAVE___libc_sethostname) && ((__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_c16sethostname_defined
#endif /* (!__CRT_HAVE_sethostname && !__CRT_HAVE___sethostname && !__CRT_HAVE___libc_sethostname) || ((!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_c16sethostname_defined */
