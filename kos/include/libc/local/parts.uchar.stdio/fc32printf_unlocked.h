/* HASH CRC-32:0xdc7a3585 */
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
#ifndef __local_fc32printf_unlocked_defined
#define __local_fc32printf_unlocked_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf_unlocked) || (defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc_unlocked) || (defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_putwc_nolock) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc)
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfc32printf_unlocked_defined
#define __local___localdep_vfc32printf_unlocked_defined
#if defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_C32PRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vfc32printf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwprintf_unlocked)
__CREDIRECT_KOS(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_C32PRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vfc32printf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_C32PRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vfc32printf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwprintf)
__CREDIRECT_KOS(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_C32PRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vfc32printf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vfwprintf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc32printf_unlocked __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SIZE_T(__LIBKCALL*)(__FILE *__restrict,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),__STDC_INT_AS_SIZE_T(__LIBKCALL&)(__FILE *__restrict,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),vfwprintf_unlocked)
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc_unlocked) || (defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_putwc_nolock) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vfc32printf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc32printf_unlocked __LIBC_LOCAL_NAME(vfc32printf_unlocked)
#else /* ... */
#undef __local___localdep_vfc32printf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vfc32printf_unlocked_defined */
__LOCAL_LIBC(fc32printf_unlocked) __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_C32PRINTF(2, 3) __STDC_INT_AS_SIZE_T
__NOTHROW_CB(__VLIBKCALL __LIBC_LOCAL_NAME(fc32printf_unlocked))(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, ...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vfc32printf_unlocked)(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fc32printf_unlocked_defined
#define __local___localdep_fc32printf_unlocked_defined
#define __localdep_fc32printf_unlocked __LIBC_LOCAL_NAME(fc32printf_unlocked)
#endif /* !__local___localdep_fc32printf_unlocked_defined */
#else /* (__CRT_HAVE_vfwprintf_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vfwprintf_unlocked || (__CRT_HAVE_vfwprintf && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vfwprintf || ((__CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock || __CRT_HAVE_putwc || __CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$file_wprinter_unlocked || (__CRT_HAVE_file_wprinter && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$file_wprinter || ((__CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock || __CRT_HAVE_putwc || __CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_fputwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fputwc_unlocked || (__CRT_HAVE_putwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$putwc_unlocked || (__CRT_HAVE__putwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_putwc_nolock || (__CRT_HAVE__fputwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_fputwc_nolock || (__CRT_HAVE_putwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$putwc || (__CRT_HAVE_fputwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fputwc */
#undef __local_fc32printf_unlocked_defined
#endif /* (!__CRT_HAVE_vfwprintf_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vfwprintf_unlocked && (!__CRT_HAVE_vfwprintf || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vfwprintf && ((!__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked && !__CRT_HAVE__putwc_nolock && !__CRT_HAVE__fputwc_nolock && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc) || __SIZEOF_WCHAR_T__ != 4) && (!__CRT_HAVE_file_wprinter_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$file_wprinter_unlocked && (!__CRT_HAVE_file_wprinter || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$file_wprinter && ((!__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked && !__CRT_HAVE__putwc_nolock && !__CRT_HAVE__fputwc_nolock && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc) || __SIZEOF_WCHAR_T__ != 4) && (!__CRT_HAVE_fputwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fputwc_unlocked && (!__CRT_HAVE_putwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$putwc_unlocked && (!__CRT_HAVE__putwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_putwc_nolock && (!__CRT_HAVE__fputwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_fputwc_nolock && (!__CRT_HAVE_putwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$putwc && (!__CRT_HAVE_fputwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fputwc */
#endif /* !__local_fc32printf_unlocked_defined */
