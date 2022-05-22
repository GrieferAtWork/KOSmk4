/* HASH CRC-32:0xda6bb3a7 */
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
#ifndef __local__vsnc32printf_s_l_defined
#define __local__vsnc32printf_s_l_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___stdio_common_vsnc32printf_s_defined
#define __local___localdep___stdio_common_vsnc32printf_s_defined
#if defined(__CRT_HAVE___stdio_common_vsnwprintf_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN(5) __ATTR_LIBC_C32PRINTF(5, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___stdio_common_vsnc32printf_s,(__UINT64_TYPE__ __options, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, __CHAR32_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__stdio_common_vsnwprintf_s,(__options,__buf,__bufsize,__maxsize,__format,__locale,__args))
#elif defined(__CRT_HAVE_KOS$__stdio_common_vsnwprintf_s)
__CREDIRECT_KOS(__ATTR_IN(5) __ATTR_LIBC_C32PRINTF(5, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___stdio_common_vsnc32printf_s,(__UINT64_TYPE__ __options, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, __CHAR32_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__stdio_common_vsnwprintf_s,(__options,__buf,__bufsize,__maxsize,__format,__locale,__args))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/__stdio_common_vsnwprintf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___stdio_common_vsnc32printf_s __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SSIZE_T(__LIBKCALL*)(__UINT64_TYPE__,__CHAR32_TYPE__ *,__SIZE_TYPE__,__SIZE_TYPE__,__CHAR32_TYPE__ const *,__locale_t,__builtin_va_list),__STDC_INT_AS_SSIZE_T(__LIBKCALL&)(__UINT64_TYPE__,__CHAR32_TYPE__ *,__SIZE_TYPE__,__SIZE_TYPE__,__CHAR32_TYPE__ const *,__locale_t,__builtin_va_list),__stdio_common_vsnwprintf_s)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/__stdio_common_vsnc32printf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___stdio_common_vsnc32printf_s __LIBC_LOCAL_NAME(__stdio_common_vsnc32printf_s)
#endif /* !... */
#endif /* !__local___localdep___stdio_common_vsnc32printf_s_defined */
__NAMESPACE_LOCAL_END
#include <corecrt_stdio_config.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vsnc32printf_s_l) __ATTR_IN(4) __ATTR_LIBC_C32PRINTF(4, 0) __ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(_vsnc32printf_s_l))(__CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, __CHAR32_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	int __result = (__NAMESPACE_LOCAL_SYM __localdep___stdio_common_vsnc32printf_s)(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, __buf, __bufsize, __maxsize, __format, __locale, __args);
	return __result < 0 ? -1 : __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vsnc32printf_s_l_defined
#define __local___localdep__vsnc32printf_s_l_defined
#define __localdep__vsnc32printf_s_l __LIBC_LOCAL_NAME(_vsnc32printf_s_l)
#endif /* !__local___localdep__vsnc32printf_s_l_defined */
#endif /* !__local__vsnc32printf_s_l_defined */
