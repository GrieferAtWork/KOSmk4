/* HASH CRC-32:0x31604ec2 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sc32printf_defined
#define __local_sc32printf_defined 1
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vsc32printf from parts.uchar.stdio */
#ifndef __local___localdep_vsc32printf_defined
#define __local___localdep_vsc32printf_defined 1
#if defined(__CRT_HAVE_vswprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsc32printf,(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE_KOS$vswprintf)
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsc32printf,(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vswprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsc32printf (*(__STDC_INT_AS_SIZE_T(__LIBKCALL *)(__CHAR32_TYPE__ *__restrict, __SIZE_TYPE__, __CHAR32_TYPE__ const *__restrict, __builtin_va_list))&__LIBC_LOCAL_NAME(vswprintf))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vsc32printf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsc32printf __LIBC_LOCAL_NAME(vsc32printf)
#endif /* !... */
#endif /* !__local___localdep_vsc32printf_defined */
__LOCAL_LIBC(sc32printf) __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBKCALL __LIBC_LOCAL_NAME(sc32printf))(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__restrict __format, ...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vsc32printf(__buf, __buflen, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sc32printf_defined
#define __local___localdep_sc32printf_defined 1
#define __localdep_sc32printf __LIBC_LOCAL_NAME(sc32printf)
#endif /* !__local___localdep_sc32printf_defined */
#endif /* !__local_sc32printf_defined */
