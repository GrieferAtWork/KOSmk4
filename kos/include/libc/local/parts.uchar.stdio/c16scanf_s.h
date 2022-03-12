/* HASH CRC-32:0x6ad7301d */
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
#ifndef __local_c16scanf_s_defined
#define __local_c16scanf_s_defined
#include <__crt.h>
#include <features.h>
#if (defined(__CRT_HAVE_vwscanf_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwscanf_s) || (defined(__CRT_HAVE__vfwscanf_s_l) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_vfwscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vc16scanf_s_defined
#define __local___localdep_vc16scanf_s_defined
#if defined(__CRT_HAVE_vwscanf_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_C16SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vc16scanf_s,(__CHAR16_TYPE__ const *__format, __builtin_va_list __args),vwscanf_s,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwscanf_s)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_C16SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vc16scanf_s,(__CHAR16_TYPE__ const *__format, __builtin_va_list __args),vwscanf_s,(__format,__args))
#elif (defined(__CRT_HAVE__vfwscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/vwscanf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16scanf_s __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SSIZE_T(__LIBDCALL*)(__CHAR16_TYPE__ const *,__builtin_va_list),__STDC_INT_AS_SSIZE_T(__LIBDCALL&)(__CHAR16_TYPE__ const *,__builtin_va_list),vwscanf_s)
#elif (defined(__CRT_HAVE__vfwscanf_s_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_vfwscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vc16scanf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vc16scanf_s __LIBC_LOCAL_NAME(vc16scanf_s)
#else /* ... */
#undef __local___localdep_vc16scanf_s_defined
#endif /* !... */
#endif /* !__local___localdep_vc16scanf_s_defined */
__LOCAL_LIBC(c16scanf_s) __ATTR_WUNUSED __ATTR_LIBC_C16SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBDCALL __LIBC_LOCAL_NAME(c16scanf_s))(__CHAR16_TYPE__ const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vc16scanf_s)(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16scanf_s_defined
#define __local___localdep_c16scanf_s_defined
#define __localdep_c16scanf_s __LIBC_LOCAL_NAME(c16scanf_s)
#endif /* !__local___localdep_c16scanf_s_defined */
#else /* (__CRT_HAVE_vwscanf_s && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vwscanf_s || (__CRT_HAVE__vfwscanf_s_l && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$_vfwscanf_s_l || __CRT_HAVE___stdio_common_vfscanf || __CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#undef __local_c16scanf_s_defined
#endif /* (!__CRT_HAVE_vwscanf_s || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vwscanf_s && (!__CRT_HAVE__vfwscanf_s_l || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$_vfwscanf_s_l && !__CRT_HAVE___stdio_common_vfscanf && !__CRT_HAVE_vfscanf && !__CRT_HAVE__vfscanf && !__CRT_HAVE__vfscanf_s && !__CRT_HAVE__IO_vfscanf && !__CRT_HAVE_vfscanf_unlocked && !__CRT_HAVE___vfscanf && ((!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock)) */
#endif /* !__local_c16scanf_s_defined */
