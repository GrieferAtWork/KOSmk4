/* HASH CRC-32:0x37cc9df7 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___conio_common_vcwprintf_defined
#define __local___conio_common_vcwprintf_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___stdio_common_vfwprintf_defined
#define __local___localdep___stdio_common_vfwprintf_defined
#ifdef __CRT_HAVE___stdio_common_vfwprintf
__CREDIRECT(__ATTR_IN(3) __ATTR_INOUT(2) __ATTR_LIBC_WPRINTF(3, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___stdio_common_vfwprintf,(__UINT64_TYPE__ __options, __FILE *__stream, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__stdio_common_vfwprintf,(__options,__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/__stdio_common_vfwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___stdio_common_vfwprintf __LIBC_LOCAL_NAME(__stdio_common_vfwprintf)
#else /* ... */
#undef __local___localdep___stdio_common_vfwprintf_defined
#endif /* !... */
#endif /* !__local___localdep___stdio_common_vfwprintf_defined */
__NAMESPACE_LOCAL_END
#include <libc/template/stdtty.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__conio_common_vcwprintf) __ATTR_IN(2) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(__conio_common_vcwprintf))(__UINT64_TYPE__ __options, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep___stdio_common_vfwprintf)(__options, __LOCAL_stdtty, __format, __locale, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___conio_common_vcwprintf_defined
#define __local___localdep___conio_common_vcwprintf_defined
#define __localdep___conio_common_vcwprintf __LIBC_LOCAL_NAME(__conio_common_vcwprintf)
#endif /* !__local___localdep___conio_common_vcwprintf_defined */
#else /* __CRT_HAVE_stdtty && (__CRT_HAVE___stdio_common_vfwprintf || __CRT_HAVE_vfwprintf || __CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) */
#undef __local___conio_common_vcwprintf_defined
#endif /* !__CRT_HAVE_stdtty || (!__CRT_HAVE___stdio_common_vfwprintf && !__CRT_HAVE_vfwprintf && !__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) */
#endif /* !__local___conio_common_vcwprintf_defined */
