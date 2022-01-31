/* HASH CRC-32:0x96bb9b8e */
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
#ifndef __local__vc16scanf_l_defined
#define __local__vc16scanf_l_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwscanf) || (defined(__LOCAL_stdin) && defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2) || (defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vc16scanf_defined
#define __local___localdep_vc16scanf_defined
#if defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc16scanf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwscanf)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc16scanf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__LOCAL_stdin) && defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16scanf __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SIZE_T(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__builtin_va_list),__STDC_INT_AS_SIZE_T(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__builtin_va_list),vwscanf)
#elif defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vc16scanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16scanf __LIBC_LOCAL_NAME(vc16scanf)
#else /* ... */
#undef __local___localdep_vc16scanf_defined
#endif /* !... */
#endif /* !__local___localdep_vc16scanf_defined */
__LOCAL_LIBC(_vc16scanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_vc16scanf_l))(__CHAR16_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_vc16scanf)(__format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vc16scanf_l_defined
#define __local___localdep__vc16scanf_l_defined
#define __localdep__vc16scanf_l __LIBC_LOCAL_NAME(_vc16scanf_l)
#endif /* !__local___localdep__vc16scanf_l_defined */
#else /* (__CRT_HAVE_vwscanf && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vwscanf || (__LOCAL_stdin && __CRT_HAVE_vfwscanf && __SIZEOF_WCHAR_T__ == 2) || (__LOCAL_stdin && ((__CRT_HAVE_vfwscanf && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vfwscanf)) */
#undef __local__vc16scanf_l_defined
#endif /* (!__CRT_HAVE_vwscanf || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vwscanf && (!__LOCAL_stdin || !__CRT_HAVE_vfwscanf || __SIZEOF_WCHAR_T__ != 2) && (!__LOCAL_stdin || ((!__CRT_HAVE_vfwscanf || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vfwscanf)) */
#endif /* !__local__vc16scanf_l_defined */
