/* HASH CRC-32:0x2f7e86a6 */
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
#ifndef __local_c32printf_unlocked_defined
#define __local_c32printf_unlocked_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vwprintf_unlocked) || ((defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS))
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vc32printf_unlocked from parts.uchar.stdio */
#ifndef __local___localdep_vc32printf_unlocked_defined
#define __local___localdep_vc32printf_unlocked_defined 1
#if defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc32printf_unlocked,(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_KOS$vwprintf_unlocked)
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc32printf_unlocked,(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwprintf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc32printf_unlocked (*(__STDC_INT_AS_SIZE_T(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __builtin_va_list))&__LIBC_LOCAL_NAME(vwprintf_unlocked))
#elif ((defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vc32printf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc32printf_unlocked __LIBC_LOCAL_NAME(vc32printf_unlocked)
#else /* ... */
#undef __local___localdep_vc32printf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vc32printf_unlocked_defined */
__LOCAL_LIBC(c32printf_unlocked) __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBKCALL __LIBC_LOCAL_NAME(c32printf_unlocked))(__CHAR32_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vc32printf_unlocked(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32printf_unlocked_defined
#define __local___localdep_c32printf_unlocked_defined 1
#define __localdep_c32printf_unlocked __LIBC_LOCAL_NAME(c32printf_unlocked)
#endif /* !__local___localdep_c32printf_unlocked_defined */
#else /* (__CRT_HAVE_vwprintf_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vwprintf_unlocked || ((__CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && !__NO_STDSTREAMS && __SIZEOF_WCHAR_T__ == 4) || (((__CRT_HAVE_vfwprintf_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vfwprintf_unlocked || ((__CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$file_wprinter_unlocked || (__CRT_HAVE_file_wprinter && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$file_wprinter || ((__CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_fputwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fputwc_unlocked || (__CRT_HAVE__fputwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_fputwc_nolock) && !__NO_STDSTREAMS) */
#undef __local_c32printf_unlocked_defined
#endif /* (!__CRT_HAVE_vwprintf_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vwprintf_unlocked && ((!__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE__fputwc_nolock) || __NO_STDSTREAMS || __SIZEOF_WCHAR_T__ != 4) && (((!__CRT_HAVE_vfwprintf_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vfwprintf_unlocked && ((!__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE__fputwc_nolock) || __SIZEOF_WCHAR_T__ != 4) && (!__CRT_HAVE_file_wprinter_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$file_wprinter_unlocked && (!__CRT_HAVE_file_wprinter || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$file_wprinter && ((!__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE__fputwc_nolock) || __SIZEOF_WCHAR_T__ != 4) && (!__CRT_HAVE_fputwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fputwc_unlocked && (!__CRT_HAVE__fputwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_fputwc_nolock) || __NO_STDSTREAMS) */
#endif /* !__local_c32printf_unlocked_defined */
