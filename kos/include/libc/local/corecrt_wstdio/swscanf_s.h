/* HASH CRC-32:0xe451b4b1 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_swscanf_s_defined
#define __local_swscanf_s_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vswscanf_s_defined
#define __local___localdep_vswscanf_s_defined
#ifdef __CRT_HAVE_vswscanf_s
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vswscanf_s,(__WCHAR_TYPE__ const *__buf, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),vswscanf_s,(__buf,__format,__args))
#else /* __CRT_HAVE_vswscanf_s */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/vswscanf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vswscanf_s __LIBC_LOCAL_NAME(vswscanf_s)
#endif /* !__CRT_HAVE_vswscanf_s */
#endif /* !__local___localdep_vswscanf_s_defined */
__LOCAL_LIBC(swscanf_s) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(swscanf_s))(__WCHAR_TYPE__ const *__buf, __WCHAR_TYPE__ const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vswscanf_s)(__buf, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_swscanf_s_defined
#define __local___localdep_swscanf_s_defined
#define __localdep_swscanf_s __LIBC_LOCAL_NAME(swscanf_s)
#endif /* !__local___localdep_swscanf_s_defined */
#endif /* !__local_swscanf_s_defined */
