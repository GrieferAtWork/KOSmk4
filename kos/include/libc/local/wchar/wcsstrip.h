/* HASH CRC-32:0xc99d0ca */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcsstrip_defined
#define __local_wcsstrip_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcslstrip_defined
#define __local___localdep_wcslstrip_defined
#ifdef __CRT_HAVE_wcslstrip
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcslstrip,(__WCHAR_TYPE__ const *__str),wcslstrip,(__str))
#else /* __CRT_HAVE_wcslstrip */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcslstrip __LIBC_LOCAL_NAME(wcslstrip)
#endif /* !__CRT_HAVE_wcslstrip */
#endif /* !__local___localdep_wcslstrip_defined */
#ifndef __local___localdep_wcsrstrip_defined
#define __local___localdep_wcsrstrip_defined
#ifdef __CRT_HAVE_wcsrstrip
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsrstrip,(__WCHAR_TYPE__ *__str),wcsrstrip,(__str))
#else /* __CRT_HAVE_wcsrstrip */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsrstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsrstrip __LIBC_LOCAL_NAME(wcsrstrip)
#endif /* !__CRT_HAVE_wcsrstrip */
#endif /* !__local___localdep_wcsrstrip_defined */
__LOCAL_LIBC(wcsstrip) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsstrip))(__WCHAR_TYPE__ *__str) {
	__str = (__NAMESPACE_LOCAL_SYM __localdep_wcslstrip)(__str);
	__str = (__NAMESPACE_LOCAL_SYM __localdep_wcsrstrip)(__str);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsstrip_defined
#define __local___localdep_wcsstrip_defined
#define __localdep_wcsstrip __LIBC_LOCAL_NAME(wcsstrip)
#endif /* !__local___localdep_wcsstrip_defined */
#endif /* !__local_wcsstrip_defined */
