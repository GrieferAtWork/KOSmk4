/* HASH CRC-32:0x89e403f6 */
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
#ifndef __local__vwscanf_l_defined
#define __local__vwscanf_l_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <features.h>
#if defined(__CRT_HAVE_vwscanf) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vwscanf_defined
#define __local___localdep_vwscanf_defined
#ifdef __CRT_HAVE_vwscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_CB,__localdep_vwscanf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))))
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vwscanf __LIBC_LOCAL_NAME(vwscanf)
#else /* ... */
#undef __local___localdep_vwscanf_defined
#endif /* !... */
#endif /* !__local___localdep_vwscanf_defined */
__LOCAL_LIBC(_vwscanf_l) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vwscanf_l))(__WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_vwscanf)(__format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vwscanf_l_defined
#define __local___localdep__vwscanf_l_defined
#define __localdep__vwscanf_l __LIBC_LOCAL_NAME(_vwscanf_l)
#endif /* !__local___localdep__vwscanf_l_defined */
#else /* __CRT_HAVE_vwscanf || (__LOCAL_stdin && (__CRT_HAVE_vfwscanf || __CRT_HAVE_vfwscanf_unlocked || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#undef __local__vwscanf_l_defined
#endif /* !__CRT_HAVE_vwscanf && (!__LOCAL_stdin || (!__CRT_HAVE_vfwscanf && !__CRT_HAVE_vfwscanf_unlocked && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__local__vwscanf_l_defined */
