/* HASH CRC-32:0x554bd15d */
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
#ifndef __local_sc32scanf_defined
#define __local_sc32scanf_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vsc32scanf_defined
#define __local___localdep_vsc32scanf_defined
#if defined(__CRT_HAVE_vswscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_LIBC_C32SCANF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsc32scanf,(__CHAR32_TYPE__ const *__restrict __input, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vswscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE_KOS$vswscanf)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_LIBC_C32SCANF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsc32scanf,(__CHAR32_TYPE__ const *__restrict __input, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vswscanf,(__input,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vswscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsc32scanf __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SIZE_T(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),__STDC_INT_AS_SIZE_T(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),vswscanf)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vsc32scanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsc32scanf __LIBC_LOCAL_NAME(vsc32scanf)
#endif /* !... */
#endif /* !__local___localdep_vsc32scanf_defined */
__LOCAL_LIBC(sc32scanf) __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_LIBC_C32SCANF(2, 3) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBKCALL __LIBC_LOCAL_NAME(sc32scanf))(__CHAR32_TYPE__ const *__restrict __src, __CHAR32_TYPE__ const *__restrict __format, ...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vsc32scanf)(__src, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sc32scanf_defined
#define __local___localdep_sc32scanf_defined
#define __localdep_sc32scanf __LIBC_LOCAL_NAME(sc32scanf)
#endif /* !__local___localdep_sc32scanf_defined */
#endif /* !__local_sc32scanf_defined */
