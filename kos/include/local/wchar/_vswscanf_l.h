/* HASH CRC-32:0xe1438778 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__vswscanf_l_defined
#define __local__vswscanf_l_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vswscanf from wchar */
#ifndef __local___localdep_vswscanf_defined
#define __local___localdep_vswscanf_defined 1
#ifdef __CRT_HAVE_vswscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vswscanf,(__WCHAR_TYPE__ const *__restrict __src, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif defined(__CRT_HAVE_DOS$vswscanf) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vswscanf,(__WCHAR_TYPE__ const *__restrict __src, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif defined(__CRT_HAVE_DOS$vswscanf) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vswscanf,(__WCHAR_TYPE__ const *__restrict __src, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/vswscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vswscanf __LIBC_LOCAL_NAME(vswscanf)
#endif /* !... */
#endif /* !__local___localdep_vswscanf_defined */
__LOCAL_LIBC(_vswscanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vswscanf_l))(__WCHAR_TYPE__ const *__src, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return __localdep_vswscanf(__src, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vswscanf_l_defined
#define __local___localdep__vswscanf_l_defined 1
#define __localdep__vswscanf_l __LIBC_LOCAL_NAME(_vswscanf_l)
#endif /* !__local___localdep__vswscanf_l_defined */
#endif /* !__local__vswscanf_l_defined */
