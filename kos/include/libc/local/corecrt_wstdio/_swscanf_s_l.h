/* HASH CRC-32:0x57a84b86 */
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
#ifndef __local__swscanf_s_l_defined
#define __local__swscanf_s_l_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vswscanf_s_l_defined
#define __local___localdep__vswscanf_s_l_defined
#ifdef __CRT_HAVE__vswscanf_s_l
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vswscanf_s_l,(__WCHAR_TYPE__ const *__buf, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vswscanf_s_l,(__buf,__format,__locale,__args))
#else /* __CRT_HAVE__vswscanf_s_l */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/_vswscanf_s_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vswscanf_s_l __LIBC_LOCAL_NAME(_vswscanf_s_l)
#endif /* !__CRT_HAVE__vswscanf_s_l */
#endif /* !__local___localdep__vswscanf_s_l_defined */
__LOCAL_LIBC(_swscanf_s_l) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 4) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_swscanf_s_l))(__WCHAR_TYPE__ const *__buf, __WCHAR_TYPE__ const *__format, __locale_t __locale, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = (__NAMESPACE_LOCAL_SYM __localdep__vswscanf_s_l)(__buf, __format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__swscanf_s_l_defined
#define __local___localdep__swscanf_s_l_defined
#define __localdep__swscanf_s_l __LIBC_LOCAL_NAME(_swscanf_s_l)
#endif /* !__local___localdep__swscanf_s_l_defined */
#endif /* !__local__swscanf_s_l_defined */
