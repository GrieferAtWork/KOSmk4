/* HASH CRC-32:0x6452aed */
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
#ifndef __local_vc32scanf_defined
#define __local_vc32scanf_defined 1
#include <__crt.h>
#if ((defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <features.h>
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vfc32scanf from parts.uchar.stdio */
#ifndef __local___localdep_vfc32scanf_defined
#define __local___localdep_vfc32scanf_defined 1
#if defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc32scanf,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwscanf)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc32scanf,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#else /* ... */
#undef __local___localdep_vfc32scanf_defined
#endif /* !... */
#endif /* !__local___localdep_vfc32scanf_defined */
__NAMESPACE_LOCAL_END
#include <local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vc32scanf) __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__LIBKCALL __LIBC_LOCAL_NAME(vc32scanf))(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
	return __localdep_vfc32scanf(__LOCAL_stdin, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vc32scanf_defined
#define __local___localdep_vc32scanf_defined 1
#define __localdep_vc32scanf __LIBC_LOCAL_NAME(vc32scanf)
#endif /* !__local___localdep_vc32scanf_defined */
#else /* ((__CRT_HAVE_vfwscanf && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vfwscanf) && !__NO_STDSTREAMS */
#undef __local_vc32scanf_defined
#endif /* ((!__CRT_HAVE_vfwscanf || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vfwscanf) || __NO_STDSTREAMS */
#endif /* !__local_vc32scanf_defined */
