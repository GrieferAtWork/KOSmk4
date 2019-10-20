/* HASH CRC-32:0xd43ca2f3 */
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
#ifndef __local__sprintf_p_defined
#if 1
#define __local__sprintf_p_defined 1
/* Dependency: "_vsprintf_p" from "stdio" */
#ifndef ____localdep__vsprintf_p_defined
#define ____localdep__vsprintf_p_defined 1
#if defined(__CRT_HAVE__vsprintf_p)
__CREDIRECT(__ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsprintf_p,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args),_vsprintf_p,(__buf,__bufsize,__format,__args))
#else /* LIBC: _vsprintf_p */
#include <local/stdio/_vsprintf_p.h>
#define __localdep__vsprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_p))
#endif /* _vsprintf_p... */
#endif /* !____localdep__vsprintf_p_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_sprintf_p) __ATTR_LIBC_PRINTF_P(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_sprintf_p))(char *__restrict __buf,
                                                         __SIZE_TYPE__ __bufsize,
                                                         char const *__restrict __format,
                                                         ...) {
#line 2216 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vsprintf_p(__buf, __bufsize, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local__sprintf_p_defined */
