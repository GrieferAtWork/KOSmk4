/* HASH CRC-32:0xe5bb63ac */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vfwscanf_s_defined
#define __local_vfwscanf_s_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE__vfwscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfwscanf) || defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vfwscanf_s_l_defined
#define __local___localdep__vfwscanf_s_l_defined
#ifdef __CRT_HAVE__vfwscanf_s_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vfwscanf_s_l,(__FILE *__stream, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vfwscanf_s_l,(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE___stdio_common_vfwscanf) || defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/_vfwscanf_s_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vfwscanf_s_l __LIBC_LOCAL_NAME(_vfwscanf_s_l)
#else /* ... */
#undef __local___localdep__vfwscanf_s_l_defined
#endif /* !... */
#endif /* !__local___localdep__vfwscanf_s_l_defined */
__LOCAL_LIBC(vfwscanf_s) __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vfwscanf_s))(__FILE *__stream, __WCHAR_TYPE__ const *__format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep__vfwscanf_s_l)(__stream, __format, __NULLPTR, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vfwscanf_s_defined
#define __local___localdep_vfwscanf_s_defined
#define __localdep_vfwscanf_s __LIBC_LOCAL_NAME(vfwscanf_s)
#endif /* !__local___localdep_vfwscanf_s_defined */
#else /* __CRT_HAVE__vfwscanf_s_l || __CRT_HAVE___stdio_common_vfwscanf || __CRT_HAVE_vfwscanf || __CRT_HAVE_vfwscanf_unlocked || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)) */
#undef __local_vfwscanf_s_defined
#endif /* !__CRT_HAVE__vfwscanf_s_l && !__CRT_HAVE___stdio_common_vfwscanf && !__CRT_HAVE_vfwscanf && !__CRT_HAVE_vfwscanf_unlocked && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked)) */
#endif /* !__local_vfwscanf_s_defined */
