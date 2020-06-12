/* HASH CRC-32:0xa4cb975f */
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
#ifndef __local__vwprintf_p_defined
#define __local__vwprintf_p_defined 1
#include <__crt.h>
#ifndef __NO_STDSTREAMS
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _vfwprintf_p from wchar */
#ifndef __local___localdep__vfwprintf_p_defined
#define __local___localdep__vfwprintf_p_defined 1
#ifdef __CRT_HAVE__vfwprintf_p
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep__vfwprintf_p,(__FILE *__stream, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vfwprintf_p,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$_vfwprintf_p) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep__vfwprintf_p,(__FILE *__stream, __CHAR32_TYPE__ const *__format, __builtin_va_list __args),_vfwprintf_p,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$_vfwprintf_p) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep__vfwprintf_p,(__FILE *__stream, __CHAR16_TYPE__ const *__format, __builtin_va_list __args),_vfwprintf_p,(__stream,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/_vfwprintf_p.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vfwprintf_p __LIBC_LOCAL_NAME(_vfwprintf_p)
#endif /* !... */
#endif /* !__local___localdep__vfwprintf_p_defined */
__NAMESPACE_LOCAL_END
#include <local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vwprintf_p) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vwprintf_p))(__WCHAR_TYPE__ const *__format, __builtin_va_list __args) __THROWS(...) {
	return __localdep__vfwprintf_p(__LOCAL_stdout, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vwprintf_p_defined
#define __local___localdep__vwprintf_p_defined 1
#define __localdep__vwprintf_p __LIBC_LOCAL_NAME(_vwprintf_p)
#endif /* !__local___localdep__vwprintf_p_defined */
#else /* !__NO_STDSTREAMS */
#undef __local__vwprintf_p_defined
#endif /* __NO_STDSTREAMS */
#endif /* !__local__vwprintf_p_defined */
