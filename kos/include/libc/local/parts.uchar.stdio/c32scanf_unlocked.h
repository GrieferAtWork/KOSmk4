/* HASH CRC-32:0x13b416f4 */
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
#ifndef __local_c32scanf_unlocked_defined
#define __local_c32scanf_unlocked_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vwscanf_unlocked) || (defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vwscanf) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc_unlocked) || (defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc_unlocked) || (defined(__CRT_HAVE__getwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_getwc_nolock) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fgetwc_nolock) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc) || (defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc)) && ((defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc_unlocked) || (defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_ungetwc_nolock) || (defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc)))))
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vc32scanf_unlocked_defined
#define __local___localdep_vc32scanf_unlocked_defined
#if defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_C32SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc32scanf_unlocked,(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_KOS$vwscanf_unlocked)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_C32SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc32scanf_unlocked,(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_C32SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc32scanf_unlocked,(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_KOS$vwscanf)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_C32SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vc32scanf_unlocked,(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)))) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwscanf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc32scanf_unlocked __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SIZE_T(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__builtin_va_list),__STDC_INT_AS_SIZE_T(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__builtin_va_list),vwscanf_unlocked)
#elif defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc_unlocked) || (defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc_unlocked) || (defined(__CRT_HAVE__getwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_getwc_nolock) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fgetwc_nolock) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc) || (defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc)) && ((defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc_unlocked) || (defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_ungetwc_nolock) || (defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc))))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vc32scanf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc32scanf_unlocked __LIBC_LOCAL_NAME(vc32scanf_unlocked)
#else /* ... */
#undef __local___localdep_vc32scanf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vc32scanf_unlocked_defined */
__LOCAL_LIBC(c32scanf_unlocked) __ATTR_WUNUSED __ATTR_LIBC_C32SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBKCALL __LIBC_LOCAL_NAME(c32scanf_unlocked))(__CHAR32_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vc32scanf_unlocked)(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32scanf_unlocked_defined
#define __local___localdep_c32scanf_unlocked_defined
#define __localdep_c32scanf_unlocked __LIBC_LOCAL_NAME(c32scanf_unlocked)
#endif /* !__local___localdep_c32scanf_unlocked_defined */
#else /* (__CRT_HAVE_vwscanf_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vwscanf_unlocked || (__CRT_HAVE_vwscanf && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vwscanf || (__LOCAL_stdin && (__CRT_HAVE_vfwscanf_unlocked || __CRT_HAVE_vfwscanf || ((__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE__ungetwc_nolock || __CRT_HAVE_ungetwc))) && __SIZEOF_WCHAR_T__ == 4) || (__LOCAL_stdin && ((__CRT_HAVE_vfwscanf_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vfwscanf_unlocked || (__CRT_HAVE_vfwscanf && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vfwscanf || ((__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE__ungetwc_nolock || __CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4) || (((__CRT_HAVE_fgetwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fgetwc_unlocked || (__CRT_HAVE_getwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$getwc_unlocked || (__CRT_HAVE__getwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_getwc_nolock || (__CRT_HAVE__fgetwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_fgetwc_nolock || (__CRT_HAVE_getwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$getwc || (__CRT_HAVE_fgetwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fgetwc) && ((__CRT_HAVE_ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$ungetwc_unlocked || (__CRT_HAVE__ungetwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_ungetwc_nolock || (__CRT_HAVE_ungetwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$ungetwc)))) */
#undef __local_c32scanf_unlocked_defined
#endif /* (!__CRT_HAVE_vwscanf_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vwscanf_unlocked && (!__CRT_HAVE_vwscanf || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vwscanf && (!__LOCAL_stdin || (!__CRT_HAVE_vfwscanf_unlocked && !__CRT_HAVE_vfwscanf && ((!__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked && !__CRT_HAVE__getwc_nolock && !__CRT_HAVE__fgetwc_nolock && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc) || (!__CRT_HAVE_ungetwc_unlocked && !__CRT_HAVE__ungetwc_nolock && !__CRT_HAVE_ungetwc))) || __SIZEOF_WCHAR_T__ != 4) && (!__LOCAL_stdin || ((!__CRT_HAVE_vfwscanf_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vfwscanf_unlocked && (!__CRT_HAVE_vfwscanf || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vfwscanf && ((!__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked && !__CRT_HAVE__getwc_nolock && !__CRT_HAVE__fgetwc_nolock && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc) || (!__CRT_HAVE_ungetwc_unlocked && !__CRT_HAVE__ungetwc_nolock && !__CRT_HAVE_ungetwc) || __SIZEOF_WCHAR_T__ != 4) && (((!__CRT_HAVE_fgetwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fgetwc_unlocked && (!__CRT_HAVE_getwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$getwc_unlocked && (!__CRT_HAVE__getwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_getwc_nolock && (!__CRT_HAVE__fgetwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_fgetwc_nolock && (!__CRT_HAVE_getwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$getwc && (!__CRT_HAVE_fgetwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fgetwc) || ((!__CRT_HAVE_ungetwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$ungetwc_unlocked && (!__CRT_HAVE__ungetwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_ungetwc_nolock && (!__CRT_HAVE_ungetwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$ungetwc)))) */
#endif /* !__local_c32scanf_unlocked_defined */
