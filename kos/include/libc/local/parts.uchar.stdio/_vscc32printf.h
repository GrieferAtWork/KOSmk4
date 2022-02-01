/* HASH CRC-32:0xdf5e7741 */
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
#ifndef __local__vscc32printf_defined
#define __local__vscc32printf_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vscc32printf_l_defined
#define __local___localdep__vscc32printf_l_defined
#if defined(__CRT_HAVE__vscwprintf_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LIBC_C32PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vscc32printf_l,(__CHAR32_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vscwprintf_l,(__format,__locale,__args))
#elif defined(__CRT_HAVE_KOS$_vscwprintf_l)
__CREDIRECT_KOS(__ATTR_LIBC_C32PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vscc32printf_l,(__CHAR32_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vscwprintf_l,(__format,__locale,__args))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/_vscwprintf_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vscc32printf_l __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SSIZE_T(__LIBKCALL*)(__CHAR32_TYPE__ const *,__locale_t,__builtin_va_list),__STDC_INT_AS_SSIZE_T(__LIBKCALL&)(__CHAR32_TYPE__ const *,__locale_t,__builtin_va_list),_vscwprintf_l)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/_vscc32printf_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vscc32printf_l __LIBC_LOCAL_NAME(_vscc32printf_l)
#endif /* !... */
#endif /* !__local___localdep__vscc32printf_l_defined */
__LOCAL_LIBC(_vscc32printf) __ATTR_LIBC_C32PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(_vscc32printf))(__CHAR32_TYPE__ const *__format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep__vscc32printf_l)(__format, __NULLPTR, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vscc32printf_defined
#define __local___localdep__vscc32printf_defined
#define __localdep__vscc32printf __LIBC_LOCAL_NAME(_vscc32printf)
#endif /* !__local___localdep__vscc32printf_defined */
#endif /* !__local__vscc32printf_defined */
