/* HASH CRC-32:0xa9424f2a */
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
#ifndef __local__vfwprintf_s_l_defined
#if defined(__CRT_HAVE_vfwprintf_s) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#define __local__vfwprintf_s_l_defined 1
#include <kos/anno.h>
/* Dependency: "vfwprintf_s" from "wchar" */
#ifndef ____localdep_vfwprintf_s_defined
#define ____localdep_vfwprintf_s_defined 1
#if defined(__CRT_HAVE_vfwprintf_s)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,__localdep_vfwprintf_s,(__FILE *__stream, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),vfwprintf_s,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwprintf)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,__localdep_vfwprintf_s,(__FILE *__stream, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#include <local/wchar/vfwprintf.h>
#define __localdep_vfwprintf_s(stream, format, args) (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))((__FILE *)(stream), (__WCHAR_TYPE__ const *)(format), args)
#else /* CUSTOM: vfwprintf */
#undef ____localdep_vfwprintf_s_defined
#endif /* vfwprintf_s... */
#endif /* !____localdep_vfwprintf_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vfwprintf_s_l) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vfwprintf_s_l))(__FILE *__stream,
                                               __WCHAR_TYPE__ const *__format,
                                               __locale_t __locale,
                                               __builtin_va_list __args) __THROWS(...) {
#line 1891 "kos/src/libc/magic/wchar.c"
	(void)__locale;
	return __localdep_vfwprintf_s(__stream, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_vfwprintf_s) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) */
#endif /* !__local__vfwprintf_s_l_defined */
