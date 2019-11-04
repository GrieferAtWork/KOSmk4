/* HASH CRC-32:0x2c17e808 */
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
#ifndef __local__swprintf_p_defined
#if 1
#define __local__swprintf_p_defined 1
/* Dependency: "_vswprintf_p" from "wchar" */
#ifndef ____localdep__vswprintf_p_defined
#define ____localdep__vswprintf_p_defined 1
#ifdef __CRT_HAVE__vswprintf_p
__CREDIRECT(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vswprintf_p,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vswprintf_p,(__buf,__bufsize,__format,__args))
#else /* LIBC: _vswprintf_p */
#include <local/wchar/_vswprintf_p.h>
#define __localdep__vswprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_p))
#endif /* _vswprintf_p... */
#endif /* !____localdep__vswprintf_p_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_swprintf_p) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_swprintf_p))(__WCHAR_TYPE__ *__dst,
                                                          __SIZE_TYPE__ __bufsize,
                                                          __WCHAR_TYPE__ const *__format,
                                                          ...) {
#line 1822 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vswprintf_p(__dst, __bufsize, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local__swprintf_p_defined */
