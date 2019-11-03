/* HASH CRC-32:0xc1ae4ca4 */
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
#ifndef __local__swprintf_c_defined
#if defined(__CRT_HAVE__vswprintf_c)
#define __local__swprintf_c_defined 1
/* Dependency: "_vswprintf_c" */
#ifndef ____localdep__vswprintf_c_defined
#define ____localdep__vswprintf_c_defined 1
#if defined(__CRT_HAVE__vswprintf_c)
__CREDIRECT(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vswprintf_c,(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __wchar_count, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vswprintf_c,(__dst,__wchar_count,__format,__args))
#else /* LIBC: _vswprintf_c */
#undef ____localdep__vswprintf_c_defined
#endif /* _vswprintf_c... */
#endif /* !____localdep__vswprintf_c_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_swprintf_c) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_swprintf_c))(__WCHAR_TYPE__ *__dst,
                                                          __SIZE_TYPE__ __wchar_count,
                                                          __WCHAR_TYPE__ const *__format,
                                                          ...) {
#line 1727 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vswprintf_c(__dst, __wchar_count, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE__vswprintf_c) */
#endif /* !__local__swprintf_c_defined */
