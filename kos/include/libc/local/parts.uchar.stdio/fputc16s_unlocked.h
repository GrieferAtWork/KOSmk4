/* HASH CRC-32:0x917e9a2a */
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
#ifndef __local_fputc16s_unlocked_defined
#define __local_fputc16s_unlocked_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc_unlocked) || (defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_putwc_nolock) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc)
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16len_defined
#define __local___localdep_c16len_defined
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_DOS$wcslen)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16len __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict),__SIZE_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict),wcslen)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16len.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16len __LIBC_LOCAL_NAME(c16len)
#endif /* !... */
#endif /* !__local___localdep_c16len_defined */
#ifndef __local___localdep_file_c16printer_unlocked_defined
#define __local___localdep_file_c16printer_unlocked_defined
#if defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/file_wprinter_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_file_c16printer_unlocked __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBDCALL*)(void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__),__SSIZE_TYPE__(__LIBDCALL&)(void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__),file_wprinter_unlocked)
#elif (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc_unlocked) || (defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_putwc_nolock) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/file_c16printer_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_file_c16printer_unlocked __LIBC_LOCAL_NAME(file_c16printer_unlocked)
#else /* ... */
#undef __local___localdep_file_c16printer_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_file_c16printer_unlocked_defined */
__LOCAL_LIBC(fputc16s_unlocked) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBDCALL __LIBC_LOCAL_NAME(fputc16s_unlocked))(__CHAR16_TYPE__ const *__restrict __str, __FILE *__restrict __stream) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_file_c16printer_unlocked)(__stream, __str, (__NAMESPACE_LOCAL_SYM __localdep_c16len)(__str));
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fputc16s_unlocked_defined
#define __local___localdep_fputc16s_unlocked_defined
#define __localdep_fputc16s_unlocked __LIBC_LOCAL_NAME(fputc16s_unlocked)
#endif /* !__local___localdep_fputc16s_unlocked_defined */
#else /* (__CRT_HAVE_file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$file_wprinter_unlocked || (__CRT_HAVE_file_wprinter && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$file_wprinter || ((__CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock || __CRT_HAVE_putwc || __CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_fputwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc_unlocked || (__CRT_HAVE_putwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc_unlocked || (__CRT_HAVE__putwc_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_putwc_nolock || (__CRT_HAVE__fputwc_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_fputwc_nolock || (__CRT_HAVE_putwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc || (__CRT_HAVE_fputwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc */
#undef __local_fputc16s_unlocked_defined
#endif /* (!__CRT_HAVE_file_wprinter_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$file_wprinter_unlocked && (!__CRT_HAVE_file_wprinter || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$file_wprinter && ((!__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked && !__CRT_HAVE__putwc_nolock && !__CRT_HAVE__fputwc_nolock && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_fputwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc_unlocked && (!__CRT_HAVE_putwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc_unlocked && (!__CRT_HAVE__putwc_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_putwc_nolock && (!__CRT_HAVE__fputwc_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_fputwc_nolock && (!__CRT_HAVE_putwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc && (!__CRT_HAVE_fputwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc */
#endif /* !__local_fputc16s_unlocked_defined */
