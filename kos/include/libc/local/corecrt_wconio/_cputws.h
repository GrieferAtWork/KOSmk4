/* HASH CRC-32:0x1fe405c */
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
#ifndef __local__cputws_defined
#define __local__cputws_defined
#include <__crt.h>
#include <features.h>
#if (defined(__CRT_HAVE__putwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__putwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__putwch_defined
#define __local___localdep__putwch_defined
#if defined(__CRT_HAVE__putwch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,__WINT_TYPE__,__NOTHROW_RPC,__localdep__putwch,(__WCHAR_TYPE__ __ch),_putwch_nolock,(__ch))
#elif defined(__CRT_HAVE__putwch)
__CREDIRECT(,__WINT_TYPE__,__NOTHROW_RPC,__localdep__putwch,(__WCHAR_TYPE__ __ch),_putwch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wconio/_putwch.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__putwch __LIBC_LOCAL_NAME(_putwch)
#else /* ... */
#undef __local___localdep__putwch_defined
#endif /* !... */
#endif /* !__local___localdep__putwch_defined */
#ifndef __local___localdep_file_wprinter_defined
#define __local___localdep_file_wprinter_defined
#if defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_file_wprinter,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter)
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_file_wprinter,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked)
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_file_wprinter,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/file_wprinter.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_file_wprinter __LIBC_LOCAL_NAME(file_wprinter)
#else /* ... */
#undef __local___localdep_file_wprinter_defined
#endif /* !... */
#endif /* !__local___localdep_file_wprinter_defined */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined
#ifdef __CRT_HAVE_wcslen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __str),wcslen,(__str))
#else /* __CRT_HAVE_wcslen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__CRT_HAVE_wcslen */
#endif /* !__local___localdep_wcslen_defined */
__NAMESPACE_LOCAL_END
#include <libc/template/stdtty.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_cputws) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_cputws))(__WCHAR_TYPE__ const *__restrict __str) {
#if defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
	__SIZE_TYPE__ __len = (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__str);
	__SIZE_TYPE__ __ok  = (__NAMESPACE_LOCAL_SYM __localdep_file_wprinter)(__LOCAL_stdtty, __str, __len);
	return __ok >= __len ? 0 : -1;
#else /* __CRT_HAVE_stdtty && (__CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) */
	for (;;) {
		__WCHAR_TYPE__ __ch = *__str++;
		if (!__ch)
			break;
		if ((__NAMESPACE_LOCAL_SYM __localdep__putwch)(__ch) == __WEOF)
			return -1;
	}
	return 0;
#endif /* !__CRT_HAVE_stdtty || (!__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__cputws_defined
#define __local___localdep__cputws_defined
#define __localdep__cputws __LIBC_LOCAL_NAME(_cputws)
#endif /* !__local___localdep__cputws_defined */
#else /* (__CRT_HAVE__putwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__putwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked)) || (__CRT_HAVE_stdtty && (__CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked)) */
#undef __local__cputws_defined
#endif /* (!__CRT_HAVE__putwch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__putwch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked)) && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked)) */
#endif /* !__local__cputws_defined */
