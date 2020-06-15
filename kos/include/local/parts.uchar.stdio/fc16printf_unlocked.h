/* HASH CRC-32:0x5494b7d9 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fc16printf_unlocked_defined
#define __local_fc16printf_unlocked_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked)) && (__SIZEOF_WCHAR_T__ == 2)) || (defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)) || (defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked)
#include <kos/anno.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vfc16printf_unlocked from parts.uchar.stdio */
#ifndef __local___localdep_vfc16printf_unlocked_defined
#define __local___localdep_vfc16printf_unlocked_defined 1
#if defined(__CRT_HAVE_vfwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc16printf_unlocked,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf_unlocked)
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc16printf_unlocked,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked)) && (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/vfwprintf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc16printf_unlocked (*(__STDC_INT_AS_SIZE_T(__LIBDCALL *)(__FILE *__restrict, __CHAR16_TYPE__ const *__restrict, __builtin_va_list))&__LIBC_LOCAL_NAME(vfwprintf_unlocked))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)) || (defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked)
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.stdio/vfc16printf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc16printf_unlocked __LIBC_LOCAL_NAME(vfc16printf_unlocked)
#else /* ... */
#undef __local___localdep_vfc16printf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vfc16printf_unlocked_defined */
__LOCAL_LIBC(fc16printf_unlocked) __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__VLIBDCALL __LIBC_LOCAL_NAME(fc16printf_unlocked))(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vfc16printf_unlocked(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fc16printf_unlocked_defined
#define __local___localdep_fc16printf_unlocked_defined 1
#define __localdep_fc16printf_unlocked __LIBC_LOCAL_NAME(fc16printf_unlocked)
#endif /* !__local___localdep_fc16printf_unlocked_defined */
#else /* (__CRT_HAVE_vfwprintf_unlocked && (__SIZEOF_WCHAR_T__ == 2) && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vfwprintf_unlocked || ((__CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)) || (__CRT_HAVE_file_wprinter_unlocked && (__SIZEOF_WCHAR_T__ == 2) && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$file_wprinter_unlocked || (__CRT_HAVE_file_wprinter && (__SIZEOF_WCHAR_T__ == 2) && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$file_wprinter || (__CRT_HAVE_fputwc_unlocked && (__SIZEOF_WCHAR_T__ == 2)) || (__CRT_HAVE_fputwc_unlocked && (__SIZEOF_WCHAR_T__ == 2) && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc_unlocked */
#undef __local_fc16printf_unlocked_defined
#endif /* (!__CRT_HAVE_vfwprintf_unlocked || !(__SIZEOF_WCHAR_T__ == 2) || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vfwprintf_unlocked && ((!__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_fputwc_unlocked) || !(__SIZEOF_WCHAR_T__ == 2)) && (!__CRT_HAVE_file_wprinter_unlocked || !(__SIZEOF_WCHAR_T__ == 2) || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$file_wprinter_unlocked && (!__CRT_HAVE_file_wprinter || !(__SIZEOF_WCHAR_T__ == 2) || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$file_wprinter && (!__CRT_HAVE_fputwc_unlocked || !(__SIZEOF_WCHAR_T__ == 2)) && (!__CRT_HAVE_fputwc_unlocked || !(__SIZEOF_WCHAR_T__ == 2) || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc_unlocked */
#endif /* !__local_fc16printf_unlocked_defined */
