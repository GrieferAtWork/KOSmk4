/* HASH CRC-32:0xf6129721 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16scanf_unlocked_defined
#define __local_c16scanf_unlocked_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwscanf_unlocked) || ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)) && !defined(__NO_STDSTREAMS))
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vc16scanf_unlocked from parts.uchar.stdio */
#ifndef __local___localdep_vc16scanf_unlocked_defined
#define __local___localdep_vc16scanf_unlocked_defined 1
#if defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc16scanf_unlocked,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwscanf_unlocked)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc16scanf_unlocked,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwscanf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16scanf_unlocked (*(__STDC_INT_AS_SIZE_T(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __builtin_va_list))&__LIBC_LOCAL_NAME(vwscanf_unlocked))
#elif ((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)) && !defined(__NO_STDSTREAMS)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vc16scanf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16scanf_unlocked __LIBC_LOCAL_NAME(vc16scanf_unlocked)
#else /* ... */
#undef __local___localdep_vc16scanf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vc16scanf_unlocked_defined */
__LOCAL_LIBC(c16scanf_unlocked) __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBDCALL __LIBC_LOCAL_NAME(c16scanf_unlocked))(__CHAR16_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vc16scanf_unlocked(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16scanf_unlocked_defined
#define __local___localdep_c16scanf_unlocked_defined 1
#define __localdep_c16scanf_unlocked __LIBC_LOCAL_NAME(c16scanf_unlocked)
#endif /* !__local___localdep_c16scanf_unlocked_defined */
#else /* (__CRT_HAVE_vwscanf_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vwscanf_unlocked || ((__CRT_HAVE_vfwscanf_unlocked || __CRT_HAVE_vfwscanf) && !__NO_STDSTREAMS && __SIZEOF_WCHAR_T__ == 2) || (((__CRT_HAVE_vfwscanf_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vfwscanf_unlocked || (__CRT_HAVE_vfwscanf && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vfwscanf) && !__NO_STDSTREAMS) */
#undef __local_c16scanf_unlocked_defined
#endif /* (!__CRT_HAVE_vwscanf_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vwscanf_unlocked && ((!__CRT_HAVE_vfwscanf_unlocked && !__CRT_HAVE_vfwscanf) || __NO_STDSTREAMS || __SIZEOF_WCHAR_T__ != 2) && (((!__CRT_HAVE_vfwscanf_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vfwscanf_unlocked && (!__CRT_HAVE_vfwscanf || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vfwscanf) || __NO_STDSTREAMS) */
#endif /* !__local_c16scanf_unlocked_defined */
