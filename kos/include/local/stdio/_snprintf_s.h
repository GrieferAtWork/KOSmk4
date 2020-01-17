/* HASH CRC-32:0xbc35d6b2 */
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
#ifndef __local__snprintf_s_defined
#if 1
#define __local__snprintf_s_defined 1
/* Dependency: "_vsnprintf_s" from "stdio" */
#ifndef ____localdep__vsnprintf_s_defined
#define ____localdep__vsnprintf_s_defined 1
#ifdef __CRT_HAVE__vsnprintf_s
__CREDIRECT(__ATTR_NONNULL((4)) __ATTR_LIBC_PRINTF(4, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnprintf_s,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),_vsnprintf_s,(__buf,__bufsize,__buflen,__format,__args))
#else /* LIBC: _vsnprintf_s */
#include <local/stdio/_vsnprintf_s.h>
#define __localdep__vsnprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_s))
#endif /* _vsnprintf_s... */
#endif /* !____localdep__vsnprintf_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_snprintf_s) __ATTR_NONNULL((4)) __ATTR_LIBC_PRINTF(4, 5) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_snprintf_s))(char *__restrict __buf,
                                                          __SIZE_TYPE__ __bufsize,
                                                          __SIZE_TYPE__ __buflen,
                                                          char const *__restrict __format,
                                                          ...) {
#line 2527 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vsnprintf_s(__buf, __bufsize, __buflen, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local__snprintf_s_defined */
