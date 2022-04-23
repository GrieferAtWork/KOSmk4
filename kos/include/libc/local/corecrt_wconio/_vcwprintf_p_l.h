/* HASH CRC-32:0xedee9631 */
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
#ifndef __local__vcwprintf_p_l_defined
#define __local__vcwprintf_p_l_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE___conio_common_vcwprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_p) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___conio_common_vcwprintf_p_defined
#define __local___localdep___conio_common_vcwprintf_p_defined
#ifdef __CRT_HAVE___conio_common_vcwprintf_p
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LIBC_WPRINTF_P(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___conio_common_vcwprintf_p,(__UINT64_TYPE__ __options, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__conio_common_vcwprintf_p,(__options,__format,__locale,__args))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_p) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wconio/__conio_common_vcwprintf_p.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___conio_common_vcwprintf_p __LIBC_LOCAL_NAME(__conio_common_vcwprintf_p)
#else /* ... */
#undef __local___localdep___conio_common_vcwprintf_p_defined
#endif /* !... */
#endif /* !__local___localdep___conio_common_vcwprintf_p_defined */
__NAMESPACE_LOCAL_END
#include <corecrt_stdio_config.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vcwprintf_p_l) __ATTR_LIBC_WPRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vcwprintf_p_l))(__WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep___conio_common_vcwprintf_p)(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, __format, __locale, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vcwprintf_p_l_defined
#define __local___localdep__vcwprintf_p_l_defined
#define __localdep__vcwprintf_p_l __LIBC_LOCAL_NAME(_vcwprintf_p_l)
#endif /* !__local___localdep__vcwprintf_p_l_defined */
#else /* __CRT_HAVE___conio_common_vcwprintf_p || (__CRT_HAVE_stdtty && (__CRT_HAVE___stdio_common_vfwprintf_p || __CRT_HAVE_vfwprintf || __CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked)) */
#undef __local__vcwprintf_p_l_defined
#endif /* !__CRT_HAVE___conio_common_vcwprintf_p && (!__CRT_HAVE_stdtty || (!__CRT_HAVE___stdio_common_vfwprintf_p && !__CRT_HAVE_vfwprintf && !__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked)) */
#endif /* !__local__vcwprintf_p_l_defined */
