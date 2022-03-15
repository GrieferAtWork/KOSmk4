/* HASH CRC-32:0xf42096ac */
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
#ifndef __local__vcwscanf_l_defined
#define __local__vcwscanf_l_defined
#include <__crt.h>
#ifdef __CRT_HAVE___conio_common_vcwscanf
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___conio_common_vcwscanf_defined
#define __local___localdep___conio_common_vcwscanf_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep___conio_common_vcwscanf,(__UINT64_TYPE__ __options, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__conio_common_vcwscanf,(__options,__format,__locale,__args))
#endif /* !__local___localdep___conio_common_vcwscanf_defined */
__NAMESPACE_LOCAL_END
#include <corecrt_stdio_config.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vcwscanf_l) __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vcwscanf_l))(__WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep___conio_common_vcwscanf)(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, __format, __locale, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vcwscanf_l_defined
#define __local___localdep__vcwscanf_l_defined
#define __localdep__vcwscanf_l __LIBC_LOCAL_NAME(_vcwscanf_l)
#endif /* !__local___localdep__vcwscanf_l_defined */
#else /* __CRT_HAVE___conio_common_vcwscanf */
#undef __local__vcwscanf_l_defined
#endif /* !__CRT_HAVE___conio_common_vcwscanf */
#endif /* !__local__vcwscanf_l_defined */
