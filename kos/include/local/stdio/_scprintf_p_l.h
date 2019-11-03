/* HASH CRC-32:0x150aa5d2 */
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
#ifndef __local__scprintf_p_l_defined
#if 1
#define __local__scprintf_p_l_defined 1
/* Dependency: "_vscprintf_p_l" from "stdio" */
#ifndef ____localdep__vscprintf_p_l_defined
#define ____localdep__vscprintf_p_l_defined 1
#if defined(__CRT_HAVE__vscprintf_p_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_PRINTF_P(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vscprintf_p_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vscprintf_p_l,(__format,__locale,__args))
#else /* LIBC: _vscprintf_p_l */
#include <local/stdio/_vscprintf_p_l.h>
#define __localdep__vscprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf_p_l))
#endif /* _vscprintf_p_l... */
#endif /* !____localdep__vscprintf_p_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_scprintf_p_l) __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_PRINTF_P(1, 3) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_scprintf_p_l))(char const *__restrict __format,
                                                            __locale_t __locale,
                                                            ...) {
#line 2383 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vscprintf_p_l(__format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local__scprintf_p_l_defined */
