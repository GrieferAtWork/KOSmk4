/* HASH CRC-32:0xdfc806ad */
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
#ifndef __local__wprintf_l_defined
#if ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf) || defined(__CRT_HAVE__vwprintf_l)
#define __local__wprintf_l_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "_vwprintf_l" from "wchar" */
#ifndef ____localdep__vwprintf_l_defined
#define ____localdep__vwprintf_l_defined 1
#ifdef __CRT_HAVE__vwprintf_l
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,__localdep__vwprintf_l,(__WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vwprintf_l,(__format,__locale,__args)) __THROWS(...)
#elif ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf)
#include <local/wchar/_vwprintf_l.h>
#define __localdep__vwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_l))
#else /* CUSTOM: _vwprintf_l */
#undef ____localdep__vwprintf_l_defined
#endif /* _vwprintf_l... */
#endif /* !____localdep__vwprintf_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wprintf_l) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_wprintf_l))(__WCHAR_TYPE__ const *__format,
                                            __locale_t __locale,
                                            ...) __THROWS(...) {
#line 1987 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vwprintf_l(__format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_vfwprintf) && !__NO_STDSTREAMS) || __CRT_HAVE_vwprintf || __CRT_HAVE__vwprintf_l */
#endif /* !__local__wprintf_l_defined */
