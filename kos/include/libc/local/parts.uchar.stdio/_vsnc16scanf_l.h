/* HASH CRC-32:0x9f3fd613 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__vsnc16scanf_l_defined
#define __local__vsnc16scanf_l_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___stdio_common_vsc16scanf_defined
#define __local___localdep___stdio_common_vsc16scanf_defined
#if defined(__CRT_HAVE___stdio_common_vswscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(4) __ATTR_INS(2, 3) __ATTR_LIBC_C16SCANF(4, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___stdio_common_vsc16scanf,(__UINT64_TYPE__ __options, __CHAR16_TYPE__ const *__buf, __SIZE_TYPE__ __bufsize, __CHAR16_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__stdio_common_vswscanf,(__options,__buf,__bufsize,__format,__locale,__args))
#elif defined(__CRT_HAVE_DOS$__stdio_common_vswscanf)
__CREDIRECT_DOS(__ATTR_IN(4) __ATTR_INS(2, 3) __ATTR_LIBC_C16SCANF(4, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___stdio_common_vsc16scanf,(__UINT64_TYPE__ __options, __CHAR16_TYPE__ const *__buf, __SIZE_TYPE__ __bufsize, __CHAR16_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__stdio_common_vswscanf,(__options,__buf,__bufsize,__format,__locale,__args))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/__stdio_common_vswscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___stdio_common_vsc16scanf __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SSIZE_T(__LIBDCALL*)(__UINT64_TYPE__,__CHAR16_TYPE__ const *,__SIZE_TYPE__,__CHAR16_TYPE__ const *,__locale_t,__builtin_va_list),__STDC_INT_AS_SSIZE_T(__LIBDCALL&)(__UINT64_TYPE__,__CHAR16_TYPE__ const *,__SIZE_TYPE__,__CHAR16_TYPE__ const *,__locale_t,__builtin_va_list),__stdio_common_vswscanf)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/__stdio_common_vsc16scanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___stdio_common_vsc16scanf __LIBC_LOCAL_NAME(__stdio_common_vsc16scanf)
#endif /* !... */
#endif /* !__local___localdep___stdio_common_vsc16scanf_defined */
__NAMESPACE_LOCAL_END
#include <corecrt_stdio_config.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vsnc16scanf_l) __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INS(1, 2) __ATTR_LIBC_C16SCANF(3, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_vsnc16scanf_l))(__CHAR16_TYPE__ const *__buf, __SIZE_TYPE__ __bufsize, __CHAR16_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep___stdio_common_vsc16scanf)(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, __buf, __bufsize, __format, __locale, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vsnc16scanf_l_defined
#define __local___localdep__vsnc16scanf_l_defined
#define __localdep__vsnc16scanf_l __LIBC_LOCAL_NAME(_vsnc16scanf_l)
#endif /* !__local___localdep__vsnc16scanf_l_defined */
#endif /* !__local__vsnc16scanf_l_defined */
