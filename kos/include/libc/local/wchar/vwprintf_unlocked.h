/* HASH CRC-32:0x2b7cf362 */
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
#ifndef __local_vwprintf_unlocked_defined
#define __local_vwprintf_unlocked_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfwprintf_unlocked_defined
#define __local___localdep_vfwprintf_unlocked_defined 1
#ifdef __CRT_HAVE_vfwprintf_unlocked
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwprintf_unlocked,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vfwprintf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfwprintf_unlocked __LIBC_LOCAL_NAME(vfwprintf_unlocked)
#else /* ... */
#undef __local___localdep_vfwprintf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vfwprintf_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <libc/local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vwprintf_unlocked) __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vwprintf_unlocked))(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep_vfwprintf_unlocked)(__LOCAL_stdout, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vwprintf_unlocked_defined
#define __local___localdep_vwprintf_unlocked_defined 1
#define __localdep_vwprintf_unlocked __LIBC_LOCAL_NAME(vwprintf_unlocked)
#endif /* !__local___localdep_vwprintf_unlocked_defined */
#else /* (__CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && !__NO_STDSTREAMS */
#undef __local_vwprintf_unlocked_defined
#endif /* (!__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE__fputwc_nolock) || __NO_STDSTREAMS */
#endif /* !__local_vwprintf_unlocked_defined */
