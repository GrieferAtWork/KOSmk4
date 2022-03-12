/* HASH CRC-32:0xb4b9ae48 */
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
#ifndef __local_vfwprintf_unlocked_defined
#define __local_vfwprintf_unlocked_defined
#include <__crt.h>
#if defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock)
#include <features.h>
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_file_wprinter_unlocked_defined
#define __local___localdep_file_wprinter_unlocked_defined
#ifdef __CRT_HAVE_file_wprinter_unlocked
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/file_wprinter_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_file_wprinter_unlocked __LIBC_LOCAL_NAME(file_wprinter_unlocked)
#else /* ... */
#undef __local___localdep_file_wprinter_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_file_wprinter_unlocked_defined */
#ifndef __local___localdep_format_vwprintf_defined
#define __local___localdep_format_vwprintf_defined
#ifdef __CRT_HAVE_format_vwprintf
__NAMESPACE_LOCAL_END
#include <bits/crt/wformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)),__SSIZE_TYPE__,__THROWING,__localdep_format_vwprintf,(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vwprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vwprintf __LIBC_LOCAL_NAME(format_vwprintf)
#endif /* !__CRT_HAVE_format_vwprintf */
#endif /* !__local___localdep_format_vwprintf_defined */
__LOCAL_LIBC(vfwprintf_unlocked) __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __localdep_format_vwprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_file_wprinter_unlocked),
	                                              __stream, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vfwprintf_unlocked_defined
#define __local___localdep_vfwprintf_unlocked_defined
#define __localdep_vfwprintf_unlocked __LIBC_LOCAL_NAME(vfwprintf_unlocked)
#endif /* !__local___localdep_vfwprintf_unlocked_defined */
#else /* __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock */
#undef __local_vfwprintf_unlocked_defined
#endif /* !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked && !__CRT_HAVE__putwc_nolock && !__CRT_HAVE__fputwc_nolock */
#endif /* !__local_vfwprintf_unlocked_defined */
