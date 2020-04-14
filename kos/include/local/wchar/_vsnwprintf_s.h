/* HASH CRC-32:0x7c272dd3 */
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
#ifndef __local__vsnwprintf_s_defined
#define __local__vsnwprintf_s_defined 1
/* Dependency: "vswprintf" from "wchar" */
#ifndef ____localdep_vswprintf_defined
#define ____localdep_vswprintf_defined 1
#ifdef __std___localdep_vswprintf_defined
__NAMESPACE_STD_USING(__localdep_vswprintf)
#elif defined(__CRT_HAVE_vswprintf)
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vswprintf,(__WCHAR_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#else /* LIBC: vswprintf */
#include <local/wchar/vswprintf.h>
#define __localdep_vswprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))
#endif /* vswprintf... */
#endif /* !____localdep_vswprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vsnwprintf_s) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsnwprintf_s))(__WCHAR_TYPE__ *__buf,
                                                           __SIZE_TYPE__ __bufsize,
                                                           __SIZE_TYPE__ __buflen,
                                                           __WCHAR_TYPE__ const *__format,
                                                           __builtin_va_list __args) {
#line 1888 "kos/src/libc/magic/wchar.c"
	(void)__buflen;
	return __localdep_vswprintf(__buf, __bufsize, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__vsnwprintf_s_defined */
