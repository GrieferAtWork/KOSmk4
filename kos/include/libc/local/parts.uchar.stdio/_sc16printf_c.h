/* HASH CRC-32:0x3b688ca6 */
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
#ifndef __local__sc16printf_c_defined
#define __local__sc16printf_c_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vsc16printf_c_defined
#define __local___localdep__vsc16printf_c_defined
#if defined(__CRT_HAVE__vswprintf_c) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsc16printf_c,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __CHAR16_TYPE__ const *__format, __builtin_va_list __args),_vswprintf_c,(__buf,__bufsize,__format,__args))
#elif defined(__CRT_HAVE_DOS$_vswprintf_c)
__CREDIRECT_DOS(__ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsc16printf_c,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __CHAR16_TYPE__ const *__format, __builtin_va_list __args),_vswprintf_c,(__buf,__bufsize,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/_vswprintf_c.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsc16printf_c __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SSIZE_T(__LIBDCALL*)(__CHAR16_TYPE__ *,__SIZE_TYPE__,__CHAR16_TYPE__ const *,__builtin_va_list),__STDC_INT_AS_SSIZE_T(__LIBDCALL&)(__CHAR16_TYPE__ *,__SIZE_TYPE__,__CHAR16_TYPE__ const *,__builtin_va_list),_vswprintf_c)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/_vsc16printf_c.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsc16printf_c __LIBC_LOCAL_NAME(_vsc16printf_c)
#endif /* !... */
#endif /* !__local___localdep__vsc16printf_c_defined */
__LOCAL_LIBC(_sc16printf_c) __ATTR_LIBC_C16PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBDCALL __LIBC_LOCAL_NAME(_sc16printf_c))(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __CHAR16_TYPE__ const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep__vsc16printf_c)(__buf, __bufsize, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__sc16printf_c_defined
#define __local___localdep__sc16printf_c_defined
#define __localdep__sc16printf_c __LIBC_LOCAL_NAME(_sc16printf_c)
#endif /* !__local___localdep__sc16printf_c_defined */
#endif /* !__local__sc16printf_c_defined */
