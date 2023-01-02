/* HASH CRC-32:0xf73f850 */
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
#ifndef __local_vwscanf_unlocked_defined
#define __local_vwscanf_unlocked_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc))))
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfwscanf_unlocked_defined
#define __local___localdep_vfwscanf_unlocked_defined
#ifdef __CRT_HAVE_vfwscanf_unlocked
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwscanf_unlocked,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwscanf_unlocked,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc))
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vfwscanf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfwscanf_unlocked __LIBC_LOCAL_NAME(vfwscanf_unlocked)
#else /* ... */
#undef __local___localdep_vfwscanf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vfwscanf_unlocked_defined */
__LOCAL_LIBC(vwscanf_unlocked) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vwscanf_unlocked))(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep_vfwscanf_unlocked)(__LOCAL_stdin, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vwscanf_unlocked_defined
#define __local___localdep_vwscanf_unlocked_defined
#define __localdep_vwscanf_unlocked __LIBC_LOCAL_NAME(vwscanf_unlocked)
#endif /* !__local___localdep_vwscanf_unlocked_defined */
#else /* __LOCAL_stdin && (__CRT_HAVE_vfwscanf_unlocked || __CRT_HAVE_vfwscanf || ((__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE__ungetwc_nolock || __CRT_HAVE_ungetwc))) */
#undef __local_vwscanf_unlocked_defined
#endif /* !__LOCAL_stdin || (!__CRT_HAVE_vfwscanf_unlocked && !__CRT_HAVE_vfwscanf && ((!__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked && !__CRT_HAVE__getwc_nolock && !__CRT_HAVE__fgetwc_nolock && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc) || (!__CRT_HAVE_ungetwc_unlocked && !__CRT_HAVE__ungetwc_nolock && !__CRT_HAVE_ungetwc))) */
#endif /* !__local_vwscanf_unlocked_defined */
