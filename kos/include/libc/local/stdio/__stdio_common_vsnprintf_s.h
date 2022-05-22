/* HASH CRC-32:0x77bf8f3 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___stdio_common_vsnprintf_s_defined
#define __local___stdio_common_vsnprintf_s_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___stdio_common_vsprintf_defined
#define __local___localdep___stdio_common_vsprintf_defined
#ifdef __CRT_HAVE___stdio_common_vsprintf
__CREDIRECT(__ATTR_ACCESS_RO(4) __ATTR_LIBC_PRINTF(4, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___stdio_common_vsprintf,(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),__stdio_common_vsprintf,(__options,__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE___stdio_common_vsprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/__stdio_common_vsprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___stdio_common_vsprintf __LIBC_LOCAL_NAME(__stdio_common_vsprintf)
#endif /* !__CRT_HAVE___stdio_common_vsprintf */
#endif /* !__local___localdep___stdio_common_vsprintf_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__stdio_common_vsnprintf_s) __ATTR_ACCESS_RO(5) __ATTR_LIBC_PRINTF(5, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__stdio_common_vsnprintf_s))(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __locale_t __locale, __builtin_va_list __args) {
	__hybrid_assert(__bufsize <= __maxsize);
	return (__NAMESPACE_LOCAL_SYM __localdep___stdio_common_vsprintf)(__options, __buf, __bufsize, __format, __locale, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___stdio_common_vsnprintf_s_defined
#define __local___localdep___stdio_common_vsnprintf_s_defined
#define __localdep___stdio_common_vsnprintf_s __LIBC_LOCAL_NAME(__stdio_common_vsnprintf_s)
#endif /* !__local___localdep___stdio_common_vsnprintf_s_defined */
#endif /* !__local___stdio_common_vsnprintf_s_defined */
