/* HASH CRC-32:0xcd101d49 */
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
#ifndef __local_c16printf_defined
#define __local_c16printf_defined
#include <__crt.h>
#include <features.h>
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_vwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwprintf) || (defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__LOCAL_stdout) && ((defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf) || (defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc_unlocked)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vc16printf_defined
#define __local___localdep_vc16printf_defined
#if defined(__CRT_HAVE_vwprintf_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf)
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf_unlocked)
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16printf __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SIZE_T(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__builtin_va_list),__STDC_INT_AS_SIZE_T(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__builtin_va_list),vwprintf)
#elif defined(__LOCAL_stdout) && ((defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf) || (defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc_unlocked))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vc16printf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16printf __LIBC_LOCAL_NAME(vc16printf)
#else /* ... */
#undef __local___localdep_vc16printf_defined
#endif /* !... */
#endif /* !__local___localdep_vc16printf_defined */
__LOCAL_LIBC(c16printf) __ATTR_IN(1) __ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SIZE_T
__NOTHROW_CB(__VLIBDCALL __LIBC_LOCAL_NAME(c16printf))(__CHAR16_TYPE__ const *__restrict __format, ...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vc16printf)(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16printf_defined
#define __local___localdep_c16printf_defined
#define __localdep_c16printf __LIBC_LOCAL_NAME(c16printf)
#endif /* !__local___localdep_c16printf_defined */
#else /* (__CRT_HAVE_vwprintf && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vwprintf || (__CRT_HAVE_vwprintf_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vwprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfwprintf || __CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2) || (__LOCAL_stdout && ((__CRT_HAVE_vfwprintf && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vfwprintf || (__CRT_HAVE_vfwprintf_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vfwprintf_unlocked || ((__CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_file_wprinter && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$file_wprinter || (__CRT_HAVE_file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$file_wprinter_unlocked || ((__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_fputwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc || (__CRT_HAVE_putwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc || (__CRT_HAVE_fputwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc_unlocked || (__CRT_HAVE_putwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc_unlocked)) */
#undef __local_c16printf_defined
#endif /* (!__CRT_HAVE_vwprintf || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vwprintf && (!__CRT_HAVE_vwprintf_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vwprintf_unlocked && (!__LOCAL_stdout || (!__CRT_HAVE_vfwprintf && !__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) || __SIZEOF_WCHAR_T__ != 2) && (!__LOCAL_stdout || ((!__CRT_HAVE_vfwprintf || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vfwprintf && (!__CRT_HAVE_vfwprintf_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vfwprintf_unlocked && ((!__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_file_wprinter || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$file_wprinter && (!__CRT_HAVE_file_wprinter_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$file_wprinter_unlocked && ((!__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_fputwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc && (!__CRT_HAVE_putwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc && (!__CRT_HAVE_fputwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc_unlocked && (!__CRT_HAVE_putwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc_unlocked)) */
#endif /* !__local_c16printf_defined */
