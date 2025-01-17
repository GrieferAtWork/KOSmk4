/* HASH CRC-32:0x98b7fb47 */
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
#ifndef __local___stdio_common_vsc16printf_p_defined
#define __local___stdio_common_vsc16printf_p_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vsc16printf_defined
#define __local___localdep_vsc16printf_defined
#if defined(__CRT_HAVE_vswprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsc16printf,(__CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE_DOS$vswprintf)
__CREDIRECT_DOS(__ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsc16printf,(__CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vswprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsc16printf __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SIZE_T(__LIBDCALL*)(__CHAR16_TYPE__ *__restrict,__SIZE_TYPE__,__CHAR16_TYPE__ const *__restrict,__builtin_va_list),__STDC_INT_AS_SIZE_T(__LIBDCALL&)(__CHAR16_TYPE__ *__restrict,__SIZE_TYPE__,__CHAR16_TYPE__ const *__restrict,__builtin_va_list),vswprintf)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vsc16printf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsc16printf __LIBC_LOCAL_NAME(vsc16printf)
#endif /* !... */
#endif /* !__local___localdep_vsc16printf_defined */
__LOCAL_LIBC(__stdio_common_vsc16printf_p) __ATTR_IN(4) __ATTR_LIBC_C16PRINTF_P(4, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(__stdio_common_vsc16printf_p))(__UINT64_TYPE__ __options, __CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __CHAR16_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	__STDC_INT_AS_SSIZE_T __result;
	(void)__locale;
	/* NOTE: DOS positional arguments work the same as Glibc's, only that
	 *       Glibc and KOS already bake  them into the normal  `wprintf'. */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vsc16printf)(__buf, __bufsize, __format, __args);
	if (!(__options & 2) && (__SIZE_TYPE__)__result > __bufsize)
		__result = __bufsize;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___stdio_common_vsc16printf_p_defined
#define __local___localdep___stdio_common_vsc16printf_p_defined
#define __localdep___stdio_common_vsc16printf_p __LIBC_LOCAL_NAME(__stdio_common_vsc16printf_p)
#endif /* !__local___localdep___stdio_common_vsc16printf_p_defined */
#endif /* !__local___stdio_common_vsc16printf_p_defined */
