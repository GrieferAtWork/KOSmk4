/* HASH CRC-32:0x41e58ccd */
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
#ifndef __local__vwprintf_s_l_defined
#define __local__vwprintf_s_l_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <features.h>
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vwprintf from wchar */
#ifndef __local___localdep_vwprintf_defined
#define __local___localdep_vwprintf_defined 1
#ifdef __CRT_HAVE_vwprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vwprintf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vwprintf __LIBC_LOCAL_NAME(vwprintf)
#else /* ... */
#undef __local___localdep_vwprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vwprintf_defined */
__LOCAL_LIBC(_vwprintf_s_l) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vwprintf_s_l))(__WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) {
	(void)__locale;
	return __localdep_vwprintf(__format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vwprintf_s_l_defined
#define __local___localdep__vwprintf_s_l_defined 1
#define __localdep__vwprintf_s_l __LIBC_LOCAL_NAME(_vwprintf_s_l)
#endif /* !__local___localdep__vwprintf_s_l_defined */
#else /* __CRT_HAVE_vwprintf || ((__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS) */
#undef __local__vwprintf_s_l_defined
#endif /* !__CRT_HAVE_vwprintf && ((!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS) */
#endif /* !__local__vwprintf_s_l_defined */
