/* HASH 0x45f27e05 */
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
#ifndef __local__vsprintf_p_l_defined
#define __local__vsprintf_p_l_defined 1
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
__LOCAL_LIBC(_vsprintf_p_l) __ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsprintf_p_l))(char *__restrict __buf,
                                                           __SIZE_TYPE__ __bufsize,
                                                           char const *__restrict __format,
                                                           __locale_t __locale,
                                                           __builtin_va_list __args) {
#line 2202 "kos/src/libc/magic/stdio.c"
	(void)__locale;
	return __localdep__vsprintf_p(__buf, __bufsize, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__vsprintf_p_l_defined */
