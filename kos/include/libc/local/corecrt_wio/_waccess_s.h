/* HASH CRC-32:0xf12592a6 */
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
#ifndef __local__waccess_s_defined
#define __local__waccess_s_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_waccess) || defined(__CRT_HAVE__waccess) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfaccessat) || (defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_waccess_defined
#define __local___localdep_waccess_defined
#ifdef __CRT_HAVE_waccess
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,__localdep_waccess,(__WCHAR_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE__waccess)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,__localdep_waccess,(__WCHAR_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type),_waccess,(__file,__type))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfaccessat) || (defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.unistd/waccess.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_waccess __LIBC_LOCAL_NAME(waccess)
#else /* ... */
#undef __local___localdep_waccess_defined
#endif /* !... */
#endif /* !__local___localdep_waccess_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_waccess_s) __ATTR_WUNUSED __ATTR_IN(1) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_waccess_s))(__WCHAR_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type) {
	if ((__NAMESPACE_LOCAL_SYM __localdep_waccess)(__file, __type) != 0)
		return __libc_geterrno_or(1);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__waccess_s_defined
#define __local___localdep__waccess_s_defined
#define __localdep__waccess_s __LIBC_LOCAL_NAME(_waccess_s)
#endif /* !__local___localdep__waccess_s_defined */
#else /* __CRT_HAVE_waccess || __CRT_HAVE__waccess || (__AT_FDCWD && (__CRT_HAVE_wfaccessat || (__CRT_HAVE_faccessat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local__waccess_s_defined
#endif /* !__CRT_HAVE_waccess && !__CRT_HAVE__waccess && (!__AT_FDCWD || (!__CRT_HAVE_wfaccessat && (!__CRT_HAVE_faccessat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) && ((!__CRT_HAVE_access && !__CRT_HAVE__access && !__CRT_HAVE___access && !__CRT_HAVE___libc_access && (!__AT_FDCWD || !__CRT_HAVE_faccessat)) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local__waccess_s_defined */
