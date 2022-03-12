/* HASH CRC-32:0x7b833bdc */
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
#ifndef __local_fc32scanf_s_defined
#define __local_fc32scanf_s_defined
#include <__crt.h>
#include <features.h>
#if (defined(__CRT_HAVE_vfwscanf_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf_s) || (defined(__CRT_HAVE__vfwscanf_s_l) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$_vfwscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfc32scanf_s_defined
#define __local___localdep_vfc32scanf_s_defined
#if defined(__CRT_HAVE_vfwscanf_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_C32SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vfc32scanf_s,(__FILE *__stream, __CHAR32_TYPE__ const *__format, __builtin_va_list __args),vfwscanf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwscanf_s)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_C32SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vfc32scanf_s,(__FILE *__stream, __CHAR32_TYPE__ const *__format, __builtin_va_list __args),vfwscanf_s,(__stream,__format,__args))
#elif (defined(__CRT_HAVE__vfwscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/vfwscanf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc32scanf_s __NAMESPACE_LOCAL_TYPEHAX(__STDC_INT_AS_SSIZE_T(__LIBKCALL*)(__FILE *,__CHAR32_TYPE__ const *,__builtin_va_list),__STDC_INT_AS_SSIZE_T(__LIBKCALL&)(__FILE *,__CHAR32_TYPE__ const *,__builtin_va_list),vfwscanf_s)
#elif (defined(__CRT_HAVE__vfwscanf_s_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_vfwscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/vfc32scanf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc32scanf_s __LIBC_LOCAL_NAME(vfc32scanf_s)
#else /* ... */
#undef __local___localdep_vfc32scanf_s_defined
#endif /* !... */
#endif /* !__local___localdep_vfc32scanf_s_defined */
__LOCAL_LIBC(fc32scanf_s) __ATTR_WUNUSED __ATTR_LIBC_C32SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBKCALL __LIBC_LOCAL_NAME(fc32scanf_s))(__FILE *__stream, __CHAR32_TYPE__ const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vfc32scanf_s)(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fc32scanf_s_defined
#define __local___localdep_fc32scanf_s_defined
#define __localdep_fc32scanf_s __LIBC_LOCAL_NAME(fc32scanf_s)
#endif /* !__local___localdep_fc32scanf_s_defined */
#else /* (__CRT_HAVE_vfwscanf_s && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$vfwscanf_s || (__CRT_HAVE__vfwscanf_s_l && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$_vfwscanf_s_l || __CRT_HAVE___stdio_common_vfscanf || __CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#undef __local_fc32scanf_s_defined
#endif /* (!__CRT_HAVE_vfwscanf_s || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$vfwscanf_s && (!__CRT_HAVE__vfwscanf_s_l || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$_vfwscanf_s_l && !__CRT_HAVE___stdio_common_vfscanf && !__CRT_HAVE_vfscanf && !__CRT_HAVE__vfscanf && !__CRT_HAVE__vfscanf_s && !__CRT_HAVE__IO_vfscanf && !__CRT_HAVE_vfscanf_unlocked && !__CRT_HAVE___vfscanf && ((!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock)) */
#endif /* !__local_fc32scanf_s_defined */
