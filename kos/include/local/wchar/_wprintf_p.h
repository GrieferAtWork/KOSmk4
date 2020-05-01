/* HASH CRC-32:0x9e34d219 */
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
#ifndef __local__wprintf_p_defined
#if !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE__vwprintf_p)
#define __local__wprintf_p_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "_vwprintf_p" from "wchar" */
#ifndef ____localdep__vwprintf_p_defined
#define ____localdep__vwprintf_p_defined 1
#ifdef __CRT_HAVE__vwprintf_p
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,__localdep__vwprintf_p,(__WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vwprintf_p,(__format,__args)) __THROWS(...)
#elif !defined(__NO_STDSTREAMS)
#include <local/wchar/_vwprintf_p.h>
#define __localdep__vwprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_p))
#else /* CUSTOM: _vwprintf_p */
#undef ____localdep__vwprintf_p_defined
#endif /* _vwprintf_p... */
#endif /* !____localdep__vwprintf_p_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wprintf_p) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_wprintf_p))(__WCHAR_TYPE__ const *__format,
                                            ...) __THROWS(...) {
#line 1959 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vwprintf_p(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__NO_STDSTREAMS || __CRT_HAVE__vwprintf_p */
#endif /* !__local__wprintf_p_defined */
