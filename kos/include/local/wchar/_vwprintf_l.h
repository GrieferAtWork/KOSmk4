/* HASH CRC-32:0x5eb40d65 */
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
#ifndef __local__vwprintf_l_defined
#if ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf)
#define __local__vwprintf_l_defined 1
#include <kos/anno.h>
/* Dependency: "vwprintf" from "wchar" */
#ifndef ____localdep_vwprintf_defined
#define ____localdep_vwprintf_defined 1
#ifdef __std___localdep_vwprintf_defined
__NAMESPACE_STD_USING(__localdep_vwprintf)
#elif defined(__CRT_HAVE_vwprintf)
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep_vwprintf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args)) __THROWS(...)
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwprintf.h>
#define __localdep_vwprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))
#else /* CUSTOM: vwprintf */
#undef ____localdep_vwprintf_defined
#endif /* vwprintf... */
#endif /* !____localdep_vwprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vwprintf_l) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vwprintf_l))(__WCHAR_TYPE__ const *__format,
                                            __locale_t __locale,
                                            __builtin_va_list __args) __THROWS(...) {
#line 1940 "kos/src/libc/magic/wchar.c"
	(void)__locale;
	return __localdep_vwprintf(__format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* ((__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_vfwprintf) && !__NO_STDSTREAMS) || __CRT_HAVE_vwprintf */
#endif /* !__local__vwprintf_l_defined */
