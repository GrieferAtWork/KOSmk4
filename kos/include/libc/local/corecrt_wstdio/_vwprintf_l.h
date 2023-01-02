/* HASH CRC-32:0xe824dbd3 */
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
#ifndef __local__vwprintf_l_defined
#define __local__vwprintf_l_defined
#include <__crt.h>
#include <features.h>
#include <libc/template/stdstreams.h>
#if defined(__CRT_HAVE_vwprintf) || defined(__CRT_HAVE_vwprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vwprintf_defined
#define __local___localdep_vwprintf_defined
#if defined(__CRT_HAVE_vwprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vwprintf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vwprintf)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vwprintf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif defined(__CRT_HAVE_vwprintf_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vwprintf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vwprintf __LIBC_LOCAL_NAME(vwprintf)
#else /* ... */
#undef __local___localdep_vwprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vwprintf_defined */
__LOCAL_LIBC(_vwprintf_l) __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vwprintf_l))(__WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_vwprintf)(__format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vwprintf_l_defined
#define __local___localdep__vwprintf_l_defined
#define __localdep__vwprintf_l __LIBC_LOCAL_NAME(_vwprintf_l)
#endif /* !__local___localdep__vwprintf_l_defined */
#else /* __CRT_HAVE_vwprintf || __CRT_HAVE_vwprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfwprintf || __CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked)) */
#undef __local__vwprintf_l_defined
#endif /* !__CRT_HAVE_vwprintf && !__CRT_HAVE_vwprintf_unlocked && (!__LOCAL_stdout || (!__CRT_HAVE_vfwprintf && !__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked)) */
#endif /* !__local__vwprintf_l_defined */
