/* HASH CRC-32:0x9facb761 */
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
#ifndef __local___wcserror_defined
#define __local___wcserror_defined
#include <__crt.h>
#include <libc/errno.h>
#if (defined(__CRT_HAVE__strerror) || defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__strerror_defined
#define __local___localdep__strerror_defined
#ifdef __CRT_HAVE__strerror
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_RPC,__localdep__strerror,(char const *__message),_strerror,(__message))
#elif defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)
__NAMESPACE_LOCAL_END
#include <libc/local/string/_strerror.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__strerror __LIBC_LOCAL_NAME(_strerror)
#else /* ... */
#undef __local___localdep__strerror_defined
#endif /* !... */
#endif /* !__local___localdep__strerror_defined */
#ifndef __local___localdep_convert_mbstowcs_defined
#define __local___localdep_convert_mbstowcs_defined
#ifdef __CRT_HAVE_convert_mbstowcs
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_convert_mbstowcs,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_mbstowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_mbstowcs __LIBC_LOCAL_NAME(convert_mbstowcs)
#else /* ... */
#undef __local___localdep_convert_mbstowcs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_mbstowcs_defined */
#ifndef __local___localdep_convert_wcstombs_defined
#define __local___localdep_convert_wcstombs_defined
#ifdef __CRT_HAVE_convert_wcstombs
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_wcstombs,(__WCHAR_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_wcstombs __LIBC_LOCAL_NAME(convert_wcstombs)
#else /* ... */
#undef __local___localdep_convert_wcstombs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_wcstombs_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__wcserror) __ATTR_IN_OPT(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__wcserror))(__WCHAR_TYPE__ const *__message) {
	static __WCHAR_TYPE__ *__saved = __NULLPTR;
	char const *__newmsg;
	char *__utf8_message;
#ifdef __libc_geterrno
	__errno_t __saved_errno;
#endif /* __libc_geterrno */
	if (__message == __NULLPTR) {
		__newmsg = (__NAMESPACE_LOCAL_SYM __localdep__strerror)(__NULLPTR);
	} else {
		__utf8_message = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__message);
		if __unlikely(!__utf8_message)
			return __NULLPTR;
		__newmsg = (__NAMESPACE_LOCAL_SYM __localdep__strerror)(__utf8_message);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_message);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		if __unlikely(!__newmsg)
			return __NULLPTR;
	}

	/* Convert message. */
#ifdef __libc_geterrno
	__saved_errno = __libc_geterrno();
#endif /* __libc_geterrno */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__saved);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	__saved = (__NAMESPACE_LOCAL_SYM __localdep_convert_mbstowcs)(__newmsg);
#ifdef __libc_geterrno
	__libc_seterrno(__saved_errno);
#endif /* __libc_geterrno */
	return __saved;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___wcserror_defined
#define __local___localdep___wcserror_defined
#define __localdep___wcserror __LIBC_LOCAL_NAME(__wcserror)
#endif /* !__local___localdep___wcserror_defined */
#else /* (__CRT_HAVE__strerror || __CRT_HAVE__strerror_s || __libc_geterrno) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local___wcserror_defined
#endif /* (!__CRT_HAVE__strerror && !__CRT_HAVE__strerror_s && !__libc_geterrno) || (!__CRT_HAVE_convert_mbstowcs && !__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local___wcserror_defined */
