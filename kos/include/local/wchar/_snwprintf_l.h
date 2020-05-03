/* HASH CRC-32:0x1a31b7a0 */
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
#ifndef __local__snwprintf_l_defined
#define __local__snwprintf_l_defined 1
#include <__crt.h>
/* Dependency: "_vsnwprintf_l" from "wchar" */
#ifndef ____localdep__vsnwprintf_l_defined
#define ____localdep__vsnwprintf_l_defined 1
#ifdef __CRT_HAVE__vsnwprintf_l
__CREDIRECT(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsnwprintf_l,(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __bufsize, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vsnwprintf_l,(__dst,__bufsize,__format,__locale,__args))
#else /* LIBC: _vsnwprintf_l */
#include <local/wchar/_vsnwprintf_l.h>
#define __localdep__vsnwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_l))
#endif /* _vsnwprintf_l... */
#endif /* !____localdep__vsnwprintf_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_snwprintf_l) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_snwprintf_l))(__WCHAR_TYPE__ *__dst,
                                                           __SIZE_TYPE__ __bufsize,
                                                           __WCHAR_TYPE__ const *__format,
                                                           __locale_t __locale,
                                                           ...) {
#line 2086 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vsnwprintf_l(__dst, __bufsize, __format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__snwprintf_l_defined */
