/* HASH CRC-32:0x60fe4965 */
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
#ifndef __local__snwprintf_s_defined
#define __local__snwprintf_s_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _vsnwprintf_s from wchar */
#ifndef __local___localdep__vsnwprintf_s_defined
#define __local___localdep__vsnwprintf_s_defined 1
#ifdef __CRT_HAVE__vsnwprintf_s
__CREDIRECT(__ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsnwprintf_s,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vsnwprintf_s,(__buf,__bufsize,__buflen,__format,__args))
#elif defined(__CRT_HAVE_DOS$_vsnwprintf_s) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsnwprintf_s,(__CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__format, __builtin_va_list __args),_vsnwprintf_s,(__buf,__bufsize,__buflen,__format,__args))
#elif defined(__CRT_HAVE_DOS$_vsnwprintf_s) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsnwprintf_s,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, __CHAR16_TYPE__ const *__format, __builtin_va_list __args),_vsnwprintf_s,(__buf,__bufsize,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/_vsnwprintf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsnwprintf_s __LIBC_LOCAL_NAME(_vsnwprintf_s)
#endif /* !... */
#endif /* !__local___localdep__vsnwprintf_s_defined */
__LOCAL_LIBC(_snwprintf_s) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_snwprintf_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vsnwprintf_s(__buf, __bufsize, __buflen, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__snwprintf_s_defined
#define __local___localdep__snwprintf_s_defined 1
#define __localdep__snwprintf_s __LIBC_LOCAL_NAME(_snwprintf_s)
#endif /* !__local___localdep__snwprintf_s_defined */
#endif /* !__local__snwprintf_s_defined */
