/* HASH CRC-32:0xfade44ad */
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
#ifndef __local__vsnprintf_s_defined
#define __local__vsnprintf_s_defined 1
/* Dependency: "_vsnprintf" from "stdio" */
#ifndef ____localdep__vsnprintf_defined
#define ____localdep__vsnprintf_defined 1
#ifdef __CRT_HAVE__vsnprintf
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__CREDIRECT(__ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args),_vsnprintf,(__buf,__bufsize,__format,__args))
#else /* LIBC: _vsnprintf */
#include <local/stdio/_vsnprintf.h>
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
#define __localdep__vsnprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf))
#endif /* _vsnprintf... */
#endif /* !____localdep__vsnprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vsnprintf_s) __ATTR_NONNULL((4)) __ATTR_LIBC_PRINTF(4, 0) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsnprintf_s))(char *__restrict __buf,
                                                          __SIZE_TYPE__ __bufsize,
                                                          __SIZE_TYPE__ __buflen,
                                                          char const *__restrict __format,
                                                          __builtin_va_list __args) {
#line 2414 "kos/src/libc/magic/stdio.c"
	(void)__buflen;
	return __localdep__vsnprintf(__buf, __bufsize, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__vsnprintf_s_defined */
