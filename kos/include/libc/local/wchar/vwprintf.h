/* HASH CRC-32:0xf682858d */
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
#ifndef __local_vwprintf_defined
#define __local_vwprintf_defined
#include <__crt.h>
#include <features.h>
#if (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfwprintf_defined
#define __local___localdep_vfwprintf_defined
#ifdef __CRT_HAVE_vfwprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwprintf,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vfwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfwprintf __LIBC_LOCAL_NAME(vfwprintf)
#else /* ... */
#undef __local___localdep_vfwprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vfwprintf_defined */
__NAMESPACE_LOCAL_END
#include <libc/template/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vwprintf) __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vwprintf))(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep_vfwprintf)(__LOCAL_stdout, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vwprintf_defined
#define __local___localdep_vwprintf_defined
#define __localdep_vwprintf __LIBC_LOCAL_NAME(vwprintf)
#endif /* !__local___localdep_vwprintf_defined */
#else /* (__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS */
#undef __local_vwprintf_defined
#endif /* (!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS */
#endif /* !__local_vwprintf_defined */
