/* HASH CRC-32:0xdf59459d */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vc16printf_unlocked_defined
#if (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS)
#define __local_vc16printf_unlocked_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "vfwprintf_unlocked" from "wchar" */
#ifndef ____localdep_vfc16printf_unlocked_defined
#define ____localdep_vfc16printf_unlocked_defined 1
#if defined(__CRT_HAVE_vfwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc16printf_unlocked,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc16printf_unlocked,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vfwprintf_unlocked.h>
#define __localdep_vfc16printf_unlocked(stream, format, args) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(stream, (__WCHAR_TYPE__ const *)(format), args)
#else /* LIBC: vfc16printf_unlocked */
#include <local/wchar/vfc16printf_unlocked.h>
#define __localdep_vfc16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc16printf_unlocked))
#endif /* LIBC: vfc16printf_unlocked */
#else /* CUSTOM: vfwprintf_unlocked */
#undef ____localdep_vfc16printf_unlocked_defined
#endif /* vfc16printf_unlocked... */
#endif /* !____localdep_vfc16printf_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vc16printf_unlocked) __ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SIZE_T
(__LIBDCALL __LIBC_LOCAL_NAME(vc16printf_unlocked))(__CHAR16_TYPE__ const *__restrict __format,
                                                    __builtin_va_list __args) __THROWS(...) {
#line 1188 "kos/src/libc/magic/wchar.c"
	return __localdep_vfc16printf_unlocked(__LOCAL_stdout, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS) */
#endif /* !__local_vc16printf_unlocked_defined */
