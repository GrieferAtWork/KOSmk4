/* HASH CRC-32:0x6e03d2d4 */
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
#ifndef __local__vsnwprintf_s_l_defined
#define __local__vsnwprintf_s_l_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vsnwprintf_s_defined
#define __local___localdep__vsnwprintf_s_defined
#ifdef __CRT_HAVE__vsnwprintf_s
__CREDIRECT(__ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsnwprintf_s,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vsnwprintf_s,(__buf,__bufsize,__buflen,__format,__args))
#else /* __CRT_HAVE__vsnwprintf_s */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/_vsnwprintf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsnwprintf_s __LIBC_LOCAL_NAME(_vsnwprintf_s)
#endif /* !__CRT_HAVE__vsnwprintf_s */
#endif /* !__local___localdep__vsnwprintf_s_defined */
__LOCAL_LIBC(_vsnwprintf_s_l) __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsnwprintf_s_l))(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep__vsnwprintf_s)(__dst, __wchar_count, __bufsize, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vsnwprintf_s_l_defined
#define __local___localdep__vsnwprintf_s_l_defined
#define __localdep__vsnwprintf_s_l __LIBC_LOCAL_NAME(_vsnwprintf_s_l)
#endif /* !__local___localdep__vsnwprintf_s_l_defined */
#endif /* !__local__vsnwprintf_s_l_defined */
