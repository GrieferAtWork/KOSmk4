/* HASH CRC-32:0x5cb2ddec */
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
#ifndef __local__swscanf_l_defined
#define __local__swscanf_l_defined 1
/* Dependency: "_vswscanf_l" from "wchar" */
#ifndef ____localdep__vswscanf_l_defined
#define ____localdep__vswscanf_l_defined 1
#ifdef __CRT_HAVE__vswscanf_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vswscanf_l,(__WCHAR_TYPE__ const *__src, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vswscanf_l,(__src,__format,__locale,__args))
#else /* LIBC: _vswscanf_l */
#include <local/wchar/_vswscanf_l.h>
#define __localdep__vswscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswscanf_l))
#endif /* _vswscanf_l... */
#endif /* !____localdep__vswscanf_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_swscanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_swscanf_l))(__WCHAR_TYPE__ const *__src,
                                                         __WCHAR_TYPE__ const *__format,
                                                         __locale_t __locale,
                                                         ...) {
#line 2125 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vswscanf_l(__src, __format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__swscanf_l_defined */
