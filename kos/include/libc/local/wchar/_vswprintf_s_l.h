/* HASH CRC-32:0xb68f826f */
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
#ifndef __local__vswprintf_s_l_defined
#define __local__vswprintf_s_l_defined 1
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vswprintf from wchar */
#ifndef __local___localdep_vswprintf_defined
#define __local___localdep_vswprintf_defined 1
#ifdef __CRT_HAVE_vswprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vswprintf,(__WCHAR_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#else /* __CRT_HAVE_vswprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vswprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vswprintf __LIBC_LOCAL_NAME(vswprintf)
#endif /* !__CRT_HAVE_vswprintf */
#endif /* !__local___localdep_vswprintf_defined */
__LOCAL_LIBC(_vswprintf_s_l) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vswprintf_s_l))(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __wchar_count, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return __localdep_vswprintf(__dst, __wchar_count, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vswprintf_s_l_defined
#define __local___localdep__vswprintf_s_l_defined 1
#define __localdep__vswprintf_s_l __LIBC_LOCAL_NAME(_vswprintf_s_l)
#endif /* !__local___localdep__vswprintf_s_l_defined */
#endif /* !__local__vswprintf_s_l_defined */
