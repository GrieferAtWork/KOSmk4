/* HASH CRC-32:0x8a9d3f11 */
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
#ifndef __local_c16strip_defined
#define __local_c16strip_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16lstrip_defined
#define __local___localdep_c16lstrip_defined
#if defined(__CRT_HAVE_wcslstrip) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16lstrip,(__CHAR16_TYPE__ const *__str),wcslstrip,(__str))
#elif defined(__CRT_HAVE_DOS$wcslstrip)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16lstrip,(__CHAR16_TYPE__ const *__str),wcslstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16lstrip __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(__CHAR16_TYPE__ const *),__CHAR16_TYPE__ *(__LIBDCALL&)(__CHAR16_TYPE__ const *),wcslstrip)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16lstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16lstrip __LIBC_LOCAL_NAME(c16lstrip)
#endif /* !... */
#endif /* !__local___localdep_c16lstrip_defined */
#ifndef __local___localdep_c16rstrip_defined
#define __local___localdep_c16rstrip_defined
#if defined(__CRT_HAVE_wcsrstrip) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16rstrip,(__CHAR16_TYPE__ *__str),wcsrstrip,(__str))
#elif defined(__CRT_HAVE_DOS$wcsrstrip)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16rstrip,(__CHAR16_TYPE__ *__str),wcsrstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsrstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16rstrip __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(__CHAR16_TYPE__ *),__CHAR16_TYPE__ *(__LIBDCALL&)(__CHAR16_TYPE__ *),wcsrstrip)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16rstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16rstrip __LIBC_LOCAL_NAME(c16rstrip)
#endif /* !... */
#endif /* !__local___localdep_c16rstrip_defined */
__LOCAL_LIBC(c16strip) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16strip))(__CHAR16_TYPE__ *__str) {
	__str = (__NAMESPACE_LOCAL_SYM __localdep_c16lstrip)(__str);
	__str = (__NAMESPACE_LOCAL_SYM __localdep_c16rstrip)(__str);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16strip_defined
#define __local___localdep_c16strip_defined
#define __localdep_c16strip __LIBC_LOCAL_NAME(c16strip)
#endif /* !__local___localdep_c16strip_defined */
#endif /* !__local_c16strip_defined */
