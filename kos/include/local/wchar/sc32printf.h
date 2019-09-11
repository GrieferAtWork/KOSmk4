/* HASH 0xe6af200b */
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
#ifndef __local_sc32printf_defined
#if 1
#define __local_sc32printf_defined 1
/* Dependency: "vswprintf" from "wchar" */
#ifndef ____localdep_vsc32printf_defined
#define ____localdep_vsc32printf_defined 1
#if defined(__CRT_HAVE_vswprintf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsc32printf,(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vswprintf.h>
#define __localdep_vsc32printf(buf, buflen, format, args) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))((__WCHAR_TYPE__ *)(buf), buflen, (__WCHAR_TYPE__ const *)(format), args)
#else /* LIBC: vsc32printf */
#include <local/wchar/vsc32printf.h>
#define __localdep_vsc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc32printf))
#endif /* vsc32printf... */
#endif /* !____localdep_vsc32printf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sc32printf) __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(sc32printf))(__CHAR32_TYPE__ *__restrict __buf,
                                                         __SIZE_TYPE__ __buflen,
                                                         __CHAR32_TYPE__ const *__restrict __format,
                                                         ...) {
#line 591 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vsc32printf(__buf, __buflen, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local_sc32printf_defined */
